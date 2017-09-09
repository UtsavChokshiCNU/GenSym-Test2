;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GRAPHS (Trend Charts)

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author(s): Joseph E. Devlin


(declare-forward-references
  (parse-graph-expression-with-info function install)
  (send-new-trend-chart-data function)
  (send-trend-chart-activation-deactivation function)
  (item-has-remote-representation-p function)
  (send-trend-chart-slot-change function)
  (in-suspend-resume-p variable activate)
  (send-trend-chart-update-for-clock-discontinuity function)
  (drawing-for-eyes-of-player-p function player))

(declare-forward-reference send-ws-representations-item-moved function)



#+development
(defvar most-recent-trend-chart)

;;; This is bound only in update-trend-chart and in
;;; initialize-after-reading
(defvar current-trend-chart-has-remote-representation-p)

(defun make-trend-chart (class)
  (let ((new-trend-chart
	  (make-frame-using-compound-types class)))
    (set-edges-of-block new-trend-chart
			0
			0
			default-trend-chart-width
			default-trend-chart-height)
    (update-trend-chart-layout new-trend-chart)
; NOTE: bind current-trend-chart-has-remote-representation-p
; if removing the following comment
;    (update-trend-chart-axes new-trend-chart)
    (update-trend-chart new-trend-chart t)
    #+development
    (setf most-recent-trend-chart new-trend-chart)
    new-trend-chart))

(def-slot-value-reclaimer 2d-image-plane-states (image-plane-state-list trend-chart)
  (declare (ignore image-plane-state-list))
  (decache-and-remove-all-image-plane-states-from-trend-chart trend-chart))

(defmacro clone-frame-with-exceptions (slot-names frame &rest other-args-to-clone-frame)
  (loop with bindings = '()
	with restores = '()
	with frame-var = (gensym)
	with new-frame-var = (gensym)
        for slot-name in slot-names
	 as temp-for-slot = (gensym)
	do
    (push `(,temp-for-slot (prog1 (,slot-name ,frame-var)
			     (setf (,slot-name ,frame-var) nil)))
	  bindings)
    (push `(setf (,slot-name ,frame-var) ,temp-for-slot) restores)
	finally
	  (return `(let* ((,frame-var ,frame)
			  ,@bindings
			  (,new-frame-var (clone-frame ,frame-var
						       ,@other-args-to-clone-frame)))
		     ,@restores
		     ,new-frame-var))))
		    

(defvar parent-trend-chart)

(defun get-time-span (trend-chart)
  (let* ((time-axis (trend-chart-time-axis trend-chart))
	 (time-span (data-window-time-span time-axis)))
    (cond ((eq (frame-like-value-key time-span) 'interval)
	   (car (frame-like-value-property time-span 'length)))
	  (t
	   nil))))

(defun get-refresh-interval (trend-chart)
  (time-axis-update-interval (trend-chart-time-axis trend-chart)))

(defparameter default-point-marker-size 5)

#+development
(defvar trace-trend-chart-values 0)
#+development
(defvar drawing-trend-chart-p nil) ; used for debugging guts of windows3
#+development
(defvar trace-trend-chart-painting nil)


(def-named-dynamic-extent grid-painting
  (module trend-chart))

(defvar-of-named-dynamic-extent current-trend-chart grid-painting)
(defvar-of-named-dynamic-extent current-2d-state grid-painting)
(defvar-of-named-dynamic-extent inner-paint-loop-counter grid-painting)
(defvar-of-named-dynamic-extent current-grid-painting-mode grid-painting)
(defvar-of-named-dynamic-extent current-grid-painting-is-full? grid-painting)
(defvar-of-named-dynamic-extent current-grid-painting-color-mode grid-painting)
(defvar-of-named-dynamic-extent current-grid-painting-queue grid-painting)
(defvar-of-named-dynamic-extent current-grid-painting-queue-tail grid-painting)
(defvar-of-named-dynamic-extent current-grid-painting-actions-to-delete grid-painting)
(defvar-of-named-dynamic-extent current-grid-painting-foreground-color-value
    grid-painting)
(defvar-of-named-dynamic-extent current-grid-painting-background-color-value
    grid-painting)
(defvar-of-named-dynamic-extent current-2d-rendering grid-painting)
(defvar-of-named-dynamic-extent current-grid-painting-x-scale grid-painting)
(defvar-of-named-dynamic-extent current-grid-painting-y-scale grid-painting)
(defvar-of-named-dynamic-extent current-grid-painting-earliest-time grid-painting)
(defvar-of-named-dynamic-extent current-grid-painting-latest-time grid-painting)

#+development
(defvar corrected-colors ())

;;; This ornate bit of dreck called `trend-chart-color-value' merely
;;; keeps me from having to shut down G2 when I enter color names
;;; that don't exist while debugging trend-charts.

(defmacro trend-chart-color-value (color defaulting-style)
  (declare (ignore defaulting-style))
  `(map-color-or-metacolor-to-color-value
     ,color))

;;;; Installing a Trend Chart

;; maximum-plots-plots

(defun grant-plot-index? (trend-chart)
  (or
    (loop for i from 0 below
	    (trend-chart-plot-slot-count trend-chart)
	  when (loop for plot being the slot-component-groups
		     of (trend-chart-plots trend-chart)
		     never (eql i (plot-index plot)))
	    return i)
    (extend-trend-chart-plot-slots trend-chart)))

;; Fixed abort bug when more than 20 plots are used
;; in a single trend-chart - (pbk 12/22/95)
;; 'extend-trend-chart-plot-slots now returns the old-size, which
;; 'grant-plot-index? uses as the index

(defun extend-trend-chart-plot-slots (trend-chart)
  (loop with old-size = (trend-chart-plot-slot-count trend-chart)
	with new-size = (+f old-size trend-chart-plot-slot-increment)
	with old-maxima-array = (trend-chart-plot-maxima trend-chart)
	with new-maxima-array =
	    (make-initialized-value-array new-size 'positive)
	with old-minima-array = (trend-chart-plot-minima trend-chart)
	with new-minima-array =
	   (make-initialized-value-array new-size 'negative)
	with old-end-time-array = (trend-chart-plot-end-times trend-chart)
	with new-end-time-array = 
	   (make-initialized-time-array new-size 'negative)
	for i from 0 below old-size
	do
    (mutate-managed-float-array
      new-maxima-array i
      (managed-float-aref old-maxima-array i))
    (mutate-managed-float-array
      new-minima-array i
      (managed-float-aref old-minima-array i))
    (mutate-managed-float-array
      new-end-time-array i
      (managed-float-aref old-end-time-array i))
	finally
	  (setf (trend-chart-plot-slot-count trend-chart) new-size)
	  (setf (trend-chart-plot-maxima trend-chart) new-maxima-array)
	  (setf (trend-chart-plot-minima trend-chart) new-minima-array)
	  (setf (trend-chart-plot-end-times trend-chart) new-end-time-array)
	  (reclaim-managed-float-array old-maxima-array)
	  (reclaim-managed-float-array old-minima-array)
	  (reclaim-managed-float-array old-end-time-array)
	;; maybe, someday do something less heavy-handed here
	;; to get the states in synch with the new state of the trend-chart
	  (decache-and-remove-all-image-plane-states-from-trend-chart
	    trend-chart)
          (return old-size)))


(defun get-plot-by-cell-index (trend-chart cell-index)
  (loop for plot being the slot-component-groups
	    of (trend-chart-plots trend-chart)
	do
          (when (and (plot-is-runnable-p plot)
		     (=f cell-index (plot-number-cell-index plot)))
	    (return plot))))

(defun demand-plot-extrema (trend-chart)
  (unless (trend-chart-plot-maxima trend-chart)
    (setf (trend-chart-plot-maxima trend-chart)
	  (make-initialized-value-array (trend-chart-plot-slot-count
					  trend-chart)
					'positive))
    (setf (trend-chart-plot-minima trend-chart)
	  (make-initialized-value-array (trend-chart-plot-slot-count
					  trend-chart)
					'negative))
    (setf (trend-chart-plot-end-times trend-chart)
	  (make-initialized-time-array (trend-chart-plot-slot-count
					 trend-chart) 
				      'negative))))

(defun clear-states-for-new-plot (trend-chart plot)
  (cond
    ((trend-chart-plot-maxima trend-chart)
     (mutate-managed-float-array
       (trend-chart-plot-minima trend-chart)
       (plot-index plot) (uninitialized-negative-value-flag))
     (mutate-managed-float-array
       (trend-chart-plot-maxima trend-chart)
       (plot-index plot) (uninitialized-positive-value-flag))
     (mutate-managed-float-array
       (trend-chart-plot-end-times trend-chart)
       (plot-index plot) (most-negative-time)))
    (t
     (demand-plot-extrema trend-chart))))

(defun trend-chart-change-check (trend-chart old-value new-value initializing?)
  (unless initializing?
    (unless (equal old-value new-value)
      (update-trend-chart trend-chart t))))

;;; `current-computation-slot-component-group' is the special variable that
;;; holds extra data for the callback function referenced in
;;; update-cell-based-display-computation-style, which is defined in the
;;; DISPLAYS module.

(defvar current-computation-slot-component-group)

(defun update-trend-chart-computation-particulars-if-necessary (trend-chart old-value
							        new-value initializing-p
								plot slot-component-indicator?)
  (unless initializing-p
    (unless (equal old-value new-value)
      (let ((current-computation-slot-component-group plot))
	(when (and (plot-index plot)
		   (not (plot-variable-or-parameter? plot)))
	  (parse-text-for-slot (copy-for-slot-value (cdr (plot-expression plot)))
			       trend-chart
			       (get-slot-description-of-frame
				 'trend-chart-plots trend-chart)
			       nil nil
			       'plot-expression slot-component-indicator?))))))



(defmacro define-standard-graph-component-putter
    (slot-component-name affects-expression-evaluation-p)
  ;; for all user accessible slots which have an immediate storage type
  `(def-slot-component-putter ,slot-component-name
       (trend-chart slot-name slot-component-indicator? new-value initializing?)
     (change-standard-trend-chart-component
       trend-chart slot-name
       ',slot-component-name
       slot-component-indicator?
       new-value initializing?
       ,(if affects-expression-evaluation-p t nil))))

(defun change-standard-trend-chart-component
    (trend-chart slot-name slot-component-name slot-component-indicator?
		 new-value initializing? affects-expression-evaluation-p)
  (let* ((component-group (get-slot-component-group trend-chart slot-name
						    slot-component-indicator?))
	 (old-value (get-slot-component-value
		      trend-chart slot-name nil
		      slot-component-name slot-component-indicator?)))
    (set-slot-component-value trend-chart slot-name nil
			      slot-component-name slot-component-indicator?
			      new-value)
    (trend-chart-change-check trend-chart old-value new-value initializing?)
    (when (and g2-has-v5-mode-windows-p
	       (not initializing?))
      (send-trend-chart-slot-change trend-chart slot-name slot-component-name
				    new-value old-value slot-component-indicator?))
    (when (and affects-expression-evaluation-p
	       (eq slot-name 'trend-chart-plots))
      (update-trend-chart-computation-particulars-if-necessary
	trend-chart old-value new-value initializing?
	component-group slot-component-indicator?))
    new-value))


(define-standard-graph-component-putter end-time nil)
(define-standard-graph-component-putter time-axis-jump-scroll? nil)
(define-standard-graph-component-putter time-axis-scroll-interval nil)
(define-standard-graph-component-putter time-axis-absolute-labels-visible? nil)
(define-standard-graph-component-putter time-axis-relative-labels-visible? nil)
(define-standard-graph-component-putter time-axis-tickmark-frequency nil)
(define-standard-graph-component-putter time-axis-label-alignment nil)
(define-standard-graph-component-putter time-axis-label-format nil)
(define-standard-graph-component-putter time-axis-base-line-visible? nil)
(define-standard-graph-component-putter color-for-time-axis-base-line nil)
(define-standard-graph-component-putter color-for-time-tickmarks nil)
(define-standard-graph-component-putter color-for-time-grid-lines nil)
(define-standard-graph-component-putter time-grid-lines-visible? nil)
(define-standard-graph-component-putter ratio-of-grid-lines-to-time-axis-tickmarks nil)

(define-standard-graph-component-putter value-axis-names nil)
(define-standard-graph-component-putter value-axis-visible? nil)
(define-standard-graph-component-putter value-axis-range-mode nil)
(define-standard-graph-component-putter value-axis-range-slack nil)
(define-standard-graph-component-putter color-for-value-axis-base-line  nil)
(define-standard-graph-component-putter value-axis-base-line-visible?  nil)
(define-standard-graph-component-putter value-axis-tickmark-frequency nil)
(define-standard-graph-component-putter value-axis-labels-visible? nil)
(define-standard-graph-component-putter show-value-labels-as-percent? nil)
(define-standard-graph-component-putter color-for-value-axis-tickmarks nil)
(define-standard-graph-component-putter value-axis-label-significant-digits nil)
(define-standard-graph-component-putter color-for-value-grid-lines nil)
(define-standard-graph-component-putter value-grid-lines-visible? nil)
(define-standard-graph-component-putter ratio-of-grid-lines-to-value-axis-tickmarks nil)
(define-standard-graph-component-putter extra-value-grid-lines nil)
(define-standard-graph-component-putter value-axis-position nil)

(define-standard-graph-component-putter outer-background-color nil)
(define-standard-graph-component-putter outer-border-color nil)
(define-standard-graph-component-putter outer-border-visible? nil)
(define-standard-graph-component-putter data-window-background-color nil)
(define-standard-graph-component-putter data-window-border-color nil)
(define-standard-graph-component-putter data-window-border-visible? nil)
(define-standard-graph-component-putter trend-chart-legend-visible? nil)
(define-standard-graph-component-putter trend-chart-legend-position nil)
(define-standard-graph-component-putter trend-chart-legend-color nil)

(define-standard-graph-component-putter trend-chart-label-visible? nil)
(define-standard-graph-component-putter trend-chart-label-position nil)
(define-standard-graph-component-putter trend-chart-label-color nil)

(define-standard-graph-component-putter point-format-names nil)
(define-standard-graph-component-putter point-visible? nil)
(define-standard-graph-component-putter point-color nil)
(define-standard-graph-component-putter point-frequency nil)

(define-standard-graph-component-putter connector-format-names nil)
(define-standard-graph-component-putter connector-visible? nil)
(define-standard-graph-component-putter connector-line-color nil)
(define-standard-graph-component-putter connector-line-style nil)
(define-standard-graph-component-putter connector-line-width nil)
(define-standard-graph-component-putter connector-shading-target nil)

(define-standard-graph-component-putter plot-names nil)   
(define-standard-graph-component-putter plot-axis  nil)
(define-standard-graph-component-putter plot-point-format nil)
(define-standard-graph-component-putter plot-connector-format nil)
(define-standard-graph-component-putter plot-wait-interval t)
(define-standard-graph-component-putter plot-update-priority t)
(define-standard-graph-component-putter plot-request-data-seeking? t)
(define-standard-graph-component-putter plot-request-event-updates? t)
(define-standard-graph-component-putter plot-use-simulator? t)
(define-standard-graph-component-putter plot-tracing-and-breakpoints t)
(define-standard-graph-component-putter include-in-legend? nil)

(def-slot-component-putter plot-update-interval
    (trend-chart slot-name slot-component-indicator?
		 new-value initializing?)
  (change-standard-trend-chart-component trend-chart
					 slot-name
					 'plot-update-interval
					 slot-component-indicator?
					 new-value
					 initializing?
					 t)
  (update-local-history-specs trend-chart))

(def-slot-putter trend-chart-label-to-display (trend-chart new-label initializing?)
  (let ((old-label (trend-chart-label-to-display trend-chart)))
    (setf (trend-chart-label-to-display trend-chart)
	  new-label)
    (trend-chart-change-check trend-chart old-label new-label initializing?)
    new-label))	 

(defun demand-cell-array (block)
  (unless (cell-array block)
    (change-slot-value block 'cell-array
		       (make-frame 'g2-cell-array))))

(defun delete-old-cells-for-plot (plot trend-chart)
  (let ((cell-array? (cell-array trend-chart))
	(*current-computation-frame* trend-chart)
	(current-computation-component-particulars nil)
	(current-computation-style the-only-dynamic-computation-style)
	(current-block-of-dependent-frame trend-chart)
	managed-array)
    (when cell-array?
      (setq managed-array (g2-cell-array-managed-array cell-array?))

      (when (plot-number-cell-index plot)
	(deactivate-cell-of-g2-cell-array cell-array?
					  (plot-number-cell-index plot))
	(delete-cell-from-g2-cell-array cell-array?
					(plot-number-cell-index plot)))

		
      ;;  (when (active-p trend-chart)
      ;;	(activate-g2-cell-array cell-array?))
      )))

(def-cleanup-slot-component-group plot (trend-chart slot-name plot)
  (declare (ignore slot-name))
  (delete-old-cells-for-plot plot trend-chart)
  (setf (plot-number-cell-index plot) nil)
  (setf (plot-index plot) nil)
  (reclaim-plot-history plot)
  (update-trend-chart trend-chart t))

(def-slot-value-compiler plot-expression (parse-result trend-chart
						       slot-name defining-class?
						       slot-component-name
						       slot-component-group)
  (declare (ignore defining-class?))
  (compile-plot-expression parse-result trend-chart slot-name
			   slot-component-name slot-component-group))

;; The defining-class? arg is not needed and so is ignored for now.  We
;; just threaded this arg through the def-slot-value-compiler mechanism,
;; so compound slots, and their users, should begin to become to deal
;; with them too, presently.  (MHD 1/13/95)



(defun compile-plot-expression (parse-result trend-chart slot-name
				      slot-component-name slot-component-group)
  (declare (ignore slot-name slot-component-name))
  (let* ((*current-computation-frame* trend-chart)
	 (current-computation-component-particulars
	   (slot-value-list
	     'slot-component 'trend-chart-plots nil
	     (slot-component-group-indicator slot-component-group)))
	 (current-computation-style the-only-dynamic-computation-style)
	 (current-block-of-dependent-frame trend-chart)
	 (cell-array (progn (demand-cell-array trend-chart)
			    (cell-array trend-chart))))

    (prog1
	(cond
	  (parse-result
	   ;; returns triple (number-cell-index v-or-p-cell-index parse-result)
	   (when (runnable-p trend-chart)
	     (deactivate-g2-cell-array cell-array))
	   (let* ((number-cell-index (make-empty-expression-cell cell-array))
		  (number-cell 
		    (managed-svref (g2-cell-array-managed-array cell-array)
				   number-cell-index)))
	     (without-consistency-analysis (trend-chart)
	       (with-part-description ((get-default-computation-style-of-class))
		 (update-computation-style-for-trend-chart
		   current-computation-style slot-component-group)
		 (cond ((not (plot-use-local-history? slot-component-group))
			;; register the expression as a variable-or-parameter
			(register-expression-cell-during-compilation
			  cell-array number-cell-index t parse-result
			  '(class variable-or-parameter)))
		       (t
			(register-expression-cell-during-compilation
			  cell-array number-cell-index t parse-result
			  '(or number (unknown-datum) (obsolete-datum)))))
		 (cond ((expression-cell-able-to-compute-p number-cell)
			#+development
			(when (> trace-trend-chart-values 1)
			  (format t "~%----***---- Number Cell Looks Good~%"))
			(update-frame-status trend-chart nil nil))
		       (t
			#+development
			(when (> trace-trend-chart-values 1)
			  (format t "~%----***---- Number Cell Looks Bad~%"))
			(update-frame-status trend-chart 'bad nil)))
		 (when (runnable-p trend-chart)
		   (activate-g2-cell-array cell-array))
		 (phrase-list parse-result
			      number-cell-index
			      nil)))))
	  (t
	   (without-consistency-analysis (trend-chart)
	     (when cell-array
	       (when (runnable-p trend-chart)
		 (deactivate-g2-cell-array cell-array))
	       (change-slot-value trend-chart 'cell-array nil))
	     (update-frame-status trend-chart 'bad nil))))
      
      (reclaim-slot-value-list current-computation-component-particulars))))

;;; `register-plot-conditions-during-compilation' returns a phrase list of
;;; cell indices or nil if any of the expressions is bad.

(defun register-plot-conditions-during-compilation (trend-chart condition-expressions)
  (let* ((*current-computation-frame* trend-chart)
	 (current-computation-component-particulars nil)
	 (current-computation-style the-only-dynamic-computation-style)
	 (current-block-of-dependent-frame trend-chart)
	 (cell-array (progn (demand-cell-array trend-chart)
			    (cell-array trend-chart)))
	 (result nil))
    (when (runnable-p trend-chart)
      (deactivate-g2-cell-array cell-array))
    (without-consistency-analysis (trend-chart)
      (with-part-description ((get-default-computation-style-of-class))
	(loop for condition-expression in condition-expressions
	      do
	  (let* ((cell-index (make-empty-expression-cell cell-array))
		 (expression-cell 
		   (managed-svref (g2-cell-array-managed-array cell-array)
				  cell-index)))
	    (register-expression-cell-during-compilation
	      cell-array cell-index t condition-expression
	      '(or symbol integer))
	    (cond ((expression-cell-able-to-compute-p expression-cell)
		   #+development
		   (when (> trace-trend-chart-values 1)
		     (format t "~%----***---- Condition Cell Looks Good~%"))
		   (phrase-push cell-index result))
		  (t
		   #+development
		   (when (> trace-trend-chart-values 1)
		     (format t "~%----***---- Number Cell Looks Bad~%"))
		   (setq result nil)
		   (return)))))))
    (when (runnable-p trend-chart)
      (activate-g2-cell-array cell-array))
    result))

(def-slot-value-writer fake-conditional-plotting-spec (slot-value trend-chart)
  (declare (ignore slot-value trend-chart))
  (twrite-string "1"))

(def-slot-value-compiler fake-conditional-plotting-spec
    (parse-result trend-chart)
  (let* ((*current-computation-frame* trend-chart)
	 (current-computation-component-particulars nil)
	 (current-computation-style the-only-dynamic-computation-style)
	 (current-block-of-dependent-frame trend-chart)
	 (cell-array (progn (demand-cell-array trend-chart)
			    (cell-array trend-chart)))
	 (result nil)
	 (condition-expression '(g2-lambda
				 ((local-1 number)
				  (local-2 number))
				 (if-expression (< local-1 local-2) 1 2))))
    (when (runnable-p trend-chart)
      (deactivate-g2-cell-array cell-array))
    (without-consistency-analysis (trend-chart)
      (with-part-description ((get-default-computation-style-of-class))
	(let* ((cell-index (make-empty-expression-cell cell-array))
	       (expression-cell 
		 (managed-svref (g2-cell-array-managed-array cell-array)
				cell-index)))
	  (register-expression-cell-during-compilation
	    cell-array cell-index t condition-expression
	    '(or symbol integer))
	    (cond ((expression-cell-able-to-compute-p expression-cell)
		   #+development
		   (when (> trace-trend-chart-values 1)
		     (format t "~%----***---- Condition Cell Looks Good~%"))
		   (phrase-push cell-index result))
		  (t
		   #+development
		   (when (> trace-trend-chart-values 1)
		     (format t "~%----***---- Number Cell Looks Bad~%"))
		   (setq result nil))))))
    (when (runnable-p trend-chart)
      (activate-g2-cell-array cell-array))
    (phrase-list result parse-result)))

#+soon
(def-slot-putter trend-chart-plotting-conditions
    (trend-chart new-condition-text initializing?)
  (format t "new-cond=~s~%" new-condition-text)
  (let* ((new-condition (car new-condition-text))
	 (cell-index-list (car new-condition))
	 (old-expression (trend-chart-plotting-conditions trend-chart)))
    (unless initializing?
      (let ((cell-array? (cell-array trend-chart)))
	(when cell-array?
	  (register-expression-cell-during-slot-putter
	    cell-array? (car cell-index-list) t)))
      (setf (trend-chart-plot-condition-indices trend-chart)
	    (copy-for-slot-value cell-index-list)))
    (setf (trend-chart-plotting-conditions trend-chart)
	  new-condition-text)
    (trend-chart-change-check
      trend-chart
      old-expression
      (trend-chart-plotting-conditions trend-chart)
      initializing?)
    (trend-chart-plotting-conditions trend-chart)))


(defun plot-is-runnable-p (plot)
  (plot-index plot))

(defun plot-has-data-p (plot)
  (and (plot-index plot)
       (let ((history? (plot-history plot)))
	 (and history?
	      (generic-history-valid-p history?)
	      (>f (generic-history-count history?) 0)))))

;;; The following scheme is designed to reduce the number of updates
;;; sent to T2 clients when G2 is running in as-fast-as-possible mode.
;;; Will send one update after a pause: this is desirable, as there
;;; may have been several trend-chart updates between the last
;;; representation-update and the pause.
;;; NOTE: this task cannot exist when a trend-chart is not active (it
;;; is cancelled in the deactivate method of trend-chart)

(defun-void send-new-trend-chart-data-task (trend-chart)
  (let ((remote-representation-p
	  (item-has-remote-representation-p trend-chart 'tc-representation)))
    (when remote-representation-p
      (actually-send-new-trend-chart-data-if-necessary trend-chart))
    (unless (and system-is-running
		 (eq 'fast-time (scheduler-mode timing-parameters))
		 remote-representation-p)
      (cancel-task (trend-chart-representation-task? trend-chart)))))

(defparameter trend-chart-representation-interval 2.0)

(defparameter trend-chart-representation-priority 2) ; is this the right choice?

(defun-simple get-trend-chart-representation-interval (trend-chart)
  (declare (ignore trend-chart))
  trend-chart-representation-interval)

;;; This could (should?) be macro-ised to incorporate
;;; schedule-trend-chart-update: the only differences are:
;;; 1. the function to get the refresh-interval,
;;; 2. whether it is real-time,
;;; 3. the actual task function, and (annoyingly)
;;; 4. the fact that the get-trend-chart-representation-interval
;;;    returns a gensym-float, rather than a managed-float

(defun schedule-trend-chart-representation-update (trend-chart)
  (with-temporary-gensym-float-creation schedule-trend-chart-representation-update
    (let* ((refresh-interval? (get-trend-chart-representation-interval trend-chart))
	   (float-refresh-interval?
	    (cond ((fixnump refresh-interval?)
		   (coerce-fixnum-to-gensym-float refresh-interval?))
		  (t refresh-interval?))))
      (when refresh-interval?
	(with-future-scheduling
	    ((trend-chart-representation-task? trend-chart)
	     trend-chart-representation-priority
	     (+e (managed-float-value (clock-get current-real-time))
		 float-refresh-interval?)
	     float-refresh-interval?
	     ;; should this be NIL? what does this argument really imply?
	     ;; just copying maybe-schedule-service-workstations
	     nil 
	     t)
	  (send-new-trend-chart-data-task trend-chart))))))

;;; the following mechanism for sending data is based on always sending
;;; all current clients the same updates. Because initial downloads for
;;; new clients may occur between updates, the first update for a new
;;; client may include some duplicate data.

(defvar sample-and-hold-plot-in-representation-update-p nil)

(defun-void mark-plot-as-needing-all-data-sent (plot)
  (setf (plot-data-tc-representation-end-index? plot) nil))

(defun-simple plot-marked-as-needing-all-data-sent-p (plot)
  (null (plot-data-tc-representation-end-index? plot)))

;;; since this is called as the last form of a defun, I decided not to make
;;; it defun-void. The return value of this function should not be held onto
;;; or interpreted as significant. The form in which it is called
;;; (update-active-trend-chart) has its return value ignored.

(defun-simple send-new-trend-chart-data-if-necessary (trend-chart)
  (and g2-has-v5-mode-windows-p
       (item-has-remote-representation-p
	 trend-chart 'tc-representation)
       (if (eq 'fast-time (scheduler-mode timing-parameters))
	   (or (trend-chart-representation-task? trend-chart)
	       (schedule-trend-chart-representation-update trend-chart))
	   (actually-send-new-trend-chart-data-if-necessary trend-chart))))

(defun-simple actually-send-new-trend-chart-data-if-necessary (trend-chart)
  (let* ((sample-and-hold-plot-in-representation-update-p nil)
	 (new-plot-data? (get-current-plot-data trend-chart nil t))
	 (current-time-p (eq 'current-time
			     (frame-like-value-key (end-time (trend-chart-time-axis
							       trend-chart)))))
	 (new-time-bounds? (collect-time-bounds trend-chart nil t))
	 (new-value-axis-extrema?
	   (collect-value-axis-extrema trend-chart nil t)))
    (when (or new-plot-data? new-time-bounds? new-value-axis-extrema?
	      (and current-time-p sample-and-hold-plot-in-representation-update-p))
      (send-new-trend-chart-data
	trend-chart
	(let ((new-data (allocate-evaluation-structure-inline
			  'current-g2-time
			  (copy-managed-float (clock-get current-g2-time)))))
	  (when new-plot-data?
	    (setf (evaluation-structure-slot new-data 'new-plot-data)
		  new-plot-data?))
	  (when new-time-bounds?
	    (setf (evaluation-structure-slot new-data 'time-bounds)
		  new-time-bounds?))
	  (when new-value-axis-extrema?
	    (setf (evaluation-structure-slot new-data 'value-axis-extrema)
		  new-value-axis-extrema?))
	  new-data)))))

;;; fix this: this is an almost clone of
;;; plot-is-sample-and-hold-p

(defun representation-plot-is-sample-and-hold-p (plot trend-chart)
  (let ((connector-format (get-slot-component-group-by-reference
			    trend-chart plot 'plot-connector-format)))
    (and (connector-visible? connector-format)
	 (not (eq (connector-line-style connector-format) 'interpolated)))))

(defun-simple collect-time-bounds (trend-chart force-p mark-collection-p)
  (let ((new-end-time (fast-time-slot trend-chart trend-chart-end-time))
	(new-timespan (fast-time-slot trend-chart trend-chart-timespan))
	(old-end-time? (time-slot trend-chart trend-chart-last-sent-end-time)))
    (when (or (null old-end-time?)
	      force-p
	      (/=time old-end-time? new-end-time)
	      ;; following non-null because old-end-time? is non-null
	      (/=time (fast-time-slot trend-chart trend-chart-last-sent-timespan)
		      new-timespan))
      (when (or (null old-end-time?)
		mark-collection-p)
	(mutate-time-slot trend-chart trend-chart-last-sent-end-time
			  new-end-time)
	(mutate-time-slot trend-chart trend-chart-last-sent-timespan
			  new-timespan))
      (allocate-evaluation-structure-inline
	'end-time (make-evaluation-float new-end-time)
	'timespan (make-evaluation-float new-timespan)))))

(defun-simple collect-value-axis-extrema (trend-chart force-p mark-collection-p)
  (loop with new-extrema? = nil
	for value-axis being the slot-component-groups
	  of (trend-chart-value-axes trend-chart)
	as old-low-value? = (value-slot value-axis value-axis-last-sent-low-value)
	as old-high-value? = (value-slot value-axis value-axis-last-sent-high-value)
	as new-low-value = (fast-value-slot value-axis value-axis-low-value)
	as new-high-value = (fast-value-slot value-axis value-axis-high-value)
	do
    (when (or force-p
	      (null old-low-value?)
	      (/=e new-low-value old-low-value?)
	      (/=e new-high-value old-high-value?))
      (eval-push
	(allocate-evaluation-structure-inline
	  'chart-element-uid
	  (slot-component-group-indicator value-axis)
	  'low-value
	  (make-evaluation-float new-low-value)
	  'high-value
	  (make-evaluation-float new-high-value))
	new-extrema?)
      (when (or (null old-low-value?)
		 mark-collection-p)
	(mutate-value-slot
	  value-axis value-axis-last-sent-low-value
	  new-low-value)
	(mutate-value-slot
	  value-axis value-axis-last-sent-high-value
	  new-high-value)))
	finally
	  (when new-extrema?
	    (return (allocate-evaluation-sequence new-extrema?)))))

(defun-simple get-current-plot-data (trend-chart get-all-data-p mark-indices-p)
  (with-temporary-gensym-float-creation get-current-plot-data
    (and (trend-chart-active-p trend-chart)
	 (loop with end-time = (fast-time-slot trend-chart trend-chart-end-time)
	       with start-time =
	       (-time end-time (fast-time-slot trend-chart trend-chart-timespan))
	       with plot-data? = nil
	       for plot being each slot-component-group
	       of (trend-chart-plots trend-chart)
	       as plot-has-data-p = (plot-has-data-p plot)
	       as new-plot-data-structure? =
	       (and plot-has-data-p
		    (get-plot-data-structure
		      plot start-time end-time get-all-data-p mark-indices-p))
	       do
	   (when (and plot-has-data-p
		      (representation-plot-is-sample-and-hold-p plot trend-chart))
	     (setf sample-and-hold-plot-in-representation-update-p t))
	   (when new-plot-data-structure?
	     (eval-push new-plot-data-structure? plot-data?))
	       finally
		 (return (and plot-data?
			      (allocate-evaluation-sequence plot-data?)))))))

;;; This function can be used in normal updates (get-all-data-p NIL, mark-indices-p T),
;;; initial subscriptions (get-all-data-p T, mark-indices-p T)
;;; subsequent-subscriptions (get-all-data-p T, mark-indices-p NIL) and
;;; "full redraws" (both T).

(defun-simple get-plot-data-structure
    (plot trend-chart-start-time trend-chart-end-time get-all-data-p mark-indices-p)
  (let* ((history (plot-history plot))
	 (absolute-previous-end-index?
	   (plot-data-tc-representation-end-index? plot))
	 (absolute-previous-earliest-index?
	   (plot-data-tc-representation-earliest-index? plot))
	 (previous-end-time?
	   (time-slot plot plot-data-last-tc-representation-send-time?))
	 ;; is this a performance drag? Should I try to detect the need
	 ;; to calculate this, rather than calculate it each time?
	 (earliest-visible-index
	   (generic-history-index history trend-chart-start-time
				  'inclusive nil))
	 (absolute-earliest-visible-index
	   (map-relative-to-absolute-history-index
	     history earliest-visible-index))
	 (collect-all-data-p
	   (or get-all-data-p
	       (plot-marked-as-needing-all-data-sent-p plot)
	       ;; if the above is nil, then all the following question-marks
	       ;; in this predicate should be actual numbers
	       (<f absolute-earliest-visible-index absolute-previous-earliest-index?)
	       (<time previous-end-time?
		      (generic-history-timestamp history earliest-visible-index))
	       ;; the following is interesting in the clock-discontiuity case
	       ;; (i.e. going from as-fast-as-possible to real-time)
	       #+development
	       (when (<f absolute-previous-end-index?
			 absolute-earliest-visible-index)
		 (cerror
		   "continue" "the indices and timestamps disagree, tell rpenny")
		 t)))
	 ;; this could be a bogus index if no new data in history
	 (start-index
	   (if collect-all-data-p
	       earliest-visible-index
	       (next-generic-history-index
		 history (map-absolute-to-relative-history-index
			   history absolute-previous-end-index?))))
	 (new-end-index
	   (generic-history-index history trend-chart-end-time
				  'inclusive t))
	 (absolute-new-end-index
	   (map-relative-to-absolute-history-index
	     history new-end-index))
	 (current-end-time (generic-history-timestamp history new-end-index)))
    (and (or collect-all-data-p
	     ;; NOTE if absolute-previous-end-index? is NIL, then
	     ;; collect-all-data-p will be non-null
	     (>f absolute-new-end-index absolute-previous-end-index?))
	 (let ((struct
		 (allocate-evaluation-structure-inline
		   'chart-element-uid
		   (slot-component-group-indicator plot)
		   'plot-data
		   (get-plot-data-evaluation-structure
		     plot
		     start-index
		     new-end-index))))
	   (when mark-indices-p
	     (setf (plot-data-tc-representation-end-index? plot)
		   absolute-new-end-index)
	     (mutate-time-slot plot plot-data-last-tc-representation-send-time?
			       current-end-time)
	     (when (or (null absolute-previous-earliest-index?)
		       (/=f absolute-earliest-visible-index
			    absolute-previous-earliest-index? ))
	       (setf (plot-data-tc-representation-earliest-index? plot)
		     absolute-earliest-visible-index)))
	   (when collect-all-data-p
	     (setf (evaluation-structure-slot struct 'history-index-start)
		   (make-evaluation-integer
		     (map-relative-to-absolute-history-index
		       history start-index)))
	     (setf (evaluation-structure-slot struct 'update-note)
		   (make-evaluation-symbol 'renew-full-history)))
	   struct))))

;;; presumes that the plot has data

(defun-simple get-plot-data-evaluation-structure (plot start-index end-index)
  (let* ((history (plot-history plot))
	 (use-simulator? (plot-use-simulator? plot))
	 (history-type (generic-history-type history))
	 (cascaded-ring-buffer (case history-type
				 (cascaded (generic-history-data history))
				 (variable (variable-history-cascaded-ring-buffer history)))))
    (when cascaded-ring-buffer
      (get-trend-chart-history-evaluation-structure-from-cascade
	cascaded-ring-buffer 'number use-simulator? t start-index end-index))))

;;; this is like get-history-evaluation-structure-from-cascade,
;;; but building a more efficient data structure.

(defun-simple get-trend-chart-history-evaluation-structure-from-cascade
    (history-enclosure? data-type storing-simulated-value? use-unix-time-p
			start-index end-index)
  (let ((value-list nil)
	(timestamp-list nil))
    (unless (cascaded-ring-buffer-empty? history-enclosure?)
      (iterate-over-history-using-evaluation-values
	(history-value history-collection-time)
	(history-enclosure? (eq data-type 'truth-value) use-unix-time-p storing-simulated-value?
			    start-index end-index)
	(eval-push history-value value-list)
	(eval-push history-collection-time timestamp-list)))
    (allocate-evaluation-structure-inline
      'history-values
      (allocate-evaluation-sequence (nreverse value-list))
      'history-collection-times
      (allocate-evaluation-sequence (nreverse timestamp-list)))))

(defun verified-value-axis-range-mode (value-axis?)
  (gensym-assert 
    ;; The following indicated drawing mode is superseded.
    ;; - jpg 11/9/00
    (or value-axis? (eq current-drawing-priority
			:draw-as-soon-as-possible)))
  (when value-axis?
    ;; value-axis? may be nil only as indicated above.
    ;; - jpg 11/9/00
    (let ((mode (value-axis-range-mode value-axis?)))
      (cond ((and (eq mode 'fixed)
		  (value-axis-lower-bound? value-axis?))
	     'fixed)
	    ((eq mode 'fixed)
	     'automatic)
	    (t
	     mode)))))

(def-slot-component-putter plot-expression (trend-chart
					     slot-name
					     slot-component-indicator?
					     text-slot-value
					     initializing?)
  #+development
  (unless (frame-of-class-p trend-chart 'trend-chart) ; trend-chart)
    (cerror
      ""
      "plot-expression slot component not supported on this class"))

  (without-consistency-analysis (trend-chart)
  ;; what DOES this (when ...) mean?? !
    (when (and initializing?
	       (not (compilations-up-to-date-p trend-chart))
	       loading-kb-p)
      (when (consp text-slot-value)
	(reclaim-slot-value (car text-slot-value))
	(setf (car text-slot-value) nil)) ;  no-value))
      (note-frame-with-compilation-removed trend-chart)
      (update-frame-status trend-chart 'incomplete initializing?))
  

  (let* ((current-block-of-dependent-frame trend-chart)
	 (expression? (caar text-slot-value))
	 (plot (get-slot-component-group trend-chart
				    slot-name slot-component-indicator?))
	 (old-expression (and plot (plot-expression plot)))
	 (new-plot-index? (or (plot-index plot)
			      (grant-plot-index? trend-chart))))
    #+development
    (unless plot
      (error "How did we get here if there is no plot"))
    (delete-old-cells-for-plot plot trend-chart)
    (cond ((and expression? new-plot-index?)
	   (let ((number-cell-index (cadar text-slot-value))
		 (plot-was-constant-p
		   (and (plot-expression plot)
			(plot-expression-is-constant-p plot))))
	     (setf (plot-number-cell-index plot) number-cell-index)
	     (setf (plot-index plot) new-plot-index?)
	     (setf (plot-expression plot) text-slot-value)
	     (clear-states-for-new-plot trend-chart plot)
	     (when (and (or plot-was-constant-p
			    (plot-expression-is-constant-p plot))
			(plot-history plot))
	       (reclaim-generic-history (plot-history plot))
	       (setf (plot-history plot) nil))
	     (demand-plot-histories trend-chart)
	     (demand-plot-extrema trend-chart)
	     (unless initializing?
	       (let ((cell-array? (cell-array trend-chart)))
		 (when cell-array?
		   (register-expression-cell-during-slot-putter
		     cell-array? number-cell-index t))))
	     ;; when constant delete old history
	     ))
	  (expression?
	   ;; complain about too many plots here !!
	   )
	  (t
	   (decache-and-remove-all-image-plane-states-from-trend-chart
	     trend-chart)
	   (setf (plot-expression plot) nil)
	   (setf (plot-v-or-p-cell-index plot) nil)
	   (setf (plot-number-cell-index plot) nil)
	   (setf (plot-index plot) nil)))
    (trend-chart-change-check
      trend-chart old-expression (plot-expression plot) initializing?)
    (when (and g2-has-v5-mode-windows-p
	       (not initializing?))
      (send-trend-chart-slot-change trend-chart slot-name 'plot-expression
				    (plot-expression plot) old-expression slot-component-indicator?))
    (plot-expression plot))))

(defparameter trend-chart-point-format-frame-notes
  '(polychrome-icon-as-plot-marker))

(def-frame-note-writer polychrome-icon-as-plot-marker (ignore-me)
  (declare (ignore ignore-me))
  (twrite-string "polychrome icon specified for point marker - will ignore."))

(defun remove-trend-chart-point-format-frame-notes (trend-chart)
  (loop for note-type in trend-chart-point-format-frame-notes
	do
    (delete-all-frame-notes-of-type-from-trend-chart
      trend-chart note-type t)))

(def-slot-component-putter point-style (trend-chart slot-name slot-component-indicator?
						    new-value initializing?)
  (let* ((point-format (get-slot-component-group trend-chart
						slot-name slot-component-indicator?))
	 (old-value (point-style point-format)))
    (without-consistency-analysis (trend-chart)
      (set-slot-component-value trend-chart slot-name nil
				'point-style
				slot-component-indicator?
				new-value))
    (let* ((icon-class?
	     (and (eq (frame-like-value-key new-value) 'custom)
		  (frame-like-value-property new-value 'icon-class)))
	   (icon-description?
	     (and icon-class?
		  (classp icon-class?)
		  (get-icon-description-given-class icon-class?))))
      (when (and icon-description?
		 (single-color-icon-description-p icon-description?))
	;; eventually do something
	))
    (when (and g2-has-v5-mode-windows-p
	       (not initializing?))
      (send-trend-chart-slot-change trend-chart slot-name 'point-style
				    (point-style point-format) old-value slot-component-indicator?))
    (trend-chart-change-check
      trend-chart old-value new-value initializing?)
    new-value))

(def-slot-component-putter time-axis-update-interval (trend-chart slot-name
						       slot-component-indicator?
						       new-update-interval
						       initializing?)
    (let* ((time-axis (get-slot-component-group trend-chart
						slot-name slot-component-indicator?))
	   (old-value (time-axis-update-interval time-axis)))
      (set-slot-component-value trend-chart slot-name nil
				'time-axis-update-interval slot-component-indicator?
				new-update-interval)
      (when (and g2-has-v5-mode-windows-p
		 (not initializing?))
	(send-trend-chart-slot-change trend-chart slot-name 'time-axis-update-interval
				      (time-axis-update-interval time-axis)
				      old-value slot-component-indicator?)))
    (reschedule-trend-chart-update trend-chart))

(def-slot-component-putter plot-use-local-history? (trend-chart
							slot-name
							slot-component-indicator?
							use-local-history-p
							initializing?)
  (let* ((plot (get-slot-component-group trend-chart
				    slot-name slot-component-indicator?))
	 (old-value (plot-use-local-history? plot)))
    (set-slot-component-value trend-chart slot-name nil
			    'plot-use-local-history? slot-component-indicator?
			    use-local-history-p)
    (unless (eq old-value use-local-history-p)
      (reclaim-plot-history plot)
      ;; (delete-old-cells-for-plot plot trend-chart)
      )
    ;; start here
    (cond
      ((eq slot-component-indicator? 'default)
       ;; loop over the other plots
       (loop for real-plot being each slot-component-group
	     of (trend-chart-plots trend-chart)
	     as plot-expression? =  (plot-expression real-plot)
	     do
	 (when plot-expression?
	   (parse-text-for-slot (copy-for-slot-value
				  (cdr (plot-expression real-plot)))
				trend-chart
				(get-slot-description-of-frame slot-name trend-chart)
				nil nil
				'plot-expression
				(slot-component-group-indicator real-plot)))))
      (t
       (parse-text-for-slot (copy-for-slot-value (cdr (plot-expression plot)))
			    trend-chart
			    (get-slot-description-of-frame slot-name trend-chart)
			    nil nil
			    'plot-expression slot-component-indicator?)))
    (when (and g2-has-v5-mode-windows-p
	       (not initializing?))
      (send-trend-chart-slot-change trend-chart slot-name 'plot-use-local-history?
				    use-local-history-p
				    old-value slot-component-indicator?))
    (trend-chart-change-check
      trend-chart old-value use-local-history-p initializing?)
    use-local-history-p))

(def-slot-component-putter data-window-time-span (trend-chart
						  slot-name
						  slot-component-indicator?
						  slot-value
						  initializing?)
  (let* ((time-axis (get-slot-component-group
			  trend-chart
			  slot-name slot-component-indicator?))
	 (old-value (data-window-time-span time-axis)))
    (set-slot-component-value trend-chart slot-name nil
			      'data-window-time-span slot-component-indicator?
			      slot-value)
    (prog1
	slot-value
      (update-local-history-specs trend-chart))
    (when (and g2-has-v5-mode-windows-p
	       (not initializing?))
      (send-trend-chart-slot-change trend-chart slot-name 'data-window-time-span
				    slot-value
				    old-value slot-component-indicator?))
    (trend-chart-change-check
	trend-chart old-value slot-value initializing?)
    (let ((data-window-time-span-spec (data-window-time-span time-axis))
	  (total-time-span-spec (total-time-span time-axis)))
      (add-or-delete-trend-chart-note
	trend-chart
	time-axis
	'defaulting-total-timespan
	(and (eq (frame-like-value-key data-window-time-span-spec)
		 'all-history)
	     (eq (frame-like-value-key total-time-span-spec)
		 'data-window))))))

(def-slot-component-putter total-time-span (trend-chart
						  slot-name
						  slot-component-indicator?
						  slot-value
						  initializing?)
  (let* ((time-axis (get-slot-component-group
			  trend-chart
			  slot-name slot-component-indicator?))
	 (old-value (total-time-span time-axis)))
    (set-slot-component-value trend-chart slot-name nil
			      'total-time-span slot-component-indicator?
			      slot-value)
    ;; expiration
    (prog1
	slot-value
      (update-local-history-specs trend-chart))
    (when (and g2-has-v5-mode-windows-p
	       (not initializing?))
      (send-trend-chart-slot-change trend-chart slot-name 'total-time-span
				    slot-value
				    old-value slot-component-indicator?))

    (trend-chart-change-check
	trend-chart old-value slot-value initializing?)    
    (let ((data-window-time-span-spec (data-window-time-span time-axis))
	  (total-time-span-spec (total-time-span time-axis)))
      (add-or-delete-trend-chart-note
	trend-chart
	time-axis
	'defaulting-total-timespan
	(and (eq (frame-like-value-key data-window-time-span-spec)
		 'all-history)
	     (eq (frame-like-value-key total-time-span-spec)
		 'data-window))))))

(defun normalize-value-range-bound (range-bound? old-range-bound?)
  (cond ((and old-range-bound? (null range-bound?))
	 (reclaim-managed-float old-range-bound?)
	 nil)
	((null range-bound?) ; old one is null too
	 nil)
	(t
	 (let ((normalized-bound (or old-range-bound?
				     (make-2d-display-value))))
	   (with-temporary-gensym-float-creation normalize-value-range-bound
	     (mutate-managed-float-value
	       normalized-bound
	       (cond ((fixnump range-bound?)
		      (coerce-fixnum-to-gensym-float range-bound?))
		     ((managed-float-p range-bound?)
		      (managed-float-value range-bound?))
		     (t
		      range-bound?)))
	     normalized-bound)))))

(def-slot-component-putter value-axis-bounds
    (trend-chart slot-name slot-component-indicator? bounds-spec initializing?)
  (let* ((value-axis (get-slot-component-group
			    trend-chart slot-name slot-component-indicator?))
	 (old-bounds-spec (value-axis-bounds value-axis))
	 (old-lower-bound? (value-axis-lower-bound? value-axis))
	 (old-upper-bound? (value-axis-upper-bound? value-axis))
	 (new-bounds-exist? (and (not (eq bounds-spec revert-marker))
				 (not (eq (frame-like-value-key bounds-spec)
					  'none)))))
    (setf (value-axis-lower-bound? value-axis)
	  (normalize-value-range-bound
	    (and new-bounds-exist?
		 (frame-like-value-property bounds-spec 'lower))
	    old-lower-bound?))
    (setf (value-axis-upper-bound? value-axis)
	  (normalize-value-range-bound
	    (and new-bounds-exist?
		 (frame-like-value-property bounds-spec 'upper))
	    old-upper-bound?))
    (set-slot-component-value trend-chart slot-name nil
			      'value-axis-bounds slot-component-indicator?
			      bounds-spec)
    (cond
      ((eq slot-component-indicator? 'default)
       (loop for axis being each slot-component-group
	     of (trend-chart-value-axes trend-chart)
	     do
	 (multiple-value-bind (ignore bounds-inherited-p)
	     (value-axis-bounds axis)
	   (declare (ignore ignore))
	   (when bounds-inherited-p
	     (setf (value-axis-lower-bound? axis)
		   (normalize-value-range-bound
		     (and new-bounds-exist?
			  (frame-like-value-property bounds-spec 'lower))
		     old-lower-bound?))
	     (setf (value-axis-upper-bound? axis)
		   (normalize-value-range-bound
		     (and new-bounds-exist?
			  (frame-like-value-property bounds-spec 'upper))
		     old-upper-bound?))))))
      ((and (not new-bounds-exist?)
	    (value-axis-bounds value-axis))
       (let ((default-bounds-spec
		 (value-axis-bounds value-axis)))
	 (setf (value-axis-lower-bound? value-axis)
	       (normalize-value-range-bound
		 (frame-like-value-property default-bounds-spec 'lower)
		 (value-axis-lower-bound? value-axis)))
	 (setf (value-axis-upper-bound? value-axis)
	       (normalize-value-range-bound
		 (frame-like-value-property default-bounds-spec 'upper)
		 (value-axis-upper-bound? value-axis))))))
	    
    (when (and g2-has-v5-mode-windows-p
	       (not initializing?))
      (send-trend-chart-slot-change trend-chart slot-name 'value-axis-bounds
				    bounds-spec
				    old-bounds-spec slot-component-indicator?))
    (trend-chart-change-check
      trend-chart old-bounds-spec bounds-spec initializing?)
    bounds-spec))


(def-acknowledge-slot-component-group trend-chart-time-axis (trend-chart
							       axis initializing?)
  (declare (ignore axis))
  (unless (or initializing-compound-slot? initializing?)
    (update-trend-chart trend-chart t)))

(def-acknowledge-slot-component-group trend-chart-value-axes (trend-chart
							       axis initializing?)
  (declare (ignore axis))
  (unless (or initializing-compound-slot? initializing?)
    (update-trend-chart trend-chart t)))

(def-acknowledge-slot-component-group trend-chart-connector-formats
    (trend-chart connector-format initializing?)
  (declare (ignore connector-format))
  (unless (or initializing-compound-slot? initializing?)
    (update-trend-chart trend-chart t)))

(def-acknowledge-slot-component-group trend-chart-point-formats
    (trend-chart point-format initializing?)
  (declare (ignore point-format))
  (unless (or initializing-compound-slot? initializing?)
    (update-trend-chart trend-chart t)))

(def-cleanup-slot-component-group value-axis (trend-chart slot-name
							       axis-being-deleted)
  (declare (ignore slot-name))
  (delete-all-frame-notes-of-trend-chart-component-group
    trend-chart axis-being-deleted)
  (update-trend-chart trend-chart t))

(defun update-computation-style-for-trend-chart
       (computation-style plot)
  (reclaim-slot-value (computation-style-scan-interval computation-style))
  (setf (computation-style-scan-interval computation-style)
	(copy-for-slot-value
	  (plot-update-interval-period (plot-update-interval plot))))
  (reclaim-slot-value
    (computation-style-initial-scan-wait-interval computation-style))
  (setf (computation-style-initial-scan-wait-interval computation-style)
	(copy-for-slot-value (plot-wait-interval plot)))
  (setf (computation-style-priority computation-style)
	(plot-update-priority plot))
  (setf (computation-style-value-domain computation-style)
	(if (plot-use-simulator? plot)
	    'simulator
	    'inference-engine))
  (setf (computation-style-may-request-data-seeking computation-style)
	(plot-request-data-seeking? plot))
  (setf (computation-style-may-request-event-updates computation-style)
	(plot-request-event-updates? plot))
  (setf (computation-style-tracing-and-breakpoints computation-style)
	(plot-tracing-and-breakpoints plot)))

(defvar recent-enough-g2-revision-for-trend-charts
  (make-system-version 4 0
		       :quality alpha-release-quality
		       :revision 7))

(def-class-method initialize-after-reading (trend-chart)
  (funcall-superior-method trend-chart)
  (cond ((system-revision-greater-p
	    recent-enough-g2-revision-for-trend-charts
	    system-version-from-kb-being-read)
	 ;; write oper message if first time
	 (notify-user "deleting an obsolete trend-chart")
	 (delete-block-after-reading-kb trend-chart))
	(t
	 (update-trend-chart-layout trend-chart)
	 (let ((current-block-of-dependent-frame trend-chart))
	   (loop for plot being the slot-component-groups
		 of (trend-chart-plots trend-chart)
		 do
	     ;; this could only happen if saved in some strange alpha of 4.0
	     (when (of-class-p (plot-v-or-p-cell-index plot) 'g2-expression-cell)
	       (setf (plot-v-or-p-cell-index plot) nil))
	     (let ((history? (plot-history plot)))
	       (when history?
		 (reclaim-slot-value history?)
		 (setf (plot-history plot) nil))))
	   (demand-plot-histories trend-chart)
	   (demand-plot-extrema trend-chart))
	 (let ((current-trend-chart-has-remote-representation-p
		 (and g2-has-v5-mode-windows-p
		      (item-has-remote-representation-p
			trend-chart 'tc-representation))))
	   (update-trend-chart-axes trend-chart)))))


;;;; History Management

;;; The following group of functions are used by slot compilers/putters,
;;; creation and deletion routines, and activate/deactivate to manage the
;;; existence and state of histories without having to know all the details for
;;; each class and/or situation.

(defun get-local-history-expiration-interval? (trend-chart)
  (let* ((time-axis (trend-chart-time-axis trend-chart))
	 (data-window-time-span-spec (data-window-time-span time-axis))
	 (total-time-span-spec (total-time-span time-axis))
	 (data-window-interval? nil))
    (case (frame-like-value-key data-window-time-span-spec)
      (all-history
       ;; no expriration time
       nil)
      (interval
       (setf data-window-interval?
	     (car (frame-like-value-property
		    data-window-time-span-spec 'length)))))
    (case (frame-like-value-key total-time-span-spec)
      (data-window
       (or
	 data-window-interval?
	 86400))     ; when this default is use a frame note is generated
                     ; see slot-component-putters for details
      (interval
       (let ((total-time-interval (car (frame-like-value-property
					 total-time-span-spec 'length))))
	 (maxf total-time-interval
	       (or data-window-interval? 0)))))))

(defun demand-plot-histories (trend-chart)
  (loop for plot being the slot-component-groups of
	    (trend-chart-plots trend-chart)
	do
    (cond ((plot-history plot)
	   (update-history-for-cell-array-change
	     (plot-history plot)
	     trend-chart
	     (plot-number-cell-index plot)
	     (plot-use-simulator? plot)))
	  (t
	   (setf (plot-history plot)
		 (make-history-for-plot plot trend-chart))))))

(defun validate-plot-histories (trend-chart)
  (loop with any-gross-changes? = nil
        for plot being the slot-component-groups of
	    (trend-chart-plots trend-chart)
	when (plot-history plot)
	  do
	    (when (validate-generic-history (plot-history plot))
	      ;; pretend we never sent anything, so that we will know
	      ;; to send everything
	      (mark-plot-as-needing-all-data-sent plot)
	      (setq any-gross-changes? t))
	finally
	  (return any-gross-changes?)))

(defun plot-expression-is-constant-p (plot)
  (declare (ignore plot))
  nil)

(defun get-constant-expression-from-plot (plot)
  (let ((compiled-expression (caar (plot-expression plot))))
    compiled-expression))

;; plot iteration, bounds
;; history methods

(defun make-history-for-plot (plot trend-chart)
  (let ((*current-computation-frame* trend-chart)
	(variable? (not (plot-use-local-history? plot))))
    (cond (variable?
	   (new-variable-history trend-chart
				 (plot-number-cell-index plot)
				 (plot-use-simulator? plot)))
	  ((plot-expression-is-constant-p plot)
	   (new-constant-history
	     (get-constant-expression-from-plot plot)))
	  (t
	   (new-cascaded-history
	     (get-local-history-expiration-interval? trend-chart)
	     (or (plot-update-interval-granularity? (plot-update-interval plot))
		 (plot-update-interval-period (plot-update-interval plot))))))))

(defun update-local-history-specs (trend-chart)
  (loop for expiration = (get-local-history-expiration-interval?
			   trend-chart)
        for plot being the slot-component-groups of
	    (trend-chart-plots trend-chart)
	as history? = (plot-history plot)
	when (and history?
		  (eq (generic-history-type history?)
		      'cascaded))
	  do
	    (update-cascaded-history-expiration
	      history?
	      expiration
	      (or (plot-update-interval-granularity? (plot-update-interval plot))
		 (plot-update-interval-period (plot-update-interval plot))))))

(defun reset-plot-histories (trend-chart)
  (loop for plot being the slot-component-groups of
	    (trend-chart-plots trend-chart)
    do (reset-plot-history plot)))

(defun reset-plot-history (plot)
  (let ((history? (plot-history plot)))
    (mark-plot-as-needing-all-data-sent plot)
    (when history?
      (reset-generic-history history?))))

(defun reclaim-plot-histories (trend-chart)
  (loop for plot being the slot-component-groups of
	    (trend-chart-plots trend-chart)
    do (reclaim-plot-history plot)))

(defun reclaim-plot-history (plot)
  (let ((history? (plot-history plot)))
    (when history?
      (reclaim-generic-history history? t)
      (setf (plot-history plot) nil))))




;;;; Data Acquisition for Graphs (runtime interface to expression cells)

;;; Most of the functions in this section are only relevant to plots that are not
;;; of variables or parameters with history-keeping-specs.

;; We don't need to be concerned about extrema caching in the following function
;; for precisely the fact that the extrema cache is designed to work with
;; any kind of update mechanism for any kind of history.  The extremum caching code
;; only kicks in when asking for a maximum or minimum.


(defun extend-plot-history (plot value)
  (let ((history (plot-history plot)))
    (case (generic-history-type history)
      (cascaded
       (add-to-cascaded-history history value))
      (local
       #+development
       (error "Local Histories are not supported")
       nil))))

;; *** this needs to start providing "data not present" signals

(def-class-method expression-cell-updated (trend-chart g2-cell-array index
						      old-cache? new-cache?)
  (declare (ignore g2-cell-array))
  (unless
    #+soon
    (loop for non-plot-cell-index
	      in (trend-chart-plot-condition-indices trend-chart)
	  when (=f non-plot-cell-index index)
	    return t)
    nil
    (let* ((trend-chart trend-chart)
	   (plot (get-plot-by-cell-index trend-chart index)))
      #+development
      (when (> trace-trend-chart-values 0)
	(with-temporary-gensym-float-creation expression-cell-updated
	  (format t "ECell(~d) Update old = ~s new = ~s at time=~d~%"
		  index
		  (if (managed-float-p old-cache?)
		      (managed-float-value old-cache?)
		      old-cache?)
		  (if (managed-float-p new-cache?)
		      (managed-float-value new-cache?)
		      new-cache?)
		  (managed-float-value (clock-get current-g2-time)))))
      #+development
      (unless t ; plot
	(format t "Plot for index ~d not currently available~%" index))
      (when (and plot
		 (= index (plot-number-cell-index plot)))
	(cond ((or (numberp new-cache?)
		   (managed-float-p new-cache?))
	       (extend-plot-history plot
				    new-cache?))
	      ((framep new-cache?)
	       (when (and (plot-history plot)
			  (neq old-cache? new-cache?))
		 (remove-generic-history-as-client-to-history-of-variable
		   (plot-history plot)))))))))





;;;; Drawing a Trend-Chart (top-level control)


(def-class-method draw (trend-chart)
  #+development
  (setf corrected-colors nil)
  (draw-trend-chart trend-chart))


(defun draw-trend-chart (trend-chart)
  (cond
    ((block-is-currently-being-dragged-p trend-chart)
     
     ;; don't do anything if focus is not block,
     ;; history will be updated by inference engine,
     ;; so next time a real draw comes around good things will happen.
     (draw-block-outline-in-current-image-plane trend-chart 'foreground))
    (t
     (let ((current-block-of-dependent-frame trend-chart))
       (draw-trend-chart-1 trend-chart)))))

(defun draw-trend-chart-1 (trend-chart)
  (let ((current-block-of-dependent-frame trend-chart)
	(*current-computation-frame* trend-chart))
    (let ((update-rect? (trend-chart-most-recent-update-rect
			  trend-chart)))
      ;; eventually split out an axis-only case
      (cond
	((or (null update-rect?)
	     (<r left-edge-of-draw-area (x-in-window (car update-rect?)))
	     (<r top-edge-of-draw-area (y-in-window (cadr update-rect?)))
	     (>r right-edge-of-draw-area (x-in-window (caddr update-rect?)))
	     (>r bottom-edge-of-draw-area (y-in-window (cadddr update-rect?))))
	 (draw-trend-chart-background trend-chart)
	 (draw-trend-chart-legend trend-chart)
	 (draw-trend-chart-axes trend-chart nil nil)
	 (draw-trend-chart-grid trend-chart))
	(t
	 (draw-trend-chart-grid trend-chart nil))))))

(defun draw-trend-chart-axes-and-grid (trend-chart)
  ;; draws axis with same layout
  ;; draws grid
  (cond
    ((block-is-currently-being-dragged-p trend-chart)
     )
    (t
     (draw-trend-chart-axes trend-chart nil) ; don't erase
     (draw-trend-chart-grid trend-chart))))  ; repaint because axis changed

(defun draw-trend-chart-axes (trend-chart erase-p &optional
					  (updating-p t))
  (cond
    ((block-is-currently-being-dragged-p trend-chart)
     )
    (t
     (draw-or-erase-all-value-axes trend-chart erase-p updating-p))))

(defun draw-trend-chart-legend (trend-chart)
  (draw-or-erase-relative-time-labels trend-chart nil)
  (draw-or-erase-trend-chart-legends trend-chart nil))

(defun trend-chart-state-out-of-date-p (trend-chart 2d-state)
  (with-temporary-gensym-float-creation draw-trend-chart
    (cond
      ((2d-state-last-painting-time 2d-state)
       (let ((last-grid-painting-time
	       (fast-time-slot 2d-state 2d-state-last-painting-time))
	     (axis-compute-time
	       (fast-time-slot trend-chart trend-chart-axis-update-time))
	     (master-end-time
	       (fast-time-slot trend-chart trend-chart-end-time))
	     (master-timespan
	       (fast-time-slot trend-chart trend-chart-timespan)))
	 (or
	     (<time last-grid-painting-time axis-compute-time)
	     (>=time (-time master-end-time last-grid-painting-time)
		     master-timespan))))
      (t
       t))))

(defun draw-trend-chart-grid (trend-chart &optional (force-full-blit? t))
  (cond
    ((block-is-currently-being-dragged-p trend-chart)
     )
    (t
     (draw-trend-chart-grid-1 trend-chart force-full-blit?))))

(defun draw-trend-chart-grid-1 (trend-chart force-full-blit?)
  ;; see event-update-status-of-block-showing
  ;; which will mark a state as missed-redraw?
  ;; should not do anything if bounds never set
  ;; step one update the raster
  (let ((mode nil)
	(previous-end-time? nil))

    (multiple-value-bind (2d-state made-new-rendering-p)
	(get-or-make-trend-chart-state trend-chart)

      (cond ((or (and (postscript-printing-p)
		      (eql printing-pass-number 2))
		 (drawing-for-eyes-of-player-p))
	     ;; (not made-new-rendering-p))
	     (setq mode :printing-pass-2))
	    ((or (not (trend-chart-end-time trend-chart))
		 (not (trend-chart-active-p trend-chart)))
	     (when (or made-new-rendering-p
		       (trend-chart-state-out-of-date-p trend-chart 2d-state))
	       (setq mode :full)))
	    ((or made-new-rendering-p
		 (trend-chart-state-out-of-date-p trend-chart 2d-state)
		 ;; guard againts aborted grid-painting
		 ;; as can happen in player
		 (not (2d-state-end-time 2d-state)))
	     (update-2d-state-time-bounds trend-chart 2d-state nil)
	     (setq mode :full))
	    (t
	     (let ((end-time-for-last-painting
		     (fast-time-slot 2d-state 2d-state-end-time))
		   (master-end-time
		     (fast-time-slot trend-chart trend-chart-end-time)))
	       ;; the following test assumes timespan is constant
	       (cond ((=time end-time-for-last-painting
			     master-end-time)
		      (setq mode :minimal))
		     (t
		      (setq previous-end-time?
			    (save-2d-state-end-time 2d-state))
		      (setq mode :partial))))))

      ;; this following is done to make sure that histories are
      ;; valid when doing a full repaint, it might be necessary
      ;; in other cases, but 
      (when (eq mode :full)
	(loop for plot being each slot-component-group
	      of (trend-chart-plots trend-chart)
	      as history? = (plot-history plot)
	  when history?
	    do
	      (validate-generic-history history?)))
      
      (cond ((and (trend-chart-active-p trend-chart)
		  (trend-chart-end-time trend-chart))

	     ;; this blocks painting past the present because
	     ;; bounds have not been set for future times - 
	     ;; well, not exactly because its not plot specific
	     (unless (eq mode :printing-pass-2)
	       (update-2d-state-time-bounds
		 trend-chart 2d-state (clock-get current-g2-time)))
	     (multiple-value-bind
		 (earliest-time-painted latest-time-painted)
		 ;; least-y-painted greatest-y-painted)
		 ;; in full null any-data-p means erase
		 ;; in partial or minimal it means do not draw
		 (unless (eq mode :printing-pass-2) ; ***
		   (do-grid-painting trend-chart 2d-state mode))
	       
	       (cond
		 ;; stub minimal update for preliminary testing
		 ((or force-full-blit?
		      (eq mode :full))
		  ;; blit the whole thing
		  (draw-grid-rendering trend-chart 2d-state mode)
		  )
		 ((eq mode :partial)
		  ;; scroll on window to the left
		  ;; blit whats on the right
		  (draw-grid-rendering trend-chart 2d-state mode
				       earliest-time-painted
				       latest-time-painted
				       previous-end-time?)
		  )
		 (t
		  ;; do the minimal blit thing using y coordinates if it's possible
		  ;; so blit rectangle can be really small
		  ;; use time bounds at first
		  (draw-grid-rendering trend-chart 2d-state mode
				       earliest-time-painted
				       latest-time-painted)
		  ))

	       (when previous-end-time?
		 (reclaim-managed-float previous-end-time?))
	       (when earliest-time-painted
		 (reclaim-managed-float earliest-time-painted)
		 (reclaim-managed-float latest-time-painted))))
	    (t
	     (when (eq mode :full)
	       (multiple-value-bind
		   (earliest-time-painted latest-time-painted)
		   (do-grid-painting trend-chart 2d-state :clear)
		 (when earliest-time-painted
		   (reclaim-managed-float earliest-time-painted)
		   (reclaim-managed-float latest-time-painted))))

	     (draw-grid-rendering trend-chart 2d-state :clear))))))

(defun save-2d-state-end-time (2d-state)
  (allocate-managed-float
    (fast-time-slot 2d-state 2d-state-end-time)))

(defun update-2d-state-time-bounds (trend-chart 2d-state time?)
  (declare (ignore trend-chart))
  (cond
    (time?
     (mutate-time-slot 2d-state 2d-state-last-painting-time
		       (managed-float-value time?)))
    (t
     (reclaim-time-slot 2d-state 2d-state-last-painting-time))))

(def-ez-float-function compute-trend-chart-time-bounds (trend-chart)
  ((result-end-time float 0.0)
   (result-timespan float 10.0)
   (old-timespan float 10.0)
   (old-time-span-existed-p t nil))
  (when (trend-chart-timespan trend-chart)
    (setf old-timespan
	  (time-slot? trend-chart trend-chart-timespan))
    (setf old-time-span-existed-p t))
  (let* ((desired-timespan? (get-time-span trend-chart))
	 (desired-timespan-as-time?
	   (and desired-timespan? (fixnum-to-time desired-timespan?)))
	 (current-time (managed-float-value (clock-get current-g2-time)))
	 (grid-pane (get-grid-for-trend-chart trend-chart)))
    (cond
      ;; Case 1 Graph at Fixed End Time
      ((and desired-timespan? (grid-end-time? grid-pane))
       (setf result-end-time
	     (+time (fast-time-slot grid-pane grid-end-time?)
		    (managed-float-value (clock-get g2-time-at-start))))
       (setf result-timespan
	     (fixnum-to-time desired-timespan?)))
      ;; Case 2-4: Establish Time Bounds
      (t
       (loop with earliest-time? = nil
	     with latest-time? = nil
	     for plot being the slot-component-groups of
	     (trend-chart-plots trend-chart)
	     do
	 (when (plot-has-data-p plot)
	   (let* ((history (plot-history plot))
		  (earliest-time-for-plot
		    (generic-history-earliest-timestamp
		      history
		      (-time current-time 
			     (if desired-timespan?
				 desired-timespan-as-time? 0.0))))
		  (latest-time-for-plot
		    (generic-history-latest-timestamp
		      history current-time)))
	     (cond (earliest-time? 
		    (setf earliest-time?
			  (mintime earliest-time? earliest-time-for-plot)))
		   (t
		      (setf earliest-time? earliest-time-for-plot)))
	     (cond (latest-time?
		    (setf latest-time?
			  (maxtime latest-time? latest-time-for-plot)))
		   (t
		    (setf latest-time? latest-time-for-plot)))))
	     finally
	       (cond
		 ;; Case 2 No Data
		 ((or (null latest-time?) 
		      (eq (grid-end-time-mode grid-pane) 'current-time))
		  ;;  no data - what to do!
		  (setf result-end-time (managed-float-value (clock-get current-g2-time)))
		  (setf result-timespan
			(fixnum-to-time (or desired-timespan? 300))))
		 ;; Case 3 Whole History Mode
		 ((null desired-timespan?)
		  ;; Previous Time Bounds Exist
		  (when (=time latest-time? earliest-time?)
		    (setf earliest-time?
			  (-time latest-time? 1.0)))
		  (let ((keeping-old-bounds-p nil))
		    (when (trend-chart-end-time trend-chart)
		      (let ((master-end-time
			      (fast-time-slot trend-chart trend-chart-end-time))
			    (master-timespan
			      (fast-time-slot trend-chart trend-chart-timespan)))
			(when
			    (and (<=time latest-time? master-end-time)
				 (>=time earliest-time?
					 (-time master-end-time master-timespan)))
			  (setf keeping-old-bounds-p t)
			  (setf result-end-time master-end-time)
			  (setf result-timespan master-timespan))))
		    (unless keeping-old-bounds-p
		      (let ((timespan
			      (*time 1.5
				     (-time latest-time? earliest-time?))))
			(setf result-end-time (+time earliest-time? timespan))
			(setf result-timespan timespan)))))
		 (t
		  (setf result-end-time latest-time?)
		  (setf result-timespan
			(fixnum-to-time desired-timespan?)))))))
    (unless (and desired-timespan? (grid-end-time? grid-pane))
      (let ((aligned-end-time 
	      (align-end-time-if-necessary
		grid-pane result-end-time result-timespan
		(trend-chart-has-interval-time-labels-p trend-chart))))
	;; this prevents left edge dithering
	(unless desired-timespan?
	  (setq result-timespan
		(+time result-timespan (-time aligned-end-time result-end-time))))
	(setq result-end-time aligned-end-time)))
    (cond ((>time result-timespan max-timespan)
	   (note-trend-chart-timespan-truncated trend-chart result-timespan)
	   (setf result-timespan max-timespan))
	  (t (note-trend-chart-timespan-ok trend-chart)))
    ))

(defparameter trend-chart-time-axis-frame-notes
  '(data-window-timespan-truncated))

(def-frame-note-writer data-window-timespan-truncated (ignore)
  (declare (ignore ignore))
  (twrite-string "the timespan is too large. Truncated to 5.369e8 seconds (about 17 years)"))

(defun remove-trend-chart-time-axis-frame-notes (trend-chart)
  (loop for note-type in trend-chart-time-axis-frame-notes
	do
    (delete-all-frame-notes-of-type-from-trend-chart
      trend-chart note-type nil)))

(defun-void note-trend-chart-timespan-truncated (trend-chart result-timespan)
  (let ((already-noted? (memq 'data-window-timespan-truncated (frame-status-and-notes trend-chart))))
    (unless already-noted?
      (add-or-delete-trend-chart-note
	trend-chart 'trend-chart-time-axis 'data-window-timespan-truncated t)
      (warning-message 1 "~NF has a potential data window timespan value of ~s seconds, which exceeds the maximum value of ~s (about 17 years). Truncating."
	trend-chart result-timespan max-timespan))))

(defun-void note-trend-chart-timespan-ok (trend-chart)
  (add-or-delete-trend-chart-note trend-chart 'trend-chart-time-axis 'data-window-timespan-truncated nil))
	
(defun-void update-trend-chart-task (trend-chart)
  (update-trend-chart trend-chart))

(defun invalidate-trend-chart-renderings (trend-chart)
  (loop for 2d-state in (2d-image-plane-states trend-chart)
	do
    (reclaim-time-slot 2d-state 2d-state-last-painting-time)))

;; update-even-if-not-showing? is supposed to force an update to happen even if
;; the chart is hidden.

(defun update-trend-chart
    (trend-chart &optional update-everything? erase-p update-even-if-not-showing?)
  (let ((current-block-of-dependent-frame trend-chart)
	(current-trend-chart-has-remote-representation-p
	  (and g2-has-v5-mode-windows-p
	       (item-has-remote-representation-p
		 trend-chart 'tc-representation)))
	(*current-computation-frame* trend-chart))
    (reclaim-slot-value
      (trend-chart-most-recent-update-rect trend-chart))
    (setf (trend-chart-most-recent-update-rect trend-chart) nil)
    (demand-plot-extrema trend-chart)
    (cond ((block-is-currently-being-dragged-p trend-chart)
	   (when (if (trend-chart-active-p trend-chart)
		     update-everything?
		     t)
	     (update-trend-chart-layout trend-chart)
	     (update-trend-chart-axes trend-chart)))
	  ((trend-chart-active-p trend-chart)
	   (cond
	     ((or update-even-if-not-showing? (showing-p trend-chart nil))
	      (update-active-trend-chart
		trend-chart update-everything? erase-p))
	     (update-everything? 
	      (update-trend-chart-layout trend-chart)
	      (update-trend-chart-axes trend-chart))))
	  (t
	   (remove-trend-chart-time-axis-frame-notes trend-chart)
	   (update-trend-chart-layout trend-chart)
	   (update-trend-chart-axes trend-chart) ; updates axis-update-time
	   (update-images erase-p trend-chart trend-chart
			  ;; block-bounds
			  (left-edge-of-block trend-chart)
			  (top-edge-of-block trend-chart)
			  (right-edge-of-block trend-chart)
			  (bottom-edge-of-block trend-chart)
			  nil
			  'draw-trend-chart trend-chart)))))

(defun update-active-trend-chart
    (trend-chart update-everything? erase-p &aux
     (gross-changes-to-histories-have-occurred-p
      (validate-plot-histories trend-chart))
     time-bounds-changed-p)
  ;; `ez-float-let*' must be called in temporary-float context
  (with-temporary-gensym-float-creation update-active-trend-chart
    (ez-float-let*
      (((new-end-time new-timespan old-timespan?)
	(compute-trend-chart-time-bounds trend-chart)))
      (setq time-bounds-changed-p
	    (update-master-state trend-chart
				 new-end-time new-timespan))
      (multiple-value-bind (any-data-p
			    bound-has-changed-for-some-axis-p
			    width-of-labels-changed-for-some-axis-p)
	  (establish-plot-bounds trend-chart)
	(declare (ignore any-data-p))
	(cond ((or update-everything?
		   width-of-labels-changed-for-some-axis-p
		   (and new-timespan old-timespan?
			(/=time new-timespan old-timespan?)))
	       (update-trend-chart-layout trend-chart)
	       ;; Since we have updated the layout, time bounds must be recomputed
	       ;; and therefore data bounds within such times
	       (ez-float-let*
		 (((new-end-time new-timespan old-timespan?)
		   (compute-trend-chart-time-bounds trend-chart)))
		 old-timespan?
		 (update-master-state trend-chart
				      new-end-time new-timespan))
	       (establish-plot-bounds trend-chart)
	       (update-trend-chart-axes trend-chart) ; updates axis-update-time
	       (invalidate-trend-chart-renderings trend-chart)
	       (update-images erase-p trend-chart trend-chart
			      (left-edge-of-block trend-chart)
			      (top-edge-of-block trend-chart)
			      (right-edge-of-block trend-chart)
			      (bottom-edge-of-block trend-chart)
			      nil
			      'draw-trend-chart trend-chart)) ; force raster repaint
	      ((or
		 gross-changes-to-histories-have-occurred-p
		 bound-has-changed-for-some-axis-p)
	       (invalidate-trend-chart-renderings trend-chart)
	       (update-images t trend-chart trend-chart
			      (left-edge-of-block trend-chart)
			      (top-edge-of-block trend-chart)
			      (right-edge-of-block trend-chart)
			      (bottom-edge-of-block trend-chart)
			      nil
			      'draw-trend-chart-axes
			      trend-chart t)
	       (unless erase-p
		 (update-trend-chart-axes trend-chart)
		 (update-images nil trend-chart trend-chart
				(left-edge-of-block trend-chart)
				(top-edge-of-block trend-chart)
				(right-edge-of-block trend-chart)
				(bottom-edge-of-block trend-chart)
				nil
				'draw-trend-chart
				trend-chart)))
	      (time-bounds-changed-p ;; scrolling case
	       (with-focused-display-pane
		   (trend-chart (get-grid-for-trend-chart trend-chart))
		 (setf (trend-chart-most-recent-update-rect trend-chart)
		       (slot-value-list current-display-pane-left
					current-display-pane-top
					current-display-pane-right
					current-display-pane-bottom))
		 (update-images erase-p trend-chart trend-chart
				current-display-pane-left
				current-display-pane-top
				current-display-pane-right
				current-display-pane-bottom
				nil
				'draw-trend-chart trend-chart)))
	      
	      (t
	       (multiple-value-bind (grid-left grid-top grid-right grid-bottom)
		   (compute-trend-chart-data-window-bounds trend-chart)
		 (setf (trend-chart-most-recent-update-rect trend-chart)
		       (slot-value-list grid-left grid-top
				       grid-right grid-bottom))
		 (update-images erase-p trend-chart trend-chart
				grid-left grid-top
				grid-right grid-bottom
				nil
				'draw-trend-chart
				trend-chart))))
	(send-new-trend-chart-data-if-necessary trend-chart)))))

(defun compute-trend-chart-data-window-bounds (trend-chart)
  (with-focused-display-pane
      (trend-chart (get-grid-for-trend-chart trend-chart))
    (loop with min-left = current-display-pane-right
	  with min-top  = current-display-pane-bottom
	  with max-right = current-display-pane-left
	  with max-bottom = current-display-pane-top
	  for 2d-state in (2d-image-plane-states trend-chart)
	  do
      (multiple-value-bind (left? top? right? bottom?)
	  (compute-trend-chart-rendering-bounds trend-chart 2d-state
						current-display-pane-left
						current-display-pane-top
						current-display-pane-right
						current-display-pane-bottom)
	(cond
	  (left?
	   (setf min-left (minw min-left left?))
	   (setf min-top (minw min-top top?))
	   (setf max-right (maxw max-right right?))
	   (setf max-bottom (maxw max-bottom bottom?)))
	  (t
	   (return
	     (values current-display-pane-left
		     current-display-pane-top
		     current-display-pane-right
		     current-display-pane-bottom)))))
	  finally
	    (return
	      (values
		(maxw current-display-pane-left
		      (-w min-left 1)) ; fudge
		min-top
		max-right
		max-bottom
		)))))

(defun compute-trend-chart-rendering-bounds (trend-chart 2d-state
						left-edge top-edge
						right-edge bottom-edge)
  ;; returns four values comprising a workspace rectangle
  (with-temporary-gensym-float-creation
      compute-trend-chart-rendering-bounds
    (loop with current-trend-chart = trend-chart
	  with earliest-time? = nil
	  with latest-time? = nil
	  with previous-plot? = nil
	  as plot-index = nil
	  as plot-end-time = nil
	  with width = (-w right-edge left-edge)
	  with plot-time-bounds = (trend-chart-plot-end-times trend-chart)
	  with end-time = (fast-time-slot trend-chart trend-chart-end-time)
	  with timespan = (fast-time-slot trend-chart trend-chart-timespan)
	  with start-time = (-time end-time timespan)
	  for plot being the slot-component-groups of
	  (trend-chart-plots trend-chart)
	  when (plot-has-data-p plot)
	    do
	      (setq plot-index (plot-index plot))
	      (setq plot-end-time (managed-float-aref plot-time-bounds plot-index))
	      (setq latest-time?
		    (cond (latest-time?
			   (maxtime latest-time? plot-end-time))
			  (t
			   plot-end-time)))
	      (cond
		((any-points-painted-p plot 2d-state)
		 (setq earliest-time?
		       (compute-earliest-time-for-plot
			 2d-state plot previous-plot? earliest-time?))
		 (setq previous-plot? plot)
		 )
		(t
		 ))
	  finally
	    ;; update plotting times one final time
	    ;; for width of last plots marker (if any)
	    (cond
	      (earliest-time?
	       (setq earliest-time?
		     (-time earliest-time?
			    (fixnum-to-time
			      (get-plot-width-as-time previous-plot?)))))
	      (t
	       (setq earliest-time? start-time)))
	    (when (or (not latest-time?)
		      (=time latest-time? (most-negative-time))) ; uninitialized
	      (setq latest-time? start-time))
	    (return
	      (values
		(+w left-edge
		    (maxw 0
			  (time-to-fixnum
			    (floor-time (*time (fixnum-to-time width)
					       (-time earliest-time? start-time))
					timespan))))
		top-edge
		(+w left-edge
		    (minw width
			  (time-to-fixnum
			    (ceiling-time (*time (fixnum-to-time width)
						 (-time latest-time? start-time))
					  timespan))))
		bottom-edge))
	  )))
		 

(defun update-master-state (trend-chart new-end-time new-timespan)
  (with-temporary-gensym-float-creation update-master-state
    (when (trend-chart-current-update-time trend-chart)
      (mutate-time-slot trend-chart trend-chart-last-update-time
			(time-slot trend-chart trend-chart-current-update-time)))
    (mutate-time-slot trend-chart trend-chart-current-update-time
		      (managed-float-value (clock-get current-g2-time)))
    (let ((old-end-time? (time-slot? trend-chart trend-chart-end-time))
	  (old-timespan? (time-slot? trend-chart trend-chart-timespan)))
      (mutate-time-slot trend-chart trend-chart-end-time new-end-time)
      (mutate-time-slot trend-chart trend-chart-timespan new-timespan)
      (not (and old-timespan?
		new-timespan
		(=time old-timespan? new-timespan)
		old-end-time?
		new-end-time
		(=time old-end-time? new-end-time))))))

(defun clear-master-state (trend-chart)
  (with-temporary-gensym-float-creation clear-master-state
    (reclaim-time-slot trend-chart trend-chart-last-update-time)
    (reclaim-time-slot trend-chart trend-chart-current-update-time)
    (reclaim-time-slot trend-chart trend-chart-end-time)
    (reclaim-time-slot trend-chart trend-chart-timespan)))

;; establish-plot-bounds also returns whether any bounds have changed

(defun establish-plot-bounds (trend-chart)
  (with-temporary-gensym-float-creation establish-plot-bounds
    (loop with bound-has-changed-for-some-plot-p = nil
	  with bound-has-changed-for-some-axis-p = nil
	  with any-data-p = nil
	  with grid-pane = (get-grid-for-trend-chart trend-chart)
	  with plot-maxima = (trend-chart-plot-maxima trend-chart)
	  with plot-minima = (trend-chart-plot-minima trend-chart)
	  with plot-time-bounds = (trend-chart-plot-end-times trend-chart)
	  with end-time = (fast-time-slot trend-chart trend-chart-end-time)
	  for plot being the slot-component-groups of
	    (trend-chart-plots trend-chart)
	  as plot-index = (plot-index plot)
	     as axis? = (get-slot-component-group-by-reference
			  trend-chart plot 'plot-axis)
	     as range-mode = (and axis? ; only nil when cleaning up
				  (verified-value-axis-range-mode axis?))
	  when (plot-is-runnable-p plot)
	    do
	 ;; the above should evnetually get passed to the next get-current-bounds
	 (ez-float-let*
	   ((((bounds-exist-p t) low-bound high-bound)
	     (get-current-bounds-for-plot
	       trend-chart plot)))
	   (when bounds-exist-p
	     (when (or (plot-has-data-p plot)
		       (not (generic-history-supports-indexed-access-p
			      (plot-history plot))))
	       (cond
		 ((and ; (plot-is-sample-and-hold-p plot)
		       (eq (grid-end-time-mode grid-pane)
			   'current-time))
		  (mutate-managed-float-array plot-time-bounds plot-index
					      (managed-float-value
						(clock-get current-g2-time))))
		 (t
		  (when-let (plot-history (plot-history plot))
		    (mutate-managed-float-array
		      plot-time-bounds plot-index
		      (generic-history-latest-timestamp plot-history end-time))))))
	     (setf any-data-p t))
	   (let ((current-low-bound (managed-float-aref plot-minima plot-index))
		 (current-high-bound (managed-float-aref plot-maxima plot-index))
		 (bound-has-changed-for-this-plot-p nil))
	     (cond ((>value current-low-bound (uninitialized-negative-value-flag)) ; has been set
		    (when (or (/=value current-low-bound low-bound)
			      (/=value current-high-bound high-bound))
		      (setf bound-has-changed-for-this-plot-p t)
		      (mutate-managed-float-array
			plot-minima plot-index low-bound)
		      (mutate-managed-float-array
		        plot-maxima plot-index high-bound)))
		   (bounds-exist-p
		    (setf bound-has-changed-for-this-plot-p t)
		    (mutate-managed-float-array
		      plot-minima plot-index low-bound)
		    (mutate-managed-float-array
		      plot-maxima plot-index high-bound))
		   (t
		    ;; do nothing, I think
		    #+development
		    (when (> trace-trend-chart-values 1)
		     (format t "Doing Nothing: Curlowval=~S~%"
			     current-low-bound))
		    ))
	     (when bound-has-changed-for-this-plot-p
	       (setf bound-has-changed-for-some-plot-p t)
	       (when (and axis?
			  (not (eq range-mode 'fixed)))
		 (setf bound-has-changed-for-some-axis-p t)))
	     #+development
	     (when (> trace-trend-chart-values 1)
	       (format t "~%_____________ low=~s and high=~s ~%"
		       (managed-float-aref plot-minima plot-index)
		       (managed-float-aref plot-maxima plot-index))
	       )))
	     finally
	       (return (values any-data-p
			       bound-has-changed-for-some-axis-p
			       nil)))))

(defun histories-are-present-p (trend-chart)
  (loop for plot being the slot-component-groups of (trend-chart-plots trend-chart)
	thereis (plot-history plot)))

(defun range-bounds-exist-p (value-axis)
  (value-axis-lower-bound? value-axis))  ; must enfore this in compiler!

(defmacro get-range-slack (value-axis)
  `(/e (coerce-fixnum-to-gensym-float
	 (value-axis-range-slack ,value-axis))
       100.0))

(def-ez-float-function get-current-bounds-for-plot
    (trend-chart plot)
  ((data-exists-p t t)            ; init to true because it will be in most cases
   (low-bound float -1.1)
   (high-bound float 1.1))

  (let* ((value-axis (get-slot-component-group-by-reference
		       trend-chart plot 'plot-axis))
	 ;; value-axis can only be nil in recursive descent of cleaning
	 ;; up plots and value-axes
	 (range-bounds-exist-p (and value-axis
				    (range-bounds-exist-p value-axis)))
	 (range-mode (if value-axis
			 (verified-value-axis-range-mode value-axis)
			 'axis-non-existent-during-cleanup))
	 (latest-time (fast-time-slot trend-chart trend-chart-end-time))
	 (earliest-time
	   (-time latest-time
		  (fast-time-slot trend-chart trend-chart-timespan))))

    (case range-mode
      (axis-non-existent-during-cleanup
       (setf data-exists-p nil))
      (fixed
       (cond (range-bounds-exist-p
	      (setf low-bound (fast-value-slot value-axis value-axis-lower-bound?))
	      (setf high-bound (fast-value-slot value-axis value-axis-upper-bound?)))
	     (t
	      (error "Must have bounds for fixed axis bounds computation"))))
      (automatic
       (ez-float-let*
	 ((((history-data-exists-p t) history-low-bound history-high-bound)
	   (get-current-min-and-max-for-plot-from-history
	     trend-chart plot
	     earliest-time latest-time)))
	 (cond ((and history-data-exists-p range-bounds-exist-p)
		(setf low-bound (minvalue history-low-bound
					  (fast-value-slot value-axis
							   value-axis-lower-bound?)))
		(setf high-bound (maxvalue history-high-bound
					   (fast-value-slot value-axis
							    value-axis-upper-bound?))))
	       (range-bounds-exist-p
		(setf low-bound (fast-value-slot value-axis value-axis-lower-bound?))
		(setf high-bound (fast-value-slot value-axis value-axis-upper-bound?)))
	       (history-data-exists-p
		(cond ((=value history-low-bound history-high-bound)
		       (setf low-bound (-value history-low-bound 1.0)) 
		       (setf high-bound (+value history-high-bound 1.0)))
		      (t
		       (setf low-bound history-low-bound)
		       (setf high-bound history-high-bound))))
	       (t
		(setf data-exists-p nil)))
	 ;; Bounds Fudging (otherwise known as anti-hysteresis)
	 (when (and data-exists-p
		    history-data-exists-p)
	   (let* ((index (plot-index plot))
		  (old-high-bound (managed-float-aref
				    (trend-chart-plot-maxima trend-chart) index))
		  (old-low-bound (managed-float-aref
				   (trend-chart-plot-minima trend-chart) index))
		  (old-range (-value old-high-bound old-low-bound))
		  (range (-value high-bound low-bound))
		  (range-slack (get-range-slack value-axis))
		  (fudge (*value range range-slack))
		  (epsilon (*value old-range range-slack)))
	     (setf high-bound
		   (cond ((or (=value old-high-bound (uninitialized-positive-value-flag))
			      (>value high-bound old-high-bound))
			  (minvalue (+value high-bound fudge)
				    (most-positive-value)))
			 ((<value high-bound (-value old-high-bound epsilon))
			 (/value (+value high-bound old-high-bound) 2.0))
			 (t
			  old-high-bound)))
	     (setf low-bound
		   (cond ((or (=value old-low-bound (uninitialized-negative-value-flag))
			      (<value low-bound old-low-bound))
			  (maxvalue (-value low-bound fudge)
				    (most-negative-value)))
			 ((>value low-bound (+value old-low-bound epsilon))
			  (/value (+value low-bound old-low-bound) 2.0))
			 (t
			 old-low-bound)))
	     ))))
      (high-water-marking
       (cond
	 ((and (plot-has-data-p plot)
	       (generic-history-high-water-marks-exist-p
		 (plot-history plot)))
	  (let* ((history (plot-history plot))
		 (index (plot-index plot))
		 (current-fudged-hwm (managed-float-aref
				(trend-chart-plot-maxima trend-chart) index))
		 (current-fudged-lwm (managed-float-aref
				(trend-chart-plot-minima trend-chart) index))
		 (high-water-mark (generic-history-high-water-mark history))
		 (low-water-mark (generic-history-low-water-mark history)))
	    (cond ((and (/=value current-fudged-hwm (uninitialized-positive-value-flag))
			;; why not (/=value current-fudged-lwm (most-negative-val
			(<value high-water-mark current-fudged-hwm)
			(>value low-water-mark current-fudged-lwm))
		   (setf high-bound current-fudged-hwm)
		   (setf low-bound current-fudged-lwm))
		  (t
		   (let* ((range (-value high-water-mark low-water-mark))
			  (range-slack (get-range-slack value-axis))
			  (fudge (*value range range-slack)))
		     (setf
		       high-bound
		       (if (or (=value current-fudged-hwm (uninitialized-positive-value-flag))
			       (>=value high-water-mark current-fudged-hwm))
			   (minvalue (+value high-water-mark fudge)
				     (most-positive-value))
			   current-fudged-hwm))
		     (setf
		       low-bound
		       (if (or (=value current-fudged-lwm (uninitialized-negative-value-flag))
			       (<=value low-water-mark current-fudged-lwm))
			   (maxvalue (-value low-water-mark fudge)
				     (most-negative-value))
			   current-fudged-lwm))))))
	  )
	 (t
	  (setf data-exists-p nil)))))))

(def-ez-float-function get-current-min-and-max-for-plot-from-history
    (trend-chart plot earliest-time latest-time)
  ((data-exists-p t nil)
   (low-bound float -1.1)
   (high-bound float 1.1))

  (unless (histories-are-present-p trend-chart)
    (ez-float-return))

  (let ((history (plot-history plot)))
    (when (plot-has-data-p plot)
      (cond
	((not (eq (generic-history-type history) 'constant))
	 (let* ((start-index (generic-history-index
			       history earliest-time 'inclusive t))
		(end-index (generic-history-index
			     history latest-time 'inclusive nil)))
	   (cond ((<=time earliest-time
			  (generic-history-timestamp history start-index)
			  (generic-history-timestamp history end-index)
			  latest-time)
		  (let ((low-bound-index (generic-history-minimum-value-index
					   history start-index end-index))
			(high-bound-index (generic-history-maximum-value-index
					    history start-index end-index)))
		    (setf data-exists-p t)
		    (setf high-bound (generic-history-value history
							    high-bound-index))
		    (setf low-bound (generic-history-value history
							   low-bound-index))))
		 (t
		  (setf data-exists-p nil)))))
	(t
	 (setf data-exists-p t)
	 (setf high-bound (generic-history-value history 0))
	 (setf low-bound (generic-history-value history 0)))))))


(defun get-grid-for-trend-chart (trend-chart)
  (loop for sub-pane in (display-pane-sub-panes
			  (trend-chart-pane-tree trend-chart))
	when (eq (display-pane-type sub-pane) 'grid-pane)
	  return sub-pane))

(defun get-legend-for-trend-chart (trend-chart)
  (loop for sub-pane in (display-pane-sub-panes
			  (trend-chart-pane-tree trend-chart))
	when (eq (display-pane-type sub-pane) 'legend-pane)
	  return sub-pane))

(defun draw-trend-chart-background (trend-chart)
  (let ((trend-chart-pane (trend-chart-pane-tree trend-chart)))
    (with-focused-display-pane
	(trend-chart (get-grid-for-trend-chart trend-chart))
      (paint-rectangle-frame-in-current-image-plane
	(left-edge-of-block trend-chart)
	(top-edge-of-block trend-chart)
	(right-edge-of-block trend-chart)
	(bottom-edge-of-block trend-chart)
	current-display-pane-left
	current-display-pane-top
	current-display-pane-right
	current-display-pane-bottom
	(display-pane-background-color trend-chart-pane))
      (draw-border-for-display-pane
	trend-chart trend-chart-pane)
      (draw-data-window-border
	trend-chart (get-grid-for-trend-chart trend-chart)))))

(defun-void draw-data-window-border (trend-chart display-pane)
  (let ((border-style? (display-pane-border-style? display-pane))
	(color-value (trend-chart-color-value
		       (display-pane-border-color display-pane)
		       foreground))
	(line-width-in-workspace 1))
    (when border-style?
      (with-focused-display-pane (trend-chart display-pane)
	(let* ((left-edge-in-window (x-in-window current-display-pane-left))
	       (top-edge-in-window (y-in-window current-display-pane-top))
	       (right-edge-in-window (x-in-window current-display-pane-right))
	       (bottom-edge-in-window (y-in-window current-display-pane-bottom))
	       (x-width-in-window
		 (if (=w line-width-in-workspace 0)
		     1
		     (maxr 1
			   (delta-x-in-window
			     line-width-in-workspace
			     current-image-x-scale))))
	       (y-width-in-window
		 (if (=w line-width-in-workspace 0)
		     1
		     (maxr 1
			   (delta-y-in-window
			     line-width-in-workspace
			     current-image-y-scale)))))
	  (paint-rectangle-outline-in-window
	    (-r left-edge-in-window x-width-in-window)
	    (-r top-edge-in-window y-width-in-window)
	    (+r right-edge-in-window x-width-in-window)
	    (+r bottom-edge-in-window y-width-in-window)
	    color-value x-width-in-window y-width-in-window))))))

(defun draw-border-for-display-pane (trend-chart display-pane)
  (let ((border-style? (display-pane-border-style? display-pane)))
    (when border-style?
      (with-focused-display-pane (trend-chart display-pane)
	(paint-rectangle-outline-in-current-image-plane	  
	  (-w current-display-pane-left 1)
	  (-w current-display-pane-top 1)
	  (+w current-display-pane-right 1)
	  (+w current-display-pane-bottom 1)
	  (display-pane-border-color display-pane)
	  (if (eq border-style? 'hairline) 0 border-style?))))))

(defun draw-grid-rendering (trend-chart 2d-state mode
			    &optional boxed-earliest-time?
			              boxed-latest-time?
				      previous-end-time?)
  (declare (ignore boxed-earliest-time?
		   boxed-latest-time?
		   previous-end-time?))
  (with-temporary-gensym-float-creation draw-grid-rendering
    (with-named-dynamic-extent* grid-painting
	((current-graph-rendering (2d-state-rendering 2d-state))
	 (current-2d-rendering current-graph-rendering)
	 (current-trend-chart trend-chart)
	 (current-2d-state 2d-state)
	 (current-grid-painting-is-full? t)
	 (current-grid-painting-queue nil)
	 (current-grid-painting-queue-tail nil)
	 (current-grid-painting-actions-to-delete nil)
	 (current-grid-painting-x-scale
	   (x-scale-of-graph-rendering current-2d-rendering))
	 (current-grid-painting-y-scale
	   (y-scale-of-graph-rendering current-2d-rendering))
	 (current-grid-painting-background-color-value
	   (grid-background-color-value current-graph-rendering))
	 (current-grid-painting-color-mode (color-painting-mode current-graph-rendering))
	 (current-grid-painting-latest-time nil)
	 (current-grid-painting-earliest-time nil)
	 (inner-paint-loop-counter 0))
      (when (printing-p)
	(update-color-values-for-trend-chart
	  trend-chart current-2d-rendering
	  (data-window-background-color (trend-chart-format trend-chart)))
	(setup-grid-painting-time-bounds)
	(cond ((eq mode :clear)
	       (setf (line-drawing-description-for-graph-rendering?
		       current-graph-rendering)
		     '((graph) (2d-call-back-partial)))) ; hack for clearing
	      (t
	       (setf (line-drawing-description-for-graph-rendering?
		       current-graph-rendering)
		     '((graph) (2d-call-back-full))))))
      
      (with-focused-display-pane
	  (trend-chart (get-grid-for-trend-chart trend-chart))
	(let ((2d-rendering (2d-state-rendering 2d-state))
	      ;; for printing (do-grid-painting)
	      (left-edge-in-window (x-in-window current-display-pane-left))
	      (top-edge-in-window (y-in-window current-display-pane-top))
	      (right-edge-in-window (x-in-window current-display-pane-right))
	      (bottom-edge-in-window (y-in-window current-display-pane-bottom)))
	  (record-lru-element-usage 2d-rendering graph-rendering-lru-queue)
	  ;; Doing this here (as opposed to within 
	  ;; add-from-graph-rendering-to-current-window) means that it will
	  ;; not be done for Telewindows processes, only for the G2 process.
	  ;; This is consistent with the fact that no independent decaching
	  ;; is done in the Telewindows processes (see documentation for
	  ;; delete-graph-rendering-and-reclaim-icp-index).
	  (clear-data-clipping-rectangles)
	  (let (#+development
		  (drawing-trend-chart-p t))
	    (draw-graph-rendering
	      left-edge-in-window top-edge-in-window 
	      right-edge-in-window bottom-edge-in-window
	      (color-values-for-rasters? 2d-rendering)
	      2d-rendering))))
      (when (printing-p)
	(reclaim-painting-queue)
	(delete-painting-actions-or-args current-grid-painting-actions-to-delete)
	(reclaim-managed-float current-grid-painting-earliest-time)
	(reclaim-managed-float current-grid-painting-latest-time))))
  )


(defun update-grid-clipping (trend-chart 2d-state earliest-time
					 latest-time x-scale y-scale)
  (let ((current-2d-state 2d-state)
	(current-trend-chart trend-chart))
    (let* ((abstract-x1 (time-to-abstract-x earliest-time))
	   (abstract-x2 (time-to-abstract-x latest-time))
	   (ring-raster-x1 (abstract-x-start-to-unscaled-ring-raster abstract-x1))
	   (ring-raster-x2 (abstract-x-end-to-unscaled-ring-raster abstract-x2)))
      ;; this test says don't clip if the whole raster is
      ;; desired, but in a rather indirect fashion
      (unless (and (=f ring-raster-x1 ring-raster-x2)
		   (>f abstract-x2 abstract-x1))
	;; the following hack feeds the right numbers to
	;; the cruftiferous ring-raster blitting code
	(when (=f ring-raster-x2 (2d-state-virtual-origin-x current-2d-state))
	  (decff ring-raster-x2))
	;; make bounds at least as wide as width of draw-area - FUDGE
	(let ((width-of-draw-area (-r right-edge-of-draw-area
				      left-edge-of-draw-area))
	      (scaled-width-of-raster
		(delta-x-in-window
		  (2d-state-grid-width 2d-state)
		  y-scale))
	      (scaled-rr-1 (delta-x-in-window ring-raster-x1 x-scale))
	      (scaled-rr-2 (delta-x-in-window ring-raster-x2 x-scale)))
	(update-graph-data-extrema                      ; from windows3
	  (minr scaled-rr-1
		(maxr 0
		      (-r scaled-rr-2 (+r width-of-draw-area 0))))
	  (delta-y-in-window 0 y-scale)
	  (maxr scaled-rr-2
		(minr scaled-width-of-raster
		      (+r scaled-rr-1 (+r width-of-draw-area 0))))
	  (delta-y-in-window (2d-state-grid-height 2d-state)
			     y-scale)))))))
 
(defun calculate-window-position-for-time (trend-chart 2d-state
						       time x-scale)
  (let ((current-2d-state 2d-state)
	(current-trend-chart trend-chart))
    (let* ((abstract-x1 (time-to-abstract-x time))
	   (ring-raster-x (abstract-x-end-to-unscaled-ring-raster abstract-x1)))
      (delta-x-in-window
	(-f ring-raster-x
	    (2d-state-virtual-origin-x 2d-state))
	x-scale))))
  
(defun reset-value-array (value-array polarity)
  (with-temporary-gensym-float-creation reset-value-array
    (loop for i from 0 below (managed-float-array-length value-array)
	  do
      (cond
	((eq polarity 'negative)
	 (mutate-managed-float-array value-array i (uninitialized-negative-value-flag)
				     ))
	(t
	 (mutate-managed-float-array value-array i (uninitialized-positive-value-flag)
				     ))))))

(defun reset-time-array (time-array polarity)
 (with-temporary-gensym-float-creation reset-time-array
   (loop for i from 0 below (managed-float-array-length time-array)
	 do
     (cond
       ((eq polarity 'negative)
	(mutate-managed-float-array time-array i (most-negative-time)
				    ))
       (t
	(mutate-managed-float-array time-array i (most-positive-time)
				    ))))))

(defun reset-trend-chart-image-plane-states (trend-chart)
  (reset-value-array (trend-chart-plot-maxima trend-chart)
		     'positive)
  (reset-value-array (trend-chart-plot-minima trend-chart)
		     'negative)
  (reset-time-array (trend-chart-plot-end-times trend-chart)
		    'negative)
  (loop for state in (2d-image-plane-states trend-chart)
	do
    (clear-incomplete-painting-actions state)
    (reclaim-time-slot state 2d-state-latest-current-data-time)
    (reclaim-time-slot state 2d-state-last-painting-time)))
  

(def-class-method activate (trend-chart)
  (unless in-suspend-resume-p
    (let* ((trend-chart trend-chart)
	   (current-block-of-dependent-frame trend-chart))
      (let ((cell-array? (cell-array trend-chart)))
	(when cell-array?
	  (activate-g2-cell-array cell-array?)))
      (demand-plot-extrema trend-chart)
      (reset-trend-chart-image-plane-states trend-chart)
      (demand-plot-histories trend-chart)
      (setf (trend-chart-active-p trend-chart) t)
      (send-trend-chart-activation-deactivation trend-chart t)
      (schedule-trend-chart-update trend-chart))))

(defun schedule-trend-chart-update (trend-chart)
  (with-temporary-gensym-float-creation schedule-trend-chart-update
    (let* ((refresh-interval? (get-refresh-interval trend-chart))
	   (float-refresh-interval?
	    (cond ((fixnump refresh-interval?)
		   (coerce-fixnum-to-gensym-float refresh-interval?))
		  (refresh-interval?
		   (managed-float-value refresh-interval?)))))
      (when refresh-interval?
	(with-future-scheduling
	    ((trend-chart-update-task? trend-chart)
	     2 ; *** priority -- look at doc for good choice and make a parameter
	     (+e (managed-float-value (clock-get current-g2-time))
		 float-refresh-interval?)
	     float-refresh-interval?)
	  (update-trend-chart-task trend-chart))))))
  
(defun reschedule-trend-chart-update (trend-chart)
  (when (trend-chart-active-p trend-chart)
    (cancel-task (trend-chart-update-task? trend-chart))
    (schedule-trend-chart-update trend-chart)))

(def-class-method deactivate (trend-chart)
  (unless in-suspend-resume-p
    (let* ((trend-chart trend-chart)
	   (current-block-of-dependent-frame trend-chart))
      ;; this MUST occur before deactivating the array
      ;; because the cells hold the link from gh's to variables
      (reset-plot-histories trend-chart)
      (let ((cell-array? (cell-array trend-chart)))
	(when cell-array?
	  (deactivate-g2-cell-array cell-array?)))
      (reset-trend-chart-image-plane-states trend-chart)
      (clear-master-state trend-chart)
      (cancel-task (trend-chart-update-task? trend-chart))
      (setf (trend-chart-active-p trend-chart) nil)
      (cancel-task (trend-chart-representation-task? trend-chart))
      (clear-all-trend-chart-representation-data trend-chart)
      (send-trend-chart-activation-deactivation trend-chart nil)
      (update-trend-chart trend-chart t))))

(defun-simple clear-all-trend-chart-representation-data (trend-chart)
  (reclaim-time-slot trend-chart trend-chart-last-sent-end-time)
  (reclaim-time-slot trend-chart trend-chart-last-sent-timespan)
  (loop for value-axis being the slot-component-groups
	of (trend-chart-value-axes trend-chart)
	do
    (reclaim-value-slot value-axis value-axis-last-sent-low-value)
    (reclaim-value-slot value-axis value-axis-last-sent-high-value))
  (loop for plot being the slot-component-groups
	of (trend-chart-plots trend-chart)
	do
    (setf (plot-data-tc-representation-end-index? plot) nil)
    (setf (plot-data-tc-representation-earliest-index? plot) nil)
    (reclaim-time-slot plot plot-data-last-tc-representation-send-time?)))

(defun update-trend-chart-for-exposure (trend-chart showing-p)
  (cond (showing-p
	 (reschedule-trend-chart-update trend-chart))
	(t
	 (cancel-task (trend-chart-update-task? trend-chart))
	 (decache-and-remove-all-image-plane-states-from-trend-chart
	   trend-chart))))


(defun update-trend-charts-for-clock-discontinuity (time-delta)
  (with-temporary-gensym-float-creation update-trend-charts-for-clock-discontinuity
    (loop for trend-chart being each class-instance of 'trend-chart
	  do
      (decache-and-remove-all-image-plane-states-from-trend-chart trend-chart)
      (clear-master-state trend-chart)
      (cancel-task (trend-chart-representation-task? trend-chart))
      (when nil ; (trend-chart-active-p trend-chart)
	(cancel-task (trend-chart-update-task? trend-chart)))
      (loop for plot being each slot-component-group of
	    (trend-chart-plots trend-chart)
	    as history? = (plot-history plot)
	    when history?
	      do
		(update-generic-history-for-clock-discontinuity
		  history? time-delta)
	      (update-plot-data-send-time-for-clock-discontinuity plot time-delta))
      (update-trend-chart trend-chart nil) ; don't redo layout
      (when (trend-chart-active-p trend-chart)
	(send-trend-chart-update-for-clock-discontinuity trend-chart time-delta))
      (when nil ; (trend-chart-active-p trend-chart)
	(reschedule-trend-chart-update trend-chart)))))

(defun-void update-plot-data-send-time-for-clock-discontinuity (plot time-delta)
  (let ((send-time? (plot-data-last-tc-representation-send-time? plot)))
    (when send-time?
      (with-temporary-gensym-float-creation
	  update-plot-data-send-time-for-clock-discontinuity
	(mutate-managed-float-value
	  send-time?
	  (+e (managed-float-value send-time?)
	      (managed-float-value time-delta)))))))
	  

;; When a graph is transferred, it is not updated since it is
;; deactivated.  The check to see if graph is being dragged inhibits
;; updating while the graph is being dragged.


(define-clear-display-function trend-chart
  (unless (block-is-currently-being-dragged-p trend-chart)
   ; (draw-block-as-rectangle-in-current-window trend-chart 'red)))
    ;; draw graph without data showing with default layout
    ;; (i.e. no effects of vertical scrolling and scaling visible)
    ))






;;;; Graph Painting Bottleneck/Callback Interface

;;; See also the callbacks on paint-graph-on-scratchpad-raster
;;; This is very yucky stuff, but ...

(defun color-painting-mode (2d-rendering)
  (cond
    ((graph-rendering-uses-polychrome-rasters? 2d-rendering)
     :polychrome)
    ((graph-rendering-uses-monochrome-raster-lists? 2d-rendering)
     :monochrome-raster-list)
    (t
     :monochrome)))

(defmacro 2d-painting-mode ()
  `(cond ((or (eq current-grid-painting-color-mode :polychrome)
	      (eq current-grid-painting-color-mode :monochrome-raster-list))
	  :single-pass)
	 ((=f 0 inner-paint-loop-counter)
	  :multiple-pass-initial)
	 (t
	  :multiple-pass-subsequent)))

(defun do-grid-painting (trend-chart 2d-state mode)
  (with-named-dynamic-extent* grid-painting
      ((current-graph-rendering (2d-state-rendering 2d-state))
       (current-2d-rendering current-graph-rendering)
       (current-trend-chart trend-chart)
       (current-2d-state 2d-state)
       (current-grid-painting-is-full?
	 (eq mode :full))
       (current-grid-painting-queue nil)
       (current-grid-painting-queue-tail nil)
       (current-grid-painting-actions-to-delete nil)
       (current-grid-painting-x-scale
	 (x-scale-of-graph-rendering current-2d-rendering))
       (current-grid-painting-y-scale
	 (y-scale-of-graph-rendering current-2d-rendering))
       (current-grid-painting-background-color-value
	 (grid-background-color-value current-graph-rendering))
       (current-grid-painting-color-mode (color-painting-mode current-graph-rendering))
       (current-grid-painting-latest-time nil)
       (current-grid-painting-earliest-time nil)
       (inner-paint-loop-counter 0))

    ;; this form will initialize the rasters for the current set
    ;; of colors in the display
    (update-color-values-for-trend-chart
      trend-chart current-2d-rendering
      (data-window-background-color (trend-chart-format trend-chart)))
;      (trend-chart-color-value
;	(cdr (2d-background-colors trend-chart)) background)

    ;; Reset current-grid-painting-background-color-value to it's possibly new
    ;; value. This was added for native printing, I don't know how regular
    ;; drawing got by without it. -fmw, 6/9/03
    (setq current-grid-painting-background-color-value
	  (grid-background-color-value current-graph-rendering))

    (setup-grid-painting-time-bounds)
    (cond ((eq mode :clear)
	   (setf (line-drawing-description-for-graph-rendering?
		   current-graph-rendering)
		 '((graph) (2d-call-back-partial)))) ; hack for clearing
	  (t
	   (setf (line-drawing-description-for-graph-rendering?
		   current-graph-rendering)
		 '((graph) (2d-call-back-full)))))
    (paint-graph-rendering-raster) ; the bottleneck
    (reclaim-painting-queue)
    (delete-painting-actions-or-args current-grid-painting-actions-to-delete)
    (values current-grid-painting-earliest-time
	    current-grid-painting-latest-time)))

(defun inner-full-paint-2d-grid (monochrome-foreground-color-value)
  (setf current-grid-painting-mode (2d-painting-mode))
  (setf current-grid-painting-foreground-color-value
	monochrome-foreground-color-value)
  (paint-trend-chart-grid) ; all args through dynamic-extent
  (incff inner-paint-loop-counter))

;; hack for clearing
(defun inner-partial-paint-2d-grid (monochrome-foreground-color-value)
  (setf current-grid-painting-mode (2d-painting-mode))
  (setf current-grid-painting-foreground-color-value
	monochrome-foreground-color-value)
  (clear-trend-chart-grid) ; all args through dynamic-extent
  (incff inner-paint-loop-counter))

(defun setup-grid-painting-time-bounds ()
  (with-temporary-gensym-float-creation setup-grid-painting-time-bounds
    (setf current-grid-painting-earliest-time
	  (allocate-managed-float (most-positive-time)))
    (setf current-grid-painting-latest-time
	  (allocate-managed-float (most-negative-time)))))

(defun any-points-painted-on-grid-p (earliest-time latest-time)
  (declare (ignore earliest-time))
  (with-temporary-gensym-float-creation any-points-painted-on-grid-p
    (/=time (managed-float-value latest-time)
	   (most-negative-time))))

;;;; Drawing a trend-chart (Borders, Axes, and Labels)


(def-text-box-format 2d-value-axis-label-format
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
  text-cell-line-color? black

  minimum-format-width-for-text-cell 440
  maximum-format-width-for-text-cell 440)



(def-text-box-format 2d-time-axis-label-format
  default-word-spacing #.(convert-to-text-width 3) ; supertight
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
  text-cell-line-color? black

  minimum-format-width-for-text-cell 440
  maximum-format-width-for-text-cell 440)


;; For now ((string left top color)+)

(defmacro format-for-value-axis (value left right precision)
  `(convert-text-string-to-text
     (twith-output-to-text-string
       (write-floating-point-number
	 ,value
	 ,left
	 ,right
	 ,precision))))

(defun format-value-axis-label (value axis-pane)
  (cond ((or (eq (axis-pane-number-format axis-pane) 'fixed)
	     (eq (axis-pane-number-format axis-pane) 'percent)
	     (not (show-label-using-scientific-p value axis-pane)))
	 (let* ((left-digits (axis-pane-fixed-left-digits axis-pane))
		(right-digits (axis-pane-fixed-right-digits axis-pane))
		(decimal-pos (axis-pane-fixed-decimal-offset axis-pane))
		(label (twith-output-to-text-string
			 (write-floating-point-number 
			   value left-digits right-digits
			   (+f left-digits right-digits))
			 (when (eq (axis-pane-number-format axis-pane)
				   'percent)
			   (tformat "%"))))
		(label-decimal-pos
		  (or (find-position-of-decimal-in-value-label label)
		      (get-width-of-value-label label))))
	   (values (convert-text-string-to-text label)
		   (-w decimal-pos label-decimal-pos))))
	(t
	 (let* ((left-digits (axis-pane-fixed-left-digits axis-pane))
		(right-digits (axis-pane-fixed-right-digits axis-pane))
		(decimal-pos (axis-pane-floating-decimal-offset axis-pane))
		(label (twith-output-to-text-string
			 (write-floating-point-number
			   value left-digits right-digits
			   (+f left-digits right-digits) nil t)))
		(label-decimal-pos
		  (or (find-position-of-decimal-in-value-label label)
		      (get-width-of-value-label label))))
	   (values (convert-text-string-to-text label)
		   (-w decimal-pos label-decimal-pos))))))

(defvar current-axis-pane)

;; ELEMENT text managed-float left-offset top-offset boolean

(defun add-element-to-axis-description (elt)
  (slot-value-push
    elt
    (axis-pane-textual-elements current-axis-pane)))

(defun start-recording-description-for-axis-pane (axis-pane interval text-color)
  (setf current-axis-pane axis-pane)
  (setf (axis-pane-interval axis-pane) interval)
  (setf (axis-pane-text-color axis-pane) text-color))

(defun clear-transients-of-axis-pane (axis-pane)
  (when (axis-pane-interval axis-pane)
    (reclaim-managed-float (axis-pane-interval axis-pane))
    (setf (axis-pane-interval axis-pane) nil))
  (loop with textual-elements = (axis-pane-textual-elements axis-pane)
	for textual-element in textual-elements
	do
          (reclaim-text (car textual-element))
	  (setf (car textual-element) nil)
	  (reclaim-slot-value textual-element)
	finally
	  (reclaim-slot-value-list textual-elements)
	  (setf (axis-pane-textual-elements axis-pane) nil)))

(defun clear-transients-of-all-axis-panes (trend-chart)
  (loop for sub-pane in (display-pane-sub-panes
			  (trend-chart-pane-tree trend-chart))
	when (eq (display-pane-type sub-pane) 'axis-pane)
	  do
	    (clear-transients-of-axis-pane sub-pane)))

(defun get-axis-pane (trend-chart axis)
  (loop for sub-pane in (display-pane-sub-panes
			  (trend-chart-pane-tree trend-chart))
	when (eq (display-pane-component-group? sub-pane)
		 axis)
	  return sub-pane))

(defparameter trend-chart-value-axis-frame-notes
  '(thinning-value-grid-lines))

(def-frame-note-writer thinning-value-grid-lines (ignore-me)
  (declare (ignore ignore-me))
  (twrite-string "too many value grid lines requested - fewer will be shown"))

(defun remove-trend-chart-value-axis-frame-notes (trend-chart)
  (loop for note-type in trend-chart-value-axis-frame-notes
	do
    (delete-all-frame-notes-of-type-from-trend-chart
      trend-chart note-type t)))

;;; NOTE: bind current-trend-chart-has-remote-representation-p
;;; if using the following function outside of update-trend-chart

(defun update-trend-chart-axes (trend-chart)
  (clear-transients-of-all-axis-panes trend-chart)
  (remove-trend-chart-value-axis-frame-notes trend-chart)
  (loop for axis being the slot-component-groups
	of (trend-chart-value-axes trend-chart)
	as axis-pane? =
	(loop for sub-pane in (display-pane-sub-panes
				(trend-chart-pane-tree trend-chart))
	      when (and (eq (display-pane-type sub-pane)
			    'axis-pane)
			(eq (display-pane-component-group? sub-pane)
			    axis))
		do
		  (return sub-pane))
	do
    (unless (value-axis-low-value axis)
      (setf (value-axis-low-value axis)
	    (make-2d-display-value))
      (setf (value-axis-high-value axis)
	    (make-2d-display-value)))
    (case (verified-value-axis-range-mode axis)
      (fixed
       (compute-fixed-value-axis-description
	 trend-chart axis axis-pane?))
      ((automatic high-water-marking)
       (compute-automatic-value-axis-description
	 trend-chart axis axis-pane?))
      (old-high-water-marking
       (cerror "" "NYI")))
	finally
	  (mutate-time-slot trend-chart trend-chart-axis-update-time
			    (managed-float-value (clock-get current-g2-time)))))


(defun compute-fixed-value-axis-description
    (trend-chart value-axis axis-pane?)
  (with-temporary-gensym-float-creation compute-graph-value-axis
    (cond
      ((value-axis-lower-bound? value-axis)
       (let ((low-bound (fast-value-slot value-axis value-axis-lower-bound?))
	     (high-bound (fast-value-slot value-axis value-axis-upper-bound?)))
	 (fast-mutate-value-slot
	   value-axis value-axis-low-value
	   low-bound)
	 (fast-mutate-value-slot
	   value-axis value-axis-high-value
	   high-bound)
	 (compute-vertical-axis-description-from-bounds
	   trend-chart value-axis axis-pane? low-bound high-bound nil)))
      (t
       (cerror "" "Consistency checking needed in slot putter"))))) ; !!

(defun compute-automatic-value-axis-description
    (trend-chart axis axis-pane?)
  (with-temporary-gensym-float-creation graph-value-axis
    (loop with plot-minima = (trend-chart-plot-minima trend-chart)
	  with plot-maxima = (trend-chart-plot-maxima trend-chart)
          with running-maximum = (uninitialized-negative-value-flag)
	  with running-minimum = (uninitialized-positive-value-flag)
          for plot being the slot-component-groups
	      of (trend-chart-plots trend-chart)
	   as plot-index = (plot-index plot)
	   as referred-axis = (get-slot-component-group-by-reference
				trend-chart plot 'plot-axis)
	  when (and (plot-is-runnable-p plot) ; plot-has-data-p ???
		    (eq axis referred-axis))
	       ;; (trend-chart-component-name axis)))
	    do
	      (let ((plot-maximum
		     (managed-float-aref plot-maxima plot-index))
		    (plot-minimum
		     (managed-float-aref plot-minima plot-index)))
		(when (/= plot-minimum (uninitialized-negative-value-flag))
		  (setf running-minimum
		    (minvalue running-minimum plot-minimum)))
		(when (/= plot-maximum (uninitialized-positive-value-flag))
		  (setf running-maximum
		    (maxvalue running-maximum plot-maximum)))
		)
	  finally
	    (when (=value running-maximum (uninitialized-negative-value-flag))
	      (setf running-maximum (uninitialized-positive-value-flag)))
	    (when (=value running-minimum (uninitialized-positive-value-flag))
	      (setf running-minimum (uninitialized-negative-value-flag)))
	    (fast-mutate-value-slot
	      axis value-axis-low-value
	      running-minimum)
	    (fast-mutate-value-slot
	      axis value-axis-high-value
	      running-maximum)
	    (compute-vertical-axis-description-from-bounds
	      trend-chart axis axis-pane?
	      running-minimum running-maximum
	      (and (=value running-maximum (uninitialized-positive-value-flag))
		   (=value running-minimum (uninitialized-negative-value-flag)))))))

(defmacro normalize-width-or-origin (value)
  (avoiding-variable-capture (value)
    `(cond ((managed-float-p ,value)
	    (managed-float-value ,value))
	   ((fixnump ,value)
	    (coerce-fixnum-to-gensym-float ,value))
	   (t
	    ,value))))
	  

(defun compute-vertical-axis-description-from-bounds
    (trend-chart axis axis-pane? lower-bound upper-bound
		bounds-have-not-been-set-p)
  (let  ((axis-tickmark-frequency (value-axis-tickmark-frequency
				    axis)))
    (cond
      ((and bounds-have-not-been-set-p
	    (not (value-axis-lower-bound? axis)))
       (fast-mutate-value-slot
	 axis value-axis-low-value -1.1)
       (fast-mutate-value-slot
	 axis value-axis-high-value 1.1)
       (when axis-pane?
	 (compute-value-tickmarks-by-interval-and-origin
	   trend-chart axis axis-pane? -1.1 1.1
	   1.0 0.0)))
      ((and axis-pane? (=value upper-bound lower-bound))
       (compute-n-value-tickmarks
	 trend-chart axis axis-pane? lower-bound upper-bound 1))
      (axis-pane?
       (when bounds-have-not-been-set-p
	 (setq lower-bound (fast-value-slot axis value-axis-lower-bound?))
	 (setq upper-bound (fast-value-slot axis value-axis-upper-bound?)))
       (case (frame-like-value-key axis-tickmark-frequency)
	 ((none automatic)
	  (cond
	    (axis-pane?
	     (multiple-value-bind (interval origin)
		 (compute-interval-and-origin-for-automatic-labels
		   lower-bound upper-bound
		   (axis-pane-maximum-tickmarks axis-pane?)
		   (axis-pane-number-format axis-pane?))
	       (compute-value-tickmarks-by-interval-and-origin
		 trend-chart axis axis-pane? lower-bound upper-bound
		 interval origin)))
	    (t
	     (compute-n-value-tickmarks
	       trend-chart axis axis-pane? lower-bound upper-bound 5))))
	 (fraction
	  (compute-n-value-tickmarks
	    trend-chart axis axis-pane? lower-bound upper-bound
	    (frame-like-value-property axis-tickmark-frequency 'count)))
	 (interval
	  (compute-value-tickmarks-by-interval-and-origin
	    trend-chart axis axis-pane? lower-bound upper-bound
	    (normalize-width-or-origin
	      (frame-like-value-property axis-tickmark-frequency 'width))
	    (normalize-width-or-origin
	      (frame-like-value-property axis-tickmark-frequency 'origin)))))))))

(defun least-significant-decimal-digit (number)
  (declare (double-float number))
  (setf number (abs number))
  (cond
    ((= number)
     0d0)
    (t
     (loop for power = (- (ceiling (log number 10d0)))
		     then (+ power 1)
	   as factor = (expt 10d0 power)
	   as shifted-number = (* factor number)
	   do
       (multiple-value-bind (quotient remainder)
	   (floor shifted-number 1d0)
	 (declare (ignore quotient))
	 (when (or (< (abs (- 1d0 remainder)) 0d000001)
		   (< (abs remainder) 0d000001))
	   (return (- power))))))))

;;; can return nil for interval: this is interpreted as using the whole
;;; range for the interval

(defun compute-interval-and-origin-for-automatic-labels (lower-bound upper-bound
							max-labels axis-number-format)
  (cond
    ((or (=value upper-bound lower-bound)
	 (=f max-labels 0))
     (return-from compute-interval-and-origin-for-automatic-labels
       (values 1.0 upper-bound)))
    ((eq axis-number-format 'fixed)
     (compute-interval-and-origin-for-fixed-automatic-labels
       lower-bound upper-bound max-labels))
    ((eq axis-number-format 'percent)
     (compute-interval-and-origin-for-percentage-labels
       lower-bound upper-bound max-labels))
    (t
     (compute-interval-and-origin-for-moving-automatic-labels
       lower-bound upper-bound max-labels))))

(defun compute-interval-and-origin-for-percentage-labels
    (lower-bound upper-bound max-labels)
  (let ((divisor (cond ((>f max-labels 120) 100)
		       ((>f max-labels 60) 50)
		       ((>f max-labels 30) 25)
		       ((>f max-labels 12) 10)
		       ((>f max-labels 6)   5)
		       ((>f max-labels 2)   2)
		       (t                   1))))
    (values (/value (-value upper-bound lower-bound)
		    (fixnum-to-value divisor))
	    lower-bound)))

;;; can return nil for interval when max-labels = 1: this is interpreted as using the whole
;;; range for the interval

(defun compute-interval-and-origin-for-fixed-automatic-labels
    (lower-bound upper-bound max-labels)
  (let* ((lsdd-for-upper (least-significant-decimal-digit upper-bound))
	 (lsdd-for-lower (least-significant-decimal-digit lower-bound))
	 (shift-factor (expt-value 10.0 (-value
					  (minvalue lsdd-for-lower lsdd-for-upper))))
	 (integer-range
	  (value-to-fixnum (-value (*value shift-factor upper-bound)
				   (*value shift-factor lower-bound)))))
    (loop for divisor from (1-f max-labels) downto 1 by 1
	  when (=f 0 (modf integer-range divisor))
	    return (values (/value (-value upper-bound lower-bound)
				   (fixnum-to-value divisor))
			   lower-bound))))
    
(defun compute-interval-and-origin-for-moving-automatic-labels
    (lower-bound upper-bound max-labels)
  (let* ((range (-value upper-bound lower-bound))
	 (place-value
	   (let ((first-guess (expt-value 10.0
					  (floor-value
					    (log-value range (fixnum-to-value 10))))))
	     (cond ((<value (/value range first-guess) 5.0)
		    (/value first-guess 10.0))
		   (t
		    first-guess))))
	 (rounded-upper-bound
	   (*value place-value (floor-value upper-bound place-value)))
	 (rounded-lower-bound
	   (*value place-value (ceiling-value lower-bound place-value)))
	 (desired-labels (maxf (floorf max-labels 2) 1)))
    (loop for i = 0
		then (modf (+f i 1) 3)
	  as interval = place-value
		      then (*value interval
				   (if (=f i 1)
				       2.5
				       2.0))
	  when (<=f (value-to-fixnum
		      (/value (-value rounded-upper-bound rounded-lower-bound)
			      interval))
		    desired-labels)
	    return
	    (let ((down-rounded-lower-bound
		    (*value interval (floor-value rounded-lower-bound
						  interval))))
	      (cond ((>=value down-rounded-lower-bound lower-bound)
		     (values interval down-rounded-lower-bound))
		    (t
		     (values interval
			     (*value interval
				     (ceiling-value
				       rounded-lower-bound interval)))))))))
			 

(defun get-color-for-axis-tickmarks (trend-chart axis)
  (let ((color-spec
	  (color-for-value-axis-tickmarks axis)))
    (case (frame-like-value-key color-spec)
      (absolute
       (frame-like-value-property color-spec 'color))
      (matching
       (or
	 (loop for plot being the slot-component-groups
	       of (trend-chart-plots trend-chart)
	       as connector-format?
	          = (get-slot-component-group-by-reference
		      trend-chart plot 'plot-connector-format)
	       when (and
		      (plot-is-runnable-p plot)
		      connector-format?
		      (eq axis
			  (get-slot-component-group-by-reference
			    trend-chart plot 'plot-axis)))
		 return (connector-line-color connector-format?))
	 ;; arbitrary-default
	 'black))))) 

(defun value-or-percent (tickmark-value axis-pane lower-bound upper-bound)
  (cond ((eq (axis-pane-number-format axis-pane) 'percent)
	 (/value (*value (-value tickmark-value lower-bound) 100.0)
		 (-value upper-bound lower-bound)))
	(t
	 tickmark-value)))


(defmacro fixnum-ratio-as-value (numerator denominator)
  `(/value (coerce-fixnum-to-gensym-float ,numerator)
	   (coerce-fixnum-to-gensym-float ,denominator)))

(defun compute-n-value-tickmarks
    (trend-chart axis axis-pane lower-bound upper-bound desired-count)
  (loop with count = (minf desired-count
			   (axis-pane-maximum-tickmarks axis-pane))
        with range = (-value upper-bound lower-bound)
	with axis-labels-visible-p =
	     (not (eq (axis-pane-number-format axis-pane) 'invisible))
	with axis-height = (display-pane-height axis-pane)
	with half-tickmark-height = (halfw (axis-pane-label-height axis-pane))
	with tickmark-color = (get-color-for-axis-tickmarks trend-chart axis)
        for i from 0 to count
	 as tickmark-value
	    = (+value lower-bound
		      (*value (fixnum-ratio-as-value i count) range))
	 as tickmark-top-offset
	    = (-w axis-height
		  (+w half-tickmark-height
		      (floorw (*w axis-height i) count)))
	initially
	  (start-recording-description-for-axis-pane
	    axis-pane
	    (allocate-managed-float
	      (*value (fixnum-ratio-as-value 1 count) range))
	    tickmark-color)
	do
    (multiple-value-bind (text label-left-offset)
	(format-value-axis-label
	  (value-or-percent tickmark-value axis-pane lower-bound upper-bound)
	  axis-pane)
      (add-element-to-axis-description
	(let ((res
		(slot-value-list
		  text
		  (allocate-managed-float tickmark-value)
		  label-left-offset
		  tickmark-top-offset
		  axis-labels-visible-p)))
	  res)))))

(defun compute-reasonable-value-axis-interval (trend-chart axis
						  interval range axis-max-labels)
  ;; assumes all args positive
  (cond
    ((or (=f axis-max-labels 0)
	 (=value interval 0.0))
     range)
    (t
     (*value interval
	     (let ((unrounded-multiple
		     (floor-value range
				  (*value (coerce-fixnum-to-gensym-float
					    axis-max-labels)
					  interval))))
	       (cond ((<value unrounded-multiple 1.0)
		      1.0)
		     (t
		      (add-or-delete-trend-chart-note
			trend-chart axis 'thinning-value-grid-lines t)
		      (*value 5.0 (ceiling-value unrounded-multiple 5.0)))))))))
    
(defun compute-value-tickmarks-by-interval-and-origin
    (trend-chart axis axis-pane lower-bound upper-bound
		interval-width origin)
  (unless origin
    (setf origin 0.0))
  (unless interval-width
    (setf interval-width 0.0))
  (let* ((range (-value upper-bound lower-bound))
;;	 (interval (minvalue interval-width range))
	 (tmp-interval (compute-reasonable-value-axis-interval
	     trend-chart axis
	     (minvalue interval-width range)
	     range
	     (axis-pane-maximum-tickmarks axis-pane))) 
	 (interval (if (<value tmp-interval 0.0000001d0) ; if interval < 0.0000001 then 
		       0.0000001d0 ; interval = 0.0000001
		     tmp-interval))
	 (label-height (axis-pane-label-height axis-pane))
	 (half-label-height (halfw label-height))
	 (axis-height (display-pane-height axis-pane))
	 (tickmark-color (get-color-for-axis-tickmarks trend-chart axis))
	 (w-units-per-interval
	   (value-to-fixnum
	     (ceiling-value (*value (fixnum-to-value axis-height)
				    (/value interval range)))))
	 (ratio-of-tickmarks-to-labels
	   (maxf 1 (floorf label-height w-units-per-interval))))
    (loop with lowest-multiple-of-interval
	       = (let  ((lowest-mult
			 (value-to-fixnum
			   (ceiling-value (/value (-value lower-bound origin)
						  interval)))))
		   lowest-mult)
	  with axis-labels-visible-p
	    = (not (eq (axis-pane-number-format axis-pane) 'invisible))
	  for index from lowest-multiple-of-interval by 1
	  as tickmark-value = (+value
				(*value interval (fixnum-to-value index))
				origin)
	   as tickmark-top-offset
	      = (-w axis-height
		    (+w half-label-height
			(value-to-fixnum
			  (ceiling-value (*value
					   (fixnum-to-value axis-height)
					   (/value (-value tickmark-value lower-bound)
						   range))))))
	  initially
	    (start-recording-description-for-axis-pane
	      axis-pane
	      (allocate-managed-float interval)
	      tickmark-color)
	  while (<=value tickmark-value upper-bound)
	    do
      (multiple-value-bind (text label-left-offset)
	  (format-value-axis-label
	    (value-or-percent tickmark-value axis-pane lower-bound upper-bound)
	    axis-pane)
	(add-element-to-axis-description
	  (slot-value-list
	    text
	    (allocate-managed-float tickmark-value)
	    label-left-offset
	    tickmark-top-offset
	    (and axis-labels-visible-p
		 (=f 0 (modf index ratio-of-tickmarks-to-labels)))))))))


(defun draw-or-erase-all-value-axes (trend-chart erase-p updating-p)
  (loop for sub-pane in (display-pane-sub-panes
			  (trend-chart-pane-tree trend-chart))
	when (eq (display-pane-type sub-pane) 'axis-pane)
	  do
	    (draw-or-erase-value-axis trend-chart sub-pane erase-p updating-p)))

(defun draw-or-erase-value-axis (trend-chart axis-pane erase-p updating-p)
  (let* ((current-text-box-format
	   (get-or-make-format-frame '2d-value-axis-label-format))
	 (background-color-value
	   (trend-chart-color-value
	     (outer-background-color (trend-chart-format trend-chart))
	     background))
	 (erase-instead? erase-p)
	 (color (axis-pane-text-color axis-pane))
	 (logical-color-value 
	   (trend-chart-color-value color foreground))
	 (base-line-left-offset?
	   (axis-pane-base-line-left-offset? axis-pane))
	 (clipping-width
	   (if base-line-left-offset?
	       (1+w (display-pane-width axis-pane))
	       (display-pane-width axis-pane)))
	 (current-foreground-color-value logical-color-value))
    (with-background-color-value background-color-value
      (with-focused-display-pane (trend-chart axis-pane)
	(when (and base-line-left-offset? (not updating-p))
	  (let ((left-in-window
		  (x-in-window (+w base-line-left-offset?
				   current-display-pane-left)))
		(top-in-window
		  (y-in-window current-display-pane-top))
		(bottom-in-window
		  (y-in-window current-display-pane-bottom)))
	    (paint-solid-rectangle
	      left-in-window
	      top-in-window
	      (1+r left-in-window)
	      bottom-in-window
	      (trend-chart-color-value
		(axis-pane-base-line-color axis-pane)
		foreground))))
	(loop for (text value left-offset top-offset has-text-p)
		  in (axis-pane-textual-elements axis-pane)
	      do
	  (when has-text-p
	    (let ((left (+w current-display-pane-left left-offset))
		  (top (+w current-display-pane-top top-offset)))
	      (new-draw-text text
			     (x-in-window left)
			     (y-in-window top)
			     (x-in-window
			       (+w left clipping-width))
			     (y-in-window
			       (+w top
				   (axis-pane-clip-height axis-pane)))))))))))
  
(defvar reclaimed-things)

#+development
(def-system-variable all-trend-charts GRAPHS nil)

#+development
(defun 2d-integrity-check ()
  (loop for trend-chart in all-trend-charts
	do
    (check-one-trend-chart trend-chart)))

(defun check-current-trend-chart ()
  (when (and (boundp 'current-block-of-dependent-frame)
	     (of-class-p current-block-of-dependent-frame 'trend-chart))
    (check-one-trend-chart current-block-of-dependent-frame)))

(defvar most-recent-trend-chart-checked)

(defun check-one-trend-chart (trend-chart)
  (setf most-recent-trend-chart-checked trend-chart)
  (loop for plot being the slot-component-groups of (trend-chart-plots trend-chart)
	do
    (check-one-plot trend-chart plot)
	finally
	  #+development
	  (when (> trace-trend-chart-values 0)
	    (format t "~s is OK~%" most-recent-trend-chart-checked))))

(defun check-one-plot (trend-chart plot)
  (let ((connector-format
	  (get-slot-component-group-by-reference trend-chart plot 'plot-connector-format)))
    (cond ((and connector-format
		(not (symbolp (connector-line-color connector-format))))
	   (break))
	  (t nil))))

(defun draw-or-erase-relative-time-labels (trend-chart erase?)
  (let ((relative-time-pane?
	  (loop for  sub-pane in (display-pane-sub-panes
				   (trend-chart-pane-tree trend-chart))
		when (eq (display-pane-type sub-pane) 'relative-time-pane)
		  return sub-pane))
	(background-color-value
	  (trend-chart-color-value
		(outer-background-color (trend-chart-format trend-chart))
		background)))
    (when relative-time-pane?
      (with-background-color-value background-color-value
	(with-focused-display-pane (trend-chart relative-time-pane?)
	  (loop with current-text-box-format
		= (get-or-make-format-frame '2d-value-axis-label-format)
		with text-color-value =
		(trend-chart-color-value
		  (relative-time-label-color relative-time-pane?)
		  foreground)
		with erase-instead? = erase?
		for (text left-offset) in (relative-time-labels relative-time-pane?)
		do
	    (let ((current-foreground-color-value text-color-value)
		  (left (+w current-display-pane-left left-offset)))
	      (new-draw-text text
			     (x-in-window left)
			     (y-in-window current-display-pane-top)
			     (x-in-window current-display-pane-right)
			     (y-in-window current-display-pane-bottom)))))))))

(defun draw-or-erase-trend-chart-legends (trend-chart erase?)
  (loop for sub-pane in (display-pane-sub-panes
			  (trend-chart-pane-tree trend-chart))
	when (eq (display-pane-type sub-pane) 'legend-pane)
	  do
	    (draw-or-erase-trend-chart-legend trend-chart sub-pane erase?)))

(defun draw-or-erase-trend-chart-legend (trend-chart legend-pane erase?)
  (let* ((current-text-box-format
	   (get-or-make-format-frame '2d-value-axis-label-format))
	 (background-color-value
	   (trend-chart-color-value
	     (outer-background-color (trend-chart-format trend-chart))
	     background))
	 (erase-instead? erase?)
	 (line-height (text-cell-line-height current-text-box-format))
	 (line-spacing (legend-pane-interline-spacing legend-pane)))
    (with-background-color-value background-color-value
      (with-focused-display-pane (trend-chart legend-pane)
	(loop for (text left-offset color) in (legend-pane-lines legend-pane)
	      as line-top = current-display-pane-top
			  then (+w line-top line-height line-spacing)
	      as logical-color-value
	      = (trend-chart-color-value color foreground)
	      do
	  (let ((current-foreground-color-value logical-color-value)
		(left (+w current-display-pane-left left-offset)))
	    (new-draw-text text
			   (x-in-window left)
			   (y-in-window line-top)
			   (x-in-window current-display-pane-right)
			   (y-in-window (+w line-top line-height)))))))))


;;;; Drawing a Trend-Chart (layout and resizing)


;; workspace coordinates
(defvar trend-chart-layout-top)
(defvar trend-chart-layout-bottom)
(defvar trend-chart-layout-right)
(defvar trend-chart-layout-left)
(defvar trend-chart-layout-parent)
(defvar trend-chart-layout-grid)
(defvar trend-chart-layout-relative-time-pane)

(defparameter graph-minimum-line-spacing 2)
(defparameter graph-minimum-text-spacing 4)

(defparameter trend-chart-layout-frame-notes
  '(too-many-value-axes))

(def-frame-note-writer too-many-value-axes (ignore-me)
  (declare (ignore ignore-me))
  (twrite-string "too many visible value axes specified for width of trend chart"))

(defun remove-trend-chart-layout-frame-notes (trend-chart)
  (loop for note-type in trend-chart-layout-frame-notes
	do
    (delete-all-frame-notes-of-type-from-trend-chart
      trend-chart note-type nil)))

(defmacro show-layout-progress (stage)
  #+development
  `(when nil
     (format t "at ~s remaining-bounds are (~s ~s ~s ~s) W=~S H=~s~%"
	     ,stage
	     trend-chart-layout-left
	     trend-chart-layout-top
	     trend-chart-layout-right
	     trend-chart-layout-bottom
	     (-w trend-chart-layout-right trend-chart-layout-left)
	     (-w trend-chart-layout-bottom trend-chart-layout-top)))
  #-development
  (declare (ignore stage))
  #-development
  nil)
	  

(defun clear-trend-chart-layout (trend-chart)
  (let ((pane-tree? (trend-chart-pane-tree trend-chart)))
    (when pane-tree?
      (reclaim-pane-tree pane-tree?)
      (setf (trend-chart-pane-tree trend-chart) nil))))

(defun update-trend-chart-layout (trend-chart)
  (clear-trend-chart-layout trend-chart)
  (remove-trend-chart-layout-frame-notes trend-chart)
  (let* ((trend-chart-layout-left (left-edge-of-block trend-chart))
	 (trend-chart-layout-top (top-edge-of-block trend-chart))
	 (trend-chart-layout-right (right-edge-of-block trend-chart))
	 (trend-chart-layout-bottom (bottom-edge-of-block trend-chart))
	 (trend-chart-layout-relative-time-pane nil))
    (show-layout-progress "start")
    (layout-trend-chart-root trend-chart)
    (show-layout-progress "root done")
    (layout-trend-chart-label trend-chart)
    (show-layout-progress "label done")
    (layout-trend-chart-legend trend-chart)
    (show-layout-progress "leged done")
    (layout-value-axes-in-x trend-chart)
    (show-layout-progress "axes-in-x done")
    (layout-time-scale-in-y trend-chart)
    (layout-graph-grid trend-chart)
    (layout-time-axis trend-chart)
    (layout-grid-data-height trend-chart)
    (layout-value-axes-in-y trend-chart))
  )

(defun layout-trend-chart-root (trend-chart)
  (let ((trend-chart-format (trend-chart-format trend-chart))
	(root-pane
	  (new-display-pane trend-chart-pane nil
			    0
			    0
			    (-w trend-chart-layout-right
				trend-chart-layout-left)
			    (-w trend-chart-layout-bottom
				trend-chart-layout-top))))
    (setf (display-pane-background-color root-pane)
	  (outer-background-color trend-chart-format))
    (setf (display-pane-border-color root-pane)
	  (outer-border-color trend-chart-format))
    (cond
      ((outer-border-visible? trend-chart-format)
       (setf (display-pane-border-style? root-pane) 1)
       (incfw trend-chart-layout-left)
       (incfw trend-chart-layout-top)
       (decfw trend-chart-layout-right)
       (decfw trend-chart-layout-bottom))
      (t
       (setf (display-pane-border-style? root-pane) nil)))
    (setf trend-chart-layout-parent root-pane)
    (setf (trend-chart-pane-tree trend-chart) root-pane)
    ))


(defun layout-trend-chart-label (trend-chart)
  (let* ((trend-chart-format (trend-chart-format trend-chart))
	 (label-position (trend-chart-label-position
			   trend-chart-format))
	 (label-text? (cdr (trend-chart-label-to-display trend-chart))))
    (when (and label-text?
	       (not (text-blank-p label-text?))
	       (trend-chart-label-visible? trend-chart-format))
      (multiple-value-bind (lines line-spacing line-height width)
	  (calculate-trend-chart-label label-text?
				       (trend-chart-label-color
					 trend-chart-format))
	(let* ((line-count (length lines))
	       (height (+f (*f line-count line-height)
			   (*f line-count line-spacing)))
	       (remaining-height
		 (-w trend-chart-layout-bottom trend-chart-layout-top))
	       legend-top-offset)
	  ;; limit lable/title size here
	  (when (>w height
		    (-w remaining-height
			(+w minimum-data-window-size
			    minimum-data-window-margin
			    (*w (+w line-spacing line-height)
				(estimate-number-of-lines-in-legend trend-chart)))))
	    ;; reclaim lines and replace with apology
	    (reclaim-slot-value lines)
	    (setf lines
		  (slot-value-list
		    (make-legend-line
		      (
		       copy-constant-wide-string #w"<title too long to display>"
		       )
		      (get-or-make-format-frame
			'2d-value-axis-label-format)
		      (-w (display-pane-width trend-chart-layout-parent)
			  2)
		      0
		      (trend-chart-label-color trend-chart-format))))
	    ;; set line-count and height appropriately
	    (setf height (+w line-height line-spacing))
	    )
	  (setq
	    legend-top-offset
	    (cond ((eq label-position 'above)
		   (incfw trend-chart-layout-top height)
		   line-spacing)
		  (t
		   (decfw trend-chart-layout-bottom height)
		   (-w trend-chart-layout-bottom
		       trend-chart-layout-top)
		   )))
	  (let ((legend-pane
		 (new-display-pane legend-pane
				   trend-chart-layout-parent
				   0 legend-top-offset width height)))
	    (setf (legend-pane-lines legend-pane) lines)
	    (setf (legend-pane-interline-spacing legend-pane)
		  line-spacing)))))))

;;  make-legend-line (string text-box-format width
;; 				minimum-indent color)

(defun calculate-trend-chart-label (text-or-text-string label-color)
  (let (delete-text-p text)
    (cond ((text-string-p text-or-text-string)
	   (setf text
		 (convert-text-string-to-text
		   (copy-text-string text-or-text-string)))
	   (setf delete-text-p t))
	  (t
	   (setf text text-or-text-string)
	   (setf delete-text-p nil)))
    (loop with lines = '()
	  with text-box-format
	       = (get-or-make-format-frame
		   '2d-value-axis-label-format)
	  with width
	       = (-w (display-pane-width trend-chart-layout-parent)
		     2)
	  with text-tail = text
	  with next-line = nil
	  with line-length = nil
	  with lost-space = nil
	  with indentation = nil
	  with line-width = nil
	  while text-tail
	  do
      (multiple-value-setq
	  (next-line line-length lost-space text-tail
		     indentation line-width)
	(get-next-text-line text-tail))
      (slot-value-push
	(make-legend-line
	  (eliminate-newlines next-line nil nil) ; can eliminate newlines's here
	  text-box-format
	  width
	  (or indentation 0)
	  label-color)
	lines)
	  finally
	    (setq lines (nreverse lines))
	    (when delete-text-p
	      (reclaim-text text))
	    (return
	      (values lines
		      (text-cell-line-spacing text-box-format)
		      (text-cell-line-height text-box-format)
		      width)))))
	    
  
(defun layout-trend-chart-legend (trend-chart)
  (let* ((trend-chart-format (trend-chart-format trend-chart))
	 (legend-color-spec (trend-chart-legend-color trend-chart-format))
	 (legend-position (trend-chart-legend-position
			    trend-chart-format)))
    (when (trend-chart-legend-visible? trend-chart-format)
      (multiple-value-bind (lines line-spacing line-height width)
	  (calculate-trend-chart-legend
	    trend-chart
	    (case (frame-like-value-key legend-color-spec)
	      (matching 'matching)
	      (absolute
	       (frame-like-value-property legend-color-spec 'color))))
	(with-focused-display-pane (trend-chart trend-chart-layout-parent)
	  (let* ((current-top-offset
		  (-w trend-chart-layout-top
		      current-display-pane-top))
		 (line-count (length lines))
		 (height (+f (*f line-count line-height)
			     (*f line-count line-spacing)))
		 (remaining-height
		   (-w trend-chart-layout-bottom trend-chart-layout-top))
		 (available-height-for-legend
		   (-w remaining-height
			  (+w minimum-data-window-size
			      minimum-data-window-margin)))
		 legend-top-offset)
	    ;; limit legend size here
	    (when (>w height available-height-for-legend)
	      ;; reclaim lines and replace with apology
	      (reclaim-slot-value lines)
	      (cond ((<=w (+w line-height line-spacing) available-height-for-legend)
		     ;; put message in if there is room
		     (setf lines
			   (slot-value-list
			     (make-legend-line
			       (
			        copy-constant-wide-string #w"<legend too long to display>"
			        )
			       (get-or-make-format-frame
				 '2d-value-axis-label-format)
			       (-w (display-pane-width trend-chart-layout-parent)
				   2)
			       0
			       (trend-chart-label-color trend-chart-format))))
		     (setf height (+w line-height line-spacing)))
		    (t
		     (setq lines nil))))
	    (when lines
	      (setq legend-top-offset
		    (cond ((eq legend-position 'above)
			   (incfw trend-chart-layout-top height)
			   line-spacing)
			  (t
			   (decfw trend-chart-layout-bottom height)
			   (-w trend-chart-layout-bottom
			       trend-chart-layout-top)
			   )))
	      (let ((legend-pane
		      (new-display-pane legend-pane
					trend-chart-layout-parent
					0
					(+w current-top-offset
					    legend-top-offset)
					width
					height)))
		(setf (legend-pane-lines legend-pane) lines)
		(setf (legend-pane-interline-spacing legend-pane)
		      line-spacing)))))))))

(defun estimate-number-of-lines-in-legend (trend-chart)
  ;; write-legend-line for block name if exists
  (let* ((trend-chart-format (trend-chart-format trend-chart))
	 (legend-color-spec (trend-chart-legend-color trend-chart-format)))
    (cond
      ((trend-chart-legend-visible? trend-chart-format)
       (loop with legend-color = 
	     (case (frame-like-value-key legend-color-spec)
	       (matching 'matching)
	       (absolute
		(frame-like-value-property legend-color-spec 'color)))
	     with line-count = 0
	     for plot being the slot-component-groups
	     of (trend-chart-plots trend-chart)
	     as name? = (trend-chart-component-name plot)
	     as expression? = (plot-expression plot)
	     as connector-format = (get-slot-component-group-by-reference
				     trend-chart plot 'plot-connector-format)
	     as point-format = (get-slot-component-group-by-reference
				 trend-chart plot 'plot-point-format)
	     as plot-color? = (cond
				((connector-visible? connector-format)
				 (connector-line-color connector-format))
				((point-visible? point-format)
				 (point-color point-format)))
	     as color? = (cond ((not (eq legend-color 'matching))
				legend-color)
			       (t
				plot-color?))
	     do
	 (when (and expression? color?
		    (include-in-legend? plot))
	   (incff line-count
		  (if (point-visible? point-format)
		      2
		      1)))
	     finally
	       (return line-count)))
      (t
       0))))

(defun calculate-trend-chart-legend (trend-chart legend-color)
  ;; write-legend-line for block name if exists
  (loop with lines = '()
	with text-box-format = (get-or-make-format-frame
				 '2d-value-axis-label-format)
	with legend-width
	     = (-w trend-chart-layout-right trend-chart-layout-left)
        for plot being the slot-component-groups
	    of (trend-chart-plots trend-chart)
	as name? = (trend-chart-component-name plot)
	as expression? = (plot-expression plot)
	as connector-format = (get-slot-component-group-by-reference
				trend-chart plot 'plot-connector-format)
	as point-format = (get-slot-component-group-by-reference
			    trend-chart plot 'plot-point-format)
	as plot-color? = (cond
			   ((connector-visible? connector-format)
			    (connector-line-color connector-format))
			   ((point-visible? point-format)
			    (point-color point-format)))
	as color? = (cond ((not (eq legend-color 'matching))
			   legend-color)
			  (t
			   plot-color?))
	do
    (when (and expression? color?
	       (include-in-legend? plot))
      (let* ((name-string
	       (cond ((and name? (not (eq name? 'default)))
		      (twith-output-to-text-string
			(tformat "~a" name?)))
		     (t
		      (eliminate-newlines
			(convert-text-to-text-string (cdr expression?))
			t ; eliminate
			t))))
	     (width-of-name-string
	       (compute-width-of-text-line
		 name-string nil nil
		 (text-cell-font-map text-box-format)
		 (default-word-spacing text-box-format)))
	     (point-marker-string?
	       (and (point-visible? point-format)
		    (make-point-style-string point-format)))
	     (width-of-point-marker-string
	       (if point-marker-string?
		   (compute-width-of-text-line
		     point-marker-string? nil nil
		     (text-cell-font-map text-box-format)
		     (default-word-spacing text-box-format))
		   0)))
	(cond ((<w (+w  width-of-name-string width-of-point-marker-string)
		   (-w legend-width
		       (twicew graph-minimum-text-spacing)))
	       (let ((legend-text-string
		       (twith-output-to-text-string
			 (tformat "~a~a~(~a~)~a~a"
				  name-string
				  (if (and (not (eq legend-color 'matching))
					   plot-color?)
				      " in " "")
				  (if (and (not (eq legend-color 'matching))
					   plot-color?)
				      plot-color? "")
				  (if point-marker-string? " " "")
				  (or point-marker-string? "")))))
		 (reclaim-text-string name-string)
		 (when point-marker-string?
		   (reclaim-text-string point-marker-string?))
		 (slot-value-push 
		   (make-legend-line legend-text-string text-box-format
				     legend-width 0 color?)
		   lines)))
	      (t
	       (slot-value-push
		 (make-legend-line name-string text-box-format
				   legend-width 0 color?)
		 lines)
	       (when point-marker-string?
		 (slot-value-push
		   (make-legend-line point-marker-string? text-box-format
				     legend-width 0 color?)
		   lines))))))
	finally
	  (setq lines (nreverse lines))
	  (return
	    (values lines
		    (text-cell-line-spacing text-box-format)
		    (text-cell-line-height text-box-format)
		    legend-width))))

(defun eliminate-newlines (text-string delete-p convert-to-spaces?) ; consumes arg
  (prog1
      (copy-text-string-without-newlines text-string convert-to-spaces?)
    (when delete-p
      (reclaim-text-string text-string)))
  ;; above replaces this original code: (MHD 12/8/94)
;  (let ((count 0)
;        (length (length text-string)))
;    (loop for i from 0 below length
;          do
;      (cond ((and (eql (char text-string i) #\@)
;                  (<f (+f i 1) length)
;                  (eql (char text-string (+f i 1)) #\L))
;             (decf count))
;            (t
;             (incf count))))
;    (loop with reduced-string = (obtain-simple-text-string count)
;          with new-index = 0
;          with skip-next-p = nil
;          for i from 0 below length
;          do
;      (cond ((and (eql (char text-string i) #\@)
;                  (<f (+f i 1) length)
;                  (eql (char text-string (+f i 1)) #\L))
;             (setf skip-next-p t))
;            (skip-next-p
;             (setf skip-next-p nil))
;            (t
;             (setf (schar reduced-string new-index)
;                   (char text-string i))
;             (incf new-index)))
;          finally
;            (when delete-p 
;              (reclaim-text-string text-string))
;            (return reduced-string)))
  )

;; Surprisingly, this previously just always got rid of newlines, rather than
;; replacing them with spaces, which it now does.  This had to changed, since it
;; would, for example, have printed
;;
;;    the
;;    g2-window-width
;;    of
;;    this
;;    window
;;
;; as
;;
;;    theg2-window-widthofthiswindow
;;
;; The conversion to space seems more reasonable all around.  The caller for the
;; title of the trend chart, however, knows that his lines have all been
;; formatted, but end with @L, so he wants the @L's just dropped.  (MHD 12/8/94)



(defun make-point-style-string (point-format)
  (let ((style-spec (point-style point-format)))
    (twith-output-to-text-string
      (case (frame-like-value-key style-spec)
	(standard
	 (tformat "using ~(~a~) as marker"
		  (let ((standard-style (frame-like-value-property
					  style-spec 'shape)))
		    (case standard-style
		      ((triangle plus-sign square)
		       standard-style)
		      (current-value
		       "current value")))))
	(custom
	 (tformat "using icon of ~(~a~) as marker"
		  (frame-like-value-property style-spec 'icon-class)))))))

(defun make-legend-line (string text-box-format width
				minimum-indent color)
  (let* ((allowed-length (-w width minimum-indent))
	 (text-width (compute-text-width-for-format 
		       string text-box-format))
	 (leftover-width (-w allowed-length text-width)))
       (slot-value-list
	 (convert-text-string-to-text string)
	 (maxw 0
	       (+w minimum-indent (halfw leftover-width)))
	 color)))

(defun compute-text-width-for-format (string text-box-format
					     &optional start end)
  (compute-width-of-text-line
    string start end
    (text-cell-font-map text-box-format)
    (default-word-spacing text-box-format)))
		     
(defun get-grid-inner-dimensions (grid-pane)
  (let ((width (display-pane-width grid-pane))
	(height (display-pane-height grid-pane))
	(border-style? (display-pane-border-style? grid-pane)))
    (cond (border-style?
	   (let ((border-width (if (eq border-style? 'hairline)
			      1 border-style?)))
	     (values (-w width (twicew border-width))
		     (-w height (twicew border-width)))))
	  (t
	   (values width height)))))


(defun layout-time-scale-in-y (trend-chart)
  (let ((time-axis (trend-chart-time-axis trend-chart)))
    (when (and (not (eq (frame-like-value-key
			  (time-axis-tickmark-frequency time-axis))
			'none))
	       (time-axis-relative-labels-visible? time-axis))
      (with-focused-display-pane (trend-chart trend-chart-layout-parent)
	(let* ((text-box-format (get-or-make-format-frame
				  '2d-time-axis-label-format))
	       (text-height (text-cell-line-height text-box-format))
	       (desired-height 
		 (+w text-height
		     graph-minimum-line-spacing
		     minimum-data-window-margin))
	       (relative-time-pane nil))
	  (setf relative-time-pane
		(new-display-pane relative-time-pane
				  trend-chart-layout-parent
				  0 ; place holder
				  (-w
				    (-w trend-chart-layout-bottom desired-height)
				    current-display-pane-top)
				  0 ; place-holder
				  desired-height))
	  (setf trend-chart-layout-relative-time-pane
		relative-time-pane)
	  (decfw trend-chart-layout-bottom desired-height)
	  (setf (relative-time-label-color relative-time-pane)
		(color-for-time-tickmarks time-axis))
	  (setf (relative-time-labels relative-time-pane)
		nil)
	  )))))

(defun-simple axis-exists-for-side-p (trend-chart side)
  (loop for sub-pane in (display-pane-sub-panes
			  (trend-chart-pane-tree trend-chart))
	thereis (and (eq (display-pane-type sub-pane) 'axis-pane)
		     (eq (axis-pane-position sub-pane) side))))

(defun layout-graph-grid (trend-chart)
  (let* ((remaining-width (-w trend-chart-layout-right trend-chart-layout-left))
	 (remaining-height (-w trend-chart-layout-bottom trend-chart-layout-top))
	 (left-offset (-w trend-chart-layout-left
			  (+w (left-edge-of-block trend-chart)
			      (display-pane-left trend-chart-layout-parent))))
	 (right-offset (-w (+w (left-edge-of-block trend-chart)
			       (display-pane-left trend-chart-layout-parent)
			       (display-pane-width trend-chart-layout-parent))
			   trend-chart-layout-right))
	 (grid-left
	   (if (axis-exists-for-side-p trend-chart 'left)
	       left-offset
	       (maxw minimum-data-window-margin left-offset)))
	 (grid-width
	   (-w remaining-width
	       (+w (-w grid-left left-offset)
		   (if (axis-exists-for-side-p trend-chart 'right)
		       0
		       (if (<=w right-offset minimum-data-window-margin)
			   minimum-data-window-margin 0)))))
	 (grid-height (-w remaining-height
			  (if trend-chart-layout-relative-time-pane
			      minimum-data-window-margin
			      (twicew minimum-data-window-margin))))
	 (grid-pane
	   (new-display-pane grid-pane
			     trend-chart-layout-parent
			     grid-left
			     (+w (-w trend-chart-layout-top
				     (+w (top-edge-of-block trend-chart)
					 (display-pane-top
					   trend-chart-layout-parent)))
				 minimum-data-window-margin)
			     grid-width
			     grid-height))
	 (trend-chart-format (trend-chart-format trend-chart)))
    (setf (display-pane-background-color grid-pane)
	  (data-window-background-color trend-chart-format))
    (setf (display-pane-border-color grid-pane)
	  (data-window-border-color trend-chart-format))
    (cond ((data-window-border-visible? trend-chart-format)
	   (setf (display-pane-border-style? grid-pane) 1)
	   (incfw trend-chart-layout-left)
	   (incfw trend-chart-layout-top)
	   (decfw trend-chart-layout-right)
	   (decfw trend-chart-layout-bottom))
	  (t
	   (setf (display-pane-border-style? grid-pane) nil)))
    (setf trend-chart-layout-grid grid-pane)
    ;; layout relative time labels in x
    (when trend-chart-layout-relative-time-pane
      (setf (display-pane-left trend-chart-layout-relative-time-pane)
	    (display-pane-left grid-pane))
      (setf (display-pane-width trend-chart-layout-relative-time-pane)
	    (display-pane-width grid-pane)))
    ))

(defun layout-grid-data-height (trend-chart)
  (declare (ignore trend-chart))
  (multiple-value-bind (inner-width inner-height)
      (get-grid-inner-dimensions
	trend-chart-layout-grid)
    (declare (ignore inner-width))
    (setf (grid-data-height trend-chart-layout-grid)
	  (-w inner-height
	      (+w (grid-label-height trend-chart-layout-grid)
		  (grid-separator-height trend-chart-layout-grid))))))

(defun layout-time-axis (trend-chart)
  (let* ((time-axis (trend-chart-time-axis trend-chart))
	 (jump-scroll-p (time-axis-jump-scroll? time-axis))
	 (scroll-interval?
	   (car (time-axis-scroll-interval time-axis)))
	 (end-time-spec (end-time time-axis))
	 (tickmark-spec (time-axis-tickmark-frequency
			  time-axis))
	 (grid-pane trend-chart-layout-grid)
	 (trend-chart-timespan? (get-time-span trend-chart)))
    (with-temporary-gensym-float-creation layout-time-axis
      (setf (grid-timespan grid-pane)
	    (if (trend-chart-timespan trend-chart)
		(time-to-fixnum
		  (fast-time-slot trend-chart trend-chart-timespan))
		(or trend-chart-timespan? 300)))
      (setf (grid-time-label-color trend-chart-layout-grid)
	    (color-for-time-tickmarks time-axis))
      (setf (grid-end-time-mode grid-pane)
	    (frame-like-value-key end-time-spec))
      (case (frame-like-value-key end-time-spec)
	((last-sample current-time)
	 (reclaim-time-slot grid-pane grid-end-time?))
	(start-relative
	 (mutate-time-slot grid-pane
			   grid-end-time?
			   (fixnum-to-time
			     (car (frame-like-value-property
				    end-time-spec 'interval)))))
	(absolute
	 (cerror "" "Write Me!")))
      (cond
	((and jump-scroll-p scroll-interval?)
	 (let ((safe-scroll-interval (minf scroll-interval?
					   (grid-timespan grid-pane))))
	   (mutate-time-slot grid-pane grid-scroll-timespan?
			     (fixnum-to-time safe-scroll-interval))
	   (mutate-time-slot grid-pane grid-time-alignment?
			     (fixnum-to-time safe-scroll-interval))))
	((and jump-scroll-p trend-chart-timespan?) ; guard against whole history
	  (let ((computed-interval
		  (fixnum-to-time 
		    (compute-default-major-grid-line-interval
		      (grid-timespan grid-pane)
		      (display-pane-width grid-pane)))))
	    (mutate-time-slot grid-pane grid-scroll-timespan?
			      computed-interval)
	    (mutate-time-slot grid-pane grid-time-alignment?
			      computed-interval)))
	(t
	 (reclaim-time-slot grid-pane grid-scroll-timespan?)
	 (reclaim-time-slot grid-pane grid-time-alignment?)))
      ;; layout the time-labels (incl. grid-lines)
      (cond
	((or (eq 'none  (frame-like-value-key tickmark-spec))
	     (null (grid-timespan grid-pane)))
	 (reclaim-time-slot grid-pane grid-tickmark-interval?)
	 (setf (grid-label-ratio grid-pane) nil)
	 (setf (grid-label-height grid-pane) 0)
	 (setf (grid-separator-height grid-pane) 0))
	(t ; (memq key (synchronized interval)
	 (let* ((text-box-format (get-or-make-format-frame
				   '2d-time-axis-label-format))
		(text-height (text-cell-line-height text-box-format))
		(text-max-width (get-maximum-width-for-time-label
				  (time-axis-label-format time-axis)
				  text-box-format))
		(specified-tickmark-interval?
		  (case (frame-like-value-key tickmark-spec)
		    (synchronized
		     (cond ((null jump-scroll-p)
			    nil)
			   ((null trend-chart-timespan?)
			    nil)
			   (t
			    (fast-time-slot grid-pane grid-scroll-timespan?))))
		    (interval
		     (fixnum-to-time
		       (car (frame-like-value-property
			      tickmark-spec 'length))))))
		(tickmark-interval
		  (or specified-tickmark-interval?
		      (fixnum-to-time
			(compute-default-major-grid-line-interval
			  (grid-timespan grid-pane)
			  (display-pane-width grid-pane))))))
	   ;; give history mode tickmarks an alignment
	   (when (and (not (grid-time-alignment? grid-pane))
		      (not trend-chart-timespan?))
	     (mutate-time-slot grid-pane grid-time-alignment?
			       tickmark-interval))
	   (mutate-time-slot grid-pane grid-tickmark-interval?
			     tickmark-interval)
	   (when trend-chart-layout-relative-time-pane
	     (compute-relative-time-labels time-axis grid-pane tickmark-interval))
	   (cond
	     ((time-axis-absolute-labels-visible? time-axis)
	      (setf (grid-label-ratio grid-pane)
		    (compute-grid-label-ratio
		      text-max-width tickmark-interval grid-pane))
	      (setf (grid-label-height grid-pane)
		    text-height)
	      (setf (grid-separator-height grid-pane)
		    (+f 2 graph-minimum-line-spacing)) ; eventually care about base line slot !
	      )
	     (t
	      (setf (grid-label-ratio grid-pane) 1)
	      (setf (grid-label-height grid-pane) 0)
	      (setf (grid-separator-height grid-pane) 0)))
	   ))))))

(defun compute-relative-time-labels (time-axis grid-pane tickmark-interval)
  (let* ((relative-time-pane trend-chart-layout-relative-time-pane)
	 (text-box-format (get-or-make-format-frame
			    '2d-time-axis-label-format))
	 (absolute-time-label-format (time-axis-label-format time-axis))
	 (relative-time-label-format (case absolute-time-label-format
				       ((hh-mm-ss-interval hh-mm-ss-am-pm)
					'hh-mm-ss)
				       ((hh-mm-interval hh-mm-am-pm)
					'hh-mm)
				       ((mmm-dd-hh-mm
					  mm/dd-hh-mm
					  dd-hh-mm-interval
					  mm-yy
					  mm-dd-yy
					  yy-mm-dd    
					  dd-mm-yy
					  dd-mmm-yyyy
					  mmm-dd-yyyy
					  mmm-yyyy)
					'days-hh-mm)
				       (mm-ss-interval 'mm-ss)
				       (otherwise absolute-time-label-format)))
	 ;; could make more specific width computer for rel-time-labels
	 (text-max-width (get-maximum-width-for-time-label
			   relative-time-label-format text-box-format))
	 (midnight (compute-midnight-as-gensym-time))
	 (label-alignment (time-axis-label-alignment time-axis))
	 (grid-width (fixnum-to-time (display-pane-width grid-pane)))
	 (grid-timespan (fixnum-to-time (grid-timespan grid-pane)))
	 (grid-label-ratio
	   (compute-grid-label-ratio text-max-width tickmark-interval grid-pane)))
       (loop with time-labels = nil
	     for offset = 0.0
			then (+time offset
				    (*time tickmark-interval
					   (fixnum-to-time grid-label-ratio)))
	     as centering-point
	        = (time-to-fixnum
		    (/time (*time grid-width (-time grid-timespan offset))
			   grid-timespan))
	     as time-label
	        = (generate-relative-time-label
		    (time-to-fixnum offset) midnight relative-time-label-format)
	     as width-of-label
	        = (graph-text-width time-label text-box-format nil nil)
	     as left-edge-of-text
	        = (case label-alignment
		    (left centering-point)
		    (center (-w centering-point (halfw width-of-label)))
		    (right  (-w centering-point width-of-label)))
	     as right-edge-of-text
	        = (case label-alignment
		    (left (+w centering-point width-of-label))
		    (center (+w centering-point (halfw width-of-label)))
		    (right  centering-point))
	     while (<=time offset grid-timespan)
	     do
	  (if (and (>=w left-edge-of-text 0)
		   (<=w right-edge-of-text (display-pane-width grid-pane)))
	    (slot-value-push
	     (slot-value-list
	      (convert-text-string-to-text time-label)
	      left-edge-of-text)
	     time-labels)
	    (reclaim-text-string time-label))
	  (setf time-label nil)
	     finally
	  (when time-label
	    (reclaim-text-string time-label))
	  (setf (relative-time-labels relative-time-pane)
		  time-labels))))


(defun compute-midnight-as-gensym-time ()
  (let ((gt (clock-get gensym-time)))
    (multiple-value-bind
	  (seconds minutes hours)
	(decode-gensym-time gt)
      (-f gt
	  (+f
	   (*f hours 3600)
	   (*f minutes 60)
	   seconds)))))

(defun compute-midnight-as-g2-time ()
  (let ((current-time (managed-float-value (clock-get current-g2-time))))
    (multiple-value-bind
	(seconds minutes hours)
	(gensym-decode-unix-time current-time)
      (-time current-time
	     (fixnum-to-time
	       (+f
		 (*f hours 3600)
		 (*f minutes 60)
		 seconds))))))
  
(defun generate-relative-time-label (time-offset midnight time-label-format)
  (let* ((days (floorf time-offset 86400))
	 (seconds-offset (-f time-offset (*f days 86400))))
    (multiple-value-bind
	(seconds minutes hours)
	(decode-gensym-time
	  (+f midnight seconds-offset))
      (twith-output-to-text-string
	(case time-label-format
	  (hh-mm-ss
	   (tformat "-~d:~a~d:~a~d"
		    hours 
		  (if (<f minutes 10) "0" "")
		  minutes
		  (if (<f seconds 10) "0" "")
		  seconds))
	  (hh-mm
	   (tformat "-~d:~a~d"
		    hours
		    (if (<f minutes 10) "0" "")
		    minutes))
	  (mm-ss
	   (tformat "-~a~d:~a~d"
		    (if (<f minutes 10) "0" "")
		    minutes
		    (if (<f seconds 10) "0" "")
		    seconds))
	  (days-hh-mm
	   (tformat "-~d ~d:~a~d"
		    days
		    hours
		    (if (<f minutes 10) "0" "")
		    minutes))
	  (hh.hh-interval 
	   (hh-mm-to-hh.hh-conversion hours minutes t))
	  )))))


;;; The time format "hh.hh as an interval" was requested by
;;; Fermentation Expert developers, etc.  This can be used to
;;; display times relative to G2 start time as hours and decimal
;;; fractions of hours.  For example, 90 minutes after G2 start
;;; time is rendered as 1:30 in the "hh-mm as an interval" time
;;; format; and as 1.50h in the "hh.hh as an interval" time format.
;;; - jpg 6/23/00

(defun hh-mm-to-hh.hh-conversion (hours minutes negative-p)
  ;; Handles the case hh.hh-interval
  ;; Displays as:  dd.ddh , d = a digit, h = h, at most 5 digits
  ;; to the left of the decimal point.
  #+development
  (when (>f hours 99999) ;; 99999 hours = 4166.625 days
    (warn "Integer hours field in hh.hh format > 5 digits wide: ~d"
	  hours))
  (when negative-p (tformat "-"))
  (with-temporary-gensym-float-creation hh-mm-to-hh.hh 
    (write-floating-point-number
      (+e (coerce-to-gensym-float hours)
	  (/e (coerce-to-gensym-float minutes) 60.0))
      (ceiling (log (+ hours 1) 10))  ;; number of digits in hours 
      2 6 nil nil nil))
  (tformat "h"))
    
(defun compute-grid-label-ratio (text-max-width tickmark-interval grid-pane)
  (let ((w-units-per-tickmark-interval
	  (*time (fixnum-to-time
		   (display-pane-width grid-pane))
		 (/time tickmark-interval
			(fixnum-to-time (grid-timespan
					  grid-pane))))))
    (time-to-fixnum
      (ceiling-time
	(/time (fixnum-to-time text-max-width)
	       w-units-per-tickmark-interval)))))

(defun compute-default-major-grid-line-interval (timespan data-window-width)
  ;; (let ((res (floorf timespan 5)))
  ;;   (if (=f res 0) timespan res)))
  (calculate-tickmark-interval timespan data-window-width
			       (floorf data-window-width 6)))

(defun calculate-tickmark-interval (fixnum-data-window-timespan
				     data-window-width
				     label-width)
  (let*
      ((max-labels (floorf data-window-width label-width))
       (fixnum-interval?
	 (cond
	   ((<= fixnum-data-window-timespan 60)
	    (loop for unit in '(1 5 10 15 30 60)
		  when (<=f (ceilingf fixnum-data-window-timespan unit)
			    max-labels)
		    return unit))
	   ((<= fixnum-data-window-timespan 3600)
	    (loop with rounded-timespan = (*f 60
					      (floorf fixnum-data-window-timespan
						      60))
		  for unit in '(15 30 60 120 180 300 600 900 1200 1800 3600)
		  when  (<=f (ceilingf rounded-timespan unit)
			    max-labels)
		    return unit))
	   ((<= fixnum-data-window-timespan 86400)
	    (loop with rounded-timespan = (*f 3600
					      (floorf fixnum-data-window-timespan
						      3600))
		  for unit in '(300 600 900 1800 3600 7200
				10800 14400 21600 28800 43200)
		  when (<=f (ceilingf rounded-timespan unit)
			    max-labels)
		    return unit))
	   (t 
	    (loop with rounded-timespan
		       = (*f 86400
			     (floorf fixnum-data-window-timespan
				     86400))
		  with first-guess = (*f 86400
					 (floorf (floorf rounded-timespan max-labels)
						 86400))
		  for unit from (maxf 86400 first-guess) by 86400
		  when (<= (ceilingf rounded-timespan unit)
			   max-labels)
		    return unit)))))
    (or fixnum-interval?
	(if (>=f label-width data-window-width)
	    (*f fixnum-data-window-timespan
		(ceilingf label-width data-window-width))
	    fixnum-data-window-timespan))))

(defun layout-value-axes-in-x (trend-chart)
  (let ((visible-value-axes '()))
    ;; Step One: Find all value axes that will be drawn under the
    ;;           current slot-(component-)values
    (loop for value-axis? being the slot-component-groups 
	      of (trend-chart-value-axes trend-chart)
	  when (and value-axis?
		    (value-axis-visible? value-axis?)
		    ;; this test is too obtuse to synchronize with in other places
;;		    (not (eq (frame-like-value-key
;;			       (value-axis-tickmark-frequency value-axis?))
;;			     'none))
		    )
	    do
	      (slot-value-pushnew value-axis?
				  visible-value-axes))
    ;; Step Two: For Each visible visible axis lay it out
    (loop for value-axis in visible-value-axes
	  do
            (layout-value-axis-in-x trend-chart value-axis)
      finally (reclaim-slot-value-list visible-value-axes))))

(defun layout-value-axes-in-y (trend-chart)
  (declare (ignore trend-chart))
  (loop with text-box-format
	  = (get-or-make-format-frame '2d-value-axis-label-format)
	with axis-label-height
	  = (+w (text-cell-line-height text-box-format)
		graph-minimum-line-spacing)
	with maximum-tickmarks
	= (floorf (grid-data-height trend-chart-layout-grid)
		  axis-label-height)
	with new-sub-pane-list = '()
        for axis-pane in (display-pane-sub-panes
			   trend-chart-layout-parent)
	do
	 (cond
	   ((eq (display-pane-type axis-pane) 'axis-pane)
	    (cond ((>w (grid-data-height trend-chart-layout-grid) 1)
		   (setf (display-pane-top axis-pane)
			 (display-pane-top trend-chart-layout-grid))
		   (setf (display-pane-height axis-pane)
			 (grid-data-height trend-chart-layout-grid))
		   (setf (axis-pane-clip-height axis-pane)
			 (display-pane-height trend-chart-layout-grid))
		   (setf (axis-pane-maximum-tickmarks axis-pane)
			 maximum-tickmarks)
		   (setf (axis-pane-label-height axis-pane)
			 axis-label-height)
		   (slot-value-push axis-pane new-sub-pane-list))
		  (t
		   (reclaim-pane-tree axis-pane))))
	   (t
	    (slot-value-push axis-pane new-sub-pane-list)))
	finally
	  (reclaim-slot-value-list
	    (display-pane-sub-panes trend-chart-layout-parent))
	  (setf (display-pane-sub-panes trend-chart-layout-parent)
		(nreverse new-sub-pane-list))))

(defun compute-layout-of-value-axis-labels (value-axis)
  (cond
    ((not (value-axis-labels-visible? value-axis))
     (values 'invisible 0 0 0 0 0))
    ((show-value-labels-as-percent? value-axis)
     (compute-width-of-fixed-value-axis-labels
       value-axis t))
    (t
     (case (verified-value-axis-range-mode value-axis)
       (fixed
	(compute-width-of-fixed-value-axis-labels
	  value-axis nil))
       ((automatic high-water-marking)
	(compute-width-of-floating-value-axis-labels
	  value-axis))))))

(defun show-label-using-scientific-p (value axis-pane)
  (with-temporary-gensym-float-creation value-axis-pane
    (let* ((places-to-left (axis-pane-fixed-left-digits axis-pane))
	   (places-to-right (axis-pane-fixed-right-digits axis-pane))
	   (range (abs-value value)))
      ;; give up if range too great
      (and (/=value range 0.0)
	   (or (>value range (expt-value 10.0 (fixnum-to-value places-to-left)))
	       (<value range (expt-value 10.0 (fixnum-to-value
						(-f places-to-right)))))))))

(defun compute-width-of-fixed-value-axis-labels (axis percent-p)
  (with-temporary-gensym-float-creation value-axis-layout
    (let* ((range
	    (if percent-p
		100.0
		(maxvalue
		  (abs-value (fast-value-slot axis value-axis-lower-bound?))
		  (abs-value  (fast-value-slot axis value-axis-upper-bound?)))))
	   (significant-digits
	    (if percent-p
		(maxf 4 (value-axis-label-significant-digits axis))
		(value-axis-label-significant-digits axis)))
	   (float-significant-digits (fixnum-to-value
				       significant-digits)))
      (cond
	;; give up if range too great
	((or (>value range (expt-value 10.0 float-significant-digits))
	     (<value range (expt-value 10.0 (-value 1.0 float-significant-digits))))
	 #+development
	 (when percent-p
	   (error "Hey Joe - Think Again!"))
	 (compute-width-of-floating-value-axis-labels
	   axis))
	(t
	 (let* (; (log-of-range (log-value range 10.0))
		(places-to-left
		  (value-to-fixnum
		    (maxvalue 1.0
			      (+value 1.0 (floor-value
					    (+value 0.000001
						    (log-value range 10.0)))))))
		(places-to-right (-f significant-digits places-to-left))
		(sample-string
		  (write-sample-float-value places-to-left places-to-right)))
	   (values (if percent-p 'percent 'fixed)
		   (+w (get-width-of-value-label sample-string)
		       (twicew graph-minimum-text-spacing)
		       (if percent-p
			   (get-width-of-value-label #w"%")
			   0))
		   (prog1
		       (+w (find-position-of-decimal-in-value-label sample-string)
			   graph-minimum-text-spacing)
		     (reclaim-slot-value sample-string))
		   nil
		   places-to-left
		   places-to-right)))))))

(defun write-sample-float-value (places-to-left places-to-right)
  (setf places-to-right (maxf places-to-right 1))
  (twith-output-to-text-string
    (twrite-char #.%\-)
    (loop for i from 0 below places-to-left do (twrite-char #.%\9))
    (twrite-char #.%\.)
    (loop for i from 0 below places-to-right do (twrite-char #.%\9))))

(defun get-width-of-value-label (value-label-text)
  (let ((text-box-format (get-or-make-format-frame '2d-value-axis-label-format)))
    (graph-text-width value-label-text text-box-format nil nil)))

(defun find-position-of-decimal-in-value-label (value-label-text)
  (let ((text-box-format (get-or-make-format-frame '2d-value-axis-label-format))
	(string-decimal-pos? (g2-text-character-search #.%\. value-label-text)))
    (and string-decimal-pos?
	 (graph-text-width value-label-text text-box-format
			   nil string-decimal-pos?))))

(defun compute-width-of-floating-value-axis-labels (axis)
  (with-temporary-gensym-float-creation value-axis-layout
    (let* ((significant-digits
	     (value-axis-label-significant-digits axis))
	   (places-to-left (ceilingf significant-digits 2))
	   (places-to-right (-f significant-digits places-to-left))
	   (sample-scientific-number (/value -1.0 (most-positive-value)))
	   (sample-scientific-text-string
	     (twith-output-to-text-string
	       (write-floating-point-number
		 sample-scientific-number places-to-left places-to-right
		 (+f places-to-left places-to-right) nil t)))
	   (sample-fixed-text-string
	     (write-sample-float-value places-to-left places-to-right))
	   (width-of-scientific-number
	     (get-width-of-value-label sample-scientific-text-string))
	   (width-of-fixed-number
	     (get-width-of-value-label sample-fixed-text-string))
	   (offset-of-scientific-number
	     (find-position-of-decimal-in-value-label sample-scientific-text-string))
	   (offset-of-fixed-number
	     (find-position-of-decimal-in-value-label sample-fixed-text-string)))
      (reclaim-slot-value sample-scientific-text-string)
      (reclaim-slot-value sample-fixed-text-string)
      (values 'floating
	      (+w (twicew graph-minimum-text-spacing)
		  (maxw width-of-scientific-number width-of-fixed-number))
	      (+w graph-minimum-text-spacing offset-of-fixed-number)
	      (+w graph-minimum-text-spacing offset-of-scientific-number)
	      places-to-left
	      places-to-right))))

;; value-axis-base-line-visible? color-for-value-axis-base-line


(defun layout-value-axis-in-x (trend-chart value-axis)
  (multiple-value-bind (axis-number-format axis-labels-max-width
			axis-fixed-decimal-offset axis-float-decimal-offset
			axis-fixed-left-digits axis-fixed-right-digits)
      (compute-layout-of-value-axis-labels value-axis)
    (let* ((width-of-base-line
	     (if (value-axis-base-line-visible? value-axis) 1 0))
	   (remaining-width-to-allocate
	     (-w trend-chart-layout-right trend-chart-layout-left))
	   (axis-max-width
	     (if (=w axis-labels-max-width 0)
		 minimum-data-window-margin
		 (+w axis-labels-max-width width-of-base-line)))
	   (leftover-width-if-axis-granted
	     (-w remaining-width-to-allocate axis-max-width)))
      (cond ((>=w leftover-width-if-axis-granted
		  minimum-data-window-size)
	     (let ((position (value-axis-position value-axis))
		   right left base-line-position)
	       (cond
		 ((eq position 'left)
		  (setf left trend-chart-layout-left)
		  (setf right (+w trend-chart-layout-left axis-max-width))
		  (setf trend-chart-layout-left right)
		  (setf base-line-position (1-w axis-max-width)))
		 (t
		  (setf left (-w trend-chart-layout-right axis-max-width))
		  (setf right trend-chart-layout-right)
		  (setf trend-chart-layout-right left)
		  (when (value-axis-base-line-visible? value-axis)
		    (incfw axis-fixed-decimal-offset)
		    (when axis-float-decimal-offset
		      (incfw axis-float-decimal-offset)))
		  (setf base-line-position 1)))
	       (let ((axis-pane
		       (new-display-pane
			 axis-pane
			 trend-chart-layout-parent
			 (-w left
			     (+w (left-edge-of-block trend-chart)
				 (display-pane-left trend-chart-layout-parent)))
			 0 ; place-holder for top
			 (-w right left)
			 0))) ; place-holder-for-height
		 (setf (display-pane-component-group? axis-pane)
		      value-axis)
		 (setf (axis-pane-position axis-pane) position)
		 (setf (axis-pane-number-format axis-pane)
		       axis-number-format
		       (axis-pane-fixed-decimal-offset axis-pane)
		       axis-fixed-decimal-offset
		       (axis-pane-floating-decimal-offset axis-pane)
		       axis-float-decimal-offset
		       (axis-pane-fixed-left-digits axis-pane)
		       axis-fixed-left-digits
		       (axis-pane-fixed-right-digits axis-pane)
		       axis-fixed-right-digits
		       (axis-pane-base-line-left-offset? axis-pane)
		       (and (value-axis-base-line-visible? value-axis)
			    base-line-position)
		       (axis-pane-base-line-color axis-pane)
		       (color-for-value-axis-base-line value-axis))
		 )))
	    (t
	     (add-or-delete-trend-chart-note
	       trend-chart nil 'too-many-value-axes t)
	     nil)))))

;; the bounding box is in workspace coordinates

(defun change-size-of-trend-chart (trend-chart
				    left-edge-of-bounding-box top-edge-of-bounding-box
				    right-edge-of-bounding-box bottom-edge-of-bounding-box)
  ;; erase old thing
  (let ((region-invalidation-is-preferred t))		    ; Required to handle XOR mode.
    (update-trend-chart trend-chart t t)

    (let* ((bounding-box-width (-w right-edge-of-bounding-box left-edge-of-bounding-box))
	   (bounding-box-height (-w bottom-edge-of-bounding-box top-edge-of-bounding-box))
	   (new-width
	     (maxw bounding-box-width (twicew minimum-data-window-size)))
	   (new-height
	     (maxw bounding-box-height (twicew minimum-data-window-size)))
	   (delta-left-edge (-f left-edge-of-bounding-box (left-edge-of-block trend-chart)))
	   (delta-top-edge  (-f top-edge-of-bounding-box (top-edge-of-block trend-chart))))
      (change-edges-of-block trend-chart
			     left-edge-of-bounding-box
			     top-edge-of-bounding-box
			     (+w left-edge-of-bounding-box new-width)
			     (+w top-edge-of-bounding-box new-height))
      (when (and g2-has-v5-mode-windows-p
		 (not ws-protocol-handle-moves-from-edge-change-p)
		 (or (/=f delta-left-edge 0)
		     (/=f delta-top-edge 0)))
	(send-ws-representations-item-moved
	  trend-chart delta-left-edge delta-top-edge)))
    
    (decache-and-remove-all-image-plane-states-from-trend-chart trend-chart)
    
    (enlarge-workspace-for-block-rectangle-if-necessary trend-chart nil)
    
    (update-trend-chart trend-chart t)))

  
(defun restore-trend-chart-to-normal-size (trend-chart)
  (let* ((left   (left-edge-of-block trend-chart))
	 (top    (top-edge-of-block  trend-chart))
	 (right  (+w left default-trend-chart-width))
	 (bottom (+w top  default-trend-chart-height)))
    (change-size-of-trend-chart trend-chart left top right bottom)))




;;;; Drawing a Trend-Chart (painting plots)

;;; Drawing Priorities are used to enforce proper layering
;;; in suspendable painting actions

(defparameter time-grid-line-priority 3)
(defparameter value-grid-line-priority 2)
(defparameter extra-grid-line-priority 1)
(defparameter default-grid-element-priority 0)


(defmacro make-painting-queue-element (&body args)
  `(slot-value-list ,@args))

(defun add-to-painting-queue (painting-queue-element)
  (cond ((null current-grid-painting-queue)
	 (let ((painting-queue (slot-value-list painting-queue-element)))
	   (setf current-grid-painting-queue painting-queue)
	   (setf current-grid-painting-queue-tail painting-queue)))
	(t
	 (setf (cdr current-grid-painting-queue-tail)
	       (slot-value-list painting-queue-element))
	 (pop current-grid-painting-queue-tail))))

(defmacro write-painting-queue-element (&body args)
  `(add-to-painting-queue (make-painting-queue-element ,@args)))

(defun reclaim-painting-queue ()
  (loop for painting-queue-element in current-grid-painting-queue
	do
    (reclaim-slot-value-list painting-queue-element))
  (reclaim-slot-value-list current-grid-painting-queue)
  (setf current-grid-painting-queue nil)
  (setf current-grid-painting-queue-tail nil))

(def-global-property-name grid-painting-function)

;; don't change this parameter without re-writing replay-grid-painting
(eval-when (:compile-toplevel :load-toplevel :execute)
  (defparameter max-args-for-grid-painting-function 10))

;; grid painting functions have a fixed number of args

#+development
(defun remove-grid-painting-function (name)
  (setf (grid-painting-function name) nil))

;;; `define-grid-painting-function' defines a function which will
;;; operate at the lowest level in 2d grid painting.  The calls
;;; to such functions are stored in a queue to accomplish the
;;; strange "monochrome" style multi-color raster painting.
;;; The arguments passed to such functions are not reclaimed, so they
;;; had better be immediate values or structures that are managed
;;; by some facility.

(defmacro define-grid-painting-function (name args &body body)
  (let ((arg-count (length args))
	(declarations (if (eq (caar body) 'declare) (list (car body)) nil))
	(real-body (if (eq (caar body) 'declare) (cdr body) body)))
    (when (>= arg-count max-args-for-grid-painting-function)
      (error "Grid Painting Function: ~a has more than ~d args"
	      name (1- max-args-for-grid-painting-function)))
    `(defun-simple ,name ,args
       ,@declarations
       (when (eq current-grid-painting-mode :multiple-pass-initial)
	 (write-painting-queue-element
	   #',name ,arg-count ,@args))
       ,@real-body)))

(defmacro make-simple-compiled-funcall (function-var arg-var n)
  (loop for i from 0 below n
	collect
	`(prog1 (car-of-cons ,arg-var)
	   (setf ,arg-var (cdr-of-cons ,arg-var)))
	  into arg-forms
	finally
	  (return `(funcall-simple-compiled-function ,function-var ,@arg-forms))))

(defmacro argument-count-based-simple-compiled-function-dispatch
    (function arg-list arg-count max-args)
  (let ((returned-value (gensym)))
    `(let ((simple-compiled-function ,function)
	   (argument-list ,arg-list)
	   ,returned-value)
       (fixnum-case ,arg-count
	 ,@(loop for i from 0 below (eval max-args)
		 collect
		 `(,i (setq ,returned-value
			    (funcall-simple-compiled-function
			      simple-compiled-function
			      ,@(loop for arg-number from 0 below i
				      collect
				      `(prog1 (car-of-cons argument-list)
					 (setf argument-list
					       (cdr-of-cons argument-list)))))))))
       ,returned-value)))


(defun replay-grid-painting ()
  (loop for (function arg-count . args) in current-grid-painting-queue
	 do
    (argument-count-based-simple-compiled-function-dispatch
      function args arg-count max-args-for-grid-painting-function)))

(def-structure (incomplete-painting-action
		 (:constructor make-incomplete-painting-action
			       (painting-action-function
				painting-action-arglist
				painting-action-argtypes
				painting-action-argcount
				painting-action-current-x
				painting-action-priority)))
  painting-action-function
  painting-action-arglist  ; per instance storage
  painting-action-argtypes ; macro-expand-time constant storage
  painting-action-argcount
  painting-action-current-x
  painting-action-priority)




(defvar current-painting-action nil)

(defun make-incomplete-painting-action-function
    (painting-action-function painting-action-arglist
     painting-action-argtypes painting-action-argcount
     painting-action-current-x
     &optional (painting-action-priority 0))
  (make-incomplete-painting-action
    painting-action-function
    painting-action-arglist
    painting-action-argtypes
    painting-action-argcount
    painting-action-current-x
    painting-action-priority))

(defun copy-incomplete-painting-action (painting-action)
  (make-incomplete-painting-action
    (painting-action-function painting-action)
    (painting-action-arglist painting-action)
    (painting-action-argtypes painting-action)
    (painting-action-argcount painting-action)
    (painting-action-current-x painting-action)
    (painting-action-priority painting-action)))

(defun queue-incomplete-painting-action (painting-action)
  (slot-value-push painting-action
		   (2d-incomplete-painting-actions current-2d-state)))

(defun-void delete-incomplete-painting-action (painting-action)
  (setf (painting-action-function painting-action) nil)
  (reclaim-slot-value (painting-action-arglist painting-action))
  (setf (painting-action-arglist painting-action) nil)
  (setf (painting-action-argtypes painting-action) nil)
  (reclaim-incomplete-painting-action painting-action))
   
(defmacro current-painting-action-state ()
  `(painting-action-current-x current-painting-action))

(def-system-variable scratch-incomplete-painting-action GRAPHS
  (:funcall make-incomplete-painting-action-function
	    nil nil nil 0 -1))

(defun-for-macro parse-suspendable-painting-action-arg-spec (arg-spec)
  (loop with arglist-for-run-function = '()
	with argtypes-for-run-function = '()
	with argcount-for-run-function = 0
	for (arg-name arg-type) in arg-spec
	do
	  (push arg-type argtypes-for-run-function)
	  (push arg-name arglist-for-run-function)
          (incf argcount-for-run-function)
    finally
	  (return (values (reverse arglist-for-run-function)
			  (reverse argtypes-for-run-function)
			  argcount-for-run-function))))


(defmacro define-suspendable-painting-action
    (name arg-spec &body body)
  (let ((name-for-run-function (build-ab-symbol 'run name)))
    (when (> (length arg-spec) maximum-painting-action-args)
      (error "Too many arguments for suspendable painting-action ~a"
	     name))
    (multiple-value-bind (arglist-for-run-function
			  argtypes-for-run-function
			  argcount-for-run-function)
	(parse-suspendable-painting-action-arg-spec arg-spec)
      (when (memq 'priority arglist-for-run-function)
	(error
	  "the priority arg is reserved by define-suspendable-painting-action"))
      `(progn
	 (defun-simple ,name-for-run-function ,arglist-for-run-function
	   ,@body)
	 (defun ,name ,(cons 'priority arglist-for-run-function)
	   (setf (painting-action-function
		   scratch-incomplete-painting-action)
		 #',name-for-run-function)
	   (setf (painting-action-arglist 
		   scratch-incomplete-painting-action)
		 (slot-value-list ,@arglist-for-run-function))
	   (setf (painting-action-argtypes
		   scratch-incomplete-painting-action)
		 ',argtypes-for-run-function)
	   (setf (painting-action-argcount
		   scratch-incomplete-painting-action)
		 ,argcount-for-run-function)
	   (setf (painting-action-current-x
		   scratch-incomplete-painting-action)
		 nil)
	   (setf (painting-action-priority
		   scratch-incomplete-painting-action)
		 priority)
	   (let ((current-painting-action
		   scratch-incomplete-painting-action))
	     (run-incomplete-painting-action
	       nil t
	       scratch-incomplete-painting-action)))))))
		   
(defun run-incomplete-painting-action (validate-arguments-p
				       running-scratch-painting-action-p
					painting-action)
  ;; apply, but not really
  (let ((runnable-p t))
    (when validate-arguments-p
      (loop for arg in (painting-action-arglist painting-action)
	    for type in (painting-action-argtypes painting-action)
	    unless
	      (case type
		(plot t)
		(otherwise t))
	      do
		(setq runnable-p nil)
		(return)))

    (cond
      (runnable-p
       (let ((done-p
	       ;; the following form is a funcall of the "run-"
	       ;; function of the suspendable-painting-action
	       (argument-count-based-simple-compiled-function-dispatch
		 (painting-action-function painting-action)
		 (painting-action-arglist painting-action)
		 (painting-action-argcount painting-action)
		 maximum-painting-action-args)))
	 (cond (done-p
		(cond
		  (running-scratch-painting-action-p
		   (slot-value-push
		     (painting-action-arglist painting-action)
		     current-grid-painting-actions-to-delete))
		  (t
		   (slot-value-push
		     painting-action current-grid-painting-actions-to-delete)))
		  ; (delete-incomplete-painting-action painting-action)))
		t)
	       ;; action is not complete
	       (t
		(queue-incomplete-painting-action
		  (cond (running-scratch-painting-action-p
			 (copy-incomplete-painting-action painting-action))
			(t
			 painting-action)))
		nil))))
      (t
       (cond
	 (running-scratch-painting-action-p
	  (slot-value-push
	    (painting-action-arglist painting-action)
	    current-grid-painting-actions-to-delete))
	 (t
	  (slot-value-push
	    painting-action current-grid-painting-actions-to-delete)))
       t))))

#+development
(defvar trace-2d-paint-queue nil)

(defun-simple incomplete-painting-action> (painting-action1
					    painting-action2)
  (>f (painting-action-priority painting-action1)
      (painting-action-priority painting-action2)))

(defun resume-incomplete-painting-actions (2d-state)
  #+development
  (when trace-2d-paint-queue
    (format t "~d actions in incomplete painting queue~%"
	    (length (2d-incomplete-painting-actions 2d-state))))
  (loop with action-queue =
	;; do priority sort here
	(sort-list (2d-incomplete-painting-actions 2d-state)
		   #'incomplete-painting-action> nil)
	for painting-action in action-queue
	initially
	  (setf (2d-incomplete-painting-actions 2d-state) nil)
	do
         (let ((current-painting-action
		 painting-action))
	     #-development
	     (run-incomplete-painting-action t nil painting-action)
	     #+development
	     (let ((done-p
		     (run-incomplete-painting-action t nil painting-action)))
	       (when (and trace-2d-paint-queue
			  (eq (painting-action-function painting-action)
			      #'RUN-PAINT-ICON-ON-GRAPH))
		 (format t
			 "  Retrying PA ~s with args ~s state=~s -> ~a~%"
			 (painting-action-function painting-action)
			 (cddddr (painting-action-arglist painting-action))
			 (painting-action-current-x painting-action)
			 (if done-p "DONE" "INCOMPLETE"))))
	     )
	finally
	  (reclaim-slot-value-list action-queue)))

(defun delete-painting-actions-or-args (list-of-actions-or-args)
  (loop for action-or-arglist in list-of-actions-or-args
	do
    (cond ((consp action-or-arglist)
	   (reclaim-slot-value action-or-arglist))
	  (t
	   (delete-incomplete-painting-action action-or-arglist)))
	finally
	  (reclaim-slot-value-list list-of-actions-or-args)))

(defun clear-incomplete-painting-actions (2d-state)
  (loop for painting-action in (2d-incomplete-painting-actions 2d-state)
	do
          (delete-incomplete-painting-action painting-action)
	finally
	  (reclaim-slot-value-list
	    (2d-incomplete-painting-actions 2d-state))
	  (setf (2d-incomplete-painting-actions 2d-state) nil)))

(defun clear-trend-chart-grid ()
  (cond
    ((eq current-grid-painting-mode :multiple-pass-subsequent)
     (replay-grid-painting))
    (t
     (reclaim-painting-queue)
     (clear-incomplete-painting-actions current-2d-state)
     (multiple-value-bind (inner-width inner-height)
	 (get-grid-inner-dimensions
	   (get-grid-for-trend-chart current-trend-chart))
       (clear-whole-raster-for-inactive
	 inner-width inner-height)))))

#+soon 
(defun test-g2-lambda-conditions () 
  (with-safe-stack-eval-reentrancy
      (let* ((cell-array? (cell-array current-trend-chart))
	     (cell-index? (car (trend-chart-plot-condition-indices
				 current-trend-chart)))
	     (cell? (and cell-array? cell-index?
			 (managed-svref
			   (g2-cell-array-managed-array cell-array?)
			   cell-index?))))
	(when (and cell?
		   (expression-cell-able-to-compute-p cell?))
	  (let ((argument-list (slot-value-list
				 (random 10)
				 (random 10))))
	    (attempt-expression-cell-execution cell? argument-list t)
	    (format t "funcalled e-cell successfully on ~s => ~S~%"
		    argument-list
		    (g2-expression-cell-cached-value cell?))
	    (reclaim-eval-list argument-list))))))

(defun paint-trend-chart-grid ()
  (cond
    ((eq current-grid-painting-mode :multiple-pass-subsequent)
     (replay-grid-painting))
    (t
     (let* ((grid-pane (get-grid-for-trend-chart current-trend-chart))
	    (fixed-time-mode-p
	      (and (get-time-span current-trend-chart)
		   (grid-end-time? grid-pane)))
 	    (full-painting-p nil))
       (reclaim-painting-queue)
       (cond
	 (current-grid-painting-is-full?
	  ;; initialize the state!
	  (initialize-2d-state current-trend-chart grid-pane)
	  (clear-incomplete-painting-actions current-2d-state)
	  (setf full-painting-p t)
	  (clear-whole-raster)
	  (update-dateline))
	 ;; partial case - scrolling
	 ((>time (fast-time-slot current-trend-chart trend-chart-end-time)
		 (fast-time-slot current-2d-state 2d-state-end-time))
	  (update-2d-state-for-scroll current-trend-chart)
	  (update-dateline)
	  )
	 ;; minimal case - no scrolling
	 (t
	  ))
       (cond
	 (full-painting-p
	  (paint-value-grid-lines current-trend-chart grid-pane)
	  (when (grid-tickmark-interval? grid-pane)
	    (paint-time-base-line current-trend-chart grid-pane)
	    (full-paint-time-labels grid-pane)))
	 (t
	  (resume-incomplete-painting-actions current-2d-state)
	  (when (grid-tickmark-interval? grid-pane)
	    (partial-paint-time-labels grid-pane))))
       
       (with-temporary-gensym-float-creation painting-tc-plots
	 ;; this loop assumes/enforces back to front layering of
	 ;; plot painting
	 (loop with earliest-time? = nil
	       with latest-time? = nil
	       with previous-plot? = nil
	       for plot being the slot-component-groups of
	       (trend-chart-plots current-trend-chart)
	       when (and
		      (plot-has-data-p plot)
		      (plot-end-time-established-p
			current-trend-chart plot))
		 do
		   (cond
		     ((any-points-painted-p plot current-2d-state)
		      (when
			  (if earliest-time?
			      (plot-has-data-to-paint-in-interval-p
				plot current-trend-chart
				earliest-time? latest-time?)
			      (plot-has-new-data-to-paint-p plot
							    current-trend-chart
							    current-2d-state))
			(setq earliest-time?
			      (compute-earliest-time-for-plot
				current-2d-state plot previous-plot? earliest-time?))
			(let ((plot-end-time
				(managed-float-aref
				  (trend-chart-plot-end-times current-trend-chart)
				  (plot-index plot))))
			  (setq latest-time?
				(if latest-time?
				    (maxtime plot-end-time latest-time?)
				    plot-end-time)))
			(setq previous-plot? plot)
			(paint-plot-data plot earliest-time? fixed-time-mode-p)))
		     (t
		      (paint-plot-data plot nil fixed-time-mode-p)))
	       finally
		 ;; update plotting times one final time
		 ;; for width of last plots marker (if any)
		 (when earliest-time?
		   (update-2d-state-for-plot-point-painting
		     previous-plot?
		     nil
		     (-time earliest-time?
			    (fixnum-to-time
			      (get-plot-width-as-time previous-plot?)))
		     nil))))
	 
       ))))

;;; A given plot might not paint in a call to paint-trend-chart-grid
;;; so what to do in earliest time computation.

(defun plot-is-sample-and-hold-p (plot)
  (let ((connector-format (get-slot-component-group-by-reference
			    current-trend-chart plot 'plot-connector-format)))
    (and (connector-visible? connector-format)
	 (not (eq (connector-line-style connector-format) 'interpolated)))))

(defun compute-earliest-time-for-plot
    (2d-state plot previous-plot? earliest-time?)
  (let ((history (plot-history plot))
	(earliest-time-for-plot
	  (managed-float-value
	    (managed-svref (2d-state-latest-event-times
			     2d-state)
			   (plot-index plot)))))
    (cond
      ((and (generic-history-supports-indexed-access-p
	      history)
	    earliest-time?)  
       (let* ((candidate-time
		(mintime
		  (-time earliest-time?
			 (fixnum-to-time
			   (get-plot-width-as-time
			     previous-plot?)))
		  earliest-time-for-plot))
	      (time-index
		(generic-history-index
		  history candidate-time 'loose t)))
	 (generic-history-timestamp
	   history time-index)))
      (earliest-time?
       (mintime
	 (-time earliest-time?
		(fixnum-to-time
		  (get-plot-width-as-time
		    previous-plot?)))
	 earliest-time-for-plot))
      (t
       earliest-time-for-plot))))


(defun get-plot-width-as-time (plot)
  (let* ((point-format 
	   (get-slot-component-group-by-reference
	     current-trend-chart plot 'plot-point-format))
	 (grid-pane (get-grid-for-trend-chart current-trend-chart))
	 (width-in-ws-units 
	   (cond
	     ((point-visible? point-format)
	      ;; un paint-plot-point
	      (let ((shape-spec (point-style point-format))
		    (marker-size default-point-marker-size))
		(case (frame-like-value-key shape-spec)
		  (custom
		   (let* ((icon-class (frame-like-value-property shape-spec
								 'icon-class))
			  (icon-description?
			    (and (classp icon-class)
				 (get-icon-description-given-class icon-class))))
		     (cond (icon-description?
			    (halfw (width-of-icon icon-description?)))
			   (t
			    0))))
		  (standard
		   (case (frame-like-value-property shape-spec 'shape)
		     (current-value
		      42) ; wow, what a hack!
		     ((triangle square plus-sign)
		      marker-size)))
		  (t
		   0))))
	     (t
	      0))))
    (ceilingf (*f (grid-timespan grid-pane)
		  width-in-ws-units)
	      (display-pane-width grid-pane))))

(defun paint-time-base-line (trend-chart grid-pane)
  (let ((time-axis (trend-chart-time-axis trend-chart)))
    (when (time-axis-base-line-visible? time-axis)
      (paint-long-line-on-graph
	value-grid-line-priority
	(grid-data-height grid-pane)
	most-positive-fixnum
	(trend-chart-color-value
	  (color-for-time-axis-base-line time-axis)
	  foreground)))))

(defun paint-value-grid-lines (trend-chart grid-pane)
  (loop for sub-pane in (display-pane-sub-panes
			  (trend-chart-pane-tree trend-chart))
	when (eq (display-pane-type sub-pane) 'axis-pane)
	  do
	    (paint-value-grid-lines-for-axis
	      trend-chart
	      grid-pane
	      (display-pane-component-group? sub-pane)
	      sub-pane)))

(defun paint-value-grid-lines-for-axis (trend-chart grid-pane axis axis-pane)
  (with-temporary-gensym-float-creation value-grid-lines
    (loop with time-axis = (trend-chart-time-axis trend-chart)
	  with interval = (if (axis-pane-textual-elements axis-pane)
			      (managed-float-value
				(axis-pane-interval axis-pane))
			      )
	  with ratio-of-grid-lines-to-tickmarks =
	  (if (value-grid-lines-visible? axis)
	      (ratio-of-grid-lines-to-value-axis-tickmarks axis)
	      0)
	  with logical-color-value =
	  (trend-chart-color-value
	    (color-for-value-grid-lines axis) foreground)
	  for ((text boxed-value left-offset top-offset has-text-p) . tail)
	  on (axis-pane-textual-elements axis-pane)
	  as first-p = t then nil
	  as last-p = (null tail)
	  do
      (loop with value = (-value 
			   (managed-float-value boxed-value)
			   (if (or first-p last-p) interval 0.0))
	    for i from (if (or first-p last-p)
			   (-f ratio-of-grid-lines-to-tickmarks)
			   0)
		  below ratio-of-grid-lines-to-tickmarks
	    do
	(paint-value-grid-line
	  value-grid-line-priority
	  axis
	  (+value value
		  (*value (if (or first-p last-p)
			      (fixnum-ratio-as-value
				(+f i ratio-of-grid-lines-to-tickmarks)
				ratio-of-grid-lines-to-tickmarks)
			      (fixnum-ratio-as-value
				i ratio-of-grid-lines-to-tickmarks))
			  interval))
	  logical-color-value
	  (if (time-axis-base-line-visible? time-axis)
	      (grid-data-height grid-pane)
	      nil))))
    ;; extra grid lines
    (loop with time-axis = (trend-chart-time-axis trend-chart)
	  for (unnormalized-value . color-spec)
	      in (cdr (extra-value-grid-lines axis))
	  as value = (cond ((fixnump unnormalized-value)
			    (coerce-fixnum-to-gensym-float unnormalized-value))
			   (t
			    (managed-float-value unnormalized-value)))
	  as logical-color-value = (trend-chart-color-value
			     (cond ((eq color-spec 'default)
				    (color-for-value-grid-lines axis))
				   (t
				    color-spec))
			     foreground)
	  when (and (<value value
			    (fast-value-slot axis value-axis-high-value))
		    (>value value
			    (fast-value-slot axis value-axis-low-value)))
	    do
	      (paint-value-grid-line
		extra-grid-line-priority
		axis value logical-color-value
		(if (time-axis-base-line-visible? time-axis)
		    (grid-data-height grid-pane)
		    nil)))))

#+development
(defun print-timestamp-as-wall-time (timestamp)
  (with-temporary-gensym-float-creation print-timestamp-as-wall-time
    (multiple-value-bind
	(seconds minutes hours date month year day-of-week)
	(gensym-decode-unix-time timestamp)
      (format t "~d:~a~d:~A~d on ~a, ~d/~d/~d~%"
	      hours
	      (if (< minutes 10) "0" "")
	      minutes
	      (if (< seconds 10) "0" "")
	      seconds
	      day-of-week month date year))))

(defun full-paint-time-labels (grid-pane)
  (paint-more-time-tickmarks grid-pane t))

(defun partial-paint-time-labels (grid-pane)
  (paint-more-time-tickmarks grid-pane nil))

(defun paint-more-time-tickmarks (grid-pane full-paint-p)
  (let* ((2d-state current-2d-state)
	 (time-axis (trend-chart-time-axis current-trend-chart))
	 (absolute-labels-visible?
	   (time-axis-absolute-labels-visible? time-axis))
	 (count 0))
    (with-temporary-gensym-float-creation paint-more-time-tickmarks
      (loop
	(incf count)
	(let* ((time-of-last-tickmark
		 (fast-time-slot 2d-state 2d-state-last-tickmark-time))
	       (interval-length
		 (fast-time-slot grid-pane grid-tickmark-interval?))
	       (time-of-new-tickmark
		 (+time time-of-last-tickmark interval-length))
	       (line-extension 0))
	  (cond ((<=time time-of-new-tickmark
			 ;;(fast-time-slot 2d-state 2d-state-last-tickmark-time)
			 (+time (fast-time-slot 2d-state 2d-state-end-time)
				(*time (fixnum-to-time
					 (grid-label-ratio grid-pane))
				       interval-length)))
		 ;; paint the label if it is its turn
		 (incf (2d-state-label-counter 2d-state))
		 (when (=f (2d-state-label-counter 2d-state)
			   (grid-label-ratio grid-pane))
		   (when absolute-labels-visible?
		     (paint-time-tickmark time-of-new-tickmark grid-pane))
		   (setf (2d-state-label-counter 2d-state) 0)
		   (setf line-extension
			 (grid-separator-height grid-pane)))
		 ;; paint time grid-lines
		 (when (and full-paint-p
			    (=f count 1)) ; special case for grid-lines to left of first
		   (loop for i from 0 to (grid-label-ratio grid-pane)
			 do
		     (paint-time-grid-lines  ; time tickmark drawn
		       (-time time-of-new-tickmark
			      (*time (fixnum-to-time i)
				     interval-length))
		       interval-length
		       0)))
		 (paint-time-grid-lines
		   time-of-new-tickmark
		   interval-length
		   line-extension)
		 (fast-mutate-time-slot 2d-state
					2d-state-last-tickmark-time
					time-of-new-tickmark))
		(t
		 (return))))))))

(defmacro interpolate-values (indep-1 dep-1 indep-2 dep-2 indep-3)
  (avoiding-variable-capture (indep-1 dep-1 indep-2 dep-2 indep-3)
    `(+e ,dep-1
	 (*e (-e ,dep-2 ,dep-1)
	     (/e (-e ,indep-3 ,indep-1)
		 (-e ,indep-2 ,indep-1))))))

(defvar plot-connector-painting-buffer-limit nil)

(defmacro allow-buffered-plot-painting-p ()
  'plot-connector-painting-buffer-limit)

(defun not-jump-scroll-mode ()
  (let ((time-axis (trend-chart-time-axis current-trend-chart)))
    (null (time-axis-jump-scroll? time-axis))))

;;; `paint-plot-data' returns a managed float in cases where the first timestamp painted
;;; precedes earliest-time-for-plot, NIL otherwise

(defun paint-plot-data (plot earliest-time-for-plot fixed-time-mode-p)
  (with-temporary-gensym-float-creation paint-plot-data
    (let* ((history (plot-history plot))
	   (constant-plot-p
	     (not (generic-history-supports-indexed-access-p history)))
	   (plot-end-time
	     (managed-float-aref
	       (trend-chart-plot-end-times current-trend-chart)
	       (plot-index plot)))
	   ;; plot end time
	   (end-time
	     (fast-time-slot current-2d-state 2d-state-end-time))
	   (current-time-p (eq 'current-time
			       (frame-like-value-key (end-time (trend-chart-time-axis
								 current-trend-chart)))))
 	   (adjust-sample-and-hold-p (and current-time-p
 					  earliest-time-for-plot))
	   (timespan (fast-time-slot current-2d-state 2d-state-grid-timespan))
	   (grid-start-time (-time end-time timespan))
 	   start-time start-index? end-index start-with-point-p)
      (cond (earliest-time-for-plot
	     (setf start-time (maxtime grid-start-time
				       earliest-time-for-plot))
	     (setf start-with-point-p nil)
	     )
	    (t
	     (setf start-time grid-start-time)
	     (setf start-with-point-p t)
	     ))
      (unless constant-plot-p
	(setf start-index?
	      (generic-history-index history start-time 'loose t))
	(when (and start-index?
	           (not-jump-scroll-mode)
	           (/=f (generic-history-start-index history) start-index?))
	  (setf start-index? (previous-generic-history-index history start-index?)))
	(setf end-index (generic-history-index history
					       (mintime plot-end-time
							end-time)
					       'inclusive nil)))
      (when (and (<=time grid-start-time start-time) ;  last-painting-time)
		 (<=time start-time end-time))
	(loop with last-value = nil
	      with last-timestamp = nil
	      with connector-format
	      = (get-slot-component-group-by-reference
		  current-trend-chart plot 'plot-connector-format)
	      with connectors-visible?
	        = (connector-visible? connector-format)
	      with point-format = (get-slot-component-group-by-reference
				    current-trend-chart plot 'plot-point-format)
	      with points-visible? = (point-visible? point-format)
	      with connector-line-style =
	      (connector-line-style connector-format)
	      with connector-color = (connector-line-color connector-format)
	      with style-arg = nil
	      with line-style =
	           (case (frame-like-value-key (connector-shading-target
						 connector-format))
		     (none
		      (setq style-arg
			    (connector-line-width connector-format))
		      'line)
		     (constant
		      (setq style-arg
			    (frame-like-value-property
			      (connector-shading-target connector-format)
			      'target))
		      'shaded))
	      with value-axis = (get-slot-component-group-by-reference
				  current-trend-chart plot 'plot-axis)
	      for index
	      = start-index? 
		  then (and start-index?
			    (next-generic-history-index history index))
	      as first-time-p = t then nil
	      as timestamp
	      = (cond
		  (start-index?
		   (generic-history-timestamp history index))
		  (first-time-p
		   start-time)
		  (t
		   end-time))
	      as value
	      = (cond
		  (start-index?
		   (generic-history-value history index))
		  (t
		   (generic-history-value-at-time history timestamp)))
	      initially
		(establish-buffered-plot-painting
		  history start-index? end-index)
		(when (allow-buffered-plot-painting-p)
		  (initialize-buffered-connector-painting
		    plot value-axis line-style connector-color style-arg
		    timespan
		    (x-in-window (2d-state-grid-width current-2d-state))))
 	      do 
	        (update-2d-state-for-plot-point-painting
		  plot index timestamp)
		(cond  
		  (last-value
		   ;; connector-line-style
		   (when connectors-visible?
		     (case connector-line-style
		       (interpolated
			(cond
			  ((allow-buffered-plot-painting-p)
			   (buffered-paint-plot-connector
			     last-value last-timestamp
			     value      timestamp))
			  (t
			   (paint-plot-connector plot value-axis
						 last-value last-timestamp
						 value      timestamp
						 connector-color
						 line-style
						 style-arg))))
		       ((sample-and-hold sample-and-hold-with-risers)
 			(when (and adjust-sample-and-hold-p
 				   (>time earliest-time-for-plot last-timestamp))
 			  (setf adjust-sample-and-hold-p nil)
 			  (setf last-timestamp (mintime timestamp earliest-time-for-plot)))
			(paint-plot-connector plot value-axis
 					      last-value last-timestamp
 					      last-value timestamp
 					      connector-color
 					      line-style
 					      style-arg)
			(when (eq connector-line-style
				  'sample-and-hold-with-risers)
			  (paint-plot-connector plot value-axis
						last-value timestamp
						value timestamp
						connector-color
						line-style
						style-arg)))))
		   (when points-visible?
		     (paint-plot-point plot value-axis value timestamp
				       point-format history)))
		  (start-with-point-p
		   (when points-visible?
		     (paint-plot-point plot value-axis value timestamp
				       point-format history))))
		(setf last-value value
		      last-timestamp timestamp)
	      until (or (and ; (not first-time-p)
			  start-index?
			  (=f index end-index))
			(if constant-plot-p
			    (>=time timestamp end-time)
			    (>=time timestamp plot-end-time)))
	      finally
		(when (allow-buffered-plot-painting-p)
		  (flush-buffered-plot-painting))
		(cond
		  ;; This fixes a bug that, in fixed time mode,
		  ;; trend-charts were not drawing the last connector
		  ;; that goes off the grid to the right. This will
		  ;; also cover right extension for sample and hold
		  ;; (i.e. the second case of the cond).
		  ((and fixed-time-mode-p
			(not constant-plot-p)
			(/=f (generic-history-end-index history)
			     end-index)
			(>time (generic-history-timestamp
				 history
				 (next-generic-history-index history end-index))
			       end-time))
		   (let* ((next-index
			    (next-generic-history-index history end-index))
			  (next-timestamp
			    (generic-history-timestamp history next-index))
			  (next-value-in-history
			    (generic-history-value history next-index))
			  (next-value
			    (if (eq connector-line-style 'interpolated)
				(if (=time timestamp next-timestamp) ; divide by 0 protection
				    value
				    (interpolate-values
				      timestamp value next-timestamp next-value-in-history
				      end-time))
				value)))
		     (update-2d-state-for-plot-point-painting
		       plot nil end-time)
		     (paint-plot-connector plot value-axis
					   value timestamp
					   next-value
					   end-time
					   connector-color
					   line-style
					   style-arg)))
		  ;; what did/does this do?
		  ;; I think it extends lines to the right so they look cool
		  ;; in sample and hold mode.
 		  ;; NOTE: only when end-time is current-time, otherwise plot-end-time
 		  ;; will equal timestamp (I think)
		  ((and connectors-visible?
 			(not (eq connector-line-style 'interpolated)))
		   (when (and adjust-sample-and-hold-p
			      timestamp
			      (>time earliest-time-for-plot timestamp))
		     (setf timestamp
			   (mintime plot-end-time
				    (maxtime start-time earliest-time-for-plot))))
		   (update-2d-state-for-plot-point-painting
		     plot nil plot-end-time)
		   (paint-plot-connector plot value-axis
					 value
					 (or timestamp start-time)
					 value plot-end-time
					 connector-color
					 line-style
					 style-arg))))))))





;;;; Painting Plot data with More Data Points than Pixels



;;; The following buffering crappola can only run in the recursive descent of
;;; paint-plot-data.  So don't get any funny ideas.  And, by the way, it's not
;;; re-entrant.  It uses globals.  Its just an optimization hack.  Some
;;; restrictions apply.  No purchase necessary.  You must be over 18 to win.
;;; Gensym employees or their families are not eligible. Void where prohibited.

(defparameter trace-buffered-plot-painting-p nil)
(defparameter trace-buffered-painting-optimization-p nil)

(defvar buffered-plot-painting-plot nil)
(defvar buffered-plot-painting-value-axis nil)
(defvar buffered-plot-painting-line-style nil)
(defvar buffered-plot-painting-color nil)
(defvar buffered-plot-painting-style-arg nil)

(defvar plot-connector-painting-buffer-head nil)
(defvar plot-connector-painting-buffer-tail nil)
(defvar plot-connector-painting-buffer-size 0)
(defvar buffered-plot-painting-one-pixel-in-seconds nil)


(defun establish-buffered-plot-painting (history start-index? end-index)
  (cond (start-index?
	 (let* ((length
		  (generic-history-interval-length
		    history start-index? end-index))
		(ratio
		 (floorf length 
			 (delta-x-in-window
			   (2d-state-grid-width current-2d-state)
			   current-grid-painting-x-scale))))
	   (cond ((>=f ratio buffered-plot-painting-minimum-ratio)
		  (setf plot-connector-painting-buffer-limit ratio))
		 (t
		  (setf plot-connector-painting-buffer-limit nil)))))
	(t
	 (setf plot-connector-painting-buffer-limit nil))))

(defun-for-system-procedure g2-set-trend-chart-buffering
    (trend-chart toggle-ev buffer-limit-ev)
  (let ((allow-buffering-p
	  (prog1 (evaluation-truth-value-is-true-p toggle-ev)
	    (reclaim-evaluation-truth-value toggle-ev)))
	(buffer-limit
	  (prog1 (maxf (minf (evaluation-integer-value buffer-limit-ev)
			     10)
		       1000)
	    (reclaim-evaluation-integer buffer-limit-ev))))
    (setf (trend-chart-paint-buffer-limit? trend-chart)
	  (and allow-buffering-p buffer-limit))))

(defmacro buffer-plot-point-value (x) `(cdr-of-cons ,x))

(defmacro buffer-plot-point-time(x) `(car-of-cons ,x))


(defmacro extend-connector-painting-buffer (time value)
  `(cond
     (plot-connector-painting-buffer-head
      (setf (cdr-of-cons plot-connector-painting-buffer-tail)
	    (gensym-list (gensym-cons ,time ,value)))
      (setf plot-connector-painting-buffer-tail
	    (cdr-of-cons plot-connector-painting-buffer-tail))
      (incff plot-connector-painting-buffer-size))
     (t
      (setf plot-connector-painting-buffer-head
	    (gensym-list (gensym-cons ,time ,value)))
      (setf plot-connector-painting-buffer-tail
	    plot-connector-painting-buffer-head)
      (setf plot-connector-painting-buffer-size 1))))
     
(defun-void initialize-buffered-connector-painting
    (plot value-axis line-style color style-arg timespan width-in-window)
  (setf plot-connector-painting-buffer-head nil)
  (setf plot-connector-painting-buffer-tail nil)
  (setf plot-connector-painting-buffer-size 0)
  (setf buffered-plot-painting-plot plot)
  (setf buffered-plot-painting-value-axis value-axis)
  (setf buffered-plot-painting-line-style line-style)
  (setf buffered-plot-painting-color color)
  (setf buffered-plot-painting-style-arg style-arg)
  (setf buffered-plot-painting-one-pixel-in-seconds
	(/e timespan
	    (coerce-fixnum-to-gensym-float width-in-window))))

(defmacro buffered-paint-connector (point-1 point-2)
  (unless (and (symbolp point-1) (symbolp point-2))
    (error "symbols only, Tex"))
  `(paint-plot-connector
     buffered-plot-painting-plot
     buffered-plot-painting-value-axis
     (buffer-plot-point-value ,point-1)
     (buffer-plot-point-time ,point-1)
     (buffer-plot-point-value ,point-2)
     (buffer-plot-point-time ,point-2)
     buffered-plot-painting-color
     buffered-plot-painting-line-style
     buffered-plot-painting-style-arg))

(defmacro buffered-paint-one-connector ()
  `(let ((point-1 (gensym-pop plot-connector-painting-buffer-head))
	 (point-2 (car plot-connector-painting-buffer-head)))
     ;; paint
     #+development
     (when trace-buffered-plot-painting-p
       (format t "painting pc from ~S at ~s to ~S at ~s~%" 
	       (buffer-plot-point-value point-1)
	       (-time (buffer-plot-point-time point-1)
		      (managed-float-value (clock-get g2-time-at-start)))
	       (buffer-plot-point-value point-2)
	       (-time (buffer-plot-point-time point-2)
		      (managed-float-value (clock-get g2-time-at-start)))))
     (buffered-paint-connector point-1 point-2)
     (reclaim-gensym-cons point-1)
     (decff plot-connector-painting-buffer-size)))

(defmacro nth-cdr-of-cons (x n)
  (if (= n 0)
      x
      `(cdr-of-cons (nth-cdr-of-cons ,x ,(1- n)))))

(defmacro paint-buffer-subset-optimizable ()
  `(let* ((first-point (car plot-connector-painting-buffer-head))
	  (later-point (car-of-cons
			 (nth-cdr-of-cons
			   plot-connector-painting-buffer-head
			   #.(1-f buffered-plot-painting-minimum-ratio))))
	  (time-difference (-time (buffer-plot-point-time later-point)
				  (buffer-plot-point-time first-point)))
	  (result
	    (<e time-difference
		buffered-plot-painting-one-pixel-in-seconds)))
     #+development
     (when trace-buffered-plot-painting-p
       (when result
	 (format t "about to optimize~%")))
     result))

(defun-void buffered-paint-plot-connector
    (value-1 time-1 value-2 time-2)
   #+development
   (when trace-buffered-plot-painting-p
     (format t "asking to paint from ~S at ~s to ~S at ~s~%" 
	     value-1
	     (-time time-1
		    (managed-float-value (clock-get g2-time-at-start)))
	     value-2
	     (-time time-2
		    (managed-float-value (clock-get g2-time-at-start)))))
  (when (=f plot-connector-painting-buffer-size 0)
    (extend-connector-painting-buffer time-1 value-1))
  (extend-connector-painting-buffer time-2 value-2)
  (when (>=f plot-connector-painting-buffer-size
	     plot-connector-painting-buffer-limit)
    (cond
      ((paint-buffer-subset-optimizable)
       (loop with start-point
	       = (car-of-cons
		   plot-connector-painting-buffer-head)
	     with start-time
	       = (buffer-plot-point-time start-point)
	     with previous-tail = nil
	     with highest-value-seen = (buffer-plot-point-value start-point)
	     with highest-value-point = start-point
	     with lowest-value-seen = highest-value-seen
	     with lowest-value-point = highest-value-point
	     for tail = plot-connector-painting-buffer-head
		      then (cdr-of-cons tail)
	     while (and (<e (-time (buffer-plot-point-time point) start-time)
			    buffered-plot-painting-one-pixel-in-seconds)
			(cdr-of-cons tail))
	     as point = start-point then (car-of-cons tail)
	     as point-value = (buffer-plot-point-value point)
	     do
	 (when (>e point-value highest-value-seen)
	   (setf highest-value-seen point-value)
	   (setf highest-value-point point))
	 (when (<e point-value lowest-value-seen)
	   (setf lowest-value-seen point-value)
	   (setf lowest-value-point point))
	 (setf previous-tail tail)
	     finally
	       (let ((point-1 highest-value-point)
		     (point-2 lowest-value-point))
		 ;; ensure monotinicity of timestamps for painting
		 (when (>e (buffer-plot-point-time point-1)
			   (buffer-plot-point-time point-2))
		   (rotatef point-1 point-2))
		 (buffered-paint-connector start-point point-1)
		 (buffered-paint-connector point-1 point-2)
		 (buffered-paint-connector point-2 point)
		 (setf (cdr previous-tail) nil)
		 #+development
		 (when trace-buffered-painting-optimization-p
		   (format
		     t "  painting ~s connectors for 3 as low = ~S hi +~S~%"
		     (1-f (length plot-connector-painting-buffer-head))
		     (buffer-plot-point-value lowest-value-point)
		     (buffer-plot-point-value highest-value-point)))
		 (reclaim-gensym-tree plot-connector-painting-buffer-head)
		 (setf plot-connector-painting-buffer-head tail)
		 (setf plot-connector-painting-buffer-size (length tail))
		 (when (null tail)
		   (setf plot-connector-painting-buffer-tail nil)))))
      (t
       (buffered-paint-one-connector)))))

(defun-void flush-buffered-plot-painting ()
  #+development
  (when trace-buffered-plot-painting-p
    (format t "Flush start ~%")
    (loop for (time . value) in plot-connector-painting-buffer-head
	  do
      (format t "    ~s  at ~s~%"
	      value
	      (-time time (managed-float-value (clock-get g2-time-at-start))))))
  (when plot-connector-painting-buffer-head
    (loop while (cdr-of-cons plot-connector-painting-buffer-head)
	  do
      (buffered-paint-one-connector))
    (reclaim-gensym-cons (car-of-cons plot-connector-painting-buffer-head))
    (reclaim-gensym-cons plot-connector-painting-buffer-head))
  (when trace-buffered-plot-painting-p
    (Format t "Flush end ~%"))
  (setf plot-connector-painting-buffer-head nil)
  (setf plot-connector-painting-buffer-tail nil))




;;;; Drawing a trend-chart (state machine primitives)

(defun initialize-2d-state (trend-chart grid-pane)
  ;; returns t/nil to say whether the state can be initialized
  ;; find latest-time for all plots
  (with-temporary-gensym-float-creation initialize-2d-state
    (multiple-value-bind (grid-inner-width grid-inner-height)
	(get-grid-inner-dimensions grid-pane)
      (let* ((end-time
	       (fast-time-slot trend-chart trend-chart-end-time))
	     (grid-timespan
	       (fast-time-slot trend-chart trend-chart-timespan))
	     (grid-data-height (grid-data-height grid-pane))
	     (base-time (-time end-time grid-timespan)))
	
	(initialize-latest-event-times current-2d-state trend-chart)
	(setf (2d-state-grid-data-height current-2d-state) grid-data-height)
	(setf (2d-state-grid-height current-2d-state) grid-inner-height)
	(setf (2d-state-grid-width current-2d-state) grid-inner-width)
	(setf (2d-state-position-shift current-2d-state) 0)
	(setf (2d-state-virtual-origin-x current-2d-state) 0)
	(setf (2d-state-raster-width-to-right current-2d-state) grid-inner-width)

	(when (grid-tickmark-interval? grid-pane)
	  (mutate-time-slot
	    current-2d-state
	    2d-state-last-tickmark-time
	    (let* ((alignment
		     (*time (fast-time-slot grid-pane grid-tickmark-interval?)
			    (fixnum-to-time (grid-label-ratio grid-pane))))
		   (aligned-first-tickmark-time?
		     (compute-aligned-graph-time
		       alignment base-time alignment grid-timespan
		       (trend-chart-has-interval-time-labels-p trend-chart))))
	      (if aligned-first-tickmark-time?
		  (-time aligned-first-tickmark-time?
			 (fast-time-slot grid-pane grid-tickmark-interval?))
		  base-time)))
	  (setf (2d-state-label-counter current-2d-state)
		(1-f (grid-label-ratio grid-pane))))
	(mutate-time-slot current-2d-state 2d-state-base-time base-time)
	(mutate-time-slot current-2d-state 2d-state-grid-timespan grid-timespan)
	(mutate-time-slot current-2d-state 2d-state-end-time end-time)
	))))


(defmacro round-time-to-interval (seconds-to-round interval)
  `(*time ,interval
	  (floor-time ,seconds-to-round ,interval)))

(defun align-end-time-if-necessary
    (grid-pane end-time timespan timestamps-are-intervals-p)
  (cond
    ((grid-time-alignment? grid-pane)
     (let* ((alignment (fast-time-slot grid-pane grid-time-alignment?))
	    (aligned-time?
	      (compute-aligned-graph-time
		alignment end-time alignment timespan
		timestamps-are-intervals-p)))
       (cond (aligned-time?
	      (loop for aligned-end-time
		    = aligned-time?
			then (+time aligned-end-time alignment)
		    when (>=time aligned-end-time end-time)
		      return aligned-end-time))
	     (t
	      end-time))))
    (t
     end-time)))

;;; Replaced by the following code. - jpg 6/22/00
; (defun decode-time-interval (interval)
;   (let* ((time-in-seconds (absf (floore-first interval)))
; 	   (seconds (modf time-in-seconds 60))
; 	   (minutes (modf (floorf (-f time-in-seconds seconds) 60)
; 			  60))
; 	   (hours (modf (floorf (-f time-in-seconds
; 				    (+f seconds (*f 60 minutes)))
; 			        3600)
; 		        3600))  ;; This 3600 should be 24 . - jpg 6/22/00
; 	   (days (floorf (-f time-in-seconds
; 			     (+f seconds
; 			         (*f 60 minutes)
; 			         (*f 3600 hours)))
; 		         86400)))
;     (values seconds minutes hours days)))

(defun decode-dd-time-interval (interval)
  ;; Used by the dd-hh-mm-interval time-format.
  (let* ((time-in-seconds (absf (floore-first interval)))
	 (seconds (modf time-in-seconds 60))
	 (minutes (modf (floorf time-in-seconds 60) 60))
	 (hours (modf (floorf time-in-seconds 3600) 24))
	 (days (floorf time-in-seconds 86400)))
    (values seconds minutes hours days)))

(defun decode-hh-time-interval (interval)
  ;; Used by the hh...-interval time-formats.
  (let* ((time-in-seconds (absf (floore-first interval)))
	 (seconds (modf time-in-seconds 60))
	 (minutes (modf (floorf time-in-seconds 60) 60))
	 (hours (floorf time-in-seconds 3600)))
    (values seconds minutes hours)))

(defun decode-mm-time-interval (interval)
  ;; Used by the mm-ss-interval time-format.
  (let* ((time-in-seconds (absf (floore-first interval)))
	 (seconds (modf time-in-seconds 60))
	 (minutes (floorf time-in-seconds 60)))
    (values seconds minutes)))

(defun compute-aligned-graph-time (alignment
				    latest-possible-time
				    interval?
				    timespan
				    timestamps-are-intervals-p)
  (when (and (if interval? (<=time alignment interval?) t)
	     (<=time alignment timespan))
    (multiple-value-bind
	(seconds minutes hours) ; date)
	(if (not timestamps-are-intervals-p)
	    (gensym-decode-unix-time latest-possible-time)
	    (decode-hh-time-interval
	      (-e latest-possible-time
		  (managed-float-value (clock-get g2-time-at-start)))))
      (let ((seconds-ahead-of-aligned-time
	      (cond
		((<time alignment (fixnum-to-time 60))
		 ;; align to n seconds
		 (-time (fixnum-to-time seconds)
			(round-time-to-interval
			  (fixnum-to-time seconds)
			  alignment)))
		((<time alignment (fixnum-to-time 3600))
		 ;; align to n minutes
		 (let ((rounded-time
			 (round-time-to-interval
			   alignment
			   (fixnum-to-time 60)))
		       (unaligned-time-since-last-hour
			 (fixnum-to-time (+f seconds (*f minutes 60)))))
		   (-time unaligned-time-since-last-hour
			  (round-time-to-interval
			    unaligned-time-since-last-hour
			    rounded-time))))
		(t ; (<time alignment (fixnum-to-time 86400))
		 ;; align to n hours
		 (let ((rounded-time
			 (round-time-to-interval
			   alignment
			   (fixnum-to-time 3600)))
		       (unaligned-time-since-last-day
			 (fixnum-to-time (+f seconds
					     (*f minutes 60)
					     (*f hours 3600)))))
		   (-time unaligned-time-since-last-day
			  (round-time-to-interval
			    unaligned-time-since-last-day
			    rounded-time)))))))
	(-time latest-possible-time seconds-ahead-of-aligned-time)))))

(defun update-2d-state-for-scroll (trend-chart)
  (with-temporary-gensym-float-creation update-2d-state-for-scroll
    (let* ((new-end-time (fast-time-slot trend-chart
					 trend-chart-end-time))
	   (grid-width (2d-state-grid-width current-2d-state)) ; a fixnum
	   (new-end-position
	    (time-to-fixnum
	      (ceiling-time
		(*time (fixnum-to-time grid-width)
		       (-time new-end-time
			      (fast-time-slot current-2d-state 2d-state-base-time)))
		(fast-time-slot current-2d-state 2d-state-grid-timespan))))
	   (new-position-shift (-f new-end-position grid-width))
	   (old-position-shift (2d-state-position-shift
				 current-2d-state))
	   (position-offset (-f new-position-shift
				(2d-state-position-shift current-2d-state))))

      ;; eventually test for index overflows and set flags
      ;; so next recompute is full !!
      (setf (2d-state-position-shift current-2d-state) new-position-shift)
      (mutate-time-slot current-2d-state 2d-state-end-time new-end-time)

      ;; update virtual-origin for shift and grid-width
      (let* ((previous-virtual-origin-x (2d-state-virtual-origin-x current-2d-state))
	     (current-virtual-origin-x
	       (modf (+f previous-virtual-origin-x position-offset)
		     grid-width)))
	(setf (2d-state-virtual-origin-x current-2d-state) current-virtual-origin-x)
	(setf (2d-state-raster-width-to-right current-2d-state)
	      (-f grid-width current-virtual-origin-x))
	(clear-scrolling-region (+f (if (=f 0 old-position-shift)
				        0
					1)
				    previous-virtual-origin-x)
				(+f 1 current-virtual-origin-x))
	))))

(defun initialize-latest-event-times (2d-state trend-chart)
  (with-temporary-gensym-float-creation initialize-latest-event-times
    (loop with event-time-array = (2d-state-latest-event-times 2d-state)
	  for i from 0 below (trend-chart-plot-slot-count trend-chart)
	  as time? = (managed-svref event-time-array i)
	  do
      (cond (time?
	     (mutate-managed-float-value time? (most-negative-time)))
	    (t
	     (setf (managed-svref event-time-array i)
		   (allocate-managed-float (most-negative-time))))))))

(defun plot-end-time-established-p (trend-chart plot)
  (with-temporary-gensym-float-creation plot-end-time-established-p
    (/=time (most-negative-time)
	    (managed-float-aref
	      (trend-chart-plot-end-times trend-chart)
	      (plot-index plot)))))

(defun plot-has-data-to-paint-in-interval-p
    (plot trend-chart start-time end-time)
  (with-temporary-gensym-float-creation
      plot-has-data-to-paint-in-interval-p
    (let* ((time-width-of-plot
	     (fixnum-to-time (get-plot-width-as-time plot)))
	   (adjusted-start-time (-time start-time time-width-of-plot))
	   (history (plot-history plot))
	   (point-format 
	     (get-slot-component-group-by-reference
	       trend-chart plot 'plot-point-format))
	   (connector-format 
	     (get-slot-component-group-by-reference
	       trend-chart plot 'plot-connector-format))
	   (start-index
	     (generic-history-index history adjusted-start-time
				    'inclusive t))
	   (time-for-start-index
	     (generic-history-timestamp history start-index)))
      (cond
	((connector-visible? connector-format)
	 (cond ((point-visible? point-format)
		(<=time adjusted-start-time time-for-start-index))
	       (t
		(<=time start-time time-for-start-index))))
	((point-visible? point-format)
	 (<=time adjusted-start-time
		 time-for-start-index
		 end-time))
	(t
	 nil)))))
    
    
;;; If any data is in the history after the last index whose timestamp
;;; is less than plot end time.

(defun plot-has-new-data-to-paint-p (plot trend-chart 2d-state)
  (let* ((plot-index (plot-index plot))
	 (history (plot-history plot))
	 (latest-event-index
	   (managed-svref (2d-state-latest-event-indices 2d-state)
			  plot-index))
	 (end-index (generic-history-end-index history)))
    (cond
      ((and (plot-is-sample-and-hold-p plot)
	    (let* ((end-time
		     (frame-like-value-key
		       (end-time (trend-chart-time-axis trend-chart)))))
	      (or (eq end-time 'last-sample)
		  (eq end-time 'current-time))))
       t)
      ((=f latest-event-index end-index)
       nil) ; by monotonicity of history timestamps
      (t
       (with-temporary-gensym-float-creation plot-has-data-to-paint-p
	 (let ((plot-end-time
		 (managed-float-aref
		   (trend-chart-plot-end-times trend-chart)
		   plot-index)))
	   (<=time (generic-history-timestamp
		     history
		     (next-generic-history-index history latest-event-index))
		   plot-end-time)))))))


(defun any-points-painted-p (plot 2d-state)
  (let ((latest-event-time?
	  (managed-svref (2d-state-latest-event-times
			       2d-state)
			     (plot-index plot))))
    (and latest-event-time?
	 (with-temporary-gensym-float-creation any-points-painted-p
	   (/=time (managed-float-value
		     latest-event-time?)
		   (most-negative-time))))))

(defun update-2d-state-for-plot-point-painting (plot index? timestamp
						     &optional (update-plot-p t))
  (with-temporary-gensym-float-creation
      update-2d-state-for-plot-point-painting
    ;; update the dynamic variables that track earliest and latest points
    (mutate-managed-float-value
      current-grid-painting-earliest-time
      (mintime (managed-float-value current-grid-painting-earliest-time)
	       timestamp))
    (mutate-managed-float-value
      current-grid-painting-latest-time
      (maxtime (managed-float-value current-grid-painting-latest-time)
	       timestamp))
    (when update-plot-p
      (let ((latest-event-indices (2d-state-latest-event-indices
				    current-2d-state))
	    (latest-event-times (2d-state-latest-event-times
				  current-2d-state))
	    (plot-index (plot-index plot)))
	(when index?
	  (setf (managed-svref latest-event-indices plot-index) index?))
	(mutate-managed-float-value
	  (managed-svref latest-event-times plot-index)
	  timestamp)))))



;;;; Drawing a trend-chart (low-level painting)

;;; A grid-painting-function is supposed to the lowest level of grid painting.
;;; this layer goes directly on top of the paint functions of the windows
;;; module.  The grid painting functions take time and value args and use plot
;;; formats and the grid-painting and grid-geometry dynamic extents to figure
;;; actual locations and styles of plot lines and markers.  These functions make
;;; no decisions about what to plot.  They may get rewritten as the interface to
;;; painting rasters supports wrapping more easily.

(defmacro 2d-painting-color-value (plot-color-value)
  `(cond ((eq current-grid-painting-color-mode :monochrome)
	  (cond ((=f ,plot-color-value
		     current-grid-painting-foreground-color-value)
		 1)
		(t
		 0)))
	 (t
	  ,plot-color-value)))

(defmacro scale-x-for-grid-painting (x)
  `(delta-x-in-window ,x current-grid-painting-x-scale))

(defmacro scale-y-for-grid-painting (y)
  `(delta-y-in-window ,y current-grid-painting-y-scale))

(defun update-dateline ()
  (let ((rendering (2d-state-rendering current-2d-state)))
    (update-graph-dateline              ; from WINDOWS3.LISP
      (delta-x-in-window (2d-state-virtual-origin-x current-2d-state)
			 current-grid-painting-x-scale)
      (delta-x-in-window (2d-state-virtual-origin-x current-2d-state)
			 current-grid-painting-x-scale)
      rendering)))

;; Abstract positions are NOT raster or window coordinates
;; They are fixnums and get mod'ed to bring them into range
;; for the above.

(defun time-to-abstract-x (timestamp)
  ;; inherits temp float context from full/partial paint plot
  (time-to-fixnum
    (/time (*time (fixnum-to-time (2d-state-grid-width current-2d-state))
		  (-time timestamp
			 (fast-time-slot current-2d-state 2d-state-base-time)))
	   (fast-time-slot current-2d-state 2d-state-grid-timespan))))

(defmacro time-to-abstract-x-macro (timestamp)
  ;; inherits temp float context from full/partial paint plot
  `(time-to-fixnum
    (/time (*time (fixnum-to-time (2d-state-grid-width current-2d-state))
		  (-time ,timestamp
			 (fast-time-slot current-2d-state 2d-state-base-time)))
	   (fast-time-slot current-2d-state 2d-state-grid-timespan))))

(defmacro abstract-x-start-to-unscaled-ring-raster-macro (x)
  `(let ((logical-pos-on-ring-raster (-f ,x (2d-state-position-shift current-2d-state))))
    (cond ((>=f logical-pos-on-ring-raster
		(2d-state-raster-width-to-right current-2d-state))
	   (-f logical-pos-on-ring-raster
	       (2d-state-raster-width-to-right current-2d-state)))
	  (t
	   (+f (2d-state-virtual-origin-x current-2d-state) ; 12/9/93 Wow!
	       logical-pos-on-ring-raster)))))

(defmacro abstract-x-end-to-unscaled-ring-raster-macro (x)
  `(let ((logical-pos-on-ring-raster (-f ,x (2d-state-position-shift current-2d-state))))
    (cond ((>f logical-pos-on-ring-raster
		(2d-state-raster-width-to-right current-2d-state))
	   (-f logical-pos-on-ring-raster
	       (2d-state-raster-width-to-right current-2d-state)))
	  (t
	   (+f (2d-state-virtual-origin-x current-2d-state) ; 2/7/93 Wow!
	       logical-pos-on-ring-raster)))))
;	   logical-pos-on-ring-raster))))

(defun abstract-x-start-to-unscaled-ring-raster (x)
  (abstract-x-start-to-unscaled-ring-raster-macro x))

(defun abstract-x-end-to-unscaled-ring-raster (x)
  (abstract-x-end-to-unscaled-ring-raster-macro x))

(defun compute-grid-y (value plot-index plot-minima plot-maxima range-mode
			     axis?)
  ;; inherits temp float context from paint-plot-data
  (declare (ignore range-mode))
  (let ((high-value (if axis?
			(fast-value-slot axis? value-axis-high-value)
			(managed-float-aref plot-maxima plot-index)))
	(low-value (if axis?
		       (fast-value-slot axis? value-axis-low-value)
		       (managed-float-aref plot-minima plot-index))))
    (cond ((=value high-value low-value)
	   (floorf (2d-state-grid-data-height current-2d-state) 2))
	  (t
	   (value-to-fixnum
	     (floor-value
	       (*value (-value high-value value)
		       (fixnum-to-value (2d-state-grid-data-height current-2d-state)))
	       (-value high-value low-value)))))))


(defparameter maximum-plot-marker-size 25)

(defparameter last-point-value nil)

(defun paint-plot-point (plot axis value timestamp point-format?
			      history)
  (let* ((plot-index (plot-index plot))
	 (latest-index-for-plot
	   (managed-svref (2d-state-latest-event-indices
			    current-2d-state)
			  plot-index)))
    (setq last-point-value value)
    (when (and point-format?
	       (point-visible? point-format?)
	       (let* ((frequency-spec (point-frequency point-format?))
		      (frequency-type (frame-like-value-key frequency-spec)))
		 (cond 
		   ((and latest-index-for-plot
			 (eq frequency-type 'ratio))
		    (=f 0 (modf (map-relative-to-absolute-history-index
				  history
				  latest-index-for-plot)
				(frame-like-value-property frequency-spec
							   'number))))
		   (t
		    nil))))
      (let ((shape-spec (point-style point-format?))
	    (marker-size default-point-marker-size)
	    (logical-color-value
	      (trend-chart-color-value
		(point-color point-format?) foreground)))
	(case (frame-like-value-key shape-spec)
	  (custom
	   (let* ((icon-class (frame-like-value-property shape-spec
							 'icon-class))
		  (icon-description?
		   (and (classp icon-class)
			(get-icon-description-given-class icon-class))))
	     (when icon-description? ; frame note is present if this is nil
	       (paint-icon-as-plot-marker plot axis value timestamp
					  icon-class icon-description?
					  logical-color-value))))
	  (standard
	   (case (frame-like-value-property shape-spec 'shape)
	     (current-value
	      (paint-string-as-plot-marker
		plot axis
		(twith-output-to-text-string
		  (twrite value))
		value timestamp
		logical-color-value))
	     (triangle
	      (paint-triangle-as-plot-marker plot axis value timestamp
					     marker-size logical-color-value))
	     (plus-sign
	      (paint-plus-sign-as-plot-marker plot axis value timestamp
					      marker-size logical-color-value))
	     (square
	      (paint-square-as-plot-marker plot axis value timestamp
					   marker-size logical-color-value))))
	  (otherwise nil))))))

(defun paint-triangle-as-plot-marker (plot axis value timestamp
					   marker-size logical-color-value)
  (let* ((plot-minima (trend-chart-plot-minima current-trend-chart))
	 (plot-maxima (trend-chart-plot-maxima current-trend-chart))
	 (range-mode (verified-value-axis-range-mode axis))
	 (half-triangle-width marker-size)
	 (slice-height 1)
	 (abstract-x (time-to-abstract-x timestamp)) ; unshifted & unscaled
	 (unscaled-y (compute-grid-y value (plot-index plot)
				     plot-minima plot-maxima
				     range-mode axis)))
    (loop for y from (-f unscaled-y half-triangle-width)
	        below (+f unscaled-y half-triangle-width)
		by slice-height
	  as width from slice-height by slice-height
	  do
             (paint-solid-rectangle-on-graph
	       default-grid-element-priority
	       (-f abstract-x (floorf width 2))
	       y
	       (+f abstract-x (ceilingf width 2))
	       (+f y slice-height)
	       logical-color-value))))

(defun paint-plus-sign-as-plot-marker (plot axis value timestamp
					   marker-size logical-color-value)
  (let* ((plot-minima (trend-chart-plot-minima current-trend-chart))
	 (plot-maxima (trend-chart-plot-maxima current-trend-chart))
	 (range-mode (verified-value-axis-range-mode axis))
	 (quarter-square-width 1)
	 (half-square-width marker-size)
	 (abstract-x (time-to-abstract-x timestamp)) ; unshifted & unscaled
	 (unscaled-y (compute-grid-y value (plot-index plot)
				     plot-minima plot-maxima
				     range-mode axis)))
    ;; should do y-clipping here
    ;; the wide one
    (paint-solid-rectangle-on-graph default-grid-element-priority
				    (-f abstract-x half-square-width)
				    (-f unscaled-y quarter-square-width)
				    (+f abstract-x half-square-width)
				    (+f unscaled-y quarter-square-width 1)
				    logical-color-value)
    ;; the tall one
    (paint-solid-rectangle-on-graph default-grid-element-priority
				    (-f abstract-x quarter-square-width)
				    (-f unscaled-y half-square-width)
				    (+f abstract-x quarter-square-width 1)
				    (+f unscaled-y half-square-width)
				    logical-color-value)))

(defun paint-square-as-plot-marker (plot axis value timestamp
					   marker-size logical-color-value)
  (let* ((plot-minima (trend-chart-plot-minima current-trend-chart))
	 (plot-maxima (trend-chart-plot-maxima current-trend-chart))
	 (range-mode (verified-value-axis-range-mode axis))
	 (half-square-width marker-size)
	 (abstract-x (time-to-abstract-x timestamp)) ; unshifted & unscaled
	 (unscaled-y (compute-grid-y value (plot-index plot)
				     plot-minima plot-maxima
				     range-mode axis)))
    ;; should do y-clipping here
    (paint-solid-rectangle-on-graph default-grid-element-priority
				    (-f abstract-x half-square-width)
				    (-f unscaled-y half-square-width)
				    (+f abstract-x half-square-width)
				    (+f unscaled-y half-square-width)
				    logical-color-value)))

#+development 
(defun create-circle-table ()
  (loop with circle-specs = ()
        for diameter from 1 to maximum-plot-marker-size
	do
    circle-specs
    (loop with rect-specs = ()
          for i from 1 to diameter
	  do
      nil
      finally (return
		rect-specs)
      )))
	  

(defun graph-text-width (text-string text-box-format start? end?)
  (let ((font-map (text-cell-font-map text-box-format))
	(word-spacing (default-word-spacing text-box-format)))
    (compute-width-of-text-line text-string start? end? font-map word-spacing)))

(defun paint-string-as-plot-marker (plot axis string
					 value timestamp
					 logical-color-value)
  (let* ((plot-minima (trend-chart-plot-minima current-trend-chart))
	 (plot-maxima (trend-chart-plot-maxima current-trend-chart))
	 (range-mode (verified-value-axis-range-mode axis))
	 (abstract-x (time-to-abstract-x timestamp)) ; unshifted & unscaled
	 (unscaled-y (compute-grid-y value (plot-index plot)
				     plot-minima plot-maxima
				     range-mode axis))
	 (grid-data-height (2d-state-grid-data-height current-2d-state))
	 (text-box-format (get-or-make-format-frame
			    '2d-time-axis-label-format))
	 (text-height (text-cell-line-height text-box-format))
	 (text-width  (graph-text-width string text-box-format nil nil))
	 (abstract-left (-f abstract-x (halff text-width)))
	 (abstract-top (-f unscaled-y (halff text-height))))
    (paint-string-on-graph default-grid-element-priority
			   string text-box-format
			   abstract-left
			   abstract-top
			   (+f abstract-left text-width)
			   (minw (+f abstract-top text-height)
				 grid-data-height)
			   logical-color-value)))

(defun paint-time-tickmark (time-of-new-tickmark grid-pane)
  (let* ((abstract-x (time-to-abstract-x time-of-new-tickmark))
	 (unscaled-y (+f (grid-data-height grid-pane)
			 (grid-separator-height grid-pane)
			 (halff (grid-label-height grid-pane))))
	 (time-axis (trend-chart-time-axis current-trend-chart))
	 (time-string (tformat-graph-time
			time-of-new-tickmark time-axis))
	 (text-box-format (get-or-make-format-frame
			    '2d-time-axis-label-format))
	 (text-height (text-cell-line-height text-box-format))
	 (text-width  (graph-text-width time-string text-box-format nil nil))
	 (abstract-top (-f unscaled-y (halff text-height)))
	 (abstract-left
	   (case (time-axis-label-alignment time-axis)
	     (left
	      abstract-x)
	     (center
	      (-f abstract-x (halff text-width)))
	     (right
	      (-f abstract-x text-width)))))
    (paint-string-on-graph default-grid-element-priority
			   time-string text-box-format
			   abstract-left
			   abstract-top
			   (+f abstract-left text-width)
			   (+f abstract-top text-height)
			   (trend-chart-color-value
			     (grid-time-label-color grid-pane)
			     foreground))))

(defvar graph-month-strings
  '#("Jan" "Feb" "Mar" "Apr" "May" "Jun"
     "Jul" "Aug" "Sep" "Oct" "Nov" "Dec"))

(defmacro convert-to-12-hour (hour)
  `(let ((rem (modf ,hour 12)))
     (if (=f rem 0)
	 12
	 rem)))

(defun trend-chart-has-interval-time-labels-p (trend-chart)
  (memq (time-axis-label-format (trend-chart-time-axis trend-chart))
	'(hh-mm-ss-interval hh-mm-interval mm-ss-interval
	  dd-hh-mm-interval hh.hh-interval)))

(defun tformat-graph-time (time-of-new-tickmark time-axis)
  (let ((negative-p nil)
	(label-format (time-axis-label-format time-axis))
	(year-mod-100 nil))
    (multiple-value-bind
	(seconds minutes hours date month year)
	(if (memq-p-macro label-format
			  '(hh-mm-ss-interval hh-mm-interval mm-ss-interval
			    dd-hh-mm-interval hh.hh-interval))
	    (let ((diff (-e time-of-new-tickmark
			    (managed-float-value (clock-get g2-time-at-start)))))
	      (when (<e diff 0.0)
		(setq negative-p t))
	      (case label-format
		(dd-hh-mm-interval
		 (decode-dd-time-interval diff))
		((hh-mm-ss-interval hh-mm-interval hh.hh-interval)
		 (decode-hh-time-interval diff))
		(mm-ss-interval
		 (decode-mm-time-interval diff))))
	    (gensym-decode-unix-time time-of-new-tickmark))
      (when year
	(setf year-mod-100 (modf year 100)))
      (twith-output-to-text-string
	(case label-format
	  ((hh-mm-ss-interval hh-mm-ss)
	   (when negative-p
	     (tformat "-"))
	   (tformat "~d:~a~d:~a~d"
		    hours 
		    (if (<f minutes 10) "0" "")
		    minutes
		    (if (<f seconds 10) "0" "")
		    seconds))
	  (hh-mm-ss-am-pm
	   (tformat "~d:~a~d:~a~d ~a"
		    (convert-to-12-hour hours)
		    (if (<f minutes 10) "0" "")
		    minutes
		    (if (<f seconds 10) "0" "")
		    seconds
		    (if (>=f hours 12) "p.m." "a.m.")))
	  ((hh-mm hh-mm-interval)
	   (when negative-p
	     (tformat "-"))
	   (tformat "~d:~a~d"
		    hours
		    (if (<f minutes 10) "0" "")
		    minutes))
	  (hh-mm-am-pm
	   (tformat "~d:~a~d ~a"
		    (convert-to-12-hour hours)
		    (if (<f minutes 10) "0" "")
		    minutes
		    (if (>=f hours 12) "p.m." "a.m.")))
	  ((mm-ss mm-ss-interval)
	   (tformat "~a~d:~a~d"
		    (if (<f minutes 10) "0" "")
		    minutes
		    (if (<f seconds 10) "0" "")
		    seconds))
	  (mmm-dd-hh-mm
	   (tformat "~a ~d ~d:~a~d"
		    (aref graph-month-strings (1-f month))
		    date
		    hours
		    (if (<f minutes 10) "0" "")
		    minutes))
	  (dd-hh-mm-interval
	   (when negative-p
	     (tformat "-"))
	   (tformat "~d ~d:~a~d"
		    date
		    hours
		    (if (<f minutes 10) "0" "")
		    minutes))
	  (mm/dd-hh-mm
	   (tformat "~d/~d ~d:~a~d"
		    month
		    date
		    hours
		    (if (<f minutes 10) "0" "")
		    minutes))
	  (mm-yy
	   (tformat "~d/~a~d"
		    month
		    (if (<f year-mod-100 10) "0" "")
		    year-mod-100))
	  (mm-dd-yy
	   (tformat "~d/~d/~a~d"
		    month
		    date
		    (if (<f year-mod-100 10) "0" "")
		    year-mod-100))
	  (yy-mm-dd
	   (tformat "~a~d/~d/~d"
		    (if (<f year-mod-100 10) "0" "")
		    year-mod-100
		    month
		    date))
	  (dd-mm-yy
	    (tformat "~d/~d/~a~d"
		     date
		     month
		     (if (<f year-mod-100 10) "0" "")
		     year-mod-100))
	  (dd-mmm-yyyy
	   (tformat "~d ~a ~d"
		    date
		    (aref graph-month-strings (1-f month))
		    year))
	  (mmm-dd-yyyy
	   (tformat "~d ~a ~d"
		    (aref graph-month-strings (1-f month))
		    date
		    year))
	  (mmm-yyyy
	   (tformat "~a ~d"
		    (aref graph-month-strings (1-f month))
		    year))
	  (hh.hh-interval 
	   (hh-mm-to-hh.hh-conversion hours minutes negative-p))
	  )))))

(defun get-maximum-width-for-time-label (time-label-format text-box-format)
  (let* ((ab-font-or-name (or (first (text-cell-font-map text-box-format))
			      #+development
			      (cerror "" "where the hell is the font")
			      'hm14))
	 (ab-font (if (symbolp ab-font-or-name)
		      (ab-font ab-font-or-name)
		      ab-font-or-name))
	 (digit-width (font-digit-text-width ab-font))
	 (colon-width (get-set-width-for-character #\: ab-font))
	 (slash-width (get-set-width-for-character #\/ ab-font))
      ;; (dash-width (get-set-width-for-character #\- ab-font))
	 ;; dash-width is no longer needed because of the extra space now 
	 ;; allowed for extra digits for positive time intervals. - jpg 6/23/00
	 (period-width (get-set-width-for-character #\. ab-font))
	 (space-width (get-set-width-for-character #\Space ab-font))
	 (capital-m-width (get-set-width-for-character #\M ab-font))
	 (month-width (*f 3 capital-m-width)))
    (+f
      (twicef graph-minimum-text-spacing)
      (text-width-to-x
	(case time-label-format
	  (hh-mm-ss
	   (+f (*f 2 colon-width) (*f 6 digit-width)))
	  (hh-mm-ss-interval
	   ;; Allows ddddd:dd:dd .
	   (+f (*f 2 colon-width) (*f 9 digit-width)))
	  (hh-mm-ss-am-pm
	   (+f (*f 2 colon-width) (*f 2 period-width) (*f 6 digit-width)
	       space-width (*f 2 capital-m-width)))
	  ((hh-mm mm-ss)
	   (+f colon-width (*f 4 digit-width)))
	  (hh-mm-interval 
	   ;; Allows ddddd:dd .
	   (+f colon-width (*f 7 digit-width)))
	  (mm-ss-interval 
	   ;; Allows ddddddd:dd
	   (+f colon-width (*f 9 digit-width)))
	  (hh-mm-am-pm
	   (+f colon-width (*f 4 digit-width) (*f 2 period-width)
	       space-width (*f 2 capital-m-width)))
	  (mmm-dd-hh-mm 
	   (+f month-width (*f 2 space-width) colon-width (*f 4 digit-width)))
	  (mm/dd-hh-mm
	   (+f (*f 8 digit-width) slash-width space-width colon-width))
	  ((dd-hh-mm-interval days-hh-mm)
	   ;; Allows dddd dd:dd .
	   (+f (* 8 digit-width) colon-width space-width))
	  (mm-yy 
	   (+f (* 4 digit-width) slash-width))
	  ((mm-dd-yy yy-mm-dd dd-mm-yy)
	   (+f (* 6 digit-width) (*f 2 slash-width)))
	  ((dd-mmm-yyyy mmm-dd-yyyy)
	   (+f month-width (*f 6 digit-width) (*f 2 space-width)))
	  (mmm-yyyy 
	   (+f month-width (*f 4 digit-width) (*f 2 space-width)))
	  (hh.hh-interval
	   ;; Allows ddddd.ddh, where d = a digit, h = h
	   (+f period-width (*f 7 digit-width) capital-m-width))
	  (otherwise 0))))))
  
(defun paint-time-grid-lines (time-of-tickmark
			       interval-length
			       extension)
  (let* ((time-axis (trend-chart-time-axis current-trend-chart))
	 (grid-line-ratio
	   (if (time-grid-lines-visible? time-axis)
	       (ratio-of-grid-lines-to-time-axis-tickmarks time-axis)
	       0))
	 (logical-color-value
	   (trend-chart-color-value
	     (color-for-time-grid-lines time-axis)
	     foreground)))
    (loop for i from 0 below grid-line-ratio
	  do
      (let* ((time (+time time-of-tickmark
			  (/time (*time interval-length
					(fixnum-to-time i))
				 (fixnum-to-time grid-line-ratio))))
	     (abstract-x (time-to-abstract-x time)))
	(paint-grid-line-at-time
	  time-grid-line-priority
	  abstract-x
	  logical-color-value
	  (if (=f i 0) extension 0))))))
 
(define-suspendable-painting-action paint-grid-line-at-time
    ((abstract-x fixnum)
     (logical-color-value fixnum)
     (extension fixnum))
  (let* ((grid-start (2d-state-position-shift current-2d-state))
	 (grid-end (+r grid-start
		       (2d-state-grid-width current-2d-state))))
    ;; grid start and end are inclusive and exclusive resp.
    (cond ((<f abstract-x grid-start)
	   t)
	  ((<f abstract-x grid-end)
	   (let ((ring-raster-x (abstract-x-start-to-unscaled-ring-raster
				  abstract-x)))
	     (primitive-line-in-rendering
	       (scale-x-for-grid-painting ring-raster-x)
	       (scale-y-for-grid-painting 0)
	       (scale-x-for-grid-painting ring-raster-x)
	       (scale-y-for-grid-painting
		 (+w (2d-state-grid-data-height
		       current-2d-state)
		     extension))
	       logical-color-value))
	   t)
	  (t
	   nil))))

(define-suspendable-painting-action paint-string-on-graph
    ((text string)
     (text-box-format format-frame)
     (abstract-left fixnum)
     (abstract-top fixnum)
     (abstract-right fixnum)
     (abstract-bottom fixnum)
     (logical-color-value fixnum))
  (let* ((grid-start (2d-state-position-shift current-2d-state))
	 (grid-end (+r grid-start
		       (2d-state-grid-width current-2d-state)))
	 (rightmost-point-painted? (current-painting-action-state)))
    (cond ((<f abstract-right grid-start) ; grid is past this point
	   t)
	  ((<f grid-end abstract-left)
	   nil) ; haven't gotten to this point yet
	  (t
	   (let ((completing-this-time-p (>f grid-end abstract-right))
		 (left-bound (maxr abstract-left
				   grid-start
				   (or rightmost-point-painted? -1)))
		 (right-bound (minr abstract-right grid-end))
		 (baseline (text-cell-baseline-position
			     text-box-format)))
	     (when (if rightmost-point-painted?
		        (>f right-bound rightmost-point-painted?)
			t)
	       (paint-text-from-abstract-coordinates
		 left-bound abstract-top right-bound abstract-bottom
		 text text-box-format
		 abstract-left (+f abstract-top baseline)
		 logical-color-value))
	     (cond (completing-this-time-p
		    t)
		   (t
		    (setf (current-painting-action-state) right-bound)
		    nil)))))))
#+development
(defvar drawing-text-for-2d nil)

(defun paint-text-from-abstract-coordinates
    (abstract-clip-left abstract-clip-top
     abstract-clip-right abstract-clip-bottom
     text text-box-format
     abstract-box-left abstract-box-baseline
     logical-color-value)
  (let ((ring-raster-left
	  (abstract-x-start-to-unscaled-ring-raster abstract-clip-left))
	(ring-raster-right
	  (abstract-x-end-to-unscaled-ring-raster abstract-clip-right))
	(abstract-width-of-printed-portion
	  (-f abstract-clip-left abstract-box-left))
	(grid-width (2d-state-grid-width current-2d-state))) 
    (cond
      ((>r ring-raster-left ring-raster-right)
       (primitive-text-in-rendering
	 text text-box-format
	 (scale-x-for-grid-painting ring-raster-left)
	 (scale-y-for-grid-painting abstract-clip-top)
	 (scale-x-for-grid-painting grid-width)
	 (scale-y-for-grid-painting abstract-clip-bottom)
	 (scale-x-for-grid-painting (- ring-raster-left
				       abstract-width-of-printed-portion))
	 (scale-y-for-grid-painting abstract-box-baseline)
	 logical-color-value)
       (primitive-text-in-rendering
	 text text-box-format
	 (scale-x-for-grid-painting 0)
	 (scale-y-for-grid-painting abstract-clip-top)
	 (scale-x-for-grid-painting ring-raster-right)
	 (scale-y-for-grid-painting abstract-clip-bottom)
	 (scale-x-for-grid-painting (-f ring-raster-left
					(+f abstract-width-of-printed-portion
					    grid-width))) ; Wow
	 (scale-y-for-grid-painting abstract-box-baseline)
	 logical-color-value))
      ((>f abstract-clip-right abstract-clip-left)
       (primitive-text-in-rendering
	 text text-box-format
	 (scale-x-for-grid-painting ring-raster-left)
	 (scale-y-for-grid-painting abstract-clip-top)
	 (scale-x-for-grid-painting ring-raster-right)
	 (scale-y-for-grid-painting abstract-clip-bottom)
	 (scale-x-for-grid-painting (-f ring-raster-left
					abstract-width-of-printed-portion))
	 (scale-y-for-grid-painting abstract-box-baseline)
	 logical-color-value)))))

(defun paint-value-grid-line (priority axis value logical-color-value disallowed-y?)
  (let* ((range-mode (verified-value-axis-range-mode axis)))
    (when (<=value (fast-value-slot axis value-axis-low-value)
		   value
		   (fast-value-slot axis value-axis-high-value))
      (let ((unscaled-y
	     (compute-grid-y value nil nil nil range-mode axis)))
	(when (and (or (null disallowed-y?)
		       (/=f unscaled-y disallowed-y?))
		   (<=f unscaled-y
			(2d-state-grid-data-height current-2d-state))
		   (>= unscaled-y 0))
	  (paint-long-line-on-graph
	    priority
	    unscaled-y
	    most-positive-fixnum
	    logical-color-value))))))

(define-suspendable-painting-action paint-long-line-on-graph
    ((unscaled-y fixnum)
     (abstract-right fixnum)
     (logical-color-value fixnum))
  (let* ((grid-start (2d-state-position-shift current-2d-state))
	 (grid-end (+r grid-start
		       (2d-state-grid-width current-2d-state)))
	 (rightmost-point-painted? (current-painting-action-state)))
    (let ((left-bound (maxr grid-start
			    (or rightmost-point-painted? -1)))
	  (right-bound (minr abstract-right grid-end)))
      (when (<f left-bound right-bound)
	;; paint some thing
	(paint-horizontal-line-from-abstract-coordinates 
	  left-bound unscaled-y right-bound logical-color-value)
	(setf (current-painting-action-state) right-bound)))
    nil))

(define-suspendable-painting-action paint-solid-rectangle-on-graph
    ((abstract-left fixnum)
     (abstract-top fixnum)
     (abstract-right fixnum)
     (abstract-bottom fixnum)
     (logical-color-value fixnum))
  (let* ((grid-start (2d-state-position-shift current-2d-state))
	 (grid-data-height (2d-state-grid-data-height current-2d-state))
	 (grid-end (+r grid-start
		       (2d-state-grid-width current-2d-state)))
	 (rightmost-point-painted? (current-painting-action-state)))
    ;; the following will never end if grid-start doesn't change
    ;; and grid-end == abstract-right
    (cond ((<f abstract-right grid-start) ; grid is past this point
	   t)
	  ((<f grid-end abstract-left)
	   nil) ; has not come on screen yet
	  (t
	   (let ((completing-this-time-p (>f grid-end abstract-right))
		 (left-bound (maxr abstract-left
				   grid-start
				   (or rightmost-point-painted? -1)))
		 (right-bound (minr abstract-right grid-end)))
	     (unless (or (<w abstract-bottom 0)
			 (>w abstract-top grid-data-height))
	       (paint-rectangle-from-abstract-coordinates
		 left-bound
		 (maxw abstract-top 0)
		 right-bound
		 (minr abstract-bottom grid-data-height)
		 logical-color-value))
	     (cond (completing-this-time-p
		    t)
		   (t
		    (setf (current-painting-action-state) right-bound)
		    nil)))))))
	   
(defun paint-icon-as-plot-marker (plot axis value timestamp
				       icon-class icon-description
				       logical-color-value)
  (let* ((plot-minima (trend-chart-plot-minima current-trend-chart))
	 (plot-maxima (trend-chart-plot-maxima current-trend-chart))
	 (range-mode (verified-value-axis-range-mode axis))
	 (abstract-x (time-to-abstract-x timestamp)) ; unshifted & unscaled
	 (unscaled-y (compute-grid-y value (plot-index plot)
				     plot-minima plot-maxima
				     range-mode axis)))
    (cond
      ((not (single-color-icon-description-p icon-description))
       )
      (t
       (let* ((icon-width (width-of-icon icon-description))
	      (icon-height (height-of-icon icon-description))
	      (abstract-left (-w abstract-x (halfw icon-width)))
	      (abstract-top (-w unscaled-y (halfw icon-height))))
	 (paint-icon-on-graph
	   default-grid-element-priority
	   icon-class
	   abstract-left
	   abstract-top
	   (+w abstract-left icon-width)
	   (+w abstract-top icon-height)
	   logical-color-value))))))

(define-suspendable-painting-action paint-icon-on-graph
    ((icon-class t)
     (abstract-left fixnum)
     (abstract-top fixnum)
     (abstract-right fixnum)
     (abstract-bottom fixnum)
     (logical-color-value fixnum))
  (let* ((icon-description
	   (and (classp icon-class)
		(get-icon-description-given-class icon-class)))
	 (grid-start (2d-state-position-shift current-2d-state))
	 (grid-data-height (2d-state-grid-data-height current-2d-state))
	 (grid-end (+r grid-start
		       (2d-state-grid-width current-2d-state)))
	 (rightmost-point-painted? (current-painting-action-state)))
    (cond
      ((not (icon-description-p icon-description))
       (format t "TC painting =~S~%" icon-description))
      (t
       ;; the following will never end if grid-start doesn't change
       ;; and grid-end == abstract-right
       (cond ((<f abstract-right grid-start) ; grid is past this point
	      t)
	     ((<f grid-end abstract-left)
	      nil) ; has not come on screen yet
	     (t
	      (let ((completing-this-time-p (>f grid-end abstract-right))
		    (left-bound (maxr abstract-left
				      grid-start
				      (or rightmost-point-painted? -1)))
		    (right-bound (minr abstract-right grid-end)))
		(unless (or (<w abstract-bottom 0)
			    (>w abstract-top grid-data-height))
		  (paint-icon-from-abstract-coordinates
		    icon-description
		    left-bound
		    (maxw abstract-top 0)
		    right-bound
		    (minr abstract-bottom grid-data-height)
		    abstract-left abstract-top
		    logical-color-value))
		(cond (completing-this-time-p
		       t)
		      (t
		       (setf (current-painting-action-state) right-bound)
		       nil)))))))))

(defun paint-icon-from-abstract-coordinates
    (icon-description
     clip-left clip-top clip-right clip-bottom
     abstract-left abstract-top
     logical-color-value)
  (let ((icon-rendering
	  (let ((current-image-x-scale current-grid-painting-x-scale)
		(current-image-y-scale current-grid-painting-y-scale))
	    (get-or-make-icon-rendering icon-description nil)))
	(ring-raster-left
	  (abstract-x-start-to-unscaled-ring-raster clip-left))
	(ring-raster-right
	  (abstract-x-end-to-unscaled-ring-raster clip-right))
	(abstract-width-of-blitted-portion
	  (-f clip-left abstract-left))
	(grid-width (2d-state-grid-width current-2d-state)))
    (cond
      ((>r ring-raster-left ring-raster-right)
       (primitive-icon-in-rendering
	 icon-rendering
	 (scale-x-for-grid-painting ring-raster-left)
	 (scale-y-for-grid-painting clip-top)
	 (scale-x-for-grid-painting grid-width)
	 (scale-y-for-grid-painting clip-bottom)
	 (scale-x-for-grid-painting (- ring-raster-left
				       abstract-width-of-blitted-portion))
	 (scale-y-for-grid-painting abstract-top)
	 logical-color-value)
       (primitive-icon-in-rendering
	 icon-rendering
	 (scale-x-for-grid-painting 0)
	 (scale-y-for-grid-painting clip-top)
	 (scale-x-for-grid-painting ring-raster-right)
	 (scale-y-for-grid-painting clip-bottom)
	 (scale-x-for-grid-painting (-f ring-raster-left grid-width)) ; Wow
	 (scale-y-for-grid-painting abstract-top)
	 logical-color-value))
      ((>f clip-right clip-left)
       (primitive-icon-in-rendering
	 icon-rendering
	 (scale-x-for-grid-painting ring-raster-left)
	 (scale-y-for-grid-painting clip-top)
	 (scale-x-for-grid-painting ring-raster-right)
	 (scale-y-for-grid-painting clip-bottom)
	 (scale-x-for-grid-painting (-f ring-raster-left
					abstract-width-of-blitted-portion))
	 (scale-y-for-grid-painting abstract-top)
	 logical-color-value)))))

(define-grid-painting-function primitive-icon-in-rendering
    (icon-rendering
      clip-left clip-top clip-right clip-bottom
      origin-left origin-top
      logical-color-value)
  (when (window-supports-paint-icon-onto-graph-raster current-window)
    ;; 4.0 Beta Phase 2 ICP message -- not handled by Beta Phase 1 or earlier
    ;; Telewindows.  (MHD 2/5/95)
    (paint-icon-onto-graph-raster
      icon-rendering
      clip-left clip-top clip-right clip-bottom
      origin-left origin-top
      (2d-painting-color-value logical-color-value))))


(defun paint-horizontal-line-from-abstract-coordinates 
    (abstract-left unscaled-y abstract-right logical-color-value)
  (let ((ring-raster-left
	  (abstract-x-start-to-unscaled-ring-raster abstract-left))
	(ring-raster-right
	  (abstract-x-end-to-unscaled-ring-raster abstract-right))
	(grid-width (2d-state-grid-width current-2d-state)))
    (cond
      ((>r ring-raster-left ring-raster-right)
       (primitive-line-in-rendering
	 (scale-x-for-grid-painting ring-raster-left)
	 (scale-y-for-grid-painting unscaled-y)
	 (scale-x-for-grid-painting grid-width)
	 (scale-y-for-grid-painting unscaled-y)
	 logical-color-value)
       (primitive-line-in-rendering
	 (scale-x-for-grid-painting 0)
	 (scale-y-for-grid-painting unscaled-y)
	 (scale-x-for-grid-painting ring-raster-right)
	 (scale-y-for-grid-painting unscaled-y)
	 logical-color-value))
      (t
       (primitive-line-in-rendering
	 (scale-x-for-grid-painting ring-raster-left)
	 (scale-y-for-grid-painting unscaled-y)
	 (scale-x-for-grid-painting ring-raster-right)
	 (scale-y-for-grid-painting unscaled-y)
	 logical-color-value)))))
       

(defun paint-rectangle-from-abstract-coordinates
    (abstract-left unscaled-top abstract-right unscaled-bottom
		   logical-color-value)
  (let ((ring-raster-left
	  (abstract-x-start-to-unscaled-ring-raster abstract-left))
	(ring-raster-right
	  (abstract-x-end-to-unscaled-ring-raster abstract-right))
	(grid-width (2d-state-grid-width current-2d-state)))
    (cond
      ((>r ring-raster-left ring-raster-right)
       (primitive-rectangle-in-rendering
	 (scale-x-for-grid-painting ring-raster-left)
	 (scale-y-for-grid-painting unscaled-top)
	 (scale-x-for-grid-painting grid-width)
	 (scale-y-for-grid-painting unscaled-bottom)
	 logical-color-value)
       (primitive-rectangle-in-rendering
	 (scale-x-for-grid-painting 0)
	 (scale-y-for-grid-painting unscaled-top)
	 (scale-x-for-grid-painting ring-raster-right)
	 (scale-y-for-grid-painting unscaled-bottom)
	 logical-color-value))
      (t
       (cond
	 ((and (=f ring-raster-right grid-width)
	       (=f ring-raster-left 0))
	  )
	 (t
	  (primitive-rectangle-in-rendering
	    (scale-x-for-grid-painting ring-raster-left)
	    (scale-y-for-grid-painting unscaled-top)
	    (scale-x-for-grid-painting ring-raster-right)
	    (scale-y-for-grid-painting unscaled-bottom)
	    logical-color-value)))))))

(defun-void paint-plot-connector (plot axis value1 timestamp1 value2 timestamp2
				  connector-color line-style style-arg)
  #+development
  (when (and trace-trend-chart-painting
	     (not (eq current-grid-painting-mode :multiple-pass-subsequent)))
    (format t "PAINT PC: (~s ~s ~s ~s) vo=~d rwtr=~d base=~d shift=~d~%"
	  value1 (-time timestamp1 (managed-float-value (clock-get g2-time-at-start)))
	  value2 (-time timestamp2 (managed-float-value (clock-get g2-time-at-start)))
	  (2d-state-virtual-origin-x current-2d-state)
	  (2d-state-raster-width-to-right current-2d-state)
	  (fast-time-slot current-2d-state 2d-state-base-time)
	  (2d-state-position-shift current-2d-state)))
  (let* ((plot-minima (trend-chart-plot-minima current-trend-chart))
	 (plot-maxima (trend-chart-plot-maxima current-trend-chart))
	 (plot-index  (plot-index plot))
	 (range-mode (verified-value-axis-range-mode axis))
	 (abstract-x1 (time-to-abstract-x-macro timestamp1))
	 (abstract-x2 (time-to-abstract-x-macro timestamp2))
	 (ring-raster-x1 (abstract-x-start-to-unscaled-ring-raster-macro
			   abstract-x1))
	 (ring-raster-x2 (abstract-x-end-to-unscaled-ring-raster-macro
			   abstract-x2))
	 (unscaled-y1 (compute-grid-y value1 plot-index plot-minima plot-maxima
				      range-mode axis))
	 (unscaled-y2 (compute-grid-y value2 plot-index plot-minima plot-maxima
				      range-mode axis)))
    (cond
      ;; more points than pixels, so we're gonna paint some vertical lines
      ((=f abstract-x1 abstract-x2)
       (paint-plot-connector-segment
	 ;  plot
	 ring-raster-x1 unscaled-y1
	 ring-raster-x1 unscaled-y2
	 connector-color line-style style-arg))
      ;; line wraps on ring raster -- must paint two lines
      ((>r ring-raster-x1 ring-raster-x2)
       (let* ((grid-width (2d-state-grid-width current-2d-state))
	      (offset-for-y
		(floorf (*f (-f unscaled-y1 unscaled-y2)
			    (-f grid-width ring-raster-x1))
			(-f abstract-x2 abstract-x1)))
	      (breakpoint-for-y (-f unscaled-y1 offset-for-y)))
       (paint-plot-connector-segment
	 ; plot
	 ring-raster-x1 unscaled-y1
	 (2d-state-grid-width current-2d-state) breakpoint-for-y
	 connector-color line-style style-arg)
       (paint-plot-connector-segment
	 ; plot
	 0 breakpoint-for-y
	 ring-raster-x2 unscaled-y2
	 connector-color line-style style-arg)))
      ;; paint one line
      (t
	(paint-plot-connector-segment
	  ; plot
	  ring-raster-x1 unscaled-y1
	  ring-raster-x2 unscaled-y2
	  connector-color line-style style-arg)))))

(defun-void paint-plot-connector-segment
    (unscaled-x1 unscaled-y1 unscaled-x2 unscaled-y2
		 connector-color line-style style-arg)
  #+development
  (when (and trace-trend-chart-painting
	     (not (eq current-grid-painting-mode :multiple-pass-subsequent)))
    (when t ; (or (>f unscaled-x1 200) (<f unscaled-x2 20))
      (format t "  SEGMENT (~d ~d ~d ~d)~%"
	      unscaled-x1 unscaled-y1 unscaled-x2 unscaled-y2)))
  (let* ((scaled-x1 (delta-x-in-window unscaled-x1
				       current-grid-painting-x-scale))
	 (scaled-y1 (delta-y-in-window unscaled-y1
				       current-grid-painting-y-scale))
	 (scaled-x2 (delta-x-in-window unscaled-x2
				       current-grid-painting-x-scale))
	 (scaled-y2 (delta-y-in-window unscaled-y2
				       current-grid-painting-y-scale))
	 (width
	   (when (numberp style-arg)
	     (delta-y-in-window style-arg ; (connector-line-width connector-format)
				current-grid-painting-y-scale)))
	 (plot-color-value
	   (trend-chart-color-value
	     connector-color ; (connector-line-color connector-format)
	     foreground)))
    ;; (none) (constant target 'top)
	(case line-style ; (frame-like-value-key connector-shading-target-spec)
	  (line
	   (paint-thick-line-in-rendering
	     scaled-x1 scaled-y1 scaled-x2 scaled-y2
	     plot-color-value width
	     (scale-y-for-grid-painting
	       (2d-state-grid-data-height current-2d-state))))
	  (shaded
	   (paint-shaded-line-in-rendering
	     scaled-x1 scaled-y1 scaled-x2 scaled-y2
	     plot-color-value
	     (scale-y-for-grid-painting
	       (if (eq style-arg ;(frame-like-value-property
		       'top)
		   0
		   (2d-state-grid-data-height current-2d-state)))
	     (scale-y-for-grid-painting
	       (2d-state-grid-data-height current-2d-state))
	     )))))

(defun paint-shaded-line-in-rendering (scaled-x1 scaled-y1 scaled-x2 scaled-y2
						 plot-color-value
						 scaled-target-y
						 scaled-y-limit)
  (let (higher-y lower-y
	triangle-base-y triangle-point-y triangle-point-x
        rectangle-top rectangle-bottom
	(grid-top 0)
	(grid-bottom scaled-y-limit))
    (cond
      ((>r scaled-y1 scaled-y2)
       (setf higher-y scaled-y2)
       (setf lower-y scaled-y1))
      (t
       (setf higher-y scaled-y1)
       (setf lower-y scaled-y2)))
    (cond
      ((=r scaled-target-y 0)
       (setf rectangle-top 0)
       (setf rectangle-bottom higher-y)
       (setf triangle-base-y higher-y)
       (setf triangle-point-y lower-y)
       (setf triangle-point-x
	     (if (=r lower-y scaled-y2) scaled-x2 scaled-x1)))
      (t
       (setf rectangle-top lower-y)
       (setf rectangle-bottom scaled-target-y)
       (setf triangle-base-y lower-y)
       (setf triangle-point-y higher-y)
       (setf triangle-point-x
	     (if (=f higher-y scaled-y2) scaled-x2 scaled-x1))))
    (when (or (and (=r scaled-target-y grid-top)
		   (<r scaled-y1 grid-top)
		   (<r scaled-y2 grid-top))
	      (and (=r scaled-target-y grid-bottom)
		   (>r scaled-y1 grid-bottom)
		   (>r scaled-y2 grid-bottom)))
      (return-from paint-shaded-line-in-rendering))
    (unless (or (and (=r scaled-target-y grid-top)
		     (<r rectangle-bottom grid-top))
		(and (=r scaled-target-y grid-bottom)
		     (>r rectangle-top grid-bottom)))
      (primitive-rectangle-in-rendering
	scaled-x1
	(maxr rectangle-top grid-top) ; chg
	scaled-x2
	(minr rectangle-bottom grid-bottom) ; grid data height clipping
	plot-color-value))
    (cond
      ((=r triangle-point-y triangle-base-y)
       nil) ; too small to draw
      ((=r scaled-target-y 0) ; shading to top
       (unless (or (>r triangle-base-y grid-bottom)
		   (<=r triangle-point-y grid-top))
	 (let* ((triangle-height (-r triangle-point-y triangle-base-y))
		(base-width (-r scaled-x2 scaled-x1))
		(up-sloping-p (>r scaled-y1 scaled-y2))
		(bottom-intercept
		 (+r (if up-sloping-p scaled-x1 scaled-x2)
		     (roundr (*r base-width (-r triangle-base-y grid-bottom)
				 (if up-sloping-p 1 -1))
			     triangle-height)))
		(top-intercept
		 (+r (if up-sloping-p scaled-x1 scaled-x2)
		     (roundr (*r base-width (-r triangle-base-y grid-top)
				 (if up-sloping-p 1 -1))
			     triangle-height))))
	   (cond 
	     (up-sloping-p
	      (cond
		((>r bottom-intercept scaled-x1)
		 (primitive-rectangle-in-rendering
		   scaled-x1 (maxr scaled-y2 grid-top)
		   bottom-intercept grid-bottom
		   plot-color-value)
		 (primitive-triangle-in-rendering
		   bottom-intercept grid-bottom
		   bottom-intercept (maxr grid-top scaled-y2)
		   (minr scaled-x2 top-intercept)
		   (maxr grid-top scaled-y2)
		   plot-color-value))
		(t
		 (primitive-triangle-in-rendering
		   scaled-x1 (minr scaled-y1 grid-bottom)
		   scaled-x1 (maxr scaled-y2 grid-top)
		   (minr scaled-x2 top-intercept)
		   (maxr scaled-y2 grid-top)
		   plot-color-value))))
	     (t ; down-sloping
	      (cond ((<r bottom-intercept scaled-x2)
		     (primitive-rectangle-in-rendering
		       bottom-intercept (maxr grid-top scaled-y1)
		       scaled-x2 grid-bottom plot-color-value)
		     (primitive-triangle-in-rendering
		       bottom-intercept grid-bottom
		       bottom-intercept (maxr grid-top scaled-y1)
		       (maxr scaled-x1 top-intercept)
		       (maxr scaled-y1 grid-top) plot-color-value))
		    (t
		     (primitive-triangle-in-rendering
		       scaled-x2 (minr scaled-y2 grid-bottom)
		       scaled-x2 (maxr grid-top scaled-y1)
		       (maxr scaled-x1 top-intercept)
		       (maxr grid-top scaled-y1) plot-color-value))))))))
      (t
       (unless (or (>=r triangle-point-y grid-bottom)
		   (<r triangle-base-y grid-top))
	 (let* ((triangle-height (-r triangle-base-y triangle-point-y))
		(base-width (-r scaled-x2 scaled-x1))
		(up-sloping-p (>r scaled-y1 scaled-y2))
		(bottom-intercept
		 (+r (if up-sloping-p scaled-x1 scaled-x2)
		     (roundr (*r base-width (-r triangle-base-y grid-bottom)
				 (if up-sloping-p 1 -1))
			     triangle-height)))
		(top-intercept
		 (+r (if up-sloping-p scaled-x1 scaled-x2)
		     (roundr (*r base-width (-r triangle-base-y grid-top)
				 (if up-sloping-p 1 -1))
			     triangle-height))))
	   (cond (up-sloping-p
		  (cond
		    ((<r top-intercept scaled-x2)
		     (primitive-rectangle-in-rendering
		       top-intercept grid-top scaled-x2
		       (minr grid-bottom scaled-y1)
		       plot-color-value)
		     (primitive-triangle-in-rendering
		       top-intercept grid-top
		       top-intercept (minr grid-bottom scaled-y1)
		       (maxr scaled-x1 bottom-intercept)
		       (minr grid-bottom scaled-y1)
		       plot-color-value))
		    (t
		     (primitive-triangle-in-rendering
		       scaled-x2 (maxr scaled-y2 grid-top)
		       scaled-x2 (minr grid-bottom scaled-y1)
		       (maxr scaled-x1 bottom-intercept)
		       (minr grid-bottom scaled-y1)
		       plot-color-value))))
		 (t
		  (cond
		    ((>r top-intercept scaled-x1)
		     (primitive-rectangle-in-rendering
		       scaled-x1 grid-top top-intercept
		       (minr grid-bottom scaled-y2)
		       plot-color-value)
		     (primitive-triangle-in-rendering
		       top-intercept grid-top
		       top-intercept (minr grid-bottom scaled-y2)
		       (minr scaled-x2 bottom-intercept)
		       (minr grid-bottom scaled-y2)
		       plot-color-value))
		    (t
		     (primitive-triangle-in-rendering
		       scaled-x1 (maxr scaled-y1 grid-top)
		       scaled-x1 (minr grid-bottom scaled-y2)
		       (minr scaled-x2 bottom-intercept)
		       (minr grid-bottom scaled-y2)
		       plot-color-value)))))))))))

	   
(defun-void primitive-clipped-line-in-rendering
    (scaled-x1 scaled-y1 scaled-x2 scaled-y2
	       scaled-y-limit logical-color-value)
  (cond
    ((=r scaled-y2 scaled-y1)
     (when (<=r scaled-y1 scaled-y-limit)
       (primitive-line-in-rendering
	 scaled-x1 scaled-y1 scaled-x2 scaled-y2
	 logical-color-value)))
    ((and (>r scaled-y2 scaled-y-limit)
	  (>r scaled-y1 scaled-y-limit))
     nil)
    ((or (>r scaled-y2 scaled-y-limit)
	 (>r scaled-y1 scaled-y-limit))
     (let ((width (-r scaled-x2 scaled-x1))
	   (height (-r scaled-y2 scaled-y1)))
       (cond
	 ((>r scaled-y2 scaled-y-limit)
	  (let ((cut-x (+r scaled-x1
			   (floorr (*r (-r scaled-y-limit scaled-y1) width)
				   height))))
	    (primitive-line-in-rendering
	      scaled-x1 scaled-y1 cut-x scaled-y-limit
	      logical-color-value)))
	 (t
	  (setf height (-r height))
	  (let ((cut-x (+r scaled-x1
			   (floorr (*r (-r scaled-y1 scaled-y-limit) width)
				   height))))
	    (primitive-line-in-rendering
	      cut-x scaled-y-limit scaled-x2 scaled-y2
	      logical-color-value))))))
    (t
     (primitive-line-in-rendering
       scaled-x1 scaled-y1 scaled-x2 scaled-y2
       logical-color-value))))

(defmacro y-intercept-line (x1 y1 x2 y2 y-intercept)
  ;; returns the x of the intercept
  (avoiding-variable-capture (x1 y1 x2 y2 y-intercept)
    `(cond ((=r ,y2 ,y1)
	    (+r ,x1 (halfr (-r ,x2 ,x1))))
	   ((>r ,y2 ,y1)
	    (+r ,x1
		(floorr (*r (-r ,x2 ,x1)
			    (-r ,y-intercept ,y1))
			(-r ,y2 ,y1))))
	   (t
	    (+r ,x1
		(floorr (*r (-r ,x2 ,x1)
			    (-r ,y1 ,y-intercept))
			(-r ,y1 ,y2)))))))

(defun-void paint-thick-line-in-rendering
    (scaled-x1 scaled-y1 scaled-x2 scaled-y2 logical-color-value width scaled-y-limit)
  (cond
    ;; Case One:  The scaled thickness is one, or the slope > width
    ((or (=r width 1)
	 (=f scaled-x1 scaled-x2) ; vertical line / div by zero case
	 (let ((slope (floorf (if (>f scaled-y2 scaled-y1) ; try ceilingf ***
				  (-f scaled-y2 scaled-y1)
				  (-f scaled-y1 scaled-y2))
			      (-f scaled-x2 scaled-x1))))
	   (>=f slope width)))
     (cond ((=r scaled-x1 scaled-x2)
	    ;; This means when drawing line from (a b) to (a b)
	    ;; nothing will be drawn!
	    (cond
	      ;; experimental hack !
	      (nil ;(>r width 1)
	       (let* ((width-odd-p width)
		      (y-limit (scale-y-for-grid-painting
				 (2d-state-grid-data-height current-2d-state)))
		      (half-width  (halfr width))
		      (y-increment (if width-odd-p half-width (1+r half-width)))
		      (y-decrement half-width)
		      greater-y lesser-y)
		 (cond ((>r scaled-y1 scaled-y2)
			(setf greater-y scaled-y1 lesser-y scaled-y2))
		       (t
			(setf greater-y scaled-y2 lesser-y scaled-y1)))
		 (primitive-line-in-rendering
		   scaled-x1
		   (-r lesser-y y-decrement)
		   scaled-x2
		   (minr (1-r (+r greater-y y-increment))
			 y-limit)
		   logical-color-value)))
	      ((/=r scaled-y1 scaled-y2)
	       (when (or (<=r scaled-y1 scaled-y-limit)
			 (<=r scaled-y2 scaled-y-limit))
		 (primitive-line-in-rendering
		   scaled-x1 (minr scaled-y1 scaled-y-limit)
		   scaled-x2 (minr scaled-y2 scaled-y-limit)
		   logical-color-value)))))
	   ((=r scaled-y1 scaled-y2)
	    (when (<=r scaled-y1 scaled-y-limit)
	      (primitive-line-in-rendering
		scaled-x1 scaled-y1 (1-r scaled-x2) scaled-y2 logical-color-value)))
	   ((>r scaled-y2 scaled-y1)
	    (primitive-clipped-line-in-rendering
	      scaled-x1 scaled-y1 (1-r scaled-x2) (1-r scaled-y2)
	      scaled-y-limit logical-color-value))
	   (t
	    (primitive-clipped-line-in-rendering
	      scaled-x1 scaled-y1 (1-r scaled-x2) (1+r scaled-y2)
	      scaled-y-limit logical-color-value))))
    ;; Case Two: Line is Wide, Draw it as two triangles
    (t
     (let* ((width-odd-p width)
	    (y-limit (scale-y-for-grid-painting
		       (2d-state-grid-data-height current-2d-state)))
	    (half-width  (halfr width))
	    (y-increment (if width-odd-p half-width (1+r half-width)))
	    (y-decrement half-width))
       (let* ((right-top (-r scaled-y2 y-decrement))
	      (right-bottom (+r scaled-y2 y-increment))
	      (left-y (-r scaled-y1 y-decrement)))
	 (cond
	   ((and (>r right-top y-limit) (>r left-y y-limit))
	    ) ; do nothing
	   ((>r right-top y-limit)
	    ;; do some clipping - we know left-y is in
	    (let ((top-cut-x
		    (y-intercept-line scaled-x1 left-y scaled-x2 right-top y-limit))
		  (bottom-cut-x
		    (y-intercept-line scaled-x1 left-y scaled-x2 right-bottom y-limit)))
	      (primitive-triangle-in-rendering
		scaled-x1 left-y top-cut-x y-limit bottom-cut-x y-limit
		logical-color-value)))
	   ((and (>r left-y y-limit) (>r right-bottom y-limit))
	    ;; one triangle (cut-x left-to-top) y-limit scaled-x2 right-top scaled-x2 y-limit
	    (let ((cut-x
		    (y-intercept-line scaled-x1 left-y scaled-x2 right-top y-limit)))
	      (primitive-triangle-in-rendering
		cut-x y-limit scaled-x2 right-top scaled-x2 y-limit
		logical-color-value)))
	   ((>r left-y y-limit)
	    ;; two triangles y-intercept both lines
	    (let ((top-cut-x
		    (y-intercept-line scaled-x1 left-y scaled-x2 right-top y-limit))
		  (bottom-cut-x
		    (y-intercept-line scaled-x1 left-y scaled-x2 right-bottom y-limit)))
	      (primitive-triangle-in-rendering
		top-cut-x y-limit bottom-cut-x y-limit scaled-x2 right-top
		logical-color-value)
	      (primitive-triangle-in-rendering
		bottom-cut-x y-limit scaled-x2 right-top scaled-x2 right-bottom
		logical-color-value)))
	   ((>r right-bottom y-limit)
	    (let ((bottom-cut-x
		    (y-intercept-line scaled-x1 left-y scaled-x2 right-bottom y-limit)))
	      (primitive-triangle-in-rendering
		scaled-x1 left-y scaled-x2 right-top scaled-x2 y-limit
		logical-color-value)
	      (primitive-triangle-in-rendering
		scaled-x1 left-y bottom-cut-x y-limit scaled-x2 y-limit
		logical-color-value)))
	   (t
	    (primitive-triangle-in-rendering
	      scaled-x1 left-y scaled-x2 right-top scaled-x2 right-bottom
	      logical-color-value))))
       (let* ((left-top (-r scaled-y1 y-decrement))
	      (left-bottom (+r scaled-y1 y-increment))
	      (right-y (+r scaled-y2 y-increment)))
	 (cond
	   ((and (>r left-top y-limit) (>r right-y y-limit)) 
	    ) ; do nothing
	   ((or (>r left-bottom y-limit) (>r right-y y-limit))
	    (let ((top-cut-x
		    (y-intercept-line scaled-x1 left-top  scaled-x2 right-y y-limit))
		  (bottom-cut-x
		    (y-intercept-line scaled-x1 left-bottom scaled-x2 right-y y-limit)))
	      (cond
		((>r left-top y-limit)
		 (primitive-triangle-in-rendering
		   top-cut-x y-limit bottom-cut-x y-limit scaled-x2 right-y
		   logical-color-value))
		((and (>r right-y y-limit) (>r left-bottom y-limit))
		 (primitive-triangle-in-rendering
		   scaled-x1 left-top scaled-x1 y-limit top-cut-x y-limit
		   logical-color-value))
		((>r right-y y-limit)
		 (primitive-triangle-in-rendering
		   scaled-x1 left-top scaled-x1 left-bottom top-cut-x y-limit
		   logical-color-value)
		 (primitive-triangle-in-rendering
		   scaled-x1 left-bottom top-cut-x y-limit bottom-cut-x y-limit
		   logical-color-value))
		((>r left-bottom y-limit)
		 (primitive-triangle-in-rendering
		   scaled-x1 left-top scaled-x1 y-limit scaled-x2 right-y
		   logical-color-value)
		 (primitive-triangle-in-rendering
		   bottom-cut-x y-limit scaled-x1 y-limit scaled-x2 right-y
		   logical-color-value)
		 ))))
	   (t
	    (primitive-triangle-in-rendering
	      scaled-x1 left-top scaled-x1 left-bottom scaled-x2 right-y
	      logical-color-value))))))))


(define-grid-painting-function primitive-line-in-rendering
    (scaled-x1 scaled-y1 scaled-x2 scaled-y2 logical-color-value)
  #+development
  (when (and trace-trend-chart-painting
	     (not (eq current-grid-painting-mode :multiple-pass-subsequent)))
    (format t "PLR =(~s ~s ~s ~s) ~%" scaled-x1 scaled-y1 scaled-x2 scaled-y2))
  (paint-line-in-current-scratchpad-raster
    scaled-x1 scaled-y1 scaled-x2 scaled-y2
    (2d-painting-color-value logical-color-value) t))

(define-grid-painting-function primitive-triangle-in-rendering
    (scaled-x1 scaled-y1 scaled-x2 scaled-y2 scaled-x3 scaled-y3 logical-color-value)
  #+development
  (when (and trace-trend-chart-painting
	     (not (eq current-grid-painting-mode :multiple-pass-subsequent)))
    (format t "(~s ~s)  (~s ~s) (~s ~s)~%"
	    scaled-x1 scaled-y1 scaled-x2 scaled-y2 scaled-x3 scaled-y3)
    (when (or (>r scaled-y1 139)
	      (>r scaled-y2 139)
	      (>r scaled-y3 139))
      ); (break))
    (when (or (<r scaled-y1 0)
	      (<r scaled-y2 0)
	      (<r scaled-y3 0))
      (break)))
  (paint-filled-triangle-in-current-scratchpad-raster
    scaled-x1 scaled-y1 scaled-x2 scaled-y2 scaled-x3 scaled-y3
    (2d-painting-color-value logical-color-value)))

(define-grid-painting-function primitive-rectangle-in-rendering
    (scaled-left scaled-top scaled-right scaled-bottom logical-color-value)
  #+development
  (when (and trace-trend-chart-painting
	     (not (eq current-grid-painting-mode :multiple-pass-subsequent)))
    (format t "(~s ~s ~s ~s)~%"
	    scaled-left scaled-top scaled-right scaled-bottom))
  (paint-solid-rectangle-in-current-scratchpad-raster
    scaled-left scaled-top scaled-right scaled-bottom
    (2d-painting-color-value logical-color-value)))

(define-grid-painting-function primitive-text-in-rendering
    (text text-box-format scaled-left scaled-top scaled-right scaled-bottom
	  box-left box-baseline logical-color-value)
  (paint-from-line-of-text-to-current-scratchpad-raster
    scaled-left scaled-top scaled-right scaled-bottom
    text  
    (default-word-spacing text-box-format)
    (text-cell-font-map text-box-format)
    (2d-painting-color-value logical-color-value)
    current-grid-painting-x-scale
    current-grid-painting-y-scale
    box-left
    box-baseline))



(define-grid-painting-function clear-whole-raster ()
  (let* ((grid-height (2d-state-grid-height current-2d-state))
	 (grid-width (2d-state-grid-width current-2d-state))
	 (background-color-value
	   (if (eq current-grid-painting-color-mode :monochrome)
	       0
	       current-grid-painting-background-color-value)))
    (paint-clearing-rectangle
      (delta-x-in-window 0
			 current-grid-painting-x-scale)
      (delta-y-in-window 0 current-grid-painting-y-scale)
      (delta-x-in-window grid-width
			 current-grid-painting-x-scale)
      (delta-y-in-window grid-height
			 current-grid-painting-y-scale)	
      background-color-value)))

(define-grid-painting-function clear-whole-raster-for-inactive
    (grid-width grid-height)
  (let* ((background-color-value
	   (if (eq current-grid-painting-color-mode :monochrome)
	       0
	       current-grid-painting-background-color-value)))
    (paint-clearing-rectangle
      (delta-x-in-window 0
			 current-grid-painting-x-scale)
      (delta-y-in-window 0 current-grid-painting-y-scale)
      (delta-x-in-window grid-width
			 current-grid-painting-x-scale)
      (delta-y-in-window grid-height
			 current-grid-painting-y-scale)	
      background-color-value)))

(define-grid-painting-function clear-scrolling-region
    (previous-virtual-origin-x current-virtual-origin-x)
  ;; *** assumes no v-scrolling
  ;; this function is f**ked up because
  ;; the coordinate system used in paint-solid-rectangle is
  ;; f**ked up too.
  (let ((grid-height (2d-state-grid-height current-2d-state))
	(background-color-value
	  (if (eq current-grid-painting-color-mode :monochrome)
	      0
	      current-grid-painting-background-color-value)))
    #+development
    (when trace-trend-chart-painting
      (unless (eq current-grid-painting-mode :multiple-pass-subsequent)
	(format t "CLEAR SCROLL prev=~d curr=~d~%"
		previous-virtual-origin-x
		current-virtual-origin-x)))
    (cond ((>f previous-virtual-origin-x current-virtual-origin-x)
	   (paint-clearing-rectangle
	     (delta-x-in-window previous-virtual-origin-x
				current-grid-painting-x-scale)
	     (delta-y-in-window 0
				current-grid-painting-y-scale)
	     (delta-x-in-window (+r 0 (2d-state-grid-width current-2d-state))
				current-grid-painting-x-scale)
	     (delta-y-in-window grid-height
				current-grid-painting-y-scale)	
	     background-color-value)
	   (paint-clearing-rectangle
	     (delta-x-in-window 0 current-grid-painting-x-scale)
	     (delta-y-in-window 0 current-grid-painting-y-scale)
	     (delta-x-in-window current-virtual-origin-x
				current-grid-painting-x-scale)
	     (delta-y-in-window grid-height
				current-grid-painting-y-scale)	
	     background-color-value))
	  (t
	   (paint-clearing-rectangle
	     (delta-x-in-window previous-virtual-origin-x
				current-grid-painting-x-scale)
	     (delta-y-in-window 0 current-grid-painting-y-scale)
	     (delta-x-in-window (+r 0 current-virtual-origin-x)
				current-grid-painting-x-scale)
	     (delta-y-in-window grid-height
				current-grid-painting-y-scale)	
	     background-color-value)))))
  
(defun-void paint-clearing-rectangle (left top right bottom color-value)
  (if nil ; icp-protocol-supports ...
      (paint-clearing-rectangle-in-current-scratchpad-raster
	left top right bottom color-value)
      (paint-solid-rectangle-in-current-scratchpad-raster
	left top right bottom color-value)))


;;;; Rendering management




(defun get-2d-state-for-current-window (trend-chart)
  ;; must be in ON-WINDOW extent
  (loop for state in (2d-image-plane-states trend-chart)
	do
          (when (eq current-window
		    (window-for-graph-rendering (2d-state-rendering state)))
	    (return state))))

(defun adjoin-2d-state (trend-chart state)
  ;; must be in ON-WINDOW extent (at least)
  ;; which is true under inside a draw method
  (unless (memq state (2d-image-plane-states trend-chart))
    (slot-value-push state (2d-image-plane-states trend-chart)))
 state)

;; get-or-make-2d-state will handle changes to size of trend-chart
;; object image-plane scaling, and, of course, non-existence

(defun make-initialized-value-array (maximum-plots polarity)
  (loop with array = (allocate-managed-float-array maximum-plots)
	for i from 0 below maximum-plots
	do
    (mutate-managed-float-array array i
				(cond ((eq polarity 'negative)
				       (uninitialized-negative-value-flag)
				       )
				      (t
				       (uninitialized-positive-value-flag)
				       )))
	finally
	  (return array)))

(defun make-initialized-time-array (maximum-plots polarity)
  (loop with array = (allocate-managed-float-array maximum-plots)
	for i from 0 below maximum-plots
	do
    (mutate-managed-float-array array i
				(cond ((eq polarity 'negative)
				       (most-negative-time)
				       )
				      (t
				       (most-positive-time)
				       )))
	finally
	  (return array)))

(defun grid-size-changed-p (grid-pane graph-rendering)
  (multiple-value-bind (width height)
      (get-grid-inner-dimensions grid-pane)
    (or (/=r (delta-x-in-window width current-image-x-scale)
	     (width-of-graph-rendering-structure graph-rendering))
	(/=r (delta-y-in-window height current-image-y-scale)
	     (height-of-graph-rendering-structure graph-rendering)))))

(defun get-or-make-trend-chart-state (trend-chart)
  ;; must be in ON-WINDOW extent
  ;; second return value indicates that a new rendering has been created
  ; (print (2d-image-plane-states trend-chart))
  (let ((found-2d-state? (get-2d-state-for-current-window trend-chart))
	(grid-pane (get-grid-for-trend-chart trend-chart)))
    (cond ((or (null found-2d-state?)
	       (grid-size-changed-p grid-pane
				    (2d-state-rendering found-2d-state?))
	       (null (2d-state-rendering found-2d-state?))
	       ;; not to scale or otherwise bogus
	       (graph-rendering-has-wrong-scale?
		 (2d-state-rendering found-2d-state?)))
	   (when (and found-2d-state? (2d-state-rendering found-2d-state?))
	     (decache-graph-rendering (2d-state-rendering found-2d-state?)))
;	     (break))
	   ;; Note that deleted-frame-p is merely a sop.  -jallard 6/10/97
	   #+development
	   (when (deleted-frame-p found-2d-state?)
	     (format t "Tell Joe that graph renderings are corrupted!~%"))
	   (let ((new-2d-rendering
		   (make-new-2d-rendering trend-chart
					  grid-pane
					  current-image-x-scale
					  current-image-y-scale))
		 (2d-state (or found-2d-state?
			       (make-frame '2d-image-plane-state))))
	     (setf (2d-state-rendering 2d-state) new-2d-rendering)
	     (setf (2d-state-latest-event-indices 2d-state)
		   (allocate-managed-array
		     (trend-chart-plot-slot-count trend-chart)))
	     (setf (2d-state-latest-event-times 2d-state)
		   (allocate-managed-array
		     (trend-chart-plot-slot-count trend-chart)))
	     (reclaim-time-slot 2d-state 2d-state-last-painting-time)
	     (adjoin-2d-state trend-chart 2d-state)
	     (values 2d-state t)))
	  (t
	   (values found-2d-state? nil)))))

(defun add-colors-used-by-plot (trend-chart plot list-of-colors)
  (let* ((connector-format? (get-slot-component-group-by-reference
			     trend-chart plot 'plot-connector-format))
	 (point-format? (get-slot-component-group-by-reference
			 trend-chart plot 'plot-point-format)))
    (when (and connector-format?
	       (connector-visible? connector-format?))
      (graph-pushnew (connector-line-color connector-format?)
		      list-of-colors))
    (when (and point-format?
	       (point-visible? point-format?))
      (graph-pushnew (point-color point-format?) list-of-colors))
    list-of-colors))
     
(defun count-foreground-colors-of-trend-chart (trend-chart)
  (loop with trend-chart-format = (trend-chart-format
				     trend-chart)
	with grid-background-color = (data-window-background-color
				       trend-chart-format)
	with color-list = (graph-list grid-background-color)
	for plot being the slot-component-groups of (trend-chart-plots trend-chart)
	do
          (setq color-list
		(add-colors-used-by-plot trend-chart plot color-list))
	finally
	  (let ((count (length color-list)))
	    (reclaim-graph-list color-list)
	    (return count))))


(defun make-new-2d-rendering (trend-chart grid-pane x-scale y-scale)
  ;; must be in ON-WINDOW context
  ;; not called directly in initialization sequence
  ;; but will be called in first time through draw code
  (multiple-value-bind (grid-inner-width grid-inner-height)
      (get-grid-inner-dimensions grid-pane)
    (let* ((trend-chart-format (trend-chart-format trend-chart))
	   (width-of-2d-rendering-structure
	     (delta-x-in-window grid-inner-width x-scale))
	   (height-of-2d-rendering-structure
	     (delta-y-in-window grid-inner-height y-scale))
	   (size
	     (compute-size-of-graph-rendering-1    ; from WINDOWS3.LISP
	       width-of-2d-rendering-structure
	       height-of-2d-rendering-structure))
	   (number-of-colors (count-foreground-colors-of-trend-chart trend-chart)))

      (increase-allocation-limit-for-trend-chart-if-necessary
	trend-chart x-scale y-scale size grid-pane)
      
      (let ((2d-rendering
	      (make-decacheable-graph-rendering
		nil
		;; safe, from GRAPHS1.LISP
		(choose-format-for-graph-rendering number-of-colors)
		x-scale y-scale
		0 ; horizontal-grid-line-width
		grid-inner-width
		grid-inner-height
		width-of-2d-rendering-structure
		height-of-2d-rendering-structure
		trend-chart
		current-window
		(get-reference-to-item trend-chart)
		size)))
	;; (set-graph-rendering-foreground-only-mode 2d-rendering t)
	;; (setf (image-plane-for-graph-rendering? 2d-rendering) current-image-plane)
	(if (eq (format-of-graph-rendering-structure 2d-rendering) ; from WINDOWS3.LISP
		'monochrome-raster-list)
	    (update-color-values-for-trend-chart
	      trend-chart 2d-rendering
	      (data-window-background-color trend-chart-format)))
	2d-rendering))))

;; Note that for graphs, 1 is not added to the height and width of the
;; rendering structure as it is for icons.


(defun increase-allocation-limit-for-trend-chart-if-necessary 
       (trend-chart x-scale y-scale size grid-pane)
  (let ((limit-info?
	  (get-memory-limit-info-given-size 
	    graph-rendering-memory-limit-info size))
	(required-size
	  (compute-size-for-trend-charts-of-size-upon-workspace
	    trend-chart x-scale y-scale size grid-pane)))
    (when limit-info?
      (setf (allocation-limit limit-info?)
	    (maxf (allocation-limit limit-info?)
		  required-size)))))

(defun compute-size-for-trend-charts-of-size-upon-workspace 
       (trend-chart x-scale y-scale size-of-given-display grid-pane)
  (multiple-value-bind (grid-inner-width grid-inner-height)
      (get-grid-inner-dimensions grid-pane)
    (let ((workspace? (superblock? trend-chart)))
      (loop with total-size = 0
	    for subblock being each subblock of workspace? 
	    do
	(when (frame-of-class-p subblock 'trend-chart)
	  (let ((some-display-size
		  (compute-size-of-graph-rendering-1  ; from WINDOWS3.LISP
		    (delta-x-in-window grid-inner-width x-scale)
		    (delta-y-in-window grid-inner-height y-scale))))
	    (when (=f some-display-size size-of-given-display)
	      (setq total-size
		    (+f total-size some-display-size)))))
	    finally
	      (return total-size)))))



;;  color-value-given-color-or-default is a safe utility macro from GRAPHS1.LISP

(defun update-color-values-for-trend-chart
       (trend-chart graph-rendering grid-background-color)
  (when t ; (not (graph-rendering-uses-polychrome-rasters? graph-rendering)) ; safe, from WINDOWS3.LISP
    (reclaim-graph-list (color-values-for-rasters? graph-rendering))
    (setf (color-values-for-rasters? graph-rendering) nil)
    (loop with time-axis = (trend-chart-time-axis trend-chart)
	  with color-list = (graph-list grid-background-color)
          for plot being the slot-component-groups of (trend-chart-plots trend-chart)
	  do
            (setq color-list
		  (add-colors-used-by-plot
		    trend-chart plot color-list))
	  finally
	    (when (and (time-grid-lines-visible? time-axis)
		       (/=f 0 (ratio-of-grid-lines-to-time-axis-tickmarks time-axis)))
	      (graph-pushnew (color-for-time-grid-lines time-axis)
			     color-list))
	    (when (time-axis-base-line-visible? time-axis)
	      (graph-pushnew (color-for-time-axis-base-line time-axis)
			     color-list))
	    (loop for value-axis being the slot-component-groups of
		      (trend-chart-value-axes trend-chart)
		  do
	      (when (and (value-axis-visible? value-axis)
			 (value-grid-lines-visible? value-axis)
			 (>f (ratio-of-grid-lines-to-value-axis-tickmarks value-axis)
			     0))
		(graph-pushnew (color-for-value-grid-lines value-axis)
			       color-list))
	      (loop for (ignore . color-spec)
			in (cdr (extra-value-grid-lines value-axis))
		    unless (eq color-spec 'default)
		      do
			(graph-pushnew color-spec color-list)))
	    (let ((tickmark-frequency-spec
		    (time-axis-tickmark-frequency time-axis)))
	      (unless (eq (frame-like-value-key tickmark-frequency-spec)
			  'none)
		(graph-pushnew (color-for-time-tickmarks time-axis)
			       color-list)))
	    (loop with color-value-list = nil
	          for color in color-list
		  do
	      (graph-pushnew (trend-chart-color-value color foreground)
			     color-value-list)
		  finally
		    (reclaim-graph-list color-list)
		    (setf (color-values-for-rasters? graph-rendering)
			  (nreverse color-value-list)))
	    (setf (grid-background-color-value graph-rendering)
		  (trend-chart-color-value
		    grid-background-color background)))))



(defun decache-and-remove-all-image-plane-states-from-trend-chart (trend-chart)
  ;; for resizing (under certain circumstances)
  (decache-all-renderings-of-trend-chart trend-chart)
  (reclaim-slot-value-list (2d-image-plane-states trend-chart))
  (setf (2d-image-plane-states trend-chart) nil)
  ;; Maybe set some flags here eventually
  )

(defun decache-all-renderings-of-trend-chart (trend-chart) 
  (loop with temp-list =  (copy-list-using-slot-value-conses
			    (2d-image-plane-states trend-chart))
        for state in temp-list
	do
    ;; Decaches the graph rendering but does not actually delete the
    ;; 2d-image-plane-state.  Unfortunately this call changes the
    ;; pointer stored in the 2d-image-plane-states of the trend-chart.
    (decache-graph-rendering (2d-state-rendering state))
    (setf (2d-state-rendering state) nil)
    (delete-frame state)
	finally
	  (reclaim-slot-value-list temp-list)))

;;; remove-graph-rendering-from-trend-chart gets called somewhere down the line
;;; (up the stack) from decache-all-renderings-of-trend-chart, through
;;; decache-graph-rendering.  Therefore be wary of the iteration of the
;;; state list versus the delete-slot-value-element below.

(defun remove-graph-rendering-from-trend-chart (graph-rendering trend-chart)
  #+development
  (when trace-trend-chart-painting
    (format t "END   IPS=~s for ~s~%"
	    (2d-image-plane-states trend-chart)
	    trend-chart))
  (let ((state-for-rendering nil))
    (loop for state in (2d-image-plane-states trend-chart)
	  do
      (when (eq graph-rendering  (2d-state-rendering state))
	(setq state-for-rendering state)
	(return)))
    (when state-for-rendering
      (setf (2d-image-plane-states trend-chart)
	    (delete-slot-value-element state-for-rendering
				       (2d-image-plane-states trend-chart)))))
  #+development
  (when trace-trend-chart-painting
    (format t "END   IPS=~s for ~s~%"
	    (2d-image-plane-states trend-chart)
	    trend-chart))
  )

    

;;;; Miscellaneous G2 Item Support


;; The following three macros are based on just cell-array being around
;; -- not some kind of expression list slot, so this will work for
;; the while.

(def-class-method initialize (trend-chart)
  (funcall-superior-method trend-chart)
  (when (and (boundp 'superior-frame-being-cloned?)
	     superior-frame-being-cloned?)
    (update-trend-chart trend-chart t)))

(def-class-method denote-cell-array-element
		  (trend-chart component-particulars include-block-denotation?)
  (declare (ignore trend-chart component-particulars include-block-denotation?))
  (twrite-string "the plot expression")
  (denote-component-of-block-1 '*current-computation-frame* " of "))




;;;; Trend-Chart Run-Time Data and Warmbooting Support

;;; The function `write-graph-data-for-kb' is the main entry point for writing the
;;; runtime data that is needed for the local histories of graphs.  This function is
;;; called from the main dispatch for writing runtime data somewhere in KB-SAVEn.LISP.
;;; The support for this function and its related reading functions is included in the
;;; same file as support for generic and local histories.

(defun write-trend-chart-data-for-kb (trend-chart)
  (loop for plot being the slot-component-groups of (trend-chart-plots trend-chart)
	 as history? = (plot-history plot)
	when (and history?
		  (eq (generic-history-type history?) 'cascaded)
		  (generic-history-data history?)
		  (not (cascaded-ring-buffer-empty?
			 (generic-history-data history?))))
	  do
	    ;; Note that the LEFT BRACKET is only written once, on the first
	    ;; loop iteration.  It is called from within the loop, so that it is
	    ;; only written when there is a non-empty history buffer.
	    (write-left-bracket-if-necessary)
	    (save-history-buffer-for-kb
	      (generic-history-data history?)
	      'trend-chart-plots
	      nil
	      'plot-history
	      (slot-component-group-indicator plot))))
      



;;; The `restore-history-buffer method for trend-chart' stores history-buffer in
;;; the generic-history-data slot of the plot-history substructure held in the
;;; designated slot component of trend-chart.  Note that the plot-history
;;; structure is guaranteed to be present in the slot component, although it
;;; will generally hold nil in its generic-history-data slot prior to this call,
;;; which fills it in.
;;;
;;; Note that no checking is done to ensure that history-location-information
;;; designates a slot component, or that it designates a currently valid slot
;;; component, since no KB should ever have been saved with bogus information
;;; here.

(def-class-method restore-history-buffer 
  (trend-chart history-buffer history-location-information)
  (let* ((slot-name (second history-location-information))
	 (defining-class? (third history-location-information))
	 (slot-component-name (fourth history-location-information))
	 (slot-component-indicator (fifth history-location-information))
	 (old-plot-history
	   (get-slot-component-value
	     trend-chart slot-name defining-class?
	     slot-component-name slot-component-indicator)))
    (let ((current-block-of-dependent-frame trend-chart))
      (when (generic-history-data old-plot-history)
	(reclaim-history-buffer (generic-history-data old-plot-history)))
      (setf (generic-history-data old-plot-history) history-buffer))))





;;;; Converting Graphs to Trend-Charts


;;; `clone-graph-as-trend-chart' takes a graph and makes a nearly
;;; equivalent trend chart.  This function should be called through a
;;; similar harness to new display, to enter dragging context etc.


(defun clone-graph-as-trend-chart (graph)
  (let* ((trend-chart (make-frame-using-compound-types 'trend-chart))
	 (time-axis (trend-chart-time-axis trend-chart))
	 (main-value-axis
	   (car (multiple-compound-slot-value-real-instances
		  (get-slot-value
		    trend-chart 'trend-chart-value-axes))))
	 (trend-chart-format (trend-chart-format trend-chart)))

    (set-edges-of-block trend-chart 0 0
			(-w (right-edge-of-block graph) (left-edge-of-block graph))
			(-w (bottom-edge-of-block graph) (top-edge-of-block graph)))
 
    ;; The biggie, must study its grammar/compiler
    ;; (expressions-to-display
    ;; nil (type list-of-graph-expressions text) no-accessor
    ;;           lookup-slot system select-changes)
    
    (convert-graph-expressions
      trend-chart
      (car (expressions-to-display graph))
      nil)

    (configure-time-axis-based-on-graph
      trend-chart time-axis graph)

    (configure-main-value-axis-based-on-graph
      trend-chart main-value-axis graph)


    ;; GRID LINE SECTION
    ;; become extra plots with constant histories (must implement)
    ;; (extra-grid-lines?
    ;; nil (type extra-grid-line-specs) vector-slot system)

    ;; TREND-CHART-FORMAT SECTION
    ;; goes directly to trend-chart-format
    ;; (background-colors
    ;;   (white . white) (type graph-background-colors) lookup-slot system)
    (let ((background-colors (background-colors graph)))
      (setf (outer-background-color trend-chart-format)
	    (car background-colors)
	    (data-window-background-color trend-chart-format)
	    (cdr background-colors)))
    (setf (data-window-border-visible? trend-chart-format) t)
    (setf (outer-border-color trend-chart-format) 'foreground)

    ;; push standard slot like name config. authors, last edit


    ;; goes directly to graph label
    ;; (label-to-display
    ;; nil (type free text) no-accessor lookup-slot system)
    (let ((label-to-display? (label-to-display graph)))
      (cond
	(label-to-display?
	 (setf (trend-chart-label-to-display trend-chart)
	       (copy-for-slot-value label-to-display?))
	 (setf (trend-chart-label-position trend-chart-format)
	       'below)
	 (setf (trend-chart-legend-visible? trend-chart-format)
	       nil)
	 (setf (trend-chart-label-color trend-chart-format) 'foreground))
	(t
	 (setf (trend-chart-legend-color trend-chart-format)
	       (make-simple-frame-like-value
		 'trend-chart-legend-color-spec 'absolute
		 (slot-value-list 'color 'foreground))))))

    (update-trend-chart-layout trend-chart)
; NOTE: bind current-trend-chart-has-remote-representation-p
; if removing the following comment
;    (update-trend-chart-axes new-trend-chart)
    (update-trend-chart trend-chart t)
    #+development
    (setf most-recent-trend-chart trend-chart)
    trend-chart))

(defmacro set-component-and-maybe-reclaim-old-value
    ((slot-component-name component-group) new-value)
  (avoiding-variable-capture (component-group)
    `(let ((old-value? (component-group-slot ,component-group ',slot-component-name)))
       (when old-value?
	 (reclaim-slot-value old-value?))
       (setf (,slot-component-name ,component-group)
	     ,new-value))))

(defun configure-time-axis-based-on-graph
    (trend-chart time-axis graph)
  (declare (ignore trend-chart))
    ;; TIME AXIS SECTION
    ;; translated to time axis directly
    ;; (desired-range-for-horizontal-axis?
    ;; nil
    ;;   (type horizontal-graph-ruling-parameter?) vector-slot system)
  (with-temporary-gensym-float-creation configure-time-axis-based-on-graph
    (setf (time-axis-update-interval time-axis)
	  (ceiling (slot-value-number-value (display-update-interval graph)))))
  (multiple-value-bind
      (show-time-labels? data-window-timespan? end-time?)
      (parse-horizontal-range-spec
	(desired-range-for-horizontal-axis? graph))
    (cond ((show-grid-lines? graph)
	   (setf (color-for-time-grid-lines time-axis) 'black))
	  (t
	   (setf (time-grid-lines-visible? time-axis) nil)))
    (setf (time-axis-base-line-visible? time-axis) t)
    (setf (color-for-time-tickmarks time-axis) 'foreground)
    (unless show-time-labels?
      (set-component-and-maybe-reclaim-old-value
	(time-axis-tickmark-frequency time-axis)
	    (make-simple-frame-like-value
	      '2d-time-axis-tickmark-frequency-spec 'none nil)))
    (set-component-and-maybe-reclaim-old-value
      (data-window-time-span time-axis)
	  (cond (data-window-timespan?
		 (let ((temp-timespan-constant
			 (slot-value-cons data-window-timespan? 'seconds)))
		   (prog1
		       (make-simple-frame-like-value
			 '2d-time-span-spec 'interval
			 (slot-value-list 'length
					  temp-timespan-constant))
		     (reclaim-slot-value-cons temp-timespan-constant))))
		(t
		 (make-simple-frame-like-value
		   '2d-time-span-spec 'all-history nil))))
    (set-component-and-maybe-reclaim-old-value
      (end-time time-axis)
	  (cond (end-time?
		 (let ((temp-end-time-constant
			 (slot-value-cons end-time? 'seconds)))
		   (prog1
		       (make-simple-frame-like-value
			 '2d-end-time-spec 'start-relative
			 (slot-value-list 'interval
					  temp-end-time-constant))
		     (reclaim-slot-value-cons temp-end-time-constant))))
		(t
		 (make-simple-frame-like-value
		   '2d-end-time-spec 'last-sample nil))))
    (when data-window-timespan?
      (let ((extra-space-percentage
	      (percentage-extra-space-to-leave graph))
	    (continuous-p
	      (scroll-continuously? graph)))
	(cond
	  ((and continuous-p
		(=f 0 extra-space-percentage))
	   (setf (time-axis-jump-scroll? time-axis) nil)
	   ;; this is the default state for trend charts
	   ;; so change nothing
	   )
	  (t
	   ;; make a scroll by interval of fraction of data-window-tspan
	   ;; which is rounded when continuous-p is nil
	   (let* ((scroll-interval-in-seconds
		    (cond (continuous-p
			   (ceilingf (*f data-window-timespan?
					 extra-space-percentage)
				     100))
			  (t
			   (calculate-tickmark-interval
			     data-window-timespan? 300 60))))
		  (temp-interval-constant
		    (slot-value-cons scroll-interval-in-seconds 'seconds)))
	     (setf (time-axis-jump-scroll? time-axis) t)
	     (set-component-and-maybe-reclaim-old-value
	       (time-axis-scroll-interval time-axis)
	       temp-interval-constant)
	     )))))))

(defun parse-horizontal-range-spec (horizontal-range-spec)
  (let (show-time-labels? interval-spec? data-window-timespan?
			 end-time?)
    (cond ((and (consp horizontal-range-spec)
		(eq (car horizontal-range-spec) 'without-tickmark-labels))
	   (setf interval-spec? (cdr horizontal-range-spec))
	   (setf show-time-labels? nil))
	  (t
	   (setf interval-spec? horizontal-range-spec)
	   (setf show-time-labels? t)))
    (cond ((null interval-spec?)
	   (setf data-window-timespan? nil))
	  ((not (eq (car interval-spec?) '\;))
	   (setf data-window-timespan? (car interval-spec?)))
	  (t
	   (let ((start-time (car (second interval-spec?)))
		 (end-time (car (third interval-spec?))))
	     (setf data-window-timespan? (-f end-time start-time))
	     (setf end-time? end-time))))
    (values show-time-labels? data-window-timespan? end-time?)))
	   
(defun configure-main-value-axis-based-on-graph
    (trend-chart value-axis graph)
  (multiple-value-bind (show-axis-labels? range-mode
					  range-low? range-high?)
      (parse-vertical-range-spec
	(desired-range-for-vertical-axis? graph))

    (setf (value-axis-base-line-visible? value-axis) nil)
    (setf (value-axis-position value-axis) 'left)
    (setf (value-axis-range-mode value-axis) range-mode)
    (setf (value-axis-range-slack value-axis) 50)
    (setf (value-axis-labels-visible? value-axis) show-axis-labels?)
    (cond ((show-grid-lines? graph)
	   (setf (color-for-value-grid-lines value-axis) 'black))
	  (t
	   (setf (value-grid-lines-visible? value-axis) nil)))
    (set-component-and-maybe-reclaim-old-value
      (color-for-value-axis-tickmarks value-axis)
      (make-simple-frame-like-value
	'2d-tickmark-label-color 'absolute
	(slot-value-list 'color 'foreground)))
    ;; bounds
    (when (and (eq range-mode 'high-water-marking)
	       (>f (slot-component-group-count
		     trend-chart 'trend-chart-value-axes nil)
		   1))
      ;; use the minimum range that covers all axes
      ;; and be paranoid about mem. leaks
      (when (or range-low? range-high?)
	(error "inconsistency in value axis conversion"))
      (multiple-value-setq (range-low? range-high?)
	(calculate-bounds-from-plot-specific-axes
	  trend-chart value-axis)))
    (when range-low? ; implies range-high?
      (change-slot-value
	trend-chart 'trend-chart-value-axes
	(make-value-for-axis-bounds range-low? range-high?)
	'trend-chart
	'value-axis-bounds
	(slot-component-group-indicator value-axis))
      (reclaim-slot-value range-low?)
      (reclaim-slot-value range-high?))
    ;; tickmark frequency
    (let ((tickmark-frequency-spec?
	   (interval-between-horizontal-grid-lines? graph)))
      ;; the default for trend charts is "compute automatically" too.
      (when tickmark-frequency-spec?
	 ;; configure by interval and offset
	(set-component-and-maybe-reclaim-old-value
	  (value-axis-tickmark-frequency value-axis)
	      (make-simple-frame-like-value 
		'2d-value-axis-tickmark-frequency-spec 'interval
		(slot-value-list
		  'width (normalize-graph-number
			   (car tickmark-frequency-spec?))
		  'origin (normalize-graph-number
			    (car tickmark-frequency-spec?)))))))
    ;; extra grid-line
    (let ((extra-grid-lines (extra-grid-lines? graph)))
      (when (and extra-grid-lines (not (eq extra-grid-lines 'none)))
	(loop with temp-list = nil
	      with extra-value-grid-lines = nil
	      with grid-line-list
	      = (cond ((and (consp extra-grid-lines)
			    (eq (car extra-grid-lines) '\,))
		       (cdr extra-grid-lines))
		      (t
		       (setf temp-list (slot-value-list extra-grid-lines))
		       temp-list))
	      for grid-line-spec in grid-line-list
	      when (not (eq grid-line-spec 'none))
		do
		  (cond ((and (consp grid-line-spec)
			      (not (managed-float-p grid-line-spec)))
			 (slot-value-push (slot-value-cons
					    (copy-managed-number-or-value
					      (car grid-line-spec))
					    (cdr grid-line-spec))
					  extra-value-grid-lines))
			(t
			 (slot-value-push (slot-value-cons
					    (copy-managed-number-or-value
					      grid-line-spec)
					    'default)
					  extra-value-grid-lines)))
	      finally
		(reclaim-slot-value-list temp-list)
		(when extra-value-grid-lines
		  (change-slot-value
		    trend-chart 'trend-chart-value-axes
		    (slot-value-cons '\, extra-value-grid-lines)
		    'trend-chart
		    'extra-value-grid-lines
		    (slot-component-group-indicator value-axis))))))))


(defun calculate-bounds-from-plot-specific-axes (trend-chart main-value-axis)
  (with-temporary-gensym-float-creation converting-value-axes
    (loop with minimum? = nil
	  with maximum? = nil
	  for axis being the slot-component-groups
	      of (trend-chart-value-axes trend-chart)
	   as lower-bound? = (value-axis-lower-bound? axis)
	   as upper-bound? = (value-axis-upper-bound? axis)
	  unless (eq axis main-value-axis)
	    do
	      (cond (minimum?
		     (setf minimum?
			   (minvalue (managed-float-value lower-bound?)
				     minimum?)))
		    (t
		     (setf minimum? (managed-float-value lower-bound?))))
	      (cond (maximum?
		     (setf maximum?
			   (maxvalue (managed-float-value upper-bound?)
				     maximum?)))
		    (t
		     (setf maximum? (managed-float-value upper-bound?))))
	  finally
	    (unless (and minimum? maximum?)
	      (error "inconsistency in value axis conversion"))
	    (return
	      (values (allocate-managed-float minimum?)
		      (allocate-managed-float maximum?))))))

(defun parse-vertical-range-spec (vertical-range-spec)
  (let (show-axis-labels? interval-spec? range-low? range-high?
			  with-all-intervals-the-same? range-mode)
    (cond ((and (consp vertical-range-spec)
		(eq (car vertical-range-spec) 'without-tickmark-labels))
	   (setf show-axis-labels? nil)
	   (setf interval-spec? (cdr vertical-range-spec)))
	  (t
	   (setf show-axis-labels? t)
	   (setf interval-spec? vertical-range-spec)))
    (cond ((null interval-spec?)
	   ;; make the axis high water marking
	   (setf range-mode 'high-water-marking)
	   )
	  ((and (consp interval-spec?)
		(eq (car interval-spec?) '\;))
	   (when (eq 'same (fourth interval-spec?))
	     (setf with-all-intervals-the-same? t))
	   (setf range-mode 'fixed)
	   (setf range-low?
		 (normalize-graph-number
		   (second interval-spec?)))
	   (setf range-high?
		 (normalize-graph-number
		   (third interval-spec?))))
	  (t
	   (when (and (consp interval-spec?)
		      (eq (cdr interval-spec?) 'same))
	     (setf with-all-intervals-the-same? t))
	   ;; make the axis have the automatic mode
	   ;; someday when a real sliding range is implemented for
	   ;; trend-charts it will be chosen here
	   (setf range-mode 'automatic)))
    (values show-axis-labels? range-mode range-low? range-high?)))

(defun normalize-graph-number (range-bound)
  (with-temporary-gensym-float-creation normalize-graph-range-bound
    (cond ((fixnump range-bound)
	   (allocate-managed-float
	     (coerce-fixnum-to-gensym-float range-bound)))
	  ((managed-float-p range-bound)
	   (copy-managed-float range-bound)))))

;; Q: What does the "sliding range" feature mean?
;; A: It attempts to slide a fixed range around recent values
;;    with mixed results

;; Q: What does with all intervals the same really do?
;; A: Only God and Andy know.
      
;; Q: What does this slot mean?
;; (scroll-continuously? nil (type yes-or-no) vector-slot system)

;; A: when scroll-continuously is "no" this number is rounded up to the
;;   number of grid lines to jump with a min of 1
;; when scroll-continuously is "yes" scrolling is not synchronized to
;; grid line intervals but an exact percentage of the grid window is used
;; with a minimum of the amount needed for the new data.  it would not
;; be too grave a sin to round this whn converting to a "nice" number
    
;; becomes a jump scrolling param
;;  (percentage-extra-space-to-leave 0 (type integer) vector-slot system)

;; goes to time-axis-refresh-interval
;;  (display-update-interval
;;    5 (type display-interval) no-accessor lookup-slot system)

;; Q: What do plot-specific ranges mean for graphs
;;  
;; A: If range for some plot is specified a main range must be
;; specified, all plots whose range is specified have their ranges
;; mapped to the main range, plots without ranges are plotted on
;; the main range directly

;; Plot-specific ranges become invisible axes with the 'fixed mode

;; Since the inconsistency is just a frame note for the case of
;; a main range not specified, make an axis with mode fixed and
;; a range that is smallest cover of the unions of all the plots ranges.

;; Q: Do "in color"'s apply to plot markers?
;; A: Yes

;; Data structures for plotting styles
;; color is symbol
;; pattern is 'shading width (marker . width)
;; range is (number . number)

;; Other Notes
;; - the desired range-for-vertical affects the main axis
;;    as does the interval between h-grid-lines
;; show-grid-lines affects main-va and time-axis
;; extra-grid-lines adds more plots with local history (eventually constant)
;;     trapped by (numberp expression) in demand-plot-history

(defmacro build-component-group-name (control-string &body args)
  `(intern-text-string
     (twith-output-to-text-string
       (tformat ,control-string ,@args))))


(defun convert-graph-expressions (trend-chart graph-expressions
					      extra-grid-line-specs)
  (let* (delete-grid-line-list-p
	 delete-graph-expression-list-p
	 (graph-expression-list 
	  (if (and (consp graph-expressions)
		   (eq (car graph-expressions) '\;))
	      (cdr graph-expressions)
	      (prog1
		  (slot-value-list graph-expressions)
		(setq delete-graph-expression-list-p t))))
	 (grid-line-list
	   (cond ((and (consp extra-grid-line-specs)
		       (eq (car extra-grid-line-specs) '\,))
		  (cdr extra-grid-line-specs))
		 (extra-grid-line-specs
		  (prog1 (slot-value-list extra-grid-line-specs)
		    (setq delete-grid-line-list-p t)))))
	 (extended-graph-expression-list nil))
    ;; pass one -- make plots and expressions
    (let* ((plot-counter 0)
	  (text-string-for-designation
	   (twith-output-to-text-string
	     (loop for (graph-expression . tail) on graph-expression-list
		   as designation =
		     (parse-graph-expression-to-atoms graph-expression)
		   initially
		     (tformat "~d plots; "
			      (maxf 1
				    (+f (length graph-expression-list)
					(length grid-line-list))))
		   do
	             (when designation
		       (incff plot-counter)
		       (slot-value-push graph-expression
					extended-graph-expression-list)
		       (tformat "the expression of plot ~d is ~ND~a"
				plot-counter designation
				(if (or tail extra-grid-line-specs)
				    "; " ""))))
	     (loop for (extra-grid-line-spec . tail)
		       on grid-line-list
		   do
	             (incff plot-counter)
		     (slot-value-push
		       (slot-value-cons 'extra-grid-line extra-grid-line-spec)
		       extended-graph-expression-list)
		     (write-expression-annotation-for-extra-grid-line
		       extra-grid-line-spec plot-counter tail)))))
      (parse-text-for-slot
	(convert-text-string-to-text text-string-for-designation)
	trend-chart
	(get-slot-description-of-frame 'trend-chart-plots trend-chart)
	nil nil))
    ;; Pass two fill out the details
    (setf extended-graph-expression-list
	  (nreverse extended-graph-expression-list))
    (loop with invisible-connector-name? = nil
          for graph-expression in extended-graph-expression-list
	  for plot being the slot-component-groups
	  of (trend-chart-plots trend-chart)
	  as plot-counter from 1 by 1
	  do
      (multiple-value-bind
	(designation-expression? 
	  plot-color? plot-shading? plot-marker? plot-line-width?
	  plot-min? plot-max? nupec-plot-marker?)
	(cond ((and (consp graph-expression)
		    (eq (car graph-expression) 'extra-grid-line))
	       (if (and (consp (cdr graph-expression))
			(not (managed-float-p (cdr graph-expression))))
		   (values nil (cddr graph-expression))
		   (values nil)))
	      (t
	       (parse-graph-expression-to-atoms
		 graph-expression)))
	(cond
	  (designation-expression?
	   (change-slot-value trend-chart
			      'trend-chart-plots
			      nil
			      nil
			      'plot-use-local-history?
			      (slot-component-group-indicator plot)))
	  (t
	   (change-slot-value trend-chart
			      'trend-chart-plots
			      86400 ; that's one day
			      nil
			      'plot-update-interval
			      (slot-component-group-indicator plot))
	   (change-slot-value trend-chart
			      'trend-chart-plots
			      nil
			      nil
			      'include-in-legend?
			      (slot-component-group-indicator plot))))
	(cond
	  ((and (not nupec-plot-marker?)
		(or (and plot-color? (not (eq plot-color? 'black)))
		    plot-shading? plot-line-width?))
	  ;; make a connector format and link by name
	  (let* ((name-for-connector-format
		  (build-component-group-name
		    "~a~a-CONNECTOR-~d"
		    (cond (plot-shading? "SHADED-")
			  (plot-line-width? "WIDE-")
			  (t ""))
		    (or plot-color? 'black)
		    plot-counter))
		 (connector-format
		  (add-component-group-to-trend-chart
		    trend-chart 'trend-chart-connector-formats
		    'connector-format name-for-connector-format)))
	    (when plot-color?
	      (setf (connector-line-color connector-format) plot-color?))
	    (when plot-shading?
	      (set-component-and-maybe-reclaim-old-value
		(connector-shading-target connector-format)
		(make-simple-frame-like-value
		  '2d-shading-target-spec 'constant
		  (slot-value-list 'target 'bottom))))
	    (when plot-line-width?
	      (setf (connector-line-width connector-format) plot-line-width?))
	    (setf (plot-connector-format plot) name-for-connector-format)))
	  (nupec-plot-marker?
	   (unless invisible-connector-name?
	     (setf invisible-connector-name?
		   (build-component-group-name "INVISIBLE-CONNECTOR"))
	     (let ((connector-format
		     (add-component-group-to-trend-chart
		       trend-chart 'trend-chart-connector-formats
		       'connector-format invisible-connector-name?)))
	       (setf (connector-visible? connector-format) nil)))
	   (setf (plot-connector-format plot)
		 invisible-connector-name?)))
	(when plot-marker?
	  ;; make a point-format and link by name
	  (let* ((plot-marker-shape
		   (if (eq plot-marker? 'star)
		       'plus-sign
		       plot-marker?))
		 (name-for-point-format
		  (build-component-group-name
		    "~a-~a-POINT-MARKER-~d"
		    (or plot-color? 'black)
		    plot-marker-shape
		    plot-counter))
		 (point-format
		  (add-component-group-to-trend-chart
		    trend-chart 'trend-chart-point-formats
		    'point-format name-for-point-format)))
	    (setf (point-visible? point-format) t)
	    (when plot-color?
	      (setf (point-color point-format) plot-color?))
	    (set-component-and-maybe-reclaim-old-value
	      (point-frequency point-format)
	      (make-simple-frame-like-value
		'2d-plot-marker-frequency 'ratio
		(slot-value-list 'number 1)))
	    (set-component-and-maybe-reclaim-old-value
	      (point-style point-format)
	      (cond ((member plot-marker-shape '(square triangle plus-sign))
		     (make-simple-frame-like-value
		       '2d-plot-marker-shape 'standard
		       (slot-value-list 'shape plot-marker-shape)))
		    (t
		     (make-simple-frame-like-value
		       '2d-plot-marker-shape 'custom
		       (slot-value-list 'icon-class plot-marker-shape)))))
	    (setf (plot-point-format plot) name-for-point-format)))
	(when plot-min?  ; implies plot-max?
	  (let* ((name-for-axis (build-component-group-name
				  "INVISIBLE-AXIS-~d" plot-counter))
		 (axis (add-component-group-to-trend-chart
			 trend-chart 'trend-chart-value-axes
			 'value-axis name-for-axis)))
	    (setf (value-axis-range-mode axis) 'fixed)
	    (setf (value-axis-visible? axis) nil)
	    (change-slot-value
	      trend-chart 'trend-chart-value-axes
	      (make-value-for-axis-bounds plot-min? plot-max?)
	      'trend-chart
	      'value-axis-bounds
	      (slot-component-group-indicator axis))
	    (setf (plot-axis plot) name-for-axis)))))
    (when delete-graph-expression-list-p
      (reclaim-slot-value-list graph-expression-list))
    (when delete-grid-line-list-p
      (reclaim-slot-value-list grid-line-list))
    (loop for graph-expression in extended-graph-expression-list
	  do
      (when (and (consp graph-expression)
		 (eq (car graph-expression) 'extra-grid-line))
	(reclaim-slot-value-cons graph-expression))
	  finally
	    (reclaim-slot-value-list extended-graph-expression-list))))

(defun write-expression-annotation-for-extra-grid-line
    (extra-grid-line-spec plot-counter print-separator?)
  (let ((value-exp
	  (cond ((and (consp extra-grid-line-spec)
		      (not (managed-float-p extra-grid-line-spec)))
		 (car extra-grid-line-spec))
		(t
		 extra-grid-line-spec))))
    (tformat "the expression of plot ~d is ~NE~a"
	     plot-counter value-exp 
	     (if print-separator?
		 "; " ""))))
			     
(defun make-text-value-for-designation (designation-expression)
  (let ((text-string
	  (twith-output-to-text-string
	    (tformat "~ND" designation-expression))))
    (slot-value-cons
      (slot-value-list 
	designation-expression nil nil)
      (convert-text-string-to-text
	text-string))))
	    
(defun make-value-for-axis-bounds (min max)
  (with-temporary-gensym-float-creation make-value-for-axis-bounds
    (let ((min (cond
		 ((fixnump min)
		  (allocate-managed-float
		    (coerce-fixnum-to-gensym-float min)))
		 ((managed-float-p min)
		  (copy-managed-float min))
		 (t
		  min)))
	  (max (cond
		 ((fixnump max)
		  (allocate-managed-float
		    (coerce-fixnum-to-gensym-float max)))
		 ((managed-float-p max)
		  (copy-managed-float max))
		 (t
		  max))))
      (make-simple-frame-like-value
	'2d-value-axis-bounds-spec 'specified
	(slot-value-list
	  'lower min 'upper max)))))

(defun make-simple-frame-like-value (category key temp-plist)
  (prog1 (make-frame-like-category-default
	   category key temp-plist)
    (reclaim-slot-value-list temp-plist)))
	  
(defun add-component-group-to-trend-chart (trend-chart
					    slot-name
					    component-type-name
					    component-name)
  (let ((new-component-group
	  (add-instance-to-multiple-compound-slot-value
	    trend-chart slot-name nil nil nil)))
    ;; set the name or names slot
    (set-slot-component-group-name-or-names
      new-component-group
      component-type-name
      component-name)
    new-component-group))

(defun parse-graph-expression-to-atoms (graph-expression)
  (multiple-value-bind 
      (designation-expression 
	plot-color? plot-pattern? plot-min-and-max?)
      (parse-graph-expression-with-info graph-expression)
    
    (let (plot-shading? plot-marker? plot-line-width?
			plot-min? plot-max? nupec-plot-marker?)
      (cond ((eq plot-pattern? 'shading)
	     (setf plot-shading? t))
	    ((consp plot-pattern?)
	     (cond ((eq (car plot-pattern?) 'nupec)
		    (setf plot-marker? (cdr plot-pattern?)
			  plot-line-width? nil
			  nupec-plot-marker? t))
		   (t
		    (setf plot-marker? (car plot-pattern?))
		    (setf plot-line-width? (cdr plot-pattern?)))))
	    ((fixnump plot-pattern?)
	     (setf plot-line-width? plot-pattern?))
	    ((and plot-pattern? (symbolp plot-pattern?))
	     (setf plot-marker? plot-pattern?)))
      (when plot-min-and-max?
	(setf plot-min? (car plot-min-and-max?))
	(setf plot-max? (cdr plot-min-and-max?)))
      (values designation-expression plot-color? plot-shading?
	      plot-marker? plot-line-width? plot-min? plot-max?
	      nupec-plot-marker?))))




;;;; Trend Chart Access System Procedures

;;; G2-GET-TEXT-OF-TREND-CHART-COMPONENT
;;;    (trend-chart :class trend-chart,
;;;     attribute-name :symbol,
;;;     slot-component-name :symbol,
;;;     slot-component-indicator :item-or-value) { symbol or integer or  false }
;;;   = (text :text) | FALSE

;;; G2-SET-TEXT-OF-TREND-CHART-COMPONENT
;;;    (trend-chart :class trend-chart,
;;;     attribute-name :symbol,
;;;     slot-component-name :symbol,
;;;     slot-component-indicator :item-or-value, { symbol or integer or false }
;;;     new-value-text :text)                    { might allow other types
;;;                                                for values that don't need compilation }
;;;    = TRUE or FALSE



;;; Shared argument validation and error-signaling features
;;; for all trend-chart system procedures.


(defmacro trend-chart-access-error (string &rest args)
  `(stack-error cached-top-of-stack ,string ,@args))

(defun trend-chart-compound-slot-name-p (x)
  (memq x
	'(trend-chart-plots trend-chart-value-axes trend-chart-time-axis
	  trend-chart-point-formats trend-chart-connector-formats
	  trend-chart-format)))

(defun get-trend-chart-slot-name-user-arg (trend-chart ev-attribute-name)
  (prog1 (or (get-slot-name-for-alias-if-any
	       (evaluation-symbol-symbol 
		 ev-attribute-name)
	       trend-chart)
	     (evaluation-symbol-symbol
	       ev-attribute-name))
    (reclaim-evaluation-symbol ev-attribute-name)))

(defun get-trend-chart-slot-component-name-user-arg (trend-chart
						      slot-name
						      ev-slot-component-name)
  (prog1 (or (get-slot-component-name-for-alias-if-any
	       (evaluation-symbol-symbol 
		 ev-slot-component-name)
	       trend-chart
	       (get-compound-slot-compound-type
		 slot-name))
	     (evaluation-symbol-symbol
	       ev-slot-component-name))
    (reclaim-evaluation-symbol
      ev-slot-component-name)))

(defun get-trend-chart-slot-component-indicator-user-arg
    (trend-chart slot-name ev-slot-component-indicator)
  (when (trend-chart-compound-slot-name-p slot-name)
    (cond
      ((or (eq ev-slot-component-indicator
	       evaluation-false-value)
	   (not (is-slot-multiple-compound-slot? slot-name nil)))
       nil)
      ((evaluation-symbol-p ev-slot-component-indicator)
       (prog1
	   (get-slot-component-indicator-for-name-if-any?
	     trend-chart slot-name
	     (evaluation-symbol-symbol ev-slot-component-indicator))
	 (reclaim-evaluation-symbol ev-slot-component-indicator)))
      (t ; it's an evaluation-integer
       (let* ((positional-index
		(evaluation-integer-value 
		  ev-slot-component-indicator))
	      (indicator?
		(and (<=f 1 positional-index 100000)
		     (slot-component-group-nth-indicator?
		       trend-chart slot-name nil (1-f positional-index)))))
	 (reclaim-evaluation-integer ev-slot-component-indicator)
	 indicator?)))))

(defun ensure-trend-chart-compound-attribute-name (slot-name)
  (unless (trend-chart-compound-slot-name-p slot-name)
    (trend-chart-access-error "Bad trend-chart attribute name")))

(defun ensure-trend-chart-slot-component-indicator
    (ev-slot-component-indicator slot-component-indicator?)
  (unless (or (eq ev-slot-component-indicator
		  evaluation-false-value)
	      slot-component-indicator?)
    (trend-chart-access-error
      "Bad trend-chart component name or number")))


;;; The trend-chart component system procedures.  Currently this
;;; includes getting and changing the text of slot value components
;;; and adding and removing component groups.


(defun-for-system-procedure g2-get-text-of-trend-chart-component
    (trend-chart ev-attribute-name ev-slot-component-name
		 ev-slot-component-indicator)
  (declare (keeps-g2-local-variables-valid t))
  (unless (and (of-class-p trend-chart 'trend-chart)
	       (evaluation-symbol-p ev-attribute-name)
	       (evaluation-symbol-p ev-slot-component-name)
	       (or (evaluation-symbol-p ev-slot-component-indicator)
		   (eq ev-slot-component-indicator
		       evaluation-false-value)
		   (evaluation-integer-p ev-slot-component-indicator)))
    (reclaim-evaluation-value ev-attribute-name)
    (reclaim-evaluation-value ev-slot-component-name)
    (reclaim-evaluation-value ev-slot-component-indicator)
    (trend-chart-access-error "Bad args for g2-get-text-of-trend-chart-component"))
  (let* ((slot-name
	   (get-trend-chart-slot-name-user-arg
	     trend-chart ev-attribute-name))
	 (slot-component-name
	   (get-trend-chart-slot-component-name-user-arg
	     trend-chart slot-name ev-slot-component-name))
	 (slot-component-indicator?
	   (get-trend-chart-slot-component-indicator-user-arg
	     trend-chart slot-name ev-slot-component-indicator)))
    (ensure-trend-chart-compound-attribute-name slot-name)
    (ensure-trend-chart-slot-component-indicator
      ev-slot-component-indicator slot-component-indicator?)
    (multiple-value-bind (slot-component-value?
			   slot-component-value-exists-p)
	(get-slot-component-value-if-any
	  trend-chart slot-name nil
	  slot-component-name slot-component-indicator?)
      (unless slot-component-value-exists-p
	(trend-chart-access-error "Unknown trend-chart component specified"))
      (let ((slot-component-type?
	      (get-slot-component-feature-if-any
		'trend-chart slot-name nil
		slot-component-name slot-component-indicator? 'type)))
	(unless slot-component-type?
	  (trend-chart-access-error "Unknown trend-chart component specified"))
	(let ((text-for-value
		(make-text-string-representation-for-slot-value-itself
		  trend-chart slot-component-value? slot-component-type?))
	      ignored-value default-p)
	  (multiple-value-setq
	      (ignored-value default-p)
	    (get-slot-component-value
	      trend-chart slot-name nil
	      slot-component-name slot-component-indicator?))
	  (values
	    (make-evaluation-text-reclaiming-argument text-for-value)
	    (copy-evaluation-value
	      (if default-p evaluation-true-value evaluation-false-value))))))))

(defun-for-system-procedure g2-set-text-of-trend-chart-component
    (trend-chart ev-attribute-name ev-slot-component-name
		 ev-slot-component-indicator ev-text-for-new-value)
  (declare (keeps-g2-local-variables-valid nil))
  (unless (and (of-class-p trend-chart 'trend-chart)
	       (evaluation-symbol-p ev-attribute-name)
	       (evaluation-symbol-p ev-slot-component-name)
	       (or (evaluation-symbol-p ev-slot-component-indicator)
		   (eq ev-slot-component-indicator
		       evaluation-false-value)
		   (evaluation-integer-p ev-slot-component-indicator))
	       (evaluation-text-p ev-text-for-new-value))
    (reclaim-evaluation-value ev-attribute-name)
    (reclaim-evaluation-value ev-slot-component-name)
    (reclaim-evaluation-value ev-slot-component-indicator)
    (reclaim-evaluation-value ev-text-for-new-value)
    (trend-chart-access-error "Bad args for g2-set-text-of-trend-chart-component"))
  (let* ((slot-name
	   (get-trend-chart-slot-name-user-arg
	     trend-chart ev-attribute-name))
	 (slot-component-name
	   (get-trend-chart-slot-component-name-user-arg
	     trend-chart slot-name ev-slot-component-name))
	 (slot-component-indicator?
	   (get-trend-chart-slot-component-indicator-user-arg
	     trend-chart slot-name ev-slot-component-indicator))
	 (text-for-new-value
	   (prog1 (copy-evaluation-text ev-text-for-new-value)
	     (reclaim-evaluation-text ev-text-for-new-value))))
    (ensure-trend-chart-compound-attribute-name slot-name)
    (ensure-trend-chart-slot-component-indicator
      ev-slot-component-indicator slot-component-indicator?)
    (multiple-value-bind (slot-component-value?
			   slot-component-value-exists-p)
	(get-slot-component-value-if-any
	  trend-chart slot-name nil
	  slot-component-name slot-component-indicator?)
      (declare (ignore slot-component-value?))
      (unless slot-component-value-exists-p
	(trend-chart-access-error "Unknown trend-chart component specified"))
      (let ((slot-component-type?
	      (get-slot-component-feature-if-any
		'trend-chart slot-name nil
		slot-component-name slot-component-indicator? 'type)))
	(unless slot-component-type?
	  (trend-chart-access-error "Unknown trend-chart component specified"))
	(let* ((slot-description
		 (get-slot-description-of-frame slot-name trend-chart nil))
	       (link-to-default-p
		 (when (string-equalw text-for-new-value #w"link to default")
		   (reclaim-text-string text-for-new-value)
		   t))
	       parse-text-status parse-text-failure-reason? return-value)
	  (multiple-value-setq
	      (parse-text-status parse-text-failure-reason?)
	    (and (not link-to-default-p)
		 (parse-text-for-slot
		   (convert-text-string-to-text-macro
		     text-for-new-value) ; parse-text... reclaims
		   trend-chart
		   slot-description
		   t slot-component-type?
		   slot-component-name
		   slot-component-indicator?
		   t)))
	  (setf return-value
		(cond
		  ((or link-to-default-p parse-text-status)
		   (copy-evaluation-truth-value evaluation-true-value))
		  (t
		   (copy-evaluation-truth-value evaluation-false-value))))
	  (cond
	    (link-to-default-p
	     (let ((slot-component-features
		     (get-slot-component-features
		       slot-name nil slot-component-name)))
	       (unless (feature-assq 'not-editable-in-default slot-component-features)
		 (revert-slot-component-value
		   trend-chart slot-name nil
		   slot-component-name slot-component-indicator?))))
	    ((and (null parse-text-status) parse-text-failure-reason?)
	     (trend-chart-access-error parse-text-failure-reason?)
	     (reclaim-text-string parse-text-failure-reason?))) 
	  return-value)))))

(defun-for-system-procedure g2-add-trend-chart-component
    (trend-chart ev-attribute-name)
  (declare (keeps-g2-local-variables-valid t)) ; Verify this!  - cpm, 5/27/95
  (unless (and (of-class-p trend-chart 'trend-chart)
	       (evaluation-symbol-p ev-attribute-name))
    (reclaim-evaluation-value ev-attribute-name)
    (trend-chart-access-error "Bad args for g2-add-trend-chart-component"))
  (let ((slot-name
	  (get-trend-chart-slot-name-user-arg
	    trend-chart ev-attribute-name)))
    (ensure-trend-chart-compound-attribute-name slot-name)
    (unless (is-slot-multiple-compound-slot? slot-name nil)
      (trend-chart-access-error
	"Attribute cannot contain multiple components"))
    (add-instance-to-multiple-compound-slot-value
      trend-chart slot-name nil nil nil)))

#+development
(define-system-rpc-access (g2-add-trend-chart-component () ui-client-interface)
    ((trend-chart (class trend-chart))
     (attribute-name symbol))
  (g2-add-trend-chart-component
    trend-chart 
    attribute-name))

(defun-for-system-procedure g2-delete-trend-chart-component
    (trend-chart ev-attribute-name ev-slot-component-indicator)
  (declare (keeps-g2-local-variables-valid t)) ; Verify this!  - cpm, 5/27/95
  (unless (and (of-class-p trend-chart 'trend-chart)
	       (evaluation-symbol-p ev-attribute-name))
    (reclaim-evaluation-value ev-attribute-name)
    (trend-chart-access-error "Bad args for g2-add-trend-chart-component"))
  (let* ((slot-name
	   (get-trend-chart-slot-name-user-arg
	     trend-chart ev-attribute-name))
	 (slot-component-indicator?
	   (get-trend-chart-slot-component-indicator-user-arg
	     trend-chart slot-name ev-slot-component-indicator)))
    (ensure-trend-chart-compound-attribute-name slot-name)
    (unless (is-slot-multiple-compound-slot? slot-name nil)
      (trend-chart-access-error
	"Attribute cannot contain multiple components"))
    (ensure-trend-chart-slot-component-indicator
      ev-slot-component-indicator slot-component-indicator?)
    (unless (>f (slot-component-group-count
		  trend-chart slot-name nil))
      (trend-chart-access-error
	"Cannot delete last trend-chart component in attribute"))
    (remove-instance-from-multiple-compound-slot-value
      trend-chart slot-name nil slot-component-indicator?)))

(define-system-rpc-access (g2-delete-trend-chart-component () ui-client-interface)
    ((trend-chart (class trend-chart))
     (attribute-name symbol)
     (component-name-or-number item-or-datum))
  (g2-delete-trend-chart-component
    trend-chart 
    attribute-name
    component-name-or-number))


;;;; Native Printing Support


;;; The function `paint-graph-to-native-printer' replaces
;;; `paint-graph-rendering-raster' when drawing to a native printer. The main
;;; reason a special routine is required is to compute the graph edges (clipping
;;; region) before we enter the drawing loop. This routine is used for graphs,
;;; charts, and trend-charts.

(defun paint-graph-to-native-printer (graph-rendering)
  (let ((graph-grid-or-chart?
	  (corresponding-graph-grid-or-chart? graph-rendering))
	(one-message-block?
	  (or (graph-rendering-uses-polychrome-rasters? graph-rendering)
	      (graph-rendering-uses-monochrome-raster-lists? graph-rendering))))
    (multiple-value-bind (left-edge-in-window top-edge-in-window
					      right-edge-in-window bottom-edge-in-window)
	(cond ((null graph-grid-or-chart?))
	      ((frame-of-class-p graph-grid-or-chart? 'graph-grid)
	       (get-edges-of-graph-grid graph-grid-or-chart?
					(grid-border-width graph-rendering)))
	      ((frame-of-class-p graph-grid-or-chart? 'trend-chart)
	       (get-edges-of-trend-chart-grid graph-grid-or-chart?))
	      ((frame-of-class-p graph-grid-or-chart? 'chart)
	       (get-edges-of-chart-grid graph-grid-or-chart?)))
      (when left-edge-in-window
	(on-native-printer-with-drawing ()
	  (paint-icon-in-current-window ; New ICP message.
	    left-edge-in-window top-edge-in-window
	    left-edge-in-window top-edge-in-window
	    right-edge-in-window bottom-edge-in-window
	    (if one-message-block? 1 (length (color-values-for-rasters? graph-rendering)))))
	(let ((native-printing-icon-x-in-window left-edge-in-window)
	      (native-printing-icon-y-in-window top-edge-in-window))
	  (cond (one-message-block?
		 (paint-graph-from-graph-rendering graph-rendering nil t)
		 (send-icp-end-message-block))
		(t
		 (loop for foreground-color-value-for-current-raster
			   in (color-values-for-rasters? graph-rendering)
		       as first-time? = t then nil
		       do (paint-graph-from-graph-rendering 
			    graph-rendering 
			    foreground-color-value-for-current-raster first-time?)
			  (send-icp-end-message-block)))))))))

(defun get-edges-of-graph-grid (graph-grid grid-border-width)
  (values (+r (x-in-window (+w (left-edge-of-block graph-grid)
			       (graph-left-margin-width graph-grid)))
	      grid-border-width)
	  (+r (y-in-window (+w (top-edge-of-block graph-grid)
			       (graph-top-margin-width graph-grid)))
	      grid-border-width)
	  (-r (x-in-window (-w (right-edge-of-block graph-grid)
			       (graph-right-margin-width graph-grid)))
	      grid-border-width)
	  (-r (y-in-window (-w (bottom-edge-of-block graph-grid)
			       (graph-bottom-margin-width graph-grid)))
	      grid-border-width)))

(defun get-edges-of-trend-chart-grid (trend-chart)
  (with-focused-display-pane
      (trend-chart (get-grid-for-trend-chart trend-chart))
    (values (x-in-window current-display-pane-left)
	    (y-in-window current-display-pane-top)
	    (x-in-window current-display-pane-right)
	    (y-in-window current-display-pane-bottom))))

(defun get-edges-of-chart-grid (chart)
  (values (x-in-window (left-edge-of-block chart))
	  (y-in-window (top-edge-of-block chart))
	  (x-in-window (right-edge-of-block chart))
	  (y-in-window (bottom-edge-of-block chart))))

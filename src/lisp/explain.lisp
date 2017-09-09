;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module EXPLAIN

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Jim Allard






;;;; Explanation Facilities




;;; This module contains facilities related to explanations of rule and other
;;; processing within G2.  In the first versions the contents of this file will
;;; mostly contain NUPEC specific code.

;;; Now it will be for standard G2. -dkuznick, 7/15/98






;;;; Dynamic Backward Chaining Displays




;;; The following code implements a dynamic display of backward chaining trees
;;; for variables.  These trees will be updated from the functions
;;; execute-rules-for-backward-chaining, withdraw-backward-chaining, and
;;; put-current-value.

;;; The system-variable `backward-chaining-displays' is used to hold all
;;; currently active backward chaining display structures.

(def-system-variable backward-chaining-displays explain nil)




;;; The structure `backward-chaining-display' is used to hold the state of
;;; a backward chaining display.

(def-structure (backward-chaining-display
		 (:include dynamic-workspace-associated-structure)
		 (:constructor make-raw-backward-chaining-display
			       (backward-chaining-graph-display)))
  (backward-chaining-graph-display nil :reclaimer reclaim-graph-display))




;;; The function `make-backward-chaining-display' can be called to present
;;; a dynamically updated display of backward chaining for a variable.

(defun make-backward-chaining-display (variable)
  (let* ((graph-display (graph-frame-hierarchy
			  variable
			  `backward-chaining-display-children
			  nil
			  'backward-chaining-display-short-rep
			  ;hash-function
			  'backward-chaining-display-hash
			  ;defaults for orientation, vertical-spacing,
			  ;and horizontal-spacing
			  nil nil nil
			  ;pane-for-workspace-display?
			  current-workstation-detail-pane
			  ;class-of-workspace
			  'dynamic-temporary-workspace))
	 (dynamic-workspace (graph-display-workspace graph-display))
	 (display (make-raw-backward-chaining-display
			  graph-display)))
    (setf (reclaimer-for-dynamic-workspace-associated-structure display)
	  'remove-backward-chaining-display)
    (setf (associated-dynamic-structure dynamic-workspace)
	  display)
    (setq backward-chaining-displays
	  (gensym-cons display backward-chaining-displays))
    t))




;;; The function `backward-chaining-displays-of-variable' returns an eval
;;; cons list of the backward chaining displays which are currently
;;; executing for a particular variable.

(defun backward-chaining-displays-of-variable (variable)
  (loop for display in backward-chaining-displays
	when (eq variable
		 (graph-display-root-item
		   (backward-chaining-graph-display display)))
	  collect display using eval-cons))




;;; The function `delete-backward-chaining-display-if-any-for-variable' is
;;; used to remove any backward chaining dynamic displays currently being shown
;;; for a particular variable.

(defun delete-backward-chaining-display-if-any-for-variable (variable)
  (let ((displays-to-delete
	  (backward-chaining-displays-of-variable variable)))
    (when displays-to-delete
      (loop for display in displays-to-delete
	    do
	(delete-backward-chaining-display display))
      (reclaim-eval-list displays-to-delete))))




;;; The function `delete-backward-chaining-display' is used to delete a
;;; backward chaining display and the workspace on which the display is
;;; being shown.  The function remove-backward-chaining-display is called
;;; through the slot value reclaimers for the associated-dynamic-structure slot
;;; of the dynamic-temporary-workspace this display is shown upon.

(defun delete-backward-chaining-display
       (backward-chaining-display)
  (delete-frame
    (graph-display-workspace
      (backward-chaining-graph-display
	backward-chaining-display))))




;;; The function `remove-backward-chaining-display' is used to remove a
;;; backward chaining display from the global list and to reclaim the
;;; graph display structure.

(defun remove-backward-chaining-display (backward-chaining-display)
  (setq backward-chaining-displays
	(delete-gensym-element backward-chaining-display
			       backward-chaining-displays))
  (reclaim-backward-chaining-display backward-chaining-display))




;;; The function `update-backward-chaining-displays-function' takes either
;;; a variable or a rule instance and should update those displays which show
;;; this item.

(defun update-backward-chaining-displays-function (thing)
  (loop for bcd in backward-chaining-displays
	do
    (when (represented-in-graph-display-p
	    thing
	    (backward-chaining-graph-display bcd))
      (when (and (update-graph-display
		   (backward-chaining-graph-display bcd))
		 (dynamic-display-delay-in-milliseconds
		   debugging-parameters))
	(force-process-drawing)
	(c-uninterruptible-sleep
	  (dynamic-display-delay-in-milliseconds
		   debugging-parameters))))))



;;; The function `backward-chaining-display-children' should return a
;;; newly consed gensym list of the children of a variable or a rule instance in
;;; a backward chaining display.

(defun backward-chaining-display-children (thing ignored)
  (declare (ignore ignored))
  (cond ((rule-instance-p thing)
	 (loop for kid in (ri-things-this-rule-instance-is-interested-in thing)
	       when (not (memq kid collected-kids))
		 collect kid into collected-kids using gensym-cons
	       finally (return collected-kids)))
	((variable-p thing)
	 (loop for kid in (things-this-variable-is-interested-in thing)
	       when (not (memq kid collected-kids))
		 collect kid into collected-kids using gensym-cons
	       finally (return collected-kids)))
	(t nil)))




;;; The function `backward-chaining-display-short-rep' is called with a
;;; variable or a rule-instance and should return a frame which can be used as
;;; the display for that thing in a backward chaining tree.

(defun backward-chaining-display-short-rep (thing)
  (cond
    ((rule-instance-p thing)
     (if (or (null (ri-context thing))	;is this still the right test? -dkuznick, 7/13/98
	     (null (invocation-local-var-vector thing))) ;not testing this caused dieage on LOOP below
;	 (progn
;	   #+development
;	   (cerror "Continue" "NUPEC backward chaining NULL context case.")
;	   (make-explanation-table (ri-rule thing) nil))

	 ;; It looks to me like there's nothing wrong with having a NIL invocation-local-var-vector,
	 ;; so don't CERROR. -dkuznick, 7/13/98
	 (make-explanation-table (ri-rule thing) nil)
	 (loop with context = (invocation-local-var-vector thing)
	       with rule = (ri-rule thing)
	       with frame-serial-number = (ri-frame-serial-number thing)
	       with var-spot = (proc-list 'var-spot 0)
	       with environment-description =
	       (byte-code-body-environment-description
		 (rule-byte-code-body rule))
	       for index from 0 below (rule-context-length rule)
	       repeat (var-count environment-description)
	       for value = (svref context index)
	       for variable-name = (var-name-from-index
				     environment-description index)
	       for variable-description = (var-general-description-from-index
					    environment-description index)
	       do
	   (setf (second var-spot) index)
	       collect
	       (slot-value-list
		 (twith-output-to-text-string
		   (print-var-spot-for-stack-using-name-and-description
		     var-spot variable-name variable-description))
		 (twith-output-to-text-string
		   (cond
		     ((framep value)
		      (if (and frame-serial-number
			       (frame-has-been-reprocessed-p
				 value
				 frame-serial-number))
			  (
			   copy-constant-wide-string #w"no binding"
			   )
			  (tformat "~NF" value)))
		     (t
		      (write-stored-value value)))))
		 into binding-description using slot-value-cons
	       finally
		 (reclaim-proc-list var-spot)
		 (return 
		   (make-explanation-table rule binding-description)))))
    ((variable-p thing)
     (make-explanation-table thing))
    (t
     (make-explanation-table
       nil
       (slot-value-list (
                         copy-constant-wide-string #w"Unknown item"
                         ))))))




;;; The function `backward-chaining-display-hash' can receive either a
;;; rule-instance or a variable frame, and returns a hash number.  The hash for
;;; the rule instance is the hash of its context.  The hash for a variable frame
;;; is its frame serial number.

(defun backward-chaining-display-hash (thing)
  (cond ((rule-instance-p thing)
	 (ri-cached-context-hash-number thing))
	((variable-p thing)
	 (frame-hash thing))
	(t 0)))






;;;; Static Chaining Display




(declare-forward-reference
  collect-all-rules-for-forward-chaining function)	; queries

(declare-forward-reference
  collect-generic-formulas-for-variable function)	; queries




;;; The function `make-static-chaining-display' is used as a new describe
;;; like facility which will show a graph of the forward and backward
;;; chaining for a variable, with the forward chaining displayed above and the
;;; backward chaining below a description of the variable.

(defun make-static-chaining-display (variable)
  (let ((spacing 30)
	(forward-chaining
	  (describe-forward-chaining-short-reps variable))
	(backward-chaining
	  (describe-backward-chaining-short-reps variable))
	(variable-short-rep
	  (make-short-representation variable nil 'large))
	(workspace (make-workspace 'temporary-workspace)))
    (add-to-workspace
      variable-short-rep
      workspace
      (-f (halff (width-of-block variable-short-rep)))
      0
      nil
      nil)
    (when forward-chaining
      (let ((total-width
	      (static-display-total-width forward-chaining spacing))
	    (y (-f (top-edge-of-block variable-short-rep)
		   spacing
		   (static-display-maximum-height forward-chaining))))
	(loop with x fixnum = (-f (halff total-width))
	      for block in forward-chaining
	      do
	  (add-to-workspace block workspace x y nil nil)
	  (setq x (+f x spacing (width-of-block block))))
	(connect-superior-and-kid-frames
	  variable-short-rep 'inverted forward-chaining
	  workspace spacing spacing)
	(reclaim-eval-list forward-chaining)))
    (when backward-chaining
      (let ((total-width
	      (static-display-total-width backward-chaining spacing))
	    (y (+f (bottom-edge-of-block variable-short-rep)
		   spacing)))
	(loop with x fixnum = (-f (halff total-width))
	      for block in backward-chaining
	      do
	  (add-to-workspace block workspace x y nil nil)
	  (setq x (+f x spacing (width-of-block block))))
	(connect-superior-and-kid-frames
	  variable-short-rep 'vertical backward-chaining
	  workspace spacing spacing)
	(reclaim-eval-list backward-chaining)))
    (put-workspace-on-pane
      workspace
      current-workstation-detail-pane
      'left 'top t)
    nil))


(defun static-display-total-width (frames spacing)
  (+f (*f spacing (-f (length frames) 1))
      (loop for block in frames
	    sum (width-of-block block))))


(defun static-display-maximum-height (frames)
  (loop with max fixnum = 0
	for block in frames
	do
    (setq max (maxf max (height-of-block block)))
	finally (return max)))


;;; The function `describe-forward-chaining-short-reps' returns an eval
;;; cons list of the frames to show as the forward chaining of the given
;;; variable.

(defun describe-forward-chaining-short-reps (variable)
  (if (forward-chain-p variable)
      (multiple-value-bind (forward-chaining-rules-to-show
			     forward-chaining-rules)
	  (collect-all-rules-for-forward-chaining variable)
	(loop for frame in forward-chaining-rules-to-show do
	  (delete-frame frame))
	(reclaim-eval-list forward-chaining-rules-to-show)
	(loop for eval-cons on forward-chaining-rules do
	  (setf (car eval-cons)
		(make-short-representation (car eval-cons) nil 'small)))
	forward-chaining-rules)
      nil))




;;; The function `describe-backward-chaining-short-reps' returns an eval
;;; cons list of the frames to show as the backward chaining of the given
;;; variable.

(defun describe-backward-chaining-short-reps (variable)
  (if (not (or (passive-p variable)
	       (dont-backward-chain-p variable)
	       (neq (get-data-server variable) 'computation)))
      (let* ((frames-to-show nil)
	     (specific-formula? (car (formula? variable)))
	     (generic-formulas
              (when (null specific-formula?)
                (collect-generic-formulas-for-variable variable)))
	     (data-type (type-specification-of-variable-or-parameter-value
                         variable))
	     (backward-chaining-link-and-objects
              (unless (or specific-formula? generic-formulas)
                (let ((*links-and-objects* nil))
                  (collect-rules-for-backward-chaining variable data-type)
                  *links-and-objects*))))
	(cond (specific-formula?
	       (setq frames-to-show
		     (eval-list
                      (make-attributes-table
                       variable nil nil nil nil '(class formula?)))))
	      (generic-formulas
	       (setq frames-to-show
		     (eval-list
                      (make-short-representation
                       (car generic-formulas) nil 'small))))
	      (backward-chaining-link-and-objects
	       (setq frames-to-show
		     (loop for entry in backward-chaining-link-and-objects
			   collect
                           (make-short-representation
                            (backward-link-rule (car entry)) nil 'small)
                           using eval-cons))))
	(reclaim-eval-list generic-formulas)
	(reclaim-eval-tree backward-chaining-link-and-objects)
	frames-to-show)
    nil))

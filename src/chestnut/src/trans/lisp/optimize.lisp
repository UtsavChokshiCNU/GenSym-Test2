;;; -*- Mode: Lisp; Package: TIMPL; Syntax: Common-Lisp -*-
;;;
;;; optimize.lisp -- target-language to target-language transformations
;;;
;;; Author :  Andy Latto
;;; Date   :  24 September 1991
;;;
;;; Copyright (c) 1991, Chestnut Software Inc.
;;;
;;;


(in-package "TIMPL")

(himpl:note-rcs-revision
 "$Source: //gensym/ab-repos/chestnut/src/trans/lisp/optimize.lisp,v $"
 "$Revision: 1.9 $"
 "$Date: 2007/11/16 15:39:43 $")

(defvar *debugging-temps* nil)

(defvar *data-flow-computed-p* nil) 

#||(defvar *eliminate-dead-code-p* nil)||#


;;; Don't do flow-analysis or coalescing if compilation speed is 
;;; very important.
;;; If compilation speed is important but not very important, don't do
;;; coalescing in init functions, since they tend to be large and have lots
;;; of variables, and people don't look at them much.

;;; Allow control of this by declarations (for customers) and by a
;;; switch (for internal use, in controlling test suites)
;;; Possible values are t, nil, and :compilation-speed
(define-translator-parameter *compute-flow-p* :compilation-speed)
(define-translator-parameter *do-coalescing-p* :compilation-speed)

(define-translator-parameter *big-function-statement-count* 400)

;;; Code to determine whether optimization should occur.
(defun do-optimization-p (function switch)
  (let ((compilation-speed-importance
	 (cadr (assoc 'compilation-speed
		      (translator-declaration-information 'optimize))))
	(classification (function-record-classification function))
	(statements (function-record-statements function)))
    (or (cond ((>= compilation-speed-importance 3)
	       nil)
	      ((>= compilation-speed-importance 2)
	       (unless (eq :init classification)
		 switch))
	      ((>= compilation-speed-importance 1)
	       (if (eq :init classification)
		   (eq switch t)
		   switch))
	      (t
	       t))
	(< (length statements) *big-function-statement-count*))))
      

(defmacro compute-flow-p (function)
  `(do-optimization-p ,function *compute-flow-p*))

(defvar *do-temp-elimination-p* t)

(defmacro do-temp-elimination-p (function)
  `(and (compute-flow-p ,function) *do-temp-elimination-p*))

(defmacro do-coalescing-p (function)
  `(do-optimization-p ,function *do-coalescing-p*))

;;; Lists of closed and unclosed variables referenced in the current function
(defvar *closed-variables* nil)
(defvar *unclosed-variables* nil)

(defvar *enclosing-catches*)

;;; Setq's to closed variables (collected during pass1, since fixing
;;; closed variable setqs must be done before the flow analysis, since
;;; it invalidates it)

(defvar *closed-variable-setqs*)

(defparameter *fix-closed-variable-setqs* t)

(define-translator-parameter *using-with-protected-variables-p* t)

;;; This holds a list of (old-variable . new-variable) pairs. The
;;; actual coalescing must be done in the reverse order from the
;;; order in which they appear on this list.
(defvar *variable-coalescings* nil)

;;; This must be called exactly once on each statement-encloser pair.
;;; It also takes care of "un-eq-ifying" target code if requested,
;;; if the statement occurs in more than one place (which it detects by
;;; the fact that the enclosing slot is already full)
(defun record-encloser (statement encloser &optional (un-eq-ify nil))
  (when statement
    (when (and un-eq-ify
	       (enclosing-statement statement))
      ;; un-eq-ify
      (let ((new-statement (copy-target-form statement)))
	(target-form-replace-aux statement new-statement encloser)
	(setq statement new-statement)))
    (setf (target-info-enclosing-statement (target-info statement)) encloser)
    statement))


(defvar *optimize-function*)

;;; Note that "optimize" is something of a misnomer,
;;; since it must be called even with compilation-speed 3 and
;;; everything else 0, since it fixes setqs to closed variables to
;;; make them gc safe.


;;; Fixes closure references to make them gc-safe, and does various
;;; target-to-target source optimizations on function and all
;;; nested functions.

(defun optimize-function (function init-p)
  (when *debugging-temps* (break))
  (let ((*optimize-function* function)
	(*closed-variables* nil)
	(*unclosed-variables* nil)
	(*enclosing-catches* nil)
	(*variable-coalescings* nil)
	(*closed-variable-setqs* nil)
	(*data-flow-computed-p* nil))
    (pass1 function)
    (when *fix-closed-variable-setqs*
      (dolist (setq *closed-variable-setqs*)
	(fix-closed-variable-setq function setq)))
    (let ((global-closed-variables
	   (remove-if #'(lambda (vr)
			  (not (variable-record-actual-closed-p vr)))
		      *unclosed-variables*)))
      (setq *unclosed-variables* (nset-difference *unclosed-variables*
						  global-closed-variables))
      (setq *closed-variables* (nconc global-closed-variables
				      *closed-variables*)))
    ;; Should we be doing type-info-propagation for closed variables
    ;; as well? Hard to say. Probably not; It's hard, and the important
    ;; point here is to avoid protection of compiler-generated temps;
    ;; For variables visible in lisp, the user can insert type declarations
    ;; if he cares.
    (propagate-type-information *unclosed-variables* function)
    (when (compute-flow-p function)
      (compute-control-flow function)
      (compute-data-flow *closed-variables* function)
      (compute-data-flow *unclosed-variables* function)
      (setq *data-flow-computed-p* t))
    (when *rtl-includes-gc-p*
      (fix-self-nonconsing-p function)
      (if (and *using-with-protected-variables-p* (not init-p))
	  (add-with-protected-variables function)
	  (record-all-gc-protection-requirements function)))
    (record-all-setjmp-protection-requirements function)
    (when (do-temp-elimination-p function)
      (find-eliminatable-temps *unclosed-variables* function)
      (when (do-coalescing-p function)
	(coalesce-variables *unclosed-variables* function))
      (dolist (c (nreverse *variable-coalescings*))
	(do-coalescing (car c) (cdr c) function)))
    ;; Get rid of declarations for variables that have been eliminated
    ;; 'for free'
    (when (compute-flow-p function)
      (dolist (v *unclosed-variables*)
	(unless (or (variable-record-references v) (variable-record-setters v))
	  (eliminate-variable v function))))
    ;;(eliminate-tail-calls function)
    ))

(defun record-all-gc-protection-requirements (function &optional statement)
  (dolist (v *closed-variables*)
    (record-gc-protection-requirements v function statement))
  (dolist (v *unclosed-variables*)
    (record-gc-protection-requirements v function statement))
  (dolist (v (function-record-argument-variables function))
    (record-gc-protection-requirements v function statement)))

(defun record-gc-protection-requirements (var function &optional wpv-statement)
  (let* ((closed (variable-record-closed-p var))
	 (push (or wpv-statement (and closed function))))
    (if (requires-gc-protection var function wpv-statement)
	(if push
	    (let ((old (variable-record-needs-gc-protection var)))
	      (if (or (eq old t) (eq old nil))
		  (setf (variable-record-needs-gc-protection var)
			(list push))
		  (push push (variable-record-needs-gc-protection var))))
	    (setf (variable-record-needs-gc-protection var) t))
	(unless push
	  (setf (variable-record-needs-gc-protection var) nil)))))

(defun requires-gc-protection (variable function &optional statement)
  ;; Protection due to relocation
  (and (function-may-gc function)
       (eq (translator-foreign-type
	    (variable-record-foreign-type variable))
	   (translator-foreign-type :object))
       ;; It's possible to avoid protecting some closed variables, but
       ;; then the recording is more complicated, since the same
       ;; closed-over variable may require protection in one function
       ;; but not in another.
       (or (variable-record-closed-p variable)
	   (and (relocatable-contents variable)
		(if *data-flow-computed-p*
		    (exclude-statements-outside
		     (variable-record-live-relocating-statements variable)
		     statement)
		    t)))))

(defun record-all-setjmp-protection-requirements (function &optional statement)
  (dolist (v *closed-variables*)
    (record-setjmp-protection-requirements v function statement))
  (dolist (v *unclosed-variables*)
    (record-setjmp-protection-requirements v function statement))
  (dolist (v (function-record-argument-variables function))
    (record-setjmp-protection-requirements v function statement)))

(defun record-setjmp-protection-requirements (var function &optional
						  wpv-statement)
  (let* ((closed (variable-record-closed-p var))
	 (push (or wpv-statement (and closed function))))
    (if (requires-setjmp-protection var wpv-statement)
	(if push
	    (let ((old (variable-record-needs-setjmp-protection var)))
	      (if (or (eq old t) (eq old nil))
		  (setf (variable-record-needs-setjmp-protection var)
			(list push))
		  (push push 
			(variable-record-needs-setjmp-protection var))))
	    (setf (variable-record-needs-setjmp-protection var) t))
	(unless push
	  (setf (variable-record-needs-setjmp-protection var) nil)))))

(defun requires-setjmp-protection (variable &optional statement)
  ;; Protection due to setjmp
  ;; Note that non-object variables may require setjmp protection.
  ;; Since there is currently no mechanism to provide such protection,
  ;; it's the emitter's job to complain about this, not this function's.
  ;; -> in this case, the emiter should make the variable be volatile.
  (let* ((dangerous-setjmps
	  (exclude-statements-outside
	   (variable-record-dangerous-setjmps variable)
	   statement))
	 (live-setjmps
	  (if *data-flow-computed-p*
	      (variable-record-live-setjmp-statements variable)
	      dangerous-setjmps)))
    (dolist (ds dangerous-setjmps nil)
      (when (dolist (ls live-setjmps nil)
	      (when (eq ls ds) (return t)))
	(return t)))))

;;; First pass is responsible for setting up the enclosing-statements
;;; links from each statement to its parent (and from top-level-statements
;;; to a special marker). It also does a sort of a gathering, to
;;; find the local-variables contained in the code. It returns two
;;; values, a list of non-closed-over local variables, and a list
;;; of closed-over local-variables.

;;; The first pass is also responsible for making sure that no two
;;; statements in the function are eq, since if they were, we
;;; wouldn't have the two independent target-info structs to record
;;; data in. Some codewalker apparently does make a target form, and then
;;; stick it in in two separate places; ugh! I think the walkers
;;; should not do this; but the expedient fix is to un-eq things here.

(defun record-variable (variable)
  (let ((closed-p (variable-record-closed-p variable)))
    (unless (memq variable (if closed-p
			       *closed-variables*
			       *unclosed-variables*))
      (if closed-p
	  (push variable *closed-variables*)
	  (push variable *unclosed-variables*))
      ;; get rid of data-flow information from other functions containing
      ;; these variables
      (setf (variable-record-setters variable) nil)
      (setf (variable-record-references variable) nil)
      (setf (variable-record-dangerous-setjmps variable) nil))))

(defun pass1 (function)
  (dolist (statement (function-record-statements function))
    (pass1-aux statement function))
  (dolist (variable (function-record-local-variables function))
    (record-variable variable)))

(defun pass1-aux (statement &optional encloser lvalue-p)
  (when statement
    (when encloser
      (setq statement (record-encloser statement encloser t)))
    (case (target-form-type statement)
      (local-variable
       (let ((var (second statement)))
	 (record-variable var)
	 (when (and (eq lvalue-p 'setq)
		    (variable-record-closed-p var)
		    (not (nonrelocating-expression-p encloser)))
	   (when *fix-closed-variable-setqs*
	     (push encloser *closed-variable-setqs*))))
       (record-variable-reference statement lvalue-p))
      (with-lexical-bindings
       (dolist (variable (second statement))
	 (record-variable variable))
       (dolist (substatement (cddr statement))
	 (pass1-aux substatement statement)))
      (setq
       (pass1-aux (second statement) statement 'setq)
       (pass1-aux (third statement) statement))
      (values-assign
       (dolist (substatement (cdr statement))
	 (pass1-aux substatement statement 'values-assign)))
      (with-catch
       (pass1-aux (third statement) statement) ; tag
       (let ((*enclosing-catches* (cons statement *enclosing-catches*)))
	 (pass1-aux (fourth statement) statement)) ; body
       (pass1-aux (fifth statement) statement)) ; catch statement
      (with-unwind-protect
       (let ((*enclosing-catches* (cons statement *enclosing-catches*)))
	 (pass1-aux (third statement) statement)) ; body
       (pass1-aux (fourth statement) statement)) ; protected
      (t
       (dolist (substatement (substatements statement))
	 (pass1-aux substatement statement))))))

;;; Currently we only record references for local variables.
;;; Recording (and doing any kind of data-flow analysis) for
;;; specials would require more work, since the target language
;;; only contains the symbol, not a record.

(defun record-variable-reference (statement lvalue-p)
  (if lvalue-p
      (progn
	(push (enclosing-statement statement)
	      (variable-record-setters (second statement)))
	(dolist (catch *enclosing-catches*)
	  (pushnew catch (variable-record-dangerous-setjmps
			  (second statement))))
	(setf (lvalue-p statement) t))
      (push statement (variable-record-references (second statement)))))

(defun fix-closed-variable-setq (function setter)
  (let* ((*current-function* function)
	 (temp (allocate-temporary))
	 (assign-temp (make-target-form
		       'setq
		       (make-target-form 'local-variable temp)
		       (third setter)))
	 (assign-closed (make-target-form
			 'setq
			 (second setter)
			 (make-target-form 'local-variable temp))))
    (push temp (function-record-local-variables function))
    (let ((new-statement
	   (if (statement-context-p setter)
	       (make-target-form 'compound-statement
				 assign-temp
				 assign-closed)
	       (make-target-form 'comma-operator
				 assign-temp
				 assign-closed))))
      (pass1-aux new-statement)
      (target-form-replace setter new-statement))))

;;;
;;; Control flow
;;;

(defun compute-control-flow (function)
  (let ((*function-entry* (make-flow-node))
	(*function-exit* (make-flow-node))
	(*nonlocal-entries* (list (make-flow-node)))
	(*break-destination* nil)
	(*enclosing-catches* nil))
    (multiple-value-bind (in outs)
	(do-straight-flow (function-record-statements function))
      (record-flow *function-entry* in)
      (record-flows outs *function-exit*))
    (setf (function-record-flow-entry function) *function-entry*)
    (setf (function-record-flow-exit function) *function-exit*)))

;;;
;;; Data flow
;;;

(defun compute-data-flow (variables function)
  (dolist (variable variables)
    (propagate-liveness variable function)))
   
;;; We record liveness at flow-nodes and call-exit and call-entry nodes
;;; to avoid infinite loops in propagate-liveness due to loops that
;;; contain no actual statements.
(defun record-liveness (variable statement)
  "records that variable is live at statement"
  (cond ((consp statement)
	 (push variable (live-variables statement))
	 (when (relocating-statement-p statement)
	   (push statement
		 (variable-record-live-relocating-statements variable)))
	 (case (target-form-type statement)
	   ((setq values-assign)
	    (push statement
		  (variable-record-live-setter-statements variable)))
	   ((with-catch with-unwind-protect)
	    (push statement
		  (variable-record-live-setjmp-statements variable)))))
	(t
	 (push variable (basic-flow-node-live-variables statement)))))

;;; and can be checked during data-flow-analysis by

(defun check-liveness (variable statement)
  "determines whether variable is live at statement"
  (cond ((consp statement)
	 (eq variable (car (live-variables statement))))
	((flow-node-p statement)
	 (eq variable (car (flow-node-live-variables statement))))
	((call-entry-p statement)
	 (eq variable (car (call-entry-live-variables statement))))
	((call-exit-p statement)
	 (eq variable (car (call-exit-live-variables statement))))
	(t (error "Unrecognized entry ~A in flow graph" statement))))

;;; NB. For efficiency of data flow analysis, (check-liveness v s) may
;;; assume that if (record-liveness v s) has been called, then
;;; (record-liveness v1 s) has not been called subsequently for any
;;; distinct value of v1. This suggests that we record everything
;;; on the statements, so we can use this hack.
;;; This probably makes for more efficient use, as well, since
;;; we are usually checking for null intersection of
;;; a live set (a big set) with the set of references to a given variable
;;; (a small set). Since we want to loop through the small set,
;;; we should have a fast answer to "Is v live here?", but don't
;;; necessarily need a fast answer to "where is v live?"

;;; Records all statements s such that there is a data-flow path
;;; from an lvalue reference to v, followed by a path containing
;;; no further lvalue references, arriving at an rvalue reference
;;; to v. Data-flow paths must obey call-node semantics; that is, a
;;; valid path must traverse all the in arcs from a call-entry to the
;;; call-exit before it can continue to the call itself.

;;; We make the arbitrary choice that a variable is considered "live"
;;; at its final use, but not at the setq statement that
;;; assigns it a value; That is, a variable is "live" at a statement
;;; if a change to the value of the variable just *before* the statement
;;; would affect the result.


;;; Helper function for the above

;;; This propagates (backwards, through in links)
;;; calling record-liveness as appropriate, stopping
;;; at elements of the list stoppers, but it is
;;; not allowed to mark the node goal (typically a call-entry node)
;;; It returns t if it found a path to goal (that is, if
;;; it would have marked stopper unless the contract
;;; prohibited it)

(defun propagate-liveness (variable function)
  ;; remove information from other functions using this variable.
  (setf (variable-record-live-setter-statements variable) nil
	(variable-record-live-relocating-statements variable) nil
	(variable-record-live-setjmp-statements variable) nil)
  (propagate-liveness-aux
   (variable-record-references variable)
   (if (memq variable (function-record-argument-variables function))
       (cons (function-record-flow-entry function)
	     (variable-record-setters variable))
       (variable-record-setters variable))
   variable))

(defun propagate-liveness-aux (starters stoppers variable &optional goal)
  (flet ((mark-call-exit (call-exit &optional except-entry)
	   (let ((entry (call-exit-call-entry call-exit))
		 (blocked nil))
	     (dolist (arg (flow-in call-exit))
	       (unless (or (and except-entry
				(eq except-entry
				    (flow-node-corresponding-entry arg)))
			   (propagate-liveness-aux
			    (list arg) stoppers variable entry))
		 (setq blocked t)))
	     (dolist (arg (call-exit-maybe-in call-exit))
	       (propagate-liveness-aux (list arg) stoppers variable entry))
	     (unless (or blocked except-entry)
	       (if goal
		   (progn
		     (record-liveness variable entry)
		     (setq starters (append (flow-in entry) starters)))
		   (push entry starters))))))
    (let ((goal-reached nil))
      (loop
       (unless starters (return goal-reached))
       (let ((s (pop starters)))
	 (if (eq s goal) (setq goal-reached t)
	     (unless (or (check-liveness variable s)
			 (member s stoppers :test #'eq))
	       (unless (lvalue-p s)
	         (record-liveness variable s))
	       ;;(when (and (call-entry-p s) goal)
	       ;;  (error "Unexpected call-entry node found"))
	       (if (call-exit-p s)
		   (mark-call-exit s)
		   (dolist (previous (flow-in s))
		     (push previous starters)
		     (when (and (null goal) (call-entry-p previous))
		       ;; Need to mark the other args, but not this one, 
		       ;; since they may have been evaluated first.
		       (mark-call-exit (call-entry-call-exit previous)
				       s)))))))))))


;;; Temp elimination proper

;;; When it has been decided to eliminate a variable, references
;;; to that variable are not immediately removed from the target code,
;;; since we don't want to mess with it (and invalidate control flow)
;;; until we have done all analysis that requires the flow info.
;;; So all code in this phase should use these functions, to ensure
;;; that they obtain the variable record for the variable currently
;;; in use.

(defmacro current-variable (v)
  (once-only (v)
    `(or (variable-record-coalesced-to ,v) ,v)))

(defmacro form-to-variable (form)
  `(current-variable (cadr ,form)))

(defmacro do-candidate-targets ((targetvar variable &rest result) &body body)
  (let ((settervar (gensym))
	(refsvar (gensym)))
    `(progn
       (dolist (,targetvar (variable-record-try-coalescing-to ,variable))
	 (unless (confusing-to-coalesce ,variable ,targetvar :hint)
	   ,@body))
       (dolist (,settervar (variable-record-setters ,variable))
	 (dolist (,targetvar (right-hand-side-vars ,settervar))
	   (unless (confusing-to-coalesce ,variable ,targetvar :var=target)
	     ,@body)))
       (dolist (,refsvar (variable-record-references ,variable))
	 (dolist (,targetvar (left-hand-side-vars ,refsvar))
	   (unless (confusing-to-coalesce ,variable ,targetvar :target=var)
	     ,@body)))
       #+code-motion-implemented
       (let ((,settervar (variable-record-setters ,variable)))
	 (when (and ,settervar (null (cdr ,settervar)))
	   (let ((,targetvar (car ,settervar)))
	     ,@body)))
       ,@result)))

(defun find-eliminatable-temps (candidates function)
  (dolist (variable candidates)
    (let ((target
	   (block found-a-target
	     (do-candidate-targets (target variable nil)
	       (when (coalescable variable target function)
		 (return-from found-a-target target))))))
      (when target
	(record-coalescing variable target function)))))

;;; Returns a list of variables to try coalescing variable to, in order
;;; of preference. Duplicates will not cause incorrect code; they
;;; just cause inefficiency, as it fails and tries again.
;;; This function makes no guarantees about the appropriateness of the
;;; candidates it returns; it merely makes suggestions.

;;; Iterates over possible targets to coalesce a variable to.
;;; Executes body with targetvar bound to each reasonable target, in
;;; order of preference.

;;; Does not guarantee that body will be executed only once for a given
;;; target. Duplicates will not cause incorrect code; they
;;; just cause inefficiency, as it fails and tries again.
;;; This macro is in charge of avoiding "confusing" coalescings,
;;; but not semantically incorrect ones.

;;; This is obsolete; use do-candidate-targets instead, to avoid huge
;;; amounts of unnecessary consing.

(defun candidate-targets (variable)
  (let ((setters (variable-record-setters variable))
	(references (variable-record-references variable)))
    (append (remove-if #'(lambda (target)
			   (confusing-to-coalesce variable target :hint))
		       (variable-record-try-coalescing-to variable))
	    (remove-if #'(lambda (target)
			   (confusing-to-coalesce variable target :var=target))
		       (mapcan #'right-hand-side-vars setters))
	    (remove-if #'(lambda (target)
			   (confusing-to-coalesce variable target :target=var))
		       (mapcan #'left-hand-side-vars references))
	    #+code-motion-implemented
	    (and setters (null (cdr setters))
		 (final-right-hand-side (car setters))))))

;;; Don't coalesce if this will generate "new" assignments to
;;; "semantically meaningful" variables which won't later be optimized
;;; away by optimize-setter.


;;; Reasons should be one of the keywords
;;; :hint --- the try-coalescing-to slot on variable contained this
;;; variable (a hint from the codewalker as to what would look good)
;;; :var=target --- the target appears among the right-hand-side-vars of
;;; an assignment to variable.
;;; :target=var --- the target appears among the left-hand-side-vars of
;;; a reference to the variable.

(defmacro semantically-meaningful (variable)
  `(symbol-package (variable-record-name ,variable)))

(defun confusing-to-coalesce (variable target reason)
  (and (semantically-meaningful target)
       (ecase reason
	 (:hint nil)
	 (:var=target
	  (dolist (setter (variable-record-setters variable) nil)
	    (when (and (dolist (var (right-hand-side-vars setter) t)
			 (when (or (eq var target) (eq var variable))
			   (return nil)))
		       (dolist (var (left-hand-side-vars setter) t)
			 (when (eq var target)
			   (return nil))))
	      (return t))))
	 (:target=var
	  (dolist (reference (variable-record-references variable) nil)
	    (when (dolist (var (left-hand-side-vars reference) t)
		    (when (or (eq var target) (eq var variable))
		      (return nil)))
	      (return t)))))))

;;; These two functions let us consider coalescing t to either x or y
;;; when we see t=x=y. This is where the smarts (real dataflow analysis
;;; for basic blocks) needs to be put in to coalesce t to x when
;;; the code says y=x;t=x.
(defun right-hand-side-vars (setter)
  (ecase (target-form-type setter)
    (setq
     (let ((rhs (third setter)))
       (case (target-form-type rhs)
	 (local-variable
	  (values (list (form-to-variable rhs)) t))
	 (setq
	  (multiple-value-bind (vars all-p)
	      (right-hand-side-vars rhs)
	    (let ((inner-lhs (second rhs)))
	      (if (eq (target-form-type inner-lhs) 'local-variable)
		  (values (cons (form-to-variable inner-lhs) vars) all-p)
		  (values vars nil)))))		  
	 (t
	  (values nil nil)))))
    (values-assign (values nil nil))))

(defun final-right-hand-side (setter)
  (ecase (target-form-type setter)
    (setq
     (let ((rhs (third setter)))
       (if (eq (target-form-type rhs) 'setq)
	   (final-right-hand-side rhs)
	   rhs)))
    (values-assign nil)))

;;; This is to let us consider coalescing t to either x or y
;;; when we see x=y=t.
(defun left-hand-side-vars (form)
  (let ((encloser (enclosing-statement form)))
    (when (and (consp encloser)
	       (eq (target-form-type encloser) 'setq))
      (if (eq (target-form-type (second encloser)) 'local-variable)
	  (cons (form-to-variable (second encloser))
		(left-hand-side-vars encloser))
	  (left-hand-side-vars encloser)))))

(defparameter *adjustable-arrays*
  (make-resource "Adjustable Arrays"
		 :constructor
		 #'(lambda () (make-array 0 :adjustable t :fill-pointer 0 :initial-element nil))
		 :initial-copies 20
		 :initialization-function
		 #'(lambda (x) (setf (fill-pointer x) 0) x)
		 :cleanup-function
		 #'(lambda (x)
		     (dotimes (i (array-dimension x 0))
		       (setf (aref x i) nil))
		     x)))

(define-translator-parameter *coalesce-variables-with-different-names-p* nil)
(define-translator-parameter *coalesce-internal-variables-with-different-names-p* nil)
(define-translator-parameter *coalesce-setf-variables-with-different-names-p* t)

(defun name-for-coalesce-test (variable &optional key-p)
  (or *coalesce-variables-with-different-names-p*
      (and key-p *coalesce-internal-variables-with-different-names-p*)
      (if (or (variable-record-compiler-generated-temp-p variable)
	      (null (symbol-package (variable-record-name variable))))
	  (or *coalesce-internal-variables-with-different-names-p*
	      (let ((var (variable-record-name variable)))
		(or (and *coalesce-setf-variables-with-different-names-p*
			 (translator-setf-method-temp-var-p var))
		    (symbol-name var))))
	  (variable-record-name variable))))

(defun temp-var-p (variable)
  (or (variable-record-compiler-generated-temp-p variable)
      (null (symbol-package (variable-record-name variable)))))

;;; This tries to coalesce away temps, and anything that has the
;;; same name as something else.
(defun coalesce-variables (vars function)
  ;; If vars might contain duplicates, we must do:
  ;;(setq vars (remove-duplicates vars))
  (let ((alist nil)
	(args (function-record-argument-variables function)))
    (dolist (variable vars)
      (unless (or (variable-record-closed-p variable)
		  (variable-record-coalesced-to variable))
	(let ((key (list (name-for-coalesce-test variable t)
			 (null (variable-needs-gc-protection variable
							     function))
			 (variable-record-foreign-type variable)
			 (variable-record-in-function variable))))
	  (let ((a (assoc key alist :test #'equal)))
	    (unless a
	      (push (setq a (cons key (resource-allocate *adjustable-arrays*)))
		    alist))
	    (vector-push-extend variable (cdr a))))))
    (dolist (a alist)
      (let ((tail (cdr a)))
	(do ((variables tail to-coalesce)
	     (to-coalesce (resource-allocate *adjustable-arrays*)
			  (progn (setf (fill-pointer variables) 0) variables)))
	    ((zerop (length variables))
	     (resource-deallocate *adjustable-arrays* variables)
 	     (resource-deallocate *adjustable-arrays* to-coalesce))
	  (let ((target (aref variables 0)))
	    (dotimes (i (length variables))
	      (unless (zerop i)
		(let ((variable (aref variables i)))
		  (if (and (coalescable-internal variable target)
			   (progn
			     (when (or (member variable args)
				       (and (not (member target args))
					    (not (temp-var-p variable))
					    (temp-var-p target)))
			       (rotatef variable target))
			     (not (member variable args))))
		      (progn
			(record-coalescing variable target function)
			(unless (or (symbol-package
				     (variable-record-name target))
				    (equal
				     (symbol-name
				      (variable-record-name variable))
				     (symbol-name
				      (variable-record-name target))))
			  (setf (variable-record-name target)
				(make-symbol "TEMP"))))
		      (vector-push-extend variable to-coalesce)))))))))))

;;; This is coalescable, but without checks that can be done individually
;;; for target and variable; these are done above in coalesce-variables for
;;; speed.

(defun coalescable-internal (variable target)
  (and (coalescable-internal-1 variable target)
       (coalescable-internal-1 target variable)))

(defun coalescable-internal-1 (var1 var2)
  (let ((live1 (variable-record-live-setter-statements var1))
	(setters1 (variable-record-setters var1)))
    (dolist (setter (variable-record-setters var2) t)
      (unless (dolist (var (right-hand-side-vars setter) nil)
		(when (or (eq var var1) (eq var var2))
		  (return t)))
	(dolist (stmt live1)
	  (when (eq stmt setter)
	    (return-from coalescable-internal-1 nil)))
	(dolist (stmt setters1)
	  (when (eq stmt setter)
	    (return-from coalescable-internal-1 nil)))))))

;;; Can variable be replaced by target throughout the code for function without
;;; affecting semantics?
;;; avoids considering "t=t" statements as obstacles to coalescing.
;;; This is only really necessary as long as record-coalescing is
;;; conservative in the way it currently is.
(defun coalescable (variable target function)
  (if (and (not (eq variable target))
	   (variable-record-p target)
	   (not (variable-record-closed-p target))
	   (not (variable-record-coalesced-to target))
	   (not (member variable
			(function-record-argument-variables function)))
	   (let ((vname (name-for-coalesce-test variable)))
	     (or (eq vname 't)
		 (equal vname (name-for-coalesce-test target))))
	   (not (variable-record-closed-p variable))
	   (not (variable-record-coalesced-to variable))
	   (eq (variable-record-foreign-type variable)
	       (variable-record-foreign-type target))
	   (eq (variable-record-in-function variable)
	       (variable-record-in-function target))
	   (or (eq (null (variable-needs-gc-protection variable function))
		   (null (variable-needs-gc-protection target function)))
	       (and (variable-needs-gc-protection target function)
		    (let ((references (variable-record-references variable)))
		      (or (null references)
			  (null (cdr references)))))))
      (coalescable-internal variable target)
      ;; Code for replacing a local unclosed variable by
      ;; anything more complex than another local unclosed variable
      ;; goes here; (though some of the above error checking
      ;; will have to be repeated); for now, we always fail.
      nil))

(defun ngcp-to-list (ngcp)
  (and (listp ngcp) ngcp))

;;; This is responsible for updating the variable record of target
;;; to contain accurate values representing the state of the target
;;; language after the coalescing has taken place, and for recording in
;;; the variable's record that it has been coalesced to target.
(defun record-coalescing (variable target function &optional
				   (preserve-protection-info nil))
  (declare (ignore function))
  (push (cons variable target) *variable-coalescings*)
  (setf (variable-record-coalesced-to variable) target)
  (push variable (variable-record-coalesced-from target))
  (dolist (v (variable-record-coalesced-from variable))
    (push v (variable-record-coalesced-from target)))
  ;; Note that this assumes we are only coalescing unclosed variables.
  (when (variable-record-needs-gc-protection variable)
    (let ((new (unionq (ngcp-to-list
			(variable-record-needs-gc-protection target))
		       (ngcp-to-list
			(variable-record-needs-gc-protection variable)))))
      (setf (variable-record-needs-gc-protection target) (or new t))))
  ;; Note that the next three are conservative; a v=t is not
  ;; a setter for the coalesced variable, and is not even a reference
  ;; or a live statement if not in value context.
  ;; Is this conservatism OK, or will bogus setters and references
  ;; screw up do-coalescing??? Need to check, and be careful in the future.
  (unionqf (variable-record-references target)
	   (variable-record-references variable))
  (unionqf (variable-record-setters target)
	   (variable-record-setters variable))
  (unionqf (variable-record-live-setter-statements target)
	   (variable-record-live-setter-statements variable))
  (when preserve-protection-info
    (unionqf (variable-record-live-setjmp-statements target)
	     (variable-record-live-setjmp-statements variable))
    (unionqf (variable-record-live-relocating-statements target)
	     (variable-record-live-relocating-statements variable))))
  
;;; Here is where we actually mung the target language and eliminate
;;; the temp; Since this destroys the control and data flow information,
;;; it shouldn't be done until we no longer need that information.

(defun do-coalescing (variable target function)
  (dolist (setter (variable-record-setters variable))
    (ecase (target-form-type setter)
      (setq
       (setf (second (second setter)) target))
      (values-assign
       (dolist (lvalue (cdr setter))
	 (when (and (eq (target-form-type lvalue) 'local-variable)
		    (eq (second lvalue) variable))
	   (setf (second lvalue) target))))))
  (dolist (reference (variable-record-references variable))
    (setf (second reference) target))
  ;; Some v = t or t = v statements have now become v=v: optimize these out.
  (mapc #'optimize-setter (variable-record-setters variable))
  (mapc #'optimize-setter (variable-record-setters target))
  ;; Make sure no declaration is generated for eliminated variable
  (eliminate-variable variable function))

(defun eliminate-variable (variable function)
  (let ((binder (variable-record-binder variable)))
    (if binder
	(setf (second binder)
	      (delete variable (second binder)))
	(setf (function-record-local-variables function)
	      (delete variable (function-record-local-variables function))))))

(defun optimize-setter (setter)
  (when (and (eq (target-form-type setter) 'setq)
	     (eq (target-form-type (second setter)) 'local-variable)
	     (memq (form-to-variable (second setter))
		   (right-hand-side-vars setter)))
    ;; Remove this setq.
    (let ((lhs-var (form-to-variable (second setter))))
      (setf (variable-record-setters lhs-var)
	    (delete setter (variable-record-setters lhs-var)))
      (if (and (eq (target-form-type (third setter)) 'local-variable)
	       (not (setq-in-value-context-p setter)))
	  ;; Remove the setq completely
	  (progn (remove-form setter)
		 (setf (variable-record-references lhs-var)
		       (delete (third setter)
			       (variable-record-references lhs-var))))
	  ;; Replace setq by rhs
	  (target-form-replace setter (third setter))))))

;;; Protection

;;; Switch to turn off smart protection-elimination
(defvar *eliminate-protection* t)

(defun record-all-protection-requirements (function &optional statement)
  (dolist (v *closed-variables*)
    (record-protection-requirements v function statement))
  (dolist (v *unclosed-variables*)
    (record-protection-requirements v function statement))
  (dolist (v (function-record-argument-variables function))
    (record-protection-requirements v function statement)))

(defun reset-all-protection-requirements (function)
  (dolist (v *closed-variables*)
    (reset-protection-requirements v))
  (dolist (v *unclosed-variables*)
    (reset-protection-requirements v))
  (dolist (v (function-record-argument-variables function))
    (reset-protection-requirements v)))

(defun reset-gc-protection-requirements (var)
  (when (not (variable-record-closed-p var))
    (setf (variable-record-needs-gc-protection var) nil)))

(defun reset-all-gc-protection-requirements (function)
  (dolist (v *closed-variables*)
    (reset-gc-protection-requirements v))
  (dolist (v *unclosed-variables*)
    (reset-gc-protection-requirements v))
  (dolist (v (function-record-argument-variables function))
    (reset-gc-protection-requirements v)))

(defun add-with-protected-variables (function)
  (reset-all-gc-protection-requirements function)
  (add-with-protected-variables1 function function))

(defun add-with-protected-variables1 (tail function)
  (let* ((fr-p (function-record-p tail))
	 (statements (if fr-p
			 (function-record-statements function)
			 (cdr tail))))
    (loop (unless statements (return nil))
	  (let ((statement (car statements)))
	    (cond ((not (or (relocating-p statement)
			    (eq 'labeled-statement
				(target-form-type statement))))
		   (setq fr-p nil)
		   (setq tail statements)
		   (setq statements (cdr statements)))
		  ((null (cdr statements))
		   (add-with-protected-variables2 statement function)
		   (return nil))
		  (t
		   (let* ((encloser (enclosing-statement
				     (car statements)))
			  (new (apply-make-target-form
				'with-protected-variables
				statements))
			  (new-statements (list new)))
		     (setf (target-info-enclosing-statement
			    (target-info new))
			   encloser)
		     (dolist (statement statements)
		       (setf (target-info-enclosing-statement
			      (target-info statement))
			     new))
		     (if fr-p
			 (setf (function-record-statements tail)
			       new-statements)
			 (setf (cdr tail) new-statements))
		     (record-all-gc-protection-requirements function new))
		   (return nil)))))))

(defun add-with-protected-variables2 (statement function)
  (case (target-form-type statement)
    ((return-value return-values return-stored-values))
    (with-lexical-bindings
     (if (with-lexical-binding-relocates-p statement)
	 (add-with-protected-variables3 statement function)
	 (add-with-protected-variables1 (cdr statement) function)))
    (if-statement
     (if (relocating-p (cadr statement))
	 (add-with-protected-variables3 statement function)
	 (progn
	   (add-with-protected-variables2 (caddr statement) function)
	   (add-with-protected-variables2 (cadddr statement) function))))
    (compound-statement
     (add-with-protected-variables1 statement function))
    (t
     (add-with-protected-variables3 statement function))))

(defun add-with-protected-variables3 (statement function)
  (let ((new (make-target-form 'with-protected-variables statement)))
    (target-form-replace statement new)
    (record-all-gc-protection-requirements function new)))

;;; For unclosed variables, the needs-gc-protection slot holds t or nil.
;;; For closed variables, it holds a list of functions in which the variable
;;; must be protected.

(defun variable-needs-gc-protection (v wpv-or-function)
  (let ((info (variable-record-needs-gc-protection v)))
    (or (eq info t)
	(memq wpv-or-function info))))

(defun variable-needs-setjmp-protection (v wpv-or-function)
  (let ((info (variable-record-needs-setjmp-protection v)))
    (or (eq info t)
	(memq wpv-or-function info))))

(defun reset-protection-requirements (var)
  (when (not (variable-record-closed-p var))
    (setf (variable-record-needs-gc-protection var) nil)))

(defun record-protection-requirements (var function &optional wpv-statement)
  (let* ((closed (variable-record-closed-p var))
	 (push (or wpv-statement (and closed function))))
    (if (requires-protection var function wpv-statement)
	(if push
	    (let ((old (variable-record-needs-gc-protection var)))
	      (if (or (eq old t) (eq old nil))
		  (setf (variable-record-needs-gc-protection var)
			(list push))
		  (push push (variable-record-needs-gc-protection var))))
	    (setf (variable-record-needs-gc-protection var) t))
	(unless push
	  (setf (variable-record-needs-gc-protection var) nil)))))

(defun requires-protection (variable function &optional statement)
  (or (not *eliminate-protection*)
      ;; Protection due to relocation
      (and (function-may-gc function)
	   (eq (translator-foreign-type (variable-record-foreign-type variable))
	       (translator-foreign-type :object))
	   ;; It's possible to avoid protecting some closed variables, but
	   ;; then the recording is more complicated, since the same
	   ;; closed-over variable may require protection in one function
	   ;; but not in another.
	   (or (variable-record-closed-p variable)
	       (and (relocatable-contents variable)
		    (if *data-flow-computed-p*
			(exclude-statements-outside
			 (variable-record-live-relocating-statements variable)
			 statement)
			t))))
      ;; Protection due to setjmp
      ;; Note that non-object variables may require setjmp protection.
      ;; Since there is currently no mechanism to provide such protection,
      ;; it's the emitter's job to complain about this, not this function's.
      ;; -> in this case, the emiter should make the variable be volatile.
      (and (not (variable-record-closed-p variable))
	   (let* ((dangerous-setjmps
		   (exclude-statements-outside
		    (variable-record-dangerous-setjmps variable)
		    statement))
		  (live-setjmps
		   (if *data-flow-computed-p*
		       (variable-record-live-setjmp-statements variable)
		       dangerous-setjmps)))
	     (dolist (ds dangerous-setjmps nil)
	       (when (dolist (ls live-setjmps nil)
		       (when (eq ls ds) (return t)))
		 (return t)))))))

(defun exclude-statements-outside (statements include-statement)
  (if include-statement
      (mapcan #'(lambda (statement)
		  (when (statement-within-statement-p statement
						      include-statement)
		    (list statement)))
	      statements)
      statements))

(defun statement-within-statement-p (statement include-statement)
  (or (eq statement include-statement)
      (dolist (substatement (substatements include-statement) nil)
	(when (and substatement
		   (statement-within-statement-p statement substatement))
	  (return t)))))

;;; Something better is needed here, to avoid protection code in
;;; functions without descriptors (for example flet'ed functions)

(defun function-may-gc (function)
  (and *rtl-includes-gc-p*
       (not (function-record-nonrelocating-p function))))

(defun relocating-function-p (name &optional env)
  (multiple-value-bind (usage boundp info)
      (translator-function-information name env)
    (declare (ignore usage))
    (relocating-function-p* name boundp info)))

(defun relocating-function-p* (name boundp info)
  (not (or (not *rtl-includes-gc-p*)
	   (cdr (assoc 'tx:nonrelocating info))
	   (let ((descriptor (unless boundp (defined-as-function name))))
	     (and descriptor
		  (or (function-descriptor-nonrelocating descriptor)
		      (function-descriptor-nonconsing descriptor)))))))

;; This isn't necessarily an error.  
;; It just implies GC must be inhibited during the call to this function.
(define-translator-parameter *warn-about-functions-improperly-declared-nonrelocating*
  t)

(defun fix-self-nonconsing-p (function)
  (when (or (eq (function-record-classification function) ':global)
	    (eq (function-record-classification function) ':global-dllexport))
    (let* ((name (function-record-name function))
	   (descr (defined-as-function name))
	   (relocating-p (relocating-function-p name))
	   (actual-relocating-p
	    (some #'relocating-p (function-record-statements function))))
      (if relocating-p
	  (if actual-relocating-p
	      (when (and (eq (target-form-type actual-relocating-p) 'call)
			 (eq name (environment-entry-name
				   (cadr actual-relocating-p))))
		(setf (function-descriptor-nonrelocating descr) t)
		(when (some #'relocating-p
			    (function-record-statements function))
		  (setf (function-descriptor-nonrelocating descr) nil)))
	      (setf (function-descriptor-nonrelocating descr) t))
	  (if (and actual-relocating-p
		   *warn-about-functions-improperly-declared-nonrelocating*)
	      (warn "The function ~S is declared nonrelocating, but it conses"
		    name))))))

;; Returns t if a GC might move the contents of this variable
(defun relocatable-contents (variable)
  (not (variable-record-nonrelocatable-type variable)))

;;; If all the assignments to a variable assign something of nonrelocatable
;;; type, the variable is also of nonrelocatable type.
;;; Iterate until we do a whole iteration where nothing useful happens.
(defun propagate-type-information (vars function)
  (loop
   (let ((changed nil))
     (dolist (var vars)
       (when (and (not (variable-record-nonrelocatable-type var))
		  (not (member var
			       (function-record-argument-variables function)))
		  (every #'nonrelocatable-setter-p
			 (variable-record-setters var)))
	 (setf (variable-record-nonrelocatable-type var) t)
	 (setf changed t)))
     (unless changed
       (return-from propagate-type-information)))))

(defun nonrelocatable-setter-p (setter)
  (multiple-value-bind (vars all-p)
      (right-hand-side-vars setter)
    (and all-p
	 (every #'variable-record-nonrelocatable-type vars))))

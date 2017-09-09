;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module SIMULATE2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andreas Hofmann




;;;; Overview

;;; This file contains simulation evaluators and other runtime code for the
;;; 1.1 simulator.

;;; Unlike the inference engine evaluators, the simulation evaluators return
;;; only one value.  Expiration time is meaningless in simulation and types
;;; are checked where necessary by checking the value.  If a simulation
;;; evaluator fails for some reason, the simulation-no-value gensym is returned
;;; as the value.  Note that the simulation-value slot of a
;;; variable-simulation-runtime-structure can be set to this value indicating
;;; that the variable has no simulation value.

;; Note that this is different from the 1.0 simulator in which a success flag
;; as well as the value was returned.  This was redundant and caused some 
;; confusion in the code, besides adding some execution overhead.  


;; Some notes on compiling simulations down to machine code -

;; It isn't fair to say compiling won't help because of overhead from other
;; things like history keeping and passing values to the inference engine.
;; Most variables in complicated simulations are really of no interest 
;; outside the simulation.  For example, in a tray by tray simulation of
;; a distillation column, there is no need to observe the data of every
;; local variable in every tray.  Thus, there may be hundreds of variables
;; needed for simulation of the distillation column but only a handful of
;; these will be observed by the user or used by the inference engine.
;; It would therefore be silly to keep histories on all of these variables
;; by default.  I think that for kbs with complicated simulations, it is
;; safe to assume that the simulator will be doing a lot more computation
;; and dealing with many more variables than the inference engine.

;; Compilation of knowledge bases, especially libraries, makes a lot of
;; sense considering that end users will eventually build sophisticated
;; knowledge bases by simply connecting objects from libraries on a 
;; schematic.  Since the user will typically be editing only a few
;; parameters of an object and connections between objects, there is no loss of
;; flexibility in compiling all heuristic and quantitative information
;; for the object.  




;;;; To Do

;; (low priority)
;; Abstract repetitive type checking code in evaluators 
;; (such as def-simulation-unary-operator, etc.).  The bad type warning message
;; for binary operators is slightly inconsistent with the messages put up for
;; unary or nary operators.  The binary operator message puts up both numbers,
;; even if only one is bad.

;; Review all error messages on evaluators.  The evaluator for "-" should have
;; a type error message.

;; (low priority)
;; There is some repetition of code in a few evaluators for handling 
;; non-numeric arguments.  Abstract this to macros some time.

;; (low priority)
;; Currently, the only recursion depth checking done is sim-eval is for
;; user defined functions.  Consider having a more general expression evaluation
;; depth limit as exists (I think) in the inference engine.





;;;; Forward Reference Declarations

(declare-forward-reference current-send-all-values-at-beginning-of-cycle? 
			   function)
(declare-forward-reference current-simulation-procedure function)
(declare-forward-reference current-integration-algorithm function)
(declare-forward-reference stack-eval function)
(declare-forward-reference increment-simulation-time-for-current-model? function)



;;;; Runtime Simulation Functions

;;; The suspendable functions in the simulator are simulate-one-cycle,
;;; calculate-new-values-for-variables,
;;; calculate-new-values-for-continuous-state-variables,
;;; calculate-new-values-for-discrete-state-variables, and
;;; calculate-new-values-for-dependent-variables.  The latter three are the
;;; "deepest" suspendable functions; functions invoked by these are not
;;; suspendable.  Simulate-until-consistent-with-gensym-time can be considered
;;; suspendable although it is outside of the G2 suspendable function mechanism.

;;; The decision to suspend is made in the macro process-variables-until-done
;;; which is expanded in the calculate new values for continuous state,
;;; discrete state, and dependent variables functions.  This macro causes
;;; a number of variables to be processed, the number being given by the
;;; special variable number-of-variables-to-process-at-a-time.  When this
;;; number of variables has been processed, if the time slice has expired,
;;; the function is suspended.  Note that the function will not be suspended
;;; if the simulator is being initialized.  Currently, the only suspendable
;;; function called from initialize-simulator is 
;;; calculate-new-values-for-dependent-variables.

;; Consider passing in number-of-variables-to-process-at-a-time as an argument
;; and using different ones depending on the operation to be performed for the
;; variable.

;; Consider making initialize-simulator suspendable since it can take several
;; seconds for some kbs.  This would be useful for allowing the user to 
;; interrupt or abort the initialization or for doing inspecting of the kb.
;; If a kb edit is made during initialization however, the initialization
;; basically has to start over.  This is the reason why initialize-simulator
;; is not currently suspendable.  Also, the idea of an uninterruptable set up
;; time before running is acceptable to most users.  This is not a runtime 
;; responsiveness issue.

;;; The overhead from the suspension mechanism itself (suspendable functions,
;;; call to frame-has-been-reprocessed-p, etc.) is relatively small
;;; (see notes for 7/27/88 in agh>new-simulator-test-results).  Of course,
;;; if there are a lot of other tasks besides the simulator (other data servers,
;;; display, inference engine) it could take much longer for the simulator to
;;; finish a cycle, but this is outside of the control of the simulator.
;; Consider implementing a switch to turn off the suspendable mechanism.
;; This would allow simulate-until-consistent-with-gensym-time to run
;; uninterrupted until done.  Note that this involves more than merely
;; increasing number-of-variables-to-process-at-a-time.  It would require
;; that values-for-calling-suspendable-subfunction not be used in this mode.

;;; Simulate-one-cycle computes (new-simulation-time current-model-runtime-info?)
;;; based on (current-simulation-time current-model-runtime-info?).
;;; Current-simulation-time itself is not updated until the end of the cycle.
;;; Thus, current-simulation-time holds the time for the previous cycle and
;;; new-simulation-time holds the time for the cycle currently being computed.

;;; Simulate-one-cycle is a suspendable function.  If first computes values for
;;; internally simulated variables in a suspendable way.  After this, if there is
;;; a simulation procedure or external simulation, it launches these and returns.
;;; If there is no simulation procedure or external simulation, it calls
;;; end-simulation-cycle and the cycle is finished.  When the simulation procedure
;;; and/or external simulation complete, they call
;;; end-simulation-procedure-or-external-simulation-cycle which calls
;;; end-simulation-cycle.  Note that simulate-one-cycle, is not called while
;;; waiting for the simulation procedure or external simulation to finish.

(declare-forward-reference work-on-external-simulator-tasks function)
(declare-forward-reference send-all-input-values-to-external-simulator function)

(defun simulate-one-cycle (objects other-args resumption?)
  other-args
  (cond
    ((not resumption?)  ; if first time through
     (add-compound-fixnum-simulation-times
       (new-simulation-time current-model-runtime-info?)
       (current-simulation-time current-model-runtime-info?)
       (shortest-simulation-time-increment current-model-runtime-info?))
     (when (simulating-externally-p)
       (setf (status-of-work-on-external-simulation current-model-runtime-info?)
	     'no-work-done-yet-for-this-cycle))
     (determine-variable-groups-to-be-updated)
     (values-for-calling-suspendable-subfunction
       'new-values-computed 'calculate-new-values-for-variables nil nil))
    ((eq objects 'new-values-computed)  ; if resumption
     (update-variables)
     (let ((simulating-externally-p (simulating-externally-p))
	   (procedure-name? (current-simulation-procedure)))
       (when simulating-externally-p
	 (if (current-send-all-values-at-beginning-of-cycle?)
	     (send-all-input-values-to-external-simulator)
	     (work-on-external-simulator-tasks)))
       (when procedure-name?
	 (invoke-simulation-procedure procedure-name?))
       (when (not (or simulating-externally-p 
		      (not (simulation-procedure-finished?
			     current-model-runtime-info?))))
	 (end-simulation-cycle))
       nil  ; to indicate that resumeable task is finished
       ))))

;; Simulation-procedure-finished?  rather than procedure-name?  must be checked
;; since invoke-simulation-procedure may encounter errors.

;; Using the objects argument of a suspendable function to hold a status flag
;; rather than a list of objects to process is not the way it was intended to be
;; used.  It works well however and is better than having global status flags.

;; The fact that external simulation is done completely after internal simulation
;; allows for immediate update of externally simulated variables when they come
;; in.  By using models, it is still possible simultaneously do external and
;; internal simulation.  The first model sends out the input vector.  The next
;; model works on internal simulation.

 

(defun end-simulation-cycle ()
  (when (increment-simulation-time-for-current-model?)
    (transfer-value-of-compound-fixnum-simulation-times
      (current-simulation-time current-model-runtime-info?) 
      (new-simulation-time current-model-runtime-info?))
    (loop for variable-group-update-structure 
	      in (model-variable-group-update-info current-model-runtime-info?)
	  do
      (transfer-value-of-compound-fixnum-simulation-times
	(time-of-next-update-for-group variable-group-update-structure)
	(new-time-of-next-update-for-group variable-group-update-structure)))))

(defun-void end-simulation-procedure-or-external-simulation-cycle ()
  (when (simulation-procedure-and-external-simulation-finished?)
    (setf (clock-get inhibit-non-real-time-clock-ticks?) nil)
    (end-simulation-cycle)
    (with-current-scheduling
	(nil (priority-of-data-service data-server-parameters))
      (continue-data-server-data-acceptance
	(data-server 'simulator-data-server)
	(clock-get current-g2-time)))))

;; jh, 5/23/91.  Changed end-simulation-procedure-or-external-simulation-cycle to
;; replace the call to priority-of-continued-data-service with one to
;; priority-of-data-service.  See comments under the system table definition in
;; VARIABLES and in take-actions-at-start-of-clock-tick in CYCLES for an
;; explanation of the name change.

(defun simulation-procedure-and-external-simulation-finished? ()
  (and (simulation-procedure-finished? current-model-runtime-info?)
       (or (not (simulating-externally-p))
	   (eq (status-of-work-on-external-simulation
		 current-model-runtime-info?)
	       'work-completed-for-this-cycle))))

;; This checks if the icp socket is still open in a manner similar to
;; writing-icp-message-group.



(defun end-external-simulation-cycle ()
  (when (external-simulation-initialization-completed?
	  current-model-runtime-info?)
    (end-simulation-procedure-or-external-simulation-cycle)))



;;; Determine-variable-groups-to-be-updated checks each
;;; variable-group-update-structure in the current-model-runtime-info? to see if the
;;; group should be updated this cycle.  If time-of-next-update-for-group <
;;; current-simulation-time, then the group is updated.  Note that the new value
;;; of time-of-next-update-for-group is computed using the current value of
;;; time-of-next-update-for-group rather than current-simulation-time.  This keeps
;;; things from getting skewed and allows time-increment-for-group to be used as
;;; the "h" value in integration techniques.  See design book notes for 6/10/88
;;; for further discussion of this.

(defun determine-variable-groups-to-be-updated ()
  (loop for variable-group-update-structure 
	    in (model-variable-group-update-info current-model-runtime-info?)
	do
    (cond
      ((or (<=compound-fixnum-simulation-time
	     (time-of-next-update-for-group variable-group-update-structure)
	     (current-simulation-time current-model-runtime-info?))
	   (not (increment-simulation-time-for-current-model?)))
       (setf (update-group-this-cycle? variable-group-update-structure) t)
       (add-compound-fixnum-simulation-times
	 (new-time-of-next-update-for-group variable-group-update-structure)
	 (time-of-next-update-for-group variable-group-update-structure)
	 (compound-fixnum-time-increment-for-group 
	   variable-group-update-structure)))
      (t 
       (setf (update-group-this-cycle? variable-group-update-structure) nil)))))


;; This simulation meter is defined in G2-METERS.

;; Taken out of AAAI88 release.  - pto 18aug88
; (declare-forward-reference simulation-values-calculated-this-clock-tick variable)




;;; Invoke-simulation-procedure does some error checking, and then calls
;;; start-procedure-invocation if there are no problems.  The simulator-procedure?
;;; arg to start-procedure-invocation is either the model definition frame in
;;; current-model-definition?, or t (for the case where current-model-definition?
;;; is nil because the current model is the main g2 model).  Note that if a model
;;; definition is deleted, any procedure invocation for that model is aborted, so
;;; there is never any need to deal with possibly reclaimed model definitions in
;;; procedure invocations.

(def-kb-specific-variable simulation-procedure-completion-form SIMULATE1
  (restart-simulator-after-procedure nil))

(defun invoke-simulation-procedure (procedure-name)
  (let* ((*current-computation-frame* 
	   (or current-model-definition? simulation-parameters))
	 (procedure (evaluate-designation procedure-name nil))
	 (current-computation-component-particulars nil))
    (cond
      ((null procedure)
       (warning-message* 1
	   "~a is given as the simulation procedure in the simulation-parameters ~
          system table, but no procedure with that name exists."
	 procedure-name))
      ((temporary-constant-p procedure)
       (warning-message* 1
	   "~a is given as the simulation procedure in the simulation-parameters ~
          system table, but this names the constant value ~NC."
	 procedure-name
	 (cached-constant-value procedure)
	 (constant-type procedure))
       (reclaim-temporary-constant procedure))
      ((not (frame-of-class-p procedure 'procedure))
       (warning-message* 1
	   "~a is given as the simulation procedure in the simulation-parameters ~
          system table, but this names a ~a, not a procedure."
	 procedure-name
	 (class procedure)))
      ((not (runnable-p procedure))
       (warning-message* 1
	   "~a is given as the simulation procedure in the simulation-parameters ~
          system table, but this procedure is either inactive, is not enabled ~
          for running while inactive, or has a status other than OK."
	 procedure-name))
      (t
       (let ((argument-error?
	       (get-procedure-argument-list-error-if-any procedure nil nil)))
	 (if argument-error?
	     (progn
	       (warning-message*
		   1 "Error starting simulation procedure ~NF: ~a"
		 procedure argument-error?)
	       (reclaim-text-string argument-error?))
	     (let ((current-model-definition-or-t
		     (or current-model-definition? t))
		   )
	       
	       (setf (simulation-procedure-finished? current-model-runtime-info?)
		     nil
		     (second simulation-procedure-completion-form)
		     current-model-definition-or-t
		     (simulation-procedure-invocation-for-model?
		       current-model-runtime-info?)
		     (procedure-invocation-of-code-body
		       (start-procedure-invocation-in-place
			 procedure  nil nil
			 nil 0 0
			 current-model-definition-or-t
			 simulation-procedure-completion-form
			 nil nil nil))))))))))





;;; Calculate-new-values-for-variables is a suspendable function.  

(defun calculate-new-values-for-variables (objects other-args resumption?)
  (case (current-integration-algorithm)
    (euler
     (calculate-new-values-using-euler objects other-args resumption?))
    (rk4
     (calculate-new-values-using-rk4 objects other-args resumption?))))

;; There will be other integration methods eventually.
    

;;; Calculate-new-values-using-euler is a suspendable function.  

(defun calculate-new-values-using-euler (objects other-args resumption?)
  other-args
  (cond
    ((not resumption?)  ; if first time through
     (setf (simulator-step-flag current-model-runtime-info?) 
	   'calculating-state-variables)
     (values-for-calling-suspendable-subfunction
       'continuous-state-done 
       'calculate-new-values-for-continuous-state-variables
       (installation-set-next?  ; skip header
	 (model-continuous-state-variable-info current-model-runtime-info?)) nil))
    ((eq objects 'continuous-state-done)
     (values-for-calling-suspendable-subfunction
       'discrete-state-done 
       'calculate-new-values-for-discrete-state-variables
       (installation-set-next?
	 (model-discrete-state-variable-info current-model-runtime-info?)) nil))
    ((eq objects 'discrete-state-done)
     (setf (simulator-step-flag current-model-runtime-info?)
	   'calculating-dependent-variables)
     (values-for-calling-suspendable-subfunction
       'dependent-done 
       'calculate-new-values-for-dependent-variables
       (installation-set-next?
	 (model-dependent-variable-info current-model-runtime-info?)) nil))
    (t
     nil   ; to indicate that resumeable task is finished
     )))

;; (simulator-step-flag current-model-runtime-info?) is used here to indicate to
;; sim-eval whether to use the current or new simulation value when encountering a
;; variable-simulation-runtime-structure structure.  If the value is
;; 'calculating-state-variables, the current simulation value is used, else, the
;; new simulation value is used.  This has to be more complicated when using more
;; sophisticated numerical techniques such as rk4.

;; The objects arg is actually a flag here rather than a list of objects.  It
;; indicates the next thing to do when resuming.  (simulator-step-flag
;; current-model-runtime-info?) could be used alternatively but this would confuse
;; the purpose of this flag.


;;; Calculate-new-values-using-euler is a suspendable function.  

(defun calculate-new-values-using-rk4 (objects other-args resumption?)
  other-args
  (cond
    ((not resumption?)  ; if first time through
     (setf (simulator-step-flag current-model-runtime-info?)
	   'calculating-state-variables)
     (setf (rk4-step current-model-runtime-info?) nil)
     (values-for-calling-suspendable-subfunction
       'discrete-state-done 
       'calculate-new-values-for-discrete-state-variables
       (installation-set-next? 
	 (model-discrete-state-variable-info current-model-runtime-info?)) nil))
    ((or (eq objects 'discrete-state-done)
	 (eq objects 'dependent-done))
     (cond 
       ((and (rk4-step current-model-runtime-info?) 
	     (=f (rk4-step current-model-runtime-info?) 4))
	nil  ; to indicate that resumeable task is finished
	)
       (t
	(setf (simulator-step-flag current-model-runtime-info?)
	      'calculating-state-variables)
	(setf (rk4-step current-model-runtime-info?)
	      (if (null (rk4-step current-model-runtime-info?))
		  1
		  (+f (rk4-step current-model-runtime-info?) 1)))
	(values-for-calling-suspendable-subfunction
	  'continuous-state-done 
	  'calculate-new-values-for-continuous-state-variables
	  (installation-set-next?
	    (model-continuous-state-variable-info current-model-runtime-info?)) nil))))
    (t  ; (eq objects 'continuous-state-done)
     (setf (simulator-step-flag current-model-runtime-info?)
	   'calculating-dependent-variables)
     (values-for-calling-suspendable-subfunction
       'dependent-done 
       'calculate-new-values-for-dependent-variables
       (installation-set-next?
	 (model-dependent-variable-info current-model-runtime-info?)) nil))))


;;; New-simulation-value-available? returns non-nil if either the variable
;;; is not being updated this cycle (the update-variable-this-cycle? slot
;;; of the variable-simulation-runtime-structure is nil), or a new value
;;; has been computed for this cycle (the 
;;; new-value-computed-for-current-simulation-cycle? slot is non-nil).
;;; The calculate-new-values... functions set or clear the 
;;; update-variable-this-cycle? slot for each variable as appropriate.
;;; They also set the new-value-computed-for-current-simulation-cycle? slot
;;; when the new-simulation-value is computed.  This slot may be used by
;;; the simulation evaluators during this cycle and is then reset by 
;;; update-variable.  Note that since it will only be set for variables
;;; updated this cycle, it need only be reset for these variables in order
;;; to ensure that it will always be nil for every variable at the beginning
;;; of a new simulation cycle.

;(defmacro new-simulation-value-available? (variable-simulation-runtime-structure)
;  (let ((value-of-structure (gensym)))
;    `(let* ((,value-of-structure ,variable-simulation-runtime-structure))
;       (or (not (update-variable-this-cycle? ,value-of-structure))
;	   (new-value-computed-for-current-simulation-cycle? ,value-of-structure)))))
;; Not currently used.  New-value-computed-for-current-simulation-cycle? is,
;; of course, used.

;; It is assumed that if a variable is not being updated this cycle, then
;; the value computed last cycle it was updated is still in the new-simulation-value
;; slot of the variable-simulation-runtime-structure.






(def-substitution-macro integrate-value-according-to-euler
			(variable-simulation-runtime-structure k-value)
  (let* ((h (extract-number-from-compound-fixnum-simulation-time
	      (get-compound-fixnum-time-increment-for-group
		variable-simulation-runtime-structure))))
    (setq k-value (*e (managed-float-value h) (coerce-to-gensym-float k-value)))
    (let* ((current-value
	     (extract-number-or-value
	       (simulation-value variable-simulation-runtime-structure)))
	   (new-value				       ; integrate to get new value
	     (if (numberp current-value)
		 (+e (coerce-to-gensym-float current-value)
		     k-value)
		 simulation-no-value)))
      (store-new-simulation-value 
	variable-simulation-runtime-structure new-value))))



(def-substitution-macro set-new-value-according-to-euler
			(k-value runtime-structure)
  (cond
    ((numberp k-value)
     (integrate-value-according-to-euler
       runtime-structure k-value))
    (t
     (stack-error
       cached-top-of-stack
       "Error while integrating ~NF.  The equation for the derivative did ~
        not evaluate to a number."
       *current-computation-frame*))))

;; Note that for the Euler method, there is no need to store a k value in the
;; variable-simulation-runtime-structure structure as is done with RK4.  



(def-substitution-macro integrate-value-according-to-rk4
			(variable-simulation-runtime-structure)
  (let* (k-value)
    (setq k-value 
	  (*e ;(managed-float-value h)
	      (/e 1.0 6.0)
	      (+e (extract-number
		    (k1-value variable-simulation-runtime-structure))
		  (*e 2.0
		      (extract-number
			(k2-value variable-simulation-runtime-structure)))
		  (*e 2.0 
		     (extract-number
		       (k3-value variable-simulation-runtime-structure)))
		  (extract-number
		    (k4-value variable-simulation-runtime-structure)))))
    (let* ((current-value
	     (extract-number-or-value
	       (simulation-value variable-simulation-runtime-structure)))
	   (new-value				       ; integrate to get new value
	     (if (numberp current-value)
		 (+e (coerce-to-gensym-float current-value) k-value)
		 simulation-no-value)))
      (store-new-simulation-value 
	variable-simulation-runtime-structure new-value))))



(defmacro store-step-value 
	  (runtime-structure &optional step-slot value step k-slot k-value)
  (let ((value-of-runtime-structure (gensym)))
    `(let ((,value-of-runtime-structure ,runtime-structure))
       ,@(when step-slot
	   `((store-managed-number-or-value
	       (,step-slot ,value-of-runtime-structure) ,value)
	     (setf (new-value-computed-for-current-simulation-cycle?
		     ,value-of-runtime-structure) ,step)))
       ,@(when k-slot
	   `((store-managed-number-or-value
	       (,k-slot ,value-of-runtime-structure) ,k-value))))))



(def-substitution-macro set-new-value-according-to-rk4 
    (k-value runtime-structure)
  (let ((previous-value
	  (coerce-to-gensym-float
	    (extract-number-or-value 
	      (simulation-value runtime-structure))))
	(h (extract-number-from-compound-fixnum-simulation-time
	      (get-compound-fixnum-time-increment-for-group
		runtime-structure))))
    (cond
      ((numberp k-value)
       (setq k-value (coerce-to-gensym-float k-value))
       (setq k-value (*e k-value (managed-float-value h)))
       (case (rk4-step current-model-runtime-info?)
	 (1
	  (store-step-value
	    runtime-structure step1-value 
	    (+e previous-value (/e k-value 2.0)) 1
	    k1-value k-value))
	 ;; Steps 2 and 3 only get half k values
	 ;; This works because the simulator has discrete time steps and
	 ;; equations are expressed in terms of the first derivative
	 (2
       ;; (setq k-value (/e k-value 2.0))
	  ;; The above now commented out line, added in 1995, is not
	  ;; the correct mathematics for the fourth order Runge-Kutta.
	  ;; Even the simplest differential equation models demonstrate
	  ;; this, e.g.
	  ;; state-variable : d/dt(x1) = 1, with initial value 0
	  ;; - jpg 7/31/00 
	  (store-step-value
	    runtime-structure step2-value 
	    (+e previous-value (/e k-value 2.0)) 2
	    k2-value k-value))
	 (3
       ;; (setq k-value (/e k-value 2.0))
	  ;;  See comment above. - jpg 7/31/00 
	  (store-step-value
	    runtime-structure step3-value 
	    (+e previous-value k-value) 3
	    k3-value k-value))
	 (4
	  (store-step-value
	    runtime-structure nil nil nil
	    k4-value k-value)
	  (integrate-value-according-to-rk4
	    runtime-structure))))
      (t
       (stack-error cached-top-of-stack
		    "Error while integrating ~NF.  The equation for the derivative did ~
not evaluate to a number."
		    *current-computation-frame*)))))



(def-substitution-macro store-new-value-for-dependent-variable
			(runtime-structure evaluation-value)
  (if (rk4-step current-model-runtime-info?)
      (case (rk4-step current-model-runtime-info?)
	(1
	 (store-step-value 
	   runtime-structure step1-value 
	   (evaluation-value-value evaluation-value) 1))
	(2
	 (store-step-value 
	   runtime-structure step2-value 
	   (evaluation-value-value evaluation-value) 2))
	(3
	 (store-step-value 
	   runtime-structure step3-value 
	   (evaluation-value-value evaluation-value) 3))
	(4
	 (store-step-value 
	   runtime-structure step4-value 
	   (evaluation-value-value evaluation-value) 4)
	 (store-new-simulation-evaluation-value runtime-structure evaluation-value)))
      (store-new-simulation-evaluation-value
	runtime-structure evaluation-value)))



(def-substitution-macro value-computed-for-current-cycle-or-step?
			(variable-simulation-runtime-structure)
  (let ((value-computed?
	  (new-value-computed-for-current-simulation-cycle?
	    variable-simulation-runtime-structure)))
    (if (and value-computed? (numberp value-computed?) 
	     (rk4-step current-model-runtime-info?))
	(case (rk4-step current-model-runtime-info?)
	  (1
	   (=f value-computed? 1))
	  (2
	   (=f value-computed? 2))
	  (3
	   (=f value-computed? 3))
	  (4
	   (=f value-computed? 4)))
	value-computed?)))





;;; Calculate-new-value-for-one-dependent-variable will, if the
;;; variables-that-need-simulated-values stack is empty, work on the variable
;;; corresponding to rest-of-structures.  In this case, it is always ok to store
;;; the value if the evaluation succeeds.  If the
;;; variables-that-need-simulated-values stack is not empty,
;;; calculate-new-value-for-one-dependent-variable will work on the variable at
;;; the top of this stack.  If evaluation for this variable is successful, the
;;; value will be stored if the value has not been tainted by a loop encounter, or
;;; if the variable is at the bottom of the variables-that-need-simulated-values
;;; stack (see also discussion of ordering loops in Stack Evaluator Functions for
;;; Simulator section of SIMULATE1).  If the variables-that-need-simulated-values
;;; stack becomes empty, the value-tainted-by-ordering-loop?  flag is cleared.
;;; Calculate-new-value-for-one-dependent-variable returns non-nil if the
;;; variables-that-need-simulated-values stack is empty, indicating to
;;; process-variables-until-done that progress has been made and that it should
;;; proceed to the next structure in rest-of-structures.

;;; Note that calculate-new-value-for-one-dependent-variable-1 calls
;;; value-computed-for-current-cycle-or-step?  before doing any evaluation to
;;; check if the value has already been computed.  This can happen if the variable
;;; got on the variables-that-need-simulated-values earlier for the purpose of
;;; computing some other variable (due to dependent variables not being completely
;;; sorted).

;; Move this doc!





;;; Process-n-variables-in-stack-eval provides a mechanism for evaluating a set of
;;; simulated variables within one call to stack-eval.  This results in a
;;; significant speed improvement over calling stack-eval for each variable
;;; individually, due to the overhead of entering and exiting stack-eval.  The
;;; functions enter-next-simulation-variable-context and
;;; exit-last-simulation-variable-context perform the context switch.  These are
;;; called by the stack instruction complete-simulation-variable-evaluation, and
;;; by process-n-variables-in-stack-eval, to get things started.

(defvar set-of-variables-to-simulation-evaluate)
(defvar current-simulation-category)
(defvar current-simulation-runtime-structure)
(defvar working-on-variables-that-need-simulated-values-stack?)
(defvar variable-is-at-bottom-of-stack?)
(defvar dont-backward-chain-in-sim-eval?)
(defvar dont-proceed-to-next-variable?)
(def-system-variable within-simulator-for-stack-error? SIMULATE2 nil)



(defmacro with-bindings-for-sim-eval-for-stack 
	  (rest-of-set simulation-category dont-backward-chain? dont-proceed?
	   &body body)
  `(let* ((current-computation-flags (make-computation-flags
				       :final-evaluation-attempt? t
				       :role-serve-inactive-objects? t))
	  (current-computation-activity 0)
	  (current-computation-component-particulars nil)
	  (*current-computation-frame* nil)
	  (current-computation-instance nil)
	  (current-computation-style nil)
	  (current-environment 'simulator)
;	  (current-profile-structure? nil)
	  (evaluating-simulator-procedure? nil)
	  (explanation-variables nil)
	  (stack-expiration 'never)
	  (*variables-that-did-not-have-values* nil)

	  (set-of-variables-to-simulation-evaluate ,rest-of-set)
	  (current-simulation-category ,simulation-category)
	  (current-simulation-runtime-structure nil)
	  (dont-backward-chain-in-sim-eval? ,dont-backward-chain?)
	  (dont-proceed-to-next-variable? ,dont-proceed?)
	  (working-on-variables-that-need-simulated-values-stack? nil)
	  (variable-is-at-bottom-of-stack? nil)

	  (within-simulator-for-stack-error? t)
	  ;; For tracing and breakpoints facility.
	  saved-warning-level saved-tracing-level saved-breakpoint-level
	  saved-source-stepping-level)
     ,@body))

(def-substitution-macro sim-eval-for-stack-1 
			(byte-code-body simulation-environment-vector)
  (stack-eval 
    byte-code-body (byte-code-body-constant-vector byte-code-body)
    simulation-environment-vector (get-fixnum-time) nil 0)
  (when (simulation-error? current-model-runtime-info?) 
    (signal-simulation-error-after-stack-eval))
  (when current-computation-instance
    (let ((dont-backward-chain-in-sim-eval? t))
      (exit-last-simulation-variable-context 
	nil simulation-environment-vector))))

(defun process-n-variables-in-stack-eval
    (rest-of-set simulation-category)
  (loop while rest-of-set do
    (with-bindings-for-sim-eval-for-stack 
	rest-of-set simulation-category nil nil
      (enter-next-simulation-variable-context) 
      (when (null current-computation-instance)
	(return-from process-n-variables-in-stack-eval nil))
      (let ((simulation-environment-vector
	      (runtime-cache? current-simulation-runtime-structure)))
	(when profiling-enabled?
	  (let ((formula (simulation-formula current-simulation-runtime-structure)))
	    (increment-profiling-calls formula)
	  (posit-profiling-structure formula)))
	(sim-eval-for-stack-1
	  (runtime-formula current-simulation-runtime-structure) 
	  simulation-environment-vector))
      (when (and (not initializing-simulator?) ran-out-of-time?)
	(return-from
	  process-n-variables-in-stack-eval
	  (values-for-suspending-task 
	    set-of-variables-to-simulation-evaluate)))
      (setq rest-of-set set-of-variables-to-simulation-evaluate))))

;; Returns nil if resumeable task is done.



(defun sim-eval-for-stack-until-value-found (variable)
  (with-bindings-for-sim-eval-for-stack 
    (simulation-info? variable) (simulation-category? variable)
    nil t
    (loop do (sim-eval-for-stack)
	  until 
	    (null (variables-that-need-simulated-values
		    current-model-runtime-info?)))))

(defun sim-eval-for-stack-without-chaining (variable)
  (with-bindings-for-sim-eval-for-stack 
    (simulation-info? variable) (simulation-category? variable) 
    t t
    (sim-eval-for-stack)))



;;; Sim-eval-for-stack is similar to process-n-variables-in-stack-eval except that
;;; it only processes one variable.

(defun sim-eval-for-stack ()
  (enter-next-simulation-variable-context)
  (with-bindings-for-variable-sim-eval
    (when profiling-enabled?
      (increment-profiling-calls
	current-computation-instance)
      ;; Note - this computation-instance will always be nil!
      ;; This should really be billing the scheduled task
      (posit-profiling-structure current-computation-instance))
    (sim-eval-for-stack-1
      byte-code-body simulation-environment-vector)))


 
(def-substitution-macro set-info-for-next-variable-to-simulate
			(rest-of-structures)
  (cond 
    ((or (eq current-simulation-category 'dependent)
	 initializing-state-variables?)
     (cond 
       ((null (variables-that-need-simulated-values current-model-runtime-info?))
	(set-info-for-next-variable-to-simulate-1 rest-of-structures))
       (t
	(let ((next-variable-to-compute (pop-next-variable-that-needs-value)))
	  (setq working-on-variables-that-need-simulated-values-stack? t
		variable-is-at-bottom-of-stack?
		(null (variables-that-need-simulated-values current-model-runtime-info?)))
	  (set-info-for-next-variable-to-simulate-1
	    (simulation-info? next-variable-to-compute))))))
    (t
     (set-info-for-next-variable-to-simulate-1 rest-of-structures))))



(defun enter-next-simulation-variable-context ()
  (cond
    (dont-backward-chain-in-sim-eval?
     (set-info-for-evaluation-only
       set-of-variables-to-simulation-evaluate))
    (t
     (setq current-computation-instance nil)
     (loop while set-of-variables-to-simulation-evaluate do
       (set-info-for-next-variable-to-simulate 
	 set-of-variables-to-simulation-evaluate)
	   until (or current-computation-instance dont-proceed-to-next-variable?)
	   do
       (setq set-of-variables-to-simulation-evaluate
	     (installation-set-next? set-of-variables-to-simulation-evaluate)))
     (when (null current-computation-instance)
       (return-from enter-next-simulation-variable-context nil))
     (setq number-of-simulated-variables-processed
	   (+f number-of-simulated-variables-processed 1))))
  (setq stack-expiration 'never)
  (enter-tracing-and-breakpoint-context
    *current-computation-frame*
    (simulation-enter-tracing-context-message)))

(defun simulation-enter-tracing-context-message ()
  (twith-output-to-text-string
    (twrite-string "Executing ")
    (write-simulation-formula-trace-entry *current-computation-frame*)
    (twrite-character #.%\.)))

(defun exit-last-simulation-variable-context 
       (value-known? simulation-environment-vector)
  (when *current-computation-frame*
    (exit-tracing-and-breakpoint-context 
      *current-computation-frame*
      (simulation-formula-trace-exit-message *current-computation-frame*))
    (when (not dont-backward-chain-in-sim-eval?)
      (let ((new-evaluation-value 
	      (if value-known?
		  (svref simulation-environment-vector 1)
		  simulation-no-value)))
	(cond 
	  ((or (eq current-simulation-category 'dependent)
	       initializing-state-variables?)
	   (when (not (variable-needs-simulated-value? 
			current-simulation-runtime-structure))
	     (store-new-value-for-dependent-variable
	       current-simulation-runtime-structure new-evaluation-value))
	   (when working-on-variables-that-need-simulated-values-stack?
	     (when (and (value-tainted-by-ordering-loop? current-model-runtime-info?)
			(not variable-is-at-bottom-of-stack?)
			(not (value-of-variable-tainted? 
			       current-simulation-runtime-structure)))
	       (mark-as-tainted-variable current-computation-instance))
	     (when (null (variables-that-need-simulated-values 
			   current-model-runtime-info?))
	       (clear-tainted-variables t))
	     (setq working-on-variables-that-need-simulated-values-stack? nil
		   variable-is-at-bottom-of-stack? nil))
	   (when (and (null (variables-that-need-simulated-values 
			      current-model-runtime-info?))
		      (not dont-proceed-to-next-variable?))
	     (setq set-of-variables-to-simulation-evaluate
		   (installation-set-next? 
		     set-of-variables-to-simulation-evaluate))))
	  ((eq current-simulation-category 'continuous-state)
	   (if (rk4-step current-model-runtime-info?)
	       (set-new-value-according-to-rk4 
		 (evaluation-value-value new-evaluation-value)
		 current-simulation-runtime-structure)
	       (set-new-value-according-to-euler 
		 (evaluation-value-value new-evaluation-value)
		 current-simulation-runtime-structure))
	   (when (not dont-proceed-to-next-variable?)
	     (setq set-of-variables-to-simulation-evaluate
		   (installation-set-next? set-of-variables-to-simulation-evaluate))))
	  ((eq current-simulation-category 'discrete-state)
	   (store-new-simulation-evaluation-value 
	     current-simulation-runtime-structure new-evaluation-value)
	   (when (not dont-proceed-to-next-variable?)
	     (setq set-of-variables-to-simulation-evaluate
		   (installation-set-next? set-of-variables-to-simulation-evaluate))))))))
  nil)

(defun write-simulation-formula-trace-entry (simulation-formula)
  (cond
    ((or (generic-simulation-formula-p simulation-formula)
	 (simulation-subtable-p simulation-formula))
     (tformat "~NF" simulation-formula))))

(defun simulation-formula-trace-exit-message (simulation-formula)
  (twith-output-to-text-string
    (cond
      ((or (generic-simulation-formula-p simulation-formula)
	   (simulation-subtable-p simulation-formula))
       (tformat "Exiting execution of ~NF." simulation-formula)))))

(defun-simple set-info-for-next-variable-to-simulate-1 (rest-of-structures)
  (let* ((runtime-structure? (runtime-info? rest-of-structures))
	 variable )
    (when runtime-structure?
      (setq variable
	    (corresponding-variable runtime-structure?))
      ;; First check if variable is to be updated this cycle.
      (cond
	((variable-to-be-updated-this-cycle? runtime-structure?)
	 (setf (update-variable-this-cycle? runtime-structure?) t)
	 (cond
	   ((or (not (eq current-simulation-category 'dependent))
		(not (value-computed-for-current-cycle-or-step?
		       runtime-structure?)))
	    (setq current-simulation-runtime-structure runtime-structure?
		  current-computation-instance variable
		  current-computation-component-particulars nil
		  *current-computation-frame* (simulation-formula runtime-structure?)))
	   (t
	    (setq current-computation-instance nil))))
	((variable-needs-initialization? runtime-structure?)
	 (setf (update-variable-this-cycle? runtime-structure?) t)
	 (setq current-simulation-runtime-structure runtime-structure?
	       current-computation-instance variable
	       current-computation-component-particulars
	       '(simulation-initial-value *current-computation-frame*)
	       *current-computation-frame* (simulation-formula runtime-structure?)))
	(t
	 (if (state-variable-p variable)
	     (when (not (eq (update-variable-this-cycle? runtime-structure?)
			    'suppress-first-update))
	       (setf (update-variable-this-cycle? runtime-structure?) nil))
	     (setf (update-variable-this-cycle? runtime-structure?) nil))
	 (setq current-computation-instance nil))))))

(defun-simple set-info-for-evaluation-only (rest-of-structures)
  (let* ((runtime-structure (runtime-info? rest-of-structures))
	 (variable (corresponding-variable runtime-structure)))
    (setq current-simulation-runtime-structure runtime-structure
	  current-computation-instance variable
	  *current-computation-frame* (simulation-formula runtime-structure))))





;;; Calculate-new-values-for-continuous-state-variables, 
;;; calculate-new-values-for-discrete-state-variables, and
;;; calculate-new-values-for-dependent-variables are suspendable sub-functions of
;;; calculate-new-values-for-variables.  These are the "deepest" suspendable functions
;;; within calculate-new-values-for-variables;  any functions called by these are
;;; not suspendable.

(defun calculate-new-values-for-continuous-state-variables
       (set-of-continuous-state-variables other-args resumption?)
  (declare (ignore other-args resumption?))
  (process-n-variables-in-stack-eval
    set-of-continuous-state-variables 'continuous-state))

(defun calculate-new-values-for-discrete-state-variables
       (set-of-discrete-state-variables other-args resumption?)
  (declare (ignore other-args resumption?))
  (process-n-variables-in-stack-eval
    set-of-discrete-state-variables 'discrete-state))

(defun calculate-new-values-for-dependent-variables
       (set-of-dependent-variables other-args resumption?)
  (declare (ignore other-args resumption?))
  (process-n-variables-in-stack-eval
    set-of-dependent-variables 'dependent))



(def-substitution-macro make-evaluation-value-from-managed-simulation-value
			(simulation-value runtime-structure)
  (cond
    ((evaluation-truth-value-p simulation-value)
     (copy-managed-number-or-value simulation-value))
    (t
     (make-evaluation-value-from-managed-value
       (eq (data-type-of-variable-or-parameter
	     (corresponding-variable runtime-structure))
	   'truth-value)
       simulation-value))))



(def-substitution-macro get-value-from-previous-step (runtime-structure)
  (if (rk4-step current-model-runtime-info?)
      (if (discrete-state-variable-p
	    (corresponding-variable runtime-structure))
	  (extract-number-or-value (simulation-value runtime-structure))
	  (fixnum-case (rk4-step current-model-runtime-info?)
	    (1 (extract-number-or-value (simulation-value runtime-structure)))
	    (2 (extract-number-or-value (step1-value runtime-structure)))
	    (3 (extract-number-or-value (step2-value runtime-structure)))
	    (4 (extract-number-or-value (step3-value runtime-structure)))))
      (extract-number-or-value (simulation-value runtime-structure))))

(def-substitution-macro get-evaluation-value-from-previous-step (runtime-structure)
  (let ((managed-value nil))
    (if (rk4-step current-model-runtime-info?)
	(if (discrete-state-variable-p
	      (corresponding-variable runtime-structure))
	    (setq managed-value (simulation-value runtime-structure))
	    (fixnum-case (rk4-step current-model-runtime-info?)
	      (1 (setq managed-value (simulation-value runtime-structure)))
	      (2 (setq managed-value (step1-value runtime-structure)))
	      (3 (setq managed-value (step2-value runtime-structure)))
	      (4 (setq managed-value (step3-value runtime-structure)))))
	(setq managed-value (simulation-value runtime-structure)))
    (make-evaluation-value-from-managed-simulation-value
      managed-value runtime-structure)))

(def-substitution-macro get-value-from-current-step (runtime-structure)
  (if (rk4-step current-model-runtime-info?)
      (if (discrete-state-variable-p
	    (corresponding-variable runtime-structure))
	  (extract-number-or-value (new-simulation-value runtime-structure))
	  (let ((result nil))
	    (fixnum-case (rk4-step current-model-runtime-info?)
	      (4 (setq result
		       (extract-number-or-value (new-simulation-value runtime-structure))))
	      (1 (setq result
		       (extract-number-or-value (step1-value runtime-structure))))
	      (2 (setq result
		       (extract-number-or-value (step2-value runtime-structure))))
	      (3 (setq result
		       (extract-number-or-value (step3-value runtime-structure)))))
	    result))
      (extract-number-or-value (new-simulation-value runtime-structure))))

(def-substitution-macro get-evaluation-value-from-current-step (runtime-structure)
  (let ((managed-value nil))
    (if (rk4-step current-model-runtime-info?)
	(if (discrete-state-variable-p
	      (corresponding-variable runtime-structure))
	    (setq managed-value (new-simulation-value runtime-structure))
	    (fixnum-case (rk4-step current-model-runtime-info?)
	      (4 (setq managed-value (new-simulation-value runtime-structure)))
	      (1 (setq managed-value (step1-value runtime-structure)))
	      (2 (setq managed-value (step2-value runtime-structure)))
	      (3 (setq managed-value (step3-value runtime-structure)))))
	(setq managed-value (new-simulation-value runtime-structure)))
    (make-evaluation-value-from-managed-simulation-value
      managed-value runtime-structure)))


(defmacro sim-eval-get-value-of-variable-1 
	  (variable-simulation-runtime-structure)
  (let ((value-of-structure (gensym)))
    `(let* ((,value-of-structure ,variable-simulation-runtime-structure))
       (cond
	 ((or do-not-update-simulated-value?
	      (not
		(variable-to-be-updated-this-cycle? ,value-of-structure)))

	  (extract-number-or-value  
	    (simulation-value ,value-of-structure))
	  ; should be the same as new-simulation-value here
	  )
	 ((eq (simulator-step-flag current-model-runtime-info?)
	      'calculating-state-variables)
	  (get-value-from-previous-step ,value-of-structure))
	 (t
	  ;; calculating-dependent-variables -
	  ;; Check if new value is known.  If not, calculate it.
	  (if (value-computed-for-current-cycle-or-step?
		,value-of-structure)
	      (get-value-from-current-step ,value-of-structure)
	      (sim-eval-calculate-new-value-for-variable
		,value-of-structure)))))))

(defmacro sim-eval-get-evaluation-value-of-variable-1 
	  (variable-simulation-runtime-structure)
  (let ((value-of-structure (gensym)))
    `(let* ((,value-of-structure ,variable-simulation-runtime-structure))
       (cond
	 ((or do-not-update-simulated-value?
	      (not
		(variable-to-be-updated-this-cycle? ,value-of-structure)))
	  (make-evaluation-value-from-managed-simulation-value
	    (simulation-value ,value-of-structure) ,value-of-structure)
	  ; should be the same as new-simulation-value here
	  )
	 ((eq (simulator-step-flag current-model-runtime-info?)
	      'calculating-state-variables)
	  (get-evaluation-value-from-previous-step ,value-of-structure))
	 (t
	  ;; calculating-dependent-variables -
	  ;; Check if new value is known.  If not, calculate it.
	  (if (value-computed-for-current-cycle-or-step?
		,value-of-structure)
	      (get-evaluation-value-from-current-step ,value-of-structure)
	      (sim-eval-calculate-new-evaluation-value-for-variable
		,value-of-structure)))))))





(def-substitution-macro sim-eval-get-value-of-externally-simulated-variable
			(variable-simulation-runtime-structure)
  (extract-number-or-value  
    (simulation-value variable-simulation-runtime-structure)))

(def-substitution-macro sim-eval-get-evaluation-value-of-externally-simulated-variable
			(variable-simulation-runtime-structure)
  (make-evaluation-value-from-managed-simulation-value
    (simulation-value variable-simulation-runtime-structure)
    variable-simulation-runtime-structure))

(defmacro simulation-loop-encountered? (runtime-structure)
  `(when (and (not do-not-update-simulated-value?)
	      (not (eq (simulator-step-flag current-model-runtime-info?)
		       'calculating-state-variables)))
     (let ((loop-encountered?
	     (or
	       (variable-needs-simulated-value? ,runtime-structure)
	       (and current-simulation-runtime-structure
		    (eq ,runtime-structure current-simulation-runtime-structure)))))
       (when loop-encountered?
	 (setf (value-tainted-by-ordering-loop? current-model-runtime-info?) t))
       loop-encountered?)))



;;; Sim-eval-get-value-of-variable returns simulation-no-value if a loop is
;;; encountered or if the variable is not being simulated.  Otherwise, it invokes
;;; sim-eval-get-value-of-variable-1 to get the value.

(defun-simple sim-eval-get-value-of-variable (variable)
  (let ((variable-simulation-runtime-structure?
	  (when variable
	    (simulation-runtime-information? variable))))
    (if (and variable-simulation-runtime-structure?  ; variable is being simulated
	     (not (simulation-loop-encountered? 
		    variable-simulation-runtime-structure?)))
	(if (externally-simulated-variable-p variable)
	    (sim-eval-get-value-of-externally-simulated-variable
	      variable-simulation-runtime-structure?)
	    (sim-eval-get-value-of-variable-1
	      variable-simulation-runtime-structure?))
	simulation-no-value)))

(defun-simple sim-eval-get-evaluation-value-of-variable (variable)
  (let ((variable-simulation-runtime-structure?
	  (when variable
	    (simulation-runtime-information? variable))))
    (if (and variable-simulation-runtime-structure?  ; variable is being simulated
	     (not (simulation-loop-encountered? 
		    variable-simulation-runtime-structure?)))
	(if (externally-simulated-variable-p variable)
	    (sim-eval-get-evaluation-value-of-externally-simulated-variable
	      variable-simulation-runtime-structure?)
	    (sim-eval-get-evaluation-value-of-variable-1
	      variable-simulation-runtime-structure?))
	simulation-no-value)))



(defun sim-eval-get-value-of-parameter (parameter)
  (let ((simulated-value
	  (sim-eval-get-value-of-variable parameter)))
    (if (not (no-simulation-value-p simulated-value))
	simulated-value
	(get-value-of-parameter-for-simulator parameter))))

(defun-simple sim-eval-get-evaluation-value-of-parameter (parameter)
  (let ((simulated-value
	  (sim-eval-get-evaluation-value-of-variable parameter)))
    (if (not (no-simulation-value-p simulated-value))
	simulated-value
	(get-evaluation-value-of-parameter-for-simulator parameter))))



(defun-simple sim-eval-calculate-new-value-for-variable
       (variable-simulation-runtime-structure)
  (let ((variable (corresponding-variable variable-simulation-runtime-structure)))
    (cond
      ((or (dependent-variable-p variable) initializing-state-variables?)
       (handle-encountered-unknown-value-in-simulator variable))
      ((state-variable-p variable)
       (sim-eval-calculate-new-value-for-state-variable variable)))))

(defun-simple sim-eval-calculate-new-evaluation-value-for-variable
       (variable-simulation-runtime-structure)
  (let ((variable (corresponding-variable variable-simulation-runtime-structure)))
    (cond
      ((or (dependent-variable-p variable) initializing-state-variables?)
       (handle-encountered-unknown-value-in-simulator variable))
      ((state-variable-p variable)
       (sim-eval-calculate-new-evaluation-value-for-state-variable variable)))))

;; This is called only from sim-eval-get-value-of-variable-1, which is called only
;; from sim-eval-get-value-of-variable.  Thus, if execution gets here, there is no
;; ordering loop problem; it would have been caught by
;; sim-eval-get-value-of-variable.



;; Since (simulator-step-flag current-model-runtime-info?) must be
;; 'calculating-dependent-variables, new simulation values have already been
;; calculated for state variables at this point.  Therefore,
;; sim-eval-calculate-new-value-for-state-variable just returns the new simulation
;; value.

(defun-simple sim-eval-calculate-new-value-for-state-variable (state-variable)
  (let* ((variable-simulation-runtime-structure 
	   (simulation-runtime-information? state-variable)))
    (get-value-from-current-step variable-simulation-runtime-structure)))

(defun-simple sim-eval-calculate-new-evaluation-value-for-state-variable
	      (state-variable)
  (let* ((variable-simulation-runtime-structure 
	   (simulation-runtime-information? state-variable)))
    (get-evaluation-value-from-current-step variable-simulation-runtime-structure)))




;;;; Variable Update

(defun update-variables ()
  (let (*current-computation-frame*
	(current-computation-instance (data-server 'simulator-data-server)))
    (with-temporary-gensym-float-creation update-variables
      (for-each-element-in-installation-set
	(model-continuous-state-variable-info current-model-runtime-info?)
	'update-state-variable)
      (for-each-element-in-installation-set
	(model-discrete-state-variable-info current-model-runtime-info?)
	'update-state-variable)
      (for-each-element-in-installation-set
	(model-dependent-variable-info current-model-runtime-info?)
	'update-dependent-variable))))

(defun update-state-variable (state-variable)
  (let* ((runtime-structure (simulation-runtime-information? state-variable))
	 (update-variable?
	   (update-variable-this-cycle? runtime-structure)))
    (when update-variable?
      (if (eq update-variable? 'suppress-first-update)
	  (setf (update-variable-this-cycle? runtime-structure) nil)
	  (update-variable state-variable)))))

(defun update-dependent-variable (dependent-variable)
  (let* ((runtime-structure (simulation-runtime-information? dependent-variable))
	 (update-variable?
	   (update-variable-this-cycle? runtime-structure)))
    (when update-variable?
      (update-variable dependent-variable))))





(def-substitution-macro time-to-send-data-for-one-shot-request?
			(interval-at-which-to-send-value-to-inference-engine)
  (and (collect-one-shot-data-request-pending?
	 interval-at-which-to-send-value-to-inference-engine)
       (simulator-almost-up-to-date?
	 (if (one-shot-and-interval-request-pending?
	       interval-at-which-to-send-value-to-inference-engine)
	     (managed-float-value (cadr interval-at-which-to-send-value-to-inference-engine))
	     (managed-float-value (cdr interval-at-which-to-send-value-to-inference-engine))))
       ;; compare simulation time with time of request
       ))

(def-substitution-macro new-begin-collecting-data-request?
			(last-time-value-sent-to-inference-engine
			 interval-at-which-to-send-value-to-inference-engine)
  (and (eq last-time-value-sent-to-inference-engine 'long-time-ago)
       (simulator-almost-up-to-date?
	 (if (one-shot-and-interval-request-pending?
	       interval-at-which-to-send-value-to-inference-engine)
	     (managed-float-value (cdddr interval-at-which-to-send-value-to-inference-engine))
	     (managed-float-value (cdr interval-at-which-to-send-value-to-inference-engine))))))

(def-substitution-macro time-to-send-collected-data-for-interval?
			(last-time-value-sent-to-inference-engine
			 interval-at-which-to-send-value-to-inference-engine)
  (let (one-shot-and-interval-request-pending?)
    (and (not (eq last-time-value-sent-to-inference-engine 'long-time-ago))
	 (or (not (eq (car interval-at-which-to-send-value-to-inference-engine)
		      'send-one-value))
	     (setq one-shot-and-interval-request-pending?
		   (one-shot-and-interval-request-pending? 
		     interval-at-which-to-send-value-to-inference-engine)))
	 (simulator-almost-up-to-date?
	   (+e
	     (managed-float-value (if one-shot-and-interval-request-pending?
				      (third interval-at-which-to-send-value-to-inference-engine)
				      (car interval-at-which-to-send-value-to-inference-engine)))
	     (managed-float-value
	       last-time-value-sent-to-inference-engine))))))

(def-substitution-macro clean-up-after-processing-one-shot-request
    (interval-at-which-to-send-value-to-inference-engine
      simulation-runtime-structure)
  (cond
    ((one-shot-and-interval-request-pending?
       interval-at-which-to-send-value-to-inference-engine)
     (setf (interval-at-which-to-send-value-to-inference-engine
	     simulation-runtime-structure)
	   (cddr interval-at-which-to-send-value-to-inference-engine))
     (setf (cddr interval-at-which-to-send-value-to-inference-engine) nil)
     (reclaim-interval-at-which-to-send-value-to-inference-engine
       interval-at-which-to-send-value-to-inference-engine))
    (t
     (reclaim-interval-at-which-to-send-value-to-inference-engine
       interval-at-which-to-send-value-to-inference-engine)
     (setf (interval-at-which-to-send-value-to-inference-engine
	     simulation-runtime-structure)
	   nil))))

;; See documentation for collect-one-shot-data-for-simulator and
;; begin-collecting-data-for-simulator for format of the slots
;; interval-at-which-to-send-value-to-inference-engine and
;; last-time-value-sent-to-inference-engine.

(defun update-variable (variable-or-parameter)
  (note-change-to-runtime-data-for-block variable-or-parameter) 
  (let* ((simulation-info (simulation-info? variable-or-parameter))
	 (simulation-subtable?
	   (when (variable-has-subtable-p simulation-info)
	     (simulation-details variable-or-parameter)))
	 (simulation-runtime-structure (runtime-info? simulation-info))
	 (simulation-stored-history-specification?
	   (if simulation-subtable?
	       (simulation-stored-history-specification? simulation-subtable?)))
	 (new-simulation-value-box
	   (new-simulation-value simulation-runtime-structure)))
    (setq *current-computation-frame* variable-or-parameter)
    (reclaim-managed-number-or-value
      (simulation-value simulation-runtime-structure))
    (setf (simulation-value simulation-runtime-structure)
	  (copy-managed-number-or-value new-simulation-value-box))
    (cond
      ((variable-p variable-or-parameter)
       (let ((interval-at-which-to-send-value-to-inference-engine
	       (interval-at-which-to-send-value-to-inference-engine
		 simulation-runtime-structure))
	     (last-time-value-sent-to-inference-engine
	       (last-time-value-sent-to-inference-engine
		 simulation-runtime-structure))
	     (time-of-request? nil))
	 (if (and interval-at-which-to-send-value-to-inference-engine
		  (not (no-simulation-value-p
			 (extract-cached-number-or-value new-simulation-value-box))))
	     (cond
	       ((setq time-of-request?
		      (time-to-send-data-for-one-shot-request?
			interval-at-which-to-send-value-to-inference-engine))
		(clean-up-after-processing-one-shot-request
		  interval-at-which-to-send-value-to-inference-engine
		  simulation-runtime-structure))
	       (t
		(setq time-of-request?
		      (or (new-begin-collecting-data-request?
			    last-time-value-sent-to-inference-engine
			    interval-at-which-to-send-value-to-inference-engine)
			  (time-to-send-collected-data-for-interval?
			    last-time-value-sent-to-inference-engine
			    interval-at-which-to-send-value-to-inference-engine))))))
	 (when time-of-request?
	   (put-simulated-value-to-inference-engine
	     variable-or-parameter 
	     (extract-cached-number-or-value new-simulation-value-box)
	     (compute-g2-time-for-simulation-time
	       (new-simulation-time current-model-runtime-info?)))
					; In 3.0, the collection-time argument
					; to put-simulated-value-to-inference-
					; engine was time-of-request?.  AGH said
					; that this is probably not necessary
					; and can instead be the simulation
					; time.  So, in 4.0, the simulation time
					; is sent, converted to g2-time format,
					; because G2 can now use subsecond
					; times.  - cpm, 7/28/94

	   (set-last-time-value-sent-to-inference-engine 
	     simulation-runtime-structure
		 time-of-request?))))
      ;; Note that last-time... slot can be set as the result of a response to 
      ;; a one shot request as well as a collect at interval request.

      (t  ; if parameter
       (let ((new-simulation-value 
	       (extract-cached-number-or-value new-simulation-value-box)))
	 (when (not (no-simulation-value-p new-simulation-value))
	   (let ((put-current-value-called-from-simulator-p t))
	     (put-simulated-value-to-inference-engine
	       variable-or-parameter new-simulation-value
	       (compute-g2-time-for-simulation-time
		 (new-simulation-time current-model-runtime-info?))))))))

    (when (and simulation-stored-history-specification?
	       (not (no-simulation-value-p 
		      (extract-cached-number-or-value
			new-simulation-value-box))))
	  (store-history-value
	    (get-or-make-history-buffer
	      simulation-subtable?
	      simulation-stored-history-specification?)
	    simulation-stored-history-specification?
	    (extract-number-or-value new-simulation-value-box)
	    
	    (extract-number-from-compound-fixnum-simulation-time
	      (new-simulation-time current-model-runtime-info?))
	    t))

    (setf (new-value-computed-for-current-simulation-cycle?
	    simulation-runtime-structure) nil)
    nil))

;; The history keeping and inference engine interface code here does not greatly 
;; reduce simulator speed if there is no data service from the variable to the 
;; inference engine and no history is being kept.


;;; Simulator-almost-up-to-date?, rather than the simulator-up-to-date?  flag,
;;; is used by update-variable to check if the simulator is up to date.  This is
;;; done for two reasons.  First of all, update-variable does this check based
;;; on the time the request for the value was made, not the current gensym time.
;;; Second, simulation values updated by update-variable are valid for data
;;; service if the simulator will be up to date after simulate-one-cycle is done.
;;; If up to date, the simulation time is returned.

(defun simulator-almost-up-to-date? (time)
  (let* ((accumulator-compound-fixnum-simulation-time
	   (make-compound-fixnum-simulation-time))
	 (current-simulation-float-time
	     (extract-gensym-float-from-compound-fixnum-simulation-time
	       (progn
		 (add-compound-fixnum-simulation-times
		   accumulator-compound-fixnum-simulation-time
		   (current-simulation-time current-model-runtime-info?)
		   (simulation-base-time current-model-runtime-info?))
		 (add-compound-fixnum-simulation-times
		   accumulator-compound-fixnum-simulation-time
		   accumulator-compound-fixnum-simulation-time
		   (shortest-simulation-time-increment current-model-runtime-info?))
		 accumulator-compound-fixnum-simulation-time))))
    (reclaim-compound-fixnum-simulation-time
      accumulator-compound-fixnum-simulation-time)
    (if (not (<e current-simulation-float-time time))
	current-simulation-float-time)))




;;;; Simulation Meter Functions

;;; The following functions implement some meters of simulation activity.

;;; The function `simulator-time-lag' is called to determine how far simulation
;;; time is lagging behind gensym-time.  This will occur when there is too much
;;; simulation to be performed within the time allotted to the simulator.


(defun simulator-time-lag ()
  (with-current-model 
    nil nil
    (if (and (simulator-on? simulation-parameters)
	     (not (g1-authorized-p)))
	(let ((accumulator-compound-fixnum-simulation-time
		(make-compound-fixnum-simulation-time)))
	  (add-compound-fixnum-simulation-times
	    accumulator-compound-fixnum-simulation-time
	    (current-simulation-time current-model-runtime-info?)
	    (simulation-base-time current-model-runtime-info?))
	  (prog1
	    (maxe
	      (-e (time-since-base-time-as-gensym-float)
		  (+e 1.0
		      (extract-gensym-float-from-compound-fixnum-simulation-time
			accumulator-compound-fixnum-simulation-time)))
	      0.0)
	    (reclaim-compound-fixnum-simulation-time
	      accumulator-compound-fixnum-simulation-time)))
	0.0)))

;; This currently works only for the main model.  Extend mechanism to all models!

;; Adding 1 and doing maxf to prevent guaranteed lag if simulator suspends.  This
;; is necessary because the g2 meters are data servers and thus run at the same
;; priority as the simulator.  Thus, they can be called while the simulator is
;; suspended.  Since gensym-time is incremented at the beginning of the cycle, and
;; current-simulation-time only when the simulator is done, the 1 must be added.



;;;; Low Level Simulation Functions


(defun-simple state-variable-p (variable)
  (or (eq (simulation-category? variable)
	  'continuous-state)
      (eq (simulation-category? variable)
	  'discrete-state)))


(defun-simple continuous-state-variable-p (variable)
  (eq (simulation-category? variable)
      'continuous-state))


(defun-simple discrete-state-variable-p (variable)
  (eq (simulation-category? variable)
      'discrete-state))

#+unused
(defun-simple input-variable-p (variable)
  (eq (simulation-category? variable)
      'input))


(defun-simple dependent-variable-p (variable)
  (eq (simulation-category? variable)
      'dependent))


(defun-simple externally-simulated-variable-p (variable)
  (eq (simulation-category? variable) 'external))

;; Consider making these macros!





;;;; Notes on Integration Functions and Data Structures

;; Move these notes to top of file.  Consider moving some of these notes
;; to a file outside ab.

;;; Integration Algorithms 
;;; (for solving ordinary first order differential equations)
;;;
;;; For a first order system, the equations are:
;;;
;;; Euler Integration Algorithm
;;;
;;; If 
;;;      x' = f(t,x) 
;;; then the numerical solution for x using a time step of h is given by
;;;      x(t0 + h) = x0 + h f(t0,x0)
;;; where t0 is the initial time and 
;;;      x0 = x(t0).
;;;
;;;
;;; Fourth Order Runge Kutta Integration Algorithm
;;;
;;; The Runge Kutta algorithm gives the solution for x as
;;;      x(t0 + h) = x0 + (1/6)(k1 + 2 k2 + 2 k3 + k4)
;;; where
;;;      k1 = h f(t0, x0)
;;;      k2 = h f(t0 + h/2, x0 + k1/2)
;;;      k3 = h f(t0 + h/2, x0 + k2/2)
;;;      k4 = h f(t0 + h, x0 + k3)
;;;
;;;
;;; For an nth order system, the equations are:
;;;
;;;      x1' = f1(t, x1, x2, ... xn)
;;;
;;; For Euler,
;;;
;;;      x1(t0 + h) = x10 + h f1(t0, x10, x20, ... xn0)
;;;
;;; The Euler algorithm is easy to implement for an nth order system.
;;; The Runge-Kutta algorithm is a little more complicated for an nth order system.
;;; For a second order system, the RK4 algorithm is:
;;;
;;;      x1(t0 + h) = x10 + (1/6)(k11 + 2 k12 + 2 k13 + k14)
;;;      x2(t0 + h) = x20 + (1/6)(k21 + 2 k22 + 2 k23 + k24)
;;; where
;;;      k11 = h f1(t0, x10, x20)
;;;      k12 = h f1(t0 + h/2, x10 + k11/2, x20 + k21/2)
;;;      k13 = h f1(t0 + h/2, x10 + k12/2, x20 + k22/2)
;;;      k14 = h f1(t0 + h, x10 + k13, x20 + k23)
;;;
;;;      k21 = h f2(t0, x10, x20)
;;;      k22 = h f2(t0 + h/2, x10 + k11/2, x20 + k21/2)
;;;      k23 = h f2(t0 + h/2, x10 + k12/2, x20 + k22/2)
;;;      k24 = h f2(t0 + h, x10 + k13, x20 + k23)
;;;
;;; The first subscript for the above k's denotes the state variable while the 
;;; second subscript denotes the number of the k (1, 2, 3, or 4).
;;;
;;;
;;; For RK4, the update functions must be evaluated for values other than the 
;;; current values of the state variables (as is the case with the Euler implementation).
;;; This suggests using an evaluator other than sim-eval which takes an argument of
;;; the form 
;;;      ((state-variable value-to-use) ...)
;;; When coming to a state variable in an expression, this evaluator will use  
;;; value-to-use rather than the current value of the state variable.  
;;; Alternatively, value-to-use could be cached in a special slot for the state variable and
;;; the evaluator could check some global flag to decide which value to use.  This is 
;;; probably better.
;;;
;;; The other complication is that k values from other state variables have to be known
;;; to compute a new higher k value for a state variable.  The order of variable calculation
;;; can still be random.  However, k values have to be cached in a special slot of the 
;;; variable.  Successive computations must then be made for all state variables.
;;; For the k1 computation, previous values of state variables and t = t0 should be used.
;;; For the k2 computation, use previous values + k1/2 and t = t0 + h/2.
;;; For the K3 computation, use previous values + k2/2 and t = t0 + h/2.
;;; For the k4 computation, use previous values + k3 and t = t0 + h.  
;;;
;;; Thus, the k values are like previous values of state variables which are cached in some
;;; slot.  There should be no need to time stamp the k values since they are only calculated
;;; once.




;;;; Implementation of RK4

;;; Each cycle of the simulation should have a number of microsteps.  The basic 
;;; sequence should be as follows:
;;;
;;; 1.  Generation i ends.  Simulator is told to update values for generation i + 1.
;;;
;;; 2.  New values of input, state, and dependent variables are calculated, the 
;;; new value being put into the new-simulation-value slot time stamped with the
;;; simulation time corresponding to generation i + 1.  New values of state variables
;;; should be calculated using values of state and dependent variables from generation i.
;;; New values of dependent variables should be calculated from new values of state 
;;; variables and dependent variables (values from generation i + 1).
;;; This way, there is no skewing of generations between state and 
;;; dependent variables. 
;;;
;;; 3.  Update the variables calculated in step 2.  Transfer the value from
;;; the new-simulation-value to the simulation-value slot.  The new-simulation-value
;;; slot is now "empty" for the next cycle.
;;;
;;; 4.  For each variable, calculate the time when it should next be updated.
;;;
;;; 5.  Simulation time is incremented to correspond to generation i + 1.
;;;
;;;
;;; Initialization involves using the initial state and input data points to calculate all
;;; dependent variables for time 0.  After that, the simulator can begin operating in its
;;; normal cycle.
;;;
;;; This basic sequence works for difference equations and also differential equations
;;; when the Euler algorithm is used, and is currently implemented. 
;;; The sequence is a bit more complicated for RK4.
;;; As mentioned above, 4 "k" values have to be calculated involving 4 complete iterations
;;; in one simulation cycle.  The sequence for RK4 is as follows:
;;;
;;; 1.  Generation i ends.  Simulator is told to update values for generation i + 1.
;;;
;;; 2.  Set global step flag to rk-step-1.  Calculate k1 values for all state variables.
;;; Use current values of state variables and simulation time from previous generation. 
;;; The marker is 'rk-step-1.  Calculate dependent variables also based on simulation time
;;; from previous generation.  Thus the dependent variables will also have "k1" values.
;;;
;;; 3.  Set global step flag to rk-step-2.  Use k1 values from previous step to 
;;; calculate k2 values for state variables and dependent variables.
;;;
;;; 4.  Set global step flag to rk-step-3.  Calculate k3 values.
;;;
;;; 5.  Set global step flag to rk-step-4.  Calculate k4 values.
;;;
;;; 6.  Set global step flag to rk-step-5.  Calculate new values for state variables and
;;; dependent variables from the state-variable's k1, k2, k3, and k4 values.
;;;
;;; Will need a special slot to cache the k values.
;;;
;;; 7.  Update the variables calculated in step 6.  Transfer the value from
;;; the new-simulation-value to the simulation-value slot.  The new-simulation-value
;;; slot is now "empty" for the next cycle.
;;;
;;; 8.  For each variable, calculate the time when it should next be updated.
;;;
;;; 9.  Simulation time is incremented to correspond to generation i + 1.
;;;
;;; In the original RK4 algorithm, dependent variables are not used.  They are
;;; introduced here because they are needed for component connection capability.
;;; To implement the algorithm correctly, "k" values have to be calculated for
;;; the dependent variables as well as the state variables.  This is only so
;;; that the new calculated values of the state variables will be correct.
;;; The actual dependent variables can then be calculated.  
;;; The need to calculate "k" values for dependent variables can be seen clearly
;;; by considering the following equations where x is a state variable and
;;; y is a dependent variable of the state variable:
;;; 
;;;      x' = f(t, x)
;;;         = g(t, y)
;;; 
;;;      y = d(x)
;;; 
;;; K2 for x is then
;;; 
;;;      k2 = h f(t0 + h/2, x + k1/2)
;;;         = h g(t0 + h/2, yk1)
;;; 
;;;      yk1 = d(x + k1/2)




;;;; Notes

;; All floating point numbers in the simulator are gensym-floats.

;; An important unresolved issue is whether the user should have to explicitly
;; declare state variables or whether the system can somehow decide them itself.
;; Another approach might be Mike's suggestion to let the user specify either
;; the current value or the previous value of a variable.


;; If the simulation is run
;; in real time (Mike's airplane simulator with user input for example) then 
;; there is a limit on how small the simulation time step can be.  If the 
;; simulation is run in simulated time, there is no such limit.  


;; There is a minor issue about the timing of when simulated variables should be 
;; updated.  Suppose x is used to calculate y and the simulation time increment for x is
;; shorter than that for y.  New simulation values will be calculated for x but they 
;; won't be reflected in y as often.  This problem is analogous to the currency interval
;; problem with truth maintenance in the inference engine; if a variables value is current
;; should it be recalculated if supporting evidence changes?  I think in the case of the
;; simulator, it is up to the user to choose the correct time increments for all variables
;; and that the simulator should calculate variables according to those time increments.




;;;; More Notes

;; A more complex scheme for the microstep sequence in one simulator cycle is:

;; 1.  Generation i ends.  Simulator is told to update values for generation i + 1.

;; 2.  Simulation time is incremented to correspond to generation i + 1.

;; 3.  Input variables for generation i + 1 are calculated.  The new value is put
;; into the new-simulation-value slot and time stamped with the new simulation time.
;; It is also marked with an 'input-calculation-step flag to indicate the step of
;; the simulation.  The format for a value put in the new-simulation-value slot is
;; thus
;;      (value time step-marker)
;; The format for the simulation-value slot is still
;;      (value time)

;; 4.  Dependent variables affected by new values of input variables are calculated,
;; the new value being put into the new-simulation-value slot.  Steps 3 and 4 can
;; be done in brute force fashion, looping through all simulated variables randomly and 
;; calculating the new values for the input and dependent variables.  This would work
;; because of the similar nature of input and dependent variables.  A more sophisticated
;; approach would involve calculating the input variables first and then selectively 
;; forward chaining to only the affected dependent variables.

;; 5.  Update the variables calculated in steps 3 and 4.  Transfer the value from
;; the new-simulation-value to the simulation-value slot.  The new-simulation-value
;; slot is now "empty" for the next steps.

;; 6.  Calculate new values for state variables based on current values of state variables
;; and dependent and input variables.  Note that the current values of state variables are
;; the values from the previous generation whereas the current values of dependent variables
;; may be the values from the previous generation or they may be the new values due to new
;; input calculated in steps 3 and 4.  The flag for this simulation step is 'state-calculation-step.

;; 7.  Dependent variables affected by new values of state variables are calculated.
;; This is analogous to step 4.  Here also, a brute force or a sophisticated forward chaining
;; approach could be used.  If the brute force approach is used, then the new values for 
;; state variables and dependent variables can calculated in random order.

;; 8.  Update the variables calculated in steps 6 and 7 (similar to step 5).

;; 9.  For each variable, calculate the time when it should next be updated.


;; There are basically two steps
;;      1.  Calculate effects of new inputs.
;;      2.  Calculate new state and dependent variables.
;; In some sense, this is the right thing to do if one assumes that new inputs at
;; the clock tick should be propagated before states are updated.  However, this
;; adds unnecessary complexity and is incompatible with the Euler algorithm convention
;; of calculating x(t0 + h) using f (x(t0), t0).  It is also incompatible with the
;; convention when simulating digital logic.  I think the assumption that inputs
;; get propagated instantly before state transition occurs would not be made by
;; most people using the system.  In any case, the results shouldn't be much 
;; different so the simpler, conventional method has been implemented.




;; The simulator can handle time-dependent expressions.  The symbol 'time in an
;; expression causes sim-eval to return current-simulation-time, the current
;; simulation time.

;; The simulator can also find exact solutions if the expressions for the
;; exact solution are provided in the exact-solution-computation-method?
;; slot of the state variables and if the integration-algorithm of 
;; simulation-parameters is set to 'exact.




;;;; Plans

;; 1.  Test thoroughly with several benchmarks.  May want to provide 
;; some single step and trace facilities.
;; 
;; 2.  Do comparative error analysis of euler and rk4 algorithms.
;; 
;; 3.  Currently, for the runge-kutta algorithm, derivative functions of 
;; time are not allowed.  This can be fixed pretty easily.  Have a special
;; variable which is accessed by sim-eval whenever time is needed.  The
;; value in the special variable will be a function of simulation time 
;; and the simulator step (it will be either t0, t0 + h/2, t0 + h).
;; 
;; 4.  In the current implementation, there is some complexity when discrete and
;; continuous state variables are mixed.  Specifically, if a continuous state 
;; variable's first derivative were somehow a function of a dependent variable
;; which is a function of a discrete state variable, then that dependent variable
;; might be calculated 4 extra times when rk4 is used;;  a slight inefficiency.
;; The reason for this is that although the discrete state variable will be 
;; time stamped with the new generation (and therefore won't be recalculated)
;; the dependent variable will not.  It currently has no way of knowing that
;; it depends on a discrete state variable and it will be stamped with the
;; integration step.  Thus, it will unnecessarily be recalculated 4 extra times
;; when the Runge-Kutta algorithm is used.  
;; 
;; 5.  May eventually want the capability to designate some continuous state
;; variables to be integrated by rk4 and some by euler.  However, this would
;; add much complexity and little usefulness I think.
;; 
;; 
;; 7.  Sim-eval-value-flag is not exactly obsolete but it is close.  This
;; could be improved.
;; 
;; 8.  Read papers on simulation.  Look at notes.  There are a lot of ideas 
;; there.  Time-step vs. event-driven simulators.  The current implementation
;; is time-step.  Simulating non-linear systems by components (see electronics
;; article.





;;;; Detailed Description of Step Mechanism of Simulator

;; Initialization Simulation time is set to -1.  (rk4-step
;; current-model-runtime-info?) is bound to nil.  For state variables,
;; new-simulation-value is set to initial-value-for-simulation.
;; (simulator-step-flag current-model-runtime-info?) is bound to
;; 'calculating-new-values-for-dependent-variables.  For input variables,
;; new-simulation-value is calculated by formula with time = 0 (not -1).  For
;; dependent-variables, new-simulation-value is calculated by using formulas which
;; are functions of other dependent-variables, input-variables, and
;; state-variables.  Whenever a new-simulation-value is calculated,
;; new-simulation-value-time is set to 0.  This then indicates that a new value
;; has already been calculated and this value will subsequently be used rather
;; than trying to calculate the value again.  When new values have been calculated
;; for all variables, they are all updated.  New-value is transferred to
;; current-value, and current-simulation-time is incremented.  The clock "ticks".


;; 1.  Discrete Case (no continuous state variables)
;; 
;; 
;; Calculating New Values in a Simulation Cycle
;; Suppose simulation time is i and shortest-simulation-time-increment is 1.
;; (rk4-step current-model-runtime-info?) and *euler-step* are set to nil.  
;; (simulator-step-flag current-model-runtime-info?) is bound to 
;; 'calculating-new-values-for-discrete-state-variables.
;; For state variables, new-simulation-value is calculated by its 
;; simulation formula which is a formula which is a function of
;; other variables which can be input, state, or dependent variables.
;; The current simulation-value (value at time i) of these
;; variables is used in the formula to calculate the new-simulation-value
;; (value at time i + 1) of the state variable.
;; *simulator-step-flag* is bound to 
;; 'calculating-new-values-for-discrete-state-variables.
;; For input variables, new-simulation-value is calculated by formula with 
;; time = i + 1.
;; For dependent-variables, new-simulation-value is calculated by using
;; formulas which are functions of other dependent-variables, input-variables,
;; and state-variables.  
;; New-simulation-value-time is set to i + 1 whenever a new-simulation-value
;; is calculated so that the value is calculated only once.
;; 
;; Thus, for the discrete case, the sequencing of the simulator is simple.
;; *simulator-step-flag* is 'calculate-new-values-for-discrete-state-variables,
;; then 'calculate-new-values-for-discrete-state-variables.
;; Only new-simulation-value-time
;; has to be checked to see if a new-simulation-value has been calculated
;; for a variable.  
;; If current-simulation-time is i and new-simulation-value-time = i +
;; shortest-simulation-time-increment, then new value has been calculated.
;; 
;; These issues are illustrated by the simple example below.
;; 
;; 
;;                 -----
;;        ---------|not|-------------- dv1
;;        |        -----    |
;;        |                 |   ----
;;        |                 ----|or|-- dv2
;;        |                 ----|  |
;;        |                 |   ----
;;        |    ------       |
;; i1 ---------|D  Q|----------------- sv1
;;             |    |
;;          ---|Clk |
;;          |  ------
;;          |
;;          |
;;         Clock
;; 
;; 
;; Timing Diagram:
;; 
;; Clock   |---|---|---|---|---|---
;;         0   1   2   3   4   5
;; 
;; i1       1   0   1   0   1   0
;; 
;; sv1      1   1   0   1   0   1
;; 
;; dv1      0   1   0   1   0   1
;; 
;; dv2      1   1   0   1   0   1
;; 
;; 
;; Input variable i1 is a square wave function of time.
;; State variable sv1 is a function of i1 and sv1's new value
;; is computed from i1's current value.  Dependent variable dv1's
;; new value is computed from i1's new value.  Dependent variable
;; dv2's new value is computed using the new values of dv1 and sv1.


;; 2.  Continuous Case (using Euler integration)

;; Continuous state variables are handled before others.  If the 
;; integration method is 'euler, (simulator-step-flag current-model-runtime-info?) is bound to
;; 'calculate-euler-k-values.  The k value for each continuous state
;; variable is then calculated using the differential equation which is
;; the simulation formula.  
;; Thus, no "backward chaining" takes place here.  When k values for
;; each continuous state variable have been calculated, (simulator-step-flag current-model-runtime-info?)
;; is bound to 'calculate-euler-new-values.  New values are then calculated
;; for each continuous state variable using the k values.  
;; New-simulation-value-time is also set to the next generation time
;; when new-simulation-value is calculated.
;; 
;; Other variables are then processed as before.


;; 3.  Continuous Case (using rk4 integration)
;; 
;; (see also above discussion of rk4 integration)
;; 
;; Continuous state variables are handled before others.  (simulator-step-flag current-model-runtime-info?)
;; is bound to 'calculate-rk4-k-values.  *rk4-step* is bound to 1.
;; *rk4-step* is then bound to 2.  
;; K2 values for state variables are then calculated from the k1
;; values according to the rk4 formula.  Specifically, sim-eval is called.
;; New values are then calculated for dependent variables.  When a state
;; variable is reached, rather than using its current value, the value
;; current value + k1 / 2 will be used.  The values in the new-simulation-value
;; slots of the dependent variables will be "k" values for the dependent variables
;; corresponding to the (current-value + k1/2) value of the state variables.
;; Note that at this point, the new-simulation-value-time slot of the dependent
;; variables is not updated.  To ensure that the new-values for the dependent
;; variables are only calculated once, the new-simulation-value-step slot
;; has to be set, in this case, to 1.  To check if a new "k" value has been
;; calculated for a dependent variable, compare *rk4-step* to 
;; new-simulation-value-step.  If new-simulation-value-step = *rk4-step* - 1,
;; then new "k" value has been calculated.
;;  
;; *rk4-step* is next bound to 3.  K3 values for continuous state variables
;; are then calculated from k2 values.  When a new-value is calculated for
;; a dependent variable, the new-simulation-value-step slot is set to 2.
;; *rk4-step* is next bound to 4.  K4 values for continuous state variables
;; are then calculated from k3 values.  When a new-value is calculated for
;; a dependent variable, the new-simulation-value-step slot is set to 3.
;; 
;; At this point, all k values for the continuous state variables have been
;; calculated.  (simulator-step-flag current-model-runtime-info?) is set to 'calculate-rk4-new-values
;; and new values are calculated from the k values.  Sim-eval is not called here.
;; New-simulation-value-time is also updated to the new generation as new values
;; are found. 
;; 
;; Other values are then processed as in the discrete case. 
;; 
;; 
;; The simulator steps are summarized in the table below
;; (assume current simulation time is i and shortest-simulation-time-increment is 1).
;; 
;; 1.  Discrete State Variables Only
;; 
;; (simulator-step-flag current-model-runtime-info?) = 'calculate-new-values
;; state variables - sim-eval uses values from time i
;; dependent variables - sim-eval uses values from time i + 1 to calculate new values
;; input variables - sim-eval uses values from time i + 1 to calculate new values
;; new-value calculated - indicated by new-value-simulation-time being i + 1.


;; 2.  Continuous State Variables (Euler integration)
;; 
;; (simulator-step-flag current-model-runtime-info?) = 'calculate-euler-k-values
;; k value for state variables - sim-eval uses values from time i
;; (simulator-step-flag current-model-runtime-info?) = 'calculate-euler-new-values
;; new value for state variables - calculated only from k value (sim-eval not called)
;; new-simulation-value-time = i + 1
;; process other variables
;; 
;; 
;; 3.  Continuous State Variables (rk4 integration)
;; 
;; (simulator-step-flag current-model-runtime-info?) = 'calculate-rk4-k-values
;; *rk4-step* = 1
;; k1 value for state variables - sim-eval uses values from time i
;; 
;; *rk4-step* = 2
;; k2 value for state variables
;;     - sim-eval uses
;;         - for state variables (value at time i + k1/2)
;;         - for dependent-variables, calculate new-simulation-value based on
;;           state variables.  New-simulation-value thus contains the "k"
;;           value for the dependent-variable.  
;;       - in both cases, value is made new-simulation-value.
;;         However, new-simulation-value-time is not yet set to i + 1.
;;         Rather, new-simulation-value-step is set to 1.  This can then
;;         be used, along with the value of *rk4-step* to ensure that 
;;         values are only calculated once.
;; 
;; *rk4-step* = 3
;; k3 value for state variables
;;     - sim-eval uses
;;         - for state variables (value at time i + k2/2)
;;         - dependent-variables as with previous step
;;       - new-simulation-value-step is set to 2.
;; 
;; *rk4-step* = 4
;; k4 value for state variables
;;     - sim-eval uses
;;         - for state variables (value at time i + k3)
;;         - dependent-variables as with previous step
;;       - new-simulation-value-step is set to 3.
;; 
;; (simulator-step-flag current-model-runtime-info?) = 'calculate-rk4-new-values
;; new value for state variables - calculated only from k values (sim-eval not called)
;; new-simulation-value-time = i + 1
;; process other variables





;; To compile simulation expressions, turn them into lambda expressions.
;; Where variables occur, they must be preceded by an appropriate function
;; so that the variable isn't lisp evaluated.  Talk to Lowell before doing
;; this since there are system-wide issues here (calling the lisp compiler
;; during installation, machine dependencies)
;; This should be done.  Benchmarks by Mike suggest 100 to 1 improvement
;; for compiled code.








;;;; Test Functions

#+development
(defun sim-values-given-names (names)
  (loop for name in names 
	as variable
	   = (get-instance-with-name-if-any 'entity name)
	as runtime-structure
	   = (when variable
	       (simulation-runtime-information? variable))
	do
    (cond 
      (runtime-structure
       (print-runtime-structure-data runtime-structure name))
      (t
       (cerror "" "no runtime structure")))))

#+development
(defun sim-values (variable-or-structure)
  (cond
    ((variable-p variable-or-structure)
     (print-runtime-structure-data 
       (simulation-runtime-information? variable-or-structure)))
    ((simulation-info-p variable-or-structure)
     (print-runtime-structure-data 
       (runtime-info? variable-or-structure)))
    ((variable-simulation-runtime-structure-p variable-or-structure)
     (print-runtime-structure-data variable-or-structure))
    (t
     (cerror "" "no runtime structure"))))

#+development
(defun print-runtime-structure-data (runtime-structure &optional name)
  (when name (format t "~%~a :~%" name))
  (format t "old-value = ~S~%"
	  (extract-number-or-value
	    (simulation-value runtime-structure)))
  (format t "new-value = ~S~%"
	  (extract-number-or-value
	    (new-simulation-value runtime-structure)))
  (format t "k1 = ~S~%"
	  (extract-number-or-value
	    (k1-value runtime-structure)))
  (format t "k2 = ~S~%"
	  (extract-number-or-value
	    (k2-value runtime-structure)))
  (format t "k3 = ~S~%"
	  (extract-number-or-value
	    (k3-value runtime-structure)))
  (format t "k4 = ~S~%"
	  (extract-number-or-value
	    (k4-value runtime-structure))))



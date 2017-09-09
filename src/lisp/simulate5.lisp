;; -*- Mode:Lisp; Package: AB; base: 10; Syntax: Common-lisp -*-
(in-package "AB")

;;;; Module SIMULATE5

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Andreas Hofmann





;;;; Overview

;; (see also ma:>agh>simulation-1-2.text)



(declare-forward-reference delete-from-external-simulation-runtime-structures function)
(declare-forward-reference write-list-in-chicago-style function)
(declare-forward-reference bad-g2-array-length-stack-error function)
(declare-forward-reference time-used-to-adjust-histories? variable)
(declare-forward-reference truncate-evaluation-float-function function)




;;;; Models

;;; The concept of a model is introduced here in order to overcome limitations of
;;; the simulator as it exists in 2.0.  These include the limitation that there
;;; can only be one simulation running at a time, as well as the fact that
;;; simulations can not be easily controlled by rules or procedures.

;;; A model is a grouping of variables to be simulated together, along with
;;; specifications on how the simulation should be performed (specifications like
;;; time increment).  The user can define any number of models and run them
;;; independently as needed.  This greatly enhances the flexibility of G2.  Models
;;; can be specified for various parts of a knowledge base and for various
;;; purposes (simulating real data, data reconciliation, prediction,
;;; optimization).  Rules or procedures can control simulation of the models,
;;; starting them and stopping them as needed.  For example, a model for the
;;; entire system can be used to generate data for off-line testing.  A model for
;;; some portion can be used to predict.  Another model, for perhaps another
;;; portion can be used to filter sensor data.  When running on-line, the model
;;; for generating data would be turned off.  The other models would be started
;;; and stopped when the inference engine decides they are needed.

;;; A model is defined using a model-definition.  A model is instantiated from a
;;; workspace menu by choosing new definition, and then choosing model definition
;;; on the resulting menu (just as object definitions are instantiated, for
;;; example).  A model-definition contains slots corresponding to each slot in the
;;; simulation-parameters system table as well as all the slots of entity, the
;;; superior class of model-definition.  In addition, it has the following slots:

;;; items-belonging-to-this-model,
;;; model-runtime-info?,
;;; simulation-time-for-model,
;;; model-simulation-status,
;;; simulation-control-specifications.

;;; Items-belonging-to-this-model is used for installation (see below).
;;; Model-runtime-info?  contains a model-runtime-info structure which contains
;;; runtime state for the model.

;;; Simulation-time-for-model gives the simulated time for the model.

;;; Model-simulation-status can be running, not-running, paused, nothing-to-simulate, or
;;; an error string indicating that an error has occurred and that the model is no
;;; longer running.

;;; Model-simulation-status is closely related to the model-runtime-status slot of the
;;; model-runtime-info.  The model-runtime-status slot can have values 'running,
;;; 'needs-to-be-initialized, 'needs-to-be-shutdown, or nil.  If the value is nil,
;;; then the model is not in a model-queue, otherwise it is (see doc for
;;; model queues).

;;; Simulation-control-specifications is a user editable slot which determines
;;; various modes for the model.  A model can "run synchronously", in which case
;;; the model is run until its simulation time is consistent with gensym time.  A
;;; model can "run as fast as possible", in which case the model is run until it
;;; is reset (at the priority of simulation data service).  If "without
;;; incrementing simulation time" is specified, the simulation time for the model
;;; will not be incremented (this is useful when iterating to converge on solution
;;; of an algebraic model such as a flow network).  If "without waiting for
;;; simulation procedure or gspan external simulation cycle to finish" is
;;; specified, this indicates that it is ok to work on the next model in the queue
;;; if this model is waiting for external simulation or for a procedure.





;;;; Designation and Installation of Variables Belonging to a Model

;;; The items-belonging-to-this-model slot of a model-definition is used to
;;; designate variables belonging to the model.  This slot can contain:

;;; 1) workspace names, 
;;; 2) object and connection names, and 
;;; 3) object and connection classes.  

;;; An object or connection belongs to a model if one or more of the following are
;;; true:

;;; 1) its name is in the items-belonging-to-this-model slot of the model, 
;;; 2) its superior frame (see function superior-frame) belongs to the model, or
;;; 3) it is a subclass of a class in the items-belonging-to-this-model slot of the model.

;;; Note, that simulation formulas play no part whatsoever in determining whether
;;; objects or connections belong to models.

;;; Install-item-in-model-if-appropriate takes as argument an item, and determines
;;; whether the item belongs to a model by calling
;;; get-model-to-which-item-belongs.  If the item is a variable or parameter, and
;;; it belongs to a model, it is marked as belonging to the model (by the function
;;; mark-variable-as-belonging-to-model).  Then,
;;; install-item-in-model-if-appropriate calls itself recursively for subitems of
;;; the item.

;;; Besides the item, install-item-in-model-if-appropriate takes two additional
;;; arguments: model-definition-for-superior-item?, and check-superior-items?.
;;; When check-superior-items?  is t, get-model-to-which-item-belongs goes up the
;;; instance hierarchy (using superior-frame) until it finds a model or reaches
;;; top level.  When check-superior-items?  is nil,
;;; get-model-to-which-item-belongs checks only the item itself.  Thus, when
;;; install-item-in-model-if-appropriate is called at top level,
;;; check-superior-items?  should be t (and model-definition-for-superior-item?
;;; nil) to indicate that the instance hierarchy must be searched.  When
;;; install-item-in-model-if-appropriate calls itself recursively, it passes
;;; either the model definition found by get-model-to-which-item-belongs or
;;; model-definition-for-superior-item?  as the
;;; model-definition-for-superior-item?  arg, and passes nil for
;;; check-superior-items?.  Thus, for recursive calls to
;;; install-item-in-model-if-appropriate, get-model-to-which-item-belongs need
;;; only check the item itself; it does not have to search up the instance
;;; hierarchy.

;;; To determine whether an item belongs to a model,
;;; get-model-to-which-item-belongs checks if the
;;; model-definition-for-item-or-class property of any name of the item contains a
;;; model-definition.  If so, then the item belongs to the model and the
;;; model-definition is returned.  If not, and the item is an object or connection
;;; (rather than a kb-workspace), then get-model-to-which-item-belongs checks the
;;; model-definition-for-item-or-class property of the item's class and all of its
;;; superior classes up to 'object or 'connection.  If any of these properties
;;; contain a model-definition, then the item belongs to the model and the
;;; model-definition is returned.

;;; Install-item-in-model-if-models-used calls
;;; install-item-in-model-if-appropriate if models are being used.  This is done
;;; because install-item-in-model-if-appropriate can, currently, be inefficient
;;; (see notes below) and therefore should not be called unless models are being
;;; used.  Install-item-in-model-if-models-used must be called in the following
;;; circumstances:

;;; 1) when a transient object or connection is made 
;;;    (see make-transient-object-or-message, make-transient-connection),
;;; 2) when a connection frame is made (see activate-connection-frame-if-appropriate),
;;; 3) when an object is added to or removed from an attribute of another object
;;;    (see put-attribute-value),
;;; 4) when an object is transferred to a workspace 
;;;    in workstation-context for dragging  (i.e. make-outline-for-blocks-to-drag),
;;;    and transfer-item for rule action case).

;;; Note that these are all cases where activate-if-possible-and-propagate methods
;;; are also called.  It is useful to look at this since there are similarities.
;;; Note also that 1, 2, and 3 are taken care of by simulation installation
;;; (see 4 below).

;;; In addition to these cases, the installation operation must be performed

;;; 1) when the name of an object, connection, or workspace is changed
;;;    (see add-as-frame-with-name, delete-as-frame-with-name),
;;; 2) when the class of an object or connection is changed
;;;    (see update-name-of-user-class),
;;; 3) when a designation is added to or removed from the
;;;    items-belonging-to-this-model slot of a model definition
;;;    (see slot putter),
;;; 4) whenever a variable or parameter is simulation installed via
;;;    one of the functions 
;;;    put-generic-simulation-formula-into-variable-or-parameter,
;;;    put-specific-simulation-formula-into-variable-or-parameter, or
;;;    put-external-simulation-formula-into-variable-or-parameter,
;;; 5) in the post loading function install-models-after-loading,
;;; 6) subworkspace cloning (when it is implemented).

;;; In the case of simulation installation, the model installation must be done
;;; after the simulation installation, because mark-variable-as-belonging-to-model
;;; will do nothing if the variable is not being simulated (if there is no
;;; simulation-info structure).  Thus, the simulation installation put-...
;;; functions call install-item-in-model-if-models-used after they are finished
;;; with simulation installation.

;;; Note that when a class is first defined, there are no instances so no
;;; simulation installation need be done.  When a class is undefined, all
;;; instances are deleted and when an object which belongs to a model is deleted,
;;; nothing has to be done because the simulation-info structure, which contains
;;; the pointer to the model-definition, is deleted as well.

;;; The post loading function install-models-after-loading is necessary because
;;; reading a saved kb does not make use of add-subblock, or any such function.



(def-class (model-definition (item entity) (foundation-class model-definition)
			     define-predicate)

  ;; initialize method now deals with initial setup -- this slot's init form
  ;; will now be nil, and inherited. (MHD 7/18/94)
;  (frame-status-and-notes (:funcall slot-value-cons-function incomplete nil))
  (frame-author-or-authors nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))

  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60 
      ((outline (0 0) (60 0) (60 60) (0 60))
       (outline (1 1) (59 1) (59 59) (1 59))
       (lines (10 50) (10 10) (30 40) (50 10) (50 50))
       )))

  (model-runtime-info?
    (:funcall initialize-model-runtime-info) system vector-slot)

  (items-belonging-to-this-model 
    nil (type item-designations-for-model text) system)

  (default-simulation-time-increment-for-model 
    (:funcall initialize-default-simulation-time-increment-for-model)
    system user-overridable
    (type simulation-time-increment))
  (integration-algorithm-for-model
    euler system user-overridable (type integration-algorithm-specification))
  (external-simulator-configuration-for-model
    nil system (type xsi-host-configuration text))
  (simulation-procedure-for-model nil system user-overridable (type procedure-name?))
  (send-all-values-at-beginning-of-cycle-for-model?
    nil system user-overridable (type yes-or-no))
  (vector-from-external-simulator-for-model nil system)
  (vector-to-external-simulator-for-model nil system)

  (simulation-time-for-model nil system vector-slot)
  (model-simulation-status 
    not-running not-user-editable (type attribute) do-not-save)
  (simulation-control-specifications 
    (:funcall initialize-simulation-control-specifications)
    system user-overridable (type simulation-control-specification))
  )





(define-slot-alias default-simulation-time-increment default-simulation-time-increment-for-model
  model-definition)

(define-slot-alias integration-algorithm integration-algorithm-for-model
  model-definition)

(define-slot-alias external-simulator-configuration external-simulator-configuration-for-model
  model-definition)

(define-slot-alias simulation-procedure simulation-procedure-for-model
  model-definition)

(define-slot-alias send-all-values-at-beginning-of-cycle send-all-values-at-beginning-of-cycle-for-model?
  model-definition)

(def-slot-putter integration-algorithm-for-model (frame new-value)
  (when (and (eq (integration-algorithm-for-model frame) 'rk4)
	     (not (eq new-value 'rk4))
	     (model-runtime-info? frame))
    (setf (rk4-step (model-runtime-info? frame)) nil))
  (setf (integration-algorithm-for-model frame ) new-value))


;; jh, 10/4/91.  Need model-runtime-info-function?  for a forward reference in
;; SIMULATE1.

(defun model-runtime-info-function? (frame)
  (model-runtime-info? frame))

(defun initialize-default-simulation-time-increment-for-model ()
  (allocate-managed-float 0.5d0))

(defun initialize-simulation-control-specifications ()
  (slot-value-list 'synchronously))

(defun model-paused? (model)
  (let ((model-definition? (model-definition-for-model? model)))
    (and model-definition? 
	 (eq (model-simulation-status model-definition?) 'paused))))

(def-class-method cleanup (model-definition)
  (funcall-superior-method model-definition)
  (change-slot-value model-definition 'items-belonging-to-this-model nil)
  (let ((model-runtime-info? (model-runtime-info? model-definition)))
    (when (memq model-runtime-info? 
		(models-in-queue (get-model-queue-for-model model-runtime-info?)))
      ;; model is currently running
      (shutdown-simulator model-runtime-info? model-definition))))

(def-slot-value-reclaimer model-runtime-info? (model-runtime-info?)
  (when model-runtime-info?
    (let ((current-model-runtime-info? model-runtime-info?))
      (reclaim-model-runtime-info model-runtime-info?))))



;;;; Abstracted Accessor Primitives

;;; The following are abstracted accessors and other functions for info in
;;; model-definitions and simulation-parameters system table.

(defmacro synchronous-mode-for-model (model-definition)
  `(first (simulation-control-specifications ,model-definition)))

(defmacro dont-increment-simulation-time-for-model? (model-definition)
  `(second (simulation-control-specifications ,model-definition)))

(defmacro dont-wait-for-model-to-finish? (model-definition)
  `(third (simulation-control-specifications ,model-definition)))

(defun dont-wait-for-model-to-finish-function? (model-runtime-info)
  (let ((model-definition?
	  (model-definition-for-model? model-runtime-info)))
    (when model-definition?
      (dont-wait-for-model-to-finish? model-definition?))))

(defun increment-simulation-time-for-current-model? ()
  (let ((model-definition?
	  (model-definition-for-model? current-model-runtime-info?)))
    (or (null model-definition?)
	(not (dont-increment-simulation-time-for-model? model-definition?)))))

(defun current-model-is-paused? ()
  (let ((model-definition?
	  (model-definition-for-model? current-model-runtime-info?)))
    (and model-definition?
	 (eq (model-simulation-status model-definition?) 'paused))))

(defun get-model-queue-for-model (model-runtime-info?)
  (let ((model-definition? 
	  (if model-runtime-info?
	      (model-definition-for-model? model-runtime-info?)
	      current-model-definition?))
	key-for-queue-to-use)
    (cond
      (model-definition?
       (setq key-for-queue-to-use
	     (synchronous-mode-for-model model-definition?))
       (if (eq key-for-queue-to-use 'as-fast-as-possible)
	   as-fast-as-possible-model-queue
	   synchronous-model-queue))
      (t synchronous-model-queue))))

(defun get-model-runtime-info-for-variable (variable-or-parameter)
  (let* ((simulation-info? (simulation-info? variable-or-parameter))
	 (model-definition? 
	   (when simulation-info? (model-definition? simulation-info?))))
    (if model-definition?
	(model-runtime-info? model-definition?)
	main-model-runtime-info)))

(defun current-default-simulation-time-increment ()
  (slot-value-number-value
    (if current-model-definition?
	(default-simulation-time-increment-for-model current-model-definition?)
	(default-simulation-time-increment simulation-parameters))))

(defun current-integration-algorithm ()
  (if current-model-definition?
      (integration-algorithm-for-model current-model-definition?)
      (integration-algorithm simulation-parameters)))

(defun current-external-simulator-configuration ()
  (if current-model-definition?
      (external-simulator-configuration-for-model current-model-definition?)
      (external-simulator-configuration simulation-parameters)))

(defun current-simulation-procedure ()
  (if current-model-definition?
      (simulation-procedure-for-model current-model-definition?)
      (simulation-procedure simulation-parameters)))

(defun current-send-all-values-at-beginning-of-cycle? ()
  (if current-model-definition?
      (send-all-values-at-beginning-of-cycle-for-model? current-model-definition?)
      (send-all-values-at-beginning-of-cycle? simulation-parameters)))

(defun current-vector-from-external-simulator ()
  (if current-model-definition?
      (vector-from-external-simulator-for-model current-model-definition?)
      (vector-from-external-simulator simulation-parameters)))

(defun current-vector-to-external-simulator ()
  (if current-model-definition?
      (vector-to-external-simulator-for-model current-model-definition?)
      (vector-to-external-simulator simulation-parameters)))

(defun change-vector-from-external-simulator (vector)
  (if current-model-definition?
      (change-slot-value
	current-model-definition? 'vector-from-external-simulator-for-model 
	vector)
      (change-slot-value
	 simulation-parameters 'vector-from-external-simulator vector)))

(defun change-vector-to-external-simulator (vector)
  (if current-model-definition?
      (change-slot-value
	current-model-definition? 'vector-to-external-simulator-for-model
	vector)
      (change-slot-value
	simulation-parameters 'vector-to-external-simulator vector)))

(defmacro with-current-model-for-simulation-procedure
	  (model-definition-or-t &body body)
  `(let (current-model-runtime-info? current-model-definition?)
     (if (framep ,model-definition-or-t)  ; if model definition
	(setq current-model-definition? ,model-definition-or-t
	      current-model-runtime-info? 
	      (model-runtime-info? ,model-definition-or-t))
	(setq current-model-definition? nil
	      current-model-runtime-info? main-model-runtime-info))
     ,@body))

;; This assumes model-definition-or-t is always a symbol.





(defun restart-simulator-after-procedure (completion-form)
  (restart-simulator-after-procedure-1 (second completion-form)))

(defun restart-simulator-after-procedure-1 (model-definition-or-t)
  (with-current-model-for-simulation-procedure 
    model-definition-or-t
    (setf (simulation-procedure-finished? current-model-runtime-info?) t
	  (simulation-procedure-invocation-for-model?
	    current-model-runtime-info?)
	  nil)
    (when (or system-is-running system-has-paused)
      (end-simulation-procedure-or-external-simulation-cycle))))



(defun get-model-runtime-info-given-icp-socket (icp-socket)
  (if (and main-model-runtime-info
	   (eq (external-simulator-interface-icp-socket
		 main-model-runtime-info)
	       icp-socket))
      (values main-model-runtime-info nil)
      (loop for md being each class-instance of 'model-definition
	    as model-runtime-info?
	       = (model-runtime-info? md)
	    do
	(when (eq (external-simulator-interface-icp-socket
		    model-runtime-info?)
		  icp-socket)
	  (return (values model-runtime-info? md))))))

;; blm & jh, 9/30/91.  Added inner let scope to multiple-value-bind form because
;; chestnut does not translate special variable bindings properly from a
;; multiple-value-bind form, though it does from a let form.

(defmacro with-current-model-for-icp-socket (icp-socket &body body)
  (avoiding-variable-capture (&aux current-model-runtime-info-lexical?
				   current-model-definition-lexical?)
    `(multiple-value-bind
       (,current-model-runtime-info-lexical? ,current-model-definition-lexical?)
	 (get-model-runtime-info-given-icp-socket ,icp-socket)
       (let ((current-model-runtime-info? ,current-model-runtime-info-lexical?)
	     (current-model-definition? ,current-model-definition-lexical?))
	 (when current-model-runtime-info?   ; should always be the case
	   ,@body)))))

(defmacro with-current-model-for-variable (variable-or-parameter &body body)
  `(let* (current-model-runtime-info? current-model-definition?
	  (simulation-info? (simulation-info? ,variable-or-parameter))
	  model-definition?)
     (when simulation-info?
       (setq model-definition? (model-definition? simulation-info?))
       (if model-definition?
	   (setq current-model-definition? model-definition?
		 current-model-runtime-info? 
		 (model-runtime-info? model-definition?))
	   (setq current-model-definition? nil
		 current-model-runtime-info? main-model-runtime-info))
       ,@body)))



(defmacro with-current-model-for-variable-if-necessary
	  (variable-or-parameter &body body)
  `(if current-model-runtime-info?
       ,@body
       (let* (current-model-runtime-info? current-model-definition?
	      (simulation-info? (simulation-info? ,variable-or-parameter))
	      model-definition?)
	 (when simulation-info?
	   (setq model-definition? (model-definition? simulation-info?))
	   (if model-definition?
	       (setq current-model-definition? model-definition?
		     current-model-runtime-info? 
		     (model-runtime-info? model-definition?))
	       (setq current-model-definition? nil
		     current-model-runtime-info? main-model-runtime-info)))
	 (when (or simulation-info? (parameter-p variable-or-parameter))
	   ,@body))))

;; This is coded for speed efficiency so body is expanded twice.  Care should be
;; taken to keep the body small.



(defun make-variable-simulation-runtime-structure-with-model (variable)
  (with-current-model-for-variable 
    variable
    (make-and-initialize-variable-simulation-runtime-structure variable)))







;;;; Adding and Removing Variables from Simulation

;;; Add-variable-to-simulation and remove-variable-from-simulation perform
;;; both installation and runtime actions.  

;;; Note that both of these call update-runtime-structures-according-to-edit
;;; for the parent frame of the variable if any and for the variable itself.
;;; This is because adding or removing a variable from simulation is really
;;; due to a kb edit and other variables which are effected by this variable
;;; must be notified.  For example, if a generic simulation formula is 
;;; deleted, variables that use it may be removed from the simulation.
;;; Variables that are effected by this variable must have their runtime
;;; formulas rederived.  Otherwise, these runtime formulas could contain
;;; variable-simulation-runtime-structures that have been deleted.
;;; This may cause unnecessary rederivation but this is never a problem.
;; (see also design book notes for 8/3/88).

(defun add-variable-to-simulation (variable)
  (with-current-model-for-variable 
    variable
    (add-variable-to-simulation-model variable)
    (when (any-models-running?)
      (add-to-variables-to-be-rederived variable)
      (let ((parent-frame? (parent-frame variable)))
	(if parent-frame?
	    (update-runtime-structures-according-to-edit parent-frame? t)))
      (update-runtime-structures-according-to-edit variable t))))

(defun remove-variable-from-simulation (variable)
  (with-current-model-for-variable 
    variable
    (remove-variable-from-simulation-model variable)
    (remove-from-variables-to-be-rederived variable)
    (let ((variable-simulation-runtime-structure?
	    (simulation-runtime-information? variable)))
      (when (any-models-running?)
	(setf (simulated-variable-removed? current-model-runtime-info?) t)
	(when variable-simulation-runtime-structure?
	  (let ((parent-frame? (parent-frame variable)))
	    (if parent-frame?
		(update-runtime-structures-according-to-edit parent-frame? t)))
	  (update-runtime-structures-according-to-edit variable t)
	  (when (frame-being-deleted-p variable)
	    (delete-from-external-simulation-runtime-structures
	      variable-simulation-runtime-structure?))))
      (when variable-simulation-runtime-structure?
	(reclaim-variable-simulation-runtime-structure
	  variable-simulation-runtime-structure?)))))

;; Note that generate-formula-eval will replace this variable with the
;; simulation-no-value gensym in the runtime formulas rederived.  This is because
;; the variable is no longer being simulated and sim-eval should fail when
;; encountering it.

;; Note that update-runtime-structures-according-to-edit is called with the
;; do-not-reinstall?  arg t.  This is necessary because
;; update-runtime-structures-according-to-edit can call
;; update-generic-simulation-formula-for-variable-or-parameter which can call
;; add-variable-to-simulation and remove-variable-from-simulation resulting in
;; infinite recursion.



(defun add-to-variables-to-be-rederived (variable)
  (let ((simulation-info? (simulation-info? variable)))
    (when simulation-info?
      (with-current-model-for-variable 
	variable
	(add-to-rederive-set
	  (variables-whose-runtime-structures-must-be-rederived
	    current-model-runtime-info?)
	  variable)))))

(defun remove-from-variables-to-be-rederived (variable)
  (let ((simulation-info? (simulation-info? variable))
	runtime-structure?)
    (when simulation-info?
      (setq runtime-structure? (runtime-info? simulation-info?))
      (when (and runtime-structure?
		 (simulation-runtime-information? variable))
	(setf (variable-needs-simulated-value? 
		(simulation-runtime-information? variable)) nil)
	(setf (value-of-variable-tainted? 
		(simulation-runtime-information? variable)) nil))
      (delete-from-rederive-set variable)
      (delete-from-set 
	(variables-that-need-simulated-values current-model-runtime-info?)
	'simulate)
      (delete-from-set 
	(tainted-variables current-model-runtime-info?)
	'simulate))))





;;;; Grammar and Slot Value Compilers for Models

(add-grammar-rules
  '((item-designations-for-model item-designation-for-model 1)
    (item-designations-for-model
      (item-designation-for-model '\, item-designations-for-model) (2 1 3)
      simplify-associative-operation)
    (item-designation-for-model object-name)
    (item-designation-for-model workspace-designation-for-model)
    (item-designation-for-model 
      ('any class) (class . 2))
    (item-designation-for-model 
      ('any class 'upon workspace-designation-for-model) (class 2 4))
    (workspace-designation-for-model workspace-name)
    (workspace-designation-for-model 
      ('this 'workspace) (this-workspace))
    ))

(def-slot-value-compiler item-designations-for-model (parse-result)
  (if (and (consp parse-result)
	   (eq (car parse-result) '\,))
      (cdr parse-result)
      (phrase-list parse-result)))





;;;; Installation Methods for Models

;;; The frame status of the model-definition is incomplete if there are no
;;; designated items.

(def-kb-specific-variable models-used-p SIMULATE5 nil t)

;; This is bound globally to nil because install-item-in-model-if-models-used
;; can be called at load time (via delete-as-frame-with-name) when a format
;; frame is redefined.  - AGH, MHD, 1/17/91


(defun initialize-model-definition (model-definition)
  (initialize-model-runtime-info-if-necessary model-definition)
  (if (items-belonging-to-this-model model-definition)
      (update-frame-status model-definition nil nil)
      (update-frame-status model-definition 'incomplete nil))
  (forward-model-install
    model-definition
    (car (items-belonging-to-this-model model-definition))
    nil)
  (update-anything-to-simulate-in-model?
    (model-runtime-info? model-definition)))

(defun initialize-model-runtime-info-if-necessary (model-definition)
  (when (null (model-runtime-info? model-definition))
    (setf (model-runtime-info? model-definition)
	  (initialize-model-runtime-info model-definition))))


(def-class-method initialize (model-definition)
  (funcall-superior-method model-definition)
  (initialize-model-definition model-definition))

(def-class-method initialize-after-reading (model-definition)
  (funcall-superior-method model-definition)
  (initialize-model-definition model-definition))
  
  



(def-kb-specific-property-name model-definitions-for-item-or-class)

(def-slot-putter items-belonging-to-this-model 
    (model-definition items-belonging-to-this-model initializing?)
  (let ((old-slot-value
	  (items-belonging-to-this-model model-definition) ))
    (prog1 (setf (items-belonging-to-this-model model-definition) 
		 items-belonging-to-this-model)
      (unless initializing?
	(initialize-model-runtime-info-if-necessary model-definition) ; nec.? (MHD 8/2/94)
	(if (items-belonging-to-this-model model-definition)
	    (update-frame-status model-definition nil nil)
	    (update-frame-status model-definition 'incomplete nil))
	
	;; Forward installation.
	(forward-model-install
	  model-definition
	  (car items-belonging-to-this-model)
	  (car old-slot-value)))
      (update-models-used-p))))

;; The mechanism that uses update-models-used-p is very inefficiently designed!
;; (It's N^2 on the number of model definitions.)  It's probably not worth
;; bothering to fix now, especially since it won't be put to heavy use in
;; practice.  (MHD 8/2/94)



(defun forward-model-install (model-definition designations deinstall-designations)
  ;; Deinstall each deinstall designation that's not one of the (install)
  ;; designations:
  (loop for designation in deinstall-designations
	when (loop for designation2 in designations
		   never (model-item-designations-eq designation designation2))	
	  do (forward-model-install-1 model-definition designation t))
  ;; Install each designation that's not one of the deinstall-designations:
  (loop for designation in designations
	when (loop for designation2 in deinstall-designations
		   never (model-item-designations-eq designation designation2))
	  do (forward-model-install-1 model-definition designation nil)))

(defun forward-model-install-1 (model-definition designation deinstall-instead?)
  (cond
    ((consp designation)
     (cond
       ((eq (car designation) 'class)
	(let ((designated-class 
		(if (symbolp (cdr designation))
		    (cdr designation)
		    (second designation))))
	  (update-model-definitions-for-item-or-class 
	    model-definition designated-class deinstall-instead?)
	  (loop for designated-item being each class-instance of designated-class
		do
	    ;; Now propagate the model-definition.  If this is not done then
	    ;; install-item-in-model-if-appropriate will always install the item on
	    ;; the default model - which is wrong.
	    ;; This change made as a fix for the bug HQ-1004612.  - ajs 12/24/96

	    ;; If deinstall-instead? revert to the previous call which is calling
	    ;; install-item-in-model-if-appropriate with no model-definition.
	    ;; (ghw 1/15/97 for bug HQ-859653)
	    (if deinstall-instead?
		(install-item-in-model-if-appropriate designated-item nil t)
		(install-item-in-model-if-appropriate designated-item
						      model-definition t)))))
       ((eq (car designation) 'this-workspace)
	(let ((workspace? (superblock? model-definition)))
	  (when workspace?
	    (if deinstall-instead?
		(install-item-in-model-if-appropriate workspace? nil t)
		(install-item-in-model-if-appropriate workspace? model-definition t)))))))
    (t
     (update-model-definitions-for-item-or-class 
       model-definition designation deinstall-instead?)
     (let ((designated-item?
	     (get-instance-with-name-if-any 'item designation)))
       (when designated-item?
	 (if deinstall-instead?
	     (install-item-in-model-if-appropriate
	       designated-item? nil t)
	     (install-item-in-model-if-appropriate
	       designated-item? model-definition t)))))))

(defun update-model-definitions-for-item-or-class 
       (model-definition item-or-class deinstall-instead?)
  (if deinstall-instead?
      (delete-from-set 
	(model-definitions-for-item-or-class item-or-class) model-definition)
      (add-to-set 
	(model-definitions-for-item-or-class item-or-class) model-definition)))



;; OBSOLETE -- no longer needed. (MHD 8/2/94)
;; ;;; Get-missing-model-item-designations returns a gensym list of designations
;; ;;; which appear in the first argument but not in the second.
;;
;; (defun get-missing-model-item-designations
;;     (first-designation-list second-designation-list)
;;   (loop for designation1 in first-designation-list
;;         when (loop for designation2 in second-designation-list
;;                    never (model-item-designations-eq designation1 designation2))
;;           collect designation1 using gensym-cons))

(defun model-item-designations-eq (designation1 designation2)
  (if (and (consp designation1)
	   (eq (car designation1) 'class))
      (and (consp designation2)
	   (eq (car designation2) 'class)
	   (eq (cdr designation1) (cdr designation2)))
      (eq designation1 designation2)))



(defun update-models-used-p ()
  (if (loop for md being each class-instance of 'model-definition
	    thereis (items-belonging-to-this-model md))
      (setq models-used-p t)
      (setq models-used-p nil)))



(defun install-items-of-class-in-model (class)
  (loop for item being each class-instance of class
	do (install-item-in-model-if-models-used item)))



(defun install-item-in-model-if-models-used (item)
  (when (variable-or-parameter-p item)
    (let ((inhibit-model-install? t))
      (update-generic-simulation-formula-for-variable-or-parameter item)))
  (when models-used-p
    (install-item-in-model-if-appropriate item nil t)))

(defun install-superblock-in-model-if-appropriate (block superblock)
  (when (and models-used-p
	     (model-definition-p block)
	     (kb-workspace-p superblock))
    (install-item-in-model-if-appropriate superblock nil t)))

(defvar install-item-in-model-if-appropriate nil) 

(defun-simple install-item-in-model-if-appropriate 
       (item model-definition-for-superior-item? 
	check-superior-items?)
  (let* ((model-definition-for-item?
	   (get-model-to-which-item-belongs item check-superior-items?))
	 (model-definition-to-pass-on?
	   (or model-definition-for-item?
	       model-definition-for-superior-item?)))
    (when (variable-or-parameter-p item)
      (mark-variable-as-belonging-to-model 
	item model-definition-to-pass-on?))
    (when (entity-p item)
      (mark-entity-as-belonging-to-model-if-appropriate
	item model-definition-to-pass-on?)
      (loop for subworkspace in (subworkspaces item) doing
	(install-item-in-model-if-appropriate
	  subworkspace model-definition-to-pass-on? nil)))
    (when (kb-workspace-p item)
      (loop for subblock being each subblock of item
	    do (when (of-class-p subblock 'item)
		 (install-item-in-model-if-appropriate
		   subblock model-definition-to-pass-on? nil))))
    (funcall-simple-compiled-function-on-attributes
      item install-item-in-model-if-appropriate 
      (or model-definition-for-item?
	  model-definition-for-superior-item?)
      nil)))

(setq install-item-in-model-if-appropriate
      #'install-item-in-model-if-appropriate)

(defun mark-variable-as-belonging-to-model 
       (variable-or-parameter model-definition?)
  (let ((simulation-info? (simulation-info? variable-or-parameter)))
    (when simulation-info?
      (setf (model-definition? simulation-info?) model-definition?)
      (let ((current-model-runtime-info? 
	      (if model-definition? 
		  (model-runtime-info? model-definition?)
		  main-model-runtime-info)))
	;; Use add-variable-to-simulation  rather than add-variable-to-simulation-model.
	;; The latter does not call add-to-variables-to-be-rederived thus failing 
	;; to tie into the "Editing while Simulation is Running"
	;; mechanism which is described in SIMULATE1
	;; This change made as a fix for the bug HQ-1004612.  - ajs 12/24/96
	(add-variable-to-simulation variable-or-parameter)))))

;; Note that if model-definition?  is nil, the variable is marked as belonging to
;; the main model.  The variable is only marked if it is being simulated.



(defun mark-entity-as-belonging-to-model-if-appropriate
       (entity model-definition?)
  (when (get-slot-value-if-any entity 'external-simulation-definition-for-entity)
    ;; if simulated externally
    (let ((current-model-runtime-info? 
	    (if model-definition? 
		(model-runtime-info? model-definition?)
		main-model-runtime-info)))
      (add-externally-simulated-entity-to-simulation-model entity))))



(defun get-model-to-which-item-belongs (item check-superior-items?)
  (if check-superior-items?
      (loop for item-to-check? = item then (superior-frame item-to-check?)
	    until (null item-to-check?)
	    as model-definition? 
	       = (get-model-which-designates-item item-to-check?)
	    when model-definition?
	      do (return model-definition?))
      (get-model-which-designates-item item)))

(defun get-model-which-designates-item (item)
  (or 
    (let ((name-or-names (name-or-names-for-frame item)))
      (when name-or-names
	(if (consp name-or-names)
	    (loop for name in name-or-names
		  as model-definition? 
		     = (car (model-definitions-for-item-or-class name))
		  when model-definition?
		    do (return model-definition?))
	    (car (model-definitions-for-item-or-class name-or-names)))))
    (when (and (frame-of-class-p item 'kb-workspace)
	       (not (frame-being-deleted-p item)))
      (loop for block being each subblock of item do
	(when (frame-of-class-p block 'model-definition)
	  (loop for designation
		    in (car (items-belonging-to-this-model block))
		do 
	    (when (and (consp designation)
		       (eq (car designation) 'this-workspace))
	      (return-from
		get-model-which-designates-item block))))))
    (when (or (frame-of-class-p item 'object)
	      (frame-of-class-p item 'connection))
      (loop for class in (class-inheritance-path
			   (class-description-slot item))
	    until (eq class 'item)
	    as model-definition? 
	       = (get-appropriate-model-definition-for-class
		   item class (model-definitions-for-item-or-class class))
	    when model-definition?
	      do (return model-definition?)))))

(defun get-appropriate-model-definition-for-class 
       (item class model-definitions-for-class)
  (loop with model-definition-for-entire-class? = nil
	for item-to-check? = item then (superior-frame item-to-check?)
	until (null item-to-check?)
	do
    (loop with any-model-definitions-specifying-items? = nil
	  for model-definition in model-definitions-for-class do
      (loop for designation
		in (car (items-belonging-to-this-model model-definition))
	    do 
	(when (and (consp designation)
		   (eq (car designation) 'class))
	  (cond
	    ((symbolp (cdr designation))
	     (when (and (null model-definition-for-entire-class?)
			(eq (cdr designation) class))
	       (setq model-definition-for-entire-class? model-definition)))
	    (t
	     (setq any-model-definitions-specifying-items? t)
	     (when (and (eq (second designation) class)
			(item-matches-one-in-designation 
			  item-to-check? (third designation) model-definition))
	       (return-from
		 get-appropriate-model-definition-for-class
		 model-definition))))))
	  finally (when (null any-model-definitions-specifying-items?)
		    (return-from
		      get-appropriate-model-definition-for-class
		      model-definition-for-entire-class?)))
	finally (return model-definition-for-entire-class?)))

(defun item-matches-one-in-designation 
       (item model-item-designation model-definition)
  (cond
    ((symbolp model-item-designation)
     (let ((name-or-names (name-or-names-for-frame item)))
       (if (consp name-or-names)
	   (memq model-item-designation name-or-names)
	   (eq model-item-designation name-or-names))))
    ((and (consp model-item-designation)
	  (eq (car model-item-designation) 'this-workspace))
     (eq (superblock? model-definition) item))))


;; Removed -- no longer needed as this is done in the initialize-after-reading
;; method on each instance of model-definition. (MHD 8/2/94)
;; 
;; ;;; Install-models-after-loading-1 is called from the post loading function
;; ;;; install-models-after-loading.
;;
;; (defun install-models-after-loading-1 ()
;;   (loop for model-definition being each class-instance of 'model-definition
;; 	do (forward-model-install 
;; 	     model-definition 
;; 	     (car (items-belonging-to-this-model model-definition)) nil)))
;; 
;; ;; I'm almost sure this is redundant with what the initialize-after-reading
;; ;; method now does, and what the slot putter used to do.  Shouldn't this be
;; ;; eliminated?!  It seems slightly more conservative to leave it until we have
;; ;; time to check further into it.  (MHD 8/2/94)



(def-slot-putter simulation-procedure-for-model 
    (model-definition simulation-procedure-for-model initializing?)
  (prog1 (setf (simulation-procedure-for-model model-definition)
	       simulation-procedure-for-model)
    (unless initializing?
      (initialize-model-runtime-info-if-necessary model-definition) ; nec.? (MHD)
      (update-anything-to-simulate-in-model?
	(model-runtime-info? model-definition)))))

(def-slot-putter external-simulator-configuration-for-model 
    (model-definition external-simulator-configuration-for-model initializing?)
  (prog1 (setf (external-simulator-configuration-for-model model-definition)
	       external-simulator-configuration-for-model)
    (unless initializing?
      (initialize-model-runtime-info-if-necessary model-definition) ; nec.? (MHD)
      (update-anything-to-simulate-in-model?
	(model-runtime-info? model-definition)))))






;;; The `install-system-table method for simulation-parameters' calls
;;; update-anything-to-simulate-in-model?.  The slot putters for the
;;; simulation-procedure and external-simulator-configuration slots of
;;; simulation-parameters do so as well provided that they're called when not
;;; initializing and when their instance is the installed system table.

(def-class-method install-system-table (simulation-parameters)
  (warn-of-simulation-license-restrictions-if-necessary)

  (when (or (simulation-procedure simulation-parameters)
	    (external-simulator-configuration simulation-parameters))
    ;; Shouldn't need the when -- and it might be bad -- but it works
    ;; around a bug!  (MHD '91 and '93)
    (update-anything-to-simulate-in-model? main-model-runtime-info)))

(def-class-method deinstall-system-table (simulation-parameters))

(defun warn-of-simulation-license-restrictions-if-necessary ()
  (when (and (simulator-on? simulation-parameters)
	     (g1-authorized-p))
    (notify-user
      "Ignoring the request to turn on the simulator found in the simulation-parameters.  The current G2 license does not include this feature.")))

  
(def-slot-putter simulation-procedure 
    (simulation-parameters-instance simulation-procedure initializing?)
  (prog1 (setf (simulation-procedure simulation-parameters-instance)
	       simulation-procedure)
    (unless initializing?
      (when (system-table-installed-p simulation-parameters-instance)
	(update-anything-to-simulate-in-model? main-model-runtime-info)))))

(def-slot-putter simulator-on?
    (simulation-parameters-instance simulator-on? initializing?)
  (prog1 (setf (simulator-on? simulation-parameters-instance)
	       simulator-on?)
    (unless initializing?
      (warn-of-simulation-license-restrictions-if-necessary)
      (when (system-table-installed-p simulation-parameters-instance)
	(when simulator-on?
	  (schedule-data-server-accept-data-calls))
	(update-anything-to-simulate-in-model? main-model-runtime-info)))))

(def-slot-putter external-simulator-configuration
    (simulation-parameters-instance external-simulator-configuration initializing?)
  (prog1 (setf (external-simulator-configuration simulation-parameters-instance)
	       external-simulator-configuration)
    (unless initializing?
      (when (system-table-installed-p simulation-parameters-instance)
	(update-anything-to-simulate-in-model? main-model-runtime-info)))))



(def-substitution-macro external-simulation-configured? (external-configuration?)
  (and external-configuration?
       (not (eq (car external-configuration?) 'none))))

(defmacro anything-to-simulate-macro (model-runtime-info)
  `(or (not (installation-set-empty?
	      (model-dependent-variable-info ,model-runtime-info)))
       (not (installation-set-empty?
	      (model-discrete-state-variable-info ,model-runtime-info)))
       (not (installation-set-empty?
	      (model-continuous-state-variable-info ,model-runtime-info)))
       (if (eq ,model-runtime-info main-model-runtime-info)
	   (when (not releasing-kb?)
	     (or (simulation-procedure simulation-parameters)
		 (external-simulation-configured?
		   (external-simulator-configuration simulation-parameters))))
	   (let ((model-definition
		   (model-definition-for-model? ,model-runtime-info)))
	     (or (simulation-procedure-for-model model-definition)
		 (external-simulation-configured?
		   (external-simulator-configuration-for-model
		     model-definition)))))))

(defun update-anything-to-simulate-in-model? (model-runtime-info)
  (if (anything-to-simulate-macro model-runtime-info)
      (add-model-which-has-something-to-simulate model-runtime-info)
      (remove-model-which-has-nothing-to-simulate model-runtime-info)))

(defun anything-to-simulate? (model-runtime-info)
  (anything-to-simulate-macro model-runtime-info))

(defun add-model-which-has-something-to-simulate (model-runtime-info)
  (let ((model-definition? (model-definition-for-model? model-runtime-info)))
    (when  ; add model?
      (if (null model-definition?)   ; main model
	  (or system-is-running system-has-paused)
	  (cond  
	    ((model-running-or-paused? model-definition?)
	     t)
	    ((eq (model-simulation-status model-definition?) 'nothing-to-simulate)
	     (change-slot-value model-definition? 'model-simulation-status 'running)
	     t)))
      (cond
	((eq (model-runtime-status model-runtime-info) 'needs-to-be-shutdown)
	 (setf (model-runtime-status model-runtime-info) 'running))
	((and (and (simulator-on? simulation-parameters)
		   (not (g1-authorized-p)))
	      (null (model-runtime-status model-runtime-info)))
	 (setf (model-runtime-status model-runtime-info) 'needs-to-be-initialized)
	 (let ((current-model-queue?
		 (get-model-queue-for-model model-runtime-info)))
	   (add-model-to-simulation model-runtime-info)))))))

(defun remove-model-which-has-nothing-to-simulate (model-runtime-info)
  (if (eq (model-runtime-status model-runtime-info) 'needs-to-be-initialized)
      (let ((current-model-queue?
	      (get-model-queue-for-model model-runtime-info)))
	(remove-model-from-simulation model-runtime-info))
      (when (and (any-models-running?)
		 (model-runtime-status model-runtime-info))
	(setf (model-runtime-status model-runtime-info) 'needs-to-be-shutdown)))
  (let ((model-definition? (model-definition-for-model? model-runtime-info)))
    (when (and model-definition? (model-running-or-paused? model-definition?))
      (change-slot-value model-definition? 'model-simulation-status 'nothing-to-simulate))))






;;;; Simulation Histories and Models




;;; In version 4.0, variable simulation histories are now adjusted when the time
;;; of the associated simulation-model is changed.  This happens both when the
;;; model is started and when the time of the model is explicitly set.
;;; Currently, these can occur when the appropriate system-procedure is called.
;;; This adjustment of histories is necessary so that values from different runs
;;; of the model do not get mixed together in the history.  Also, if the time is
;;; newly set, the history should not contain any future values.




;;; The function `clear-simulation-history-of-model-variables' removes the
;;; simulation history values for the variables in the given simulation-model.
;;; This is needed to prevent values of different runs of the model to be mixed
;;; together in the history.

;;; Note that this function should only be called whent this is a runtime change
;;; to the histories.

(defun clear-simulation-history-of-model-variables (model-definition)
  (let ((model-runtime-info? (model-runtime-info? model-definition)))
    (for-each-element-in-installation-set
      (model-continuous-state-variable-info model-runtime-info?)
      'clear-simulation-history-at-runtime)
    (for-each-element-in-installation-set
      (model-discrete-state-variable-info model-runtime-info?)
      'clear-simulation-history-at-runtime)
    (for-each-element-in-installation-set
      (model-dependent-variable-info model-runtime-info?)
      'clear-simulation-history-at-runtime)))



;;; The function `adjust-simulation-history-of-model-variables-if-necessary' is
;;; used to adjust the values in the simulation histories based on the current
;;; simulation time.

;;; When the simulation time of the model changes, the histories is adjusted in
;;; one several ways.  If the new simulation time is older than the variables'
;;; first simulation history value, then the entire history is cleared.  If the
;;; time is newer than the most recent simulation history value, then there is
;;; no change.  If the new time is somewhere between the first and last history
;;; value, then the histories values newer than the new time are removed.

;;; IMPORTANT: This function should be called after any necessary are made to
;;; the simulation time that will affect the histories.  Also, it should be
;;; called only when this is a runtime change to the model-definition and the
;;; associated simulation histories.

(defun adjust-simulation-history-of-model-variables-if-necessary
    (model-definition)
  (let ((model-runtime-info? (model-runtime-info? model-definition))
        (time-used-to-adjust-histories?
	  ;; Bind this system-variable, which is referenced when the history is
	  ;; adjusted.
	  (transform-evaluation-float-into-managed-float
	    (get-model-simulation-time model-definition))))
    (when time-used-to-adjust-histories?
      (for-each-element-in-installation-set
	(model-continuous-state-variable-info model-runtime-info?)
	'adjust-simulation-history-at-runtime-if-necessary)
      (for-each-element-in-installation-set
	(model-discrete-state-variable-info model-runtime-info?)
	'adjust-simulation-history-at-runtime-if-necessary)
      (for-each-element-in-installation-set
	(model-dependent-variable-info model-runtime-info?)
	'adjust-simulation-history-at-runtime-if-necessary)
      (reclaim-managed-float time-used-to-adjust-histories?))))






;;;; System Procedures for Simulation




;;; Start-model, reset-model, pause-model, resume-model, and
;;; get-current-model-definition are the lisp functions called by the system
;;; procedures g2-start-model, g2-reset-model, g2-pause-model, g2-resume-model,
;;; and g2-get-current-model-definition.

;;; Note that as of version 4.0 Beta 2, simulation histories are cleared, if
;;; necessary, when the model is started (not when it is reset).  This is needed
;;; so that values from different runs of the model do not get mixed together in
;;; the history.  Also, note that simulation histories are "adjusted", if
;;; necessary, when set-model-simulation-time is called.  - cpm, 11/2/94 

(declare-system-procedure-function start-model t)

(defun-funcallable start-model (model-definition)
  (let ((model-runtime-info (model-runtime-info? model-definition)))
    (cond
      ((anything-to-simulate? model-runtime-info)
       (change-slot-value
	 model-definition 'model-simulation-status 'running)
       (initialize-simulator
	 model-runtime-info model-definition)
       (clear-simulation-history-of-model-variables model-definition)
       (when (simulator-on? simulation-parameters)
	 ;; Must be scheduled after initialize-simulator for this model.
	 (schedule-data-server-accept-data-calls)))
      (t
       (change-slot-value
	 model-definition 'model-simulation-status 'nothing-to-simulate)))))


(declare-system-procedure-function reset-model t)

(defun-funcallable reset-model (model-definition)
  (when (model-running-or-paused? model-definition)
    (shutdown-simulator
      (model-runtime-info? model-definition) model-definition))
  (change-slot-value
    model-definition 'model-simulation-status 'not-running))

(declare-system-procedure-function pause-model t)

(defun-funcallable pause-model (model-definition)
  (when (eq (model-simulation-status model-definition) 'running)
    (change-slot-value
      model-definition 'model-simulation-status 'paused)))

(declare-system-procedure-function resume-model t)

(defun-funcallable resume-model (model-definition)
  (when (eq (model-simulation-status model-definition) 'paused)
    (adjust-model-simulation-time-to-skip-paused-period model-definition)
    (change-slot-value
      model-definition 'model-simulation-status 'running)))



;;; The function `adjust-model-simulation-time-to-skip-paused-period' adjusts
;;; the model simulation time to skip over the paused period so that the model
;;; does not try to "catch up" to gensym time.  The only disadvantage of doing
;;; this is that it will cause a gap in histories (and graphs showing such
;;; histories).  Users can circumvent this by setting the simulation time of the
;;; model using the system procedure for this.

(defun adjust-model-simulation-time-to-skip-paused-period (model-definition)
  (let* ((model-runtime-info (model-runtime-info? model-definition))
	 (as-fast-as-possible-model?
	   (memq 'as-fast-as-possible
		 (simulation-control-specifications model-definition)))
	 (current-gensym-time (floore-first (time-since-base-time-as-gensym-float)))
	 (current-simulation-time
	   (macro-time (current-simulation-time model-runtime-info)))
	 (base-simulation-time
	   (macro-time (simulation-base-time model-runtime-info))))
    (cond (as-fast-as-possible-model?
	   (when (> current-gensym-time current-simulation-time)
	     (store-number-into-compound-fixnum-simulation-time
	       (current-simulation-time model-runtime-info)
	       (-f current-gensym-time base-simulation-time))))
	  (t
	   (store-number-into-compound-fixnum-simulation-time
	     (current-simulation-time model-runtime-info)
	       (-f current-gensym-time base-simulation-time))))))

(defun model-running-or-paused? (model-definition)
  (let ((status (model-simulation-status model-definition)))
    (or (eq status 'running) (eq status 'paused))))


(declare-system-procedure-function set-model-simulation-time t)

(defun-funcallable set-model-simulation-time (model-definition time)
  (let ((model-runtime-info (model-runtime-info? model-definition)))
    (add-compound-fixnum-simulation-times
      simulation-time-accumulator
      (current-simulation-time model-runtime-info)
      (simulation-base-time model-runtime-info))
    (with-temporary-gensym-float-creation set-model-simulation-time
      (store-number-into-compound-fixnum-simulation-time
	(current-simulation-time model-runtime-info)
	(evaluation-value-value time)))
    (reclaim-evaluation-value time)
    (subtract-compound-fixnum-simulation-times
      (simulation-base-time model-runtime-info)
      simulation-time-accumulator
      (current-simulation-time model-runtime-info))

    (loop for variable-group-update-structure 
	      in (model-variable-group-update-info model-runtime-info)
	  do
      (transfer-value-of-compound-fixnum-simulation-times
	(time-of-next-update-for-group variable-group-update-structure)
	(current-simulation-time model-runtime-info)))

    (setf (simulated-variable-removed? model-runtime-info) t)

    ;; Remove any values that are now aged or in the future, given the new time.
    (adjust-simulation-history-of-model-variables-if-necessary
      model-definition)))

;; Time can be a float here.

;; Note that simulation-base-time is adjusted as well as current-simulation-time
;; so that their sum stays the same.  This is to maintain the synchronicity of
;; the model in the model queues (simulate-model-until-consistent-internal
;; compares the sum with simulation-time-for-models-in-queue.  The
;; simulated-variable-removed?  slot is set here in order to cause a rollback
;; (see check-for-simulation-changes).

;; Note that time-of-next-update-for-group of each
;; variable-group-update-structure is adjusted so that all variables are updated
;; on the next cycle after the rollback.


(declare-system-procedure-function get-model-simulation-time t)

(defun-funcallable get-model-simulation-time (model-definition)
  (with-temporary-gensym-float-creation get-model-simulation-time
    (let* ((model-runtime-info (model-runtime-info? model-definition))
	   (time-as-quantity
	     (extract-number-from-compound-fixnum-simulation-time
	       (current-simulation-time model-runtime-info))))
      (copy-managed-float-into-evaluation-float
	time-as-quantity))))

;; Fixed get-model-simulation-time to copy the time-as-quantity managed-float.
;; The function extract-number-from-compound-fixnum-simulation-time returns a
;; managed float that is held by the system-variable simulation-time-managed-
;; float and so should be copied.  - cpm, 11/3/92


(declare-system-procedure-function set-model-simulation-time-increment t)


(defun-funcallable set-model-simulation-time-increment
		   (model-definition time-increment)
  (let* ((model-runtime-info (model-runtime-info? model-definition))
	 (variable-group-update-structure?
	   (get-non-override-variable-group-update-structure
	     model-runtime-info)))
    (with-current-model-and-queue
      model-runtime-info model-definition
      (when variable-group-update-structure?
	(with-temporary-gensym-float-creation set-model-simulation-time-increment
	  (store-number-into-compound-fixnum-simulation-time

	    (compound-fixnum-time-increment-for-group
	      variable-group-update-structure?)
	    (evaluation-value-value time-increment)))
	(reclaim-evaluation-value time-increment)
	(cond 
	  ((<f (macro-time (shortest-override-time-increment
			     model-runtime-info))
	       0)
	   (transfer-value-of-compound-fixnum-simulation-times
	     (shortest-simulation-time-increment model-runtime-info)
	     (compound-fixnum-time-increment-for-group
	       variable-group-update-structure?)))
	  (t
	   (transfer-value-of-compound-fixnum-simulation-times
	     (shortest-simulation-time-increment model-runtime-info)
	     (min-compound-fixnum-simulation-time
	       (shortest-override-time-increment model-runtime-info)
	       (compound-fixnum-time-increment-for-group
		 variable-group-update-structure?))))))
      (update-shortest-simulation-time-increment-for-all-models)
      (setf (simulated-variable-removed? model-runtime-info) t))))

;; The simulated-variable-removed?  slot is set here in order to cause a rollback
;; (see check-for-simulation-changes).



(declare-system-procedure-function get-model-simulation-time-increment t)

(defun-funcallable get-model-simulation-time-increment (model-definition)
  (with-temporary-gensym-float-creation get-model-simulation-time
    (let* ((model-runtime-info (model-runtime-info? model-definition))
	   (variable-group-update-structure?
	     (get-non-override-variable-group-update-structure
	       model-runtime-info)))
      (cond
	(variable-group-update-structure?
	 (copy-managed-float-into-evaluation-float
	   (extract-number-from-compound-fixnum-simulation-time
	     (compound-fixnum-time-increment-for-group
	       variable-group-update-structure?))))
	(t
	 (stack-error
	   cached-top-of-stack
	   "The model ~NF has no variables whose time increments are the one ~
            specified in the model definition."
	   model-definition))))))

;; Fixed get-model-simulation-time-increment to copy the returned managed-float.
;; The function extract-number-from-compound-fixnum-simulation-time returns a
;; managed float that is held by the system-variable simulation-time-managed-
;; float and so should be copied.  - cpm, 11/3/92



(declare-system-procedure-function get-current-model-definition t)

(defun-funcallable get-current-model-definition ()
  (cond ((framep evaluating-simulator-procedure?)
	 evaluating-simulator-procedure?)
	(t
	 (stack-error
	   cached-top-of-stack
	   "There is no current simulator model"))))





;;;; Debugging Functions

#+development
(defun print-rederive-set (&optional rederive-set)
  (let ((rederive-set 
	  (or rederive-set
	      (variables-whose-runtime-structures-must-be-rederived 
		current-model-runtime-info?))))
    (for-each-element-in-rederive-set
      rederive-set
      'print-installation-set-variable)))

#+development
(defun print-external-sim (model-definition)
  (print-external-set
    (externally-simulated-entities
      (model-runtime-info? model-definition))))

#+development
(defun print-external-set (external-set)
  (for-each-element-in-external-set
    external-set
    'print-installation-set-variable))

#+development
(defun print-installation-set (installation-set)
  (for-each-element-in-installation-set
    installation-set
    'print-installation-set-variable))

#+development
(defun print-installation-set-variable (variable)
  (format t "~%~s" variable)
  (multiple-value-bind (frame? slot-name? class-qualifier?)
      (get-kb-parent-information variable)
    (when frame?
      (let ((temporary-text-string
	      (tformat-text-string
		" the ~NQ of ~a"
		slot-name? class-qualifier?
		frame?)))
	(format t "~a" temporary-text-string)
	(reclaim-text-string temporary-text-string)))))

#+development
(defun print-dependent-variables (&optional model-definition?)
  (let ((current-model-runtime-info?
	  (if model-definition?
	      (model-runtime-info? model-definition?)
	      main-model-runtime-info)))
    (print-dependent-variables-with-sort-boundary)))

#+development
(defun print-discrete-state-variables (&optional model-definition?)
  (let ((current-model-runtime-info?
	  (if model-definition?
	      (model-runtime-info? model-definition?)
	      main-model-runtime-info)))
    (print-installation-set
      (model-discrete-state-variable-info current-model-runtime-info?))))

#+development
(defun print-continuous-state-variables (&optional model-definition?)
  (let ((current-model-runtime-info?
	  (if model-definition?
	      (model-runtime-info? model-definition?)
	      main-model-runtime-info)))
    (print-installation-set
      (model-continuous-state-variable-info current-model-runtime-info?))))

#+development
(defun print-dependent-variables-with-sort-boundary ()
  (let ((first-element? 
	  (installation-set-next? 
	    (model-dependent-variable-info current-model-runtime-info?))))
    (when first-element?
      (loop as simulation-info? 
	       = first-element?
	       then (installation-set-next? simulation-info?)
	    until (null simulation-info?)
	    as variable-or-parameter
	       = (variable-for-simulation-info simulation-info?)
	    for count from 1
	    do
	(when 
	  (eq (model-sort-boundary-for-dependent-variable-info current-model-runtime-info?)
	      simulation-info?)
	  (format t "~%Sort Boundary"))
	(print-installation-set-variable variable-or-parameter)
	    finally 
	      (format t "~%Count = ~d" count)))))





;;;; Matrix Operations

;;; The following routines perform matrix addition, subtraction, transpose,
;;; copy, equal test, multiplication, and LU decomposition.  G2 system
;;; procedures call these functions.

;;; g2-lu-decompose
;;; g2-lubksb
;;; g2-lu-solve
;;; g2-array-add
;;; g2-array-subtract
;;; g2-array-equal
;;; g2-array-copy
;;; g2-transpose
;;; g2-array-multiply
;;; g2-matrix-multiply
;;; g2-scalar-multiply

;;; Note that these call optimized routines based on the types of the arrays
;;; (quantity, integer, float).  Note also that for integer arrays, there is
;;; no protection on fixnum overflow.  This is consistent with the integer
;;; data type in G2 evaluation.



;;; General guidelines include the following.  

;;; 1.  Many of these system procedures can take arrays or matrices as
;;; arguments.  If they are arrays (one dimension) they should be
;;; quantity-arrays.  If they are matrices, they should be item-arrays, the rows
;;; of which are quantity-arrays.  Thus, g2-array-add, g2-array-subtract,
;;; g2-array-equal, and g2-array-copy can all take either all arrays, or all
;;; matrices as arguments.  These procedures do not allow some args to be arrays
;;; and others to be matrices since this wouldn't make any sense for these
;;; operations.  G2-transpose takes matrices, but not arrays, as arguments.
;;; G2-array-multiply takes only arrays and returns a result of type quantity.
;;; G2-matrix-multiply takes either a matrix and two arrays, or three matrices,
;;; the first two args being the inputs to the multiply operation, the third
;;; being the output.  The lu decomposition procedures take very specific arg
;;; data types as described below.

;;; 2.  All of these system procedures take arguments such that the output
;;; result does not necessarily have to overwrite the input arguments.  Thus,
;;; g2-array-add and g2-array-subtract take 3 arguments, the first two being the
;;; input arrays or matrices to the add or subtract operation, the third being
;;; the result array or matrix.  However, the third argument can be the same
;;; matrix as one of the first two.  In fact, all three can be the same.
;;; G2-array-equal never modifies its arguments; it simply returns true or
;;; false.  G2-array-copy copies its first argument into its second.
;;; G2-transpose takes the matrix transpose of the first argument and puts the
;;; result into the second.  Since the result of transposing an m X n matrix
;;; (where m /= n) is an n X m matrix, the second argument obviously can not be
;;; the same as the first for non-square cases.  For square cases, the second
;;; argument can be the same as the first, resulting in an in-place
;;; modification.  G2-array-multiply never modifies its arguments; it simply
;;; returns a quantity.  G2-matrix-multiply multiplies its first two arguments
;;; and puts the result into the third.  For the case of a matrix being
;;; multiplied by a vector (1st arg is a matrix, 2nd a vector), the third
;;; argument can be the same as the second, in which case, the multiplying
;;; vector's values are replaced with those of the result.  The same is true for
;;; the case of a matrix being multiplied by a matrix, even in non-square cases;
;;; the third argument can be the same as the second.  For g2-lu-decompose, the
;;; lu matrix argument holds the result of the decomposition.  The lu argument
;;; may be the same as the a matrix argument, in which case, the original a
;;; matrix is destroyed.  For g2-lubksb, the x vector argument may be the same
;;; as the b vector argument, in which case, the original b vector is destroyed.
;;; For g2-lu-solve, the rules for the lu matrix argument and the x vector
;;; argument are the same as for g2-lu-decompose and g2-lubksb, since
;;; g2-lu-solve simply calls these functions.

;;; 3.  Just as many of these system procedures can take arrays as well as
;;; matrices as arguments, they can also take non-square matrices.  Thus,
;;; g2-array-add, g2-array-subtract, g2-array-equal, g2-array-copy,
;;; g2-array-transpose, and g2-matrix-multiply can all take non-square matrices.
;;; The lu decomposition procedures require square matrices for the a and lu
;;; matrix arguments.





;;; The LU decomposition routine uses Crout's method with partial pivoting as
;;; described in section 2.3 of "Numerical Recipes" by Press, et.  al.  This
;;; routine is for dense, rather than sparse matrices; sparse matrix routines
;;; are far more complicated.  Nevertheless, there are many applications where
;;; this is useful, and some sparse matrix routines (frontal methods) use dense
;;; routines.

;;; For the most part, names of variables have been kept the same as in the
;;; routines in "Numerical Recipes", even though this is somewhat of a departure
;;; from the G2 style of using long descriptive names.

;;; LUDCMP (LU decomposition) takes a matrix A represented by G2-arrays.  The
;;; required data structure is a G2 item array, with each element containing a G2
;;; float array.  A runtime error is signaled if this is not the case.  N is the
;;; number of rows and columns in A.  INDX must be a G2 integer array and is
;;; filled to record the row permutation effected by partial pivoting.  LUDCMP
;;; returns t if the number of row interchanges was even, else nil.  LUDCMP is
;;; used in combination with LUBKSB (LU backward substitution) to solve linear
;;; equations.

;;; LUBKSB solves the set of N linear equations AX = B.  The arg A is not the
;;; original matrix, but rather, its LU decomposition, determined by LUDCMP.
;;; INDX is the permutation vector modified by LUDCMP.  B is the right-hand side
;;; vector and is modified to return the solution vector X.  B must be a managed
;;; float array.  A and INDX are not modified by this routine so they can be
;;; used for successive calls with different right-hand sides B.  LUBKSB takes
;;; into account the possibility that B will begin with many zero elements.



(defvar current-a-matrix)
(defvar current-lu-matrix)
(defvar current-index-array)
(defvar current-b-vector)
(defvar current-x-vector)



(def-substitution-macro matrix-element (a i j)
  (managed-float-aref (managed-g2-array (managed-svref a i)) j))

(def-substitution-macro set-matrix-element (a i j value)
  (let ((managed-float-array (managed-g2-array (managed-svref a i))))
    (mutate-managed-float-array managed-float-array j value)))

(def-substitution-macro swap-rows (a i j)
  (psetf (managed-svref a j) (managed-svref a i)
	 (managed-svref a i) (managed-svref a j)
	 (managed-svref a (+f j 1)) (managed-svref a (+f i 1))
	 (managed-svref a (+f i 1)) (managed-svref a (+f j 1))))



;;; G2-initialize-lu-decompose, g2-lu-compute-scaling, and g2-lu-crout
;;; are called by the system procedure g2-lu-decompose.

(declare-system-procedure-function g2-initialize-lu-decompose t)

(defun-funcallable g2-initialize-lu-decompose (a indx lu)
  (let ((current-a-matrix a)
	(current-index-array indx)
	(current-lu-matrix lu))
    (check-ludcmp-datatypes 
      (managed-g2-array a)
      (g2-array-length a) 
      (managed-g2-array indx)
      (managed-g2-array lu))))

(declare-system-procedure-function g2-lu-compute-scaling t)

(defun-funcallable g2-lu-compute-scaling (a a-row lu-row vv i)
  ;; One iteration of loop over rows to get the implicit scaling
  ;; information and copy a to lu if necessary.
  (with-temporary-gensym-float-creation g2-lu-compute-scaling
    (let ((current-a-matrix a))
      (g2-lu-compute-scaling-1 a-row lu-row vv i))))

(defun g2-lu-compute-scaling-1 (a-row lu-row vv i)
  ;; No special var bindings.
  (let* ((n (g2-array-length a-row))
	 (need-to-copy? (neq a-row lu-row))
	 (aamax-box (allocate-managed-float-box))
	 (element-value-box (allocate-managed-float-box))
	 (abs-value-box (allocate-managed-float-box))
	 (row-for-a (managed-g2-array a-row))
	 (row-for-lu (managed-g2-array lu-row)))
    (setq vv (managed-g2-array vv))
    (mutate-managed-float-value aamax-box 0.0d0)
    (loop for j from 0 below n
	  do
      (mutate-managed-float-value 
	element-value-box (managed-float-aref row-for-a j))
      (mutate-managed-float-value 
	abs-value-box (abse (managed-float-value element-value-box)))
      (when (>e (managed-float-value abs-value-box)
		(managed-float-value aamax-box))
	(mutate-managed-float-value aamax-box (managed-float-value abs-value-box)))
      (when need-to-copy?
	(mutate-managed-float-array 
	  row-for-lu j (managed-float-value element-value-box)))
	  finally
	    (if (=e (managed-float-value aamax-box) 0.0)
		(stack-error
		  cached-top-of-stack
		  "The MATRIX ~NF is singular and therefore cannot be lu decomposed.~
                       The singularity is due to the fact that row ~a contains all zeroes."
		  current-a-matrix i)
		(mutate-managed-float-array 
		  vv i
		  (/e 1.0 (managed-float-value aamax-box)))))
    (reclaim-managed-float aamax-box)
    (reclaim-managed-float element-value-box)
    (reclaim-managed-float abs-value-box)))

(declare-system-procedure-function g2-lu-crout t)

(defun-funcallable g2-lu-crout (a lu vv indx j)
  ;; This is one iteration of the loop over columns of Crout's method.
  (with-temporary-gensym-float-creation g2-lu-crout
    (let ((current-a-matrix a))
      (g2-lu-crout-1 lu vv indx j))))

(defun g2-lu-crout-1 (lu vv indx j)
  ;; No special var bindings.
  (let* ((aamax-box (allocate-managed-float-box))
	 (sum-box (allocate-managed-float-box))
	 (dum (allocate-managed-float-box))
	 imax
	 (n (g2-array-length lu))
	 (two-n (*f 2 n))
	 (two-j (*f 2 j)))
    
    (setq lu (managed-g2-array lu)
	  indx (managed-g2-array indx)
	  vv (managed-g2-array vv))
    
    ;; This is equation 2.3.12 except for i = j.
    (loop for i from 0 below two-j by 2
	  for i1 from 0
	  as row = (managed-g2-array (managed-svref lu i))
	  do
      (mutate-managed-float-value sum-box (managed-float-aref row j))
      (loop for k from 0 below i by 2
	    for k1 from 0 
	    as managed-float-array 
	       = (managed-g2-array (managed-svref lu k))
	    do
	(mutate-managed-float-value
	  sum-box (-e (managed-float-value sum-box)
		      (*e (managed-float-aref row k1)
;			      (matrix-element lu k j)  ; float optimizations don't work with macros
			  (managed-float-aref managed-float-array j)
			  )))
	    finally (mutate-managed-float-array 
		      row j (managed-float-value sum-box))))
    
    ;; This is i = j of equation 2.3.12 and i = j + 1 ... N of equation 2.3.13
    (mutate-managed-float-value aamax-box 0.0d0)       ; Initialize for the search for largest pivot element.
    (loop for i from two-j below two-n by 2 
	  for i1 from j
	  as row = (managed-g2-array (managed-svref lu i))
	  do
      (mutate-managed-float-value sum-box (managed-float-aref row j))
      (loop for k from 0 below two-j by 2
	    for k1 from 0 
	    as managed-float-array 
	       = (managed-g2-array (managed-svref lu k))
	    do
	(mutate-managed-float-value
	  sum-box (-e (managed-float-value sum-box)
		      (*e (managed-float-aref row k1)
;			      (matrix-element lu k j)   ; float optimizations don't work with macros
			  (managed-float-aref managed-float-array j)
			  )))
	    finally 
	      (setq imax (g2-lu-crout-2 row j sum-box dum vv i1 aamax-box imax))))
    
    ;; Pivot if appropriate.
    (when (/=f j imax)
      (swap-rows lu two-j (*f imax 2))
      (mutate-managed-float-array 
	vv imax (managed-float-aref vv j)))
    (setf (managed-svref indx j) imax)
    (when (=e 
;		(matrix-element lu two-j j)   ; float optimizations don't work with macros
	    (managed-float-aref (managed-g2-array (managed-svref lu two-j)) j)
	    0.0)
;	  (set-matrix-element lu two-j j tiny))
      (stack-error
	cached-top-of-stack
	"Singularity encountered in row ~a while lu decomposing the MATRIX ~NF."
	j current-a-matrix))
    
    (when (/=f j (-f n 1))
      (let ((managed-float-array (managed-g2-array (managed-svref lu two-j))))
	(mutate-managed-float-value
	  dum (/e 1.0 
;		    (matrix-element lu two-j j)  ; float optimizations don't work with macros
		  (managed-float-aref managed-float-array j)
		  )))
      (loop for i from (+f two-j 2) below two-n by 2
	    as row = (managed-g2-array (managed-svref lu i))
	    do
	(mutate-managed-float-array 
	  row j (*e (managed-float-aref row j) (managed-float-value dum)))))
    (reclaim-managed-float aamax-box)
    (reclaim-managed-float sum-box)
    (reclaim-managed-float dum)))

(defun g2-lu-crout-2 (row j sum-box dum vv i1 aamax-box imax)
  (mutate-managed-float-array row j (managed-float-value sum-box))
  (mutate-managed-float-value 
    dum (*e (managed-float-aref vv i1) (abse (managed-float-value sum-box))))
  (when (>=e (managed-float-value dum) (managed-float-value aamax-box))
    (setf imax i1)
    (mutate-managed-float-value
      aamax-box (managed-float-value dum)))
  imax)



;;; G2-initialize-lubksb, g2-lu-forward-substitute-row, and
;;; g2-lu-backward-substitute-row are called by the system procedure
;;; g2-lu-back-substitute.

(declare-system-procedure-function g2-initialize-lubksb t)

(defun-funcallable g2-initialize-lubksb 
		   (lu-matrix index b-vector x-vector)
  (with-temporary-gensym-float-creation g2-initialize-lubksb
    (let ((current-lu-matrix lu-matrix)
	  (current-index-array index)
	  (current-b-vector b-vector)
	  (current-x-vector x-vector))
      (g2-initialize-lubksb-1 lu-matrix index b-vector x-vector))))

(defun g2-initialize-lubksb-1 (lu-matrix index b-vector x-vector)
  ;; No special var bindings.
  (let ((n (g2-array-length lu-matrix))
	(b-managed-array (managed-g2-array b-vector))
	(x-managed-array (managed-g2-array x-vector)))
    (check-lubksb-datatypes 
      (managed-g2-array lu-matrix) n (managed-g2-array index)
      b-managed-array x-managed-array t)
    
    ;; Copy vector if necessary
    (when (neq b-vector x-vector)
      (loop for i from 0 below n do
	(mutate-managed-float-array 
	  x-managed-array i (managed-float-aref b-managed-array i))))))

(declare-system-procedure-function g2-lu-forward-substitute-row t)

(defun-funcallable g2-lu-forward-substitute-row
		   (lu-matrix-row index x i ii)
  ;; Forward substitution, taking into account permutations
  ;; ii is an optimization - when not -1, there is work to be done
  (with-temporary-gensym-float-creation g2-lu-forward-substitute-row
    (g2-lu-forward-substitute-row-1 lu-matrix-row index x i ii)))

(defun g2-lu-forward-substitute-row-1 (lu-matrix-row index x i ii)
  ;; No special var bindings.
  (setq index (managed-g2-array index)
	x (managed-g2-array x)
	ii (evaluation-integer-value ii))
  (let ((ll (managed-svref index i))
	(row (managed-g2-array lu-matrix-row))
	(sum-box (allocate-managed-float-box)))
    (mutate-managed-float-value sum-box (managed-float-aref x ll))
    (mutate-managed-float-array x ll (managed-float-aref x i))
    (if (/=f ii -1)
	(loop for j from ii below i
	      do 
	  (mutate-managed-float-value
	    sum-box (-e (managed-float-value sum-box)
			(*e (managed-float-aref row j)
			    (managed-float-aref x j)))))
	(when (/=e (managed-float-value sum-box) 0.0)
	  ;; A nonzero element was encountered, so from now on,
	  ;; it will be necessary to accumulate sums in the
	  ;; loop above.
	  (setq ii i)))
    (mutate-managed-float-array x i (managed-float-value sum-box))
    (reclaim-managed-float sum-box)
    (make-evaluation-integer ii)))

(declare-system-procedure-function g2-lu-backward-substitute-row t)

(defun-funcallable g2-lu-backward-substitute-row (lu-matrix-row x i)
  ;; Backward substitution
  (with-temporary-gensym-float-creation g2-lu-backward-substitute-row
    (g2-lu-backward-substitute-row-1 lu-matrix-row x i)))

(defun g2-lu-backward-substitute-row-1 (lu-matrix-row x i)
  ;; No special var bindings.
  (setq x (managed-g2-array x))
  (let ((row (managed-g2-array lu-matrix-row))
	(sum-box (allocate-managed-float-box))
	(n (g2-array-length lu-matrix-row)))
    (mutate-managed-float-value sum-box (managed-float-aref x i))
    (when (<f i (-f n 1))			
      (loop for j from (+f i 1) below n do
	(mutate-managed-float-value
	  sum-box (-e (managed-float-value sum-box)
		      (*e (managed-float-aref row j)
			  (managed-float-aref x j))))))
    (mutate-managed-float-array x i (/e (managed-float-value sum-box)
					(managed-float-aref row i)))
    (reclaim-managed-float sum-box)))



(defun check-float-matrix-1 (a n)
  (loop for i from 0 below (*f 2 n) by 2
	as row-vector = (managed-svref a i)
	as row-vector-internal = (when row-vector (managed-g2-array row-vector))
	as frame-serial-number = (when row-vector (managed-svref a (+f i 1)))
	do
    (when (or (not row-vector)
	      (not (frame-serial-number-equal (frame-serial-number row-vector) frame-serial-number))
	      (not (active-p row-vector))
	      (not (managed-float-array-p row-vector-internal))
	      (not (>=f (managed-float-array-length row-vector-internal) n)))
      (stack-error
	cached-top-of-stack
	"A row of the MATRIX ~NF was not an active float array with length >= ~a, ~
         the required minimum length for the matrix operation being attempted."
	current-a-matrix
	n))
	finally (return n)))

(defun check-ludcmp-datatypes (a n indx &optional lu)
  (when (not (>=f (managed-array-length indx) n))
    (stack-error
      cached-top-of-stack
      "The index array ~NF is not >= ~a, ~
       the required minimum length for the matrix operation being attempted."
      current-index-array
      n))
  (check-float-matrix-1 a n)
  (when lu
    (let ((current-a-matrix current-lu-matrix))
      (check-float-matrix-1 lu n))))



(defun check-lubksb-datatypes (lu n indx b x check-lu?)
  (when check-lu?
    (check-ludcmp-datatypes lu n indx))
  (cond
    ((not (>=f (managed-float-array-length b) n))
     (stack-error
       cached-top-of-stack
       "The b vector ~NF is not >= ~a, ~
        the required minimum length for the matrix operation being attempted."
       current-b-vector
       n))
    ((not (>=f (managed-float-array-length x) n))
     (stack-error
       cached-top-of-stack
       "The x vector ~NF is not >= ~a, ~
        the required minimum length for the matrix operation being attempted."
       current-x-vector
       n))))



(defun check-array-lengths-compatible (array1 array2 &optional array3)
  (let ((n (g2-array-length array1)))
    (when (not (=f n (g2-array-length array2)))
      (stack-error
	cached-top-of-stack
	"The array ~NF is not the same length as the array ~NF."
	array2 
	array1))
    (when (and array3 (not (=f n (g2-array-length array3))))
      (stack-error
	cached-top-of-stack
	"The array ~NF is not the same length as the array ~NF."
	array3 
	array1))
    n))

(defun check-index-within-bounds (index max-index)
  (when (or (<f index 0)
	    (>f index max-index))
    (stack-error
      cached-top-of-stack
      "The specified index ~d is outside the range 0 to ~d."
      index max-index)))

(defun check-array-length-compatible (array1 n)
  (when (not (=f n (g2-array-length array1)))
    (stack-error
      cached-top-of-stack
      "The array ~NF does not have the required length ~d"
      array1 n)
    n))

(defun check-range-array (range-array)
  (when (not (=f 4 (g2-array-length range-array)))
    (stack-error
      cached-top-of-stack
      "The range array ~NF does not have the required length 4."
      range-array))
  (managed-g2-array range-array))



(defun check-matrix-row-type (matrix array)
  (cond
    ((null array)
     (write-stack-error cached-top-of-stack
       (tformat "The matrix ~NF contains an empty row." matrix)))
    ((not (framep array))
     (write-stack-error cached-top-of-stack
       (tformat "The matrix ~NF contains a row which is not an item." matrix)))
    ((frame-of-class-p array 'integer-array) 'integer)
    ((frame-of-class-p array 'float-array) 'float)
    ((frame-of-class-p array 'quantity-array) 'quantity)
    (t 
     (write-stack-error cached-top-of-stack
       (tformat "The array ~NF is not a subclass of quantity-array and is therefore ~
       not suitable as a row of the MATRIX ~NF."
		array matrix)))))

(defun check-row-length-and-type-compatible (matrix array length type)
  (let ((row-type (check-matrix-row-type matrix array)))
    (when (not (eq type row-type))
      (stack-error
	cached-top-of-stack
	"The array ~NF is not of type ~a and is therefore ~
         not compatible with other rows of the MATRIX ~NF."
	array
	row-type
	matrix)))
  (let ((row-length (g2-array-length array)))
    (when (not (=f row-length length))
      (stack-error
	cached-top-of-stack
	"The length of array ~NF is ~a which is different ~
         from other rows of the MATRIX ~NF."
	array
	row-length
	matrix))))



#+development
(defun print-test-matrix (a)
  (let ((n (g2-array-length a)))
    (terpri) (terpri)
    (setq a (managed-g2-array a))
    (loop for i from 0 below (*f 2 n) by 2
	  as row-vector = (managed-g2-array (managed-svref a i)) do
      (loop for j from 0 below n do
	(format t "~S " (managed-float-aref row-vector j)))
      (terpri))))

;; This could be improved to nicely line up columns when elements have different
;; lengths.



#+development
(defun print-test-array (x)
  (terpri)
  (setq x (managed-g2-array x))
  (let ((n (managed-float-array-length x)))
    (loop for j from 0 below n do
      (format t "~S " (managed-float-aref x j)))))





;;; G2-initialize-matrix-add and g2-vector-add are called by the system
;;; procedures g2-array-add and g2-array-subtract.

(declare-system-procedure-function g2-initialize-matrix-add t)

(defun-funcallable g2-initialize-matrix-add (matrix1 matrix2 matrix3)
  (make-evaluation-integer
    (check-array-lengths-compatible matrix1 matrix2 matrix3)))

(def-system-variable subtract-arrays-instead? SIMULATE5 nil)

(declare-system-procedure-function g2-vector-add t)

(defun-funcallable g2-vector-add (vector1 vector2 vector3 add-or-subtract)
  (unless (and (> (g2-array-length vector1) 0)
	       (> (g2-array-length vector2) 0)
	       (> (g2-array-length vector3) 0))
    (stack-error
      cached-top-of-stack
      "All arrays must be of non-zero length"))
  (barrier)
  (let ((subtract-arrays-instead?
	  (/=f (evaluation-integer-value add-or-subtract) 0)))
    (multiple-value-prog1
	(with-temporary-gensym-float-creation g2-vector-add
	  (cond ((and (frame-of-class-p vector1 'integer-array)
		      (frame-of-class-p vector2 'integer-array)
		      (frame-of-class-p vector3 'integer-array))
		 (g2-integer-vector-add vector1 vector2 vector3))
		((and (frame-of-class-p vector1 'float-array)
		      (frame-of-class-p vector2 'float-array)
		      (frame-of-class-p vector3 'float-array))
		 (g2-float-vector-add vector1 vector2 vector3))
		((and (frame-of-class-p vector1 'quantity-array)
		      (frame-of-class-p vector2 'quantity-array)
		      (frame-of-class-p vector3 'quantity-array))
		 (g2-quantity-vector-add vector1 vector2 vector3))
		(t
		 (signal-invalid-vectors 
		   (gensym-list vector1 vector2 vector3) "a row add"))))
      (barrier))))

(defmacro with-three-g2-vectors
	  ((vector1 vector2 vector3) &body body)
  `(let ((managed-array-1 (managed-g2-array ,vector1))
	 (managed-array-2 (managed-g2-array ,vector2))
	 (managed-array-3 (managed-g2-array ,vector3)))
     ,@body))

(defmacro add-or-subtract-float-vector-elements (subtract?)
  (let ((j (gensym)))
    `(loop for ,j from 0 below n do
       (mutate-managed-float-array
	 managed-array-3 ,j
	 (,(if subtract? `-e `+e)
	  (managed-float-aref managed-array-1 ,j)
	  (managed-float-aref managed-array-2 ,j))))))

(defmacro add-or-subtract-integer-vector-elements (subtract?)
  (let ((j (gensym)))
    `(loop for ,j from 0 below n do
       (setf (managed-svref managed-array-3 ,j)
	     (,(if subtract? `-f `+f)
	      (managed-svref managed-array-1 ,j)
	      (managed-svref managed-array-2 ,j))))))

(defparameter max-number-of-array-elements-to-do 500)

(defmacro do-for-array-elements ((j n) &body body)
  `(let* ((n-minus-1 (-f ,n 1))
	  (end-value-of-j (minf n-minus-1
				(+f ,j
				    max-number-of-array-elements-to-do))))
     (when (>f ,j n-minus-1) (return nil))
     (with-temporary-gensym-float-creation do-for-array-elements
       (loop do
	 ,@body
	 (when (>=f ,j n-minus-1) (return nil))
	 (when (=f ,j end-value-of-j) (return end-value-of-j))
	 (setq ,j
	       (+f ,j 1))))))

(defmacro add-or-subtract-quantity-vector-elements (subtract?)
  (let ((j (gensym)))
    `(loop with ,j = 0 
	   do
       (setq ,j (do-for-array-elements (,j n) 
		  (set-quantity-element
		    managed-array-3 ,j
		    (,(if subtract? `-e `+e) 
		     (get-quantity-element managed-array-1 ,j)
		     (get-quantity-element managed-array-2 ,j)))))
	   while ,j)))

(declare-system-procedure-function g2-vector-add-new t) 

(defun-funcallable g2-vector-add-new (vector1 vector2 vector3)
  (let ((n (check-array-lengths-compatible vector1 vector2 vector3)))
    (when (=f n 0)
      (stack-error
       cached-top-of-stack
       "All arrays must be of non-zero length"))
    (barrier)
    (multiple-value-prog1
	(with-temporary-gensym-float-creation g2-vector-add-new
	  (cond ((and (frame-of-class-p vector1 'float-array)
		      (frame-of-class-p vector2 'float-array)
		      (frame-of-class-p vector3 'float-array))
		 (with-three-g2-vectors (vector1 vector2 vector3)
		   (add-or-subtract-float-vector-elements nil)))
		((and (frame-of-class-p vector1 'integer-array)
		      (frame-of-class-p vector2 'integer-array)
		      (frame-of-class-p vector3 'integer-array))
		 (with-three-g2-vectors (vector1 vector2 vector3)
		   (add-or-subtract-integer-vector-elements nil)))
		((and (frame-of-class-p vector1 'quantity-array)
		      (frame-of-class-p vector2 'quantity-array)
		      (frame-of-class-p vector3 'quantity-array))
		 (with-three-g2-vectors (vector1 vector2 vector3)
		   (add-or-subtract-quantity-vector-elements nil)))
		((and (frame-of-class-p vector1 'item-array)
		      (frame-of-class-p vector2 'item-array)
		      (frame-of-class-p vector3 'item-array))
		 (loop for k from 0 below n do
		   (g2-vector-add-new
		     (g2-array-aref vector1 k)
		     (g2-array-aref vector2 k)
		     (g2-array-aref vector3 k))))
		(t
		 (signal-invalid-vectors 
		   (gensym-list vector1 vector2 vector3) "a row add"))))
      (barrier))))

(declare-system-procedure-function g2-vector-substract t) 

(defun-funcallable g2-vector-substract (vector1 vector2 vector3)
  (let ((n (check-array-lengths-compatible vector1 vector2 vector3)))
    (when (=f n 0)
      (stack-error
       cached-top-of-stack
       "All arrays must be of non-zero length"))
    (barrier)
    (multiple-value-prog1
	(with-temporary-gensym-float-creation g2-vector-substract
	  (cond ((and (frame-of-class-p vector1 'float-array)
		      (frame-of-class-p vector2 'float-array)
		      (frame-of-class-p vector3 'float-array))
		 (with-three-g2-vectors (vector1 vector2 vector3)
		   (add-or-subtract-float-vector-elements t)))
		((and (frame-of-class-p vector1 'integer-array)
		      (frame-of-class-p vector2 'integer-array)
		      (frame-of-class-p vector3 'integer-array))
		 (with-three-g2-vectors (vector1 vector2 vector3)
		   (add-or-subtract-integer-vector-elements t)))
		((and (frame-of-class-p vector1 'quantity-array)
		      (frame-of-class-p vector2 'quantity-array)
		      (frame-of-class-p vector3 'quantity-array))
		 (with-three-g2-vectors (vector1 vector2 vector3)
		   (add-or-subtract-quantity-vector-elements t)))
		((and (frame-of-class-p vector1 'item-array)
		      (frame-of-class-p vector2 'item-array)
		      (frame-of-class-p vector3 'item-array))
		 (loop for k from 0 below n do
		   (g2-vector-substract 
		     (g2-array-aref vector1 k)
		     (g2-array-aref vector2 k)
		     (g2-array-aref vector3 k))))
		(t
		 (signal-invalid-vectors 
		   (gensym-list vector1 vector2 vector3) "a row add"))))
      (barrier))))

;;; G2-initialize-matrix-copy and g2-vector-copy are called by the system
;;; procedure g2-array-copy.  Note that g2-initialize-matrix-copy is currently
;;; called only with item-arrays.  (10/31/97)

(declare-system-procedure-function g2-initialize-matrix-copy t)

(defun-funcallable g2-initialize-matrix-copy (matrix1 matrix2)
  (let ((array-lengths-if-non-zero-and-equal
	  (check-array-lengths-compatible matrix1 matrix2)))
    (unless (and (loop for index from 0 below (g2-array-length matrix1)
		       for array-element = (g2-array-aref matrix1 index)
		       always (and (framep array-element)
				   (frame-of-class-p array-element 'quantity-array)))
		 (loop for index from 0 below (g2-array-length matrix2)
		       for array-element = (g2-array-aref matrix2 index)
		       always (and (framep array-element)
				   (frame-of-class-p array-element 'quantity-array))))
      (stack-error
	cached-top-of-stack
	"The elements of item-arrays given to g2-array-copy must be quantity-arrays."))
    (make-evaluation-integer array-lengths-if-non-zero-and-equal)))

(declare-system-procedure-function g2-vector-copy t)

(defun-funcallable g2-vector-copy (vector1 vector2)
  (let ((length1 (g2-array-length vector1))
	(length2 (g2-array-length vector2)))
    (unless (and (>f length1 0) (>f length2  0))
      (stack-error
	cached-top-of-stack
	"All arrays must be of non-zero length")))
  (barrier)
  (multiple-value-prog1
      (with-temporary-gensym-float-creation g2-vector-copy
	(cond ((and (frame-of-class-p vector1 'integer-array)
		    (frame-of-class-p vector2 'integer-array))
	       (g2-integer-vector-copy vector1 vector2))
	      ((and (frame-of-class-p vector1 'float-array)
		    (frame-of-class-p vector2 'float-array))
	       (g2-float-vector-copy vector1 vector2))
	      ((and (frame-of-class-p vector1 'quantity-array)
		    (frame-of-class-p vector2 'quantity-array))
	       (g2-quantity-vector-copy vector1 vector2))
	      (t
	       (signal-invalid-vectors 
		 (gensym-list vector1 vector2) "a row copy"))))
    (barrier)))

;;; G2-initialize-matrix-equal and g2-vector-equal are called by the system
;;; procedure g2-array-equal.

(declare-system-procedure-function g2-initialize-matrix-equal t)

(defun-funcallable g2-initialize-matrix-equal (matrix1 matrix2)
  (make-evaluation-integer
    (check-array-lengths-compatible matrix1 matrix2)))

(declare-system-procedure-function g2-vector-equal t)

(defun-funcallable g2-vector-equal (vector1 vector2)
  (unless (and (> (g2-array-length vector1) 0)
	       (> (g2-array-length vector2) 0))
    (stack-error
      cached-top-of-stack
      "All arrays must be of non-zero length"))
  (barrier)
  (multiple-value-prog1
      (with-temporary-gensym-float-creation g2-vector-equal
	(let ((equality?
	       (cond ((and (frame-of-class-p vector1 'integer-array)
			   (frame-of-class-p vector2 'integer-array))
		      (g2-integer-vector-equal vector1 vector2))
		     ((and (frame-of-class-p vector1 'float-array)
			   (frame-of-class-p vector2 'float-array))
		      (g2-float-vector-equal vector1 vector2))
		     ((and (frame-of-class-p vector1 'quantity-array)
			   (frame-of-class-p vector2 'quantity-array))
		      (g2-quantity-vector-equal vector1 vector2))
		     (t
		      (signal-invalid-vectors 
		        (gensym-list vector1 vector2) "an equal test")))))
	  (make-evaluation-truth-value
	    (if equality? truth falsity))))
    (barrier)))

;;; G2-initialize-matrix-transpose and g2-transpose-row are called by the system
;;; procedure g2-transpose.

(declare-system-procedure-function g2-initialize-matrix-transpose t)

(defun-funcallable g2-initialize-matrix-transpose (matrix1 matrix2)
  (multiple-value-bind 
    (m n n-for-square type)
      (check-matrices-compatible-for-transpose matrix1 matrix2)
    (values (make-evaluation-integer m)
	    (make-evaluation-integer n)
	    (make-evaluation-integer n-for-square)
	    (make-evaluation-symbol type))))

(declare-system-procedure-function g2-transpose-row t)

(defun-funcallable g2-transpose-row (i begin-j end-j type swap? matrix1 matrix2)
  (with-temporary-gensym-float-creation g2-transpose-row
    (setq i (evaluation-integer-value i)
	  begin-j (evaluation-integer-value begin-j)
	  end-j (evaluation-integer-value end-j)
	  type (evaluation-value-value type)
	  swap? (=f (evaluation-integer-value swap?) 1))
    (transpose-row 
      i begin-j end-j type swap? 
      (managed-g2-array matrix1) (managed-g2-array matrix2))))

;; Consider optimizing to not set diagonal for case when matrix1 and matrix2 are
;; the same.




(declare-system-procedure-function g2-array-multiply t)

(defun-funcallable g2-array-multiply (g2-array1 g2-array2)
  (barrier)
  (multiple-value-prog1
      (with-temporary-gensym-float-creation g2-array-multiply
	(let ((result? (g2-vector-multiply g2-array1 g2-array2)))
	  (make-evaluation-quantity result?)))
    (barrier)))

(declare-system-procedure-function g2-scalar-multiply t)

(defun-funcallable g2-scalar-multiply (g2-array1 g2-array2 x)
  (barrier)
  (multiple-value-prog1
      (with-temporary-gensym-float-creation g2-scalar-multiply
	(g2-scalar-multiply-1 g2-array1 g2-array2 (evaluation-value-value x)))
    (reclaim-evaluation-value x)
    (barrier)))

(declare-system-procedure-function g2-matrix-vector-to-vector-multiply t)

(defun-funcallable g2-matrix-vector-to-vector-multiply 
		   (matrix-vector vector1 vector2 index)
  (barrier)
  (with-temporary-gensym-float-creation g2-matrix-to-vector-multiply
    (cond ((frame-of-class-p vector2 'integer-array)
	   (g2-matrix-to-integer-vector-multiply 
	     matrix-vector vector1 vector2 index))
	  ((frame-of-class-p vector2 'float-array)
	   (g2-matrix-to-float-vector-multiply
	     matrix-vector vector1 vector2 index))
	  ((frame-of-class-p vector2 'quantity-array)
	   (g2-matrix-to-quantity-vector-multiply
	     matrix-vector vector1 vector2 index)))
    (barrier)
    ;; Return NIL, so that the caller does not reclaim an evaluation-value from
    ;; the above compuation.  - cpm, 6/13/95
    nil))

(declare-system-procedure-function g2-initialize-matrix-multiply t)

(defun-funcallable g2-initialize-matrix-multiply (matrix1 matrix2 matrix3)
  (multiple-value-bind 
    (m1 m2 n2 type)
      (check-matrices-compatible-for-multiply matrix1 matrix2 matrix3)
    (values (make-evaluation-integer m1)
	    (make-evaluation-integer m2)
	    (make-evaluation-integer n2)
	    (make-evaluation-symbol type))))

(declare-system-procedure-function g2-matrix-to-matrix-multiply t)

(defun-funcallable g2-matrix-to-matrix-multiply 
		   (j m2 type matrix1-vector matrix2 matrix3-vector)
  (barrier)
  (multiple-value-prog1
      (with-temporary-gensym-float-creation g2-matrix-to-matrix-multiply
	(setq j (evaluation-integer-value j)
	      m2 (evaluation-integer-value m2)
	      type (evaluation-value-value type))
	(multiply-row
	  j m2 type
	  (managed-g2-array matrix1-vector)
	  (managed-g2-array matrix2)
	  (managed-g2-array matrix3-vector)))
    (barrier)))

(defun signal-invalid-vectors (vector-list operation)
   (write-stack-error cached-top-of-stack
    (when (not 
	    (loop for vector in vector-list do
	      (when (not (framep vector))
		(if (null vector)
		    (tformat "Error attempting ~a on an array which does not exist.  "
			     operation)
		    (tformat "Error attempting ~a on something which is not an array.  "
			     operation))
		(tformat "Please check system procedure arguments, and contents of arguments.")
		(return t))))
      (write-list-in-chicago-style vector-list "and" t)
      (reclaim-gensym-list vector-list)
      (tformat " are not compatible for ~a." operation))))

;; J is assumed to always be a symbol here.



(defun get-matrix-row (matrix i)
  (managed-svref matrix (*f 2 i)))

(defun get-quantity-element (managed-array i)
  (let ((value-of-managed-array managed-array))
    (coerce-to-gensym-float
      (if (managed-float-array-p value-of-managed-array)
	  (managed-float-aref value-of-managed-array i)
	(extract-number (managed-svref value-of-managed-array i))))))

(defun set-quantity-element (managed-array i value)
  (let ((value-of-managed-array managed-array))
    (if (managed-float-array-p value-of-managed-array)
	(mutate-managed-float-array
	  value-of-managed-array i
	  (coerce-to-gensym-float value))
      (store-managed-number
	(managed-svref value-of-managed-array i)
	value))))

(defmacro with-three-g2-vectors-of-same-length
	  ((vector1 vector2 vector3) &body body)
  `(let ((n (check-array-lengths-compatible ,vector1 ,vector2 ,vector3))
	 (managed-array-1 (access-once (managed-g2-array ,vector1)))
	 (managed-array-2 (access-once (managed-g2-array ,vector2)))
	 (managed-array-3 (access-once (managed-g2-array ,vector3))))
     ,@body))

(defmacro with-two-g2-vectors-of-same-length
	  ((vector1 vector2) &body body)
  `(let ((n (check-array-lengths-compatible ,vector1 ,vector2))
	 (managed-array-1 (access-once (managed-g2-array ,vector1)))
	 (managed-array-2 (access-once (managed-g2-array ,vector2))))
     ,@body))

(defun g2-integer-vector-add (vector1 vector2 vector3)
  (with-three-g2-vectors-of-same-length
    (vector1 vector2 vector3)
    (if subtract-arrays-instead?
	(add-or-subtract-integer-vector-elements t)
	(add-or-subtract-integer-vector-elements nil))))

(defun g2-float-vector-add (vector1 vector2 vector3)
  (with-three-g2-vectors-of-same-length
    (vector1 vector2 vector3)
    (if subtract-arrays-instead?
	(add-or-subtract-float-vector-elements t)
	(add-or-subtract-float-vector-elements nil))))

(defun g2-quantity-vector-add (vector1 vector2 vector3)
  (with-three-g2-vectors-of-same-length
    (vector1 vector2 vector3)
    (if subtract-arrays-instead?
	(add-or-subtract-quantity-vector-elements t)
	(add-or-subtract-quantity-vector-elements nil))))

(defun g2-integer-vector-equal (vector1 vector2)
  (with-two-g2-vectors-of-same-length 
    (vector1 vector2)
    (loop for j from 0 below n do
      (when (/=f (managed-svref managed-array-1 j)
		 (managed-svref managed-array-2 j))
	(return nil))
	  finally (return t))))

(defun g2-integer-vector-copy (vector1 vector2)
  (with-two-g2-vectors-of-same-length 
    (vector1 vector2)
    (loop for j from 0 below n do
      (setf (managed-svref managed-array-2 j)
	    (managed-svref managed-array-1 j)))))

(defun g2-float-vector-equal (vector1 vector2)
  (with-two-g2-vectors-of-same-length 
    (vector1 vector2)
    (loop for j from 0 below n do
      (when (/=e (managed-float-aref managed-array-1 j)
		 (managed-float-aref managed-array-2 j))
	(return nil))
	  finally (return t))))

(defun g2-float-vector-copy (vector1 vector2)
  (with-two-g2-vectors-of-same-length 
    (vector1 vector2)
    (loop for j from 0 below n do
      (mutate-managed-float-array
	managed-array-2 j
	(managed-float-aref managed-array-1 j)))))

(defun g2-quantity-vector-equal (vector1 vector2)
  (with-two-g2-vectors-of-same-length 
    (vector1 vector2)
    (loop with value-to-return = t
	  with j = 0 
	  do
      (setq j (do-for-array-elements (j n)
		(when (/=e (get-quantity-element managed-array-1 j)
			   (get-quantity-element managed-array-2 j))
		  (setq value-to-return nil
			j nil)
		  (return nil))))
	  while j
	  finally (return value-to-return))))

(defun g2-quantity-vector-copy (vector1 vector2)
  (let ((target-is-integer-array-p
	  (frame-of-class-p vector2 'integer-array)))
    (with-two-g2-vectors-of-same-length 
	(vector1 vector2)
      (loop with j = 0 
	    do
	(setq j (do-for-array-elements (j n)
		  (set-quantity-element
		    managed-array-2 j
		    (let ((source-value
			    (get-quantity-element managed-array-1 j)))
		      (if (and target-is-integer-array-p
			       (gensym-float-p source-value))
			  (truncate-evaluation-float-function
			    (make-evaluation-float source-value)
			    'g2-array-copy
			    cached-top-of-stack)
			  source-value)))))
	  while j))))

(defun check-matrices-compatible-for-transpose (matrix1 matrix2)
  (let* ((managed-array-for-matrix-1 (managed-g2-array matrix1))
	 (managed-array-for-matrix-2 (managed-g2-array matrix2))
	 (m (g2-array-length matrix1))
	 (first-row-of-matrix-1
	   (managed-svref managed-array-for-matrix-1 0))
	 (type
	   (check-matrix-row-type matrix1 first-row-of-matrix-1))
	 (n (g2-array-length first-row-of-matrix-1)))
    (loop for i from 2 below (*f 2 m) by 2
	  as row = (managed-svref managed-array-for-matrix-1 i)
	  do 
      (check-row-length-and-type-compatible
	matrix1 row n type))
    (check-array-length-compatible matrix2 n)
    (loop for i from 0 below (*f 2 n) by 2
	  as row = (managed-svref managed-array-for-matrix-2 i)
	  do 
      (check-row-length-and-type-compatible
	matrix2 row m type))
    (values m n (minf m n) type)))

(defun check-matrices-compatible-for-multiply (matrix1 matrix2 matrix3)
  (let* ((managed-array-for-matrix-1 (managed-g2-array matrix1))
	 (managed-array-for-matrix-2 (managed-g2-array matrix2))
	 (managed-array-for-matrix-3 (managed-g2-array matrix3))
	 (m1 (g2-array-length matrix1))
	 (m2 (g2-array-length matrix2))
	 (first-row-of-matrix-3
	   (managed-svref managed-array-for-matrix-3 0))
	 (type
	   (check-matrix-row-type matrix3 first-row-of-matrix-3))
	 (n2 (g2-array-length first-row-of-matrix-3)))
    (loop for i from 2 below (*f 2 m1) by 2
	  as row = (managed-svref managed-array-for-matrix-1 i)
	  do 
      (check-row-length-and-type-compatible
	matrix1 row m2 type))
    (loop for i from 0 below (*f 2 m2) by 2
	  as row = (managed-svref managed-array-for-matrix-2 i)
	  do 
      (check-row-length-and-type-compatible
	matrix2 row n2 type))
    (check-array-length-compatible matrix3 m1)
    (loop for i from 2 below (*f 2 m1) by 2
	  as row = (managed-svref managed-array-for-matrix-3 i)
	  do 
      (check-row-length-and-type-compatible
	matrix3 row n2 type))
    (values m1 m2 n2 type)))

(defmacro swap-elements-for-transpose
	  (i j type
	   managed-array-for-matrix-1-row
	   managed-array-for-matrix-2-row
	   managed-array-for-matrix-1-row-for-column
	   managed-array-for-matrix-2-row-for-column)
  (case type
    (integer
     `(psetf (managed-svref ,managed-array-for-matrix-2-row-for-column ,i)
	     (managed-svref ,managed-array-for-matrix-1-row ,j)
	     (managed-svref ,managed-array-for-matrix-2-row ,j)
	     (managed-svref ,managed-array-for-matrix-1-row-for-column ,i)))
    (float
     `(let ((temp (allocate-managed-float
		    (managed-float-aref 
		      ,managed-array-for-matrix-1-row-for-column ,i))))
	(mutate-managed-float-array
	  ,managed-array-for-matrix-2-row-for-column ,i
	  (managed-float-aref ,managed-array-for-matrix-1-row ,j)) 
	(mutate-managed-float-array
	  ,managed-array-for-matrix-2-row ,j
	  (managed-float-value temp))
	(reclaim-managed-float temp)))
    (quantity
     `(let ((temp (get-quantity-element
		    managed-array-for-matrix-1-row-for-column ,i)))
	(set-quantity-element
	  managed-array-for-matrix-2-row-for-column ,i
	  (get-quantity-element
	    managed-array-for-matrix-1-row ,j))
	(set-quantity-element
	  managed-array-for-matrix-2-row ,j temp)))))
;; Args are always symbols.

(defmacro set-elements-for-transpose
	  (i j type
	   managed-array-for-matrix-1-row
	   managed-array-for-matrix-2-row-for-column)
  (case type
    (integer
     `(setf (managed-svref ,managed-array-for-matrix-2-row-for-column ,i)
	    (managed-svref ,managed-array-for-matrix-1-row ,j)))
    (float
     `(mutate-managed-float-array 
	,managed-array-for-matrix-2-row-for-column ,i
	(managed-float-aref ,managed-array-for-matrix-1-row ,j)))
    (quantity
     `(set-quantity-element
	,managed-array-for-matrix-2-row-for-column ,i
	(get-quantity-element
	  ,managed-array-for-matrix-1-row ,j)))))
;; Args are always symbols.

(defmacro transpose-row-1 
	  (i begin-j end-j type swap?
	   managed-array-for-matrix-1
	   managed-array-for-matrix-2
	   managed-array-for-matrix-1-row
	   managed-array-for-matrix-2-row)
  (if (neq type 'quantity)
      `(loop for j from ,begin-j below ,end-j
		 ,@(if swap?
		       `(as managed-array-for-matrix-1-row-for-column
			    = (managed-g2-array
				(get-matrix-row ,managed-array-for-matrix-1 j))))
	     as managed-array-for-matrix-2-row-for-column
		= (managed-g2-array
		    (get-matrix-row ,managed-array-for-matrix-2 j))
	     do
	 ,(if swap?
	      `(swap-elements-for-transpose
		 ,i j ,type
		 ,managed-array-for-matrix-1-row
		 ,managed-array-for-matrix-2-row
		 managed-array-for-matrix-1-row-for-column
		 managed-array-for-matrix-2-row-for-column)
	      `(set-elements-for-transpose
		 ,i j ,type
		 ,managed-array-for-matrix-1-row
		 managed-array-for-matrix-2-row-for-column)))
      `(loop with j = ,begin-j
	     do
	 (setq j (do-for-array-elements (j ,end-j)
		   (let (,@(if swap?
			       `((managed-array-for-matrix-1-row-for-column
				   (managed-g2-array
				     (get-matrix-row 
				       ,managed-array-for-matrix-1 j)))))
			 (managed-array-for-matrix-2-row-for-column
			   (managed-g2-array
			     (get-matrix-row 
			       ,managed-array-for-matrix-2 j))))
		     ,(if swap?
			  `(swap-elements-for-transpose
			     ,i j ,type
			     ,managed-array-for-matrix-1-row
			     ,managed-array-for-matrix-2-row
			     managed-array-for-matrix-1-row-for-column
			     managed-array-for-matrix-2-row-for-column)
			  `(set-elements-for-transpose
			     ,i j ,type
			     ,managed-array-for-matrix-1-row
			     managed-array-for-matrix-2-row-for-column)))))
	     while j)))

;; Args are always symbols.

;; Consider optimizing for square case.



(defmacro transpose-row-with-or-without-swaps
	  (i begin-j end-j type swap?
	   managed-array-for-matrix-1
	   managed-array-for-matrix-2
	   managed-array-for-matrix-1-row
	   managed-array-for-matrix-2-row)
  `(cond 
     ((eq ,type 'integer)
      (transpose-row-1
	,i ,begin-j ,end-j integer ,swap?
	,managed-array-for-matrix-1
	,managed-array-for-matrix-2
	,managed-array-for-matrix-1-row
	,managed-array-for-matrix-2-row))
     ((eq ,type 'float)
      (transpose-row-1
	,i ,begin-j ,end-j float ,swap?
	,managed-array-for-matrix-1
	,managed-array-for-matrix-2
	,managed-array-for-matrix-1-row
	,managed-array-for-matrix-2-row))
     ((eq ,type 'quantity)
      (transpose-row-1
	,i ,begin-j ,end-j quantity ,swap?
	,managed-array-for-matrix-1
	,managed-array-for-matrix-2
	,managed-array-for-matrix-1-row
	,managed-array-for-matrix-2-row))))
;; Args are always symbols.



(defun transpose-row
       (i begin-j end-j type swap?
	managed-array-for-matrix-1
	managed-array-for-matrix-2)
  (let ((managed-array-for-matrix-1-row
	  (managed-g2-array
	    (get-matrix-row managed-array-for-matrix-1 i)))
	managed-array-for-matrix-2-row)
    (cond
      (swap?
       (setq managed-array-for-matrix-2-row
	     (managed-g2-array
	       (get-matrix-row managed-array-for-matrix-2 i)))
       (transpose-row-with-or-without-swaps
	 i begin-j end-j type t
	 managed-array-for-matrix-1
	 managed-array-for-matrix-2
	 managed-array-for-matrix-1-row
	 managed-array-for-matrix-2-row))
      (t
       (transpose-row-with-or-without-swaps
	 i begin-j end-j type nil
	 managed-array-for-matrix-1
	 managed-array-for-matrix-2
	 managed-array-for-matrix-1-row
	 managed-array-for-matrix-2-row)))))

(defun g2-vector-multiply (vector1 vector2)
  (barrier)
  (multiple-value-prog1
      (cond ((and (frame-of-class-p vector1 'integer-array)
		  (frame-of-class-p vector2 'integer-array))
	     (g2-integer-vector-multiply vector1 vector2))
	    ((and (frame-of-class-p vector1 'float-array)
		  (frame-of-class-p vector2 'float-array))
	     (g2-float-vector-multiply vector1 vector2))
	    ((and (frame-of-class-p vector1 'quantity-array)
		  (frame-of-class-p vector2 'quantity-array))
	     (g2-quantity-vector-multiply vector1 vector2))
	    (t
	     (signal-invalid-vectors 
	       (gensym-list vector1 vector2) "a row multiply")))
    (barrier)))

(defun g2-scalar-multiply-1 (vector1 vector2 x)
  (barrier)
  (multiple-value-prog1
      (cond ((and (frame-of-class-p vector1 'integer-array)
		  (frame-of-class-p vector2 'integer-array)
		  (fixnump x))
	     (g2-integer-scalar-multiply vector1 vector2 x))
	    ((and (frame-of-class-p vector1 'float-array)
		  (frame-of-class-p vector2 'float-array)
		  (gensym-float-p x))
	     (g2-float-scalar-multiply vector1 vector2 x))
	    (t
	     (g2-quantity-scalar-multiply vector1 vector2 x)))
    (barrier)))

(defun g2-integer-vector-multiply (vector1 vector2)
  (with-two-g2-vectors-of-same-length 
    (vector1 vector2)
    (loop with sum = 0
	  for j from 0 below n do
      (setf sum
	    (+f sum
		(*f
		  (managed-svref managed-array-1 j)
		  (managed-svref managed-array-2 j))))
	  finally (return sum))))

(defun g2-integer-scalar-multiply (vector1 vector2 x)
  (with-two-g2-vectors-of-same-length 
    (vector1 vector2)
    (loop for j from 0 below n do
      (setf (managed-svref managed-array-2 j)
	    (*f x (managed-svref managed-array-1 j))))))

(defun g2-float-vector-multiply (vector1 vector2)
  (with-two-g2-vectors-of-same-length 
    (vector1 vector2)
    (loop with managed-sum = (allocate-managed-float 0.0d0)
	  for j from 0 below n do
      (mutate-managed-float-value
	managed-sum
	(+e (managed-float-value managed-sum)
	    (*e (managed-float-aref managed-array-1 j)
		(managed-float-aref managed-array-2 j))))
	  finally
	    (let ((sum (managed-float-value managed-sum)))
	      (reclaim-managed-float managed-sum)
	      (return sum)))))

(defun g2-float-scalar-multiply (vector1 vector2 x)
  (with-two-g2-vectors-of-same-length 
    (vector1 vector2)
    (loop for j from 0 below n do
      (mutate-managed-float-array
	managed-array-2 j
	(*e x (managed-float-aref managed-array-1 j))))))

(defun g2-quantity-vector-multiply (vector1 vector2)
  (with-two-g2-vectors-of-same-length 
      (vector1 vector2)
    (loop with sum-box = (allocate-managed-float 0.0d0)
	  with j = 0 
	  do
      (setq j (do-for-array-elements (j n)
		(mutate-managed-float-value
		  sum-box
		  (+e (managed-float-value sum-box)
		      (*e
			(get-quantity-element managed-array-1 j)
			(get-quantity-element managed-array-2 j))))))
	  while j
	  finally
	    (let ((sum (managed-float-value sum-box)))
	      (reclaim-managed-float sum-box)
	      (return sum)))))

(defun g2-quantity-scalar-multiply (vector1 vector2 x)
  (with-two-g2-vectors-of-same-length 
    (vector1 vector2)
    (loop with j = 0
	  do
      (setq j (do-for-array-elements (j n)
		(set-quantity-element
		  managed-array-2 j
		  (* x (get-quantity-element managed-array-1 j)))))
	  while j)))

(defun g2-matrix-to-integer-vector-multiply 
       (matrix-vector vector1 vector2 index)
  (setf (managed-svref (managed-g2-array vector2) index)
        (g2-round (g2-vector-multiply matrix-vector vector1))))

(defun g2-matrix-to-float-vector-multiply 
       (matrix-vector vector1 vector2 index)
  (mutate-managed-float-array
   (managed-g2-array vector2) index
   (coerce-to-gensym-float 
    (g2-vector-multiply matrix-vector vector1))))

(defun g2-matrix-to-quantity-vector-multiply 
       (matrix-vector vector1 vector2 index)
  (set-quantity-element
    (managed-g2-array vector2) index
    (g2-vector-multiply matrix-vector vector1)))

(defmacro multiply-row-1 
	  (j n type
	   managed-array-for-matrix-1-row
	   managed-array-for-matrix-2 managed-array-for-matrix-3-row)
  (if (neq type 'quantity)
      `(loop with sum = ,(if (eq type 'integer)
			     `0
			     `(allocate-managed-float 0.0d0))
	     for k from 0 below ,n
	     as managed-array-for-matrix-2-row
		= (managed-g2-array
		    (get-matrix-row ,managed-array-for-matrix-2 k))
	     do
	 ,(if (eq type 'integer)
	      `(setq sum 
		     (+f sum
			 (*f (managed-svref
			       ,managed-array-for-matrix-1-row k)
			     (managed-svref
			       managed-array-for-matrix-2-row ,j))))
	      `(mutate-managed-float-value
		 sum
		 (+e (managed-float-value sum)
		     (*e (managed-float-aref
			   ,managed-array-for-matrix-1-row k)
			 (managed-float-aref
			   managed-array-for-matrix-2-row ,j)))))
	     finally
	       ,(if (eq type 'integer)
		    `(setf (managed-svref 
			     ,managed-array-for-matrix-3-row ,j)
			   sum)
		    `(progn
		       (mutate-managed-float-array
			 ,managed-array-for-matrix-3-row ,j
			 (managed-float-value sum))
		       (reclaim-managed-float sum))))
      `(loop with sum-box = (allocate-managed-float 0.0d0)
	     with k = 0
	     do
	 (setq k (do-for-array-elements (k ,n)
		   (let ((managed-array-for-matrix-2-row
			   (managed-g2-array
			     (get-matrix-row 
			       ,managed-array-for-matrix-2 k))))
		     (mutate-managed-float-value
		       sum-box
		       (+e (managed-float-value sum-box)
			   (*e
			     (get-quantity-element
			       ,managed-array-for-matrix-1-row k)
			     (get-quantity-element
			       managed-array-for-matrix-2-row ,j)))))))
	     while k
	     finally
	       (progn
		 (set-quantity-element
		   ,managed-array-for-matrix-3-row ,j
		   (managed-float-value sum-box))
		 (reclaim-managed-float sum-box)))))

;; Args are always symbols.

(defun multiply-row
       (j n type
	managed-array-for-matrix-1-row
	managed-array-for-matrix-2 managed-array-for-matrix-3-row)
  (case type
    (integer (multiply-row-1
	       j n integer
	       managed-array-for-matrix-1-row
	       managed-array-for-matrix-2
	       managed-array-for-matrix-3-row))
    (float (multiply-row-1
	     j n float
	     managed-array-for-matrix-1-row
	     managed-array-for-matrix-2
	     managed-array-for-matrix-3-row))
    (quantity (multiply-row-1
		j n quantity
		managed-array-for-matrix-1-row
		managed-array-for-matrix-2
		managed-array-for-matrix-3-row))))

;;;; Sparse Matrix Operations

;;; g2-sparse-scatter
;;; g2-sparse-gather
;;; g2-sparse-multiply
;;; g2-sparse-add
;;; g2-sparse-get
;;; g2-sparse-set
;;; g2-array-min
;;; g2-array-max
;;; g2-array-sum
;;; g2-array-sum-abs

;;; G2-sparse-add takes args value-array-1, index-array-1,
;;; value-array-2, index-array-2, full-array, alpha, begin-index-1,
;;; end-index-1, begin-index-2, end-index-2, and
;;; full-array-initialized?.  The value and index arrays represent
;;; sparse vectors.  All elements of the second sparse vector with
;;; sparse indices between begin-index-2 and end-index-2 (inclusive) are
;;; multiplied by alpha and then are added to the elements of the first
;;; sparse vector with sparse indices between begin-index-1 and
;;; begin-index-2 inclusive, the result being left in the first sparse
;;; vector.

;;; The begin-index, end-index, and full-array-initialized?  args are
;;; useful since in many cases, a sparse scatter, add, or multiply is to
;;; be done on only a portion of a sparse array.

;;; All system procedures which take full array arguments assume that
;;; the full array is initialized to all 0's, and return the full array
;;; to this state when done, unless the full-array-initialized?  arg is
;;; true, in which case the full-array is not modified at all.  In the
;;; case of g2-sparse-multiply, if full-array-initialized?  is true,
;;; then value-array-2, index-array-2, begin-index-2, and end-index-2
;;; are dummy arguments.  The full array must always be of length n
;;; where n is the maximum index in the corresponding sparse array + 1.

;; Scattering is efficient since it only involves iterating over the sparse
;; vector.  Gathering is inefficient since it involves iterating over the full
;; vector.  Because scatter is efficient, and because scatter is used in many
;; primitives and results in an ordered full vector, it is not very important to
;; keep the sparse vectors ordered (elements appearing in order of increasing
;; index).  If ordered sparse vectors are really necessary, this can be
;; accomplished by doing a scatter, then a gather.



(declare-system-procedure-function g2-sparse-scatter t)

(defun-funcallable g2-sparse-scatter 
		   (value-array index-array full-array begin-index end-index)
  (cond ((or (not (evaluation-integer-p begin-index))
	     (not (evaluation-integer-p end-index)))
	 (stack-error
	    cached-top-of-stack
	    "The begin index and end index must both be integers"))
	((or (not (g2-array-p value-array))
	     (not (g2-array-p index-array)))
	 (stack-error
	    cached-top-of-stack
	    "The value and index arrays must both be arrays")))
  
  (setq begin-index (evaluation-integer-value begin-index)
	end-index (evaluation-integer-value end-index))
  (when (>= begin-index end-index)
    	 (stack-error
	    cached-top-of-stack
	    "The end-index ~a must be greater than the begin-index ~a"
	    end-index begin-index))
  (check-for-incompatible-from-to-arrays value-array full-array)
  (with-temporary-gensym-float-creation g2-sparse-scatter
    (cond 
      ((and 
	 (frame-of-class-p value-array 'integer-array)
	 (frame-of-class-p full-array 'integer-array))
       (g2-integer-sparse-scatter 
	 value-array index-array full-array begin-index end-index))
      ((and 
	 (frame-of-class-p value-array 'float-array)
	 (frame-of-class-p full-array 'float-array))
       (g2-float-sparse-scatter 
	 value-array index-array full-array begin-index end-index))
      ((and 
	 (frame-of-class-p full-array 'integer-array)
	 (frame-of-class-p value-array 'quantity-array))
       (g2-quantity-to-integer-sparse-scatter 
	 value-array index-array full-array begin-index end-index))
      (t					       ; quantity arrays case
       (g2-quantity-sparse-scatter 
	 value-array index-array full-array begin-index end-index)))))

(declare-system-procedure-function g2-sparse-gather t)

(defun check-for-incompatible-from-to-arrays (from-array to-array)
  (when (frame-of-class-p to-array 'integer-array)
    (when (frame-of-class-p from-array 'float-array)
	  (stack-error
	   cached-top-of-stack
	   "Values cannot be automatically converted from ~NF to ~NF"
	   from-array to-array))))

(defun-funcallable g2-sparse-gather (value-array index-array full-array)
  (unless (and (g2-array-p value-array)
	       (g2-array-p index-array)
	       (g2-array-p full-array))
    (stack-error
      cached-top-of-stack
      "The value,index and full arrays must all be arrays"))
  (check-for-incompatible-from-to-arrays full-array value-array)
  (with-temporary-gensym-float-creation g2-sparse-gather
    (cond 
      ((and 
	 (frame-of-class-p value-array 'integer-array)
	 (frame-of-class-p full-array 'integer-array))
       (g2-integer-sparse-gather value-array index-array full-array))
      ((and 
	 (frame-of-class-p value-array 'float-array)
	 (frame-of-class-p full-array 'float-array))
       (g2-float-sparse-gather value-array index-array full-array))
      ((and 
	 (frame-of-class-p value-array 'integer-array)
	 (frame-of-class-p full-array 'quantity-array))
       (g2-quantity-to-integer-sparse-gather value-array index-array full-array))
      (t					       ; quantity arrays case
       (g2-quantity-sparse-gather value-array index-array full-array)))))

(defun evaluation-truth-value-true-p (evaluation-truth-value)
  (>f (evaluation-truth-value-value evaluation-truth-value) 0))

(declare-system-procedure-function g2-sparse-add t)

(defun-funcallable g2-sparse-add 
		   (value-array-1 index-array-1 value-array-2 index-array-2 
		    full-array alpha
		    range
		    full-array-initialized?)
  (unless (and (g2-array-p value-array-1)
	       (g2-array-p index-array-1)
	       (g2-array-p value-array-2)
	       (g2-array-p index-array-2)
	       (g2-array-p full-array))
    (stack-error
      cached-top-of-stack
      "value-array-1, index-array-1, value-array-2, index-array-2 and full array must all be arrays"))
  (let* ((range-managed-array (check-range-array range))
	 (begin-index-1 (managed-svref range-managed-array 0))
	 (end-index-1 (managed-svref range-managed-array 1))
	 (begin-index-2 (managed-svref range-managed-array 2))
	 (end-index-2 (managed-svref range-managed-array 3)))
    (setq full-array-initialized? 
	  (evaluation-truth-value-true-p full-array-initialized?))
    (barrier)
    (multiple-value-prog1
	(with-temporary-gensym-float-creation g2-sparse-add
	  (setq alpha (evaluation-value-value alpha))
	  (cond ((and (frame-of-class-p value-array-1 'integer-array)
		      (frame-of-class-p value-array-2 'integer-array)
		      (frame-of-class-p full-array 'integer-array)
		      (fixnump alpha))
		 (g2-integer-sparse-add
		   value-array-1 index-array-1 value-array-2 index-array-2 full-array alpha
		   begin-index-1 end-index-1 begin-index-2 end-index-2
		   full-array-initialized?))
		((and (frame-of-class-p value-array-1 'float-array)
		      (frame-of-class-p value-array-2 'float-array)
		      (frame-of-class-p full-array 'float-array)
		      (gensym-float-p alpha))
		 (g2-float-sparse-add
		   value-array-1 index-array-1 value-array-2 index-array-2 full-array alpha
		   begin-index-1 end-index-1 begin-index-2 end-index-2
		   full-array-initialized?))
		(t ; quantity arrays case
		 (when (fixnump alpha)
		   (setq alpha (coerce-fixnum-to-gensym-float alpha)))
		 (g2-quantity-sparse-add
		   value-array-1 index-array-1 value-array-2 index-array-2 full-array alpha
		   begin-index-1 end-index-1 begin-index-2 end-index-2
		   full-array-initialized?))))
      (barrier))))

(declare-system-procedure-function g2-sparse-multiply t)

(defun-funcallable g2-sparse-multiply
    (value-array-1 index-array-1 value-array-2 index-array-2 full-array
		   range
		   full-array-initialized?)
  (unless (and (g2-array-p value-array-1)
	       (g2-array-p index-array-1)
	       (g2-array-p value-array-2)
	       (g2-array-p index-array-2)
	       (g2-array-p full-array))
    (stack-error
      cached-top-of-stack
      "value-array-1, index-array-1, value-array-2, index-array-2 and full array must all be arrays"))
  (let* ((range-managed-array (check-range-array range))
	 (begin-index-1 (managed-svref range-managed-array 0))
	 (end-index-1 (managed-svref range-managed-array 1))
	 (begin-index-2 (managed-svref range-managed-array 2))
	 (end-index-2 (managed-svref range-managed-array 3)))
    (setq full-array-initialized?
	  (evaluation-truth-value-true-p full-array-initialized?))
    (barrier)
    (multiple-value-prog1
	(with-temporary-gensym-float-creation g2-sparse-multiply
	  (cond ((and (frame-of-class-p value-array-1 'integer-array)
		      (frame-of-class-p value-array-2 'integer-array)
		      (frame-of-class-p full-array 'integer-array))
		 (g2-integer-sparse-multiply
		   value-array-1 index-array-1 value-array-2 index-array-2 full-array
		   begin-index-1 end-index-1 begin-index-2 end-index-2
		   full-array-initialized?))
		((and (frame-of-class-p value-array-1 'float-array)
		      (frame-of-class-p value-array-2 'float-array)
		      (frame-of-class-p full-array 'float-array))
		 (g2-float-sparse-multiply
		   value-array-1 index-array-1 value-array-2 index-array-2 full-array
		   begin-index-1 end-index-1 begin-index-2 end-index-2
		   full-array-initialized?))
		(t ; quantity arrays case
		 (g2-quantity-sparse-multiply
		   value-array-1 index-array-1 value-array-2 index-array-2 full-array
		   begin-index-1 end-index-1 begin-index-2 end-index-2
		   full-array-initialized?))))
      (barrier))))

(defmacro with-sparse-and-full-vector
	  ((value-array index-array full-array &optional begin-index end-index) 
	   &body body)
  `(let* ((n (g2-array-length full-array))
	  (l (check-array-lengths-compatible ,value-array ,index-array))
	  ,@(when (or begin-index end-index)
	      `((max-index (-f l 1))))
	  (value-managed-array (managed-g2-array ,value-array))
	  (index-managed-array (managed-g2-array ,index-array))
	  (full-managed-array (managed-g2-array ,full-array)))
     ,@(when begin-index
	 `((check-index-within-bounds ,begin-index max-index)))
     ,@(when end-index
	 `((check-index-within-bounds ,end-index max-index)))
     ,@body))

(defmacro check-sparse-index-exceeds-full-length (full-index n full-array)
  `(cond ((not (<f ,full-index ,n))
	  (stack-error
	    cached-top-of-stack
	    "The index ~d for the packed vector is greater than the maximum index ~d for the array ~NF." 
	    ,full-index (-f ,n 1) ,full-array))
	 ((minusp full-index)
	  (stack-error
	    cached-top-of-stack
	    "The index ~d for the packed vector is negative"
	    ,full-index))))

(defparameter default-min-to-extend-sparse-vector 20)

(defun extend-sparse-vector-as-necessary
       (value-array index-array sparse-index value-array-length)
  (change-sparse-vector-length
    value-array index-array
    (+f value-array-length
	(maxf
	  default-min-to-extend-sparse-vector
	  (-f sparse-index (-f value-array-length 1)))))
  (values (g2-array-length value-array)
	  (managed-g2-array value-array)
	  (managed-g2-array index-array)))

(defun make-sparse-vector-exact-size
       (value-array index-array sparse-index value-array-length)
  (when (/=f sparse-index value-array-length)
    (change-sparse-vector-length
      value-array index-array
      sparse-index)))

(defun change-sparse-vector-length
       (value-array index-array desired-length)
  (when (not (g2-array-length-ok-p value-array desired-length))
    (bad-g2-array-length-stack-error value-array desired-length cached-top-of-stack))
  (let ((note-as-kb-state-change? t)
	(do-not-note-permanent-changes-p t))
    (note-kb-state-change value-array 'g2-array-length)
    (note-kb-state-change index-array 'g2-array-length)
    (change-slot-value value-array 'g2-array-length desired-length)
    (change-slot-value index-array 'g2-array-length desired-length)))

(def-substitution-macro integer-set-sparse-and-clear-full
			(value-managed-array index-managed-array full-managed-array
			 value sparse-index full-index)
  (setf (managed-svref value-managed-array sparse-index) value
	(managed-svref index-managed-array sparse-index) full-index
	(managed-svref full-managed-array full-index) 0))



(defun g2-integer-sparse-scatter 
       (value-array index-array full-array begin-index end-index)
  (with-sparse-and-full-vector
    (value-array index-array full-array begin-index end-index)
    (loop for j from begin-index to end-index
	  as full-index = (managed-svref index-managed-array j)
	  do
      (check-sparse-index-exceeds-full-length full-index n full-array)
      (setf (managed-svref full-managed-array full-index)
	    (managed-svref value-managed-array j)))))

(defun g2-quantity-to-integer-sparse-scatter 
       (value-array index-array full-array begin-index end-index)
  (with-sparse-and-full-vector
    (value-array index-array full-array begin-index end-index)
    (loop for j from begin-index to end-index
	  as full-index = (managed-svref index-managed-array j)
	  as value = (evaluation-value-value (managed-svref value-managed-array j))
	  do
      
      (check-sparse-index-exceeds-full-length full-index n full-array)
      (unless (fixnump value)
	(stack-error cached-top-of-stack "~a is not a valid value for an integer array " value))
      (setf (managed-svref full-managed-array full-index)
	    value))))

(defun g2-integer-sparse-gather (value-array index-array full-array)
  (with-sparse-and-full-vector
    (value-array index-array full-array)
    (loop with sparse-index = 0
	  with value-array-length = l
	  for j from 0 below n
	  as value = (managed-svref full-managed-array j)
	  do
      (when (/=f value 0)
	(when (not (<f sparse-index value-array-length))
	  (multiple-value-setq
	    (value-array-length value-managed-array index-managed-array)
	    (extend-sparse-vector-as-necessary
	      value-array index-array sparse-index value-array-length)))
	(integer-set-sparse-and-clear-full
	  value-managed-array index-managed-array full-managed-array
	  value sparse-index j)
	(setq sparse-index (+f sparse-index 1)))
      finally
	    (make-sparse-vector-exact-size
	      value-array index-array sparse-index value-array-length))))

;; This extends the sparse vector if necessary (if there is fill-in).  To avoid
;; excessive extension, the sparse vector is extended by at least
;; default-min-to-extend-sparse-vector.  The sparse vector is set to the exact
;; size needed in the finally clause.



(defun g2-integer-sparse-add 
       (value-array-1 index-array-1 value-array-2 index-array-2 full-array alpha
	begin-index-1 end-index-1 begin-index-2 end-index-2
	full-array-initialized?)
  (when (not full-array-initialized?)
    (g2-integer-sparse-scatter 
      value-array-2 index-array-2 full-array begin-index-2 end-index-2))
  (with-sparse-and-full-vector
    (value-array-1 index-array-1 full-array begin-index-1 end-index-1)
    (let* (value
	   (l2 (check-array-lengths-compatible 
		 value-array-2 index-array-2))
	   (max-index-2 (-f l2 1)))
      (check-index-within-bounds begin-index-2 max-index-2)
      (check-index-within-bounds end-index-2 max-index-2)
      (loop for j from begin-index-1 to end-index-1
	    as full-index = (managed-svref index-managed-array j)
	    do
	(check-sparse-index-exceeds-full-length full-index n full-array)
	(setq value (managed-svref full-managed-array full-index))
	(when (/=f value 0)
	  (setf (managed-svref value-managed-array j)
		(+f (managed-svref value-managed-array j)
		    (*f alpha value)))
	  (setf (managed-svref full-managed-array full-index)
		0)))
      (loop with index-managed-array-2 = (managed-g2-array index-array-2)
	    with value-managed-array-2 = (managed-g2-array value-array-2)
	    with value-array-length = l
	    with sparse-index = value-array-length
	    for j from begin-index-2 to end-index-2
	    as full-index = (managed-svref index-managed-array-2 j)
	    do
	(check-sparse-index-exceeds-full-length full-index n full-array)
	(setq value (managed-svref full-managed-array full-index))
	(cond
	  ((/=f value 0)
	   (when (not (<f sparse-index value-array-length))
	     (multiple-value-setq
	       (value-array-length value-managed-array index-managed-array)
	       (extend-sparse-vector-as-necessary
		 value-array-1 index-array-1 sparse-index value-array-length)))
	   (setf (managed-svref value-managed-array sparse-index) (*f alpha value)
		 (managed-svref index-managed-array sparse-index) full-index)
	   (when (not full-array-initialized?)
	     (setf (managed-svref full-managed-array full-index) 0))
	   (setq sparse-index (+f sparse-index 1)))
	  (full-array-initialized?
	   (setf (managed-svref full-managed-array full-index)
		 (managed-svref value-managed-array-2 j))))
	    finally
	      (make-sparse-vector-exact-size
		value-array-1 index-array-1 sparse-index value-array-length)))))

(defun g2-integer-sparse-multiply
       (value-array-1 index-array-1 value-array-2 index-array-2 full-array
	begin-index-1 end-index-1 begin-index-2 end-index-2
	full-array-initialized?)
  (when (not full-array-initialized?)
    (g2-integer-sparse-scatter 
      value-array-2 index-array-2 full-array begin-index-2 end-index-2))
  (with-sparse-and-full-vector
    (value-array-1 index-array-1 full-array begin-index-1 end-index-1)
    (loop with value
	  with product = 0
	  for j from begin-index-1 to end-index-1
	  as full-index = (managed-svref index-managed-array j)
	  do
      (check-sparse-index-exceeds-full-length full-index n full-array)
      (setq value (managed-svref full-managed-array full-index))
      (when (/=f value 0)
	(setq product
	      (+f product (*f value (managed-svref value-managed-array j)))))
	  finally
	    (when (not full-array-initialized?)
	      (loop with index-managed-array-2 = (managed-g2-array index-array-2)
		    for j from begin-index-2 to end-index-2
		    do
		(setf (managed-svref full-managed-array
				     (managed-svref index-managed-array-2 j))
		      0)))
	    (return (make-evaluation-integer product)))))

(defun g2-float-sparse-scatter 
       (value-array index-array full-array begin-index end-index)
  (with-sparse-and-full-vector
    (value-array index-array full-array begin-index end-index)
    (loop for j from begin-index to end-index
	  as full-index = (managed-svref index-managed-array j)
	  do
      (check-sparse-index-exceeds-full-length full-index n full-array)
      (mutate-managed-float-array
	full-managed-array full-index
	(managed-float-aref value-managed-array j)))))

(defun g2-float-sparse-gather (value-array index-array full-array)
  (with-sparse-and-full-vector
    (value-array index-array full-array)
    (loop with sparse-index = 0
	  with value-array-length = l
	  with boxed-zero = (allocate-managed-float 0.0d0)
	  for j from 0 below n
	  do
      (when (/=e (managed-float-aref full-managed-array j) 
		 (managed-float-value boxed-zero))
	(when (not (<f sparse-index value-array-length))
	  (multiple-value-setq
	    (value-array-length value-managed-array index-managed-array)
	    (extend-sparse-vector-as-necessary
	      value-array index-array sparse-index value-array-length)))
	(mutate-managed-float-array
	  value-managed-array sparse-index (managed-float-aref full-managed-array j))
	(setf (managed-svref index-managed-array sparse-index) j)
	(mutate-managed-float-array 
	  full-managed-array j (managed-float-value boxed-zero))
	(setq sparse-index (+f sparse-index 1)))
      finally
	(make-sparse-vector-exact-size
	  value-array index-array sparse-index value-array-length))))

(defun g2-float-sparse-add 
       (value-array-1 index-array-1 value-array-2 index-array-2 full-array alpha
	begin-index-1 end-index-1 begin-index-2 end-index-2
	full-array-initialized?)
  (when (not full-array-initialized?)
    (g2-float-sparse-scatter 
      value-array-2 index-array-2 full-array begin-index-2 end-index-2))
  (with-sparse-and-full-vector
    (value-array-1 index-array-1 full-array begin-index-1 end-index-1)
    (let* ((value-box (allocate-managed-float-box))
	   (boxed-zero (allocate-managed-float 0.0d0))
	   (l2 (check-array-lengths-compatible 
		 value-array-2 index-array-2))
	   (max-index-2 (-f l2 1)))
      (check-index-within-bounds begin-index-2 max-index-2)
      (check-index-within-bounds end-index-2 max-index-2)
      (loop for j from begin-index-1 to end-index-1
	    as full-index = (managed-svref index-managed-array j)
	    do
	(check-sparse-index-exceeds-full-length full-index n full-array)
	(mutate-managed-float-value
	  value-box (managed-float-aref full-managed-array full-index))
	(when (/=e (managed-float-value value-box) 
		   (managed-float-value boxed-zero))
	  (mutate-managed-float-array 
	    value-managed-array j
	    (+e (managed-float-aref value-managed-array j)
		(*e alpha (managed-float-value value-box))))
	  (mutate-managed-float-array
	    full-managed-array full-index 
	    (managed-float-value boxed-zero))))
      (loop with index-managed-array-2 = (managed-g2-array index-array-2)
	    with value-managed-array-2 = (managed-g2-array value-array-2)
	    with value-array-length = l
	    with sparse-index = value-array-length
	    for j from begin-index-2 to end-index-2 
	    as full-index = (managed-svref index-managed-array-2 j)
	    do
	(check-sparse-index-exceeds-full-length full-index n full-array)
	(mutate-managed-float-value
	  value-box (managed-float-aref full-managed-array full-index))
	(cond
	  ((/=e (managed-float-value value-box) 
		(managed-float-value boxed-zero))
	   (when (not (<f sparse-index value-array-length))
	     (multiple-value-setq
	       (value-array-length value-managed-array index-managed-array)
	       (extend-sparse-vector-as-necessary
		 value-array-1 index-array-1 sparse-index value-array-length)))
	   (mutate-managed-float-array
	     value-managed-array sparse-index 
	     (*e alpha (managed-float-value value-box)))
	   (setf (managed-svref index-managed-array sparse-index) full-index)
	   (when (not full-array-initialized?)
	     (mutate-managed-float-array
	       full-managed-array full-index 
	       (managed-float-value boxed-zero)))
	   (setq sparse-index (+f sparse-index 1)))
	  (full-array-initialized?
	   (mutate-managed-float-array
	     full-managed-array full-index 
	     (managed-float-aref value-managed-array-2 j))))
	    finally
	      (make-sparse-vector-exact-size
		value-array-1 index-array-1 sparse-index value-array-length))
      (reclaim-managed-float boxed-zero)
      (reclaim-managed-float value-box))))


(defun g2-float-sparse-multiply
       (value-array-1 index-array-1 value-array-2 index-array-2 full-array
	begin-index-1 end-index-1 begin-index-2 end-index-2
	full-array-initialized?)
  (when (not full-array-initialized?)
    (g2-float-sparse-scatter 
      value-array-2 index-array-2 full-array begin-index-2 end-index-2))
  (with-sparse-and-full-vector
    (value-array-1 index-array-1 full-array begin-index-1 end-index-1)
    (loop with value-box = (allocate-managed-float-box)
	  with product-box = (allocate-managed-float 0.0d0)
	  with boxed-zero = (allocate-managed-float 0.0d0)
	  for j from begin-index-1 to end-index-1
	  as full-index = (managed-svref index-managed-array j)
	  do
      (check-sparse-index-exceeds-full-length full-index n full-array)
      (mutate-managed-float-value 
	value-box (managed-float-aref full-managed-array full-index))
      (when (/=e (managed-float-value value-box) 
		 (managed-float-value boxed-zero))
	(mutate-managed-float-value
	  product-box (+e (managed-float-value product-box)
			(*e (managed-float-value value-box)
			    (managed-float-aref value-managed-array j)))))
	  finally
	    (when (not full-array-initialized?)
	      (loop with index-managed-array-2 = (managed-g2-array index-array-2)
		    for j from begin-index-2 to end-index-2
		    do
		(mutate-managed-float-array
		  full-managed-array (managed-svref index-managed-array-2 j) 
		  (managed-float-value boxed-zero))))
	    (reclaim-managed-float value-box)
	    (reclaim-managed-float boxed-zero)
	    (return product-box))))


(defun g2-quantity-sparse-scatter 
       (value-array index-array full-array begin-index end-index)
  (with-sparse-and-full-vector
    (value-array index-array full-array begin-index end-index)
    (loop with j = begin-index
	  with full-index
	  do
      (setq j (do-for-array-elements (j (+f end-index 1))
		(setq full-index (managed-svref index-managed-array j))
		(check-sparse-index-exceeds-full-length full-index n full-array)
		(set-quantity-element
		  full-managed-array full-index
		  (get-quantity-element value-managed-array j))))
	  while j)))



(defun g2-quantity-sparse-gather (value-array index-array full-array)
  (with-sparse-and-full-vector
      (value-array index-array full-array)
    (loop with sparse-index = 0
	  with value-array-length = l
	  with value-box = (allocate-managed-float-box)
	  with integer-array? = (frame-of-class-p full-array 'integer-array)
	  with j = 0
	  do
      (setq j (do-for-array-elements (j n)
		(mutate-managed-float-value 
		  value-box (get-quantity-element full-managed-array j))
		(when (/=e (managed-float-value value-box) 0.0)
		  (when (not (<f sparse-index value-array-length))
		    (multiple-value-setq
			(value-array-length value-managed-array index-managed-array)
		      (extend-sparse-vector-as-necessary
			value-array index-array sparse-index value-array-length)))
		  (set-quantity-element 
		    value-managed-array sparse-index (managed-float-value value-box))
		  (setf (managed-svref index-managed-array sparse-index) j)
		  (if integer-array?
		      (set-quantity-element full-managed-array j 0)
		      (set-quantity-element full-managed-array j 0.0)) 
		  (setq sparse-index (+f sparse-index 1)))))
	  while j
	  finally
	    (reclaim-managed-float value-box)
	    (make-sparse-vector-exact-size
	      value-array index-array sparse-index value-array-length))))

(defun g2-quantity-to-integer-sparse-gather (value-array index-array full-array)
  (with-sparse-and-full-vector
      (value-array index-array full-array)
    (loop with sparse-index = 0
	  with value-array-length = l
	  for j from 0 below n
	  as value = (evaluation-value-value (managed-svref full-managed-array j))
	  do
      (unless (fixnump value)
	(stack-error cached-top-of-stack "~a is not a valid value for an integer array " value))
      (when (/=f value 0)
	(when (not (<f sparse-index value-array-length))
	  (multiple-value-setq
	      (value-array-length value-managed-array index-managed-array)
	    (extend-sparse-vector-as-necessary
	      value-array index-array sparse-index value-array-length)))
	(integer-set-sparse-and-clear-full
	  value-managed-array index-managed-array full-managed-array
	  value sparse-index j)
	(setq sparse-index (+f sparse-index 1)))
	  ;; while j ;; this is always true, why added? --binghe
	  finally
	    (make-sparse-vector-exact-size
	      value-array index-array sparse-index value-array-length))))

(defun g2-quantity-sparse-add 
    (value-array-1 index-array-1 value-array-2 index-array-2 full-array alpha
		   begin-index-1 end-index-1 begin-index-2 end-index-2
		   full-array-initialized?)
  (when (not full-array-initialized?)
    (g2-quantity-sparse-scatter
      value-array-2 index-array-2 full-array begin-index-2 end-index-2))
  (with-sparse-and-full-vector
      (value-array-1 index-array-1 full-array begin-index-1 end-index-1)
    (let* ((value-box (allocate-managed-float-box))
	   full-index
	   (l2 (check-array-lengths-compatible 
		 value-array-2 index-array-2))
	   (max-index-2 (-f l2 1)))
      (check-index-within-bounds begin-index-2 max-index-2)
      (check-index-within-bounds end-index-2 max-index-2)
      (loop with j = begin-index-1
	    do
	(setq j (do-for-array-elements (j (+f end-index-1 1))
		  (setq full-index (managed-svref index-managed-array j))
		  (check-sparse-index-exceeds-full-length full-index n full-array)
		  (mutate-managed-float-value
		    value-box (get-quantity-element full-managed-array full-index))
		  (when (/=e (managed-float-value value-box) 0.0)
		    (set-quantity-element
		      value-managed-array j
		      (+e (get-quantity-element value-managed-array j)
			  (*e alpha (managed-float-value value-box))))
		    (set-quantity-element
		      full-managed-array full-index 0.0))))
	    while j)
      (loop with index-managed-array-2 = (managed-g2-array index-array-2)
	    with value-managed-array-2 = (managed-g2-array value-array-2)
	    with value-array-length = l
	    with sparse-index = value-array-length
	    with integer-array? = (frame-of-class-p full-array 'integer-array)
	    with j = begin-index-2
	    do
	(setq j (do-for-array-elements (j (+f end-index-2 1))
		  (setq full-index (managed-svref index-managed-array-2 j))
		  (check-sparse-index-exceeds-full-length full-index n full-array)
		  (mutate-managed-float-value
		    value-box (get-quantity-element full-managed-array full-index))
		  (cond
		    ((/=e (managed-float-value value-box) 0.0)
		     (when (not (<f sparse-index value-array-length))
		       (multiple-value-setq
			   (value-array-length value-managed-array index-managed-array)
			 (extend-sparse-vector-as-necessary
			   value-array-1 index-array-1 sparse-index value-array-length)))
		     (set-quantity-element
		       value-managed-array sparse-index 
		       (*e alpha (managed-float-value value-box)))
		     (setf (managed-svref index-managed-array sparse-index) full-index)
		     (when (not full-array-initialized?)
		       (if integer-array?
			   (set-quantity-element full-managed-array full-index 0)   
			   (set-quantity-element full-managed-array full-index 0.0)))
		     (setq sparse-index (+f sparse-index 1)))
		    (full-array-initialized?
		     (set-quantity-element 
		       full-managed-array full-index
		       (get-quantity-element value-managed-array-2 j))))))
	    while j
	    finally
	      (make-sparse-vector-exact-size
		value-array-1 index-array-1 sparse-index value-array-length))
      (reclaim-managed-float value-box))))


(defun g2-quantity-sparse-multiply
    (value-array-1 index-array-1 value-array-2 index-array-2 full-array
		   begin-index-1 end-index-1 begin-index-2 end-index-2
		   full-array-initialized?)
  (when (not full-array-initialized?)
    (g2-quantity-sparse-scatter 
      value-array-2 index-array-2 full-array begin-index-2 end-index-2))
  (with-sparse-and-full-vector
      (value-array-1 index-array-1 full-array begin-index-1 end-index-1)
    (loop with value-box = (allocate-managed-float-box)
	  with product-box = (allocate-managed-float 0.0d0)
	  with integer-array? = (frame-of-class-p full-array 'integer-array)
	  with full-index
	  with j = begin-index-1
	  do
      (setq j (do-for-array-elements (j (+f end-index-1 1))
		(setq full-index (managed-svref index-managed-array j))
		(check-sparse-index-exceeds-full-length full-index n full-array)
		(mutate-managed-float-value 
		  value-box (get-quantity-element full-managed-array full-index))
		(when (/=e (managed-float-value value-box) 0.0)
		  (mutate-managed-float-value
		    product-box (+e (managed-float-value product-box)
				    (*e (managed-float-value value-box)
					(get-quantity-element value-managed-array j)))))))
	  while j
	  finally
	    (when (not full-array-initialized?)
	      (loop with index-managed-array-2 = (managed-g2-array index-array-2)
		    with j = begin-index-2
		    do
		(setq j (do-for-array-elements (j (+f end-index-2 1))
			  (if integer-array?
			      (set-quantity-element
				full-managed-array (managed-svref index-managed-array-2 j) 0)
			      (set-quantity-element
				full-managed-array (managed-svref index-managed-array-2 j) 0.0))))
		    while j))
	    (reclaim-managed-float value-box)
	    (return product-box))))



(defvar result-index)

(defun zero-length-sparse-vector-error (value-array)
  (stack-error
    cached-top-of-stack
    "The value vector ~NF is of length 0 and is therefore not suitable for the current operation."
    value-array))

(defun integer-accumulation-for-sparse-min (accumulation value-array j)
  (let ((value (managed-svref value-array j)))
    (cond 
      ((or (null accumulation) 
	   (<f value accumulation))
       (setq result-index j)
       value)
      (t
       accumulation))))

(defun integer-accumulation-for-sparse-max (accumulation value-array j)
  (let ((value (managed-svref value-array j)))
    (cond
      ((or (null accumulation) 
	   (>f value accumulation))
       (setq result-index j)
       value)
      (t
       accumulation))))

(defun integer-accumulation-for-sparse-sum (accumulation value-array j)
  (+f accumulation (managed-svref value-array j)))

(defun integer-accumulation-for-sparse-sum-abs (accumulation value-array j)
  (+f accumulation (absf (managed-svref value-array j))))

(defun float-accumulation-for-sparse-min (accumulation value-array j)
  (cond
    ((null accumulation)
     (setq result-index j)
     (setq accumulation
	   (allocate-managed-float (managed-float-aref value-array j))))
    ((<e (managed-float-aref value-array j) (managed-float-value accumulation))
     (setq result-index j)
     (mutate-managed-float-value accumulation (managed-float-aref value-array j))))
  accumulation)

(defun float-accumulation-for-sparse-max (accumulation value-array j)
  (cond
    ((null accumulation)
     (setq result-index j)
     (setq accumulation
	   (allocate-managed-float (managed-float-aref value-array j))))
    ((>e (managed-float-aref value-array j) (managed-float-value accumulation))
     (setq result-index j)
     (mutate-managed-float-value accumulation (managed-float-aref value-array j))))
  accumulation)

(defun float-accumulation-for-sparse-sum (accumulation value-array j)
  (mutate-managed-float-value 
    accumulation
    (+e (managed-float-value accumulation) (managed-float-aref value-array j)))
  accumulation)

(defun float-accumulation-for-sparse-sum-abs (accumulation value-array j)
  (mutate-managed-float-value 
    accumulation
    (+e (managed-float-value accumulation) (abse (managed-float-aref value-array j))))
  accumulation)

(defun quantity-accumulation-for-sparse-min (accumulation value-array j)
  (let ((element-value 
	  (get-quantity-element value-array j)))
    (cond
      ((null accumulation) 
       (setq result-index j)
       (setq accumulation (allocate-managed-float element-value)))
      ((<e element-value (managed-float-value accumulation))
       (setq result-index j)
       (mutate-managed-float-value accumulation element-value))))
  accumulation)

(defun quantity-accumulation-for-sparse-max (accumulation value-array j)
  (let ((element-value 
	  (get-quantity-element value-array j)))
    (cond
      ((null accumulation) 
       (setq result-index j)
       (setq accumulation (allocate-managed-float element-value)))
      ((>e element-value (managed-float-value accumulation))
       (setq result-index j)
       (mutate-managed-float-value accumulation element-value))))
  accumulation)

(defun quantity-accumulation-for-sparse-sum (accumulation value-array j)
  (let ((element-value 
	  (get-quantity-element value-array j)))
    (mutate-managed-float-value 
      accumulation (+e (managed-float-value accumulation) element-value)))
  accumulation)

(defun quantity-accumulation-for-sparse-sum-abs (accumulation value-array j)
  (let ((element-value 
	  (get-quantity-element value-array j)))
    (mutate-managed-float-value 
      accumulation (+e (managed-float-value accumulation) (abse element-value))))
  accumulation)

(defun accumulate-sparse-values (value-array initial-value? update-function)
  (let ((l (g2-array-length value-array)))
    (when (not (>f l 0))
      (zero-length-sparse-vector-error value-array))
    (loop with accumulation = initial-value?
	  with result-index = 0
	  with managed-array = (managed-g2-array value-array)
	  for j from 0 below l
	  do
      (setq accumulation
	    (funcall-simple-compiled-function
	      update-function accumulation managed-array j))
	  finally (return (values accumulation result-index)))))

(defun accumulate-quantity-sparse-values (value-array initial-value? update-function)
  (let ((l (g2-array-length value-array)))
    (when (not (>f l 0))
      (zero-length-sparse-vector-error value-array))
    (loop with accumulation = initial-value?
	  with result-index = 0
	  with managed-array = (managed-g2-array value-array)
	  with j = 0 
	  do
      (setq j (do-for-array-elements (j l)
		(setq accumulation
		      (funcall-simple-compiled-function
			update-function accumulation managed-array j))))
	  while j
	  finally (return (values accumulation result-index)))))

(defun g2-integer-sparse-min (value-array)
  (multiple-value-bind
    (result index)
      (accumulate-sparse-values
	value-array nil #'integer-accumulation-for-sparse-min)
    (values (make-evaluation-integer result)
	    (make-evaluation-integer index))))

(defun g2-integer-sparse-max (value-array)
  (multiple-value-bind
    (result index)
      (accumulate-sparse-values
	value-array nil #'integer-accumulation-for-sparse-max)
    (values (make-evaluation-integer result)
	    (make-evaluation-integer index))))

(defun g2-integer-sparse-sum (value-array)
  (make-evaluation-integer
    (accumulate-sparse-values
      value-array 0 #'integer-accumulation-for-sparse-sum)))

(defun g2-integer-sparse-sum-abs (value-array)
  (make-evaluation-integer
    (accumulate-sparse-values
      value-array 0 #'integer-accumulation-for-sparse-sum-abs)))

(defun g2-float-sparse-min (value-array)
  (multiple-value-bind
    (result index)
      (accumulate-sparse-values
	value-array nil #'float-accumulation-for-sparse-min)
    (values result (make-evaluation-integer index))))

(defun g2-float-sparse-max (value-array)
  (multiple-value-bind
    (result index)
      (accumulate-sparse-values
	value-array nil #'float-accumulation-for-sparse-max)
    (values result (make-evaluation-integer index))))

(defun g2-float-sparse-sum (value-array)
  (accumulate-sparse-values
    value-array (allocate-managed-float 0.0d0) #'float-accumulation-for-sparse-sum))

(defun g2-float-sparse-sum-abs (value-array)
  (accumulate-sparse-values
    value-array (allocate-managed-float 0.0d0) #'float-accumulation-for-sparse-sum-abs))

(defun g2-quantity-sparse-min (value-array)
  (multiple-value-bind
    (result index)
      (accumulate-quantity-sparse-values
	value-array nil #'quantity-accumulation-for-sparse-min)
    (values result (make-evaluation-integer index))))

(defun g2-quantity-sparse-max (value-array)
  (multiple-value-bind
    (result index)
      (accumulate-quantity-sparse-values
	value-array nil #'quantity-accumulation-for-sparse-max)
    (values result (make-evaluation-integer index))))

(defun g2-quantity-sparse-sum (value-array)
  (accumulate-quantity-sparse-values
    value-array (allocate-managed-float 0.0d0)
    #'quantity-accumulation-for-sparse-sum))

(defun g2-quantity-sparse-sum-abs (value-array)
  (accumulate-quantity-sparse-values
    value-array (allocate-managed-float 0.0d0)
    #'quantity-accumulation-for-sparse-sum-abs))



(declare-system-procedure-function g2-array-min t)

(defun-funcallable g2-array-min (value-array)
  (execute-sparse-vector-operation-according-to-type
    value-array 
    #'g2-integer-sparse-min
    #'g2-float-sparse-min
    #'g2-quantity-sparse-min))

(declare-system-procedure-function g2-array-max t)

(defun-funcallable g2-array-max (value-array)
  (execute-sparse-vector-operation-according-to-type
    value-array 
    #'g2-integer-sparse-max
    #'g2-float-sparse-max
    #'g2-quantity-sparse-max))

(declare-system-procedure-function g2-array-sum t)

(defun-funcallable g2-array-sum (value-array)
  (execute-sparse-vector-operation-according-to-type
    value-array 
    #'g2-integer-sparse-sum
    #'g2-float-sparse-sum
    #'g2-quantity-sparse-sum))

(declare-system-procedure-function g2-array-sum-abs t)

(defun-funcallable g2-array-sum-abs (value-array)
  (execute-sparse-vector-operation-according-to-type
    value-array 
    #'g2-integer-sparse-sum-abs
    #'g2-float-sparse-sum-abs
    #'g2-quantity-sparse-sum-abs))

(defun execute-sparse-vector-operation-according-to-type 
    (value-array 
      integer-case-function float-case-function quantity-case-function)
  (let (value index)
    (with-temporary-gensym-float-creation execute-sparse-vector-operation
      (cond 
	((frame-of-class-p value-array 'integer-array)
	 (multiple-value-setq
	     (value index)
	   (funcall-simple-multi-valued-compiled-function
	     integer-case-function value-array)))
	((frame-of-class-p value-array 'float-array)
	 (multiple-value-setq
	     (value index)
	   (funcall-simple-multi-valued-compiled-function
	     float-case-function value-array)))
	((frame-of-class-p value-array 'quantity-array)					; quantity arrays case
	 (multiple-value-setq
	     (value index)
	   (funcall-simple-multi-valued-compiled-function
	     quantity-case-function value-array)))
	(t
	 (stack-error cached-top-of-stack
		      "~a must be an integer, quantity or float array" value-array))))
    (values value index)))


(declare-system-procedure-function g2-sparse-get t)

(defun-funcallable g2-sparse-get (value-array index-array index)
  (unless (and (g2-array-p value-array)
		 (g2-array-p index-array))
      (stack-error
	cached-top-of-stack
	"value-array and index-arraymust all  arrays"))
  (unless (evaluation-integer-p index)
    (stack-error
      cached-top-of-stack
      "Index must be an integer"))
  (with-temporary-gensym-float-creation g2-sparse-get
    (setq index (evaluation-value-value index))
    (loop with index-managed-array = (managed-g2-array index-array)
	  with integer-array? = (frame-of-class-p value-array 'integer-array)
	  with float-array? =  (frame-of-class-p value-array 'float-array)
	  for j from 0 below (check-array-lengths-compatible 
			       value-array index-array)
	  do
      (when (=f (managed-svref index-managed-array j) index)
	(cond 
	  (integer-array?
	   (return (managed-svref (managed-g2-array value-array) j)))
	  (float-array?
	   (return (make-evaluation-float
		     (managed-float-aref (managed-g2-array value-array) j))))
	  (t					       ; quantity arrays case
	   (return (make-evaluation-float
		     (get-quantity-element (managed-g2-array value-array) j))))))
	  finally (return
		    (cond (integer-array?
			   (make-evaluation-integer 0))
			  (float-array?
			   (make-evaluation-float 0.0d0))
			  (t
			   (make-evaluation-quantity 0)))))))

(declare-system-procedure-function g2-sparse-set t)

(defun-funcallable g2-sparse-set (value-array index-array value index)
  (with-temporary-gensym-float-creation g2-sparse-set
    (let (current-sparse-length
	   index-managed-array 
	   value-of-value 
	   sparse-index
	   index-value)
      (setq index-value (evaluation-value-value index))
      (cond ((not (evaluation-quantity-p value))
	     (stack-error cached-top-of-stack
			  "g2-sparse-set requires a quantity not ~a" (evaluation-value-value value)))
	    ((or (not (fixnump index-value))
		 (minusp index-value))
	     (stack-error cached-top-of-stack
			  "The provided index ~a is not a positive integer" index-value))
	    ((not (and (g2-array-p value-array)
		       (g2-array-p index-array)))
	     (stack-error cached-top-of-stack
			  "Both the value and the index arrays must be arrays"))
	    ((or (=f (g2-array-length value-array) 0)
		 (=f (g2-array-length index-array) 0))
	     (stack-error cached-top-of-stack
			  "Both the value and the index arrays must have non-zero length"))
	    (t
	     (setq current-sparse-length (check-array-lengths-compatible value-array index-array))
	     (setq value-of-value (evaluation-value-value value))
	     (setq index-managed-array (managed-g2-array index-array))
	     (reclaim-evaluation-value value)
	     (reclaim-evaluation-value index)

	     (loop for i from 0 below current-sparse-length do
	       (when (=f (managed-svref index-managed-array i) index)
		 (setq sparse-index i)
		 (return))
		   finally
		     (setq sparse-index current-sparse-length)
		     (change-sparse-vector-length 
		       value-array index-array (+f sparse-index 1))
		     (setf (managed-svref
			     (managed-g2-array index-array)
			     sparse-index)
			   index-value))
	     (cond 
	       ((frame-of-class-p value-array 'integer-array)
		(cond ((fixnump value-of-value)
		       (setf (managed-svref (managed-g2-array value-array) sparse-index)
			     value-of-value))
		      (t
		       (stack-error
			 cached-top-of-stack
			 "Trying to put a non integer value ~a into an integer array " value-of-value))))
	       ((frame-of-class-p value-array 'float-array)
		(mutate-managed-float-array
		  (managed-g2-array value-array) sparse-index
		  (if (fixnump value-of-value)
		      (coerce-to-gensym-float value-of-value)
		      value-of-value)))
	       (t					       ; quantity arrays case
		(set-quantity-element
		  (managed-g2-array value-array) sparse-index value-of-value))))))))



;;;; Alignment Hack

;;; The following alignment hack can be used to improve the appearance of
;;; knowledge bases.  It should be used in conjunction with kb procedures like
;;; align-objects in "ma:>agh>matrix-tests-30.kb".  To use, start, run the
;;; align-objects procedure, then run fix-item-position.

;;; This can go away when we have a way of removing kb state changes in G2 (some
;;; sort of make-permanent option).

#+development
(defun fix-items-on-workspace (workspace class)
  (loop for x being each subblock of workspace do
    (when (of-class-p x class)
      (remove-kb-state-variable-record x 'item-position))))





;;;; Testing 

;;; Test kbs and player files are:
;;;   (on ma:>ab) - flow, control-sim, sc-power, paper, distiller, xs_exam1, xs_exam2
;;;   (on ma:>agh) - sim-test-30, sim-formulas-30, sim-formulas-30-1, sim-circuits, 
;;;                  multiple-models-run-test, matrix-tests-30, cogenerator-5
;;;   (on ma:>player-tests) - simulation-installation-1.lisp
;;;   (on ma:>agh) - simulation-installation-2.kb
;;;   (on ma:>agh>sim-solve) - matrix-tests-30.lisp
;;;   (on ma:>agh>sim-comp) - many-carts.kb, many-adders.kb
;;;   (on ma:>agh) - procedure-speed-test.kb
;;;   ma:>agh>simulation-ordering-loops

;;; Note that due to Ben's changes to clone and create, the player files have to
;;; be updated!  Also, Ben has added a push and pop of mouse position (see head of
;;; utilities for doc).



;;; Testing of Model Installation and Running

;;; Use ma:>player-tests>simulation-installation-1 to test model installation.

;;; Use ma:>agh>multiple-models-run-test.kb to test running of multiple models.
;;; Build player file around this.  It is useful to look at the model queues to
;;; verify that the correct models are running.  Also, check
;;; shortest-time-increment-for-models-in-queue as models are being added and
;;; deleted.

;;; Start.  Main model should be running, model-a and model-t not.

;;; Start model-a and model-t using action buttons.  Do in different orders.
;;; do several times.

;;; Reset.

;;; Start, start model-a, model-t.  Reset model-a, model-t in different orders.



;;; Testing of Expanded Grammar for Simulation Formulas

;;; Loaded the following kbs to test that loading (installation) speed was
;;; reasonable:
;;; ma:>ab>control-sim, flow,
;;; ma:>agh>sim-circuits, sim-test-30, sim-formulas-30-1

;;; The player file ma:>player-test>simulation-installation-2 tests simulation
;;; formulas with the new grammar.  Note that describing variables and parameters
;;; is also a useful way of checking that they have been installed correctly for
;;; simulation.  Also "ma:>agh>sim-formulas-30-1.kb" (the kb which the player
;;; loads) now contains a test-display workspace which indicates whether the
;;; simulation installation is correct.



;;;; To Do for Matrix System Procedures

;; Return error code for errors in LU
;; decomposition routine, it actually avoids a singularity by replacing 0 with
;; tiny.  It would probably be better to flag this as an error.  Alternatively, an
;; arg could control this.  For error code, consider returning index of row it was
;; working on.  For error codes, use tagbodies for easy exit (see stack-eval).

;; If time, put allow other processing in.  Have this controllable by arg, or by
;; global variable.  Note that it will be difficult to add arguments to system
;; procedures in the future, unless we implement optional arguments.

;; Test non-square cases thoroughly.

;; Complex numbers (represent as two element float arrays).

;; Review temporary float creation.

;; In LU decomposition, check whether allocating a managed float array has a 
;; significant impact on performance (probably not).

;; Should LU decomposition also return determinant 
;; Do singular value decomposition?  - possibly for the future





;;;; To Do

;; - make sure that variables from other models just return their values.

;; Review history functions with Chris.  These are still returning 
;; multiple values in some cases.  Review use-simulated-histories.

;; Make sure this works with "item" focal classes
;; "the level of tank1" vs. "the level of any tank".

;; Finish testing system procedures to get and set a model's time increment and
;; simulation time itself.  Get to documentation.  Do this as part of rewrite of
;; control-sim.kb.

;; Need to test GSPAN with multiple models.  Make demo with SPEEDUP.

;; Make use of simulation-error slot of model-runtime-info.  Consider
;; incorporating into simulation-status slot.  Allow user to access these (this is
;; probably better than constantly making functions for user access).  Eventually,
;; consider using error signalling mechanism for models.  Could do in manner
;; similar to system procedure for warmboot.  Start procedure would not return but
;; rather, would allow other processing.  This could also call
;; simulate-until-consistent...  The stop procedure would cause this one to
;; finish.  In this way, any simulation errors could be passed on to the general
;; error handling scheme.  Test all stack-error cases and convert appropriate
;; warning messages to stack-error.
;; Error handling -
;; Review all error messages in simulator and convert to stack-error
;; if appropriate.
;; Switch all current simulation error messages to use simulation-error?
;; mechanism.  Review. 

;; Search with-current-model.

;; Fix pausing of simulator.  When resuming, just update time.

;; Review simulation of non-quantitative variables and parameters.

;; Review dependent variables which get their values from externally simulated
;; ones.

;; Review external-simulator-init-completed.



;; Lower Priority

;; Speed improvements

;; In compilation for generic-simulation-formulas, use
;; type-specification-of-designation-p to specify type of time when possible for
;; cached bindings.

;; Flag error as soon as simulation-no-value is encountered.  Don't even store it
;; if this can be avoided.

;; Review all the number-p checks in euler and rk4 integration routines.
;; Try to reduce by trapping error earlier.

;; Test cases - include ones that exercise ordering loops issue.

;; Optimizations to mechanism that deals with 
;; variables-that-need-simulated-values
;; 1.  Save stack program counter so that variables already evaluated 
;; aren't evaluated again.
;; 2.  Change order of variables (unless it was an ordering loop).

;; Tracing and breakpoints.
;; Review write-simulation-formula-trace-entry, add specific simulation formula
;; stuff, make sure consistent with what is written for rules.

;; Test to make sure that nil is put into simulation-environment-vector 
;; cached bindings if binding designation fails.

;; Don't put nil as car of box-translation-and-text (I think this is a problem
;; with specific simulation formulas, bad compiles). (separate issue)

;; Check to make sure that no ordering problems in kbs that shouldn't
;; have any.  This can be easily checked for by breaking in
;; handle-simulator-stack-error (when initializing-simulator?  is not
;; true).

;; A good way to disable the sorting is to comment out the body of
;; note-supporting-variables.  This is useful for testing the
;; variables-that-need-simulated-values stack which can be observed from
;; calculate-new-value-for-one-dependent-variable.





;; After 3.0

;; Eventually allow vectors of synchronous and as fast as possible model queues,
;; one for each priority.  The queues are needed to control synchronization so it
;; is not possible to just get rid of the queues and let the scheduler handle this
;; stuff.

;; Eventually, implement model groups, to be run together synchronously.  These
;; are what should be called by the scheduler.

;; Eventually, consider implementing something like call-model (as opposed to just
;; start-model).  Consider including option to call just one object in a model.

;; Simplify data service.

;; Flatten out simulation-info structure by folding in
;; variable-simulation-runtime-structure.  This will save one pointer indirection.

;; Improve doc for slots of model-runtime-info.  This is currently spread out.

;; Consider implementing a simple tearing style solver.  If algebraic loops
;; encountered, it chooses an optimal tear set and informs the user of torn
;; variables.  Could also highlight tear paths.  Lotus 123 G has such a solving
;; feature.  They call this goal-seeking.  The latest version of EXCEL has it as
;; well.

;; Review Documentation.

;; Review how args are passed in simulator.  See if some of this can
;; be streamlined, possibly with special vars.

;; Make a tree, similar to Jim's evaluation trees, for showing evaluation status
;; in the simulator.



;; Expanded grammar for generic simulation formulas:

;; for any <entity> <bindings> <formula-list>

;; <bindings> : [where <local-name> is <designation>, ...]
;; <formula-list> : <left-side-designation> = <unique-expression>

;; <left-side-designation> is a designation that contains only roles
;; that can be inverted (for installation purposes).  It can also 
;; be one of the local names in bindings as long as the designation
;; for the local name contains only invertible roles.

;; Ex.
;; For any tank
;; where x1 is the level of the tank, 
;;       x2 is the volume of the tank,
;;       x3 is the area of the tank,
;; x2 = x1 * x3

;; Note that this is not true equation grammar yet; it is still in assignment or
;; formula form.  True equation grammar will come later.

;; Each formula in the formula list should be compiled separately, with each
;; compilation containing only those local variable bindings needed for that
;; formula.  The compiled formulae should go into a managed array so that they
;; can be accessed quickly.  When installing the generic simulation formula into
;; the simulation-info structure of a variable, an index number for accessing the
;; correct formula in this array should be stored as well.




;;;; Notes on Models

;; The installation is currently done at all times, even if the simulator is not
;; running.  Note that the only inefficient part of this installation is the need
;; to check if the class is a subclass of one of the classes in the
;; items-belonging-to-this-model slot.  This can be improved by noting the
;; model-definition in the model-definitions-for-item-or-class property of all
;; subclasses of a class.  I have discussed this with Jim as well.  This sort of
;; search is a problem in other parts of the product as well (chaining analysis
;; for example).

;; Consider adding an accuracy-requirements slot to both model-definition and
;; simulation-parameters.

;; Need to review issues of communication between models.  Just use existing
;; values.








;;;; Notes on Stack Evaluator and Simulator

;; byte-code-body  (see UTILITIES4)
;; - has slots:
;; length, byte-vector, constant-vector, environment-description,
;; byte-code-body-free-references
;; Use byte-vector-aref to access stuff in byte-vector.
;; Byte-code-body-free-references used for consistency analysis.

;; Byte-code-bodies are slot values.

;; Describe is set up in development to show stack disassembles for
;; generic-simulation-formulas.

;; Environment vector has following format:
;; element 0 - need-to-recache?  - take out of simulation-info
;; element 1 - result of stack-eval
;; element 2 - focal class if one exists
;; The rest of the elements, from 3 on if there is a focal class,
;; or from 2 on if there isn't, contain bindings.








;;;; Speed Test Results for Stack Evaluator

;; Using ma:>agh>sim-comp>many-carts.kb:  (on micro-explorer)

;; old evaluator - 33 sec. simulated in 101 sec real time
;; new evaluator - 17 sec. simulated in 105 sec real time

;; Thus, the new evaluator was about half as fast.

;; With performance metering:

;; with meter-microsecond-performance around sim-eval-top in old
;; evaluator, indicated 45%

;; with meter-microsecond-performance around sim-eval-for-stack in new
;; evaluator, indicated 60%

;; Thus, a significant part of the slow-down is related to the stack evaluator.
;; Given that in the old evaluator, it took .45 seconds in sim-eval-top to do 1
;; second of simulated time, and that in the new evaluator, it took 2 X .60
;; seconds = 1.20 seconds in sim-eval-for-stack to do 2 seconds of simulated time,
;; it seems that the evaluation part itself has slowed down by 2.66 seconds.

;; Something else outside of stack-evaluation seems to have slowed down as well
;; though.  Given that in the old evaluator, it took 0.55 seconds outside of
;; sim-eval-top to do 1 second of simulated time, and that in the new evaluator,
;; it took 2 X .40 = .80 seconds outside of sim-eval-for-stack to do 1 second of
;; simulated time, something else has gotten 1.45 times slower.

;; Using ma:>agh>sim-comp>many-adders.kb:

;; old-evaluator - 10 sec. simulated in 41 sec real time
;; new-evaluator - 10 sec. simulated in 50 sec real time

;; I did an interesting experiment with performance metering to see how much
;; overhead there was to entering and exiting sim-eval-for-stack vs.  executing
;; the stack instructions.  I repeated the experiment using the new stack
;; evaluator on ma:>agh>sim-comp>many-carts.kb.  Wrapping
;; meter-microsecond-performance inside stack-eval indicated 30% time, vs.  the
;; 60% when it was wrapped around sim-eval-for-stack.

;; I also did a test using ma:>agh>procedure-speed-test.kb.  The old evaluator
;; took 450 seconds to complete and the new evaluator took 179 seconds to
;; complete.  The new evaluator is thus 2.5 times faster in this test.

;; 7/8/91
;; After fixing the ordering bug, I repeated the many-carts test and this time
;; was able to do 24 sec. simulated in 103 sec real - an improvement.

;; 7/31/91
;; After implementing mechanism for evaluating several variables within stack-eval,
;; speed is up to 30 sec. simulated in 100 sec real for the many-carts test.  This
;; is an improvement, but it still isn't faster than 2.1.



;; 2/19/92
;; Have done some more improvements, but still not up to 2.1 speed.  Did
;; some quick estimates though.  Jim says that his tests indicate that
;; stack instructions can be as fast as 7 micro-seconds.  Let's assume,
;; for the moment, that this is an average.  Analysis of the control
;; block formula compilations indicates that they contain between 12 and
;; 18 instructions (formulas with "first of the following" have been
;; replaced with formulas that check "exists").  Assuming an average of
;; 18 instructions yields 133 micro-seconds in the stack evaluator to
;; compute one variable.  Given that there are about 340 variables and
;; that the time increment is 0.5 seconds, the total number of variables
;; per simulated second is 680.  Multiplying this by the 133
;; micro-seconds yields about 0.1 seconds in the stack evaluator to
;; compute a cycle.  Taking into account non stack evaluator overhead,
;; this number is not too different from the 0.25 seconds that we are
;; seeing in test results.  Thus, it seems that we can't do that much
;; better given the current architecture.

;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module VARIABLES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin, Andreas Hofmann, Stephen R. DeVoy, Jim Allard, and Mark David




;; In histories

(declare-forward-reference get-or-make-history-buffer function)

;; In EXPLAIN

(declare-forward-reference
  update-backward-chaining-displays-function function)

(declare-forward-reference
  backward-chaining-displays variable)

;; In GRAMMAR2

(declare-forward-reference write-list-in-chicago-style function)

;; In CHAINING

(declare-forward-reference install-true-value-update function)

;; In CELLS

(declare-forward-reference make-empty-expression-cell function)

(declare-forward-reference g2-cell-array-managed-array-function function)

(declare-forward-reference g2-expression-cell-byte-code-body-function function)

;; In PROC-UTILS

(declare-forward-reference exit-computation-context-for-variable-formula function)

(declare-forward-reference schedule-computation-instance-execution function)

(declare-forward-reference var-count function)

;;; To STACK-INST

(declare-forward-reference clean-up-wake-ups-state-if-any function)

(declare-forward-reference set-wake-ups-function function)

(declare-forward-reference open-wake-up-collection-function function)

;; In STACK-UTILS

(declare-forward-reference generate-standard-error-message function)

;; In GSI

(declare-forward-reference handle-update-to-sensor-data-type function)

;; In STACK-KERN

(declare-forward-reference invoke-user-defined-default-error-handler function)

(declare-forward-reference
  registered-and-active-default-error-handler-p function)

(declare-forward-reference write-data-server-map-from-slot function)

(declare-forward-reference reclaim-cached-explanation function)  ; QUERIES

(declare-forward-reference remove-request-for-rule-instance-invocation function)

;; In ACTIVATE

(declare-forward-reference items-needing-initialization-tree variable)

;; In CHAINING-LINK

(declare-forward-reference invoke-update-functions-for-expired-value function)

;;; The global variable `stack-eval?' controls whether or not the compiler will
;;; produce compiled procedures with stack-evaluated expressions.

;; The default has been changed to leave the new evaluators on.  -jra 7/24/91

(defvar stack-eval? t)






;;;; Overview of Variables




;;; Variable is a subclass of entity.  Sensors and other g2-variables are
;;; subclasses of variable.  A variable may be asked for a current value.  If
;;; its value is not current, it will attempt to obtain the latest value.  If
;;; its value is current, it may either return it, or (if the request insists on
;;; the latest data) attempt to obtain the latest value.
;;;
;;; A variable may attempt to obtain a value by evaluating a formula or backward
;;; chaining, or if it is a sensor variable, by getting external data.  If it
;;; fails in obtaining a value, it is subject to wake-up (see eval).  A variable
;;; may also obtain its value from its simulated value.  This is typically done
;;; for simulating sensor variables, but simulations can also be entered for
;;; non-sensor variables.  When a variable receives a new value, it may wake up
;;; other variables that have requested it when there was no current value
;;; available.
;;;
;;; A variable may maintain a record of values in history tables.  The amount
;;; and type of history will vary and will be directly specified by the user.  A
;;; method for saving histories on disk will have to be implemented so that the
;;; history of a process survives that process.  A variable may have to obtain
;;; current values even when not requested in order to maintain its history.
;;; This can be done through setting the background-collection-interval? slot of
;;; a variable.
;;;
;;; Request for data and receipt of data are completely de-coupled.  Request is
;;; handled by get-current-value, receipt by put-current-value.
;;;
;;; History dependent functions such as lag, averaging, rates of change, maxima,
;;; minima, and variance, all make use of a variables history.  The user must
;;; make sure that variables that are used with these functions maintain the
;;; required histories.


;;; The code is organized in the following sections:

;;;  KB-specific symbol properties
;;;  Variable Class Definitions
;;;  Data Types
;;;  Getting Values of Variables
;;;  Receiving Values of Variables
;;;  Activate, Deactivate, and Reset Methods
;;;  Notes





;;;; KB-specific symbol properties

(def-kb-specific-property-name formulas-for-this-role)







;;; Note that the old class names `formula-statement' and
;;; `formula-for-attribute' have been replaced with the class name
;;; `generic-formula'.  Note also that `simulation-formula-for-attribute' has
;;; been replaced by `generic-simulation-formula'.

(def-substitute-for-old-class formula-statement generic-formula)
(def-substitute-for-old-class formula-for-attribute generic-formula)

(def-substitute-for-old-class simulation-formula-for-attribute
                              generic-simulation-formula)

;; Delete these in release 1.1!!


;;; The generic-formula class definition has been moved here from
;;; formulas due the use of needed accessor definitions in this file.

(def-class (generic-formula statement (foundation-class generic-formula) define-predicate)
  ;; initialize method now deals with initial setup -- this slot's init form
  ;; will now be nil, and inherited. (MHD 7/18/94)
;  (frame-status-and-notes
;    (:funcall slot-value-cons-function incomplete nil))
  (frame-author-or-authors
    nil (type authors-with-time-of-last-edit?)
    (attribute-export-comment
      "Will allow 0 or more author entries. each author entry may have a date. ~
authors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true
"))
  (frame-change-log nil (type frame-change-log))
  (box-translation-and-text nil                 ; nil or (translation . text)
     (type generic-formula text) vector-slot system select-changes))

;; The following were formerly slots.

(defmacro formula-class (generic-formula)
  `(second (car (box-translation-and-text ,generic-formula))))

(defmacro formula-role-name (generic-formula)
  `(first (car (box-translation-and-text ,generic-formula))))

(defmacro formula-role-class-qualifier (generic-formula)
  `(if (>f (length (car (box-translation-and-text ,generic-formula))) 2)
       (third (car (box-translation-and-text ,generic-formula))))
           )

(defmacro formula-role-class-qualifier-of-formula-translation (translation)
  `(if (>f (length ,translation) 2)
       (third ,translation)))


;;; The slot generic-formula-byte-code-body existed for about two weeks during
;;; 3.0 development, but was dropped in favor of using the cell array slot
;;; already on the frame.

(def-absent-slot-putter generic-formula-byte-code-body
                        (generic-formula byte-code-body)
  (declare (ignore generic-formula))
  (reclaim-slot-value byte-code-body))



(def-class-method initialize (generic-formula)
  (funcall-superior-method generic-formula)
  (unless (of-class-p (cell-array generic-formula) 'g2-cell-array)
    (let* ((current-block-of-dependent-frame generic-formula)
           (new-cell-array (make-frame 'g2-cell-array)))
      (change-slot-value
        generic-formula 'cell-array new-cell-array)
      (make-empty-expression-cell new-cell-array))))

(def-class-method cleanup (generic-formula)
  (funcall-superior-method generic-formula)
  (let ((old-role-name (formula-role-name generic-formula)))
    (when old-role-name
      (delete-from-set (formulas-for-this-role old-role-name)
                       generic-formula)))
  (without-consistency-analysis (generic-formula)
    (change-slot-value generic-formula 'cell-array nil))
  (change-slot-value generic-formula 'box-translation-and-text nil))




;;; Generic Simulation Formulas moved here from simulate due to needed
;;; accessor definitions.

;;; If a variable has specific simulation formulas, they go in the
;;; simulation-formulas? slot of the simulation frame.  These specific
;;; simulation formulas are just expressions.  Generic simulation formulas are
;;; generic-simulation-formulas and are accessed via kb-specific properties on
;;; attribute names.  Thus, simulation formulas are similar to formulas for the
;;; inference engine.  May want the capability to put specific simulation
;;; formulas in separate statements as well.

;;; At some point, it may be desireable to compile generic simulation formulas
;;; down to specific ones and install them in the appropriate slots.  This could
;;; be done in batch mode or as a caching operation at run time.

;;; A generic-simulation-formula is similar to a formula statement.

(def-class (generic-simulation-formula
             statement (foundation-class generic-simulation-formula) define-predicate)
  ;; initialize method now deals with initial setup -- this slot's init form
  ;; will now be nil, and inherited. (MHD 7/18/94)
;  (frame-status-and-notes
;    (:funcall slot-value-cons-function incomplete nil) system)
  (frame-author-or-authors
    nil (type authors-with-time-of-last-edit?)
    (attribute-export-comment
      "Will allow 0 or more author entries. each author entry may have a date. ~
authors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true
"))
  (frame-change-log nil (type frame-change-log))
  (box-translation-and-text nil                 ; nil or (translation . text)
     (type generic-simulation-formula text) vector-slot system select-changes)
  (tracing-and-breakpoints
    nil system lookup-slot save (type tracing-and-breakpoints))
  (generic-simulation-formula-byte-code-body nil vector-slot save)
  (generic-simulation-initial-value-byte-code-body nil vector-slot save))

;; Byte-code-bodies are slot values and therefore don't need reclaimers.



(defmacro simulation-class-or-item-given-translation (translation)
  `(second ,translation))

(defmacro simulation-role-given-translation (translation)
  `(first ,translation))

(defmacro compiled-simulation-formula-given-translation (translation)
  `(third ,translation))

(defmacro simulation-category-given-translation (translation)
  `(fourth ,translation))

(defmacro simulation-initial-value-given-translation (translation)
  `(fifth ,translation))

(defmacro simulation-time-increment-given-translation (translation)
  `(sixth ,translation))

(defmacro left-side-of-simulation-formula-given-translation (translation)
  `(seventh ,translation))

(defmacro simulation-formula-class-or-item (generic-simulation-formula)
  `(simulation-class-or-item-given-translation
     (car (box-translation-and-text ,generic-simulation-formula))))

(defmacro simulation-formula-role (generic-simulation-formula)
  `(simulation-role-given-translation
     (car (box-translation-and-text ,generic-simulation-formula))))

(defmacro compiled-simulation-formula (generic-simulation-formula)
  `(compiled-simulation-formula-given-translation
     (car (box-translation-and-text ,generic-simulation-formula))))

(defmacro simulation-formula-category (generic-simulation-formula)
  `(simulation-category-given-translation
     (car (box-translation-and-text ,generic-simulation-formula))))

(defmacro simulation-formula-initial-value? (generic-simulation-formula)
  `(simulation-initial-value-given-translation
     (car (box-translation-and-text ,generic-simulation-formula))))

(defmacro simulation-formula-time-increment? (generic-simulation-formula)
  `(simulation-time-increment-given-translation
     (car (box-translation-and-text ,generic-simulation-formula))))

(defmacro simulation-formula-left-side (generic-simulation-formula)
  `(left-side-of-simulation-formula-given-translation
     (car (box-translation-and-text ,generic-simulation-formula))))

;; Unlike rules, simulation-formulas, and also formulas have only one compilation.
;; The focal-name is for the left side of the formula.




;;;; Variables Forward References



(declare-forward-reference store-history-value function)

(declare-forward-reference simulator-data-server variable)

(declare-forward-reference invoke-rules-for-backward-chaining function)

(declare-forward-reference withdraw-backward-chaining function)

(declare-forward-reference invoke-rules-for-forward-chaining function)

(declare-forward-reference invoke-rules-for-failure-chaining function)

(declare-forward-reference variable-has-received-a-value function)

(declare-forward-reference variable-is-no-longer-available function)

(declare-forward-reference items-needing-initialization variable)  ; ACTIVATE

(declare-forward-reference set-external-variable-for-simulator function)



(declare-forward-reference cache-explanation-variables function) ; Queries

(declare-forward-reference cache-explanation function)   ; Queries






;;;; Variable Class Definitions


;;; The variable frame contains various slots, some of which contain parameters
;;; entered by the user and some which contain values that change often when
;;; running.  For example, the validity interval of a variable is entered by the
;;; user during knowledge base editing, and the expiration time of the variable
;;; is deduced often at run time whenever a new current value for the variable
;;; is obtained.

;;; The variable-or-parameter-stored-histories? slot contains a buffer of stored
;;; values which is not allocated until there is at least one datum.  The buffer
;;; is not saved as part of the knowledge base.

;;; In the future there will have to be a way to save the value of this slot
;;; between G2 invocations, and some mechanism for keeping a fairly recent value
;;; stored in a file in case of an unexpected system operation interruption
;;; (i.e. a crash in layman's parlance).

;;; The variable-or-parameter-history-specification? slot contains specifications
;;; about whether and how to save data in histories.  If no histories are to be
;;; kept the value is nil.  Otherwise it is of the form (history
;;; maximum-number-of-data-points?  maximum-age-of-data-points?)  If
;;; maximum-number-of-data-points? is 0, then none are stored.  If it is nil,
;;; then there is no limit on number.  If maximum-age-of-data-points is nil,
;;; then there is no limit on age.

;;; A value averaging capability may be added at some point.  This involves
;;; specifying an averaging period, and possibly different averaging
;;; specifications depending on age of the data (so that older values are
;;; averaged over larger intervals resulting in fewer older values being kept).
;;; Implementation of this is deferred for now.  If this capability is needed,
;;; it can certainly be implemented, although somewhat less efficiently, by
;;; using intermediate variable and the basic averaging functions.

(def-class (variable-or-parameter #-mtg2 object #+mtg2 shareable-object
				  (foundation-class variable-or-parameter)
                                  define-predicate not-solely-instantiable
                                  not-user-instantiable do-not-put-in-menus)

  (data-type-of-variable-or-parameter nil vector-slot system (type data-type))
  ;; Must be a specific data-type (see grammar in slots).

  (tracing-and-breakpoints nil system user-overridable lookup-slot save
                           (type tracing-and-breakpoints))

  (time-of-most-recent-value
    #.*some-time-ago* vector-slot system
    (attribute-export-comment "Export?"))

  (initial-value-of-variable-or-parameter
    nil vector-slot user-overridable system save
    (attribute-export-comment "Export"))

  (current-value-of-variable-or-parameter nil vector-slot system
                             (type supplied-value) ; don't show now!
                             not-user-editable do-not-save)
  (variable-or-parameter-stored-histories?
    nil vector-slot system
    (attribute-export-comment "Export: Struct"))

  (variable-or-parameter-history-specification?
    nil
    (type history-specification)
    vector-slot user-overridable system
    (attribute-export-comment "Export: Struct"))

  (simulation-info?
    nil lookup-slot system
    (attribute-export-comment "Possible export."))

  (g2-internal-cached-explanation
    nil lookup-slot system do-not-save
    (attribute-export-comment "Internal."))
  )

;;; Probably unnecessary, but just to be on the safe side -alatto, 5/3/99
(def-slot-value-reclaimer g2-internal-cached-explanation (cached-explanation)
  (when cached-explanation
    (reclaim-cached-explanation cached-explanation)))

(defmacro cached-explanation (vop)
  `(g2-internal-cached-explanation ,vop))

;; We should try and change the values in current-value-of-variable-or-parameter
;; so that they are always evaluation values.  I believe that truth values are
;; the only exception now.  -jra 11/5/93


(defun data-type-of-variable-or-parameter-function (variable-or-parameter)
  (data-type-of-variable-or-parameter variable-or-parameter))



;;; Variables and parameters are installed for simulation during loading by the
;;; initialize-after-reading method for variable-or-parameter.  This approach is
;;; used (over the one of installing everything at the end either from
;;; simulation formulas or from variables) due to the fact that kb modules are
;;; expected to be used extensively.  Thus, it could be inefficient to reinstall
;;; everything everytime a (possibly small) kb module is merged.  Using the
;;; loading initialize method is also superior to the incremental approach of
;;; just leaving installation to the slot putters which do the installation for
;;; the non-loading case.  Besides efficiency advantages, the loading initialize
;;; approach assures that all data structures are present (there are no dummy
;;; frames anywhere).  Thus, the simulation installation normally done in slot
;;; putters and other installation functions is disabled when loading a kb.

(declare-forward-reference generic-simulation-formulas-used-p variable)
(declare-forward-reference
  update-generic-simulation-formula-for-variable-or-parameter function)

(def-class-method initialize-after-reading (variable-or-parameter)
  (funcall-superior-method variable-or-parameter)                ; per convention

  ;; The following is intended to catch corruption due to
  ;; automerging. HQ-4378720. It shouldn't be needed, but it's quite inexpensive
  ;; to run here, so it's lowcost insurance. (MHD 11/21/02)
  (fix-up-initial-value-of-variable-or-parameter variable-or-parameter t)

  (when (frame-of-class-p variable-or-parameter 'parameter)
    (let ((initial-value
            (initial-value-of-variable-or-parameter
              variable-or-parameter)))
      (if (slot-value-float-p initial-value)
          (with-temporary-gensym-float-creation initialize-parameters
            (store-managed-number-or-value
              (current-value-of-variable-or-parameter variable-or-parameter)
              (slot-value-float-value initial-value)))
          (store-managed-number-or-value
            (current-value-of-variable-or-parameter variable-or-parameter)
            initial-value))))
  (update-representations-of-variable-or-parameter-value variable-or-parameter)
  (when generic-simulation-formulas-used-p
    (update-generic-simulation-formula-for-variable-or-parameter
      variable-or-parameter)))




;;; The initialize method for variable-or-parameter performs simulation
;;; installation on the variable or parameter if appropriate.  The check of
;;; attribute-nesting-depth is performed to make sure that this is not in the
;;; context of instantiate-variable; if it is, this installation is performed by
;;; put-attribute-value.  Note also that the initialize method is not called
;;; during loading.

(declare-forward-reference attribute-nesting-depth variable)

(def-class-method initialize (variable-or-parameter)
  (funcall-superior-method variable-or-parameter)                ; per convention
  (when (and generic-simulation-formulas-used-p
             (=f attribute-nesting-depth 1))
    (update-generic-simulation-formula-for-variable-or-parameter
      variable-or-parameter)
    ))



(def-absent-slot-putter simulation-category?
                        (variable-or-parameter value)
  (declare (ignore variable-or-parameter value)))

(def-absent-slot-putter initial-simulated-value?
                        (variable-or-parameter value)
  (declare (ignore variable-or-parameter value)))

(def-absent-slot-putter formula-specified-time-increment-for-update?
                        (variable-or-parameter value)
  (declare (ignore variable-or-parameter value)))

(def-slot-putter data-type-of-variable-or-parameter (variable new-data-type)
  (setf (data-type-of-variable-or-parameter variable) new-data-type)
  (handle-update-to-sensor-data-type variable)
  new-data-type)

;; jh, 12/20/91.  Added a slot-putter for data-type-of-variable-or-parameter.  All
;; that this slot putter currently needs to do is notify the GSI extension process
;; when the user edits the data type of a variable with GSI data-service
;; capability.  This happens through a call to handle-update-to-sensor-data-type.
;; This change does not affect the behavior of a variable without GSI data-service
;; capability.


(def-absent-slot-putter data-type-of-variable (variable value)
  (change-slot-value variable 'data-type-of-variable-or-parameter value))

(def-absent-slot-putter variable-stored-history-specification? (variable value)
  (change-slot-value variable 'variable-or-parameter-history-specification?
                     value))



(define-slot-alias initial-value initial-value-of-variable-or-parameter)


(def-class (variable variable-or-parameter define-predicate
                     not-solely-instantiable
                     not-user-instantiable do-not-put-in-menus
                     (foundation-class variable)
                     (class-export-comment "Export computation style and history info, etc."))
  (frame-flags 0 system vector-slot user-overridable (type variable-frame-flags))
  (expiration-time-of-current-value #.*some-time-ago* vector-slot system)
  ;; Expiration is stored in a gensym-time format.
  ;; 'never if valid indefinitely. Reset to *some-time-ago*.

  (validity-interval nil vector-slot system user-overridable (type validity-interval))
  ;; Must be a positive interval in seconds, 'indefinite or 'supplied.  It is
  ;; necessary for o.k. installation.  Only derived variables can have 'supplied
  ;; as their validity interval.  Sensor variables should not have 'supplied as
  ;; their validity interval.  Furthermore, if the validity-interval of a sensor
  ;; is 'never then it must be one-shot.  The installation methods should check
  ;; for these.  If the validity-interval is chaged from indefinite, then
  ;; expiration-time must be reset to make it invalid.

  (formula? nil vector-slot system (type instance-formula text) select-changes)
  ;; The text may be an expression or logical expression

  (time-of-oldest-unsatisfied-request? nil vector-slot system)
  ;; The time-of-oldest-unsatisfied-request? is the earliest time at which a
  ;; request for the current value of a variable was made and not satisfied,
  ;; which follows the last time at which the value was current. If the last
  ;; attempt was successful, or the variable is virgin, it should be nil.  Reset
  ;; to nil.

  (task-to-check-variable? nil vector-slot system)
  ;; This slot holds tasks which are used to detect failure in variables and
  ;; sensors, and to hold the task which probes sensors when they have failed.

  (simulation-details
    nil lookup-slot system user-overridable
    (type simulation-frame?) not-user-editable
    (class-of-optional-subframe simulation-subtable))

  (history-specification-for-simulation-subtables?
    nil lookup-slot system user-overridable
    (type history-specification) do-not-put-in-attribute-tables)
  ;; This slot holds the class default value for the simulation-stored-history-
  ;; specification? slot of the subframes (simulation-subtables) of the
  ;; simulation-details slots of variables.

  (non-default-initial-simulated-value?
    nil (type non-default-number?) lookup-slot system)

  (data-server-map computation vector-slot system user-overridable
                   (type data-server-map))
  ;; The value is either a data supplier or an alist mapping modes to data
  ;; suppliers.  A data supplier is either a defstruct of which there is a
  ;; unique one per supplier, e.g. simulator-data-server, or it is 'computation.

  (background-collection-interval? nil vector-slot system user-overridable
                                   (type positive-quantity-interval?))
  ;; The user controlled interval for causing automatic and regular data
  ;; collection.

;  (task-for-background-collection nil vector-slot system)
;  ;; This location is used by the scheduler when the task is scheduled to
;  ;; instigate-current-value as a background-collection.

  (structure-for-background-collection? nil vector-slot system)
  ;; A structure to hold the task on interest-lists of requests to the inference
  ;; engine for background collection of a variable's value.

  ;; Note, this slot used to be named task-for-background-collection.  More
  ;; structure was needed, so the task is now stored as part of this structure.
  ;; -jra 7/11/90

  (formula-invocation? nil vector-slot system)
  ;; This slot is used to hold formula invocations when backward chaining to
  ;; formulas from variables.

;  (variable-time-of-wake-up nil vector-slot system)
  ;; List of frames and other things to wake-up when value is received.

  (things-this-variable-is-interested-in nil vector-slot system)
  ;; List of the variables and rule instances which this variable is using in
  ;; trying to determine its value through backward chaining.  When evaluating a
  ;; formula to determine a value for this variable there will be variables on
  ;; this list.  When backward chaining to rules there will be rule instances on
  ;; this list.  This slot is cleared with notifications to the objects when
  ;; this variable receives a value, when it is about to re-evaluate a formula,
  ;; or when there are no longer any things which are interested in this
  ;; variable.  This slot replaces variables-that-can-wake-up-this-variable.

  (things-interested-in-this-variable nil vector-slot system)
  ;; List of the things which are currently requesting the value of this
  ;; variable.  These things will receive a notification when this variable
  ;; receives a value.  If all of these things are removed from a variable, then
  ;; nothing is interested in it and any work being performed for backward
  ;; chaining should be stopped.

  (task-for-wake-up? nil vector-slot system)
  ;; This slot holds the task which is in the process of waking up this
  ;; variable, if any.

  (thing-postponing-clean-up? nil vector-slot system)
  ;; An item on the things-interested-in-this-variable list may choose to remove
  ;; itself from the list but delay the clean up process of shutting down its
  ;; backward chaining until the thing has had a chance to possibly add itself
  ;; back on to the list.  This is a spot for storing the thing postponing the
  ;; clean up.

  (task-for-expiration? nil vector-slot system)

  ;; This task will be scheduled when there are items which need to be updated
  ;; upon expiration of this variable's value, for example table displays of its
  ;; value.  When there are no such items, then no task will be scheduled.  The
  ;; schedule time for this task will always be expiration-time-of-current-value
  ;; plus one.
  (task-for-local-data-server? nil vector-slot system)

  (backward-chain-new-rules nil system vector-slot)

  (backward-chain-priority? nil system vector-slot)

  )



(def-absent-slot-putter simulation-frame? (variable value)
  (change-slot-value variable 'simulation-details value))

(define-slot-alias data-server data-server-map)

(declare-forward-reference remove-variable-from-simulation function)

(define-slot-alias history-keeping-spec-for-simulation-subtables history-specification-for-simulation-subtables?)



(declare-forward-reference
  delete-dynamic-rule-displays-for-rule-or-object function)      ; queries

(declare-forward-reference
  delete-backward-chaining-display-if-any-for-variable function) ; EXPLAIN

(def-class-method cleanup (variable)
  (funcall-superior-method variable)
  (delete-dynamic-rule-displays-for-rule-or-object variable)
  (delete-backward-chaining-display-if-any-for-variable variable)
  (change-slot-value variable 'variable-or-parameter-history-specification? nil)
  (change-slot-value variable 'simulation-info? nil))

(def-class-method cleanup (parameter)
  (funcall-superior-method parameter)
  (delete-dynamic-rule-displays-for-rule-or-object parameter)
  (change-slot-value parameter 'variable-or-parameter-history-specification? nil)
  (change-slot-value parameter 'simulation-info? nil))

;; In the cleanup methods for variable and parameter, changing the
;; simulation-info?  slot to nil causes the slot putter for simulation-info?  to
;; call remove-simulation-info-from-variable-or-parameter if the value of this
;; slot is non-nil.  Remove-simulation-info-from-variable-or-parameter calls
;; remove-variable-from-simulation, which reclaims any
;; variable-simulation-runtime-structure.
;; Remove-simulation-info-from-variable-or-parameter then reclaims the
;; simulation-info structure.



(def-class-method cleanup (object)
  (funcall-superior-method object)
  (delete-dynamic-rule-displays-for-rule-or-object object))




;;; The G2-variable class is a subclass of variable, but is not a sensor.
;;; G2-variable class has three system supplied subclasses, logical-variable,
;;; quantitative-variable, and symbolic-variable.  Note that the forward-chain
;;; frame flag is set for only logical and symbolic variables.  Neither
;;; quantitative variables nor sensor variables will participate in forward
;;; chaining.

(def-class (g2-variable variable (foundation-class g2-variable)
                        define-predicate not-solely-instantiable
                        not-user-instantiable)
  (validity-interval supplied vector-slot system (type validity-interval)))


(def-class (logical-variable g2-variable
                             (foundation-class logical-variable) define-predicate)
  (frame-flags #.forward-chain-flag system vector-slot
               (type variable-frame-flags))
  (data-type-of-variable-or-parameter
   truth-value vector-slot system (type read-only-truth-value-data-type) not-user-editable)
  (initial-value-of-variable-or-parameter
    nil vector-slot system (type truth-value?))
  (formula? nil vector-slot system (type logical-instance-formula text) select-changes)
  ;; The text may be an expression or logical expression
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((outline (0 0) (60 0) (60 60) (0 60))
       (outline (17 9) (43 9) (43 33) (33 33) (33 42) (27 42)
                (27 27) (36 27) (36 15) (24 15) (24 21) (17 21))
       (outline (27 48) (33 48) (33 54) (27 54))))))

(def-class (quantitative-variable g2-variable
                                  (foundation-class quantitative-variable)
                                  define-predicate)
  (frame-flags 0 system vector-slot (type variable-frame-flags))
  (data-type-of-variable-or-parameter
    number vector-slot system (type quantitative-data-type) user-overridable)
  (initial-value-of-variable-or-parameter
    nil vector-slot system (type quantity?))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((outline (0 0) (60 0) (60 60) (0 60))
       (lines (0 30) (60 30))
       (lines (0 30) (arc (15 15)) (30 30))
       (lines (30 30) (arc (45 45)) (60 30))))))

(def-class (float-variable quantitative-variable
                           (foundation-class float-variable) define-predicate)
  (frame-flags 0 system vector-slot (type variable-frame-flags))
  (data-type-of-variable-or-parameter
   float vector-slot system (type float-data-type))
  (initial-value-of-variable-or-parameter
    nil vector-slot system (type initial-value-float?))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((outline (0 0) (60 0) (60 60) (0 60))
       (lines (0 30) (60 30))
       (lines (2 30) (arc (9 23)) (16 30) (arc (23 37)) (30 30)
              (arc (37 23)) (44 30) (arc (51 37)) (58 30))))))

(def-class (integer-variable quantitative-variable
                             (foundation-class integer-variable) define-predicate)
  (frame-flags 0 system vector-slot (type variable-frame-flags))
  (data-type-of-variable-or-parameter
   integer vector-slot system (type integer-data-type))
  (initial-value-of-variable-or-parameter
    nil vector-slot system (type initial-value-integer?))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((outline (0 0) (60 0) (60 60) (0 60))
       (lines (0 30) (60 30))
       (lines (2 30) (2 23) (16 23) (16 37) (30 37)
              (30 23) (44 23) (44 37) (58 37) (58 30))))))

(def-class (long-variable quantitative-variable
                             (foundation-class long-variable) define-predicate)
  (frame-flags 0 system vector-slot (type variable-frame-flags))
  (data-type-of-variable-or-parameter
    long vector-slot system (type long-data-type))
  (initial-value-of-variable-or-parameter
    nil vector-slot system (type initial-value-long?))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((outline (0 0) (60 0) (60 60) (0 60))
       (lines (0 30) (60 30))
       (lines (2 30) (2 23) (16 23) (16 37) (30 37)
              (30 23) (44 23) (44 37) (58 37) (58 30))))))

;;; GENSYMCID-758: G2 abort when loading gsi_exam.kb
(def-substitute-for-old-class int64-variable long-variable
  (+ g2-version-2011-kb-flags 1))

(def-class (symbolic-variable g2-variable
                              (foundation-class symbolic-variable)
                              define-predicate)
  (frame-flags #.forward-chain-flag system vector-slot
               (type variable-frame-flags))
  (data-type-of-variable-or-parameter
    symbol vector-slot system (type read-only-symbol-data-type) not-user-editable)
  (initial-value-of-variable-or-parameter
    nil vector-slot system (type standard-or-class-qualified-symbol?))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((outline (0 0) (60 0) (60 60) (0 60))
       (outline (24 6) (36 6) (36 18) (24 18))
       (outline (24 24) (36 24) (36 36) (24 36))
       (outline (24 42) (36 42) (36 54) (24 54))))))

(def-class (text-variable g2-variable
                          (foundation-class text-variable) define-predicate)
  (frame-flags 0 system vector-slot (type variable-frame-flags))
  (data-type-of-variable-or-parameter
    text vector-slot system (type read-only-text-data-type) not-user-editable)
  (initial-value-of-variable-or-parameter
    nil vector-slot system (type whole-string?))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((outline (0 0) (60 0) (60 60) (0 60))
       (lines (7 30) (7 35)) (lines (10 30) (10 35))
       (lines (49 30) (49 35)) (lines (52 35) (52 30))
       (lines (16 40) (16 41) (17 41) (17 40))
       (lines (22 40) (22 41) (23 41) (23 40))
       (lines (28 40) (28 41) (29 41) (29 40))
       (lines (34 40) (34 41) (35 41) (35 40))
       (lines (40 40) (40 41) (41 41) (41 40))
       (lines (46 40) (46 41) (47 41) (47 40))))))

;; Specific reference to the symbols generated by the following macro are made
;; in the grammar, compiler and writer for default-overrides in grammar2.

;(declare-user-editable-frame-flags variable
;  (forward-chain (do forward chain) (do not forward chain))
;  (dont-backward-chain (do not backward chain) (do backward chain)))






;;; Sensor is a subclass of variables. Specific types of sensors should be
;;; defined as subclasses of sensor.


(def-class (sensor variable
                   (foundation-class sensor)
                   define-predicate
                   not-user-instantiable do-not-put-in-menus)

  (data-type-of-variable-or-parameter number vector-slot system
                                      user-overridable
                                      (type data-type))

  (initial-value-of-variable-or-parameter
    nil vector-slot system (type initial-sensor-value?))

  (formula? nil vector-slot system (type nil))

  ;; The type for formulas of sensors should be left as is to allow users to
  ;; enter formulas for sensor variables!!!  Gotta check with Lowell first.
  ;; -jra 8/16/88

  (validity-interval indefinite vector-slot system
                     (type sensor-validity-interval))

  (data-server-map simulator-data-server vector-slot system
                   (type data-server-map))

  (icon-description
    (:funcall-at-load-time
      create-icon-description
      20 20
      ((circle (0 10) (10 0) (20 10))
       (lines (7 4) (7 15) (13 15)))))

  )


;;; The following two absent slot putters area to handle any values for the
;;; above obsolete slots.

(def-absent-slot-putter rule-to-invoke-when-value-arrives?
                        (sensor old-rule-to-invoke-value)
  (declare (ignore sensor old-rule-to-invoke-value)))

(def-absent-slot-putter rule-to-invoke-when-sensor-fails?
                        (sensor old-rule-to-invoke-value)
  (declare (ignore sensor old-rule-to-invoke-value)))




;;; The macro `sensor-collection-interval' for a sensor having a numeric
;;; validity-interval returns 1 less than its validity-interval but at least 1.
;;; This used to be a slot.  It should not be called if the validity-interval is
;;; 'indefinite.

(defmacro sensor-collection-interval? (sensor)
  `(maxi 1 (-i (validity-interval ,sensor) 1)))




;;; The slot putter for the formula? slot checks for out of date specific
;;; formulas.

(def-slot-putter formula? (variable new-formula? initializing?)
  (when (and (consp new-formula?)
             initializing?
             (not (compilations-up-to-date-p variable))
             loading-kb-p)
    (reclaim-slot-value (car new-formula?))
    (setf (car new-formula?) no-value)
    (note-frame-with-compilation-removed variable)
;    (update-frame-status variable 'incomplete t)  ; removed. (MHD 7/18/94)
    )
  (setf (formula? variable) new-formula?))




;;; The macro `value-of-variable-is-current' returns non-null if the
;;; expiration-time-of-current-value of the variable is 'never or if it is a
;;; clock tick time greater than or equal to the current gensym-time.

(defmacro value-of-variable-is-current (variable)
  `(let ((expiration-time-of-current-value
           (expiration-time-of-current-value ,variable)))
     (or (eq expiration-time-of-current-value 'never)
         (>=i expiration-time-of-current-value (clock-get gensym-time)))))




;;; The macro `variable-has-received-no-value' takes a variable and returns
;;; non-null if the variable has been given a value (via put-current-value)
;;; since the system was started.  If the variable is inactive, it also returns
;;; non-nil.

(def-substitution-macro variable-has-received-no-value (expiration-of-variable)
  (and (neq expiration-of-variable 'never)
       (=f expiration-of-variable *some-time-ago*)))






;;;; Parameters

;;; A `Parameter' is an object. Thus it is also an entity and an item.  A
;;; parameter is in many ways like a variable except that it lacks data service,
;;; backward chaining, expiration, and history.

;;; Parameters have an initialization slot which is an appropriate datum.  This
;;; slot may not contain NIL.  This initial value is copied into the current
;;; value slot at three different times: creation (in the initialize method),
;;; load time (in a post-loading function), and at deactivation time (via the
;;; deactivate-subclass-of-entity method).  Through these three copy operations,
;;; the parameter ALWAYS has a value (except for the short period between when
;;; the frame is created in a load and the load function is called).  None of
;;; these three cause forward chaining, though a conclude that would.  Also,
;;; when the system is not running, changing the initial value causes the value
;;; to propagate to the current value of a parameter.

(def-class (parameter variable-or-parameter (foundation-class parameter)
                      define-predicate not-solely-instantiable
                      not-user-instantiable)
  (frame-flags 0 system vector-slot user-overridable (type parameter-frame-flags)))






;;; The function `valid-initial-value-p' is given a proposed value for the
;;; initial-value-of-variable-or-parameter of a variable-or-parameter instance.
;;; If it is valid, this returns true (non-nil); otherwise, false (nil).

;;; This is prepared to deal only with the types associated with subclasses of
;;; variable-or-parameter, i.e., symbol, quantity, integer, float, truth-value,
;;; text.

(defun valid-initial-value-p (variable-or-parameter)
  (let* ((managed-value
           (initial-value-of-variable-or-parameter variable-or-parameter)))
    (cond
      ((null managed-value)                ; nil is OK for variables only
       (variable-p variable-or-parameter))
      (t
       (let ((required-type
               (get-data-type-of-variable-or-parameter-from-frame
                 variable-or-parameter)))
         ;; We can't use number-subtype-p here because that would force both
         ;; integers and floats to be seen only as 'number which meand a type
         ;; mismatch between an integer and float would be missed.  It would be
         ;; really nice to use convert-type-or-unit-of-measure-to-type, but the
         ;; problem is that it curently signals a warning of its own, and then
         ;; punts to 'number so it would require some abstracting to use in this
         ;; conext.  Too close to code-freeze.  -dkuznick, 8/22/03
         (when (numeric-data-type required-type)
           (setq required-type 'number))
         (case required-type
           (truth-value                        ; see note
            (valid-value-for-managed-truth-value-p managed-value))
           (t
            (symbolic-type-specification-subtype-p
              (evaluation-value-type managed-value) ; see note 2
              required-type))))))))

;; Note: this continues the tradition of special-casing the handling of the
;; "managed value" that is stored in the slot. In particular, it has to
;; special-case truth values, unfortunately, as done, e.g., by callers to
;; make-evaluation-value-from-managed-value.

;; Note 2: this knows that, apart from truth values, evaluation values and
;; managed values, as used with initial value of a variable-or-parameter
;; instance, are equivalently type tagged ! (MHD 11/21/02)





;;; The function `fix-up-initial-value-of-variable-or-parameter' is to be used
;;; to fix up slightly corrupted instances of variable-or-parameter, namely
;;; those with a value for the INITIAL-VALUE parameter that does not conform the
;;; type implied by the class of the instance.  If bad, the initial value is
;;; changed to the default for the class.  If report-if-bad? is true, this
;;; advises the user of the fix being made, both on the logbook and on the
;;; console.

(defun fix-up-initial-value-of-variable-or-parameter
    (variable-or-parameter &optional report-if-bad?)
  (unless (valid-initial-value-p variable-or-parameter)
    (when report-if-bad?
      (report-bad-initial-value-of-variable-or-parameter
        variable-or-parameter))
    (change-slot-value
      variable-or-parameter
      'initial-value-of-variable-or-parameter
      (get-slot-init-form
        (class variable-or-parameter)
        'initial-value-of-variable-or-parameter))))



(defun report-bad-initial-value-of-variable-or-parameter (variable-or-parameter)
  (let* ((value
           (initial-value-of-variable-or-parameter variable-or-parameter))
         (evaluation-value?                ; see note
           (if value (make-evaluation-value-from-managed-value nil value)))
         (type
           (get-data-type-of-variable-or-parameter-from-frame
             variable-or-parameter))
         (class (class variable-or-parameter))
         (init-form
           (get-slot-init-form class 'initial-value-of-variable-or-parameter))
         (init-form-evaluation-value?
           (if init-form
               (make-evaluation-value-from-managed-value
                 (eq type 'truth-value)
                 init-form))))
    (notify-user-at-console-and-on-logbook
      "The initial-value (~NV) of ~NF is not of the valid type (~NT) for this ~
       class.  Changing value to ~NV, the default for class ~A."
      evaluation-value? variable-or-parameter
      type init-form-evaluation-value? class)
    (when evaluation-value?
      (reclaim-evaluation-value evaluation-value?))
    (when init-form-evaluation-value?
      (reclaim-evaluation-value init-form-evaluation-value?))))

;; Note: we store the initial value as a "managed value", but we have to supply
;; an evaluation-value to the ~NV formatting directive.  A managed truth value
;; in the range -1000..1000 is indistinguishable from an integer.  So if it's of
;; the wrong type, we don't know exactly how to print it. In this case, we just
;; punt and print it as an integer. (MHD 11/21/02)


;;; Mess-up-initial-values-for-testing is a development function.
;;;
;;; Use with caution! It actually corrupts the KB to simulate a kind of
;;; corruption that could have happened in the past: bad values getting into the
;;; initial-value-of-variable-or-parameter of variable-or-parameter instances.
;;; After running this in a KB with a bunch of instances of each class with an
;;; entry in messed-up-initial-values-for-testing, save the KB, and then by
;;; loading it, you will test G2's ability to heal itself.  Make sure the
;;; messages all look OK. Then save the KB, and make sure no messages appear
;;; (since the KB should be clean).

#+development
(defparameter messed-up-initial-values-for-testing
  '((logical-parameter nil 1001 g2 #w"XXX")
    (logical-variable 1001 g2 #w"YYY")
    (symbolic-parameter nil #w"abc" 123)
    (symbolic-variable #w"def" 123)
    (text-parameter nil foo 123)
    (text-variable  bar 123)
    (float-parameter nil foo 123)
    (float-variable  bar 123)))

#+development
(defun mess-up-initial-values-for-testing ()
  (loop for (class . values) in messed-up-initial-values-for-testing
        do (loop for instance being each class-instance of class
                 as value in values
                 do (change-slot-value
                      instance 'initial-value-of-variable-or-parameter
                      value))))

;; This creates a subset of possible mismatches.  The idea is just to test the
;; ones that could result from class changes.  That was a problem with an issue,
;; HQ-4378720.  You can always add more, but I (MHD) don't know how you test
;; with floats at this time. I tested this using
;; /gensym/issuekbs/g2-61r0/HQ-4378720-a/mhd-variable-or-parameter-init-value-test.kb,
;; which has, and originally pointed out, the corruption. (MHD 11/21/02)







;;; The slot putter for the initial-value-of-variable-or-parameter will reclaim
;;; the old value in the slot (if it is not eq to the default value), and then
;;; determines if the given value is datum-equal to the default value.  If so,
;;; then the default value is actually stored into the initial-value slot.  This
;;; helps invoke the kb-save optimization which doesn't write frame descriptions
;;; into kbs when all savable slots of the frame are EQ to the default values.

(def-slot-putter initial-value-of-variable-or-parameter
                 (variable-or-parameter new-value initialize?)
  (let ((default-value (get-slot-init-form
                         (class variable-or-parameter)
                         'initial-value-of-variable-or-parameter)))
    ;; Note that the non-sensical predicate of the when below was inserted to
    ;; effectively eliminate the code within the when clause.  This was done due
    ;; to a corruption which occured when changing the default settings slot of
    ;; the class definition.  Assumptions in that slot putter made the code
    ;; below corrupt memory.  When that slot putter is fixed, then the code
    ;; below can be made active again.  -jra & mhd 3/5/92
    (when (and (not (eq new-value default-value))
               (eq variable-or-parameter new-value))
      (cond ((and (text-string-p new-value)
                  (text-string-p default-value)
                  (string=w new-value default-value))
             (reclaim-slot-value new-value)
             (setq new-value default-value))
            ((and (or (gensym-float-p new-value)
                      (slot-value-float-p new-value))
                  (or (gensym-float-p default-value)
                      (slot-value-float-p default-value)))
             (with-temporary-gensym-float-creation put-initial-value
               (when (=e (if (slot-value-float-p new-value)
                             (slot-value-float-value new-value)
                             new-value)
                         (if (slot-value-float-p default-value)
                             (slot-value-float-value default-value)
                             default-value))
                 (when (slot-value-float-p new-value)
                   (reclaim-slot-value new-value))
                 (setq new-value default-value))))))
    (setf (initial-value-of-variable-or-parameter variable-or-parameter) new-value)
    (when (and (not (or system-is-running system-has-paused initialize?))
               (frame-of-class-p variable-or-parameter 'parameter))
      (with-temporary-gensym-float-creation put-initial-value-into-current
        (store-managed-number-or-value
          (current-value-of-variable-or-parameter variable-or-parameter)
          (if (slot-value-float-p new-value)
              (slot-value-float-value new-value)
              new-value))
        nil)
      (update-representations-of-variable-or-parameter-value variable-or-parameter))
    new-value))

(def-class-method initialize (parameter)
  (funcall-superior-method parameter)                ; per convention
  (let ((initial? (initial-value-of-variable-or-parameter parameter)))
    (if (slot-value-float-p initial?)
        (with-temporary-gensym-float-creation initialize-parameter
          (store-managed-number-or-value
            (current-value-of-variable-or-parameter parameter)
            (slot-value-float-value initial?)))
        (store-managed-number-or-value
          (current-value-of-variable-or-parameter parameter)
          initial?))
    nil))

(def-class (logical-parameter parameter
                              (foundation-class logical-parameter)
                              define-predicate)
  (frame-flags #.(+f forward-chain-flag passive-flag dont-backward-chain-flag)
               system vector-slot
               (type parameter-frame-flags))
  (data-type-of-variable-or-parameter
   truth-value vector-slot system (type read-only-truth-value-data-type) not-user-editable)

  (initial-value-of-variable-or-parameter
    #.falsity vector-slot system (type truth-value))

  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((outline (12 0) (48 0) (60 12) (60 48) (48 60) (12 60) (0 48) (0 12))

       (outline (17 9) (43 9) (43 33) (33 33) (33 42) (27 42)
                (27 27) (36 27) (36 15) (24 15) (24 21) (17 21))
       (outline (27 48) (33 48) (33 54) (27 54))))))

(def-class (quantitative-parameter parameter
                                   (foundation-class quantitative-parameter)
                                   define-predicate)
  (frame-flags #.(+f passive-flag dont-backward-chain-flag)
               system vector-slot (type parameter-frame-flags))
  (data-type-of-variable-or-parameter
   number vector-slot system (type quantitative-data-type) user-overridable)
  (initial-value-of-variable-or-parameter
    0.0 vector-slot system (type quantity))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((outline (12 0) (48 0) (60 12) (60 48) (48 60) (12 60) (0 48) (0 12))
       (lines (0 30) (60 30))
       (lines (0 30) (arc (15 15)) (30 30))
       (lines (30 30) (arc (45 45)) (60 30))))))

(def-class (integer-parameter quantitative-parameter
                              (foundation-class integer-parameter)
                              define-predicate)
  (data-type-of-variable-or-parameter
    integer vector-slot system (type integer-data-type))
  (initial-value-of-variable-or-parameter
    0 vector-slot system (type initial-value-integer))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((outline (12 0) (48 0) (60 12) (60 48) (48 60) (12 60) (0 48) (0 12))
       (lines (0 30) (60 30))
       (lines (2 30) (2 23) (16 23) (16 37) (30 37)
              (30 23) (44 23) (44 37) (58 37) (58 30))))))

(def-class (long-parameter quantitative-parameter
                              (foundation-class long-parameter)
                              define-predicate)
  (data-type-of-variable-or-parameter
    long vector-slot system (type long-data-type))
  (initial-value-of-variable-or-parameter
    0 vector-slot system (type initial-value-long))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((outline (12 0) (48 0) (60 12) (60 48) (48 60) (12 60) (0 48) (0 12))
       (lines (0 30) (60 30))
       (lines (2 30) (2 23) (16 23) (16 37) (30 37)
              (30 23) (44 23) (44 37) (58 37) (58 30))))))

;;; GENSYMCID-758: G2 abort when loading gsi_exam.kb
(def-substitute-for-old-class int64-parameter long-parameter
  (+ g2-version-2011-kb-flags 1))

(def-class (float-parameter quantitative-parameter
                            (foundation-class float-parameter) define-predicate)
  (data-type-of-variable-or-parameter
    float vector-slot system (type float-data-type))
  (initial-value-of-variable-or-parameter
    0.0
    vector-slot system (type initial-value-float))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((outline (12 0) (48 0) (60 12) (60 48) (48 60) (12 60) (0 48) (0 12))
       (lines (0 30) (60 30))
       (lines (2 30) (arc (9 23)) (16 30) (arc (23 37)) (30 30)
              (arc (37 23)) (44 30) (arc (51 37)) (58 30))))))

(def-class (symbolic-parameter parameter
                               (foundation-class symbolic-parameter) define-predicate)
  (frame-flags #.(+f forward-chain-flag passive-flag dont-backward-chain-flag)
               system vector-slot
               (type parameter-frame-flags))
  (data-type-of-variable-or-parameter
   symbol vector-slot system (type read-only-symbol-data-type) not-user-editable)

  (initial-value-of-variable-or-parameter
    g2 vector-slot system (type standard-or-class-qualified-symbol))

  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((outline (12 0) (48 0) (60 12) (60 48) (48 60) (12 60) (0 48) (0 12))
       (outline (24 6) (36 6) (36 18) (24 18))
       (outline (24 24) (36 24) (36 36) (24 36))
       (outline (24 42) (36 42) (36 54) (24 54))))))

(def-class (text-parameter parameter
                           (foundation-class text-parameter) define-predicate)
  (frame-flags #.(+f passive-flag dont-backward-chain-flag)
               system vector-slot (type parameter-frame-flags))
  (data-type-of-variable-or-parameter
   text vector-slot system (type read-only-text-data-type) not-user-editable)

  (initial-value-of-variable-or-parameter
    "" vector-slot system (type whole-string))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((outline (12 0) (48 0) (60 12) (60 48) (48 60) (12 60) (0 48) (0 12))
       (lines (7 30) (7 35)) (lines (10 30) (10 35))
       (lines (49 30) (49 35)) (lines (52 35) (52 30))
       (lines (16 40) (16 41) (17 41) (17 40))
       (lines (22 40) (22 41) (23 41) (23 40))
       (lines (28 40) (28 41) (29 41) (29 40))
       (lines (34 40) (34 41) (35 41) (35 40))
       (lines (40 40) (40 41) (41 41) (41 40))
       (lines (46 40) (46 41) (47 41) (47 40))))))






;;;; Type Specifications of Variables and Parameters




;;; The function type-specification-of-variable-or-parameter-value fetches the
;;; type specification of values which can be held within variables or
;;; parameters.  The slot data-type-of-variable-or-parameter holds a user
;;; specified type-specification or defined engineering unit.  This function
;;; looks to that slot, and if a defined type specification is held there,
;;; returns it.  Otherwise, this function checks that the held value is a
;;; defined engineering unit, and returns the type NUMBER, since all defined
;;; types are numbers.  If the held type is neither a type specification nor a
;;; defined engineering unit, then this function returns the most general type
;;; allowable for the class of the variable or parameter.

(declare-side-effect-free-function
  type-specification-of-variable-or-parameter-value)

(defun-simple type-specification-of-variable-or-parameter-value
              (variable-or-parameter)
  (let ((stored-data-type
          (data-type-of-variable-or-parameter variable-or-parameter)))
    (cond ((symbolic-type-specification-subtype-p stored-data-type 'datum)
           stored-data-type)
          ((number-subtype-p stored-data-type)
           'number)
          (t
           ;; Maybe issue warning, or does something else issue warnings like
           ;; this?
           'datum))))

;;;






;;;; Expiration Updates




;;; Some representations of this variables value will have to be updated when
;;; the value within a variable expires.  Current examples are the displays of
;;; the attribute values of a parent frame.  The expiration update facility is
;;; designed to handle the needs of these updates in a consistent and
;;; centralized place.

;;; Please note that this facility is one which we had purposefully avoided in
;;; the past.  A good part of our argument about the efficiency of a truth
;;; maintenance scheme built on variable value expirations was that values of
;;; variables could expire for free -- literally no processing was required to
;;; let a value expire.  Given a pattern of data computation which has large
;;; sets of values which are required only once in a long while, when compared
;;; to their validity intervals, free expiration is an important part of an
;;; efficiency argument.  This facility is a hook to violate that efficiency.
;;; It should be used with care, so as to not require expiration computation on
;;; a large percentage of the variables in the system.  That caveat out of the
;;; way, what follows is a description of the facility.  -jra 11/1/88

;;; The function `update-representations-of-variable-or-parameter-value' takes a
;;; variable and will cause updates to be executed for frame representations
;;; which were dependent on the value of this variable.  This function tries to
;;; be very efficient about returning when there are no representations to be
;;; updated.

(defun update-representations-of-variable-or-parameter-value
       (variable-or-parameter)
  (when (frame-representations variable-or-parameter)
    (update-representations-of-slot-value-macro
      variable-or-parameter
      'current-value-of-variable-or-parameter
      nil))
  (when (and (parent-frame variable-or-parameter)
             (frame-representations (parent-frame variable-or-parameter)))
    ;; This is fixed for  non-unique (pretty) slot names.  (MHD 2/16/94)
    (multiple-value-bind (parent-frame slot-name class-qualifier?)
        (get-kb-parent-information variable-or-parameter)
      (update-representations-of-slot-value-macro
        parent-frame slot-name class-qualifier?)))
  (update-subscriptions-from-variable-change variable-or-parameter))

;; In the when, the first nil check could be done on the first return value, and
;; the second one could be skipped, but this is a bit more optimal, since both
;; slots are quite often nil. (MHD 2/16/94)



;;; The function `schedule-update-for-variable-expiration' takes a variable and
;;; will ensure that a task is scheduled which will update any representations
;;; of that variable's value when the current value of the variable expires.
;;; This macro requires that the expiration be already confirmed as a
;;; gensym-time which is either equal to or greater than the current
;;; gensym-time.  The task is scheduled for the second after the expiration,
;;; since a value is still considered valid when gensym-time equals the
;;; expiration time.

(defparameter priority-of-expiration-update-task 2)

(defun schedule-update-for-variable-expiration (variable)
  (let* ((expiration (expiration-time-of-current-value variable))
         (task-time (+f expiration 1))
         (task (task-for-expiration? variable)))
    (declare (type fixnum expiration task-time))
    (if (schedule-task-in-place-p task)
        (when (/=f (convert-unix-time-to-gensym-time
                     (schedule-task-time task))
                   task-time)
          (reschedule-task
            (task-for-expiration? variable) (-f task-time (clock-get gensym-time))))
        (with-future-scheduling
            ((task-for-expiration? variable) priority-of-expiration-update-task
             (g2-future-interval (-f task-time (clock-get gensym-time))))
          (propagate-variable-value-expiration variable)))))



;;; The function `propagate-variable-value-expiration' is called as a scheduled
;;; task when the value of a variable expires, and either a frame
;;; representation, or a true-value-update-recipient needs to be updated in
;;; response to the change.

(defun-void propagate-variable-value-expiration (variable)
  (update-representations-of-variable-or-parameter-value variable)
  (let ((*current-computation-frame*-previously-bound?
          (framep *current-computation-frame*))
        (old-value (extract-cached-number-or-value
                     (current-value-of-variable-or-parameter variable))))
    (unless *current-computation-frame*-previously-bound?
        (setq *current-computation-frame* variable))
    (invoke-update-functions-for-expired-value variable old-value)
    (unless *current-computation-frame*-previously-bound?
        (setq *current-computation-frame* nil))))



;;; A kb-frame can be active or inactive.  Use (active-p kb-frame), (set-active
;;; kb-frame), and (set-inactive kb-frame).

;;; A frame is active if the surrounding knowledge block it is in is active.
;;; Activate, de-activate, and reset methods are defined below.  Note that these
;;; runtime activate methods are distinct from the start and stop using methods
;;; of installation.

;;; When a variable is active, it can collect data.  If background-collection-
;;; interval is not nil, the variable will begin collecting data for histories
;;; at the specified interval.  The variable can respond to requests for current
;;; data (via get-current-value), and respond to receipts of data (via put-
;;; current-value).  Both of these should check the active? slot of the
;;; variable.  If a variable is not active, get-current-value should return
;;; (values nil nil nil) and put-current-value should do nothing.  When the
;;; variable is deactivated, wake-ups on it should be removed (see section on
;;; wake-up in "eval") and there shouldn't be any outstanding tasks for it.
;;; Histories will persist however; histories shouldn't be cleared when a
;;; variable is de-activated.

;;; The notion of a variable being active is distinct from the notion of a
;;; sensor variable being "on".  A sensor variable may be "turned on" if data is
;;; requested from it.  In this case, the interface will collect data for it and
;;; keep the value current for some period of time.  The details of this are
;;; handled by get-current-value which uses information in the sensor frame of
;;; the sensor variable.

;;; The class definition for simulation-subtable has been moved here from
;;; "simulate" because some of the slots are used in this file and therefore the
;;; macros for the slots have to be defined here.


(def-substitute-for-old-class simulation-frame simulation-subtable)


(def-class (simulation-subtable (item block) (foundation-class simulation-subtable)
                                define-predicate not-normally-transient)

  (tracing-and-breakpoints
    nil system lookup-slot save user-overridable (type tracing-and-breakpoints))

  (time-increment-for-update? nil (type simulation-time-increment?)
                              vector-slot system user-overridable save)
  ;; time-increment-for-update? specifies the time between updates of this
  ;; variable.  If this is nil, then the default time increment specified in
  ;; simulation-parameters will be used.  It seems easier to put this time
  ;; increment on variables but they could alternatively be put on the
  ;; simulation computation methods.

  (simulation-formulas? nil (type specific-simulation-formula? text)
                        vector-slot system)

  (exact-solution-computation-method? nil ; (type text exact-solution)
                                      vector-slot system)
  ;; This is only applicable for state variables.  If the user can supply an
  ;; analytic solution for the state variable as a function of time only, then
  ;; the expression can be put here and if the integration method is 'exact
  ;; (rather than 'euler or 'rk4), this expression will be used to calculate the
  ;; value of the state variable.

  (delay-interval-for-sending-value-to-inference-engine 0 vector-slot system)
  ;; Used in conjunction with previous two slots to simulate delays in the data
  ;; acquisition system.

  (simulation-stored-histories? nil vector-slot system)
  (simulation-stored-history-specification? nil (type history-specification)
                                            vector-slot system user-overridable)
  ;; The simulation history slots are similar to those for variables.  Note that
  ;; if histories of simulated values are to be kept, a simulation frame must
  ;; exist for the variable.

  (parent-variable nil vector-slot system save do-not-clone)
  ;; Parent-variable is a backpointer to the variable whose simulation-details
  ;; slot contains the simulation-subtable.

  (simulation-subtable-byte-code-body nil vector-slot save)
  (simulation-subtable-initial-value-byte-code-body nil vector-slot save))

;; Byte-code-bodies are slot values and therefore don't need reclaimers.



;;; Referenced in FILES

(defun parent-variable-function (simulation-subtable)
  (parent-variable simulation-subtable))

;;; Simulation-class is now simulation-category? in the variable frame.
;;; Initial-value-for-simulation? is now initial-simulated-value?  in the
;;; variable frame.  Absent slot putters for these are defined below.

(def-absent-slot-putter simulation-class (simulation-subtable value)
  simulation-subtable value)

(def-absent-slot-putter initial-value-for-simulation? (simulation-subtable value)
  simulation-subtable value)


;;; A number of slots used only at run time have been moved from
;;; simulation-subtable to variable-simulation-runtime-structure defined below.
;;; Since these slots are now absent in existing knowledge bases,
;;; absent slot putters are defined for them.

(def-absent-slot-putter simulation-value (simulation-subtable value)
  simulation-subtable value)
(def-absent-slot-putter simulation-value-time (simulation-subtable value)
  simulation-subtable value)
(def-absent-slot-putter new-simulation-value (simulation-subtable value)
  simulation-subtable value)
(def-absent-slot-putter new-simulation-value-time (simulation-subtable value)
  simulation-subtable value)
(def-absent-slot-putter new-simulation-value-step (simulation-subtable value)
  simulation-subtable value)
(def-absent-slot-putter k1-value (simulation-subtable value)
  simulation-subtable value)
(def-absent-slot-putter k2-value (simulation-subtable value)
  simulation-subtable value)
(def-absent-slot-putter k3-value (simulation-subtable value)
  simulation-subtable value)
(def-absent-slot-putter k4-value (simulation-subtable value)
  simulation-subtable value)
(def-absent-slot-putter time-of-next-update (simulation-subtable value)
  simulation-subtable value)
(def-absent-slot-putter interval-at-which-to-send-value-to-inference-engine
                        (simulation-subtable value)
  simulation-subtable value)
(def-absent-slot-putter last-time-value-sent-to-inference-engine
                        (simulation-subtable value)
  simulation-subtable value)



(def-structure (simulation-info)
  (runtime-info? nil)
  (simulation-category nil)
  (initial-value? nil :reclaimer reclaim-slot-value)
  (specific-time-increment? nil :reclaimer reclaim-slot-value)
  (generic-formula? nil)
  (specific-formula? nil)
  (external-simulation-definition? nil)
  (model-definition? nil)
  (installation-set-next? nil)
  (installation-set-previous? nil)
  (variable-for-simulation-info nil)
  (rederive-set-next? nil)
  (rederive-set-previous? nil)
  (generic-formula-focal-entity? nil)
  (variable-has-subtable-p nil))



(def-substitution-macro simulation-runtime-information? (variable-or-parameter)
  (let ((simulation-info? (simulation-info? variable-or-parameter)))
    (when simulation-info? (runtime-info? simulation-info?))))

(def-substitution-macro set-simulation-runtime-information?
                        (variable-or-parameter value)
  (let ((simulation-info? (simulation-info? variable-or-parameter)))
    (when simulation-info? (setf (runtime-info? simulation-info?) value))))

;; Note that this does nothing if simulation-info?  does not exist.  Thus, it
;; could not be the set function for a defsetf for
;; simulation-runtime-information?; some more work would have to be done for this.

(def-substitution-macro simulation-category? (variable-or-parameter)
  (let ((simulation-info? (simulation-info? variable-or-parameter)))
    (when simulation-info? (simulation-category simulation-info?))))

(def-substitution-macro initial-simulated-value? (variable-or-parameter)
  (let ((simulation-info? (simulation-info? variable-or-parameter)))
    (when simulation-info? (initial-value? simulation-info?))))

(def-substitution-macro formula-specified-time-increment-for-update?
                        (variable-or-parameter)
  (let ((simulation-info? (simulation-info? variable-or-parameter)))
    (when simulation-info? (specific-time-increment? simulation-info?))))





(def-structure (variable-simulation-runtime-structure
                 (:reclaimer
                   reclaim-variable-simulation-runtime-structure-internal))
  (simulation-value nil :reclaimer reclaim-managed-number-or-value)
  (new-simulation-value nil :reclaimer reclaim-managed-number-or-value)
  (k1-value nil)
  (k2-value nil)
  (k3-value nil)
  (k4-value nil)
  (step1-value nil)
  (step2-value nil)
  (step3-value nil)
  (step4-value nil)
  ;; k values for Runge-Kutta integration algorithm.  Only k1 is used for euler
  ;; integration algorithm.

  (time-increment-group nil)
  ;; This slot contains a gensym corresponding to the group of variables
  ;; with the same time increment as this one (see also
  ;; variable-group-update-structure).

  (new-value-computed-for-current-simulation-cycle? nil)
  ;; This flag is used by simulation evaluators to check if a
  ;; new-simulation-value has already been computed for the current cycle.

  (update-variable-this-cycle? nil)
  ;; This flag indicates whether the variable is being updated this cycle
  ;; (thus eliminating the need to compute this more than once).

  (interval-at-which-to-send-value-to-inference-engine nil)
  ;; Used for sensor variables to mimic the behavior of the data acquisition
  ;; system in periodically sending values.

  (last-time-value-sent-to-inference-engine nil
                                            :reclaimer reclaim-possible-managed-float)
  ;; Used in conjunction with previous slot.  'Long-time-ago is a valid value
  ;; for this slot.

  (corresponding-variable nil)  ; backpointer to variable
  (runtime-formula nil)
  (supporting-structures nil :reclaimer reclaim-eval-list)   ; for sorting dependent variables
  (sort-flag nil)   ; for sorting dependent-variables
  (runtime-cache? nil :reclaimer reclaim-simulation-runtime-cache)
  (simulation-formula nil)
  (initial-value-simulation-environment-vector?
    nil :reclaimer reclaim-simulation-runtime-cache)
  (variable-needs-simulated-value? nil)
  (value-of-variable-tainted? nil)
  (variable-needs-initialization? nil)
  )

(defun set-last-time-value-sent-to-inference-engine (variable new-value)
  #+development
  (when (fixnump new-value)
    (break "No fixnums for last time value"))
  (let ((old-value (last-time-value-sent-to-inference-engine variable)))
    (cond
      #+development
      ((managed-float-p new-value)
       (break "no managed floats as new values"))
      ((gensym-float-p new-value)
       (cond ((managed-float-p old-value)
              (mutate-managed-float-value old-value  new-value))
             (t
              (setf
                (last-time-value-sent-to-inference-engine variable)
                (allocate-managed-float new-value)))))
      (t
       (when (managed-float-p old-value)
         (reclaim-managed-float old-value))
       (setf
         (last-time-value-sent-to-inference-engine variable) new-value)))))


(defun get-or-make-simulation-runtime-cache
       (simulation-environment-vector-length runtime-structure
        environment-for-initial-value?)
  (let ((existing-simulation-environment-vector?
          (if environment-for-initial-value?
              (initial-value-simulation-environment-vector? runtime-structure)
              (runtime-cache? runtime-structure))))
    (cond
      ((null existing-simulation-environment-vector?)
       (set-simulation-environment-vector
         runtime-structure simulation-environment-vector-length
         environment-for-initial-value?))
      ((=f (length existing-simulation-environment-vector?)
           simulation-environment-vector-length)
       existing-simulation-environment-vector?)
      (t
       (reclaim-simulation-runtime-cache
         existing-simulation-environment-vector?)
       (set-simulation-environment-vector
         runtime-structure simulation-environment-vector-length
         environment-for-initial-value?)))))

(defun set-simulation-environment-vector
       (runtime-structure length environment-for-initial-value?)
  (if environment-for-initial-value?
      (setf (initial-value-simulation-environment-vector? runtime-structure)
            (allocate-environment-vector length))
      (setf (runtime-cache? runtime-structure)
            (allocate-environment-vector length))))

(defun reclaim-simulation-runtime-cache (simulation-runtime-cache?)
  (when simulation-runtime-cache?
    (reclaim-environment-vector simulation-runtime-cache?)))





;(def-absent-slot-putter sensor-frame? (sensor sensor-frame)
;  (declare (ignore  sensor))
;  (when sensor-frame
;    (setf (sensor-collection-interval? sensor)
;         (*sensor-collection-interval? sensor-frame))
;    (delete-frame sensor-frame)))

;(def-absent-slot-putter sensor-collection-interval? (sensor-frame interval)
;  (setf (*sensor-collection-interval? sensor-frame) interval))

;;; When a request for data is made, a task is scheduled for some time in the
;;; future to check if the sensor has failed.  If the request is not "one shot",
;;; the sensor is "turned on" and a task is scheduled for some time in the
;;; future to check if it should be turned off.  When data is received, the task
;;; which checks if the sensor has failed should be rescheduled further into the
;;; future (if it has not been invoked yet).  When a new request is received,
;;; the task which checks if the sensor should be turned off must be rescheduled
;;; (if it has not been invoked).  If the sensor is turned off, the task which
;;; checks if it has failed should be canceled.  There may be a better way to
;;; check if a sensor has failed than scheduling individual tasks.









;; Subsection "Putting and Reclaiming Attribute Values" has been moved to module
;; INSTALL, in which macros it depended on were defined. (MHD 7/15/87)






;;;; Data Servers



;;; Data acqusition should be same whether getting data externally or from
;;; simulator.  Data servers structures provide the following slots,
;;;
;;;   name-of-data-server containing a symbol uniquely naming this data server,
;;;
;;;   function-to-collect-one-shot-data containing a symbol which names a
;;;   function of one argument which takes a variable and causes a value to be
;;;   collected for that variable,
;;;
;;;   function-to-begin-collecting-data containing a symbol naming a function of
;;;   one argument which takes a variable and will cause data to begin to be
;;;   collected for this variable at regular intervals,
;;;
;;;   function-to-stop-collecting-data containing a symbol naming a function of
;;;   one argument which will cause any regular data collection for this
;;;   variable to be stopped,
;;;
;;;   function-to-accept-data containing a symbol naming a function of no
;;;   arguments which will cause any queued up data for this server to be set
;;;   into G2 via put-current-value,
;;;
;;;   server-is-in-use containing a T or NIL depending on whether this server is
;;;   in active use,
;;;
;;;   function-to-initialize-data-server containing a symbol naming a function
;;;   of no arguments which will be called whenever G2 is started,
;;;
;;;   function-to-set-external-variable containing a symbol naming a function of
;;;   three arguments.  The first argument is a variable, and the second is a
;;;   value that this external variable should receive, and the third argument
;;;   is the datum type of the value.  This function should not reclaim the
;;;   given value, but should copy it if the value will be retained after this
;;;   function returns.
;;;
;;;   function-to-shut-down-data-server? containing NIL or a symbol naming a
;;;   function of no arguments to call when G2 is being shut down,
;;;
;;;   function-to-deliver-messages contains a symbol naming a function with the
;;;   following arguments:  (1) message (a text-string to process and yours to
;;;   reclaim, (2) urgency? not yet used, (3) duration? (nil or a number in
;;;   seconds), (4) inference-frame (the rule that sent the message
;;;   function-to-deliver-messages), and (5) destination (the object the message
;;;   was send to),
;;;
;;;   function-to-pause-data-server? contains NIL or a symbol naming a function
;;;   of no arguments which will be called whenever G2 is paused, and
;;;
;;;   function-to-resume-data-server? contains NIL or a symbol naming a function
;;;   of no arguments which will be called whenever G2 is resumed after being
;;;   paused.
;;;
;;;   function-to-request-accept-data? contains T, NIL, or a symbol naming a
;;;   function.  If T, accept data should be called every second for this data
;;;   server.  If NIL, accept data should never be called for this data server.
;;;   If it is a symbol other than T or NIL, it should name a function of no
;;;   arguments that will return T when accept data needs to be called and NIL
;;;   when accept data does not need to be called for this data server.  When a
;;;   function is provided, if this data server ever transitions from not
;;;   needing accept data to needing accept data, then the function
;;;   schedule-data-server-accept-data-calls must be called to ensure that
;;;   accept datas are still being sent.

;;; These operations are accessed through sensor variables when they are
;;; responding to the operations get-current-value and put-current-value, and
;;; when G2 is being started, paused, resumed, or halted.






;;; The variable `global-list-of-all-data-servers' is used to hold the global
;;; list of all data servers that have been defined.  Copies of these data
;;; servers are made for each process and kept in the list-of-all-data-servers
;;; system variable, which is defined in schedule.

;;; The kb specific property `data-server' used to provide a mapping between
;;; names and aliases of data servers and the structures that represent them.
;;; They are presently initialized in each kb by
;;; `initialize-data-server-properties', which is called from
;;; switch-to-new-empty-kb.  They are then updated and maintained by the slot
;;; putter for data-server-aliases of the data-server-parameters system frame.

;; USE KB-SPECIFIC VARIABLES IN ADDITION TO OR IN LIEU OF DATA-SERVER
;; PROPERTIES!!!



(defvar global-list-of-all-data-servers nil)

(def-kb-specific-property-name data-server)

(def-kb-specific-property-name data-server-or-alias?)



;;;; Data Server Structures

(def-system-variable list-of-all-data-servers variables
  (:funcall copy-data-servers-for-process) t nil)

(def-structure (data-server
                 (:constructor
                   make-data-server
                   (name-of-data-server
                     function-to-collect-one-shot-data
                     function-to-begin-collecting-data
                     function-to-stop-collecting-data
                     function-to-accept-data
                     server-is-in-use
                     function-to-initialize-data-server
                     function-to-set-external-variable
                     function-to-shut-down-data-server?
                     function-to-deliver-messages
                     function-to-pause-data-server?
                     function-to-resume-data-server?
                     function-to-request-accept-data?
                     function-to-start-data-server?
                     function-to-reset-data-server?)))
  name-of-data-server
  function-to-collect-one-shot-data
  function-to-begin-collecting-data
  function-to-stop-collecting-data
  function-to-accept-data
  (server-is-in-use nil)

  ;; Required function of no args called when user selects START.
  function-to-initialize-data-server

  function-to-set-external-variable

  ;; Optional function of no args is called when user selects RESET.
  (function-to-shut-down-data-server? nil)

  ;; Required function: Args are (1) message (a text-string to process and yours
  ;; to reclaim, (2) urgency? not yet used, (3) duration? (nil or a number in
  ;; seconds), (4) inference-frame (the rule that sent the message
  ;; function-to-deliver-messages) (5) destination (the object the message was
  ;; send to)
  function-to-deliver-messages

  ;; An optional function of no args is called when user selects the PAUSE
  ;; option.
  (function-to-pause-data-server? nil)

  ;; An optional function of no args is called when user selects the RESUME
  ;; option.
  (function-to-resume-data-server? nil)

  ;; The location of the task which accepts data for the dataserver.
  (task-to-accept-data nil) ;Added slot.  jh, 4/30/91.

  function-to-request-accept-data?

  ;; An optional function of no args is called when user selects the START
  ;; for servers that can run while inactive (a 5.0 feature)
  (function-to-start-data-server? nil)

  ;; An optional function of no args is called when user selects the RESET
  ;; for servers that can run while inactive. (a 5.0 feature)
  (function-to-reset-data-server? nil))



;;; The function `initialize-data-server-properties' is used to bind the names
;;; of existing data servers to their true names upon creation of a new
;;; knowledge base environment, and to create copies of the data server objects
;;; to be used for this process and kb.



(defun initialize-data-server-properties ()
  (setf (data-server 'computation) 'computation)
  (setf (data-server-or-alias? 'computation) 'computation)
  (loop for data-server in list-of-all-data-servers
        for name = (name-of-data-server data-server)
        do
    (setf (data-server name) data-server)
    (setf (data-server-or-alias? name) data-server)))




;;; The function `copy-data-servers-for-process' returns a newly consed list of
;;; copies of the data servers in the global-list-of-all-data-servers.  This
;;; function is called to initialize the system variable
;;; list-of-all-data-servers.


(defun copy-data-servers-for-process ()
  (loop for data-server in global-list-of-all-data-servers
        collect (copy-data-server data-server) using gensym-cons))




;;; Data server structures should be created by calling the macro
;;; `def-data-server'.  This will create the data structure and install it into
;;; the data server naming and aliasing system.


(defun def-data-server
       (name-of-data-server
        function-to-collect-one-shot-data
        function-to-begin-collecting-data
        function-to-stop-collecting-data
        function-to-accept-data
        server-is-in-use
        function-to-initialize-data-server
        function-to-set-external-variable
        function-to-shut-down-data-server?
        function-to-deliver-messages
        function-to-pause-data-server?
        function-to-resume-data-server?
        function-to-request-accept-data?
        &optional
        function-to-start-data-server?
        function-to-reset-data-server?)
  (let ((new-server
          (make-data-server
            name-of-data-server
            function-to-collect-one-shot-data
            function-to-begin-collecting-data
            function-to-stop-collecting-data
            function-to-accept-data
            server-is-in-use
            function-to-initialize-data-server
            function-to-set-external-variable
            function-to-shut-down-data-server?
            function-to-deliver-messages
            function-to-pause-data-server?
            function-to-resume-data-server?
            function-to-request-accept-data?
            function-to-start-data-server?
            function-to-reset-data-server?)))

    ;; Add this data server to the global-list-of-all-data-servers, replacing
    ;; any old data server with the same name.  Note that this function should
    ;; only be called at load time of G2, so it's OK to cons with a call to
    ;; push.
    (loop for data-server-cons on global-list-of-all-data-servers
          do
      (when (eq (name-of-data-server (car data-server-cons))
                name-of-data-server)
        (setf (car data-server-cons) new-server)
        (return nil))
          finally
            (push new-server global-list-of-all-data-servers)) ))


;;; The function `def-data-server-pretty-printer' defines a pretty name for the
;;; given named data server.  This will cause the slot value writer for
;;; data-server-map to print the pretty name instead of the symbol.  Note that
;;; you still need to define the grammar which turns this pretty name into the
;;; given symbol name.


(defvar data-server-pretty-name-alist nil)

(defun def-data-server-pretty-printer
       (data-server-symbol-name data-server-pretty-string-name)
  (let ((pretty-name-entry (assq data-server-symbol-name
                                 data-server-pretty-name-alist)))
    (if pretty-name-entry
        (setf (cdr pretty-name-entry) data-server-pretty-string-name)
        (with-dynamic-creation
          (setq data-server-pretty-name-alist
                (cons
                  (cons data-server-symbol-name
                        data-server-pretty-string-name)
                  data-server-pretty-name-alist))))))


(defun copy-data-server (data-server)
  (make-data-server
    (name-of-data-server data-server)
    (function-to-collect-one-shot-data data-server)
    (function-to-begin-collecting-data data-server)
    (function-to-stop-collecting-data data-server)
    (function-to-accept-data data-server)
    (server-is-in-use data-server)
    (function-to-initialize-data-server data-server)
    (function-to-set-external-variable data-server)
    (function-to-shut-down-data-server? data-server)
    (function-to-deliver-messages data-server)
    (function-to-pause-data-server? data-server)
    (function-to-resume-data-server? data-server)
    (function-to-request-accept-data? data-server)
    (function-to-start-data-server? data-server)
    (function-to-reset-data-server? data-server)))




;;; Get-data-server is a macro that finds the data-server for a variable.
;;; Data servers are found by looking up the data-server-or-alias?  property
;;; of the symbol found in the data-server-map slot of a variable.  This
;;; function will return either a data server or NIL, and if it has returned
;;; NIL it will already have issued a warning message about the undefined
;;; data server reference.


(def-substitution-macro get-data-server (variable)
  (let* ((source-or-map (data-server-map variable))
         (server?
           (if (atom source-or-map)
               (data-server-or-alias? source-or-map))))
    (if server?
        server?
        (warn-of-undefined-data-server variable source-or-map))))

(defun warn-of-undefined-data-server (variable data-server-map)
  (write-warning-message 1
    (tformat "The data server specified for ~NF is " variable)
    (write-data-server-map-from-slot data-server-map nil)
    (twrite ", which is not a defined data server or data server alias."))
  nil)






(defmacro collect-one-shot-data (data-server variable)
  `(funcall-symbol (function-to-collect-one-shot-data ,data-server) ,variable))

(defmacro begin-collecting-data (data-server variable collection-interval)
  `(funcall-symbol (function-to-begin-collecting-data ,data-server)
                   ,variable ,collection-interval))

(defmacro stop-collecting-data (data-server variable)
  `(funcall-symbol (function-to-stop-collecting-data ,data-server)
                   ,variable))


(defun-void notify-data-server-of-start-or-reset (start-p)
  (loop for server in list-of-all-data-servers
        for function? = (if start-p
                            (function-to-start-data-server? server)
                            (function-to-reset-data-server? server))
        do
    (if function? (funcall-symbol function?))))


;;; The new macro `halt-data-service' is called to inform a data server that
;;; it is no longer the data server for a given variable.  The data server
;;; should drop all references to the variable and reclaim all data structures
;;; relating to it.  It also prohibits the data server from supplying any more
;;; values for this variable.

;;; Note, at the present time we do not have a true halt-data-collection
;;; function in the data server definition.  It will be added presently, before
;;; release 2.0.  For the time being, this functionality will be stubbed by
;;; stop-collecting-data.  -jra 3/29/89

(def-substitution-macro halt-data-service (data-server variable)
  (if (eq data-server 'computation)
      (withdraw-backward-chaining variable)
      (funcall-symbol (function-to-stop-collecting-data data-server)
                      variable)))




;;; The slot putter for the data-server-map slot of variables should check if
;;; the variable is active, and if so should make sure that the current data
;;; server for the variable is no longer collecting data for this sensor, and
;;; that if there is a background collection interval it gets going for the new
;;; data server.


(def-slot-putter data-server-map (variable new-data-server-map)
  (cond ((active-p variable)
         (let ((old-data-server? (get-data-server variable)))
           (cond ((data-server-p old-data-server?)
                  (stop-collecting-data old-data-server? variable))
                 ((eq old-data-server? 'computation)
                  (stop-collecting-data-for-inference-engine variable))))
         (without-consistency-analysis (variable)
             (setf (data-server-map variable) new-data-server-map))
         (let ((collection-interval?
                 (background-collection-interval? variable)))
           (if collection-interval?
               (let ((new-data-server? (get-data-server variable)))
                 (cond ((data-server-p new-data-server?)
                        (begin-collecting-data
                          new-data-server? variable collection-interval?))
                       ((eq new-data-server? 'computation)
                        (begin-collecting-data-for-inference-engine
                          variable collection-interval?))))))
         new-data-server-map)
        (t
         (without-consistency-analysis (variable)
           (setf (data-server-map variable) new-data-server-map)))))




;;; The function `data-server-requests-accept-data-calls' takes a data server
;;; and returns whether or not that data server needs to have have accept data
;;; called for it.

(defun-simple data-server-requests-accept-data-calls (data-server)
  (let ((function? (function-to-request-accept-data? data-server)))
    (cond ((null function?) nil)
          ((eq function? t) t)
          (t (funcall-symbol function?)))))






;;;; Data Server Aliasing




;;; When in testing mode and the like, users will want to be able to swap
;;; between data servers for variables.  At the moment, there has been a
;;; facility in the system called G2 Modes, which was used to provide switches
;;; that could be referenced inside of if-expressions in a data server map to
;;; provide this swapping.  However, this mechanism required users to write code
;;; into their data server maps to support debugging.  This functionality should
;;; be elevated out of the individual data server maps into a global mapping
;;; facility.

;;; A system table called data-server-parameters is defined which will a
;;; mechanism for redirecting data servers names to go to specific data servers.
;;; These mappings may only be edited when the system is halted.  Note that
;;; their presence does make it possible for a variable to hold a data server
;;; name which is not currently aliased to any data server.  This means that any
;;; code which uses the function get-data-server must be prepared to receive a
;;; NIL.  An error message will have been presented in get-data-server if this
;;; happens.


(def-system-frame data-server-parameters variables
  (data-server-aliases nil system lookup-slot save (type data-server-aliases))
  (priority-of-data-service 4 system vector-slot save (type priority))
  (g2-meter-data-service-on? nil system lookup-slot save (type yes-or-no)) ;; see note with alias
  (gsi-data-server-filters-text? nil system lookup-slot save
                                 ;; Hold off on giving users this feature for
                                 ;; now. (MHD 2/10/92)
                                 ; (type yes-or-no?)
                                 ;; Expunged the feature 12/18/96. See note in Tables
                                 ;; near make-text-for-cell-identifying-attribute-in-table.
                                 ))

;; jh, 12/9/91.  Added gsi-data-server-filters-text?  slot to
;; data-server-parameters.  This allows GSI users a tradeoff between the speed of
;; transmitting text strings "as is" and the safety of filtering out G2-internal
;; escape character sequences (such as @L for #\Newline).

(def-absent-slot-putter priority-of-continued-data-service
                        (data-server-parameters-table new-priority)
  ;; Notify user of change in name and possible change in behavior?
  (change-slot-value
    data-server-parameters-table
    'priority-of-data-service
    new-priority))

(defun-simple g2-priority-of-data-service-function ()
  (priority-of-data-service data-server-parameters))

;; jh, 5/22/91.  Changed the name of priority-of-continued-data-service (in the
;; data-server-parameters system table) to priority-of-data-service.  This is
;; because we always schedule a task to accept data now, rather than scheduling a
;; task only after failing to accept all the data we were supposed to.


(define-slot-alias gsi-data-server-filters-text gsi-data-server-filters-text?)

(define-slot-alias g2-meter-data-service-on g2-meter-data-service-on?)

(add-grammar-rules
  '((data-server-aliases 'none)
    ;;; GENSYM-076: fix corruption when adding 'none after a valid data-server-alias
    ;;; GENSYMCID-1333: previous solution for fixing the corruption is wrong and in 
    ;;;                 this ticket, re-work GENSYM-076 to fix both issues.
    (data-server-aliases list-of-data-server-alias-spec)
    (list-of-data-server-alias-spec data-server-alias-spec)
    (list-of-data-server-alias-spec
      (data-server-alias-spec '\, list-of-data-server-alias-spec)
      (and 1 3) simplify-associative-operation)
    (data-server-alias-spec
      (data-server-map 'implies 'service 'through data-server-spec)
      (1 5) ) ))




(def-class-method install-system-table (data-server-parameters)
  (initialize-or-shut-down-g2-meter-data-server
    (g2-meter-data-service-on? data-server-parameters))
  (absorb-data-server-aliases                        ; just absorbs new
    nil
    (data-server-aliases data-server-parameters)))


(def-class-method deinstall-system-table (data-server-parameters)
  (absorb-data-server-aliases                        ; just deabsorbs old
    (data-server-aliases data-server-parameters)
    nil))





;;; The function `initialize-or-shut-down-g2-meter-data-server' is to be called
;;; in order to reflect the current value of the g2-meter-data-service-on?  slot
;;; of data-server-parameters, with install-case?  = true if the slot is true,
;;; and false otherwise.

;;; This may be called too early in the initialization process of G2 for there
;;; to be a value for (data-server 'g2-meter-data-server).  When that is true,
;;; this does nothing.  (Presumably, it will not matter because the system
;;; could not have been started, and the initialization will happen then.

(defun initialize-or-shut-down-g2-meter-data-server (install-case?)
  (let ((data-server? (data-server 'g2-meter-data-server)))
    (when data-server?
      (if install-case?
          (when (or system-is-running system-has-paused)
            (funcall-symbol
              (function-to-initialize-data-server
                (data-server 'g2-meter-data-server))))
          (let ((function-to-shut-down-data-server?
                  (function-to-shut-down-data-server?
                    (data-server 'g2-meter-data-server))))
            (if function-to-shut-down-data-server?
                (funcall-symbol function-to-shut-down-data-server?)))))))



;;; Slot handling functions for g2-meter-data-service-on? follow:

(def-gensym-c-function c-set-record-waits (:void "g2ext_set_record_waits")
  ((:fixnum-int waitp)))

(def-slot-putter g2-meter-data-service-on? (data-server-parameters-instance new-value)
  (setf (g2-meter-data-service-on? data-server-parameters-instance) new-value)
  (setq record-fixnum-time-units-of-sleep-this-clock-tick? new-value)
  (c-set-record-waits (if new-value 1 0))
  (when (system-table-installed-p data-server-parameters-instance)
    ;; notice that this would initialize/shut down more than once
    ;;   if called with new-value = true/false more than once
    (initialize-or-shut-down-g2-meter-data-server new-value))
  new-value)

;; Above definition replaces the old one below, commented out.  The change was
;; made bring the slot putter for g2-meter-data-service-on? into conformance
;; with the new constraint that system tables may not have their side effects
;; unless they're installed.  (MHD 10/15/91)

;(def-slot-putter g2-meter-data-service-on? (data-server-parameters-instance new-value)
;  (let* ((g2-meter-data-server (data-server 'g2-meter-data-server))
;         (function-to-shut-down-g2-meter-data-server?
;           (function-to-shut-down-data-server? g2-meter-data-server)))
;    (setf (g2-meter-data-service-on? data-server-parameters-instance) new-value)
;    (when (and new-value
;             (or system-is-running
;                 system-has-paused))
;      (funcall-symbol
;        (function-to-initialize-data-server g2-meter-data-server)))
;    (when (and (null new-value) function-to-shut-down-g2-meter-data-server?)
;      (funcall-symbol function-to-shut-down-g2-meter-data-server?))))






;;; Slot handling functions for data-server-aliases follow:


(def-slot-value-compiler data-server-aliases (parse-result)
  (cond ((eq parse-result 'none)
         nil)
        ((eq (car parse-result) 'and)
         (loop for alias-cons on (cdr parse-result)
               do (if (assq (caar alias-cons) (cdr alias-cons))
                      (return
                        (values
                          bad-phrase
                          (tformat-text-string
                            "the name ~(~a~) may not be given two alias mappings"
                            (caar alias-cons)))))
               finally
                 (return parse-result)))
        (t
         parse-result)))



(def-slot-value-writer data-server-aliases (data-server-aliases)
  (cond ((null data-server-aliases)
         (twrite "none"))
        ((eq (car data-server-aliases) 'and)
         (loop for alias-cons on (cdr data-server-aliases)
               for alias = (car alias-cons)
               do
           (write-data-server-map-from-slot (first alias) nil)
           (twrite " implies service through ")
           (write-data-server-map-from-slot (second alias) nil)
           (if (cdr alias-cons)
               (twrite ", "))))
        (t
         (progn
           (write-data-server-map-from-slot (first data-server-aliases) nil)
           (twrite " implies service through ")
           (write-data-server-map-from-slot (second data-server-aliases)
                                            nil)))))





;;; The slot putter for data-server-aliases needs to update the data-server-or-
;;; alias? kb-specific properties of the alias names given.  It first determines
;;; how the aliases have changed by generating a list of new, changed, and
;;; removed aliases.  If the system is running, make a list of the currently
;;; active variables which use any of the aliases in the new and old list, along
;;; with their current data server.  It will then remove any aliases in the old
;;; list but not mentioned in the new, then add the new values of the changed
;;; and the totally new aliases.  Finally, for each variable using an affected
;;; alias, if the data server has actually changed for the variable it will halt
;;; data service for the old data server.  If it also has a default update
;;; interval, begin collecting data is called on that variable.  If it has no
;;; background collection, but does have existing requests for its value, then
;;; we will make a one shot collect request.

;;; We will not be reinstating one shots for variables whose data server is the
;;; symbol computation.  These are inference engine variables, and we'll wait to
;;; reinstate this until the inference engine has been made a full-fledged data
;;; server.

;;; If a new alias is defined which redirects to a name for which there is no
;;; data server, we will still make the assignment, but notify the user that
;;; this has occurred.

(def-slot-putter data-server-aliases
                 (data-server-parameters-instance new-aliases initializing?)
  (when (system-table-installed-p data-server-parameters-instance)
    (absorb-data-server-aliases
      (if (not initializing?)
          (data-server-aliases data-server-parameters-instance))
      new-aliases))
  ;; Set the value into the frame.
  (setf (data-server-aliases data-server-parameters-instance) new-aliases))

;; Changed the above by pulling out most of its contents into the function
;; below, so that it can be called both from the putter, when the system
;; table is installed, and from the install- and deinstall-system-table
;; methods. (MHD 10/15/91)
;; -- Changed formal parameter name to have "-instance" suffix in the slot
;; putters.  Part of general bug fix.  See comment/discussion in BOOKS with
;; this stamp: (MHD 6/30/93)





;;; The function `absorb-data-server-aliases' is called by the putter for
;;; data-server-aliases and the install-/deinstall-system-table methods for
;;; data-server-parameters.

(defun absorb-data-server-aliases (old-aliases new-aliases)
  (let* ((old-alias-list
           (cond ((null old-aliases) nil)
                 ((eq (car old-aliases) 'and)
                  (copy-list-using-eval-conses (cdr old-aliases)))
                 (t (eval-list old-aliases))))
         (new-alias-list
           (cond ((null new-aliases) nil)
                 ((eq (car new-aliases) 'and)
                  (copy-list-using-eval-conses (cdr new-aliases)))
                 (t (eval-list new-aliases))))
         (undefined-data-server-names nil)
         data-server-structure
         notification-text-string
         (aliases-to-remove nil)
         (aliases-to-add (copy-list-using-eval-conses new-alias-list))
         (affected-variables nil))
    ;; Determine the changes called for in this edit.
    (loop for old-alias-spec in old-alias-list
          for new-spec? = (assq (car old-alias-spec) aliases-to-add)
          do
      (cond ((null new-spec?)
             (setq aliases-to-remove
                   (eval-cons old-alias-spec aliases-to-remove)))
            ((eq (second old-alias-spec) (second new-spec?))
             (setq aliases-to-add
                   (delete-eval-element new-spec? aliases-to-add)))))
    ;; If the system is running or paused, find those active variables using the
    ;; changing aliases and add them and their current data servers on the
    ;; affected variables list.
    (when (or system-is-running system-has-paused)
      (loop for variable being each class-instance of 'variable
            do
        (when (active-p variable)
          (let ((server-map (data-server-map variable)))
            (when (or (assq server-map aliases-to-add)
                      (assq server-map aliases-to-remove))
              (setq affected-variables
                    (eval-cons (eval-cons variable (get-data-server variable))
                               affected-variables)))))))
    ;; Remove old aliases.
    (loop for (old-alias) in aliases-to-remove
          do (setf (data-server-or-alias? old-alias) (data-server old-alias)))
    ;; Add the new aliases.
    (loop for alias in aliases-to-add
          do
      (setq data-server-structure (data-server (second alias)))
      (if (null data-server-structure)
          (setq undefined-data-server-names
                (gensym-cons (second alias) undefined-data-server-names)))
      (setf (data-server-or-alias? (first alias)) data-server-structure))
    ;; If the data servers have changed for any of the listed affected
    ;; variables, halt data service for the old data server, and either start
    ;; background collection or instigate a one shot if either is called for.
    (loop for affected-entry in affected-variables
          for variable = (car affected-entry)
          for old-data-server? = (cdr affected-entry)
          for new-data-server? = (get-data-server variable)
          do
      (reclaim-eval-cons-macro affected-entry)
      (when (neq old-data-server? new-data-server?)
        (when old-data-server?
          (halt-data-service old-data-server? variable))
        (let ((interval? (background-collection-interval? variable)))
          (cond (interval?
                 (cond ((data-server-p new-data-server?)
                        (begin-collecting-data
                          new-data-server? variable interval?))
                       ((eq new-data-server? 'computation)
                        (begin-collecting-data-for-inference-engine
                          variable interval?))))
                ((and (things-interested-in-this-variable variable)
                      (data-server-p new-data-server?))
                 (collect-one-shot-data new-data-server? variable))))))
    ;; Notify the engineer of any undefined aliases.
    (cond ((and undefined-data-server-names (cdr undefined-data-server-names))
           (setq notification-text-string
                 (twith-output-to-text-string
                   (twrite
                     "Within the data server aliases just defined, note that")
                   (loop for name-cons on undefined-data-server-names
                         for name = (car name-cons)
                         do (twrite " ")
                            (write-data-server-map-from-slot name nil)
                            (if (cdr name-cons)
                                (progn
                                  (if (/=f (length undefined-data-server-names) 2)
                                      (twrite ","))
                                  (if (null (cddr name-cons))
                                      (twrite " and")
                                      (twrite " ")))))
                   (twrite "are not defined data servers.")))
           (notify-engineer notification-text-string)
           (reclaim-text-string notification-text-string)
           (reclaim-gensym-list undefined-data-server-names))
          (undefined-data-server-names
           (setq notification-text-string
                 (twith-output-to-text-string
                   (twrite
                     "Within the data server aliases just defined, note that ")
                   (write-data-server-map-from-slot
                     (car undefined-data-server-names) nil)
                   (twrite " is not a defined data server.")))
           (notify-engineer notification-text-string)
           (reclaim-text-string notification-text-string)
           (reclaim-gensym-cons undefined-data-server-names)))
    ;; Reclaim all the incremental data structures created in this slot putter.
    (reclaim-eval-list-macro old-alias-list)
    (reclaim-eval-list-macro new-alias-list)
    (reclaim-eval-list-macro aliases-to-add)
    (reclaim-eval-list-macro aliases-to-remove)
    (reclaim-eval-list-macro affected-variables)))






;;;; Notes On Data Acquisition Interface




;;; These are some old notes on data service.

;;; Messages to be received should include begin-collecting-data and
;;; stop-collecting-data.  These can be implemented as functions
;;; Begin-collecting-data should take a variable and a collection interval as
;;; arguments.  Stop-collecting-data takes a variable as an argument.  Messages
;;; to be sent should include put-current-value and error-getting-value.
;;; Put-current-value should have arguments variable, value, and
;;; collection-time.  Error-getting-value should have arguments variable and
;;; error-type.

;;; Brian mentioned that block data acquisition is a common and useful thing for
;;; many interfaces.  This could be handled in a variety of ways.

;;; 1.  If a variable contains a value which is an array or structure data type,
;;; then this entire value could be acquired in block mode.  Special operators
;;; would then be used by the inference engine to access parts of the array or
;;; structure.

;;; 2.  The data acquisition interface should make use of the dynamic variable
;;; earliest-valid-data-time to decide whether to make another block collection
;;; or just pass back the existing value with the time when it was collected.
;;; Earliest-valid-data-time must be recent enough to ensure that the returned
;;; value will be current.






;;;; Removing Requests for Variables



;;; When a call is made to get-current-value and the value is not able to be
;;; supplied, data requests or backward chaining may be started on the variable
;;; to get a value.  If the requestor no longer needs the value of this
;;; variable, it will call remove-request-for-variable-value, or
;;; remove-request-for-variable-value-without-clean-up and then
;;; perform-postponed-variable-clean-up.  If a variable is backward chaining and
;;; the last thing interested in the value of this variable removes its request,
;;; then backward chaining should be stopped for this variable, and it should
;;; remove any requests from things it is interested in.

(def-substitution-macro remove-request-for-variable-value (variable thing)
  (let ((pruned-interest-list
          (delete-eval-element
            thing (things-interested-in-this-variable variable))))
    (setf (things-interested-in-this-variable variable) pruned-interest-list)
    (if (and (null pruned-interest-list)
             (null (thing-postponing-clean-up? variable)))
        (withdraw-backward-chaining variable))))

(def-substitution-macro remove-request-for-variable-value-without-clean-up
                        (variable thing)
  (setf (things-interested-in-this-variable variable)
        (delete-eval-element
          thing (things-interested-in-this-variable variable)))
  (when (null (thing-postponing-clean-up? variable))
    (setf (thing-postponing-clean-up? variable) thing)))

(def-substitution-macro perform-postponed-variable-clean-up (variable thing)
  (when (eq (thing-postponing-clean-up? variable) thing)
    (setf (thing-postponing-clean-up? variable) nil)
    (if (null (things-interested-in-this-variable variable))
        (withdraw-backward-chaining variable))))






;;;; Requesting Values of Variables




;;; Wake Up List Management

;;; A network of `wake up lists' or `interest lists' are kept within G2 to
;;; control the data seeking and backward chaining processes.  There are two
;;; kinds of instances in this network.  First there are instances which can
;;; cause requests for evaluation, which will be called requestors.  Secondly
;;; there are instances which perform evaluations on behalf of the requestors,
;;; which will be called evaluators.  Currently (-jra 7/11/90) there are six
;;; kinds of requestors:
;;;
;;;   1. rule instances, 
;;;   2. code-body-invocations for procedures,
;;;   3. displays,
;;;   4. inter-g2-data-request structures for G2 to G2 data servers,
;;;   5. variables for backward chaining,
;;;   6. inference-background-collections for default update intervals.
;;;
;;; There are two kinds of evaluators:
;;;
;;;   1. variables
;;;   2. rule-instances.
;;;   3. (It is likely that code body invocations will be added to the list of
;;;       evaluators when we add backward chaining to procedures.)
;;;
;;; Any requestor can ask for the value of a variable, but only variables (type 5)
;;; can be the instance interested in the evaluation of a rule instance (because
;;; of backward chaining).

;;; When some requestor wants to have an ongoing request be registered for an
;;; evaluator, this instance must have itself listed in the
;;;
;;;   * things-interested-in-this-variable slot of the variable, or the
;;;   * things-interested-in-this-rule-instance list of the rule-instance, and
;;;
;;; the instance must itself keep a list of things that it is interested in.  As
;;; long as there is an outstanding request for the execution of an evaluator,
;;; it will continue to be scheduled for processing.  If there are no
;;; outstanding requests for an evaluator, then all processing for it should be
;;; withdrawn.  Note that the inference engine is the only data server for which
;;; this withdraw has any effect.  In the future if we add a "stop collecting
;;; data for one shot" function to the data server, it should be called at this
;;; point.  The corresponding function for the inference engine is
;;; withdraw-backward-chaining.  To withdraw all processing for a rule instance,
;;; that instance is removed from the hash table of rule instances for the rule.
;;; Note that the "things-interested-in-this-rule-instance slot is really the
;;; purposes slot of a rule instance.  Purposes such as forward chaining and
;;; scanning can also be on this list.




;;; Current Implementation of Wake Up Management

;;; This network of pointers and backpointers is always kept up to date, with
;;; the single exception being the inclusion of variables on interest lists
;;; during the time that an instance's expression is being evaluated.  The
;;; process of evaluating an instance's expression is managed as follows.  The
;;; evaluating instance is bound to the current-computation-instance global
;;; variable (e.g.  a rule-instance or code-body-invocation), and some frame
;;; representing that instance (a rule or procedure-invocation) is bound into
;;; current computation frame for printing error messages.  On entry to the
;;; evaluation function, the existing interest list requests are removed from
;;; variables, but postponing clean ups.  The item postponing clean up is noted,
;;; and only that item can actually invoke the postponed clean up.  This is done
;;; since evaluations can be entered recursively, and the outermost instance
;;; postponing clean-up should be the only one which can release the
;;; postponement.  This removal of wake ups and execution of postponed wake ups
;;; is performed by the macro remove-wake-ups-postponing-clean-up.

;;; Next the evaluation of the expression is entered.  This will call
;;; get-current-value on variables needing values.  If any variables are unable
;;; to supply values during this evaluation, then they are placed onto the
;;; global *variables-that-did-not-have-values* list, and the variable's list of
;;; things interested in it is marked with the symbol 'value-request-pending.
;;; On exit from the evaluation function, if the expression returned a useful
;;; value, or if the evaluation is to be given up, then the list of
;;; *variables-that-did-not-have-values* is reclaimed, removing the
;;; value-request-pending marker from their interest lists.  If the evaluation
;;; did not return a value and wake ups are to be set, then the current
;;; computation instance gets its things-this-instance-is-interested-in slot set
;;; to the list of *variables-that-did-not-have-values*, and the
;;; value-request-pending marker is replaced with a pointer to the current
;;; computation instance.  This manipulation of wake up lists around an
;;; evaluation is handled by the macro with-wake-up-management.  After this
;;; management, postponed clean ups are performed and any variables which now
;;; have nothing interested in them should withdraw any backward chaining they
;;; have scheduled.

;;; Lists of rule instances executing for backward chaining are handled by the
;;; backward chaining mechanisms of variables, but the basic ideas are the same.
;;; Any rule instance which is executing on behalf of backward chaining for a
;;; variable will have the variable in the list of things interested in it (i.e.
;;; the purposes list).  When this list is empty, then the rule instance is
;;; cancelled, and when the variable receives a value, then all interest in
;;; backward chaining rule instances is removed.




;;; The function `interested-slot-name' is used by macros at compile time only
;;; to determine the name of the slot which holds interest lists for requestors
;;; of evaluations.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defun-for-macro interested-slot-name (instance-type)
    (case instance-type
      ((rule-instance)
       'ri-things-this-rule-instance-is-interested-in)
      ((code-body-invocation)
       'things-this-code-body-invocation-is-interested-in)
      ((variable) 'things-this-variable-is-interested-in)
      ((display) 'things-this-display-is-interested-in)
      ((inference-background-collection)
       'things-this-inference-background-collection-is-interested-in)
      ((g2-expression-cell)
       'things-this-g2-expression-cell-is-interested-in)
      ((pass-variables-on)
       'variables-that-did-not-have-values-variable)
      ;; The "none" case is for those situations where we know before-hand that
      ;; wake ups will never be set.
      ((none)
       'with-wake-up-management-null-slot-name)
      (otherwise
        (error "Macro with-wake-up-management or ~
                remove-wake-ups-and-clean-up-after-body called with unknown ~
                instance type ~A."
               instance-type)))))




;;; The macro `with-wake-up-management' is responsible for managing wake up
;;; pointers generated while evaluating inference engine expressions.  It takes
;;; three arguments and a body.  The first argument is an unquoted symbol naming
;;; the type of object which is currently bound on the current-computation-
;;; instance special variable.  If the wake-up-predicate is NIL, this may be
;;; NONE.  The second argument is a list of variables which will be setqed to
;;; the values returned by the given expression, ala multiple-value-setq.  The
;;; third argument is a predicate form to determine whether to set wake ups, or
;;; to discard any wake up links and continue.  This will typically be a null
;;; check on the given expiration variable.  Note that if the given predicate is
;;; a constant NIL or constant non-nil value, this macro will emit only the
;;; relevant code.  When passing NIL as the wake up predicate, you may also pass
;;; NONE as the first argument, the instance-type, since no wake ups will ever
;;; be set.  The body contains the forms to evaluate in a progn to produce the
;;; values.  This is typically now some call to the stack evaluator.

;;; Note that unlike the old wake ups facility, this does not perform any set
;;; membership tests on the wake up lists.  So, it is certainly possible to get
;;; one variable on a single interest list twice.  This will not be a problem,
;;; however, since each of these copies is double ended and will be properly
;;; removed and handled.  Note that it is also possible to follow the wake-ups
;;; twice, since we will not be "folding" multiple invocations back into each
;;; other.  Since I believe we handle these interest and variables that did not
;;; receive a value lists more often than we actually follow wake up links, it
;;; is more efficient to allow double wake ups than to have to memq down the
;;; list every time you want to add something to it.  Also, it should be very
;;; rare to actually have a variable on the list twice.

;;; Also note that the verbosity of the loop reclaiming the
;;; *variables-that-did-not-have-values* list is an attempt to produce the most
;;; efficient code possible, taking care not to traverse the list twice while
;;; removing requests for variables and then reclaiming the list.  This code
;;; will be executed very often, and the size of the binary produced to execute
;;; this loop should actually be quite small.

(defmacro with-wake-up-management
          ((instance-type setqed-result-variables set-wake-ups-p-form)
           &body expression-forms)
  (let* ((interested-slot (interested-slot-name instance-type))
         (interested-form
           (if (eq instance-type 'pass-variables-on)
               `*variables-that-did-not-have-values*
               `(,interested-slot current-computation-instance)))
         (successful-completion? (gensym))
         (variable-list-holder (gensym))
         (variable-cons (gensym))
         (cdr-of-cons (gensym))
         (variable (gensym))
         (expression-form
           (if (=f (length expression-forms) 1)
               (car expression-forms)
               (cons 'progn expression-forms)))
         ;; Note the the following call to eval is at compile time.
         (always-reclaim? (and (constantp set-wake-ups-p-form)
                               (not (eval set-wake-ups-p-form)))))
    (if (not (listp setqed-result-variables))
        (error "Call to with-wake-up-management gave setqed-result-variables ~
                which were not in a list.  Argument was ~s."
               setqed-result-variables))
    `(let (,@(if (not always-reclaim?)
                 `((,successful-completion? nil))
                 nil)
           ,variable-list-holder)
       (unwind-protect
           (let ((*variables-that-did-not-have-values* nil))
             ,(cond ((null setqed-result-variables)
                     expression-form)
                    ((=f (length setqed-result-variables) 1)
                     `(setq ,@setqed-result-variables
                            ,expression-form))
                    (t
                     `(multiple-value-setq ,setqed-result-variables
                        ,expression-form)))
             ,@(if (not always-reclaim?)
                   `((setq ,successful-completion? t))
                   nil)
             (setq ,variable-list-holder *variables-that-did-not-have-values*))
         ,(if always-reclaim?
              `(if ,variable-list-holder
                   (loop for ,variable-cons = ,variable-list-holder
                                            then ,cdr-of-cons
                         for ,variable = (car ,variable-cons)
                         for ,cdr-of-cons = (cdr ,variable-cons)
                         do (remove-request-for-variable-value
                              ,variable
                              'value-request-pending)
                         until (null ,cdr-of-cons)
                         finally
                           (reclaim-eval-list-given-tail
                             ,variable-list-holder
                             ,variable-cons)))
              `(if ,(if (constantp set-wake-ups-p-form)
                        successful-completion?
                        `(and ,successful-completion?
                              ,set-wake-ups-p-form))
                   (progn
                     ,@(if (neq instance-type 'pass-variables-on)
                           `((loop for ,variable in ,variable-list-holder
                                   for list-spot
                                       = (memq
                                           'value-request-pending
                                           (things-interested-in-this-variable
                                             ,variable))
                                   do
                               (if list-spot
                                   (setf (car list-spot)
                                         current-computation-instance)
                                   (write-wake-up-list-lossage-warning))))
                           nil)
                     (setf ,interested-form
                           (nconc ,variable-list-holder
                                  ,interested-form)))
                   (if ,variable-list-holder
                       (loop for ,variable-cons = ,variable-list-holder
                                                then ,cdr-of-cons
                             for ,variable = (car ,variable-cons)
                             for ,cdr-of-cons = (cdr ,variable-cons)
                             do (remove-request-for-variable-value
                                  ,variable
                                  'value-request-pending)
                             until (null ,cdr-of-cons)
                             finally
                               (reclaim-eval-list-given-tail
                                 ,variable-list-holder
                                 ,variable-cons))))) ))))




;;; The macro `remove-wake-ups-and-clean-up-after-body' should be wrapped around
;;; code which is executed as the result of a wake up, and which may produce
;;; interest links from variables back to this object.  When something is woken
;;; up, it should remove links to any variables whose values it is waiting for.
;;; However, it may happen that a particular wake up link may just end up being
;;; reinstated.  So, we do not want a variable on this wake up list now to do
;;; any clean ups until after this woken up instance has a chance to reinstate
;;; its interest in the variable.

;;; The caller should pass its type and itself to the first two arguments of
;;; this macro, and within the body it should execute whatever code it has which
;;; may reinstate interest links.  This macro will remove all interest links
;;; from this instance, postponing clean-ups.  It will then execute the body,
;;; returning all values returned by the last form in the body.  After the body
;;; has completed, and before the values are returned, this macro will then
;;; perform any clean-ups needed on the variables, and reclaim the eval conses
;;; of the old interest list.

(defmacro remove-wake-ups-and-clean-up-after-body
          ((instance-type instance) &body forms)
  (let ((interested-instance (gensym))
        (wake-ups (gensym))
        (interested-slot-name (interested-slot-name instance-type))
        (variable (gensym))
        (variable-cons (gensym))
        (cdr-of-cons (gensym))
        (remaining-wake-ups (gensym))
        (thing (gensym)))
    `(let* ((,interested-instance ,instance)
            (,wake-ups (,interested-slot-name ,interested-instance)))
       (unwind-protect-for-development remove-wake-ups-and-clean-up-after-body
           (progn
             ,(if (neq instance-type 'variable)
                  `(loop for ,variable in ,wake-ups
                         do
                     (remove-request-for-variable-value-without-clean-up
                       ,variable ,interested-instance)
                         finally
                           (setf (,interested-slot-name ,interested-instance)
                                 nil))
                  `(loop with ,remaining-wake-ups = nil
                         for ,thing in ,wake-ups
                         do
                     (if (rule-instance-p ,thing)
                         (setq ,remaining-wake-ups
                               (eval-cons ,thing ,remaining-wake-ups))
                         (remove-request-for-variable-value-without-clean-up
                           ,thing ,interested-instance))
                         finally
                           (setf (,interested-slot-name ,interested-instance)
                                 ,remaining-wake-ups)))
             ,@forms)
         (when ,wake-ups
           (loop for ,variable-cons = ,wake-ups then ,cdr-of-cons
                 for ,variable = (car ,variable-cons)
                 for ,cdr-of-cons = (cdr ,variable-cons)
                 do
             ,(if (neq instance-type 'variable)
                  `(perform-postponed-variable-clean-up
                     ,variable ,interested-instance)
                  `(unless (rule-instance-p ,variable)
                     (perform-postponed-variable-clean-up
                       ,variable ,interested-instance)))
                 until (null ,cdr-of-cons)
                 finally
                   (reclaim-eval-list-given-tail
                     ,wake-ups ,variable-cons)))))))




;;; The function `remove-wake-ups-postponing-clean-up' will remove outstanding
;;; requests from a requestor object, without cleaning up the computations from
;;; the evaluators which the requestor was previously interested in.

;;; Note that this function cannot receive a variable as a requestor object;
;;; variables must be handled using the remove-wake-ups-and-clean-up-after-body
;;; macro.  Also note that perform-postponed-clean-ups must be called with the
;;; same wake-up list, after the instance has had its chance to reestablish wake
;;; ups.

;;; This macro takes two arguments, the instance which held wake ups, and a list
;;; of wake ups.

(defun remove-wake-ups-postponing-clean-up (requestor wake-ups)
  (loop for variable in wake-ups
        do
    (remove-request-for-variable-value-without-clean-up
      variable requestor)))




;;; The function `perform-postponed-clean-ups' takes two arguments: the
;;; requestor of wake ups which had been previously removed but not cleaned up,
;;; and the list of wake ups which need to be cleaned up.  This function must be
;;; called after a call to remove-wake-ups-postponing-clean-up.  Note that this
;;; function reclaims the given wake up list.

;;; Note that the requestor instance cannot be a variable.  Variables must be
;;; handled using remove-wake-ups-and-clean-up-after-body.

(defun perform-postponed-clean-ups (requestor wake-ups)
  (when wake-ups
    (loop for variable-cons = wake-ups then cdr-of-cons
          for variable = (car-of-cons variable-cons)
          for cdr-of-cons = (cdr-of-cons variable-cons)
          do
      (perform-postponed-variable-clean-up variable requestor)
          until (null cdr-of-cons)
          finally
            (reclaim-eval-list-given-tail wake-ups variable-cons))))




;;; The function `set-pending-wake-ups' takes a requestor-instance which
;;; established the currently outstanding requests for the values of variables.
;;; This function will mark the requested variables with the given requestor.
;;; Note that after executing this function, the caller should encorporate the
;;; list of wake ups into its list of things it is interested in.

(defun set-pending-wake-ups (requestor wake-ups)
  (loop for variable in wake-ups
        for list-spot
            = (memq-macro 'value-request-pending
                          (things-interested-in-this-variable variable))
        do
    (if list-spot
        (setf (car list-spot) requestor)
        (write-wake-up-list-lossage-warning))))




;;; The function `clear-pending-wake-ups' takes an eval cons list of wake ups
;;; and clears the requests for the listed items.  This function is called when
;;; wake ups have been registered by requests for variable values, but continued
;;; execution of these variables is not required.  This function reclaims the
;;; list after removing the wake-ups.

(defun clear-pending-wake-ups ()
  (let ((wake-ups *variables-that-did-not-have-values*))
    (when wake-ups
      (setq *variables-that-did-not-have-values* nil)
      (loop for variable-cons = wake-ups
                              then cdr-of-cons
            for variable = (car-of-cons variable-cons)
            for cdr-of-cons = (cdr-of-cons variable-cons)
            do
        (remove-request-for-variable-value variable 'value-request-pending)
            until (null cdr-of-cons)
            finally
              (reclaim-eval-list-given-tail wake-ups variable-cons)))))



;;; The function `write-wake-up-list-lossage-warning' posts a logbook
;;; warning about a bug with wake ups.

(defun write-wake-up-list-lossage-warning ()
  (write-warning-message* 1
    (twrite-string "An error has occurred while setting wake ups, when an item ")
    (twrite-string "was not found in the wake up list of a variable which did ")
    (twrite-string "not have a value.  Please report this wake up list ")
    (twrite-string "management bug to Gensym software support.")))




;;; The macro `note-that-variable-has-no-value' takes a variable and performs
;;; the operation necessary to notify an expression evaluator that this variable
;;; did not have a value which was requested in the expression.  This adds the
;;; given variable onto the *variables-that-did-not-have-values* list, and
;;; pushes the symbol VALUE-REQUEST-PENDING onto the variables
;;; things-interested-in-this-variable-list.  The requesting instance will
;;; replace this symbol with a pointer to itself if it wishes to actually set
;;; the wake-up.

(def-substitution-macro note-that-variable-has-no-value (variable)
  ;; this is a push operation using EVAL conser.
  (setq *variables-that-did-not-have-values*
        (eval-cons variable *variables-that-did-not-have-values*))
  ;; another push operation using EVAL conser.
  (setf (things-interested-in-this-variable variable)
        (eval-cons
          'value-request-pending
          (things-interested-in-this-variable variable))))






;;;; Computation Context Variables (Some of them at least)




;;; The computation-flag `cache-explanation-variables?' is set to T if the
;;; rule-instance or item is explainable.  Otherwise, the value is NIL.  If this
;;; flag is T, variables referenced in the rule instance antecedent, formula,
;;; etc. will be cached in the rule instance or bound in the
;;; explanation-variables variable.  This flag is defined in the file sets
;;; by def-computation-flags.

(def-concept cache-explanation-variables?)




;;; The variable `explanation-variables' is let-bound in
;;; compute-newer-value-of-variable.  This variable is used to contain a
;;; list of variables used in non-rule explanations.  (Explanation-variables for
;;; rules are stored in a slot of the rule-instance def-structure.)  (The
;;; variable is defined here since it is modified in this module, e.g., in
;;; get-current-value.)

(defvar explanation-variables nil)

(defun-void reclaim-explanation-variables ()
  (loop for var in explanation-variables
        do
        (reclaim-frame-serial-number (cdr var))
        (reclaim-eval-tree (car var)))
  (reclaim-eval-list explanation-variables)
  (setf explanation-variables nil))

(defun copy-explanation-variables (vars)
  (loop for var in vars
        collect (eval-cons (copy-tree-using-eval-conses (car var)) (copy-frame-serial-number (cdr var)))
        using eval-cons))

;;; Obtain-newer-value-from-sensor is called with a variable known to be
;;; active, known to be a sensor, and known not to have a current-value.

;;; A sensor variable is `failed' if the failed flag is set, which is an
;;; explicitly detected situation. (The variable fails to get a value in
;;; a reasonable amount of time.) A passive sensor cannot be failed.
;;; When a sensor is failed, rather than being `unavailable', then there
;;; will be a periodic attempt to obtain a value. Any time a value
;;; arrives, the variable is no longer failed.

;;; A sensor variable is `seeking' if it is not inactive, current, or failed,
;;; and if time-of-oldest-unsatisfied-request? is not nil. (If inactive or
;;; current, this should be nil. There should only be an unsatisfied request for
;;; a failed or seeking variable.) If a sensor is seeking for too long, then
;;; this should be detected and it should be noted as failed.

;;; A variable that is active, has no current value, and is not seeking or
;;; failed is `unused'.

;;; All variables have all these modes except for failed and
;;; unsatisfied, which belongs only to sensors.

;;; If time-of-oldest-unsatisfied-request? is not nil for a sensor
;;; variable, then one of the following must be: (This is a constraint.)

;;;  (a) The variable is seeking, and one-shot. There is a
;;;  task-to-detect-failure.

;;;  (b) The variable is seeking and not one-shot. There is a
;;;       task-to-detect-failure.

;;;  (c) The variable is unavailable. Nothing is happening.

;;;  (d) The variable is failed. There is a task-to-probe-failed-variable.


;; For the moment, all variables are being made to behave as one shots.  This is
;; because the existing one shot mechanism was not documented, there was no
;; interface to it for the user, and folks in the consulting group found its
;; behavior surprising.  If and when we have a more appropriate interface and
;; definition of its behavior, we can put back support for it.  -jra 3/11/88


;;;; Variable Failure  -jra 7/21/88


;;; The above definition of variable failure is obsolete.  The following
;;; documentation is the current definition of variable failure and the
;;; consequences of it.

;;; A variable is 'failed' when a request is made for the value of a variable,
;;; and the variable does not receive a value within the interval specified in
;;; the inference engine `timeout for variables' system parameter, or if all
;;; possible avenues for receiving the value have been attempted and determined
;;; that they will not supply a value for the variable.  (This second case can
;;; occur when backward chaining and all rules which could supply a value have
;;; been attempted, and all have completed but not fired.)  If all requests for
;;; the value of a variable have been withdrawn before the timeout expires or
;;; before all avenues have been exhausted, then this variable will not be set
;;; to failed at the end of the given interval.

;;; When a variable does fail, all "whenever" event rules which check for the
;;; failure of the variable will be invoked for the variable, and a task will be
;;; scheduled to probe the variable.

;;; When a variable has failed and there are still pending requests for its
;;; value, then the variable is `probed' at the interval specified in the
;;; inference engine `retry interval after timeout' system parameter.  The first
;;; probe does not actually occur until one retry interval after the variable
;;; actually fails.  As long as there are still pending requests for the value
;;; of the variable, then probing will continue.  When the last request has been
;;; withdrawn, then probing will stop, but the variable will still be considered
;;; failed.  If another request is made for this variable and it is still
;;; failed, then an attempt will be made immediately to get the value of the
;;; variable, and probing will begin again immediately.

;;; The only way that a failed varaible's status can be changed to not failed is
;;; for that variable to receive a value.  Note that for variables which receive
;;; their values from external data servers, this is a reasonable behavior.
;;; This hinges on the expectation that any sensor, when asked for a value,
;;; should be able to supply it in a timely manner.  However, this expectation
;;; may not hold for all variables which receive their values from the inference
;;; engine.  In particular, there may be diagnostic rules in a knowledge base
;;; which are not mutually exhaustive of the possible state space of a system.
;;; If a variable is requested, it fails, and the request then removed, the
;;; variable will be failed, put not probing.  If a knowledge base does nothing
;;; about failed variables, then this will have no affect on the performance of
;;; the knowledge base.  If however, there are whenever rules about failed
;;; variables, or checks of the variable has failed predicate, then there may be
;;; an effect.

;;; If a user wishes to make use of variable failure within a knowledge base,
;;; then the following methodology is recommended.  For variables for which it
;;; is an expected behavior for them to fail to receive a value, it is
;;; recommended that whenever rules be made which wait for the failure of
;;; variables and which perform a conclude that in their consequents.  They
;;; should set the variable to some value which indicates that the requested
;;; inference failed, and behaviors should be specified for those situations.

;;; Proposal:  This system of failure recognition could be completed if we
;;; supply two more predicates to the system.  The first is a "<designation> has
;;; failed" logical expression which would return whether or not the variable is
;;; currently in a failed state.  The second is "<designation> has pending
;;; requests" which returns whether there are currently any pending requests for
;;; a variable, and thus whether the variable is currently attempting to obtain
;;; a value.  These predicates are both mutually exclusive with respect to the
;;; "<designation> has a current value" predicate.






;;;; Computing Variable Values With Formulas




;;; When variables backward chain, they first look to formulas to compute their
;;; values.  The following code implements backward chaining to variable
;;; formulas.

;;; The function compute-newer-value-of-variable is called when a variable
;;; needs to compute a newer value through the "computation" data server
;;; (better known as the inference engine).  If there is either a specific or
;;; generic formula for the variable, then this function should call
;;; `schedule-formula-for-backward-chaining'.  This will place the variable and
;;; its formula onto the current queues of computations to execute.

;;; The structure `formula-invocation' is used to represent the execution of
;;; formula to compute the value of a variable.  The generic-formula? and
;;; frame-serial-number?  slots are used to cache a fetched generic formula for
;;; this variable, and a frame serial number with which to validate the formula.

(def-structure (formula-invocation
                 (:include computation-instance)
                 (:constructor make-formula-invocation
                  (formula-invocation-variable
                    formula-invocation-generic-formula?
                    formula-invocation-frame-serial-number?)))
  formula-invocation-variable
  formula-invocation-generic-formula?
  (formula-invocation-frame-serial-number? nil :reclaimer reclaim-frame-serial-number)
  (formula-invocation-postponed-clean-ups nil)
  formula-invocation-component-particulars)




;;; The macro `obtain-newer-value-from-sensor' may possibly write a trace
;;; message, then it performs a collect one shot on its data server.

(def-substitution-macro obtain-newer-value-from-sensor (variable data-server)
  (when (major-trace-message-will-be-written-p)
    (write-major-trace-message-for-sensor-data-seek variable))
  (collect-one-shot-data data-server variable))

(defun write-major-trace-message-for-sensor-data-seek (variable)
  (write-major-trace-message
    (tformat "Requesting a value for ~NF from a data server."
             variable)))




;;; Obtain-newer-value takes the same argument and returns the same values as
;;; get-current-value.  Obtain-newer-value attempts to obtain a sufficiently
;;; current value for a variable.  If the variable is a sensor variable,
;;; obtain-newer-value-from-sensor is called.  If it is not a sensor variable,
;;; the global variable mode is checked to decide the source of the value:
;;; simulation, or computation.  If the source is computation, formulas in the
;;; formula?  slot of the variable will be used if they exist.  If the
;;; computation methods don't exist, specific rules in the backward-chaining-
;;; list property of the variable name will be invoked.  If specific rules don't
;;; exist, generic rules may be found in the backward-chaining-list property of
;;; the slotname-for-this-variable?  of the variable.  The generic rules will be
;;; activated with the parent-for-this-variable? of the variable as the focus.
;;; If the attempt to obtain a value is unsuccessful, nil is returned for all
;;; values and a wake-up may be set up.  If the attempt is successful and the
;;; value was obtained by evaluation of a formula, put-current-value is called
;;; and its value is returned.  Note that in general, obtain-newer-value doesn't
;;; have to figure out the type of the value.  If the value is derived from
;;; rules or formulas, then its type is supplied as a third value (taken care of
;;; by eval).  If the value is supplied externally, assume for now that the
;;; external supplier or data acquisition interface will supply the type.
;;; Obtain-newer-value may have to check the type to make sure that it is one of
;;; the ones which are legal for the variable.

(defun-void obtain-newer-value (variable wake-up?)
  (let ((data-server (get-data-server variable))
        (*current-computation-frame* variable)
        (current-computation-instance variable))
    (cond
      ;; A message will be given from get-data-server if there is no data
      ;; server for this variable.
      ((null data-server)
       (unless (value-of-variable-is-current variable)
         (task-to-detect-failure variable))
       nil)

      ((eq data-server 'computation)
       (compute-newer-value-of-variable
         *current-computation-frame* wake-up?))

      (t
       (obtain-newer-value-from-sensor
         *current-computation-frame* data-server)))))




;;; The function `wake-up-variable' is called when a variable (the sub-var)
;;; that was in the interest list of the given variable (the var) receives a
;;; value.  This function should take the argument (the var) and call
;;; obtain-newer-value on it.

;;; Note that in a previous life, it was possible that wake ups could be
;;; "lost", in that if this variable had a current value, but got woken up,
;;; then the formula might not have been re-run.  This might have caused a bug
;;; in variables with formulas (specific or generic) where a default update
;;; interval ran more often than the variable expired, and where the formula
;;; caused backward chaining in a sub-variable.  This problem should not occur
;;; in this implementation, but this one might run the formulas more often,
;;; which I suppose could cause other subtle bugs, though I can't think of any
;;; now.  -jra 5/13/92

(defun wake-up-variable (variable)
  (compute-newer-value-of-variable variable t))




;;; The computation-flag `dont-compute-new-variable-values' is NIL by default
;;; and may be lambda bound to T within processes.  When there is not a current
;;; value for a variable, it is used to control whether or not get-current-value
;;; will attempt to compute a new value or just return a unknown (i.e.  NIL NIL
;;; NIL).  This variable is bound by code in eval and displays, and is used in
;;; variables by get-current-value.  The default is the default of the item
;;; currently executing.

(def-concept dont-compute-new-variable-values)

(def-concept default-dont-compute-new-variable-values)




;;; Requesting data and receiving data are completely decoupled.  The function
;;; 'get-current-value' is the main facility for requesting current values for
;;; variables and parameters.  It takes a variable-or-parameter as an argument.
;;; Three values are returned:  current value, expiration time, and data type.
;;; If the attempt to obtain a value is unsuccessful, all values will be nil.
;;; The second value should be checked to test for success.  The current value
;;; of the variable will be returned without further computation or data service
;;; if it is current.  If the special variable force-new-request-for-value is
;;; non-nil, it will only return a current value if it was obtained within this
;;; second.  If this is not the case, then a newer value must be obtained.  If
;;; the variable is not active, all returned values will be nil.


(defun get-current-value (variable-or-parameter wake-up?)
  (let ((old-stack-expiration stack-expiration))
    (setq stack-expiration 'never)
    (let* ((result (get-current-evaluation-value
                     variable-or-parameter wake-up?))
           (new-expiration stack-expiration))
      (setq stack-expiration old-stack-expiration)
      (if (or (null new-expiration) (null result))
          (values nil nil nil)
          (let* ((type (evaluation-value-type result))
                 (value (transform-evaluation-value-into-value
                          result type)))
            (values value new-expiration type))))))


;;; The subsitution macro `get-current-evaluation-value-of-parameter' takes a parameter
;;; as its argument and returns an evaluation value encapsulating the value of
;;; that parameter.  This function is used by procedures to fetch parameter
;;; values.

(def-substitution-macro get-current-evaluation-value-of-parameter (parameter)
  (make-evaluation-value-from-managed-value
    (eq (data-type-of-variable-or-parameter parameter) 'truth-value)
    (current-value-of-variable-or-parameter parameter)))

(def-substitution-macro get-current-evaluation-value-of-variable-1 (variable)
  (make-evaluation-value-from-managed-value
    (eq (data-type-of-variable-or-parameter variable) 'truth-value)
    (current-value-of-variable-or-parameter variable)))

(def-substitution-macro get-current-evaluation-value-of-variable-or-parameter (variable)
  (make-evaluation-value-from-managed-value
    (eq (data-type-of-variable-or-parameter variable) 'truth-value)
    (current-value-of-variable-or-parameter variable)))




;;; The function `get-current-evaluation-value' is a replacement for
;;; get-current-value.  It returns either NIL or an evaluation value which is
;;; the value of the given variable or parameter.  If the expiration is
;;; something other than NEVER, this function will modify the stack-expiration
;;; global variable, minimizing the expiration against that value.

;; This function now enters a temporary-area to reference the float expiration
;; of a variable.  - cpm, 5/31/94

(defun-simple get-current-evaluation-value (variable-or-parameter wake-up?)
  #+development
  (unless (and (boundp '*current-computation-frame*)
               (of-class-p *current-computation-frame* 'block)
               (boundp '*variables-that-did-not-have-values*))
    (error "Get-current-value was called without the environment for~@
            *current-computation-frame*, or *variables-that-did-not-have-values*."))
  (let ((result nil)
        (expiration 'never))
    (cond
      ;; If a variable is not active, a value cannot be supplied even if it has
      ;; one.
      ((not (active-p variable-or-parameter))
       ;; Stack-eval-warning-message
       (warning-message*
           1 "~NF is not active, its value was requested in ~NF."
         variable-or-parameter
         *current-computation-frame*)
       (setq expiration nil)
       (setq result nil))

      ;; Parameters always have values with indefinite expirations.
      ((parameter-p variable-or-parameter)
       (setq result
             (get-current-evaluation-value-of-parameter variable-or-parameter)))

      ;; If we are in a current value context or if the passive flag is set,
      ;; only return a value if it is current.
      ((or (dont-compute-new-variable-values)
           (passive-p variable-or-parameter))
       (cond ((value-of-variable-is-current variable-or-parameter)
              (setq expiration
                    (expiration-time-of-current-value variable-or-parameter))
              (setq result
                    (get-current-evaluation-value-of-variable-1
                      variable-or-parameter)))
             (t
              (unless (dont-compute-new-variable-values)
                (note-that-variable-has-no-value variable-or-parameter))
              (setq expiration nil))))

      ;; Otherwise, attempt to get a value for this variable.
      (t
       (let ((current? (value-of-variable-is-current variable-or-parameter)))
         (cond
           ((and current? (not (force-new-request-for-value)))
            (setq expiration
                  (expiration-time-of-current-value variable-or-parameter))
            (setq result (get-current-evaluation-value-of-variable-1
                           variable-or-parameter)))
           (t
            (obtain-newer-value variable-or-parameter wake-up?)
            (setq current?
                  (value-of-variable-is-current variable-or-parameter))
            (cond
              (current?
               (setq expiration
                     (expiration-time-of-current-value variable-or-parameter))
               (setq result (get-current-evaluation-value-of-variable-1
                              variable-or-parameter)))
              (t
               ;; If a value for this variable was not obtained, then add it to
               ;; the list of variables that did not have values.  Update the
               ;; time of the oldest unsatisfied request if necessary, and if
               ;; there was a new request, then schedule a task to detect
               ;; failure if there is a timeout for variables.
               (note-that-variable-has-no-value variable-or-parameter)

               ;; If this variable is already failed, and if there is not
               ;; currently a task scheduled to probe this variable, then
               ;; schedule it.
               (cond ((failed-p variable-or-parameter)
                      (task-to-detect-failure variable-or-parameter))
                     ((null (time-of-oldest-unsatisfied-request?
                              variable-or-parameter))
                      (setf (time-of-oldest-unsatisfied-request?
                              variable-or-parameter)
                            (clock-get gensym-time))
                      (let ((timeout? (timeout-for-variables
                                        inference-engine-parameters)))
                        (when timeout?
                          (with-future-scheduling
                              ((task-to-check-variable? variable-or-parameter)
                               8 (g2-future-interval timeout?))
                            (task-to-detect-failure variable-or-parameter))))))
               (setq expiration nil))))))))

    ;; If we are caching explanations, add variables or parameters with
    ;; values to the list.
    (when (and (cache-explanation-variables?)
               expiration
               result)
      (cache-explanation-variables variable-or-parameter))

    (setq stack-expiration
          (minimum-expiration stack-expiration expiration))

    result))



;;; The macro `get-value-of-parameter-for-simulator' is used to get the value of
;;; parameter from within the simulator when there is no simulation formula.  It
;;; is indifferent about activation.

(def-substitution-macro get-value-of-parameter-for-simulator (parameter)
  (extract-number-or-value
    (current-value-of-variable-or-parameter parameter)))

(defmacro get-evaluation-value-of-parameter-for-simulator (parameter)
  `(get-current-evaluation-value-of-parameter ,parameter))




;;; Task-to-detect-failure should not get executed unless the variable fails to
;;; return a value after being requested and waiting for the timeout-for-
;;; variables interval.  This task puts the variable into failure mode and
;;; invokes rules for variable failure.

(defun-void task-to-detect-failure (variable)
  (when (not (failed-p variable))
    (set-failed variable)
    (invoke-rules-for-failure-chaining variable)
    (cancel-task (task-to-check-variable? variable)))
  (let ((failed-sensor-probing-interval?
          (retry-interval-after-sensor-timeout inference-engine-parameters)))
    (when (and failed-sensor-probing-interval?
               (not (schedule-task-in-place-p
                      (task-to-check-variable? variable))))
      (with-current-scheduling ((task-to-check-variable? variable)
                                8
                                (coerce-fixnum-to-gensym-float
                                  failed-sensor-probing-interval?))
        (task-to-probe-failed-variable variable)))))

(defun-void task-to-probe-failed-variable (variable)
  (attempt-new-variable-value-collection variable nil nil))




;;; The macro `find-generic-formula' takes a parent object of a variable and a
;;; slot name for that variable, and returns the first applicable, active
;;; generic formula it can find.

;;; note that the slot designator is a parent-attribute and is a dotted pair!
;;; -rdf, 3/10/94

(defun find-generic-formula (parent-entity? slot-designator)
  (when parent-entity?
    (let ((pretty-name (if (consp slot-designator)
                           (attribute-of-qualified-attribute slot-designator)
                           slot-designator)))

      (loop named find-generic-formula
            with generic-formulas = (formulas-for-this-role pretty-name)
            for class in (class-inheritance-path
                           (class-description-slot parent-entity?))
            with defining-class = (defining-class-of-qualified-attribute-if-any? slot-designator)
            with defining-description = (if defining-class
                                            (class-description defining-class)
                                            (class-description-slot parent-entity?))
            with description  = (get-slot-description-of-class-description
                                                pretty-name defining-description)
            do
        (loop for formula in generic-formulas
              for formula-qualifier-description
              =  (if (formula-role-class-qualifier formula)
                     (class-description (formula-role-class-qualifier formula))
                     (class-description-slot parent-entity?))
              do
          #+development
          (when nil (consp slot-designator)
                (break "find-generic-formula"))
          (when (and (eq class (formula-class formula))
                     (runnable-p formula)
                     (eq description
                         (get-slot-description-of-class-description
                           pretty-name formula-qualifier-description)))
            (return-from find-generic-formula
              formula)))))))

(def-bombout-clean-up-function
  'clear-currently-evaluating-formula-after-bombout)

(defun clear-currently-evaluating-formula-after-bombout ()
  (loop for variable being each class-instance of 'variable
        do
    (clear-currently-evaluating-formula variable)))




;;; If a variable is already backward chaining or being woken up, and another
;;; request arrives for the value of the variable, the function
;;; `maximize-priority-of-variable' will be called with the variable and the new
;;; priority.  If the given priority is higher than the current priority of
;;; variable execution, then the varaible's backward-chaining-priority and the
;;; priority of any task in task-for-wake-up? should be raised.

(declare-forward-reference maximize-priority-of-rule-instance function)


(defun maximize-priority-of-variable (variable priority)
  (let ((old-priority? (backward-chain-priority? variable)))
    (when (and old-priority?
               (higher-priority-p priority old-priority?))
      (setf (backward-chain-priority? variable) priority)

      ;; Remove?  Only if there are no uses other than formula evaluation.
      ;; -jra 5/13/92
      (when (schedule-task-in-place-p (task-for-wake-up? variable))
        (change-priority-of-task
          (task-for-wake-up? variable) priority))

      ;; Maximize the formula-invocation, if any.
      (when (formula-invocation? variable)
        (schedule-computation-instance-execution
          (formula-invocation? variable) priority variable))
      (loop for thing in (things-this-variable-is-interested-in variable)
            do
        (cond ((rule-instance-p thing)
               (maximize-priority-of-rule-instance thing priority))
              ((of-class-p thing 'variable)
               (maximize-priority-of-variable thing priority))
              #+development
              (t
               (cerror
                 "Continue maximize-priority."
                 "Something which was not a rule instance or variable was ~
                  found in the things-this-variable-is-interested-in list.  ~
                  Unknown thing = ~s."
                 thing)))))))

(defvar within-backward-chaining-task nil)




;;; The macro `circular-variable-interests-p' takes a variable frame and
;;; returns either NIL or an eval cons list of the variable frames involved in a
;;; circular pathway of variable interests.  When users have written formulas
;;; which refer back to the variable whose value the formula is supposed to
;;; compute, these loops will arise.  These are errors in a knowledge base which
;;; should be reported back to the user.  The caller of this function is
;;; responsible for reclaiming the conses in this list.

;;; The simple function circular-variable-interests-1 is used to perform the
;;; search of variable interests lists for circular-variable-interests-p.  This
;;; function returns NIL if the given original-variable is not within the
;;; sub-tree of interest below variable-to-search.  If the original-variable is
;;; within the subtree, this function returns an eval cons list of the variables
;;; along the tree branch which led to the original-variable, excluding the
;;; orginal-variable itself.  So, if A calls B and B calls C, given A and C,
;;; this function would return the list (A B).  If A called A directly, given A
;;; and A this function would return the list (A).

(def-substitution-macro circular-variable-interests-p (variable)
  (circular-variable-interests-1 variable variable))

(defun-simple circular-variable-interests-1
              (variable-to-search original-variable)
  (let ((loop-result nil))
    (set-currently-evaluating-formula variable-to-search)
    ;; Intesting-thing will be either a variable or a rule-instance.
    (loop for interesting-thing
              in (things-this-variable-is-interested-in variable-to-search)
          do
      (unless (rule-instance-p interesting-thing)        ; i.e. variable-p
        (if (eq interesting-thing original-variable)
            (setq loop-result (eval-list interesting-thing))
            (unless (currently-evaluating-formula-p interesting-thing)
              (setq loop-result
                    (circular-variable-interests-1
                      interesting-thing original-variable))
              (when loop-result
                (setq loop-result
                      (eval-cons interesting-thing loop-result))))))
                until loop-result)
    (clear-currently-evaluating-formula variable-to-search)
    loop-result))




;;; The function `write-circular-path-warning' is used to issue the
;;; warning message about a circular path through formula evaluations.

(defun write-circular-path-warning (variable path)
  (write-warning-message* 1
    (if (and (null (cdr path))
             (eq variable (car path)))
        (tformat
          "The formula computing the value of ~NF refers directly to ~
           itself, and so cannot be evaluated."
          variable)
        (progn
;          (loop for variable-cons on path do
;            (setf (car variable-cons)
;                  (get-or-make-up-designation-for-block
;                    (car variable-cons))))
          (tformat
            "Formulas computing the value of ~NF refer indirectly to ~
             itself, and so cannot be evaluated.  The variables in the ~
             loop are the following: "
            variable)
          (write-list-in-chicago-style path "and" t)
          (twrite-char #.%\.))))
  (reclaim-eval-list path))




;;; The function `compute-newer-value-of-variable' implements backward chaining
;;; for variables.  Compute-newer-value-of-variable will attempt to use
;;; computation-methods (specific and then generic), specific backward chaining
;;; rules, and generic backward chaining rules, in that order of preference, to
;;; get a sufficiently recent value for the variable.

;;; In order to guarantee reference perspective side-effect free expression
;;; evaluation, there are restrictions on what this function may do.  Basicly,
;;; the restrictions are designed to insure that if an expression is evaluated
;;; twice in a row with no actions taken in-between, then the expression will
;;; evaluate to the same value twice in a row.  This could be interpreted to
;;; mean that no side effects may be taken on variable values within the
;;; recursive descent of expression evaluation.  However, we may relax this
;;; restriction if side effect does not modify data which the expression results
;;; are already dependent upon.  Because of the complexities of implementation
;;; we will not allow this extension to be applied to rule backward chaining,
;;; but it will be extended to formula evaluation in the following manner.  If a
;;; variable is attempting to get a value and it has no wake ups currently set
;;; to it, then it may attempt to evaluate a formula and call put-current-value
;;; to set that value into itself.  If it does have wake-ups set to it, then it
;;; must evaluate formulas within a scheduled task, outside of the recursive
;;; descent of the requesting expression evaluation.  The special variable
;;; within-backward-chaining-task will be T when in the first level of a
;;; backward chaining task, and NIL otherwise.  In all cases, backward chaining
;;; rule execution must be performed outside of the recursive descent of this
;;; function, though requests for the scheduling of rule executions may be
;;; performed here.

;;; Note that if there is a circular path through variable formulas, there could
;;; be continuous processing occurring around the loop.  Normally these loops
;;; will be detected and processing for them stopped, but if there are requests
;;; for more than one of the variables in the loop which arise from sources
;;; outside of the loop, then continuous processing around the loop will result.
;;; Warning messages about this will be continually sent to the logbook in this
;;; case.  -jra & ml 7/20/90

;;; The above bug has been fixed by the circular path checker installed here.
;;; -jra 8/9/91

(defun compute-newer-value-of-variable (variable wake-up?)
  (declare (ignore wake-up?))
  (when (dont-backward-chain-p variable)
    (return-from compute-newer-value-of-variable nil))
  (cancel-task (task-for-wake-up? variable))
  (let ((specific-formula? (car (formula? variable))))
    ;; If there is a specific formula for this variable, try to evaluate it.
    (if specific-formula?
        (schedule-formula-for-backward-chaining variable nil)

        ;; If there is a generic formula, evaluate it.
        (let* ((parent-entity? (parent-frame variable))
              (slot-name (parent-attribute-name variable)))
          (let ((generic-formula?
                  (find-generic-formula parent-entity? slot-name)))
            (if generic-formula?
                (schedule-formula-for-backward-chaining
                  variable generic-formula?)
                ;; Invoke backward chaining rules to try and set a value for the
                ;; variable.
                (invoke-rules-for-backward-chaining variable)))))))



(defun-simple is-a-formula-invocation? (a-potential-formula-invocation)
  (formula-invocation-p a-potential-formula-invocation))

(defun-simple item-to-profile-of-formula-invocation (a-formula-invocation)
  (let (the-item)
    (setq the-item (formula-invocation-generic-formula? a-formula-invocation))
    (unless the-item
      (setq the-item (formula-invocation-variable a-formula-invocation)))
    the-item))

(defun-simple schedule-formula-for-backward-chaining
              (variable generic-formula?)
  (if (formula-invocation? variable)
      (maximize-priority-of-variable variable priority-of-current-task)
      (let* ((old-priority? (backward-chain-priority? variable))
             (priority-to-propagate
               (if (priority-p priority-of-current-task)
                   priority-of-current-task
                   1))
             (priority-of-task
               (if old-priority?
                   (highest-priority old-priority? priority-to-propagate)
                   priority-to-propagate))
             (formula-invocation
               (make-formula-invocation
                 variable generic-formula?
                 (if generic-formula?
                     (copy-frame-serial-number (frame-serial-number generic-formula?))
                     nil))))
        (remove-rule-instances-from-variable-interests variable)
        (setf (formula-invocation? variable) formula-invocation)
        (when profiling-enabled?
          (let ((item-to-profile
                  (item-to-profile-of-formula-invocation formula-invocation)))
            (increment-profiling-calls
              item-to-profile)))
        (schedule-computation-instance-execution
          formula-invocation priority-of-task variable)
        (when (and old-priority?
                   (higher-priority-p priority-to-propagate old-priority?))
          (maximize-priority-of-variable variable priority-to-propagate))))
  nil)

(defun remove-rule-instances-from-variable-interests (variable)
  (loop with list = (things-this-variable-is-interested-in variable)
        for previous-cons = nil
        for current-cons = list then next-cons
        while current-cons
        for (interesting-thing . next-cons) = current-cons
        do (cond ((not (rule-instance-p interesting-thing))
                  (setq previous-cons current-cons))
                 (t
                  (remove-request-for-rule-instance-invocation
                   interesting-thing variable)
                  (if previous-cons
                      (setf (cdr previous-cons) next-cons)
                      (setf list next-cons))
                  (reclaim-eval-cons current-cons)))
        finally (setf (things-this-variable-is-interested-in variable) list)))

(defun-void cancel-formula-for-backward-chaining (variable)
  (let ((formula-invocation? (formula-invocation? variable)))
    (when formula-invocation?
      (setf (formula-invocation? variable) nil)
      (cancel-task (invocation-schedule-task formula-invocation?))
      (unless (eq formula-invocation? current-computation-instance)
        (reclaim-formula-invocation formula-invocation?)))))

(defun handle-formula-invocation-error
    (formula-invocation error error-level error-text-string
             current-program-counter local-stack top-of-stack computation-frame
             computation-component-particulars byte-code-body constant-vector
                        local-var-vector)
  (let ((standard-message
          (generate-standard-error-message
            error error-text-string computation-frame
            computation-component-particulars formula-invocation byte-code-body
            constant-vector current-program-counter local-stack top-of-stack
            local-var-vector)))
    ;; Invoke default error handler if registered and active
    (cond
      ((and (registered-and-active-default-error-handler-p)
            (invoke-user-defined-default-error-handler error
                                                  standard-message)))
      (t
       (warning-message
           error-level
           "~nw~%Exiting execution of this formula.  No value was computed for ~NF"
         standard-message
         (formula-invocation-variable formula-invocation))
       (reclaim-error-text standard-message)))
    (reclaim-error-text error-text-string)
    (exit-computation-context-for-variable-formula formula-invocation)
    nil))


(defvar new-value-computed-in-formula? nil)

;; This variable should be removed at the end of the inner context switching
;; project.  -jra 5/14/92

;(defun-allowing-unwind execute-instance-formula (variable)
;  (let* ((within-backward-chaining-task nil)
;         (check-for-circular-paths?
;           (things-this-variable-is-interested-in variable))
;         (g2-cell-array (cell-array variable))
;         (expression-cell
;           (when g2-cell-array
;             (managed-svref
;               (g2-cell-array-managed-array-function g2-cell-array)
;               0)))
;         (current-computation-instance variable)
;         (new-value-computed-in-formula? nil))
;    (remove-wake-ups-and-clean-up-after-body (variable variable)
;      (when expression-cell
;        (with-wake-up-management
;          (variable nil (not new-value-computed-in-formula?))
;          (attempt-expression-cell-execution-for-formula
;            expression-cell nil variable))))
;    (when (not new-value-computed-in-formula?)
;      (when check-for-circular-paths?
;        (let ((circular-path?
;                (circular-variable-interests-p variable)))
;          (when circular-path?
;            (write-circular-path-warning
;              variable circular-path?)
;            (remove-wake-ups-and-clean-up-after-body (variable variable)
;              nil)
;            (cancel-task (task-for-wake-up? variable))))))
;    new-value-computed-in-formula?))

(def-class-method expression-cell-updated
                  (variable g2-cell-array index old-cache? new-cache?)
  (declare (ignore g2-cell-array index old-cache?))
  (when new-cache?
    (setq new-value-computed-in-formula? t)
    (put-current-value
      variable
      (evaluation-value-value new-cache?)
      (evaluation-value-type new-cache?)
      stack-expiration
      nil)))

;(defun-allowing-unwind execute-generic-formula
;                       (generic-formula variable parent-entity)
;  (let* ((argument-list (eval-list parent-entity))
;         (within-backward-chaining-task nil)
;         (check-for-circular-paths?
;           (things-this-variable-is-interested-in variable))
;         (g2-cell-array (cell-array generic-formula))
;         (expression-cell
;           (when g2-cell-array
;             (managed-svref
;               (g2-cell-array-managed-array-function g2-cell-array)
;               0)))
;         (current-computation-instance variable)
;         (new-value-computed-in-formula? nil))
;    (remove-wake-ups-and-clean-up-after-body (variable variable)
;      (when expression-cell
;        (with-wake-up-management
;          (variable nil (not new-value-computed-in-formula?))
;          (attempt-expression-cell-execution-for-formula
;            expression-cell argument-list variable))))

;    ;; Reclaim the eval conses for the argument list.
;    (reclaim-eval-list argument-list)

;    (when (not new-value-computed-in-formula?)
;      (when check-for-circular-paths?
;        (let ((circular-path?
;                (circular-variable-interests-p variable)))
;          (when circular-path?
;            (write-circular-path-warning
;              variable circular-path?)
;            (remove-wake-ups-and-clean-up-after-body (variable variable)
;              nil)
;            (cancel-task (task-for-wake-up? variable))))))
;    new-value-computed-in-formula?))

(def-class-method expression-cell-updated
                  (generic-formula g2-cell-array index old-cache? new-cache?)
  (declare (ignore generic-formula g2-cell-array index old-cache?))
  (when new-cache?
    (setq new-value-computed-in-formula? t)
    (put-current-value
      current-computation-instance
      (evaluation-value-value new-cache?)
      (evaluation-value-type new-cache?)
      stack-expiration
      nil)))

(def-class-method denote-cell-array-element
                  (variable component-particulars include-block-denotation?)
  (declare (ignore variable component-particulars include-block-denotation?))
  (twrite-string "the formula")
  (denote-component-of-block-1 '*current-computation-frame* " of "))

(def-class-method denote-cell-array-element
                  (generic-formula component-particulars include-block-denotation?)
  (declare (ignore generic-formula component-particulars include-block-denotation?))
  (twrite-string "the text")
  (denote-component-of-block-1 '*current-computation-frame* " of "))






;;;; Validating Generic-Formula Invocations




;;; The function `validate-all-generic-formula-invocations' locates all
;;; generic-formula-invocations and validates the corresponding context-vectors.
;;; If a location in the context is invalid, it is set to NIL, but the
;;; invocation does not get dismissed.  Also, note that the validation checks
;;; for items of the wrong class, as well as deleted items.

;;; This function is needed when there has been a change to a running or paused
;;; KB, and, therefore, some formula-invocation variables may no longer be
;;; valid.

(defun-void validate-all-generic-formula-invocations ()
  (loop for variable being each class-instance of 'variable
        for formula-invocation? = (formula-invocation? variable)
        do
    (when formula-invocation?
      (validate-generic-formula-invocation-environment
        formula-invocation? variable t)))
  nil)

;; An alternative design in the above function is to iterate over the
;; generic-formulas, but there does not seem to be a pointer from the formula to
;; the formula-invocations.  - cpm, 3/17/94



;;; The function `validate-generic-formula-invocation-environment' validates the
;;; values in the environment-vector of the generic-formula-invocation.  Any
;;; vector locations that contain an invalid value are set to NIL.  Optionally,
;;; this function can also validate the class of the items.

(declare-forward-reference var-type-from-index-function function)

(defun-void validate-generic-formula-invocation-environment
    (formula-invocation variable also-validate-item-classes?)
    (let* ((generic-formula?
             (formula-invocation-generic-formula? formula-invocation))
           (frame-serial-number
             (formula-invocation-frame-serial-number? formula-invocation))
           (expression-cell-parent
             (if (and generic-formula?
                      (frame-has-not-been-reprocessed-p
                        generic-formula? frame-serial-number))
                 generic-formula?
                 variable))
           (g2-cell-array (cell-array expression-cell-parent))
           (expression-cell
             (when g2-cell-array
               (managed-svref
                 (g2-cell-array-managed-array-function g2-cell-array) 0)))
           (byte-code-body
             (when expression-cell
               (g2-expression-cell-byte-code-body-function expression-cell)))
           (environment-description
             (when byte-code-body
               (byte-code-body-environment-description byte-code-body)))
           (environment-length (var-count environment-description))
           (local-var-vector (invocation-local-var-vector formula-invocation)))
      (when generic-formula?
        ;; Only validate generic-formulas.  Specific-formulas do not have
        ;; generic-references or local-variables, and so do not need to be
        ;; validated.
        (if (null also-validate-item-classes?)
            (loop for index from 0 below environment-length
                  for value? = (svref local-var-vector index)
                  do
              (when value?
                (setf (svref local-var-vector index)
                      (validate-item-or-evaluation-value
                        value? frame-serial-number nil))))
            (loop for index from 0 below environment-length
                  for value? = (svref local-var-vector index)
                  for item-type? = (if (framep value?)
                                       (var-type-from-index-function
                                         environment-description index)
                                       nil)
                  do
              (when value?
                (setf (svref local-var-vector index)
                      (validate-item-or-evaluation-value
                        value? frame-serial-number item-type?))))))
      nil))






;;;; Receiving Values of Variables




;;; `Put-current-value' is the main function for putting current values into
;;; variables and parameters.  It takes a variable-or-parameter frame, a value,
;;; a data-type, and optionally a collection time and an expiration time as
;;; arguments.  It returns a value, expiration-time, data-type triple.
;;; Put-current-value first checks if the variable-or-parameter is active.  If
;;; it isn't, nothing is done and nil is returned for all values.   If it is,
;;; the value is put in the current-value slot, the appropriate time slots are
;;; updated, wake ups may be invoked, and the value may be saved in the history.
;;; If the variable is a sensor which has been marked as questionable or dead,
;;; this status may be changed.  Note that if a collection time is given, and
;;; that collection time is less than the time of the most recent value of the
;;; variable-or-parameter, then the value will only be entered in the history.
;;; Also note, that the expiration has no effect on parameters.

;;; The variable *current-computation-frame* must be bound to a frame during the
;;; call to this function.

;;; The time related slots are updated as follows.  If the validity interval of
;;; the variable is 'indefinite, then the expiration time is 'never.  If the
;;; validity interval is a number n, then if collection time is provided, the
;;; the expiration time is n + collection-time, else the expiration time is n +
;;; gensym-time.  Collection-time should only typically be provided in the case
;;; of values of sensed variables.  Note that this could result in an
;;; expiration-time which is less than gensym-time in which case the value is
;;; not current.  If the validity interval is 'supplied, then the expiration
;;; time is set to the expiration-time argument which must be provided.  The
;;; validity interval should be 'supplied only for derived variables, not for
;;; sensor variables.

;;; Put-current-value must check if there are any outstanding tasks which check
;;; if a sensor has failed and cancel them.  The status of the variable must
;;; also be checked and possibly updated.

;;; Wake-ups are set up by the frames (typically rules) requesting values of
;;; variables (see "eval").  Thus, get-current-value does very little in the way
;;; of setting up wake-ups.  Put-current-value may however invoke wake-ups.  It
;;; must check the things-to-wake-up slot of the variable and if it is not nil,
;;; invoke the appropriate wake-up for each frame.  (copy some of the
;;; documentation in eval to here)

;;; Put-current-value will also cause `forward chaining'.  The forward chaining
;;; links are stored in the forward-chaining-list property of variable names,
;;; attribute names of parent objects of truth variables, and object names of
;;; parent objects of symbolic variables.  See invoke-rules-for-forward-chaining
;;; for a more detailed description of the forward chainer.  Note that forward
;;; chaining will not be performed if the forward-chain flag of the variable is
;;; not set, if the dont-forward-chain-from-rule special variable is non-nil, or
;;; if the value and expiration of the new value is the same as the old.  Even
;;; though we will not forward chain per se, we must still call the
;;; invoke-rules-for-forward-chaining function to cause event (i.e. whenever
;;; rule) chaining.

;;; If a text-string is being put into the variable-or-parameter, a copy of the
;;; passed string will be stored in the variable-or-parameter frame, and the
;;; passed string will be returned as the value of the value, expiration, type
;;; triplet.  It is the responsibility of the caller to reclaim the text string.

;;; When clearing out the list of things interested in this variable, note that
;;; if this variable has the symbol value-request-pending on its interest list
;;; then there is some expression evaluating object which has this variable on
;;; its *variables-that-did-not-have-values* list.  In this case, we will leave
;;; the symbol on the interest list, and let the expression evaluating object
;;; remove it or set a wake up.  Note that this could result in a variable with
;;; a value getting a wake up set to it, but this is already the case in the old
;;; rules, and so I won't change it now.  This will never happen in new rules
;;; since we always clean up the wake up management stuff before executing
;;; actions.

;; An optional argument, override-validity-interval?, has been added to
;; put-current-value.  If this argument has a value of non-nil, the expiration
;; argument overrides the variable's validity-interval (a time interval or
;; "indefinite").  In this case, it is an error if an expiration is not passed
;; as an argument.

;; Eventually, make the override-validity-interval?  argument non-optional (for
;; efficiency)!!!  All callers to put-current-value would then need to be
;; modified!!  cpm, jra 7/18/89.

(def-concept dont-forward-chain-from-rule)



(def-system-variable put-current-value-called-from-simulator-p VARIABLES nil)

;; Put-current-value-called-from-simulator-p is bound to t when the simulator
;; calls put-current-value for a parameter so that
;; set-external-variable-for-simulator will not be needlessly called.


;;; IMPORTANT: see put-current-evaluation-value for more information on the
;;; expiration-time? and collection-time? arguments!

;;; This function should be called within a temporary-area.

(defun put-current-value (variable-or-parameter value data-type
                          expiration-time? collection-time?
                          &optional (override-validity-interval? nil))
  (let* ((evaluation-value (make-evaluation-value value data-type))
         (problem-description?
           (put-current-evaluation-value
             variable-or-parameter evaluation-value expiration-time?
             collection-time? override-validity-interval?)))
    (cond ((null problem-description?)
           (values value (or expiration-time? (clock-get gensym-time)) data-type))
          (t
           (warning-message* 1 "~a" problem-description?)
           (reclaim-evaluation-value evaluation-value)
           (reclaim-text-string problem-description?)
           (values nil nil nil)))))




;;; The function `put-current-evaluation-value' is a replacement for put
;;; current value which takes and reclaims an evaluation value argument for the
;;; new value.  It is more efficient than the old put-current-value, and is the
;;; preferred interface.

;;; If the value is successfully put, this function returns NIL.  If there is a
;;; problem, it does not put the value and returns a string (which must be
;;; reclaimed) that describes the problem.  Note that the evaluation-value
;;; argument is not reclaimed when a string is returned.

;;; Expiration time and collection time arguments:
;;; 1. Note that unlike the evaluation-value argument, the expiration and
;;; collection time arguments are *NOT RECLAIMED* here and are owned by the
;;; caller.
;;; 2. As of version 4.0, the expiration and collection time arguments, if
;;; non-NIL, can be g2-time (unix time) floats (gensym or managed-floats), as
;;; well as fixnums.  The expiration can also be the symbol NEVER.
;;; 3. Note that if the time arguments are fixnums, they must be in gensym-time
;;; format.
;;; 4. Note that we are trying to convert to only using floats (g2-time format)
;;; for the time arguments.  All callers should eventually pass this format,
;;; when non-NIL.  (See note #5.)
;;; 5. Note that, unlike the collection time, the expiration time is currently
;;; stored internally as a fixnum (gensym-time format) or a symbol.  This should
;;; eventually be changed and would involve reviewing, among other things, the
;;; implementation of STACK-EXPIRATION and *some-time-ago*, which are fixnums.

;;; This function should be called within a TEMPORARY-FLOAT-AREA.

(defvar put-current-evaluation-value-old-value? nil)
(defvar put-current-evaluation-value-return-value nil) ; result of CAS

(defun put-current-evaluation-value
       (variable-or-parameter evaluation-value supplied-expiration-time?
        supplied-collection-time? override-validity-interval?)
  #+development
  (unless (and (boundp '*current-computation-frame*)
               (of-class-p *current-computation-frame* 'block))
    (error
      "Put-current-value requires a frame binding for ~
       *current-computation-frame*.  Its value was ~a."
      (if (boundp '*current-computation-frame*)
          *current-computation-frame*
          "not bound")))

  (note-change-to-runtime-data-for-block variable-or-parameter)

  (when (not (active-p variable-or-parameter))
    (return-from put-current-evaluation-value
      (tformat-text-string
        "An attempt was made to store a value into ~NF which failed, ~
         because it was not active."
        variable-or-parameter)))

  (let* ((variable? (variable-p variable-or-parameter))
         (history-spec? (variable-or-parameter-history-specification?
                          variable-or-parameter))
         (type-specification
           (type-specification-of-variable-or-parameter-value
             variable-or-parameter))
         (unix-supplied-collection-time?
           ;; A g2-time (gensym-float) or NIL.
           (when supplied-collection-time?
             (cond
               ;; Testing for fixnum, until we have converted all callers of
               ;; this function to pass gensym-time collection.  - cpm, 7/6/94
               ((fixnump supplied-collection-time?)
                (convert-gensym-time-to-unix-time supplied-collection-time?))
               ((managed-float-p supplied-collection-time?)
                ;; g2-time format
                (managed-float-value supplied-collection-time?))
               (t
                ;; gensym-float, g2-time format
                supplied-collection-time?))))
         (old-collection-time
           (time-of-most-recent-value variable-or-parameter)))
    ;; Convert integer or long to float
    (cond ((and (evaluation-integer-p evaluation-value)
		(eq type-specification 'float))
	   (let ((new-value
		  (make-evaluation-float
		    (coerce-fixnum-to-gensym-float
		      (evaluation-integer-value evaluation-value)))))
	     (reclaim-evaluation-integer evaluation-value)
	     (setq evaluation-value new-value)))
	  ((and (evaluation-long-p evaluation-value)
		(eq type-specification 'float))
	   (let ((new-value
		  (make-evaluation-float
		    (normalize-to-gensym-float evaluation-value))))
	     (reclaim-evaluation-long evaluation-value)
	     (setq evaluation-value new-value))))
    ;; Check the type.
    (unless (or (and (eq type-specification 'number)
		     (or (evaluation-integer-p evaluation-value)
			 (evaluation-long-p evaluation-value)))
		(evaluation-value-of-type-p evaluation-value type-specification))
      (return-from put-current-evaluation-value
        (tformat-text-string
          "An attempt to store the value ~NV of type ~NT into ~NF failed ~
           because of type mismatch.  ~NF requires values of type ~NT."
          evaluation-value
          (evaluation-value-type evaluation-value)
          variable-or-parameter
          variable-or-parameter
          type-specification)))

    ;; Now we know that the value is of the correct type.  If the collection
    ;; time is older than the most recent value, either put it in the history,
    ;; or do nothing.
    (when (and unix-supplied-collection-time?
               (<e unix-supplied-collection-time?
                   ;; managed-float or fixnum (see note below).
                   (if (fixnump old-collection-time)
                       (coerce-to-gensym-float old-collection-time)
                       (managed-float-value old-collection-time))))
      ;; Note that the second arg, time-of-most-recent-value, could be a
      ;; managed-float or *some-time-ago* (close to most-negative-fixnum, which
      ;; is used to indicate no value).  The above test works in the
      ;; *some-time-ago* case because the new collection time is positive and
      ;; cannot be less than *some-time-ago*.  - cpm, 5/12/95
      (when history-spec?
        (store-history-value
          (get-or-make-history-buffer variable-or-parameter history-spec?)
          history-spec?
          (evaluation-value-value evaluation-value)
          unix-supplied-collection-time?
          nil))
      (reclaim-evaluation-value evaluation-value)
      (return-from put-current-evaluation-value nil))

    ;; This will be the most recent value.
    (let* ((validity-interval-of-variable?
             (if variable? (validity-interval variable-or-parameter)))
           (collection-time-of-new-current-value
             ;; A G2-TIME (gensym-float).
             (or unix-supplied-collection-time?
                 (managed-float-value (clock-get current-g2-time))))
           (expiration-time-of-new-current-value
             ;; A GENSYM-TIME (fixnum), the symbol NEVER, or NIL.
             (cond
               ((not variable?)
                nil)
               ((or override-validity-interval?
                    (eq validity-interval-of-variable? 'supplied))
                (if supplied-expiration-time?
                    (cond ((fixnump supplied-expiration-time?)
                           ;; Remove this case, when all callers are passing a
                           ;; g2-time expiration argument.  - cpm, 7/6/94
                           supplied-expiration-time?)
                          ((managed-float-p supplied-expiration-time?)
                           (convert-unix-time-to-gensym-time
                             (managed-float-value supplied-expiration-time?)))
                          ((gensym-float-p supplied-expiration-time?)
                           (convert-unix-time-to-gensym-time
                             supplied-expiration-time?))
                          (t supplied-expiration-time?))
                    (return-from put-current-evaluation-value
                      (tformat-text-string
                        "The variable ~NF, which has a validity ~
                        interval of SUPPLIED, received a value ~
                        with no supplied expiration time."
                        variable-or-parameter))))
               ((eq validity-interval-of-variable? 'indefinite)
                'never)
               ((fixnump validity-interval-of-variable?)
                (+f validity-interval-of-variable?
                   (convert-unix-time-to-gensym-time
                     collection-time-of-new-current-value)))
               (t
                (return-from put-current-evaluation-value
                  (tformat-text-string
                    "The variable ~NF has an invalid validity ~
                     interval.  This is a G2 internal error, please ~
                     notify Gensym software support."
                    variable-or-parameter)))))
           (truth-value-p
             (evaluation-truth-value-p evaluation-value))
           (new-value-type
             (evaluation-value-type evaluation-value))
           (new-managed-value
             (transform-evaluation-value-into-managed-value evaluation-value))
           (old-managed-value
             (current-value-of-variable-or-parameter variable-or-parameter))
           (old-expiration
             ;; A gensym-time (fixnum), the symbol NEVER, or NIL.
             (when variable?
               (expiration-time-of-current-value variable-or-parameter))))
      (declare (type gensym-float collection-time-of-new-current-value))

      ;; Change the value and collection time.
      (if put-current-evaluation-value-old-value?
          (progn
            #-SymScale
            (setf (current-value-of-variable-or-parameter variable-or-parameter)
                  new-managed-value)
            #-SymScale ; above SETF should always success
            (setq put-current-evaluation-value-return-value t)
            ;; GENSYMCID-1331: Implement KB level atomic CONCLUDE for SymScale
            ;; Here, pass the CAS result through special variable
            #+SymScale
            (setq put-current-evaluation-value-return-value
                  (compare-and-swap (current-value-of-variable-or-parameter variable-or-parameter)
                                    put-current-evaluation-value-old-value?
                                    new-managed-value))
            ;; block rest of operations if CAS failed.
            (unless put-current-evaluation-value-return-value
              (return-from put-current-evaluation-value nil)))
        (setf (current-value-of-variable-or-parameter variable-or-parameter)
              new-managed-value))

      (cond ((managed-float-p old-collection-time)
             ;; Modify the old collection time.
             (mutate-managed-float-value
               old-collection-time collection-time-of-new-current-value))
            (t
             ;; The old collection time does not need to be reclaimed.
             (setf (time-of-most-recent-value variable-or-parameter)
                   (allocate-managed-float
                     collection-time-of-new-current-value))))

      ;; Clear any failed frame flag that may be set on this variable.
      (when variable?
        (set-not-failed variable-or-parameter)
        (cancel-task (task-to-check-variable? variable-or-parameter))
        (setf (expiration-time-of-current-value variable-or-parameter)
              expiration-time-of-new-current-value)
        (setf (time-of-oldest-unsatisfied-request? variable-or-parameter) nil))

      ;; If there is a history, stuff the value into it.
      (when history-spec?
        (store-history-value
          (get-or-make-history-buffer variable-or-parameter history-spec?)
          history-spec?
          (extract-cached-number-or-value new-managed-value)
          collection-time-of-new-current-value
          nil))

      ;; Notify those things interested in this variable that it has received a
      ;; value.
      (when variable?
        (let ((interested-list?
                (things-interested-in-this-variable variable-or-parameter)))
          (when interested-list?
            (setf (things-interested-in-this-variable variable-or-parameter)
                  nil)
            (loop for thing-cons = interested-list? then cdr-of-cons?
                  for cdr-of-cons? = (cdr-of-cons thing-cons)
                  for thing = (car-of-cons thing-cons)
                  do
              (variable-has-received-a-value thing variable-or-parameter)
                  while cdr-of-cons?
                  finally
                    (reclaim-eval-list-given-tail
                      interested-list? thing-cons)))))

      ;; Invoke forward chaining.
      (let* ((value-changed-p
               (or (and (fixnump new-managed-value) (fixnump old-managed-value) 
			    (/=f old-managed-value new-managed-value)) 
			    (not (managed-value-eql new-managed-value old-managed-value))))
             (value-or-expiration-changed?
               (or value-changed-p
			       (and variable?
                        (not (or (and (fixnump
                                        expiration-time-of-new-current-value)
                                      (fixnump old-expiration)
                                      (=f expiration-time-of-new-current-value
                                          old-expiration))
                                 (eq expiration-time-of-new-current-value
                                     old-expiration)))))))
        (invoke-rules-for-forward-chaining
          variable-or-parameter new-managed-value new-value-type
          (and (forward-chain-p variable-or-parameter)
               (not (dont-forward-chain-from-rule))
               (or (always-forward-chain-if-possible-p variable-or-parameter)
                   value-or-expiration-changed?))
          old-managed-value)

        ;; If the value of this variable is being displayed by any tables,
        ;; update them.
        (when value-or-expiration-changed?
          (update-representations-of-variable-or-parameter-value
            variable-or-parameter)

          ;; Notify the simulator of parameter value changes that came from
          ;; outside of the simulator.
          (when (and (not variable?)
                     (not put-current-value-called-from-simulator-p))
            (let ((evaluation-value-for-simulator
                    (make-evaluation-value-from-managed-value
                      truth-value-p new-managed-value)))
              (set-external-variable-for-simulator
                variable-or-parameter
                evaluation-value-for-simulator
                ;; since the new-managed-value of truth values are integers we
                ;; also need to explicitly pass in the type -rdf, 10/17/94
                (if truth-value-p 'truth-value))
              (reclaim-evaluation-value evaluation-value-for-simulator)))))

      ;; After having caused invocations to proceed through wake-ups and
      ;; forward chaining, stop any backward chaining and remove requests for
      ;; things this variable was trying to execute.
      (when variable?
        (withdraw-backward-chaining variable-or-parameter))

      ;; Reclaim the old value.
      (unless (fixnump old-managed-value)
	(reclaim-managed-number-or-value old-managed-value))

      ;; If we are caching explanations, do it.
      (when (cache-data-for-explanation-p variable-or-parameter)
        (cache-explanation variable-or-parameter))
      nil)))




;;; The function `put-has-no-current-value' takes a variable and will cause the
;;; variable to no longer have a current value by expiring the value.  This is
;;; done by setting its expiration time to the value of one second previous to
;;; the current gensym time.  If the given variable is not active, there will be
;;; no effect on the variable, and a level 2 run-time message will be given.  If
;;; the variable is active but does not have a current value, then this function
;;; has no effect.

(declare-forward-reference invoke-update-functions-for-put-has-no-current-value
                           function)

(defun put-has-no-current-value (variable)
  (cond
    ((active-p variable)
     (note-change-to-runtime-data-for-block variable)
     (when (value-of-variable-is-current variable)
       (let ((old-value (extract-cached-number-or-value
                          (current-value-of-variable-or-parameter variable))))
         (setf (expiration-time-of-current-value variable) (-f (clock-get gensym-time) 1))
         (invoke-update-functions-for-put-has-no-current-value
           variable old-value)
         (update-representations-of-variable-or-parameter-value variable)
         ;; If we are caching explanations, do it.
         (when (cache-data-for-explanation-p variable)
           (cache-explanation variable)))))
    (t
     (warning-message*
       3 "In ~NF, an attempt was made to conclude that the variable ~NF has no ~
          current value.  The attempt failed, because the variable was not ~
          active."
       *current-computation-frame*
       variable)))
  (values nil nil nil))




;;; The function `put-has-no-value' takes a variable and will cause the variable
;;; to no longer have a value by resetting the expiration of the variable back
;;; to its initial value on system start.  This will make the variable appear
;;; "cleared" to the user, and for example will not show the expired value of
;;; the variable in attribute tables.  This function will also update any
;;; representations of the value of this variable.  If the variable was already
;;; in this state, then this action has no effect.  The initial value of the
;;; expiration-time-of-current-value of a variable is the value of the parameter
;;; *some-time-ago*.

(defun put-has-no-value (variable)
  (cond
    ((active-p variable)
     (note-change-to-runtime-data-for-block variable)
     (let ((expiration (expiration-time-of-current-value variable)))
       (when (or (eq expiration 'never)
                 (/=f expiration *some-time-ago*))
         (let ((old-value (extract-cached-number-or-value
                            (current-value-of-variable-or-parameter variable))))
           (setf (expiration-time-of-current-value variable)
                 *some-time-ago*)
           (when (managed-float-p (time-of-most-recent-value variable))
             (reclaim-managed-float (time-of-most-recent-value variable)))
           ;; ML, 1/6/89
           (setf (time-of-most-recent-value variable) *some-time-ago*)
           (invoke-update-functions-for-put-has-no-current-value
             variable old-value)
           (update-representations-of-variable-or-parameter-value variable)
           ;; If we are caching explanations, do it.
           (when (cache-data-for-explanation-p variable)
             (cache-explanation variable))))))
    (t
     ;; stack-eval-warning-message
     (warning-message
       3 "In ~NF, an attempt was made to conclude that the variable ~NF has no ~
         value.  The attempt failed, because the variable was not ~
         active."
       *current-computation-frame*
       variable)))
  (values nil nil nil))







;;;; Variable Activation Actions






;;; The macro `schedule-variable-or-parameter-activation-actions' is called from
;;; the activate-subclass-of-entity method of variables, and causes a variable
;;; to be added to the current list of variables needing activation actions.
;;; The two current activation actions needed for variables are installation of
;;; initial values and initialization of background collection tasks.  Initial
;;; values must be installed in a scheduled task since rules which would receive
;;; forward chaining may be waiting to be activated.  Background collection
;;; interval scheduling must itself be scheduled since GSI interface objects
;;; which provide data service may still need to be activated.

;(def-system-variable variables-scheduled-for-initialization variables nil)

;(def-substitution-macro schedule-variable-or-parameter-activation-actions
;                        (variable-or-parameter)
;  (when (null variables-scheduled-for-initialization)
;    (schedule-current-task 1 'execute-variable-initializations))
;  (setq variables-scheduled-for-initialization
;        (eval-cons
;          (eval-cons variable-or-parameter
;                     (frame-serial-number variable-or-parameter))
;          variables-scheduled-for-initialization)))

;(defun execute-variable-initializations ()
;  (loop do
;    (loop while variables-scheduled-for-initialization
;          repeat 10
;          for variable-cons = (car variables-scheduled-for-initialization)
;          for variable-or-parameter = (car variable-cons)
;          for initial-value? = (initial-value-of-variable-or-parameter
;                                 variable-or-parameter)
;          for interval?
;              = (if (variable-p variable-or-parameter)
;                    (background-collection-interval? variable-or-parameter)
;                    nil)
;          do
;      (when (and (frame-has-not-been-reprocessed-p
;                   variable-or-parameter (cdr variable-cons))
;                 (active-p variable-or-parameter))
;        ;; Install initial value.
;        (when initial-value?
;          (let ((*current-computation-frame* variable-or-parameter))
;            (put-current-value
;              variable-or-parameter initial-value?
;              (type-specification-of-variable-or-parameter-value variable-or-parameter)
;              'never nil nil)))

;        ;; Begin any background collection.
;        (when interval?
;          (let ((data-server? (get-data-server variable-or-parameter)))
;            (when data-server?
;              (cond ((eq data-server? 'computation)
;                     (schedule-cyclic-task
;                       (task-for-background-collection variable-or-parameter)
;                       0 interval?
;                       4
;                       'instigate-current-value
;                       variable-or-parameter))
;                    ((data-server-p data-server?)
;                     (begin-collecting-data
;                       data-server? variable-or-parameter interval?)))))))
;      (reclaim-eval-cons-macro variable-cons)
;      (setq variables-scheduled-for-initialization
;            (prog1 (cdr variables-scheduled-for-initialization)
;                   (reclaim-eval-cons-macro
;                     variables-scheduled-for-initialization))))
;        until (or (null variables-scheduled-for-initialization)
;                  (time-slice-expired-p))
;        finally
;          (when variables-scheduled-for-initialization
;            (schedule-current-task 1 'execute-variable-initializations))))

;(defun clear-variables-scheduled-for-initialization ()
;  (when variables-scheduled-for-initialization
;    (loop for variable-cons in variables-scheduled-for-initialization
;          do
;      (reclaim-eval-cons-macro variable-cons))
;    (reclaim-eval-list-macro variables-scheduled-for-initialization)
;    (setq variables-scheduled-for-initialization nil)))






;;;; Activate, De-activate, and Reset Methods for Variables and Parameters


(def-skip-list-or-binary-tree items-needing-initialization
  :constructor make-items-needing-initialization-tree
  :clearer clear-items-needing-initialization-tree
  :hash-function frame-serial-number-hash
  :key-comparitor frame-serial-number-equal-function
  :key-reclaimer reclaim-frame-serial-number)

;; This macro may need to be moved up further if necessary.
;; See documentation in ACTIVATE

(def-substitution-macro note-item-needing-initialization (item)
  #+development
  (when (eq items-needing-initialization t)
    (break "note-item-needing-initialization called when items-needing-initialization is t"))
;  (setq items-needing-initialization
;        (eval-cons
;          (eval-cons item (copy-frame-serial-number (frame-serial-number item)))
;          items-needing-initialization))
  (setf (get-items-needing-initialization
	  (copy-frame-serial-number (frame-serial-number item))
	  items-needing-initialization-tree)
	item))

(defun note-item-needing-initialization-function (item)
  (note-item-needing-initialization item))



;;; Note that these methods take care of the variable as a whole, including
;;; sub-frames like simulation-subtable, history-frame, etc.  There is currently no
;;; need to define separate methods for the sub-frames.

;;; The activate method for variables sets the variable's active flag, given
;;; that it is in use, ok, and not already active.  It will start background
;;; collection if a background collection interval is specified.  It will set up
;;; tasks to display the variable.  It will also activate things in its
;;; attribute slots.

;;; If a variable has either a background collection interval or an initial
;;; value, then this variable will be added to the list of variables needing
;;; initialization.  The initialization actions cannot be carried out within
;;; this function, since the actions attempt forward chaining, or data service
;;; from other items which are also in the process of being activated.

;;; These collection tasks have been changed from priority 1 to priority 4.
;;; This is so that we will still collect even when falling behind on rules, and
;;; so that these collections will occur before display updating when we are on
;;; schedule.  -jra 1/28/88

(def-class-method activate-subclass-of-entity (variable)
  (when (or (background-collection-interval? variable)
            (initial-value-of-variable-or-parameter variable))
    (note-item-needing-initialization-function variable)))






;;;; Inference Engine Default Updates




;;; This section implements default update intervals for the inference engine.

;;; This facility used to be provided by the function instigate-current-value,
;;; with wake ups from a variable back to itself providing the required interest
;;; list networks.  This suffered from many bugs, and was scrapped in July, 1990
;;; for the current implementation, which uses a sub-structure of a variable to
;;; store the interest list and task pointer for background collection.  -jra
;;; 7/11/90

;;; The structure `inference-background-collection' is used as a sub-structure
;;; of variable's to represent a cyclic background collection of that variable's
;;; value.  It contains an interest list for the request, a task for the
;;; collection, and a pointer back to the variable being collected.

(def-structure (inference-background-collection
                 (:constructor
                   make-inference-background-collection
                   (inference-background-collection-variable)))
  inference-background-collection-variable
  (inference-background-collection-variable-fsn
    (frame-serial-number-recycled))
  (inference-background-collection-task nil :reclaimer cancel-task)
  (things-this-inference-background-collection-is-interested-in nil)
  (inference-background-collection-wake-up-task nil :reclaimer cancel-task)
  (inference-background-collection-postponed-clean-ups nil))




;;; The function `begin-collecting-data-for-inference-engine' takes a variable
;;; and interval at which that variable's value should be collected.  This
;;; function causes a cyclic task to be scheduled to collect cause a request for
;;; this variable's value at the given interval.  The effect of this function
;;; can be cancelled by calling stop-collecting-data-for-inference-engine.

(defun begin-collecting-data-for-inference-engine
    (variable interval)
  (let ((collection-structure (structure-for-background-collection? variable)))
    (when (null collection-structure)
      (setq collection-structure
            (make-inference-background-collection variable))
      (frame-serial-number-setf (inference-background-collection-variable-fsn
                                  collection-structure)
                                (frame-serial-number variable))
      (setf (structure-for-background-collection? variable)
            collection-structure))
    (with-current-scheduling
        ((inference-background-collection-task collection-structure) 4
         (if (fixnump interval)
             (coerce-fixnum-to-gensym-float interval)
             (managed-float-value interval)))
      (perform-background-collection-for-inference-engine
        collection-structure t))))




;;; The function `attempt-new-variable-value-collection' takes a variable and a
;;; priority, and schedules a task to attempt to collect one value for the
;;; variable.  This implements the behavior of the update action for variables
;;; and the probing for failed variables.  If the priority?  argument is passed,
;;; then a task is scheduled, else the attempt at collection is performed within
;;; the recursive descent of this function.  Tasks should be scheduled if it is
;;; possible for this function to be called from within stack-eval.  If the
;;; force? argument is given, then a new value will be collected whether or not
;;; a current value for this variable exists.

;;; This works by piggybacking off of the background collection mechanism for
;;; the inference engine.  If there is no currently existing structure for
;;; background collection for the variable, then a new one is allocated.  Then a
;;; single execution of the perform background collection function is called.
;;; When a wake up is sent from the variable back to this structure, then this
;;; structure is reclaimed if there is no true background collection interval
;;; for this variable.

(defun attempt-new-variable-value-collection (variable priority? force?)
  (let ((collection-structure (structure-for-background-collection? variable)))
    (unless collection-structure
      (setq collection-structure
            (make-inference-background-collection variable))
      (frame-serial-number-setf (inference-background-collection-variable-fsn
                                  collection-structure)
                                (frame-serial-number variable))
      (setf (structure-for-background-collection? variable)
            collection-structure))
    (if priority?
        (with-current-scheduling
            ((inference-background-collection-wake-up-task
               collection-structure)
             priority?)
          (perform-background-collection-for-inference-engine
            collection-structure force?))
        (perform-background-collection-for-inference-engine
          collection-structure force?))
    nil))


;;; The function `wake-up-inference-background-collection' takes a collection
;;; structure and is called when the variable being collected gets a value.  If
;;; this variable does not have a background collection interval, then this
;;; collection structure was made via a call to force-one-new-variable-value-
;;; collection, and the collection structure should be reclaimed.  The
;;; reclamation is handled by stop-collecting-data-for-inference-engine.

(defun-void wake-up-inference-background-collection (collection-structure)
  (let ((variable
          (inference-background-collection-variable collection-structure)))
    (unless (or (frame-has-been-reprocessed-p
                  variable
                  (inference-background-collection-variable-fsn
                    collection-structure))
                (background-collection-interval? variable))
      (stop-collecting-data-for-inference-engine variable))))




;;; The function `perform-background-collection-for-inference-engine' takes an
;;; inference-background-collection structure and performs a single collection
;;; for that structure.  Note that this will force collection of a new piece of
;;; data, even if the variable already has a value.

(defun-void perform-background-collection-for-inference-engine
    (collection-structure force?)
  (let ((variable (inference-background-collection-variable
                    collection-structure)))
    (unless (frame-has-been-reprocessed-p
              variable
              (inference-background-collection-variable-fsn
                collection-structure))
      (let* ((*current-computation-frame* variable)

             (current-computation-instance collection-structure)
             (current-computation-flags current-computation-flags)
             (*variables-that-did-not-have-values* nil))

        (setf (force-new-request-for-value) force?)
        (setf (dont-compute-new-variable-values) nil)

        ;; Clean up any wake up task.
        (cancel-task
          (inference-background-collection-wake-up-task collection-structure))

        ;; Perform a get-current-evaluation-value with new values being forced.
        (open-wake-up-collection-function nil)
        (reclaim-if-evaluation-value (get-current-evaluation-value variable nil))
        (set-wake-ups-function nil)
        (clean-up-wake-ups-state-if-any)))))




;;; The function `stop-collecting-data-for-inference-engine' is used to cancel
;;; the task for background collections of inferred variables, and to cancel any
;;; currently ongoing collection.

(defun-void stop-collecting-data-for-inference-engine (variable)
  (let ((collection-structure (structure-for-background-collection? variable)))
    (when collection-structure
      (loop for variable in
                (things-this-inference-background-collection-is-interested-in
                  collection-structure)
            do
        (remove-request-for-variable-value variable collection-structure))
      (reclaim-eval-list
        (things-this-inference-background-collection-is-interested-in
          collection-structure))
      (setf (things-this-inference-background-collection-is-interested-in
              collection-structure)
            nil)
      (reclaim-inference-background-collection collection-structure)
      (setf (structure-for-background-collection? variable) nil))))





;;; The deactivate method variables clears the variable's active flag given that
;;; it is active.  It will stop background collection and clear wake-up
;;; references.  It will cancel tasks to display the variable.  It will also
;;; deactivate things in its attribute slots.  It will erase histories for now.
;;; Eventually, there will be different modes of running and reset where
;;; histories may not be cleared upon deactivation.

(def-class-method deactivate-subclass-of-entity (variable)
  (let ((data-server? (get-data-server variable)))
    (when data-server?
      (when (data-server-p data-server?)
        (stop-collecting-data data-server? variable))
      (stop-collecting-data-for-inference-engine variable)))
  (cancel-task (task-to-check-variable? variable))
  (setf (time-of-oldest-unsatisfied-request? variable) nil)
  (setf (expiration-time-of-current-value variable) *some-time-ago*)
  (when (managed-float-p (time-of-most-recent-value variable))
    (reclaim-managed-float (time-of-most-recent-value variable)))
  (setf (time-of-most-recent-value variable) *some-time-ago*)

  ;; Reclaim and clear cached explanation.
  (let ((cached-explanation
          (cached-explanation variable)))
    (when cached-explanation
      (reclaim-cached-explanation cached-explanation)
      (setf (cached-explanation variable) nil)))

  (update-representations-of-variable-or-parameter-value variable)
  (cancel-task (task-for-expiration? variable))
  (set-not-failed variable)
  (let ((interested-list (things-interested-in-this-variable variable)))
    (loop for thing in interested-list
          do
      (variable-is-no-longer-available thing variable))
    (reclaim-eval-list-macro interested-list)
    (setf (things-interested-in-this-variable variable) nil))
  (withdraw-backward-chaining variable)
  (clear-histories variable))





(declare-forward-reference clear-histories function)




(def-class-method activate-subclass-of-entity (parameter)
  (note-item-needing-initialization-function parameter)
  nil)

(def-class-method deactivate-subclass-of-entity (parameter)
  (let ((initial-value (initial-value-of-variable-or-parameter parameter)))
    (if (slot-value-float-p initial-value)
        (with-temporary-gensym-float-creation deactivate-subclass-of-entity
          (store-managed-number-or-value
            (current-value-of-variable-or-parameter parameter)
            (slot-value-float-value initial-value)))
        (store-managed-number-or-value
          (current-value-of-variable-or-parameter parameter)
          initial-value)))
  (clear-histories parameter)
  (update-representations-of-variable-or-parameter-value parameter)
  nil)



#+unused
(defun print-interesting-slots ()
  (loop for class being each subclass of 'root
        do (loop for slot-description
                     in (slot-descriptions (class-description class))
                 as slot-initialization
                    = (slot-init-form slot-description)
                 when (or (floatp slot-initialization)
                          (text-string-p slot-initialization)
                          (consp slot-initialization))
                   do (format t "~%~(~a~) = ~s"
                              (unique-slot-name slot-description)
                              (slot-init-form slot-description)))))






;;;; Indexed Attributes




;;; Expressions can reference an item based on the value of an attribute.  An
;;; example is "if there exists a car C such that (the car-id of C =
;;; current-car-id) then".  Normally, the speed of this reference depends on the
;;; number of car instances searched.  To improve the performance of this and
;;; other expressions, an attribute can be defined to be indexed.

;;; An `indexed attribute' provides a fast mapping from the value of an
;;; attribute to its parent object.  The attribute value is used as an index
;;; into a table that hashes parent objects (and defining-classes for the slot).
;;; This feature eliminates the search of items when evaluating the expression.
;;; For example, it can be used to efficiently access unnamed transient objects
;;; based on an attribute value.

;;; Only certain types of attributes and attribute values can be indexed.  Only
;;; attribute parameter or constant attibutes can be indexed since their values
;;; do not expire and they do not require data seeking.  The only valid indexed
;;; attribute values are text, symbol, and integer attribute values.

;;; An expression references an indexed attribute in the same way as any
;;; attribute.  Only certain expressions and statements that reference objects
;;; based on a logical expression can make use of the indexed attribute
;;; optimization.  The expression compiler determines which expressions may make
;;; use indexed attributes.  If the attribute reference can be indexed, the
;;; compiler substitutes the indexed attribute role for the original attribute
;;; reference in the compilation.  The expression evaluator (i.e., the role)
;;; determines at run-time which attributes are indexed.  If the attribute is
;;; indexed for the specified class, the attribute index (hash) table is checked
;;; for that value.  Otherwise, all objects of the class are searched for the
;;; attribute value.

;;; The expressions and statements that check for indexed attributes are:
;;;
;;; THERE EXISTS a(n) <object> such that (<restricted logical expression>)
;;;
;;; the COUNT of each <object> such that (<restricted logical expression>)
;;;
;;; {call | start} INDEXED-ATTRIBUTE-ITEM-LIST
;;;                (<item-list>, <class>, <attribute>, <wait-state-flag>)

;;; See the predicate expression-may-use-indexed-attribute-p for a description
;;; of the <restricted logical expression> format.  Not all logical expressions
;;; can make use of the indexed-attribute optimization.

;;; An indexed attribute is defined in its parent object definition with the
;;; following grammar.

;;; For text, symbolic, integer, quantitative parameters:
;;;
;;; <attribute> is given by a(n) <class of parameters>, WITH AN INDEX
;;; <attribute> a(n) instance of <class of parameters>, WITH AN INDEX

;;; For symbolic parameters:
;;;
;;; <attribute> [, has values <list of allowed values>,]
;;;             and is given by <class of parameters>, WITH AN INDEX

;;; For constants:
;;;
;;; <attribute> [is <constant value>], WITH AN INDEX
;;; <attribute> [has values <list of allowed values>]
;;;             [, (default is <allowed value>)], WITH AN INDEX



;;; The attribute index tables are maintained as follows.

;;; When an attribute receives a value, that value is used as the key to hash
;;; the parent object (and defining class of the slot) into the hash-table.
;;; There may be more than one object hashed for a value because one hash table
;;; is used for all classes that index the given attribute.  The hash-table
;;; maintains a list of parent objects and defining-classes for a value which is
;;; updated as new values are added or removed, objects are deleted, and object
;;; definitions are created, deleted, or modified.  This is described below.

;; Note that in version 3.0, only the parent object was hashed.  Now in version
;; 4.0, both the parent object and the defining class for the slot are hashed.
;; This change was necessary because, with multiple-inheritance, an object may
;; now contain more than one slot with the same pretty-slot-name.  This does
;; slow down the indexed-attribute expression, but this should not be so
;; significant.  It adds an extra hash-table lookup to locate the
;; slot-description and defining-class for the hashed parent.  It would also add
;; another hash-table lookup if the attribute reference contains a
;; class-qualified name, of the form, "class::attribute".  - cpm, 2/20/94

;;; Initial constant value - Upon activation of the parent object, an indexed
;;; constant attribute hashes the parent object using the initial value as the
;;; index.

;;; Initial parameter values and new, different constant or parameter attribute
;;; values - When an indexed constant receives a new value or a parameter
;;; receives a new and different value through an edit, conclude, forward
;;; chaining, or other data service, the parent object will be removed from the
;;; old index in the hash table and the parent object will be hashed at the
;;; index of the new value.

;;; Constant value of "none" - If the user edits an attribute constant such that
;;; it receives a new value which is "none", the parent object is removed from
;;; the indexed hash table location.

;;; Deletion of indexed parameter - When an indexed parameter is manually
;;; deleted, the parent object is removed from the indexed hash table location.

;;; Deletion of parent object - When a parent object is deleted manually or
;;; through a delete action, any attribue index hash tables are updated or
;;; deleted as necessary.

;;; Deletion of an object definition with indexed attributes - When a
;;; deletion of this definition occurs, the hash table(s) are either updated or
;;; deleted depending on whether there are any other classes that are indexing
;;; the same attribute(s).

;;; Deactivation or deletion of the attribute object or parent object will cause
;;; the parent object to be removed from the hash-table.

;;; Reset - When G2 is reset, the hash-table is reclaimed.

;;; Save KB - Attribute index information is not saved to a kb.  The attribute
;;; index defining information of an object class definition is saved.




;;; `Indexed-attribute-hash-table' is a kb-specific property based on an indexed
;;; attribute.  It contains the hash-table that indexes the attribute for any
;;; class.  The hash-table property value is present only when G2 is not reset.

(def-kb-specific-property-name indexed-attribute-hash-table)


;;; `Indexed-attribute-classes' is a kb-specific property based on an indexed
;;; attribute.  It contains a list of the classes that defined, not inherit,
;;; this attribute to be indexed.  But, if a class inherits and also defines the
;;; attribute as indexed, it will be in this list.

;;; If this property is nil, the attribute is not indexed.  This is a better
;;; test than the hash-table property since it may not yet be created.

(def-kb-specific-property-name indexed-attribute-classes)


;;; `*Indexed-attributes*' is a kb-specific variable that contains a list of all
;;; the attributes that are currently indexed.  This variable is kept up to date
;;; as class definitions that affect indexed attributes are modified.

(def-kb-specific-variable *indexed-attributes* variables nil)




;;; The binary tree `indexed-attribute-defining-classes' is used in the
;;; indexed-attribute-hash-table to hold the set of blocks that have a given
;;; value for an indexed attribute.  The values in this binary tree are a
;;; gensym-conses list of the class names that define the attribute that
;;; contains the indexed value.

(def-skip-list-or-binary-tree indexed-attribute-defining-classes
    :constructor make-indexed-attribute-defining-classes-tree
    :reclaimer reclaim-indexed-attribute-defining-classes-tree
    :hash-function frame-hash-function
    :entry-reclaimer reclaim-gensym-list-macro
    :set-if-no-entry-given-hash set-indexed-attribute-defining-classes-if-no-entry
    :use-binary-tree nil)


;;; `Has-indexed-attributes' is a non-savable frame-flag that indicates whether
;;; an object contains an constant or parameter attribute that is indexed.  This
;;; flag allows a fast test for a possible indexed attribute.  This test can be
;;; used without affecting the speed of concluding new values.  This flag is
;;; defined in FRAMES3.




;;; The substitution-macro `hash-indexed-attribute-value' takes an
;;; attribute-value to be hashed into the indexed-attribute-parent-objects hash
;;; table and returns a non-negative fixnum hash for the given value.

(def-substitution-macro hash-indexed-attribute-value (attribute-value)
  (cond ((fixnump attribute-value)
         (absf attribute-value))
        ((symbolp attribute-value)
         (sxhash-symbol attribute-value))
        ((text-string-p attribute-value)
         (compute-text-hash-code attribute-value))
        (t 0)))




;;; `Indexed-attributes-for-definition' is a slot on class definitions that
;;; contains a list of attributes that are defined to be indexed for that class.
;;; This slot does not included inherited attributes that are indexed or
;;; inherited attributes that are redefined for the class not be indexed.  This
;;; slot is defined in DEFINITIONS.



;;; `Indexed-attribute-parent-objects' is a hash table that maps indexed
;;; attribute values to a binary tree of parent objects and defining-classes of
;;; slots.  The hash table is of the default size, currently 43.

;;; There is a reclaimer defined for the key.  The key is
;;; copied before doing a setf on an entry because several item entries can
;;; share the same key, which is an attribute value, and the attribute value is
;;; reclaimed as the attribute value of an entry changes.

(def-hash-table indexed-attribute-parent-objects
    :hash-function-or-macro hash-indexed-attribute-value
    :key-comparitor evaluation-value-equal-p
    :key-reclaimer reclaim-evaluation-value
    :entry-reclaimer reclaim-indexed-attribute-defining-classes-tree)

;; Note that this format is new to version 4.0.  Previously, only the parent
;; objects were hashed.  See related comments above.  - cpm, 2/20/94

;; Note, if the keys can be evaluation-values other than symbol, text, and
;; integer, the key-comparitor would also need to be modified.  - cpm, 9/7/94



;;; The functions `make-indexed-attribute-hash-table' and
;;; `reclaim-indexed-attribute-hash-table' handle creating and reclaiming the
;;; hash-table and adding or removing it from the indexed-attribute-hash-table
;;; kb-property of the attribute.

;;; The reclaim function iterates over all entries of the hash-table, reclaiming
;;; the lists of parent objects in the entry.  The entry data structures will be
;;; reclaimed when the hash-table itself is reclaimed.  Therefore,
;;; delete-indexed-attribute-parent-objects is not called on the entry.  The key
;;; has a reclaimer defined for it, so it will be reclaimed with the hash-table.

(defun make-indexed-attribute-hash-table (attribute-name)
  (setf (indexed-attribute-hash-table attribute-name)
        (make-indexed-attribute-parent-objects)))

(defun reclaim-indexed-attribute-hash-table (attribute-name)
  (let ((hash-table? (indexed-attribute-hash-table attribute-name)))
    (when hash-table?
      (reclaim-indexed-attribute-parent-objects hash-table?)
      (setf (indexed-attribute-hash-table attribute-name) nil))))



;;; The function `clear-indexed-attribute-hash-table' clears the given
;;; hash-table by first iterating over all the hashed-values and reclaiming
;;; them.  (The hash-table does not have a reclaimer for the hashed-values.

(defun clear-indexed-attribute-hash-table (attribute-name)
  (let ((hash-table? (indexed-attribute-hash-table attribute-name)))
    (when hash-table?
      (clear-indexed-attribute-parent-objects hash-table?))))



;;; The functions `make-all-indexed-attribute-hash-tables' and
;;; `reclaim-all-indexed-attribute-hash-tables' create and reclaim the
;;; hash-tables for all attributes that are already declared to be indexed.

(defun make-all-indexed-attribute-hash-tables ()
  (loop for attribute in *indexed-attributes*
        do
    (make-indexed-attribute-hash-table attribute)))

(defun reclaim-all-indexed-attribute-hash-tables ()
  (loop for attribute in *indexed-attributes*
        do
    (reclaim-indexed-attribute-hash-table attribute)))



;;; The function `put-indexed-attribute-parent' accepts four arguments, an
;;; attribute (used to determine the hash table), a defining class for the
;;; attribute, an attribute value (a hash key), and an attribute parent item.  A
;;; binary tree containing the parent item and defining slot class is the hashed
;;; value.

;;; The item and defining class are added to the tree of values hashed at that
;;; key.  (More than one item and more than one attribute of the same item can
;;; have the same attribute value.)  Note that this function does not reenter
;;; the parent and defining class pair if they are already in the tree.  This is
;;; necessary since several classes may be updating the hash-table, where one
;;; class is a subclass of the other.

;;; Note that if there was a previous hashed value for this object, defining
;;; class, and attribute, delete-indexed-attribute-item should be called before
;;; this function!

(defun-simple put-indexed-attribute-parent
    (attribute defining-attribute-class attribute-value attribute-parent-object)
  (let ((indexed-attribute-hash-table?
          (indexed-attribute-hash-table attribute)))
    (when indexed-attribute-hash-table?
      (let* ((new-attribute-value-tree
               (make-indexed-attribute-defining-classes-tree))
             (attribute-evaluation-value (copy-evaluation-value attribute-value))
             (stored-attribute-value-tree
               (set-indexed-attribute-parent-objects-if-no-entry
                 attribute-evaluation-value
                 indexed-attribute-hash-table?
                 new-attribute-value-tree)))
        (cond
          ((eq stored-attribute-value-tree new-attribute-value-tree)
           (setf (get-indexed-attribute-defining-classes
                   attribute-parent-object
                   new-attribute-value-tree)
                 (gensym-list defining-attribute-class)))
          (t
           (reclaim-evaluation-value attribute-evaluation-value)
           (reclaim-indexed-attribute-defining-classes-tree
             new-attribute-value-tree)
           (let* ((new-class-list (gensym-list defining-attribute-class))
                  (stored-class-list
                    (set-indexed-attribute-defining-classes-if-no-entry
                     attribute-parent-object
                     stored-attribute-value-tree
                     (frame-hash attribute-parent-object)
                     new-class-list)))
             (unless (eq stored-class-list new-class-list)
               (cond ((memq defining-attribute-class stored-class-list)
                      (reclaim-gensym-cons new-class-list))
                     (t
                      ;; Splice in the new class-list cons.
                      (setf (cdr new-class-list)
                            (cdr-of-cons stored-class-list))
                      (setf (cdr stored-class-list)
                            new-class-list)))))))))))



;;; The function `remove-indexed-attribute-parent' is used to remove a parent
;;; object and defining class pair from the indexed-attribute hash-table.  It is
;;; used to remove an old hashed value, before the new value is about to be
;;; added.

(defun-simple remove-indexed-attribute-parent
    (attribute attribute-defining-class attribute-value attribute-parent-object)
  (let* ((hash-table?
           (indexed-attribute-hash-table attribute))
         (defining-classes-tree?
           (when hash-table?
             (get-indexed-attribute-parent-objects
               attribute-value hash-table?)))
         (classes-list?
           (when defining-classes-tree?
             (get-indexed-attribute-defining-classes
               attribute-parent-object defining-classes-tree?))))
    (when (memq attribute-defining-class classes-list?)
      (cond ((neq (car-of-cons classes-list?) attribute-defining-class)
             (delete-gensym-element attribute-defining-class classes-list?))
            ((null (cdr-of-cons classes-list?))
             (delete-indexed-attribute-defining-classes
               attribute-parent-object defining-classes-tree?)
             (when (skip-list-or-binary-tree-empty-p defining-classes-tree?)
               (delete-indexed-attribute-parent-objects
                 attribute-value
                 hash-table?)))
            (t
             ;; In this case, the first cons in the list holds the class we want
             ;; to remove, and there are more classes remaining in the rest of
             ;; the list.  The SETF into the binary tree will reclaim the list
             ;; in the tree that we are overwriting, which would reclaim the
             ;; remaining conses of the class list that we want to retain.  So
             ;; the following line could work by calling COPY-GENSYM-LIST on the
             ;; value we place into the binary tree. Instead, we'll do a little
             ;; list manipulation to prevent the conses we want from being
             ;; reclaimed and let the normal reclaiming of the old value in the
             ;; binary tree handle reclaiming the cons we want to get rid of.
             (let ((remaining-classes (cdr-of-cons classes-list?)))
               (setf (cdr classes-list?) nil)
               (setf (get-indexed-attribute-defining-classes
                       attribute-parent-object defining-classes-tree?)
                     remaining-classes)))))))




;;; The function `valid-indexed-attribute-value-p' is used to test the attribute
;;; value is of a type that can be indexed.  The type of the value must be text,
;;; integer, or symbol.

(defun-simple valid-indexed-attribute-value-p (attribute-value)
  (or (fixnump attribute-value)
      (symbolp attribute-value)
      (text-string-p attribute-value)))



;;; The function `Of-valid-indexed-attribute-class-p' takes a frame and tests if
;;; the attribute object is of the correct class to be indexed.

(defun-simple of-valid-indexed-attribute-class-p (attribute-object)
  (and (parameter-p attribute-object)
       (not (logical-parameter-p attribute-object))))



;;; The function `indexed-attribute-or-inherited-attribute-p' is used to
;;; determine that the attribute is defined to be indexed for a given object.
;;; The class argument is used as a qualifier for the attribute name.

(defun-simple indexed-attribute-or-inherited-attribute-p
    (attribute-name class parent-object)
  (when (and (has-indexed-attributes-p parent-object)
             (frame-of-class-p parent-object class))
    (let ((class-description (class-description class)))
      (when class-description
        (loop for indexed-class in (indexed-attribute-classes attribute-name)
              thereis (class-description-of-class-p
                        class-description indexed-class))))))




;;; The function `indexed-attribute-for-class-p' is used to determine if the
;;; attribute is defined to be indexed for a given class.  This function
;;; checks the attribute defined at the class, not inherited attributes.

#+unused
(defun-simple indexed-attribute-for-class-p (attribute-name class)
  (when (get-class-feature-if-any class 'has-indexed-attributes)
    (memq class (indexed-attribute-classes attribute-name))))




;;; The function `indexed-attribute-or-inherited-attribute-for-class-p' is used
;;; to determine if the attribute is defined to be indexed for a given class or
;;; superior class.

(defun indexed-attribute-or-inherited-attribute-for-class-p
    (attribute-name class)
  (when (get-class-feature-if-any class 'has-indexed-attributes)
    (loop with class-description? = nil
          for indexed-class in (indexed-attribute-classes attribute-name)
          thereis (class-description-of-class-p
                    (or class-description?
                        (setq class-description? (class-description class)))
                    indexed-class))))



;;; The function `get-and-validate-indexed-attribute-value' is used when
;;; updating the indexed attribute hash-table based on a current attribute
;;; value.  This function either gets the current value of an attribute
;;; parameter object, gets the cached value of a temporary-constant, or converts
;;; the slot-value of an attribute constant to a datum.

(defun get-and-validate-indexed-attribute-value (attribute-value?)
  (let ((attribute-datum?
          (cond ((framep attribute-value?)
                 (when (of-valid-indexed-attribute-class-p attribute-value?)
                   (extract-cached-number-or-value
                     (current-value-of-variable-or-parameter
                       attribute-value?))))
                ((temporary-constant-p attribute-value?)
                 (cached-constant-value attribute-value?))
                ((slot-constantp attribute-value?)
                 (get-slot-value-number-or-string-from-slot-constant
                   attribute-value?))
                (t attribute-value?))))
    (if (and attribute-datum?
             (valid-indexed-attribute-value-p attribute-datum?))
        attribute-datum?
        nil)))



;;; The function `put-parent-if-indexed-attribute' puts the parent and defining
;;; attribute class in the indexed attribute hash-table, if possible.  The hash
;;; is done if the attribute is indexed for the slot class and if the attribute
;;; value can be indexed.

;;; This function is used to update the hash-table when an attribute receives a
;;; new value.

;;; Note that if the old and new attribute values are equal, the hashed values
;;; are not changed.  Also, if an old-attribute-value argument is non-NIL, the
;;; parent is removed from the corresponding hash table location.

;;; The attribute-defining-class argument is need to locate the correct
;;; attribute for the object.

(defun put-parent-if-indexed-attribute
    (attribute-name attribute-defining-class attribute-value
                    old-attribute-value? attribute-parent-object)
  (let ((valid-old-attribute-value? nil)
        (valid-attribute-value? nil))
    (when (and (not (equal attribute-value old-attribute-value?))
               (indexed-attribute-or-inherited-attribute-p
                 attribute-name attribute-defining-class
                 attribute-parent-object))
      ;; Remove the the old hashed value if there is one.
      (when old-attribute-value?
        (setq valid-old-attribute-value?
              (get-and-validate-indexed-attribute-value old-attribute-value?))
        (when valid-old-attribute-value?
          (remove-indexed-attribute-parent
            attribute-name attribute-defining-class valid-old-attribute-value?
            attribute-parent-object)))
      ;; Add the new hashed value.
      (setq valid-attribute-value?
            (get-and-validate-indexed-attribute-value attribute-value))
      (when valid-attribute-value?
        ;; Hash the parent object, only if the attribute value is of the correct
        ;; type.  Otherwise, don't hash and don't issue a warning.  (Version 3.0
        ;; gave a warning, in this case.  Starting in 4.0, we won't give a
        ;; warning.  - cpm, 1/6/94)
        (put-indexed-attribute-parent
          attribute-name attribute-defining-class valid-attribute-value?
          attribute-parent-object)))))



;;; The function `put-parent-for-its-indexed-constant-attributes' tests if the
;;; parent contains any indexed constant attributes.  If any are found, it
;;; hashes the parent in the hash-table of these indexed attributes.  This
;;; function is used when the parent object is activated and the initial
;;; constant values need to be updated in the hash-table.  (Note that parameter
;;; values and new constant values are updated in the hash-table elsewhere
;;; through true-value-update.)

;;; Note that this function does not any remove old hashed values.  (There
;;; should be none.)

(defun put-parent-for-its-indexed-attributes (attribute-parent-object
                                               &optional do-frames?)
  (when (has-indexed-attributes-p attribute-parent-object)
    (let ((indexed-attribute-alist
            (collect-all-indexed-attributes-for-object
              attribute-parent-object)))
      (loop for (indexed-attribute . defining-class) in indexed-attribute-alist
            for slot-description-from-class? =
                (slot-description-from-class
                  defining-class indexed-attribute defining-class)
            for attribute-value? =
                (get-slot-value-if-any
                  attribute-parent-object indexed-attribute defining-class)
            do
        ;; See note 1 below.
        (when (and slot-description-from-class?
                   (eq defining-class
                       (defining-class slot-description-from-class?))
                   (or do-frames?
                       (not (framep attribute-value?))))
          (put-parent-if-indexed-attribute
            indexed-attribute defining-class attribute-value? nil
            attribute-parent-object))
            finally
              (reclaim-gensym-tree indexed-attribute-alist)))))

;; NOTE 1: The defining-class check is needed to verify that the hash is made
;; only with the class that defines the slot and not an inherited class.  This
;; is necessary because future updates to the hash depend on this.  (Both the
;; parent object and attribute defining class make up the hashed value.)
;;
;; This fixes a bug (HQ-582103) that occurs if the indexed-attributes-for-
;; definition contains any inherited indexed attributes.  Note that, per GHW,
;; this slot should no longer be able to get into this state.  But, we need to
;; handle those definitions that are already in this state.  - cpm, 1/11/96



;;; The function `remove-parent-if-indexed-attribute-parent' tests and removes
;;; the parent from the indexed attribute hash-table if necessary.  This
;;; function is used when an attribute is being deactivated and the hash-table
;;; needs to be updated.  Note, that attribute-value is either a constant
;;; attribute value or an attribute object, such as a parameter.  The class
;;; argument is used to qualify the attribute reference.

(defun remove-parent-if-indexed-attribute
    (attribute-name attribute-defining-class attribute-value
                    attribute-parent-object)
  (when (indexed-attribute-or-inherited-attribute-p
          attribute-name attribute-defining-class attribute-parent-object)
    (let ((valid-attribute-value?
            (get-and-validate-indexed-attribute-value attribute-value)))
      (when valid-attribute-value?
        (remove-indexed-attribute-parent
          attribute-name attribute-defining-class valid-attribute-value?
          attribute-parent-object)))))



;;; The function `remove-parent-for-its-indexed-attributes' tests if the parent
;;; contains any indexed attributes.  If any are found, it removes the parent
;;; from the hash-table of these indexed attributes.  This function is used when
;;; the parent object is being deactivated and the hash-table needs to be
;;; updated.

(defun remove-parent-for-its-indexed-attributes (attribute-parent-object)
  (when (has-indexed-attributes-p attribute-parent-object)
    (let ((indexed-attribute-alist
            (collect-all-indexed-attributes-for-object
              attribute-parent-object)))
      (loop for (indexed-attribute . class) in indexed-attribute-alist
            for attribute-value? =
                (get-slot-value-if-any
                  attribute-parent-object indexed-attribute class)
            do
        (when attribute-value?
          (remove-parent-if-indexed-attribute
            indexed-attribute class attribute-value? attribute-parent-object))
        finally
          (reclaim-gensym-tree indexed-attribute-alist)))))



;;; The functions `collect-all-indexed-attributes-for-object' and
;;; `collect-all-indexed-attributes-for-class' are used to generate a
;;; gensym-list of indexed-attributes that are defined at or inherited by the
;;; class or object argument.

;;; The form of the tree is: ((pretty-slot-name . class) ...)

;;; IMPORTANT: Note that the list of gensym-conses should be RECLAIMED by the
;;; caller, for example, using RECLAIM-GENSYM-TREE.

(defun collect-all-indexed-attributes-for-object (object)
  (collect-all-indexed-attributes-for-class (class object)))

(defun collect-all-indexed-attributes-for-class (class)
  (when (get-class-feature-if-any class 'has-indexed-attributes)
    (loop for inherited-class in
            (class-inheritance-path (class-description class))
          for inherited-class-def = (class-definition inherited-class)
          with indexed-attribute-list? = nil
          ;; the following check blocks looking at superior classes
          ;; that are system-defined
          ;; NB. listp check here rather than consp because
          ;; we do not want to allow inherited-class-def to be
          ;; nil.
          unless (listp inherited-class-def)
            do
              (loop for indexed-attribute in
                    (indexed-attributes-for-definition inherited-class-def)
                    for new-indexed-attribute-list =
                    (gensym-list (gensym-cons indexed-attribute inherited-class))
                    do
                (cond ((null indexed-attribute-list?)
                       (setq indexed-attribute-list? new-indexed-attribute-list))
                      (t
                       (setq indexed-attribute-list?
                             (nconc
                               indexed-attribute-list? new-indexed-attribute-list)))))
          finally
            (return indexed-attribute-list?))))



;;; The function `update-indexed-attribute-hash-table' is used to update a new
;;; or cleared hash-table with indexed parent objects for the given attribute.

;;; This function is not the normal method of hash-table update, which is done
;;; from true-value update.  This function is called when the hash-table needs
;;; to updated for existing attribute values.  For example, this is necessary
;;; when a class definition no longer indexes an attribute or when a warm-boot
;;; has occurred.

;;; This function iterates over the instances of all classes that index the
;;; attribute.  If each instance contains an attribute constant or object that
;;; can be indexed, the hash-table is updated with the parent object.

(defun update-indexed-attribute-hash-table (indexed-attribute)
  (loop with indexed-classes? = (indexed-attribute-classes indexed-attribute)
        for indexed-class in indexed-classes?
        do
    (loop for class being each subclass of indexed-class
          for slot-description = (slot-description-from-class
                                   class indexed-attribute indexed-class)
          do
      (loop for indexed-item being each strict-class-instance of class
            do
        (when (active-p indexed-item)
          (let* ((slot-value?
                   (get-slot-description-value indexed-item slot-description))
                 (indexed-attribute-value?
                   (when slot-value?
                     (get-and-validate-indexed-attribute-value slot-value?))))
            (when indexed-attribute-value?
              (put-indexed-attribute-parent
                indexed-attribute indexed-class indexed-attribute-value?
                indexed-item))))))))




;;; The function `update-all-indexed-attribute-hash-tables' is used to
;;; update indexed attribute hash tables, e.g., after a warm-boot.  This
;;; function assumes that the hash-tables have already been created.

(defun update-all-indexed-attribute-hash-tables ()
  (loop for attribute in *indexed-attributes*
        do
    (update-indexed-attribute-hash-table attribute)))



;;; The function `expression-may-use-indexed-attribute-p' is a test that should
;;; be done during expression compilation to see if the expression is of the
;;; form that can make use of indexed-attributes.  If this predicate is true,
;;; the actual attribute and value still need to be tested when the expression
;;; is evaluated.

;;; If the expression may use an indexed attribute, the logical (sub)expression
;;; containing the attribute reference is returned.  Otherwise, NIL is returned.

;; NOTE: This has been modified to return the logical expression that may use an
;; indexed-attribute, instead of only the name.  Since this expression can now
;; also be found anywhere in the top-level of an "and" expression, we don't want
;; to search for the logical-expression again.  We need the expression that is
;; compared to the attribute-value within the logical-expression.  - cpm,
;; 9/26/91

;;; Only the logical-expression there-exists and "the count of" and the system
;;; procedure indexed-attribute-item-list can use indexed-attributes.  This
;;; function tests does not test for the system procedure which only needs to do
;;; the evaluation tests.

;;; The logical expression must have the following format for this predicate to
;;; be true.

;;; The object reference must be of the form: <class-name>
;;; not a more complicated reference such as: <class-name> connected to <object>

;;; The logical expression must be of the form:
;;;    <indexed-attribute-designation>
;;;       = <symbolic, text, or integer expression>
;;; or
;;;    <indexed-attribute-designation>
;;;       is <symbolic value>
;;; or
;;;    [<logical-expression> and]
;;;    <indexed-attribute-designation>
;;;       = <symbolic, text, or integer expression> and
;;;    [and <logical-expression>] ...
;;; or
;;;    [<logical-expression> and]
;;;    <indexed-attribute-designation>
;;;       is <symbolic value>
;;;    [and <logical-expression>] ...

;;; where <indexed-attribute-designation> is of the form:
;;;    the <indexed-attribute> of {<local-name> | the <class>}
;;; OR
;;;    the <class>::<indexed-attribute> of {<local-name> | the <class>}

;;  The second form of the attribute designation, the class-qualified-name, is
;;  new for version 4.0.  - cpm, 2/21/94

;;; Note that an OR expression can not be the outer expression, e.g., "the x of
;;; foo is ok AND the y of foo is not ok OR the z of foo is blue".  The OR can
;;; be a top-level expression of an AND expression, if the OR expression has
;;; parens surrounding it so that the AND takes precedence.  An example is "the
;;; x of foo is ok AND (the y of foo is not ok OR the z of foo is blue)".  Note
;;; that in this case, the indexed attribute is only recognized in the top-level
;;; form of the AND and not in a sub-expression of the OR.

;; The predicate handles the various compilations:
;;
;; Rule
;;   role:  (class class)
;;   role and local name: (class local)
;;   attribute-domain: class | attribute
;; Procedure:
;;   role:  (class)
;;   role and local name: ((class . local))
;;   attribute-domain: (the class) | attribute

;; IMPORTANT: Update this predicate if the above list of compilations change or
;; is not complete!!  cpm, 7/31/91

(defun expression-may-use-indexed-attribute-p (expression)
  (let ((operator? (when (consp expression) (first expression))))
    ;; Test the operator, role, and logical-expression for the correct format.
    ;; Note that the expression contained in the logical operator is not tested
    ;; here.  It's value is tested when the role is here.  It's value is tested
    ;; when the role is evaluated.
    (when (or (eq operator? 'there-exists-literal)
              (eq operator? 'count))
      (gensym-dstruct-bind
          ((nil (role var-spot-or-symbol domain?) logical-expression)
           expression)
        (when (consp logical-expression)
          (loop with logical-expression-list? =
                (when (eq (first logical-expression) 'and)
                  (cdr logical-expression))
                for possible-equality-expression?
                    = (cond (logical-expression-list?
                             (car logical-expression-list?))
                            ;; OR cannot be at the top-level.
                            ((eq (first logical-expression) 'or) nil)
                            (t logical-expression))
                    then (when logical-expression-list?
                           (car logical-expression-list?))
                with indexed-attribute-expression-found? = nil
                while possible-equality-expression?
                do
            (when (and (consp possible-equality-expression?)
                       ;; possible attribute role
                       (consp (second possible-equality-expression?))
                       ;; Truth-values(i.e. (1000 . truth-value) )were getting
                       ;; through the previous test which screwed up the
                       ;; destructuring bind. -dkuznick, 7/21/99
                       (designation-p (second possible-equality-expression?)))
              ;; Test for an equality expression that can use indexing.
              ;; Also, test the role and domain of the main expression.
              (gensym-dstruct-bind
                  ((op (attribute-quantifier attribute-role attribute-domain?)
                       . expression?)
                   possible-equality-expression?)
                (when (and (or (eq op '=)
                               (eq op 'is))
                           (eq attribute-quantifier 'the)
                           (or (symbolp attribute-role)
                               ;; class::attribute reference
                               (class-qualified-name-list-p attribute-role))
                           ;; Test the main expression role and domain.
                           (null domain?)
                           ;; Test that the attribute refers to the class or
                           ;; local name in the role.
                           (if (symbolp role)
                               (or
                                 ;; Rule, no local name.
                                 (eq attribute-domain? role)
                                 ;; Rule local name.
                                 (eq attribute-domain? var-spot-or-symbol)
                                 ;; Procedure with no local name,
                                 ;; attribute-domain of the form (the <class>).
                                 (and (consp attribute-domain?)
                                      (eq (car attribute-domain?) 'the)
                                      (cdr attribute-domain?)
                                      (null (cddr attribute-domain?))
                                      (eq (second attribute-domain?) role)))
                               ;; Procedure Role: (attribute . local-name)
                               (and (consp role)
                                    (symbolp (simple-role-of-role role))
                                    ;; this may keep a rule from going further
                                    (not (consp (cdr role)))
                                    ;; Test that the attribute-domain refers
                                    ;; to the attribute in the role.
                                    (or (eq attribute-domain? (car role))
                                        (eq attribute-domain? (cdr role))
                                        (and (consp attribute-domain?)
                                             (eq (car attribute-domain?) 'the)
                                             (cdr attribute-domain?)
                                             (null (cddr attribute-domain?))
                                             (eq (second attribute-domain?)
                                                 (car role))))))
                           ;; The type of the value of the expression is
                           ;; tested at run-time.
                           (not (null expression?))
                           ;; Return the attribute role if the predicate is
                           ;; true.
                           attribute-role)
                  (setq indexed-attribute-expression-found? t))))

            (setq logical-expression-list? (cdr logical-expression-list?))

                until indexed-attribute-expression-found?
                finally
                  (return (when indexed-attribute-expression-found?
                            possible-equality-expression?))))))))



;;; The function `update-indexed-attribute-properties' is used to update
;;; information related to indexed-attributes.  This should be called, for
;;; example, when an object-definition has been read in or modified.  It updates
;;; the list of indexed-attributes, the list of indexed-attribute classes,
;;; true-value updating, and the hash-table, when necessary.  "Update" means to
;;; add or remove indexed-attribute information, as needed.  To remove
;;; information the remove-old-indexed-attributes-if-necessary? argument must be
;;; non-NIL.

;;; Note that if the definition has changed, this function should be called
;;; after the changes have been installed in the definition and propagated to
;;; the instances.

;;; Also, if the definition has changed, such that any existing indexed-
;;; attributes are affected, pass a non-NIL remove-old-indexed-attributes-
;;; if-necessary? argument.  The old-indexed-attributes-if-different? and
;;; old-class-name-if-different? are provided, in this case, if they have been
;;; changed in the definition.  In this case, the old indexed-attribute
;;; information needs to be removed before any new indexed-attribute information
;;; is added.

;;; This function is called from the slot putters in DEFINITIONS which can
;;; affect existing indexed-attribute hash tables and installations of true
;;; value updates.

;;; This function can be called either for definitions that have instance and
;;; those that do not.

(defun-void update-indexed-attribute-properties
    (definition remove-old-indexed-attributes-if-necessary?
        old-indexed-attributes-if-different? old-class-name-if-different?)
  (let* ((current-class-name? (name-of-defined-class definition))
         (current-indexed-attributes?
           (indexed-attributes-for-definition definition))
         (old-class-name?
           (or old-class-name-if-different? current-class-name?))
         (old-indexed-attributes?
           (or old-indexed-attributes-if-different?
               current-indexed-attributes?))
         (test-if-old-indexed-attribute-is-still-defined?
           (and remove-old-indexed-attributes-if-necessary?
                current-class-name?
                current-indexed-attributes?
                (eq old-class-name? current-class-name?)))
         (any-class-instances? nil))

    (when (and current-class-name? (classp current-class-name?))
      (loop for thing being each class-instance of current-class-name?
            do
        (setq any-class-instances? t)
            until any-class-instances?))
    (when (and (null any-class-instances?)
               old-class-name?
               (classp old-class-name?))
      (loop for thing being each class-instance of old-class-name?
            do
        (setq any-class-instances? t)
            until any-class-instances?))


    ;; Remove old indexed attribute information, when the attribute is not in
    ;; the list of currently indexed-attributes.  Update the list of indexed
    ;; attribute classes, true-value updating, and the hash-table.
    (when (and remove-old-indexed-attributes-if-necessary?
               old-indexed-attributes?
               old-class-name?)
      (remove-indexed-attribute-properties
        old-indexed-attributes?
        old-class-name?
        (if test-if-old-indexed-attribute-is-still-defined?
            current-indexed-attributes?
            nil)
        ;; Value for the update-hash-table-if-necessary? argument.
        (if (or loading-kb-p
                currently-automatically-resolving-class-name-conflicts?)
            nil
            any-class-instances?)))

    ;; Add new indexed attribute information, if it is not in the old
    ;; indexed-attribute list.  Update the list of indexed-attribute classes,
    ;; true-value updating, and the hash-table.  Note that when there are
    ;; instances of the class, the hash-table is always updated, even if the
    ;; attribute was in the old indexed-attribute list.
    (when (and current-class-name? current-indexed-attributes?)
      ;; Always update the hash-table.  This is necessary, even if the attribute
      ;; was in the list of old indexed-attributes.  If the attribute is
      ;; continuing to be indexed, other information, such as class or
      ;; superior-classes, could have changed such that the hash-table still
      ;; needs updating.  For example, a hashed item may no longer be of a class
      ;; that indexes the attribute.
      (add-indexed-attribute-properties
        current-indexed-attributes? current-class-name?
        ;; The value for the update-hash-table-if-necessary? argument.
        (if (or loading-kb-p
                currently-automatically-resolving-class-name-conflicts?)
            nil
            any-class-instances?)
        t))))



;;; The function `remove-indexed-attribute-properties' removes the
;;; indexed-attribute attribute information and hash-table for an attribute.
;;; Note that if the indexed-attributes-to-keep? is non-NIL, those attributes in
;;; this list are not removed.

(defun-void remove-indexed-attribute-properties
    (indexed-attribute-to-remove class-name indexed-attributes-to-keep?
                                 update-hash-table-if-necessary?)
  (loop for indexed-attribute in indexed-attribute-to-remove
        for indexed-attribute-classes? =
          (indexed-attribute-classes indexed-attribute)
        with update-designation =
          ;; Reclaimed below.
          (gensym-list 'the nil (gensym-list 'any class-name))
        do
    ;; Only remove the information if the attribute is no longer indexed for
    ;; the class.
    (when (and (memq class-name indexed-attribute-classes?)
               (or (null indexed-attributes-to-keep?)
                   (not (memq indexed-attribute indexed-attributes-to-keep?))))

      ;; Deinstall-true-value-update.
      (setf (second update-designation) indexed-attribute)
      (install-true-value-update
        'handle-update-to-indexed-attribute nil nil update-designation nil)

      ;; Update the list of classes that index the attribute.
      (setq indexed-attribute-classes?
            (delete-gensym-element class-name indexed-attribute-classes?))
      (setf (indexed-attribute-classes indexed-attribute)
            indexed-attribute-classes?)

      ;; Update the list of indexed attributes, if necessary.
      (unless indexed-attribute-classes?
        (setq *indexed-attributes*
              (delete-gensym-element indexed-attribute *indexed-attributes*)))

      (when (and update-hash-table-if-necessary?
                 (indexed-attribute-hash-table indexed-attribute))
        (reclaim-indexed-attribute-hash-table indexed-attribute)
        ;; If the attribute is still indexed by other classes, recreate and
        ;; update the hash-table.  Note that the attribute class information
        ;; must be updated first.  This has been done above, if necessary.
        (when indexed-attribute-classes?
          (make-indexed-attribute-hash-table indexed-attribute)
          (update-indexed-attribute-hash-table indexed-attribute))))

        finally
          (reclaim-gensym-tree update-designation)))



;;; The function `add-indexed-attribute-properties' adds the indexed-attribute
;;; attribute information and hash-table for an attribute.  Note that if an
;;; attribute is already indexed for this class, it is not added.

;;; If the update-hash-table-if-necessary? argument is non-NIL, the
;;; corresponding hash-tables are cleared and updated, when necessary.  If the
;;; updates-apply-to-existing-attributes-also? argument is non-NIL, the
;;; hash-table updates, if being done at all, occur for existing and newly
;;; indexed-attributes.

(defun-void add-indexed-attribute-properties
    (indexed-attributes-to-add class-name update-hash-table-if-necessary?
                               updates-apply-to-existing-attributes-also?)
  (loop for indexed-attribute in indexed-attributes-to-add
        for indexed-attribute-classes? =
          (indexed-attribute-classes indexed-attribute)
        for attribute-added-p? = nil
        with update-designation =
          ;; Reclaimed below.
          (gensym-list 'the nil (gensym-list 'any class-name))
        do
    (when (not (memq class-name indexed-attribute-classes?))
      (setq attribute-added-p? t)
      ;; install-true-value-update
      (setf (second update-designation) indexed-attribute)
      (install-true-value-update
        'handle-update-to-indexed-attribute nil nil nil update-designation)

      ;; Update the list of classes that index the attribute.
      (setq indexed-attribute-classes?
            (gensym-cons class-name indexed-attribute-classes?))
      (setf (indexed-attribute-classes indexed-attribute)
            indexed-attribute-classes?)

      ;; Update the list of indexed attributes, if necessary.
      (unless (memq indexed-attribute *indexed-attributes*)
        (setq *indexed-attributes*
              (gensym-cons indexed-attribute *indexed-attributes*))))

    (when (and (or attribute-added-p?
                   updates-apply-to-existing-attributes-also?)
               (or system-has-paused system-is-running))
      (cond
        (update-hash-table-if-necessary?
         (when (indexed-attribute-hash-table indexed-attribute)
           (reclaim-indexed-attribute-hash-table indexed-attribute))
         ;; Create and update the hash-table.
         (make-indexed-attribute-hash-table indexed-attribute)
         (update-indexed-attribute-hash-table indexed-attribute))
        ((null (indexed-attribute-hash-table indexed-attribute))
         ;; Create the hash-table if it does not exist.
         (make-indexed-attribute-hash-table indexed-attribute))
        (t nil)))
        finally
          (reclaim-gensym-tree update-designation)))



;;; The function `handle-update-to-indexed-attribute' is called whenever the
;;; value of an indexed attribute changes.  If the attribute-name argument is
;;; non-null, it means that a constant, variable, or parameter attribute of the
;;; passed frame has changed.  If the attribute-name argument is nil, the
;;; changed-frame is an attribute variable or parameter.

;;; Note that if the attribute-name argument is provided (non-NIL), then the
;;; defining-class-if-attribute-name-is-provided argument must always be given.

;;; If the attribute is indexed and the current value can be indexed, the parent
;;; object is hashed into the corresponding indexed attribute hash-table.  If
;;; the attribute is indexed and the current value can not be indexed, the old
;;; value is removed from the hash-table.

(defun handle-update-to-indexed-attribute
    (ignored-frame ignored-extra-argument changed-frame attribute-name?
                   old-value defining-class-if-attribute-name-is-provided)
  (declare (ignore ignored-frame ignored-extra-argument))
  (if (null attribute-name?)
      ;; Changed-frame is an attribute variable or parameter.
      (when (has-indexed-attributes-p (parent-frame changed-frame))
        (put-parent-if-indexed-attribute
          (get-pretty-slot-name-for-parent-attribute-if-any changed-frame)
          (get-defining-class-for-parent-attribute-if-any changed-frame)
          changed-frame
          old-value
          (parent-frame changed-frame)))
      ;; Changed-frame is a constant attribute, variable, or parameter.
      (when (has-indexed-attributes-p changed-frame)
        (put-parent-if-indexed-attribute
          attribute-name?
          defining-class-if-attribute-name-is-provided
          (get-slot-value
            changed-frame attribute-name?
            defining-class-if-attribute-name-is-provided)
          old-value
          changed-frame))))



;;; The function `insert-indexed-attribute-items-in-list' is a way of locating
;;; all instances of a class that have the given indexed-attribute and value.
;;; This function is called from a system-procedure and is used by the user to
;;; iterate over the indexed-attribute parent objects.  The system procedure
;;; tests that the list is an item-list and that the class and attribute names
;;; are symbols.  The non-items arguments to this function are evaluation values
;;; and are reclaimed, as necessary, by this function.

;;; This function fills a list with the instances of the class that contain the
;;; indexed-attribute with the given value.  The list is passed as an argument
;;; to this function and the elements are added to the end of this list.  (The
;;; list is not first cleared.) If no indexed items are found, no items are
;;; added to the list and no warning is given.  If the attribute is not indexed
;;; for the class and value, a level 1 error is signaled and no items are added
;;; to the list.

;;; There are several reasons why the indexed-attribute iteration must currently
;;; be implemented with a system-procedure.  During the scheduling of rule
;;; instances, the attribute value expression needs to be evaluated and may
;;; require data service.  Currently, this is not possible, since a wait state
;;; can not occur at this time.  Also, in procedures, there is a problem because
;;; attribute values and the attribute value in the iteration expression may not
;;; always be stable during the iteration.

;; There is one problem not curently solved by the system procedure.  A wait
;; state may be needed when iterating over the items.  An iteration with wait
;; states could be accomplished in a way similar to role-service.  The
;; system-procedure would need to make system-calls to open the server, pass
;; some continuation data and serve a value one at a time, and then close the
;; server.  Maybe, the wait state could be more easily implemented when there is
;; the new version of "system-call" that allows wait-states.

;; Note if this system procedure is modified to contain wait states, then update
;; the call to declare-system-procedure-function to say that it can invalidate
;; the calling procedure's environment!  (Change the second argument to nil.)  -
;; cpm, 8/3/93

(declare-system-procedure-function insert-indexed-attribute-items-in-list t)

;; Consider writing a new system-procedure similar to this one.  Have it accept
;; an additional attribute defining-class argument.  In this way, the caller can
;; then specify a class-qualified attribute name.  Note that as of version 4.0,
;; the user can reference class-qualified attribute names in expressions that
;; can reference indexed attributes.  - cpm, 2/20/94

(defun insert-indexed-attribute-items-in-list
       (indexed-item-list class-name attribute-name attribute-value)
  (let* ((class (evaluation-symbol-symbol class-name))
         (class-description (class-description class))
         (attribute (evaluation-symbol-symbol attribute-name))
         (attribute-value-value (evaluation-value-value attribute-value))
         (indexed-attribute-value?
           (and (indexed-attribute-or-inherited-attribute-for-class-p
                  attribute class)
                (get-and-validate-indexed-attribute-value
                  attribute-value-value)))
         (indexed-attribute-table?
           (indexed-attribute-hash-table attribute)))
    (cond
      ((and indexed-attribute-value? indexed-attribute-table?)
       (let ((parent-and-class-tree?
               (get-indexed-attribute-parent-objects
                 indexed-attribute-value? indexed-attribute-table?))
             (empty-list-p? (g2-list-empty-p indexed-item-list)))
         (when (and parent-and-class-tree? class-description)
           (loop for (item . class-list) being each binary-tree-entry-cons
                 of parent-and-class-tree?
                 do
             (loop for defining-class in class-list
                   do
               (when (frame-of-class-description-p item class-description)
                 (let* ((slot-description?
                          (get-slot-description-of-frame
                            attribute-name item nil))
                        (defining-class-of-attribute?
                            (when slot-description?
                              (defining-class slot-description?))))
                   (when (eq defining-class-of-attribute? defining-class)
                     ;; Add the item to the list and update the record of the
                     ;; lists that an item belongs to, checking for duplicates
                     ;; if the original list wasn't empty.
                     (g2-list-insert-at-end
                       item indexed-item-list empty-list-p?)))))))))
      ((and (eq attribute 'uuid)
            class-description
            (class-description-of-class-p class-description 'unique-identification)
            (text-string-p attribute-value))
       (let ((item-or-item-list (get-item-or-item-list-for-uuid attribute-value))
             (empty-list-p? (g2-list-empty-p indexed-item-list)))
         (cond ((null item-or-item-list)
                nil)
               ((atom item-or-item-list)
                (when (frame-of-class-description-p
                        item-or-item-list
                        class-description)
                  (g2-list-insert-at-end
                    item-or-item-list indexed-item-list empty-list-p?)))
               (t
                (loop for item in item-or-item-list
                      when (frame-of-class-description-p
                             item
                             class-description)
                        do (g2-list-insert-at-end
                             item indexed-item-list empty-list-p?))))))
      (t
       (progn (reclaim-evaluation-value attribute-value)
       (stack-error
         cached-top-of-stack
         "The attribute ~a and value ~NV are not indexed for the class ~
          ~a.  No items will be added to the item-list ~NF."
         attribute attribute-value class indexed-item-list))))
    ;; Reclaim the non-item evaluation-value arguments.
    (reclaim-evaluation-symbol class-name)
    (reclaim-evaluation-symbol attribute-name)
    (reclaim-evaluation-value attribute-value)))


;;; GENSYMCID-787: Improve item lookup speed for lookup by class and id
;;; System defined procedure added for UC16

(declare-system-procedure-function p-get-item-of-class-by-attribute-value t)

(defun-funcallable p-get-item-of-class-by-attribute-value
    (class-name attribute-name attribute-value)
  (unless (g2-enterprise-p)
    (stack-error
      cached-top-of-stack
      "The system procedure p-get-item-of-class-by-attribute-value is only available in G2 Enterprise"))
  (let* ((class (evaluation-symbol-symbol class-name))
         (class-description (class-description class))
         (attribute (evaluation-symbol-symbol attribute-name))
         (attribute-value-value (evaluation-value-value attribute-value))
         (indexed-attribute-value?
           (and (indexed-attribute-or-inherited-attribute-for-class-p
                  attribute class)
                (get-and-validate-indexed-attribute-value
                  attribute-value-value)))
         (indexed-attribute-table?
           (indexed-attribute-hash-table attribute))
         (item-or-not-found 'item-not-found))
    (cond
      ((and indexed-attribute-value? indexed-attribute-table?)
       (let ((parent-and-class-tree?
               (get-indexed-attribute-parent-objects
                 indexed-attribute-value? indexed-attribute-table?)))
         (when (and parent-and-class-tree? class-description)
           (loop for (item . class-list) being each binary-tree-entry-cons
                 of parent-and-class-tree?
                 do
             (loop for defining-class in class-list
                   do
               (when (frame-of-class-description-p item class-description)
                 (let* ((slot-description?
                          (get-slot-description-of-frame
                            attribute-name item nil))
                        (defining-class-of-attribute?
                            (when slot-description?
                              (defining-class slot-description?))))
                   (when (eq defining-class-of-attribute? defining-class)
                     ;; Add the item to the list and update the record of the
                     ;; lists that an item belongs to, checking for duplicates
                     ;; if the original list wasn't empty.
                     (setf item-or-not-found item)
                     (loop-finish)))))
             (unless (eq item-or-not-found 'item-not-found)
               (loop-finish))))))
      ((and (eq attribute 'uuid)
            class-description
            (class-description-of-class-p class-description 'unique-identification)
            (text-string-p attribute-value))
       (let ((item-or-item-list (get-item-or-item-list-for-uuid attribute-value)))
         (cond ((null item-or-item-list)
                nil)
               ((atom item-or-item-list)
                (when (frame-of-class-description-p
                        item-or-item-list
                        class-description)
                  (setf item-or-not-found item-or-item-list)))
               (t
                (loop for item in item-or-item-list
                      when (frame-of-class-description-p
                             item
                             class-description)
                        do (setf item-or-not-found item)
                           (loop-finish))))))
      (t
       (reclaim-evaluation-value attribute-value)
       (stack-error
         cached-top-of-stack
         "The attribute ~a and value ~NV are not indexed for the class ~
          ~a.  No items will be found."
         attribute attribute-value class)))
    ;; Reclaim the non-item evaluation-value arguments.
    (reclaim-evaluation-symbol class-name)
    (reclaim-evaluation-symbol attribute-name)
    (reclaim-evaluation-value attribute-value)
    item-or-not-found))

;;; Debugging Code For Indexed-Attributes

#+development
(defun find-reclaimed-frame-in-indexed-attribute-table (attribute attribute-value)
  (let* ((indexed-attribute-value?
           (get-and-validate-indexed-attribute-value
                  attribute-value))
         (indexed-attribute-table?
           (indexed-attribute-hash-table attribute)))
    (when (and indexed-attribute-value? indexed-attribute-table?)
      (let ((parent-and-class-tree?
              (get-indexed-attribute-parent-objects
                indexed-attribute-value? indexed-attribute-table?)))
        (when parent-and-class-tree?
          (loop with bad-item? = nil
                for (item . class-list) being each binary-tree-entry-cons
                of parent-and-class-tree?
                do
            (when (frame-serial-number-equal (frame-serial-number item) (frame-serial-number-recycled))
              (setq bad-item? item)
              (return bad-item?))
                finally
                  (return nil)))))))

#+development
(defun collect-entries-for-indexed-attribute-hash-table (hash-table)
  (loop with ht-length = (length hash-table)
        with result? = nil
        with node-result? = nil
        with tree? = nil
        for i = 1 then (incff i)
        until (>=f i ht-length)
        do
    (setq tree? (aref hash-table i))
    (when tree?
      (setq node-result? (collect-entries-for-indexed-attribute-tree tree?))
      (when node-result?
        (if result?
            (nconc result? node-result?)
            (setq result? node-result?))))
        finally (return result?)))

#+development
(defun collect-entries-for-indexed-attribute-tree (tree)
  (unless (null (cdr tree))                ; no elements
    (collect-indexed-attribute-elements (cdr tree))))

#+development
(defun collect-indexed-attribute-elements (element?)
  (when element?
    (nconc
      (collect-indexed-attribute-elements (less-than-branch element?))
;      (format t "~%Elements at hash ~a" (binary-element-hash-number element?))
      (loop with result? = nil
              for entry in (binary-element-alist element?)
              for tree-list? = (and (cdr entry) (cddr entry)
                                   (aref (cddr entry) 3))
;        (format t "~%  ~S => ~S" (car entry) (cdr entry))
              do
          (when (and tree-list? (car tree-list?) (caar tree-list?))
            (pushnew (caar tree-list?) result?))
              finally (return result?))
      (collect-indexed-attribute-elements (greater-than-branch element?)))))

;;

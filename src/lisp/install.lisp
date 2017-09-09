;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module INSTALL

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andreas Hofmann, Michael Levin, and Jim Allard



(declare-forward-reference delete-dynamic-rule-displays-for-rule-or-object
			   function)		       ; queries
(declare-forward-reference suppress-consistency-analysis-warnings-notes?
			   variable)	               ; queries

(declare-forward-reference install-externally-simulated-variable function)


(declare-forward-reference add-to-variables-to-be-rederived function)
(declare-forward-reference note-runtime-structure-in-things-that-affect-it function)



(declare-forward-reference add-variable-to-simulation function)
(declare-forward-reference remove-variable-from-simulation function)

(declare-forward-reference install-item-in-model-if-models-used function)

;; To CONTROLS
(declare-forward-reference embedded-rule-p function)
(declare-forward-reference add-as-inferior-block function)
(declare-forward-reference associated-variable-designation-function? function)
(declare-forward-reference button-frame-status function)

(declare-forward-reference any-models-running-function? function) ;SIMULATE1

;; to GRAMMAR5
(declare-forward-reference is-generic-forumula-executable? function)

;; To GRAMMAR6
(declare-forward-reference write-list-in-chicago-style-given-format function)

(declare-forward-reference write-list-in-chicago-style function)

;; To FILTERS
(declare-forward-reference g2-xor function)
(declare-forward-reference map-over-external-names-in-object-configuration function)

;;  to STACK_COMP
(declare-forward-reference datum-type-specifications-could-be-coerced-p  function)

(declare-forward-reference type-specifications-could-be-coerced-p  function)

;; to EVENTS-G2
(declare-forward-reference send-ws-representations-connection-moved function)

(declare-forward-reference representation-address-valid-p function)
(declare-forward-reference block-can-be-inlined-p function)
(declare-forward-reference send-ws-representations-item-virtual-attribute-change function)
(declare-forward-reference block-can-be-dependent-p function)




;;; New rules for installation - 6/22/87
;;; (see also Lowell's documentation in KB-FRAMES)

;;; 1.  Slot putters must return value installed.

;;; 2.  Normally, slot putters don't do any reclaiming of the old slot value;
;;; this is usually the responsibility of the caller of the slot putter.  If the
;;; slot putter does reclaim the old value, t should be returned as the second
;;; value of the slot putter to inhibit reclamation by the caller.

;;; 3.  If the installed value is modified by the slot putter from the given new
;;; value, any things dropped should be reclaimed by the slot putter.

;;; 4.  Put-slot-value is no longer a generally available capability.  Don't use
;;; it inside slot-putters.  If the need for this arises, talk to Lowell.

;;; Notes by ML on 10 June 87:

;;; Side effects of slot values are accomplished by slot-putters.  Generally, a
;;; slot-putter should deal with removing the side effects of the old value
;;; unless it is called while making a frame.

;;; When a frame is either edited, created or reconstructed, change-slot-value
;;; is called.  Since there are no longer update methods, this will put the slot
;;; value and update its representations.  A slot putter will be called to put
;;; the value if one exists.

;;; Side effects must also be removed by slot-value-reclaimers.  This is the way
;;; the side effects go away when deleting frames.

;;; Slot-putters should change the frame status as appropriate.  The status is
;;; changed by calling update-frame-status.  If this changes the status so as to
;;; make it ok when previously it was not ok, then if the activate bit is on,
;;; the frame is activated with a second argument of nil.

;;; If a slot-putter is going to make a frame not ok, when it was previously ok,
;;; then if the frame is active, it should be deactivated with a second argument
;;; of nil, and then be marked should-be-active.

;;; The frame status of a frame must nevertheless be maintained.  If a type of
;;; frame is not usable with default values (i.e.  exactly as created) then it
;;; should be given the initial frame-status-and-notes 'incomplete.  The frame
;;; status must be updated by any slot putter that causes the frame to become
;;; usable.

;;; At present (16 June 87) RULE is such a frame.  It becomes usable when it is
;;; given a valid rule text.  But there is no way to take it out of use, since
;;; the editor will not allow the replacement of the valid text by one that is
;;; not valid.  Suppose you want the rule to be taken out of use.  There is no
;;; way to do this.  Furthermore, neither BAD or INCOMPLETE correctly describe
;;; this situation.




;; To do

;; Review set up of backward and forward chaining lists
;; Test "undefined notes"
;; Review how "undefined" notes are removed



;;; Install contains installation methods for rules, variables, and other
;;; entities.  Included is a mechanism for efficiently updating runtime data
;;; structures when an edit is made (see Edit while Running section).  Install
;;; also contains slot-putters, slot-writers ...  It also contains an interface
;;; function to the rule compiler.  It also contains some user interface type
;;; functions currently used in knowledge bases to put various kinds of blocks
;;; onto schematics.  These functions will probably be moved to a different
;;; file eventually.



;;;; Frame Notes

;;; def-frame-note-writer ...  (see "kb-frames")




;;;; Rule Installation;  Introduction

;;; Rule installation involves checking for undefined names, and setting up
;;; forward and backward chaining lists as kb-symbol properties of names.  Rule
;;; compilation is invoked from the translator and is a separate issue (see
;;; below).  The checking for undefined names and setting up of chaining lists
;;; can be accomplished by slot putters so there is currently nothing that the
;;; installation themselves have to do.







;;;; Slot Putter Definitions


;;; `get-new-translation-of-text-slots' actually get car of the translation
;;; which is suitable for rules and possible simulation statements. It does not
;;; work for formulas!!!

(defun get-new-translation-of-text-slot (translation-and-text)
  (if (consp translation-and-text)
      (let ((new-translation (car translation-and-text)))
	(if (and new-translation (neq new-translation no-value))
	    (car new-translation)))))




(def-class-method put-box-translation-and-text-slot-value
		  (rule box-translation-and-text initializing?)
  ;; When loading a KB saved before 3.0, clear its compile and parse and note
  ;; that it is pre-3.0.  Note that further down in the slot putter, the frame
  ;; status will be changed to incomplete.  -jra 6/5/91
  (when (and initializing?
	     (not (compilations-up-to-date-p rule))
	     loading-kb-p)
    (delete-frame-note-if-any 'old-rule rule)
    (reclaim-slot-value (car box-translation-and-text))
    (setf (car box-translation-and-text) no-value)
    (note-frame-with-compilation-removed rule))

  ;; When loading a kb older than 6 Aug 88, set the invocable flags in a
  ;; default way.  Note: The conjunction of initializing?  and loading-kb-p is
  ;; caused by lack of definitional clarity.  We want this code to execute only
  ;; when a rule is coming in from a stored kb!
  (when (and loading-kb-p initializing?
	     (not (invocable-rule-flags-ok-p)))
    (set-invocable-via-forward-chaining rule)
    (set-invocable-via-backward-chaining rule))

  (let ((new-translation?
	  (get-new-translation-of-text-slot box-translation-and-text))
	(was-runnable? (runnable-p rule)))

    ;; If the rule was runnable, deactivate it now to get rid of existing
    ;; rule-instances before we pull the rug out from under them.
    (when was-runnable?
      (funcall-method 'deactivate-and-propagate rule nil))

    ;; If the rule is becoming an initial rule or a whenever rule, we want to
    ;; get rid of the rule scan interval.  The new scan is set such that the
    ;; slot putter does not get called, since the slot putter looks at the box
    ;; translation and text, which we haven't put yet.
    (when (and (not initializing?)
	       (or (initial-rule-p rule)
		   (eq (rule-keyword rule) 'whenever))
	       (rule-scan-interval rule))
      (set-slot-value-and-update-representations
	rule 'rule-scan-interval nil))

    ;; Put the new box-translation-and-text into the rule.
    (setf (box-translation-and-text rule)
	  box-translation-and-text)

    ;; If the rule isn't already bad, update its frame status based on whether a
    ;; translation was given to us by the slot value compiler.
    (cond ((eq (frame-status rule) 'bad)
	   nil)
	  (new-translation?
	   (update-frame-status rule nil t)
	   #+development
	   (when (and (null (rule-byte-code-body rule))
		      (not initializing?))
	     (cerror "Continue" "Rule ok, but no byte-code-body!"))
	   (when was-runnable?
	     (funcall-method 'activate-if-possible-and-propagate rule))
	   (unless initializing?
	     (update-representations-of-slot-value
	       rule 'frame-status-and-notes)))
	  (t
	   (update-frame-status rule 'incomplete initializing?)
	   (change-slot-value rule 'rule-byte-code-body nil)))

    (values box-translation-and-text nil)))




;;; The slot-putter for focal-classes uses eval-conses for now because of the
;;; convenience of add-to-set and delete-from-set.  These could be generalized.
;;; It maintains the kb-specific property rules-of-this-class-or-object-name.

;;; The slot putter for focal-objects works in the same way.

;;; When editing (as opposed to kb-loading) there is the possibility of
;;; mistakenly putting an on object name in the class slot or visa versa.  Then,
;;; if the mistake is rectified by first putting the name where it belongs and
;;; then deleting it from where it does not belong, one would delete its unique
;;; reference on rules-of-this-class-or-object-name if the last line of code did
;;; not put it back.  Efficiency is not an issue here.

;;; To delete these effects, set the slot to nil.

;;; Note that this putter is invoked during compilation of the action forms for
;;; user menu choices.  In this case, a compilation of the rule should not be
;;; forced, since it will happen within the slot value compiler for the action
;;; anyway.

(def-kb-specific-property-name rules-of-this-category)
(def-kb-specific-property-name rules-of-this-class-or-object-name)

(def-slot-putter focal-classes (rule value initializing?)
  (let ((old-value (if initializing? nil (focal-classes rule))))
    (loop for name in old-value
	  do
      (delete-from-directory-of-names name 'focal-class)
      (delete-from-set (rules-of-this-class-or-object-name name) rule))
    
    (loop for name in value
	  do
      (add-to-directory-of-names name 'focal-class)
      (add-to-set (rules-of-this-class-or-object-name name) rule))
    
    (unless initializing?
      (loop for name in (focal-objects rule)
	    do
	(add-to-set (rules-of-this-class-or-object-name name) rule)))
    
    (setf (focal-classes rule) value)

    (unless (or initializing? (embedded-rule-p rule))
      ;; When editting the focal classes, the rule body must be recompiled to
      ;; generate new compiled prefixes.
      (recompile-item rule))

    value))

(def-slot-value-reclaimer focal-classes (value frame)
  (loop for name in value
	do
    (delete-from-directory-of-names name 'focal-class)
    (delete-from-set (rules-of-this-class-or-object-name name) frame))
  (reclaim-slot-value-list value)
  (setf (focal-classes frame) nil))

(def-slot-putter focal-objects (rule value making-frame?)
  (let ((old-value (if making-frame? nil (focal-objects rule))))
    (loop for name in old-value
	  do
      (delete-from-directory-of-names name 'focal-object-name)
      (delete-from-set (rules-of-this-class-or-object-name name) rule))

    (loop for name in value
	  do
      (add-to-directory-of-names name 'focal-object-name)
      (add-to-set (rules-of-this-class-or-object-name name) rule))

    (unless making-frame?
      (loop for name in (focal-classes rule)
	    do
	(add-to-set (rules-of-this-class-or-object-name name) rule)))

    (setf (focal-objects rule) value)

    value))

(def-slot-value-reclaimer focal-objects (value frame)
  (loop for name in value
	do
    (delete-from-directory-of-names name 'focal-object-name)
    (delete-from-set (rules-of-this-class-or-object-name name) frame))
  (reclaim-slot-value-list value)
  (setf (focal-objects frame) nil))

(def-slot-putter rule-categories (rule value making-frame?)
  (let ((old-value (if making-frame? nil (rule-categories rule))))
    (loop for name in old-value
	  do
      (delete-from-directory-of-names name 'rule-category-name)
      (delete-from-set (rules-of-this-category name) rule))
    
    (loop for name in value
	  do
      (add-to-directory-of-names name 'rule-category-name)
      (add-to-set (rules-of-this-category name) rule))
    
    (setf (rule-categories rule) value)

    value))

(def-slot-value-reclaimer rule-categories (value frame)
  (loop for name in value
	do
    (delete-from-directory-of-names name 'rule-category-name)
    (delete-from-set (rules-of-this-category name) frame))
  (reclaim-slot-value-list value)
  (setf (rule-categories frame) nil))






;;;; Simulation Parameters




;;; *simulation-time* advances each cycle by shortest-simulation-time-increment,
;;; which is not necessarily the same as default-simulation-time-increment.
;;; Shortest-simulation-time-increment will initially be the same as 
;;; default simulation-time-increment but can change if a shorter time increment
;;; is specified for some variable.  This allows for simulation of variables 
;;; described by differential equations which have to be integrated at a smaller
;;; time step than the rest of the system.  Note that not all variables are 
;;; updated at each time step, only the ones specified.  Thus, the efficiency
;;; of the simulator is improved when averaged over a long simulation time.

;;; Suffering an acute attack of moral fiber, I changed the default value of
;;; simulator-on? to nil. -ncc, 8 Aug 1997

(def-system-frame simulation-parameters simulate1
  (default-simulation-time-increment 
    0.5 system (type simulation-time-increment) vector-slot)
  (integration-algorithm euler system (type integration-algorithm-specification) 
			 vector-slot)
  (simulator-on? nil system (type yes-or-no) vector-slot) ;; was yes-or-no?. See Tables
  (run-in-real-time? nil system vector-slot)   ; (type yes-or-no)  - editing disabled - agh 1/12/88
  (external-simulator-configuration 
    nil system (type xsi-host-configuration text) vector-slot)
  (simulation-procedure nil system (type procedure-name?) vector-slot)
  (send-all-values-at-beginning-of-cycle? nil system (type yes-or-no) vector-slot)
  (vector-from-external-simulator nil system vector-slot)
  (vector-to-external-simulator nil system vector-slot)
  )

;; External-simulator-configuration will eventually be a slot in a model!

;; The variables-to-simulate slot has been removed from simulation parameters.
;; The kb-specific variable variables-to-simulate is used instead.  This is
;; because system frames should only contain parameters.  Putting frames into
;; slots of system frames causes problems when loading or merging since the
;; system frames are not kb-specific.  Note that there is no need to define
;; an absent slot putter since this slot was not saved.  For the same reason,
;; there is no absent slot putter for shortest-simulation-time-increment or
;; for epsilon-for-constraint-checking.
;; Consider moving this system frame definition back to simulate;  it should
;; no longer be necessary to keep it here.  

(define-slot-alias simulator-on simulator-on?)


(def-absent-slot-putter handle-ordering-loops?
			(frame value)
  (declare (ignore frame value)))

;;; The `initialize method on simulation-parameters' is used to turn off
;;; the simulator when this user has a G1 license.  This, in turn, prevents
;;; him from getting warnings when he loads the KB that his license is
;;; insufficent to fulfill this wish.

(def-class-method initialize (simulation-parameters)
  (funcall-superior-method simulation-parameters)
  (when (and (simulator-on? simulation-parameters)
	     (g1-authorized-p))
    (setf (simulator-on? simulation-parameters) nil)))

;; As usual this can't tell if it's called out of clone, but in this
;; case it probably doesn't happen.


(defun expression-cell-element-for-generic-formula (generic-formula)
  (declare (ignore generic-formula))
  0)

(def-class-method put-box-translation-and-text-slot-value
    (generic-formula box-translation-and-text initializing?)
  
  ;; In the style of the put-NEW-box-translation-and-text-slot-value method
  ;; for rule:  (MHD 7/1/91)
  (let ((recompiling? (and initializing?
			   (not (compilations-up-to-date-p generic-formula))
			   loading-kb-p)))
    (when recompiling?
      (reclaim-slot-value (car box-translation-and-text))
      (setf (car box-translation-and-text) no-value)
      (note-frame-with-compilation-removed generic-formula))
    
    (let* ((old-box-translation-and-text
	     (box-translation-and-text generic-formula))
	   (old-translation?
	     (unless (or initializing?
			 (null old-box-translation-and-text)
			 (eq (car old-box-translation-and-text) no-value))
	       (car old-box-translation-and-text)))
	   (new-translation
	     (if (and (consp box-translation-and-text)
		      (neq (car box-translation-and-text) no-value))
		 (car box-translation-and-text)))
	   (new-role-name
	     (if new-translation (first new-translation)))
	   (old-role-name 
	     (if old-translation? (first old-translation?)))
	   (old-class-qualifier
	     (if old-translation? (third old-translation?)))
	   (new-class-qualifier
	     (if new-translation (third new-translation))))
      (when old-role-name
	(delete-from-set (formulas-for-this-role old-role-name) generic-formula)
	(reconcile-formulas-for-role-and-class
	  old-role-name (second old-translation?) old-class-qualifier))
      (update-frame-status
	generic-formula
	(cond (new-translation nil)
	      ((and old-translation? (not recompiling?)) 'bad)
	      (t 'incomplete))
	initializing?)

      (if initializing?
	  (setf (box-translation-and-text generic-formula) box-translation-and-text)
	  (without-consistency-analysis (generic-formula)
	    (setf (box-translation-and-text generic-formula) box-translation-and-text)))
      
      (when new-role-name
	(add-to-set (formulas-for-this-role new-role-name) generic-formula)
	(reconcile-formulas-for-role-and-class
	  new-role-name (second new-translation) new-class-qualifier))
      (when (and (null (is-generic-forumula-executable? generic-formula))
		 (not recompiling?))
	(update-frame-status generic-formula 'bad nil))
      (values box-translation-and-text nil))))




(def-frame-note-writer multiple-generic-formulas (role generic-formula)
  (let* ((class (formula-class generic-formula)))
    (tformat
      "this is not the only generic formula for the ~(~A~) of a ~(~A~)"
      role class)))


;;; added class-qualifier -rdf, 3/10/94

(defun reconcile-formulas-for-role-and-class (role class class-qualifier)
  (loop with formulas =  (formulas-for-this-role role)
	with first-found? = nil
	with multiple? = nil
	for formula in formulas doing
    (cond
      ((null first-found?)
       (when (and (eq (formula-class formula) class)
		  (frame-not-bad-p formula))
	 (setq first-found? t)))
      (t
       (when (and (eq (formula-class formula) class)
		  (frame-not-bad-p formula)
		  (or (null class-qualifier)
		      (eq (formula-role-class-qualifier formula)
			  class-qualifier)
		      (eq class class-qualifier))
		  
		  )
	 (setq multiple? t))))
	finally
	  (loop for formula in formulas doing
	    (when (eq (formula-class formula) class)
	      (if multiple?
		  (add-frame-note 'multiple-generic-formulas formula role t nil)
		  (delete-frame-note-if-any 'multiple-generic-formulas formula))))))





;;;; Putting and Reclaiming Attribute Values



;;; `Put-attribute-value' is the slot putter for all user defined attribute
;;; values.

;;; If the new-attribute-value is a variable, put-attribute-value will,
;;; if there is no simulation frame for the variable and if there exist generic
;;; simulation formulas for the variable, put the variable on the list of
;;; variables to be simulated.  It will also set simulation category ,initial
;;; value, and time increment slots of the variable.

;;; Note that prior to today, when a frame was removed from a slot value, it's
;;; parent information was reset before it was deleted, and it was not
;;; deactivated prior to deletion.  This seemed racy to us to say the least, and
;;; so today we have changed this code to explicitly deactivate the frame before
;;; deleting it.  Also, when a new frame was installed, the parent information
;;; was being set on the subframe, but then the subframe was activated before
;;; the pointer from the parent to the subframe was changed.  This also seems a
;;; bit bizarre, and so all pointers between the two frames are going to be
;;; installed before the subframe is activated.  -jra & ml 7/11/91

;;; The flag generic-simulation-formulas-used-p is used to optimize installation
;;; for kbs where there are no generic simulation formulas.  It is similar in
;;; purpose to models-used-p.

;;; `Put-attribute-description-value' is similar, but takes a slot description
;;; rather than a slot name and a defining class, is a simple function, and just
;;; returns a single value, the value put in the attribute.  Note that
;;; put-attribute-description-value is an internal subfunction of
;;; put-attribute-value and
;;; change-slot-description-value-without-updating-representations, and should
;;; only be used by them.

(def-kb-specific-variable generic-simulation-formulas-used-p SIMULATE5 nil t)

(defmacro skip-generic-simulation-formula-installation? ()
  `(or loading-kb-p (not generic-simulation-formulas-used-p)))

(defun put-attribute-value 
       (frame unique-or-pretty-slot-name new-attribute-value initializing?
	      &optional class-if-specific?)
  (values
    (put-attribute-description-value
      frame
      (get-slot-description-of-frame
	unique-or-pretty-slot-name frame class-if-specific?)
      new-attribute-value initializing?)
    t))


(defun-simple put-attribute-description-value
    (frame slot-description new-attribute-value retaining-old-frame-or-initializing?)
  (let* ((old-attribute-value
	   (get-slot-description-value frame slot-description))
	 (new-value-is-frame-p (framep new-attribute-value))
	 (*current-computation-frame*
	   (if (framep *current-computation-frame*)
	       *current-computation-frame*
	       frame)))
    
    (unless (or do-not-note-permanent-changes-p
		(slot-value-equal-p old-attribute-value new-attribute-value))
      (note-permanent-change frame slot-description))
    
    (unless retaining-old-frame-or-initializing?
      (when (framep old-attribute-value)
	(when (frame-of-class-p old-attribute-value 'variable-or-parameter)
	  (remove-variable-from-simulation old-attribute-value))
	(when (active-p old-attribute-value)
	  (funcall-method
	    'deactivate-and-propagate old-attribute-value nil))
	(set-parent-information old-attribute-value nil nil nil)
	(delete-frame old-attribute-value)
	(setq old-attribute-value nil)))

    (set-slot-description-value frame slot-description new-attribute-value)
    
    (when new-value-is-frame-p
      (add-as-inferior-block new-attribute-value frame)
      (set-parent-information
	new-attribute-value
	frame
	(pretty-slot-name slot-description)
	(if (slot-name-needs-qualification-p
	      slot-description (class-description-slot frame))
	    (defining-class slot-description)))
      (cond
	((active-p frame)
	 (funcall-method 'activate-if-possible-and-propagate new-attribute-value))
	((or (manually-disabled-p frame)
	     (ancestor-not-activatable-p frame)
	     (frame-status frame))
	 (funcall-method 'deactivate-and-propagate new-attribute-value t))))
    
    (unless (or (skip-generic-simulation-formula-installation?)
		class-is-undergoing-inheritance-change?)
      (cond
	((and new-value-is-frame-p
	      (frame-of-class-p new-attribute-value 'variable-or-parameter))
	 (update-generic-simulation-formula-for-variable-or-parameter
	   new-attribute-value))
	((and new-value-is-frame-p
	      (frame-of-class-p new-attribute-value 'object))
	 (update-runtime-structures-according-to-edit new-attribute-value)))

      (update-runtime-structures-according-to-edit frame))
    
    (unless retaining-old-frame-or-initializing?
      (when (and new-value-is-frame-p
		 (frame-of-class-p new-attribute-value 'variable-or-parameter))
	(install-externally-simulated-variable new-attribute-value)))

    ;; This call should be checked:  probably a unique slot name is
    ;; needed.
    
    ;; Change interface to pass slot description?!
    (invoke-rules-for-attribute-change-chaining
      frame
      (pretty-slot-name slot-description)
      old-attribute-value
      (defining-class slot-description))

    (when (and (not retaining-old-frame-or-initializing?) old-attribute-value)
      (unless (eq old-attribute-value (slot-init-form slot-description))
         (reclaim-slot-value old-attribute-value)))
    
    new-attribute-value))

;; Install-externally-simulated-variable is only called when not
;; initializing (when some attribute slot is being edited).  The initializing
;; case is handled by the frame-initialize method for entity.

;; Note that there is no need to do anything for installation for external
;; simulation if the old-attribute-value is a variable.  Deleting a variable
;; does not affect the installation of objects for the external simulator.



;;; Update-simulator-information-for-attribute-name-change is called when an 
;;; attribute name is changed in a definition (see DEFINITIONS).  It 
;;; duplicates some of the functionality of put-attribute-value.

(defun update-simulator-information-for-attribute-name-change
       (parent-entity variable-in-slot old-attribute-name new-attribute-name)
  (declare (ignore old-attribute-name new-attribute-name parent-entity))
  (unless (skip-generic-simulation-formula-installation?)
    (update-generic-simulation-formula-for-variable-or-parameter
      variable-in-slot)))





;;;; Editing while Running

;;; In order to maintain efficient runtime structures, a mechanism is needed to
;;; handle edits made while running.  The function
;;; update-runtime-structures-according-to-edit is called by various slot putters
;;; and editing functions to take care of updating runtime structures effected by
;;; edits.  Update-runtime-structures-according-to-edit uses the
;;; runtime-structures-affected-by-this-...  slots in argument entities,
;;; statements, and connections.  Note that these slots are reset to nil after
;;; they have been processed and the conses reclaimed.  Note also that the
;;; elements in the edit caches are filtered via frame-has-been-reprocessed-p to
;;; ensure that no action is taken for deleted frames.

;;; Edits to entities, including instantiation and deletion, are completely
;;; handled by put-attribute-value and the slot value reclaimer for 
;;; runtime-structures-affected-by-this-entity which simply
;;; call update-runtime-structures-according-to-edit with the entity.

;;; For connections, the simulation can change when the connections slot of an
;;; entity is modified; if a connection is added or deleted from this slot.  The
;;; low level functions that do this are: replace-connection-in-block,
;;; add-connection-in-block, and delete-connection-in-block.  These functions
;;; are called by higher level connection functions such as join-two-connections
;;; which in turn are called by general editing functions such as
;;; mouse-down-in-dragging-context.  There is no need, however, to be concerned
;;; with these; edits to connections are almost completely handled by the lower
;;; level functions that modify the connections slot.  These simply call
;;; update-runtime-structures-according-to-edit with their argument connections.
;;; There are a number of other functions that set the connections slots of
;;; loose ends but this doesn't effect simulation.  See design book notes for
;;; 5/10/88 for a more thorough discussion of these issues.  Note that
;;; insert-junction-block also calls
;;; update-runtime-structures-according-to-edit.  Note that connection-frames
;;; are entities so their edits are handled as for other entities (described above). 

;;; Edits to generic-simulation-formulas, including instantiation and deletion,
;;; are completely handled by the slot putter for the box-translation-and-text
;;; slot (which calls the method put-box-translation-and-text-slot-value).
;;; This method simply calls update-runtime-structures-according-to-edit
;;; with the generic-simulation-formula.  Note that the slot putter is also
;;; invoked when the frame is deleted (by the cleanup method which sets the
;;; box-translation-and-text slot to nil).  Therefore, there is no need for an
;;; explicit slot value reclaimer (as in the case with entities) that calls 
;;; update-runtime-structures-according-to-edit when the generic-simulation-formula
;;; is deleted.
;;; Note that edits to specific simulation formulas are handled by the slot 
;;; putter which removes and adds the variable to the simulation.  Edits
;;; to user defined attributes of variables are handled by put-attribute the 
;;; same way that edits to attributes of any entity are handled (see above
;;; description).

;; It may be completely redundant to note generic-simulation-formulas since
;; the slot putter for these already removes and adds variables to the simulation
;; as appropriate.  Still, there is never any harm in redundantly noting
;; variables that may have to be re-derived.

;;; Note that there are only a very few functions that have to call
;;; update-runtime-structures-according-to-edit.  This great simplicity is 
;;; achieved through good abstraction in the installation and connection editing
;;; functions, and by the fact that it is not necessary to get too detailed about 
;;; what kind of edit was made;  only the fact that something was edited has to
;;; be noted.  This may cause some unnecessary updating of runtime structures
;;; but this is always ok to do and takes a negligible amount of time considering
;;; that the system is responding to an edit.

;;; Any-models-running?  is used to decide if edit changes should result in
;;; effected runtime structures being re-derived for the simulator.  It is an
;;; optimization which assures that this is only done if there are any models
;;; being simulated.



(def-structure (edit-cache (:reclaimer reclaim-edit-cache-internal))
  (edit-cache-frame-serial-number nil :reclaimer reclaim-frame-serial-number)
  (variables-to-rederive nil)
  (variables-to-reinstall nil))

(defun reclaim-edit-cache (edit-cache)
  (reclaim-eval-list (variables-to-rederive edit-cache))
  (reclaim-eval-list (variables-to-reinstall edit-cache))
  (reclaim-edit-cache-internal edit-cache))

(defun update-runtime-structures-according-to-edit 
       (thing-that-was-edited &optional do-not-reinstall?)
  (unless (skip-generic-simulation-formula-installation?)
    (let ((edit-cache
	    (cond
	      ((framep thing-that-was-edited)
	       (cond
		 ((frame-of-class-p thing-that-was-edited 'entity)
		  (prog1
		    (runtime-structures-affected-by-this-entity 
		      thing-that-was-edited)
		    (setf (runtime-structures-affected-by-this-entity 
			    thing-that-was-edited) nil)))
		 ((frame-of-class-p thing-that-was-edited 'statement)
		  (prog1
		    (runtime-structures-affected-by-this-statement 
		      thing-that-was-edited)
		    (setf (runtime-structures-affected-by-this-statement 
			    thing-that-was-edited) nil)))
		 ((frame-of-class-p thing-that-was-edited 'connection)
		  (let ((connection
			  (connection-for-this-connection-frame
			    thing-that-was-edited)))
		    (prog1
			(runtime-structures-affected-by-this-connection 
			  connection)
		      (setf (runtime-structures-affected-by-this-connection 
			      connection) nil))))))
	      ((connection-p thing-that-was-edited)
	       (prog1
		 (runtime-structures-affected-by-this-connection 
		   thing-that-was-edited)
		 (setf (runtime-structures-affected-by-this-connection 
			 thing-that-was-edited) nil))))))
      (when edit-cache
	(let ((frame-serial-number-for-cache 
		(edit-cache-frame-serial-number edit-cache)))
	  (unless do-not-reinstall?
	    (when (any-models-running-function?)
	      (loop for runtime-structure in (variables-to-rederive edit-cache)
		    do
		(when (and (framep runtime-structure)
			   (frame-of-class-p runtime-structure 'variable-or-parameter)
			   (not (frame-has-been-reprocessed-p
				  runtime-structure frame-serial-number-for-cache))
			   (simulation-runtime-information? runtime-structure))
		  ;; Runtime formula in variable-simulation-runtime-structure for variable
		  ;; must be re-derived.  
		  ;; Have to check if this variable has been deleted
		  ;; (see also note-runtime-structure-in-things-that-affect-it in
		  ;; SIMULATE).
		  ;; Checking if simulation-runtime-information? is non-nil is 
		  ;; more efficient than, but equivalent to checking if the variable
		  ;; is in variables-to-simulate because of the convention that
		  ;; a variable only have a variable-simulation-runtime-structure if
		  ;; it is being simulated (see notes before initialize-simulator).
		  
		  (add-to-variables-to-be-rederived runtime-structure))))

	    (loop for runtime-structure in (variables-to-reinstall edit-cache)
		  do
	      (when (and (framep runtime-structure)
			 (frame-of-class-p runtime-structure 'variable-or-parameter)
			 (not (frame-has-been-reprocessed-p
				runtime-structure frame-serial-number-for-cache)))
		(update-generic-simulation-formula-for-variable-or-parameter
		  runtime-structure)))))
	(reclaim-edit-cache edit-cache)))))

;; Note that this clears the effected runtime structures cache slots in 
;; thing-that-was-edited.  When the runtime structure is re-derived, these cache slots
;; will be filled as appropriate.

;; See also design book notes for 6/13/88.






;;;; Validation of KB's Modified at Runtime




;;; In version 4.0, the user can now modify additional definition attributes at
;;; runtime, manually or from actions.  These attributes include class-name,
;;; direct-superior-classes, class-specific-attributes, and several additional
;;; features of the change attribute.  Runtime changes to these attributes can
;;; affect other parts of the KB, that therefore need to be validated.

;;; Depending on the type of definition change, there are several parts of the
;;; KB that need to be validated.  These include executing statements, some
;;; data-structures internal to G2, and some user data-structures.

;;; The validation involves checking for several changes to items, which include
;;; item deletion and items now being of another class.  In many cases, if the
;;; item is no longer valid for the statement, the reference is replaced with
;;; NIL, "no value", and will cause an error if referenced.  In some cases, such
;;; as for some rule-instances, the statement may be dismissed, if the item is
;;; no longer valid.

;;; Note that changes to user-defined attributes in definitions are not
;;; validated here, because this is handled in the appropriate slot-putters.

;;; Also, note that existing values based on attributes, such as local-variable
;;; values, and g2-array values, are not validated.  These values are considered
;;; correct and future references to modified attributes will be based on any
;;; changes to the definition.




;;; The function `validate-kb-after-runtime-definition-change' validates parts
;;; of the KB that may have been affected by a runtime change to a KB definition
;;; (object, connection, or message).  See further comment above, in this
;;; section.

;;; The class argument names the definition that was changed.  The second
;;; argument, if non-NIL, is the name of the class before the recent definition
;;; (i.e., class name) change.  If the class hiearchy of the named class may
;;; have changed, then the third argument should be non-NIL.  For example, if
;;; the class name or a superior class has changed, this would require extra
;;; validation.

(defun validate-kb-after-runtime-definition-change
    (class old-class? change-may-have-affected-class-hierarchy-of-class?)
  (validate-executing-statements-and-procedures)
  (validate-internal-data-structures-containing-items)
  (unless currently-automatically-resolving-class-name-conflicts?
    (when change-may-have-affected-class-hierarchy-of-class?
      (validate-user-data-structures-containing-items class old-class?))))

;; This function used to only revalidate when the system was running or paused.
;; With the addition of the running while inactive and permanent list and array
;; work, it must now always validate.  -jra 11/15/96

;; Note that executing statements and internal-data-structures validation are
;; both called even if there are currently no instances of the old or new class.
;; This is necessary because instances of these classes may have been deleted as
;; a result of the definition change.  Executing statements and
;; "internal-data-structures" are not automatically updated when an item is
;; deleted, though the user-data-structures (i.e., g2-lists, g2-arrays, and
;; relations) are.

;; Note that when the attributes of a class have been changed, the validation
;; function can be called with the definition name as the class argument.  This
;; can be done instead of calling the validation once for the class of each
;; attribute object for any old and new attribute init form.  (This saves alot
;; of extra validation.)  The first case (i.e., calling the validation once
;; using the definition name) should be done only when the definition change may
;; have caused only attribute objects to be deleted, and not when the class
;; hierarchy of existing attribute objects have changed.  This works for all
;; definition attribute modifications because the class hierarchy of attribute
;; objects do not change when attribute slot init form specify a new attribute
;; object class.  When necessary, any existing attribute objects are first
;; deleted and then created using the new class name.  The attribute change is
;; not done by changing the class of the old attribute object.  (I hope this is
;; clear!)  - cpm, 7/22/94



;;; The function `validate-executing-statements-and-procedures' validates all
;;; code-bodies that have started executing, which include those of procedures,
;;; rules, formulas, and simulation-formulas.  This function is called when
;;; there has been a change to KB definitions, which may have invalidated the
;;; environment of any executing code-bodies.

;;; The procedure or statement invocation are validated by checking the items
;;; contained in local-variables.  If the item is either deleted or no longer of
;;; the expected class, the local-variable location is set to NIL.  Also, in
;;; some cases, such as rule-instances that have not yet finished evaluating the
;;; antecedent, if the item is no longer valid, the invocation is dismissed.

;;; Note that expression-cells do not need to be validate because they do not
;;; have local-variable contexts.  Also, note that specific-formulas and
;;; specific-simulation-formulas do not need validation because they do not
;;; items based on a class reference, as generic formulas do.  When the item is
;;; designated by referring to a class, the current class of the item needs to
;;; be validated when there is a change to a definition in the KB.

(defun-void validate-executing-statements-and-procedures ()
  (validate-all-procedure-invocations)
  (validate-all-rule-instances)
  (validate-all-generic-formula-invocations)
  (validate-all-simulation-formula-invocations)
  nil)



;;; The function `validate-all-simulation-formula-invocations' validates the
;;; simulation caching and runtime-structures of variables, parameters, and
;;; generic-simulation-formulas.

;;; This function is called when there has been a change to a class or
;;; superior-class of a user-defined definition at runtime.  This change could
;;; affect the generic-simulation-formulas associated with a variable or
;;; parameter.

(defun-void validate-all-simulation-formula-invocations ()
  (when generic-simulation-formulas-used-p
    (loop for variable-or-parameter being each class-instance of
	    'variable-or-parameter
	  do
      (update-runtime-structures-according-to-edit variable-or-parameter nil))
    (loop for generic-simulation-formula being each class-instance of
	    'generic-simulation-formula
	  do
      (update-runtime-structures-according-to-edit
	generic-simulation-formula nil)))
  nil)



;;; The function `validate-internal-data-structures-containing-items' validates
;;; some internal data-structures that may be affected by a change to items,
;;; resulting from a runtime change to KB definitions.

;;; Note that indexed-attribute hash-tables contain parent-objects of
;;; attributes.  This data-structure needs validation, but is done separately
;;; because the type of validation depends on the change that is being done.
;;; Much of the indexed-attribute validation is done in the slot-putters or
;;; functions called in the slot-putters of definition slots.

(defun-void validate-internal-data-structures-containing-items ()
  (validate-role-service)
  nil)



;;; The function `validate-user-data-structures-containing-items' validates user
;;; data-structures that may be affected by a change to items, resulting from a
;;; runtime change to KB definitions.

;;; The class argument specifies the class that has changed and that is
;;; triggering the validation.  If this is not a user-defined class with
;;; instances, the validation is not done.  The old-class? argument, if non-NIL,
;;; specifies the name of the class before it was changed to the new class name
;;; (the classs argument).

;;; This function checks that the contents g2-lists, g2-arrays, and relations
;;; containing items do not conflict with their defined relation classes or
;;; element-type.  If an element or relation instance is no longer valid it is
;;; removed from the array, list, or relation.

;;; Note that this function does not need to check for deleted items.  Lists,
;;; and relations are already updated when an item is deleted.  Arrays store
;;; frame-serial numbers and so are validated when an item is fetched.

(defun-void validate-user-data-structures-containing-items (class old-class?)
  (when (and (user-defined-class-p class)
	     (loop for thing being each class-instance of class
		   thereis thing))
    (validate-all-item-lists class old-class?)
    (validate-all-item-arrays class old-class?)
    (validate-items-in-all-relations class old-class?)))






;;;; Interface to Compiler




;; Compile-statement-translation will be invoked by the translator.
;; It would be wrong to invoke this from an installation method because
;; compilations are saved with the rule and there is no need to 
;; re-compile when the rule is loaded from a knowledge base.
;; Similarly, it would be wrong to invoke this from the slot putter
;; for the statement translation and text slot since this slot putter
;; is invoked when the knowledge base is loaded.
;; Compile-statement-translation will invoke the method appropriate
;; for the type of statement.  Thus, the correct compilation functions
;; will be invoked whether the statement is an if-then rule, a formula,
;; a simulation-statement, or any other kind of statement.

;; The following code is superceded by the slot-value-compilers in module RULES.
;
;(defun compile-statement-translation (statement translation focus-names)
;  (funcall-method-if-any 'compile-statement
;			 statement
;			 translation
;			 focus-names))

;; Consider passing only a statement argument.
;; This depends on what the translator does.


;(def-class-method compile-statement (rule translation focus-names)
;  (loop for focus-name in focus-names
;	doing (add-to-set (alist-of-compiled-rule-forms
;			    rule)
;			  (eval-cons
;			    focus-name
;			    (compile-if-then-rule
;			      (second translation)
;			      (third translation)
;			      (fourth translation)
;			      focus-name)))))

;; Need to get focus names somehow, perhaps from "focus-keywords"
;; slot in the rule.

;
;
;(def-class-method compile-statement (formula translation)
;  formula translation)
;;; Maybe should go into different file
;
;
;(def-class-method compile-statement (simulation-statement translation)
;  simulation-statement translation)
;;; Maybe should go into different file











;;;; Variable Installation

;;; Basic Approach 

;; (some of this applies for rule installation also)

;;; Slot putters are responsible for putting up and removing frame notes
;;; but not for updating frame status;  this is left to the installation
;;; methods.  This is a good division since slot putters can easily put
;;; up and remove frame notes concerning their slots.  Frame status however
;;; requires checking slots from the frame as a whole and deciding what the
;;; status should be.  This is therefore better left to the installation
;;; methods.  The installation methods don't actually have to check the
;;; slots in the same way the slot putters do.  The installation methods
;;; only have to check the frame notes in the frame status slot and can
;;; use these to decide what the frame status should be.

;; It would be nice to have a hierarchy of frame note types.

;;; The installation methods may still have to check some slots for 
;;; missing values.  If a value is never entered for a slot, the slot
;;; putter is never invoked and it is up to the installation method
;;; to check for problems.

;;; It is important to avoid having the slot putters unnecessarily check
;;; things that are automatically taken care of by the user interface
;;; (by a slot's grammar).

;;; Slot putters should also be responsible for recycling conses of old
;;; slot values that are replaced with new ones.  Slot value reclaimers
;;; (see "kb-frames") should be used for this.  This isn't a high
;;; priority because it is an installation, not run time, issue, and
;;; because many slots don't even have conses in them.  May want to
;;; implement an installation cons pool.

;;; It is easy for slot putters to get the old slot values before they
;;; setf the new value (see the slot putter definition for 
;;; name-or-names-for-frame in "kb-frames").

;;; A number of slots have to be checked for wrong or absent values
;;; before the variable can be installed.
;;; The frame note types for variables are:
;;; 'problem-with-sub-frame-of-variable
;;; 'problem-with-validity-interval-of-variable
;;; The frame note types for simulation frames are:
;;; 'problem-with-initial-value-for-simulation
;;; 'problem-with-simulation-formula
;;; 'problem-with-sub-frame-of-simulation-frame

;;; Consider putting properties on the frame note types indicating the
;;; frame status' possible.  This would make things easier for the
;;; installation methods which check frame notes, among other things,
;;; to determine the frame's status.

;;; Note that in many cases, it is not necessary to check slots for no-value
;;; since they are initialized to nil and there
;;; is no way that the user (if the user interface is working properly)
;;; should be able to set them to no-value.

;; Slot putter for name-or-names-for-frame already exists in "kb-frames".


;;; Deinstall methods are called by delete-frame or possibly by
;;; update-installation methods.  Frame status should be updated to nil.
;;; There is often a complex web of connections that are broken when a
;;; variable is deinstalled, especially if the deinstallation occurs
;;; while the variable is active.  Therefore, if the variable is active,
;;; it is deactivated by calling the deactivate method.  Note that this
;;; takes care of the entire variable including sub-frames such as
;;; simulation-subtable, etc.  Deinstall methods do not have
;;; to do any slot reclamation; this is taken care of by delete-frame.




;;; Frame Note Writers for Variables

(def-frame-note-writer problem-with-sub-frame-of-variable
		       (sub-frame-types)
  (loop as (sub-frame-type . rest-of-types)
	   = sub-frame-types
	then rest-of-types
	do (twrite-string "the ")
	   (twrite sub-frame-type)
	   (if (eq sub-frame-type 'simulation)
	       (twrite-string " subtable")
	       (twrite-string " frame"))
	   (if (null rest-of-types)
	       (return
		 (twrite-string
		   (if (null (cdr sub-frame-types))
		       " has problems"
		       " have problems"))))
	   (twrite-string
	     (cond
	       ((cdr rest-of-types) ", ")
	       ((cddr sub-frame-types) ", and ")
	       (t " and ")))))


(def-frame-note-writer problem-with-validity-interval-of-variable
		       (problem)
  (case problem
    (validity-interval-of-sensor-variable-is-supplied
      (twrite-string "the validity interval of a sensor variable should not be 'supplied"))
    (missing-validity-interval
      (twrite-string "there is no validity interval"))))


(def-frame-note-writer problem-with-initial-value-for-simulation
		       (problem)
  (case problem
    (missing-initial-value
      (twrite-string "a simulated state variable must have an initial value"))
    (unused-initial-value
      (twrite-string "the initial value is not needed"))))


(def-frame-note-writer problem-with-simulation-formula
		       (foo)
  foo
  (twrite-string "there is no simulation computation method"))


(def-frame-note-writer problem-with-sub-frame-of-simulation-frame
		       (sub-frame-types)
  (loop as (sub-frame-type . rest-of-types)
	   = sub-frame-types
	then rest-of-types
	do (twrite-string "the ")
	   (twrite sub-frame-type)
	   (twrite-string " frame ")
	   (if (null rest-of-types)
	       (return
		 (twrite-string
		   (if (null (cdr sub-frame-types))
		       " has problems"
		       " have problems"))))
	   (twrite-string
	     (cond
	       ((cdr rest-of-types) ", ")
	       ((cddr sub-frame-types) ", and ")
	       (t " and ")))))


(def-frame-note-writer problem-with-simulation-class
		       (problem)
  (case problem
    (missing-simulation-class
      (twrite-string "the simulation class must be specified"))))





;;; Slot Putters for Variables



(defvar changing-validity-interval-invalidates-current-value-p t)

(def-slot-putter validity-interval (variable validity-interval initializing?)
  (unless initializing?
    (cancel-task (task-to-check-variable? variable))
    (setf (time-of-oldest-unsatisfied-request? variable) nil)
    (set-not-failed variable))
  (when changing-validity-interval-invalidates-current-value-p
    (setf (expiration-time-of-current-value variable) *some-time-ago*))
  (without-consistency-analysis (variable)
    (setf (validity-interval variable) validity-interval)))


(def-slot-putter background-collection-interval? (variable interval?)
  (let ((old-interval? (background-collection-interval? variable)))
    (setf (background-collection-interval? variable) interval?)
    (if (active-p variable) 
	(let* ((data-server? (get-data-server variable)))
	  (cond ((data-server-p data-server?)
		 (if interval?
		     (begin-collecting-data data-server? variable interval?)
		     (if old-interval?
			 (stop-collecting-data data-server? variable))))
		((eq data-server? 'computation)
		 (if interval?
		     (begin-collecting-data-for-inference-engine
		       variable interval?)
		     (stop-collecting-data-for-inference-engine variable)))))))
  interval?)




(defun variable-frame-status-given-frame-note (frame-note-type particulars variable)
  (case frame-note-type
    (problem-with-sub-frame-of-variable
      (let ((simulation-subtable-status
	      (if (memq 'simulation particulars)
		  (car (frame-status-and-notes
			 (simulation-details variable))))))

	(if (eq simulation-subtable-status 'bad)
	    'bad
	    simulation-subtable-status)))
    (problem-with-validity-interval-of-variable
      (case particulars
	(validity-interval-of-sensor-variable-is-supplied
	  'bad)
	(missing-validity-interval
	  'incomplete)))))

; Note that errors connected with former sensor-frame must be brought into here!


(defun simulation-subtable-status-given-frame-note (frame-note-type particulars simulation-subtable)
  (declare (ignore simulation-subtable))
  (case frame-note-type
    (problem-with-initial-value-for-simulation
      (case particulars
	(missing-initial-value
	  'incomplete)
	(unused-intial-value
	  nil)))
    (problem-with-simulation-formula
      'incomplete)))


(def-text-cell-format rule-display-text-cell-format
		      text-cell-paragraph-indentation 0
		      text-cell-line-spacing 8
		      minimum-format-width-for-text-cell 500)
;; Get rid of this soon.






;;;; Slot Putters for Displays






(def-slot-putter expressions-to-display
		 (display-frame new-expressions initializing?)
  (when (and initializing?
	     (not (frame-of-class-p display-frame 'graph))
	     (not (compilations-up-to-date-p display-frame))
	     loading-kb-p)
    (when (consp new-expressions)
      (reclaim-slot-value (car new-expressions))
      (setf (car new-expressions) no-value))
    (note-frame-with-compilation-removed display-frame)
    (update-frame-status display-frame 'incomplete initializing?))
  (cond
    ((frame-of-class-p display-frame 'graph)
     (if initializing?
	 (setf (expressions-to-display display-frame) new-expressions) 
	 (without-consistency-analysis (display-frame)
	   (setf (expressions-to-display display-frame) new-expressions)
	   (let* ((graph-grid?
		    (get-graph-grid-given-graph display-frame))
		  (display-expressions-1
		    (car new-expressions)))
	     (when (and (not initializing?)
			graph-grid?)
	       (change-slot-value
		 graph-grid?
		 'list-of-plots
		 (when display-expressions-1
		   (if (and (consp display-expressions-1)
			    (eq (car display-expressions-1) '\;))	
		       ;; if list of expressions
		       (loop with graph-expression-without-info 
			     and plot-color? and plot-pattern?
			     and plot-min-and-max?
			     for graph-expression in (cdr display-expressions-1)
			     do
			 (multiple-value-setq
			   (graph-expression-without-info 
			    plot-color? plot-pattern? plot-min-and-max?)
			   (parse-graph-expression-with-info graph-expression))
			     collect
			       (make-plot 
				 graph-expression-without-info 
				 plot-color? plot-pattern? plot-min-and-max?
				 graph-grid?)
						  using slot-value-cons)
		       (multiple-value-bind
			 (graph-expression-without-info 
			  plot-color? plot-pattern? plot-min-and-max?)
			   (parse-graph-expression-with-info
			     display-expressions-1)
			 (slot-value-list 
			   (make-plot 
			     graph-expression-without-info 
			     plot-color? plot-pattern? plot-min-and-max?
			     graph-grid?)))))))
	     (when graph-grid?
	       (let ((redraw-as-well-as-reformat-p t))
		 ;; The graph must be drawn here so that a full redraw will occur.
		 ;; Update-representations-in-tables will draw the graph again but
		 ;; will not update the line drawing description.  Improve so that
		 ;; the graph is only drawn once so that there is only one bitblt!
		 (make-or-reformat-graph-grid 
		   nil
		   graph-grid?
		   (graph-format display-frame)
		   t t)))))))
    ;; If its a cell based display, register the expression cell if any.  Note
    ;; that activation should be suppressed during this registration, since
    ;; consistency between the activation status of the display and the cell
    ;; array is kept consistent throughout the slot value compilers for
    ;; displays.
    ((kind-of-cell-based-display-p display-frame)
     (setf (expressions-to-display display-frame) new-expressions)
     (unless initializing?
       (let ((cell-array? (cell-array display-frame)))
	 (when cell-array?
	   (register-expression-cell-during-slot-putter cell-array? 0 t)))))
    (t
     (setf (expressions-to-display display-frame) new-expressions)
     (unless initializing?
       (let ((priority-of-current-task
	       (display-update-priority display-frame)))
	 (funcall-method 'update-display display-frame nil nil nil)))))
  new-expressions)

;; If display-frame is a graph and initializing? is non-nil, 
;; the slot putter for expressions-to-display 
;; sets up a plot for each expression.  The plots are kept 
;; in the list-of-plots slot of the graph-grid.

;; The slot value reclaimer for list-of-plots also reclaims the plots.


(defun parse-graph-expression-with-info (graph-expression-with-info)
  (if (consp graph-expression-with-info)
      (if (eq (car graph-expression-with-info) '\,)
	  (values (copy-tree-using-slot-value-conses	; can't contain strings/floats
		    (second graph-expression-with-info))
		  (third graph-expression-with-info)
		  (copy-tree-using-slot-value-conses	; can't contain strings/floats
		    (fourth graph-expression-with-info))
		  (let ((min-and-max? (fifth graph-expression-with-info)))
		    (if min-and-max?
			(slot-value-cons
			  (copy-for-slot-value (car min-and-max?))
			  (copy-for-slot-value (cdr min-and-max?))))))
	  (Values (copy-tree-using-slot-value-conses graph-expression-with-info)
		  nil nil nil))
      (values graph-expression-with-info nil nil nil)))


(def-slot-putter label-to-display
		 (display-frame new-label initializing?)
  (when (not initializing?)
    (cond
      ((and (not (text-blank-p new-label))
	    (text-blank-p (label-to-display display-frame)))
       (revise-cell-for-label-to-display display-frame nil))
      ((and (text-blank-p new-label)
	    (not (text-blank-p (label-to-display display-frame))))
       (revise-cell-for-label-to-display display-frame t))))
  (setf (label-to-display display-frame) new-label))

;; When a label-to-display is entered, a text cell is made and put into the
;; left cell of the table to represent this slot.  This cell will 
;; automatically be updated by update-representations-in-tables since this is
;; called by change-slot-value after the slot putter.  However, when a
;; label-to-display is removed (text is blank), a text cell is made to
;; represent the expressions-to-display slot and this is put into the
;; left cell of the table.  This cell will not be automatically updated
;; since it is not a representation of label-to-display, it is a representation
;; of expressions-to-display.  Therefore, change-slot-value is called for
;; the expressions-to-display slot so that the cell is updated.


(defun revise-cell-for-label-to-display (display-frame new-label-blank?)
  (cond 
    ((frame-of-class-p display-frame 'readout-table)
     (update-images-of-block display-frame t t)
     (reclaim-text (text? (caar (table-rows display-frame))))
     (setf (caar (table-rows display-frame))
	   (make-readout-table-expression-text 
	     display-frame 
	     (if new-label-blank? 'expressions-to-display 'label-to-display)
	     nil))
     (reformat-table-in-place display-frame)
     (update-images-of-block display-frame nil t))
    ((frame-of-class-p display-frame 'graph)
     (with-updating-that-requires-the-draw-function-be-used
	 (update-images-of-block display-frame t t))
     (reclaim-text (text? (car (second (table-rows display-frame)))))
     (setf (car (second (table-rows display-frame)))
	   (make-horizontal-axis-graph-heading-text-1
	     display-frame
	     (if new-label-blank? 'expressions-to-display 'label-to-display)
	     nil))
     (reformat-table-in-place display-frame)
     (with-updating-that-requires-the-draw-function-be-used
	 (update-images-of-block display-frame nil t))))
  (when new-label-blank?
    (change-slot-value display-frame 'expressions-to-display
		       (expressions-to-display display-frame))))


(def-slot-putter format-for-readout-table
		 (display-frame new-value initializing?)
  (setf (format-for-readout-table display-frame) new-value)
  (when (not initializing?)
    (let ((priority-of-current-task
	    (display-update-priority display-frame)))
      (funcall-method 'update-display display-frame t nil nil))
    (values new-value nil)))

(def-slot-putter display-evaluation-should-use-simulated-values?
		 (display-frame new-value initializing?)
  (setf (display-evaluation-should-use-simulated-values?
	  display-frame)
	new-value)
  (when (not initializing?)
    (cond ((frame-of-class-p display-frame 'graph)
	   (reformat-graph-based-on-edit-if-necessary
	     display-frame initializing?))
	  ((kind-of-cell-based-display-p display-frame)
	   (update-cell-based-display-computation-style display-frame))
	  (t
	   (let ((priority-of-current-task
		   (display-update-priority display-frame)))
	     (funcall-method 'update-display display-frame nil nil nil))
	   (values new-value nil)))))


(def-slot-putter low-value-for-dial-ruling
		 (dial new-value initializing?)
  (put-slot-value-for-dial-ruling-parameter
    dial 'low-value-for-dial-ruling new-value initializing?))


(def-slot-putter high-value-for-dial-ruling
		 (dial new-value initializing?)
  (put-slot-value-for-dial-ruling-parameter
    dial 'high-value-for-dial-ruling new-value initializing?))


(def-slot-putter increment-per-dial-ruling
		 (dial new-value initializing?)
  (put-slot-value-for-dial-ruling-parameter
    dial 'increment-per-dial-ruling new-value initializing?))


(def-slot-putter low-value-for-meter-ruling
		 (meter new-value initializing?)
  (put-slot-value-for-meter-ruling-parameter
    meter 'low-value-for-meter-ruling new-value initializing?))


(def-slot-putter high-value-for-meter-ruling
		 (meter new-value initializing?)
  (put-slot-value-for-meter-ruling-parameter
    meter 'high-value-for-meter-ruling new-value initializing?))


(def-slot-putter increment-per-meter-ruling
		 (meter new-value initializing?)
  (put-slot-value-for-meter-ruling-parameter
    meter 'increment-per-meter-ruling new-value initializing?))


(defun put-slot-value-for-dial-ruling-parameter
       (dial slot-name new-value initializing?)
  (set-slot-value dial slot-name new-value)
  (when (not initializing?)
    (let ((dial-ruling (get-ruling-for-dial dial)))
      (erase-images-of-block dial-ruling t)
      (make-or-reformat-ruling-for-dial dial-ruling dial)
      (draw-images-of-block dial-ruling t))
    (let ((priority-of-current-task (display-update-priority dial)))
      (funcall-method 'update-display dial t nil nil))
    (values new-value nil)))

(defun put-slot-value-for-meter-ruling-parameter
       (meter slot-name new-value initializing?)
  (set-slot-value meter slot-name new-value)
  (when (not initializing?)
    (let ((meter-ruling (get-ruling-for-meter meter)))
      (erase-images-of-block meter-ruling t)
      (make-or-reformat-ruling-for-meter meter-ruling meter)
      (draw-images-of-block meter-ruling t))
    (let ((priority-of-current-task (display-update-priority meter)))
      (funcall-method 'update-display meter nil nil nil))
    (values new-value nil)))

;; The meter ruling and meter marker are both updated.



(defmacro define-slot-putter-causing-graph-reformat (slot-name &body body)
  (let ((primary-action
	  `(progn (setf (,slot-name graph) new-value)
		  (reformat-graph-based-on-edit-if-necessary graph initializing?))))
    `(def-slot-putter ,slot-name (graph new-value initializing?)
       ,(subst primary-action :do-it (if body (cons 'progn body) :do-it)))))

(defun without-tickmark-labels-state-changed-p (new-value old-value)
  (macrolet ((no-label-p (slot-value)
	       `(and (consp ,slot-value) (eq (car ,slot-value) 'without-tickmark-labels))))
    (g2-xor (no-label-p new-value) (no-label-p old-value))))

(define-slot-putter-causing-graph-reformat desired-range-for-horizontal-axis?
  (let ((changing-graph-margins?
	  (or changing-graph-margins?
	      (without-tickmark-labels-state-changed-p
		new-value
		(desired-range-for-horizontal-axis? graph)))))
    :do-it))

(define-slot-putter-causing-graph-reformat desired-range-for-vertical-axis?
  (let ((changing-graph-margins?
	  (or changing-graph-margins?
	      (without-tickmark-labels-state-changed-p
		new-value
		(desired-range-for-vertical-axis? graph)))))
    :do-it))

(define-slot-putter-causing-graph-reformat interval-between-horizontal-grid-lines?)

(define-slot-putter-causing-graph-reformat scroll-continuously?)

(define-slot-putter-causing-graph-reformat show-grid-lines?)

(define-slot-putter-causing-graph-reformat extra-grid-lines?)

(define-slot-putter-causing-graph-reformat background-colors)

(defun reformat-graph-based-on-edit-if-necessary (graph initializing?)
  (when (not initializing?)
    (let ((redraw-as-well-as-reformat-p t))
      (make-or-reformat-graph-grid
	nil
	(get-graph-grid-given-graph graph)
	(graph-format graph)
	t t))))


(def-slot-putter display-update-interval
		 (display new-value initializing?)
  (setf (display-update-interval display) new-value)
  (if (kind-of-cell-based-display-p display)
      (when (not initializing?)
	(update-cell-based-display-computation-style display))
      (reschedule-display-update display initializing?))
  new-value)

(def-slot-putter display-wait-interval
		 (display new-value initializing?)
  (setf (display-wait-interval display) new-value)
  (if (kind-of-cell-based-display-p display)
      (when (not initializing?)
	(update-cell-based-display-computation-style display))
      (reschedule-display-update display initializing?))
  new-value)

(def-slot-putter display-update-priority
		 (display new-value initializing?)
  (setf (display-update-priority display) new-value)
  (if (kind-of-cell-based-display-p display)
      (when (not initializing?)
	(update-cell-based-display-computation-style display))
      (reschedule-display-update display initializing?))
  new-value)



(defun-void scheduled-display-update (display)
  (funcall-method 'update-display display nil nil nil))

(defun reschedule-display-update (display initializing?)
  (when (and (not initializing?)
	     (runnable-p display))
    (let ((wait (display-wait-interval display))
	  (update (display-update-interval display)))
      (with-future-scheduling
	  ((display-update-task? display)
	   (display-update-priority display)
	   (+e (managed-float-value (clock-get current-g2-time))
	       (if (fixnump wait)
		   (coerce-fixnum-to-gensym-float wait)
		   (managed-float-value wait)))
	   (if (fixnump update)
	       (coerce-fixnum-to-gensym-float update)
	       (managed-float-value update)))
	(scheduled-display-update display)))))




;;; The function `set-simulation-stored-history-spec-for-update-slot-description'
;;; takes care of changing the values of the simulation-stored-history-
;;; specification? of the simulation-details? for a class of variables.  The
;;; class default value can be set in the attribute-initializations slot for
;;; the class.  

(defun set-simulation-stored-history-spec-for-update-slot-description
    (class unchanged-slot-init-form new-slot-init-form?)
  (loop for instance being each strict-class-instance of class
	for simulation-details = (simulation-details instance)
	do
    (when (and simulation-details
	       (equal (simulation-stored-history-specification?
			simulation-details)
		      unchanged-slot-init-form))
      (change-slot-value
	simulation-details 'simulation-stored-history-specification?
	(copy-for-slot-value new-slot-init-form?)))))
	
      



(def-slot-putter variable-or-parameter-history-specification?
		 (variable new-value initializing?)
  (setf (variable-or-parameter-history-specification? variable) new-value)
  (when (not initializing?)
    (setf (variable-or-parameter-stored-histories? variable)
	  (reformat-history-based-on-edit
	    (variable-or-parameter-stored-histories? variable) new-value))))

(def-slot-putter simulation-stored-history-specification?
		 (simulation-subtable new-value initializing?)
  (setf (simulation-stored-history-specification? simulation-subtable) new-value)
  (when (not initializing?)
    (setf (simulation-stored-histories? simulation-subtable)
	  (reformat-history-based-on-edit
	    (simulation-stored-histories? simulation-subtable) new-value))))


;; Review reformat-history-based-on-edit.  Should the history be reformatted if
;; the granularity changes??  - cpm, 6/9/94

(defun reformat-history-based-on-edit
    (value-history-cascaded-ring-buffer? new-value)
  (let ((maximum-number-of-data-points? (second new-value))
	(maximum-age-of-data-points? (third new-value)))
    (when value-history-cascaded-ring-buffer?
      (cond
	;; Return the cascaded-ring-buffer, if any.
	((or maximum-number-of-data-points?
	     maximum-age-of-data-points?)
	 (prog1
	     (make-or-reformat-cascaded-ring-buffer
	       value-history-cascaded-ring-buffer?
	       (second new-value)
	       (third new-value)
	       (fourth new-value))
	   (map-over-cascaded-ring-buffer-clients
	     'notify-client-of-change-to-cascaded-ring-buffer
	     value-history-cascaded-ring-buffer?)))
	(t
	 (map-over-cascaded-ring-buffer-clients
	   'notify-client-of-change-to-cascaded-ring-buffer
	   value-history-cascaded-ring-buffer?)
	 (reclaim-history-buffer value-history-cascaded-ring-buffer?)
	 nil)))))




;;;; Installation for Simulation

;;; The ultimate goal of installation for the simulator is to appropriately
;;; set the simulation-category? slot of simulated variables and parameters
;;; (see slot putter for simulation-category? below).  This is accomplished
;;; by the put-box-translation-and-text-slot-value method for
;;; generic-simulation-formulas and by the slot putter for simulation-formulas?
;;; when a specific simulation formula is specified.

(def-kb-specific-property-name generic-simulation-formulas-for-this-role)

(defun add-formula-to-generic-simulation-formulas-for-this-role
       (role class-or-item new-generic-simulation-formula)
  (add-to-set (generic-simulation-formulas-for-this-role
		(compute-key-from-role-class-or-item
		  (atomic-naming-element-of-role role) class-or-item))
	      new-generic-simulation-formula))

(defun delete-formula-from-generic-simulation-formulas-for-this-role
       (role class-or-item generic-simulation-formula-to-delete)
  (delete-from-set (generic-simulation-formulas-for-this-role 
		     (compute-key-from-role-class-or-item role class-or-item))
		   generic-simulation-formula-to-delete))

(defun compute-key-from-role-class-or-item (role class-or-item)
  (or role
      (get-simulation-formula-class-or-item-name class-or-item)))

(defun get-simulation-formula-class-or-item-name (class-or-item)
  (if (symbolp class-or-item)
      class-or-item
      (second class-or-item)))




;; I moved to the following variable up here, away from its section, because
;; it is needed in the next function. (MHD 10/16/91)

(def-system-variable post-analyzer-warning-notes-for-generic-simulation-formulas?
		     INSTALL nil)




;;; The slot putter for box-translation-and-text-slot-value for
;;; generic-simulation-formula performs the following
;;; installation tasks:
;;; 1.  Adds the simulation formula to the generic-simulation-formulas-for-this-role
;;; property of the role name
;;; 2.  Sets the simulation-category-for-this-role and 
;;; initial-value-for-this-role properties of the role name.  If there
;;; is a conflict, then a frame note is put up on the simulation formula.
;;; 3.  Finds all variables that can use this simulation formula and 
;;; a.  adds the variable to the list of variables to be simulated,
;;; b.  if the variable has no specific simulation formula and there
;;; is no conflict,  sets the simulation-category? and initial-value?
;;; slots of the variable.

;;; If the initial value is an expression rather than a number or nil,
;;; then the initial-value-for-this-role property and the initial-value?
;;; slot of the variable will be set to
;;; 'use-initial-value-expression-in-generic-simulation-formula.
;;; This indicates to the simulator that it should get the initial value
;;; expression from the formula (see also initialize-simulator).

;;; These side effects have to be undone by the cleanup method for the
;;; generic-simulation-formula.

;;; Generic-simulation-formulas-for-this-role is a kb specific property of 
;;; attribute names which holds generic formulas for computing the 
;;; simulated value.  Note that only one generic-simulation-formula for a
;;; given role and class is allowed.  If more are entered, an error message
;;; is posted and the extra generic-simulation-formula is given a bad status.
;;; It is however added to generic-simulation-formulas-for-this-role so that
;;; if the other formulas for that class and role are deleted, its status 
;;; becomes O.K. and it becomes the formula for that class and role.
;;; Thus, at runtime, the simulator must check the status of a formula
;;; before it can be used.
;;; Note that if role-and-class-changed? is nil, then the status
;;; of the generic simulation formula regarding other generic simulation
;;; formulas for the same role and class will not be changed.
;;; This is done so that the act of editing the right side of the formula
;;; (which has nothing to do with the role or class to which the formula
;;; applies) does not cause a change in the status of the formula
;;; regarding other generic simulation formulas for the same role and class.
;;; Note also that generic compiler frame notes and frame notes indicating
;;; that there are other generic simulation formulas for the same role and
;;; class are put up independently.  Suppose a generic simulation formula
;;; with a compile problem is put up and its frame status is bad.  If another
;;; generic simulation formula for the same role and class is put up, the
;;; new one will get a frame note indicating more than one formula with the
;;; same role and class, even though the first one has a bad frame status.

(def-class-method put-box-translation-and-text-slot-value
		  (generic-simulation-formula box-translation-and-text 
		   initializing?)

  ;; In the style of the put-NEW-box-translation-and-text-slot-value method
  ;; for rule:  (MHD 7/1/91)
  (when (and initializing?
	     (not (compilations-up-to-date-p generic-simulation-formula))
	     loading-kb-p)
    (reclaim-slot-value (car box-translation-and-text))
    (setf (car box-translation-and-text) no-value)
    (note-frame-with-compilation-removed generic-simulation-formula))

  (let ((post-analyzer-warning-notes-for-generic-simulation-formulas? t))
    (without-consistency-analysis (generic-simulation-formula)
      (let* ((old-translation?
	       (unless 
		 (or initializing?
		     (null (box-translation-and-text generic-simulation-formula))
		     (eq (car (box-translation-and-text 
				generic-simulation-formula)) no-value))
		 (car (box-translation-and-text generic-simulation-formula))))
	     (new-translation
	       (if (and (consp box-translation-and-text)
			(neq (car box-translation-and-text) no-value))
		   (car box-translation-and-text)))
	     new-role-name old-role-name new-class-or-item old-class-or-item
	     new-left-side old-left-side)
	(when new-translation
	  (setq new-role-name
		(simulation-role-given-translation new-translation)
		new-class-or-item
		(simulation-class-or-item-given-translation new-translation)
		new-left-side
		(left-side-of-simulation-formula-given-translation new-translation)))
	(when old-translation?
	  (setq old-role-name
		(simulation-role-given-translation old-translation?)
		old-class-or-item
		(simulation-class-or-item-given-translation old-translation?)
		old-left-side
		(left-side-of-simulation-formula-given-translation old-translation?)))
	
	(when old-translation?
	  (delete-formula-from-generic-simulation-formulas-for-this-role
	    old-role-name old-class-or-item generic-simulation-formula)
	  (forward-install-variables-for-generic-simulation-formula
	    old-left-side old-class-or-item generic-simulation-formula))
	
;      (if (third new-translation)
;	   (update-frame-status generic-simulation-formula nil initializing?)
;	   (update-frame-status generic-simulation-formula 'bad initializing?))
	;; Changed the above to the following:  (MHD 6/25/91)
	(update-frame-status
	  generic-simulation-formula
	  (cond ((and
		   (or
		     (generic-simulation-formula-byte-code-body generic-simulation-formula)
		     loading-kb-p)
		   (third new-translation))
		   nil)
		((or
		   (compiler-errors? generic-simulation-formula)
		   (and
		     (not loading-kb-p)
		     ;;during load even good generic-simulation-formulas will meet this condition
		     (third new-translation)
		     (null (generic-simulation-formula-byte-code-body generic-simulation-formula)))
		   old-translation?)
		 'bad)
		(t 'incomplete))
	  initializing?)
	(setf (box-translation-and-text generic-simulation-formula) 
	      box-translation-and-text)
	
	(when new-translation
	  (add-formula-to-generic-simulation-formulas-for-this-role
	    new-role-name new-class-or-item generic-simulation-formula)
	  (forward-install-variables-for-generic-simulation-formula
	    new-left-side new-class-or-item generic-simulation-formula)))
      (update-runtime-structures-according-to-edit generic-simulation-formula)
      (update-generic-simulation-formulas-used-p)))
  (values box-translation-and-text nil))



(defun update-generic-simulation-formulas-used-p ()
  (if (loop for formula being each class-instance of 'generic-simulation-formula
	    thereis formula)
      (setq generic-simulation-formulas-used-p t)
      (setq generic-simulation-formulas-used-p nil)))



;;; The slot putter for generic-simulation-formula-byte-code-body changes the
;;; byte-code-body within a window for consistency analysis changes.

(def-slot-putter generic-simulation-formula-byte-code-body
		 (generic-simulation-formula new-byte-code-body initializing?)
  (when (and initializing?
	     (not (compilations-up-to-date-p generic-simulation-formula))
	     loading-kb-p)
    (reclaim-slot-value new-byte-code-body)
    (setq new-byte-code-body nil)
    (note-frame-with-compilation-removed generic-simulation-formula))
  (without-consistency-analysis (generic-simulation-formula)
    (setf (generic-simulation-formula-byte-code-body generic-simulation-formula)
	  new-byte-code-body))
  new-byte-code-body)

(def-slot-putter generic-simulation-initial-value-byte-code-body
		 (generic-simulation-formula new-byte-code-body initializing?)
  (when (and initializing?
	     (not (compilations-up-to-date-p generic-simulation-formula))
	     loading-kb-p)
    (reclaim-slot-value new-byte-code-body)
    (setq new-byte-code-body nil)
    (note-frame-with-compilation-removed generic-simulation-formula))
  (without-consistency-analysis (generic-simulation-formula)
    (setf (generic-simulation-initial-value-byte-code-body
	    generic-simulation-formula)
	  new-byte-code-body))
  new-byte-code-body)



(def-class-method cleanup (generic-simulation-formula)
  (funcall-superior-method generic-simulation-formula)
  (change-slot-value 
    generic-simulation-formula 'generic-simulation-formula-byte-code-body nil)
  (change-slot-value 
    generic-simulation-formula 
    'generic-simulation-initial-value-byte-code-body nil)
  (change-slot-value generic-simulation-formula 'box-translation-and-text nil))

;; Consider using slot value reclaimer instead.



;(defun variable-or-parameter-has-simulation-subtable-formula? (variable-or-parameter)
;  (and (variable-p variable-or-parameter)
;       (simulation-details variable-or-parameter)
;       (second
;	 (car (simulation-formulas? (simulation-details variable-or-parameter))))))



;;; Forward-install-variables-for-generic-simulation-formula takes a left side
;;; simulation formula designation and a focal class or item and determines which
;;; variables may have to be re-installed for simulation.  It thus accomplishes a
;;; level of filtering to avoid having to re-install all variables.

(defun forward-install-variables-for-generic-simulation-formula 
       (left-side-designation class-or-item generic-simulation-formula)
  (unless loading-kb-p
    (cond
      ((symbolp class-or-item)			       ; if class
       (loop with alist = (gensym-list (gensym-cons class-or-item nil))
	     with *current-computation-frame* = generic-simulation-formula
	     with current-computation-flags = current-computation-flags
	     with designated-item
	     initially (setf (role-serve-inactive-objects?) t)
	     for item being each class-instance of class-or-item
	     do
	 (setf (cdar alist) item)
	 (setq designated-item (evaluate-designation left-side-designation alist))
	 (when (of-class-p designated-item 'variable-or-parameter)
	   (update-generic-simulation-formula-for-variable-or-parameter
	     designated-item))
	     finally (reclaim-gensym-tree alist)))
      (t
       (let ((current-computation-flags current-computation-flags))
	 (setf (role-serve-inactive-objects?) t)
	 (let* ((*current-computation-frame* generic-simulation-formula)
		(designated-item (evaluate-designation left-side-designation nil)))
	   (when (of-class-p designated-item 'variable-or-parameter)
	     (update-generic-simulation-formula-for-variable-or-parameter
	       designated-item))))))))



;;; Generic-simulation-formula-for-variable-or-parameter returns the most specific
;;; generic simulation formula (if any) for the variable or parameter.

(def-system-variable focal-entity-for-simulation-formula INSTALL nil)
(def-system-variable get-focal-entity-for-simulation-formula? INSTALL nil)

(defun generic-simulation-formula-for-variable-or-parameter 
       (variable-or-parameter)
  (let (formula focal-entity?
	(name-or-names (name-or-names-for-frame variable-or-parameter)))
    (cond
      ((consp name-or-names)
       (loop for name in name-or-names 
	     do
	 (multiple-value-setq
	   (formula focal-entity?)
	   (generic-simulation-formula-for-variable-or-parameter-1
	     variable-or-parameter name))
	 (when formula
	   (return-from generic-simulation-formula-for-variable-or-parameter
	     (values formula focal-entity?)))))
      (t
       (multiple-value-setq
	 (formula focal-entity?)
	 (generic-simulation-formula-for-variable-or-parameter-1
	   variable-or-parameter name-or-names))
       (when formula
	 (return-from generic-simulation-formula-for-variable-or-parameter
	   (values formula focal-entity?)))))
    (multiple-value-setq
      (formula focal-entity?)
      (generic-simulation-formula-for-variable-or-parameter-1
	variable-or-parameter (class variable-or-parameter)))
    (when formula
      (return-from generic-simulation-formula-for-variable-or-parameter
	(values formula focal-entity?)))
    
    (multiple-value-bind
      (parent-entity slot-name)
	(get-kb-parent-information variable-or-parameter)
      (when parent-entity
	(generic-simulation-formula-for-variable-or-parameter-1
	  variable-or-parameter slot-name)))))

(defun generic-simulation-formula-for-variable-or-parameter-1 
       (variable-or-parameter role-or-other-key)
  (when role-or-other-key
    (let ((most-specific-formula nil)
	  (most-specific-class? nil)
	  (focal-entity? nil))
      (let*-sim ((*current-computation-frame* variable-or-parameter)
		 (note-things-encountered-during-role-service? t)
		 (things-that-affect-this-formula nil)
		 (current-computation-flags current-computation-flags))
	(setf (role-serve-inactive-objects?) t)
	(loop for simulation-formula
		  in (generic-simulation-formulas-for-this-role role-or-other-key)
	      do
	  (when (frame-ok-p simulation-formula)
	    (let ((class-or-item
		    (simulation-formula-class-or-item simulation-formula)))
	      (cond
		((symbolp class-or-item)	; if class
		 (when (or (null most-specific-class?)
			   (not (subclassp most-specific-class? class-or-item)))
		   (let*-sim ((get-focal-entity-for-simulation-formula? t)
			      (focal-entity-for-simulation-formula nil))
		     (when (generic-simulation-formula-applies-to-this-variable?
			     simulation-formula variable-or-parameter)
		       (setq most-specific-class? class-or-item
			     most-specific-formula simulation-formula
			     focal-entity? focal-entity-for-simulation-formula)))))
		(t
		 (when (generic-simulation-formula-applies-to-this-variable?
			 simulation-formula variable-or-parameter)
		   (note-runtime-structure-in-things-that-affect-it
		     variable-or-parameter things-that-affect-this-formula t)
		   (reclaim-eval-list things-that-affect-this-formula)
		   (setq most-specific-formula simulation-formula)
		   (return))))))
	      finally
		(note-runtime-structure-in-things-that-affect-it
		  variable-or-parameter things-that-affect-this-formula t)
		(reclaim-eval-list things-that-affect-this-formula)))
      (values most-specific-formula focal-entity?))))

;; Note that things-that-affect-this-formula is actually accumulated for all
;; formulas encountered.  This is necessary in order to make sure that all things
;; which affect the variable are noted.



(defun generic-simulation-formula-applies-to-this-variable? 
       (generic-simulation-formula variable-or-parameter)
  (designation-denotes-item-p
    (simulation-formula-left-side generic-simulation-formula) variable-or-parameter))



;; It is assumed that if the slots sensor-frame?, and simulation-details,
;; are not nil, they contain the appropriate frame type.  If the user
;; interface is working properly, there should be no need to double
;; check this.  Also, it is not the responsibility of the slot putters
;; or installation methods for variables to check for problems in these
;; other frames; this is handled by installation methods for these
;; frames.  The appropriate slot putters for variables should however
;; check the frame-status-and-notes slot of these frames and if it is
;; non-nil, post a message of type 'problem-with-sub-frame-of-variable.

;; It is also assumed that when a sub-frame of a variable (a sensor
;; frame for example) is loaded or modified, it is put into the variable
;; using the slot putter and it has already been fully checked for
;; problems.  


(def-slot-putter simulation-details
		 (variable simulation-details initializing?)
  (body-of-put-for-simulation-frame
    variable simulation-details initializing?)
  (setf (simulation-details variable) simulation-details))

;; The above slot-putter is called by make-simulation-subtable-and-install.  This
;; is only because slot-putters are not currently being called to initialize.



(defun body-of-put-for-simulation-frame
    (variable simulation-details initializing?)
  (if (and simulation-details
	   (frame-status-and-notes simulation-details))  ; if not nil (not completely o.k.)
      (add-to-frame-note-particulars-list-if-necessary
	'simulation 'problem-with-sub-frame-of-variable variable)
      (delete-from-frame-note-particulars-list
	'simulation 'problem-with-sub-frame-of-variable variable))
  (if (and (not loading-kb-p) simulation-details)
      (add-as-inferior-block simulation-details variable))
  (let ((old-value?
	  (if (not initializing?)
	      (simulation-details variable))))
    (cond 
      ((null old-value?)
       (cond
	 (simulation-details
	  (let ((class-history-spec-for-simulation-subtables?
		  (slot-init-form
		    (slot-description-from-class
		      (class variable)
		      'history-specification-for-simulation-subtables?))))
	    (when class-history-spec-for-simulation-subtables?
	      (put-simulation-stored-history-specification?
		simulation-details
		(copy-for-slot-value class-history-spec-for-simulation-subtables?) t)))
	  (setf (parent-variable simulation-details) variable))))
      (t					; if both old and new, they must be eq
       (if (null simulation-details)
	   ;; Test if old-value is a frame.  Some pre-2.0 kb's could have on
	   ;; old-value set to the slot init-form (:funcall
	   ;; make-simulation-frame-and-install).  See bug #3892.  - cpm,
	   ;; 10/23/92
	   (when (framep old-value?)
	     (delete-frame old-value?))))))
  (when (and simulation-details (active-p variable))
    (funcall-method 'activate-if-possible-and-propagate
		    simulation-details))
  (let ((simulation-info? (simulation-info? variable)))
    (when simulation-info?
      (setf (variable-has-subtable-p simulation-info?) 
	    (if simulation-details t nil))))
  simulation-details)

;; This is defined outside of the slot putter for the benefit of
;; make-simulation-subtable-and-install.  Due to deficiencies in make-frame, the
;; slot putter can't be used because it sets a lookup slot.



(def-slot-putter simulation-subtable-byte-code-body
		 (simulation-subtable new-byte-code-body initializing?)
  (when (and initializing?
	     (not (compilations-up-to-date-p simulation-subtable))
	     loading-kb-p)
    (reclaim-slot-value new-byte-code-body)
    (setq new-byte-code-body nil)
    (note-frame-with-compilation-removed simulation-subtable))
  (without-consistency-analysis (simulation-subtable)
    (setf (simulation-subtable-byte-code-body simulation-subtable)
	  new-byte-code-body))
  new-byte-code-body)

(def-slot-putter simulation-subtable-initial-value-byte-code-body
		 (simulation-subtable new-byte-code-body initializing?)
  (when (and initializing?
	     (not (compilations-up-to-date-p simulation-subtable))
	     loading-kb-p)
    (reclaim-slot-value new-byte-code-body)
    (setq new-byte-code-body nil)
    (note-frame-with-compilation-removed simulation-subtable))
  (without-consistency-analysis (simulation-subtable)
    (setf (simulation-subtable-initial-value-byte-code-body 
	    simulation-subtable)
	  new-byte-code-body))
  new-byte-code-body)



(defun valid-simulation-formula-p (simulation-formula)
  (if simulation-formula
      (let ((info-without-text (car simulation-formula)))
	(and info-without-text
	     (not (no-value-p info-without-text))))))



;;; When the simulation frame of a variable is deleted, it is important that the
;;; simulation-category?  and initial-simulated-value?  slots of the variable be
;;; updated appropriately.  Its status as a variable to simulate must also be
;;; updated appropriately.

(def-class-method cleanup (simulation-subtable)
  (funcall-superior-method simulation-subtable)
  (let ((variable
	  (parent-variable simulation-subtable)))
    (when (and variable
	       (not (frame-being-deleted-p variable)))
      (put-specific-simulation-formula-into-variable-or-parameter
	variable nil)
      ;; to update simulation-category? and initial-simulated-value?
      ;; according to generic simulation formulas if any exist

      (change-slot-value variable 'simulation-details nil))
    (change-slot-value simulation-subtable 'simulation-formulas? nil)
    (change-slot-value 
      simulation-subtable 'simulation-stored-history-specification? nil)
    (change-slot-value 
      simulation-subtable 'simulation-subtable-byte-code-body nil)
    (change-slot-value 
      simulation-subtable 
      'simulation-subtable-initial-value-byte-code-body nil)))



(def-slot-value-reclaimer simulation-details (simulation-subtable?)  
  (delete-frame simulation-subtable?))

(def-slot-putter non-default-initial-simulated-value?
		 (variable initial-simulated-value? initializing?)
  (setf (non-default-initial-simulated-value?
	  variable)
	initial-simulated-value?)
  (if (not initializing?)
      (change-slot-value variable 'simulation-details (simulation-details variable)))
  initial-simulated-value?)


(defun update-generic-simulation-formula-for-variable-or-parameter
    (variable-or-parameter)  
  (multiple-value-bind 
      (formula? focal-entity?)
      (generic-simulation-formula-for-variable-or-parameter 
	variable-or-parameter)
    (put-generic-simulation-formula-into-variable-or-parameter
      variable-or-parameter formula? focal-entity?)))

(defun get-or-make-simulation-info (variable-or-parameter make-new?)
  (or (simulation-info? variable-or-parameter)
      (when make-new?
	(let ((new-simulation-info
		(make-simulation-info)))
	  (setf (variable-for-simulation-info new-simulation-info)
		variable-or-parameter)
	  (when (and (variable-p variable-or-parameter)
		     (simulation-details variable-or-parameter))
	    (setf (variable-has-subtable-p new-simulation-info) t))
	  new-simulation-info))))



(def-system-variable inhibit-model-install? INSTALL nil)

(defun put-generic-simulation-formula-into-variable-or-parameter
       (variable-or-parameter generic-simulation-formula? focal-entity?)
  (let ((simulation-info?
	  (get-or-make-simulation-info 
	    variable-or-parameter generic-simulation-formula?)))
    (when simulation-info?
      (setf (generic-formula? simulation-info?)
	    generic-simulation-formula?
	    (generic-formula-focal-entity? simulation-info?)
	    focal-entity?)
      (change-slot-value 
	variable-or-parameter 'simulation-info? simulation-info?)
      (when (not inhibit-model-install?)
	(install-item-in-model-if-models-used variable-or-parameter)))))

(defun put-specific-simulation-formula-into-variable-or-parameter
       (variable-or-parameter simulation-subtable?)
  (let ((simulation-info?
	  (get-or-make-simulation-info 
	    variable-or-parameter simulation-subtable?)))
    (when simulation-info?
      (setf (specific-formula? simulation-info?)
	    simulation-subtable?)
      (change-slot-value 
	variable-or-parameter 'simulation-info? simulation-info?)
      (install-item-in-model-if-models-used variable-or-parameter))))

(defun put-external-simulation-formula-into-variable-or-parameter
       (variable-or-parameter external-simulation-definition?)
  (let ((simulation-info?
	  (get-or-make-simulation-info 
	    variable-or-parameter external-simulation-definition?)))
    (when simulation-info?
      (setf (external-simulation-definition? simulation-info?)
	    external-simulation-definition?)
      (change-slot-value 
	variable-or-parameter 'simulation-info? simulation-info?)
      (install-item-in-model-if-models-used variable-or-parameter))))

;; Note that in the above functions, generic-simulation-formula?,
;; simulation-subtable?, and external-simulation-definition?  can be nil, in which
;; case, the variable or parameter is marked as not having one of these.



(def-slot-putter simulation-info? 
		 (variable-or-parameter simulation-info? initializing?)
  (let ((old-simulation-info? 
	  (when (not initializing?)
	    (simulation-info? variable-or-parameter))))
    (delete-frame-note-if-any 
      'more-than-one-simulation-specifier-for-variable variable-or-parameter)
    ;; I'm not sure why the frame is being marked OK here in the first
    ;; place. But it's certainly wrong to do so if we are in the process
    ;; of deleting the frame, and we call this slot-putter as part of
    ;; the cleanup on variable and parameter; see the comment on the
    ;; cleanup method to see why. If we call update-frame-status while
    ;; the variable is being deleted, it may try to reactivate it,
    ;; which was causing a crash. -alatto, 7/19/02
    (unless (frame-being-deleted-p variable-or-parameter)
      (update-frame-status variable-or-parameter nil nil))
    (cond
      (simulation-info?
       (when (and (generic-formula? simulation-info?)
		  (external-simulation-definition? simulation-info?))
	 (warning-message 
	   2 "Installation problem:  variable-or-parameter ~NF has more than one simulation specifier"
	   variable-or-parameter)
	 (add-to-frame-note-particulars-list-if-necessary
	   nil 
	   'more-than-one-simulation-specifier-for-variable
	   variable-or-parameter)
	 (update-frame-status variable-or-parameter 'bad nil))
       (multiple-value-bind
	 (category initial-value? time-increment?)
	   (get-category-info-given-simulation-info simulation-info?)
	 (cond 
	   (category
	    (reclaim-slot-value (specific-time-increment? simulation-info?))
	    (reclaim-slot-value (initial-value? simulation-info?))
	    (setf (simulation-info? variable-or-parameter) simulation-info?
		  (simulation-category simulation-info?) category
		  (initial-value? simulation-info?) 
		  (copy-for-slot-value initial-value?)
		  (specific-time-increment? simulation-info?) 
		  (copy-for-slot-value time-increment?))
	    (remove-variable-from-simulation variable-or-parameter)
	    (add-variable-to-simulation variable-or-parameter))
	   (t					       ; if variable not being simulated
	    (when old-simulation-info?
	      (remove-simulation-info-from-variable-or-parameter 
		variable-or-parameter))))))
      (t
       (when old-simulation-info?
	 (remove-simulation-info-from-variable-or-parameter 
	   variable-or-parameter))))
    (when (variable-p variable-or-parameter)
      (change-slot-value variable-or-parameter 'simulation-details 
			 (simulation-details variable-or-parameter)))
    (values nil t)))

;; Note that simulation-info?  will be nil if the variable or parameter is not
;; being simulated.



(defun remove-simulation-info-from-variable-or-parameter (variable-or-parameter)
  (let ((simulation-info? (simulation-info? variable-or-parameter)))
    (when simulation-info?
      (remove-variable-from-simulation variable-or-parameter)
      (reclaim-simulation-info simulation-info?)
      (setf (simulation-info? variable-or-parameter) nil))))



(def-frame-note-writer more-than-one-simulation-specifier-for-variable
		       (dummy-for-particulars)
  dummy-for-particulars
  (twrite-string 
    "this variable has more than one simulation specifier"))

;; Improve so that particulars include at least what kind of simulation specifiers
;; the variable has so that this can be put into the note!





(defun get-category-info-given-simulation-info (simulation-info)
  (cond
    ((specific-formula? simulation-info)
     (let* ((simulation-subtable (specific-formula? simulation-info))
	    (info-without-text 
	      (car (simulation-formulas? simulation-subtable)))
	    (category (first info-without-text))
	    (initial-value? (third info-without-text))
	    (time-increment? (time-increment-for-update? simulation-subtable)))
       (values category initial-value? time-increment?)))
    ((generic-formula? simulation-info)
     (let* ((generic-formula? (generic-formula? simulation-info))
	    (initial-value?
	      (simulation-formula-initial-value? generic-formula?))
	    (time-increment? 
	      (simulation-formula-time-increment? generic-formula?)))
       (values
	 (simulation-formula-category generic-formula?)
	 (if (consp initial-value?)
	     'use-initial-value-expression-in-generic-simulation-formula
	     initial-value?)
	 time-increment?)))
    ((external-simulation-definition? simulation-info)
     (values 'external nil nil))))



(defun get-simulation-specifier-to-use (variable)
  (let ((simulation-info? (simulation-info? variable)))
    (when simulation-info?
      (or (specific-formula? simulation-info?)
	  (generic-formula? simulation-info?)
	  (external-simulation-definition? simulation-info?)))))

(defun get-formula-focal-entity-for-variable (variable)
  (let ((simulation-info? (simulation-info? variable)))
    (when simulation-info?
      (generic-formula-focal-entity? simulation-info?))))



;;; The slot putter for simulation-formulas? installs formulas
;;; in the simulation-subtable.  The value is of the form
;;; (simulation-category simulation-expression initial-value).
;;; If simulation-expression is nil, then the variable's simulation status
;;; is updated according to applicable generic simulation formulas, if any.

(def-slot-putter simulation-formulas? 
		 (simulation-subtable formulas-and-info? initializing?)

  ;; In the style of the put-NEW-box-translation-and-text-slot-value method
  ;; for rule:  (MHD 7/1/91)
  (when (and initializing?
	     (not (compilations-up-to-date-p simulation-subtable))
	     loading-kb-p)
    (reclaim-slot-value (car formulas-and-info?))
    (setf (car formulas-and-info?) no-value)
    (note-frame-with-compilation-removed simulation-subtable)
    (update-frame-status
      simulation-subtable 'incomplete initializing?))

  (let ((variable? (parent-variable simulation-subtable)))
    (setf (simulation-formulas? simulation-subtable) formulas-and-info?)
    (let* ((info-without-text (car formulas-and-info?))
	   (simulation-expression? (second info-without-text)))
      (when variable?
	(cond 
	  ((null simulation-expression?)
	   (put-specific-simulation-formula-into-variable-or-parameter
	     variable? nil))
	  (t
	   (put-specific-simulation-formula-into-variable-or-parameter
	     variable? simulation-subtable)))
	(update-runtime-structures-according-to-edit variable?))))

  (simulation-formulas? simulation-subtable))

;; The slot value compiler for specific-simulation-formulas? is in GRAMMAR2.



(def-slot-putter parent-variable (simulation-subtable parent-variable)
  (setf (parent-variable simulation-subtable) parent-variable)
  (change-slot-value simulation-subtable 'simulation-formulas?
		     (simulation-formulas? simulation-subtable)))
 
;; This is necessary when loading a kb so that the variable gets installed 
;; correctly.  Note that it is always ok to call change-slot-value with 
;; the existing value (the existing value is not reclaimed in this case.





;;;; Installation for Connections

(def-slot-putter connection-style (connection value initializing?)
  (setf (connection-style connection) value)
  (unless initializing?
    (let* ((connection-for-connection-frame
	     (connection-for-this-connection-frame connection))
	   (output-end-object?
	     (output-end-object connection-for-connection-frame))
	   (workspace?
	     (when output-end-object?
	       (superblock? output-end-object?))))
      (update-connection-images 
	t workspace? connection-for-connection-frame)
      (if (eq value 'orthogonal)
	  (change-connection-attribute 
	    connection-for-connection-frame 'connection-style nil)
	  (change-connection-attribute 
	    connection-for-connection-frame 'connection-style value))
       (when (and g2-has-v5-mode-windows-p
		 (not ws-protocol-handle-moves-from-edge-change-p))
	 (send-ws-representations-item-change-macro
	   connection-for-connection-frame
	   (allocate-evaluation-structure-inline
	     'attribute-name 'connection-style
	     'new-value value))
	 (send-ws-representations-connection-moved connection-for-connection-frame))
      (update-connection-images 
	nil workspace? connection-for-connection-frame)))
  value)

;; Output-end-object?  may be nil here when this is called from
;; make-new-connection-frame-for-connection from make-stub.



(defun add-or-delete-subworkspace-connection-post
       (connection-post-set connection-post delete-instead?)
  (if delete-instead?
      (delete-from-set connection-post-set connection-post slot-value)
      (add-to-set connection-post-set connection-post slot-value))
  connection-post-set)



;;; Install-connection-posts-after-loading-1 is called from the post loading
;;; function install-connection-posts-after-loading.

(defun install-connection-posts-after-loading-1 ()
  (loop for connection-post being each class-instance of 'connection-post
	do (handle-connection-post-addition-or-removal-as-subblock-1
	     connection-post nil)))



;;;; Form Analyzer for Consistency Checking


;;; Analyze-compiled-form takes as arguments a form, an alist, and constraints.
;;; It analyzes the form recursively, binding names encountered in let forms on
;;; the alist.  It is thus similar to the runtime evaluators.  However, rather
;;; than evaluating data, analyze-compiled-form checks the consistency of the
;;; form against the rest of the knowledge base.  It detects problems such as
;;; missing instances, missing class definitions, missing attributes, and also
;;; type mismatches.  The side effects of analyze-compiled-form are putting up
;;; frame notes for errors and noting all names encountered in the property
;;; compiled-items-referring-to-this-name.

;;; When loading a kb, the analyze functions are disabled (see checks for 
;;; loading-kb-p).  Rather, the post loading function
;;; analyze-compiled-items-after-loading is called after loading to do
;;; the analysis.  This avoids some extra work although it is not really
;;; necessary since the analyze functions are fast.

;;; Note that currently, analyze-compiled-form does not change the status of
;;; the frame being analyzed.

;;; Note that analysis is not done for old rules.


;;; Check-kbs-for-name-inconsistencies (in module CHECK-KBS) is an automated
;;; test facility for the consistency analyzer mechanism.  See CHECK-KBS for
;;; more details.



;; Notes

;; As mentioned above, name consistency checking is disabled when loading a kb
;; and the checking is done afterward by the post loading function
;; analyze-compiled-items-after-loading.  There is no such mechanism for when
;; clearing a kb, however.  Thus, the consistency checking functions could be
;; called many times redundantly when a kb is cleared (or when a large workspace
;; is deleted).  It turns out though that the time taken by the consistency
;; checking functions when clearing a kb is relatively small.  Thus, there is no
;; problem.  If this ever becomes a problem, consider disabling checking (except
;; for compiled items that were analyzed in order to clear properties) when
;; clearing a kb.  Another way to improve speed is to cache how the name is used
;; in a compiled item along with the name in the
;; compiled-items-referring-to-this-name.  It is certainly possible to cache,
;; for example, the fact that x1 is used as the name of an instance, that pump
;; is used as the name of a class, and that level is used as the name of an
;; attribute.  With this information, complete analysis is usually not
;; necessary, unless the compiled item itself is being edited.  The only
;; disadvantage of doing this caching is that it would take up some more memory.



;; To Do

;; Note that analyze-compiled-form currently returns nothing useful.  It could
;; return constraint info about the form.

;; Put most of what is in the spec into this documentation!

;; Document when analyze... is called, how incremental mechanism works.
;; Class method, called from slot putters, analyze-compiled-items ...
;; add-as-item-referring-to-name?, delete-as-item-referring-to-name?
;; the fact that clean up methods or slot reclaimers must set the
;; slots to nil so that items are deleted from name properties when
;; the items are deleted (otherwise data corruption results).

;; Use templates!  Make templates for all functions.
;; type info comes from templates,  analyze according to template
;; Check eval for what the currently valid data types are.



;;; The defvar `post-kb-loading-consistency-analysis' is bound to T when
;;; running the consistency analysis deffered due to kb load.

(defvar post-kb-loading-consistency-analysis nil)


(defun reclaim-installation-list-function (list)
  (reclaim-installation-list-macro list))

(def-kb-specific-property-name compiled-items-referring-to-this-name
			       reclaim-installation-list-function)

;; Compiled-items-referring-to-this-name is similar to
;; frames-referring-to-this-name.  Consider merging or getting rid of one or the
;; other.

(defun compiled-items-referring-to-this-name-function (name)
  (compiled-items-referring-to-this-name name))




;;; The function `do-consistency-analysis-work-on-subframe-overrides' is
;;; called from the process-default-override code to force implementation
;;; of subframe overrides when loading order delays the definition of the
;;; subframe class.

(defun do-consistency-analysis-work-on-subframe-overrides
    (class-definition class-of-subframe)
  (add-to-set (compiled-items-referring-to-this-name class-of-subframe)
	      class-definition installation)
  (add-to-frame-note-particulars-list-if-necessary
    class-of-subframe 'undefined-classes class-definition))



;;; `Analyze-for-consistency' is a method on blocks.  See
;;; define-analyze-for-consistency and analyze-for-consistency-in-progress below
;;; for futher discussion.  These methods are never defined directly.

(def-generic-method analyze-for-consistency
		    (block 
		      add-as-item-referring-to-name?
		      delete-as-item-referring-to-name?))



;;; An `analyze-for-consistency-in-progress' dynamic extent is established when
;;; ever a frame is being revisiteding its usage of names refering to other
;;; frames.  The frame being analyzed is bound to
;;; `compiled-item-being-analyzed'.  There are three modes of analysis:
;;;   1. Registration of the names a frame uses.
;;;   2. Removing the registration of the names a frame uses.
;;;   3. Revisiting a frame when the definition of a name it uses changes.

;;; `Add-as-item-refering-to-name?' is bound to true when in mode 1, otherwise
;;; it is bound to false.  `Delete-as-item-referring-to-name?' is bound to true
;;; with in mode 2. otherwise it is bound to false.  If both are bound to false
;;; then we are in mode 3.

;;; The actually binding of these three variables is a little scattered.  The
;;; two flags are bound in the methods created by
;;; define-analyze-for-consistency.  The frame is bound either in the body of
;;; those expansions or in the immediate subroutines of those methods.

;; - ben 2/11/90

(def-named-dynamic-extent analyze-for-consistency-in-progress (module install))

(defvar-of-named-dynamic-extent compiled-item-being-analyzed      analyze-for-consistency-in-progress)
(defvar-of-named-dynamic-extent add-as-item-referring-to-name?    analyze-for-consistency-in-progress)
(defvar-of-named-dynamic-extent delete-as-item-referring-to-name? analyze-for-consistency-in-progress)



;;; `List-of-types-to-be-analyzed' contains all the classes of items that can be
;;; analyzed.  Classes are added automatically by define-analyze-for-consistency.

(defvar list-of-types-to-be-analyzed nil)




;;; `def-named-list-of-items-with-property' lets one create a global list
;;; (using defparameter) and at the same time associate every element on
;;; the list (presumed to be a symbol) with a designated property. It was
;;; motivated by the efficency boost post-analyzer-warning-note-if-necessary,
;;; where a serial search down the list was replaced with a property lookup.
;;; The list was retained because it was used by other code.  ddm 2/25/97

(defmacro def-named-list-of-items-with-property (name-of-list property &body list)
  `(progn
     (defparameter ,name-of-list
       '(,@list))
     (loop for note in ,name-of-list
	   do (setf (,property note) t))
     ',name-of-list ))

(defmacro def-named-list-of-items-with-new-property (name-of-list new-property &body list)
  `(progn
     (def-global-property-name ,new-property)
     (def-named-list-of-items-with-property ,name-of-list ,new-property ,@list)))


(def-named-list-of-items-with-new-property list-of-stack-compiler-frame-note-types
    stack-compiler-frame-note-type-p
  compiler-errors compiler-warnings)



;;; `List-of-consistency-analysis-frame-note-types' contains all the frame note
;;; types that could be put up by analyze-compiled-form.

(def-named-list-of-items-with-new-property list-of-consistency-analysis-frame-note-types
    consistency-analysis-frame-note-type-p
  SUPERSEDED-ATTRIBUTES			;old, but still in some kbs -dkuznick, 3/17/00
  non-existent-instances
  #+mtg2 foreign-faction-instances
  undefined-classes
  undefined-attributes
  undefined-attributes-of-classes
  undefined-methods-of-classes
  non-existent-instances-of-class
  non-existent-instances-of-type
  arg-count-mismatch
  return-count-mismatch
  item-not-ok
  arg-type-mismatch
  return-type-mismatch
  non-existent-procedure-method
  specific-method-argument-conflict
  no-arg-for-method-call
  no-item-arg-for-method-call
  no-method-for-arg-count
  no-method-for-class
  method-for-class-not-okay
  item-no-longer-dependent
  item-depends-on-modified-stable-item
  incompatible-validity-interval-and-data-server
  item-depends-on-unstable-heirarchy
  item-depends-on-invalid-inlining
  item-inlineable-but-has-no-parse
  nonexistent-classes-for-export
  nonexistent-static-methods-for-export
  duplicate-class-export)



(defun delete-all-consistency-analysis-frame-notes 
       (compiled-item &optional delete-only-from-component-particulars?)
  (delete-frame-notes-of-types-in-list 
    compiled-item list-of-consistency-analysis-frame-note-types
    delete-only-from-component-particulars?))

;; Should this supress the delete if we are "adding references", at that point
;; in that mode there shouldn't be any consistency notes. - ben 9/19/91






;;;; Posting Analyzer Warning Notes



;; I moved def. for post-analyzer-warning-notes-for-generic-simulation-formulas?
;; above ahead of put-box-translation-and-text-slot-value for generic-simulation-
;; formula where it needs to be special.  (MHD 10/16/91)

(defun post-analyzer-warning-note-for-generic-simulation-formula 
       (generic-simulation-formula)
  (when post-analyzer-warning-notes-for-generic-simulation-formulas?
    (let ((add-as-item-referring-to-name? t))
      (post-analyzer-warning-note-if-necessary generic-simulation-formula))))

;; Post-analyzer-warning-note-for-generic-simulation-formula is used to avoid
;; multiple calls to post-analyzer-warning-note-if-necessary.



;;; `Post-analyzer-warning-note-if-necessary' (follows its subroutine
;;; definitions below) will send a warning note to the logbook if any of
;;; the notes on the frame that is it passed are on any of the lists of
;;; frame note types that are supposed to trigger warnings.  It is called
;;; by a plethora of functions, often in contexts where a warning would be
;;; inappropriate, transient, or redundant. These situations are checked
;;; for in an initial preamble. 


;;; `Propagate-test-outcome-via-flags' is used when a set of flags are being
;;; used to communicate the results of a set of mutually-exclusive conditions
;;; within some block. The caller needs to bind the flags. 

(defmacro propagate-test-outcome-via-flags (flag test other-flags block-name)
  `(unless ,flag
     (when ,test
       (setq ,flag t)
       (if (and ,@other-flags)
	   (return-from ,block-name))
       t )))


;;; `Analyzer-warning-note-criteria' is what it says. If any of the note-types
;;; on the frame pass any of the tests, then a warning will be posted. This
;;; is the workhorse subroutine of post-analyzer-warning-note-if-necessary.

(defmacro analyzer-warning-note-criteria (block-name)
  `(or (propagate-test-outcome-via-flags compiler-error?
	   (eq note-type 'compiler-errors)
	   (analyzer-warning?) ,block-name)
       (propagate-test-outcome-via-flags analyzer-warning?
	   (or (stack-compiler-frame-note-type-p note-type)
	       (consistency-analysis-frame-note-type-p note-type))
	   (compiler-error?) ,block-name)))



;;; When the frame note pertains to any of the individual attributes of a
;;; frame, it is stored in an alist inside the particular of a special
;;; note-type: `frame-notes-for-component-particulars', whose purpose
;;; is to serve as the collector for all such notes. (See code in Frames5,
;;; written by jra 10/95.)  The keys on the alist are forms corresponding
;;; to accessors, e.g. (CELL-ARRAY-ELEMENT 0), and the values (cadr of
;;; the alist entry) are lists that exactly mimic the structure of frame
;;; note entries at the toplevel: a symbol giving the status of the
;;; attribute, followed by a plist of note-types and particulars.

(defun scan-component-frame-notes-for-warning-criteria (component-structure)
  (let ( compiler-error?  analyzer-warning? )
    (block component-notes-scan
      (loop for (key frame-status-and-notes) in component-structure
	    do (loop for (note-type particulars)
		         on (cdr frame-status-and-notes) by #'cddr
		     do (analyzer-warning-note-criteria component-notes-scan))))
    (values compiler-error? analyzer-warning?)))


(defvar post-analyzer-warning-note? t)

(defun post-analyzer-warning-note-if-necessary (compiled-item)
  (when (and add-as-item-referring-to-name?
	     (frame-has-frame-notes-p compiled-item)
	     (not suppress-consistency-analysis-warnings-notes?))
    ;; Only post warning if actually editing item or after loading.
    ;; or when not suppressed, otherwise, too many messages could be posted.
    (let ( compiler-error?  analyzer-warning? )
      (block look-for-notes-that-prompt-a-warning
	(loop
	  for (note-type particulars)
	       on (cdr (frame-status-and-notes compiled-item)) by #'cddr
	  
	  do (or (when (eq note-type 'frame-notes-for-component-particulars)
		   (multiple-value-setq (compiler-error? analyzer-warning?)
		     (scan-component-frame-notes-for-warning-criteria particulars))
		   (if (and compiler-error? analyzer-warning?) (return)))

		 (analyzer-warning-note-criteria look-for-notes-that-prompt-a-warning))))

      (cond ((and compiler-error? analyzer-warning?)
	     (post-compiler-and-analyzer-warning-note compiled-item))
	    (compiler-error?
	     (let ((*current-computation-frame* compiled-item))
	       (post-compiler-warning-note)))
	    (analyzer-warning?
	     (if collecting-procedures-to-warn-about-p
		 (gensym-push (gensym-cons compiled-item
					   (copy-frame-serial-number
					     (frame-serial-number compiled-item)))
			      procedures-to-warn-about-p)
		 (post-analyzer-warning-note compiled-item))))))
  nil)

(defun post-collected-warnings (collected-items-with-warnings-alist)
  (loop for a in collected-items-with-warnings-alist
	for (message-type . item-list) = a
	do
    (if (null (cdr item-list))
	(post-warning-note (car item-list) message-type)
	(with-user-notification ()
	  (tformat
	    (case message-type
	      (compiler-and-analyzer
	       "There were problems compiling the following-items, which have inconsistencies: ")
	      (analyzer
	       "Inconsistencies were detected in the following items: ")
	      (compiler
	       "There were problems compiling the following items: ")))
	  (setq item-list (sort-list item-list #'string<w #'get-or-make-up-designation-for-block))
	  (setf (cdr a) item-list)
	  (loop with length = (length item-list)
		for firstp = t then nil
		for i from 1
		for item in item-list
		do
	    (unless firstp
	      (cond ((<f i length)
		     (tformat ", "))
		    ((=f length 2)
		     (tformat " and "))
		    (t
		     (tformat ", and "))))
	    (tformat "~NF" item))
	  (tformat "; see their notes for details.")))))

(defun do-tw-notification (compiled-item message-type)
  (with-user-notification ()
    (tformat
     (case message-type
       (compiler-and-analyzer
        "There were problems compiling ~NF, and it has inconsistencies")
       (analyzer
        "Inconsistencies were detected in ~NF")
       (compiler
        "There were problems compiling ~NF"))
     compiled-item)
    (cond ((or send-logbook-messages-to-console-p
               ;; GENSYMCID-965: __GCC-EVAL-PROC-TMP inconsistencies were detected at startup
               ;; When G2 change the `compiled item 's content with a kb instruction,
               ;; for example,change the procedure text by kb codes
               ;; `change the text of fn to "proc-name() begin call non-exists(); end";'
               ;; The frame notes should be printed out to help user locate the problem.
               current-computation-instance)
           (tformat ": ")
           (twrite-frame-notes compiled-item t))
          (t
           (tformat "; see its notes for details.")))))

(defun post-warning-note (compiled-item message-type)
  (if (and collecting-warnings-p (not send-logbook-messages-to-console-p))
      (collect-warning compiled-item message-type)
    (do-tw-notification compiled-item message-type)))

(defun post-compiler-and-analyzer-warning-note (compiled-item)
  (when (or post-analyzer-warning-note? post-compiler-warning-note?)
    (post-warning-note compiled-item 'compiler-and-analyzer)))

(defun post-analyzer-warning-note (compiled-item)
  (when post-analyzer-warning-note?
    (post-warning-note compiled-item 'analyzer))
  #+development
  (when break-if-name-inconsistency?
    (cerror "Continue" "Name inconsistency")))

(defun post-compiler-warning-note ()
  (when post-compiler-warning-note?
    (post-warning-note *current-computation-frame* 'compiler)))

;; This now says "See its notes for details" instead of "See frame notes for
;; details".  This fix was long overdue.  What we internally call "frame notes"
;; have always been "notes" to users -- e.g. the slot that appears in tables is
;; called "notes", the inspect command is "show ... every item with notes", etc.
;; "Frame notes" never appears to users except in this and similar notifications
;; from the compiler. (MHD 2/22/91)









(def-frame-note-writer non-existent-instances (non-existent-instance-names)
  (write-frame-notes-for-names
    non-existent-instance-names 
    "the item " "the items " " does not exist" " do not exist"))

(def-frame-note-writer undefined-classes (undefined-classes)
  (write-frame-notes-for-names
    undefined-classes 
    "the class " "the classes " " is not defined" " are not defined"))

#+mtg2
(def-frame-note-writer foreign-faction-instances (foreign-faction-instance-names)
  (write-frame-notes-for-names
    foreign-faction-instance-names 
    "the item " "the items " " belongs to another faction" " belong to another faction"))


;;; The parameters `frame-note-for-superseded-attributes-1 and 2' concatenate a
;;; long text string for the superseded-attributes frame note.  It was necessary
;;; to use concatenation because vms platforms do not support literal text
;;; strings of over 200 characters.

(defparameter frame-note-for-superseded-attributes-1
  (concatenate
    'string
    " has been superseded.  G2 will automatically process the statement containing its reference, but the "
    "result should be examined and the statement should be brought up to date before further kb development.  "
    "Please see the release notes."))

;(defparameter frame-note-for-superseded-attributes-2
;  (concatenate
;    'string
;    " have been superseded.  G2 will automatically process the statements containing the references, but the "
;    "results should be examined and the statements should be brought up to date before further kb development.  "
;    "Please see the release notes."))

;; Superseded-attributes is no longer implemented as a frame-note.  See the
;; function compiler-warning-if-superseded-attribute.  - cpm, 9/9/94

;(def-frame-note-writer superseded-attributes (superseded-attributes)
;  (temporary-progn (12 1 94 "Gretchen, superseded-attributes frame-note ~
;                             writer needs revision.")
;      (write-frame-notes-for-names
;        superseded-attributes
;        "the attribute " "the attributes "
;        frame-note-for-superseded-attributes-1
;        frame-note-for-superseded-attributes-2)))


(def-frame-note-writer undefined-attributes (undefined-attributes)
  (write-frame-notes-for-names
    undefined-attributes 
    "the attribute " "the attributes " " is not defined" " are not defined"))

(def-frame-note-writer undefined-attributes-of-classes 
		       (undefined-attributes-and-classes)
  (loop for (class-and-attributes . rest-of-class-entries) 
	    = undefined-attributes-and-classes
				  then rest-of-class-entries
	do
    (write-frame-notes-for-names
      (cdr class-and-attributes)
      "the attribute " "the attributes " " is not defined" " are not defined")
    (twrite-string " for the class ")
    (twrite (car class-and-attributes))
    (if (null rest-of-class-entries)
	(return (values))
	(twrite-string ", "))))


(def-frame-note-writer undefined-methods-of-classes 
		       (undefined-methods-and-classes)
  (loop for (class-and-methods . rest-of-class-entries) 
	    = undefined-methods-and-classes
				  then rest-of-class-entries
	do
    (write-frame-notes-for-names
      (cdr class-and-methods)
      "the method " "the methods" " is not defined" " are not defined")
    (twrite-string " for the class ")
    (twrite (car class-and-methods))
    (if (null rest-of-class-entries)
	(return (values))
	(twrite-string ", "))))

(def-frame-note-writer non-existent-instances-of-class (undefined-instances-of-classes)
  (loop for ((class . names) . rest-of-entries) 
	    = undefined-instances-of-classes
	    then rest-of-entries
	do
    (write-frame-notes-for-names
      names 
      "the name " 
      "the names " 
      " does not exist as an instance of the class " 
      " do not exist as instances of the class ")
    (twrite class)
    (if (null rest-of-entries) 
	(return nil)
	(twrite-string ", "))))

(def-frame-note-writer non-existent-instances-of-type
    (undefined-instances-of-types)
  (loop for ((type . names) . rest-of-entries) 
	    = undefined-instances-of-types
	    then rest-of-entries
	do
    (write-frame-notes-for-names
      names 
      "the name " 
      "the names " 
      " does not exist as an instance of the type "
      " do not exist as instances of the type ")
    (write-type-specification type)
    (if (null rest-of-entries) 
	(return nil)
	(twrite-string ", "))))


(def-frame-note-writer non-existent-procedure-method
		       (dummy-for-particulars)
  dummy-for-particulars
  (twrite-string 
    "there is no method-declaration defined with this name"))

(def-frame-note-writer specific-method-argument-conflict
		       (dummy-for-particulars specific-method)
  (declare (ignore dummy-for-particulars))
  (let ((method-class? (procedure-method-class specific-method))
	(arg-count? (argument-count specific-method)))
    (cond
      ((and method-class? arg-count?)
       (tformat
	 "there is more than one method defined for the ~
          class ~a and that has ~a ~a"
	 method-class? arg-count?
	 (if (>f arg-count? 1) "arguments" "argument")))
       (t
	(tformat
	  "there is more than one method defined with the ~
           same class for the first argument and with the same number of ~
           arguments")))))

(def-frame-note-writer no-arg-for-method-call (names)
  (write-frame-notes-for-names
    names
    "the method "
    "the methods "
    " is being called with no arguments"
    " are being called with no arguments"))

(def-frame-note-writer no-item-arg-for-method-call
    (method-and-first-arg-types-list)
  (loop for ((method . first-arg-types) . rest-of-entries) 
	    = method-and-first-arg-types-list
	    then rest-of-entries
	do
    (tformat
      "the method ~NN requires a first argument of class item, but ~
       is being given "
      method)
    (cond ((null (cdr-of-cons first-arg-types))
	   (tformat "a first argument of type ~NT"
		    (car-of-cons first-arg-types)))
	  (t
	   (twrite-string "first arguments of type ")
	   (write-list-in-chicago-style-given-format
	     first-arg-types "and" "~NT")))
    (if (null rest-of-entries) 
	(return nil)
	(twrite-string "; "))))


;;; The frame note writers for `no-method-for-arg-count' print warnings about
;;; incorrect numbers given to a method for a class.  Note that methods of this
;;; name may be defined for the class, but not with the given argument count.

;;; The format of the frame note particulars is
;;;   (((<class> . <arg-count>) . <methods>) ...)

(def-frame-note-writer no-method-for-arg-count (method-info)
  (loop for (((class . arg-count) . method-list) . rest-of-list) on method-info
	do
    (tformat
      "the method~a "
      (if (null (cdr-of-cons method-list)) "" "s"))
    (write-list-in-chicago-style-given-format
      method-list "and" "~NT")
    (tformat ", with ~a argument~a," arg-count (if (=f arg-count 1) "" "s"))
    (tformat " ~a not defined for the class ~NN"
	     (if (null (cdr-of-cons method-list)) "is" "are")
	     class)
    (if (null rest-of-list) 
	(return nil)
	(twrite-string "; "))))

(def-frame-note-writer no-method-for-class (class-and-methods-list)
  (loop for ((class . methods) . rest-of-entries) 
	    = class-and-methods-list
	    then rest-of-entries
	do
    (write-frame-notes-for-names
      methods
      "the method " 
      "the methods " 
      " is not defined for the class " 
      " are not defined for the class ")
    (twrite class)
    (if (null rest-of-entries) 
	(return nil)
	(twrite-string "; "))))

(def-frame-note-writer method-for-class-not-okay (class-and-methods-list)
  (loop for ((class . methods) . rest-of-entries) 
	    = class-and-methods-list
	    then rest-of-entries
	do
    (write-frame-notes-for-names
      methods
      "the method " 
      "the methods " 
      " defined for the class " 
      " defined for the class ")
    (if (null(cdr-of-cons methods))
	(tformat "~a is not OK" class)
	(tformat "~a are not OK" class))
    (if (null rest-of-entries) 
	(return nil)
	(twrite-string "; "))))



(defun write-frame-notes-for-names 
       (names preamble-singular-string preamble-plural-string
	singular-string plural-string)
  (let ((singular? (null (cdr names))))
    (twrite-string 
      (if singular? preamble-singular-string preamble-plural-string))
    (loop with limit = (if abbreviate-frame-notes-p 3 most-positive-fixnum)
	  as (name . rest-of-names) = names
		   then rest-of-names
	  for index from 1 to limit
	  do
      (if (class-qualified-name-list-p name)
	  (write-name-or-class-qualified-name name)
	  (twrite name))
      (when (or (null rest-of-names)
		(=f index limit))
	(when rest-of-names
	  (twrite-string " (and others, as well)"))
	(twrite-string (if singular? singular-string plural-string))
	(return nil))
      (twrite-string
	(cond
	  ((and (cdr rest-of-names)
		(<f index (1-f limit)))
	   ", ")
	  ((cddr names) ", and ")
	  (t " and "))))))




;;; The frame notes arg-count-mismatch and return-count-mismatch are used to
;;; represent bad calls or start actions to procedures,
;;; remote-procedure-declarations, and functions.

(def-frame-note-writer arg-count-mismatch (names-and-counts)
  (twrite-count-mismatch names-and-counts t))

(def-frame-note-writer return-count-mismatch (names-and-counts)
  (twrite-count-mismatch names-and-counts nil))




;;; The function `twrite-count-mismatch' is used to write frame note particulars
;;; for the frame notes arg-count-mismatch and return-count-mismatch.

(defun twrite-count-mismatch (names-and-counts args?)
  (loop for ((name defined-count . supplied-count-list) . rest-of-list)
	    on names-and-counts
	do
    (tformat (if args?
		 "~a requires ~a argument~a but was given "
		 "~a returns ~a value~a but was expected to return ")
	     name defined-count
	     (if (=f defined-count 1) "" "s"))
    (write-list-in-chicago-style supplied-count-list "and")
    (tformat
      (if args? " argument~a" " value~a")
      (if (and (=f (length supplied-count-list) 1)
	       (=f (first supplied-count-list) 1))
	  ""
	  "s"))
	while rest-of-list do
    (twrite-string
      (cond ((cdr rest-of-list) ", ")
	    ((cddr names-and-counts) ", and ")
	    (t " and ")))))

(def-frame-note-writer item-depends-on-unstable-heirarchy (stability-info-list)
  (let ((class-stability-items nil)
	(method-stability-items nil))
    (loop for info-item in stability-info-list
	  do
      (cond ((null (cdr-of-cons info-item))
	     (installation-push info-item class-stability-items))
	    (t
	     (installation-push info-item method-stability-items))))
    (when class-stability-items
      (tformat 
	"the class~a "
	(if (null (cdr-of-cons class-stability-items)) "" "es"))
      (loop for ((class-name) . rest-of-list) on class-stability-items
	    do
	(tformat "~a" class-name)
	(if (null rest-of-list) 
	    (return nil)
	    (twrite-string "; "))))
    (when method-stability-items 
      (tformat 
	"the method~a "
	(if (null (cdr-of-cons method-stability-items)) "" "s"))
      (loop for ((method-name focus-class arg-count) . rest-of-list) on method-stability-items
	    do
	(cond (arg-count
	       (tformat "~a, with ~a argument~a, " method-name arg-count (if (=f arg-count 1) "" "s")))
	      (t
	       (tformat "~a" method-name)))
	(tformat " ~NN depends upon a stable heirarchy which is no longer stable "
		 focus-class)
	(if (null rest-of-list) 
	    (return nil)
	    (twrite-string "; "))))))


(def-frame-note-writer item-depends-on-invalid-inlining (stability-info-list)
  (when stability-info-list
    (let ((plural-string (if (null (cdr-of-cons stability-info-list)) "" "s")))
      (cond ((loop for (focus-class?) in stability-info-list
		   always focus-class?)
	     (tformat "the method~a " plural-string))
	    ((loop for (focus-class?) in stability-info-list
		   never focus-class?)
	     (tformat "the procedure~a " plural-string))
	    (t
	     (tformat "the methods and procedures "))))
    (loop for ((focus-class? method-name arg-count reason) . rest-of-list)
	    on stability-info-list
	  do
      (write-name-denotation-components method-name focus-class?)
      (when arg-count
	(tformat ", with ~a argument~a," arg-count (if (=f arg-count 1) "" "s")))
      (twrite-string (if (eq reason :cross-module-violation)
			 " can't be inlined because of a cross-module violation "
			 " is no longer the same as what was inlined "))
      (if (null rest-of-list) 
	  (return nil)
	  (twrite-string "; ")))))

(def-frame-note-writer item-inlineable-but-has-no-parse (particulars)
  (declare (ignore particulars))
  (twrite-string
    #w"this item needs to be recompiled to generate data needed for inlining")
  )



;;; The frame note writer for `item-not-ok' is used to write frame notes about
;;; references to bad or incomplete items.

;; Currently, only used for procedures, but we should change this.  - cpm, jra
;; 12/29/92

(def-frame-note-writer item-not-ok (names)
  (write-frame-notes-for-names
    names
    "the item " "the items " " is not OK" " are not OK"))




;;; The frame note writers for `arg-type-mismatch' and `return-type-mismatch'
;;; print warnings about incorrect types given as arguments and incorrect types
;;; expected from procedures, remote-procedure-declarations, and functions.

;;; The format of the frame note particulars is
;;;   (((<name> . <which>) <defined-type> . (<supplied-type> ...)) ...)
;;; where which is the number (e.g. 1 for first) argument or return value that
;;; this warning is about.

(def-frame-note-writer arg-type-mismatch (names-and-types)
  (twrite-type-mismatch names-and-types t))

(def-frame-note-writer return-type-mismatch (names-and-types)
  (twrite-type-mismatch names-and-types nil))




;;; The function `twrite-type-mismatch' is used by the arg-type-mismatch and
;;; return-type-mismatch frame note writers, and writes messages the wrong types
;;; of values being passed to and expected from function, procedure, and
;;; remote-procedure-declaration calls and starts.

(defun twrite-type-mismatch (names-and-types args?)
  (loop for (((name . which) defined-type . supplied-type-list) . rest-of-list)
	    on names-and-types
	do
    (tformat
      (if args?
	  "argument ~a of ~a requires values of type ~NT but was given values ~
           of type~a "
	  "return value ~a of ~a provides values of type ~NT but was expected ~
           to provide values of type~a ")
      which name defined-type
      (if (=f (length supplied-type-list) 1) "" "s"))
    (write-list-in-chicago-style-given-format supplied-type-list "and" "~NT")
	while rest-of-list do
    (twrite-string
      (cond ((cdr rest-of-list) ", ")
	    ((cddr names-and-types) ", and ")
	    (t " and ")))))



;(def-frame-note-writer undefined-class-qualified-attributes-of-classes
;                       (undefined-class-qualified-attributes-and-classes)
;  (loop for (class-and-qualified-attributes . rest-of-entries) 
;            = undefined-class-qualified-attributes-and-classes
;            then rest-of-entries
;        do
;    (write-frame-notes-for-names
;      (cdr class-and-qualified-attributes)
;      "the attribute " "the attributes " " is not defined" " are not defined")
;    (twrite-string " for the class ")
;    (twrite (car class-and-qualified-attributes))
;    (if (null rest-of-entries)
;        (return (values))
;        (twrite-string ", "))))



;;; The frame note writers for `item-no-longer-dependent' and
;;; `item-depends-on-modified-stable-item' are used when a change has been made
;;; to a stable or dependent item, requiring the dependent item to be
;;; recompiled.

(def-frame-note-writer item-no-longer-dependent (dummy-for-particulars)
  dummy-for-particulars
  (twrite-string 
    "this item needs to be recompiled because it is no longer dependent"))


(def-frame-note-writer item-depends-on-modified-stable-item (names)
  (write-frame-notes-for-names
    names
    "this item needs to be recompiled because it depends on the stable item "
    "this item needs to be recompiled because it depends on the stable items "
    " which has been modified"
    " which have been modified"))




(defmacro ok-to-do-name-consistency-analysis? ()
  `(not loading-kb-p))



;;; `Analyze-compiled-items-after-loading-1' is called from the post loading
;;; function analyze-compiled-items-after-loading.

(defun analyze-compiled-items-after-loading-1 ()
  (let ((post-analyzer-warning-notes-for-generic-simulation-formulas? t)
	(post-kb-loading-consistency-analysis t))
    ;; We now have to do this for every block!
    (loop for item being each class-instance of 'block doing
      (assert-consistency-analysis-if-allowed item))))

;;    (loop for type-to-be-analyzed in list-of-types-to-be-analyzed doing)
;;      (loop for item being each class-instance of type-to-be-analyzed doing)




;;; The function `analyze-compiled-items-for-consistency' runs consistency
;;; analysis in the "check" mode on every frame in the KB which refers to
;;; or used to refer to the given name.

(defun analyze-compiled-items-for-consistency (name)
  (when (ok-to-do-name-consistency-analysis?)
    (let ((compiled-items-referring-to-this-name
            (compiled-items-referring-to-this-name name)))
      (loop for item in compiled-items-referring-to-this-name doing
        (cond ((frame-in-use-p item)
	       (check-consistency-analysis item))
	      (t
	       #+development
	       (cerror
		 "continue"
		 "Consistency analysis was attempted on a recycled frame, aka \"the clear kb problem\".")))))))

;; See the documentation on define-analyze-for-consistency to understand how
;; easy it is to corrupt these data structures. - ben  (12/17/90)




;;; `Define-analyze-for-consistency' is used to create the analyze-for-
;;; consistency method of a frame.  This method is responsible for maintaining
;;; those frame notes that appear on this frame that note problems with the use
;;; of names.  These frame note types must be enumerated in
;;; `list-of-consistency-analysis-frame-note-types'.

;;; The method is called in one of four modes:
;;;  1. To analyze the frame when a slot has changed or is initialized,
;;;  2. To analyze the frame when a name it references has changed,
;;;  3. To reclaim storage built in mode 1 or 2 when the slot is deleted.
;;;  4. Do nothing mode.
;;; Do nothing mode is provided to allow the analyze method to be disabled
;;; during loading.

;;; This method is called at these times:
;;;  1. Once on each frame after kb load by a post loading function.
;;;  2. Twice by slot putters upon changes to slots in the frame;
;;;     once for the old slot value, to remove it,
;;;     once for the new slot value, to install it.
;;;  3. The cleanup method of the frame must set the slots to
;;;     nil that contain names so their slot putters can remove
;;;     name registrations.
;;;  4. By all code that changes the definitions of names in a way
;;;     known to be of interest to some analyze method.

;;; Many of these calls are the responsiblity of the author of the new class or
;;; slot.  Failure to include one of these will corrupt the name registry.
;;; Failures of this nature are sometimes uncovered by clear kb.

;;; All slots that contain names should have a slot putter.  This slot putter
;;; should do step 2.  The cleanup method for the frame should use change slot
;;; value on those slots until they have no names in them.  That lets the slot
;;; putter clean them up.  Do not attempt to enhance the performance of your
;;; analyze method with knowledge of which slot it is working on (notice that
;;; compiled-items-referring-to-this-name is a set).

;;; Before implementing a define-analyze-for-consistency method you will want to
;;; inspect the existing examples.  They are very stylized.  The method may
;;; infer what mode it is called in from the bindings of a number of specials.
;;; The primitives these methods are built out of depend on these bindings.
;;; Some of these binds are made by the method.  These bindings include:
;;;    add-as-item-referring-to-name?
;;;    delete-as-item-referring-to-name?
;;;    compiled-item-being-analyzed
;;;    ok-to-do-name-consistency-analyzsis?

;;; The primitives for implementing a consistency method include these
;;; routines.  At the lowest level a frame registers its interest in a name
;;; using
;;;    add-or-delete-as-item-referring-to-name 
;;; The following routines do simple checks on names.
;;;    check-attribute-name
;;;    check-for-undefined-class 
;;;    check-for-undefined-attribute-of-class
;;;    as well as some others...
;;; The following routines check more complex S-expressions.
;;;    analyze-compiled-form 
;;;    analyze-formula-for-consistency
;;;    as well as some others...
;;; If the method is updating the frame notes it usually calls `delete-all-
;;; consistency-analysis-frame-notes' so it can start with a clean slate.  It
;;; calls 'post-analyzer-warning-note-if-necessary' just prior to finishing
;;; reporting on the logbook if any problems were uncovered.

;; - ben (12/17/90)

;;; The class-method defined here now allows deferral of consistency-analysis in
;;; some cases.  Refer to defer-consistency-analysis-of-item-p and
;;; defer-some-consistency-analysis (currently in DEFINITIONS).

;; - cpm, 9/23/93

(defmacro define-analyze-for-consistency (class &body forms)
  `(progn
     (pushnew ',class list-of-types-to-be-analyzed)
     
     (def-class-method analyze-for-consistency
	 (,class 
	    add-as-item-referring-to-name?
	    delete-as-item-referring-to-name?)

       (cond ((defer-consistency-analysis-of-item-p
		  ,class add-as-item-referring-to-name?
		  delete-as-item-referring-to-name?)
	      (defer-consistency-analysis-of-item ,class))
	     (t
	      (with-named-dynamic-extent analyze-for-consistency-in-progress ()
		,@forms))))))

;; It isn't apparent, to me, why compiled-item-being-analyzed isn't bound at
;; this point, it is bound apparently sooner or later in the direct subroutines
;; of this method.  - ben 2/11/91.



;;; The function `analyze-consistency-of-block' does the part of consistency
;;; analysis which handles the object-configuration of any block.  It should
;;; be called from within all analyze-for-consistency methods.

(def-substitution-macro analyze-consistency-of-block (block)
  (let ((object-configuration? (object-configuration block)))
    (when object-configuration?
      (map-over-external-names-in-object-configuration
	#'check-undefined-instances-of-class object-configuration?))))




;;; The analyze-for-consistency method for `block' grovels through the object
;;; configuration slot looking for image-names, frame-style-names, and procedure
;;; names.

(define-analyze-for-consistency block
  (when (ok-to-do-name-consistency-analysis?)
    (delete-all-consistency-analysis-frame-notes block)
    (let ((compiled-item-being-analyzed block))
      (analyze-consistency-of-block block))
    (post-analyzer-warning-note-if-necessary block)))

;; It is unfortunate that we now have to scan all blocks in the KB after
;; loading.  But, that is already done by `identify-all-permanent-blocks', for
;; example, so our scan may not take much additional time.  Still, the cost
;; could be reduced to a minimum if we kept an explicit list of all blocks
;; which have non-NIL object configs. -fmw, 2/1/94



;;; The analyze-for-consistency for `class-definition', at a minimum, analyzes
;;; the areas covered by the analyze-for-consistency forms for
;;; object-definition, connection-definition, and message-definition:
;;; connections, images mentioned in the icon description, and class names in
;;; attribute descriptions and default overrides.


(define-analyze-for-consistency class-definition
  (when (ok-to-do-name-consistency-analysis?)
    (delete-all-consistency-analysis-frame-notes class-definition)

    (let* ((compiled-item-being-analyzed class-definition)
	   (class-name? (name-of-defined-class class-definition))
	   (class-description? (class-description class-name?))
	   (default-overrides (default-overrides class-definition))
	   (connections?
	     (if (frame-of-class-p class-definition 'object-definition)
		 (connections-for-class? class-definition)
		 (let ((stubs-for-class-override?
			 (car (member
				'stubs-for-class default-overrides
				:test 'car-eq))))
		   (and stubs-for-class-override?
			(cadr-of-cons stubs-for-class-override?)))))
	   (icon-description?
	     (icon-description-for-class? class-definition)))

      (unless (symbolp connections?) ; none or nil
	(loop for stub-spec in (cdr connections?)
	      as connection-class = (second stub-spec)
	      do
	  (check-for-undefined-class connection-class)))

      ;; Check for any images mentioned in the icon description.
      (loop with any? = nil
	    with default-variables
	      = (cdr (get-variable-specification-if-any   
		       icon-description?))
	    for drawing-element in (cddr icon-description?)
	    as image-name? = (and (image-drawing-element-p drawing-element)
 				  (evaluating-icon-elements
				    (nil nil default-variables nil)
				    (simple-eval-for-icon
				      (image-drawing-element-image-name
					drawing-element))))
	    when (and image-name?
		      #-development
		      (symbolp image-name?))
	      do
		#+development
		(unless (symbolp image-name?)
		  (cerror
		    "continue"
		    "Invalid image-name in icon-description. Talk to pbk."))
		(check-undefined-instances-of-class image-name? 'image-definition)
		 (setq any? t)
            finally
              ;; If we had any, assume they may have changed, and erase and draw
              ;; them all.
	      (when any?
		(flush-icon-caches-and-redraw-instances class-definition)))
      (let* ((background-layer (icon-background-images class-definition))
	     (image-name?
	       (and (image-drawing-element-p background-layer)
		    (second background-layer))))
	;(when (and (null image-name?) background-layer
	;	   (symbolp background-layer)
	;	   (not (gensym-color-p background-layer)))
	;  ;;notify undefined-background-color
	;  )
	(when image-name?
	  (check-undefined-instances-of-class image-name? 'image-definition))

	;; We will be called in this fashion if any name we refer to has changed
	;; meaning.  Just in case that name was our background-image,
	;; refresh the background.
	(when (and image-name?
		   (or post-kb-loading-consistency-analysis
		       ;; Do this after loading, to ensure caches.
		       (checking-for-consistency-analysis-p))
		   (not (frame-being-deleted-p class-definition)))  ; Hmm.
	  (flush-icon-caches-and-redraw-instances class-definition)))

      (loop for attribute-description in (class-specific-attributes
					   class-definition)
	    do
	(when (slot-init-form-needs-evaluation?
		(attribute-initial-value attribute-description))
	  (let* ((attribute-name (attribute-name attribute-description))
		 (attribute-type-specification
		   (attribute-type-specification attribute-description))
		 (class-type-specification?
		   (class-type-specification-p attribute-type-specification))
		 (class-type?
		   (and class-type-specification?
			(type-specification-class-function
			  attribute-type-specification)))
		 (attribute-initial-type
		   (attribute-initial-type attribute-description)))
	    (when class-type?
	      (check-for-undefined-class class-type?)
	      (when (and (classp class-type?)
			 (classp attribute-initial-type))
		(if (subclassp attribute-initial-type class-type?)
		    (delete-from-frame-note-particulars-list
		      attribute-name
		      'initial-value-class-incompatible-with-type
		      class-definition)
		    (add-to-frame-note-particulars-list-if-necessary
		      attribute-name
		      'initial-value-class-incompatible-with-type
		      class-definition))))
	    (check-for-undefined-class attribute-initial-type))))

      (let ((cons-holding-validity-interval-override?
	      (member 'validity-interval default-overrides :test 'car-eq))
	    (cons-holding-data-server-map-override?
	      (member 'data-server-map default-overrides :test 'car-eq)))
       (when (or cons-holding-validity-interval-override?
		 cons-holding-data-server-map-override?)
	 (let ((real-or-implied-validity-interval-value
		 (cond (cons-holding-validity-interval-override?
			(second (car cons-holding-validity-interval-override?)))
		       (class-description?
			(let ((slot-description?
				(slot-description-from-class
				  class-name? 'validity-interval)))
			  (and slot-description?
			       (slot-init-form slot-description?))))
		       (t (slot-init-form
			    (slot-description-from-class
			       'g2-variable 'validity-interval)))))
		(real-or-implied-data-server-map-value
		 (cond (cons-holding-data-server-map-override?
			(second (car cons-holding-data-server-map-override?)))
		       (class-description?
			(let ((slot-description?
				(slot-description-from-class
				  class-name? 'data-server-map)))
			  (and slot-description?
			       (slot-init-form slot-description?))))
		       (t (slot-init-form
			    (slot-description-from-class
			      'g2-variable 'data-server-map))))))
	   (when (eq real-or-implied-validity-interval-value 'supplied)
	     (unless (eq real-or-implied-data-server-map-value 'computation)
	       (add-frame-note
		 'incompatible-validity-interval-and-data-server
		 class-definition))))))

      (loop for override in default-overrides
	    for class-to-instantiate? = (class-to-instantiate-for-override
					  override)
	    do
	(when class-to-instantiate?
	  (check-for-undefined-class class-to-instantiate?)
	  (when (and (classp class-to-instantiate?)
		     class-description?)
	    (let* ((name-denotation (car-of-cons override))
		   (pretty-slot-name (unqualified-name name-denotation))
		   (defining-class (class-qualifier name-denotation))
		   (slot-description?
		     ;; The override may have no applicable inherited slot.
		     (slot-description-from-class
		       class-name? pretty-slot-name defining-class)))
	      (when slot-description?
		(if (class-in-attribute-conforms-to-type-p
		      slot-description? class-name? t
		      (slot-init-form slot-description?))
		    (delete-from-frame-note-particulars-list
		      name-denotation
		      'override-value-is-not-compatible
		      class-definition)
		    (add-to-frame-note-particulars-list-if-necessary
		      (copy-for-slot-value name-denotation)
		      'override-value-is-not-compatible
		      class-definition))))))))
		   
    (post-analyzer-warning-note-if-necessary class-definition)))




;;; The analyze-for-consistency method for `drawing-parameters' checks for the
;;; existance of the image-name mentioned for custom palettes.  It is called
;;; whenever the image-name in drawing-parameters is changed, or, when the
;;; thing refered to by the extant name in drawing parameters changes in some
;;; way (eg, an image-definition transitioned to OK).  Note that we do this
;;; regardless of whether the system table is actually installed.  Seems
;;; reasonable, and does no harm, I think

(define-analyze-for-consistency drawing-parameters
  (when (ok-to-do-name-consistency-analysis?)
    (let* ((image-palette (image-palette drawing-parameters))
	   (image-name? (image-palette-image-name image-palette)))

      (delete-all-consistency-analysis-frame-notes drawing-parameters)
      (let ((compiled-item-being-analyzed drawing-parameters))
	(analyze-consistency-of-block drawing-parameters)
	(when image-name?
	  (check-undefined-instances-of-class image-name? 'image-definition)))

      (when (and (system-table-installed-p drawing-parameters)
		 (or add-as-item-referring-to-name?	    ; Check or add mode.
		     (checking-for-consistency-analysis-p))
		 (not (frame-being-deleted-p drawing-parameters)))

	(funcall-method-if-any 'update-frame-status-and-notes drawing-parameters)

	;; Is this overkill?  I only post the note after kb-load.
	(when post-kb-loading-consistency-analysis
	  (post-analyzer-warning-note-if-necessary drawing-parameters))

	;; Reify the change.  If Kb loading, then the install-system-table will
	;; take care of this (and properly, too, since we may appear to be installed
	;; at this pointer even when we are not).
	(unless loading-kb-p
	  (propagate-image-palette-to-all-gensym-windows image-palette))))))

;; This piece of code is called when:
;;   (1) The image-palette slot is set. (retract mode before set, then add mode after set)
;;   (2) Some object newly acquires the name referenced in the image-pallete. (check mode)
;;   (3) The image-definition referenced by the name reads its file. (check mode).



(define-analyze-for-consistency kb-workspace
  (when (ok-to-do-name-consistency-analysis?)
    (delete-all-consistency-analysis-frame-notes kb-workspace)

    (let ((compiled-item-being-analyzed kb-workspace))
      (analyze-consistency-of-block kb-workspace)

      (loop for (image-name) in (workspace-background-images kb-workspace) doing
	(check-undefined-instances-of-class image-name 'image-definition))

      (when (frame-style kb-workspace)
	(check-undefined-instances-of-class (frame-style kb-workspace)
					    'frame-style-definition)))

    (post-analyzer-warning-note-if-necessary kb-workspace)

    ;; We will be called in this fashion if any name we refer to has changed
    ;; meaning.  Just in case that name was our background-image,
    ;; refresh the background.  The refresher is smart enough to know whether
    ;; anything has really changed.
    
    (when (and (or post-kb-loading-consistency-analysis	    ; Do this after loading, to ensure caches.
		   (checking-for-consistency-analysis-p))
	       (not (frame-being-deleted-p kb-workspace)))  ; Hmm.
      (reconsider-formatting kb-workspace) ;; frame style
      (refresh-background-images kb-workspace))))



(define-analyze-for-consistency generic-formula
  (let ((formula-is-incomplete?
	  (eq (car (box-translation-and-text generic-formula)) no-value)))
    (analyze-formula-for-consistency
      generic-formula
      (if (not formula-is-incomplete?)
	  (formula-class generic-formula))
      (if (not formula-is-incomplete?)
	  (formula-role-name generic-formula))
      nil
      nil)))

(def-frame-note-writer incompatible-validity-interval-and-data-server
    (particulars)
  (declare (ignore particulars))
  (tformat
    "a validity interval of \"supplied\" (the default value) is only valid ~
     when the data server is \"inference engine\""))

(define-analyze-for-consistency variable
  (when (ok-to-do-name-consistency-analysis?)
    (let ((current-computation-component-particulars nil))
      (delete-all-consistency-analysis-frame-notes variable)
      (delete-all-consistency-analysis-frame-notes variable t))
    (let ((compiled-item-being-analyzed variable)
	  (compiled-item-being-analyzed-started-out-incomplete?
	    (frame-incomplete-p variable))
	  (cell-array? (cell-array variable)))
      ;; Make the variable OK, because some of the specific formula's
      ;; free-references that made the item incomplete, such as stable
      ;; references, may no longer be invalid.  The consistency analysis
      ;; will correct the frame-status, if necessary.
      (when cell-array?
	(when (and (not delete-as-item-referring-to-name?)
		   (frame-incomplete-p variable)
		   (g2-cell-array-expression-cells-have-byte-code-bodies-p
		     cell-array?))
	  (update-frame-status variable nil nil))
	(analyze-g2-cell-array-for-consistency cell-array?))
      ;; Incompatible values in the validity-interval and data-server-map slots
      ;; will result in a frame note, but not effect frame status.
      (when (eq (validity-interval variable) 'supplied)
	(unless (eq (data-server-map variable) 'computation)
	  (add-frame-note
	    'incompatible-validity-interval-and-data-server variable))))
    (post-analyzer-warning-note-if-necessary variable)))

(define-analyze-for-consistency generic-simulation-formula
  (analyze-formula-for-consistency 
    generic-simulation-formula 
    (simulation-formula-class-or-item generic-simulation-formula)
    (simulation-formula-role generic-simulation-formula)
    nil 
    (simulation-formula-left-side generic-simulation-formula)))

;;; This was added to fix bug HQ-2629102 which was that merging in a
;;; generic-simulation-formula into a KB already containing variables it should
;;; effect, wasn't doing so.

(def-class-method initialize-after-reading (generic-simulation-formula)
  (funcall-superior-method generic-simulation-formula)
  (funcall-method 'put-box-translation-and-text-slot-value
		  generic-simulation-formula
		  (box-translation-and-text generic-simulation-formula)
		  nil))

(defun analyze-formula-for-consistency
    (formula formula-class-or-item formula-role
	     form-to-analyze	left-side-of-formula?)
  (when (ok-to-do-name-consistency-analysis?)
    (delete-all-consistency-analysis-frame-notes formula)
    (delete-all-consistency-analysis-frame-notes formula t)
    (let* ((compiled-item-being-analyzed formula)
	   (compiled-item-being-analyzed-started-out-incomplete?
	     (frame-incomplete-p formula))
	   (item-needs-recompile?
	     (and compiled-item-being-analyzed-started-out-incomplete?
		  (no-value-p (car (box-translation-and-text formula)))))
	   (formula-class-case? (symbolp formula-class-or-item))
	   (alist 
	     (when formula-class-case?
	       (installation-list
		 (installation-cons 
		   formula-class-or-item formula-class-or-item))))
	   byte-code-body?
	   initial-value-byte-code-body?
	   initial-value-component-particulars?
	   cell-array?)
      (cond
	((frame-of-class-p formula 'generic-simulation-formula)
	 (setq byte-code-body?
	       (generic-simulation-formula-byte-code-body formula)
	       initial-value-byte-code-body?
	       (generic-simulation-initial-value-byte-code-body formula)
	       initial-value-component-particulars?
	       '(simulation-initial-value *current-computation-frame*)
	       ))
	((frame-of-class-p formula 'generic-formula)
	 (setq cell-array? (cell-array formula))))
      (cond
	(left-side-of-formula?
	 (analyze-compiled-form left-side-of-formula? alist nil)
	 (when (and formula-class-case? formula-class-or-item)
	   (check-for-undefined-class formula-class-or-item)))
	;; The following case is for generic-formulas.  This hack is to ensure
	;; that any consistency notes for the generic formula are registered
	;; with the remainder of the free references for the expression cell
	;; that implements the generic formula.  -jra 6/23/92
	((and formula-class-case? formula-class-or-item formula-role)
	 (let ((current-computation-component-particulars 
		 (slot-value-list
		   'cell-array-element
		   (expression-cell-element-for-generic-formula formula))))
	   (check-for-undefined-class formula-class-or-item)
	   (check-for-undefined-attribute-of-class
	     formula-role formula-class-or-item)
	   (reclaim-slot-value-list current-computation-component-particulars))))
      (when form-to-analyze 
	(analyze-compiled-form form-to-analyze alist nil))
      (when alist (reclaim-installation-tree alist))
      ;; Also analyze the byte-code-body if any.
      (when byte-code-body?
	(when (and (not delete-as-item-referring-to-name?)
		   (not item-needs-recompile?)
		   (frame-incomplete-p formula))
	  ;; Make the formula OK, because some free-references that made the
	  ;; item incomplete, such as stable references, may no longer be
	  ;; invalid.  The consistency analysis will correct the frame-status,
	  ;; if necessary.
	  (update-frame-status formula nil nil))
	(analyze-byte-code-body-for-free-reference-consistency formula
	  byte-code-body?))
      (when initial-value-byte-code-body?
	(let ((current-computation-component-particulars
		initial-value-component-particulars?))
	  (analyze-byte-code-body-for-free-reference-consistency formula
	    initial-value-byte-code-body?)))
      ;; Analyze the cell array, if any.
      (when cell-array?
	(when (and (not delete-as-item-referring-to-name?)
		   (not item-needs-recompile?)
		   (frame-incomplete-p formula)
		   (g2-cell-array-expression-cells-have-byte-code-bodies-p
		     cell-array?))
	  ;; Make the simulation-subtable OK, because some free-references that
	  ;; made the item incomplete, such as stable references, may no longer
	  ;; be invalid.  The consistency analysis will correct the
	  ;; frame-status, if necessary.
	  (update-frame-status formula nil nil))
	(analyze-g2-cell-array-for-consistency cell-array?)))
    (if (null left-side-of-formula?)  ; if not simulation formula
	(post-analyzer-warning-note-if-necessary formula)
	(post-analyzer-warning-note-for-generic-simulation-formula formula))))

;; Left-side-of-formula?  is not a compiled form so it can not currently be
;; analyzed by analyze-compiled-form.  Make special analyzer for it!

(define-analyze-for-consistency function-definition
  (when (ok-to-do-name-consistency-analysis?)
    (delete-all-consistency-analysis-frame-notes function-definition)
    (let ((compiled-item-being-analyzed function-definition)
	  (compiled-item-being-analyzed-started-out-incomplete?
	    (frame-incomplete-p function-definition))
	  (byte-code-body?
	    (function-definition-byte-code-body function-definition)))
      ;; Analyze the byte-code-body, if any.
      (when byte-code-body?
	(when (and (not delete-as-item-referring-to-name?)
		   (frame-incomplete-p function-definition))
	  ;; Make the function OK, because some free-references that made the
	  ;; item incomplete, such as stable references, may no longer be
	  ;; invalid.  The consistency analysis will correct the frame-status,
	  ;; if necessary.
	  (update-frame-status function-definition nil nil))
	(analyze-byte-code-body-for-free-reference-consistency
	  function-definition
	  byte-code-body?)))
    (post-analyzer-warning-note-if-necessary function-definition)))

(define-analyze-for-consistency readout-table
  (analyze-display-for-consistency readout-table))

(define-analyze-for-consistency dial
  (analyze-display-for-consistency dial))

(define-analyze-for-consistency meter
  (analyze-display-for-consistency meter))

(defun analyze-display-for-consistency (display)
  (when (ok-to-do-name-consistency-analysis?)
    (delete-all-consistency-analysis-frame-notes display t)
    (delete-all-consistency-analysis-frame-notes display)
    (let ((compiled-item-being-analyzed display)
	  (compiled-item-being-analyzed-started-out-incomplete?
	    (frame-incomplete-p display))
	  (cell-array? (cell-array display)))
      (when cell-array?
	(when (and (not delete-as-item-referring-to-name?)
		   (frame-incomplete-p display)
		   (g2-cell-array-expression-cells-have-byte-code-bodies-p
		     cell-array?))
	  ;; Make the display OK, because some of the free-references that made
	  ;; the item incomplete, such as stable references, may no longer be
	  ;; invalid.  The consistency analysis will correct the frame-status,
	  ;; if necessary.
	  (update-frame-status display nil nil))
	(analyze-g2-cell-array-for-consistency cell-array?)))
    (post-analyzer-warning-note-if-necessary display)))

(define-analyze-for-consistency trend-chart
  (analyze-display-for-consistency trend-chart)
  (loop with compiled-item-being-analyzed = trend-chart
        for point-format being the slot-component-groups
	    of (trend-chart-point-formats trend-chart)
	as indicator = (slot-component-group-indicator point-format)
	as current-computation-component-particulars
	   = (slot-value-list 'slot-component 'trend-chart-point-formats
			      nil indicator)
	as marker-style = (point-style point-format)
	do
    (when (eq (frame-like-value-key marker-style) 'custom)
      (check-for-undefined-class
	(frame-like-value-property marker-style 'icon-class)))
    (reclaim-slot-value-list current-computation-component-particulars)))

(define-analyze-for-consistency graph
  (let ((display-expressions (car (expressions-to-display graph))))
    (when (and (ok-to-do-name-consistency-analysis?)
	       display-expressions)
      (delete-all-consistency-analysis-frame-notes graph t)
      (let ((compiled-item-being-analyzed graph))
	(if (and (consp display-expressions)
		 (eq (car display-expressions) '\;))
	    ;; if list of expressions
	    (loop with current-computation-component-particulars
		    = (slot-value-cons 'graph-expression 1)
		  for graph-expression in (cdr display-expressions)
		  for expression-index from 1
		  do
	      (setf (cdr current-computation-component-particulars)
		    expression-index)
	      (multiple-value-bind
		  (graph-expression-without-info 
		    plot-color? plot-pattern? plot-min-and-max?)

		  (parse-graph-expression-with-info graph-expression)
		(declare (ignore plot-color?))
		(analyze-compiled-form
		  graph-expression-without-info nil nil)
		(reclaim-slot-value-tree graph-expression-without-info)
		(when (consp plot-pattern? )
		  (reclaim-slot-value-tree plot-pattern?))
		(when (consp plot-min-and-max?)
		  (reclaim-slot-value plot-min-and-max?)))
		  finally
		    (reclaim-slot-value-cons 
		      current-computation-component-particulars))
	    (let* ((current-computation-component-particulars
		     (slot-value-cons 'graph-expression 1)))
	      (multiple-value-bind
		  (graph-expression-without-info 
		    plot-color? plot-pattern? plot-min-and-max?)
		  (parse-graph-expression-with-info display-expressions)
		(declare (ignore plot-color?))
		(analyze-compiled-form
		  graph-expression-without-info nil nil)
		(reclaim-slot-value-tree graph-expression-without-info)
		(when (consp plot-pattern?)
		  (reclaim-slot-value-tree plot-pattern?))
		(when (consp plot-min-and-max?)
		  (reclaim-slot-value plot-min-and-max?))
		(reclaim-slot-value-cons 
		  current-computation-component-particulars))))))
    (post-analyzer-warning-note-if-necessary graph)))



;;; `Analyze-for-consistency, for chart' checks expressions in slot values for
;;; name usage; i.e. it checks if the data series actually name quantity lists.

(define-analyze-for-consistency chart
  #+debug
  (format t "~&analyze-for-consistency chart to~(~A~A~A~A~)"
	  (if (ok-to-do-name-consistency-analysis?) "" " ... (but supressed)")
	  (if add-as-item-referring-to-name? " adding references" "")
	  (if delete-as-item-referring-to-name? " removing references" "")
	  (if (and (not delete-as-item-referring-to-name?)
		   (not add-as-item-referring-to-name?)) " reconsider uses" ""))
  (when (ok-to-do-name-consistency-analysis?)
    (let ((current-computation-component-particulars nil))
      (delete-all-consistency-analysis-frame-notes chart t) ;; get all those in components
      (delete-all-consistency-analysis-frame-notes chart))
    (let ((compiled-item-being-analyzed chart)
	  (data-series (data-series chart)))
      (loop with current-computation-component-particulars
	    = (slot-value-list 'data-series 0)
	    finally (reclaim-slot-value-list current-computation-component-particulars)
	    for a-data-series in data-series
	    as designation-1
	    = (get-simple-part-feature a-data-series 'data-series-info-1)
	    as designation-2
	    = (get-simple-part-feature a-data-series 'data-series-info-2)
	    as data-series-index from 1
	    do (setf (second current-computation-component-particulars)
		     data-series-index)
	    unless (get-simple-part-feature a-data-series 'data-series-failed-to-compile)
	      do
		(when designation-1
		  (analyze-compiled-form designation-1 nil nil))
		(when designation-2
		  (analyze-compiled-form designation-2 nil nil))))
    (post-analyzer-warning-note-if-necessary chart)))


;;; New tables are the first class to use cell arrays, so they have to do
;;; the analyze on the cell array here.

(define-analyze-for-consistency new-table
  (analyze-for-consistency-block-with-only-cell-array new-table))

(define-analyze-for-consistency inter-g2-data-request-holder
  (analyze-for-consistency-block-with-only-cell-array
    inter-g2-data-request-holder))

(define-analyze-for-consistency kb-search-state
  (analyze-for-consistency-block-with-only-cell-array kb-search-state))

(define-analyze-for-consistency user-menu-choice
  (analyze-for-consistency-block-with-only-cell-array user-menu-choice))


;;; `Analyze-for-consistency, method for procedures', uses the free references
;;; stored in its first byte code body as consistency registration location for
;;; the entire procedure.

(define-analyze-for-consistency procedure
  (when (ok-to-do-name-consistency-analysis?)
    (delete-all-consistency-analysis-frame-notes procedure)
    (let ((compiled-item-being-analyzed procedure))
      (analyze-procedure-for-free-reference-consistency procedure))
    (post-analyzer-warning-note-if-necessary procedure)))

(defun analyze-procedure-for-free-reference-consistency (procedure)
  (let* ((compiled-item-being-analyzed procedure)
	 (compiled-item-being-analyzed-started-out-incomplete?
	   (frame-incomplete-p procedure))
	 (first-code-body? (car (code-bodies procedure)))
	 (first-byte-code-body?
	   (when first-code-body?
	     (code-body-byte-code-body first-code-body?))))
    (when first-byte-code-body?
      (when (and (not delete-as-item-referring-to-name?)
		 (frame-incomplete-p procedure))
	;; Make the procedure OK, because some free-references that made the
	;; item incomplete, such as stable references, may no longer be invalid.
	;; The consistency analysis will correct the frame-status, if necessary.
	(update-frame-status procedure nil nil))
      (analyze-byte-code-body-for-free-reference-consistency procedure
	first-byte-code-body?)
      (when (and (not delete-as-item-referring-to-name?)
		 (frame-ok-p procedure)
		 (block-can-be-inlined-p procedure)
		 (or (null (md5-identifier? procedure))
		     (null (parse-results? procedure))))
	(add-frame-note 'item-inlineable-but-has-no-parse procedure)))))

(define-analyze-for-consistency rule
  (when (ok-to-do-name-consistency-analysis?)
    (let* ((parent? (parent-frame rule))
	   (parent-of-embedded-rule?
	    (and parent?
		 (or (frame-of-class-p parent? 'action-button)
		     (frame-of-class-p parent? 'user-menu-choice))
		 parent?))
	   (status-of-embedded-rule-parent?
	    (when parent-of-embedded-rule?
	      (button-frame-status parent-of-embedded-rule?))))
      (delete-all-consistency-analysis-frame-notes rule)
      (let* ((compiled-item-being-analyzed rule)
	     (compiled-item-being-analyzed-started-out-incomplete?
	       (frame-incomplete-p rule))
	     (byte-code-body? (rule-byte-code-body rule)))
	;; Analyze the byte code body, if any.
	(when byte-code-body?
	  (when (and (not delete-as-item-referring-to-name?)
		     (frame-incomplete-p rule))
	    ;; Try to make the rule OK, because some free-references that made
	    ;; the item incomplete, such as stable references, may no longer be
	    ;; invalid.  The consistency analysis will correct the frame-status,
	    ;; if necessary.
	    (cond ((null parent-of-embedded-rule?)
		   (update-frame-status rule nil nil))
		  ((null status-of-embedded-rule-parent?)
		   ;; Only make the item OK, if there are no frame-notes
		   ;; affecting the status.
		   (update-frame-status rule nil nil))))
	  (analyze-byte-code-body-for-free-reference-consistency rule
	    byte-code-body?)))
      (post-analyzer-warning-note-if-necessary rule))))

;; See NEW-RULES and COMPILE1 for documentation on rule forms.



(define-analyze-for-consistency simulation-subtable
  (when (ok-to-do-name-consistency-analysis?)
    (delete-all-consistency-analysis-frame-notes simulation-subtable)
    (let* ((compiled-item-being-analyzed simulation-subtable)
	   (compiled-item-being-analyzed-started-out-incomplete?
	     (frame-incomplete-p simulation-subtable))
	   (byte-code-body?
	     (simulation-subtable-byte-code-body simulation-subtable))
	   (initial-value-byte-code-body?
	     (simulation-subtable-initial-value-byte-code-body
	       simulation-subtable)))
      (when byte-code-body?
	(when (and (not delete-as-item-referring-to-name?)
		   (frame-incomplete-p simulation-subtable))
	  ;; Make the simulation-subtable OK, because some free-references that
	  ;; made the item incomplete, such as stable references, may no longer
	  ;; be invalid.  The consistency analysis will correct the
	  ;; frame-status, if necessary.
	  (update-frame-status simulation-subtable nil nil))
	(analyze-byte-code-body-for-free-reference-consistency
	  simulation-subtable
	  byte-code-body?))
      (when initial-value-byte-code-body?
	(let ((current-computation-component-particulars
		'(simulation-initial-value *current-computation-frame*)))
	  (analyze-byte-code-body-for-free-reference-consistency
	    simulation-subtable
	    initial-value-byte-code-body?))))
    (post-analyzer-warning-note-if-necessary simulation-subtable)))

(define-analyze-for-consistency non-action-button
  (when (ok-to-do-name-consistency-analysis?)
    (delete-all-consistency-analysis-frame-notes non-action-button)
    (let* ((compiled-item-being-analyzed non-action-button)
	   (designation?
	     (associated-variable-designation-function? non-action-button)))
      (when designation?
	(when (and g2-has-v5-mode-windows-p
		   (frame-of-class-p non-action-button 'type-in-box))
	  (send-ws-representations-item-virtual-attribute-change
	    non-action-button (virtual-attribute 'type-in-box-variable-or-parameter) nil))
	(analyze-compiled-form designation? nil nil)))
    (post-analyzer-warning-note-if-necessary non-action-button)))



;;; The analyze-for-consistency `g2-array' checks that any items in the
;;; initial-values attribute and any class in the element-type attribute are
;;; defined.

(define-analyze-for-consistency g2-array
  (when (ok-to-do-name-consistency-analysis?)
    (let ((element-type (g2-array-element-type g2-array)))
      (when (and (not (frame-of-class-p g2-array 'value-array))
		 (g2-list-or-array-element-type-may-contain-item-p
		   element-type))
	(let ((compiled-item-being-analyzed g2-array)
	      (initial-values? (g2-array-initial-values g2-array))
	      (element-type-spec
		(if (eq element-type 'item-or-datum)
		    element-type
		    (gensym-list 'class element-type))))
	  (delete-all-consistency-analysis-frame-notes g2-array)
	  (when (and (symbolp element-type)
		     (not (eq element-type 'item-or-datum))
		     ;; The following is a sub-optimal fix for Issue HQ-4403737
		     ;; "Performance decreasing on creation of item-arrays vs
		     ;; item-lists".  It doesn't fix the true problem, but is
		     ;; more of a workaround for the specific case of having an
		     ;; element-type which is a built-in class.  Bug HQ-4465005
		     ;; -dkuznick, 12/31/02
		     (not (system-defined-class-p element-type)))
	    (check-for-undefined-class element-type))
	  (loop for item-designation-or-value in initial-values?
		do
	    (when (designation-p item-designation-or-value)
	      (if (symbolp item-designation-or-value)
		  ;; Named item reference.
		  (check-undefined-instances-of-type
		    item-designation-or-value element-type-spec)
		  (analyze-compiled-form item-designation-or-value nil nil))))
	  (when (consp element-type-spec)
	    (reclaim-gensym-list element-type-spec)
	    (setq element-type-spec nil))
	  (post-analyzer-warning-note-if-necessary g2-array))))))

;; Improve the above analysis of g2-array initial-values.  Currently, only named
;; items are tested to be of the correct element-type.  All valid designations
;; (constant designations) should be checked for the correct class, if possible.
;; (But, note that all designations are already checked for existence.)
;; - cpm, 1/16/95


;;; The analyze-for-consistency `language-parameters'

(define-analyze-for-consistency language-parameters
  (when (ok-to-do-name-consistency-analysis?)
    (let ((compiled-item-being-analyzed language-parameters))
      (delete-all-consistency-analysis-frame-notes language-parameters)
      (let ((text-conversion-style? (text-conversion-style language-parameters)))
	(when text-conversion-style?
	  (check-undefined-instances-of-class
	    text-conversion-style? 'text-conversion-style))))))



(defun analyze-compiled-form (form alist constraints)
  (cond
    ((numberp form) t)
    ((null form) t)
    ((symbolp form)
     (when (not (reserved-word-p form))
       (analyze-instance-or-local-name form alist)))
    ((text-string-p form) t)
    ((numberp (car form)) t)
    ((eq (car form) 'quote) t)
    (t
     (let ((operator (car form)))
       (cond
	 ((eq operator 'the)
	  (analyze-the-form form alist constraints))
	 ((eq operator 'giver-of-value)
	  (analyze-giver-of-value-form form alist constraints))
	 ((eq operator 'simulation-variable-cache)

	  ;; This should provide more information.
	  ;; However, all of this code will be going
	  ;; away so defer.

	  t)
	 ((memq operator '(let rule-let let-action))
	  (analyze-let-form form alist constraints))
	 (t
	  (analyze-form-according-to-template
	    form (lookup-function-template operator)
	    alist constraints)))))))

;; Class in call to get-instance-with-name-if-any should probably be
;; something higher in the hierarchy than entity.




;(defun analyze-context-iterator (iterator alist)
;  (let* ((domain? (fourth iterator))
;	 (type-info
;	   (analyze-context-iterator-role 
;	     (second iterator) 
;	     (eq (car iterator) 'the)
;	     (name-is-class? domain? alist)
;	     alist)))
;    (when domain? (analyze-instance-or-local-name domain? alist))
;    (installation-cons 
;      (third iterator) type-info)))

;; Inverse iterators (the-inverse, etc.) are not encountered here since 
;; only the context for the universal compilation is analyzed.



(defun name-is-class? (name alist)
  (let ((alist-info (cdr (assq name alist))))
    (when (and alist-info
	       (not (eq alist-info t)))
      alist-info)))

;; If name is a class, the constraint info on the alist will be the
;; class name.  Otherwise, it is t.



;(defun analyze-context-iterator-role (role unique-iterator? domain-class? alist)
;  (cond
;    ((symbolp role)
;     (cond
;       (unique-iterator?  ; if attribute name
;	(if domain-class?
;	    (check-for-undefined-attribute-of-class role domain-class?)
;	    (check-for-undefined-attribute role))
;	t)
;       (t
;	(check-for-undefined-class role)
;	role)))
;    (t
;     (analyze-role role nil alist))))

;; If role is not a symbol analyze-role does not make use of the domain?
;; arg so nil can be passed.



(defun analyze-the-form (form alist constraints)
  (declare (ignore constraints))
  (analyze-role (simple-role-of-role (second form)) (third form) alist))

;; See also atomic-class-element-of-role for notes on role analysis.



(defun analyze-giver-of-value-form (form alist constraints)
  (declare (ignore constraints))
  (check-for-undefined-class (second form))
  (analyze-compiled-form (third form) alist nil))



(defun analyze-role (role domain? alist)
  (cond
    ((symbolp role)
     (when domain?
       (cond
	 ((symbolp domain?)
	  (analyze-compiled-form domain? alist nil)
	  (let ((name-is-class? (name-is-class? domain? alist)))
	    (if name-is-class?
		(check-for-undefined-attribute-of-class role name-is-class?)
		(check-for-undefined-attribute role))))
	 (t
	  (let ((constraint-info (analyze-compiled-form domain? alist nil)))
	    (if (and (symbolp constraint-info)
		     (not (eq constraint-info t)))     ; class
		(check-for-undefined-attribute-of-class role constraint-info)
		(check-for-undefined-attribute role))))))
     (or (name-is-class? role alist)
	 t))
    ((eq (car role) 'class-qualified-name)
     (let ((class-of-role (class-qualifier role)))
       (check-for-undefined-class class-of-role)
       class-of-role))
    ((or (memq
	   (car role) 
	   '(role-server item-color subworkspace system-attribute nth-element))
	 (and (memq
		(car role)
		'(list-iterator first-of-list second-of-list last-of-list
		  next-to-last-of-list))
	      (memq
		(second role)
		internal-g2-element-types-that-can-contain-datum)))
     (analyze-compiled-form domain? alist nil)
     t)
    (t
     (analyze-compiled-form domain? alist nil)
     (let ((class-of-role (car (last role))))
       (check-for-undefined-class class-of-role)
       class-of-role))))

;; Note that for the case where the role is a symbol, there is no need to check
;; the domain for whether it is an undefined class.  If the domain is a class, it
;; has been checked by analyze-context-iterator-role.  If it is an instance or an
;; attribute, it has already been checked.  Consider combining analyze-role and
;; analyze-context-iterator-role.

;; Consider implementing role templates, similar to function and action
;; templates!



(def-substitution-macro add-to-alist-given-binding-list (alist binding-list)
  (loop with binding-count = 0
	for binding in binding-list
	as local-name = (first binding)
	as binding-form = (second binding)
	as binding-form-constraint-info
	   = (analyze-compiled-form binding-form alist nil)
	do
    (setq alist
	  (installation-cons
	    (installation-cons 
	      local-name binding-form-constraint-info) alist)
	  binding-count (+f binding-count 1))
	finally (return (values alist binding-count))))

(def-substitution-macro remove-from-alist-according-to-binding-count
			(alist binding-count)
  (loop for i from 1 to binding-count
	doing (setq alist (prog1 (cdr alist)
				 (reclaim-installation-cons (car alist))
				 (reclaim-installation-cons alist)))
	finally (return alist)))

;; Consider abstracting and using in other evaluators!


(defun analyze-let-form (form alist constraints)
  (multiple-value-bind
    (alist binding-count)
      (add-to-alist-given-binding-list alist (second form))
    (analyze-compiled-form (third form) alist constraints)
    (remove-from-alist-according-to-binding-count
      alist binding-count))
  t  ; return constraint info!
  )

;; Analyze-compiled-form does have to return constraint info
;; since this is put into the binding of a let form!




(defun analyze-rule-body (rule-body alist constraints)
  (let* ((rule-has-non-context-bindings?
	   (eq (car rule-body) 'rule-let))
	 (inner-body
	   (if rule-has-non-context-bindings? (third rule-body) rule-body)))
    (multiple-value-bind
      (alist binding-count)
	(if rule-has-non-context-bindings?
	    (add-to-alist-given-binding-list alist (second rule-body))
	    (values alist 0))
      (analyze-compiled-form (second inner-body) alist constraints)
      (analyze-rule-actions (third inner-body) alist constraints)
      (remove-from-alist-according-to-binding-count
	alist binding-count))))


(defun analyze-rule-actions (actions alist constraints)
  (loop for action in (cdr actions)
	do (analyze-rule-action action alist constraints)))


(defun analyze-rule-action (action alist constraints)
  (let ((action-operator (car action)))
    (case action-operator
      (let-action
       (analyze-let-action action alist constraints))
      (every
       (analyze-every-action action alist constraints))
      ((change-icon-color change-color-pattern) t)
      (t (analyze-form-according-to-template
	   action (lookup-action-template action-operator)
	   alist constraints)))))



(defun analyze-let-action (action alist constraints)
  (multiple-value-bind
    (alist binding-count)
      (add-to-alist-given-binding-list alist (second action))
    (analyze-rule-action (third action) alist constraints)
    (remove-from-alist-according-to-binding-count
      alist binding-count))
  t  ; return constraint info!
  )



(def-substitution-macro add-to-alist-given-scope (alist scope constraints)
  constraints
  (let* ((role (first scope))
	 (local-name (second scope))
	 (domain? (third scope))
	 (binding-constraint-info
	   (analyze-role role domain? alist)))
    (installation-cons
      (installation-cons 
	local-name binding-constraint-info) alist)))

(def-substitution-macro remove-scope-bindings-from-alist (alist)
  (prog1 (cdr alist)
	 (reclaim-installation-cons (car alist))
	 (reclaim-installation-cons alist)))



(defun analyze-every-action (action alist constraints)
  (setq alist (add-to-alist-given-scope alist (second action) constraints))
  (analyze-rule-action (third action) alist constraints)
  (remove-scope-bindings-from-alist alist)
  t  ; return constraint info!
  )


(defun analyze-form-according-to-scope (scope rest-of-forms alist constraints)
  (setq alist (add-to-alist-given-scope alist scope constraints))
  (loop for form in rest-of-forms 
	do (analyze-compiled-form form alist constraints))
  (remove-scope-bindings-from-alist alist)
  t  ; return constraint info!
  )



(defun analyze-form-according-to-template
       (form template? alist constraints)
  (loop with rest-of-template = (cdr template?)
	with template-symbol 
	  = (if template? (car rest-of-template) 'expression)
	with rest-of-sub-forms = (cdr form)
	as sub-form = (car rest-of-sub-forms)
	until (null rest-of-sub-forms)
	do
    (case template-symbol
      (other)  ; do nothing
      (create-connection-spec)		; Should analyze option g2-list of vertices.
					; - cpm, 6/12/95
      ((expression-list designation-list)
       (loop for expression in sub-form
	     do (analyze-compiled-form expression alist constraints)))
      (color-changes
       (loop for (expression1 . expression2) in rest-of-sub-forms
	     do (analyze-compiled-form expression1 alist constraints)
		(analyze-compiled-form expression2 alist constraints))
       (setq rest-of-sub-forms nil))
      (message-designation
       (when (not (memq sub-form '(operator me)))
	 (analyze-compiled-form sub-form alist constraints)))
      (scope
       (analyze-form-according-to-scope
	 (car rest-of-sub-forms) (cdr rest-of-sub-forms)
	 alist constraints)
       (setq rest-of-sub-forms nil))
      (show-or-hide-argument-list
       (when (eq (car sub-form) 'in)
	 (analyze-compiled-form (second sub-form) alist constraints)))

      (t
       ;; designation, expression, message-designation, message-text, 
       ;; inform-option
       (analyze-compiled-form sub-form alist constraints)))
    (when template?
      (if (symbolp (cdr rest-of-template))  ; if dotted list template
	  (setq template-symbol (cdr rest-of-template))
	  (setq rest-of-template (cdr rest-of-template)
		template-symbol (car rest-of-template))))
    (setq rest-of-sub-forms (cdr rest-of-sub-forms))))


(defun analyze-for-consistency-block-with-only-cell-array (block)
  (when (ok-to-do-name-consistency-analysis?)
    (let* ((cell-array? (cell-array block))
	   (user-menu-choice? (frame-of-class-p block 'user-menu-choice))
	   (user-menu-choice-status?
	    (when user-menu-choice?
	      (button-frame-status block))))
      (let ((current-computation-component-particulars nil))
	(delete-all-consistency-analysis-frame-notes block t)  ;; get all those in components
	(delete-all-consistency-analysis-frame-notes block))   ;; get all those on block at large.
      (let ((compiled-item-being-analyzed block)
	    (compiled-item-being-analyzed-started-out-incomplete?
	      (frame-incomplete-p block)))
	(when cell-array?
	  (when (and (not delete-as-item-referring-to-name?)
		     (frame-incomplete-p block))
	    ;; Try to make the block OK, because some of the free-references
	    ;; that made the item incomplete, such as stable references, may no
	    ;; longer be invalid.  The consistency analysis will correct the
	    ;; frame-status, if necessary.
	    (when (and (or (null user-menu-choice?)
			   (null user-menu-choice-status?))
		       ;; Test all the cells.  This is especially important for
		       ;; freeform-tables.  To be OK they should all have byte
		       ;; code bodies.
		       (g2-cell-array-expression-cells-have-byte-code-bodies-p
			 cell-array?))
	      ;; Only make the item OK, if there are no frame-notes affecting
	      ;; the status.
	      (update-frame-status block nil nil)))
	  (analyze-g2-cell-array-for-consistency (cell-array block)))
	(post-analyzer-warning-note-if-necessary block)))))






;;;; Name Checking Functions


;;; The following are the functions that actually note compiled-item-being-
;;; analyzed on the compiled-items-referring-to-this-name property and put up
;;; frame notes if necessary.

;;; Two special variables add-as-item-referring-to-name?, and delete-as-item-
;;; referring-to-name? control whether compiled-item-being-analyzed is added
;;; or deleted from the property.  This is important since the item must be
;;; deleted from the compiled-items-referring-to-this-name property of a name
;;; if a compiled item is edited such that it no longer refers to the name.

;;; Also, there is no need to add the item if the analysis is being done for a
;;; reason other than an edit to the item.  For example, definition of a class
;;; does not affect the compiled-items-referring-to-this-name property of any
;;; rules.  Also, no frame notes are added if delete-as-item-referring-to-name?
;;; is non-nil.



(defun add-or-delete-as-item-referring-to-name (name)
  (cond
    (delete-as-item-referring-to-name?
     (delete-from-set (compiled-items-referring-to-this-name name)
		      compiled-item-being-analyzed installation))
    (add-as-item-referring-to-name?
     (add-to-set (compiled-items-referring-to-this-name name)
		 compiled-item-being-analyzed installation))))    

(defun check-for-undefined-class (class)
  (add-or-delete-as-item-referring-to-name class)
  (when (and (null delete-as-item-referring-to-name?)
	     (not (subclassp class 'item)))
    (add-to-frame-note-particulars-list-if-necessary
      class 'undefined-classes compiled-item-being-analyzed)))


(defun check-undefined-instances-of-class (name class)
  (add-or-delete-as-item-referring-to-name name)
  (unless delete-as-item-referring-to-name?
    ;; Note that the following line must pass 'item, not the given class, since
    ;; the runtime lookup also uses item and this function is warning about
    ;; troubles that might happen during runtime.  -jra 12/1/94
    (let ((instance (get-instance-with-name-if-any 'item name)))
      (cond 
	((and (null instance) (not (eq name 'message-board)))
	 (add-to-frame-note-particulars-list-if-necessary
	   name 'non-existent-instances compiled-item-being-analyzed))
	((or (and instance
		  (not (frame-of-class-p instance class)))
	     ;; Message-boards are created by G2 and are not saved in KB's.
	     (and (eq name 'message-board)
		  (not (subclassp 'message-board class))))
	 (add-to-frame-note-particular-pairs-as-necessary
	   'non-existent-instances-of-class class name nil))))))

(defun check-undefined-instances-of-type (name type)
  (add-or-delete-as-item-referring-to-name name)
  (unless delete-as-item-referring-to-name?
    ;; Note that the following line must pass 'item, not the given class, since
    ;; the runtime lookup also uses item and this function is warning about
    ;; troubles that might happen during runtime.  -jra 12/1/94
    (let ((instance (get-instance-with-name-if-any 'item name)))
      (cond 
	((and (null instance) (not (eq name 'message-board)))
	 (add-to-frame-note-particulars-list-if-necessary
	   name 'non-existent-instances compiled-item-being-analyzed))
	((or (and instance (not (type-specification-type-p instance type)))
	     ;; Message-boards are created by G2 and are not saved in KB's.
	     (and (eq name 'message-board)
		  (not (type-specification-subtype-p
			 '(class message-board) type))))
	 (add-to-frame-note-particular-pairs-as-necessary
	   'non-existent-instances-of-type type name t))))))



;;; The function `check-for-undefined-instance-name' will not issue a note for
;;; the name message-board.  The message board created by G2 for inform actions
;;; is never saved in KBs, and so is always destined to be a problem for name
;;; consistency analysis if users do anything with it.

(defun check-for-undefined-instance-name (name)
  (add-or-delete-as-item-referring-to-name name)
  (when (and (null delete-as-item-referring-to-name?)
	     (null (get-instance-with-name-if-any 'item name))
	     (neq name 'message-board))
    (add-to-frame-note-particulars-list-if-necessary
     name 'non-existent-instances compiled-item-being-analyzed)))

#+mtg2
(defun check-for-foreign-factions (parent name)
  (when (and
	 parent
	 (null (get-faction-instance-with-name-if-any
		(faction? parent) 'item name)))
    (add-to-frame-note-particulars-list-if-necessary
     name 'foreign-faction-instances compiled-item-being-analyzed)))


;;; The function `check-for-valid-method' warns of several types of problems
;;; with a method: a missing generic method-declaration; argument conflicts with
;;; other specific methods for the class (i.e., there is no unique method
;;; dispatch for this method and class).

(defun check-for-valid-method (name)
  (add-or-delete-as-item-referring-to-name name)
  (when (null delete-as-item-referring-to-name?)
    (when (null (get-instance-with-name-if-any 'method-declaration name))
      (add-frame-note
	'non-existent-procedure-method compiled-item-being-analyzed))
    (let ((argument-count? (argument-count compiled-item-being-analyzed))
	  (method-class?
	    (procedure-method-class compiled-item-being-analyzed)))
      (when (and argument-count? method-class?
		 (duplicate-specific-methods-p
		   name method-class? argument-count?))
	(add-frame-note
	  'specific-method-argument-conflict compiled-item-being-analyzed)))))



;;; The function `check-for-cached-name-undefined-instance' checks if the named
;;; item exists and updates the constant-vector.  It caches either the item or a
;;; cons containing the item name.

;; Note that caching an item in the constant-vector does not cause problems with
;; saving KBs and/or modules.  When the constant-vector is written to the KB, it
;; writes nil instead of the item.  Then, when the KB is loaded the consistency
;; analysis takes care of updating the cached item or name in the
;; constant-vector.  It is important that the save KB does not write the cached
;; item into the KB because the item could be from another module.  - cpm,
;; 7/1/93

(defconstant cached-name-cons-marker '|cached-item-name|)

(defun check-for-cached-name-undefined-instance (#+mtg2 parent name index)
  (let* ((byte-code-body?
	   (get-byte-code-body-if-any
	     compiled-item-being-analyzed
	     current-computation-component-particulars))
	 (constant-vector?
	   (and byte-code-body?
		(byte-code-body-constant-vector byte-code-body?)))
	 (instance?
	  #-mtg2
	  (get-instance-with-name-if-any 'item name)
	  #+mtg2
	  (or
	   (get-faction-instance-with-name-if-any
	    (faction? parent) 'item name)
	   (get-instance-with-name-if-any 'item name))))
    (when (and constant-vector? (<f index (length constant-vector?)))
      ;; Cache the item, if it exists, or the item name.
      (let ((old-constant-value? (svref constant-vector? index)))
	(cond
	  (instance?
	   ;; If the constant location held a cached name, reclaim it.
	   (when (and old-constant-value? (consp old-constant-value?))
	     (reclaim-slot-value-cons old-constant-value?))
	   (setf (svref constant-vector? index) instance?))
	  (t
	   ;; If the constant location already holds a cached name, modify it.
	   ;; Otherwise, add a new cached name.
	   (if (and old-constant-value? (consp old-constant-value?))
	       (setf (car old-constant-value?) name)
	       (setf (svref constant-vector? index)
		     (slot-value-cons name cached-name-cons-marker)))))))
    ;; The following adds or deletes as item referring to name.  It also adds
    ;; frame-notes when necessary.
    (check-for-undefined-instance-name name)))



;;; The function `check-for-cached-attribute' checks if the attribute exists for
;;; the item or class, attempts to determine the location of this attribute, and
;;; then updates a cache in the constant-vector based on this information.

;;; It caches either the vector index for the attribute, if it exists, or the
;;; attribute's name and other information in a list.  Note that to cache the
;;; attribute index based on a class (i.e., a generic-reference), no subclass of
;;; the class can have that attribute at a different index location.

;;; Here are the conditions under which the user-vector-slot-index value for a
;;; user-defined attribute reference may differ between related classes:
;;;
;;; (1) NON-CLASS-QUALIFIED ATTRIBUTE REFERENCES
;;;     (the default attribute with that unqualified-name for the class):
;;;
;;;     (a) For single-inheritance or multiple-inheritance class hierarchies
;;;         that have overloaded attribute names.
;;;         
;;;             Example-a:  If the hierarchy consists of two classes, A and B,
;;;                         that have an inferior/superior relationship and
;;;                         both A and B define a class-specific attribute named
;;;                         <same-unqualified-name>, the user-vector locations for
;;;                         those attributes will differ.
;;;
;;;     (b) For multiple-inheritance class hierarchies without name
;;;         overloading. 
;;;         
;;;             Example-b:  If the hierarchy consists of two sibling classes,
;;;                         A and B, where A defines a class-specific-attribute
;;;                         called att-a and B defines a class-specific attribute
;;;                         called att-b, and A and B share a direct-inferior class,
;;;                         C, EITHER the user-vector location of att-a in C OR the
;;;                         user-vector location of att-b in C will differ from the
;;;                         user-vector location of the superior that defined that
;;;                         attribute.
;;;
;;;
;;; (2) CLASS-QUALIFIED ATTRIBUTE REFERENCES:
;;;
;;;     This can only happen in multiple-inheritance clas hierarchies.  Example-b
;;;     above can serve as an example.
;;; (ghw 3/20/96)

;;; Note that the attribute is cached either as a vector index or a list
;;; containing the attribute name and some other information.  A list is used,
;;; instead of perhaps a symobl, so that this constant-vector value does not
;;; collide (constant-fold) with other values in the constant vector.  In
;;; particular, this prevents constant-folding with non-attribute references to
;;; the same symbol and with other references to the same attribute of a
;;; different class or instance of a different class.

;;; The form of cached attribute information in the constant-vector is either:
;;;     (attribute-name item-name? class-name? class-specific-attribute-class?
;;;      <cached-attribute-cons-marker>)
;;; or
;;;     <attribute-vector-index>

(defun check-for-cached-attribute
    (attribute-name item-name? class? class-specific-attribute-class?
		    constant-index)
  (let* ((item? 
	  (and item-name? (get-instance-with-name-if-any 'item item-name?)))
	 (item-class?
	  (and item? (class item?))))
    (unless delete-as-item-referring-to-name?
      ;; Don't need to do update the cached attribute information if
      ;; delete-as-item-referring-to-name?
      (let* ((byte-code-body?
	       (get-byte-code-body-if-any
		 compiled-item-being-analyzed
		 current-computation-component-particulars))
	     (constant-vector?
	       (when byte-code-body?
		 (byte-code-body-constant-vector byte-code-body?)))
	     (class-description? (and (not (eq class? 'item)) (classp class?)))
	     (slot-description?
	       (cond
		 ((eq attribute-name 'class) nil)
		 (item-class?
		  (get-slot-description-of-frame
		    attribute-name item? class-specific-attribute-class?))
		 (class-description?
		  (get-slot-description-of-class-description
		    attribute-name class-description?
		    class-specific-attribute-class?))
		 (t nil)))
	     (attribute-index?
	       (when slot-description?
		 ;; Get the attribute index if the class and attribute exist.
		 (user-vector-slot-index? slot-description?))))

	;; Validate the attribute-index of a generic-reference that is not a
	;; class-specific attribute reference.
	(when (and attribute-index? (null item?) class?
		   (user-vector-slot-location-differs-in-subclass-p
		     attribute-name class? class-specific-attribute-class?))
	  ;; If all subclasses do not have the same location for the attribute,
	  ;; then do not cached the attribute index.
	  (setq attribute-index? nil))

	;; Update the attribute cache.
	(when (and constant-vector?
		   (<f constant-index (length constant-vector?)))
	  ;; Cache the attribute index, if it exists, or the attribute name.
	  (let ((old-constant-value? (svref constant-vector? constant-index)))
	    (cond
	      (attribute-index?
	       (when (and old-constant-value? (listp old-constant-value?))
		 (reclaim-slot-value-list old-constant-value?))
	       (setf (svref constant-vector? constant-index) attribute-index?))
	      (t
	       ;; If the constant location already holds a cached attribute
	       ;; name, modify it.  Otherwise, add a new cached attribute.
	       (if (and old-constant-value? (listp old-constant-value?))
		   (setf (car old-constant-value?) attribute-name)
		   (setf (svref constant-vector? constant-index)
			 (slot-value-list
			   attribute-name item-name? class?
			   class-specific-attribute-class?
			   cached-attribute-cons-marker)))))))))
    ;; Analyze the attribute and register references to the attribute and class.
    (cond
      (class-specific-attribute-class?
       ;; Note that this function takes the class? and not the item-class?
       ;; argument.  The item-class? argument should not be registered with
       ;; add-or-delete-as-item-referring-to-name because it can be non-NIL when
       ;; the item is present and then NIL when it has been deleted.  This would
       ;; leave the item-referring-to-name in an inconsistent state.  - cpm,
       ;; 11/2/94
       (check-for-undefined-class-qualified-attribute-of-class
	 attribute-name class-specific-attribute-class? class?))
      ((and item-class? (or (null class?)
			    (subclassp item-class? class?)))
       ;; Also registers the compiled item as referring to the attribute.
       (check-for-undefined-attribute-of-class attribute-name item-class?)
       (when class?
	 (add-or-delete-as-item-referring-to-name class?)))
      (class?
       ;; Also registers the compiled item as referring to the attribute.
       (check-for-undefined-attribute-of-class attribute-name class?)
       ;; Registers the compiled item as referring to the class.  The item will
       ;; then be analyzed when the class changes.
       (add-or-delete-as-item-referring-to-name class?))
      (t
       ;; If this free reference was added without a registered class, then it
       ;; is possible that this attribute fetch may reference an attribute of a
       ;; structure.  In this case, register this as an item referring to the
       ;; attribute name, but do not issue any warnings about the attribute
       ;; being undefined.  -jra 1/19/97
       (add-or-delete-as-item-referring-to-name attribute-name)))))


;; This function assumes that add-or-delete-as-item-referring-to-name does not
;; need to be called for the item name.  This should have already been recorded
;; using another free-reference, such as cached-name or name.  - cpm, 7/22/93

;; Note that authorized-system-slots will be cached as symbols, if there are no
;; user-defined attributes that override them.  The cached-attribute-value
;; instruction then will lookup the value based on the attribute name.  - cpm,
;; 7/23/93


;; The following notes analyze how changes to classes affect the
;; cached-attribute free-reference and whether additional consistency analysis
;; is needed.
;; 1. Attribute change:
;;   Add attribute to class.
;;     Analysis of attribute name.
;;     * Can cause new attribute locations in class and subclasses.
;;   New inherited attribute (add attribute to superior-class).
;;     Analysis of attribute name.
;;     * Can cause new attribute locations in class and subclasses.
;;   Remove attribute from class.
;;     Analysis of attribute name.
;;     * Can cause new attribute locations in class and subclasses.
;;   Remove inherited attribute from class (delete from superior-class).
;;     Analysis of attribute name.
;;     * Can cause new attribute locations in class and subclasses.
;; 2. Class name change
;;     Analysis of old and new class name.
;;     Analysis of the non-inherited attributes of the class.
;; 3. Superior class name change
;;   Change superior-class attribute.
;;     Analysis of local attributes of the class.
;;     Analysis of the local attributes of the subclasses.
;;     Does not analyze the old or new inherited attributes of the class.
;;     Analysis of the class name (not the superior-class name).
;;     Analysis of sub-class names.
;;     * Need to analyze the old and new superior-classes cached-attribute
;;     free-references.
;;       (Analysis of local attributes of the class may suffice because
;;        these are the ones that can possibly conflict with those of the old
;;        and new superior classes.)
;;       This could affect possible attribute location conflicts.
;;     * Need to analyze the sub-classes cached-attribute free-references.
;;       (Analysis of the local attributes of the subclasses may suffice because
;;        these may be in conflict with the old or new inherited attributes.)
;;       This could affect possible attribute location conflicts.
;;   The superior-class changes its name, which is propagated to the
;;   superior-class attribute of the class.
;;     Analysis of old and new (superior-class) name
;;     Analysis of attributes of the superior-class.
;; 4. Delete class
;;     Analysis of local attributes of the class.
;;     Analysis of the class name.
;; 5. Delete superior-class.
;;     Analysis of local attributes of the superior-class being deleted and
;;     subclass.
;;     Analysis of the superior-class and subclass names.
;; 6. Class "change" operation
;;   Rename attribute.
;;     Analysis of old and new attribute names.
;;     * Can cause new attribute locations in subclasses.
;;   Merge all instances and subclasses into definition.
;;     Analysis is not done.
;;     Will be done when the obsolete (merged) class is deleted.
;; 7. Verify how the above cases are affected by having instances of the
;;    classes.
;;   * not yet verfied.
;; 8. Verify how the above cases are affected by multiple inheritance.
;;   * not yet verfied.
;; 9. Capabilities
;;   * not yet verfied.
;;
;; Based on the above analysis, the current behavior of consistency analysis
;; will maintain the cached-attribute free references when there are changes to
;; a class or attribute in a class.  (Note that that this needs to be reviewed
;; based on #7 and #8.)
;;
;; The current consistency-analysis did not handle the case where a change in a
;; class affects the location of attributes in another class or a change in
;; attribute affects the location of other attributes of this and other classes.
;; In these cases, the attributes of the affected classes need to be analyzed.
;; This is now handled in the slot-putter for attribute-descriptions-for-class
;; which calls analyze-attributes-of-subclasses-for-consistency.
;;
;; - cpm, 8/23/93




;;; The function `analyze-attributes-of-subclasses-for-consistency' is used to
;;; do consistency analysis on attributes of all subclasses of the given
;;; user-class.

;;; This analysis is necessary when attributes have changed in the user-class
;;; such that the attribute locations of subclasses may be affected.  This
;;; analysis is important for the cached-attribute free-reference which inlines
;;; attribute vector locations, when possible.  Note that the user-class itself
;;; *is* also analyzed.

;;; Note that inherited attributes are also analyzed, if specified by the second
;;; argument.

(defun analyze-attributes-of-subclasses-for-consistency
    (user-class analyze-inherited-attributes-also?)
  (when (classp user-class)
    (if (null analyze-inherited-attributes-also?)
	(loop for subclass being each subclass of user-class
	      do
	  (analyze-class-attributes-for-consistency subclass nil))
	;; Analyze attributes (including inherited) of only the "leaf"
	;; subclasses (no inferiors).  This is done so that the same attributes
	;; are not analyzed repeatedly for different classes.
	(loop for subclass being each subclass of user-class
	      do
	  (when (null (inferior-classes subclass))
	    (analyze-class-attributes-for-consistency subclass t))))))

;; Another way of analyzing the attribute expressions is to analyze those items
;; referring to the subclasses of the class (by class name).  This may be more
;; efficient because an item is analyzed only once when referring to different
;; attributes of the same class.  The problem with this is that it would only
;; analyze generic attribute references and not non-generic references.  - cpm,
;; 9/17/93



;;; The function `analyze-class-attributes-for-consistency' is used to analyze
;;; for consistency all the attributes defined for the given user class.  Note
;;; that inherited attributes are also analyzed, if specified by the second
;;; argument.

(defun analyze-class-attributes-for-consistency
    (user-class analyze-inherited-attributes-also?)
  (when (classp user-class)
    (loop with class-description? = (class-description user-class)
	  with slot-descriptions? =
	    (and class-description? (slot-descriptions class-description?))
	  for slot-description in slot-descriptions?
	  for slot-name = (pretty-slot-name slot-description)
	  ;; Only analyze user-defined, non-inherited slots, when specified.
	  ;; Don't want to analyze the same attribute multiple times.
	  when (and (user-defined-slot-description-p slot-description)
		    (or analyze-inherited-attributes-also?
			(eq (defining-class slot-description) user-class)))
	    do
	      (analyze-compiled-items-for-consistency slot-name))))

;; Check-undefined-instances-of-class may only be used for system-defined
;; classes until such time as changing the superior class of user definitions
;; invokes analyze-for-consistency for all instances with names.  Not currently
;; used.




(defun check-for-undefined-attribute (attribute)
  (add-or-delete-as-item-referring-to-name attribute)
  ;; Note that the compiler will decline to register free references for
  ;; expressions where the domain may intersect with (structure), so that case
  ;; does not need to be handled here.  -jallard 5/8/97
  (when (and (null delete-as-item-referring-to-name?)
	     (null (attribute-of-class-or-subclass-p attribute 'item))
	     (not (exported-attribute-of-class-or-subclass-p attribute 'item))
	     (not (virtual-attribute attribute)))
    (add-to-frame-note-particulars-list-if-necessary
      attribute 'undefined-attributes compiled-item-being-analyzed)))

(defun check-for-undefined-attribute-of-class (attribute class)
  (add-or-delete-as-item-referring-to-name attribute)
  (when (and (null delete-as-item-referring-to-name?)
	     (null (attribute-of-class-or-subclass-p attribute class))
	     (not (exported-attribute-of-class-or-subclass-p attribute class))
	     (not (virtual-attribute attribute)))
    (add-to-undefined-attribute-of-class
      class attribute compiled-item-being-analyzed)))

;; The following clauses were removed from the functions
;; check-for-undefined-attribute and check-for-undefined-attribute-of-class
;; today.  I believe this completes the notes rewrite to now be up to date with
;; exported attributes.  -jallard 5/10/97
;;
;;  (null (memq attribute undefined-attribute-exceptions))
;;  (not (system-defined-attribute-p attribute))
;;  (not (attribute-previously-put-in-attribute-tables-p attribute))
;;  (not (attribute-previously-put-in-attribute-tables-p attribute class)) ; just in check-for-undefined-attribute-of-class




(defun check-for-undefined-method-of-class (method class)
  (add-or-delete-as-item-referring-to-name method)
  (when (and (null delete-as-item-referring-to-name?)
	     (null (method-of-class-or-subclass-p method class)))
    (add-to-undefined-method-of-class
      class method compiled-item-being-analyzed)))


(defun check-for-undefined-class-qualified-attribute
    (attribute-name class-qualifier)
  ;; The following also registers the compiled item as referring to the
  ;; class-specific attribute class.  The item will then be analyzed when the
  ;; class changes.
  (check-for-undefined-class class-qualifier)
  ;; Also registers the compiled item as referring to the attribute.
  (check-for-undefined-attribute-of-class attribute-name class-qualifier)
  nil)

(defun check-for-undefined-class-qualified-method
    (method-name class-qualifier)
  ;; The following also registers the compiled item as referring to the
  ;; class-specific-method class.  The item will then be analyzed when the
  ;; class changes.
  (check-for-undefined-class class-qualifier)
  ;; Also registers the compiled item as referring to the method.
  (check-for-undefined-method-of-class method-name class-qualifier)
  nil)

(defun check-for-undefined-class-qualified-attribute-of-class
    (attribute-name class-qualifier class?)
  ;; Also, registers the compiled item as referring to the class-qualifier.
  (check-for-undefined-class class-qualifier)
  ;; Also, registers the compiled item as referring to the attribute.
  (check-for-undefined-attribute-of-class attribute-name class-qualifier)
  ;; Check that the qualified attribute may be defined for the class.
  (when (and class-qualifier class?
	     (not (subclassp class? class-qualifier))
	     (not (subclassp class-qualifier class?)))
    ;; Similar to check-for-undefined-attribute-of-class, only warn if the
    ;; attribute is not defined for the class or a subclass.  This is done by
    ;; checking if class and class-qualifier are not disjoint.
    (let ((slot-name-denotation?
	   (make-slot-name-denotation
	     attribute-name class-qualifier slot-value-cons)))
      (add-to-frame-note-particular-pairs-as-necessary
	'undefined-attributes-of-classes class?	slot-name-denotation? t)
      ;; The denotation was copied into the above frame-note, so reclaim the
      ;; original.
      (reclaim-slot-value-list slot-name-denotation?)))
  (when (and class? (not (system-defined-class-p class?)))
    ;; Register the compiled item as referring to the generic-reference class,
    ;; if any.  The item will then be analyzed when the class changes.
    (add-or-delete-as-item-referring-to-name class?))
  nil)

(defun analyze-instance-or-local-name (name alist)
  (let ((alist-info (cdr (assq name alist))))
    (cond 
      (alist-info				       ; local name
       )
      ((memq name '(message-board)))
      (t
       (check-for-undefined-instance-name name)
       ))
    t))

;(defun add-to-undefined-attribute-of-class
;       (class attribute compiled-item-being-analyzed) 
;  (let* ((existing-particulars
;	   (get-particulars-of-frame-note-if-any 
;	     'undefined-attributes-of-classes compiled-item-being-analyzed))
;	 (entry-for-class?
;	   (assq class existing-particulars)))
;    (if (not entry-for-class?)
;	(add-frame-note
;	  'undefined-attributes-of-classes compiled-item-being-analyzed
;	  (nconc existing-particulars 
;		 (slot-value-list (slot-value-list class attribute)))
;	  nil nil)
;	(if (not (memq attribute entry-for-class?))
;	    (setf (cdr entry-for-class?)
;		  (slot-value-cons attribute (cdr entry-for-class?)))))))

(defun add-to-undefined-attribute-of-class
    (class attribute compiled-item-being-analyzed)
  (add-to-frame-note-particular-pairs-as-necessary
    'undefined-attributes-of-classes class attribute nil))

(defun add-to-undefined-method-of-class
    (class method compiled-item-being-analyzed)
  (add-to-frame-note-particular-pairs-as-necessary
    'undefined-methods-of-classes class method nil))
  

;;; The function `check-for-valid-procedure-call' takes five arguments, the
;;; symbol remote-procedure-call or procedure-call, the name of the procedure, a
;;; list of actual argument types, a list of required return value types, and a
;;; flag that indicates if this is a stable procedure call.  This function
;;; should seek an actual procedure by that name, and if found verify that the
;;; arguments to be given fit within the arguments required by the procedure,
;;; and that the return types required can be satisfied by the return types of
;;; the procedure.

;;; Note that stable procedure calls are not validated with type coercion of its
;;; arguments.  For stable procedures, this should have already been handled in
;;; its compilation.  So, its args should have already been coerced, if
;;; necessary.  Also, note that stable procedure argument and return types must
;;; be EQUAL to the types passed to this function.  This is necessary because a
;;; dependent item was compiled based on the these argument and return types.
;;; If the types for the called procedure changed, even if they are more
;;; general, the call should be considered invalid and require a recompile.

;;; Also note that stable procedure calls do not depend on the called procedure
;;; being OK.  (This check is done when the procedure is called.)  This is
;;; important because we want the calling procedure's stable free reference to
;;; only depend on the conditions of its free-reference, not whether the called
;;; procedure has valid stable free-references.  (Incorrect stability dependence
;;; should only be noted in the dependent item and not propagated among the
;;; graph of procedure calls.)  This allows the calling procedure not to require
;;; a recompile when the called procedure, which had an invalid stable
;;; free-reference, is now OK.

;;; This function returns T if the procedure call is valid and NIL if it is
;;; invalid.  Note that if the procedure call reference is being deleted (i.e.,
;;; when delete-as-item-referring-to-name?), this function returns T, without
;;; checking for a valid call.

(defun check-for-valid-procedure-call
    (type-of-call name arg-types return-types stable-procedure-call?
		  procedure-to-analyze?)
  (let ((valid-procedure-call? t))	; return-value
    (add-or-delete-as-item-referring-to-name name)
    (unless delete-as-item-referring-to-name?
      (let ((instance? nil)
	    (formal-arg-types nil)
	    (formal-arg-restp-index nil)
	    (formal-arg-kinds nil)
	    (formal-return-types nil)
	    (formal-return-restp-index nil)
	    (method-first-arg-class? nil)
	    (method-error-no-arg? nil)
	    (method-error-first-arg-type-not-class? nil)
	    (method-error-no-method-for-arg-count?)
	    (method-error-no-method-for-class?)
	    (method-error-method-for-class-not-ok?))
	(case type-of-call
	  ((procedure-call stable-procedure-call)
	   (setq instance?
		 (or procedure-to-analyze?
		     (get-instance-with-name-if-any 'item name)))
	   (cond 
	     ((null instance?)
	      (setq valid-procedure-call? nil)
	      (add-to-frame-note-particulars-list-if-necessary
		name 'non-existent-instances compiled-item-being-analyzed))
	     ((and instance?
		   (not (frame-of-class-p instance? 'procedure)))
	      (setq valid-procedure-call? nil)
	      (add-to-frame-note-particular-pairs-as-necessary
		'non-existent-instances-of-class 'procedure name nil)
	      (setq instance? nil))
	     ((and instance?
		   (not (frame-ok-p instance?)))
	      (unless stable-procedure-call?
		(setq valid-procedure-call? nil))
	      (add-to-frame-note-particulars-list-if-necessary
		name 'item-not-ok compiled-item-being-analyzed)
	      (setq instance? nil))
	     ((frame-of-class-p instance? 'method-declaration)
	      (let* ((method-list? nil)
		     (first-arg-type?
		       (if arg-types (car-of-cons arg-types))))
		(setq method-first-arg-class?
		      (cond ((null first-arg-type?) nil) ; No argument.
			    ((class-type-specification-p first-arg-type?)
			     (type-specification-class first-arg-type?))
			    ((type-specifications-could-intersect-p
			       first-arg-type? '(class item))
			     ;; Test if the method is defined for any item.
			     'item)
			    (t nil)))
		(cond ((null first-arg-type?)
		       (setq method-error-no-arg? t))
		      ((null method-first-arg-class?)
		       (setq method-error-first-arg-type-not-class?
			     first-arg-type?))
		      ((not (classp method-first-arg-class?))
		       ;; Try to locate a method, even though the class is not
		       ;; yet defined.
		       (setq method-list?
			     (get-specific-methods-for-class-or-superior-class
			       name method-first-arg-class?))
		       (if (null method-list?)
			   (setq method-error-no-method-for-class? t)
			   (loop for method in method-list?
				 with arg-count = (length arg-types)
				 with method-found? = nil
				 do
			     (when (=f (argument-count method) arg-count)
			       (setq method-found? t))
				 until method-found?
				 finally
				   (unless method-found?
				     (setq method-error-no-method-for-arg-count?
					   t)))))
		      (t
		       ;; Else, check the method hierarchy for the class
		       ;; (methods defined on inferior and superior classes).
		       (case (check-valid-method-definition-of-existing-class
			 name method-first-arg-class? arg-types)
			 (arg-count (setq method-error-no-method-for-arg-count? t))
			 (class (setq method-error-no-method-for-class? t)))))))
	     (t
	      (setq formal-arg-types
		    (collect-types-into-list-using-gensym-conses
		      (argument-list-description instance?)))
	      ;; GENSYMCID-1816: Access to uninitialized data while reading kb
	      ;; In this case, the list is not used, fill all elements with NILs to make cons-checking happy.
	      (let ((var-count (var-count (argument-list-description instance?))))
		(setq formal-arg-kinds (make-gensym-list var-count))
		#+cons-checking
		(loop for e on formal-arg-kinds do
		  (setf (car e) nil)))
	      (setq formal-return-types
		    (collect-types-into-list-using-gensym-conses
		      (returned-values-description instance?))))))
	  ((remote-procedure-call stable-remote-procedure-call)
	   (setq instance?
		 (or procedure-to-analyze?
		     (get-instance-with-name-if-any 'item name)))
	   (cond 
	     ((null instance?)
	      (setq valid-procedure-call? nil)
	      (add-to-frame-note-particulars-list-if-necessary
		name 'non-existent-instances compiled-item-being-analyzed))
	     ((and instance?
		   (not (frame-of-class-p
			  instance? 'remote-procedure-declaration)))
	      (setq valid-procedure-call? nil)
	      (add-to-frame-note-particular-pairs-as-necessary
		'non-existent-instances-of-class
		'remote-procedure-declaration
		name
		nil)
	      (setq instance? nil))
	     ((and instance?
		   (not (frame-ok-p instance?)))
	      (unless stable-procedure-call?
		(setq valid-procedure-call? nil))
	      (add-to-frame-note-particulars-list-if-necessary
		name 'item-not-ok compiled-item-being-analyzed)
	      (setq instance? nil))
	     (t
	      (setq formal-arg-types
		    (loop with description-vector =
			  (remote-procedure-argument-description instance?)
			  for index from 0 below (var-count description-vector)
			  collect (var-type-from-index description-vector index)
			    using gensym-cons))
	      (setq formal-arg-kinds
		    (loop with description-vector =
			  (remote-procedure-argument-description instance?)
			  for index from 0 below (var-count description-vector)
			  for description = (var-general-description-from-index description-vector index)
			  when (getf description :all-remaining)
			    do (setq formal-arg-restp-index index)
			  collect (getf description :kind)
			    using gensym-cons))	      
	      (setq formal-return-types
		    (loop with description-vector =
			  (remote-procedure-returned-values-description instance?)
			  for index from 0 below (var-count description-vector)
			  for description = (var-general-description-from-index description-vector index)
			  when (getf description :all-remaining)
			    do (setq formal-return-restp-index index)
			  collect (var-type-from-index description-vector index)
			    using gensym-cons))))))
	;; Analyze the expected arguments and return values.  Note that
	;; method declarations are a special case.
	(when instance?
	  (cond ((frame-of-class-p instance? 'method-declaration)
		 (cond
		   (method-error-no-arg?
		    (add-to-frame-note-particulars-list-if-necessary
		      name
		      'no-arg-for-method-call
		      compiled-item-being-analyzed))
		   (method-error-first-arg-type-not-class?
		    (add-to-frame-note-particular-pairs-as-necessary
		      'no-item-arg-for-method-call
		      name method-error-first-arg-type-not-class? t))
		   (method-error-no-method-for-class?
		    (add-to-frame-note-particular-pairs-as-necessary
		      'no-method-for-class
		      method-first-arg-class? name t))
		   (method-error-no-method-for-arg-count?
		    (let ((frame-key
			    (gensym-cons
			      method-first-arg-class? (length arg-types))))
		      (add-to-frame-note-particular-pairs-as-necessary
			'no-method-for-arg-count frame-key name t)
		      (reclaim-gensym-cons frame-key)))
		   (method-error-method-for-class-not-ok?
		    (add-to-frame-note-particular-pairs-as-necessary
		      'method-for-class-not-okay
		      method-first-arg-class? name t))
		   (t
		   ;; Note, not doing analysis of method argument types.
		    nil)))
		((if formal-arg-restp-index
		     (<f (length arg-types) (1-f (length formal-arg-types)))
		     (/=f (length arg-types) (length formal-arg-types)))
		 (setq valid-procedure-call? nil)
		 ;; Issue note about argument length mismatch.
		 (add-to-frame-note-particulars-for-counts
		   'arg-count-mismatch
		   name (length formal-arg-types) (length arg-types)))
		((if formal-return-restp-index
		     (<f (length return-types) (1- (length formal-return-types)))
		     (>f (length return-types) (length formal-return-types)))
		 (setq valid-procedure-call? nil)
		 ;; Issue note about not enough return values.
		 (add-to-frame-note-particulars-for-counts
		   'return-count-mismatch
		   name (length formal-return-types) (length return-types)))
		(stable-procedure-call?
		 (loop for arg-type in arg-types
		       for index from 0
		       for restp = (eq index formal-arg-restp-index)
				 then (or restp (eq index formal-arg-restp-index))
		       for formal-arg-types-tail = formal-arg-types
						 then (if restp
							  formal-arg-types-tail
							  (cdr formal-arg-types-tail))
		       for formal-arg-type = (car formal-arg-types-tail)
		       for formal-arg-kinds-tail = formal-arg-kinds
						 then (if restp
							  formal-arg-kinds-tail
							  (cdr formal-arg-kinds-tail))
		       for kind = (car formal-arg-kinds-tail)
		       for as-handle-p = (eq 'handle kind)
		       for arg-number from 1
		       do
		   (when (and stable-procedure-call?
			      (not (equal arg-type formal-arg-type)))
		     ;; The current argument types and the argument types being
		     ;; depended upon must be EQUAL.
		     (setq valid-procedure-call? nil)))
		 (loop for required-type in return-types
		       for index from 0
		       for restp = (eq index formal-return-restp-index)
				 then (or restp (eq index formal-return-restp-index))
		       for formal-return-types-tail = formal-return-types
						 then (if restp
							  formal-return-types-tail
							  (cdr formal-return-types-tail))
		       for formal-return-type = (car formal-return-types-tail)
		       for return-number from 1
		       do
		   (when (and stable-procedure-call?
			      (not (equal required-type formal-return-type)))
		     ;; The current returns types and the returns types being
		     ;; depended upon must be EQUAL.
		     (setq valid-procedure-call? nil))))
		(t
		 (unless (and (check-for-argument-type-mismatch
				name arg-types formal-arg-types formal-arg-kinds formal-arg-restp-index)
			      (check-for-return-type-mismatch
				name return-types formal-return-types))
		   (setq valid-procedure-call? nil)))))
	(reclaim-gensym-list formal-arg-types)
	(reclaim-gensym-list formal-arg-kinds)
	(reclaim-gensym-list formal-return-types)))
    valid-procedure-call?))

;; Note #1, regarding incomplete method frame notes.  This function is not yet
;; ready to test for incomplete methods.  (See reference to note #1, above.)  We
;; need to consider two things:
;; 1. If an inherited method is incomplete, do we want to continue searching for
;; another inherited method that is not incomplete?  If one is found, should we
;; then not issue a warning?
;; 2. Note that procedures and methods can be made incomplete because a
;; destabilizing change.  But, this change does not cause further analysis of
;; the items referring to the now incomplete, dependent item.  Therefore, we
;; should not report incomplete methods because the caller is not always
;; notified of a change in the (in)complete status.
;; - cpm, 6/2/95

(defun check-valid-method-definition-of-existing-class (name method-first-arg-class? arg-types)
  (let* ((arg-count (length arg-types))
	 (trial-class
	   (or (caar (classes-of-procedure-method name))
	       (return-from check-valid-method-definition-of-existing-class 'class))) ; no methods at all
	 (class-description-of-trial-class
	   (class-description trial-class))
	 (unique-method-or-string?
	   (get-specific-method
	     name
	     (if (and class-description-of-trial-class
		      (or (eq method-first-arg-class? 'item) ; common case
			  (memq method-first-arg-class?
				(class-inheritance-path-internal class-description-of-trial-class))))
		 class-description-of-trial-class
		 (class-description method-first-arg-class?))
	     arg-count
	     nil nil nil)))
    (unless (and unique-method-or-string?
		 (not (text-string-p unique-method-or-string?)))
      ;; Search the inheritance path of all subclass "leaves"
      ;; (subclasses with no inferior classes).  This is done for efficiency reasons.
      (loop for class being each subclass of method-first-arg-class?
	    do (setq unique-method-or-string?
		     (unless (inferior-classes class)
		       (get-specific-method
			 name (class-description class) arg-count
			 nil nil nil)))
	    until (and unique-method-or-string?
		       (not (text-string-p unique-method-or-string?)))))
    (cond ((text-string-p unique-method-or-string?)
	   ;; Either no method or no method with the
	   ;; correct arguments were found.
	   (if (get-specific-methods-for-class-or-superior-class
		 name method-first-arg-class?)
	       'arg-count 'class))
	  ((or (null unique-method-or-string?)
	       (not (framep unique-method-or-string?)))
	   'class)
	  ;; See note #1 at the end of this function.
	  ;; Not yet reporting incomplete methods.
	  ;; - cpm, 6/2/95
	  ;;((not (frame-ok-p unique-method-or-string?))
	  ;; (setq method-error-method-for-class-not-ok? t))
	  (t nil))))


(defun check-for-argument-type-mismatch (name arg-types formal-arg-types formal-arg-kinds formal-arg-restp-index)  
  (loop with valid-procedure-call? = t
	for arg-type in arg-types
	for index from 0
	for formal-arg-types-tail = formal-arg-types
				  then (if restp
					   formal-arg-types-tail
					   (cdr formal-arg-types-tail))
	for formal-arg-type = (car formal-arg-types-tail)
	for formal-arg-kinds-tail = formal-arg-kinds
				  then (if restp
					   formal-arg-kinds-tail
					   (cdr formal-arg-kinds-tail))
	for kind = (car formal-arg-kinds-tail)
	for as-handle-p = (eq 'handle kind)
	for restp = (eq index formal-arg-restp-index)
		  then (or restp (eq index formal-arg-restp-index))
	for arg-number from 1
	unless (or (type-specifications-could-intersect-p
		     arg-type formal-arg-type)
		   (and (type-specification-subtype-p
			  formal-arg-type 'datum)
			(type-specifications-could-intersect-p
			  arg-type
			  (if (procedure-p compiled-item-being-analyzed)
			      (type-specification-returning-datum-type
				formal-arg-type)
			      (type-specification-returning-datum-type-or-unknown
				formal-arg-type))))
		   (type-specifications-could-be-coerced-p
		     arg-type formal-arg-type)
		   (datum-type-specifications-could-be-coerced-p
		     arg-type formal-arg-type)
		   (and (class-type-specification-p formal-arg-type)
			as-handle-p
			(eq arg-type 'integer)))
	  do (let ((arg-key (gensym-cons name arg-number)))
	       (setq valid-procedure-call? nil)
	       (add-to-frame-note-particulars-for-counts
		 'arg-type-mismatch arg-key formal-arg-type arg-type)
	       (reclaim-gensym-cons arg-key))
	finally (return valid-procedure-call?)))

(defun check-for-return-type-mismatch (name return-types formal-return-types)
  (loop with valid-procedure-call? = t
	for required-type in return-types
	for formal-type in formal-return-types
	for return-number from 1
	unless (or (type-specifications-could-intersect-p
		     formal-type required-type)
		   (and (type-specification-subtype-p
			  required-type 'datum)
			(type-specifications-could-intersect-p
			  formal-type
			  (if (procedure-p compiled-item-being-analyzed)
			      (type-specification-returning-datum-type
				required-type)
			      (type-specification-returning-datum-type-or-unknown 
				required-type))))
		   (type-specifications-could-be-coerced-p
		     formal-type required-type)
		   (datum-type-specifications-could-be-coerced-p
		     formal-type required-type))
	  do (let ((return-key (gensym-cons name return-number)))
	       (setq valid-procedure-call? nil)
	       (add-to-frame-note-particulars-for-counts
		 'return-type-mismatch return-key formal-type
		 required-type)
	       (reclaim-gensym-cons return-key))
	finally (return valid-procedure-call?)))


(defun check-for-valid-stable-compile-time-selected-method
    (selected-class method-name first-arg-class arg-types return-types)
  (add-or-delete-as-item-referring-to-name method-name)
  (add-or-delete-as-item-referring-to-name first-arg-class)
  (add-or-delete-as-item-referring-to-name selected-class)
  
  ;; First, test that the compiled item is dependent and that the named item
  ;; is stable.  (This is similar to check-for-unstable-instance-name.)  Then,
  ;; test if the procedure-call is valid.
  (cond
    ((not (block-can-be-dependent-p compiled-item-being-analyzed))
     (unless delete-as-item-referring-to-name?
       (note-independent-item-in-stable-free-reference
	 compiled-item-being-analyzed)))
    (t
     (let* ((first-arg-class-description? (class-description first-arg-class))
	    (method? (and first-arg-class-description?
			  (compile-time-selected-method-p
			    method-name first-arg-class-description?
			    (length arg-types)))))
       (cond
	 ((or (null method?)
	      (not (eq (procedure-method-class method?)
		       selected-class)))
	  (unless delete-as-item-referring-to-name?
	    (note-invalid-stable-hierarchy
	      compiled-item-being-analyzed
	      (slot-value-list method-name first-arg-class (length arg-types)))))
	 (t
	  (let* ((name (get-primary-name-for-frame-if-any method?))
		 (valid-stable-procedure-call?
		   (check-for-valid-procedure-call
		     'stable-procedure-call name
		     arg-types return-types t method?)))
	    (unless delete-as-item-referring-to-name?
	      (unless valid-stable-procedure-call?
		(note-invalid-stable-free-reference
		  compiled-item-being-analyzed name))))))))))




;;; The function `check-for-valid-function-call' takes two arguments, the name
;;; of the function and a list of actual argument types.  This function should
;;; seek an actual user-defined function by that name, and if found verify that
;;; the arguments to be given fit within the arguments required by the
;;; procedure.  Note that we only verify the argument count because functions do
;;; not declare their argument types.

;; This currently only works for user-defined functions.  Consider modifying
;; this for tabular-functions-of-1-args.  Note that system-defined functions
;; already check for the correct number of arguments in the parser.  - cpm,
;; 1/7/93

(defun check-for-valid-function-call (name arg-types)
  (add-or-delete-as-item-referring-to-name name)
  (unless delete-as-item-referring-to-name?
    (let ((instance? nil)
	  (formal-arg-count? nil))
      (setq instance? (get-instance-with-name-if-any 'item name))
      (cond 
	((null instance?)
	 (add-to-frame-note-particulars-list-if-necessary
	   name 'non-existent-instances compiled-item-being-analyzed))
	((and instance?
	      (not (frame-of-class-p instance? 'function-definition))
	      (not (frame-of-class-p instance? 'tabular-function))
	      (not (frame-of-class-p instance? 'foreign-function-declaration)))
	 (add-to-frame-note-particular-pairs-as-necessary
	   'non-existent-instances-of-class 'function-definition name nil)
	 (setq instance? nil))
	((and instance?
	      (not (frame-ok-p instance?)))
	 (add-to-frame-note-particulars-list-if-necessary
	   name 'item-not-ok compiled-item-being-analyzed)
	 (setq instance? nil))
	((frame-of-class-p instance? 'tabular-function-of-1-arg)
	 (setq formal-arg-count? 1))
	(t
	 (setq formal-arg-count? (argument-range name))))
      (when (and instance? formal-arg-count?
		 (/=f (length arg-types) formal-arg-count?))
	;; Issue note about argument length mismatch.
	(add-to-frame-note-particulars-for-counts
	  'arg-count-mismatch
	  name formal-arg-count? (length arg-types))))))
;;




;;; The function `add-to-frame-note-particulars-pair-if-necessary' records for a
;;; frame notes whose particulars consists of a set of pairs a new pair, if that
;;; pair does not already appear in the particulars.

;;; The data structure used is an alist keyed by the first of the pair.  The
;;; rest of the entries in that alist is a set of the second of the pair.  This
;;; routine works only in the dynamic scope of consistency checking, i.e.  it
;;; modifies the frame notes of the compiled-item-being-analyzed.

;;; The frame note writer for these frame notes usually writes notes that using
;;; the plural when possible, i.e.  "the class widget does not have alpha and
;;; beta attributes." In this example making the pair key the class name.

;; Modified to use EQUAL test on the key and value, instead of an EQ test (using
;; ASSOC and MEMQ).  Also, added a flag that specifies whether the pair-key and
;; pair-value should be copied, if added to the frame-notes.  - cpm, 8/26/94

(defun add-to-frame-note-particular-pairs-as-necessary
       (frame-note pair-key pair-value copy-pair-key-and-value?)
  (let* ((existing-particulars-alist
	   (get-particulars-of-frame-note-if-any 
	     frame-note compiled-item-being-analyzed))
	 (entry-for-key?
	   (assoc-equal pair-key existing-particulars-alist))
	 (trigger-update-of-representations?
	   (cond 
	     ((null existing-particulars-alist)
	      (add-to-frame-note-particulars-list-if-necessary
		(slot-value-list
		  (if copy-pair-key-and-value?
		      (copy-for-slot-value pair-key)
		      pair-key)
		  (if copy-pair-key-and-value?
		      (copy-for-slot-value pair-value)
		      pair-value))
		frame-note
		compiled-item-being-analyzed)
	      nil)
	     ((null entry-for-key?)
	      (nconc existing-particulars-alist
		     (slot-value-list
		       (slot-value-list
			 (if copy-pair-key-and-value?
			     (copy-for-slot-value pair-key)
			     pair-key)
			 (if copy-pair-key-and-value?
			     (copy-for-slot-value pair-value)
			     pair-value))))
	      T)
	     ((null (member-equal pair-value (rest entry-for-key?)))
	      (slot-value-push
		(if copy-pair-key-and-value?
		    (copy-for-slot-value pair-value)
		    pair-value)
		(rest entry-for-key?))
	      T))))
    (when trigger-update-of-representations?
      (add-frame-note
	frame-note compiled-item-being-analyzed existing-particulars-alist
	nil nil))))




;;; The function `add-to-frame-note-particulars-for-counts' records frame notes
;;; for patterns of notes where a slot value (comparable with equal) is the key,
;;; a slot-value is given which is associated with the key, and another slot
;;; value is then given one of a list of values that may be associated with that
;;; key.  This function will uniquely add new lists for unique keys, and will
;;; add elements to the list for a particular key where necessary.  Note that
;;; the arguments to this function are copied, not reclaimed or incorporated
;;; into the frame note.

;;; This function is currently used for the arg-count-mismatch and
;;; return-count-mismatch notes, where the key is a symbol, the associated value
;;; with the key is a fixnum, and the elements of the list of values associated
;;; with that key are fixnums.  However, this could be used in situations where
;;; the fixnums are replaced by any slot value.

;;; The format of the resulting frame note particulars are:
;;;   ((<key> <associated-slot-value> . (<listed-slot-value> ...)) ...)

(defun add-to-frame-note-particulars-for-counts
       (frame-note key associated-slot-value listed-slot-value)
  (let* ((existing-particulars-alist
	   (get-particulars-of-frame-note-if-any
	     frame-note compiled-item-being-analyzed))
	 (entry-for-key?
	   (assoc-equal key existing-particulars-alist))
	 (trigger-update-of-representations?
	   (cond 
	     ((null existing-particulars-alist)
	      (add-to-frame-note-particulars-list-if-necessary
		(slot-value-list
		  (copy-for-slot-value key)
		  (copy-for-slot-value associated-slot-value)
		  (copy-for-slot-value listed-slot-value))
		frame-note
		compiled-item-being-analyzed)
	      nil)
	     ((null entry-for-key?)
	      (nconc existing-particulars-alist
		     (slot-value-list
		       (slot-value-list
			 (copy-for-slot-value key)
			 (copy-for-slot-value associated-slot-value)
			 (copy-for-slot-value listed-slot-value))))
	      t)
	     ((null (member-equal listed-slot-value (cddr entry-for-key?)))
	      (setf (cdr (last entry-for-key?))
		    (slot-value-list (copy-for-slot-value listed-slot-value)))
	      t))))
    (when trigger-update-of-representations?
      (add-frame-note
	frame-note compiled-item-being-analyzed existing-particulars-alist
	nil nil))))

;;

;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module CHAINING
;;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;;; All Rights Reserved. 

;;;; Jim Allard

;;;; Major sections in this module:
;;;;   Event Detectors
;;;;   Forward Chaining
;;;;   Backward Chaining
;;;;   Movement Chaining
;;;;   Existential Chaining
;;;;   Variable Failure Chaining
;;;;   True Value Update
;;;;   Relation Chaining
;;;;   NUPEC Synchronization Chaining


;;;; Properties and Forward References for Chaining



;;; The properties `forward-chaining-list' and `backward-chaining-list' are
;;; KB-specific symbol properties for forward and backward chaining lists.

(def-kb-specific-property-name forward-chaining-list)
(def-kb-specific-property-name cached-class-forward-chaining-list)
(def-kb-specific-property-name backward-chaining-list)
(def-kb-specific-property-name cached-class-backward-chaining-list)

(declare-forward-reference send-ws-representations-item-moved function)
(declare-forward-reference generate-and-schedule-rule-instances function)
(declare-forward-reference backward-chaining-precedence-function function)
(declare-forward-reference remove-request-for-rule-instance-invocation function)
(declare-forward-reference rule-chaining-links-function function)

(declare-forward-reference trigger-event-detector function)	; DISPLAYS

(declare-forward-reference
  update-backward-chaining-displays-function function)	; EXPLAIN

(declare-forward-reference
  backward-chaining-displays variable)	; EXPLAIN

(declare-forward-reference
  write-list-in-chicago-style function)		; GRAMMAR6

(declare-forward-reference initializing-items-needing-initialization variable)




;;;; Forward and Backward Chaining




;;; Within G2, rules may be invoked through forward chaining and backward
;;; chaining on all variable types.  `Forward chaining' implies that the values
;;; which are dependant on another value will be updated when the underlying
;;; value is changed through the invocation of any rules which refer to the
;;; underlying value.  `Backward chaining' implies that if the value of a
;;; variable is requested, the system will attempt to supply a value for that
;;; variable by invoking rules which could set that value.

;;; The mechanisms which implement forward chaining are in:
;;;
;;; 1. update-forward-chaining-lists, 
;;; 2. note-names-and-info-for-forward-chaining, 
;;; 3. invoke-rules-for-forward-chaining, and
;;; 4. put-current-value.
;;;
;;; The functions for backward chaining are:
;;;
;;; 1. update-backward-chaining-lists,
;;; 2. note-names-and-info-for-backward-chaining,
;;; 3. invoke-rules-for-backward-chaining, and
;;; 4. compute-newer-value-of-variable.

;;; The forward chaining mechanisms have been used more widely now than had been
;;; anticipated.  At the heart of chaining are the mechanisms that trace back
;;; from a variable to statements which may refer to it via a designation and
;;; need to be notified when a change has to this variable has occurred.  The
;;; major extension to rule update chaining has been to include event chaining
;;; to whenever rules for a variety of variable and entity affecting conditions.
;;; The second extension to chaining has been to include a function calling
;;; update facility.  This is currently used for button and slider updating, but
;;; has been designed in a generic way to attempt to fill any need for further
;;; updating facilities based on variable value changes.  Note that a large
;;; portion of the documentation here, especially that analyzing chaining cases,
;;; has not been updated to reflect these new uses of the chaining facilities,
;;; since the main message of these comments still applies to the new forms of
;;; chaining.  Also, there ain't been a whole lota time to go through and clean
;;; it up.  The forward chaining style mechanisms for the invocation of rules
;;; based on the occurances of events are:
;;;
;;; 1. invoke-rules-for-movement-chaining,
;;; 2. invoke-rules-for-failure-chaining,
;;; 3. install-true-value-update, and
;;; 4. invoke-update-function-for-put-has-no-current-value.

;;; There are two major parts to the code in this file.  First is the code which
;;; updates the chaining lists to reflect new designation references.  Second is
;;; the code which gets notified of changes to a variable or frame and which
;;; searches the chaining lists to find chaining links which must be followed to
;;; designation containing rules or update functions and then schedules those
;;; rules and update functions for invocation.






;;;; Forward Chaining




;;; The following cases specify the behavior of the forward chaining mechanism.
;;; For each given rule case the following information is listed: an example of
;;; the case, the keyword which will be used to store the forward chaining link,
;;; constraints that rules on the list of that keyword must match before the
;;; forward chainer will fire them, the focal role (if any) which will be used
;;; in invoking that rule, and the object (if any) which will be focused upon
;;; when invoking that rule.

;;; Note that the cases for named attributes below should be extended to include
;;; that fact that objects may be nested at arbitrary levels within attributes
;;; of attributes of objects.  In this case, the chaining keyword should be the
;;; name of the outermost attribute, the focal role should be the class naming
;;; symbol of the outermost non-attribute role, or nil if there is attribute
;;; nesting all the way up to a name.

;;; Also note that "the foo of any bar" used to mean "the foo connected to any
;;; bar" as well as having its current meaning of "the foo attribute of any
;;; bar".  This meaning has been removed in release 1.1.  Therefore, the
;;; chaining mechanisms need not handle the case of a "named role" of anything.
;;; This means that one less chaining link need be generated per attribute
;;; terminated designation.






;;;; Logical Value Chaining Cases




;;; Case: Named Logical Variable
;;; Example: "if foo and..."
;;; Keyword: Variable Name, "foo"
;;; Constraints: Senses match, link is from a name reference.
;;; Focal Role: nil
;;; Focal Object: nil

;;; Case: Named Role
;;; Example: "if any alarm-variable then..."
;;; Keyword: Naming Role, "alarm-variable"
;;; Constraints: Senses match, link is not from a name reference.
;;; Focal Role: Naming Role, "alarm-variable"
;;; Focal Object: Variable, the "alarm-variable"

;;; Case: Named Attribute of Named Parent
;;; Example: "if the baz of bar-18 and..."
;;; Keyword: Attribute Name, "baz"
;;; Constraints: Senses match, parent names match.
;;; Focal Role: none
;;; Focal Object: none

;;; Case: Named Attribute of Role Named Parent
;;; Example: "if the uffda of any frobitz of any widget and..."
;;; Keyword: Attribute Name, "uffda"
;;; Constraints: Senses match, and if focal role "frobitz" is a class,
;;;   parent object of variable being set must be an instance of that
;;;   class.
;;; Focal Role: Parent Role Name, "frobitz"
;;; Focal Object: Parent entity of variable being set, the "frobitz"

;;; Case: Non-atomic Role of Named Parent
;;; Example: "if the uffda at the spout of fromage-23 and..."
;;; Keyword: Class name of the connected object, "uffda"
;;; Constraints: Senses match, the variable being set is an instance of the
;;;   class "uffda", and the designation is invertible.
;;; Focal Role: Class in non-atomic role, "uffda"
;;; Focal Object: Variable being set, the "uffda"

;;; Case: Non-atomic Role of Role Named Parent
;;; Example: "if the uffda at the spout of any frobitz then..."
;;; Keyword: Class name of connected object, "uffda"
;;; Constraints: Senses match, the variable being set is an instance of the
;;;   class "uffda", and the designation is invertible.
;;; Focal Role: Class of non-atomic role, "uffda"
;;; Focal Object: Variable being set, the "uffda"

;;; Case: Named Attribute of Non-atomic Role Named Parent
;;; Example: "if the uffda of the frobitz at an input to any fromage then..."
;;; Keyword: Named Attribute, "uffda"
;;; Constraints: Senses match, and if the atomic naming element
;;;   mentioned in the non-atomic role (the "frobitz") is a class, the
;;;   parent of the variable being set is an instance of that class.
;;; Focal Role: Class in the non-atomic role, "frobitz"
;;; Focal Object: Parent of the variable being set, the "frobitz"






;;;; Symbolic Value Chaining Cases




;;; Case: Named Symbolic Variables
;;; Example: "if system-state is ok then..."
;;; Keyword: Variable Name, "system-state"
;;; Constraints: Same value and positive sense, or different value and
;;;   negative sense, link is from a name reference.
;;; Focal Role: none
;;; Focal Object: none

;;; NOTE:  There is no way of storing the set of possible values for symbolic
;;; variables.  Therefore, all references to this variable with a negative sense
;;; will be chained upon, instead of just references within the possible value
;;; set.

;;; Case: Implied Attribute of Named Role
;;; Example: "if any manual-valve is closed then..."
;;; Keyword: Role Name, "manual-valve"
;;; Constraints: Same value and sense, or differing value in the set of
;;;   possible values for parent class and attribute and negative sense,
;;;   link is not from a name reference.
;;; Focal Role: Role Name, "manual-valve"
;;; Focal Object: Parent Object, the "manual-valve"

;;; Case: Named Attributes of Named Parents
;;; Example: "if the temp-description of furnace-23 is boiling then..."
;;; Keyword: Attribute Name, "temp-description"
;;; Constraints: Parent names match, and same value and sense, or
;;;   differing value in set of possible values for parent class and
;;;   attribute, and negative sense.
;;; Focal Role: none
;;; Focal Object: none

;;; Case: Named Attribute of Role Named Parent
;;; Example: "if the level-indicator of any tank is full then..."
;;; Keyword: Named Attribute, "level-indicator"
;;; Constraints: If focal role (e.g., "tank") is a class, then parent
;;;   must be an instance of it, and sense and values match, or both
;;;   senses and values differ but value is in the set of possible values.
;;; Focal Role: Parent Role, "tank"
;;; Focal Object: Parent Object of Variable, the "tank"

;;; Case: Implied Attribute Values of Named Parents
;;; Example: "if furnace-42 is hot then..."
;;; Keyword: Parent Names, "furnace-42"
;;; Constraints: Same value and positive sense, or differing value in
;;;   set of possible values for parent class and attribute and negative
;;;   sense.
;;; Focal Role: none
;;; Focal Object: none

;;; Case: Implied Attributes of Role Named Parents of Named Grandparents
;;; Example: "if the valve of tank-42 is broken then..."
;;; Keyword: Parent Role, "valve"
;;; Constraints: Same sense and value, or opposite sense and differing
;;;   value which is in the set of possible values for the parent
;;;   attribute and class, and the designation is invertible.
;;; Focal Role: Parent Class, "valve"
;;; Focal Object: Parent Instance, the "valve"

;;; Case: Implied Attributes of Role Named Parents of Role Named Grandparents
;;; Example: "if the valve of any tank is broken then..."
;;; Keyword: Parent Role, "valve"
;;; Constraints: Same sense and value, or opposite sense and differing
;;;   value which is in the set of possible values for the parent
;;;   attribute and class, and the designation is invertible.
;;; Focal Role: Parent Class, "valve"
;;; Focal Object: Parent Instance, the "valve"






;;;; Cons Storage Allocation




;;; There used to be a set of functions written here for installation cons
;;; management, but this has been changed to use the defconser facility defined
;;; in utilities.

(defconser installation chaining)






;;;; Forward Chaining Link Format




;;; Forward chaining links are structures stored on forward chaining lists which
;;; are used to represent a rule or update function which needs to be called
;;; when some frame changes in a way represented in the forward-link-sense.

;;; Forward chaining links have four elements: recipient, the designation in the
;;; recipient which generated this link, the symbolic value if this is a rule,
;;; and the sense.  The recipient will always be either a rule instance, or else
;;; an instance of the structure true-value-update-recipient.  Forward links are
;;; allocated with `make-forward-chaining-link' and deallocated with
;;; `reclaim-forward-chaining-link'.  Note that any contents of the forward link
;;; designation slot will be reclaimed with reclaim-installation-tree on
;;; reclamation of a forward link, and that if the recipient is an update list,
;;; the spine of allocation conses will be reclaimed.

;(def-structure (forward-chaining-link
;		 (:constructor make-forward-chaining-link-1
;			       (forward-link-recipient
;				 forward-link-designation
;				 forward-link-focus
;				 forward-link-focus-local-name
;				 forward-link-symbolic-value
;				 forward-link-sense
;				 forward-link-second-designation
;				 forward-link-second-focus
;				 forward-link-second-focus-local-name)))
;  (forward-link-recipient nil :reclaimer reclaim-if-update-recipient)
;  (forward-link-designation nil :reclaimer reclaim-installation-tree)
;  forward-link-focus
;  forward-link-focus-local-name
;  forward-link-symbolic-value
;  forward-link-sense
;  (forward-link-second-designation nil :reclaimer reclaim-installation-tree)
;  forward-link-second-focus
;  forward-link-second-focus-local-name)

(def-class (forward-chaining-link dependent-frame define-predicate)
  (forward-link-recipient nil vector-slot system save)
  (forward-link-designation nil vector-slot system save)
  (forward-link-focus nil vector-slot system save)
  (forward-link-focus-local-name nil vector-slot system save)
  (forward-link-symbolic-value nil vector-slot system save)
  (forward-link-sense nil vector-slot system save)
  (forward-link-second-designation nil vector-slot system save)
  (forward-link-second-focus nil vector-slot system save)
  (forward-link-second-focus-local-name nil vector-slot system save))

#-chestnut-trans
(defun-simple forward-chaining-link-p-function (link)
  (forward-chaining-link-p link))

#-chestnut-trans
(defun-simple forward-link-focus-function (link)
  (forward-link-focus link))

#-chestnut-trans
(defun-simple forward-link-second-focus-function (link)
  (forward-link-second-focus link))

;;; The macro `reclaim-forward-chaining-link' merely deletes the frame.

(defmacro reclaim-forward-chaining-link (forward-chaining-link)
  `(delete-frame ,forward-chaining-link))




;;; Forward links are equal if their components are equal.  Note that there is a
;;; special equality test for forward link recipients.

(defun equal-forward-chaining-link (link1 link2)
  (and (or (eq (forward-link-recipient link1)
	       (forward-link-recipient link2))
	   (equal-true-value-update-recipients
	     (forward-link-recipient link1)
	     (forward-link-recipient link2)))
       (equal (forward-link-designation link1)
	      (forward-link-designation link2))
       (equal (forward-link-focus link1)
	      (forward-link-focus link2))
       (equal (forward-link-focus-local-name link1)
	      (forward-link-focus-local-name link2))
       (equal (forward-link-symbolic-value link1)
	      (forward-link-symbolic-value link2))
       (equal (forward-link-sense link1)
	      (forward-link-sense link2))
       (equal (forward-link-second-designation link1)
	      (forward-link-second-designation link2))
       (equal (forward-link-second-focus link1)
	      (forward-link-second-focus link2))
       (equal (forward-link-second-focus-local-name link1)
	      (forward-link-second-focus-local-name link2))))




;;; The `true-value-update' structure is a forward chaining link recipient which
;;; calls a function on variable value changes.  It contains a function to be
;;; called, a frame to pass as an argument, and one further argument, which may
;;; be whatever the installer of the update function chooses.

;(def-structure (true-value-update-recipient
;		 (:constructor make-true-value-update-recipient-1
;		  (true-value-update-function
;		    true-value-update-frame
;		    true-value-update-argument)))
;  true-value-update-function
;  true-value-update-frame
;  (true-value-update-argument nil :reclaimer reclaim-installation-tree))

(def-class (true-value-update-recipient dependent-frame define-predicate)
  (true-value-update-function nil vector-slot system save)
  (true-value-update-frame nil vector-slot system save)
  (true-value-update-argument nil vector-slot system save))

(defmacro reclaim-true-value-update-recipient (recipient)
  `(delete-frame ,recipient))

(defun make-true-value-update-recipient
       (true-value-update-function
	true-value-update-frame
	true-value-update-argument)
  (let ((new-frame (make-frame 'true-value-update-recipient)))
    (let* ((current-block-of-dependent-frame 'dependent-frame-has-no-owner))
      (setf (true-value-update-function new-frame) true-value-update-function)
      (setf (true-value-update-frame new-frame) true-value-update-frame)
      (setf (true-value-update-argument new-frame)
	    (copy-for-slot-value true-value-update-argument)))
    new-frame))

(def-class-method copy-frame (true-value-update-recipient)
  (make-true-value-update-recipient
    (true-value-update-function true-value-update-recipient)
    (true-value-update-frame true-value-update-recipient)
    (true-value-update-argument true-value-update-recipient)))




;;; The function `reclaim-if-update-recipient' is called on the value of the
;;; recipient slot of forward chaining links upon link reclamation.  The value
;;; of this slot will be either a rule frame or a list of installation conses
;;; whose first element is a symbol naming an updating function.  If the value
;;; passed here is an update list, then reclaim the conses from this list.

;(defun reclaim-if-update-recipient (forward-link-recipient)
;  (if (true-value-update-recipient-p forward-link-recipient)
;      (reclaim-true-value-update-recipient forward-link-recipient)))

;; Only used in the forward link structure previously.  Will now be
;; handled by reclaim-slot-value.  -jra 6/5/91




;;; The function `equal-true-value-update-recipient' takes two objects and
;;; returns whether they are both true-value-update-recipients and whether their
;;; components are equal.

(defun equal-true-value-update-recipients (thing1 thing2)
  (and (true-value-update-recipient-p thing1)
       (true-value-update-recipient-p thing2)
       (equal (true-value-update-function thing1)
	      (true-value-update-function thing2))
       (eq (true-value-update-frame thing1)
	   (true-value-update-frame thing2))
       (equal (true-value-update-argument thing1)
	      (true-value-update-argument thing2))))



;;; The function `copy-if-true-value-update-recipient' takes a thing, and will
;;; return a copy of it if the thing is an update recipient.  If not, it returns
;;; the thing.

;(defun copy-if-true-value-update-recipient (thing)
;  (if (true-value-update-recipient-p thing)
;      (make-true-value-update-recipient
;	(true-value-update-function thing)
;	(true-value-update-frame thing)
;	(true-value-update-argument thing))
;      thing))

;; Obsolete.  -jra 6/5/91




;;; The dependent frame creator function `make-forward-chaining-link'
;;; takes all components of a forward chaining link, copies the
;;; recipient and designation if necessary, and returns a new link with
;;; the given components.

(defun make-forward-chaining-link
       (forward-link-recipient
	forward-link-designation
	forward-link-focus
	forward-link-focus-local-name
	forward-link-symbolic-value
	forward-link-sense
	&optional
	(forward-link-second-designation nil)
	(forward-link-second-focus nil)
	(forward-link-second-focus-local-name nil))
  (let ((new-frame (make-frame 'forward-chaining-link)))
    (let ((current-block-of-dependent-frame 'dependent-frame-has-no-owner))
      (setf (forward-link-recipient new-frame)
	    (copy-for-slot-value forward-link-recipient))
      (setf (forward-link-designation new-frame)
	    (make-simple-designation-slot-value-copy forward-link-designation))
      (setf (forward-link-focus new-frame)
	    forward-link-focus)
      (setf (forward-link-focus-local-name new-frame)
	    forward-link-focus-local-name)
      (setf (forward-link-symbolic-value new-frame)
	    forward-link-symbolic-value)
      (setf (forward-link-sense new-frame)
	    forward-link-sense)
      (setf (forward-link-second-designation new-frame)
	    (make-simple-designation-slot-value-copy
	      forward-link-second-designation))
      (setf (forward-link-second-focus new-frame)
	    forward-link-second-focus)
      (setf (forward-link-second-focus-local-name new-frame)
	    forward-link-second-focus-local-name))
    new-frame))

(def-class-method copy-frame (forward-chaining-link)
  (make-forward-chaining-link
    (forward-link-recipient forward-chaining-link)
    (forward-link-designation forward-chaining-link)
    (forward-link-focus forward-chaining-link)
    (forward-link-focus-local-name forward-chaining-link)
    (forward-link-symbolic-value forward-chaining-link)
    (forward-link-sense forward-chaining-link)
    (forward-link-second-designation forward-chaining-link)
    (forward-link-second-focus forward-chaining-link)
    (forward-link-second-focus-local-name forward-chaining-link)))






;;;; Event Detectors




;;; This section implements functions for registering, detecting, signalling
;;; detection of, and reclaiming event detectors.  Event detectors are data
;;; structures registered directly on frames to detect an event on an individual
;;; object.  The events detected are the same as those detected within the
;;; antecedents of whenever rules.  They differ in that whenever rules are
;;; implemented by registering forward chaining links on property lists of
;;; symbols which syntacticly describe a pattern of reference, allowing chaining
;;; to a whenever to be triggered when an event is detected across classes of
;;; objects.  This occurs without having to individually mark each object.  In
;;; procedures, the wait until event statement does not have a syntactic pattern
;;; to register detectors on, and so must resort to marking frames with
;;; detectors individually.  These event detectors implement markers on
;;; individual frames.

;;; There are different types of event detectors.  Each type is a symbol.  The
;;; typing is included entirely so that the functions which trigger events can
;;; quickly detect which registered event detectors on a frame should be
;;; triggered and which should not.  The type is held in a slot of the event
;;; detector.

;;; Event detectors always have a consumer, which is a code-body-invocation
;;; which executed a wait until statement and registered the event detector.
;;; When an event occurs, the response to the event is to schedule the consumer
;;; for execution.  Other kinds of event consumers and reponses to events could
;;; be implemented in the future, but for now, this is it.

;;; Event detectors have another slot for holding extra information.  If a
;;; particular kind of event needs to register information to further filter
;;; which events will trigger this detector, this should be put here.  The
;;; contents of this slot are particular to each type of event detector.

;;; Event detectors are held in the registered-event-detectors slot of blocks,
;;; and are an eval cons list of event detector structures.  A list is also kept
;;; in the consumer all events which it has registered.  The structure has
;;; pointers to both the monitored block and the consumer, so that tranversals
;;; can be made through the event in either direction.  The funcalled
;;; instructions register event detector and clear event detectors manipulate
;;; event detectors, and functions which search for event detectors and trigger
;;; them are included here in the chaining file.  Documentation for each of the
;;; kinds of events is kept in the stack-acts file, near the funcalled
;;; instructions.

;;; The structure `event-detector' holds individual event detectors.

(def-structure (event-detector
		 (:constructor
		   make-event-detector
		   (event-detector-type
		     event-detector-monitored-block
		     event-detector-consumer
		     event-detector-extra-information)))
  event-detector-type
  event-detector-monitored-block
  event-detector-consumer
  event-detector-extra-information)


;;;






;;;; Forward Chaining Algorithms




;;; The function `invoke-rules-for-forward-chaining' is called from
;;; put-current-value to cause `forward chaining' when new values are placed
;;; into variables.  It takes as arguments the variable which is receiving a new
;;; value, the new value, and the data type of the value.  All variable data
;;; types are now eligible for forward chaining.

;;; The ideal specification for this code is to invoke once all those rules
;;; which can reference the variable being modified, and no rules which do not
;;; reference it.  This ideal is approached in this code by ensuring that all
;;; rules that do reference the variable will be invoked, and as few rules as
;;; possible which do not reference it be invoked, given "a reasonable amount of
;;; work" to filter out the non-referencers.  This relaxation of specification
;;; can be made under the assumption that rule compilations themselves verify
;;; all parent role unifications, that the rule invocation mechanism will insure
;;; that the same rule instance will not be scheduled to occur more than once,
;;; and that extraneous rule invocations will have no effect.  A reasonable
;;; amount of work to filter out non-references is considered to be insuring
;;; that an invoked rule appears to reference the given variable within the role
;;; referencing the variable, that any attribute parent roles can reference a
;;; parent of the variable, and that the referencing designation is invertible.
;;; Parent here means an object which reaches the variable through an attribute
;;; or other role.  A designation is invertible when it is a name, or when its
;;; primary role has an inverse role value server.  Named-by is an example of a
;;; non-invertible role.







;;;; Forward Chaining Algorithm for Logical Variables




;;; In the following discussion `sense for forward chaining on logical
;;; variables' refers to whether or not the antecedant of a given rule requires
;;; true or false for a particular variable in order to fire.  `Matching sense'
;;; means that either the stored sense is set to 'either, or if a logical
;;; variable is being set to truth, the stored sense for that rule is positive
;;; (the rule antecedant satisfies on truth for that variable), or if the
;;; variable is being set to falsity the stored sense for that rule is negative.
;;; Note that positive sense means the sense must be EQ to T, as opposed to
;;; non-null.  This restriction is imposed since event senses, such as
;;; receives-a-value and is-moved, are non-null but should not match here.
;;; Also, in the following discussion the term parent role means the domain of
;;; the designation stored in a forward chaining link.

(def-substitution-macro logical-sense-matches-p
			(value-sense link-sense chaining-as-well-as-events?)
  (or (and chaining-as-well-as-events?
	   (or (eq link-sense 'either)
	       (eq value-sense link-sense)))
      (eq link-sense 'receives-a-value)
      (eq link-sense 'loses-its-value)))




;;; The following algorithm is used to find rules which will be invoked for
;;; forward chaining on logical variables.

;;; If the variable being set has a name, find the forward chaining list for
;;; that name and invoke with a null focal role all rules which have
;;; designations which are this name and whose sense matches the new value.

;;; Next, find the parent object and attribute for this variable, if there is
;;; any.  Find the forward chaining list for the attribute and do the following
;;; for each rule entry within it.  For each attribute role in the domain
;;; of the link designation of the rule entry, verify that the parent itself has
;;; a parent and that its attribute matches the attribute found in the link.
;;; Iteratively perform this step for each attribute type role in the stored
;;; designation, replacing the parent with each parent found.  If the attribute
;;; nesting in the designation and the parent nesting in the objects do not
;;; match, then discard this rule entry.  If the entry matches this criteria,
;;; then if the sense matches and if it satisfies any of the three following
;;; criteria, invoke its rule:  the rule's parent role contains a parent name
;;; which matches the name of the parent of the variable being set, the rule's
;;; parent role is non-null and has an atomic naming element which is not a
;;; class, or the rule's parent role has an atomic class element and the parent
;;; of the variable being set is an instance of that class.  If a rule is
;;; invoked after a name match, use a null focal role, but if it is invoked
;;; through either of the latter two criteria, invoke the rule with the atomic
;;; naming element as the focal role and the parent as the focal object.

;;; Finally, for each class in the class inheritance path of the variable up to
;;; and including the class "entity", find the class' forward chaining list and
;;; do the following for each rule entry in those lists.  Invoke those rules
;;; whose sense matches and whose designation is not symbolic, is invertible,
;;; and whose outermost role is not an attribute.  All of the rules invoked here
;;; should use the class whose forward chaining list the rule was on as the
;;; focal role, and the variable as the focal object.

;;; Note that forward chaining links to designation in a rule will only be
;;; generated when the designation is invertible to start with, so at run time
;;; the above algorithm need not check that the designation is invertible.  Also
;;; note that the restriction that the outermost role not be an attribute is to
;;; avoid extraneous chaining in the case where a class name of the variable
;;; collides with an attribute name of some object.





;;;; Forward Chaining Algorithm for Symbolic Variables




;;; In the following discussion `sense for forward chaining on symbolic
;;; variables' refers to whether or not the antecedant of a given rule requires
;;; the presense or absence of a particular symbolic value for a variable in
;;; order to fire.  Matching sense depends on whether the designation being
;;; tested is in reference to the variable being set or to the parent of the
;;; variable (the implied attribute case).

;;; When the designation is to the variable which is being set, then matching
;;; sense means that if a symbolic variable is being set to a new symbolic
;;; value, the stored value for that rule matches the new value and the stored
;;; sense is positive, or the stored value differs from the new value and the
;;; sense is negative or the sense is either.  If a set of possible values is
;;; available, then there is further restriction on the negative and either
;;; sense case, in that the new value must be a member of the set of possible
;;; values.  If the sense is :receives-a-value, then sense matches when the
;;; designation is directly to the variable (as opposed to the parent).

;;; NOTE of implementation choice.  If the sense is positive, the new value and
;;; stored values match, but the new value is not a member of an available set
;;; of possible values, then we are allowing sense to match, though we might
;;; have decided to NOT have the sense match.  We are assuming that in this
;;; case, the set of possible values is in error, and so we'll allow the forward
;;; chain to be completed.  In this case a level 1 warning message is being
;;; issued to the user, in other code.

;;; When the designation of the link is to the parent of variable, the new value
;;; must be within the set of possible values to match.  If it is within the set
;;; of possible values, then if the sense is positive, the new value must match
;;; the stored value, if the sense is negative the new value must differ from
;;; the stored value.  There are no implied attribute references allowed for a
;;; sense of either.  Note that :receives-a-value is not a legal sense for the
;;; case where the link denotes the parent of the variable.

;;; NOTE of implementation choice.  For interpreted rules, we could allow the
;;; EITHER chaining case for implied attributes (references to parents).
;;; However, the choice has been made to NOT allow either, since in the final
;;; compiled version of G2 we would like to resolve implied attributes at
;;; COMPILE time of rules, rather than run time.  Compile time resolution would
;;; allow us to eliminate all of the implied attribute chaining computation
;;; here, and would make compiled KBs faster.  Rather than allow EITHER chaining
;;; for interpreted rules and not allow it for compiled rules, we have made the
;;; choice to not allow it at all, in anticipation of the performance advantage
;;; of compile time resolution of implied attributes.  -jra & cpm 4/28/90

;;; This is implemented in the substitution macro `symbolic-sense-matches-p'.

(def-substitution-macro
  symbolic-sense-matches-p
  (designation-to-parent? new-value possible-values stored-value sense
			  chaining-as-well-as-events?)
  (if designation-to-parent?
      (and chaining-as-well-as-events?
	   (or (and (eq sense t)
		    (eq new-value stored-value))
	       (and (null sense)
		    (neq new-value stored-value)))
	   (memq new-value possible-values))
      (or (eq sense 'receives-a-value)
	  (eq sense 'loses-its-value)
	  (and chaining-as-well-as-events?
	       (or (and (eq sense t)
			(eq new-value stored-value))
		   (and (or (eq sense 'either)
			    (and (null sense)
				 (neq new-value stored-value)))
			(or (null possible-values)
			    (memq new-value possible-values))))))))



;;; Changes were made to the sense matching algorithm.  There was a bug in that
;;; symbolic variables which had symbolic attributes were inappropriately
;;; getting forward chaining when the parent symbolic variable was referenced in
;;; a whenever rule.  After further analysis of the algorithm the following
;;; changes were implemented.  1) Receives a value is never an appropriate sense
;;; when chaining to a parent designation.  Receives a value used to always
;;; match sense, whether the designation was to the variable itself or to the
;;; parent.  2) In the parent designation case, the new value always must be a
;;; member of the given possible values.  It used to be that when the new value
;;; and stored value matches, and when the sense was T, that sense would match,
;;; even if the new value was not a member of the possible values list.  3)
;;; There is a further restriction on the either sense case, that the new value
;;; must be a member of the possible values, if possible values are supplied.
;;; It used to match sense for either when the new value was not a member of a
;;; given set of possible values, even though that was required for the NIL
;;; sense case.  -jra & cpm 4/28/90

;;; The following algorithm is used to find rules which will be invoked for
;;; forward chaining on symbolic variables.

;;; If the variable being set has a name, find the forward chaining list for
;;; that name and invoke with a null focal role those rules whose link was
;;; generated from a name reference and whose sense matches.

;;; Next, for each class in the class inheritance path of the variable up to but
;;; not including the class "entity", find the forward chaining list for the
;;; class and do the following for each rule entry in those lists.  Invoke those
;;; rules whose sense matches, whose designation is invertible, but is not a
;;; name reference nor has an outermost role which is an attribute.  All rules
;;; invoked from these lists should use the list's class name as the focal role,
;;; and the variable as the focal object.

;;; Next, find the parent object and attribute for this variable, if there is
;;; any.  Find the forward chaining list for the attribute and do the following
;;; for each rule entry within it.  For each attribute role in the domain of the
;;; link designation of the rule entry, verify that the parent itself has a
;;; parent and that its attribute matches the attribute found in the link.
;;; Iteratively perform this step for each attribute type role in the stored
;;; designation, replacing the parent with each parent found.  If the attribute
;;; nesting in the designation and the parent nesting in the objects do not
;;; match, then discard this rule entry.  Then, invoke those rules whose sense
;;; matches and which satisfy any of the following three criteria:  the rule's
;;; parent role contains a proper name that matches the name of the parent of
;;; the variable, the rule's parent role is non-null and has an atomic naming
;;; element that is not a class, or the rule's parent role has an atomic class
;;; element and the parent of the variable is an instance of that class.  If a
;;; rule is invoked through a name match, it should have a null focal role,
;;; otherwise its focal role should be the atomic naming element of the parent
;;; role, and the variable's parent object should be used as the focal object.

;;; Next, if the variable has a parent object and that object has a name, find
;;; the forward chaining list of that name and invoke with a null focal role
;;; those rules whose links were from name references and whose sense matches.

;;; Next, if the variable has a parent object, for each class in the class
;;; inheritance path of the parent, find the forward chaining list for the class
;;; and do the following for each rule entry in those lists.  Invoke those rules
;;; whose sense matches, and whose designation is invertible, is not a direct
;;; name reference, and does not have an outermost role which is an attribute.
;;; All rules invoked from these lists should use the class from whose list the
;;; entry came as the focal role and the parent object as the focal object.



;;;; Forward Chaining Algorithm for Variables Other than Logical or Symbolic


;;; In the following discussion `sense for forward chaining on general
;;; variables' means no filtering at all in the chaining case, since there are
;;; no filtering mechanisms that we have defined for predetermining boundaries
;;; on generalized variables which could say whether a particular value in them
;;; would cause a rule to fire or not.  So, the sense always matches for a
;;; generalized variable, as long as the link is not an event link.  This is
;;; implemented in the substitution macro `general-sense-matches-p'.

(def-substitution-macro general-sense-matches-p
			(link-sense chaining-as-well-as-events?)
  (or (and chaining-as-well-as-events?
	   (or (eq link-sense 'either)
	       (eq link-sense t)
	       (null link-sense)))
      (eq link-sense 'receives-a-value)
      (eq link-sense 'loses-its-value)))

;;; The algorithm for forward chaining on general variables is the same as that
;;; for logical variables, except that there no sense to match.






;;;; Designation Decomposition Functions



;;; The function `chaining-symbol-for-designation' takes a designation and
;;; returns the symbol which should be used for storing that designation on a
;;; chaining list.

(defun chaining-symbol-for-designation (designation)
  (if (symbolp designation)
      designation
      (atomic-naming-element-of-role (role-of-designation designation))))




;;; The function `local-name-for-designation' takes a designation and returns a
;;; symbol which can used later in this rule to refer the object being
;;; designated here, or else it returns nil if there is no name specified.

(defun local-name-for-designation (designation)
  (let ((role (role-of-designation designation)))
    (if (or (null role)
	    (simple-role-p role))
	nil
	(cdr role))))




;;; The function `copy-designation-using-installation-conses' returns a copy of
;;; the passed designation made out of installation conses.  Note that this
;;; copying function leaves all local names within roles intact.

(defmacro copy-designation-using-installation-conses (designation)
  `(copy-tree-using-installation-conses ,designation))




;;; The function `copy-role-using-installation-conses' returns a copy the passed
;;; role made out of installation conses.

(defmacro copy-role-using-installation-conses (role)
  `(copy-tree-using-installation-conses ,role))




;;; The function `copy-designation-using-slot-value-conses' returns a copy of
;;; the passed designation made out of slot value conses.  Note that this
;;; copying function leaves all local names within roles intact.

(defmacro copy-designation-using-slot-value-conses (designation)
  `(copy-for-slot-value ,designation))




;;; The function `copy-role-using-slot-value-conses' returns a copy the passed
;;; role made out of slot value conses.

(defmacro copy-role-using-slot-value-conses (role)
  `(copy-tree-using-slot-value-conses ,role))




;;; The function `simple-installation-designation' returns a copy of the passed
;;; designation in installation conses, with all roles containing local names
;;; converted to simple roles.

(defun simple-installation-designation (designation)
  (cond ((atom designation)
	 designation)
	(t
	 (installation-cons
	   (first designation)
	   (installation-cons
	     (simple-installation-role designation)
	     (loop for domain in (cddr designation)
		   collect (simple-installation-designation domain)
			      using installation-cons))))))




;;; The function `simple-installation-role' returns a copy of the simple role
;;; component of the passed designation, consed in installation conses.

(defun simple-installation-role (designation)
  (copy-tree-using-installation-conses
    (simple-role-of-role (role-of-designation designation))))




;;; The function `make-simple-designation-slot-value-copy' takes a designation
;;; and and returns a simple designation copy made from slot value conses.

(defun make-simple-designation-slot-value-copy (designation)
  (if (atom designation)
      designation
      (slot-value-cons
	(first designation)
	(slot-value-cons
	  (make-simple-role-slot-value-copy designation)
	  (loop for domain in (cddr designation)
		collect
		  (make-simple-designation-slot-value-copy domain)
			   using slot-value-cons)))))




;;; The function `make-simple-role-slot-value-copy' takes a designation and
;;; makes a slot value cons copy of the simple role of that designation.

(defun make-simple-role-slot-value-copy (designation)
  (copy-tree-using-slot-value-conses
    (simple-role-of-role (role-of-designation designation))))




;;; The function `chaining-focal-role-and-local-name-for-designation' takes a
;;; designation and returns two values.  The first is the symbol which will be
;;; the focal role for invocations of rules for chaining through this
;;; designation, the second is the local name (if any) for the focal item in the
;;; designation.  For non-atomic designations it is the atomic naming element
;;; (i.e.  the embedded class name) of the outermost non-attribute (i.e.
;;; non-atomic) role in the designation.

(defun chaining-focal-role-and-local-name-for-designation (designation)
  (if (consp designation)
      (let ((role (role-of-designation designation)))
	(if (and (symbolp (simple-role-of-role role))
		 (domain-of-designation designation))
	    (chaining-focal-role-and-local-name-for-designation
	      (domain-of-designation designation))
	    (values (atomic-naming-element-of-role role)
		    (get-explicitly-specified-local-name-of-role-if-any
		      role))))
      (values nil nil)))






;;;; Function Templates




;;; Within chaining analysis and compiliation of expressions, it is necessary to
;;; correctly analyze functions which have arguments which are not purely
;;; expressions.  This is analagous to the special form problem in Common Lisp.
;;; Our language needs a way of representing these departures from pure function
;;; form in a consistent way.  The representation for this is the function
;;; template.

;;; A function template is a quoted list whose first element is the name of the
;;; function and whose remaining elements are types of the argument list
;;; components for the function.  The following are the defined argument types.

;;;   expression = the argument in this position is an expression
;;;
;;;   scope = the argument is a scope.  A scope is a local binding directive
;;;     which has the form (role binding <domain>) where domain is optional.
;;;
;;;   there-exists-scope = the argument is a scope given to a there-exists-literal
;;;     form.  This is textually the same as a scope for other quantifiers and
;;;     aggregators, but it is compiled differently by procedures, to allow mutation
;;;     of an existing local name binding instead of creating a new binding.
;;;
;;;   designation = the argument is a designation which will be evaluate as a
;;;     designation and not datum evaluated
;;;
;;;   other = the argument is something which is a special format used only for
;;;     this function.  It does not itself contain any further expressions or
;;;     designations and therefore need not be analyzed by chaining or the
;;;     compiler, and may be passed on verbatim to the final compiled
;;;     expression.

;;; When analyzing an expression, if a function does not have a template
;;; associated with it, then all of the arguments to the function are themselves
;;; expressions.

;;; New function templates are declared with the `def-function-template'
;;; function.  It takes a quoted list which is a new function template and will
;;; install this template for the function.  If there is an existing template
;;; for this function, it will replace it with the new template.  It returns the
;;; name of the newly defined function template.  Templates are kept in a list
;;; in the global variable `function-templates'.

;; Note that this is always called at top level and so doesn't need to
;; set the area.  -jra 1/16/92

(defmacro def-template (new-template template-alist)
  (let ((value-of-new-template (gensym))
	(value-of-template-alist (gensym)))
    `(let ((,value-of-new-template ,new-template)
	   (,value-of-template-alist ,template-alist))
       (loop with template-name = (car ,value-of-new-template)
	     for template-cons on ,value-of-template-alist
	     do
	 (when (eq template-name (caar template-cons))
	   (setf (car template-cons) ,value-of-new-template)
	   (return template-name))
	     finally
	       (setq ,template-alist
		     (cons ,value-of-new-template ,value-of-template-alist))
	       (return template-name)))))

;; Def-template is used to define both function templates and action templates.


(defvar function-templates nil)

(defun def-function-template (new-function-template)
  (def-template new-function-template function-templates))




;;; Function templates are looked up with the `lookup-function-template'
;;; function.  It takes the symbol with names the function and returns the
;;; function template, if any, for that function.  If no function template
;;; exists for the given symbol, then NIL is returned.  Note that at the moment
;;; these are stored in a list and a linear search is performed to find them.
;;; If this becomes a speed issue, then we can take some other course.

(defun lookup-function-template (function-name)
  (assq function-name function-templates))


;;;; Action Templates




;;; Action templates are just like function templates except that there are the
;;; following additional argument types:

;;; message-designation - either a designation or '(the operator)

;;; message-text - either a string or of the form
;;; ('and . list-of-expressions)

;;; inform-option -

;;; ('on designation)
;;; ('above designation)
;;; ('below designation)
;;; or
;;; ('duration expression)

;;; color-expression - a symbol or of the form ('eval expression) (this will go
;;; away when change-icon-color is simplified)

;; Color-expression is obsolete and should be removed after the official
;; release of 2.0.  -jra & ml 8/1/89

;;; color-changes - a list of elements of the form (expression . expression)

;; Color-changes used to be a list of (other . color-expression).  -jra
;; & ml 8/1/89

;;; expression-list - a list of expressions

;;; show-or-hide-argument-list - a list of expressions, which can be one of the
;;; following:
;;;   (IN designation)
;;;   (SCALE . other)
;;;   (SCREEN-POSITIONING-DETAILS . other)
;;;   (WORKSPACE-POSITION . other)

;;; If no template is specified, the action is assumed to be of the form
;;; ('action-name designation . expressions).  Note that this is slightly
;;; different from the default function template which is ('operator-name .
;;; expressions).

(defvar action-templates nil)

(defun def-action-template (new-action-template)
  (def-template new-action-template action-templates))

(defun lookup-action-template (action-name)
  (assq action-name action-templates))






;;;; Parent Stacks for Chaining Parent Search




;;; The function `make-parent-stack' takes an entity frame and returns a list of
;;; entries describing the parent frame ancestry for this frame.  The list is
;;; ordered from immediate parent to oldest grandparents.  Each entry contains
;;; the parent frame, the attribute of that parent which contains its child, a
;;; list of the names for this parent frame, and possibly a cons used to
;;; temporarily put a single parent name into a list.  This stack is made of
;;; eval conses.  The function `reclaim-parent-stack' reclaims these data
;;; structures.

(defun-simple make-parent-stack (entity)
  (loop for child = entity then parent?
	for parent? = (parent-frame child)
	while parent?
	for parent-name-or-names? = (name-or-names-for-frame parent?)
	for parent-name-cons?
	    = (if (and parent-name-or-names?
		       (symbolp parent-name-or-names?))
		  (eval-cons-macro parent-name-or-names? nil))
	collect (eval-list-macro
		  parent?
		  (parent-attribute-name child)
		  (or parent-name-cons? parent-name-or-names?)
		  parent-name-cons?)
	    using eval-cons-macro))

(defun-simple reclaim-parent-stack (parent-stack)
  (when parent-stack
    (loop for trailer = nil then current-entry-cons
	  for current-entry-cons on parent-stack
	  for entry = (car-of-cons current-entry-cons)
	  for name-cons-cons =
	      (cdr-of-cons (cdr-of-cons (cdr-of-cons entry)))
	  do
      (if (car-of-cons name-cons-cons)
	  (reclaim-eval-cons-macro (car-of-cons name-cons-cons)))
      (reclaim-eval-list-given-tail entry name-cons-cons)
	  finally
	    (reclaim-eval-list-given-tail parent-stack trailer))))




;;; The macros `parent-stack-frame', `parent-stack-attribute', and
;;; `parent-stack-parent-names' access elements of entries in parent stack
;;; lists.  The last element of these lists, the parent-name-cons, does not have
;;; or need an accessor.

(defmacro parent-stack-frame (parent-stack-entry)
  `(car-of-cons ,parent-stack-entry))

;;; changed for multiple-inheritance -rdf, 3/1/94

(defmacro parent-stack-attribute (parent-stack-entry)
  (let ((attribute-designation (gensym)))
    `(let ((,attribute-designation (car-of-cons (cdr-of-cons ,parent-stack-entry))))
       (cond ((consp ,attribute-designation)
	      (car-of-cons ,attribute-designation))
	     (t
	      ,attribute-designation)))))

(defmacro parent-stack-role (parent-stack-entry)
  `(car-of-cons (cdr-of-cons ,parent-stack-entry)))
;    `(let ((,attribute-designation (car-of-cons (cdr-of-cons ,parent-stack-entry))))
;       (cond ((consp ,attribute-designation)
;	      (car-of-cons ,attribute-designation))
;	     (t
;	      ,attribute-designation)))))
;  

(defmacro parent-stack-parent-names (parent-stack-entry)
  `(car-of-cons (cdr-of-cons (cdr-of-cons ,parent-stack-entry))))

(defmacro parent-stack-attribute-class (parent-stack-entry)
  (let ((attribute-designation (gensym))
	(entry-name parent-stack-entry))
    `(let ((,attribute-designation (car-of-cons (cdr-of-cons ,entry-name))))
       (cond ((consp ,attribute-designation)
	       (cdr-of-cons ,attribute-designation))
	     (t
	      (class (parent-stack-frame ,entry-name)))))))


;;; The substitution macro `match-parent-frame-with-designation-focus' takes a
;;; parent stack and the domain of a designation stored in a chaining link.
;;; It should already have been confirmed that the designation in the link has
;;; an attribute which matches the attribute stored in the first entry in the
;;; parent stack.

(def-substitution-macro match-parent-frame-with-designation-focus
       (parent-stack simple-designation)
  (loop with role
	with domain?
	with class-of-role?
	with parent-stack-entry = (car parent-stack)
	for parent-frame = (parent-stack-frame parent-stack-entry)
	do
    (if (symbolp simple-designation)
	(if (memq simple-designation
		  (parent-stack-parent-names parent-stack-entry))
	    (return parent-frame)
	    (loop-finish))
	(progn
	  (setq role (role-of-designation simple-designation))
	  (setq domain? (domain-of-designation simple-designation))
	  (if (symbolp role)
	      ;; If there is a domain, this atomic role is an attribute.  If
	      ;; there is no domain, then this symbol is a class name.
	      (if domain?
		  (progn
		    (setq parent-stack (cdr parent-stack))
		    (setq parent-stack-entry (car parent-stack))
		    ;; If the roles match, iterate.
		    (if (and parent-stack
			     (eq (parent-stack-attribute parent-stack-entry)
				 role))
			(setq simple-designation domain?)
			(loop-finish)))
		  (if (frame-of-class-p parent-frame role)
		      (return parent-frame)
		      (loop-finish)))
	      ;; Note that this line requires that the role name of an
	      ;; invertible role always be a symbol and that this symbol always
	      ;; name a class.  If and when this restriction is violated,
	      ;; rewrite this code.
	      ;;
	      ;; It is now true that the type of a role could be a datum type,
	      ;; but classes are restricted to not have type names as their
	      ;; name, and so the code below will correctly reject any parent
	      ;; frame which attempts to match a datum-type.  -jra 10/30/89
	      (progn
		(setq class-of-role? (atomic-class-element-of-simple-role role))
		(if (and class-of-role?
			 (frame-of-class-p parent-frame class-of-role?))
		    (return parent-frame)
		    (loop-finish))))))))



(defmacro class-of-qualified-attribute-name (qualified-attribute)
  `(cdr-of-cons ,qualified-attribute))

(defmacro attribute-of-qualified-attribute-name (qualified-attribute)
  `(car-of-cons ,qualified-attribute))
  

;;; Given a parent stack and a designation from a chaining link, this function
;;; will find and return a frame from the parent stack which is the focal
;;; object for the given designation.  If the designation does not match the
;;; given parent stack, this function will return NIL.


(defun find-referenced-parent (parent-stack designation)
  ;; the parent-role comes through as a dotted pair, while the test-role should
  ;; be a CLASS-QUALIFIED-NAME
  (when parent-stack
    (let ((parent-role (parent-stack-role (car-of-cons parent-stack)))
	  (test-role (role-of-designation designation)))
      (if (or
	    ;; just simple with no class qualifications whatsoever
	    (eq parent-role test-role)

	    ;; if the test-role is a class-qualified-name then there are two
	    ;; possible ways of satisfying
	    (and
	      (class-qualified-name-denotation-p test-role)		 
	      (or
		;; both designations are class qualified in their own
		;; special ways
		(and
		  (consp parent-role)
		  (eq (class-qualifier test-role)
		      (class-of-qualified-attribute-name parent-role))
		  (eq (unqualified-name test-role)
		      (attribute-of-qualified-attribute-name parent-role)))
		(and
		  (symbolp parent-role)
		  (eq (class-qualifier test-role)
		      (let ((slot-description?
			      (get-slot-description-of-frame
				parent-role
				(parent-stack-frame
				  (car-of-cons parent-stack)))))
			(and slot-description?
			     (defining-class slot-description?))))))))
	  (let ((domain-for-parent? (domain-of-designation designation)))
	    (if domain-for-parent?
		(match-parent-frame-with-designation-focus
		  parent-stack domain-for-parent?)))))))




;;; When executing chaining based on the class name of a variable, the collected
;;; chaining lists of all superior class name symbols of a class are cached in
;;; the properties cached-class-forward-chaining-list and
;;; cached-class-backward-chaining-list.  The system variables
;;; cached-classes-for-forward-chaining and cached-classes-for-backward-chaining
;;; are used to hold lists of those classes which contain caches of chaining
;;; lists.

(def-system-variable cached-classes-for-forward-chaining chaining nil)

(def-system-variable cached-classes-for-backward-chaining chaining nil)




;;; The macro `forward-chaining-list-for-classes' takes a class inheritance path
;;; list and returns a list of forward chaining links for those classes in that
;;; list.  This is accomplished by looking up the cached list of the first class
;;; in the list.  If no such cache exists, then a search is made up the class
;;; list for the forward chaining list for each class and the resulting list is
;;; cached before being returned to the caller.

;;; Note that the class list cannot be empty, or this will crash.

(def-substitution-macro forward-chaining-list-for-classes (classes)
  (let ((cache? (cached-class-forward-chaining-list-macro
		  (car-of-cons classes))))
    (if cache?
	(cdr-of-cons cache?)
	(loop for class in classes
	      for specific-list = (forward-chaining-list class)
	      do
	  (when specific-list
	    (setq specific-list (copy-list-using-eval-conses specific-list))
	    (if cache?
		(setq cache?
		      (nconc cache? specific-list))
		(setq cache? specific-list)))
	      until (eq class 'item)
	      finally
		(setf (cached-class-forward-chaining-list (car-of-cons classes))
		      (eval-cons nil cache?))
		#-SymScale
		(eval-push (car-of-cons classes)
			   cached-classes-for-forward-chaining)
		#+SymScale
		(eval-push-atomic (car-of-cons classes)
			   cached-classes-for-forward-chaining)
		(return cache?)))))




;;; The macro `backward-chaining-list-for-classes' takes a class inheritance
;;; path list and returns a list of backward chaining links for those classes in
;;; that list.  This is accomplished by looking up the cached list of the first
;;; class in the list.  If no such cache exists, then a search is made up the
;;; class list for the backward chaining list for each class and the resulting
;;; list is cached before being returned to the caller.

;;; Note that the class list cannot be empty, or this will crash.

(def-substitution-macro backward-chaining-list-for-classes (classes)
  (let ((cache? (cached-class-backward-chaining-list-macro
		  (car-of-cons classes))))
    (if cache?
	(cdr-of-cons cache?)
	(loop for class in classes
	      for specific-list = (backward-chaining-list class)
	      do
	  (when specific-list
	    (setq specific-list (copy-list-using-eval-conses specific-list))
	    (if cache?
		(setq cache?
		      (nconc cache? specific-list))
		(setq cache? specific-list)))
	      until (eq class 'item)
	      finally
		(setf (cached-class-backward-chaining-list (car-of-cons classes))
		      (eval-cons nil cache?))
		#-SymScale
		(eval-push (car-of-cons classes)
			   cached-classes-for-backward-chaining)
		#+SymScale
		(eval-push-atomic (car-of-cons classes)
			   cached-classes-for-backward-chaining)
		(return cache?)))))




;;; The function `decache-class-chaining-lists' decaches all chaining lists for
;;; classes.

;; Note that at this moment, I do not know when this function is being called
;; during the changing of a class hierarchy.  It could be called before the
;; change has been made, in which case I could reliably find the subclasses of a
;; changed class and only decache those, or it could be called in the middle of
;; the change or after the change, in which the class hierarchy is gone and
;; cannot be used to determine which classes to decache.  Since we may be in
;; either of the two latter cases, this facility currently receives no class
;; name and decaches all cached lists.  -jra 7/13/91

(defun-void decache-class-chaining-lists ()
  (when cached-classes-for-backward-chaining
    (loop for class in cached-classes-for-backward-chaining
	  for cache = (cached-class-backward-chaining-list class)
	  do
      (reclaim-eval-list cache)
      (setf (cached-class-backward-chaining-list class) nil))
    #-SymScale
    (reclaim-eval-list cached-classes-for-backward-chaining)
    #-SymScale
    (setq cached-classes-for-backward-chaining nil)
    #+SymScale
    (let ((old-cache cached-classes-for-backward-chaining))
      (when (compare-and-swap cached-classes-for-backward-chaining old-cache nil)
	(reclaim-eval-list old-cache))))
  (when cached-classes-for-forward-chaining
    (loop for class in cached-classes-for-forward-chaining
	  for cache = (cached-class-forward-chaining-list class)
	  do
      (reclaim-eval-list cache)
      (setf (cached-class-forward-chaining-list class) nil))
    #-SymScale
    (reclaim-eval-list cached-classes-for-forward-chaining)
    #-SymScale
    (setq cached-classes-for-forward-chaining nil)
    #+SymScale
    (let ((old-cache cached-classes-for-forward-chaining))
      (when (compare-and-swap cached-classes-for-forward-chaining old-cache nil)
	(reclaim-eval-list old-cache)))))


;;; The variable `*links-and-objects*' is used in the chainers as a place to keep
;;; a list of the links which should be chained upon.  Note that the chaining
;;; functions do not specially bind this value anymore, but explicitly use the
;;; global value.  There should be no non-local exits from these functions, and
;;; if there are any, then a small eval cons leak will result.

(def-system-variable *links-and-objects* chaining nil)

;; is this a PUSH?
(defmacro add-tuple-to-link-list (link object)
  #-SymScale
  `(setf *links-and-objects*
         (eval-cons-macro
	   (eval-cons-macro ,link ,object)
	   *links-and-objects*))
  #+SymScale
  `(eval-push-atomic (eval-cons-macro ,link ,object)
		     *links-and-objects*))

(defun collect-forward-chaining-for-logical-class-references
       (object new-value-sense chaining-as-well-as-events?)
  ;; Iterate over each link in each class list.
  (loop for link in (forward-chaining-list-for-classes
		      (class-inheritance-path
			(class-description-slot object)))
	for link-sense = (forward-link-sense link)
	for designation = (forward-link-designation link)
	do
    ;; If sense doesn't match, or the designation is a name or an attribute
    ;; access of something, punt this link.
    (if (and (logical-sense-matches-p
	       new-value-sense link-sense chaining-as-well-as-events?)
	     (not (symbolp designation))
	     (not (and (domain-of-designation designation)
		       (symbolp (role-of-designation designation))))
	     (or (null (domain-of-designation designation))
		 (multiple-value-bind (role continuation expiration?)
		     (serve-first-value-of-role-inverse
		       object
		       (first designation)
		       (role-of-designation designation)
		       (domain-of-designation designation))
		   (when expiration?
		     (reclaim-if-evaluation-value role))
		   (when continuation
		     (close-role-value-server continuation))
		   expiration?)))
	(add-tuple-to-link-list link object))))




;;; The function `collect-forward-chaining-for-symbolic-class-references' will
;;; collect all forward chaining links which reference the classes of the given
;;; object.  If the parent-of-variable? argument is T, then the given frame is
;;; the parent of the variable, and we are chaining on implied attribute
;;; references.  If the parent-of-variable? argument is NIL, then we are
;;; chaining on the variable itself.

(defun collect-forward-chaining-for-symbolic-class-references
       (object new-value possible-values? chaining-as-well-as-events?
	parent-of-variable?)
  ;; Iterate over each link in each class list.
  (loop for link in (forward-chaining-list-for-classes
		      (class-inheritance-path
			(class-description-slot object)))
	for symbolic-value = (forward-link-symbolic-value link)
	for sense = (forward-link-sense link)
	for designation = (forward-link-designation link)
	do
    (if (and (symbolic-sense-matches-p
	       parent-of-variable? new-value possible-values?
	       symbolic-value
	       sense
	       chaining-as-well-as-events?)
	     (not (symbolp designation))
	     (not (and (domain-of-designation designation)
		       (symbolp (role-of-designation designation))))
	     (or (null (domain-of-designation designation))
		 (multiple-value-bind (role continuation expiration?)
		     (serve-first-value-of-role-inverse
		       object
		       (first designation)
		       (role-of-designation designation)
		       (domain-of-designation designation))
		   (when expiration?
		     (reclaim-if-evaluation-value role))
		   (when continuation
		     (close-role-value-server continuation))
		   expiration?)))
	(add-tuple-to-link-list link object))))


(defun collect-forward-chaining-for-general-class-references
       (object chaining-as-well-as-events?)
  
  (loop for link in (forward-chaining-list-for-classes
		      (class-inheritance-path
			(class-description-slot object)))
	for link-sense = (forward-link-sense link)
	for designation = (forward-link-designation link)
	do
    ;; If sense doesn't match, the designation is an attribute, or there is a
    ;; domain of the designation, it doesn't inverse serve to anything, punt
    ;; the link.
 ;   (format t "~% Link ~a link des ~a sense ~a" link designation link-sense)
;    (break)
    (if (and (general-sense-matches-p link-sense chaining-as-well-as-events?)
	     (not (symbolp designation))
	     (not (and (domain-of-designation designation)
		       (symbolp (role-of-designation designation))))
	     (or (null (domain-of-designation designation))
		 (multiple-value-bind (role continuation expiration?)
		     (serve-first-value-of-role-inverse
		       object
		       (first designation)
		       (role-of-designation designation)
		       (domain-of-designation designation))
		   (when expiration?
		     (reclaim-if-evaluation-value role))
		   (when continuation
		     (close-role-value-server continuation))
		   expiration?)))
	(add-tuple-to-link-list link object))))




;;; The macro `invoke-true-value-update' is called to invoke the update function
;;; for a true value update recipient structure instance.

(def-substitution-macro invoke-true-value-update
    (true-value-update-recipient changed-frame attribute? old-value class-if-specific?) 
  (funcall-symbol
    (true-value-update-function true-value-update-recipient)
    (true-value-update-frame true-value-update-recipient)
    (true-value-update-argument true-value-update-recipient)
    changed-frame
    attribute?
    old-value
    class-if-specific?))

;;; Invoke rules for forward chaining collects the links, roles, and objects to
;;; be invoked into a list and then invokes them.

(defun invoke-rules-for-forward-chaining
       (variable new-managed-value data-type chaining-as-well-as-events?
                 old-managed-value)
  (let ((needs-true-value-expiration-task? nil)
	(old-extracted-value? nil)
	(*links-and-objects* nil))
    (collect-rules-for-forward-chaining
      variable new-managed-value data-type chaining-as-well-as-events?)
    (if *links-and-objects*
	(loop for trailer = nil then link-entry-cons
	      for link-entry-cons on *links-and-objects*
	      for link-entry = (car-of-cons link-entry-cons)
	      for link = (car-of-cons link-entry)
	      for recipient = (forward-link-recipient link)
	      do
              ;; If the recipient is a cons, then it is an update function,
              ;; else it is a rule.
              (cond
               ((true-value-update-recipient-p recipient)
                ;; If it can be conclusively shown that the variable really is
                ;; denoted by the designation in the link, then call the update
                ;; function.
                (when (designation-denotes-item-p
                       (forward-link-designation link) variable)
                  (when (true-value-update-frame recipient)
                    (tformat-major-trace-message
                     "Notifying ~NF that a new value has been placed in ~NF."
                     (true-value-update-frame recipient)
                     variable))
                  ;; Parameters don't need expiration tasks.
                  (setq needs-true-value-expiration-task?
                        (frame-of-class-p variable 'variable))
                  (when (null old-extracted-value?)
                    (setq old-extracted-value?
                          (extract-cached-number-or-value old-managed-value)))
                  (invoke-true-value-update
                   recipient variable nil old-extracted-value? nil)))
               ((eq (forward-link-sense link) 'loses-its-value)
                (if (frame-of-class-p variable 'variable)
                    (setq needs-true-value-expiration-task? t)))
               (t
                ;; Schedule the rule.
                (when (runnable-p recipient)
                  (let* ((role? (forward-link-focus link))
                         (local-name? (if role?
                                          (forward-link-focus-local-name link)
                                        nil))
                         (object? (if role?
                                      (cdr-of-cons link-entry)
                                    nil)))
                    #+development
                    (if (and role? (not object?))
                        (error "Error in forward chaining!  A link with the ~
                            stored focal role ~a was chained to with no ~
                            focal object.  Inform Jim of this error."
                               role?))
                    (when (major-trace-message-will-be-written-p)
                      (write-trace-message-for-forward-chaining
                       recipient variable role? local-name? object?))
                    (generate-and-schedule-rule-instances
                     recipient role? local-name? object?
                     'forward-chaining nil
                     (rule-priority recipient) nil)))))
              (reclaim-eval-cons-macro link-entry)
	      finally
              (when *links-and-objects*
                (reclaim-eval-list-given-tail *links-and-objects* trailer)
                (setq *links-and-objects* nil))))
    (when needs-true-value-expiration-task?
      (let ((expiration (expiration-time-of-current-value variable)))
	(when (and (fixnump expiration)
		   (>=f expiration gensym-time))
	  (schedule-update-for-variable-expiration variable))))))

(defun write-trace-message-for-forward-chaining
       (rule variable role? local-name? object?)
  (write-major-trace-message 
    (if role?
	(if local-name?
	    (tformat
	      "Scheduling forward chaining to ~NF with ~NF as the ~A ~
               with local name ~A because a new value was placed in ~NF by ~NF."
	      rule
	      object?
	      role?
	      local-name?
	      variable
	      *current-computation-frame*)
	    (tformat
	      "Scheduling forward chaining to ~NF with ~NF as the ~A ~
               because a new value was placed in ~NF by ~NF."		    
	      rule
	      object?
	      role?
	      variable
	      *current-computation-frame*))
	(tformat
	  "Scheduling forward chaining to ~NF because a new value was ~
         placed in ~NF by ~NF."
	  rule
	  variable
	  *current-computation-frame*))))


(defun collect-rules-for-logical-forward-chaining
       (variable new-value chaining-as-well-as-events?
	parent-stack variable-names?)
  (let ((new-value-sense (>f new-value 0)))
    ;; Chain on references to the variable name, if it has one, invoking
    ;; those rules whose links have the right sense.
    (loop for name-for-variable in variable-names?
	  do
      (loop for link in (forward-chaining-list-macro name-for-variable)
	    for link-sense = (forward-link-sense link)
	    do
	(if (and (eq name-for-variable (forward-link-designation link))
		 #+mtg2
		 (eq (faction? variable)
		     (faction? (forward-link-recipient link)))
		 (logical-sense-matches-p
		   new-value-sense
		   link-sense
		   chaining-as-well-as-events?))
	    (add-tuple-to-link-list link nil))))
    ;; If the variable has a parent, chain on the name of the attribute
    ;; which holds this variable.
    (when parent-stack
      (loop for link in (forward-chaining-list-macro
			  (parent-stack-attribute
			    (car-of-cons parent-stack)))
	    for link-sense = (forward-link-sense link)
	    do
	(if (logical-sense-matches-p
	      new-value-sense
	      link-sense
	      chaining-as-well-as-events?)
	    (let ((parent-frame?
		    (find-referenced-parent
		      parent-stack (forward-link-designation link))))
	      (if parent-frame?
		  (add-tuple-to-link-list link parent-frame?))))))
    ;; Chain on superior classes of the variable itself.
    (collect-forward-chaining-for-logical-class-references
      variable new-value-sense chaining-as-well-as-events?)))


(defun collect-rules-for-symbolic-forward-chaining
       (variable new-value chaining-as-well-as-events?
	parent-stack variable-name-or-names?)
  (let ((possible-values? nil)
	(parent-stack-entry (car parent-stack)))
    ;; First chain on references to a parent entity.  This is so
    ;; that we can find a set of possible values for this variable
    ;; as the first thing that happens, if that list is available.
    (when parent-stack-entry
      ;; If we've got a parent entity, get the set of possible values. 
      (setq possible-values?
	    (value-set-given-attribute-and-class
	      (parent-stack-attribute parent-stack-entry)
	      (parent-stack-attribute-class parent-stack-entry)))
      ;; Check that the new value is in the set of possible values, and
      ;; give a note to the engineer if it is not.
      (when (and possible-values?
		 (not (memq-macro new-value possible-values?)))
	(warn-of-inappropriate-value new-value variable possible-values?))
      ;; If there are names for this parent object, chain on direct
      ;; references to names.
      (when possible-values?
	(loop for name-for-parent?
		  in (parent-stack-parent-names parent-stack-entry)
	      do
	  (loop for link in (forward-chaining-list-macro name-for-parent?)
		for symbolic-value = (forward-link-symbolic-value link)
		for sense = (forward-link-sense link)
		do
	    (if (and (symbolic-sense-matches-p
		       t new-value possible-values?
		       symbolic-value
		       sense
		       chaining-as-well-as-events?)
		     #+mtg2
		     (eq (faction? variable)
			 (faction? (forward-link-recipient link)))
		     (symbolp (forward-link-designation link)))
		(add-tuple-to-link-list link nil)))))
      ;; Chain on the attribute of the parent, to handle the case of
      ;; references to the variable through a named attribute of an
      ;; object.
      (loop for link in (forward-chaining-list-macro
			  (parent-stack-attribute parent-stack-entry))
	    for link-symbolic-value = (forward-link-symbolic-value link)
	    for link-sense = (forward-link-sense link)
	    do
	(when (symbolic-sense-matches-p
		nil new-value possible-values?
		link-symbolic-value link-sense
		chaining-as-well-as-events?)
	  (let ((parent-frame? (find-referenced-parent
				 parent-stack
				 (forward-link-designation link))))
	    (if parent-frame?
		(add-tuple-to-link-list link parent-frame?)))))
      ;; Chain on the references to this variable through the class of
      ;; its parent entity.
      (when possible-values?
	(collect-forward-chaining-for-symbolic-class-references
	  (parent-stack-frame parent-stack-entry)
	  new-value possible-values? chaining-as-well-as-events? t)
	;; Chain on the references to the parent through attributes of
	;; its further parent, if any.
	(when (cdr parent-stack)
	  (setq parent-stack-entry (second parent-stack))
	  (loop for link in (forward-chaining-list-macro
			      (parent-stack-attribute parent-stack-entry))
		for link-symbolic-value = (forward-link-symbolic-value link)
		for link-sense = (forward-link-sense link)
		do
	    (when (symbolic-sense-matches-p
		    t new-value possible-values?
		    link-symbolic-value link-sense
		    chaining-as-well-as-events?)
	      (let ((parent-frame? (find-referenced-parent
				     (cdr parent-stack)
				     (forward-link-designation link))))
		(if parent-frame?
		    (add-tuple-to-link-list link parent-frame?))))))) )
    ;; Next, chain on references directly to the variable itself.
    ;; First, references to the name of the variable.
    (loop for name-for-variable in variable-name-or-names?
	  do
      (loop for link in (forward-chaining-list-macro name-for-variable)
	    for symbolic-value = (forward-link-symbolic-value link)
	    for sense = (forward-link-sense link)
	    do
	(if (and (symbolic-sense-matches-p
		   nil new-value possible-values?
		   symbolic-value sense
		   chaining-as-well-as-events?)
		 (symbolp (forward-link-designation link)))
	    (add-tuple-to-link-list link nil))))
    ;; Next, chain on references to this variable through its class.
    (collect-forward-chaining-for-symbolic-class-references
      variable new-value possible-values? chaining-as-well-as-events? nil)))

(defun warn-of-inappropriate-value (new-value variable possible-values)
  (unless (and initializing-clear-text-p 
	       initializing-items-needing-initialization)
    (write-warning-message 1
      (tformat
	"The value ~(~a~) is being stored into the symbolic variable ~NF but ~
       this value is not a member of the set of possible values for its ~
       attribute and class.  The set of possible values contains the ~
       element~a "
	new-value
	variable
	(if (cdr possible-values) "s" ""))
      (write-list-in-chicago-style possible-values "and")
      (twrite-character #.%\.)))
  nil)


(defun collect-rules-for-general-forward-chaining
       (variable chaining-as-well-as-events?
	parent-stack variable-name-or-names?)
  ;; Chain on references to the variable name, if it has one.
  (loop for name-for-variable in variable-name-or-names?
	do
    (loop for link in (forward-chaining-list-macro name-for-variable)
	  for link-sense = (forward-link-sense link)
	  do
      (if (and (general-sense-matches-p
		 link-sense
		 chaining-as-well-as-events?)
	       #+mtg2
	       (eq (faction? variable)
		   (faction? (forward-link-recipient link)))
	       (symbolp (forward-link-designation link)))
	  (add-tuple-to-link-list link nil))))
  ;; If the variable has a parent, chain on the name of the attribute
  ;; which holds this variable.
  (if parent-stack
      (loop for link in (forward-chaining-list-macro
			  (parent-stack-attribute
			    (car-of-cons parent-stack)))
	    for link-sense = (forward-link-sense link)
	    do
	(if (general-sense-matches-p link-sense chaining-as-well-as-events?)
	    (let ((parent-frame? (find-referenced-parent
				   parent-stack
				   (forward-link-designation link))))
	      (if parent-frame?
		  (add-tuple-to-link-list link parent-frame?))))))
  ;; Chain on superior classes of the variable itself.
  (collect-forward-chaining-for-general-class-references
    variable chaining-as-well-as-events?))




(defun collect-rules-for-forward-chaining
       (variable new-value data-type chaining-as-well-as-events?)
  ;; Collect names and parent info before starting on the specific
  ;; algorithms for logical, symbolic, or generic type variables.
  (let* ((variable-name-or-names?
	   (name-or-names-for-frame variable))
	 (variable-name-cons?
	   (if (and variable-name-or-names?
		    (symbolp variable-name-or-names?))
	       (setq variable-name-or-names?
		     (eval-cons variable-name-or-names? nil))
	       nil))
	 (parent-stack (make-parent-stack variable))
	 (parent-entry?
	   (when parent-stack (car-of-cons parent-stack))))
    ;; Trigger any event detectors on the frame or its parent.
    (loop with triggerable-event-detectors =
      (let ((event-detectors (registered-event-detectors variable)))
	(when event-detectors
	  (loop for event-detector in event-detectors
		when (and (eq (event-detector-type event-detector)
			      'receives-a-value)
			  (null (event-detector-extra-information
				  event-detector)))
		  collect event-detector using eval-cons)))
	  while triggerable-event-detectors
	  for event-detector = (eval-pop triggerable-event-detectors)
	  do (trigger-event-detector event-detector))
    (when parent-entry?
      (loop with triggerable-event-detectors =
	(let ((event-detectors (registered-event-detectors
				 (parent-stack-frame parent-entry?))))
	  (when event-detectors
	    (loop for event-detector in event-detectors
		  when (and (eq (event-detector-type event-detector)
				'receives-a-value)
			    (eq (event-detector-extra-information event-detector)
				(parent-attribute-name variable)))
		    collect event-detector using eval-cons)))
	    while triggerable-event-detectors
	    for event-detector = (eval-pop triggerable-event-detectors)
	    do (trigger-event-detector event-detector)))
    ;; chaining on the logical variables, and figure out what sense we have
    ;; from the new value.
    (cond
      ((eq data-type 'truth-value)
       (collect-rules-for-logical-forward-chaining
	 variable new-value chaining-as-well-as-events?
	 parent-stack variable-name-or-names?))
      ;; Chaining on symbolic variables.
      ((eq data-type 'symbol)
       (collect-rules-for-symbolic-forward-chaining
	 variable new-value chaining-as-well-as-events?
	 parent-stack variable-name-or-names?))
      ;; This section performs chaining on general variables other than
      ;; symbolic or logicals.
      (t
       (collect-rules-for-general-forward-chaining
	 variable chaining-as-well-as-events?
	 parent-stack variable-name-or-names?)))
    (if variable-name-cons? (reclaim-eval-cons-macro variable-name-cons?))
    (reclaim-parent-stack parent-stack)))


;;;; Forward Chaining Link Generation Functions




;;; The function `update-forward-chaining-lists' removes forward chaining links
;;; that had been generated from the old source for this rule, and installs new
;;; references for the new source.  Note that either of these sources could be
;;; null.

;; Note that this has been replaced by chaining link functions called from the
;; slot value compiler for rules.  -jra 10/8/91

(defvar names-and-info-for-chaining)




;;; The function `note-names-and-info-for-forward-chaining-in-rule-translation'
;;; takes two arguments, the raw translation of a rule and the frame for that
;;; rule.  When called it conses (using slot value conses) onto the specially
;;; bound list `names-and-info-for-chaining' the names and descriptions of those
;;; objects which should be set up for forward chaining invocation of this rule.
;;; The given descriptions will be added to the KB specific property
;;; `forward-chaining-list' of the given name.  Variables or object attributes
;;; which are checked in an antecedant for symbolic or truth values comprise the
;;; contents of this list.  Forward chaining propagates values of logical and
;;; symbolic variables.  Forward chaining will not ever handle propagation of
;;; numeric values, though backward chaining will.

;;; Names-and-info-for-chaining will contain a list where the entries are conses
;;; whose car is the symbol which should get the forward chaining list link, and
;;; the cdr is the link.  The link will be an instance of the forward-link
;;; def-structure.

;;; The forward chaining list symbol for a link is derived from a designation in
;;; a rule antecedant and could be any of several different types references
;;; within a designation.  If a link comes from a direct reference to a variable
;;; name, or if it comes from a reference to an implied attribute of a directly
;;; named object, then the symbol will be the given name.  If a link comes from
;;; a role, then the symbol will be the atomic naming element of that role.
;;; (See the documentation in compile1 for a definition of atomic naming
;;; element.)

;;; Forward links are def-structures with four elements: a rule, the designation
;;; used to name a variable in this rule, a symbolic value compared against the
;;; value of a variable, and a positive or negative sense.

;;; The following function analyses the raw translation of a rule to find the
;;; references which will be forward chained upon.  Since designations in the
;;; later part of a rule may use designations from a previous part, each
;;; designation will be pushed onto a specially bound list
;;; `designations-in-rule' using slot value conses, which will be unbound on
;;; return from this function.  The elements on this list will be a cons whose
;;; car may contain a symbolic name of a designated object, and whose cdr
;;; contains a designation.  This is to handle references such as "if the
;;; valve-state of any tank, t1 and the cap-state of t1 then...".  The raw
;;; translation of the antecedant of this rule is "(and (the valve-state (any
;;; (tank . t1))) (the cap-state t1))".  In this case, there would be three
;;; entries to the designations-in-role variable.  They are "(nil . (the
;;; valve-state (any tank)))", "(t1 . (any tank))", and "(nil . (the cap-state
;;; (any tank)))".  Note that designations put onto the list will contain only
;;; simple roles.  (See the file compile1 for documentation on simple roles.)


(defvar designations-in-rule nil)

(defun note-names-and-info-for-forward-chaining-in-rule-translation
       (translation rule frame-flags)
  (let ((designations-in-rule nil))
    ;; First note then move past designations in FOR iterators in the
    ;; beginning of rules.
    (loop while (and (consp translation) (eq (first translation) 'for))
	  for unabbreviated-designation? =
	      (lookup-previous-reference-and-note-designation
		(second translation))
	  do
      (when (and unabbreviated-designation?
		 (invocable-via-forward-chaining-of-flag-vector-p frame-flags))
	(note-links-for-dynamic-roles rule unabbreviated-designation?))
      (setq translation (third translation)))
    ;; Next, note forward chaining.
    (cond ((invocable-via-forward-chaining-of-flag-vector-p frame-flags)
	   (note-forward-chaining-given-antecedent
	     (second translation) rule t))
	  ((and (consp translation)
		(eq (car translation) 'whenever))
	   (note-forward-chaining-given-event-antecedent
	     (second translation) rule)))
    ;; Clean up any designations left over.
    (reclaim-slot-value designations-in-rule)))




;;; The function `note-names-and-info-for-cell-chaining-in-expression' is used
;;; by the cell chaining installation facilities to search expressions
;;; containing invertible designations.  Note that this differs from true value
;;; update chaining only in that the sense is either instead of receives a
;;; value.

(defun note-names-and-info-for-cell-chaining-in-expression
       (expression true-value-recipient)
  (let ((designations-in-rule nil))
    (note-forward-chaining-given-antecedent
      expression true-value-recipient 'either)
    (reclaim-slot-value designations-in-rule)))




;;; The function `note-names-and-info-for-true-value-chaining-in-expression' is
;;; used by the true value update facilities to search expressions containing
;;; invertible designations.

(defun note-names-and-info-for-true-value-chaining-in-expression
       (expression true-value-recipient)
  (let ((designations-in-rule nil))
    (note-forward-chaining-given-antecedent
      expression true-value-recipient 'receives-a-value)
    (reclaim-slot-value designations-in-rule)))

(defun note-forward-chaining-given-antecedent (expression rule sense)
  (cond ((null expression) nil)
	;; Chain on the designation for references to logical variables.
	((designation-p expression)
	 (let ((unabbreviated-designation?
		 (note-link-and-designations-for-forward-chaining
		   rule expression nil sense)))
	   (when unabbreviated-designation?
	     (note-links-for-dynamic-roles
	       rule unabbreviated-designation?))))
	((consp expression)
	 (let ((operator (car-of-cons expression)))
	   (cond
	     ;; Non-symbolic operators are parameters, and the operator
	     ;; "quote" merely quotes a following symbol, so neither of
	     ;; these should be analyzed for chaining references.
	     ((or (not (symbolp operator))
		  (eq operator 'quote))
	      nil)
	     ;; Chain on symbolic comparisons.
	     ((eq operator 'is)
	      (note-link-and-designations-for-forward-chaining
		rule
		(second expression)
		(if (or (eq sense 'either)
			(eq sense 'receives-a-value))
		    nil
		    (second (third expression)))
		sense))
	     ;; Chain on negated symbolic comparisons.
	     ((eq operator 'is-not)
	      (note-link-and-designations-for-forward-chaining
		rule
		(second expression)
		(if (or (eq sense 'either)
			(eq sense 'receives-a-value))
		    nil
		    (second (third expression)))
		(if (or (eq sense 'either)
			(eq sense 'receives-a-value))
		    sense
		    (not sense))))
	     ;; Chain on relation predicates.
	     ((or (eq operator 'is-not-related)
		  (eq operator 'is-related))
	      (gensym-dstruct-bind
		((nil relation-name-expression subject-designation
		      object-designation)
		 expression)
		(when (and (consp relation-name-expression)
			   (eq (car-of-cons relation-name-expression) 'quote)
			   (symbolp (second relation-name-expression)))
		  (note-link-and-designations-for-forward-chaining
		    rule
		    subject-designation
		    (second relation-name-expression)	; relation name
		    (cond ((or (eq sense 'either)
			       (eq sense 'receives-a-value))
			   :related-change)
			  ((null sense)
			   (if (eq operator 'is-related)
			       :not-related
			       :related))
			  (t
			   (if (eq operator 'is-related)
			       :related
			       :not-related)))
		    object-designation))))	; object designation
	     (t
	      (unless (eq sense 'receives-a-value)
		(cond ((and (memq operator '(false not))
			    (neq sense 'either))
		       (setq sense (not sense)))
		      ((and (not (logical-operator-p operator))
			    (not (memq operator '(there-exists-literal
						   for-every-literal))))
		       (setq sense 'either))))
	      (let ((function-template? (lookup-function-template operator)))
		(if (null function-template?)
		    (loop for sub-expression in (cdr expression)
			  doing
		      (note-forward-chaining-given-antecedent
			sub-expression rule sense))
		    (note-forward-chaining-given-antecedent-and-function-template
		      expression function-template? rule sense)))))))))

(defun note-forward-chaining-given-antecedent-and-function-template
       (expression template rule sense)
  (loop for sub-expression in (cdr expression)
	for argument-type in (cdr template)
	do
    (case argument-type
      ((expression)
       (note-forward-chaining-given-antecedent sub-expression rule sense))
      ((designation)
       (note-links-for-dynamic-roles
	 rule
	 (lookup-previous-reference-and-note-designation sub-expression)))
      ((scope)
       (let ((designation
	       (slot-value-cons
		 'any
		 (copy-for-slot-value sub-expression))))
	 (note-links-for-dynamic-roles
	   rule
	   (lookup-previous-reference-and-note-designation designation))
	 (reclaim-slot-value designation)))
      ((other)
       t)
      ;; If there are additions to the argument type list which don't get
      ;; propagated here, then this clause will be run.
      (otherwise
	#+development
	(cerror "Continue."
		"Unknown argument type ~a from function template ."
		argument-type)))))


(defun note-forward-chaining-given-event-antecedent (antecedent rule)
  (note-forward-chaining-given-event-logical-expression
    (if (and (consp antecedent)
	     (eq (car antecedent) 'and))
	(second antecedent)
	antecedent)
    rule))

(defun note-forward-chaining-given-event-logical-expression (expression rule)
  (when (consp expression)
    (let ((operator (car expression)))
      (case operator
	;; The only operators for event expression are "or" and the event
	;; predicates themselves, so there will be no sense switching.
	((or)
	 (loop for sub-expression in (cdr expression)
	       doing
	   (note-forward-chaining-given-event-logical-expression
	     sub-expression rule)))
	;; Chain on new value reception.
	((receives-a-value)
	 (note-link-and-designations-for-forward-chaining
	   rule (second expression) nil 'receives-a-value))
	((fails-to-receive-a-value)
	 (note-link-and-designations-for-forward-chaining
	   rule (second expression) nil 'fails-to-receive-a-value))
	((is-moved)
	 (note-link-and-designations-for-forward-chaining
	   rule (second expression) nil 'is-moved))
	((is-moved-by-the-user)
	 (note-link-and-designations-for-forward-chaining
	   rule (second expression) nil 'is-moved-by-the-user))
	((is-moved-by-g2)
	 (note-link-and-designations-for-forward-chaining
	   rule (second expression) nil 'is-moved-by-g2))
	((is-resized-by-the-user)
	 (note-link-and-designations-for-forward-chaining
	   rule (second expression) nil 'is-resized-by-the-user))
	((becomes-related)
	 (note-link-and-designations-for-forward-chaining
	   rule
	   (third expression)			; relation subject
	   (second (second expression))			; relation name
	   :related
	   (fourth expression)))		; relation object
	((ceases-to-be-related)
	 (note-link-and-designations-for-forward-chaining
	   rule
	   (third expression)			; relation subject
	   (second (second expression))			; relation name
	   :not-related
	   (fourth expression)))		; relation object
	((generic-event)
	 (note-link-and-designations-for-forward-chaining
	   rule
	   (second expression) ; the designation
	   (second (third expression)) ; the event-name
	   'has-generic-event
	   (fourth expression))) ; binding for event object
	((is-activated)
	 (note-link-and-designations-for-forward-chaining
	   rule (second expression) nil 'is-activated))
	((is-deactivated)
	 (note-link-and-designations-for-forward-chaining
	   rule (second expression) nil 'is-deactivated))
	((is-enabled)
	 (note-link-and-designations-for-forward-chaining
	   rule (second expression) nil 'is-enabled))
	((is-disabled)
	 (note-link-and-designations-for-forward-chaining
	   rule (second expression) nil 'is-disabled))
	((loses-its-value)
	 (note-link-and-designations-for-forward-chaining
	   rule (second expression) nil 'loses-its-value))
	((is-created)
	 (note-link-and-designations-for-forward-chaining
	   rule (second expression) nil 'is-created))
	((generic-becomes-related)
	 (note-link-and-designations-for-forward-chaining
	   rule
	   (second expression)			; relation subject
	   nil                                  ; no relation name
	   :related
	   (third expression)))                 ; relation object
	((generic-ceases-to-be-related)
	 (note-link-and-designations-for-forward-chaining
	   rule
	   (second expression)			; relation subject
	   nil                                  ; no relation name
	   :not-related
	   (third expression)))
	((generic-directly-connected-to)
	 (note-link-and-designations-for-forward-chaining
	   rule
	   (second expression)			; connection
	   (filter-symbol-given-filter-expression (third expression))               ; possible filter
	   :connected
	   (fourth expression)))                 ; item being connected to
	((generic-directly-disconnected-from)
	 (note-link-and-designations-for-forward-chaining
	   rule
	   '(any connection)			; connection
	   (filter-symbol-given-filter-expression (second expression))               ; possible filter
	   :disconnected
	   (third expression)))                 ; item being disconnected from
	;; The '(any connection) form is inserted here to "fool" the mechanism within
	;; note-link-and-designations-for-forward-chaining into putting the rule
	;; onto the link list for the symbol 'connection.  The designation does not
	;; actually exist in the rule translation.  The invoke mechanism
	;; (invoke-rules-for-connection-chaining) works here since it will look for rules
	;; on the forward chaining list of the symbol 'connection since it is the base class
	;; for all connections.  This approach is used here to allow for chaining to be based
	;; on subclasses of connection as well.

	((directly-connected-to)
	 (note-link-and-designations-for-forward-chaining
	   rule
	   (second expression)			; connection class
	   (filter-symbol-given-filter-expression (third expression))               ; possible filter
	   :connected
	   (fourth expression)))
	((directly-disconnected-from)
	 (let ((class-specifier
		 (slot-value-list 'any (second (second expression)))))
	   (note-link-and-designations-for-forward-chaining
	     rule
	     class-specifier
	     (filter-symbol-given-filter-expression (third expression))               ; possible filter
	     :disconnected
	     (fourth expression))
	   (reclaim-slot-value-list class-specifier)))
	((indirectly-connected-to)
	 (note-link-and-designations-for-forward-chaining
	   rule
	   (second expression)			; connection subject
	   nil                                  ; no connection relation name
	   :connected
	   (third expression)))                 ; connection object
	((indirectly-disconnected-from)
	 (note-link-and-designations-for-forward-chaining
	   rule
	   (second expression)			; connection subject
	   nil                                  ; no connection relation name
	   :disconnected
	   (third expression)))                 ; connection object
	(t
	 (when (and (eq operator 'nupec-synchronization-occurs)
		    (nupec-authorized-p))
	   (note-link-and-designations-for-forward-chaining
	     rule
	     'nupec-synchronization-occurs
	     nil
	     'nupec-synchronization-occurs)))))))



(defun filter-symbol-given-filter-expression (filter-expression)
  (let ((filter-symbol (second filter-expression)))
    (if (eq filter-symbol 'no-filter)
	nil
	filter-symbol)))



;;; Designation-and-filter-of-connection-target-specifier takes a connection-target-specifier
;;; and returns two values:  the designation and a filter.  The filter is a symbol and can be
;;; nil.  The filter indicates how the connection is made to the block (at an input, output, or
;;; at a port).  Connection-target-specifier can have one of the following forms:
;;;   designation
;;;   ('at-port portname designation)
;;;   ('at-an-input designation)
;;;   ('at-an-output designation)
;;; For the 'at-an-input and 'at-an-output cases, these symbols are returned as the filter.
;;; For the 'at-port case, the portname is returned as the filter.  For the pure designation
;;; case, nil is returned as the filter.

;(defun designation-and-filter-of-connection-target-specifier (connection-target-specifier)
;  (case (first connection-target-specifier)
;    ((at-an-input at-an-output)
;     (values (second connection-target-specifier) (first connection-target-specifier)))
;    ((at-port)
;     (values (third connection-target-specifier) (second connection-target-specifier)))
;    (t
;     (values connection-target-specifier nil))))



;;; Given a designation and a rule, this function will place whatever forward
;;; chaining links necessary onto the names-and-info-for-chaining list and note
;;; the given designations onto designations-in-rule.  Note that this treats the
;;; roles value-of and current-value-of specially, in that if the primary role
;;; of a designation is one of these two roles, chaining and designation noting
;;; will be done on the domain of the given designations.  This function always
;;; returns the unabbreviated version of the given designation.
(defun note-link-and-designations-for-forward-chaining
       (rule designation symbolic-value? sense?
	&optional (second-designation? nil))
  (when (and (neq designation 'true)
	     (neq designation 'false))
    (let ((unabbreviated-designation
	    (lookup-previous-reference-and-note-designation designation))
	  (second-unabbreviated-designation?
	    (if second-designation?
		(lookup-previous-reference-and-note-designation
		  second-designation?))))
      (when (and (invertible-designation-p unabbreviated-designation)
		 (or (null second-unabbreviated-designation?)
		     (invertible-designation-p
		       second-unabbreviated-designation?)))
	(note-link-for-forward-chaining
	  rule unabbreviated-designation symbolic-value? sense?
	  second-unabbreviated-designation?))
      unabbreviated-designation)))




;;; The function `note-designation' stores a reference to the passed designation
;;; in the designations-in-rule list.  If this designation has a local name, it
;;; is stored in the list as well.


(defun note-designation (designation)
  (if (consp designation)
      (setf designations-in-rule
	    (slot-value-cons
	      (slot-value-cons
		(local-name-for-designation designation)
		designation)
	      designations-in-rule))))




;;; The function `lookup-previous-reference-and-note-designation' takes a
;;; designation, checks if this designation, or any parent designation of this
;;; designation might be able to be replaced with a previous reference, and if
;;; it does it searches for a previous reference.  If it finds one it returns
;;; the previous reference, but otherwise it returns a designation which is a
;;; copy of the passed designation.  If this designation or any parent
;;; designation of it does not bind to a previously given designation, this
;;; designation is noted on the designations-in-rule special variable.  The
;;; returned copy is made of slot value conses, and will eventually be reclaimed
;;; on exit from the chaining link collection functions.  Use
;;; copy-simple-designation-using-slot-value-conses to copy this designation
;;; before storing it in any chaining link.

(defun lookup-previous-reference-and-note-designation (designation)
  (cond ((or (null designation)
	     (and (atom designation) (not (symbolp designation))))
	 designation)
	((symbolp designation)
	 (let ((local-designation?
		 (cdr (assq designation designations-in-rule))))
	   (if local-designation?
	       local-designation?
	       designation)))
	((and (consp designation)
	      (=f (length designation) 2))
	 (let ((previous-designation nil))
	   (when (designation-requires-previous-reference-p designation)
	     (loop with referenced-element =
		     (atomic-naming-element-of-designation designation)
		   for entry in designations-in-rule
		   for naming-element = (atomic-naming-element-of-designation
					  (cdr entry))
		   do
	       (when (eq referenced-element naming-element)
		 (setq previous-designation (cdr entry))
		 (loop-finish))))
	   (if previous-designation
	       previous-designation
	       (let ((local-copy (copy-designation-using-slot-value-conses
				   designation)))
		 (note-designation local-copy)
		 local-copy))))
	((and (consp designation)
	      (=f (length designation) 3))
	 (let* ((local-parent-designation
		  (lookup-previous-reference-and-note-designation
		    (domain-of-designation designation)))
		(local-copy
		  (slot-value-list
		    (first designation)
		    (copy-role-using-slot-value-conses
		      (role-of-designation designation))
		    (copy-designation-using-slot-value-conses
		      local-parent-designation))))
	   (note-designation local-copy)
	   local-copy))
	;; No designations should get down here, but if they do, just return 'em.
	(t designation)))

(defun note-link-for-forward-chaining
       (rule designation symbolic-value? sense?
	&optional (second-focus-designation? nil))
  (let* ((chaining-list-symbol
	   (chaining-symbol-for-designation designation))
	 (focus-symbol-for-link? nil)
	 (local-name-for-focus? nil)
	 (second-focus-symbol-for-link? nil)
	 (second-local-name-for-focus? nil)
	 new-link)
    (multiple-value-setq (focus-symbol-for-link? local-name-for-focus?)
      (chaining-focal-role-and-local-name-for-designation designation))

    ;; GENSYMCID-1220: Detecting when a workspace is moved/scaled
    ;; Here we have to mark the rule as `self-referenced' first, then in
    ;; `really-invoke-rules?' (on firing the rule) the flag is checked.
    (case (role-name-of-role (role-of-designation designation))
      ((this-workspace
        this-rule)
       (setf (self-referenced-p rule) t)))

    (when second-focus-designation?
      (multiple-value-setq
	(second-focus-symbol-for-link? second-local-name-for-focus?)
	(chaining-focal-role-and-local-name-for-designation
	  second-focus-designation?)))
    (setq new-link (make-forward-chaining-link
		     rule
		     designation
		     focus-symbol-for-link?
		     local-name-for-focus?
		     symbolic-value?
		     sense?
		     second-focus-designation?
		     second-focus-symbol-for-link?
		     second-local-name-for-focus?))
    (loop for entry in names-and-info-for-chaining
	  do
      (when (and (eq chaining-list-symbol (car-of-cons entry))
		 (equal-forward-chaining-link new-link (cdr-of-cons entry)))
	(reclaim-forward-chaining-link new-link)
	(return nil))
	  finally
	    (setf names-and-info-for-chaining
		  (slot-value-cons
		    (slot-value-cons chaining-list-symbol new-link)
		    names-and-info-for-chaining)))))




;;; The function `note-links-for-dynamic-roles' takes an unabbreviated
;;; designation and rule and generates forward chaining links for any dynamic
;;; roles in the designation.  This function need not lookup any previous
;;; designations or note them, since that will have already been done.

(defun note-links-for-dynamic-roles (rule unabbreviated-designation)
  (when (consp unabbreviated-designation)
    (let ((role (simple-role-of-role
		  (role-of-designation unabbreviated-designation)))
	  (domain? (domain-of-designation unabbreviated-designation)))
      (when (and (consp role)
		 (invertible-designation-p unabbreviated-designation))
	(case (car-of-cons role)
	  ((related)
	   (note-link-for-forward-chaining
	     rule unabbreviated-designation
	     (second role)			; relation name
	     :related
	     domain?))
;	  ((first-of-list second-of-list next-to-last-of-list last-of-list
;			  list-iterator)
;	   (note-link-for-forward-chaining
;	     rule unabbreviated-designation nil :list-member))
	  ))
      (when domain?
	(note-links-for-dynamic-roles rule domain?)))))

;; It has not yet been decided if we will ever forward chain from list contents,
;; but this would be the spot to collect such references.  An example is
;; commented out above.  -jra 12/28/89






;;;; Backward Chaining




;;; Backward chaining will work in much the same way as forward chaining does
;;; above, in that references within consequents of rules will be listed under
;;; chaining symbols whose links have parent designation information, and those
;;; links will be made through a syntactic examination of the consequents of
;;; rules in the same manner that forward chaining links are made.  The major
;;; difference is that the links for this system will not contain either a
;;; symbolic value or a sense, since there is no sense matching in backward
;;; chaining.  Backward chaining shares a feature with forward chaining in that
;;; it blithely and blindly assumes that the focal roles it needs in invoking a
;;; rule are available for that rule.

;;; With the requirements of data set consistency and reference-perspective
;;; side-effect free expression evaluation (RePSEFEE), there is only a limited
;;; context within which we can recursively run backward chaining rules.  These
;;; restrictions are to provide a situation where the only G2 variable which may
;;; be mutated during a backward chain is the one being backward chained to.  If
;;; this is not the case, then the rules which are backward chained to must be
;;; scheduled to occur and the current attempt to backward chain must return
;;; UNKNOWN.  The restrictions are as follows:

;;; 1.  We can at most go one deep in a recursive backward chain.  A second
;;; backward chain recursion would be setting a second variable, which violates
;;; RePSEFEE.

;;; 2.  We can only recursively backward chain to rules which have one
;;; side-effect causing action in their consequent.  This is checked for in the
;;; code which sets up backward chaining links and is reflected in the frame
;;; flag recursive-backward-chain.

;;; All other backward chaining must call invoke-rule outside of the
;;; recursive closure of invoke-rules-for-backward-chaining.

;;; We need to develop a concise description of the restrictions that apply for
;;; forward and backward chaining for the user manual!  It is not obvious when
;;; it works and when it won't.  No chaining can occur through roles which are
;;; not invertible.  The only non-invertible role right now is "named by".






;;;; Depth-First and Breadth-First Backward Chaining




;;; It is useful to have two modes of backward chaining for G2, depth-first and
;;; breadth-first.  Depth-first backward chaining is useful for controlling the
;;; amount of data which is sought by the inference engine, and controlling
;;; which hypotheses are tested first.  If, for example, the user is responding
;;; to questions to supply values for variables involved in a backward chain,
;;; this depth-first approach should be used to limit the number of questions
;;; presented.  Breadth-first backward chaining is useful where the rules which
;;; could set the value of a variable are logically disjoint and where there is
;;; no problem with starting data service on many values at the same time.  The
;;; classic situation where data service should controlled is where the operator
;;; is answering questions to supply data.

;;; For breadth-first backward chaining it is the intent to find all rule
;;; instances which could supply a value for a variable and schedule them all
;;; for execution.  When one does supply a value for this variable, then the
;;; requests for invocation of the other rules should be retracted.  If a rule
;;; executes, runs to completion, but does not fire, then it should inform those
;;; variables waiting for it that it has completed.  If all which could supply
;;; the value of a variable have completed but none has actually fired and
;;; supplied a value for the variable, then the variable should be declared to
;;; have failed.

;;; For depth-first backward chaining, an ordered list of rule instances should
;;; be generated, and the instances should be run to completion in turn.  When
;;; one fires and causes this variable to receive a value then the continuation
;;; of the rest of them should be discarded.

;;; The following paragraph describes the needs of variables and rule instances
;;; for pointers between each other for wake up and for withdrawing requests for
;;; execution and requests for value.

;;; When rule instances are already scheduled to be run, these calls for
;;; execution should fold in with the previous executions.  When a variable has
;;; invoked a rule instance, the variable needs to keep a pointer to the
;;; instance so that it can withdrawn it's need for computation if something
;;; else supplies a value for the variable.  The rule instance needs to keep a
;;; pointer to the variable to inform the variable that the instance has
;;; completed.  When a rule instance needs a value from a variable, the variable
;;; needs to keep a pointer to the rule instance to wake it up, and the rule
;;; instance needs to keep a pointer to the variable to remove the wake up in
;;; case it is woken up by something else.  When a variable needs a value from
;;; another requested variable, the requested variable needs to keep a pointer
;;; to the requestor for wake ups, and the requestor needs to keep a pointer to
;;; the requested variable to remove the wake up when something else wakes up
;;; the requestor.

;;; These needs can be clumped into two sets which should be included as part of
;;; rule instances and variables.  The sets are things-this-variable-is-
;;; interested-in and things-interested-in-this-variable.  The same slots are
;;; needed for rule-instances, and a things-this-display-is-interested-in type
;;; slot for displays and inter-g2-data-service-requests.  The functions needed
;;; to implement the operations described in the previous paragraph are:

;;; For breadth-first backward chaining scheduling of invocations.  This
;;; function is free to store the purpose and interested party in any way it
;;; sees fit, but for backward chaining purpose and a variable interested party,
;;; it is required to keep a pointer to the variable and inform it when the rule
;;; has completed.  This function should also add each scheduled instance to the
;;; variable with add-rule-instance-to-variable-interests when the purpose is
;;; backward-chaining and the party is a variable.

;;; (generate-and-schedule-rule-instances
;;;   rule focal-role focal-object purpose interested-party? priority?)

;;; For a variable cancelling its request for the invocation of a particular
;;; rule instance, this function should be used.  This will happen when backward
;;; chaining for a variable is cancelled.  This will also happen in
;;; put-current-value when a variable receives a value.  There are two possible
;;; situations when this is called from put-current-value.  The first is where
;;; something other than this rule instance has set the value of this variable.
;;; The second is where this rule-instance is currently executing and is setting
;;; the value of this variable.

;;; (remove-request-for-rule-instance-invocation rule-instance variable)

;;; For a rule to inform a variable that it has completed (whether or not it
;;; actually fired) it should call the following function.  If a variable was
;;; being backward chained to and this rule instance succeeded in supplying a
;;; value for it then the variable would have already removed itself from the
;;; rule instance's interested parties list using remove request for rule
;;; instance.

;;; (rule-instance-completed variable rule-instance)

;;; For a variable to inform a thing that it has received a value, it should
;;; call the following function.  (This will encapsulate some of the code from
;;; the old remove-wake-ups-from-variable-and-wake-them-up.)  The thing should
;;; remove the variable from the list of things it is interested in and do
;;; whatever it does to wake itself up.

;;; (variable-has-received-a-value thing variable)

;;; When get-current-value is called on a variable and that variable does not
;;; have a value, it will push itself onto the
;;; *variables-that-did-not-have-values* list and note the current computation
;;; frame in its list of things-interested-in-this-variable.  When the code
;;; binding *variables-that-did-not-have-values* wishes to let go the variable,
;;; then it should call the following function.  This will remove the thing from
;;; the things-interested-in-this-variable list.  As well, if that list is now
;;; empty, and there is no clean-up postponer for this variable, then the
;;; variable should stop any backward chaining still going on to obtain its
;;; value.

;;; (remove-request-for-variable-value variable thing)

;;; When a rule instance or some other thing which runs expressions has a
;;; variable on its list of things it is interested in, but wants to retry an
;;; expression it should call the following function for each interesting
;;; variable.  This should cause the variable to remove the thing from the
;;; things-interested-in-this-variable list.  Also, if there is no clean-up
;;; postponer for this variable, the thing should be put into that slot of the
;;; variable.  When a thing calls this function for a variable, it is
;;; guaranteeing that it will also call perform-postponed-clean-up on the
;;; variable after the thing has had its chance to get back on the variable's
;;; list of interested things.  Note that in recursive chaining another thing
;;; may also call remove-request-for-variable-value-without-clean-up and then
;;; call perform-postponed-clean-up.  Any clean-ups should be postponed until
;;; the thing which originally called remove-request-for-variable-value-
;;; without-clean-up calls back.

;;; (remove-request-for-variable-value-without-clean-up variable thing)

;;; After a thing has called remove-request-for-variable-value-without-clean-up
;;; has had a chance to renew any request for the value of a variable, it should
;;; call perform-postponed-clean-up.  If this function is called on a variable
;;; and the thing passed is the thing which first postponed clean-up, then the
;;; clean-up postponer slot should be cleared, and if there are no longer any
;;; things interested in this variable, then this variable should perform any
;;; clean-ups (i.e. withdrawing of backward chaining) that is required.

;;; (perform-postponed-clean-up variable thing)

;;; If a variable has had all interested things removed from it, then it should
;;; call this function to withdraw any backward chaining which is ongoing for
;;; it.  The list of things-this-variable-is-interested-in should be reclaimed,
;;; and requests for invocations of things on this list should be removed.
;;; Also, if this variable has a list of contexts-for-depth-first-backward-
;;; chaining, the contexts and list should be reclaimed.

;;; (withdraw-backward-chaining variable)








;;;; Backward Chaining Installation



;;; The macros `make-backward-chaining-link' and `reclaim-backward-chaining-
;;; link' get and return backward chaining links from their pool.


;(def-structure
;  (backward-chaining-link
;    (:constructor make-backward-chaining-link
;     (backward-link-rule backward-link-designation
;			 backward-link-focus
;			 backward-link-focus-local-name
;			 backward-link-symbolic-value)))
;  backward-link-rule
;  (backward-link-designation nil :reclaimer reclaim-installation-tree)
;  backward-link-focus
;  backward-link-focus-local-name  
;  backward-link-symbolic-value)

(def-class (backward-chaining-link dependent-frame define-predicate)
  (backward-link-rule nil vector-slot system save)
  (backward-link-designation nil vector-slot system save)
  (backward-link-focus nil vector-slot system save)
  (backward-link-focus-local-name nil vector-slot system save)
  (backward-link-symbolic-value nil vector-slot system save))

(defmacro reclaim-backward-chaining-link (link)
  `(delete-frame ,link))

#-chestnut-trans
(defun-simple backward-chaining-link-p-function (link)
  (backward-chaining-link-p link))

#-chestnut-trans
(defun-simple backward-link-focus-function (link)
  (backward-link-focus link))

(defun make-backward-chaining-link
       (backward-link-rule
	backward-link-designation
	backward-link-focus
	backward-link-focus-local-name
	backward-link-symbolic-value)
  (let ((new-frame (make-frame 'backward-chaining-link)))
    (let*-sim ((current-block-of-dependent-frame 'dependent-frame-has-no-owner))
      (setf (backward-link-rule new-frame) backward-link-rule)
      (setf (backward-link-designation new-frame) backward-link-designation)
      (setf (backward-link-focus new-frame) backward-link-focus)
      (setf (backward-link-focus-local-name new-frame) backward-link-focus-local-name)
      (setf (backward-link-symbolic-value new-frame) backward-link-symbolic-value))
    new-frame))

(def-class-method copy-frame (backward-chaining-link)
  (make-backward-chaining-link
    (backward-link-rule backward-chaining-link)
    (copy-for-slot-value (backward-link-designation backward-chaining-link))
    (backward-link-focus backward-chaining-link)
    (backward-link-focus-local-name backward-chaining-link)
    (backward-link-symbolic-value backward-chaining-link)))

(def-substitution-macro equal-backward-chaining-link (link1 link2)
  (and (eq (backward-link-rule link1)
	   (backward-link-rule link2))
       (equal (backward-link-designation link1)
	      (backward-link-designation link2))
       (equal (backward-link-focus link1)
	      (backward-link-focus link2))
       (equal (backward-link-focus-local-name link1)
	      (backward-link-focus-local-name link2))
       (equal (backward-link-symbolic-value link1)
	      (backward-link-symbolic-value link2))))




;;; The function `generate-forward-and-backward-chaining-links' takes a rule and
;;; the parse for that rule and generates any forward and backward chaining
;;; links for that rule.  Note that the frame flags for forward and backward
;;; chaining should already be set on the rule before this function is called.
;;; This function returns a slot value list of forward and backward chaining
;;; links.

(defun generate-forward-and-backward-chaining-links (rule translation)
  (let* ((current-block-of-dependent-frame 'dependent-frame-has-no-owner)
	 (names-and-info-for-chaining nil)
	 (frame-flags (frame-flags rule)))
    (note-names-and-info-for-forward-chaining-in-rule-translation
      translation rule frame-flags)
    (note-names-and-info-for-backward-chaining-in-rule-translation
      translation rule frame-flags)
    names-and-info-for-chaining))




;;; The substitution macros `install-forward-chaining-link' and `deinstall-
;;; forward-chaining-link' take a symbol and a forward chaining link and either
;;; install the link or remove that link from the property of the given name.

(def-substitution-macro install-forward-chaining-link
			(name forward-chaining-link)
  (setf (forward-chaining-list name)
	(eval-cons forward-chaining-link
		   (forward-chaining-list name)))
  nil)

(def-substitution-macro deinstall-forward-chaining-link
			(name forward-chaining-link)
  (setf (forward-chaining-list name)
	(delete-eval-element
	  forward-chaining-link
	  (forward-chaining-list name)))
  nil)




;;; The functions `install-chaining-links' and `deinstall-chaining-links' take
;;; lists of chaining links as generated by generate-forward-and-backward-
;;; chaining links and generate-cell-chaining-links and install and deinstall
;;; those links in the properties used by the chaining mechanisms.  These
;;; functions are also responsible for decaching the class based chaining
;;; caches.

(defun install-chaining-links (chaining-links)
  (when chaining-links
    (decache-class-chaining-lists)
    (loop for (name . link) in chaining-links
	  do
      (cond ((forward-chaining-link-p link)
	     (install-forward-chaining-link name link))
	    ((backward-chaining-link-p link)
	     (install-backward-chaining-link name link))
	    (t
	     #+development
	     (error "Installing unidentified chaining link ~a."
		    link)
	     nil)))))

(defun deinstall-chaining-links (chaining-links)
  (when chaining-links
    (decache-class-chaining-lists)
    (loop for (name . link) in chaining-links
	  do
      (cond ((forward-chaining-link-p link)
	     (deinstall-forward-chaining-link name link))
	    ((backward-chaining-link-p link)
	     (deinstall-backward-chaining-link name link))
	    (t
	     #+development
	     (error "Deinstalling unidentified chaining link ~a."
		    link)
	     nil)))))




;;; The function `update-backward-chaining-lists' takes a rule, an old raw
;;; translation for the rule, and a new raw translation of the rule as
;;; arguments.  It removes any backward chaining links stored for the old source
;;; and then installs new links for the new source.

;; Note that this has been replaced by analyzers called from the slot value
;; compiler for rules.  -jra 10/8/91




;;; The functions `install-backward-chaining-link' and `deinstall-backward-
;;; chaining-link' and used to manage backward chaining link installation status
;;; of links.  When we implement caching of links, the decachings must be
;;; installed here.

;;; Note that this function keeps a partial ordering on the links that it adds
;;; to backward chaining lists, such that any links whose parent references are
;;; proper names will be added to the ends of backward chaining lists, and all
;;; other references are added to the beginning of the the lists.  This is so
;;; that the ordering of specific and generic rule invocations during backward
;;; chaining are maintained to have specific references be chained on first.
;;; See the documentation for the function invoke-rules-for-backward-chaining
;;; for a more complete description.

(defun install-backward-chaining-link (name backward-chaining-link)
  (let ((designation (backward-link-designation backward-chaining-link)))
    (if (and (domain-of-designation designation)
	     (symbolp (domain-of-designation designation)))
	(setf (backward-chaining-list name)
	      (nconc (backward-chaining-list name)
		     (eval-cons backward-chaining-link nil)))
	(setf (backward-chaining-list name)
	      (eval-cons backward-chaining-link
			 (backward-chaining-list name))))
    (decache-class-chaining-lists)
    nil))

(defun deinstall-backward-chaining-link (name backward-chaining-link)
  (setf (backward-chaining-list name)
	(delete-eval-element
	  backward-chaining-link
	  (backward-chaining-list name)))
  (decache-class-chaining-lists)
  nil)




(defun note-names-and-info-for-backward-chaining-in-rule-translation
       (translation rule frame-flags)
  (let ((designations-in-rule nil))
    ;; First note any designations in preceeding FOR iterators.
    (loop while (and (consp translation) (eq (first translation) 'for))
	  do
      (lookup-previous-reference-and-note-designation (second translation))
      (setq translation (third translation)))
    ;; If this rule is not a when or whenever rule, note designations in
    ;; the antecedent and then note any backward chaining.
    (if (invocable-via-backward-chaining-of-flag-vector-p frame-flags)
	(progn
	  (note-designations-in-antecedant
	    (second translation))
	  (note-names-and-info-for-backward-chaining-in-actions
	    (third translation)
	    rule)))
    ;; Clean up any of the held designation structure.
    (reclaim-slot-value designations-in-rule)))




;;; The function `note-designations-in-antecedant' takes an antecedant and notes
;;; all designations within on the designations-in-rule special variable.

(defun note-designations-in-antecedant (expression)
  (cond ((null expression) nil)
	((designation-p expression)
	 (lookup-previous-reference-and-note-designation expression))
	((consp expression)
	 (let ((operator (first expression)))
	   (if (and (symbolp operator)
		    (neq operator 'quote))
	       (let ((template? (lookup-function-template operator)))
		 (if (null template?)
		     (loop for sub-expression in (cdr expression)
			   do
		       (note-designations-in-antecedant sub-expression))
		     (note-designations-in-antecedant-given-template
		       expression template?))))))))

(defun note-designations-in-antecedant-given-template (expression template)
  (loop for argument in (cdr expression)
	for argument-type in (cdr template)
	do
    (case argument-type
      ((expression)
       (note-designations-in-antecedant argument))
      ((designation)
       (lookup-previous-reference-and-note-designation argument))
      ((scope)
       (let ((designation (slot-value-cons
			    'any
			    (copy-for-slot-value argument))))
	 (lookup-previous-reference-and-note-designation designation)
	 (reclaim-slot-value designation)))
      ((other)
       t)
      (otherwise
	#+development
	(cerror "Continue."
		"Unknown argument type ~a from function template."
		argument-type)))))

(defun note-names-and-info-for-backward-chaining-in-actions (actions rule)
  (if (consp actions)
      (case (car actions)
	((and in-order simultaneously)
	 (loop for action in (cdr actions)
	       doing
	   (note-names-and-info-for-backward-chaining-in-actions
	     action rule)))
	;; Note the designation which is being set.
	((conclude-not)
	 (note-link-and-designations-for-backward-chaining
	   rule (second actions) nil))
	;; Note the designation which is being set.  If a value is being
	;; set into the variable denoted by this designation, and that
	;; value is a quoted symbol, then store that as the symbolic
	;; value of the backward link.
	((conclude)
	 (if (and (consp (third actions))
		  (eq (first (third actions)) 'quote)
		  (symbolp (second (third actions))))
	     (note-link-and-designations-for-backward-chaining
	       rule (second actions) (second (third actions)))
	     (note-link-and-designations-for-backward-chaining
	       rule (second actions) nil))))))




;;; Given a designation and a rule, `note-link-and-designations-for-backward-
;;; chaining' will place whatever backward chaining links that need to be
;;; generated onto the names-and-info-for-chaining list and note the given
;;; designations onto designations-in-rule.


(defun note-link-and-designations-for-backward-chaining
       (rule designation symbolic-value?)
  ;; The chaining symbol names the backward-chaining-list where this
  ;; generated link will be stored.
  (let ((unabbreviated-designation
	  (lookup-previous-reference-and-note-designation designation)))
    (if (invertible-designation-p unabbreviated-designation)
	(note-link-for-backward-chaining
	  rule unabbreviated-designation symbolic-value?))))

(defun note-link-for-backward-chaining
       (rule designation symbolic-value?)
  (let ((chaining-symbol (chaining-symbol-for-designation designation))
	focal-role?
	local-name-for-focus?
	new-link)
    (multiple-value-setq (focal-role? local-name-for-focus?)
      (chaining-focal-role-and-local-name-for-designation designation))
    (setq new-link (make-backward-chaining-link
		     rule
		     (make-simple-designation-slot-value-copy designation)
		     focal-role?
		     local-name-for-focus?
		     symbolic-value?))
    (loop for entry in names-and-info-for-chaining
	  do
      (cond ((and (eq chaining-symbol (car-of-cons entry))
		  (backward-chaining-link-p (cdr-of-cons entry))
		  (equal-backward-chaining-link new-link (cdr-of-cons entry)))
	     (reclaim-backward-chaining-link new-link)
	     (return nil)))
	  finally
	    (setf names-and-info-for-chaining
		  (slot-value-cons
		    (slot-value-cons chaining-symbol new-link)
		    names-and-info-for-chaining)))))




;;; The function `invoke-backward-chaining-for-symbolic-class-references' takes
;;; an object and the set of possible symbolic values associated with that
;;; object, and notes the backward chaining likes which could refer to this
;;; object.

(defun invoke-backward-chaining-for-symbolic-class-references
       (object possible-values? symbolic-value-required?)
  (loop for link in (backward-chaining-list-for-classes
		      (class-inheritance-path
			(class-description-slot object)))
	for symbolic-value? = (backward-link-symbolic-value link)
	for designation = (backward-link-designation link)
	do
    (if (and (or (not symbolic-value-required?)
		 symbolic-value?)
	     (or (null symbolic-value?)
		 (null possible-values?)
		 (memq symbolic-value? possible-values?))
	     (not (symbolp designation))
	     (not (and (domain-of-designation designation)
		       (symbolp (role-of-designation designation)))))
	(add-tuple-to-backward-link-list link object))))

(defun invoke-backward-chaining-for-class-references (object)
  (loop for link in (backward-chaining-list-for-classes
		      (class-inheritance-path
			(class-description-slot object)))
	for designation = (backward-link-designation link)
	do
    (if (and (not (symbolp (backward-link-designation link)))
	     (not (and (domain-of-designation designation)
		       (symbolp (role-of-designation designation)))))
	(add-tuple-to-backward-link-list link object))))




;;; The function `invoke-rules-for-backward-chaining' takes a variable and does
;;; the following.  It searches through all the backward chaining lists which
;;; could apply to this variable and its parents and stores up all of the rule,
;;; focal role, and focal object tuples whose invocation could supply a value
;;; for this variable.  As it is collecting this list, it sorts the rules by
;;; their backward chaining precedence. 

;;; Note that the order in which these rules are collected is important, since
;;; it provides an ordering within the same precedence.  Specific rules should
;;; be invoked before generic rules, so we should collect specific (i.e.  rules
;;; which reference the variable or parent by name) referencing rules last.  For
;;; direct references we can insure this order by the ordering of collections
;;; here.  For efficient correct ordering of rules which reference a connected
;;; object by name, and this variable by class, the backward chaining list of
;;; the class of a variable should be ordered such that the named references of
;;; parents should be on the end of the list.  That ordering will propagate to
;;; the list being gathered here.

;;; Within the new system of backward chaining, we will be relying more on the
;;; variable to determine when it should or shouldn't attempt to invoke rules to
;;; backward chain.  For old style backward chaining we invoke all rules for
;;; backward chaining every time they are asked for.  For new style backward
;;; chaining we cause new invocations only if there are no old invcations still
;;; attempting to complete.  This can be determined by checking if there is an
;;; existing backward chaining structure in the variable and if there are any
;;; objects this variable is interested in.  Since we will never get down to
;;; this function if there is a formula which could supply a value for the
;;; variable, we can be assured that the only things on the interested list will
;;; be rule instances.  There is a question about whether we should cause a
;;; retry of the currently pending rule instances when the variable is asked for
;;; again, since the dynamic state of some of these rule instances may have
;;; changed such that the rule instance could actually run even though there has
;;; been no wake up to the rule.

(defun-simple add-tuple-to-backward-link-list (link object)
  (loop with new-precedence = (backward-chaining-precedence-function
                               (backward-link-rule link))
	with new-entry = (eval-cons-macro
                          (eval-cons-macro link object)
                          *links-and-objects*)
	for splice-point = nil then link-position
	for link-position on *links-and-objects*
	until (<= new-precedence
		  (backward-chaining-precedence-function
                   (backward-link-rule
                    (car-of-cons (car-of-cons link-position)))))
	finally
        (if (null splice-point)
            (setq *links-and-objects* new-entry)
          (progn
            (setf (cdr new-entry) (cdr-of-cons splice-point))
            (setf (cdr splice-point) new-entry)))))

(defun invoke-rules-for-backward-chaining (variable)
  (cond ((null (backward-chain-priority? variable))
	 (let ((data-type (type-specification-of-variable-or-parameter-value variable))
	       (*links-and-objects* nil))
	   ;; Collect link, role, and object tuples into an eval list in the
	   ;; special variable *links-and-objects*.
	   (collect-rules-for-backward-chaining variable data-type)
	   (setf (backward-chain-priority? variable) priority-of-current-task)
	   (setf (backward-chain-new-rules variable) *links-and-objects*)))
	(t
	 (maximize-priority-of-variable variable priority-of-current-task)))
  (execute-backward-chaining-for-rules variable))




;;; When the last of the pending requests for a variable's value have been
;;; withdrawn, `withdraw-backward-chaining' will be called on the variable.
;;; This function should withdraw any pending requests for the execution
;;; performed for backward chaining, stop any further requests from being
;;; generated, and stop any tasks to check the variable for failure, or to probe
;;; the variable when it has already failed.

(defun-simple withdraw-backward-chaining (variable)
  (let ((new-rules? (backward-chain-new-rules variable))
	(interest-list (things-this-variable-is-interested-in variable)))
    ;; Clean up the backward chaining structure.
    (setf (backward-chain-priority? variable) nil)
    (when new-rules?
      (reclaim-eval-tree new-rules?)
      (setf (backward-chain-new-rules variable) nil))
    ;; Clean up any formula-invocations.
    (when (formula-invocation? variable)
      (cancel-formula-for-backward-chaining variable))
    ;; Maybe remove this if only used for formulas.  -jra 5/13/92
    (cancel-task (task-for-wake-up? variable))
    ;; Remove requests for things previously found to be interesting.
    (when interest-list
      (setf (things-this-variable-is-interested-in variable) nil)
      (loop for interesting-thing in interest-list
	    do
	(cond ((rule-instance-p interesting-thing)
	       (remove-request-for-rule-instance-invocation
		 interesting-thing variable))
	      ((and (framep interesting-thing)
		    (variable-p interesting-thing))
	       (remove-request-for-variable-value interesting-thing variable))
	      #+development
	      (t
	       (cerror "Continue withdraw backward chaining."
		       "Withdraw-backward-chaining found something other than ~
                        a rule-instance or variable in a variable's interest ~
                        list.  Unknown thing = ~s."
		       interesting-thing))))
      (update-backward-chaining-displays variable)
      (reclaim-eval-list-macro interest-list)))
    ;; Stop any detection of failure or any probing if already failed.
    (cancel-task (task-to-check-variable? variable))
    ;; If not failed, clear eariliest unsatisfied request.  How can we fail if
    ;; we're no longer trying?  We can't.
    (when (not (failed-p variable))
      (setf (time-of-oldest-unsatisfied-request? variable) nil))
    nil)




;;; When a variable has requested the invocation of a rule instance for backward
;;; chaining and that rule instance has completed, the rule instance will call
;;; `rule-instance-completed' on the requesting variable and pass itself along.
;;; This function should remove the rule-instance from the list of things-this-
;;; variable-is-interested-in.  If this list is now empty, this function should
;;; continue backward chaining.

(defun-void rule-instance-completed (variable rule-instance)
  (let ((pruned-interests
	  (delete-eval-element
	    rule-instance (things-this-variable-is-interested-in variable))))
    (setf (things-this-variable-is-interested-in variable) pruned-interests)
    (update-backward-chaining-displays variable)
    (when (and (null pruned-interests)
	       (not (schedule-task-in-place-p (task-for-wake-up? variable))))
      (with-current-scheduling
	  ((task-for-wake-up? variable) (backward-chain-priority? variable))
	(execute-backward-chaining-for-rules
	  variable)))))

(defun add-rule-instance-to-variable-interests (variable rule-instance)
  #-SymScale
  (setf (things-this-variable-is-interested-in variable)
	(eval-cons
	  rule-instance
	  (things-this-variable-is-interested-in variable)))
  #+SymScale
  (eval-push-atomic rule-instance
		    (things-this-variable-is-interested-in variable))
  (update-backward-chaining-displays variable)
  nil)




;;; The function `execute-backward-chaining-for-rules' gets called in two
;;; situations.  The first is when the variable is initially being backward
;;; chained to.  If there are no old rules it is called in the recursive descent
;;; of get-current-value.  If there are old rules, it is scheduled to occur.  In
;;; this situation there may be any number of new or old rules.  The other case
;;; in which this function will be called is when the last of the rule instances
;;; on the list of things this variable is interested in completes.  In that
;;; this function should check if there are any remaining rules, and will
;;; execute them.

(defun-void execute-backward-chaining-for-rules (variable)
  (let ((new-rules (backward-chain-new-rules variable))
	(*current-computation-frame* variable))
    (cond ((and (null new-rules)
		(null (things-this-variable-is-interested-in variable)))
	   ;; No rules were available to set this, clear the backward chain and
	   ;; set this variable to failed.
	   (setf (backward-chain-priority? variable) nil)
	   (cancel-task (task-for-wake-up? variable))
	   (when (not (value-of-variable-is-current variable))
	     (task-to-detect-failure variable)))
	  ((depth-first-p variable)
	   (execute-depth-first-backward-chain variable))
	  (t
	   (execute-breadth-first-backward-chain variable)))))

(defun execute-breadth-first-backward-chain (variable)
  (loop with link-list = (backward-chain-new-rules variable)
	for link-entry in link-list
	for link = (car link-entry)
	for focal-role? = (backward-link-focus link)
	for rule = (backward-link-rule link)
	do
    (when (runnable-p rule)
      (when (major-trace-message-will-be-written-p)
	(write-backward-chaining-trace-message
	  variable link (cdr link-entry) nil))
      (if focal-role?
	  (generate-and-schedule-rule-instances
	    rule
	    focal-role? (backward-link-focus-local-name link) (cdr link-entry)
	    'backward-chaining variable
	    (backward-chain-priority? variable) nil)
	  (generate-and-schedule-rule-instances
	    rule nil nil nil
	    'backward-chaining variable
	    (backward-chain-priority? variable) nil)))
    (reclaim-eval-cons-macro link-entry)
	finally
	  (reclaim-eval-list-macro link-list)
	  (setf (backward-chain-new-rules variable) nil)
	  (when (null (things-this-variable-is-interested-in variable))
	    (setf (backward-chain-priority? variable) nil)
	    (task-to-detect-failure variable))))

(defun execute-depth-first-backward-chain (variable)
  (when (null (things-this-variable-is-interested-in variable))
    (loop for link-list = (backward-chain-new-rules variable)
			then rest-of-links?
	  while link-list
	  for link-entry = (car link-list)
	  for link = (car link-entry)
	  for focal-role? = (backward-link-focus link)
	  for rule = (backward-link-rule link)
	  for rest-of-links? = (cdr link-list)
	  do
      (when (runnable-p rule)
	(when (major-trace-message-will-be-written-p)
	  (write-backward-chaining-trace-message
	    variable link (cdr link-entry) t))
	(if focal-role?
	    (generate-and-schedule-rule-instances
	      rule
	      focal-role? (backward-link-focus-local-name link) (cdr link-entry)
	      'backward-chaining variable
	      (backward-chain-priority? variable) nil)
	    (generate-and-schedule-rule-instances
	      rule nil nil nil
	      'backward-chaining variable
	      (backward-chain-priority? variable) nil)))
      (reclaim-eval-cons-macro link-list)
      (reclaim-eval-cons-macro link-entry)
	  until (things-this-variable-is-interested-in variable)
	  while rest-of-links?
	  finally
	    ;; If this variable has nothing on its interest list, then this
	    ;; backward chain has failed to generate and rule instances, and this
	    ;; chain has failed.
	    (setf (backward-chain-new-rules variable) rest-of-links?)
	    (when (null (things-this-variable-is-interested-in variable))
	      (setf (backward-chain-priority? variable) nil)
	      (task-to-detect-failure variable)))))

(defun write-backward-chaining-trace-message (variable link object? depth-first?)
  (write-major-trace-message
    (let ((rule (backward-link-rule link))
	  (focal-role? (backward-link-focus link))
	  (local-name? (backward-link-focus-local-name link))
	  (priority (backward-chain-priority? variable))
	  (chain-type (if depth-first? "depth first" "breadth first")))
      (if focal-role?
	  (if local-name?
	      (tformat
		"Scheduling ~NF for execution at priority ~a with ~NF as the ~a ~a ~
               while ~a backward chaining for the value of ~NF."
		rule
		priority
		object?
		focal-role?
		local-name?
		chain-type
		variable)
	      (tformat
		"Scheduling ~NF for execution at priority ~a with ~NF as the ~a ~
               while ~a backward chaining for the value of ~NF."
		rule
		priority
		object?
		focal-role?
		chain-type
		variable))
	  (tformat
	    "Scheduling ~NF for execution at priority ~a while ~a ~
           backward chaining for the value of ~NF."
	    rule
	    priority
	    chain-type
	    variable)))))

(defun collect-rules-for-backward-chaining (variable data-type)
  (let* ((name-or-names-for-variable? (name-or-names-for-frame variable))
	 (variable-name-cons?
          (if (and name-or-names-for-variable?
                   (symbolp name-or-names-for-variable?))
              (setq name-or-names-for-variable?
                    (eval-cons name-or-names-for-variable? nil))
            nil))
	 (parent-stack (make-parent-stack variable))
	 (possible-values?
          (if (and (eq data-type 'symbol) parent-stack)
              (value-set-given-attribute-and-class
               (parent-stack-attribute (car parent-stack))
               (parent-stack-attribute-class (car parent-stack)))
            nil)))
    ;; First check if there is a parent entity, and add rules refering
    ;; to it to the *links-and-objects* list.
    (if parent-stack
	(let ((parent-stack-entry (car-of-cons parent-stack)))
	  ;; Chain on the class of the parent, if this is a symbolic variable.
	  (if (eq data-type 'symbol)
	      (invoke-backward-chaining-for-symbolic-class-references
               (parent-stack-frame parent-stack-entry) possible-values? t))
	  ;; Chain on the attribute of the parent.
	  (loop with symbolic-value?
		for link in (backward-chaining-list-macro
                             (parent-stack-attribute parent-stack-entry))
		do
                (if (or (neq data-type 'symbol)
                        (or (null (setq symbolic-value?
                                        (backward-link-symbolic-value link)))
                            (null possible-values?)
                            (memq symbolic-value? possible-values?)))
                    (let ((parent-frame?
                           (find-referenced-parent
                            parent-stack (backward-link-designation link))))
                      (if parent-frame?
                          (add-tuple-to-backward-link-list link parent-frame?)))))
	  ;; If we are putting a value into a symbolic variable, chain on the
	  ;; name of the parent, since this variable may be referenced through
	  ;; it.
	  (if (eq data-type 'symbol)
	      (loop for name-for-parent
                    in (parent-stack-parent-names parent-stack-entry)
		    do
                    (loop for link in (backward-chaining-list-macro name-for-parent)
                          for symbolic-value? = (backward-link-symbolic-value link)
                          do
                          (if (and (eq name-for-parent (backward-link-designation link))
                                   symbolic-value?
                                   (or (null possible-values?)
                                       (memq symbolic-value? possible-values?)))
                              (add-tuple-to-backward-link-list link nil)))))))
    ;; Chain on the class names which apply to the variable.
    (if (eq data-type 'symbol)
	(invoke-backward-chaining-for-symbolic-class-references
         variable possible-values? nil)
      (invoke-backward-chaining-for-class-references variable))
    ;; Lastly, chain on the name of the variable, if it has any.
    (loop for name-for-variable in name-or-names-for-variable?
	  do
          (loop for link in (backward-chaining-list-macro name-for-variable)
                with symbolic-value?
                do
                (if (and (eq name-for-variable (backward-link-designation link))
                         (or (neq data-type 'symbol)
                             (and (or (null (setq symbolic-value?
                                                  (backward-link-symbolic-value link)))
                                      (null possible-values?)
                                      (memq symbolic-value? possible-values?)))))
                    (add-tuple-to-backward-link-list link nil))))
    (if variable-name-cons?
	(reclaim-eval-cons-macro variable-name-cons?))
    (reclaim-parent-stack parent-stack)))





;;;; Movement Chaining




;;; The macro `movement-sense-matches-p' takes a mover and a sense from a
;;; forward chaining link and returns whether or not the senses match.  Matching
;;; sense in this case means that either the stored sense is "is-moved", or the
;;; mover is "user" and the stored-sense is eq to the mover.

(def-substitution-macro movement-sense-matches-p (mover stored-sense)
  (or (eq stored-sense 'is-moved)
      (eq stored-sense mover)))

;;; GENSYMCID-1220: Detecting when a workspace is moved/scaled
;;; the purpose of `really-invoke-rules?' is to block some unwanted firing of rules.

(def-substitution-macro really-invoke-rules? (role? recipient chain-object)
  (case role?
    (kb-workspace ; this-workspace
     (if (self-referenced-p recipient)
	 (eq (get-workspace-if-any (superblock? recipient)) chain-object)
       t))
    (rule         ; this-rule
     (if (self-referenced-p recipient)
	 (eq recipient chain-object)
       t))
    ;; GENSYMCID-1283: G2-2011 JUNE 2014 Release gub whenever a workspace is moved
    ;; For compatibility, `whenever any item is moved' doesn't support WORKSPACE.
    (item
     (not (workspace-p chain-object)))
    ;; by default, pass all rules.
    (otherwise t)))

;;; Whenever an icon is moved and the system is running, the function
;;; `invoke-rules-for-movement-chaining' will be called with the icon which has
;;; just been moved and with a symbol naming the mover of the icon, currently
;;; either :moved-by-the-user or :moved-by-the-inference-engine.  This function
;;; will collect those whenever rules which should be invoked through event
;;; predicates which check for movement, and it will then schedule them for
;;; invocation.

(defun invoke-rules-for-movement-chaining (object mover &optional do-not-notify-ws-representations-p)
  (when (and (not do-not-notify-ws-representations-p)
	     g2-has-v5-mode-windows-p
	     (not ws-protocol-handle-moves-from-edge-change-p))
    (send-ws-representations-item-moved object 0 0))
  (let ((current-computation-frame-previously-bound?
         (framep *current-computation-frame*))
	(*links-and-objects* nil))
    (unless current-computation-frame-previously-bound?
      (setq *current-computation-frame* object))
    (collect-rules-for-movement-chaining object mover)
    ;; Schedule the collected rules for invocation.
    (loop for link-entry in *links-and-objects*
	  for link = (car link-entry)
	  for recipient = (forward-link-recipient link)
	  do
          ;; The forward link recipient will be either an update list or a rule
          ;; frame.  Do nothing if it is a true value update recipient or if the
          ;; rule is inactive.
          (when (and (not (true-value-update-recipient-p recipient))
                     (runnable-p recipient))
            (let* ((role? (forward-link-focus link))
                   (local-name? (if role?
                                    (forward-link-focus-local-name link)
                                  nil))
                   (chain-object (if role?
                                     (cdr link-entry)
                                   nil)))
              (when (really-invoke-rules? role? recipient chain-object)
                (write-major-movement-chaining-trace-message
                  object chain-object recipient role? mover)
                (generate-and-schedule-rule-instances
                  recipient role? local-name? chain-object 'forward-chaining nil
                  (rule-priority recipient) nil))))
          (reclaim-eval-cons-macro link-entry))
    (unless current-computation-frame-previously-bound?
      (setq *current-computation-frame* nil))
    (reclaim-eval-list-macro *links-and-objects*)))

(defun write-major-movement-chaining-trace-message
    (object chain-object recipient role? mover)
  (write-major-trace-message
    (if role?
	(tformat
	  "Scheduling event chaining to ~nf with ~nf as ~a because ~nf was moved by ~nf."
	  recipient
	  chain-object
	  role?
	  object
	  (case mover
	    ((is-moved-by-the-user) "the user")
	    ((is-moved-by-g2) *current-computation-frame*)))
	(tformat
	  "Scheduling event chaining to ~NF because ~NF was moved by ~NF."
	  recipient
	  object
	  (case mover
	    ((is-moved-by-the-user) "the user")
	    ((is-moved-by-g2) *current-computation-frame*))))))

(defun collect-rules-for-movement-chaining (object mover)
  (let* ((object-names? (name-or-names-for-frame object))
	 (object-name-cons?
	   (if (and object-names?
		    (symbolp object-names?))
	       (setq object-names? (eval-cons object-names? nil))
	       nil))
	 (parent-stack (make-parent-stack object)))
    ;; Chain to any name of the object.
    (loop for object-name in object-names?
	  do
      (loop for link in (forward-chaining-list-macro object-name)
	    for stored-sense = (forward-link-sense link)
	    do
	(if (and (movement-sense-matches-p mover stored-sense)
		 (eq object-name (forward-link-designation link)))
	    (add-tuple-to-link-list link nil))))
    ;; Chain to the attribute name of any parent entity.
    (if parent-stack
	(let ((parent-stack-entry (car-of-cons parent-stack)))
	  (loop for link in (forward-chaining-list-macro
			      (parent-stack-attribute parent-stack-entry))
		for stored-sense = (forward-link-sense link)
		do
	    (if (movement-sense-matches-p mover stored-sense)
		(let ((parent-frame? (find-referenced-parent
				       parent-stack
				       (forward-link-designation link))))
		  (if parent-frame?
		      (add-tuple-to-link-list link parent-frame?)))))))
    ;; Chain to references to a class of this object.
    (loop for link in (forward-chaining-list-for-classes
			(class-inheritance-path
			  (class-description-slot object)))
	  for stored-sense = (forward-link-sense link)
	  for designation = (forward-link-designation link)
	  do
      (if (and (movement-sense-matches-p mover stored-sense)
	       (not (symbolp designation))
	       (not (and (domain-of-designation designation)
			 (symbolp (role-of-designation designation)))))
	  (add-tuple-to-link-list link object)))
    (if object-name-cons? (reclaim-eval-cons-macro object-name-cons?))
    (reclaim-parent-stack parent-stack)))


;;; The function `invoke-rules-for-user-icon-movement-if-necessary' takes a block
;;; as its argument and will call `invoke-rules-for-movement-chaining' if the system
;;; is running and the block is an item.

;;; changed to set *current-computation-frame* rdf 5/25/93

(defun invoke-rules-for-user-icon-movement-if-necessary (block)
  (cond ((frame-of-class-p block 'item)
	 (let ((*current-computation-frame* (g2-window-for-this-workstation? current-workstation)))
	   (when (null *current-computation-frame*)
	     (setq *current-computation-frame* block))
	   (invoke-rules-for-movement-chaining block 'is-moved-by-the-user)))
	((and g2-has-v5-mode-windows-p
	      (not ws-protocol-handle-moves-from-edge-change-p))
	 (send-ws-representations-item-moved block 0 0))))


;;;; Existential Chaining

;;; Existential chaining encompasses chaining due to activation/deactivation,
;;; enable/disable, and creation.

;;; The macro `existential-sense-matches-p' takes a sense from a
;;; forward chaining link and returns whether or not it matches a key-sense.

(def-substitution-macro existential-sense-matches-p
    (stored-sense key-sense)
  (eq stored-sense key-sense))

;;; Whenever an item is activated, deactivated, enabled, disabled, or created,
;;; and the system is running, the function
;;; `invoke-rules-for-existential-chaining' will be called with that item.  The
;;; key-sense arg indicates what kind of event has occurred.  This function will
;;; collect those whenever rules which should be invoked through event
;;; predicates which check for the kind of event, and it will then schedule them
;;; for invocation.

(defun-simple invoke-rules-for-existential-chaining (object key-sense precomputed-links-and-objects)
  (let ((current-computation-frame-previously-bound?
         (framep *current-computation-frame*))
	(*links-and-objects* precomputed-links-and-objects))
    (unless current-computation-frame-previously-bound?
      (setq *current-computation-frame* object))
    (unless precomputed-links-and-objects
      (collect-rules-for-existential-chaining object key-sense))
    ;; Schedule the collected rules for invocation.
    (loop for link-entry in *links-and-objects*
	  for link = (car link-entry)
	  for recipient = (forward-link-recipient link)
	  do
          ;; The forward link recipient will be either an update list or a rule
          ;; frame.  Do nothing if it is a true value update recipient or if the
          ;; rule is inactive.
          (when (and (not (true-value-update-recipient-p recipient))
                     (runnable-p recipient))
            (let* ((role? (forward-link-focus link))
                   (local-name? (if role?
                                    (forward-link-focus-local-name link)
                                  nil))
                   (chain-object (if role?
                                     (cdr link-entry)
                                   nil)))
              (when (really-invoke-rules? role? recipient chain-object)
                (write-major-existential-chaining-trace-message
                  object chain-object recipient role? key-sense)
                (generate-and-schedule-rule-instances
                  recipient role? local-name? chain-object 'forward-chaining nil
                  (rule-priority recipient) nil))))
          (reclaim-eval-cons-macro link-entry))
    (unless current-computation-frame-previously-bound?
      (setq *current-computation-frame* nil))
    (reclaim-eval-list-macro *links-and-objects*)))

;;; Facilities to allow invoke-rules-for-existential-chaining to be
;;; scheduled.  This allows for the better handling of multiple
;;; existential events which can take place one after the other in
;;; the Lisp source code.
;;; Example: an item is created and then it is activated.
;;; We do not want invoke-rules-for-existential-chaining for the
;;; creation event until the item has been activated.

(defun-simple safe-invoke-rules-for-existential-chaining
    (object key-sense fsn precomputed-links-and-objects)
  ;; caller reclaims fsn
  (when (and (not (frame-has-been-reprocessed-p object fsn))
	     ;; The first clause of this (OR ...) has to do with a
	     ;; special case in g2-initialize-gsi-interface.
	     (or (and (frame-of-class-p object 'gsi-interface)
		      (runs-while-inactive-p object))
		 (permanent-block-p object)
		 (transient-p object)))
    (invoke-rules-for-existential-chaining object key-sense precomputed-links-and-objects)))

(defvar queue-existential-rules nil)
(defvar queue-existential-rules-tail nil)

(defmacro handling-queued-existential-rule-invocations (&body forms)
  `(let ((queue-existential-rules t)
	 (queue-existential-rules-tail nil))
     (multiple-value-prog1
	 (progn ,@forms)
       (let ((queue queue-existential-rules))
	 (unless (eq queue t)
	   (loop for tail = queue then next-tail
		 while tail
		 for (item sense fsn . last-cons) = tail
		 for (precomputed-links-and-objects . next-tail) = last-cons
		 do
             (safe-invoke-rules-for-existential-chaining
	       item sense fsn precomputed-links-and-objects)
	     (reclaim-frame-serial-number fsn)
		 finally
                   (reclaim-gensym-list-given-tail queue last-cons)))))))

(defun-void schedule-task-to-invoke-existential-rules (new-frame sense)
  (when (frame-of-class-p new-frame 'item) ; exclude dependant-frames
    (let ((*links-and-objects* nil))
      ;; NOTE: the commented code looks reasonable, but they're commented for long. --binghe
      #+SymScale
      (collect-rules-for-existential-chaining new-frame sense)
      (when #+SymScale *links-and-objects*
	    #-SymScale t
	(let ((fsn (frame-serial-number new-frame))
	      (qtail queue-existential-rules-tail))
	  ;; TODO: not thread-safe.
	  (cond (qtail
		 (let* ((new-tail (gensym-cons *links-and-objects* nil))
			(new-entry
			 (gensym-cons new-frame
				      (gensym-cons sense (gensym-cons
							   (copy-frame-serial-number fsn) new-tail)))))
		   (setf (cdr qtail) new-entry)
		   (setq queue-existential-rules-tail new-tail)))
		(queue-existential-rules
		 (let* ((new-tail (gensym-cons *links-and-objects* nil))
			(new-entry
			 (gensym-cons
			   new-frame
			   (gensym-cons sense (gensym-cons (copy-frame-serial-number fsn) new-tail)))))
		   (setq queue-existential-rules new-entry)
		   (setq queue-existential-rules-tail new-tail)))
		(scheduler-has-been-initialized-p
		 (with-immediate-scheduling (nil nil (nil nil 'reclaim-frame-serial-number))
		   ;; scheduler reclaims fsn
		   (safe-invoke-rules-for-existential-chaining new-frame
							       sense
							       (copy-frame-serial-number fsn)
							       *links-and-objects*)))))))))

;;; Recursive version of schedule-task-to-invoke-creation-rules.
;;; This function is deliberately the same in structure as
;;; `funcall-function-to-inferior-blocks' but is a different function
;;; for the following two reasons:
;;; 1.  The output connections for each block are used rather
;;;  than the input connections.  
;;; 2.  We do not want creation rules to fire on embedded rules.  

(defun-void recursive-schedule-task-to-invoke-creation-rules
    (new-frame)
  (schedule-task-to-invoke-existential-rules new-frame 'is-created)

  ;; Subblocks
  (loop for subblock being each subblocks of new-frame
	do
    (when (framep new-frame)
      (recursive-schedule-task-to-invoke-creation-rules
	subblock)))
  
  ;; User defined attributes containing frames
  (loop for slot-description in (slot-descriptions (class-description (class new-frame)))
	with slot-value
	do
    (when (user-defined-slot-description-p slot-description)
      (setq slot-value (get-slot-description-value-macro
			 new-frame slot-description))
      (when (framep slot-value)
	(recursive-schedule-task-to-invoke-creation-rules
	  slot-value))))

  ;; Output connection frames
  (loop for connection being the output-connections of new-frame
	for connection-frame-or-class =
	(if (connection-p connection)
	    (connection-frame-or-class connection))
	do
    (when (framep connection-frame-or-class)
      (recursive-schedule-task-to-invoke-creation-rules
	connection-frame-or-class)))

  ;; Subworkspace if entity and has one
  (when (frame-of-class-p new-frame 'entity)
    (loop for subworkspace in (subworkspaces new-frame)
	  do
      (recursive-schedule-task-to-invoke-creation-rules
	subworkspace)))

  ;; Variable case when there are simulation subtables
  (when (frame-of-class-p new-frame 'variable)
    (let ((simulation-subtable? (simulation-details new-frame)))
      (when (and simulation-subtable?
		 (of-class-p simulation-subtable? 'simulation-subtable))
	(recursive-schedule-task-to-invoke-creation-rules
	  simulation-subtable?)))))


(defun write-major-existential-chaining-trace-message
    (object chain-object recipient role? key-sense)
  (write-major-trace-message
    (if role?
	(tformat
	  "Scheduling event chaining to ~nf with ~nf as ~a because ~nf ~nf."
	  recipient
	  chain-object
	  role?
	  object
	  (indicate-appropriate-existential-event key-sense))
	(tformat
	  "Scheduling event chaining to ~NF because ~NF ~nf."
	  recipient
	  object
	  (indicate-appropriate-existential-event key-sense)))))

(defun indicate-appropriate-existential-event (key-sense)
  (case key-sense
    ((is-activated) "was activated")
    ((is-deactivated) "was deactivated")
    ((is-enabled) "was enabled")
    ((is-disabled) "was disabled")
    ((is-created) "was created")
    ((loses-its-value) "has lost its value")))

(defun collect-rules-for-existential-chaining (object key-sense)
  (let* ((object-names? (name-or-names-for-frame object))
	 (object-name-cons?
	   (if (and object-names?
		    (symbolp object-names?))
	       (setq object-names? (eval-cons object-names? nil))
	       nil))
	 (parent-stack (make-parent-stack object)))
    ;; Chain to any name of the object.
    (loop for object-name in object-names?
	  do
      (loop for link in (forward-chaining-list-macro object-name)
	    for stored-sense = (forward-link-sense link)
	    do
	(if (and (existential-sense-matches-p stored-sense key-sense)
		 (eq object-name (forward-link-designation link)))
	    (add-tuple-to-link-list link nil))))
    ;; Chain to the attribute name of any parent entity.
    (if parent-stack
	(let ((parent-stack-entry (car-of-cons parent-stack)))
	  (loop for link in (forward-chaining-list-macro
			      (parent-stack-attribute parent-stack-entry))
		for stored-sense = (forward-link-sense link)
		do
	    (if (existential-sense-matches-p stored-sense key-sense)
		(let ((parent-frame? (find-referenced-parent
				       parent-stack
				       (forward-link-designation link))))
		  (if parent-frame?
		      (add-tuple-to-link-list link parent-frame?)))))))
    ;; Chain to references to a class of this object.
    (loop for link in (forward-chaining-list-for-classes
			(class-inheritance-path
			  (class-description-slot object)))
	  for stored-sense = (forward-link-sense link)
	  for designation = (forward-link-designation link)
	  do
      (if (and (existential-sense-matches-p stored-sense key-sense)
	       (not (symbolp designation))
	       (not (and (domain-of-designation designation)
			 (symbolp (role-of-designation designation)))))
	  (add-tuple-to-link-list link object)))
    (if object-name-cons? (reclaim-eval-cons-macro object-name-cons?))
    (reclaim-parent-stack parent-stack)))


;;;; Resizement Chaining

;;; The macro `resizement-sense-matches-p' takes a resizer and a sense from a
;;; forward chaining link and returns whether or not the senses match.  Matching
;;; sense in this case means that the stored sense is "is-resized-by-the-user".


(def-substitution-macro resizement-sense-matches-p (resizer stored-sense)
  (eq stored-sense resizer))


;;; Whenever an icon is resized and the system is running, the function
;;; `invoke-rules-for-resizement-chaining' will be called with the icon which has
;;; just been resized and with a symbol naming the resizer of the icon, currently
;;; :resized-by-the-user.  This function
;;; will collect those whenever rules which should be invoked through event
;;; predicates which check for resizement, and it will then schedule them for
;;; invocation.

(defun invoke-rules-for-resizement-chaining (object resizer)
  (let ((current-computation-frame-previously-bound?
	 (framep *current-computation-frame*))
	(*links-and-objects* nil))
    (unless current-computation-frame-previously-bound?
      (setq *current-computation-frame* object))
    (collect-rules-for-resizement-chaining object resizer)
    ;; Schedule the collected rules for invocation.
    (loop for link-entry in *links-and-objects*
	  for link = (car link-entry)
	  for recipient = (forward-link-recipient link)
	  do
	  ;; The forward link recipient will be either an update list or a rule
	  ;; frame.  Do nothing if it is a true value update recipient or if the
	  ;; rule is inactive.
	  (when (and (not (true-value-update-recipient-p recipient))
		     (runnable-p recipient))
	    (let* ((role? (forward-link-focus link))
		   (local-name? (if role?
				    (forward-link-focus-local-name link)
				  nil))
		   (chain-object (if role?
				     (cdr link-entry)
				   nil)))
	      (when (really-invoke-rules? role? recipient chain-object)
                (write-major-resizement-chaining-trace-message
                  object chain-object recipient role? resizer)
                (generate-and-schedule-rule-instances
                  recipient role? local-name? chain-object 'forward-chaining nil
                  (rule-priority recipient) nil))))
	  (reclaim-eval-cons-macro link-entry))
    (unless current-computation-frame-previously-bound?
      (setq *current-computation-frame* nil))
    (reclaim-eval-list-macro *links-and-objects*)))

(defun write-major-resizement-chaining-trace-message
    (object chain-object recipient role? resizer)
  (declare (ignore resizer))
  (write-major-trace-message
    (if role?
	(tformat
	  "Scheduling event chaining to ~nf with ~nf as ~a because ~nf was resized by the user."
	  recipient
	  chain-object
	  role?
	  object)
	(tformat
	  "Scheduling event chaining to ~NF because ~NF was resized by the user."
	  recipient
	  object))))

(defun collect-rules-for-resizement-chaining (object resizer)
  (let* ((object-names? (name-or-names-for-frame object))
	 (object-name-cons?
	   (if (and object-names?
		    (symbolp object-names?))
	       (setq object-names? (eval-cons object-names? nil))
	       nil))
	 (parent-stack (make-parent-stack object)))
    ;; Chain to any name of the object.
    (loop for object-name in object-names?
	  do
      (loop for link in (forward-chaining-list-macro object-name)
	    for stored-sense = (forward-link-sense link)
	    do
	(if (and (resizement-sense-matches-p resizer stored-sense)
		 (eq object-name (forward-link-designation link)))
	    (add-tuple-to-link-list link nil))))
    ;; Chain to the attribute name of any parent entity.
    (if parent-stack
	(let ((parent-stack-entry (car-of-cons parent-stack)))
	  (loop for link in (forward-chaining-list-macro
			      (parent-stack-attribute parent-stack-entry))
		for stored-sense = (forward-link-sense link)
		do
	    (if (resizement-sense-matches-p resizer stored-sense)
		(let ((parent-frame? (find-referenced-parent
				       parent-stack
				       (forward-link-designation link))))
		  (if parent-frame?
		      (add-tuple-to-link-list link parent-frame?)))))))
    ;; Chain to references to a class of this object.
    (loop for link in (forward-chaining-list-for-classes
			(class-inheritance-path
			  (class-description-slot object)))
	  for stored-sense = (forward-link-sense link)
	  for designation = (forward-link-designation link)
	  do
      (if (and (resizement-sense-matches-p resizer stored-sense)
	       (not (symbolp designation))
	       (not (and (domain-of-designation designation)
			 (symbolp (role-of-designation designation)))))
	  (add-tuple-to-link-list link object)))
    (if object-name-cons? (reclaim-eval-cons-macro object-name-cons?))
    (reclaim-parent-stack parent-stack)))



;;;; Variable Failure Chaining




;;; The macro `failure-sense-matches-p' takes a sense from a forward chaining
;;; link and returns whether or not this matches sense for failure.  Matching
;;; sense in this case means that either the stored sense is
;;; "fails-to-receive-a-value".


(defmacro failure-sense-matches-p (stored-sense)
  `(eq ,stored-sense 'fails-to-receive-a-value))




;;; Whenever a variable fails, the function `invoke-rules-for-failure-chaining'
;;; will be called with the variable which has just failed.  This function will
;;; collect those whenever rules which should be invoked through event
;;; predicates which check for failure, and it will then schedule them for
;;; invocation.


(defun invoke-rules-for-failure-chaining (object)
  (let ((*links-and-objects* nil))
    (collect-rules-for-failure-chaining object)
    ;; Schedule the collected rules for invocation.
    (loop for link-entry in *links-and-objects*
	  for link = (car link-entry)
	  for recipient = (forward-link-recipient link)
	  do
          (if (and (not (true-value-update-recipient-p recipient))
                   (runnable-p recipient))
              (let* ((role? (forward-link-focus link))
                     (local-name? (if role?
                                      (forward-link-focus-local-name link)
                                    nil))
                     (chain-object (if role?
                                       (cdr link-entry)
                                     nil))
                     (*current-computation-frame* object))
                (write-major-failure-chaining-trace-message
                 object chain-object recipient role?)
                (generate-and-schedule-rule-instances
                 recipient role? local-name? chain-object 'forward-chaining nil
                 (rule-priority recipient) nil)))
          (reclaim-eval-cons-macro link-entry))
    (reclaim-eval-list-macro *links-and-objects*)))

(defun write-major-failure-chaining-trace-message
       (object chain-object recipient role?)
  (write-major-trace-message
    (if role?
	(tformat
	  "Scheduling event chaining to ~NF with ~NF as ~A because ~NF failed ~
         to receive a value."
	  recipient
	  chain-object
	  role?
	  object)
	(tformat
	  "Scheduling event chaining to ~NF because ~NF failed to receive a value."
	  recipient
	  object))))



(defun collect-rules-for-failure-chaining (object)
  (let* ((object-names? (name-or-names-for-frame object))
	 (object-name-cons?
	   (if (and object-names?
		    (symbolp object-names?))
	       (setq object-names? (eval-cons object-names? nil))
	       nil))
	 (parent-stack (make-parent-stack object)))
    ;; Chain to any name of the object.
    (loop for object-name in object-names?
	  do
      (loop for link in (forward-chaining-list-macro object-name)
	    for stored-sense = (forward-link-sense link)
	    do
	(if (and (failure-sense-matches-p stored-sense)
		 (eq object-name (forward-link-designation link)))
	    (add-tuple-to-link-list link nil))))
    ;; Chain to the attribute name of any parent entity.
    (if parent-stack
	(let* ((parent-stack-entry (car-of-cons parent-stack)))
	  (loop for link in (forward-chaining-list-macro
			      (parent-stack-attribute parent-stack-entry))
		for stored-sense = (forward-link-sense link)
		do
	    (if (failure-sense-matches-p stored-sense)
		(let ((parent-frame (find-referenced-parent
				      parent-stack
				      (forward-link-designation link))))
		  (if parent-frame
		      (add-tuple-to-link-list link parent-frame)))))))
    ;; Chain to references to a class of this object.
    (loop for link in (forward-chaining-list-for-classes
			(class-inheritance-path
			  (class-description-slot object)))
	  for stored-sense = (forward-link-sense link)
	  for designation = (forward-link-designation link)
	  do
      (if (and (failure-sense-matches-p stored-sense)
	       (not (symbolp designation))
	       (not (and (domain-of-designation designation)
			 (symbolp (role-of-designation designation)))))
	  (add-tuple-to-link-list link object)))
    (if object-name-cons? (reclaim-eval-cons-macro object-name-cons?))
    (reclaim-parent-stack parent-stack)))


;;;; True Value Update




;;; The true value update facility provides event based updating of facilities
;;; which depend upon the values of variables, parameters, and constant
;;; attributes.

;;; The function `install-true-value-update' sets up chaining mechanisms such
;;; that whenever a variable mentioned in an expression receives a new value, or
;;; the conclude that x has no current value action is called, or the value of the
;;; variable expires, an update function will be called on the variable and the
;;; arguments given here.  The arguments to this function are a symbol naming an
;;; update function, a frame to pass to the update function, an extra argument
;;; to pass to the update function, a designation to a variable which should be
;;; removed (deinstalled) from the system, and a designation which should be
;;; added (installed) to the update system.

;;; When a change to the value of any variable or parameter attribute matching
;;; the installed designation is made, then the update function will be called
;;; (from inside of put-current-value) with the following arguments: the frame
;;; given to this function, the extra argument given to this function, the
;;; changed frame, and an attribute of the changed frame which was changed, or
;;; else nil, and finally the old value that has been replaced.  A copy-tree is
;;; performed on the extra argument, and that is stored by this facility.

;;; If the last argument to the update function is NIL (the typical case), then
;;; the changed frame is a variable which has either received a new value, or
;;; had its old value expire.  If the last argument to the update function is
;;; non-null, then it is the name of the attribute of the changed frame which
;;; was changed.  This will occur in the case where a constant attribute of a
;;; frame has been edited by the user.

;;; Note that this update facility can only be used with invertible
;;; designations, as certified by invertible-designation-p.  Anything
;;; referencing designations which are not invertible must use some other
;;; mechanism, such as polling, to keep their values up to date.

(defun install-true-value-update
       (update-function frame? extra-argument old-expression? new-expression?)
  (decache-class-chaining-lists)
  (let ((current-block-of-dependent-frame 'dependent-frame-has-no-owner))
    (if old-expression?
	(let ((names-and-info-for-chaining nil)
	      (update-function-spec
		(make-true-value-update-recipient
		  update-function frame? extra-argument)))
	  (note-names-and-info-for-true-value-chaining-in-expression
	    old-expression?
	    update-function-spec)
	  (reclaim-true-value-update-recipient update-function-spec)
	  (loop for old-name-and-info in names-and-info-for-chaining
		for old-name = (car old-name-and-info)
		for old-link = (cdr old-name-and-info)
		do
	    (loop for chaining-link in (forward-chaining-list old-name)
		  do
	      (when (equal-forward-chaining-link old-link chaining-link)
		(setf (forward-chaining-list old-name)
		      (delete-eval-element
			chaining-link (forward-chaining-list old-name)))
		(reclaim-forward-chaining-link chaining-link)))
	    (reclaim-forward-chaining-link old-link)
	    (reclaim-slot-value-cons old-name-and-info))
	  (reclaim-slot-value-list names-and-info-for-chaining)))
    (if new-expression?
	(let ((names-and-info-for-chaining nil)
	      (update-function-spec
		(make-true-value-update-recipient
		  update-function frame? extra-argument)))
	  (note-names-and-info-for-true-value-chaining-in-expression
	    new-expression?
	    update-function-spec)
	  (reclaim-true-value-update-recipient update-function-spec)
	  (loop for new-name-and-info in names-and-info-for-chaining
		for new-name = (car new-name-and-info)
		for new-link = (cdr new-name-and-info)
		do
	    (setf (forward-chaining-list new-name)	; order irrelevant
		  (eval-cons new-link (forward-chaining-list new-name)))
	    (reclaim-slot-value-cons new-name-and-info))
	  (reclaim-slot-value-list names-and-info-for-chaining)))))




;;; The function `generate-cell-chaining-links' is used to collect a slot value
;;; cons list of the forward chaining links called for within the given
;;; expression.

(defun generate-cell-chaining-links
       (update-function frame? extra-argument expression)
  (let ((names-and-info-for-chaining nil)
	(update-function-spec
	  (make-true-value-update-recipient
	    update-function frame? extra-argument)))
    (note-names-and-info-for-cell-chaining-in-expression
      expression update-function-spec)
    (reclaim-true-value-update-recipient update-function-spec)
    names-and-info-for-chaining))




;;; The function `redirect-chaining-link-recipient' takes a forward chaining
;;; link and a block.  If the recipient of this forward chaining link is a
;;; true-value-update-recipient, then this function will change the held frame
;;; of the true-value-update-recipient to point to the given frame.  This
;;; function is called indirectly by the slot putter for the cell-array slot.
;;; This is used to rebuild backpointers to parent frames, and to actually
;;; redirect forward chaining links when the holder of a cell-array is cloned.

(defun redirect-chaining-link-recipient (forward-chaining-link frame)
  (let ((recipient (forward-link-recipient forward-chaining-link)))
    (when (and recipient
	       (true-value-update-recipient-p recipient))
      (setf (true-value-update-frame recipient) frame))))


(defun invoke-update-functions-for-put-has-no-current-value (variable old-value)
  (let ((*links-and-objects* nil))
    (cancel-task (task-for-expiration? variable))
    (collect-links-for-put-has-no-current-value variable)
    ;; Schedule the collected rules for invocation.
    (loop for link-entry in *links-and-objects*
	  for link = (car-of-cons link-entry)
	  for recipient = (forward-link-recipient link)
	  do
          (when (true-value-update-frame recipient)
            (tformat-major-trace-message
             "Notifying ~NF that ~NF has been forced to have no current value."
             (true-value-update-frame recipient)
             variable))
          (invoke-true-value-update
           recipient variable nil old-value nil)
          (reclaim-eval-cons-macro link-entry))
    (reclaim-eval-list-macro *links-and-objects*))

  (invoke-rules-for-existential-chaining variable 'loses-its-value nil))

(defun invoke-update-functions-for-expired-value (variable old-value)
  (let ((*links-and-objects* nil))
    (cancel-task (task-for-expiration? variable))
    (collect-links-for-put-has-no-current-value variable)
    ;; Schedule the collected rules for invocation.
    (loop for link-entry in *links-and-objects*
	  for link = (car-of-cons link-entry)
	  for recipient = (forward-link-recipient link)
	  do
          (when (true-value-update-frame recipient)
            (tformat-major-trace-message
             "Notifying ~NF that the value of ~NF has expired."
             (true-value-update-frame recipient)
             variable))
          (invoke-true-value-update
           recipient variable nil old-value nil)
          (reclaim-eval-cons-macro link-entry))
    (reclaim-eval-list-macro *links-and-objects*))

  (invoke-rules-for-existential-chaining variable 'loses-its-value nil))

(defmacro put-has-no-current-value-sense-matches-p (stored-sense)
  `(eq ,stored-sense 'receives-a-value))

(defun-void collect-links-for-put-has-no-current-value (object)
  (let* ((object-names? (name-or-names-for-frame object))
	 (object-name-cons?
	   (if (and object-names?
		    (symbolp object-names?))
	       (setq object-names? (eval-cons object-names? nil))
	       nil))
	 (parent-attribute? (cond
			      ((consp (parent-attribute-name object))
			       (let ((parent-attribute-slot-description
				      (get-slot-description-of-frame
					(car-of-cons (parent-attribute-name object))
					(parent-frame object)
					(cdr-of-cons (parent-attribute-name object)))))
				 (unique-slot-name parent-attribute-slot-description)))
			      (t 
			       (parent-attribute-name object)))))
    ;; Chain to any name of the object.
    (loop for object-name in object-names?
	  do
      (loop for link in (forward-chaining-list-macro object-name)
	    do
	(if (and (true-value-update-recipient-p link)
		 (put-has-no-current-value-sense-matches-p
		   (forward-link-sense link))
		 (eq object-name (forward-link-designation link)))
	    (add-tuple-to-link-list link nil))))
    ;; Chain to the attribute name of any parent entity.
    (if parent-attribute?
	(loop for link in (forward-chaining-list-macro parent-attribute?)
	      do
	  (if (and (true-value-update-recipient-p link)
		   (put-has-no-current-value-sense-matches-p
		     (forward-link-sense link))
		   (designation-denotes-item-p
		     (forward-link-designation link)
		     object))
	      (add-tuple-to-link-list link nil))))
    ;; Chain to references to a class of this object.
    (loop for link in (forward-chaining-list-for-classes
			(class-inheritance-path
			  (class-description-slot object)))
	  do
      (if (and (true-value-update-recipient-p link)
	       (put-has-no-current-value-sense-matches-p
		 (forward-link-sense link))
	       (designation-denotes-item-p
		 (forward-link-designation link)
		 object))
	  (add-tuple-to-link-list link nil)))
    (if object-name-cons? (reclaim-eval-cons-macro object-name-cons?))))

;;; The function `invoke-rules-for-attribute-change-chaining' takes a parent frame
;;; and an attribute name.  It will invoke rules ala forward chaining which
;;; mention this attribute of a class of the parent frame.  This function will
;;; only be called when a user edits a constant attribute of a frame, or when a
;;; conclude on a constant attribute occurs.

(defun-void invoke-rules-for-attribute-change-chaining
    (parent-frame attribute-name old-value class-if-specific?)
  (let ((*links-and-objects* nil))
    (collect-links-for-attribute-change-chaining parent-frame attribute-name)
    ;; Schedule the collected rules for invocation.
    (when *links-and-objects*
      (loop for trailer = nil then link-entry-cons
	    for link-entry-cons on *links-and-objects*
	    for link-entry = (car-of-cons link-entry-cons)
	    for link = (car-of-cons link-entry)
	    for recipient = (forward-link-recipient link)
	    do
            (if (true-value-update-recipient-p recipient)
                (when (designation-denotes-item-p
                       (domain-of-designation (forward-link-designation link))
                       parent-frame)
                  ;; Run the update function.
                  (when (true-value-update-frame recipient)
                    (tformat-major-trace-message
                     "Executing update for ~NF because a new value was placed ~
                 in the ~a of ~NF."
                     (true-value-update-frame recipient)
                     attribute-name
                     parent-frame))
                  (invoke-true-value-update
                   recipient parent-frame attribute-name old-value class-if-specific?))
              ;; Schedule the rule.
	      (when (and (runnable-p recipient)
			 ;; GENSYMCID-1681: G2 abort when loading kb
			 ;; prevent scheduling rules during KB loading stage.
			 (not reading-kb-p))
                (let* ((role? (forward-link-focus link))
                       (local-name? (if role?
                                        (forward-link-focus-local-name link)
				      nil))
                       (object? (if role?
                                    (cdr link-entry)
				  nil)))
                  #+development
                  (if (and role? (not object?))
                      (error "Error in forward chaining!  A link with the ~
                          stored focal role ~a was chained to with no ~
                            focal object.  Please inform Gensym software ~
                            support."
                             role?))
                  (when (major-trace-message-will-be-written-p)
                    (write-major-attribute-chaining-message
                     recipient parent-frame attribute-name local-name?
                     role? object?))
                  (generate-and-schedule-rule-instances
                   recipient role? local-name? object? 'forward-chaining nil
                   (rule-priority recipient) nil))))
            (reclaim-eval-cons-macro link-entry)
	    finally
            (reclaim-eval-list-given-tail *links-and-objects* trailer)))))

(defun write-major-attribute-chaining-message
       (recipient parent-frame attribute-name local-name? role? object?)
  (write-major-trace-message 
    (if role?
	(if local-name?
	    (tformat
	      "Scheduling forward chaining to ~NF with ~NF as ~
             the ~A with local name ~A because a new value ~
             was placed in the ~A of ~NF."
	      recipient
	      object?
	      role?
	      local-name?
	      attribute-name
	      parent-frame)
	    (tformat
	      "Scheduling forward chaining to ~NF with ~NF as the ~A ~
             because a new value was placed in the ~A of ~NF."
	      recipient
	      object?
	      role?
	      attribute-name
	      parent-frame))
	(tformat
	  "Scheduling forward chaining to ~NF because a new value was ~
         placed in the ~A of ~NF."
	  recipient
	  attribute-name
	  parent-frame))))





;;; The macro `chain-forward-for-attribute-if-necessary' does a quick check for
;;; any work to be done by invoke-rules-for-attribute-change-chaining.  If there
;;; is, it call invoke-rules-for-attribute-change-chaining on block, and binds
;;; *current-computation-frame* to block around the call if it's currently nil.

;;; This is a slightly optimized interface to
;;; invoke-rules-for-attribute-change-chaining on average.  It's faster for the
;;; more common case of there not being any chaining work to do, and it's
;;; marginally slower for the less common case of there being chaining work to
;;; do.

(defun-substitution-macro fast-registered-event-detectors (block)
  (look-up-slot-value-else-compute-default
    block 'registered-event-detectors 'nil))

(defun-void chain-forward-for-attribute-if-necessary
  (frame attribute-name defining-class?)
  (when (or (fast-registered-event-detectors frame)
	    (forward-chaining-list-macro attribute-name))
    (cond
     (*current-computation-frame*
      (invoke-rules-for-attribute-change-chaining
       frame attribute-name nil defining-class?))
     (t (let ((*current-computation-frame* frame)) 
	  (invoke-rules-for-attribute-change-chaining
	   frame attribute-name nil defining-class?))))))

;; At present the users of this are just in VIEW-DEF.  (MHD 5/12/00)





(defun-void collect-links-for-attribute-change-chaining
    (parent-frame attribute-name)
  ;; Trigger any event detectors waiting for this attribute to change.
  (loop with triggerable-event-detectors =
    (let ((event-detectors (registered-event-detectors parent-frame)))
      (when event-detectors
	(loop for event-detector in event-detectors
	      when (and (eq (event-detector-type event-detector)
			    'receives-a-value)
			(eq (event-detector-extra-information event-detector)
			    attribute-name))
		collect event-detector using eval-cons)))
	while triggerable-event-detectors
	for event-detector = (eval-pop triggerable-event-detectors)
	do (trigger-event-detector event-detector))
  ;; Chain to the attribute name of any parent entity.
  (loop with parent-names? = nil
	with parent-name-cons? = nil
	with parent-stack = nil
	for link in (forward-chaining-list-macro attribute-name)
	for stored-sense = (forward-link-sense link)
	do
    (when (general-sense-matches-p stored-sense t)
      ;; Make the parent stack if we haven't already done so.  Most times
      ;; through this function, there will be no forward chaining and so most
      ;; times we will never have to make the parent stack at all.
      (unless parent-stack
	(setq parent-names? (name-or-names-for-frame parent-frame))
	(setq parent-name-cons?
	      (if (and parent-names?
		       (symbolp parent-names?))
		  (eval-cons parent-names? nil)
		  nil))
	(setq parent-stack
	      (eval-cons
		(eval-list-macro parent-frame attribute-name
				 (or parent-name-cons? parent-names?)
				 parent-name-cons?)
		(make-parent-stack parent-frame))))
      (let ((frame-to-chain? (find-referenced-parent
			       parent-stack
			       (forward-link-designation link))))
	(when frame-to-chain?
	  (add-tuple-to-link-list link frame-to-chain?))))
	finally
	  (when parent-stack
	    (reclaim-parent-stack parent-stack))))



;;;; Relation Chaining




;;; When a new relation is established between two items, forward chaining is
;;; invoked to propagate logical values which may depend upon the relation.

;;; Forward chaining links for relations can possibly contain two focal roles.
;;; The first focal role is for the subject of the relation, and the second is
;;; for the object.  Note that either or both of these focal roles may be NIL,
;;; in which case the designation for that reference ended in a name and so does
;;; not need to be focused upon.

;;; The forward-chaining-symbolic-sense slot of the forward chaining link holds
;;; the symbol which names the relation which can be chained to.

;;; When chaining for relations is invoked, the forward chaining list search
;;; should proceed based on the subject of the relation, but when a link is
;;; found then the object of the relation needs to be verified that it could be
;;; denoted by the second designation of the forward chaining link.




;;; The function `invoke-rules-for-relation-chaining' takes a relation name, a
;;; subject of the relation (the value of the designation role), an object of
;;; the relation, (the domain of a relation designation), and whether the
;;; relation is being added or removed.  This function will then invoke all
;;; rules which reference this relation in either a for iteration specifier or
;;; in the antecedent, or any references to the is-related predicates.

;;; Note that there are four possible calls from this function to generate-and-
;;; schedule-rule-invocations.

;;; The first contains a focus, and a constraint alist.  This happens in the
;;; case where both the subject and object of the relation have designations in
;;; the rule which require a focal object.  Note that the item in the relation
;;; may not necessarily be the item which is passed as the focus of the second
;;; designation, but instead a search needs to be made for the first item which
;;; is not found through an attribute reference.  This is the item passed as the
;;; focus.

;;; The second two cases cover the situations in which only one of the two
;;; designations of the role require focus.  This function needs to determine
;;; which of them gets a focus, and if it is the second it must search for the
;;; correct item to send as the focus.

;;; The last case is where both designations in the relation are rooted in
;;; names, in which case the rule will be invoked for its universal compilation.

(defun invoke-rules-for-relation-chaining
       (relation subject object adding-relation?)
  (let ((current-computation-frame-previously-bound?
         (framep *current-computation-frame*))
	(object-parent-stack (make-parent-stack object))
	(*links-and-objects* nil))
    (unless current-computation-frame-previously-bound?
      (setq *current-computation-frame* subject))
    (collect-rules-for-relation-chaining relation subject adding-relation?)
    ;; Schedule the collected rules for invocation.
    (loop with role?
	  with local-name?
	  with chain-object
	  with second-designation
	  with second-role?
	  with second-local-name?
	  with second-chain-object?
	  for link-entry in *links-and-objects*
	  for link = (car link-entry)
	  for recipient = (forward-link-recipient link)
	  do
          ;; The forward link recipient will always be a rule, but cover the
          ;; true-value-update-recipient case just in case.  Also make sure that the
          ;; rule is active.
          (when (and (not (true-value-update-recipient-p recipient))
                     (runnable-p recipient))
            (setq role? (forward-link-focus link)
                  local-name? (if role? (forward-link-focus-local-name link) nil)
                  chain-object (if role? (cdr link-entry) nil)
                  second-designation (forward-link-second-designation link)
                  second-role? (forward-link-second-focus link)
                  second-local-name? (if second-role?
                                         (forward-link-second-focus-local-name
                                          link)
                                       nil)
                  second-chain-object?
                  (if second-role?
                      (if (and (symbolp second-role?)	; attribute designation
                               (domain-of-designation second-designation))
                          (find-referenced-parent
                           object-parent-stack
                           second-designation)
                        (if (designation-could-denote-item-p
                             second-designation object)
                            object
			  nil))
                    nil))

            ;; If there is a second role, only invoke rules if there is an object
            ;; for that role.  If there is no second role, but there is a
            ;; second-designation, only invoke rules if the designation could denote
            ;; the object.
            (unless (if second-role?
                        (not second-chain-object?)
                      (and second-designation
                           (not (designation-could-denote-item-p
                                 second-designation object))))
              (when (major-trace-message-will-be-written-p)
                (write-major-relation-chaining-trace-message
                 relation role? second-role? recipient chain-object
                 second-chain-object? local-name? second-local-name?
                 adding-relation? subject object))
              (cond
               ((and role? second-role?)
                (let ((constraint-alist (eval-list
                                         (eval-cons
                                          (or second-local-name? second-role?)
                                          second-chain-object?))))
                  (generate-and-schedule-rule-instances
                   recipient role? local-name? chain-object
                   'forward-chaining nil
                   (rule-priority recipient)
                   constraint-alist)
                  (reclaim-eval-cons-macro (car constraint-alist))
                  (reclaim-eval-cons-macro constraint-alist)))
               (role?
                (generate-and-schedule-rule-instances
                 recipient role? local-name? chain-object
                 'forward-chaining nil
                 (rule-priority recipient)
                 nil))
               (second-role?
                (generate-and-schedule-rule-instances
                 recipient second-role? second-local-name? second-chain-object?
                 'forward-chaining nil
                 (rule-priority recipient)
                 nil))
               (t
                (generate-and-schedule-rule-instances
                 recipient nil nil nil
                 'forward-chaining nil
                 (rule-priority recipient)
                 nil)))))
          (reclaim-eval-cons-macro link-entry))
    (unless current-computation-frame-previously-bound?
      (setq *current-computation-frame* nil))
    (reclaim-eval-list-macro *links-and-objects*)
    (reclaim-parent-stack object-parent-stack)))


(defun write-major-relation-chaining-trace-message
       (relation role? second-role? recipient chain-object second-chain-object?
	local-name? second-local-name? adding-relation? subject object)
  (write-major-trace-message
    (cond
      ((and role? second-role?)
       (tformat
	 "Scheduling chaining to ~NF with ~NF as ~A and ~NF as ~A ~
          because a ~A relation was ~a for these items."
	 recipient
	 chain-object
	 (or local-name? role?)
	 second-chain-object?
	 (or second-local-name? role?)
	 relation
	 (if adding-relation? "established" "removed")))
      (role?
       (tformat
	 "Scheduling chaining to ~NF with ~NF as ~A ~
          because a ~A relation was ~A for ~NF and ~NF."
	 recipient
	 chain-object
	 (or local-name? role?)
	 relation
	 (if adding-relation? "established" "removed")
	 subject
	 object))
      (second-role?
       (tformat
	 "Scheduling chaining to ~NF with ~NF as ~A ~
          because a ~A relation was ~A for ~NF and ~NF."
	 recipient
	 second-chain-object?
	 (or second-local-name? second-role?)
	 relation
	 (if adding-relation? "established" "removed")
	 subject
	 object))
      (t
       (tformat
	 "Scheduling chaining to ~NF ~
          because a ~A relation was ~A for ~NF and ~NF."
	 recipient
	 relation
	 (if adding-relation? "established" "removed")
	 subject
	 object)))))




;;; The macro `relation-sense-matches-p' takes a mover and a sense from a
;;; forward chaining link and returns whether or not the senses match.  Matching
;;; sense in this case means that either the stored sense is :related-change, or
;;; that we are adding a relation and the stored sense is :related, or that we
;;; are removing a relation and the stored sense is :not-related.  In all cases
;;; the stored symbolic value (which contains the name of the relation in the
;;; source) must be eq to the relation for which chaining is being invoked.

(defmacro relation-sense-matches-p
	  (relation sense-symbolic-value? stored-sense adding-relation?)
  (let* ((sense (if (or (constantp stored-sense) (symbolp stored-sense))
		    stored-sense
		    (gensym))))
    (if (eq sense stored-sense)
	`(and (or (eq nil ,sense-symbolic-value?)   ; generic case of any relation
		  (eq ,relation ,sense-symbolic-value?))
	      (or (eq ,sense :related-change)
		  (if ,adding-relation?
		      (eq ,sense :related)
		      (eq ,sense :not-related))))
	`(if (or
	       (eq nil ,sense-symbolic-value?)   ; generic case of any relation
	       (eq ,relation ,sense-symbolic-value?))
	     (let ((,sense ,stored-sense))
	       (or (eq ,sense :related-change)
		   (if ,adding-relation?
		       (eq ,sense :related)
		       (eq ,sense :not-related))))
	     nil))))




;;; The function `collect-rules-for-relation-chaining' iterates across the
;;; forward chaining lists for the subject of a newly added or deleted relation.

(defun collect-rules-for-relation-chaining
       (relation subject adding-relation?)
  (let* ((subject-names? (name-or-names-for-frame subject))
	 (subject-name-cons?
	   (if (and subject-names?
		    (symbolp subject-names?))
	       (setq subject-names? (eval-cons subject-names? nil))
	       nil))
	 (parent-stack (make-parent-stack subject)))
    ;; Chain to any name of the object.
    (loop for subject-name in subject-names?
	  do
      (loop for link in (forward-chaining-list subject-name)
	    do
	(if (and (relation-sense-matches-p
		   relation (forward-link-symbolic-value link)
		   (forward-link-sense link) adding-relation?)
		 (eq subject-name (forward-link-designation link)))
	    (add-tuple-to-link-list link nil))))
    ;; Chain to the attribute name of any parent entity.
    (when parent-stack
      (let ((parent-stack-entry (car-of-cons parent-stack)))
	(loop for link in (forward-chaining-list
			    (parent-stack-attribute parent-stack-entry))
	      do
	  (if (relation-sense-matches-p
		relation (forward-link-symbolic-value link)
		(forward-link-sense link) adding-relation?)
	      (let ((parent-frame? (find-referenced-parent
				     parent-stack
				     (forward-link-designation link))))
		(if parent-frame?
		    (add-tuple-to-link-list link parent-frame?)))))))
    ;; Chain to references to a class of this object.
    (loop for link in (forward-chaining-list-for-classes
			(class-inheritance-path
			  (class-description-slot subject)))
	  for designation = (forward-link-designation link)
	  do
      (if (and (relation-sense-matches-p
		 relation (forward-link-symbolic-value link)
		 (forward-link-sense link) adding-relation?)
	       (not (symbolp designation))
	       (not (and (domain-of-designation designation)
			 (symbolp (role-of-designation designation)))))
	  (add-tuple-to-link-list link subject)))
    (if subject-name-cons? (reclaim-eval-cons-macro subject-name-cons?))
    (reclaim-parent-stack parent-stack)))

;;;; Connection Chaining

;;; When a connection is made or broken, forward chaining is invoked to
;;; propagate logical values which may depend upon the connection.  There are a
;;; number of cases.

;;; Directly Connected Cases

;;; In the directly connected cases (see grammar, evaluator for
;;; generic-directly-connected-to and other directly connected cases), a
;;; connection has been either joined to another connection, or has been added
;;; as a new connection of a block (see finish-connection-dragging).  This case
;;; is handled by the function `invoke-rules-for-direct-connection-chaining'
;;; which takes a connection and a boolean indicating whether the connection is
;;; being made or broken.  This function will check the blocks at both ends of
;;; the connection and call invoke-rules-for-chaining if the block is not
;;; transparent.

;;; As with relations, forward chaining links for connections can possibly
;;; contain two focal roles.  For the directly connected cases, the first focal
;;; role is for the connection, and the second is for the object (block).  Note
;;; that either or both of these focal roles may be NIL, in which case the
;;; designation for that reference ended in a name and so does not need to be
;;; focused upon.

;;; The forward-chaining-symbolic-sense slot of the forward chaining link holds
;;; nothing for the generic directly connected case.

;;; When chaining for connections is invoked, the forward chaining list search
;;; should proceed based on the connection, but when a link is found then the
;;; object (block) needs to be verified that it could be denoted by the second
;;; designation of the forward chaining link.

;; This functionality is somewhat similar to that for relation chaining.
;; Consider whether it would be possible to combine the two.



;;; The function `invoke-rules-for-connection-chaining' takes a connection, a
;;; block, and a boolean indicating whether the connection is being made or
;;; broken.  This function will then invoke all rules which reference the
;;; connection in either a for iteration specifier or in the antecedent.

;;; Note that (as is the case with relations) there are four possible calls from
;;; this function to generate-and- schedule-rule-invocations.

;;; The first contains a focus, and a constraint alist.  This happens in the
;;; case where both the connection and the object (block) have designations in
;;; the rule which require a focal object.  

;;; The second two cases cover the situations in which only one of the two
;;; designations require focus.  This function needs to determine which of them
;;; gets a focus, and if it is the second it must search for the correct item to
;;; send as the focus.

;;; The last case is where both designations in the relation are rooted in
;;; names, in which case the rule will be invoked for its universal compilation.

;;; Note one important difference between relation chaining and connection
;;; chaining.  In relation chaining, the object (corresponding to the second
;;; focal role) can be any object including one that is embedded in an attribute
;;; of another object.  In connection chaining, the object corresponding to the
;;; second focal role is always a block and is therefore never embedded in an
;;; attribute.  Thus, an object-parent-stack is never utilized in connection
;;; chaining.

;;; Indirectly Connected Cases

;;; In the indirectly connected cases (see grammar, evaluator for
;;; indirectly-connected-to and other directly connected cases), some connection
;;; has been made between a set of one or more input blocks, and a set of one or
;;; more output blocks.  The connection may have been established by joining two
;;; connections, by adding a connection to a block, or by dragging one
;;; connection into another to form a junction (see finish-connection-dragging).
;;; This case is handled by the function
;;; `invoke-rules-for-indirect-connection-chaining' which takes a connection and
;;; a boolean indicating whether the connection is being made or broken.  This
;;; function iterates over and collects all blocks connected at the input end of
;;; the connection.  Note that the search for this block does not stop at
;;; transparent blocks like junctions or connection posts.  Thus, the set of
;;; input blocks may be large.  Similarly, the function iterates over all blocks
;;; at the output end of the connection, forming a set of output blocks.
;;; the function then forms the cross product of these sets, calling
;;; `invoke-rules-for-indirect-connection-chaining-for-pair' for each
;;; input-output pair.

;;; Note that there can sometimes be a large number of input-output pairs. If
;;; there are m objects in the input set, and n objects in the output set, then
;;; there will be m * n pairs.  However, this is not nearly as bad as taking all
;;; the input end objects and all the output end objects together as one set and
;;; finding every combination of pairs (this would result in (m + n)^2 pairs.
;;; It is perfectly valid to split the affected objects into two sets like this.
;;; The event mechanism is concerned with change.  The connectivity of the
;;; objects in the input set with respect to each other does not change in this
;;; context.  The same is the case for the output set.  The only change is that
;;; the set of input end objects is now connected to the set of output end
;;; objects.

;;; As with relations and as with the directly connected cases, forward chaining
;;; links for the indirectly connected cases can contain two focal roles.  The
;;; first focal role is for an input end object, the second is for an output end
;;; object.  Note that either or both of these focal roles may be NIL, in which
;;; case the designation for that reference ended in a name and so does not need
;;; to be focused upon.

;;; The forward-chaining-symbolic-sense slot of the forward chaining link holds
;;; nothing for the indirectly connected to case.

;;; As in the other two focal role cases, the forward chaining list search
;;; proceeds based on the first focal role (the input end object).  When a link
;;; is found, the output end block needs to be verified that it could be denoted
;;; by the second designation of the forward chaining link.

(defun invoke-rules-for-direct-connection-chaining (connection disconnecting?)
  (when (and (not (loose-end-p (input-end-object connection)))
	     (not (loose-end-p (output-end-object connection))))
    ;; This filter has been added to inhibit response to this event when the connection is a stub.
    ;; This was deemed to be the appropriate behavior, by popular consent.
    
    (when (and (not (loose-end-p (input-end-object connection)))
	       (not (class-transparent-p (class (input-end-object connection)))))
      (invoke-rules-for-connection-chaining
        ;; (get-or-make-connection-frame-and-activate-if-appropriate connection)
	connection
	(input-end-object connection)
	disconnecting?))
    (when (and (not (loose-end-p (output-end-object connection)))
	       (not (class-transparent-p (class (output-end-object connection)))))
      (invoke-rules-for-connection-chaining
        ;; (get-or-make-connection-frame-and-activate-if-appropriate connection)
	connection
	(output-end-object connection)
	disconnecting?))))

(defun invoke-rules-for-connection-chaining
       (connection block disconnecting?)
  (let ((current-computation-frame-previously-bound?
         (framep *current-computation-frame*))
	(*links-and-objects* nil))
    (unless current-computation-frame-previously-bound?
      (setq *current-computation-frame* block))
    (collect-rules-for-connection-chaining connection block disconnecting?)
    ;; Schedule the collected rules for invocation.
    (loop with role?
	  with local-name?
	  with chain-object
	  with second-designation
	  with second-role?
	  with second-local-name?
	  with second-chain-object?
	  for link-entry in *links-and-objects*
	  for link = (car link-entry)
	  for recipient = (forward-link-recipient link)
	  do
          ;; The forward link recipient will always be a rule, but cover the
          ;; true-value-update-recipient case just in case.  Also make sure that the
          ;; rule is active.
          (when (and (not (true-value-update-recipient-p recipient))
                     (runnable-p recipient))
            (setq role? (forward-link-focus link)
                  local-name? (if role? (forward-link-focus-local-name link) nil)
                  chain-object (if role? (cdr link-entry) nil)
                  second-designation (forward-link-second-designation link)
                  second-role? (forward-link-second-focus link)
                  second-local-name? (if second-role?
                                         (forward-link-second-focus-local-name
                                          link)
                                       nil)
                  second-chain-object?
                  (if second-role?
                      (if (designation-could-denote-item-p
                           second-designation block)
                          block
                        nil)
                    nil))
            (unless (and second-role? (not second-chain-object?))
              (when (major-trace-message-will-be-written-p)
                (write-major-connection-chaining-trace-message
                 role? second-role? recipient chain-object
                 second-chain-object? local-name? second-local-name?
                 disconnecting? connection block))
              (cond
               ((and role? second-role?)
                (let ((constraint-alist (eval-list
                                         (eval-cons
                                          (or second-local-name? second-role?)
                                          second-chain-object?))))
                  (generate-and-schedule-rule-instances
                   recipient role? local-name? chain-object
                   'forward-chaining nil
                   (rule-priority recipient)
                   constraint-alist)
                  (reclaim-eval-cons-macro (car constraint-alist))
                  (reclaim-eval-cons-macro constraint-alist)))
               (role?
                (generate-and-schedule-rule-instances
                 recipient role? local-name? chain-object
                 'forward-chaining nil
                 (rule-priority recipient)
                 nil))
               (second-role?
                (generate-and-schedule-rule-instances
                 recipient second-role? second-local-name? second-chain-object?
                 'forward-chaining nil
                 (rule-priority recipient)
                 nil))
               (t
                (generate-and-schedule-rule-instances
                 recipient nil nil nil
                 'forward-chaining nil
                 (rule-priority recipient)
                 nil)))))
          (reclaim-eval-cons-macro link-entry))
    (unless current-computation-frame-previously-bound?
      (setq *current-computation-frame* nil))
    (reclaim-eval-list-macro *links-and-objects*)))



(defun write-major-connection-chaining-trace-message
       (role? second-role? recipient chain-object second-chain-object?
	local-name? second-local-name? disconnecting? connection-structure block)
  (write-major-trace-message
    (cond
      ((and role? second-role?)
       (tformat
	 "Scheduling chaining to ~NF with ~NF as ~A and ~NF as ~A ~
          because a connection was ~a for these items."
	 recipient
	 chain-object
	 (or local-name? role?)
	 second-chain-object?
	 (or second-local-name? role?)
	 (if disconnecting? "broken" "made")))
      (role?
       (tformat
	 "Scheduling chaining to ~NF with ~NF as ~A ~
          because a connection of class ~A connected to ~NF was ~A."
	 recipient
	 chain-object
	 (or local-name? role?)
	 (get-connection-class-given-connection connection-structure)
	 block
	 (if disconnecting? "broken" "made")))
      (second-role?
       (tformat
	 "Scheduling chaining to ~NF with ~NF as ~A ~
          because a connection of class ~A connected to ~NF was ~A."
	 recipient
	 second-chain-object?
	 (or second-local-name? second-role?)
	 (get-connection-class-given-connection connection-structure)
	 block
	 (if disconnecting? "broken" "made")))
      (t
       (tformat
	 "Scheduling chaining to ~NF ~
          because a connection of class ~A connected to ~NF was ~A."
	 recipient
	 (get-connection-class-given-connection connection-structure)
	 block
	 (if disconnecting? "broken" "made"))))))




;;; The macro `connection-sense-matches-p' takes a mover and a sense from a
;;; forward chaining link and returns whether or not the senses match.  Matching
;;; sense in this case means that either we are making a connection and the
;;; stored sense is :connected, or that we are breaking a connection and the
;;; stored sense is :disconnected.  

(defmacro connection-sense-matches-p
	  (stored-sense disconnecting?)
  (let* ((sense (if (or (constantp stored-sense) (symbolp stored-sense))
		    stored-sense
		    (gensym))))
    (if (eq sense stored-sense)
	`(if ,disconnecting?
	     (eq ,sense :disconnected)
	     (eq ,sense :connected))
	`(let ((,sense ,stored-sense))
	   (if ,disconnecting?
	       (eq ,sense :disconnected)
	       (eq ,sense :connected))))))



;;; The function `collect-rules-for-connection-chaining' iterates across the
;;; forward chaining lists of a newly added or deleted connection.
;;; Since the connection will never be embedded in an attribute of another object,
;;; a parent stack is not utilized.

(defun collect-rules-for-connection-chaining
       (connection-structure block disconnecting?)
  (let* ((connection (get-or-make-connection-frame-and-activate-if-appropriate
		       connection-structure))
	 (subject-names? (name-or-names-for-frame connection))
	 (subject-name-cons?
	   (if (and subject-names?
		    (symbolp subject-names?))
	       (setq subject-names? (eval-cons subject-names? nil))
	       nil)))
    ;; Chain to any name of the object.
    (loop for subject-name in subject-names?
	  do
      (loop for link in (forward-chaining-list-macro subject-name)
	    do
	(if (and (connection-satisfies-invoke-requirements-p
		   connection block link (forward-link-sense link) disconnecting?)
		 (eq subject-name (forward-link-designation link)))
	    (add-tuple-to-link-list link nil))))

    ;; Chain to references to a class of this object.
    (loop for link in (forward-chaining-list-for-classes
			(class-inheritance-path
			  (class-description-slot connection)))
	  for designation = (forward-link-designation link)
	  do
      (if (and (connection-satisfies-invoke-requirements-p
		 connection block link (forward-link-sense link) disconnecting?)
	       (not (symbolp designation))
	       (not (and (domain-of-designation designation)
			 (symbolp (role-of-designation designation)))))
	  (add-tuple-to-link-list link connection)))
    (if subject-name-cons? (reclaim-eval-cons-macro subject-name-cons?))))

;; This could be optimized to not make a connection frame for the disconnecting
;; case.  This would require replacing the (class-inheritance-path ... form.

(defun connection-satisfies-invoke-requirements-p (connection block link stored-sense disconnecting?)
  (and (connection-sense-matches-p stored-sense disconnecting?)
       (designation-could-denote-item-p (forward-link-second-designation link) block)
       (let ((filter-name? (forward-link-symbolic-value link))
	     (connection-structure
	       (connection-for-this-connection-frame connection)))
	 (or (not filter-name?)
	     (case filter-name?
	       ((at-an-input)
		(and (connection-directed? connection-structure)
		     (eq (output-end-object connection-structure) block)))
	       ((at-an-output)
		(and (connection-directed? connection-structure)
		     (eq (input-end-object connection-structure) block)))
	       (t  ; at-port case
		(eq filter-name?
		    (get-port-name-given-block-and-connection block connection-structure))))))))
		
(defun invoke-rules-for-indirect-connection-chaining (connection disconnecting?)
  ;; Form set of input end objects.  Form set of output end objects.
  ;; Call invoke-rules-for-indirect-connection-chaining-for-pair for each input-output pair.
  (let* ((connection-frame
	   (get-or-make-connection-frame-and-activate-if-appropriate connection))
	 (input-end-entities-or-triples-found-in-search
	   (search-for-entities-at-input-end connection-frame 'object nil))
	 (output-end-entities-or-triples-found-in-search
	   (search-for-entities-at-output-end connection-frame 'object nil)))

    ;; In this case, since search-for-entities-at-input-end is used,
    ;; input-end-entities-or-triples-found-in-search and
    ;; output-end-entities-or-triples-found-in-search will contain entities rather than triples.
    ;; Iterate over input set.  For each input-set-entity, iterate over output set to form
    ;; cross-product of all pairs of input set and output set entities.
    ;; Call invoke-rules-for-indirect-connection-chaining-for-pair for each such pair.

    (loop for input-set-entity in input-end-entities-or-triples-found-in-search
	  do
      (loop for output-set-entity in output-end-entities-or-triples-found-in-search
	    do
	(invoke-rules-for-indirect-connection-chaining-for-pair
	  connection-frame input-set-entity output-set-entity disconnecting?)
	(invoke-rules-for-indirect-connection-chaining-for-pair
	  connection-frame output-set-entity input-set-entity disconnecting?)))

    ;; Reclaim sets.
    (reclaim-eval-tree input-end-entities-or-triples-found-in-search)
    (reclaim-eval-tree output-end-entities-or-triples-found-in-search)))



(defun invoke-rules-for-indirect-connection-chaining-for-pair
       (connection-frame input-set-entity output-set-entity disconnecting?)
  (let ((current-computation-frame-previously-bound?
         (framep *current-computation-frame*))
	(*links-and-objects* nil))
    (unless current-computation-frame-previously-bound?
      (setq *current-computation-frame* input-set-entity))
    (collect-rules-for-indirect-connection-chaining
     connection-frame input-set-entity output-set-entity disconnecting?)
    ;; Schedule the collected rules for invocation.
    (loop with role?
	  with local-name?
	  with chain-object
	  with second-designation
	  with second-role?
	  with second-local-name?
	  with second-chain-object?
	  for link-entry in *links-and-objects*
	  for link = (car link-entry)
	  for recipient = (forward-link-recipient link)
	  do
          ;; The forward link recipient will always be a rule, but cover the
          ;; true-value-update-recipient case just in case.  Also make sure that the
          ;; rule is active.
          (when (and (not (true-value-update-recipient-p recipient))
                     (runnable-p recipient))
            (setq role? (forward-link-focus link)
                  local-name? (if role? (forward-link-focus-local-name link) nil)
                  chain-object (if role? (cdr link-entry) nil)
                  second-designation (forward-link-second-designation link)
                  second-role? (forward-link-second-focus link)
                  second-local-name? (if second-role?
                                         (forward-link-second-focus-local-name
                                          link)
                                       nil)
                  second-chain-object?
                  (if second-role?
                      (if (designation-could-denote-item-p
                           second-designation output-set-entity)
                          output-set-entity
                        nil)
                    nil))
            (unless (and second-role? (not second-chain-object?))
              (when (major-trace-message-will-be-written-p)
                (write-major-indirect-connection-chaining-trace-message
                 role? second-role? recipient chain-object
                 second-chain-object? local-name? second-local-name?
                 disconnecting? connection-frame output-set-entity))
              (cond
               ((and role? second-role?)
                (let ((constraint-alist (eval-list
                                         (eval-cons
                                          (or second-local-name? second-role?)
                                          second-chain-object?))))
                  (generate-and-schedule-rule-instances
                   recipient role? local-name? chain-object
                   'forward-chaining nil
                   (rule-priority recipient)
                   constraint-alist)
                  (reclaim-eval-cons-macro (car constraint-alist))
                  (reclaim-eval-cons-macro constraint-alist)))
               (role?
                (generate-and-schedule-rule-instances
                 recipient role? local-name? chain-object
                 'forward-chaining nil
                 (rule-priority recipient)
                 nil))
               (second-role?
                (generate-and-schedule-rule-instances
                 recipient second-role? second-local-name? second-chain-object?
                 'forward-chaining nil
                 (rule-priority recipient)
                 nil))
               (t
                (generate-and-schedule-rule-instances
                 recipient nil nil nil
                 'forward-chaining nil
                 (rule-priority recipient)
                 nil)))))
          (reclaim-eval-cons-macro link-entry))
    (unless current-computation-frame-previously-bound?
      (setq *current-computation-frame* nil))
    (reclaim-eval-list-macro *links-and-objects*)))



(defun write-major-indirect-connection-chaining-trace-message
       (role? second-role? recipient chain-object second-chain-object?
	local-name? second-local-name? disconnecting? connection-frame output-set-entity)
  (write-major-trace-message
    (cond
      ((and role? second-role?)
       (tformat
	 "Scheduling chaining to ~NF with ~NF as ~A and ~NF as ~A ~
          because a connection was ~a for these items."
	 recipient
	 chain-object
	 (or local-name? role?)
	 second-chain-object?
	 (or second-local-name? role?)
	 (if disconnecting? "broken" "made")))
      (role?
       (tformat
	 "Scheduling chaining to ~NF with ~NF as ~A ~
          because a connection of class ~A connected to ~NF was ~A."
	 recipient
	 chain-object
	 (or local-name? role?)
	 (class connection-frame)
	 output-set-entity
	 (if disconnecting? "broken" "made")))
      (second-role?
       (tformat
	 "Scheduling chaining to ~NF with ~NF as ~A ~
          because a connection of class ~A connected to ~NF was ~A."
	 recipient
	 second-chain-object?
	 (or second-local-name? second-role?)
	 (class connection-frame)
	 output-set-entity
	 (if disconnecting? "broken" "made")))
      (t
       (tformat
	 "Scheduling chaining to ~NF ~
          because a connection of class ~A connected to ~NF was ~A."
	 recipient
	 (class connection-frame)
	 output-set-entity
	 (if disconnecting? "broken" "made"))))))



;;; The function `collect-rules-for-indirect-connection-chaining' iterates across the
;;; forward chaining lists of an input-set-entity of a newly made or broken connection.
;;; Since the input-set-entity will never be embedded in an attribute of another object,
;;; a parent stack is not utilized.

(defun collect-rules-for-indirect-connection-chaining
       (connection-frame input-set-entity output-set-entity disconnecting?)
  (let* ((subject-names? (name-or-names-for-frame input-set-entity))
	 (subject-name-cons?
	   (if (and subject-names?
		    (symbolp subject-names?))
	       (setq subject-names? (eval-cons subject-names? nil))
	       nil)))
    ;; Chain to any name of the object.
    (loop for subject-name in subject-names?
	  do
      (loop for link in (forward-chaining-list-macro subject-name)
	    do
	(if (and (input-and-output-set-entities-satisfy-invoke-requirements-p
		   connection-frame input-set-entity output-set-entity
		   link (forward-link-sense link) disconnecting?)
		 (eq subject-name (forward-link-designation link)))
	    (add-tuple-to-link-list link nil))))

    ;; Chain to references to a class of this object.
    (loop for link in (forward-chaining-list-for-classes
			(class-inheritance-path
			  (class-description-slot input-set-entity)))
	  for designation = (forward-link-designation link)
	  do
      (if (and (input-and-output-set-entities-satisfy-invoke-requirements-p
		 connection-frame input-set-entity output-set-entity
		 link (forward-link-sense link) disconnecting?)
	       (not (symbolp designation))
	       (not (and (domain-of-designation designation)
			 (symbolp (role-of-designation designation)))))
	  (add-tuple-to-link-list link input-set-entity)))
    (if subject-name-cons? (reclaim-eval-cons-macro subject-name-cons?))))

(defun input-and-output-set-entities-satisfy-invoke-requirements-p
    (connection-frame input-set-entity output-set-entity link stored-sense disconnecting?)
  (declare (ignore connection-frame input-set-entity))
  (and (connection-sense-matches-p stored-sense disconnecting?)
       (designation-could-denote-item-p (forward-link-second-designation link) output-set-entity)))

;; Currently, there are no filters (directional, port, etc.) here, unlike the direct connection case.




;;;; NUPEC Synchronization Chaining




;;; Within the NUPEC enchanced version of G2, another form of chaining which
;;; occurs after the completion of any nupec synchronization is available.

;;; The macro `nupec-synchronization-sense-matches-p' takes a sense
;;; from a forward chaining link and returns whether or not the senses match.
;;; Matching sense in this case means that the sense is eq to the symbol
;;; NUPEC-SYNCHRONIZATION-OCCURS.

(defmacro nupec-synchronization-sense-matches-p (stored-sense)
  `(eq ,stored-sense 'nupec-synchronization-occurs))




;;; Whenever an icon is moved and the system is running, the function
;;; `invoke-rules-for-movement-chaining' will be called with the icon which has
;;; just been moved and with a symbol naming the mover of the icon, currently
;;; either :moved-by-the-user or :moved-by-the-inference-engine.  This function
;;; will collect those whenever rules which should be invoked through event
;;; predicates which check for movement, and it will then schedule them for
;;; invocation.

;;; Whenever a synchronization is completed in a target system, the function
;;; `invoke-rules-for-nupec-synchronization-chaining' will be called.  It takes
;;; no arguments.  It will collect those whenever rules which should be invoked
;;; through the event proposition for NUPEC synchronization and will schedule
;;; them for execution.

(defun invoke-rules-for-nupec-synchronization-chaining ()
  (let ((*links-and-objects* nil))
    (collect-rules-for-nupec-synchronization-chaining)
    ;; Schedule the collected rules for invocation.
    (loop for link-entry in *links-and-objects*
	  for link = (car-of-cons link-entry)
	  for recipient = (forward-link-recipient link)
	  do
          ;; The forward link recipient will be either an update list or a rule
          ;; frame.  Do nothing if it is a true value update recipient.
          (when (and (not (true-value-update-recipient-p recipient))
                     (runnable-p recipient))
            (tformat-major-trace-message
             "Scheduling event chaining to ~NF because a NUPEC synchronization ~
           has occurred."
             recipient)
            (generate-and-schedule-rule-instances
             recipient nil nil nil 'forward-chaining nil
             (rule-priority recipient) nil))
          (reclaim-eval-cons-macro link-entry))
    (reclaim-eval-list *links-and-objects*)))




;;; All links for NUPEC synchronization events are stored on the plist of the
;;; symbol nupec-synchronization-occurs.  Just in case some fool gave a frame
;;; the same name, check that the sense is correct.  Note that there can never
;;; be a focus for chaining from this event.

(defun collect-rules-for-nupec-synchronization-chaining ()
  (loop for link in (forward-chaining-list 'nupec-synchronization-occurs)
	do
    (when (nupec-synchronization-sense-matches-p (forward-link-sense link))
      (add-tuple-to-link-list link nil))))


;;;; Generic Event Chaining

;;; Generic Events are way of pumping in notifications from the outside world,
;;; usually Object-oriented bridges like CorbaLink, JavaLink, and ActiveXLink,
;;; to be seen by the G2 whenever rules event detection.  This mechanism can be
;;; extended reasonably easily to include true-value-update-recipient/wake-ups.


(defun invoke-rules-for-generic-event-chaining
       (event-name item event-object)
  (let ((current-computation-frame-previously-bound?
         (framep *current-computation-frame*))
	(*links-and-objects* nil))
    (unless current-computation-frame-previously-bound?
      (setq *current-computation-frame* item))
    (collect-links-for-generic-event-chaining item event-name)
    ;; Schedule the collected rules for invocation.
    (loop with role?
	  with local-name?
	  with chain-object
	  with second-designation
	  with second-role?
	  with second-local-name?
	  for link-entry in *links-and-objects*
	  for link = (car link-entry)
	  for recipient = (forward-link-recipient link)
	  do
          ;; The forward link recipient will always be a rule, but cover the
          ;; true-value-update-recipient case just in case.  Also make sure that the
          ;; rule is runnable.
          (when (and (not (true-value-update-recipient-p recipient))
                     (runnable-p recipient))
            (setq role? (forward-link-focus link)
                  local-name? (and role? (forward-link-focus-local-name link))
                  chain-object (and role? (cdr link-entry))
                  second-designation (forward-link-second-designation link)
                  second-role? (forward-link-second-focus link)
                  second-local-name? (and second-role?
                                          (forward-link-second-focus-local-name
                                           link)))
            (when role?
              (let ((constraint-alist (eval-list
                                       (eval-cons
                                        (or second-local-name? second-role?)
                                        event-object))))
                (generate-and-schedule-rule-instances
                 recipient role? local-name? chain-object
                 'forward-chaining nil
                 (rule-priority recipient)
                 constraint-alist)
                (reclaim-eval-cons-macro (car constraint-alist))
                (reclaim-eval-cons-macro constraint-alist))))
          (reclaim-eval-cons-macro link-entry))
    (unless current-computation-frame-previously-bound?
      (setq *current-computation-frame* nil))
    (reclaim-eval-list-macro *links-and-objects*)))

(defun-for-system-procedure g2-invoke-generic-event-rules
    (event-name-ev item event-object)
  (let ((event-name
	  (prog1 (evaluation-symbol-symbol event-name-ev)
	    (reclaim-evaluation-symbol event-name-ev))))
    (invoke-rules-for-generic-event-chaining
      event-name item event-object)))


;;; The function `collect-links-for-generic-event-chaining' iterates across the
;;; forward chaining lists for the subject of a newly added or deleted relation.

(defun-simple generic-event-sense-matches-p (link event-name)
  (and (eq (forward-link-sense link) 'has-generic-event)
       (eq (forward-link-symbolic-value link) event-name)))

(defun collect-links-for-generic-event-chaining
       (item event-name)
  (let* ((item-names? (name-or-names-for-frame item))
	 (item-name-cons?
	   (if (and item-names?
		    (symbolp item-names?))
	       (setq item-names? (eval-cons item-names? nil))
	       nil))
	 (parent-stack (make-parent-stack item)))
    ;; Chain to any name of the object.
    (loop for item-name in item-names?
	  do
      (loop for link in (forward-chaining-list item-name)
	    do
	(if (and (generic-event-sense-matches-p link event-name)
		 (eq item-name (forward-link-designation link)))
	    (add-tuple-to-link-list link nil))))
    ;; Chain to the attribute name of any parent entity.
    (when parent-stack
      (let ((parent-stack-entry (car-of-cons parent-stack)))
	(loop for link in (forward-chaining-list
			    (parent-stack-attribute parent-stack-entry))
	      do
	  (if (generic-event-sense-matches-p link event-name)
	      (let ((parent-frame? (find-referenced-parent
				     parent-stack
				     (forward-link-designation link))))
		(if parent-frame?
		    (add-tuple-to-link-list link parent-frame?)))))))
    ;; Chain to references to a class of this object.
    (loop for link in (forward-chaining-list-for-classes
			(class-inheritance-path
			  (class-description-slot item)))
	  for designation = (forward-link-designation link)
	  do
      (if (and (generic-event-sense-matches-p link event-name)
	       (not (symbolp designation))
	       (not (and (domain-of-designation designation)
			 (symbolp (role-of-designation designation)))))
	  (add-tuple-to-link-list link item)))
    (if item-name-cons? (reclaim-eval-cons-macro item-name-cons?))
    (reclaim-parent-stack parent-stack)))


;;; `maybe-get-user-supplied-focus-local' takes a class name and possibly a
;;; local-name from a chaining link ina rule, and returns the local-name iff it
;;; is a user-supplied local variable name, as opposed to NIL or a
;;; rule-compiler generated one.  Otherwise, it returns NIL.

(defun maybe-get-user-supplied-focus-local (class-name local-name?)
  (when local-name?
    ;; This is a TOTAL kludge, but there really is no other good way to
    ;; figure this out without doing a total rewalk of the rule, which seems
    ;; excessive.  We should either set a property on the generated locals,
    ;; or set an attribute on the chaining link so we can tell, but that
    ;; would require a recompile of the rule to work so we definitely can't
    ;; do that now. -dkuznick, 4/15/05  Oh look, it's tax day.
    (let* ((text-to-check
	     (twith-output-to-text-string
	       (tformat #w"COMPILER-")
	       (tformat (symbol-name-text-string class-name))
	       (tformat #w"-")))
	   (text-to-check-length (text-string-length text-to-check))
	   (local-name-text (symbol-name-text-string local-name?)))
      (prog1
	  ;; First check that the beginning of local-name looks like
	  ;; #w"COMPILER-<CLASS-NAME>-"
	  (if (and (text-string= local-name-text text-to-check
				 :end1 text-to-check-length)
		   ;; Then check if it ends in an integer.
		   (eq (syntactically-numeric-substring-p
			 local-name-text
			 text-to-check-length
			 (text-string-length local-name-text)
			 t
			 t
			 t)
		       'integer))
	      nil
	      local-name?)
	(reclaim-text-string text-to-check)))))

;;; A VERY optimized and specialized test to be used in
;;; get-forward-chaining-names-and-locals instead of using EQUAL.
(defun collected-focus-class-names-and-locals-equal (list1 list2)
  (and (eq (car-of-cons list1) (car-of-cons list2))
       (eq (cadr-of-cons list1) (cadr-of-cons list2))))

;;; `get-forward-chaining-names-and-locals' is used to get back a fresh
;;; gensym-tree of forward-chaining-link focal class names and their associated
;;; local variable names from a list of chaining-links (presumably from a rule)
;;; rule (this has nothing to do directly with the "focal classes" attribute of
;;; a rule).  The return form is:
;;;
;;; ((class-name1 local-name-1) (class-name1 local-name2) (class-name2
;;;     local-name3) ...).
;;;
;;; It is valid for a local-name-n to be NIL, which means that a class was
;;; mentioned without a local variable.  There will be at most one clause like
;;; this returned for each class, no matter how many times it is mentioned
;;; without a local variable.
;;;
;; This is similar in many ways to what is done to get the binding for
;; chaining-roles in the slot-value-compiler for rule, but is different enough
;; that trying to abstract it so it was useable in both cases was getting
;; messy, complex and hard to read. -dkuznick, 4/15/05

(defun get-forward-chaining-names-and-locals (chaining-links)
  (loop with collected-roles = nil
	for (nil . link) in chaining-links
	for forward-chaining-link-p = (forward-chaining-link-p link)
	for focus-role? = (when forward-chaining-link-p
			    (forward-link-focus link))
	for user-focus-local? = (when focus-role?
				  (maybe-get-user-supplied-focus-local
				    focus-role?
				    (forward-link-focus-local-name link)))
	for second-focus-role? = (when forward-chaining-link-p
				   (forward-link-second-focus link))
	for user-second-focus-local? =
	(when second-focus-role?
	  (maybe-get-user-supplied-focus-local
	    second-focus-role?
	    (forward-link-second-focus-local-name link)))
	do
    (when focus-role?
      (gensym-pushnew (gensym-list focus-role? user-focus-local?)
		      collected-roles
		      :test #'collected-focus-class-names-and-locals-equal))
    (when second-focus-role?
      (gensym-pushnew (gensym-list second-focus-role? user-second-focus-local?)
		      collected-roles
		      :test #'collected-focus-class-names-and-locals-equal))
    
	finally (return collected-roles)))

;;; `get-forward-chaining-focus-info-as-sequence' takes a rule and returns a fresh
;;; evaluation-sequence of evaluation-structures which describe the names of
;;; classes mentioned in the left hand side of the rule by "any" clauses along
;;; with their corresponding local variable, and whether a local variable was
;;; specified.

(defun get-forward-chaining-focus-info-as-sequence (rule)
  (loop with names-and-locals = (get-forward-chaining-names-and-locals
				  (rule-chaining-links-function rule))
	for (class-name local-name?) in names-and-locals
	collect (allocate-evaluation-structure-inline
		  'chaining-link-focus-class-name
		  class-name
		  'chaining-link-focus-local-name-is-specified
		  (make-evaluation-boolean-value local-name?)
		  'chaining-link-focus-local-name
		  local-name?)
	  into structures using eval-cons
	finally (reclaim-gensym-tree names-and-locals)
		(return (allocate-evaluation-sequence structures))))

(defun-for-system-procedure g2-get-forward-chaining-focus-info ((rule item))
  (declare (values sequence)
	   (keeps-g2-local-variables-valid t))
  (get-forward-chaining-focus-info-as-sequence rule))


;;; finding out if there are rules to backward chain to a variable

;;; `get-backward-chaining-rules-for-variable' returns a fresh eval-list of
;;; rules which can backward chain to the given variable.  This is done via
;;; static analysis.

(defun get-backward-chaining-rules-for-variable (var)
  ;; This is finding ALL rules.  We can make this faster by stopping when we
  ;; find the first one, but that requires duplicating or re-factoring a lot of
  ;; code.  This should be fine for a first pass.  It is stolen from code in
  ;;; describe-backward-chaining-short-reps.
  (let ((*links-and-objects* nil))
    (collect-rules-for-backward-chaining
     var
     (type-specification-of-variable-or-parameter-value var))
    ;; If we want to return a list of rules we need to loop over each entry in
    ;; *links-and-objects* and call backward-link-rule on the car.
    (prog1
	(loop for (link . nil) in *links-and-objects*
	      collect (backward-link-rule link) using eval-cons)
      (reclaim-eval-tree *links-and-objects*))))


;;; The system procedure `g2-get-backward-chaining-rules-for-variable' takes a
;;; variable and returns a sequence of all rules which can backwards chain to
;;; this variable.  Notice this does NOT mean that any of these rules wil
;;; actually give the variable a value, it simply does a static analysis.  A
;;; typical use of this would be figuring out if a "collect data" can be
;;; avoided (because there are no backwards-chaining rules), as it's currently
;;; expensive to timeout from one.  Note it currently does not take into
;;; account whether a variable has do not backward chain specified, or gets its
;;; value from a formula.  This should eventually be turned into a more general
;;; facility which will take this and other things into account.

(defun-for-system-procedure g2-get-backward-chaining-rules-for-variable ((var item))
  (declare (values sequence)
	   (keeps-g2-local-variables-valid t))
  (allocate-evaluation-sequence
    (get-backward-chaining-rules-for-variable var)))

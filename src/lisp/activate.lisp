;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module ACTIVATE: Frames for Knowledge Bases

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin


;;;; Forward References

;; To EVENTS-G2
(declare-forward-reference send-ws-representations-item-virtual-attribute-change
			   function)


;;;; Activate, Deactivate, Disable, and Enable



;;; Frame A is the `superior' of frame B, and frame B is an `inferior' of frame A
;;; if and only if one of the following is true:

;;; (1) A is a kb-workspace and B is an entity placed on A.
;;; (2) A is a kb-workspace and B is a frame of a connection placed on A.
;;; (3) A is an entity or connection, and B is an attribute of A.
;;; (4) A is an entity and B is a subworkspace (kb-workspace) of A.

;;; Note that every frame has at most one superior, although there are three different
;;; ways for a frame to be a superior (parent-frame, superblock?, parent-of-subworkspace?)

;;; The ancestors of a frame are its superior and the ancestors of its superior.

;;; The following discussion completely excludes frames not having activate and 
;;; deactivate methods.


;;; A kb-workspace is activation controllable if either (1) it has no superior, or
;;; (2) it is a subworkspace of an entity for which activatable-subworkspace-p. The
;;; former is called a `top-level' block of a kb. The latter presently consist of
;;; subworkspaces of entities having the configuration activatable-subworkspace. This will 
;;; be extended to include procedure bodies.

;;; `Manually disabled' is a kb saved property of frames which is altered only by editing.
;;; A frame is manually disabled when the user deactivates it, and remains so until the
;;; user restores it. Manual disabling does not propagate beyond the particular frame, 
;;; although the consequences of it do as described below.


;;; A frame which is not an activation controllable kb-workspace is active if and only if 
;;; the conjunction of the following is true. 

;;; (1) The frame status is OK.
;;; (2) The frame has not been manually disabled.
;;; (3) It superior is active.

;;; A top level kb-workspace is active if and only if (1) through (3) are true and
;;; (4) G2 is running or paused.

;;; A subworkspace of an entity which has the configuration activatable-subworkspace is active
;;; if and only (1) through (3) are true and:

;;; (5) the activate command has been applied to the superior entity at a time when (1) 
;;; through (3) were true for both the superior entity and the subworkspace, and neither the
;;; deactivate command nor the lapse of any of these conditions has caused it to become
;;; inactive since then.


;;; The flags used to implement activation are as follows: 
;;; (1) active is true if and only if the frame is active
;;; (2) ancestor-not-activatable is true if and only if some ancestor is manually disabled
;;;     or not ok.
;;; (3) manually-disabled is true if and only if the frame has been manually disabled.


;;; Class Methods:

;;; The following two methods are not recursive and need to be written specifically for 
;;; certain types of frames such as rules and variables. They are called only by the methods
;;; that follow them:

;;; activate frame
;;;      Does whatever specific activation is necessary for frames of that type and
;;;      sets active flag t. (Does nothing if already active.)

(def-generic-method activate (kb-frame)
  )

;;; deactivate frame
;;;      Does whatever specific deactivation is necessary for frames of that type and
;;;      sets active flag nil. (Does nothing if already inactive.)

(def-generic-method deactivate (kb-frame)
  )

;;; The following four methods are identical for all kb-frames. The last two are recursive:

;;; (manually-disable frame)
;;;      Sets manually-disabled to t and calls deactivate-and-propagate.

(def-generic-method manually-disable (kb-frame)
  )



;;; (manually-enable-fram
;;;      Sets manually-disabled to nil, and calls activate-if-possible-and-propagate or
;;;         deactivate-and-propagate depending on the environment.

(def-generic-method manually-enable (kb-frame)
  )



;;; (activate-if-possible-and-propagate frame)
;;;   is called only if one of the following is true:
;;;     (a) The superior frame is active and is not an entity for which
;;;             activatable-subworkspace.
;;;     (b) The superior frame is active and is an entity for which activatable-subworkspace,
;;;             and the activate action is now being performed.
;;;     (c) The frame is a top level workspace, and system is running.
;;;     (d) The frame is a transient object.
;;;     In summary, there is no environmental reason for the frame not to be active.

;;;   It is called on the following occasions:
;;;     (d) On starting G2, for all top level kb-workspaces.
;;;     (e) On a new object when placed on an active kb-workspace.
;;;     (f) On a new connection when placed on an active block.
;;;     (g) On a new entity when placed in an attribute of an active frame.
;;;     (h) On an inactive object which is moved to an active kb-workspace.
;;;     (i) By update-frame-status, when it changes the status to ok, but
;;;             only if (a) above applies.
;;;     (j) By manually-enable, but only if (a) or (c) above applies.
;;;     (k) By make-transient-object-r-message.
;;;     (k) Need to review what happens during merge. Should not be different than
;;;             adding things while running?!
;;;     (l) Recursively.

;;;   What it does:
;;;      (m) Determines whether the frame can be be activated:
;;;           Frame status is OK
;;;           Frame is not manually deactivated
;;;      (n) Does nothing and exits if frame is already active; otherwise it
;;;      (o) Calls activate method if frame can be activated.
;;;      (p) Sets ancestor-not-activatable flag to nil. (If it were t, you couldn't be here.)
;;;      (q) If frame has been activated then call activate-if-possible-and-propagate
;;;          for all inferiors, except subworkspaces of an an activatable-subworkspace
;;;          entity. Otherwise call deactivate-and-propagate with a second
;;;          argument which is t (because this frame is not capable of activation).

(def-generic-method activate-if-possible-and-propagate (kb-frame)
  )
    

;;; deactivate-and-propagate frame ancestor-not-ok?
;;;   It is called on the following occasions:
;;;      (a) On resetting G2, for all top level kb-workspaces.
;;;      (a) On a new entity, when placed on a kb-workspace that is manually disabled
;;;              or has a superior that is manually disabled or not ok.
;;;      (c) On a new connection, when placed on a kb-workspace that is manually disabled
;;;              or not ok, or has a superior that is ...
;;;      (d) On an active entity that is moved to an inactive kb-workspace, or
;;;              on any entity when it is moved to a kb-workspace which is ...
;;;      (d) On a new object when placed in an attribute of a frame that is ...
;;;      (e) By update-frame-status:
;;;		(i)  If the frame is made ok, but cannot be activated.
;;;                    (Purpose is to propagate ancestor-not-activatable.)
;;;             (ii) If the frame status is made other than ok.
;;;      (f) By manually-disable.
;;;      (f) Merge?!
;;;      (g) Recursively when (i) the entity was fomerly active, or (ii) either the entity
;;;          or an ancestor is becoming not activatable. (Actually safe to recur always
;;;          but marginally more efficient to do it this way.) 

;;;   What it does:
;;;      (h) Calls deactivate method if the frame is not inactive.
;;;      (i) Sets ancestor-not-activatable flag according to its second argument.
;;;      (j) Calls itself recursively. The second argument is the logical OR of
;;;          its own ancestor-not-activatable flag, its own frame-status, and its
;;;          own disabled status.

(def-generic-method deactivate-and-propagate (kb-frame ancestor-not-ok?)
  )


;;; Note that activate-if-possible-and-propagate and deactivate-and-propagate are
;;; defined for all kb-frames. Note, also, that these are the only places that call
;;; activate and deactivate methods, and that activate and deactivate methods are optional.


;;; The `activate-subclass-of-entity' and the `deactivate-subclass-of-entity' methods
;;; ...

(def-generic-method activate-subclass-of-entity (block)
  )

(def-generic-method deactivate-subclass-of-entity (block)
  )



;;; Ancestor-not-activatable is true if at least one ancestor of the entity is either
;;; manually-deactivated or has a frame status other than ok.

(def-generic-method note-ancestor-not-activatable (entity)
  )

(def-generic-method note-ancestor-manually-enabled (kb-frame)
  )

(def-class-method note-ancestor-manually-enabled (kb-frame)
  (propagate-simple-method-to-attributes
    kb-frame
    'note-ancestor-manually-enabled))

(def-class-method note-ancestor-manually-enabled (kb-workspace)
  (funcall-superior-method kb-workspace)
  (loop for subblock being each subblock of kb-workspace
	do
    (funcall-simple-method-macro 'note-ancestor-manually-enabled subblock)))


;;; Superior-frame returns either (a) the superblock of frame, if frame is a subblock,
;;; (b) the parent of frame, if frame is a variable used for an attribute or a subworkspace,
;;; or (c) the superblock of the input end object of the connection for frame, if frame is
;;; a connection frame.

;;; Note that it has been coded for maximal speed, and making use of the fact that
;;; workspace, connection, and simulation-subtable are all subclasses of block, and that
;;; they are all disjoint classes.

(defun-simple superior-frame (frame)
  (let ((class-description (class-description-slot frame)))
    (and (class-description-of-class-p class-description 'block)
	 (or (superblock? frame)
	     (parent-frame frame)
	     (class-description-class-case class-description
	       ((workspace)
		(parent-of-subworkspace? frame))
	       ((connection)
		(let ((connection? (connection-for-this-connection-frame frame))) ;; Nil while initializing
		  (when connection?
		    (superblock? (input-end-object connection?)))))
	       ((simulation-subtable)
		(parent-variable frame)))))))


;;; Ancestor-p is true if frame1 is a strict ancestor of frame2, in the superior-frame
;;; sense of ancestor.  It is not coded for maximal speed.

(defun-simple ancestor-p (frame1 frame2)
  (loop for frame? = (superior-frame frame2) then (superior-frame frame?)
	do
    (cond ((null frame?) (return nil))
	  ((eq frame? frame1) (return t)))))

;; Using "ancestor" for the transitive closure of "superior" is metaphorical mixup -- LH.


;;; In the slot-putter for direct-superiors-of-defined-class,
;;; we temporarily deactivate items while changing the classes they
;;; inherit from. This has good consequences (it does the right
;;; thing if we change whether the object is a gsi-data-server,
;;; for example), and bad consequences (it will cause initially
;;; rules to fire again if the object is a rule, for example).
;;; So we invent the new concept of "suspend-activation" and
;;; "resume-activation" to
;;; handle this situation, that does a minimal activation
;;; and deactivation. -alatto, 7/15/03

;;; In order to make data-service work properly when a class is edited
;;; to add or remove data-server classes from its inheritance list, the
;;; instances of this class are deactivated and then activated again
;;; when the inheritance is changed.

;;; However, while some deactivation and activation methods, such as the
;;; ones on gsi-data-service, should be called when the object starts or
;;; stops inheriting from this method, in order to assure proper
;;; functioning of the item, other methods should not be called.
;;; For example, calling deactivate and then activate on an initially
;;; rule will cause that rule to fire, which should not happen just
;;; because the set of other classes from which the class of the
;;; inherits has changed.

;;; So we've added a new concept, of suspend-activation and resume-activation,
;;; to handle this case. Suspending and then resuming activation of
;;; an active data server will cause it to note any changes that
;;; have occurred so that data service can continue properly. And
;;; suspending and resuming an instance that has just become
;;; a data server will cause initializations that normally occur
;;; when a data server is activated to occur. But other deactivate
;;; and activate methods will not be called by suspend-activation
;;; and resume-activation. In particular, since the foundation class
;;; of an instance cannot be changed, any methods associated with
;;; foundation classes are not called by suspend-activation and
;;; resume-activation. This avoids the problem of having
;;; an initially rule fire again when it is suspended and then resumed.
;;; -alatto, 7/16/03

;;; To avoid duplicating code between the new suspend and resume
;;; functions and the existing deactivate and activate methods,
;;; suspend and resume work by setting a special variable,
;;; in-suspend-resume, and calling the existing activate and deactivate
;;; methods. This variable is in turn checked by activate and deactivate
;;; methods, which take no action if they are methods on foundation
;;; classes and the variable is set to t.

;;; The slot-putter for gsi-interface-name, which also uses the
;;; trick of deactivation and immediate reactivation to cause
;;; the data server to process the new name, and also therefore was
;;; subject to the above bugs, was also modified to use the new
;;; suspend and resume functions. -alatto, 7/16/03

;;; `in-suspend-resume-p' is set to t to indicate that any calls to
;;; deactivate or activate should only do a suspend-activation or
;;; resume-activation, respectively--- that is, only actions
;;; associated with non-foundation classes should take place.

(def-system-variable in-suspend-resume-p activate nil)

;;; `suspend-activation' is like deactivate-and-propagate, but
;;; only takes actions associated with non-foundation classes.
;;; It should only be used when resume-activation is about to be
;;; called; the purpose is not actually to deactivate an instance,
;;; but to rerun deactivate and activate methods, to take into
;;; account new inheritance structures or new interface names.
;;; -alatto, 7/16/03

(defun suspend-activation (item)
  (let ((in-suspend-resume-p t))
    (funcall-method 'deactivate-and-propagate item nil)))

;;; `resume-activation' is like activate-if-possible-and-propagate, but
;;; only takes actions associated with non-foundation classes.
;;; It should only be used immediately after suspend-activation
;;; the purpose is not actually to activate an instance,
;;; but to rerun deactivate and activate methods, to take into
;;; account new inheritance structures or new interface names.
;;; -alatto, 7/16/03

(defun resume-activation (item)
  (let ((in-suspend-resume-p t))
    (funcall-method 'activate-if-possible-and-propagate item)))

;;; The function `existence-depends-on-p' takes two frames and checks if the
;;; existence of the first depends on the second.  This function is used to
;;; preflight deletions where the delete could clobber the thing executing the
;;; delete action.  There are two hierarchies which must be traversed to detect
;;; existence dependance.  The first is the object hierarchy, in that frames are
;;; dependent on the existence of their superiors.  The second hierarchy is the
;;; class hierarchy, in that frames are dependent on the existence of their user
;;; defined class and superior classes.  This predicate is trivially implemented
;;; here with no thought to optimization of merging paths in the search.

;;; Note that I now have to worry about merging paths.  If there is a definition
;;; of a class on a subworkspace of an instance of that class (yes, we do allow
;;; this), then the algorithm is in trouble, since it can get into an infinite
;;; loop.  So, I'll deter against this by keeping a list of the classes which
;;; have been checked.  I know this could be made better by marking the classes
;;; in some way, but all I really care about here is getting this project done.
;;; -jra 1/22/92

(def-system-variable existence-classes-already-checked activate nil)

(declare-side-effect-free-function existence-depends-on-p)

(declare-side-effect-free-function existence-depends-on-p-1)

(declare-side-effect-free-function frame-class-existence-depends-on-p-1)

(defun-simple existence-depends-on-p (possible-dependent-frame frame)
  (setq existence-classes-already-checked nil)
  (let ((result (existence-depends-on-p-1 possible-dependent-frame frame)))
    (reclaim-eval-list-macro existence-classes-already-checked)
    (setq existence-classes-already-checked nil)
    result))

(def-substitution-macro frame-class-existence-depends-on-p
			(possible-dependent-frame frame)
  (and (class-of-frame-is-user-defined-p possible-dependent-frame)
       (frame-class-existence-depends-on-p-1 possible-dependent-frame frame)))

(defun-simple existence-depends-on-p-1 (possible-dependent-frame frame)
  (or (eq possible-dependent-frame frame)
      (let ((superior? (superior-frame possible-dependent-frame)))
	(and superior?
	     (existence-depends-on-p-1 superior? frame)))
      (frame-class-existence-depends-on-p possible-dependent-frame frame)))

(defun-simple frame-class-existence-depends-on-p-1
	      (possible-dependent-frame frame)
  (loop for class in (class-inheritance-path
		       (class-description-slot possible-dependent-frame))
	do
    (unless (memq class existence-classes-already-checked)
      (eval-push class existence-classes-already-checked)
      (let ((class-definition-frame? 
	      (get-instance-with-name-if-any 'class-definition class)))
	(unless class-definition-frame?
	  (return nil))
	(when (existence-depends-on-p-1 class-definition-frame? frame)
	  (return t))))))




(def-class-method manually-disable (kb-frame)
  (funcall-superior-method kb-frame)
  (set-manually-disabled kb-frame)
  (when (and g2-has-v5-mode-windows-p
	     (frame-of-class-p kb-frame 'item))
    (send-ws-representations-item-virtual-attribute-change
      kb-frame (virtual-attribute 'manually-disabled?) nil))
  
  (unless (or system-is-running system-has-paused)
    ;; Update notes, when reset, to show the item is disabled.
    ;; If not reset, the update is handled within the deactivation.
    ;; - cpm, 10/6/95
    (if (frame-representations kb-frame)
	(update-representations-of-slot-value
	  kb-frame 'frame-status-and-notes)))
  (funcall-method 'deactivate-and-propagate kb-frame
		  (ancestor-not-activatable-p kb-frame))
  (schedule-task-to-invoke-existential-rules kb-frame 'is-disabled))



(def-class-method manually-enable (kb-frame)
  (funcall-superior-method kb-frame)
  (clear-manually-disabled kb-frame)
  (when (and g2-has-v5-mode-windows-p
	     (frame-of-class-p kb-frame 'item))
    (send-ws-representations-item-virtual-attribute-change
      kb-frame (virtual-attribute 'manually-disabled?) nil))

  (unless (or system-is-running system-has-paused)
    ;; Update notes, when reset, to show the item is enabled.  If not reset, the
    ;; update is handled within the activation or deactivation.  - cpm, 10/6/95
    (if (frame-representations kb-frame)
	(update-representations-of-slot-value 
	  kb-frame 'frame-status-and-notes)))

  ;; Only if environmentally ok, is it permitted to really activate.
  (let ((superior-frame (superior-frame kb-frame)))
    ;; Activation of a top level kb-workspace when system is running or superior
    ;; is active, and this is not an activatable subworkspace.
    (cond
      ((or (and (null superior-frame)
		(or system-is-running system-has-paused))
	   (and superior-frame
		(active-p superior-frame)
		(if (and (frame-of-class-p kb-frame 'kb-workspace)
			 (parent-of-subworkspace? kb-frame))
		    (not (activatable-subworkspace-p superior-frame))
		    t)))

       (funcall-method 'activate-if-possible-and-propagate kb-frame)
       (schedule-task-to-invoke-existential-rules kb-frame 'is-enabled))
      (t (funcall-method 'deactivate-and-propagate kb-frame
			 (ancestor-not-activatable-p kb-frame))
	 (funcall-method 'note-ancestor-manually-enabled kb-frame)))))




;;;; Units of activation

;; The following is per plan of ML and JRA, 10/31/89. It is not fully
;; implemented. In particular, initial rule scheduling and deactivation
;; does not work in this way, which is a problem.

;;; A unit of activation is all that gets activated at once. In the case of
;;; of system-start, this is all of G2 that is reachable from the forest
;;; of top level workspaces and their descendents (stopping at any item
;;; for which subactivatable-workspace). In all other cases, including
;;; activating an activatable subworkspace, it is the tree visited by
;;; activate-and-propagate-if-possible recursively starting with its
;;; outermost call.

;;; The purpose of having units is to activate everything in the unit
;;; before initializing everying in the unit. This is because initializations
;;; fail if the entire unit is not active. For example, forward chaining fails
;;; when items are not active.

;;; To implement this, there is a system variable items-needing-initialization
;;; is globally set to t. It is set to nil by the function handling
;;; the unit which is either system-start or an activate-and-propagate-if-possible
;;; method. Once set to nil, it is valid to push (item . frame-serial-number)
;;; onto it. The function that sets it from t to nil must later call
;;; initialize-items-needing-initialization, which resets the value to t.

;;; Clean-up-items-needing-initialization handles errors that throw out of the
;;; scope of the unit handling function.

;;; Handling initial rules will need to have some further mechanism in order
;;; to complete the deactivation as a unit.

;;; This protocol has now been abstracted in the macro with-activation-unit.
;;; All calls to activate should be in the dynamic scope of a call
;;; to with-activation-unit (typically contained in the
;;; activate-if-possible-and-propagate method). The
;;; items-needing-initialization variable should only be modified
;;; by this macro, note-item-needing-initialization,
;;; and clean-up-items-needing-initialization. -alatto, 7/16/03

;;; With-activation-unit returns one value, the first value returned by
;;; the last form in the body.

(defmacro with-activation-unit (&body body)
  (let ((old-value (gensym)))
    `(let ((,old-value items-needing-initialization))
       (when (eq ,old-value t)
	 (atomic-exchange items-needing-initialization nil))
       (prog1
	   (progn
	     ,@body)
	 (when (eq ,old-value t)
	   (initialize-items-needing-initialization))))))

(defun activate-in-new-activation-unit (item)
  (with-activation-unit
      (funcall-simple-method-if-any-macro 'activate item)))

;;; Now we use a binary-tree/skip-list to manage the (frame-serial-numer . item)
;;; pairs which are originally stored in `items-needing-initialization'. In this
;;; way the tree can be thread-safe in SymScale. Performance in legacy G2 could
;;; also be a little better. -- Chun Tian (binghe), May 2015.

(defun-simple make-items-needing-initialization-tree-function ()
  (make-items-needing-initialization-tree))

(def-system-variable items-needing-initialization-tree activate
  (:funcall make-items-needing-initialization-tree-function))

(def-system-variable items-needing-initialization activate t)
(defvar initializing-items-needing-initialization nil)



;;; The function `initialize-items-needing-initialization' initializes
;;; g2-arrays, variables, and parameters.  These are currently the only items
;;; needing initialization.

;;; The code is a special case.  It could be generalized later, such as by
;;; having an initialization method.  It does this without continuations
;;; because it would be more pernitious to delay some of these than to cause
;;; unresponsiveness, particularly when starting a system.  The list of conses
;;; is reclaimed, and items-needing-initialization is set to t.

(defun initialize-items-needing-initialization ()
  (let* ((*current-computation-frame* nil)
	 (current-computation-instance 'initial-value)
	 (initializing-items-needing-initialization t))

    ;; Currently g2-arrays, variables, and parameters are the only items
    ;; placed on the items-needing-initialization list (by their activate-
    ;; subclass-of-entity class methods).
    
    ;; First, initialize all of the arrays because otherwise forward chaining
    ;; on variables may cause uninitialized array access resulting in a G2
    ;; abort.
    (loop ; for (item . frame-serial-number) in items-needing-initialization
	  for (frame-serial-number . item) being
	    each binary-tree-entry-cons of items-needing-initialization-tree
	  when (and (frame-has-not-been-reprocessed-p item frame-serial-number)
		    (frame-of-class-p item 'g2-array))
	    do
       (setq *current-computation-frame* item)
       (initialize-g2-array item))
    
    ;; Initialize the variables and parameters.
    (loop ; for (item . frame-serial-number) in items-needing-initialization
	  for (frame-serial-number . item) being
	    each binary-tree-entry-cons of items-needing-initialization-tree
	  unless (or (frame-has-been-reprocessed-p item frame-serial-number)
		     (frame-of-class-p item 'g2-array))
	    do
	      (setq *current-computation-frame* item)
	      (let ((initial-value?
		      (initial-value-of-variable-or-parameter item)))
		(when (and initial-value? (not warmbooting?))
		  (cond ((slot-value-float-p initial-value?)
			 (put-initial-float-value item initial-value?))
			((slot-value-long-p initial-value?)
			 (put-initial-long-value item initial-value?))
			(t
			 (put-current-value
			   item
			   initial-value?
			   (data-type-of-variable-or-parameter-datum
			     initial-value? item)
			   'never nil nil)))))
	      (let ((interval? (if (frame-of-class-p item 'variable)
				   (background-collection-interval? item))))
		(when interval?
		  (let ((data-server? (get-data-server item)))
		    (when data-server?
		      (cond ((eq data-server? 'computation)
			     (begin-collecting-data-for-inference-engine
			       item interval?))
			    ((data-server-p data-server?)
			     (begin-collecting-data
			       data-server? item interval?))))))))
;    (loop for x in items-needing-initialization do
;      (reclaim-frame-serial-number (cdr x))
;      (setf (cdr x) nil))
;    (reclaim-eval-tree items-needing-initialization)
    (clean-up-items-needing-initialization)
    nil))

(defun put-initial-float-value (variable-or-parameter initial-value-float)
  (with-temporary-gensym-float-creation 
    initialize-items-needing-initialization
    (let* ((new-value (copy-managed-float initial-value-float))
	   (problem-string? 
	    (put-current-evaluation-value
	      variable-or-parameter
	      new-value
	      'never nil nil)))
      (when problem-string?
	(warning-message 1 "Cannot conclude initial value for ~NF: ~a"
	  variable-or-parameter problem-string?)
	(reclaim-text-string problem-string?)
	(reclaim-managed-float new-value)))
    nil))

(defun put-initial-long-value (variable-or-parameter initial-value-long)
  (with-temporary-creation 
    initialize-items-needing-initialization
    (let* ((new-value (copy-managed-long initial-value-long))
	   (problem-string? 
	    (put-current-evaluation-value
	      variable-or-parameter
	      new-value
	      'never nil nil)))
      (when problem-string?
	(warning-message 1 "Cannot conclude initial value for ~NF: ~a"
	  variable-or-parameter problem-string?)
	(reclaim-text-string problem-string?)
	(reclaim-managed-long new-value)))
    nil))

(defun clean-up-items-needing-initialization ()
;  (when (consp items-needing-initialization)
;    (loop for cons on items-needing-initialization doing
;      (reclaim-frame-serial-number (cdar cons))
;      (reclaim-eval-cons-macro (car cons)))
;  (reclaim-eval-list items-needing-initialization))
  (unless (access-once items-needing-initialization)
    (clear-items-needing-initialization-tree
      items-needing-initialization-tree))
  (not (atomic-exchange items-needing-initialization t)))

(def-bombout-clean-up-function 'clean-up-items-needing-initialization)


;;; note-item-needing-initialization adds its argument to
;;; note-item-needing-initialization.
;;; There is an assumption that note-item-needing-initialization is
;;; not t. This is correct when using this macro from within any
;;; activation code.

;;;It has been moved to VARIABLES for now.

;;;; Executable code for activating and deactivating any item.

;;; The following macros will be performed upon activation of any item after its
;;; activate method if any has been performed, and upon deactivation of
;;; any item before its deactivate method if any is performed. This is lieu of
;;; having a full hierarchical before, after and around facility for methods.

;;; Remember that this will be done for many items at start and reset

(def-substitution-macro activate-code-for-item (item)
  ;; Update the indexed-attribute hash-table if the item contains indexed
  ;; constant attributes.  This updates based on the initial values of the
  ;; constants.  New indexed constant values and new or initial indexed
  ;; parameter values are handled elsewhere through true-value-update.
  (when (has-indexed-attributes-p item)
    (put-parent-for-its-indexed-attributes item))

  (set-active-and-update-representations-of-status item)
  ;; Schedule invocation of rules for chaining
  (unless warmbooting?
    (schedule-task-to-invoke-existential-rules item 'is-activated)))


;;; The def-substitution-macro `deactivate-code-for-item' is called upon
;;; deactivation of an item.  It tests if an item is the member of any g2-list.
;;; If so this element (item) is removed from all g2-lists.

(def-substitution-macro deactivate-code-for-item (item)
  (unless in-suspend-resume-p
    (if (and (list-elements-for-item item)
	     ;; KB-workspaces remain in lists whether active or not.
	     (not (frame-of-class-p item 'kb-workspace)))
	(remove-element-from-all-g2-lists item t)))
  ;; When the item has registered event detectors, trigger and clear them.
  (when (registered-event-detectors item)
    (trigger-and-clear-event-detectors item))

  ;; Schedule invocation of rules for chaining
  (unless warmbooting?
    (schedule-task-to-invoke-existential-rules item 'is-deactivated)))



;;; The def-substitution-macro `remove-parent-indexed-attributes-for-item' (item)
;;; is called upon deactivation of an item.  It updates the indexed-attribute hash
;;; table if it is contained within an attribute that is indexed, or if it contains
;;; any indexed attributes itself.  This macro has been separated from
;;; deactivate-code-for-item because this needs to be called upon all items, not just
;;; active ones.

(def-substitution-macro remove-parent-indexed-attributes-for-item (item)
    ;; Update the indexed-attibute hash-table if this object is contained in an
  ;; attribute and the parent of this item is indexes this attribute.
  (let ((parent? (parent-frame item)))
    (when (and parent? (has-indexed-attributes-p parent?))
      (remove-parent-if-indexed-attribute
	(get-pretty-slot-name-for-parent-attribute-if-any item)
	(get-defining-class-for-parent-attribute-if-any item)
	item
	parent?)))
  ;; Update the indexed-attibute hash-table if this object contains attributes
  ;; that are indexed.
  (when (has-indexed-attributes-p item)
    (remove-parent-for-its-indexed-attributes item)))

  
  

;;;; Optimizing assumptions:

;;; Assuptions concerning existence of inferiors needing activation:
;;;    Only kb-workspaces have blocks placed on them needing activation.
;;;    Only kb-workspaces have connections (with possible frames in them)
;;;        needing activation.
;;;    Only entities have subworkspaces.
;;;    

;;; Assumtions concerning the nature of inferiors:
;;;    A subblock is a block. It needs activation and propagation only if it has
;;;        an activation method.
;;;    An attribute is an entity.
;;;    A subworkspace needs activation only if it is a kb-workspace.
;;;    A frame in a connection is an entity.

;;; Naming assumption:
;;;    The name of method foo for class bar is foo-for-bar. It can be called directly.

;;; Non-proliferation assumption:
;;;    Activate-if-possible-and-propagate and deactivate-and-propagate methods 
;;;    will not be written for other than kb-frame, kb-workspace and entity.




(defmacro set-active-and-update-representations-of-status (frame)
  (let ((frame-value (gensym)))
    `(let ((,frame-value ,frame))
       (set-active ,frame-value)
       (update-subscriptions-from-virtual-attribute-change
	 ,frame-value (virtual-attribute 'item-active) nil)
       (if (frame-representations ,frame-value)
	   (update-representations-of-slot-value ,frame-value 'frame-status-and-notes)))))

(defmacro set-inactive-and-update-representations-of-status (frame)
  (let ((frame-value (gensym)))
    `(let ((,frame-value ,frame))
       (set-inactive ,frame-value)
       (update-subscriptions-from-virtual-attribute-change
 	 ,frame-value (virtual-attribute 'item-active) nil)
       (if (frame-representations ,frame-value)
	   (update-representations-of-slot-value ,frame-value 'frame-status-and-notes)))))




(def-class-method activate-if-possible-and-propagate (kb-frame)
  (unless (active-p kb-frame)   
    (note-change-to-runtime-data-for-block kb-frame)
    (collecting-updates-to-sensor-attributes
      (with-activation-unit

	(clear-ancestor-not-activatable kb-frame)	     
	
	(cond
	  ((and (frame-not-bad-p kb-frame) ;jh, 8/20/91.
		(not (manually-disabled-p kb-frame)))
	   (funcall-simple-method-if-any-macro 'activate kb-frame)
	   (activate-code-for-item kb-frame)
	   ;; So far, message and entites have attributes. 13 Sept, 89
	   ;; (if (frame-of-class-p kb-frame 'message)
	   ;; More item classes are now user-extensible.  (ghw 7/12/96)
	   (propagate-simple-method-to-attributes
	     kb-frame 'activate-if-possible-and-propagate))
	  
	  ;;((frame-of-class-p kb-frame 'message)    
	  (t (propagate-simple-method-to-attributes
	       kb-frame 'deactivate-and-propagate t)))))))

;; jh, 8/20/91.  Changed the activate-if-possible-and-propagate method for
;; kb-frames to allow a status of incomplete.  This is so the "change the text of"
;; action will work on statements and statement-like items such as procedures,
;; which used to be inactive (and therefore invisible to this action) when
;; incomplete.  This is a fairly pervasive change in the meaning of the incomplete
;; status.  The KB which tests this change is in
;; ma:>jh>kb>transient-statements.kb.



(def-class-method deactivate-and-propagate (kb-frame ancestor-not-activatable?)
  (note-change-to-runtime-data-for-block kb-frame)

  (cond
    (ancestor-not-activatable?
     (set-ancestor-not-activatable kb-frame)
     (funcall-simple-method-if-any-macro
       'note-ancestor-not-activatable
       kb-frame))
    (t (clear-ancestor-not-activatable kb-frame)))

  (remove-parent-indexed-attributes-for-item kb-frame)
  (when (active-p kb-frame)
    (deactivate-code-for-item kb-frame)
    (funcall-simple-method-if-any-macro 'deactivate kb-frame)
    (set-inactive-and-update-representations-of-status kb-frame))

  ;; More kb-frame classes are user extensible now.  (ghw 7/12/96)
  ;;(if (frame-of-class-p kb-frame 'message)
  (let ((this-frame-is-not-activatable?
	  (or (ancestor-not-activatable-p kb-frame)
	      (manually-disabled-p kb-frame)
	      (frame-status kb-frame))))
    (propagate-simple-method-to-attributes
      kb-frame 'deactivate-and-propagate this-frame-is-not-activatable?)))


(def-substitution-macro activate-connection-frames-for-block (block)
  (when (connections block)		; just an opt.
    (loop for connection being the output-connections of block
	  as connection-frame-or-class = (connection-frame-or-class connection)
	  unless (symbolp connection-frame-or-class)
	    do (funcall-simple-method-macro
		 'activate-if-possible-and-propagate
		 connection-frame-or-class))))



(def-substitution-macro deactivate-connection-frames-for-block
    (block ancestor-not-activatable?)
  (when (connections block)		; opt.
    (loop for connection being the output-connections of block
	  as connection-frame-or-class = (connection-frame-or-class connection)
	  unless (symbolp connection-frame-or-class)
	    do (funcall-simple-method-macro
		 'deactivate-and-propagate connection-frame-or-class
		 ancestor-not-activatable?))))






(def-class-method activate-if-possible-and-propagate (kb-workspace)
  (unless (active-p kb-workspace)
    (note-change-to-runtime-data-for-block kb-workspace)
    (collecting-updates-to-sensor-attributes
      (with-activation-unit
	
	(clear-ancestor-not-activatable kb-workspace)
	
	(cond
	  ((and (frame-not-bad-p kb-workspace) ;jh, 8/20/91.
		(not (manually-disabled-p kb-workspace)))

	   (loop for subblock being each subblock of kb-workspace
		 with within-activate-for-kb-workspace = t
		 doing
	     (funcall-method-macro
	       'activate-if-possible-and-propagate subblock)
	     (activate-connection-frames-for-block subblock))

	   (propagate-simple-method-to-attributes
	     kb-workspace 'activate-if-possible-and-propagate)

	   ;; AFTER activating subblocks, this will schedule rules executions.
	   (activate-for-kb-workspace kb-workspace)
	   (activate-code-for-item kb-workspace))
	  
	  (t (loop for subblock being each subblock of kb-workspace doing
	       (funcall-method-macro
		 'deactivate-and-propagate subblock t)
	       (deactivate-connection-frames-for-block subblock t))
	     (propagate-simple-method-to-attributes
	       kb-workspace 'deactivate-and-propagate t)))))))


;; jh per jra, 8/21/91.  Changed the activate-if-possible-and-propagate method for
;; kb-workspaces to allow a status of incomplete.  Although kb-workspaces cannot
;; have an incomplete status currently, this will make for cleaner semantics in
;; activate-if-possible-and-propagate, and we might indeed allow kb-workspaces to
;; be incomplete someday (consider the subclass named-kb-workspace, for example).
;; For further details, see the note following the
;; activate-if-possible-and-propagate method for kb-frame.





(def-class-method deactivate-and-propagate (kb-workspace ancestor-not-activatable?)
  (note-change-to-runtime-data-for-block kb-workspace)

  (if ancestor-not-activatable?
      (set-ancestor-not-activatable kb-workspace)
      (clear-ancestor-not-activatable kb-workspace))

  (remove-parent-indexed-attributes-for-item kb-workspace)
  (when (active-p kb-workspace)
    (deactivate-code-for-item kb-workspace)
    ;; Deactivate-for-kb-workspace currently does nothing.
    (deactivate-for-kb-workspace kb-workspace)
    (set-inactive-and-update-representations-of-status kb-workspace))
  
  (let* ((this-frame-is-not-activatable?
	   (or (ancestor-not-activatable-p kb-workspace)
	       (manually-disabled-p kb-workspace)
	       (frame-status kb-workspace))))
    (loop for subblock being each subblock of kb-workspace doing
      (funcall-method-macro
	'deactivate-and-propagate subblock this-frame-is-not-activatable?)
      (deactivate-connection-frames-for-block subblock this-frame-is-not-activatable?))
    (propagate-simple-method-to-attributes
      kb-workspace 'deactivate-and-propagate this-frame-is-not-activatable?)))





(def-class-method activate-if-possible-and-propagate (entity)
  (unless (active-p entity)
    (note-change-to-runtime-data-for-block entity)
    (collecting-updates-to-sensor-attributes
      (with-activation-unit
	  (let ((subworkspace-list (subworkspaces entity)))
	    (clear-ancestor-not-activatable entity)
	    (cond
	      ((and (frame-not-bad-p entity) ;jh, 8/20/91.
		    (not (manually-disabled-p entity)))
	       (funcall-simple-method-if-any-macro 'activate entity)
	       (activate-code-for-item entity)
	       
	       (when subworkspace-list	; optimization  -jra 5/17/95
		 (cond
		   ((not (activatable-subworkspace-p entity))
		    (loop for subworkspace in subworkspace-list doing
		      (funcall-simple-method-macro
			'activate-if-possible-and-propagate subworkspace)))
		   (warmbooting?	    
		    (loop for subworkspace in subworkspace-list
			  when (workspace-was-active-p subworkspace)
			    do
			      (clear-workspace-was-active subworkspace)
			      (funcall-simple-method-macro
				'activate-if-possible-and-propagate
				subworkspace)))) )
	       
	       (propagate-simple-method-to-attributes
		 entity 'activate-if-possible-and-propagate)
	       (when (frame-of-class-p entity 'variable)
		 (let ((simulation-details (simulation-details entity)))
		   (when simulation-details
		     (activate-if-possible-and-propagate-for-kb-frame simulation-details)))))
	      
	      (t
	       (loop for subworkspace in subworkspace-list doing
		 (funcall-simple-method-macro 'deactivate-and-propagate subworkspace nil))
	       
	       (propagate-simple-method-to-attributes entity 'deactivate-and-propagate t))))))))

;; jh, 8/20/91.  Changed the activate-if-possible-and-propagate method for
;; entities to allow a status of incomplete.  For further details, see the note
;; following the activate-if-possible-and-propagate method for kb-frame.






(def-class-method deactivate-and-propagate (entity ancestor-not-activatable?)
  (note-change-to-runtime-data-for-block entity)

  (cond
    (ancestor-not-activatable?
     (set-ancestor-not-activatable entity)
     (funcall-simple-method-if-any-macro
       'note-ancestor-not-activatable
       entity))
    (t (clear-ancestor-not-activatable entity)))

  (remove-parent-indexed-attributes-for-item entity)
  (when (active-p entity)
    (deactivate-code-for-item entity)
    (funcall-simple-method-if-any-macro 'deactivate entity)
    (set-inactive-and-update-representations-of-status entity))
  
  (let ((this-frame-is-not-activatable?
	  (or (ancestor-not-activatable-p entity)
	      (manually-disabled-p entity)
	      (frame-status entity))))
    
    (loop for subworkspace in (subworkspaces entity) doing
      ;; GENSYMCID-815: G2 Abort caused by reload of the KB file.
      ;; if subworkspace is not a frame, ignore. This prevent G2 abort from some
      ;; bad KB which developed by UNDO feature.
      (when (framep subworkspace)
	(funcall-simple-method-macro
	  'deactivate-and-propagate
	  subworkspace this-frame-is-not-activatable?)))

    (when (frame-of-class-p entity 'variable)
      (let ((simulation-details (simulation-details entity)))
	;; Simulation-details can be non-nil and not a frame in one obscure
	;; case: it can be the slot init form (:funcall ...) when loading a KB
	;; and this frame is still only a forward refererence (G) element and
	;; has not yet been recreated from the KB by read-frame-for-kb.
	;; Therefore, the slightly less efficient framep check is necessary,
	;; rather than the check previously here.  This fixes a well-known bug
	;; bothering Texaco PACP (MHD 6/9/94)
	(when (framep simulation-details)
	  (deactivate-and-propagate-for-kb-frame
	    simulation-details this-frame-is-not-activatable?))))
    
    (propagate-simple-method-to-attributes
      entity 'deactivate-and-propagate this-frame-is-not-activatable?)))




;;;; Activation of entities




(def-class-method activate (entity)
  (unless (active-p entity)
    (funcall-superior-method entity)
    (unless in-suspend-resume-p
      (funcall-simple-method-if-any-macro 'activate-subclass-of-entity entity))))


;; Consider eliminating these methods and incorporating them into 
;; activate-if-possible-and-propagate and deactivate-and-propagate.



(def-class-method deactivate (entity)
  (when (active-p entity)
    (unless in-suspend-resume-p
      (decache-connection-roles entity))		;added 12aug88  -pto
    (funcall-superior-method entity) ; def-class-method deactivate (system-item)
    (unless in-suspend-resume-p
      (funcall-simple-method-if-any-macro 'deactivate-subclass-of-entity entity))))







;;;; Kb-workspace Activate and Deactivate Methods




;;; When activating a kb-workspace, search for initial rules, noting if
;;; there are any initial rules, and noting and scheduling any old initial x
;;; rules.  All old initial rules are scheduled at the highest priority,
;;; priority 1.

;;; If there are any old ones, then schedule the task to deactivate them,
;;; schedule all cyclic rules to start up after an initialization interval, and
;;; make initial-rule-count negative to inhibit the behavior for the case where
;;; there are only new initial rules.  If there are also new initial rules,
;;; schedule a task which will generate and schedule the new rule instances once
;;; everything has been activated, but pass it a flag so that it will not
;;; attempt to to schedule the scanned rules on this workspace.

;;; When there are only new initial rules, schedule a task which will generate
;;; and schedule the rule instances for these rules after everything has been
;;; activated.  Then, as each new rule instance is completed or times out, the
;;; initial-rule-count of the kb-workspace is decremented.  When it reaches
;;; 0, the scanned rules are scheduled without any initialization-period, and
;;; the initial rules are deactivated.


(def-class-method activate (kb-workspace)
  (unless in-suspend-resume-p
    (unless (active-p kb-workspace)
      (cond
	(warmbooting?
	 ;; Deactivate all initial rules before they do anything.
	 (loop for block being each subblock of kb-workspace do
	   (when (and (frame-of-class-p block 'rule)
		      (initial-rule-p block)
		      (active-p block)
		      (not (runs-while-inactive-p block)))
	     (funcall-simple-method-macro 'deactivate-and-propagate block nil))))
	
	((loop for block being each subblock of kb-workspace
	       thereis (and (frame-of-class-p block 'rule)
			    (initial-rule-p block)
			    (active-p block)))	   
	 ;; Schedule task to execute initial rules, when there are some.
	 (with-current-scheduling (nil 1 nil nil nil (nil 'reclaim-frame-serial-number))
	   (schedule-initial-rules-from-activated-kb-workspace
	     kb-workspace
	     (copy-frame-serial-number (frame-serial-number kb-workspace))
	     window-instigating-this-rule-instance?)))
	
	(t
	 ;; When there are no initial rules, schedule scanned rules.
	 (schedule-scanned-rules kb-workspace))))
    (funcall-superior-method kb-workspace)))




;;; The function `schedule-initial-rules-from-activated-kb-workspace' takes a
;;; kb-workspace and its frame serial number.  This function will generate and
;;; schedule all rule instances for the initial rules on this block and will
;;; cause the scanned rules on the block to be scheduled after all new initial
;;; rule instances have been completed.

(defun-void schedule-initial-rules-from-activated-kb-workspace
    (workspace frame-serial-number instigating-window?)
  (when (frame-has-not-been-reprocessed-p workspace frame-serial-number)
    (loop with new-rule-count fixnum = 0
	  with window-instigating-this-rule-instance? = instigating-window?
	  for block being each subblock of workspace
	  do
      (when (and (frame-of-class-p block 'rule)
		 (initial-rule-p block)
		 (active-p block)
		 (not (runs-while-inactive-p block)))
	(incff new-rule-count
	       (generate-and-schedule-rule-instances
		 block nil nil nil 'initializing nil
		 (rule-priority block) nil)))
	  finally
	      (if (=f new-rule-count 0)
		  (schedule-scanned-rules workspace)
		  (setf (initial-rule-count workspace) new-rule-count)))))


;;; For a initial rule, when it has completed or timed out, decrement initial
;;; rule count of its kb-workspace.  When this is 0, schedule the scanned rules
;;; of the kb-workspace without any initialization-period, and deactivate all
;;; the initial rules.

(defun-void handle-completion-of-initial-rule (rule-instance)
  (unless (runs-while-inactive-p (ri-rule rule-instance))
    (let* ((kb-workspace? (ri-rule-workspace? rule-instance)))
      (when kb-workspace?
	(let ((residue (decff (initial-rule-count kb-workspace?))))
	  (when (=f residue 0)
	    (with-current-scheduling (nil 1)
	      (complete-initial-rules kb-workspace?))))))))

(defun-void complete-initial-rules (kb-workspace)
  (deactivate-initial-rules kb-workspace)
  (schedule-scanned-rules kb-workspace))

(defun schedule-scanned-rules (kb-workspace)
  (loop with distribution-list = nil
	for block being each subblock of kb-workspace doing
    (when (and (frame-of-class-p block 'rule) (active-p block))
      (let ((scan-interval (rule-scan-interval block)))
	(when scan-interval
	  (setq scan-interval
		(maxf
		  (if (fixnump scan-interval)
		      scan-interval
		      (floore-first (managed-float-value scan-interval)))
		  1))
	  ;; The following presumes that EQ works for fixnums, which it always
	  ;; will for G2 code since we require immediate fixnums.  -jra 12/6/96
	  (let ((sublist (assq scan-interval distribution-list)))
	    (cond
	      (sublist (setf (cdr sublist) (gensym-cons block (cdr sublist))))
	      (t (setq distribution-list
		       (gensym-cons
			 (gensym-list scan-interval block)
			 distribution-list))))))))
	finally
	  (loop for (floored-scan-interval . rules) in distribution-list
		for how-many = (length rules) doing
	    (loop for rule in rules
		  for scan-interval = (rule-scan-interval rule)
		  for k from 0 doing
	      (with-future-scheduling
		  ((rule-scan-task? rule) (rule-priority rule)
		   (g2-future-interval
		     (floorf-positive (*f k floored-scan-interval) how-many))
		   (if (fixnump scan-interval)
		       (coerce-fixnum-to-gensym-float scan-interval)
		       (managed-float-value scan-interval))
		   nil
		   (runs-while-inactive-p rule))
		(invoke-rule-universally rule))))
	  (reclaim-gensym-tree distribution-list)))

(defun deactivate-initial-rules (kb-workspace)
  (loop for block being each subblock of kb-workspace do
    (when (and (initial-rule-p block)
	       (active-p block)
	       (not (runs-while-inactive-p block)))
      (funcall-simple-method-macro 'deactivate-and-propagate block nil))))


(def-class-method deactivate (kb-workspace)
  (funcall-superior-method kb-workspace)
;  (declare (ignore kb-workspace))
  nil)



;;; `schedule-all-cyclic-rules' is called by warmboot to activate all cyclic
;;; rules in the kb, including those on activatable subworkspaces that are
;;; presently active. Following the order of the activate mechanism generally,
;;; it works from the bottom up.

(defun schedule-all-cyclic-rules ()
  (loop for ws being each class-instance of 'kb-workspace
	when (and (active-p ws) (null (superblock? ws)))
	  do (schedule-all-cyclic-rules-1 ws)))



(defun schedule-all-cyclic-rules-1 (kb-workspace)
  (loop for subblock being each subblock of kb-workspace
	for subworkspace? =
	    (if (and (active-p subblock)
		     (frame-of-class-p subblock 'entity))
		(car (subworkspaces subblock))) doing
    (when (and subworkspace? (active-p subworkspace?))
      (schedule-all-cyclic-rules-1 subworkspace?)))

  (schedule-scanned-rules kb-workspace))

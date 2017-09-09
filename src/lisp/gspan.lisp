;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GSPAN

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andreas Hofmann


;; To Do


;; Make send-all-input-values-to-external-simulator suspendable.

;; Prevent creation and deletion of external-simulation-definitions while
;; running (check with Mark about how to do this).  Currently, editing an
;; external-simulation-definition while running is checked by the function
;; ok-to-edit-external-simulation-definition?.

;; Write overall spec on simulation installation for 1.2.  The current
;; mechanism for GSPAN is a good model to follow.

;; When merging kbs, if in wrong order (if gspan kb is not loaded last)
;; the external-simulation-configuration slot will not be put in.  This
;; is due to the rules of merging kbs.  Put up error warning message?
;; Eventually, need interface objects similar to ones in GSI so that
;; several external simulator processes can be run.

;; Handle errors in handler for begin-simulation-output-vector-for-object
;; (see code) (see also receive-value-for-gsi-sensor in GSI).

;; Purge ca:/usr/agh/xsim and quincy:[dataservers.source.xsim] when done
;; with C file re-configuration.

;; Installation problem? - cloned object, cloned external simulation definition,
;; can't seem to disable object.

;; Test for memory leaks.
;; Boxed numbers coming back from external simulator.  Are these within a 
;; temporary context?  Review.

;; Need to reclaim external-simulation-object structures.  These correspond 
;; to G2-sensors in GSI which are reclaimed by the def-capability deactivator.

;; Set up mechanism so that errors on C side can be reported back to G2 side.
;; GSI has this feature.

;; In GSI, grammar for gsi-host-configuration should not be compiler
;; switched since it may be desireable to develop kbs on machines other
;; than the ones on which they are run.  Use slot value compiler to check.
;; Talk to Brian.

;; Take integration algorithm out of simulation parameters slot for 1.11
;; versions.

;; In run_one_simulation_cycle (in xs_main.c), key_fill_ptr and in_fill_ptr
;; are not being passed to user function.

;; Put make-icp-connection... into GSI-COMMON, at least in ab.

;; Put disclaimer into C source files that are distributed.

;; GSPAN sounds like CSPAN, the cable news network.  Need to do a product
;; name search to make sure that this is OK.

;; Add to documentation the user functions for initialize, shutdown,
;; pause, and resume.

;; Deleting simulation subtable for externally simulated variable causes
;; "no simulation formula yet" to be printed in the simulation details
;; slot.

;; Problem passing float 0 over ICP.  Also, pass integers as well as floats?
;; There seems to be a problem with the floating point format in ICP in general.
;; Besides having difficulty with 0, the log format can cause precision
;; problems.
;; The short term solution is to modify wr_icp_float in gsi_icp.c when
;; compiling for GSPAN so that a small amount is added to 0 before it
;; is sent.  This is necessary because GSPAN currently only deals with
;; floats.  Switch to icp parameter mechanism so that the current 
;; mechanism used for GSI will work.  The ultimate solution, however, is to
;; fix the floating point format for ICP.

;; Need to check in G2 whether maximum numbers of args and maximum sizes have
;; been exceeded.  See xs_definitions.h

;; Improve error message in external-simulator-input-values-ok? since it is 
;; easy for mistakes to occur.  Indicate the number of the arg that failed.
;; Improve error messages for output side as well.

;; For 1.2, really need to review variable installation for simulator.
;; Change variable frame and consolidate installation slots.  Save
;; only what is absolutely necessary.  Coordinate with Jim.

;; On VAX in [dataservers.source.xsim], delete gsi_ext_cpp1.c, 
;; gsi_ext_cpp2.c, xs_ext_ipp.c, xs_example2.c.  These are by products of
;; Bjorn's visit.

;; Write up complete procedures for running external simulator on
;; VAX and SUN.  Start from handwritten notes and put them onto MAC file.

;; In the C function wr_icp_float (in "ma:>agh>gsi_icp_func.c"), a check
;; is made for 0 and it is converted into a very small float.  This is
;; necessary because float is the ICP type expected by the handler on
;; the G2 side.  Consider generalizing to allow other types.  GSI uses
;; more complicated types.

;; Prevent runtime edits of external simulation definition by putting
;; checks into slot putters (easy).

;; Installation errors.  Need to implement frame notes and warning notes.
;; The other slot putters have to be set up.

;; Handling editing changes while running.
;; Handle-updates-to-externally-simulated-entities.

;; Runtime and network errors.
;; Finish documentation in section Error Conditions and How they are Handled.
;; Also document error handlers where they are located.

;; Keywords
;; The grammar for keywords currently allows only fixed strings.
;; It is desireable to have the strings be set by the inference engine somehow 
;; rather than being fixed.  There are several approaches for this:
;; 1.  Have inference engine change slots containing strings
;;     (need change action),
;; 2.  Keep string variables in slots
;;     (requires datum-evaluate to be called from simulator),
;; 3.  Implement string variables for simulator and input values from
;;     inference engine via set action.
;; For the second and third approach, the grammar type for the message-keywords
;; slot must be attribute-designations.  I think the first approach is the best.
;; Hold off for now until this is available, especially since keywords are not
;; absolutely necessary.

;; Send resume and pause ICP messages.

;; Search for ! for other to do.

;; Need to integrate with installation for rest of simulator, for both 1.11 and
;; 1.2


;; Low Priority

;; Review whether frame status of external simulation definition should be
;; incomplete if output vector slot is empty.  It probably shouldn't.

;; Currently, initialize-externally-simulated-variable calls
;; set-up-update-timing-for-variable for externally simulated variables.
;; This is somewhat inappropriate since update is object and not variable
;; oriented The only reason this is done is so that 
;; begin-collecting-data-for-simulator won't bomb out in 
;; variable-to-be-updated-this-cycle?.  
;; See work-on-external-simulator-tasks for details on deciding whether to
;; execute an external simulation cycle).

;; Currently, a warning message (see simulate-one-cycle,
;; warn-of-loss-of-connection-to-external-simulator) is posted if the connection
;; to the external simulator is broken.  This does not, however, check for the
;; case where the connection is not broken but the external simulator is
;; (external simulator is in an infinite loop for example).  Consider implementing
;; some sort of timeout check in simulate-one-cycle to post warning messages
;; if the external simulator takes too long.

;; Consider caching vector designations (not a high priority).

;; Consider implementing mechanism where G2 side can send vectors for more
;; than one object in a message group.  This would make the C side more
;; complicated.

;; Consider making the external-simulation-definition-for-entity slot 
;; visible to the user in the table.  This would indicate to the user
;; that the object is simulated externally.

;; Connections and objects are both entities.  Should we have a subclass of
;; entity that includes both but nothing else?

;; Longer range - send messages indicating connectivity of objects.

;; Have a message type that allows many objects to be sent at once.
;; Or, have message type that indicates that all objects have been sent.
;; External process C code would store object values as they come in but
;; would not do any actual simulation until they are all in.  This will
;; probably become the normal mode of running.




;;;; Overview



;;;; Special Variables





;;;; External Simulation Definition


(def-class (external-simulation-definition
	     (item entity) (foundation-class external-simulation-definition)
	     define-predicate)
  (frame-author-or-authors nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))

  ;; initial setup of frame-status-and-notes now done in the initialize method
;  (frame-status-and-notes
;    (:funcall slot-value-cons-function incomplete nil))

  (icon-description
    (:funcall-at-load-time
      create-icon-description
      100 100 
      ((outline (0 0) (100 0) (100 100) (0 100))
; doesn't scale on right edge! (MHD 8/4/89)
;       (outline (1 1) (99 1) (99 99) (1 99))
       (lines (20 20) (50 80))
       (lines (50 20) (20 80))
       (lines (82 25) (arc (58 35)) (70 50) (arc (82 65)) (58 75)))
      nil
      ;; later, maybe redo the icon in order to be able to eliminate
      ;;   the magnification; the goal is to have this be the same size
      ;;   as most other system icons (e.g. variables), 60 X 60, but
      ;;   we decided to do this after the icon was already designed
      ;;   for 100 X 100. (MHD 8/4/89)
      #.(convert-to-magnification-at-compile-time 3/5)
      #.(convert-to-magnification-at-compile-time 3/5)
      ))

  (name-or-names-for-frame		  ; gets filled in per name-of-defined-class
    nil do-not-save do-not-put-in-attribute-tables)

  (class-of-object-computed-by-this
    nil vector-slot system user-overridable (type new-class))

  (message-keywords
    nil vector-slot system (type keyword-strings-or-none text))

  (input-vector-to-external-simulator
    nil vector-slot system (type attribute-designations-or-none text))

  (output-vector-from-external-simulator
    nil vector-slot system (type attribute-designations text))

  (initialization-vector-for-external-simulator
    nil vector-slot system (type attribute-designations-or-none text)))

;; Allow constant designations as well as attribute designations (variable names,
;; numbers).  Allow attribute designations as well as strings.

;; Class-of-object-computed-by-this shouldn't just be of type new-class.
;; Should also allow existing class names and put up menus!




(def-system-variable proceed-with-edit GSPAN nil)



(def-kb-specific-property-name external-simulation-definitions-for-attribute)

;; The property external-simulation-definitions-for-attribute is like 
;; generic-simulation-formulas-for-this-role.


(def-kb-specific-property-name external-simulation-definition-for-class)

;; The property external-simulation-definition-for-class is like 
;; generic-simulation-formulas-for-this-role except that it is a property on an
;; object's class rather than on an attribute name.  It is used, for example,
;; to find a newly created object's external simulation definition, if it has
;; one.


;;;; Grammar for Slots of External Simulation Definition

(add-grammar-rules
  '((attribute-designations attribute-designation)
    (attribute-designations
      (attribute-designation '\, attribute-designations) (2 1 3)
      simplify-associative-operation)
    (attribute-designations-or-none attribute-designations)
    (attribute-designations-or-none 'none)
    (attribute-designation
      ('the attribute-name 'of 'the class) (1 2 (4 5)))
    (attribute-designation
      ('the attribute-name 'of attribute-designation) (1 2 4))
    
    (keyword-strings-or-none keyword-strings)
    (keyword-strings-or-none 'none)
    (keyword-strings keyword-string)
    (keyword-strings
      (keyword-string '\, keyword-string) (2 1 3)
      simplify-associative-operation)
    (keyword-string whole-string)
    ))

;; There should be no need to compile attribute designations since they are
;; so simple.



(def-slot-value-writer-as-existing-function
  attribute-designations-or-none
  write-symbol-from-slot)

(def-slot-value-writer-as-existing-function
  keyword-strings-or-none
  write-symbol-from-slot)

;; The above writers are expected to only be called when the slot is nil;
;; otherwise, the slot would be text, and there would be no need to call a
;; writer.  (MHD 3/7/91)



;;; The following grammar rules are similar to or identical to ones in GSI.
;;; The grammar type xsi-host-configuration is used for the external simulator
;;; interface as opposed to gsi-host-configuration which is used for GSI.
;;; This duplication is necessary to allow for G2's with the external simulator
;;; interface but without GSI.

(add-grammar-rules
  '((host-name unreserved-symbol)
    (network-task-name unreserved-symbol)
    (tcp-ip-port-number integer)
    (file-pathname whole-string)
    (host-name-string whole-string)

    (xsi-host-configuration ('tcp-ip 'host host-name-string
			     'port-number tcp-ip-port-number)
			    (tcp-ip 3 5))


    (xsi-host-configuration ('spawned 'vms 'process file-pathname)
                           (vms-process 4))
    (xsi-host-configuration 'none)))







;;;; Slot Putters and Installation Functions for External Simulation Definition

;;; In order for an external-simulation-definition to be complete, the
;;; slots class-of-object-computed-by-this and
;;; output-vector-from-external-simulator must be non-nil.  Typically,
;;; the slots initialization-vector-for-external-simulator
;;; and input-vector-to-external-simulator should also be non-nil.

;;; The slot putters for all slots that contain attribute designations
;;; check to make sure that the class in the designation matches
;;; the one in the class-of-object-computed-by-this slot.  If not, the
;;; frame status becomes bad and a frame note is put up.

;;; The basic procedure for slot putters for external simulation definitions
;;; is as follows:
;;;   1.  temporarily save frame status and contents of slot,
;;;   2.  set slot, update frame status
;;;   3.  forward install or deinstall according to following rules:

;;;       old frame status   new frame status    installation
;;;       ----------------   ----------------    ------------
;;;       not ok             not ok              do nothing
;;;       ok                 not ok              completely deinstall
;;;       not ok             ok                  completely install
;;;       ok                 ok                  incremental deinstall and install

;;; Note that if initializing, there is no need to deinstall anything.
;;; In the case where both the old and new frame status are ok, it is only
;;; necessary to do anything if the slot is output-vector-from-external-simulator.
;;; In this case, a complete deinstall and install could be done but an
;;; incremental deinstall and install, based only on designations that have
;;; changed, is more efficient.

;;; There are two basic kinds of installation:  forward and inverse.
;;; As is defined in previous documents, forward installation involves
;;; beginning with a simulation behavior specification and finding all
;;; variables which it describes, while inverse installation involves
;;; beginning with a variable and finding the (usually one) describing
;;; behavior specification.  Installation for external simulation has
;;; the additional wrinkle that parent entities, as well as variables
;;; are installed.  Installing a new entity involves finding variables
;;; in the entity and its sub-objects.  This is a forward installation
;;; from the standpoint of the variables.


;; This general approach should be used for simulation installation in
;; general.

;; Slot putters still need work - updating frame status, installing or 
;; deinstalling when frame status changes!

;; Consider putting up frame note if the slots 
;; initialization-vector-for-external-simulator and
;; input-vector-to-external-simulator are nil.  These are not, however,
;; required to be non-nil in order for frame status to be ok!



(defun ok-to-edit-external-simulation-definition? ()
  (cond
    ((or system-is-running system-has-paused)
     ;; if we're going to do it anyhow don't complain
     (unless proceed-with-edit
       (warning-message 2
	   "An external-simulation-definition may not be edited while the system is running or paused.  Please reset before editing an external-simulation-definition."))
     proceed-with-edit)
    (t t)))


(def-slot-putter class-of-object-computed-by-this
		 (external-simulation-definition class initializing?)
  (when (ok-to-edit-external-simulation-definition?)
    (let ((old-slot-value
	    (when (not initializing?)
	      (class-of-object-computed-by-this external-simulation-definition))))
      (setf (class-of-object-computed-by-this external-simulation-definition)
	    class)
      (if class
	  (setf (external-simulation-definition-for-class class)
		external-simulation-definition)
	  (setf (external-simulation-definition-for-class old-slot-value)
		nil)))))

;; If another external-simulation-definition exists for the same class,
;; status should be bad!  If class is null, frame status should be
;; incomplete!

;(def-slot-putter class-of-object-computed-by-this
;		 (external-simulation-definition class)
;  (setf (class-of-object-computed-by-this external-simulation-definition)
;	class)
;  (cond
;    (class
;     (if (output-vector-from-external-simulator external-simulation-definition)
;	 (update-frame-status external-simulation-definition nil nil)))
;    (t
;     (update-frame-status external-simulation-definition 'incomplete nil)))
;  ;; Need to check if already a definition for this class.
;  ;; Need to set names slot.
;  )


(def-slot-putter input-vector-to-external-simulator
		 (external-simulation-definition input-vector)
  (when (ok-to-edit-external-simulation-definition?)
    (setf (input-vector-to-external-simulator external-simulation-definition)
	  input-vector)
    ;; Will get more sophisticated.
    ;; Check to make sure class names of designations match 
    ;; class-of-object-computed-by-this.
    ))


(def-slot-putter message-keywords
		 (external-simulation-definition message-keywords)
  (when (ok-to-edit-external-simulation-definition?)
    (setf (message-keywords external-simulation-definition)
	  message-keywords)
    ;; Will get more sophisticated.
    ;; Check to make sure class names of designations match 
    ;; class-of-object-computed-by-this.
    ))


(def-slot-putter initialization-vector-for-external-simulator
		 (external-simulation-definition initialization-vector)
  (when (ok-to-edit-external-simulation-definition?)
    (setf (initialization-vector-for-external-simulator
	    external-simulation-definition)
	  initialization-vector)
    ;; Will get more sophisticated.
    ;; Check to make sure class names of designations match 
    ;; class-of-object-computed-by-this.
    ))


(def-slot-putter output-vector-from-external-simulator
		 (external-simulation-definition output-vector initializing?)
  (when (ok-to-edit-external-simulation-definition?)
    (let ((old-frame-status-ok? nil) 
	  new-frame-status-ok?
	  (old-slot-value nil)
	  (class-of-object 
	    (class-of-object-computed-by-this external-simulation-definition))
	  (designations-to-remove nil)
	  (designations-to-add nil))
      
      (when (not initializing?)
	(setq old-frame-status-ok? (frame-ok-p external-simulation-definition)
	      old-slot-value 
	      (output-vector-from-external-simulator
		external-simulation-definition)))
      
      (setf (output-vector-from-external-simulator external-simulation-definition)
	    output-vector)
      
      ;; Forward installation.
      (when (not initializing?)
	;; The initializing case is taken care of by the initialize method
	;; for external-simulation-definition and by the install-external-simulation
	;; post loading function.
	
	(cond
	  (output-vector
	   (if (class-of-object-computed-by-this external-simulation-definition)
	       (update-frame-status external-simulation-definition nil nil)))
	  (t
	   (update-frame-status external-simulation-definition 'incomplete nil)))
      
	(setq new-frame-status-ok? 
	      (and (frame-ok-p external-simulation-definition)
		   (not (frame-being-deleted-p external-simulation-definition))))
	
	(cond
	  ((and old-frame-status-ok? new-frame-status-ok?)
	   (setq designations-to-remove
		 (get-missing-designations
		   (car old-slot-value)
		   (car output-vector))
		 designations-to-add
		 (get-missing-designations
		   (car output-vector)
		   (car old-slot-value)))
	   ;; incremental forward deinstall
	   (when designations-to-remove
	     (forward-external-simulation-install
	       external-simulation-definition 
	       class-of-object designations-to-remove t t))
	   ;; incremental forward install
	   (when designations-to-add
	     (forward-external-simulation-install
	       external-simulation-definition 
	       class-of-object designations-to-add nil t)))
	  (old-frame-status-ok?			; and (null new-frame-status-ok?)
	   (setq designations-to-remove
		 (get-attribute-designations (car old-slot-value)))
	   (forward-external-simulation-install
	     external-simulation-definition 
	     class-of-object designations-to-remove t nil))
	  (new-frame-status-ok?			; and (null old-frame-status-ok?)
	   (setq designations-to-add
		 (get-attribute-designations (car output-vector)))
	   (forward-external-simulation-install
	     external-simulation-definition 
	     class-of-object designations-to-add nil nil)))
	
	(reclaim-simulate-list designations-to-remove)
	(reclaim-simulate-list designations-to-add))
      
      ;; Check to make sure class names of designations match 
      ;; class-of-object-computed-by-this!  If not, frame status 
      ;; should be bad.
      )))

;; ALL OF THESE PUTTERS FAIL TO RETURN THEIR SLOT'S FINAL VALUES!  Check
;; into this later! (MHD 7/18/94)

;; I believe that no-one ever uses the value returned by
;; a slot-putter. All clients of def-slot-putter get hold
;; of the slot putter by calling
;; get-slot-description-putter-if-any
;; which calls get-slot-putter-if-any, which
;; gets the slot-putter. The callers of get-slot-description-putter-if-any
;; are initialize-slot-description-value, which returns the
;; value returned by the slot-putter, but I believe this value
;; is ultimately never used, and
;; change-slot-description-value-without-updating-representations and
;; tw-change-slot-description-value, which only use the second
;; value returned by the slot-putter.

;; So the right thing to do would be to change the protocol so that
;; def-slot-putter only returns one value, do-not-reclaim-old-value?,
;; but that would involve modifying all existing slot-putters.
;; Not today. -alatto, 1/15/03






;;; The initialize method for external-simulation-definition ...

(def-class-method initialize (external-simulation-definition)
  (funcall-superior-method external-simulation-definition)
  (update-frame-status
    external-simulation-definition
    (if (and (output-vector-from-external-simulator external-simulation-definition)
	     (class-of-object-computed-by-this external-simulation-definition))
	nil
	'incomplete)
    nil)
  (install-new-external-simulation-definition external-simulation-definition))

;; Decide whether frame is OK here, rather than in the putters when initializing
;; slots during a clone, or as a computed init form, for the make-frame case.
;; (MHD 7/19/94)

;; Added documentation stub above, moved initialize method for entity to
;; ENTITIES, changed name from frame-initialization-method to initialize
;; per change in spec.



;;; The cleanup method for external-simulation-definition changes the
;;; output-vector-from-external-simulator slot to nil so the slot putter 
;;; will be invoked to deinstall things.  It then changes the 
;;; class-of-object-computed-by-this slot to nil to do further deinstallation
;;; (see slot putters).

(def-class-method cleanup (external-simulation-definition)
  (funcall-superior-method external-simulation-definition)
  (let ((proceed-with-edit t))
    (change-slot-value external-simulation-definition 
		       'output-vector-from-external-simulator nil)
    ;; This will deinstall affected entities and variables.
    
    (change-slot-value external-simulation-definition 
		       'class-of-object-computed-by-this nil)))



;;; Install-external-simulation-1 is called from the post loading function
;;; install-external-simulation.

(defun install-external-simulation-1 ()
  (loop for definition 
	    being each class-instance of 'external-simulation-definition			   
	do (install-new-external-simulation-definition definition)))



;;; Install-new-external-simulation-definition is used to forward install when
;;; the external simulation definition is created, cloned, or loaded.  The slot
;;; putters do not do forward installation in these cases (see slot putter for
;;; output-vector-from-external-simulator).

(defun install-new-external-simulation-definition 
       (new-external-simulation-definition)
  (when (frame-ok-p new-external-simulation-definition)
    ;; Slot putters may set status to not "ok" (if, for example, the
    ;; class-of-object-computed-by-this slot is empty) before this is called.
    (let ((designations-to-add
	    (get-attribute-designations 
	      (car (output-vector-from-external-simulator
		     new-external-simulation-definition))))
	  (class-for-new-external-simulation-definition
	    (class-of-object-computed-by-this new-external-simulation-definition)))
      ;; Install.
      (when class-for-new-external-simulation-definition
	(forward-external-simulation-install
	  new-external-simulation-definition
	  class-for-new-external-simulation-definition
	  designations-to-add nil nil))
      (reclaim-simulate-list designations-to-add))))




;;; Install-externally-simulated-entity finds the most specific 
;;; external-simulation-definition applicable and uses it to call 
;;; install-externally-simulated-entity-1.

(defun install-externally-simulated-entity 
       (entity &optional 
	external-simulation-definition-being-edited? designations?
	deinstall? incremental?)
  (loop	for class
	    in (class-inheritance-path
		 (class-description-slot entity))
	as external-simulation-definition?
	   = (external-simulation-definition-for-class class)
	do
    (when (and external-simulation-definition?
	       (frame-ok-p external-simulation-definition?)
	       (not (frame-being-deleted-p external-simulation-definition?)))
      (if external-simulation-definition-being-edited?
	  (when (eq external-simulation-definition-being-edited?
		    external-simulation-definition?)
	    ;; Install if the external simulation definition being
	    ;; edited is also the most specific.
	    (install-externally-simulated-entity-1
	      entity external-simulation-definition? class designations?
	      deinstall? incremental?))
	  (let ((designations
		  (get-attribute-designations 
		    (car (output-vector-from-external-simulator 
			   external-simulation-definition?)))))
	    (install-externally-simulated-entity-1
	      entity external-simulation-definition? class designations
	      deinstall? incremental?)
	    (reclaim-simulate-list designations)))
      (return (values)))))



(defun install-externally-simulated-entity-1 
       (entity external-simulation-definition class 
	designations deinstall? incremental?)
  (cond 
    ((external-simulation-p entity)
     (loop with alist = (simulate-list (simulate-cons class entity))
	   with *current-computation-frame* = external-simulation-definition
	   with current-computation-flags = current-computation-flags
	   initially (setf (role-serve-inactive-objects?) t)
	   for designation in designations
	   as output-variable?
	      = (evaluate-designation designation alist)
	   do
       (when (of-class-p output-variable? 'variable-or-parameter)
	 (install-externally-simulated-variable-1
	   output-variable? external-simulation-definition deinstall?))
       ;; Consider posting warning for designations that don't designate
       ;; a variable!
	   finally (reclaim-simulate-tree alist))
     (when (not incremental?)
       (cond 
	 (deinstall?
	  (set-slot-value entity 'external-simulation-definition-for-entity nil)
	  (with-current-model-for-item entity
	    (remove-externally-simulated-entity-from-simulation-model entity)))
	 (t
	  (set-slot-value entity 'external-simulation-definition-for-entity
			  external-simulation-definition)
	  (make-external-set-pointers-if-necessary entity)
	  (with-current-model-for-item entity
	    (add-externally-simulated-entity-to-simulation-model entity))))))
    (t
     ;; Post warning message if entity does not have external simulation
     ;; capability.  Consider posting a frame note (much more complicated).

     (warning-message 2
       "The object ~NF does not have an external simulation capability.  If this is ~
        desired, add the external-simulation capability to the capabilities-and-~
        restrictions attribute of ~a, the object definition for this object's class."
       entity
       (class entity))
     ;; the following had problems: (1) illegal linebreak characters in the
     ;; string; (2) referred to entity, which is not in the user model; (3)
     ;; referred to an "object definition for the entity" instead of for it's
     ;; class; (4) referred to capabilities-and-restrictions slot, literally,
     ;; which is obsolete (for 4.0 -- a new problem, in other words); (5) reference
     ;; here to the slot capabilities-and-restrictions should have hyphens here
     ;; (but the reference is obsolete, so it doesn't matter).
     ;;
     ;; I have tried to just solve all of the problems except for (4) at this time.
     ;; Other messages that acknowledge the existence of capabilities in the user
     ;; model may need to change. (MHD 9/28/93)

     ;;     (warning-message 2
     ;;       "The entity ~NF does not have external simulation capability.  If this is
     ;;desired, add the external-simulation capability to the capabilities and
     ;;restrictions in the object definition for the entity."
     ;;       entity)
     )))




;;; Forward-external-simulation-install updates the
;;; external-simulation-definitions-for-attribute properties and then loops
;;; through all entities that are a subclass of class and installs each one by
;;; calling install-externally-simulated-entity.  If deinstall? is t, the entity
;;; is first deinstalled.

(defun forward-external-simulation-install
       (external-simulation-definition class designations deinstall? incremental?)

  ;; Update external-simulation-definitions-for-attribute property.
  (loop for designation in designations 
	as attribute = (get-attribute-of-attribute-designation designation)
	do
    (if deinstall?
	(delete-from-set
	  (external-simulation-definitions-for-attribute attribute)
	  external-simulation-definition simulate)
	(add-to-set
	  (external-simulation-definitions-for-attribute attribute)
	  external-simulation-definition simulate)))

  ;; Install variables and entities.
  (cond
    (incremental?
     (loop for entity being each class-instance of class
	   do (install-externally-simulated-entity
		entity external-simulation-definition designations 
		deinstall? incremental?)))
    (deinstall?  ; and (not incremental?)
     (loop for entity being each class-instance of class
	   do
       (install-externally-simulated-entity-1
	 entity external-simulation-definition class 
	 designations deinstall? incremental?)
       (install-externally-simulated-entity entity)))
    (t   ; install and (not incremental?)

     ;; Deinstall entities that will be simulated by
     ;; external-simulation-definition.  Note that the 
     ;; external-simulation-definition-for-class property must be 
     ;; temporarily set to nil so that install-externally-simulated-entity
     ;; will be deinstalled properly.
     (setf (external-simulation-definition-for-class class) nil)
     (loop for super-class
	       in (cdr (class-inheritance-path
			 (class-description class)))
	   as external-simulation-definition?
	      = (external-simulation-definition-for-class super-class)
	   do
       (when (and external-simulation-definition?
		  (frame-ok-p external-simulation-definition?))
	 ;; This external simulation definition is used for all classes
	 ;; and subclasses of class
	 ;; that don't have their own, more specific external simulation definition.
	 ;; Instances of such classes must be deinstalled before the new
	 ;; external simulation definition is installed.
	 (let ((super-class-designations
		 (get-attribute-designations 
		   (car (output-vector-from-external-simulator 
			  external-simulation-definition?)))))
	   (loop for entity being each class-instance of class
		 do
	     (install-externally-simulated-entity
	       entity external-simulation-definition? 
	       super-class-designations t nil))
	    (reclaim-simulate-list super-class-designations))
	 (return (values))))
     (setf (external-simulation-definition-for-class class)
	   external-simulation-definition)

     (loop for entity being each class-instance of class
	   do (install-externally-simulated-entity
		entity external-simulation-definition designations 
		deinstall? incremental?)))))

;; Class is passed as an arg so that if the class-of-object-computed-by-this
;; is changed to something different from what is in the designation (resulting
;; in the frame status becoming bad), the old class, for which the frame status
;; was good, can be used to deinstall.


;;; Get-class-of-attribute-designation ...

(defun get-class-of-attribute-designation (attribute-designation)
  (if (null (third attribute-designation))
      (second attribute-designation)
      (get-class-of-attribute-designation (third attribute-designation))))


;;; Get-attribute-of-attribute-designation ...

(defun get-attribute-of-attribute-designation (attribute-designation)
  (second attribute-designation))
;; May have to get more complicated.
;; Consider implementing attribute-designation-p.


;;; Get-missing-designations returns a simulate list of designations which
;;; appear in the first argument but not in the second.

(defun get-missing-designations
       (first-designation-or-designations second-designation-or-designations)
  (let ((missing-designations nil))
    (cond
      ((more-than-one-designation-in-vector-p first-designation-or-designations)
       (loop for designation in (cdr first-designation-or-designations)
	     do
	 (cond
	   ((more-than-one-designation-in-vector-p 
	      second-designation-or-designations)
	    (when (not (member 
			 designation second-designation-or-designations
			 :test #'equal))
	      (setq missing-designations
		    (simulate-cons designation missing-designations))))
	   ((at-least-one-designation-in-vector-p
	      second-designation-or-designations)
	    (when (not (equal designation second-designation-or-designations))
	      (setq missing-designations
		    (simulate-cons designation missing-designations))))
	   (t (setq missing-designations
		    (simulate-cons designation missing-designations))))))
      ((at-least-one-designation-in-vector-p first-designation-or-designations)
       (cond
	 ((more-than-one-designation-in-vector-p 
	    second-designation-or-designations)
	  (when (not (member first-designation-or-designations
			     second-designation-or-designations
			     :test #'equal))
	    (setq missing-designations
		  (simulate-cons first-designation-or-designations
				 missing-designations))))
	 ((at-least-one-designation-in-vector-p
	    second-designation-or-designations)
	  (when (not (equal first-designation-or-designations
			    second-designation-or-designations))
	    (setq missing-designations
		  (simulate-cons first-designation-or-designations
				 missing-designations))))
	 (t (setq missing-designations
		  (simulate-cons first-designation-or-designations
				 missing-designations))))))
    missing-designations))


;;; Get-attribute-designations returns a simulate list of designations, 
;;; regardless of whether there is one or more.

(defun get-attribute-designations (designation-or-designations)
  (cond
    ((more-than-one-designation-in-vector-p designation-or-designations)
     (copy-list-using-simulate-conses (cdr designation-or-designations)))
    ((at-least-one-designation-in-vector-p designation-or-designations)
     (simulate-list designation-or-designations))))




;;;; Externally Simulated Variable Installation


;;; Install-externally-simulated-variable is called by put-attribute-value to
;;; perform an inverse installation for the variable.  This is much more
;;; efficient than the brute force approach of doing an entire forward
;;; installation. 

(defun install-externally-simulated-variable (variable)
  (let ((external-simulation-definitions-for-variable?
	  (find-external-simulation-definitions-for-variable-if-any variable)))
    (if external-simulation-definitions-for-variable?
	(loop for definition in external-simulation-definitions-for-variable?
	      do
	  (install-externally-simulated-variable-1 variable definition nil)
	      finally (reclaim-simulate-list 
			external-simulation-definitions-for-variable?))
	(install-externally-simulated-variable-1 variable nil nil))))


;;; Find-external-simulation-definitions-for-variable-if-any searches for
;;; external-simulation-definitions which compute values for variable.  It does
;;; this by searching up the subobject tree.  For each entity that has an
;;; external simulation definition which designates the variable (in the
;;; output-vector-from-external-simulator slot), the external simulation
;;; definition is collected.  Nil will be returned if none are found.  Because
;;; sub-objects in attributes of objects always form a tree and never a network,
;;; the only case where there can be more than one is when the object
;;; corresponding to the class in one definition is a sub-object of the object
;;; corresponding to the class in another other definition.  This is the only
;;; case where designations from different external simulation definitions can
;;; refer to the same variable and it is flagged as an error.  (see Error
;;; Conditions and How they are Handled section below).  A frame note is put on
;;; the variable and it is not simulated.  This does not, however, prevent the
;;; parent object from being simulated externally.

;;; Note that although only one external simulation definition is allowed per
;;; object and only one external simulation definition is allowed per variable,
;;; it is possible for an object to have variables simulated via different
;;; external simulation definitions.  This is actually a useful feature as is
;;; illustrated by the following example.  Suppose a distillation column is
;;; modelled as an object with trays as sub-objects and suppose that they are
;;; all simulated externally.  Suppose, further, that the distillation column
;;; model provides an input to the tray model.  The external simulation
;;; definition for the distillation column would designate variables in the
;;; trays in its output vector slot.  The external simulation definition for the
;;; trays would designate these same variables in its input vector slot and
;;; designate other tray variables in its output vector slot.  Thus, the trays
;;; have variables designated in output vectors of two different external
;;; simulation definitions.  Note, however, that there is only one external
;;; simulation definition for the distillation column, the trays, and any 
;;; variable in the model.  It is important to remember here that this is
;;; object oriented and that the external simulation definitions apply first
;;; to objects and only indirectly to the variables.

;; Note how limiting designations in vector slots of
;; external-simulation-definitions to attribute-designations greatly simplifies
;; installation.  Things would be much more complicated if, for example,
;; connection roles were allowed since it would then be possible for many
;; external-simulation-definitions to designate the same variable in a manner
;; which makes it difficult to decide which is the most appropriate.  This will
;; be an issue if generic-simulation-formulas are extended to allow the left
;; sides to be any kind of designation.

(defun find-external-simulation-definitions-for-variable-if-any (variable)
  (multiple-value-bind
    (parent-entity? parent-attribute?)
      (get-kb-parent-information variable)
    (when parent-entity?
      (find-external-simulation-definitions-for-variable-1
	variable parent-attribute? parent-entity? nil))))

(defun find-external-simulation-definitions-for-variable-1
       (variable attribute entity external-simulation-definitions-so-far)
  (when (external-simulation-p entity)
    (let ((external-simulation-definition-for-entity
	    (get-slot-value 
	      entity 'external-simulation-definition-for-entity)))
      (when (and (memq external-simulation-definition-for-entity
		       (external-simulation-definitions-for-attribute attribute))
		 (variable-simulated-by-external-simulation-definition?
		   variable entity external-simulation-definition-for-entity))
	(setq external-simulation-definitions-so-far
	      (simulate-cons external-simulation-definition-for-entity
			     external-simulation-definitions-so-far)))))
  (multiple-value-bind
    (parent-entity? parent-attribute?)
      (get-kb-parent-information entity)
    (declare (ignore parent-attribute?))
    (if parent-entity?
	(find-external-simulation-definitions-for-variable-1
	  variable attribute parent-entity? external-simulation-definitions-so-far)
	external-simulation-definitions-so-far)))


;;; Variable-simulated-by-external-simulation-definition?  returns the
;;; designation in the output-vector-from-external-simulator which designates
;;; the variable.  Note that it is impossible for more than one attribute of an
;;; object to designate the same variable.  Likewise, it is impossible for
;;; attributes of sub-objects of an object to designate the same variable; the
;;; sub-object structure is always a tree, never a network.  Therefore, there
;;; can be at most one unique designation in the 
;;; output-vector-from-external-simulator slot which designates the variable.

(defun variable-simulated-by-external-simulation-definition?
       (variable entity external-simulation-definition)
  (when (frame-ok-p external-simulation-definition)
    (loop with designations
	    = (get-attribute-designations 
		(car (output-vector-from-external-simulator
		       external-simulation-definition)))
	  for designation 
	      in designations
	  do
      (when (variable-designated-by-designation?
	       variable designation entity external-simulation-definition)
	(reclaim-simulate-list designations)
	(return designation))
	  finally 
	    (reclaim-simulate-list designations))))


(defun variable-designated-by-designation?
       (variable designation entity external-simulation-definition)
  (let* ((alist (simulate-list 
		  (simulate-cons
		    (class-of-object-computed-by-this
		      external-simulation-definition)
		    entity)))
	 (*current-computation-frame* external-simulation-definition)
	 (current-computation-flags current-computation-flags))
    (setf (role-serve-inactive-objects?) t)
    (eq variable (evaluate-designation designation alist))))

;; The class specified in the external-simulation-definition rather than
;; the class of the entity is used for the alist since the latter may be 
;; a sub-class of the former and the designations are in terms of the former.
;; Since evaluate-designation uses assq to search the alist and does not do any
;; kind of subclass test, it is important that the class on the alist be 
;; identical to the one in the designation.

;; Note that there is no need here for any kind of true inverse pattern
;; matching mechanism like the focus compilations for rules because 
;; only attribute designations are used.  This will not be true, however,
;; when more complicated designations are allowed in the left sides of
;; generic simulation formulas.


;;; Install-externally-simulated-variable-1 will, if external-simulation-definition
;;; is nil, remove all external-simulation-definition specifiers from the 
;;; variable.  If external-simulation-definition is not nil, it will be added
;;; or removed according to the deinstall? argument.

;;; Install-externally-simulated-variable-1 is called by
;;; install-externally-simulated-variable for inverse installation and
;;; install-externally-simulated-entity-1 for forward installation.  The only
;;; case where the deinstall?  argument is t is when
;;; forward-external-simulation-install calls
;;; install-externally-simulated-entity-1 or install-externally-simulated-entity
;;; for deinstalling.  In this case, the external-simulation-definition is
;;; removed from the simulation-category?  slot of the variable.  This approach
;;; of only removing what has to be removed is more efficient and simple than
;;; deinstalling everything and then
;;; reinstalling everything.

(defun install-externally-simulated-variable-1 
       (variable external-simulation-definition? deinstall?)
  (if (and external-simulation-definition?
	   (not deinstall?))
      (put-external-simulation-formula-into-variable-or-parameter
	variable external-simulation-definition?)
      (put-external-simulation-formula-into-variable-or-parameter
	variable nil)))





;;;; Kb-specific variables used at runtime.

(def-kb-specific-variable output-vector-for-object simulate1 nil nil)
;; Will eventually be a slot in a model!!





;;;; ICP Message Types and Objects


(def-structure (external-simulation-object)
  g2-object
  (external-simulation-object-corresponding-icp-object-map nil))

;; Change slot name to corresponding-icp-object-map-for-xs-object!




(def-icp-object-type external-simulation-object
		     (standard-icp-object-index-space
		       (external-simulation-object-corresponding-icp-object-map
			 external-simulation-object))
  (let ((g2-object (g2-object external-simulation-object)))
    (define-external-simulation-object
      g2-object corresponding-icp-object-index)))


;;; Many of the following message types go only from G2 to the external
;;; process and therefore have no handler bodies.


(def-icp-message-type new-externally-simulated-object
  ((external-simulation-object external-simulation-object))
  :no-handler)

(def-icp-message-type define-external-simulation-object
  ((integer icp-object-index) (text-string object-class))
  :no-handler)

(def-icp-message-type simulation-initialization-value
  ((float initialization-value))
  :no-handler)

(def-icp-message-type end-simulation-initialization-vector-for-object ()
  :no-handler)

(def-icp-message-type begin-simulation-input-vector-for-object
  ((external-simulation-object external-simulation-object))
  :no-handler)

(def-icp-message-type simulation-keyword
  ((text-string keyword))
  :no-handler)

(def-icp-message-type simulation-input-value
  ((float input-value))
  :no-handler)

(def-icp-message-type end-simulation-input-vector-for-object ()
  :no-handler)

(def-icp-message-type begin-simulation-output-vector-for-object
  ((returned-external-simulation-object external-simulation-object?))
  (if external-simulation-object?
      (let ((g2-object (g2-object external-simulation-object?)))
	(setq output-vector-for-object
	      (simulate-list g2-object)))
      (warning-message 1
	"Unable to retrieve external simulation object")))

;; Check for case where external-simulation-object can not be retrieved and send
;; warning message!

;; jh, 8/2/93.  Indeed, in G2 3.0 running on the Vax, the reader for
;; external-simulation-object sometimes fails to retrieve one, causing a
;; segmentation violation in the svref that is the expansion of the g2-object
;; macro.  Not sure how to "send" a warning to the remote process, as suggested
;; in the above note, since there seem to be no GSPAN messages for this purpose.
;; In order to fix the bug, we will "post" a warning to the G2 user for now.

;; Need to check if frame-has-been-reprocessed-p for g2-object!


(def-icp-message-type simulation-output-value
  ((float output-value))
  (setq output-vector-for-object
	(nconc output-vector-for-object
	       (simulate-list output-value))))

;; Keep tail pointer!



;;; The message handler for end-simulation-output-vector-for-object sets the
;;; simulation values according to the output vector and begins simulation
;;; of the next externally simulated object. 

(def-icp-message-type end-simulation-output-vector-for-object ()
  (with-current-model-for-icp-socket 
    current-icp-socket
    (cond 
      ((not (waiting-for-external-simulator? current-model-runtime-info?))
       (let* ((g2-object (car output-vector-for-object))
	      (external-simulation-definition
		(get-slot-value 
		  g2-object 'external-simulation-definition-for-entity))
	      (alist (simulate-list 
		       (simulate-cons 
			 (class-of-object-computed-by-this 
			   external-simulation-definition)
			 g2-object)))
	      (*current-computation-frame* external-simulation-definition)
	      (current-computation-flags current-computation-flags)
	      (designations
		(progn
		  (setf (role-serve-inactive-objects?) t)
		  (get-attribute-designations
		    (car (output-vector-from-external-simulator
			   external-simulation-definition))))))
	 (cond
	   ((=f (length designations)
		(length (cdr output-vector-for-object)))
	    (loop with variable-simulation-runtime-structure
		  for designation in designations
		  for output-value in (cdr output-vector-for-object)
		  as output-variable? 
		     = (evaluate-designation designation alist)
		  do
	      (cond 
		((and output-variable?
		      (of-class-p output-variable? 'variable-or-parameter)
		      (externally-simulated-variable-p output-variable?)
		      (frame-ok-p output-variable?)
		      ;; Also check if frame has been reprocessed!
		      )
		 (setq variable-simulation-runtime-structure
		       (simulation-runtime-information? output-variable?))
		 (store-new-simulation-value
		   variable-simulation-runtime-structure output-value)
		 (update-variable output-variable?))
		(t
		 (warning-message 
		   2 "Problem encountered simulating the designation ~a for the entity ~NF externally."
		   designation			       ; need to print in better format!
		   g2-object)
		 ;; Consider giving a more precise warning message here!
		 ))))
	   (t
	    (warning-message 
	      2 "Problem encountered simulating the entity ~NF externally due to 
mismatch in number of designations specified in \"output vector from external 
simulator\" slot of external simulation definition and number of values returned
by the external simulator."
	      g2-object)))
	 
	 (reclaim-simulate-tree alist)
	 (reclaim-simulate-list designations)
	 (reclaim-simulate-list output-vector-for-object)
	 (setq output-vector-for-object nil))
       (when (not (current-send-all-values-at-beginning-of-cycle?))
	 (work-on-next-externally-simulated-entity)))
      (t
       ;; Rolling back due to edit change.
       (reclaim-simulate-list output-vector-for-object)
       (setq output-vector-for-object nil)
       (setf (waiting-for-external-simulator? current-model-runtime-info?) nil)))))



(def-icp-message-type initialize-external-simulator ())
(def-icp-message-type shutdown-external-simulator ())
(def-icp-message-type pause-external-simulator ())
(def-icp-message-type resume-external-simulator ())


(def-icp-message-type end-simulation-input-for-cycle ())

(def-icp-message-type end-simulation-output-for-cycle ()
  (with-current-model-for-icp-socket 
    current-icp-socket
    (end-external-work-for-cycle)))



(def-icp-message-type connection-info 
		      ((external-simulation-object input-end-object)
		       (external-simulation-object output-end-object)
		       (unsigned-integer directional?)
		       (text-string port-name-for-input-end-object)
		       (text-string port-name-for-output-end-object)
		       (external-simulation-object externally-simulated-connection)
		       (unsigned-integer number-of-connections-left-in-path))
  )






(defun-allowing-unwind define-external-simulation-object 
		       (g2-object icp-object-index)
  (writing-icp-message-group
    ((icp-output-port (external-simulator-interface-icp-socket
			current-model-runtime-info?)))
    (let ((class-string (tformat-text-string "~a" (class g2-object))))
      (send-icp-define-external-simulation-object
	icp-object-index class-string)
      (reclaim-text-string class-string))))


(def-icp-value-reader returned-external-simulation-object
  (let ((corresponding-icp-object-index
         (read-icp-unsigned-integer))
        (current-icp-port
         (icp-output-port current-icp-socket)))
    (get-original-icp-object corresponding-icp-object-index)))

;; The icp-arg-type returned-external-simulation-object is needed to handle the
;; message type begin-simulation-output-vector-for-object.
;; External-simulation-object can't be used as the type since the default reader
;; would be used.  The default reader uses the
;; corresponding-icp-object-index-space-plist for the icp-input-port of the
;; socket rather than the icp-output-port.  This causes problems since the index
;; is assigned in the index space of the output port and therefore, the object
;; cannot be retrieved using the index space of the input port.  Thus, to
;; circumvent this problem, the type returned-external-simulation-object is used
;; and a value reader is defined for this type which binds current-icp-port to
;; the output port so that the correct index space is used to retrieve the
;; object.  This approach is also used in GSI.


(def-icp-value-writer returned-external-simulation-object
  'dummy-definition)




;;;; Initialization


;;; Initialize-externally-simulated-portion-of-model calls
;;; work-on-external-simulator-tasks (after setting
;;; external-simulation-initialization-completed?  to nil) to actually send
;;; initialization data to the external simulator.  The icp handler for
;;; end-simulation-output-vector-for-object calls
;;; work-on-next-externally-simulated-entity which sets
;;; external-simulation-initialization-completed?  to t when all externally
;;; simulated entities have been processed.  If there is no external simulation,
;;; external-simulation-initialization-completed?  is set to t.  Note that
;;; simulate-until-consistent-with-gensym-time will do nothing if
;;; external-simulation-initialization-completed?  is nil.  Thus, gensym-time
;;; can get far ahead of simulation-time if initialization of external
;;; simulator takes a long time.

;; This could be revised to not return control to the scheduler until external
;; simulation initialization is finished.  Review, especially when designing a
;; kb initialization phase which is distinct from running.

(defun-allowing-unwind initialize-externally-simulated-portion-of-model ()
  (let ((external-simulator-configuration
	  (current-external-simulator-configuration)))
    (cond
      ((and external-simulator-configuration
	    (not (eq (car external-simulator-configuration)
		     'none)))
       ;; The following code is from GSPAN, which is no longer supported.
       (warning-message 1
	   "Attempting to execute GSPAN functionality.  GSPAN has been ~
            discontinued as a product and its features were removed from G2 ~
            as of Version 4.0.")
       
;       (execute-body-if-gspan-is-authorized
;	 (for-each-element-in-external-set 
;	   (externally-simulated-entities current-model-runtime-info?)
;	   'initialize-externally-simulated-entity)

;	 (change-vector-to-external-simulator nil)
;	 (change-vector-from-external-simulator nil)
	 
;	 (setf (external-simulator-interface-icp-socket current-model-runtime-info?)
;	       (make-icp-connection
;		 (car external-simulator-configuration)))
	 
;	 (setf (external-simulation-initialization-completed? current-model-runtime-info?)
;	       nil)
;	 (setf (status-of-work-on-external-simulation current-model-runtime-info?)
;	       'no-work-done-yet-for-this-cycle)
	 
;	 (cond
;	   ((external-simulator-interface-icp-socket current-model-runtime-info?)
;	    (register-icp-callback 'icp-connection-loss
;	      'warn-of-loss-of-connection-to-external-simulator
;	      (external-simulator-interface-icp-socket current-model-runtime-info?))
;	    (writing-icp-message-group
;	      ((icp-output-port (external-simulator-interface-icp-socket
;				  current-model-runtime-info?)))
;	      (send-icp-initialize-external-simulator))
;	    (cond
;	      ((not (current-send-all-values-at-beginning-of-cycle?))
;	       (work-on-external-simulator-tasks))
;	      (t
;	       (send-all-input-values-to-external-simulator)
;	       )))
;	   (t
;	    (warning-message 
;	      1 "Cannot make ICP connection for external simulator interface."))))
       )
    (t						       ; if no external simulation
     (setf (external-simulation-initialization-completed? 
	     current-model-runtime-info?) t)))))

;; Note that if external-simulator-interface-icp-socket is nil,
;; work-on-external-simulator-tasks will not be called and
;; external-simulation-initialization-completed?  will not be set back to t and
;; simulate-one-cycle will never be called.  Therefore, there is no need to
;; check external-simulator-interface-icp-socket anywhere else.

;; Note that there is no need to check if the frame status of the 
;; external-simulation-definition is ok since if it were not, the entity
;; would not be in externally-simulated-entities in the first place.
;; In other words, this is checked at installation time rather than 
;; runtime.



(defun initialize-externally-simulated-entity (entity)
  (let* ((*current-computation-frame* entity)
	 (current-computation-flags current-computation-flags)
	 (external-simulation-definition
	   (get-slot-value 
	     entity 'external-simulation-definition-for-entity))
	 (alist 
	   (simulate-list 
	     (simulate-cons
	       (class-of-object-computed-by-this 
		 external-simulation-definition)
	       entity))))
    (setf (role-serve-inactive-objects?) t)
    (loop with designations
	    = (get-attribute-designations
		(car (output-vector-from-external-simulator
		       external-simulation-definition)))
	  for designation in designations
	  as output-variable?
	     = (evaluate-designation designation alist)
	  do
      (if (and output-variable?
	       (of-class-p output-variable? 'variable-or-parameter)
	       (externally-simulated-variable-p output-variable?)
	       (frame-ok-p output-variable?))
	  (initialize-externally-simulated-variable output-variable?)
	  (warning-message 
	    1 "Problem encountered simulating the designation ~a for the entity ~NF externally."
	    designation				       ; need to print in better format!
	    entity)
	  ;; Consider giving a more precise warning message here!
	  )
      
	  finally
	    (reclaim-simulate-tree alist)
	    (reclaim-simulate-list designations))))



(defun initialize-externally-simulated-variable (variable)
  (let* ((variable-simulation-runtime-structure
	   (let ((old-runtime-structure?
		   (simulation-runtime-information? variable))
		 (new-runtime-structure
		   (make-variable-simulation-runtime-structure)))
	     (when old-runtime-structure?
	       (reclaim-variable-simulation-runtime-structure
		 old-runtime-structure?))
	     (setf (corresponding-variable new-runtime-structure) variable)
	     (set-simulation-runtime-information? variable new-runtime-structure)
	     new-runtime-structure)))
    (setf (interval-at-which-to-send-value-to-inference-engine
	    variable-simulation-runtime-structure) nil)
    (setf (simulation-value variable-simulation-runtime-structure)
	  simulation-no-value
	  (new-simulation-value variable-simulation-runtime-structure)
	  simulation-no-value)
    (set-up-update-timing-for-variable 
      variable-simulation-runtime-structure nil)
    variable-simulation-runtime-structure))



;;; Create-new-externally-simulated-object returns non-nil if it is successful
;;; in obtaining the full initialization vector and sending it to the external
;;; simulator.

(defun create-new-externally-simulated-object 
       (external-simulation-definition entity)
  (let ((class 
	  (class-of-object-computed-by-this external-simulation-definition))
	(external-simulation-object
	  (make-external-simulation-object)))
    (set-slot-value entity 'external-simulation-object-structure
		    external-simulation-object)
    (setf (g2-object external-simulation-object) entity)
    (let ((current-computation-flags current-computation-flags))
      (setf (role-serve-inactive-objects?) t)
      (let* ((alist (simulate-list (simulate-cons class entity)))
	     (*current-computation-frame* external-simulation-definition)
	     (current-simulation-runtime-structure nil)
	     (designations
	       (get-attribute-designations
		 (car (initialization-vector-for-external-simulator
			external-simulation-definition))))
	     (initializing-simulator? t)
	     initialization-values)
	(setf (simulator-step-flag current-model-runtime-info?)
	      'calculating-state-variables
	      initialization-values
	      (loop for designation in designations
		    collect
		    (sim-eval-variable-for-designation designation alist)
		      using simulate-cons))
	(prog1
	    (when (external-simulator-input-values-ok? 
		    initialization-values entity 'initialization)
	      (send-create-new-externally-simulated-object
		external-simulation-object initialization-values)
	      t)
	  (reclaim-simulate-tree alist)
	  (reclaim-simulate-list designations)
	  (reclaim-simulate-list initialization-values))))))

;; Sim-eval-variable-for-designation will get the current simulated value.  This
;; is ok since initialize-simulator updates all internally simulated variables
;; before initializing externally simulated ones.  It does, however, mean that
;; externally simulated variables can not be used to initialize other externally
;; simulated variables nor to initialize internally simulated variables.  In other
;; words, neither the initialization-vector-for-external-simulator slot of an
;; external simulation definition, nor the initial value expressions of internally
;; simulated variables, should contain designations for externally simulated
;; variables.


(defun more-than-one-designation-in-vector-p (designation-or-designations)
  (and (consp designation-or-designations)
       (eq (car designation-or-designations) '\,)))


(defun at-least-one-designation-in-vector-p (designation-or-designations)
  (and designation-or-designations
       (not (eq designation-or-designations 'none))))


(defun-allowing-unwind send-create-new-externally-simulated-object
		       (external-simulation-object initialization-values)
  (writing-icp-message-group
    ((icp-output-port (external-simulator-interface-icp-socket
			current-model-runtime-info?)))
    (send-icp-new-externally-simulated-object external-simulation-object)
    (loop for initialization-value in initialization-values
	  do (send-icp-simulation-initialization-value initialization-value))
    (send-icp-end-simulation-initialization-vector-for-object)))


(defun warn-of-loss-of-connection-to-external-simulator (icp-socket)
  icp-socket
  (warning-message 
    2 "ICP connection to external simulator is broken.")
;  (notify-user
;    "ICP: Error #~d; closing broken connection with ~a"
;    (io-status-block-condition-value
;      (vms-io-handle-iosb input-port-handle))
;    (icp-remote-host-name icp-socket))
;  receive-icp-input-in-callback

;; Talk to Brian.

)




;;;; Simulation using External Simulation Definitions

;;; Currently, externally simulated variables are not sorted in any way.  A
;;; state variable approach is used where for all input variables to the
;;; external simulator, values from the previous cycle are sent to compute the
;;; output variables for the current cycle.  Similarly, for all output variables
;;; from the external simulator, values from the previous cycle are used for
;;; purposes of computing values for the current cycle in the internal
;;; simulator.  Thus, all variables that are inputs to the external simulator
;;; are treated as state variables from the standpoint of the external simulator
;;; and all variables that are outputs of the external simulator are treated as
;;; state variables from the standpoint of the internal simulator.
;;; This approach greatly simplifies the external simulator mechanism since
;;; it eliminates the need to sort variables and avoids problems with algebraic
;;; loops.  Furthermore, it allows internal and external simulations to run
;;; completely in parallel.  A sorted approach would require portions of the
;;; internal and external simulations to run in series.

;;; This is implemented very easily by some minor extra logic.
;;; Begin-simulating-object-externally temporarily binds (simulator-step-flag
;;; current-model-runtime-info?) to 'calculating-state-variables when simulation
;;; evaluating the inputs to be sent to the external simulator.  When generating
;;; runtime formulas, if an externally simulated variable is encountered, it is
;;; wrapped with 'externally-simulated which has its own simulation evaluator.
;;; Finally, sim-eval-get-value-of-variable checks if the variable is simulated
;;; externally and handles this by calling
;;; sim-eval-get-value-of-externally-simulated-variable.

(defun work-on-external-simulator-tasks ()
  (case (status-of-work-on-external-simulation current-model-runtime-info?)
    (no-work-done-yet-for-this-cycle
     (handle-updates-to-externally-simulated-entities)
     (cond
       ((and (not (external-set-empty? 
		    (externally-simulated-entities
		      current-model-runtime-info?)))
	     (execute-external-simulation-cycle?))
	(setf (externally-simulated-entities-to-process 
		current-model-runtime-info?)
	      (external-set-next?
		(externally-simulated-entities current-model-runtime-info?)))
	(work-on-next-externally-simulated-entity))
       (t
	(setf (status-of-work-on-external-simulation current-model-runtime-info?)
	      'work-completed-for-this-cycle)
	(end-external-simulation-cycle))))))

(defun execute-external-simulation-cycle? ()
  (let ((variable-group-update-structure?
	  (get-non-override-variable-group-update-structure
	    current-model-runtime-info?)))
    (and variable-group-update-structure?
	 (update-group-this-cycle? variable-group-update-structure?))))

;; This ensures that the external simulation time increment is the same as the
;; default-simulation-time-increment.  Time increments specified in 
;; externally simulated variables are ignored.  Post a warning or frame
;; note if the user tries to specify a separate time increment for an
;; externally simulated variable!  Also, consider adding a slot to the
;; external simulation definitions to allow classes to update at different
;; rates.


;;; Work-on-next-externally-simulated-entity will call
;;; create-new-externally-simulated-object rather than
;;; begin-simulating-object-externally if
;;; external-simulation-initialization-completed? is nil.

(defun work-on-next-externally-simulated-entity (&optional sending-all-at-once?)
  (loop as next-entity-set-structure?
	   = (externally-simulated-entities-to-process
	       current-model-runtime-info?)
	until (null next-entity-set-structure?)
	as next-entity
	   = (entity-in-external-set next-entity-set-structure?)
	do
    (setf (externally-simulated-entities-to-process current-model-runtime-info?)
	  (external-set-next?
	    (externally-simulated-entities-to-process current-model-runtime-info?)))
    (when 
      (if (external-simulation-initialization-completed?
	    current-model-runtime-info?)
	  (begin-simulating-object-externally
	    (get-slot-value 
	      next-entity 'external-simulation-definition-for-entity)
	    next-entity)
	  (create-new-externally-simulated-object
	    (get-slot-value 
	      next-entity 'external-simulation-definition-for-entity)
	    next-entity))
      (setf (status-of-work-on-external-simulation current-model-runtime-info?)
	    'waiting-for-values)
      (return (values)))
	finally
	  (cond
	    (sending-all-at-once?
	     (setf (status-of-work-on-external-simulation 
		     current-model-runtime-info?)
		   'work-completed-for-this-cycle))
	    (t
	     (end-external-work-for-cycle)))))

(defun end-external-work-for-cycle ()
  (setf (status-of-work-on-external-simulation current-model-runtime-info?)
	'work-completed-for-this-cycle)
  (when (null (external-simulation-initialization-completed? 
		current-model-runtime-info?))
    (setf (external-simulation-initialization-completed? current-model-runtime-info?)
	  t))
  (end-external-simulation-cycle))




;;; Send-all-input-values-to-external-simulator is used instead of
;;; work-on-external-simulator-tasks when the
;;; send-all-values-at-beginning-of-cycle?  slot of the simulation-parameters
;;; system table is t.

(defun-allowing-unwind send-all-input-values-to-external-simulator ()
  (case (status-of-work-on-external-simulation current-model-runtime-info?)
    (no-work-done-yet-for-this-cycle
     (handle-updates-to-externally-simulated-entities)
     (cond
       ((execute-external-simulation-cycle?)
	(cond
	  ((not (external-set-empty?
		  (externally-simulated-entities current-model-runtime-info?)))
	   (setf (externally-simulated-entities-to-process 
		   current-model-runtime-info?)
		 (external-set-next?
		   (externally-simulated-entities current-model-runtime-info?)))
	   (loop while (not (eq (status-of-work-on-external-simulation
				  current-model-runtime-info?)
				'work-completed-for-this-cycle))
		 do (work-on-next-externally-simulated-entity t))
	   (setf (status-of-work-on-external-simulation current-model-runtime-info?)
		 'waiting-for-values)
	   
	   (when (null (external-simulation-initialization-completed?
			 current-model-runtime-info?))
	     (send-connection-information-to-external-simulator))
	   
	   (writing-icp-message-group
	     ((icp-output-port (external-simulator-interface-icp-socket
				 current-model-runtime-info?)))
	     (send-icp-end-simulation-input-for-cycle)))
	  (t
	   (setf (status-of-work-on-external-simulation current-model-runtime-info?)
		 'waiting-for-values)
	   (send-speedup-input)
	   (writing-icp-message-group
	     ((icp-output-port (external-simulator-interface-icp-socket
				 current-model-runtime-info?)))
	     (send-icp-end-simulation-input-for-cycle)))))
       (t
	(setf (status-of-work-on-external-simulation current-model-runtime-info?)
	      'work-completed-for-this-cycle)
	(end-external-simulation-cycle))))))





;;; Send-connection-information-to-external-simulator sends information about all
;;; connections that have at least one end connected to an externally simulated
;;; object.  If such a connection is connected at one end to an object that is not
;;; externally simulated, then no information is sent for that end.  This is
;;; indicated by sending an empty string for the portname.  If there is no
;;; portname for an object that is simulated externally, then the string "none" is
;;; sent.  Externally simulated connections along the connection path between
;;; objects are also sent out (see send-info-for-each-connection-in-path).  As
;;; each externally simulated connection in the path is sent,
;;; number-of-connections-left-in-path is decremented.  If there are no externally
;;; simulated connections in the path, port information is sent but
;;; number-of-connections-left-in-path is -1 to indicate no externally simulated
;;; connections.

(defun send-connection-information-to-external-simulator ()
  (for-each-element-in-external-set 
    (externally-simulated-entities current-model-runtime-info?)
    'send-connection-information-to-external-simulator-1))

(defun send-connection-information-to-external-simulator-1 
       (externally-simulated-entity)
  (loop for connection being each output-connection 
	    of externally-simulated-entity
	do (get-and-send-info-for-connection
	     connection externally-simulated-entity t))
  (loop for connection being each input-connection 
	    of externally-simulated-entity
	do (get-and-send-info-for-connection
	     connection externally-simulated-entity nil)))



(defun get-and-send-info-for-connection 
       (connection externally-simulated-entity output-connection?)
  (let (opposite-end-info-triples
	connection-paths
	(local-port-name-string
	  (tformat-text-string 
	    "~a"
	    (get-port-name-given-block-and-connection
	      externally-simulated-entity connection)))
	(directionality
	  (if (connection-not-directed? connection) 0 1)))
    (multiple-value-setq
      (opposite-end-info-triples connection-paths)
      (get-info-for-connection-and-entity 
	connection externally-simulated-entity))
    (loop with opposite-end-entity-to-send and opposite-end-port-name-string
	  for (opposite-end-entity port-name-list nil)
	      in opposite-end-info-triples
	  for connection-path
	      in connection-paths
	  as opposite-end-entity-externally-simulated?
	     = (external-simulation-p opposite-end-entity)
	  do
      (when (or output-connection?
		(not opposite-end-entity-externally-simulated?)) 
	(if opposite-end-entity-externally-simulated?
	    (setq opposite-end-entity-to-send opposite-end-entity
		  opposite-end-port-name-string
		  (tformat-text-string 
		    "~a"
		    (or (car port-name-list)
			'none)))
	    (setq opposite-end-entity-to-send externally-simulated-entity
		  opposite-end-port-name-string
		  (tformat-text-string "")))
	(send-info-for-this-connection-path
	  output-connection? directionality
	  externally-simulated-entity local-port-name-string
	  opposite-end-entity-to-send opposite-end-port-name-string
	  connection-path)
	(reclaim-text-string opposite-end-port-name-string)))
    (reclaim-text-string local-port-name-string)
    (reclaim-eval-tree opposite-end-info-triples)
    (reclaim-eval-tree connection-paths)))

;; Note that if opposite-end-entity-externally-simulated?  is nil,
;; opposite-end-entity-to-send is set to externally-simulated-entity.  This is
;; necessary as a dummy since the icp message for connection info requires an
;; external-simulation-object argument.  As mentioned above, the fact that the
;; port name string is empty indicates that this is a dummy argument.

;; Note that nothing is done in the case where the connection is an input
;; connection to externally-simulated-entity and the entity at opposite end is
;; being externally simulated since this connection is processed as an output
;; connection for that entity.



(defun get-info-for-connection-and-entity (connection entity)
  (let* (entities
	  connections
	  (current-connection-path nil)
	  (connections-in-connection-paths nil))
    (searching-connections ()
      (search-for-directly-connected-entities-for-connection
	entity 'object connection nil 'both nil nil 'save-path)
      (setq entities entities-or-triples-found-in-search)
      (setq connections connections-in-connection-paths))
    (values entities connections)))

;; Consider moving to roles.



(defun-allowing-unwind send-info-for-this-connection-path
       (output-connection? directionality
	externally-simulated-entity local-port-name-string
	opposite-end-entity opposite-end-port-name-string connection-path)
  (writing-icp-message-group
    ((icp-output-port (external-simulator-interface-icp-socket
			current-model-runtime-info?)))
    (if output-connection?
	(send-info-for-each-connection-in-path
	  (get-slot-value-if-any 
	    externally-simulated-entity 'external-simulation-object-structure)
	  (get-slot-value-if-any 
	    opposite-end-entity 'external-simulation-object-structure)
	  directionality
	  local-port-name-string
	  opposite-end-port-name-string
	  connection-path)
	(send-info-for-each-connection-in-path
	  (get-slot-value-if-any 
	    opposite-end-entity 'external-simulation-object-structure)
	  (get-slot-value-if-any 
	    externally-simulated-entity 'external-simulation-object-structure)
	  directionality
	  opposite-end-port-name-string
	  local-port-name-string
	  connection-path))))

(defun send-info-for-each-connection-in-path
       (input-end-object output-end-object directional?
	port-name-for-input-end-object port-name-for-output-end-object 
	connection-path)
  (let ((externally-simulated-connections-in-connection-path
	  (loop for connection in connection-path
		as external-simulation-object-for-connection?
		   = (get-slot-value-if-any 
		       connection 'external-simulation-object-structure)
		nconc (if external-simulation-object-for-connection?
			  (eval-list external-simulation-object-for-connection?)))))
    (if externally-simulated-connections-in-connection-path
	(loop for number-left-in-path 
		  from (-f (length externally-simulated-connections-in-connection-path) 1)
		  downto 0
	      for externally-simulated-connection 
		  in externally-simulated-connections-in-connection-path
	      do
	  (send-icp-connection-info
	    input-end-object output-end-object directional? 
	    port-name-for-input-end-object port-name-for-output-end-object
	    externally-simulated-connection number-left-in-path))
	(send-icp-connection-info
	  input-end-object output-end-object directional? 
	  port-name-for-input-end-object port-name-for-output-end-object
	  input-end-object -1))
    (reclaim-eval-list externally-simulated-connections-in-connection-path)))

;; Note that for the case where
;; externally-simulated-connections-in-connection-path is nil, input-end-object is
;; sent as the externally-simulated-connection arg to send-icp-connection-info.
;; This is needed as a dummy since the icp message for connection info requires an
;; external-simulation-object argument.  The -1 number-of-connections-left-in-path
;; arg indicates that this is a dummy and (as mentioned above) that there are no
;; externally simulated connections in the path.



(defun handle-updates-to-externally-simulated-entities ())



;;; Begin-simulating-object-externally returns non-nil if it is successful
;;; in obtaining the full input vector and sending it to the external simulator.

(defun begin-simulating-object-externally (external-simulation-definition object)
  (let ((current-computation-flags current-computation-flags))
    (setf (role-serve-inactive-objects?) t)
    (let* ((alist
	     (simulate-list 
	       (simulate-cons
		 (class-of-object-computed-by-this external-simulation-definition)
		 object)))
	   (*current-computation-frame* external-simulation-definition)
	   (current-simulation-runtime-structure nil)
	   (input-value-designations
	     (get-attribute-designations
	       (car (input-vector-to-external-simulator 
		      external-simulation-definition))))
	   (message-keywords
	     (get-attribute-designations
	       (car (message-keywords external-simulation-definition))))
	   input-values)
      (setf (simulator-step-flag current-model-runtime-info?)
	    'calculating-state-variables
	    input-values
	    (loop for designation in input-value-designations
		  collect (sim-eval-variable-for-designation designation alist)
		    using simulate-cons))
      (prog1
	  (when (external-simulator-input-values-ok? 
		  input-values object 'input)
	    (send-input-vector-for-object-simulated-externally
	      (get-slot-value-if-any object 'external-simulation-object-structure)
	      message-keywords input-values)
	    t)
	(reclaim-simulate-tree alist)
	(reclaim-simulate-list input-value-designations)
	(reclaim-simulate-list input-values)
	(reclaim-simulate-list message-keywords)))))

;; Consider renaming get-attribute-designations since it is useful for things
;; other than just attribute designations!


(defun external-simulator-input-values-ok? 
       (input-values entity input-or-initialization)
  (loop for input-value in input-values
	do 
    (when (not (numberp input-value))
      (warning-message 
	2 "Problem encountered simulating the entity ~NF externally.  The ~a
value ~a is not a number."
	entity
	input-or-initialization
	input-value)
      (return nil))
	finally (return t)))


(defun-allowing-unwind send-input-vector-for-object-simulated-externally
       (external-simulation-object keywords input-values)
  (writing-icp-message-group
    ((icp-output-port (external-simulator-interface-icp-socket
			current-model-runtime-info?)))
    (send-icp-begin-simulation-input-vector-for-object external-simulation-object)
    (loop for keyword in keywords
	  as keyword-string = (tformat-text-string "~a" keyword)
	  do (send-icp-simulation-keyword keyword-string)
	     (reclaim-text-string keyword-string))
    (loop for input-value in input-values
	  do (send-icp-simulation-input-value input-value))
    (send-icp-end-simulation-input-vector-for-object)))


;; Check if symbols are converted to strings automatically by ICP.

;; Need to specify exactly how external simulations should be called for each
;; model type and for batch as well as interactive modes.  Initialization
;; issues must be detailed as well.

;; This simple scheme uses values from previous cycle when evaluating input
;; vector.  Thus, the input variables are like state variables in that there
;; may be some lag.  No attempt is made at a "simultaneous" solution.

;; Need to work on pattern matching issues installation, similar to those for 
;; implicit equations.
;; See design memo.

;; Consider caching designations in input, output and initialization vectors.
;; Should be no problem caching these at runtime in the same way that 
;; runtime simulation formulas are cached.
 
;; Flag error if one of the output vector
;; designations is not a variable or one of the input or initialization vectors
;; fails to evaluate.

;; Don't allow editing of external simulation frame while running.  Put up error
;; message if this is attempted.  Talk to Mark, Mike.  We will need a general
;; mechanism for this in the future anyway when we compile simulations.
;; Alternatively, editing could be allowed but it will not have any effect 
;; until the next time the model is started.

;; Note that external simulator is run completely synchronously with rest of
;; model in G2.  Of course, if the model is being run in batch mode and there
;; is no G2 component, then it is essentially running asynchronously on its
;; own, at least from the user's standpoint.




;;;; Shutdown

(defun-allowing-unwind shutdown-externally-simulated-portion-of-model ()

  (setf (externally-simulated-entities-to-process 
	  current-model-runtime-info?) nil)

  (shutdown-speedup-simulation)

  (when (external-simulator-interface-icp-socket current-model-runtime-info?)
    (writing-icp-message-group
      ((icp-output-port (external-simulator-interface-icp-socket
			  current-model-runtime-info?)))
      (send-icp-shutdown-external-simulator))
    (shutdown-icp-socket-connection
      (external-simulator-interface-icp-socket current-model-runtime-info?))
    (setf (external-simulator-interface-icp-socket 
	    current-model-runtime-info?) nil)))

;; Shutdown dataserver functions are always called when loading kbs.  Thus,
;; it is important to check here if external-simulator-interface-icp-socket
;; is non-nil and to set it to nil when done.  Otherwise, an attempt
;; will be made to send the icp shutdown message whenever loading kbs
;; resulting in the "broken connection" error message being posted
;; (see warn-of-loss-of-connection-to-external-simulator).




;;;; Configuration of C Files

;; The following C files are used for the external portion of the external
;; simulator interface:

;; xs_sys.h
;; xs_icp.c
;; xs_main.c
;; xs_exam1.c
;; xs_stubs.h

;; These currently reside on "ma:>ab".  They correspond in purpose to
;; similarly named GSI files.  Identical copies are also currently
;; kept on "ma:>ab-1-11b".

;; These files must be linked with the GSI C files to make an image.
;; The features.h file must be modified to indicate GSPAN
;; configuration.  The user sees source for xs_ext.c and xs_example1.c
;; only.  The file xs_stubs.c is so that GSI can be linked without GSPAN.

;; The make file for compiling on the SUN is 
;; "ca:/disc/ab/makegsixsim".  Do
;; make -f makegsixsim 
;; to do the make.

;; For compiling on the VAX, the com file
;; QUINCY:[ab]make_xsi.com is used.  It calls link_xsi.com.  
;; Do
;; @make_xsi for_mbx
;; to compile mailbox version (other args for other versions).
;; This produces the executeable "xs_exam1_mbx.exe".





;;;; Notes for 3.0

;; Extension C sources are in directory accessed by ext-c (NFS directory).  Edit
;; these here and use "makecpp gspan [opt]" to compile and link.
;; Actual path is /bt/ab/ext/c.  Need to do setup-env ab bt.
;; To edit, need to use source code control mechanism.
;;  - rlogin bolton
;;  - domain ext vax
;;  - cms reserve gw_gspan.c "comment"

;;  - edit from any convenient editor

;;  - cms replace gw_gspan.c ""
;;  - cms fetch gw_gspan.c ""

;; Images are in ext-o if opt is not specified, ext-opt if it is.  Run
;; xs_exam1 or xs_exam2 to test.  OK on SPARC, 2/4/92.

;; For Speedup executables, the network task name should be given as a
;; command line argument.  This argument defaults to GSPANOBJ (see
;; gsi_main_edi.c).  May have to compile this differently for each
;; executable.  Make note in update to SPEEDUP manual.

;; Take draft designation off of SPEEDUP manual.



;; VAX

;; Fortran currently only runs from HOLDEN.  Thus, Speedup must be run
;; from HOLDEN.  There are sometimes problems logging on to HOLDEN due
;; to limiting of number of users.  This is due to the "aims" project.
;; To stop this, log on aim71, gensym and do @aim:aimdwn.

;; FTP only works on ACTON.



;; To make GSPAN extensions on the VAX, do

;; to GSI$ROOT
;; mms/desc = makegspan-vms

;; Use 
;; lib/list libgspan.olb
;; to see what is in there.

;; Use 
;; list gsioptions.opt/opt
;; to see what is in.

;; In the Speedup bridge, libgspan.olb, and gsioptions.opt/opt are
;; linked in, just like object files (see speedup.include).



;;;; Notes for VAX

;; 2/21/89
;; quincy:[ab]gspan.lisp -> quincy:[ab]gspan-1-11a-patch.lisp
;; The only difference is that the patch uses 
;; with-temporary-short-float-creation rather than 
;; with-temporary-gensym-float-creation.  This issue will go away
;; after 1.11a since subsequent releases all use 
;; with-temporary-gensym-float-creation (see also note above in
;; to do list).

;; Another difference is that to initialize the frame-status-and-notes slot
;; of an external-simulation-definition, slot-value-cons is used in 1.11a
;; and slot-value-cons-function is used in subsequent releases.

;; Another difference is that the ICP protection mechanism in
;; writing-icp-message-group has to be patched for 1.11a.


;; 2/27/89
;; Don't ship any more 1.11a versions.  The patches are piling up too much
;; (see above notes).  Just send 1.11b or beyond from now on.




;;;; Notes

;; Process-icp-sockets contains a with-temporary-gensym-float-creation
;; wrapper so there is never any number consing problem here when
;; handling floats being returned from the external simulator.

;; There are a number of problems when running the external-simulator under
;; ti-tcp (running G2 on Explorer2 and external part on Sun).  First of all,
;; "more" processing should be turned off in the Telnet process (use TERM-0-M
;; to turn it off, TERM-1-M to turn it on).  If this is not done, and if the
;; C program prints things, the network will soon stop sending ICP message
;; groups.  Another problem is that for some reason, network can only send
;; one ICP message group per second from the external process.  It turns out
;; (for some low-level reason) that moving the mouse around causes message
;; groups to be sent faster.  Note that this problem does not occur when
;; running both the G2 and external processes on the SUN.

;; Unlike GSI, the external simulator interface allows for only one ICP
;; socket.  The capability for more than one external simulation process
;; should be implemented via the model framework.  Thus, each model
;; could have its own separate external simulation process.

;; For now, do not deal with sorting issues as Jim has suggested.  Treat all
;; externally simulated variables as state variables.  This is perfectly
;; acceptable as long as it is documented clearly.  Sorting is done now in the
;; simulator but it is complicated.  It has to be done not just at
;; initialization time but also each time an edit is made.  Also, trying to sort
;; externally simulated variables with internally simulated variables makes it
;; impossible to run external and internal portions in parallel and greatly
;; complicates the sequencing.

;; Use stuff from agh>external-simulator-design.text to document.

;; Make sure that the grammar for attribute-designation does not have any
;; problems with generating attribute-names and classs for menus.

;; A good test kb is agh>dupont-external-simulation-test.kb.

;; Consider changing name from external-simulation-definition to
;; external-simulation-for-class to emphasize object oriented nature and
;; distinguish it from other external simulation we may do in the future
;; (outputting equations to be solved externally).

;; Make list of customers actively interested in this:
;;   Dupont, Combustion Engineering, Badger.

;; Need to do a memo on how this capability should be used and how it is
;; distinguished from GSI and foreign function calls.
;;   1.  More efficient than GSI or foreign function call since many values
;;   are input and output at once.
;;   2.  Real benefit though is object oriented approach which allows for
;;   specifying the simulation in a high level way (by drawing a schematic
;;   in G2), and then executing it externally.
;;   3.  Close integration with G2 simulator makes it easy to simulate some
;;   things in G2 and other things externally.
;; There is always potential for misuse of this as just a foreign function
;; type of interface where a simulation object is defined and this is
;; used to interface to an external simulator.  In this case, the objects in
;; the G2 schematic (except for the simulation object) are not related in 
;; any way to the external simulator.  In such a case, it would make more
;; sense to not use the G2 simulator at all and just interface the
;; external simulator directly to the inference engine via GSI.

;; It may be desirable at some point to implement a foreign function capability
;; that allows for returning multiple values.  This would allow object
;; oriented procedures using external functions.  This would have none of
;; the framework or synchronization of the external simulator and therefore
;; should not be used for simulation.




;;;; Error Conditions and How they are Handled

;; Need to test all these error conditions and their handlers systematically
;; at some point.  Include tests here!  See also installation test procedure
;; below.

;; Be sure to include rules for what makes frame status on external
;; simulation definition and on variables bad.

;;; Installation Errors for Variables

;;; Installation errors for externally simulated variables actually only occur
;;; in relatively obscure situations involving external simulation definitions
;;; at more than one level in the subobject tree (see also documentation for
;;; find-external-simulation-definitions-for-variable-if-any).  Nevertheless,
;;; some users may attempt such things and the errors are therefore flagged
;;; using frame notes and posted warnings.  Variables with such problems are
;;; not simulated and their status is 'bad.

;;; An error is flagged when a variable is designated by two different external
;;; simulation definitions at different levels in the subobject hierarchy.  For
;;; example, suppose variable V1 is in an attribute of object B1 which is of
;;; class B.  Suppose also that object B1 is in an attribute of object A1 which
;;; is of class A.  Finally, suppose that external-simulation-definitions exist
;;; for both A and B and both designate V1 in the
;;; output-vector-from-external-simulator slot.  Such a case is flagged as an
;;; error for the variable; a frame note is put on the variable, a warning note
;;; is posted, and the variable is not simulated.  Note however that no frame
;;; note is posted on the parent entities and they will still be simulated
;;; externally, thus providing values for variables that don't have problems.
;;; An argument could be made that this situation should not be flagged as an
;;; error and that the "shorter" designation should be applied to the variable.
;;; Consider doing this if it customers want it.  See also documentation for
;;; find-external-simulation-definitions-for-variable-if-any for another
;;; example of this issue.

;;; An installation error is not currently flagged if a variable designated
;;; by some external simulation definition does not exist in the attribute of 
;;; the entity designated.  The entity will be simulated at runtime and a
;;; level 3 warning put up indicating that the variable is missing.  This
;;; allows overiding external simulations with constants, a reasonable thing
;;; to allow.

;;; An important point to note about the above errors is that they are localized 
;;; to variables;  they don't affect installation or simulation of any parent 
;;; entities.  This greatly simplifies the complexity of the installation logic
;;; since put-attribute, when it calls install-externally-simulated-variable,
;;; does not have to worry that the installation of some parent entity has
;;; changed.

;;; See also find-external-simulation-definition-for-variable-if-any.


;;; Installation Errors for Entities


;;; Installation Errors for External Simulation Definitions


;;; Runtime Errors

;;; Broken ICP Connections

;; writing-icp-message-group, checking if external-simulator-interface-icp-socket
;; is non-nil, warn-of-loss-of-connection-to-external-simulator


;;;; Test Procedure for External Simulator Installation

;; Checking installation of externally simulated objects is done by checking
;; externally-simulated-entities, and the simulation-details (simulation-frame?,
;; simulation-category?) slot of all externally simulated variables.  All objects
;; that should be simulated externally should be in externally-simulated-entities
;; and the simulation details slot of all variables that should be simulated
;; externally should be 'external.  Also check the
;; external-simulation-definition-for-entity slot.  The simulation details slot,
;; external-simulation-definition-for-entity slot, and
;; externally-simulated-entities are all affected by frame status of relevent
;; external-simulation-definitions; if the frame status is bad, these should all
;; be in a state that is the same as if the external-simulation-definition did not
;; exist.  The external-simulation-definitions-for-attribute and
;; external-simulation-definition-for-class properties should also be checked at
;; each point.  Note that these properties are not affected by frame status of the
;; external-simulation-definition, they are maintained regardless of the frame
;; status.


;; 1.  Load "ma:>agh>xs-test1.kb".  Check installation of externally
;; simulated objects.

;; 2.  Edit the external-simulation-definition for water-tank so that the
;; output-vector-from-external-simulator slot does not contain "the level of the
;; water-tank".  Check to make sure that the variables in the level slot of each
;; water-tank are deinstalled.  Edit the slot again putting the designation back
;; in.  Check to make sure that the variables are installed.

;; 3.  Delete the external-simulation-definition for water-tank.  Make sure
;; everything is deinstalled correctly.  Create the 
;; external-simulation-definition again.  Check installation.

;; 4.  Delete and create instances of water-tank.  Check installation at each
;; point.  Cloning water-tanks should be included in the tests.

;; 5.  Check cases with frame hierarchies to make sure the external simulation
;; definitions overide correctly.  
;; - Load xs-test1.
;; - Delete instances of water-tank.
;; - Add tank, a superclass of water-tank.
;; - Add external-simulation-definition for tank, similar to one for water-tank
;;   except that the output-vector-from-external-simulator slot contains a
;;   designation for outflow rather than level.
;; - Create instance of tank and watertank.  Check installation.
;; - Delete external-simulation-definition for water-tank. Check installation.
;;   Make sure that in the water-tank, outflow, rather than level is simulated
;;   externally.
;; - Put external-simulation-definition for water-tank back in.  Check installation.
;;   Level, rather than outflow, should now be simulated externally in the
;;   water-tank.
;; This test is pretty thorough although more sophisticated tests are possible.

;; 6.  Test all error cases including more than one
;; external-simulation-definition for a variable (see previous notes) and more
;; than one type of simulation specifier for a variable (a
;; generic-simulation-formula and an external-simulation-definition for example).


;;; Runtime Testing of External Simulator

;; 1.  Break ICP connections.






;;;; Notes for Release 2.0

;;; The C files for GSPAN are now maintained on Nevada, just like the other
;;; GSI C files.  The directory is 
;;;   NV:/usr/DATASERVERS/GSPAN_2.0
;;; which is maintained by Guillermo.

;;; The working directory is
;;;   OR:/disc/DATASERVERS/gspan
;;; (see also /GSI_2.0).

;;; The home of all GSPAN sources is on Nevada, as mentioned above.  However, to
;;; do compiles, these sources must be moved to other machines.  The directories
;;; for compiles are as follows.


;;; A neat GSPAN demo is to pull out the connection while running and then plug it
;;; in again.  The simulation will simply pause, and then continue from where it
;;; left off (because it is synchronized).






;;;; SPEEDUP Interface

;;; The SPEEDUP Interface is an extension of GSPAN to allow for a completely
;;; customized interface to SPEEDUP executables which requires no programming on
;;; the part of the user.  This extension may also be useful for subsequent
;;; similar interfaces.  In particular, the vector-to-external-simulator and
;;; vector-from-external-simulator slots of the simulation parameters system table
;;; are generally useful and could eventually be made available as part of the
;;; general GSPAN product.

;;; The relevant files for the SPEEDUP Interface are:

;;; edi_calls.for
;;; edi_bridge.c
;;; sp_xs_main.c
;;; gsi_main_edi.c
;;; make_edi.com
;;; speedup.include
;;; exec.com
;;; run-speedup.com
;;; common-back.sup

;;; soy1.kb
;;; soy1.speedup

;;; master-speedup.com

;;; Edi_calls.for is the fortran file containing definitions for the EDI calls.
;;; These do not do anything themselves, they simply call functions in
;;; edi_bridge.c.  Edi_bridge.c contains the bridge code which makes up the
;;; G2-SPEEDUP interface.  It contains functions called by the SPEEDUP EDI
;;; functions, as well as functions which interface with the GSPAN extension and
;;; functions in sp_xs_main.c.  Sp_xs_main.c has functions that interface with the
;;; GSPAN extension.

;;; Make_edi.com compiles various SPEEDUP interface files but does not link them;
;;; linking is done by speedup.include.  Exec.com and run-speedup.com are command
;;; files used for running SPEEDUP executables.  Common-back.sup is a "virgin"
;;; SPEEDUP runtime database which is copied to common.sup by run-speedup.com so
;;; that the simulation starts fresh each time.  This may become unnecessary if
;;; the mechanism for turning off writing to the database works.

;;; Note that none of these files are part of GSPAN; the GSPAN modules must be
;;; linked to (see speedup.include).  Note also that source code is not provided
;;; for the C file edi_bridge.c, only object code.  Source is, however, provided
;;; for edi_calls.for to allow users to link to these functions for purposes such
;;; as printing data.  Source is also provided for gsi_main_edi.c to allow users
;;; to change the address of the GSPAN extension.  Source is also provided
;;; for the command files to allow for changes to pathnames.  Source is also
;;; provided for speedup.include to allow the user to specify other modules to
;;; link in (with code in edi_calls.for).

;;; Also provided with the interface are the example files soy1.kb, and
;;; soy1.speedup; the G2 knowledge base, and the SPEEDUP database for the soy bean
;;; leaching example.

;;; Master-speedup.com is an in-house only command file for mastering the SPEEDUP
;;; interface.  It resides on "ma:>ab" and on quincy::dua0:[speedup.demo.edi].

;; See also "ma:>agh>specs>speedup-sdd.text" and the file "G2-SPEEDUP Interface"
;; on the agh-memos MAC disc.



;; SPEEDUP Interface To Do

;; Have option to turn off printing of "in edi...".

;; Turn off writing of results to COMMON.SUP by setting WFLAG to 0 in EXTINI (as
;; described in the manual and release notes.  Haven't gotten this to work in the
;; past but try again.  Ask Goom if there are still problems.  If this can be
;; accomplished, then won't have to use common-back.sup kludge.  Also, make sure
;; that speedup.lis doesn't grow when running.

;; Fix kludge of requiring at least one dummy variable simulated in G2.  This is
;; currently necessary because model-variable-group-update-info of
;; main-model-runtime-info is nil if variables are being simulated only in
;; SPEEDUP.  This causes execute-external-simulation-cycle?  to return nil.

;; Send-all-values-at-beginning-of-cycle?  must be set to yes when interfacing
;; with SPEEDUP.  If this is not the case, flag SPEEDUP error.

;; Mode to turn off printing by EDI functions.

;; Try PH control example.  James Goom says that this is a good one for
;; demonstrating configuring the interface to users.

;; Look at readdelv.com in top level SPEEDUP directory.  This takes care of
;; loading the tape and making subdirectories.

;; Convert GSPAN to use IEEE floats.  This will, however, cause problems on
;; Quincy.  Don't do this until SPEEDUP stuff is safely off Quincy.

;; Review timing issues.  Also, there seems to be a problem with a missing 
;; cycle at initialization.

;; Investigate problems of wrong type getting into simulated values.
;; Look at OA1 sensor in soy example.



;; Documentation To Do

;; Figure out directory names for distribution.  Need installation guide.

;; Update user doc regarding sp_xs_main.c (see above).  Also, update user doc
;; regarding run-speedup.com.

;; Mention that gspan modules must be in working directory when making
;; speedup executable.

;; Take make_edi.com out of doc.  Not distributed.

;; For Appendix D, list SPEEDUP related error conditions flagged by G2.
;; For messages sent by EXTMSG from SPEEDUP, just say that these are
;; posted in G2.

;; Need to doc how setting time increment in simulation parameters system table
;; affects things.

;; Documentation needs standard cover and disclaimer (just as GSPAN manual).  Also
;; mark as draft.

;; Send to Prosys for review.  Also have documentation department review this.

;; Send to prospects in database.

;; Make separate document of planned improvements for 3.0.



;;;; Notes for SPEEDUP Interface

;; - The bridge code for the SPEEDUP interface is currently on Quincy in
;; dua0:[speedup.demo.edi].  See speedup.include for a list of object modules that
;; are linked.

;; Currently, it is not possible to link gspan (or gsi) modules on Quincy.  This
;; presents a problem since when running SPEEDUP, the speedup.com file compiles
;; and then attempts to link.  I have solved this for now by putting a set verify
;; in speedup.com before the link in order to see what should be linked.  These
;; object modules can then be copied over to acton::dua0:[usr.agh.speedup-test]
;; and linked there.  A command file for linking for the soy example is
;; link-soy-speedup.com.  The linked image [usr.agh.speedup-test]speedp.exe should
;; be moved to [usr.agh.speedup-dist.executable.scrdisk] to run.  This situation
;; will go away after SPEEDUP is installed on a VMS 5 platform.  

;; For now, don't use master-speedup.com.  Compile all bridge code sources on
;; acton and link there.  The gspan modules don't need to be compiled, the object
;; files can just be brought over to [usr.agh.speedup-test] from the distribution
;; directory.

;; There is, actually, an enormous side benefit to being able to do this.  It
;; allows for making changes in the bridge code, and linking them in, without
;; having to run SPEEDUP at all.



;;;; Making and Running a SPEEDUP Executable with a G2 Interface

;;; First, check [speedup.libdisk]speedup.com to make sure that
;;; link_qualifiers are userlibrary, rather than nouserlibrary.  This is
;;; necessary to allow C library functions to be linked in.

;;; 1.  Get into appropriate directory and get into SPEEDUP.
;;; Ex.  
;;; $ set def [speedup.demo.edi] (groton$dka200:[agh.speedup-bridge] in 3.0)
;;; $ @[speedup.libdisk]splogical.com     
;;; $ speedup CLEAR *
;;;       enter 1 for SPEEDUP standard library database
;;;       enter user name

;;; 2.  Enter problem name and store problem specification.
;;; Ex.
;;; enter command >  new
;;; enter problem name > agh1
;;; enter command >  store soy1

;;; 3.  Run.
;;; Ex.
;;; enter command >  run dyn

;;; SPEEDUP performs the necessary translations and compilations, and links the
;;; modules with the bridge code according to what is in the speedup.include in
;;; the default directory.  It then runs the simulation.  Exit at this point by
;;; doing ctrl-y.

;;; An executable can now be made using the following steps (see also "The SPEEDUP
;;; Newsletter", Issue 5, October 1989).

;;; 4.  Create an empty directory (the executable directory) and copy the
;;; following files from your working problem:
;;;   COMMON.SUP
;;;   SPEEDUP.LIS
;;; Also copy the following files from the bridge code directory to the
;;; executable directory:
;;;   exec.com
;;;   run-speedup.com
;;;   common-back.sup

;;; 5.  Create an SCRDISK directory below the executable directory and copy into
;;; it, from the SCRDISK directory for your working problem, any of the following
;;; files that are present:

;;;   SPEEDP.EXE
;;;   SPEEDUP.SCRATCH    SPMINOS.FILE13
;;;   SUPLIST.LIS        SPMINOS.FILE14
;;;   SPEEDUP.FITDATA    SPMINOS.FILE15
;;;   SPEEDUP.EXTDATA    SPMINOS.FILE16
;;;   RTMSFT.PCB         SPMINOS.FILE17
;;;   SPMINOS.SPECS      SPMINOS.FILE19
;;;   SPMINOS.FILE12     SPMINOS.FILE20

;;; Also copy the file RTMSFT.PCB into this directory from the 'libdisk'
;;; directory, by doing
;;;   COPY 'libdisk'RTMSFT.PCB *

;;; 6.  To run, do
;;;   @run-speedup



;;;; SPEEDUP Interface Functional Summary

;;; The sequence of operations for initialization and for simulating a cycle are
;;; as follows.  When the SPEEDUP process is started, it calls EXTINI, the EDI
;;; function for initialization.  This calls c_extini which establishes the
;;; connection with G2 and performs other initialization functions.  C_extini, and
;;; EXTINI then return and the SPEEDUP process begins simulating.  Note that
;;; c_extini will not return until it establishes the connection with G2 and that
;;; a connection with G2 will not be established until the G2 system is started
;;; (the "start" menu selection is chosen from the main menu).

;;; After initialization and before each cycle, the SPEEDUP process calls EXTGET,
;;; the EDI function for inputting external data into SPEEDUP.  This calls
;;; c_extget.  The first time c_extget is called, it sends the EDI tagnames for
;;; SPEEDUP input to G2 so that the variables to which they refer can be cached.
;;; C_extget then waits for data from G2.  On subsequent calls to c_extget, it
;;; skips sending the EDI tagnames and simply waits for input data.  When the data
;;; arrives, it puts it into the EDI values vector and returns.  Note that
;;; c_extget will not return until it receives input data from G2.  This ensures
;;; that G2 and SPEEDUP are synchronized.

;;; At the end of each cycle, the SPEEDUP process calls EXTPUT, the EDI function
;;; for outputting data from SPEEDUP.  This calls c_extput.  The first time
;;; c_extput is called, it sends the EDI tagnames for SPEEDUP output to G2 so that
;;; the variables to which they refer can be cached.  C_extput then sends the
;;; output data in the EDI values vector to G2.  On subsequent calls to c_extput,
;;; it skips sending the EDI tagnames and simply sends the output data.  After the
;;; output data is sent, c_extput returns and SPEEDUP begins the next simulation
;;; cycle or terminates.

;;; At the end of a simulation, the SPEEDUP process calls EXTTRM, an EDI function.
;;; This calls c_exttrm, which sends a message to G2 indicating that the
;;; simulation is finished.  G2 will then stop sending data to the SPEEDUP
;;; process.  Note that this does not cause a reset of G2; G2 is not reset until
;;; the "reset" menu selection is chosen from the main menu.

;;; G2 will abort the SPEEDUP process upon reset.  This is accomplished via the
;;; GSPAN extension function xsim_shutdown, which is called upon reset of G2.
;;; Xsim_shutdown sets the flag sp_shutdown.  The functions c_extint and c_extget
;;; check this flag and set the iflag error flag if sp_shutdown is set.  This
;;; causes SPEEDUP to terminate and call EXTTRM.  Note that this allows for a nice
;;; mechanism for repeatedly starting and stopping simulations from G2.  The
;;; command file run-speedup.com executes a loop which initializes some files and
;;; then calls exec.com, which calls the SPEEDUP executable.  When the SPEEDUP
;;; executable is terminated, exec.com returns and run-speedup.com loops back to
;;; the beginning.  Thus, the SPEEDUP process is immediately started again and
;;; waits for the next G2 start.



;;;; ICP Messages for SPEEDUP Interface


(def-icp-message-type speedup-begin-tagnames ()
  (with-current-model-for-icp-socket 
    current-icp-socket
    (setf (speedup-tagnames current-model-runtime-info?) nil
	  (speedup-tagnames-tail current-model-runtime-info?) nil)))

(def-icp-message-type speedup-input-or-output-tagnames
		      ((text-string input-or-output-tagnames))
  (with-current-model-for-icp-socket 
    current-icp-socket
    (setf (input-tagnames? current-model-runtime-info?)
	  (string-equalw input-or-output-tagnames #w"INPUT"))))

(def-icp-message-type speedup-tagname ((text-string tagname))
  (with-current-model-for-icp-socket 
    current-icp-socket
    (if (speedup-tagnames-tail current-model-runtime-info?)
	(setf (cdr (speedup-tagnames-tail current-model-runtime-info?))
	      (slot-value-list 
		(convert-speedup-tagname-to-designation tagname))
	      (speedup-tagnames-tail current-model-runtime-info?)
	      (cdr (speedup-tagnames-tail current-model-runtime-info?)))
	(setf (speedup-tagnames current-model-runtime-info?)
	      (slot-value-list 
		(convert-speedup-tagname-to-designation tagname))
	      (speedup-tagnames-tail current-model-runtime-info?)
	      (speedup-tagnames current-model-runtime-info?)))))



(def-icp-message-type speedup-end-tagnames ()
  (define-speedup-end-tagnames))

(defun-allowing-unwind define-speedup-end-tagnames ()
  (with-current-model-for-icp-socket 
    current-icp-socket
    (setf (speedup-output-vector-cache current-model-runtime-info?) nil
	  (speedup-output-vector-cache-tail current-model-runtime-info?) nil)
    (if (input-tagnames? current-model-runtime-info?)
	(change-vector-to-external-simulator 
	  (speedup-tagnames current-model-runtime-info?))
	(change-vector-from-external-simulator 
	  (speedup-tagnames current-model-runtime-info?)))
    (cond
      ((input-tagnames? current-model-runtime-info?)
       (send-speedup-input)
       (writing-icp-message-group
	 ((icp-output-port (external-simulator-interface-icp-socket
			     current-model-runtime-info?)))
	 (send-icp-end-simulation-input-for-cycle)))
      (t					       ; output tagnames, cache variables
       (let ((current-computation-flags current-computation-flags)
	     (*current-computation-frame* simulation-parameters))
	 (setf (role-serve-inactive-objects?) t)
	 (loop for designation 
		   in (current-vector-from-external-simulator)
	       as variable-or-parameter? 
		  = (evaluate-designation designation nil)
	       do
	   (cond
	     ((not (variable-or-parameter-p variable-or-parameter?))
	      (speedup-tagname-not-variable 
		designation variable-or-parameter?))
	     ((and (simulation-runtime-information? variable-or-parameter?)
		   (not (externally-simulated-variable-p variable-or-parameter?)))
	      (speedup-simulation-conflict designation variable-or-parameter?))
	     (t
	      (make-simulation-info-for-speedup-variable variable-or-parameter?)
	      (let ((new-variable-simulation-runtime-structure
		      (make-and-initialize-variable-simulation-runtime-structure
			variable-or-parameter?)))
		(if (speedup-output-vector-cache-tail current-model-runtime-info?)
		    (setf (cdr (speedup-output-vector-cache-tail 
				 current-model-runtime-info?))
			  (simulate-list new-variable-simulation-runtime-structure)
			  (speedup-output-vector-cache-tail current-model-runtime-info?)
			  (cdr (speedup-output-vector-cache-tail 
				 current-model-runtime-info?)))
		    (setf (speedup-output-vector-cache current-model-runtime-info?)
			  (simulate-list new-variable-simulation-runtime-structure)
			  (speedup-output-vector-cache-tail current-model-runtime-info?)
			  (speedup-output-vector-cache current-model-runtime-info?)))
		(begin-collecting-data-for-simulated-variable-if-appropriate
		  variable-or-parameter?)
		)))))))))

;; The speedup-simulation-conflict check should result in a simulation
;; error, not just a warning!



(defun make-simulation-info-for-speedup-variable (variable-or-parameter)
  (let ((simulation-info?
	  (get-or-make-simulation-info variable-or-parameter t)))
    (setf (simulation-info? variable-or-parameter) simulation-info?
	  (simulation-category simulation-info?) 'external)))

;; Make-simulation-info-for-speedup-variable is used here instead of
;; put-external-simulation-formula-into-variable-or-parameter in order
;; to avoid the extra installation performed by the latter, which is not
;; appropriate for variables simulated by Speedup.



(def-icp-message-type speedup-begin-values ()
  (with-current-model-for-icp-socket 
    current-icp-socket
    (setf (speedup-output-vector-cache-tail current-model-runtime-info?)
	  (speedup-output-vector-cache current-model-runtime-info?))))



(def-icp-message-type speedup-value ((float value))
  (with-current-model-for-icp-socket 
    current-icp-socket
    (store-new-simulation-value
      (car (speedup-output-vector-cache-tail current-model-runtime-info?)) value)
    (update-variable (corresponding-variable 
		       (car (speedup-output-vector-cache-tail
			      current-model-runtime-info?))))
    (when (cdr (speedup-output-vector-cache-tail
		 current-model-runtime-info?))	; should always be true
      (setf (speedup-output-vector-cache-tail current-model-runtime-info?)
	    (cdr (speedup-output-vector-cache-tail
		   current-model-runtime-info?))))))



;(def-icp-message-type speedup-end-values ()
;  nil
;  )

;; Not needed.



;; The messages speedup-begin-values, speedup-value, and speedup-end-values are
;; used for both input and output.  This approach should be used for the rest of
;; GSPAN as well!





(defun-allowing-unwind send-speedup-input ()
  (when (current-vector-to-external-simulator)
    (writing-icp-message-group
      ((icp-output-port (external-simulator-interface-icp-socket 
			  current-model-runtime-info?)))
      (send-icp-speedup-begin-values)
      (let ((current-computation-flags current-computation-flags)
	    (*current-computation-frame* simulation-parameters)
	    (current-simulation-runtime-structure nil)
	    (do-not-update-simulated-value? t))
	(setf (role-serve-inactive-objects?) t)
	(setf (simulator-step-flag current-model-runtime-info?)
	      'calculating-state-variables)
	(loop for designation in (current-vector-to-external-simulator)
	      as input-value = (sim-eval-variable-for-designation designation nil)
	      do
	  (if (numberp input-value)
	      (send-icp-speedup-value input-value)
	      (speedup-input-value-not-a-number designation input-value))))
;      (send-icp-speedup-end-values)
      )))




(defun shutdown-speedup-simulation ()
  (with-current-model-for-icp-socket 
    current-icp-socket
    (reclaim-simulate-list 
      (speedup-output-vector-cache current-model-runtime-info?))
    (setf (speedup-output-vector-cache current-model-runtime-info?) nil
	  (speedup-output-vector-cache-tail current-model-runtime-info?) nil)))




;;;; EDI Tagname Parser



;;; A speedup tagname can be one of the following:

;;; speedup-tagname -> name
;;; speedup-tagname -> 'the attribute-name 'of speedup-tagname

;;; The simple parser below converts strings of this form into G2 designations
;;; (name or attribute designations).  If the grammar for speedup tagnames ever
;;; becomes more complicated (unlikely) a more general parsing scheme should be
;;; used.


;; Note that ICP text-string args are reclaimed automatically when exiting the
;; ICP handler.




(defvar speedup-tagname-string-index)
(defvar speedup-tagname-string)

(defun convert-speedup-tagname-to-designation (speedup-tagname-string)
  (let ((speedup-tagname-string-index 0))
    (parse-first-symbol-for-speedup-tagname)))

(defun parse-first-symbol-for-speedup-tagname ()
  (let ((first-symbol (get-next-speedup-tagname-symbol)))
    (cond 
      ((not first-symbol)
       (incorrect-format-for-speedup-tagname speedup-tagname-string))
      ((eq first-symbol 'the)
       (parse-attribute-name-for-speedup-tagname))
      (t  ; if name
       first-symbol))))

(defun parse-attribute-name-for-speedup-tagname ()
  (let ((attribute-name (get-next-speedup-tagname-symbol)))
    (cond 
      ((or (null attribute-name) 
	   (memq attribute-name '(of the)))
       (incorrect-format-for-speedup-tagname speedup-tagname-string))
      (t  ; attribute name
       (slot-value-cons 
	 'the 
	 (slot-value-cons 
	   attribute-name
	   (parse-after-attribute-for-speedup-tagname)))))))

(defun parse-after-attribute-for-speedup-tagname ()
  (if (not (eq (get-next-speedup-tagname-symbol) 'of))
      (incorrect-format-for-speedup-tagname speedup-tagname-string))
  (let ((name-or-attribute-designation
	  (get-next-speedup-tagname-symbol)))
    (cond 
      ((or (null name-or-attribute-designation)
	   (eq name-or-attribute-designation 'of))
       (incorrect-format-for-speedup-tagname speedup-tagname-string))
      ((eq name-or-attribute-designation 'the)
       (parse-attribute-name-for-speedup-tagname))
      (t  ; name
       (slot-value-list name-or-attribute-designation)))))

(defun get-next-speedup-tagname-symbol ()
  (multiple-value-bind (next-symbol? next-string-index)
      (read-symbol-from-text-string
	speedup-tagname-string speedup-tagname-string-index)
    (cond
      (next-symbol?
       (setq speedup-tagname-string-index next-string-index)
       next-symbol?)
      (t
       (non-symbol-in-speedup-tagname
	 speedup-tagname-string-index speedup-tagname-string)
       nil))))

;; Note that speedup-tagname-string is known to be a legal text string,
;; which it must be, because it comes through ICP, which will only pass
;; legal text strings through.







;;;; SPEEDUP Error Handlers



(def-simulation-error-handler non-symbol-in-speedup-tagname
			      (start-index tagname-string)
  (warning-message* 1
    "Unable to read a symbol beginning with character ~d in the SPEEDUP tagname ~s."
    start-index tagname-string))



(def-simulation-error-handler incorrect-format-for-speedup-tagname 
			      (tagname-string)
  (warning-message* 1
    "The SPEEDUP tagname ~a does not have the correct format." tagname-string))



(def-simulation-error-handler speedup-tagname-not-variable
			      (designation variable-or-parameter?)
  (warning-message* 1
    "The SPEEDUP output designation ~s refers to ~s, which is not a variable or parameter."
    designation variable-or-parameter?))



(def-simulation-error-handler speedup-simulation-conflict
			      (designation variable-or-parameter?)
  (warning-message* 1
    "The SPEEDUP output designation ~s refers to ~s which is already being simulated. ~
    Please check if this variable is designated more than once by SPEEDUP tagnames, or ~
    if it is being simulated by G2."
    designation variable-or-parameter?))



(def-simulation-error-handler speedup-output-variable-deleted ()
  (warning-message* 1
    "A variable simulated by SPEEDUP has been deleted."))



(def-simulation-error-handler speedup-input-value-not-a-number
			      (designation input-value)
  (warning-message* 1
    "The SPEEDUP input designation ~s evaluates to ~s, which is not a number."
    designation input-value))



(defun delete-from-external-simulation-runtime-structures
       (variable-simulation-runtime-structure)
  (declare (ignore variable-simulation-runtime-structure))
;  (if (memq variable-simulation-runtime-structure 
;	    speedup-output-vector-cache)
;      (speedup-output-variable-deleted)))
  )

;; Make model-specific!


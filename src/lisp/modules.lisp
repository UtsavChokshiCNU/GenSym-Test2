;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module MODULES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David

(declare-forward-reference name-of-module-being-read? variable)
(declare-forward-reference main-kb-being-read? variable)
(declare-forward-reference system-tables-read-for-this-module variable)
(declare-forward-reference stack-of-deferred-notification-strings variable)
(declare-forward-reference try-to-do-deferred-user-notifications function)
(declare-forward-reference inform-ui-client-interfaces-of-module-creation function)
(declare-forward-reference delete-block-after-reading-kb function)
(declare-forward-reference inform-ui-client-interfaces-of-module-deletion function)
(declare-forward-reference clone-frame function)
(declare-forward-reference parse-text-for-slot function)
(declare-forward-reference multiple-add-to-results-for-inspect-command function)
(declare-forward-reference make-message function)
(declare-forward-reference make-short-representation function)
(declare-forward-reference collect-bad-definitions-for-kb function)
(declare-forward-reference get-module-block-is-in function)
(declare-forward-reference read-symbol-from-text-string function)
(declare-forward-reference update-saving-parameters-status-attributes function)
(declare-forward-reference source-code-control-support-enabled-p variable)
(declare-forward-reference recompute-editability-of-modules function)
(declare-forward-reference restrict-edits-to-modules-having-read-only-files-p variable)
(declare-forward-reference enable-scc-check function)
(declare-forward-reference add-source-code-control-grammar function)
(declare-forward-reference miscellaneous-parameters variable)




;;;; System Frames


;;; A `system frame' (aka `system table') is a special "one-of-a-kind" frame
;;; that holds parameters for part of the G2 system.  Previously, system
;;; frames had the following restrictions.  A system frame
;;; 
;;;   (1) must be a subclass of system-table in the class hierarchy;
;;;   
;;;   (2) must have among its name(s) the names of each class of which it is
;;;   a subclass that is a proper subclass of system-table;
;;;
;;;   (3) must be the value of the special variable(s) of that are the same
;;;   symbols as required in the set of names in (2); and
;;;
;;;   (4) must reside in some entry in the a-list
;;;   modules-and-system-tables-a-list

;;; Only proper subclasses of SYSTEM-TABLE may have instances instantiated.
;;; [Prior o 4.0, these classes were not permitted to have proper subclasses,
;;; but that restriction has been lifted as of 4.0.]
;;;
;;; A subclass of SYSTEM-TABLE may not, at present, have more than one direct
;;; superior class (i.e., may not multiply inherit).

;;; As (3) implies, there is always a (kb-specific) variable corresponding to
;;; each proper subclass of SYSTEM-TABLE, except in the (degenerate) case of
;;; a completely obsolete class.
;;;
;;; As (2) and (3) implies, if SYSTEM-TABLE < A < B, where "<" is the
;;; subclass relation, then there should be a variable named A and B, and A
;;; should be bound to an instance of the class A, and B should be bound to
;;; an instance of the class B.  Note that this allows for there to be just
;;; one instance that both A and B are bound to: if A and B are bound to the
;;; same instance, it would have to be and instance of B.
;;;
;;; There is an example of this in the current G2 (4.0) software:
;;; SYSTEM-TABLE < KB-RESTRICTIONS < KB-CONFIGURATION, where "<" is the is
;;; the subclass relation, and both KB-RESTRICTIONS and KB-CONFIGURATION are
;;; always bound to the same instance, an instance of KB-CONFIGURATION.  And
;;; this instance has among its names both KB-CONFIGURATION and
;;; KB-RESTRICTIONS.  Things were arranged this way in order to allow
;;; applications using the old (pre-4.0) name, kb-restrictions, but to have
;;; the new name, kb-configuration phased in.
;;;
;;; This kind of setup is now directly supported by def-system-frame, q.v.
;;;
;;; When the system-tables menus is presented to the user, it contains the
;;; system-table subclasses that are furthest from the root class
;;; SYSTEM-TABLE.  E.g., it will contain KB-CONFIGURATION, but not
;;; KB-RESTRICTIONS.

;;; The initialize method of a system frame may not have major side affects.
;;; And the slot putters of a system frame may not have major side affects
;;; unless the system frame is installed.  Similarly, the reclaimers and
;;; cleanup methods of a system frame should not expect their side effects
;;; to be in effect, and therefore in need of undoing, unless the system
;;; frame is installed.

;;; A system frame, f, is said to be `installed' (an `installed system
;;; table') if (system-table-installed-p f) is true.  That predicate is
;;; implemented at present as a test of the slot
;;; (this-system-table-is-installed? f), but that implementation is subject
;;; to change, and only the system-table-installed-p predicate is exported
;;; for use.
;;;
;;; Also, for f, an installed system table, it is guaranteed that for each
;;; name, n, that is, or is an element of, (name-or-names-for-frame f)
;;;
;;;    (get-instance-with-name-if-any (class f) n)
;;;
;;; returns f, assuming there are no other (non-system table) items with the
;;; same name as f.
;;;
;;; Finally, the symbol that is (class f) is bound to f itself. This feature
;;; is taken advantage by the inference engine to make references to the
;;; installed system table fast.

;;; When a system frame is installed, its install-system-table method is
;;; called.  This gives it an opportunity to have the side effects it might
;;; have skipped in its slot putters if they were called when it was not
;;; installed.

;;; Similarly, when a system frame is deinstalled (or uninstalled), its
;;; deinstall-system-table method is called.  

;;; System tables should only be referred to through the Lisp variable
;;; binding of their class names.  Slot putters, initialize methods, cleanup
;;; methods, and install-system-table and deinstall-system-tables may not
;;; refer to other classes of system tables during their execution, since
;;; there may or may not be any installed then.  [More here about when there
;;; are system tables, contraints at times like when reading a new KB, during
;;; post-loading functions, etc.!]

;;; In releases of G2 prior to 4.0, all slots of system frames were saved; in
;;; 4.0, system-frame slots are saved like other slots, i.e., only if they
;;; have non-default values.
;;;
;;; Furthermore, in 4.0, system frames that have all defaulted values in all
;;; of their slots except name-or-names-for-frame,
;;; this-system-table-is-installed?, and module-system-table-belongs-to?, are
;;; not saved at all.  They are instead reconstructed upon loading.
;;;
;;; System frames, as of 4.0 (4/13/94, in development) had the
;;; frame-author-or-authors slot exposed to users. They benefit greatly from
;;; the extra auditing this provides, and at very low cost given their small
;;; number of instances.  Unlike most (if not all) classes with this feature
;;; enabled, they are not strictly speaking "definitional" items, as that
;;; term is defined in KB-MERGE.  It doesn't complicate the story too much
;;; more to say that this feature "is available on definitional items and
;;; system tables", for those even interested in it at all.  (By the way, it
;;; is conceivable that they would some day become "definitional" items.  A
;;; scheme to be considered another day.)

(def-class (system-frame entity)		; should not allow instances!

  (name-or-names-for-frame nil do-not-put-in-attribute-tables)

  (frame-author-or-authors nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))

  (this-system-table-is-installed?
    nil do-not-put-in-attribute-tables
    system vector-slot save
    (attribute-export-comment "Export, boolean, writable = false"))

  (module-system-table-belongs-to?
    nil do-not-put-in-attribute-tables		; maybe DO later! 
    system vector-slot save
    (attribute-export-comment "Export, symbol, writable = false")))

;; Historical:  documentation for system frames prior to 8/91:  (MHD 9/22/91)
;; 
;; ;;; A `system frame' is a special "one-of-a-kind" frame that holds parameters for
;; ;;; part of the G2 system.  A system frame (1) must be the only instance of its class,
;; ;;; (2) must have a class this is under system-frame in the class hierarchy, (3) must
;; ;;; have a single name (in its name-or-names-for-frame slot) that is the same as its
;; ;;; class; and (4) must be the value of the kb-specific variable whose name is its name.
;;
;; ;; Consider changing "system frame" to "unique frame" and "system table" to "special table".


;;; The class `system-table' is a subclass of system-frame.  This class was
;;; slipped into the class hierarchy in between system-frame and all of its
;;; subclasses (e.g. logbook-parameters, et al) to allow us to move system-
;;; table into the class item.  Changing the name of system-frame was too
;;; daunting a task to contemplate.

(def-class (system-table (item system-frame) not-normally-transient))

;; The only other changes associated with the introduction of this class was
;; to replace system-frame with system-table in the expansion of the macro
;; below and to add system-table to the list subclasses-of-item.
;; (MHD/BAH 6/26/90)



;;; `Def-system-frame' defines a system frame, the class and name for which is
;;; system-frame-name.  If class-or-linearized-subclasses is a list, it should
;;; be a list of one or more elements, (C1 C2 C3 ... CN), such that
;;;
;;;     C1 < C2 < C3 < ... < CN < system-table
;;;
;;; where each Ci is a class, and "<" is the subclass relation.  This will
;;; generate a succession of def-class forms like
;;;
;;;    (def-class (CN system-table) . slot-definitions)
;;;    (def-class (CN-1 CN))
;;;    .
;;;    .
;;;    .
;;;    (def-class (C2 C3))
;;;    (def-class (C1 C2))
;;;
;;; And then this will arrange for just the one instance to be created, an
;;; instance of the class C1.  There will be kb-specific variables declared
;;; for the symbols C1..CN, and each of these will be initialize in a new
;;; KB the one instance of C1.
;;;
;;; If class-or-linearized-subclasses is an atom, the effect is the same
;;; as if C1 = CN.

;;; An example of how this is to be used is to declare the (new) system-table
;;; subclass kb-configuration, as a subclass of the (old) class kb-restrictions
;;;
;;;    (def-system-frame (kb-configuration kb-restrictions) filters
;;;       ... { <slot definition> } ...
;;;       )
;;;
;;; This has the effect of having both kb-configuration and kb-restrictions be
;;; bound to an instance of kb-configuration, a class that is a subclass of
;;; kb-restrictions, and is identical to it in terms of all its slots and class
;;; features.

(defmacro def-system-frame
    (class-or-linearized-subclasses module-name &body slot-definitions)
  (let ((linearized-subclasses
	  (if (atom class-or-linearized-subclasses)
	      (list class-or-linearized-subclasses)
	      class-or-linearized-subclasses)))
    `(progn
       ,@(reverse
	   (loop for classes on linearized-subclasses
		 collect `(def-class (,(first classes)
				       ,(if (cdr classes) (second classes) 'system-table)
				       not-normally-transient)
			    . ,(if (null (cdr classes)) slot-definitions))))
       ,@(loop for previous-class? = nil then (first classes)
	       as classes on linearized-subclasses
	       collect `(def-kb-specific-variable ,(first classes) ,module-name
			  ,(if previous-class?
			       `(:funcall symbol-value ,previous-class?)
			       :system-frame))))))


;;; `Sort-slot-value-list-by-example' takes two lists.  The first list is
;;; sorted into the order implied by the elements in the second list.  Any
;;; elements not given in the second list are put on the end of the result
;;; in their original order.  The slot-value conses of the original list
;;; are reclaimed.

(defun sort-slot-value-list-by-example (list-to-sort list-in-default-order)
  (loop with result = nil
	with elements-to-put-on-end
	for element in list-in-default-order
	when (memq element list-to-sort)
	  do (slot-value-push element result)
	finally
	  (loop for element in list-to-sort
		unless (memq element result)
		  do
		    (slot-value-push element elements-to-put-on-end))
	  (reclaim-slot-value-list list-to-sort)
	  (return (nreverse
		    (nconc (nreverse elements-to-put-on-end)
			   result)))))



;;; `compute-system-table-choices' returns a slot value list of system frame
;;; classes (and names and variables).
(defparameter order-of-system-tables-in-menu
  '(debugging-parameters
    timing-parameters
    inference-engine-parameters
    data-server-parameters
    g2gl-parameters
    simulation-parameters 
    kb-configuration
    printer-setup
    message-board-parameters
    logbook-parameters
    log-file-parameters
    color-parameters
    language-parameters
    fonts
    editor-parameters
    menu-parameters
    miscellaneous-parameters
    item-reference-parameters
    drawing-parameters
    saving-parameters
    module-information
    version-control-parameters
    server-parameters))


(defun compute-system-table-choices (&optional exclude-this-window)
  (nconc
    (when (and servicing-workstation? (not exclude-this-window))
      (let ((g2-window-for-this-workstation?
	      (g2-window-for-this-workstation? current-workstation)))
	(when g2-window-for-this-workstation?
	  (slot-value-list 'this-window))))
    
    (sort-slot-value-list-by-example
      (loop for module-name in (system-modules current-system-name)
	    nconc (loop for (system-variable-name initialization)
			    in (system-variable-descriptions module-name)
			when (eq initialization :system-frame)
			  collect system-variable-name using slot-value-cons))
      order-of-system-tables-in-menu)))





;;; Make-system-frame ..

(defun make-system-frame (class)
  (let ((system-frame (make-frame class)))
    (set-permanent-block system-frame)
    (when noting-changes-to-kb-p
      (set-block-permanently-changed-function system-frame))
    (put-name-or-names-for-frame
      system-frame 
      (compute-name-of-system-frame class)
      t)
    system-frame))


;;; The function `clone-system-frame' clones an existing system frame and sets
;;; its name-or-names attribute (which is not cloned because it's a DO-NOT-CLONE
;;; attribute).

(defun clone-system-frame (old-system-frame)
  (let ((system-frame (clone-frame old-system-frame)))
    (put-name-or-names-for-frame
      system-frame 
      (compute-name-of-system-frame (class system-frame))
      t)
    system-frame))


;;; The function `compute-name-of-system-frame' computes name-or-names for a
;;; system frame.  The value is usually just the class name, but in general is
;;; a list of all of the class names in the inheritance path, up to
;;; system-table.

(defun compute-name-of-system-frame (class)
  (let ((names
	  (loop for class-name = class
			       then (first (direct-superior-classes class-name))
		until (eq class-name 'system-table)
		collect class-name using slot-value-cons)))

    (cond ((singleton? names)
	   (prog1 (first names)
	     (reclaim-slot-value-cons names)))
	  (t
	   names))))




;;; `Install-system-table' does the following:
;;;
;;;   (1) sets the (Lisp) variable whose name is
;;;     (class system-table) to system-table; and
;;;
;;;   (2) sets the this-system-table-is-installed? slot
;;;     of system-table to true; and
;;;
;;;   (3) makes system-table be the first element in
;;;       (frame-or-frames-with-this-name (class system-table))
;;;       so that
;;;          (get-instance-with-name-if-any class name)
;;;       will get system-table, where class and name
;;;       are both (class system-table); and
;;;     
;;;   (4) calls the install-system-table method, if
;;;     any, on system-table; and
;;;
;;;   (5) calls the activate-if-possible-and-propagate
;;;     method on system-table if system-is-running.
;;;
;;; This assumes that the class of system-table is a defined variable
;;; that should be set to the instance, and that each superior class
;;; up until, but not including, SYSTEM-TABLE, should also be set in
;;; the same manner to system-table.  This also assumes that none
;;; of the classes set will have more than one direct superior class.

(defun install-system-table (system-table)
  (set (class system-table) system-table)
  (loop for class
	  = (first (direct-superior-classes (class system-table)))
	  then (first (direct-superior-classes class))
	until (eq class 'system-table)	; can't fail
	do (set class system-table))		  
  (setf (this-system-table-is-installed? system-table) t)

  (ensure-named-frame-is-first-fetched system-table)
    
  (funcall-method-if-any 'install-system-table system-table)
  (if (or system-is-running system-has-paused)
      (funcall-method
	'activate-if-possible-and-propagate system-table)))




;;; Deinstall-system-table does the following:
;;;
;;;   (1) sets the (Lisp) variable whose name is
;;;     (class system-table) to nil; 
;;;     
;;;   (2) calls the deinstall-system-table method, if
;;;     any, on system-table; and
;;;
;;;   (3) calls the deactivate-and-propagate method
;;;     on system-table.

(defun deinstall-system-table (system-table)
  (set (class system-table) nil)
  (setf (this-system-table-is-installed? system-table) nil)
  (funcall-method-if-any 'deinstall-system-table system-table))





;;; The `install-system-table method' is optionally to be be defined
;;; for system tables that have some side effect based on their slots.
;;; It is not called with any arguments.

(def-generic-method install-system-table (system-table)
  )

;;; The `deinstall-system-table method' should be optionally defined on most
;;; subclasses of system-table.  ....

(def-generic-method deinstall-system-table (system-table)
  )



;;; `with-normal-system-table-inferior-classes' is used to help abstract the hackery
;;; involved with the server-parameters system-table (see below).  We don't
;;; often want to let the normal system-table-related functions see it, so we
;;; provide this as a way to hide it easily.  This form takes a user-supplied
;;; variable which will be bound to a gensym-list of all of the subclasses of
;;; system-table except server-parameters wihtin the body. Don't hold onto the list
;;; bound to the variable.  Copy it if it's needed.

(defmacro with-normal-system-table-inferior-classes ((var) &body body)
  (let ((classes (gensym))
	(class-var (gensym)))
    `(let* ((,classes (inferior-classes 'system-table))
	    (scope-conses scope-conses)
	    (,var (loop for ,class-var in ,classes
			unless (eq ,class-var 'server-parameters)
			  collect ,class-var using scope-cons)))
       ,@body)))



;;; `Modules-and-system-tables-a-list' is a variable bound to a `modules and
;;; system frames alist', which is of the form
;;;
;;;     (  { (module-information . other-system-tables) }+  )
;;;
;;; where each module-information is a unique module-information system
;;; table with a unique value for (top-level-kb-module?
;;; module-information).  Note that there must always be at least one
;;; entry in the a-list.  Note also that NIL is one of the possible
;;; values for (top-level-kb-module? module-information).

;;; Each entry in this a-list contains a set of system tables for one
;;; KB.  The entire a-list is composed of slot value conses.   Modules-and-
;;; system-frames is a kb-specific variable.  It is automatically reclaimed
;;; using reclaim-slot-value.  It is not automatically initialized; rather,
;;; it is explicitly initialized by switch-to-new-empty-kb after all kb-
;;; specific variables have been initialized, which is when the basic set of
;;; system tables is initially created.  It is also added to and altered
;;; when new KB's are merged in; see KB-* modules.

;;; Note that server-parameters (see below) never gets put onto the list and
;;; should never be.

(def-kb-specific-variable modules-and-system-tables-a-list
			  modules :no-initial-value nil
			  reclaim-slot-value-tree-function)



;;; `Initialize-modules-and-system-tables-a-list' is called by switch-to-new-
;;; empty-kb to initialize the variable modules-and-system-tables-a-list, as
;;; described above.

(defun initialize-modules-and-system-tables-a-list ()
  (setq modules-and-system-tables-a-list
	(create-initialized-system-tables-suite module-information)))


;;; `Create-initialized-system-tables-suite' is called by
;;; initialize-modules-and-system-tables-a-list and delete-top-level-module.  It
;;; creates a default set of system-tables.

(defun create-initialized-system-tables-suite (module-information-instance)
  (slot-value-list
    (with-normal-system-table-inferior-classes (system-table-classes)
      (loop with result = (slot-value-list module-information-instance)
	    for class in system-table-classes
	    as system-table-instance = (symbol-value class)
	    unless (or (eq class 'module-information)
		       (memq system-table-instance result))
	      do (nconc result (slot-value-list system-table-instance))
	    finally (return result)))))



;;; `System-table-installed-p' is true if system-table is currently installed.

(defun system-table-installed-p (system-table)
  (this-system-table-is-installed? system-table))

;; Previously, the definition was
;;
;;   (and (boundp (class system-table))            ; nec.?
;;        (eq (symbol-value (class system-table)) system-table))
;;
;; but that would definitely lose in the case of code within methods, that had
;; no choice, due to current limitations of expression, but to bind the special
;; variable that is their class symbol and thereby make this definition always
;; return true, and make the test, in effect, useless.
;;
;; This was fixed today, a bit late in the 4.0 cycle.  (MHD 6/23/94)
  

(defun system-table-suite-test (module? module-information-instance)
  (eq module?
      (get-slot-value		; fwd. ref.!
	module-information-instance
	'top-level-kb-module?)))

(defun get-system-table-suite-for-module-or-nil (module?)
  (assoc module? modules-and-system-tables-a-list
	 :test #'system-table-suite-test))



;(defun system-table-for-module-p (system-table module)
;  (memq system-table
;	(get-system-table-suite-for-module-or-nil module)))

;; Obsolete. (MHD 6/4/92)


(defun get-system-table-of-class-for-module-or-nil (module? class)
  (let ((system-table-suite?
	  (get-system-table-suite-for-module-or-nil module?)))
    (if system-table-suite?
	(loop for system-table in system-table-suite?
	      when (frame-of-class-p system-table class)
		return system-table))))

;;; Get-system-table-currently-in-force ... returns the system table of
;;; class class which is currently in force, if any.  

(defun get-system-table-currently-in-force (class)
  (if (boundp class)
      (symbol-value class)))


(defun get-module-for-system-table (system-table)
  (loop for system-table-suite
	    in modules-and-system-tables-a-list
	when (memberp system-table system-table-suite)
	  return
	    (get-slot-value		; fwd. ref.!
	      (first system-table-suite)
	      'top-level-kb-module?)))






;;; `Instantiable-system-table-subclass-p' is true if system-table-subclass
;;; may be instantiated.  To be instantiable, a subclass of system-table must
;;; have no inferior classes.

(defun instantiable-system-table-subclass-p (system-table-subclass)
  (null (inferior-classes system-table-subclass)))



;;; `Store-hand-created-module-information-if-appropriate' is a workstation context
;;; return function, to be called by the editor upon a normal return.  Workstation-
;;; context is expected to contain in its workstation-context-return-information
;;; slot a list of the form
;;;
;;;    (module-information frame-reference-serial-number)

;;; This first checks that module-information has not been deleted, doing
;;; nothing if it has been deleted.  Otherwise, if the value in the
;;; top-level-kb-module?  slot is non-nil, and there is no name conflict with an
;;; existing module, then module-information is stored in
;;; modules-and-system-tables-a-list.  If there is a name conflict, then a
;;; notification is posted on the logbook saying that nothing is being done and
;;; why.

;;; Storing module-information involves creating, by cloning, an entire suite of
;;; system tables that will go along with module-information into the ultimately
;;; module (KB file).

;;; This does not reclaim the conses in the return information, since there is
;;; a reclaimer function to perform that, defined below as delete-hand-created-
;;; module-information-if-appropriate

(defun store-hand-created-module-information-if-appropriate (workstation-context)
  (let* ((workstation-context-return-information
	   (workstation-context-return-information workstation-context))
	 (module-information-instance (first workstation-context-return-information))
	 (frame-serial-number (second workstation-context-return-information))
	 (top-level-kb-module?
	   (get-slot-value
	     module-information-instance 'top-level-kb-module?)))
    (unless (frame-has-been-reprocessed-p
	      module-information-instance frame-serial-number)
      (if (cond
	    ((null top-level-kb-module?)
	     ;; doesn't come up in practice due to barrier in parser/compiler, which
	     ;; won't let you type UNSPECIFIED
	     (notify-user
	       "The module-information instance which has just been created is ~
                being discarded because it does not specify any top-level KB ~
                module.")
	     t)
	    ((get-system-table-suite-for-module-or-nil top-level-kb-module?)
	     ;; doesn't come up in practice due to barrier in parser/compiler, which
	     ;; won't let you type the name of an existing module
	     (notify-user
	       "There already is a module-information system table that specifies ~
                the module ~a as its top-level KB module.  Therefore, the ~
                module-information instance which has just been created is being ~
                discarded."
	       (get-slot-value module-information-instance 'top-level-kb-module?))
	     t))
	  (delete-frame module-information-instance)

	  (finish-setup-of-system-table-suite-for-new-module
	    module-information-instance)))
    (exit-current-workstation-context-in-return-function 'editing)))
;;; Delete-hand-created-module-information-if-appropriate is a workstation context
;;; information reclaimer function, to be called by the editor upon exit, either
;;; normal return or an abort.  Its argument is the return information in the
;;; editor workstation context, which is a list of the form 
;;;
;;;    (module-information frame-reference-serial-number)
;;;
;;; If module-information has not been deleted already, and has not been stored
;;; in modules-and-system-tables-a-list, it is deleted.

(defun delete-hand-created-module-information-if-appropriate
    (module-information-frame-serial-number)
  (let ((module-information-instance
	  (first module-information-frame-serial-number))
	(frame-reference-serial-number
	  (second module-information-frame-serial-number)))
    (if (and (frame-has-not-been-reprocessed-p
	       module-information-instance
	       frame-reference-serial-number)
	     (null (assq module-information-instance
			 modules-and-system-tables-a-list)))
	(delete-frame module-information-instance))
    (reclaim-frame-serial-number frame-reference-serial-number)
    (reclaim-slot-value-list module-information-frame-serial-number)
    ))

;; Note that although I think module-information-instance is a little ugly as a
;; variable name above, module-information is special and I would not like to
;; have to distinguish between local-variable and special-variable uses of the
;; symbol module-information.  (MHD 12/5/91)







;;;; KB Modularity


;; Mark David, 5/20/91

;;; The "Level 0" Proposal:  (Lowell's & MHD's)
;;;
;;; 1. Assume no duplicates in any of modules, except among format frames
;;; and system tables.  That is, the modules are disjoint.  For example,
;;; no duplicate definitions are allowed.
;;;
;;; 2. In load sequence, definitions must preceed instances.  And superior
;;; class definitions must preceed inferior class definitions.
;;;
;;; 3. KBs and KLs consist of workspaces.
;;;
;;; 4. A top-level (KB) workspace has an editable attribute the module it
;;; belongs to.
;;;
;;; 5. Save only workspaces from "current" KB (or KL).
;;;
;;; 6. New workspaces belong to "current" KB.
;;;
;;; 7. The module-information system table gives "include" information.
;;;
;;; (7a. For now just have an ordered list of modules to load.)
;;; (7b. Then add a slot to declare dependencies between modules.  And
;;; help users by not allowing them to unintentionally create new
;;; dependencies.)
;;;
;;; 8. Assume no pointers across modules (e.g., frame-representations,
;;; subworkspaces, subblocks, superblock?, superior-of-subworkspace, etc.);
;;; only definitional dependencies or representations across modules --
;;; warn of violations and require acknowledgement if violations found
;;; while saving.
;;;
;;; 9. Only current KB's workspaces retained in pane description.

;;; The "Level 1" Proposal:  (Ben's and MHD's)
;;;
;;; ... [This is really best represented by the paper trail document "KB
;;; Modularity", authored by Ben Hyde.]


;;; Partitioning a KB into Modules.
;;;
;;; Creating a module means creating a new suite of system tables that include
;;; a module-information system table

;;; Some Random Fine Points.
;;;
;;; When a workspace moves to being top-level or away therefrom, the slot
;;; module-this-is-part-of? is changed as appropriate to keep the slot and
;;; all notes in synch with each other and all constraints.  This is managed
;;; by add-subworkspace and remove-as-subworkspace-if-necessary.
;;; 
;;;
;;; When a workspace becomes permanent or ceases to be permanent, nothing is
;;; done.  Transient workspaces are subject to the same constraints as any
;;; others as far as KB Modularity is concerned.  Other parts of the software treat
;;; them differently, e.g., KB saving.  I think this is ok.  On the one hand,
;;; if a user creates a top-level transient KB workspace, and then changes its
;;; module to an unknown one, it may seem dumb to have notes for it, since it will
;;; not be saved anyway.  So, we COULD say that transient workspaces will not
;;; be subject to consistency analysis between workspace module assignments
;;; and the module-information system table.  But the obscurity of it means we're
;;; adding more complexity than is necessary to the bottleneck around making things
;;; transient/permanent as well as to the code that does consistency analysis
;;; between workspace module assignments and the module-information system table.
;;; --- BUT!  But: it wouldn't seem right to make the KB "unsavable" when a
;;; workspace has a note about belonging to a non-existant or unkown module, as proposed
;;; in the paper trail, if you were doing this for transient workspaces!
;;; (MHD 12/18/91) 
;;; 
;;; You can't keep frames in a frame note, and can't easily maintain a count of
;;; frames in a frame note, and we don't treat UNSPECIFIED just like any other
;;; module name and therefore we don't have the benefit of knowing which workspaces
;;; are "assigned" to it, so the writer for the frame note about all the workspaces
;;; with NIL as their assigned module has to just count them up each time it's called.
;;; We think that's easily cheap enough.  (MHD 11/21/91)

(def-system-frame module-information modules
  (kb-module-file-name?				; a read-only slot for information
    nil (type module-file-name?)			;   purposes only, not saved
    ; not-user-editable				; -- NO LONGER -- Now allowed to
						;   be specified. (MHD 2/12/92)
    vector-slot system				; (still) never saved
    ; do-not-save				;  -- NO LONGER not saved; i.e., now saved
    )						;   (MHD 5/28/92)

  (top-level-kb-module?
    nil (type module-name-for-module-information?)
    vector-slot system)
  (directly-required-kb-modules
    nil (type list-of-modules?) vector-slot system)

  (cached-module-is-required-p		; used by module frame
    nil do-not-save vector-slot system) ;   note mechanism
  (module-annotations nil (type module-annotations) system)
  )



;; Regarding kb-module-file-name? -- At first, this was a read-only slot that
;; just reported as information the truename of the kb file loaded, if any.
;; Files would be saved out to this file name.  Then it became the pathname
;; of the file name loaded, if any, or what the user wanted to be where the
;; file is saved -- still read-only.  Now it has become a true saved slot,
;; with a default of NIL (written "DEFAULT"), which means to save it according
;; to what the user specified in the file dialog, or what the top-level
;; module specifies.  It can be overridden with a pathname, in which case that
;; pathname has precedence over the user-suppied/superior defaults for merging
;; purposes.
;;
;; However, we are missing two things: (1) information to the user as to where
;; the module was loaded from, if any, and (2) adequate warning when the slot
;; specifies saving to a different pathname than that to which the file has
;; been saved.
;;
;; The proposed solution is to introduce a read-only informational slot, again,
;; that again gives the truename of the file loaded, if any.  Then, if that
;; differs, at the time loaded, from the truename you get when you apply the
;; default pathname computation to what's in kb-module-file-name?, you get
;; a frame note advising you of this potentially undesirable state of affairs,
;; i.e., that saving now would not write the same file as was loaded.  (From
;; a meeting with Ben, me, and Sam.) (MHD 6/9/92)
;;
;;
;; KINDS OF LOSSAGE:
;;
;; (1) Save out with a different name than the module, leaving no module there.
;; 
;; (2) Load in from non-default directory -- won't go back there. (bug? misdesign?)
;; 
;; (3) Create & save out a new module as FOO.KB, when there is already a
;; FOO.KL unrelated -- that FOO.KL will be loaded instead of your FOO.KB.


(define-slot-alias top-level-module top-level-kb-module?)

;; Alias for top-level-kb-module? changed from top-level-kb-module
;; => top-level-module today. (MHD 2/19/92)


(define-slot-alias directly-required-modules directly-required-kb-modules)

;; Alias for directly-required-kb-modules changed from
;; directly-required-kb-modules (no alias) 
;; => directly-required-modules today. (MHD 2/19/92)


(define-slot-alias module-file-name kb-module-file-name?)

;; Changed alias from file-name => module-file-name today. (MHD 2/18/92)


(def-class-method install-system-table (module-information)
  (change-slot-value				; start with a clean slate
    module-information 'frame-status-and-notes nil)
  (update-module-related-frame-notes-for-all-workspaces))

(def-class-method deinstall-system-table (module-information)
  (change-slot-value
    module-information 'frame-status-and-notes nil))


(add-grammar-rules '((file-name? 'none)
		     (file-name? file-name)))

(def-slot-value-compiler file-name? (parse-result)
  (if (eq parse-result 'none)
      nil
      parse-result))

(def-slot-value-writer file-name? (file-name?)
  (tformat (if file-name? "~s" "~a") (or file-name? "none")))

(add-grammar-rules '((module-file-name? 'default)
		     (module-file-name? file-name)))

(def-slot-value-compiler module-file-name? (parse-result)
  (if (eq parse-result 'default)
      nil
      parse-result))

(def-slot-value-writer module-file-name? (file-name?)
  (tformat (if file-name? "~s" "~a") (or file-name? "default")))

(define-category-evaluator-interface (module-file-name?
				       :access read-write)
    (or (no-item) text symbol)
  ((set-form (evaluation-value))
   (if evaluation-value
       (copy-for-phrase evaluation-value)
       'default))
  ((get-form (slot-value))
   (cond ((text-string-p slot-value)
	  (make-evaluation-text slot-value))
	 ((symbolp slot-value)
	  slot-value))))

(add-grammar-rules
  '((module-annotations module-annotation-list)
    (module-annotations 'none nil)
    (module-annotation-list
     (symbol 'is module-annotation-value)
     (1 3))
    (module-annotation-list
     (symbol 'is module-annotation-value '\; module-annotation-list)
     (1 3 . 5))
    (module-annotation-value
     evaluation-value-constant)
    (module-annotation-value
     symbol)))

  

(def-slot-value-writer module-annotations (plist)
  (cond
    (plist
     (loop for (k v . tail) on plist by 'cddr
	   do
       (tformat "~a is ~NV" k v)
       (when tail
	 (tformat ";~%"))))
    (t
     (tformat "none"))))

(def-slot-value-compiler module-annotations (plist)
  (let ((duplicate-key?
	  (loop for (k v . tail) on plist by 'cddr
		when (loop for (k2 v2 . t2) on tail by 'cddr
			   thereis (eq k k2))
		  return k)))
    (cond
      (duplicate-key?
       (values bad-phrase
	       (tformat-text-string
		 "Duplicate annotation for ~a found."
		 duplicate-key?)))
      (t
       plist))))

(define-category-evaluator-interface (module-annotations
				       :access read-write)
    (sequence (structure annotation-pair
			 ((annotation-name symbol)
			  (annotation-value datum))
			 (and annotation-name
			      annotation-value))
	      0)
  ((set-form (sequence))
   (loop for structure
	     being each evaluation-sequence-element of sequence 
	 collect
	 (evaluation-symbol-symbol
	   (evaluation-structure-slot structure 'annotation-name))
	   using phrase-cons
	 collect
	 (copy-for-phrase
	   (evaluation-structure-slot structure 'annotation-value))
	   using phrase-cons))
  ((get-form (slot-value))
   (allocate-evaluation-sequence
     (loop for (k v . tail) on slot-value by 'cddr
	   collect (allocate-evaluation-structure-inline
		     'annotation-name (make-evaluation-symbol k)
		     'annotation-value (copy-evaluation-value
					 v))
	     using eval-cons))))
	   


;slot?
;
;  (module-map-for-kb?
;    nil (type module-map)
;    vector-slot system)
;
;(def-slot-alias module-map-for-kb? module-map)
;
;
;(def-slot-value-writer module-map (value)
;  (if (null value)
;      (twrite "none")
;      (loop for ((module file-name) . more?)
;              on (cdr value)            ; car is |,|
;            do (tformat "~a ~s"
;                        module file-name)
;               (tformat (if more? ",~%" "")))))
;
;(add-grammar-rules '((module-map 'none)
;                     (module-map-entry
;                      (module-name file-name))))
;
;(add-grammar-rules-for-list 'module-map 'module-map-entry)




;;; A `module' or `module name' is a symbol other than nil.  A `non-existant
;;; module' is one that is mentioned as required in the module-this-is-part-of?
;;; slot of some workspace or in the directly-required-kb-modules slot of some
;;; module-information system table, but which is not the value of
;;; top-level-kb-module?  slot of some module-information system table.  An existant
;;; module is one which is associated with a module-information system table, i.e.,
;;; is the value of some module-information's top-level-kb-module? slot.  A
;;; `mentioned module' is either a non-existant or an existant module.
;;; An `empty module' is one to which workspaces belong, but which is not a
;;; `known module'.  A `known module' is either the top-level module or a module
;;; that is directly or indirectly required by the top-level module.

;; There is a proposal to maintain the constraint that, in terms of the above,
;; non-existant modules are always immediately converted into existant modules,
;; and so, in effect, never exist.  This would mean that a known module and
;; an empty module would always exist.  This would presumably be done as side
;; effects of editing the directly-required-kb-modules and module-this-is-part-of?
;; slots.
;;
;; The current implementation does not do that, so you can have a known module
;; that doesn't exist.
;;
;; The current implementation is in synch with the above only if you revise
;; the definition of existant module to mean that it EVER was mentioned
;; in the lifetime of the KB.  Once a module is mentioned, it never becomes
;; non-existant, even if all mentions of it are removed, as long as the KB
;; exists (in memory).
;;
;;
;;
;; Can a KB be saved when there is an unspecified top-level module but workspaces
;; are assigned to modules?  When you load in the KB are the workspaces still
;; assigned to modules?  If so, how do notes get updated, through putter for
;; the workspace-this-is-part-of? slot?
;;
;; If there is a specified top-level module, then presumably there would be
;; absolutely no workspaces saved out that weren't assigned to that module.
;; However, if that KB were merged into a KB where that module was already
;; an existing module, you would have to update notes, so how?  Through the
;; putter for the workspace-this-is-part-of? slot?

;;; The `workspaces-belonging-to-this-module' property of a module name specifies
;;; the top-level kb-workspace, if any, that belong this module.  When there is only
;;; one such instance, the value of this property is just the instance.  When there
;;; are more than one, the value is a gensym list of them.  A mentioned module has a
;;; non-nil value for this property.  This property is kb-specific, and since its
;;; value is determined entirely by the slot putter for module-this-is-part-of?,
;;; it need not be represented explicitly in a saved kb.

(def-kb-specific-property-name workspaces-belonging-to-this-module
    reclaim-gensym-list-if-list)

;; This facility is patterned after frame-or-frames-with-this-name, which see.
;; The reclaimer reclaim-gensym-list-if-list is defined as part of that facility.






;;; The kb-specific property name `module-information-instance-for-module?' is
;;; maintained at all times to point to the unique module-information instance
;;; that names its value as the value of the slot top-level-kb-module?
;;; Note that this property is never maintained for the symbol NIL, which represents
;;; an "unspecified" module.

;;; Historical note: this is newly being added (in 3.0 Beta Rev. 3) as the new
;;; way to map from a module (a symbol) to the (unique) module-information
;;; system-table for that module.  Prior to this time, that mapping was done
;;; by a relatively slow assq test.  After this was done, all calls of the form
;;;    
;;;    (get-system-table-of-class-for-module-or-nil
;;;	  module 'module-information)
;;;
;;; were changed to
;;;
;;;    (module-information-instance-for-module? module)

(def-kb-specific-property-name module-information-instance-for-module?)



;;; The slot putter for top-level-kb-module? adds/deletes module names to/from
;;; their name directory.  

(def-slot-putter top-level-kb-module?
		 (module-information-instance new-value initializing?)
  (unless initializing?
    (let ((system-table-suite-this-is-part-of
	    (assq module-information-instance
		  modules-and-system-tables-a-list)))
      (loop for system-table in system-table-suite-this-is-part-of
	    do (setf (module-system-table-belongs-to? system-table)
		     new-value)))
    (when (top-level-kb-module? module-information-instance)
      (add-or-delete-module-name-from-directory-of-names
	(top-level-kb-module? module-information-instance)
	t)
      (if (eq (module-information-instance-for-module?
		(top-level-kb-module? module-information-instance))
	      module-information-instance)
	  (setf (module-information-instance-for-module?
		  (top-level-kb-module? module-information-instance))
		nil))))
  (when new-value
    (add-or-delete-module-name-from-directory-of-names new-value nil)
    (setf (module-information-instance-for-module? new-value)
	  module-information-instance))
  (setf (top-level-kb-module? module-information-instance) new-value)
  (update-module-related-frame-notes-for-all-workspaces)
  (update-representations-of-slot-value module-information-instance 'class)
  new-value)



(def-slot-value-reclaimer top-level-kb-module? (module? module-information-instance)
  (when module?
    (add-or-delete-module-name-from-directory-of-names module? t)
    (if (eq (module-information-instance-for-module? module?)
	    module-information-instance)
	(setf (module-information-instance-for-module? module?) nil))))


(add-grammar-rules '((module-name-for-module-information? module-name?)))

(def-slot-value-compiler module-name-for-module-information?
			 (parse-result frame slot-name)
  (cond
    ((eq parse-result 'unspecified)
     (if (and (frame-of-class-p frame 'module-information)
	      (not (system-table-installed-p frame))
	      (eq parse-result 'unspecified))
	 ;; maybe relax this -- only prohibit if module is required?
	 ;; -- could this be used as a way (the only way) to delete an
	 ;; existing module?
	 (values
	   bad-phrase
	   (tformat-text-string
	     "you cannot change the ~a attribute of a ~
              non-top-level module-information system table ~
              to UNSPECIFIED."
	     (alias-slot-name-if-necessary slot-name frame)))
	 nil))
    ((and (frame-of-class-p frame 'module-information)
	  (module-exists-p parse-result)
	  (not (eq parse-result (get-slot-value frame slot-name))))
     (values
       bad-phrase
       (tformat-text-string
	 "you cannot change the ~a attribute of a ~
          module-information system table ~
          to the name of an already existing module."
	 (alias-slot-name-if-necessary slot-name frame))))
    (t parse-result)))



(def-slot-value-writer module-name-for-module-information? (module-name?)
  (twrite-symbol (or module-name? 'unspecified)))

(define-category-evaluator-interface (module-name-for-module-information?
				       :access read-write)
    (or (no-item) symbol)
  ((set-form (evaluation-value))
   (if evaluation-value
       evaluation-value
       'unspecified))
  ((get-form (slot-value))
   (if (eq slot-value 'unspecified)
       nil
       slot-value)))

(add-grammar-rules-for-list 'list-of-modules? 'module-name  nil nil 'none)

(def-slot-value-writer list-of-modules? (value)
  (if (null value)
      (twrite-string "none")
      (loop for l on value
	    do (tprin (car l) t)
	       (when (cdr l) (twrite-string ", ")))))

(def-slot-value-compiler list-of-modules? (parse-result)
  (if (eq parse-result 'none)
      nil
      (if (eq (car parse-result) '\,)		; sloppy!
	  (cdr parse-result)
	  parse-result)))
  
(define-category-evaluator-interface (list-of-modules?
				       :access read-write)
    (or (no-item)
	(sequence symbol 0))
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
    ((no-item) 'none)
    ((sequence) 
     (with-evaluation-sequence-to-phrase-list-mapping
	 (evaluation-value module-name)
       module-name))))
  ((get-form (slot-value))
   (cond
     (slot-value
      (with-list-to-evaluation-sequence-mapping (slot-value module-name)
	  module-name))
     (t
      (allocate-evaluation-sequence '())))))




(def-slot-putter directly-required-kb-modules (module-information-instance value)
  (if value
      (setq value
	    (delete-duplicates-from-list
	      value 'reclaim-slot-value-cons-function)))
  (loop for module in (directly-required-kb-modules module-information-instance)
	do (add-or-delete-module-name-from-directory-of-names
	     module t))
  (loop for module in value
	do (add-or-delete-module-name-from-directory-of-names
	     module nil))
  (setf (directly-required-kb-modules module-information-instance) value)
  (update-module-related-frame-notes-for-all-workspaces)
  value)

(def-slot-value-reclaimer directly-required-kb-modules (value module-information-instance)
  (loop for module in value
	do (add-or-delete-module-name-from-directory-of-names
	     module t))
  (setf (directly-required-kb-modules module-information-instance) nil)
  (reclaim-slot-value value))




;;; Add-or-delete-module-name-from-directory-of-names ...

(defun add-or-delete-module-name-from-directory-of-names (module-name delete-case?)
  (funcall-symbol
    (if delete-case?
	'delete-from-directory-of-names
	'add-to-directory-of-names)
    module-name 'module-name))





;;; Modules-that-have-already-been-loaded ...

(def-kb-specific-variable modules-that-have-already-been-loaded modules nil
  nil reclaim-gensym-list-function)


;;; `Currently-loading-modules?', a system variable, is bound to nil at
;;; top-level and to true when read-kb is being called from within
;;; itself to load modules of a KB.

(def-system-variable currently-loading-modules? modules nil)




(defun notify-user-of-autostart-and-reason (kb-autostart-reason)
  (notify-user 
    "Starting to run G2 automatically~a.  ~
     You may pause, reset, or restart at any time."
    (case kb-autostart-reason
      (system-table 
       ", because \"Start KB after Load?\" is set in Miscellaneous Parameters")
      (load-grammar
       ", as specified in the last \"Load KB\" command")
      (merge-grammar
       ", as specified in the last \"Merge KB\" command")
      (load-in-init-file 
       ", from the last \"Load KB\" line in the G2 Init file to specify this")
      (merge-in-init-file 
       ", from the last \"Merge KB\" line in the G2 Init file to specify this")
      (load-from-command-line
       ", because the command line that launched G2 specified the \"-start\" option")
      (otherwise ""))))

;; jh, 5/29/92.  Added a new autostart reason, load-from-command-line.  This
;; means the autostart happened because the keyword -kb and the flag -start
;; appeared on the command line.  See do-g2-kb-load-at-launch in KB-SAVE2 for
;; details.





;;;; Macro for Suppressing Module Frame Note Updating

;;; With-module-related-frame-note-updates-supressed ...  Body may only return
;;; one value.  This does not expect to be thrown out of.  There is no unwind-
;;; protect, and throwing out will leave frame notes of potentially numerous
;;; frames in an inconsistent state.

;;; This uses the variable `inhibit-updating-module-related-frame-notes-for-
;;; all-workspaces?', which should be used only by this macro for communication
;;; with update-module-related-frame-notes-for-all-workspaces.

(defvar inhibit-updating-module-related-frame-notes-for-all-workspaces? nil)

(defmacro with-module-related-frame-note-updates-supressed (&body body)
  `(prog1
       (let ((inhibit-updating-module-related-frame-notes-for-all-workspaces? t))
	 (progn . ,body))
     (unless inhibit-updating-module-related-frame-notes-for-all-workspaces?
       (update-module-related-frame-notes-for-all-workspaces))))

;; FIX THE MISSPELLING OF "SUPRESSED"!! (MHD 8/19/96)

;; The above has the usual severe restrictions on Lisp semantics in order to
;; guarantee efficiency and lack of consing.  Its only callers, at present, are
;; make-new-top-level-kb-workspace and system-reset.  (MHD 12/13/91)

;;
;; -- Added this around read-kb-or-group-thereof -- we were calling for the
;; update multiple times proportional to the number of workspace in a KB for
;; every KB read in! (MHD 8/16/96)





;;;; Maintaining Per-Module System Table Suites



;;; Upon loading a file we will obtain 1 or more suites of system
;;; tables.  The more than one case arises only if this file contains
;;; multiple modules.  If we are installing system tables then one of
;;; these suites will be installed.  In the presence of more than one
;;; suite the suite to install is discovered by noting the suite whose
;;; members are marked as being "this-system-table-is-installed?," this
;;; is the only use of this flag on loading and the only reason this is
;;; a saved slot.



;;; `Partition-system-tables-into-separate-module-suites' ... System-tables should
;;; be a list of system tables such that no two system tables are of the same
;;; class AND have the same value for module-system-table-belongs-to?.  NIL
;;; is one of the legal values for module-system-table-belongs-to?.

;;; The result is a list of lists containing all of the system classes
;;; partitioned into suites such that each element of a suite has the
;;; same value for module-system-table-belongs-to?.

;;; For a module or unmodularized KB, the result will be a single-element list.
;;; For a KB containing multiple modules combined into a single KB, the
;;; result will be a list N long.  

;;; For KBs saved in 3.0 Beta or later, it is assumed that they contain at
;;; least one complete suite.  If the KB is NOT saved out as a module -- meaning
;;; it has a module in its plist, and name-of-module-being-read? is now bound,
;;; then one and only one of the complete suites has the slot
;;; this-system-table-is-installed? true for each member.  When the KB is saved
;;; out as a module, the slot this-system-table-is-installed? is not relevant.
;;; Older KBs can have only one suite, which is always the only one that was
;;; installed in that KB.  Older KBs can never have been saved out as modules.

;;; It is also assumed that only the installed suite of system tables may have
;;; NIL for a module.

(defun partition-system-tables-into-separate-module-suites (system-tables)
  (loop with result = nil
	for system-table in system-tables
	for server-parameters? = (of-class-p system-table 'server-parameters)
	as module-for-system-table?
	   = (module-system-table-belongs-to? system-table)
	as entry-for-this-module?
	   = (loop for entry in result
		   when (eq (module-system-table-belongs-to?
			      (car entry))
			    module-for-system-table?)
		     return entry)
	do (cond (server-parameters?
		  (delete-frame system-table))
		 (entry-for-this-module?
		  (slot-value-push system-table (cdr entry-for-this-module?)))
		 (t
		  (slot-value-push (slot-value-list system-table) result)))
	finally
	  (return (or result
		      ;; this case is only if there are no system tables
		      ;; at all:
		      (slot-value-list nil)))))




;;; Set-up-modules-and-system-tables-a-list-after-reading ...  called while
;;; reading a KB, from read-kb, after all top-level frames have been read in.
;;; It expects to be called when it is still too early to delete frames, and so
;;; when it deletes, it uses delete-block-after-reading-kb rather than
;;; delete-frame after changing the name-or-names-for-frame slot to nil via
;;; change-slot-value.

;;; The first thing this does is partition all of the system tables read in
;;; into different suites.  Most KBs have only one suite, but KBs saved in
;;; "ALL-" format can have several.  When there are several suites, only one
;;; will be an installed suite, i.e., one that was installed when that KB was
;;; saved out.  When there is only one suite, it has to be an installed suite.


;;; For each suite of system tables merge them in.  If we have one that is
;;; being installed it is done first.  The merging is done in the following
;;; function in these steps by `merge-in-system-table-suite-read-in'.
;;;
;;;   (1) Discard duplicate system tables for the same module, recovering
;;;       from a bug (MHD 6/11/92).
;;; 
;;;   (2) If installing, the current set of system tables is deinstalled.
;;;       If the ones being deinstalled and named NIL, they are deleted (in step 6).
;;;
;;;   (3) The suite of system tables may be incomplete if new system tables
;;;       have been added since the save.  Missing ones are created and
;;;       added to the suite.
;;;
;;;   (4) Make the first element of the suite just read in be the
;;;       module-information system.
;;;
;;;   (5) Make each element of suite belong to a module or NIL, and clear
;;;       the this-system-table-is-installed? flag.
;;;
;;;   (6) The new suite may conflict with an old suite of the same name (or
;;;       they both are named NIL).  This conflict is resolved by discarding
;;;       one or the other suite.  If we are installing, the old suite gets
;;;       discarded.
;;;
;;;   (7) If not deleting the system table suite read in, store it in the
;;;       set of all system table suites.  Also, ensure that the
;;;       module-information instance in the incoming suite is pointed to by
;;;       module-information-instance-for-module?.  (This may need to be done
;;;       because of pruning, as explained above.  (MHD 6/12/92))
;;;       
;;;   (8) If installing, the system tables read in are installed.
;;;
;;;   (9) All module frame notes are updated.

(defun set-up-modules-and-system-tables-a-list-after-reading ()  
  (let ((do-not-note-permanent-changes-p t)
	(all-system-table-suites-read-in
	  (partition-system-tables-into-separate-module-suites
	    system-tables-read-for-this-module)))
    (cond
      ((or name-of-module-being-read?
	   (null (cdr all-system-table-suites-read-in)))
       (merge-in-system-table-suite-read-in
	 (car all-system-table-suites-read-in)
	 main-kb-being-read?))
      (t
       (let ((suite-to-install
	       (or
		 (loop for entry in all-system-table-suites-read-in
		       when (this-system-table-is-installed? (first entry))
			 return entry)
		 #+development
		 (cerror
		   "Continue (using NIL as the suite)."
		   "There was no installed system table suite saved out!"))))
	 (merge-in-system-table-suite-read-in
	   suite-to-install main-kb-being-read?)
	 (loop for entry in all-system-table-suites-read-in
	       unless (eq entry suite-to-install)
		 do (merge-in-system-table-suite-read-in entry nil)))))
    (reclaim-slot-value-list all-system-table-suites-read-in)))





;;; `Merge-in-system-table-suite-read-in' ... Installing?  says whether this
;;; system table suite is to become the installed system table suite.  When
;;; installing?  is true, system-table-suite can never be deleted.  When it is
;;; false, system-table-suite can be deleted if there already is a system table
;;; suite for the same module, or if system-table-suite is for the NIL
;;; ("unspecified") module.
;;;
;;; System-table-suite-to-replace? should be either nil or a system table for a
;;; module that is to be replaced, i.e., deleted, by the suite being merged in.

;; merge above & following paragraphs! The following used to be inline. (MHD
;; 9/8/94)

;;; If NOT installing and the suite read in is either for the same module as an
;;; existing suite or is for the unspecified module, then we delete the suite
;;; being read in.  Otherwise, if installing and the suite read in is for the
;;; same module as an existing suite, then delete the matching existing suite.
;;; Finally, if installing a specified (non-nil) module's system table suite,
;;; and there is an existing suite for the unspecified module -- it should have
;;; just been deinstalled, since system tables for the unspecifed module should
;;; only exist if they're installed, then delete that suite.

;;; This is primarily a subfunction of set-up-modules-and-system-tables-a-list-
;;; after-reading, and it is mostly documented there.

(defun merge-in-system-table-suite-read-in
    (suite installing? &optional system-table-suite-to-replace?)
  (let* ((module? (get-module-assignment-of-system-table-suite-read-in suite))
	 (matching-existing-suite?
	   (find-system-table-suite-with-module-assignment module?))
	 (suite-for-unspecified-module?
	   (unless (eq module? 'nil)
	     (find-system-table-suite-with-module-assignment 'nil))))
    (cond
      ((and (not installing?) (or matching-existing-suite? (null module?)))
       (delete-system-table-suite suite t t))
      (t
       (setq suite (make-fully-fleshed-out-system-table-suite suite))
       (store-system-table-suite suite)
       (when installing?  
	 ;; ajs 6/28/96.
	 ;; Defer notifications until system tables have been restored
	 ;; This is because there will be no logbook or message board
	 ;; parameters until the system tables have been restored.
	 (let ((defer-notifications? t))
	   (deinstall-currently-installed-system-table-suite)
	   (when system-table-suite-to-replace?
	     (delete-system-table-suite
	       system-table-suite-to-replace? nil
	       t))			; essential to suppress, since
					;   frame note updating assumes
					;   a consistent state
	   (install-system-table-suite suite)
	   (setq defer-notifications? nil)
	   (try-to-do-deferred-user-notifications))
	 (when matching-existing-suite?
	   (delete-system-table-suite matching-existing-suite? t t))
	 (when suite-for-unspecified-module?
	   (delete-system-table-suite suite-for-unspecified-module? t t)))
       (inform-ui-client-interfaces-of-module-creation (car suite))))
    (set-up-all-module-to-module-information-instance-backpointers)
    (update-module-related-frame-notes-for-all-workspaces)))

;; Note that there is (almost) no way right now to replace the system tables of
;; a module that is not installed.  If you merge in a KB, installing system
;; tables, it will not merge in the non-top-level modules that already exist in
;; the KB.  Say your top-level module is TOP, and it just requires BOTTOM, which
;; requires nothing.  If you want to get the system tables for TOP from disk,
;; you can: just merge kb top, installing system tables.  When you do this, it
;; won't install bottom's system tables because it sees that bottom exists.  The
;; only workaround is to rename the module BOTTOM in the KB in memory to XBOTTOM,
;; say, and then do it.  This will cause it to think BOTTOM does not exist and
;; bring in its system tables.  Then, after that is done, you can delete the
;; module XBOTTOM via the delete-module menu choice.  (MHD 6/12/92)



;;; `Get-module-assignment-of-system-table-suite-read-in' takes a system table
;;; suite that may not have yet been fleshed out and partially ordered, i.e.,
;;; one which has just been read in, and returns the module assignment for
;;; that suite, if any, or else nil.

(defun get-module-assignment-of-system-table-suite-read-in (suite)  
  (loop for system-table in suite
	when (frame-of-class-p system-table 'module-information)
	  return (top-level-kb-module? system-table)))


;;; `Obsolete-system-table-p' is the test to determine if a system table,
;;; presumably being read in from an older KB, is now obsolete.
;;;
;;; Currently, this test amounts to simply seeing if the symbol that is the
;;; class name for the system table is a special variable bound to something.
;;; In all known, conceivable cases, this is known to work at present.
;;;
;;; (Note that it would fail if a system table class ever became obsolete, and
;;; its name became a special variable that could be bound for some other
;;; purpose.)

(defun obsolete-system-table-p (system-table)
  (not (boundp (class system-table))))


;;; `Find-duplicate-system-table-in-list' returns the first element in
;;; list-of-system-tables, if any, that is strictly of the same class as
;;; system-table.

(defun find-duplicate-system-table-in-list (system-table list-of-system-tables)
  (loop for system-table-in-list in list-of-system-tables
	when (eq (class system-table) (class system-table-in-list))
	  return system-table-in-list))



;;; `Make-fully-fleshed-out-system-table-suite' ... 

(defun make-fully-fleshed-out-system-table-suite (suite)
  ;; Make each element of suite belong to the module for the suite:
  (propagate-module-assignment-throughout-system-table-suite 
    ;; Make the first element be the module-information system table:
    (make-suite-be-headed-up-by-module-information-system-table
      ;; Fill in for classes newly introduced since release in which
      ;; saved:
      (add-newer-system-tables-to-suite-if-necessary
	;; Prune obsolete or duplicate system tables:
	(delete-obsolete-or-duplicate-system-tables-in-suite
	  ;; Turn off the installed flag in case it's on from the save:
	  (remove-any-trappings-of-installation-in-system-table-suite
	    suite))))))


;;; `Remove-any-trappings-of-installation-in-system-table-suite' ... returns the
;;; suite as its sole value.

(defun remove-any-trappings-of-installation-in-system-table-suite (suite)
  (loop for system-table in suite
	do (setf (this-system-table-is-installed? system-table) nil))
  suite)



;;; `Delete-obsolete-or-duplicate-system-tables-in-suite' destructively deletes
;;; elements that are either duplicates or are of obsolete classes.
;;;
;;; The conses in suite are assumed to be from the slot-value cons pool, and are
;;; returned to that pool when appropriate.
;;;
;;; This is at times called while reading a KB.  When that is the case, deletion
;;; of system tables is actually deferred until after reading has completed.  If
;;; it is called while with a fully loaded KB, it instead uses delete-frame.
;;; (Note that this function really is only useful in the kb reading case; in a
;;; fully loaded KB, there should be no obsolete or duplicate system tables, but
;;; this case is implemented for completeness.)
;;; 
;;; This returns the resulting suite as its sole value.  Note that this value
;;; must be captured, since pointers to elements of the original list structure
;;; may now point into the recycled cons pool.

(defun delete-obsolete-or-duplicate-system-tables-in-suite (suite)
  (loop with copied-suite-list = (copy-list-using-slot-value-conses suite)
	for copied-sublist on copied-suite-list
	for system-table = (car copied-sublist)
	do
    (when (or (obsolete-system-table-p system-table)
	      (find-duplicate-system-table-in-list
		system-table (cdr copied-sublist)))
      (if (eq (car suite) system-table)
	  (reclaim-slot-value-cons 
	    (prog1 suite
	      (setf suite (cdr suite))))
	  (loop for sublist on suite
		for suite-system-table = (cadr sublist)
		do
	    (when (eq suite-system-table system-table)
	      (reclaim-slot-value-cons 
		(prog1 
		    (cdr sublist) 
		  (setf (cdr sublist) (cddr sublist))))
	      (loop-finish))))
      (cond (reading-kb-p
	     (delete-block-after-reading-kb system-table))
	    (t
	     #+development
	     (warn
	       "Why are there obsolete or duplicate ~
                   system tables in a loaded kb?!")
	     (delete-frame system-table))))
    finally (progn
	      (reclaim-slot-value-list copied-suite-list)
	      (return suite))))

;; Due to the rarity of deletion, and the shortness of the lists, a tail-pointer
;; optimization is quite unnecessary.


		      

;;; `Deinstall-currently-installed-system-table-suite' finds the currently installed
;;; system table suite and deinstalls it.

(defun deinstall-currently-installed-system-table-suite ()
  (loop for suite in modules-and-system-tables-a-list
	when (this-system-table-is-installed? (first suite))
	  return (deinstall-system-table-suite suite)))

(defun find-currently-installed-system-table-suite ()
  (loop for suite in modules-and-system-tables-a-list
	when (this-system-table-is-installed? (first suite))
	  return suite))

;;; `Deinstall-system-table-suite' takes a system table suite known to be the
;;; currently installed one and deinstalls it.

(defun deinstall-system-table-suite (suite)
  (loop for system-table in suite
	do (deinstall-system-table system-table)))



;;; `Add-newer-system-tables-to-suite-if-necessary' conses (using slot-value
;;; conses) new elements onto the beginning of suite that are necessary to
;;; ensure that all system table classes that should be instantiated are
;;; represented as elements of suite.  If an element does need to be added,
;;; presumably it is because the suite was loaded from a KB saved in an older
;;; version of G2 in which the class for that element had not yet been defined.
;;; This is intended to be called when loading a KB.  This returns the resulting
;;; suite as its sole value.  Note that the new system table is activated if
;;; this is called in a running or paused G2.  [However, that was not getting
;;; done in G2 versions prior to the second Beta release of G2 5.0. (MHD
;;; 2/26/97)]

(defun add-newer-system-tables-to-suite-if-necessary (suite)
  (loop for class being each subclass of 'system-table
	when (and (neq class 'server-parameters)
		  (instantiable-system-table-subclass-p class)
		  (loop for system-table in suite
			never (frame-of-class-p system-table class)))
	  do (let ((new-system-table (make-system-frame class)))
	       ;; Activate if appropriate
	       (when (or system-is-running system-has-paused)
		 (funcall-method
		   'activate-if-possible-and-propagate new-system-table))
	       (setq suite (slot-value-cons new-system-table suite))))
  suite)



;;; `Make-suite-be-headed-up-by-module-information-system-table' normalizes
;;; suite in terms of the convention that its first element must be an instance
;;; of the class module-information.  The order that results for other elements
;;; is not defined.  This returns the resulting suite as its sole value.

(defun make-suite-be-headed-up-by-module-information-system-table (suite)
  (let ((temp (car suite)))
    (loop for elements on suite
	  when (frame-of-class-p (car elements) 'module-information)
	    do (setf (car suite) (car elements))
	       (setf (car elements) temp)
	       (return nil))
    suite))



;;; `Propagate-module-assignment-throughout-system-table-suite' makes all
;;; elements of the suite have the module assignment indicated by its
;;; module-information instance element, which should, per convention, at this
;;; point already have been made to be the first element of suite.  This returns
;;; the resulting suite as its sole value.

(defun propagate-module-assignment-throughout-system-table-suite (suite)
  (loop with module? = (top-level-kb-module? (first suite))
	for system-table in suite
	do (setf (module-system-table-belongs-to? system-table) module?))
  suite)



;;; `Find-system-table-suite-with-module-assignment' finds and returns the
;;; system table suite in modules-and-system-tables-a-list that has module? as
;;; its module assignment.  If no such suite is present, this returns nil.

(defun find-system-table-suite-with-module-assignment (module?)  
  (loop for suite in modules-and-system-tables-a-list
	as module-information-instance = (first suite)
	when (eq (top-level-kb-module? module-information-instance) module?)
	  return suite))



;;; `Install-system-table-suite' installs each system table in suite.

(defun install-system-table-suite (suite)
  (loop for system-table in suite
	do (install-system-table system-table)))



;;; `Store-system-table-suite' stores suite on modules-and-system-tables-a-list.

(defun store-system-table-suite (suite)
  (slot-value-push suite modules-and-system-tables-a-list))



;;; Delete-system-table-suite ... system-table-suite-or-module-information-therefor
;;; should either be a system table suite, or the module-information instance at the
;;; head of one.  The system table suite to be deleted may not be the one that's 
;;; installed and must be present in modules-and-system-tables-a-list.  This does
;;; not do any checking.

;;; If delete-after-reading? is true, delete-block-after-reading-kb is used; otherwise,
;;; system tables are deleted using delete-frame.  This should be used for deleting
;;; system table suites while reading a KB.

;;; Suppress-update-of-module-related-frame-notes?, when true, suppresses updating
;;; of module-related frame notes, should only be done when it is known that they're
;;; going to get updated again almost immediately after this function is invoked.

(defun delete-system-table-suite
    (system-table-suite-or-module-information-therefor
      &optional
      delete-after-reading?
      suppress-update-of-module-related-frame-notes?)
  (let ((system-table-suite
	  (if (atom system-table-suite-or-module-information-therefor)
	      (assq system-table-suite-or-module-information-therefor
		    modules-and-system-tables-a-list)
	      system-table-suite-or-module-information-therefor)))
    (setq modules-and-system-tables-a-list
	  (delete-slot-value-element
	    system-table-suite modules-and-system-tables-a-list))
    (decache-dynamic-menus 'modules)
    (inform-ui-client-interfaces-of-module-deletion (first system-table-suite))
    (loop for system-table in system-table-suite
	  do (change-slot-value system-table 'name-or-names-for-frame nil))
    (loop for system-table in system-table-suite 
	  do (if delete-after-reading?
		 (delete-block-after-reading-kb system-table)		
		 (delete-frame system-table)))
    (reclaim-slot-value-list system-table-suite)
    ;; Update all workspaces' module-related frame notes:
    (unless suppress-update-of-module-related-frame-notes?
      (update-module-related-frame-notes-for-all-workspaces))))



;;; `Set-up-all-module-to-module-information-instance-backpointers' ensures that
;;; for every module, i.e., a symbol naming a module, that symbol's
;;; module-information-instance-for-module? property points to its corresponding
;;; module-information instance.  Note that the "unassigned module", i.e., NIL,
;;; is never to point back to any module-information instance.
;;;
;;; This is intended to be called after changes to the set of system table
;;; suites.  (It does some work that is redundant, but at negligable cost.)

(defun set-up-all-module-to-module-information-instance-backpointers ()  
  (loop for suite in modules-and-system-tables-a-list
	as module? = (top-level-kb-module? (first suite))
	when module?
	  do (setf (module-information-instance-for-module? module?)
		   (first suite))))


;;; Finish-setup-of-system-table-suite-for-new-module creates a new suite of
;;; system tables by cloning of the installed set, given a newly created
;;; module-information table instance which has just had its
;;; top-level-kb-module?  slot filled in with a non-nil value. 
;;; ... Modularity-related frame notes are updated as appropriate.

(defun finish-setup-of-system-table-suite-for-new-module
    (module-information-instance)  
  ;; Reabstract the following in conjunction with set-up-modules-and-
  ;; system-tables-a-list-after-reading and get-system-table-currently-
  ;; in-force.
  (with-normal-system-table-inferior-classes (system-table-classes)
    (loop for system-table-class in system-table-classes
	  as system-table-in-force?
	     = (get-system-table-currently-in-force system-table-class)
	  as new-system-table
	     = (cond
		 ((eq system-table-class 'module-information)
		  module-information-instance)
		 (system-table-in-force?
		  (clone-system-frame system-table-in-force?))
		 (t
		  (make-system-frame system-table-class)))
	  do (setf (module-system-table-belongs-to? new-system-table)
		   (top-level-kb-module? module-information-instance))
	     (setf (this-system-table-is-installed? new-system-table)
		   nil)
      ;; Set notes initially to nil for non-installed system table
      ;; [They might have been cloned -- review!]
	     (when (frame-status-and-notes new-system-table)
	       (change-slot-value
		 new-system-table 'frame-status-and-notes nil))
      ;; Activate if appropriate
	     (if (or system-is-running system-has-paused)
		 (funcall-method
		   'activate-if-possible-and-propagate new-system-table))
	  collect new-system-table
	    into new-system-table-suite using slot-value-cons
	  finally
	    ;; This makes the first element be the module-information system table:
	    (let ((system-table-suite new-system-table-suite))
	      ;; -- same code as in merge-in-system-table-suite-read-in! -- 
	      (let ((temp (car system-table-suite)))
		(loop for elements on system-table-suite
		      when (frame-of-class-p (car elements) 'module-information)
			do (setf (car system-table-suite) (car elements))
			   (setf (car elements) temp)
			   (return nil))))
	    (setq modules-and-system-tables-a-list
		  (slot-value-cons
		    new-system-table-suite
		    modules-and-system-tables-a-list))      
	    (update-module-related-frame-notes-for-all-workspaces)))
  (decache-dynamic-menus 'modules)
  (inform-ui-client-interfaces-of-module-creation module-information-instance))





;;; `Get-system-table-instance-for-module' returns the instance of
;;; system-frame-subclass, which should be a subclass of system-frame, which
;;; belongs to module.  If there is no such instance, this returns nil.

(defun get-system-table-instance-for-module
    (system-frame-subclass module)
  (loop for instance being each class-instance of system-frame-subclass
	when (eq (module-system-table-belongs-to? instance) module)
	  return instance))





;;;; Creating New Modules



;;; `Create-new-module' attempts to create a new, non-top-level module.
;;; If it fails, it returns nil.  Otherwise, it creates a new module
;;; with the name module-name.
;;;
;;; Reasons for failure include:
;;;
;;;   attempting to create a new module in a runtime system
;;;   (pre-G2-5.0 licensing): RUNTIME-SYSTEM
;;;
;;;   or an embedded system (pre-G2-5.0 licensing): EMBEDDED-SYSTEM
;;;
;;;   attempting to use an module-name that's already in use:
;;;      MODULE-NAME-IN-USE
;;;
;;;   attempting to use a module-name that's reserved:
;;;      MODULE-NAME-IS-RESERVED-WORD
;;;
;;;   attempting to use UNSPECIFIED as a module name:
;;;      MODULE-NAME-UNSPECIFIED
;;;
;;;   failure to create a module with the given name for
;;;      reasons unknown: MODULE-CREATION-FAILED-FOR-UNKNOWN-REASON
;;;
;;;   
;;;
;;; This is the API used by the Lisp side of the system-procedure API, giving
;;; users access to the same functionility as was previously available only via
;;; the miscellany menu for create-new-module up until now.

(defun create-new-module (module-name)
  (cond
    #+pre-g2-v5-licensing		; patterned after menu behavior
    ((runtime-option-authorized-p)
     'runtime-system)
    #+pre-g2-v5-licensing
    ((embedded-option-authorized-p)
     'embedded-system)
    ((eq module-name 'unspecified)
     'module-name-unspecified)
    ((module-exists-p module-name)
     'module-name-in-use)
    ((reserved-word-p module-name)
     'module-name-is-reserved-word)
    (t
     (let ((module-information-instance
	     (make-system-frame 'module-information))
	   (module-text
	     (convert-text-string-to-text
	       (twith-output-to-text-string
		 (twrite-parsably module-name)))))
       (parse-text-for-slot
	 module-text
	 module-information-instance
	 (get-slot-description-of-class-description
	   'top-level-kb-module?
	   (class-description-slot module-information-instance)))
       (cond
	 ((top-level-kb-module? module-information-instance)
	  (finish-setup-of-system-table-suite-for-new-module
	    module-information-instance)
	  module-information-instance)
	 (t
	  (delete-frame module-information-instance)
	  'module-creation-failed-for-unknown-reason))))))












;;;; Maintaining Module-Related Frame Notes




;;; Update-module-related-frame-notes-for-all-workspaces ...  called by the slot
;;; putter for top-level-kb-module?, after the slot has been set.  Also called by the
;;; slot putter for directly-required-kb-modules, after the slot has been set.  Also
;;; called, indirectly, by set-up-modules-and-system-tables-a-list-after-reading,
;;; after any installation of system tables may have taken place.  Also by
;;; install-system-table method for module-information.  Also called by
;;; store-hand-created-module-information-if-appropriate after a new system table
;;; suite for a newly created module has come to exist.  Also called by the once-only
;;; post-loading function fix-module-related-frame-notes-after-loading.  Also
;;; called by the slot putter for module-this-is-part-of? on kb-workspace,
;;; after the slot has been set.

;;; This function should make everything be right with the installed
;;; module-information system table's notes.

;;; The variable inhibit-updating-module-related-frame-notes-for-all-workspaces?  is
;;; an implicit parameter to this function, but its use is private to this function
;;; and the macro with-module-related-frame-note-updates-supressed.  Its effect, when
;;; true, is that this function is suppressed, and does nothing.
;;;
;;; When releasing-kb? is true, as it is while clearing a KB, this function is
;;; similarly suppressed. This is necessary because constraints about system
;;; tables are not obeyed during this time, and this function could not work
;;; reliably.  For example, if a workspace was deletd while releasing the KB
;;; after the module-information instance was deleted, this function would get
;;; an error.  [Changes for this case done for 4.0, post Beta II, on 5/6/95;
;;; prior to this, corruption could have gotten in, but no cases have been
;;; reported that are thought to be linked to this issue. (MHD 5/6/95)]

;;; Specific-workspace-with-module-assignment-change? may be specified non-nil
;;; in a context in which we have workspace and system table frame notes
;;; up-to-date except for the change to a particular workspace's module
;;; assignment.  This the case where the user edits the module-assignment
;;; attribute by hand or creates a new top-level KB workspace.  In this case,
;;; this function can save significant time by skipping the analysis of all KB
;;; workspaces in the KB.  If a specific workspace is provided,
;;; old-module-assignment-of-specific-workspace? should be the old module
;;; assignment, if any, so we can update the frame notes for that module if
;;; needed.

(defun update-module-related-frame-notes-for-all-workspaces
    (&optional specific-workspace-with-module-assignment-change?
	       old-module-assignment-of-specific-workspace?)
  (when (and (not inhibit-updating-module-related-frame-notes-for-all-workspaces?)
	     (not releasing-kb?))
    (with-updates-to-representations-supressed
      (module-information 'frame-status-and-notes)
      (let ((suppress-updating-of-slot-value-representations? nil))
						; special, bound by load-kb
	(cond (specific-workspace-with-module-assignment-change?
	       ;; If we're only changing the module assignment of a single
	       ;; workspace, check the old module assignment (if any) to see if
	       ;; it's now empty (i.e. has no workspaces assigned to it) and
	       ;; should be deleted from the particulars lists of the relevant
	       ;; frame notes on the installed module-information system table.
	       ;; Leave the rest of the particulars intact.  -dougo, 2/9/05
	       (when (and old-module-assignment-of-specific-workspace?
			  (null
			    (workspaces-belonging-to-this-module
			      old-module-assignment-of-specific-workspace?)))
		 (delete-from-frame-note-particulars-list
		   old-module-assignment-of-specific-workspace?
		   'workspaces-belong-to-unrequired-modules
		   module-information)
		 (delete-from-frame-note-particulars-list
		   old-module-assignment-of-specific-workspace?
		   'workspaces-belong-to-non-existant-modules
		   module-information)))
	      (t
	       ;; Otherwise, we're checking ALL workspaces, so delete the frame
	       ;; notes from the installed module-information system table
	       ;; because they'll be reconstructed as workspaces with bogus
	       ;; module assignments are found.
	       (delete-multiple-frame-notes-if-any
		 '(workspaces-belong-to-unknown-modules ; obsolete
		   workspaces-belong-to-unrequired-modules
					; ^-- replaces the obsolete
		   workspaces-belong-to-non-existant-modules)
		 module-information)))
	
	;; Encache module-required-p information so, within the main loop,
	;; cached-module-is-required-p can be used instead of
	;; kb-requires-module-p, which is relatively expensive:
	(propagate-kb-requires-module-p-to-all-modules)
	(cond
	  (specific-workspace-with-module-assignment-change?
	   (update-module-related-frame-notes-of-workspace
	     specific-workspace-with-module-assignment-change?))
	  (t
	   (loop for kb-workspace
		     being each class-instance of 'kb-workspace	    
		 do (update-module-related-frame-notes-of-workspace
		      kb-workspace))))

	;; The rest of the code updates module-information frame notes.  
	
	(unless specific-workspace-with-module-assignment-change?
	  (update-module-related-circularity-frame-notes))
	
	;; TO DO! Remove tests that are unnecessary given a non-nil first arg,
	;; below!  We just don't have time today.  (MHD 8/16/96)
	
	;; Various notes on all module-information system tables:
	(loop for module-information-instance
		  being each class-instance of 'module-information
	      as module?
		 = (top-level-kb-module? module-information-instance)
	      initially
		(delete-multiple-frame-notes-if-any
		  '(modules-that-exist-are-unknown ; obsolete
		    modules-that-exist-are-not-required ; replaces the obsolete
		    modules-required-by-kb-do-not-exist
		    module-is-empty-but-that-is-ok)
		  module-information)
	      do (with-updates-to-representations-supressed
		     (module-information-instance 'frame-status-and-notes)
		   
		   ;; Do note on installed module-information system table
		   ;; for MODULE-EXISTS-BUT-IS-UNKNOWN and note on module-information
		   ;; instances for MODULE-EXISTS-BUT-IS-UNKNOWN:
		   (if (and module?
			    (not (cached-module-is-required-p
				   module-information-instance)))
		       (progn
			 (add-to-frame-note-particulars-list-if-necessary
			   module? 'modules-that-exist-are-not-required
			   module-information)
			 (add-frame-note
			   'module-exists-but-is-unknown
			   module-information-instance))
		       (delete-frame-note-if-any
			 'module-exists-but-is-unknown
			 module-information-instance))
		   
		   ;; Do notes on all module-information system tables for
		   ;; MODULE-REQUIRED-BUT-DOES-NOT-EXIST, and on the installed
		   ;; module-information for
		   ;; MODULES-REQUIRED-BY-KB-DO-NOT-EXIST:
		   (delete-frame-note-if-any
		     'module-required-but-does-not-exist
		     module-information-instance)
		   (loop for required-module
			     in (directly-required-kb-modules
				  module-information-instance)
			 when (null (module-exists-p required-module))
			   do (add-to-frame-note-particulars-list-if-necessary
				required-module
				'module-required-but-does-not-exist
				module-information-instance)
			      (add-to-frame-note-particulars-list-if-necessary
				required-module
				'modules-required-by-kb-do-not-exist
				module-information))
		   
		   ;; Do notes on all module-information system tables for
		   ;; MODULE-IS-EMPTY, and on the installed module-information
		   ;; for MODULE-IS-EMPTY-BUT-THAT-IS-OK:
		   (delete-frame-note-if-any
		     'MODULE-IS-EMPTY module-information-instance)
		   (when (and module?
			      (null (workspaces-belonging-to-this-module module?)))
		     (add-frame-note
		       'MODULE-IS-EMPTY
		       module-information-instance)
		     (if (not (cached-module-is-required-p
				module-information-instance))
			 (add-to-frame-note-particulars-list-if-necessary
			   module? 'MODULE-IS-EMPTY-BUT-THAT-IS-OK
			   module-information)))))))))


(defun update-module-related-circularity-frame-notes ()  
  ;; Do note on installed module-information system table
  ;; for CIRCULARITY-IN-MODULE-HIERARCHY:
  (let ((cycles?
	  (find-all-cycles-in-module-hierarchy module-information)))
    (if cycles?
	(add-frame-note
	  'circularity-in-module-hierarchy module-information
	  cycles? t nil)
	(delete-frame-note-if-any
	  'circularity-in-module-hierarchy module-information))))



(defvar all-module-frame-notes-for-workspaces
  '(workspace-does-not-belong-to-any-module
    kb-workspace-is-part-of-unknown-module ; obsolete
    kb-workspace-is-part-of-unrequired-module ; obsolete, newer
    kb-workspace-assigned-to-unrequired-module ; replaces obsolete
    kb-workspace-is-part-of-non-existant-module))


;;; `Update-module-related-frame-notes-of-workspace' updates the frame notes for
;;; module-information (the current binding of the special variable pointing to
;;; the currently installed module-information system table) and for
;;; kb-workspace.
;;;
;;; This expects to be called in a context in which cached-module-is-required-p
;;; and efficient-kb-requires-module-p are valid for every module-information
;;; instance; update-module-related-frame-notes-for-all-workspaces sets this
;;; up by calling propagate-kb-requires-module-p-to-all-modules, q.v.

(defun update-module-related-frame-notes-of-workspace (kb-workspace)
  (cond
    ((parent-of-subworkspace? kb-workspace)
     ;; The following is only for cleanup of sloppyness
     ;; in adding notes to non-top-level kb-workspaces
     ;; prior to 3.0 final release -- remove after 3.0
     ;; & testing that they're being removed as workspaces
     ;; go from/to top-level!  (MHD 2/6/92)

     ;; HQ-2273578:
     ;; This code has been changed to explicitly remove the kb-workspace
     ;; from the particulars of the module-information workspaces-belong-
     ;; to-unspecified-module frame note (if necessary).  It will be
     ;; necessary in the case where the kb-workspace was an unmodularized
     ;; top-level module that has become a subworkspace.
     ;; (ghw 11/20/98)
     (when (frame-status-and-notes kb-workspace)
       (when (frame-has-note-p
	       kb-workspace 'workspace-does-not-belong-to-any-module)
	 (when (and (top-level-kb-module? module-information)
		    (frame-has-note-p
		      module-information 'workspaces-belong-to-unspecified-module))
	   (delete-from-frame-note-particulars-list
	     kb-workspace 'workspaces-belong-to-unspecified-module module-information)))
       (delete-multiple-frame-notes-if-any
	 all-module-frame-notes-for-workspaces kb-workspace)))
    (t
     ;; top-level workspace
     (with-updates-to-representations-supressed
	 (kb-workspace 'frame-status-and-notes)
       (let ((module? (module-this-is-part-of? kb-workspace)))
	 (delete-from-frame-note-particulars-list
	   kb-workspace
	   'workspaces-belong-to-unspecified-module
	   module-information)
	 (when (frame-status-and-notes kb-workspace)
	   (delete-multiple-frame-notes-if-any 
	     all-module-frame-notes-for-workspaces kb-workspace))
	 (cond
	   ((null module?)
	    (unless (frame-being-deleted-p kb-workspace)
	      ;; Do note on workspace for
	      ;; WORKSPACE-DOES-NOT-BELONG-TO-ANY-MODULE
	      ;; and WORKSPACES-BELONG-TO-UNSPECIFIED-MODULE:
	      
	      (cond
		((top-level-kb-module? module-information)
		 (add-to-frame-note-particulars-list-if-necessary
		   kb-workspace 'workspaces-belong-to-unspecified-module
		   module-information)
		 (add-frame-note 
		   'workspace-does-not-belong-to-any-module
		   kb-workspace)))))
	   (t
	    (let ((module-information-instance?
		    (module-information-instance-for-module? module?)))
	      (unless (and module-information-instance?
			   (cached-module-is-required-p
			     module-information-instance?))
		;; Do particular of note on installed
		;; module-information system table for
		;; WORKSPACES-BELONG-TO-UNREQUIRED-MODULES, and also note
		;; on workspace for
		;; kb-workspace-assigned-to-unrequired-module:
		(add-to-frame-note-particulars-list-if-necessary
		  module? 'workspaces-belong-to-unrequired-modules
		  module-information)
		(add-to-frame-note-particulars-list-if-necessary
		  module? 'kb-workspace-assigned-to-unrequired-module
		  kb-workspace))
	      
	      (unless module-information-instance? ; module exists
		;; Do particular of note on installed module-information
		;; system table for
		;; WORKSPACES-BELONG-TO-NON-EXISTANT-MODULES, and also note
		;; on workspace for non-existant-module-assigned-workspaces
		;; KB-WORKSPACE-IS-PART-OF-NON-EXISTANT-MODULE:
		(add-to-frame-note-particulars-list-if-necessary
		  module? 'workspaces-belong-to-non-existant-modules
		  module-information)
		(add-to-frame-note-particulars-list-if-necessary
		  module? 'kb-workspace-is-part-of-non-existant-module
		  kb-workspace))))))))))

;; Module-required-p is too expensive as currently implemented to be called so
;; many times.  It should be recoded and/or have its results cached to speed
;; up this function.

;; Rename ...-for-all-TOP-LEVEL-... ?!









;;;; Useful KB Modularity Functions for External Use



;;; `Get-modules-that-require-this-module' returns a gensym-list of the modules
;;; that require target-module.  Note that target-module need not be required by
;;; the KB for this to work.  And also note that the KB need not be consistently
;;; modularized for this to work. Finally, note that this list does not include
;;; target-module itself.

(defun get-modules-that-require-this-module (target-module)
  (loop for module-information-instance
	  being each class-instance of 'module-information
	as module? = (top-level-kb-module? module-information-instance)
	when (and module?
		  (not (eq module? target-module))
		  (module-requires-module-p module? target-module))
	  collect module? using gensym-cons))


;;; `Top-level-kb-module-p' is true iff module is the top-level KB module.

(defun top-level-kb-module-p (module)
  (eq module-information (module-information-instance-for-module? module)))


;;; `Tformat-warning-about-modules-that-require-this-if-necessary' writes to the
;;; current output string (using tformat, et al) a warning about module
;;; dependencies if there are any.  If it does not need to write anything, it
;;; returns nil.  Otherwise, it returns true after writing an appropriate message.
;;;
;;; The information conveyed in the message is:
;;;
;;;   (a) whether module is required by the KB
;;;
;;; and
;;;
;;;   (b) which modules require module, directly or indirectly

(defun tformat-warning-about-modules-that-require-this-if-necessary (module)
  (let ((kb-requires-module-p (kb-requires-module-p module))
	(modules-that-require-this (get-modules-that-require-this-module module)))
    (cond
      ((and modules-that-require-this
	    (not (top-level-kb-module-p module)))
       (tformat				; kludgey
	 "~%~%Warning: this module is ~arequired by the KB, ~a is ~
          required directly or indirectly by "
	 (if kb-requires-module-p "" "not ")
	 (if kb-requires-module-p "and in particular" "but"))
       (tformat "~L,&." modules-that-require-this) ; includes period at end of sentence
       t)
      (t nil))))

;; COnsider not saying "this module is required by the KB" on the theory that it's
;; assumed, and that we can just point out the other case, "not required".
;;
;; Consider just listing _directly_ required modules, and labelling accordingly.
;;
;; Review with real users.






;;; Kb-is-modularized-p is true if there is a top-level module, i.e.,
;;; (top-level-kb-module? module-information) is non-nil, or if the
;;; installed module-information system table has non-nil in its
;;; frame-status-and-notes slot, indicating that there is inconsistencies
;;; of some sort in modularity.

;;; Note that this depends on the frame-status-and-notes of module-information
;;; being up-to-date; therefore functions involved with keeping it up-to-date
;;; obviously can't use this function.

(defun kb-has-modularity-information-p ()
  (or (top-level-kb-module? module-information)
      (frame-status-and-notes module-information)))










  

;;;; Module Consistency Frame Notes




;;; ... Module names are generally printed in all-caps, e.g, "UTILITIES", not
;;; "utilities".



;;; Obsolete-frame-note-types-from-modularity-development is a list of obsolete
;;; types of frame notes, and their successors, if any.  These notes were all at
;;; one time used in Alpha versions of G2 for the modularity facilities.
;;;
;;; The list is of the form
;;;
;;;    ( { frame-note-type | (frame-note-type . successor-frame-note-type) } )
;;;
;;; Something may want to be done about getting rid of these in the final released
;;; versions.  (MHD 12/23/91)
;;;
;;; It is an error for this to be called more than once with the same first 
;;; argument (frame-note-type) but a different second argument (successor-type?).

(defvar obsolete-frame-note-types-from-modularity-development nil)

(defmacro declare-obsolete-modularity-frame-note-type
	  (frame-note-type &optional successor-type?)
  `(unless (assoc ',frame-note-type
		  obsolete-frame-note-types-from-modularity-development)
     (push
       '(,frame-note-type . ,successor-type?)
       obsolete-frame-note-types-from-modularity-development)))




;;; kb-workspace-assigned-to-unrequired-module ... to be called with a list
;;; containing a single module as the particulars var.
;;; Example:
;;; 
;;;   the module UTILITYS is not required by the KB
;;;
;;; The misspelling is intentional; it is often the cause of this
;;; particular problem in the first place.

(def-frame-note-writer kb-workspace-assigned-to-unrequired-module
		       (listed-module kb-workspace)
  (declare (ignore kb-workspace))
  (tformat "the module ~a is not required by the KB" (first listed-module)))

;; Get rid of the "kb-" prefix?!

(declare-obsolete-modularity-frame-note-type
  kb-workspace-is-part-of-unknown-module
  kb-workspace-assigned-to-unrequired-module)

(def-frame-note-writer kb-workspace-is-part-of-unknown-module	; OBSOLETE - REMOVE AFTER 3.0 RELEASE
		       (listed-module kb-workspace)
  (funcall-simple-compiled-function
    (frame-note-writer 'kb-workspace-assigned-to-unrequired-module)
    listed-module kb-workspace))


(declare-obsolete-modularity-frame-note-type	; temporary came on the scene as a goof for a week or so (MHD)
  kb-workspace-is-part-of-unrequired-module
  kb-workspace-assigned-to-unrequired-module)

(def-frame-note-writer Kb-workspace-is-part-of-unrequired-module	; OBSOLETE - REMOVE AFTER 3.0 RELEASE
		       (listed-module kb-workspace)
  (funcall-simple-compiled-function
    (frame-note-writer 'kb-workspace-assigned-to-unrequired-module)
    listed-module kb-workspace))

;; NOTE -- was in for about one week, dec. 23 to Jan. 2! (MHD 1/2/92)

;; Note: "unknown" was used to mean "not required by the KB" in earlier versions
;; of the design.  (MHD 1/16/92)




;;; 


;;; Kb-workspace-is-part-of-non-existant-module ... to be called with a list
;;; containing a single module as the particulars var.
;;; Example:
;;; 
;;;   the module UTILITYS does not exist

(def-frame-note-writer kb-workspace-is-part-of-non-existant-module
		       (listed-module kb-workspace)
  (declare (ignore kb-workspace))
  (tformat "the module ~a does not exist" (first listed-module)))

;; Eliminate the "kb-" from the name?!





;;; `Workspace-does-not-belong-to-any-module' ...
;;; Example:
;;;
;;;    the top-level module is MY-FACTORY, but this workspace is
;;;    not assigned to any module

(def-frame-note-writer workspace-does-not-belong-to-any-module
		       (particulars kb-workspace)
  particulars kb-workspace
  (tformat "the top-level module is ~a, but this workspace is not assigned to any module"
	   (get-slot-value module-information 'top-level-kb-module?)))	; fwd. ref.
  


;;; The frame-note writer for workspaces-belong-to-unspecified-module ... only to be
;;; present on the installed module-information instance.
;;; Example:
;;;
;;;     4 workspaces are not assigned to any module

(def-frame-note-writer workspaces-belong-to-unspecified-module
		       (particulars top-level-module-information)
  (declare (ignore top-level-module-information
		   ; particulars
		   ))
  (let ((number
	  (length particulars)
;	  (loop for kb-workspace being each class-instance
;		    of 'kb-workspace
;		count (and (null (parent-of-subworkspace? kb-workspace))
;			   (null (module-this-is-part-of? kb-workspace))
;			   (not (frame-being-deleted-p kb-workspace))))
	  ))
    (tformat "~a workspace~a ~a not assigned to any module"
	     number
	     (if (=f number 1) "" "s")
	     (if (=f number 1) "is" "are")
	     (if (=f number 1) "its" "their"))))




;;; The frame-note writer for workspaces-belong-to-unrequired-modules ... only to be
;;; present on the installed module-information instance.
;;; Example:
;;;
;;;    the modules UTILITYS, BOOILERS, and COKERS have workspaces assigned
;;     to them but are not required by the KB.

(def-frame-note-writer workspaces-belong-to-unrequired-modules
		       (problem-modules top-level-module-information)
  (declare (ignore top-level-module-information))
  (let ((number (length problem-modules)))
    (tformat
      "the module~a "
      (if (=f number 1) "" "s"))
    (let ((write-symbols-in-lower-case? nil))
      (write-symbol-list problem-modules "," "and"))
    (tformat
      " ~a workspaces assigned to ~a but ~a not required by the KB"
      (if (=f number 1) "has" "have")
      (if (=f number 1) "it" "them")
      (if (=f number 1) "is" "are"))))

(declare-obsolete-modularity-frame-note-type
  workspaces-belong-to-unknown-modules
  workspaces-belong-to-unrequired-modules)


(def-frame-note-writer workspaces-belong-to-unknown-modules (problem-modules)	; OBSOLETE - REMOVE AFTER 3.0 RELEASE
  (funcall-simple-compiled-function 
    (frame-note-writer 'workspaces-belong-to-unrequired-modules)
    problem-modules nil))

;;; The frame-note writer for kb-unsavable-due-to-module-inconcistency ...
;;; called only for the currently installed instance of a module-information
;;; system table.
;;; Example:
;;; 
;;;     this KB can not be saved because the modules are inconsistent

(def-frame-note-writer kb-unsavable-due-to-module-inconcistency (particulars)
  (declare (ignore particulars))
  (tformat
    "this KB cannot be saved because the modules are not consistent"))




;;; The frame-note writer for module-has-no-workspaces-assigned-to-it ... called
;;; for an instance of a module-information system table, which may be assumed
;;; to have in its top-level-kb-module? slot the name of the offending module.
;;; Example:
;;;
;;;   no workspaces are assigned to the module UTILITIES

(def-frame-note-writer module-has-no-workspaces-assigned-to-it
		       (particulars module-information-instance)
  (declare (ignore particulars))
  (let ((write-symbols-in-lower-case? nil))
    (tformat
      "no workspaces are assigned to the module ~a"
      (top-level-kb-module? module-information-instance))))



;;; The frame-note writer for workspaces-belong-to-non-existant-modules ...  is
;;; only to be present on the installed module-information instance.
;;; Problem-modules should be the list of all of the non-existant modules in the
;;; KB.
;;; Example:
;;; 
;;;     the modules UTILITYS and BOOLERS do not exist, but workspaces are
;;;     assigned to them

(def-frame-note-writer workspaces-belong-to-non-existant-modules
		       (problem-modules top-level-module-information)
  #-development
  (declare (ignore top-level-module-information))
  #+development
  (assert (eq top-level-module-information module-information))
  (let ((number (length problem-modules)))
    (tformat
      "the module~a "
      (if (=f number 1) "" "s"))
    (let ((write-symbols-in-lower-case? nil))
      (write-symbol-list problem-modules "," "and"))
    (tformat
      " do~a not exist, but workspaces are assigned to ~a"
      (if (=f number 1) "es" "")
      (if (=f number 1) "it" "them"))))

;; (Should the word "workspaces" in the note always be plural?)








;;; The frame-note writer for module-not-required-but-has-workspaces-assigned-to-it
;;; ...
;;; Example:
;;;
;;;    there are workspaces assigned to the module UTILITIES, but it is not
;;;    required by the KB

(def-frame-note-writer module-not-required-but-has-workspaces-assigned-to-it
		       (particulars module-information-instance)
  (declare (ignore particulars))
  (tformat
    "there are workspaces assigned to the module ~a, but it is not required by the KB"
    (top-level-kb-module? module-information-instance)))



;;; The frame-note writer for module-exists-but-is-unknown ...  only to be
;;; present on a module-information instance, and only one that has non-nil for
;;; top-level-kb-module?
;;; Example:
;;;
;;;     the module UTILITIES is not required by the KB

(def-frame-note-writer module-exists-but-is-unknown
		       (particulars module-information-instance)
  (declare (ignore particulars))
  #+development
  (test-assertion
    (top-level-kb-module? module-information-instance))
  (tformat
    "the module ~a is not required by the KB"
    (top-level-kb-module? module-information-instance)))






;;; The frame-note writer for modules-that-exist-are-not-required ...  only to be
;;; present on the installed module-information instance.  Note that the
;;; top-level-kb-module?  slot of top-level-module-information may be nil or a
;;; module.  Problem-modules should be the list of all of the unknown modules in
;;; the KB.
;;; Example:
;;;
;;;    the modules UTILITIES, BOILERS, and DSP exist but are not required by 
;;;    the KB

(def-frame-note-writer modules-that-exist-are-not-required
		       (problem-modules top-level-module-information)
  #-development
  (declare (ignore top-level-module-information))
  #+development
  (assert (eq top-level-module-information module-information))
  (let ((number (length problem-modules))
	(write-symbols-in-lower-case? nil))
    (tformat
      "the module~a "
      (if (=f number 1) "" "s"))
    (write-symbol-list problem-modules "," "and")
    (tformat
      " exist~a but ~a not required by the KB"
      (if (=f number 1) "s" "")
      (if (=f number 1) "is" "are"))))

(declare-obsolete-modularity-frame-note-type
  modules-that-exist-are-unknown
  modules-that-exist-are-not-required)

(def-frame-note-writer modules-that-exist-are-unknown	; OBSOLETE - REMOVE AFTER 3.0 RELEASE
		       (problem-modules top-level-module-information)
  (funcall-simple-compiled-function
    (frame-note-writer 'modules-that-exist-are-not-required)
    problem-modules top-level-module-information))



;;; The frame-note writer for module-is-empty ...  only to be present on a
;;; module-information instance, and only one that has non-nil for
;;; top-level-kb-module?
;;; Example:
;;;
;;;    no workspaces are assigned to the module OLD-UTILITIES

(def-frame-note-writer module-is-empty
		       (particulars module-information-instance)
  (declare (ignore particulars))
  #+development
  (assert (top-level-kb-module? module-information-instance))
  (tformat
    "no workspaces are assigned to the module ~a"
    (top-level-kb-module? module-information-instance)))




;;; The frame-note writer for module-is-empty-but-that-is-ok ...  only to be
;;; present on the top-level (installed) module-information instance.
;;; Example:
;;;
;;;    the modules X, Y, and Z have no workspaces assigned to them but since they are
;;;    not required by the top level module of this KB there will be no problem when
;;;    the KB is reloaded

(def-frame-note-writer module-is-empty-but-that-is-ok
		       (problem-modules top-level-module-information)
  #-development
  (declare (ignore top-level-module-information))
  #+development
  (assert (eq top-level-module-information module-information))
  (let ((number (length problem-modules))
	(write-symbols-in-lower-case? nil))
    (tformat "no workspaces are assigned to the module~a "
	     (if (=f number 1) "" "s"))
    (write-symbol-list problem-modules nil)
    (tformat
      ", but since ~a ~a not required by this KB, it is probably best to ~
       delete ~a module~a"
      (if (=f number 1) "it" "they")
      (if (=f number 1) "is" "are")
      (if (=f number 1) "this" "these")
      (if (=f number 1) "" "s"))))

;; Module-is-empty-but-that-is-ok is usually a mistake, since it means that
;; the module has nothing at all in it except for system tables.  It is possible,
;; however, that someone would want this, so we should not make this a fatal
;; error, I believe. (MHD 1/29/92)





;;; `Module-required-but-does-not-exist' ...
;;; Example:
;;; 
;;;      the modules A, B, and C are required here but do not exist

(def-frame-note-writer module-required-but-does-not-exist 
		       (problem-modules module-information-instance)
  (declare (ignore module-information-instance))
  (let ((number (length problem-modules))
	(write-symbols-in-lower-case? nil))
    (tformat "the module~a " (if (=f number 1) "" "s"))
    (write-symbol-list problem-modules "," "and")
    (tformat
      " ~a required here but do~a not exist"
      (if (=f number 1) "is" "are")
      (if (=f number 1) "es" ""))))

;; This would better have been called modules-required-but-do-not-exist,
;; it may involve more than one module.  The version for the entire KB
;; below corrects this mistake, hence the slight, additional naming
;; inconsistency between the two.




;;; `Modules-required-by-kb-do-not-exist' ...
;;; Example:
;;; 
;;;      the modules A, B, and C are required by the KB but do not exist

(def-frame-note-writer modules-required-by-kb-do-not-exist
		       (problem-modules top-level-module-information)
  (declare (ignore top-level-module-information))
  (let ((number (length problem-modules))
	(write-symbols-in-lower-case? nil))
    (tformat "the module~a " (if (=f number 1) "" "s"))
    (write-symbol-list problem-modules "," "and")
    (tformat
      " ~a required by the KB but do~a not exist"
      (if (=f number 1) "is" "are")
      (if (=f number 1) "es" ""))))




(def-frame-note-writer circularity-in-module-hierarchy 
		       (cycles? top-level-module-information)
  (declare (ignore top-level-module-information))
  (when cycles?
    (tformat "the module hierarchy has the following ~a~acycle~a: "
	     (if (cdr cycles?) (length cycles?) "")
	     (if (cdr cycles?) " " "")
	     (if (cdr cycles?) "s" ""))
    (let ((write-symbols-in-lower-case? nil))
      (loop for (cycle . more?) on cycles?
	    do (write-symbol-list cycle "--")
	       (tformat "--")
	       (twrite-symbol (car cycle) (not write-symbols-in-lower-case?))
	       (if more? (tformat "; "))))))








;;;; Checking Module Definition Consistency








;;; Check-module-definition-consistency ...

(defun check-module-definition-consistency (module)
  ;; This should
  ;; 
  ;; (1) Check that there is no definition in module that depends on definitions
  ;; that are not in either module or in modules required by module.
  ;;
  ;; (2) Check that there are no definitions in module that have instances in
  ;; modules that are required by module.
  ;;
  ;; (3) Apply this to all modules required by module.
  (declare (ignore module)))





;;; Check-savability-of-module is to be called from save-kb in order to check
;;; whether module can be saved and, if not, to inform the user of the nature
;;; of the problem on the logbook and/or to point to problems given by frame
;;; notes of various items in the KB.  It return non-nil if module may be saved;
;;; otherwise, it returns nil.

;;; [The above function should be written.  But for now, I'm starting with the
;;; function check-savability-of-kb-in-terms-of-modularity.]





(def-global-property-name format-string-for-kb-modularity-problem)
(def-global-property-name format-args-for-kb-modularity-problem)
(def-global-property-name particulars-printer-for-kb-modularity-problem)

(defmacro def-kb-modularity-problem
    (problem-name format-string? &optional list-of-format-args
		  printer-name-or-printer-lambda-list-for-particulars?
		  &body printer-body?)
  `(progn
     ,@(when format-string?
	 `((setf (format-string-for-kb-modularity-problem ',problem-name)
		 ',format-string?)))
     ,@(when list-of-format-args
	 `((when ,list-of-format-args
	     (setf (format-args-for-kb-modularity-problem ',problem-name)
		   ',list-of-format-args))))
     ,@(when printer-name-or-printer-lambda-list-for-particulars?
	 (cond
	   ((symbolp printer-name-or-printer-lambda-list-for-particulars?)
	    (if printer-body?
		(error "you can't have a body and the name of a function"))
	    `((setf (particulars-printer-for-kb-modularity-problem ',problem-name)
		    ',printer-name-or-printer-lambda-list-for-particulars?)))
	   ((or (not (listp printer-name-or-printer-lambda-list-for-particulars?))
		(not (= (length printer-name-or-printer-lambda-list-for-particulars?)
			1)))
	    (error "illegal arglist: ~a; the printer function must ~
                        have a fixed argument list of length 1"
		   printer-name-or-printer-lambda-list-for-particulars?))
	   (t
	    (let ((printer-name (format-symbol "PRINT-~a" problem-name)))
	      `((defun ,printer-name
		    ,printer-name-or-printer-lambda-list-for-particulars?
		  . ,printer-body?)
		(setf (particulars-printer-for-kb-modularity-problem ',problem-name)
		      ',printer-name))))))
     ',problem-name))


(def-named-dynamic-extent modularity-checking (module modules))


(defvar-of-named-dynamic-extent current-modularity-problems
    modularity-checking)

(defvar-of-named-dynamic-extent inspect-command-for-modularity-problems?
    modularity-checking)

(defvar-of-named-dynamic-extent current-modularity-problems-fatal?
    modularity-checking)



;;; Do-modularity-checking ... returns at most one value, the first value that
;;; is results from evaluating body.

(defmacro do-modularity-checking ((inspect-command?) &body body)
  `(with-named-dynamic-extent* modularity-checking
       ((current-modularity-problems nil)
	(inspect-command-for-modularity-problems? ,inspect-command?)
	(current-modularity-problems-fatal? nil))
     (prog1
	 (progn ,@body)
       (report-on-modularity-checking)
       (reclaim-modularity-problems))))


(defun reclaim-modularity-problems ()
  (reclaim-gensym-tree current-modularity-problems))


(defun emit-kb-modularity-problem
    (seriousness problem-name &optional listed-particulars?)
  (gensym-push listed-particulars? current-modularity-problems)
  (gensym-push problem-name current-modularity-problems)
  (case seriousness
    (fatal (setq current-modularity-problems-fatal? t))
    (advisory 
     ;; others?
     )))


(defun report-on-modularity-checking ()
  (loop with inspect-messages = '()
	for (problem listed-particulars) on current-modularity-problems by #'cddr
	as format-string? = (format-string-for-kb-modularity-problem problem)
	as format-args? = (format-args-for-kb-modularity-problem problem)
	as particulars-printer?
	  = (particulars-printer-for-kb-modularity-problem problem)
	when format-string?
	  do (cond
	       (inspect-command-for-modularity-problems?
		(eval-push
		  (apply #'tformat-text-string format-string? format-args?)
		  inspect-messages))
	       (t
		(apply #'notify-user format-string? format-args?)))
	when particulars-printer?
	  do (funcall particulars-printer? listed-particulars)
	finally
	  (when inspect-command-for-modularity-problems?
	    (multiple-add-to-results-for-inspect-command
	      (nreverse inspect-messages)
	      inspect-command-for-modularity-problems?))))

;;; `Check-frame-note-based-modularity-problems' ... seriousness can only be
;;; either NIL or FATAL.

(defun check-frame-note-based-modularity-problems (seriousness note-names)
  (loop for note-name in note-names
	do (check-one-frame-note-based-modularity-problem
	     seriousness note-name)))	

(defun check-one-frame-note-based-modularity-problem (seriousness note-name)
  (when (frame-has-note-p module-information note-name)
    (emit-kb-modularity-problem seriousness note-name)))





;;; What this should do:
;;;
;;;   (1) for notes that say "see the installed module-information system table
;;;   ...", just display the table (with relevant attributes, i.e., notes, etc.)
;;;
;;;   (2) for notes that say something like "there are N problem items" (for
;;;   some N >= 100), print all of the frames.
;;;
;;;   (3) Count the number of frames that have problems and display that in the
;;;   results table.  When we add a programmatic access, users will be able to
;;;   access this.
;;;   

(def-kb-modularity-problem circularity-in-module-hierarchy ; same as frame note name
    "There are cycles among the modules required by this KB; see the ~
     installed module-information system table for further information.")

(def-kb-modularity-problem modules-that-exist-are-not-required ; same as frame note
    "Modules that exist are not required by the KB; see the ~
     installed module-information system table for further information.")

(def-kb-modularity-problem workspaces-belong-to-unspecified-module
    "Workspaces exist whose module assignment is UNSPECIFIED; see the ~
     installed module-information system table for further information.")

(def-kb-modularity-problem workspaces-belong-to-unrequired-modules
    "Workspaces belong to modules that are not required by the KB; see the ~
     installed module-information system table for further information.")

(def-kb-modularity-problem modules-required-by-kb-do-not-exist
    "Modules required by the KB do not exist; see the ~
     installed module-information system table for further information.")


(def-kb-modularity-problem classes-not-defined-in-any-module
  nil nil (classes)
  (cond
    (inspect-command-for-modularity-problems?
     (loop with items = (eval-list (tformat-text-string 
				     "These class definitions are not assigned to any module."))
	   for class in classes
	   as class-definition = (class-definition class)
	   do
       (eval-push class-definition items)
	   finally
     (multiple-add-to-results-for-inspect-command
       (nreverse items)
       inspect-command-for-modularity-problems?)))
    ((<f (length classes) 100)
     (notify-user
       "The following classes are not assigned to any module: ~L,&"
       classes))
    (t
     (notify-user
       "There are ~d classes that are not assigned to any module."
       (length classes)))))


(def-kb-modularity-problem classes-whose-superiors-are-not-defined-in-required-modules
    nil nil (classes)
    (cond
      (inspect-command-for-modularity-problems?
       (loop with items = (eval-list
			    (tformat-text-string
			      "These class definitions do not have their superior assigned to their module hierarchy."))
	     for class in classes
	     as class-definition = (class-definition class)
	     do
	 (eval-push class-definition items)
	     finally
	 (multiple-add-to-results-for-inspect-command	   
	   (nreverse items)
	   inspect-command-for-modularity-problems?)))
      ((<f (length classes) 100)
       (notify-user
	 "The following classes do not have their superior assigned to their module hierarchy: ~L,&"
	 classes))
      (t
       (notify-user
	 "There are ~d classes that do not have their superior assigned to their module hierarchy."
	 (length classes)))))



(def-kb-modularity-problem classes-with-instances-in-modules-that-do-not-require-them
    nil nil (a-list-of-classes)
    (cond
      (inspect-command-for-modularity-problems?
       (loop with items 
	       = (eval-list
		   (tformat-text-string
		     "These class definitions are not in the module hierarchy of the indicated instances."))
	     for (class . instances) in a-list-of-classes
	     as class-definition = (class-definition class)
	     do
	 (eval-push class-definition items)
	 (loop for instance in instances
	       do
	   (eval-push instance items))
	     finally
	       (multiple-add-to-results-for-inspect-command
		 (nreverse items)
		 inspect-command-for-modularity-problems?)))
      (t
       (loop for (class . instances) in a-list-of-classes
	     as number = (length instances)
	     do (notify-user
		  "The class ~a has ~a instance~a that do~a not reside in any module that ~
                    requires the module of the class (~a)."
		  class number
		  (if (=f number 1) "" "s")
		  (if (=f number 1) "es" "")
		  (get-module-block-is-in (class-definition class)))))))




(def-kb-modularity-problem table-in-different-module-than-item-represented
    nil nil
    (listed-represented-frame-and-workspace)
    (let ((represented-frame (first listed-represented-frame-and-workspace))
	  (workspace (second listed-represented-frame-and-workspace)))
      (cond
	(inspect-command-for-modularity-problems?
	 (multiple-add-to-results-for-inspect-command
	   (eval-list
	     (tformat-text-string
	     "~NF has a table on workspace ~NF, which does not ~
                 belong to the same module.  Tables must reside in ~
                 the same module as the item they represent."
	     represented-frame workspace))
	   inspect-command-for-modularity-problems?))
	(t
	 (notify-user
	   "~NF has a table on workspace ~NF, which does not ~
             belong to the same module.  Tables must reside in ~
             the same module as the item they represent. This KB will ~
             not be savable until this problem is resolved."
	   represented-frame workspace)))))





;;; Unmark-all-module-information-instances ...

(defun unmark-all-module-information-instances ()
  (loop for module-information-instance
	    being each strict-class-instance
	    of 'module-information
	do (clear-module-information-instance-mark
	     module-information-instance)))





;;; Find-all-cycles-in-module-hierarchy ... returns nil if ok (no cycles);
;;; otherwise a slot-value list containing all of the cycles it found.  The
;;; caller has the responsibility to reclaim (or incorporate) the slot value
;;; conses that make up the result, if any.
;;;
;;; Each cycle in the resulting list of cycles is of the form
;;;
;;;    ( <1st/last module>
;;;      .
;;;      .
;;;      <2nd-to-last module>)
;;;
;;; That is, the list always leads the first (and really the last) member of the
;;; cycle.  (The choice of which member of the is first is based on closeness
;;; to the root of the module hierarchy.)  The list continues with the children
;;; on the path to where the loop begins and then continues until the last
;;; module before the loop repeats.  Note that it's always the case that
;;; <2nd-to-last module> requires <1st/last module>.  
;;; 
;;; For example, if module M1 requires module M2, M2 requires M1 and M3, M3
;;; requires M4, and M4 requires M2 this would result in
;;;
;;;    ((M1 M2)
;;;     (M2 M3 M4))
;;;
;;; That is, the list always leads with the top of the module hierarchy and the
;;; children on the path to where the loop begins and then continues until the
;;; beginning element of the loop repeats.  Note that all of the elements are
;;; symbols, the names of modules.

(defvar all-cycles-found-so-far-in-module-hierarchy)

(defun-simple module-hierarchy-contains-cyclic-dependency-p
    (module-information-instance)
  (and module-information-instance  ;; should never be nil
       (let ((all-cycles-found-so-far-in-module-hierarchy '())
	     result)
	 (find-all-cycles-in-module-hierarchy-1 module-information-instance nil)
	 (unmark-all-module-information-instances)
	 (setq result (not (null all-cycles-found-so-far-in-module-hierarchy)))
	 (reclaim-slot-value-tree all-cycles-found-so-far-in-module-hierarchy)
	 result)))


(defun find-all-cycles-in-module-hierarchy (module-information-instance)
  (let* ((all-cycles-found-so-far-in-module-hierarchy nil))
    
    
    ;; The following subfunctions collects all the cycles using slot-
    ;; value conses; it leaves the collection in all-cycles-found-so-far-
    ;; in-module-hierarchy; it also leaves all nodes it visited marked,
    ;; which has to be cleaned up by an unmark sweep that follows.
    
    (find-all-cycles-in-module-hierarchy-1 module-information-instance nil)


    ;; Unmark any marked nodes.
    
    (unmark-all-module-information-instances)

    
    ;; Each cycle now contains the actual module-information instances; replace
    ;; each with the module name.  It is assumed here that no instances
    ;; collected can have NIL in the slot giving their module name.
    
    (loop for cycle in all-cycles-found-so-far-in-module-hierarchy
	  do (loop for l on cycle
		   do (setf (car l)
			    (top-level-kb-module? (car l)))))

    
    all-cycles-found-so-far-in-module-hierarchy))






;;; Find-all-cycles-in-module-hierarchy-1 ... Note: this does not find the
;;; trivial cycle from the root to itself.  That is easily handled by the
;;; caller as a special case.

(defun find-all-cycles-in-module-hierarchy-1 (node history-path)
  (set-module-information-instance-mark node)
  (loop for name-for-node-2 in (directly-required-kb-modules node)
	as node-2?
	   = (module-information-instance-for-module? name-for-node-2)
	when node-2?
	  do (let ((cycle? (if node-2? (memq node-2? history-path))))
	       (cond
		 (cycle?
		  ;; collect the cycle, copying conses:
		  (setq all-cycles-found-so-far-in-module-hierarchy
			(slot-value-cons
			  (nconc
			    (copy-list-using-slot-value-conses cycle?)
			    (slot-value-list node))
			  all-cycles-found-so-far-in-module-hierarchy)))
		 ((not (module-information-instance-mark-p node-2?))
		  (let ((temporary-list-history-path-and-node
			  (nconc
			    (copy-list-using-slot-value-conses history-path)
			    (slot-value-list node))))
		    (find-all-cycles-in-module-hierarchy-1
		      node-2? temporary-list-history-path-and-node)
		    ;; reclaim the temporary cons
		    (reclaim-slot-value-list
		      temporary-list-history-path-and-node))))))

  
  ;; Note: the above does not find the trivial cycle from the root to itself.
  ;; That is easily handled by the caller as a special case by evaluating
  ;; 
  ;;   (find-trivial-root-to-root-cycle-if-any module-information-instance)
  ;;   
  ;; It is probably possible to prevent it from being possible at all
  ;; through guards on editing, although that might introduce unnecessary
  ;; frustration to users.
  
  (find-trivial-root-to-root-cycle-if-any node))



;;; Find-trivial-root-to-root-cycle-if-any just adds its arg in a slot-value
;;; cons to all-cycles-found-so-far-in-module-hierarchy if it requires itself;
;;; otherwise, it returns nil.

(defun find-trivial-root-to-root-cycle-if-any (module-information-instance)
  (if (memq (top-level-kb-module? module-information-instance)
	    (directly-required-kb-modules module-information-instance))
      (setq all-cycles-found-so-far-in-module-hierarchy
	    (slot-value-cons
	      (slot-value-list module-information-instance)
	      all-cycles-found-so-far-in-module-hierarchy))))



;;;; Module Maintenence Utilities





;; Moved here from KB-SAVE1




;;; The macro `within-module-p' is true if block is assigned to the designated
;;; module.  The macro `within-module-hierarchy-p' is true if block is assigned
;;; to the designated module's hierarchy, i.e., either is assigned to module, or
;;; any module directly or indirectly required by module.

(def-substitution-macro within-module-p (block module)
  (eq (get-module-block-is-in block) module))

(defun-simple within-module-hierarchy-p (block module)
  (let ((module-block-is-in? (get-module-block-is-in block)))
    (and module-block-is-in?
	 (or (eq module-block-is-in? module)
	     (module-requires-module-p module module-block-is-in?)))))






;;; Get-module-block-is-within-if-required is true if block is in a module
;;; required, directly or indirectly, by module.  Note that this does not
;;; return true of block is in module itself.

(defun-simple get-module-block-is-within-if-required (block module)
  (let ((module-block-is-in? (get-module-block-is-in block)))
    (and module-block-is-in?
	 (module-requires-module-p module module-block-is-in?))))



;;; Within-modules-p returns true iff there is a module M such that
;;; (within-module-p block M).

(defun-simple within-modules-p (block list-of-modules)
  (memq (get-module-block-is-in block)
	list-of-modules))

;; This is too slow -- important ultimately to optimize within-module-p!!!
;; (MHD 1/.../92)
;; -- Better now -- have to improve get-module-block-is-in and/or
;; sort list-of-modules to improve on this.  (MHD 2/4/92)






;;; Delete-as-workspace-belonging-to-module is invoked with delete-case? true
;;; when module is deleted from (module-this-is-part-of? kb-workspace), and
;;; with delete-case? false when module is added.

(defun add-or-delete-as-workspace-belonging-to-module
       (kb-workspace module delete-case?)
  (if delete-case?
      (setf (workspaces-belonging-to-this-module module)
	    (delete-slot-value-element
	      kb-workspace
	      (workspaces-belonging-to-this-module module)))
      (slot-value-pushnew
	kb-workspace
	(workspaces-belonging-to-this-module module))))
    
;; Ultimately, this function could have the smarts about incrementally
;; maintaining module consistency; for now, I feel that goal is at odds with
;; making this software work in a timely fashion, so for now, the batch fix-all
;; function is just called from all over the place.  If the smarts were being
;; added, consider that this function must be sensitive to being called in two
;; special situation: (1) when (frame-being-delete-p kb-workspace) is true, and
;; (2) when (parent-of-subworkspace?  kb-workspace) is true.  Case (1) is for
;; when this is being called as a side affect of deleting kb-workspace, by the
;; reclaimer for module-this-is-part-of?, and thus having that slot changed to
;; nil just to cause notes to be reconsidered.  Case (2) is for when
;; kb-workspace is being added as a subworkspace, thereby ceasing to be a
;; top-level workspace, and also just for the purpose of having notes
;; reconsidered.  In both cases, it avoids adding anything to the frame notes
;; that it might otherwise, since the new status -- either deleted or being a
;; subworkspace -- means it will not be subject to the same constraints.  (MHD
;; 12/10/91)




;;; Module-exists-p is true if module is the value of the top-level-kb-module
;;; slot of some module-information system table instance.

(defun-simple module-exists-p (module)
  (module-information-instance-for-module? module))





;;; Kb-requires-module-p is true if module is required.  A `module required by
;;; the KB' is one that is the name of the top-level module, or is required by
;;; that module, directly or indirectly.  See also module-exists-p.

;;; This works even if the module hierarchy has cycles.

(defun-simple kb-requires-module-p (module)
  (or (eq module (top-level-kb-module? module-information))
      (prog1 (module-required-p-1 module module-information)
	(unmark-all-module-information-instances))))


;;; Module-requires-module-p is true if module-1 requires module-2, directly or
;;; indirectly.

;;; This works even if the module hierarchy has cycles.

(defun-simple module-requires-module-p (module-1 module-2)
  (prog1
      (let ((module-information-instance?
	      (module-information-instance-for-module? module-1)))
	(if module-information-instance?
	    (module-required-p-1 module-2 module-information-instance?)))
    (unmark-all-module-information-instances)))

;; It's assumed no unmarking sweep is needed, i.e., that all other code leaves
;; this set of marks perfectly unset.

;; If the above is ever interrupted, things will be screwed up, since
;; things will be marked that shouldn't be.

(defun-simple module-required-p-1 (module node)
  (set-module-information-instance-mark node)
  (loop for directly-required-module
	    in (directly-required-kb-modules node)
	thereis
	(or (eq module directly-required-module)
	    (let ((module-information-instance?
		    (module-information-instance-for-module? directly-required-module)))
	      (and module-information-instance?
		   (not (module-information-instance-mark-p
			  module-information-instance?))
		   (module-required-p-1
		     module module-information-instance?))))))




;;; `propagate-kb-requires-module-p-to-all-modules' sets up a context in which
;;; the slot cached-module-is-required-p may be tested to determine if a module
;;; is required by the KB for all module-information instances.
;;; `Propagate-module-requires-module-p-to-all-modules' is similar except that
;;; it works with respect to its argument module, i.e., it sets up a context in
;;; which the knowledge is cached as to whether each module is required by the
;;; argument module.
;;;
;;; After the invocation of either function, the test function
;;; `efficient-kb-requires-module-p' can be tested on a module name symbol.  The
;;; macro `efficient-kb-requires-module-p' will run dramatically faster than
;;; kb-requires-module-p, but in this context it should yield exactly equivalent
;;; results.  The macro `efficient-module-requires-module-p' is to be used to
;;; test if module-1 requires module-2 in a context in which being required by
;;; module-1 or not has been cached.  Note that slot accessor
;;; `cached-module-is-required-p' may also be validly tested directly on a
;;; module-information instance; this is somewhat faster, especially if the
;;; instance is stored in a local variable.
;;;
;;; For the duration of the context set up, it is an error to either change the
;;; the module hierarchy configuration in any way or to set up any other
;;; context.  It is the programmer's responsibility to ensure that these
;;; constraints are met.

(defun-void propagate-kb-requires-module-p-to-all-modules ()
  (propagate-module-requires-module-p-to-all-modules ; propagate down from top,
    (top-level-kb-module? module-information))       ;   leaving top out
  (setf (cached-module-is-required-p module-information) t)) ; then do top

(defun-void propagate-module-requires-module-p-to-all-modules (module)
  (loop for module-information-instance
	    being each class-instance of 'module-information
	do (setf (cached-module-is-required-p module-information-instance) nil))
  (let ((instance? (module-information-instance-for-module? module)))
    (when instance?
      (propagate-cached-module-is-required-p-1 instance?))))

(defun-void propagate-cached-module-is-required-p-1
    (module-information-instance)
  (loop for module
	    in (directly-required-kb-modules module-information-instance)
	as instance? = (module-information-instance-for-module? module)
	when (and instance?
		  (not (cached-module-is-required-p ; mark of previous visit
			 instance?)))
	  do (setf (cached-module-is-required-p instance?) t)
	     (when (directly-required-kb-modules instance?)
	       (propagate-cached-module-is-required-p-1 instance?))))

(defmacro efficient-module-requires-module-p (module-1 module-2)
  `(progn ,module-1 (efficient-kb-requires-module-p ,module-2)))

(defmacro efficient-kb-requires-module-p (module)
  (avoiding-variable-capture (&aux instance?)
    `(let ((,instance? (module-information-instance-for-module? ,module)))
       (and ,instance? (cached-module-is-required-p ,instance?)))))

;; The previous two defs are almost identical because they share the same cached
;; information slot.

;; NOTE: unfortunately, G2 4.1 Rev. 0 did not properly check for a module
;; information instance, which could lead to crashes in some cases.  See bug
;; HQ-1100323 "delete top level module and save aborts G2".  This is being fixed
;; now and may be fixed in a subsequent patch or revision to 4.1.  To transfer
;; the fix, it would be necessary to simply replace the above two definitions,
;; i.e., of the macros efficient-kb-requires-module-p and
;; efficient-module-requires-module-p, with those above in 5.0.  (At least that
;; work based on today's sources, i.e., assuming no further forking of this code
;; from 4.1.)  (MHD 1/8/96)



;;; The macro `with-module-required-by-relationships' executes body in a context
;;; in which it is valid to call efficient-module-required-by-module-p, and returns
;;; the first value that results from that evaluation.

(defmacro make-module-relationship-key (module-1 module-2)
  `(gensym-cons ,module-1 ,module-2))

(defmacro reclaim-module-relationship-key (key)
  `(reclaim-gensym-cons ,key))

(defun-simple module-relationship-key-equal (key-1 key-2)
  (and (eq (car-of-cons key-1) (car-of-cons key-2))
       (eq (cdr-of-cons key-1) (cdr-of-cons key-2))))


(def-hash-table module-required-by-relationships
    :key-reclaimer reclaim-module-relationship-key
    :key-comparitor module-relationship-key-equal)


(defvar module-required-by-relationships)

(defmacro with-module-required-by-relationships (&body body)
  `(let ((module-required-by-relationships
	   (make-module-required-by-relationships)))
     (prog1
	  (progn . ,body)
       (reclaim-module-required-by-relationships
	 module-required-by-relationships))))

;;; `Efficient-module-required-by-module-p' is true if module-1 is required
;;; by module-2, i.e., if (module-requires-module-p module-2 module-1).  This
;;; may only be called in a with-module-required-by-relationships context.

(defmacro efficient-module-required-by-module-p (module-1 module-2)
  (avoiding-variable-capture (module-1 module-2)
    `(or (let* ((key (make-module-relationship-key ,module-1 ,module-2))
		(hashed-relationship (get-module-required-by-relationships
				       key
				       module-required-by-relationships))
		(relationship
		  (or hashed-relationship
		      (setf (get-module-required-by-relationships
			      key
			      module-required-by-relationships)
			    (if (module-requires-module-p ,module-2 ,module-1)
				'dependent
				'non-dependent)))))
	   (when hashed-relationship
	     (reclaim-gensym-cons key))
	   (eq relationship 'dependent)))))







;;; `Propagate-modules-to-subworkspaces' propagates module to all permanent kb-
;;; workspaces.  

(defun propagate-modules-to-subworkspaces ()
  (loop for workspace being each class-instance of 'kb-workspace
	when (and (permanent-block-p workspace)
		  ;; GENSYMCID-694: G2 Server abort while attempting to save KB after deleting item on WS and double clicking WS name.
		  ;; Prevent set module of a deleted workspace for recycle
		  (not (equal (frame-serial-number workspace) (frame-serial-number-recycled))))
	  do (set-module-for-workspace workspace)))



(defun set-module-for-workspace (workspace)
  (or
    (module-this-is-part-of? workspace)
    (setf (module-this-is-part-of? workspace)
	  (get-module-block-is-in workspace))))

;; This could be optimized in the following way.  When you go up the
;; workspace hierarchy, fill in module-this-is-part-of?, which get-module-
;; block is in does not currently do.  Then this would not have to go up
;; the same path as much on average.





;;; `Unpropagate-modules-to-subworkspaces' ... is called at the end of a with-
;;; modules-propagated-to-subworkspaces context.

(defun unpropagate-modules-to-subworkspaces ()
  (loop for workspace being each class-instance of 'kb-workspace
	when (permanent-block-p workspace)
	  do (if (parent-of-subworkspace? workspace)
		 (setf (module-this-is-part-of? workspace) nil))))





;;; `Efficient-get-module-block-is-in' ... is intended to be called after
;;; propagate-modules-to-subworkspaces has done its work, and before that
;;; effect has been cleared by unpropagate-modules-to-subworkspaces, which
;;; must be done in a single dynamic (i.e., non-interuptible) extent.

(defun-simple efficient-get-module-block-is-in (block)
  (loop for superior? = block then (superior-frame superior?)
	do (cond
	     ((null superior?)
	      (return (get-module-block-is-in block)))
	     ((frame-of-class-p superior? 'kb-workspace)
	      (return (module-this-is-part-of? superior?))))))
  










;(defun do-fix ()
;  (loop with top-level-module = (top-level-kb-module? module-information)
;	for c in (inferior-classes 'system-table)
;	do (loop for i from 1
;		 for instance-1 being each class-instance of c
;		 when (eq (module-system-table-belongs-to? instance-1)
;			  top-level-module)
;		   do (loop-finish)
;		 finally
;		   (loop while
;			   (loop for instance being each class-instance of c
;				 unless (eq instance instance-1)
;				   do (delete-frame instance)
;				      (return t))))
;	finally
;	  (let ((system-table-suite
;		  (loop for c in (inferior-classes 'system-table)
;			as instances-listed
;			   = (loop for inst being each class-instance of c
;				   collect inst using slot-value-cons)
;			do (assert (and instances-listed (null (cdr instances-listed))))
;			do (set (class (car instances-listed))
;				(car instances-listed))
;			nconc instances-listed)))
;	    ;; This makes the first element be the module-information system table:
;	    ;; -- same code as in merge-in-system-table-suite-read-in! -- 
;	    (let ((temp (car system-table-suite)))
;	      (loop for elements on system-table-suite
;		    when (frame-of-class-p (car elements) 'module-information)
;		      do (setf (car system-table-suite) (car elements))
;			 (setf (car elements) temp)
;			 (return nil)))
;	    (setq modules-and-system-tables-a-list
;		  (slot-value-list system-table-suite)))))






;; To Do/Ideas for KB Modularity:
;;
;; JRA wants to have symbol Import/Export w/absolute boundaries.
;; 
;; Now that this has been changed to create a "schedule" of modules to load
;; in order before doing anything -- making it non-recursive, call a subset
;; of post-loading functions that only should run after all modules have been
;; loaded -- see JRA.  (MHD 12/3/91)
;;
;;
;; Immediate To Do List:  (MHD 2/13/92)
;;
;; 0. In the warning comment that gets put into the save command, refer the user
;; to the logbook for further information.  (Ben reported that he looked everywhere
;; except the logbook when this came up.)
;;
;; 1. Make file-name attribute of all module-information system tables editable,
;; not just if installed.  It is now going to be the only way to change submodules
;; saving file name.
;;
;; 2. Add a boolean user-editable attribute, read-only, that says to NOT save
;; the module when saving a superior module and all required modules.  Have this
;; default to the read-only bit from the file system.  
;;
;; 3. Change class name module-information to module-parameters.
;;
;; 4. Take out "kb-" from the attribute name top-level-kb-module.
;;
;; 5. Generally, take "kb-" out from "kb-module" wherever the user sees it.





;;;; Deleting Modules



;;; Do-deletion-of-module-after-confirmation ... If the module to be deleted is
;;; the installed module, the top-level suite of system tables is replaced by a
;;; new suite of all-new tables, with no module assignment at all.

(defun do-deletion-of-module-after-confirmation
    (module also-delete-assigned-workspaces?)
  (let* ((system-table-suite?
	   (get-system-table-suite-for-module-or-nil module)))
    (cond
      ((null system-table-suite?)
       (notify-user "No module named ~a was found." module)
       nil)
      (t
       (with-module-related-frame-note-updates-supressed ; helps esp. with workspace deletion
	 (notify-user
	   "Module ~a~a is being deleted with its associated set of system tables~a. ~a"
	   module
	   (if (system-table-installed-p (first system-table-suite?))
	       ", the top-level module," "")
	   (if also-delete-assigned-workspaces?
	       " as well as its associated set of workspaces"
	       "")
	   (if (system-table-installed-p (first system-table-suite?))
	       " A new set of system tables is being installed." ""))
	 (when also-delete-assigned-workspaces?
	   (delete-workspaces-of-module module))
	 (if (system-table-installed-p (first system-table-suite?))
	     (delete-top-level-module)
	     (delete-system-table-suite system-table-suite?))
	t)))))


;; `Delete-workspaces-of-module' was extracted from the function above so it
;; could be accessed separately. -pga, 4/28/95

;;; `Delete-workspaces-of-module' ...

(defun delete-workspaces-of-module (module)
  (let ((workspaces-belonging-to-this-module
	  (loop for workspace being each class-instance of 'kb-workspace
		when (within-module-p workspace module)
		  collect workspace using gensym-cons)))
    ;; this is just to get those pesky object definitions for junction
    ;; blocks that are in limbo and hang off of the module just by the
    ;; thinnest of threads; see get-module-block-is-in for details.  It's
    ;; possible that this would or should come for free by deleting the
    ;; workspaces, but I don't want take that chance; this is at least
    ;; guaranteed to give correct results. (MHD 8/12/94)
    (loop for definition being each class-instance of 'class-definition
	  as workspace? = (get-workspace-if-any definition)
	  when (and (null workspace?)
		    (within-module-p definition module))
	    do (delete-frame definition))
    (loop with frame-reference-serial-number = (copy-frame-serial-number (current-frame-serial-number))
	  for workspace in workspaces-belonging-to-this-module
	  when (frame-has-not-been-reprocessed-p
		 workspace frame-reference-serial-number)
	    do (delete-frame workspace)
	    finally (reclaim-frame-serial-number frame-reference-serial-number))
    (reclaim-gensym-list workspaces-belonging-to-this-module)))




;;; `Delete-top-level-module' deletes the top-level module's system table suite.
;;; A new suuite of system table is created for the unspecified module, and it
;;; is installed in place of the previous top-level module.
;;;
;;; This is called by do-deletion-of-module-after-confirmation in the special
;;; case that the top-level module is being deleted.  Note that
;;; do-deletion-of-module-after-confirmation handles deletion of workspace assigned
;;; to modules, if that is even desired.

(defun delete-top-level-module ()
  (let* ((installed-suite (find-currently-installed-system-table-suite))
	 (module-information-instance (make-system-frame 'module-information))
	 (new-suite (slot-value-list module-information-instance)))
    (merge-in-system-table-suite-read-in new-suite t installed-suite)))



;;;; File and Pathname Interface to Modules



;;; A `module map' gives a mapping from module names to file names.  These file
;;; names may be either absolute or relative file names, and may also be
;;; abbreviated file names, i.e., file names with certain components
;;; unspecified.  The usual tradeoffs between the choice of which kind of file
;;; name to use should apply (i.e., abbreviated vs. not, relative vs. absolute).
;;;
;;; A `module-map file' (or `mm file'), is an ascii flat-file representation of
;;; such a module map.

;; NOTE: the following was never fully implemented: -mhd, 2/16/01
;;
;; ;;; The `module-map' attribute of a module-information
;; ;;; instance is an attribute-table representation of a module map.

;;; Each line of a module-map file contains a module name, followed by any
;;; whitespace character, followed by a filename, optionally enclosed in
;;; quotes (").  A line whose first non-blank character is # is ignored.
;;; This feature is intended to support comments.
;;;
;;; For example, the lines of a module-map file might be
;;;
;;;    # Module Map file for Guide Rev. 2001
;;;    guide guide-2001
;;;    sys-mod /home/mhd/frozen/sys-mod-1999.kl
;;;
;;; In this example, the module GUIDE is mapped to the (abbreviated, relative)
;;; file name "guide-2001", and the module SYS-MOD is mapped to the (absolute,
;;; mostly unabbreviated) file name "/home/mhd/frozen/sys-mod-1999.kl".  The
;;; line "# Module Map file for Guide Rev. 2001" is ignored, but presumably
;;; provides commentary.
;;;
;;; At present, there is only one module map in memory at a time.

;; Not implemented: -mhd, 2/16/01
;; ;;; If the
;; ;;; current KB supplies a module map, via the installed (i.e., the top-level
;; ;;; module's) module-information table, then that becomes the only module map.

;;; If that KB is cleared, then the module map is taken from the mm file.
;;;
;;; When a module M is saved in G2, its file name is picked as follows:
;;;
;;;    (1) a default file name is generated as follows:
;;;
;;;       Merge in order
;;;
;;;          (a) the value of the file-name attribute of the
;;;              module-information system table for M;
;;;
;;;          (b) the value of the entry for M, if any, in the module map;
;;;
;;;          (c) the directory for the top-level module (if applicable);
;;;
;;;          (d) the current default KB directory
;;;
;;;    (2) in an interactive save, the user is presented with a table
;;;        of modules to save, with their default pathnames; users may
;;;        edit these pathnames to change them further
;;;
;;;    (3) saving ultimately decides where the files end up; for example,
;;;        if the final pathname is relative, it will end up ....
;;;

;;; The system variable `g2-module-file-name-map' is an a-list of the form
;;;
;;;    ( { (module-name file-name) }* )
;;;
;;;
;;; The sytem variable `g2-module-search-path' is a list of the form
;;;
;;;    ( { directory-pathname }* )
;;;
;;; G2-module-search-path gets its value from either the command line argument
;;;
;;;     -module-search-path <search-path>
;;;
;;; or the environment variable
;;;
;;;     G2_MODULE_SEARCH_PATH
;;;
;;; `Cons pools' - the module search path is originally returned as a list
;;; in the TOKEN cons pool, because that's what the tokenizer returns.  To
;;; be placed into a slot in the server parameters, it obviously needs to
;;; be moved into the slot-value-cons pool.  To be used for the g2-module-
;;; search-path variable, it really can be in any pool, but of course needs
;;; to be consistent so that it can be reclaimed properly.  I am using token
;;; conses to build up g2-module-search-path as well, since slot-value conses
;;; really should only be used for slot values, and gensym-conses are so
;;; prevalent that it makes it difficult to track down leaks there.


;;; `module-search-path-tokenizer' - all tokenizer specs are defined in
;;; alphabet because I tried to keep the rest of the code from being dependent
;;; on a particular implementation of a character set.

(def-lexing-table module-search-path-tokenizer module-search-path-tokens)


;;; `override-for-default-module-search-path?' - used for testing in
;;; development.

#+development
(defvar override-for-default-module-search-path? nil)



;;; `Get-g2-module-search-path-string-from-environment-or-command-line' returns
;;; either (a) a freshly created text string with the module search path that
;;; the user specified, either in an environment variable or on the command
;;; line, if any; or (b) if there is none, it returns nil.

(defun get-g2-module-search-path-string-from-environment-or-command-line ()
  (or #+development
      (copy-if-text-string override-for-default-module-search-path?)
      
      (copy-if-text-string
	(get-command-line-keyword-argument
	  #w"module-search-path"))
      ;; "module_search_path" is superceded and removed from "g2 -help"
      ;; but why not continue to support it if given?  jv, 10/25/99
      (copy-if-text-string
	(get-command-line-keyword-argument
	  #w"module_search_path"))

      (get-gensym-environment-variable
	#w"G2_MODULE_SEARCH_PATH")))


;;; `get-g2-module-search-path-as-token-list-of-texts' obtains the module-
;;; search-path as a typical unix path string, i.e., a string with directory
;;; pathnames separated by colons.  The individual pathnames may end with or
;;; without the slash character (/).  They are in any case interpreted as
;;; directories.
;;;
;;; An example might look like this:  (but would have no internal linebreaks)
;;;
;;;   "/usr/openwin/demo:.:/usr/lang:/usr/ucb:/usr/openwin/b
;;;   in:/usr/openwin/etc:/home/frame/bin:/usr/ccs/bin:/usr/
;;;   lib/gcc:/usr/sunlink/dni:/usr/bsd:/usr/sbin:/usr/ucb:/
;;;   bin:/usr/bin:/usr/local/bin:/etc:/usr/etc:/usr/bin/X11"
;;;
;;; This specified the directories
;;;
;;;    /usr/openwin/demo/
;;;    .                     (the current ("dot") directory)
;;;    /usr/lang/
;;;    /usr/openwin/bin/
;;;    ...                   (etc.)
;;;
;;; in the order given.

(defun-simple get-g2-module-search-path-as-token-list-of-texts ()
  (let* ((search-path-string?
	   (get-g2-module-search-path-string-from-environment-or-command-line))
	 (token-list-of-text-strings
	   (tokenize-text-string search-path-string?
				 module-search-path-tokenizer)))
    (reclaim-if-text-string search-path-string?)
    token-list-of-text-strings))



;;; `list-of-text-strings->list-of-pathnames' is used to abstract the body of
;;; parse-search-path-string-into-list-of-pathnames so it can be called from
;;; update-g2-module-search-path as well.  This function may receive a token-
;;; list or slot-value list (or whatever), since it does no reclamation.

(defun-simple list-of-text-strings->list-of-pathnames (list-of-text-strings)
  ;; these might be the kind of directories that end with slash
  ;; (e.g., "/foo/bar/") or the kind that end without a slash
  ;; (e.g., "/foo/bar").  Both have to be handled.  Both are
  ;; assumed to be directories.
  (loop for text-string in list-of-text-strings
	collect (or (gensym-file-as-directory text-string)
		    (gensym-pathname text-string))
	  using token-cons))


(defun-simple list-of-pathnames->list-of-text-strings (list-of-pathnames)
  (loop for pathname in list-of-pathnames
	collect (gensym-namestring pathname)
	  using slot-value-cons))
  


;;; `Get-initial-value-for-g2-module-search-path' gives the initial value for
;;; the system variable g2-module-search-path, a list of freshly created gensym
;;; directory pathnames.

(defun-simple get-initial-value-for-g2-module-search-path ()
  (let* ((token-list (get-g2-module-search-path-as-token-list-of-texts))
	 (list-of-pathnames (list-of-text-strings->list-of-pathnames
			      token-list)))
    (reclaim-token-list token-list)
    list-of-pathnames))




;;; `g2-module-search-path'

(def-system-variable g2-module-search-path modules
  (:funcall get-initial-value-for-g2-module-search-path))


;;; `test-parse-module-search-path'

#+development
(defun-simple test-parse-module-search-path (module-search-path)
  (let ((override-for-default-module-search-path? module-search-path))
    (get-g2-module-search-path-as-token-list-of-texts)))


;;; `module-search-path-test-suite'

#+development
(defvar module-search-path-test-suite '())

#+development
(setq module-search-path-test-suite
  '((#w"'c:\\Program Files\\gensym\\' d:\\gensym e:\\gensym" .
     (#w"c:\\Program Files\\gensym\\" #w"d:\\gensym" #w"e:\\gensym"))
    (#w"" . nil)
    (#w"/bt/ab/kbs /home/jv/kbs/5.0 /gensym/ut/kbs-latest/utils" .
     (#w"/bt/ab/kbs" #w"/home/jv/kbs/5.0" #w"/gensym/ut/kbs-latest/utils"))
    (#w"/bt/ab/kbs/ /john's-dir/kbs/5.0 /gensym/ut/kbs-latest/Samples" .
     (#w"/bt/ab/kbs/" #w"/john's-dir/kbs/5.0" #w"/gensym/ut/kbs-latest/Samples"))
    (#w"'c:\\Program Files\\gensym\\' 'd:\\gensym' 'e:\\gensym'" .
     (#w"c:\\Program Files\\gensym\\" #w"d:\\gensym" #w"e:\\gensym"))
    ;; the next one is not what the user probably wants, but it is the correct
    ;; result
    (#w"'e:\\gensym' c:\\Program Files\\gensym" .
     (#w"e:\\gensym" #w"c:\\Program" #w"Files\\gensym"))
    (#w"g2$disk:[kbs.samples] [home.user] [-.-.kbs] btdisk:[gensym.ut.dev.kbs-51r3.utils]" .
     (#w"g2$disk:[kbs.samples]" #w"[home.user]" #w"[-.-.kbs]"
      #w"btdisk:[gensym.ut.dev.kbs-51r3.utils]"))
    ;; The next one is really tricky
    (#w"/home/john's-dir/kbs /home/bob's-dir/kbs" .
     (#w"/home/john's-dir/kbs" #w"/home/bob's-dir/kbs"))
    ;; The same trick, on Windows
    (#w"x:\\users\\john's-dir\\kbs y:\\home\\bob's-dir\\kbs\\" .
     (#w"x:\\users\\john's-dir\\kbs" #w"y:\\home\\bob's-dir\\kbs\\"))
    ;; empty quotes
    (#w"/bt/ab/kbs '' /gensym/ut" .
     (#w"/bt/ab/kbs" #w"" #w"/gensym/ut"))
    (#w"/bt/ab/kbs ' ' /gensym/ut" .
     (#w"/bt/ab/kbs" #w" " #w"/gensym/ut"))
    ;; This one is probably not what is desired, but matches the best spec
    ;; I can come up with.
    (#w"'s-dir/kbs /home/bob's-dir/kbs" .
     (#w"s-dir/kbs /home/bob" #w"s-dir/kbs"))
    ))


;;; `execute-module-search-path-tests' - note: this tests parsing a text string
;;; into component texts.  It does NOT test making pathnames out of those tests.
;;; Anyone who wants to construct a test to test pathnames should be interested
;;; in the function set-up-pseudo-file-system.

#+development
(defun-simple execute-module-search-path-tests ()
  (let ((token-conses-outstanding-at-start
	  (outstanding-token-conses)))
    (and (loop with all-tests-pass-p = t
	       for (input . expected-output) in module-search-path-test-suite
	       as resulting-output = (test-parse-module-search-path input)
	       unless (equalw expected-output resulting-output) do
		   (format t "~s != ~s~%" expected-output resulting-output)
		   (setq all-tests-pass-p nil)
	       do
	   (print input)
	   (reclaim-token-list resulting-output)
	       finally (return all-tests-pass-p))
	 (let ((token-conses-leaked
		 (-f (outstanding-token-conses)
		     token-conses-outstanding-at-start)))
	   (if (=f token-conses-leaked 0)
	       t
	       token-conses-leaked)))))
    
  



;;; `g2-module-file-name-map'

(def-system-variable g2-module-file-name-map modules
  nil)



;;; `Parse-module-map-line-into-parts' returns a gensym list of the form
;;;
;;;    (<module-name/symbol> <module-name-file-pathname/gensym-pathname>)
;;;
;;; as long as module-map-line specifies this.  If not, this returns nil.
;;;
;;; When this returns a non-nil result, it is made of fresh gensym conses,
;;; and of a fresh gensym pathname, reclamation of which is the responsibility
;;; of the caller.

(defun parse-module-map-line-into-parts (module-map-line)
  (let ((list-of-strings
	  ;; used parse-colon-delimited-ascii-text-line-into-list-of-ascii-strings
	  ;; until Beta Phase 2. (MHD 1/25/95)
	  (parse-space-delimited-text-line-into-list-of-text-strings
	    module-map-line)))
    (when list-of-strings
      (let* ((module-name?
	       (read-symbol-from-text-string (first list-of-strings)))
	     (gensym-pathname?
	       (when (text-string-p (second list-of-strings))
		 (gensym-parse-namestring (second list-of-strings))))
	     (converted-gensym-pathname?
	       (when gensym-pathname?
		 (gensym-pathname gensym-pathname?))))
	    ;; we want:
	    ;;   :JUNK-ALLOWED T
	    ;; JH says: this is the default; hmmm....  (MHD 4/9/94)
	    ;; (if (nthcdr 2 list-of-strings) (notify-user "error...")) ??

	;; Added this gensym-pathname reclaimer to fix a VW bug fix where
	;; g2-save-module leaks only when a module-map appears on the command
	;; line.  This function was leaking one gensym-pathname per
	;; module-map entry.  (ghw 10/25/96)
	(when gensym-pathname? 
	  (reclaim-gensym-pathname gensym-pathname?))
	(prog1
	    (cond
	      ((and module-name? converted-gensym-pathname?)
	       (gensym-list module-name? converted-gensym-pathname?))
	      (t
	       (if converted-gensym-pathname?
		   (reclaim-gensym-pathname converted-gensym-pathname?))
	       nil))
	  (loop for string? in list-of-strings
		when string?
		  do (reclaim-text-string string?))
	  (reclaim-gensym-list list-of-strings))))))
	
    
;; Consider a more ambitions mapping file spec:
;;
;; 
;; Search path
;;      => filename : filename : ...
;;      
;; module name mappings and module-specific defaults
;;      => { module name [: file name translation] [: search path] }*
;;
;; # Module Name Mappings
;; guide:guide-1:/home/dwr/guide/latest
;; sys-mod:sysmod-greatest-ever
;; gda::/home/gda/


(def-kb-specific-property-name gensym-pathname-for-module reclaim-if-gensym-pathname)
(def-kb-specific-property-name default-pathname-for-module reclaim-if-gensym-pathname)
(def-kb-specific-property-name module-is-writable-p)
(def-kb-specific-property-name module-is-locked-p)
(def-kb-specific-property-name reason-module-is-not-editable reclaim-if-text-string-function)
(def-kb-specific-property-name module-uses-crlf-p)
(def-global-property-name initial-plist-for-loaded-module)

(defun-simple set-gensym-pathname-for-module (module-name new-value)
  (reclaim-if-gensym-pathname (gensym-pathname-for-module module-name))
  (setf (gensym-pathname-for-module module-name) (copy-gensym-pathname new-value))
  (update-saving-parameters-status-attributes module-name)
  new-value)

(defun-simple set-default-pathname-for-module (module-name new-value)
  (reclaim-if-gensym-pathname (default-pathname-for-module module-name))
  (setf (default-pathname-for-module module-name) (when new-value (copy-gensym-pathname new-value))))

(defun-simple set-reason-module-is-not-editable (module-name new-value)
  (reclaim-if-text-string (reason-module-is-not-editable module-name))
  (setf (reason-module-is-not-editable module-name) new-value)
  (unless (eq 'unknown new-value)
    (update-saving-parameters-status-attributes module-name))
  new-value)

(defun-simple set-initial-plist-for-loaded-module (module-name new-value)
  (reclaim-slot-value (initial-plist-for-loaded-module module-name))
  (setf (initial-plist-for-loaded-module module-name) new-value))


;;; The `true pathname of a module' is the pathname from which that module
;;; was loaded, or the pathname to which it was last saved, if different.  Note
;;; that not every module has a true pathname.  For a module to have a
;;; true pathname, it must have been merged in from a KB saved as a module,
;;; or have been saved as a module in a KB file.

;;; A module newly created in memory would not have an true pathname, unless
;;; it happened to have the same name as a module that really was merged in.  A
;;; renamed module would lose its true pathname, if it had one, unless,
;;; again, it happened to be renamed to the name of a module that was previously
;;; merged in.

;;; The function `get-true-pathname-of-module-if-any' returns the true
;;; pathname for the module named module-name, if any.
;;;
;;; The function `set-true-pathname-of-module-if-any' is to be called by the
;;; saving code when a module is saved to revise or record anew the pathname
;;; associated with a module.  The default-pathname? argument should be the
;;; default pathname in effect when the KB was saved.  

(defun get-true-pathname-of-module-if-any (module-name)
  (gensym-pathname-for-module module-name))


(defun set-true-pathname-of-module (module-name true-pathname default-pathname?)
  (unless (default-pathname-for-module module-name)
    (set-default-pathname-for-module module-name default-pathname?))
  (set-gensym-pathname-for-module module-name true-pathname))

;;; The function `get-enough-pathname-of-module-loaded-if-any' 

(defun get-enough-pathname-of-module-loaded-if-any (module-name)
  (let ((default-pathname? (default-pathname-for-module module-name)))
    (when default-pathname?
      (let ((enough-namestring
	      (gensym-enough-namestring
		(gensym-pathname-for-module module-name)
		default-pathname?)))
	(prog1 (gensym-pathname enough-namestring)
	  (reclaim-text-string enough-namestring))))))

(defun note-crlf-use-in-module-or-file (module kb-uses-crlf-p)
  (setf (module-uses-crlf-p module) kb-uses-crlf-p))



;;;; Server Parameters

;;; `server-parameters' is a system table which is meant to contain information
;;; global to an invocation of G2 (e.g. module-search-path), rather than on a
;;; per-KB basis.  If we were more OO, we could accomplish this more easily, but
;;; such is life.  As it's currently implemented we're breaking the abstraction
;;; about how system-tables are dealt with.  We're taking advantage of the fact
;;; that upon a CLEAR-KB, the new system tables are created before the old ones
;;; are deleted.  So we simply get the slot values from the "old" system table
;;; and put them in the new one.  The values should never be reclaimed. In
;;; addition, rather than saving the info with the KB/module, users will be able
;;; to save/restore the info to a profile.  (.g2rc?).  This isn't implemented
;;; yet.  -dkuznick, 10/8/99

;; Issues: What to do about multiple modules?
;;     -        Don't save table.  Rick's idea: Splice the table out of the
;;                list(s) that hold them.  (DONE) Also have to prevent deletion by the
;;                user (I don't see how system-tables can ever be deleted since
;;               they can't be made transient, so DONE)
;;     -       Only have one per G2, not per module (DONE) (module-assignment should
;;               return an empty sequence for it - check with JV if confused)
;;     -       Tests to try: clearing (DONE), merging (DONE) , warmbooting (DONE), creating new modules (DONE)
;;     -        Need to deal with install/deinstall-system-table? (Don't think so)
;;     -        Are we chaging the format of the command-line option (i.e. spaces)?
;;    -        Don't allow table to be transferred.  Done in prohibit-transfer-of-table-p (commands2)
;;     -        Init file - later

(def-system-frame server-parameters modules
  (module-search-path nil (type module-search-path))
  (source-code-control-support-is-enabled nil (type #-use-scc nil #+use-scc yes-or-no))
  (restrict-edits-to-read-only-files nil (type #-edit-restrctions nil
					       #+edit-restrictions yes-or-no))
  (current-style-if-other-than-default? nil (type g2-window-style-override)))

(def-grammar-category module-search-path ()
  ('none)
  (module-path-spec))

(def-grammar-category module-path-spec ()
  (pathname-string (1))
  ((pathname-string '\, module-path-spec) (1 . 3)))

(add-grammar-rules '((pathname-string whole-string)))

(define-slot-alias g2-window-style current-style-if-other-than-default?
  server-parameters)

(def-grammar-category g2-window-style ()
  standard standard-large g2-5.x)

(def-grammar-category g2-window-style-override ()
  default
  (g2-window-style))





;;; The cascade of defaults for the window style goes along these lines
;;;
;;;    1. The Window/Workstation, given by the G2 Window object, if any, or by
;;;       the command line (-window-style)
;;;    2. The KB, given by the default-window-style of miscellaneous-parameters
;;;    3. The Server, given by the window style of server-parameters,
;;;       if any, or by the command line, if any, or by the command line
;;;       (-default-window-style)
;;;    4. The factory default (STANDARD)


;;; The macro `current-g2-window-style' returns the first of the following values
;;; that is non-nil:
;;;
;;;    1. (get-style-for-current-workstation-if-any)
;;;    2. (current-style-if-other-than-default? server-parameters)
;;;    3. (get-kb-default-window-style-override-if-any)
;;;    4. default-style

(defmacro current-g2-window-style ()
  `(or
     ;; Window:
     (get-style-for-current-workstation-if-any)
     ;; KB:
     (get-kb-default-window-style-override-if-any)
     ;; Server:
     (and server-parameters
	  (get-slot-value
	    server-parameters 'current-style-if-other-than-default?))
     ;; Factory:
     default-g2-window-style))

(defparameter default-g2-window-style 'standard)

(defun-simple get-initial-window-style ()
  (getf command-line-arguments 'default-window-style))

(def-system-variable current-style-if-other-than-default modules
  (:funcall get-initial-window-style))

(defun-simple get-workstation-g2-window-style-in-force (workstation)
  (or
    ;; Window:
    (style-specifically-for-this-workstation? workstation)
    ;; KB:
    (get-kb-default-window-style-override-if-any)
    ;; Server:
    current-style-if-other-than-default
    ;; Factory:
    default-g2-window-style))



;;; `Reset-current-workstation-new-g2-classic-ui-p' sets special variable
;;; new-g2-classic-ui-p to the result of
;;; `get-value-for-current-workstation-new-g2-classic-ui-p', which returns a new
;;; UI style (symbol STANDARD or STANDARD-LARGE) or nil (meaning G2-5.X) based
;;; on the style dynamically in force for the current workstation.  These
;;; functions may only be called in a for-workstation dynamic extent, i.e., when
;;; current-workstation is bound and when servicing-workstation? is true.

(defun reset-current-workstation-new-g2-classic-ui-p ()
  (setq new-g2-classic-ui-p
	(get-value-for-current-workstation-new-g2-classic-ui-p)))

(defun get-value-for-current-workstation-new-g2-classic-ui-p ()
  (assert-that-within-named-dynamic-extent 'for-workstation)
  (let ((style (get-workstation-g2-window-style-in-force current-workstation)))
    (case style
      (g2-5.x nil)
      (t style))))



(defun-simple get-kb-default-window-style-override-if-any ()
  (if (and (boundp 'miscellaneous-parameters)
	   miscellaneous-parameters
	   ;; when clearing a KB, the frame could be deleted, so the following
	   ;; might be false!
	   (framep miscellaneous-parameters))
      (get-slot-value miscellaneous-parameters 'default-window-style)))

(defun-simple get-style-for-current-workstation-if-any ()
  (when servicing-workstation?		; <- check should not be needed; remove some day!
    (style-specifically-for-this-workstation? current-workstation)))

(def-command-line-argument default-window-style ((value? :keyword))
  (when value?
    (validate-window-style-command-line-argument value? "-default-window-style")))
  
(def-slot-value-writer module-search-path (value)
  (if (null value)
      (twrite-string "none")
      (loop for path-list on value
	    do
	(tprin (car path-list) t)
	(when (cdr path-list) (twrite-string ", ")))))

(def-class-method initialize (server-parameters)
  (funcall-superior-method server-parameters)
  (setf (module-search-path server-parameters)
	(list-of-pathnames->list-of-text-strings g2-module-search-path))
  (setf (source-code-control-support-is-enabled server-parameters)
	source-code-control-support-enabled-p)
  (setf (restrict-edits-to-read-only-files server-parameters)
	restrict-edits-to-modules-having-read-only-files-p)
  (setf (current-style-if-other-than-default? server-parameters)
	current-style-if-other-than-default))

(def-slot-putter module-search-path (server-parameters new-path-list initializing?)
  (unless (or initializing? called-within-clear-text-loading)
    (loop for gensym-pathname in g2-module-search-path
	   do (reclaim-gensym-pathname gensym-pathname))
     (reclaim-token-list g2-module-search-path)
     (setq g2-module-search-path (if (eq new-path-list 'none)
				     nil
				     (list-of-text-strings->list-of-pathnames new-path-list))))

  ;; Unlike most slot-putters (which store the new value in the object), we are
  ;; making a new value to store based on the passed in value (new-path-list),
  ;; so we have to explicitly reclaim the passed in value or else there will be
  ;; a leak. (Bug HQ-3763576) -dkuznick, 1/8/01
  (when (consp new-path-list)
    (loop for str in new-path-list
	  do
      (reclaim-text-string str)
	  finally
	    (reclaim-slot-value-list new-path-list)))

  (setf (module-search-path server-parameters)
	(list-of-pathnames->list-of-text-strings g2-module-search-path)))

(def-slot-putter source-code-control-support-is-enabled (server-parameters new-value initializing?)
  (unless (or initializing? called-within-clear-text-loading)
    (setq source-code-control-support-enabled-p new-value))
  (when source-code-control-support-enabled-p
    (add-source-code-control-grammar))
  (setf (source-code-control-support-is-enabled server-parameters)
	source-code-control-support-enabled-p)
  (enable-scc-check)
  (recompute-editability-of-modules)
  (update-saving-parameters-status-attributes '*)
  new-value)

(def-slot-putter restrict-edits-to-read-only-files (server-parameters new-value initializing?)
  (unless (or initializing? called-within-clear-text-loading)
    (setq restrict-edits-to-modules-having-read-only-files-p new-value))
  (setf (restrict-edits-to-read-only-files server-parameters)
	restrict-edits-to-modules-having-read-only-files-p)
  (recompute-editability-of-modules)
  new-value)

(def-slot-putter current-style-if-other-than-default? (server-parameters new-value initializing?)
  (unless (or initializing? called-within-clear-text-loading)
    (setq current-style-if-other-than-default new-value))
  (setf (current-style-if-other-than-default? server-parameters)
	current-style-if-other-than-default)
  current-style-if-other-than-default)




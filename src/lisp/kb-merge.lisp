;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module KB-MERGE

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark David







;;;; Forward References


(declare-forward-references
  (type-specification-for-user-type function sets)
  (warmboot-kb function warmboot)
  (traverse-kb-for-saving function traversals)
  (goto-frame-instance function facilities)
  (enter-dialog function controls)
  (save-kb function kb-save3)
  (start-kb-after-load-from-system-table? function grammar7)
  (miscellaneous-parameters variable grammar7)
  (system-start function cycles)
  (set-transient-and-propagate function stack-acts)
  (superior-frame function activate)
  (clear-kb function kb-save2)
  (doing-g2-init-file-p variable kb-save2)
  (doing-g2-init-kb-p variable kb-save2)
  (current-kb-serial-number variable kb-save2)
  (collect-bad-definitions-for-kb function kb-save3)
  (multiple-add-to-results-for-inspect-command function)
  (update-indexed-attribute-properties function)
  (get-reason-module-is-not-editable function filters)
  (allow-unsavable-change-p function filters)
  (will-cause-source-code-control-problems-if-saved-p function kb-save3)
  (twrite-changed-modules-note function stack-eval2)
  (modules-with-unsaved-changes function stack-eval2))

(declare-forward-references-to-module kb-load1
  old-format-for-default-overrides-p-function
  need-to-normalize-message-properties-p-function
  normalize-message-properties-for-message-definition
  find-differences-in-frames-if-any
  get-less-case-sensitive-gensym-pathname-if-any
  get-or-make-default-kb-pathname
  clone-frame
  icon-editor-fixed-p-function
  (kb-flags variable)
  (name-text-string-for-kb-being-read variable)
  (next-character-for-kb? variable)
  (current-kb-pathname? variable))

(declare-forward-references-to-module kb-load2
  delete-block-after-reading-kb
  read-kb
  fix-unimplemented-definitions
  read-initial-plist
  fixup-icon-description-for-class
  (launch-recompile-for-compilations-removed-in-this-kb? variable)
  (reading-ghost-definitions-p variable)
  (main-kb-being-read? variable)
  (name-of-kb-being-read variable)
  (name-of-module-being-read? variable)
  (system-tables-read-for-this-module variable)
  (reading-kb-p variable)
  (post-loading-functions-will-be-executed-again-later? variable)
  (current-frame-serial-number-before-reading variable)
  (kb-load-case? variable)
  (record-class-name-conflict function)
  (put-workspace-on-detail-panes-now-or-later function)
  (loading-kb-p variable)
  (fix-up-default-overrides-for-5-0 function)
  (do-post-loading-functions function))

(declare-forward-references-to-module kb-save1
  write-frame-for-kb
  write-char-for-kb
  start-new-kb-line)

(declare-forward-references-to-module kb-save2
  empty-kb-p
  (releasing-kb? variable))

(declare-forward-references-to-module view-g2
  (inform-ui-client-interfaces-of-module-creation function)
  (inform-ui-client-interfaces-of-module-deletion function))

(declare-forward-reference current-attribute-file-pathname? variable)

(declare-forward-reference current-statistics-file-pathname? variable)

(declare-forward-reference current-foreign-image-pathname? variable)

(declare-forward-reference check-for-matching-methods function)

(declare-forward-reference file-types-for-module function)

(declare-forward-reference note-update-to-file-progress function)

(declare-forward-reference current-system-rpc-icp-socket? variable)

(declare-forward-reference do-not-show-conflicts-during-kb-load? variable)

(declare-forward-reference message function) ; COMMANDS0
(declare-forward-reference get-workspace-of-thing-if-any function) ; COMMANDS0
(declare-forward-reference enable-ui-on-all-workstations function) ; COMMANDS2

(declare-forward-reference suppress-notification-for-kb-save? variable)

;(declare-forward-reference
;  send-all-telewindows-new-kb-workspace-existence function) ; VIEW-G2


;;;; Class Name Conflicts



;;; A `class name conflict' is a slot value list of the form
;;; 
;;;    (class new-name?
;;;     old-class-definition? new-class-definition names-of-differing-slots
;;;     [ghost-definition-p]).
;;;
;;; 
;;;
;;;
;;; There are 5, and only 5, possible cases, as follows.  (Case 4 has two subcases.)
;;;
;;;     (1) (class nil nil new-class-definition nil t)
;;;
;;; New-class-definition is a "sketch" definition (a kind of "ghost" definition),
;;; and no old definition could be found.  This means that a definition that was
;;; once in a lower-level module has been "lost".  Such entries are only added when
;;; loading the header of a KB that was saved as a module. When
;;; dont-load-if-definitions-have-changed-p is true, the load of such a KB
;;; is to be aborted immediately after the loading of the header.  The function
;;; deal-with-class-name-conflicts therefore can only encounter this case
;;; that the flag is false.  In this case as well, new-class-definition never
;;; has a superblock.  This fact may be also be used to (help) identify it as a
;;; ghost, which must be brought to the attention of the user on a conflict
;;; workspace.  Also, the scratch definition must be put onto the conflict
;;; workspace.  This case is entirely handled by deal-with-class-name-conflicts;
;;; this case is never entered in record-of-class-name-conflicts?, and so need
;;; not be handled by resolve-class-name-conflicts.
;;; 
;;;
;;; 	(2) (class nil old-definition new-definition ({differing-slot}+) t)
;;;
;;; New-definition is a "sketch", and it differs from old-definition.  Such
;;; entries are only added when dont-load-if-definitions-have-changed-p is true
;;; while loading the header of a KB that was saved as a module. If dont-load-if-
;;; definitions-have-changed-p is false, this will instead appear as case 4
;;; below.  If dont-load-if-definitions-have-changed-p is true, however, the load
;;; of such a KB is to be aborted immediately after the loading of the header.
;;; In particular, note that deal-with-class-name-conflicts, which
;;; is called at the end of a non-aborted merge, can completely ignore this case;
;;; this case is never entered in record-of-class-name-conflicts?, and so need
;;; not be handled by resolve-class-name-conflicts.  In this case as well,
;;; new-class-definition never has a superblock.  This fact may be also be used
;;; to (help) identify it as a ghost.
;;; 
;;;
;;; 	(3) (class nil old-definition new-definition nil [ghost-definition-p])
;;;
;;; This is the normal (no-conflict) merge case, wherein the conflict is always
;;; easily resolved and will never even come to the users attention.  This case
;;; is entirely handled by deal-with-class-name-conflicts; this case is never
;;; entered in record-of-class-name-conflicts?, and so need not be handled by
;;; resolve-class-name-conflicts.  The final element, ghost-definition-p, which
;;; says whether new-definition was read in as a ghost is irrelevant in this case.
;;; 
;;;
;;; 	(4a) (class new-name old-definition new-definition ({differing-slot}+) nil)
;;;
;;; This is the conflict merge case, wherein the conflict will end up coming
;;; to the notice of the user via conflict workspaces (except when automerge
;;; intercedes).  Note that new-definition cannot be a ghost definition in subcase
;;; a of this case, but see subcase 4b.  This case may end up being deferred (in
;;; the "automerge" case), and so may appear in record-of-class-name-conflicts?,
;;; to be dealt with by resolve-class-name-conflicts.
;;; 
;;; 	(4b) (class new-name old-definition new-definition ({differing-slot}+) t)
;;;
;;; This is the same as case 4a except that new-definition was just read in as
;;; a ghost definition.  When this conflict is flagged for the user to see, the
;;; "scratch" definition must be put onto the permanent kb-workspace that holds
;;; the conflict report, and the conflict report identifies it as a "backup"
;;; definition.
;;; 
;;;
;;; 	(5a) (class new-name nil new-definition nil [nil])
;;;
;;; Class names a built-in class or a build-in type (though it did not when the
;;; kb containing new-class-definition was created).  In this case,
;;; names-of-differing-slots will also be nil.
;;;
;;; 	(5b) (class new-name nil new-definition nil t)
;;;
;;; This is the same as case 5a except that new-definition was just read in as
;;; a ghost definition.  When this conflict is flagged for the user to see, the
;;; "scratch" definition must be put onto the permanent kb-workspace that holds
;;; the conflict report, and the conflict report identifies it as a "backup"
;;; definition.

(defvar class-name-conflicts)		; a slot value tree

;; Consider adding extra-attributes-of-new-class-definition and incompatible-attributes
;; to class name conflicts.




;;; `Deferred-class-definitions-alist' is a slot value tree of the form
;;; 
;;;    { (name-for-class . class-definition-with-no-name) }.
;;;
;;; The class definitions in it are installed after the last class definition
;;; has been read in.

;;; The deferred class definition mechanism and the top-level-element? argument
;;; of read-element-for-kb are needed only when class-definitions-ordered-p is
;;; false, that is, for kbs saved with versions of G2 made prior to 7/25/88.

(defvar deferred-class-definitions-alist)






;;; The variable `record-class-name-conflicts?' is only bound while reading a
;;; KB.  If it is true, a record of class name conflicts due to merging KBs are
;;; recorded in the variable record-of-class-name-conflicts? for the purpose
;;; of automatically resolving the conflicts after the merge completes.

(defvar record-class-name-conflicts?)

;; See below for the section "Resolving Class Name Conflicts Automatically"
;; for how this is used.




;;;; Handling Class Name Conflicts



;;; `Combine-class-definitions' combines the combinable class definitions,
;;; class-definition-1 and class-definition-2, as described above under
;;; class-definitions-combinable-p, with class-definition-1 surviving.  Both
;;; class-definition-1 and class-definition-2 must have names, indeed different
;;; names.
;;;
;;; This first iterates over every strict instance of class-2, the class
;;; corresponding to class-definition-2, and reclassifies it to be class-1,
;;; the class corresponding to class-definition-1.
;;;
;;; Next, if class-definition-1 is a connection definition, class-definition-2
;;; must also be one -- that is assumed.  In this case, this updates the class
;;; name in all connection structures.
;;;
;;; Next, this propagates the change to any inferior classes.
;;;
;;; Finally, this reflects the changes in table representations of any
;;; instances.
;;;
;;; Added backtrace-for-internal-error ajs (4/30/96)

(defun combine-class-definitions (class-definition-1 class-definition-2)

  (with-backtrace-for-internal-error 'combine-class-defintions 
    (let* ((class-1 (name-of-defined-class class-definition-1))
	   (class-2 (name-of-defined-class class-definition-2)))

      ;; This looks at (instances-specific-to-this-class class-2), which
      ;; gives the first link in the chain of class-specific instances,
      ;; repeatedly until there are no more strict instances.
      ;;
      ;; At the end of this loop, class-2 will have no strict class instances,
      ;; although it may have non-strict instances, i.e., strict instances of its
      ;; subclasses.
      (loop for instance? = (instances-specific-to-this-class class-2)
	    while instance?
	    do (reclassify-frame instance? class-1))

      (when (memq 'connection
		  (class-inheritance-path-of-definition class-definition-1))
	(update-class-in-connections class-2 class-1)
	;; Do a merge instances on the respective junction block classes if possible.
	(let* ((junction-block-class-2
		 (class-slot-description-value
		   'junction-block-class-for-class class-2))
	       (junction-block-class-1
		 (class-slot-description-value
		   'junction-block-class-for-class class-1))
	       (change-command
		 (slot-value-list 'merge-definitions junction-block-class-1))
	       (junction-block-definition-2
		 (class-definition junction-block-class-2)))	     
	  (when (of-class-p junction-block-definition-2 'class-definition)
	    (put-change junction-block-definition-2 change-command nil))))

      ;; The job of the slot putter for direct-superiors-of-defined-class is to
      ;; ensure that the inferior-classes property of class-2 becomes nil by
      ;; repeatedly calling it with its inferior classes removed.
      ;; 
      ;; The function change-superior-of-class (called indirectly through
      ;; change-slot-value) will make the necessary changes throughout the class
      ;; hierarchy below class-2.
      ;;
      ;; At the end of the following loop, class-2 will still be defined, but will
      ;; have no subclasses at all, and no class instances at all.
      (loop for inferior-class in (inferior-classes class-2)
	    for inferior-class-definition = (class-definition inferior-class)
	    for inferior-class-definition-class = (class inferior-class-definition)
	    for  direct-superiors-of-defined-class =
	    (direct-superiors-of-defined-class inferior-class-definition)
	    for class-1-a-direct-superior-already?
	        = (memq class-1 direct-superiors-of-defined-class)
	    for new-direct-superiors-of-defined-class =
	    (let ((new-direct-superiors nil))
	      (loop for class in direct-superiors-of-defined-class
		    do
		(if (eq class class-2)
		    (unless class-1-a-direct-superior-already?
		      (setq new-direct-superiors
			    (nconc new-direct-superiors
				   (slot-value-list class-1))))
		    (setq new-direct-superiors
			  (nconc new-direct-superiors
				 (slot-value-list class)))))
	      new-direct-superiors)
	    do
	;; This call was changed from change-slot-value of direct-superiors-of-
	;; defined-class because alter-inheritance-of-class-without-changing-
	;; foundation-class needs the last two arguments in order to access
	;; the old slot-descriptions with the old name and access the new
	;; slot descriptions with the new-name.  
	(clear-override-frame-notes-from-class-definitions inferior-class)
	(alter-inheritance-of-class-without-changing-foundation-class
	  inferior-class-definition
	  new-direct-superiors-of-defined-class class-2 class-1)
	(process-default-overrides inferior-class t))

      ;; The following loop fixes up any table representations of all instances of
      ;; class-1 to reflect any of the changes.
      (loop for instance being each class-instance of class-1
	    do (update-attribute-tables instance)))))




;;; `Reclassify-frame' changes the class of frame to new-class, where new-class and the old
;;; (current) class must be "strictly compatible", in that both have class definitions that
;;; have no "differences" (as determined by find-differences-in-frames-if-any).  In
;;; addition,
;;; 
;;;   (1) the frame serial number is updated;
;;;   (2) if frame is a block on a workspace, it will be erased before
;;;       the changes and redrawn after;
;;;   (3) if frame is active, it will be deactivated before the changes
;;;       and reactivated after; and
;;;   (4) Representations of the CLASS slot (i.e. in attribute tables)
;;;       are updated after the changes

;; Examine this code carefully to be sure that there is no shared data structure
;; between the instance frame being reclasified and its old class-definition.
;; This could be the case if it has any vector slots that have default values
;; which are not immediate.

(defun reclassify-frame (frame new-class)
  (let* ((old-class (class frame))
	 (old-class-description (class-description-slot frame))
	 (old-slot-descriptions (slot-descriptions old-class-description))
	 (new-class-description (class-description new-class))
	 (frame-active? (active-p frame)))

    ;; erase block
    (when (frame-of-class-p frame 'block)
      (update-images-of-block frame t nil))
    
    (when frame-active?
      (funcall-method-if-any 'deactivate-and-propagate frame nil))
    (setf (class-description-slot frame) new-class-description)

    ;; When a slot value is eq to its old slot-init-form, set it eq to the new
    ;; slot-init-form.  (2/22/93 ghw)  Updated to use the correct defining
    ;; class component (2/19/97).
    (loop for old-slot-description in old-slot-descriptions
	  for defining-class = (defining-class old-slot-description)
	  as new-slot-description
	     = (get-slot-description-of-class-description
		 (pretty-slot-name old-slot-description)
		 new-class-description
		 (if (eq defining-class old-class)
		     new-class
		     defining-class))
		   
	  do
      (when (eq (get-slot-description-value frame old-slot-description)
		(slot-init-form old-slot-description))
	(set-slot-description-value 
	  frame new-slot-description
	  (slot-init-form new-slot-description))))

    (delete-from-instances-specific-to-this-class old-class frame)
    (add-to-end-of-instances-specific-to-this-class new-class frame)

    (frame-serial-number-setf (frame-serial-number frame) (increment-current-frame-serial-number))

    ;; redraw block
    (if (frame-of-class-p frame 'block)
	(update-images-of-block frame nil nil))

    (update-representations-of-slot-value   ; updates frame representations
      frame 'class)			    ;   to reflect the reclassification

    (if frame-active?
	(funcall-method-if-any 'activate-if-possible-and-propagate frame))))

;; This seems to cause turds sometimes!  Also, it can leave slot list-of-rule-instances-
;; for-entity nil, which may not be right!
;;   -- Note that the turding problem probably just went away, since I fixed this to
;;   erase and redraw images of the frame before and after the change.
;;   (MHD 2/23/90)

;; Consider having this update representations for frame, particularly tables, to
;; reflect the reclassification.
;;   -- Has now been done (by calling update-representations-of-slot-value for
;;   the class slot). (MHD 2/23/90)

;; Note that it may be possible to have this be able to work when the old
;; class has a different icon description, but all the details have not been
;; worked out.  Some complications might include: (1) extra information in the
;; icon attributes plist referring to old (perhaps no longer existent) named
;; regions and (2) similaraly invalid elements in the kb-state-change-plist slot.
;; (MHD 2/23/90)





;;; `Install-deferred-class-definitions' deals with the deferred class
;;; definition mechanism. The variable deferred-class-definitions-alist and the
;;; top-level-element? argument of read-element-for-kb are needed only when
;;; (class-definitions-ordered-p) is false, that is, for kbs saved with versions
;;; of G2 made prior to 7/25/88 (pre-1.11B versions of G2).

(defun install-deferred-class-definitions ()
  (loop for (name-for-class . class-definition-with-no-name)
	    in deferred-class-definitions-alist
	do (install-class-definition
	     name-for-class class-definition-with-no-name nil nil t))
  (reclaim-slot-value-tree deferred-class-definitions-alist)
  (setq deferred-class-definitions-alist nil))



;;; `Defer-class-definition' ... inserts the entry for this definition directly
;;; after an entry for its superior, if any.  This is only needed for pre-1.11B
;;; KBs.

(defun defer-class-definition
    (name-for-class class-definition-with-no-name-yet)
  (let ((superior-class? 
	  (first (direct-superiors-of-defined-class ; always singleton
		   class-definition-with-no-name-yet))))
    (loop with pair
	  = (slot-value-cons name-for-class class-definition-with-no-name-yet)
	  as l on deferred-class-definitions-alist
	  when (eq (car (car l)) superior-class?)
	    return (setf (cdr l) (slot-value-cons pair (cdr l)))
	  finally
	    (slot-value-push pair deferred-class-definitions-alist))))

;; Note that in 3.0, this did not used to be called when superior-class? was
;; nil, but that shouldn't matter much.  This is part of the same obsolete
;; deferred definition facility of which deferred-class-definitions-alist is a
;; part.  Defined here here just to get it out of read-frame-for-kb, from which
;; this code is derived.  (MHD 9/12/94)




;;; `Adjust-superiors-if-necessary-per-class-conflicts' is called while reading
;;; a definition from a KB.
;;;
;;; Direct-superiors should be the list structure of the
;;; direct-superiors-of-defined-class slot for a definition being read in, prior
;;; to its being stored in that slot.
;;;
;;; If a superior class has been changed (because of a compatibility problem
;;; detected earlier in the reading of this kb, i.e., a class conflict), then
;;; the superior class in the list gets changed in place accordingly.
;;;
;;; Note that the change is done by directly mutating the list structure of the
;;; direct-superiors-of-defined-class slot.  This must be called prior to
;;; setting the slot to this list structure.  Otherwise, we'd bypass the slot
;;; putter, which could leave the class system in a bad state.
;;;
;;; This doesn't return any particular value; it's just called for the side
;;; effect of mutating the list structure of its argument.

(defun adjust-direct-superiors-per-class-conflicts (direct-superiors)
  (when class-name-conflicts
    (loop for sublist on direct-superiors
	  for direct-superior = (car-of-cons sublist)
	  do
      (loop for class-name-conflict in class-name-conflicts
	    when (and (eq (car-of-cons class-name-conflict) direct-superior)
		      (cadr-of-cons class-name-conflict))
	      do (setf (car sublist) (cadr-of-cons class-name-conflict))))))

;; In 1.11, when a merged-in kb has an incompatible definition for a class,
;; instances in the merged-in kb will get the OLD class definition, which could
;; result in a corrupted kb if there are new or differently defined attributes
;; in the merged-in kb definion!!




;;; The predicate `automatically-created-junction-block-class-p' returns
;;; a non-null value when the class-definition is a system-generated
;;; default-junction class; otherwise it returns nil.

(def-substitution-macro automatically-created-junction-block-class-p
    (class-definition)
  (and (not (transient-p class-definition))
       (classp (name-of-defined-class class-definition))
       (null (superblock? class-definition))
       (equal (direct-superiors-of-defined-class class-definition) '(default-junction))))




;;; The function `deal-with-junction-block-class-differences' takes care of the
;;; condition caused by the fact that up to G2 50r0 we did not create a
;;; junction-block class when the connection class had no cross-section-pattern;
;;; and in G2 50r1 and beyond we do create a junction-block class even without
;;; a cross-section-pattern in the connection class.

;;; The 50 behavior was done to deal with various kb save/load problems for
;;; junction-block classes (only saved out when there are instances, for example).
;;; Since savingt is a more difficult area to deal with than slot differences,
;;; we use this function to deal with the problems.
;;;
;;; This function returns t when there is a conflict that must be brought to the
;;; users attention; otherwise it returns nil.

(defun deal-with-junction-block-class-differences
    (new-definition old-definition class-name)
  
        ;; When there is no junction-block-class for the new-definition
        ;; but the old-definition has one that is system generated, return nil
        ;; (for no conflict) and the new-definition will be deleted in favor of the old.
    (cond ((and (null (junction-block-class-for-connection new-definition))
		(junction-block-class-for-connection old-definition))
	   (not (automatically-created-junction-block-class-p 
		  (class-definition
		    (junction-block-class-for-connection old-definition)))))

	  ;; when there is no junction-block-class for the old-definition
	  ;; but the new-definition has one, give the old-definition the junction-
	  ;; block value and update the junction-block (if necessary).  The null
	  ;; return value (no junction-block-class conflict) will cause the new-definition
	  ;; to be deleted.
	  ((and (null (junction-block-class-for-connection old-definition))
		(junction-block-class-for-connection new-definition))
	   (cond ((automatically-created-junction-block-class-p
		    (class-definition
		      (junction-block-class-for-connection new-definition)))
		  (change-slot-value
		    old-definition 'junction-block-class-for-connection
		    (junction-block-class-for-connection
		      new-definition))
		  (when (classp class-name)
		    (let ((cross-section-pattern?
			    (or (class-slot-description-value
				  'cross-section-pattern-for-class class-name)
				(let* ((cross-section-pattern-slot-description
					 (slot-description-from-class
					   class-name 'cross-section-pattern)))
				  (slot-init-form
				    (slot-description-of-most-specific-superior-refining-slot
				      (class-inheritance-path
					(class-description class-name))
				      cross-section-pattern-slot-description))))))
		      (update-junction-block-for-connection
			class-name old-definition cross-section-pattern?)
		      (update-connection-subrectangle-structures
			class-name cross-section-pattern?)))
		  nil)
		 ;; The junction-block-class is user-defined and the conflict
		 ;; must come to the attention of the user.
		 (t t)))
	;; We have a genuine conflict in the slot, hopefully with a user-defined
	;; junction-block class.
	  (t t)))




;;; `Install-class-definition' ... does the following:
;;;
;;;    (1) if the class name is now the name of another user-defined class, a
;;;    system class, or a symbol which signifies a G2 datatype, e.g. QUANTITY,
;;;    a class conflict is generated; otherwise, the name is put via the
;;;    slot putter for name-of-defined-class; and
;;;
;;;    (2) update for indexed attribute properties for the definition are made
;;;    as appropriate

(defun install-class-definition
    (name-for-class class-definition-with-no-name-yet new-class-name?
		    differing-slots? class-inheritance-path-needs-refreshing?)
  ;; When differing-slots? is t, read-ghost-definitions has already called
  ;; the fixup code for default overrides.  If the calls change, this
  ;; should be reviewed!  Right now it is an optimization.  (ghw 6/18/97)
  (when (null differing-slots?)
    (when (old-format-for-default-overrides-p-function)
      (fix-up-default-overrides-for-5-0 class-definition-with-no-name-yet))
    (when (and (need-to-normalize-message-properties-p-function)
	       (frame-of-class-p class-definition-with-no-name-yet 'message-definition))
      (normalize-message-properties-for-message-definition class-definition-with-no-name-yet)))
  
  (let ((old-class-definition? (class-definition name-for-class))
    	(direct-superior-classes?
	  (direct-superiors-of-defined-class class-definition-with-no-name-yet)))
    ;; Refresh the class-inheritance-path of the definition since changes in the
    ;; inheritance of its direct-superiors may have changed.  (ghw 10/21/98)
    (when class-inheritance-path-needs-refreshing?
      (reclaim-slot-value
	(class-inheritance-path-of-definition class-definition-with-no-name-yet))
      (setf (class-inheritance-path-of-definition class-definition-with-no-name-yet)
	    (if (direct-superiors-are-defined-p direct-superior-classes?)
		(make-class-inheritance-path-for-user-defined-class
		  nil direct-superior-classes?)
		nil)))
    (cond
      ((and (null old-class-definition?)
	    (null (type-specification-for-user-type name-for-class))
	    (null (substitute-class name-for-class)))
       (put-name-of-defined-class
	 class-definition-with-no-name-yet name-for-class t))
      (t
       (let* ((old-class-definition-is-frame-p
		(and old-class-definition?
		     (class-definition-is-frame-p old-class-definition?)))
	      (definition-classes-are-compatible?
		  (and old-class-definition-is-frame-p
		       (definition-classes-are-compatible-p
			   old-class-definition? class-definition-with-no-name-yet)))
	      (denotations-of-differing-slots
		(when old-class-definition-is-frame-p
		  (let ((current-differing-slots?
			  (or differing-slots?
			      (find-differences-in-frames-if-any
				class-definition-with-no-name-yet old-class-definition?
				nil definition-classes-are-compatible?))))
		    (when (and (frame-of-class-p
				 old-class-definition? 'connection-definition)
			       (frame-of-class-p
				 class-definition-with-no-name-yet 'connection-definition)
			       (neq (junction-block-class-for-connection
				      old-class-definition?)
				    (junction-block-class-for-connection
				      class-definition-with-no-name-yet)))
		      (let ((add-junction-block-class-to-slot-differences?
			      (deal-with-junction-block-class-differences
				class-definition-with-no-name-yet old-class-definition?
				name-for-class)))
			(when add-junction-block-class-to-slot-differences?
			  (setq current-differing-slots?
				(nconc current-differing-slots?
				       (slot-value-list
					 'junction-block-class-for-connection))))))
			current-differing-slots?)))
	      (list-of-conflicts-for-subclasses? nil)
	      (new-name?
		(or new-class-name?
		    (if (or (null old-class-definition?)
			    (not old-class-definition-is-frame-p)
			    denotations-of-differing-slots)
			;; This function changes the name-of-defined-class slot.
			(name-class-with-variant-name
			  name-for-class class-definition-with-no-name-yet)))))
	 (when new-name?
	     ;; The following two loops deal with kbs that have had a subclass
	     ;; definition saved before one of its superior-class definitions.
	     ;; See the comments before this function for an example.
	     
	     ;; If a subclass for name-of-class has been loaded before name-
	     ;; for-class, it can now be a potential-definition of name-for-class
	     ;; unless there is a definition for name-for-class in a basis kb.
	     
	     ;; This loop changes the direct-superiors of such potential
	     ;; definitions and other (genuine) potential definitions to reflect
	     ;; the new name.

	     ;; Note that checking the potential definition frame-serial-
	     ;; number against the current-frame-serial-number-before-reading
	     ;; assures that the potential-definition is in the module currently
	     ;; being loaded or merged and not in any basis kb.
	     (loop for potential-definition
		       in (potential-inferior-class-definitions name-for-class)
		   do
	       (when (frame-has-been-reprocessed-p
		       potential-definition
		       current-frame-serial-number-before-reading)
		 (let* ((direct-superior-classes
			  (direct-superiors-of-defined-class potential-definition))
			(new-direct-superiors
			  (loop for superior in direct-superior-classes
				collect (if (eq superior name-for-class)
					    new-name?
					    superior)
				  using slot-value-cons)))
		   (initialize-slot-value
		     potential-definition 'direct-superiors-of-defined-class
		     new-direct-superiors)
		   (reclaim-slot-value direct-superior-classes))))

	     ;; This loop covers the cases where a subclass was loaded before
	     ;; a superior class, but the basis kb is supplying defined direct
	     ;; superiors for the subclass.  This situation keeps the subclass
	     ;; definition from appearing on the potential-inferior-
	     ;; class-definitions property for name-for-class.
	     (when old-class-definition?
	       (loop for subclass being each subclass of name-for-class
		     for conflict-for-subclass?
			 = (assq subclass class-name-conflicts)
		     do
		 (when conflict-for-subclass?
		   (let* ((new-class-definition-for-subclass
			    (fourth conflict-for-subclass?))
			  (direct-superior-classes
			    (direct-superiors-of-defined-class
			      new-class-definition-for-subclass)))
		     ;; The third component is the old-class-definition.
		     (when (and (third conflict-for-subclass?)
				;; The second component would be the new name.
				(null (second conflict-for-subclass?)))
		       ;; There is essentially no conflict.  It is on the class-
		       ;; name-conflicts list for reclamation purposes only.
		       (setf (second conflict-for-subclass?)
			     (name-class-with-variant-name
			       subclass
			       new-class-definition-for-subclass)))
		     ;; Change the direct-superiors of the inferior class.
		     (when (memq name-for-class direct-superior-classes)
		       (let ((new-direct-superiors
			       (loop for superior in direct-superior-classes
				     collect (if (eq superior name-for-class)
						 new-name?
						 superior)
				       using slot-value-cons)))
			 (initialize-slot-value
			   new-class-definition-for-subclass
			   'direct-superiors-of-defined-class
			   new-direct-superiors)
			 (reclaim-slot-value direct-superior-classes)))
		     ;; Add direct-superiors-of-defined-class to the
		     ;; denotations-of-differing-slots.
		     (when (third conflict-for-subclass?)
		       (setf (fifth conflict-for-subclass?)
			     (slot-value-cons
			       'direct-superiors-of-defined-class
			       (fifth conflict-for-subclass?))))
		     ;; The class-name-conflicts list will need reordering.
		     (setq class-name-conflicts
			   (delete-slot-value-element
			     conflict-for-subclass? class-name-conflicts))
		     (slot-value-push
		       conflict-for-subclass?
		       list-of-conflicts-for-subclasses?))))))
	   ;; Record the conflict for the definition being read.
	   (record-class-name-conflict
	     name-for-class new-name?
	     (if old-class-definition-is-frame-p
		 old-class-definition?)
	     class-definition-with-no-name-yet
	     denotations-of-differing-slots
	     reading-ghost-definitions-p)

	   (setq class-name-conflicts
		 (nconc list-of-conflicts-for-subclasses?
			class-name-conflicts))))))

  (update-indexed-attribute-properties
    class-definition-with-no-name-yet nil nil nil))

;; Defininition saving uses the breadth-first subclass loop path.
;; In a multiple-inheritance hierarchy this path can put a subclass
;; before one of its superior classes.

;; For example:  in the hierarchy below.  If BB is defined before CC,
;; the subclasses of AA will be (AA BB CC EE DD).

;;                        /\
;;                       /  \
;;                      / AA \
;;                      ------
;;                     /      \
;;                    /\      /\
;;                   /  \    /  \
;;                  / BB \  / CC \
;;                  ------  ------
;;                   \         |
;;                    \        /\
;;                     \      /  \
;;                           / DD \
;;                       \   ------
;;                        \/
;;                        /\
;;                       /  \
;;                      / EE \
;;                      ------





;;; `Name-class-with-variant-name' ...

(defun name-class-with-variant-name (intended-name class-definition-with-no-name-yet)
  (when (frame-of-class-p class-definition-with-no-name-yet 'connection-definition)
    (setf (junction-block-class-for-connection class-definition-with-no-name-yet) nil))  
  (put-name-of-defined-class
    class-definition-with-no-name-yet
    (make-new-name-for-frame
      intended-name "-FROM-"
      (get-simple-name-of-kb-being-read))
    t))




;;; `Get-simple-name-of-kb-being-read' ... returns name-of-kb-being-read as a
;;; string iff it contains more than zero (0) gensym characters; otherwise, it
;;; returns the string "KB".  This is only to be called in a KB-reading context,
;;; in which name-of-kb-being-read is appropriately bound.  The resulting string
;;; may be a shared or constant text string.

(defun get-simple-name-of-kb-being-read ()  
  (if (not (string=w name-of-kb-being-read #w""))
      name-of-kb-being-read
      #w"KB"))

;; Note: it may not be possible for the else clause to ever trigger, but I'm not
;; sure.  This used to verify if name-of-kb-being-read was a legal gensym text
;; string, and used the name "KB" if it was not.  But now name-of-kb-being-read
;; is always legal, so it doesn't need to handle that case anymore. (MHD 3/7/94)




;;; `Developer-class-name-conflicts' in development is bound to a list of the
;;; class-name-conflicts from the last KB loaded that had any.

#+development
(def-kb-specific-variable developer-class-name-conflicts
    kb-merge
  nil nil reclaim-slot-value)




;;; The function `preprocess-class-name-conflicts-with-move-attribute-facility'
;;; is the the first-step in dealing with class name conflicts during automerge.
;;; Its role is to notice attributes that have been moved in the basis module
;;; and then move the corresponding attributes in the new-module before the
;;; traditional slot-difference resolution and class-merging work is done.

;;; New module refers to the module currently being loaded, while basis module
;;; refers to a previously loaded module that may have already been processed by
;;; automerge.

;;; This function deals with class name conflicts that are of the form:
;;;    (class new-name old-definition new-definition ({differing-slot}+) t/nil)
;;; where the class-specific-attributes slot occurs in the differing-slots list.

;;; The attribute move is made when conditions are clear, that is, the attribute
;;; to be moved must be equal to the attribute found in the basis-module class
;;; and the target class or any classes that appear between the target class and
;;; the attribute class do not have a class specific attribute with that name,
;;; nor do they have any override with that attribute name.
;;;
;;; Added with-backtrace-for-internal-error ajs (4/30/96)

(defun preprocess-class-name-conflicts-with-move-attribute-facility ()
  (with-backtrace-for-internal-error 'preprocess-class-name-conflicts-with-move-attribute-facility
    (let ((top-down-class-name-conflicts
	    (nreverse (copy-list-using-slot-value-conses class-name-conflicts))))
      (loop for (basis-class new-class basis-definition new-definition
			     differing-slots) in top-down-class-name-conflicts
	    do
	(when (and basis-class new-class basis-definition new-definition
		   (memq 'class-specific-attributes differing-slots))
	  (let ((basis-class-attributes
		  (class-specific-attributes basis-definition))
		;; Copy into new-class-attributes.
		;; Reclaimed at end of let body.
		;; Fix for side-effect in loop body.  See Bug HQ-705559
		;; ajs 4/8/96
		(new-class-attributes
		  (copy-for-slot-value
		    (class-specific-attributes new-definition))))
	    ;;(new-class-attributes
	    ;;(class-specific-attributes new-definition)))
	    ;; See whether the new class has an attribute the basis class doesn't.
	    (loop for new-class-attribute in new-class-attributes
		  for attribute-name = (attribute-name new-class-attribute)
		  do
	      (unless (or (member attribute-name basis-class-attributes
				  :test 'car-eq)
			  (class-has-override-on-pretty-slot-name-p
			    basis-definition attribute-name))
		(loop for basis-subclass being each subclass of basis-class
		      for basis-class-definition = (class-definition
						     basis-subclass)
		      for cons-holding-attribute-description? =
		      (unless (eq basis-subclass basis-class)
			(member attribute-name
				(class-specific-attributes
				  basis-class-definition)
				:test 'car-eq))
		      for override-on-attribute? =
		      (unless (eq basis-subclass basis-class)
			(class-has-override-on-pretty-slot-name-p
			  basis-class-definition attribute-name))
		      do
		  ;; The basis-subclass loop terminates when the or form is t.
		  (when (or cons-holding-attribute-description?
			    override-on-attribute?)
		    (when (and cons-holding-attribute-description?
			       (not override-on-attribute?)
			       (equal (car-of-cons
					cons-holding-attribute-description?)
				      new-class-attribute))
		      (let* ((cons-holding-basis-subclass-name-conflict?
			       (member basis-subclass
				       top-down-class-name-conflicts
				       :test 'car-eq))
			     (new-subclass?
			       (when cons-holding-basis-subclass-name-conflict?
				 (second
				   (car-of-cons
				     cons-holding-basis-subclass-name-conflict?)))))
			(when new-subclass?
			  (let ((new-subclass-definition
				  (class-definition new-subclass?)))
			    (unless (or (member
					  attribute-name
					  (class-specific-attributes
					    new-subclass-definition)
					  :test 'car-eq)
					(class-has-override-on-pretty-slot-name-p
					  new-subclass-definition attribute-name))
			      (put-change
				new-definition
				(slot-value-list
				  'move-attribute attribute-name new-subclass?) nil))))))
		    (loop-finish)))))
	    ;; See if the basis class has an attribute the new class doesn't.
	    (loop for basis-class-attribute in basis-class-attributes
		  for attribute-name = (attribute-name basis-class-attribute)
		  do
	      (unless (or (member
			    attribute-name
			    (class-specific-attributes new-definition)
			    :test 'car-eq)
			  (class-has-override-on-pretty-slot-name-p
			    new-definition attribute-name))
		(loop for new-subclass being each subclass of new-class
		      for new-subclass-definition = (class-definition
						      new-subclass)
		      for cons-holding-attribute-description? =
		      (unless (eq new-subclass new-class)
			(member attribute-name
				(class-specific-attributes
				  new-subclass-definition)
				:test 'car-eq))
		      for override-on-attribute? =
		      (unless (eq new-subclass new-class)
			(class-has-override-on-pretty-slot-name-p
			  new-subclass-definition attribute-name))
		      do
		  ;; The new-subclass loop terminates when the or form is t.
		  (when (or cons-holding-attribute-description?
			    override-on-attribute?)
		    (when (and cons-holding-attribute-description?
			       (not override-on-attribute?)
			       (equal (car-of-cons
					cons-holding-attribute-description?)
				      basis-class-attribute))
		      (let* ((cons-holding-new-subclass-name-conflict?
			       (member new-subclass
				       top-down-class-name-conflicts
				       :test 'cadr-eq))
			     (basis-subclass?
			       (when cons-holding-new-subclass-name-conflict?
				 (car-of-cons
				   (car-of-cons
				     cons-holding-new-subclass-name-conflict?)))))
			(when basis-subclass?
			  (let ((basis-subclass-definition
				  (class-definition basis-subclass?)))
			    (unless (or (member
					  attribute-name
					  (class-specific-attributes
					    basis-subclass-definition)
					  :test 'car-eq)
					(class-has-override-on-pretty-slot-name-p
					  basis-subclass-definition attribute-name))
			      (put-change
				(class-definition new-subclass)
				(slot-value-list
				  'move-attribute attribute-name new-class) nil))))))
		    (loop-finish)))))
	    ;; ajs 4/8/96. see copy above.
	    (reclaim-slot-value new-class-attributes))))
      (reclaim-slot-value-list top-down-class-name-conflicts))))




;;; `Deal-with-class-name-conflicts' ... is performed at the end of reading a kb.
;;; Note that this expects to be called in a for-workstation context.

;;; At present, if two definitions are equivalent, one is always deleted.  If just
;;; one has a subworkspace, that subworkspace is kept.  If both have a subworkspace,
;;; the subworkspace of the newer equivalent definition will be deleted, even if it
;;; is not equivalent to the subworkspace of the older definition.
;;;
;;; Added with-backtrace-for-internal-error  ajs (4/30/96)

(defun deal-with-class-name-conflicts (auto-merge-case? new-algorithm?)
  (with-backtrace-for-internal-error 'deal-with-class-name-conflicts
    (when auto-merge-case?
      (preprocess-class-name-conflicts-with-move-attribute-facility))
    (loop with number-of-conflicts = 0
	  with number-of-subworkspaces-deleted = 0	; eliminate later!
	  with ghost-definitions-to-restore = nil
	  with deferred-class-name-conflicts = nil	; added to in reverse order
	  with workspace-coordinate-information = nil
	  as class-name-conflict in class-name-conflicts
	  as (class new-name? old-class-definition?
		    new-class-definition denotations-of-differing-slots
		    ghost-definition-p)
	     = class-name-conflict
	  do
      (cond
	((and ghost-definition-p
	      (superblock? new-class-definition))
	 (setq workspace-coordinate-information
	       (fix-definitions-saved-as-ghost-definitions
		 new-class-definition
		 workspace-coordinate-information
		 new-algorithm?)))
	;; In this case, it is a ghost definition and there is no
	;; old-definition, indicating that a definition was removed from a
	;; required module.  If there are no non-ghost subclasses and no
	;; instances, we do not bring it to the attention of the user.
	;; (ghw 8/13/97)
	((and (null new-name?)
	      (null old-class-definition?)
	      (null denotations-of-differing-slots)
	      ghost-definition-p)
	 (if (or (if (subclassp class 'connection)
		     (connection-class-is-instantiated-p class)
		     (instantiated-class-p class))
		   ;; There is a subclass definition that is not a ghost.
		 (loop for subclass being each subclass of class
		       thereis
		       (superblock? (class-definition subclass))))
	     (unless (automatically-created-junction-block-class-p new-class-definition)
	       (gensym-push
		 new-class-definition ghost-definitions-to-restore))
	     (delete-frame new-class-definition)))
	;; There is a ghost definition that is, inexplicably, not defined because
	;; of an undefined direct superior.  This was seen in a 4.0 kb.
	((and ghost-definition-p
	      new-name?
	      (not (classp new-name?)))
	 #+development
	 (cerror "kb-merge" "loaded ghost definition is an aberration -- tell ghw")
	 (delete-frame new-class-definition))
	;; In this case, there is a conflict between a user-defined default-junction
	;; class-definition and a system-defined default-junction class-defintion.
	;; This conflict should never be brought to the attention of the user
	;; because the system-generated class-definition is not editable.  

	;; The ideal way of handling this situation is to have the code that
	;; automatically generates the default-junction classes (define-user-
	;; class and the slot-putter for cross-section-pattern) to refrain from
	;; creating the classes during kb-load time.  It is not necessary to do
	;; so because the system-defined default-junction classes are saved.
	;; However, recreating of them at loadtime has been in the product for
	;; a long time and creates no serious problems when users do not create
	;; their own classes, although it is a performance drag at loadtime and,
	;; I suspect, there may be some older kbs that depend on this behavior.

	;; The code below detects an automatically created default-junction class
	;; that conflicts with a user-defined default-junction class and deletes
	;; the system-generated class and renames the user-defined class.  (ghw 8/20/98).
	((and (subclassp class 'default-junction)
	      (subclassp new-name? 'default-junction)
	      (not (instantiated-class-p class))
	      (not (transient-p old-class-definition?))
	      (null (superblock? old-class-definition?)))
	 (delete-frame old-class-definition?)
	 (change-slot-value new-class-definition 'name-of-defined-class class))
	((or (null new-name?)
	     (and (frame-status new-class-definition)
		  (null (superblock? new-class-definition))))
	 (if (subworkspaces new-class-definition)
	     (cond
	       ((null (subworkspaces old-class-definition?))
		(transfer-subworkspace-if-any
		  new-class-definition old-class-definition?)
		(delete-block-after-reading-kb new-class-definition))
	       (t (delete-block-after-reading-kb new-class-definition)	; eliminate later!
		  (incff number-of-subworkspaces-deleted))
;		    ((workspaces-equal-p	; do later!
;		       new-class-definition old-class-definition?)
;		     (delete-block-after-reading-kb new-class-definition))
;		    (t (setq new-name?
;			     (name-class-with-variant-name
;			       class new-class-definition)))
	       )
	     (delete-block-after-reading-kb new-class-definition)))
	(t
	 (when ghost-definition-p
	   (unless (automatically-created-junction-block-class-p new-class-definition)
	     (gensym-push
	       new-class-definition ghost-definitions-to-restore)))
	 (if (and record-class-name-conflicts?
		  (and old-class-definition?
		       denotations-of-differing-slots))
	     (setq deferred-class-name-conflicts
		   (slot-value-cons
		     (copy-tree-using-slot-value-conses class-name-conflict)
		     deferred-class-name-conflicts))
	     (progn
	       (incff number-of-conflicts)
	       (create-class-definition-conflict-workspace
		 class new-name?
		 old-class-definition? new-class-definition
		 denotations-of-differing-slots (not new-algorithm?))))))
      
	  finally
	    (when workspace-coordinate-information
	      (reclaim-frame-tree workspace-coordinate-information))
	    (when ghost-definitions-to-restore
	      (restore-ghost-definitions
		ghost-definitions-to-restore new-algorithm?))
	  
	    (if record-class-name-conflicts?
		(record-class-name-conflicts
		  (nreverse deferred-class-name-conflicts)))
	    (progn
	      ;; let developers like me have a record of this stuff:
	      #+development
	      (setq developer-class-name-conflicts
		    (copy-tree-using-slot-value-conses class-name-conflicts))
	      (reclaim-slot-value-tree class-name-conflicts)
	      (setq class-name-conflicts nil))
	    (if (>f number-of-conflicts 0)
		(notify-user-of-conflict-report-workspace-creation number-of-conflicts))
	    (if (>f number-of-subworkspaces-deleted 0)	; eliminate later!
		(notify-user-of-conflicts
		  "The merged-in KB ~S contains ~D class definition(s) with subworkspaces ~
                 that have been verified to be the same as established (existing) ~
                 definitions with subworkspaces, except that the corresponding ~
                 subworkspaces have not been verified to be equivalent.  These ~
                 new definitions, with their subworkspaces, have been deleted."
		  name-text-string-for-kb-being-read 
		  number-of-subworkspaces-deleted)))))




;;; `Restore-ghost-definitions' creates a "Backup Definitions" KB-workspace
;;; containing backup ("ghost") definitions in ghost-definitions-to-restore and
;;; an explanation of this workspace's purpose.  This returns the resulting
;;; workspace.
;;;
;;; New-algorithm? is required as the arg to normalize-kb-workspace, which this
;;; function must apply to the resulting workspace; it is to be passed down from
;;; KB loading based on the "vintage" of the KB being loaded.
;;;
;;; It is an error for any definition in ghost-definitions-to-restore to be
;;; already a subblock of any workspace.
;;;
;;; The workspace is assigned to the module being read, if any.
;;;
;;; The name made up for the workspace is of the form
;;;
;;;    BACKUP-DEFINITION-FROM-<name of KB being read>
;;;
;;; This sets up `current-backup-definition-workspace-serial-number?' and
;;; `current-backup-definition-workspace?' so that the workspace can be
;;; dealt with after automerge.
;;;
;;; Upon completion, the workspace is either displayed now or later using
;;; put-workspace-on-detail-panes-now-or-later.

(def-kb-specific-variable current-backup-definition-workspace?
    kb-merge nil)

(def-kb-specific-variable current-backup-definition-workspace-serial-number?
    kb-merge nil nil reclaim-frame-serial-number)
    

(defun restore-ghost-definitions (ghost-definitions-to-restore new-algorithm?)
  (let* ((explanation
	   (make-free-text-box
	     (tformat-text-string
	       "The class definitions on this workspace have been restored ~
                because they are no longer provided by the required modules.  ~
                After you have examined the class definitions ~
                and any subclasses and instances, you can move the definitions ~
                to other workspaces or delete them, and then delete ~
                this workspace.")))
	 (workspace
	   (make-new-top-level-kb-workspace
	     'kb-workspace
	     nil 
	     (intern-text-string
	       (tformat-text-string
		 "BACKUP-DEFINITIONS-FROM-~a"
		 (get-simple-name-of-kb-being-read)))
	     nil nil nil
	     (if reading-kb-p name-of-module-being-read?)))
	 (name-box
	   (loop for subblock being each subblock of workspace
		 when (frame-of-class-p subblock 'workspace-name-box)
		   return subblock))
	 (spacing-between-columns 200)	; sadly, must leave room for name 
	 (spacing-between-entries 50)	;   boxes jutting out
	 (spacing-within-entries 10)
	 ;; start off in extreme upper left corner of coordinate system, to give
	 ;; maximum room to grow down and right:
	 (inside-left-edge	     
	   (+w most-negative-workspace-coordinate
	       500			; leave 500 ws units to spare for 
	       ))			;   name boxes jutting out
	 (inside-top-edge
	   (+w most-negative-workspace-coordinate
	       300			; ditto. (300 for name box)
	       ))
	 (inside-bottom-edge
	   (-w most-positive-workspace-coordinate
	       100			; a little extra space for convenience
	       500))			; plenty of extra space if needed due
					;   to mishandling of name boxes in the
					;   layout function
	 (list-of-layout-entries
	   (loop for definition in ghost-definitions-to-restore
		 as class = (name-of-defined-class definition)
		 as caption = (make-caption-for-class-definition-table class definition)
		 do (progn
		      #+development
		      (test-assertion (null (superblock? definition))))		    
		 collect (gensym-list caption definition)
		   using gensym-cons)))
    (add-to-workspace
      explanation workspace inside-left-edge inside-top-edge)
    (shift-block			; moves name box above explanation
      name-box
      (-w inside-left-edge (left-edge-of-block name-box))
      (-w (-w (top-edge-of-block explanation)
	      (+w spacing-between-entries
		  (height-of-block name-box)))
	  (top-edge-of-block name-box)))
    (add-and-lay-out-blocks-on-workspace
      list-of-layout-entries
      workspace
      inside-left-edge
      (+w (bottom-edge-of-block explanation)
	  spacing-between-entries)
      inside-bottom-edge
      spacing-between-columns
      spacing-between-entries
      spacing-within-entries)
    (shrink-wrap-workspace workspace)	; around group of stuff in upper, left
    (reclaim-gensym-tree list-of-layout-entries)
    (normalize-kb-workspace workspace new-algorithm?)
    (setq current-backup-definition-workspace-serial-number?
	  (copy-frame-serial-number (frame-serial-number workspace)))
    (setq current-backup-definition-workspace? workspace)
    (unless do-not-show-conflicts-during-kb-load?
      (put-workspace-on-detail-panes-now-or-later workspace))
    workspace))



;;; `Add-and-lay-out-blocks-on-workspace' is a general routine for adding blocks
;;; to workspaces and laying them out in columns with an upper and lower
;;; (vertical) limit, growing out to the right with no definite limit.  At
;;; present, we don't do anything about that.  [Ultimately, this should be an
;;; error condition in the case of overflowing a workspace coordinate maximum!
;;; An approach to this in the backup-definitions case might be to have this
;;; function return the tail of the argument list that could not fit; then the
;;; caller could open a another workspace to deal with the remainder.  That work
;;; is deferred for now. (MHD 6/6/95)]
;;;
;;; List-of-layout-entries should be a list of lists of blocks.  For each block
;;; in each sublist, it is added to workspace using add-to-workspace.
;;;
;;; Right after the call to add-to-workspace, the name-or-names-for-frame slot
;;; of the block is updated, just in order to cause the name box to be added to
;;; the block if it has a name box that would be shown.
;;;
;;; The position is determined by the variables initial-left-edge,
;;; initial-top-edge, bottom-edge-limit, spacing-between-entries,
;;; spacing-between-entries, and spacing-within-entries.
;;;
;;; Note that when the name box is shown, it is typically centered under its
;;; object, this may result in the extreme edges of the column jutting out on
;;; the right or left.  The only way to avoid them jutting out past some
;;; boundary at present is to leave enough room on the left edge (i.e., have the
;;; initial-left-edge argument start out far enough to the right), and to allow
;;; enough room between columns (i.e., have the argument spacing-between-columns
;;; be large enough to keep columns from overlapping).  Unfortunately, this
;;; doesn't allow you to have a custom fitted column based on the actual widths
;;; of the items that get laid out.  This might be addressed as an improvement,
;;; later.
;;;
;;; The first block of the first sublist always has its top-left corner at
;;; (initial-left-edge, initial-top-edge).  Each subsequent block (if any) in
;;; the sublist has its top edge spacing-within-entries workspace units below
;;; the previous block's bottom edge.
;;;
;;; After each entry, if the bottom edge of the _next_ block in that entry, if
;;; any, would fall above bottom-edge-limit, the next entry begins as normal,
;;; i.e., spacing-between-entries workspace units below the bottom edge of the
;;; last block in the previous entry.
;;;
;;; Otherwise, a new column begins spacing-between-columns workspace units to
;;; the right of the maximum right edge of all the blocks in the previous
;;; column.  The first block in each such new column has its top edge at
;;; initial-top-edge again.
;;; 
;;; Note that the above test is after the placement of the first of the
;;; remaining entries to ensure that at least one entry gets added to each
;;; column.  That entry could extend below the bottom-edge-limit if it were long
;;; enough.  But apart from that case, the test assures that subsequent entries
;;; will not appear in a column if they would spill over the limit.  This is
;;; similar to our text line breaking algorithm (but x/y reversed, of course).
;;; Thus entries never hang over bottom-edge-limit except in the somewhat
;;; pathological case of a single entry being taller than (bottom-edge-limit
;;; minus initial-top-edge).  [Ultimately, this should be also be an error
;;; condition in the case of overflowing a workspace coordinate maximum!  That
;;; work is deferred for now. (MHD 6/6/95)]
;;;
;;; The above process of laying out the entries continues until all entries have
;;; been added.  .
;;;
;;; Note that the workspace argument may be any subclass of workspace.  But note
;;; also that this does not call normalize-kb-workspace after adding entries --
;;; that is the caller's responsibility to do for kb-workspace workspaces.  It
;;; may be assumed that it is OK to call normalize-kb-workspace after a call to
;;; add-and-lay-out-blocks-on-workspace has completed (i.e., it need not be
;;; called incrementally with the addition of each new subblock).
;;;
;;; This does not reclaim or alter the list structure of list-of-layout-entries
;;; in any way.
;;;
;;; NOTE: add-and-lay-out-blocks-on-workspace has a limitation that should keep
;;; it out of general use until it is fixed: it does not account for the name
;;; box that gets added under an item (e.g., a definition) when deciding if the
;;; next entry would fit.  Therefore, the caller must supply plenty of padding
;;; below bottom-edge-limit to account for the possible discrepancy, which
;;; is limited to the height of a potential name box plus its distance below
;;; its item.

(defun add-and-lay-out-blocks-on-workspace
    (list-of-layout-entries
      workspace
      initial-left-edge initial-top-edge bottom-edge-limit
      spacing-between-columns spacing-between-entries spacing-within-entries)
  (loop with remaining-entries = list-of-layout-entries
	with max-right-edge = initial-left-edge
	as left-edge
	   = initial-left-edge
	   then (+w max-right-edge spacing-between-columns)
	while remaining-entries
	do (loop with max-bottom-edge = initial-top-edge
		 for entry = (pop remaining-entries)
		 as top-edge
		 = initial-top-edge
		    then (+w max-bottom-edge spacing-between-entries)
		 do (loop for block in entry
			  as top-edge-now
			     = top-edge
			     then (+w max-bottom-edge
				      spacing-within-entries)
			  do (add-to-workspace
			       block workspace
			       left-edge top-edge-now)
			     (update-representations-of-slot-value
			       ;; only to fix up the name box !!
			       block 'name-or-names-for-frame)
			     (multiple-value-bind
				 (extreme-left-edge extreme-top-edge
				  extreme-right-edge extreme-bottom-edge)
			       (determine-extreme-edges-of-block block)
			       (declare (ignore extreme-left-edge
						extreme-top-edge))
			       (setq max-right-edge
				     (maxw max-right-edge
					   extreme-right-edge))
			       (setq max-bottom-edge
				     (maxw max-bottom-edge
					   extreme-bottom-edge))))
		 while (and remaining-entries
			    (<w (+w max-bottom-edge
				    ;; the following sum is the total
				    ;; height for the next entry:
				    (+w spacing-between-entries
					(loop with height = 0
					      for block in (first remaining-entries)
					      do (setq height
						       (+w height
							   (height-of-block block) ; see note!
							   (if (=f height 0)
							       0
							       spacing-within-entries)))
					      finally (return height))))
				bottom-edge-limit)))))


;; Whoops -- what about subblocks or potential subblocks!  Redo the code to put
;; items down, and then be prepared to shift them up to a new column if they
;; overflow.  Remember that name box gets added only after you add the item to
;; the workspace!


#+development
(defun test-layout ()
  (let* ((count 100)
	 (workspace
	   (make-new-top-level-kb-workspace
	     'kb-workspace
	     nil 'test-layout
	     nil nil nil nil))
	 (name-box
	   (loop for subblock being each subblock of workspace
		 when (frame-of-class-p subblock 'workspace-name-box)
		   return subblock))
	 (inside-left-edge
	   (left-edge-of-block name-box))
	 (inside-top-edge
	   (+w (bottom-edge-of-block name-box) 10))
	 (inside-bottom-edge 1000)
	 (spacing-between-columns 200)
	 (spacing-between-entries 10)
	 (spacing-within-entries 10)
	 (objects
	   (loop for i from 1 to count
		 as object
		 = (make-entity 'quantitative-variable)
		 do (change-slot-value
		      object 'name-or-names-for-frame
		      (intern-text-string
			(tformat-text-string "ASDFASDFASDFASFASDFASDFASFADFOBJECT-~d" i)))
		 collect object using gensym-cons))
	 (list-of-layout-entries
	   (prog1
	       (loop for object in objects
		     collect (gensym-list object) using gensym-cons)
	     (reclaim-gensym-list objects))))
    (add-and-lay-out-blocks-on-workspace
      list-of-layout-entries
      workspace
      inside-left-edge inside-top-edge inside-bottom-edge
      spacing-between-columns spacing-between-entries spacing-within-entries)
    (shrink-wrap-workspace workspace)	; around group of stuff in upper, left
    (reclaim-gensym-tree list-of-layout-entries)
    (normalize-kb-workspace workspace t)
    (put-workspace-on-detail-panes-now-or-later workspace)))

;; The above should put up a workspace laid out neatly.




;;; This clause shouldn't be necessary, but there were bugs that caused some
;;; instances of definitions that were really in the saved workspace hierarchy
;;; to be saved as "ghost definitions".  If a definition is found here with a
;;; superblock, presumably it is one of these definitions, and should be ignored
;;; here as it already exists on some workspace in the KB.
;;;
;;; One further point of lossage is that we've lost the name box and the
;;; workspace location of the definition. Here we arrange the definition icons
;;; in a row at the bottom of the enlarged workspace.  (MHD/GHW 10/24/94)
;;;
;;; Added with-backtrace-for-internal-error ajs (4/30/96) 

(defun fix-definitions-saved-as-ghost-definitions
    (new-class-definition workspace-coordinate-information new-algorithm?)
  (with-backtrace-for-internal-error 'fix-definitions-saved-as-ghost-definitions
    (let* ((workspace (superblock? new-class-definition))
	   (coordinate-information?
	     (car (member
		    workspace workspace-coordinate-information
		    :test 'car-eq)))
	   (left-edge nil)
	   (top-edge nil))
      (cond (coordinate-information?
	     (setq top-edge (second coordinate-information?))
	     (setq left-edge (third coordinate-information?))
	     (setf (third coordinate-information?)
		   (+w left-edge 60)))
	    (t (setq top-edge (bottom-edge-of-block workspace))
	       (setq left-edge (left-edge-of-block workspace))
	       (setq workspace-coordinate-information
		     (frame-cons (frame-list
				   workspace
				   top-edge (+w left-edge 80))
				 workspace-coordinate-information))))
      (shift-block new-class-definition left-edge top-edge)
      (enlarge-workspace-for-block-and-subblocks-as-necessary
	new-class-definition workspace)
      (update-representations-of-slot-value
	;; only to fix up the name box !!
	new-class-definition 'name-or-names-for-frame)
      (normalize-kb-workspace
	(superblock? new-class-definition)
	new-algorithm?)
      workspace-coordinate-information)))

;; Use special color for workspace area background!

;; Most, if not all, of the width-of-block and height-of-block calls herein could
;; be replaced by right-edge-of-block and bottom-edge-of-block, respectively, since
;; their arguments are at (0,0)!

;; When more than one such workspace is put up, consider offsetting their image planes.

;; Ideally, the text boxes would not be selectable.





;;; The function `notify-user-of-conflicts' notifies the user of certain events
;;; during conflict resolution.

(defun notify-user-of-conflicts (notification-as-format-string 
				  &optional
				  (arg1 no-arg) (arg2 no-arg) (arg3 no-arg)
				  (arg4 no-arg) (arg5 no-arg) (arg6 no-arg)
				  (arg7 no-arg) (arg8 no-arg) (arg9 no-arg))
  (unless do-not-show-conflicts-during-kb-load?
    (call-per-number-of-actual-args
      notify-user
      1 notification-as-format-string	
      arg1 arg2 arg3
      arg4 arg5 arg6
      arg7 arg8 arg9)))


;;; Notify-user-of-conflict-report-workspace-creation ... expects only be called
;;; when name-text-string-for-kb-being-read is bound, i.e., during reading of a
;;; KB.  This should be called iff number-of-conflicts, the number of conflict
;;; workspaces created, is 1 or more.

(defun notify-user-of-conflict-report-workspace-creation (number-of-conflicts)
  (notify-user-of-conflicts
    (if (=f number-of-conflicts 1)
	"The KB ~S contains a class definition that differs from an established ~
	 (existing) definition.  A conflict report workspace has been created for this."
	"The KB ~S contains ~D class definitions that differ from established ~
	 (existing) definitions.  For each of these, a conflict report workspace has ~
	 been created.")
    name-text-string-for-kb-being-read number-of-conflicts))




;;; Create-class-definition-conflict-workspace ... If old-algorithm? is true,
;;; then the new-algorithm? arg to normalize-kb-workspace is provided as
;;; false.

(defun create-class-definition-conflict-workspace
    (class new-name?
	   old-class-definition? new-class-definition
	   denotations-of-differing-slots &optional old-algorithm?)
  (let* ((class-definition (or old-class-definition? new-class-definition))
	 (paragraph-1
	   (make-free-text-box
	     
	     (tformat-text-string
	       (if old-class-definition?
		   "CONFLICT REPORT!  The merged-in KB ~S contained a definition for ~A ~
                    that differed from an established (existing) definition.  The class ~
                    from the merged-in KB has been renamed ~A.  (If you keep this new ~
                    name, you should update rules, formulas, etc., appropriately.)"
		   "CONFLICT REPORT!  When the KB ~S was saved out, it contained a ~
                    definition for ~A, which has since become a built-in class or type.  Because ~
                    of this, the class from the KB has been renamed ~A.  You should ~
                    update rules, formulas, etc., appropriately.  (You may delete ~
                    this workspace when you are done looking at it.)")
	       name-text-string-for-kb-being-read class new-name?)
	     
	     'borderless-free-text 'conflict-report-format))
	 (paragraph-2?
	   (if old-class-definition?
	       (make-free-text-box
		 (tformat-text-string
		   "You may wish to edit one or both of the tables below.  Differences in ~
                    the tables have been highlighted.  If the tables become identical ~
                    except for the class names, you may merge one of them into the other ~
                    by editing the CHANGE slot.  Type or select \"merge all instances and ~
                    subclasses into definition for <other class>.\"  Be sure to read the ~
                    logbook notes when you do this.  You should delete this workspace when ~
                    you are done with it.")
		 'borderless-free-text 'conflict-report-format)))
	 (caption-for-class-definition-table
	   (make-caption-for-class-definition-table
	     (name-or-names-for-frame class-definition) class-definition))
	 (class-definition-table
	   (make-attributes-table class-definition))
	 (caption-for-new-class-definition-table?
	   (if old-class-definition?
	       (make-caption-for-class-definition-table
		 new-name? new-class-definition)))
	 (new-class-definition-table?
	   (if old-class-definition?
	       (make-attributes-table		; omit slot descriptions?
		 new-class-definition)))
	 (workspace
	   (make-new-top-level-kb-workspace
	     'kb-workspace
	     ;; conflict-report-workspace? temporary-workspace?
	     nil
	     (make-name-for-class-name-conflict-workspace class)
	     paragraph-1 nil nil
	     (if reading-kb-p name-of-module-being-read?)))
	 (left-edge-for-class-definition-table
	   (left-edge-of-block paragraph-1))
	 (left-edge-for-new-class-definition-table
	   (+w left-edge-for-class-definition-table
	       (maxw (width-of-block class-definition-table)
		     (width-of-block caption-for-class-definition-table)
		     (width-of-block paragraph-1))
	       50)))				; adjust?
    (if paragraph-2?
	(add-to-workspace
	  paragraph-2? workspace left-edge-for-new-class-definition-table
	  (top-edge-of-block paragraph-1)))
    (add-to-workspace
      caption-for-class-definition-table workspace
      (+w left-edge-for-class-definition-table
	  (maxw (halfw (-w (width-of-block class-definition-table)
			   (width-of-block caption-for-class-definition-table)))
		0))		  
      (+w (maxw (bottom-edge-of-block paragraph-1)
		(bottom-edge-of-block (or paragraph-2? paragraph-1)))
	  40))					; adjust?
    (if caption-for-new-class-definition-table?
	(add-to-workspace
	  caption-for-new-class-definition-table? workspace
	  (+w left-edge-for-new-class-definition-table
	      (maxw (halfw (-w (width-of-block new-class-definition-table?)
			       (width-of-block
				 caption-for-new-class-definition-table?)))
		    0))
	  (top-edge-of-block caption-for-class-definition-table)))
    
    ;; Old code commented out! -- this no longer the right thing to do here.  There were
    ;; two things wrong: (1) this was confusing junction block definitions,
    ;; which may or may not have been ghosts, with ghosts, and (2) the putter
    ;; for direct-superiors-of-defined-class did not like dealing (non-junction)
    ;; definitions, so doing this here was too late in the automerge case!
    ;; (MHD 4/24/92)
;    (if (null (superblock? new-class-definition))	; "sketch of ghost" case
;	(add-to-workspace
;	  new-class-definition workspace
;	  (+w left-edge-for-new-class-definition-table
;	      (maxw (halfw (-w (width-of-block new-class-definition-table?)
;			       (width-of-block new-class-definition)))
;		    0))
;	  (+w (maxw (bottom-edge-of-block caption-for-class-definition-table)
;		    (bottom-edge-of-block
;		      (or caption-for-new-class-definition-table?
;			  caption-for-class-definition-table)))
;	      15)))
    
    (add-to-workspace
      class-definition-table workspace
      left-edge-for-class-definition-table
      (+w (maxw (bottom-edge-of-block caption-for-class-definition-table)
		(bottom-edge-of-block
		  (or (if (eq (superblock? new-class-definition)
			      workspace)
			  new-class-definition)
		      caption-for-new-class-definition-table?
		      caption-for-class-definition-table)))
	  15					; adjust?
	  (if (eq (superblock? new-class-definition)
		  workspace)
	      20				; extra bit for name box
	      0)))			
    (if old-class-definition?
	(highlight-differing-slots-in-definitions
	  class-definition new-class-definition
	  denotations-of-differing-slots))
    (if new-class-definition-table?
	(add-to-workspace
	  new-class-definition-table? workspace
	  left-edge-for-new-class-definition-table
	  (top-edge-of-block class-definition-table)))
    
    
    (progn
      (change-slot-value			; only to fix up the name box
	new-class-definition 'name-or-names-for-frame	; later for
	just-update-representations-of-slot-value))	;   class-definition?
    
    
    (unless do-not-show-conflicts-during-kb-load?
      (if servicing-workstation?	        ; put up problem workspace only on
	  (put-workspace-on-pane		;   the window from which the KB
	    workspace				;   is being interactively loaded, if any
	    current-workstation-detail-pane	;   -- maybe put on all windows?!
	    'left 'top
	    nil					; no longer use scale-to-fit as
						;   of today: there can be hundreds
						;   of these, and scaling takes a
						;   lot more time and consumes a
						;   huge amount of space for the
						;   odd-sized font bitmaps.
						;   (MHD 12/6/91)
						;
	    :margin-in-pane 50)))
    ;; RETROFIT!!!
    ;; Any kb-workspace created during read-kb must be normalized, otherwise
    ;; the tamper mechanism for packages will bomb out.
    (normalize-kb-workspace workspace (not old-algorithm?))))




;;; Make-name-for-class-name-conflict-workspace ...

(defun make-name-for-class-name-conflict-workspace (class)
  (intern-text-string
    (tformat-text-string "~a-CLASS-NAME-CONFLICT" class)))




;;; `Make-caption-for-class-definition-table' ...

(defun make-caption-for-class-definition-table (class class-definition)
  (let* ((number-of-instances
	   (loop for frame being class-instances of class count frame))
	 (number-of-subclasses
	   (-f (loop for frame being subclasses of class count frame) 1))
	 (subclasses-phrase
	   (if (>f number-of-subclasses 0)
	       (tformat-text-string
		 " and ~D subclass~A"
		 number-of-subclasses (if (=f number-of-subclasses 1) "" "es"))
	       "")))
    (prog1
      (make-free-text-box
	(tformat-text-string
	  "Definition for ~A.  ~D instance~A~A~A."
	  class number-of-instances (if (=f number-of-instances 1) "" "s")
	  subclasses-phrase
	  (if (subworkspaces class-definition) " and a subworkspace" ""))
	'borderless-free-text 'conflict-report-format)	; center the caption?
      (if (>f number-of-subclasses 0)
	  (reclaim-text-string subclasses-phrase)))))



;;; `Conflict-report-format' is borderless.

(def-text-box-format conflict-report-format
  minimum-format-width-for-text-cell 590
  maximum-format-width-for-text-cell 790
  text-cell-font-map (hm18)			; 1 en = 10 workspace units
  text-cell-line-height 20			; experiment with these!
  text-cell-baseline-position 15
  text-cell-line-spacing 4
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 6.75)  ; 2/3 en
  minimum-word-spacing #.(convert-to-text-width 5)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 15)	          ; 3/2 en
  text-cell-paragraph-indentation 0		; 12?
  text-cell-turnover-line-indentation 0
  text-cell-lines-justified? nil
  text-cell-line-color? black
  text-box-border-color? black
  text-cell-left-margin 6
  text-cell-top-margin 3
  text-cell-right-margin 6
  text-cell-bottom-margin 2
  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0)

;; Elimate wide-caption-format in module BOXES if it is no longer used!










;;;; Automerge: Resolving Class Name Conflicts Automatically


;;; The following is based on DWR's "Merge Enhancement Proposal - 5/14/91"
;;;
;;; Classes whose instances to delete when there is a conflict:
;;; 
;;;    procedure				named
;;;                                             NOTE: a common situation is where
;;;                                             there's an initially system-defined
;;;                                             procedure that the user is expected
;;;                                             to modify and enhance; if it would
;;;                                             be bad to then delete the users work,
;;;                                             the procedure should be renamed in each
;;;                                             new release with a version suffix or
;;;                                             prefix embedded in its name to prevent
;;;                                             it from overriding the previous version.
;;;                                             E.g. in GMM.KB, you can have a configuration
;;;                                             -action-VERSION-8 procedure, instead
;;;                                             of simply configuration-action.  [Maybe
;;;                                             this needs some more thought! -MHD/DWR]
;;;
;;;    method-declaration                       conflicts are ignored, since they don't
;;;                                             matter, and we invite conflict by requiring
;;;                                             these to be present for methods to work in
;;;                                             a given module; note that this is NOT
;;;                                             handled the same way as procedure or method
;;;                                             
;;;
;;;    method                                   if the procedure name is the same (different
;;;                                             from its name) AND for the same class, AND
;;;                                             has the same number of arguments
;;;
;;;    
;;; 
;;;    function					named
;;;    tabular-function				named
;;;
;;;    relation					named
;;;    
;;; A special situation arises with the class `relation'.  A completed relation
;;; definition actually has two names in its name-or-names-for-frames list.
;;; However, these are not directly editable by the user in that slot (the names
;;; attribute).  Instead, the names attribute is not shown, and instead the
;;; attributes relation-name and inverse-relation-name are shown.  These then
;;; are "controlling" slots, and their values become the primary and secondary
;;; name, respectively, of a relation.
;;;
;;; In 3.0 and 4.0 Rev. 0, relations were not participating in the usual name
;;; conflict handling of automerge due to the fact that the
;;; name-or-names-for-frame slot is not saved in a KB, and the only call to
;;; to record-name-conflict-if-necessary was in the lowest-level slot-reading
;;; code for that slot (in read-frame-for-kb).
;;;
;;; Note that this is not the only class that does not use an attribute
;;; explicitly named NAMES to determine name conflict: function and procedure are
;;; two others.  So it would not be a the right thing to say, "well, we only handle
;;; the NAMES attribute, and absolutely nothing else, so we'll ignore this".
;;;
;;; There are a various ways in which the user is aware of these being names: both
;;; can be used to refer to the item, e.g., in a move or show action, as well as
;;; of course in a relation establishing or breaking operation requiring the name
;;; of a relation.  In the relation-name case, but not the inverse-relation-name
;;; case, the name box shows the name of the slot.  (It could be counted as a
;;; usability problem or anomoly that it only shows up in the one case, but not
;;; the other, enforcing a kind of asymmetry that's necessarily appropriate.)
;;;
;;; So, I'm thinking that the right thing to do would be to tread the two names
;;; that get established just the same way you would treat any other
;;; definitional item with two names.  Implementation-wise this slightly tricky
;;; -- involving a special call to record-name-conflict-if-necessary after the
;;; two controlling slots have been read in.  A bit of a challenge, but I think
;;; the documentation can be clear, and it can make intuitive sense, at least as
;;; much as any other automerge rule.
;;;
;;; The change is planned for 4.0 Rev. 1, and is submitted as a bug fix, rather
;;; than a change in spec, based on the arguments above that this is the proper
;;; interpretation of the spec. (MHD 7/28/95)
;;;
;;; 
;;;    units-of-measure-declaration		named
;;;    external-simulation-definition		named
;;;    foreign-function-declaration		named
;;;    remote-procedure-declaration		named
;;;
;;;
;;; Classes whose instances to preserve when there is a conflict:
;;;
;;;    rule                                     NOTE: these typically don't have names;
;;;                                             it might be nice to treat these like
;;;                                             procedures if they're named.  Another
;;;                                             thing you could do is treat two rules
;;;                                             as duplicates if they have the same
;;;                                             antecedant, options, focal category,
;;;                                             and focal class.  No, you can't do
;;;                                             this!  What if they're on different
;;;                                             workspaces, in different workspace
;;;                                             hierarchies and get activated at
;;;                                             different times based on their superior
;;;                                             item(s).  Too hard!!
;;;    generic-simulation-formula		NOTE: for both generic simulation formulas
;;;    						and formulas, you could regard two as
;;;    						duplicates if they pertain to the same
;;;						thing.  Consider using this approach
;;;						and thereby put them in the
;;;						same category as procedures.
;;;    generic-formula
;;;    user-menu-choice
;;;
;;;
;;;    language-translation			Note -- earlier we thought of putting
;;;                                             these in the other list, but these are
;;;                                             not typically unnamed and apply to whole
;;;                                             sets of things -- one or more, but not
;;;                                             necessarily all elements, may conflict.  
;;;    						A possible alternative solution is: if
;;;    						they both translate for the same language,
;;;    						and for the same set of menu choices,
;;;    						then regard them as duplicates.  OR,
;;;    						if they happen to be named, regard them
;;;    						as duplicates.
;;;
;;;
;;; Handling Definition Objects (i.e., message-, connection-, and object-definitions)
;;;
;;;
;;;
;;; Philosophy:
;;;   a. Change the picture, but don't change the meaning.  E.g., update
;;;   the icon description, but don't update the stubs.  Example KB: Diagnostic
;;;   Assistant.
;;;
;;;   
;;; Principles
;;;
;;; 1. Always update the following attributes in existing instances:
;;;
;;;    icon-description			(object definitions only)
;;;
;;; 2. Never update the following attributes in existing instances:
;;;
;;;    default-settings         	(object definitions only)
;;;    stubs				(object definitions only)
;;;    
;;;    default-message-properties	(message definitions only)
;;;
;;;    [The following were moved here by DWR -- "the only one you should
;;;    change, I think, is Icon Description" --DWR, 7/19/91]
;;;    
;;;    stub-length                   	(connection definitions only)
;;;    cross-section-pattern		(connection definitions only)
;;;
;;; NOTE: To update the instances means to make the instances reflect
;;; their (new) definition in addition to changing the definition.

;; What was I trying to say here? (MHD):
;; NOTE: The this is, 1/2 are unnecessary, since the only element in 1
;; is icon-description, and that element is always reflected in instances.
;; Hmmmmmm.

;;; 
;;; 3. Handle attributes-specific-to-class according to the following guidelines:
;;;
;;;    (3.1) User begins by loading a later rev of some KB.
;;;    
;;;    (3.2) User continues by auto-merging an earlier rev of the same KB.
;;;
;;; [New for 4.0:
;;;
;;;    (2.5) Automerge attributes-specific-to-class BEFORE dealing with
;;;           direct-superior-classes.  This introduces another ordering
;;;           dependency.  It is still loosely compatible with the notion
;;;           that users could "do this all themselves via hand-editing",
;;;           since they're themselves free to edit the attributes before
;;;           they edit the superior class(es).  Note that this fixes the
;;;           problem that arises under following kind of scenario:
;;;
;;;             create a KB, t1.kb, with class A defined with attribute ID,
;;;             and class B defined with superior class A.  Create another
;;;             KB, t2.kb, with class A defined with no attributes, and class
;;;             B defined with suerior class A still but now itself defining
;;;             attribute ID.
;;;
;;;             Load t2.kb, and then automerge t1.kb.
;;;
;;;           Enforcing this order will allow non-default values of ID in
;;;           instances to be preserved.
;;;
;;;           If the opposite order happened to be taken (as it did in practice
;;;           previously), then the ID slot would disappear when B-FROM-T1
;;;           changed its superior from A-FROM-T1 to A.  It's true that it would
;;;           be regained upon copying the attributes from B over to B-FROM-T1,
;;;           but by that time, the non-default values in instances of B-FROM-T1
;;;           would have already been lost.
;;;
;;; STILL NEEDS TO BE IMPLEMENTED!
;;; (MHD 10/5/94)
;;; ]
;;;           
;;;    
;;;    (3.3) Keep the attributes that are in the later rev of the KB but
;;;          not in the earlier rev.  Remove the attributes that are
;;;          in the earlier rev but not in the later rev.  (Ignore differences
;;;          in the ordering of the attributes within the attributes-specific-
;;;          to-class slot -- regard this as a set.)
;;;
;;;    (3.4) If the attribute exists in both the later and earlier rev, then
;;;          perform according to the following rules:
;;;          
;;;          (a) When changing from a variable/parameter to a constant:
;;;          
;;;                1. Replace the attribute with a constant in all instances
;;;                2. If the variable/parameter specified by the earlier
;;;                   definition has an initial value, then change the
;;;                   value of the constants in the instances to that
;;;                   initial value.
;;;                3. Use the default value specified in the later definition
;;;                   if it is specified, e.g., my-attribute is 3.4.
;;;                4. Just use whatever default value would normally be
;;;                   used in newly created instances -- i.e., G2 displays
;;;                   NONE on attribute tables for that attribute.
;;;                   
;;;          (b) When changing from a constant to a variable/parameter:
;;;          
;;;                 Place the constant value in each instance as the initial
;;;                 value of the variable/parameter.
;;;
;;; PROBLEM: A principle of all of this is that nothing is being done that the
;;; user could not do by hand -- (a) and (b) above appear to violate that, unless
;;; you consider that the user could find every instance and do the edits by
;;; hand; that is, there is no "change" grammar for effecting changes according
;;; to the above spec. (MHD 7/24/91)
;;;
;;;          (c) When changing an attribute to be "indexed", reindex all the
;;;              instances.  Note that if the type changes and the attribute
;;;              is indexed, reindexing is also necessary.
;;;              
;;;          (d) When changing a constant from one value to another value,
;;;              preserve existing instances' value as is unless they are
;;;              the same as the default.
;;;              
;;;          (e) Always update all instances UNLESS
;;;          
;;;              i. minor type change ONLY (e.g., quantitative-parameter to
;;;                 integer-parameter) [WHY???? (Ask Eric!) --DWR]; or
;;;             ii. value change only (for constants) [WHY???? Contradicts
;;;                 what (d), above, says! (Ask Eric!) -- DWR]; or
;;;            iii. no value or type change. [I.e., if there's nothing to
;;;                 change, don't change anything -- "kind of a pointless
;;;                 statement" --DWR]

;;; Comments, Problems, Notes, etc.
;;;
;;; PROBLEM: what about user-defined classes of objects, messages,
;;; connections (?!); should they be subject to an automatic delete
;;; action where "everything" is the same (i.e., name, class,
;;; attributes)??
;;;
;;; PROBLEM: How can you do this while paused?  It's problematic because
;;; at least because of indexing, if not for other reasongs.  [I could
;;; see not allowing merge, or at least auto-merge, while paused. --MHD]
;;; [Merge is used for other things while paused; so let's allow merge,
;;; but not auto-merge while paused.  --MHD/DWR]
;;;
;;; NOTE: In all versions of merge so far, G2 would consider two object
;;; definitions to be different if they contained the same set of attributes
;;; but just in a different order.  The only thing the order defines is
;;; the appearance in the attribute table.  This may be a bit disappointing
;;; for users.  (If you do regard the ordering as an important thing, 
;;; notice below that we are giving up worrying about it, and weep.)
;;;
;;; PROBLEM: When slots go away or are added, attribute tables (query
;;; tables and attibute displays, too), should reflect the change -- they
;;; don't now.  This has always been a problem, but now it gets worse.
;;; 
;;;
;;; CONSIDER:  Always regard same-named things of the same class (except
;;; connection posts??) as duplicates, & replace old same-named thing with
;;; new in auto-merge.  Then, they can have a very simple definition of
;;; automerge and how it works instead of having to read a table.  Maybe
;;; only do this for G2-defined classes? (e.g., procedures, rules, etc.)



;;; A `record of class name conflicts' is a list of the form
;;;
;;;    (frame-reference-serial-number . class-name-conflicts)
;;;
;;; where frame-reference-serial-number is the current frame serial number
;;; at the time of the creation of the record, and class-name-conflicts is a list
;;; of class name conflicts.

;;; The kb-specific variable `record-of-class-name-conflicts?' is either nil,
;;; or, if the current KB was created via a merge with the variable record-class-
;;; name-conflicts? true, a record of class name conflicts, each class name conflict
;;; of which is of the form
;;;
;;;	(class new-name old-definition new-definition ({differing-slot}+))
;;;
;;;
;;; Its value gets reclaimed (via reclaim-slot-value-tree) and reset to nil
;;; upon creation of a new KB.  
;;;
;;; Reclaiming is now via reclaim-class-name-conflicts (below) so that the frame serial number
;;; gets reclaimed -alatto, 4/7/99

(defun reclaim-class-name-conflicts (conflicts)
  (when conflicts
    (reclaim-slot-value (cdr conflicts))
    (reclaim-frame-serial-number (car conflicts))
    (reclaim-slot-value-cons conflicts)))
  
(def-kb-specific-variable record-of-class-name-conflicts? kb-merge nil
  nil reclaim-class-name-conflicts)


;;; Record-class-name-conflicts is to be called with class-name-conflicts, a slot
;;; value tree of class name conflicts.  It sets the variable record-of-class-name-
;;; conflicts?, after reclaiming its previous value, if any.

(defun record-class-name-conflicts (class-name-conflicts)
  (when record-of-class-name-conflicts?
    (reclaim-class-name-conflicts
      (prog1 record-of-class-name-conflicts?
	(setq record-of-class-name-conflicts? nil))))
  (setq record-of-class-name-conflicts?
	(slot-value-cons
	  (copy-frame-serial-number (current-frame-serial-number))
	  class-name-conflicts)))




;;; `Record-class-name-conflict' records one individual class name conflict.  This
;;; adds to the variable class-name-conflicts at the beginning, and it is called in the
;;; order of arriving classes, which must be in top-down order.  Thus, when this list is
;;; complete, it is the reverse of top-down class-hierarchy order.
;;;
;;; (For very old KBs, this order is not guaranteed -- a bug for 1.11B KBs.)
;;;
;;; (NOTE: In G2 4.0 Beta Rev 24 and earlier versions, we did not particularly
;;; rely on the order of this list.  The new attribute-moving prepass feature of
;;; automerge that causes some attributes to be moved, using the new
;;; move-attribute feature, requires a well-specified order, in particular a
;;; top-down ordering.  It is not timely to change the order for Automerge
;;; generally, so the attribute-moving prepass will copy the list in reverse
;;; order.)

(defun record-class-name-conflict
    (class new-name? old-class-definition? new-class-definition
	   denotations-of-differing-slots &optional ghost-definition-p)
  #+development
  (test-assertion
    (or (not ghost-definition-p)
	(null (superblock? new-class-definition))))
  (slot-value-push
    (slot-value-list
      class
      new-name?
      old-class-definition?
      new-class-definition
      denotations-of-differing-slots
      ghost-definition-p)
    class-name-conflicts))

;; TO BE MOVED ASAP TO KB-MERGE!! (MHD 10/7/94)




;;; Currently-automatically-resolving-class-name-conflicts?  is bound to nil
;;; globally, but it is rebound to non-nil within resolve-class-name-conflicts.
;;; This just serves to suppress messages that users should only see when
;;; intereractively resolving conflicts by hand.  

(defvar currently-automatically-resolving-class-name-conflicts? nil)



;;; The function `transfer-values-to-interim-class-definition-for-merge'
;;; unpacks the information contained in an object or message or connection
;;; definition and puts it into a newly allocated class-definition.  The
;;; object/message/connection defintion will have copies of the slot values
;;; it originally had.  The instances and class-description are transferred
;;; to the class-definition.
;;;
;;; This is a helper function to the merge code in combine-class-definitions,
;;; resolve-class-name-conflicts, the change attribute, and alter-inheritance-
;;; of-class-without-changing-foundation-class.  This code makes it possible to
;;; merge a class defined with an object/message/connection definition into a
;;; class defined with a class-definition.
  
(defun transfer-values-to-interim-class-definition-for-merge
    (interim-class-definition current-definition)
  (let* ((current-definition-class (class current-definition))
	 (current-definition-slot-descriptions
	   (slot-descriptions (class-description-slot current-definition)))
	 (class-name (name-of-defined-class current-definition))
	 (interim-class-definition-class-description-slot
	   (class-description-slot interim-class-definition))
	 (current-attribute-displays-spec?
	   (and (frame-of-class-p current-definition 'object-definition)
		(attribute-displays-spec? current-definition))))

    ;; Clear the incomplete class frame note.
    (change-slot-value interim-class-definition 'frame-status-and-notes nil)
    
    (loop for current-slot-description in current-definition-slot-descriptions
	  for pretty-slot-name = (pretty-slot-name current-slot-description)
          for interim-slot-description? = (get-slot-description-of-class-description
					    pretty-slot-name
					    interim-class-definition-class-description-slot)
	  do
      (when interim-slot-description?
	(case pretty-slot-name
	  ((frame-serial-number class-specific-instances-forward-pointer
				class-specific-instances-reverse-pointer icon-description
				icon-attributes-plist class-description-slot menus-for-this
				original-kb-state-plist lookup-structure frame-representations
				frame-transforms-of-block remembered-block-transform
				unsaved-but-remembered-block-transforms overlapping-blocks-cache
				layer-position-of-block squirreled-data change-log-information
				runtime-structures-affected-by-this-entity
				kb-state-changes-previous-cons?
				subworkspaces)
	   ;;yduj, May 01: shouldn't we be doing something better than just
	   ;;having a list of slots not to copy?  E.g., UUID is not in this
	   ;;list.  Shouldn't it be?  Should we be checking do-not-clone?
	   nil)
	  ((object-configuration direct-superiors-of-defined-class
				 class-specific-attributes instance-configuration
				 instantiate? include-in-menus? frame-flags frame-flags-2)
	   (let ((current-value
		   (get-slot-description-value
		     current-definition current-slot-description)))
	     (set-slot-description-value-without-noting
	       interim-class-definition interim-slot-description?
	       current-value)
	     (set-slot-description-value-without-noting
	       current-definition current-slot-description
	       (copy-for-slot-value current-value))))
	  (slot-group-for-block?
	   (let* ((current-slot-group-for-block
		    (slot-group-for-block? current-definition))
		  (new-current-slot-group-for-block (make-icon-slot-group))
		  (current-subblocks
		    (subblocks-internal current-slot-group-for-block)))
	     (setf (slot-group-for-block? interim-class-definition)
		   current-slot-group-for-block)
	     (setf (slot-group-for-block? current-definition)
		   new-current-slot-group-for-block)
	     (setf (left-edge-internal new-current-slot-group-for-block)
		   (left-edge-internal current-slot-group-for-block))
	     (setf (top-edge-internal new-current-slot-group-for-block)
		   (top-edge-internal current-slot-group-for-block))
	     (setf (right-edge-internal new-current-slot-group-for-block)
		   (right-edge-internal current-slot-group-for-block))
	     (setf (bottom-edge-internal new-current-slot-group-for-block)
		   (bottom-edge-internal current-slot-group-for-block))
	     (setf (superblock?-internal new-current-slot-group-for-block)
		   (superblock?-internal current-slot-group-for-block))
	     (when (superblock?-internal current-slot-group-for-block)
	       (add-subblock
		 interim-class-definition
		 (superblock?-internal current-slot-group-for-block)))
	     #-subblocks-v2
	     (loop for subblock in current-subblocks
		do (set-superblock-and-faction
		    subblock interim-class-definition))
	     #+subblocks-v2
	     (when current-subblocks
	       (loop for subblock being each constant-queue-element of current-subblocks
		  do (set-superblock-and-faction
		      subblock interim-class-definition)))
	     (setf (subblocks-internal new-current-slot-group-for-block) nil)
	     (setf (connections-internal new-current-slot-group-for-block) nil)))
	  (default-overrides
	      (let ((current-default-overrides?
		      (default-overrides current-definition)))
		(cond
		  ((frame-of-class-p current-definition 'object-definition)
		   (let ((stubs? (connections-for-class? current-definition)))
		     (setf (default-overrides interim-class-definition)
			   (if (or current-attribute-displays-spec? stubs?)
			       (nconc
				 current-default-overrides?
				 (when current-attribute-displays-spec?
				   (slot-value-list
				     (slot-value-list
				       'attribute-displays-for-class
				       current-attribute-displays-spec?)))
				 (when stubs?
				   (slot-value-list
				     (slot-value-list
				       'stubs-for-class stubs?))))
			       current-default-overrides?))
		     (setf (connections-for-class? current-definition)
			   (copy-for-slot-value stubs?))
		     (setf (attribute-displays-spec? current-definition)
			   (copy-for-slot-value current-attribute-displays-spec?))))
		  ((subclassp current-definition-class 'connection-definition)
		   (let ((cross-section-pattern?
			   (cross-section-pattern-for-connection
			     current-definition))
			 (stub-length?
			   (stub-length-for-connection current-definition))
			 (junction-block?
			   (junction-block-class-for-connection
			     current-definition)))
		     (setf (default-overrides interim-class-definition)
			   (if (or cross-section-pattern? stub-length?
				   junction-block?)
			       (nconc
				 current-default-overrides?
				 (when cross-section-pattern?
				   (slot-value-list
				     (slot-value-list
				       'cross-section-pattern-for-class
				       cross-section-pattern?)))
				 (when stub-length?
				   (slot-value-list
				     (slot-value-list
				       'stub-length-for-class stub-length?)))
				 (when junction-block?
				   (slot-value-list
				     (slot-value-list
				       'junction-block-class-for-class
				       junction-block?))))
			       current-default-overrides?))
		     (setf (cross-section-pattern-for-connection
			     current-definition)
			   (copy-for-slot-value cross-section-pattern?))
		     (setf (stub-length-for-connection current-definition)
			   (copy-for-slot-value stub-length?))
		     (setf (junction-block-class-for-connection current-definition)
			   (copy-for-slot-value junction-block?))))

		  (t ; message-definition
		   (let ((default-message-properties?
			     (default-message-properties current-definition)))
		     (setf (default-overrides interim-class-definition) 
			   (if default-message-properties?
			       (nconc
				 current-default-overrides?
				 (slot-value-list
				   (slot-value-list
				     'default-message-properties-for-class
				     default-message-properties?)))
			       current-default-overrides?))
		     (setf (default-message-properties current-definition)
			   (copy-for-slot-value default-message-properties?)))))
		(setf (default-overrides current-definition)
		      (copy-for-slot-value current-default-overrides?))))
	  (t
	   (let ((current-value
		   (get-slot-description-value
		     current-definition current-slot-description)))
	     (set-slot-description-value-without-noting
	       interim-class-definition interim-slot-description?
	       current-value)
	     (if currently-automatically-resolving-class-name-conflicts?
		 (set-slot-description-value-without-noting
		   current-definition current-slot-description
		   (slot-init-form current-slot-description))
		 (set-slot-description-value-without-noting
		   current-definition current-slot-description
		   (copy-for-slot-value current-value))))))))
    (setf (class-definition class-name) interim-class-definition)))

      
;;; `reorder-class-name-conflicts-with-referenced-slots-first' takes as its
;;; single argument, conflicts, the current value of
;;; record-of-class-name-conflicts?, which is a slot-value list whose car is a
;;; frame-serial number, and whose cdr is a list of class name conflicts (see
;;; the entry "class name conflicts" at the top of this file for details on the
;;; format and structure of class name conflicts).  It returns a reordered
;;; version of this list, if possible, otherwise nil.

;;; The reordered version follows the existing rule that subclasses always occur
;;; before their superclasses, and the added constraint that if X and Y are
;;; classes for which there are conflicts, and an attribute in class X is
;;; constrained to be of type (class Y), then the class-name-conflict for Y
;;; occurs before the class-name-conflict for X in the list.  If a slot in class
;;; X is constrained to be of type class Y, it's important that we resolve any
;;; conflict in class Y before we resolve any conflict in class X. Otherwise,
;;; when we change instances to be instances of X, instead of X-from-foo, we
;;; will notice that the contents of the slot is of type Y-from-foo, when it is
;;; constrained to be of type Y.  This will result in the subtable containing
;;; the instance of Y-from-foo (and any subtables and subworkspaces it has,
;;; containing potentially irrecoverable data) being deleted. While reordering
;;; the conflicts, we retain the constraint that subclass conflicts are resolved
;;; before superclasses, and we otherwise make an effort not to gratuitously
;;; perturb the existing order, to avoid unintended consequences. If there is no
;;; such reordering possible, (for example, if X contains an attribute
;;; constrained to be of type class Y, while Y contains an attribute constrained
;;; to be of type class X), we return nil. This fixes bug HQ-4541449 "Suggestion
;;; for change to auto-conflict resolution to first address leaf nodes" -alatto,
;;; 11/16/05

;;; Note that if the new constraint is impossible to meet due to a resulting
;;; circularity of constraints, we use the old unmodified order, rather than
;;; attempting to modify the order to meet the new constraint as often as possible.
;;; So in obscure cases, unnecessary deletion may still occur. This is bug
;;; HQ-5156447 "auto-conflict-resolution sometimes uses an inappropriate resolution order."

;;; To accomplish the reordering, we do a topological sort of the conflicts.
;;; To do this, we build up two data structures. One is a list that for each
;;; conflict, consists of
;;; (conflict-info number-of-predecessors . list-of-successors)
;;; The other is the subset of this list where number-of-predecessors is 0.
;;; We then loop, moving one class at a time from the number-of-predecessors-is-0
;;; list to the final list, and decrementing the number-of-predecessors for
;;; each of its ancestors, placing the result on the list of
;;; items-with-zero-predecessors when appropriate.

;;; From a conflict entry, it's easy to find the name of any class that must be
;;; a predecessor. To find the corresponding conflict entry quickly, We build up
;;; a hash table of conflict entries indexed by class name.

(defun reorder-class-name-conflicts-with-referenced-slots-first (conflicts)
  (let* ((result nil)
         (conflicts-with-predecessors nil)
         (conflicts-ready-to-be-processed nil)
         (conflicts-hash (make-eq-hash-table (length conflicts) nil nil))
	 (fsn (car conflicts))
         (number-of-conflicts 0)
         (number-of-reordered-conflicts 0))
    (loop for conflict in (cdr conflicts) do
      (incff number-of-conflicts)
      (let ((conflict-structure (gensym-list conflict 0)))
	(gensym-push conflict-structure conflicts-with-predecessors)
	(unless (frame-has-been-reprocessed-p (third conflict) fsn)
	  (eq-puthash conflicts-hash (first (first conflict-structure)) conflict-structure))))
    (loop for conflict-structure in conflicts-with-predecessors do
      (let ((definition (third (first conflict-structure))))
	(unless (frame-has-been-reprocessed-p definition fsn)
	  (let ((inheritance-path (class-inheritance-path-of-definition definition)))
	    (loop for class in inheritance-path do
	      (unless (eq class (name-of-defined-class definition))
		(let ((follower? (eq-gethash conflicts-hash class nil)))
		  (when follower?
		    (incff (second follower?))
		    (gensym-push follower? (cddr conflict-structure)))))
	      (let* ((definition (class-definition class))
		     (attribute-descriptions
		       (when (and (framep definition)
				  ;; pretty sure that definition will always
				  ;; be nil, a cons, or a class definition, but
				  ;; checkqing just to be safe.
				  (class-definition-p definition))
			 (class-specific-attributes definition))))
		(loop for attribute-description in attribute-descriptions do
		  (when (class-type-specification-p
			  (attribute-type-specification attribute-description))
		    (let ((preceder? (eq-gethash conflicts-hash
						 (type-specification-class
						   (attribute-type-specification
						     attribute-description))
						 nil)))
		      (when preceder?
			(incff (second conflict-structure))
			(gensym-push conflict-structure (cddr preceder?))))))))))))
    (loop for conflict-structure in conflicts-with-predecessors do
      (when (=f (second conflict-structure) 0)
        (gensym-push conflict-structure conflicts-ready-to-be-processed)))
    ;; process unconstrained conflicts in the order in which they are put on the
    ;; ready-to-be-processed list, which is the order in which they
    ;; originally appeared. This perturbs the order as little as
    ;; possible, in particular keeping the order unchanged if there are no
    ;; ordering constraints.
    (setq conflicts-ready-to-be-processed (nreverse conflicts-ready-to-be-processed))
    (reclaim-eq-hash-table conflicts-hash)
    (loop do
      (when (null conflicts-ready-to-be-processed)
        (loop-finish))
      (incff number-of-reordered-conflicts)
      (let ((next (gensym-pop conflicts-ready-to-be-processed)))
        (slot-value-push (car next) result)
        (loop for follower in (cddr next) do
          (decff (second follower))
          (when (=f (second follower) 0)
            (gensym-push follower conflicts-ready-to-be-processed)))))
    (loop for conflict-structure in conflicts-with-predecessors do
      (reclaim-gensym-list conflict-structure))
    (reclaim-gensym-list conflicts-with-predecessors)
    (if (=f number-of-conflicts number-of-reordered-conflicts)
        (slot-value-cons (car conflicts) (nreverse result))
        (progn (reclaim-slot-value-list result)
               nil))))
  
;;; Resolve-class-name-conflicts ... this is only to be called after workspace
;;; tampering has been checked; specifically, the "old-algorithm?" arg to
;;; create-class-definition-conflict-workspace is always false.

(defun resolve-class-name-conflicts ()
  (when record-of-class-name-conflicts?
    (let ((reordered-class-name-conflicts
            (reorder-class-name-conflicts-with-referenced-slots-first
              record-of-class-name-conflicts?)))
      (if reordered-class-name-conflicts
          (progn
            (reclaim-slot-value-list record-of-class-name-conflicts?)
            (setq record-of-class-name-conflicts?
                  reordered-class-name-conflicts))
          #+development
          (warn "Unable to safely reorder class name conflicts in module ~S: subtables of type-constrained slots may be gratuitously deleted"
                  name-of-kb-being-read)))
    (loop with do-not-note-permanent-changes-p = t
	  with number-of-conflicts = 0
	  with (reference-frame-serial-number . class-name-conflicts)
	    = record-of-class-name-conflicts?
	  with currently-automatically-resolving-class-name-conflicts?
	    = t
	  for class-name-conflict in class-name-conflicts
	  for class = (first class-name-conflict)
	  for new-name = (second class-name-conflict)
	  for old-class-definition = (third class-name-conflict)
	  for new-class-definition = (fourth class-name-conflict)
	  for denotations-of-differing-slots = (fifth class-name-conflict)
	  do
      (unless (or (frame-has-been-reprocessed-p
		    old-class-definition reference-frame-serial-number)
		  (frame-has-been-reprocessed-p
		    new-class-definition reference-frame-serial-number))
	;; When new-definition is a subclass of an object-definition or a subclass
	;; of a connection-definition or a subclass of a connection-definition,
	;; but old-class-definition is not a subclass of the any of the three
	;; inferior-classes of class-definition, a class-definition is created
	;; and the slot values from the new-class-definition are transferred to
	;; it before attempting a merge.
	(cond ((and (not (definition-class-is-subclass-of-obj-conn-mess-definition-p
			     old-class-definition))
		    (definition-class-is-subclass-of-obj-conn-mess-definition-p
			new-class-definition))
	       (cond
		 ;; Passes the compiler for the direct-superiors-of-defined-class slot.
		 ;; The class should merge successfully.
		 ((inheritance-for-merge-is-acceptable-p
		    new-class-definition old-class-definition)
		  ;; Merging into a class-definition.
		  (let ((interim-class-definition (make-frame 'class-definition)))
		    ;; After this call, the new-class-definition will have no name.
		    (transfer-values-to-interim-class-definition-for-merge
		      interim-class-definition new-class-definition)
		    (setf (fourth class-name-conflict) interim-class-definition)
		    (delete-as-frame-with-name new-class-definition new-name)
		    (delete-frame new-class-definition)
		    ;; Resolve-one-class-name-conflict reclaims the interim-class-
		    ;; definition after a successful merge.
		    (let ((successful-resolution?
			    (resolve-one-class-name-conflict
			      old-class-definition interim-class-definition)))
		      (unless successful-resolution?
			#+development
			(cerror
			  "KB-MERGE"
			  "Unfortunate error in resolve-class-name-conflicts -- tell ghw.")
			(incff number-of-conflicts)
			;; Should we get here, the user will be left with a conflict-
			;; workspace that contains the interim-class-definition
			;; instead of the new-class-definition.
			(create-class-definition-conflict-workspace
			  class new-name old-class-definition interim-class-definition
			  (slot-value-list 'direct-superiors-of-defined-class))))))
		 (t
		  ;; Can't do the mixed-class definition merge because the
		  ;; compiler rejected the direct-superior classes.
		  (incff number-of-conflicts)
		  (create-class-definition-conflict-workspace
		    class new-name old-class-definition new-class-definition
		    (slot-value-list 'direct-superiors-of-defined-class)))))

	      ;; Can't merge a class-definition into a specialized connection.
	      ((and (not (definition-class-is-subclass-of-obj-conn-mess-definition-p
			     new-class-definition))
		    (definition-class-is-subclass-of-obj-conn-mess-definition-p
			old-class-definition))
	       (incff number-of-conflicts)
	       (create-class-definition-conflict-workspace
		 class new-name old-class-definition new-class-definition
		 (slot-value-list 'direct-superiors-of-defined-class)))
	       
	      ;; The definitions are compatible.
	      (t (unless (resolve-one-class-name-conflict
			   old-class-definition new-class-definition)
		   (incff number-of-conflicts)
		   (let ((slots-that-still-have-differences
			   (find-differences-in-frames-if-any
			     old-class-definition new-class-definition nil t)))
		     (create-class-definition-conflict-workspace
		       class new-name
		       old-class-definition new-class-definition
		       slots-that-still-have-differences)
		     (reclaim-slot-value-list slots-that-still-have-differences))))))
      
	  finally
	    (if (>f number-of-conflicts 0)
		(notify-user-of-conflict-report-workspace-creation
		  number-of-conflicts))
	    ;; reclaims conses in class-name-conflicts, too:
	    (record-class-name-conflicts nil)
	    (setq class-name-conflicts nil)
	    (deal-with-backup-definition-workspace-after-automerge))))




;;; `Deal-with-backup-definition-workspace-after-automerge' ... At present, this
;;; simply deletes the backup workspace, if any, if it has no definitions.  It
;;; also resets current-backup-definition-workspace-serial-number? and
;;; current-backup-definition-workspace?  to nil.

(defun deal-with-backup-definition-workspace-after-automerge ()
  (let ((workspace?
	  (if (and current-backup-definition-workspace?
		   (not (frame-has-been-reprocessed-p
			  current-backup-definition-workspace?
			  current-backup-definition-workspace-serial-number?)))
	      current-backup-definition-workspace?)))
    (when (and workspace?
	       (loop for subblock being each subblock of workspace?
		     never (frame-of-class-p subblock 'class-definition)))
      ;; if there's a backup workspace with no definitions, we delete it
      (notify-user-of-conflicts
	"Automatically deleting the backup-definitions workspace ~NF; all ~
         of its definitions were automatically deleted after conflicts ~
         with existing definitions were successfully resolved."
	workspace?)
      (delete-frame workspace?))
    (frame-serial-number-setf current-backup-definition-workspace-serial-number? nil)
    (setq current-backup-definition-workspace? nil)))

;; Ultimately, consider removing the captions, and laying out anew so that empty
;; space is not shown where the old definitions were automerged. (MHD/GHW
;; 6/6/95)
      




;;; Find-definition-conflict-workspace ... is somewhat heuristic and therefore
;;; unable to guarantee that it can find any workspace or a real conflict
;;; workspace; in practice, it should work 99.999% of the time.

;;; One problem that has arisen: if either of the definitions gets deleted, or
;;; anything else deletes the table of one of them, this won't find such a
;;; workspace.  We think this could arise in an automerge case where a backup
;;; definition gets deleted.

(defun find-definition-conflict-workspace (definition-1 definition-2)
  (loop for frame-representation-1
	    in (frame-representations definition-1)
	as workspace-1?
	   = (get-workspace-if-any frame-representation-1)
	thereis
	  (loop for frame-representation-2
		    in (frame-representations definition-2)
		as workspace-2?
		   = (get-workspace-if-any frame-representation-2)
		when (eq workspace-1? workspace-2?)
		  return workspace-1?)))




;;; The function `merge-differing-slots-in-definitions' attempts to change the
;;; values of the slots in new-class-definition to the values those slots have
;;; in the old-class-definition.  It is an error to call this with two
;;; "incompatible" definitions: both old- and new-class-definition must be, and
;;; are assumed to be, compatible (as could be determined by
;;; definition-classes-are-compatible-p).
;;;
;;; This function returns a slot-value-consed list of irreconcilable slot
;;; denotations when it fails in its attempt; otherwise it returns nil,
;;; indicating success.  In addition, the user is notified (via notify-user) of
;;; any slot that cannot be merged.
;;;
;;; This is the first step for merging all instances and subclasses of the class
;;; defined by new-class-definition into the class defined by old-
;;; class-definition.

(defun merge-differing-slots-in-definitions
    (old-class-definition new-class-definition differing-slots)
  (let* ((slot-denotations
	   (sort-list
	     (copy-for-slot-value differing-slots)
	     #'superiors-first-partial-ordering-of-slot-denotations-to-automerge
	     nil))
	 (remaining-differing-slots?
	   (prog1 (merge-differing-slots-in-definitions-1
		    old-class-definition new-class-definition
		    slot-denotations nil)
	     (reclaim-slot-value slot-denotations))))
    (if remaining-differing-slots?
	;; Because one slot-value can effect the value of another slot,
	;; we run through the exercise again, this time with warnings.
	(merge-differing-slots-in-definitions-1 
	  old-class-definition new-class-definition
	  remaining-differing-slots? nil))))



(defun merge-differing-slots-in-definitions-1
    (old-class-definition new-class-definition differing-slots warn-p)
  (loop for slot-denotation in differing-slots
	for class-qualifier? = (class-qualifier slot-denotation)
	for slot-name = (unqualified-name slot-denotation)
	for text-representation-for-slot-value
	    = (let ((write-floats-accurately-p t))
		(make-text-representation-for-slot-value
		  old-class-definition slot-name class-qualifier?))
	for slot-description
	    = (get-slot-description-of-frame
		slot-name new-class-definition class-qualifier?)
	unless (parse-text-for-slot
		 text-representation-for-slot-value
		 new-class-definition slot-description)
	  do (when warn-p
	       (notify-user-of-conflicts
		 "Unable to merge the ~NN attribute between definitions ~NF and ~NF."
		 slot-denotation old-class-definition new-class-definition))
	finally
	  (return 
	    (find-differences-in-frames-if-any
	      old-class-definition new-class-definition nil t))))
			 
			 







;;; Find-complex-differences-in-attribute-specs-if-any creates a slot value list
;;; of all attribute names that are in both old-class-definition and
;;; new-class-definition, and differ in that the initial value for same
;;; attribute is a constant in in one definition, and a subobject in the other,
;;; or [not documented in 3.0] the type of the initial value is different.  Such
;;; a difference can be called a `complex difference'.  In 4.0, this is extended
;;; to ignore specs that have non-general type declarations, i.e., (OR
;;; ITEM-OR-DATUM (NO-ITEM)).

(defun find-complex-differences-in-attribute-specs-if-any
       (old-class-definition new-class-definition)
  (loop with the-most-general-type = '(OR ITEM-OR-DATUM (NO-ITEM))
	with old-attribute-descriptions-for-class
	  = (class-specific-attributes old-class-definition)
	for new-attribute-description
	    in (class-specific-attributes new-class-definition)
	as old-attribute-description?
	   = (loop with new-attribute-name = (attribute-name new-attribute-description)
		   for description in old-attribute-descriptions-for-class
		   when (eq new-attribute-name (attribute-name description))
		     return description)
	when (and old-attribute-description?
		  (equal (attribute-type-specification new-attribute-description)
			 the-most-general-type)
		  (equal (attribute-type-specification old-attribute-description?)
			 the-most-general-type)
		  (and (or (not (slot-value-equal-p
				  (attribute-initial-value
				    old-attribute-description?)
				  (attribute-initial-value
				    new-attribute-description)))
			   (not (equal
				  (attribute-range
				    old-attribute-description?)
				  (attribute-range
				    new-attribute-description))))
		       ;; the attribute-initial-type for a subobject spec is
		       ;; NIL; if at least one of the specs is for a subobject,
		       ;; then a difference in the initial value is always a
		       ;; "complex difference; otherwise, it is only a complex
		       ;; difference if the type is changing, e.g., number ->
		       ;; truth-value, integer-> logical-parameter, etc.  (Note,
		       ;; however, that floats are not differentiated from
		       ;; integers here -- they are all numbers.)
		       (or (null (attribute-initial-type old-attribute-description?))
			   (not (eq
				  (attribute-initial-type old-attribute-description?)
				  (attribute-initial-type new-attribute-description))))))
	  collect (attribute-name new-attribute-description)
	   using slot-value-cons))



;;; `Partial-ordering-of-slot-denotations-to-automerge' is bound to a list of
;;; slot denotations for slots in definitions.  When automerge takes place, this
;;; ordering will partially determine the sequential order in which merging
;;; takes place.
;;;
;;; At present, this enforces just one ordering constraint: that the automerge
;;; of the direct-superiors-of-defined-class slot comes before the class-specific-
;;; attributes slot.

(defparameter partial-ordering-of-slot-denotations-with-superiors-first
  '(direct-superiors-of-defined-class class-specific-attributes))

(defun superiors-first-partial-ordering-of-slot-denotations-to-automerge
    (slot-denotation-1 slot-denotation-2)
  (<f (or (loop with slot-name-1 = (unqualified-name slot-denotation-1)
		for slot-denotation
		    in partial-ordering-of-slot-denotations-with-superiors-first
		as index from 0
		when (eq (unqualified-name slot-denotation) slot-name-1)
		  return index)
	  0)
      (or (loop with slot-name-2 = (unqualified-name slot-denotation-2)
		for slot-denotation
		    in partial-ordering-of-slot-denotations-with-superiors-first
		as index from 0
		when (eq (unqualified-name slot-denotation) slot-name-2)
		  return index)
	  0)))




;;; The function `get-slot-values-to-save-for-conflict-resolution' makes a list
;;; of the non-default slot values that will be lost during automerge in order
;;; to reinstate them after automerge has been completed on a class.  This only
;;; applies to default slot-descriptions.

;;; The problem this function adresses is that non-default slot-values can be
;;; lost whether we resolve the differences in the direct-superiors-of-defined-
;;; class slots first or we resolve the differences in the class-specific-
;;; attributes slot first.  Now we pick one slot to be resolved first --
;;; arbitrarily picking the direct-superiors-of-defined-class slot -- and deal
;;; with the remaining slot-value problems.

(defun get-slot-values-to-save-for-conflict-resolution
    (old-class-definition new-class-definition)
  (let* ((new-class (name-of-defined-class new-class-definition))
	 (new-class-class-description (class-description new-class))
	 (old-class (name-of-defined-class old-class-definition))
	 (old-class-class-description (class-description old-class))
	 (value-to-return? nil))
    (loop for new-slot-description in (slot-descriptions
					new-class-class-description)
	  do
      (when (and (user-defined-slot-description-p new-slot-description)
		 (not (slot-name-needs-qualification-p
			new-slot-description new-class-class-description)))
	(let ((old-slot-description?
		(get-slot-description-of-class-description
		  (pretty-slot-name new-slot-description)
		  old-class-class-description)))
	  (when old-slot-description?
	    (let* ((losing-slot-temporarily?
		     (and (eq (defining-class old-slot-description?) old-class)
			  (neq (defining-class new-slot-description) new-class)))
		   (gaining-slot-temporarily?
		     (and (eq (defining-class new-slot-description) new-class)
			  (neq (defining-class old-slot-description?) old-class)))
		   (defining-class-for-slot-description-to-set?
		     (if losing-slot-temporarily?
			 old-class
			 (when gaining-slot-temporarily?
			   (defining-class old-slot-description?))))
		   (instances-and-slot-values-list?
		     (when defining-class-for-slot-description-to-set?
		       (loop with pretty-slot-name = (pretty-slot-name
						       new-slot-description)
			     with defining-class = (defining-class
						       new-slot-description)
			     with old-type-specification = (slot-type-specification
							     old-slot-description?)
			     for class being each subclass of new-class
			     for class-description = (class-description class)
			     for class-slot-description
				 = (if (eq class new-class)
				       new-slot-description
				       (get-slot-description-of-class-description
					 pretty-slot-name class-description defining-class))
			     for new-slot-init-form = (slot-init-form class-slot-description)
			     for user-vector-slot-index? = (user-vector-slot-index?
							     class-slot-description)
			     nconc
			     (loop for instance being each strict-class-instance of class
				   for current-slot-value = (get-slot-description-value
							      instance class-slot-description)
				   when (and (not (eq current-slot-value new-slot-init-form))
					     (slot-value-conforms-to-type-specification-p
					       current-slot-value old-type-specification))
				     ;; the current slot-value is non-default, and will
				     ;; conform to the future type specification
				     collect
				     (prog1 (let ((attribute-table-display?
						    (loop for subblock being each
							  subblock of instance
							  thereis
							  (and
							    (table-p subblock)
							    (attribute-display-p subblock)
							    (get-text-cell-representing-slot-if-any
							      subblock instance pretty-slot-name
							      nil)))))
					      (frame-list
						instance
						current-slot-value attribute-table-display?))
				       (setf (svref (lookup-structure instance)
						    user-vector-slot-index?)
					     nil))
				       using frame-cons)))))
	      (when instances-and-slot-values-list?
		(setq value-to-return?
		      (nconc
			value-to-return?
			(frame-list
			  (nconc
			    (frame-list (pretty-slot-name new-slot-description)
					defining-class-for-slot-description-to-set?)
			    (frame-list instances-and-slot-values-list?)))))))))))
    value-to-return?))

(defun reinstate-non-default-values-after-merge (preserved-non-default-values)
  (loop while preserved-non-default-values
	for attribute-information = (frame-pop preserved-non-default-values)
	for pretty-slot-name = (frame-pop attribute-information)
	for defining-class = (frame-pop attribute-information)
	for list-of-instances-and-values = (frame-pop attribute-information)
	do
    (loop while list-of-instances-and-values
	  for instance-and-values = (frame-pop list-of-instances-and-values)
	  for instance = (frame-pop instance-and-values)
	  for slot-value = (frame-pop instance-and-values)
	  for attribute-display? = (frame-pop instance-and-values)
	  for class-description-slot = (class-description-slot
					 instance)
	  for slot-description
	      = (get-slot-description-of-class-description
		  pretty-slot-name class-description-slot
		  defining-class)
	  do
      (change-slot-description-value
	instance slot-description slot-value)
      (when attribute-display?
	(unless (loop for subblock being each subblock of instance
		      thereis
		      (and (table-p subblock)
			   (attribute-display-p subblock)
			   (get-text-cell-representing-slot-if-any
			     subblock instance pretty-slot-name
			     nil)))
	  (add-slot-representation-as-attribute-display
	    instance pretty-slot-name defining-class))))))


			 
			 
;;; The function, `resolve-one-class-name-conflict' returns true if successful;
;;; null otherwise.

;;; Old-class-definition is from a priorly-loaded module, new-class-definition is
;;; from the module that has just been loaded.

;;; When both definitions define classes, this function attempts to resolve
;;; their slot differences and merge the instances and subclasses, if any, of
;;; the class defined by new-class-definition into the class defined by
;;; old-class-definition.  When either of these operations is unsuccessful, the
;;; attribute-tables of the definitions will appear on a conflict workspace with
;;; their slot differences highlighted.
;;;
;;; In the case where the new-class-definition does not define a class, new-class
;;; definition is deleted in favor of old-class-definition (which may or may not
;;; define a class) and true is returned.

;;; When old-class-definition defines a class but old-class-definition does not,
;;; no attempt is made to merge the classes.  Nil is returned and the definitions
;;; will appear on a class-conflict workspace.

(defun-allowing-unwind resolve-one-class-name-conflict
    (old-class-definition new-class-definition)
  
  (let* ((definition-classes-are-compatible?
	    (definition-classes-are-compatible-p
		old-class-definition new-class-definition))
	 (old-definition-class-name (name-of-defined-class old-class-definition))
	 (new-definition-class-name (name-of-defined-class new-class-definition))
	 (old-definition-defines-class? (classp old-definition-class-name))
	 (new-definition-defines-class? (classp new-definition-class-name))
	 (both-definitions-define-classes?
	   (and old-definition-defines-class? new-definition-defines-class?)))

    (cond
      (both-definitions-define-classes?
       (protected-let ((denotations-of-differing-slots
			 (find-differences-in-frames-if-any
			   old-class-definition new-class-definition
			   nil definition-classes-are-compatible?)
			 (reclaim-slot-value denotations-of-differing-slots)))
	 (cond ((equal denotations-of-differing-slots '(class))
		(notify-user-of-conflicts
		  "Warning: the attempt failed to automatically resolve ~
                   the old and new definitions, ~NF and ~NF because they ~
                   are not of compatible classes.  Neither definition will be deleted."
		  old-class-definition new-class-definition)
		nil)
	       (t
		(protected-let
		    ((preserved-non-default-values?
		       (when (and (memq 'class-specific-attributes
					denotations-of-differing-slots)
				  (memq 'direct-superiors-of-defined-class
					denotations-of-differing-slots))
			 (get-slot-values-to-save-for-conflict-resolution
			   old-class-definition new-class-definition)))
		     (irreconcilable-slots?
		       (merge-differing-slots-in-definitions
			 old-class-definition new-class-definition
			 denotations-of-differing-slots)
		       (reclaim-slot-value irreconcilable-slots?)))
		  (cond
		    (irreconcilable-slots?
		     (highlight-differing-slots-in-definitions
		       old-class-definition new-class-definition
		       irreconcilable-slots?)
		     (notify-user-of-conflicts
		       "Warning: the attempt failed to automatically resolve ~
                        the old and new definitions, ~NF and ~NF; they ~
                        still differ in ~d slots!  So neither definition will be deleted."
		       old-class-definition new-class-definition
		       (length irreconcilable-slots?))
		     nil)
		    (t
		     (let ((successful-resolution?
			     (resolve-by-merging-all-instances
			       old-definition-class-name new-class-definition
			       new-definition-class-name)))
		       (cond
			 (successful-resolution?
			  ;; Now delete new-class-definition which could contain
			  ;; a subworkspace that will be deleted (a hazard of automerging).
			  (let ((class-name-conflict-workspace?
				  (get-instance-with-name-if-any
				    'kb-workspace
				    (make-name-for-class-name-conflict-workspace
				      old-definition-class-name))))
			    (notify-user-of-conflicts
			      "Automatically deleting definition ~NF, whose instances, ~
                                   if any, were merged into the class defined by ~NF."
			      new-class-definition old-class-definition)
			    (delete-frame new-class-definition)
			    (when (and class-name-conflict-workspace?
				       (eq class-name-conflict-workspace?
					   (find-definition-conflict-workspace
					     old-class-definition
					     new-class-definition)))
			      (notify-user-of-conflicts
				"Automatically deleting conflict workspace ~NF."
				class-name-conflict-workspace?)
			      (delete-frame class-name-conflict-workspace?)))
			  (when preserved-non-default-values?
			    (reinstate-non-default-values-after-merge
			      preserved-non-default-values?))
			  t)
			 ;; The merge attempt failed.
			 (t
			  (notify-user-of-conflicts
			    "Warning: Final attempt to merge ~NF with ~NF failed!"
			    old-class-definition new-class-definition)
			  nil))))))))))
      ;; Old-class-definition may or may not define a class.
      ((null new-definition-defines-class?)
       (notify-user-of-conflicts
	 "Automatically deleting the incomplete class-definition ~NF in favor of ~
          the class-definition ~NF from a required module."
	 new-class-definition old-class-definition)
       (delete-frame new-class-definition)
       t)
      ;; The t case is when the new-class-definition defines a class, but the
      ;; old-class-definition does not.  This will be brought to user attention.
      (t nil))))



;;; The function `resolve-by-merging-all-instances' is a subfunction of
;;; resolve-one-class-name-conflict. It uses the change attribute of definition
;;; to do the equivalent of the user entering
;;;
;;;   MERGE ALL INSTANCES AND SUBCLASSES INTO DEFINITION FOR old-name
;;;
;;; where definition has the name (and defines the class) old-name.  If this
;;; change, is successful in transitioning the instances (leaving this the class
;;; old-name uninstantated), this function returns true; otherwise, it returns
;;; nil.

(defun resolve-by-merging-all-instances (old-name definition new-name)
  (and (parse-text-for-slot
	 (convert-text-string-to-text
	   (tformat-text-string
	     "merge all instances and subclasses into definition for ~a"
	     old-name))
	 definition
	 (get-slot-description-of-frame 'change definition 'class-definition))
       (not (instantiated-class-p new-name))))

;; Note: the change slot detects a limited subset of all possible change
;; failures. If the change look successful after parse-text-for-slot, it's still
;; not necessarily successful (HQ-4433924 "G2 aborts with an inspect after
;; manually deleting a module from G2"). So the additional test for instantiated
;; instances is still necessary.  It would probably be a lot of work to fix
;; change to always catch the full set of possible failures, and thus give a
;; perfect answer.  (MHD 11/12/02)



;;; Highlight-differing-slots-in-definitions ...

(defun highlight-differing-slots-in-definitions
       (class-definition-1 class-definition-2 differing-slots)  
  (loop for slot-denotation in differing-slots
	as class-qualifier? = (class-qualifier slot-denotation)
	as slot-name = (unqualified-name slot-denotation)
	do (highlight-or-unhighlight-for-slot
	     class-definition-1 slot-name class-qualifier? nil nil)
	   (highlight-or-unhighlight-for-slot
	     class-definition-2 slot-name class-qualifier? nil nil)))

;; Fix caller to send in "denotations" of slots!





;;;; Definitional Classes


;;; A `definitional class' is either a rule or any class that appears in the
;;; new-definition menu except for the subclasses of the class-definition.
;;; For example, procedure, rule, and user-menu-choice are all examples of
;;; definitional classes.

;;; A `definitional item' is an instance of a definitional class.

;;; A `definitional name conflict' is a name conflict, when merging a KB,
;;; between a named definitional instance in the base KB and an instance of
;;; the same class in the merge KB with the one or more names in common.
;;;
;;; See above for documentation of special situations in the handling
;;; of the name conflicts among definitional items.





;;; The global constant `all-definitional-classes' gives the list of all
;;; top-level definitional classes in G2.

(defconstant all-definitional-classes
  '(procedure
    function-definition
    tabular-function-of-1-arg
    tabular-function
    relation
    units-of-measure-declaration
    external-simulation-definition
    foreign-function-declaration
    remote-procedure-declaration
    rule
    generic-simulation-formula
    generic-formula
    user-menu-choice
    language-translation

    image-definition
    frame-style-definition

    tokenizer
    text-conversion-style))

;; I'd like, I think, to revise the definition of "definitional class" to
;; include DEFINITION itself.  It seems more useful that way, and more natural
;; to use and explain to people.  (MHD 4/18/94)


;;; `Definitional-class-p' ...

(defun definitional-class-p (class)
  (loop for definitional-class in all-definitional-classes
	thereis (subclassp class definitional-class)))



;;; A `record of definitional name conflicts' is a slot value list of the form
;;;
;;;   ( { (base-kb-instance-with-same-name
;;;         merge-kb-instance-with-same-name
;;;         name-in-common
;;;         [class-in-common-in-method-case?
;;;          common-arglist-length-in-method-case?])
;;;     } )
;;;
;;;
;;; If base-kb-instance-with-same-name is an instance of method, then the
;;; name-in-common will actually be the value of its procedure-method-name slot,
;;; and the final two elements should be filled in with its
;;; procedure-method-class and argument-count slot values, respectively.
	    
	    


;;; The kb-specific variable `record-of-definitional-name-conflicts?' is either nil,
;;; or, if the current KB was created via a merge with the variable record-definitional-
;;; name-conflicts? true, a record of that merge.  Its value gets reclaimed (via
;;; reclaim-slot-value-tree) and reset to nil upon creation of a new KB.

(def-kb-specific-variable record-of-definitional-name-conflicts? kb-merge nil
  nil reclaim-slot-value)



;;; When the variable `record-definitional-name-conflicts?' is true, a record of definitional
;;; name conflicts due to merging KBs are recorded in the variable
;;; record-of-definitional-name-conflicts?.

(defvar record-definitional-name-conflicts? t)		; only bound globally at present!



;;; `Record-name-conflict-if-necessary' ... called while reading a frame, just
;;; before name-or-names-for-frame has been put in its slot.  Note that
;;; name-or-class-name-for-frame is just can be any legal value of the
;;; name-or-names-for-frame slot of a block.

(defun-void record-name-conflict-if-necessary (frame name-or-class-name-for-frame)
  (when (and 
	  name-or-class-name-for-frame	; for named items
	  (null kb-load-case?)		; for merge case only
	  record-definitional-name-conflicts?
					; ^-- for auto-merge case only
					;   (this var. always true now --
					;   safe -- but do fix later!!)
	  (definitional-class-p (class frame)))
    (frame-class-case frame
      (method-declaration)		; maybe in the future, but don't
					;   consider multiple same-named
					;   method-declaration instance
					;   a conflict for now
      (method				; methods class if name, class, and
					;   arg count matches
	(loop with name?
	      with class
	      with count
	      for method being each class-instance of 'method
	      when (and (not (or (eq method frame)
				 (frame-has-been-reprocessed-p
				   method
				   current-frame-serial-number-before-reading)))
			(multiple-value-setq (name? class count)
			  (check-for-matching-methods
			    frame name-or-class-name-for-frame method)))
		return (note-definitional-name-conflict
			 method frame name? class count)))
      (t				; any other definitional class:
					;   conflict if more than one such
					;   with same name
	(loop with definitional-class-for-frame
	          ;; Frame is guaranteed to be a definitional class.
		= (loop for class in all-definitional-classes
		      when (frame-of-class-p frame class)
		      return class)
	      for name?
		  in (if (consp name-or-class-name-for-frame)
			 name-or-class-name-for-frame
			 '(nil))
	      as name-to-match = (or name? name-or-class-name-for-frame)
	      as base-kb-instance-with-same-name?
	      ;; The following gets a class instance of the same definitional-class-
	      ;; for-frame with the same name from the basis kb, if any:
		 = (let ((frame-or-frames-with-this-name
			   (frame-or-frames-with-this-name name-to-match)))
		     (if frame-or-frames-with-this-name
			 (if (atom frame-or-frames-with-this-name)
			     (when (and (not (frame-has-been-reprocessed-p
					       frame-or-frames-with-this-name
					       current-frame-serial-number-before-reading))
					(frame-of-class-p
					  frame-or-frames-with-this-name
					  definitional-class-for-frame))
			       frame-or-frames-with-this-name)
			     (loop for frame-with-same-name
				       in frame-or-frames-with-this-name
				   when (and (not (frame-has-been-reprocessed-p
						    frame-with-same-name
						    current-frame-serial-number-before-reading))
					     (frame-of-class-p
					       frame-with-same-name
					       definitional-class-for-frame))
				     return frame-with-same-name))))
	      when base-kb-instance-with-same-name?
		return (note-definitional-name-conflict
			 base-kb-instance-with-same-name?
			 frame name-to-match))))))

;; This doesn't work as spec'd if there are duplicates in the KB being read.
;; Decide what to do about this issue, and if and how to document it, and write
;; error messages in this situation. (MHD 12/2/94)


;;; `Note-definitional-name-conflict' adds entries to
;;; record-of-definitional-name-conflicts?, which see.

(defun note-definitional-name-conflict
    (base-kb-instance-with-same-name
     merge-kb-instance-with-same-name
     name-in-common
     &optional class-in-common-in-method-case?
               common-arglist-length-in-method-case?)
  (setq record-of-definitional-name-conflicts?
	(slot-value-cons
	  (nconc
	    (slot-value-list
	      base-kb-instance-with-same-name
	      merge-kb-instance-with-same-name
	      name-in-common)
	    (if class-in-common-in-method-case?
		(slot-value-list
		  class-in-common-in-method-case?
		  common-arglist-length-in-method-case?)))	  
	  record-of-definitional-name-conflicts?)))

;; Note: if you do multiple merges, you could get multiple entries with the same
;; base kb instance.




;;; The function `fix-up-relation-frame-references-for-definition-conflict'
;;; replaces (in relation-instances) the reference to the base-kb relation
;;; frame for the relation frame that is shortly to be deleted.  Definitional
;;; name conflicts are resolved by deleting the later-loaded same-named frame
;;; in favor of the frame loaded first.

(defun fix-up-relation-frame-references-for-definition-conflict
    (base-kb-relation relation-to-be-deleted)
  (loop for block being each class-instance of 'block
	for relation-instances = (relation-instances block)
	do
    (cond ((relation-instance-tree-p relation-instances)
	   (loop for relation-instance being each relation-instance of relation-instances
		 for relation-frame-reference = (relation-instance-relation relation-instance)
		 do
	     (when (eq relation-frame-reference relation-to-be-deleted)
	       (setf (relation-instance-relation relation-instance) base-kb-relation))))
	  ;; NOTE: sometimes the newly loaded data is not upgraded yet. For example,
	  ;; Merging a modified UILLIB into exist KB application. -- Chun Tian (binghe)
	  (t
	   (loop for relation-instance in relation-instances
		 for relation-frame-reference = (cadr-of-cons relation-instance)
		 do
	     (when (eq relation-frame-reference relation-to-be-deleted)
	       ;; In this case, API `relation-instance-relation` can't be used, we must use
	       ;; (SETF SECOND) or (SETF CADR) instead. -- Chun Tian (binghe), Mar 13, 2016.
	       (setf (second relation-instance) base-kb-relation)))))))

;;; Resolve-definitional-name-conflicts ... upon completion, it reclaims all conses
;;; in record-of-definitional-name-conflicts?, and sets it to nil.

(defun resolve-definitional-name-conflicts ()
  (when record-definitional-name-conflicts?
    (let ((resolving-definitional-name-conflicts? t))
      (loop with reference-frame-serial-number
	      = (copy-frame-serial-number (current-frame-serial-number))
	    for (base-kb-instance-with-same-name
		  merge-kb-instance-with-same-name
		  name-in-common
		  class-in-common-in-method-case?
		  common-arglist-length-in-method-case?)
		in record-of-definitional-name-conflicts?
	    unless (frame-has-been-reprocessed-p
		     merge-kb-instance-with-same-name
		     reference-frame-serial-number)
	      do
		(let ((class (class merge-kb-instance-with-same-name)))
		  (if (eq class 'method)
		      (notify-user-of-conflicts
			"Automatically deleting method ~A for ~
                         class ~A because a previously-loaded method ~
                         has the same name, is for the same class, and takes the same ~
                         number of arguments (~d)."
			name-in-common class-in-common-in-method-case?
			common-arglist-length-in-method-case?)     
		      (notify-user-of-conflicts
			"Automatically deleting ~(~a~) ~a because a ~
                         previously-loaded ~(~a~) has the same name."
			class name-in-common class)))
		(when (frame-of-class-p merge-kb-instance-with-same-name 'relation)
		  (fix-up-relation-frame-references-for-definition-conflict
		    base-kb-instance-with-same-name merge-kb-instance-with-same-name))
		(delete-frame merge-kb-instance-with-same-name)
	    finally
	      (loop for (base-kb-instance-with-same-name nil name-in-common)
			in record-of-definitional-name-conflicts?
		    when (frame-has-been-reprocessed-p
			   base-kb-instance-with-same-name
			   reference-frame-serial-number)
		      do (notify-user-of-conflicts
			   "WARNING: ~a ~a from the Basis KB no longer ~
                          exists.  You probably have to start over, and ~
                          resolve and merge and resolve conflicts by hand."
			   (class base-kb-instance-with-same-name)
			   name-in-common))
	      (reclaim-frame-serial-number reference-frame-serial-number)
	      (reclaim-slot-value-tree record-of-definitional-name-conflicts?)
	      (setq record-of-definitional-name-conflicts? nil)))))


;; To Do/Ideas for Automerge

;; Do not allow automerge when paused?!  If it were possible to restrict
;; the grammar based on whether you're paused or not (without a
;; tremendous kludge), we should do that.  I think without that, it's ok
;; to leave in as "something that's legal but doesn't work out too
;; well".  (TO DO!!!)









;;;; Showing Progress While Reading or Writing



;;; A `file progress' ...

(def-class (file-progress entity)

  (module-of-file-in-progress?
    nil (type module-name?) system
    vector-slot
    not-user-editable do-not-save)

  (namestring-of-file-in-progress?	; a legal text string
    nil (type unquoted-file-name?) system
    vector-slot
    not-user-editable do-not-save
    do-not-identify-in-attribute-tables)

  (progress-through-file			; for a KB, number of kb lines so far
						; in lines -- add "-in-lines"?
    0 (type progress-through-file) system vector-slot not-user-editable do-not-save)

  (length-of-file-in-characters?		; nil => not maintaining percentage
						; note that this may never be zero;
						;   if the file is zero length, this
						;   slot should be set to nil
						; always a positive fixnum -- if a 
						;   file's length is zero or a bignum, 
						;   slot is set to nil
    nil (type nil) system vector-slot not-user-editable do-not-save)

  (fixnum-time-of-last-file-progress-display-update
    0 system
    vector-slot
    not-user-editable do-not-save
    do-not-identify-in-attribute-tables)

  (direction-of-file-progress?
    nil (type direction-of-file-progress)
    system vector-slot)			; INPUT or OUTPUT
					; nil means same as INPUT

  (status-of-file-progress?		; UNOPENED, OPENING,
    nil (type status-of-file-progress)	;   OPEN, CLOSING, CLOSED, or
    system vector-slot)			;   ABORTED
					; nil means same as OPEN

  (number-of-kb-characters-so-far?
    nil system vector-slot)

  (total-number-of-items
    nil system vector-slot)

  (units-for-progress-through-file
    nil system vector-slot) ; items lines
  )

;; Consider having the slot be called "position-in-file".

;; When to update display?  (Now done every 50 lines.)
;; 
;; BAH: Update display every 5 seconds or every 3 seconds.
;; JRA: Update display every 200 lines.
;; MHD: These make you wait a bit too long between displays.
;;      Every second or every 100 lines.
;;
;; NOTE: G2 4.0 KB's have many more lines, due to the effort to make KBs more
;; "stable".  Consider upping the number from 100 to maybe 500.


(define-slot-alias direction direction-of-file-progress? file-progress)
(define-slot-alias status status-of-file-progress? file-progress)
(define-slot-alias file-name namestring-of-file-in-progress? file-progress)
(define-slot-alias module module-of-file-in-progress? file-progress)


(def-slot-value-writer direction-of-file-progress (value)
  (tformat
    "~(~a~)"
    (case value
      ((nil input)
       'in)
      (t 'out))))

(def-slot-value-writer status-of-file-progress (value)
  (tformat
    "~(~a~)"
    (case value
      (unopened "unopened")
      ((open nil) "writing")
      (closing "closing")
      (closed "closed")
      (aborted "ABORTED")
      (t value))))




;;; Number-of-kb-characters-so-far? is bound at top-level to nil, and by read-kb.
;;; If nil, then the percentage-through-file display is not being maintained (either
;;; because no kb is being read -- presumably being written, the number of characters
;;; in the file is unavailable, the number of characters is zero, or the number of
;;; characters is not a fixnum.)  Otherwise, it starts off being set to zero in read-
;;; kb, is incremented by read-next-char-for-kb, and is looked at by the writer for
;;; the progress-through-file slot of file-progress frames in order to know whether
;;; to show the percentage.  Also, when the file progress table is initially put
;;; up, this variable is bound appropriately to either nil or zero in order to
;;; get the writer to the percentage (0%) the first time, if appropriate.

(defvar number-of-kb-characters-so-far? nil)


;;; Unquoted-file-name? is slot type for the slot namestring-of-file-in-
;;; progress?.  It is never used as a grammar type.  It is only used for its
;;; writer, which prints out value without quotes, if value is non-nil, and
;;; prints no characters if value is nil.

(def-slot-value-writer unquoted-file-name? (value)
  (if value (twrite-string value) (twrite-string "none")))

(defvar total-items-in-file nil)
(defvar write-xml-object-items-collected nil)




(defparameter file-progress-finished-reading-states  
  '(reinitialize post-load post-load2 revert reformat automerge automerge2 finished))

(def-slot-value-writer progress-through-file (value file-progress)
  (let ((finished-reading-status?
	  (car (memq (status-of-file-progress? file-progress)
		     file-progress-finished-reading-states))))
    (cond
      (write-xml-object-items-collected
       (twrite-positive-fixnum value)
       (twrite-string " items"))
      (total-items-in-file
       (let ((percentage-through-file
	       (with-temporary-gensym-float-creation progress-through-file
		 (round
		   (*e (/e (coerce-fixnum-to-gensym-float
			     value)
			   (coerce-fixnum-to-gensym-float
			     total-items-in-file))
		       100.0)))))
	 (twrite-positive-fixnum percentage-through-file)
	 (twrite-string "%  ")
	 (twrite-positive-fixnum value)
	 (twrite-string " items")))
      (t
       (when (or number-of-kb-characters-so-far?
		 finished-reading-status?)
	 (let ((percentage-through-file
		  (if finished-reading-status?
		      100
		      (with-temporary-gensym-float-creation progress-through-file
			(round
			  (*e (/e (coerce-fixnum-to-gensym-float
				    number-of-kb-characters-so-far?)
				  (coerce-fixnum-to-gensym-float
				    (length-of-file-in-characters? file-progress)))
			      100.0))))))
	   (twrite-positive-fixnum percentage-through-file)
	   (twrite-string "%  ")))
       (twrite-positive-fixnum value)
       (twrite-string " lines")
       (unless (or (not (eql number-of-kb-characters-so-far? 0))
		   (memq (status-of-file-progress? file-progress) '(open nil)))
	 (twrite-string " (buffered)"))
    ;; New extra information for post-reading phases: (MHD 7/20/99)
    (when finished-reading-status?
      (tformat "  [~(~a~)]" finished-reading-status?))))))





;;; kb-file-progress is bound by read-kb to the frame whose table shows the
;;; progress through reading the KB.  For saving, such a frame is bound for each
;;; of the possibly multiple kb-saves in progress, and this variable is then
;;; irrelevant.

(defvar kb-file-progress nil)			; for read-kb

(defvar number-of-kb-lines-so-far 0)            ; added init value 0 for G2 running in LispWorks


(defvar namestring-for-kb-being-read)		; for displaying file progress.
;  Also used by images to provide a default directory.

(defvar name-text-string-for-kb-being-read)	; i.e. ~ is ~~, etc. (MHD 4/5/90)
						;   -- Now this one must be used
						;   the one above is not necessarily
						;   legal-text-string-p. -mhd


;;; Do-not-update-file-progress-display? inhibits graphic display on the file
;;; progress.  See documented uses in put-up-file-progress-display and
;;; update-file-progress-display.

(defvar do-not-update-file-progress-display? nil)


;;; The variable `do-not-restore-image-planes?' inhibits displaying the saved
;;; set of visible workspaces upon KB loading or merging, as well as not adding
;;; them to `saved-pane-description', used for new logins.

(defvar do-not-restore-image-planes? nil)

;;; The variable `do-not-notify-user-during-kb-load?' inhibits posting the
;;; "normal case" logbook messages when a KB is merged. That is, the
;;; "Merging..." and "Done merging..." messages.

(defvar do-not-notify-user-during-kb-load? nil)

;;; The variable `do-not-show-conflicts-during-kb-load?' inhibits showing
;;; conflict workspaces, or posting logbook messages relating to conflicts, when
;;; a KB is merged.

(defvar do-not-show-conflicts-during-kb-load? nil)


;;; The variable `do-not-allow-user-interactions-during-kb-load?' causes the UI
;;; to be completely disabled on all workstations during KB loading or saving.

(defvar do-not-allow-user-interactions-during-kb-load? nil)


;;; The macro `def-symbol-subset-selector' defines a "selector" function whose
;;; name is
;;; 
;;;   SELECT-SUBSET-OF-name-of-set
;;;
;;; along with a system variable named
;;;
;;;   SELECTED-name-of-set-SUBSETS-PLIST
;;;
;;; The selector function takes as its arguments a set of boolean-valued
;;; arguments, one for each element of selectable-elements, and returns a list
;;; that contains all elements of constant-elements, plus those elements
;;; selectable-elements for which a corresponding boolean-valued argument is
;;; true.
;;;
;;; For convenience, the symbol &optional signals the beginning of optional
;;; arguments in the selector function, i.e., that the rest of the symbols in
;;; the list should correspond to optional arguments in the selector function.
;;; (Note that it is an error for the symbol &OPTIONAL, literally, to appear
;;; more than once in the list.  It can never be a candidate member of a subset
;;; element.)
;;;
;;; The list the selector function returns is either taken from a previously
;;; made list saved in the system variable, or stored there for subsequent use.
;;; This means they are not to be reclaimed or incorporated into temporary
;;; structures.
;;; 
;;; The sets this can work for have to be relatively small.  The maximum number
;;; of selectable elements is 30.  The maximum number of optional arguments is
;;; limited in a implementation.  So is the maximum number of non-optional
;;; arguments, though usually less severely.  This macro does enforce the limit
;;; of 30 elements, but it doesn't deal with the limit on argument list lengths,
;;; since it's explicit about what the argument lists will be.
;;;
;;; The conses that make up the list in the system variable all belong to this
;;; facility.  They may be shared freely, but are not to be mutated in any way.
;;;
;;; This facility is intended to be used as a convenience in programming.  It is
;;; an alternative to having explicitly quoted lists in the code, which have
;;; common elements because they are subsets of some well-known set.  This is
;;; particularly common, for example, with G2 slot names, which have to be
;;; listed, by various callers, for example, of make-attributes-table.
;;;
;;; For example,
;;; 
;;;   (def-symbol-subset-selector stooges comedy
;;;     (moe larry)
;;;     (old-curly new-curly shemp))
;;;
;;; says that stooges is the set that you want to select subsets of.  This is
;;; in your comedy module.  You'll always subsets to include moe and larry.
;;; Old-curly, new-curly, and shemp may or may not appear.  Now,
;;;
;;;   (select-subset-of-stooges t nil nil)
;;;   => (moe larry old-curly)
;;;
;;;   (select-subset-of-stooges nil nil t)
;;;   => (moe larry shemp)
;;;
;;;   (select-subset-of-stooges t nil t)  ; wierd
;;;   => (moe larry old-curly shemp)

;;;   (select-subset-of-stooges t t t)  ; wait a minute....very wierd
;;;   => (moe larry old-curly new-curly shemp)


(defmacro def-symbol-subset-selector
    (name-of-set module-name constant-elements selectable-elements)
  (if (>f (length selectable-elements) positive-bits-per-fixnum)
      (error "the set of selectable elements is limited in size ~
              to ~d; this many elements, ~d, won't work!"
	     positive-bits-per-fixnum
	     (length selectable-elements)))
  (let ((include-p-lamda-list
	  (loop for symbol-or-&optional in selectable-elements
		collect (if (eq symbol-or-&optional '&optional)
			    symbol-or-&optional
			    (intern (format nil "INCLUDE-~a-P" symbol-or-&optional)))))
	(selected-subsets-plist-var
	  (intern (format nil "SELECTED-~a-SUBSETS-PLIST" name-of-set))))
	  
  `(progn
     (def-system-variable ,selected-subsets-plist-var ,module-name nil)
     (defun ,(intern
	       (format nil "SELECT-SUBSET-OF-~a" name-of-set))
	 ,include-p-lamda-list
       (let* ((pattern
		(logior
		  . ,(loop for arg-or-&optional in include-p-lamda-list
			   as shift-amount from 0
			   unless (eq arg-or-&optional '&optional)
			     collect `(ashf (if ,arg-or-&optional 1 0)
					    ,shift-amount)))))
	 (or (getf ,selected-subsets-plist-var pattern)
	     (let ((selected-subset
		     (nconc
		       ,@(loop for arg-or-&optional in include-p-lamda-list
			       as symbol-or-&optional in selectable-elements
			       unless (eq symbol-or-&optional '&optional)
				 collect `(if ,arg-or-&optional
					      (with-permanent-allocation
						(list ',symbol-or-&optional))))
		       ',constant-elements)))
	       (setq ,selected-subsets-plist-var
		     (nconc
		       (gensym-list pattern selected-subset)
		       ,selected-subsets-plist-var))
	       selected-subset)))))))

;; Move this general facility to UTILITIESx.  Make a better example!  (MHD 2/13/94)




;;; The function `select-subset-of-file-progress-attributes-to-show' returns a
;;; list, which should not be reclaimed, of the set of file-progress attributes
;;; to show.  By default, PROGRESS-THROUGH-FILE is always included.  The boolean
;;; value of the first, second, and third arguments select
;;; NAMESTRING-OF-FILE-IN-PROGRESS?, MODULE-OF-FILE-IN-PROGRESS?, and
;;; STATUS-OF-FILE-PROGRESS?, respectively.

(def-symbol-subset-selector file-progress-attributes-to-show
    kb-load1
  (progress-through-file)
  (&optional
    namestring-of-file-in-progress?
    module-of-file-in-progress?
    status-of-file-progress?))




;;; `Put-up-file-progress-display' puts up a table intended to show progress in
;;; reading or writing a file (a KB, for example), unless do-not-update-file-
;;; progress-display? is true.  It returns a file-progress frame, which should be
;;; updated using update-file-progress-display.  The display may be deleted by
;;; invoking delete-frame on the file-progress frame.  Note a file-progress frame
;;; is always created and returned; if do-not-update-file-progress-display? is
;;; true, it would simply not be put on a temporary workspace on any image planes.

;; New:   (MHD 8/30/91)

;;; The final optional argument, namestring-of-file-in-progress?, should be a
;;; namestring, an unshared text string, or nil.  If nil, nothing will be displayed.
;;; If non-nil, the string will be displayed underneath the progress-through-file
;;; display, without any "attribute name" showing.

(defun put-up-file-progress-display
    (read-case? &optional file-length?
		namestring-of-file-in-progress?
		direction? status?
		offset-in-saving-context?
		preexisting-file-progress?
		module-of-file-in-progress?)
  (let ((file-progress
	  (make-or-revise-file-progress
	    read-case? file-length?
	    namestring-of-file-in-progress?
	    direction? status?
	    module-of-file-in-progress?
	    preexisting-file-progress?)))
    (unless (or do-not-update-file-progress-display?
		preexisting-file-progress?)
      
      ;; Put file progress up on all workstations:
      (loop with file-progress-attributes-table
	      = (make-attributes-table
		  file-progress nil nil nil nil
		  (select-subset-of-file-progress-attributes-to-show
		    namestring-of-file-in-progress?))
	    with number-of-kb-characters-so-far?	; just for 1st call to writer
	      = (if (length-of-file-in-characters? file-progress) 0)
	    with file-progress-workspace
	      = (make-workspace
		  'temporary-workspace nil file-progress-attributes-table 2)
	    initially
	      
	      ;; Kludge to preallocate max space in cell to keep table
	      ;;   from flopping around on subsequent reformats:   (MHD 9/19/91)
	      (let ((suppress-updating-of-slot-value-representations? nil))	; bound t sometimes
		(change-slot-value file-progress 'module-of-file-in-progress? module-of-file-in-progress?)
		(change-slot-value file-progress 'progress-through-file
				   (or (length-of-file-in-characters? file-progress) 10000000))
		(change-slot-value file-progress 'progress-through-file 0)
		(change-slot-value file-progress 'number-of-kb-characters-so-far? 0)
		(change-slot-value file-progress 'direction-of-file-progress?
				   (or direction?
				       (if read-case? 'input 'output)))
		(note-update-to-file-progress file-progress))
	    
	    for workstation in workstations-in-service
	    as window = (window-for-workstation workstation)
	    unless (native-progress-bar-p window)
	      do (put-workspace-on-pane
		   file-progress-workspace
		   (detail-pane window)
		   'left 'top t
		   ;; Don't have a "standard" title bar, since at least for now we
		   ;; have no support for a close box while it's up. -mhd, 3/29/01
		   :frame-description-reference
		   (lookup-frame-description-reference-of-frame-style
		     'dialog-workspace-frame-style
		     'default-workspace-frame-style)
		   :margin-in-pane
		   (+ 11 (if offset-in-saving-context?
			     (* 100 offset-in-saving-context?)
			     0)))) ; YUCH!
      )

    (force-process-drawing)
    
    file-progress))


;; The way this puts up the file-progress attribute tables is just like
;; put-up-attributes-table, except it does not use font-for-attributes-table from
;; the fonts system table.

;; Consider abstracting away from Common Lisp's file-length function into our own
;; primitive, if file-length proves buggy or inept.

;; When the percentage is added, the line count should be kept too.  I believe people
;; like to see that number grow as they develop their KB, and have come to count on the
;; line count as it is now computed.  Updating the percentage when the line count changes
;; should be adequately often, in my view.  (LH, 3/4/89)

;; This may be called while kb-flags has an old value.




;;; The function `make-or-revise-file-progress' (previously make-file-progress)
;;; creates a new, or revises an existing, file-progress instance according to
;;; its arguments. Preexisting-file-progress? should be a previously created
;;; file-progress instance if this is to be a revision, otherwise nil to create
;;; a new instance.

(def-concept make-file-progress)	; name changed to: 

(defun make-or-revise-file-progress
    (read-case?
      &optional file-length?
      namestring-of-file-in-progress?
      direction? status? module?
      preexisting-file-progress?)
  (let* ((suppress-updating-of-slot-value-representations? nil)	; See Note 2
	 (file-progress (or preexisting-file-progress? (make-frame 'file-progress))))
    (change-slot-value file-progress 'direction-of-file-progress? direction?)
    (change-slot-value file-progress 'status-of-file-progress? status?)
    (change-slot-value file-progress 'namestring-of-file-in-progress?
		       namestring-of-file-in-progress?)
    (change-slot-value file-progress 'module-of-file-in-progress? module?)
    (when read-case?
      (change-slot-value
	file-progress 'length-of-file-in-characters? ; See Note 1
	(if (and file-length? (fixnump file-length?) (>f file-length? 0))
	    file-length?)))
    (change-slot-value file-progress 'fixnum-time-of-last-file-progress-display-update
		       (get-fixnum-time))
    (change-slot-value file-progress 'progress-through-file 0) ; See Note 2
    (change-slot-value file-progress 'number-of-kb-characters-so-far? 0)
    (unless (or do-not-update-file-progress-display?
		suppress-notification-for-kb-save?)
      (note-update-to-file-progress file-progress))
    file-progress))

;; Note 1: Modified by ML, 6/27/91. read-kb now gets the file length, avoiding
;; opening a second stream.  We can't use anything other than a positive fixnum,
;; since in C at least it means that file position is not implemented the
;; obvious way.

;; Note 2: We have here from a series of change-slot-value's, rather than setf
;; forms, since we could be using a preexisting instance, which needs the extra
;; processing of change-slot-value, e.g., for table updating and for
;; reclamation.  Also note that suppress-updating-of-slot-value-representations?
;; is bound true when this is invoked, so it has to be bound nil in order for
;; table updates to happen properly.  (MHD 7/21/99)





;;; `Update-file-progress-display' updates file-progress so that new-integer-value
;;; is shown on the display, unless do-not-update-file-progress-display? has been
;;; bound to true.

(defun update-file-progress-display (file-progress new-integer-value &optional force-update-p)
  (declare (special saving-kb-p))		; forward ref.
  (unless do-not-update-file-progress-display?
    (let ((fixnum-time-now (get-fixnum-time)))
      (when (or (>=f (fixnum-time-difference
		       fixnum-time-now
		       (fixnum-time-of-last-file-progress-display-update file-progress))
		     fixnum-time-interval-for-one-second)	; 1 second
		force-update-p)
	(setf (fixnum-time-of-last-file-progress-display-update file-progress)
	      fixnum-time-now)
	(change-slot-value file-progress 'progress-through-file new-integer-value)
	(change-slot-value file-progress 'units-for-progress-through-file
			   (if (or write-xml-object-items-collected total-items-in-file)
			       'items 'lines))
	(change-slot-value file-progress 'total-number-of-items total-items-in-file)
	(change-slot-value file-progress 'number-of-kb-characters-so-far? number-of-kb-characters-so-far?)
	(note-update-to-file-progress file-progress)
	(raise-file-progress-display-to-top file-progress) ; ensure display's visibility
	(force-process-drawing)))))



;;; `Update-file-progress-display-after-reading' ... Phase may be one of the
;;; following symbols: INITIALIZE-AFTER-READING, POST-LOAD, REVERT,
;;; REFORMAT-AS-APPROPRIATE, AUTOMERGE, AUTOMERGE2.

(defun update-file-progress-display-after-reading (file-progress phase)
  #+development
  (test-assertion (memq phase file-progress-finished-reading-states))
  (unless do-not-update-file-progress-display?
    (change-slot-value file-progress 'status-of-file-progress? phase)
    (setf (fixnum-time-of-last-file-progress-display-update file-progress)
	  (get-fixnum-time))
    (change-slot-value file-progress 'number-of-kb-characters-so-far? number-of-kb-characters-so-far?)
    (change-slot-value file-progress 'units-for-progress-through-file
		       (if (or write-xml-object-items-collected total-items-in-file)
			   'items 'lines))
    (update-representations-of-slot-value file-progress 'progress-through-file)
    (note-update-to-file-progress file-progress)
    (force-process-drawing)))





;;; File-progress-table-p is true if table represents a frame of class
;;; file-progress.

(defun file-progress-table-p (table)
  (loop for row in (table-rows table)
	thereis
	  (loop for cell? in row
		thereis
		  (and cell?
		       (not (cell-is-block-p cell?))
		       (let ((frame?
			       (get-slot-represented-by-text-cell-if-any
				 cell?)))
			 (and frame?
			      (frame-of-class-p
				frame? 'file-progress)))))))





;;; The function `raise-file-progress-display-to-top' ensures the display is on
;;; top (frontmost) in its window. Something could have covered it up during the
;;; loading of multiple KBs, notably merge conflict workspaces.  To be called
;;; when the periodic update is done the display of a file-progress.

(defun raise-file-progress-display-to-top (file-progress)
  (loop for representation in (frame-representations file-progress)
	as workspace?
	   = (if (table-p representation) (get-workspace-if-any representation))
	when workspace?
	  do (loop for image-plane in (image-planes-this-is-on workspace?)
		   do (raise-image-plane-to-top image-plane))))

;; If we supported having a workspace or image plane be always on top (ala the
;; topmost concept in Windows), then we would use that for the file progress
;; display, and calling this would not be necessary. (MHD 11/21/02)





;;;; Reading Groups of KBs



;;; Read-kb-or-group-thereof ...  returns true iff reading was successful.
;;; Read-kb-or-group-thereof is responsible for implementing autostart as
;;; appropriate.  It does not start G2 if the KB was read while G2 was paused.
;;; In other words, an explicit pause by the user overrides all flags inside the
;;; KB being loaded or merged.  [Make sure this is documented somewhere, too!]
;;;
;;; The argument gensym pathname gensym-pathname-to-read is not reclaimed or
;;; altered in any way by this function; that is the callers responsibility.
;;;
;;; What-to-do-after-loading-kb? should be either NIL or one of the following
;;; symbols:
;;;
;;;    WARMBOOT-AFTERWARDS
;;;    WARMBOOT-AFTERWARDS-WITH-CATCH-UP
;;;    
;;;    LOAD-FROM-COMMAND-LINE
;;;    
;;;    NEVER-START-AFTERWARDS
;;;    START-AFTERWARDS
;;;    ...
;;;

(defvar first-kb-in-group-read-in-yet?)
(defvar level-of-group-kb-read)
(defvar modules-loaded-in-this-group)
(defvar kb-serial-number-before-loading-this-group)




(defun-allowing-unwind read-kb-or-group-thereof
    (gensym-pathname-to-read
      clear-kb? install-system-tables?
      bring-formats-up-to-date?
      resolve-conflicts-automatically?
      what-to-do-after-loading-kb?
      update-before-loading?
      client?)
  (let ((time-before nil) (time-after nil)
        (measure-load-time? (string=w (get-command-line-keyword-argument #w"measure-load-time") #w"t")))
    (when do-not-allow-user-interactions-during-kb-load?
      (enable-ui-on-all-workstations nil))

    (when measure-load-time?
      (setq time-before (gensym-get-unix-time))
      (multiple-value-bind
	  (second minute hour date month year day-of-the-week daylight-savings-time-p time-zone)
	  (gensym-decode-unix-time time-before)
	(declare (ignore day-of-the-week daylight-savings-time-p time-zone))
	(notify-user-at-console 
	  "starting kb file '~a' loading (merging) on: ~a ~a ~a, ~a:~a:~a"
	  (gensym-namestring gensym-pathname-to-read) date
	  (nth (- month 1)
	       '("Jan" "Feb" "Mar" "Apr" "May" "Jun" "Jul" "Aug" "Sep" "Oct" "Nov" "Dec"))
	  year hour minute second)))
    (prog1
	(unwind-protect
	    (cond ((workstation-p client?)
		   (if servicing-workstation?
		       (read-kb-or-group-thereof-1
			 gensym-pathname-to-read clear-kb? install-system-tables?
			 bring-formats-up-to-date? resolve-conflicts-automatically? what-to-do-after-loading-kb?
			 update-before-loading?)
		       (for-workstation (client?)
			 (read-kb-or-group-thereof-1
			   gensym-pathname-to-read clear-kb? install-system-tables?
			   bring-formats-up-to-date? resolve-conflicts-automatically? what-to-do-after-loading-kb?
			   update-before-loading?))))
		  ((of-class-p client? 'ui-client-interface)
		   (let ((current-system-rpc-icp-socket?
			   (get-slot-value client? 'gsi-interface-icp-socket)))
		     (read-kb-or-group-thereof-1
		       gensym-pathname-to-read clear-kb? install-system-tables?
		       bring-formats-up-to-date? resolve-conflicts-automatically? what-to-do-after-loading-kb?
		       update-before-loading?)))
		  (t
		   (read-kb-or-group-thereof-1
		     gensym-pathname-to-read clear-kb? install-system-tables?
		     bring-formats-up-to-date? resolve-conflicts-automatically? what-to-do-after-loading-kb?
		     update-before-loading?)))
	  (when do-not-allow-user-interactions-during-kb-load?
	    (enable-ui-on-all-workstations t)))
      ;; GENSYMCID-976: G2-merge-kb returns true in case of failure
      ;; NOTE: return value of the whole function is above UNWIND-PROTECT form!
      (when measure-load-time?
	(setq time-after (gensym-get-unix-time))
	(multiple-value-bind
	    (second minute hour date month year day-of-the-week daylight-savings-time-p time-zone)
	    (gensym-decode-unix-time time-after)
	  (declare (ignore day-of-the-week daylight-savings-time-p time-zone))
	  (notify-user-at-console 
	    "ending kb file '~a' loading (merging) on: ~a ~a ~a, ~a:~a:~a"
	    (gensym-namestring gensym-pathname-to-read) date
	    (nth (- month 1)
		 '("Jan" "Feb" "Mar" "Apr" "May" "Jun" "Jul" "Aug" "Sep" "Oct" "Nov" "Dec"))
	    year hour minute second))
	(notify-user-at-console 
	  "the time span for the kb '~a' loading (merging) is ~as"
	  (gensym-namestring gensym-pathname-to-read)
	  (- time-after time-before))))))

(defun-allowing-unwind read-kb-or-group-thereof-1
    (gensym-pathname-to-read
      clear-kb? install-system-tables?
      bring-formats-up-to-date?
      resolve-conflicts-automatically?
      what-to-do-after-loading-kb?
      update-before-loading?)
  (protected-let* ((level-of-group-kb-read 0)
		   (first-kb-in-group-read-in-yet? nil)
		   (modules-loaded-in-this-group
		     nil
		     (reclaim-gensym-list modules-loaded-in-this-group))
		   (kb-serial-number-before-loading-this-group
		     current-kb-serial-number))
    (with-module-related-frame-note-updates-supressed
      (read-kb-or-group-thereof-2
	gensym-pathname-to-read clear-kb? install-system-tables?
	bring-formats-up-to-date? resolve-conflicts-automatically?
	nil what-to-do-after-loading-kb? update-before-loading?))))

(defun read-kb-or-group-thereof-2
    (gensym-pathname-to-read
      clear-kb? install-system-tables?
      bring-formats-up-to-date?
      resolve-conflicts-automatically?
      required-module-name?
      what-to-do-after-loading-kb?
      update-before-loading?)
  (declare (ignore required-module-name?))
  (let* ((warmboot-case?
	   (or (eq what-to-do-after-loading-kb? 'warmboot-afterwards)
	       (eq what-to-do-after-loading-kb?
		   'warmboot-afterwards-with-catch-up)))
	 (defer-notifications? clear-kb?)
	 (module-loading-schedule
	   (create-module-loading-schedule
	     gensym-pathname-to-read warmboot-case? update-before-loading? clear-kb?))
	 (source-code-control-warnings-p
	  (loop for (nil nil nil nil error?) in module-loading-schedule
		when error? return t))
	 (copy-of-module-loading-schedule
	   (copy-tree-using-gensym-conses module-loading-schedule)))
    (prog1 (cond
	     ((null module-loading-schedule)
	      (setq defer-notifications? nil)
	      (try-to-do-deferred-user-notifications)
	      nil)
	     ((and warmboot-case?
		   (or (not clear-kb?) (cdr module-loading-schedule)))
	      (notify-user
	       "Warmbooting can only be done when loading~A.  Cancelling the command!"
	       (if (not clear-kb?)
		   ", not when merging"
		   " a single KB file with no required modules"))
	      (setq defer-notifications? nil)
	      (try-to-do-deferred-user-notifications)
	      (reclaim-module-loading-schedule copy-of-module-loading-schedule)
	      nil)
	     ((loop for (module truename? mapped-default-directory requiring-module?)
			in module-loading-schedule
		    do
		(when (and (not (module-exists-p module)) ; added to fix bug 
			   (null truename?))              ; HQ-479462 "different merge KB
					; behavior between 40r0 and 40r1
					; (MHD 2/7/96)
		  (give-module-not-found-warning
		   module requiring-module?
		   (first (first (last module-loading-schedule)))
		   gensym-pathname-to-read)
		  
		  (return t))
		    finally (return nil))
	      (setq defer-notifications? nil)
	      (try-to-do-deferred-user-notifications)
	      ;; be sure all have truenames
	      nil)
	     ((and
	       servicing-workstation?	; only seek confirmation if there's a a user
	       (not doing-g2-init-file-p) ; and not during init file
	       (not doing-g2-init-kb-p)
	       ;; clear-kb?  ; DWR, and many users, requested that "Merge KB"
	       ;; prompt in just the same way as Load KB do, for consistency.
	       ;; I am enabling that behavior here.  (Note the change also
	       ;; to the text string below.) (MHD 5/29/94)
	       (or (not (empty-kb-p))
		   source-code-control-warnings-p))		   
	      (setq defer-notifications? nil)
	      (try-to-do-deferred-user-notifications)
	      (post-module-schedule-dialog
	       'loading module-loading-schedule
	       (let ((namestring-as-text-string
		      (gensym-namestring-as-text-string
		       (second (first module-loading-schedule)))))
		 (prog1 (twith-output-to-text-string
			  (tformat
			   ;; Merge modules as shown?
			   ;; Load modules as shown?
			   ;; Merge [namestring] into existing KB?
			   ;; Replace existing KB with [namestring]?
			   ;;   (Used to be "Replace existing KB?")
			   (cond
			     ((cdr module-loading-schedule)
			      (if clear-kb?
				  "Replace existing KB with modules as shown?"
				  "Merge modules as shown into existing kb?"))
			     (t		; consumes first format arg
			      (if clear-kb?
				  "Replace existing KB with \"~a\""
				  "Merge \"~a\" into existing KB")))
			   namestring-as-text-string)
			  (when clear-kb?
			    (twrite-changed-modules-note))
			  (when source-code-control-warnings-p
			    (tformat "  (Note: See the logbook for source code control warnings.)")))
		   (reclaim-text-string namestring-as-text-string)))
	       (if warmboot-case?
		   'warmboot-kb
		   'read-modules-of-kb-per-loading-schedule)	       
	       (if warmboot-case?
		   (slot-value-list			  
		    (second (first module-loading-schedule)) ; <=> gensym-pathname-to-read
		    (eq what-to-do-after-loading-kb? 'warmboot-afterwards-with-catch-up))
		   (slot-value-list 
		    copy-of-module-loading-schedule
		    clear-kb? install-system-tables?
		    bring-formats-up-to-date?
		    resolve-conflicts-automatically?
		    what-to-do-after-loading-kb?))
	       (if warmboot-case?
		   nil
		   'reclaim-module-loading-schedule-and-representations-thereof)
	       (if warmboot-case?
		   nil
		   (slot-value-list copy-of-module-loading-schedule))))

	     (warmboot-case?
	      (prog1 (warmboot-kb
		      (second (first module-loading-schedule))
		      (eq what-to-do-after-loading-kb? 'warmboot-afterwards-with-catch-up))
		(setq defer-notifications? nil)
		(try-to-do-deferred-user-notifications)))
	     (t	   
	      (prog1 (read-modules-of-kb-per-loading-schedule
		      copy-of-module-loading-schedule
		      clear-kb? install-system-tables?
		      bring-formats-up-to-date?
		      resolve-conflicts-automatically?
		      what-to-do-after-loading-kb?)
		(setq defer-notifications? nil)
		(try-to-do-deferred-user-notifications))))
      (reclaim-module-loading-schedule module-loading-schedule))))




(defvar some-module-is-clear-text-p nil)

;;; The function `read-modules-of-kb-per-loading-schedule' does the work of
;;; reading an ordered list of modules (a `module-loading-schedule') into the
;;; current KB. ...

;;; The variable `kb-file-progress-is-currently-for-modules-p' is bound nil at
;;; top-level.  It may be bound to t, normally by
;;; read-modules-of-kb-per-loading-schedule, to indicate to read-kb that a
;;; higher-level caller is handling the creation/deletion of the file-progress
;;; instance bound to kb-file-progress.

(defvar kb-file-progress-is-currently-for-modules-p nil)
(defvar current-kb-file-progress-for-modules? nil)
(defparameter need-call-system-start nil)

(defun read-modules-of-kb-per-loading-schedule
    (module-loading-schedule
      clear-kb? install-system-tables?
      bring-formats-up-to-date?
      resolve-conflicts-automatically?
      what-to-do-after-loading-kb?)
  (reclaim-any-module-schedule-displays)
  (setq some-module-is-clear-text-p nil)
  (loop with defer-notifications? = clear-kb?
	with current-kb-file-progress-for-modules?
	  = nil				; new: we control the kb-file-progress, 
					;   rather than having it done by read-kb
	with kb-file-progress-is-currently-for-modules-p
	  = t				; tells read-kb we're in control
	with remaining-modules-to-load = module-loading-schedule
	as (module truename? default-kb-directory)
	  = (car remaining-modules-to-load)
	as first-time? = t then nil
	as last-time? = (null (cdr remaining-modules-to-load))
	as post-loading-functions-will-be-executed-again-later?
	  = (not last-time?)
	when
	  (null
	    (cond
	      ((and (module-exists-p module)
		    (not last-time?)
		    (or (not first-time?)
			(not clear-kb?)))
	       (unless do-not-notify-user-during-kb-load?
		 (notify-user		; Consider this a "normal case" message.
		   "Skipping module ~a, since it is already present."
		   module))
	       t)
	      ((null truename?)
	       (notify-user
		 "Module ~a could not be found!"
		 module)
	       nil)
	      (t
	       (read-kb
		 module
		 truename?		 
		 (if clear-kb? first-time?)
		 (if install-system-tables? last-time?)
		 bring-formats-up-to-date?
		 resolve-conflicts-automatically?
		 default-kb-directory))))
	  return
	  (progn
	    (do-post-loading-functions :error-recovery)
	    (notify-user
	      "WARNING!! This KB was not loaded successfully.")
	    (setq defer-notifications? nil)
	    (try-to-do-deferred-user-notifications)
	    nil)			; nil indicates failure
	do (pop remaining-modules-to-load)
	while remaining-modules-to-load
	finally
	  (when current-kb-file-progress-for-modules?
	    ;; deal with file-progress display, if any
	    (note-update-to-file-progress current-kb-file-progress-for-modules? 'delete)
	    (delete-frame current-kb-file-progress-for-modules?)
	    (force-process-drawing))
	  (unless (or doing-g2-init-file-p
		      system-has-paused)
	    (let ((autostart-reason?
		    (cond
		      ((eq what-to-do-after-loading-kb?
			   'start-afterwards)
		       (if clear-kb? 'load-grammar 'merge-grammar))
		      ((eq what-to-do-after-loading-kb?
			   'load-from-command-line)
		       'load-from-command-line)
		      ((and (not (eq what-to-do-after-loading-kb?
				     'never-start-afterwards))
			    (start-kb-after-load-from-system-table?))
		       'system-table))))
	      (when autostart-reason?
		(cond
		  (launch-recompile-for-compilations-removed-in-this-kb?
		   ;; Don't autostart if recompiling, e.g., between major
		   ;; versions of G2.
		   (notify-user
		     "G2 cannot start automatically because this KB has not been ~
                  compiled up-to-date and saved in the current version of G2.  ~
                  Once you save the KB in this version of G2, it will be possible ~
	          for G2 to start automatically."))
		  (t	       
		   (notify-user-of-autostart-and-reason autostart-reason?)
		   (setq need-call-system-start t))))))
	  (setq defer-notifications? nil)
	  (try-to-do-deferred-user-notifications)
	  (reclaim-pathnames-in-loading-schedule module-loading-schedule)
	  (reclaim-module-loading-schedule module-loading-schedule)
	  (return t)))




;; ADD NEEDED WARNING MESSAGE NOTIFICATIONS:
;; 
;; AND: WARNING!!  G2 could not open a file that corresponds to the module
;; name ~a.  Loading has failed!!" for cases where a required module cannot
;; be found!!
;;
;; AND: "WARNING!! This KB (~s) requires modules but does not specify its
;; own module name!" for cases where it has nil as its top-level module but
;; requires submodules!
;;
;; AND: "WARNING!! This KB (~s) is being required as module ~a, but it does not 
;; specify its own module name!" for cases where it is required but but does
;; not specify a top-level module.
;;
;; AND: "WARNING!! For KB ~s, the file name ~a is not the same as the module
;; name, ~a."
;; 
;; AND: "WARNING!! The module name ~a for for this KB (~s) is other than the
;; one that was required, ~a."
;;
;; (MHD 12/3/91)

;; Make sure top-level kb pathname is being properly installed as the default
;; in the appropriate cases. (MHD 11/8/91)



;;;; File and Pathname Interface to Modules


(def-class (module-load-request file-progress)
  (module-that-required-this?
    nil (type module-name?)
    system vector-slot not-user-editable do-not-save)
  (modules-this-required
    nil (type list-of-modules?)
    system vector-slot not-user-editable do-not-save))

(defun make-module-load-request
    (module file-truename? &optional requiring-module? required-modules)
  (let ((module-load-request (make-frame 'module-load-request)))
    (setf (module-of-file-in-progress? module-load-request)
	  module)
    (setf (namestring-of-file-in-progress? module-load-request)
	  (if file-truename? (gensym-namestring-as-text-string file-truename?)))
    (setf (module-that-required-this? module-load-request)
	  requiring-module?)
    (setf (modules-this-required module-load-request)
	  required-modules)
    (note-update-to-file-progress module-load-request)
    module-load-request))


;;; `Create-module-load-requests-per-schedule' creates a gensym-cons list of
;;; module-load-request instances based module-loading-schedule.

(defun create-module-load-requests-per-schedule (module-loading-schedule)
  (loop for (module truename?) in module-loading-schedule
	as module-load-request = (make-module-load-request module truename?)
	collect module-load-request using gensym-cons))


;;; The function `select-subset-of-module-load-request-attributes-to-show'
;;; returns a list, which should not be reclaimed, of the set of file-progress
;;; attributes to show.  By default, MODULE-OF-FILE-IN-PROGRESS? and
;;; NAMESTRING-OF-FILE-IN-PROGRESS? are always included.  The boolean value of
;;; the first and second arguments select MODULES-THIS-REQUIRED and
;;; MODULE-THAT-REQUIRED-THIS?, respectively.

(def-symbol-subset-selector module-load-request-attributes-to-show
    kb-load1
  (module-of-file-in-progress? namestring-of-file-in-progress?)
  (&optional
    modules-this-required
    module-that-required-this?))

(def-text-cell-format small-file-progress-display-value-format
  text-cell-lines-justified? nil
  text-cell-left-margin 8
  text-cell-top-margin 4
  text-cell-right-margin 8
  text-cell-bottom-margin 4
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 8
  text-cell-font-map (hm14)
  text-cell-line-height 18
  text-cell-baseline-position 14
  text-cell-line-spacing 3
  default-word-spacing #.(convert-to-text-width 4)
  minimum-format-width-for-text-cell 500)

;; Based on small-attribute-value-format, but just has a wider
;; minimum-format-width.
    

;;; `Make-multiframe-table-per-module-load-requests' ... Note: this is called
;;; for both loads andb saves now.

(defun make-multiframe-table-per-module-load-requests (module-load-requests)
  (loop with existing-table-rows = nil
	with existing-slots = nil
	for module-load-request in module-load-requests
	do (multiple-value-setq
	       (existing-table-rows existing-slots)
	     (merge-frame-into-multiframe-table-rows
	       module-load-request
	       (select-subset-of-module-load-request-attributes-to-show)
	       existing-table-rows
	       existing-slots
	       'small-file-progress-display-value-format))
	finally
	  (reclaim-slot-value existing-slots)
	  (return
	    (finish-making-multiframe-table existing-table-rows nil))))


(defparameter module-schedule-title #w"Modules and File Names")

;;; `Display-table-module-load-requests' creates a multiframe table displaying
;;; the information in module-loading-schedule, and shows it on the current
;;; workstation on a temporary workspace, assuming there is a current
;;; workstation, and returns the table.  If this is not called in a
;;; servicing-workstation? context, this does nothing, and returns nil.

(defun display-module-loading-schedule (module-loading-schedule)
  (when servicing-workstation?
    (let* ((module-load-requests
	     (create-module-load-requests-per-schedule
	       module-loading-schedule))
	   (table
	     (prog1
		 (make-multiframe-table-per-module-load-requests
		   module-load-requests)
	       (reclaim-gensym-list module-load-requests)))
	   (workspace
	     (make-workspace 'temporary-workspace nil table)))

      ;; set the title bar text -- it actually only appears now in the
      ;; multiwindow UI.  We don't particularly want it there, but there's
      ;; currently no way to suppress the title bar.  In the non-multiwindow
      ;; case, a frame style is used, so no title bar appears. (MHD 8/22/03)
      (setf (title-bar-text workspace)
	    (copy-text-string module-schedule-title))
      (put-workspace-on-pane
	workspace
	current-workstation-detail-pane 'left 'top t))))


;;; `reclaim-any-module-schedule-displays' deletes all instances of the class
;;; module-load-request.

(defun reclaim-any-module-schedule-displays ()  
  (loop while
	(loop for module-load-request
	        being each class-instance of 'module-load-request
	      do (note-update-to-file-progress module-load-request 'delete)
		 (delete-frame module-load-request)
	      return t)))



;;; `Reclaim-module-loading-schedule-and-representations-thereof' ...

(defun reclaim-module-loading-schedule-and-representations-thereof
    (module-loading-schedule)
  (reclaim-any-module-schedule-displays)
  (reclaim-module-loading-schedule module-loading-schedule))


;;; The function `post-module-schedule-dialog' combines the functions of
;;; display-module-loading-schedule and enter-dialog so that we can use a single
;;; native dialog for both, if the window supports it. Used for both loading and
;;; saving.

(defun post-module-schedule-dialog
    (type module-schedule dialog-message-text-string
	  ok-function? ok-function-arglist?
	  cancel-function? cancel-function-arglist?)
  (let* ((native-dialog-p
	   (and (native-simple-dialogs-p current-workstation-window)
		(window-supports-simple-dialog-ex current-workstation-window)))
	 (display-schedule-p
	   (case type
	     (loading (not (null (cdr module-schedule))))
	     (t (not (null module-schedule)))))
	 (warning-p			; HACK
	   (or (gensym-search #w"(note" dialog-message-text-string)
	       (gensym-search #w"(Note" dialog-message-text-string)))
	 (simple-dialog-title?
	   (when (and native-dialog-p display-schedule-p)
	     module-schedule-title))
	 (simple-dialog-fill-text-p
	   nil)
	 (simple-dialog-plist?
	   (when (and native-dialog-p display-schedule-p)
	     (gensym-list
	       'icon (if warning-p 'warning 'question)
	       'checkable (if (eq 'saving type) t nil)
	       'row-count (if (eq 'saving type) (length module-schedule))
	       'columns (copy-gensym-tree-with-text-strings
			  '(#w"Module" #w"File name"))
	       'rows (loop for (module truename?) in module-schedule
			   as namestring = (if truename? 
					       (gensym-namestring truename?)
					       (copy-wide-string #w""))
			   collect (copy-text-string (stringw module)) using gensym-cons
			   collect namestring using gensym-cons)))))

    (unless native-dialog-p		; Native dialog displays the schedule itself.
      (when display-schedule-p
	(display-module-loading-schedule module-schedule)))

    (enter-dialog dialog-message-text-string
		  nil nil
		  ok-function? ok-function-arglist?
		  cancel-function? cancel-function-arglist?)
    (when simple-dialog-plist?
      (reclaim-gensym-tree-with-text-strings simple-dialog-plist?))))




;;;; Cached Directory Search Operations


;;; The variable `directory-cache-use-disabled-p' may be bound or set true to
;;; disable use of the cache.  When it is true, the principle exported function
;;; interfaces, gensym-probe-file-using-cache and gensym-directory-using-cache,
;;; should behave exactly the same, but not actually do any caching, but rather
;;; use tried and true PATHNAMES functionality.
;;;
;;; This can be used at times in the product development cycle
;;; when we either have bugs in this code, or at times when we lack complete
;;; confidence in it, or just to disable it in some dynamic extent when it is
;;; deemed not a good thing a some specific reason.
;;;
;;; [As of 6/13/94, the directory caching code is known not to work for DOS file
;;; system (i.e., Windows NT, Windows, etc.).  Therefore,
;;; directory-cache-use-disabled-p defaults to T in the shipping product.  It has
;;; been extensively tested and found to work in unix environments.  VMS
;;; environments remain a question mark.  Moreover, its performance
;;; characteristics are in doubt because it at present uses a linearized search.
;;; For production use, it should use either a binary tree or hash table lookup,
;;; at least when directories are on the large side. (MHD 6/13/94)]

(defparameter directory-cache-use-disabled-p t)

(defvar file-system-directory-search-cache-active-p nil)
(defvar file-system-directory-search-cache)
(defvar file-system-directory-search-cache-wildcard-string nil)

(defmacro with-file-system-directory-search-cache
    ((&key wildcard-string initial-cache-contents) &body body)
  `(let ((file-system-directory-search-cache ,initial-cache-contents)
	 (file-system-directory-search-cache-active-p t)
	 (file-system-directory-search-cache-wildcard-string
	   (or ,wildcard-string "*.*"))) ; WON'T WORK FOR VMS!! FIX!
     (prog1
	 (progn . ,body)
       (reclaim-file-system-directory-search-cache))))


(defun reclaim-file-system-directory-search-cache ()
  (setq file-system-directory-search-cache
	(prog1 nil
	  (reclaim-directory-search-cache
	    file-system-directory-search-cache))))

(defun copy-file-system-directory-search-cache ()
  (copy-directory-search-cache file-system-directory-search-cache))

(defun seize-file-system-directory-search-cache ()
  (prog1 file-system-directory-search-cache
    (setq file-system-directory-search-cache nil)))
  


(defun reclaim-directory-search-cache (directory-search-cache)
  (loop for entry in directory-search-cache
	do (loop for gensym-pathname in entry
		 do (reclaim-gensym-pathname gensym-pathname))
	finally
	  (reclaim-gensym-tree directory-search-cache)))

(defun copy-directory-search-cache (directory-search-cache)
  (loop for entry in directory-search-cache
	collect (loop for gensym-pathname in entry
		      collect (copy-gensym-pathname gensym-pathname)
			using gensym-cons)
	  using gensym-cons))


;;; `Gensym-probe-file-using-cache' ... differs from gensym-probe-file
;;; in that it's case-insensitive.  It may be called even without being
;;; in a with-file-system-directory-search-cache environment; however,
;;; it is generally much faster in the environment.

(defun-allowing-unwind gensym-probe-file-using-cache (convertable-thing)
  (when directory-cache-use-disabled-p
    (return-from gensym-probe-file-using-cache
      (gensym-probe-file convertable-thing)))
  (if file-system-directory-search-cache-active-p
      (protected-let*
	  ((gensym-pathname
	     (gensym-pathname convertable-thing)
	     (reclaim-gensym-pathname gensym-pathname))
	   (gensym-directory-and-above-namestring
	     (gensym-directory-and-above-namestring gensym-pathname)
	     (reclaim-text-string gensym-directory-and-above-namestring))
	   (directory-pathname
	     (gensym-pathname gensym-directory-and-above-namestring)
	     (reclaim-gensym-pathname directory-pathname))
	   (wildcarded-namestring
	     (tformat-text-string
	       "~a~a"
	       gensym-directory-and-above-namestring
	       file-system-directory-search-cache-wildcard-string)
	     (reclaim-text-string wildcarded-namestring))
	   (cached-directory-entry?
	     (assoc directory-pathname
		    file-system-directory-search-cache
		    :test #'gensym-pathnames-equal-p)))	; For VMS, may want ..-enough-p!
	(when (null cached-directory-entry?)
	  (setq cached-directory-entry?
		(gensym-cons
		  (copy-gensym-pathname directory-pathname)
		  (gensym-directory wildcarded-namestring nil)))
	  (gensym-push
	    cached-directory-entry?
	    file-system-directory-search-cache))
	(loop for candidate-gensym-pathname
		  in (cdr cached-directory-entry?)
	      when (and (string-equalw	; case insensitive name
			  (gensym-pathname-name gensym-pathname)
			  (gensym-pathname-name candidate-gensym-pathname))
			(string-equalw 	; case insensitive type
			  (gensym-pathname-type gensym-pathname)
			  (gensym-pathname-type candidate-gensym-pathname))
			(eql		; version?
			  (gensym-pathname-version gensym-pathname)
			  (gensym-pathname-version candidate-gensym-pathname))
			;; directory, host are presumably same; other fields?
			)
		return (copy-gensym-pathname candidate-gensym-pathname)))
      (with-file-system-directory-search-cache ()
	  (gensym-probe-file-using-cache convertable-thing))))

;; Build this on top of file name strings, rather than pathnames. That would
;; allow a really speedy implementation to be built, at least on top of unix,
;; where we could easily avoid the huge overhead associated with converting
;; from strings to pathnames.  (MHD 4/19/94) 

;; Move this to the module PATHNAMES!
  
;; At present, we allow the cache to grow without bounds within its dynamic
;; extent.  Consider limiting this.



;;; `Gensym-directory-file-using-cache' ... if include-subdirectories? is true, all
;;; subdirectories in the directory specified by pathname are returned.

(defun-allowing-unwind gensym-directory-using-cache
    (convertable-thing &optional include-subdirectories?)
  (when directory-cache-use-disabled-p	; should say "disabled"! (MHD 12/21/94)
    (return-from gensym-directory-using-cache
      (nconc
	(gensym-directory convertable-thing nil)
	;; The following is different from the really (caching) version in that
	;; it doesn't include the up ("..") directory pathname in its results,
	;; which is also sad.  Fix later! (MHD 6/13/94)
	(if include-subdirectories?
	    (protected-let ((directory-pathname
			      (gensym-make-pathname
				:host (gensym-pathname-host convertable-thing)
				:device (gensym-pathname-device convertable-thing)
				:directory (gensym-pathname-directory convertable-thing)
				:name :wild :type nil :version nil)
			      (reclaim-gensym-pathname directory-pathname))
			    (path-list
			      (gensym-subdirectories directory-pathname nil)
			      (reclaim-path-list path-list)))
	      (loop for file in path-list
		    as directory? = (gensym-file-as-directory file)
		    when directory?
		      collect directory?
			   using path-cons
		    do (reclaim-gensym-pathname file)))))))
  (if file-system-directory-search-cache-active-p
      (protected-let*
	  ((gensym-pathname
	     (gensym-pathname convertable-thing)
	     (reclaim-gensym-pathname gensym-pathname))
	   (gensym-directory-and-above-namestring
	     (gensym-directory-and-above-namestring gensym-pathname)
	     (reclaim-text-string gensym-directory-and-above-namestring))
	   (directory-pathname
	     (gensym-pathname gensym-directory-and-above-namestring)
	     (reclaim-gensym-pathname directory-pathname))
	   (wildcarded-namestring
	     (tformat-text-string
	       "~a~a"
	       gensym-directory-and-above-namestring
	       file-system-directory-search-cache-wildcard-string)
	     (reclaim-text-string wildcarded-namestring))
	   (cached-directory-entry?
	     (assoc directory-pathname
		    file-system-directory-search-cache
		    :test #'gensym-pathnames-equal-p))
	   (file-directory-if-needed
	     (if (null cached-directory-entry?)
		 (gensym-directory wildcarded-namestring nil)))
	   (subdirectory-directory-if-needed-1
	     (all-subdirectories-in-directory
	       directory-pathname)
	     (reclaim-path-list subdirectory-directory-if-needed-1))
	   (subdirectory-directory-if-needed
	     (if (null cached-directory-entry?)
		 (loop with result = nil
		       with list
		         = subdirectory-directory-if-needed-1
		       for l on list
		       as d? = (if (or (string=w (gensym-pathname-name (car l))
						 #w".")
				       (string=w (gensym-pathname-name (car l))
						 #w".."))
				   (car l)
				   (gensym-file-as-directory (car l)))
		       as d1? = (cond
				  ((null d?)
				   (car l))
				  ((eq d? (car l))
				   (car l))
				  (t
				   (reclaim-gensym-pathname
				     (car l))
				   d?))
		       do (cond

			    ((or (member d1? result
					 :test
					 #'gensym-pathnames-equal-p)
				 (member d1? file-directory-if-needed
					 :test
					 #'gensym-pathnames-equal-p))
			     (reclaim-gensym-pathname d1?)
			     nil)
			    (t
			     (path-push d1? result)))
		       finally (return result)))))
	(when (null cached-directory-entry?)
	  (setq cached-directory-entry?
		(gensym-cons
		  (copy-gensym-pathname directory-pathname)
		  (nconc
		    file-directory-if-needed
		    subdirectory-directory-if-needed)))
	  (gensym-push
	    cached-directory-entry?
	    file-system-directory-search-cache))
        (loop for candidate-gensym-pathname
                  in (cdr cached-directory-entry?)
              when (if (and (null (gensym-pathname-name candidate-gensym-pathname)) ; OR instead?!
                            (null (gensym-pathname-type candidate-gensym-pathname))
                            (null (gensym-pathname-version candidate-gensym-pathname)))
                       include-subdirectories?
                       (and (if (eq 
                                  (gensym-pathname-name gensym-pathname)
                                  :wild)
                                t
                                (string-equalw   ; case insensitive name
                                  (gensym-pathname-name gensym-pathname)
                                  (gensym-pathname-name candidate-gensym-pathname)))
                            (if (eq 
                                  (gensym-pathname-type gensym-pathname)
                                  :wild)
                                t
                                (string-equalw   ; case insensitive type
                                  (gensym-pathname-type gensym-pathname)
                                  (gensym-pathname-type candidate-gensym-pathname)))
                            (if (eq 
                                  (gensym-pathname-version gensym-pathname)
                                  :wild)
                                t
                                (eql            ; version?
                                  (gensym-pathname-version gensym-pathname)
                                  (gensym-pathname-version candidate-gensym-pathname)))
                            ;; directory, host are presumably same; other fields?
                            ))
                collect (copy-gensym-pathname candidate-gensym-pathname)
                  using path-cons))
      (with-file-system-directory-search-cache ()
	  (gensym-directory-using-cache
	    convertable-thing
	    include-subdirectories?))))








;;; The function `search-for-module-truename' searches as follows:
;;;
;;;   (1) If there is an entry for module in the special variable
;;;   g2-module-file-name-map, then let the current goal file name be the
;;;   pathname resulting from merging the module name with the file name
;;;   specified in that entry; otherwise, let the current goal file name be the
;;;   file name with just the name component, module name.
;;;
;;;   (2) Do the following search until a truename is returned for each of the
;;;   following directories in turn: (a) the directory specified by
;;;   default-pathname; (b) each directory in g2-module-search-path (in
;;;   first-to-last order); (c) the G2 launch directory.
;;;
;;;         let the current goal file name be the current goal
;;;         file name merged with the directory file name, and
;;;         with type "kl", and probe for the file name;
;;;
;;;         do the same, but for "kl"
;;;
;;;         If at any point, a probe is successful, the truename
;;;         is found, and is returned.




(def-suite-for-loading-file-at-launch-time module-map g2
  :base-name-of-file-to-load   "g2"
  :type-of-file-to-load        "mm"
  :command-line-keyword        "module-map"
  :environment-variable-name   "G2_MODULE_MAP"
  :base-name-of-disabling-file "NOG2MODULEMAP"
  :type-of-disabling-file      "CMD")


(defun-allowing-unwind update-g2-module-file-name-map ()
  (let* ((module-map-pathname?
	   (get-or-use-g2-module-map-pathname))
	 (reclaim-module-map-pathname?
	   (loop for (nil gensym-pathname) in g2-module-file-name-map
		 always (neq module-map-pathname? gensym-pathname))))
    (cond
      (module-map-pathname?
       (prog1 (g2-stream-with-open-stream
		  (g2-input-stream? module-map-pathname? :direction :input
				    ;; :if-does-not-exist "return nil" -- what we want,
				    ;; and now get, I believe.
				    )
		(when g2-input-stream?
		  (update-g2-module-file-name-map-from-map-file-stream
		    g2-input-stream?)))
	 ;; Added this gensym-pathname reclaimer to fix a VW bug fix where
	 ;; g2-save-module leaks only when a module-map appears on the command
	 ;; line.  (ghw 10/22/96)
	 (when reclaim-module-map-pathname?
	   (reclaim-gensym-pathname module-map-pathname?))))
      (t
       (setq g2-module-file-name-map nil)))))


(defun update-g2-module-file-name-map-from-map-file-stream (g2-input-stream)
  (setq g2-module-file-name-map
	(prog1 (read-module-file-name-map-from-stream g2-input-stream)
	  (reclaim-module-file-name-map g2-module-file-name-map))))

(defun reclaim-module-file-name-map (module-file-name-map)
  (loop for (nil gensym-pathname) in module-file-name-map
	do (reclaim-gensym-pathname gensym-pathname)
	finally (reclaim-gensym-tree module-file-name-map)))

(defun read-module-file-name-map-from-stream (input-g2-stream)
  (loop for input-line? = (g2-stream-read-line input-g2-stream)
	while input-line?
	as module-map-entry? = (parse-module-map-line-into-parts input-line?)
	when module-map-entry?
	  collect module-map-entry? into result-so-far using gensym-cons
	finally
	  (return result-so-far)))



;;; `Find-module-pathname-mapping-if-any' returns a new gensym pathname corresponding
;;; to the user-supplied mapping for module in g2-module-file-name-map, if found.  If
;;; not found, nil is returned.  Note that a pathname might have all components,
;;; including the name components, equal to nil, i.e., if the user entered a null
;;; pathname (""), or made a syntax error in specifying a pathname ("://.\\:").

(defun find-module-pathname-mapping-if-any (module)
  (let ((gensym-pathname-mapping?
	 (second (assq module g2-module-file-name-map))))
    (if gensym-pathname-mapping?
	(copy-gensym-pathname gensym-pathname-mapping?))))



(defun find-module-specific-search-path-if-any (module)
  (let ((search-path? (nthcdr 2 (assq module g2-module-file-name-map))))
    (loop for p in search-path?
	  collect (copy-gensym-pathname p)
	    using gensym-cons)))
	 
      



;;; `Module-name-as-gensym-pathname' returns a gensym pathname whose only
;;; non-nil component is its name component, which is derived from the symbol
;;; name of module.

(defun module-name-as-gensym-pathname (module)
  (let ((symbol-name-text-string-copy (copy-symbol-name module nil)))
    (prog1 (gensym-make-pathname :name symbol-name-text-string-copy)
      (reclaim-text-string symbol-name-text-string-copy))))







;;; `Get-or-make-directory-for-module-truename-search' ...
;;;
;;; `Saved-directories-for-module-truename-search' ...
;;;
;;; `Reclaim-saved-directories-for-module-truename-search' ...

(defvar saved-directories-for-module-truename-search)

(defun get-or-make-directory-for-module-truename-search (wild-name-pathname)
  (or (loop for (pathname . directory)
		in saved-directories-for-module-truename-search
	    when (gensym-pathnames-equal-p pathname wild-name-pathname)
	      return directory)
      (let* ((pathname (copy-gensym-pathname wild-name-pathname))
	     (directory (gensym-directory pathname nil)))
	(setq saved-directories-for-module-truename-search
	      (gensym-cons
		(gensym-cons pathname directory)
		saved-directories-for-module-truename-search))
	directory)))


(defun reclaim-saved-directories-for-module-truename-search (saved-directories)
  (loop for cons in saved-directories
	for (pathname . directory) = cons
	do (reclaim-gensym-pathname pathname)
	   (loop for pathname in directory
		 do (reclaim-gensym-pathname pathname))
	   (reclaim-path-list directory)
	   (reclaim-gensym-cons cons))
  (reclaim-gensym-list saved-directories)
  nil)
    



(defun-allowing-unwind search-for-module-truename
    (module overriding-pathname? current-kb-directory)
  (protected-let*
      ((saved-directories-for-module-truename-search
	 nil
	 (reclaim-saved-directories-for-module-truename-search
	   saved-directories-for-module-truename-search))
       (module-pathname-mapping?
	 (find-module-pathname-mapping-if-any module)
	 (reclaim-gensym-pathname module-pathname-mapping?))
       (module-as-pathname
	 (module-name-as-gensym-pathname module)
	 (reclaim-gensym-pathname module-as-pathname))
       (series-of-pathnames-to-merge
	 (nconc
	   (if overriding-pathname?
	       (gensym-list overriding-pathname?))
	   (if module-pathname-mapping?
	       (gensym-list module-pathname-mapping?))
	   (gensym-list module-as-pathname))
	 (reclaim-gensym-list series-of-pathnames-to-merge))
       (mapped-module-file-name
	 (merge-series-of-pathnames series-of-pathnames-to-merge)
	 (reclaim-gensym-pathname mapped-module-file-name)))	  
    ;; See if the mapped module name is in any of the directories
    ;; in our search path.
    (search-for-module-truename-in-various-places
      mapped-module-file-name current-kb-directory
      '(default-directory path-directories launch-directory))))

(defun search-for-module-truename-in-various-places
    (mapped-module-file-name current-kb-directory places)
  (loop for place in places
	thereis
	(search-for-module-truename-with-various-file-types
	  mapped-module-file-name current-kb-directory
	  place (file-types-for-module))))

(defun search-for-module-truename-with-various-file-types
    (mapped-module-file-name current-kb-directory place file-types)
  (loop for file-type in file-types
	thereis
	   (case place
	     (path-directories
	      (loop for directory-file-name in g2-module-search-path
		    thereis
		       (search-for-module-truename-in-directory
			 mapped-module-file-name file-type
			 directory-file-name)))
	     (t
	      (let ((directory-file-name?
		     (case place
		       (default-directory current-kb-directory)
		       (launch-directory
			process-specific-system-pathname))))
		(when directory-file-name?
		  (search-for-module-truename-in-directory
		    mapped-module-file-name file-type
		    directory-file-name?)))))))
	


;;; `Search-for-module-truename-in-directory' implements a case-insensitive
;;; probe-file operation in service of module-to-filename mapping.

(defun-allowing-unwind search-for-module-truename-in-directory
    (mapped-module-file-name file-type directory-file-name)
  (protected-let* ((directory-pathname
		     (gensym-pathname directory-file-name)
		     (reclaim-gensym-pathname directory-pathname))
		   (pathname
		     (gensym-merge-pathnames
		       mapped-module-file-name directory-pathname)
		     (reclaim-gensym-pathname pathname))
		   (pathname-with-type
		     (gensym-make-pathname :type file-type :defaults pathname)
		     (reclaim-gensym-pathname pathname-with-type))
		   (wild-name-pathname
		     (gensym-make-pathname :name :wild :type :wild :defaults pathname-with-type)
		     (reclaim-gensym-pathname wild-name-pathname))
		   (directory
		     (get-or-make-directory-for-module-truename-search wild-name-pathname)))
    (get-less-case-sensitive-gensym-pathname-given-directory
      pathname-with-type directory)))

;; It would be nice to improve this overall facility to cache directories around
;; repeated searches all for the same module load.  It would also be nice to
;; allow the load to be continued, from an open stream read past the initial
;; plist, rather than restarting the load from scratch after all the module
;; loading schedule has been determined.




;;; Create-module-loading-schedule ... returns a fresh gensym-cons `module loading
;;; schedule', describing modules to be loaded in order.  The "schedule" is is made up
;;; of gensym conses.  A module loading schedule is a list of the form
;;;
;;;    ( {module-load-request}+ )
;;;
;;; A `module load request' is a list of the form
;;;
;;;    (module-name truename? default-directory-pathname? requiring-module?)
;;;
;;; Truename? is nil if the request is pending; if it non-nil, then the request
;;; has been filled.  If it cannot be filled (and any level), this returns nil.

(defun give-module-not-found-warning
    (sought-after-module requiring-module?
			 top-level-module top-level-gensym-pathname)
  (let ((pathname-text-string 
	  (gensym-namestring-as-text-string top-level-gensym-pathname)))
    (notify-user
      "No KB file could be found for the module ~
       named ~a~a~a; cancelling the loading of ~a from ~s."
      sought-after-module
      (if requiring-module? ", required by " "")
      (or requiring-module? "")
      top-level-module
      pathname-text-string)
    (reclaim-text-string pathname-text-string)))


(defun non-reclaimable-pathname (a-pathname) 
  (or (eq a-pathname current-kb-pathname?)
      (eq a-pathname log-file-default-pathname?)
      (eq a-pathname current-attribute-file-pathname?)
      (eq a-pathname current-statistics-file-pathname?)
      (eq a-pathname current-foreign-image-pathname?)))

(defun reclaim-pathnames-in-loading-schedule (module-loading-schedule)
  (loop for list? in module-loading-schedule
	do
    (when (consp list?)
      (loop for text-string? in list?
	    do
	(when (text-string-p text-string?)
	  (reclaim-text-string text-string?)))
      (loop for pathname? in list?
	    do
	(when (and (gensym-pathname-p pathname?)
		   ;; don't reclaim it if others hold a pointer to it
		   (not (non-reclaimable-pathname pathname?)))
	  (reclaim-gensym-pathname pathname?))))))

(defun reclaim-module-loading-schedule (module-loading-schedule)
  (reclaim-gensym-tree module-loading-schedule))


(defvar modules-scheduled-so-far-by-save-all-modules-of-kb)
(defvar kb-module-currently-to-save? nil)


;;; Inhibit-modularity-consistency-checking? is bound globally to nil; it should
;;; only ever be bound otherwise by save-one-module-of-kb.  It is only ever used
;;; by save-kb, which uses it to decide not to check for module consistency when
;;; that is known not to be necessary.

(defvar inhibit-modularity-consistency-checking? nil)


(defvar current-module-directory-binding-alist)
(defvar current-module-pathname-override-binding-alist)

(defvar modules-scheduled-so-far)	; use for saving and loading

(defun create-module-saving-schedule
    (module current-default-pathname include-required? override-pathname? use-clear-text?
            only-changed-modules?)
  (update-g2-module-file-name-map)
  (let ((current-module-pathname-override-binding-alist
	  (if override-pathname?
	      (gensym-list (gensym-list module override-pathname?))))
	(current-module-directory-binding-alist nil)
	(modules-scheduled-so-far nil)
        (changed-modules (if only-changed-modules? (modules-with-unsaved-changes))))
    (create-module-saving-schedule-1 module current-default-pathname 
				     include-required? use-clear-text? t changed-modules)
    (loop for list in current-module-pathname-override-binding-alist
	  do (reclaim-gensym-list list))
    (reclaim-gensym-list current-module-pathname-override-binding-alist)
    (reclaim-gensym-list changed-modules)
    modules-scheduled-so-far))

(defun-void create-module-saving-schedule-1 (module current-default-pathname 
						    include-required? use-clear-text? top-module?
                                                    changed-modules)
  (unless (assq module modules-scheduled-so-far)
    (let ((module-information-instance?
	    (module-information-instance-for-module? module)))
      #+development
      (unless module-information-instance?
	(cerror "Go on"
		"Unable to find module-information table for module ~s."
		module))
      (when module-information-instance?
	(cond
	  ((module-hierarchy-contains-cyclic-dependency-p
	     module-information-instance?)
	   #+development
	   (cerror "Go on"
		   "Trying to save modules Which have a ~
                       cyclic dependency.")
	   (reclaim-gensym-tree modules-scheduled-so-far)
	   (setq modules-scheduled-so-far '()))
	  (t
	   (create-module-saving-schedule-2
	     module
	     current-default-pathname 
	     module-information-instance?
	     include-required?
	     use-clear-text?
	     top-module?
	     changed-modules)))))))



;see g2-stream-file-is-writable-p, which does not affect the file write date
;of an existing file.

(defun-allowing-unwind gensym-pathname-read-only-p (convertible-thing)
  (protected-let* ((gensym-truename?
		     (gensym-probe-file convertible-thing)
		     (reclaim-gensym-pathname gensym-truename?))
		   (truename-text-string?
		     (if gensym-truename?
			 (gensym-namestring gensym-truename?))
		     (reclaim-text-string truename-text-string?)))
    (and truename-text-string?
	 (not (g2-stream-probe-file-for-write truename-text-string?)))))

;; Written in order to be put in the PATHNAMES module.  Show this to JH! (MHD
;; 9/14/94)
	 

;;; Create-module-saving-schedule-2 ... pushes entries into modules-scheduled-so-far
;;; of the form
;;;
;;;    (module gensym-pathname read-only? module-that-requires-this?)
;;;
;;; Save-KB doesn't try to save, and doesn't mind not being able to save, files
;;; that are discovered to be read-only.

(defun create-module-saving-schedule-2
    (module current-default-pathname module-information-instance
	    include-required? use-clear-text? top-module?
            changed-modules)
  (let ((mapped-module-pathname?
	  (or (let ((entry? (assq module current-module-pathname-override-binding-alist)))
		(if entry? (copy-gensym-pathname (second entry?))))
	      (find-module-pathname-mapping-if-any module))))
    (when mapped-module-pathname?
      (gensym-push
	(gensym-list module mapped-module-pathname?)
	current-module-directory-binding-alist))
    (when include-required?
      (loop for required-module
		in (directly-required-kb-modules module-information-instance)
	    do (create-module-saving-schedule-1
		 required-module current-default-pathname 
		 include-required?
		 use-clear-text?
		 nil
	         changed-modules)))

    ; process only changed modules if changed-modules is not nil
    (when (or (not changed-modules) (memq module changed-modules))
      (let* ((clear-text-requested?
	    (or use-clear-text?
		(and (not top-module?)
		     (get-slot-value-if-any
		      (get-saving-parameters module)	 
		      'save-in-clear-text-by-default))))
	   (clear-text-prohibited?
	    (when clear-text-requested?
	      (not (null (module-contains-text-stripped-frames-p module)))))
	   (gensym-pathname
	     (make-module-pathname
	       module-information-instance
	       (second (first current-module-directory-binding-alist))
	       current-default-pathname 
	       mapped-module-pathname?))
	   (read-only?
	    (gensym-pathname-read-only-p gensym-pathname))
	   (source-code-control-troubles?
	    (will-cause-source-code-control-problems-if-saved-p gensym-pathname)))
      
      (gensym-push
	(gensym-list
	  module
	  gensym-pathname
	  read-only?
	  source-code-control-troubles?
	  clear-text-prohibited?)
	modules-scheduled-so-far)))
    (when mapped-module-pathname?
      ;; Call reclaim-gensym-pathname for the gensym-pathname in the
      ;; module-saving-schedule, then call reclaim-gensym-tree (ghw 2/6/96)
      (let ((module-saving-schedule
	      (gensym-pop current-module-directory-binding-alist)))
	(reclaim-gensym-pathname (second module-saving-schedule))
	(reclaim-gensym-tree module-saving-schedule)))))


(defun create-module-loading-schedule
    (gensym-pathname-to-read warmboot-case? update-before-loading? clear-kb?)
  (create-module-loading-schedule-0
    (make-module-name-from-kb-pathname gensym-pathname-to-read)
    gensym-pathname-to-read t gensym-pathname-to-read warmboot-case?
    update-before-loading? clear-kb?))



;;; Modules-considered-in-loading-schedule-so-far is used internally by
;;; create-module-loading-schedule-0.  It is a list of modules traversed, built
;;; out gensym conses.  Membership in the list acts as a mark on a node
;;; indicating that it's been traversed.  Create-module-loading-schedule-2
;;; pushes its module into this list before recurring on required modules.  This
;;; prevents infinite recursion in all cases, including the pathological case
;;; where more than one module might be mapped to the same KB file.

(defvar modules-considered-in-loading-schedule-so-far)


;;; Long-operation-posting-delay-for-module-loading-schedule-creation is used
;;; internally by create-module-loading-schedule-0 to determine how long it
;;; waits while making a schedule before putting up a notification, using the
;;; long-operation notification facility.  It defaults to 1000, which is in
;;; millisecond units.

(defparameter long-operation-posting-delay-for-module-loading-schedule-creation
  1000)

(defun-allowing-unwind create-module-loading-schedule-0
    (module current-kb-directory include-required? known-module-truename?
	    warmboot-case? update-before-loading? clear-kb?)
  (do-long-operation-with-notification ;   running the batch test
      (#w"Creating module loading schedule." t)
    (with-file-system-directory-search-cache () ; "*.k*" won't work for xml files.
      (protected-let ((saved-directories-for-module-truename-search
			nil ; alt. directory mechanism -- clean up! (MHD 5/31/95)
			(reclaim-saved-directories-for-module-truename-search
			  saved-directories-for-module-truename-search))
		      (modules-considered-in-loading-schedule-so-far
			nil
			(reclaim-gensym-list
			  modules-considered-in-loading-schedule-so-far)))
	(update-g2-module-file-name-map)
	(let ((current-module-directory-binding-alist nil)
	      (modules-scheduled-so-far nil))
	  (create-module-loading-schedule-1
	    module current-kb-directory include-required? known-module-truename?
	    nil warmboot-case? update-before-loading? clear-kb?)
	  (nreverse-canonically modules-scheduled-so-far))))))

(defun create-module-loading-schedule-1
    (module current-kb-directory include-required? known-module-truename?
	    requiring-module? warmboot-case? update-before-loading? clear-kb?)
  (put-up-long-operation-notification-if-timely
    long-operation-posting-delay-for-module-loading-schedule-creation)
  (unless (memq module modules-considered-in-loading-schedule-so-far)
    (create-module-loading-schedule-2
      module current-kb-directory include-required?
      known-module-truename? requiring-module? warmboot-case?
      update-before-loading? clear-kb?)))

(defun create-module-loading-schedule-2
    (module current-kb-directory include-required? known-module-truename?
	    requiring-module? warmboot-case? update-before-loading? clear-kb?)
  (let ((module-directory-binding?
	  (find-module-pathname-mapping-if-any module)))
    (when module-directory-binding?
      (gensym-push
	(gensym-list module module-directory-binding?)
	current-module-directory-binding-alist))
    (let* ((mapped-default-directory? nil)
	   (module-truename?
	     (or (when known-module-truename?
		   (copy-gensym-pathname known-module-truename?))
		 (multiple-value-setq-some (nil mapped-default-directory?)
		     (find-module-truename
		       module
		       (second (first current-module-directory-binding-alist))
		       current-kb-directory nil))))
	   (initial-kb-plist nil)
	   (module-scc-warning? nil)
	   (directly-required-modules nil))
      (multiple-value-setq (initial-kb-plist module-scc-warning?)
	(when module-truename?
	  (read-initial-plist module-truename?
			      update-before-loading?
			      (or (not clear-kb?) requiring-module?))))
      (set-initial-plist-for-loaded-module module initial-kb-plist)
      (setq directly-required-modules
	    (getf initial-kb-plist 'required-modules))
      (when (null initial-kb-plist)	; don't include if damaged (null plist)
	(setq module-truename? nil))
      (gensym-push module modules-considered-in-loading-schedule-so-far)
      (when include-required?
	(loop for required-module in directly-required-modules
	      do
	  (create-module-loading-schedule-1
	    required-module current-kb-directory
	    include-required? nil module warmboot-case? update-before-loading? clear-kb?)))
      (gensym-push
	(gensym-list module module-truename? mapped-default-directory? requiring-module?
		     module-scc-warning?)
	modules-scheduled-so-far))
    (when module-directory-binding?
      (reclaim-gensym-tree
	(gensym-pop current-module-directory-binding-alist)))))


(defun-allowing-unwind find-module-truename ; NEW
    (module relative-default-directory? current-kb-directory
	    overriding-pathname?)
  (protected-let*
      ((module-pathname-mapping?
	 (find-module-pathname-mapping-if-any module)
	 (reclaim-gensym-pathname module-pathname-mapping?))
       (module-as-pathname
	 (module-name-as-gensym-pathname module)
	 (reclaim-gensym-pathname module-as-pathname))
       (series-of-pathnames-to-merge
	 (nconc
	   (if overriding-pathname?
	       (gensym-list overriding-pathname?))
	   (if module-pathname-mapping?
	       (gensym-list module-pathname-mapping?))
	   (gensym-list module-as-pathname))
	 (reclaim-gensym-list series-of-pathnames-to-merge))
       (mapped-module-file-name
	 (merge-series-of-pathnames series-of-pathnames-to-merge)
	 (reclaim-gensym-pathname mapped-module-file-name))
       (series-of-directories-to-merge
	 (nconc
	   (if relative-default-directory?
	       (gensym-list relative-default-directory?))
	   (gensym-list current-kb-directory))
	 (reclaim-gensym-list series-of-directories-to-merge))
       (mapped-default-directory
	 (merge-series-of-pathnames series-of-directories-to-merge)))
    (values
      ;; See if the mapped module name is in any of the directories
      ;; in our search path.
      (search-for-module-truename-in-various-places
	mapped-module-file-name mapped-default-directory
	'(default-directory path-directories launch-directory))
      mapped-default-directory)))



;;; The system variable
;;; `pathname-with-default-type-if-required-for-module-pathnames?'  is used by
;;; make-module-pathname as the last entry in its series of pathnames to merge
;;; with the supplied pathname.  If non-nil, it should be a gensym pathname
;;; containing only the type to be used as the pathname component by default.
;;; The default binding for this is simply a pathname specifying the type "kb".

(def-system-variable
    pathname-with-default-type-if-required-for-module-pathnames?
    kb-merge
  (:funcall make-pathname-with-default-type-for-modules)
  nil nil reclaim-if-gensym-pathname)

(defun make-pathname-with-default-type-for-modules ()
  (gensym-make-pathname :type #w"kb"))

;; I'm specifying this as possibly nil, though in practice it will always be
;; non-nil.  Later, we may wish to parameterize this.  In particular, we could
;; allow pathnames that have no type whatsoever.  Likewise, we could allow some
;; other kind of default extension.  But no interface is being provided to
;; change this parameter at this time. (MHD 6/30/05)




(defun-allowing-unwind make-module-pathname
    (module-information-instance
      relative-default-directory-pathname? current-default-pathname 
      &optional override-pathname?)
  (protected-let*
      ((module (top-level-kb-module? module-information-instance))
       (module-as-pathname
	 (module-name-as-gensym-pathname module)
	 (reclaim-gensym-pathname module-as-pathname))
       (kb-module-file-name?		; a symbol or string
	 (kb-module-file-name? module-information-instance))
       (module-info-pathname-string?
	 (if kb-module-file-name?
	     ;; per convention, downcase if a symbol:  (MHD 9/8/94)
	     (if (symbolp kb-module-file-name?)
		 (copy-text-string-with-case-conversion
		   (symbol-name-text-string kb-module-file-name?)
		   :none)		; REVIEW SPEC FOR THIS
					;   ARG! (MHD 9/8/94)
		 (copy-text-string kb-module-file-name?)))
	 (reclaim-text-string module-info-pathname-string?))
       (module-info-pathname?
	 (when module-info-pathname-string?
	   (gensym-pathname module-info-pathname-string?))
	 (when module-info-pathname?
	   (reclaim-gensym-pathname module-info-pathname?)))
       (enough-pathname-of-module-loaded?
	 (get-enough-pathname-of-module-loaded-if-any module)
	 (reclaim-gensym-pathname enough-pathname-of-module-loaded?))
       (series-of-default-pathnames
	 (gensym-list
	   override-pathname?
	   module-info-pathname?
	   module-as-pathname
	   relative-default-directory-pathname?
	   ;; switching the previous and following forms would cause
	   ;; relative file renaming. (PGA 5/20/95)
	   enough-pathname-of-module-loaded?
	   current-default-pathname 
	   ;; Note: the following, supplying the default type (.kb), is
	   ;; primarily for the case when there's a module map and this module's
	   ;; entry lacks a type. Fix for HQ-5067338 "Save All Required Modules
	   ;; drops .kb extension when using a module map file".(MHD 7/1/05)
	   pathname-with-default-type-if-required-for-module-pathnames?)
	 (reclaim-gensym-list series-of-default-pathnames)))
    ;; series now has at least one element
    (merge-series-of-pathnames series-of-default-pathnames)))



;;; The function `make-pathname-for-saving-module' returns a pathname as
;;; follows.
;;;
;;; It is required that that this not be called unless (top-level-kb-module?
;;; module-information-instance) has a non-nil value.
;;;
;;; The non-nil elements of the following series of possible pathnames are
;;; merged successively, to produce a gensym pathname.  Note that the pathname
;;; produced still doesn't necessarily have all components specified, and is not
;;; necessarily an absolute pathname.  It is guaranteed, however, that it at
;;; least has a name component.
;;; 
;;;   (1) override-pathname?, if non-nil;
;;;   
;;;   (2) (kb-module-file-name? module-information-instance), if non-nil;
;;;
;;;   (3) the result of
;;;
;;;      (find-module-pathname-mapping-if-any
;;;        (top-level-kb-module?
;;;            module-information-instance))
;;;
;;;   if any;
;;;   
;;;   (4) the pathname containing just its directory component, taken from
;;;   directory-override-pathname?, provided it's non-nil;
;;;       
;;;   (5) the pathname containing just its name component, taken from
;;;   (top-level-kb-module?  module-information-instance), which cannot be nil;
;;;
;;;   (6) the pathname from which a module by this name was last loaded;
;;;
;;;   (7) the supplied default-pathname?, if non-nil
;;;
;;;   (8) the current KB pathname (the value of current-kb-pathname?)

	





;;; List-required-modules ... returns a gensym cons module's required modules,
;;; provided that module is the name of an existing module. Otherwise, it
;;; simply returns nil.  Note that module is never returned as a required
;;; module of itself.  Thus, this may return nil both in the case where
;;; module is not an existing module, and where module has not required
;;; modules.

(defvar modules-listed-so-far)

(defun list-required-modules (module)
  (let ((modules-listed-so-far nil))
    (list-required-modules-1 module)
    (delete-gensym-element module modules-listed-so-far)))

(defun list-required-modules-1 (module)
  (cond
    ((memberp module modules-listed-so-far))
    (t
     (let ((module-information-instance?
	     (module-information-instance-for-module? module)))
       (cond
	 (module-information-instance?
	  (setq modules-listed-so-far
		(gensym-cons module modules-listed-so-far))
	  (loop for directly-required-module
		    in (directly-required-kb-modules module-information-instance?)
		do (list-required-modules-1 directly-required-module))))))))

;; Code this more efficiently! (MHD 1/16/92)



#+development
(def-feature :compiled-code-loading-is-initially-enabled)

#+development
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :compiled-code-loading-is-initially-enabled *features*))

(defvar enable-loading-compiled-kbs-p
  #+compiled-code-loading-is-initially-enabled t
  #-compiled-code-loading-is-initially-enabled nil)

(eval-when (#-translating :compile-toplevel :load-toplevel :execute)
(defun-for-macro enable-loading-compiled-code-function ()
  'es-l-c)
)

(defun-for-system-procedure #.(enable-loading-compiled-code-function) ()
  (unless enable-loading-compiled-kbs-p
    (setq enable-loading-compiled-kbs-p t))
  (copy-evaluation-truth-value evaluation-true-value))

(defvar enable-saving-compiled-kbs-p nil) ; will be bound at each save
(defvar delete-compiled-kb-source-p nil)
(defvar loading-compiled-kb-p nil)





;;; Save-module-of-kb ... if include-required-modules? is true, this saves
;;; module and its required modules; otherwise, it just saves module.  This
;;; does not check the state of the system to see if saving of modules should
;;; be allowed; that is presumably done by the caller as well as by save-kb,
;;; which this eventually calls.  If module is not an existing module, this
;;; does nothing.
;;;
;;; If servicing a workstation (servicing-workstation? is true), and we're not
;;; processing the G2 init file ((not doing-g2-init-file-p)), this obtains
;;; confirmation prior to actually doing the save.  Otherwise, it just goes
;;; ahead, as though the confirm had happened.

(defun-allowing-unwind save-module-of-kb
    (default-pathname? module &optional include-required-modules?
		       use-clear-text? emit-c-code? commit-after-saving? only-changed-modules?)
  (protected-let* ((default-series
		       (nconc (if default-pathname? (gensym-list default-pathname?))
			      (gensym-list current-kb-pathname?))
		       (reclaim-gensym-list default-series))
		   (current-default-pathname
		     (merge-series-of-pathnames default-series)
		     (reclaim-gensym-pathname current-default-pathname))
		   (module-saving-schedule
		     (create-module-saving-schedule
		       module current-default-pathname
		       include-required-modules?
		       default-pathname?
		       use-clear-text?
		       only-changed-modules?)))
    (cond
      ((null module-saving-schedule)
       (notify-user
	 "The modules in this KB are not consistent; you ~
          therefore cannot save individual modules.  ~
          NO PART OF THIS KB HAS BEEN SAVED!"))
      ((and servicing-workstation?
	    (not doing-g2-init-file-p))	; and not during init file
       (post-module-schedule-dialog
	'saving module-saving-schedule
	(message-for-save-dialog module-saving-schedule)
	'save-modules-of-kb-after-confirmation
	(slot-value-list module-saving-schedule emit-c-code? commit-after-saving?)
	'reclaim-module-loading-schedule-and-representations-thereof
	(slot-value-list module-saving-schedule)))
      (t
       ;; No user -- just do it, as though already confirmed.  (This could
       ;; be the init file case.)
       (save-modules-of-kb-after-confirmation
	module-saving-schedule emit-c-code? commit-after-saving?)))))

(defun message-for-save-dialog (module-saving-schedule)
  (loop for (module truename? read-only? scc-problems? clear-text-problems?) in module-saving-schedule
	when read-only?
	  collect module into read-only-modules using gensym-cons
	when scc-problems?
	  collect module into scc-problem-modules using gensym-cons
	when clear-text-problems?
	  collect module into clear-text-problem-modules using gensym-cons
	finally
	  (return (prog1 (twith-output-to-text-string
			   (tformat "Save Modules as Shown?")
			   (when (or read-only-modules scc-problem-modules clear-text-problem-modules)
			     (tformat " (note ")
			     (when read-only-modules
			       (let ((one? (null (cdr read-only-modules))))
				 (tformat "that the module~a ~L,& will not be saved, because ~a read-only"
					  (if one? #w"" #w"s")
					  read-only-modules
					  (if one?
					      #w"its file is"
					      #w"their files are"))))
			     (when scc-problem-modules
			       (when read-only-modules
				 (tformat ", and also "))
			       (let ((one? (null (cdr scc-problem-modules))))
				 (tformat "that the module~a ~L,& can not be committed, ~
                                           because ~a already been committed by someone else"
					  (if one? #w"" #w"s")
					  scc-problem-modules
					  (if one?
					      #w"a newer revision has"
					      #w"newer revisions have"))))
			     (when clear-text-problem-modules
			       (when (or read-only-modules read-only-modules)
				 (tformat ", and also "))
			       (let ((one? (null (cdr clear-text-problem-modules))))
				 (tformat "that the module~a ~L,& will be not saved in clear text ~
                                           because ~a proprietary or text-stripped items"
					  (if one? #w"" #w"s")
					  clear-text-problem-modules
					  (if one? #w"it contains" #w"they contain"))))
			     (tformat ".)")))
		    (reclaim-gensym-list read-only-modules)
		    (reclaim-gensym-list scc-problem-modules)
		    (reclaim-gensym-list clear-text-problem-modules)))))





;;; Save-modules-of-kb-after-confirmation saves the modules in
;;; module-saving-schedule, after reclaiming (and deleting/removing from the
;;; screen) any displays of the schedule.  It also reclaims the argument
;;; module-saving-schedule after the saves have been launched.

(defun save-modules-of-kb-after-confirmation (module-saving-schedule emit-c-code? commit-after-saving?)
  (reclaim-any-module-schedule-displays)
  (let* ((saving-schedule module-saving-schedule)
         (need-to-reclaim? nil))
    (when (and (boundp 'current-workstation-event) current-workstation-event)
      (let* ((plist (workstation-event-detail current-workstation-event))
             (checkable? (getf plist 'checkable))
             (checked-items? (getf plist 'checked-items)))
        (when checkable?
          (setf saving-schedule
            (loop for num in checked-items?
                  collect (nth num module-saving-schedule) using gensym-cons))
          (setf need-to-reclaim? t))))
    (cond
      (saving-schedule
        (save-kb saving-schedule nil emit-c-code? commit-after-saving?)
        (when need-to-reclaim?
          (reclaim-gensym-list saving-schedule)))
      (t
        (message #w"There are no KB to save.")
        (notify-user "There are no KB to save."))))
  ;; The loop below reclaims the gensym-pathnames.  Reclaim-module-saving-schedule
  ;; simply calls reclaim-gensym-tree.  (ghw 2/6/96)
  (loop for (nil pathname) in module-saving-schedule
	do
    (reclaim-gensym-pathname pathname))
  (reclaim-module-saving-schedule module-saving-schedule))


;;; Save-one-module-of-kb ... saves module in pathname.  No confirmation is
;;; done.  No required modules of module are saved.  Pathname is absorbed
;;; by this function, so it should be copied if pointers to it are to be
;;; maintained.  If dont-check-consistency? is true, this inhibits the batch
;;; consistency check that's normally done for every save; this should only
;;; be called after a consistency check is known to have been done since
;;; the last time any changes to the KB (i.e., by the user) could have been
;;; done.  This is done, for example, when you are saving multiple modules
;;; after the first one has been saved, knowing that user interactions during
;;; or between module saves are disabled.

(defun save-one-module-of-kb (pathname module &optional dont-check-consistency?)
  (let ((kb-module-currently-to-save? module)	; special
	(inhibit-modularity-consistency-checking?
	  dont-check-consistency?))		; special
    (save-kb pathname 'kb-save)))



(defun reclaim-module-saving-schedule (module-saving-schedule)
  (reclaim-module-loading-schedule module-saving-schedule)) ; unkludge later!



;;; `Relations-with-related-items-in-modules-that-do-not-require-them' informs
;;; the user that the kb is inconsistently modularized because there is at least
;;; one item that participates in a permanent intermodule relationship, but that
;;; item is in a module that does not require the relation module.
;((relation (module item1)))
(def-kb-modularity-problem relations-with-related-items-in-modules-that-do-not-require-them
    nil nil (relation-and-related-items)
  (cond
    (inspect-command-for-modularity-problems?
     (loop with header  
	     = (if (or (cdr relation-and-related-items)
		       (cddr (car relation-and-related-items))
		       (cddr (cadar relation-and-related-items)))
		   (tformat-text-string
		     "The items below participate in permanent intermodule relationships ~
                  defined by the relation that follows them, but the items do not ~
                  reside in modules that require the relation module.")
		   (tformat-text-string
		     "The item below participates in a permanent intermodule relationship ~
                  defined by the relation that follows it, but the item does not ~
                  reside in a module that requires the relation module."))
	   with results = (eval-list header)
	   for (relation-frame . modules-and-items) in relation-and-related-items
	   do
       (loop for (relate-item-module . related-items) in modules-and-items
	     do
	 (loop for related-item in related-items
	       do
	   (eval-push related-item results)))
       (eval-push relation-frame results)
	   finally
	     (multiple-add-to-results-for-inspect-command
	       (nreverse results)
	       inspect-command-for-modularity-problems?)))
    (t
     (loop for (relation-frame . modules-and-items) in relation-and-related-items
	   do
       (with-user-notification ()
	 (tformat "The items listed below participate in permanent intermodule ~
                             relationships defined by the relation ~NF, but the items do not ~
                             reside in modules that require the relation module ~(~a~): "
		  relation-frame (get-module-block-is-in relation-frame))
	 (loop for first-module-p = t then nil
	       for (relate-item-module . related-items) in modules-and-items
	       do
	   (unless first-module-p (tformat ", "))
	   (tformat "(module ~(~a~)) " relate-item-module)
	   (loop for first-p = t then nil
		 for related-item in related-items
		 do (unless first-p (tformat ", "))
		    (tformat "~NF" related-item))))))))






;;; Check-savability-of-kb-in-terms-of-modularity ... returns true if the
;;; current KB has modularity information but there would be problems restoring
;;; it if it were saved out in its present state; otherwise, it returns nil.  As
;;; it find problems, it notifies the user of the specifics of the problem(s)
;;; found.

(defun check-savability-of-kb-in-terms-of-modularity
    (&optional inspect-command? for-save?)
  (when (kb-has-modularity-information-p)
    (do-modularity-checking (inspect-command?)
      (check-frame-note-based-modularity-problems
	'fatal
	'(circularity-in-module-hierarchy
	  modules-that-exist-are-not-required
	  workspaces-belong-to-unspecified-module
	  workspaces-belong-to-unrequired-modules
	  modules-required-by-kb-do-not-exist))
      (multiple-value-bind
	  (classes-not-defined-in-any-module ; straight class list
	    classes-whose-superiors-are-not-defined-in-required-modules
	    a-list-of-classes-with-instances-in-modules-that-do-not-require-them
	    a-list-of-relations-with-related-items-in-modules-that-do-not-require-them)
	  (collect-bad-definitions-for-kb for-save?) ; (MHD 1/25/94)
	(when classes-not-defined-in-any-module
	  (emit-kb-modularity-problem
	    'fatal 'classes-not-defined-in-any-module
	    classes-not-defined-in-any-module))
	(when classes-whose-superiors-are-not-defined-in-required-modules
	  (emit-kb-modularity-problem
	    'fatal 'classes-whose-superiors-are-not-defined-in-required-modules
	    classes-whose-superiors-are-not-defined-in-required-modules))
	(when a-list-of-classes-with-instances-in-modules-that-do-not-require-them
	  (emit-kb-modularity-problem
	    'fatal 'classes-with-instances-in-modules-that-do-not-require-them
	    a-list-of-classes-with-instances-in-modules-that-do-not-require-them))
	(when a-list-of-relations-with-related-items-in-modules-that-do-not-require-them
	  (emit-kb-modularity-problem
	    'fatal 'relations-with-related-items-in-modules-that-do-not-require-them
	    a-list-of-relations-with-related-items-in-modules-that-do-not-require-them)))

      ;; Check for cross-module entanglements between items and their table
      ;; representations.
      (loop for table being each class-instance of 'table
	    as workspace? = (get-workspace-if-any table)
	    when (and workspace?
		      (frame-of-class-p workspace? 'kb-workspace))
	      do (do-frames-this-represents (represented-frame table)
		   (unless (eq (get-module-block-is-in represented-frame)
			       (get-module-block-is-in table))
		     (setq current-modularity-problems-fatal? t)
		     (emit-kb-modularity-problem
		       'fatal 'table-in-different-module-than-item-represented
		       (gensym-list represented-frame workspace?)))))
      
      current-modularity-problems-fatal?)))






;;;; Creating New Top-Level KB Workspaces




;;; Make-new-top-level-kb-workspace does the following in order:
;;;
;;;   (1) creates a workspace of class kb-workspace;
;;;   (2) if transient? is true, sets the workspace transient; otherwise,
;;;       it sets the workspace to permanent and notes the workspace as a 
;;;       permanently changed block provided that noting-changes-to-kb-p
;;;       is true;
;;;   (3) if the system is running or paused, it activates the workspace;
;;;   (4) it assigns the workspace to module?, or if that's nil, to the
;;;       top-level module, i.e. (top-level-kb-module? module-information); 
;;;   (5) module-related frame notes everywhere are updated on exit; and
;;;   (6) the new workspace is returned

;;; Note that in cases where the creation of this workspace cannot affect the
;;; frame notes of any other frame in the system, then we suppress updates to
;;; module frame notes around the creation of the workspace, without using the
;;; macro version that actually updates those frame notes on exit from the form.

(defun make-new-top-level-kb-workspace (class &optional transient? name?
					      initial-subblock? width?
					      height? module?)
  (cond
    ((and transient?
	  (null name?)
	  (null initial-subblock?)
	  (null module?)
	  (null (frame-status-and-notes module-information))
	  (eq (top-level-kb-module? module-information)
	      (module-system-table-belongs-to? module-information)))
     (let ((inhibit-updating-module-related-frame-notes-for-all-workspaces? t))
       (make-new-top-level-kb-workspace-1
	 class transient? name? initial-subblock? width? height? module?)))
    (t
     (let ((new-kb-workspace 
	     (make-new-top-level-kb-workspace-1
	       class transient? name? initial-subblock? width? height? module?)))
;       (when g2-has-v5-mode-windows-p 
;	 (send-all-telewindows-new-kb-workspace-existence new-kb-workspace))
       new-kb-workspace))))

;; pbk 11/6/95 added hook to v5-mode-telewindows


(defun-simple make-new-top-level-kb-workspace-1
    (class transient? name? initial-subblock? width? height? module?)
  (let* ((do-not-note-permanent-changes-p t)
	 (workspace-margin
	   (if (or called-within-clear-text-loading
		   (and (user-defined-class-p class)
			(let ((default-workspace-margin
				  (slot-init-form
				    (slot-description-from-class
				      'kb-workspace 'workspace-margin)))
			      (class-specific-workspace-margin
				(slot-init-form
				  (slot-description-from-class
				    class 'workspace-margin))))
			  (/=f default-workspace-margin class-specific-workspace-margin))))
	       (slot-init-form
		 (slot-description-from-class class 'workspace-margin))
	       (get-slot-value
		 miscellaneous-parameters 'initial-margin-for-workspaces)))
	 (kb-workspace 
	   (make-workspace
	    class name? initial-subblock?
	    workspace-margin
	    (or width? 700)
	    (or height? 500)))
	(module-to-use?	    
	  (or module?
	      (top-level-kb-module? module-information))))
    (when (and (not transient?)
	       module-to-use?
	       (get-reason-module-is-not-editable module-to-use?)
	       (not (allow-unsavable-change-p module-to-use?)))
      (setq module-to-use? nil))
    (cond
      (transient?
       (set-transient-and-propagate kb-workspace nil))
      (t
       (set-permanent-block kb-workspace)
       (when noting-changes-to-kb-p
	 (set-block-permanently-changed kb-workspace))))
    
    (when (or system-is-running system-has-paused)
      (funcall-method 'activate-if-possible-and-propagate kb-workspace))
  
  ;; Make new workspaces be part of the "current module", if any:
  (when module-to-use?
    (change-slot-value
      kb-workspace 'module-this-is-part-of?
      module-to-use?))
  
  kb-workspace))


;; Parameterize the initial width/height of workspaces, perhaps with calls like
;; 
;;  (get-slot-value
;;    miscellaneous-parameters 'initial-width-for-workspaces)
;;  (get-slot-value
;;    miscellaneous-parameters 'initial-height-for-workspaces)
;;
;; See hint about this by miscellaneous parameters, also.  (MHD 12/19/91)
	      

;;;; Module Maintenence Utilities


;;; Get-module-block-is-in returns the module block resides in, if any.

(defun-simple get-module-block-is-in (block)
  (loop with following-junction-class-definition?	; use explained below
	  = nil
	with superior = block
	when (and (frame-of-class-p superior 'kb-workspace)
		  (null (parent-of-subworkspace? superior)))
	  return (module-this-is-part-of? superior)
	when (frame-of-class-p block 'system-table)
	  return (get-module-for-system-table block)
	while
	  (setq superior
		(or (superior-frame superior)
		    ;; Get module of associated connection
		    ;; definition if this is an object
		    ;; definition in limbo.  The following
		    ;; would not be reached unless superior
		    ;; were an item in limbo.  The following exits
		    ;; quickly if superior is not an object
		    ;; definition; otherwise, it visits, at
		    ;; worst, every connection definition.
		    (if (and
			  (or (frame-of-class-p superior 'object-definition)
			      (frame-of-class-p superior 'class-definition))
			  (not			; this test explained below
			    following-junction-class-definition?))
			(loop with class-defined?
				= (name-of-defined-class superior)
			      initially
				(when (null class-defined?) (return nil))
			      for class-definition
				  being each class-instance
				  of 'class-definition
			      when
				(if (frame-of-class-p class-definition 'connection-definition)
				    (eq (junction-block-class-for-connection
					  class-definition)
					class-defined?)
				    (and (memq 'connection
					       (class-inheritance-path-of-definition
						 class-definition))
					 (classp (name-of-defined-class class-definition))
					 (eq (class-slot-description-value
					       'junction-block-class-for-class
					       (name-of-defined-class class-definition))
					     class-defined?)))
				do (setq following-junction-class-definition? t)
				   ;; the above is to prevent infinite
				   ;; loops like j->c->wc-j, where j is the
				   ;; junction class def, c is the connection
				   ;; class def upon wc, and wc is a workspace
				   ;; that's a subworkspace of j.
				and return
				      (superior-frame
					class-definition)))))))






;;;; Wacko Definitions


;;; A `wacko definition' is a definition frame that
;;;
;;;    (1) is not transient-p
;;;    (2) has no superblock
;;;    (3) either
;;;       (a) has frame status other than nil (OK) or
;;;       (b) does not define a class that is the value
;;;           of some connection definition's
;;;           junction-block-class-for-connection.
;;;
;;; A wacko definition needs to be either deleted (if it has no instances)
;;; or put on a permanent KB workspace (if it has instances).
;;;
;;; Note that a wacko definition cannot belong to any module until it
;;; ceases to be wacko.




;;; Wacko-definition-p is true if definition is a "wacko definition".

(def-substitution-macro wacko-definition-p (definition class?)
  (and (not (transient-p definition))
       (null (superblock? definition))
       (or (neq (frame-status definition) nil)
	   (loop for definition being each class-instance of 'class-definition
		 for class-name = (name-of-defined-class definition)
		 never (and (classp class-name)
			    (memq
			      'connection (class-inheritance-path-of-definition definition))
			    (eq class?
				(class-slot-description-value
				  'junction-block-class-for-class class-name)))))))
		 



;;; Put-wacko-definition-on-kb-workspace ...

(defun put-wacko-definition-on-kb-workspace (wacko-definition)
  (let ((name-for-new-workspace
	  (intern-text-string 
	    (tformat-text-string "~NF-DEFINITION" wacko-definition))))
    (make-new-top-level-kb-workspace
      'kb-workspace nil name-for-new-workspace wacko-definition 50 50)
    (notify-user
      "The definition ~NF, which has one or more instances, has been ~
       put on the newly created KB workspace ~a."
      wacko-definition name-for-new-workspace)))

;; Add more explanatory text to the message above.  Note, however, that this
;; will happen only extremely rarely, if at all, ordinarily.

;; Wacko is a poor name! Think of a better one.  It is never to be shown to
;; the user, so the need is not very urgent.  

;; This is only called right now from fix-unimplemented-definitions, a
;; post-loading function in KB-LOAD2.  

;; This is a new that was added 2/5/92 and 2/6/92 by ML and MHD.  I added the
;; this "wacko" abstraction.  (MHD 2/6/92)

;; The functions above should be used when a "wacko definition" comes into
;; existence.  That is the plan; implement it!  Until then, people modularizing
;; will have to save as a single KB, load that in, and then save as a module!
;; (MHD 2/6/92)





;;;; Ghost Definitions



;;; `Write-ghost-definitions' is called by
;;; write-initial-sections-of-kb-to-first-checkpoint in the case of a modular
;;; save only (one in which only a portion of the entire KB is being saved).  It
;;; writes out certain definitions in class-hierarchical order.
;;; WRONG! See below -alatto, 12/23/04
;;; (An ordering of
;;; classes in which a class occurs prior to the occurance of any subclass.
;;; Such an ordering may be breadth- or depth-first.) The definitions are
;;; written without pointers to any other frames.  In particular, they are
;;; written as if without subworkspaces and superblocks.  The definitions
;;; written are exactly those that (1) have a subclass definition which is
;;; within the module being saved, or (2) have an instance which is within the
;;; module being saved.

;;; Actually, the ghost definitions are written in neither super-class first nor
;;; subclass-first order, presumably due to error. In particular, consider the case
;;; where there are two classes in a required module, one a subclass of the other,
;;; and an instance of the subclass is in the module being saved. Whether the subclass
;;; or the superclass is loaded first depends on whether the module being saved also
;;; includes a direct instance of the superclass.

;;; Since kbs have been saved with this buggy version of write-ghost-definitions, we
;;; have modified read-ghost-definitions to always install the definitions in superclass-first
;;; order, so that old kbs will always load correctly. This fixes bug
;;; Bug is HQ-4895236 Inconsistently modularized kb after merging modules.

;;; For consistency, we should probably change this to write the definitions in
;;; superclass-first order, the same order in which they should be loaded, which is
;;; also the order that non-ghost definitions are written. -alatto, 12/23/04

;;; Now changed so that definitions actually are written in superclass-before-subclass order,
;;; for consistency with the way every other kind of defintion is written. But note
;;; that they were written in inconsistent order for a long time, so the reading code should
;;; still strive to make no assumptions about the order in which the ghost definitions
;;; were written. -alatto, 12/28/04

;;; Note that this assumes that it can only be called in a consistently
;;; modularized KB.  It is an error to call this function when there are
;;; modularity constraint violations.

(defun write-ghost-definitions (module-being-saved)
  (loop with noting-changes-to-kb-p = nil
	with required-modules
	  = (list-required-modules module-being-saved)
	with required-definitions
	  = (collect-ghost-definitions module-being-saved required-modules)
	for definition in required-definitions
	
	initially
	  (reclaim-gensym-list required-modules)
	  (if required-definitions
	      (write-section-mark-for-kb #\1))
	  
	do (write-frame-for-kb definition t t)	; writes "as an ghost"
    
	finally
	  (if required-definitions
	      (write-section-mark-for-kb #\2))
	  (reclaim-gensym-list required-definitions)))

;; The markers changed from 1 and 2 to 3 and 4, respectively, for 4.0 KBs,
;; along with the kb flag stable-non-human-readable-kbs?.  (MHD 10/1/93)

;; Put into save-kb-2

(defun write-section-mark-for-kb (char)
  (start-new-kb-line)			; newline added in 3.0 for
  (write-char-for-kb #\*)		;  stable KB saving (MHD 10/1/93)
  (write-char-for-kb char))


(defvar required-definitions)
(defvar definitions-not-required)
(defvar connections-in-modules-a-list) ; a-list of (class . modules)

(defun collect-ghost-definitions (module-being-saved required-modules)
  (let* ((required-definitions nil)
	 (definitions-not-required nil)
	 (connections-in-modules-a-list
	   (get-connections-in-modules-a-list)))

    (loop for subclass being each subclass of 'block do
	  (collect-ghost-definition? subclass module-being-saved required-modules))

   (loop for definition in definitions-not-required
	 do (clear-second-definition-mark definition))
   (reclaim-gensym-list definitions-not-required)

   (loop for definition in required-definitions
	 do (clear-first-definition-mark definition))

   (reclaim-gensym-tree connections-in-modules-a-list)

   (nreverse required-definitions)))

;;; `Collect-ghost-definitions-1' collects every definition that is in a
;;; required module of the current module and is either in the inheritance
;;; path of some definition in the current module, or has a strict instance
;;; in the current module. All collecting is done by collect-ghost-definition,

;;; `Collect-ghost-definition?' Examines a definition, and determines whether
;;; this definition, and any superclasses of this definition, should
;;; be collected as ghost definitions. It is included as a ghost
;;; definition if it is in a
;;; required module of the current module and is either in the inheritance
;;; path of some definition in the current module, or has a strict instance
;;; in the current module.
;;; If it determines that a class
;;; should be collected, it does so by first
;;; marking that this definition is to be collected, using
;;; first-definition-mark, then
;;; recursively collecting any definition that should be read first (that
;;; is, superclass definitions, and classes of which this class is itself
;;; an instance), and then placing this class on the required-definition-list
;;; At the same
;;; time, if it determines that this class should not be included in the
;;; current module as a ghost definition, it
;;; marks it using the flag second-definition-mark, and
;;; collects it in the list definitions-not-required.


;;; This assumes that current-kb-save is bound, and that
;;;
;;;   (kb-module-being-saved? current-kb-save)
;;;
;;; points to the current module.

;;; These functions are subfunctions of collect-ghost-definitions.

;;; Note that these functions assume that they can only be called in a
;;; consistently modularized KB.  In particular, for each definition in the
;;; current module, the inheritance path (less itself) consists of 0 or more
;;; classes whose definitions belong to the current module, followed by 0 or
;;; more classes whose definitions belong to required modules, followed by some
;;; system defined classes.

;;; The function `collect-ghost-definition?' examines a class, and
;;; collects that class if it is not in the module but has instances in
;;; the module, or collects its superclasses not in the module
;;; if it is defined in this module.

;;; The function `collect-ghost-definition' does the actual collection,
;;; first collecting any classes that should be writted first; that is,
;;; superclasses and classes this is an instance of.

(defun collect-ghost-definition? (class module-being-saved required-modules)
  (let ((definition (class-definition class)))
    ;; The definition is for a defined user class in the current kb.
    ;; It will be given a second-definition mark and added to the
    ;; definitions-not-required list.
    (unless (or (not (user-defined-class-p class))
		(first-definition-mark-p definition)
		(second-definition-mark-p definition))
      (if
	(within-module-p definition module-being-saved)
	(progn
	  (set-second-definition-mark definition)
	  (gensym-push definition definitions-not-required)
	  ;; Any user-defined superior-to-subclass definitions that are not
	  ;; in the current kb must be collected.
	  (loop for inherited-class in (cdr (class-inheritance-path-of-definition
					      definition))
		for inherited-definition = (class-definition inherited-class)
		do
	    (when (and (user-defined-class-p inherited-class)
		       (not (within-module-p
			      inherited-definition
			      module-being-saved)))
	      (collect-ghost-definition inherited-class
					module-being-saved required-modules))))
	(when (and
		(within-modules-p definition required-modules)
		(strict-instances-within-module-p
		  class module-being-saved))
	  (collect-ghost-definition class
				    module-being-saved required-modules))))))


(defun collect-ghost-definition (class module-being-saved required-modules)
  (let ((definition (class-definition class)))
    #+development
    (when (second-definition-mark-p definition)
      (cerror "ignore it"
	      "Trying to collect a ghost definition for class ~A which we've already determined shouldn't have one collected"
	      (return-from collect-ghost-definition)))
    (unless (first-definition-mark-p definition)
      (set-first-definition-mark definition)
      (loop for inherited-class in (cdr (class-inheritance-path-of-definition
					  definition))
	    for inherited-definition = (when
					   (user-defined-class-p inherited-class)
					 (class-definition inherited-class))
	    do
	(when (and inherited-definition
		   (not (within-module-p
			  inherited-definition
			  module-being-saved)))
	  (collect-ghost-definition inherited-class
				    module-being-saved required-modules)))
      (let ((class-of-definition (class (class-definition class))))
	(when (user-defined-class-p class-of-definition)
	  (loop for defining-class in
	      (class-inheritance-path-of-definition
		(class-definition class-of-definition)) do
	    (when
		(user-defined-class-p defining-class)
	      (let ((defining-class-definition
			(class-definition defining-class)))
		(when
		    (and
		      (not
			(or (second-definition-mark-p defining-class-definition)
			    (within-module-p defining-class-definition module-being-saved)))
		      (within-modules-p defining-class-definition required-modules))
	      (collect-ghost-definition defining-class
					module-being-saved required-modules)))))))
      (gensym-push definition required-definitions))))



;;; `Get-connections-in-modules-a-list' creates an alist made up entirely
;;; of symbols and gensym conses.  Each entry is of the form
;;;
;;;    (connection-subclass . modules-list)
;;;
;;; where connection-subclass is a user-defined subclass of CONNECTION, and
;;; where modules-list is a list of modules (including the "module" nil, meaning
;;; the unassigned module) that contain either instances of connection-subclass
;;; or "pseudo instances", i.e., connection structures that are "for" that
;;; class.
;;;
;;; This produces an exhaustive list of entries in that each user-defined
;;; subclass of connection has an entry and that all of the modules in which its
;;; instances or pseudo-instances reside.
;;;
;;; This is intended to be called in order to set up the special variable
;;; `connections-in-modules-a-list', which is bound and reclaimed when collecting
;;; ghost definitions and when checking for module consistency.
;;;
;;; `Strict-instances-within-module-p' checks if class has instances in module,
;;; using the a-list connections-in-modules-a-list if appropriate for
;;; connections, and checking in more traditional ways for other kinds of
;;; block subclasses.

(defun get-connections-in-modules-a-list ()
  (let ((a-list
	  (loop for class being each subclass of 'connection
		when (user-defined-class-p class) 
		  collect (gensym-list class)
		    using gensym-cons)))
    (loop for b being each class-instance of 'block
	  ;; assuming output direction reaches all connections eventually:
	  do (loop for c being each output-connection of b
		   as connection-frame-or-class = (connection-frame-or-class c)
		   as class = (if (symbolp connection-frame-or-class)
				  connection-frame-or-class
				  (class connection-frame-or-class))
		   as entry? = (and (user-defined-class-p class)
				    (assq class a-list)) ; if here, can't fail
		   when entry?
		     do (gensym-pushnew
			  (get-module-connection-is-in c)
			  (cdr entry?))))
    a-list))

;; Could the traversal over all blocks be piggybacked on top of
;; some other one as an optimization?! (MHD)


(defun strict-instances-within-module-p (class module)
  (if (subclassp class 'connection)
      (memq module (cdr (assq class connections-in-modules-a-list)))
      (loop for instance being each strict-class-instance of class
	    thereis (within-module-p instance module))))



;;; The function `connection-class-is-instantiated-p' returns a non-null value
;;; when there exists a connection-frame with a connection-frame-or-class
;;; component that is a either a class-instance of the connection-class or
;;; names a subclass of the connection-class; otherwise, it returns nil.

(defun-simple connection-class-is-instantiated-p (connection-class)
  (loop for block being each class-instance of 'block
	thereis
	(loop for connection being the output-connections of block
	      thereis
	      (let ((frame-or-class (connection-frame-or-class connection)))
		(subclassp
		  (if (framep frame-or-class)
		      (class frame-or-class)
		      frame-or-class)
		  connection-class)))))
	       



;;; Collect-bad-definitions-for-kb ... returns three values, which
;;; must be reclaimed by the user.  Each value is made up of recyclable
;;; gensym conses.  The third and fourth values are a-lists containing
;;; non-top-level conses.  Note that the first value, definitions-not-in-
;;; any-module, implies that ALL instance of each such definition are
;;; not savable, since the definition itself is unsavable.
;;;
;;; 
;;;
;;;    (1) classes-not-defined-in-any-module; 
;;;    (2) classes-whose-superiors-are-not-defined-in-required-modules; and
;;;    (3) a-list-of-classes-with-instances-in-modules-that-do-not-require-them
;;;    (4) a-list-of-relations-with-related-items-in-modules-that-do-not-require-them
;;;
;;; Unless this is being called from saving a module of a KB, this puts up a
;;; long-operation notification, since it can take many seconds.

(defvar classes-not-defined-in-any-module)
(defvar classes-whose-superiors-are-not-defined-in-required-modules)
(defvar a-list-of-classes-with-instances-in-modules-that-do-not-require-them)
(defvar current-linearized-kb-required-modules)
(defvar a-list-of-relations-with-related-items-in-modules-that-do-not-require-them)

(defparameter long-operation-posting-delay-for-kb-modularity-consistency-check 1000)

(defun-allowing-unwind collect-bad-definitions-for-kb (&optional secretly?)
  (if secretly?				; if we are saving, don't
      (collect-bad-definitions-for-kb-1) ;   notify the user that we're 
      (do-long-operation-with-notification ;   running the batch test
	(#w"Checking definitions in this KB for consistency of modularity." t)
	(collect-bad-definitions-for-kb-1))))




;;; Collect-bad-definitions-for-kb-1 is just a subfunction of collect-bad-
;;; definitions-for-kb.

(defun collect-bad-definitions-for-kb-1 ()
  (let* ((classes-not-defined-in-any-module nil)
	 (classes-whose-superiors-are-not-defined-in-required-modules nil)
	 (a-list-of-classes-with-instances-in-modules-that-do-not-require-them nil)
	 (connections-in-modules-a-list	; FIX TO USE THIS!!!!!!!
	   (get-connections-in-modules-a-list))
	 (a-list-of-relations-with-related-items-in-modules-that-do-not-require-them nil))
    (propagate-modules-to-subworkspaces)
    (with-module-required-by-relationships
	(collect-bad-definitions)
        (collect-potentially-unreloadable-permanent-relationships))
    (unpropagate-modules-to-subworkspaces)
    (reclaim-gensym-tree connections-in-modules-a-list)
    (values
      classes-not-defined-in-any-module
      classes-whose-superiors-are-not-defined-in-required-modules
      a-list-of-classes-with-instances-in-modules-that-do-not-require-them
      a-list-of-relations-with-related-items-in-modules-that-do-not-require-them)))




;;; The macro `instance-and-definition-modularity-problem-p' is used to
;;; determine whether a class-instance is in a module that requires the module
;;; of its class-definition or if an item involved in a permanent intermodule
;;; relationship is in an module that requires the relation module.
;;;
;;; Note that instances that either are transient, are
;;; neither-permanent-nor-transient, or have their do-not-save-in-kb frame flag
;;; set are exempt from the requirement that they be be in a module that
;;; requires their definition's module (or even to be in any module at all:
;;; i.e., they can be in limbo).
;;;
;;; Here are some oddball cases to keep in mind:
;;;
;;;   (a) autocreated G2-window instances (or instances of subclasses of
;;;   g2-window) are permanent but have their do-not-save-in-kb flag set, and
;;;   therefore are exempt;
;;;
;;;   (b) procedure-invocation instances are transient, have their
;;;   do-not-save-in-kb flag clear; and
;;;
;;;   (c) autocreated GSI-interface instances created via
;;;   gsi_initiate_connection() with the keep_connection argument TRUE are
;;;   neither permanent nor transient, and have their do-not-save-in-kb flag
;;;   clear.

(defmacro instance-and-definition-modularity-problem-p
    (instance module-for-definition?)
  `(and (and (permanent-block-p ,instance) (not (do-not-save-in-kb-p ,instance)))
	(let ((module-for-instance? (efficient-get-module-block-is-in ,instance)))
	  (not (or (eq ,module-for-definition? module-for-instance?)
		   (efficient-module-required-by-module-p
		     ,module-for-definition? module-for-instance?))))))




;;; The function `collect-bad-definitions' checks each user-defined class
;;; definition for modular consistency in three areas: (1) if a definition lacks
;;; a module assignment, the class name is placed on the classes-not-defined-
;;; in-any-module list; (2) if the direct-superiors of the class are not defined
;;; in any required module, the class is placed on the classes-whose-superiors-
;;; are-not-defined-in-required-modules list; and (3) if there are class
;;; instances that do not appear in any required module, the class name and
;;; instances are placed on the a-list-of-classes-with-instances-in-modules-
;;; that-do-not- require-them list.

;;; This function contains a call to put-up-long-operation-notification-if-timely.

(defun collect-bad-definitions ()
  (loop for class being each subclass of 'block
	for class-definition = (class-definition class)
	do
    (put-up-long-operation-notification-if-timely
      long-operation-posting-delay-for-kb-modularity-consistency-check)
    (cond
      ((class-definition-is-frame-p class-definition)
       (let ((module-for-definition?
	       (efficient-get-module-block-is-in class-definition)))
	 (cond
	   ((null module-for-definition?)
	    (gensym-pushnew
	      class classes-not-defined-in-any-module))
	   (t
	    (let ((module module-for-definition?))
	      ;; set up efficient way to test for each module M:
	      ;;    (module-requires-module-p module M)
	      (propagate-module-requires-module-p-to-all-modules module)
	      (loop for direct-superior in (direct-superior-classes class)
		    for direct-superior-class-definition
			= (class-definition direct-superior)
		    do
		(when (class-definition-is-frame-p
			direct-superior-class-definition)
		  (let ((module-for-superior-definition?
			  (efficient-get-module-block-is-in
			    direct-superior-class-definition)))
		    (unless (and module-for-superior-definition?
				 (or (eq module
					 module-for-superior-definition?)
				     (efficient-module-requires-module-p
				       module
				       module-for-superior-definition?)))
		      (gensym-pushnew
			class
			classes-whose-superiors-are-not-defined-in-required-modules)
		      (loop-finish)))))

	      (loop for instance being each strict-class-instance of class
		    for workspace-of-instance = (get-workspace-of-thing-if-any instance)
		    ;; GENSYM-1925: protect the frame for undo cause the problem when saving kb
		    when (and (not (frame-serial-number-equal (frame-serial-number instance)
							      (frame-serial-number-recycled)))
			      ;; GENSYMCID-790: Delete workspace results in inconsistent modularization problems.
			      (not (and workspace-of-instance
					(frame-serial-number-equal (frame-serial-number workspace-of-instance)
								   (frame-serial-number-recycled))))
			      (instance-and-definition-modularity-problem-p
				instance module-for-definition?))
		      collect instance into result using gensym-cons
		    finally
		      (when result
			(gensym-push
			  (gensym-cons class result)
			  a-list-of-classes-with-instances-in-modules-that-do-not-require-them
			  )))))))))))




;;; The function `collect-potentially-unreloadable-permanent-relationships'
;;; detects types of permanent intermodule relation situations that
;;; make the kb inconsistently modularized and therefore would jeopardize
;;; successful kb saving and loading.

;;; An item participates in a permanent intermodule relationship, but,
;;; the item is in a module that does not require the relation module.
;;;
;;; Note that only permanent instances have this requirement.  Both transient
;;; and neither-permanent-nor-transient instances are exempt.

(defun collect-potentially-unreloadable-permanent-relationships ()
  (propagate-kb-requires-module-p-to-all-modules)
  (loop for subject-block being each class-instance of 'block
	for relation-instances = (relation-instances subject-block)
	when relation-instances
	do
    (loop for relation-instance being each relation-instance of relation-instances
	  for relation-name = (relation-instance-name relation-instance)
	  for relation-frame = (relation-instance-relation relation-instance)
	  for object-block-list = (relation-instance-items relation-instance)
	  when (and (relation-is-permanent relation-frame)
		    (permanent-block-p relation-frame)
		    (relation-name relation-frame))
	    do (let ((module-for-relation? (efficient-get-module-block-is-in relation-frame)))
		 (note-item-used-by-relation subject-block relation-frame module-for-relation?)
		 (loop for object-block being each related-item of object-block-list
		       when object-block do
		   (note-item-used-by-relation object-block relation-frame module-for-relation?))))))

(defun-simple note-item-used-by-relation (block relation module-for-relation?)
  (unless (and (permanent-block-p block) (not (do-not-save-in-kb-p block)))
    (return-from note-item-used-by-relation nil))
  (let ((module-for-instance? (efficient-get-module-block-is-in block)))
    (unless (or (eq module-for-relation? module-for-instance?)
		(efficient-module-required-by-module-p module-for-relation? module-for-instance?))
      (let ((a1 (assq relation a-list-of-relations-with-related-items-in-modules-that-do-not-require-them)))
	(unless a1
	  (setq a1 (gensym-cons relation nil))
	  (gensym-push a1 a-list-of-relations-with-related-items-in-modules-that-do-not-require-them))
	(let ((a2 (assq module-for-instance? (cdr a1))))
	  (unless a2
	    (setq a2 (gensym-cons module-for-instance? nil))
	    (gensym-push a2 (cdr a1)))
	  (unless (memq block (cdr a2))
	    (gensym-push block (cdr a2)))))
      t)))






;;;; Notes on 4.0 Module Saving and Releated Issues

;; Mark H. David, January, 1994

;;; While saving a modularized KB while running, you set up a save context for
;;; every module in the KB.  Some of these save contexts have "bitsinks" as
;;; their destination streams.  Only a small amount of low-level code has to
;;; be aware of the fact that a kb-save-state is for a bitsink, as opposed
;;; to a real stream.  (It is important, however, that users aren't mislead
;;; into thinking that a file is being saved if they did not request it.)
;;;
;;; 
;;; Upsets to Saving Modules
;;;
;;; 0. Making an item, and its inferiors, permanent by transferring it
;;;    to a permanent workspace from a transient one while snapshotting.
;;;    - not a problem: this is already handled -- unfortunately, this
;;;    requires that G2 save out every single inferior before coming up
;;;    for a breath of air.
;;;
;;; 1. Transfer of an item from one module's workspace to another's.
;;;    - the problem is that the items _underneath_ the transferred
;;;    item must be written out right away; otherwise, you will have
;;;    trouble later identifying the module they belong to, e.g., if
;;;    they are changed and need to be written out.
;;;    - solution: treat the same way as you'd tread a transfer from
;;;    a transient to a non-transient workspace
;;;    - drawback: low performance -- may require entire module to
;;;    be written out without coming up for air
;;;    - answer to drawback: this could have happened before with
;;;    the type of transfer we're emulating.
;;;    - implementation: change add-as-inferior-block, create
;;;    a variation of it;  review all of its (other) callers
;;;    - remarks: transfers to limbo are not possible for permanent
;;;    items; transfers to limbo are only possible from actions
;;;    at present; transfers from permanent items to transient ones
;;;    are not possible, either from actions or from the mouse/menu
;;;
;;; 2. Transfer of an item from a module to a non-module.
;;;    - solution: handle as variation of 0./1.
;;;
;;; 3. Change module assignment on a top-level kb-workspace.
;;;    - problem is that all of the inferiors of that workspace
;;;    must be able to know which module they belong to -- saving
;;;    them all at once before the change is one way to make this
;;;    happen
;;;
;;; 4. Deletion of a module.
;;;
;;; 5. Changing a definition.
;;;   - not handled anyway?
;;;
;;; 6. Computation-style and format-frame instances keep the list of modules
;;; they've been written in.  They are then saved only when they're pointed to.
;;; They no longer are all saved in their own section at the top of the KB.  The
;;; constraint on this is that these instance may never point to other frames, or
;;; at least not unless we engineer some way to make those other frames fit into
;;; the traversal hierarchy.
;;;
;;; 7. Changed (default-priority-for-runtime-saving attribute) to 2, from 8.  Fix
;;; documentation!  Review.

;;; MISC. ISSUES
;;;
;;; 1. Why is the priority for saving while running set so low (8).  In a KB such
;;; as MILL, it appears to make no progress during for a long period of time (>
;;; 1 minute) with this setting.  Defaulting it to 2 would seem a wiser thing to
;;; do.  It's probably not a good idea to default anything to 1, the highest
;;; priority.
;;;
;;; Recommendation: change default for the journal-priority slot
;;; (default-priority-for-runtime-saving attribute) to 2, from 8.
;;; DONE.
;;;
;;; 
;;; 2. Why is handle-connection-post-addition-or-removal-as-subblock handled only
;;; for transfer-grouped-blocks-with-their-external-connections by hand?
;;;
;;; Recommendation: put this in add-subblock/remove-subblock.
;;;
;;;
;;; 3. Make-workspace ... 
;;;
;;; Recommendation: In initial-subblock? case, call transfer-item instead of
;;; explicitly calling add-subblock, etc.  Then, having eliminating its one
;;; caller, jetison add-loose-ends-as-subblocks-and-shift.
;;;
;;; 4. Why does note-change-to-block (note-change-to-block-2) do a single step
;;; in the traversal of the KB below the block its in.  Why is this necessary?
;;; Why not go all the way down to the bottom?  Why is this not done for deletion
;;; of a block?  Or for deletion or slot change of a connection?
;;;
;;; 5. How does a KB subhierarchy get saved in the event of a deletion when
;;; saving while running?  Here's how:
;;;
;;;    B1 is a workspace, a superblock of b2-1, b2-2, b2-3.  has a subworkspace,
;;;    b3-1.
;;;
;;;    delete-frame (B1)
;;;      -> note-deletion-of-block (B1)
;;;         -> write-block-as-it-is-now (B1)
;;;            -> ... -> write-reference-to-block (b2-1)
;;;                   -> write-reference-to-block (b2-2)
;;;                   -> write-reference-to-block (b2-3)
;;;      -> delete-frame (b2-1)
;;;        -> note-deletion-of-block (b2-1)
;;;         -> write-block-as-it-is-now (b2-1)
;;;            -> ... -> write-reference-to-block (b3-1)
;;;         -> delete-frame (b3-1)
;;;           -> note-deletion-of-block (b3-1)
;;;            -> write-block-as-it-is-now (b3-1)
;;;      -> delete-frame (b2-2)
;;;        -> note-deletion-of-block (b2-2)
;;;         -> write-block-as-it-is-now (b2-2)
;;;      -> delete-frame (b2-3)
;;;        -> note-deletion-of-block (b2-3)
;;;         -> write-block-as-it-is-now (b2-3)
;;;
;;;  Thus, everything is written withing the recursive descent of delete-frame
;;;  (b1), not in the recursive descent of note-deletion-of-block.  We're
;;;  depending then on delete-frame to walk the same KB subhierarchy as
;;;  traverse-kb-for-saving would walk, and to delete every node it it
;;;  encounters in that walk.
;;;
;;;  6. Note-{change|deletion|}-for-{block|connection} and write-{connection|block}-
;;;  as-it-is-now were overlapping continue-current-save-or-backup.  I combined
;;;  them, eliminating the two write-...-as-it-is-now functions, and much other
;;;  code.
;;;
;;;  7. Runtime data for definitions written when the definition is encountered
;;;  in the traversal under the workspace hierarchy.
;;;
;;;  8. Frame reference mark is no longer set when the frame is written.  If a
;;;  frame has never been written or referenced, a forward reference (G) is
;;;  written and the frame reference balance is incremented.  When a frame is
;;;  written, if it has been referenced, the frame reference balance is
;;;  decremented.  This will uncover all unresolved references.  This has been
;;;  simplified by not recording a reference every time a frame is written.
;;;  The one thing that's now odd is that we must still set the referenced
;;;  bit on definitions when writing them in the definitions section, and also
;;;  increment the frame reference balance at this time.
;;;
;;;  9. Why is transient not a flag defined for connections?  See
;;;  collectable-connection-p.
;;;
;;;  10. At present, we don't reclaim the list of modules on format frames or
;;;  computation styles until the next save.
;;;
;;;  11. The way we initialize written/referenced flags makes us be commited
;;;  to the new recursive write of format frames & computation styles.
;;;
;;;  12. What about note-change-of-text-slot, called from change to text list
;;;  structure out of try-to-finish-editing.  It doesn't seem to get the frame
;;;  saved?!  What about note-kb-state-change-to-slot-by-saving-text?!



;;; BUGS
;;;
;;; 1. Add-Subblock Bug
;;; 
;;; Add-subblock, when called with the following condition false, splices in the
;;; subblock without first writing out the subblocks slot "as it is now".
;;; 
;;;    (or (opaque-block-p block)
;;;        (null (subblocks superblock))
;;;        (not (opaque-block-p (first-subblock superblock))))
;;;
;;; This means that it gets by on the skin of its teeth _most_ of the time, that is
;;; by virtue of the fact that (not (opaque-block-p (first-subblock superblock))), or
;;; that the first subblock is usually not an opaque block.
;;;
;;; To get a bug, then, all you have to do is add a block to a workspace that only
;;; contains an opaque block (e.g., a graph).
;;;
;;; (Is this new for 4.0?  Conceivably Ben made changes that brought this about.
;;; -- ANS: yes)
;;;
;;; I think the fix is:
;;;
;;; (FIX 1) add the form
;;;
;;;    (note-change-to-block superblock 'subblocks)
;;;
;;; to the code just before the list splicing happens.
;;; 
;;; OR:
;;;
;;; (FIX 2) consider adding this as a job that add-as-inferior-block does, but
;;; then call that first, prior to operating on the subblocks list.
;;;
;;; For now, I'll do (FIX 1), since it rolls us back to the 3.0 functionality at
;;; least.  (MHD 1/19/93)
;;;
;;;
;;; 2. How is transferring off handled?  Oh, I know: you can't transfer off from
;;; an action with a permanent item.  You can't transfer off by hand (from the
;;; mouse/menu/ui) at all.










;;; More stuff

;; 1. Proprietary (including private) workspaces should not be
;;    journalled. Nothing should be added to them, because
;;    thses things cannot be saved. (But savable subworkspaces
;;    can be journalled.) There may be a clipping problem here.

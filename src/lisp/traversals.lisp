;; -*- Mode: Lisp; Package:AB; Base: 10; Syntax: Common-lisp -*-
(in-package "AB")

;;;; Module TRAVERSALS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Michael Levin


;;; This file contains functions that are logically part
;;; of FILES or JOURNALS, but needs to be put later in the
;;; sequence of modules because of certain macro problems.



;; To CELLS
;; (declare-forward-reference traverse-computation-style-for-backup function)



;;; Traversal for backup


;; Will clip transients.
;; Does not enumerate transients.
;; Does not deal with transient workspaces.
;; Does not look at what has been modifed.
;; Does not deal with transfers.
;; Does not deal with any changes to savable-kb-workspace-p. 


(defvar attributes-collector)
(defvar attributes-collector-tail)






;;; `traverse-kb-for-saving' is used to traverse the hierarchy of all savable
;;; blocks and connection-structures.

;;; The tree consists of symbols, blocks, and connection-structures and observes
;;; the following constraint:
;;;
;;;    Let the nodes have values as follows:
;;;    
;;;      V(symbol) = 3;
;;;      V(permanent block) = 2;
;;;      V(permanent connection-structure) = 2;
;;;      V(transient block) = 1;
;;;      V(transient conection-structure) = 1
;;;
;;;    Then node N along any path starting from the root node
;;;    has non-increasing values of V(N).

;;; The value of traverse-kb-for-saving for any node of the tree is a
;;; journal-list of its immediate inferiors.  For an example of how this is used
;;; to accomplish traversal, see continue-current-kb-save-or-backup.

;;; The traversal is modified by the state of current-saving-context and
;;; current-kb-save, always bound when this is called, as follows.
;;;
;;; If (save-runtime-data? current-saving-context), then the traversal includes
;;; all of the above.  Otherwise, it terminates above nodes whose value is 1.
;;;
;;; If (kb-module-being-saved? current-kb-save) is non-nil, then the save is
;;; module-specific, and traversal is restricted to that module.  A module is a
;;; subset of the complete traversal that includes only those top-level
;;; kb-workspaces that bear the module name, and only those definitions which
;;; are inferior (hierarchically) to those kb-workspaces.  Module traversal must
;;; not be used in conjunction with traversing transients.

;;; At present, traverse-kb-for-saving does not serve connection frames if
;;; has-slot-values-to-save-p is nil.  This is correct behavior for saving, and
;;; is in synch with write-connection-for-kb, which writes a symbol rather than
;;; a frame reference in the slot connection-frame-or-class.  But for other
;;; uses, such as activation, this behavior must be filtered out.

;;; Similarly, it does not serve attributes for which has-slot-values-to-save-p
;;; is nil.  This works differently, in that pointers to these attributes will
;;; be saved.  The empty frame created by this pointer will have its parent info
;;; filled in by put-attribute, and nothing else should be needed to make the
;;; frame usable.

;;; When (save-runtime-data? current-saving-context) is true, the behavior
;;; described above is inhibited, and all savable frames are written.  This is
;;; incompatible with saving any one module, so it is an error for the save to
;;; be module-specific when this flag is true.  (See has-slot-values-to-save-p.)

;;; The traversal description above is not completely accurate in that each
;;; definition is accessed twice in the traversal.  (This does not happen to
;;; format-frames, computation-styles, and system-frames because they are not
;;; encountered on the kb-workspace portion of the traversal.)
;;;
;;; The calling function, continue-current-kb-save-or-backup, deals with this by
;;; looking below a definition only when it is encountered for the second time,
;;; which is when (finished-writing-definitions? current-kb-save) is true.

;;; The constant `top-level-kb-elements-for-saving' contains the top-level list
;;; of elements for saving, in the order in which they must be traversed.  This
;;; list is to be traversed to from the top-level node :KB.  If the order of
;;; this list changes, review traverse-kb-for-saving and
;;; write-kb-traversal-state-node.

(defconstant top-level-kb-elements-for-saving
  '(:system-frames
    :definitions
    :top-level-workspaces
    :transient-items-in-limbo))		; ??

(defun traverse-kb-for-saving (tree)
  (cond
    ((symbolp tree)
     (case tree
       (:kb (copy-list-using-journal-conses top-level-kb-elements-for-saving))       
       (:system-frames (traverse-system-frames-of-kb-for-saving))       
       (:definitions (traverse-definitions-of-kb-for-saving))       
       (:top-level-workspaces (traverse-top-level-workspaces-of-kb-for-saving))
       (:transient-items-in-limbo (traverse-transient-items-of-kb-for-saving))
       (t
	;; must be a class
	(unless (eq tree 'procedure-invocation)
	    ;; Procedure-invocations are never saved unless they are referenced.
	    (traverse-transient-class-instances-of-kb-for-saving tree)))))
    ((connection-p tree) nil)
    (t
     ;; must be a block
     (traverse-block-for-saving tree))))

;; It would be nice if this could be toggled to walk even the parts of the KB
;; that are in ML's "other" catagory, i.e. (not (or permanent transient)). - ben
;; 1/10/92

;; Note that you can have a substantial proportion of the KB in the :definitions
;; section since definitions can have subworkspaces. - ben 1/10/92

;; If you use this to traverse the entire KB you will visit some frames more
;; than once.  The only examples I know of are because of the structure that can
;; appear below class definitions.  - ben 1/10/92





(defun traverse-system-frames-of-kb-for-saving ()
  (loop for frame being each class-instance of 'system-frame
	when (and (if (kb-module-being-saved? current-kb-save)

		      ;; If saving a module, only save if frame is
		      ;; in the current module being saved.
		      (within-module-p
			frame
			(kb-module-being-saved? current-kb-save))

		      ;; Otherwise, save out just about every system table.
		      ;; The following should actually only exclude a
		      ;; module-information instance having its module
		      ;; name typed into the editor -- rare.  Notice
		      ;; that non-installed system tables belong
		      ;; to some module.
		      (or (system-table-installed-p frame)
			  (module-system-table-belongs-to? frame)))
		  (has-slot-values-to-save-p
		    frame
		    '(name-or-names-for-frame ; always 1:1 with class name
		      
		      this-system-table-is-installed? ; derived upon reading
		      module-system-table-belongs-to?

		      ;; Don't need this slot because system tables cannot
		      ;; be on workspaces:
		      slot-group-for-block?)))
	  collect frame using journal-cons))



;;; `Within-module-being-saved-p' is true if either the current save is not for
;;; a particular module ((kb-module-being-saved? current-kb-save) is nil) or
;;; block belongs to that module.

(defun-simple within-module-being-saved-p (block)
  (or (null (kb-module-being-saved? current-kb-save))
      (within-module-p block (kb-module-being-saved? current-kb-save))))

;; Newly defined; use elsewhere to replace old explicit code. (MHD 1/18/95)



;;; The function `traverse-definitions-of-kb-for-saving' collects definitions
;;; for the current KB being saved.  If this is a save for a module, only
;;; definitions belonging to that module are collected.
;;;
;;; All instances of the class DEFINITION must be collected.  Those that define
;;; classes (i.e., are not incomplete) must be collected in top down order.
;;;
;;; First-definition-mark is a flag which is always clear before this code is
;;; executed, and must be left cleared.  Its purpose is to avoid duplicate
;;; collection, and is cleared immediately after.
;;;
;;; The forest of user definitions is traversed starting from a list of its
;;; roots (root-classes-of-user-definable-classes).  Definitions picked up in
;;; this sweeped are marked using first-definition-mark.
;;;
;;; Then a second sweep is made over all definitions to pick up any that do not
;;; define classes, and were not picked up by the previous sweep over classes.
;;; This second iteration picks up incomplete definition frames (i.e., ones that
;;; did not yield actual classes) in the case of a non-modular save, and in the
;;; case of a modular save, just those that are in the module.
;;;
;;; At the end, the entire list is unmarked.
;;;
;;; NOTE: This has undergone a significant change (a simplification) in its
;;; dealing with junction block definitions.  Now, nothing special at all needs
;;; to be done.  Here's the description of the problem:
;;;
;;; Problems with Saving Junction Blocks in Modules
;;; -----------------------------------------------
;;;
;;; They can seem to belong to more than one module.  How is saving/loading
;;; supposed to deal with this?
;;;
;;; The module a junction block definition belongs to cannot always be
;;; determined by user inspection.
;;;
;;; The definition just says that it a junction block definition J belongs to
;;; the module of some connection-definition C, such that the
;;; junction-block-class of D is the name of J.  At present, this is not
;;; necessarily one unique module.  Since there can be multiple C's (belonging
;;; to multiple modules).  However, it is stable between calls provided that
;;; there are no changes to the state of the class or module hierarchy.
;;;
;;; When this occurs in practice, how can saving work out?  In 3.0 and 4.0 prior
;;; to 1/18/95 in the sources, the junction definition is scheduled for saving
;;; in all of the modules for all of the connections that name it as their
;;; junction block.
;;;
;;; For example, in /home/mak/g1transfer/gdaapps.kb (a module hierarchy), the
;;; junction block definition junction-block-for-gdl-path is given as the
;;; junction block of four different connection definitions.  Three of these
;;; belong to module GDL, but one belongs to module GDACORE.
;;;
;;; However, when saving in modules, this didn't work out because the definition
;;; would be written in one KB, marked as written, and then skipped when it next
;;; became time to write it in another KB because it appeared to have already
;;; been written.  The frame reference balance counter would then be out of
;;; whack, and the user would get an error (in 3.0) or a warning (in 4.0) that
;;; the KB had not been written out properly.
;;;
;;; The solution currently is to just save the definition in whichever module it
;;; appears to be in, which is stable at least during the definition collection
;;; phase of saving a KB, and rely on the ghost definition saving mechanism to
;;; assure the presence of the definition in other modules that may require it.
;;;
;;; The code affected is in traverse-definitions-of-kb-for-saving.  Changes
;;; effective as of today. (MHD 1/18/95)




;; The variable `definitions-for-saving' is used to collect user-defined class-
;; definitions for kb saving.

(defvar definitions-for-saving nil)





;;; The predicate `savable-definition-p' returns a true value when the definition
;;; is a frame, has the correct permanent/transient state for the type of save,
;;; is within the module being saved, and has not already been saved; otherwise,
;;; it returns nil.

(defun-simple savable-definition-p (definition)
  (and (framep definition)
       (collectable-block-p definition)
       (within-module-being-saved-p definition)
       (not (first-definition-mark-p definition))))




;;; The function `definition-is-dependent-on-uncollected-definitions-p' collects
;;; a journal-consed list of definitions that must be saved prior to saving
;;; the definition argument.  The list can include the class-definition instance
;;; used by the definition to define a definition class and the definitions for
;;; the user-defined class-definition superiors.

(defun-simple definition-is-dependent-on-uncollected-definitions-p (definition)
  (nconc
    (let* ((class-of-definition (class definition)) 
	   (definition-for-class-of-definition      
	       (class-definition class-of-definition)))
      (and (savable-definition-p definition-for-class-of-definition)
	   (journal-list definition-for-class-of-definition)))
    (and (instantiated-class-p (name-of-defined-class definition))
	 (loop for superior in (direct-superiors-of-defined-class definition)
	       when (savable-definition-p (class-definition superior))
		 collect (class-definition superior) using journal-cons))))




;;; The function `collect-definition-for-saving' recursively collects any
;;; definitions that the definition argument depends on.  There should be no
;;; unsolvable dependencies because the compiler for list-of-classes (the
;;; grammar category for direct-superiors-of-defined-class) should reject
;;; unsavable definitions.

(defun collect-definition-for-saving (definition)
  (let ((journal-consed-dependent-definitions?
	  (definition-is-dependent-on-uncollected-definitions-p definition)))
    (cond (journal-consed-dependent-definitions?
	   (loop for dependent-definition in journal-consed-dependent-definitions?
		 do
	     (collect-definition-for-saving dependent-definition)
		 finally
		   (progn (reclaim-journal-list journal-consed-dependent-definitions?)
			  (set-first-definition-mark definition)
			  (setq definitions-for-saving
				(nconc definitions-for-saving
				       (journal-list definition))))))
	  (t
	   (set-first-definition-mark definition)
	   (setq definitions-for-saving
		 (nconc definitions-for-saving (journal-list definition)))))))




(defun traverse-definitions-of-kb-for-saving ()
  ;; First clear any marks -- not necessary when all goes well, but safer:
  (loop for definition being each class-instance of 'class-definition
	do (clear-first-definition-mark definition))
  (let* ((result
	   (nconc
	     (loop for uomd being each strict-class-instance of 'units-of-measure-declaration
		   for value = (car (box-translation-and-text uomd))
		   when (and (collectable-block-p uomd)
			     (within-module-being-saved-p uomd)
			     (not (eq value no-value)) value)
		     collect uomd using journal-cons)
	     ;; This loop collects class-definitions that define user-defined
	     ;; class-definition classes.  Since user-defined class-definition
	     ;; classes can be defined using instances of user-defined class-
	     ;; definition classes, saving order is dependent both on the class
	     ;; inheritance path of the definition class, but also on the
	     ;; class-type of the class-definition instance used to define the
	     ;; class.
	     ;; It should not be possible to define a class-definition hierarcy
	     ;; that cannot be saved properly for reload.  The compiler for
	     ;; direct-superiors-of-defined-class should reject a set of
	     ;; superiors that causes cycles in the definition class hierarchy.
	     (loop with journal-consed-definition-list
		   = (loop for class being each subclass of 'class-definition
			   for definition = (class-definition class)
			   when (savable-definition-p definition)
			     collect definition using journal-cons)
		   for definition in journal-consed-definition-list
		   unless (first-definition-mark-p definition)
		     do (collect-definition-for-saving definition)
		   finally
		     (progn (let ((return-value
				    (copy-list-using-journal-conses definitions-for-saving)))
			      (reclaim-journal-list journal-consed-definition-list)
			      (reclaim-journal-list definitions-for-saving)
			      (setq definitions-for-saving nil)
			      (return return-value))))
	     ;; Now collect the class-definitions that define non-definition-
	     ;; class classes.
	     (loop for class being each subclass of 'item
		   for definition = (class-definition class)
		   when (and (framep definition)
			     (collectable-block-p definition)
			     (within-module-being-saved-p definition)
			     (not (first-definition-mark-p definition)))
		     do (set-first-definition-mark definition)
			     and collect definition using journal-cons)
	     ;; This loop should collect incomplete definitions.
	     (loop for definition being each class-instance of 'class-definition
		   when (and (not (first-definition-mark-p definition))
			     (collectable-block-p definition)
			     (within-module-being-saved-p definition))
		     collect definition using journal-cons))))
    (prog1 result
      (loop for definition in result
	    do (clear-first-definition-mark definition)
	    when (and (not (transient-p definition))
		      (not (permanent-block-p definition)))
	      do #+development		; See note below (MHD 1/18/95) 
	      (cerror "Continue -- do the usual thing."
		      "MHD: A definition about to be saved ~
                          has to be made permanent.  This ~
                          shouldn't be!")
	      (let ((noting-changes-to-kb-p nil))
		(set-permanent-block definition))))))

;; Note: I don't know why this should need to be done.  I'm scared to change it
;; just days before the code freeze for 4.0 Beta Phase 2, but it should not be
;; needed.  Note that auto-created junction block definitions are always set
;; permanent.  I don't see any effect this could have, other than either a bad
;; one, or papering over some other, perhaps more serious, flaw.  Still, I've
;; made it signal a cerror in development.  (MHD 1/18/95)




;; The following fails for transient workspaces and for
;; changes that occur doing journalling!!
;; 
;; (WHAT'S WITH THIS?! OLD COMMENT?! -- MHD, 1/17/95)

(defun traverse-top-level-workspaces-of-kb-for-saving ()
  (loop for workspace 
	being class-instances of 'kb-workspace
	;; Only top level workspaces. Fix!!!
	when (and (null (parent-of-subworkspace? workspace))
		  (collectable-block-p workspace)
		  (within-module-being-saved-p workspace))
	  collect workspace using journal-cons))



;; `Traverse-transient-items-of-kb-for-saving' .... If transients are included,
;; then start traversing the class hierarchy, mixing strict instances and
;; immediate subclasses when both are present. Presently, there are three roots
;; for transient items.

(defun traverse-transient-items-of-kb-for-saving ()
  (when (save-runtime-data? current-saving-context)
    (journal-cons 'loose-end
		  ;; Old:
		  ;;
		  ;;    (copy-list-using-journal-conses subclasses-of-item)
		  ;;
		  ;; New:   -- see note (MHD 1/25/95)
		  (journal-list 'item))))

;; Note: this entire subcase of traverse-kb-for-saving was removed in a commit
;; by GHW that had to do with NUPEC on 12/28/94.
;;
;; That apparently broke the snapshotting facility and led to the snapshot build
;; bug, via the failure of the snap-1 regression test, "snap-1 test failed to
;; write 10 items".
;;
;; GHW's change was commented as
;;
;;   nupec work
;;
;;   The variable subclasses-of-item has been removed and circumvented
;;   in the nupec code.
;;
;; Don't know why the code would have just been removed, i.e., rather than
;; adapted to the above.  Review with GHW. (MHD 1/25/95)



;;; `Traverse-transient-class-instances-of-kb-for-saving' called when tree is
;;; known to be a symbol naming a class.  It finds the strict instances of class
;;; potentially apropriate for saving.  To be potentially appropriate for saving,
;;; an instance must
;;;
;;;    (1) be transient;
;;;    (2) have no superblock;
;;;    (3) have no parent frame;
;;;    (4) if a workspace, be a subworkspace
;;;
;;; The resulting list returned is of the form
;;;
;;;    ( { direct-inferior-class }
;;;      { strict-class-instance
;;;        { connection-structure
;;;          [frame-for-connection-if-any]
;;;        }
;;;      }
;;;    )
;;;
;;; The initial sublist is the list of direct inferior classes (symbols) of
;;; class.  Following that sublist is a series of strict-class-instance
;;; sublists, in which each sublist that is started by a strict class instance
;;; of class is followed by each of that instance's connections (structures).
;;; Following each connection structure is its frame, if any.
;;;
;;; The conses that make up the result list are journal conses.  Note that the
;;; resulting list is a flat list of atoms containing no cons elements
;;; whatsoever.
;;; 
;;; Note that this can, at present, be called upon to visit the same class more
;;; than once.  This was not the case originally, when the code was first
;;; implemented, but became true with the advent of multiple inheritance.  This
;;; means that the same class may end up being visited more than once.
;;; Circularity is not a problem, since the class hierarchy cannot be circular.
;;; While this can be inefficient, it ends up not being a fatal problem because
;;; instances are always checked for having been previously written before
;;; finally deciding to write them to a KB; i.e., we don't end up with
;;; duplicates in the KB because of this.

(defun traverse-transient-class-instances-of-kb-for-saving (class)
  (nconc
    (copy-list-using-journal-conses (inferior-classes class))
    (loop with kb-workspace-subclass-p
	    = (subclassp class 'kb-workspace)
	  for instance being each strict-class-instance of class
	  when (and (transient-p instance)
		    (null (superblock? instance))
		    (null (parent-frame instance))
		    (or (not kb-workspace-subclass-p)
			(null (parent-of-subworkspace? instance)))
		    
		    ;; See note 1. - ben 1/10/92

		    ;; See note 2 about the following:  (MHD/ML 7/21/93)
		    (block-existed-at-start-of-save-p instance)
		    )
	    collect instance using journal-cons
	    and nconc
	      (loop for connection being each input-connection of instance
		    for frame-or-class
		    = (connection-frame-or-class connection)
		    collect connection using journal-cons
		    when (and (framep frame-or-class)
			      (has-slot-values-to-save-p frame-or-class))
		      collect frame-or-class using journal-cons))))

;; Note 1: a connection can never be in limbo, they always live hanging off
;; something else.  Is this the definition of in-limbo-p? - ben 1/10/92
;;
;;   (or (not (frame-of-class-p instance 'connection))
;;       (null (connection-for-this-connection-frame instance)))


;; Note 2 BUG FIX: You must only collect blocks that existed at the start of
;; save.  The lack of the following test, added in 3.1, has been a bug in 3.0
;; all along.  This could lead to a bombout (an "abort") if, for example, after
;; starting to save out a snapshot, you created pairs of transient items, put
;; half of each pair on a workspace, left the other half in limbo, and then
;; related the halves in limbo to the halves on the workspaces.  You could get
;; the abort because the in-limbo transients would be saved, in error, and they
;; would reference the on-workspace transients, which were correctly not saved.
;; Frame-reference-balance would get out of whack, and G2 would abort,
;; complaining about half of the pairs not being saved.  (MHD/ML 7/21/93)





;;; Traverse-class-instances-of-kb-for-saving ... called when tree is a known to
;;; be a block.

(defun traverse-block-for-saving (tree)
  (when (collectable-block-p tree)   ;why?
    (nconc
      (loop with connections
	    with kb-workspace? = (frame-of-class-p tree 'kb-workspace)
	    for subblock being each subblock of tree
	    for collectable? = (collectable-block-p subblock)
	    ;; This bit of clipping was done in write-frame-for-kb in
	    ;; the old saved kb format.
	    when collectable?
	      collect subblock into subblocks using journal-cons
	    do
	(when (and collectable? kb-workspace?)
	  (setq
	    connections
	    (nconc
	      connections		   
	      (loop for connection being each input-connection of subblock
		    for connection-frame-or-class =
		    (connection-frame-or-class connection)
		    when (collectable-connection-p connection)
		      collect connection using journal-cons
		    when (and (framep connection-frame-or-class)
			      (collectable-block-p
				connection-frame-or-class)
			      (has-slot-values-to-save-p
				connection-frame-or-class))
		      collect connection-frame-or-class using journal-cons))))
	    finally (return (nconc subblocks connections)))
      
      (let ((attributes-collector nil)
	    (attributes-collector-tail nil))
	(funcall-simple-compiled-function-on-attributes
	  tree #'collect-attribute-if-savable)
	attributes-collector)

      (when (frame-of-class-p tree 'entity)
	(nconc
	  
	  (let ((subworkspace? (car (subworkspaces tree))))
	    (when (and subworkspace?
		       (collectable-block-p subworkspace?))
	      (journal-list subworkspace?)))
	  
	  (let ((other-inferior?
		  (frame-class-case tree
		    (image-definition
		      (image-definition-media-bin tree))
		    
		    (variable
		      (simulation-details tree))

		    (generic-action-button
		      (embedded-rule? tree))

		    (g2-java-bean
		      (g2-java-bean-media-bin tree))
		    
		    (user-menu-choice
		      (embedded-rule-in-user-menu-choice? tree)))))
	    (when other-inferior? (journal-list other-inferior?))))))))




;;; The function `collect-attribute-if-savable' enqueues for collection a block
;;; that is an attribute of some item if appropriate.  If block is
;;; collectable-block-p and has slot values to save, it is included.
;;;
;;; In the case where a block is collectable, but doesn't have slot values to
;;; save, this does not mark it as having been referenced. This is so that if
;;; the block is subsequently referenced, the first reference will be a #\G
;;; form. If the block has already been referenced, then since the first such
;;; reference caused frame-reference-balance to be incremented, this now
;;; decrements it.  It should now be decremented since it will never be written,
;;; which is where the decrementing normally occurs.  The frame is marked as
;;; written in all cases, lest some modification to it later make us want to
;;; save it then.

(defun-simple collect-attribute-if-savable (block)
  (when (collectable-block-p block)
    (cond
      ((has-slot-values-to-save-p block)
       (let ((new-cons (journal-list block)))
	 (if attributes-collector
	     (setf (cdr attributes-collector-tail) new-cons)
	     (setq attributes-collector new-cons))
	 (setq attributes-collector-tail new-cons)))
      (t
       (when (and (block-referenced-in-current-save-p block)
		  (not (block-written-in-current-save-p block)))
	 (decrement-frame-reference-balance
	   block 'collect-attribute-if-savable))
       (setf (block-written-in-current-save-p block) t)))))








;; If superior is transient or permanent, copy this.  except that if subordiante
;; is already transient, do nothing.  Then apply this function down the
;; hierarchy.

;;; Add-as-inferior-block is called for each new frame being created or
;;; transfered. It has two functions. (1) it marks the frame as transient or
;;; permanent unless the frame is not part of the traversal hierarchy as
;;; indicated by the do-not-save-in-kb flag. (2) If a save or backup is
;;; occuring, it notes the fact that the traversal hierarcy is being modified,
;;; so that nothing is missed or covered twice.

;;; It is called:

;;; (1) When making a new connection by
;;;     make-new-connection-frame-for-connection.
;;; (2) When placing an embedded rule by put-embedded-rule? and
;;;     put-embedded-rule-in-user-menu-choic?.
;;; (3) When placing any subblock, including transfers, by add-subblock.
;;; (4) When adding a subworkspace by go-to-maybe-newly-created-subworkspace.
;;; (5) When putting frames as attributes by put-attribute-value.
;;; (6) When putting simulation formulas by put-simulation-details.

;; The case not covered here is that when the superior is neither permanent nor
;; transient, the inferior ought to be made to be neither. See the note on the
;; hierarchy principle at end of this file.

;; It's covered now. -alatto, 2/15/05

(defun-simple add-as-inferior-block (inferior superior)
  
  ;; If this is a transfer, then the block being transferred should be noted
  ;; as a kb change. The alternative is that the block did not exist at the
  ;; time that the save started. Note-change-to-block already checks for this.
  (note-change-to-block superior :inferiors)
  (note-change-to-block inferior :superior)
  
  (when (not (do-not-save-in-kb-p superior))
    (add-as-inferior-block-1 inferior superior)))
  

;;; The function `permanence-of-block-represented' tells you whether the
;;; input block is a frame representation of another block, and if so,
;;; whether the represented block is permanent, transient, or neither.
;;; More precisely, since the input may be a table that is
;;; a frame-representation of more than one block,
;;; if this is not the frame representation of some other block, it returns
;;; nil. If it is, it returns one of the symbols 'permanent, 'transient, or
;;; 'neither-permanent-nor-transient. If this is the frame representation of
;;; more than one block, it returns the least permanent one, that is,
;;; 'permanent of all represented blocks are permanent, 'transient if all
;;; represented blocks are either permanent or transient and at least one
;;; is transient, otherwise (meaning at least one represented block is
;;; neither permanent nor transient), it returns
;;; 'neither-permanent-nor-transient

;;; Note; if the frame passed as an argument is a representation of itself,
;;; this is not included in the set of represented blocks used to
;;; compute permanence-of-block-represented. That's because while
;;; it's normally wrong to make the representation "more permanent" than
;;; the thing represented, it's OK if by doing so we are also simultaneiously
;;; making the thing represented more permanent. This case actually comes
;;; up, because readout tables (for example) are representations of
;;; themselves. -alatto, 3/2/05
(defun permanence-of-block-represented (frame)
  (let ((result 'permanent))
    (do-frames-this-represents
	(represented-frame frame)
      (unless (eq represented-frame frame)
	(if (transient-p represented-frame)
	    (setq result 'transient)
	    (unless (permanent-block-p represented-frame)
	      (return-from permanence-of-block-represented 'neither-permanent-nor-transient)))))
      result))

;;; This call is required exactly when all of the following are true:
;;; 0. Frame is a block
;;; 1. noting-changes-to-kb-p is true
;;; 2. (not (frame-has-been-touched-p frame)) (always the case if newly created)
;;; 3. (frame-has-been-touched-p superior) or superior is a symbol.
;;; 4. (not transient-p frame)   (will change later)
;;; 5. (not (transient-p superior)) or superior is a symbol.

;;; Note: the comment above is no longer valid, and has been wrong at least
;;; since October of 1995.. In particular,
;;; add-as-inferior-block-1 is called regardless of the value of
;;; noting-changes-to-kb-p, since it also has to adjust the permanence
;;; of the block being added, in any case. -alatto, 2/18/05

;;; Modified to ensure that the representation of a block is never
;;; changed to be more permanent than the block itself. -alatto, 2/17/05

(defun-simple add-as-inferior-block-1 (inferior superior)
  (when (not (do-not-save-in-kb-p inferior))
    (let ((represented-block-permanence
	    (permanence-of-block-represented inferior)))
      (cond ((transient-p superior)
	     (unless
		 (eq represented-block-permanence 'neither-permanent-nor-transient)
	       (set-transient inferior)
	       (clear-permanent-block inferior)))
	    ((and (not (transient-p inferior))
		  (permanent-block-p superior))
	     (case represented-block-permanence
	       ((permanent nil)
		(set-permanent-block inferior)
		(when noting-changes-to-kb-p
		  (set-block-permanently-changed inferior)))
	       (transient
		(set-transient inferior))
	       (neither-permanent-nor-transient
		nil)))		; table should already be neither permanent nor transient
	    ((and (not (transient-p superior))
		  (not (permanent-block-p superior)))
	     (clear-permanent-block inferior)
	     (clear-transient inferior))))
    (funcall-function-to-inferior-blocks inferior #'add-as-inferior-block-1)))

;;; The function `remove-as-inferior-block' is to be called before inferior has
;;; been from superior in order to save (or back up) the inferior's
;;; subhierarchy.
;;;
;;; This starts at the bottom of the hierarchy and works its way up.  For each
;;; node it visits, it calls
;;;
;;;    (note-change-to-block inferior :module)
;;;
;;; Finally, it calls
;;;
;;;    (note-change-to-block superior :inferiors)
;;;
;;; on the topmost superior node.
;;;
;;; This has the effect of writing out the entire workspace hierarchy under
;;; superior.

;;; The variable `remove-as-inferior-block' is just bound to the value of
;;; (symbol-function 'remove-as-inferior-block), as a means to funcall that
;;; function efficiently.

(defun-simple remove-as-inferior-block (inferior superior)  
  (note-change-to-block superior :inferiors)
  (remove-as-inferior-block-1 inferior superior))

(defvar remove-as-inferior-block-1)

(defun-simple remove-as-inferior-block-1 (inferior superior)
  (declare (ignore superior))
  (funcall-function-to-inferior-blocks inferior remove-as-inferior-block-1)
  (note-change-to-block inferior :module))

(setq remove-as-inferior-block-1 #'remove-as-inferior-block-1)


;;; `Remove-block-from-module' must be called when deleting a block that belongs
;;; to a module.

(defun remove-block-from-module (block)
  (when noting-changes-to-kb-p
    (funcall-function-to-inferior-blocks
      block
      remove-as-inferior-block-1)))





;;; `Funcall-function-to-inferior-blocks' applies function to each immediate
;;; inferior of block. Function must take two arguments, and the second one is
;;; block (the immediate superior of the first argument).
;;;
;;; NOTE: FUNCTION MUST BE A SIMPLE, COMPILED FUNCTION.  This is for efficiency
;;; reasons; it is an error to supply some other kind of function.

(defun-simple funcall-function-to-inferior-blocks (block function)
  (loop for subblock being each subblock of block
	when (not (do-not-save-in-kb-p subblock))
	  do (funcall-simple-compiled-function function subblock block))

  (funcall-simple-compiled-function-on-attributes
    block function block)

  ;; NOTE: this part may be called at KB loading time, but connection structures
  ;; may not be filled yet. -- Chun Tian (binghe), Aug 2015
  (loop for connection being each input-connection of block do
    #+development
    (unless (connection-connected-to-block-p connection block)
      (error "impossible: block is not connected yet?!"))
    (let ((connection-frame-or-class (connection-frame-or-class connection)))
      (when (framep connection-frame-or-class)
	(funcall-simple-compiled-function
	  function connection-frame-or-class block))))

  (when (frame-of-class-p block 'entity)    
    (let ((subworkspace? (car (subworkspaces block))))
      (when subworkspace?
	(funcall-simple-compiled-function
	  function subworkspace? block)))

    (frame-class-case block
      (variable
	(let ((simulation-subtable? (simulation-details block)))
	  (when (and simulation-subtable?
		     (of-class-p simulation-subtable? 'simulation-subtable))
	    (funcall-simple-compiled-function
	      function simulation-subtable? block))))
      
      (generic-action-button
	(let ((embedded-rule? (embedded-rule? block)))
	  (when embedded-rule?
	    (funcall-simple-compiled-function
	      function embedded-rule? block))))
      
      (user-menu-choice
	(let ((embedded-rule? (embedded-rule-in-user-menu-choice? block)))
	  (when embedded-rule?
	    (funcall-simple-compiled-function
	      function embedded-rule? block))))

      (image-definition
	(let ((media-bin? (image-definition-media-bin block)))
	  (when media-bin?
	    (funcall-simple-compiled-function
	      function media-bin? block))))


      (g2-java-bean
	(let ((media-bin? (g2-java-bean-media-bin block)))
	  (when media-bin?
	    (funcall-simple-compiled-function
	      function media-bin? block)))))))

;; Documented the assumption about "simple, compiled".  It was assumed by virtue
;; of the call to funcall-simple-compiled-function-on-attributes.  A couple of
;; places in filters got by just being defined with defun, but I changed them to
;; defun-simple for sanity.  Also changed all of the other calls regular old
;; funcall to calls to funcall-simple-compiled-function.  (Why wasn't this done
;; before?!)  (MHD 1/20/94)











#+development
(defun complain (sub sup)
  (format t "sub: ~a    sup: ~a      ~a~%"
	  sub
	  sup
	  (cond
	    ((transient-p sub) 'transient)
	    ((permanent-block-p sub) 'permanent)
	    (t 'neither))))





;; This tests a constraint that the blocks identified as savable by the
;; present save-kb traversal are exactly those marked as permanent-blocks.

#+development
(defun report-saving-discrepencies ()
  (identify-all-savable-kb-workspaces)
  (loop for block being each class-instance of 'block
	unless (g2-equiv
		 (permanent-block-p block)
		 (or
		   (savable-block-p block)
		   (format-frame-p block)))
	  do (print block)))

;; Known problems with above. 

;; (1) Need to fix up old kbs.
;; (2) Need to mark format-frames made while reading in.


 

#+development
(defun check-integrity-of-kb ()
  (loop for block being each class-instance of 'block
	do
    (loop for subblock being each subblock of block
	  do
      (unless (eq block (superblock? subblock))
	(cerror "continue"
		"Subblock ~a of ~a does not have corect superblock." 
		subblock block)))
    (when (superblock? block)
      (unless (subblock-memq block (superblock? block))
	(cerror "continue"
		"Superblock ~a of ~a does not list it as a subblock."
		(superblock? block) block)))

    (when (and (frame-of-class-p block 'workspace)
	       (parent-of-subworkspace? block))
      (unless (memq block (subworkspaces (parent-of-subworkspace? block)))
	(cerror "continue"
		"The parent ~a of workspace ~a does not list it as a subworkspace." 
		(parent-of-subworkspace? block) block)))
    (when (frame-of-class-p block 'entity)
      (loop for workspace in (subworkspaces block)
	    do
	(unless (eq (parent-of-subworkspace? workspace) block)
	  (cerror "continue"
		  "A subworkspace ~a of ~a does not list it as a parent."
		  workspace block))))

    (loop for attribute being each attribute of block
	  do
      (when (framep attribute)
	(unless (and (eq (parent-frame attribute) block)
		     (eq attribute
			 (get-slot-value
			   block
			   (if (consp (parent-attribute-name
					attribute))
			       (progn
				 (cerror "continue somehow"
					 "this function has not been ~
                                        fixed to deal with class-qualified ~
                                        parent slot names!")
				 (car (parent-attribute-name
					attribute))) ; DEFERRED! (MHD 2/20/94)
			       (parent-attribute-name
				 attribute)))))
	  (cerror "An attribute ~a of ~a does not have one of the parent slots ~
                   correct." 
		  attribute block))))

    (when (parent-frame block)
      (let ((parent-slot-name?
	      (if (consp (parent-attribute-name
			   block))
		  (progn
		    (cerror "continue somehow"
			    "this function has not been ~
                                        fixed to deal with class-qualified ~
                                        parent slot names!")
		    (car (parent-attribute-name
			   block))) ; DEFERRED! (MHD 2/20/94)
		  (parent-attribute-name
		    block))))
	(unless (or (and parent-slot-name?
			 (eq block
			     (get-slot-value
			       (parent-frame block)
			       parent-slot-name?)))
		    (and (frame-of-class-p block 'rule)
			 (or (and (frame-of-class-p (parent-frame block)
						    'generic-action-button)
				  (eq block (embedded-rule? (parent-frame
							      block))))
			     (and (frame-of-class-p (parent-frame block)
						    'user-menu-choice)
				  (eq block (embedded-rule-in-user-menu-choice?
					      (parent-frame block)))))))
	  (cerror "continue"
		  "The parent ~a of ~a does not correctly point to it as an embedded ~
                 rule or attribute."
		  (parent-frame block) block))))

    (loop for thing being each connection of block
	  doing (cond
		 ((eq block (input-end-object thing))
		  (unless  (connection-exist-p thing (connections (output-end-object thing)))
		    (cerror "continue" "Problem with object at output end of ~
            connection ~a of ~a."
			    thing block)))
		 ((eq block (output-end-object thing))
		  (unless  (connection-exist-p thing (connections (input-end-object thing)))
		    (cerror "continue" "Problem with object at input end of ~
            connection ~a of ~a."
			    thing block)))
		 (t (cerror "continue" "A connection ~a of ~a does not reference ~
			    it as an end object."
			    thing block))))

    (when (frame-of-class-p block 'connection)
      (unless (and (connection-for-this-connection-frame block)
		   (eq (connection-frame-or-class
			 (connection-for-this-connection-frame block))
		       block))
	(cerror "continue"
		"Connection frame ~a lacks a structure, or its structure ~a does ~
                 not point to it."
		block
		(or (connection-for-this-connection-frame block) "none"))))
    ))




;;; The global variable `blocks-with-specialized-method?' is used
;;; when determining whether a block contains any subitems for which there
;;; is a specialized action method.  See its use in
;;; check-for-specialized-method in traversals.  Moved here from
;;; traversals.

(defvar blocks-with-specialized-method? nil)


;;; The global variable `interesting-blocks-found-in-search' is used to prevent
;;; looping when traversing the KB hierarchy to determine whether a block
;;; contains any subitems for which there is a specialized action-method.
;;; See its use in check-for-specialized-method in traversals. 

(defvar interesting-blocks-found-in-search nil)



(defun check-for-specialized-method (block reference-method method-name arg-count
					   add-instances-if-class-definition
					   include-connections?)
  (let ((class-description? nil))
    (when (and add-instances-if-class-definition
	       (class-definition-p block)
	       (and (not (block-found-in-search-p block))))
      (set-block-found-in-search block)
      (eval-push block interesting-blocks-found-in-search) 
      (setq class-description? (class-description (name-of-defined-class block)))
      (when class-description?
	(cond ((not (eq (get-specific-method method-name class-description?
					     arg-count nil nil nil)
			reference-method))
	       ;; gather up all the class instances if they are special
	       (loop for an-item being each class-instance of (name-of-defined-class block)
		     do
		 (eval-push an-item blocks-with-specialized-method?)))
	      (t
	       (loop for an-item being each class-instance of (name-of-defined-class block)
		     do

		 (check-for-specialized-method an-item reference-method method-name arg-count
					       add-instances-if-class-definition include-connections?))))))
    (loop for slot-description in  (slot-descriptions (class-description (class block)))
	  with slot-value?
	  do
      (when (user-defined-slot-description-p slot-description)
	(setq slot-value? (get-slot-description-value-macro
			    block slot-description))
	(when (framep slot-value?)
	  (setq class-description? (class-description (class slot-value?)))
	  (cond
	    ((and class-description?
		  (not (eq (get-specific-method method-name class-description?
						arg-count nil nil nil)
			   reference-method)))
	     (eval-push slot-value? blocks-with-specialized-method?))
	    (t
	     (check-for-specialized-method slot-value? reference-method method-name arg-count
					   add-instances-if-class-definition
					   include-connections?))))))
    (loop for subblock being each subblock of block
	  do
      (setq class-description? (class-description (class subblock)))
      (when class-description?
	(cond ((not (eq (get-specific-method method-name class-description?
					     arg-count nil nil nil)
			reference-method))
	       (eval-push subblock blocks-with-specialized-method?))
	      (t
	       (check-for-specialized-method subblock reference-method method-name arg-count
					     add-instances-if-class-definition
					     include-connections?)))))
    (when (frame-of-class-p block 'entity)
      (loop for subworkspace in (subworkspaces block)
	    for workspace-class-description?  = (class-description (class subworkspace))
	    do
	(cond ((and workspace-class-description?
		    (not (eq (get-specific-method method-name workspace-class-description?
						  arg-count nil nil nil)
			     reference-method)))
	       (eval-push subworkspace blocks-with-specialized-method?))
	      (t
	       (loop for subblock being each subblock of subworkspace
		     do
		 (setq class-description? (class-description (class subblock)))
		 (cond ((and class-description?
			     (not (eq (get-specific-method method-name class-description?
							   arg-count nil nil nil)
				      reference-method)))
			(eval-push subblock blocks-with-specialized-method?))
		       (t
			(check-for-specialized-method subblock reference-method
						      method-name arg-count
						      add-instances-if-class-definition
						      include-connections?))))))))
    (when include-connections?
      (loop for connection being each connection of block
	    for connection-frame-or-class =
	    (if (connection-p connection)
	       (connection-frame-or-class connection))
	    do
	(when (and (framep connection-frame-or-class)
		   (and (not (block-found-in-search-p connection-frame-or-class))))
	  (set-block-found-in-search block)
	  (eval-push block interesting-blocks-found-in-search) 
	  (setq class-description? (class-description
				     (class connection-frame-or-class)))
	  (cond ((and class-description?
		      (not (eq (get-specific-method method-name
						    class-description?
						    arg-count nil nil
						    nil)
			       reference-method)))
		 (eval-push
		   connection-frame-or-class
		   blocks-with-specialized-method?))
		(t
		 (check-for-specialized-method
		   connection-frame-or-class
		   reference-method method-name
		   arg-count
		   add-instances-if-class-definition
		   nil))))))
    (when nil
      (let ((other-inferior?
	      (frame-class-case block
		(variable
		  (simulation-details block))
		(generic-action-button
		  (embedded-rule? block))
		(user-menu-choice
		  (embedded-rule-in-user-menu-choice? block)))))
	(setq class-description? (class-description (class other-inferior?)))
	(when (and other-inferior? class-description?)
	  (cond ((not (eq (get-specific-method method-name class-description?
					       arg-count nil nil nil)
			  reference-method))
		 (eval-push other-inferior? blocks-with-specialized-method?))
		(t
		 (check-for-specialized-method other-inferior? reference-method method-name arg-count
					       add-instances-if-class-definition include-connections?))))))))






;;; Notes on constraints and principles.

;;; 1. Hierarchy constraint: Letting permanent = 2, transient = 1, and neither =
;;; 0, then it must be the case that the structural hierarchy of G2 is
;;; non-increasing as you go from root to leaf.

;;; 2. Traversal is of two kinds:
;;; 
;;;       (1) permanent
;;;    or
;;;       (2) permanent and transient
;;;       
;;; In either case, things that are neither are not saved.

;;; 3. Clipping a list: If saving only permanent, clip the list to contain only
;;; the permanent things. If saving both, clip the list to include both.

;;; 4. Saving constraint: What is referenced must be written. The only exception
;;; is those blocks that have default values.

;;; 5. Anything not in the traversal must never be marked as permanent or
;;; transient.

;;; 6.  Because saving occurs as an interruptible process, the only reasonable
;;; way to guarantee that tables are not written out that refer to items having
;;; less status than themselves is to never allow a permanent table to reference
;;; anuthing not permanent, and to never allow a transient table to reference
;;; anything not permanent or transient.

;;; 7. Do the right thing for modules. [FINISH!! -- MHD/ML, 11/19/91]



;;; End file with CR.



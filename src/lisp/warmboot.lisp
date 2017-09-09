;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module WARMBOOT

;; Copyright (c) 1986 - 2017 Gensym Corporation.
;; All Rights Reserved.

;; Michael Levin and Mark H. David


(declare-forward-references
  (current-computation-component-particulars variable comp-utils)
  (*current-computation-frame* variable comp-utils)
  (system-start function cycles)
  (schedule-all-cyclic-rules function activate)
  (start-procedure-invocation-in-place function proc-utils)
  (update-all-indexed-attribute-hash-tables function proc-utils)
  (simulate-until-consistent-with-gensym-time function simulate1)
  (read-hash-table-data function hash-tables)
  )


(declare-forward-references-to-module histories
  make-or-reformat-cascaded-ring-buffer
  store-new-element-in-history-cascaded-ring-buffer
  read-past-history-buffer-for-block
  read-past-history-buffer-for-block
  unsquirrel-data-for-block
  read-history-buffer-for-block
  read-history-buffer-and-location-for-block
  read-past-history-buffer-and-location-for-block)

(declare-forward-reference read-array-data function)
(declare-forward-reference read-list-data function)
(declare-forward-reference runnable-p-function function)


;;;; Warmboot, Top Level

(defconser warmboot)


;;; `complete-warmboot-internals' is a macro which contains the
;;; part of warmboot-kb which comes after system-start.  It has
;;; been abstracted out from warmboot-kb to allow it to be reused
;;; by the g2-start completion-form. See:
;;; `complete-warmbooting-after-system-start' 

(defmacro complete-warmboot-internals ()
  '(if system-is-running
    (progn
      ;; Now unsquirrel all runtime data.
      (loop for block being each class-instance of 'block do
	(unsquirrel-data-for-block block))

      (update-all-indexed-attribute-hash-tables)

      ;; Delete any frames that need to be deleted after unsquirreling
      (delete-blocks-after-unsquirreling)


					;(initialize-simulator-as-data-server)

      
      ;; Execute warmboot user procedure if any.
      (let ((warmboot-procedure?
	      (get-instance-with-name-if-any 'procedure 'warmboot)))
	(if (and warmboot-procedure?
		 (runnable-p-function warmboot-procedure?))
	    ;; Set necessary variables for start-procedure-invocation-in-place
	    (let ((old-computation-frame *current-computation-frame*)
		  (old-computation-component-particulars
		    current-computation-component-particulars))
	      (setq *current-computation-frame* warmboot-procedure?)
	      (setq current-computation-component-particulars nil)
	      ;; If the procedure invocation cannot be scheduled, a
	      ;; warning-message is displayed and nil is returned.  In this case,
	      ;; schedule cyclic rules.
	      (when (error-text-p
		      (start-procedure-invocation-in-place
			warmboot-procedure?
			nil nil
			0 0
			0			; 0 arguments
			nil '(finish-warmbooting) nil nil nil))
		(schedule-all-cyclic-rules))
	      (setq *current-computation-frame* old-computation-frame)
	      (setq current-computation-component-particulars
		    old-computation-component-particulars))

	    (schedule-all-cyclic-rules)))
      ;; setup simulator
      (simulate-until-consistent-with-gensym-time)
      ;; Return T - the warmboot succeeded.
      t)))


;;; The function `warmboot-kb' loads the given KB, which may contain runtime
;;; data.  If the load succeeded, then the scheduler-mode is optionally changed
;;; to "as fast as possible" (for catch-up mode), the system is started, any
;;; runtime data is "unsquirrelled", any user-defined WARMBOOT procedure is
;;; scheduled for execution, and the simulator is setup.

;;; Warmboot-kb returns T if the warmboot succeeded and NIL if it failed.
;;;
;;; Added with-backtrace-for-internal-error ajs (4/30/96)

(defun warmboot-kb (pathname &optional (catch-up? nil))
  (with-backtrace-for-internal-error 'warmboot-kb
    (let* ((warmbooting? t)
	   (warmbooting-with-catch-up? catch-up?)
	   (blocks-to-delete-after-unsquirreling nil)
	   (copy-of-current-kb-pathname?
	     (and current-kb-pathname?
		  (copy-gensym-pathname current-kb-pathname?)))
	   (warmboot-read-kb-succeeded? nil))

      ;; Read in the KB.  While reading, runtime data is squirelled.  (If runtime
      ;; data is encountered other than while warmbooting, it is read and
      ;; discarded.) Read the active status of any kb-workspace, marking it with
      ;; workspace-was-active.
      (setq warmboot-read-kb-succeeded?
	    (read-kb nil pathname t t nil nil copy-of-current-kb-pathname?))

      ;; Note that current-kb-pathname? is copied and reclaimed here because the
      ;; original value may be reclaimed within read-kb, by clear-kb.
      ;; MHD please review this!!  - cpm, 3/1/95
      (when copy-of-current-kb-pathname?
	(reclaim-gensym-pathname copy-of-current-kb-pathname?)
	(setq copy-of-current-kb-pathname? nil))

      (unless warmboot-read-kb-succeeded?
	;; Do not start the KB or read any runtime data. The read failed.
	(return-from warmboot-kb nil))

      ;; Change the scheduler-mode to "as fast as possible" to catch up to the
      ;; current real time.  Do this after the system tables are already installed
      ;; in read-kb.
      (when warmbooting-with-catch-up?
	(parse-text-for-slot
	  (convert-text-string-to-text (copy-constant-wide-string #w"as fast as possible"))
	  timing-parameters
	  (get-slot-description-of-frame 'scheduler-mode timing-parameters nil)
	  t))

      ;; If the KB requires a runtime data file, read that also

      ;; Consider pausing and reverting

      ;; If recompiling automatically, should happen here.

      ;; Execute system-start, but inhibit initial rules.  During this cycle,
      ;; extend the activation to all subworkspaces that were active at save time.
      ;; (Variations to system-start happen because of the binding of
      ;; 'warmbooting?.)
      (system-start)
      (complete-warmboot-internals))))




;;; The function `complete-warmbooting-after-system-start' will
;;; be called when g2-start has been completed. This function
;;; is passed its own function calling list, which it must
;;; reclaim.

;;; I believe that this function is no longer called -alatto, 9/14/04

;;; Code added to delete-blocks-after-unsquirreling by fix
;;; HQ-4862584 relies on the assumption that the only additions
;;; to blocks-to-delete-after-unsquirreling are the ones made by
;;; the call to delete-block-after-unsquirreling in read-frame-for-kb.
;;; More precisely, the assumption in the code is that the only reason
;;; a ui-client-item is on the blocks-to-delete-after-unsquirreling
;;; list is because it lacked a superblock, and that if it has now
;;; acquired a superblock, it is OK for it to hang around and not get
;;; deleted after all. -alatto, 9/14/04
(defun complete-warmbooting-after-system-start (completion-form)
  (gensym-dstruct-bind ((nil blocks-to-delete-after-unsquirreling)
                        completion-form)
   (complete-warmboot-internals)
   (reclaim-warmboot-list completion-form)))
 

(defun finish-warmbooting (x)
  (declare (ignore x))
  (schedule-all-cyclic-rules))







;;;; Reading Runtime Data

;;; `squirreled-data' is a lookup slot of block used only during the execution
;;; of warmboot, and null otherwise.  The format is a list of lists, with the
;;; first of each sublist being a LISP character.  The character is the same as
;;; is used to encode each type of runtime data, as documented in KB-LOAD1. The
;;; remaining elements are the components of the data. The sublist is never part
;;; of the data itself. The list and its sublists are made of slot-value conses.

;;; `read-runtime-data-for-block' is called from read-frame-for-kb upon
;;; encountering a #\[ while reading name/value pairs. It must read the rest of
;;; the block, and exit having read #\!. Within the runtime data, each element
;;; begins with distinct capital letter, and its reader should exit leaving
;;; either #\!  or the next such capital letter to be read by
;;; read-runtime-data-for-block. This may require backstuffing one character.

;;; Unless warmbooting?, each element read is to be reclaimed. (Consider writing
;;; something that can pass over each type of element without allocating
;;; storage.

;;; When warmbooting, all data is put on the slot squirreled-data, as cdr of a
;;; pair. Car of the pair is the dispatching keyword (since these things do not
;;; always correspond to slots of a frame.)

;;; Each case in the following must have a corresponding case in
;;; read-past-runtime-data-for-block which follows.

(defun read-runtime-data-for-block (block)
  (loop for character = (read-char-for-kb)
	do
    (character-case character
      (#\! (return (values)))
      ;; probably not used
      (#\T (set-transient block))
      ;; Occurs only on kb-workspaces
      (#\K (set-workspace-was-active block))
      (#\V
	 (squirrel-away-data-in-block
	   block character
	   
	   ;; read current value
	   (read-element-for-kb-with-temporary-floats nil)
	   
	   ;; timestamp or #\G meaning *some-time-ago*
	   (cond
	     ((eql (setq character (read-char-for-kb)) #\G)
	      *some-time-ago*)			   
	     (t (unread-char-for-kb character)
		(read-element-for-kb nil)))

	   ;; expiration is a timestamp, #\X meaning 'never, or
	   ;; #\G meaning *some-time-ago*
	   (cond
	     ((eql (setq character (read-char-for-kb)) #\X)
	      'never)
	     ((eql character #\G)
	      *some-time-ago*)			   
	     (t (unread-char-for-kb character)
		(read-element-for-kb nil)))))
      (#\P
	 (squirrel-away-data-in-block
	   block character
	   
	   ;; read current value
	   (read-element-for-kb-with-temporary-floats nil)
	   
	   ;; timestamp or #\G meaning *some-time-ago*
	   (cond
	     ((char= (setq character (read-char-for-kb)) #\G)
	      *some-time-ago*)			   
	     (t (unread-char-for-kb character)
		(read-element-for-kb nil)))))
      (#\S
	 (let ((next-element
		 (read-element-for-kb-with-temporary-floats nil)))
	   ;; In KBs saved before the kb-flag checked below was introduced,
	   ;; i.e., in 4.0 (development) as of 6/24/94, simulation-no-value was
	   ;; written out as a no-value (X) element.  Now that there are
	   ;; simulation-no-value (#) elements, this is unnecessary, but the
	   ;; conversion process should remain here as long as there can be old
	   ;; KBs (saved with runtime data).  (MHD 6/24/94)
	   (when (and (not (simulation-no-value-can-be-written-p))
		      (eq next-element no-value))
	     (setq next-element simulation-no-value))
	   (squirrel-away-data-in-block block character next-element)))
      ((#\H #\J)
       (squirrel-away-data-in-block
	 block character
	 (read-history-buffer-for-block block character)))
      (#\B
	 (multiple-value-bind (history-buffer location-information)
	     (read-history-buffer-and-location-for-block)
	   (squirrel-away-data-in-block
	     block character
	     history-buffer location-information)))
      (#\R
       (squirrel-away-data-in-block block character (read-element-for-kb nil)))
      (#\A
       (squirrel-away-data-in-block block character (read-array-data block)))
      (#\L
       (squirrel-away-data-in-block block character (read-list-data block)))
      (#\O
       (squirrel-away-data-in-block block character (read-hash-table-data block))))))

(defun read-element-for-kb-with-temporary-floats (top-level?)
  (with-temporary-gensym-float-creation read-element-for-kb-with-temporary-floats
    (read-element-for-kb top-level?)))

(defun squirrel-away-data-in-block
    (block key data-element-1 &optional data-element-2? data-element-3?)
  (slot-value-push
    (nconc
      (slot-value-list key data-element-1)
      (if data-element-2? (slot-value-list data-element-2?))
      (if data-element-3? (slot-value-list data-element-3?)))
    (squirreled-data block)))



(defun-void read-past-runtime-data-for-block (print?)
  (loop

        with create-frames-and-connections-reading-past? = t
	;; see read-past-element-for-kb
	
	for character = (read-char-for-kb)
	when print?
	  do (format t "~c" character)
	do (character-case character
	     (#\!
		(when print?
		  (format t "; end of runtime data~%"))
		(return (values))) ; JED 12/28/93
	     ((#\T #\K))
	     ((#\V #\P)
	      (let ((variable-current-status-case? (char= character #\V)))
		(read-past-element-for-kb print?)
		(when (not (eql (setq character (read-char-for-kb)) #\G))
		  (unread-char-for-kb character)
		  ;; The value, a gensym time, does not need reclaiming.  This
		  ;; could be optimized by detailed semantic reading of
		  ;; characters.
		  (read-past-element-for-kb print?))
		(when variable-current-status-case?
		  (cond
		    ((eql (setq character (read-char-for-kb)) #\X))
		    ((eql character #\G))
		    (t (unread-char-for-kb character)
		       (read-past-element-for-kb print?))))))
	     (#\S
		(cond
		  ((eql (setq character (read-char-for-kb)) #\X))
		  (t (unread-char-for-kb character)       
		     (read-past-element-for-kb print?))))
	     ((#\H #\J) (read-past-history-buffer-for-block print?))
	     (#\B (read-past-history-buffer-and-location-for-block print?))
	     (#\R (read-past-element-for-kb print?))
	     ((#\A #\L)
	      (let ((number-of-elements (read-element-for-kb nil)))
		(when print?
		  (format t "~%; ~a contents -- ~d elements:~%"
			  (if (char= character #\V) 'vector 'list)
			  number-of-elements))
		(loop repeat number-of-elements
		      do (read-past-element-for-kb print?))
		(when print?
		  (format t "~%; end ~a contents -- ~d elements~%"
			  (if (char= character #\V) 'vector 'list)
			  number-of-elements)))))))



(def-system-variable initialization-inhibit WARMBOOT
  (:funcall gentemp "initialization-inhibit"))



(defun delete-blocks-after-unsquirreling ()
  (loop with frame-serial-number = (copy-frame-serial-number (current-frame-serial-number))
	for frame in blocks-to-delete-after-unsquirreling
	when (and (frame-has-not-been-reprocessed-p
		    frame frame-serial-number)
		  ;; A ui-client-item might be saved before the
		  ;; window it is on, due to a bug fixed by
		  ;; HQ-4862584. In this case, read-frame-for-kb will
		  ;; think that this item is not on a window, and
		  ;; it will erroneously put it on the list of
		  ;; blocks-to-delete-after-unsquirreling. So we
		  ;; check here, after the superblock has been read, so
		  ;; we don't erroneously delete it. -alatto, 9/13/04
		  (not
		    (and (superblock? frame)
			 (frame-of-class-p frame 'ui-client-item))))
	  do (delete-frame frame)
	finally
	  (reclaim-frame-serial-number frame-serial-number)
	  (reclaim-gensym-list blocks-to-delete-after-unsquirreling)))
 






;;;; System Procedures for Save

;;; These have been moved to SETS because they use evaluation value
;;; macros.



;; Data for reclaiming: -done-

;; (current-value-of-variable-or-parameter var-or-param) *
;; (time-of-most-recent-value var-or-param) nothing
;; (expiration-time-of-current-value    nothing

;; (simulation-value simulation-runtime-information) * 
;; (new-simulation-value simulation-runtime-information) *


;; variable-or-parameter-stored-histories? **
;; simulation-stored-histories? **

;; * reclaim-managed-number-or-value

;; ** reclaim-history-buffer




;; To do: 7/7/91

;; 1. Read-runtime-data-for-block modified to store as managed number.
;;               store-managed-number-or-value   -done-

;; 2. Demonstarate loading of histories as working.  -done-



;; 3. When not warmbooting?, reclaim stuff.   -done-

;; 4. Modify traverse-kb-for-saving to work for transients. It is called from
;;    kb-save3 and frames3. It will also be necessary to modify the clipping
;;    that goes on in write-frame-for-kb for subblocks, frame-representations,
;;    and (new) for connections. Are there any others?   -done-

;; 5. Call warmboot procedure using start-procedure-invocation. Study how Andy
;;    uses it. Make it continue the warmboot. -done-

;; 6. Make a cyclic rule starter. Base it upon a traversal of kb-workspaces. -done-



;; To do: 8/6/91

;; 2. System procedure for save.
;; -done-

;; Note that saving context is kept in current-saving-context for
;; resumption.  This means that there can currently only be one save at
;; a time.  Doc.  Need to enforce this.  Mike says that this is already
;; done.  In save-kb, returns should be hooked up to error mechanism
;; (should return error strings to save-kb system procedure).

;; Test kb is "ma:>agh>backup-test.kb".

;; Development grammar for saving kb with runtime data has been commented
;; out of file-command grammar in KB-LOAD1.



;; See to do list in "ma:>agh>backup-test.kb".



;; Spec of what gets saved (easy) and what doesn't get saved (harder).  Procedure
;; invocations are an open issue.

;; Values of the system procedure save-kb are unclear.  Should return error string
;; at a minimum.  Check if error handling stuff can be used.

;; Things to do after unsquirrelling (if any) including entering values into
;; event-based displays, and tasks that should be run when values expire (see
;; also other notes).

;; Inhibit setting of initial values during activation (could cause unwanted value
;; in history buffer).

;; To what extent are display values retained?

;; UI for executing warmboot including load grammar, and warnings indicating when
;; loading a kb with runtime data and warmbooting a kb without runtime data.



;; Issues of how to handle errors encountered while saving.  Best thing would be
;; to use on-error mechanism.  In any case, error string should be returned
;; somehow to the user.

;; What happens on a pause or reset.  If someone aborts the save-kb procedure,
;; terminate has to be executed.  May need to use callback similar to the one for
;; the simulator.  Jim may not have on-exit ready.

;; 3. Menu choice for warmboot. Put on main menu miscellany. 
;; Actually, I think that the way it is now is best. It it is part of the
;; load-kb dialog, it is easy to specify the kb to warmboot.  Putting it on
;; the main menu miscellany removes this capability.  - Review with Mike -



;; 7. Arrays and Lists
;; Array, list writer, squirreler, unsquirreler - done.
;; - see write-runtime-data-for-kb, read-runtime-data-for-block,
;; unsquirrel-data-for-block
;; Truth-value type has been defined. It is used for lists and arrays,
;; because there could be mixed types here.
;; Read-array-data and read-list-data need to deal with U character.
;; Still need to deal with temporary area overflow problems.
;; Test more thoroughly.  Test for truth-value cases.


;; 28. Some saved kb analysis tools would be good.  Ben did some of these
;; but they probably have to be updated.  These should be modelled after
;; the kb-load functions.

;; Review iterate-over-history.  It looks like this may well be leaking.
;; I'm pretty sure that write-kb is not wrapped with a with-temporary
;; wrapper.  Also, there is a bug in read-history-buffer-for-block in
;; that with-temporary-gensym-float-creation is wrapped around the whole
;; thing.  This can cause a temporary area overflow.
;; The shedding of datapoints in read-history-buffer-for-block shouldn't
;; be necessary.  It it were, I would need to do something similar for
;; arrays and lists.  

;; Also, when are history buffers allocated?  On activation?,
;; installation, store of first data point?  Mike is currently
;; allocating his own buffer and if one already exists, it has to be
;; reclaimed.  He is doing this in unsquirrel-data-for-block.

;; Looks like an initially rule flashed on warmboot.  Initially rules
;; shouldn't be getting executed.

;; Slot putter review project.  Send checklist around.



;; 12.  All noting of changes for saving runtimedata should be in place.
;; Put-current-value is done.  Arrays, lists, are done.  Also done for relations
;; (in add-to-relation, remove-from-relation), and for simulation values (in
;; update-variable).  See also put-current-value.  Test all this by saving with
;; runtime data and then changing things while the save is in progress.

;; 9.  A bounding-box in the subblocks of a subworkspace got marked
;; permanent-block.  The flag do-not-save-in-kb was not set on the bounding box.
;; - Fixed (in make-bounding-box).  This flag is now used for messages,
;; g2-windows, and bounding boxes.  Review whether it is needed anywhere else.

;; 23.  Interference between recompile processing and warmboot.  It now happens
;; after starting, and changes the status of initial rules.  This could happen
;; with any KB when not warmbooted if you started while the recompile is in
;; progress.  Should not be an issue.  No recompiling should currently be
;; necessary for any warmboot kb.  May be an issue for future releases.

;; Currently unsquirreling of data for variables and parameters does not
;; go through put-current-value (see unsquirrel-data-for-block).  Thus,
;; unwanted side effects of put current value such as history saving and
;; forward chaining are avoided.  However, there are some side effects
;; that are desireable, initializing true-value updated displays for
;; example.

;; Don't use read-element-for-kb for warmboot arrays, lists, histories.  It is too
;; inefficient since it enters and exits temporary contexts for each element.
;; Optimize to have special readers for these (see read-runtime-data-for-block).

;; Read-element-for-kb currently always converts gensym floats to slot value
;; floats.  Eventually, functions like put-current-value and store-history-value
;; should be converted to take slot values as args.  Currently, the slot values
;; from read-element-for-kb lead to some inefficiencies in functions like
;; read-history-buffer-for-block because the gensym floats are dug out of the slot
;; values before being passed to
;; store-new-element-in-history-cascaded-ring-buffer.





;; For saves done via the system procedure for save
;; (g2-save-kb), the default priority for runtime saving is overridden
;; by the priority of the g2 system procedure. - tell Mark Allen -

;; 18.  Hide much of the "journal and backup parameters" and change its
;; name to saving parameters.  Three slots are interesting: pathname for
;; basis kb, unique identifier for basis kb, and default priority of
;; runtime saving.  - done -

;; 26.  Indexed attributes are initialized by system-start which is
;; called by warmboot-kb.  However, they need to be updated after data
;; is unsquirrelled into variables.  This is done by
;; update-all-indexed-attribute-hash-tables which is called by
;; warmboot-kb after unsquirreling.  - done -

;; Review 	      ;; Only top level workspaces. Fix!!! 
;; in traverse-kb-for-saving.  Looks like an inefficiency.

;; 1. Make loading transient connections work. Consider transient flag. Need to
;;    delete connection after loading if doing a regular load/merge, and
;;    connection is permanent. -done-

;; 4. Transient connections should work. Test.

;; 5. Revert warmboot data. No longer relevent if start is forced.

;; 10. Consider an alternative to START after a WARMBOOT. It must reclaim the
;; squirreled stuff, and reset the workspace-was-active flag on all workspaces.
;; Also undo-kb-state-changes-after-reading-kb. -no go. we now start
;; automatically-

;; 11. original-kb-state-plist is now saved.
;; undo-kb-state-changes-after-reading-kb is called by read-kb to undo the state
;; changes that were loaded and leave original-kb-state-plist NIL. When
;; warmbooting, this should be inhibited. -done- (Also, read-frame-for-kb now
;; calls note-as-frame-with-kb-state-changes when loading
;; original-kb-state-plist. The use of undo... is now the same for loading and
;; resetting.)   -done really done --

;; 13. (for ML, no hurry) Instead of a list of symbols with 'numeric syntactic
;; ambiguity, preface each with a character other than quote mark. This makes
;; the feature more local, and removes a headache that interferes with journals,
;; etc.

;; 14. What sort of side effects should be done when current values and
;; dynamic relations are established? Any? Need help from Jim and Ben. What
;; about arays and lists.

;; 19. What happens if there is a warmboot, and the user deletes a frame before
;; starting. Do the right things happen with regard to removing from relations,
;; lists, etc? Probably not. Could cause crash. David and Michael decided that
;; warmboot should start automatically.  -gone away-

;; 20. When running save from a procedure, probably don't want file display.
;; (David Riddell.)  Consider making this specifiable via an arg to the
;; procedure.  - done -

;; 21. When warmbooting a file that was not a save with runtime data, it will
;; still attempt a warmboot, and will still have runtime changes. This is
;; probably a reasonable thing, should be documented.

;; 22. Andy should devise a test for simulator and simuation histories.

;; 24. Warmboot procedure. Describe to Mark Allen.  Provide some examples.

;; 27. Are there other side effects that are bypassed by unsquirreling??

;; 29. ML (after he gets back) investigate recompiling and initial rules.

;; 30.  Review funcall-function-to-inferior-blocks for connection stuff.  The loop
;; over all input connections is guaranteed to get all connections only if it is
;; called for all blocks on a workspace.  Also, the fact that connection frames
;; are required for transient connections, and the fact that there are now
;; transient flags on both the connection structure and the frame complicates
;; set-transient-and-propagate a bit.  We will also need a set-permanent and
;; propagate.

;; See efficiency notes for write-g2-array-data-for-kb.

;; In write-runtime-data-for-kb, we should probably be doing much more
;; checking of whether blocks are active, just to save time.

;; It would be nice to have a capability to set the universal time for
;; the G2 which is being warmbooted.  This would allow setting the time
;; back to the time at which the last save with runtime data occurred,
;; presumably just before a crash.  This would be useful for
;; investigating what may have led to the crash.  The current lack of
;; this capability also means that all knowledge bases with runtime data
;; have a limited time during which they are useful; eventually, their
;; histories and data expire and they become no different from kbs
;; without the runtime data, except that they may be much bigger.  The
;; capability to set this time would also be useful when running in as
;; fast as possible mode and saving histories with timestamps in the
;; future.  When warmbooting these, it may be necessary to set the time
;; into the future.

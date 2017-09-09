;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module KB-SAVE2: Saving Knowledge Bases

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson, Michael Levin, Mark H. David






(declare-forward-references
  (parent-variable-function function variables)
  (system-reset function cycles)
  (system-start function cycles)
  (write-list-in-chicago-style function)
  (g2-array-length-function function arrays)
  (start-kb-after-load-from-system-table? function grammar7)
  (clear-inspect-command-history-list function queries)
  (superior-frame function activate)
  (shut-down-g2ds-clients-for-clear-kb function g2ds)
  (workspaces-can-be-shown-at-this-kb-level-p function filters)
  (savable-computation-style-p function cells)
  (kb-save-termination-reason? variable sets)
  (next-class-bit-number variable frames2)
  (last-system-class-bit-number variable frames2)
  (make-original-value-for-text-box-font-kb-state-change function controls)
  (restore-original-value-for-text-box-font-kb-state-change function controls)
  (save-icp-object-map-for-registered-item function g2-rpc2)
  (restore-icp-object-map-for-registered-item function g2-rpc2)
  (check-denotation-well-defined function conclude)
  (install-subscription function conclude)
  (make-ui-client-session-internal function view-g2)
  (completely-shut-down-g2 function commands1)
  (clear-all-twng-disconnect-callbacks function commands1)
  (reason-to-exclude-slot-description-for-compute-class-description-node-attributes function kb-save4))


(declare-forward-references-to-module view-g2
  (inform-ui-client-interface-of-module-creation function)
  (inform-ui-client-interfaces-of-clear-kb function)
  (ui-client-session-slots-to-save-for-clear-kb variable)
  (get-slots-to-save-in-clear-kb-for-representation function))


(declare-forward-reference g2-initialize-gsi-interface function)
(declare-forward-reference send-ws-representations-item-moved function)
(declare-forward-reference send-ws-representations-item-color-pattern-change function)
(declare-forward-reference copy-denotation function)
(declare-forward-reference unedit-up-to-date-modules function)

(declare-forward-reference note-gensym-window-initialized function)
(declare-forward-reference run-state-change-hook function)


;;;; Pane and Image Plane Descriptions



;;; A `pane description' describes the contents of a pane in terms of some or all of
;;; the image planes on it that have workspaces.  Structurally, it is a slot value
;;; list of "image plane descriptions", in stack-of-image-planes order.

;;; An `image plane description' describes an image plane, as a slot value list of
;;; the form
;;;
;;;   (workspace
;;;      workspace-x-at-center-of-pane workspace-y-at-center-of-pane
;;;      magnification-of-default-x-scale magnification-of-default-y-scale
;;;      [x-in-window? y-in-window?
;;;        [image-border-width? image-border-color?]])

;;; We believe that the clause "[image-border-width? image-border-color?]" was
;;; never emitted into KB files, and that but readers should remain ready to
;;; ignore this clause if they every happen to encounter it.  The mechinism that
;;; might have emitted this has been removed.

;; - ben 12/7/93



;;; `Make-pane-description' makes a pane description for pane, which does not
;;; include image plane descriptions for image planes with non-kb workspaces
;;; unless include- non-kb-workspaces? is non-nil.  If there is no such pane,
;;; nil is returned.  See also make-image-plane-description for the significance
;;; of record-window- position-too?.  Note that nil is a valid pane description;
;;; it describes a pane with no contents and is sometimes called a
;;; `null pane description'.

;; This doc doesn't look like it matchs the code. - ben 12/7/93

(defun make-pane-description
    (pane include-transient-kb-workspaces? record-window-position-too? module?)
  (loop for image-plane in (stack-of-image-planes pane)
	for workspace? = (workspace-on-image-plane? image-plane)
	when (and

	       ;; if this is showing a workspace:
	       workspace?
	       
	       ;; If we ever display image-planes from other remote G2s,
	       ;; i.e., via "Telewindows II", then exclude them here.
	       
	       ;; save only kb workspaces:
	       (frame-of-class-p workspace? 'kb-workspace)

	       ;; don't save transients, unless snapshotting:
	       (or include-transient-kb-workspaces?
		   (permanent-block-p workspace?))

	       ;; if saving a module, include only workspaces in that module:
	       (or (null module?)
		   (within-module-p workspace? module?)))
	  collect
	     (make-image-plane-description image-plane record-window-position-too?)
	    using slot-value-cons))


(defun create-pseudo-frame (item)
  (make-pseudo-frame item (copy-frame-serial-number (frame-serial-number item))))

;;; When saving, backing up or journalling a KB, a pane-description is made at the
;;; beginning of the save, and not written until the end of the save. By this
;;; time, the kb-workspaces within it may have been reclaimed. For this reason,
;;; a `modified-pane-description' is defined. If the structure of a
;;; pane-description is changed, then the modifier and reclaimer below must be
;;; redefined.

(defun modify-pane-description (pane-description)
  (loop for form in pane-description
	do (setf (first form) (create-pseudo-frame (first form))))
  pane-description)


(defun reclaim-modified-pane-description (modified-pane-description)
  (loop for form in modified-pane-description do
    (reclaim-pseudo-frame (prog1 (car form) (setf (car form) nil))))
  (reclaim-slot-value modified-pane-description))


;; `check-pane-description-for-unwritten-workspaces' will hopefully allow us to
;; catch a bug: this removes any image plane descriptions for workspaces that
;; have not yet been written -- if any are found, an error is signalled in
;; development -- there should not be any! (MHD 1/9/94)

(defun check-pane-description-for-unwritten-workspaces (modified-pane-description)
  (loop while 
	(loop for form in modified-pane-description
	      as pf = (first form)
	      as fsn = (pseudo-frame-frame-serial-number pf)
	      unless (loop for workspace being each class-instance of 'kb-workspace
			   when (frame-serial-number-equal (frame-serial-number workspace) fsn)
			     return
			     (cond
			       ((block-has-been-written-p workspace)
				t)
			       (t
				#+development
				(cerror
				  "Continue, with fix used in production (safe to do -- but tell MHD)"
				  "MHD: ~A, about to be H referenced, ~
                                   has not been written!"
				  workspace)
				nil)))
		do (setq modified-pane-description ; waste conses, since it's an error
					;   if this happens
			 (delq form modified-pane-description))
		   (return t)))
  modified-pane-description)



;;; `Make-image-plane-description' makes an image plane description for image-plane,
;;; which is assumed to have a workspace on it.

;;; Normally, the image plane will be restored so that the same workspace position
;;; will be at the center of the pane as at the time the image plane description
;;; was made, regardless of differences in pane position or size.  If record-
;;; window-position-too? is true, however, the position of the image plane in the
;;; window is also recorded and the image plane will be restored to the same position
;;; it had before in the window, without regard to the position of the pane.

(defun make-image-plane-description (image-plane record-window-position-too?)
  (let ((gensym-window
	  (gensym-window-for-pane (pane-for-image-plane image-plane)))
	x-in-workspace y-in-workspace)
    (with-image-plane-transform (image-plane)
      (setf x-in-workspace
	    (x-in-workspace
	      (halfr (+r (left-edge-of-pane-in-window image-plane)
			 (right-edge-of-pane-in-window image-plane)))))
      (setf y-in-workspace
	    (y-in-workspace
	      (halfr (+r (top-edge-of-pane-in-window image-plane)
			 (bottom-edge-of-pane-in-window image-plane))))))
    (nconc
      (slot-value-list
	(workspace-on-image-plane? image-plane)
	x-in-workspace y-in-workspace
	(convert-ratio-to-magnification
	  (image-x-scale image-plane)
	  (get-gensym-window-parameter gensym-window 'default-x-scale))
	(convert-ratio-to-magnification
	  (image-y-scale image-plane)
	  (get-gensym-window-parameter gensym-window 'default-y-scale)))
      (when record-window-position-too?
	(slot-value-list
	  (if record-window-position-too?
	      (halfr (+r (left-edge-of-pane-in-window image-plane)
			 (right-edge-of-pane-in-window image-plane))))
	  (if record-window-position-too?
	      (halfr (+r (top-edge-of-pane-in-window image-plane)
			 (bottom-edge-of-pane-in-window image-plane)))))))))

;; Consider allowing an image plane description to be made for an image plane without
;; a workspace on it, in which case documentation above would need revision.



;;; `Restore-image-planes-to-pane' restores onto pane the image planes described
;;; in pane-description, below any image planes that may already be on the pane,
;;; and excluding image planes described for workspaces already on an image plane
;;; in pane.

;;; The positions and scales of the restored image planes are determined from the
;;; image plane descriptions, as further discussed under make-image-plane-
;;; description above, but in addition the image plane is required to be visible
;;; by calling require-that-image-plane-be-visible after it is put up.

;;; Unless frame-serial-number? is nil, it is assumed that workspaces have not
;;; been reprocessed; if frame-serial-number? is non-nil, it is used to check
;;; each workspace, and if a workspace has been reprocessed, its entry is simply
;;; ignored. 

;;; If check-user-restrictions? is true, workspaces are subject to KB
;;; restrictions, and thus entries for workspaces not permitted to be shown in
;;; the current workstation according to KB restrictions will be simply
;;; ignored.  When check-user-restrictions? is true, restore-image-planes-to-
;;; pane assumes it is being called in a for-workstation context.

;;; If clear-image-planes-of-other-kb-workspaces? is true, this does not leave
;;; existing images for workspaces not specified by pane-description.  In other
;;; words, the layout of image planes for kb workspaces in pane is completely
;;; specified by pane-description.  Images for non-kb workspaces cannot be
;;; affected by this.  If, on the other hand, clear-image-planes-of-other-kb-
;;; workspaces? is nil, this leaves all kb workspaces as is; note that this means
;;; that you could have multiple images of the same workspace if workspaces
;;; included in pane-description could already be showing.

;;; If specific-module? is non-null, it is assumed to be a module (a symbol, the
;;; name of a module); in this case workspaces must belong the specified module
;;; in order to be restored.  This is intended particularly to be used when a
;;; module is merged in to an existing G2 KB; therefore, continue-read-kb
;;; supplies this argument when it reads in a module, since you generally do not
;;; want to have all the workspaces restored, but only those belonging to the
;;; module being merged.  Note: in past versions of G2 all workspaces would be
;;; restored in the merge, but this was ruled a bug (HQ-4851595 "when merging
;;; kb, top-level workspaces for ALL modules are shown") and fixed for G2 8.0r1
;;; (under development as of 8/4/04).

(defun restore-image-planes-to-pane
    (pane pane-description
	  &optional frame-serial-number? check-user-restrictions?
	  clear-image-planes-of-other-kb-workspaces?
	  specific-module?)
  (when clear-image-planes-of-other-kb-workspaces?
    (loop while
	  (loop for image-plane in (stack-of-image-planes pane)
		as workspace? = (workspace-on-image-plane? image-plane)
		when (and workspace?
			  (frame-of-class-p workspace? 'kb-workspace))
		  do (delete-image-plane image-plane)
		     (return t))))
  (loop with frame-description-reference
	as (workspace
	     workspace-x-at-center-of-pane workspace-y-at-center-of-pane
	     magnification-of-default-x-scale magnification-of-default-y-scale
	     x-in-window? y-in-window?
	     ;; image border width? and color?  -- no longer supported.
	     )
	   in pane-description
	when (and (or (null frame-serial-number?)
		      (not (frame-has-been-reprocessed-p
			     workspace frame-serial-number?)))
		  (or (null check-user-restrictions?)
		      (workspaces-can-be-shown-at-this-kb-level-p
			workspace current-workstation))
		  (or (null specific-module?)
		      (within-module-p workspace specific-module?))
		  (loop for image-plane		; don't show if already on an image plane
			    in (image-planes-this-is-on workspace)
			never
			(eq pane (pane-for-image-plane image-plane))))
	  do (setq frame-description-reference
		   (lookup-frame-description-reference-of-block? workspace))
	     (when (or (floatp magnification-of-default-x-scale)	; for KBs older than 12/5/87
		       (slot-value-float-p magnification-of-default-x-scale))
	       (setq magnification-of-default-x-scale
		     (convert-to-magnification
		       (slot-value-number-value magnification-of-default-x-scale))))
	     (when (or (floatp magnification-of-default-y-scale)	; for KBs older than 12/5/87
		       (slot-value-float-p magnification-of-default-y-scale))
	       (setq magnification-of-default-y-scale
		     (convert-to-magnification
		       (slot-value-number-value magnification-of-default-y-scale))))
	     (let ((image-plane
		     (get-available-image-plane
		       pane
		       frame-description-reference 
		       t)))
	       (put-image-on-image-plane
		 image-plane workspace
		 (magnify (get-gensym-window-parameter
			    (gensym-window-for-pane pane) 'default-x-scale)
			  magnification-of-default-x-scale)
		 (magnify (get-gensym-window-parameter
			    (gensym-window-for-pane pane) 'default-y-scale)
			  magnification-of-default-y-scale)
		 nil nil
		 workspace-x-at-center-of-pane workspace-y-at-center-of-pane
		 x-in-window? y-in-window?)
	       (require-that-image-plane-be-visible image-plane))))

;; Note: the 1.11B distribution KB colors.kb has a float.  Actually, it gets
;; read in as a managed float, not a float.  3.0 only checked for floats, so it
;; probably would not have survived loading in 3.0.  (MHD 10/15/93)

;; Args frame-serial-number? and check-user-restrictions? added today.  They are
;; only used by restore-current-workstation-detail-pane, earlier in FILES.
;; (MHD 4/16/90)






;;; Restore-image-planes-to-pane-now-or-later ...  Argument specific-module?  is
;;; ultimately passed on to restore-image-planes-to-pane, q.v., for doc.

(defun restore-image-planes-to-pane-now-or-later
       (pane-description &optional redisplay-logbook?	; new arg. (MHD 7/12/92)
			 specific-module?) ; new arg (MHD 8/4/04)

  ;; Older comment:  -mhd, 8/30/91
  ;; ;; Put saved detail pane configuration in a KB-specific
  ;; ;; (global) variable, to be restored on each workstation
  ;; ;; upon successful login.  Note: consider having save-
  ;; ;; kb update this variable; consider restoring it on
  ;; ;; telewindows that later log in for the first time.
  
  ;; Remove/reclaim any entries in the existing saved-detail-pane-description
  ;; for deleted workspace:
  (loop while
	  (loop as entry in saved-detail-pane-description
		when (frame-has-been-reprocessed-p
		       (car entry)
		       reference-serial-number-for-saved-detail-pane-description)
		  do (setq saved-detail-pane-description
			   (delete-slot-value-element
			     entry saved-detail-pane-description))
		     (reclaim-slot-value entry)
		     (return t)))
  ;; Append the old detail pane description to the new one, and make
  ;; the result be the current detail pane description:
  ;; being two image planes for each ws of the old KB.
  (setq saved-detail-pane-description
	(nconc
	  (copy-for-slot-value pane-description)
	  saved-detail-pane-description))
  ;; Revise frame reference serial number:
  (frame-serial-number-setf reference-serial-number-for-saved-detail-pane-description
  			    (current-frame-serial-number))
  ;; Restore as appropriate on various workstations
  (loop for workstation in workstations-in-service
	when (eq (workstation-login-state workstation) 'logged-in)
	  do (for-workstation (workstation)
	       (restore-current-workstation-detail-pane
		 backup-case?
		 redisplay-logbook?
		 specific-module?)
	       (when (and (boundp 'main-kb-being-read?) main-kb-being-read?)
		 (note-gensym-window-initialized current-workstation-window)))))



;;; `Put-workspace-into-detail-pane-layout' puts workspace at the front of the
;;; current saved detail-pane description.  If it is already present elsewhere,
;;; it is removed, and previous scaling/position information is discarded.
;;;
;;; This mutates the special variable saved-detail-pane-description, which holds
;;; the current saved pane layout pending restoration on newly logged in
;;; windows.
;;;
;;; It is arranged that workspace, when it appears, is put on a full-scale image
;;; plane, centered in the pane, frontmost in its stack.
;;; 
;;; This can be thought of as akin to a time-delayed version of the following
;;; call:
;;;
;;;   (put-workspace-on-pane workspace detail-pane 'center 'center nil)
;;;
;;; where detail-pane is the detail pane for each workstation at the time when
;;; saved-detail-pane-description is restored.
;;; 
;;;
;;; `Put-workspace-into-detail-panes' puts workspace on all currently logged in
;;; workstations' detail panes only.
;;; 
;;;
;;; `Put-workspace-on-detail-panes-now-or-later' does a combination of the two
;;; previous function, putting workspace on all currently logged in
;;; workstations' detail panes, as well as adding the workspace to the pane
;;; layout description to be restored upon subsequent workstations.


(defun put-workspace-into-detail-pane-layout (workspace)
  ;; Remove workspace from the description.  Also, revalidate
  ;; the global reference frame serial number, allowing us to
  ;; be able to add an arbitrary workspace and up the reference
  ;; to account for it.
  (loop while
	  (loop for image-plane-description in saved-detail-pane-description
		as stored-workspace = (first image-plane-description)
		when (or (eq stored-workspace workspace)
			 (frame-has-been-reprocessed-p
			   stored-workspace
			   reference-serial-number-for-saved-detail-pane-description))
		  do (setq saved-detail-pane-description
			   (delete-slot-value-element
			     image-plane-description
			     saved-detail-pane-description))
		     (reclaim-slot-value image-plane-description)
		     (return t)))
  ;; Add the workspace to the description.  Pushing it onto the end makes it be
  ;; frontmost.
  (setq saved-detail-pane-description
	(nconc
	  saved-detail-pane-description
	  (slot-value-list
	    (slot-value-list
	      workspace
	      (halfw (+w (left-edge-of-block workspace)
			 (right-edge-of-block workspace)))
	      (halfw (+w (top-edge-of-block workspace)
			 (bottom-edge-of-block workspace)))
	      (convert-to-magnification 1)
	      (convert-to-magnification 1)))))
  (frame-serial-number-setf reference-serial-number-for-saved-detail-pane-description
  			    (current-frame-serial-number)))

;; Code common to this and put-workspace-into-detail-pane-layout should
;; be factored out! (MHD 5/8/95)


(defun put-workspace-into-detail-panes (workspace)
  (loop for workstation in workstations-in-service
	when (eq (workstation-login-state workstation) 'logged-in)
	  do (for-workstation (workstation)
	       (put-workspace-on-pane
		 workspace
		 current-workstation-detail-pane
		 'center 'center nil))))


(defun put-workspace-on-detail-panes-now-or-later (workspace)
  (put-workspace-into-detail-pane-layout workspace)
  (put-workspace-into-detail-panes workspace))





;;;; Clearing and Releasing a KB



;;; `Empty-kb-p' is true if the current KB is considered `empty' for purposes
;;; of such things as requiring confirmation to replace it, displaying the
;;; system title block, allowing users into unknown user modes, and the like.

(defun empty-kb-p ()
  (null (instances-specific-to-this-class 'kb-workspace)))

;; This, or perhaps another predicate named changed-kb-p, probably should also
;; provided to determine if the current kb has had work put into it; as things
;; now stand, users could spend a lot of time, say, editing the kb-restrictions
;; system table, but G2 would not ask for confirmation if they tried to replace
;; the current kb.






;;; `Current-kb-serial-number' is a kb-specific variable bound to a fixnum
;;; integer that increases every time a new KB is created, i.e., when you do a
;;; clear-kb.

;;; Note that comparison of frame serial numbers is not valid across KBs.  When
;;; code is run that could potentially clear the KB within its dynamic scope,
;;; checking of the KB serial number must be done to see if a new KB has 
;;; resulted, and thus whether checking of frame serial numbers is valid, or
;;; whether, instead, all frames should just be assumed to have been deleted
;;; by virtue of the KB having been cleared and a new KB created.
;;;
;;; The sample code below evaluates (x) and then returns true if that cleared
;;; the KB, and nil otherwise.
;;;
;;;   (let ((saved-kb-serial-number current-kb-serial-number))
;;;      (x)
;;;      (>f current-kb-serial-number
;;;	     saved-kb-serial-number))

(def-kb-specific-variable current-kb-serial-number kb-save2
  (:funcall initialize-current-kb-serial-number))

(def-system-variable last-assigned-kb-serial-number kb-save2 -1)

(defun initialize-current-kb-serial-number ()
  (incff last-assigned-kb-serial-number))

;; Consider implementing workspace-has-been-reprocessed-p.  (The name is
;; analagous to frame-has-been-reprocessed-p.) (MHD 9/11/91)




;;; `Clear-kb' clears the current kb, by making a new empty kb with current system
;;; tables and releasing the old current kb.

;;; The following takes place:
;;;
;;;   (1) all workstation contexts are aborted;
;;;   (2) the inference engine is reset;
;;;   (3) a new empty KB is switched to;
;;;   (4) the old KB is released; 
;;;   (5) the file name component is cleared from all default loading pathnames; and
;;;   (6) the system title block is displayed.


;;; The function `clear-base-name-from-default-load-pathnames' modifies the
;;; default pathnames for G2-related file operations.  After clearing a KB, the
;;; user probably wants to continue defaulting to the same directory, but not to
;;; the name of the last-saved KB.  On file systems which don't support multiple
;;; versions, the user could inadvertantly overwrite the last KB saved before
;;; clearing.  So we change the default here.  We also change the default
;;; attribute file pathname and the default statistics file pathname under the
;;; same rationale, but we leave the default foreign image pathname intact, since
;;; this is something the user is likely to need across different KBs.

;; jh per mhd, 9/27/91.  

(defun-allowing-unwind clear-base-name-from-default-load-pathnames ()
  (macrolet ((clear-base-name (default-pathname-var g2-file-type)
	       `(when ,default-pathname-var
		  (protected-let*
		      ((user-name-string 
			   (tformat-text-string "~a" (get-current-user-name))
			   (reclaim-text-string user-name-string))			   
		       (working-pathname
			 (gensym-make-pathname
			   :name
			   user-name-string
			   :type     
			   (make-default-file-type ,g2-file-type)
			   :version  
			   :newest)
			 (reclaim-gensym-pathname working-pathname)))
		    (store-current-pathname ,default-pathname-var
					    (gensym-merge-pathnames
					      working-pathname
					      ,default-pathname-var))))))
    (clear-base-name current-kb-pathname? 'kb)
    (clear-base-name current-attribute-file-pathname? 'attribute)
    (clear-base-name current-statistics-file-pathname? 'statistics)))


(def-system-variable ui-client-interface-saved-icp-socket-list KB-SAVE2
  nil)

(def-system-variable ui-client-interface-saved-session-list KB-SAVE2
  nil)

(defun-simple make-storage-of-representation-data (representation)
  (let* ((slot-list (get-slots-to-save-in-clear-kb-for-representation representation))
	 (storage
	   (loop for slot-name in slot-list
		 for value
		     = (case slot-name
			 (callback-representation-callback-serial-number
			  ;; Mark as recycled, since all frames are getting recycled
			  ;; during clear-kb
			  (if (callback-representation-callback-serial-number representation)
			      (frame-serial-number-0)
			      nil))
			 (t
			  (get-slot-value representation slot-name)))
		 collect (case slot-name
			   (callback-representation-callback-serial-number
			    (copy-frame-serial-number value))
			   (item-representation-denotation
			    (copy-denotation value))
			   (representation-address
			    (loop for element in value
				  collect element using slot-value-cons))
			   (t
			    (copy-for-slot-value value)))
		   using gensym-cons)))
    (gensym-push (class representation) storage)
    storage))

(defvar deleting-ui-client-interfaces-for-clear-kb nil)

(defun save-and-delete-ui-client-interfaces ()
  (let ((saved-ui-client-sessions nil))
    (loop for frame being each class-instance of 'ui-client-session
	  do
      (gensym-push frame saved-ui-client-sessions)
      (gensym-push
	(gensym-list
	  (save-icp-object-map-for-registered-item frame)
	  (loop for slot-name in ui-client-session-slots-to-save-for-clear-kb
		for value = (get-slot-value frame slot-name)
		collect (copy-for-slot-value value)
		  using gensym-cons)
	  (loop with representation-list = nil
		for frame-representation in (frame-representations frame)
		do
	    (when (frame-of-class-p frame-representation 'callback-representation)
	      (gensym-push
		(make-storage-of-representation-data frame-representation)
		representation-list))
		finally
		  (return representation-list)))
	ui-client-interface-saved-session-list))
    (loop for frame being each class-instance of 'gsi-interface
	  for icp-socket? = (get-slot-value frame 'gsi-interface-icp-socket)
	  for connection-configuration = (car (get-slot-value frame 'gsi-connection-configuration))
	  do
      (when (and icp-socket? (runs-while-inactive-p frame))
	(gensym-push
	  (gensym-list icp-socket?
		       (if (consp connection-configuration)
			   (car connection-configuration)
			   nil)
		       (if (consp connection-configuration)
			   (copy-if-text-string (cadr connection-configuration))
			   nil)
		       (if (consp connection-configuration)
			   (copy-if-text-string (caddr connection-configuration))
			   nil)
		       (copy-if-text-string
			 (get-slot-value frame 'remote-process-initialization-string))
		       (get-slot-value frame 'name-or-names-for-frame)
		       (class frame)
		       (get-slot-value-if-any frame 'ui-client-interface-callback?)
		       (copy-if-evaluation-value
			 (get-slot-value-if-any frame 'ui-client-interface-callback-data))
		       (get-slot-value-if-any frame
					      'ui-client-interface-module-information-callback?)
		       (copy-if-evaluation-value
			 (get-slot-value-if-any frame
						'ui-client-interface-module-information-callback-data))
		       (get-slot-value-if-any frame 'ui-client-interface-progress-callback?)
		       (copy-if-evaluation-value
			 (get-slot-value-if-any frame 'ui-client-interface-progress-callback-data))
		       (get-slot-value-if-any frame 'ui-client-interface-dialog-callback?)
		       (copy-if-evaluation-value
			 (get-slot-value-if-any frame 'ui-client-interface-dialog-callback-data))
		       (copy-for-slot-value
			 (get-slot-value-if-any frame 'ui-client-interface-dialog-list))
		       (loop for session in (get-slot-value-if-any frame 'ui-client-interface-sessions)
			     collect (position session saved-ui-client-sessions)
			       using gensym-cons)
		       (save-icp-object-map-for-registered-item frame))
	  ui-client-interface-saved-icp-socket-list)
	(set-slot-value frame 'gsi-interface-icp-socket nil)
	(setf (enclosing-interface-frame? icp-socket?) nil)))
    (let ((deleting-ui-client-interfaces-for-clear-kb t))
      (loop for frame being each class-instance of 'gsi-interface
	    do (delete-frame frame)))
    (reclaim-gensym-list saved-ui-client-sessions)))

(defun-simple restore-ui-client-session-item-representations (frame representation-list)
  (let ((representations
	  (loop for representation-data in representation-list
		collect (restore-ui-client-session-item-representation
			  representation-data frame)
		  using slot-value-cons)))
    (setf (frame-representations frame) representations)))

(defun-simple restore-ui-client-session-item-representation (representation-data frame)
  (loop with representation-class = (car representation-data)
	with representation = (make-frame representation-class)
	initially (setf (represented-frame representation) frame)
	for slot-name in (get-slots-to-save-in-clear-kb-for-representation representation)
	for value in (cdr representation-data)
	do
    (if  (eq slot-name 'callback-representation-callback-serial-number)
	 (frame-serial-number-setf
	   (callback-representation-callback-serial-number representation)
	   value)
	 (change-slot-value representation slot-name value))
    finally
	  (let* ((address? (representation-address representation))
		 (icp-socket? (and address?
				   (getf address? 'socket))))
	    (and icp-socket?
		 (not (eq icp-socket? local-pseudo-socket))
		 (gensym-push representation
			      (icp-socket-representations icp-socket?))))
 	  (when (eq representation-class 'item-representation)
 	    (let ((denotation (item-representation-denotation representation)))
 	      (multiple-value-bind (definition-error-or-inner-item-index
 				       class-description?)
 		  (check-denotation-well-defined frame denotation)
 		(cond ((access-error-p definition-error-or-inner-item-index)
 		       #+development
 		       (cerror "continue" "previously checked denotation failed")
 		       ;; NOTE that the denotation was checked the first time
 		       ;; the original was made, so this should never happen,
 		       ;; on the the other hand
 		       ;; proceeding with the install-subscription would lead
 		       ;; to further corruption
 		       (warning-message 1 "Unable to restore ui-client-session ~NF properly"
 			   frame))
 		      (t (install-subscription
 			   class-description?
 			   representation
 			   denotation
 			   definition-error-or-inner-item-index))))))
	(store-callback-representation representation)
	(reclaim-gensym-list representation-data)
	(return representation)))

(def-post-loading-function restore-ui-client-interfaces
  (let ((sessions
	  (loop while ui-client-interface-saved-session-list
		for frame-spec = (gensym-pop ui-client-interface-saved-session-list)
		for (icp-object-map slot-value-list representation-list) = frame-spec
		for frame = (make-ui-client-session-internal)
		do
	    (restore-icp-object-map-for-registered-item frame icp-object-map)
 	    ;; if the leak of nonce data that is associated with
 	    ;; deleting a ui-client-session is ever fixed, then the
 	    ;; squirrelled nonce data being restored here should be put
 	    ;; back into the nonce-data tree.
	    (loop for slot-name in ui-client-session-slots-to-save-for-clear-kb
		  for value in slot-value-list
		  do (change-slot-value frame slot-name value))
	    (restore-ui-client-session-item-representations frame representation-list)
	    (reclaim-gensym-list representation-list)
	    (reclaim-gensym-list slot-value-list)
	    (reclaim-gensym-list frame-spec)
		collect frame using gensym-cons)))
    (loop while ui-client-interface-saved-icp-socket-list
	  for frame-spec = (gensym-pop ui-client-interface-saved-icp-socket-list)
	  for (current-icp-socket
		network-type host port
		remote-process-initialization-string
		name-or-names-for-frame
		class
		callback? callback-data
		module-information-callback?
		module-information-callback-data
		progress-callback? progress-callback-data
		dialog-callback? dialog-callback-data
		dialog-list
		session-position-list
		icp-object-map)
	      = frame-spec
	  do
      (reclaim-gensym-list frame-spec)
      (let ((ui-client-interface
	      (g2-initialize-gsi-interface
		name-or-names-for-frame
		class
		t network-type host port
		remote-process-initialization-string
		t)))
	(restore-icp-object-map-for-registered-item ui-client-interface icp-object-map)
	(when (frame-of-class-p ui-client-interface 'ui-client-interface)
	  (change-slot-value
	    ui-client-interface
	    'ui-client-interface-sessions
	    (loop for position in session-position-list
		  for session = (nth position sessions)
		  do (change-slot-value session 'ui-client-session-parent-interface ui-client-interface)
		  collect session
		    using slot-value-cons))
	  (change-slot-value
	    ui-client-interface
	    'ui-client-interface-callback?
	    callback?)
	  (change-slot-value
	    ui-client-interface
	    'ui-client-interface-callback-data
	    callback-data)
	  (change-slot-value
	    ui-client-interface
	    'ui-client-interface-module-information-callback?
	    module-information-callback?)
	  (change-slot-value
	    ui-client-interface
	    'ui-client-interface-module-information-callback-data
	    module-information-callback-data)
	  (change-slot-value
	    ui-client-interface
	    'ui-client-interface-progress-callback?
	    progress-callback?)
	  (change-slot-value
	    ui-client-interface
	    'ui-client-interface-progress-callback-data
	    progress-callback-data)
	  (change-slot-value
	    ui-client-interface
	    'ui-client-interface-dialog-callback?
	    dialog-callback?)
	  (change-slot-value
	    ui-client-interface
	    'ui-client-interface-dialog-callback-data
	    dialog-callback-data)
	  (change-slot-value
	    ui-client-interface
	    'ui-client-interface-dialog-list
	    dialog-list)
	  ;; there should only be one module-information at this time
	  (loop for module-info being each class-instance of 'module-information
		do
	    (inform-ui-client-interface-of-module-creation
	    module-info ui-client-interface)))))
    (reclaim-gensym-list sessions)))

(defvar in-clear-kb-p nil)

(defun clear-kb (&optional reading-kb?)
  (with-backtrace-for-internal-error 'clear-kb-internal
    (let ((old-kb-specific-property-list-property-name
	   *current-kb-specific-property-list-property-name*)
	  (do-not-note-permanent-changes-p t)
	  (in-clear-kb-p t))
      (loop for workstation in workstations-in-service
	    unless (and servicing-workstation?
			(eq current-workstation workstation))
	    do (for-workstation (workstation)
		   (unwind-current-workstation-back-to-top-level))
	    finally ;; in the correct contour
	      (when servicing-workstation?
		(unwind-current-workstation-back-to-top-level)))

      (clear-all-twng-disconnect-callbacks)

      (inform-ui-client-interfaces-of-clear-kb)

      (unedit-up-to-date-modules)

      (shut-down-g2ds-clients-for-clear-kb) ;Added (jh, 10/3/91)

      (system-reset)				; arg to suppress this?  later, can cut 
						;   corners knowing KB's being cleared!

      (run-state-change-hook 'clear-kb)		; If system was already reset, former call did nothing.

      (switch-to-new-empty-kb)			; this initializes system frames

      ;; GENSYMCID-1209: Clear KB doesn't recover the title of TW/TWNG
      (loop for workstation in workstations-in-service
	    as gensym-window = (window-for-workstation workstation)
	    do
	(set-window-title gensym-window nil))

      (clear-inspect-command-history-list) ; clear inspect command history

      (release-kb old-kb-specific-property-list-property-name t nil nil)
      (release-all-kb-write-locks)
      (make-or-clear-complete-kb-name "new-kb" t)
      ;; Clear-kb will now reset the frame-serial-number counter
      ;; It is assumed that there is now only one KB, that it
      ;; was newly created, and that none of its frames are being referenced.
      (reset-current-frame-serial-number)
      (setq use-current-time-for-next-uuid t)
      (loop for frame being each class-instance of 'block do
	(frame-serial-number-setf (frame-serial-number frame)
				  (increment-current-frame-serial-number)))
      (setq next-class-bit-number (1+f last-system-class-bit-number))

      (clear-base-name-from-default-load-pathnames)

      (unless reading-kb?
	(restore-ui-client-interfaces))
      
      #+pre-g2-v5-licensing
      (restore-authorization-if-temporary)
      (unless reading-kb?		; see note (MHD 1/29/01)
	(display-credits)))))

;; Consider having an option to preserve the current system tables.

;; Consider having this really clear the current kb without creating a new one.

;; The title block is annoying users, so having it at least not show up every
;; time you load a KB, just when you start up or explicitly clear the KB, should
;; help out in a very safe way. (MHD 1/29/01)




;;; `Release-kb' deletes everything in the kb specified by kb-specific-property-list-
;;; property-name.  

;;; The following happens in order
;;;
;;;   (1) if also-clear-windows? is non-nil, close-logbooks is invoked
;;;       and all image planes belonging to the kb are deleted;
;;;       
;;;   (2) if try-to-do-deferred-user-notifications? is non-nil, that
;;;       will be done in the new KB;
;;;   
;;;   (3) all frames in the old KB are deleted;
;;;
;;;   (4) all kb-specific properties are reclaimed -- if
;;;       keep-locations-entry? is non-nil, the entry for
;;;       kb-specific-property-list-property-name in
;;;       *locations-of-kb-specific-property-lists* will
;;;       be kept;
;;;       
;;;   (5) all kb-specific variables with value reclaimers
;;;       are reclaimed; and

;;; While the kb is being released, special variable releasing-kb? is bound to a non-nil
;;; value.  In this state, certain cleanup steps may be omitted, in order to save time.
;;; For example, delete-from-directory-of-symbols may do nothing at all when releasing-kb?
;;; is non-nil, knowing that all directories will in any case be ultimately eliminated
;;; (and reclaimed more efficiently) by reclaim-kb-specific-property-lists-of-kb.

(defvar releasing-kb? nil)

(defun-allowing-unwind release-kb
    (kb-specific-property-list-property-name also-clear-windows? keep-locations-entry?
                                             try-to-do-deferred-user-notifications?)

  (let ((releasing-kb? t)
	(old-kb-specific-property-list-property-name
	 *current-kb-specific-property-list-property-name*))

    (in-kb (kb-specific-property-list-property-name)

      (cond
	(also-clear-windows?
	 (close-logbooks)               ; see module BOOKS
	 (loop for workstation in workstations-in-service
	       as gensym-window = (window-for-workstation workstation)
	       do (loop for pane in (panes-in-window gensym-window)
			do (loop while
				   (loop with image-plane-to-delete? = nil
					 as image-plane in (stack-of-image-planes pane)
					 ;; assumed: no TWII capability yet
					 do (setq image-plane-to-delete? image-plane)
					 finally
					   (return
					     (if image-plane-to-delete?
						 (cond
						   ((eq (car (stack-of-image-planes pane))
							image-plane-to-delete?)
						    (delete-image-plane
						      image-plane-to-delete?)
						    nil)
						   (t (delete-image-plane
							image-plane-to-delete?)
						      t))))))))))
    
      (if try-to-do-deferred-user-notifications?
	  (in-kb (old-kb-specific-property-list-property-name)
	    (try-to-do-deferred-user-notifications)))

      (note-progress #w"Clearing KB" 0)

      ;; Recycle everything in kb, by doing a delete-frame on all frames (all
      ;; workspaces?) in the kb (in a mode where loose-ends are not created).
      (loop for a-block being class-instances of 'block
	    do
	(permanently-retract-consistency-analysis a-block))

      (delete-frame-list
	(nconc				; all workspaces and system frames
	  (loop for workspace being class-instances of 'workspace
		collect workspace using gensym-cons) ; See Note A.
	  (loop for system-frame being class-instances of 'system-frame
		collect system-frame using gensym-cons)))
      (delete-frame-list
	(loop for frame being class-instances of 'block	; all remaining frames
	      unless (or (frame-of-class-p frame 'ui-client-interface)
			 (frame-of-class-p frame 'ui-client-session))
		collect frame using gensym-cons))
      (save-and-delete-ui-client-interfaces)

      (delete-classes-queued-by-delete-frame classes-to-delete-when-releasing-kb)
      (setq classes-to-delete-when-releasing-kb nil)

      (reclaim-kb-specific-properties keep-locations-entry?)

      (reclaim-values-of-kb-specific-variables current-system-name)
      (note-progress))))


(defun-void delete-frame-list (frames-to-delete)
  (let ((ref (copy-frame-serial-number (current-frame-serial-number))))
    (loop for frame in frames-to-delete
	  unless (frame-has-been-reprocessed-p frame ref)
	    do (delete-frame frame))
    (reclaim-frame-serial-number ref)
    (reclaim-gensym-list frames-to-delete)))

;; Note A: System frames must be reclaimed after the workspaces, since
;; pointer run into the system frames from the rest of the KB.  See
;; computation-styles in CELLs for an example.  (ben 4/25/91)








;;;; KB State Changes



;;; `Note-kb-state-change' records, in the original-kb-state-plist slot of frame, the
;;; (present and presumably original) value of kb-state-variable for frame if no such
;;; value is yet recorded and if frame is not transient.  Kb-state-variable may be any
;;; of the following:
;;;      WORKSPACE-FRAME, with value (workspace-left  workspace-top 
;;;                                   workspace-right workspace-bottom);
;;;
;;;      ITEM-POSITION, with value (item-x-position . item-y-position);
;;;      
;;;      ICON-POSITION, with value (icon-x-position . icon-y-position);  [OBSOLETE! (MHD 1/29/90)]
;;;
;;;      ICON-ORIENTATION, with the reflection-and-rotation icon attribute as the value;
;;;
;;;      ICON-COLOR, with the line-color icon attribute as the value; or
;;;
;;;      ICON-COLOR-PATTERN, with an icon-color-change-pattern (made up of slot
;;;	   value conses) for changing back to the original value.
;;;
;;;      WORKSPACE-COLOR-PATTERN, with a color change pattern based on the existing
;;;        values of the workspace color regions. The names of the regions are
;;;        background-color or foreground-color.  Frame should be a workspace.
;;;
;;;      TEXT-BOX-COLOR-PATTERN, with a color change pattern based on the existing
;;;        values of the text-box color regions. The names of the regions are
;;;        background-color, text-color, and border-color.  Frame should be a
;;;        text box.
;;;
;;;      TEXT-COLOR, with a color based on the existing value of the text box
;;;        text-color region.  Frame should be a text-box.
;;;      
;;;      BORDER-COLOR, with a color based on the existing value of the text box
;;;        border-color region.  Frame should be a text-box.
;;;
;;;      BACKGROUND-COLOR, with a color based on the existing value of the text box
;;;        background-color region, if frame is a text box, or else the workspace 
;;;        background-color region, if frame is a workspace.  Frame should be a text-
;;;        box or a workspace.
;;;
;;;      FOREGROUND-COLOR, with a color based on the existing value of the workspace
;;;        foreground-color region, if frame is a text box, or else the workspace 
;;;        foreground-color region, if frame is a workspace.  Frame should be a
;;;        workspace.
;;;
;;;      CONNECTION-COLOR-PATTERN, with the cross section regions of the current
;;;        connection cross section pattern for frame, which should be a connection.
;;;
;;;      STRIPE-COLOR, with the current connection cross section pattern for frame,
;;;        which should be a connection.
;;;
;;;      TEXT, with the text of frame, which should be a message.  (Note that text
;;;        is a text copy of the cdr of the box-translation-and-text slot of frame;
;;;        the car is not copied or recorded.)
;;; 
;;;      G2-ARRAY-LENGTH, with a length based on the existing value of the 
;;;        g2-array-length slot of frame, which should be a g2-array.
;;;
;;;      ;; New for G2 5.0:  (4.0 added system procedures that just changed
;;;                           font and magnification permanently)
;;;
;;;      TEXT-BOX-FONT
;;;
;;; It also records frame as a frame that has had a kb state change, if it is not
;;; already so recorded and, again, as long as frame is not transient.
;;;
;;; The kb-state-variable is used as a key for in the original-kb-state-plist of the frame.
;;; In addition to those keys enumerated above these keys may appear in that plist.
;;;      TEXT-OF-CHANGED-SLOTS is used by note-kb-state-change-to-slot-by-saving-text.
;;;        It is used to record arbitrary changes made to system-attributes via the
;;;        change action and statement.

;;; It is a curiosity of this implementation and hand edits done may also be undone.  This
;;; happens if an entry is made in the kb-state-changes prior to the user making a hand edit.

(defvar ignore-kb-state-changes-p nil)

(defun note-kb-state-change (frame kb-state-variable)
  (let ((original-kb-state-plist (original-kb-state-plist frame)))
    (unless (or ignore-kb-state-changes-p
		(transient-p frame)
		(loop for indicator in original-kb-state-plist by #'cddr
		      thereis (eq indicator kb-state-variable)))
      ;; The above test replaces
      ;; 
      ;;   (null (getfq original-kb-state-plist kb-state-variable))
      ;;   
      ;; which had the defect of not distinguishing the case of a
      ;; kb state variable value never having been recorded from
      ;; that of kb state variable having been recorded with the
      ;; value nil. (MHD 12/01/89)
      (if (null original-kb-state-plist)
	  (note-as-frame-with-kb-state-changes frame))
      (setf (original-kb-state-plist frame)
	    (slot-value-cons
	      kb-state-variable
	      (slot-value-cons
		(case kb-state-variable
		  (workspace-frame
		   (slot-value-list
		     (left-edge-of-block frame)
		     (top-edge-of-block frame)
		     (right-edge-of-block frame)
		     (bottom-edge-of-block frame)))
		  ((item-position icon-position) ; icon-position is OBSOLETE!
		   (slot-value-cons (item-x-position frame) (item-y-position frame)))
		  (icon-orientation
		   (getf (icon-attributes-plist frame) 'reflection-and-rotation))
		  (icon-color
		   (getf (icon-attributes-plist frame) 'line-color))
		  (icon-color-pattern
		   (get-icon-color-pattern frame))
		  (workspace-color-pattern
		   (get-workspace-color-pattern frame))
		  (text-box-color-pattern
		   (get-text-box-color-pattern frame))
		  (connection-color-pattern
		   (get-connection-color-pattern frame))
		  (text-color			; for text boxes
		   (getf (text-cell-plist-for-text-box frame) 'line-color))
		  (border-color		; for text boxes
		   (getf (text-cell-plist-for-text-box frame)
			 'border-color))
		  (background-color		; for text boxes or workspaces
		   (frame-class-case frame
		     (workspace
		       (workspace-background-color? frame))
		     (t			; otherwise, a text box
		       (getf (text-cell-plist-for-text-box frame)
			     'background-color))))
		  (foreground-color		; for workspaces
		   (workspace-foreground-color? frame))
		  (stripe-color
		   (copy-tree-using-slot-value-conses
		     (cross-section-pattern frame)))
		  (text			; for messages
		   (copy-text
		     (cdr (box-translation-and-text frame))))
		  (g2-array-length
		   (g2-array-length-function frame))
		  (text-box-font
		   (make-original-value-for-text-box-font-kb-state-change
		     frame)))
		original-kb-state-plist))))))

;; Changed to do nothing for transient items. (MHD 2/22/90)


;;; `Note-kb-state-change-to-slot' records, in the original-kb-state-plist slot
;;; of frame, in a manner analagous to note-kb-state-change, current value of a
;;; slot.  If this is a text type slot, the original text is saved out;
;;; otherwise, the slot value is converted to a text string via the slot writer
;;; and that is recorded.  Upon reset the slot will be restored to this value as
;;; if the user editted the slot back again.  No record is made if the frame is
;;; transient.  No record is made if a record was already made for this
;;; particular slot.
;;;
;;; The use of this mechanism is restricted to slots that can be restored in any
;;; order.
;;;
;;; A composite entry on the original-kb-state-plist.  This entry is a plist
;;; where the keys are slot names, and values are text strings.
;;;
;;; If frame is transient-p, this does nothing at all.
;;;
;;; Note that slot components (i.e., for now, trend chart slot components) are
;;; not currently able to be handled by this facility.  (They are not currently
;;; amenable to change-the-text-of actions.)

(defun note-kb-state-change-to-slot-by-saving-text (frame slot-description)
  (unless (or ignore-kb-state-changes-p
	      (transient-p frame))
    (when (null (original-kb-state-plist frame))
      (note-as-frame-with-kb-state-changes frame))
    (let* ((plist-entry
	     (or
	       (loop for plist-entry on (original-kb-state-plist frame) by #'cddr
		     when (eq 'text-of-changed-slots (first plist-entry))
		       do (return plist-entry))
	       (setf (original-kb-state-plist frame)
		     (nconc
		       (slot-value-list 'text-of-changed-slots nil)
		       (original-kb-state-plist frame)))))
	   (slot-denotation
	     (denote-slot-using-slot-value-conses
	       slot-description
	       (class-description-slot frame))))
      (unless (if (atom slot-denotation)
		  (getf (second plist-entry) slot-denotation)
		  (loop for (name value) on (second plist-entry) by 'cddr
			thereis (equal name slot-denotation)))
	(setf (second plist-entry)
	      (slot-value-cons
		slot-denotation
		(slot-value-cons
		  (if (text-slot-type-p
			(feature-assq 'type (slot-features slot-description)))
		      (copy-text
			(cdr
			  (get-slot-description-value frame slot-description)))
		      ;; make a text: more direct than what was previously here,
		      ;; creating an string, and then turning that into a text.
		      ;; This new approach may also avoid transient huge
		      ;; strings.  Note that the consumer deals with either
		      ;; type, text-string or text.  (MHD 1/24/96)
		      (make-text-representation-for-slot-description-value
			frame slot-description))
		  (second plist-entry))))))))

;; Does make-text-string-representation-for-slot-value live in the right module?

(defvar do-not-note-permanent-changes-p nil)

(defun-void note-permanent-change (frame slot-description)
  (unless do-not-note-permanent-changes-p
    (when (and (frame-of-class-p frame 'item) ; skip dependent-frames like g2-cell-arrays
	       (not (transient-p frame))
	       (permanent-block-p frame)
	       (item-was-created-by-load-p frame)
	       (or (superior-frame frame)
		   (frame-of-class-p frame 'kb-workspace)
		   (frame-of-class-p frame 'system-frame))
	       ;;(slot-value-is-permanent-p frame slot-description)
	       (not (memq (reason-to-exclude-slot-description-for-compute-class-description-node-attributes
			    slot-description)
			  ;; also: no-type no-category-in-type-specification neither-rw-cei-nor-slot-value-writer
			  '(depreciated dependant not-savable)))) 
      (note-permanent-changes frame slot-description))))

(defun note-permanent-change-to-slot-group-for-block (frame)
  (unless do-not-note-permanent-changes-p
    (when (and (frame-of-class-p frame 'item) ; skip dependent-frames like g2-cell-arrays
	       (not (transient-p frame))
	       (permanent-block-p frame)
	       (item-was-created-by-load-p frame)
	       (or (superior-frame frame)
		   (frame-of-class-p frame 'kb-workspace)
		   (frame-of-class-p frame 'system-frame)))
      (note-permanent-changes
	frame
	(get-slot-description-of-frame
	  'slot-group-for-block? frame)))))

(defun-void note-permanent-change-to-component
    (frame slot-description slot-component-name? slot-component-indicator?)
  (declare (ignore slot-component-name? slot-component-indicator?))
  (note-permanent-change frame slot-description))

(defun note-permanent-changes (frame slot-description-or-symbol-or-state-plist)
  (let ((attributes-permamently-changed (attributes-permamently-changed frame)))
    (cond ((eq attributes-permamently-changed t)
	   nil)
	  ((symbolp slot-description-or-symbol-or-state-plist)
	   (setf (attributes-permamently-changed frame) t))
	  ((consp slot-description-or-symbol-or-state-plist)
	   (loop for (name value) on slot-description-or-symbol-or-state-plist by #'cddr
		 for denotations in (denotations-of-slots-given-state-change-name name frame)
		 do
	     (loop for slot-denotation in denotations
		   do (unless (memq slot-denotation attributes-permamently-changed)
			(slot-value-push slot-denotation attributes-permamently-changed))))
	   (setf (attributes-permamently-changed frame) attributes-permamently-changed))
	  (t
	   (let ((slot-denotation (denote-slot-using-slot-value-conses
				    slot-description-or-symbol-or-state-plist
				    (class-description-slot frame))))
	     (unless (if (atom slot-denotation)
			 (memq slot-denotation attributes-permamently-changed)
			 (member-equal slot-denotation attributes-permamently-changed))
	       (slot-value-push slot-denotation attributes-permamently-changed)
	       (setf (attributes-permamently-changed frame) attributes-permamently-changed))))))
  nil)

(defun note-saving-frame (frame)
  (clear-block-permanently-changed frame)
  (set-item-was-created-by-load frame)
  (let ((attributes-permamently-changed (attributes-permamently-changed frame)))
    (when attributes-permamently-changed
      (reclaim-slot-value attributes-permamently-changed)
      (setf (attributes-permamently-changed frame) nil))))

(defun-simple slot-value-is-permanent-p (frame slot-description)
  (or (not (frame-of-class-p frame 'block))
      (loop with slot-denotation = (denote-slot-using-slot-value-conses
				     slot-description
				     (class-description-slot frame))
	    for (name value) on (original-kb-state-plist frame) by #'cddr
	    when (or (and (eq 'text-of-changed-slots name)
			  (if (atom slot-denotation)
			      (getf value slot-denotation)
			      (loop for (name1 value1) on value by 'cddr
				    thereis (equal name1 slot-denotation))))
		     (memq slot-denotation
			   (denotations-of-slots-given-state-change-name name frame)))
	      return nil
	    finally (when (consp slot-denotation)
		      (reclaim-slot-value slot-denotation))
			 (return t))))

(defun-simple denotations-of-slots-given-state-change-name (name frame)
  (case name
    ;; workspace-frame item-position icon-position
    ((icon-orientation icon-color)
     '(icon-attributes-plist))
    ((icon-color-pattern workspace-color-pattern
			 text-box-color-pattern get-text-box-color-pattern)
     '(icon-attributes-plist))
    ((text-color border-color)
     '(text-cell-plist-for-text-box))
    (background-color		; for text boxes or workspaces
     (frame-class-case frame
       (workspace '(workspace-background-color?))
       (t	  '(text-cell-plist-for-text-box))))
    (foreground-color		; for workspaces
     '(workspace-foreground-color?))
    (text			; for messages
     '(box-translation-and-text))
    (text-box-font
     '(text-cell-plist-for-text-box text-box-format))))



;;; `Note-as-frame-with-kb-state-changes' must be called to record frame as
;;; having kb state changes, i.e., whenever the original-kb-state-plist slot of
;;; frame changes to take on a non-nil value.  Note, however, that when
;;; original-kb-state-plist is restored from a KB, this is not called.

;;; `Remove-as-frame-with-kb-state-changes' must be called to record
;;; that frame has no kb state changes, i.e., whenever original-kb-state-plist is
;;; made nil.

;;; As long as they are called when the original-kb-state-plist slot of frame
;;; has its appropriate value, these functions are safe to call more than once
;;; on a frame.

;;; Note that "frame" here must actually be a block.  There is no use for this
;;; facility with non-block frames.

(defun-void note-as-frame-with-kb-state-changes (frame)
  (unless (kb-state-changes-previous-cons? frame)
    (setf (first kb-state-changes) frame)
    (setq kb-state-changes (kb-property-cons nil kb-state-changes))
    (setf (kb-state-changes-previous-cons? frame) kb-state-changes)))

(defun-void remove-as-frame-with-kb-state-changes (frame)
  (let ((previous-cons? (kb-state-changes-previous-cons? frame)))
    (when previous-cons?
      (let* ((this-cons (cdr previous-cons?))
	     (next-cons? (cdr this-cons))
	     (next-frame? (first next-cons?)))
	#+development
	(test-assertion (eq frame (first this-cons)))
	(setf (kb-state-changes-previous-cons? frame) nil)
	(setf (cdr this-cons) nil)
	(reclaim-kb-property-cons this-cons)
	(setf (cdr previous-cons?) next-cons?)
	(when next-frame?
	  (setf (kb-state-changes-previous-cons? next-frame?) previous-cons?))))))





;;; `Undo-kb-state-changes' undoes all kb state changes for the current kb.

;;; This is invoked when the system is reset.  Guided by the entries on
;;; kb-state-changes modifications to the KB done by actions are undone.  It is
;;; a curiosity of this implementation that hand edits done may also be undone.
;;; This happens when a change by an action records an entry in kb-state-changes
;;; before the user does his hand edit.  See the documentation on
;;; note-kb-state-change for a full enumeration of the kinds of changes
;;; recorded.

;;; If the user asks to save the current kb when there are kb state changes from
;;; running, the user SHOULD be given the choice of undoing those changes or not
;;; before the save takes place.  If the user elects NOT to undo the changes,
;;; there will be no way of undoing them when the saved kb is subsequently
;;; loaded.  [Actually, as of 6/23/88, any kb state changes are always
;;; automatically done before the save takes place.]

(defun undo-kb-state-changes ()
  (when (cdr kb-state-changes)
    (let ((list (cdr kb-state-changes)))
      (setf (cdr kb-state-changes) nil)
      (loop for frame in list
	    do (setf (kb-state-changes-previous-cons? frame) nil)
	       (undo-kb-state-changes-for-frame frame))
      (reclaim-kb-property-list list))))

(defmacro color-change-p (change-symbol)
  `(memq ,change-symbol
	 '(icon-color icon-color-pattern text-box-color-pattern
	   background-color border-color foreground-color text-color
	   connection-color-pattern)))

;;; The function `undo-kb-state-changes-for-frame' is used to undo the KB state
;;; changes for the given frame.

;;; Note that this function also has the side affect of reclaiming the kb state
;;; plist and *not* the corresponding element from the kb state changes
;;; variable.

(defun undo-kb-state-changes-for-frame (frame)
  (loop for plist			; begins with kb-state-variable
	on (original-kb-state-plist frame) by 'cddr
	as (kb-state-variable original-value) = plist
	do (case kb-state-variable
	     (workspace-frame
	      (cond 
		#+development
		((not (workspace-p frame))
		 (cerror "Continue"
			 "Only workspaces can have workspace-frames")
		 nil)
		((has-subblocks-p frame)
		 (multiple-value-bind (extreme-left-edge
				       extreme-top-edge
				       extreme-right-edge
				       extreme-bottom-edge)
		   (determine-extreme-edges-of-workspace-subblocks frame)
		   (let ((workspace-margin (workspace-margin frame)))
		     (decff extreme-left-edge workspace-margin)
		     (decff extreme-top-edge workspace-margin)
		     (incff extreme-right-edge workspace-margin)
		     (incff extreme-bottom-edge workspace-margin)
		     (new-change-workspace-edges
		      frame
		      (minf extreme-left-edge (first original-value))
		      (minf extreme-top-edge  (second original-value))
		      (maxf extreme-right-edge (third original-value))
		      (maxf extreme-bottom-edge (fourth original-value))))))
		(t
		 (new-change-workspace-edges
		  frame 
		  (first original-value) (second original-value)
		  (third original-value) (fourth original-value)))))
	     (item-position
	      (let* ((new-x (car original-value))
		     (new-y (cdr original-value))
		     (delta-x (-w (round-macro new-x)(item-x-position frame)))
		     (delta-y (-w (round-macro new-y)(item-y-position frame))))
		(move-item-by frame delta-x delta-y nil)
		(when (and g2-has-v5-mode-windows-p
			   (not ws-protocol-handle-moves-from-edge-change-p))
		  (send-ws-representations-item-moved frame delta-x delta-y))))
	     (icon-position			; OBSOLETE!
	      (move-icon
		frame (car original-value) (cdr original-value)))
	     (icon-orientation
	      (let ((reflection-and-rotation
		      (multiply-reflection-and-rotation
			(invert-reflection-and-rotation
			  (getfq (icon-attributes-plist frame)
				 'reflection-and-rotation))
			original-value)))
		(rotate-and-reflect-icon
		  frame				
		  (case reflection-and-rotation
		    ((reflected normal nil) 0)
		    ((reflected-clockwise-90 clockwise-90) 90)
		    ((reflected-clockwise-180 clockwise-180) 180)
		    ((reflected-clockwise-270 clockwise-270) 270))
		  (memq reflection-and-rotation
			'(reflected
			  reflected-clockwise-90
			  reflected-clockwise-180
			  reflected-clockwise-270))
		  nil nil nil)))
	     (icon-color
	      (change-color-of-icon frame nil original-value))
	     (icon-color-pattern
	      (change-color-pattern-of-icon frame nil original-value))
	     
	     ;; new ones added: (MHD 7/21/89, 8/3/89)
	     (workspace-color-pattern
	      (change-color-of-workspace
		frame nil
		(cdr (assq 'background-color original-value))
		(cdr (assq 'foreground-color original-value))))
	     (text-box-color-pattern
	      (change-color-of-text-box
		frame nil
		(cdr (assq 'background-color original-value))
		(cdr (assq 'border-color original-value))
		(cdr (assq 'text-color original-value))))
	     (background-color			; for text boxes or workspaces
	      (frame-class-case frame
		(workspace
		  (change-color-of-workspace
		    frame nil
		    original-value :no-change))
		(t				; otherwise, a text box
		  (change-color-of-text-box
		    frame nil
		    original-value :no-change :no-change))))
	     (border-color			; for text boxes
	      (change-color-of-text-box
		frame nil
		:no-change original-value :no-change))
	     (foreground-color			; for workspaces
	      (change-color-of-workspace
		frame nil
		:no-change original-value))
	     (text-color			; for text boxes
	      (change-color-of-text-box
		frame nil
		:no-change :no-change original-value))
	     (connection-color-pattern		; similar to icon-color-pattern
	      (change-color-pattern-of-connection
		frame nil original-value))
	     (stripe-color
	      (let* ((connection
		       (connection-for-this-connection-frame
			 frame))
		     (workspace
		       (superblock? (output-end-object connection))))
		(update-connection-images
		  t workspace connection)
		(change-slot-value 
		  frame 'cross-section-pattern 
		  original-value)
		(setf (cadr plist) nil)		; prevents double reclamation
		(update-connection-images
		  nil workspace connection)
		;; Consider revising this to use something like 
		;; change-color-pattern-of-connection so that 
		;; erase is not necessary.  The difficulty is 
		;; that when stripe-color is changed, colors
		;; in the cross-section-stripes as well as in the
		;; cross-section-regions may be changed.
		))
	     (text-of-changed-slots
	      (loop for plist on original-value by #'cddr
		    for (slot-denotation text-or-text-string) = plist
		    for slot-description?
			= (get-slot-description-of-frame
			    (unqualified-name slot-denotation)
			    frame
			    (class-qualifier slot-denotation))
		    when slot-description?
		      do (parse-text-for-slot
			   (if (text-string-p text-or-text-string)
			       (convert-text-string-to-text text-or-text-string)
			       text-or-text-string)
			   frame
			   (get-slot-description-of-frame
			     (unqualified-name slot-denotation)
			     frame
			     (class-qualifier slot-denotation))
			   nil)
			 (setf (cadr plist) nil)))	; prevents double reclamation
	     (text
	      (change-slot-value
		frame 'box-translation-and-text
		(slot-value-cons
		  (car (box-translation-and-text frame))
		  original-value))
	      (setf (cadr plist) nil))		; prevents double reclamation
	     (g2-array-length
	      (change-slot-value frame 'g2-array-length original-value))
	     (text-box-font
	      (restore-original-value-for-text-box-font-kb-state-change
		frame original-value)))
	   (when (and g2-has-v5-mode-windows-p
		      (not (frame-of-class-p frame 'workspace))
		      (color-change-p kb-state-variable))
	     (send-ws-representations-item-color-pattern-change
	       frame
	       nil ;;specific-region
	       (get-color-pattern-of-item frame nil t)))
	finally
	  
	  (reclaim-slot-value (original-kb-state-plist frame))
	  (setf (original-kb-state-plist frame) nil)))


;;; The function `convert-text-and-parse-for-slot' gets the actual slot-name
;;; (from the alias if necessary), converts the text to unformatted text, and
;;; attempts to parse and place the parse value in the slot.  If the parse
;;; fails, the slot value is not changed and nil is returned.  This function
;;; does not verify that the slot can be editted and is in the frame.  The
;;; text-to-parse argument is not reclaimed and should be managed by the caller
;;; to this function.

;; Move this function to EDIT!!

#+unused
(defun convert-text-and-parse-for-slot
       (frame attribute-name text-to-parse &optional (note-as-kb-state-change? t)
	      defining-class?)		; reorder someday?!
  (let ((slot-description?
	  (get-slot-description-of-frame
	    (or (get-slot-name-for-alias-if-any attribute-name frame)
		attribute-name)
	    frame
	    defining-class?)))
    (when slot-description?
      (let ((unformatted-text-to-parse
	      (convert-text-string-to-text
		;; This arg is reclaimed.
		(copy-text-string text-to-parse)))
	    (do-not-note-permanent-changes-p note-as-kb-state-change?))
	(when note-as-kb-state-change?
	  (note-kb-state-change-to-slot-by-saving-text
	    frame slot-description?))
	(parse-text-for-slot
	  ;; This text arg is reclaimed.
	  unformatted-text-to-parse frame
	  slot-description?)))))





;;; `Remove-kb-state-variable-record' removes and recycles the record for
;;; kb-state- variable in frame's original-kb-state-plist slot.  If no further
;;; records remain in the plist, frame is removed from kb-state-changes.

(defun remove-kb-state-variable-record (frame kb-state-variable)
  (loop as l-trailer? = nil then (cdr l)
	as l = (original-kb-state-plist frame) then (cdr l-trailer?)
	while l
	when (eq (car l) kb-state-variable)
	  do (if l-trailer?
		 (setf (cdr l-trailer?) (cddr l))
		 (setf (original-kb-state-plist frame) (cddr l)))
	     (setf (cddr l) nil)
	     (reclaim-slot-value l)
	     (return))
  (when (null (original-kb-state-plist frame))
    (remove-as-frame-with-kb-state-changes frame)))

;; Currently used only in DEFINITIONS in one place at present.  (MHD 2/22/90)



;;; `Remove-kb-state-changes deletes and reclaims all record of KB state changes
;;; for the given frame.

;; jh, 8/14/91.  For make-permanent action (see STACK-ACTS).

;; cpm, 9/10/91.  Since reclaim-slot-value does not call the
;; slot-value-reclaimer, reclaim-original-kb-state-plist-value is called here
;; instead.  It would be nice if there was an abstracted way of calling the
;; slot-value reclaimer through reclaim-slot-value!!

(defun remove-kb-state-changes (frame)
  (reclaim-slot-value (original-kb-state-plist frame))
  (setf (original-kb-state-plist frame) nil))




;;;; Saving Screen Images



;; Save-screen-image ...

;(defun save-screen-image (pathname default-pathname-type)
;  (with-open-file (output-stream
;		   (merge-pathnames
;		     pathname
;		     (make-system-pathname
;		       'ab "SCREEN" default-pathname-type ':newest nil nil))
;		   :direction :output
;		   ; :element-type '(unsigned-byte 16)  ; ?? (see p. 419)
;                   )
;    output-stream))

;; Implement!

;; Consider recycling pathnames generated herein.

;; This should later take as args: file-format (POSTSCRIPT, PIC, etc.), left-edge-in-
;; window?, top-edge-in-window?, right-edge-in-window?, bottom-edge-in-window?,
;; swap-bytes?, etc!



;(defun compare-pic-files (pathname1 pathname2)
;  (with-open-file (input-stream1
;		    (merge-pathnames pathname1 "ma:>lh>*.pic")
;		    :element-type '(unsigned-byte 8))
;    (with-open-file (input-stream2
;		      (merge-pathnames pathname2 "ma:>lh>*.pic")
;		      :element-type '(unsigned-byte 8))
;      (loop with first-non-zero-byte? = nil
;	    with number-of-different-bytes = 0
;	    as i from 0
;	    as byte1? = (read-byte input-stream1 nil nil)
;	    as byte2? = (read-byte input-stream2 nil nil)
;	    while (or byte1? byte2?)
;	    when (not (eql byte1? byte2?))
;	      do (incff number-of-different-bytes)
;		 (if (null first-non-zero-byte?)
;		     (setq first-non-zero-byte? `(,i ,byte1? ,byte2?)))
;	    finally
;	      (return
;		(values
;		  i number-of-different-bytes first-non-zero-byte?))))))








;;;; Debugging



#+development
(defun look-for-ghost-tables ()
  (loop for frame being each class-instance of 'block
	when (loop for table in (frame-representations frame)
		   thereis (null (superblock? table)))
	  collect frame))









;;;; G2 Init Files




;;; `Do-g2-init-file' tests for a file named "g2.init" in the same directory as
;;; the ok.ok file (the "G2 home directory"), and if there is such a file loads
;;; it and executes each command line until the end of file (or until a Start G2
;;; command is encountered, whichever comes first).

;;; Note that this function at present conses and is run within a with-dynamic-
;;; creation context.

;; Modified get-or-use-default-init-pathname to use the new reclaimable
;; gensym-pathnames.  This function still conses, since it drops the command-line
;; text-strings and the gensym-pathname it ultimately returns.  Since the init
;; file is only loaded once, this is tolerable.  jh, 1/11/91.

;; jh, 8/15/91.  Modified get-or-use-default-init-pathname to look for both
;; command-line arguments and environment variables on any non-Lispm, since thanks
;; the new translation process, these are available on both UNIX and VMS
;; platforms.

;; jh, 12/17/91.  Added a way to defeat the -init option on the command line.  It
;; is felt that this represents a security breach, as does the loading of an OK
;; file specified on the command line.  Now G2 will look for a file called
;; NOCMD.INT in the top-level directory.  (The reason for this compressed name is
;; that some file systems support only a limited number of characters in a file
;; name).  If G2 finds this file, it will not obey the "-init" command-line
;; option.  The site administrator can then place a delete-proof NOCMD.INT file on
;; the top-level directory of every machine running a secure G2.

(def-suite-for-loading-file-at-launch-time init g2
  :base-name-of-file-to-load   "g2"
  :type-of-file-to-load        "init"
  :command-line-keyword        "init"
  :environment-variable-name   "G2_INIT"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "INIT") ;what about DOS ?!


(def-system-variable doing-g2-init-file-p KB-SAVE2 nil)

(def-system-variable doing-g2-init-kb-p KB-SAVE2 nil)

;; The system variable autostart-after-doing-init-file?  can have one of the
;; following values: do-not-autostart, autostart, never-autostart, or nil.

;; The only place never-autostart occurs is when a per-directory menu was offered
;; by the Init file and the user dismissed the menu.  This dismissal will
;; invalidate any subsequent start-after-load command in the Init file.  
;; jh, 8/14/91.

(def-system-variable autostart-after-doing-init-file? KB-SAVE2 nil) 

;; The system variable autostart-reason-in-init-file?  can have one of the
;; following values: load-grammar, merge-grammar, or nil.
(def-system-variable autostart-reason-in-init-file? KB-SAVE2 nil) 


(defvar command-line?)

(defun-allowing-unwind do-g2-init-file ()
  (force-process-drawing)
  (let ((init-file-pathname?	 
	 ;; jh, 1/24/92.  Changed the following from a call to
	 ;; get-or-use-default-init-pathname.  We now look for the init file in a
	 ;; more security-conscious way.  See details in PATHNAMES above the
	 ;; definition of def-suite-for-loading-file-at-launch-time.
	 (get-or-use-g2-init-pathname)))
    (when init-file-pathname?
      (protected-let
	  ((init-file-truename
	     (gensym-namestring init-file-pathname?)
	     (reclaim-text-string init-file-truename)))
	(g2-stream-with-open-stream 
            (init-file-stream? init-file-truename 
			       :direction :input)
	  (let ((doing-g2-init-file-p t) ;special binding
		(start-on-load-p
		  (or (get-command-line-flag-argument #w"start")
		      (get-gensym-environment-variable #w"G2_START")))
		(start-happened-p nil)
		(error-happened-p nil))
	    (setq autostart-after-doing-init-file? nil) ;set in execute-file-command
	    (when init-file-stream?
	      (loop with init-file-command? = nil
		    with frame-serial-number-of-init-file-command?
		    for command-line? 
			= (g2-stream-read-line init-file-stream?)
			then (g2-stream-read-line init-file-stream?)
		    while command-line?
		    do (setq command-line?
			     (prog1
				 (import-text-string
				   command-line?
				   'INIT-FILE-COMMAND-LINE)
			       (reclaim-text-string command-line?)))
		       (setq command-line? ; strip off lead/trail space just so
			     (prog1	   ;   it looks better in logbook
				 (text-string-trim
				   '(#.%space #.%tab) ; added tab
				   command-line?)
			       (reclaim-text-string command-line?)))
		    if (or (=f (text-string-length command-line?) 0) ; empty
			   ;; Added support for Lisp-style comments in init file. -binghe, 4 Sep 2016.
			   (char=w (charw command-line? 0) #.%\;))
		      do (reclaim-text-string command-line?)
		    else		; command-line? gets incorporated
					;   into the text
		      do 
			;; All subsequent forms up to the "finally" depend on the
			;; preceding "else" clause.
			(unless init-file-command?
			  (setq init-file-command?
				(make-command-frame 'init-file-command))
			  (setq frame-serial-number-of-init-file-command?
				(copy-frame-serial-number (frame-serial-number init-file-command?))))
			(notify-user
			  "Executing the command line: ~a" command-line?)
			(if (string-equalw command-line? #w"shut down g2")
			    (completely-shut-down-g2 'requested)
			    (multiple-value-bind (successp reason-for-failure?)
				(parse-text-for-slot
				  (convert-text-string-to-text	; incorporates the string into the text
				    (copy-text-string command-line?))
				  init-file-command?
				  (get-slot-description-of-frame
				    'box-translation-and-text
				    init-file-command?
				    nil)
				  nil nil nil nil t)
			      (cond (successp
				     (reclaim-text-string command-line?)
				     (let ((command-translation
					     (car (box-translation-and-text 
						    init-file-command?))))
				       (case command-translation
					 (start-g2
					  (cond
					    ((or system-is-running system-has-paused)
					     (notify-user
					       "Cannot execute `Start G2' in the G2 Init file (\"~a\") ~
                                    because G2 has already been started."
					       init-file-truename))
					    (t
					     (setq start-happened-p t)
					     (system-start)
					     (loop-finish))))
					 (otherwise
					  (funcall-method-if-any
					    'execute-command init-file-command?)
					  (unless (and frame-serial-number-of-init-file-command?
						       (frame-serial-number-equal frame-serial-number-of-init-file-command?
										  (frame-serial-number init-file-command?)))
					    (setq init-file-command?
						  (make-command-frame 
						    'init-file-command))
					    (setq frame-serial-number-of-init-file-command?
						  (copy-frame-serial-number (frame-serial-number init-file-command?))))))))
				    (t
				     (notify-user
				       "Error in G2 Init file (\"~a\") while executing the ~
                            command line: ~a~
                            ~%~a~%Aborting execution of the G2 Init file."
				       init-file-truename
				       command-line?
				       reason-for-failure?)
				     (reclaim-text-string command-line?)
			   (setq error-happened-p t)
			   (loop-finish)))))
		    finally
		      (unless (or start-happened-p error-happened-p)
			(case autostart-after-doing-init-file?
			  (autostart
			   (notify-user-of-autostart-and-reason 
			     autostart-reason-in-init-file?) ;set in execute-file-command
			   (system-start))
			  (do-not-autostart nil)
			  (otherwise
			   ;; However the start-after-load flag ends up after the
			   ;; arbitrary sequence of merges and loads, that's what we
			   ;; do here.
			   (when (start-kb-after-load-from-system-table?)
			     (notify-user-of-autostart-and-reason 'system-table)
			     (system-start))))
			;; still support the -start command option.
			(when start-on-load-p
			  (system-start)))
		    ;; Nothing is allowed after a start-g2 command.
		      (when start-happened-p
			(unless
			    (let ((next-line?
				    (g2-stream-read-line init-file-stream?)))
			      (or (null next-line?)
				  (loop for residue? = next-line?
						     then
					(progn (reclaim-text-string residue?)
					       (g2-stream-read-line init-file-stream?))
					while residue?
					always
					(loop for i from 0 below (text-string-length residue?)
					      always
					      (wide-character-member
						(charw residue? i)
						'(#.%Space #.%Tab))))))
			  (notify-user
			    "Ignoring commands following the \"Start G2\" command ~
                           in the G2 Init file.")))
		      (when (and init-file-command?
				 (frame-serial-number-equal frame-serial-number-of-init-file-command?
							    (frame-serial-number init-file-command?)))
			(delete-frame init-file-command?)))))))
      t))) ;return t if found an init file pathname

;; Modified do-g2-init-file to use the new gensym-pathanmes.  jh, 1/11/91.

;; jh, 8/12/91.  Modified do-g2-init-file to start on load if the init file so
;; specifies.  The last explicit "start" or "do not start" command is obeyed.
;; While I was at it, I made it complain if there are commands after a "Start G2"
;; in the Init file.




;;;; Loading KBs from the Command Line

;;; The following implements the ability to load and start a KB specified in the
;;; command line rather than a G2 init file.  The load will only take place if
;;; an acceptable init file does not exist.  The command line keyword -kb will
;;; specify a KB for G2 to load after launch, and the flag -start will start the
;;; KB after the load.  There is a command-line disabling process similar to
;;; these other facilities.  If a file named NOCMD.KB is present in the root
;;; directory, G2 will only load the KB if it is listed on a separate line in
;;; that file.  Unlike the -init and -ok facilities, there is no default file to
;;; load if nothing is specified in the command line.

(def-suite-for-loading-file-at-launch-time kb g2
  :base-name-of-file-to-load   nil
  :type-of-file-to-load        "kb"
  :command-line-keyword        "kb"
  :environment-variable-name   "G2_KB"
  :base-name-of-disabling-file "NOCMD"
  :type-of-disabling-file      "KB")

(defun-allowing-unwind do-g2-kb-load-at-launch ()
  (force-process-drawing)
  (let ((init-file-pathname?
	 (get-or-use-g2-init-pathname)))
    ;; Now the KB is loading no matter if there's an init file.
    (unless nil ;; init-file-pathname?
      ;; Read-kb-or-group-thereof stores its pathname arg in
      ;; current-kb-pathname?  as the next default for KB saves and loads, so we
      ;; don't reclaim it here.  In other words, protected-let is out.
      (multiple-value-bind 
	  (kb-file-pathname?
	   namestring-explicitly-specified-from-os-environment?
	   source-of-namestring-specification)
	  (get-or-use-g2-kb-pathname t) ;provide-desired-namestring-p
	(prog1 (if kb-file-pathname?
		   (let ((doing-g2-init-kb-p t) ;special binding
			 (start-on-load-p
			   (or (get-command-line-flag-argument
				 #w"start")
			       (get-gensym-environment-variable
				 #w"G2_START"))))
		     (read-kb-or-group-thereof
		       kb-file-pathname?
		       t ; clear-kb? 
		       t ; install-system-tables?
		       nil ; bring-formats-up-to-date?
		       ;; Added a new -manually-resolving-conflicts
		       ;; command-line argument as per Suggestion
		       ;; HQ-4466212. - jpg 3/18/03
		       (unless (get-command-line-flag-argument
				 #w"-manually-resolving-conflicts")
			 'default) ; resolve-conflicts-automatically?
		       (if (and start-on-load-p
				;; If there's also init file, do not start KB here!
				(not init-file-pathname?))
			   'load-from-command-line
			   nil) ; what-to-do-after-loading-kb?
		       nil ; update-before-loading?
		       nil)) ; client?
		   (when namestring-explicitly-specified-from-os-environment?
		     (let ((readable-namestring
			    (import-text-string
			     namestring-explicitly-specified-from-os-environment?
			     'COMMAND-LINE-ARGUMENT)))
		       (case source-of-namestring-specification
			 (:environment-variable
			  (notify-user
			   "G2 could not find the file \"~a\", ~
                            which was specified as an environment variable ~
                            when G2 was launched."
			   readable-namestring))
			 (:command-line
			  (notify-user
			   "G2 could not find the file \"~a\", ~
                            which was specified in the command line that launched G2."
			   readable-namestring)))
		       (reclaim-text-string readable-namestring)
		       nil)))
	  (when namestring-explicitly-specified-from-os-environment?
	    (reclaim-text-string 
	     namestring-explicitly-specified-from-os-environment?)))))

	  ;; After loading KB (or not), continue to handle the init file.
	  (when init-file-pathname?
	    (do-g2-init-file))))

;; jh, 8/28/92.  Modified do-g2-kb-load-at-launch to notify the user if it was
;; unable to follow an explicit commmand-line directive to load a KB.  This
;; involves getting an extra value from get-or-use-g2-kb-pathname which
;; specifies the desired namestring.  It is the responsibility of
;; do-g2-kb-load-at-launch to reclaim this string.  Note that the message
;; waffles about getting the KB name from an environment variable in the
;; operating system.  There are differing opinions about whether we should
;; advertise os environment variables to users.




;;;; G2 OK Files



;;; `Message-regarding-authorized-OK-file?', a system variable, normally is nil,
;;; its global per-process default value; however it may be set to a text string
;;; for the purpose transmitting a warning about a user's OK file after it's
;;; been cleared.  The text string does not get reclaimed until and unless a new
;;; one is needed, but should rarely be used, so this should not matter.
;;;
;;; This string gets passed in through the post-prominent-notification
;;; interface, and displayed via that interface.
;;;
;;; The interface to setting this variable is the function,
;;; `make-message-regarding-ok-file'.  It's argument should be a fresh
;;; text string.

#+development
(def-system-variable message-regarding-authorized-OK-file? kb-save2
  nil)

#+development
(defun reset-authorizations ()
  (deauthorize)
  (setq message-regarding-authorized-OK-file? nil)
  (setq chaining-refresh-version 5)
  (setq keytab1 (choose-keytab))
  (setq chaining-refresh-list (choose-chaining-refresh-list))
  nil)




;;;; Checking for OK KBs



;;; The function `ok-kb-p' is true if the KB might just be an `OK KB', (an
;;; "ok.kb" file).  This means that it can be saved out even if this is a
;;; runtime-only or embedded G2.  (You have to be able to save an OK file even
;;; in these systems.)  Currently, to be ok-kb-p, it must be the case that none
;;; of the following classes has instances in the current KB:
;;;
;;;    definition
;;;    rule
;;;    procedure
;;;    variable
;;;    parameter

#+pre-g2-v5-licensing
(defun ok-kb-p ()
  (loop for class in '(definition rule procedure variable parameter)
	never (instantiated-class-p class)))

;; I suppose a good question is: why doesn't it also check for the presence
;; of OK objects?  I don't know myself.  I do believe this should not be
;; documented to the user other than as: you can save an OK file, but you
;; can't save anything else, in a runtime version.  Check!  (MHD 11/30/93)





;;;; Problem KB Detection


;;; Kb-is-savable-p is a test to see if there are conditions in the KB that
;;; make it impossible to save, or that make it savable only if certain
;;; transient items are deleted. 

;;; There are three values: (1) true if the KB is savable at all (even
;;; with deletions) and false otherwise. (2) a text string if there are
;;; problems, else NIL. (3) A list of items to delete if the KB is savable
;;; but requires deletions first, else NIL.

;;; Restating the above by cases:

;;; Case I:   No problems. Values: t, nil, nil
;;; Case II:  KB can be saved, but it will delete some transient items first.
;;;                Values: t, text string, list-of-transient-items-to-delete
;;; Case III: KB cannot be saved in its present state: Values nil, text string, nil

;;; The reason for these values is that kb-is-savable-p is called near the
;;; entry to kb saving, but after the last menu choice giving final permission.
;;; If there are no problems, saving occurs without interrupts immediately
;;; after kb-is-savable-p. If the KB is not savable, a message is displayed, and
;;; the saving does not occcur. If the KB is savable after deletions, the message
;;; is displayed. If the user then chooses to save, kb-is-savable-p is performed again.
;;; If the list of deletions has changed, then the user is told that conditions
;;; have changed, and saving does not occur. If all is ok, then saving occurs
;;; without interrupts.



;;; Causes of entanglement:

;;; (1) A definition has been placed in a portion of the KB which is not
;;; to be saved, such as a subworkspace of a transient item. The KB is
;;; not savable

;;; (2) A representation of a definition or system table is savable, and
;;; it has connections. The KB is not savable.

;;; (3) A representation of a non-savable item in limbo is savable. A G2 window
;;; that is automatically created to correspond to a G2 or Telewindows workstation
;;; is an example of such an item.

;;; (4) A transient item is connected to a savable item. The transient item
;;; will be deleted before saving.

;;; (5) A representation of a transient item is savable. The transient item
;;; will be deleted before saving.


(defvar transients-to-delete)

(defvar represented-frames-in-limbo)






(defun kb-is-savable-p ()
  (let (;(badly-placed-definitions nil)
	(represented-frames-in-limbo nil)
	(entangled-representations nil)
	(transients-to-delete nil))

    ;; Until this is done, savability tests do not have correct values.
    (identify-all-savable-kb-workspaces)

;    (loop for definition being each class-instance of 'definition
;	  for superblock? = (superblock? definition)
;	  doing

;      ;; Each definition must be in limbo or must be a subblock of a
;      ;; savable kb-workspace.
;      (when (and superblock?
;		 (transient-p definition))
;	(setq badly-placed-definitions
;	      (gensym-cons definition badly-placed-definitions))))

    (loop for kb-workspace being each class-instance of 'kb-workspace
	  doing
      (when (savable-kb-workspace-p kb-workspace)

	(loop for block being each subblock of kb-workspace
	      doing
	  ;; For each table which is a descendant of a savable kb-workspace via
	  ;; subblocks (iterated), it must not represent anything non-savable.
	  (when (and (frame-of-class-p block 'table) (permanent-block-p block))
	    (setq entangled-representations
		  (nconc (check-table-for-entanglement block) entangled-representations)))	  
	  )))

    (cond
;      ((or badly-placed-definitions represented-frames-in-limbo)
      (represented-frames-in-limbo
       (values nil				; not savable
	       (prog1 (write-problems-saving-kb
;			badly-placed-definitions
			represented-frames-in-limbo
			entangled-representations
			transients-to-delete)
		      (reclaim-gensym-list transients-to-delete)
		      (setq transients-to-delete nil))
	       nil))

      (entangled-representations
       (values t				; problems solved by deleting	       
	       (write-problems-saving-kb
;		 badly-placed-definitions
		 represented-frames-in-limbo
		 entangled-representations
		 transients-to-delete)
	       transients-to-delete))

      (t (values t nil nil)))

    ))

;;; Constraints: A transient connection always has a frame. A loose end is
;;; transient if and only if the other end of its connection is transient.



;;; Check-table-for-entanglement is called only with its argument being
;;; a table which is not transient and is a subblock of a savable workspace
;;; from kb-is-savable-p, and from within itself for non-transient tables
;;; which are subblocks of the argument recursively. It checks tables to
;;; see if they represent non-savable frames. The value is a gensym-list
;;; of all such tables found within the recursive dynamic extent of the
;;; execution. Concurrently, it examines the non-savable frames represented.
;;; For each one it either finds a transient item which is that frame or an
;;; ancestor of that frame, and adds it to transients-to-delete, or if none is
;;; found, it adds the highest level thing it can find to
;;; represented-frames-in-limbo. G2 windows are the only known cases
;;; of this presently.

(defun check-table-for-entanglement (table)
  (let ((problem? nil))

    (do-frames-this-represents (represented-frame table)
      (unless (not (transient-or-unsavable-p represented-frame))
	(loop for root? = represented-frame then (parent root?)
	      until (or (null root?) (transient-p root?))
	      finally
		(if root? 
		    (gensym-pushnew root? transients-to-delete)
		    (gensym-pushnew represented-frame represented-frames-in-limbo)))
	(setq problem? t)))

    (nconc
      (if problem? (gensym-list table) nil)
      (loop for subblock being each subblock of table
	    when (and (frame-of-class-p subblock 'table)
		      (not (transient-or-unsavable-p subblock)))
	      nconc (check-table-for-entanglement subblock)))))



;;; parent is similar to a superior-frame defined in
;;; ACTIVATE, except that it assumes its argument to be a block,
;;; and the parent of a connection is the input end object
;;; rather than the superblock thereof.

(defun parent (block)
  (or    
    (superblock? block)
    (parent-frame block)
    (if (frame-of-class-p block 'workspace)
	(parent-of-subworkspace? block))
    (if (frame-of-class-p block 'connection)
	(input-end-object
	  (connection-for-this-connection-frame block)))
    (if (frame-of-class-p block 'simulation-subtable)
	(parent-variable-function block))
    ))
  
  
  
(defun write-list-of-forced-names (list-of-frames)
  (let ((list-of-names
	  (loop for block in list-of-frames
		collect
		  (get-or-make-up-designation-for-block block) using gensym-cons)))
    (write-list-in-chicago-style list-of-names "and")
    (reclaim-gensym-list list-of-names)))


  

(defun write-problems-saving-kb
       (;badly-placed-definitions
	represented-frames-in-limbo
	entangled-representations
	transients-to-delete)
  (prog1
    (twith-output-to-text-string
      
      (when (or ;badly-placed-definitions
		represented-frames-in-limbo
		entangled-representations)
	(tformat
	  "~A, ~A ~A ~A"
	  "This KB cannot be saved because of certain problems.  Generally"
	  "such problems tend to go away if you reset G2 and/or delete"
	  "certain transient items.  Note that"
	  "resetting G2 deletes all transient items."))
      
      
;      (when badly-placed-definitions
;	(tformat
;	  "~%~%The definition~a "
;	  (if (cdr badly-placed-definitions) "s" ""))
;	(write-list-of-forced-names badly-placed-definitions)
;	(tformat
;	  " ~a ~A.  ~a ~A .  ~A"

;	  (if (cdr badly-placed-definitions) "are" "is")
;	  "upon one or more transient subworkspaces"
;	  (if (cdr badly-placed-definitions) "They" "It")
;	  "must be moved to a permanent kb-workspace before the KB can be saved"
;	  "Note that if you reset G2, these definitions will be deleted."))
      
      (when represented-frames-in-limbo
	(tformat
	  "~%~%The item~a "
	  (if (cdr represented-frames-in-limbo) "s" ""))
	(write-list-of-forced-names represented-frames-in-limbo)
	(tformat
	  " cannot be saved, but ~a ~a represented by one or more tables that ~
           must be saved.  Deleting such tables or deleting the above item~a ~
           may make this KB savable."
	  (if (cdr represented-frames-in-limbo) "they" "it")
	  (if (cdr represented-frames-in-limbo) "are" "is")
	  (if (cdr represented-frames-in-limbo) "s" "")))

      
      ;; Don't include the following for now because it forces names onto table,
      ;; but there is no way to make use of these names (i.e. in Inspect)!
;      (when entangled-representations
;	(tformat
;	  "~%~%The table~a "
;	  (if (cdr entangled-representations) "s" ""))
;	(write-list-of-forced-names entangled-representations)
;	(tformat
;	  " must be saved, but ~a represent~a one or more items that cannot be saved.  ~
;           Deleting such items or deleting the above table~a may make this KB ~
;           savable."
;	  (if (cdr entangled-representations) "they" "it")
;	  (if (cdr entangled-representations) "" "s")
;	  (if (cdr entangled-representations) "s" "")))
      
      (when transients-to-delete
	(tformat
	  "~%~%Deleting the following transient item~a ~a make this KB savable: "
	  (if (cdr transients-to-delete) "s" "")
	  (if (not represented-frames-in-limbo)
	      ;(or badly-placed-definitions represented-frames-in-limbo))
	      ;; Note: the condition tested is exactly the same condition that
	      ;;   determines the value of the repairable-p value (the first value)
	      ;;   of kb-is-savable-p.
	      "will"
	      "may"))
	(write-list-of-forced-names transients-to-delete)))
    
;    (reclaim-gensym-list badly-placed-definitions)
    (reclaim-gensym-list represented-frames-in-limbo)
    (reclaim-gensym-list entangled-representations)
    
    ))




;;; identify-all-savable-kb-workspaces iterates over all
;;; kb-workspaces either setting or clearing the frame flag
;;; savable-kb-workspace. This frame flag shares a bit with flags
;;; belonging to variables and/or rules, and may be inadvertently
;;; saved in a kb. The status of the flag before saving is of no importance
;;; because identify-all-savable-kb-workspaces is performed befoe the
;;; the flag is tested which occurs only within the dynamic extent of
;;; menu choosing and executing a save.


(defun identify-all-savable-kb-workspaces ()
  (loop for kb-workspace being each class-instance of 'kb-workspace do
    (clear-savable-kb-workspace kb-workspace))

  (loop for kb-workspace being each class-instance of 'kb-workspace do
    (if (not (savable-kb-workspace-p kb-workspace))
	(mark-kb-workspace-if-savable kb-workspace))))


;;; mark-kb-workspace-if-savable sets savable-kb-workspace and returns true
;;; if the workspace is savable. Else it returns NIL. It is safely assumed
;;; that a kb-workspace marked as savable is so, but one not marked may
;;; or may not be savable.

;;; Performance note: To avoid having to touch many savable frames, this
;;; function iterates over kb-workspaces. It touches only those frames in the
;;; line of descent of kb-workspaces. It may touch some of these many times,
;;; but if most kb-workspaces are savable, this does not happen very much
;;; because the algorithm marks as savable as it ascends the ancestry tree.

;;; Should not be called on a kb-workspace for which savable-kb-workspace-p is t.

;;; An orphan kb-workspace is not savable.

(defun mark-kb-workspace-if-savable (kb-workspace)
  (let ((parent? (parent-of-subworkspace? kb-workspace)))
    (cond
      ((null parent?)
       ;; top level kb-workspace
       (cond ((or (orphan-workspace-p kb-workspace)
		  (transient-p kb-workspace))
	      nil)
	     (t
	      (set-savable-kb-workspace kb-workspace)
	      t)))
      ((transient-or-unsavable-p parent?)
       ;; subworkspace of transient item
       nil)	
      (t (let ((parent-of-parent? (superblock? parent?)))
	   (if parent-of-parent?
	       (cond
		 ((not (frame-of-class-p parent-of-parent? 'kb-workspace))
		  ;; subworkspace of block which is on a temporary workspace
		  nil)
		 ((savable-kb-workspace-p parent-of-parent?)
		  ;; savable by descent
		  (set-savable-kb-workspace kb-workspace)
		  t)
		 ((mark-kb-workspace-if-savable parent-of-parent?)
		  ;; savable by descent just discovered
		  (set-savable-kb-workspace kb-workspace)
		  t)
		 (t nil))
	       ;; subworkspace of block in limbo
	       nil))))))


;;; Constraints: If a kb-workspace has a parent, it is via parent-of-subworkspace?.
;;; If that exists and has a parent, the parent is via superblock? and is a workspace.
;;; I.e., there is a single line of descent to subworkspaces which alternates between
;;; items which are subblocks of workspaces and subworkspaces of items.





;;; Constraints: Definitions never have connections. They are never
;;; attributes. They cannot be placed on non kb-workspaces.



;;; A non-transient block is savable if (1) it is a savable kb-workspace, 
;;; or (2) has an ancestor that is a savable kb-workspace and has no 
;;; transient ancestors, or (3) is a system-frame or definition without ancestors.

;;; This is a derrivative definition and assume that we already kbow what kb-workspaces
;;; are savable.

;; Savable-block-p will bomb out if given a non-block, which as of the moment must
;; be a plot. 1/20/91 ML 

;; I removed the compiler switch which made this a development only function to
;; stop a bug in the Chestnut compiles.  -jra 7/31/91

(defun savable-block-p (block)
  (loop with parent
	with saved-block
	initially
	  (if (transient-or-unsavable-p block)
	      ;; transient items are not savable
	      (return nil)
	      
	      (class-case (class block)
		
		(simulation-subtable
		  (setq parent (parent-variable-function block)))
		
		(workspace
		  (if (frame-of-class-p block 'kb-workspace)
		      (return (savable-kb-workspace-p block)))
		  ;; Non-kb workspaces are not savable
		  (return nil))
		
		(connection
		  (setq parent (input-end-object
				 (connection-for-this-connection-frame
				   block))))
		(computation-style
		  (return (savable-computation-style-p block)))
		
		(t (setq parent
			 (or (superblock? block)   ; if subblock
			     (parent-frame block)))	       ; if attribute or
					; embedded 
		   (cond
		     ((null parent)
		      ;; item in limbo
		      (return (or (frame-of-class-p block 'class-definition)
				  (frame-of-class-p block 'system-frame))))
		     
		     ((frame-of-class-p parent 'workspace)
		      (if (frame-of-class-p parent 'kb-workspace)
			  (return (savable-kb-workspace-p parent))
			  ;; Non-kb workspaces are not savable
			  (return nil)))))))
	
	do
    
    ;; parent, at this point may not be null, and may not be a workspace
    ;; given the way this is coded.
    (cond
      ((transient-or-unsavable-p parent) (return nil))
      
      ((frame-of-class-p parent 'connection)
       (setq parent (input-end-object
		      (connection-for-this-connection-frame parent))))
      
      (t (setq saved-block parent)
	 (setq parent
	       (or (superblock? parent)
		   (parent-frame parent)))
	 (cond
	   ((null parent)
	    (return
	      (or (frame-of-class-p saved-block 'class-definition)
		  (frame-of-class-p saved-block 'system-frame))))
	   
	   ((frame-of-class-p parent 'workspace)
	    (if (frame-of-class-p parent 'kb-workspace)
		(return (savable-kb-workspace-p parent))
		;; Non-kb workspaces are not savable
		(return nil))))))))


;;; Constraints: Simulation-frames and embedded rules are not ancestors.

;;; Constraint:
;;; (input-end-object (connection-for-this-connection-frame connection-frame))
;;; is always a frame.





;;;; Rejecting a KB Save



;;; This section most recently was under the function save-kb in KB-SAVE3.  In
;;; version 3.0 most of the contents of the functions in this section were
;;; inlined into save-kb.  All of the following function return true if the save
;;; is to be rejected.  They may do their own posting of messages and other
;;; forms of information.



;;; `Reject-save-kb-if-saving-modules-without-consistency' ... only to be called
;;; if saving modules.

(defun reject-save-kb-if-saving-modules-without-consistency ()  
  (when (or
	  #+obsolete
	  (when system-is-running	; usually doesn't get here - module save 
	    (notify-user		;   not offered by default when running
	      "G2 is running; you ~
                   therefore cannot save ~
                   individual modules unless you pause or reset.  ~
                   NO PART OF THIS KB HAS BEEN SAVED!")
	    t)
	  (and (not inhibit-modularity-consistency-checking?)
	       (when (check-savability-of-kb-in-terms-of-modularity nil t)
		 (notify-user
		   "The modules in this KB are not consistent; you ~
                        therefore cannot save individual modules.  ~
                        NO PART OF THIS KB HAS BEEN SAVED!")
		 t)))
    (setq kb-save-termination-reason?
	  'kb-not-consistently-modularized)
    t))

(defun reject-save-kb-if-not-savable ()
  (multiple-value-bind (repairable-p message-text-string? transients-to-delete)
      (kb-is-savable-p)
    (declare (ignore repairable-p))		; for now
    (when message-text-string?
      (notify-user "~a" message-text-string?)
      (reclaim-text-string message-text-string?)
      (reclaim-gensym-list transients-to-delete)
      (setq transients-to-delete nil)
      ;; What about reclaiming some strings?!
      (setq kb-save-termination-reason? 'kb-not-savable)      
      t)))


(defun reject-save-kb-if-not-authorized ()
  (when (not (g2-authorized-p))
    ;; OK to reject saving silently; the menu choice is not offered unless g2 is
    ;; authorized.
    (setq kb-save-termination-reason? 'g2-not-authorized)
    t))

;(defun reject-save-kb-if-for-impossible-backup ()
;  (when (and (eq type-of-kb-save 'backup)
;	     (not all-permanently-changed-things-are-marked))
;    (notify-user
;      "Writing a backup is not possible at this time.")
;    t))

(defun reject-save-kb-if-save-or-backup-in-progress ()
  (when current-saving-context?
    (notify-user "Save is already in progress.")
    (setq kb-save-termination-reason? 'in-progress)
    t))


(defun reject-save-kb-if-run-time-only (type-of-kb-save)
  #+pre-g2-v5-licensing
  (when (and (or (runtime-option-authorized-p)
		 (embedded-option-authorized-p)) ;Added (12/20/91)
	     (neq type-of-kb-save 'kb-save-with-runtime-data)
	     (not (ok-kb-p)))
    ;; (really menu choice disabling should prevent being here)
    (notify-user 
      ;; exact same message in FACILITIES
      "Saving KBs is prohibited in run-time-only systems.")
    (setq kb-save-termination-reason? 'prohibited-with-this-license)
    t)
  #-pre-g2-v5-licensing
  (declare (ignore type-of-kb-save))
  #-pre-g2-v5-licensing
  nil)

(defmacro reject-save-kb-if-system-clock-set-back ()
  `(cond
     ((system-clock-set-back-p)
      (setf (setback-time-preventing-kb-save?)
	    (accumulated-clock-setback-time))
      (cond
	((license-has-expiration-date-p g2)
	 (notify-user
	   (refuse-save-after-system-clock-tampering-message))
	 (setq kb-save-termination-reason? 'prohibited-with-this-license)
	 t)
	(t nil)))
     (t nil)))

(defun reject-save-kb-if-filename-problems
    (pathname-or-module-saving-schedule)
  (let ((filename-string?
	  (any-wild-pathnames-p pathname-or-module-saving-schedule)))
    (when filename-string?
      (notify-user
	"WARNING: Saving did not complete. ~A" 
	(get-error-string-for-illegal-wildcards-in-filename filename-string?))
      (reclaim-text-string filename-string?)
      (setq kb-save-termination-reason? 'wildcards-in-filename)      
      t)))


(defun any-wild-pathnames-p (pathname-or-module-saving-schedule)
  (cond ((consp pathname-or-module-saving-schedule)
	 (or (any-wild-pathnames-p
	       (car pathname-or-module-saving-schedule))
	     (any-wild-pathnames-p
	       (rest pathname-or-module-saving-schedule))))
	((gensym-pathname-p pathname-or-module-saving-schedule)
	 (and (gensym-wild-pathname-p pathname-or-module-saving-schedule)
	      (funcall (gensym-pathname-namestring-generator 
			pathname-or-module-saving-schedule)
		       pathname-or-module-saving-schedule)))
	(t
	 nil)))



;; Was called at the beginning of save-kb, before check for modularity
;; consistency.  Removed for 4.0 -- hopefully we don't need to solve this
;; problem, if it still exists, in this way! (MHD 1/10/94)
;; 
;; ;; If this function is not removed for 4.0 change it for multiple-inheritance.
;; ;; (7/20/93 ghw)
;; 
;; ;;; Repair-definitions-with-none-in-superior-class-bug-if-necessary looks for
;; ;;; definition instances that have nil in their superior-of-
;; ;;; defined-class attribute where they should actually have a class.  This is to
;; ;;; be called just before saving.  This corruption violates software
;; ;;; constraints, and will make the KB being saved unloadable.  If such a
;; ;;; corruption is found, this function repairs the definitions, and, at the end,
;; ;;; advises the user to call Gensym Customer Support and to shut down G2 after
;; ;;; saving.

;; ;;; This has been done because one KB, the Gensym Bug Database, was found to
;; ;;; have developed this problem.  It appeared to happen after the KB was loaded
;; ;;; in and also spread to other class definitions after having been
;; ;;; observed in only a few.  Much effort was expended attempting to recreate
;; ;;; the problem, to no avail.

;; ;;; It is hoped that this function may never find a problem because the problem
;; ;;; may actually no longer be there.  We're not sure.  If no one observes this
;; ;;; problem before 4.0, this function should probably be removed.
;; 
;; (defun repair-definitions-with-none-in-superior-class-bug-if-necessary ()
;;   (loop for definition being each class-instance of 'definition
;; 	for class? = (name-of-defined-class definition)
;; 	for class-description?
;; 	    = (if class? (class-description class?))
;; 	as superior-class?
;; 	   = (if class-description?
;; 		 (second (class-inheritance-path class-description?)))
;; 	when (and superior-class?
;; 		  (null (direct-superiors-of-defined-class definition)))
;; 	  do (let ((noting-changes-to-kb-p nil))       ; special
;; 	       (setf (direct-superiors-of-defined-class definition)
;;                   (phrase-list superior-class?)))
;; 	  and collect (gensym-cons class? superior-class?)
;; 		into problems using gensym-cons
;; 	finally
;; 	  (when problems
;; 	    (let ((message-string
;; 		    (twith-output-to-text-string
;; 		      (tformat
;; 			"Warning!  NONE was found in the superior-class attribute ~
;;                          of ~a class~a.  The problem has been repaired in order to ~
;;                          make the KB you are saving safe, but please shut down G2 ~
;;                          after saving, and report this to Gensym Customer Support.~%~
;;                          The class~a involved ~a: "
;; 			(if (cdr problems) "several" "a")
;; 			(if (cdr problems) "es" "")
;; 			(if (cdr problems) "es" "")
;; 			(if (cdr problems) "are" "is"))
;; 		      (loop for ((class . superior) . more?)
;; 				on problems
;; 			    do (tformat "~a (superior class: ~a)" class superior)
;; 			       (when more? (tformat ";~%"))))))
;; 	      (post-prominent-notification message-string)
;; 	      (reclaim-gensym-tree problems)))))
;; 
;; ;; By ML and MHD.  (MHD 3/2/92)





;;;; Saving Knowledge Bases

;;; Michael Levin

;; This was written in the fall of 1990. Since then, the saving method has been
;; extensively revised. The relations called child and parent below have been
;; codified in traversals as inferior and superior. Dependent frames have also
;; been introduced since this was written. 

;; An important and still current piece of information is the list of all
;; savable slots that have pointers. This is still limited to the inferior and
;; superior set of slots, frame-representations, and stack-of-subblocks,
;; frame-representations, and its inverses such as table-rows.


;;; 1. Overview

;;; The saving of knowledge bases is a fragile part of G2 which has 
;;; resulted in many bugs, some of which cause customers to loose their 
;;; work. Until now, there has been no documentation on what 
;;; constraints are necessary to have the saving and reading of KBs 
;;; function properly. The purpose of this paper is to explain how it 
;;; works and what can cause it to fail. This is done by defining certain 
;;; terms precisely, stating some requirements that the saving 
;;; algorithm must satisfy, and then showing that these requirements 
;;; are satisfied if certain constraints are observed. 

;;; The paper discusses changes that were made in the software to 
;;; satisfy the constraints and to improve the saving algorithm, as well 
;;; as certain bugs that have occurred and serve as examples of 
;;; constraint violation.

;;; Finally, possible changes to the format of saved KBs are discussed, 
;;; because they would allow the relaxation of certain saving 
;;; requirements. The present system is fragile even when well 
;;; documented because it cannot be made robust as a self contained 
;;; module. It depends on constraints which can only be enforced at the 
;;; user interface level as the software is currently organized. (The 
;;; present round of repairs has made no change to the format of saved 
;;; KBs.)

;;; In this paper, the term frame is used for kb-frame. All frames in G2 
;;; are in fact kb-frames, and all frames except plots (!) are blocks.

;;; 2. Definitions


;;; Several important definitions are introduced in this section. Child 
;;; and parent are defined as inverse relations on frames, and 
;;; descendent and ancestor are then defined as their respective 
;;; transitive closures. Child is multi-valued, and parent is single-
;;; valued, thus organizing the frames as a forest.

;;; Savable is then defined in a manner which depends on the preceding 
;;; definitions. The definition of savable is used to determine which 
;;; frames should and should not be saved in a KB. This definition is 
;;; completely independent of the saving algorithm which does not 
;;; traverse the forest mentioned above. Thus the correctness of the 
;;; saving algorithm becomes something to be proved.

;;; Reachable is then defined as a directed graph over frames for the 
;;; purpose of explaining what the saving algorithm does. 

;;; The concept of clipping is then defined as a method of removing 
;;; certain edges from the reachability graph. 

;;;  At this point, the saving algorithm itself is defined non-
;;; deterministically as an ordered tree. It is a clear specification of 
;;; the order in which frames are written, and correctly models the fact 
;;; of nested frame writing.

;;; Definition 2.1
;;; X is a child of Y iff:
;;; 	X is a subblock of Y
;;; 	X is an attribute of Y
;;; 	X is a subworkspace of Y
;;; 	X is an embedded-rule
;;; 	X is a simulation-subtable of Y
;;; 	X is a connection, and Y is its input-end-object

;;; (Generally, this paper discussed frames, and relations, graphs, 
;;; orderings, and sequences thereof. The single exception is that a 
;;; connection will be treated as though it were a frame, although in 
;;; fact it is either a structure or a structure and a frame.)

;;; Definition 2.2
;;; X is a parent of Y iff:
;;; 	X is the superblock of Y
;;; 	X is the parent-frame of Y
;;; 	X is the parent-of-subworkspace of Y
;;; 	X is the parent-variable of Y
;;; 	X is the input-end-object of Y

;;; Definition 2.3
;;; Descendent and ancestor are defined as the transitive closures of 
;;; child and parent respectively.

;;; (When a relation R is a transitive closure of another relation, it is 
;;; always the case that xRx for any x. Thus any frame is an ancestor or 
;;; descendent of itself.)

;;; Constraints 2.4 
;;; X is the child of Y if and only if Y is the parent of X. A frame has at 
;;; most one parent. The directed graphs of child and parent are each 
;;; loop free.

;;; [We believe that these constraints have been observed at all times in 
;;; the history of G2.]

;;; [There are future plans to reduce the number of slots on frames 
;;; required to represent child and parent. This will require examination 
;;; of the software and detailed modification of these definitions, but 
;;; the rest of the theory is left intact.]

;;; Definition 2.5
;;; A top-level kb-workspace is one which has no parent.

;;; Definition 2.6
;;; A frame is in limbo if it  has no parent and is not a kb-workspace.

;;; Definition 2.7 
;;; A frame is intrinsically not savable if transient-p or or do-not-
;;; save-in-kb-p is true for it.

;;; Definition 2.8
;;; A frame is savable if (1) it is a system-table, or (2) it is a 
;;; definition in limbo and is not an orphan (documented in software), or 
;;; (3) it has an ancestor which is a top-level kb-workspace and it has 
;;; no ancestor which is intrinsically not savable. 

;;; (Note that it may itself be a top-level kb-workspace, and must not 
;;; itself be intrinsically not savable.)

;;; (Note that a definition placed on a subworkspace of a transient item 
;;; is not savable.)

;;; Algorithm for computing savability:
;;; Check in order:
;;; (1) if it is intrinsically not savable then it is not savable.
;;; (2) if it is a system-frame then is savable.
;;; (3) if it is a definition and it has no parent then it is savable.
;;; (4) If it is a kb-workspace and has no parent it is savable.
;;; (5) if it has no parent it is not savable.
;;; (6) if its parent is savable then it is savable.
;;; (7) it is not savable.

;;; [The algorithm is made more efficient en mass by determining the 
;;; savability of all kb-workspaces and marking them first.]

;;; Definition 2.9
;;; X is directly connected to Y iff X is an input-end-object or 
;;; output-end-object of Y, or Y is an input-end-object or output-end-
;;; object of X. 

;;; Definition 2.10
;;; Connected is the transitive closure of directly connected.

;;; Connected is a symmetric, transitive relation. 

;;; Definition 2.11 
;;; X is represented by Y if Y is on frame-representations of X. If X is 
;;; represented by Y, then Y represents X.

;;; [Generally, if Y represents X and Y is a table, then there is a pointer 
;;; to X in table-rows of Y.]

;;; Definition 2.12
;;; X is directly reachable from Y iff:
;;; 	X is a subblock of Y
;;; 	X is an attribute of Y
;;; 	X is an embedded-rule of Y
;;; 	X is a simulation-subtable of Y
;;; 	X is a parent-frame of Y
;;; 	X is a parent-of-subworkspace of Y
;;; 	X  is connected to Y
;;; 	X represents Y
;;; 	Y represents X

;;; Being a superblock or a subworkspace does not imply direct 
;;; reachability because these slots are not in fact saved.

;;; Notice that the only way to reach a kb-workspace is from a frame 
;;; that represents it.

;;; Definition 2.13
;;; Reachable is defined as the transitive closure of directly 
;;; reachable. The directed graph defined by directly reachable is called 
;;; the reachability graph.

;;; The G2 saving algorithm has the property that when writing a frame, 
;;; in most cases in which it encounters a reference to another frame 
;;; that has not yet been written, it must immediately write the 
;;; referenced frame before continuing. We will be focusing attention on 
;;; edges of the reachability graph that go from a savable frame to one 
;;; that it is not savable. 

;;; When a technique exists in the software for not including a 
;;; referenced frame (because it should not be saved) this is called 
;;; clipping. At present, G2 is able to clip subblocks and frame-
;;; representations. When clipping an edge that transitions from savable 
;;; to not savable, the fact that pointers in G2 are often bidirectional is 
;;; not a problem because the other frame is never going to be written.

;;; [As of October, 1990, subblocks and frame-representations, if not 
;;; savable, are clipped. We should consider clipping connections and 
;;; represented frames soon.]

;;; Definition 2.14
;;; The clipped reachability graph is the reachability graph less all edges 
;;; which go from a savable to a non-savable frame via being a subblock 
;;; or being a representation. 



;;; 3. The Saving Algorithm

;;; Definition 3.1
;;; To specify the behavior of the saving algorithm, we define a saving 
;;; tree which is an ordered (n-ary) tree. Every node of the tree except 
;;; the root is a frame. 

;;; On an ordered tree, node X is to the left of node Y if there is a node 
;;; at which two distinct subtrees containing X and Y respectively join, 
;;; and the subtree containing X is to the left of the subtree containing 
;;; Y. For any X and Y, either X is to the left of Y, Y is to the left of X, or 
;;; there is a descending path that containing both X and Y. "To the left 
;;; of" is a partial ordering.  

;;; The algorithm for specify the saving tree is non-deterministic. It 
;;; does not completely describe the ordering behavior of the 
;;; implemented algorithm which in any case depends upon 
;;; environmental details such as the ordering of various stored lists. It 
;;; does have enough determinism to prove what we need to prove here.

;;; First, an initial sequence of certain frames is specified. This 
;;; contains in order: (1) all system-frames in any order, (2) all 
;;; definitions in any order such that a definition of a subclass always 
;;; follows the definition, if any, of its superior class, and (3) all 
;;; savable kb-workspaces. (The reason for specifying savable only for 
;;; kb-workspaces is that we are defining what the algorithm actually 
;;; does.)

;;; [If any definition is not savable, the kb is defined to be unsavable in 
;;; G2 Version 2.0. This happens when a definition is placed on a 
;;; subworkspace of a transient item.]

;;; [Savability was defined only as of October, 1990. Before that, all kb-
;;; workspaces were saved.]

;;; To build the saving graph, start by placing the first frame of the 
;;; initial sequence as the leftmost node directly below the root. Below 
;;; it, build an ordered tree consisting of any depth first traversal of 
;;; the portion of the clipped reachability graph that can be reached from
;;; that frame, not including any frames already incorporated into the tree.
;;; Since the clipped reachability graph is not ordered, there is non-
;;; determinism in the way this tree is built. This is intended to model 
;;; the behavior of the G2 saving algorithm which when writing a frame, 
;;; must write every frame reachable from that frame except those that 
;;; are clipped.

;;; To continue building the saving tree, iterate over the initial 
;;; sequence omiting frames that are already part of the tree. If a frame 
;;; is not already part of the tree, add it as the next node (to the right) 
;;; directly below the root, and build a subtree in the same manner as 
;;; was done for the first frame of the initial sequence.

;;; This complete the definition of the saving tree. If this seems hard to 
;;; follow, just reflect that the actual saving algorithm iterates over 
;;; the starting sequence, writing everything that is reachable but not 
;;; clipped and that has not already been written.

;;; Definition 3.2
;;; If X is to the left of Y on the saving tree, we shall say that X is 
;;; written before Y, and Y is written after X. This is a partial 
;;; ordering. It might be that X is written within Y or visa versa.


;;; 4. Requirements of Saving

;;; 1. Every savable frame must be on the saving tree.

;;; 2. No frame that is not savable may be on the saving tree.

;;; 3. A definition may not be written before the definition of its 
;;; superior class, if any.

;;; 4. A definition must be written before any instance of its class is 
;;; written.

;;; 5. All definitions must be on the saving tree.

;;; 6. [?? System-frames must be written before certain other frames 
;;; are written. We do not know what the actual constraints are here. At 
;;; present, some format-frames are written while system-frames are 
;;; being written. Representations of system-frames are also written 
;;; at this time.] 

;;; To show that these requirements are not violated, we must show 
;;; that certain constraints are observed. In this process, we find that 
;;; there are certain KBs which cannot be saved because their structure 
;;; results in a violation of these requirements. We identify these as we 
;;; review the requirements (1-5):

;;; Requirement 1: No constraints are needed to show that the saving 
;;; tree does include all savable frames. All system-tables and 
;;; definitions are on the saving tree (even unsavable definitions). All 
;;; savable kb-workspaces are explicitly included. All other savable 
;;; frames are descendents of and reachable from savable kb-
;;; workspaces, because all pathways for being a child are reachable 
;;; with the exception of being a subworkspace.

;;; Requirement 2: To show that no unsavable frames are on the saving 
;;; tree requires detailed analysis. It is not always the case, thus the 
;;; saving algorithm must detect violations and refuse to save such a 
;;; KB. When an unsavable frame is on the saving tree it must be the 
;;; case that (1) it is on the initial sequence, or (2) there is an edge of 
;;; the clipped reachability graph that goes from a savable frame to it.

;;; The only violations that are possible on the initial sequence are 
;;; unsavable definitions. Definitions are explicitly checked for 
;;; savability before saving.

;;; There are currently two sources of violation on the clipped 
;;; reachability graph. They occur (1) when a savable frame is connected 
;;; to an unsavable one, and (2) when a savable representation 
;;; represents a frame that is not savable.

;;; Case 1: A savable block has an unsavable connection.
;;; Case 2: An unsavable block has a savable connection.

;;; Both these cases are treated by iterating over all subblocks of 
;;; savable kb-workspaces, and iterating over the output connections of 
;;; these. A violation occurs if one end of the connection is intrinsically 
;;; not savable and the other end is intrinsically savable,  or when the 
;;; connection is intrinsically not savable, but the end objects are both 
;;; intrinsically savable. There is no violation if the connection is 
;;; intrinsically savable, but the end objects are intrinsically not
;;; savable, because the connection is not savable for reason that its
;;; parent is not.

;;; For this to work, there is a constraint that any connected set of 
;;; blocks has the same parent. They are either all subblocks of a 
;;; workspace, or in the case of a transient item in limbo, there is no 
;;; parent for either the item or its loose ends. Thus it is not necessary 
;;; to perform a more expensive ancestor search to determine
;;; savability.

;;; In order for a transient object with stubs placed on a workspace not 
;;; to be flagged as a violation, there is now a constraint that a loose 
;;; end must be transient or not according as its other end is transient 
;;; or not.

;;; Case 3: A savable representation represents an unsavable frame. 

;;; These must all be checked explicitly. At present, all representations 
;;; are tables. There is now a way to iterate over all represented 
;;; frames of a table. These must be explicitly checked for savability, 
;;; since no context can be presumed.

;;; Violations of cases 1, 2 and 3 are checked before saving.

;;; Requirement 3-4: These are satisfied if we can show that no 
;;; definition is reachable from a system-frame or a definition. The 
;;; constraints for this to be the case are numerous. (1) Neither of these 
;;; can have subblocks that lead anywhere. Presently, the subblocks path 
;;; leads only to name-boxes and format-frames. (2) Neither has 
;;; attributes. (3) Neither is embedded. (4) Neither is a simulation-
;;; subtable. (5) Neither has connections. (This was only implemented 
;;; when it was discovered that it was possible to drag connections into 
;;; definitions.) (6) Representations are a problem. At present, we check 
;;; for savable representations of definitions which either have 
;;; connections, or represent things other than the particular definition. 
;;; All other edges leading away from representations have been 
;;; examined, and they do not appear to lead anywhere that is dangerous.

;;; There is presently no check made for representations of system-
;;; frames. This will be a problem after tables that represent more 
;;; than one thing can become savable. System-frames are not reachable 
;;; from inspect now, which blocks the only way known to get a 
;;; representation with connections. It is possible to get a savable 
;;; attribute table for a system-table, but connections cannot be 
;;; dragged into it. Altogether, this situation is the most fragile part of 
;;; savability.

;;; Requirement 5: All definitions are saved.  There cannot be a violation 
;;; of requirement 5, but there can be violation of requirement 2.

;;; Requirement 6: Very little is known about the required order for 
;;; reading system-frames. At present format-frames, and attribute 
;;; tables that represent them are reachable from them. This may be 
;;; about to change when tables are introduced into G2.


;;; 6 Design Issues

;;; The present system is fragile because the constraints are 
;;; complicated to understand, and to a large extent depend upon the 
;;; user interface, or on the belief that a certain configuration cannot 
;;; be arrived at. Avoidance of errors requires continual group 
;;; mindfulness.

;;; It is important that no new savable slots with pointers be 
;;; introduced, and none of the numerous constraints that make this 
;;; system work be changed, without prior discussion.

;;; One proposal is to go over to a new format for saving in which 
;;; frames need not be written when pointers to them are encountered. 
;;; Instead, an index is issued. This requires that upon reading, it is 
;;; possible to determine the size vector to allocate the first time that 
;;; an index is encountered. There are various ways to accomplish this, 
;;; including having all frames be the same size, and having 
;;; substructures for the variations as required. Another way is to 
;;; include a reference to a foundation class the first time any index 
;;; number is written.

;;; However, there are other things that can be done which are less 
;;; radical, and the recursive writing does have a certain elegance and 
;;; simplicity in it. 

;;; (1) Reading sequence problems for definitions can be solved by writing 
;;; out class descriptions before writing out any frames. Then it does 
;;; not matter when the definitions are written.

;;; (2) Sequence problems, if any, for system-frames are simply not known 
;;; at this point. They need to be investigated.

;;; (3) The other class of problems has to do with clipping. If all edges that 
;;; go from savable to non-savable can be clipped, then these problems 
;;; go away. 

;;; (3a) Clipping of connections is not at all difficult. Transient connections 
;;; to savable blocks can be omited. When a savable connection has a 
;;; transient item at the other end, the situation is less clear. Should 
;;; the connection be omited, reduced to a stub, or should the transient 
;;; item be replaced with a permanent loose end?

;;; (4) Being able to clip the table-rows of a table to avoid references to 
;;; unsavable frames should be feasible if it is studied. 

;;; (5) If new savable slots with pointers are introduced, one should 
;;; consider how they can be clipped when they are first designed.

;;; (6) The one remaining problem, placement of definitions on 
;;; subworkspaces of transient items, is an open issue.



;;; 8. Miscellaneous Notes:

;;; There is a saved slot of workspaces called stack-of-subblocks. This 
;;; list is a subset of subblocks. Furthermore, the implementation of 
;;; clipping is done in the same way as for subblocks, that is, write-
;;; frame-for-kb does nothing if its argument is not savable.






;;;; Changes to make new saved KB formats work


;;; 1. Review pre-existing-frame. Could any of these be referenced?
;;;    Possibly, we now deal with that.

;;; 2. Savable-block-p issues.
;;;     (a) Representation and the represented are blocks.
;;;     (b) Referenced plots are savable.

;;; 3. Continue to stress savable slots with frames issue.

;;; 4. Check hydro.kb which has a concurrent-block. -ok-

;;; 5. The identity problem for merged KBs when doing a build.

;;; 6. Build a test for references to non-frames, and frames that
;;;    are doubly referenced. Build a test for duplicate fsns.

;;; 7. Show MHD format-frame changes.

;;; 8. For merge.
;;;       Ignore read in fsn.
;;;       Renumber every frame at the time that it is read in.



;;; End file with CR

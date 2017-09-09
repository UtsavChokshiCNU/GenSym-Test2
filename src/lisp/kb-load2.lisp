;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module KB-LOAD2: Loading, Merging, Knowlege Bases

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson, Michael Levin, Mark H. David
	 
 
(declare-forward-references-to-module kb-save2
  savable-block-p
  identify-all-savable-kb-workspaces
  empty-kb-p
  clear-kb
  restore-image-planes-to-pane-now-or-later
  note-as-frame-with-kb-state-changes
  (current-kb-serial-number variable))

(declare-forward-references-to-module kb-save1
  make-or-clear-complete-kb-name
  reformat-as-appropriate
  #+pre-g2-v5-licensing	   ; (MHD 1/10/96)
  reclaim-rest-of-index-count)


(declare-forward-references-to-module kb-save2
  undo-kb-state-changes
  undo-kb-state-changes-for-frame
  restore-image-planes-to-pane
  release-kb
  remove-as-frame-with-kb-state-changes)

(declare-forward-references-to-module kb-save3
  change-all-permanently-changed-things-are-marked
  try-to-get-newest-version-of-file-1
  file-is-in-source-code-control-p
  non-update-kb-check-1)


(declare-forward-references-to-module kb-save4
  read-initial-plist-for-clear-text-kb
  read-clear-text-module
  read-top-level-xml-element)

(declare-forward-references-to-module warmboot
  read-runtime-data-for-block
  read-past-runtime-data-for-block)

(declare-forward-references-to-module cells
  cleanup-g2-cell-array
  initialize-g2-cell-array-after-reading
  initialize-g2-cell-array
  note-g2-cell-array-runs-while-inactive-change)

(declare-forward-references
  (put-parent-for-its-indexed-attributes function variables)
  (make-all-indexed-attribute-hash-tables function variables)
  (reclaim-all-indexed-attribute-hash-tables function variables)
  (system-reset function cycles)
  (install-compiled-byte-code-body function stack-kern)
  (compiled-kb-initialization-argument function stack-kern)
  (put-attribute-value function install)
  (update-representations-of-variable-or-parameter-value 
    function variables)
  (change-on/off-switch function controls)
  (activate-if-possible-and-propagate-for-kb-workspace function activate)
  (update-indexed-attribute-properties function variables)
  (get-or-make-entry-to-set-of-all-permanent-computation-styles function cells)
  (read-truth-value-for-kb function sets)

  (launch-compile-to-bring-kb-up-to-date function queries)

  (kb-configuration variable filters)
  (fix-up-double-click-configuration-clauses function filters)
  (make-declaration-clause-for-item-configuration function filters)
  (set-ignore-insert-action-duplicate-element function grammar7)
  (set-get-connection-vertices-backward-compatibility function grammar7)
  (set-print-means-print-to-server-in-configurations function grammar7)
;  (set-right-click-lifts-to-top-in-native-ui function grammar7)
  (set-inconsistent-behavior-of-move-in-configurations function grammar7)
  (set-ignore-snap-grid-in-transfer-operations function grammar7)
  
  (recompile-on-next-load variable comp-utils)
  (add-as-item-referring-to-name? variable install)
  (post-analyzer-warning-note-if-necessary function install)
  (post-collected-warnings function install)

  (color-or-metacolor-p function grammar4)
  (get-saving-parameters function kb-save3)
  (module-name-string-for-xml-object function kb-save4)
  (read-clear-text-module-from-xml-object function kb-save4))

(declare-forward-reference remove-dialog-info-from-ui-client-interface-dialog-list function) ;VIEW-G2


;;;; Post-Loading Cleanup and Fixup



;;; `Delete-block-after-reading-kb' ...  These frames are deleted after restoring
;;; image planes to the detail pane and before post-loading fixups.  The function
;;; that will end up deleting the blocks then is
;;;
;;;    delete-blocks-and-connections-to-be-deleted-after-reading



(defvar blocks-to-delete-after-reading-kb)

(defun delete-block-after-reading-kb (block)
  (setq blocks-to-delete-after-reading-kb
	(gensym-cons block blocks-to-delete-after-reading-kb)))


(defvar connections-to-delete-after-reading-kb)

(defun delete-connection-after-reading-kb (connection)
  (setq connections-to-delete-after-reading-kb
	(gensym-cons connection connections-to-delete-after-reading-kb)))


(defvar blocks-to-delete-after-unsquirreling)

(defun delete-block-after-unsquirreling (block)
  (setq blocks-to-delete-after-unsquirreling
	(gensym-cons block blocks-to-delete-after-unsquirreling)))


;;; The variable `blocks-with-bad-connections' is a gensym list of
;;; (reference-fsn . blocks) computed during loading and processed
;;; in the post-loading function `delete-bad-connection-structures'.

(defvar blocks-with-bad-connections)


;;; A `post-loading function' is a function of no arguments that is executed after
;;; every successful load or merge.  (In certain cases, it could be
;;; applied to an empty kb or the kb that existed before loading.)  Each post-loading
;;; function is executed exactly once as the last thing to happen within read-kb, and
;;; the order in which they happen is not guaranteed.  The function must be
;;; non-harmful to execute from a paused kb.  Remember that when doing a
;;; merge, some of the work that it may expect to do may be done already
;;; and some may not be.

;;; Post-loading functions may call delete-frame.  They are called after the blocks
;;; "deleted" using delete-block-after-reading-kb have been processed.

;;; If the option :once-only t is used, the function will not be called during a modular
;;; merge except past the last of the modules. Any function with this option must
;;; be independent of any binding context other then the top level execution loop
;;; of G2. It may get executed outside of any reading context. (Note that many
;;; post-loading-functions reference kb-flags-from-last-kb-read, and so do not qualify.)

;;; Historical note: while it seems to be technically correct to run
;;; post-load functions after conflict resolution, changing the
;;; order in which things happen to this extent seems risky. We
;;; have encountered one part of one post-load function that must be
;;; run after conflict resolution; it's possible there are others.
;;; So for safety, and to make only the minimal change that solves
;;; the problem, we leave all once-only post-load functions running
;;; after conflict resolution, and only move the running of post-load
;;; functions that are run for each module to before conflict resolution. -alatto, 1/6/05

;;; So whether a post-loading-function is run before or after conflict
;;; resolution is controlled by the option :after-conflict-resolution,
;;; which can have one of 3 values: :always, :never, or :switched (the
;;; default). If the value is :switched, or the :after-conflict-resolution
;;; option is unspecified, then whether the function is run before or
;;; after conflict resolution is determined by the value of the switch
;;; switched-once-only-post-loads-are-after-conflict-resolution, currently
;;; that it can be easily changed if desired.

;;; The :after-conflict-resolution option should only be specified for
;;; functions where :once-only t is specified; since conflict resolution
;;; is only performed once, it only makes sense to specify this for
;;; once-only post-loading functions.

;;; In the error-recovery case, we run both the functions
;;; on list-of-error-recovery-post-loading-functions, and
;;; list-of-post-conflict-resolution-post-loading-functions.
;;; This is to ensure that the post-conflict-resolution functions
;;; always get run last, after the pre-conflict-resolution functions.

;;; We keep separate lists of the various sorts of post-loading functions,
;;; to give us flexibility in do-post-loading-functions as to when
;;; to execute which sort.

;;; In theory, post-loading functions should be free of order dependencies.
;;; However, there is at least one known exception to this:
;;; rendezvous-frame-denotations-in-relation-instances must run before
;;; delete-type-violating-relation-instances. To make sure this happens,
;;; without otherwise perturbing the current order in which post-loading
;;; functions are executing in case of existing inadvertant dependencies,
;;; we enforce a rule that those post-loading-functions with
;;; (:after-conlict-resolution :switched) always run before those with
;;; (:after-conlict-resolution :always). For consistency, we also
;;; ensure that those with (:after-conlict-resolution :never) always run
;;; before those with (:after-conlict-resolution :switched)
;;; For functions with (:after-conflict-resolution :switched), we maintain
;;; the existing order with respect to the non-once-only functions (that
;;; is, interspersed with them in reverse order of definition), since the
;;; few functions for which :never or :always are specified are the ones
;;; where we have thought carefully about relative order, while for
;;; the others we want to preserve the existing execution order for
;;; safety's sake -alatto, 1/20/05

(defparameter switched-once-only-post-loads-are-after-conflict-resolution t)

(defvar list-of-module-pre-conflict-resolution-post-loading-functions nil)
(defvar list-of-once-only-pre-conflict-resolution-post-loading-functions nil)
(defvar list-of-once-only-switched-post-loading-functions nil)
(defvar list-of-once-only-post-conflict-resolution-post-loading-functions nil)
(defvar list-of-switched-and-module-post-loading-functions nil)

(defvar post-loading-functions-will-be-executed-again-later? nil)

(defmacro def-post-loading-function (name-or-name-and-options &body body)
  (let* ((name
	   (if (atom name-or-name-and-options)
	       name-or-name-and-options
	       (car name-or-name-and-options)))
	 (options 
	   (if (atom name-or-name-and-options)
	       nil
	       (cdr name-or-name-and-options)))
	 (once-only?
	   (getf options :once-only))
	 (after-conflict-resolution?
	   (getf options :after-conflict-resolution)))
    #+development
    (when (and after-conflict-resolution? (not once-only?))
      (cerror "Make it once-only"
	      "Post-loading function ~S specified after-conflict-resolution, but not specified as once-only"
	      name)
      (setq once-only? t))
    (when (and once-only? (not after-conflict-resolution?))
      (setq after-conflict-resolution? :switched))
    `(progn
       ,@(case after-conflict-resolution?
	   (:always
	     `((pushnew ',name list-of-once-only-post-conflict-resolution-post-loading-functions)))
	   (:never
	     `((pushnew ',name list-of-once-only-pre-conflict-resolution-post-loading-functions)))
	   (:switched
	    `((pushnew ',name list-of-once-only-switched-post-loading-functions)
	      (pushnew ',name list-of-switched-and-module-post-loading-functions)))
	   ((nil)
	    ;; non-once-only case.
	    `((pushnew ',name
		       list-of-module-pre-conflict-resolution-post-loading-functions)
	      (pushnew ',name
		       list-of-switched-and-module-post-loading-functions)))
	   #+development
	   (t (cerror "treat it as :switched"
		      "Bad value ~S for :after-conflict-resolution: should be ~
                       :always, :never, or :switched")
	      `((pushnew ',name list-of-once-only-switched-post-loading-functions)
		(pushnew ',name list-of-switched-and-module-post-loading-functions))))
       (defun-void ,name ()
	 ,@body))))

;; Consider having post-loading functions executed only after successful loads and
;; merges.

;; Consider having a predicate frame-from-just-read-kb-p for use in post-loading
;; functions.



;;; The function `do-post-loading-functions' runs the post-loading
;;; functions. It's called from either continue-read-kb or, in a special
;;; error-recovery case, from read-modules-of-kb-per-loading-schedule.
;;; When called from continue-read-kb, the type argument is either
;;; :before-conflict-resolution or :after-conflict-resolution, and
;;; the appropriate class of post-loading functions are executed.
;;; In the error recovery case, the type arg is :error-recovery. In this
;;; case, it only runs the once-only post-loading functions, running
;;; first the pre-conflict post-loading functions, followed by
;;; the post-conflict post-loading functions..  This is an
;;; unusual error case, which comes up when the loading of a KB is abandoned
;;; as unsuccessful.

;;; The subfunction `do-one-post-loading-function' is called for each individual
;;; post-loading function.  Its position arg is used in verbose mode only, and
;;; should be a small fixnum integer giving its 1-based position in the list of
;;; post-loading functions.

;;; The parameter `verbose-post-loading-p' can be used to enable verbose mode,
;;; which causes the printing of entry and exit statistics, even in
;;; non-development, about post-loading functions.  By default it's nil, of
;;; course, but can conveniently be set to true in in a debugger, or transiently
;;; in the saved version of this file or its chestnut-translator-generated C
;;; file counterpart.  This can be helpful for isolating bugs, problems, and
;;; bottlenecks.  In verbose mode, this prints the total number of functions to
;;; call, prints the name of each function as its entered and exited, prints the
;;; time taken to run each function (to the nearest second).  If a given
;;; function takes a more than one second to run, exclamation points (!!!)
;;; appear next to its timing.  Finally, the time taken to run all of the
;;; post-loading functions is printed.


(defparameter verbose-post-loading-p nil)

;;; This business with lists of lists is a bit of a kludge.
;;; It should be cleaned up, to build a single list for each
;;; type of postloading. We can build these the first time do-post-loading
;;; is called. -alatto, 5/28/03

(defun sum-list-lengths (lists)
  (let ((sum 0))
    (loop for list in lists
	  do
      (incf sum (length (symbol-value list))))
    sum))

(defun do-post-loading-functions (type)
  (let ((list-of-lists-of-functions
	  (ecase type
	    (:error-recovery
	     '(list-of-once-only-pre-conflict-resolution-post-loading-functions
	       list-of-once-only-switched-post-loading-functions
	       list-of-once-only-post-conflict-resolution-post-loading-functions))
	    (:before-conflict-resolution
	     (if post-loading-functions-will-be-executed-again-later?
		 '(list-of-module-pre-conflict-resolution-post-loading-functions)
		 (if switched-once-only-post-loads-are-after-conflict-resolution
		     '(list-of-once-only-pre-conflict-resolution-post-loading-functions
		       list-of-module-pre-conflict-resolution-post-loading-functions)
		     '(list-of-once-only-pre-conflict-resolution-post-loading-functions
		       list-of-switched-and-module-post-loading-functions))))
	    (:after-conflict-resolution
	     (if post-loading-functions-will-be-executed-again-later?
		 ;; non-once-only functions are always run before conflict
		 ;; resolution
		 '()
		 (if switched-once-only-post-loads-are-after-conflict-resolution
		     '(list-of-once-only-switched-post-loading-functions
		       list-of-once-only-post-conflict-resolution-post-loading-functions)
		     
		     '(list-of-once-only-post-conflict-resolution-post-loading-functions))))))
	(error-recovery-case (eq type :error-recovery))
	start-time
	end-time)
    (when verbose-post-loading-p
      (setq start-time (get-fixnum-time))
      (notify-user-at-console
	"~%Doing ~d ~apost-loading functions...."
	(sum-list-lengths list-of-lists-of-functions)
	(if error-recovery-case "ERROR RECOVERY CASE " ""))
      (when reading-kb-p		; not called from read-modules-...
	(notify-user-at-console
	  "KB name: \"~a\"" name-text-string-for-kb-being-read)
	(when name-of-module-being-read?
	  (notify-user-at-console
	    "Module: \"~a\"" name-of-module-being-read?)))
      (when (or error-recovery-case
		(null
		  post-loading-functions-will-be-executed-again-later?))
	(notify-user-at-console
	  "~%*** NOTE: once-only functions ARE enabled. ***"))
      (when (eq type :before-conflict-resolution)
	(notify-user-at-console
	  "~%*** NOTE: pre-conflict-resolution post-loading functions only are enabled. ***"))
      (when (eq type :after-conflict-resolution)
	(notify-user-at-console
	  "~%*** NOTE: post-conflict-resolution post-loading functions only are enabled. ***")))
    (loop
      with do-not-note-permanent-changes-p = t
      for list-of-functions in list-of-lists-of-functions
      with position = 1
      do
      (loop 
	for function in (symbol-value list-of-functions)
	do (do-one-post-loading-function function position)
	   (incff position)))
    (when verbose-post-loading-p
      (setq end-time (get-fixnum-time))
      (notify-user-at-console
	"~%Finished post-loading functions. Elapsed Time: ~d seconds.~%"
	(fixnum-time-difference-in-seconds end-time start-time)))))



(defun do-one-post-loading-function (function position)
  (let (start-time end-time)
    (when verbose-post-loading-p
      (setq start-time (get-fixnum-time))
      (notify-user-at-console
	"~%(~d) Entering ~a function...." position function))
    (funcall-symbol function)
    (when verbose-post-loading-p
      (setq end-time (get-fixnum-time))
      (let* ((seconds (fixnum-time-difference-in-seconds end-time start-time))
	     (emphasis-string (if (>f seconds 0) "   !!!!!!!!!!" "")))
	(notify-user-at-console
	  "     Exiting ~a function.~%     Elapsed Time: ~d seconds~a"
	  function seconds emphasis-string)))))





;;;; Mapping from frame serial number to frame




;;; During KB load a map is needed from the numbers used to index frames in the
;;; KB file to the actual frames that get created.  Since multiple modules can
;;; all be loaded into the same KB environment, we cannot use the numbers in the
;;; KB file as the frame-serial-numbers of the created frames, but for
;;; historical purposes this numbering scheme in KB files has been called the
;;; frame-serial-number-map.  The index numbers within a KB are not necessarily
;;; tightly packed, but they most often are, so a sparse array is used to
;;; implement the mapping from indices to frames.

(defvar frame-serial-number-map)

(defun-simple make-frame-serial-number-to-frame-map ()
  (setq frame-serial-number-map (allocate-sparse-array)))

(defun-void reclaim-frame-serial-number-map ()
  (when frame-serial-number-map
    (reclaim-sparse-array frame-serial-number-map)
    (setq frame-serial-number-map nil)))

(defun enter-frame-into-frame-serial-number-map (frame-serial-number frame)
  (setf (aref-sparse-array frame-serial-number-map frame-serial-number) frame))

(defun get-frame-given-frame-serial-number (frame-serial-number)
  (aref-sparse-array frame-serial-number-map frame-serial-number))






;;;; Reading (Loading and Merging) KBs



;;; A developer should set `ignore-kb-flags-in-kbs?' non-nil, in Lisp, to allow
;;; a KB to be read even though it was created with a newer version of G2.

(defvar ignore-kb-flags-in-kbs? nil)



;;; The variables `saved-detail-pane-configuration' and `frame-serial-number-
;;; for-saved-detail-pane-description?' ...

(def-kb-specific-variable saved-detail-pane-description
  kb-load2 nil nil
  reclaim-slot-value)			; even though not a slot value,
					;   reclaim slot value is used -- it
					;   handles floats as leaves


(def-kb-specific-variable reference-serial-number-for-saved-detail-pane-description
  kb-load2 nil nil reclaim-frame-serial-number)


;;; `Restore-current-workstation-detail-pane' restores the current workstation
;;; detail pane according the current KB's saved detail description and obeying
;;; user restrictions for (or against) showing workspaces.  Restore-current-
;;; workstation-detail-pane assumes it is being called in a for-workstation
;;; context.
;;;
;;; ... Argument specific-module? is passed on to restore-image-planes-to-pane,
;;; q.v., for doc.
;;;
;;; If G2 is not authorized, and there is an easily identifiable OK workspace,
;;; it gets raised to the top, presumably, in front of the title block and any
;;; logbook pages just put up.

(defun restore-current-workstation-detail-pane
    (&optional clear-image-planes-of-other-kb-workspaces?
	       redisplay-logbook?	; new arg. (MHD 7/12/92)
	       specific-module?)	; new arg. (MHD 8/4/04)

  ;; TEMP for 8.0 alpha TWAXL mode. -fmw, 1/20/04
  (unless (inhibit-restore-detail-pane-p current-workstation-window)

    (restore-image-planes-to-pane
      current-workstation-detail-pane
      saved-detail-pane-description
      reference-serial-number-for-saved-detail-pane-description
      t clear-image-planes-of-other-kb-workspaces?
      specific-module?)
    (when redisplay-logbook?
      (redisplay-logbook-in-current-workstation))

    (when (not (g2-authorized-p))
      (let ((ok-workspace?
	      (get-instance-with-name-if-any 'kb-workspace 'ok)))
	(when ok-workspace?
	  (loop for image-plane in (image-planes-this-is-on ok-workspace?)
		do (raise-image-plane-to-top image-plane)))))))

;; At present, this is only used by log-in-workstation (in CONTROLS).
;; (MHD 4/16/90)

;; Note that restore-current-workstation-detail-pane is not called when creating
;; a new single workspace view.
  

;;; `Reading-kb-p' is true while reading (loading or merging) a kb or kb file
;;; and also during any deferred or cleanup actions that occur after reading.

(def-system-variable reading-kb-p kb-load2 nil)



;;; `Loading-kb-p' is true while reading (loading or merging) a kb or kl file,
;;; though not in any deferred or cleanup actions that occur after reading.
;;; Note also that slot putters called during reading will have a non-nil
;;; initializing? argument.

;;; In addition, while loading-kb-p is true, system-version-from-kb-being-read
;;; is bound to the system version of the KB being read.  (System-version-
;;; greater-p is the only operation supported for a system version.)

(def-system-variable loading-kb-p kb-load2 nil)


;; Verify that the initializing? argument can only be non-nil when loading-kb-p is
;; non-nil.  If so, consider eliminating the initializing? argument.  In any case,
;; document slot putters accordingly!


;;; `Saving-kb-p' is true while saving a kb or kl file, though not in any
;;; deferred or cleanup actions that occur after reading.

(def-system-variable saving-kb-p kb-load2 nil)

;; Maybe this, and the one above, should say they are true only while the
;; kb file file is open (for input or output).

;; This has been introduced, and is only used now, to deal with the problem of
;; calling draw methods on frames while saving, e.g. when an X window is
;; "deiconified", which would bomb out when it tried to call a frame which has
;; had an index put into its class slot.  For now, we deal with this by
;; disabling the call (force-process-drawing) in
;; update-file-progress-display while saving.  Other proposals are
;; 
;;    (1) Do marking in some other way (e.g. a using a hash table) so
;;        that marked frames can be drawn.
;;        
;;    (2) Fix refresh-window so that the contents of kb workspaces are
;;        not drawn while saving, on the assumption that only kb
;;        workspaces could have marked frames (which has only been true
;;        since we (mhd/ml) did the patch of 7/26/90 in write-frame-for-
;;        kb).  This would leave the details of the file progress
;;        display correct, and presumably users could live with just
;;        seeing outlines of KB workspaces until the saving finished.
;;        There would also have to be, at the end of saving, a complete
;;        refresh of at least the kb workspaces that were left undrawn
;;        if such a partial refresh happened.
;;
;; Note that draw methods are not called when refreshing image planes
;; from graphic element memory except in the case of opaque blocks (e.g.
;; graphs), which are always refreshed by calling their draw method. 
;;
;; (MHD 8/24/90)
;;
;;
;; UPDATE: The problem above goes away with the  new saved kb format, since
;; the class slot of frames is not set when saving in the new KB format.
;;
;; (MHD 1/24/91)



;;; `Refresh-all-windows-after-merging?' is bound while reading (loading or
;;; merging) and indicates whether all workstations in service should have
;;; their gensym windows refreshed (including all graphic element memory)
;;; after a merge.

;;; While merging, code that changes graphic characteristics of items that
;;; may already be visible on workspaces need to set this to true, so that
;;; graphic element memory is correct.  Such code should set this
;;; variable only to true; it is initially nil and there should be no reason
;;; to set it back if it has ever been set true.  Also, such code need not
;;; worry about whether the KB being loaded is being merged or not; setting
;;; this to true will merely have no effect unless it is the merge case.

(defvar refresh-all-windows-after-merging?)



(defvar kb-load-case?)
(defvar reformat-as-appropriate?)


;;; The variable `name-of-kb-being-read' holds the name of the KB being read.
;;; The name is result of applying make-kb-name to the gensym pathname for
;;; the KB being read.  This produces a (legal) gensym text string.

(defvar name-of-kb-being-read)


(defvar main-kb-being-read?)
(defvar system-version-from-kb-being-read)

(defvar frames-with-substitute-classes)

(defvar kb-object-index-space)

(defvar next-character-for-kb?)

(def-system-variable read-kb-buffer kb-load2 (:funcall make-string 524288))

(defvar read-kb-buffer-index)

(defvar read-kb-buffer-length)

(def-system-variable warmboot-simulated-time kb-load2 nil)





;;; `Warmboot-current-time' ... only to be used when 
;;; warmbooting-with-catch-up? is true.  This can be nil or
;;; undefined at other times.  

;;; This is only available for snapshots taken in or after G2 3.0 Rev. 1.
;;; NOTE: for the case where warmbooting-with-catch-up? is true,
;;; but the KB is from before Rev. 1, i.e., Rev. 0, this discrepency will
;;; be immediately detected while reading, and the KB loading will be
;;; aborted.

(def-system-variable warmboot-current-time kb-load2 nil)
	      





;;; `Read-next-char-for-kb' ...

;; Modified macro read-next-char-for-kb to take an explicit stream instead of
;; rebinding *standard-input*.  Rebinding *standard-input*, while convenient for
;; debugging, causes obscure problems in some Lisps.  This change is associated
;; with the leak-free pathnames project.  jh, 1/11/91.

(def-system-variable read-kb-stream kb-load2 nil)




;;; `basis-kb-frame-serial-number'contains the value of
;;; (current-frame-serial-number) at the time the basis KB was saved. If there
;;; is no basis kb (into which to merge a backup), then the value is not
;;; relevent. The value is establshed when saving and when loading. It is used
;;; to distingish among frame-serial-numbers being read from a backup between
;;; those that reference things that were in the basis KB, and those that were
;;; not. (Without such a test, a frame-serial-number read from a backup could be
;;; identified with a new thing created after the basis was loaded. (For
;;; example, a logbook page.)

 

(def-system-variable basis-kb-frame-serial-number kb-load2 0)



;;; `Fix-frame-with-substitute-class' is a method on classes used to
;;; revise entire classes after loading ...

(def-generic-method fix-frame-with-substitute-class (block))



;;; `Initialize-after-reading' is a class method defined for all blocks and
;;; may be further refined for subclasses.  It is called near the end of the
;;; loading process by read-kb, after the "reading" process has ended, i.e.,
;;; after the entire KB file has been read in.  

;;; By convention, method implementations for a given class X are required to do
;;; (funcall-superior-method X) in addition to their own initializing.  And this
;;; is, by convention, to be done before performing their own initializing (i.e.
;;; initialize-after-reading are after method).

;;; The method is called before the post loading functions.  Unlike the post
;;; loading functions, loading-kb-p is t and reading-kb-p is also T, and
;;; kb-flags is bound to the value of kb-flags with the KB, i.e., the value that
;;; kb-flags had globally in the G2 that saved the KB that is now being restored
;;; (read).
;;;
;;; The order of iteration over the frames is unspecified.

;;; See also the initialize method, def-slot-putter, and def-post-loading-function.

(def-generic-method initialize-after-reading (block))

;; Doc. was wrong about the facts concerning how this compared with post-loading
;; function.  I've just fixed the documentation and added to it. Hopefully, no
;; code was written erroneously because of the wrong/misleading information.  I
;; plan to take advantage the fact that KB-FLAGS don't need to be rebound to
;; kb-flags-from-last-kb-read as with post-loading functions. (MHD 3/20/95)

;; I think ML, and AGH know more about this - 10/22/91 ben -- I made a pass at
;; this myself, after consultation with ML. Changed the name and the spec a
;; little.  (MHD 10/24/91)




;;; The development-only system variable kb-char-unread? is used to detect
;;; people pushing back more than once character into the kb reading stream.
;;; This was the cause of a recent bug (-jra 11/17/93).  This error checking
;;; only happens in development images.

#+development
(def-system-variable kb-char-unread? kb-load2 nil)

(defvar kb-format-identifier-read? nil)


;;; The macros `read-char-for-kb' and `read-next-char-for-kb' are used to read
;;; all characters from knowledge bases.  It used to be that
;;; read-next-char-for-kb was a little faster, but that is no longer the case.

;;; This macros use a single string from the system variable read-kb-buffer as
;;; an input buffer for use by the g2-stream-read-into-buffer function.
;;; Also note that the variable number-of-kb-characters-so-far? is only
;;; incremented when refilling the buffer to further streamline the reading of
;;; each character.  Since this variable is currently only used to update a file
;;; progress display, and since it is only looked at once every 50 lines (i.e.
;;; 50 * 80 chars/line = 4000 characters) it is OK to let its value lag somewhat
;;; from the true value (at most 2047) during reads.  -jra 11/16/93

;;; TODO: almost all caller of `read-char-for-kb' assumes the return value is a
;;; character, however the `read-next-char-for-kb' may return NIL in theory.
;;; How to fix the potential type issues here?  -- Chun Tian (binghe), June 2016.

(defmacro read-char-for-kb ()
  `(read-next-char-for-kb))

(defmacro read-next-char-for-kb ()
  `(cond ((null read-kb-buffer-index)
	  nil)
	 (t
	  (read-next-char-for-kb-1))))

;; A type-safe version (never returns NIL)
(defmacro read-char-for-kb-1 ()
  `(read-next-char-for-kb-1))

(defmacro read-next-char-for-kb-1 ()
  `(cond ((<f read-kb-buffer-index read-kb-buffer-length)
	  (prog1 (schar read-kb-buffer read-kb-buffer-index)
	    #+development
	    (setq kb-char-unread? nil)
	    (incff read-kb-buffer-index)))
	 (t
	  (read-next-char-for-kb-from-refilled-buffer))))

(defun-simple read-next-char-for-kb-from-refilled-buffer ()
  (when number-of-kb-characters-so-far?
    (incff number-of-kb-characters-so-far? read-kb-buffer-index))
  (let ((number-of-characters-in-buffer?
	  (g2-stream-read-into-buffer
	    read-kb-buffer
	    (length-of-simple-string read-kb-buffer)
	    read-kb-stream)))
    (cond ((and number-of-characters-in-buffer?
		(pluspf number-of-characters-in-buffer?))
	   (setq read-kb-buffer-length number-of-characters-in-buffer?)
	   (setq read-kb-buffer-index 1)
	   #+development
	   (setq kb-char-unread? nil)
	   (schar read-kb-buffer 0))
	  ((clear-text-kb-format-p)
	   (setq read-kb-buffer-index nil)
	   nil)
	  ((null kb-format-identifier-read?)
	   #\Z)
	  (t
	   (abort-on-bad-kb)))))




;;; The macro `unread-char-for-kb' places its argument in next-character-for-kb?
;;; which effectively unreads it provided this is not done twice in a row
;;; without reading. It is the user's responsibility not to do that.  The
;;; argument must be the last character read from the stream.

(defmacro unread-char-for-kb (character)
  (declare (ignore character))
  #+development
  `(cond (kb-char-unread?
	  (second-kb-char-unread-error))
	 (t
	  (setq kb-char-unread? t)
	  (decff read-kb-buffer-index)))
  #-development
  `(decff read-kb-buffer-index))
  
#+development
(defun second-kb-char-unread-error ()
  (error "The macro unread-char-for-kb has been called twice without an ~
          intervening read-char-for-kb.  There is only one character worth of ~
          unread available."))




(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar newline-characters
  (let ((temp nil))
    (pushnew #\newline temp)
    (pushnew #.(code-char 10) temp)	; ascii linefeed
    (pushnew #.char-linefeed temp)
    (pushnew #.char-return temp)
    (pushnew #.(code-char 13) temp)	; ascii carriage return
    (pushnew #.(code-char 12) temp)	; ascii page
    (nreverse temp))) ; return in order shown above
)


(def-substitution-macro newline-character-p-macro (character)
  (cond ((char= character #\linefeed)) ; #\newline is #\linefeed (for Lucid and Chestnut)
	((char= character #\return)
	 (setq kb-uses-crlf-p t)
	 t)
	((char= character #\page))))


(defun-simple read-char-for-kb-past-newline ()
  (let ((character (read-char-for-kb-1)))
    (cond ((newline-character-p-macro character)
	   (update-file-progress-display-for-newline-in-kb)
	   ;; handles, e.g., double, triple, quadruple, etc., control-M's:
	   (loop for next-character = (read-char-for-kb)
		 when (not (newline-character-p-macro next-character))
		   do (return next-character)))
	  (t
	   character))))



;;; `Read-char-for-kb-past-spaces' returns the first character after going
;;; past any space elements in the KB.  

(defparameter *ignore-process-newline* 0)

(defun-simple read-char-for-kb-past-spaces ()
  (loop for character
	    = (read-char-for-kb-1)
	    then (read-next-char-for-kb-1)
	do
    (when (and (not (char= character #\space))
	       (not (char= character #\tab))
	       (not (char= character #\;)))
	(if (newline-character-p-macro character)
	  (prog1
	    (when (=f *ignore-process-newline* 50000)
	      (setq *ignore-process-newline* 0)
	      (update-file-progress-display-for-newline-in-kb))
	    (incff *ignore-process-newline*)
	    (incff number-of-kb-lines-so-far))
	  (return character)))))

;; New breakpoint introduced for 4.0.  (MHD 10/8/93)

;; Maybe allow #\Tab at top level -- they tend to get added as "spaces" by
;; mistake in certain cases.  Actually note that tabs, or really any character
;; other than one that "looks like" a newline character, are allowed in a
;; comment (past the ;).

;; This must have negligable function calling overhead in all implementations.
;; Make sure it does, or else make it a substitution macro.





;;; `Break-in-kb' causes a Lisp breakpoint to be called, giving the
;;; line and character position in the file.  This is only defined in
;;; #+development.

#+development
(defun break-in-kb ()
  (break "Break on ^ at KB line ~d~a~a~a."
	 number-of-kb-lines-so-far
	 (if number-of-kb-characters-so-far? " (char " "")
	 (or number-of-kb-characters-so-far? "")
	 (if number-of-kb-characters-so-far? ")" "")))

;; Used only to support the new ;^ breakpoint/space.  (MHD 10/8/93)


;;; `Update-file-progress-display-for-newline-in-kb' should be called for every
;;; Newline read from the file.  It keeps the line count up to date, and it
;;; periodically updates the frame whose tables display the progress to the
;;; users.  If the special variable kb-file-progress is nil, this does nothing.
;;; It's OK is this is not called for absolutely every Newline in the file: it
;;; just means that the count of lines will not be 100% exact.  The line count
;;; is just intended as a rough metric for users.

(defun update-file-progress-display-for-newline-in-kb (&optional force-update-p)
  (when (and kb-file-progress
	     (or force-update-p
		 (=f (modf-positive (incff number-of-kb-lines-so-far)
				    50)	; parameterize this?
		     0)))
    (let ((suppress-updating-of-slot-value-representations? nil))
      (update-file-progress-display
	kb-file-progress
	number-of-kb-lines-so-far
	force-update-p))))



(defmacro radix-94-char (digit)
  `(ascii-code-char (+f ,digit 33)))

(defmacro radix-94-weight (char)
  `(-f (ascii-char-code ,char) 33))

;;; read-binary-word-for-kb, after reading past any spaces, and reads exactly 5
;;; characters and forms the left and right halfs of a 32 bit word from them.
;;; The values are placed in left-place and right-place respectively.

(defmacro read-binary-word-for-kb (left-place right-place)
  (let ((x1 (gensym))
	(x2 (gensym))
	(x3 (gensym))
	(character (gensym)))
    `(let ((,x1 0) (,x2 0) (,x3 0) (,character #\a))
       (declare (character ,character)
		(fixnum ,x1 ,x2 ,x3))
       (setq ,character (read-char-for-kb-past-newline))
       ;; This style of coding uses an extra local variable in
       ;; preference to writing an expression with multiple reads
       ;; which relies on left-to-right expression evaluation to work.
       (setq ,x1 (radix-94-weight ,character))
       (setq ,x2 (radix-94-weight (read-next-char-for-kb-1)))
       (setq ,x1 (+f (*f 94 ,x1) ,x2))
       
       (setq ,x2 (radix-94-weight (read-next-char-for-kb-1)))
       (setq ,x3 (radix-94-weight (read-next-char-for-kb-1)))
       (setq ,x2 (+f (*f 94 ,x2) ,x3))
       (setq ,x3 (radix-94-weight (read-next-char-for-kb-1)))
       (setq ,x2 (+f (*f 94 ,x2) ,x3))
       
       (setf ,left-place (+f (ashf ,x1 3) (ashf ,x2 -16))) 
       (setf ,right-place (logandf ,x2 #.(- (expt 2 16) 1))))))


;;; `read-past-binary-word-for-kb' ...

(defun-void read-past-binary-word-for-kb (print?)
  (loop for i from 1 to 5
	as character
	  = (if (=f i 1)
		(read-char-for-kb-past-newline)
		(read-next-char-for-kb))
	when print?
	  do (format t "~c" character)
	finally
	  (when print? (format t " "))))
  



;;; `Read-list-element-for-kb' ... handles the L (List) element, which can
;;; return either a dotted list or a regular list.  Note that this does
;;; not handle empty lists (i.e., LR); they must be written as #\N

;;; `Read-past-list-element-for-kb' ...

(defun-simple read-list-element-for-kb ()
  (loop with l = (slot-value-cons-macro (read-element-for-kb nil) nil)
	with l-tail = l
	for character = (read-char-for-kb-past-spaces)
	do (character-case character
	     (#\R (return l))
	     (#\. (setf (cdr l-tail) (read-element-for-kb nil))
		  (return l))
	     (t
	       (unread-char-for-kb character)
	       (setq l-tail
		     (setf (cdr l-tail)
			   (slot-value-cons-macro
			     (read-element-for-kb nil) nil)))))))

;; This must have negligable function calling overhead in all implementations.
;; Make sure it does, or else make it a substitution macro.


(defun-void read-past-list-element-for-kb (print?)
  (read-past-element-for-kb print?)
  (loop for character = (read-char-for-kb-past-spaces)
	do (character-case character
	     (#\R (return))
	     (#\. (when print?
		    (format t "~%; Final dotted element: ~%"))
		  (read-past-element-for-kb print?)
		  (return))
	     (t (unread-char-for-kb character)
		(read-past-element-for-kb print?)))))







;;;; Encrypting of Symbols and Strings



(defconstant standard-base-reference 27)

(defvar base-reference standard-base-reference)
(defconstant base-modulus 3989)



;;; Char-encrypt-or-decrypt is used to make the saved KB less readable.
;;; 
;;; Note: we don't really consider this encryption; it's not a superdifficult
;;; thing to break, and it's been made easier to crack in 4.0, as discussed
;;; below.  In particular, we DO NOT tell users that their KBs are "encrypted";
;;; rather, we say that they are "not human-readable".  The "encrypt", then, is
;;; to be used just as an internal name, and should be taken with a grain of
;;; salt.
;;; 
;;; It encrypts ASCII characters with codes 32-91 and 93-126. The state of the
;;; encryption transform is the value of base-reference-variable, which in 3.0
;;; KBs is maintained in the global base-reference, and in 4.0+ KBs is
;;; maintained in a local variable, initialized to standard-base-reference at
;;; the beginning of writing or reading a character sequence (text string).
;;; This state, called base-reference here for expository purposes, is always a
;;; fixnum.  This state is not changed when char-encrypt-or-decrypt is given a
;;; character out of the specified range.  Encrypt-char maps characters within
;;; the range onto other characters within the range. It maps each character
;;; outside of the range onto itself.

;;; Guaranteed property: If base-reference is set to some fixnum < 4000, and
;;; (char-encrypt-or-decrypt ci nil) is executed on some sequence of characters
;;; {ci} resulting in the sequence {di}; if base-reference is then reset to its
;;; initial value, and (char-encrypt-or-decrypt {di} t) is executed, the
;;; resulting series will be {ci}.

;;; char-encrypt-or-decrypt is a non-standard macro in that the second argument,
;;; decrypt?, is evaluated at macro-expand time. It must be t or nil at this
;;; time, and may not be an expression that determines the direction at runtime.

;;; Note one other departure from macro standards: base-reference-variable may
;;; be evaluted 0 times or twice.

;;; Because char-encrypt-or-decrypt has the side effect of modifying
;;; base-reference when applied to a character within the specified range, it
;;; must be called exactly once on each such character when writing, and exactly
;;; once on the transforms of these characters when reading a kb. Thus
;;; decrypting a character, stuffing it back in the input stream (via
;;; next-character-for-kb?)  and decrypting it again will destroy the
;;; decrypting. In read-kb, the only character which is treated in this way is
;;; #\\, (ASCII = 92) which is specifically defined to be out-of-range, and
;;; transforms to itself without modifying base-reference.

;;; char-encrypt-or-decrypt is used in writing KBs to encrypt the texts of
;;; symbols and text-strings, and is not used elsewhere. There is a performance
;;; penalty in its use, and this limits it while accomplishing the purpose of
;;; making a KB reasonably opaque.

;;; char-encrypt-or-decrypt is dependent on the standard ASCII printing
;;; characters and #\space having their standard char-codes. (If a file were
;;; converted to EBSDIC, for example, it would fail.) This dependency is
;;; encapsulated by ascii-code-char and ascii-code-char which would have to
;;; become mapping functions to handle non-ascii files.

;;; Review/Summary of changes (by MHD, et al) from 3.0:
;;; 
;;; - Char-encrypt became char-encrypt-or-decrypt.
;;; 
;;;   - Char-encrypt and Char-decrypt were defined and former callers of
;;;   char-encrypt were converted to char-encrypt/char-decrypt and their (new)
;;;   argument signatures.
;;; 
;;;   - Char-encrypt and Char-decrypt now take a base-reference variable rather
;;;   than always using the global base-reference.  This is mostly an
;;;   optimization, to allow cheaper local vars to be used inside speed-critical
;;;   loops where this is used.
;;;   
;;;   - Char-encrypt and Char-decrypt now take an optional character-
;;;   code-variable? argument, which, when supplied, will be set to the
;;;   resulting character code.  This is information, it turns out, is needed
;;;   anyway by the caller.  A minor optimization.
;;;   
;;;   - The code for the encryption/decryption has been transformed from its
;;;   original appearance in 3.0.  It is now very dense, uses fewer variables,
;;;   uses a few less instructions, and type-declare its variables.
;;;   
;;;   - I added a macro (intended for development, but available as a macro at
;;;   all times) to aid in benchmarking: char-decrypt-n.  By using this, one may
;;;   be able to isolate the cost of the encryption/decryption alone.
;;;   
;;;   - KB-FLAGS were incremented to 238 to mark this change in format. Note
;;;   that no new initial character is needed.  (I.e., J remains the first KB
;;;   character)
;;;   
;;;   - When this is called to decrypt charactes from an old (3.0) KB, the
;;;   base-reference-variable is the global base-reference.  For new KBs, it's
;;;   called with a local variable, initialized at the beginning of each
;;;   character sequence to either base-reference or standard-base-reference.
;;;   In 3.0, it always used base-reference, since base-reference was explicitly
;;;   referenced by the earlier version of this macro, and base-reference was/is
;;;   initialized at the start of reading each KB to a function of the current
;;;   frame serial number at the time of writing and base-modulus.
;;;   
;;;   - When this is called to encrypt a character being written, i.e., in 4.0+
;;;   KBs, it is always called with a local variable initialized to either
;;;   base-reference or standard-base-reference.  It used to use base-reference,
;;;   which was initialized at the start of writing a KB to a function of
;;;   base-modulus and the then current frame serial number.
;;;
;;;   - Started to move towards a new KB format in which system tables were
;;;   saved out in their own section at the start of the KB, and that section
;;;   would be encrypted in the old, "unstable" manner.  I backed that out
;;;   after finding that that added an inordinate amount of diffs.  There are
;;;   commented out parts of KB-MERGE that could be used to reconstruct this
;;;   feature.  Consider, instead, (a) trying to get rid of the feature of
;;;   system tables that makes them write ALL of their slots, and/or (b)
;;;   encoding the hidden parts of the system tables in some other "band"
;;;   (series of lines) of the KB file.
;;;
;;; (MHD 10/1/93)


(def-gensym-c-function c-char-code-encrypt-or-decrypt
  (:fixnum-int "g2ext_characters_cipher")
  ((:fixnum-int character-code)
   (:fixnum-int base-reference-var)
   (:fixnum-int decrypt?)))
   
(def-gensym-c-function c-eval-base-ref-val
 (:fixnum-int "g2ext_eval_base_ref_val")
 ((:fixnum-int base-value))) 

(defmacro char-encrypt-or-decrypt
    (char base-reference-variable decrypt? &optional character-code-variable?)
  (avoiding-variable-capture
      (char &aux code)
    `(let ((,code (ascii-char-code ,char)))
       (declare (type fixnum ,code))		; declare as 8-bit fixnum?
       (setq ,code
	     (char-code-encrypt-or-decrypt
	       ,code ,base-reference-variable ,decrypt?))
       ,@(if character-code-variable?
	     `((setf ,character-code-variable? ,code)))
       (ascii-code-char ,code))))


(defmacro char-code-encrypt-or-decrypt 
    (character-code base-reference-variable decrypt?)
  (let ((result-code '#:result-code))
    `(let ((,result-code ,character-code))
       (declare (type fixnum ,result-code))
       (when (and (/=f ,result-code 92)
		  (<=f 32 ,result-code 126))
	 ;; for almost every character
	 (progn 
	   (setf ,base-reference-variable
		 (c-eval-base-ref-val ,base-reference-variable))
	   (setq ,result-code 
		 (c-char-code-encrypt-or-decrypt ,character-code 
		   ,base-reference-variable 
		   (if ,decrypt? 1 0)))))
       ,result-code)))

(defmacro char-encrypt
    (char base-reference-variable &optional character-code-variable?)
  `(char-encrypt-or-decrypt
     ,char ,base-reference-variable nil ,character-code-variable?))

(defmacro char-decrypt
    (char base-reference-variable &optional character-code-variable?)
  `(char-encrypt-or-decrypt
     ,char ,base-reference-variable t ,character-code-variable?))


(defmacro char-code-encrypt
    (char-code base-reference-variable)
  `(char-code-encrypt-or-decrypt
     ,char-code ,base-reference-variable nil))

(defmacro char-code-decrypt
    (char-code base-reference-variable)
  `(char-code-encrypt-or-decrypt
     ,char-code ,base-reference-variable t))


;;; Char-decrypt-n is intended only for development environments, or possibly
;;; for experimental use in non-development environments.  Its arguments are the
;;; same as for char-decrypt, except that there's an additional argument,
;;; n-times, saying how many times to do the encryption.  N-times is evaluated
;;; at runtime.
;;;
;;; To find the cost of encryption, you simply must compare the timings for some
;;; task involving (a lot) of encryption with n-times varied by some amount, say
;;; 1 the first time, and 10 the second time.

(defmacro char-decrypt-n
    (char base-reference-variable character-code-variable? n-times)
  (avoiding-variable-capture (char n-times &aux saved-base-reference)
    `(let ((,saved-base-reference ,base-reference-variable))
       (loop repeat (-f ,n-times 1)
	     do (char-decrypt
		  ,char ,base-reference-variable ,character-code-variable?))
       (setf ,base-reference-variable ,saved-base-reference)
       (char-decrypt ,char ,base-reference-variable ,character-code-variable?))))

;;; `Benchmark-decrypting-n-times?' is a variable used in development-only to
;;; cause encryption to be run N times, as opposed to the usual 1 time, in
;;; read-character-sequence-as-text-string.  This can be used in development
;;; for benchmarking and evaluating the performance of character decryption.

#+development
(defvar benchmark-decrypting-n-times? nil)





;;;; Storing KB Objects



;;; `Store-next-kb-object' ... returns its argument.

(defmacro store-next-kb-object (kb-object)
  (let ((index (gensym)))
    `(let ((,index (assign-index-in-index-space kb-object-index-space)))
       (store-object-in-index-space
	 kb-object-index-space
	 ,index
	 ,kb-object))))





;;;;  Reading Symbols or Strings



;;; `Read-symbol-or-string-for-kb' ... handles the S (text-string), \:
;;; (keyword), \, (unindexed keyword), \' (symbol), and \` (unindexed symbol) kb
;;; element formats.  Character should be the character corresponding to the
;;; type of element.  Count should be a fixnum that gives the number of
;;; characters to be read.  Count is an integer value that prefixes character.
;;; The current character to be read should be that immediately following
;;; character in the KB.

(defun-substitution-macro read-symbol-or-string-for-kb (count character)
  (cond
    ((char= character #\S)
     (read-character-sequence-as-text-string
       count
       (and new-saved-kb-format-p
	    base-reference)))
    (t
     (let* ((symbol
	      (read-character-sequence-as-symbol
		count
		(and new-saved-kb-format-p
		     base-reference)
		(if (or (char= character #\:) (char= character #\,))
		    ;; intern in keyword package
		    keyword-package-1))))
       ;; return an interned symbol       
       (cond
	 ((or (char= character #\:) (char= character #\,))
	  (when (eq symbol 'nil)
	    (setq symbol ':nil)) ; Bug workaround?!  See note below.
	  (let ((ordinary-symbol? (find-symbol (symbol-name symbol))))
	    (when (and ordinary-symbol?
		       (punctuation-mark-p ordinary-symbol?))
	      (setf (type-of-syntactic-anomaly symbol)
		    'punctuation-mark))))
	 (t
	  symbol))
       (when (or (char= character #\') (char= character #\:))
	 ;; store as object in index space
	 (store-next-kb-object symbol))
       symbol))))

;; Modified so that a keyword of nil is always returned as :nil.  Currently,
;; there is a problem in the Chestnut intern function.  Interning "nil" in the
;; keyword package returned nil instead of :nil.  - cpm, 1/3/92

;; This is coded and is a macro for maximum speed.


;;; `Read-character-sequence-as-text-string' ... callers may not assume that this 
;;; absolutely always returns a string exactly of length number-of-characters;
;;; that will be true, however, in the vast majority of cases.  Due to mostly
;;; historical reasons, however, it cannot be guaranteed.  In particular, illegal
;;; characters and illegal character sequences are dropped from the result string.

;; I believe that the following is true, at least when all the kb flags in this
;; code are true. (ML 4/10/91): The function reads exactly number-of-characters
;; characters with the following exceptions. (1) /{non-simple character}/ may
;; appear internally within the string and is not counted. This is used to
;; effect line breaks as necessary. On some hardware, the break may require two
;; chararacters. (2) If the last character is /, then another slash follows.
;; This second slash must be read and ignored. It is there to avoid ambiguity if
;; the string were to be followed by a newline, which would otherwise invoke the
;; preceeding convention.

;;; Read-encrypted-character-sequence-as-text-string handles the reading and
;;; decrypting of as many characters as specified by number-of-characters from
;;; the KB.  This expects to be called in a 5.0 or greater version in one of
;;; (lightly) encrypted portions of the KB.


;;; `Read-encrypted-character-sequence-into-simple-gensym-string' reads the
;;; requested number of characters from the KB into simple-gensym-string
;;; and returns no useful values.  This is implemented as a macro for
;;; maximum inline speed.
;;;
;;; `Read-unencrypted-character-sequence-into-simple-gensym-string' does the
;;; same thing, but is used when the sequence being read is not encyrpted.  This
;;; is used for reading very small amounts of the KB, and is therefore a not a
;;; macro but a function.
;;;
;;;
;;; `Read-encrypted-character-sequence-into-wide-string' reads the requested
;;; number of characters from the KB into wide-string and returns true or false
;;; based on whether of the characters read in were Gensym complex characters
;;; (\, ~, or @).
;;;
;;; `Read-encrypted-character-sequence-into-wide-string' does the same thing,
;;; but is used when the sequence being read is not encyrpted.  This is used for
;;; reading very small amounts of the KB, and is therefore a not a macro but a
;;; function.

(defmacro read-encrypted-character-sequence-into-simple-gensym-string
    (number-of-characters simple-gensym-string
			  &optional quoted-not-really-encrypted-flag)
  (avoiding-variable-capture (number-of-characters simple-gensym-string)
    `(let (,@(if (not quoted-not-really-encrypted-flag)
		 `((local-base-reference standard-base-reference)))
	   (character #\a)
	   (character-index 0))
       (declare
	 ,@(if (not quoted-not-really-encrypted-flag)
	       `((type fixnum local-base-reference)))
	 (type fixnum character-index)
	 (type character character))
       (loop while (<f character-index ,number-of-characters)
	     do
	 (setq character
	       ,(if quoted-not-really-encrypted-flag
		    `(read-char-for-kb-1)
		    `(char-decrypt (read-char-for-kb-1) local-base-reference)))
	 (cond
	   ((and (char= character #\\)
		 (check-slash-extension-for-character-sequence
		   (=f (1+f character-index) number-of-characters))))
	   (t
	    (setf (schar ,simple-gensym-string character-index) character)
	    (incff character-index)))))))


(defun-simple read-unencrypted-character-sequence-into-simple-gensym-string
    (number-of-characters simple-gensym-string)
  (read-encrypted-character-sequence-into-simple-gensym-string
    number-of-characters simple-gensym-string t))


(defmacro read-encrypted-character-sequence-into-wide-string
    (number-of-characters wide-string
			  &optional quoted-not-really-encrypted-flag)
  (avoiding-variable-capture (number-of-characters wide-string)
    `(let (,@(if (not quoted-not-really-encrypted-flag)
		 `((local-base-reference standard-base-reference)))
	   (character #.%\a)
	   (character-index 0)
	   (complex-p nil))
       (declare
	 ,@(if (not quoted-not-really-encrypted-flag)
	       `((type fixnum local-base-reference)))
	 (type fixnum character-index)
	 (type wide-character character))
       (loop while (<f character-index ,number-of-characters)
	     for chrr = (read-char-for-kb-1)
	     do
	 (setq character
	       (code-wide-character
		 ,(if quoted-not-really-encrypted-flag
		      `(ascii-char-code chrr)
		      `(char-code-decrypt
			 (ascii-char-code chrr)
			 local-base-reference))))
	 (cond
	   ((and (char=w character #.%\\)
		 (check-slash-extension-for-character-sequence
		   (=f (1+f character-index) number-of-characters))))
	   (t
	    (unless complex-p
	      (setf complex-p
		    (or (char=w character #.%\~)
			(char=w character #.%\@)
			(char=w character #.%\\))))
	    (setf (charw ,wide-string character-index) character)
	    (incff character-index))))
       complex-p)))


(defun-simple read-unencrypted-character-sequence-into-wide-string
    (number-of-characters wide-string)
  (read-encrypted-character-sequence-into-wide-string
    number-of-characters wide-string t))


    

(defun-simple read-character-sequence-as-text-string
    (number-of-characters decrypt?)
  (declare (type fixnum number-of-characters))
  (cond
    ((stable-non-human-readable-kbs?)
     (let ((wide-string (make-wide-string number-of-characters)))
       (cond
	 ((if decrypt?
	      (read-encrypted-character-sequence-into-wide-string
		number-of-characters wide-string)
	      (read-unencrypted-character-sequence-into-wide-string
		number-of-characters wide-string))
	  ;; if returns true, there are complex characters that we must transcode:
	  (twith-output-to-text-string
	    (twrite-unicode-from-utf-G-encoded-string
	      wide-string 0 number-of-characters t)
	    (reclaim-wide-string wide-string)))
	 (t wide-string))))
    (t
     ;; Old reliable case as of 8/20/96
     (cond
       ((or (not (character-sequences-breakable-in-kb-p))
	    (not (three-escape-characters-p)))
	(read-character-sequence-as-text-string-old-way
	  number-of-characters decrypt?))
       (t
	(read-character-sequence-as-text-string-for-any-recent-version
	  number-of-characters decrypt?))))))


(defun-simple read-character-sequence-as-symbol
    (number-of-characters  decrypt?  package)
  (declare (type fixnum number-of-characters))
  (cond
    ((stable-non-human-readable-kbs?)
     (let ((simple-gensym-string
	     (obtain-simple-gensym-string number-of-characters)))
       (if decrypt?
	   (read-encrypted-character-sequence-into-simple-gensym-string
	     number-of-characters simple-gensym-string)
	   (read-unencrypted-character-sequence-into-simple-gensym-string
	     number-of-characters simple-gensym-string))
       (intern-gensym-string simple-gensym-string package)))
    (t
     ;; Unencrypted and/or old reliable case as of 8/20/96
     (cond
       ((or (not (character-sequences-breakable-in-kb-p))
	    (not (three-escape-characters-p)))
	(intern-text-string
	  (read-character-sequence-as-text-string-old-way
	    number-of-characters decrypt?)
	  package))
       (t
	(intern-text-string       
	  (read-character-sequence-as-text-string-for-any-recent-version
	    number-of-characters decrypt?)       
	  package))))))






(defun-simple check-slash-extension-for-character-sequence (keep-slash?)
  (let ((next-character (read-char-for-kb)))
    (declare (type character next-character))
    (cond
      ((simple-character-p next-character)
       (unless (and keep-slash? (char= next-character #\\))
	 (unread-char-for-kb next-character))
       nil)
      (t	; i.e., this is a Newline.
       (loop until (char= (read-next-char-for-kb) #\\))
       t))))




;;; `Read-character-sequence-as-text-string-for-any-recent-version' handles any
;;; version but the very oldest ("old way"), but is not optimized for 5.0.

(defun read-character-sequence-as-text-string-for-any-recent-version
    (number-of-characters decrypt?)
  ;; This clause can stay around forever.  Note, however, that it only
  ;; began always providing legal text strings POST 3.0 Beta 0 G2.
  ;; Various illegal characters could be found -- esp. tabs, unquoted
  ;; @'s, and singular guillmots (which were never legal, but were leaked
  ;; into a few KBs). (MHD 3/27/92)
  ;; This will efficiently read in a new text string
  
  (when (and decrypt? (stable-non-human-readable-kbs?))
    (setq base-reference standard-base-reference))
  (let ((local-base-reference base-reference))
    (declare (type fixnum local-base-reference))
    (let ((gensym-string
	    (prog1
		(provide-legal-gensym-string
		  :form-to-determine-string-length number-of-characters
		  :loop-clauses-to-get-next-character
		  (do					; a LOOP DO clause
		    ;; the protocol here is that we end up setting the
		    ;; variables CHARACTER and CHARACTER-CODE as appropriate
		    ;; unless we set the variable SKIP-THIS-CHARACTER-P to true,
		    ;; which case the values of CHARACTER and CHARACTER-CODE
		    ;; are irrelevant.
		    (setq character (read-char-for-kb-1))
		    (cond
		      (decrypt?
		       (setq character
			     #+development
			     (char-decrypt-n
			       character local-base-reference character-code
			       (or benchmark-decrypting-n-times? 1))
			     #-development
			     (char-decrypt
			       character local-base-reference character-code)))
		      (t
		       (setq character-code (char-code character))))
		    (when (char= character #\\)
		      (let ((next-character (read-char-for-kb-1)))
			(declare (character next-character))
			(cond
			  ((simple-character-p next-character)
			   (unless (and (=f (1+f character-index) number-of-characters)
					(char= next-character #\\))
			     (unread-char-for-kb next-character)))
			  (t	; i.e., this is a Newline.
			   (loop until (char= (read-next-char-for-kb-1) #\\))
			   (setq skip-this-character-p t)))))))
	      (when decrypt?
		(setq base-reference local-base-reference)))))
      (prog1 (gensym-string-to-wide-string gensym-string)
	(reclaim-gensym-string gensym-string)))))




;;; `Read-character-sequence-as-text-string-OLD-WAY' ... OBSOLETE -- Only called
;;; when reading rather old KBs. This actually used to be the function
;;; read-character-sequence-as-text-string, but it had -OLD-WAY appended to
;;; its name.  [per MHD, 3/27/92]

(defun read-character-sequence-as-text-string-OLD-WAY (number-of-characters encrypt?)
     ;; This clause is to die out -- it is only for older KBs.
  (let ((gensym-string
	  (read-character-sequence-as-gensym-string-OLD-WAY-1
	    number-of-characters encrypt?)))
    ;; the testing for legal text string was skipped prior to
    ;; now -- otherwise, this is the same as the old way things
    ;; were read.
    (let ((gensym-string-2
	    (if (legal-gensym-string-p gensym-string)
		gensym-string
		(prog1
		    (copy-illegal-gensym-string-without-bad-characters gensym-string)
		  (reclaim-gensym-string gensym-string)))))
      (prog1 (gensym-string-to-wide-string gensym-string-2)
	(reclaim-gensym-string gensym-string-2)))))

;; The following is a textbook example of why structured programing
;; was invented. ML. 3/26/91

;; I believe that the following is true, at least when all the kb flags in this
;; code are true. (ML 4/10/91): The function reads exactly number-of-characters
;; characters with the following exceptions. (1) /{non-simple character}/ may
;; appear internally within the string and is not counted. This is used to
;; effect line breaks as necessary. On some hardware, the break may require two
;; chararacters. (2) If the last character is /, then another slash follows.
;; This second slash must be read and ignored. It is there to avoid ambiguity if
;; the string were to be followed by a newline, which would otherwise invoke the
;; preceeding convention.

(defun read-character-sequence-as-gensym-string-OLD-WAY-1 (number-of-characters encrypt?)
  (loop with gensym-string = (obtain-simple-gensym-string number-of-characters)
	with number-of-unprefixed-escape-characters
	  = 0		   ; useful only when (not (three-escape-characters-p))
	with i = 0
	with character
	while (<f i number-of-characters)
	do

    (case (setq character
		(if encrypt?
		    (char-decrypt (read-char-for-kb) base-reference)
		    (read-char-for-kb)))
      (#\\
       (cond
	 ((or (not (character-sequences-breakable-in-kb-p))
	      (and (eql (setq character
			      (read-next-char-for-kb))
			#\\)
		   (not (three-escape-characters-p))))
	  (incff number-of-unprefixed-escape-characters)
	  (setf (schar gensym-string i) character)
	  (incff i))
	 ((or (not (simple-character-p character))
	      (not (three-escape-characters-p)))
	  (loop until (eql (read-next-char-for-kb)
			   #\\)))
	 (t (setf (schar gensym-string i) #\\)
	    (incff i)
	    (unless (and (=f i number-of-characters)
			 (eql character #\\))
	      (unread-char-for-kb character))))) 
      (t (if (and (eql character #\~)
		  (not (three-escape-characters-p)))
	     (incff number-of-unprefixed-escape-characters))
	 (setf (schar gensym-string i) character)
	 (incff i)))
	finally
	  (return
	    (if (>f number-of-unprefixed-escape-characters 0)
		(loop with new-gensym-string
			= (obtain-simple-gensym-string
			    (+f number-of-characters
				number-of-unprefixed-escape-characters))
		      with j = 0
		      as i from 0 below number-of-characters
		      as character = (schar gensym-string i)
		      do (case character
			   ((#\\ #\~)
			    (setf (schar new-gensym-string j) #\~)
			    (incff j)))
			 (setf (schar new-gensym-string j) character)
			 (incff j)
		      finally
			(reclaim-simple-gensym-string gensym-string)
			(return new-gensym-string))
		gensym-string))))

;; Consider not using a simple text string if number-of-characters is large.

;; Consider using (read-next-char-for-kb) more liberally in the loop, avoiding the
;; next-character-for-kb? logic, for a bit more speed.

;; Consider defining this, properly, as a macro, to gain a bit of speed.





;;;; Reading Integers from KBs



;;; The macro `kb-digit-char-p' returns the digit corresponding the character in
;;; radix 32, provided that character is not uppercase, and falls in the range
;;; of radix 32 digits.  Otherwise, it returns nil.

(defmacro kb-digit-char-p (character)
  (avoiding-variable-capture (&aux character-code)
    ;; Original:
    ;;`(if (not (upper-case-p ,character))
    ;;     (digit-char-p ,character 32))
    ;; Optimized:
    `(let ((,character-code (char-code ,character)))
       (declare (type fixnum ,character-code))
       (cond
	 ((<=f #.(char-code #\0) ,character-code #.(char-code #\9))
	  (-f ,character-code #.(char-code #\0)))
	 ((<=f #.(char-code #\a) ,character-code #.(+ (char-code #\a) (- 32 10)))
	  (+f (-f ,character-code #.(char-code #\a)) 10))))))

;; This optimization is worthwhile for a few reasons.  Digit-char-p is not
;; inlined in Chestnut.  Also, this saves time by not parameterizing radix, and
;; by not handling the uppercase character range.  The code is quite small, too.
;; This is even actually legal Common Lisp, I think. (MHD)





;;; The macro `read-integer-for-kb-if-present' reads from the KB past any spaces
;;; for an integer element or prefix.  If no integer element or integer prefix
;;; is present, it returns nil.  Otherwise it returns an integer.  The integer
;;; is signed if this is an integer element, i.e., if it is followed by #\+
;;; or #\-.  Otherwise, this only returns positive results.
;;;
;;; This leaves the character following the integer in the input, so that the
;;; next call to read-char-for-kb will return it.

;;; Integer results are USUALLY fixnums, but this can theoritically return a
;;; bignum.  Depending on what this is a prefix for (what character ends up as),
;;; a bignum may or may not be a legal situation.  Some of the history of the
;;; development of G2 may also dictate the range of possible values.

;;; Read-integer-for-kb-if-present is a macro internal to read-element-for-kb.

(defun-substitution-macro read-integer-for-kb-if-present ()
  (let* ((character (read-char-for-kb-past-spaces))
	 (weight? (kb-digit-char-p character)))
    (cond
      (weight?
       (read-remainder-of-integer-for-kb 0 weight?))
      (t
       (unread-char-for-kb character)
       nil))))

(defconstant most-positive-fixnum-ash-minus-5-minus-1
  (-f (ashf most-positive-fixnum -5) 1))

(defun-simple read-remainder-of-integer-for-kb (value-so-far weight)
  (declare (type fixnum value-so-far))
  (loop with character
	do (setq value-so-far		; setq's arg
		 (+f (ashf value-so-far 5) weight))
	while (setq weight
		    (kb-digit-char-p
		      (setq character (read-next-char-for-kb))))
	when (not (<=f value-so-far
		       most-positive-fixnum-ash-minus-5-minus-1))
	  return
	    (read-bignum-remainder-of-integer-for-kb
	      value-so-far weight)
	finally
	  (unread-char-for-kb character)
	  (return
	    (cond ((and (char= character #\-) (eq value-so-far 0))
			(setq value-so-far most-negative-fixnum))
		  ((char= character #\-) (-f value-so-far))
		  (t value-so-far)))))


;;; Read-bignum-remainder-of-integer-for-kb continues reading an integer,
;;; potentially reading a bignum.  However, it may also just be called upon
;;; to return a fixnum near the higher ranges of integer length.

(defun read-bignum-remainder-of-integer-for-kb (value-so-far weight)
  (let (character)
    (with-temporary-bignum-creation
      (loop do (setq value-so-far
		     (+ (ash value-so-far 5) weight))
	    while (setq weight
			(kb-digit-char-p
			  (setq character
				(read-next-char-for-kb)))))
      (setq value-so-far
	    (make-permanent-integer
	      (if (char= character #\-)
		  (- value-so-far)
		  value-so-far))))
    (unread-char-for-kb character)
    value-so-far))

;; There's a chance bignum's never were read in successfully: the old code below
;; for reading bignums in 3.0 would always read in a positive bignum as a
;; negative bignum, due to the (case character (#\P value-so-far) (t (-
;; value-so-far))) inside the (case character ((#\+ #\-) ...)) clause.
;;
;; The code below also handled the #\P and #\M cases differently than
;; they're handled for fixnums when in the "new" (3.0) KB save format.
;;
;; The code below is now replaced by 
;;
;; (MHD 10/12/93)
;;
;; 
;;   (defun read-remainder-of-integer-as-bignum (value-so-far weight?)
;;     (with-temporary-bignum-creation
;;       (loop with character
;;   	  do (setq value-so-far (+ (ash value-so-far 5) weight?))
;;   	  while (setq weight?
;;   		      (if (not (upper-case-p
;;   				 (setq character
;;   				       (read-next-char-for-kb))))
;;   			  (digit-char-p character 32)))
;;   	  finally
;;   	    (return
;;   	      (case character
;;   		((#\+ #\-)			; error instead on bignum?
;;   		 (make-permanent-integer
;;   		   (case character
;;   		     (#\P value-so-far)
;;   		     (t (- value-so-far)))))
;;   		((#\P #\M)
;;   		 (finish-reading-slot-value-float
;;   		   value-so-far character t)))))))
;;   


;; Lost comment?
;; 	     ;; As an alternative to reading the significand as a bignum,
;; 	     ;; one could read it as a series of fixnums, converting each
;; 	     ;; to a gensym float and scaling and adding the results
;; 	     ;; appropriately.  This might be more efficient.
;; (MHD 10/12/93)

(defun-simple read-long-for-kb ()
  (with-temporary-bignum-creation
    (let ((integer? (read-element-for-kb nil)))
      (cond ((fixnump integer?)
	     (let ((long-value (coerce-fixnum-to-gensym-long integer?)))
	       (declare (type #.(gensym-long-type) long-value))
	       (allocate-managed-long long-value)))
	    ((gensym-long-p integer?)
	     (allocate-managed-long integer?))
	    ;; In 32-bit G2, the reading result could also be a bignum.
	    ((typep integer? 'bignum)
	     (let ((long-value (coerce-to-gensym-long integer?)))
	       (declare (type #.(gensym-long-type) long-value))
	       (allocate-managed-long long-value)))
	    (t
	     #+development
	     (cerror "continue" "unknown integer type when reading long from KB")
	     (let ((long-value (coerce-fixnum-to-gensym-long 0)))
	       (declare (type #.(gensym-long-type) long-value))
	       (allocate-managed-long long-value)))))))


;; The goal of this function is to read LONG value in KB according to the
;; old format, and then simply return zero. In this way, old KBs containing
;; old LONG value can still be loaded.

(defun-simple read-legacy-long-for-kb ()
  (let* ((s (read-element-for-kb nil))
	 (len (read-element-for-kb nil))
	 (long-value (coerce-fixnum-to-gensym-long 0)))
    (declare (type #.(gensym-long-type) long-value)
	     (type fixnum len)
	     (ignore s))
    (let ((i64 (allocate-managed-long long-value)))
      (loop for i from 0 to len do
	(read-element-for-kb nil))
      i64)))




;;;; Reading KB Files


#+unused
(defvar testing-double-read nil)

;; ML: What's this for? (MHD 10/1/93)


;(defvar index-of-duplicates-and-deletions)



;;; The variable `original-kb-state-plist-written?' is bound around the reading
;;; of KBs.  It gets its value at the end of reading the KB.  Its value is set
;;; to that of the final plist indicator of the same name.  That value is based
;;; on whether there is at least one frame in the KB that was written with an
;;; original KB state plist, i.e., the original-kb-state-plist slot of a frame.
;;;
;;; If this ends up true, then it is necessary to do a call to
;;; undo-kb-state-changes.  That's what it does, but I doubt it ever really
;;; made sense.  What was really wanted, probably, was a call to
;;; undo-kb-state-changes-for-frame for every frame with a state change plist.
;;; What undo-kb-state-changes does is call that function for every element of
;;; kb-state-changes.  I don't see where that list gets built up into anything
;;; like the list of all frames with state changes.  ****FIX!!! (MHD 12/17/93)
;;;
;;; See also the original-kb-state-plist? slot of a kb-save structure, which
;;; records this upon saving of a KB.  See KB-SAVE1.

(defvar original-kb-state-plist-written?)




(defvar backup-case?)
(defvar type-of-file-being-read)

;; Modified read-kb to accommodate the new reclaimable gensym-pathnames.  There
;; are no longer any leaks due to dropped pathnames.  There may be a leak when a
;; symbol for the KB is newly interned.  jh, 1/11/91.

;; The pathname argument for read-kb is assumed always to be a gensym-pathname,
;; even on Lispms.




;;; `Previous-timestamp?' is bound by read-kb and by a saving-context. It is not
;;; bound globally. Its value is initially NIL, and after at least one timestamp
;;; has been read/written, its value is the most recent timestamp read/written
;;; as a gensym time. Its use is to encode timestamps as fixnum size deltas
;;; rather than double floats when possible.

(defvar previous-timestamp?)



;;; `Current-frame-serial-number-before-reading' is bound by read-kb around
;;; its main body to the value of (current-frame-serial-number) before
;;; reading begins.  This means that, while merging, for any frame F
;;;
;;;    (frame-has-been-reprocessed-p
;;;       F current-frame-serial-number-before-reading)
;;;
;;; will be true while reading if and only if F was read in from the KB
;;; being merged, and thus did not exist in the basis KB.

(defvar current-frame-serial-number-before-reading)




(defvar name-of-module-being-read?)

(defvar frame-being-read?)
(defvar slot-description-for-slot-value-being-read?)
(def-system-variable frames-for-rendezvous-in-aggregate-values? kb-load2 nil)

(defvar system-tables-read-for-this-module)


;;; `locked-to-kb?' is set to nil if this is G2, and the user may read any kb
;;; he likes.  If this is an application built with G2 and locked to a
;;; particular kb, this variable should be set to identify the magic cookie
;;; that must be found in the kb in order for it to be loaded.
;;;   Although this is a variable, it should never be changed after ab is
;;; launched.  It should only be set before beginning the launch process,
;;; through an API that will be provided.

(defvar locked-to-kb? nil)



;;; `lock-to-kb' is the API function to set the variable locked-to-kb?.

(defun-simple lock-to-kb (kb-identification)
  (declare (ignore kb-identification)))



;;; Reject-gensym-pathname-to-read is a subfunction of read-kb, and related
;;; functions, which notifies the user that the file corresponding to
;;; gensym-pathname-or-namestring-for-file could not be openned for reading a
;;; KB.  It returns nil.

(defun-allowing-unwind reject-gensym-pathname-to-read
    (gensym-pathname-or-namestring-for-file)
  (protected-let 
    ((namestring-for-file
       (if (text-string-p gensym-pathname-or-namestring-for-file)
	   (copy-text-string gensym-pathname-or-namestring-for-file)
	   (gensym-namestring gensym-pathname-or-namestring-for-file))
       (reclaim-text-string namestring-for-file))
     (namestring-for-user
       (import-text-string
	 namestring-for-file
	 'GENSYM-PATHNAME-NAMESTRING)
       (reclaim-text-string namestring-for-user))
     (error-string-for-user
       ;; previously used copy-string-filtering-out-non-gensym-characters (MHD 3/2/96)
       (import-text-string
	 (g2-stream-error-string)
	 'G2-STREAM-ERROR-STRING)
       (reclaim-text-string error-string-for-user)))
    (notify-user 
      "G2 could not open the file \"~a\":  ~a."
      namestring-for-user error-string-for-user)
    nil))

;; This body of this function used to be part of the body of read-kb.
;; (MHD 7/31/91)




;;; `Read-initial-plist' opens the file at gensym-pathname-to-read, if possible,
;;; and reads its plist, if possible.  If successfule, it returns a plist, a
;;; slot value, which should be reclaimed by the caller using
;;; reclaim-slot-value.  It does not reclaim gensym-pathname-to-read.
;;;
;;; If it fails, it may possible abort or do a non-local exit.  It does, however,
;;; prefer to avoid that, if possible, by simply notify the user of any problems
;;; it encounters, and returning nil.
;;;
;;; This is generally intended to be used for probing a KB file, e.g., to
;;; determine its required modules.
;;;
;;; When this returns the value nil, it may be assumed that
;;; gensym-pathname-to-read is a bad KB, and should not and cannot be loaded.
;;; Note that all valid G2 KBs have non-empty plists.
;;;
;;; While this function tries to avoid non-local exits (aborts or throws), it
;;; may not be successful.  Code that calls this must therefore take appropriate
;;; precautions.

(defun-allowing-unwind simple-kb-read
    (gensym-pathname-to-read operation update-before-loading? not-top-level?)
  #-use-scc (declare (ignore update-before-loading? not-top-level?))
  (let ((message?		  
	  #+use-scc
	  (if (if (eq update-before-loading? 'default)
		  update-before-loading-by-default
		  update-before-loading?)
	      (try-to-get-newest-version-of-file-1 gensym-pathname-to-read nil t)
	      (non-update-kb-check-1 gensym-pathname-to-read (not not-top-level?)))))
    (when message?
      (notify-user-1 (copy-text-string message?)))
    (values
     (handling-gensym-file-errors    
       (g2-stream-with-open-stream
	   (read-kb-stream gensym-pathname-to-read
			   :direction :input
			   :element-type string-char-without-os-newline-translations)
	 (if (null read-kb-stream)
	     (reject-gensym-pathname-to-read gensym-pathname-to-read)
	     (simple-kb-read-1 read-kb-stream gensym-pathname-to-read operation nil))))
     message?)))

(defun-allowing-unwind simple-kb-read-1 (read-kb-stream gensym-pathname-to-read? operation
							xml-object?)
  (protected-let*
      ((truename?
	 (when gensym-pathname-to-read?
	   (gensym-truename gensym-pathname-to-read?))
	 (when truename?
	   (reclaim-gensym-pathname truename?)))
       (namestring-for-kb-being-read
	 (cond (truename?
		(gensym-namestring truename?))
	       (xml-object?
		(tformat-text-string "a xml-object for module ~a"
				     (module-name-string-for-xml-object xml-object?)))
	       (t
		(tformat-text-string "something")))
	 (reclaim-text-string namestring-for-kb-being-read))
       (kb-object-index-space
	 (make-index-space nil nil)
	 (reclaim-index-space kb-object-index-space))
       (name-text-string-for-kb-being-read
	 (copy-text-string	; convert charset here!
	   namestring-for-kb-being-read)
	 (reclaim-text-string name-text-string-for-kb-being-read))
       (new-saved-kb-format-p nil)
       (kb-uses-crlf-p nil)
       (#.(clear-text-kb-format-p-variable) nil)
       
       ;; Variables needed to call KB element reading functions:
       (previous-timestamp? nil)
       (next-character-for-kb? nil)
       (read-kb-buffer-length 0)
       (read-kb-buffer-index 0)
       (base-reference nil))
    (case operation
      (plist
       (when (read-format-identifier-for-kb)
	 (read-initial-plist-for-kb)))
      (get-xml-kb
       (read-top-level-xml-element gensym-pathname-to-read? t))
      (restore-xml-kb
       (let ((name-of-kb-being-read nil)
	     (reformat-as-appropriate? nil) ; or t
	     (auto-merge-case? nil))
	 (continue-read-kb
	   nil nil nil nil
	   reformat-as-appropriate? auto-merge-case? nil xml-object?))))))

(defun-allowing-unwind read-initial-plist (gensym-pathname-to-read
					   update-before-loading? not-top-level?)
  (simple-kb-read gensym-pathname-to-read 'plist update-before-loading? not-top-level?))




;;; `Read-format-identifier-for-kb' reads the first non-whitespace character
;;; from the current KB being read, which is the `format identifier of a KB'. A
;;; proper format identifier must be either J or K (uppercase characters only).
;;;
;;; If this function finds J or K, it returns true.  Also, when it finds J, it
;;; also sets new-saved-kb-format-p to true.  If it fails to find J or K, it
;;; notifies the user that the file is not a KB or lacks a proper KB header, and
;;; returns nil.
;;;
;;; Note that only KBs older than 3.0 should have the K character as their first
;;; non-space character.
;;;
;;; Note that comments may be included in the category "whitespace".  That is
;;; somewhat new for 4.0.  Prior to 4.0, KBs needed to have J or K as the actual
;;; first byte.
;;;
;;; This depends on the KB reading dynamic extent, specifically that which
;;; provides name-text-string-for-kb-being-read, and the set of variables needed
;;; to call KB element reading functions.

(defun read-format-identifier-for-kb ()
  (setq kb-format-identifier-read? nil)
  (let* ((non-empty-file-p
	   (g2-stream-file-non-empty read-kb-stream))
	 (kb-file-comment-string?
	   (if non-empty-file-p
	       (read-comment-string-if-any-for-kb)))
	 (character?
	   (if non-empty-file-p
	       (read-char-for-kb-past-spaces))))
    (cond
      ((eql character? #\J)
       (setq new-saved-kb-format-p t)
       (setq kb-format-identifier-read? t)
       (or kb-file-comment-string? t))
      ((eql character? #\K)
       (setq kb-format-identifier-read? t)
       (or kb-file-comment-string? t))
      ((and #.(enable-loading-clear-text-kbs-p-variable)
	    (null kb-file-comment-string?)
	    (eql character? #\<))
       (setq #.(clear-text-kb-format-p-variable) t)
       (setq kb-format-identifier-read? t)
       ;; Unread the character as it's part of XML tags.
       (unread-char-for-kb character?)
       t)
      (t
       ;; bad KB -- this function must return NIL
       (notify-user	   
	 "File \"~A\" is not a KB or lacks a proper KB header."
	 name-text-string-for-kb-being-read)
       nil))))



;;; `Read-initial-plist-for-kb' is to be called when reading a KB, right after
;;; the format identifier for the KB has been read (see
;;; read-format-identifier-for-kb).  It reads the next KB element, expecting to
;;; find that it is the initial plist for the KB.  It then does some massaging
;;; of the plist, in order to deal with some historical baggage caused by name
;;; changes.
;;;
;;; If kb-file-comment-string? is non-nil, it should be an
;;; unshared text string representing the `source code comment string' for the
;;; KB, as would be read in by read-comment-string-if-any-for-kb, q.v., as part
;;; of read-format-identifier-for-kb, q.v.  If so, this will be incorporated
;;; into the resulting plist with the indicator
;;; KB-FILE-COMMENT-STRING.  This result is in turn intended to be
;;; incorporated into the kb-file-comment slot of saving-parameters,
;;; q.v.  Ultimimately, the intended use of this string is as the comment header
;;; for a source code control system, such as CVS, for file versioning.
;;;
;;; Note: since it is unclear how to specify a character set translation
;;; preference without a KB loaded, we punt, and just import the raw characters.
;;; If only ASCII or Latin-1 text is used, in this day and age the most likely
;;; scenario, then it will appear normal in G2, which uses Unicode, a superset
;;; of ASCII and Latin-1.  Text in other character sets will not be displayed
;;; correctly inside of G2.  However, the intent is mostly to retransmit the
;;; text unharmed in its original form, and this should serve that purpose as
;;; long as the user does not edit it.  If the user tries to edit text that is
;;; not ASCII/Latin-1, then the resulting text will most likely be corrupted,
;;; and probably unusable for the user's intended purpose.  [Better heuristics
;;; could certainly be applied, e.g., use the Locale/code page to determine the
;;; interpretation of the text; while the current release schedule does not
;;; permit such work, we can and should consider adding such smarts in the
;;; future. (MHD 11/12/96)]

(defun read-initial-plist-for-kb
    (&optional kb-file-comment-string?)
  (if (clear-text-kb-format-p)
      (read-initial-plist-for-clear-text-kb)
      (let* ((plist (read-element-for-kb t)))
	(when kb-file-comment-string?
	  (setq plist
		(nconc
		  (slot-value-list
		    'kb-file-comment-string
		    kb-file-comment-string?)
		  plist)))
	(case (getf plist 'type-of-file)
	  (save-kb (setf (getf plist 'type-of-file) 'kb-save))
	  (save-kb-with-runtime-data
	   (setf (getf plist 'type-of-file) 'kb-save-with-runtine-data))) ; See NOTE!
	;; See comment by new-grammar-for-class-specific-attributes-p for
	;; description of this fixup to the initial plist.  -jra 8/15/95
	(when (=f (or (getf plist 'kb-flags)
		      0) ; <= needed for ancient (G2 1.0) KBs (MHD 9/6/96)
		  253)
	  (setf (getf plist 'kb-flags) 252))
	plist)))

;; At one point, it was decided that SAVE-KB should not be seen, but rather,
;; only KB-SAVE.  Similarly for SAVE-KB-WITH-RUNTIME-DATA: it wanted to be
;; KB-SAVE-WITH-RUNTIME-DATA.  However, a misspelling occured when the code
;; above needed to transition in this way was laid down: runtime was misspelled
;; runtine.
;;
;; I and ML know that "runtime" is mispelled "runtine" above!  We plan to deal
;; with it later.  (There are issues, such as what to do with code that hasn't
;; been running because it's N instead of M, that would all of a sudden fire,
;; and such as the fact that old KBs are the way they are. Sigh.  Things have
;; been this way since 3.0 was released more than two years ago. (MHD 4/6/94)

;; Document the format of a KB plist!



;;; `Read-comment-string-if-any-for-kb' reads comments lines as
;;; a string from the current KB, if any, and if returns them
;;; as a text string, with the comment character (;) and at
;;; most one leading space after the comment character

(defun-simple read-comment-string-if-any-for-kb ()
  ;; Should use import purpose kb-kb-file-comment somewhere, as per
  ;; comment elsewhere! (MHD 11/12/96)
  (let ((result
	  (twith-output-to-text-string
	    (loop for character
		      = (read-char-for-kb)
		      then (read-next-char-for-kb)
		  do
	      (cond
		((char= character #\space))
		((char= character #\tab))
		((char= character #\;)
		 (loop for next-character = (read-next-char-for-kb)
		       with started? = nil
		       do (cond
			    ((newline-character-p-macro next-character)
			     (tformat "~%")
			     (update-file-progress-display-for-newline-in-kb)
			     (return))
			    ((and (not started?)
				  (or (char= next-character #\space)
				      (char= next-character #\;)))
			     (when (char= next-character #\space)
			       (setq started? t))
			     nil)
			    (t
			     (setq started? t)
			     (twrite-char
			       (character-to-wide-character
				 next-character))))))
		((newline-character-p-macro character)
		 (update-file-progress-display-for-newline-in-kb))
		(t
		 (unread-char-for-kb character)
		 (return)))))))
    (cond
      ((string=w result '#w"")
       (reclaim-text-string result)
       nil)
      (t
       result))))




(defvar new-compiled-byte-code-body-list nil)
(defvar new-byte-code-body-list nil)

(defun-simple add-new-compiled-byte-code-body (function)
  #-development
  (c-show-function-address function)
  (eval-push function new-compiled-byte-code-body-list))

(defun-simple add-new-byte-code-body (byte-code-body)
  (eval-push byte-code-body new-byte-code-body-list))


;;; `Read-kb' ...

;;; Read-kb returns the `kb name' (the name component of the "truename" of
;;; pathname as an all-uppercase, text string), or nil to indicate failure.

;;; To merge in a bad kb: load it, fix it up, save it, and THEN merge it in.

;;; Read-kb invokes update-representations-of-slot-value for the
;;; frame-status-and-notes slot of each new frame (as well as for the
;;; readout-table-display-value slot of each readout table and for the
;;; representations of variable values) only after it has finished bringing in
;;; the entire saved kb, and, in fact, suppresses all updating of slot value
;;; representations until then.  Representations of slot values can only be
;;; safely updated after the entire saved kb has been brought in, because tables
;;; containing such representations might not until then be present or
;;; sufficiently constructed to allow the updating.

;;; Notifications given by means of notify-user while loading-kb-p is true will
;;; be deferred until after kb reading has been completed (successfully or
;;; unsuccessfully).  (This is not intended to entirely replace calls to error
;;; that alert programmers to errors in their Lisp code.)


;;; During the execution of read-kb, reading-kb-p, which is globally bound by
;;; default to nil, is bound to true.  Also during the execution of read-kb, the
;;; variable kb-load-case? is bound to nil if a KB is being merged and to non-nil
;;; if a new KB is being loaded and the old KB is intended to be cleared.  Note
;;; that this variable is bound during post-loading functions.  Also, note that
;;; it has no global binding; it should only be examined while reading-kb-p is
;;; true.  Finally, loading-kb-p has a global default binding of nil, but is true
;;; only while actually loading the KB file; it is nil during post-loading
;;; functions.

;; Actually reading-kb-p is only bound around continue-read-kb, but should amount
;; to the same thing.

;;; The first character of a KB is K (old format) or J (new format).
;;; New-saved-kb-format-p is set accordingly. In the new format, the plist
;;; following J has the property current-frame-serial-number. It contains a number
;;; larger than the number of any frame that follows. 

;;; In the old format, the kb-object-index-space is used for symbols and for frames.
;;; In the new format, it is used for symbols only.

;;; In the new format, frame-serial-number-map is used to map frame serial numbers
;;; to frames. This is now used the same way in both loading and merging.

;;;  Loading and Merging case:
;;;  Stored frame serial numbers are not preserved. Current-frame-serial-number is
;;;  ignored. Instead, each frame when first encountered as a specification or
;;;  reference is assigned a frame serial number in sequence from the existing KB.
;;;  Either an empty vector, or a frame is created at this time. The vector or frame
;;;  is entered into frame-serial-number-map, but using the frame serial number from
;;;  the stored KB as an index, since this is what is needed for resolving
;;;  references.

;; Because read-kb was too long, n pieces of its straight-line code have been
;; moved into separate functions called read-kb-detail-1, ..., read-kb-detail-n. 

(defun-allowing-unwind read-kb
    (module? gensym-pathname-to-read clear-kb? install-system-tables?
	     reformat-as-appropriate? auto-merge-case? default-kb-directory?)
  (with-backtrace-for-internal-error 'read-kb-internal
    (let ((kb-load-case? (and clear-kb? install-system-tables?)))    
      (setq noting-changes-to-kb-p nil)
      (handling-gensym-file-errors    
	(setq gensym-pathname-to-read		; CHANGES ARG!
	      (or (get-less-case-sensitive-gensym-pathname-if-any
		    gensym-pathname-to-read)
		  gensym-pathname-to-read))    
	(protected-let* ((namestring-for-file
			   (gensym-namestring gensym-pathname-to-read)
			   (reclaim-text-string namestring-for-file))
			 (new-compiled-byte-code-body-list
			   nil
			   (reclaim-eval-list new-compiled-byte-code-body-list))
			 (new-byte-code-body-list
			   nil
			   (reclaim-eval-list new-byte-code-body-list))
			 (loading-compiled-kb-p
			   (when enable-loading-compiled-kbs-p
			     (let ((compiled-file-pathname
				     (pathname->shared-file-pathname gensym-pathname-to-read)))
			       (when (gensym-probe-file compiled-file-pathname)
				 (let ((namestring-as-gensym-string
					 (namestring-as-gensym-string compiled-file-pathname)))
				   (cond
				     #+development
				     (emit-lisp-p
				      (load namestring-as-gensym-string))
				     (t
				      #-development
				      (load-library
					namestring-as-gensym-string
					"initialize_compiled_kb"
					(compiled-kb-initialization-argument))))
				   (reclaim-gensym-string namestring-as-gensym-string)
				   t))))))
	  (g2-stream-with-open-stream
	      (read-kb-stream namestring-for-file
			      :direction :input
			      :element-type string-char-without-os-newline-translations)
	    (if (null read-kb-stream)
		(reject-gensym-pathname-to-read namestring-for-file)
		(protected-let* ((truename
				   (gensym-truename gensym-pathname-to-read)
				   (reclaim-gensym-pathname truename))
				 (name-of-kb-being-read
				   (make-kb-name truename)
				   (reclaim-text-string name-of-kb-being-read))
				 (namestring-for-kb-being-read
				   (gensym-namestring truename)
				   (reclaim-text-string namestring-for-kb-being-read))
				 (name-text-string-for-kb-being-read
				   (copy-text-string ; convert charset here!
				     namestring-for-kb-being-read)
				   (reclaim-text-string name-text-string-for-kb-being-read)))
		  (unless do-not-notify-user-during-kb-load?
		    (notify-user
		      (cond
			((and clear-kb? install-system-tables?)
			 "Loading \"~A\" -- after clearing old KB")
			((and clear-kb? (not install-system-tables?))
			 "Clearing KB and merging in \"~A\"")
			((and (not clear-kb?) install-system-tables?)
			 "Merging \"~A\" into current KB -- and installing its system tables")
			((and (not clear-kb?) (not install-system-tables?))
			 "Merging \"~A\" into current KB"))
		      name-text-string-for-kb-being-read))

		  ;; Since notify-user now forces drawing on the just the
		  ;; logbook, not the entire window, do that here.  This ensures
		  ;; the title block is fully refreshed during the clear-kb.
		  (force-process-drawing)

		  (if clear-kb? (clear-kb t))

		  ;; NOTE: the following line was added in r78731, and it's the only code change
		  ;; for project 'Gensym-676-TAM1-CH-SUCA-JIRA-17737-sys-mod.kb should work after
		  ;; saving and loading from XML format'. It doesn't make sense at all, because
		  ;; the function as a system procedure will be called by an initial rule defined
		  ;; in SYS-MOD.  Let's comment it out.  -- Chun Tian (binghe), Mar 2015.
		  #+ignore (extend-procedure-grammar)

		  (prog1 (continue-read-kb
			   module? read-kb-stream gensym-pathname-to-read
			   install-system-tables? reformat-as-appropriate?
			   auto-merge-case? default-kb-directory? nil)
		    ;; The following two lines were added by r88064 by BVBLogic in July 2011.
		    (setq recompile-on-next-load nil))))))))
    ;; TODO: investigate this line and the function `count-and-fix-invalid-items'. --binghe
    (count-and-fix-invalid-items)))


;; ;;; Foundation-class-list is a variable bound during reading which contains the list
;; ;;; of foundation classes with their daughter user defined classes. It is used to
;; ;;; make repairs to KBs which may be inconsistent because of changes to
;; ;;; preceeding modules.
;; 
;; (defvar foundation-class-list)

;; In the previous version of the software, G2 3.0, this variable was named
;; mother-class-list.  It was renamed as part of a wider renaming of the
;; mother-class concept.  (MHD 4/6/94)

;; I, MHD, cannot see where we ever use this list.  I also do not see any place
;; in the current code where we save this out.  It could be that the code that
;; reads past this is needed for reading some KBs.  I don't know enough to say
;; if it does or doesn't.  It should be looked into.  The variable should
;; at least be done away with even if the reading past is needed!  Check with
;; ML and GHW, and/or check the history by looking grep'ing mother-class in
;; the 3.0 sources.  (MHD 4/6/94)
;;
;; -- UPDATE: The variable has been removed.  We have assured ourselved by
;; inspection of the sources that that cannot hurt.  We're leaving the logic in
;; for now to skip past the @ character as it has always done, but we'll throw
;; away the results rather than putting it into the above variable.  ML has
;; reviewed this move, and thinks it's the right one for 4.0.  (MHD 4/6/94)




;;; `Reading-ghost-definitions-p' is bound to t by read-ghost-definitions and
;;; alters the behavior of read-frame-for-kb and install-class-definition when
;;; these are called within its dynamic extent.  At top-level, its binding is
;;; always nil.  It is never to be set.

(defvar reading-ghost-definitions-p nil)

(defvar class-name-read-while-reading-current-ghost-definition)


;; This should be bound by the caller of continue-read-kb rather than be global,
;; and its value should be set from a file command parse.

(defvar dont-load-if-definitions-have-changed-p nil)




;; forward-referenced-format-frames is a gensym list which is used to deal with
;; a bug introduced for a few weeks in december, 1993, that caused forward
;; referenced to format frames to be written out.  Read-kb binds this to nil.
;; When read-frame-or-connection-reference-for-kb sees a forward reference to a
;; format frame, it sets it to t.  When read-frame-for-kb reads a format frame,
;; if it's t, it won't mark same-named format frames for deletion.  Instead, it
;; will change their name to nil, and allow references to them to continue to
;; exist.  It will also recommend that the KB be reformatted with ", BRINGING
;; FORMATS UP-TO-DATE".

;#+development
(defvar forward-referenced-format-frames) 



(defvar preexisting-frames)
(defvar plist-from-end-element?)
(defun-void note-as-preexisting-frame-if-appropriate (frame)
  (when (and loading-kb-p
	     (frame-of-class-p frame 'block)
	     (null plist-from-end-element?))
    (setf (preexisting-frame-p frame) t)
    (gensym-push frame preexisting-frames)))

;; Use of these is documented where they are referred to, below and around
;; make-frame (FRAMES3).  Document better later! (MHD 7/6/94)




;;; Kb-error ...  Format-control-string and format-args should be arguments
;;; acceptable to tformat.  The resulting text string is exported for purpose
;;; KB-ERROR using export-text-string.  It may not be possible to get all
;;; non-ascii characters through to the user, either in G2/TW or on the console.
;;;
;;; At present, this does a non-local exit by signalling a fatal (Lisp) error,
;;; and users should be prepared for that behavior.  However, some day, this
;;; might be recoded to do a non-local exit via abort, which just throws to
;;; top-level but allows the program to proceed.  (That was the behavior in 2.1
;;; and early, pre-alpha versions of 3.0.  -mhd, 12/3/91)

(defmacro kb-error (format-control-string &rest format-args)  
  `(let* ((text-string (tformat-text-string ,format-control-string . ,format-args))
	  (error-message-as-text-string
	    (export-text-string text-string 'kb-error))
	  (error-message-as-gensym-string
	    (wide-string-to-string error-message-as-text-string)))
     (error "~a" error-message-as-gensym-string)
     ;; Result becomes garbage:  -- ok in this exceptional situation
     ))




(defvar collecting-warnings-p nil)
(defvar collected-items-with-warnings-alist nil)

(defun collect-warning (item message-type)
  (let ((a (assq message-type collected-items-with-warnings-alist)))
    (unless a
      (setq a (gensym-cons message-type nil))
      (gensym-push a collected-items-with-warnings-alist))
    (gensym-push item (cdr a))))

(defun reclaim-collected-warnings (alist)
  (loop for l in alist do (reclaim-gensym-list l))
  (reclaim-gensym-list alist))

(defmacro with-collected-warnings (args &body body)
  (declare (ignore args))
  `(let ((collecting-warnings-p t)
	 (collected-items-with-warnings-alist nil))
     (prog1 (progn ,@body)
       (setq collecting-warnings-p nil)
       (post-collected-warnings collected-items-with-warnings-alist)
       (reclaim-collected-warnings collected-items-with-warnings-alist))))


;; Consider notifying the user in G2 first, which would allow all characters to
;; get through, and later sending it through to ERROR, which can't handle all
;; non-ASCII characters!  (MHD 4/24/96)

;; Note: this has just been created to replace calls to notify-user followed
;; by abort in the following two function.  Note that there are still calls
;; to notify-user followed by abort, but they were determined to happen early
;; enough in the load process (i.e., before the variable TIMESTAMP? is receives
;; to a non-nil binding) that a fatal error need not be signalled.
;;
;; Note that the unwind-protect part of read-kb may also signal a fatal error if
;; it is thrown past, e.g., by abort, before reading has succeeded.  But
;; signalling the error here may be much friendlier because an informative error
;; message may be provided. (MHD 12/3/91)


;;; The constant `earliest-version-to-allow-kb-loading' has been established on
;;; Mar. 29, 2004, for the major release pending (8.0a1), with value
;;; corresponding to G2 5.1r0.  For the upcoming release, users will be advised
;;; that 5.1r0 is the earliest version we support going back to when loading a
;;; KB, and it will not work to load back more than that many versions.
;;;
;;; Note that previously, that is, since 6.0, users had been advised that 2
;;; major versions back are supported, and there was a different variable used,
;;; number-of-major-versions-back-to-allow-kb-loading.  So now we're going to a
;;; more flexible scheme, allowing us to support a fewer or greater number of
;;; releases back to support depending on the current situation.
;;;
;;; Though we're being more flexible now, in general the goal and the policy
;;; understood by our users is that we strive to support at least 2 major
;;; versions back.
;;;
;;; This is a constant, and should normally never be changed to imply support of
;;; an earlier release, both because of the impact on the installed base, and
;;; because code to support versions of KBs earlier than the earliest version is
;;; subject to deletion at any time now.

(defconstant earliest-version-to-allow-kb-loading
  (make-system-version 5 10 :quality release-quality :revision 0)) ; 5.1r0


;;; `System-version-major-difference' returns the result of subtracting the
;;; major version of system-version-2 from the major version of
;;; system-version-1.

(defun system-version-major-difference (system-version-1 system-version-2)
  (-f (first system-version-1) (first system-version-2)))

;; Maybe move to BOOTSTRAP. (MHD 9/22/99)

(defvar automatically-resolve-conflicts-by-default t) ; continue-read-kb
(defvar update-before-loading-by-default t) ; simple-kb-read

(defvar definitions-read-in-this-module)

(defun-allowing-unwind continue-read-kb
    (module? read-kb-stream gensym-pathname-to-read main-kb-being-read?
	     reformat-as-appropriate? auto-merge-case?
	     default-kb-directory? xml-object?)
  (let* ((reading-kb-p t)
	 (reading-succeeded? nil)
	 (definitions-read-in-this-module nil)
	 ;; jh, 7/2/91.  Need the following three variables for the
	 ;; system time comparison.  Note the cons-hiding.
	 (discrepancy-with-system-time1-p 
	   (path-list nil nil))
	 (discrepancy-with-system-time2-p 
	   (path-cons nil (cdr discrepancy-with-system-time1-p)))
	 (separate-imminent-actions-p nil)
	 
	 (defer-notifications? nil)

					;#+development
	 (forward-referenced-format-frames nil)

	 (record-class-name-conflicts?
	   (if (eq auto-merge-case? 'default)
	       automatically-resolve-conflicts-by-default
	       auto-merge-case?))
	 kb-state-changes-for-module-being-read?
	 kb-object-index-space
	 plist-from-initial-element?	; why the "?"?  history? (MHD 4/6/94)
	 (name-of-module-being-read? nil)
	 system-version?
	 flag-in-kb-is-higher-than-g2-kb-flag?
	 (timestamp? nil)
	 (kb-file-progress		; add "?"
	   (if kb-file-progress-is-currently-for-modules-p
	       current-kb-file-progress-for-modules?
	       nil))
	 (class-name-conflicts nil)
	 (blocks-to-delete-after-reading-kb nil)
	 (connections-to-delete-after-reading-kb nil)
	 (blocks-with-bad-connections nil) ; -fmw, 12/23/01
	 (refresh-all-windows-after-merging? nil)
	 (new-saved-kb-format-p nil)
	 (kb-uses-crlf-p nil)
	 
	 (#.(clear-text-kb-format-p-variable) nil)
	 original-kb-state-plist-written?
	 (previous-timestamp? nil)
	 (file-length?
	   (unless xml-object?
	     (g2-stream-file-length read-kb-stream)))
	 
	 local-kb-flags-from-last-kb-read
	 local-system-version-from-last-kb-read
	 frame-serial-number-map
	 ;; foundation-class-list ; obsolete (MHD 4/6/94)

	 (blocks-to-activate-unless-reset nil) ; gensym cons list
	 (frame-serial-number-for-blocks-to-activate nil)

	 (do-not-note-permanent-changes-p t)
	 
	 value-of-read-kb
	 (.unwind-abort. t))

    (setq defer-notifications? t)
    (reclaim-items-deleted-since-load-or-save)
    (let ((current-frame-serial-number-before-reading
	    (copy-frame-serial-number (current-frame-serial-number))))
      (unwind-protect
	   (let* ((loading-kb-p t)
		  (suppress-updating-of-slot-value-representations? t)
					; abort possibility precludes
					; reset
		  system-version-from-kb-being-read
		  system-quality-from-last-kb-read
		  system-revision-from-last-kb-read
		  (kb-flags kb-flags)	; not great, but may need to be bound 
					;   appropriately while reading plist
					;   -- used to be bound to nil here!
					;   (MHD 9/13/90)
		  (deferred-class-definitions-alist nil)
		  (frames-with-substitute-classes nil)
		  (number-of-kb-lines-so-far 0)
		  (number-of-kb-characters-so-far? nil)	; set to 0 below if counting
		  (next-character-for-kb? nil)
		  (read-kb-buffer-length 0)
		  (read-kb-buffer-index 0)
		  (plist-from-end-element? nil)
		  (preexisting-frames nil)
		  base-reference
		  (type-of-file-being-read nil)
		  (backup-case? nil)	       
		  (system-tables-read-for-this-module nil)
		  (comment-string-or-t? nil))
	     
	     (setq kb-object-index-space (make-index-space nil nil))

	     (unless (or xml-object? ; should already have been checked
			 (setq comment-string-or-t?
			       (read-format-identifier-for-kb)))
	       (abort-on-bad-kb))

	     (unless (text-string-p comment-string-or-t?)
	       (setq comment-string-or-t? nil))

	     (setq plist-from-initial-element?
		   (cond (xml-object?
			  nil)
			 ((clear-text-kb-format-p)
			  (when module?
			    (prog1 (initial-plist-for-loaded-module module?)
			      (setf (initial-plist-for-loaded-module module?) nil))))
			 (t
			  (read-initial-plist-for-kb comment-string-or-t?))))
	     
	     (setq type-of-file-being-read
		   (getf plist-from-initial-element? 'type-of-file))

	     (prepare-to-read-snapshot-if-appropriate
	       plist-from-initial-element?)

	     (prepare-to-read-backup-if-appropriate
	       plist-from-initial-element?)

	     (when (or system-has-paused system-is-running)
	       (reclaim-all-indexed-attribute-hash-tables))
	     
	     ;; For new kb-format, make the frame-serial-number map. If
	     ;; load case, deal with the few frames that exist at
	     ;; the start of the save. If a backup, enter old frames into
	     ;; map. In all cases (except 2.1 and older KBs) enter
	     ;; encryption mode by setting base-reference. 
	     (read-kb-detail-2 plist-from-initial-element?)
	     
	     (setq system-version?
		   (getf plist-from-initial-element? 'system-version))
	     (setq system-version-from-kb-being-read
		   (if (and system-version? (not (eql system-version? 0)))
		       system-version?
		       '#.(make-system-version 0 8)))	; older than 23 Oct 87!
	     (multiple-value-setq
		 (system-quality-from-last-kb-read system-revision-from-last-kb-read)
	       (get-quality-and-revision-of-system-version system-version-from-kb-being-read))

	     (setq local-system-version-from-last-kb-read
		   (copy-for-slot-value
		     system-version-from-kb-being-read))

	     (unless (or xml-object? (clear-text-kb-format-p))
	       (setq kb-flags
		     (or (getf plist-from-initial-element? 'kb-flags) 0))

	       (normalize-kb (new-tampering-algorithm-p))

	       (setq flag-in-kb-is-higher-than-g2-kb-flag?
		     (unless ignore-kb-flags-in-kbs?
		       (>f kb-flags kb-flags-of-software))))

	     (setq name-of-module-being-read?
		   (getf plist-from-initial-element? 'top-level-module))

	     (when name-of-module-being-read?
	       (setf (module-is-writable-p name-of-module-being-read?) 'unknown))
	     
	     (cond
	       ((and (not flag-in-kb-is-higher-than-g2-kb-flag?)
		     (or xml-object? (clear-text-kb-format-p)
			 (and (setq timestamp?		; a simple verification
				    (getf plist-from-initial-element? 'timestamp))
			      (not (system-version-greater-p
				     earliest-version-to-allow-kb-loading
				     local-system-version-from-last-kb-read)))))
		(cond
		  ((null kb-file-progress)
		   (setq kb-file-progress
			 (put-up-file-progress-display
			   t file-length?
			   (copy-text-string name-text-string-for-kb-being-read)
			   nil nil nil nil name-of-module-being-read?))
		   (when kb-file-progress-is-currently-for-modules-p
		     (setq current-kb-file-progress-for-modules?
			   kb-file-progress)))
		  (t
		   (put-up-file-progress-display
		     t file-length?
		     (copy-text-string name-text-string-for-kb-being-read)
		     nil nil nil kb-file-progress name-of-module-being-read?)))
		(if (length-of-file-in-characters? kb-file-progress)
		    (setq number-of-kb-characters-so-far? 0))	; => counting

		(setq local-kb-flags-from-last-kb-read kb-flags)
		
		;; Prior to 4.0, spaces could not appear before the *'s; I
		;; made them be allowed. (MHD 10/4/93)
		(unless (or xml-object? (clear-text-kb-format-p))
		  (let ((char (read-char-for-kb-past-spaces)))
		    (cond
		      ((not (char= char #\*))
		       (unread-char-for-kb char))
		      (t (setq char (read-char-for-kb))
			 (when (not (or (char= char #\1)
					(char= char #\3)))
			   ;; used *3/*4 instead of *1/*2 for a time
			   ;; in 4.0 development.  Only #\1 needs
			   ;; to remain here. (MHD 12/17/93)
			   (abort-on-bad-kb char))
			 (read-ghost-definitions)
			 (when (and dont-load-if-definitions-have-changed-p
				    class-name-conflicts)
			   (terminate-load-when-definitions-have-changed))))))

		;; If dont-load-if-definitions-have-changed-p and there are
		;; conflicts from the ghost definitions, then safe to
		;; abort-on-bad-kb. Nothing has been installed.
		
		;; Top level elements are frames, and connections.
		(cond (xml-object?
		       (setq some-module-is-clear-text-p t)
		       (setq reading-succeeded?
			     (read-clear-text-module-from-xml-object xml-object? auto-merge-case?)))
		      ((clear-text-kb-format-p)
		       (setq some-module-is-clear-text-p t)
		       (setq reading-succeeded?
			     (read-clear-text-module gensym-pathname-to-read auto-merge-case?)))
		      (t
		       (read-all-top-level-kb-elements)

		       ;; Set up modules-and-system-tables-a-list based on the
		       ;; (installed) set of system tables saved out with this KB.
		       (set-up-modules-and-system-tables-a-list-after-reading)))
		
		;; Above loop terminates because value for reading #\E is NIL.
		(unless (or xml-object? (clear-text-kb-format-p))
		  (setq plist-from-end-element? (read-element-for-kb t))
		  (update-file-progress-display-for-newline-in-kb t))

		(when name-of-module-being-read?
		  (note-crlf-use-in-module-or-file
		    name-of-module-being-read?
		    kb-uses-crlf-p))

		;; A G2 authorized as development or restricted-use will be made
		;; runtime only if runtime data saved from a runtime system was
		;; loaded into it.  If this is the case, it gets reverted upon
		;; reset. 
		#+pre-g2-v5-licensing
		(when (and warmbooting?
			   (not (or xml-object? (clear-text-kb-format-p)))
			   (reclaim-rest-of-index-count plist-from-end-element?))
		  (temporarily-make-runtime-only))
		(setq original-kb-state-plist-written?
		      (getf plist-from-end-element?
			    'original-kb-state-plist-written?))
		(if deferred-class-definitions-alist
		    (install-deferred-class-definitions))

		;; Frames that were present before the KB was read are marked
		;; block-has-been-referenced.If the frame has not been deleted, it
		;; will still be marked and in use. These frames should be given
		;; new frame serial numbers higher than any in use.
		;; Is it possible that any of these frames had references to
		;; their frame serial numbers?
		(loop for frame in preexisting-frames
		      when (and (preexisting-frame-p frame)
				(frame-in-use-p frame))
			;; i.e., this has not been deleted or recycled
			do (frame-serial-number-setf (frame-serial-number frame)
						     (increment-current-frame-serial-number))
			   (clear-preexisting-frame frame)
			   (cond ((eq frame current-logbook?)
				  (frame-serial-number-setf current-logbook-serial-number?
							    (frame-serial-number frame)))))
		(reclaim-gensym-list preexisting-frames)
		#+development
		(if (loop with reference-serial-number =
			  (current-frame-serial-number)
			  for block being each class-instance of 'block
			  thereis
			  (frame-has-been-reprocessed-p
			    block reference-serial-number))
		    (cerror "You may continue"
			    "Notify ML of frame serial number problem."))
		
		(cond
		  ((and (or xml-object? (clear-text-kb-format-p))
			(not reading-succeeded?))) ; user already notified
		  ((not (or (or xml-object? (clear-text-kb-format-p))
			    (= (read-element-for-kb t)	; assume fixnum?
			       (+ (last-assigned-index kb-object-index-space)
				  1))))
		   (notify-user
		     "Invalid KB.  File contents are internally inconsistent."))
		  ;; verify further!?
		  (t (setq loading-kb-p nil)
		     (setq suppress-updating-of-slot-value-representations? nil)
		     (loop for frame in frames-with-substitute-classes	; delete?
			   do (funcall-method-if-any
				'fix-frame-with-substitute-class frame)
			   finally
			     (reclaim-gensym-list frames-with-substitute-classes)
			     (setq frames-with-substitute-classes nil))
		     

		     ;; (1) Note (current-frame-serial-number) before calling delete-blocks-
		     ;;     and-connections-to-be-deleted-now.
		     ;; (2) Iterate over all kb-frame instances just read in and call each 
		     ;;     one's initialize-after-reading method, if any.
		     
		     (let ((frame-serial-number-before-deleting (copy-frame-serial-number (current-frame-serial-number)))
			   (collect-kb-state-changes-for-module?
			     (and original-kb-state-plist-written?
				  (not warmbooting?))))

		       (setq frame-serial-number-for-blocks-to-activate
			     (copy-frame-serial-number frame-serial-number-before-deleting))

		       
		       (delete-blocks-and-connections-to-be-deleted-after-reading)
		       (update-file-progress-display-after-reading
			 kb-file-progress 'reinitialize)
		       (with-collected-warnings ()
			 (if new-saved-kb-format-p
			     (loop with do-not-note-permanent-changes-p = t
				   for kb-object being each sparse-array-value
				   of frame-serial-number-map
				   when (and (framep kb-object)
					     ;; all frames in this map have fsn's,
					     ;; i.e., are blocks
					     (frame-has-not-been-reprocessed-p
					       kb-object frame-serial-number-before-deleting))
				     do (when (block-needs-activation-upon-reading-p kb-object)
					  (gensym-push kb-object blocks-to-activate-unless-reset))
					(funcall-method 'initialize-after-reading kb-object)
					(when (and collect-kb-state-changes-for-module?
						   (original-kb-state-plist kb-object))
					  (gensym-push
					    kb-object kb-state-changes-for-module-being-read?)))
			     
			     (loop with do-not-note-permanent-changes-p = t
				   for i from 0
					 to (last-assigned-index kb-object-index-space)
				   as kb-object
				      = (get-object-from-index-space kb-object-index-space i)
				   when (and (framep kb-object)
					     ;; only blocks have fsn's, but all frames are
					     ;; kept in kb-object-index-space
					     (frame-of-class-p kb-object 'block)
					     (frame-has-not-been-reprocessed-p
					       kb-object frame-serial-number-before-deleting))
				     do (when (block-needs-activation-upon-reading-p kb-object)
					  (gensym-push kb-object blocks-to-activate-unless-reset))
					(funcall-method 'initialize-after-reading kb-object)
					(when (and collect-kb-state-changes-for-module?
						   (original-kb-state-plist kb-object))
					  (gensym-push
					    kb-object kb-state-changes-for-module-being-read?)))))
		       (reclaim-frame-serial-number frame-serial-number-before-deleting))
		     
		     (update-file-progress-display-after-reading
		       kb-file-progress 'reformat)
		     (reformat-as-appropriate-if-necessary)
		     
		     (setq reading-succeeded? t)
		     
		     ;; jh, 11/4/91.  Added license-has-expiration-date-p as partial
		     ;; fix of the refusal of the mechanism to load into a UNIX G2, a
		     ;; KB timestamped and saved from a VMS G2.
		     (when (and (not (or xml-object? (clear-text-kb-format-p)))
				(system-time-is-earlier-than-kb-timestamp)
				(license-has-expiration-date-p g2))
		       (setf (cadr discrepancy-with-system-time2-p) t))
		     (unless xml-object?
		       (when main-kb-being-read?	; had been: (null main-kb-exists-p) -mhd
			 (store-current-pathname current-kb-pathname? gensym-pathname-to-read)
			 (add-recent-loaded-kb current-kb-pathname?)))
		     (let ((complete-name-from-kb?
			     (getf plist-from-initial-element? 'kb-name)))
		       (make-or-clear-complete-kb-name
			 (if (and main-kb-being-read?
				  reading-succeeded?
				  (text-string-p complete-name-from-kb?))
			     complete-name-from-kb?
			     nil)
			 t
			 nil
			 (copy-for-slot-value ; OK if nil
			   (getf plist-from-initial-element?
				 'kb-file-comment-string)))
		       (when complete-name-from-kb?
			 (if (text-string-p complete-name-from-kb?)
			     (reclaim-text-string complete-name-from-kb?))
			 (setf (getf plist-from-initial-element? 'kb-name) nil)))
		     (unless xml-object?
		       (set-gensym-pathname-for-module name-of-module-being-read? gensym-pathname-to-read)
		       (set-default-pathname-for-module name-of-module-being-read? default-kb-directory?)
		       (setf (module-is-writable-p name-of-module-being-read?) 'unknown)
		       (set-reason-module-is-not-editable name-of-module-being-read? 'unknown))
		     (unless (second discrepancy-with-system-time2-p)
		       (unless do-not-notify-user-during-kb-load?
			 (notify-user
			   (if kb-load-case? "Done loading \"~A\"~A" "Done merging \"~A\"")
			   name-text-string-for-kb-being-read
			   (if kb-load-case?
			       " -- and clearing old KB"
			       ""))))			; used to say "releasing", but this is
					;  just like "Clear KB", the command
					;  (MHD 7/31/91)
					; Add things like facts about whether 
					; installing system tables, auto
					; merging, etc.?! (MHD 8/26/91)
		     (when loading-compiled-kb-p
		       (loop for compiled-function in new-compiled-byte-code-body-list
			     for byte-code-body in new-byte-code-body-list
			     do (install-compiled-byte-code-body
				  byte-code-body compiled-function)))
		     (when class-name-conflicts
		       (update-file-progress-display-after-reading
			 kb-file-progress 'automerge)
		       (deal-with-class-name-conflicts
			 auto-merge-case?
			 (let ((kb-flags local-kb-flags-from-last-kb-read))
			   (new-tampering-algorithm-p))))

		     ;; This is the second time this is called. We are not sure as
		     ;; to what order dependencies would be a problem if
		     ;; deal-with-class-name-conflicts were moved to an earlier location.
		     (delete-blocks-and-connections-to-be-deleted-after-reading)
		     ;; Also put up a conflict report workspace to list names that
		     ;; became ambiguous because of the merge!!!

		     (unless do-not-restore-image-planes?
		       (restore-image-planes-to-pane-now-or-later
			 (getf plist-from-end-element? 'detail-pane-description)
			 ;; if installing new logbook params => redisplay logbook:
			 main-kb-being-read?
			 ;; if reading a module, restore now only for that module:
			 name-of-module-being-read?))
		     
		     (loop for symbol in (getf plist-from-end-element? 'numeric-symbols)
			   do (setf (type-of-syntactic-anomaly symbol) 'numeric))
		     (reclaim-slot-value plist-from-end-element?)
		     ;; provides read-kb's value:
		     (setq value-of-read-kb
			   (if reading-succeeded? name-of-kb-being-read))))))
	     #+pre-g2-v5-licensing
	     (when (and (runtime-option-is-temporary-p)
			(eq type-of-file-being-read 'kb-save-with-runtime-data))		 
	       (notify-user "You have just loaded a snapshot that was made by a G2 ~
authorized for runtime use only into this G2 which is authorized as either ~
development or restricted use. This G2 is now a runtime system, and will remain ~
so until it has been reset or shut down."))
	     (when system-tables-read-for-this-module
	       (reclaim-slot-value-list system-tables-read-for-this-module)
	       (setq system-tables-read-for-this-module nil))
	     (setf .unwind-abort. nil)
	     ;; end protected-form
	     )
	
	;; Makes class membership test work for user defined classes
	;; read in.
	(if (null reading-succeeded?)
	    (make-or-clear-complete-kb-name nil nil))
	(reclaim-items-deleted-since-load-or-save)
	(reclaim-slot-value plist-from-initial-element?)



	;; NEW: (MHD/ML 10/22/92)
	;; The mark first-definition-mark is used in the kb loading
	;; context exclusively to mark ghost definitions.  It must remain
	;; clear at all other times.  (It is also used in a limited
	;; context while saving, which also leaves it cleared.)
	;; (MHD/ML 10/22/92)
	(loop for definition being each class-instance of 'class-definition
	      do (clear-first-definition-mark definition))

	;; Reclaim map(s) of all symbols and kb objects just read in.

	(if new-saved-kb-format-p
	    (reclaim-frame-serial-number-map))
	(reclaim-index-space kb-object-index-space)
	
					;#+development
	(reclaim-gensym-list forward-referenced-format-frames)
	
	
	
	
;      (when index-of-duplicates-and-deletions
;	(reclaim-frame-serial-number-tree
;	  index-of-duplicates-and-deletions)
;	(setq index-of-duplicates-and-deletions nil))
	
	(cond
	  ((null reading-succeeded?)		; if read-kb has failed
	   
	   (cond
	     ((or xml-object? (clear-text-kb-format-p)))
	     ((null timestamp?)
	      ;; for simple non-KB file and backward incompatibility cases:
	      (notify-user
		(if flag-in-kb-is-higher-than-g2-kb-flag?
		    "\"~A\" cannot be loaded because it was created ~
                    with a newer version of G2 than this one"
		    "File \"~A\" is not a KB or lacks a proper KB header")
		name-text-string-for-kb-being-read))
	     ((system-version-greater-p
		earliest-version-to-allow-kb-loading
		local-system-version-from-last-kb-read)
	      (let ((text-string
		      (twith-output-to-text-string
			(tformat
			  "\"~A\" cannot be loaded because it was saved in G2 "
			  name-text-string-for-kb-being-read)
			(twrite-system-version local-system-version-from-last-kb-read t)
			(tformat ". The KB must be saved in G2 ")
			(twrite-system-version earliest-version-to-allow-kb-loading t)
			(tformat " or later in order to be loaded in this version of G2 (")
			(twrite-system-version system-version-of-current-gensym-product-line t)
			(tformat ")."))))
		(notify-user "~a" text-string)
		(reclaim-text-string text-string)))
	     
	     (t
	      
	      
	      ;; Reading has failed -- can't continue! 
	      ;; The idea behind putting the call to error here is that
	      ;; read-kb has "evolved" to the point where it is hopeless
	      ;; to try to recover, at least by proceeding past here.
	      ;; A considerable amount of work would now be needed to
	      ;; make recovery safe at this point.  So, in consultation
	      ;; with DWR, ML, and BAH, I've put in the hard error.
	      ;; (MHD 10/24/91)
	      (if top-level-error-seen
		  (notify-user-at-console "READING HAS FAILED -- UNABLE TO PROCEED!")
		  (error "READING HAS FAILED -- UNABLE TO PROCEED!"))

	      ;; This is code that presumably could never be reached, but it
	      ;; predates the (fatal) error code above, and if we remove that relatively
	      ;; newer code, this should be here.  (However, it should not apply
	      ;; for any reason I know in the earlier cond clause; it used to, and
	      ;; that it has been moved to this cond clause as the resolution to
	      ;; bug HQ-1138940.) (MHD 5/12/97)
	      (unless top-level-error-seen
		(clear-kb)
		(change-all-permanently-changed-things-are-marked nil)))))
	  (t (let* ((kb-flags-from-last-kb-read
		      local-kb-flags-from-last-kb-read)
		    (system-version-from-last-kb-read
		      local-system-version-from-last-kb-read))
	       (unless (or xml-object? (clear-text-kb-format-p))
		 (let ((kb-flags kb-flags-from-last-kb-read))
		   (check-for-tampered-kb	    
		     (kb-security-implemented-p)
		     (new-tampering-algorithm-p))))
	       
	       (let ((frame-reference-serial-number
		       (copy-frame-serial-number (current-frame-serial-number))))
		 ;; Auto-merge happens now -- this must come AFTER
		 ;; check-for-tampered-kb because we assume in it that workspace
		 ;; tampering has already been check when we call
		 ;; resolve-class-name-conflicts; this must happen BEFORE the
		 ;; function fix-unimplemented-definitions because if we're
		 ;; doing automerge, then ghost definitions read in will be
		 ;; wacko-definition-p until after resolve-class-name-conflicts
		 ;; is run; see fix-unimplemented-definitions.  (MHD 4/20/92)
		 ;; It also must happen BEFORE
		 ;; delete-type-violating-relation-instances, since
		 ;; otherwise, this will perform spurious deletion
		 ;; of relations due to temporary class mismatches
		 ;; that would be fixed by the conflict resolution.
		 ;; -alatto, 5/22/03
		 
		 (update-file-progress-display-after-reading
		   kb-file-progress 'post-load)

		 (do-post-loading-functions :before-conflict-resolution)

		 (update-file-progress-display-after-reading
		   kb-file-progress 'automerge2)
		 
		 (when auto-merge-case?
		   (resolve-class-name-conflicts)
		   (resolve-definitional-name-conflicts))

		 (update-file-progress-display-after-reading
		   kb-file-progress 'post-load2)

		 (do-post-loading-functions :after-conflict-resolution)

		 (update-file-progress-display-after-reading
		   kb-file-progress 'revert)
		 (loop for frame in kb-state-changes-for-module-being-read?
		       do
		   ;; Resolve-one-class-name-conflict may have deleted the ghost-
		   ;; definition after a successful merge.
		   (unless (frame-has-been-reprocessed-p
			     frame frame-reference-serial-number)
		     (undo-kb-state-changes-for-frame frame)
		     (remove-as-frame-with-kb-state-changes frame))
		       finally (reclaim-gensym-list
				 kb-state-changes-for-module-being-read?))
		 (update-file-progress-display-after-reading
		   kb-file-progress 'finished)	       
		 (reclaim-frame-serial-number frame-reference-serial-number)))))
	(progn
	  (unless kb-file-progress-is-currently-for-modules-p
	    (note-update-to-file-progress kb-file-progress 'delete)
	    (delete-frame kb-file-progress))
	  (delete-all-title-block-workspaces))
	
	(unless top-level-error-seen
	  (reclaim-slot-value local-system-version-from-last-kb-read)
	  (if refresh-all-windows-after-merging?	; note: only really nec. if merging, 
					;   but now no way to tell!
	      ;; need to update kb-listeners in TWII
	      (loop for workstation in workstations-in-service
		    do (refresh-window (window-for-workstation workstation))))
	  (change-all-permanently-changed-things-are-marked
	    (if kb-load-case? t nil))
	  
	  (setq defer-notifications? nil)
	  (try-to-do-deferred-user-notifications))
	(reclaim-frame-serial-number current-frame-serial-number-before-reading)
	(when .unwind-abort.
	  (reclaim-frame-serial-number (prog1 frame-serial-number-for-blocks-to-activate
					 (setf frame-serial-number-for-blocks-to-activate nil))))
	))	; end unwind-protect
    (path-pop discrepancy-with-system-time2-p)
    (when (and (not (or xml-object? (clear-text-kb-format-p)))
	       (do-kb-timestamp-load-check-p)
	       (cadr discrepancy-with-system-time1-p))
      (clear-kb)
      (notify-user
	(refuse-load-at-discrepancy-with-system-clock-message)
	name-text-string-for-kb-being-read))
    (reclaim-path-list discrepancy-with-system-time1-p)
    
    (when (or system-is-running system-has-paused)
      (make-all-indexed-attribute-hash-tables)
      ;; Add the entries to the indexed-attribute tables for
      ;; each active item that has indexed-attributes.  This will
      ;; exclude the newly read-in items which activate-roots-of-kb-
      ;; hierarchy-just-read-in will take care of.  (ghw 6/8/97)
      (loop for block being each class-instance of 'block
	    when (and (has-indexed-attributes-p block)
		      (active-p block))
	      do (put-parent-for-its-indexed-attributes block t))
      (activate-roots-of-kb-hierarchy-just-read-in
	blocks-to-activate-unless-reset
	frame-serial-number-for-blocks-to-activate)
      )

    (reclaim-gensym-list blocks-to-activate-unless-reset)
    (reclaim-frame-serial-number (prog1 frame-serial-number-for-blocks-to-activate
				   (setf frame-serial-number-for-blocks-to-activate nil)))
    
    #+development
    (when (or connections-to-delete-after-reading-kb
	      blocks-to-delete-after-reading-kb)
      (cerror "continue" "Things to be deleted after last call to delete them."))

    value-of-read-kb))




;;; `Block-needs-activation-upon-reading-p' is true of a block that is at one of
;;; the roots of the KB hierarchy, and therefore needs to be activated.
;;;
;;; In particular, this selects
;;;
;;;  (1) top-level kb workspaces;
;;;  (2) definitions that are not on any workspace; and
;;;  (3) system tables not on any window
;;;
;;; Note [as of 5.0 post Beta Rev. 0 (MHD 2/26/97)]: defaulted system tables,
;;; i.e., those that are not saved out because their slots have all default
;;; values, get created and activated separately; see code for this in
;;; add-newer-system-tables-to-suite-if-necessary.

(defun-simple block-needs-activation-upon-reading-p (block)
  (frame-class-case block
    (kb-workspace (null (parent-of-subworkspace? block)))
    ((definition system-table) (null (superblock? block)))))


(defun-void activate-roots-of-kb-hierarchy-just-read-in
    (blocks reference-serial-number)
  (loop for block in blocks
	unless (frame-has-been-reprocessed-p block reference-serial-number)
	  do (funcall-method 'activate-if-possible-and-propagate block)))




;;; `Read-all-top-level-kb-elements' reads in all of the top level elements of
;;; the KB.  

(defun read-all-top-level-kb-elements ()
  (loop while (read-element-for-kb t)))



(defun terminate-load-when-definitions-have-changed ()
  ;; Generate a report about the problems!!!
  (abort))



;;; `prepare-to-read-snapshot-if-appropriate' is called after the reading of
;;; the initial plist.  If the special variable warmbooting? is true, and if the
;;; appropriate elements are present in the plist, this sets various specials
;;; involved in the warmbooting process based on corresponding entries in
;;; initial-kb-plist, as follows:
;;;
;;;    (1) Gensym-base-time-as-managed-float is set to the value of the
;;;    BASE-TIME entry, if any.  If there is no base-time entry, then the plist
;;;    is considered to not have the apppropriate elements, and nothing else,
;;;    here or below, is done.
;;;
;;;   (2) Gensym-time-at-start is set to the value of the START-TIME entry.
;;;
;;;   (3) Warmboot-simulated-time is set to the value of the SIMULATED-TIME
;;;   entry.
;;;
;;;   (4) If the special variable warmbooting-with-catch-up? is true, this sets
;;;   warmboot-current-time to the GENSYM-TIME entry.
;;;
;;; Note that early versions of G2, notably 3.0 Rev. 0, did not store
;;; gensym-time (the "current time" at the time of the snapshot) in their
;;; initial plists; therefore, if this feature is attempted on a KB saved in
;;; such a version, the gensym-time entry will not be found.  Such a case was
;;; previously handled by calling kb-error, which resulted in an abort.  It is
;;; now handled by setting warmbooting-with-catch-up? to nil, effectively
;;; cancelling the feature for this load.  A notification is also given.  In any
;;; case, the possibility of some actual user encountering becomes increasing
;;; more remote each day.  When we no longer allow a 3.0 Rev. 0 KB to be loaded,
;;; at all, we can erase this. (MHD 4/6/94)

(defun prepare-to-read-snapshot-if-appropriate (initial-kb-plist)
  (when warmbooting?
    (let* ((base-time? (getf initial-kb-plist 'base-time)))
      (when base-time?
	(with-clock-sync
	(setq gensym-base-time-as-managed-float
	      (prog1 (copy-managed-float base-time?)
		(if gensym-base-time-as-managed-float
		    (reclaim-managed-float
		      gensym-base-time-as-managed-float))))
	(setq gensym-time-at-start
	      (getf initial-kb-plist 'start-time)))
	(setq warmboot-simulated-time
	      (getf initial-kb-plist 'simulated-time))
	(when warmbooting-with-catch-up?
	  (setq warmboot-current-time
		(getf initial-kb-plist 'gensym-time))
	  (when (null warmboot-current-time)
	    (notify-user
	      "KB saved in wrong version, and the current-time is ~
               unavailable.  Therefore, we cannot run from snapshot time!")
	    (setq warmbooting-with-catch-up? nil)))))))




;;; `prepare-to-read-backup-if-appropriate' is at present basically a
;;; placeholder for initialization and checking to be done if we're reading a
;;; "backup", i.e., where type-of-file-being-read = BACKUP.  That feature is
;;; described elsewhere.
;;;
;;; Since this is not currently a fully supported feature in G2, the code within
;;; it is commented out.  And it's a big noop.  It was written in 1991 by ML,
;;; originally inline at the point of the call to this function, and it may be
;;; relevant reading if work on the backup feature is ever resumed. (MHD 4/6/94)
;;;
;;; A related function was `read-kb-detail-1', but since that is a subfunction
;;; of the commented out code in this function, it is commented out entirely,
;;; immediately below.

(defun prepare-to-read-backup-if-appropriate (initial-kb-plist)
  (declare (ignore initial-kb-plist))
;  (when (eq type-of-file-being-read 'backup)
;    (setq backup-case? t))  
;
;  (when (and backup-case?
;             main-kb-being-read?)
;    (notify-user
;      "A backup file cannot be loaded. It can only ~
;              be merged into its proper basis KB.")
;    (abort))
;  
;  ;; If the load is a backup, then it can only be loaded into
;  ;; the KB on which it was based. Else print a message and
;  ;; abort.
;  (read-kb-detail-1 initial-kb-plist)
;  
;  (setq duplicates-and-deletions-p
;        (getf initial-kb-plist
;              'duplicates-and-deletions-p))
;  (when (or duplicates-and-deletions-p
;            testing-double-read)
;    (setq index-of-duplicates-and-deletions
;          (read-kb-for-duplicates-and-deletions
;            namestring-for-file)))
  )

;(defun read-kb-detail-1 (initial-kb-plist)
;  (when backup-case?
;    (let ((complete-name-from-kb?
;	    (getf initial-kb-plist 'kb-name)))
;      (when (or (null complete-name-from-kb?)
;		(null complete-kb-name?)
;		(string/= complete-name-from-kb? complete-kb-name?))
;	(notify-user
;	  "A backup file can only be merged into the KB ~
;                               from which it was derived. The present KB has ~
;                               the identifier `~a', while the backup ~
;                               you are merging is `~a'."
;	  complete-kb-name? complete-name-from-kb?)
;	(abort)))))





(defun read-kb-detail-2 (initial-kb-plist)  
  (when new-saved-kb-format-p
    (make-frame-serial-number-to-frame-map)
    (when kb-load-case?
      ;; To make sure that any preexisting frames (blocks) that survive the load
      ;; do not have frame-serial-numbers that conflict with those of frames
      ;; loaded, we make a list of them, and examine them later. This must also
      ;; be done for any block created created during the load. This is done in
      ;; make-frame which is not called during the load procedure. (Note that
      ;; make-frame-without-initializations is not called except from within
      ;; read-kb and clone-frame.)
      (setq preexisting-frames
	    (loop for frame being each class-instance of 'block
		  do (set-preexisting-frame frame)
		  collect frame using gensym-cons)))
    
    ;; When merging a backup, the incoming deletions and frames must be
    ;; identified with existing blocks when possible. Only those
    ;; with frame-serial-numbers below
    ;; basis-kb-frame-serial-number were there as part of the
    ;; the basis KB.
    (when backup-case?
      (enter-old-things-into-map))
    
    (setq base-reference
	  (modf
	    (getf initial-kb-plist 'current-frame-serial-number)
	    base-modulus))
    
    (let ((character (read-char-for-kb)))
      (if (eql character #\@)
	  
	  (read-past-element-for-kb nil)
	  ;; above replaces the following form commented out:
	  ;;
	  ;;   (setq foundation-class-list (read-element-for-kb t))
	  ;;
	  ;; This is obsolete, and probably unnecessary, but we'll keep it in at
	  ;; least for 4.0.  (MHD 4/6/94)
	
	(unread-char-for-kb character)))))




(defun reformat-as-appropriate-if-necessary ()  
  
  ;; The following implements reformat-as-appropriate.  It decides to do the
  ;; reformatting of the entire KB (i.e., all of the workspaces in the KB) if
  ;; there exists at least one format frame with a format-change?  that's an
  ;; integer or with a format-change?  that's non-nil, i.e., a symbol, when
  ;; reformat-as-appropriate?  is true.  (The case where format-change?  is an
  ;; integer in practice never arises with KBs saved after version 0.91 at this
  ;; time.) (MHD 10/9/91)
  
  (cond
    ((loop for format-frame being class-instances of 'format-frame
	   as format-change? = (format-change? format-frame)
	   thereis
	     (if format-change?
		 (or reformat-as-appropriate?
		     (integerp format-change?))))
     
     ;; inform the user?
     (loop for workspace being class-instances of 'workspace
	   do (reformat-as-appropriate workspace nil))
     
     (loop for format-frame being class-instances of 'format-frame
	   as format-change? = (format-change? format-frame)
	   when (and format-change? (integerp format-change?))
	     do (setf (format-change? format-frame) nil)))))




;;; The variable `blocks-with-relation-instances-from-kb-read' is a list that
;;; will be gensym-consed by the initialize-after-reading method on blocks to
;;; contain the blocks that have relation-instances from the KB just read.  The
;;; once-only posting-loading function, rendezvous-frame-denotations-in-
;;; relation-instances, will use this list to rendezvous frame references and
;;; check for inter-module inconsistencies, and then reclaim the list.  This
;;; variable makes it possible to optimize the post-loading code; allowing it
;;; to iterate over those blocks just loaded instead of every block in G2.

(def-kb-specific-variable blocks-with-relation-instances-from-kb-read kb-load2 nil)

;;; The variable `blocks-with-connections-from-kb-read' is a list that
;;; will be used for post-loading function for upgrading connections list to
;;; connections-v2 hash table.

(def-kb-specific-variable blocks-with-connections-from-kb-read kb-load2 nil)

;;; The variable `blocks-with-subblocks-from-kb-read' is a list that
;;; will be used for post-loading function for upgrading subblocks list to
;;; subblocks-v2 constant queue.

(def-kb-specific-variable blocks-with-subblocks-from-kb-read kb-load2 nil)

(defun-substitution-macro loading-7-0-rev-0-kb-p ()
  (and (=f (first system-version-from-kb-being-read) 7)
       (=f (second system-version-from-kb-being-read) 0)
       (=f system-revision-from-last-kb-read 0)
       (=f system-quality-from-last-kb-read release-quality)))

;;; The `initialize-after-reading method for block' ... Note that this method
;;; is required to be defined for class BLOCK, and that subclasses that refine
;;; this method are expected to funcall-superior-method.

(def-class-method initialize-after-reading (block)
  ;; This is the root of this method's hierarchy, so don't call superior
  (when (relation-instances block)
    (gensym-push block blocks-with-relation-instances-from-kb-read))
  ;; Update every item's frame-status-and-notes slot:

  (when (frame-representations block)	; optimization
    ;; only pass in t for version change of kb
    (update-attribute-tables 	; new call. (MHD 2/20/95)
      block
      (<f kb-flags kb-flags-of-software)
      nil)
    (update-representations-of-slot-value block 'frame-status-and-notes))

  ;; Replace any double-mouse-down key codes with double-mouse-select, if KB was
  ;; saved in 7.0r0. Similar code on definition.
  (when (and (object-configuration block)
	     (loading-7-0-rev-0-kb-p))
    (fix-up-double-click-configuration-clauses (object-configuration block)))

  ;; The following code is adapted from the system-procedure-function 
  ;; G2-CLEAR-FLOATING-CONNECTION-STRUCTURES.  It reclaims
  ;; connection-structures that have a null connection-frame-or-class
  ;; component.  One way this can happen is illustrated by Bug HQ-3387902
  ;; "KB with connection to transient item causes unattached connection
  ;; upon reload".  This code locates such connections, removes their
  ;; references, and reclaims them. - jpg 2/12/01

  ;; We can't reclaim a connection here since it may still be in use by another
  ;; block (in fact, it almost always is -- by the block at its other end).  If
  ;; we did reclaim it, and any other initialize-after-reading method called
  ;; `make-connection', it would pick up the one we just reclaimed.  The
  ;; connection would now be valid and no longer satisfy `bad-connection-p'.
  ;; Although we could detect it with `connection-has-been-reprocessed-p', that
  ;; doesn't seem like the right thing to do.  To avoid this problem altogether
  ;; we defer reclaimation to a post-loading function. The only reason we aren't
  ;; doing everything in a post-loading function is a concern about looping over
  ;; all blocks as opposed to just the blocks being loaded from the KB, which is
  ;; effectively what we are doing here.
  
  ;; TODO: Conditionalize this code on kb-flags once the KB-save bug is fixed.
  ;; -fmw, 1/3/02
  
  (when (block-has-bad-connection-p block) ; This takes time O(number-of-connections)
    (unless blocks-with-bad-connections
      (setq blocks-with-bad-connections (gensym-list (copy-frame-serial-number
						       (current-frame-serial-number)))))
    (gensym-push block (cdr blocks-with-bad-connections)))

  (let ((cell-array? (cell-array block)))
    (when cell-array?
      (initialize-g2-cell-array-after-reading cell-array?))))

(def-class-method initialize (block)
  (let ((cell-array? (cell-array block)))
    (when cell-array?
      (initialize-g2-cell-array cell-array?))))

(def-class-method cleanup (block)
  (funcall-superior-method block)
  (remove-as-frame-with-kb-state-changes block)
  (let ((cell-array? (cell-array block)))
    (when cell-array?
      (cleanup-g2-cell-array cell-array?))))

(def-class-method note-runs-while-inactive-change (block)
  (let ((cell-array? (cell-array block)))
    (when cell-array?
      (note-g2-cell-array-runs-while-inactive-change cell-array? block))))





;;; `Classes-needing-data-interface-initialization' are those classes
;;; from pre-4.0 kbs that specified more than one data-interface capability
;;; in their capabilities-of-class slot.  Because only one data-interface
;;; is tolerated in 4.0, the last data-interface capability is chosen as the
;;; sole data-interface superior class and the instances of that class are
;;; initialized to the default values of that data-interface class.

;; This variable is a list of these lists:  (class data-interface-class).

(def-kb-specific-variable classes-needing-data-interface-initialization
    kb-load2 nil t)

(def-post-loading-function (initialize-instances-with-default-data-interface-values
			     :once-only t)
  (progn
    (loop for (class data-interface-class)
	        in classes-needing-data-interface-initialization
	  do
      (when (classp class)
	(loop for instance being each class-instance of class
	      do
	  (loop for slot-description in
		      (slot-descriptions
			(class-description data-interface-class))
		do
	    (when (eq (defining-class slot-description) data-interface-class)
	      (set-slot-description-value-without-noting
		instance slot-description
		(slot-init-form slot-description)))))))
    (reclaim-frame-tree classes-needing-data-interface-initialization)
    (setq classes-needing-data-interface-initialization nil))) ; added today (MHD 7/20/99)

;; I think this has probably never, or rarely, been invoked for users.  If it
;; were to run, there would have been corruption, since the variable
;; classes-needing-data-interface-initialization was never being reset to nil
;; after the reclamation, and since this was not :once-only.  So this might have
;; been called for successive modules after the first with reclaimed conses.
;; Perhaps it just would have squeeked by with old data in practice.
;; Furthermore, why wouldn't this have a KB-flag associated with it?  I don't
;; know.  Hopefully, we can just drop support for pre-3.0 KBs loaded into 5.x,
;; and just forget it.  (MHD 7/20/99)






;;; The initialize-after-reading method for table is defined in order to
;;; reestablish the WYSIWYGness of tables -- i.e., to fix up tables that grew
;;; but never shrank.  The laxness of the WYSIWYG rule is discussed by the
;;; function that introduces the laxness, update-text-cell.

#+development
(def-system-variable initialize-after-reading-for-table-accounting-version kb-load2 -1)
#+development
(def-system-variable initialize-after-reading-for-table-time-spent kb-load2)
#+development
(def-system-variable number-of-tables-updated-by-initialize-after-reading-for-table kb-load2)
#+development
(defparameter report-time-spent-on-initialize-after-reading-for-table? nil)
#+development
(def-post-loading-function maybe-report-time-spent-on-initialize-after-reading-for-table
  (if report-time-spent-on-initialize-after-reading-for-table?
      (notify-user
	"~d tables updated in ~f seconds"
	number-of-tables-updated-by-initialize-after-reading-for-table
	(/					; consing float -- ok for development
	  (float initialize-after-reading-for-table-time-spent)
	  fixnum-time-units-per-second))))


(defun-substitution-macro loading-7-0-alpha-or-beta-kb-p ()
  (and (=f (first system-version-from-kb-being-read) 7)
       (=f (second system-version-from-kb-being-read) 0)
       (<f system-quality-from-last-kb-read release-quality)))


(def-class-method initialize-after-reading (table)

  (funcall-superior-method table)		; per convention
    
  (unless (frame-of-class-p table 'graph)
    (when (or (table-may-not-be-wysiwyg-p table)	; (new) frame flag
	      (not (table-wysiwyg-p-flag-in-this-kb)))	; kb flag (for kbs old than
      (make-table-wysiwig-if-necessary-after-reading table)))

  (when (loading-7-0-alpha-or-beta-kb-p)
    (remove-bogus-parent-property-from-text-cells table)))


;;; The function `remove-bogus-parent-property-from-text-cells' removes the
;;; PARENT property from each text-cell in table. This property was used by the
;;; selection UI in 7.0 alpha and was inadvertantly saved out with KBs.

(defun remove-bogus-parent-property-from-text-cells (table)
  (loop for row in (table-rows table) doing
    (loop for cell? in row doing
      (when (cell-is-text-cell-p cell?)
	#+development (when (getf (text-cell-plist cell?) 'parent)
			(format t "Removing bogus PARENT property from ~s~%" cell?))
	(change-text-cell-property cell? 'parent nil)))))



(defun make-table-wysiwig-if-necessary-after-reading (table)
  (let (#+development
	(earlier-fixnum-time
	  (if report-time-spent-on-initialize-after-reading-for-table?
	      (get-fixnum-time))))
    
    (erase-images-of-block table nil)			    ; the frame flag
    (reformat-table-in-place table)
    (draw-images-of-block table nil)
    
    
    #+development
    (if report-time-spent-on-initialize-after-reading-for-table?
	
	(progn
	  (if (not (=f initialize-after-reading-for-table-accounting-version
		       current-kb-serial-number))
	      (progn
		(setq initialize-after-reading-for-table-time-spent 0)
		(setq number-of-tables-updated-by-initialize-after-reading-for-table 0)
		(setq initialize-after-reading-for-table-accounting-version
		      current-kb-serial-number)))
	  
	  (incff number-of-tables-updated-by-initialize-after-reading-for-table)
	  
	  (incff initialize-after-reading-for-table-time-spent
		 (fixnum-time-difference
		   (get-fixnum-time) earlier-fixnum-time))))))

;; Consider suppressing introduction of further non-wysiwigness by updating the
;; representations of the NOTES attribute in every block.  See this method
;; for block.

;; This method was introduced newly for for version 3.0 release rev 0.
;; (MHD 6/29/92)




;;; Delete-blocks-and-connections-to-be-deleted-after-reading ...

(defun delete-blocks-and-connections-to-be-deleted-after-reading ()
  (let ((do-not-note-permanent-changes-p t)
	(reference-serial-number (copy-frame-serial-number
				   (current-frame-serial-number))))
    ;; One cannot tell that a rule is an embedded rule before
    ;; the initialize-after-reading method of the containing item
    ;; sets up the parent-frame pointer.  So, this allows button deletion
    ;; to delete embedded rules safely.
    (loop with rules-seen = '()
	  for frame in blocks-to-delete-after-reading-kb
	  when (frame-has-not-been-reprocessed-p
		 frame reference-serial-number)
	    do (cond ((frame-of-class-p frame 'rule)
		      (gensym-push frame rules-seen))
		     (t
		      (delete-frame frame)))
	      finally
	    (loop for rule in rules-seen
		  when (frame-has-not-been-reprocessed-p
			 rule reference-serial-number)
		    do (delete-frame rule))
	  (reclaim-gensym-list rules-seen))
    (loop for connection in connections-to-delete-after-reading-kb
	  when (connection-has-not-been-reprocessed-p
		 connection reference-serial-number)
	    ;; Delete with no stubs
	    do (delete-connection connection))
    (reclaim-gensym-list connections-to-delete-after-reading-kb)
    (setq connections-to-delete-after-reading-kb nil)
    (reclaim-gensym-list blocks-to-delete-after-reading-kb)
    (reclaim-frame-serial-number reference-serial-number)
    (setq blocks-to-delete-after-reading-kb nil)))



(defun enter-old-things-into-map ()
  (loop for block being each class-instance of 'block
	when (and (permanent-block-p block)
		  (frame-serial-number-<= (frame-serial-number block)
					  basis-kb-frame-serial-number))
	  do
	    (enter-frame-into-frame-serial-number-map
	      (frame-serial-number block) block)
	    (loop for connection being each
		      input-connection of block
		  when
		    (and (permanent-connection-p connection)
			 (or (frame-serial-number-<
			       (frame-serial-number-for-connection
				 connection)
			       basis-kb-frame-serial-number)
			     (frame-serial-number-equal
			       (frame-serial-number-for-connection
				 connection)
			       basis-kb-frame-serial-number)))
		    do
		      (enter-frame-into-frame-serial-number-map
			(frame-serial-number-for-connection
			  connection)
			connection))))



;;; `read-kb-for-duplicates-and-deletions' is called by read-kb immediately
;;; after reading the plist-from-initial-element if the indicator
;;; duplicates and deletions is present. A second stream is opened on the same
;;; file. The file is read without side-effects (particularly allocation of frames
;;; or other satorage) paying attention only to the frame-serial-numbers of each
;;; frame or connection read at the top level, and to deletion messages
;;; read at the top level. There is an assumption that a frame or connection
;;; cannot occur after the same frame or connection has been given a
;;; delete message. The value is index-of-duplicates-and-deletions, a binary
;;; tree whose keys are frame-serial-numbers. The value is -1 to indicate a
;;; deletion, and n to indicate duplications, where there are more than
;;; one.

;(defun read-kb-for-duplicates-and-deletions (namestring)
;  (let ((completed? nil)
;	read-kb-stream
;	index-being-built)
;    (handling-gensym-file-errors
;      (unwind-protect
;	  (let* ((number-of-kb-lines-so-far 0)
;		 (number-of-kb-characters-so-far? nil)
;		 (next-character-for-kb? nil)		 
;		 frame-serial-number
;		 index-entry)	  
	    
;	    (setq read-kb-stream (g2-stream-open-for-input namestring))
;	    (setq index-being-built(make-frame-serial-number-tree)) 
;	    ;; No reason not to be able to read this file.
;	    (unless read-kb-stream (abort-on-bad-kb))
	    
;	    ;; Read past initial plist
;	    (read-char-for-kb)
;	    (read-past-element-for-kb nil)
	    
;	    ;; read frames, connections and deletion messages
;	    (loop for char = (read-char-for-kb)
;		  do
;	      (case char
;		((#\F #\C)
;		 (setq frame-serial-number (read-element-for-kb nil))
;		 (setq index-entry
;		       (get-frame-serial-number
;			 frame-serial-number index-being-built))
;		 #+development
;		 (if (and index-entry (<f index-entry 1))
;		     (cerror "continue" "Frame or connection found after its deletion mesage. ML"))	     
;		 (set-frame-serial-number-tree-value
;		   frame-serial-number
;		   index-being-built
;		   (if index-entry (incff index-entry) 1))
;		 ;; Read to end of frame or connection
;		 (if (eql char #\F)
;		     (loop for char1 = (read-char-for-kb)
;			   do
;		       (cond
;			 ((eql char1 #\!)
;			  (return))
;			 (t (unread-char-for-kb char1)
;			    (read-past-element-for-kb nil))))
;		     ;; 8 elements follow frame-serial-number in a connection 
;		     (loop for i from 1 to 8 do
;		       (read-past-element-for-kb nil))))
		
;		(#\D
;		 (set-frame-serial-number-tree-value
;		   (read-element-for-kb nil)
;		   index-being-built
;		   -1))
		
;		((#\space #\newline))
		
;		(#\E   
;		 (return))
		
;		(t (cerror "continue" "Error reading file for duplicates and deletions. See ML."))))
	    
;	    (setq completed? t))		; protected form

;	(if (null completed?)
;	    (cerror "continue" "failed to do inner read"))
;	(g2-stream-close read-kb-stream)))	;unwind protect and handling

;    index-being-built))





;; Problems: Binding of stream to small.
;; It gets into trouble reading.. Does it exit correctly?
;; Trace through its reads, and find out what it is doing.
;; Is there something wronf with newline logic?








;;; `fix-icon-variables-alists-in-icon-description'
;;; variables can be specified in icon-descriptions starting in 5.0.
;;; They were at one point stored as an alist of variable names and values,
;;; but were changed to a plist.  The alist version was never shipped,
;;; however a sufficient number of kbs were created (internally) to warrent
;;; this conversion function.

;;; Also see function fix-icon-variables-alists-in-icon-attributes-plist that fixes
;;; the instance-specific overrides of these default values.


(defmacro variable-list-is-alist-p (list)
  `(and ,list (consp (car-of-cons ,list))))

(defun-substitution-macro fix-icon-variables-alist-in-icon-description (line-drawing-description)
  (let ((kb-flags 0) ;kb-flags-from-last-kb-read
	 variables-spec? variable-values?)
    (when (possible-icon-variables-alist-p)
      (setf variables-spec? (get-variable-specification-if-any line-drawing-description))
      (setf variable-values? (cdr variables-spec?))
      (when (variable-list-is-alist-p variable-values?)
	(setf (cdr variables-spec?)
	      (convert-alist-to-plist variable-values?))))))






;;; `Finish-reading-slot-value-float' is now all but obsolete.  It is used for
;;; reading floats only in pre-3.0 G2 KBs.
;;;
;;; When significand-might-be-a-bignum?  is non-nil, significand is either a
;;; bignum or close to it and definitely non-zero.

(defun finish-reading-slot-value-float
       (significand postfix-character significand-might-be-a-bignum?)
  (with-temporary-gensym-float-creation
    finish-reading-slot-value-float
    (make-slot-value-float
      (let* ((exponent
	       (read-element-for-kb nil))	; speed up a bit?
	     (positive-gensym-float
	       (if (if (not significand-might-be-a-bignum?)
		       (=f significand 0))
		   0.0				; needed to fix an Ibuki bug
						;    -- JRA -- 5/14/90
		   (scale-float			; CHECK FOR OVERFLOW!!
		     (coerce-to-gensym-float	; optimize in fixnum case?
		       significand)
		     exponent))))
	(case postfix-character
	  (#\P positive-gensym-float)
	  (t (-e positive-gensym-float)))))))







;;; `Read-frame-for-kb' reads either a frame, or a frame modification, from the
;;; current KB. This reads either a frame, which has been written by
;;; write-frame-for-kb, or, quite rarely, a frame modification, written by
;;; write-relation-instances-frame-modification.

;;; ... This code should not delete items, since if those items
;;; were contained in a sequence or structure in a slot, it would
;;; cause problems with incorrect guard frame serial numbers in
;;; frames-for-rendezvous-in-aggregate-values? More precisely, the
;;; constraint that must be satisfied is that items must not be
;;; deleted while frame-being-read? is bound to a non-nil value.
;;; -alatto, 9/2/04

;;; Historical note regarding special handling of definitions:

;;; In read-frame-for-kb, after all slot values are read in,
;;; initialize-slots-of-frame-needing-evaluation is called, so that any system
;;; slots that didn't exist in the version of G2 in which the save occured
;;; will be filled with appropriate values. However, in the case of
;;; class-definitions that are of user-defined types, this presents a problem,
;;; because not all slot values in the saved kb are contained in the saved
;;; frame slots containing items ("entangled slots") are saved later as a frame
;;; modification. This means that the call to
;;; initialize-slots-of-frame-needing-evaluation sees these entangled slots
;;; as empty, and uses the initializer to create a value to put in, even though
;;; there is actually a value in the saved kb. When the value in the saved kb
;;; is encountered in a later frame modification, read-frame-for-kb puts
;;; it in the slot using initialize-slot-description-value, which
;;; in turn calls put-attribute-description-value with
;;; retaining-old-frame-or-initializing set to t, which means that the
;;; erroneous value put in the slot by the call to
;;; initialize-slots-of-frame-needing-evaluation is never reclaimed, leading
;;; to a leak. Worse, this value still exists and believes that it is in
;;;  the slot, even though it isn't, which can lead to a corruption.

;;; To fix this problem (HQ-5043098)we now to delay the call to
;;; initialize-slots-of-frame-needing-evaluation 
;;; until after the frame modification has been encountered, so only slots
;;; that do not have values saved in the kb are filled by this function.
;;; Unfortunately, we cannot tell at the time that the initial frame is 
;;; encountered that there will be a subsequent frame modification. So we
;;; just delay the call to initialize-slots-of-frame-needing-evaluation until the
;;; entire module is read, and call it in a per-module post-loading function.
;;; To minimize impact, we only perform this delay for class definitions,
;;; since these are the only frames for which frame modifications that fill
;;; slots are used. -alatto, 6/3/05

(defun-simple read-frame-for-kb (character top-level-element?)
  (let* ((frame-serial-number?
	  (if (and new-saved-kb-format-p (char= #\F character))
	      (read-element-for-kb nil)))
	 (class (read-element-for-kb nil))
	 (class-was-substituted? nil))	; for keeping track of instances
					;   of substituted classes

    ;; OLD KBs used to save out frame-author-or-authors and time-of-last-edit?
    ;; for each frame in this fixed position unconditionally.  That is obsolete.
    ;; Just read past them for old format (pre-3.0) KBs.
    ;; 
    ;; Note: IN OLD KBs these were always nil, as far as I know, because the
    ;; interface to them (from the editor) was never hooked up at that time.
    ;; (MHD 9/23/93)
    (when (not new-saved-kb-format-p)
      (read-past-element-for-kb nil)	; frame-author-or-authors
      (read-past-element-for-kb nil))	; time-of-last-edit?

    ;; GENSYMCID-1167: Verify in the source code the difference ...
    (when (and (null (class-description class))
	       (malformed-symbol-name-p class))
      (setq class (find-similar-class-name class)))

    ;;(pbk) check for title-block etc
    (when (eq class 'table)
      (setq class 'table-item))

    ;; Substitute for class if necessary:
    (cond
      ((if class-name-conflicts
	   (second (assq class class-name-conflicts)))
       (setq class (second (assq class class-name-conflicts))))
      ((and (substitute-class class)
	    ; (null (class-definition class))  ; obsolete restriction lifted! (MHD 6/24/94)
	    )
       (setq class (substitute-class class))
       (setq class-was-substituted? t)))
        
    ;; Install deferred class definitions, if any, at the end of the definitions
    ;; section of the KB.  This could only happen if reading KBs saved in
    ;; pre-1.11B versions of G2. See doc for deferred-class-definitions-alist
    ;; for further information.
    (if (and top-level-element?
	     deferred-class-definitions-alist
	     (not (subclassp class 'class-definition)))
	(install-deferred-class-definitions))

    (loop with class-description
	  = (class-description class)
	  with class-inheritance-path
	  = (class-inheritance-path class-description)
	  with frame-is-block?
	  = (inheritance-path-memq 'block class-inheritance-path)
 	  
	  ;; Definition-being-read-in-is-a-ghost? may be come true during the
	  ;; binding of frame, below.  If it becomes true, this is a duplicate
	  ;; of a ghost definition already read in earlier -- we will not
	  ;; install it and will discard it after reading past it.  This never
	  ;; gets setq'd if this is an old-format (pre-3.0) KB.  
	  with definition-being-read-in-is-a-ghost? = nil

	  ;; KB-object-index-for-frame is to be setq'd during the binding of
	  ;; frame below iff this is an old-format (pre-3.0) KB.
	  with kb-object-index-for-frame
	  with frame
	  = (cond
	      (new-saved-kb-format-p
	       (cond
		 (frame-serial-number?
		  (let ((frame?
			 (get-frame-given-frame-serial-number
			   frame-serial-number?)))
		    (when (and frame?
			       (frame-of-class-p frame? 'class-definition)
			       ;; a ghost definition is marked this way:
			       (first-definition-mark-p frame?))
		      (setq definition-being-read-in-is-a-ghost? t))
		    
		    (when (or (null frame?)
			      definition-being-read-in-is-a-ghost?)
		      (setq frame?
			    (make-frame-without-computed-initializations
			      class-description
			      nil ; (increment-current-frame-serial-number)
			      nil))
		      ;; But the frame is entered into the map using the old
		      ;; frame-serial-number, unless it is a dummy for a ghost.
		      (unless definition-being-read-in-is-a-ghost?
			(enter-frame-into-frame-serial-number-map
			  frame-serial-number? frame?)))
		    frame?))
		 (t 			; dependent frames
		  (make-frame-without-computed-initializations
		    class-description
		    nil ; (increment-current-frame-serial-number)
		    nil))))

	      (t					; old format
	       (let ((frame
		       (store-next-kb-object		   
			 (make-frame-without-computed-initializations
			   class-description nil nil))))
		 (setq kb-object-index-for-frame
		       (last-assigned-index kb-object-index-space))
		 frame)))
	  ;; for re-entrancy problem: HQ-4779004 -dkuznick, 5/19/04
	  with frame-being-read? = frame
	  ;; Ditto.  Bug HQ-4779004 is not hitting *this* problem, but one may
	  ;; be able to contruct an example KB which would -dkuznick, 5/21/04
	  with slot-description-for-slot-value-being-read?

	  ;; Variables that may be set when the name-of-defined-class or
	  ;; name-or-names-for-frame slot is encountered: (these two variables
	  ;; could be replaced by one)
	  with name-of-defined-class? = nil
	  with capabilities-of-class? = nil
	  with attribute-descriptions? = nil
	  with default-overrides-of-system-slots? = nil
	  with superior-of-defined-class? = nil
	  with direct-superiors-of-defined-class? = nil
	  with format-name? = nil
	  with line-color-of-icon? = nil
	  with icon-description-for-class? = nil	    ; As in object-definitions
                                                            ; and class-definitions
	  ;; Variables set for each slot encountered:
	  with slot-denotation-or-left-edge
	  with slot-name
	  with class-qualifier?
	  with slot-value
	  
	  initially
	    
	    ;; Keep track of which frames are of substituted classes:
	    (when class-was-substituted?
	      (gensym-push frame frames-with-substitute-classes))



	  ;; At this point, the frame should not be marked as permanent
	  ;; because its frame-flags have not yet been read. The following
	  ;; protects against the possibility that the frame has default
	  ;; frame-flags, but has been set permanent by add-as-inferior-block
	  ;; when it was in an incomplete state and existed only as a forward
	  ;; reference.
	  ;;
	  ;; ----- Update: NOT ALWAYS -- don't do that when this is frame
	  ;; modification!  In that case, the frame-flag is read in earlier or
	  ;; later by a separate call that reads in the whole frame.
	  ;;
	  ;; (MHD 5/23/95)
	    (when (and frame-is-block?
		       (not (frame-flags-read-p frame)))
	      (clear-permanent-block frame))
	  
	  do (setq character (read-char-for-kb))
	     (character-case character
	       (#\! (loop-finish))
	       (#\[ (if warmbooting?
			(read-runtime-data-for-block frame)
			(read-past-runtime-data-for-block nil))
		    (loop-finish))
	       (otherwise (unread-char-for-kb character)))
      
	     (setq slot-denotation-or-left-edge (read-element-for-kb nil))
      
	     (cond
	       ((fixnump slot-denotation-or-left-edge)
		(read-final-block-data-in-old-format-kb
		  frame slot-denotation-or-left-edge)
		(loop-finish))
	       (t
		(setq slot-name
		      (unqualified-name slot-denotation-or-left-edge))
		(let* ((original-qualifier-name?
                         (class-qualifier slot-denotation-or-left-edge))
                       (substitute-qualifier-name?
                         (second (assq original-qualifier-name? class-name-conflicts))))
                  (setq class-qualifier? (or substitute-qualifier-name?
                                             original-qualifier-name?)))
		(setq slot-description-for-slot-value-being-read?
		      (get-slot-description-of-class-description
			slot-name class-description class-qualifier?))
		(reclaim-slot-value slot-denotation-or-left-edge)))
	     (setq slot-value (read-element-for-kb nil))
	     (case slot-name
	       (name-of-defined-class
		;; frame may be assumed to be a class definition
		(setq name-of-defined-class? slot-value))
	       (superior-of-defined-class
		(setq superior-of-defined-class? slot-value))
	       (direct-superiors-of-defined-class
		(setq direct-superiors-of-defined-class? slot-value))
	       (capabilities-of-class
		(setq capabilities-of-class? slot-value))
	       (default-overrides-of-system-slots
		   (setq default-overrides-of-system-slots? slot-value))   
	       (attribute-descriptions-for-class
		(setq attribute-descriptions? slot-value))
	       (line-color-of-icon  ; specially-handled, absent slot as of 4.0;
				    ;   previously in definitions
		(when (and (symbolp slot-value) ; necessary?
			   (color-or-metacolor-p slot-value)
			   (object-definition-p frame)) ; necessary?
		  (setq line-color-of-icon? slot-value)))
	       (icon-description-for-class?
		(fix-icon-variables-alist-in-icon-description slot-value)
		(setq icon-description-for-class? slot-value))
	       (name-or-names-for-frame
		(cond
		  ((if (not (class-definitions-ordered-p)) ;for pre-1988 kbs!		       
		       (inheritance-path-memq 'class-definition class-inheritance-path)))
		  ((inheritance-path-memq 'format-frame class-inheritance-path)
		   ;; names of format frames are handled specially below
		   (setq format-name? slot-value))
		  ((inheritance-path-memq 'system-frame class-inheritance-path)
		   (put-name-or-names-for-frame frame slot-value t)

		   ;; Record reading of all system frames: (Note: this
		   ;; happens once and only once, since system frames always
		   ;; have this slot saved out.)
		   (slot-value-push frame system-tables-read-for-this-module))
		  (t		   
		   ;; Put the slot: (name-or-names-for-frame slot putter assumed
		   ;; present)
		   (put-name-or-names-for-frame frame slot-value t))))

	       (slot-group-for-block?
		(process-slot-group-for-block frame slot-value))
	       ;; The following slots are being converted for now piecemeal from
	       ;; text strings upon loading, where appropriate.  Later, a more
	       ;; abstratc means may be developed. (MHD 12/23/95)
	       (t
		(let ((slot-description?
		       (get-slot-description-of-frame
			 slot-name frame class-qualifier?)))
		  ;; GENSYMCID-1167: Verify in the source code the difference ...
		  (when (and (null slot-description?)
			     (malformed-symbol-name-p slot-name))
		    (setq slot-name
			  (find-similar-slot-name slot-name class))
		    ;; try again
		    (setq slot-description?
			  (get-slot-description-of-frame
			    slot-name frame class-qualifier?)))
		  (cond
		    ((null slot-description?)
		     (let ((absent-slot-putter?
			     (absent-slot-putter
			       slot-name)))
		       (cond
			 (absent-slot-putter?
			  (funcall-simple-compiled-function
			    absent-slot-putter? frame slot-value))
			 (t 
			  (notify-user
			    "~S contains a value for attribute ~NQ in an instance ~
                     of class ~NR, which does not have such an attribute.  The ~
                     value will simply be discarded. Please notify Gensym Customer Support."
			    name-text-string-for-kb-being-read
			    slot-name class-qualifier?
			    frame class)
			  ;; This behavior changed by ML on 5 July, 1991. It used
			  ;; to abort when there was an attribute not belonging
			  ;; to the class and having no slot putter.  Now, there will
			  ;; be a warning, and the value will be discarded. G2 will
			  ;; proceed.
			  ;; -- I removed the sentence at the end that requested
			  ;; that the user notify Gensym Customer Service, and
			  ;; replaced that with "The value will simply be discarded.".
			  ;; (MHD 12/3/91)
			  ;; -- I added the new ~NR directive (record block) to make
			  ;; the frame in question easily accesable by the user.
			  ;; -fmw, 4/15/94
			  ;; I think that this is an error when this occurs (the module
			  ;; containing the item should also contain a ghost definition that
			  ;; contains the same slots as the item actually has), so I'm
			  ;; putting the "notify Gensym Customer Service back in, and adding
			  ;; a development-time cerror. -alatto, 12/28/04
			  #+development
			  (cerror "Continue anyway"
				  "~S contains a value for attribute ~S in an instance ~
                                   of class ~S, but we can't find this attribute."
				  name-text-string-for-kb-being-read slot-name class)))))

		    (t 
		     (initialize-slot-description-value
		       frame slot-description? slot-value)		
		     (when (eq slot-name 'frame-flags) ; see above. (MHD 5/23/95)
		       (setf (frame-flags-read-p frame) t)))))))

	finally

	    ;; The following form used to not be commented out and was part of
	    ;; the cause of bug HQ-4779004.  Now that we are binding
	    ;; frame-being-read? for re-entrancy purposes, we should no longer
	    ;; need to set it to NIL, unless
	    ;; read-aggregate-evaluation-value-for-kb is called somewhere in
	    ;; the finally clause, but in that case, it would have caused an
	    ;; abort anyway. -dkuznick, 5/20/04

	    ;; (setq frame-being-read? nil)

	    ;; Ditto this next form, though the KB for bug HQ-4779004 wasn't
	    ;; exhibiting this. -dkuznick, 5/21/04

	    ;; (setq slot-description-for-slot-value-being-read? nil)

	    ;; Finish setting the up the slots of frame by initializing the
	    ;; slots that need evaluation, but that weren't saved out,
	    ;; presumably because they didn't need evaluation at the time
	    ;; they were saved.
	    ;; 
	    ;; (Added to handle slots whose init for changed to needing
	    ;; evaluation between releases, a previously unsolved problem, and
	    ;; to fix bugs related to this.  (MHD 4/14/94))
	    ;; We don't fill the slots until later (in a post-loading-function)
	    ;; for definitions, because the slots might be entangled
	    ;; slots, which will get filled by a subsequent frame modification.
	    ;; this fixes bug HQ-5043098 -alatto, 6/3/05
	    (if (frame-of-class-p frame 'class-definition)
		(gensym-push (gensym-cons frame
					  (copy-frame-serial-number
					    (current-frame-serial-number)))
			     definitions-read-in-this-module)
		(initialize-slots-of-frame-needing-evaluation frame))
	    
	    ;; Note: the value of CHARACTER is not guaranteed during execution
	    ;; of the finally code. The final #\! may have been read by
	    ;; read-runtime-data-for-block which has its own local variable
	    ;; CHARACTER.

	    ;; In KBs until 2/13/92 source code, computation-styles were not
	    ;; being marked as permanent, and hence if loading runtime data could
	    ;; be deleted after loading. They need to be marked permanent in any
	    ;; case.
	    (when (eq class 'computation-style)
	      (set-permanent-block frame))


	    ;; Fix up old icon descriptions in object definitions, and set the
	    ;; slot:
	    (cond
	      (icon-description-for-class?
	       (fixup-icon-description-for-class
		 frame icon-description-for-class? line-color-of-icon?))
	      ((and line-color-of-icon?
		    (icon-description-for-class? frame))
	       ;; really old (2.0) and has a color
	       (fix-icon-description-for-class-slot
		 frame nil nil nil line-color-of-icon?)))

	    ;; Initialize the direct superiors of defined class with the listed
	    ;; pre-4.0 superior-of-defined-class value or the post-4.0 value.
	    ;;
	    ;; Here, we also handle propagating changes in names of classes due
	    ;; to class conflicts down to subclasses, i.e., to their lists
	    ;; direct superiors.
	    (when (or name-of-defined-class? superior-of-defined-class?
		    direct-superiors-of-defined-class?)
	      (let ((adjusted-direct-superiors
		      (if superior-of-defined-class?
			  (if (atom superior-of-defined-class?)
			      (slot-value-list superior-of-defined-class?)
			      superior-of-defined-class?)
			  direct-superiors-of-defined-class?)))
		(adjust-direct-superiors-per-class-conflicts
		  adjusted-direct-superiors)
		(initialize-slot-value
		  frame 'direct-superiors-of-defined-class adjusted-direct-superiors)))
	    
	    ;; Shift the pre-4.0 attribute descriptions to the class-specific-
	    ;; attributes slot or the default-overrides slot, as appropriate.
	    (when (or attribute-descriptions? default-overrides-of-system-slots?)

	      ;; Some code to check for a kind of corruption found in a KB from
	      ;; Rockwell -- /vmsdisc/customer-kbs/rockwell/finderr.kb -- that
	      ;; had FOO as the value of default-overrides-of-system-slots?.  We
	      ;; hope this is a one-of-a-kind fluke. (MHD/GHW 9/12/94)
	      (when (not (listp default-overrides-of-system-slots?))
		#+development
		(cerror "Continue -- changing it to nil"
			"A definition has a corrupted default-overrides ~
                         attribute: ~a  (Tell GHW or MHD.)"
			default-overrides-of-system-slots?)
		(setq default-overrides-of-system-slots? nil))
	      
	      (process-pre-4.0-attribute-descriptions-and-default-overrides
		frame name-of-defined-class? attribute-descriptions? 
		(direct-superiors-of-defined-class frame)
		default-overrides-of-system-slots? nil nil))

	    ;; Shift the symbols of the obsolete capabilities into the direct-
	    ;; superiors-of-defined-class and instance-configuration slots.
	    (when (and capabilities-of-class? name-of-defined-class?)
	      (process-pre-4.0-capabilities-of-class
		frame name-of-defined-class? capabilities-of-class? nil)
	      ;;-rdf, 9/29/94	      
	      (when (and capabilities-of-class? (consp capabilities-of-class?))
		(reclaim-slot-value-tree capabilities-of-class?)))
	  
	  ;; Must handle the name conflicts between relations here, since
	  ;; the name-or-names-for-frame slot of this class's instance does
	  ;; not get saved in KBs, but rather is formed as a side effect
	  ;; of reading the saved values of the relation-name and
	  ;; inverse-relation-name slots.  See KB-MERGE for further
	  ;; discussion. (MHD 7/28/95)
	  ;; 
	  ;; If merging, find and note all name conflicts: (This
	  ;; applies to "definitional" items; see KB-MERGE for
	  ;; details.)
	    (when (and frame-is-block?
		       (name-or-names-for-frame frame))	; opt.
	      (record-name-conflict-if-necessary
		frame
		(name-or-names-for-frame frame)))
	    (cond
	      ((and name-of-defined-class?
		    ;; Definitions should not be installed while reading ghost
		    ;; definitions.
		    reading-ghost-definitions-p)
	       (setq class-name-read-while-reading-current-ghost-definition
		     name-of-defined-class?))

	      ;; NEW:  (MHD/ML 10/22/92)
	      (definition-being-read-in-is-a-ghost?	; dummy for a ghost, to 
		  (delete-block-after-reading-kb frame))	;   be deleted at end

	      (name-of-defined-class?
	       (cond
		 ((class-definitions-ordered-p)
		  (install-class-definition
		    name-of-defined-class? frame nil nil t))
		 (t
		  (defer-class-definition name-of-defined-class? frame))))
	      
	      ((or format-name?
		   (inheritance-path-memq 'format-frame class-inheritance-path))
	       (let ((old-format-frame-to-return?
		      (finish-reading-format-frame-for-kb frame format-name?)))
		 (when old-format-frame-to-return?
		   (setq frame old-format-frame-to-return?)
		   (cond
		     (new-saved-kb-format-p
		      (enter-frame-into-frame-serial-number-map
			frame-serial-number? frame))
		     (t
		      (store-object-in-index-space
			kb-object-index-space
			kb-object-index-for-frame
			frame))))))
	      
	      ((frame-of-class-p frame 'computation-style)
	       (let ((existing-computation-style
		      (get-or-make-entry-to-set-of-all-permanent-computation-styles
			frame)))
		 (unless (eq frame existing-computation-style)
		   (delete-block-after-reading-kb frame)
		   (setq frame existing-computation-style)
		   (enter-frame-into-frame-serial-number-map ; only saved in 3.0+
		     frame-serial-number? frame)))))

	  ;; Any saved frame must be transient or permanent. Permanent-block is
	  ;; a savable flag. So its absence allows us to conclude that a block is
	  ;; permanent. (True only for recent 3.0 KBs, but only these could have
	  ;; kb-save-with-runtime-data.) 
	    (when (and (eq type-of-file-being-read 'kb-save-with-runtime-data)
		       frame-is-block?)
	      ;; A bug here in 3.0 that caused transient G2 windows on
	      ;; workspaces to not be deleted.  Code's been rearranged to fix
	      ;; that.  (MHD 8/29/94)
	      (when (not (permanent-block-p frame))
		(set-transient frame))
	      (cond
		((and warmbooting?
		      (or (frame-of-class-p frame 'procedure-invocation)
			  (and (null (superblock? frame))
			       (frame-of-class-p frame 'ui-client-item))))
		 ;; See note about instances of classes procedure-invocation and
		 ;; ui-client-item in write-reference-to-frame (module
		 ;; KB-SAVE1).
		 (delete-block-after-unsquirreling frame))
		((and (not warmbooting?) (transient-p frame))
		 (delete-block-after-reading-kb frame))))
	    (return frame))))

(def-post-loading-function initialize-unbound-slots-in-definitions
  (loop for definition-and-fsn in definitions-read-in-this-module
	for definition = (car definition-and-fsn)
	for fsn = (cdr definition-and-fsn)
	do
    (unless (frame-has-been-reprocessed-p definition fsn)
      (initialize-slots-of-frame-needing-evaluation definition))
    (reclaim-frame-serial-number fsn)
    (reclaim-gensym-cons definition-and-fsn))
  (reclaim-gensym-list definitions-read-in-this-module))

;;; The function `fixup-icon-description-for-class' sets the
;;; icon-description-for-class? slot after fixing it up.
;;;
;;; Frame here is a object definition.
;;;
;;; Icon-description-for-class must be a non-null value of the
;;; icon-description-for-class? slot.
;;;
;;; Line-color-of-icon? is non-nil, it should be a color or metacolor, and it
;;; may be incorporated into the line drawing description in
;;; icon-description-for-class.
;;;
;;; It fixes old icon descriptions in object-definitions, when the kb flags do
;;; not yield (icon-editor-fixed-p-function).  (Previously, this was done in
;;; install-class-definition, but here is better.).
;;;
;;; And it fixes up the pre-4.0 monochrome icon descriptions (as well as 4.0
;;; Beta intermediate versions that had various problems).  

(defun fixup-icon-description-for-class
    (frame icon-description-for-class line-color-of-icon?)

  ;; Fixup broken filled-polygon elements.
  (unless (icon-editor-fixed-p-function)
    (loop for thing in (cddr icon-description-for-class)
	  with second-thing
	  when (and (consp thing)
		    (eq (car thing) 'filled-polygon)
		    (not (clockwise-polygon-p (second thing))))
	    do
	      (setq second-thing (second thing))
	      (setf (second thing)
		    (nreverse (copy-for-slot-value (second thing))))
	      (reclaim-slot-value second-thing)))

  (unless (and (all-icons-are-polychrome-p) ; Redundant:  (See Note A)
	       (get-variable-specification-if-any 
		 icon-description-for-class)
	       (get-icon-background-layer-if-any
		 icon-description-for-class)
	       (no-blinking-areas-in-icon-descriptions-p)
	       (not (empty-layer-in-icon-description-p
		      (cddr icon-description-for-class))))
    (setf (cddr icon-description-for-class)
	  (fix-line-drawing-description-for-class
	    (cddr icon-description-for-class)
	    line-color-of-icon?)))

  (initialize-slot-value
    frame 'icon-description-for-class? icon-description-for-class))

;; Note A:
;;
;; This replaces post-loading functions fix-icon-descriptions-after-reading and
;; fix-icon-descriptions-after-reading-1, which used to do the same thing for
;; all instances of object-definition.  (Those functions have now been
;; incorporated into the initialize-after-reading method for entity.)
;;
;; (MHD 5/31/94)
;;
;; -- Note that this was at first improperly implemented in the
;; initialize-after-reading method for object-definition.  That's too late. Now
;; it's here, where it fits in well.  It was moved here at the same time as the
;; (all-icons-are-polychrome-p), so as a slight kludge, we require that flag to
;; decide if they're out.  Test KB: /home/mhd/kb1/dissolver.kb (1.11b KB)
;;
;; (MHD 6/8/95)

;; Note: it's best to do this here, rather than in a post-loading function,
;; because we're guaranteed not to have any instances yet.  Note that these
;; fixups should have no effect on the size or visual appearance of icons based
;; upon them, at least for previously legal inputs.  They're intended just as
;; updates or normalizations of formats. (MHD 6/8/95)


;; description-element = (X (blinking-area ...) ...)  Some
;; Very old KBs have blinking areas, e.g. pulp-and-paper as
;; of 7/5/88.  The cleanup has been in place for some time,
;; since 2.0 in 1989, but the kb-flag was only added for
;; 4.0, in 1993.  (MHD 12/19/93)
;; Abstracted this predicate  -fmw, 12/21/93

(defun blinking-area-p (icon-description-element)
  (and (cdr icon-description-element)
       (consp (cadr icon-description-element))
       (symbolp (car (cadr icon-description-element)))))


(defun empty-layer-in-icon-description-p (line-drawing-description)
  (loop for previous-element-was-layer-name-p = nil
					      then element-is-layer-name-p
	for element in line-drawing-description
	for element-is-layer-name-p = (symbolp element)
	thereis (and previous-element-was-layer-name-p element-is-layer-name-p)))


;;; Fix-line-drawing-description-for-class fixes all icon descriptions to have
;;; valid, polychrome headers for 4.0.  It returns a replacement
;;; for line-drawing-description, which may incorporate the argument, and may
;;; or may not be eq to it.

;;; For line-color-of-icon, it maintains compatibility between pre-4.0 kbs when
;;; there was a line-color-of-icon slot on object definitions and kbs developed
;;; after the removal of this slot.  When color? has a value and the
;;; icon-description is monochrome, this function transforms the
;;; icon-description into a polychrome description with an icon-color of color;
;;; otherwise it discards the value of color.  An example transformation given a
;;; monochrome description and color? value of red:
;;;
;;;    (50 50 . ((lines (0 0) (0 50) (50 0) (50 50))))
;;;      -->
;;;    (50 50
;;;     . ((polychrome (foreground . foreground) (icon-color . red))
;;;        icon-color (lines (0 0) (0 50) (50 0) (50 50))))
;;;
;;;  (7/12/94 ghw)
;;;
;;;  Note: generally, this can be called multiple times in any order; however,
;;;  it is assumed that color? is only specified after there already is an
;;;  description.

;;; It manages converting from four obsolete slots, width-of-icon-for-class?,
;;; height-of-icon-for-class?, line-drawing-description-for-class?, and
;;; line-color-of-icon to icon-description-for-class?, which incorporates their
;;; values when appropriate.
;;;
;;; Note that (FOREGROUND . FOREGROUND) is to be present in the header only
;;; when FOREGROUND is used as one of the regions. See the little in-line
;;; comment in the compiler for icon-description?; see GRAMMAR6.

(defun fix-line-drawing-description-for-class
    (line-drawing-description line-color-of-icon?)
  (when (null (get-polychrome-header-if-any line-drawing-description))
    (slot-value-push (slot-value-list 'polychrome) line-drawing-description))
  (when (null (get-variable-specification-if-any line-drawing-description))
    (slot-value-push (slot-value-list 'variables) (cdr line-drawing-description)))
  (when (null (get-icon-background-layer-if-any line-drawing-description))
    (slot-value-push (slot-value-list 'background-layer) (cddr line-drawing-description)))

  #+development
  (test-assertion (get-polychrome-header-if-any line-drawing-description))
  
  ;; Eliminate (ancient) blinking areas:  (wastes conses; rare)
  (loop for description-elements on (cdr line-drawing-description)
	as description-element = (car description-elements)
	when (and (consp description-element)
		  (blinking-area-p description-element))
	  do (loop for l on (cdr description-element)
		   when (not (symbolp (car (car l))))
		     do (setf (cdr description-element) l)
			(return nil)))
  
  (let ((polychrome-header (car line-drawing-description)))

    ;; Handle fixing up of old colored monochrome icons, converting them
    ;; to polychrome icons with icon-color defined as a region in that
    ;; one color, and with icon-color named as the (first/only) region
    ;; for all of the elements:
    (when (and line-color-of-icon?
	       (not (assq 'icon-color (cdr polychrome-header))))
      (slot-value-push
	(slot-value-cons 'icon-color line-color-of-icon?)
	(cdr polychrome-header))
      (slot-value-push
	'icon-color
	(cdddr line-drawing-description)))

    (when (empty-layer-in-icon-description-p (cdddr line-drawing-description))
      (loop for last-cons = nil then current-cons
	    for current-cons = (cdddr line-drawing-description)
			     then next-cons
	    while current-cons
	    for next-cons = (cdr current-cons)
	    when (and (symbolp (car current-cons))
		      (symbolp (cadr current-cons)))
	      do (if last-cons
		     (setf (cdr last-cons) next-cons)
		     (setf (cdddr line-drawing-description) next-cons))
		 (reclaim-slot-value-cons current-cons)))
      

    ;; If there are elements implicitly drawn in foreground, then if other
    ;; regions are defined in the header, then foreground must be explicitly
    ;; present in header, so we put in (foreground .  foreground) to pick up
    ;; the initial elements; in the case where there is only one region, and
    ;; it's implicitly foreground, this is not done to save a little space,
    ;; and the icon painters (for screen drawing and for printing) handle it
    ;; as they would a polychrome header of (polychrome (foreground .
    ;; foreground)).
    ;;
    ;; Also, make sure it's present if foreground is used as a color
    ;; region within the line drawing description.  (The compiler definitely
    ;; ensures this, but we're not sure about those that came from other
    ;; sources.)
    (when (and (or (and (not (symbolp (first (cdddr line-drawing-description))))
			(cdr polychrome-header))
		   (memq 'foreground (cdr line-drawing-description)))
	       (null (assq 'foreground (cdr polychrome-header))))
      (setf (cdr polychrome-header)
	    (slot-value-cons
	      (slot-value-cons 'foreground 'foreground)
	      (cdr polychrome-header))))
    
    ;; Also delete NIL's in the header. A bug in
    ;; fix-icon-description-for-class-slot used to introduce them, so they
    ;; may now exist in KB's saved while the bug was present -fmw, 2/15/95.
    (loop while (memq 'NIL (cdr polychrome-header))
	  do (setf (cdr polychrome-header)
		   (delete-slot-value-element 'NIL (cdr polychrome-header)))))
  line-drawing-description)

;; To test icon-color fixup with 1.11b KB, load /home/mhd/kb1/autopainter.kb.
  




      

;;; `Read-final-block-data-in-old-format-kb' is used to only to read the data at
;;; the end of a block saved in an old (pre-3.0) KB.  These cannot have runtime
;;; data, since that was not part of the the pre-3.0 format.  This is called
;;; after reading an integer, which is taken to be the left edge of the block,
;;; as well as to signal the start of this data.  The other three edges follow,
;;; and there follows the list of subblocks.  All of the edges and subblocks are
;;; set into the argument block by this function.  The reading of subblocks is
;;; terminated by the reading of the final #\! character, after which this
;;; function returns.  No useful values are returned.

(defun read-final-block-data-in-old-format-kb (block left-edge-of-block)
  #+development
  (test-assertion (not new-saved-kb-format-p))
  (set-edges-of-block
    block left-edge-of-block
    (read-element-for-kb nil)
    (read-element-for-kb nil)
    (read-element-for-kb nil))
  (loop with subblock
	as first-time? = t then nil
	for character = (read-char-for-kb-past-spaces)
	until (char= character #\!)
	do (unread-char-for-kb character)
	   (setq subblock (read-element-for-kb nil))
	   #+development (when (superblock? subblock)
			   (cerror "Go ahead" "Slamming the superblock of ~s from ~s to ~s"
				   block (superblock? subblock) block))
           (set-superblock-and-faction subblock block)
	collect subblock into subblocks using slot-value-cons
	finally
	  (setf (subblocks block)
		#-subblocks-v2 subblocks
		#+subblocks-v2 (upgrade-subblocks subblocks))))




;;; `Process-pre-4.0-attribute-descriptions-and-default-overrides', when the
;;; superior class has a user-defined slot description with attribute name,
;;; shifts the class-level attribute description to the default-overrides slot;
;;; otherwise it shifts the attribute description to the
;;; class-specific-attributes slot.  Note that there is a single direct
;;; superior for pre-4.0 definitions.  This function is called during kb
;;; loading and by the role servers for pre-4.0 "change the text of attributes-
;;; specific-to-class" (attribute-descriptions? is the value given to change-
;;; the-text and default-overrides? is nil) and "change the text of the
;;; default-settings" (default-overrides? is the value given to change-the-
;;; text and attribute-descriptions? is nil.

;;; This function also deals with the indexed-attributes-of-definition slot on
;;; the frame.  In G2 4.0, only the defining class of an attribute can have
;;; that attribute-name as a member of its indexed-attributes-of-definition
;;; slot.  Because shadowing attributes in 3.0 become default overrides in 4.0,
;;; whenever a shadowing attribute is in the indexed-attributes-of-definition
;;; slot of the shadowing definition, the attribute name must be moved from
;;; that slot and added, if necessary, to the indexed-attributes-for-definition
;;; slot of the defining class even when the defining class has not indexed it
;;; in 3.0.

(defun process-pre-4.0-attribute-descriptions-and-default-overrides
    (frame name-of-defined-class? attribute-descriptions? direct-superiors?
	   default-overrides? change-the-text-of-attributes?
	   change-the-text-of-overrides?)
  (let ((class-specific-attributes-list nil)
	 (default-overrides-list
	     (cond (change-the-text-of-attributes?
		    ;; The new value for the default-overrides is initialized
		    ;; to contain only the overrides on system-defined slots.
		    (loop for override in (default-overrides frame)
			  when (not (override-is-for-user-defined-slot-p override))
			    collect override using slot-value-cons))
		   (change-the-text-of-overrides?
		    ;; The new value for the default-overrides is initialized
		    ;; to contain only the overrides on user-defined slots.
		    (loop for override in (default-overrides frame)
			  when (override-is-for-user-defined-slot-p override)
			    collect (copy-for-slot-value override)
			      using slot-value-cons))
		   (t default-overrides?)))
	 (direct-superiors-are-defined?
	   (direct-superiors-are-defined-p direct-superiors?))
	 (indexed-attributes-for-definition
	   (indexed-attributes-for-definition frame))
	 (indexed-attributes-becoming-overrides? nil)
	 (new-superior-indexed-attributes? nil))
    (if change-the-text-of-overrides?
	(setq default-overrides-list
	      (nconc default-overrides-list default-overrides?))
	(loop for attribute-description in attribute-descriptions?
	      for attribute-name = (attribute-name attribute-description)
	      for superior-slot-description? =
	            (if direct-superiors-are-defined?
			(loop for superior in direct-superiors?
			      for slot-description? =
			      (slot-description-from-class
				superior
				(unalias-slot-name-if-necessary
				  attribute-name superior))
			      when slot-description?
				return slot-description?)
			(let* ((definition-class (class frame))
			       (superior-class
				 (case definition-class
				   (object-definition 'object)
				   (message-definition 'message)
				   (connection-definition 'connection))))
			  (slot-description-from-class
			    superior-class
			    (unalias-slot-name-if-necessary
			      attribute-name superior-class))))
	      for system-defined-slot-description? =
	            (and superior-slot-description?
			 (system-defined-slot-description-p
			   superior-slot-description?))
	      do
	  (cond ((and superior-slot-description?
		      (not system-defined-slot-description?))
		 (when (memq attribute-name indexed-attributes-for-definition)
		   (let* ((superior-class (defining-class superior-slot-description?))
			  (superior-definition (class-definition superior-class)))
		     (unless (memq
			       attribute-name
			       (indexed-attributes-for-definition superior-definition))
		       (let ((list-holding-superior-information?
			       (member superior-class new-superior-indexed-attributes?
				       :test 'car-eq)))
			 (if list-holding-superior-information?
			     (let ((superior-information
				     (car list-holding-superior-information?)))
			       (setf (second superior-information)
				     (frame-cons attribute-name
						 (second superior-information))))
			     (setq new-superior-indexed-attributes?
				   (frame-cons
				     (frame-list superior-class (frame-list attribute-name))
				     new-superior-indexed-attributes?)))))
		     (setq indexed-attributes-becoming-overrides?
			   (frame-cons attribute-name
				       indexed-attributes-becoming-overrides?))))
		 (let* ((attribute-initial-value
			  (copy-for-slot-value (second attribute-description)))
			(attribute-initial-type?
			  (copy-for-slot-value (third attribute-description))))
		   (setq default-overrides-list
			 (nconc default-overrides-list
				(cond
				  ((and (consp attribute-initial-value)
					(eq (car attribute-initial-value)
					    ':funcall))
				   (slot-value-list
				     (slot-value-list
				       (first attribute-description)
				       (slot-value-list attribute-initial-value)
				       'user-defined)))
				  ((or attribute-initial-value
				       attribute-initial-type?)
				   (slot-value-list
				     (slot-value-list
				       (first attribute-description)
				       (if attribute-initial-type?
					   (slot-value-list
					     attribute-initial-value
					     attribute-initial-type?)
					   attribute-initial-value)
				       'user-defined)))
				  (t (slot-value-list
				       (slot-value-list
					 (first attribute-description)
					 nil
					 'user-defined)))))))
		 (reclaim-slot-value attribute-description))
		(t
		 (when system-defined-slot-description?
		   (if name-of-defined-class?
		       (notify-user
			 "~%~% Urgent:  ~
                          A class-specific attribute for ~a ~
                          has the same name (~(~a~)) as a system-defined ~
                          attribute. ~
                          ~% It is extremely important to rename ~
                          the ~a class-specific ~
                          attribute before running this kb or doing any further ~
                          development work to avoid a likely G2 failure."
			 name-of-defined-class? attribute-name attribute-name)
		       (notify-user
			 "~%~% Urgent:  ~
			  A class-specific attribute for an unnamed class ~
                          has the same name (~(~a~)) as a system-defined ~
                          attribute. ~
                          ~% It is extremely important to rename the ~a class-specific ~
                          attribute before running this kb or doing any further ~
                          development work to avoid a likely G2 failure."
			 attribute-name attribute-name)))
		 (setf (cdr attribute-description)
		       (slot-value-cons
			 (slot-value-list
			   'or 'item-or-datum (slot-value-list 'no-item))
			 (cdr attribute-description)))
		 (setq class-specific-attributes-list
		       (nconc class-specific-attributes-list
			      (slot-value-list attribute-description)))))))

    (when indexed-attributes-becoming-overrides?
      (let ((new-indexed-attributes-for-definition
	      (loop for attribute-name
			in indexed-attributes-for-definition
		    unless (memq attribute-name
				 indexed-attributes-becoming-overrides?)
		      collect attribute-name using slot-value-cons)))
	(prepare-for-indexed-attributes-moveage
	  frame
	  indexed-attributes-for-definition
	  new-indexed-attributes-for-definition)
	(reclaim-frame-list indexed-attributes-becoming-overrides?)))

    (loop for (superior-class new-indexed-attributes)
	      in new-superior-indexed-attributes?
	  for superior-class-definition = (class-definition superior-class)
	  for indexed-attributes-for-definition =
	        (indexed-attributes-for-definition superior-class-definition)
	  for new-indexed-attributes-for-definition =
	        (nconc (copy-for-slot-value indexed-attributes-for-definition)
		       (copy-for-slot-value new-indexed-attributes))
	  do
      (prepare-for-indexed-attributes-moveage
	superior-class-definition
	indexed-attributes-for-definition
	new-indexed-attributes-for-definition)
      (change-slot-value superior-class-definition 'class-specific-attributes
			 (class-specific-attributes superior-class-definition)))
    (reclaim-frame-tree new-superior-indexed-attributes?)
    
    (unless change-the-text-of-overrides?
      (change-slot-value
	frame 'class-specific-attributes class-specific-attributes-list))
    (unless (equal default-overrides-list (default-overrides frame))
      (change-slot-value frame 'default-overrides default-overrides-list)))
  (when (consp attribute-descriptions?)
    (reclaim-slot-value-list attribute-descriptions?)))



  
;;; `Process-pre-4.0-capabilities-of-class' shifts the obsolete data service
;;; and data service interface capabilities into the direct-superiors-of-class
;;; slot, and shifts all of the remaining legitimate capabilities into the
;;; instance-configuration slot.  This function is called at load time and
;;; for the pre-4.0 role "change the text of the capabilities-and-restrictions".
;;; Note that the quoted value of a change-of-text currently replaces the old
;;; slot value.  (ghw 3/15/94)

(defun process-pre-4.0-capabilities-of-class
    (frame class-name capabilities-of-class called-from-change-the-text?)
  (let* ((capability-flat-list
	   (nconc (loop for symbol in (car capabilities-of-class)
			collecting symbol using frame-cons)
		  (loop for symbol in (cdr capabilities-of-class)
			collecting symbol using frame-cons)))
	 (former-data-service-capabilities
	   '(gsi-data-service gsi-message-service gfi-data-service
	     g2-to-g2-data-service g2-meter-data-service))
	 (former-data-interface-capabilities
	   '(gsi-interface-configuration g2-to-g2-data-interface
	     gfi-input-interface gfi-output-interface))
	 (present-data-interface-classes
	   '(gsi-interface g2-to-g2-data-interface
	     gfi-input-interface gfi-output-interface))
	 (former-configuration-capabilities
	   '(activatable-subworkspace external-simulation
	     no-manual-connections subworkspace-connection-posts))
	 (chosen-data-interface-capability? nil)
	 (more-than-one-interface-capability? nil)
	 (direct-superiors-of-defined-class?
	   (direct-superiors-of-defined-class frame))
	 (data-service-and-interface-capabilities? nil)
	 (instance-configuration-capabilities? nil))

  ;; The processing of a "change the text of the capabilities-and-restrictions
  ;; attribute" should begin with its list of direct-superiors-of-defined-
  ;; class stripped of former data service and data interface capabilities.
  (when called-from-change-the-text?
    (if (and direct-superiors-of-defined-class?
	     (null (cdr direct-superiors-of-defined-class?))
	     (memq (car direct-superiors-of-defined-class?)
		   '(gsi-interface g2-to-g2-data-interface
		     gfi-input-interface gfi-output-interface)))
	(setq direct-superiors-of-defined-class? (slot-value-list 'object))
	(setq direct-superiors-of-defined-class?
	      (loop for superior in direct-superiors-of-defined-class?
		    when (not (memq superior '(gsi-interface g2-to-g2-data-interface
					       gfi-input-interface gfi-output-interface
					       gsi-data-service gsi-message-service
					       gfi-data-service g2-to-g2-data-service
					       g2-meter-data-service)))
		      collect superior using slot-value-cons))))

  (loop for symbol in capability-flat-list
	for present-symbol = (if (eq symbol 'gsi-interface-configuration)
				 'gsi-interface
				 symbol)
	do
    ;; In the case of multiple data-interface capabilities,
    ;; the last one in the capability list will be selected
    ;; as the sole data-interface-class direct superior.
    (cond ((and (memq symbol former-data-interface-capabilities)
		(loop for superior in direct-superiors-of-defined-class?
		      when (memq present-symbol
				 (class-inheritance-path
				   (class-description superior)))
			return nil
		      finally (return t)))
	   (when chosen-data-interface-capability?
	     (setq more-than-one-interface-capability? t))
	   (setq chosen-data-interface-capability? present-symbol))
	  
	  ((memq symbol former-data-service-capabilities)
	   ;; Omit possible duplicate capabilities.
	   (when (and (not (memq symbol
				 data-service-and-interface-capabilities?))
		      (loop for superior in direct-superiors-of-defined-class?
			    when (memq present-symbol
				       (class-inheritance-path
					 (class-description superior)))
			      return nil
			    finally (return t)))
	     (setq data-service-and-interface-capabilities?
		   (frame-cons
		     symbol data-service-and-interface-capabilities?))))
	  ((memq symbol former-configuration-capabilities)
	   (when (not (memq symbol instance-configuration-capabilities?))
	     (setq instance-configuration-capabilities?
		   (nconc instance-configuration-capabilities?
			  (frame-list symbol)))))
	  (t nil)))

  (cond ((and chosen-data-interface-capability?
	      data-service-and-interface-capabilities?)
	 (setq data-service-and-interface-capabilities?
	       (nconc data-service-and-interface-capabilities?
			(frame-list chosen-data-interface-capability?))))
	(chosen-data-interface-capability?
	 (setq data-service-and-interface-capabilities?
	       (frame-list chosen-data-interface-capability?)))
	(t nil))

  (when data-service-and-interface-capabilities?
    (let* ((new-direct-superior-classes
	     ;; If there is a single data interface capability and the current
	     ;; direct superior class is object, replace it with the data
	     ;; interface.
	     (cond ((and (null (cdr data-service-and-interface-capabilities?))
			 (memq (car data-service-and-interface-capabilities?)
			    present-data-interface-classes)
			 (eq
			   (car direct-superiors-of-defined-class?) 'object))
		    (when called-from-change-the-text?
		      (reclaim-slot-value-list direct-superiors-of-defined-class?)
		      (setq direct-superiors-of-defined-class? nil))
		    (copy-for-slot-value data-service-and-interface-capabilities?))
		   (t (nconc (copy-for-slot-value
			       data-service-and-interface-capabilities?)
			     direct-superiors-of-defined-class?)))))
      (if called-from-change-the-text?
	  (change-slot-value
	    frame 'direct-superiors-of-defined-class new-direct-superior-classes)
	  (initialize-slot-value
	    frame 'direct-superiors-of-defined-class new-direct-superior-classes))
      (when more-than-one-interface-capability?
	(notify-user
	  "The class ~A had more than one data-interface capability. ~
             This situation would make data connection-selection ambiguous. ~
             One has been chosen to be the sole data-interface direct-superior ~
             class, ~A, and the class instances, if any, have had their ~A ~
             attributes set to the default values."
	  class-name chosen-data-interface-capability?
	  chosen-data-interface-capability?)
	(unless called-from-change-the-text?
	  (setq classes-needing-data-interface-initialization
		(frame-cons
		  (frame-list class-name chosen-data-interface-capability?)
		  classes-needing-data-interface-initialization))))
      (reclaim-frame-list data-service-and-interface-capabilities?)))
  
  (when instance-configuration-capabilities?
    (let ((configuration-list nil))
      (loop for symbol in instance-configuration-capabilities?
	    do
	(setq configuration-list
	      (nconc configuration-list
                         (slot-value-list
			   (make-declaration-clause-for-item-configuration
			     symbol t))))
                finally
		  (if called-from-change-the-text?
		      (change-slot-value
			frame 'instance-configuration configuration-list)
		      (initialize-slot-value
			frame 'instance-configuration
			(nconc (instance-configuration frame)
			       configuration-list))))
          (reclaim-frame-list instance-configuration-capabilities?)))

    (reclaim-frame-list capability-flat-list)))





(defun-void read-past-frame-for-kb (character print?)
  (when print?
    (format t "~%; starting reading of frame~%"))
  (if (and new-saved-kb-format-p (char= #\F character))
      (read-past-element-for-kb print?)) ; frame-serial-number?
  (read-past-element-for-kb print?)	; class
  (when (not new-saved-kb-format-p)
    ;; read past old kbs' frame-author-or-authors and time-of-last-edit?
    (read-past-element-for-kb print?)
    (read-past-element-for-kb print?))
  (loop for character = (read-char-for-kb)
	initially
	   (when print?
	     (format t "~%;slots:~%"))
	do (character-case character
	     (#\! (loop-finish))
	     (#\[ (read-past-runtime-data-for-block print?)
		  (loop-finish))
	     (t (unread-char-for-kb character)))
	   (let* ((slot-denotation-or-left-edge (read-element-for-kb nil))
		  slot-name class-qualifier?)
	     ;; May create symbols unnecessarily! Maybe OK?  Could
	     ;; be fixed, but it would be a slight pain.
	     (cond
	       ((fixnump slot-denotation-or-left-edge)
		(when print?
		  (format t "~%; (old format) edges and subblocks:~%")
		  (format t " ~d " slot-denotation-or-left-edge))
		;; "slot-denotation-or-left-edge" is a left edge i.e., an integer.
		;; Read past top, right, bottom edges, and then, for old-format
		;; KBs, the subblocks, which end the reading the frame.
		(read-past-element-for-kb print?)
		(read-past-element-for-kb print?)
		(read-past-element-for-kb print?)
		(loop as first-time? = t then nil
		      for character = (read-char-for-kb-past-spaces)
		      until (char= character #\!)
		      when (and new-saved-kb-format-p first-time?)
			do
			  #+development
			  (cerror "continue" "Error in frame format")
			  ;; Only some local KBs in early 3.0 (before slot
			  ;; group) have this format. These cannot have runtime
			  ;; data.  (Eliminate this test?!)
			  (unread-char-for-kb character)
			  (read-past-element-for-kb print?))
		(loop-finish))
	       (t
		(setq slot-name
		      (unqualified-name slot-denotation-or-left-edge))
		(setq class-qualifier?
		      (class-qualifier slot-denotation-or-left-edge))
		(reclaim-slot-value slot-denotation-or-left-edge)))
	     (when print?
	       (format t
		       (if class-qualifier?
			   "~%; slot ~s::~s:~%"
			   "~%; slot ~s:~%")
		       slot-name class-qualifier?)))
	   (read-past-element-for-kb print?)) ; slot value
  (when print?
    (format t "~%; finished reading frame~%"))
  )



;;; `Def-substitute-for-old-format-name' ... Substitutes should only be given
;;; for names that no longer have format descriptions.

(def-global-property-name substitute-format-name)

(defmacro def-substitute-for-old-format-name
    (original-format-name substitute-format-name)
  ;; add kb-flags as an arg?  See def-substitute-for-old-class!
  `(setf (substitute-format-name ',original-format-name)
	 ',substitute-format-name))

(def-substitute-for-old-format-name
    GRAPH-HORIZONrAL-AXIS-HEADING-TEXT-CELL-FORMAT
    GRAPH-HORIZONtAL-AXIS-HEADING-TEXT-CELL-FORMAT)

;; The first, and thus far only, "old format name" is one that must have been a
;; typo for some time in 1.0, 2.0, or 3.0 G2.  The t in horizontal was
;; apparently misspelled for some time as r.  It has surfaced in the Gensym
;; Helpdesk KBs as of 8/26/94.  (See "/home/helpdesk/Src/help-desk.kb" and
;; required modules, for example, as of this date.)  (MHD 8/26/94)





;;; Finish-reading-format-frame-for-kb is a subfunction of read-frame-for-kb.
;;; It is only called after new-format-frame has been almost fully created,
;;; except for having its name-or-names-for-frame slot set and having been
;;; registered in the frame serial number map (or, for new-saved-kb-format-p,
;;; in kb-object-index-space).

;;; When format-name? is nil, this enforces the constraint that there are never
;;; more than one unnamed formats that are "equivalent"; also in this case, it
;;; was not saved with a name and therefore does not need to have its name-or-
;;; names-for-frame slot to be put.

;;; This function either returns nil or a other than new-format-frame.  When
;;; it returns a frame, other-format-frame, the caller should return it as the
;;; result of read-frame-for-kb after rerouting references to frame to new-
;;; frame (via either object index or frame serial number maps).

;;; When special variable reformat-as-appropriate? is true, that triggers
;;; a reformat using an up-to-date format frame, and the ultimate elimination
;;; of new-format-frame.

;;; If format-name? is non-nil, and (format-change? new-format-frame) has
;;; a value, which should be an integer, that also triggers a reformat using
;;; an up-to-date format frame.  [Note that, at present, in practice this case
;;; could only arise for a 0.9x (ancient) kb that was saved out with a font
;;; map referring to an old obsolete font like HC14. -mhd, 10/4/91].

;;; As of 4.0 (Alpha version after circa 8/26/94), if format-name? is non-nil,
;;; but the name has no corresponding format description, the name that is the
;;; substitute-format-name global symbol property of format-name? is used
;;; instead.  It is a constraint violation for the resulting name to be either
;;; nil or itself lack a corresponding format description.  If it does, G2
;;; doesn't do anything unless a reformat is called for.  Note that if a
;;; reformat is called for (i.e., if reformat-as-appropriate? is true), G2 will
;;; be unable to comply in the case of items using this particular format frame.
;;; In that case, since it would make a difference, it notifies the user on the
;;; logbook that there is a problem with their KB or with G2, and that they
;;; should report this problem to Gensym Customer Support.  At present, we don't
;;; expect this to occur.  If it does, we don't expect it to indicate a serious
;;; problem, but users should be cautioned, mildly.  In development, a
;;; continuable error is signalled whether or not a reformat is requested.

;;; When a merge is being done on top of an old KB in the replacing-system-
;;; tables?=true case, then if new-format-frame differs from the one by
;;; which items were formatted in old kb, new-format-frame then dominates, and
;;; if the above two cases do not apply, the items in the old KB that use
;;; the old format frame continue to use it, but the old format frame's name
;;; is changed to nil, and its old name moves to its format-change? slot.

(defun finish-reading-format-frame-for-kb (new-format-frame format-name?)
  (let ((do-not-note-permanent-changes-p t)
	(other-format-frame?
	  (cond
	    ((null format-name?)
	     (find-existing-equivalent-format-frame new-format-frame))
	    (t
	     (when (null (format-description format-name?))
	       (let ((substitute-format-name?
		       (substitute-format-name format-name?)))
		 (cond
		   ((or (null substitute-format-name?)
			(null (format-description substitute-format-name?)))		    
		    ;; This is not thought to be tremendously serious at this
		    ;; time.  I also don't expect it to occur, but feel
		    ;; there's a chance it might.  It should be rooted out --
		    ;; all calls should be handled by writing new
		    ;; def-subsitute's!  See above.  (MHD 8/26/94)
		    #+development
		    (cerror
		      "Continue"
		      "Warning: An internal constraint has been violated.  A format ~
                      with the unknown name ~A (substitute ~a) was discovered."
		      format-name? substitute-format-name?)
		    (notify-user
		      "Warning: An internal constraint has been violated.  A format ~
                      with the unknown name ~A was discovered. Please report this ~
                      problem to Gensym Customer Support."
		      (or substitute-format-name?
			  format-name?)))
		   (t
		    (setq format-name?
			  substitute-format-name?)))))
	     (cond
	       ((and (or reformat-as-appropriate?
			 (format-change? new-format-frame))
		     ;; make sure we now have a format-description for safety,
		     ;; "it shouldn't happen" that we don't but
		     ;; historical/programmer error could happen:
		     (format-description format-name?))
		(get-or-make-format-frame format-name?))
	       (t
		(get-instance-with-name-if-any 'format-frame format-name?)))))))
    (when				; other-format-frame? should be returned?
	(cond
	  ((null other-format-frame?)
	   (put-name-or-names-for-frame new-format-frame format-name? t)
	   nil)      
	  ((or (null format-name?)
	       (null (find-differences-in-frames-if-any
		       new-format-frame other-format-frame? t)))
	   t)
	  ((or reformat-as-appropriate? (format-change? new-format-frame))
	   ;; The following says to reformat other-format-frame's users:
	   (setf (format-change? other-format-frame?) 0)
	   t)
	  ((or kb-load-case? main-kb-being-read?)
	   (change-slot-value
	     other-format-frame? 'name-or-names-for-frame nil)
	   
	   ;; Bug corrected -- it did not used to do the following at
	   ;; all, resulting in violation of the constraint that the
	   ;; format name was kept in either the format-change? or
	   ;; the name-or-names-for-frame slot!  (MHD 10/3/91)
	   (change-slot-value
	     other-format-frame? 'format-change? format-name?)
	   (put-name-or-names-for-frame new-format-frame format-name? t)
	   nil)
	  (t
	   ;; Bug corrected. (MHD 5/30/95)
	   (change-slot-value
	     new-format-frame 'format-change? format-name?)
	   nil))
      (cond
	;;#+development
	((memq new-format-frame forward-referenced-format-frames)
	 ;; Fixes a temporary problem that was around in Nov/Dec '93 of the 4.0
	 ;; development cycle; for info., see var
	 ;; forward-referenced-format-frames.  (MHD 12/30/93)
	 (change-slot-value new-format-frame 'name-or-names-for-frame nil)
	 (change-slot-value new-format-frame 'format-change? format-name?)
	 (notify-user
	   "This KB has formatting problems! You should load with ~
            with \", BRINGING FORMATS UP-TO-DATE\", and then save. ~
            If you are a customer, please report this to software ~
            support. If you work for Gensym, this KB should not be ~
            released to customers until it's had its formats brought ~
            up-to-date."))
	(t
	 (delete-block-after-reading-kb new-format-frame)))
      other-format-frame?)))

;; The logic for fixing up old format frames that did not have color changes
;; up-to-date when (not (allow-format-frame-color-discrepancies-p)) has been
;; removed.  It was used for the 1.11b -> 2.0, 2.1.  This just means that
;; colors won't be brought up-to-date unless an explicit reformat-as-appropriate?
;; is requested, which brings everything up-to-date.








;;; `Connection-classes-warned-about-for-this-kb' is a gensym-list of classes
;;; for which frameless connection structure instances were encountered.  These
;;; were presumably saved without their definition due to a software bug that
;;; was fixed prior to 4.0 Rev. 0 (Final) as of 6/16/95. (by MHD)
;;;
;;; Warnings describing the problem are issued by read-connection-for-kb calling
;;; warn-of-undefined-connection-subclass-if-appropriate the first time the
;;; problem occurs.  This list is primarily just the mechanism to keep multiple
;;; messages from going out.  It may have a secondary use as an aid to
;;; developers.
;;;
;;; Note that if the message ever fires

(def-kb-specific-variable connection-classes-warned-about-for-this-kb
    kb-load2 nil nil reclaim-gensym-list-function)

(defun warn-of-undefined-connection-subclass-if-appropriate (class)
  (unless (memq class connection-classes-warned-about-for-this-kb)
    (gensym-push class connection-classes-warned-about-for-this-kb)
    (let* ((problem
	     (tformat-text-string
	       "WARNING: When this KB (~s) was last saved, ~A was a ~
         defined subclass of CONNECTION, but the class definition ~
         was not saved with that KB due in part to a software ~
         problem.  Unfortunately, instances of this class cannot ~
         be properly restored.  "
	       namestring-for-kb-being-read
	       class))
	   (solution
	     (tformat-text-string
	       "Therefore, instances of the class ~A within this KB will ~
         be turned into instances of the class CONNECTION.  ~
         If you can restore the original definition of ~A, you ~
         may wish to abandon the current KB, and then merge this ~
         KB into a KB that contains the restored definition."
	       class class)))
      (notify-user "~a~a" problem solution)
      (reclaim-text-string problem)
      (reclaim-text-string solution))))

;; Long constant strings a problem in Chestnut?  These are at least safely below
;; the length of other constant strings in this file. (MHD)


(defun-simple read-connection-for-kb ()
  (let (connection frame-serial-number)
    (cond
      (new-saved-kb-format-p
       (setq frame-serial-number (read-element-for-kb nil))
       (setq connection (get-frame-given-frame-serial-number frame-serial-number))
       (when (null connection)
	 (setq connection (make-connection))
	 (frame-serial-number-setf (frame-serial-number-for-connection connection)
				   (increment-current-frame-serial-number))
	 (enter-frame-into-frame-serial-number-map frame-serial-number connection)))
      (t (setq connection (make-connection)) 		
	 (frame-serial-number-setf (frame-serial-number-for-connection connection)
				   (increment-current-frame-serial-number))
	 (store-next-kb-object connection)))
    
    (setf (connection-frame-or-class connection)
	  (let ((connection-frame-or-class (read-element-for-kb nil)))
	    (cond
	      ((symbolp connection-frame-or-class)
	       (let ((class
		       (or (if class-name-conflicts
			       (second (assq connection-frame-or-class
					     class-name-conflicts)))
			   (if (and (substitute-class connection-frame-or-class)
				    (null (class-definition connection-frame-or-class)))
			       (substitute-class connection-frame-or-class))
			   connection-frame-or-class)))
		 (cond
		   ;; Recover from a bug in earlier G2's:  (MHD 5/16/95)
		   ((null (class-description class)) ; defined class or trouble!
		    (warn-of-undefined-connection-subclass-if-appropriate class)
		    ;; So, as we've just told the user (if this is the first
		    ;; time for this class), we're going to reclassify their
		    ;; connection as strictly a CONNECTION.  Fortunately, there
		    ;; are _NO_ slots in a (frameless) connection structure, as
		    ;; we have here, that are class-dependent.  Isn't life
		    ;; good?!  Note that this is understood to be exceedingly
		    ;; rare.  Fixed by get-connections-in-modules-a-list coming
		    ;; into use, in KB-MERGE. (MHD 6/16/95)
		    'connection)
		   (t class))))
	       (t (setf (connection-for-this-connection-frame
			  connection-frame-or-class)
		       connection)
		  connection-frame-or-class))))
    
    (setf (input-end-object connection) (read-element-for-kb nil))
    (setf (output-end-object connection) (read-element-for-kb nil))
    (setf (input-end-position connection)
	  (read-element-for-kb nil))
    (setf (output-end-position connection)
	  (read-element-for-kb nil))
    (setf (delta-or-deltas connection) (read-element-for-kb nil))
    (let ((connections-flags (read-element-for-kb nil)))
      ;; Used to be called connection-not-directed?
      ;; The value was nil or t, and is now represented
      ;; by frame-flag 1
      (setf (connection-flags connection)
	    (cond
	      ((null connections-flags) 0)
	      ((eq connections-flags t) 1)
	      #+development
	      ((not (fixnump connections-flags))
	       (cerror "continue" "Strange value as connection-flag. See ML"))			   
	      (t (logandf connections-flags
			  savable-connection-flags)))))
    (when (connection-attributes-saved-p)
      (setf (connection-attributes-plist connection)
	    (read-element-for-kb nil))

      (let ((connection-frame-or-class
	      (connection-frame-or-class connection)))
	(when (framep connection-frame-or-class)
	  (copy-unsaved-slots-from-connection-to-connection-frame
	    connection connection-frame-or-class))))
    (when (and (eq type-of-file-being-read 'kb-save-with-runtime-data)
	       (transient-connection-p connection))
      (unless warmbooting?
	(delete-connection-after-reading-kb connection)))
    #+development
    (test-assertion
      (and (input-end-object connection)
	   (output-end-object connection)
	   (connection-frame-or-class connection)))
    connection))

(defun-void read-past-connection-for-kb (print?)
  (when new-saved-kb-format-p
    (read-past-element-for-kb print?))	; frame-serial-number?
  (read-past-element-for-kb print?)	; class
  (read-past-element-for-kb print?)	; input-end-object
  (read-past-element-for-kb print?)	; output-end-object
  (read-past-element-for-kb print?)	; input-end-position
  (read-past-element-for-kb print?)	; output-end-position
  (read-past-element-for-kb print?)	; delta-or-deltas
  (read-past-element-for-kb print?)	; connections-flags
  (when (connection-attributes-saved-p)
    (read-past-element-for-kb print?)))	; connection-attributes-plist



(defun-simple read-frame-or-connection-reference-for-kb (character)
  (let* ((frame-serial-number (read-element-for-kb nil))
	 (frame-or-connection?
	   (get-frame-given-frame-serial-number frame-serial-number))
	 (class?		; note that nil can't be a class
	   (if (char= character #\G) (read-element-for-kb nil))))
    (or frame-or-connection?
	(progn 
	(cond
	  (class?		; <=> G case
	   (cond
	     ((if class-name-conflicts
		  (second (assq class? class-name-conflicts)))
	      (setq class? (second (assq class? class-name-conflicts))))
	     ((and (substitute-class class?)
		   (null (class-definition class?)))
	      (setq class? (substitute-class class?))))
	   ;;pbk check for title-block etc...
	   (when (eq class? 'table)
	     (setq class? 'table-item))
	   ;; GENSYMCID-758: G2 abort when loading gsi_exam.kb
	   (when (null (class-description class?))
	     (kb-error "Cannot find frame reference of class ~a." class?))
	   (setq frame-or-connection?
		 (make-frame-without-computed-initializations
		   (class-description class?)
		   nil ; (copy-frame-serial-number new-frame-serial-number)
		   nil))
	   (when (frame-of-class-p frame-or-connection? 'format-frame)
	     ;; for info, see notes by def of the variable; should not
	     ;; be here in non-development!
	     (gensym-pushnew frame-or-connection? forward-referenced-format-frames)))
	  ((char= character #\H)
	   #+development
	   (cerror "continue" "Error reading H reference ~d" frame-serial-number))
	  (t			; <=> I case
	   (let ((connection (make-connection)))
	     ;; "connection" here means a connection structure, not a
	     ;; frame
	     (frame-serial-number-setf (frame-serial-number-for-connection connection)
				       (increment-current-frame-serial-number))
	     (setq frame-or-connection? connection))))
	(enter-frame-into-frame-serial-number-map frame-serial-number frame-or-connection?)
	  frame-or-connection?))))


(defun-void read-past-frame-or-connection-reference-for-kb (character print?)
  (read-past-element-for-kb print?)	; frame serial number
  (when (char= character #\G)		; class in #\G case
    (read-past-element-for-kb print?)))
  





;;; `Read-element-for-kb' ... returns nil if it reads an E (end-of-kb).

(defun-simple read-element-for-kb (top-level-element?)
  (let* ((integer? (read-integer-for-kb-if-present))
	 (character (read-char-for-kb)))
    (cond
      (integer?
       (character-case character
	 ((#\S #\' #\` #\: #\,)
	  (read-symbol-or-string-for-kb integer? character))
	 ((#\+ #\-) integer?)		; signed already
	 (#\( (incff previous-timestamp? integer?))
	 (#\) (decff previous-timestamp? integer?))
	 (#\W
	    (finish-reading-managed-array-for-kb integer?))
	 (#\O				; new in 4.0 (MHD 5/16/94)
	    (finish-reading-managed-float-array-for-kb integer?))
	 (t
	   (cond
	     ((and (not new-saved-kb-format-p)
		   (or (char= character #\P) (char= character #\M)))
	      ;; Float format in old (Pre-3.0) KBs only.
	      (finish-reading-slot-value-float
		integer? character
		(not (eql integer? 0))))
	     (t
	      (unless (char= character #\space) ; opt.
		(unread-char-for-kb character))
	      (get-object-from-index-space
		kb-object-index-space integer?))))))
      (t
       (character-case character
	 (#\N nil) (#\T t) (#\Z 0) (#\X no-value) (#\# simulation-no-value)
	 (#\{ most-negative-fixnum)
	 (#\L (read-list-element-for-kb))
	 ((#\G #\H #\I) (read-frame-or-connection-reference-for-kb character))
	 ((#\F #\Y) (read-frame-for-kb character top-level-element?))
	 (#\C (read-connection-for-kb))
	 ((#\P #\M) (read-slot-value-float-for-kb-from-binary character))
	 (#\B (read-byte-code-body-for-kb))
	 (#\K (read-element-for-kb nil))
	 (#\J (setq new-saved-kb-format-p t)      
	      (read-element-for-kb nil))
	 (#\E nil)
	 (#\$ (let ((symbol (read-element-for-kb nil)))
		(setf (type-of-syntactic-anomaly symbol) 'numeric)
		symbol))
	 (#\& (setq previous-timestamp? (read-previous-timestamp-for-kb)))
	 (#\A (read-readable-element-for-kb)) ; for kbs older than 2/6/90
	 (#\* (let ((char (read-char-for-kb)))
		(cond ((or (char= char #\2) ; used *3/*4 instead of *1/*2 for a time 
			   (char= char #\4) ;   in 4.0 development.  Only #\2 needs
			   )		;   to remain here. (MHD 12/17/93)
		       nil)
		      (t
		       #+development
		       (cerror "continue" "bad character sequence: *~c" character)))))
	 (#\% (read-aggregate-evaluation-value-for-kb))
	 (#\U (read-truth-value-for-kb))
	 (#\? (read-long-for-kb))
	 (#\^ (read-legacy-long-for-kb))
	 (#\~ (slot-value-list 'frame-denotation (read-element-for-kb nil)))
	 (#\| (read-user-mode-alias-for-kb))
	 (t (abort-on-bad-kb character)))))))

;; Keep this, and its subfunctions and macros, in synch with
;; read-past-element-for-kb.

;; Modified so that this gets the first character with
;; read-char-for-kb-past-spaces.  This means it does not have to handle #\space,
;; #\Newline, or #\; as a character.  It also means that there's no risk of
;; overrecursion, which the previous implementation could do.  I am also at this
;; time fixing the L (list) element reader to read past space between elements.
;; These modifications are being done for 4.0.  (MHD 9/30/92)






;;; `Read-past-element-for-kb' can be called whenever it is appropriate to call
;;; (read-element-for-kb nil).  It reads the same number of characters as
;;; read-element-for-kb, does not permanently allocate any storage, and has no
;;; useful value.  It uses the stream read-kb-stream, and the environment of
;;; read-char-for-kb.
;;;
;;; Read-past-element-for-kb has some side effects that cannot be avoided.  In
;;; particular, (1) if reading past runtime data and not printing, then frames,
;;; connections, and forward references thereto are created; and (2) symbols
;;; read in are always added to index spaces.
;;;
;;; This allows calls to read-past-element-for-kb to be interleaved with calls
;;; to read-element-for-kb.
;;;
;;; The creation of frames and connections is done when reading past runtime
;;; data to ensure that references back to them will work out later in the
;;; reading process.  When this is called from read-past-runtime-data-for-kb and
;;; print? is nil, the special variable
;;; `create-frames-and-connections-reading-past?', which is globally nil, is
;;; bound non-nil.  In many cases, such frames read in will be transient, and
;;; will therefore be disposed of by other code.  But they could also be frames
;;; that are to be pointed to by non-runtime data.

;;; The handling of symbols is necessary to ensure that object index spaces
;;; later in the KB could are valid.  The space allocated for the interning of
;;; by this process are never reclaimed.
;;;
;;; Note that it is also frequently necessary to call read-element-from-kb to
;;; get a count of the number of elements to read past.

(defvar create-frames-and-connections-reading-past? nil)

(defun-void read-past-element-for-kb (print?)
  (let* ((integer? (read-integer-for-kb-if-present))
	 (character (read-char-for-kb)))
    (cond
      (integer?
       (character-case character
	 ((#\S #\' #\` #\: #\,)
	  (let ((string-or-symbol
		  (read-symbol-or-string-for-kb integer? character)))
	    (when print?
	      (format t "~% ~s " string-or-symbol)
	      (case character
		(#\S (format t "; string~%"))
		((#\' #\:)
		 (format t "; index = ~d~%"
			 (last-assigned-index kb-object-index-space)))
		(t
		 (format t "; not interned in index space~%"))))
	    (unless (symbolp string-or-symbol)
	      (reclaim-text-string string-or-symbol))))
	 (( #\+ #\- #\) #\( )
	  (when print? 
	    (when (not (or (char= character #\+)
			   (char= character #\-)))
	      (format t "~c"  character))
	    (format t " ~d " integer?)))
	 ((#\W #\O #+not-presently-allowed #\V)	; O is new for 4.0 (MHD 6/14/94)
	  (when print? (format t "~% ~c " character))
	  (loop repeat integer?
		do (read-past-element-for-kb print?))
	  (when print?
	    (format t "; end ~c~%" character)))
	 (t
	   (cond
	     ((and (not new-saved-kb-format-p)
		   (memberp character '(#\P #\M)))
	      (when print?
		(format t "~% ~d ~c " integer? character))
	      (read-past-element-for-kb print?))
	     (t
	      (unless (char= character #\space) ; opt.
		(unread-char-for-kb character))
	      (when print?
		(format t "~% ~d ; ~s~%"
			integer?
			(get-object-from-index-space
			  kb-object-index-space integer?))))))))
      (t
       (when print?
	 (format t "~% ~c" character))
       (character-case character
	 ((#\N #\T #\Z #\X #\E #\#))
	 ((#\$ #\K #\J)
	  ;; miscellaneous single-subelement cases
	  (read-past-element-for-kb print?))
	 (#\L (when print?
		(format t "; start of List element~%"))
	      (read-past-list-element-for-kb print?)
	      (when print?
		(format t "; end of List element~%")))
	 ((#\F #\Y)
	  (if (and (not print?)
		   create-frames-and-connections-reading-past?)
	      (read-frame-for-kb character nil)
	      (read-past-frame-for-kb character print?)))
	 ((#\G #\H #\I)
	  (if (and (not print?)
		   create-frames-and-connections-reading-past?)
	      (read-frame-or-connection-reference-for-kb character)
	      (read-past-frame-or-connection-reference-for-kb character print?)))
	 (#\C
	    (if (and (not print?)
		     create-frames-and-connections-reading-past?)
		(read-connection-for-kb)
		(read-past-connection-for-kb print?)))
	 ((#\P #\M)
	  (read-past-slot-value-float-for-kb-from-binary character print?))
	 (#\B (read-past-byte-code-body-for-kb print?))
	 (#\& (read-past-previous-timestamp-for-kb print?))	
	 (#\A (read-past-readable-element-for-kb print?))
	 (#\% (read-past-aggregate-evaluation-value-for-kb print?))
	 (#\* (when print?
		(format t "~%~c~c~%" #\* (read-char-for-kb)))))))))

;; Consider having read-past-element-for-kb be able to return either a symbol,
;; an integer, or nil, thus eliminating the need to call read-element-for-kb
;; from within the recursive descent of this function.




;;; Reading aggregate evaluation-values from kb's. The function
;;; `read-aggregate-evaluation-value-for-kb' knows that the
;;; internal structure of eval structs and sequence is the same (from
;;; the storage perspective).  See `write-aggregate-evaluation-value-for-kb'
;;; for more.

(defun-simple read-aggregate-evaluation-value-for-kb ()
  (let ((aggregate-type (read-element-for-kb nil)))
    (read-element-for-kb nil) ; throw away ref count because we will 
                              ; elimate sharing of structure in parts through
                              ; a save and load
    (macrolet ((prepare-to-rendezvous-frame-in-aggregate ()
		 `(progn
		    #+development
		    (when (or (null frame-being-read?)
			      (null slot-description-for-slot-value-being-read?))
		      (cerror "kb-load2.lisp" "kb read error"))
		    (let ((cons-holding-frame?
			    (car
			      (member frame-being-read?
				      frames-for-rendezvous-in-aggregate-values?
				      :test 'car-eq))))
		      (if cons-holding-frame?
			  ;; Push it onto the slot-description-list if it's not
			  ;; already there
			  (progn
			    (frame-serial-number-setf (second cons-holding-frame?)
						      (current-frame-serial-number))
			    (gensym-pushnew slot-description-for-slot-value-being-read?
					    (third cons-holding-frame?)))
			  (setq frames-for-rendezvous-in-aggregate-values?
				(gensym-cons
				  (gensym-list
				    frame-being-read?
				    (copy-frame-serial-number
				      (current-frame-serial-number))
				    (gensym-list
				      slot-description-for-slot-value-being-read?))
				  frames-for-rendezvous-in-aggregate-values?)))))))
      (loop with length = (-f (read-element-for-kb nil)
			      (if (evaluation-aggregates-contain-frame-serial-numbers)
				  1 0))
	    with managed-array = (allocate-managed-array length)
	    for index from (case aggregate-type
			     (sequence (evaluation-sequence-first-element-index))
			     (structure (estructure-first-attribute-index)))
		      below length
	    for next-character = (read-char-for-kb-1)
	    do
	(cond ((char= next-character '#\~)
	       ;; The twiddle char indicates that the next element read will be
	       ;; a frame denotation which can be either a uuid text-string or
	       ;; a name symbol.  We put the denotation in an slot-value-list with
	       ;; the symbol 'frame-denotation as its car.  The once-only post-
	       ;; loading function, rendezvous-frame-denotations-in-aggregate-
	       ;; evaluation-values is in charge of rendezvousing.
	       (let ((element (read-element-for-kb nil)))
		 (setf (managed-svref managed-array index)
		       (slot-value-list 'frame-denotation element))
		 (prepare-to-rendezvous-frame-in-aggregate)))
	      (t
	       (unread-char-for-kb next-character)
	       (let ((element (read-element-for-kb nil)))
		 (cond ((and (framep element)
			     (transient-p element)
			     (not warmbooting?))
			(setf (managed-svref managed-array index) nil))
		       (t
			;; Note this is breaking the constraint for seqs/structs
			;; that as of 6.0, they can never have items in them,
			;; but instead should use an item-reference.  However,
			;; there is a very tricky bug that has to do with the
			;; subtleties of how item-references are dealt with
			;; during load-time {see HQ-4173702}, so we stick the
			;; real item in here and we'll replace it with an
			;; item-reference later (post-loading time).  Note that
			;; this is really not fixing this the right way as it's
			;; incurring a performance hit, namely every seq/struct
			;; with an item in it will cause a push onto a list and
			;; then the entire seq/struct will need to be traversed
			;; to replace the item with its item-reference. The
			;; better way to fix it would be to make the
			;; saving/loading of item-references work correctly.  If
			;; performance becomes an issue, we can try only doing
			;; this for frames that really need it {haven't had the
			;; final put-uuid called yet - maybe can check whether
			;; frame-flags have been read for it?}, or push more
			;; info onto the list so we don't have to traverse the
			;; whole seq/struct in the post-loading-function.
			;; -dkuznick, 1/16/02
			(when (framep element)
			  (prepare-to-rendezvous-frame-in-aggregate))
			(setf (managed-svref managed-array index) element))))))
	       finally
	       (let ((aggregate-evaluation-value
		       (eval-cons managed-array aggregate-type)))
		 (setf (aggregate-evaluation-value-reference-count
			 aggregate-evaluation-value)
		       1)
		 (return aggregate-evaluation-value))))))



(defun read-past-aggregate-evaluation-value-for-kb (print?)
  ;; once for the aggregate value type (structure or sequence)
  (read-past-element-for-kb print?)
  ;; the other for ref-count
  (read-past-element-for-kb print?)
  (loop with len = (read-element-for-kb nil)
	;; GENSYMCID-666: G2 abort when loading snapshot kb without selecting warmboot afterwards
	for i from 2 upto len ; old: below len
	do (read-element-for-kb nil)))




;;; The macro `read-gensym-float-for-kb-from-binary' returns a raw gensym float,
;;; after reading it from the KB.  Character is either P or M, and determines
;;; how the rest of the characters from the current KB input should be read.  It
;;; should only be called within a temporary float context.
;;;
;;; This is intended to be used a subfunction of the higher level reader
;;; functions read-slot-value-float-for-kb-from-binary and
;;; finish-reading-managed-float-array-for-kb.  

(def-substitution-macro read-gensym-float-for-kb-from-binary (character)
  (if (char= character #\P)
      (let ((x1 0) (x2 0) (x3 0) (x4 0))
	(declare (type fixnum x1 x2 x3 x4))
	(read-binary-word-for-kb x1 x2)
	(read-binary-word-for-kb x3 x4)
	(decode-double-float x1 x2 x3 x4))
      (coerce-to-gensym-float (read-element-for-kb nil))))



;;; `Read-slot-value-float-for-kb-from-binary' ...
;;; `Read-past-slot-value-float-for-kb-from-binary' ...

(defun-simple read-slot-value-float-for-kb-from-binary (character)
  (with-temporary-gensym-float-creation reading-float
    (if (char= character #\P)
	(let ((x1 0) (x2 0) (x3 0) (x4 0))
	  (declare (type fixnum x1 x2 x3 x4))
	  (read-binary-word-for-kb x1 x2)
	  (read-binary-word-for-kb x3 x4)
	  (make-slot-value-float-macro
	    (decode-double-float x1 x2 x3 x4)))
	(make-slot-value-float-macro
	  (coerce-fixnum-to-gensym-float (read-element-for-kb nil))))))

(defun-void read-past-slot-value-float-for-kb-from-binary (character print?)
  (cond ((char= character #\P)
	 (read-past-binary-word-for-kb print?)
	 (read-past-binary-word-for-kb print?))
	(t
	 (read-past-element-for-kb print?))))




;;; The function `finish-reading-managed-float-array-for-kb' is called by
;;; read-element-for-kb to read a managed-float-array element, which is a new
;;; kind of top-level element that was introduced for G2 4.0.  It returns a
;;; managed array after reading it from the current KB.  See
;;; write-managed-float-array-for-kb further documentation and information
;;; on the format of this element.

(defun finish-reading-managed-float-array-for-kb (length)
  (declare (type fixnum length))
  (finish-reading-into-managed-float-array-for-kb
    (allocate-managed-float-array length)
    length))


(defun finish-reading-into-managed-float-array-for-kb (managed-float-array length)
  (declare (type fixnum length))
  (loop with i fixnum = 0
	until (=f i length)
	do (with-temporary-gensym-float-creation
	       read-managed-float-array-for-kb
	     (loop repeat (minf 500 (-f length i))
		   as char = (read-char-for-kb-past-spaces)
		   do (setf (managed-float-aref managed-float-array i)
			    (read-gensym-float-for-kb-from-binary char))
		      (incff i)))
	finally (return managed-float-array)))


;;; `Finish-reading-managed-array-for-kb' ...

(defun finish-reading-managed-array-for-kb (length)
  (declare (type fixnum length))
  (finish-reading-into-managed-array-for-kb
    (allocate-managed-array length)
    length))


;;; `Finish-reading-into-managed-array-for-kb' ...

(defun finish-reading-into-managed-array-for-kb (managed-array length)
  (declare (type fixnum length))
  (loop as i from 0 below length
	do (setf (managed-svref managed-array i)
		 (read-element-for-kb nil))
	finally (return managed-array)))




;;; `Read-previous-timestamp-for-kb' ...
;;; `Read-past-previous-timestamp-for-kb' ...

(defun-simple read-previous-timestamp-for-kb ()
  (with-temporary-gensym-float-creation reading-float
    (convert-unix-time-to-gensym-time	       
      (let ((x1 0) (x2 0) (x3 0) (x4 0))
	(declare (type fixnum x1 x2 x3 x4))
	(read-binary-word-for-kb x1 x2)
	(read-binary-word-for-kb x3 x4)
	(decode-double-float x1 x2 x3 x4)))))

(defun-void read-past-previous-timestamp-for-kb (print?)
  (read-past-binary-word-for-kb print?)
  (read-past-binary-word-for-kb print?))



;;; `Read-readable-element-for-kb' ... is really only intended to handle numbers
;;; and symbols or strings that don't have spaces, and that appear all on the
;;; same, i.e., the current, line.  This is only for KBs older than 2/6/90,
;;; pre-3.0 KBs, where it is thought that that suffices.  Originally, it was
;;; intended to handle all Lisp READ'able elements, i.e., anything the default
;;; Lisp reader could handle, but that is no longer the requirement. [as of 3.0,
;;; and later]
;;;
;;; This returns floats as slot-value floats.  Anything else would be as Lisp
;;; would return it.

(defun read-readable-element-for-kb ()
  ;; It should be possible to do the following in a temporary gensym float
  ;; creation context, to avoid leaking floats created during number reading.
  ;; However, this appears to cause corruption in Lucid for unknown reasons.
  ;; DIAGNOSE!	
  (let ((readable-element 
	  (twith-output-to-then-use-of-gensym-string
	    (loop as character = (read-next-char-for-kb)
		  until (char= character #\space)
		  do (twrite-char character)
		  finally
		    (return
		      (read-from-string
			current-gensym-string nil nil
			:end fill-pointer-for-current-gensym-string)
                      ;; GHW wanted to read a string from here, presumably to
                      ;; get rid of READ, but that can't be done if we want to
                      ;; really handle old KBs.  Sent mail to her. (MHD 4/17/96)
		      )))))
    (cond
      ((gensym-float-p readable-element)
       (make-slot-value-float-macro readable-element))
      ((floatp readable-element)
       (make-slot-value-float-macro (coerce-to-gensym-float readable-element)))
      (t readable-element))))


(defun-void read-past-readable-element-for-kb (print?)
  (loop as character = (read-next-char-for-kb)
	when print?
	  do (format t "~c" character)
	until (char= character #\space)
	finally
	  (when print? (format t "; end readable element~%"))))


;; Note that this function will bomb out if there is data corruption in the KB
;; file when a number is being read.  A bomb out might also occur because
;; read-from-string is used (?).  Fix this!

;; Is it okay for temporary bignum contexts to be nested, as they would be within
;; the recursive call to read-element-for-kb from finish-reading-slot-value-float?

;; It is assumed that read-next-char-for-kb and finish-reading-slot-value-float (and
;; also read-element-for-kb, as called from finish-reading-slot-value-float), when
;; used here within a-temporary bignum or gensym floatcreation context, do no
;; extraneous work that might store temporary structures (e.g., do not update the
;; file progress display, though they may update the fixnum in its
;; progress-through-file-in-characters slot).

;; Note that this does some unnecessary work when it is called in contexts where
;; only certain types of elements may be found.  For example, when called from
;; read-kb, only a frame or end-of-kb element may be found.

;; Note that a class definition with no name-of-defined-class slot or a system
;; frame or format frame with no name-or-names-for-frame slot will be handled
;; like any ordinary frame.

;; A frame is reconstructed by first making the frame (with default slot values)
;; and then reading and "putting" non-default slot values.  The alternative of
;; accumulating non-default slot initializations before calling make-frame,
;; though it would save a little slot-value-initialization time, requires some
;; (recyclable) consing and, even worse, doesn't work in certain circular
;; references cases.

;; This assumes that text strings are usable as symbol names.

;; Instead of having the equivalent of put-slot-value in-line, consider having a
;; macro defined in module FRAMES that handles everything except where the assq
;; returns nil.  Note, incidentally, that the lookup structure is not kept in a
;; loop variable because reading a slot value could possibly change it.

;; Consider doing a copy-list of subblocks, and recycling the original, in order
;; to get a cdr-coded list in implementations that provide it.

;; Cdr-coding is a bad idea for G2, since setf CDR becomes a consing operation
;; for cdr-coded conses.  -jra 5/29/91




;;; The function `read-byte-code-body-for-kb' reads and returns a byte-code-body
;;; read from the currently open kb.  This function is called after the
;;; character B, which is the marker for byte-code-bodies, has already been read
;;; from the file.

(declare-forward-reference convert-description-list-to-managed-array function)

(defun-simple read-byte-code-body-for-kb ()
  (let* ((body-vector-length (read-element-for-kb nil))
	 (length-in-words (ceilingf-positive body-vector-length 4))
	 (body-vector (allocate-byte-vector body-vector-length))
	 (constant-vector? nil)
	 constant-vector-length?
	 environment-description
	 free-reference-vector-length?
	 (free-references? nil)
	 (left-half 0) (right-half 0)
	 environment-description-as-read?)
    (declare (type fixnum length-in-words left-half right-half))
    (loop for i from 0 below (*f length-in-words 4) by 4
	  do
      (read-binary-word-for-kb left-half right-half)
      (setf (byte-vector-aref body-vector i)
	    (logandf right-half 255))
      (setf (byte-vector-aref body-vector (+f i 1))
	    (ashf right-half -8))
      (setf (byte-vector-aref body-vector (+f i 2))
	    (logandf left-half 255))
      (setf (byte-vector-aref body-vector (+f i 3))
	    (ashf left-half -8)))
    (setq constant-vector-length? (read-element-for-kb nil))
    (when constant-vector-length?		
      (setq constant-vector? (allocate-managed-simple-vector
			       constant-vector-length?))
      (loop for index from 0 below constant-vector-length? do
	(setf (svref constant-vector? index) (read-element-for-kb nil))))
    (setq environment-description-as-read? (read-element-for-kb nil))
    (cond ((consp environment-description-as-read?)
	   (setq environment-description
		 (convert-description-list-to-managed-array environment-description-as-read?))
	   (reclaim-slot-value environment-description-as-read?))
	  (t
	   (setq environment-description environment-description-as-read?)))
    
    (setq free-reference-vector-length? (read-element-for-kb nil))
    (when free-reference-vector-length?
      (setq free-references? (allocate-managed-simple-vector
			       free-reference-vector-length?))
      (loop for index from 0 below free-reference-vector-length? do
	(setf (svref free-references? index) (read-element-for-kb nil))))
    (let ((byte-code-body (make-byte-code-body
			    body-vector-length
			    body-vector
			    constant-vector?
			    environment-description
			    free-references?)))
      (when loading-compiled-kb-p
	(add-new-byte-code-body byte-code-body))
      byte-code-body)))

(defun-void read-past-byte-code-body-for-kb (print?)
  (let* (length-in-words constant-vector-length?
	 body-vector-length free-reference-vector-length?)
    (setq body-vector-length (read-element-for-kb nil))
    (setq length-in-words (ceilingf-positive body-vector-length 4))
    (when print?
      (format t "~%; Byte code body; ~d words:~%" length-in-words))
    (loop repeat length-in-words
	  do (read-past-binary-word-for-kb print?))
    (setq constant-vector-length? (read-element-for-kb nil))
    (when constant-vector-length?
      (when print?
	(format t "~%; Byte code body constant vector; ~d elements long:~%"
		constant-vector-length?))
      (loop repeat constant-vector-length?
	    do (read-past-element-for-kb print?)))
    (when print?
      (format t "~%; environment description:~%"))
    (read-past-element-for-kb print?)
    (setq free-reference-vector-length? (read-element-for-kb nil))
    (when free-reference-vector-length?
      (when print?
	(format t "~%; Free reference vector; ~d elements long:~%"
		free-reference-vector-length?))
      (loop repeat free-reference-vector-length?
	    do (read-past-element-for-kb print?)))))





;;;; Printing KB Files





#+development
(progn					; around this whole section


;;; `32r' ... Given a number-or-string, interprets its characters as a base 32
;;; representation of a number, which it returns.  Given a number, it returns
;;; it as a string containing that number written in base 32.
;;;
;;; Junk is allowed at the end of strings.  For instance, "e7+" works as well as
;;; "e7+".  If a string is given that does not start with any number of spaces
;;; followed by a base 32 number, this returns nil.
;;;
;;; When this returns a string, the letters are always in lower case, and there
;;; are no leading or trailing spaces.
;;;
;;; This is intended to be used in #+development environments only.
  
(defun 32r (number-or-string)
  (if (gensym-string-p number-or-string)
      (parse-integer number-or-string :radix 32 :junk-allowed t)
      (format nil "~(~32r~)" number-or-string)))


;;; Print-kb prints the KB file with the given pathname to either the file
;;; specified, if any, or to the standard output.... gensym-pathname-to-read,
;;; and gensym-pathname-to-write?, if non-nil, may be anything coercible to a
;;; gensym pathname.

(defun-allowing-unwind print-kb
    (gensym-pathname-to-read &optional gensym-pathname-to-write?)
  (handling-gensym-file-errors
    (protected-let ((namestring-for-file
		      (gensym-namestring gensym-pathname-to-read)
		      (reclaim-text-string namestring-for-file)))
      (g2-stream-with-open-stream
        (read-kb-stream namestring-for-file
			:direction :input
			:element-type string-char-without-os-newline-translations)
	(if (null read-kb-stream)
	    (reject-gensym-pathname-to-read namestring-for-file)
	    (let ((output-stream? nil)
		  (normal-exit? nil))
	      (unwind-protect
		   (let ((*standard-output*
			   (or (if gensym-pathname-to-write?
				   (setq output-stream?
					 (open
					   gensym-pathname-to-write?
					   :direction :output)))
			       *standard-output*)))
		     (protected-let*
			 ((truename 
			    (gensym-truename gensym-pathname-to-read)
			    (reclaim-gensym-pathname truename))
			  (namestring-for-kb-being-read
			    (gensym-namestring truename)
			    (reclaim-text-string namestring-for-kb-being-read))
			  (name-text-string-for-kb-being-read  ; used by abort-on-bad-kb
			    (copy-text-string ; convert charset here!
			      namestring-for-kb-being-read)
			    (reclaim-text-string
			      name-text-string-for-kb-being-read))
			  (number-of-kb-lines-so-far 0))
		       (print-current-kb-file-to-standard-output)
		       (setq normal-exit? t)))
		(when (not normal-exit?)
		  (format (or output-stream? t) "~%***~%Reading aborted.~%***~%"))
		(when output-stream?
		  (close output-stream?))))))))) ; does NOT delete the file



(defun print-current-kb-file-to-standard-output ()
  (let* ((new-saved-kb-format-p nil)
	 (kb-uses-crlf-p nil)
	 (#.(clear-text-kb-format-p-variable) nil)
	 (next-character-for-kb? nil)
	 (read-kb-buffer-length 0)
	 (read-kb-buffer-index 0)
	 (base-reference nil)
	 (kb-flags kb-flags)
	 (kb-object-index-space (make-index-space nil nil))
	 (comment-string-or-t? nil))
    (unless (setq comment-string-or-t?
		  (read-format-identifier-for-kb))
      (abort-on-bad-kb))
    (format t "~%KB: ~s" namestring-for-kb-being-read)
    (when (text-string-p comment-string-or-t?)
      (format t "~%Comment String: ~s~%" comment-string-or-t?))
    (read-past-initial-plist )
    (format t "~%~%")
    (loop for character = (read-char-for-kb-past-spaces)
	  until (char= character #\E)
	  do (unread-char-for-kb character)
	     (read-past-element-for-kb t))
    (read-past-final-plist)
    (reclaim-index-space kb-object-index-space)))

(defun-void read-past-initial-plist ()
  (let ((initial-plist (read-element-for-kb t)))
    (setq kb-flags (or (getf initial-plist 'kb-flags) 0))
    (setq base-reference
	  (if new-saved-kb-format-p
	      (modf
		(getf initial-plist 'current-frame-serial-number)
		base-modulus)
	      nil))
    (format t "~%Plist: ~s" initial-plist)
    (reclaim-slot-value initial-plist)))

(defun-void read-past-final-plist ()
  (format t "~%~%; Final Plist~%")
  (read-past-element-for-kb t))

) ; end #+development







;;;; Ghost Definitions



;;; The function `read-ghost-definitions' reads in `ghost definitions', the
;;; definitions saved out in a KB that does not explicitly contain them for
;;; instances and subclass definitions in the KB that use them.
;;;
;;; This is called in a particular section of a KB.  The beginning of this
;;; section is signalled by the appearance of the characters *1 as top-level
;;; elements.  The end of the section is signalled by the characters *2.  This
;;; gets called right after the initial characters have been read, and exits
;;; after it reads past the the final characters.
;;;
;;; This calls KB reading functions after setting up some special variables that
;;; affect them.  This binds reading-ghost-definitions-p to true, which causes
;;; the setting of the name of a definition by read-frame-for-kb to be
;;; suppressed.  This function also binds
;;; class-name-read-while-reading-current-ghost-definition a binding (to an
;;; irrelevant value).  During the reading of a definition, the name of the
;;; class being read is stored in this variable (instead of in the definition),
;;; so that it can be examined by this function after reading.
;;;
;;; Each definition has its first-definition-mark frame flag set true.  This
;;; marks it as a ghost definition during the KB reading process.  (I.e., this
;;; information is not to be used beyond the dynamic extend of the KB reading
;;; process.)

;;; Each definition is examined for class-name conflicts and processed in 
;;; roughly the same way that non-ghost definitions are as far as conflicts
;;; are concerned.

(defun ghost-definitions-may-be-saved-in-wrong-order ()
  (not
    (system-version-greater-p
      system-version-from-kb-being-read
      '#.(make-system-version 8 0))))

(defun read-ghost-definitions ()
  (let* ((reading-ghost-definitions-p t))
    ;; before version 8.0, ghost definitions were saved in the wrong
    ;; order, so we have to reorder them here, to make sure
    ;; the superclass comes before the subclass.
    ;; See Bug HQ-4895236 Inconsistently modularized kb after merging modules.
    ;; for doc on why this is the correct order.
    ;; For version 8.1 and later, though, we have to install each definition
    ;; as we read it, rather than reading all the ghost definitions before
    ;; installing any of them, because one ghost definition may be an
    ;; instance of a class defined by another ghost definition. This is needed
    ;; to fix bug HQ-5037224 "Ghosts of user-defined definition types are direct instances of class-definition" -alatto, 6/6/05
    (if (ghost-definitions-may-be-saved-in-wrong-order)
	(read-ghost-definitions-2
	   (order-ghost-definitions (read-ghost-definitions-1 nil)))
	(read-ghost-definitions-1 t))))

;;; We need to do a topological sort of the definitions. To do this, we build up
;;; two data structures. One is a list that for each class, consists of
;;; (class-info number-of-predecessors . list-of-successors)
;;; The other is the subset of this list where the number-of-predecessors is 0.
;;; We then loop, moving one class at a time from the number-of-predecessors-is-0 list to the
;;; final list, and decrementing the number-of-predecessors for each of its ancestors.
;;; We start with only a list of predecessors, not ancestors, so we put the class-infos into
;;; a hash table so we can build up the ancestor lists.

(defun order-ghost-definitions (definition-infos)
  ;; First build up a list
  (let* ((result nil)
	 (definitions-with-ancestors nil)
	 (definitions-ready-to-be-processed nil)
	 (definitions-hash (make-eq-hash-table (length definition-infos) nil nil)))
    (loop for definition-info in definition-infos do
      (let ((definition-structure (gensym-list definition-info 0)))
	(gensym-push definition-structure definitions-with-ancestors)
	(eq-puthash definitions-hash (caar definition-structure) definition-structure)))
    (loop for definition-form in definitions-with-ancestors do
      (let* ((definition (third (first definition-form)))
	     (direct-superiors (direct-superiors-of-defined-class definition)))
	(loop for possible-preceder in direct-superiors do
	  (let ((preceder? (eq-gethash definitions-hash possible-preceder nil)))
	    (when preceder?
	      (incff (cadr definition-form))
	      (gensym-push definition-form (cddr preceder?))))))
      (when (=f (cadr definition-form) 0)
	(gensym-push definition-form definitions-ready-to-be-processed)))
    (reclaim-eq-hash-table definitions-hash)
    (loop do
      (when (null definitions-ready-to-be-processed)
	(loop-finish))
      (let ((next (gensym-pop definitions-ready-to-be-processed)))
	(gensym-push (car next) result)
	(loop for ancestor in (cddr next) do
	  (decff (second ancestor))
	  (when (=f (second ancestor) 0)
	    (gensym-push ancestor definitions-ready-to-be-processed)))
	(reclaim-gensym-list next)))
    (reclaim-gensym-list definitions-with-ancestors)
    (nreverse result)))

(defun read-ghost-definitions-1 (install?)
  (if install?
      (let ((information-on-ghost-definitions nil))
	(loop with class-name-read-while-reading-current-ghost-definition
	      as definition? = (read-element-for-kb t)
	      while definition? do
	  (slot-value-push
	    (slot-value-list
	      class-name-read-while-reading-current-ghost-definition
	      nil
	      definition?)
	    information-on-ghost-definitions)
	  (let ((new-name
		  (read-ghost-definition-2
		    class-name-read-while-reading-current-ghost-definition
		    definition?
		    information-on-ghost-definitions)))
	    (setf (second (car information-on-ghost-definitions))
		  new-name))
	      finally (reclaim-slot-value-tree information-on-ghost-definitions)))
      (loop with class-name-read-while-reading-current-ghost-definition
	    as definition? = (read-element-for-kb t)
	    while definition?
	    collect (slot-value-list
		      ;; class-name
		      class-name-read-while-reading-current-ghost-definition
		      ;; new-name?
		      nil
		      ;; new-definition?
		      definition?)
	      using slot-value-cons)))

(defun read-ghost-definitions-2 (information-on-ghost-definitions?)
  (loop for ghost-definition-information in information-on-ghost-definitions?
	for (class-name new-name? new-definition) = ghost-definition-information
	for new-name = (read-ghost-definition-2
			 class-name new-definition
			 information-on-ghost-definitions?)
	when new-name
	  do (setf (second ghost-definition-information) new-name)
	finally (reclaim-slot-value-tree information-on-ghost-definitions?)))

(defun read-ghost-definition-2
    (class-name new-definition information-on-ghost-definitions?)
  (let* ((old-definition? (class-definition class-name))
	 (old-class-definition-is-frame-p?
	   (and old-definition? (class-definition-is-frame-p old-definition?)))
	 (definition-classes-are-compatible?
	   (and old-class-definition-is-frame-p?
		(definition-classes-are-compatible-p new-definition old-definition?)))
	 (names-of-differing-slots?
	   (when old-class-definition-is-frame-p?
	     (when (old-format-for-default-overrides-p)
	       (fix-up-default-overrides-for-5-0 new-definition))
	     (when (and (need-to-normalize-message-properties-p)
			(frame-of-class-p new-definition 'message-definition))
	       (normalize-message-properties-for-message-definition new-definition))
	     (let ((slot-differences?
		     (and old-class-definition-is-frame-p?
			  (find-differences-in-frames-if-any
			    old-definition? new-definition nil
			    definition-classes-are-compatible?))))
	       ;; Do fix-ups if necessary
	       (when (and (frame-of-class-p
			    old-definition? 'connection-definition)
			  (frame-of-class-p
			    new-definition 'connection-definition)
			  (neq (junction-block-class-for-connection
				 old-definition?)
			       (junction-block-class-for-connection
				 new-definition)))
		 (let ((add-junction-block-class-to-slot-differences?
			 (deal-with-junction-block-class-differences
			   new-definition old-definition? class-name)))
		   (when add-junction-block-class-to-slot-differences? 
		     (setq slot-differences?
			   (nconc slot-differences?
				  (slot-value-list
				    'junction-block-class-for-connection))))))
	       (when (and slot-differences?
			  (system-revision-greater-p
			    '#.(make-system-version
				 4 0 :quality beta-release-quality :revision 3)
			    system-version-from-kb-being-read)
			  (fixup-attribute-configuration-error-p))
		 (or (fix-up-configuration-attribute-error
		       old-definition? new-definition slot-differences?)
		     (fix-up-configuration-attribute-error
		       new-definition old-definition? slot-differences?)))
	       slot-differences?))))
    (set-first-definition-mark new-definition)
    (cond
      ((null old-definition?)
       (unless dont-load-if-definitions-have-changed-p
	 ;; This will deal with a class-name that conflicts with a
	 ;; type or system-class name.
	 (install-class-definition class-name new-definition nil nil t))
       ;; Conflict report with only one class which is in limbo.
       ;; It should be placed on the conflict report if install-class-definition
       ;; has not already done so because it is a type or system-defined class
       ;; name.
       (unless (assq class-name class-name-conflicts)
	 (record-class-name-conflict class-name nil nil new-definition nil t))
       nil)
      (t
       ;; When a direct-superior definition has a class-name conflict
       ;; causing it to be renamed, the inferior-class definition must
       ;; reflect the new-name in its direct-superiors-of-defined-class
       ;; slot and have its names-of-differing-slots? revised.
       (when old-class-definition-is-frame-p?
	 (let* ((direct-superiors?
		  (direct-superiors-of-defined-class new-definition))
		;; Just in case we have a pre-4.0 kb.
		(adjusted-direct-superiors?
		  (and direct-superiors?
		       (if (atom direct-superiors?)
			   (slot-value-list direct-superiors?)
			   direct-superiors?)))
		(changed-direct-superiors? nil))
	   (loop for sublist on adjusted-direct-superiors?
		 for direct-superior = (first sublist)
		 for new-name?
		     = (second
			 (assq class-name information-on-ghost-definitions?))
		 when new-name?
		   do (setq changed-direct-superiors? t)
		      (setf (first sublist) new-name?))
	   (when changed-direct-superiors?
	     (initialize-slot-value
	       new-definition 'direct-superiors-of-defined-class
	       adjusted-direct-superiors?)
	     (unless (memq 'direct-superiors-of-defined-class
			   names-of-differing-slots?)
	       (setq names-of-differing-slots?
		     (nconc names-of-differing-slots?
			    (slot-value-list
			      'direct-superiors-of-defined-class)))))))
       (cond
	 ;; There is no conflict.
	 ((and old-class-definition-is-frame-p?
	       (null names-of-differing-slots?))
	  (delete-block-after-reading-kb new-definition)
	  nil)
	 ;; There is a conflict when old-class-definition-is-frame-p?,
	 ;; and possibly a conflict when it is not.
	 (t
	  ;; When there have been changes in direct superiors further up the
	  ;; hierarchy the class-inheritance-path-of-definition will need
	  ;; refreshing.  Name-class-with-variant-name will cause the class
	  ;; to be defined.
	  (let ((new-name
		  (when names-of-differing-slots?
		    (let ((direct-superior-classes?
			    (direct-superiors-of-defined-class new-definition)))
		      (reclaim-slot-value
			(class-inheritance-path-of-definition new-definition))
		      (setf (class-inheritance-path-of-definition new-definition)
			    (if (direct-superiors-are-defined-p direct-superior-classes?)
				(make-class-inheritance-path-for-user-defined-class
				  nil direct-superior-classes?)
				nil))
		      (name-class-with-variant-name class-name new-definition)))))
	    ;; Is this case ever encountered?
	    (if dont-load-if-definitions-have-changed-p
		(record-class-name-conflict
		  class-name nil old-definition? new-definition
		  names-of-differing-slots? t)
		(install-class-definition
		  class-name new-definition
		  new-name
		  names-of-differing-slots?
		  nil))
	    new-name)))))))

;; Fix up this function to call names-of-differing-slots
;; denotations-of-differing-slots and fix functions it calls to observe that not
;; all elements are symbols, but may be class-qualified name lists!  Not needed
;; now in practice! (MHD/GHW 6/14/95)




;;; `Fix-up-configuration-attribute-error' fixes up an error introduced in 4.0
;;; whereby in 3.0 kbs user-defined shadowing attributes with an attribute name
;;; of "configuration" were kept in the class-specific-attributes slot instead of
;;; being moved to the default-overrides slot.  If the loading KB was saved in
;;; G2 4.0 Beta Rev. 2 or earlier and there are class-name conflicts, this function
;;; corrects the error.  This function returns when it has detected and corrected
;;; the error; otherwise it returns nil.

(defun fix-up-configuration-attribute-error
    (definition1 definition2 names-of-differing-slots)
  (when (and (memq 'class-specific-attributes names-of-differing-slots)
	     (memq 'default-overrides names-of-differing-slots)
	     (member 'configuration (class-specific-attributes definition1)
		     :test 'car-eq)
	     (not (member 'configuration (class-specific-attributes definition2)
			  :test 'car-eq))
	     (member 'configuration (default-overrides definition2)
		     :test 'car-eq)
	     (loop for superior in (direct-superiors-of-defined-class definition1)
		   thereis (slot-description-from-class superior 'configuration)))
    (let* ((definition1-attributes (class-specific-attributes definition1))
	   (definition1-configuration-attribute-description
	       (car (member 'configuration definition1-attributes
			    :test 'car-eq)))
	   (copied-definition1-configuration-attribute-description
	     (copy-for-slot-value
	       definition1-configuration-attribute-description))
	   (definition2-configuration-default-override
	       (car (member 'configuration (default-overrides definition2)
			    :test 'car-eq)))
	   (proposed-definition1-configuration-default-override
	     (let* ((attribute-initial-value
		      (copy-for-slot-value
			(attribute-initial-value
			  copied-definition1-configuration-attribute-description)))
		    (attribute-initial-type?
		      (copy-for-slot-value
			(attribute-initial-type
			  copied-definition1-configuration-attribute-description))))
	       (prog1
		   (cond
		     ((and (consp attribute-initial-value)
			   (eq (car attribute-initial-value) ':funcall))
		      (slot-value-list
			(attribute-name copied-definition1-configuration-attribute-description)
			(slot-value-list attribute-initial-value)
			'user-defined))
		     ((or attribute-initial-value
			  attribute-initial-type?)
		      (slot-value-list
			(attribute-name copied-definition1-configuration-attribute-description)
			(if attribute-initial-type?
			    (slot-value-list
			      attribute-initial-value
			      attribute-initial-type?)
			    attribute-initial-value)
			'user-defined)))
		 (reclaim-slot-value
		   copied-definition1-configuration-attribute-description)))))
      (if (equal definition2-configuration-default-override
		 proposed-definition1-configuration-default-override)
	  (let* ((definition1-default-overrides (default-overrides definition1))
		 (new-definition1-default-overrides
		   (if (null definition1-default-overrides)
		       (slot-value-list
			 proposed-definition1-configuration-default-override)
		       (loop with new-override-added? = nil
			     with definition2-list = (default-overrides definition2)
			     with last-definition1-override =
			            (car (last definition1-default-overrides))
			     for override in definition1-default-overrides
			     nconc
			     (cond ((null definition2-list)
				    (if (and (null new-override-added?)
					     (eq override
						 last-definition1-override))
					(slot-value-list
					  override
					  proposed-definition1-configuration-default-override)
					(slot-value-list override)))
				   ((eq (attribute-name (car definition2-list)) 'configuration)
				    (setq new-override-added? t)
				    (setq definition2-list nil)
				    (slot-value-list
				      proposed-definition1-configuration-default-override
				      override))
				   (t (setq definition2-list (cdr definition2-list))
				      (slot-value-list override)))))))
	    (setf (class-specific-attributes definition1)
		  (delete-slot-value-element
		    definition1-configuration-attribute-description definition1-attributes))
	    (reclaim-slot-value definition1-configuration-attribute-description)
	    (setf (default-overrides definition1)
		  new-definition1-default-overrides)
	    t)
	  (progn
	    (reclaim-slot-value
	      proposed-definition1-configuration-default-override)
	    nil)))))
		    
			 
		    

#+development
(defun decode-float-from-kb-format (string)
  (let (x1 x2 x3 x4)
    (multiple-value-setq (x1 x2)
      (convert-characters-to-binary-word
	(aref string 0)
	(aref string 1)
	(aref string 2)
	(aref string 3)
	(aref string 4)))
    (multiple-value-setq (x3 x4)
      (convert-characters-to-binary-word
	(aref string 5)
	(aref string 6)
	(aref string 7)
	(aref string 8)
	(aref string 9)))
    (decode-double-float x1 x2 x3 x4)))

#+development
(defun convert-characters-to-binary-word (y0 y1 y2 y3 y4)
  (let (x1 x2 x3)
    ;; This style of coding uses an extra local variable in
    ;; preference to writing an expression with multiple reads
    ;; which relies on left-to-right expression evaluation to work.
    (setq x1 (radix-94-weight y0))
    (setq x2 (radix-94-weight y1))
    (setq x1 (+f (*f 94 x1) x2))
    
    (setq x2 (radix-94-weight y2))
    (setq x3 (radix-94-weight y3))
    (setq x2 (+f (*f 94 x2) x3))
    (setq x3 (radix-94-weight y4))
    (setq x2 (+f (*f 94 x2) x3))
    
    (values (+f (ashf x1 3) (ashf x2 -16)) 
	    (logandf x2 #.(- (expt 2 16) 1)))))




;;; `Abort-on-bad-kb' ...

(defun abort-on-bad-kb (&optional (problem-character-unless-eof? nil))
  (kb-error
    "~A ~A~A~Aencountered while reading.  ~S either: (1) is not a KB, (2) has ~
     been damaged, or (3) was not written properly due to a system software ~
     error."
    (if problem-character-unless-eof?
	"Bad character"
	"End-of-file unexpectedly")
    (if problem-character-unless-eof? "(" "")
    (or problem-character-unless-eof? "")
    (if problem-character-unless-eof? ") " " ")
    name-text-string-for-kb-being-read))


    

;;; `Abort-on-missing-class-in-kb' ...

#+unused
(defun abort-on-missing-class-in-kb (class)
  (kb-error
    "~S contains an instance of an undefined class, ~A.  ~
     You may have neglected to load a library KB that ~
     defined this class.  In any case, you must start over."
    name-text-string-for-kb-being-read class))






;;; Process-slot-group-for-block reads the value for this slot and sets the
;;; subblocks and connections collapsed slots appropriately.  For kbs saved
;;; before these slots were collapsed, subblocks-and-connections (the value read
;;; in from the kb) will be nil.  For such kbs, the collapsed slots are set by
;;; the absent slot putters for subblocks and connections.  For kbs saved after
;;; slots were collapsed, subblocks-and-connections will be of the form
;;; (subblocks .  connections) (see also write-slot-group-for-block?).  Such kbs
;;; will not have haved information for subblocks and connections slots so the
;;; absent slot putters will not be invoked for these.

;; Some of the above documentation confuses me and lacks credibility! (MHD
;; 10/14/93)

;;; Slot-group-data is either NIL or a list of the form
;;;
;;;    (left-edge-of-block top-edge-of-block
;;;     right-edge-of-block bottom-edge-of-block
;;;     ( { subblock } )
;;;     ( { connection } )
;;;     )
;;;
;;; This function either uses or reclaims, at its discretion, all of the conses
;;; within slot-group-data.  They all should be slot value conses.
;;;
;;; This function knows the internal representation of the slot-group-for-block?
;;; slot; if that slot changes, this must be kept up-to-date.
;;;
;;; This returns no useful value.

(defun-void process-slot-group-for-block (block slot-group-data)
  (when slot-group-data
    (let* ((left-edge (first slot-group-data))
	   (top-edge (second slot-group-data))
	   (right-edge (third slot-group-data))
	   (bottom-edge (fourth slot-group-data))
	   (subblocks (fifth slot-group-data))
	   (connections (sixth slot-group-data)))
      (unless (and (null (slot-group-for-block? block))
		   (=f left-edge 0)
		   (=f top-edge 0)
		   (=f right-edge 0)
		   (=f bottom-edge 0)
		   (eq subblocks nil)
		   (eq connections nil))
	(let ((slot-group-for-block
	       (or (slot-group-for-block? block)
		   (setf (slot-group-for-block? block)
			 (make-icon-slot-group)))))
	  (setf (left-edge-internal slot-group-for-block) left-edge)
	  (setf (top-edge-internal slot-group-for-block) top-edge)
	  (setf (right-edge-internal slot-group-for-block) right-edge)
	  (setf (bottom-edge-internal slot-group-for-block) bottom-edge)
	  (loop for subblock in subblocks
	     do (set-superblock-and-faction subblock block))
	  (when subblocks
	    (setf (subblocks-internal slot-group-for-block)
		  #-subblocks-v2 subblocks
		  #+subblocks-v2 (upgrade-subblocks subblocks)))
	  (when connections
	    (setf (connections-internal slot-group-for-block)
		  #-connections-v2 connections
		  #+connections-v2 (upgrade-connections connections))
	    #+connections-v2
	    (gensym-push block blocks-with-connections-from-kb-read))))
      (reclaim-slot-value-list slot-group-data))))

;; It would be nice, and a bit more efficient, if it didn't have to check
;; whether setting was necessary.  If saving is guaranteed never to write
;; out a a default slot-group-data, that would be so.  Maybe it is true,
;; but I'm not sure right now.  (MHD 10/14/93)

;; Name was changed slightly: was process-slot-group-for-block? (MHD 10/14/93)

;; Optimized today by teaching it the internals of slot-group-for-block.  Made
;; this be a defun-void.  Cleaned up a bit, too. (MHD 10/14/93)





;;;; G2 Post Loading Functions



;;; `Fix-subworkspace-names' is a post-loading-function used on a kb
;;; with kb-flags < 33 to remove the name of any kb-workspace when
;;; that name is also the name of the superior item if any.

(def-post-loading-function fix-subworkspace-names
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless 
      (subworkspaces-no-longer-inherit-names-p)
      (loop with names-removed = nil
	    for kb-workspace being each class-instance of 'kb-workspace
	    for superior-item = (parent-of-subworkspace? kb-workspace) doing
	(when superior-item
	  (let ((kb-workspace-name (name-or-names-for-frame kb-workspace))
		(superior-item-name-or-names
		  (name-or-names-for-frame superior-item)))
	    
	    (when (and kb-workspace-name superior-item-name-or-names
		       (or (eq kb-workspace-name superior-item-name-or-names)
			   (and (consp superior-item-name-or-names)
				(memq kb-workspace-name superior-item-name-or-names))))
	      
	      (setq names-removed (gensym-cons kb-workspace-name names-removed))
	      
	      (change-slot-value kb-workspace
				 'name-or-names-for-frame nil))))
	    finally
	      (when names-removed
		(let ((names-removed-as-text
			(twith-output-to-text-string
			  (loop for listed-name on names-removed doing
			    (tprinc (car listed-name))
			    (if (cdr listed-name) (tprinc ", "))))))
		  (notify-engineer "This KB, which was created before version 2.0, has ~
                    subworkspaces that have the same names as their superior objects. The names of ~
                    these subworkspaces have been removed. They are: ~(~a~)" names-removed-as-text)
		  (reclaim-text-string names-removed-as-text)
		  (reclaim-gensym-list names-removed)))))))
				     
				     
				     
;; The stack-of-subblocks slot is no longer used for anything.
;; Neither drawing nor mouse tracking pays any attention to this
;; slot.  The only thing we might want to do here, to be sure
;; that we get exactly the 3.0 behavior is to place the graphs
;; into the subblocks list in the same order they were placed
;; into stack-of-subblocks, ie, whatever order the loop over
;; all instances obtained. -fmw, 5/13/94

;; Obsolete:
;(def-post-loading-function put-old-graphs-into-stack-of-subblocks
;  (let ((kb-flags kb-flags-from-last-kb-read))
;    (unless (old-graphs-are-now-in-stack-of-subblocks-p)
;      (loop 
;        with list-of-workspaces-to-invalidate = nil
;        for graph being each class-instance of 'graph
;        as superblock = (superblock? graph)
;        unless (memq graph (stack-of-subblocks superblock))
;          do (slot-value-push graph (stack-of-subblocks superblock))
;             (gensym-pushnew superblock list-of-workspaces-to-invalidate)
;        finally
;          (loop for workspace in list-of-workspaces-to-invalidate
;                do (invalidate-workspace workspace))
;          (reclaim-gensym-list list-of-workspaces-to-invalidate)))))



;;; Post loading function initialize-parameters is in file VARIABLES.


;;; Fix up the format of default-overrides for strict instances of
;;; class-definitions slot for 5.0.

(defun-void fix-up-default-overrides-for-5-0 (definition)
  (when (and (eq (get-specialized-definition-class definition)
		 'class-definition)
	     (old-format-for-default-overrides-p)
	     (default-overrides definition))
    ;; This loop adds a missing class designation to overrides on
    ;; three slots where the grammar has this syntax:
    ;;    <aliased-slot-name> 'for <class> :  <value>
    (loop for override in (default-overrides definition)
	  do
      (unless (or (override-is-for-user-defined-slot-p override)
		  (third override))
	(let ((slot-name (first override)))
	  (when (or (eq slot-name 'data-type-of-variable-or-parameter)
		    (eq slot-name 'initial-value-of-variable-or-parameter)
		    (eq slot-name 'g2-array-initial-values))
	    (setf (cdr override)
		  (nconc (cdr override)
			 (slot-value-list
			   (most-refined-foundation-class-of-direct-superiors
			     (direct-superiors-of-defined-class definition)
			     slot-name))))))))
    (parse-text-for-slot
      (make-text-representation-for-slot-value
	definition 'default-overrides nil)
      definition
      (get-slot-description-of-frame
	'default-overrides definition nil))))


;;; The class-method `initialize-after-reading' fixes up
;;; instance-configurations.

(def-class-method initialize-after-reading (definition)
  (funcall-superior-method definition)	; per convention  
  (when (and (instance-configuration definition)
	     (loading-7-0-rev-0-kb-p))
    (fix-up-double-click-configuration-clauses (instance-configuration definition))))


;;; The initialize-after-reading method for object-definition eliminates
;;; miscellaneous obsolete features of user icon descriptions.  

(def-class-method initialize-after-reading (object-definition)
  (funcall-superior-method object-definition) ; per convention
  )





(def-post-loading-function (clean-up-orphan-frame-representations :once-only t)
  ;; to clean up orphan frame representations; eliminate later?

  (loop while
	  (loop for table being class-instances of 'table
		do (cond
		     ((or (null (superblock? table))
			  
			  ;; This condition added -- for a short time, tables in
			  ;; modules other than the frames they were representing
			  ;; could be saved out, particularly with class-name
			  ;; conflicts, which this looks for especially. 
			  ;; Note that this assumes that deleting a table
			  ;; pointing back to a deleted frame or to a frame
			  ;; that doesn't point back to it is not dangerous.
			  ;; See reclaimer for table-rows slot, which calls
			  ;; remove-from-frame-representations-if-present.
			  ;; Add a flag for this after the beta!!  (MHD 2/11/92)
			  (block search
			    (do-frames-this-represents (represented-frame table)
			      (if (or (not (framep represented-frame))	; deleted?
				      (check-for-table-representing-recycled-definition table))
				  (return-from search t)))))
		      (delete-frame table)
		      
		      ;; Once you've deleted table out of the linked
		      ;; list of instances, this loop iteration is
		      ;; probably invalid, so we return t to the outside
		      ;; loop to have it try again until exausted.  (MHD
		      ;; 2/11/92)
		      (return t))))))


(defun check-for-table-representing-recycled-definition (table)
  ;; just part of clean-up-orphan-frame-representations above
  (loop for row in (table-rows table)
	thereis
	  (loop for cell? in row
		thereis
		  (and cell?
		       (not (cell-is-block-p cell?))
		       (multiple-value-bind (frame? slot-name-or-index)
			   (get-slot-represented-by-text-cell-if-any cell?)
			 (and (eq slot-name-or-index
				  'direct-superiors-of-defined-class)
			      ;; if table thinks it has a definition, make
			      ;; sure it really does; if not, it's recycled
			      (not (frame-of-class-p frame? 'class-definition))))))))





(declare-forward-reference make-graphs-opaque-1 function)

(def-post-loading-function make-graphs-opaque ()
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (graphs-opaque-p) (make-graphs-opaque-1))))



(def-post-loading-function make-all-rule-boxes-have-text-box-format ()
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (all-rule-boxes-have-text-box-format)
      (loop for text-box being each class-instance of 'rule
	    when (null (text-box-format text-box))
	      do (setf (text-box-format text-box)
		       (get-or-make-format-frame
			 (default-text-box-format-name text-box)))
		 ;; reformat unnec. if it wasn't done by now
		 ))))



;;; The constraint that an unimplemented definition may not have capabilities or defaults
;;; is violated by the method of uniplementing duplicate definitions in the merge process.
;;; Another aspect of this process is that it is not easy for the user to figure out which
;;; of two definitions is the unimpleneted one, because the frame status was not being set
;;; to INCOMPLETE.

(def-post-loading-function (fix-unimplemented-definitions :once-only t :after-conflict-resolution :always)
  (loop for definition being each class-instance of 'class-definition
	for class? = (name-of-defined-class definition)
	  do (if (wacko-definition-p definition class?)
		 ;; These are left over junction block definitions in some old
		 ;; KBs. It is hoped that no more of these will arise.
		 (cond
		   ((instantiated-class-p class?)
		    (put-wacko-definition-on-kb-workspace definition)
		    (when (not (complete-definition-p definition))
		      (update-frame-status definition 'incomplete nil)))
		   (t
		    (delete-frame definition)))
		 (when (not (complete-definition-p definition))
		   (update-frame-status definition 'incomplete nil)))))

  


(def-post-loading-function fix-capabilities-of-old-kbs
  (let ((kb-flags kb-flags-from-last-kb-read))
;    (unless (capabilities-are-ok-p)
;      (fix-capabilities))))
    nil))



;;; Some old KBs have a superior-of-defined-class filled in when no
;;; such class exists. It should be removed. The definition is then
;;; incomplete, and there should be no frame note of this category.
;;; The frame note is going away.

;; Since there can be old KBs with this note, this code must be kept. But the
;; note no longer is defined.

(def-post-loading-function remove-unimplemented-superiors
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (no-unimplemented-superiors-p)
      (loop for def being each class-instance of 'class-definition
	    doing
	(delete-frame-note-if-any 'potential-class-note def)))))



;;; The post-loading function `provide-message-board-after-loading-kb' initializes
;;; the pair of variables current-message-board? and frame-serial-number-of-current-
;;; message-board as described in BOOKS if
;;;
;;;   (1) we're installing (i.e., main-kb-being-read? is true) and
;;; 
;;;   (2) either
;;; 
;;;      (a) there is no current message board; or
;;;      (b) the current message board has been deleted
;;;
;;; These rules are meant to be somewhat heuristic, but tend to ensure that a
;;; fully loaded module starts out with a message board workspace, even before
;;; the KB gets started running and a message gets put up.
;;;
;;; Doing this only in the installing case means that we take the parameters for
;;; message board size, etc., from the installed message-board-parameters system
;;; table.  [This rule was added for 4.0 Beta; it was seen as a bug in 3.0 that
;;; the installed module's (= not the first KB merged in's) parameters were
;;; apparently being ignored. (MHD 12/9/94)]
;;;
;;; This is heuristic, and not foolproof.  Users can't absolutely rely on having
;;; a message board when they start up, and they also can't reliably depend on
;;; it having been created according to their installed top-level module's
;;; message-board-parameters system table.  For example, any of the following
;;; scenerios get in the way:
;;;
;;;    - they do a clear-KB and just put together their KB from scratch
;;;      during a session, i.e., never even loading
;;;
;;;    - they just to merges of KBs
;;;
;;;    - they load in a KB with modules, then merge in a new set of modules,
;;;      installing system tables (i.e., they got the message board parameterized
;;;      for the first KB they loaded, not the second one the merged on top of it,
;;;      even though they changed the top-level module.)
;;;
;;;    - they delete the message board or edit the parameters after loading

(def-post-loading-function provide-message-board-after-loading-kb
  (when (and main-kb-being-read?
	     (or (null current-message-board?)
		 (frame-has-been-reprocessed-p
		   current-message-board?
		   frame-serial-number-of-current-message-board)))
    (setq current-message-board?
	    (make-message-board))
    (frame-serial-number-setf
      frame-serial-number-of-current-message-board
      (frame-serial-number current-message-board?))))

;; Consider deleting even an existing message board certain circumstances like
;;
;;    - reset (not paused) and
;;    - it's not shown on any windows 



(def-post-loading-function remove-redundant-simulation-formulas-notes
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (redundant-simulation-formulas-notes-removed-p)
      (loop for formula being each class-instance of 'generic-simulation-formula
	    do (delete-frame-note-if-any 
		 'redundant-generic-simulation-formulas formula)))))





(def-kb-specific-variable launch-recompile-for-compilations-removed-in-this-kb?
			  kb-load2
  nil)

;(def-frame-note-writer block-had-compilations-removed (particulars)
;  (declare (ignore particulars))
;  (twrite "this item needs to be recompiled"))

;; Before this frame note becomes useful we need to have plan for how to
;; remove it and make the frame incomplete when it exists introducing a
;; recompile method might help but what if the user edit's components of
;; the frame?



;;; `Note-frame-with-compilation-removed' is called when frame does not have
;;; its compiled slots filled in up-to-date upon loading.  See its use in
;;; INSTALL.

;;; This sets the kb-specific variable
;;;
;;;    launch-recompile-for-compilations-removed-in-this-kb?
;;;
;;; to true.

(defun note-frame-with-compilation-removed (frame)
  (declare (ignore frame))
  (setq launch-recompile-for-compilations-removed-in-this-kb? t)
  )



(def-kb-specific-variable workstation-in-which-to-launch-recompilation?
  kb-load2 nil)

;; When the above is true, service-workstations calls back here, to
;; launch-recompilation-for-this-kb.  (Yuch! -- the next generation of
;; WORKSTATIONS will eliminate the need for such a kludge! (MHD 7/1/91))


(def-kb-specific-variable ui-client-interface-in-which-to-launch-recompilation?
  kb-load2 nil)

(defun launch-recompilation-for-this-kb ()
  (setq workstation-in-which-to-launch-recompilation? nil)
  (setq launch-recompile-for-compilations-removed-in-this-kb? nil)
  (launch-compile-to-bring-kb-up-to-date
    (tformat-text-string
      "Once you save the KB in this version ~
       of G2, recompilation will no longer happen automatically.")))



;;; The post-loading function `recompile-if-compilations-were-removed' sets up a
;;; a variable which will be used to launch a recompile once all kb loading and
;;; module merging has been completed.

(def-post-loading-function recompile-if-compilations-were-removed
  (when launch-recompile-for-compilations-removed-in-this-kb?
    (cond (servicing-workstation?
	   (setq workstation-in-which-to-launch-recompilation?
		 (or current-workstation
		     (car (last workstations-in-service)))))
	  (t
	   (let ((interface? (and current-system-rpc-icp-socket?				     
				  (enclosing-interface-frame? current-system-rpc-icp-socket?))))
	     (setq ui-client-interface-in-which-to-launch-recompilation? 
		   (and (framep interface?)
			(frame-of-class-p interface? 'ui-client-interface)
			interface?))
	     (setq workstation-in-which-to-launch-recompilation?
		   (car (last workstations-in-service))))))))

;; Old condition -- removed:  (MHD/JRA 9/17/91)
;; 
;;    (or (not (compilations-up-to-date-p nil))
;;	  (system-version-greater-p
;;	    current-system-version 
;;	    system-version-from-last-kb-read))








;;; The post-loading function `identify-all-permanent-blocks' ...

(def-post-loading-function identify-all-permanent-blocks
  ;; Commented out by ML and MHD. 5/5/92. There used to be
  ;; no way to delete unexposed blank  kb-workspaces. Note that we
  ;; still do not save them if orphan-p.
;  (loop for ws being each class-instance of 'kb-workspace do
;    (when (orphan-workspace-p ws) (delete-frame ws)))

  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (permanent-blocks-really-marked-p)
      
      (identify-all-savable-kb-workspaces)
      (loop for block being each class-instance of 'block
	    do
	(if (or (savable-block-p block)
		(format-frame-p block))
	    (set-permanent-block block)
	    #+development
	    (if (and (permanent-block-p block)
		     (not (format-frame-p block))
		     (not (frame-of-class-p block 'ui-client-item)))
		(cerror "Continue"
			"Non-savable block ~a marked as permanent. See ML."
			block)))))))


(declare-forward-reference install-external-simulation-1 function)

(def-post-loading-function (install-external-simulation :once-only t)
  (install-external-simulation-1))



(declare-forward-reference install-connection-posts-after-loading-1 function)

(def-post-loading-function install-connection-posts-after-loading
  (install-connection-posts-after-loading-1))



(defun-simple collect-unreprocessed-items (list)
  (loop for (item . frame-serial-number) in list
	unless (frame-has-been-reprocessed-p item frame-serial-number)
	  collect item using gensym-cons))

(defun-void reclaim-item-and-fsn-list (list)
  (loop for cons in list
	for (item . fsn) = cons
	do (reclaim-frame-serial-number fsn)
	   (reclaim-gensym-cons cons))
  (reclaim-gensym-list list))


(declare-forward-reference analyze-compiled-items-after-loading-1 function)

(defvar compiling-incomplete-items-after-analyze-p nil)
(defvar collecting-procedures-to-warn-about-p nil)
(defvar procedures-to-warn-about-p)

(def-post-loading-function (analyze-compiled-items-after-loading :once-only t)
  (with-collected-warnings ()
    (if some-module-is-clear-text-p
	(recording-items-made-incomplete ('analyze)
	  (let ((procedures-to-warn-about-p nil))
	    (let ((collecting-procedures-to-warn-about-p t))
	      (let ((compiling-incomplete-items-after-analyze-p t))
		(analyze-compiled-items-after-loading-1))
	      (when items-made-incomplete-were-recorded?
		(loop with items = (collect-unreprocessed-items items-made-incomplete)
		      while items
		      for item = (gensym-pop items)
		      do (recompile-item-1 item))))
	    (loop with add-as-item-referring-to-name? = t
		  with items = (collect-unreprocessed-items procedures-to-warn-about-p)
		  while items
		  for item = (gensym-pop items)
		  do (post-analyzer-warning-note-if-necessary item))
	    (reclaim-item-and-fsn-list procedures-to-warn-about-p)))
	(analyze-compiled-items-after-loading-1))))




;;; The post-loading function `rendezvous-frame-denotations-in-relation-instances'
;;; deals with processing the relation-instance slot values on blocks after all
;;; kb modules have been loaded.

;;; The value of a relation-instances slot is a list of relation-instances,
;;; where each relation-instance is in this form:
;;;
;;;     (<relation-name> <relation-frame> <object-frame-1> ... <object-frame-n>)

;;; These conditions qualify a relation-instance for saving:

;;; (1) The relation-is-permanent slot on its relation frame is positive.

;;; (2) At least one of the object frames resides in the same module as the
;;; block being saved or has a frame-denotation (either a uuid or a name, chosen
;;; in that order).  Note that the relation frame is always savable because for
;;; it to participate in a relation-instance, it must have a name.

;;; The function that saves relation-instances is convert-intermodual-relation-
;;; instances-for-saving in KB-SAVE1.

;;; This post-loading function in this file replaces uuid or name references
;;; with frames, and also fixes up any intermodual relation-instance
;;; inconsistencies.

;;; These are the intermodual inconsistencies it fixes up:

;;; (1) There is a rendezvous failure for the relation frame: The relation-
;;; instance is removed.

;;; (2) There is a rendezvous failure with an object frame: If it is the only
;;; object frame in the relation-instance, the relation-instance is removed;
;;; otherwise the object-frame reference is removed.

;;; (3) There is a relation-instance in which the relation-name does not
;;; correspond to any name on the relation frame: All relation-instances
;;; with that relation are removed.

;;; (4) There is a relation-instance in which the relation-name is the
;;; secret-inverse-name even though the relation frame now has a value in its
;;; inverse-of-relation slot: The relation-name is changed to the
;;; inverse-of-relation name.

;;; (5) There is a relation-instance on one block but no corresponding relation-
;;; instance on the object frame: The missing relation instance is added.

;;; (6) There is a relation-instance that violates the class types specified on
;;; the relation: The relation-instance and its corresponding object relation-
;;; instance are removed.

;;; This one needs to be checked only after conflict resolution has been
;;; performed, since otherwise relation instances will be deleted
;;; due to spurious mismatches between classes about to be
;;; unified. So it is now performed in a separate post-conflict-resolution
;;; post-loading function, delete-type-violating-relation-instances.
;;; -alatto, 5/22/03

;;; (7) There is more than one relation-instance with the same relation-name
;;; and relation-frame on a block: Duplicates relation-instances are
;;; removed.

;;; (8) The relation has changed its symmetric status.  The relation-instance
;;; is removed.

;;; (9) There is a relation that is one-to-one, but there are relation-instances
;;; with more than one related item.  All relation-instances with that relation
;;; are removed.

;;; (10) There is a relation that is one-to-many, but there is a relation-instance
;;; with the reation-name of the relation with more than one related item.  All
;;; relation-instances with that relation are removed.

;;; (11) There is a relation that is many-to-one, but there is a relation-instance
;;; with an inverse name with more than one related item.  All relation-instances
;;; with that relation are removed.

;;; (12) There is a relation that is one-to-one, but two instances
;;; are related to the same instance. All relation-instances with that relation
;;; are removed.

;;; (13) Same as (12), for a many-to-one relation.
;;; (14) Same as (12), for the inverse of a one-to-many relation.
;;; (15) A relation is one-to-one, but item A is related to item B, which is
;;; itself related via the inverse relation to something other than A.
;;; All relation-instances with that relation are removed.
;;; (16) same as (15), for a many-to-one relation.
;;; (17) Same as (15), for the inverse of a one-to-many relation.


;;; rendezvous-successful-blocks? and additional-related-blocks must
;;; now be special variables, since they are used to communicated between
;;; the pre-conflict post-loading function,
;;; rendezvous-frame-denotations-in-relation-instances, and
;;; the post-conflict post-loading function,
;;; delete-type-violating-relation-instances.

;;; both of these lists will have a frame-serial-number as the first
;;; element, followed by a list of blocks.

(defvar rendezvous-successful-blocks? nil)
(defvar additional-related-blocks nil)

(def-post-loading-function (rendezvous-frame-denotations-in-relation-instances
			     :once-only t)
  (let ((relations-with-changed-slots? nil))
    ;; This catches blocks with relation instances that have not been placed
    ;; on the blocks-with-relation-instances-from-kb-read list because an
    ;; initialize-after-reading method did not call the superior method and
    ;; the block missed out in the processing in the initialize-after-reading
    ;; method for block.
    #+development
    (loop for block being each class-instance of block
	  when (and (relation-instances block)
		    (not (memq block blocks-with-relation-instances-from-kb-read)))
	    do
	      (cerror
		"kb-load2"
		"error in rendezvous-frame-denotations-in-relation-instances -- tell ghw"))

    ;; This loop replaces name and uuid references with frames where possible
    ;; ((1) and (2) above).
    
    ;; It also removes duplicate relation-instances (7), collects relation-frames
    ;; whose names do not match the relation-name on the relation-instance,
    ;; and replaces secret-inverse relation-names with inverse-of-relation
    ;; names (4).
    (let ((reference-serial-number (copy-frame-serial-number (current-frame-serial-number))))
      (loop for block in blocks-with-relation-instances-from-kb-read
	    ;; The following test is really only going to catch reclaimed
	    ;; frames or frames that get reclaimed and reprocessed sometime
	    ;; during the life of this loop.  It won't notice frames that have
	    ;; been recycled before this (because there's no guard FSN, it's
	    ;; simply using the current FSN).  Note that unfortunately, when a
	    ;; frame gets reclassified, it WANTS to not be considered
	    ;; reprocessed, so we can't just stick a guard into the global
	    ;; list.
	    unless (frame-has-been-reprocessed-p block reference-serial-number)
	    do
	     (let ((relation-instances (relation-instances block)))
	       (when (old-relation-instances-p relation-instances)
		 (loop with current-pointer = relation-instances
		       with following-pointer = nil
		       until (null current-pointer)
		       for relation-instance = (car-of-cons current-pointer)
		       for relation-name-reference = (car-of-cons relation-instance)
		       for relation-reference = (cadr-of-cons relation-instance)
		       for relation-frame? = (or (and (framep relation-reference)
						      relation-reference)
						 (find-frame-for-denotation
						   relation-reference 'block))
		       ;; Duplicate relation-instances are removed.
		       for duplicate-relation-instance?
			   = (and relation-frame?
				  (loop for other-relation-instance in (relation-instances block)
					until (eq other-relation-instance relation-instance)
					thereis (and (eq relation-name-reference
							 (car-of-cons other-relation-instance))
						     (eq relation-frame?
							 (cadr-of-cons
							   other-relation-instance)))))
		       ;; This has been found to happen when a block is related to two
		       ;; items with the same uuid.
		       for item-references-with-possible-duplicates
			   = (cddr relation-instance)
		       for item-references
			   = (loop with list-to-return = nil
				   for reference in item-references-with-possible-duplicates
				   unless (or (and (wide-string-p reference)
						   (loop for other-reference in list-to-return
							 thereis
							 (and (wide-string-p other-reference)
							      (string=w
								reference other-reference))))
					      (memq reference list-to-return))
				     do (setq list-to-return
					      (nconc list-to-return
						     (slot-value-list reference)))
				   finally (return list-to-return))
		       
		       for item-frames?
			   = (and relation-frame? 
				  (not duplicate-relation-instance?)
				  (loop with leading-pointer = item-references
					with trailing-pointer = nil
					until (null leading-pointer)
					for item-reference = (car-of-cons leading-pointer)
					for item-frame = (or (and (framep item-reference)
								  item-reference)
							     (and (or (symbolp item-reference)
								      (wide-string-p
									item-reference))
								  (find-frame-for-denotation
								    item-reference 'block)))
					do
				    (cond
				      ;; Replace the reference with the frame.
				      (item-frame
				       (setf (car leading-pointer) item-frame)
				       (setq trailing-pointer leading-pointer)
				       (setq leading-pointer (cdr trailing-pointer)))
				      ;; Snip out the rendezvous-failing reference.
				      (t
				       (cond
					 (trailing-pointer
					  (setf (cdr trailing-pointer) (cdr leading-pointer))
					  (reclaim-slot-value-cons leading-pointer)
					  (setq leading-pointer (cdr trailing-pointer)))
					 (t 
					  (reclaim-slot-value-cons 
					    (prog1 item-references
					      (setq item-references (cdr item-references))))
					  (setq leading-pointer item-references)))))
					finally (progn
						  (setf (cddr relation-instance)
							item-references)
						  (reclaim-slot-value-list
						    item-references-with-possible-duplicates)
						  (return item-references))))
		       do
		   ;; Keep the relation instance.
		   (cond (item-frames?
			  (setf (cadr-of-cons relation-instance) relation-frame?)
			  (setq following-pointer current-pointer)
			  (setq current-pointer (cdr following-pointer))
			  (let ((secret-inverse-name (secret-inverse-name relation-frame?))
				(inverse-of-relation (inverse-of-relation relation-frame?))
				(relation-name (relation-name relation-frame?)))
			    (if (and (neq relation-name-reference relation-name)
				     (neq relation-name-reference inverse-of-relation)
				     (neq relation-name-reference secret-inverse-name))
				;; Collect the relation frames that no longer have names
				;; corresponding to the relation-name-reference in the
				;; relation-instance.  All relation-instances with such
				;; frames will be removed when all frame references have
				;; undergone rendezvous.
				(unless (memq relation-frame? relations-with-changed-slots?)
				  (frame-push relation-frame? relations-with-changed-slots?))
				;; Fix up relation-instances in which the
				;; relation-name-reference is the secret-inverse-name even
				;; though there is now a value in the inverse- of relation
				;; slot (this situation is not expected in the relation
				;; code and causes reclamation problems).
				(when (and (eq relation-name-reference secret-inverse-name)
					   inverse-of-relation)
				  (setf (car-of-cons relation-instance) inverse-of-relation)))))
			 (t
			  ;; Snip out the relation instance.
			  (cond (following-pointer
				 (setf (cdr following-pointer) (cdr current-pointer))
				 (reclaim-slot-value-cons current-pointer)
				 (setq current-pointer (cdr following-pointer)))
				(t 
				 (reclaim-slot-value-cons 
				   (prog1 (relation-instances block)
				     (setf (relation-instances block)
					   (cdr (relation-instances block)))
				     (setq current-pointer (relation-instances block))))))
			  (reclaim-slot-value-list relation-instance))))
		 (when (relation-instances-not-empty-p (relation-instances block))
		   (frame-push block rendezvous-successful-blocks?)))))
      (reclaim-frame-serial-number reference-serial-number))

    ;; Now upgrade the relation-instances to v2
    #+relation-instances-v2
    (upgrade-relation-instances blocks-with-relation-instances-from-kb-read)

    ;; Add relations that have changed symmetry to relation-instances-with-changed-
    ;; slots? (8).
    (loop for block in rendezvous-successful-blocks?
	  for relation-instances = (relation-instances block)
	  do
      (loop for relation-instance being each relation-instance of relation-instances
	    for relation = (relation-instance-relation relation-instance)
	    do
	(unless (memq relation relations-with-changed-slots?)
	  (let* ((relation-name-reference (relation-instance-name relation-instance))
		 (relation-name (relation-name relation))
		 (other-relation-name-reference
		   (if (neq relation-name-reference relation-name)
		       relation-name
		       (if (relation-is-symmetric relation)
			   relation-name-reference
			   (or (inverse-of-relation relation)
			       (secret-inverse-name relation)))))
		 (object-frames (relation-instance-items relation-instance)))
	    (loop for object-frame being each related-item of object-frames
		  for other-instances = (when object-frame (relation-instances object-frame))
		  for corresponding-relation? =
		      (when other-instances
			(get-relation-instance other-relation-name-reference other-instances))
		  when object-frame
		  do
	      ;; There is a corresponding relation but relation has changed
	      ;; from non-symmetric to symmetric (but inverse reference has
	      ;; succeeded).
	      (if (and corresponding-relation?
		       (relation-exist-p block (relation-instance-items corresponding-relation?))
		       (relation-is-symmetric relation)
		       (neq relation-name-reference relation-name))

		  (unless (memq relation relations-with-changed-slots?)
		    (frame-push relation relations-with-changed-slots?))

		  (unless (and corresponding-relation?
			       (relation-exist-p block
						 (relation-instance-items corresponding-relation?)))
		    ;; There is no corresponding-relation.
		    (cond
		      ;; Try the inverse-name to see if the relation has
		      ;; changed from non-symmetric to symmetric.
		      ((and (eq relation-name-reference relation-name)
			    (relation-is-symmetric relation)
			    (when other-instances
			      (get-relation-instance
			        (or (inverse-of-relation relation)
				    (secret-inverse-name relation))
				other-instances)))
		       (unless (memq relation relations-with-changed-slots?)
			 (frame-push relation relations-with-changed-slots?)))
		      ;; Try the relation-name to see if the relation has
		      ;; changed from symmetric to non-symmetric.
		      ((and (eq relation-name-reference relation-name)
			    (null (relation-is-symmetric relation))
			    (get-relation-instance relation-name other-instances))
		       (unless (memq relation relations-with-changed-slots?)
			 (frame-push relation relations-with-changed-slots?)))
		      (t nil)))))))))

    ;; Add relations that violate one-to-one, one-to-many, and many-to-one
    ;; cardinality to relations-with-changed-slots (9), through (14).
    (loop for block in rendezvous-successful-blocks?
	  for relation-instances = (relation-instances block)
	  do
      (loop for relation-instance being each relation-instance of relation-instances
	    for relation = (relation-instance-relation relation-instance)
	    do
	(unless (memq relation relations-with-changed-slots?)
	  (let* ((relation-name-reference (relation-instance-name relation-instance))
		 (relation-name (relation-name relation))
		 (type-of-relation (type-of-relation relation))
		 (object-frames (relation-instance-items relation-instance)))
	    (when
		(and
		  (or
		    (eq type-of-relation 'one-to-one)
		    (and (eq type-of-relation 'one-to-many)
			 (eq relation-name-reference relation-name))
		    (and (eq type-of-relation 'many-to-one)
			 (neq relation-name-reference relation-name)))
		  ;; In these cases, block should only be related
		  ;; to at most one other instance. This is cases
		  ;; 12, 13, and 14.
		  (more-than-one-related-item-p object-frames))
	      (unless (memq relation relations-with-changed-slots?)
		(frame-push relation relations-with-changed-slots?)))))))

    ;; Supply the missing relation-instances that relate one item to another (5).
    ;; While doing this, check for violations of 'one-to-one, one-to-many,
    ;; and many-to-one constraints.

    (loop for block in rendezvous-successful-blocks?
	  for relation-instances = (relation-instances block)
	  do
      (when relation-instances
	(loop with copied-relation-instances = (copy-list-of-relation-instances
						 relation-instances)
	      for copied-relation-instance in copied-relation-instances
	      for relation-name-reference = (car-of-cons copied-relation-instance)
	      for relation = (cadr-of-cons copied-relation-instance)
	      for relation-name = (relation-name relation)
	      for other-relation-name-reference =
	      (if (neq relation-name-reference (relation-name relation))
		  (relation-name relation)
		  (if (relation-is-symmetric relation)
		      relation-name-reference
		      (or (inverse-of-relation relation)
			  (secret-inverse-name relation))))
	      for copied-object-frames = (cddr copied-relation-instance)
	      for type-of-relation = (type-of-relation relation)
	      do
	  (unless (memq relation relations-with-changed-slots?)
	    (loop for object-frame in copied-object-frames
		  for other-instances = (when object-frame (relation-instances object-frame))
		  for corresponding-relation?
		    = (when other-instances
			(get-relation-instance other-relation-name-reference
					       other-instances))
		  do
	      (if
		(and
		  (or
		    (eq type-of-relation 'one-to-one)
		    (and (eq type-of-relation 'one-to-many)
			 (neq relation-name-reference relation-name))
		    (and (eq type-of-relation 'many-to-one)
			 (eq relation-name-reference relation-name)))
		  ;; In this case, at most one other instance should
		  ;; be related to this one. This can fail in two ways.
		  ;; The instance block is related to might
		  ;; be related via the inverse relation to another
		  ;; instance. This is cases 15, 16, and 17.
		  corresponding-relation?
		  (loop for inverse-instance being each related-item of
			    (relation-instance-items corresponding-relation?)
			thereis (not (eq inverse-instance block))))
		;; We don't need to check the second failure case,
		;; cases (12), (13), and (14), explicity. Restoring the relation
		;; on the instance related to will transform a case of this
		;; problem into a case of (15), (16), or (17), which
		;; we will then catch when trying to restore
		;; the relation of the second related-to item.
		(unless (memq relation relations-with-changed-slots?)
		  (frame-push relation relations-with-changed-slots?))
		(unless (and corresponding-relation?
			     (relation-exist-p block
					       (relation-instance-items corresponding-relation?)))
		  ;; We remove the relation-instance from block and then call
		  ;; add-to-relation to put it back on block and on the related
		  ;; item.
		  (unless other-instances
		    (frame-push object-frame additional-related-blocks))

		  (let* ((block-relevant-relation-instance
			  (get-relation-instance relation-name-reference relation-instances))
			 (relevant-object-frames
			  (relation-instance-items block-relevant-relation-instance)))
		    ;; there are other object-class-frames
		    #-relation-instances-v2
		    (cond ((more-than-one-related-item-p relevant-object-frames)
			   (setf (cddr block-relevant-relation-instance)
				 (delete-slot-value-element
				   object-frame
				   relevant-object-frames)))
			  (t
			   ;; object-frame is the only object-class-frame
			   (setf (relation-instances block)
				 (setq relation-instances
				       (delete-slot-value-element
					 block-relevant-relation-instance
					 relation-instances)))
			   (reclaim-slot-value block-relevant-relation-instance)))

		    #+relation-instances-v2.0
		    (loop with queue = relevant-object-frames
			  for queue-element = #+Lockfree-Deque (constant-queue-next
								 (constant-queue-head queue) queue)
					      #-Lockfree-Deque (constant-queue-head queue)
					 then next-queue-element
			  until (or #+Lockfree-Deque (null queue-element)
				    #-Lockfree-Deque (eq queue-element queue)
				    (eq (queue-datum queue-element) object-frame))
			  for next-queue-element = (constant-queue-next queue-element queue)
			  finally
		      (cond (#+Lockfree-Deque (null queue-element)
			     #-Lockfree-Deque (eq queue-element queue)
			     #+development
			     (cerror "kb-load2" "unsuccessful relevant-object-frames clean"))

			    ((eq (queue-datum queue-element) object-frame) ; double check
			     ;; delete found queue element
			     (constant-queue-delete queue-element queue)

			     ;; delete the queue if possible
			     (when (related-items-is-empty-p queue) ; relevant-object-frames
			       (setf (get-relation-instance relation-name-reference relation-instances) nil)
			       (delete-relation-instance relation-name-reference relation-instances)
			       (reclaim-relation-instance block-relevant-relation-instance)))))

		    #+relation-instances-v2.1
		    (cond ((more-than-one-related-item-p relevant-object-frames)
			   (setf (get-related-item object-frame relevant-object-frames) nil)
			   (delete-related-item object-frame relevant-object-frames))
			  (t
			   (setf (get-related-item object-frame relevant-object-frames) nil)
			   (delete-related-item object-frame relevant-object-frames)
			   (when (related-items-is-empty-p relevant-object-frames)
			     (setf (get-relation-instance relation-name-reference relation-instances) nil)
			     (delete-relation-instance relation-name-reference relation-instances)
			     (reclaim-relation-instance block-relevant-relation-instance)))))

		  (if (eq relation-name relation-name-reference)
		      (add-to-relation
			relation-name-reference object-frame block t nil nil)
		      (add-to-relation
			other-relation-name-reference block object-frame t nil nil))
		  #+development
		  (let ((corresponding-relation1? (get-relation-instance
						    other-relation-name-reference
						    (relation-instances object-frame))))
		    (unless (and corresponding-relation1?
				 (relation-exist-p block (relation-instance-items corresponding-relation1?)))
		      (cerror "kb-load2" "unsuccessful completion-of-relation")))))))

	      finally (progn (reclaim-slot-value copied-relation-instances)
			     #+development
			     (when (duplicate-relation-instances-p
				     relation-instances)
			       (cerror
				 "kb-load2.lisp"
				 "duplicate relation-instances1"))))))

    ;; Remove all relation-instances that have relations with slot changes that
    ;; violate relation-instances.
    (when relations-with-changed-slots?
      (remove-relations relations-with-changed-slots?
			rendezvous-successful-blocks?)
			
      (remove-relations relations-with-changed-slots?
			additional-related-blocks))
    (reclaim-frame-list relations-with-changed-slots?)

    (frame-push (copy-frame-serial-number (current-frame-serial-number))
		rendezvous-successful-blocks?)
    (frame-push (copy-frame-serial-number (current-frame-serial-number))
		additional-related-blocks)
    (reclaim-gensym-list blocks-with-relation-instances-from-kb-read)
    (setq blocks-with-relation-instances-from-kb-read nil)))


    
;;; Remove any relation-instances in which either the subject or object
;;; frames violate the class type specified on the relation class-of-subject
;;; or class-of-object slots (6). This is now a separate function,
;;; since it needs to be performed after conflict resolution, so
;;; that class mismatches that will disappear when conflict resolution
;;; is performed do not lead to needless deletions.

(def-post-loading-function (delete-type-violating-relation-instances
			     :once-only t :after-conflict-resolution :always)
  (delete-type-violating-relation-instances-1 rendezvous-successful-blocks?)
  (setq rendezvous-successful-blocks? nil)
  (delete-type-violating-relation-instances-1 additional-related-blocks)
  (setq additional-related-blocks nil))

(defun delete-type-violating-relation-instances-1 (blocks)
  (let ((fsn (car blocks)))
    (loop for block in (cdr blocks)
	  do
      ;; This needs sanity-checking in the face of a reclassified-frame, which
      ;; in general does NOT want to be considered reprocessed.
	  (unless (frame-has-been-reprocessed-p block fsn)
	    (when (block-relation-instances-violate-class-type-p block)
	      (remove-invalid-relation-instances block))
	    #+development
	    (when (block-relation-instances-violate-class-type-p block)
	      (cerror "kb-load2" "relation class-type violation"))))
    (reclaim-frame-serial-number fsn)
    (reclaim-frame-list blocks)))

;;; remove any instances of these relations from the specified
;;; blocks.
(defun remove-relations (relations blocks)
  (loop for block in blocks
	for relation-instances = (relation-instances block)
	do
	#-relation-instances-v2
	(loop with current-pointer = relation-instances
	      with following-pointer = nil
	      until (null current-pointer)
	      for relation-instance = (car-of-cons current-pointer)
	      do
	  (cond ((memq (cadr-of-cons relation-instance)
		       relations)
		 (cond (following-pointer
			(setf (cdr following-pointer) (cdr current-pointer))
			(reclaim-slot-value-cons current-pointer)
			(setq current-pointer (cdr following-pointer)))
		       (t 
			(reclaim-slot-value-cons 
			  (prog1 (relation-instances block)
			    (setf (relation-instances block) (cdr (relation-instances block)))
			    (setq current-pointer (relation-instances block))))))
		 (reclaim-slot-value-list relation-instance))
		(t
		 (setq following-pointer current-pointer)
		 (setq current-pointer (cdr following-pointer)))))
    #+relation-instances-v2
    (when relation-instances
      (loop for relation-instance being each relation-instance of relation-instances
	    for relation-name = (relation-instance-name relation-instance)
	    for relation = (relation-instance-relation relation-instance)
	    with deleted-names = nil
	    do
	(when (memq relation relations)
	  (setf (get-relation-instance relation-name relation-instances) nil)
	  (slot-value-push relation-name deleted-names)
	  (reclaim-relation-instance relation-instance))
	    finally
	      (when deleted-names
		(loop for name in deleted-names do
		  (delete-relation-instance name relation-instances))
		(reclaim-slot-value-list deleted-names))))))











;;; The function `rendezvous-frames-and-denotations-in-aggregate-evaluation-values'
;;; replaces block denotation references (uuids or frame names) with and
;;; item-reference to their corresponding frames if they can be found, and
;;; replaces frames with an item-references.

;;; This function relies on the information stored in the global gensym-consed
;;; tree variable, frames-for-rendezvous-in-aggregate-values?, to locate the
;;; frames and slots that need attention.

;;; If there is a rendezvous failure, the value reverts to nil.

(def-post-loading-function (rendezvous-frames-and-denotations-in-aggregate-evaluation-values
			     :once-only t :after-conflict-resolution :never)
  (loop for info in frames-for-rendezvous-in-aggregate-values?
	for (frame frame-serial-number slot-descriptions) = info
	do
    (unless (frame-has-been-reprocessed-p frame frame-serial-number)
      (loop for slot-description in slot-descriptions
	    for slot-value = (get-slot-description-value frame slot-description)
	    do
	(when (aggregate-evaluation-value-p slot-value)
	  ;; There used to be a development-only cerror here for system-defined
	  ;; slots, but there doesn't seem to be any reason to differentiate
	  ;; between system-defined slots and user-defined slots so I took it
	  ;; out.  See HQ-5270861 "dev-only abort in
	  ;; rendezvous-frame-denotations-in-aggregate-evaluation-values".
	  ;; -dougo, 4/27/06
	  (replace-frame-denotations-in-aggregate-evaluation-value
	    slot-value frame-serial-number))))
    (setf (second info) nil)
    (reclaim-frame-serial-number frame-serial-number))
  (reclaim-gensym-tree frames-for-rendezvous-in-aggregate-values?)
  (setq frames-for-rendezvous-in-aggregate-values? nil))
	     
	    


;;; The function `replace-frame-denotations-in-aggreate-evaluation-value'
;;; replaces uuid or name references

(defun-simple replace-frame-denotations-in-aggregate-evaluation-value
    (evaluation-value frame-serial-number)
  (let* ((managed-array (evaluation-value-value evaluation-value))
	 (managed-array-length (managed-array-length managed-array)))
    (cond ((evaluation-sequence-p evaluation-value)
	   (loop for index from (evaluation-sequence-first-element-index)
			   below managed-array-length
		 for element = (managed-svref managed-array index)
		 do
	     (cond ((and (consp element)
			 (eq (car-of-cons element) 'frame-denotation))
		    (let* ((denotation (car-of-cons (cdr-of-cons element))))
		      (setf (managed-svref managed-array index)
			    (get-reference-to-item-if-item
			      (find-frame-for-denotation denotation 'block)))
		      (reclaim-slot-value-list element)))
		   ((frame-or-deleted-frame-p element)
		    (if (frame-has-been-reprocessed-p element frame-serial-number)
			(setf (managed-svref managed-array index) nil)
			(setf (managed-svref managed-array index)
			      (get-reference-to-item-if-item element))))
		   ((or (evaluation-sequence-p element)
			(evaluation-structure-p element))
		    (replace-frame-denotations-in-aggregate-evaluation-value
		      element frame-serial-number))
		   (t nil))))
	  ((evaluation-structure-p evaluation-value)
	   (loop for index from (1+f (estructure-first-attribute-index))
			   below managed-array-length by 2
		 for element = (managed-svref managed-array index)
		 do
	     (cond ((and (consp element)
			 (eq (car-of-cons element) 'frame-denotation))
		    (let* ((block-denotation (car-of-cons (cdr-of-cons element)))
			   (corresponding-frame?
			     (find-frame-for-denotation block-denotation 'block)))
		      (setf (managed-svref managed-array index)
			    (get-reference-to-item-if-item corresponding-frame?))
		      (reclaim-slot-value-list element)))
		   ((frame-or-deleted-frame-p element)
		    (if (frame-has-been-reprocessed-p element frame-serial-number)
			(setf (managed-svref managed-array index) nil)
			(setf (managed-svref managed-array index)
			      (get-reference-to-item-if-item element))))
		   ((or (evaluation-sequence-p element)
			(evaluation-structure-p element))
		    (replace-frame-denotations-in-aggregate-evaluation-value element frame-serial-number))
		   (t nil))))
	  (t nil))))

   
	     


(def-post-loading-function (fix-module-related-frame-notes-after-loading :once-only t)
  (update-module-related-frame-notes-for-all-workspaces))


;; Removed -- no longer needed as this is done in the initialize-after-reading
;; method on each instance of model-definition. (MHD 8/2/94)

;(declare-forward-reference install-models-after-loading-1 function)
;
;(def-post-loading-function install-models-after-loading
;  (install-models-after-loading-1))


;(declare-forward-reference assure-all-charts-have-style-1 function)

(declare-forward-reference assure-all-charts-are-modern-1 function)  ; CHARTS 

(def-post-loading-function (assure-all-charts-have-style :once-only t)
  (assure-all-charts-are-modern-1))



(def-post-loading-function ensure-connections-have-frames-if-necessary
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (all-connections-have-frames-if-necessary)
      (loop for block being each class-instance of 'block do
	(loop for connection-structure being each output connection of block 
	      as connection-frame-or-class = (connection-frame-or-class
					       connection-structure)
	      do
	  (when (and
		  ;; This must test with CLASSP now, instead of just
		  ;; with SYMBOLP, because (1) the next function cannot
		  ;; tolerate a non-class symbol, since slot-descriptions
		  ;; now cannot tolerate a non-class symbol, and (2) it
		  ;; has been discovered that at least one KB ("Ma:>mhd>
		  ;; abb-bad.kb", from ABB) has "classless" connections,
		  ;; i.e., connection structures giving the name of a
		  ;; class that does not exist in their
		  ;; connection-frame-or-class slot.  (MHD 9/14/92)
		  (classp connection-frame-or-class)
		  (always-instantiate-connection-frame-for-this-class?
		    connection-frame-or-class))
	    (make-new-connection-frame-for-connection
	      connection-structure connection-frame-or-class)))))))




;;; The `eliminate-procedure-invocation-frame-notes' post-loading function cleans
;;; up a bug which was in G2 during development of 3.0.  In this bug,
;;; compilation frame notes got entered into the frames notes for the component
;;; particulars for "(procedure-invocation)".  This happened during change the
;;; text of actions, and because procedures were not adequately cleaning up
;;; their computation context global variable scope.  These bugs have been
;;; fixed, and this post-loading function ensures that any frame notes generated
;;; during that period are removed.

(def-post-loading-function eliminate-procedure-invocation-frame-notes
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (procedure-invocation-frame-notes-fixed-p)
      (loop for block being each class-instance of 'block do
	(when (frame-status-and-notes block)
	  (delete-all-frame-notes-for-component-particular
	    '(procedure-invocation) block))))))




(def-post-loading-function fix-possible-non-symbols-in-g2-user-mode
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (possible-non-symbols-in-g2-user-mode-fixed-p)
      (loop for g2-window being each class-instance of 'g2-window
	    as g2-user-mode? = (get-slot-value g2-window 'g2-user-mode)	; fwd. ref.!
	    when (and g2-user-mode?
		      (not (symbolp g2-user-mode?)))
	      do (when (framep g2-user-mode?)
		   (delete-frame g2-user-mode?))
		 (set-slot-value g2-window 'g2-user-mode nil)))))	; fwd. ref.!

;; This was previously :once-only; it shouldn't have been because it depends on
;; kb-flags-from-last-kb-read.  There's a slight chance that some KBs did not get
;; this processing that needed. it! Time will tell... (MHD 8/24/95)

;; See the flag possible-non-symbols-in-g2-user-mode-fixed-p in KB-LOAD1 for further
;; information on this function.  (MHD 12/28/92)





;;; `fix-icon-variables-alists-in-icon-attributes-plist'
;;; icon-variables are stored in the icon-attributes-plist of an entity
;;; under the property-name 'variables.  The value was at one point an alist
;;; of variable names and values, but was changed to a plist.  The alist version
;;; was never shipped, however a sufficient number of kbs were created (internally)
;;; to warrent this conversion function.
;;; Also see function fix-icon-variables-alist-in-icon-description that fixes
;;; line-drawing-description DURING loading.

(defun convert-alist-to-plist (variables-alist?)
  (cond ((consp (car variables-alist?))
	 (loop with variables-plist = nil
	       for (variable-name variable-value) in variables-alist?
	       do
	   (slot-value-push variable-name variables-plist)
	   (slot-value-push variable-value variables-plist)
	       finally
		 (reclaim-slot-value-tree variables-alist?)
		 (return (nreverse variables-plist))))
	(t variables-alist?)))


(def-post-loading-function fix-icon-variables-alists-in-icon-attributes-plist ()
  (let ((kb-flags kb-flags-from-last-kb-read))
    (when (possible-icon-variables-alist-p)
      (loop for entity being each class-instance of 'entity
	    as icon-attributes-plist = (icon-attributes-plist entity)
	    as variables? = (getfq icon-attributes-plist 'variables)
	    when (variable-list-is-alist-p variables?)
	      do
		(setf (getf icon-attributes-plist 'variables)
		      (convert-alist-to-plist variables?))))))



;;; The post-loading-function `reset-assorted-system-parameters' resets some
;;; configurable system parameters to their backwards-compatible values, if the
;;; kb is pre-4.0: walking-menus: no, drawing-mode: xor.
;; Now done in initialize and initialize-after-reading methods.
;; -fmw, 6/15/95

;(def-post-loading-function reset-assorted-system-parameters
;  (let ((kb-flags kb-flags-from-last-kb-read))
;    (when kb-load-case?					    ; Don't do this for merge-kb.
;      (when (loading-version-3-or-earlier-kb-p)
; 	(when (system-table-installed-p menu-parameters)
; 	  (change-slot-value menu-parameters 'walking-menus nil))
; 	(when (system-table-installed-p drawing-parameters)
; 	  (change-slot-value drawing-parameters 'drawing-in-paint-mode-p nil))))))



;;; The post-loading-function `center-workspace-background-images' updates
;;; old background-images slots to have center-relative coordinates, instead
;;; of upper-left-relative.

(def-post-loading-function center-workspace-background-images ()
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (workspace-background-images-are-centered-p)
      (center-workspace-background-images-after-loading))))



;;; The post-loading-function `check-insert-action-duplicate-element-flag' sets
;;; a slot in the miscellaneous parameters system-table to indicate that the
;;; default behavior for the insert duplicate element error.

;;; KB's created before this KB flag, will ignore duplicate errors, as in
;;; version 3.0.

(def-post-loading-function check-insert-action-duplicate-element-flag ()
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (insert-action-duplicate-element-fix-in-kb-p)
      (set-ignore-insert-action-duplicate-element))))



;;; The post-loading-function `check-new-get-connection-vertex-behavior-flag' sets
;;; a slot in the miscellaneous parameters system-table to indicate that the
;;; default behavior g2-get-connection-vertices will return "extra" vertices
;;; per the old behavior

(def-post-loading-function check-new-get-connection-vertex-behavior-flag ()
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (new-get-connection-vertex-behavior-p)
      (set-get-connection-vertices-backward-compatibility))))


;;; The post-loading-function
;;; `check-print-means-print-to-server-in-configurations' sets the
;;; backwards-compatibility flag for pre-7.1r0 KBs which makes PRINT as an
;;; action in item-configurations mean print-to-server.

(def-post-loading-function check-print-means-print-to-server-in-configurations ()
  (unless (system-version-greater-p
	    system-version-from-last-kb-read
	    '#.(make-system-version 7 0))
    (set-print-means-print-to-server-in-configurations)))


;;; The post-loading-function `check-right-click-lifts-to-top-in-native-ui'
;;; sets the backwards-compatibility flag for pre-82r1 KBs that keeps the
;;; behavior that a right click on a workspace lifts it to the top.

;(def-post-loading-function check-right-click-lifts-to-top-in-native-ui ()
;  (unless (system-version-greater-p
;	    system-version-from-last-kb-read
;	    '#.(make-system-version 8 20)) ; Means 8.2r0!
;    (set-right-click-lifts-to-top-in-native-ui)))


;;; The post-loading-function
;;; `check-inconsistent-behavior-of-move-in-configurations' sets the
;;; backwards-compatibility flag for pre-8.0r1 KBs which makes MOVE as an action
;;; in item-configurations depend on whether the item has "move" in its
;;; menu. See HQ-839554. -fmw, 2/26/04 -- UPDATE: revised to be for 8.0r1,
;;; rather than for 7.1r1, as originally planned. -mhd, 8/11/04

(def-post-loading-function check-inconsistent-behavior-of-move-in-configurations ()
  (unless (system-version-greater-p
	    system-version-from-last-kb-read
	    '#.(make-system-version 8 0))
    (set-inconsistent-behavior-of-move-in-configurations)))


;;; The post-loading-function `update-representations-of-configuration-grammar'
;;; updates tables displaying the text of the old item/instance configuration
;;; grammar.  It also handles some fallout from renaming kb-restrictions to
;;; kb-configuration, which should have been handled much earlier.

(def-post-loading-function update-representations-of-configuration-grammar
  (let ((kb-flags kb-flags-from-last-kb-read))

    (unless (new-item-configuration-key-binding-grammar-p)

      ;; Update any labels of this guy's CLASS.
      (loop for config being each class-instance of 'kb-configuration doing
	(update-representations-of-slot-value config 'class))
      
      ;; Update displays of config grammar.
      (loop for block being each class-instance of 'block doing
	(when (frame-representations block)
	  ;; Item config.
	  (when (object-configuration block)
	    (update-representations-of-slot-value block 'object-configuration))

	  ;; Instance config.
	  (when (and (class-definition-p block)
		     (instance-configuration block))
	    (update-representations-of-slot-value block 'instance-configuration)))))))


;; put post loading loose-end and connection cleanup
;; look for some official remove-stub facility




;;; The post-loading-function `update-representations-of-class-specific-attributes-grammar'
;;; updates tables displaying the test of the old attributes-specific-to-class
;;; grammar.

(def-post-loading-function update-representations-of-class-specific-attributes-grammar
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (or (new-grammar-for-class-specific-attributes-p)
		(system-revision-greater-p
		  '#.(make-system-version 4 0 :quality release-quality :revision 0)
		  system-version-from-last-kb-read))
      (loop for class-definition being each class-instance of 'class-definition
	    do
	(when (and (class-specific-attributes class-definition)
		   (frame-representations class-definition))
	  (update-representations-of-slot-value
	    class-definition 'class-specific-attributes))))))

;; Note: this cannot be once-only because it uses kb-flags-from-last-kb-read.


(def-post-loading-function update-representations-of-default-overrides-grammar
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (fixed-representations-of-default-overrides-p)
      (loop for class-definition being each class-instance of 'class-definition
	    do
	(when (and (default-overrides class-definition)
		   (frame-representations class-definition))
	  (update-representations-of-slot-value
	    class-definition 'default-overrides))))))

(def-post-loading-function update-representations-of-initial-value-of-variable-or-parameter
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (fixed-representations-of-default-overrides-p)
      (loop for v-or-p being each class-instance of 'variable-or-parameter
	    do
	(when (frame-representations v-or-p)
	  (update-representations-of-slot-value
	   v-or-p 'initial-value-of-variable-or-parameter))))))




(def-post-loading-function remove-bogus-stubs-on-frames-in-attributes
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (and (strict-prohibition-of-connections-on-frames-in-attributes-p)		 
		 (system-revision-greater-p ; See note below! (MHD 8/24/95)
		   system-version-from-last-kb-read
		   '#.(make-system-version 4 0 :quality release-quality :revision 0)))
      (loop for block being each class-instance of 'object
	    do
	(when (and (parent-frame block)
		   (parent-attribute-name block))
	  (loop for connection being each connection of block
		collect connection into connections-to-delete
		using gensym-cons
		finally
		  (loop for connnection in connections-to-delete
			do
			;; I don't think its possible for these connections
			;; to have (in/out)put ends because of bogus connections
			;; are never fully written out in kb-saves in the first
			;; place.
		    (cond ((or (input-end-object connection)
			       (output-end-object connection))
			   (cond
			     ((and (input-end-object connection)
				   (output-end-object connection))
			      (delete-connection connection))
			     (t
			      #+development
			      (cerror
				"go"
				"found a seeming valid connection in a sub-frame")
			      )))
			  (t
			   (delete-connection-in-block block connection t)
			   (frame-serial-number-setf (frame-serial-number-for-connection connection)
						     (frame-serial-number-recycled))
			   (reclaim-connection connection))))
		  (reclaim-gensym-list connections-to-delete)))))))

;; This was previously :once-only; it shouldn't have been because it depends on
;; kb-flags-from-last-kb-read.  There's a slight chance that some KBs did not get
;; this processing that needed. it! Time will tell... (MHD 8/24/95)
;;
;; Note that this existed as of 4.0 Rev. 0, as a once-only, and now is being
;; made an every-time post-loading function as of Rev. 1.  This is here to
;; prevent a serious corrupting situation, so I'm therefore making it run for
;; all pre-Rev. 1 KBs. (MHD 8/24/95)


(def-post-loading-function (fix-kb-workspaces-that-might-be-too-big :once-only t)
  (when t ;; "workspaces might be too big" -- a kb flag??
    (loop for workspace being each class-instance of 'kb-workspace
	  do (shrink-wrap-workspace-around-maximum-rectangle workspace))))

;; NOTE: MISTAKE IN 4.0, through rev. 2! The :once-only was kept in the code
;; despite the following note.  I decided to fix this by just taking out the
;; flag check.  It failed in development, but it probably "happened to work"
;; in production.  (MHD 2/14/96)
;;
;; This was previously :once-only; it shouldn't have been because it depends on
;; kb-flags-from-last-kb-read.  There's a slight chance that some KBs did not get
;; this processing that needed. it! Time will tell... (MHD 8/24/95)

;; The need for this is partially explained by in the def-concept for
;; workspace-unit.  The other change that's going in simultaneously, namely to
;; transform-image, as explained in this doc (from
;; shrink-wrap-workspace-around-maximum-rectangle):
;;
;;    If this can't make a workspace small enough, transform-image must, and
;;    can, still cope with it, scaling it down as necessary to have window
;;    coordinates as small as the largest "allowable" workspace.



;; The following post-loading function deletes connection frames that do not
;; have associated connection structures.  Such frames are present in GUIDEMO
;; kbs of 6/22/95 and 9/14/95.  It was not possible to delete such frames
;; because the cleanup method for connection frames expected a structure (the
;; method has been changed to deal with missing structures so that the corrupted
;; connection frames can be deleted by this post-loading function).  Another
;; characteristic of these frames was that they also lacked a module assignment,
;; making it impossible to save a kb in modularized form.  (ghw 9/16/95)

(def-post-loading-function (delete-connection-frames-without-connection-structures
			     :once-only t)
  (loop for connection-frame being each class-instance of 'connection
	when (null (connection-for-this-connection-frame connection-frame))
	do (delete-frame connection-frame)))

(def-post-loading-function fixup-all-author-or-authors
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (does-not-need-null-author-fixup-p)
      (loop for frame being class-instance of 'block
	    for author-or-authors = (frame-author-or-authors frame)
	    do
	(when author-or-authors
	  (let ((new-value-or-nil
		  (fixup-author-or-authors-value author-or-authors)))
	    (when new-value-or-nil
	      (change-slot-value
		frame 'frame-author-or-authors
		new-value-or-nil))))))))



(def-post-loading-function fixup-all-digital-clocks
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (digital-clocks-are-fixed-p)
      (loop for frame being class-instance of 'digital-clock
	    for first-row = (first (table-rows frame))
	    when (first first-row)
	      do (reclaim-slot-value (first first-row))
		 (setf (first first-row) nil)
		 (reformat-table-in-place frame)
		 (update-images-of-block frame nil t)))))






(defun-void normalize-message-properties-for-message-definition (message-definition)
  (let* ((message-properties (default-message-properties message-definition))
	 (normalized-message-properties
	   (loop for sym in '(line-color background-color border-color
			      minimum-width minimum-height font)
		 for value = (cdr (assq sym message-properties))
		 when value
		   collect (slot-value-cons sym value) using slot-value-cons)))
    (setf (default-message-properties message-definition) normalized-message-properties)
    (reclaim-slot-value message-properties)))








;;; `get-updated-edges-from-elements-and-background' checks
;;; the candidate edges to see if they actually enclose all
;;; the elements on the workspace, and returns larger
;;; dimensions if necessary.

(defun get-updated-edges-from-elements-and-background (workspace left top right bottom margin)
  (let ((new-left left)
	(new-top top)
	(new-right right)
	(new-bottom bottom))
    (when (or (has-subblocks-p workspace) ; code stolen from shrink-wrap-workspace
	      (has-background-images-p workspace))
      (with-extreme-edges-minimizing-workspace (workspace)
	(when (has-subblocks-p workspace)
	  (update-extreme-edges-from-elements workspace))
	(update-extreme-edges-from-background-images workspace)  ; Possible bg images.
	(setq new-left   (minw left   (-w extreme-left-edge-so-far margin)))
	(setq new-top    (minw top    (-w extreme-top-edge-so-far margin)))
	(setq new-right  (maxw right  (+w extreme-right-edge-so-far margin)))
	(setq new-bottom (maxw bottom (+w extreme-bottom-edge-so-far margin)))))
    (values new-left new-top new-right new-bottom)))




(def-post-loading-function maybe-normalize-workspace-edges ()
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (workspace-edges-are-normalized-p)
      (loop for workspace being each class-instance of 'kb-workspace
	    do (let ((old-left (left-edge-of-block workspace))
		     (old-top (top-edge-of-block workspace))
		     (old-right (right-edge-of-block workspace))
		     (old-bottom (bottom-edge-of-block workspace))
		     (margin (workspace-margin workspace)))
		 (multiple-value-bind (new-left new-top new-right new-bottom)
		     (get-updated-edges-from-elements-and-background
		       workspace old-left old-top old-right old-bottom margin)
		   (setf (left-edge-of-block workspace) new-left)
		   (setf (top-edge-of-block workspace) new-top)
		   (setf (right-edge-of-block workspace) new-right)
		   (setf (bottom-edge-of-block workspace) new-bottom)))))))



(def-post-loading-function reset-default-window-style-if-needed
  ()
  (let ((kb-flags kb-flags-from-last-kb-read))
    (when (loading-version-5-or-earlier-kb-p)
      (let ((misc-params?
	      (or (if name-of-module-being-read?
		      (get-system-table-instance-for-module
			'miscellaneous-parameters
			name-of-module-being-read?))
		  miscellaneous-parameters)))
	(when misc-params?
	  (change-slot-value
	    misc-params? 'default-window-style 'g2-5.x))))))

;; Note that this cannot be done as an initialize-after-reading method due to
;; the fact that system tables with no nondefault values are not saved in KBs
;; in version 5, and the initialize-after-reading method therefore may not
;; get called therefore.


;;; The post-loading function `delete-bad-connection-structures' deletes bad
;;; connections on blocks in blocks-with-bad-connections, which was computed
;;; during KB loading.  Dangling LOOSE-END blocks are also deleted.  A bad
;;; connection is one satisfying `bad-connection-p'.

(def-post-loading-function delete-bad-connection-structures
  (when blocks-with-bad-connections
    (let* ((reference-fsn (car blocks-with-bad-connections))
	   (blocks (cdr blocks-with-bad-connections))
	   (count (reclaim-bad-connections-of-blocks blocks reference-fsn)))

      (when (>f count 0)
	(notify-user-at-console-and-on-logbook
	  "Cleared ~d unattached connection~a from ~a."
	  count (if (=f count 1) "" "s")
	  (or name-of-module-being-read? "KB")))

      (reclaim-gensym-list blocks-with-bad-connections)
      (reclaim-frame-serial-number reference-fsn)
      (setq blocks-with-bad-connections nil))))

#+connections-v2
(def-post-loading-function (upgrade-block-connections-to-connections-v2 :once-only t)
  (when blocks-with-connections-from-kb-read
    (loop for block in blocks-with-connections-from-kb-read
	  ;; GENSYMCID-1679: blocks-with-connections-from-kb-read
	  ;; In case the block has been reclaimed during KB (post-)loading processes,
	  ;; skip the further upgradation. -- Chun Tian (binghe), Mar 25, 2016.
	  when (framep block)
	  do
      (upgrade-block-connections block))
    (reclaim-gensym-list blocks-with-connections-from-kb-read)
    (setq blocks-with-connections-from-kb-read nil)))

;; See g2-clear-floating-connection-structures for similar code.
;; See HQ-4162779, HQ-3387902.

;; Note that this won't work as a once-only function because the
;; blocks-with-bad-connections list is lost by then.


(defmacro get-system-table-during-load (name)
  `(if name-of-module-being-read?
       (get-system-table-instance-for-module ',name name-of-module-being-read?)
       ,name))

(def-post-loading-function classic-kbs-prefer-classic-editor
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (at-or-beyond-kb-format-revision-number-p g2-version-8-1-alpha-0-kb-flags)
      (let ((editor-parameters? (get-system-table-during-load editor-parameters)))
	(when editor-parameters?
	  (change-slot-value editor-parameters? 'prefer-native-editor nil))))))

(def-post-loading-function classic-kbs-prefer-classic-ui-features
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (at-or-beyond-kb-format-revision-number-p g2-version-82r0-kb-flags)
      (let ((logbook-parameters? (get-system-table-during-load logbook-parameters)))
	(when logbook-parameters?
	  (change-slot-value logbook-parameters? 'prefer-native-logbook nil)))
      (let ((message-board-parameters? (get-system-table-during-load message-board-parameters)))
	(when message-board-parameters
	  (change-slot-value message-board-parameters? 'prefer-native-message-board nil)))
      (let ((miscellaneous-parameters? (get-system-table-during-load miscellaneous-parameters)))
	(when miscellaneous-parameters
	  (change-slot-value miscellaneous-parameters? 'prefer-native-login-dialog nil))))))

(def-post-loading-function classic-kbs-prefer-classic-selection-highlighting
  (let ((kb-flags kb-flags-from-last-kb-read))
    (unless (at-or-beyond-kb-format-revision-number-p g2-version-8-3-alpha-0-kb-flags)
      (let ((drawing-parameters? (get-system-table-during-load drawing-parameters)))
	(when drawing-parameters?
	  (change-slot-value drawing-parameters? 'show-selection-handles nil))))))

(def-post-loading-function check-ignore-snap-grid-in-transfer-operations ()
   (unless (at-or-beyond-kb-format-revision-number-p g2-version-8-3-alpha-0-kb-flags)
     (set-ignore-snap-grid-in-transfer-operations)))

;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module KB-SAVE1: Saving Knowledge Bases

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson, Michael Levin, Mark H. David





;; The following to KB-SAVE2

(declare-forward-references
  (convert-permanent-list-structure-for-saving function lists)
  (convert-permanent-array-structure-for-saving function arrays)
  (check-pane-description-for-unwritten-workspaces function kb-save2)
  (saving-parameters variable kb-save3)
  (increment-compiled-kb-file function kb-save3)
  #+development
  (show-code-body function stack-utils)
  (write-byte-code-body function stack-utils)
  (save-kb function kb-save3)
  (module-contains-text-stripped-frames-p function kb-save4)

  (reclaim-modified-pane-description function kb-save2)

  (write-variable-data-for-kb function histories)
  (write-parameter-data-for-kb function histories)
  (write-simulation-subtable-data-for-kb function histories)
  (procedure-definition-of-code-body-function function proc-utils)
  (code-bodies-function function proc-utils)
  (code-body-byte-code-body-function function proc-utils)
  (code-body-entry-points-function function proc-utils)
  (superior-frame function activate)

  (write-trend-chart-data-for-kb function graphs)
  (lisp-for-byte-code-body function stack-kern)
  (inlined-function-data function stack-kern)
  (inlined-function-data-given-arg-count function stack-kern)
  (inlined-function-c-name function stack-kern)
  (inlined-function-argument-type function stack-kern)
  (inlined-function-return-type function stack-kern)
  (inlined-function-numbered function stack-kern)
  (c-byte-code-inlined-functions variable stack-kern)
  (byte-code-body-contains-backward-branch-p function stack-utils)
  (byte-code-body-contains-instruction-that-should-not-be-compiled-p function stack-utils)
  (byte-code-body-is-too-long-to-compile-p function stack-utils)
  (media-stream-p-function function media)
  (reclaim-xml-object-and-fixups function kb-save4)

  (write-hash-table-data-for-kb function hash-tables))



;;;; Saving OK Files


;;; OK files are saved out so as to be "backward compatible", i.e., loadable in
;;; earlier versions of G2.
;;;
;;; This is not a general facility.  It is only to be used in development, by
;;; authorized individuals, and only for the purpose of maintaining a Gensym
;;; site OK file.
;;;
;;; The only developer authorized to maintain this at present is Mark David
;;; (MHD).
;;;
;;; The function `save-ok-file' is used to save an OK file.  Its only argument
;;; is namestring, a string giving a pathname.  Namestring is not recycled.
;;;
;;; Save-ok-file works by calling save-kb in a new way.  Save-kb's third
;;; argument can now be OK-KB-SAVE.  This is to be used when saving an OK file
;;; only.  OK files have instances of only the following classes, strict
;;; instance unless otherwise indicated:
;;;
;;;    OK
;;;    USER
;;;    SYSTEM-FRAME, and subclasses as they existed in 3.0 Rev. 0
;;;    FORMAT-FRAME, and subclasses as they existed in 3.0 Rev. 0
;;;    KB-WORKSPACE
;;;    FREE-TEXT
;;;    BORDERLESS-FREE-TEXT
;;;    NAME-BOX
;;;
;;; At present, our target version is G2 3.0 Rev. 0.  When slot names are added,
;;; they should be added to to the list slots-to-skip-saving-in-ok-files.
;;;
;;; Instances of new class cannot be added to the standard OK file, at least
;;; without work to include a definition that would load with it in 3.0.
;;;
;;; If any new classes were have instances in all KBs -- system frames, format
;;; frames, etc., there would be work.
;;;
;;; If a new system table were to be added, it would probably work to simply not
;;; save it in an OK file.  There's no provision for this yet.
;;;
;;; If things get too hard, we can abandon this.  As time passes, we can also at
;;; least abandon really old versions for newer ones, e.g., 3.0 Rev. 0 for 4.0,
;;; say.

(defvar ok-file-saving-mode? nil)

(defun make-system-version-for-ok-file ()
  '#.(make-system-version
       3 0
       :quality release-quality
       :revision 5))

(defun make-kb-flags-for-ok-file ()
  234)

(defvar slots-to-skip-saving-in-ok-files
  ;; all slots added since 3.0
  '(user-annotations			; on all items (old name)
    object-configuration
    walking-menus			; on menu-parameters system table

    left-edge-of-content-of-block-1 ;; these four slots are now obsolete -- ben, 12/19/94
    top-edge-of-content-of-block-1
    right-edge-of-content-of-block-1
    bottom-edge-of-content-of-block-1

    object-passing-info?

    remembered-block-transform		; these from text-box-format,
    position-of-horizontal-elevator	;   apparently (MHD 2/2/95)
    position-of-vertical-elevator
    
    ;; for ok's, so can't skip if saving a 4.0 OK file, since
    ;; this is needed in 4.0. (MHD 2/2/95)
    ;; maximum-number-of-concurrent-floating-telewindows-allowed
    ))


#+development
(defun save-ok-kb (namestring)
  (save-kb (gensym-pathname (copy-text-string namestring)) 'ok-kb-save))

;; Consider making this facility #+development only.  Note that there is no
;; security risk here.  This just enables saving out backward compatible
;; KBs.






;;;; KB-Save Data Structures





;;; The `kb-transfer' structure is used to hold state while reading and writing
;;; knowledge bases.  This is a new structure being retrofitted onto G2.  When
;;; this is completed, it will be part of a renovated KB save/load facility
;;; that can
;;;
;;;     save any number of KBs (including modules) while running, in parallel
;;;     read any number of KBs (including modules) while running, in parallel
;;;     save and load at the same time
;;;     save and load over the network (via ICP)
;;;
;;; In short, this facility will be the basis of new `Knowledge Passing'
;;; facilities.  (MHD 12/9/93)

(def-structure kb-transfer
  (kb-transfer-direction :output)  
  (kb-transfer-medium :stream)	; :stream or :network
  (kb-transfer-socket? nil)

  ;; next four slots relevant only for medium = :stream case:
  (kb-transfer-stream? nil)		; nil => bitsink
  ;; next three slots relevant only if ...-stream? is non-nil.
  (kb-transfer-pathname
    nil :reclaimer reclaim-gensym-pathname) ; arbitrary init
  (kb-transfer-namestring
    nil :reclaimer reclaim-text-string) ; arbitrary init
  (kb-transfer-user-namestring
    nil :reclaimer reclaim-text-string) ; arbitrary init
  (kb-transfer-stream-uses-crlf? nil)   ; arbitrary init
  
  (kb-transfer-base-reference? nil)	; nil or base-reference, a pos. fixnum
					; non-nil means encrypt? is true 

  (kb-transfer-serial-number? nil)	; needed?
  
  (kb-transfer-numeric-symbols nil)	; for now, for kb-save only  
  (kb-transfer-pane-description?	; for now, for kb-save only  
    nil :reclaimer reclaim-modified-pane-description)

  (kb-transfer-kb-file-progress-display? nil)


  ;; `kb-transfer-stream-open?' is used to track the fact of an open file
  ;; as well as is possible given the OS, so as to close it exactly once, even
  ;; if an abort occurs. It is set t as soon as it is determined that a stream
  ;; for the file exists, and set nil just before closing that stream.  --
  ;; (previously a system variable was defined -- same name as this slot) (MHD
  ;; 1/12/93)

  (kb-transfer-stream-open? nil)

  (kb-transfer-compiled-stream? nil)		; nil => bitsink
  ;; next three slots relevant only if ...compiled--stream? is non-nil.
  (kb-transfer-compiled-pathname
    nil :reclaimer reclaim-if-gensym-pathname) ; arbitrary init
  (kb-transfer-compiled-stream-open? nil)
  (jv-unused-slot-1 nil)
  (jv-unused-slot-2 nil)
  )



(defconstant write-kb-buffer-length 2048) ; documented below


(def-hash-table kb-fsn-hash-table
    :constructor make-kb-fsn-hash-table
    :reclaimer reclaim-kb-fsn-hash-table
    :key-comparitor frame-serial-number-equal-function
    :key-reclaimer reclaim-frame-serial-number
    :hash-function-or-macro frame-serial-number-hash-function
    :size 131 ; use a prime number
    )

(def-binary-tree frame-reference-balance
    :constructor make-frame-reference-balance-tree
    :reclaimer reclaim-frame-reference-balance-tree
    :accessor get-frame-reference-balance
    :key-deleter delete-frame-reference-balance
    :key-comparitor eq
    :hash-function frame-hash)

(def-structure (kb-save
		 (:include kb-transfer)
		 (:constructor make-kb-save-internal))
  (kb-save-fsn-hash-table (make-kb-fsn-hash-table) :reclaimer reclaim-kb-fsn-hash-table)
  (kb-save-fsn-index 0)
  (kb-object-index-property-name nil)
  (next-kb-object-index 0)
  (last-thing-written-was-an-index? nil)

  ;; `write-kb-buffer' is a simple text string, of length determined by the
  ;; constant write-kb-buffer-length, which is used by the low-level writing
  ;; routines to buffer their output.
  
  (write-kb-buffer
    (obtain-simple-gensym-string write-kb-buffer-length)
    :reclaimer reclaim-gensym-string) 

  ;; `Next-unoccupied-write-kb-buffer-index' is the index in the write buffer
  ;; used by write-char-for-kb and associated function.
  
  (next-unoccupied-write-kb-buffer-index 0)
  

  ;; `String-from-write-error-during-save?'  is either a reclaimable string
  ;; which describes the first file-writing error encountered during this save,
  ;; or nil if no file writing error was encountered.
  
  (string-from-write-error-during-save?
    nil :reclaimer reclaim-slot-value)
  
  
  (symbols-with-earlier-kb-object-indices
    nil :reclaimer reclaim-journal-list-function)
  
  ;; Instead of keeping track of symbols with earlier kb object indices while
  ;; writing a kb, consider either (a) leaving the properties on the symbols
  ;; indefinitely and using a new property name each time a kb is saved or (b)
  ;; mapping through all symbols in the AB package to remove the properties,
  ;; where it can be done efficiently.  The advantage is that fewer transient
  ;; conses are required during saving.  The disadvantage is that symbol plist
  ;; conses are not (as efficiently) reclaimed.  Alternatively, consider using,
  ;; for this purpose, the sorts of vectors that are used while reading a kb,
  ;; even if it is a bit clumsy to do so.

  ;; When the save is completed, the elements of this list need to be kept
  ;; around for journalling.  Journals dependent on a saving context need to
  ;; reference this list after the save.  Consider if journaling is revived!
  ;; (MHD 1/14/93)

  (length-of-saved-kb-line-so-far 0)
  (number-of-kb-lines-so-far 0)


  ;; `finished-writing-definitions?' is initially nil. It becomes true just
  ;; before the first top-level kb-workspace is written. It is a flag used to
  ;; avoid writing definitions twice. It also serves as an indicator of whether
  ;; the save has progressed to the point where it is possible to write modified
  ;; frames out of order.

  (finished-writing-definitions? nil)

  
  ;; `Frame-reference-balance' is part of a check on the integrity of writing a
  ;; KB.  Every frame which is referenced must be written, unless it is a
  ;; user-defined attribute with no slots to save, in which case it need not be
  ;; written, although it may be. (An example in which it would be written is
  ;; when it has a slot changed by the actions of the running KB, requiring it to
  ;; be written, before it has been encountered by the traversal of the KB, which
  ;; would mark it as having been written, but would not actually write it.)
  ;; When a #\G reference is written for a block, frame-reference-balance is
  ;; incremented.  The frame will be marked as referenced. When either #\F for
  ;; the frame is written, or when the frame is encountered as an attribute in
  ;; the traversal and not served to the traversal state because it has no slots
  ;; to save, it is marked as written, and frame-reference-balance is
  ;; decremented. Accordingly, after writing out a KB, frame-reference-balance
  ;; should be 0, and every frame marked as referenced should also be marked as
  ;; written. This should work for saving modules also.  It will not work for
  ;; incremental saves without modification.

  (frame-reference-balance 0)

  ;; GENSYMCID-1214: Error while saving KB
  ;;
  ;; `frame-reference-balance-tree' is holding each frame when it's balance being
  ;; increased, they're removed from the tree once the balance is decreased. In
  ;; this way, if `frame-reference-balance' is not zero, the left items in the
  ;; tree should be the problematic ones.

  (frame-reference-balance-tree (make-frame-reference-balance-tree)
    :reclaimer reclaim-frame-reference-balance-tree)

  ;;; `Deferred-kb-save-write-buffers' ... a slot-value list of simple strings.
  ;;; (They must be simple because all strings that get passed to stream
  ;;; operations must be simple.)  Unlike write-kb-buffer, these are of exact
  ;;; lengths needed, i.e., they have no fill pointer.  However, if there are
  ;;; more than one of them, they'll all end up the same, constant length (i.e.,
  ;;; the maximum, 2048).
  ;;;
  ;;; This is maintained as a FIFO queue: elements are added to at the end
  ;;; (nconc'ed).  The elements are then drained from the front (popped)
  ;;; when it's time to write them.
  (deferred-kb-save-write-buffers nil
      :reclaimer reclaim-deferred-kb-save-write-buffers)
  
  (original-kb-state-plist-written? nil)
  
  (kb-transfer-previous-timestamp? nil)
  
  (kb-module-being-saved? nil)

  (format-for-kb-save nil)
  
  

  ;; `Kb-traversal-state-for-backup' has the form
  ;; 
  ;;    ( { (reference-frame-serial-number .  nodes) } )
  ;;
  ;; where nodes is a list of frames or connections to be written, and
  ;; reference-frame-serial-number is a frame-serial-number to verify that the
  ;; frames in the list have not been deleted. See traverse-kb-for-saving (in
  ;; TRAVERSALS).
  ;;
  ;; This is initialized to the tree
  ;;
  ;;    ((<current-frame-serial-number> . (:KB)))
  ;;
  ;; The conses that make up this slot are journal conses.  This slot has
  ;; reclaim-journal-tree-function as its reclaimer.

  (kb-traversal-state-for-backup
    (journal-list (journal-list (copy-frame-serial-number (current-frame-serial-number)) :kb))
    :reclaimer reclaim-kb-traversal-state)


  (write-compiled-kb-buffer
    (obtain-simple-gensym-string write-kb-buffer-length)
    :reclaimer reclaim-gensym-string)
  (next-unoccupied-write-compiled-kb-buffer-index 0)
  (length-of-saved-compiled-kb-file-so-far 0)
  (deferred-compiled-kb-save-write-buffers nil :reclaimer reclaim-slot-value)

  (compiled-kb-byte-code-body-count 0)
  (starting-byte-code-body-count 0)
  (compiled-kb-emitted-files-count 1)

  (xml-object-for-module nil :reclaimer reclaim-xml-object-and-fixups)

  (kb-save-log-message-for-commit-after-saving-p nil :reclaimer reclaim-if-text-string)

  ;; `saving-is-started?' becomes true when saving process is started and 
  ;;  initial plist has been written to KB
  (saving-is-started? nil))

(defun reclaim-kb-traversal-state (list)
  (loop for x in list do
    (reclaim-frame-serial-number (prog1 (car x) (setf (car x) nil))))
  (reclaim-journal-tree list))

(def-kb-specific-variable kb-object-index-property-name-pool kb-save1
  nil t reclaim-gensym-list-function)

(defvar next-object-index-property-number 0)



(defun-void set-compiled-kb-file-pathname (kb-save pathname index)
  (let* ((indexed-basename
	   (cond
	     #+development
	     (emit-lisp-p
	      (twith-output-to-text-string
		(twrite-string (gensym-pathname-name pathname))))
	     (t (twith-output-to-text-string
		  (twrite-string (gensym-pathname-name pathname))
		  (twrite-string #w"_")
		  (twrite-fixnum index))))))
    (setf (kb-transfer-compiled-pathname kb-save)
	  (gensym-make-pathname :defaults indexed-basename
				:directory
				(gensym-pathname-directory
				  pathname)
				:type  (cond
					 #+development
					 (emit-lisp-p #w"lisp")
					 (t #w"c"))))
    (reclaim-text-string indexed-basename)))


(defun make-kb-save
    (pathname serial-number module? pane-description? use-clear-text? log-message-for-commit-after-saving? use-crlf?)
  (let ((kb-save (make-kb-save-internal)))
    (setf (kb-transfer-direction kb-save) :output)
    (setf (kb-transfer-medium kb-save) :stream)	; other modes not yet supported!
    (setf (kb-transfer-pathname kb-save) pathname)
    (setf (kb-transfer-namestring kb-save) (gensym-namestring pathname))
    (setf (kb-transfer-user-namestring kb-save)
	  (copy-text-string
	    (kb-transfer-namestring kb-save)))
    (setf (kb-transfer-stream-uses-crlf? kb-save) use-crlf?)
    (cond
      (enable-saving-compiled-kbs-p
       (set-compiled-kb-file-pathname
	 kb-save pathname 1))
      (enable-loading-compiled-kbs-p
       (let ((compiled-file-pathname
	       (pathname->shared-file-pathname pathname)))
	 (when (gensym-probe-file compiled-file-pathname)
	   (gensym-delete-file compiled-file-pathname))
	 (reclaim-gensym-pathname compiled-file-pathname))))
    
    (setf (kb-object-index-property-name kb-save)
	  (if kb-object-index-property-name-pool
	      (gensym-pop kb-object-index-property-name-pool)
	      (intern-text-string
		(tformat-text-string
		  "OBJECT-INDEX-PROPERTY-~d"
		  (incff next-object-index-property-number)))))

    (setf (kb-transfer-serial-number? kb-save) serial-number)
    (setf (kb-module-being-saved? kb-save) module?)    
    (setf (kb-transfer-pane-description? kb-save) pane-description?)
    (setf (format-for-kb-save kb-save) (if use-clear-text? 'clear-text 'normal))
    (setf (kb-save-log-message-for-commit-after-saving-p kb-save)
	  (copy-if-text-string log-message-for-commit-after-saving?))
    
    kb-save))






;;;; Saving-contexts



;;; A `kb save' is a structure whose slots hold contextual information that is
;;; used by the saving, backup, and journalling machinery.  The kb-save
;;; structure is further described, and defined, in KB-SAVE1.
;;;
;;; A `saving context' is a structure that holds the values for certain special
;;; variables that are to be bound around saving activity.  At present, the only
;;; such variable is `current-kb-save', which holds current kb save structure,
;;; and gets is value from the slot `saving-context-kb-save'.  The slot
;;; list-of-kb-saves-in-progress must be set up at the time of the setup of the
;;; saving context, and it and its variable and the top level conses of its
;;; value must not change during the entire course of the save.
;;;
;;; The term `saving context' also refers to the dynamic extent created by the
;;; with-saving-context macro.
;;;
;;; The macro `with-saving-context' iterates over each kb-save structure with
;;; current-saving-context and current-kb-save bound appropriately.  Body is
;;; executed once for every kb-save structure in list-of-kb-saves-in-progress.
;;; Current-saving-context is never to be setq'd; it should only be bound via
;;; this macro, and it's only value should be the binding this macro gives it.

(def-structure (saving-context
		 (:constructor
		   make-saving-context-internal
		   (list-of-kb-saves-in-progress
		     type-of-kb-save
		     save-permanent-data?
		     save-runtime-data?
		     saving-context-kb-file-progress-displays
		     saving-compiled-kbs-p)))

  (list-of-kb-saves-in-progress nil :reclaimer reclaim-journal-list)
  

  ;; `type-of-kb-save' is true when a kb-save or backup has been started and is
  ;; not yet complete. It holds its value during suspensions.  Its value, if
  ;; true, is a symbol which can be KB-SAVE, BACKUP, KB-SAVE-WITH-RUNTIME-DATA
  ;; or RUNTIME-DATA-ONLY.
  
  type-of-kb-save
  ;; NOTE: This slot, type-of-kb-save, used to be a system variable named
  ;; kb-save-or-backup-in-progress-p in the 3.0 release of the software.
  ;;
  ;; NOTE -- N.B.! -- the existence of a misspelling, RUNTINE [sic], with an N,
  ;; instead of RUNTIME, with an M, is now known.  Dealing with it has been
  ;; deferred however.  (MHD 1/11/93)

  ;; The type of a kb-save from the user's view is SAVE-KB or
  ;; SAVE-KB-WITH-RUNTINE-DATA. These symbols ought to replace KB-SAVE and
  ;; KB-SAVE-WITH-RUNTINE-DATA in all occurnaces. This requires a recompile of
  ;; all files, and is deferred to after 3.0 release. The function g2-save-kb now
  ;; performs a transation from the user's symbols to the internal symbols. These
  ;; symbols also occur at the begginning of saved KB files, unfortunately. For
  ;; the present, the user's symbols are being translated into internal symbols
  ;; when the initial plist is read, and the reverse transation when it is
  ;; written. ML. 9/23/91
  

  ;; `save-runtime-data?' is true when the type-of-kb-save slot of this
  ;; structure is KB-SAVE-WITH-RUNTIME-DATA or RUNTIME-DATA-ONLY. Its function
  ;; is to control clipping.  This slot corresponds the previously defined
  ;; variable that was named including-transients-p .  Its name has been been
  ;; generalized in recognition of the fact that it controls saving of runtime
  ;; data in slots of frames, as well as transient items.
  
  save-runtime-data?

  
  ;; `save-permanent-data?' is true when the type-of-kb-save slot of this
  ;; structure is KB-SAVE or KB-SAVE-WITH-RUNTIME-DATA.  When true, all
  ;; permanent frames are to be saved; transient frames will also be saved
  ;; provided that the save-runtime-data? slot is also true, i.e., in the
  ;; KB-SAVE-WITH-RUNTIME-DATA case.
  
  save-permanent-data?

  
  ;; At the time of creation of this structure, i.e., at the start of a save or
  ;; backup, the unix time is noted in the slot `time-of-kb-save-or-backup'.
  ;; This holds the universal time as a managed float.  This slot uses
  ;; reclaim-managed-float as a reclaimer.

  (time-of-kb-save-or-backup
    (get-unix-time-to-the-second-as-managed-float)
    :reclaimer reclaim-managed-float)
  

  ;; `rest-of-deleted-items' and `last-of-deleted-items' are part of the state
  ;; of the backup process. They are used to iterate over
  ;; items-deleted-since-load-or-save in the state it was in at the beginning of
  ;; the backup, that is, without new additions at the tail end.  These are
  ;; pointers to the same list structure as items-deleted-since-load-or-save and
  ;; items-deleted-since-load-or-save-tail, so they need no reclaimer.  These
  ;; are irrelevant -- and not used -- unless the save is a backup.
  (rest-of-deleted-items nil)
  (last-of-deleted-items nil)

  (saving-context-kb-file-progress-displays
    nil :reclaimer reclaim-gensym-list-function)

  ;;; `Need-to-call-terminate-kb-save?' becomes true when the save needs to be
  ;;; terminted.  It is initialized to NEVER-OPENED in a new saving context, and
  ;;; becomes NIL after the saving is under way.
  (need-to-call-terminate-kb-save? 'never-opened)

  (saving-compiled-kbs-p nil))




;;; The variable `current-saving-context' is bound only within the
;;; with-saving-context macro.  Its binding is the current saving-context
;;; structure.

(defvar current-saving-context)

;; Previously defined as a system variable in SETS.  Removed in favor
;; current-saving-context?.  This is now a defvar, unbound at top-level, and is
;; bound by with-saving-context.



;;; The variable `current-kb-save' is bound only within the with-saving-context
;;; macro. Its binding is the current kb-save structure.

(defvar current-kb-save)


(defmacro with-saving-context ((saving-context) &body body)
  `(let* ((current-saving-context ,saving-context)
	  (enable-saving-compiled-kbs-p (saving-compiled-kbs-p current-saving-context))
	  (current-computation-flags current-computation-flags)
	  (write-xml-object-items-collected nil)
	  (total-items-in-file nil))
     (setf (serve-only-permanent-items-p) nil)
     (setf (serve-loose-ends-p) nil)
     (loop for current-kb-save		; special
	       in (list-of-kb-saves-in-progress current-saving-context)
	   do ,@body)))





;;;; Global and dynamic variables



;;; `current-saving-context?' is true when a kb-save or backup has been started
;;; and is not yet complete. It holds its value during suspensions.  Its value,
;;; if true, is the context for the save or backup.

(def-system-variable current-saving-context? kb-save3 nil)

;; Previously a system variable named current-save-or-backup-context?, in KB-SAVE3.


;; The system varialbe `continuation-task-for-current-backup' is used to hold
;; saving scheduling tasks.

(def-system-variable continuation-task-for-current-backup kb-save3 nil)





;;;; Saving a KB



;;; This section contains the primitives for saving. The top level function,
;;; save-kb is in KB-SAVE3.

;;; Number-of-characters-beyond-which-to-start-a-new-saved-kb-line ...

;;; Number-of-characters-at-which-to-break-a-character-sequence ...

(defparameter number-of-characters-beyond-which-to-start-a-new-saved-kb-line 60)
(defparameter number-of-characters-beyond-which-to-start-a-new-saved-compiled-line 100)
(defparameter number-of-characters-beyond-which-to-start-a-new-saved-compiled-file 400000)

(defparameter number-of-characters-at-which-to-break-a-character-sequence 75)



;;; `Start-new-kb-line-if-appropriate' ...

(defmacro start-new-kb-line-if-appropriate ()
  `(if (>f (length-of-saved-kb-line-so-far current-kb-save)
	   number-of-characters-beyond-which-to-start-a-new-saved-kb-line)
       (start-new-kb-line)))



;;; `Write-char-for-kb' ...

;; jh, 6/2/92.  Modified write-char-for-kb to buffer its output.  As well as
;; improving efficiency, this allows us to check the error flag during the
;; write, so we can respond more quickly to things like the disk being full.
;; Note that the buffer must be flushed for proper operation.  This is done by a
;; call call flush-kb-write-buffer just before the g2-stream to the KB file is
;; closed.

;; jh, 6/4/92.  Added a cached error string, so we can catch write errors during
;; the save.  Caching is necessary because some platforms (e.g., Aviion) only
;; report a disk full error the first time a write to a full disk is attempted.
;; So we have to save the fact that an error occurred until we reach a
;; consistent stopping place in the save, say the final protected form in
;; continue-current-kb-save-or-backup, and then respond to that error.

;; jh, 6/2/92.  Jim tells me that 2048 is the size of TCP packets, which might
;; give us some synergy in performance.
;; moved above: (defconstant write-kb-buffer-length 2048)

;(def-system-variable write-kb-buffer KB-SAVE1 
;  (:funcall initialize-write-kb-buffer))
;; moved to slots. (MHD 1/26/94)

;(defun initialize-write-kb-buffer ()
;  (make-string write-kb-buffer-length))

(defun-void flush-kb-write-buffer ()
  (cond
    ((kb-transfer-stream? current-kb-save)
     (when (or (null (flush-deferred-pending-kb-write-buffers-to-stream))
	       (null (flush-kb-write-buffer-to-stream)))
       (when (null (string-from-write-error-during-save? current-kb-save))
	 (setf (string-from-write-error-during-save? current-kb-save)
	       (most-recent-file-operation-status-as-text)))))
    (t
     ;; Note that nconc is fine -- these lists are very short, usually 0 or 1
     ;; long; a list longer than a 100 would be practically inconceivable. (MHD)
     (setf (deferred-kb-save-write-buffers current-kb-save)
	   (nconc (deferred-kb-save-write-buffers current-kb-save)
		  (slot-value-list (make-current-kb-write-buffer-copy))))
     (setf (next-unoccupied-write-kb-buffer-index current-kb-save) 0))))

(defun-void flush-compiled-kb-write-buffer ()
  (cond
    #+development
    (emit-lisp-p nil)
    ((kb-transfer-compiled-stream? current-kb-save)
     (when (or (null (flush-deferred-pending-compiled-kb-write-buffers-to-stream))
	       (null (flush-compiled-kb-write-buffer-to-stream)))
       (when (null (string-from-write-error-during-save? current-kb-save))
	 (setf (string-from-write-error-during-save? current-kb-save)
	       (most-recent-file-operation-status-as-text)))))
    ((<f 0 (next-unoccupied-write-compiled-kb-buffer-index current-kb-save))
     (setf (deferred-compiled-kb-save-write-buffers current-kb-save)
	   (nconc (deferred-compiled-kb-save-write-buffers current-kb-save)
		  (slot-value-list (make-current-compiled-kb-write-buffer-copy))))
     (setf (next-unoccupied-write-compiled-kb-buffer-index current-kb-save) 0))))

(defun-void reclaim-deferred-kb-save-write-buffers (buffer-list)
  (loop while buffer-list
	for buffer = (slot-value-pop buffer-list)
	do (reclaim-simple-gensym-string buffer)))

;;; `Flush-kb-write-buffer-to-stream' and
;;; `flush-deferred-pending-kb-write-buffers' flush buffers to the stream in
;;; (kb-transfer-stream? current-kb-save), which is here known not to be nil.
;;;
;;; The former flushes the active contents of the buffer in the kb-write-buffer
;;; slot of current-kb-save. The latter flushes entirely the buffers in the
;;; deferred-kb-save-write-buffers slot of current-kb-save.  If successul, they
;;; both leave the structure in an "empty" state.  In the former case, with no
;;; characters outstanding.  In the latter case, with no buffers left to write.
;;; In the latter case, additionally, all strings and conses are reclaimed.
;;;
;;; They return true if successful; and nil otherwise.  If nil is returned, the
;;; state of buffering and file output is not well defined: it cannot be
;;; guaranteed that the entire contents are safe on disk.  Nor is it generally
;;; true that the entire active contents of the buffers remains intact in the
;;; current kb-save structure.

(defun-simple flush-kb-write-buffer-to-stream ()
  (let ((status
	  (g2-stream-write-from-buffer 
	    (write-kb-buffer current-kb-save)
	    (next-unoccupied-write-kb-buffer-index current-kb-save)
	    (kb-transfer-stream? current-kb-save))))
    (setf (next-unoccupied-write-kb-buffer-index current-kb-save) 0)
    (and status t)))

(defun-simple flush-compiled-kb-write-buffer-to-stream ()
  (let ((status
	  (g2-stream-write-from-buffer 
	    (write-compiled-kb-buffer current-kb-save)
	    (next-unoccupied-write-compiled-kb-buffer-index current-kb-save)
	    (kb-transfer-compiled-stream? current-kb-save))))
    (setf (next-unoccupied-write-compiled-kb-buffer-index current-kb-save) 0)
    (and status t)))


(defun-simple flush-deferred-pending-kb-write-buffers-to-stream ()
  (loop while (deferred-kb-save-write-buffers current-kb-save)
	for buffer
	  = (slot-value-pop (deferred-kb-save-write-buffers current-kb-save))
	as status = (g2-stream-write-from-buffer
		       buffer
		       (glength buffer t)
		       (kb-transfer-stream? current-kb-save))
	do (reclaim-simple-gensym-string buffer)
	when (null status)
	  return nil
	finally (return t)))

(defun-simple flush-deferred-pending-compiled-kb-write-buffers-to-stream ()
  (loop while (deferred-compiled-kb-save-write-buffers current-kb-save)
	for buffer
	  = (slot-value-pop (deferred-compiled-kb-save-write-buffers current-kb-save))
	as status = (g2-stream-write-from-buffer
		       buffer
		       (glength buffer t)
		       (kb-transfer-compiled-stream? current-kb-save))
	do (reclaim-simple-gensym-string buffer)
	when (null status)
	  return nil
	finally (return t)))
  

;;; `Make-current-kb-write-buffer-copy' copies the active contents of the
;;; current kb write buffer (the write-kb-buffer slot of current-kb-save) as a
;;; new text string.  The length of the string corresponds exactly to the length
;;; of the active content region of the current kb write buffer, not to that
;;; buffer's actual length.

(defun-simple make-current-kb-write-buffer-copy ()
  (let* ((buffer
	   (write-kb-buffer current-kb-save))
	 (length
	   (next-unoccupied-write-kb-buffer-index current-kb-save))
	 (new-simple-gensym-string
	   (obtain-simple-gensym-string length)))
    (copy-portion-of-string-into-simple-gensym-string
      buffer 0 length new-simple-gensym-string 0)
    new-simple-gensym-string))

(defun-simple make-current-compiled-kb-write-buffer-copy ()
  (let* ((buffer
	   (write-compiled-kb-buffer current-kb-save))
	 (length
	   (next-unoccupied-write-compiled-kb-buffer-index current-kb-save))
	 (new-simple-gensym-string
	   (obtain-simple-gensym-string length)))
    (copy-portion-of-string-into-simple-gensym-string
      buffer 0 length new-simple-gensym-string 0)
    new-simple-gensym-string))
    

;;; `Write-char-for-kb-minimal' takes a Common Lisp character and puts it into
;;; the write-kb-buffer (a simple gensym string) of the current kb save.  This
;;; is low level.

(def-substitution-macro write-char-for-kb-minimal-internal (character)
  (incff (length-of-saved-kb-line-so-far current-kb-save))
  (setf (schar (write-kb-buffer current-kb-save)
	       (next-unoccupied-write-kb-buffer-index current-kb-save))
	character)
  (when (>=f (incff (next-unoccupied-write-kb-buffer-index ; > not really nec.
		      current-kb-save))
	     write-kb-buffer-length)
    (flush-kb-write-buffer)))

(def-substitution-macro write-char-for-kb-minimal (character)
  (when (and (char= #\newline character) ; note: #\newline is #\linefeed
	     (kb-transfer-stream-uses-crlf? current-kb-save))
    (write-char-for-kb #\return))
  (write-char-for-kb-minimal-internal character))

(defun-simple write-char-for-kb (character)
  (setf (last-thing-written-was-an-index? current-kb-save) nil)	; often unnecessary
  (write-char-for-kb-minimal character))


;;; `Start-new-kb-line' ...

(defun start-new-kb-line ()
  (incff (number-of-kb-lines-so-far current-kb-save))
  (update-file-progress-for-writing)
  (write-char-for-kb-minimal #\newline)
  (setf (length-of-saved-kb-line-so-far current-kb-save) 0)
  (setf (last-thing-written-was-an-index? current-kb-save) nil))

(defun update-file-progress-for-writing (&optional force-update-p)
  (when (and (kb-transfer-kb-file-progress-display? current-kb-save)
	     (or force-update-p
		 (=f (modf-positive
		       (number-of-kb-lines-so-far current-kb-save)
		       50)	; parameterize this?
		     0)))
    (update-file-progress-display
      (kb-transfer-kb-file-progress-display? current-kb-save)
      (number-of-kb-lines-so-far current-kb-save)
      force-update-p)))


;; This used to use the variable within-write-as-it-is-now? to suppress
;; updating.  That would be bound when interrupting saving called by the
;; scheduler from a random slot change, deletion, etc.  I don't see the need for
;; it.  There was a statement that "updates to the screen must not occur" at
;; this time, but no reason given as to why.  Add this back if we think of a
;; reason.  One reason to leave this in: if the user makes a change that results
;; in a lot of saving, and the system "stops" for a while, it's at least giving
;; some feedback.  (MHD 1/23/94) -- UPDATE -- it's to prevent recursive
;; on-window calls.  (MHD 2/2/94)

;; By present good fortune, update-file-progress-display succeeds because it
;; apparently does not use class slots in frames that might have such slots
;; temporarily clobbered.

;; Consider keeping track of the total number of characters written.




;;; `compiled-kb' write functions

(defun-simple write-char-for-compiled-kb (character)
  (incff (length-of-saved-compiled-kb-file-so-far current-kb-save))
  (setf (schar (write-compiled-kb-buffer current-kb-save)
	       (next-unoccupied-write-compiled-kb-buffer-index current-kb-save))
	character)
  (when (>=f (incff (next-unoccupied-write-compiled-kb-buffer-index ; > not really nec.
		      current-kb-save))
	     write-kb-buffer-length)
    (flush-compiled-kb-write-buffer)))

(defun-simple write-gensym-string-for-compiled-kb (gensym-string)
  (loop for i from 0 below (length gensym-string) do
    (write-char-for-compiled-kb (char gensym-string i))))

(defun-simple write-gensym-string-comment-for-compiled-kb (gensym-string)
  (write-gensym-string-for-compiled-kb "/*")
  (loop for i from 0 below (length gensym-string)
	for prev = #\space then char
	for char = (char gensym-string i)
	do (when (or (and (eql prev #\/) (eql char #\*))
		     (and (eql prev #\*) (eql char #\/)))
	     (write-char-for-compiled-kb #\\))
	   (write-char-for-compiled-kb char))
  (write-gensym-string-for-compiled-kb "*/"))

(defun-void start-new-compiled-kb-line-function ()
  ;; if we want to count the number of lines emitted to the compiled-kb
  ;; file, here's the place to do it.
  (write-char-for-compiled-kb #\newline))

(defmacro start-new-compiled-kb-line ()
  ;; #+count-lines-for-compiled-kbs
  ;; `(start-new-compiled-kb-line-function)
  ;; #-count-lines-for-compiled-kbs
  `(write-char-for-compiled-kb #\newline))





;;; `Frame-has-kb-object-index-p' ...

;;; In a frame, a kb object index is kept in place of the class.

(defmacro frame-has-kb-object-index-p (frame)
  `(not (symbolp (class ,frame))))



;;; write-binary-word-for-kb writes 32 bits of binary data encoded
;;; as 5 ascii characters. The data is given as two 16 bit positive
;;; fixnums. What it writes is not self delimited. Therefore it should
;;; be called only by a writer which has specified by some convention
;;; exactly how many words are to be written. write-binary-word-for-kb
;;; writes exactly 5 characters, and read-binary-word-for-kb reads
;;; exactly 5 characters. 

(defun write-binary-word-for-kb (left-half right-half)
  (let* ((num (ashf left-half -3)))   
    (write-char-for-kb (radix-94-char (floorf-positive num 94)))
    (write-char-for-kb (radix-94-char (modf-positive num 94)))
    
    (setq num (+f (ash (logandf left-half 7) 16) right-half))
    (write-char-for-kb (radix-94-char (floorf-positive num #.(* 94 94))))
    (setq num (modf-positive num #.(* 94 94)))
    (write-char-for-kb (radix-94-char (floorf-positive num 94)))
    (write-char-for-kb (radix-94-char (modf-positive num 94)))))




;;; `Write-non-negative-fixnum-for-kb' ...
(defmacro write-non-negative-fixnum-for-kb (non-negative-fixnum)
  `(progn
     (if (last-thing-written-was-an-index? current-kb-save)
	 (write-char-for-kb-minimal '#\space)
	 (setf (last-thing-written-was-an-index? current-kb-save) t))
     (write-fixnum-digits-for-kb ,non-negative-fixnum)))

;;; `Write-integer-for-kb' can be used to write an integer, including bignums,
;;; as a KB element.

;;; `Write-fixnum-for-kb' is a bit faster, and can be used when an integer is
;;; known to be a fixnum.

(defun-void write-integer-for-kb (integer) 
  (cond
    ((32bit-fixnump integer)
     (let ((fixnum (coerce-number-to-fixnum integer)))
       (write-fixnum-for-kb-1 fixnum)))
    (t
     (start-new-kb-line-if-appropriate)		; sometimes redundant
     (if (last-thing-written-was-an-index? current-kb-save)
	 (write-char-for-kb-minimal '#\space))
     (with-temporary-bignum-creation
       (write-char-for-kb
	 (cond
	   ;; Chestnut's generic negative cannot handle most-negative-int64.
	   ((and (long-p integer)
		 (=l integer most-negative-int64))
	    (write-most-negative-int64-for-kb integer)
	    '#\-)
	   ((>= integer 0)
	    (write-bignum-digits-for-kb integer)
	    '#\+)
	   (t
	    (write-bignum-digits-for-kb (- integer))
	    '#\-)))))))


;; for 64-bit environments it's possible that the fixnum exceed 32-bit limits,
;; in this case directly calling `write-fixnum-for-kb-1' will result to
;; bad kb, we must prevent this, so the best choice is to always use
;; `write-integer-for-kb' instead, which is flexible.
;; -- Chun Tian (binghe), 11 maggio 2013

(defun-void write-fixnum-for-kb (fixnum)
  (write-integer-for-kb fixnum))

(defun write-long-for-kb (gensym-long)
  (write-char-for-kb '#\?) ; this is the new format; old is #\^
  (write-integer-for-kb gensym-long))

;; NOTE: this function can only work for 32-bit fixnum!
(defun-void write-fixnum-for-kb-1 (fixnum)
  (declare (type fixnum fixnum))
  (start-new-kb-line-if-appropriate)		; sometimes redundant
  (if (last-thing-written-was-an-index? current-kb-save)
      (write-char-for-kb-minimal '#\space))
  (write-char-for-kb
    (cond
      ((=f fixnum most-negative-fixnum)
       (write-fixnum-digits-for-kb 0)
       '#\-)
      ((<f fixnum 0)
       (write-fixnum-digits-for-kb (-f fixnum))
       '#\-)
      ((=f fixnum 0)
       '#\Z)
      (t
       (write-fixnum-digits-for-kb fixnum)
       '#\+))))

(defun write-frame-serial-number-for-kb (frame-serial-number)
  (let ((ht (kb-save-fsn-hash-table current-kb-save)))
    (write-fixnum-for-kb
      (or (get-kb-fsn-hash-table frame-serial-number ht)
	  (setf (get-kb-fsn-hash-table (copy-frame-serial-number frame-serial-number) ht)
		(incf (kb-save-fsn-index current-kb-save)))))))

;; NOTE: these now handle the writing of 0 (zero) as Z.  Previously, they did
;; not.  For 4.0.  This undoubtedly left some 0's written as 0+, since at
;; least write-g2-list-data-for-kb called write-integer-for-kb directly with
;; arbitrary integers, including 0's. (MHD 12/17/93)

;; Have callers converted to call write-fixnum-for-kb?! -- in most or all cases
;; they know they're dealing with fixnums.  



;;; `Write-significand-for-kb' ... is to be used in a permanent bignum creation
;;; context with do-not-update-file-progress-display? bound to true.

#+unused
(def-substitution-macro write-significand-for-kb (significand postfix-character)
  (start-new-kb-line-if-appropriate)		; sometimes redundant
  (if (last-thing-written-was-an-index? current-kb-save)
      (write-char-for-kb-minimal '#\space))
  (if (fixnump significand)
      (write-fixnum-digits-for-kb significand)
      (write-bignum-digits-for-kb significand))
  (write-char-for-kb postfix-character))




;;; The macro `kb-digit-char' returns the character corresponding to weight in
;;; radix 32.  When this is an alphabetic character, it is guaranteed lowercase,
;;; as is required for writing digits in KBs.  Weight must be an integer between
;;; 0 and 31 -- unlike Common Lisp's digit-char this never returns nil.

(defmacro kb-digit-char (weight)
  (avoiding-variable-capture (weight)
    `(ascii-code-char
       (+f ,weight
	   (if (<f ,weight 10)
	       #.(char-code #\0)
	       #.(- (char-code #\a) 10))))))


;;; `Write-fixnum-digits-for-kb' writes non-negative-fixnum in the current KB.  It
;;; is written as a base-32 number, with all-lowercase alphabetic digits.

;;; `Write-bignum-digits-for-kb' is the bignum version, which is a bit slower.
;;; It uses generic arithmetic.  It may create temporary bignums in the course
;;; of doing its work.  It is the callers responsibility to call it in a
;;; with-temporary-bignum-creation context.

;; Write-fixnum-digit-at-or-above-bit-number is a NON-STANDARD macro for use
;; only in write-fixnum-digits-for-kb-1.

(defmacro write-fixnum-digit-at-or-above-bit-number
    (fixnum always-write? bit-number)
  `(when (or ,always-write? (>=f ,fixnum ,(expt 2 bit-number)))
     (write-char-for-kb-minimal (kb-digit-char (ashf ,fixnum ,(- bit-number))))
     (setq ,fixnum (logandf ,fixnum ,(1- (expt 2 bit-number))))
     (setq ,always-write? t)))

(defun-void write-fixnum-digits-for-kb (non-negative-fixnum)
  (declare (type fixnum non-negative-fixnum))
  (let ((chars-written? nil))
    (write-fixnum-digit-at-or-above-bit-number
      non-negative-fixnum chars-written? 25)
    (write-fixnum-digit-at-or-above-bit-number
      non-negative-fixnum chars-written? 20)
    (write-fixnum-digit-at-or-above-bit-number
      non-negative-fixnum chars-written? 15)
    (write-fixnum-digit-at-or-above-bit-number
      non-negative-fixnum chars-written? 10)
    (write-fixnum-digit-at-or-above-bit-number
      non-negative-fixnum chars-written?  5)
    (write-char-for-kb-minimal (kb-digit-char non-negative-fixnum))))

(defun write-bignum-digits-for-kb (non-negative-bignum)
  (when (> non-negative-bignum 31)
    (let ((next (ash non-negative-bignum -5)))
      (write-bignum-digits-for-kb next)))
  (let* ((last (logand non-negative-bignum 31))
	 (lastf (coerce last 'fixnum)))
    (declare (type fixnum lastf))
    (write-char-for-kb-minimal (kb-digit-char lastf))))

(defparameter minus-most-negative-int64-ash-minus-5
  #+chestnut-trans (* #.(expt 2 8) (* #.(expt 2 25) #.(expt 2 25)))
  #-chestnut-trans (ash (- most-negative-int64) -5)) ; 2^58

(defun write-most-negative-int64-for-kb (bignum)
  (write-bignum-digits-for-kb minus-most-negative-int64-ash-minus-5)
  (let* ((last #.(logand (- most-negative-int64) 31)))
    (declare (type fixnum last))
    (write-char-for-kb-minimal (kb-digit-char last))))


;; Rewritten by ML, 6/8/91 -- unrewritten by MHD, 12/13/93
;; 
;; (def-substitution-macro write-radix-32-digit (digit)
;;   (write-char-for-kb-minimal
;;     (ascii-code-char
;;       (+f digit
;;           (if (<f digit 10) 48 87)))))
;; 
;; (defun write-fixnum-digits-for-kb (non-negative-fixnum)
;;   (let* ((register non-negative-fixnum)
;;          (digit-count 1)
;;          (d0 0)
;;          (d1 0)
;;          (d2 0)
;;          (d3 0) d4 d5 d6)
;;     (declare (type fixnum register digit-count d0))
;;     (setq d0 (logandf register 31))
;;     (setq register (ashf register -5))
;;     (when (/=f register 0)
;;       (setq d1 (logandf register 31))
;;       (setq register (ashf register -5))
;;       (incff digit-count)
;;       (when (/=f register 0)
;;         (setq d2 (logandf register 31))
;;         (setq register (ashf register -5))
;;         (incff digit-count)
;;         (when (/=f register 0)
;;           (setq d3 (logandf register 31))
;;           (setq register (ashf register -5))
;;           (incff digit-count)
;;           (when (/=f register 0)
;;             (setq d4 (logandf register 31))
;;             (setq register (ashf register -5))
;;             (incff digit-count)
;;             (when (/=f register 0)
;;               (setq d5 (logandf register 31))
;;               (setq register (ashf register -5))
;;               (incff digit-count)
;;               (when (/=f register 0)
;;                 (setq d6 (logandf register 31))
;;                 (incff digit-count)                             
;;                 (write-radix-32-digit d6))            
;;               (write-radix-32-digit d5))            
;;             (write-radix-32-digit d4))    
;;           (write-radix-32-digit d3))    
;;         (write-radix-32-digit d2))      
;;       (write-radix-32-digit d1))
;;     (write-radix-32-digit d0)
;;     (incff (length-of-saved-kb-line-so-far current-kb-save) digit-count)))



;;; `Write-character-sequence-for-kb' ...

(defun-void write-character-sequence-for-kb (prefix-character text-string encrypt?)
  (let* ((gensym-string (wide-string-to-gensym-string text-string))
	 (number-of-chars (gensym-string-length gensym-string)))
    (if (>f (+f (length-of-saved-kb-line-so-far current-kb-save)
		number-of-chars
		3)			; 3 for count-and-char??
	    number-of-characters-at-which-to-break-a-character-sequence)
	(start-new-kb-line))
    (write-non-negative-fixnum-for-kb number-of-chars)
    (write-char-for-kb prefix-character)
    (loop with local-base-reference fixnum
	    = (if ok-file-saving-mode?
		  (or (kb-transfer-base-reference? current-kb-save) 0)
		  standard-base-reference)
	  with string-is-simple? = (simple-gensym-string-p gensym-string)
	  as i fixnum from 0 below number-of-chars
	  as char = (gchar gensym-string i string-is-simple?)
	  when (>=f (length-of-saved-kb-line-so-far current-kb-save)
		    number-of-characters-at-which-to-break-a-character-sequence)
	    do (write-char-for-kb-minimal #\\)
	       (start-new-kb-line)
	       (write-char-for-kb-minimal #\\)
	  do (write-char-for-kb-minimal
	       (if encrypt?
		   (char-encrypt char local-base-reference)
		   char))
	  finally
	    (when (and encrypt? ok-file-saving-mode?)
	      (setf (kb-transfer-base-reference? current-kb-save)
		    local-base-reference))
            ;; If the last char is #\\, write another #\\.
	    (if (and (>f number-of-chars 0)
		     (char= char #\\))
		(write-char-for-kb #\\)))
    (reclaim-gensym-string gensym-string)))

;; The input arg is a text string; this is where it gets translated to a Gensym
;; string using the Gensym character encoding, or the UTF-G (Gensym Universal
;; Transformation Format), for 5.0. (MHD 2/15/96)

;; Fixed to do stable encryption today, for 4.0, and for the kb-flag
;; (stable-non-human-readable-kbs?).  It no longer refers to the global
;; base-reference (which has been in any case replaced by a slot in kb-save
;; structure), only to the constant standard-base-reference.  For saving
;; OK files, it still saves the old 3.0 way, to save 3.0-compatible
;; KBs.  But that's only for development.  (MHD 9/30/92 and 12/93)



;;; `Write-symbol-for-kb' ...

(defun-void write-symbol-for-kb (symbol indexed?)
  (start-new-kb-line-if-appropriate)
  (let ((kb-object-index?
	  (if indexed?
	      (get symbol
		   (kb-object-index-property-name current-kb-save)))))
    (cond
      (kb-object-index?
       (write-non-negative-fixnum-for-kb kb-object-index?))
      (t (when indexed?
	   (as-atomic-operation
	     (setf (symbol-plist symbol)
		   (gensym-cons
		     (kb-object-index-property-name current-kb-save)
		     (gensym-cons
		       (next-kb-object-index current-kb-save)
		       (symbol-plist symbol)))))
	   (incff (next-kb-object-index current-kb-save))
	   (setf (symbols-with-earlier-kb-object-indices current-kb-save)
		 (journal-cons
		   symbol
		   (symbols-with-earlier-kb-object-indices current-kb-save))))
	 (when (eq (type-of-syntactic-anomaly symbol) 'numeric)
	   (if indexed?
	       (setf (kb-transfer-numeric-symbols current-kb-save)
		     (slot-value-cons
		       symbol
		       (kb-transfer-numeric-symbols current-kb-save)))
	       (write-char-for-kb #\$)))
	 (let* ((name (symbol-name-text-string symbol))
		(package? (symbol-package symbol)))
	   (write-character-sequence-for-kb
	     (cond
	       ((or (eq package? *package*) (eq package? lisp-package-1))
		(if indexed? #\' #\`))
	       ((eq package? keyword-package-1)
		(if indexed? #\: #\,))
	       ((find-symbol name)
		(if indexed? #\' #\`))
	       ((null package?)
		(error "Uninterned symbol ~S encountered while trying to save KB" symbol))
	       (t (error
		    "Symbol ~S from a foreign package encountered while trying to save KB"
		    symbol)))
	     name
	     (kb-transfer-base-reference? current-kb-save)))))))

;; This assumes that as-atomic-operation is implemented.

;; Consider having the kb-object-index case handled in a macro expansion.

;; Not used. 7/30/91, ML




;;;; Noting changes


;;; The macro `collectable-block-p' is an inclusion test for blocks used to
;;; determine whether they should be included for file writing. Some files
;;; include only permanent blocks, while others include transient ones. (This is
;;; part of the kb save module which has to be defined early for reasons of
;;; compilation order.)
;;;
;;; This must only be called in a saving context.

(defun-substitution-macro collectable-block-p (block)
  (or (permanent-block-p block)
      (and (save-runtime-data? current-saving-context)
	   (transient-p block))))



(defun-substitution-macro collectable-connection-p (connection)
  (or (permanent-connection-p connection)
      (save-runtime-data? current-saving-context)))

;; I don't know why it was defined differently than collectable-block-p aside
;; from different names of the permanent/transient test macros.  I.e., why is
;; there's no "transient-connection-p"?
;; 
;; (MHD 1/11/94)








(defmacro get-referenced-recorder-slot-if-any (class)
  (avoiding-variable-capture (class)
    `(class-case ,class
       (format-frame
	 'modules-this-format-frame-has-been-referenced-in)
       (computation-style
	 'modules-this-computation-style-has-been-referenced-in))))

(defmacro get-written-recorder-slot-if-any (class)
  (avoiding-variable-capture (class)
    `(class-case ,class
       (format-frame
	 'modules-this-format-frame-has-been-written-in)
       (computation-style
	 'modules-this-computation-style-has-been-written-in))))


;;; The function `prepare-blocks-and-connections-for-saving' is called at the
;;; very beginning of a save-kb to initialize the written/reference flags of
;;; every block and connection, and to mark all blocks and connections as being
;;; in existence as of the start of the save.
;;;
;;; This now, in addition, flushes scheduled table updates, if any, so that all
;;; representations of slots in tables that may be saved are up-to-date.  Note
;;; that currently table updates are never scheduled while saving a KB. [New as
;;; of G2 5.1r5 and G2 6.0 (MHD 2/16/00)]

(defun prepare-blocks-and-connections-for-saving (saving-modules?)
  (finish-all-table-updates)
  (loop with referenced-recorder-slot-name? = nil
	with written-recorder-slot-name	; nil/non-nil in lockstep with above var
	for class being each subclass of 'block
	do
    (when saving-modules?
      (setq referenced-recorder-slot-name?
	    (get-referenced-recorder-slot-if-any class))
      (setq written-recorder-slot-name
	    (get-written-recorder-slot-if-any class)))
    (loop for block being each strict-class-instance of class
	  do
      (cond (referenced-recorder-slot-name?
	     (reclaim-slot-value
	       (prog1
		   (get-slot-value block referenced-recorder-slot-name?)
		 (set-slot-value
		   block referenced-recorder-slot-name? nil)))
	     (reclaim-slot-value
	       (prog1
		   (get-slot-value block written-recorder-slot-name)
		 (set-slot-value
		   block written-recorder-slot-name nil))))
	    (t
	     (setf (block-has-been-referenced-p block) nil)
	     (setf (block-has-been-written-p block) nil)))
      (set-block-existed-at-start-of-save block)
      (when (connections block)
	(loop for connection-structure being each output-connection of block
	      do
	  (clear-connection-has-been-written connection-structure)
	  (set-connection-existed-at-start-of-save connection-structure))))))

;; The above visits each subclass of block, figures out which slot will be used
;; to record the written/referenced flag -- a per-class choice, and then visits
;; each strict instance of that class.  (This wins over using the general
;; instances loop path, since that would entail a class test on every instance.)
;;
;; Note that the setf methods for the slots in the computation-style class are
;; not available here, due to the order module.  Calling them directly would
;; probably add a bit of speed, but we know that there are relatively few of
;; them.

;; This takes too long!! Doing this incrementally would require more work.  (ML)


(defun-simple block-referenced-in-current-save-p (block)
  (let ((referenced-recorder-slot-name?
	  (when (kb-module-being-saved? current-kb-save)
	    (get-referenced-recorder-slot-if-any (class block)))))
    (cond
      (referenced-recorder-slot-name?
       (memq-p-macro
	 (kb-module-being-saved? current-kb-save)
	 (get-slot-value block referenced-recorder-slot-name?)))
      (t
       (block-has-been-referenced-p block)))))

(defun-simple set-block-referenced-in-current-save (block value)
  (let ((referenced-recorder-slot-name?
	  (when (kb-module-being-saved? current-kb-save)
	    (get-referenced-recorder-slot-if-any (class block)))))
    (cond
      (referenced-recorder-slot-name?
       (set-slot-value
	 block referenced-recorder-slot-name?
	 (let ((old-slot-value
		 (get-slot-value block referenced-recorder-slot-name?)))
	   (if value
	       (if (memq-p-macro
		     (kb-module-being-saved? current-kb-save)
		     old-slot-value)
		   old-slot-value
		   (slot-value-cons
		     (kb-module-being-saved? current-kb-save)
		     old-slot-value))
	       (delete-slot-value-element
		 (kb-module-being-saved? current-kb-save)
		 old-slot-value))))
       value)
      (t
       (setf (block-has-been-referenced-p block) value)))))

(defsetf block-referenced-in-current-save-p
    set-block-referenced-in-current-save)

(defun-simple block-written-in-current-save-p (block)
  (let ((written-recorder-slot-name?
	  (when (kb-module-being-saved? current-kb-save)
	    (get-written-recorder-slot-if-any (class block)))))
    (cond
      (written-recorder-slot-name?
       (if (memq-p-macro
	     (kb-module-being-saved? current-kb-save)
	     (get-slot-value block written-recorder-slot-name?))
	   t))				; return t/nil
      (t
       (block-has-been-written-p block)))))

(defun-simple set-block-written-in-current-save (block value)
  (let ((written-recorder-slot-name?
	  (when (kb-module-being-saved? current-kb-save)
	    (get-written-recorder-slot-if-any (class block)))))
    (cond
      (written-recorder-slot-name?
       (set-slot-value
	 block written-recorder-slot-name?
	 (let ((old-slot-value
		 (get-slot-value block written-recorder-slot-name?)))
	   (if value
	       (if (memq-p-macro
		     (kb-module-being-saved? current-kb-save)
		     old-slot-value)
		   old-slot-value
		   (slot-value-cons
		     (kb-module-being-saved? current-kb-save)
		     old-slot-value))
	       (delete-slot-value-element
		 (kb-module-being-saved? current-kb-save)
		 old-slot-value))))
       value)
      (t
       (setf (block-has-been-written-p block) value)))))

(defsetf block-written-in-current-save-p
    set-block-written-in-current-save)

;;; the parameter can be enabled by a command-line flag
(defparameter debug-frame-reference-balance? nil)

(defun-substitution-macro incf-frame-reference-balance
    (frame calling-function amount)
  (incff (frame-reference-balance current-kb-save) amount)
  (when debug-frame-reference-balance?
    ;; GENSYMCID-1214: Error while saving KB
    (let ((tree (frame-reference-balance-tree current-kb-save)))
      (cond ((>f amount 0) ; 1
	     (setf (get-frame-reference-balance frame tree) calling-function))
	    (t ; -1
	     (delete-frame-reference-balance frame tree))))
    #+development
    (format t "~%~a balance~a~a~a~a to ~d from ~a for ~a"
	    (if (>f amount 0) "Incrementing" "Decrementing")
	    current-kb-save
	    (if (kb-module-being-saved? current-kb-save)
		" in "
		"")
	    (if (kb-module-being-saved? current-kb-save)
		" for module "
		"")
	    (or (kb-module-being-saved? current-kb-save)
		"")
	    (frame-reference-balance current-kb-save)
	    calling-function
	    frame)))

(defun-void increment-frame-reference-balance (frame calling-function)
  (incf-frame-reference-balance frame calling-function 1))

(defun-void decrement-frame-reference-balance (frame calling-function)
  (incf-frame-reference-balance frame calling-function -1))





;;;; Transient Blocks as Values of Slots



;;; `Transient-block-in-slot-p' can be called with any attribute value, and
;;; returns true if it is a transient block.  Note that at present, if a
;;; frame that is the value of a slot in a permanent frame is transient,
;;; it must be of class OBJECT.  (Frames such as embedded rules cannot be
;;; transient, unless their parents are transient.  Workspaces, connections,
;;; definitions, and other non-object items may not be transient as the
;;; value of a slot of a permanent frame.)

(def-substitution-macro transient-block-in-slot-p (value-of-slot)
  (and (framep value-of-slot)
       (block-p value-of-slot)
       (transient-p value-of-slot)))





;;;; Connection Clipping

;; moved here from CONNECT1. (MHD 1/1/94)



;;; Clip-transients-from-connections returns a list of gensym-conses which
;;; contains only the permanent connections and associated port names.  It
;;; should only be called within a saving context in which (save-runtime-data?
;;; current-saving-context) is nil and connections is non-nil.  Its value must
;;; be reclaimed by the caller.

(defun-simple clip-transients-from-connections (connections)
  (loop with connection-or-symbol = nil
	with symbols-and-connection = nil
	with clipped-list = nil
	with clipped-list-tail = nil
	while connections
	do (setq connection-or-symbol (first connections))
	   (cond
	     ((symbolp connection-or-symbol)
	      (setq symbols-and-connection
		    (nconc symbols-and-connection 
			   (gensym-list connection-or-symbol))))
	     (t ; connection structure
	      (cond
		((permanent-connection-p connection-or-symbol)
		 (let* ((new-tail (gensym-list connection-or-symbol))
			(list-to-add 
			  (nconc symbols-and-connection new-tail)))
		   (if (null clipped-list)
		       (setq clipped-list list-to-add
			     clipped-list-tail new-tail)
		       (setf (cdr clipped-list-tail) list-to-add
			     clipped-list-tail new-tail)))
		 (setq symbols-and-connection nil))
		(t
		 (reclaim-gensym-list symbols-and-connection)
		 (setq symbols-and-connection nil)))))
	   (setq connections (cdr connections))
	finally (return clipped-list)))

;;;; Index Spaces Needed for Reading a KB



;;; In the new format of saving a KB, the initial plist contains the property
;;; current-frame-serial-number, which is guaranteed to be greater than the frame
;;; serial number of any frame that follows. In the old format, this does
;;; not  exist. This allows one to distinguish between the formats
;;; In the old 

;; The function checkpoint-file-if-necessary renames the file designated by
;; convertible-thing (typically to by post-pending a tilde) so that a new version
;; may be stored.  It is used, among other things, to checkpoint an old KB on file
;; systems that don't support multiple versions.  Checkpoint-file-if-necessary
;; quietly gives up if unsuccessful.

(defun-allowing-unwind checkpoint-file-if-necessary (convertible-thing)
  (protected-let ((truename?
		    (gensym-probe-file convertible-thing)
		    (reclaim-gensym-pathname truename?)))
    (when (and truename?
	       (memq (gensym-pathname-file-system truename?) '(unix win32)))
      (protected-let* ((namestring
			 (gensym-namestring convertible-thing)
			 (reclaim-text-string namestring))
		       (new-name-for-existing-file
			 (tformat-text-string "~a~~" namestring)
			 (reclaim-text-string new-name-for-existing-file)))
	(gensym-rename-file-indifferent-to-return-values
	  namestring
	  new-name-for-existing-file)
	t))))

;; jh, 1/28/92.  Changed call to gensym-rename-file in checkpoint-file-if-necessary
;; to gensym-rename-file-indifferent-to-return-values, since gensym-rename-file now
;; returns pathnames as values which must be reclaimed.  That is not needed here.



;;; `Make-or-clear-complete-kb-name' forms a name from the kb from its first
;;; argument if non-null. If complete-as-is? then complete-kb-name-or-kb-name?,
;;; which must be a string is copied, otherwise the machine-id and the date and
;;; time to the second are added to form a name that is almost certainly
;;; world-wide unique. complete-kb-name-or-kb-name? is always copied rather than
;;; having its structure used.

;;; The result of the above, or nil if file-name? is nil is placed in the system
;;; variable complete-kb-name?. The old value, if any, is reclaimed.  In
;;; addition, the relevant slots of the currently installed saving-parameters
;;; system table are changed, i.e., identifier-of-basis-kb and
;;; filename-of-basis-kb.  These are not slots that get saved in a KB.

;;; All incremental backups are made with respect to a saved kb, or to a new
;;; empty kb. After doing a merge, or having a failed load, G2 is not in a state
;;; to do incremental backups. It can be put in this state by save, load or
;;; clear-kb.

(defun make-or-clear-complete-kb-name
    (complete-kb-name-or-kb-name? complete-as-is? &optional module?
				  kb-file-comment?)  
  (if complete-kb-name? (reclaim-text-string complete-kb-name?))
  (setq complete-kb-name? 
	(if complete-kb-name-or-kb-name?
	    (if complete-as-is?
		(copy-text-string complete-kb-name-or-kb-name?)
		(make-complete-kb-name complete-kb-name-or-kb-name?))
	    nil))
  (let ((saving-parameters-instance?
	  (if module?
	      (get-system-table-of-class-for-module-or-nil
		module? 'saving-parameters)
	      saving-parameters))
	(do-not-note-permanent-changes-p t))
    (when saving-parameters-instance?
      (change-slot-value
	saving-parameters 'identifier-of-basis-kb
	(if complete-kb-name?
	    (copy-text-string complete-kb-name?)))
      (change-slot-value
	saving-parameters 'filename-of-basis-kb
	(if current-kb-pathname?
	    (when complete-kb-name?
	      (gensym-namestring current-kb-pathname?))))

      ;; new feature for 5.0: -- may ultimately be used for source code control
      ;; comments, but version recording with $ would be a problem still. (MHD
      ;; 11/17/96)
      (when kb-file-comment?
	(change-slot-value
	  saving-parameters 'kb-file-comment
	  (slot-value-cons
	    no-value
	    (convert-text-string-to-text
	      kb-file-comment?))))))
  complete-kb-name?)



;;; Make-complete-kb-name actually produces a identifier for a basis KB.  This
;;; is a subfunction of make-or-clear-complete-kb-name.

(defun make-complete-kb-name (kb-name)
  (twith-output-to-text-string
    ;; make sure legal text string (the machine id, that is)!!
    (let ((local-machine-id (get-local-machine-id)))
      (tformat "~a ~a " kb-name local-machine-id)
      ;; Reclaim form added by ghw (2/15/96)
      (reclaim-text-string local-machine-id))
    (multiple-value-bind (second minute hour date month year)
	(get-decoded-real-time)
      (print-decoded-time second minute hour date month year))))


  

;; jh, 3/20/91.  Changed make-or-clear-complete-kb-name so that it copies the
;; symbol name and file name instead of using the given text-strings.  This was
;; causing a crash on the Sparc when G2 tried to reclaim a symbol-name string.


;;; reclaimed-index-count is a misleading name for information as to what kind
;;; of authorized G2 product the save was performed from. This became necessary
;;; when it was decided that runtime data from a a runtime only license could
;;; not be recovered into a more expensive license. The code is as follows:
;;;    1   embedded
;;;    2   runtime
;;;    3   restricted use
;;;    0   other
;;;    The code is the value of (modf (-f reclaimed-index-count
;;;    final-frame-serial-number) 11).






;;; reclaim-rest-of-index-count (misleading name) when given a final-plist
;;; during a read, is true if the KB being read was saved from an embedded or
;;; runtime system, but the present software is something other than one of
;;; these. This is to enforce a licensing policy that prevents the migration of
;;; runtime data from such a system to a more expensive lisense by ...??

#+pre-g2-v5-licensing
(defun reclaim-rest-of-index-count (final-plist)
  (let* ((reclaimed-index-count
	   (getf final-plist 'reclaimed-index-count))
	 (residue
	   (if reclaimed-index-count
	       (modf (+f reclaimed-index-count
			 (frame-serial-number-hash
			   (getf final-plist 'final-frame-serial-number)))
		     11)
	       0)))
    (cond
      ((or (embedded-option-authorized-p)
	   (runtime-option-authorized-p))
       nil)
      (t (or (=f residue 1) (=f residue 2))))))





;;;; Copying Collectable Blocks



;;; Copy-collectable-blocks collects (using gensym conses) blocks in list
;;; that are collectable-block-p.

(defun copy-collectable-blocks (list)
  (loop for block in list
	when (collectable-block-p block)
	  collect block using gensym-cons))

(defun copy-collectable-blocks-for-subblocks (list)
  #-subblocks-v2
  (loop for block in list
	when (collectable-block-p block)
	  collect block using gensym-cons)
  #+subblocks-v2
  (when list
    (loop for block being each constant-queue-element of list
	  when (collectable-block-p block)
	  collect block using gensym-cons)))

;;; Copy-collectable-blocks-within-module ... is just like
;;; copy-collectible-blocks except that it filters out blocks that are not
;;; within module.

(defun copy-collectable-blocks-within-module (list module)
  (loop for block in list
	when (and (collectable-block-p block)
		  (within-module-p block module))
	  collect block using gensym-cons))

;;; `Convert-intermodual-relation-instances-for-saving' replaces the frame
;;; references in intermodual relation-instances with the uuids or names of the
;;; frames.  This function is called from write-frame-for-kb.

(defun-simple convert-intermodual-relation-instances-for-saving
    (block relation-instances)
  (let ((converted-value? nil))
    (loop with block-module? = (kb-module-being-saved? current-kb-save)
	  with block-denotation? = (block-denotation-p block)
	  for relation-instance being each relation-instance of relation-instances
	  for relation-frame = (relation-instance-relation relation-instance)
	  for object-class-references-for-saving? =
	        (when (and (not (transient-p relation-frame))
				(relation-is-permanent relation-frame))
		  (loop for object-frame being each related-item of
					       (relation-instance-items relation-instance)
			for object-frame-module? = (when object-frame
						     (get-module-block-is-in object-frame))
			when object-frame
			nconc
			(unless (or (transient-p object-frame)
				    ;; Guard against saving posted messages
				    ;; and automatically created default-junctions.
				    (and (not (transient-p object-frame))
					 (not (permanent-block-p object-frame))))
			  (if (or (eq block-module? object-frame-module?)
				  ;; Block-module? will be null when the kb is
				  ;; being saved into a single file.
				  (null block-module?))
			      (slot-value-list object-frame)
			      (let ((object-frame-denotation?
				      (block-denotation-p object-frame)))
				(when (and block-denotation? object-frame-denotation?)
				  (slot-value-list object-frame-denotation?)))))))
	  do
      (setq converted-value?
	    (nconc converted-value?
		   (when object-class-references-for-saving?
		     (slot-value-list
		       (nconc
			 (slot-value-list
			   (relation-instance-name relation-instance)
			   (if (eq block-module?
				   (get-module-block-is-in relation-frame))
			       relation-frame
			       ;; To have associated relation-instances, a
			       ;; relation frame will at least have a name.
			       (block-denotation-p relation-frame)))
			 object-class-references-for-saving?)))))
	  finally (reclaim-slot-value block-denotation?))
    converted-value?))








;;;; Writing Frames



;;; `Write-frame-for-kb' is called within a saving-context to write a block or
;;; dependent-frame.

;;; block? must be nil if frame is a dependent frame, and t if it is a block.

;;; As-ghost?, if true when block?  is true, makes frame be written out as an
;;; "ghost", i.e., an block that reads back in with nil for its subworkspaces,
;;; slot-group-for-block?, frame-represetntations, and icon-attributes-plist
;;; slots.  This is at present only used for writing "ghost" definitions; see
;;; the function write-ghost-definitions, for further details.  The constraints
;;; on using the as-ghost?  option when writing a KB are: (1) no subblocks of
;;; frame may be written or referred to elsewhere in the KB; (2) no frame
;;; representations may be written or referred to elsewhere in the KB; (3) no
;;; subworkspace of frame may be written or referred to elsewhere in the KB;
;;; (4) and no connections of frame may be written or referred to elsewhere in
;;; the KB.  Note that definition objects may be relied on not to have
;;; connections in or out. [Since 0.91, at least, I think.]

;;; The permanent slots of a frame are saved if the frame is transient, or if
;;; the save is not runtime-data-only. This needs further elaboration for the
;;; backup and runtime-data-only cases. Furthermore, slots that have reversibe
;;; changes are not dealt with here!!!

;; The runtime-data slots are saved if kb-save-with-runtime-data, or
;; runtime-data-only.

;; Used to supply debugging information when writing a compiled byte-code-body
(defvar frame-for-write-frame-for-kb nil)
(defvar slot-name-for-write-frame-for-kb nil)
(defvar slot-value-for-write-frame-for-kb nil)

(defun write-frame-for-kb (frame block? &optional as-ghost?)
  (let* ((frame-for-write-frame-for-kb frame)
	 (class (class frame))
	 (class-description (class-description-slot frame))
	 (include-initializations-for-all-slots? ; Note A
	   (class-description-of-class-p class-description 'format-frame))
	 (last-thing-written-was-long? nil)
	 (frame-is-a-class-definition? (frame-of-class-p frame 'class-definition))
	 (slot-descriptions (slot-descriptions class-description)))
    (funcall-method 'prepare-to-saving-frame frame)
    (start-new-kb-line)		; note B

    ;; #\Y for dependent frames in new format
    (write-char-for-kb (if block? '#\F '#\Y))
    
    ;; No frame serial number in old format or for dependent frames
    (when block?
      (when (block-referenced-in-current-save-p frame)
	(decrement-frame-reference-balance frame 'write-frame-for-kb))
      (write-frame-serial-number-for-kb (frame-serial-number frame)))
    
    (write-symbol-for-kb class t)
    
    ;; When runtime-data-only the permanent slots of permanent blocks are not
    ;; written. This is inadequeute because some such slots may have changed.
    ;; Need a more refined marking system!!!
    
    (when (or (not block?)
	      (neq (type-of-kb-save current-saving-context?) 'runtime-data-only)
	      ;; or marked as changed???!!
	      (transient-p frame))

      ;; The following form, together with a do-not-save feature on
      ;; frame-flags causes frame-flags to be written out in advance of the
      ;; lookup-slots. (I tried interchanging the order of vector and lookup
      ;; slots by interchanging the second and third forms following this
      ;; coment. This caused a problem with the "tampering" mechanism that I
      ;; did not diagnose, so I reverted the change.) The reason for writing
      ;; the frame-flags first has to do with attribute frames that are not
      ;; written because (not (has-slot-values-to-save-p attribute)). Such an
      ;; attribute was losing its permanent-block flag. If the parent frame
      ;; is already installed, and already has its permanent flag, then a      
      ;; problem occurs only when the attribute is not written. The attribute
      ;; is added as an inferior block when a reference to it is encountered
      ;; as the value of a user defined slot of the parent. If the parent is
      ;; permanent by this time, the right things happen.

      ;; Another reason for writing frame-flags first is that the permanent
      ;; flag, if absent, causes a definition not to be installed.
      
      (when block?
	(let* ((slot-description
		 (get-slot-description-of-class-description 
		   'frame-flags class-description))
	       (frame-flags (frame-flags frame)))
	  ; should be replace slot-init-form?
	  (when (neq frame-flags (slot-init-form slot-description))
	    (write-slot-for-kb
	      frame slot-description frame-flags as-ghost?
	      last-thing-written-was-long?))))
      ;; MHD's questions for ML:  (MHD 9/30/93)
      ;; ML: what does that comment mean, "; should be replace slot-init-form?"?
      ;; ML: what about include-initializations-for-all-slots? -- why doesn't
      ;; this check that, and write out frame-flags unconditionally if it's
      ;; true?!  Same question with the original-kb-state-plist slot
      ;; written out after the following loop.
      ;; ML: What is going on with the original-kb-state-plist slot? below?!
      
      ;; Note that some slots are special cased, and that if a slot changes
      ;; from being vector to lookup or vv, that this code must be changed.
      ;; Today (11/5/91), I fixed a bug by moving the special casing of
      ;; subworkspaces from the vector slot code (second form below) to the
      ;; lookup-slot code (first form below). ML.
      ;; -- I assumed that subworkspaces is a lookup slot, and that
      ;; slot-group-for-block? and frame-representations is a vector
      ;; slot, when I implemented the as-ghost? argument. But these
      ;; assumptions had already present in adjacent code anyway.
      ;; (MHD 1/3/92)
      ;; -- I further assumed that icon-attributes-plist is a vector-slot
      ;; (on class entity) for doing the as-ghost? arg. (MHD 1/8/92)
      
      ;; the code below needs to be changed for project vectorized user slots.
      ;; (jra/ghw 01/04/92)  The code has been changed so that there is one loop
      ;; instead of two, and the code is slot-representation independent.  
      ;; (2/22/93 ghw)
      (loop for slot-description in slot-descriptions
	    for slot-name = (pretty-slot-name slot-description)
	    for slot-name-for-write-frame-for-kb = slot-name
	    for possibly-transient-slot-value
		= (cond ((and as-ghost?
			      (or (eq slot-name 'subworkspaces)
				  (eq slot-name 'frame-representations)
				  (eq slot-name 'icon-attributes-plist)))
			 nil)
			;; GENSYMCID-1462: Fatal Error in Snapshot read (Part II)
			;; Do not save frame-status-and-notes
			;;   slot of instance of class module-information. there
			;;   are external frame references in this slot and that
			;;   frame will be saved later. On the other hand, this
			;;   slot will be updated once KB loaded -- Fei Liu, Jun 2015.
			((and (eq class 'module-information)
			      (eq slot-name 'frame-status-and-notes))
			 nil)
			((eq slot-name 'uuid)
			 (item-uuid frame))
			(t
			 (get-slot-description-value frame slot-description)))
	    ;; If slot-value is a transient item, and we're not saving
	    ;; runtime data, then the slot value should be saved as nil,
	    ;; since nil is what it would become upon a KB reset.
	    ;; (MHD/GHW 2/27/97)
	    for slot-value = 			
	    (if (and (transient-block-in-slot-p possibly-transient-slot-value)
		     (not (save-runtime-data? current-saving-context)))
		nil
		possibly-transient-slot-value)
	    for entangled-slot-on-definition?
	        = (and frame-is-a-class-definition?
		       slot-value
		       (or (eq slot-name 'relation-instances)
			   (eq slot-name 'subworkspaces)
			   (and (slot-description-is-of-savable-slot-p
				  slot-description)
				(or (framep slot-value)
				    (evaluation-sequence-p slot-value)
				    (evaluation-structure-p slot-value)))))
	    do
	;; The entangled-slots slot of definitions will be used and reclaimed
	;; by the function write-entangled-slots-of-definition-as-frame-modification.
	(when entangled-slot-on-definition?
	  (slot-value-push
	    (unique-slot-name slot-description) (entangled-slots frame)))

	(when (and (or (not (eq slot-value (slot-init-form slot-description)))
		       include-initializations-for-all-slots?)
		   (or (slot-description-is-of-savable-slot-p slot-description)
					; Consider making
					; original-kb-state-plist a saveable
					; slot, so we don't need a special test
					; here. - cpm, 2/13/95
		       (eq slot-name 'original-kb-state-plist))
		   (or (not ok-file-saving-mode?)
		       (not (memq slot-name
				  slots-to-skip-saving-in-ok-files)))
		   (or (not entangled-slot-on-definition?)
		       (and
			 (or (not (save-runtime-data? current-saving-context))
			     ;; Only permanent relation-instances will be saved here.
			     ;; When saving run-time data (doing a snapshot save)
			     ;; all relation-instances, whether permanent or transient,
			     ;; will be saved in the squirrelled-data slot of the block.
			     ;; Saving the permanent relation-instances here preserves
			     ;; them when loading a snapshot kb without the warmboot option.
			     ;; When loading a snapshot kb with the warmboot option,
			     ;; we substitute the relation-instances squirrelled data
			     ;; for the value of the relation-instances slot after we
			     ;; have reclaimed its value.  See unsquirrel-data-for-block.
			     (eq slot-name 'relation-instances))
			 
			 ;; Don't save relation-instances in the definitions
			 ;; section of the KB.  (In general, don't save entangled
			 ;; slots of definitions that are dangerous to save in
			 ;; this section).  They must be written afterwards.
			 ;; Abstract this predicate!
			 (or
			   (finished-writing-definitions? current-kb-save)
			   (not (frame-of-class-p frame 'definition))))))

	  (if (or (and (eq slot-name 'relation-instances) slot-value)
		  (eq slot-name 'list-structure)
		  (eq slot-name 'managed-g2-array))
	      (let ((slot-value-to-save?
		      (case slot-name
			(relation-instances
			 (convert-intermodual-relation-instances-for-saving
			   frame slot-value))
			(list-structure
			 (convert-permanent-list-structure-for-saving
			   frame))
			(managed-g2-array
			 (convert-permanent-array-structure-for-saving
			   frame)))))
		(when slot-value-to-save?
		  (setq last-thing-written-was-long?
			(write-slot-for-kb
			  frame slot-description slot-value-to-save? as-ghost?
			  last-thing-written-was-long?))
		  (reclaim-slot-value slot-value-to-save?)))
	      (setq last-thing-written-was-long?
		    (write-slot-for-kb
		      frame slot-description slot-value as-ghost?
		      last-thing-written-was-long?)))
	  (when (eq slot-name 'uuid)
	    (reclaim-text-string slot-value))
	  (when (eq slot-name 'original-kb-state-plist)
	    (setf (original-kb-state-plist-written? current-kb-save) t)))))

      ;; When either kb-save-with-runtime-data or runtime-data-only, the runtime
      ;; aspect of frames must be written.
      (when (and block? (save-runtime-data? current-saving-context))
	(write-runtime-data-for-kb frame class))

      (write-char-for-kb '#\!)
      (funcall-method 'on-frame-saved frame)))

;; Note A.  We no longer, as of 11/19/93, decide that if the frame is a system
;; table, all slots should be written out.  (MHD 11/19/93)

;; Note B.  Using the "-if-appropriate" variant of start-new-kb-line would result
;; in "less stable" KBs.

;; Write-frame-for-kb can decide not to write a frame, for example,
;; transient objects in workspaces are skipped.  If the
;; start-new-kb-line-if-appropriate check is done before we know
;; if we are actually going to write something, then you may leave a #\!
;; at the beginning of a line.  The load-kb code prior to this date can not
;; handle that. As of this date the save avoids doing that, and the
;; load can handle that.  - bah 9/21/90

;; Note that when this is called by write-element-for-kb, it could be given the
;; class description.  In all cases, it could be given the class.

;; This code depends on the details of frame and class structures.

;; The absurdly unlikely case where a (:funcall form) or the like could yield
;; precisely itself -- the very same cons -- is mercifully ignored.

;; Note that this code has been changed to check the transient-p frame flag,
;; since transient frames should not be saved in KBs.  Lowell, please check that
;; this, and the other documentation added for transient objects, is OK.  -jra
;; 9/4/89




;;; A `pseudo-frame' is a structure holding only a frame-serial-number. It is
;;; used in pane-descriptions and possibly elsewhere to represent a frame that
;;; might be deleted before the structure can be written. The writer for it is
;;; #\H frame-serial-number, which is identical to that for a reference to a
;;; frame already written.

(def-structure (pseudo-frame (:constructor make-pseudo-frame
					   (pseudo-frame-item pseudo-frame-frame-serial-number)))
  pseudo-frame-item
  (pseudo-frame-frame-serial-number nil :reclaimer reclaim-frame-serial-number))





;;;; Slot Saving


;; slot-description-is-of-savable-slot-p macro moved to FRAMES2


;; Consider changing the term "savable" to something less misleading.


;;; `Has-slot-values-to-save-p' is true if (1) it has a superblock?; (2)
;;; include-transients-p is true; or (3) has non-default-valued slot, i.e.,
;;; there is a slot in frame that (a) has a non-default value and (b) has either
;;; a type feature and no do-not-save feature or a save feature and no type
;;; feature and (c) is not one named in names-of-slots-to-disregard.  Note that
;;; criterion (b) excludes time stamp, author, and block edge slots.
;;;
;;; This may only be called in a saving context (i.e., with current-saving-context
;;; bound).

;;; When this returns non-nil, it for case (1) the superblock, for case (2), t,
;;; and for case (3) the name of the first encountered non-default-valued slot.

;;; When (save-runtime-data? current-saving-context), all blocks are regarded as
;;; having savable slots, since they might have runtime data.

;; Superblock? was added (1/29/91) by ML because otherwise subblocks of a
;; kb-workspace were treated as default frames when in fact they had coordinate
;; information. This function is used to save a KB as if connection frames
;; without savable information had reverted to symbols. This is done in
;; traverse-kb-for-saving and write-connection-for-kb.

;; test for frame flags needing saving added: (ML/MHD/AGH 7/26/89)

(defun has-slot-values-to-save-p (frame &optional names-of-slots-to-disregard)
  (let* ((class-description (class-description-slot frame))
	 (slot-descriptions (slot-descriptions class-description)))
    (or
      (if (save-runtime-data? current-saving-context) t)
      (superblock? frame)
      (loop for slot-description in slot-descriptions
	    for slot-init-form = (slot-init-form slot-description)
	    for slot-value
	      = (get-slot-description-value-macro frame slot-description)
	    thereis
	      (if (and (not (eq slot-value slot-init-form))
		       (or (slot-description-is-of-savable-slot-p slot-description)
			   (and (eq (unique-slot-name slot-description) 'frame-flags)
				;; frame flags need saving? 
				(/=f (logandc2f			    
				       (frame-flags frame)
				       #.(logior class-of-frame-is-user-defined-flag
						 permanent-block-flag))
				     (logandc2f
				       slot-init-form
				       #.class-of-frame-is-user-defined-flag))))
		       (not (memq
			      (unique-slot-name slot-description)
			      names-of-slots-to-disregard)))
		  (unique-slot-name slot-description))))))

;; The return values are only used for informational purposes at present. (MHD
;; 11/18/93)



;; The class-of-frame-is-user-defined-flag should be set in the default value for
;; the frame-flags slot, when appropriate!

;; Note that before the test was added for frame flags (in 2.0), connection
;; frames were always saved and never filtered out by this when they ought
;; to have been.  (MHD/AGH 7/26/89)

;; Consider abstracting some of this for use in write-frame-for-kb.

;; This code depends on the details of frame and class structures.

;; The absurdly unlikely case where a (:funcall form) or the like could yield precisely
;; itself -- the very same cons -- is mercifully ignored.




;;; `Write-slot-for-kb' writes the value slot-value for the slot corresponding
;;; to slot-name-or-description in frame.  as-ghost?  is documented in
;;; write-frame-for-kb, of which this is a subfunction.  A few slots are handled
;;; specially:
;;;
;;;   stack-of-subblocks frame-representations subworkspaces
;;;     ...
;;; 
;;;   slot-group-for-block?
;;;     ...
;;; 
;;;   column-of-args column-of-values
;;;     ...
;;;
;;; Before the slot is written, this writes a newline if
;;;
;;; NEW for 4.0 KBs: if slot-name needs qualification, this writes out the cons
;;;
;;;     (slot-name . class-qualifier?)
;;;
;;; Otherwise, this writes, as before, just slot-name.

;; [both writing-or-reading-system-tables-p is nil AND ] [not doing this now. -mhd]

;;; either good-to-force-newline?  is true or slot value is "long", which is
;;; true or if slot-value is a cons, or if slot-value is a string that's greater
;;; than 60 in length.  This returns long-thing-was-written?, true if slot-value
;;; was "long".  The expectation is that the caller will pass in
;;; long-thing-was-written? on the subsequent call to write-slot-for-kb when
;;; writing a series of slots within a frame.  The newlines are not part of the
;;; format of the KB, but are just put in so that the lines of text in a KB tend
;;; to be stable between saves.  This was added as a feature for G2 4.0.

(defun write-slot-for-kb
    (frame slot-description slot-value
	   &optional as-ghost? good-to-force-newline?)
  (let ((force-newline?
	 (and ; (not writing-or-reading-system-tables-p)
	      ; consider adding the above, to compact the
	      ; system frames a bit
	      (or good-to-force-newline?
		  (or (not (atom slot-value))
		      (and (text-string-p slot-value)
			   (>f (text-string-length slot-value)
			       60)))))))
    (when force-newline?
      (start-new-kb-line))
    (let* ((slot-name (pretty-slot-name slot-description))
	   (slot-denotation
	     (denote-slot-using-slot-value-conses
	       slot-description
	       (class-description-slot frame))))
      (write-element-for-kb slot-denotation)
      (reclaim-slot-value slot-denotation)
      (case slot-name
	;; The following slots all consist of lists of blocks. They
	;; are clipped by copy-collectable-blocks. The resultant
	;; list may be empty. If so, it must be written as #\N.
	((stack-of-subblocks frame-representations subworkspaces)
	 (let ((collectable-blocks
		(if (and (kb-module-being-saved? current-kb-save)
			 (eq slot-name 'frame-representations))
		    (copy-collectable-blocks-within-module
		      slot-value (kb-module-being-saved? current-kb-save))
		    (copy-collectable-blocks slot-value))))
	   (write-element-for-kb collectable-blocks)
	   (reclaim-gensym-list collectable-blocks)))
	(slot-group-for-block?
	 (write-slot-group-for-block? frame slot-value as-ghost?))
	((column-of-args column-of-values)	; KLUDGE for series-of-values!
	 (write-char-for-kb '#\L)		; handle in write-element-for-kb
	 (loop with series-of-values	;   for greater efficiency?
	       = slot-value
	       as i from 0
		    below (get-slot-value frame 'number-of-rows-in-table)
	       do (write-element-for-kb
		    (get-value-from-series-of-values series-of-values i)))
	 (write-char-for-kb '#\R))
	(t (write-element-for-kb slot-value))))
    force-newline?))




;;; `Write-aggregate-evaluation-value-for-kb' is the writer for evaluation
;;; structs and sequences.  These are both valid slot values and can be
;;; included just about anywhere.  Therefore the read/write-element-for-kb
;;; now knows about these "aggregate evaluation values" and stores them
;;; under the prefix code #\%.

;;; Elements that reference frames are handled specially.  An intramodual frame
;;; reference is handled by write-element-for-kb which writes the frame serial
;;; number.  A cross-module reference to a frame that has a block denotation (a
;;; uuid or a name, in that order) is also written by write-element-for-kb, but
;;; first this function writes out the block denotation prefix code (#\~).  A
;;; cross-module reference to a frame that has no block denotation is written
;;; out as nil.

(defun-void write-aggregate-evaluation-value-for-kb (evaluation-value)
  (let* ((managed-array (evaluation-value-value evaluation-value))
	 (managed-array-length (managed-array-length managed-array))
	 (current-module? (kb-module-being-saved? current-kb-save))
	 (aggregate-type (cdr evaluation-value)))
      (write-element-for-kb aggregate-type)
      (write-element-for-kb
	(aggregate-evaluation-value-reference-count evaluation-value))
      (write-element-for-kb managed-array-length)
      (loop for index from (case aggregate-type
			     (sequence (evaluation-sequence-first-element-index))
			     (structure (estructure-first-attribute-index)))
		      below managed-array-length
	    for element = (managed-svref managed-array index)
	    for dereferenced-element = (if (evaluation-item-reference-p element)
					   (evaluation-item-reference-referenced-item element)
					   element)
	    do
	(cond
	  ((null dereferenced-element)
	   (write-element-for-kb nil))
	  ((framep dereferenced-element)
	   (cond ((or (not (transient-p dereferenced-element))
		      (save-runtime-data? current-saving-context))
		  (if (or (null current-module?)
			  (eq (get-module-block-is-in dereferenced-element) current-module?)
			  ;; Block-module? will be null when the kb is
			  ;; being saved into a single file.
			  )
		      (write-element-for-kb dereferenced-element)
		      (let ((denotation? (block-denotation-p dereferenced-element)))
			(cond (denotation?
			       (write-char-for-kb '#\~)
			       (write-element-for-kb denotation?)
			       (reclaim-slot-value denotation?))
			      (t
			       (write-element-for-kb nil))))))
		 (t
		  (write-element-for-kb nil))))
	  (t
	   (write-element-for-kb element))))))


;; Note that writing a newline after this doesn't work -- that's probably
;; a bug.








;;;; Writing Elements of a KB


;;; `Write-element-for-kb' ... Note that there is an asymmetry in the way gensym
;;; floats are written and read in that you can write a gensym float, but when
;;; it is read back in it will returned by read-element-for-kb as managed float.
;;;
;;; As of 4.0 (Alpha Rev. 23, in fact), managed float arrays are KB elements,
;;; writeable by write-element-for-kb, and readable by read-element-for-kb.
;;; Note that managed float arrays are slot values.

(defun-void write-element-for-kb (x)
  (start-new-kb-line-if-appropriate)
  (cond
    ((consp x)
     (cond
       ((no-value-p x)			; changed to no-value-p (MHD/ML 6/9/89)
	(write-char-for-kb '#\X))
       ((evaluation-item-reference-p x)
	(write-element-for-kb (evaluation-item-reference-referenced-item x)))
       ((aggregate-evaluation-value-p x)
	(write-char-for-kb '#\%)
	(write-aggregate-evaluation-value-for-kb x))
       #+comment		 ; truth values cannot now be uniquely identified!
       ((cons-is-evaluation-truth-value-p x)
	(write-truth-value-for-kb x))
       ((eq (car x) 'frame-denotation)
	(write-char-for-kb '#\~)
	(write-element-for-kb (second x)))
       ;; handle connections! (plus other lists)
       (t (write-char-for-kb '#\L)
	  (loop for y = x then (cdr y)
		until (or (atom y)
			  (no-value-p y))
		do (write-element-for-kb (car y))
		finally
		  (cond
		    ((not (null y))
		     (write-char-for-kb '#\.)
		     (write-element-for-kb y))
		    (t (write-char-for-kb '#\R)))))))
    ((symbolp x)
     (cond
       ((null x)
	(write-char-for-kb '#\N))
       ((eq x 't)
	(write-char-for-kb '#\T))
       ((no-simulation-value-p x)	; simulation-no-value (#) elements
	(write-char-for-kb '#\#))	;   are new for 4.0 (MHD 6/24/94)
       (t (write-symbol-for-kb x t))))
    ((integerp x)
     (write-integer-for-kb x))
    ((text-string-p x)
     (write-character-sequence-for-kb
       '#\S x
       (kb-transfer-base-reference? current-kb-save)))
    ((managed-float-p x)
     (with-temporary-gensym-float-creation write-managed-float
       (let ((gensym-float (managed-float-value x)))
	 (write-double-float-for-kb gensym-float))))
    ((managed-long-p x)
     (with-temporary-creation write-managed-long
       (let ((gensym-long (managed-long-value x)))
	 (declare (type (signed-byte 64) gensym-long))
	 (write-long-for-kb gensym-long))))
    ((slot-value-float-p x)
     (with-temporary-gensym-float-creation writing-slot-value-float
       (write-double-float-for-kb
	 (slot-value-float-value x))))
    ((gensym-float-p x)				; rare
     (with-temporary-gensym-float-creation writing-slot-value-float
       (write-double-float-for-kb x)))
    ((gensym-long-p x)
     (with-temporary-creation writing-managed-long
       (write-long-for-kb x)))
    ((simple-vector-p x)
     (cond
       ((framep x)
	(cond
	  ((frame-of-class-p x 'dependent-frame)
	   (write-frame-for-kb x nil))
	  ((and (not (block-written-in-current-save-p x))
		(or (frame-of-class-p x 'format-frame)
		    (frame-of-class-p x 'computation-style)
		    (frame-of-class-p x 'g2gl-variable-compilation)
		    ;; Kb-workspaces can have subframe attributes in 5.0.
		    ;; They will be missed by other save traversals.
		    ;; (ghw 8/29/96)
		    (and (parent-frame x)
			 (frame-of-class-p
			   (parent-frame x) 'kb-workspace))))
	   (setf (block-written-in-current-save-p x) t)
	   (write-frame-for-kb x t))
	  (t
	   (write-reference-to-frame x))))
       ((connection-p x)
	(write-char-for-kb '#\I)
	(write-frame-serial-number-for-kb
	  (frame-serial-number-for-connection x)))
       ((managed-float-array-p x)
	(write-managed-float-array-for-kb x))
       ((managed-array-p x)
	(write-managed-array-for-kb x))
       ((byte-code-body-p x)
	(write-byte-code-body-for-kb x))
       ((pseudo-frame-p x)
	(write-char-for-kb '#\H)
	(write-frame-serial-number-for-kb
	  (pseudo-frame-frame-serial-number x)))
       ((media-stream-p-function x)
	(write-element-for-kb nil))
       ((user-mode-alias-p x)
	(write-user-mode-alias-for-kb x))
       (t
	;; GENSYMCID-1621: Problem with Snapshot Saves
	;;
	;; For unknown objects inside a simple vector, do not abort G2 any more,
	;; now we output messages on G2 logbook and write NIL instead.
	;; 					-- Chun Tian (binghe), Feb 2015
	#+development
	(error "Illegal vector (starting with ~A) encountered while trying to save KB"
	       (svref x 0))
	#-development
	(notify-user-at-console
	  "Illegal vector (starting with ~A) encountered while trying to save KB"
	  (svref x 0))
	(write-char-for-kb '#\N)))) ; write NIL instead
    (t
     (error "Illegal object ~A encountered while trying to save KB" x))))

;; Note: it would be a good idea, I think, to make managed-float-array be a KB
;; element type.  There is currenting an asymmetry, for example, in local
;; histories for graphs and variable histories in which we write out raw gensym
;; floats, which are the elements of a managed-float-array, and then read them
;; back in as managed floats, unbox them, and then reclaim the boxes.  We could
;; eliminate this asymmetry, and improve efficiency, by adding this element type.
;; Also, this would make KB elements more like slot values, which we are happy
;; to see.  (MHD/JED 1/5/94)

;; This code depends on the details of frame, class, and connection structures.

;; This will fail if it encounters a simple vector of length zero.  It also assumes that
;; any simple vector whose zeroeth element is either an integer or a symbol with a
;; class description is a frame.

;; Consider not recording earlier kb object indices on symbols that are expected to
;; occur only once, though an earlier kb object index must be assigned in any case for
;; each symbol written.

;; Note that this does not handle cyclical list structures.

;; Note that lines-in-text (text-lines) are (indistinguishable from) strings, but in the
;; context of a text they need only be distinguishable from numbers and lists.




;;; write-connection-for-kb is called to write connections in the new format only.
;;; It is not called to reference them. That still happens in write-element-for-kb.

(defun write-connection-for-kb (connection)
  (write-char-for-kb '#\C)
  (write-frame-serial-number-for-kb (frame-serial-number-for-connection connection))
  
  (when (or (neq (type-of-kb-save current-saving-context?) 'runtime-data-only)
	    (transient-connection-p connection))
    
    (let ((connection-frame-or-class (connection-frame-or-class connection)))
      (cond
	((symbolp connection-frame-or-class)
	 (write-symbol-for-kb connection-frame-or-class t))
	((has-slot-values-to-save-p connection-frame-or-class)
	 (write-reference-to-frame connection-frame-or-class))
	(t (write-symbol-for-kb
	     (class connection-frame-or-class) t))))
    
    (write-element-for-kb (input-end-object connection))
    (write-element-for-kb (output-end-object connection))
    (write-element-for-kb (input-end-position connection))
    (write-element-for-kb (output-end-position connection))
    (write-element-for-kb (delta-or-deltas connection))
    (write-element-for-kb
      (logandf (connection-flags connection)
	       savable-connection-flags))
    (write-connection-attributes-plist-for-kb
      (connection-attributes-plist connection)))
  )



(defun write-connection-attributes-plist-for-kb (connection-attributes-plist)
  (let ((attributes-to-save 
	  (get-savable-connection-attributes-plist connection-attributes-plist)))
    (write-element-for-kb attributes-to-save)
    (reclaim-slot-value-list attributes-to-save)))



;;; The function `write-managed-float-array-for-kb' writes managed-float-array
;;; contents to the current KB.  The format is
;;;
;;;    length #\O {element}
;;;
;;; where each element is written as by write-element-for-kb, which in turn
;;; calls write-double-float-for-kb to write the value of a managed float, and
;;; where exactly length elements are written.
;;;
;;; Between elements, the same interelement rules for whitespace as for
;;; top-level elements are used, in order to keep lines of the KB reasonable in
;;; length, so care needs to be taken in reading these back in.
;;;
;;; This enters and exits temporary gensym float creation contexts in order to
;;; write a maximum number of 500 gensym floats, in order not to risk
;;; overflowing temporary area space allocated for such purposes.
;;;
;;; See also the function finish-reading-managed-float-array, which does most of
;;; the job of reading the managed float arrays that this function writes.

(defun write-managed-float-array-for-kb (managed-float-array)
  (let ((length (managed-float-array-length managed-float-array)))
    (declare (type fixnum length))
    (write-non-negative-fixnum-for-kb length)
    (write-char-for-kb #\O)
    (finish-writing-out-managed-float-array-for-kb
      managed-float-array 0 length)))


;;; `Finish-writing-out-managed-float-array-for-kb' writes out
;;; 
;;;    (- end-index start-index)
;;;
;;; elements from managed-float-array, starting with the element indexed by
;;; start-index.  Note that end-index should be one past the last element to be
;;; written, and that, if end-index is less or equal to start-index, no elements
;;; will be written.
;;;
;;; Each element is written is a double-float KB element.

(defun finish-writing-out-managed-float-array-for-kb
    (managed-float-array start-index end-index)
  (declare (type fixnum start-index end-index))
  (when (<f start-index end-index)
    (loop with i fixnum = start-index
	  until (=f i end-index)
	  do
      (with-temporary-gensym-float-creation
	  write-managed-float-array-for-kb
	(loop repeat (minf 500 (-f end-index i))
	      do
	  (start-new-kb-line-if-appropriate)
	  (write-double-float-for-kb
	    (cached-managed-float-aref managed-float-array i))
	  (incff i))))))


(defun write-managed-array-for-kb (managed-array)
  (let ((length (managed-array-length managed-array)))
    (write-non-negative-fixnum-for-kb length)
    (write-char-for-kb '#\W)
    (finish-writing-out-managed-array-for-kb managed-array 0 length)))

;;; `Finish-writing-out-managed-array-for-kb' is just like
;;; finish-writing-out-managed-float-array-for-kb, but writes out general KB
;;; elements, not double floats.

(defun finish-writing-out-managed-array-for-kb
    (managed-array start-index end-index)
  (declare (type fixnum start-index end-index))
  (loop for i fixnum from start-index below end-index
	do (write-element-for-kb (managed-svref managed-array i))))

(defun write-fixnum-for-compiled-kb (fixnum)
  (when (<f fixnum 0)
    (write-char-for-compiled-kb #\-)
    (setq fixnum (-f fixnum)))
  (if (>f fixnum 9)
      (let ((quotient (floorf-positive fixnum 10))
	    (remainder (modf-positive fixnum 10)))
	(declare (type fixnum quotient remainder))
	(write-fixnum-for-compiled-kb quotient)
	(write-char-for-compiled-kb (decimal-digit-char remainder)))
      (write-char-for-compiled-kb (decimal-digit-char fixnum))))

(defvar compiled-kb-indent 0)

(defun write-newline-for-compiled-kb ()
  (start-new-compiled-kb-line)
  (loop for i from 1 to compiled-kb-indent
	do (write-char-for-compiled-kb #\space)))

(defun-void write-variable-for-compiled-kb (variable)
  (cond ((eq variable t)
	 #+development
	 (cerror "Go and give it a shot anyway"
		 "The constant T is not allowed in emitted code.")
	 (write-char-for-compiled-kb #\T))
	(t
	 (loop with string = (symbol-name variable)
	       for i from 0 below (length string)
	       for char = (schar string i)
	       for dchar = (if (eql char #\-)
			       #\_
			       (char-downcase char))	
	       do
	   (if (char= dchar #\?)
	       (progn
		 (write-char-for-compiled-kb #\_)
		 (write-char-for-compiled-kb #\q)
		 (write-char-for-compiled-kb #\m))
	       (write-char-for-compiled-kb dchar))))))

(defun write-variable-list-for-compiled-kb (variable-list separator-string)
  (loop for first = t then nil
	for variable in variable-list
	do (unless first
	     (write-gensym-string-for-compiled-kb separator-string))
	   (write-variable-for-compiled-kb variable)))

(defun write-tag-for-compiled-kb (tag)
  (typecase tag
    (symbol (write-variable-for-compiled-kb tag))
    (fixnum (write-fixnum-for-compiled-kb tag))))

(defun write-case-tag-for-compiled-kb (tag)
  (cond
    ((eq tag t)
     (write-gensym-string-for-compiled-kb "default:"))
    (t
     (write-gensym-string-for-compiled-kb "case ")
     (write-tag-for-compiled-kb tag)
     (write-char-for-compiled-kb #\:))))

;;; c-type is one of :object, :boolean, :int or :double
;;; Note that both :int and :double are the C type int, but :int
;;; is used if the variable stores a fixnum (0 represents the
;;; fixnum 0), while :boolean is used if the variable stores
;;; a boolean (0 represents the symbol T)

;;; desired-type is a hack so that nil can get output as either 0 or Nil,
;;; as appropriate, rather than always emitting one of them and then casting
;;; to the other.

(defun c-type-of-expression (form desired-type)
  (typecase form
    (float :double)
    (integer :int)
    (null (if (eq desired-type :object) :object :int))
    (symbol (c-type-of-variable form))
    (cons
     (case (car form)
       (compiled-function-in-place :object)
       (setf (c-type-of-expression (second form) desired-type))
       ((or and) (if (eq desired-type :boolean)
		     :boolean
		     (c-type-of-expression (second form) desired-type)))
       ((progn let let*) (c-type-of-expression (car (last form)) desired-type))
       (ife (c-type-of-expression (third form) desired-type))
       (quote :object)
       (otherwise
	(let ((type (inlined-function-return-type
		      (inlined-function-data (car form)))))
	  #+development
	  (unless type
	    (cerror "Skip it and continue emitting"
		    "Don't know how to emit ~S" form))
	  type))))))

       
(defun write-expression-for-compiled-kb-as-type (form desired-type)
  (let ((actual-type (c-type-of-expression form desired-type)))
    (case desired-type
      (:object
       (case actual-type
	 (:object
	  (write-object-expression-for-compiled-kb form))
	 (:int
	  (write-gensym-string-for-compiled-kb "FIX(")
	  (write-int-expression-for-compiled-kb form)
	  (write-gensym-string-for-compiled-kb ")"))
	 (:boolean
	  (write-gensym-string-for-compiled-kb "(")
	  (write-boolean-expression-for-compiled-kb form)
	  (write-gensym-string-for-compiled-kb " ? T : Nil)"))
	 (:double
	  (write-gensym-string-for-compiled-kb "DOUBLE_TO_DOUBLE_FLOAT(")
	  (write-double-expression-for-compiled-kb form)
	  (write-gensym-string-for-compiled-kb ")"))))
      (:int
       (case actual-type
	 (:object
	  (write-gensym-string-for-compiled-kb "(IFIX(")
	  (write-object-expression-for-compiled-kb form)
	  (write-gensym-string-for-compiled-kb "))"))
	 (:int
	  (write-int-expression-for-compiled-kb form))
	 (:boolean
	  #+development
	  (cerror "write it anyway"
		  "A boolean is not an int")
	  (write-boolean-expression-for-compiled-kb form))
	 (:double
	  #+development
	  (cerror "write it anyway"
		  "A float is not an int")
	  (write-double-expression-for-compiled-kb form))))
      (:boolean
       (case actual-type
	 (:object
	  (write-gensym-string-for-compiled-kb "((")
	  (write-object-expression-for-compiled-kb form)
	  (write-gensym-string-for-compiled-kb ") != Nil)"))
	 (:boolean
	  (write-boolean-expression-for-compiled-kb form))
	 (:int
	  ;; an int is not nil
       	  (write-gensym-string-for-compiled-kb "T"))
	 (:double
	  ;; a double is not nil, either.
       	  (write-gensym-string-for-compiled-kb "T"))))
      (:double
       (case actual-type
	 (:object
	  (write-gensym-string-for-compiled-kb "DOUBLE_FLOAT_TO_DOUBLE(")
	  (write-object-expression-for-compiled-kb form)
	  (write-gensym-string-for-compiled-kb ")"))
	 (:int
	  #+development
	  (cerror "Write it anyway"
		  "Type mismatch in emitter: int is not a float")
	  (write-int-expression-for-compiled-kb form))
	 (:boolean
	  #+development
	  (cerror "write it anyway"
		  "A boolean is not a float")
	  (write-boolean-expression-for-compiled-kb form))
	 (:double
	  (write-double-expression-for-compiled-kb form)))))))

;;; when this is called, any required casting of result has already been
;;; performed. 
(defun write-function-call-for-compiled-kb (form c-type)
  (let ((fn (car form)))
    (cond ((eq fn 'setf)
	   (write-expression-for-compiled-kb-as-type (cadr form) c-type)
	   (write-gensym-string-for-compiled-kb " = ")
	   (write-expression-for-compiled-kb-as-type (caddr form) c-type))
	  ((memq fn '(or and))
	   (write-char-for-compiled-kb #\()
	   (write-expression-for-compiled-kb-as-type (cadr form) c-type)
	   (write-gensym-string-for-compiled-kb (case fn
						  (or  " || ")
						  (and " && ")))
	   ;; (write-newline-for-compiled-kb)
	   (write-expression-for-compiled-kb-as-type (caddr form) c-type)
	   (write-char-for-compiled-kb #\)))
	  ((eq fn 'progn)
	   (write-char-for-compiled-kb #\()
	   (loop for firstp = t then nil
		 for form-tail on (cdr form)
		 for form = (car form-tail)
		 for lastp = (null (cdr form-tail))
		 do (unless firstp
		      (write-gensym-string-for-compiled-kb ", "))
		    (write-expression-for-compiled-kb-as-type form (if lastp c-type :object)))
	   (write-char-for-compiled-kb #\)))
	  ((eq fn 'ife)
	   (write-char-for-compiled-kb #\()
	   (write-boolean-expression-for-compiled-kb (cadr form))
	   (write-gensym-string-for-compiled-kb " ? ")
	   (write-expression-for-compiled-kb-as-type (caddr form) c-type)
	   (write-gensym-string-for-compiled-kb " : ")
	   (write-expression-for-compiled-kb-as-type (cadddr form) c-type)
	   (write-char-for-compiled-kb #\)))
	  ((eq fn 'quote)
	   #+development
	   (cerror "Go and give it a shot anyway"
		   "Quote is not allowed in emitted code.")
	   (write-gensym-string-for-compiled-kb "STATIC_SYMBOL(\"")
	   (write-object-expression-for-compiled-kb (cadr form))
	   (write-gensym-string-for-compiled-kb "\")"))
	  ((memq fn '(let let*))
	   #+development
	   (cerror "Go and give it a shot anyway"
		   "Let is not allowed at this level emitted code.")
	   (write-newline-for-compiled-kb)
	   (write-gensym-string-for-compiled-kb "/* bad let */")
	   (write-newline-for-compiled-kb)
	   (write-char-for-compiled-kb #\{)
	   (let ((compiled-kb-indent (+f compiled-kb-indent 2)))
	     (write-newline-for-compiled-kb)
	     (loop for (name value) in (cadr form) do
	       (write-object-expression-for-compiled-kb name)
	       (write-gensym-string-for-compiled-kb " = ")
	       (write-object-expression-for-compiled-kb value)
	       (write-char-for-compiled-kb #\;)
	       (write-newline-for-compiled-kb))
	     (loop for expression in (cddr form) do
	       (write-object-expression-for-compiled-kb expression)
	       (write-char-for-compiled-kb #\;)
	       (write-newline-for-compiled-kb)))
	   (write-char-for-compiled-kb #\})
	   (write-newline-for-compiled-kb))
	  (t
	   (let* ((inlined-function-data
		    (inlined-function-data-given-arg-count fn (1-f (length form))))
		  (numbered? (inlined-function-numbered inlined-function-data))
		  (name (inlined-function-c-name inlined-function-data)))
	     #+development
	     (unless inlined-function-data
	       (cerror "continue anyway" "unknown function ~S encountered by emitter"
		       fn))
	     (write-gensym-string-for-compiled-kb name)
	     (when numbered?
	       (write-fixnum-for-compiled-kb (- (length (cdr form)) numbered?)))
	     (write-char-for-compiled-kb #\()
	     (when (memq fn '(get-constant get-variable call-simple-function call-function))
	       (write-fixnum-for-compiled-kb (cadr form))
	       (pop form)
	       (when (cdr form)
		 (write-gensym-string-for-compiled-kb ", ")))
	     (write-expression-list-for-compiled-kb
	       (cdr form) ", "
	       (inlined-function-argument-type inlined-function-data))
	     (write-char-for-compiled-kb #\)))))))

(defun c-type-of-variable (variable-name)
  (cond
    ;; No need to unbox integers, since integer ops are designed to
    ;; work with boxed ints.
    ((memq variable-name '(fixnum-register-1 fixnum-register-2))
     :object)
    ((memq variable-name '(float-register-1 float-register-2)) :double)
    (t :object)))

;;; The five following functions can assume that the expression is of
;;; the appropriate type. Any required casting will already have been performed
;;; by write-expression-for-compiled-kb-as-type

(defun write-object-expression-for-compiled-kb (form)
  (typecase form
    (null   (write-gensym-string-for-compiled-kb "Nil"))
    (symbol (write-variable-for-compiled-kb form))
    (cons
     (cond ((eq (car form) 'compiled-function-in-place)
	    (write-expression-for-compiled-kb-as-type (cadr form) :object))
	   (t (write-function-call-for-compiled-kb form :object))))))

(defun write-boolean-expression-for-compiled-kb (form)
  (typecase form
    ;; explicit fixnums in the code are always implicitly type
    ;; int, not type boolean, so we don't have a fixnum case here.
    (null   (write-gensym-string-for-compiled-kb "0"))
    (symbol
     (write-variable-for-compiled-kb form))
    (cons
     (write-function-call-for-compiled-kb form :boolean))))

(defun write-int-expression-for-compiled-kb (form)
  (typecase form
    (fixnum (write-fixnum-for-compiled-kb form))
    (symbol
     (write-variable-for-compiled-kb form))
    (cons
     (write-function-call-for-compiled-kb form :int))))

(defun write-double-expression-for-compiled-kb (form)
  (typecase form
    (float (let ((gensym-string (tformat-gensym-string "~F" form)))
	     (write-gensym-string-for-compiled-kb gensym-string)
	     (reclaim-gensym-string gensym-string)))
    (symbol
     (write-variable-for-compiled-kb form))
    (cons (write-function-call-for-compiled-kb form :double))))

;;; c-type is either a type (to be used for all expressions on the list)
;;; or a list of types (one for each expression)
(defun write-expression-list-for-compiled-kb
    (form-list separator-string c-types)
  (loop for first = t then nil
	for form in form-list
	for c-types-left = (when (consp c-types) c-types)
			 then (when c-types-left (cdr c-types-left))
	for c-type = (if c-types-left (car c-types-left) c-types)
	do (unless first
	     (write-gensym-string-for-compiled-kb separator-string))
	   (write-expression-for-compiled-kb-as-type form c-type)))

(defun write-statement-for-compiled-kb (form)
  (when (consp form)
    (case (car form)
      (tagbody
        (write-statement-or-tag-block-for-compiled-kb (cdr form)))
      (progn
        (write-statement-list-for-compiled-kb (cdr form)))
      (go
        (write-newline-for-compiled-kb)
        (write-gensym-string-for-compiled-kb "goto ")
        (write-tag-for-compiled-kb (cadr form)))
      (loop
	(write-newline-for-compiled-kb)
	(write-gensym-string-for-compiled-kb "while (")
	(write-expression-for-compiled-kb-as-type (third form) :boolean)
	(write-gensym-string-for-compiled-kb ") {")
	(let ((compiled-kb-indent (+f compiled-kb-indent 2)))
	  (write-statement-list-for-compiled-kb (cddddr form)))
	(write-newline-for-compiled-kb)
	(write-gensym-string-for-compiled-kb "}"))
      ((fixnum-case fixnum-case-with-fallthrough)
	(write-newline-for-compiled-kb)
	(write-gensym-string-for-compiled-kb "switch (")
	(write-expression-for-compiled-kb-as-type (cadr form) :int)
	(write-gensym-string-for-compiled-kb ") {")
	(let ((compiled-kb-indent (+f compiled-kb-indent 2)))
	  (loop for clause in (cddr form)
		do (let ((compiled-kb-indent (-f compiled-kb-indent 2)))
		     (write-newline-for-compiled-kb)
		     (write-case-tag-for-compiled-kb (car clause)))
		   (write-statement-list-for-compiled-kb (cdr clause))
		   (write-newline-for-compiled-kb)
	           (when (eq (car form) 'fixnum-case)
		     (write-gensym-string-for-compiled-kb "break;"))))
	(write-newline-for-compiled-kb)
	(write-gensym-string-for-compiled-kb "}"))	       
      (if
	(write-newline-for-compiled-kb)
	(write-gensym-string-for-compiled-kb "if (")
	(write-expression-for-compiled-kb-as-type (cadr form) :boolean)
	(write-gensym-string-for-compiled-kb ") {")
	(let ((compiled-kb-indent (+f compiled-kb-indent 2)))
	  (write-statement-for-compiled-kb (caddr form)))
	(write-newline-for-compiled-kb)
	(write-gensym-string-for-compiled-kb "} else {")
	(let ((compiled-kb-indent (+f compiled-kb-indent 2)))
	  (write-statement-for-compiled-kb (cadddr form)))
	(write-newline-for-compiled-kb)
	(write-gensym-string-for-compiled-kb "}"))
      (multiple-value-setq
       (write-newline-for-compiled-kb)
       (write-gensym-string-for-compiled-kb "{Object result = ")
       (write-expression-for-compiled-kb-as-type (caddr form) :object)
       (write-char-for-compiled-kb #\;)
       (let ((compiled-kb-indent (+f compiled-kb-indent 1)))
	 (write-newline-for-compiled-kb)
	 (write-gensym-string-for-compiled-kb "MVS_")
	 (write-fixnum-for-compiled-kb (length (cadr form)))
	 (write-gensym-string-for-compiled-kb "(result,")
	 (write-variable-list-for-compiled-kb (cadr form) ",")
	 (write-gensym-string-for-compiled-kb ");}")))
      ((let let*)
       (write-newline-for-compiled-kb)
       (write-char-for-compiled-kb #\{)
       (let ((compiled-kb-indent (+f compiled-kb-indent 2)))
	 (loop for (var init) in (cadr form)
	       do
	   (write-newline-for-compiled-kb)
	   (let ((c-type (c-type-of-variable var)))
	     (write-gensym-string-for-compiled-kb
	       (case (c-type-of-variable var)
		 (:object "Object ")
		 (:int "int ")
		 (:double "double ")
		 (:boolean "int ")))
	     (write-variable-for-compiled-kb var)
	     (write-gensym-string-for-compiled-kb " = ")
	     (write-expression-for-compiled-kb-as-type init c-type)
	     (write-char-for-compiled-kb #\;)))
	 (write-statement-list-for-compiled-kb (cddr form)))
       (write-newline-for-compiled-kb)
       (write-char-for-compiled-kb #\}))
      (t
       (write-newline-for-compiled-kb)
       (write-expression-for-compiled-kb-as-type
	 form (c-type-of-expression form :object)))))
  (write-char-for-compiled-kb #\;))

(defun write-statement-or-tag-list-for-compiled-kb (form-list)
  (loop for form in form-list
	do (if (atom form)
	       (if form
		   (let ((compiled-kb-indent (-f compiled-kb-indent 2)))
		     (write-newline-for-compiled-kb)
		     (write-tag-for-compiled-kb form)
		     (write-char-for-compiled-kb #\:)))
	       (write-statement-for-compiled-kb form))))

(defun write-statement-list-for-compiled-kb (form-list)
  (loop for form in form-list
	do (write-statement-for-compiled-kb form)))

(defun-void write-statement-block-for-compiled-kb (form-list index)
  (write-newline-for-compiled-kb)
  (write-char-for-compiled-kb #\{)
  (write-gensym-string-for-compiled-kb "  char *fn_name = \"fn")
  (write-fixnum-for-compiled-kb index)
  (write-gensym-string-for-compiled-kb "\";")
  (let ((compiled-kb-indent (+f compiled-kb-indent 2)))
    (write-statement-list-for-compiled-kb form-list))
  (write-newline-for-compiled-kb)
  (write-char-for-compiled-kb #\}))

(defun write-statement-or-tag-block-for-compiled-kb (form-list)
  (write-newline-for-compiled-kb)
  (write-char-for-compiled-kb #\{)
  (let ((compiled-kb-indent (+f compiled-kb-indent 2)))
    (write-statement-or-tag-list-for-compiled-kb form-list))
  (write-newline-for-compiled-kb)
  (write-char-for-compiled-kb #\}))
  
(defun-void write-function-for-compiled-kb (index lambda-form)
  (let ((compiled-kb-indent 0))
    (start-new-compiled-kb-line)
    (write-gensym-string-for-compiled-kb "static Object fn")
    (write-fixnum-for-compiled-kb index)
    (write-char-for-compiled-kb #\()
    (write-variable-list-for-compiled-kb (cadr lambda-form) ", ")
    (write-char-for-compiled-kb #\))
    (start-new-compiled-kb-line)
    (write-gensym-string-for-compiled-kb "  Object ")
    (write-variable-list-for-compiled-kb (cadr lambda-form) ", ")
    (write-char-for-compiled-kb #\;)
    (write-statement-block-for-compiled-kb (cddr lambda-form) index)
    (start-new-compiled-kb-line)))

(defun-void write-uncompiled-function-for-compiled-kb ()
  (cond
    #+development
    (emit-lisp-p
     (let ((out (kb-transfer-compiled-stream? current-kb-save)))
       (when out
	 (format out "(add-new-compiled-byte-code-body nil)~%"))))
    (t
     (start-new-compiled-kb-line)
     (write-gensym-string-for-compiled-kb "#define fn")
     (write-fixnum-for-compiled-kb
       (incff (compiled-kb-byte-code-body-count current-kb-save)))
     (write-gensym-string-for-compiled-kb " 0")
     (start-new-compiled-kb-line)
     (when (>f (length-of-saved-compiled-kb-file-so-far current-kb-save)
	       number-of-characters-beyond-which-to-start-a-new-saved-compiled-file)
       (increment-compiled-kb-file)))))

(defun-void write-function-definition-for-compiled-kb (byte-code-body constant-vector entry-points)
  (with-phrase-conses
    (multiple-value-bind (lambda-form new-constant-vector)
	(lisp-for-byte-code-body byte-code-body constant-vector entry-points)
      (unless (eq constant-vector new-constant-vector)
	(setf (byte-code-body-constant-vector byte-code-body)
	      new-constant-vector))
      (cond
	#+development
	(emit-lisp-p
	 (let ((out (kb-transfer-compiled-stream? current-kb-save)))
	   (when out
	     (format out "(add-new-compiled-byte-code-body~%  #'")
	     (let ((*print-level* nil)
		   (*print-length* nil))
	       (write lambda-form :stream out
		      :pretty t :case :downcase :right-margin 100))
	     (format out ")~%"))))
	(t
	 (start-new-compiled-kb-line)
	 (write-function-for-compiled-kb
	   (incff (compiled-kb-byte-code-body-count current-kb-save))
	   lambda-form)
	 (when (>f (length-of-saved-compiled-kb-file-so-far current-kb-save)
		   number-of-characters-beyond-which-to-start-a-new-saved-compiled-file)
	   (increment-compiled-kb-file)))))))

(defun-void write-description-of-function-for-compiled-kb
    (byte-code-body frame definition code-bodies constant-vector long-form-p)
  (let* ((text-string
	   (twith-output-to-text-string
	     (cond ((of-class-p frame 'code-body)
		    (if (cdr code-bodies)
			(tformat "  ~NF ~D~%"
				 definition
				 (position frame code-bodies))
			(tformat "  ~NF~%" definition)))
		   ((block-p frame)
		    (tformat "  ~NF ~A~%"
			     frame
			     slot-name-for-write-frame-for-kb))
		   ((framep frame)
		    (tformat "  ~A ~A~%"
			     (class frame)
			     slot-name-for-write-frame-for-kb)))
	     (when long-form-p
	       (write-byte-code-body
		 byte-code-body
		 constant-vector)
	       (tformat "~%"))))
	 (gensym-string
	   (twith-output-to-gensym-string
	     (twrite-string text-string)
	     (reclaim-text-string text-string))))
    (cond
      #+development
      (emit-lisp-p
       (let ((out (kb-transfer-compiled-stream? current-kb-save)))
	 (when out
	   (format out "~%#|~A|#~%" gensym-string))))
      (t
       (write-gensym-string-comment-for-compiled-kb gensym-string)))
    (reclaim-gensym-string gensym-string)))

(defvar write-all-byte-code-bodies-for-kb-p nil)

(defun compile-byte-code-body-for-kb-p (byte-code-body frame definition constant-vector)
  (declare (ignore frame))
  (and definition
       (not (byte-code-body-contains-instruction-that-should-not-be-compiled-p
	      byte-code-body constant-vector))
       (not (byte-code-body-is-too-long-to-compile-p byte-code-body))
       ;; remove this line once calling is optimized.
       (or write-all-byte-code-bodies-for-kb-p
	   (byte-code-body-contains-backward-branch-p byte-code-body constant-vector))))

(defun write-compiled-byte-code-body-for-kb (byte-code-body)
  (when enable-saving-compiled-kbs-p
    (let* ((frame frame-for-write-frame-for-kb)
	   (definition (and (of-class-p frame 'code-body)
			    (procedure-definition-of-code-body-function frame)))
	   (code-bodies (and (of-class-p definition 'procedure)
			     (code-bodies-function definition)))
	   (constant-vector
	     ;; interesting fact:  Only (byte-)code-body 0
	     ;; of a procedure has a constant vector
	     (or (byte-code-body-constant-vector byte-code-body)
		 (and code-bodies
		      (byte-code-body-constant-vector
			(code-body-byte-code-body-function
			  (car code-bodies))))))
	   (entry-points
	     (when definition
	       (loop for code-body-1 in (code-bodies-function definition)
		     do (when (eq (code-body-byte-code-body-function code-body-1)
				  byte-code-body)
			  (return (code-body-entry-points-function code-body-1)))
		 finally (return nil))))
	   (compile-p
	     (compile-byte-code-body-for-kb-p
	       byte-code-body frame definition constant-vector)))
      (write-description-of-function-for-compiled-kb
	byte-code-body frame definition code-bodies constant-vector compile-p)
      (if compile-p
	  (write-function-definition-for-compiled-kb
	    byte-code-body constant-vector entry-points)
	  (write-uncompiled-function-for-compiled-kb)))))


;;; The function `write-byte-code-body-for-kb' takes a byte-code-body and writes
;;; its contents into the kb currently being written.  This function is called
;;; from write-element-for-kb.

(defun write-byte-code-body-for-kb (byte-code-body)
  (write-compiled-byte-code-body-for-kb byte-code-body)
  (let* ((body-vector (byte-code-body-byte-vector byte-code-body))
	 (body-vector-length (byte-code-body-length byte-code-body))
	 (length-in-words
	   (ceilingf-positive body-vector-length 4))
	 (constant-vector? (byte-code-body-constant-vector byte-code-body))
	 (constant-vector-length?
	   (if constant-vector?
	       (length-of-simple-vector constant-vector?)))
	 (free-reference-vector?
	   (byte-code-body-free-references byte-code-body))
	 (free-reference-vector-length?
	   (if free-reference-vector?
	       (length-of-simple-vector free-reference-vector?))))
    (write-char-for-kb #\B)
    (write-fixnum-for-kb body-vector-length)
    (loop for index fixnum from 0 below (*f length-in-words 4) by 4
	  do
      (start-new-kb-line-if-appropriate)
      (write-binary-word-for-kb
	(logiorf
	  (byte-vector-aref body-vector (+f index 2))
	  (ashf (byte-vector-aref body-vector (+f index 3)) 8))
	(logiorf
	  (byte-vector-aref body-vector index)
	  (ashf (byte-vector-aref body-vector (+f index 1)) 8))))
    (start-new-kb-line-if-appropriate)
    (cond (constant-vector?
	   (write-fixnum-for-kb constant-vector-length?)
	   (loop for index fixnum from 0 below constant-vector-length?
		 for constant = (svref constant-vector? index)
		 do
	     (write-element-for-kb
	       (if (thing-is-item-p constant)
		   nil
		   constant))))
	  (t
	   (write-char-for-kb #\N)))
    (write-element-for-kb
      (byte-code-body-environment-description byte-code-body))
    (start-new-kb-line-if-appropriate)
    (cond (free-reference-vector?
	   (write-fixnum-for-kb free-reference-vector-length?)
	   (loop for index fixnum from 0 below free-reference-vector-length?
		 do
	     (write-element-for-kb (svref free-reference-vector? index))))
	  (t
	   (write-char-for-kb #\N)))))









;;; `Write-reference-to-frame' writes a `reference' to frame, either a G or
;;; an H KB element.
;;;
;;; This may be called before or after frame has been written.  If it is called
;;; before frame has been referenced or written, it writes out a G reference,
;;; sets (block-referenced-in-current-save-p block) to true, and increments
;;; (frame-reference-balance current-kb-save).
;;;
;;; Write-frame-for-kb decrements (frame-reference-balance current-kb-save) when
;;; it encounters a frame that has (block-referenced-in-current-save-p frame)
;;; true.  This information is used for debugging, to ensure that all references
;;; get resolved.
;;;
;;; On subsequent calls for the same frame, this writes an H references.  The H
;;; reference contains only the frame serial number.  (The G reference contains
;;; the class in addition.)
;;; 
;;; Note that frame here may only be a block, since it is a constraint violation
;;; to even have a reference to a non-block, i.e., a dependent frame.

(defmacro add-nodes-to-current-kb-save-traversal (new-nodes)
  `(journal-push
     (journal-cons (copy-frame-serial-number (current-frame-serial-number))
		   ,new-nodes)
     (kb-traversal-state-for-backup current-kb-save)))

(defmacro add-node-to-current-kb-save-traversal (new-node)
  `(add-nodes-to-current-kb-save-traversal (journal-list ,new-node)))

(defun write-reference-to-frame (frame)
  (start-new-kb-line-if-appropriate)
  (cond
    ((or (block-referenced-in-current-save-p frame)
	 (block-written-in-current-save-p frame))
     (write-char-for-kb '#\H)
     (write-frame-serial-number-for-kb (frame-serial-number frame)))
    (t
     (increment-frame-reference-balance frame 'write-reference-to-frame)
     (when
	 (and
	   (save-runtime-data? current-saving-context)
	   (or (and (null (superblock? frame))
	            (frame-of-class-p frame 'ui-client-item))
	       (frame-of-class-p frame 'procedure-invocation)))
       ;; See note.
       (add-node-to-current-kb-save-traversal frame))
     (setf (block-referenced-in-current-save-p frame) t)
     (write-char-for-kb '#\G)
     (write-frame-serial-number-for-kb (frame-serial-number frame))
     (start-new-kb-line-if-appropriate)
     (write-symbol-for-kb (class frame) t))))


;; Note:
;; G2-windows, and other instances of ui-client-item that are not on
;; kb-workspaces are considered not to be part of
;; the savable KB. (They are in limbo but not transient.)  However, if they
;; are linked to the KB by relation instances or membership in arrays or
;; lists, they will be referenced in the KB. So they must be written out. Note
;; that this case does not, and cannot apply in the case of saving modules.
;;
;; Upon being read back in, they will be
;; deleted after the read.  Procedure-invocations are never part of a saved
;; kb, but they may be referenced. They are always deleted after loading. They
;; will be written out if they have been referenced, or if they appear within
;; the traversal. These happen only when saving runtime data. The reason for
;; saving them is to have a consistent saved kb. When a consistent kb is
;; loaded, deleting procedure-invocations will remove all references to them.

;; We used to do this as a separate pass at the end of the traversal. The
;; problem with this technique is that if one ui-client-item is
;; referenced, and writing this item out causes a reference to another
;; ui-client-item or procedure-call to be written out, we weren't
;; writing the second ui-client-item out. So now we write these
;; out as soon as we detect that a reference to them has been written.


;;; Write-slot-group-for-block?  ...  This is called from write-frame-for-kb.
;;; Slot-group-for-block?  is presumably the same as (slot-group-for-block?
;;; block).

;;; The as-ghost? argument is as documented for write-frame-for-kb.  Note
;;; that it's illegal to call this if block has connections.  Note that
;;; when writing out an ghost, the location of the top, left corner is
;;; put at (0, 0), and the width and height of an entity are normalized
;;; to what they would be if icon-attributes-plist is nil, which is
;;; how block is expected to be written out by the caller.

(defun write-slot-group-for-block? (block slot-group-for-block?
				     &optional as-ghost?)
  (cond
    (slot-group-for-block?
     (let* ((connections (downgrade-connections (connections block)))
	    (collectable-connections
	      (if (and connections
		       (not (save-runtime-data? current-saving-context)))
		  (clip-transients-from-connections connections)
		  connections))
	    (collectable-subblocks
	      (if as-ghost?
		  nil
		  (copy-collectable-blocks-for-subblocks (subblocks block)))))
       (write-char-for-kb #\L)
       (write-fixnum-for-kb
	 (if as-ghost?
	     0
	     (left-edge-of-block block)))
       (write-fixnum-for-kb
	 (if as-ghost?
	     0
	     (top-edge-of-block block)))
       (write-fixnum-for-kb
	 (if as-ghost?
	     (if (and (entity-p block)
		      (icon-description block))
		 (or (getfq (icon-attributes-plist block) 'width)
		     (width-of-icon (icon-description block)))
		 (width-of-block block))
	     (right-edge-of-block block)))
       (write-fixnum-for-kb
	 (if as-ghost?
	     (if (and (entity-p block)
		      (icon-description block))
		 (or (getfq (icon-attributes-plist block) 'height)
		     (height-of-icon (icon-description block)))
		 (height-of-block block))
	     (bottom-edge-of-block block)))
       (when (or collectable-subblocks collectable-connections)
	 (write-element-for-kb collectable-subblocks))
       (when collectable-connections
	 #+development
	 (if as-ghost?
	     (error
	       "It's an error to write out a block with ~
                connections as an ghost!"))
	 (write-element-for-kb collectable-connections))
       (write-char-for-kb #\R)
       (reclaim-gensym-list collectable-subblocks)
       (when (and (not (save-runtime-data? current-saving-context))
		  collectable-connections)
	 (reclaim-gensym-list collectable-connections))
       #+connections-v2 ; for downgrade-connections
       (reclaim-slot-value-list connections)))
    (t
     (write-element-for-kb nil))))

;; See also read-slot-group-for-block?.



;;; write-double-float-for-kb writes a double float in either
;;; M or P format, according to whether or not it has an integer
;;; value of moderate size. Any number within the interval bounded
;;; by the following constants is a fixnum on all platforms. 

(defmacro most-positive-fixnum-for-ti () 16777215)

(defmacro most-negative-fixnum-for-ti () -16777216)

(defmacro float-of-most-positive-fixnum-for-ti ()
  (coerce-to-gensym-float 16777215))

(defmacro float-of-most-negative-fixnum-for-ti ()
  (coerce-to-gensym-float -16777216))

;;; The M format is like an integer format preceeded by M. It ends in
;;; + or -. The P format has a P followed by exactly 10 ascii characters.
;;; Each group of 5 encodes 32 bits using binary word format.

(defmacro write-double-float-second-case (double-float char)
  `(multiple-value-bind (x1 x2 x3 x4)
       (encode-double-float ,double-float)
     (write-char-for-kb ,char)
     (write-binary-word-for-kb x1 x2)
     (write-binary-word-for-kb x3 x4)))


(defun write-double-float-for-kb (double-float)
  ;; Put in case I
  (cond
    ((and (not (exceptional-float-p double-float)) ; Issue #HQ-116393
						   ;   (MHD/JH 11/7/94)
	  (<e (float-of-most-negative-fixnum-for-ti)
	      double-float
	      (float-of-most-positive-fixnum-for-ti))
	  ;; This test comes second, otherwise bignums can
	  ;; be generated.
	  (= double-float (ftruncate double-float)))
     (write-char-for-kb #\M)
     (write-fixnum-for-kb (truncate double-float)))
    
    (t (write-double-float-second-case double-float #\P))))


  
#+obsolete				; to be removed shortly
(defun write-managed-float-array-for-kb (managed-float-array character?)
  (when character?
    (write-char-for-kb character?))
  (loop with length = (managed-float-array-length managed-float-array)
	with elements-written = 0
	initially (write-integer-for-kb length)
	do (with-temporary-gensym-float-creation write-managed-float-array
	     (loop
	       do (multiple-value-bind (x1 x2 x3 x4)
		      (encode-double-float
			(managed-float-aref
			  managed-float-array
			  elements-written))
		    (write-binary-word-for-kb x1 x2)
		    (write-binary-word-for-kb x3 x4))
		  (incff elements-written)
	       until (or (=f elements-written length)
			 (=f 0 (modf elements-written 1000)))))
	while (<f elements-written length)))

;; Make this a primitive KB element!


;; The following pieces of save-kb have been turned into functions
;; because they are also called from journals.

(defun delete-kb-object-index-property-names
       (property-name symbol-list)  
  (loop for symbol 
	    in symbol-list
	do 
    (as-atomic-operation			; wrap around outer loop?
      (loop as l-trailer? = nil then (cdr l)
	    as l = (symbol-plist symbol) 
		 then (cdr l-trailer?)
	    while l				; just in case
	    when (eq (car l) property-name)
	      do 
		(if l-trailer?
		    (setf (cdr l-trailer?) (cddr l))
		    (setf (symbol-plist symbol) (cddr l)))
		(setf (cddr l) nil)
		(reclaim-gensym-list l)
		(loop-finish)))))


(defun-allowing-unwind write-initial-plist (kb-name)
  (protected-let*
      ((clean-version			; copies gensym strings as
	 (copy-for-slot-value		;   text strings as necessary!
	   (if ok-file-saving-mode?
	       (make-system-version-for-ok-file)
	       current-system-version))
	 (reclaim-slot-value clean-version))
       (plist
	 (slot-value-list
	   'system-version clean-version
	   
	   'kb-flags
	   (if ok-file-saving-mode?
	       (make-kb-flags-for-ok-file)
	       kb-flags-for-saving)
	   'timestamp 0
	   'base-time (clock-get gensym-base-time-as-managed-float)
	   'start-time (clock-get gensym-time-at-start)
	   'gensym-time (clock-get gensym-time)
	   'kb-name kb-name
	   'current-frame-serial-number (frame-serial-number-hash (current-frame-serial-number))
	   'type-of-file
	   ;; See note by defn. of type-of-kb-save.
	   (cond
	     ((eq (type-of-kb-save current-saving-context?) 'kb-save)
	      'save-kb)
	     ((eq (type-of-kb-save current-saving-context?) 'kb-save-with-runtine-data)
	      'save-kb-with-runtine-data) ; ... runtiNe [SIC][!!!] [See note (MHD 1/11/93)]
	     ((null (type-of-kb-save current-saving-context?))
	      'journal)
	     (t (type-of-kb-save current-saving-context?)))
;	      (or (type-of-kb-save current-saving-context?)
;		  'journal)
	   )))

    ;; jh per the licensing committee, 5/8/97.  Added the following three
    ;; properties so we can observe possible infringement by customers holding a
    ;; mixture of permanent and temporary G2 licenses.
    (when (system-time-too-early-for-launch?)
      (setq plist
	    (nconc plist  
		   (slot-value-list
		     (property-for-system-time-too-early-for-launch?)
		     (system-time-too-early-for-launch?)))))
    (when (system-clock-setback-before-kb-load?)
      (setq plist
	    (nconc plist  
		   (slot-value-list
		     (property-for-system-clock-setback-before-kb-load?)
		     (system-clock-setback-before-kb-load?)))))
    (when (setback-time-preventing-kb-save?)
      (setq plist
	    (nconc plist  
		   (slot-value-list
		     (property-for-setback-time-preventing-kb-save?)
		     (setback-time-preventing-kb-save?)))))
    
    ;; Note: just noticed that the following seems wrong to do, i.e., in the
    ;; case of saving a module other than the installed, top-level module.  It
    ;; looks as though this is only used at warmboot time, so that's probably
    ;; why this has caused no problems.  This has been this way for a while, so
    ;; it would take some amount and be risky to casually change it at
    ;; present. (MHD 11/13/96)
    (when (neq 'real-time (scheduler-mode timing-parameters))
      (nconc plist (slot-value-list 'simulated-time (clock-get gensym-time))))

    (let ((module-information-table?
	    (if (kb-module-being-saved? current-kb-save)
		(module-information-instance-for-module?
		  (kb-module-being-saved? current-kb-save)))))
      (when module-information-table?
	(if (top-level-kb-module? module-information-table?)
	    (nconc
	      plist  
	      (slot-value-list
		'top-level-module
		(top-level-kb-module? module-information-table?))))
	(if (directly-required-kb-modules module-information-table?)
	    (nconc
	      plist  
	      (slot-value-list	    
		'required-modules
		(directly-required-kb-modules module-information-table?))))))
    (write-source-code-comment-if-any-for-kb)
    (write-char-for-kb #\J)
    (write-element-for-kb plist)
    (reclaim-slot-value-list plist)))


;;; `Write-source-code-comment-if-any-for-kb' emits the lines of
;;; the saving-parameters source code control comment text to the
;;; current KB as a comment, where each line starts with a semicolon
;;; and a space, followed by the line of text from the comment, e.g.,
;;;
;;;    ; this is one line of text
;;;    ; and this is the second

(defun-allowing-unwind write-source-code-comment-if-any-for-kb ()
  (protected-let*
      ((saving-parameters-instance?
	 (if (kb-module-being-saved? current-kb-save)
	     (get-system-table-instance-for-module
	       'saving-parameters
	       (kb-module-being-saved? current-kb-save))
	     saving-parameters))
       (kb-file-comment-text?
	 (if saving-parameters-instance?
	     (cdr (get-slot-value	; fwd. ref.!
		    saving-parameters-instance?
		    'kb-file-comment)))))
    (when kb-file-comment-text?
      (twith-output-to-then-use-of-wide-string
	(macrolet ((emit ()
		     `(let ((s (export-text-string
				 current-wide-string
				 'kb-file-comment
				 output-string-start
				 fill-pointer-for-current-wide-string)))
			(write-char-for-kb #\;)
			(write-char-for-kb #\space)
			(loop for i from 0 below (length s)
			      do (write-char-for-kb (char s i)))
			(reclaim-gensym-string s)
			(setq output-string-start
			      fill-pointer-for-current-wide-string)
			(start-new-kb-line))))
	  (loop with output-string-start
		  = fill-pointer-for-current-wide-string
		for character being each text-character
	        of kb-file-comment-text?
		do (cond
		     ((newline-p character)
		      (emit))
		     (t
		      (twrite-char character)))
		finally
		  (unless (=f fill-pointer-for-current-wide-string
			      output-string-start)			    
		    (emit))))))))




;;; `Write-final-plist' writes the last set of characters out to the current KB
;;; being written.  As of 4.0, this appends a newline character at the very end,
;;; just to help lame unix tools that can't "see" records that end with the
;;; end-of-file instead of a newline.

(defun write-final-plist (pane-description? timestamp)
  (start-new-kb-line)
  (write-char-for-kb '#\E)

  ;; Catch a bug: this removes any image plane descriptions for
  ;; workspaces that have not yet been written -- if any are
  ;; found, an error is signalled in development -- there should
  ;; not be any! (MHD 1/9/94)
  (if pane-description?
      (setq pane-description?
	    (check-pane-description-for-unwritten-workspaces
	      pane-description?)))
  
  (let ((plist
	  (nconc
	    (slot-value-list
	      'final-frame-serial-number
	      (frame-serial-number-hash (current-frame-serial-number))
	      ;; Misleading; this is really timestamp, same time as the in
	      ;; initial-plist, but as a float.
	      'index-displacement
	      timestamp
	      ;; Use of this mystifying entry explained below
	      #-pre-g2-v5-licensing
	      'reclaimed-index-count
	      #-pre-g2-v5-licensing
	      (+f
		#+runtime-functionality-without-a-license
		2
		#-runtime-functionality-without-a-license
		(cond
		    ((embedded-option-authorized-p) 1)
		    ((runtime-option-authorized-p) 2)
		    ((restricted-use-option-authorized-p) 3)
		    (t 0))
		  ;; Relies on frame-serial-number being non-negative fixnum.
		  (-f (frame-serial-number-hash (current-frame-serial-number)))
		  (*f (floorf-positive
			(modf-positive
			  (get-fixnum-time) (most-positive-fixnum-for-ti))
			11) 11))
	      )
	    ;; Null pane description if not
	    ;;    being saved from a window
	    (if pane-description?
		(slot-value-list 'detail-pane-description pane-description?))
	    (if (kb-transfer-numeric-symbols current-kb-save)
		(slot-value-list
		  'numeric-symbols
		  (kb-transfer-numeric-symbols current-kb-save)))
	    (if (original-kb-state-plist-written? current-kb-save)
		(slot-value-list
		  'original-kb-state-plist-written?
		  t)))))		
    (write-element-for-kb plist)
    (reclaim-slot-value-list plist))
  (write-element-for-kb (next-kb-object-index current-kb-save))
  (write-element-for-kb 0)
  (write-element-for-kb 0)

  (start-new-kb-line)			; final newline (MHD 2/3/94)
  (update-file-progress-for-writing t))




;;; `write-timestamp-for-kb' write a timestamp to a KB using the convention
;;; documented for saved files. The argument is a gensym time, which at present
;;; is a fixnum. Since there is no way to recognize a gensym time,
;;; write-timestamp-for-kb cannot be called contextually from
;;; write-element-for-kb. It is called from history buffer writing and elsewhere
;;; explicitly.

(defun write-timestamp-for-kb (gensym-time-arg)
  (if (kb-transfer-previous-timestamp? current-kb-save)
      (let ((delta (- gensym-time-arg
		      (kb-transfer-previous-timestamp? current-kb-save))))
	(cond
	  ((and (<f delta 0)
		(>f delta (most-negative-fixnum-for-ti)))
	   (write-non-negative-fixnum-for-kb (-f delta))
	   (write-char-for-kb #\) ))
	  ((and (>=f delta 0)
		(<f delta (most-positive-fixnum-for-ti)))
	   (write-non-negative-fixnum-for-kb delta)
	   (write-char-for-kb #\( ))
	  (t (write-double-float-second-case
	       (convert-gensym-time-to-unix-time gensym-time-arg) #\&))))
      (write-double-float-second-case
	(convert-gensym-time-to-unix-time gensym-time-arg) #\&))

  (setf (kb-transfer-previous-timestamp? current-kb-save) gensym-time-arg))

;; gensym-time-arg is used because gensym-time is a system-variable.





;;;; Writing Runtime Data for KB

(def-system-variable left-braket-written? kb-save1 nil)

(defmacro write-left-bracket-if-necessary ()
  '(unless left-braket-written?
     (write-char-for-kb #\[ )
     (setq left-braket-written? t)))



;;; `write-runtime-data-for-kb' writes runtime elements if there is anything to
;;; write. If it writes anything, the first character must be #\[. This is
;;; controlled by left-braket-written?, which is global to avoid rebinding cost.

(declare-forward-reference write-g2-array-data-for-kb function)
(declare-forward-reference write-g2-list-data-for-kb function)

(defun-void write-runtime-data-for-kb (block class)  
  (setq left-braket-written? nil)
  (class-case class
    (parameter
      (write-parameter-data-for-kb block))
    (variable
      (write-variable-data-for-kb block))
    (simulation-subtable
      (write-simulation-subtable-data-for-kb block))
    (kb-workspace
      (when (active-p block)
	(write-left-bracket-if-necessary)
	(write-char-for-kb #\K)))
    (trend-chart
      (write-trend-chart-data-for-kb block)) ; JED 12/28/93
    (g2-array 
      (write-g2-array-data-for-kb block))
    (g2-list
      (write-g2-list-data-for-kb block))
    (hash-table
      (write-hash-table-data-for-kb block)))
  (when (and (relation-instances block)
	     (if (frame-of-class-p block 'class-definition)
		 (finished-writing-definitions? current-kb-save)
		 t))
    (write-relation-instances-for-kb block)))

;; Write-parameter-data-for-kb and write-variable-data-for-kb are in
;; HISTORIES.  Write-g2-array-data-for-kb is in ARRAYS,
;; write-g2-list-data-for-kb is in LISTS.


;;; The function `write-relation-instances-for-kb' writes the relation-instances
;;; of a block when saving run-time data (snapshotting a kb).  It's only caller
;;; is write-runtime-data-for-kb.  It is only useful for saving a kb in a single
;;; file with runtime-changes which includes transient items.

(defun-void write-relation-instances-for-kb (block)
  (let ((value-to-save?
	 (when-let (relation-instances (relation-instances block))
	   (loop with converted-value? = nil
		for relation-instance being each relation-instance of relation-instances
		for relation-frame = (relation-instance-relation relation-instance)
		for object-frames-for-saving?
		    = (loop for object-frame being each related-item
					     of (relation-instance-items relation-instance)
			    when (collectable-block-p object-frame)
			      collect object-frame using slot-value-cons)
		do
	    (setq converted-value?
		  (nconc
		    converted-value?
		    (when object-frames-for-saving?
		      (slot-value-list
			(nconc
			  (slot-value-list
			    (cond ((consp relation-instance)
				   (first relation-instance))
				  (t
				   (relation-instance-name relation-instance)))
			    relation-frame)
			  object-frames-for-saving?)))))
		finally (return converted-value?)))))
    (when value-to-save?
      (write-left-bracket-if-necessary)
      (write-char-for-kb #\R)
      (write-element-for-kb value-to-save?)
      (reclaim-slot-value value-to-save?))))



;;; `Write-relation-instances-block-modification' .... Presumably, block has
;;; runtime data, but that is not strictly necessary.

(defun-void write-runtime-data-frame-modification (block)
  (start-new-kb-line)
  (write-char-for-kb '#\F)
  (write-frame-serial-number-for-kb (frame-serial-number block))
  (write-element-for-kb (class block))
  (write-runtime-data-for-kb block (class block))
  (write-char-for-kb '#\!))

;; This is used by write-kb-traversal-state-node when writing definitions as
;; they appear in the KB hierarchy, since runtime data cannot be included in the
;; definitions section of a definition.  In fact this is the first, and only,
;; case of writing a "frame modification", which is new for 4.0.  (MHD 1/4/94
;; and 1/24/94)


;;; `Write-entangled-slots-of-definition-as-frame-modification' .... writes all
;;; of the known entangled slots a definition may have.
;;; Frame-representations have have entanglements, but they're not difficult,
;;; since they at present only refer to the item they represent and to the class
;;; table, which is built in.

(defun-void write-entangled-slots-of-definition-as-frame-modification (definition)
  (when (entangled-slots definition)
    (start-new-kb-line)
    (write-char-for-kb '#\F)
    (write-frame-serial-number-for-kb (frame-serial-number definition))
    (write-element-for-kb (class definition))
    (loop with entangled-slots = (entangled-slots definition)
	  for unique-slot-name in (entangled-slots definition)
	  for slot-description = (get-slot-description-of-frame
				   unique-slot-name definition)
	  
	  do
      (if (eq unique-slot-name 'relation-instances)
	  (let ((relation-instances-slot-description
		  (slot-description-from-class 'definition 'relation-instances))
		(slot-value-to-save
		  (convert-intermodual-relation-instances-for-saving
		    definition (relation-instances definition))))
	    (write-slot-for-kb
	      definition relation-instances-slot-description slot-value-to-save)
	    (reclaim-slot-value slot-value-to-save))
	  (write-slot-for-kb
	    definition slot-description
	    (get-slot-description-value-macro definition slot-description)))
	  finally
	    (progn
	      (reclaim-slot-value entangled-slots)
	      (setf (entangled-slots definition) nil)))
    (write-char-for-kb '#\!)))

;; This may need to be revisited.  Consider having a slot type feature
;; "entangled".  This should also go on slots such as frame-representations,
;; and some of the slots on g2 arrays and g2 lists.  Note that for saving
;; definitions, an entanglement is only a problem if it involves pointers
;; to instances whose definition may not yet have been read in.




;;;; Reformatting Blocks



;;; Slot putters for font map slots of format frames should, when loading or
;;; merging a kb, substitute for unavailable fonts, indicating that this has
;;; been done by setting the format-change? slot to an (arbitary) integer.



;;; `Reformat-as-appropriate' implements the bringing formats uptodate switch of
;;; KB load for individual items.  It is defined for all blocks, and refined for
;;; those blocks that can update their formats.

;;; A reformat-as-appropriate method returns either: nil, to indicate that the
;;; method should be applied to each subblock; DO, to indicate that the
;;; superblock should reformat this, as it promised it could; or DONE, to
;;; indicate that the block is all set, whether reformatted or not, and should
;;; not apply the method to subblocks.

(def-generic-method reformat-as-appropriate
		    (table superblock-will-do-reformatting?))

(defun reformat-as-appropriate (block superblock-will-do-reformatting?)
  (or (funcall-method-if-any
	'reformat-as-appropriate block superblock-will-do-reformatting?)
      (loop for subblock being each subblock of block
	    do (reformat-as-appropriate subblock nil))))



;;; `Format-frame-to-reformat-by-if-any' ...  Block? is used either (1) to see
;;; whether it is new or (2) to get a default format name if the format-frame is
;;; missing a name AND has a null format-change? slot.  Case (2) is really a
;;; constraint violation, but it's crept in to KBs and we now expect it.  This
;;; applies in the common case where block? is a text box.
;;;
;;; A returned format frame may or may not be format-frame.

(defun format-frame-to-reformat-by-if-any (block? format-frame)
  (let ((format-change? (format-change? format-frame)))
    (if format-change?
	(cond
	  ((integerp format-change?)
	   (if block?				; is this a new block?!!!
	       format-frame))
	  (reformat-as-appropriate?
	   (get-instance-with-name-if-any
	     'format-frame
	     format-change?))
	  (t nil))
	(if (and block?
		 (null (name-or-names-for-frame format-frame))
		 (text-box-p block?)
		 (default-text-box-format-name block?))	; defensive
	    (get-or-make-format-frame
	      ;; new: if none to reformat by, then use the default text box
	      ;; format.  (MHD 12/29/93) and (MHD 5/30/95)
	      (default-text-box-format-name block?))))))



(def-class-method reformat-as-appropriate (table superblock-will-do-reformatting?)
  (let* ((table-format-to-reformat-by?
	   (format-frame-to-reformat-by-if-any table (table-format table)))
	 (reformat-table? table-format-to-reformat-by?))
    (loop for row in (table-rows table)
	  do (loop for cell? in row
		   when (if cell?
			    (if (cell-is-block-p cell?)
				(eq (reformat-as-appropriate cell? t) 'do)
				(let ((text-box-format-to-reformat-by?
					(format-frame-to-reformat-by-if-any
					  table (text-cell-format cell?))))
				  (if text-box-format-to-reformat-by?
				      (setf (text-cell-format cell?)
					    text-box-format-to-reformat-by?)))))
		     do (setq reformat-table? t)))
    (if table-format-to-reformat-by?
	(setf (table-format table) table-format-to-reformat-by?))
    (if reformat-table?
	(cond
	  (superblock-will-do-reformatting? 'do)
	  (t (reformat-table-in-place table)
	     (setq refresh-all-windows-after-merging? t)  ; fix by mhd
	     'done))
	'done)))


(def-class-method reformat-as-appropriate (text-box superblock-will-do-reformatting?)
  (let* ((text-box-format-to-reformat-by?
	   (format-frame-to-reformat-by-if-any text-box (text-box-format text-box))))
    (cond
      (text-box-format-to-reformat-by?
       (setf (text-box-format text-box) text-box-format-to-reformat-by?)
       (cond
	 (superblock-will-do-reformatting? 'do)
	 (t (reformat-text-box-in-place text-box nil)
	    (setq refresh-all-windows-after-merging? t)  ; fix by mhd
	    nil))))))

;; The above two were fixed today so that (1) changes in graphics due to reformatting
;; would be properly reflected in the GEM's of existing image planes after a merge,
;; and (2) changes in the size of blocks due to reformatting would result in
;; workspaces being enlarged if appropriate.  (MHD 4/2/90)

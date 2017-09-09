;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module FACILITIES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David




;;;; Forward References in FACILITIES



;; To EDIT1

(declare-forward-reference enter-editing-context function)
(declare-forward-reference find-position-in-text-given-image-plane function)


;; To EDIT2

(declare-forward-reference delete-frame-after-checking-serial-number function)


;; To DISPLAYS

(declare-forward-reference make-graph function)
(declare-forward-reference make-meter function)
(declare-forward-reference make-dial function)
(declare-forward-reference make-readout-table function)
(declare-forward-reference enter-move-dragging-context function)
(declare-forward-reference enter-transfer-dragging-context function)
(declare-forward-reference enter-image-plane-dragging-context function)


;; To GRAPHS1

(declare-forward-reference change-size-of-graph function)
(declare-forward-reference restore-graph-to-normal-size function)


;; To FUNCTIONS

(declare-forward-reference put-up-table-of-values function)


;; To CYCLES

(declare-forward-reference system-start function)
(declare-forward-reference system-reset function)
(declare-forward-reference system-resume function)
(declare-forward-reference system-restart function)



;; To PARSE

(declare-forward-reference finish-parsing-insofar-as-possible function)


;; To CONTROLS

(declare-forward-reference enter-dialog function)
(declare-forward-reference enter-button-down-context function)
(declare-forward-reference set-up-bounding-dialog-ws function)
(declare-forward-reference highlight-or-unhighlight-button function)
(declare-forward-reference get-block-on-workspace-for-frame function)
(declare-forward-reference get-type-in-text-box function)
(declare-forward-reference goto-frame-instance function)
(declare-forward-reference add-as-inferior-block function)
(declare-forward-reference make-button function)
(declare-forward-reference
  fit-entity-around-text-box-or-bounding-rectangle
  function)
(declare-forward-reference enter-close-box-widget-pending-context function)
(declare-forward-reference show-or-hide function)


;; To MOVES

(declare-forward-reference reclaim-dragging-list-function function)
(declare-forward-reference dragging-cons-function function)
(declare-forward-reference block-transferable-p function)
(declare-forward-reference move-blocks-with-their-external-connections function)
(declare-forward-reference make-outline-for-blocks-to-drag function)
(declare-forward-reference shift-blocks-with-their-external-connections function)



;; To KB-SAVE2

#+pre-g2-v5-licensing
(declare-forward-reference ok-kb-p function)

(declare-forward-reference saving-parameters variable)
(declare-forward-reference get-saving-parameters function)

;; To KB-SAVE4

(declare-forward-reference module-contains-text-stripped-frames-p function)


;; To KB-MERGE

(declare-forward-reference make-new-top-level-kb-workspace function)
(declare-forward-reference check-savability-of-kb-in-terms-of-modularity function)
(declare-forward-reference module-information variable)


;; To FILTERS

(declare-forward-reference make-table-describing-restrictions function)
(declare-forward-reference non-menu-choice-permitted-p function)
(declare-forward-reference frame-system-operation-is-allowed-p function)
(declare-forward-reference workspaces-can-be-shown-at-this-kb-level-p function)
(declare-forward-reference subworkspace-connection-posts-p function)


;; To QUERIES

(declare-forward-reference name-for-frame-p function)	; move?!


;; To GRAMMAR2

(declare-forward-reference miscellaneous-parameters variable)

;; To GRAMMAR6

(declare-forward-reference
  grammar-categories-getting-choose-existing-class-feature variable)


;; To ICONS2

(declare-forward-reference enter-icon-editor function)

;; To CHARTS1

(declare-forward-reference restore-chart-to-normal-size function)
(declare-forward-reference change-size-of-chart function)
(declare-forward-reference default-chart-width variable)
(declare-forward-reference default-chart-height variable)

;; To NEW-TABLES

(declare-forward-reference mouse-over-cell-in-new-table-p function)

;; To KB-LOAD1

(declare-forward-reference make-and-set-up-kb-load-file-command function)
(declare-forward-reference handle-file-command function)
(declare-forward-reference clone-frame function)
(declare-forward-reference get-pathname-for-file-command function)


;; To ACTIONS

(declare-forward-reference set-neither-permanent-nor-transient-and-propagate function)


;; To ACTIVATE

(declare-forward-reference superior-frame function)

;; To GRAPHS

(declare-forward-reference change-size-of-trend-chart function)
(declare-forward-reference restore-trend-chart-to-normal-size function)
(declare-forward-reference make-trend-chart function)
(declare-forward-reference default-trend-chart-width variable)
(declare-forward-reference default-trend-chart-height variable)

;; To Others..

(declare-forward-reference requeue-event-and-abort-workstation-context function)
(declare-forward-reference destabilizing-item-deletion-p function) ;comp-utils
(declare-forward-reference c-get-system-drives-list function) ;commands2
(declare-forward-reference c-get-system-special-folders function) ;commands2
(declare-forward-reference invoke-rules-for-movement-chaining function)

(declare-forward-reference send-ws-representations-item-moved function)
(declare-forward-reference send-ws-representations-item-virtual-attribute-change function)
(declare-forward-reference start-procedure-invocation-in-place function)

(declare-forward-reference count-instances-of-g2gl-process function) ; G2-BPEL
(declare-forward-reference user-writable-slot-of-instance-p function) ; attr-export


;; I'm removing all of these -- they should be consistent with the main
;; menu, which (algorithmically) initial-caps each word.  Also, they
;; were inconsistent among themselves -- the first one being capitalize-
;; all-words, and the other two being sentence-style capitalization.
;; At this time, we're also capitalizing the menu title capitalize-all-words
;; style; it used to be sentence-style.   Note that the Miscellany menu
;; now has sentence-like choices with insignificant words capitalized,
;; e.g., "Connect To Foreign Image" with "To" capitialized.  Now these
;; are consistent with those.  Consider making the algorithmic capitilization
;; scheme optionally leave insignificant words in all lowercase, e.g.,
;; to, from, in, and, etc.  (MHD 6/18/92)

;(def-menu-string	   ; this probably was meant to be initial cap only!
;  remove-tracing-and-breakpoints  "Remove Tracing and Breakpoints")
;(def-menu-string enable-all-items "Enable all items")
;(def-menu-string highlight-invoked-rules "Highlight invoked rules")
;(def-menu-string
;  do-not-highlight-invoked-rules "Do not highlight invoked rules")




;;; The five commands for running G2 are Start, Pause, Resume, Reset and Restart
;;; There are three modes that the system can be in and only some of the commands
;;; are available in each mode.
;;;
;;;   (i)   Initially and after Reset:
;;;         Start causes G2 to run starting from the beginning.
;;;   (ii)  While running:
;;;         Pause causes G2 to stop running. One may Resume.
;;;         Reset causes G2 to stop running. G2 is now in initial condition and one may Start.
;;;         Restart causes G2 to immediately start from the beginning. This is equivalent
;;;            to Reset followed by Start.
;;;   (iii) After pausing:
;;;         Resume causes G2 to continue from where it had left off. There is no
;;;            interuption to simulated time. (See note on local time below.)
;;;         Reset as above
;;;         Restart as above

;;; Note on local time: It is desirable to keep G2 time and real time synchronized when
;;; possible. In as-fast-as-possible mode, G2 time and real time will be synchronized each
;;; time G2 is started, but not each time G2 is resumed. If the simulation is
;;; running at a rate which is the real time rate, the local time and G2 time will be
;;; identical unless there is a pause followed by a resume. It is unavoidable in that
;;; case that they be out of synch since G2 time must continue as if there had been no pause.

;; Consider changing the names of these (boolean) variables to have the standard "?"
;; or "p" suffix.

;; Consider having only one three-way variable, say current-state-of-running-system?, that
;; can be set to, say, either nil, suspended, or t, instead of two boolean variables.


;;; **** Fix the editor to not call this !!! ****

;; At present, load-kb, merge-kb, and save-kb are essentially gigantic
;; "atomic operations" which are only known to work while the system is in
;; an initial, reset, or paused state.  Engineering IS required in a number
;; of different areas of the system to be able to do these while running.










;;; Workspace-can-be-hidden? ...

(defun workspace-can-be-hidden? (workspace)
  ;; Only allow hiding non-KB workspaces (including temporary
  ;; workspaces) if they are named (e.g.  the Message Board) or if they
  ;; are logbook pages.  (MHD 1/18/88) -- Updated to inlude logbook
  ;; pages today.  (MHD 6/22/92)
  (if (frame-of-class-p workspace 'non-kb-workspace)
      (or (name-or-names-for-frame workspace)
	  (frame-of-class-p workspace 'logbook-page))
      t))

  




(defun handle-create-new-module-window-menu-choice
       (x-in-window y-in-window)  
  (let ((new-module-information (make-system-frame 'module-information)))
    (put-up-attributes-table new-module-information x-in-window y-in-window)
    (with-old-style-workstation-return-function
	('store-hand-created-module-information-if-appropriate
	   (slot-value-list new-module-information
			    (copy-frame-serial-number (frame-serial-number new-module-information)))
	   'delete-hand-created-module-information-if-appropriate)
      (enter-editing-context new-module-information 'top-level-kb-module?))
    'delete-module-information-if-unspecified-module))





;;; Handle-file-related-window-menu-choice ... Choice-symbol must one of
;;; the following symbols.
;;;
;;;    save-kb  load-kb  merge-kb
;;;    connect-to-foreign-image  disconnect-from-foreign-image
;;;    load-attribute-file

(defparameter use-new-load-kb? t)

(defun handle-file-related-window-menu-choice (choice-symbol)
  (cond ((and (native-file-dialog-p current-workstation-window)
	      (memq choice-symbol '(load-kb merge-kb save-kb save-module
				    load-attribute-file write-g2-stats)))
	 (native-handle-file-related-window-menu-choice choice-symbol))
	(t
	 (classic-handle-file-related-window-menu-choice choice-symbol))))

(defun classic-handle-file-related-window-menu-choice (choice-symbol)
  (multiple-value-bind (title? symbolic-file-type?
			       inconsistent-so-save-all? module-case?
			       new-operation-symbol? command-verb-string?
			       comment-string?)
      (preflight-file-related-window-menu-choice choice-symbol)
    (declare (ignore new-operation-symbol?))
    (cond ((null title?))
	  ((and use-new-load-kb?
		(or (eq choice-symbol 'load-kb)
		    (eq choice-symbol 'merge-kb)))
	   (let ((command-frame
		   (make-and-set-up-kb-load-file-command
		     (eq choice-symbol 'merge-kb))))
	     (with-old-style-workstation-return-function
		 (nil
		   (gensym-list
		     command-frame
		     (copy-frame-serial-number (current-frame-serial-number)))
		   'delete-frame-after-checking-serial-number-with-list)
	       (enter-editing-context
		 command-frame
		 'box-translation-and-text))))
	  (t
	   (handle-file-command (or command-verb-string? title?)
				symbolic-file-type?
				inconsistent-so-save-all?
				module-case?)))
    (when command-verb-string?
      (reclaim-text-string command-verb-string?))
    (when comment-string?
      (reclaim-text-string comment-string?))))
    

;; return values:
;;  (title? symbolic-file-type inconsistent-so-save-all? module-case? new-operation-symbol?
;;   command-verb-string? comment-string?)

(defun preflight-file-related-window-menu-choice (choice-symbol)
  (when (and system-is-running
	     (neq choice-symbol 'save-kb)
	     (neq choice-symbol 'write-g2-stats))
    (notify-user "You cannot do file commands other than Save KB or Write G2 Stats while running.")
    (return-from preflight-file-related-window-menu-choice nil))
  (case choice-symbol
    (load-kb
     #w"Load KB")
    (merge-kb
     #w"Merge KB")
    (connect-to-foreign-image
     (values #w"Connect to Foreign Image" 'foreign-image))
    (disconnect-from-foreign-image
     (values #w"Disconnect from Foreign Image" 'foreign-image))
    (load-attribute-file
     (values #w"Load Attribute file" 'attribute))
    (write-g2-stats
     (values #w"Write G2 Stats As" 'statistics))
    (save-kb
     (cond
       ((check-savability-of-kb-in-terms-of-modularity)
	;; An inconsistently-modularized KB!
	(notify-user
	  "Since this KB is not consistently modularized, you may ~
           only save the KB in a single file!")
	(let* ((comment-string
		(tformat-text-string
		  "WARNING: since this KB is not consistently ~
           	   modularized, you may only save the KB in a single file!  ~
                   See logbook messages for further information."))
	       (command-verb-string
		(tformat-text-string
		  "{Comment: ~a}~%~%Save current KB as" comment-string)))
	  (values #w"Save current KB as" nil
		  t			; inconsistent-so-save-all?
		  nil			; module-case?
		  nil			; new-operation-symbol?
		  command-verb-string	; command-verb-string?
		  comment-string)))
       ((get-slot-value module-information 'top-level-kb-module?)
	;; A consistently modularized KB.
	(let* ((write-symbols-parsably? t)
	       (module (get-slot-value module-information 'top-level-kb-module?))
	       (command-verb-string
		 (tformat-text-string "Save module ~A as" module))
	       (symbolic-file-type
		 (when (and (get-slot-value-if-any
			      (get-saving-parameters module)
			      'save-in-clear-text-by-default)
			    (not (module-contains-text-stripped-frames-p module)))
		   'xml)))
	  (values #w"Save Module" symbolic-file-type
		  nil			; inconsistent-so-save-all?
		  t			; module-case?
		  'save-module		; new-operation-symbol?
		  command-verb-string)))
       (t
	;; Good, old-fashioned KB save:
	#w"Save current KB as")))
    (source-code-control-update-file
     (values #w"Source code control update" 'source-control))
    (source-code-control-edit-file
     (values #w"Source code control edit" 'source-control))
    (source-code-control-unedit-file
     (values #w"Source code control unedit" 'source-control))
    (source-code-control-commit-file
     (values #w"Source code control commit" 'source-control))
    (source-code-control-revert-file
     (values #w"Source code control revert" 'source-control))
    (t
     (dwarn "Unknown file command: ~s" choice-symbol))))

;; From old SoftServe project, not used any more (from OS-ERROR).
(defun-for-system-procedure g2-abort-callback-userdefine (callback-user-spec)
  )


;;;; Native File Dialog


(def-concept native-file-dialog)

;;; These `dialog-buttons' are lists of (name type label . data), where type can be
;;;   TEXT       which creates static text box.
;;;   CHECKBOX   which creates a checkbox. Data is (checked string),
;;;              where checked, T or NIL, initially checks the item, and string is
;;;              an optional string which is set into the filename edit box of the
;;;              file dialog when this box is checked. Also, it makes checking this
;;;              box disable all the other controls in the subdialog.
;;;   COMBOBOX   which creates a combo box. Data is a list of symbols whose print names
;;;              are the choices in the box.

;;; The buttons are laid out below the main file dialog, from top to bottom, one
;;; per line, except for checkboxes which are laid out two per line.

;;; Once the user makes a selection from the fiale dialog, we get back a
;;; `file-dialog' event with an event-plist containing properties corresponding
;;; to the names given to the controls above.  The value of a property is T or
;;; NIL for a checkbox, and the selected symbol for a combo box.

(defparameter native-load-kb-file-dialog-buttons
  '((starting-afterwards checkbox #w"start afterwards")
    (not-starting-afterwards checkbox #w"never start afterwards")
    (warmbooting-afterwards checkbox #w"warmboot afterwards")
    (warmbooting-afterwards-with-catch-up checkbox #w"warmboot afterwards with catch-up feature")
    (merge-kb checkbox #w"merge-in this KB" merge-kb)
    (merge-kb-and-install-system-tables checkbox #w"merge-in this KB and install its system tables")
    (update-before-loading checkbox #w"bring formats up-to-date")
    (automatically-resolving-conflicts checkbox #w"automatically resolve conflicts" t)))
;; Cf make-load-command-items-and-add-to-workspace

(defparameter native-save-module-file-dialog-buttons
  '((including-all-required-modules checkbox #w"including all required modules")
    (save-only-changed-modules checkbox #w"save only changed modules")
    (save-all-to-one-file checkbox #w"save all modules to one file" nil special-string)))


;;; The function `compute-pathname-filter-for-file-type' returns a new
;;; gensym-list of pathname filter specs for a native file dialog. Only the
;;; spine of the list is newly consed.

(defun compute-pathname-filter-for-file-type (symbolic-file-type? &optional use-xml-mask?)
  (nconc
    (case symbolic-file-type?
      (xml
       (gensym-list '(#w"XML Files (*.xml)" #w"*.xml")))
      (foreign-image
       (gensym-list '(#w"Foreign Images (*.fgn)" #w"*.fgn")))
      ((attribute statistics)
       (gensym-list '(#w"Text Files (*.text; *.txt)" #w"*.text" #w"*.txt")))
      (log
       (gensym-list '(#w"Log Files (*.log)" #w"*.log")))
      (t
       (nconc
         (gensym-list
           '(#w"Knowledge Bases (*.kb; *.kl)" #w"*.kb" #w"*.kl"))
         (when use-xml-mask?
           (gensym-list '(#w"XML Knowledge Bases (*.xml)" #w"*.xml"))))))
    (gensym-list '(#w"All Files (*.*)" #w"*.*"))))

;; Cf make-default-file-type


;;; The function `compute-list-of-modules-putting-top-in-front' returns a newly
;;; consed gensym list of the names of all loaded modules, as symbols, ensuring
;;; that the top-level module is at the head of the list.
;; Maybe someday this should order the list even more intelligently.
;; -dkuznick 7/24/03  

(defun compute-list-of-modules-putting-top-in-front ()
  (let ((list-of-modules-in-random-order-sans-top
	  (loop for (module-information-table) in modules-and-system-tables-a-list
		as module? = (top-level-kb-module? module-information-table)
		when (and module?
			  (neq module-information-table module-information))
		  collect module? using gensym-cons))
	(top-level-module-name? (top-level-kb-module? module-information)))
    (if top-level-module-name?
	(gensym-cons top-level-module-name?
		     list-of-modules-in-random-order-sans-top)
	list-of-modules-in-random-order-sans-top)))


;;; The function `interesting-directories' returns a newly consed gensym-list of
;;; directories (as strings) which may be of interest to a user of the native
;;; file dialog.

(defun interesting-directories ()
  (let* ((buflen 1024)
	 (buffer (obtain-text-string buflen))
	 (count (c-get-places-bar buffer buflen)))
    (prog1
	(if (>f count 0)
	    (double-nul-string-to-list buffer)
	    (default-interesting-directories))
      (reclaim-text-string buffer))))

;;; The function `default-interesting-directories' returns a gensym-list of the
;;; user's homedir, the KB dir, and the dirs in the module search path, with
;;; duplicates removed, as the default set of interesting directories. This is
;;; what's used for Unix G2's.

(defun default-interesting-directories ()
  (let* ((kb-gp? (current-kb-directory?))
	 (home? (get-gensym-environment-variable #w"HOME"))
	 (homedir? (if home? (coerce-to-directory-string home?)))
	 (modules (loop for dir in (module-search-path server-parameters)
			collect (copy-text-string dir) using gensym-cons))
	 (dirs (nconc
		 (if homedir? (gensym-list homedir?))
		 (if kb-gp? (gensym-list (gensym-namestring kb-gp?)))
		 modules))
	 (directories
	   (loop for dir in dirs
		 unless (member dir result :test #'string-equalw)
		   collect (copy-text-string dir) into result using gensym-cons
		 finally (return result))))
    (reclaim-gensym-tree-with-text-strings dirs)
    (when kb-gp?
      (reclaim-gensym-pathname kb-gp?))
    (when home?
      (reclaim-text-string home?))
    directories))

;;; The gensym-c-function `c-get-places-bar' returns a platform-dependent list
;;; of interesting directories, in the form of a double-NUL-terminated
;;; string. Value is the number of pathnames placed into the buffer.

(def-gensym-c-function c-get-places-bar
    (:fixnum-int "g2ext_get_places_bar")
  ((:wide-string buffer)
   (:fixnum-int buflen)))


(defun coerce-to-directory-string (pathname)
  (let ((gensym-pathname
	  (or (gensym-file-as-directory pathname)
	      (gensym-parse-namestring pathname))))
    (prog1
	(gensym-namestring gensym-pathname)
      (reclaim-gensym-pathname gensym-pathname))))

;;; The function `post-file-dialog' sends the appropriate ICP message to post
;;; the native file dialog on window. It also computes the plist to send with
;;; extended dialog message as needed.

(defun post-file-dialog (gensym-window handle operation flags caption initial-pathname
				       default-extension filter buttons &optional places)
  (with-icp-window (gensym-window)
    (cond ((window-supports-file-dialog-ex gensym-window)
	   (let* ((server-dialog-p (/=f (logandf flags 2) 0))
		  (dirs (when server-dialog-p
			  (or (copy-gensym-tree-with-text-strings places)
			      (interesting-directories))))
		  (places-buflen 1280)
		  (places-values (obtain-text-string places-buflen))
		  (drives-buflen 300)
		  (drives-values (obtain-text-string drives-buflen))
		  (plist nil))
	     (if (windows-platform-p)
		 (progn
		   (c-get-system-drives-list drives-values drives-buflen)
		   (c-get-system-special-folders places-values places-buflen)
		   (setq plist
			 (gensym-list 'places (double-nul-string-to-list places-values)
				      'drives (double-nul-string-to-list drives-values))))
	       ;; other unix platforms
	       (setq plist
		     (when dirs
			   (gensym-list 'places (loop for dir in dirs
						      collect (coerce-to-directory-string dir)
						      using gensym-cons)))))
	     (send-icp-file-dialog-ex
	       gensym-window handle operation flags
	       caption initial-pathname default-extension filter buttons plist)
	     (reclaim-gensym-tree-with-text-strings dirs)
	     (reclaim-gensym-tree-with-text-strings plist)))
	  (t
	   (send-icp-file-dialog
	     gensym-window handle operation flags
	     caption initial-pathname default-extension filter buttons)))))


;;; The function `post-native-file-dialog' posts a native file dialog on window,
;;; for the purpose of executing the G2 file-command, operation.  Eventually
;;; calls handle-file-dialog-message, when response comes back.

;;; The dialog *always* browses the server's file system. If the window is
;;; incapable of that, then this function must not be called!

(defun post-native-file-dialog (gensym-window operation title
					      symbolic-file-type?
					      inconsistent-so-save-all?
					      module-case? comment?)
  (let* ((gensym-pathname (get-pathname-for-file-command
			    symbolic-file-type? inconsistent-so-save-all?
			    module-case? t))
	 (pathname (gensym-namestring gensym-pathname))
	 (use-xml-filter? (memq operation '(load-kb save-kb merge-kb save-module)))
	 (filter (compute-pathname-filter-for-file-type symbolic-file-type? use-xml-filter?))
	 (basic-buttons (copy-gensym-tree-with-text-strings
			  (case operation
			    ((load-kb merge-kb) native-load-kb-file-dialog-buttons)
			    (save-module native-save-module-file-dialog-buttons))))
	 (all-filename? (and module-case?
			     (get-pathname-for-file-command symbolic-file-type? t nil t)))
	 (buttons (nconc (when comment?
			   (gensym-list (gensym-list 'comment 'text (copy-text-string comment?))))
			 (when module-case?
			   (gensym-list (nconc (gensym-list 'module 'combobox
							    (copy-wide-string #w"Module:"))
					       (compute-list-of-modules-putting-top-in-front))))
			 (if all-filename?
			     (nsubst (os-pathname-nondirectory all-filename?
							       g2-operating-system)
				     'special-string
				     basic-buttons)
			     basic-buttons)))
	 (savep (memq operation '(save-kb save-module write-attribute-file write-g2-stats)))
	 (flags (logiorf (if savep 1 0)	; Flags: Bit0=Save/Open, Bit1:Server/client
			 (if (server-and-client-share-file-system-p gensym-window) 0 2)
			 (ashf (encode-pathname-os g2-operating-system) 2))))

    (post-file-dialog gensym-window
		      123		; Dialog handle (ignored)
		      operation		; Operation (symbol)
		      flags
		      title		; title
		      pathname		; default-pathname
		      (or (gensym-pathname-type gensym-pathname) #w"") ; default-extension
		      filter		; Filter
                      buttons)          ; Buttons
    (when all-filename?
      (reclaim-gensym-pathname all-filename?))
    (reclaim-gensym-tree-with-text-strings buttons)
    (reclaim-gensym-list filter)
    (reclaim-text-string pathname)
    (reclaim-gensym-pathname gensym-pathname)))


;;; The function `native-handle-file-related-window-menu-choice' posts a native
;;; file dialog on the current-window which always browses the server's file
;;; system.

(defun native-handle-file-related-window-menu-choice (choice-symbol)
  (multiple-value-bind (title? symbolic-file-type?
			       inconsistent-so-save-all? module-case?
			       new-operation-symbol? command-verb-string?
			       comment-string?)
      (preflight-file-related-window-menu-choice choice-symbol)
    (when title?
      (post-native-file-dialog current-workstation-window
			       (or new-operation-symbol? choice-symbol)
			       title?
			       symbolic-file-type?
			       inconsistent-so-save-all?
			       module-case?
			       comment-string?))
    (when command-verb-string?
      (reclaim-text-string command-verb-string?))
    (when comment-string?
      (reclaim-text-string comment-string?))))






;;; Put-up-table-of-network-info ... 

(defun put-up-table-of-network-info ()  
  (multiple-value-bind (host-name port-list local-host-aliases?)
      (get-raw-network-info)
    (let* ((workspace
	     (make-workspace
	       'temporary-workspace nil
	       (make-or-reformat-table
		 (nconc
		   (unless new-g2-classic-ui-p
		     (slot-value-list
		       (slot-value-list
			 nil
			 (make-text-cell
			   (slot-value-list (copy-text-string host-name))
			   'class-format))))

		   (loop for (type-of-network address secure-p) in port-list
			 collect 
			 (slot-value-list
			   (make-text-cell
			     (slot-value-list (tformat-text-string "~a" type-of-network))
			     'default-text-cell-format)
			   (make-text-cell
			     (slot-value-list
			       (twith-output-to-text-string
				 (tformat "~a~a" address (secure-icp-string :network-type type-of-network :secure-p secure-p))))
			     'default-text-cell-format))
			   using slot-value-cons)

		   (if local-host-aliases?
		       (slot-value-list
			 (slot-value-list
			   (make-text-cell
			     (slot-value-list
			       (copy-constant-wide-string #w"Aliases"))
			     'default-text-cell-format)
			   (make-text-cell
			     (slot-value-list
			       (twith-output-to-text-string
				 (write-symbol-list local-host-aliases? ",")))
			     'default-text-cell-format)))))
		 'default-table-format nil)
	       1)))
      (when new-g2-classic-ui-p
	(setf (stretch-new-image-planes-for-caption-p workspace) t)
	(setf (title-bar-caption-text workspace)
	      (twith-output-to-text (tformat "~a" host-name))))
      (reclaim-raw-network-info host-name port-list)
      (put-workspace-on-pane
	workspace current-workstation-detail-pane 'left 'top nil))))




;;; `Get-workspace' returns a workspace with the given name if there is one;
;;; if not, it returns a workspace with the given name as the value of its
;;; name-for-debugging slot if there is one; if not, it returns nil.

(defun get-workspace (name)
  (let ((found-workspace? nil))
    (loop for workspace being each class-instance of 'workspace
	  do
      (when (and (null found-workspace?)
		 (name-for-frame-p name workspace)
		 (or (not servicing-workstation?)      ; can this be true?!
		     (workspace-can-appear-on-workstation-p
		       workspace current-workstation)))
	(setq found-workspace? workspace)))
    found-workspace?))


;; Fixed to handle temporary (debugging) names if a real name that matches cannot
;; be found. (MHD 12/4/89)

;  (get-instance-with-name-that-satisfies-predicate-if-any
;    'workspace name
;    #'(lambda (workspace)
;	(null (parent-of-subworkspace? workspace)))))

;; Consider changing the name to get-workspace-with-name-if-any!

;; Move this!!




(defun neatly-stack-image-planes-in-window (gensym-window)
  (let* ((pane
	   (detail-pane gensym-window))
	 (top-plane
	   (car (stack-of-image-planes pane))))
    (neatly-stack-image-planes-in-pane
      pane 'left 'top
      (+r (left-edge-of-pane-in-window top-plane) 25)
      (+r (top-edge-of-pane-in-window top-plane) 25)
      25 25)
    ;; Alternative/example:
    ;;   This stacks workspaces down from the top center, logbook pages
    ;;     down from the right, and other workspaces down from the
    ;;     left
;    (neatly-stack-image-planes-in-pane
;      pane nil 'top
;      (halfr
;	(+r (left-edge-of-pane-in-window top-plane)
;	    (right-edge-of-pane-in-window top-plane)))
;      (+r (top-edge-of-pane-in-window top-plane) 25)
;      0 50 'kb-workspace)
;    (neatly-stack-image-planes-in-pane
;      pane 'right 'top
;      (-r (right-edge-of-pane-in-window top-plane) 25)
;      (+r (top-edge-of-pane-in-window top-plane) 25)
;      -50 25 'logbook-page)
;    (neatly-stack-image-planes-in-pane
;      pane 'left 'top
;      (+r (left-edge-of-pane-in-window top-plane) 25)
;      (+r (top-edge-of-pane-in-window top-plane) 25)
;      25 25 nil
;      #'(lambda (image-plane workspace)
;	  image-plane
;	  (and (not (frame-of-class-p workspace 'kb-workspace))
;	       (not (frame-of-class-p workspace 'logbook-page)))))
    ))

;; Consider having this, as a special case, home logbooks to their own
;; home positions.




;;; `Neatly-stack-image-planes-in-pane' stacks image planes in pane beginning
;;; at (x-in-window, y-in-window) and continuing delta-x-in-window units to
;;; the right and delta-y-in-window units below that for each successive
;;; image plane in the stack.  If workspace-class? is specified, only
;;; workspaces of that class are affected.  If predicate? is specified, it
;;; is funcalled with the arguments (image-plane workspace), for each workspace
;;; and image plane in the stack that would be otherwise be affected; it should
;;; return true if the image plane should be affected, and nil otherwise.

(defun neatly-stack-image-planes-in-pane
       (pane left-or-right? top-or-bottom?
	x-in-window y-in-window delta-x-in-window delta-y-in-window
	&optional workspace-class? predicate?)
  (loop with number-of-images
	  = (loop for image-plane in (stack-of-image-planes pane)
		  as workspace? = (workspace-on-image-plane? image-plane)
		  count (and workspace?
			     (or (null workspace-class?)
				 (frame-of-class-p
				   workspace? workspace-class?))
			     (or (null predicate?)
				 (funcall
				   predicate? image-plane workspace?))))
	for image-plane in (stack-of-image-planes pane)
	as workspace? = (workspace-on-image-plane? image-plane)
	when (and workspace?
		  (or (null workspace-class?)
		      (frame-of-class-p
			workspace? workspace-class?))
		  (or (null predicate?)
		      (funcall
			predicate? image-plane workspace?)))
	  do (move-image-plane
	       image-plane 
	       (-r (+r x-in-window
		       (*r (-r number-of-images 1) delta-x-in-window))
		   (case left-or-right?
		     (left
		      (left-edge-of-image-in-window image-plane))
		     (right
		      (right-edge-of-image-in-window image-plane))
		     (t
		      (halfr
			(+r (left-edge-of-image-in-window image-plane)
			    (right-edge-of-image-in-window image-plane))))))
	       (-r (+r y-in-window
		       (*r (-r number-of-images 1) delta-y-in-window))
		   (case top-or-bottom?
		     (top
		      (top-edge-of-image-in-window image-plane))
		     (bottom
		      (bottom-edge-of-image-in-window image-plane))
		     (t
		      (halfr
			(+r (top-edge-of-image-in-window image-plane)
			    (bottom-edge-of-image-in-window image-plane)))))))
	     (decff number-of-images)))

;; Add the optional arg stack-position?.

;; Move this to a better place, like PANES!  

;; Notice that this does not require the image-plane to be visible.



;; making this a symbol now would capitalize  "a" and "to", so I've defined a
;;   menu-string below. (MHD 6/18/92)
(def-menu-string choose-a-module-to-delete "Choose A Module To Delete")


(defun compute-module-deletion-choices ()
  (loop for (module-information-table) in modules-and-system-tables-a-list
	unless (or ;; obsolete restriction:  (MHD 8/12/94)
		   ;; SHOULD BE OBSOLETE -- NEEDS WORK FOR 4.0! (MHD 9/13/94)
		 #+obsolete
		 (system-table-installed-p module-information-table)
		 (null 
		   (get-slot-value
		     module-information-table 'top-level-kb-module?)))
	  collect (get-slot-value
		    module-information-table 'top-level-kb-module?)
	    using slot-value-cons))




(def-menu-string lift-to-top "Lift to Top")
(def-menu-string drop-to-bottom "Drop to Bottom")
(def-menu-string kb-workspace "KB Workspace")

;;; Delete-workspace-for-user ... 

;;; Delete-block-for-user ...

;;; may put up a dialog box asking for confirmation in the
;;; current workstation detail window.  Last-mouse-x-in-window? and last-mouse-y-in-
;;; window? should be supplied if known in order for the dialog to be displayed
;;; in the standard way, i.e. near the mouse.

(defun delete-workspace-for-user
    (workspace &optional last-mouse-x-in-window? last-mouse-y-in-window?)
  (if (or (temporary-workspace-p workspace)	; (non-kb-workspace-p workspace) instead?
	  (frame-of-class-p			;   => no confirmation for logbook pages,
	    workspace				;   message boards, etc.
	    'category-instance-menu-workspace)
	  (workspace-subblocks-may-be-deleted-without-prompting-p workspace))
      (delete-frame workspace)
      (loop with number-of-subworkspaces = 0	; also count "subsubworkspaces"?
	    as subblock being each subblock of workspace
	    when (if (entity-p subblock) (subworkspaces subblock))
	      do (incff number-of-subworkspaces (length (subworkspaces subblock)))
	    finally
	      (enter-dialog
		(tformat-text-string
		  (cond
		    ((=f number-of-subworkspaces 0)
		     "Delete this ~(~a~)?")
		    ((=f number-of-subworkspaces 1)
		     "Delete this ~(~a~), with its one subworkspace?")
		    (t "Delete this ~(~a~), with its ~D subworkspaces?"))
		  (class workspace)
		  number-of-subworkspaces)
		nil nil
		'delete-frame-after-checking-serial-number
		(slot-value-list workspace (copy-frame-serial-number (current-frame-serial-number)))
		nil nil
		last-mouse-x-in-window? last-mouse-y-in-window?))))

;; Consider using names for workspaces in addition to or instead of the class name
;; when requesting confirmation!

;; Consider highlighting the block being considered for deletion when requesting
;; confirmation.  (Or should enter-dialog somehow manage this?)




;;; The function `block-may-be-deleted-without-prompting' is true if G2's UI
;;; policy is to allow block to be deleted without prompting.  This is true if
;;; block is a name-box or old-ghost instance or just a non-display table
;;; instance.

(defun block-may-be-deleted-without-prompting-p (block)
  (or (and (table-p block)		; Do not confirm if the choice is just
	   (not (display-table-p block)))
      (frame-of-class-p block 'name-box)	;to "hide" something -- 
					; have a name-box-p predicate!
      (frame-of-class-p block 'ole-ghost)))

;; This code used to be be embedded in delete-block-for-user. We've broken it
;; out so it can also be called from
;; workspace-subblocks-may-be-deleted-without-prompting-p, below. (MHD 5/12/03)




;;; The function `workspace-subblocks-may-be-deleted-without-prompting-p' is
;;; true if G2's UI policy is to allow block to be deleted without prompting.
;;; At present, this is true if workspace either has no subblocks or if all of
;;; its subblocks are block-may-be-deleted-without-prompting-p.

(defun workspace-subblocks-may-be-deleted-without-prompting-p (workspace)
  (loop for block being each subblock of workspace
	always (block-may-be-deleted-without-prompting-p block)))

;; This replaces the code that used to be embedded in delete-workspace-for-user,
;; which used to check if workspace just had no subblocks. Previously we
;; considered having only a workspace name box no differently.  We're changing
;; that policy per suggestion HQ-3210235 "G2 prompts to delete ws w/nothing but
;; name-box". (5/12/03)





;;; The function `item-deletion-causes-workspace-deletion-p' examines the item
;;; and its possible class hierarchy to determine whether deleting the item
;;; specified by a user will delete any workspaces.  It returns the subworkspaces
;;; of there are any; otherwise it returns nil.

(defun item-deletion-causes-workspace-deletion-p (item)
  (or (subworkspaces item)
      (and (class-definition-p item)
	   (let ((class-name? (name-of-defined-class item)))
	     (when (classp class-name?)
	       (loop for subclass being each subclass of class-name?
		 thereis
		 (or (subworkspaces (class-definition subclass))
		     (unless (or (eq (class item) 'message-definition)
				 (not (subclassp class-name? 'entity)))
		       (loop for instance being each strict-class-instance
			     of subclass
			     thereis
			     (subworkspaces instance))))))))))





;;; `Delete-block-for-user' ...

(defun delete-block-for-user
    (block &optional last-mouse-x-in-window? last-mouse-y-in-window?)
  (let ((block-to-delete
	  (let ((workspace? (get-workspace-if-any block))
		(superblock? (superblock? block)))
	    (if (and workspace?
		     (frame-of-class-p workspace? 'non-kb-workspace)
		     superblock?
		     (or (has-only-one-subblock-p superblock?)
			 (workspace-is-for-virtual-attribute-table-p superblock?)))
		;; If only block (not counting timestamp and refresh button in
		;; virtual-attribute table case) on non-KB workspace, this
		;; deletes the workspace.
		workspace?
		block))))
    (if (block-may-be-deleted-without-prompting-p block)
	(delete-frame block-to-delete)
	(enter-dialog
	  (dialog-message-string-for-delete-block block)
	  nil nil
	  'delete-frame-after-checking-serial-number
	  (slot-value-list block-to-delete (copy-frame-serial-number (current-frame-serial-number)))
	  nil nil
	  last-mouse-x-in-window? last-mouse-y-in-window?))))


(defun dialog-message-string-for-delete-block (block)
  (twith-output-to-text-string
    (when (destabilizing-item-deletion-p block)	; destabilizing deletion
      (tformat "This action would cause the deletion of stable item(s).  "))
    (when (frame-of-class-p block 'g2gl-process) ; for G2GL/BPEL (MHD 2/8/05)
      (let ((count (count-instances-of-g2gl-process block)))
	(unless (=f count 0)
	  (tformat
	    "This action would cause the deletion of ~d process instance~a.  "
	    count (if (=f count 1) "" "s")))))
    (let* ((workspace-deletion?
	     (and (entity-p block)
		  (item-deletion-causes-workspace-deletion-p block))))
      (cond ((frame-of-class-p block 'class-definition)
	     (let ((class-name? (name-of-defined-class block)))
	       (cond ((classp class-name?)
		      (tformat "Delete this class")
		      (if (instantiated-class-p class-name?)
			  (if workspace-deletion?
			      (tformat
				", its instances, and its associated subworkspace(s)")
			      (tformat " and its instances"))
			  (if workspace-deletion?
			      (tformat
				" and its subworkspace(s)")))
		      (tformat "?"))
		     (t
		      (tformat "Delete this class-definition")
		      (if workspace-deletion?
			  (tformat " and its subworkspace(s)"))
		      (tformat "?")))))
	    (t
	     (tformat "Delete this ~(~a~)" (class block))
	     (if (and (entity-p block) (subworkspaces block))
		 (tformat " and its subworkspace(s)"))
	     (tformat "?"))))))




;;; Problem-item-in-limbo-p ...

(defun problem-item-in-limbo-p (block)
  (and (permanent-block-p block)
       (not (frame-of-class-p block 'kb-workspace))
       (null (superior-frame  block))
       
       (not (frame-of-class-p block 'g2-window))
       (not (frame-of-class-p block 'procedure-invocation))
       (not (frame-of-class-p block 'system-table))
       
       (or (not (and (frame-of-class-p block 'class-definition)
		     (class-definition-defines-user-editable-icon-class-p 
		       block)))
	   (let ((class-name? (name-of-defined-class block)))
	     (or (null class-name?)
		 (loop for connection-definition being
			   each class-instance of 'connection-definition
		       never (eq class-name?
				 (junction-block-class-for-connection
				   connection-definition))))))))



;;; Comments on the `table-menu'

;; Since we added the final T arg (find-nearest-cell? = true) to the call to
;; pick-cell-from-table, we can dispense with the "poor" hack of returning the
;; first text cell if the click was not properly inside of a cell.  So we are
;; commenting out this case (which should basically never happen now with the
;; new arg.)  The old way, when you'd click at the bottom of an attribute table
;; (on the table's border), and you would get the menu for the table's class
;; slot (table-header attribute)!  (MHD 7/9/92)
		

;; NEW: now if you click on an attribute table (or close relatives attribute
;; displays and short representation tables), you should always get the menu
;; for a text cell that represents a slot (except in the rare case of a "no
;; values to display" table, representing no frame).

;; The following searches for such a cell if you've clicked on a cell in an
;; attribute table or the like that does not represent a slot in a frame.  It
;; makes certain assumptions about their format.  (MHD 7/2/92)
      


;;; Comments on `click-to-edit'

;; Also, this happened to only be called on text boxes, tables, and procedures
;; before.  This then hand-filtered out procedures.  The real restriction is
;; that it should filter out anything that's not a table or text box.

;; Added new slot-component-name? and slot-component-indicator? args. (MHD
;; 2/1/94) Made args past block optional, and dropped some.  Only two elements
;; are now needed in the edit-information-for-current-selection?  structure now.
;; (MHD 2/1/94)

;; It is not great to have both a menu and click to edit for a borderless text
;; box.  Consider getting rid of the free text box menu, which implies that
;; certain operations on free text boxes need to be done as area operations.

;; Consider having a click on a label box mean edit.  If this were done, moving
;; would not be possible by menu choice, deletion would only be doable by
;; deleting the entire text, and changing the size of the text would have to be
;; done in some special way, say.

;; Consider having a click on a name box mean edit.  If this were done, moving
;; would not be possible by menu choice, and hiding a name would be either not
;; be possible or would require a menu choice on the superblock.  Also, changing
;; the size of a name would have to be done in some special way.



(def-menu-string rotate-reflect rotate/reflect)



;;; The function `include-yes-no-menu-choice-p' currently returns nil when
;;; the frame is a relation, the subtable slot is relation-is-symmetric, and
;;; either the relation has an inverse-of-relation value or the type-of-relation
;;; would conflict with a symmetric relation, and also when the slot is declared
;;; as not user editable, that is, is an informational slot only.

(defun include-yes-no-menu-choice-p (text-cell)
  (multiple-value-bind (frame? slot-name?)
      (get-slot-represented-by-text-cell-if-any text-cell)
    (cond ((and (framep frame?)
		(symbolp slot-name?)
		(eq (class frame?) 'relation)
		(eq slot-name? 'relation-is-symmetric))
	   (if (or (inverse-of-relation frame?)
		   (not (valid-symmetric-relation-type (type-of-relation frame?))))
	       nil
	       t))
	  ((and (framep frame?) slot-name? (symbolp slot-name?)
		(not (user-writable-slot-of-instance-p frame? slot-name? nil)))
	   nil)
	  (t t))))


;;; `grammar-categories-getting-yes-no-feature' is a list of grammar-categories
;;; whose slots are to edited by "change to yes" and "change to no".  Defvar in
;;; file RELATIONS.

(pushnew 'yes-or-no grammar-categories-getting-yes-no-feature)
;(pushnew 'yes-or-no? grammar-categories-getting-yes-no-feature)
;; Expunged this category. ddm 12/18/96   See note in Tables near code for
;; make-text-for-cell-identifying-attribute-in-table.



; OBSOLETE: -- See note above with this datestamp: (MHD 6/2/92)
; (def-menu-string table-from-short-representation "table")

(def-menu-string change-to-yes "change to \"yes\"")
(def-menu-string change-to-no "change to \"no\"")



(setf (type-of-syntactic-anomaly '|180|) 'numeric)

(def-menu-string left-right-reflection "left-right reflection")
(def-menu-string up-down-reflection "up-down reflection")


;;; `Enter-text-editor-on-text-cell' ... click-to-edit-line-index? and
;;; click-to-edit-cursor-index?  may be supplied if it has already been decided
;;; where the cursor should be, i.e., for the click-to-edit case.

(defun enter-text-editor-on-text-cell
    (table text-cell image-plane x-in-window y-in-window
	   &optional click-to-edit-line-index?
	             click-to-edit-cursor-index?
		     intercepted-text-cell-text?)
  ;; It would be handy and more efficient to have a multiple-lookup-permitted-p hinkey.
  (multiple-value-bind
      (frame? slot-name? defining-class?
	      slot-component-name? slot-component-indicator? virtual-attribute? exported-format?)
      (get-slot-represented-by-text-cell-if-any text-cell)
    (when frame?			; checking necessary?
      (let ((edit-in-place?
	      (not (non-menu-choice-permitted-p 'full-editor frame?)))
	    (blank-for-type-in?
	      (not (non-menu-choice-permitted-p 'do-not-clear-text-for-edit-in-place frame?)))
	    (do-not-have-edit-option-buttons?
		(not (non-menu-choice-permitted-p 'option-buttons-for-edit-in-place frame?)))
	    (do-not-have-edit-menus?
		(not (non-menu-choice-permitted-p 'menus-for-edit-in-place frame?))))

	(multiple-value-bind
	    (left-edge-of-area top-edge-of-area
	     right-edge-of-area bottom-edge-of-area)
	    (get-table-cell-edges table text-cell)

	  (multiple-value-bind (cursor-line-index? cursor-character-index?)
	    (find-position-in-text-given-image-plane
	      table nil text-cell left-edge-of-area top-edge-of-area
	      nil
	      image-plane x-in-window y-in-window)
	    (cond
	      ((not edit-in-place?)
	       (enter-editing-context
		 frame?
		 (make-slot-name-denotation slot-name? defining-class?)
		 (if intercepted-text-cell-text?
		     (add-intercepted-token-to-text
		       intercepted-text-cell-text?)
		     (get-text-to-edit-from-text-cell text-cell))
		 nil nil nil
		 (unless blank-for-type-in?
		   click-to-edit-line-index?)
		 (unless blank-for-type-in?
		    click-to-edit-cursor-index?)
		 nil nil nil
		 nil nil nil nil nil nil nil nil
		 slot-component-name? slot-component-indicator?
		 table virtual-attribute? exported-format?))
	      (t
	       (enter-editing-context
		 frame?
		 (make-slot-name-denotation slot-name? defining-class?)
		 (if intercepted-text-cell-text?
		     (add-intercepted-token-to-text
		       intercepted-text-cell-text?)
		     (if blank-for-type-in?
			 (make-empty-text)
			 (get-text-to-edit-from-text-cell text-cell)))
		 nil nil nil
		 (unless blank-for-type-in?
		   cursor-line-index?)
		 (unless blank-for-type-in?
		   cursor-character-index?)
		 image-plane
		 table
		 left-edge-of-area top-edge-of-area
		 right-edge-of-area bottom-edge-of-area
		 nil nil nil
		 do-not-have-edit-option-buttons? do-not-have-edit-menus?
		 slot-component-name? slot-component-indicator?
		 table virtual-attribute? exported-format?)))))))))



;; Def-menu-action-handler, n'est pas?


;; MHD's notes (mostly from around spring '91) on alternatives for
;; clone, transfer, move, create, etc.:
;;
;; ;; if you wanted to clone or create-instance to work more like move,
;; ;; this would have to first add the new block to workspace, then enter
;; ;; dragging context just like a move.
;;
;; ;; NEEDS WORK:
;; ;; 
;; ;;   (1) People use clone with "palettes", and simply cannot get
;; ;;   used to duplicating the items on these and then transferring
;; ;;   them.  Plus, duplicating on the pallette might enlarge the
;; ;;   workspace, which looks bad, too.
;; ;;
;; ;;   (1.5) As for create-instance, similarly, there tend to be
;; ;;   quite a few workspaces with just just definitions on them,
;; ;;   and people are pretty sensitive about them, and they would
;; ;;   tend to be disconcerted to change the workspace in any way
;; ;;   by creating an instance on it, whereas they don't mind new
;; ;;   instances flying OFF of their definitions.
;; ;;
;; ;; (It's interesting that write-protecting a disk would prevent
;; ;; you from duplicating a file on that disk under the Mac's UI;
;; ;; if we ever had restrictions on adding items to a workspace,
;; ;; and we had a mac-like duplicate feature, we would have the
;; ;; same dilemma in G2, where restricting adding items to a
;; ;; workspace would disable the DUPLICATE functionality.)
;; ;;
;; ;;   (2) People clone messages on message boards and logbooks
;; ;;   and transfer them to KB workpaces.  The way this works, you just
;; ;;   get a duplicate of your message on your message board and
;; ;;   then have to transfer the message.  That all violates
;; ;;   constraints on message boards and logbooks, and looks pretty
;; ;;   embarassing, too.
;; ;;
;; ;;   (MHD 4/5/91)
;; ;;
;; ;;

;; ;; warping the cursor seems good for small things or things at small scales
;; ;; and when there is little or no overlap between old and new, but seems
;; ;; poor for other cases, particularly for cloning statements.  Experiment
;; ;; with this.

;; ;; Note that on a Macintosh (and maybe others), after creating (or duplicating)
;; ;; you would select the new thing.  That visual indication of what got cloned
;; ;; would partially make up for not moving the mouse on top of the new thing, if
;; ;; we were to do that.
(progn)



;;; Get-text-to-edit-from-text-cell is a subfunction of
;;; enter-text-editor-on-text-cell, used to copy the text of a text cell.
;;;
;;; Normally this just copies and returns the text of the cell.
;;;
;;; However, in certain cases, it may provide a modified copy of the text.  At
;;; present, modifications are made only to handle the display-format text cell
;;; property, as follows.
;;;
;;; At present, this just handles the FREE-TEXT value for the
;;; display-format property.  If the following conditions are met:
;;;
;;;  (a) cell represents a slot;
;;;  (b) has FREE-TEXT as its display format;
;;;  (c) the slot value is a text string;
;;;  (d) the cell does not represent a virtual attribute;
;;;  (e) the cell is not in "export format"; 
;;;  (f) the cell is not in text-summarized form (trend charts only); and
;;;  (g) not a slot component
;;;
;;; then this assumes that the text of the cell has been formatted as free text,
;;; and that it should reformat it as a readable text string, i.e., with
;;; surrounding double quotes ("") and quoting @'s as necessary.  Note that this
;;; _can_ handle slot component values (the kind used by subtabls of trend
;;; charts).

(defun get-text-to-edit-from-text-cell (text-cell)
  (multiple-value-bind (frame? slot-name defining-class?
			       slot-component-name? slot-component-indicator?
			       virtual-attribute-p
			       exported-format-p text-summarized-p
			       display-format?)
      (get-slot-represented-by-text-cell-if-any text-cell)
    (let ((text-cell-text (text? text-cell)))
      (or (if (and display-format?
		   frame?
		   (not virtual-attribute-p)
		   (not exported-format-p)
		   (not text-summarized-p)
		   (null slot-component-name?)
		   (null slot-component-indicator?))
	      ;; We don't want to do this. This gives a text corresponding
	      ;; to the display format.
;	      (let ((slot-value
;		      (if slot-component-name?
;			  (get-slot-component-value
;			    frame? slot-name defining-class?
;			    slot-component-name? slot-component-indicator?)
;			  (get-slot-value frame? slot-name defining-class?))))
;		(let* ((slot-description
;			 (if (eq slot-name 'class)				    
;			     pseudo-class-slot-description
;			     (get-slot-description-of-frame
;			       slot-name frame? defining-class?)))
;		       (features
;			 (if (null slot-component-name?)
;			     (if slot-description
;				 (slot-features slot-description))
;			     (get-slot-component-features
;			       slot-name defining-class?
;			       slot-component-name?)))
;		       (type-feature
;			 (feature-assq 'type features)))
;		  (make-text-representation-for-slot-value-per-display-format
;		    frame? slot-value type-feature display-format?)))
	      ;; Instead, we want to give the text corresponding to the
	      ;; actual slot type.
	      (make-text-representation-for-slot-value
		frame? slot-name defining-class?))
	  (copy-text text-cell-text)))))

;; Bug: what about the cursor position! TBD! (MHD 1/11/02)





;;;; Choosing Class Names for Class Definitions


(defun do-addition-of-optional-subtable-from-menu
       (class image-plane x-in-window y-in-window frame slot-name class-qualifier?)
  image-plane					; no longer used -- was arg to put-up-...
  (let ((subtable 
	  (make-frame class)))			; make-entity instead of make-frame ever?
    (change-slot-value frame slot-name subtable class-qualifier?)
    (put-up-attributes-table
      subtable x-in-window y-in-window)))





;;; `Go-to-maybe-newly-created-subworkspace' ... if entity does not have a
;;; subworkspace already and user restrictions in the current workstation
;;; at entity's level in the KB hierarchy permit showing workspaces,
;;; then this creates a subworkspace for entity, shows it at the center of
;;; the current workstation detail pane, and returns the new subworkspace;
;;; otherwise, it just shows the subworkspace of entity and returns its
;;; subworkspace, provided that KB restrictions permit.

;;; If KB restrictions did not get in the way, this returns the subworkspace
;;; of entity; otherwise, nil.

(defun go-to-maybe-newly-created-subworkspace (entity workspace-class?)
  (cond
    ((workspaces-can-be-shown-at-this-kb-level-p	; KB restrictions permit
       (if (subworkspaces entity)
	   (car (subworkspaces entity))
	   entity)
       current-workstation)
     (goto-frame-instance
       (if (subworkspaces entity)		; do we have a workspace? 
	   (first (subworkspaces entity))	; YES: then just return it.
	   (let* ((inhibit-updating-module-related-frame-notes-for-all-workspaces?
		    t)			; adding a subworkspace cannot have
					;  any impact on modularity; suppress
					;  all frame notes activity around
					;  the incremental steps
		  (kb-workspace-class
		    (or workspace-class? 'kb-workspace))
		  (workspace
		    (make-new-top-level-kb-workspace
		      kb-workspace-class nil nil nil
		      (class-slot-description-value
			'kb-workspace-initial-width kb-workspace-class)
		      (class-slot-description-value
			'kb-workspace-initial-height kb-workspace-class)
		      (slot-init-form (slot-description-from-class
					kb-workspace-class
					'module-this-is-part-of?)))))
	     (add-subworkspace workspace entity)
	     ;; we used to name it at this point (in 1.11b)
	     (when (subworkspace-connection-posts-p entity)
	       (add-subworkspace-connection-posts workspace entity))
	     workspace)))
     (first (subworkspaces entity)))))

;;; Note: width and height were 600 and 450, respectively, prior to 2.0 Beta5.
;;; And they were different (700 and 500) when specified for new top-level
;;; workspaces (above).  [DWR and FEF said they never noticed the difference
;;; and would not miss its absence.]  (MHD 6/14/90)




;;;; Commands



(def-class (command text-box)
  (default-text-box-format-name statement-format)
  (box-translation-and-text nil (type command text)))


;;; `Execute-command' command is a method on all subclasses of command.  It
;;; implements the actual command.

(def-generic-method execute-command (command)
  )



;;; Make-command-frame ... makes and returns a new command frame.

(defun make-command-frame (command-class &optional initial-text-line?)
  (let ((command-frame (make-frame command-class)))
    (setf (text-box-format command-frame)
	  (get-or-make-format-frame
	    (default-text-box-format-name command-frame)))
    (setf (box-translation-and-text command-frame)
	  (slot-value-cons
	    no-value
	    (if initial-text-line?
		(convert-text-string-to-text initial-text-line?)
		(make-empty-text))))
    command-frame))


;;; Handle-command ...  If initial-text-line? is nil, an empty text will be used;
;;; otherwise, it should be an unshared text line (not ending with a space).

(defun handle-command (command-class initial-text-line?)
  (let ((command-frame (make-command-frame command-class)))
    (with-old-style-workstation-return-function
	('execute-command-on-return command-frame 'delete-frame)
      (enter-editing-context 
	command-frame 'box-translation-and-text
	(if initial-text-line?
	    (slot-value-list initial-text-line?)
	    (make-empty-text))))))

(defun handle-inspect-command	; New for Inspect! (MHD 6/12/90)
       (inspect-command
	 &optional cursor-line-index? cursor-character-index?
	 edit-workspace-hidden?)
  (with-old-style-workstation-return-function
      ('execute-command-on-return inspect-command nil)
    (enter-editing-context 
      inspect-command 'box-translation-and-text nil edit-workspace-hidden?
      nil nil
      cursor-line-index? cursor-character-index?))
  (when edit-workspace-hidden?
    (finish-parsing-insofar-as-possible)))
  

;;; The function `execute-command-on-return' ... Note: this is used after the
;;; editing sessions ends for some, but not all, commands.  Specifically, this
;;; is used for commands of class init-file-command and inspect-command, and
;;; also file-command subclasses except kb-load-file-command and
;;; kb-save-file-command.  It gets necessary info from the workstation context,
;;; which should be an edit context for the command frame.  It then clears the
;;; info from the workstation context, exits the editor, and calls the
;;; `execute-command' method of the command frame if the frame has not been
;;; deleted, deletes the command frame, if necssary, and reclaims the supplied
;;; frame serial number..

(defun execute-command-on-return (workstation-context)
  (let* ((command-frame (workstation-context-return-information workstation-context))
	 (command-name (class command-frame)))
    (setf (workstation-context-return-information-reclaimer? workstation-context)
	  nil) ;; Preempt reclaiming by the context's cleanup method.
    (exit-current-workstation-context-in-return-function 'editing)
    (let ((frame-serial-number (copy-frame-serial-number (frame-serial-number command-frame))))

      (with-backtrace-for-internal-error command-name	    ; Additional backtrace info.
	(funcall-method-if-any 'execute-command command-frame))
      
      (if (not (or (frame-has-been-reprocessed-p command-frame frame-serial-number)
		   (get-workspace-if-any command-frame)))	; New for INSPECT (MHD 6/12/90)
	  (delete-frame command-frame))
      (reclaim-frame-serial-number frame-serial-number))))

;; The frame serial number should be recorded in handle-command for use by the context
;; cleanup mechanism!  (And "reprocessed"?, "reference"?)

;; The command must be executed after exiting from the editing context because it may
;; enter a new (sub)context.  But it would be nice in certain cases if exiting the
;; editor could be done conditionally after command execution, based on a returned
;; value or whatever.





;;;; Class Choice Action Definitions




(defun manifest-item-creation (item image-plane x-in-window y-in-window)
  (declare (ignore image-plane))
  (set-cursor-position x-in-window y-in-window)	; See NOTE below
  (enter-transfer-dragging-context item))

;; NOTE: The set-cursor-position is only done for some of the class choice actions
;; due mostly to sloppyness (inconsistency), mine.  I am not a big fan of doing it
;; anyway.  (MHD 4/3/91)

;; Why did we just start ignoring the image-plane today? - ben 1/13/92

  

(def-class-choice-action entity (class image-plane x-in-window y-in-window)
  (manifest-item-creation (make-entity class) image-plane x-in-window y-in-window))

;; Should this be on a subclass of entity?


(def-class-choice-action message (class image-plane x-in-window y-in-window)
  (manifest-item-creation
    (make-message nil class)
    image-plane x-in-window y-in-window))


(def-class-choice-action readout-table (class image-plane x-in-window y-in-window)
  (manifest-item-creation
    (make-readout-table class)
    image-plane x-in-window y-in-window))


(def-class-choice-action dial (class image-plane x-in-window y-in-window)
  (manifest-item-creation
    (make-dial class)
    image-plane x-in-window y-in-window))


(def-class-choice-action meter (class image-plane x-in-window y-in-window)
  (manifest-item-creation
    (make-meter class)
    image-plane x-in-window y-in-window))

;; Despite the fact that dials and meters are entities, it is necessary to use
;; make-dial and make-meter since these cause the rulings to be made as well
;; (see make-dial and make-meter in DISPLAYS).


(def-class-choice-action button (class image-plane x-in-window y-in-window)
  (manifest-item-creation
    (make-button class)
    image-plane x-in-window y-in-window))


(def-class-choice-action graph (class image-plane x-in-window y-in-window)
  (manifest-item-creation
    (make-graph class)
    image-plane x-in-window y-in-window))
 

(def-class-choice-action chart (class image-plane x-in-window y-in-window)
  (manifest-item-creation
    (make-frame class)
    image-plane x-in-window y-in-window))


(def-class-choice-action freeform-table (class image-plane x-in-window y-in-window)
  (manifest-item-creation
    (make-frame class)
    image-plane x-in-window y-in-window))




(def-class-choice-action text-box (class image-plane x-in-window y-in-window)
  (if ;; Usually doesn't get this far, since menu  
    ;; choices for new-rule, et al, are disabled.
    #-pre-g2-v5-licensing
    nil
    #+pre-g2-v5-licensing
    (and
      (or (runtime-option-authorized-p)	     
	  (restricted-use-option-authorized-p)
	  (embedded-option-authorized-p))
      (null (type-of-slot-if-editable	
	      class 'box-translation-and-text)))
    (notify-user
      "Creation of ~a instances is prohibited in run-time-only systems."
      class)
    (unless (null (workspace-on-image-plane? image-plane))
      ;; the null workspace case would be degenerate, if even possible!
      (let ((text-box (make-text-box class)))
	(with-old-style-workstation-return-function
	    ('hand-place-on-return
	         (gensym-list
		   text-box x-in-window y-in-window
		   (copy-frame-serial-number (frame-serial-number text-box)))
	         'reclaim-hand-placement-return-information)
	    (enter-editing-context
	      text-box 'box-translation-and-text
	      (make-empty-text)		; blank -- don't let see initial "..."
					;   (New -- something caused "..." to start
					;   showing up just recently; I think that's
					;   ok, & this removes the minor annoyance
					;   of the "..."'s appearing.  (MHD 8/13/91)
	    ))))))

;; Why did we just start ignoring the image-plane today? - ben 1/13/92



;;; Make-text-box ... creates a text box of the specified class.  ...
;;; chooses the appropriate "font" (format) based on the class and the
;;; Fonts system table.

(defun make-text-box (class)
  (let* ((new-text-box (make-frame class))
	 (default-text-box-format-name
	   (default-text-box-format-name new-text-box)))
    (setf (text-box-format new-text-box)
	  (get-or-make-format-frame
	    (class-case class
	      (statement
		(choose-font-format-per-fonts-table
		  default-text-box-format-name
		  'font-for-statements))
	      ((free-text borderless-free-text)
	       (choose-font-format-per-fonts-table
		 default-text-box-format-name
		 'font-for-free-text))
	      (t
		default-text-box-format-name))))
    (setf (box-translation-and-text new-text-box)
	  (make-incomplete-box-translation-and-text))
    (reformat-text-box-in-place new-text-box)
    new-text-box))

;; Should this be where run-time-only restrictions on creating rules, etc.,
;; are enforced?!  (Now done, instead, in the def-class-choice-action for
;; text-box.)  (MHD 7/18/91)




(defun hand-place-on-return (workstation-context)
  (let* ((workstation-context-return-information
	  (workstation-context-return-information workstation-context))
	 (text-box (first workstation-context-return-information))
	 (x-in-window (second workstation-context-return-information))
	 (y-in-window (third workstation-context-return-information))
	 (frame-serial-number (copy-frame-serial-number (fourth workstation-context-return-information))))
    (setf (first workstation-context-return-information) nil)
    (exit-current-workstation-context-in-return-function 'editing)
    (set-cursor-position x-in-window y-in-window)
    (when (frame-serial-number-equal (frame-serial-number text-box) frame-serial-number)
      ;; editor deletes blank texts
      (with-workstation-context-continuation
	  (reenter-editor-if-not-hand-placed)
	(enter-transfer-dragging-context text-box)))
    (reclaim-frame-serial-number frame-serial-number)))



(defun reclaim-hand-placement-return-information (hand-placement-return-information)
  (when (first hand-placement-return-information)
    (delete-frame (first hand-placement-return-information)))
  (reclaim-frame-serial-number (fourth hand-placement-return-information))
  (reclaim-gensym-list hand-placement-return-information))

;; Consider having an "autoplace" option, where the autoplacement workspace position would
;; be (x-in-workspace x-in-window image-plane) and its y counterpart.  In addition to this
;; position, (workspace-on-image-plane? image-plane) and its frame serial number would be
;; passed as return information.  Old code follows.
;; 
;;      (cond
;;	  ((= (frame-serial-number placement-upon-exit-from-editing?)
;;	      (serial-number-of-placement-workspace? current-edit-state))
;;	   ;; place on placement-upon-exit-from-editing? at
;;	   ;; left-edge-in-placement-workspace? top-edge-in-placement-workspace?
;;	   (add-to-workspace
;;	     frame? placement-upon-exit-from-editing?
;;	     (-w (left-edge-in-placement-workspace? current-edit-state)
;;	         (left-edge-of-block frame?))
;;	     (-w (top-edge-in-placement-workspace? current-edit-state)
;;	         (top-edge-of-block frame?))
;;	     t)))



(defun hand-place-on-return-move-style (workstation-context)
  (let* ((workstation-context-return-information
	  (workstation-context-return-information workstation-context))
	 (text-box (first workstation-context-return-information))
	 (x-in-window (second workstation-context-return-information))
	 (y-in-window (third workstation-context-return-information))
	 (frame-serial-number (copy-frame-serial-number (fourth workstation-context-return-information)))
	 (image-plane (fifth workstation-context-return-information)))
    (setf (first workstation-context-return-information) nil)
    (exit-current-workstation-context-in-return-function 'editing)
    (set-cursor-position x-in-window y-in-window)
    (when (frame-serial-number-equal (frame-serial-number text-box) frame-serial-number)
      ;; editor deletes blank texts
      (with-workstation-context-continuation
	  (reenter-editor-if-not-hand-placed)
	(enter-move-dragging-context text-box 0 0 image-plane)))
    (reclaim-frame-serial-number frame-serial-number)))

(defun reclaim-move-style-hand-placement-return-information (hand-placement-return-information)
  (let* ((text-box? (first hand-placement-return-information))
	 (reference-serial-number (fourth hand-placement-return-information)))
    (when (and text-box?
	       (not (frame-has-been-reprocessed-p text-box? reference-serial-number))
	       (incomplete-box-translation-and-text-p text-box?))
      (delete-frame text-box?)))
  (reclaim-frame-serial-number (fourth hand-placement-return-information))
  (reclaim-gensym-list hand-placement-return-information))





;;;; Graph Menus


(def-class-choice-action trend-chart (class image-plane x-in-window y-in-window)
  (manifest-item-creation
    (make-trend-chart class)
    image-plane x-in-window y-in-window))



;;;; System Tables Menu



(def-menu-string kb-configuration "KB Configuration")



;;;; Special-purpose Box Menus



(defun describe-restrictions-on-temporary-workspace (item pane)
  (let* ((table (make-table-describing-restrictions item))
	 (workspace (make-workspace 'temporary-workspace nil table 2)))
    (when new-g2-classic-ui-p
      (change-slot-value
	workspace 'workspace-background-color?
	(get-ui-parameter 'system-workspace-background-color))
      ;; code cribbed from expose-menu! (MHD)
      (let* ((first-row (first (table-rows table)))
	     (title-text?
	       (loop for cell? in first-row
		     when (and cell? (not (cell-is-block-p cell?)))
		       do (return (copy-text (text? cell?))))))
	(cond
	  ((and title-text?
		;; can't handle case of degenerate table with just one row:
		(cdr (table-rows table))
		;; can't handle blocks in cells (rare):
		(not (loop for cell? in first-row
			   thereis (and cell? (cell-is-block-p cell?)))))
	   (pop (table-rows table))
	   (reclaim-slot-value first-row)
	   (reformat-table-in-place
	     table t
	     (+w (get-total-title-bar-text-width title-text?)
		 ;; Disclosure: hand-tweaked to account for:   (MHD 10/5/99)
		 ;;  + extra padding around title bar
		 ;;  + extra padding around title bar text
		 ;;  + extra padding around close box
		 ;;  + width of close box
		 ;;  - table (i.e., table) border width
		 33))
	   (change-slot-value
	     workspace 'title-bar-caption-text
	     title-text?)
	   (shrink-wrap-workspace workspace))
	  (title-text?
	   (reclaim-text title-text?)))))
    (put-workspace-on-pane workspace pane 'left 'top nil)))




;;;; Display Menus (Graphs, Dials, Meters, and Readouts)


(def-spot meter-or-dial-spot
    :slots nil
    :include spot
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented entity)

(def-spot dial-spot
    :include meter-or-dial-spot
    :type-of-frame-represented dial)

(def-spot meter-spot
    :include meter-or-dial-spot
    :type-of-frame-represented meter)



;;;; Rotate/Reflect, Change Size, and Change Color




;;; `Color-parameters' ...


(def-system-frame color-parameters facilities
  (color-menu-ordering
    hue vector-slot system (type color-menu-ordering))
  
  (colors-on-1st-level-color-menu
    standard-set vector-slot system (type color-set-spec))
  (colors-on-2nd-level-color-menu
    all vector-slot system (type color-set-spec))
  
;; include after workspace-scale design has been done (or cancelled) for SHOW!
;  (scale-for-1st-level-color-menu
;    nil vector-slot system (type workspace-scale))
;  (scale-for-2nd-level-color-menu
;    nil vector-slot system (type workspace-scale))
  
  (number-of-columns-for-1st-level-color-menu
    1 vector-slot system (type number-of-menu-columns-spec))	; in range [1-4]!
  (number-of-columns-for-2nd-level-color-menu
    3 vector-slot system (type number-of-menu-columns-spec))
  
  (dismiss-color-menu-after-choosing?
    t vector-slot system (type yes-or-no)))

;; Keep around for a few weeks, at least (MHD 1/30/90)
(def-absent-slot-putter do-not-dismiss-color-menu-after-choosing?
    (color-parameters value)
  (setf (dismiss-color-menu-after-choosing? color-parameters)
	(not value)))


;; color-menu-ordering

(add-grammar-rules
  '((color-menu-ordering 'intensity)
    (color-menu-ordering 'alphabetic)
    (color-menu-ordering 'hue)))

(def-slot-value-writer color-menu-ordering (value)
  (twrite-symbol value))




;; color-set-spec

(add-grammar-rules
  '((color-set-spec 'all)
    ;; was in 3.1 in development for a few months until now. 
    ;; -- remove remaining support below before the
    ;; final release! (MHD 4/27/93)
;    (color-set-spec
;      ('all '\, 'including 'the 'new 'pastels)	; "added for version 3.1"?
;      all-including-new-pastels)
    (color-set-spec ('standard 'set) standard-set)
    (color-set-spec list-of-colors)))

(add-grammar-rules-for-list
  'list-of-colors 'color '\, nil 'none)



(def-slot-value-compiler color-set-spec (parse-result)
  (if (atom parse-result)			; nil, STANDARD-SET, or ALL,
						;   or ALL-INCLUDING-NEW-PASTELS -- the
						;   last one is under review; it was
						;   added today. (MHD 12/17/92)
      (if (eq parse-result 'none)		; Used to not do this! Bug in 2.0 Beta4!
	  nil
	  parse-result)
      (cdr parse-result)))			; a list (\, . colors)

(def-slot-value-writer color-set-spec (value)
  (if (atom value)
      (case value
	(all-including-new-pastels		; new. (MHD 12/17/92)
	 (tformat "all, including the new pastels"))
	(t
	 (twrite-symbol (or value 'none))))
      (write-symbol-list value '\, nil)))


(def-slot-putter colors-on-1st-level-color-menu (color-parameters-instance value)
  (if (eq value 'none) (setq value nil))	       ; fixes bug in 2.0 Beta 4!
  (setf (colors-on-1st-level-color-menu color-parameters-instance) value))

(def-slot-putter colors-on-2nd-level-color-menu (color-parameters-instance value)
  (if (eq value 'none) (setq value nil))	       ; fixes bug in 2.0 Beta 4!
  (setf (colors-on-2nd-level-color-menu color-parameters-instance) value))

;; The above slot putters are only needed for the initializing case and only to fix
;; the problem with old kbs that mistranslated NONE by failing to convert it to
;; nil!  This was only a problem with Beta software.  The slot putters could be
;; removed for the next major release after 2.0.  (MHD 7/12/90)




;; number-of-menu-columns-spec

(add-grammar-rules
  '((number-of-menu-columns-spec '1)
    (number-of-menu-columns-spec '2)
    (number-of-menu-columns-spec '3)
    (number-of-menu-columns-spec '4)
    (number-of-menu-columns-spec '5)
    (number-of-menu-columns-spec '6)
    (number-of-menu-columns-spec '7)))

(def-slot-value-writer number-of-menu-columns-spec (value)
  (twrite value))



(def-menu-item-format left-aligned-color-menu-item-format
  text-cell-left-margin 1
  text-cell-top-margin 1
  text-cell-right-margin 1
  text-cell-bottom-margin 1
  text-cell-font-map (hm14)
  
  text-cell-line-height 17			; 15 and 12 are usable but
  text-cell-baseline-position 13		;   a bit uncomfortable
  
  text-cell-line-spacing 0
  text-cell-line-quadding? nil			; left aligned
  minimum-format-width-for-text-cell 100)

(def-menu-item-format center-aligned-color-menu-item-format
  text-cell-left-margin 1
  text-cell-top-margin 1
  text-cell-right-margin 1
  text-cell-bottom-margin 1
  text-cell-font-map (hm14)
  
  text-cell-line-height 17			; 15 and 12 are usable but
  text-cell-baseline-position 13		;   a bit uncomfortable
  
  text-cell-line-spacing 0
  text-cell-line-quadding? center
  minimum-format-width-for-text-cell 100)

(def-menu-item-format right-aligned-color-menu-item-format
  text-cell-left-margin 1
  text-cell-top-margin 1
  text-cell-right-margin 1
  text-cell-bottom-margin 1
  text-cell-font-map (hm14)
  
  text-cell-line-height 17			; 15 and 12 are usable but
  text-cell-baseline-position 13		;   a bit uncomfortable
  
  text-cell-line-spacing 0
  text-cell-line-quadding? center
  minimum-format-width-for-text-cell 100)

;(def-menu-item-format color-menu-subcommand-format
;  text-cell-left-margin 1
;  text-cell-top-margin 1
;  text-cell-right-margin 1
;  text-cell-bottom-margin 1
;  text-cell-font-map (hm14)			; smaller?
  
;  text-cell-line-height 15
;  text-cell-baseline-position 12
  
;  text-cell-line-spacing 0
;  text-cell-line-quadding? left
;  minimum-format-width-for-text-cell 100)

;(def-menu-item-format color-menu-subcommand-subtitle-format
;  text-cell-left-margin 1
;  text-cell-top-margin 1
;  text-cell-right-margin 1
;  text-cell-bottom-margin 1
;  text-cell-font-map (hm14)			; smaller?
  
;  text-cell-line-height 15
;  text-cell-baseline-position 12
  
;  text-cell-line-spacing 0
;  text-cell-line-quadding? right
;  minimum-format-width-for-text-cell 100)

(def-table-format color-menu-table-format
  table-background-color? black
  table-border-color? black
  table-line-color? black
  table-left-border-width 2
  table-top-border-width 2
  table-right-border-width 2
  table-bottom-border-width 2
  table-row-boundary-width 1
  table-column-boundary-width 1)

#+development
(def-table-format-spot-generator color-menu-table-format (menu mouse-pointer)
  (declare (ignore menu mouse-pointer))
  (error "This shouldn't be called, preempted by the method on the entire-menu-spot."))


;(def-table-format color-menu-table-subcommand-format
;  table-background-color? white
;  table-border-color? black
;  table-left-border-width 1
;  table-top-border-width 1
;  table-right-border-width 1
;  table-bottom-border-width 1
;  table-row-boundary-width 1
;  table-column-boundary-width 1)



;;; `Make-text-cell-plist-for-color-background' creates a slot value list of
;;; the form
;;;
;;;   (BACKGROUND-COLOR color LINE-COLOR black-or-white)
;;;
;;; suitable for inclusion in a text cell plist, where color (same as the arg)
;;; is to be the background color of the text cell, and black-or-white is
;;; black, if color is light, or black, if color is dark.

(defun make-text-cell-plist-for-color-background (color)
  (slot-value-list
    'background-color color
    'line-color
      (case (map-to-black-or-white color) (white 'black) (black 'white))))




;;; `Post-color-choice-menu' ...  Number-of-columns?  can be either 1, 2, 3, 4,
;;; 5, 6, or 7.  It defaults to 3.  When there are an odd number of colors to
;;; occupy the last row of color choices, ...  [DECIDE!]

;;; Color-for-transparent? defaults to nil.  If specified, it should be the
;;; background color of the workspace associated with whatever this menu is
;;; for (or some generic background color, such as white).  When specified,
;;; it appears as the entire first row.

;;; Color-for-foreground? defaults to nil.  If specified, it should be the
;;; foreground color of the workspace associated with whatever this menu is
;;; for (or some generic foreground color, such as black).  When specified,
;;; it appears as the row following the menu title row as well as the
;;; transparent choice row, if any.

;;; If More-choice? is true, it causes a choice that looks like "More ..." to
;;; appear as the entire last row.  When this choice is selected, a "second
;;; level" color choice menu can be expected to be popped up. ...

;;; Heading-symbol-or-string, if a string, should be a reclaimable text string.

;;; Note: at present, color choices are not subject to translation, but
;;; heading-symbol-or-string, if a symbol, is subject to translation or
;;; substitution of def-menu-string aliases.





;;;; Bounding Boxes



;;; A `bounding box' is a specialized class of frame used to draw rectangular
;;; boxes.  Note that this class is actually based on the class text-box,
;;; although it is not really related.

;;; Bounding boxes allow users to `surround' objects on the screen (via the
;;; "change size" menu option -- see below) and are also used to display the
;;; rectangular border of type-in boxes (see CONTROLS).

;;; The operations on a bounding box are
;;;
;;;    make-bounding-box (width, height) => bounding-box
;;;
;;;    bounding-box-border-width (bounding-box) => width of the border
;;;
;;;    update-border-of-bounding-box (bounding-box, new-left-edge?,
;;;      new-top-edge?, new-right-edge?, new-bottom-edge?)
;;;
;;; in addition to other usual block/frame operations (e.g. delete-frame, width-
;;; of-block, height-of-block, etc.).

;;; The left, top, right, and bottom edges of a bounding box the corresponding
;;; block edges offset by the bounding box border width.  I.e. the bounding box
;;; edges are its inner edges.

;; Consider defining bounding-box-left-edge, etc.

(def-class (bounding-box text-box)
  (default-text-box-format-name bounding-box-format))


(def-text-box-format bounding-box-format
  text-box-left-border-width 5			; all four edges must be the same
  text-box-top-border-width 5
  text-box-right-border-width 5
  text-box-bottom-border-width 5)

;; The following did not work out:
;; 
;; ;; I changed border width from 5 to 1 for two reasons: (1) 5 was too clunky
;; -- it ;; flopped around, even on fast machines, getting all the bits up; (2)
;; the hairline ;; (1 pixel) width version appears the same thickness at all
;; workspace scales, ;; whereas 5 got scaled down to 1 when the workspace
;; happened to be small, which ;; is not particularly desirable.  Best would be
;; to be able to keep the box from ;; scaling at all, but we can not do that
;; until we have some other type of drawing ;; mechanism -- see notes about
;; "ghost images" in paper train.  (MHD 2/8/91)
;;
;; Why?  Because the hairline got xor'ed out along with "border" lines on the
;; icons, especially at certain scales.  Also, the picking region in the icon
;; editor is just the 5 pixels of width of the border.  Both of the problems
;; could probably be solved without leaving the border so fat, but work on that
;; later!  (MHD 3/5/91)



(def-spot bounding-box-spot
    :slots nil
    :include spot
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented bounding-box)

(def-class-method generate-spot (bounding-box mouse-pointer)
  (push-last-spot mouse-pointer (make-bounding-box-spot) bounding-box))


(defmacro bounding-box-border-width (bounding-box)
  `(text-box-left-border-width (text-box-format ,bounding-box)))




(defun make-bounding-box (width height)
  (let* ((bounding-box
	   (make-free-text-box
	     (obtain-simple-text-string 0) 'bounding-box))
	 (doubled-border-width
	   (twicew (bounding-box-border-width bounding-box))))
    (set-edges-of-block bounding-box 0 0 
			(+w width doubled-border-width)
			(+w height doubled-border-width))
    (set-do-not-save-in-kb bounding-box)
    bounding-box))


(defun update-border-of-bounding-box
       (bounding-box new-left-edge? new-top-edge?
	new-right-edge? new-bottom-edge?)
  (update-border-of-text-box
    bounding-box
    (if new-left-edge?
	(-w new-left-edge?
	    (bounding-box-border-width bounding-box)))
    (if new-top-edge?
	(-w new-top-edge?
	    (bounding-box-border-width bounding-box)))
    (if new-right-edge?
	(+w new-right-edge?
	    (bounding-box-border-width bounding-box)))
    (if new-bottom-edge?
	(+w new-bottom-edge?
	    (bounding-box-border-width bounding-box)))))



(define-workstation-context bounding ()
  :keymap ((<standard-enter-keys> enter-keys-in-bounding-state)
	   ((<mouse-down> close-box-spot)
	    mouse-down-on-close-box-widget-in-bounding-state)
	   ((<mouse-down> title-bar-spot) search-for-mouse-drag)
	   ((<mouse-drag> title-bar-spot) start-dragging-title-bar-handler)
	   ((<mouse-down> image-plane-spot) mouse-down-on-image-plane-in-bounding-state)
	   (<mouse-down> requeue-event-and-abort-workstation-context)
	   (<mouse-motion> mouse-motion-in-bounding-state)
	   (<mouse-up> mouse-up-in-bounding-state))
  :constructor (make-bounding-state
		 (bounding-dialog-workspace
		   bounding-state-bounding-box
		   bounding-state-constrained-width?
		   bounding-state-constrained-height?
		   edge-or-corner-of-bounding-box?
		   x-offset-from-bounding-box?
		   y-offset-from-bounding-box?
		   sizing-box-corner-x0
		   sizing-box-corner-y0
		   bounding-image-plane
		   block-to-be-bounded?
		   workspace-for-bounding-box))
  :state-variables (bounding-dialog-workspace
		     bounding-state-bounding-box
		     bounding-state-constrained-width?
		     bounding-state-constrained-height?
		     edge-or-corner-of-bounding-box?
		     x-offset-from-bounding-box?
		     y-offset-from-bounding-box?
		     sizing-box-corner-x0
		     sizing-box-corner-y0
		     bounding-image-plane

		     block-to-be-bounded?; move these to more logical position!
		     workspace-for-bounding-box))

(def-structure-method valid-workstation-context-p (bounding-state)
  (and (funcall-superior-method bounding-state)
       (valid-block-in-workstation-context-p
	 (bounding-dialog-workspace bounding-state)
	 bounding-state)
       (valid-block-in-workstation-context-p
	 (bounding-state-bounding-box bounding-state)
	 bounding-state)
       (or (null (block-to-be-bounded? bounding-state))
	   (valid-block-in-workstation-context-p
	     (block-to-be-bounded? bounding-state)
	     bounding-state))
       (valid-block-in-workstation-context-p
	 (workspace-for-bounding-box bounding-state)
	 bounding-state)
       (memq (bounding-image-plane bounding-state)	    ; image plane went away?
	     (image-planes-this-is-on
	       (workspace-for-bounding-box bounding-state)))))


(def-structure-method clean-up-workstation-context (bounding-state)
  (when (valid-block-in-workstation-context-p
	  (bounding-dialog-workspace bounding-state)
	  bounding-state)
    (delete-frame (bounding-dialog-workspace bounding-state)))
  (when (valid-block-in-workstation-context-p
	  (bounding-state-bounding-box bounding-state)
	  bounding-state)
    (delete-frame 
      (bounding-state-bounding-box bounding-state)))
  (funcall-superior-method bounding-state))

;; This seems old fashion... can't valid-block-in-workstation-context-p cut it?






(def-dialog-box-format dialog-message-format
  text-cell-left-margin 3
  text-cell-top-margin 3
  text-cell-right-margin 3
  text-cell-bottom-margin 3
  text-cell-font-map (hm18)
  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0)



(defun operate-on-area-of-workspace
       (workspace image-plane original-x-in-window original-y-in-window)
  (enter-bounding-dialog
    "Select operation on area after moving its edges and corners"
    '(((move "Move" move-area) (clone "Clone" clone-area)
       (transfer "Transfer" transfer-area))
      ((left "Left" move-area-to-left)
       (l-r-center "L/R Center" move-area-to-l-r-center)
       (right "Right" move-area-to-right))
      ((top "Top" move-area-to-top)
       (t-b-center "T/B Center" move-area-to-t-b-center)
       (bottom "Bottom" move-area-to-bottom))
      ((delete "Delete" delete-area)
       (quit "Quit" sizing-quit)))
    ;; alt: exit, done; NOT cancel
    ;; When Help is added, suggest the following layout:
    ;; '((move clone transfer delete)
    ;;   (quit help))
    nil workspace
    image-plane original-x-in-window original-y-in-window 110))



(defconstant sizing-dialog-message-string
  "Done moving edges and corners?")
;; Too brief?!  Alt:
;;    "To change the size, move the edges and corners of the box and then click on OK."
  

(defun enter-sizing-dialog
       (block image-plane original-x-in-window original-y-in-window)
  (enter-bounding-dialog
    sizing-dialog-message-string
    '(((cancel "Cancel" sizing-quit) (ok "Yes" sizing-ok t))
					; add "Help" eventually! (to the
					; right of cancel?)
      ((restore-to-normal-size "Restore to Normal Size" sizing-restore)
       (update-now "Update Now" sizing-update)))
    block
    (get-workspace-if-any block)		; can't return nil
    image-plane original-x-in-window original-y-in-window))


(defun enter-min-sizing-dialog
       (block image-plane original-x-in-window original-y-in-window)
  (enter-bounding-dialog
    sizing-dialog-message-string
    '(((cancel "Cancel" sizing-quit) (ok "Yes" sizing-ok t))
      ((no-minimum "No Minimum" sizing-no-minimum)
       (update-now "Update Now" sizing-update)))
    block
    (get-workspace-if-any block)		; can't return nil
    image-plane original-x-in-window original-y-in-window))



(defun enter-bounding-dialog
       (message-string rows-of-button-names
	block-for-bounding-box? workspace-for-bounding-box
	image-plane x-in-window y-in-window
	&optional minimum-width-of-button?)  
  (let* ((bounding-box	     
	   (make-bounding-box
	     (if block-for-bounding-box?
		 (width-of-block block-for-bounding-box?)
		 100)
	     (if block-for-bounding-box?
		 (height-of-block block-for-bounding-box?)
		 100)))
	 (bounding-box-border-width
	   (bounding-box-border-width bounding-box))
	 x-in-workspace y-in-workspace)
    (with-image-plane-transform (image-plane)
      (setf x-in-workspace (x-in-workspace x-in-window))
      (setf y-in-workspace (y-in-workspace y-in-window)))
    (add-to-workspace
      bounding-box
      workspace-for-bounding-box
      (-w (if block-for-bounding-box?
	      (left-edge-of-block block-for-bounding-box?)
	      x-in-workspace)
	  bounding-box-border-width)
      (-w (if block-for-bounding-box?
	      (top-edge-of-block block-for-bounding-box?)
	      y-in-workspace)
	  bounding-box-border-width)
      t t)
    (let* ((workspace
	     (make-workspace
	       'temporary-workspace nil
	       (make-dialog-message message-string) 10)))
      (set-up-bounding-dialog-ws
	rows-of-button-names workspace
	(+w (left-edge-of-block workspace) (workspace-margin workspace))
	(bottom-edge-of-block workspace) minimum-width-of-button?)
      (put-workspace-on-pane
	workspace current-workstation-detail-pane 'left 'top t)
      
      (enter-context-in-current-workstation
	'bounding
	(make-bounding-state
	  workspace
	  bounding-box
	  (if block-for-bounding-box?
	      (unless (frame-of-class-p block-for-bounding-box? 'text-box)
		;; do not constrain width for text boxes
		(width-of-block block-for-bounding-box?)))
	  (if block-for-bounding-box?
	      (unless (frame-of-class-p block-for-bounding-box? 'text-box)
		;; do not constrain width for text boxes
		(height-of-block block-for-bounding-box?)))
	  nil nil nil
	  nil nil
	  image-plane				; when reorder args, put near
						;   original-x,y-in-window!
	  block-for-bounding-box?
	  workspace-for-bounding-box)))))


(defun-void sizing-ok ()
  (let* ((bounding-state
	   specific-structure-for-current-workstation-context)
	 (block
	     (block-to-be-bounded? bounding-state))
	 (bounding-box
	   (bounding-state-bounding-box bounding-state))
	 (text-box-format
	   (text-box-format bounding-box))
	 (left-edge-of-bounding-box
	   (+w (left-edge-of-block bounding-box)
	       (text-box-left-border-width text-box-format)))
	 (top-edge-of-bounding-box
	   (+w (top-edge-of-block bounding-box)
	       (text-box-top-border-width text-box-format)))
	 (right-edge-of-bounding-box
	   (-w (right-edge-of-block bounding-box)
	       (text-box-right-border-width text-box-format)))
	 (bottom-edge-of-bounding-box
	   (-w (bottom-edge-of-block bounding-box)
	       (text-box-bottom-border-width text-box-format))))

    (change-size-per-bounding-rectangle
      block
      left-edge-of-bounding-box
      top-edge-of-bounding-box
      right-edge-of-bounding-box
      bottom-edge-of-bounding-box)
    (return-from-current-workstation-context 'bounding)))



(defun-void sizing-quit ()
  (return-from-current-workstation-context 'bounding))

(defun restore-item-to-normal-size (block)
  (frame-class-case block
    (entity
      (magnify-icon block nil nil nil nil nil))
    (graph
      (restore-graph-to-normal-size block))
    (trend-chart
      (restore-trend-chart-to-normal-size block))
    (chart
      (restore-chart-to-normal-size block))
    (text-box
      (restore-size-of-text-box block))))


(defun-void sizing-restore ()
  (let* ((bounding-state
	   specific-structure-for-current-workstation-context)
	 (block
	     (block-to-be-bounded? bounding-state))
	 (bounding-box
	   (bounding-state-bounding-box bounding-state))
	 (text-box-format
	   (text-box-format bounding-box)))
    (restore-item-to-normal-size block)
    (fit-bounding-box-around-block bounding-box block text-box-format)))

(defun-void sizing-update ()
  (let* ((bounding-state
	   specific-structure-for-current-workstation-context)
	 (block
	     (block-to-be-bounded? bounding-state))
	 (bounding-box
	   (bounding-state-bounding-box bounding-state))
	 (text-box-format
	   (text-box-format bounding-box))
	 (left-edge-of-bounding-box
	   (+w (left-edge-of-block bounding-box)
	       (text-box-left-border-width text-box-format)))
	 (top-edge-of-bounding-box
	   (+w (top-edge-of-block bounding-box)
	       (text-box-top-border-width text-box-format)))
	 (right-edge-of-bounding-box
	   (-w (right-edge-of-block bounding-box)
	       (text-box-right-border-width text-box-format)))
	 (bottom-edge-of-bounding-box
	   (-w (bottom-edge-of-block bounding-box)
	       (text-box-bottom-border-width text-box-format))))
    (change-size-per-bounding-rectangle block
      left-edge-of-bounding-box top-edge-of-bounding-box
      right-edge-of-bounding-box bottom-edge-of-bounding-box)
    (fit-bounding-box-around-block bounding-box block text-box-format)))


(defun-void sizing-no-minimum ()
  (let* ((bounding-state
	   specific-structure-for-current-workstation-context)
	 (block (block-to-be-bounded? bounding-state)))
    (restore-size-of-text-box block)))

(defun restore-size-of-text-box (text-box)
  (update-images-of-block text-box t t)
  (setf (minimum-width-of-text-box text-box) 0)
  (setf (minimum-height-of-text-box text-box) 0)
  (reformat-text-box-in-place text-box)
  (update-images-of-block text-box nil t))


(defmacro with-operate-on-area-local-variables (button-name &body body)
  `(let* ((bounding-state
	    specific-structure-for-current-workstation-context)
	  (bounding-box
	    (bounding-state-bounding-box bounding-state))
	  (text-box-format
	    (text-box-format bounding-box))
	  (left-edge-of-bounding-box
	    (+w (left-edge-of-block bounding-box)
		(text-box-left-border-width text-box-format)))
	  (top-edge-of-bounding-box
	    (+w (top-edge-of-block bounding-box)
		(text-box-top-border-width text-box-format)))
	  (right-edge-of-bounding-box
	    (-w (right-edge-of-block bounding-box)
		(text-box-right-border-width text-box-format)))
	  (bottom-edge-of-bounding-box
	    (-w (bottom-edge-of-block bounding-box)
		(text-box-bottom-border-width text-box-format)))
	  (specific-image-plane-for-bounding-box
	    (bounding-image-plane bounding-state))
	  (blocks-in-bounding-box		; non-nil for these group case operation
	    (prepare-blocks-for-operation-on-area
	      (superblock? bounding-box)		   
	      left-edge-of-bounding-box top-edge-of-bounding-box
	      right-edge-of-bounding-box bottom-edge-of-bounding-box
	      (eq ,button-name 'transfer)
	      (eq ,button-name 'clone))))
     ,@body))




(defun-void move-area ()
  (with-operate-on-area-local-variables
      'move
    (progn
      (warp-cursor-for-bounding-state-button bounding-state 'move)

      (when blocks-in-bounding-box
	(let ((blocks-to-drag
		(dragging-cons-function bounding-box blocks-in-bounding-box))
	      (x-offset-from-dragger
		(-w (halfw
		      (+w (left-edge-of-block bounding-box)
			  (right-edge-of-block bounding-box)))
		    (left-edge-of-block bounding-box)))
	      (y-offset-from-dragger
		(-w (halfw
		      (+w (top-edge-of-block bounding-box)
			  (bottom-edge-of-block bounding-box)))
		    (top-edge-of-block bounding-box))))
	  (enter-move-dragging-context
	    blocks-to-drag
	    x-offset-from-dragger y-offset-from-dragger
	    specific-image-plane-for-bounding-box
	    nil))))))


(defun-void transfer-area ()
  (with-operate-on-area-local-variables
      'transfer
    (progn
      (warp-cursor-for-bounding-state-button bounding-state 'transfer)

      (when blocks-in-bounding-box
	(let ((blocks-to-drag
		(dragging-cons-function bounding-box blocks-in-bounding-box))
	      (x-offset-from-dragger
		(-w (halfw
		      (+w (left-edge-of-block bounding-box)
			  (right-edge-of-block bounding-box)))
		    (left-edge-of-block bounding-box)))
	      (y-offset-from-dragger
		(-w (halfw
		      (+w (top-edge-of-block bounding-box)
			  (bottom-edge-of-block bounding-box)))
		    (top-edge-of-block bounding-box))))
	  (with-workstation-context-continuation
	      (fix-up-bounding-state-if-necessary-after-transfer)
	    (when (workspace-on-image-plane?
		    specific-image-plane-for-bounding-box) 
	      (invoke-workspace-invalidation-handler-if-any
		(workspace-on-image-plane?
		  specific-image-plane-for-bounding-box)
		'transfer-source))
	    (enter-transfer-dragging-context
	      blocks-to-drag
	      x-offset-from-dragger y-offset-from-dragger
	      specific-image-plane-for-bounding-box
	      nil
	      nil)))))))
	


(defun-void clone-area ()
  (with-operate-on-area-local-variables 'clone
    (warp-cursor-for-bounding-state-button bounding-state 'clone)
    (when blocks-in-bounding-box
      (let ((dragging-list-of-cloned-blocks
	      (clone-blocks blocks-in-bounding-box)))
	(reclaim-dragging-list-function blocks-in-bounding-box)

	(let ((region-invalidation-is-preferred t)) ; See Note A.
	  (erase-images-of-block bounding-box t)    ; makes transfer work -- i.e.
	  (remove-as-subblock-if-necessary		 ; all blocks wo/superblocks
	    bounding-box))

	(with-workstation-context-continuation
	    (fix-up-bounding-state-if-necessary-after-transfer)
	  (enter-transfer-dragging-context
	    (dragging-cons-function
	      bounding-box dragging-list-of-cloned-blocks)
	    (-w
	      (halfw
		(+w
		  (left-edge-of-block bounding-box)
		  (right-edge-of-block bounding-box)))
	      (left-edge-of-block bounding-box))
	    (-w
	      (halfw
		(+w
		  (top-edge-of-block bounding-box)
		  (bottom-edge-of-block bounding-box)))
	      (top-edge-of-block bounding-box))
	    specific-image-plane-for-bounding-box))))))

;; Note A: This binding works around a bug in the protocol for drawing --
;; removing the block as a subblock deletes pending block changes, of which the
;; inval created by the erase-block was one.  The binding forces the inval to
;; go to the workspace, rather then the block.  Ideally, the drawing protocol
;; should be be fixed, but this will do for now.  This was added to fix
;; HQ-175247 "Clone via operate-on-area leaves bounding-box", but there are
;; probably other bugs of this nature waiting to be uncovered. -fmw, 1/25/95


;;; The function `clone-blocks' returns a newly consed dragging-list of clones
;;; of blocks.

(defun clone-blocks (blocks)
  (block finally-finally
    (let ((plist-of-blocks-and-corresponding-clones
	    (loop for block in blocks
		  as new-block = (clone-frame block blocks)
		  ;; after cloning an item other than a workspace manually,
		  ;; set it to be neither permanent nor transient:
		  do (set-neither-permanent-nor-transient-and-propagate
		       new-block nil)
		  nconc (gensym-list block new-block))))
      
      ;; At this point, all blocks in blocks have been cloned,
      ;; stubs have been cloned for external connections and internal output
      ;; connections, and plist-of-blocks-and-corresponding-clones has been set up.  
      ;; It is now necessary to tie the cloned internal output connections to 
      ;; their corresponding cloned output end objects.
      
      (loop for (block cloned-block) 
	    on plist-of-blocks-and-corresponding-clones 
		by #'cddr
	    as x-shift
	       = (-w (left-edge-of-block block)
		     (left-edge-of-block cloned-block))
	    as y-shift
	       = (-w (top-edge-of-block block)
		     (top-edge-of-block cloned-block))
	    do 
	(clone-connections-for-block
	  block cloned-block plist-of-blocks-and-corresponding-clones)
	
	;; At this point, all internal connections of cloned-block have been 
	;; tied to their correct blocks at other end.  The next step is to
	;; shift the cloned block and the loose ends for its external 
	;; connections.
	
	(shift-block cloned-block x-shift y-shift)
	#-connections-v2
	(loop for connection-or-port-name in (connections cloned-block)
	      as block-at-other-end? 
		 = (if (not (symbolp connection-or-port-name))
		       (get-block-at-other-end-of-connection
			 connection-or-port-name cloned-block))
	      do
	  (when (and block-at-other-end?
		     (not (memq block-at-other-end? plist-of-blocks-and-corresponding-clones)))
	    ;; if external connection, shift loose end
	    (shift-block block-at-other-end? x-shift y-shift)))
	#+connections-v2
	(loop for connection being each connection of cloned-block
	      as block-at-other-end = (get-block-at-other-end-of-connection
				        connection cloned-block)
	      do
	  (unless (memq block-at-other-end plist-of-blocks-and-corresponding-clones)
	    ;; if external connection, shift loose end
	    (shift-block block-at-other-end x-shift y-shift)))

	;; An alternative here would be to have clone-frame put external
	;; connections in a special variable.  This would save searching of
	;; the plist.
	
	    finally
	      (loop for (nil cloned-block) 
		    on plist-of-blocks-and-corresponding-clones 
			by #'cddr
		    if (not (loose-end-p cloned-block))
		      collect cloned-block into dragging-list-of-cloned-blocks
			using dragging-cons-function
		      ;; As with other move options, loose ends for straight 
		      ;; connections are not included in blocks to drag when
		      ;; calling enter dragging context.
		    finally
		      (reclaim-gensym-list plist-of-blocks-and-corresponding-clones)
		      (return-from finally-finally dragging-list-of-cloned-blocks))))))

;; Much of this code is duplicated in g2-clone-list-contents.


(defun-void delete-area ()
  (with-operate-on-area-local-variables
      'delete
    (declare (ignore specific-image-plane-for-bounding-box))
    (delete-blocks-for-operate-on-area-after-confirmation
      blocks-in-bounding-box)))


(defun-void align-for-operate-on-area (button-name)
  (with-operate-on-area-local-variables button-name
    (declare (ignore specific-image-plane-for-bounding-box))
    (when blocks-in-bounding-box
      (align-blocks blocks-in-bounding-box button-name))))


;;; The function `align-blocks' moves blocks around according to operation, one
;;; of left, right, l-r-center (or left/right-center), top, bottom, t-b-center
;;; (or top/bottom-center).  Note that the set of operations is a proper
;;; superset of align-selection-operations: it contains, in addition to that
;;; set, l-r-center and t-b-center.

(defun align-blocks (blocks operation)
  (loop for block in blocks
	minimize (left-edge-of-block block)
	  into extreme-left-edge using minf
	maximize (right-edge-of-block block)
	  into extreme-right-edge using maxf
	minimize (top-edge-of-block block)
	  into extreme-top-edge using minf
	maximize (bottom-edge-of-block block)
	  into extreme-bottom-edge using maxf
	finally
	  (loop with workspace
		  = (get-workspace-if-any (car blocks))
		for block in blocks
		as delta-x
		   = (case operation
		       (left
			(-w extreme-left-edge (left-edge-of-block block)))
		       (right
			(-w extreme-right-edge (right-edge-of-block block)))
		       ((l-r-center left/right-center)
			(-w (halfw (+w extreme-left-edge
				       extreme-right-edge))
			    (halfw (+w (left-edge-of-block block)
				       (right-edge-of-block block)))))
		       (t 0))
		as delta-y
		   = (case operation
		       (top
			(-w extreme-top-edge (top-edge-of-block block)))
		       (bottom
			(-w extreme-bottom-edge (bottom-edge-of-block block)))
		       ((t-b-center top/bottom-center)
			(-w (halfw (+w extreme-top-edge extreme-bottom-edge))
			    (halfw (+w (top-edge-of-block block)
				       (bottom-edge-of-block block)))))
		       (t 0))
		do
	    (move-blocks-with-their-external-connections
	      block workspace delta-x delta-y)
	    (when g2-has-v5-mode-windows-p
	      (send-ws-representations-item-moved block delta-x delta-y)))))


;;; The macro `distribute-blocks-1' is a helper macro for distribute-blocks, not
;;; for general use.

(defmacro distribute-blocks-1 (blocks left right midline width dx dy)
  `(with-temporary-gensym-float-creation distribute-blocks-1
     (let* ((sorted-blocks (sort-list (copy-list-using-gensym-conses ,blocks) #'< #',midline))
	    (workspace (get-workspace-if-any (car sorted-blocks)))
	    (min (,right (car sorted-blocks))) ; Todo: Change min/max for dist-wrt-workspce
	    (max (,left (car (last sorted-blocks))))
	    (blocks-to-move (cdr sorted-blocks))
	    (n (-f (length sorted-blocks) 2))
	    (spacing (/ (coerce-to-gensym-float
			  (-f max min (loop for block in blocks-to-move
					    for i below n
					    sum (,width block) using +f)))
			(1+f n))))
       (loop for block in blocks-to-move
	     for i from 1 to n
	     as pos = (round (+ min (* i spacing) sum-extents))
	     sum (,width block) into sum-extents using +f
	     as delta = (-f pos (,left block))
	     do
	 (move-blocks-with-their-external-connections block workspace ,dx ,dy)
	 (when g2-has-v5-mode-windows-p
	   (send-ws-representations-item-moved block ,dx ,dy)))
       (reclaim-gensym-list sorted-blocks))))

;;; The function `distribute-blocks' moves blocks in order to make the spaces
;;; BETWEEN them constant, in the X or Y direction. The blocks at each extreme
;;; position are not moved.

(defun distribute-blocks (blocks operation)
  (cond ((<=f (length blocks) 2))
	((eq operation 'horizontally)
	 (distribute-blocks-1 blocks left-edge-of-block right-edge-of-block
			      midline-x-of-block-function
			      width-of-block delta 0))
	((eq operation 'vertically)
	 (distribute-blocks-1 blocks top-edge-of-block bottom-edge-of-block
			      midline-y-of-block-function
			      height-of-block 0 delta))))

(defun-void move-area-to-left ()
  (align-for-operate-on-area 'left))

(defun-void move-area-to-l-r-center ()
  (align-for-operate-on-area 'l-r-center))

(defun-void move-area-to-right ()
  (align-for-operate-on-area 'right))

(defun-void move-area-to-top ()
  (align-for-operate-on-area 'top))
			 
(defun-void move-area-to-t-b-center ()
  (align-for-operate-on-area 't-b-center))

(defun-void move-area-to-bottom ()
  (align-for-operate-on-area 'bottom))


;;; `Warp-cursor-for-bounding-state-button' is to be called to handle a bounding
;;; context action initiated by a click on the button named by button-name.  If
;;; appropriate, and if possible in the native window system, the mouse is
;;; "warped" to an appropriate new position in the window in which the bounding
;;; context is taking place.
;;;
;;; This does something only when button-name is one of
;;;
;;;    MOVE CLONE TRANSFER
;;;
;;; When button-name is CLONE, the mouse is warped to the position 2 workspace
;;; units to the right of, and 2 workspaces units below, the position of the
;;; center of the bounding box.
;;;
;;; When button-name is MOVE or TRANSFER, this simple warps the mouse to the
;;; center of the bounding box.
;;;
;;; For all other values of button-name, this does nothing at all.

(defun warp-cursor-for-bounding-state-button (bounding-state button-name)
  (let ((bounding-box
	  (bounding-state-bounding-box bounding-state))
	(specific-image-plane-for-bounding-box
	  (bounding-image-plane bounding-state)))
    (set-cursor-position
      ;; should the x,y slots be reset on return from
      ;; move?  now moves to center of bounding box
      ;; consider dragging from top-left?
      (x-in-frame-transform
	(+w (halfw
	      (+w
		(left-edge-of-block bounding-box)
		(right-edge-of-block bounding-box)))
	    (if (eq button-name 'clone) 2 0))
	bounding-box
	specific-image-plane-for-bounding-box)
      (y-in-frame-transform
	(+w (halfw
	      (+w
		(top-edge-of-block bounding-box)
		(bottom-edge-of-block bounding-box)))
	    (if (eq button-name 'clone) 2 0))
	bounding-box
	specific-image-plane-for-bounding-box))))



;;; The `change-size-per-bounding-rectangle' method is generic to blocks.
;;; In addition to the instance, it is called with these arguments
;;;
;;;   left-edge, top-edge, right-edge, and bottom-edge
;;;
;;;     -- these are simply the four edges that make up the
;;;     bounding rectangle.
;;;
;;;   mode
;;;
;;;     -- If there can be more than one variety of change-size
;;;     handled, this says which one it is.  For example, a
;;;     text-box could have a change-size that scales the text
;;;     up, a change-size that sets the minimum (the only kind
;;;     now supported), and a change size that sets the maximum
;;;     (of its frame, presumably).  This is an
;;;     application-defined symbol, and is in fact not yet used
;;;     by anyone.  In the future, it is suggestted that these
;;;     modes be used by convention:
;;;
;;;        nil or default
;;;                     - "default" or unknown or unspecified
;;;                       (Users pass in DEFAULT through the
;;;                       system procedure.)
;;;        grow         - make the "content area" bigger
;;;        scale        - scale things up (or down) in size
;;;        set-minimum  - for things that change size based on
;;;                         content, make this the minimum size
;;;                         to shrink to
;;;        set-maximum  - opposite of set-maximum
;;;
;;; The interpretation of the change size is up to the individual class of
;;; block.  And the interpretation may be made further dependent on the mode
;;; argument.
;;;
;;; Implementations of the method may assume that it is called when block is
;;; fully drawn.  It must leave it in a fully drawn state when it is through.
;;; It should also take care to enlarge the workspace as needed before finishing
;;; its drawing.
;;;
;;; In practice, entities generally handle it by magnification; text boxes
;;; handle it by setting the minimum width; graphs, charts, and trend charts
;;; handle it by expanding the size, and lowering the resolution, of their
;;; respective data windows.
;;;
;;; The default `change-size-per-bounding-rectangle method for block' simply
;;; erases block, moves the upper-left corner of block to the position specified
;;; by left- and top-edge, leaves the right- and bottom-edge as they were, and
;;; enlarges the workspace as necessary, and draws block in the new position.
;;;
;;; The `change-size-per-bounding-rectangle method for connection' does nothing
;;; at all.  Recall that connections are entities, but they are not explicitly
;;; drawn as entities, so it does not make sense to do anything like changing
;;; their size with this operation; only the items they connect to can have
;;; their size changed.

(def-generic-method change-size-per-bounding-rectangle
    (block left-edge top-edge right-edge bottom-edge mode))

(defun change-size-per-bounding-rectangle (block left-edge top-edge right-edge bottom-edge &optional mode)
  (funcall-method-if-any 'change-size-per-bounding-rectangle
			 block left-edge top-edge right-edge bottom-edge mode))

(def-class-method change-size-per-bounding-rectangle
    (block left-edge top-edge right-edge bottom-edge mode)
  (declare (ignore right-edge bottom-edge mode))
  (erase-images-of-block block nil)
  (shift-block
    block
    (-w (left-edge-of-block block) left-edge)
    (-w (top-edge-of-block block) top-edge))
  (enlarge-workspace-for-block-rectangle-if-necessary block nil)
  (draw-images-of-block block nil))

(def-class-method change-size-per-bounding-rectangle
    (kb-workspace left-edge top-edge right-edge bottom-edge mode)
  (declare (ignore mode))
  (with-extreme-edges-minimizing-workspace (kb-workspace)
    (update-extreme-edges-from-elements kb-workspace)
    (update-extreme-edges-from-background-images kb-workspace)  ; Possible bg images.
    (change-workspace-edges-after-including-margin
      kb-workspace
      (minw left-edge extreme-left-edge-so-far)
      (minw top-edge extreme-top-edge-so-far)
      (maxw right-edge extreme-right-edge-so-far)
      (maxw bottom-edge extreme-bottom-edge-so-far))
    nil))

(def-class-method change-size-per-bounding-rectangle
    (connection left-edge top-edge right-edge bottom-edge mode)
  (declare (ignore connection left-edge top-edge right-edge bottom-edge mode)))





;;; `Heuristic-maximum-edge' is given a pair of edges, either left and right or
;;; top and bottom, returns what the more positive edge should be based on a
;;; heuristic limit that is based on the default width or height magnified by
;;; greatest magnification allowed in Gensym software, given by the constant
;;; greatest-magnification.
;;;
;;; The idea is to determine the limit based on similar criteria as icons, even
;;; though a facility that uses this may not necessarily even use magnification,
;;; and so would not in principle need to impose such a limit.  But some
;;; facilities, such as graphs, charts, and trend charts, want to reduce the
;;; chances of running out of memory, and this gives them a pseudo-technical
;;; sounding "limit" to advertise.

(defun heuristic-maximum-edge
    (more-negative-edge more-positive-edge default-width-or-height)
  (minw more-positive-edge
	(+w more-negative-edge
	    (magnify default-width-or-height greatest-magnification))))



    
(def-class-method change-size-per-bounding-rectangle
    (action-button left-edge top-edge right-edge bottom-edge mode)
  (declare (ignore mode))
  ;; determine max same as for all icons/entities
  (setq right-edge
	(heuristic-maximum-edge
	  left-edge right-edge
	  (width-of-icon (icon-description action-button))))
  (setq bottom-edge
	(heuristic-maximum-edge
	  top-edge bottom-edge
	  (height-of-icon (icon-description action-button))))  
  (fit-entity-around-text-box-or-bounding-rectangle
    action-button
    (loop for subblock being each subblock of action-button
	  when (frame-of-class-p subblock 'button-label)
	    return subblock)
    left-edge top-edge right-edge bottom-edge))

(defvar width-for-change-size? nil)
(defvar height-for-change-size? nil)

(def-class-method change-size-per-bounding-rectangle
    (entity left-edge top-edge right-edge bottom-edge mode)
  (declare (ignore mode))
  (let* ((icon-description (icon-description entity))
	 (width-of-icon
	   (or (getfq (icon-attributes-plist entity) 'width)
	       (width-of-icon icon-description)))
	 (height-of-icon  
	   (or (getfq (icon-attributes-plist entity) 'height)
	       (height-of-icon icon-description))))
    (when (rotated-by-90-p		; if so, swap width & height
	    (getfq (icon-attributes-plist entity) 'reflection-and-rotation))
      (rotatef width-of-icon height-of-icon))
    (magnify-icon
      entity
      ;; imposes its own maximum size, effectively based on greatest-magnification
      (convert-ratio-to-magnification
	(if width-for-change-size?
	    (if (managed-float-p width-for-change-size?)
		(managed-float-value width-for-change-size?)
		width-for-change-size?)
	    (-w right-edge left-edge))
	(maxw width-of-icon 1))
      (convert-ratio-to-magnification
	(if height-for-change-size?
	    (if (managed-float-p height-for-change-size?)
		(managed-float-value height-for-change-size?)
		height-for-change-size?)
	    (-w bottom-edge top-edge))
	(maxw height-of-icon 1))
      left-edge top-edge nil)))  

(defvar force-change-to-minimum-size-p nil)

(def-class-method change-size-per-bounding-rectangle
    (text-box left-edge top-edge right-edge bottom-edge mode)
  (update-images-of-block text-box t nil)
  (let* ((width (-w right-edge left-edge))
	 (height (-w bottom-edge top-edge)))
    (case mode				; not used yet
      (scale
       (change-text-box-property
	 text-box 'x-magnification
	 (convert-ratio-to-magnification
	   width
	   (maxw (width-of-block text-box) 1)))
       (change-text-box-property
	 text-box 'y-magnification
	 (convert-ratio-to-magnification
	   height
	   (maxw (height-of-block text-box) 1)))
       (when g2-has-v5-mode-windows-p
	 (send-ws-representations-item-virtual-attribute-change
	   text-box (virtual-attribute 'text-x-magnification) nil)
	 (send-ws-representations-item-virtual-attribute-change
	   text-box (virtual-attribute 'text-y-magnification) nil)))
      (set-maximum
       (change-slot-value
	 text-box 'text-cell-desired-maximum-line-measure-for-text-box?
	 (-w right-edge top-edge)))
      (t
       ;; mode of nil or SET-MINIMUM -- change minimum size case

       ;; If the width is not changed, do not set the minimum width.
       ;; Same for height.  This allows them to set only the minimum
       ;; width or height by only choosing a side.  Notice that if
       ;; they choose a corner, they would have to have a steady
       ;; hand to avoid making the width or height appear to have
       ;; changed.  (Is this too tricky?!)  (MHD 3/25/91)

       (unless (or (=w (minimum-width-of-text-box text-box) width)
		   (and (not force-change-to-minimum-size-p)
			(=w width (width-of-block text-box))))
	 (setf (minimum-width-of-text-box text-box) width))
       (unless (or (=w (minimum-height-of-text-box text-box) height)
		   (and (not force-change-to-minimum-size-p)
			(=w height (height-of-block text-box))))
	 (setf (minimum-height-of-text-box text-box) height)))))
  ;; move top left corner to the bounding box:
  (let ((delta-left-edge (-w left-edge (left-edge-of-block text-box)))
	(delta-top-edge (-w top-edge (top-edge-of-block text-box))))
    (shift-block
      text-box
      delta-left-edge
      delta-top-edge)
    (when (and g2-has-v5-mode-windows-p
	       (not ws-protocol-handle-moves-from-edge-change-p)
	       (or (/=f delta-left-edge 0)
		   (/=f delta-top-edge 0)))
      (send-ws-representations-item-moved
	text-box delta-left-edge delta-top-edge)))
  (reformat-text-box-in-place text-box)
  (enlarge-workspace-for-block-rectangle-if-necessary text-box nil)
  (update-images-of-block text-box nil nil))

;; This doesn't have or need limits for the cases not currently accessible
;; by users now; review later! (MHD 5/12/95)

;; See controls -- more special-purpose sys. proc.'s for text box there.


(def-class-method change-size-per-bounding-rectangle
    (trend-chart left-edge top-edge right-edge bottom-edge mode)
  (declare (ignore mode))
  (setq right-edge (heuristic-maximum-edge left-edge right-edge default-trend-chart-width))
  (setq bottom-edge (heuristic-maximum-edge top-edge bottom-edge default-trend-chart-height))
  (change-size-of-trend-chart trend-chart left-edge top-edge right-edge bottom-edge))

(def-class-method change-size-per-bounding-rectangle
    (graph left-edge top-edge right-edge bottom-edge mode)
  (declare (ignore mode))
  (setq right-edge
	(heuristic-maximum-edge
	  left-edge right-edge
	  ;; approximate default width, doesn't count margins
	  (get-slot-init-form 'graph-format 'minimum-graph-width)))
  (setq bottom-edge
	(heuristic-maximum-edge
	  top-edge bottom-edge
	  ;; approximate default height, doesn't count margins
	  (get-slot-init-form 'graph-format 'minimum-graph-height)))
  (change-size-of-graph graph left-edge top-edge right-edge bottom-edge))

(def-class-method change-size-per-bounding-rectangle
    (chart left-edge top-edge right-edge bottom-edge mode)
  (declare (ignore mode))
  (setq right-edge (heuristic-maximum-edge left-edge right-edge default-chart-width))
  (setq bottom-edge (heuristic-maximum-edge left-edge bottom-edge default-chart-height))
  (change-size-of-chart chart left-edge top-edge right-edge bottom-edge))




(defun find-image-plane-showing-workspace (workspace)
  (loop for image-plane in (stack-of-image-planes current-workstation-detail-pane)
	when (eq (workspace-on-image-plane? image-plane)
		 workspace)
	  return image-plane))



;;; `Fix-up-bounding-state-if-necessary-after-transfer' is the continuation
;;; called when dragging returns to a bounding state. It checks that things are
;;; still ok with the bounding state and if necessary fixes up some of that
;;; state's slots.  It can also exit the bounding state if it decides that
;;; things have gotten messed up.

(defun fix-up-bounding-state-if-necessary-after-transfer (bounding-context)
  (with-workstation-context-return-values (transfer-return-information)
    (let ((bounding-state (specific-structure-for-workstation-context
			    bounding-context)))
      (cond ((eq transfer-return-information ':abort))
	    (t
	     (let* ((new-workspace?			    ; probably can't be nil
		      (get-workspace-if-any
			(bounding-state-bounding-box bounding-state)))
		    (new-image-plane?
		      (and new-workspace?
			   (find-image-plane-showing-workspace new-workspace?))))
	       (when new-workspace?
		 (invoke-workspace-invalidation-handler-if-any
		   new-workspace? 'clone-or-transfer-target))
	       (cond ((eq new-workspace?
			  (workspace-for-bounding-box bounding-state)))
		     ;; Old one still good?

		     (new-image-plane?
		      (setf (bounding-image-plane bounding-state) new-image-plane?
			    (workspace-for-bounding-box bounding-state) new-workspace?))
		     (t
		      (abort-current-workstation-context 'bounding)))))))))



(defun fit-bounding-box-around-block (bounding-box block text-box-format)
  (erase-images-of-block bounding-box t)
  (change-edges-of-block bounding-box
			 (-w (left-edge-of-block block)
			     (text-box-left-border-width text-box-format))
			 (-w (top-edge-of-block block)
			     (text-box-top-border-width text-box-format))
			 (+w (right-edge-of-block block)
			     (text-box-right-border-width text-box-format))
			 (+w (bottom-edge-of-block block)
			     (text-box-bottom-border-width text-box-format)))
  (enlarge-workspace-for-block-rectangle-if-necessary
    bounding-box (superblock? bounding-box))
  (draw-images-of-block bounding-box t))


(define-event-handler enter-keys-in-bounding-state
                      ((bounding-state workstation-context-specifics))
  ;; If we have a default button in this dialog click it and return.
  (loop for subblock being each subblock of (bounding-dialog-workspace bounding-state)
        when (frame-of-class-p subblock 'default-action-button) do
    (highlight-or-unhighlight-button subblock nil)
    (funcall-method 'click subblock (left-edge-of-block subblock)
                                    (top-edge-of-block subblock))
    (return nil)))

;; This is almost identical to wrap-up-in-dialog-state...

(define-event-handler mouse-down-on-image-plane-in-bounding-state
    ((bounding-state workstation-context-specifics)
     workspace
     x-in-window
     y-in-window
     (x-in-workspace-for-bounding-box x-in-workspace)
     (y-in-workspace-for-bounding-box y-in-workspace)
     image-plane
     mouse-pointer)
  (let ((bounding-box (bounding-state-bounding-box bounding-state))
	(put-back-and-exit? nil))
    (loop for subblock being each subblock of workspace
	  do
      (cond
	((and
	   (eq subblock bounding-box)
	   (>r x-in-window
	       (-r (x-in-frame-transform
		     (left-edge-of-block bounding-box)
		     bounding-box
		     (bounding-image-plane bounding-state))
		   10))
	   (>r y-in-window
	       (-r (y-in-frame-transform
		     (top-edge-of-block bounding-box)
		     bounding-box
		     (bounding-image-plane bounding-state))
		   10))
	   (<r x-in-window
	       (+r (x-in-frame-transform
		     (right-edge-of-block bounding-box)
		     bounding-box
		     (bounding-image-plane bounding-state))
		   10))
	   (<r y-in-window
	       (+r (y-in-frame-transform
		     (bottom-edge-of-block bounding-box)
		     bounding-box
		     (bounding-image-plane bounding-state))
		   10)))
	 (multiple-value-bind (edge-or-corner? x-offset y-offset)
	     (select-edge-or-corner-of-bounding-box
	       bounding-box
	       x-in-window
	       y-in-window
	       (bounding-image-plane bounding-state))
	   (cond
	     ((null edge-or-corner?)
	      (enter-move-dragging-context	; if click in center, just move box
		bounding-box
		(-w x-in-workspace-for-bounding-box
		    (left-edge-of-block bounding-box))
		(-w y-in-workspace-for-bounding-box
		    (top-edge-of-block bounding-box))
		image-plane t))
	     (t
	      (start-tracking-mouse-in-current-workstation-context)
	      (push-back-mouse-motion-event)

	      (setf (edge-or-corner-of-bounding-box? bounding-state)
		    edge-or-corner?)
	      (setf (x-offset-from-bounding-box? bounding-state)
		    x-offset)
	      (setf (y-offset-from-bounding-box? bounding-state)
		    y-offset)
	      (setf (sizing-box-corner-x0 bounding-state)
		    (case edge-or-corner?
		      ((top-left bottom-left)
		       (left-edge-of-block bounding-box))
		      (t (right-edge-of-block bounding-box))))
	      
	      ;; if this this was selected on a different image
	      ;;   plane, change orientation (for dragging) to the
	      ;;   image plane clicked on: 
	      (setf (bounding-image-plane bounding-state)
		    image-plane)	; perhaps this should not allow
					;   clicking on other image
					;   planes at all?!
	      
	      (setf (sizing-box-corner-y0 bounding-state)
		    (case edge-or-corner?
		      ((top-left top-right)
		       (top-edge-of-block bounding-box))
		      (t (bottom-edge-of-block bounding-box)))))))
	 (return nil))
	((eq workspace
	     (bounding-dialog-workspace bounding-state))	; the dialog workspace
	 (cond
	   ((and 
	      (frame-of-class-p subblock 'button)
	      (let (x-in-workspace y-in-workspace)
		(with-image-plane-transform (image-plane)
		  (setf x-in-workspace
			(x-in-workspace x-in-window))
		  (setf y-in-workspace
			(y-in-workspace y-in-window)))
		(in-block-p subblock x-in-workspace y-in-workspace)))
	    (enter-button-down-context subblock image-plane)
	    (return nil)))))
	  finally
	    (if (eq workspace (bounding-dialog-workspace bounding-state))
		(enter-image-plane-dragging-context ; drag the dialog box
		  image-plane
		  (-r x-in-window
		      (left-edge-of-image-in-window image-plane))
		  (-r y-in-window
		      (top-edge-of-image-in-window image-plane))
		  t)
		(setq put-back-and-exit? t)))

    (when put-back-and-exit?
      (requeue-event-and-abort-workstation-context mouse-pointer))))

(define-event-handler mouse-up-in-bounding-state
    (mouse-pointer
      (bounding-state workstation-context-specifics))
  (mouse-motion-in-bounding-state mouse-pointer)
  (stop-tracking-mouse-in-current-workstation-context)
  (setf (edge-or-corner-of-bounding-box? bounding-state) nil))

(define-event-handler mouse-motion-in-bounding-state
    ((bounding-state workstation-context-specifics)
     (x-in-window x-in-window)
     (y-in-window y-in-window))
  (let* ((bounding-box
	   (bounding-state-bounding-box bounding-state))
	 (text-box-format
	   (text-box-format bounding-box))
	 (left-border-width			; of bounding box
	  (text-box-left-border-width text-box-format))
         (top-border-width
           (text-box-top-border-width text-box-format))
         (right-border-width
           (text-box-right-border-width text-box-format))
         (bottom-border-width
           (text-box-bottom-border-width text-box-format))
	 (edge-or-corner
	  (edge-or-corner-of-bounding-box? bounding-state))

	 ;; All this could be x/y-in-workspace-of-selection-focus magic
	 ;; arguments, if this context had selection focus.
	 (focus-workspace
	   (workspace-for-bounding-box bounding-state))
	 (focus-image-plane?
	   (image-plane-of-workspace focus-workspace))
	 (x-in-workspace-for-bounding-box
	   (and focus-image-plane?
		(x-in-workspace-coordinates x-in-window focus-image-plane?)))
	 (y-in-workspace-for-bounding-box
	   (and focus-image-plane?
		(y-in-workspace-coordinates y-in-window focus-image-plane?))))

    (cond
      ((null focus-image-plane?))
      ((and (bounding-state-constrained-height? bounding-state)
	    (memq edge-or-corner
		  '(top-left top-right bottom-left bottom-right)))
       (with-temporary-gensym-float-creation tag
	 (with-temporary-bignum-creation
	   (let* ((vertical-edge-of-bounding-box
		   (case edge-or-corner
		     ((top-left bottom-left)
		      (left-edge-of-block bounding-box))
		     (t (right-edge-of-block bounding-box))))
		  (horizontal-edge-of-bounding-box
		   (case edge-or-corner
		     ((top-left top-right)
		      (top-edge-of-block bounding-box))
		     (t (bottom-edge-of-block bounding-box))))
		  (x0
		   (sizing-box-corner-x0 bounding-state))
		  (y0
		   (sizing-box-corner-y0 bounding-state))
		  (negative-slope?
		   (memq edge-or-corner '(bottom-left top-right)))
		  (absolute-slope
		    (/e (maxe (coerce-to-gensym-float
				(bounding-state-constrained-height? bounding-state))
			      (coerce-to-gensym-float 1.0))
			(maxe (coerce-to-gensym-float
				(bounding-state-constrained-width? bounding-state))
			      (coerce-to-gensym-float 1.0))))
		  (m (if negative-slope?
			 (-e absolute-slope)
			 absolute-slope))
		  (x1 (-w x-in-workspace-for-bounding-box x0))	; delta x!
		  (y1 (-w y-in-workspace-for-bounding-box y0))	; delta y!
		  (x2
		   (/e (+e (coerce-to-gensym-float y1)
			   (/e (coerce-to-gensym-float x1)
			       m))
		       (+e m (/e (coerce-to-gensym-float 1) m))))
		  (y2 (*e m (coerce-to-gensym-float x2)))
		  (new-vertical-edge-of-bounding-box
		   (+w x0 (round x2)))		    ; Commonlisp ROUND?
		  (new-horizontal-edge-of-bounding-box
		   (+w y0 (round y2))))
	     
	     (cond
	       ((not (=w horizontal-edge-of-bounding-box
			 new-horizontal-edge-of-bounding-box))
		(case edge-or-corner
		  ((top-left top-right)
		   (if (<w new-horizontal-edge-of-bounding-box
			   (-w (bottom-edge-of-block bounding-box)
			       bottom-border-width
			       top-border-width))
		       (update-border-of-text-box
			 bounding-box nil
			 new-horizontal-edge-of-bounding-box nil nil)))
		  (t
		   (if (>w new-horizontal-edge-of-bounding-box
			   (+w (top-edge-of-block bounding-box)
			       bottom-border-width
			       top-border-width))
		       (update-border-of-text-box
			 bounding-box nil nil nil
			 new-horizontal-edge-of-bounding-box))))))
	     (cond
	       ((not (=w vertical-edge-of-bounding-box
			 new-vertical-edge-of-bounding-box))
		(case edge-or-corner
		  ((top-left bottom-left)
		   (if (<w new-vertical-edge-of-bounding-box
			   (-w (right-edge-of-block bounding-box)
			       left-border-width right-border-width))
		       (update-border-of-text-box
			 bounding-box
			 new-vertical-edge-of-bounding-box nil nil nil)))
		  (t 
		   (if (>w new-vertical-edge-of-bounding-box
			   (+w (left-edge-of-block bounding-box)
			       left-border-width
			       right-border-width))
		       (update-border-of-text-box
			 bounding-box nil nil
			 new-vertical-edge-of-bounding-box nil))))))))))
      (t
       (let* (new-edge
	      (text-box-to-be-bounded?
	       (if (and (block-to-be-bounded? bounding-state)
			(frame-of-class-p
			  (block-to-be-bounded? bounding-state)
			  'text-box))
		   (block-to-be-bounded? bounding-state)))
	      (text-box-format?
	       (if text-box-to-be-bounded?
		   (text-box-format text-box-to-be-bounded?)))
	      (maximum-text-box-width?
	       (if text-box-format?
		   maximum-text-box-width-or-height)))
	 (case edge-or-corner
	   ((left top-left bottom-left)
	    (setq new-edge
		  (minw x-in-workspace-for-bounding-box
			(-w (right-edge-of-block bounding-box)
			    left-border-width right-border-width 1)))
	    (if text-box-to-be-bounded?
		(setq new-edge
		      (maxw new-edge
			    (-w (-w (right-edge-of-block bounding-box)
				    right-border-width)
				maximum-text-box-width?))))
	    (if (not (=w new-edge (left-edge-of-block bounding-box)))
		(update-border-of-text-box bounding-box new-edge nil nil nil)))
	   ((right top-right bottom-right)
	    (setq new-edge
		  (maxw x-in-workspace-for-bounding-box
			(+w (left-edge-of-block bounding-box)
			    left-border-width right-border-width 1)))
	    (if text-box-to-be-bounded?
		(setq new-edge
		      (minw new-edge
			    (+w (+w (left-edge-of-block bounding-box)
				    left-border-width)
				maximum-text-box-width?))))
	    (if (not (=w new-edge (right-edge-of-block bounding-box)))
		(update-border-of-text-box bounding-box nil nil new-edge nil))))
	 (case edge-or-corner
	   ((top top-left top-right)
	    (setq new-edge
		  (minw (-w (bottom-edge-of-block bounding-box)
			    top-border-width bottom-border-width 1)
			y-in-workspace-for-bounding-box))
	    (if (not (=w new-edge (top-edge-of-block bounding-box)))
		(update-border-of-text-box bounding-box nil new-edge nil nil)))
	   ((bottom bottom-left bottom-right)
	    (setq new-edge
		  (maxw (+w (top-edge-of-block bounding-box)
			    top-border-width bottom-border-width 1)
			y-in-workspace-for-bounding-box))
	    (if (not (=w new-edge (bottom-edge-of-block bounding-box)))
		(update-border-of-text-box
		  bounding-box nil nil nil new-edge)))))))))


(define-event-handler mouse-down-on-close-box-widget-in-bounding-state
    (mouse-pointer
      (bounding-state workstation-context-specifics)
      x-in-window
      y-in-window
      image-plane
      workspace)
  (if (eq workspace (bounding-dialog-workspace bounding-state))
      (enter-close-box-widget-pending-context workspace image-plane)
      (requeue-event-and-abort-workstation-context mouse-pointer)))





;;; The function `Select-edge-or-corner-of-bounding-box' returns nil in case the
;;; position specified by (x-in-window, y-in-window) is not on the border, or,
;;; unless no-leeway-p is specified true, up to 10 window units from the inside
;;; border edge.  It is assumed that this function will be called only if the
;;; position is near to (or within) the bounding box. If nil is returned, then,
;;; it means the position is in the interior of the bounding box.  Othewise it
;;; return three values indicating which edge or corner and how far, in
;;; workspace units, we are from its outside edge.

;;; [NOTE: this has changed, 1/28/00, to take its x/y position args in window
;;; units.  The two callers had this information handy, and there seemed no
;;; reason to throw out the precision. So the callers are being changed
;;; simultaneously to pass in the x-in-window/y-in-window.  Note that the return
;;; offsets remain in workspace units.  The no-leeway-p arg was also added a
;;; this time based on the needs of the icon editor.  (MHD 1/28/00)]

(defun select-edge-or-corner-of-bounding-box
    (bounding-box x-in-window y-in-window image-plane &optional no-leeway-p)
  (with-raw-window-transform-and-draw-area
      ((gensym-window-for-image-plane image-plane))
    (with-nested-draw-area-of-pane? (image-plane)
      (on-image-plane-without-drawing (image-plane)
	(multiple-value-bind (edge-or-corner? x-offset y-offset) ; in window units
	  (let* ((border-width (bounding-box-border-width bounding-box))
		 ;; All following variables in window units:
		 (outside-left-edge
		   (x-in-window (left-edge-of-block bounding-box)))
		 (outside-top-edge
		   (y-in-window (top-edge-of-block bounding-box)))
		 (outside-right-edge
		   (x-in-window (right-edge-of-block bounding-box)))
		 (outside-bottom-edge
		   (y-in-window (bottom-edge-of-block bounding-box)))
		 (inside-left-edge
		   (x-in-window (+w (left-edge-of-block bounding-box) border-width)))
		 (inside-top-edge
		   (y-in-window (+w (top-edge-of-block bounding-box) border-width)))
		 (inside-right-edge
		   (x-in-window (-w (right-edge-of-block bounding-box) border-width)))
		 (inside-bottom-edge
		   (y-in-window (-w (bottom-edge-of-block bounding-box) border-width)))
		 (leeway (if no-leeway-p 0 10)))
	    (cond
	      ((<r x-in-window (+r inside-left-edge leeway))
	       (cond
		 ((<r y-in-window (+r inside-top-edge leeway))
		  (values 'top-left
			  (-r x-in-window outside-left-edge)
			  (-r y-in-window outside-top-edge)))
		 ((>r y-in-window (-r inside-bottom-edge leeway))
		  (values 'bottom-left
			  (-r x-in-window outside-left-edge)
			  (-r y-in-window outside-bottom-edge)))
		 (t
		  (values 'left (-r x-in-window outside-left-edge) 0))))
	      ((>r x-in-window (-r inside-right-edge leeway))
	       (cond
		 ((<r y-in-window (+r inside-top-edge leeway))
		  (values 'top-right
			  (-r x-in-window outside-right-edge)
			  (-r y-in-window outside-top-edge)))
		 ((>r y-in-window (-r inside-bottom-edge leeway))
		  (values 'bottom-right
			  (-r x-in-window outside-right-edge)
			  (-r y-in-window outside-bottom-edge)))
		 (t
		  (values 'right (-r x-in-window outside-right-edge) 0))))
	      ((<r y-in-window (+r inside-top-edge leeway))
	       (values 'top 0 (-r y-in-window outside-top-edge)))
	      ((>r y-in-window (-r inside-bottom-edge leeway))
	       (values 'bottom 0 (-r y-in-window outside-bottom-edge)))
	      (t nil)))
	  (if edge-or-corner?
	      (values
		edge-or-corner?
		(delta-x-in-workspace x-offset current-image-x-scale)
		(delta-y-in-workspace y-offset current-image-y-scale))))))))




;;; `Delete-blocks-for-operate-on-area-after-confirmation' is called out of the
;;; operate-on-area context to prompt for, and eventually execute, deletion of
;;; the list blocks, which should be the list of blocks found within the
;;; bounding box area (and appropriate for deletion).  Blocks should be made up
;;; of dragging conses.  Whether or not the user confirms the deletion, the list
;;; blocks gets recycled into the dragging cons pool.
;;;
;;; `Delete-blocks-for-operate-on-area-upon-confirmation' actually carries out
;;; the deletion of blocks upon confirmation by the user.  This function takes
;;; care to arrange not to have junction blocks within the area deleted.

(defun delete-blocks-for-operate-on-area-after-confirmation (blocks)
  (enter-dialog
    (copy-constant-wide-string #w"Delete all items inside the box?")
    nil nil
    'delete-blocks-for-operate-on-area-upon-confirmation
    (slot-value-list blocks)
    'reclaim-dragging-list-function
    (slot-value-list blocks)))


(defun delete-blocks-for-operate-on-area-upon-confirmation (blocks)
  (loop with junction-blocks-not-to-be-deleted = blocks
	with serial-number = (copy-frame-serial-number (current-frame-serial-number))
	with workspace? = (and (car blocks) (superblock? (car blocks)))
	for block in blocks
	do (delete-frame-after-checking-serial-number block serial-number)
	finally
	  (when workspace?
	    (invoke-workspace-invalidation-handler-if-any
	      workspace? 'delete))
	  (reclaim-frame-serial-number serial-number))
  (reclaim-dragging-list-function blocks))
    
  
  


;;; `List-blocks-within-area-of-workspace' prepares a dragging-cons list of
;;; blocks suitable for further handling by operate-on-area.  They are in order
;;; from top-most to bottom-most.

(defun prepare-blocks-for-operation-on-area
    (workspace left-edge top-edge right-edge bottom-edge
	       &optional transfer-case? clone-case?)
  (unless #+pre-g2-v5-licensing 
          (and clone-case?
	       (or (runtime-option-authorized-p)
		   (embedded-option-authorized-p)))
	  #-pre-g2-v5-licensing
	  nil
    (let ((result-blocks
	    (list-blocks-within-area-of-workspace
	      workspace left-edge top-edge right-edge bottom-edge
	      transfer-case? clone-case?)))
      (cond
	(transfer-case?
	 (delete-connections-of-blocks-within-area
	   result-blocks left-edge top-edge right-edge bottom-edge)
	 (reclaim-dragging-list-function result-blocks)
	 (list-blocks-within-area-of-workspace
	   workspace left-edge top-edge right-edge bottom-edge
	   transfer-case? clone-case?))
	(t
	 result-blocks)))))

;; You can't clone in runtime or embedded systems.  That's why this returns nil
;; in such systems when this is the clone case.  Consider either not having the
;; clone choice in such systems, or giving a warning that clone is suppressed in
;; such systems! (MHD 6/13/94)

;; The deletion happens without warning, notification, or confirmation.  That's
;; certainly going to be a major side effect in many situations.  Consider doing
;; one of these.  Note that TRANSFER choice is not even offered when an item has
;; external connections.  There should be something between "you can't transfer
;; at all" and "you can transfer -- no problem -- I'll just zap these here
;; connections for you".  Especially if these two different transfer operations
;; are to have the same name, they should have a more similar story on how they
;; relate to external connections.  Of course, everything must now be done in
;; the light of compatibility.... (MHD 6/13/94)



;;; The function `list-blocks-within-area-of-workspace' returns a new-consed
;;; dragging-list of the subblocks on the workspace which are entirely inside
;;; of the given rectangle.  The list is in order from topmost to bottommost.

(defun list-blocks-within-area-of-workspace
    (workspace left-edge top-edge right-edge bottom-edge
	       transfer-case? clone-case?)
  (let ((block-list? nil))
    (setq block-list?
	  (loop for block being each subblock of workspace
		
		when (and (block-inside-rectangle-p
			    block left-edge top-edge right-edge bottom-edge)
			  (or (not (or transfer-case? clone-case?))
			      (and (not (frame-of-class-p block 'workspace-name-box))
				   (not (proprietary-p block))))
			  (or clone-case?
			      (not (loose-end-p block))))
		  collect block using dragging-cons-function))
    ;; this list should not include any loose ends in which the other end of the connection
    ;; is not on the list
    (loop for block in block-list?
	  with blocks-to-delete? = nil
	  do
      (when (of-class-p block 'loose-end)
	;; we know that loose ends only have one connection, but the path
	;; makes life easier
	(loop for connection being each connection of block
	      do
	  (unless (memq (get-block-at-other-end-of-connection connection block)
			block-list?)
	    (gensym-push block blocks-to-delete?))))
	  finally
	    (when blocks-to-delete?
	      (loop for block in blocks-to-delete?
		    do
		(setq block-list?
		      (delete-item-from-list-and-reclaim-cons-cells
			block-list? block 'reclaim-dragging-cons-function nil)))
	      (reclaim-gensym-list blocks-to-delete?)))
    block-list?))





;;; `Delete-connections-of-blocks-within-area' deletes all connections of
;;; blocks-to-check that stray outside of the specified area, and replaces them
;;; with stubs.  Note that certain elements of blocks-to-check may end up being
;;; deleted as a side effect.  All elements of blocks that are junction blocks
;;; (instances of default-junction) that were already found within the area (on
;;; a prior search) are prevented from being deleted.

(defun delete-connections-of-blocks-within-area
    (blocks left-edge top-edge right-edge bottom-edge)
  (loop with junction-blocks-not-to-be-deleted = blocks ; Special Variable
	with frame-serial-number = (copy-frame-serial-number (current-frame-serial-number))
	for block in blocks
	when (not (frame-has-been-reprocessed-p block frame-serial-number))
	  do (delete-connections-of-block-not-within-area-of-workspace
	       block left-edge top-edge right-edge bottom-edge)
	  finally (reclaim-frame-serial-number frame-serial-number)))





;;; `Delete-connections-of-block-not-within-area-of-workspace' deletes all
;;; connections (down to stubs) of block that stray outside of the specified
;;; area, and that

(defun delete-connections-of-block-not-within-area-of-workspace
    (block left-edge top-edge right-edge bottom-edge)
  (loop with connections-to-check
	  = (loop for connection
		  being each connection of block
		  collect connection using gensym-cons)
	for connection in connections-to-check
	as block-at-other-end
	  = (get-block-at-other-end-of-connection connection block)
	when (not (block-inside-rectangle-p
		    block-at-other-end
		    left-edge top-edge right-edge bottom-edge))
	  do (delete-connection-to-stub connection)
	finally 
	  (reclaim-gensym-list connections-to-check)))





;; Lots of trouble in here with the menus of table slots.  In this situation
;; the menu shown to the user often has items drawn from three sources.  The
;; enclosing table, the slot, and finally the thing displayed in the slot.
;; The mechinisms that show such menus are confusing to all parties.

;; For example if you have menu choices on a quantitative variable, say plot,
;; and you select it in a slot do you show that or not?  Maybe something like
;;  "menu choice on quantitative variable represented via an attribute table include plot"

;; Desires
;; - submenu indicators (DONE)
;; - left justification (?)
;; - scrolling
;; - dimming
;; - push pin menus
;; - spacers between groups of menu items (DONE)
;; - control over menu order sorting and ones with explicit ordering
;; - class structure and declarative structure around menu items


;;;; System Procedures for Monitoring Operate on Area

;;; This facility is being introduced to support GDA having access to workspace
;;; edits using operate one area without having to add a new "whenever" facility
;;; to G2 before the release of 4.0.


(def-kb-specific-variable workspace-invalidation-handling-procedure?
    facilities nil nil nil)
(def-kb-specific-variable workspace-invalidation-handling-procedure-fsn?
    facilities nil nil reclaim-frame-serial-number)
(def-kb-specific-variable workspace-invalidation-handling-workspace-queue
    facilities nil nil reclaim-slot-value-list-function)
(def-kb-specific-variable workspace-invalidation-handling-fsn-queue
    facilities nil nil reclaim-slot-value-fsn-queue)
(def-kb-specific-variable workspace-invalidation-handling-window-queue
    facilities nil nil reclaim-slot-value-list-function)
(def-kb-specific-variable workspace-invalidation-handling-event-type-queue
    facilities nil nil reclaim-slot-value-list-function)

;; kb-props for proc-frame & proc-fsn

(defun-for-system-procedure g2-register-workspace-invalidation-handling-procedure
    (procedure)
  (cond
    ((of-class-p procedure 'procedure)
     (setq workspace-invalidation-handling-procedure? procedure)
     (frame-serial-number-setf workspace-invalidation-handling-procedure-fsn?
			       (frame-serial-number procedure))
     (make-evaluation-truth-value-function truth))
    (t
     (setq workspace-invalidation-handling-procedure? nil)
     (make-evaluation-truth-value-function falsity))))

(defun-for-system-procedure g2-get-invalid-workspace-to-handle ()
  (values (let ((frame (slot-value-pop
			 workspace-invalidation-handling-workspace-queue))
		(fsn (slot-value-pop
		       workspace-invalidation-handling-fsn-queue)))
	    (if (and frame
		     (not (frame-has-been-reprocessed-p
			    frame fsn))
		     (active-p frame))
		(progn
		  (reclaim-frame-serial-number fsn)
		  frame)
		(progn
		  (reclaim-frame-serial-number fsn)
		  (make-evaluation-truth-value-function falsity))))
;	  (slot-value-pop workspace-invalidation-handling-window-queue)
	  (slot-value-pop workspace-invalidation-handling-event-type-queue))
)

(defun-for-system-procedure g2-more-invalid-workspaces-to-be-handled ()
  (if workspace-invalidation-handling-workspace-queue
      (make-evaluation-truth-value-function truth)
      (make-evaluation-truth-value-function falsity)))

(defun invoke-workspace-invalidation-handler-if-any
    (workspace? event-type)
  (when (and workspace-invalidation-handling-procedure?
	     (not (frame-has-been-reprocessed-p
		    workspace-invalidation-handling-procedure?
		    workspace-invalidation-handling-procedure-fsn?)))
    (when workspace?
      (setq workspace-invalidation-handling-workspace-queue
	    (nconc
	      workspace-invalidation-handling-workspace-queue
		(slot-value-list workspace?)))
      (setq workspace-invalidation-handling-fsn-queue
	    (nconc
	      workspace-invalidation-handling-fsn-queue
	      (slot-value-list (copy-frame-serial-number (frame-serial-number workspace?)))))
;	(setq workspace-invalidation-handling-window-queue
;	      (nconc
;		workspace-invalidation-handling-window-queue
;		(slot-value-list window)))
      (setq workspace-invalidation-handling-event-type-queue
	    (nconc
	      workspace-invalidation-handling-event-type-queue
	      (slot-value-list event-type)))
      (start-procedure-invocation-in-place
	workspace-invalidation-handling-procedure? nil nil
	nil 0 0
	nil nil nil nil nil))))


;;;; G2-Side of Simple Dialogs

;; This code is here in order to be before its use in kb-merge and controls, but
;; not be in TW, which dialogs.lisp is.

(defvar simple-dialog-title? nil)
(defvar simple-dialog-fill-text-p t)
(defvar simple-dialog-plist? nil)

;;; The function `post-simple-dialog' requires the window has been put into
;;; native-simple-dialog workstation context for the returned result to be
;;; handled.

(defun post-simple-dialog (gensym-window handle message
					 ok-string cancel-string additional-string
					 default-button?)
  (when (native-simple-dialogs-p gensym-window)
    (let ((title (or simple-dialog-title? #w"")))
      (with-icp-window (gensym-window)
	(cond ((null simple-dialog-plist?)
	       (send-icp-simple-dialog
		 gensym-window handle title message
		 ok-string cancel-string additional-string
		 default-button? 0))
	      ((window-supports-simple-dialog-ex gensym-window)
	       (send-icp-simple-dialog-ex
		 gensym-window 'listbox handle title message simple-dialog-plist?))
	      (t
	       (dwarn "Simple dialog plist being ignored: ~s" simple-dialog-plist?)))))))

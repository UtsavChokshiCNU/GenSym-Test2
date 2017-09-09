;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module BOOKS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David and Lowell B. Hawkinson





;;;; Forward References in BOOKS


;; To BOOKS (variables defined later than they're used)

(declare-forward-reference current-logbook? variable)

;; To EDIT

(declare-forward-reference highlight-or-unhighlight-for-slot function)


;; To CONTROLS 

(declare-forward-reference make-button function)
(declare-forward-reference show-workspace function)


;; To FILES

(declare-forward-reference note-kb-state-change function)
(declare-forward-reference 
  g2-stream-open-for-output-handling-file-errors function)
(declare-forward-reference 
  g2-stream-open-for-appending-handling-file-errors function)


;; To FACILITIES:

(declare-forward-reference workspaces-can-be-shown-at-this-kb-level-p function)


;; To RUN:

(declare-forward-reference current-kb-pathname? variable)

;; To COMP-UTILS

(declare-forward-reference runnable-p-function function)

;; To STACK-KERN:

(declare-forward-reference check-user-defined-message-handler-arguments function)

(declare-forward-reference invoke-user-defined-message-handler function)

(declare-forward-reference pass-loop-check-for-user-defined-message-handler-p function)

;; To VIEW-G2

(declare-forward-reference inform-ui-client-interfaces-of-general-update function)

(declare-forward-reference send-ws-representations-item-virtual-attribute-change function)

;; To KB-SAVE2

(declare-forward-reference current-kb-serial-number variable)

;; To COMMANDS2
(declare-forward-reference use-native-logbook-p function)
(declare-forward-reference append-message-to-all-native-logbooks function)
(declare-forward-reference show-native-logbook function)
(declare-forward-reference hide-native-logbook function)
(declare-forward-reference note-native-logbook-preference-changed function)

;; To COMMANDS2
(declare-forward-reference use-native-message-board-p function)
(declare-forward-reference append-message-to-all-native-message-boards function)
(declare-forward-reference ensure-native-message-board function)
(declare-forward-reference show-native-message-board function)
(declare-forward-reference hide-native-message-board function)
(declare-forward-reference note-native-message-board-preference-changed function)

;; To SETS
(declare-forward-reference is-g2-save-module-flag-set function)
(declare-forward-reference g2-save-module-list variable)

;;;; Introduction to Logbooks and Message Boards



;;; G2, as it runs on-line, generates explanations and messages, as directed by
;;; explicit actions. Messages are produced from templates by filling in numeric
;;; values and names. Explanations show (1) the rules involved in deciding that a
;;; particular action (such as generating a message) should be taken and (2) the
;;; values of variables referred to in these rules. The values of variables are
;;; typically shown as trend graphs that plot several variables against time. The
;;; operator may, upon request, get a more detailed explanation than is normally
;;; given.

;;; Messages and explanations are logged, with timestamps, in a logbook, the most
;;; recent pages of which are stacked on the operator's display screen. All such
;;; operator interface may be sent to remote terminals, and to laser printers.

;; [from the 2/17/87 Product Description]








;;;; Books





;;; ... When a kb is saved, the book itself is saved but not its pages.  Books require
;;; a separate facility for saving.

(def-class (book entity)

  (stack-of-pages nil vector-slot system)	;not necessarily complete (see page number)

  (last-page-number				;not saved, but editable
    0 (type integer) do-not-save vector-slot system)

  (names-of-display-areas-to-put-new-pages-on	;saved in kb 
    nil (type list-of-names) vector-slot system)

  (title-of-book? nil (type string) vector-slot system)	;saved in kb

  (book-format nil (type format) save vector-slot system)	; OBSOLETE!!

  ;; lookup slots should be vector slots below at some point!
  (x-offset-for-next-page-of-this-book
    -5 lookup-slot system (type integer))
  (y-offset-for-next-page-of-this-book
    -28 lookup-slot system (type integer))

  (x-offset-for-this-book			; in workspace units
    10 lookup-slot system (type integer))
  (y-offset-for-this-book
    -10 lookup-slot system (type integer))

;  ;; the following are in workspace units (maybe! not used!!!)
;  (x-scale-for-top-page-of-this-book
;    #.(normalized-scale) lookup-slot system)
;  (y-scale-for-top-page-of-this-book
;    #.(normalized-scale) lookup-slot system)
;  (x-scale-for-buried-pages-of-this-book
;    #.(normalized-scale) lookup-slot system)
;  (y-scale-for-buried-pages-of-this-book
;    #.(normalized-scale) lookup-slot system)

;  (maximum-number-of-pages-to-show-in-this-book
;    3 lookup-slot system (type positive-integer))
;  (number-of-pages-to-shed-at-limit-in-this-book
;    1 lookup-slot system (type non-negative-integer))

;  (spacing-between-entries-in-this-book
;    10 lookup-slot system (type positive-integer))

;  (log-inform-messages-in-this-book?
;    nil lookup-slot system (type yes-or-no?))

;  (maximum-number-of-pages-to-keep-in-memory-in-this-book
;    200 lookup-slot system (type non-negative-integer))

  )

;; Make the slots vector slots here and below!



(def-class (logbook book)
  (names-of-display-areas-to-put-new-pages-on (detail-pane) vector-slot system))


(def-slot-value-writer format (slot-value)
  (let ((names-for-frame? (name-or-names-for-frame slot-value)))
    (if names-for-frame?
	(twrite-symbol
	  (if (atom names-for-frame?) names-for-frame? (car names-for-frame?)))
	(twrite-string "none"))))


;; At times, changes to logbook parameters should not be allowed (if, say, there were already
;; some pages there, unless perhaps we reformatted everything).

;; Make an icon description for (different kinds of) books!

;; Types integer, string, and list-of-names need to be defined!!

;; Get this in line with ML's slot values conventions!!





(def-class (page non-kb-workspace)
  (book-this-is-part-of nil vector-slot system)	;must be filled in 
  (page-number nil vector-slot system))		;must be filled in 

;; Need to have a slot value reclaimer for page-book cross references!

;; Consider also having previous-page? and next-page? slots.

;; At some point, we want to save books as saved kb's.  This will require a large
;; set of special capabilities, probably.  None of this exists right now.





(def-slot-value-reclaimer stack-of-pages (stack-of-pages book)
  stack-of-pages
  (loop while (stack-of-pages book)
	do
    (delete-frame (car (stack-of-pages book)))))

(def-slot-value-reclaimer book-this-is-part-of (book page)
  (setf (stack-of-pages book)
	(delete-slot-value-element page (stack-of-pages book))))


(def-class (logbook-page (item page) not-normally-transient)
  (date-of-logbook-page?
    nil vector-slot system
    (attribute-export-comment
      "Export: type (none or time), writable = false. Internally can be nil or a ~
	 gensym-time. If a time, all messages will be for that day only. What ~
	happens at midnight?")))

(def-system-frame logbook-parameters books
  
  (width-for-pages
    ; 340 ; was 340 until today.  (MHD 10/11/91)
    345 vector-slot system (type positive-integer))	; workspace units;  
  (height-for-pages 400 vector-slot system (type positive-integer))	;  does not include 
									;  margins

  (margin-for-pages 5 vector-slot system (type positive-integer))	; workspace units
  
  (x-offset-for-next-page -5 vector-slot system (type integer))	;workspace units
  (y-offset-for-next-page -28 vector-slot system (type integer))

  (x-offset-for-logbook	;workspace units
    10 vector-slot system (type integer))
  (y-offset-for-logbook
    -10 vector-slot system (type integer))

  ;; the following are in workspace units (maybe! not used!!!)
  (x-scale-for-top-page #.(normalized-scale) vector-slot system)
  (y-scale-for-top-page #.(normalized-scale) vector-slot system)
  (x-scale-for-buried-pages #.(normalized-scale) vector-slot system)
  (y-scale-for-buried-pages #.(normalized-scale) vector-slot system)

  (maximum-number-of-pages-to-show 3 vector-slot system (type positive-integer))
  (number-of-pages-to-shed-at-limit 1 vector-slot system (type non-negative-integer))

  (spacing-between-entries 10 vector-slot system (type positive-integer))

  (log-inform-messages? nil vector-slot system (type yes-or-no)) ;; see note with alias

  (maximum-number-of-pages-to-keep-in-memory
    200 vector-slot system (type non-negative-integer))

  (lift-logbook-to-top-when-new-pages-are-added?
    t						; I think nil would be a better 
    vector-slot system (type yes-or-no))	;   default, but this is compatible
						;   with 1.11B behavior.
						;   (MHD 1/20/90)
  (prefer-native-logbook t (type yes-or-no) vector-slot system save) ; 8.2r0 -fmw, 11/1/05

  (include-date-in-logbook-messages nil vector-slot system (type yes-or-no))
  ;; GENSYMCID-1124: TWNG : how to automatically have the native logbook at the bottom of the window (instead of left) ?
  (default-docking-position right (type docking-position-spec) vector-slot system save)
  )

;; Docking-position-spec, only four value supported: 'left 'right 'top 'bottom
(add-grammar-rules
  '((docking-position-spec 'top)
    (docking-position-spec 'bottom)
    (docking-position-spec 'left)
    (docking-position-spec 'right)))

(def-slot-value-writer docking-position-spec (value)
  (twrite-symbol value))

(define-slot-alias log-inform-messages log-inform-messages? logbook-parameters)

;; The following gives us the same user-visible slot-name for both
;; logbook-parameters and message-board-parameters. - jpg 9/7/07
(define-slot-alias include-date-in-messages include-date-in-logbook-messages
  logbook-parameters)

(def-slot-putter prefer-native-logbook (logbook-parameters-instance new-value initializing?)
  (let ((old-value (prefer-native-logbook logbook-parameters-instance)))
    (setf (prefer-native-logbook logbook-parameters-instance) new-value)
    (if (and (neq old-value new-value)
	     (system-table-installed-p logbook-parameters-instance)
	     (not initializing?))
	(note-native-logbook-preference-changed 'prefer-native new-value))
    new-value))

(def-slot-putter include-date-in-logbook-messages (logbook-parameters-instance new-value initializing?)
  (let ((old-value (include-date-in-logbook-messages logbook-parameters-instance)))
    (setf (include-date-in-logbook-messages logbook-parameters-instance) new-value)
    (if (and (neq old-value new-value)
	     (system-table-installed-p logbook-parameters-instance)
	     (not initializing?))
	(note-native-logbook-preference-changed 'include-date new-value))
    new-value))


(def-system-frame message-board-parameters books
  
  (initial-width-of-message-board		; default changed from 340 => 345 (MHD 10/11/91)
    345 vector-slot system (type positive-integer))	; workspace units; does 
  (initial-height-of-message-board
    400 vector-slot system (type positive-integer))	;  not include margins

  (spacing-between-message-board-entries
    10 vector-slot system (type positive-integer))

  (maximum-number-of-message-board-entries
    10 vector-slot system (type positive-integer))
  

  (highlight-new-messages?
    t vector-slot system (type yes-or-no))  ;; see note below with alias

  (minimum-display-interval
    indefinite vector-slot system (type sensor-validity-interval))

  (prefer-native-message-board t (type yes-or-no) vector-slot system save)

  (include-date-in-messages nil vector-slot system (type yes-or-no)))

(define-slot-alias highlight-new-messages highlight-new-messages?)

(def-slot-putter prefer-native-message-board (message-board-parameters-instance new-value initializing?)
  (let ((old-value (prefer-native-message-board message-board-parameters-instance)))
    (setf (prefer-native-message-board message-board-parameters-instance) new-value)
    (if (and (neq old-value new-value)
	     (system-table-installed-p message-board-parameters-instance)
	     (not initializing?))
	(note-native-message-board-preference-changed 'prefer-native new-value))
    new-value))

(def-slot-putter include-date-in-messages (message-board-parameters-instance new-value initializing?)
  (let ((old-value (include-date-in-messages message-board-parameters-instance)))
    (setf (include-date-in-messages message-board-parameters-instance) new-value)
    (if (and (neq old-value new-value)
	     (system-table-installed-p message-board-parameters-instance)
	     (not initializing?))
	(note-native-message-board-preference-changed 'include-date new-value))
    new-value))
  
(def-absent-slot-putter width-of-message-board (frame slot-value)
  (setf (initial-width-of-message-board frame) slot-value))

(def-absent-slot-putter height-of-message-board (frame slot-value)
  (setf (initial-height-of-message-board frame) slot-value))

;; These were around BEFORE 1.11B, but some old KBs were recently found
;; to have them. (MHD 12/13/89)


(def-absent-slot-putter left-margin-for-pages (frame slot-value)
  (setf (margin-for-pages frame) slot-value))

(def-absent-slot-putter top-margin-for-pages (frame slot-value)
  (declare (ignore frame slot-value)))

(def-absent-slot-putter right-margin-for-pages (frame slot-value)
  (declare (ignore frame slot-value)))

(def-absent-slot-putter bottom-margin-for-pages (frame slot-value)
  (declare (ignore frame slot-value)))

;; These were eliminated 7/10/89 in favor of one margin parameter.  Old frames
;; use the value of left-margin-for-pages as the new value for margin-for-
;; pages.  (MHD 7/10/89)



; the alias is the same as the analagous slot name for logbook parameters, and it's "nicer".
(define-slot-alias spacing-between-entries spacing-between-message-board-entries
  message-board-parameters)			     

(define-slot-alias maximum-number-of-entries maximum-number-of-message-board-entries
  message-board-parameters)



;;;; System Table Installation Bug


;;; Important change and bug fix around the slot putters for the system tables
;;; defined here.  The format parameters had been literally the same name as
;;; the system variables (global variables).  This interfered with the test
;;; used, system-table-installed-p, which relied on the global value binding
;;; of the variables to work properly.  The result was that within such slot
;;; putters (system-table-installed-p s) would always return true, where s
;;; is the name of a system table class and system variable.  This has been
;;; fixed today by renaming the formal parameter to have a suffix, "-instance",
;;; at the end. ...
;;;
;;; This affected the following system table classes and slots:
;;;
;;; Module BOOKS
;;; 
;;; logbook-parameters 		width-for-pages*
;;; 				margin-for-pages*
;;;
;;; message-board-parameters	initial-width-of-message-board*
;;;
;;; log-file-parameters		maximum-number-of-log-files*
;;; 				when-to-back-up-log-file
;;; 				when-to-close-log-file
;;; 				root-name-for-log-files*
;;; 				directory-for-log-files*
;;; 	
;;; Module CYCLES
;;;
;;; timing-parameters-instance	scheduler-mode*
;;;
;;;
;;; Module DEBUG
;;; 
;;; debugging-parameters	message-and-breakpoint-overrides*
;;; 				tracing-file*
;;; 				breakpoint-level*
;;; 				tracing-message-level*
;;; 				warning-message-level*
;;;
;;;
;;; Module FACILITIES
;;;
;;; color-parameters		colors-on-1st-level-color-menu
;;; 				colors-on-2nd-level-color-menu
;;;
;;;
;;; Module FILTERS
;;;
;;; kb-restrictions		simulated-optional-modules*
;;; 				initial-g2-user-mode-for-this-kb*
;;; 				global-keyboard-command-user-restrictions*
;;; 				main-menu-user-restrictions*
;;;
;;;
;;; Module MENUS
;;; 
;;; language-parameters		current-language-if-other-than-default?
;;;
;;;
;;; Module PRINTING
;;; 
;;; printer-setup		printing-details*
;;; 				page-layout*
;;; 				print-spooling*
;;; 				
;;; Module SETS
;;;
;;; inference-engine-parameters	truth-threshold
;;;
;;;
;;; Module SIMULATE5
;;;
;;; simulation-parameters	external-simulator-configuration*
;;; 				simulation-parameters-instance*
;;;
;;;
;;; Module VARIABLES
;;; 
;;; data-server-parameters	data-server-aliases*
;;; 				g2-meter-data-service-on?*
;;;
;;; * indicates that the slot putter in question uses the predicate
;;; system-table-installed-p.
;;; 
;;; (MHD 6/30/93)

(def-slot-putter width-for-pages (logbook-parameters-instance new-value initializing?)
  (setf (width-for-pages logbook-parameters-instance)
	(maxf 50 (minf 1000 new-value)))	; restrict to reasonable range
  (if (and (system-table-installed-p logbook-parameters-instance)
	   (not initializing?))
      (update-message-format-for-books-per-logbook-parameters))
  (width-for-pages logbook-parameters-instance))


(def-slot-putter margin-for-pages (logbook-parameters-instance new-value initializing?)
  (setf (margin-for-pages logbook-parameters-instance)
	(maxf 0 (minf 25 new-value)))	; restrict to reasonable range
  (if (and (system-table-installed-p logbook-parameters-instance)
	   (not initializing?))
      (update-message-format-for-books-per-logbook-parameters))
  (margin-for-pages logbook-parameters-instance))

;; New slot putter. (MHD 10/8/91)  

;; NOTE: the other two of these slot putters were revised extensively
;; today.  (MHD 10/8/91)


(def-slot-putter initial-width-of-message-board
		 (message-board-parameters-instance new-value initializing?)
  (setf (initial-width-of-message-board message-board-parameters-instance)
	(maxf 50 (minf 1000 new-value)))	; restrict to reasonable range
  (if (and (system-table-installed-p message-board-parameters-instance)
	   (not initializing?))
      (update-message-format-for-message-board-per-message-board-parameters))
  (initial-width-of-message-board message-board-parameters-instance))





(def-class-method install-system-table (logbook-parameters)
  (update-message-format-for-books-per-logbook-parameters))


(def-class-method deinstall-system-table (logbook-parameters)
  ; (restore-message-format-for-books-to-default-values)  ; IMPLEMENT!!
  )

(defun update-message-format-for-books-per-logbook-parameters ()
  (change-standard-format-frame-slot
    'message-format-for-books 'minimum-format-width-for-text-cell
    (-f (width-for-pages logbook-parameters)
	(margin-for-pages logbook-parameters))))





(def-class-method install-system-table (message-board-parameters)
  (update-message-format-for-message-board-per-message-board-parameters))

;; Note that the deinstall-system-table is not really needed, for either
;; message-board-parameters or logbook-parameters, since the install-
;; system-table can be relied on to do the right thing, i.e., to undo
;; side effects it had the last time it was called as appropriate.
;; (MHD 10/11/91)




(defun update-message-format-for-message-board-per-message-board-parameters ()
  (change-standard-format-frame-slot
    'message-format-for-message-board 'minimum-format-width-for-text-cell
    (-f (initial-width-of-message-board message-board-parameters)
	;; Ignores existing message board instance, if any,
	;; since any non-default setting it may have would
	;; never be saved in the KB anyway.
	(get-slot-init-form 'message-board 'workspace-margin))))


;; Helper functions for message-board & logbook enable/disable status query

(defun is-operator-logbook-enabled (workstation)
  (let* ((gensym-window (window-for-workstation workstation))
         (icp-socket (icp-socket-for-gensym-window? gensym-window)))
    (or (null icp-socket)
        (eq (get-remote-icp-version-info-value icp-socket 'operator-logbook-enabled 1) 1))))

(defun is-message-board-enabled (workstation)
  (let* ((gensym-window (window-for-workstation workstation))
         (icp-socket (icp-socket-for-gensym-window? gensym-window)))
    (or (null icp-socket)
        (eq (get-remote-icp-version-info-value icp-socket 'message-board-enabled 1) 1))))


;; The user should get some indication that his page width was rejected if it was
;; less than 50 or more than 1000.  

;; Do constraints on all of these!  (This is a few hours work!)  Have as possible
;; value "standard" or "default" or "system default"!?

;; Consider also having a log book title and a page header, which might not only be
;; a fixed string but may also have time, date, site, etc., information.  (Time and
;; date stuff might also go w/individual message.)

;; Consider also having an index of "categories" (?) of messages so the user could
;; quickly scan and retrieve.

;; Consider putting here also position of log book in pane (and/or which pane it's in),
;; but this will probably want to be decided at a higher level.

;; Consider parameterizing a way of getting rid of pages after they are too old.







;;; The function `post-message-in-book' posts the block, which should be a
;;; message instance, on the given book, creating new book pages as needed.
;;; The book page (a workspace) on which the message was finally posted
;;; is returned.

(defun post-message-in-book (block book)
  (let* ((top-edge-for-block nil)
	 (last-page? nil)
	 (current-page
	   (if (or (null (setq last-page? (car (stack-of-pages book))))
		   (not (same-gensym-date-p	; GENERALIZE FOR NON-LOGBOOKS!!
			  (date-of-logbook-page? last-page?) gensym-time))
		   (>w (+w
			 (setq top-edge-for-block
			       (+w
				 (loop for subblock being each subblock of last-page?
				       maximize
				       (bottom-edge-of-block subblock) using maxf)
				 (spacing-between-entries logbook-parameters)))
			 (height-of-block block))
		       (-w (bottom-edge-of-block last-page?)
			   (workspace-margin last-page?))))
	       (let ((page
		       (make-workspace
			 'logbook-page		; GENERALIZE FOR NON-LOGBOOKS!!
			 nil nil (margin-for-pages logbook-parameters)
			 (width-for-pages logbook-parameters)
			 (height-for-pages logbook-parameters))))
		 (setf (book-this-is-part-of page) book)
		 (setf (stack-of-pages book)
		       (slot-value-cons page (stack-of-pages book)))
		 (setf (page-number page)	       ; COULD BECOME A BIGNUM!!
		       (atomic-incf (last-page-number book)))
		 (setf (date-of-logbook-page? page) gensym-time)
		 ;; Here maybe delete excess pages if over limit!
		 (setq top-edge-for-block
		       (+w (add-running-head-elements book page)
			   (spacing-between-entries logbook-parameters)))
		 
		 ;; This just displays the just-added page, and may also delete
		 ;; views (image planes) if there are too many, as specified by
		 ;; logbook-parameters.  (It does not delete any actual pages:
		 ;; the form after this takes care of that.)
		 (loop for workstation in workstations-in-service
		       unless (use-native-logbook-p (window-for-workstation workstation))
			 do (for-workstation (workstation)
			      (add-page-to-display-of-book       ; IMPROVE! *
				page book current-workstation-detail-pane)))

		 ;; This deletes any pages that are in excess of limits
		 ;; specified by logbook-parameters.
		 (prune-logbook-pages-to-maximum book)
		 page)
	       last-page?)))

    (add-to-workspace
      block current-page
      (+w (left-edge-of-block current-page)
	  (workspace-margin current-page))
      top-edge-for-block t t)

    (append-message-to-all-native-logbooks block)

    current-page))

;; This would probably want to make use of a variant of add-subblock that puts
;; them at the end of the subblocks if such a variant were available.  (See
;; add-subblock.)  That would make the workspace draw subblocks from top to
;; bottom rather than bottom to top.  One could also nreverse the subblocks
;; of the previous page when going on to the next page, but that would be too
;; ugly.  And it would be less efficient, assuming that the variant of add-
;; subblock made use of a tail pointer for efficient adding at the end.

;; * Improve this for the case where the previous page is not there because the
;; user has scrolled back to look at previous pages.  Right now, if a new page
;; happens to be needed, it will destroy the current view in favor of a new
;; "normalized" view.  FIX!!





;;; Add-running-head-elements ... returns the maximum bottom edge of all of the
;;; blocks that were added as elements of the running head for page.

(defun add-running-head-elements (book page)
  (let* ((title-heading
	   (make-running-head
	     (copy-text-string (or (title-of-book? book) ""))))
	 (date-heading
	   (make-running-head
	     (if (include-date-in-logbook-messages logbook-parameters)
		 (copy-text-string "")
		 (twith-output-to-text-string
		   (multiple-value-bind (seconds minutes hours day month year)
		       (if system-is-running
			   (decode-gensym-time gensym-time)
			   (get-decoded-real-time))
		     (declare (ignore seconds minutes hours))
		     (print-decoded-date day month year))))))
	 (down-arrow
	   (let ((down-arrow (make-button 'down-arrow-button))) ;; for-use-by-system?
	     (set-slot-value down-arrow 'button-action? 'do-arrow-action)
	     (set-slot-value
	       down-arrow 'button-action-data? (slot-value-list down-arrow t))
	     down-arrow))
	 (up-arrow
	   (let ((up-arrow (make-button 'up-arrow-button))) ;; for-use-by-system?
	     (set-slot-value up-arrow 'button-action? 'do-arrow-action)
	     (set-slot-value
	       up-arrow 'button-action-data? (slot-value-list up-arrow nil))
	     up-arrow))
	 (page-number-heading
	   (make-page-number
	     (tformat-text-string "Page ~d" (page-number page))))
	 (workspace-margin (workspace-margin page))
	 (top-edge-for-elements
	   (+w (top-edge-of-block page) workspace-margin)))
    (add-to-workspace
      title-heading page
      (-w (+w (left-edge-of-block page) workspace-margin)
	  (left-edge-of-block title-heading))
      top-edge-for-elements)
    (add-to-workspace
      date-heading page
      (maxw
	(+w (right-edge-of-block title-heading) 7)
	(-w (+w (left-edge-of-block page)
		(halfw (width-of-block page)))
	    (halfw (width-of-block date-heading))))
      top-edge-for-elements)
    (add-to-workspace
      down-arrow page
      (maxw
	(+w (right-edge-of-block date-heading) 7)
	(-w (-w (right-edge-of-block page) workspace-margin)
	    (+w (width-of-block down-arrow)
		5
		(width-of-block up-arrow)
		8
		(width-of-block page-number-heading))))
      top-edge-for-elements)
    (add-to-workspace
      up-arrow page
      (+w (right-edge-of-block down-arrow) 5)
      top-edge-for-elements)
    (add-to-workspace
      page-number-heading page
      (+w (right-edge-of-block up-arrow) 8)
      top-edge-for-elements)
    (loop for subblock being each subblock of page
	  maximize (bottom-edge-of-block subblock) using maxf)))





;;; Do-arrow-action ...

(defun do-arrow-action (arrow forward?)
  (declare (special current-image-plane-for-button))	; forward ref. to CONTROLS
  (let* ((page (get-workspace-if-any arrow))
	 (book (book-this-is-part-of page))
	 (image-plane current-image-plane-for-button)
	 (pane (pane-for-image-plane image-plane))
	 (image-planes-with-pages-in-pane
	   (get-image-planes-with-pages-in-pane pane book t))
	 (stack-of-pages (stack-of-pages book))
	 (first-image-plane-displaying-page
	   (car (cdr image-planes-with-pages-in-pane)))
	 (first-page-displayed
	   (workspace-on-image-plane?
	     first-image-plane-displaying-page)))
    (cond
      ((eq (car (if forward?
		    stack-of-pages
		  (last stack-of-pages)))
	   page)
       nil)
      (forward?
	(loop for ll = nil then l
	      as l on stack-of-pages
	      when (eq (car l) first-page-displayed)
	        return
		  (if (<f (length ll)
			  (halff (length image-planes-with-pages-in-pane)))
		      (rotate-logbook-pages pane t)
		    (loop for page in ll
			  for (nil image-plane)
			      on image-planes-with-pages-in-pane
			      by #'cddr
			  do (transform-image
			       image-plane page
			       nil nil nil nil nil nil nil nil)
			  finally (return t)))))
      (t
	(loop as l on stack-of-pages
	      when (eq (car l) first-page-displayed)
	        return
		  (if (<f (length (cdr l))
			  (halff (length image-planes-with-pages-in-pane)))
		      (rotate-logbook-pages pane nil)
		      (loop for page in (cdr l)
			    for (nil image-plane)
				on image-planes-with-pages-in-pane
				by #'cddr
			    do (transform-image
				 image-plane page
				 nil nil nil nil nil nil nil nil)
			    finally (return t))))))
    (reclaim-gensym-list image-planes-with-pages-in-pane)))






;;; Rotate-list-of-image-planes ...

(defun rotate-list-of-image-planes (list-of-image-planes)
  (loop for image-plane in list-of-image-planes
	collect (workspace-on-image-plane? image-plane)
	  into list-of-workspaces using gensym-cons
	finally (loop for l on list-of-image-planes
		      as workspace in list-of-workspaces
		      do (transform-image
			   (car (or (cdr l) list-of-image-planes))
			   workspace nil nil nil nil nil nil nil nil))
		(reclaim-gensym-list list-of-workspaces)))





;;; Rotate-logbook-pages ...

(defun rotate-logbook-pages (pane &optional backwards?)
  (loop for image-plane in (stack-of-image-planes pane)
	as workspace? = (workspace-on-image-plane? image-plane)
	when (and workspace? (frame-of-class-p workspace? 'logbook-page))
	  collect image-plane into list-of-image-planes using gensym-cons
	finally (if (not backwards?)
		    (setq list-of-image-planes (nreverse list-of-image-planes)))
		(rotate-list-of-image-planes list-of-image-planes)
		(reclaim-gensym-list list-of-image-planes)))





;;; Get-image-planes-with-pages-in-pane ... gets a gensym list of a page number
;;; alternating with an image plane showing the page corresponding to that page
;;; number in increasing or decreasing order (according to decreasing?).

(defun get-image-planes-with-pages-in-pane (pane book decreasing?)
  (loop with page-numbers-and-image-planes-so-far-in-order = nil
	for image-plane in (stack-of-image-planes pane)
	as workspace? = (workspace-on-image-plane? image-plane)
	as page-number?
	   = (if (and workspace?
		      (frame-of-class-p workspace? 'page)
		      (eq (book-this-is-part-of workspace?) book))
		 (page-number workspace?))
	when page-number?
	  do (loop with listed-page-number-and-image-plane
		     = (gensym-list page-number? image-plane)
		   for ll = nil then l
		   as l = page-numbers-and-image-planes-so-far-in-order
			then (cddr l)
		   when (or (null l)
			    (if decreasing?
				(> page-number? (car l))
				(< page-number? (car l))))
		     do (setf (cddr listed-page-number-and-image-plane) 
			      l)
			(if ll 
			    (setf (cddr ll)
				  listed-page-number-and-image-plane)
			    (setq page-numbers-and-image-planes-so-far-in-order
				  listed-page-number-and-image-plane))
			(return nil))
	finally (return page-numbers-and-image-planes-so-far-in-order)))







#+unused
(defun put-page-at-beginning-of-display-of-book-in-pane (page book pane)
  (let* ((page-numbers-and-image-planes-in-order
	   (get-image-planes-with-pages-in-pane pane book t)))
    (cond
      ((not (null page-numbers-and-image-planes-in-order))
       (let ((workspace-to-shift 
	       (workspace-on-image-plane?
		 (car (cdr page-numbers-and-image-planes-in-order)))))
	 (transform-image 
	   (car (cdr page-numbers-and-image-planes-in-order))
	   page nil nil nil nil nil nil nil nil)
	 (loop for (nil image-plane) 
	       on (cddr page-numbers-and-image-planes-in-order)
		   by #'cddr 
	       do (transform-image
		    image-plane
		    (prog1 workspace-to-shift 
		      (setq workspace-to-shift 
			    (workspace-on-image-plane? image-plane)))
		    nil nil nil nil nil nil nil nil))
	 (delete-frame workspace-to-shift))	       ; temp!!!
       (reclaim-gensym-list page-numbers-and-image-planes-in-order)))))






;;; `Add-page-to-display-of-book'

;;; ... If the value of the lift-logbook-to top-when-new-pages-are-added?
;;; slot of the logbook parameters is true, then the image planes showing
;;; logbook pages are brought to top of the stack, in the same order, by
;;; this function.

;;; When a new page is added, its image plane is required to be visible
;;; by calling require-that-image-plane-be-visible, regardless of logbook
;;; parameters which might otherwise have them be shown outside of the pane.

;;; When a new page is added and there is a previous page, ...
;;; 
;;; When all pages are the same size, it should appear as though the offset
;;; for new pages is measured FROM the inside edge of the side of the previous
;;; page closest to the border of the window TO the outside edge of the
;;; new page in the side closest to the border of the window.
;;;
;;; Visually, a way to think about this is that the width of the white strip
;;; showing between the border of the new page and the old page always equals
;;; the absolote value of the offset.
;;;
;;; For example, if x-offset-for-new-pages is -5, then a new pages is added
;;; with its outside right edge 5 pixels to the left of the previous page's
;;; inside right edge.  For another example, If x-offset-for-new-pages is 5,
;;; then the new page is added with its outside left edge 5 pixels to the
;;; right of the inside left edge of the previous page.
;;;
;;; Note that the offsets are not subject to scaling, but that a new page
;;; inherits the x/y scales of the previous page.  Thus, at reduced scales,
;;; the spacing between pages may appear to grow wider.

;;; IMPORTANT CHANGE: This no longer deletes pages, i.e., the workspaces, which
;;; are shared among all the windows. This only puts up and possibly deletes the
;;; image planes showing the pages.  The deletion of the pages themselves, i.e.,
;;; to be within the maximum limits, now happens in post-message-in-book, the
;;; principle caller of this function, after the calls to this function (for
;;; each workstation) have been done. It calls (new function)
;;; prune-logbook-pages-to-maximum, adapted from code that previously was in
;;; this function.  This change fixes the bug (HQ-4744572 "Memory Leak when
;;; posting to operator and all g2-windows are set to hide the logbook") that if
;;; this function was exited early on all workstations (or if there were no
;;; workstations), the excess pages were never being deleted, and memory was
;;; constantly being chewed up. Changed on main line (8.0 development) as of
;;; 3/26/04. -mhd & ajs, 3/26/04

(defun add-page-to-display-of-book (page book pane)
  ;; first: exit right out if showing the logbook is not allowed for this
  ;; G2 window 
  (let* ((gensym-window (gensym-window-for-pane pane))
         (workstation (workstation-this-is-on gensym-window))
         (g2-window? (g2-window-for-this-workstation? workstation)))
    (when (or (and g2-window?
                   (not (show-operator-logbook-in-this-window? g2-window?)))
              (not (is-operator-logbook-enabled workstation)))
      (return-from
	add-page-to-display-of-book
	nil)))
  ;; If not exiting early, do actually add the page to the display:
  (let* ((maximum-number-of-pages-to-show
	   (maximum-number-of-pages-to-show logbook-parameters))
	 (x-offset-for-next-page
	   (x-offset-for-next-page logbook-parameters))
	 (y-offset-for-next-page
	   (y-offset-for-next-page logbook-parameters))
	 (x-offset-for-logbook
	   (x-offset-for-logbook logbook-parameters))
	 (y-offset-for-logbook
	   (y-offset-for-logbook logbook-parameters))
	 (number-of-pages-to-shed-at-limit
	   (number-of-pages-to-shed-at-limit
	     logbook-parameters)))
    (let* ((page-numbers-and-image-planes-in-order	; gets recycled at the end
	     (get-image-planes-with-pages-in-pane pane book t))
	   (number-of-pages-on-image-planes
	     (halff (length page-numbers-and-image-planes-in-order))))
      (cond
	((=f number-of-pages-on-image-planes 0)
	 (let* ((image-plane
		  (get-available-image-plane
		    pane
		    (lookup-frame-description-reference-of-frame-style
		      'default-workspace-frame-style
		      'default-workspace-frame-style)
		    nil))
		(x-in-window
		  (if (>r x-offset-for-next-page 0)
		      (+r (left-edge-of-pane-in-window image-plane)
			  x-offset-for-logbook)
		      (-r (right-edge-of-pane-in-window image-plane)
			  x-offset-for-logbook)))
		(y-in-window
		  (if (>=r (-w y-offset-for-next-page) 0)
		      (+r (top-edge-of-pane-in-window image-plane)
			  (-w y-offset-for-logbook))
		      (-r (bottom-edge-of-pane-in-window image-plane)
			  (-w y-offset-for-logbook))))
		(x-in-workspace
		  (if (>r x-offset-for-next-page 0)
		      (left-edge-of-block page)
		      (right-edge-of-block page)))
		(y-in-workspace
		  (if (>=r (-w y-offset-for-next-page) 0)
		      (top-edge-of-block page)
		      (bottom-edge-of-block page))))	     
	   (transform-image
	     image-plane page nil nil nil nil
	     x-in-workspace y-in-workspace x-in-window y-in-window)
	   (require-that-image-plane-be-visible image-plane)))
	((<f number-of-pages-on-image-planes
	     maximum-number-of-pages-to-show)
	 (let* ((previous-image-plane
		  (car (cdr page-numbers-and-image-planes-in-order)))
		(image-x-scale (image-x-scale previous-image-plane))
		(image-y-scale (image-y-scale previous-image-plane))
		(image-plane
		  (new-get-available-image-plane
		    pane
		    (frame-description-reference-of-image-plane
		      previous-image-plane)
		    'above
		    previous-image-plane))
;		  (get-available-image-plane-on-top-of-another 
;		    pane
;		    previous-image-plane
;		    (frame-description-reference-of-image-plane
;		      previous-image-plane)))
		(screen-offset-between-pages 3)
		(x-in-window
		  (+r (+r (left-edge-of-image-in-window previous-image-plane)
			  screen-offset-between-pages
			  x-offset-for-next-page)))
		(y-in-window
		  (-r (+r (top-edge-of-image-in-window previous-image-plane)
			  screen-offset-between-pages)
		      y-offset-for-next-page))
		(x-in-workspace
		  (left-edge-of-block page))
		(y-in-workspace
		  (top-edge-of-block page)))
	   (transform-image
	     image-plane page 
	     image-x-scale image-y-scale nil nil
	     x-in-workspace y-in-workspace x-in-window y-in-window)
	   (require-that-image-plane-be-visible image-plane)))
	(t
	 (loop with number-to-delete
		 = (maxf 0
			 (minf (-f number-of-pages-on-image-planes 1)
			       (maxf
				 (-f number-of-pages-on-image-planes
				     maximum-number-of-pages-to-show)
				 number-of-pages-to-shed-at-limit)))
;		   as x = (y-or-n-p "~d" number-to-delete)
	       for l on page-numbers-and-image-planes-in-order
		     by #'cddr
	       as i from 1
	       until (>f i number-to-delete)
	       finally
		 (loop for trailer
		       on page-numbers-and-image-planes-in-order
			   by #'cddr
		       with number-of-workspaces-to-keep = (-f (halff (length l)) 1)
		       as i from 1
		       if (<=f i number-of-workspaces-to-keep)
			 collect (workspace-on-image-plane? (car (cdr trailer)))
			   into workspaces-to-shift using gensym-cons
		       else
			 collect (workspace-on-image-plane? (car (cdr trailer)))
			   into workspaces-to-remove-from-display using gensym-cons
		       finally
			 (transform-image 
			   (car (cdr l)) page
			   nil nil nil nil nil nil nil nil)
; see alternative to the following loop below it:
			 (loop with image-planes-to-delete-in-bottom-up-order-so-far = nil
			       for image-plane in (stack-of-image-planes pane)	; in top down order
			       do (if (loop for ll
					    on page-numbers-and-image-planes-in-order
						by #'cddr
					    until (eq ll l)
					    thereis (eq (car (cdr ll)) image-plane))
				      (setq image-planes-to-delete-in-bottom-up-order-so-far
					    (gensym-cons
					      image-plane
					      image-planes-to-delete-in-bottom-up-order-so-far)))
			       finally
				 (loop for image-plane
					   in image-planes-to-delete-in-bottom-up-order-so-far
				       do (delete-image-plane image-plane))
				 (reclaim-gensym-list
				   image-planes-to-delete-in-bottom-up-order-so-far))
; simpler alternative, but it may refresh image planes from below that are about to be deleted:
;			   (loop for ll
;				   on page-numbers-and-image-planes-in-order
;				   by #'cddr
;				 until (eq ll l)
;				 do (delete-image-plane (car (cdr ll))))
; THERE SHOULD BE A WAY TO TELL PANES THAT AN IMAGE PLANE IS ABOUT TO BE TRANSFORMED AND SO
;   NOT TO BOTHER REFRESHING IT FROM BELOW!!!  (Lacking that (1) we need the complicated alternative
;   above and (2) there will have been unnecessary refreshing by the previous loop of image planes
;   transformed in the following loop if any parts of them were exposed by deleting planes higher
;   up!  That could, at present, only be avoided by putting the following before the previous; but that
;   is traded off for the advantage of exposing the newest page first before going off and shifting
;   the old pages to lower image planes.)
			 (loop for workspace in workspaces-to-shift
			       for ll = (cddr l) then (cddr ll)
			       do (transform-image
				    (car (cdr ll)) workspace
				    nil nil nil nil nil nil nil nil))
			 (reclaim-gensym-list workspaces-to-shift)
			 (reclaim-gensym-list workspaces-to-remove-from-display)))))
      (reclaim-gensym-list page-numbers-and-image-planes-in-order)
      nil)
    (if (lift-logbook-to-top-when-new-pages-are-added? logbook-parameters)
	(if (lift-logbook-to-top-when-new-pages-are-added? logbook-parameters)
	    ;; the following could be made more efficient, and should be!
	    ;; (MHD 1/31/90)
	    (loop with page-numbers-and-image-planes-in-order	; to be recycled
		    = (get-image-planes-with-pages-in-pane pane book t)
		  for (nil image-plane)
		  on page-numbers-and-image-planes-in-order
		      by #'cddr
		  as new-position-index from 0
		  do (loop for existing-image-plane in (stack-of-image-planes pane)
			   as old-position-index from 0
			   when (eq existing-image-plane image-plane)
			     return
			     (revise-pane
			       pane
			       image-plane
			       (-f new-position-index old-position-index)
			       nil))
		  finally
		    (reclaim-gensym-list
		      page-numbers-and-image-planes-in-order))))))



;;; The function `prune-logbook-pages-to-maximum' ensures that no more than the
;;; maximum number of pages, as specified by logbook-parameters, exists.

(defun prune-logbook-pages-to-maximum (book)
  (loop with maximum-number-of-pages-to-keep
	  = (maxf (maximum-number-of-pages-to-show
		    logbook-parameters)
		  (maximum-number-of-pages-to-keep-in-memory
		    logbook-parameters))
	while
	  (loop for page in (stack-of-pages book)
		as count from 1
		when (>f count
			 maximum-number-of-pages-to-keep)
		  do
		    (delete-frame page)
		    (return t))))





;;; Neatly-stack-logbook-pages-in-pane gets rid of all logbook pages in pane,
;;; and then displays all the available pages (up to the limit specified by
;;; maximum-number-of-pages-to-show of logbook-parameters) in pane.

(defun neatly-stack-logbook-pages-in-pane (pane book)

  ;; Hide all logbook pages there first:
  
  (hide-all-logbook-pages-in-pane pane)
  

  ;; Display the maximum number of pages permissible (per logbook
  ;; parameters) in pane at proper locations.
  (unless (use-native-logbook-p (gensym-window-for-pane pane))
    (loop for index
	  from (1-f (maximum-number-of-pages-to-show logbook-parameters))
	  downto 0	
	  as page? = (nth index (stack-of-pages book))
	  when page?
	    do (add-page-to-display-of-book page? book pane))))


;;; `Show-logbook-in-g2-window' lays out certain pages of the logbook according
;;; to logbook-parameters in the detail pane, if any, of the window, if any,
;;; corresponding to G2-window.

(defun show-logbook-in-g2-window (g2-window)
  (let* ((workstation? (workstation-for-g2-window? g2-window))
	 (gensym-window?
	   (if workstation? (window-for-workstation workstation?)))
	 (pane? (if gensym-window?
		    (detail-pane gensym-window?))))
    (when pane?
      (provide-current-logbook)
      (when (use-native-logbook-p gensym-window?)
	(show-native-logbook gensym-window?))
      (neatly-stack-logbook-pages-in-pane pane? current-logbook?))))






;;; Hide-all-logbook-pages-in-pane hides all logbook pages in pane.

(defun hide-all-logbook-pages-in-pane (pane)
  (loop with image-planes-to-delete = nil
	for image-plane in (stack-of-image-planes pane)
	when (and (workspace-on-image-plane? image-plane)
		  (frame-of-class-p
		    (workspace-on-image-plane? image-plane)
		    'logbook-page))
	  do (setq image-planes-to-delete	; in back-to-front order
		   (gensym-cons image-plane image-planes-to-delete))
	finally
	  (loop for image-plane in image-planes-to-delete
		do (delete-image-plane image-plane))
	(reclaim-gensym-list image-planes-to-delete)
	))



;;; `Hide-logbook-in-g2-window' hides all pages of the logbook in the detail
;;; pane, if any, of the window, if any, corresponding to G2-window.

(defun hide-logbook-in-g2-window (g2-window)
  (let* ((workstation? (workstation-for-g2-window? g2-window))
	 (gensym-window?
	   (if workstation? (window-for-workstation workstation?)))
	 (pane? (if gensym-window?
		    (detail-pane gensym-window?))))
    (when pane?
      (hide-native-logbook gensym-window?)
      (hide-all-logbook-pages-in-pane pane?))))
    




;;; `Current-message-board?' and `frame-serial-number-of-current-message-board'
;;; are initialized as a pair by the post-loading function provide-message-board-
;;; after-loading-kb, which is in FILES.  These two variables must always be in
;;; synch.  

(def-kb-specific-variable current-message-board? books nil)

(def-kb-specific-variable frame-serial-number-of-current-message-board
    ;; only examine if current-message-board?
    books :no-initial-value nil reclaim-frame-serial-number)


(defun current-message-board? ()
  (when (and current-message-board?
	     frame-serial-number-of-current-message-board
	     (frame-has-not-been-reprocessed-p
	       current-message-board? frame-serial-number-of-current-message-board))
    current-message-board?))


;;; Whenever a message is written to the message board,
;;; `provide-current-message-board' uses the above variables to check if the
;;; message board exists and has not been deleted; if necessary it creates a
;;; new message board and resets these variables appropriately.  In any case,
;;; it ensures that message board has an image plane on every detail pane
;;; (though the user may "show" it off of the screen, out of view) in every
;;; workstation that is in service and is logged into and which has no kb
;;; restriction against showing a workspace named message-board.  When it puts
;;; up a new image plane, it always puts it in the top left corner of the
;;; detail pane at full scale.  This returns the current message board.

(defun provide-current-message-board ()
  (loop with message-board
	  = (progn
	      (when (or (null current-message-board?)
			(frame-has-been-reprocessed-p current-message-board? frame-serial-number-of-current-message-board))
		(setq current-message-board? (make-message-board))
		(frame-serial-number-setf frame-serial-number-of-current-message-board (frame-serial-number current-message-board?)))
	      current-message-board?)
	for workstation in workstations-in-service
	as gensym-window = (window-for-workstation workstation)
	when (and (eq (workstation-login-state workstation) 'logged-in)
		  (is-message-board-enabled workstation)
		  (workspaces-can-be-shown-at-this-kb-level-p ; and showing message-board
		    message-board workstation))               ;   not restricted
	  do (cond ((use-native-message-board-p gensym-window)
		    ;; Ensure- rather than Show- since message-boards are never
		    ;; automatically lifted-to-top except when first shown.
		    (ensure-native-message-board gensym-window))
		   (t
		    (show-message-board-in-window gensym-window)))
	finally
	  (return message-board)))

(defun show-message-board-in-window (gensym-window)
  (when (current-message-board?)
    (let ((workstation (workstation-this-is-on gensym-window))
	  (detail-pane (detail-pane gensym-window))
	  (message-board current-message-board?))
      (when (and detail-pane				   ; Paranoia, never nil.
		 (is-message-board-enabled workstation)
		 (loop for image-plane			   ; no images of message-board 
			   in (image-planes-this-is-on message-board)
		       never (eq (pane-for-image-plane image-plane) detail-pane)))
	(for-workstation (workstation)
	  (put-workspace-on-pane message-board detail-pane 'left 'top nil))))))


;;; The function `workspace-show-or-hide-hook' is called when a workspace is
;;; about to be shown or hidden on the given window, EXCEPT when done by
;;; `put-workspace-on-pane'. Restrictions have NOT been checked yet.  If it
;;; returns non-NIL, the caller assumes the showing or hiding has been done and
;;; returns immediately.

(defun workspace-show-or-hide-hook (workspace gensym-window show-p)
  (cond ((and (current-message-board?)
	      (eq workspace current-message-board?)
	      (use-native-message-board-p gensym-window))
	 (cond (show-p
		(when (workspaces-can-be-shown-at-this-kb-level-p
			workspace (workstation-this-is-on gensym-window))
		  (show-native-message-board gensym-window)))
	       (t
		(hide-native-message-board gensym-window)))
	 t)))


(def-kb-specific-variable next-serial-number-to-be-generated books 1)

(def-kb-specific-variable current-message-serial-number books 1)

(def-kb-specific-variable current-message-unix-time? books nil)	; managed-float or NIL

;; Now that these are kb-specific, there may be some obsolete code to reset them.



(defun increment-message-serial-number ()
  (setq current-message-serial-number
	(prog1 next-serial-number-to-be-generated
	  (atomic-incf next-serial-number-to-be-generated))))



;;; The function `compute-current-message-time' returns the time-tag for a new
;;; logbook or message board message, as a newly consed managed float.

;;; If the value of the special variable system-is-running is nil, the lisp
;;; system's version of universal-time, as given by get-decoded- time, is used
;;; as the time.  Otherwise, the value of gensym time is used.

(defun compute-current-message-time ()
  (with-temporary-gensym-float-creation compute-current-message-time
    (allocate-managed-float
      (if system-is-running
	  (convert-gensym-time-to-unix-time gensym-time)
	  (gensym-get-unix-time)))))

(defun simple-encode-date (unix-time-mf?)
  (when unix-time-mf?
    (multiple-value-bind (seconds minutes hours day month year)
	(decode-unix-time-as-managed-float unix-time-mf?)
      (declare (ignore seconds minutes hours))
      (logiorf day (ashf month 5) (ashf year 14)))))

(defun simple-decode-date (date)
  (values (logandf date #x1F)
	  (logandf (ashf date -5) #xF)
	  (logandf (ashf date -14) #xFFF)))

;;; Print-message-header prints the standard header for messages to logbooks and
;;; message boards.  Currently, it prints "#n   hh:mm:ss   ", where n is the value
;;; of the special variable current-message-serial-number and hh:mm:ss is the
;;; current time of day.

(defun print-message-header (unix-time-mf logbook-p)
  (tformat "#~d   " current-message-serial-number)
  (multiple-value-bind (seconds minutes hours day month year)
      (decode-unix-time-as-managed-float unix-time-mf)
    (if (or (and logbook-p
		 (include-date-in-logbook-messages logbook-parameters))
	    (and (not logbook-p)
		 (include-date-in-messages message-board-parameters)))
	;; Changed this to print the seconds on 9/1/88.
	;; Consider making this a "message" parameter (or individual
	;; logbook/message-board parameters). (MHD 9/1/88)
	(print-decoded-time seconds minutes hours day month year)
	(print-decoded-time-of-day seconds minutes hours)))
  (tformat "   "))

;; Note that the current value of gensym-time is not printed at all, at present.
;; The technical problems with doing so need further resolution.  Address this!






;;;; Log Files




;;; A `log file' is a file that records messages that are displayed on the
;;; logbook.  The user controls the output through the system table
;;; log-file-parameters, which specifies: log file enabled?, directory
;;; for log files, root name for log files, current log file, when to close
;;; current log file and open next one, when to back up current log file
;;; other than when closing, and maximum number of log files.

;;; The file name is generated from the user specified directory for log
;;; files, a file root name, and a count of the existing log files.  (The
;;; file name length is restricted because of the file name length limit on
;;; certain platforms.) As the maximum number of log files is reached, the
;;; oldest file (i.e., the file that was written longest ago) is overwritten.
;;; Note that this file which is overwritten can be from an earlier run of G2.
;;; As the maximum number of messages per file is reached, the next file is then
;;; opened and written to.

;; **NOTE** Currently the OLDEST FILE IS NOT WRITTEN when beginning a new G2
;; process.  In this cases, THE FIRST LOG FILE (WITH THE FIRST FILE INDEX) IS
;; WRITTEN OVER FIRST.  Then the files that follow the first index are
;; overwritten!!  This needs to be improved so that the oldest file (with the
;; oldest write date) is overwritten first!!  

;;; Upon restart or reset, the log file output is not disabled.  In this wasy,
;;; the user can record messages during KB development.

;;; "When to back up current log file other than when closing" controls the time
;;; at which the file is written on the disk and the file is closed.  (This is
;;; specified in terms of number of messages written and/or time from last
;;; update.) This allows the user to be certain that messages are safely on disk
;;; in case of a G2 or machine problem.

;;; "When to close current log file and open next one" controls, obviously, when
;;; the file is to be closed and the next file used for output.  

;;; Log files are opened when necessary (e.g., when the first message is
;;; being written to a file or the first message is being written after a file
;;; update).  The files remain open between message output unless the system is
;;; being shutdown or a file close or backup condition is reached (e.g., number
;;; of messages or time interval).

;;; The log file name parameters for directory and root name can only be
;;; modified when the log file is not enabled.  This prevents confusion among
;;; file names and file counters.

;; Issues:
;;
;; (1) Log file is not really opened when it gets "enabled" (log-file-enabled =>
;; yes).
;;
;; (2) Log file _is_ really closed when it gets "disabled". (log-file-enabled =>
;; no).
;;
;; (3) When you change log-file-enabled to "yes" the first time, it shows "none"
;; for current-log-file.  Then it shows the file name after the first message
;; has been printed out.  Then, if you change log-file-enabled to "no", it shows
;; the name of the last log file you were working with, even though it's not
;; being output to.  (And then, if you enable it, it does start writing to that
;; file, and continues to display it, which makes sense.)
;;
;; (3) Messages are appended to the end of any existing file with the same name
;; as the log file wants to have.
;;
;; (4) If you have trouble opening the log file, you get the message about the
;; trouble with sequence number n+1 followed in the logbook by the message
;; "Log file is being enabled." with sequence number n.  This is wierd.
;;
;; (5) Note that the first message is always "Log file being enabled.".
;;
;; (6) The message "Log file being disabled." is never put into the log file.
;;
;; (7) It doesn't it let you change log files while enabled?  Why?!
;;
;; (8) Work on flushing old comments and code in this section with CPM.
;;
;; -- review these issues with CPM & put more into them later!
;;
;; (MHD 7/1/93)


;; LOG FILES MAKE USE OF COMMON LISP PATHNAMES.  WE NEED TO IMPLEMENT A
;; NON-CONSING VERSION OF PATHNAMES!! 12mar90,cpm.


;; OLD SYSTEM FRAME SLOTS OF LOGBOOK-PARAMETERS:
;;   1. logbook-file-update-frequency
;;   2. maximum-number-of-logbook-files
;;   3. maximum-number-of-messages-per-logbook-file
;;   4. logbook-file-prefix
;;   
;; (... as of ca. March, '90, I believe. -mhd, 10/11/91)


;; PUT THIS SYSTEM FRAME BEFORE message-board-parameters (so that it
;; comes after logbook parameters in the system table menu)!!?? 18mar90, cpm.


(def-system-frame log-file-parameters books
  (log-file-enabled?
    nil vector-slot system (type yes-or-no))  ;; see note with alias
  (directory-for-log-files
    nil vector-slot system (type log-file-directory))
  (root-name-for-log-files
    "g2-log-" vector-slot system (type log-file-name))
  (current-log-file				       ; read-only display slot.
    nil vector-slot system not-user-editable (type read-only-whole-string?)
    do-not-save)
  (when-to-close-log-file
    (100 (86400 . seconds))			; 86,400 = (* 60 60 24)
    vector-slot system (type close-log-file))
  (when-to-back-up-log-file
    nil vector-slot system (type back-up-log-file))
  (maximum-number-of-log-files			; nil or an integer [1..999]
    10 vector-slot system (type log-file-maximum)))

(def-absent-slot-putter when-to-backup-log-file (log-file-parameters value)
  (change-slot-value log-file-parameters 'when-to-back-up-log-file value))

;; Minor spelling correction: when-to-backup-log-file => when-to-back-up-log-file.
;; For 3.0.  (MHD 7/9/91)

;; Also: (type backup-log-file) => (type back-up-log-file). See also GRAMMAR7.
;; (MHD 10/11/91)


(define-slot-alias log-file-enabled log-file-enabled? log-file-parameters)

(define-slot-alias when-to-close-current-log-file-and-open-next-one when-to-close-log-file
  log-file-parameters)

(define-slot-alias when-to-back-up-current-log-file-other-than-when-closing when-to-back-up-log-file
  log-file-parameters)




;;; The function `initialize-log-file-update-for-slot' is used in the log-file
;;; system-frame to initialize the slot "when-to-close-log-file".

(defun initialize-log-file-update-for-slot (message-count interval-in-seconds)
  (slot-value-list message-count 
		   (slot-value-cons interval-in-seconds 'seconds)))



;;; The system variable `log-file-outputting?' indicates whether logbook messages
;;; should be written to the log file.  (All necessary Log File system parameters
;;; have been provided.)

(def-system-variable log-file-outputting? books nil)


;;; The system variable `log-file-writing-message?  indicates whether a logbook
;;; message is in the process of being written.  This is helpful when posting an
;;; error message to the logbook when writing a logbook message to the log file.
;;; (This prevents overflowing the stack because of recursively writing
;;; messages.)

(def-system-variable log-file-writing-message? books nil)


;;; The system variable `log-file-string' contains the Gensym text-string for
;;; the namestring of the pathname associated with the current log file, if any.
;;; By default, and when there is no such log file, it is nil.  [As of 4.0,
;;; rev. 49,] this is a gensym text string.  It must be translated to ASCII or
;;; whatever is the external character set from the Gensym character set.

(def-system-variable log-file-string books nil)


;;; The system variable `log-file-stream' contains the stream associated with the
;;; current log file.

(def-system-variable log-file-stream books nil)


;;; The system variable `log-file-default-pathname?' is either nil or a pathname
;;; whose name is created from the log file pathname prefix specified in
;;; log-file-parameters.  This variable is useful when creating the actual,
;;; verfied pathnames that contain the file counter.

(def-system-variable log-file-default-pathname? books nil nil nil reclaim-pathname-or-string)



;;; The system variable `log-file-count' is an index to the current log file.
;;; This number is used when creating a log file name.

(def-system-variable log-file-count books 0)


;;; The system variable `log-file-message-count' contains a count of the Logbook
;;; messages already written to the current log file.  This number is used to
;;; determine if the maximum number of messages per file has been reached.

(def-system-variable log-file-message-count books 0)


;;; A `message count and interval' is a data-abstracted structure that gives
;;; two pieces of information: (1) a message count or nil, which is accessed by
;;; the macro `message-count-of-message-count-and-interval?', and (2) interval
;;; or nil, which is accessed by the macro `interval-of-message-count-and-interval?'.

;;; A "message count and interval" is implemented as either nil or a cons
;;; structure containing two elements, one of which is an interval, i.e., a cons of
;;; the form
;;; 
;;;    (interval . second)
;;; 
;;; and the other of which is the integer
;;;
;;;    number-of-messages

(def-substitution-macro message-count-of-message-count-and-interval?
			(message-count-and-interval?)
  (if (consp (first message-count-and-interval?))
      (second message-count-and-interval?)
      (first message-count-and-interval?)))

(def-substitution-macro interval-of-message-count-and-interval?
			(message-count-and-interval?)
  (first
    (if (consp (first message-count-and-interval?))
	(first message-count-and-interval?)
	(second message-count-and-interval?))))



;;; `Close-log-file-after-message-count?' says after how many messages the
;;; log file should be closed, if any, based on the when-to-close-log-file
;;; slot of log-file-parameters.

;;; `Update-log-file-after-message-count?' is similar, but is based instead on
;;; the when-to-update-log-file slot.

(defmacro close-log-file-after-message-count? ()
  '(message-count-of-message-count-and-interval?
     (when-to-close-log-file log-file-parameters)))

(defmacro update-log-file-after-message-count? ()
  '(message-count-of-message-count-and-interval?
     (when-to-back-up-log-file log-file-parameters)))


;;; `Close-log-file-after-interval?' says after how long a time interval
;;; the log file should be closed, if any, based on the when-to-close-log-file
;;; slot of log-file-parameters.

;;; `Update-log-file-after-interval?' is similar, but is based instead on
;;; the when-to-update-log-file slot.

(defmacro close-log-file-after-interval? ()
  '(interval-of-message-count-and-interval?
     (when-to-close-log-file log-file-parameters)))


(defmacro update-log-file-after-interval? ()
  '(interval-of-message-count-and-interval?
     (when-to-back-up-log-file log-file-parameters)))




;; OBSOLETE, due to the above! (MHD 10/11/91)
;; 
;; ;;; The system variable `close-log-file-after-message-count?' specifies the
;; ;;; number of messages written before the file is closed.
;; 
;; (def-system-variable close-log-file-after-message-count? books nil)
;;
;;
;; ;;; The system variable `close-log-file-after-interval?' specifies the time
;; ;;; interval between file openning and writing of the most recent message.
;; ;;; When this time interval elapses the file is closed.
;; 
;; (def-system-variable close-log-file-after-interval? books nil)
;;  
;;
;; ;;; The system variable `update-log-file-after-message-count?' is the number of
;; ;;; logbook messages written between updates that triggers the next update.
;; 
;; (def-system-variable update-log-file-after-message-count? books nil)
;;
;;
;; ;;; The system variable `update-log-file-after-interval?' is the time interval
;; ;;; from the last log file update that triggers the next update.
;; 
;; (def-system-variable update-log-file-after-interval? books nil)


;;; The system variable `log-file-message-count-at-last-update' contains a
;;; count of the number of messages written into the file at the last file
;;; udpate.  This number is used when determining if a file needs to be updated.

(def-system-variable log-file-message-count-at-last-update books 0)


;;; The system variable `log-file-time-at-last-update' contains the time at which
;;; the log file was last updated.  This time can be used to determine if a file
;;; needs to be updated.

(def-system-variable log-file-time-at-last-update books nil)


;;; The system variable `log-file-time-at-open' contains the time at which the
;;; log file was opened.  This time can be used to determine if a file needs to
;;; be closed.  (This number is not updated when re-opened for appending after a
;;; backup.)

(def-system-variable log-file-time-at-open books nil)


;;; The system variable `log-file-pathnames' is an ordered list of log file
;;; pathnames.  Pathnames are added to the end of this list as they are created.
;;; When all the necessary pathnames have been created, pathnames are used from
;;; this list as needed.  This list is cleared when the log file specification
;;; (e.g., root-name or directory) system parameter receives a new value.

(def-system-variable log-file-pathnames books nil)


;;; The constant `log-file-name-extension' is the default file extension used
;;; when creating log file names.

(defconstant log-file-name-extension #.(stringw "text"))


;;; The constant `maximum-log-file-name-prefix-length' is the maximum character
;;; length of the part of the file name specified by the user (i.e., not
;;; generated by the system).  For example, the file log1234.text, has a prefix
;;; of "log".

(def-system-variable maximum-log-file-name-prefix-length? BOOKS
  (:funcall initialize-maximum-log-file-name-prefix-length?))

(defun initialize-maximum-log-file-name-prefix-length? ()
  (and maximum-file-name-length?
       (- maximum-file-name-length?
	  ;; 4 because of the maximum file number length (i.e.,
	  ;; 999) plus decimal point.
	  (lengthw log-file-name-extension)
	  4)))

;; jh, 5/31/91.  Changed maximum-log-file-name-prefix-length?  from a parameter to
;; a system variable because we no longer know its value at compile time.  See
;; note under maximum-file-name-length?  in STREAMS for further details.

;; The activation method for Log File parameters resets log file variables.

;; Currently not used!

;(def-class-method activate-subclass-of-entity (log-file-parameters)
;  (unless (active-p log-file-parameters)
;    ;; If the logging to file is enabled and the log file root-name is provided,
;    ;; turn on log filing flag.
;    (when (and (root-name-for-log-files log-file-parameters)
;	       (log-file-enabled? log-file-parameters))
;      (setq log-file-outputting? t)
;      (setq log-file-count 0)
;      (setq log-file-message-count 0)
;      (setq log-file-message-count-at-last-update 0)
;      (setq log-file-time-at-last-update gensym-time))))



;; The deactivation method for Log File parameters turns off logbook message
;; output if necessary.

;; Currently not used!

;(def-class-method deactivate-subclass-of-entity (log-file-parameters)
;  (when (and (active-p log-file-parameters)
;	     log-file-outputting?)
;    (if system-has-paused
;	;; If paused, close the file, but hold onto the name.  Will reopen upon
;	;; activation.
;	(close-log-file nil)
;	(progn
;	  ;; Close the file, clear the name, and turn off log file message
;	  ;; output.
;	  (close-log-file t)
;	  (setf log-file-outputting? nil)))))



;;; The slot putter for log-file-enabled? sets the Log file outputting flag if the
;;; necessary Log file parmeters are set and if log file is being enabled.  If
;;; log file is being disabled, the log file outputting flag is set to nil.

(def-slot-putter log-file-enabled? (log-file-parameters-instance new-value initializing?)
  (when (system-table-installed-p log-file-parameters-instance)
    (when (or initializing? (not new-value))
      ;; Close the log file in case a kb is being loaded or if
      ;; disabling; do not clear the name if disabling, since the
      ;; same file can be appended when reenabling.  
      (close-log-file)
      (reset-log-file-information (or initializing? new-value) nil))
    (if new-value
	;; a default pathname is needed upon startup and clearing g2. (Oh. -mhd)
	(create-log-file-default-pathname-if-necessary
	  (directory-for-log-files log-file-parameters-instance)
	  nil))
    ;; turn log file message output on or off. 
    (setf log-file-outputting? new-value)
    ;; Log-file-stream is actually NIL here, but will typically become
    ;; set when the following calls to warning-message, which ultimately
    ;; opens the stream & sets log-file-stream.  It's a little hairy to
    ;; do right now, but it should be arranged so that the truename of
    ;; the file being logged to could be included in the message.  (MHD
    ;; 11/14/91)
    (when (or new-value (not initializing?))
      ;; should not be warning-message* since this is not an error. FIX!
      (warning-message
	1 "Log file is being ~Aabled."
	(if new-value "en" "dis"))))
  (setf (log-file-enabled? log-file-parameters-instance)
	;; log-file-outputting?      	; -- BAD IDEA! (MHD 6/30/93)
	new-value)			; usually new-value, but
						;   could be reset nil if
						;   the logging of the
						;   "warning" fails.
						;   (MHD 11/14/91)
  new-value)

;;; The slot putter for directory-for-log-files sets the log file directory
;;; value and if necessary, resets the pathname list.  The default pathname is
;;; created from the directory and root-name values.
;;;
;;; Note that this slot always holds a legal Gensym text string.  It must be
;;; translated into the character set of the target OS pathname system when used
;;; with G2 stream and pathname functions that expect to deal with OS-specific
;;; (usually ASCII for now) strings.

(def-slot-putter directory-for-log-files (log-file-parameters-instance new-value)
  (if (system-table-installed-p log-file-parameters-instance)
      (create-log-file-default-pathname-if-necessary new-value nil))
  (setf (directory-for-log-files log-file-parameters-instance) new-value)
  new-value)



;;; The slot putter for root-name-for-log-files sets the root-name value and if
;;; necessary, resets the pathname list.  The default pathname is created from
;;; the root-name and directory values.
;;;
;;; Note that this slot always holds a legal Gensym text string.  It must be
;;; translated into the character set of the target OS pathname system when used
;;; with G2 stream and pathname functions that expect to deal with OS-specific
;;; (usually ASCII for now) strings.

(def-slot-putter root-name-for-log-files (log-file-parameters-instance new-value)
  (if (system-table-installed-p log-file-parameters-instance)
      (create-log-file-default-pathname-if-necessary nil new-value))
  (setf (root-name-for-log-files log-file-parameters-instance) new-value)
  new-value)



;;; The function `create-log-file-default-pathname-if-necessary' creates a
;;; default log file pathname (not yet validated) when a directory and root-name
;;; are present.  If either of the values are not passed to this functions
;;; (i.e., they are not new values), then the existing values are used.  When a
;;; pathname is successfully created, the log file pathname list is cleared and
;;; the pathname is saved in a system variable.  Either new-directory?  or
;;; new-root-name?  should be passed as new value, not both.  New-root-name?
;;; must be a string if it is a new value.  New-directory?  can have nil or a
;;; string as a new value.  (If new-root-name?  is nil then new-directory?
;;; value is a new value, even if nil.)

;; Modified create-log-file-default-pathname-if-necessary to use the new
;; reclaimable gensym-pathnames.  This means, among other things, that this
;; functions sets log-file-default-pathname? to a gensym-pathname instead of a lisp
;; one.  jh, 1/11/91.

(defun-allowing-unwind create-log-file-default-pathname-if-necessary 
    (new-directory? new-root-name?)
  (protected-let*
      ((new-directory-string-in-target-charset?
	 (if new-directory?
	     (convert-text-string-to-ascii-filename-as-much-as-possible
	       new-directory?))
	 (reclaim-text-string new-directory-string-in-target-charset?)))
    (when (or (null log-file-default-pathname?)
	      ;; a new directory which has changed.
	      (or (and (null new-directory-string-in-target-charset?)
		       (directory-for-log-files log-file-parameters))
					; 1 ; <- this 1 was here, uncommented, before today!! (MHD 5/5/95)
		  (and new-directory-string-in-target-charset? 
		       (not (and (directory-for-log-files log-file-parameters)
				 (string-equalw 
				   new-directory-string-in-target-charset? 
				   (directory-for-log-files log-file-parameters))))))
	      ;; a new root name which has changed.
	      (and new-root-name?
		   (not (and (root-name-for-log-files log-file-parameters)
			     (string-equalw 
			       new-root-name?
			       (root-name-for-log-files log-file-parameters))))))
      (handling-gensym-file-errors
	(protected-let
	    ((current-system-pathname? process-specific-system-pathname)
	     (root-name?
	       (or new-root-name?
		   ;; root name always has a text-string value in kbs as of
		   ;; 3-23-90.
		   (root-name-for-log-files log-file-parameters)))
	     (root-name-in-target-charset?
	       (if root-name?
		   (convert-text-string-to-ascii-filename-as-much-as-possible
		     root-name?))
	       (reclaim-text-string root-name-in-target-charset?))
	     (directory-pathname?
	       (if new-directory-string-in-target-charset?
		   (or (gensym-file-as-directory new-directory-string-in-target-charset?)
		       ;; unfortunately, gensym-file-as-directory returns NIL if the
		       ;; parameter has a trailing slash.
		       (gensym-parse-namestring new-directory-string-in-target-charset?))
		   (if new-root-name?
		       ;; Not changing the directory.
		       (protected-let*
			   ((log-file-directory?
			      (directory-for-log-files log-file-parameters))
			    (log-file-directory-in-target-charset?
			      (if log-file-directory?
				  (convert-text-string-to-ascii-filename-as-much-as-possible
				    log-file-directory?))
			      (reclaim-text-string log-file-directory-in-target-charset?)))
			 (cond (log-file-directory-in-target-charset?
				(or (gensym-file-as-directory
				      log-file-directory-in-target-charset?)
				    (gensym-parse-namestring
				      log-file-directory-in-target-charset?)))
			       (current-kb-pathname?
				(copy-gensym-pathname current-kb-pathname?))
			       (current-system-pathname?
				(copy-gensym-pathname current-system-pathname?))
			       (t nil)))
		       ;; Changing the directory to nil.
		       (cond (current-kb-pathname?
			      (copy-gensym-pathname current-kb-pathname?))
			     (current-system-pathname?
			      (copy-gensym-pathname current-system-pathname?))
			     (t nil))))
	       (reclaim-gensym-pathname directory-pathname?)))
	  ;; Create the default pathname.
	  (when directory-pathname?
	    (reset-log-file-information t t)
	    (when root-name-in-target-charset?
	      ;; The store-current-pathname macro reclaims the old value if any.
	      (store-current-pathname log-file-default-pathname?
				      ;; returns nil on error and gives the user a warning message.
				      (gensym-make-pathname ;copies its components
					:name root-name-in-target-charset?
					:type log-file-name-extension
					:defaults directory-pathname?)))))

	
	;; Verify the file name prefix character length.
;    (when (and log-file-default-pathname?
;	       maximum-log-file-name-prefix-length?
;	       log-file-default-pathname?
;	       (>f (length 
;		     (gensym-pathname-name 
;		       log-file-default-pathname?))
;		   maximum-log-file-name-prefix-length?))
;      ;; This should not be warning-message* since this is not an error.
;      (write-warning-message 1 
;	(tformat
;	  "Warning.  The log file name ~s is greater than ~d characters.  ~
;         This value will be truncated when creating file names." 
;	  (gensym-pathname-name log-file-default-pathname?)
;	  maximum-log-file-name-prefix-length?)))
      ))))





;;; The slot putter for when-to-close-log-file sets the necessary system
;;; variables that trigger log file closing.

(def-slot-putter when-to-close-log-file (log-file-parameters-instance new-value)
  (setf (when-to-close-log-file log-file-parameters-instance) new-value)
  new-value)


;;; The slot putter for when-to-back-up-log-file sets the necessary system
;;; variables that trigger log file backup.

(def-slot-putter when-to-back-up-log-file (log-file-parameters-instance new-value)
  (setf (when-to-back-up-log-file log-file-parameters-instance) new-value)
  new-value)



;;; The slot putter for maximum-number-of-log-files keeps the current file
;;; counter within the new maximum-number-of-log-files, unless it's nil.
;;; (Since this maximum value can be modified while running.)

(def-slot-putter maximum-number-of-log-files (log-file-parameters-instance new-value)
  (if (system-table-installed-p log-file-parameters-instance)
      ;; If the current file counter is greater than the new maximum file counter,
      ;; set the current file counter to the maximum value.
      (when (and new-value			; This had not expected nil! I
						;   fixed that. (MHD 10/12/91)
		 (>f log-file-count new-value))
	(setq log-file-count new-value)))
  (setf (maximum-number-of-log-files log-file-parameters-instance) new-value)
  new-value)




;;; The function `open-log-file' opens the log file specified in the Log File
;;; parameters table regardless of whether the system is running, paused, or
;;; activating (e.g., restarting).  If open-for-appending?  is non-nil, the file
;;; is opened for appending.  Otherwise, the file is opened for writing.  A
;;; message is displayed if an error occurs when opening the file.  (An error is
;;; not displayed if the pathname is not specified.) If the file is successfully
;;; opened, t is returned, otherwise nil is returned.  Log-file-string should
;;; already have a value.  Current-log-file system parameter is set to the
;;; current log file name and the gensym-time is saved.

(defun-allowing-unwind open-log-file (open-for-appending?)
  (protected-let* ((log-file-string-in-target-charset
		     (convert-text-string-to-ascii-filename-as-much-as-possible
		       log-file-string)
		     (reclaim-text-string log-file-string-in-target-charset)))
    (cond
      (log-file-string
       (setq log-file-stream 
	     (cond
	       (open-for-appending?
		(g2-stream-open-for-appending-handling-file-errors
		  log-file-string-in-target-charset
		  t))
	       (t
		(g2-stream-open-for-output-handling-file-errors
		  log-file-string-in-target-charset))))
       (cond
	 ((g2-stream-p log-file-stream)
	  (when (null open-for-appending?)
	    (change-slot-value 
	      log-file-parameters 'current-log-file 
	      (copy-text-string log-file-string)))
	  (unless open-for-appending?
	    (setq log-file-time-at-open gensym-time))
	  t)
	 (t	
	  ;; should be warning-message instead of warning-message*, since
	  ;; warning-message* makes up and prints a name for the current
	  ;; computation frame.
	  (let ((error-text? (most-recent-file-operation-status-as-text)))
	    (cond
	      (error-text?
	       (warning-message
		   1 "Error.  Could not open log file ~s: ~a."
		 log-file-string error-text?))
	      (t
	       (warning-message ;jh, 10/21/94.  Never reached.
		   1 "Error.  Could not open log file ~s."
		 log-file-string)))
	    (reclaim-text-string error-text?)) ; was previously not reclaimed! (MHD 2/22/96)
	  nil)))
      (t
       #+development
       (warning-message 1 "could not open log file.  Missing log file string.")
       nil))))



;;; The function `reset-log-file-information' is used to set log file
;;; information back to the initial values when a file is closed.  If the
;;; clear-current-file-information?  argument is non-nil, current file
;;; information is cleared as well as reset.  (Clear-file-information?  should
;;; be nil when the file is being closed for a backup and will be reopened.)
;;; If clear-all-file-information? is non-nil, all file information is cleared.
;;; This is necessary when starting a new log file session (e.g., there is a new
;;; log file counter).  Clear-current-file-information? and
;;; clear-all-file-information? should both be nil, when a file is being closed
;;; for a backup/update.

;; Modified reset-log-file-information to reclaim the gensym-pathnames in
;; log-file-pathnames, not just the spine of the list, since we have consing
;; control over pathnames now.  jh, 1/11/91.

(defun reset-log-file-information (clear-current-file-information?
				   clear-all-file-information?)
  (when (or clear-current-file-information?
	    clear-all-file-information?)
    ;; clear information when a file is being closed, not to be appended to.
    (when log-file-string
      ;; The log-file-string is not reclaimed because this was part of the
      ;; pathname.
      (setq log-file-string nil)
      (change-slot-value log-file-parameters 'current-log-file nil))
    (setq log-file-message-count 0))
  (when clear-all-file-information?
    (setq log-file-count 0)
    ;; Reset the pathname list.
    (loop for log-file-pathname in log-file-pathnames
	  do (reclaim-gensym-pathname log-file-pathname)
	  finally (reclaim-gensym-list log-file-pathnames))
    (when (gensym-pathname-p log-file-default-pathname?)
      (reclaim-gensym-pathname log-file-default-pathname?))
    (setq log-file-default-pathname? nil)
    (setq log-file-pathnames nil))

  ;; File backup information.
  (setq log-file-time-at-last-update gensym-time)
  (setq log-file-message-count-at-last-update log-file-message-count))








(def-class-method install-system-table (log-file-parameters)
  ;; Close the log file in case a kb is being loaded or if
  ;; disabling; do not clear the name if disabling, since the
  ;; same file can be appended when reenabling.  
  (progn
    (close-log-file)
    (reset-log-file-information (log-file-enabled? log-file-parameters) nil))
  
  (create-log-file-default-pathname-if-necessary
   (directory-for-log-files log-file-parameters)
   nil)

  ;; turn log file message output on or off. 
  (setf log-file-outputting?
	(log-file-enabled? log-file-parameters)))


(def-class-method deinstall-system-table (log-file-parameters)
  (close-log-file)
  (reset-log-file-information nil t)		; both args T? (MHD 10/11/91)
  (setq log-file-outputting? nil))




;; OBSOLETE!  Functionality now incorporated into the new (de)install-system-table
;; class methods.  (MHD 10/11/91)
;; ;;; The function `log-file-initialize' is called during initialization of the
;; ;;; log-file-parameters log-file-enabled?  slot.  This is necessary to reset
;; ;;; logfile variables and close the logfile, if necessary, upon kb clearing or
;; ;;; loading of a new kb.
;; 
;; (defun log-file-initialize ()
;;   (close-log-file)
;;   (reset-log-file-information nil t)
;;   (setq log-file-outputting? nil))




;;; The function `close-log-file' closes the log-file-stream and clears that
;;; variable.

(defun close-log-file ()
  (when log-file-stream
    (g2-stream-close log-file-stream)
    (setq log-file-stream nil)))



;;; The function `update-log-file-if-necessary' closes or backs up the log file
;;; when the udpate conditions are met.  The update conditions are specified by
;;; the user and then parsed and saved in system parameters.  A close, closes
;;; the file and clears file information.  An backup closes the file, but does
;;; not clear the log file variables.  (The file may be opened at a later time.)


;; log-file-message-count
;; OBSOLETE: ;; close-log-file-after-message-count?
;; OBSOLETE: ;; close-log-file-after-interval?
;; OBSOLETE: ;; update-log-file-after-message-count?
;; OBSOLETE: ;; update-log-file-after-interval?
;; log-file-message-count-at-last-update
;; log-file-time-at-last-update
;; log-file-time-at-open

(defun update-log-file-if-necessary ()
  ;; First test if the file should be closed because of time interval reached
  ;; or message maximum reached.  Then, test if the file should be backed up
  ;; because of backup interval being reached or message backup maximum
  ;; reached.
  (cond ((and (close-log-file-after-message-count?)
	      (>=f log-file-message-count
		   (close-log-file-after-message-count?)))
	 ;; Close the file and clear the file information.
;	 #+development
;	 (format t "close: log-file-message-count=~d, ~
;                   close-log-file-after-message-count?=~d.~2%"
;		 log-file-message-count
;		 (close-log-file-after-message-count?))		 
	 (close-log-file)
	 (reset-log-file-information t nil))
	((and (close-log-file-after-interval?)
	      (>=i (-i gensym-time log-file-time-at-open)
		   (close-log-file-after-interval?)))
	 ;; Close the file and clear the current file information.
;	 #+development
;	 (format t "close: gensym-time=~d, ~
;                   log-file-time-at-open=~d,
;                   close-log-file-after-interval?=~d.~2%"
;		 gensym-time
;		 log-file-time-at-open
;		 (close-log-file-after-interval?))
	 (close-log-file)
	 (reset-log-file-information t nil))
	((and (update-log-file-after-message-count?)
	      (>=f (-f log-file-message-count
		       log-file-message-count-at-last-update)
		   (update-log-file-after-message-count?)))
;	 #+development
;	 (format t "backup: log-file-message-count=~d, ~
;                   log-file-message-count-at-last-update=~d,
;                   update-log-file-after-message-count?=~d.~2%"
;		 log-file-message-count
;		 log-file-message-count-at-last-update
;		 (update-log-file-after-message-count?))
	 ;; Close the file, but do not clear the file information.
	 (close-log-file)
	 (reset-log-file-information nil nil))
	((and (update-log-file-after-interval?)
	      (>=i (-i gensym-time log-file-time-at-last-update)
		   (update-log-file-after-interval?)))
;	 #+development
;	 (format t "backup: gensym-time=~d, ~
;                   log-file-time-at-last-update=~d,
;                   update-log-file-after-interval?=~d.~2%"
;		 gensym-time
;		 log-file-time-at-last-update
;		 (update-log-file-after-interval?))
	 ;; Close the file, but do not clear the file information.
	 (close-log-file)
	 (reset-log-file-information nil nil))))




;;; The function `get-next-log-file' gets the next log file name and saves it in
;;; log-file-string.  If necessary, the file name is created from the log file
;;; root-name and directory (specified by the user) and the
;;; current-log-file-counter.  (The root name is truncated as necessary if the
;;; log file name will be too long for that platform.) If the file pathname has
;;; already been created, the file name is taken from log-file-pathnames.  If a
;;; file name is created or located, the pathname is saved (if necessary),
;;; file-name string is saved, the log file count is updated, and T is returned.
;;; Otherwise, NIL is returned.  (Any previous file-name string value is not
;;; reclaimed since it is associated with and part of a pathname.)

;; THIS FUNCTION CONSES!!!  WE NEED TO WRITE A NON-CONSING PATHNAME
;; OPERATIONS!!!  THIS FUNCTION WILL CREATES (CONSES) 2N PATHNAMES, WHERE N IS
;; THE NUMBER OF FILES WRITTEN.  Two pathnames are created per file.  The first
;; is without file-name and file-extension correction.  The second is the
;; validated pathname.  9mar90, cpm !!

;; The truncation of file name is based on the platform that the user is
;; currently running on.  If the user is writing to a different platform, this
;; may not be accurate!!!  16mar90, cpm.

;; Modified get-next-log-file to accommodate the new reclaimable gensym-pathnames.
;; jh, 1/11/91.

(defun-allowing-unwind get-next-log-file ()
  (protected-let* ((file-root-name?
		     (root-name-for-log-files log-file-parameters))
		   (file-root-name-in-target-charset?
		     (if file-root-name?
			 (convert-text-string-to-ascii-filename-as-much-as-possible
			   file-root-name?))
		     (reclaim-text-string file-root-name-in-target-charset?))
		   (validated-pathname? nil)
		   (next-file-index? nil))
    (when (and file-root-name-in-target-charset?
	       (setq next-file-index?
		     (find-next-log-file-index file-root-name-in-target-charset?)))
      (if (nth (-f next-file-index? 1) log-file-pathnames)
	  ;; The pathname was already created.
	  (progn 
	    (setq validated-pathname?
		  (nth (-f next-file-index? 1) log-file-pathnames))
	    ;; The macro store-current-namestring reclaims the old one if any.
	    ;; It is inefficient to keep doing a gensym-namestring on something
	    ;; that never changes.  Consider caching the namestring somewhere.
	    (store-current-namestring log-file-string 
	      (gensym-namestring-as-text-string validated-pathname?))
	    (setq log-file-count next-file-index?))
	  
	  ;; Else, try to create a new pathname.  First create the default
	  ;; pathname if necessary.
	  (when log-file-default-pathname?
	    (handling-gensym-file-errors
	      (protected-let* 
	          ((validated-filename-prefix-string?
		     ;; The file name maximum length varies per platform.  The
		     ;; file name consists of:
		     ;; <file-name-prefix><file-counter>.<file-type>
		     ;; The file names are truncated as needed.  
		     ;; A warning for file names that are too long is given in
		     ;; the slot-putter for root-name-for-log-files
		     (if (and maximum-log-file-name-prefix-length?
			      (<=f (length 
				     (gensym-pathname-name 
				       log-file-default-pathname?))
				   maximum-log-file-name-prefix-length?))
			 (copy-text-string 
			   (gensym-pathname-name log-file-default-pathname?))
			 (text-string-substring 
			   (gensym-pathname-name log-file-default-pathname?)
			   0 
			   maximum-log-file-name-prefix-length?))
		     (reclaim-text-string validated-filename-prefix-string?))
		   (validated-pathname-name
		     (twith-output-to-text-string
		       (twrite-string 
			 validated-filename-prefix-string?)
		       (twrite next-file-index?))
		     (reclaim-text-string validated-pathname-name)))
		(setq validated-pathname?
		      (gensym-make-pathname ;copies its components
			:name validated-pathname-name 
			:type 
			(or (gensym-pathname-type log-file-default-pathname?)
			    ;; Use the default extension if
			    ;; the user did not provide one.
			    log-file-name-extension)
			:defaults 
			log-file-default-pathname?)))

	    (when validated-pathname?
	      (if log-file-pathnames
		  (setf (cdr (last log-file-pathnames))
			(gensym-list validated-pathname?))
		  (setf log-file-pathnames
			(gensym-list validated-pathname?)))
	      ;; The macro store-current-namestring reclaims the old one if any.
	      ;; This string is not shared with any gensym-pathname structure,
	      ;; so it is ok to reclaim it here.  Again, it's inefficient to 
	      ;; keep doing a gensym-namestring on something that never changes.  
	      ;; Consider caching the namestring somewhere.
	      (store-current-namestring log-file-string
		(gensym-namestring-as-text-string validated-pathname?))
	      (setq log-file-count next-file-index?))))))

    ;; Return value.
    (if validated-pathname?
	t
	(progn
	  ;; should be warning-message instead of warning-message*, since
	  ;; warning-message* makes up and prints a name for the current
	  ;; computation frame.
	  #+development
	  (warning-message 1 "Invalid Log file name.")
	  nil))))






;;; The function `find-next-log-file-index' takes as an argument the prefix of the
;;; Log file pathname.  It computes the next file index and returns that value.
;;; The file index (counter) is computed in the following manner.
;;;
;;; The pathname-prefix-string arg is in the target file system pathname system
;;; charset, not a text string in the Gensym character.

;; POSSIBLE FUTURE MODIFICATION: Modify this function so that upon reset, restart,
;; or the running of a new G2 process, only the oldest log files are overwritten.
;; Currently, in these cases, the file index is set to its initial value!!
;; 9mar90, cpm.
;;
;; Algorithm for future implementation: If there is a current log-file-count, the
;; next file-count is the current-count + 1.  Otherwise, a search is done for the
;; oldest Log file (i.e., written the earliest) which has a file name of the form
;; <pathname-prefix><log-file-count>.  If no existing Log file is located, the
;; log-file-count is reset to the initial value.  The log-file-count is not
;; modified.  (There is no side effect.)

(defun find-next-log-file-index (pathname-prefix-string)
  (declare (ignore pathname-prefix-string))	       ; Currently not used.
						       ; Is needed for the new
						       ; approach (see above).
						       ; 9mar90,cpm.
;  (let ((next-log-file-index nil))
;    (if (=f log-file-count 0)
;	;; If we have no current file, locate the oldest file (i.e., file that
;	;; was last written).  Return the index of that file.
;	(progn
;	  (setq next-log-file-index
;		(find-next-log-file-index-if-maximum-not-reached
;		  pathname-prefix-string))
;	  (if next-log-file-index
;	      (return-from find-next-log-file-index next-log-file-index)
;	      (setq next-log-file-index
;		    (find-next-log-file-index-maximum-reached
;		      pathname-prefix-string))))

;	;; Else, use the current file counter to compute the next one.
;	(setq next-log-file-index 
;	      (if (maximum-number-of-log-files log-file-parameters)
;		  ;; Since there is a maximum number of files, reuse the
;		  ;; earliest file.
;		  (+f 1 (modf log-file-count 
;			      (maximum-number-of-log-files 
;				log-file-parameters)))
;		  ;; There is no maximum file count.
;		  (+f 1 log-file-count))))
;    ;; return value.
;    next-log-file-index)

  ;; Compute the next index based on the current one.  (We are not checking for
  ;; the oldest file.)  Currently, upon reset, restart, and startup (of a new
  ;; process) the index is reset to the initial value.
  (if (maximum-number-of-log-files log-file-parameters)
      ;; Since there is a maximum number of files, select the next file.  This
      ;; could be the file with the lowest index if the maximum has been
      ;; reached.
      (+f 1 (modf log-file-count 
		  (maximum-number-of-log-files log-file-parameters)))
      ;; There is no maximum file count.
      (+f 1 log-file-count)))




;; The function `find-next-log-file-index-if-maximum-not-reached' is used to
;; locate the next log file index when the maximum number of log files has not
;; been reached or there is no maximum.

;(defun find-next-log-file-index-if-maximum-not-reached 
;       (pathname-prefix-string)
;)




;; The function `find-next-log-file-index-maximum-reached' is used to locate the
;; next log file index when the maximum number of log files has been reached.
;; Therefore, the oldest file (i.e., file last written) can be any of the files
;; (not necessarily the file with the highest counter).  (The files are in a
;; sorted, cyclic order.  The oldest file is any of the files.  The files after
;; that file are newer and are increasing in age.  The files before that file are
;; also newer and increasing in age.)

;(defun find-next-log-file-index-maximum-reached (pathname-prefix-string)
;)




;;; The function `write-message-to-log-stream' writes a logbook message to the
;;; stream converting any Unicode newline characters into newlines in the output
;;; stream (using g2-stream-terpri).  If an error in writing occurs, NIL is
;;; returned.  Otherwise, T is returned.  As a side effect, if the writing of
;;; the message is successfull log-file-message-count is incremented.

(defun write-message-to-log-stream (message-text-string stream)
  (when (write-text-string-to-stream message-text-string stream)
    (incff log-file-message-count)
    t))




;;; The function `write-message-to-log-file' takes as input a message-text string
;;; and writes it to the log file.  This is the top-level function that is called
;;; in post-message-on-logbook.  The message-text is not reclaimed by this
;;; function.  T is returned if the message is written successfully.  Otherwise,
;;; nil is returned.
;;;
;;; Log-file-outputting?  could be tested before calling this function (to be
;;; more efficient).  Messages are only written when log-file-outputting?  is
;;; non-nil.
;;;
;;; See the documentation at the start of this section for information on file
;;; name creation, maximum number of files, maximum number of messages per file,
;;; and update frequency.
						       ; when an error occurs
						       ; should log file
						       ; outputting be turned
						       ; off?? 18mar90, cpm.

(defun write-message-to-log-file (message-text)
  ;; Log file output must be turned on and not currently writing a message to
  ;; write a new message to the log file.
  (when (or (null log-file-outputting?)
	    log-file-writing-message?)
    (return-from write-message-to-log-file nil))

  (setq log-file-writing-message? t)

  ;; Open the file when necessary.
  (when (null log-file-stream)
    (if (null log-file-string)
	;; Get the next file and open for writing.
	(if (get-next-log-file)
	    (open-log-file nil)
	    (warning-message
	      1 "Error in opening Log File.  Invalid directory."))
	;; Else, Open the current file name for appending.
	(open-log-file t))
    (when (null log-file-stream)
      ;; Failed to open the stream.  Error message has already been displayed.
      (reset-log-file-information nil nil)
      (setq log-file-outputting? nil)
      ;; bad idea to do the following; instead, do the above! (MHD 6/30/93)
      ;; (change-slot-value log-file-parameters 'log-file-enabled? nil)
      (setq log-file-writing-message? nil)
      (return-from write-message-to-log-file nil)))
    
  ;; Write the logbook message.
  (when (or (null (write-message-to-log-stream
		    message-text log-file-stream))
	    (null (g2-stream-terpri log-file-stream))
	    (null (g2-stream-terpri log-file-stream)))
    ;; should be warning-message instead of warning-message*, since
    ;; warning-message* makes up and prints a name for the current
    ;; computation frame.
    (warning-message
      1 "Write to Log File ~a failed.  The file is being ~
             closed."
      log-file-string)
    (close-log-file)
    (reset-log-file-information nil nil)
    (setq log-file-outputting? nil)
    ;; bad idea to do the following; instead, do the above! (MHD 6/30/93)
    ;; (change-slot-value log-file-parameters 'log-file-enabled? nil)
    (setq log-file-writing-message? nil)
    (return-from write-message-to-log-file nil))
	
  ;; Check if the file should be updated (closed).
  (update-log-file-if-necessary)

  (setq log-file-writing-message? nil)
  (return-from write-message-to-log-file t))






;;;; Posting Messages on Logbooks and Message Boards




;;; `Post-message-on-logbook' ... message-as-text-string is not reclaimed.

;;; Modifications:
;;; 1. Post-message-on-logbook has been modified to write logbook messages to a
;;; log file when the necessary log file parameters are set.
;;;
;;; 2. For NUPEC: (now for all -dkuznick, 7/13/98)
;;;  Tracing and debugging messages can be optionally sent to a file as well
;;;  as the logbook.
;;;
;;;  In the debugging parameters, the user must enable tracing and breakpoints,
;;;  provides a file name in the slot "tracing-file", and starts G2.
;;;  Reset, start, and the editing of tracing-and-breakpoints-enabled? opens or
;;;  closes the file stream as appropriate.
;;;
;;;  Tracing has been modified so that all information for a rule will
;;;  be displayed in one message.  To accomplish this, upon entering a tracing
;;;  context, all messages are held in a variable, and on exit of the context
;;;  all tracing information is shown as one message.

;;; `force-workspace-drawing' is called since log book messages are assumed to
;;; be sufficently high priority to be worth the tax.  Of course this can cause
;;; the caller to consume what ever remains of his quantum.

(def-kb-specific-variable current-logbook? books nil)
(def-kb-specific-variable current-logbook-serial-number? books nil nil reclaim-frame-serial-number)

(defvar allow-user-defined-logbook-handlers-p t)
(defvar currently-posting-message-on-logbook-p nil)

(defun current-logbook? ()
  (when (and current-logbook?
	     current-logbook-serial-number?
	     (frame-has-not-been-reprocessed-p
	       current-logbook? current-logbook-serial-number?))
    current-logbook?))

(defun post-message-on-logbook (text-line from-message-board-p)
  (when (and send-logbook-messages-to-console-p
	     from-message-board-p
	     (not send-messages-to-console-p))
    (notify-user-at-console "message: ~A" text-line))
  (provide-current-logbook)
  (let* ((current-message-unix-time?
	   (compute-current-message-time))
	 (message-text-line
	   (twith-output-to-text-string
	     (print-message-header current-message-unix-time? t)
	     (twrite-string text-line)))
	 (currently-posting-message-on-logbook-p t)
	 (tracing-file-string-if-error? nil))

    (cond ((and (registered-and-active-logbook-handling-procedure-p)
		(pass-loop-check-for-logbook-handling-procedure-p)
		allow-user-defined-logbook-handlers-p
		(invoke-user-defined-logbook-handling-procedure
		  message-text-line)))
	  (t
	   
	   ;; Write any tracing text and logfile text before creating and posting
	   ;; a message in the logbook.  This order is necessary since the newly
	   ;; created logbook message reclaims or incorporates the message text.
	   (when (trace-outputting-to-file? debugging-parameters)
	     (when (or (null (g2-stream-write-line-for-trace-to-file
			       message-text-line
			       (tracing-file-stream debugging-parameters)))
		       (null (g2-stream-terpri 
			       (tracing-file-stream debugging-parameters)))
		       (null (g2-stream-terpri 
			       (tracing-file-stream debugging-parameters))))
	       ;; Turn off the tracing before writing the warning message!
	       (setq tracing-file-string-if-error?
		     (copy-text-string
		       (tracing-file-string debugging-parameters)))
	       (close-tracing-file)))

	   ;; Writeout Logbook messages when log file output is turned on (i.e., the
	   ;; necessary Log File parameters are specified).
	   (when log-file-outputting?
	     (write-message-to-log-file message-text-line))

	   (let ((message
		   (make-message
		     message-text-line nil 'message-format-for-books)))
	     (when (is-g2-save-module-flag-set) 
	       (setq g2-save-module-list (gensym-cons current-message-serial-number g2-save-module-list)))
		
	     (inform-ui-client-interfaces-of-general-update
	       'add-to-logbook message)
	     
	     (set-do-not-save-in-kb message)			    ; was not done by make-message
					;   because inform-message? arg
					;   to make-message was nil
	     (let ((logbook-page
		     (post-message-in-book message current-logbook?)))

	       (when tracing-file-string-if-error?
		 (warning-message*
		     1 "Error when writing to tracing file ~a.  The file is being closed."
		   tracing-file-string-if-error?)
		 (reclaim-text-string tracing-file-string-if-error?))

	       (force-workspace-drawing logbook-page)))))
    (reclaim-managed-float current-message-unix-time?)))

;; Consider having named message boards, just like we (will) have named logbooks!!




(defun g2-stream-write-line-for-trace-to-file (text-string stream)
  (when (write-text-string-to-stream text-string stream)
    t))






;;;; Messages



(def-substitute-for-old-class message-box-format message-format)

;; This and the following def-subsitute-for-old-classes should be eliminated
;; when KBs older than 9/4/87 are no longer supported.  (MHD 10/9/91)


(def-text-box-format message-format-for-books	; exact clone of message-format
  text-box-left-border-width 1			;   but subject to change in width
  text-box-top-border-width 1			;   per logbook parameters -- had
  text-box-right-border-width 1			;   actually been message-format, 
  text-box-bottom-border-width 1		;   that was a bug! (MHD 1/25/91)
  text-cell-lines-justified? nil		; This affects old kbs in that 
  text-cell-paragraph-indentation 0		;   user-created messages might
  text-cell-turnover-line-indentation 14	;   have the bad formats.  Consider
  text-cell-line-spacing 3			;   fixing this with a KB post loading
  text-cell-left-margin 6			;   function in 3.0!!!!! (MHD 1/25/91)
  text-cell-top-margin 5
  text-cell-right-margin 6
  text-cell-bottom-margin 6
  text-cell-line-quadding? nil
  minimum-format-width-for-text-cell 340	; <=>     (MHD 10/11/91)
						; #.(- (get-slot-init-form
						;         'logbook-parameters 'margin-for-pages)
						;      (get-slot-init-form
						;         'logbook-parameters 'width-for-pages))
  maximum-format-width-for-text-cell 1000)	; newly specified. (MHD 3/20/91)



(def-text-box-format message-format
  text-box-left-border-width 1
  text-box-top-border-width 1
  text-box-right-border-width 1
  text-box-bottom-border-width 1
  text-cell-lines-justified? nil
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 14
  text-cell-line-spacing 3
  text-cell-left-margin 6
  text-cell-top-margin 5
  text-cell-right-margin 6
  text-cell-bottom-margin 6
  text-cell-line-quadding? nil
  minimum-format-width-for-text-cell 340
  maximum-format-width-for-text-cell 1000)	; newly specified. (MHD 3/20/91)

(def-text-box-format large-message-format	; as of 9/11/89
  text-cell-font-map (hm18)
  text-cell-line-height 20
  text-cell-baseline-position 17
  text-box-left-border-width 1
  text-box-top-border-width 1
  text-box-right-border-width 1
  text-box-bottom-border-width 1
  text-cell-lines-justified? nil
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 14
  text-cell-line-spacing 3
  text-cell-left-margin 6
  text-cell-top-margin 5
  text-cell-right-margin 6
  text-cell-bottom-margin 6
  text-cell-line-quadding? nil
  minimum-format-width-for-text-cell 340
  maximum-format-width-for-text-cell 1000)	; newly specified. (MHD 3/20/91)

(def-text-box-format extra-large-message-format	; as of 9/11/89
  text-cell-font-map (hm24)
  text-cell-baseline-position 24
  text-cell-line-height 30
  text-box-left-border-width 1
  text-box-top-border-width 1
  text-box-right-border-width 1
  text-box-bottom-border-width 1
  text-cell-lines-justified? nil
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 14
  text-cell-line-spacing 3
  text-cell-left-margin 6
  text-cell-top-margin 5
  text-cell-right-margin 6
  text-cell-bottom-margin 6
  text-cell-line-quadding? nil
  minimum-format-width-for-text-cell 340
  maximum-format-width-for-text-cell 1000)	; newly specified. (MHD 3/20/91)

(setf (corresponding-small-font-format-name 'large-message-format)
      'message-format)

(setf (corresponding-extra-large-font-format-name 'large-message-format)
      'extra-large-message-format)



(def-text-box-format message-format-for-message-board	; could have gotten into 2.0 KBs
  text-box-left-border-width 1				;   prior to 7/10/89 or 1.11KBs
  text-box-top-border-width 1
  text-box-right-border-width 1
  text-box-bottom-border-width 1
  text-cell-lines-justified? nil
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 14
  text-cell-line-spacing 3
  text-cell-left-margin 6
  text-cell-top-margin 5
  text-cell-right-margin 6
  text-cell-bottom-margin 6
  text-cell-line-quadding? nil
  minimum-format-width-for-text-cell 340	; <=>     (MHD 10/11/91)
						; #.(- (get-slot-init-form
						;        'message-board-parameters
						;        'initial-width-of-message-board)
						;      (get-slot-init-form
						;        'message-board 'workspace-margin))
  maximum-format-width-for-text-cell 1000)	; newly specified. (MHD 3/20/91)

(def-substitute-for-old-class message-box message)

(def-class (message (item text-box)
		    (foundation-class message)
		    (class-export-comment
		      "The width, height, and property attributes should be exported ~
 as with text-box"))
  (box-translation-and-text nil (type free text))
  (default-text-box-format-name message-format user-overridable
    (attribute-export-comment "Export"))
  (text-cell-plist-for-text-box	nil user-overridable)
  (minimum-width-of-text-box 0 (type integer) lookup-slot system
    user-overridable do-not-put-in-attribute-tables)
  (minimum-height-of-text-box 0 (type integer) lookup-slot system
    user-overridable do-not-put-in-attribute-tables)
  (inform-message-information?
    nil vector-slot system ; previous: lookup-slot
    (attribute-export-comment "Export: "))
  (default-message-properties-for-class
    nil lookup-slot system (type message-properties) class-slot do-not-save 
    not-user-editable no-accessor do-not-put-in-attribute-tables user-overridable
    (attribute-export-comment "Export: "))
  ;; Snapshots of blocks this message is "about".
  (snapshots-of-blocks-related-to-message nil lookup-slot system do-not-save)
  ;; Used only by native logbooks.
  (message-serial-number? nil vector-slot system do-not-put-in-attribute-tables do-not-save)
  (message-encoded-date? nil vector-slot system do-not-put-in-attribute-tables do-not-save))

(defun message-serial-number-function (message)
  (message-serial-number? message))

(def-slot-value-reclaimer snapshots-of-blocks-related-to-message (snapshots message)
  (reclaim-list-of-block-snapshots snapshots)
  ;; Tidyness.
  (setf (snapshots-of-blocks-related-to-message message) nil))


;;; The function `snapshots-of-valid-blocks-related-to-message' deletes and
;;; reclaims any snapshots which have become invalid, and returns a list
;;; of the valids ones.

(defun snapshots-of-valid-blocks-related-to-message (message)
  (let* ((snapshots (snapshots-of-blocks-related-to-message message))
	 (deceased-blocks?
	   (loop for snapshot in snapshots
		 thereis (not (snapshot-of-block-valid-p snapshot)))))
    (when deceased-blocks?
      (setf (snapshots-of-blocks-related-to-message message)
	    (loop for snapshot in snapshots
		  if (snapshot-of-block-valid-p snapshot)
		    collect snapshot using slot-value-cons
		  else
		    do (reclaim-snapshot-of-block snapshot)))
      (reclaim-slot-value-list snapshots)))

  (snapshots-of-blocks-related-to-message message))



(def-structure (inform-message-information
		 #-development			; (:type vector) in non-development just 
		 (:type vector)			;   to save a bit of space (MHD 4/17/91)
		 (:constructor
		   make-inform-message-information
		   (urgency-of-inform-message?
		     origin-of-inform-message?
		     frame-serial-number-of-origin-of-inform-message?
		     destination-of-inform-message?
		     duration-of-inform-message?
		     timestamp-of-inform-message?)))
  
  (task-to-remove-inform-message?
    nil :reclaimer reclaim-task-to-remove-inform-message)
  (task-to-unhighlight-inform-message? 
    nil :reclaimer reclaim-task-to-unhighlight-inform-message)
  
  (urgency-of-inform-message? nil)
  
  (origin-of-inform-message? nil)		; "sender-", "source-" ??
  (frame-serial-number-of-origin-of-inform-message?
    nil :reclaimer reclaim-frame-serial-number)
  
  (destination-of-inform-message? nil)
  (duration-of-inform-message? nil)
  (timestamp-of-inform-message? nil))		; a "gensym time" or nil



(def-slot-value-reclaimer inform-message-information? (value)
  (if value (reclaim-inform-message-information value)))

(defun reclaim-task-to-remove-inform-message (task?)
  (if task?
      (cancel-task
	(task-to-remove-inform-message?
	  structure-being-reclaimed))))

(defun reclaim-task-to-unhighlight-inform-message (task?)
  (if task?
      (cancel-task
	(task-to-unhighlight-inform-message?
	  structure-being-reclaimed))))



(defmacro task-to-remove-message? (message)
  `(let ((inform-message-information? (inform-message-information? ,message)))
     (if inform-message-information?
	 (task-to-remove-inform-message? inform-message-information?))))

(defmacro task-to-unhighlight-message?  (message)
  `(let ((inform-message-information? (inform-message-information? ,message)))
     (if inform-message-information?
	 (task-to-unhighlight-inform-message? inform-message-information?))))

(defmacro origin-of-message? (message)
  `(let ((inform-message-information? (inform-message-information? ,message)))
     (if inform-message-information?
	 (origin-of-inform-message? inform-message-information?))))

(defmacro urgency-of-message? (message)
  `(let ((inform-message-information? (inform-message-information? ,message)))
     (if inform-message-information?
	 (urgency-of-inform-message? inform-message-information?))))

(defmacro frame-serial-number-of-origin-of-message? (message)
  `(let ((inform-message-information? (inform-message-information? ,message)))
     (if inform-message-information?
	 (frame-serial-number-of-origin-of-inform-message?
	   inform-message-information?))))

(defmacro destination-of-message? (message)
  `(let ((inform-message-information? (inform-message-information? ,message)))
     (if inform-message-information?
	 (destination-of-inform-message? inform-message-information?))))

(defmacro duration-of-message? (message)
  `(let ((inform-message-information? (inform-message-information? ,message)))
     (if inform-message-information?
	 (duration-of-inform-message? inform-message-information?))))

(defmacro timestamp-of-message? (message)
  `(let ((inform-message-information? (inform-message-information? ,message)))
     (if inform-message-information?
	 (timestamp-of-inform-message? inform-message-information?))))




;;; Inform-message-p is true iff message was created via an inform action.

(defmacro inform-message-p (message)
  `(origin-of-message? ,message))




;;; `get-origin-of-message-if-appropriate' ... if block is a message that has
;;; an associated "origin of message" item that is not deleted, that item is
;;; returned.

(defun get-origin-of-message-if-appropriate (message)
  (when (frame-of-class-p message 'message)
    (let ((origin-of-message? (origin-of-message? message)))
      (when origin-of-message?			    ; Inform messages.
	(let ((frame-serial-number
		(frame-serial-number-of-origin-of-message? message)))
	  (unless (frame-has-been-reprocessed-p
		    origin-of-message?
		    frame-serial-number)
	    origin-of-message?))))))




(defparameter new-message-highlight-color 'foreground)






;;; `make-message' ... origin-frame? is the frame which triggered the sending
;;; of the message -- typically a rule frame.

;;; If text-line? is null, a message with blank text will be created.  Its
;;; size will be determined by its minimum width and minimum height class
;;; defaults.

;;; Class? defaults to MESSAGE.  

;;; Inform-message? should be true if this is an inform message, as opposed to
;;; a message for the logbook.  If inform-message? is not true, the args
;;; urgency, duration?, origin-frame?, and destination have no meaning.

;;; An inform message created by make-message is set to not be saved in a KB.
;;; Note that messages can also be created from the workspace menu, in which
;;; case they are created in the standard way for text boxes.  Messages created
;;; in this way do get non-default settings for slots specific to inform
;;; messages: urgency, duration?, origin-frame?, or destination.  These would
;;; have to be filled in if they wanted to be used.  They are also then
;;; typically non-transient and get saved in KBs.

(defun make-message (&optional
		      text-line? message-class? text-box-format-name?
		      inform-message? urgency? duration?
		      origin-frame? destination? do-not-reformat?)
  #+development
  (test-assertion
    (or (null message-class?) (subclassp message-class? 'message)))
  (let ((message
	  (make-free-text-box
	    (or text-line? (copy-constant-wide-string #w""))
	    (or message-class? 'message)
	    text-box-format-name?
	    nil nil do-not-reformat?)))

    (setf (message-serial-number? message) current-message-serial-number
	  (message-encoded-date? message) (simple-encode-date current-message-unix-time?))

    (cond (inform-message?
	   (set-do-not-save-in-kb message)
	   (setf (inform-message-information? message)
		 (make-inform-message-information
		   urgency? origin-frame?
		   (if origin-frame? (copy-frame-serial-number
				       (frame-serial-number origin-frame?)))
		   destination? duration? gensym-time))
	   (when (highlight-new-messages? message-board-parameters)
	     (change-text-box-property
	       message 'highlight-color new-message-highlight-color)))

	  (snapshots-of-related-blocks
	   (setf (snapshots-of-blocks-related-to-message message)
		 snapshots-of-related-blocks)
	   (setf snapshots-of-related-blocks nil)))
    
    message))

;; Consider having options to this function control settings do-not-save-in-kb
;; and transient flags.






;;; Change-text-of-message ... called from ACTIONS.  Text-string is incorporated
;;; into the new text of message.  At present, the change is noted as a KB
;;; state change unless do-not-note-as-kb-state-change? is true.

(defun change-text-of-message (message text-string
			       &optional do-not-note-as-kb-state-change?)
  (let ((note-as-kb-state-change? (not do-not-note-as-kb-state-change?))
	(do-not-note-permanent-changes-p note-as-kb-state-change?))
    (unless do-not-note-as-kb-state-change?
      (note-kb-state-change message 'text))
    (change-slot-value
      message 'box-translation-and-text
      (slot-value-cons
	no-value
	(convert-text-string-to-text text-string)))))










;;; Update-default-message-properties-in-instances updates STRICT instances of
;;; subclass of only the default-message-property slots that are inherited from
;;; class.

(defun update-default-message-properties-if-inherited-in-instances (class subclass)
  (let* ((format-name?
	   (slot-inherited-from-class-p class subclass 'default-text-box-format-name))
	 (minimum-width?
	   (slot-inherited-from-class-p class subclass 'minimum-width-of-text-box))
	 (minimum-height?
	   (slot-inherited-from-class-p class subclass 'minimum-height-of-text-box)))
    
    (loop with format-frame? =
	  (when format-name?
	    (get-or-make-format-frame
	      (get-slot-init-form class 'default-text-box-format-name)))
	  for message being each strict-class-instance of subclass
	  for message-class-description = (class-description-slot message)
	  do
      (erase-images-of-block message nil)
      (when format-name?
	(setf (text-box-format message) format-frame?)
	(when g2-has-v5-mode-windows-p
	    (send-ws-representations-item-virtual-attribute-change
	      message (virtual-attribute 'format-type) nil))
	(let ((slot-description
		(get-slot-description-of-class-description
		  'default-text-box-format-name message-class-description)))
	  (set-slot-description-value-without-noting 
	    message slot-description (slot-init-form slot-description))))
      (when minimum-width?
	(let ((slot-description
		(get-slot-description-of-class-description
		  'minimum-width-of-text-box message-class-description)))
	  (set-slot-description-value-without-noting
	    message slot-description (slot-init-form slot-description))))
      (when minimum-height?
	(let ((slot-description
		(get-slot-description-of-class-description
		  'minimum-height-of-text-box message-class-description)))
	  (set-slot-description-value-without-noting
	    message slot-description (slot-init-form slot-description))))
      (let ((slot-description
	      (get-slot-description-of-class-description
		   'text-cell-plist-for-text-box message-class-description)))
	(set-slot-description-value-without-noting
	  message slot-description (slot-init-form slot-description)))
      (reformat-text-box-in-place message)
      (draw-images-of-block message nil))))

;; Later: do the loop only when one or more elements is inherited; for now, we
;; cannot tell if text-cell-plist-for-text-box is (partially) inherited, so we
;; must assume that it is and always revert that slot in each instance.  Fixing
;; this will save a lot of redrawing and some other work.  (MHD 5/12/92)

;; The above assumes that the text-cell-plist-for-text-box slot is either entirely
;; shared with the slot init form, or is entirely a unique slot value.

;; This is called from update-default-message-properties-governed-by-this-definition,
;; in definitions, q.v.  (MHD 5/11/92)







;;;; Message Boards



;; Basic documentation about message boards by ML, 4 Sept, 89

;;; (1) There is exactly one message-board instance per G2 process. It is an
;;; item, initially has the name MESSAGE-BOARD. (2) The user could delete it,
;;; in which case there is no message board.  (He could also change its name,
;;; in which case ... [?!].)  But putting a message on the message board via
;;; inform will re-instantiate it. (3) It is now activated by system-start
;;; and deactivated by system-reset exactly in the manner of kb-workspaces.
;;; This causes items placed upon it to be active.






(def-format-class (message-board-format format-frame)	; this is really OBSOLETE!! (See the
						;   system table for message boards.)
  (spacing-between-message-board-subblocks 10 vector-slot system)
  (initial-message-board-width 400)
  (initial-message-board-height 400))

;; As of 10/9/91, in 3.0 development, instances of this class stopped being
;; created and put into message boards.  As of a few months earlier in 3.0
;; development, however, all format-frame instances started being saved in
;; KBs; therefore, instances of the above class might exist in some KBs saved
;; out in 3.0 pre-alpha prior to today.  And, as things now stand, they would
;; continue to live and be saved out in KBs derived from KBs in which they
;; were saved out.  Consider writing something to get rid of these forever
;; before the final release of 3.0.  (MHD 10/9/91)





(def-class (message-board (item non-kb-workspace) not-normally-transient)
  (workspace-margin 5))

;; There should never have been any instances of message-board ever saved in
;; a KB in the history of G2; message-board has always been non-kb-workspace
;; subclass.





(defvar send-messages-to-logbook-p nil)
(defvar send-messages-to-console-p nil)

;;; Post-on-message-board ... text-line is the string that should be printed
;;; out on the logbook and message board.  It is reclaimed by this function.

;;; If workspace? is nil, the message is put on the current message board, which
;;; will be created shown if it is hidden.  If non-nil, it should be a
;;; workspace.  The workspace is not automatically shown if it hidden.

;;; When workspace? is non-nil, target-block? may also be specified non-nil.  If
;;; so, it should be a block whose superblock is workspace?.  In that case, the
;;; column of messages will be put under that block (or above, instead, if above-
;;; target? is non-nil).  

;;; When no target block is specified, the column appears under the name box, if
;;; there is one on the workspace the message is put on, or, if there is no name
;;; box, under the top, left corner of the workspace.

(defun post-on-message-board
    (text-line urgency? duration? origin-frame? destination?
	       &optional workspace? target-block? above-target? do-not-reformat?)
  (cond ((and (registered-and-active-message-board-handling-procedure-p)
	      (pass-loop-check-for-message-board-handling-procedure-p)
	      (invoke-user-defined-message-board-handling-procedure text-line)))
	(t
	 (let* ((current-message-serial-number
		  (increment-message-serial-number))
		(current-message-unix-time?
		  (compute-current-message-time))
		(gensym-time gensym-time)
		(message-board
		  (or
		    (if (and workspace? (workspace-p workspace?))
			workspace?)
		    (if (and target-block?
			     (workspace-p (superblock? target-block?)))
			(superblock? target-block?))
		    (progn (provide-current-message-board)
			   current-message-board?)))
		(message
		  (make-message
		    (twith-output-to-text-string
		      (print-message-header current-message-unix-time? nil)
		      (when do-not-reformat?
			(twrite-line-separator))
		      (twrite-string text-line))
		    nil
		    (if (frame-of-class-p message-board 'message-board)
			'message-format-for-message-board)
		    t urgency? duration? origin-frame? destination?
		    do-not-reformat?))
		(maximum-number-of-entries
		  (maximum-number-of-message-board-entries
		    message-board-parameters)))
	   (inform-ui-client-interfaces-of-general-update
	     'add-to-message-board message)
	   (loop until
		 (<f
		   (loop with oldest-message? = nil	; make room for next message
			 with oldest-message-timestamp
			 with count = 0
			 for subblock being each subblock of message-board
			 when (and (frame-of-class-p subblock 'message)
				   (inform-message-p subblock))
			   do (incff count)
			      (let ((message-timestamp (timestamp-of-message? subblock)))
				(cond
				  ((or (null oldest-message?)
				       (null message-timestamp)
				       (null oldest-message-timestamp)
				       ;; don't absolutely assume message timestamps --
				       ;;   ones from logbooks, for example, do not have
				       ;;   them and could conceivably be moved here.
				       (<=i message-timestamp
					    oldest-message-timestamp))	  
				   (setq oldest-message? subblock)
				   (setq oldest-message-timestamp message-timestamp))))
			 finally
			   (return
			     (cond
			       ((and oldest-message?
				     (>=f count maximum-number-of-entries))
				(delete-frame oldest-message?)
				(-f count 1))
			       (t count))))
		   maximum-number-of-entries))
	   (cond
	     ((highlight-new-messages? message-board-parameters)
	      ;; highlighting already put in as a property when we create the message
	      (with-future-scheduling 
		  ((task-to-unhighlight-inform-message? (inform-message-information? message))
		    2 (future-interval 1) nil nil t
		   (nil 'reclaim-frame-serial-number))
		(unhighlight-recent-message
		  message
		  (copy-frame-serial-number (frame-serial-number message))))))
	   (let ((target-block?
		   (if (and target-block?		; check earlier!!
			    (eq (superblock? target-block?) message-board))
		       target-block?)))
	     (when (and (current-message-board?)
			(eq message-board current-message-board?)
			(prefer-native-message-board message-board-parameters))
	       (append-message-to-all-native-message-boards message))
	     (post-message-on-message-board
	       message message-board
	       target-block?
	       (if target-block? above-target?)))	; check earlier!!
	   (cond
	     (duration?
	      (let ((real-time-duration?
		      (and (of-class-p origin-frame? 'block)
			   (runs-while-inactive-p origin-frame?))))
		;; Note that the g2-future-interval and future-interval
		;; functions require fixnum arguments.  When we fix the duration
		;; to allow floats, this must be changed.  -jra 1/19/97
		(with-future-scheduling
		    ((task-to-remove-inform-message?
		       (inform-message-information? message))
			 2 (if real-time-duration?
			   (future-interval duration?)
			   (g2-future-interval duration?))
		     nil nil real-time-duration?
		     (nil 'reclaim-frame-serial-number))
		  (execute-message-removal-task
		    message
		    (copy-frame-serial-number (frame-serial-number message)))))))
	   (when (or (log-inform-messages? logbook-parameters)
		     send-messages-to-logbook-p)
	     (post-message-on-logbook text-line t))
	   (when send-messages-to-console-p
	     (notify-user-at-console "message: ~A" text-line))
	   (reclaim-managed-float current-message-unix-time?)
	   (reclaim-text-string text-line)))))




(defun-void unhighlight-recent-message (message frame-reference-serial-number)
  (cond
    ((not (frame-has-been-reprocessed-p
	    message frame-reference-serial-number))
     (highlight-or-unhighlight-for-slot
       message 'box-translation-and-text nil
       new-message-highlight-color t)
     (cancel-task
       (task-to-unhighlight-inform-message?
	 (inform-message-information? message))))))






;;; Post-message-on-message-board ...

(defun post-message-on-message-board
       (message message-board target-block? above-target?)
  (loop with height = (height-of-block message)
	with workspace-margin = (workspace-margin message-board)
	with interspacing
	  = (spacing-between-message-board-entries message-board-parameters)
	with target-block?
	  = (or target-block?
		(loop for subblock being each subblock of message-board
		      thereis
			(if (frame-of-class-p subblock 'workspace-name-box)
			    subblock)))
	with extreme-top-edge-of-target
	with extreme-bottom-edge-of-target
	with extreme-left-edge-of-target
	  = (if target-block?
		(multiple-value-bind (left top right bottom)
		    (determine-extreme-edges-of-block target-block?)
		  (declare (ignore right))
		  (setq extreme-top-edge-of-target top)
		  (setq extreme-bottom-edge-of-target bottom)
		  left))
	with potential-left-edge
	  = (or (if target-block? extreme-left-edge-of-target)
		(+w (left-edge-of-block message-board) workspace-margin))
	with potential-right-edge
	  = (+w potential-left-edge (width-of-block message))
	as potential-top-edge
	   = (or (if target-block?
		     (if above-target?
			 (-w extreme-top-edge-of-target
			     interspacing height)
			 (+w extreme-bottom-edge-of-target interspacing)))
		 (+w (top-edge-of-block message-board) workspace-margin))
	   then (if above-target?
		    (-w potential-top-edge interspacing)
		    (+w potential-top-edge interspacing))	; magic number?
	until (loop for subblock being each subblock of message-board
		    as subblock-is-inform-message?
		       = (and (frame-of-class-p subblock 'message)
			      (inform-message-p subblock))
		    when (block-or-subblocks-overlap-rectangle-p
			   subblock
			   potential-left-edge
			   (-w potential-top-edge
			       (if subblock-is-inform-message? interspacing 0))
			   potential-right-edge
			   (+w potential-top-edge height
			       (if subblock-is-inform-message? interspacing 0)))
		      do (setq potential-top-edge
			       (if above-target?
			 	   (-w (nth-value 1 (determine-extreme-edges-of-block subblock)) height)
			 	   (nth-value 3 (determine-extreme-edges-of-block subblock))))
			 (return nil)
		    finally (return t))
	finally
	  (add-to-workspace
	    message message-board
	    potential-left-edge potential-top-edge t t)))




;;; Clear-inform-messages deletes all inform messages.  Note that this does not
;;; affect copies of inform messages logged in the logbook.

(defun clear-inform-messages ()
  (loop for message being each class-instance of 'message
	when (inform-message-p message)
	  do (delete-frame message)))





;;; Make-message-board creates an instance of message-board, with name =
;;; MESSAGE-BOARD, and width and height given by initial-width/height-
;;; of-message-board slots of message-board-parameters.  The resulting workspace
;;; is also activated, i.e., via the activate-if-possible-and-propagate method,
;;; unless the system is reset.

(defun make-message-board ()
  (let ((message-board
	  (make-workspace
	    'message-board 'message-board nil nil
	    (initial-width-of-message-board message-board-parameters)
	    (initial-height-of-message-board message-board-parameters))))
    (if (or system-is-running system-has-paused)
	(funcall-method 'activate-if-possible-and-propagate message-board))
    message-board))

	



(defun provide-current-logbook ()
  (if (or (null current-logbook?)
	  (not (frame-serial-number-equal
		 (frame-serial-number current-logbook?)
		 current-logbook-serial-number?)))
      (let ((logbook (make-entity 'logbook)))
	(frame-serial-number-setf
	  current-logbook-serial-number? (frame-serial-number logbook))
	(setf (title-of-book? logbook)
	      (copy-constant-wide-string #w"Operator Logbook"))
	(setq current-logbook? logbook))))



;;; Execute-message-removal-task assumes, unless message has been deleted, that
;;; message has non-nil inform-message-information? in which a scheduled task
;;; to remove message is stored.  If message has not been deleted, this deletes
;;; message after cancelling the task.

(defun-void execute-message-removal-task
    (message message-frame-serial-number)
  ;; I think this could be simply
  ;;   (delete-frame message)
  ;; since the reclaimer for the message calls
  ;; reclaimers that should end up removing the
  ;; task .... but do this after release 3.0 is
  ;; out, when I have time to make sure. (MHD 11/1/91)
  (unless (frame-has-been-reprocessed-p message message-frame-serial-number)
    (cancel-task
      (task-to-remove-inform-message? (inform-message-information? message)))
    (delete-frame message)))





;;; Close-logbooks should eventually finish streaming out logbooks.

(defun close-logbooks ()
  (setq current-message-serial-number 1)
  (setq next-serial-number-to-be-generated 1)
  (setq current-message-board? nil)		; random!
  (setq current-logbook? nil))			; ditto.








(defun redisplay-logbook-in-current-workstation ()
  (when (and servicing-workstation?     ; safest: iff there is
             (is-operator-logbook-enabled (current-workstation)))
    (provide-current-logbook)           ;   a current workstation
    (when (and (use-native-logbook-p current-workstation-window)
               (stack-of-pages current-logbook?))
      (show-native-logbook current-workstation-window))
    (neatly-stack-logbook-pages-in-pane
      current-workstation-detail-pane current-logbook?)))

;; Calling this from slot putters of logbook-parameters needs some review, &
;; would probably bear documenting.  Consider later! (MHD 7/12/92)



(defun message-on-message-board-p (block)
  (let ((superblock? (superblock? block)))
    (and (frame-of-class-p block 'message)
	 superblock?
	 (current-message-board?)
	 (eq superblock? current-message-board?))))



(defun message-on-logbook-p (block)
  (let ((superblock? (superblock? block)))
    (and (frame-of-class-p block 'message)
	 superblock?
	 (frame-of-class-p superblock? 'logbook-page))))





;;;; Running Heads



(def-text-box-format running-head-format
  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0
;  table-row-boundary-width 5   ; maybe use this info to fix for box conversion!! (MHD 7/23/87)
  text-cell-left-margin 0
  text-cell-top-margin 0
  text-cell-right-margin 0
  text-cell-bottom-margin 0

  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 0
  text-cell-lines-justified? nil

  minimum-format-width-for-text-cell 440
  maximum-format-width-for-text-cell 440)



(def-class (running-head text-box)
  (box-translation-and-text nil (type nil text))
  (default-text-box-format-name running-head-format))



(defun make-running-head (text-line)
  (make-free-text-box text-line 'running-head))


;; Takes the place of (declare-unselectable-class-of-subblock running-head)
;; in facilities.

(def-class-method generate-spot (running-head mouse-pointer)
  (declare (ignore running-head))
  (generate-workspace-background-spot mouse-pointer))






;;;; Page Numbers



(def-class (page-number text-box)
  (box-translation-and-text nil (type nil text))
  (default-text-box-format-name running-head-format))


(defun make-page-number (text-line)
  (make-free-text-box text-line 'page-number))

(def-class-method generate-spot (page-number mouse-pointer)
  (declare (ignore page-number))
  (generate-workspace-background-spot mouse-pointer))










;;;; Notifications



;; notify-user has been moved to DEBUG to reduce the number of forward refs.
;; notify-user-2 is here to pick up those curious macros


;;; The function `notify-user-2' is called directly, and also by deferred
;;; notifications.

(defun notify-user-2 (notification-string)
  (call-per-actual-arg-if-necessary
      notification-string notify-user-2
    (if (not (check-ok))
	(plant-seed)))
  (increment-message-serial-number)
  (post-message-on-logbook notification-string nil)
  (reclaim-text-string notification-string))


;;; The function `notify-engineer' is presently a synonym for notify-user.

(defun notify-engineer (notification-as-format-string 
			 &optional
			 (arg1 no-arg) (arg2 no-arg) (arg3 no-arg)
			 (arg4 no-arg) (arg5 no-arg) (arg6 no-arg)
			 (arg7 no-arg) (arg8 no-arg) (arg9 no-arg))
  (call-per-number-of-actual-args
    notify-user 1 notification-as-format-string	
    arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9))

;; There was a also notify-operator function until today.  I removed it because
;; there were no callers.  (MHD 2/9/90)




;;; The function `notify-user-at-workstation' is to be used for
;;; workstation-specific messages.  This may only be called from within a
;;; for-workstation context.  These are usually messages that are side-effects
;;; of user interaction.  AT PRESENT, THIS DOES NOTHING -- THIS WILL BE
;;; IMPLEMENTED LATER!

(defun notify-user-at-workstation
    (notification-as-format-string 
      &optional
      (arg1 no-arg) (arg2 no-arg) (arg3 no-arg)
      (arg4 no-arg) (arg5 no-arg) (arg6 no-arg)
      (arg7 no-arg) (arg8 no-arg) (arg9 no-arg))
  (declare
    (ignore	   
      notification-as-format-string 
      arg1 arg2 arg3
      arg4 arg5 arg6
      arg7 arg8 arg9)))

;; This was implemented in order to be able to redirect calls to notify user that
;; were workstation specific, such as "<keystroke> not legal here!", "Cannot transfer
;; objects to non-KB workspaces!", etc. (MHD 3/13/90)



;;; `Post-prominent-notification' posts a message whose text is made from text-
;;; line, which is reclaimed by this function, on each logged-in workstation
;;; in service.  In addition, a notification to the operator logbook is done.

(defparameter width-for-prominent-notification-workspaces 400)
(defparameter height-for-prominent-notification-workspaces 100)

(defun post-prominent-notification (text-line &optional width? height? disarm?)
  (notify-user "~a" text-line)
  (let ((workspace
	  (make-workspace
	    'temporary-workspace nil
	    (make-message text-line)
	    nil
	    (or width? width-for-prominent-notification-workspaces)
	    (or height? height-for-prominent-notification-workspaces)
	    (if disarm? -1))))
    (loop for workstation in workstations-in-service
	  as gensym-window = (window-for-workstation workstation)
	  when (eq (workstation-login-state workstation) 'logged-in)
	    do (put-workspace-on-pane
		 workspace (detail-pane gensym-window)
		 'center 'center nil))
    (force-process-drawing)
    workspace))

;; Note that the message should not be user editable!  

;; Note that the time and message serial number appear in the logbook notification
;; but not in the new workspace.  Is that ok?

;; The initial (and so far the only) use for this is for warning of impending timeout
;; time-limited (i.e. evaluation or demo) copies of G2.  This is mostly a prototype.
;; (MHD 2/2/90)








;;; `do-long-operation-with-notification' ... message-text-string is a
;;; text-string to be incorporated into the message.  It should not contain any
;;; tformat directives.  If defer-putting-up-notification? is true, this does
;;; not actually put up the notification; instead, body must contain one or
;;; more calls to either put-up-long-operation-notification or
;;; put-up-long-operation- notification-if-timely, q.v.

;;; This macro contains an unwind-protect around body to clean up the
;;; notification upon exit, local or not.  Note that body may return any number
;;; of values.

;;; This can be used even if the workspace it puts up might be deleted during
;;; body, and even if the KB might be cleared.

(defvar long-operation-notification-has-been-put-up? nil)
(defvar fixnum-time-at-start-of-current-long-notification)
(defvar current-long-operation-notification-workspace)


;;; The variable `doing-long-operation-with-notification?' is true only within
;;; the scope of the macro do-long-operation-with-notification.  Otherwise, it
;;; has a global binding of nil.  Ordinarily only that macro should bind this.
;;; (But see the documented limitation for
;;; put-up-long-operation-notification-if-timely for why you might bind it
;;; yourself.)

(defvar doing-long-operation-with-notification? nil)


;;; `put-up-long-operation-notification-if-timely' puts up the current long
;;; notification if a long operation is being done, if the notification has not
;;; been put up yet, and if interval-in-milliseconds has expired since the start
;;; of the operation.

;;; This is intended to be called many times during a long operation, and does
;;; a fairly efficient check for "timeliness"; the dominating cost is a call to
;;; get-fixnum-time.

;;; A limitation of this is that it may be called even if not within the scope
;;; of a long operation; since there is no "ID" kept for a long operation's
;;; scope, a caller that uses this might bump into a higher long operation scope
;;; unexpectedly.  That problem is not solved completely, but you can bind
;;; doing-long-operation-with-notification?  to nil around code that calls this
;;; to keep it from ever putting up a notification.

;;; This is coded as a macro for maximum speed of testing whether a notification
;;; is to be put up; if so, it calls out to a function.  So, it tests quite
;;; fast, in order to make it suitable for use in time-critical code, but also
;;; takes up little space.

(defmacro put-up-long-operation-notification-if-timely
	  (interval-in-milliseconds)
  (avoiding-variable-capture (interval-in-milliseconds)
    `(if (and doing-long-operation-with-notification?
	      (not long-operation-notification-has-been-put-up?)
	      (>=f (fixnum-time-difference
		     (get-fixnum-time)
		     fixnum-time-at-start-of-current-long-notification)
		   (fixnum-time-interval ,interval-in-milliseconds)))
	 (put-up-long-operation-notification-now))))

;; For efficiency, we might change the protocol to have so that the caller
;; always provides interval-in-fixnum-time-units, rather than
;; interval-in-milliseconds, to avoid doing the conversion here every time.



;;; `put-up-long-operation-notification' puts up the current long notification
;;; if a long operation is being done, and if the notification has not been put
;;; up yet.  It is like put-up-long-operation-notification-if-timely, except
;;; that it does not wait until an time interval has been exceeded.

(defun put-up-long-operation-notification ()
  (put-up-long-operation-notification-if-timely 0))

;; At present, this function is "stubbed" in tw-patches, allowing it to be
;; referenced in FONT-FILES, a Telewindows module.  This also added the requirement
;; that this be a function, so do not change that, although it is somewhat of a
;; kludge.  (MHD 11/10/92)



(defun put-up-long-operation-notification-now ()
  ;; may want to support TWII
  (loop for workstation in workstations-in-service
	as gensym-window = (window-for-workstation workstation)
	do (put-workspace-on-pane
	     current-long-operation-notification-workspace
	     (detail-pane gensym-window)
	     'center 'center nil))
  (force-process-drawing)
  (setq long-operation-notification-has-been-put-up? t))
  

(defmacro do-long-operation-with-notification
    ((message-text-string &optional defer-putting-up-notification?)
     &body body)
  `(let* ((current-long-operation-notification-workspace			; ABSTRACT THIS!!!
	    (make-workspace
	      'temporary-workspace nil
	      (make-message 
		(tformat-text-string
		  "~a~%Please wait . . . " ,message-text-string))
	      nil
	      width-for-prominent-notification-workspaces
	      height-for-prominent-notification-workspaces))
	  (frame-serial-number
	    (copy-frame-serial-number (current-frame-serial-number)))
	  (kb-serial-number
	    current-kb-serial-number)
	  (fixnum-time-at-start-of-current-long-notification
	    (get-fixnum-time)))
     (unwind-protect
         (let ((doing-long-operation-with-notification? t)
               (long-operation-notification-has-been-put-up? nil))
           (unless ,defer-putting-up-notification?
             (put-up-long-operation-notification-if-timely 0))
           ,@body)
       (when (and (=f current-kb-serial-number kb-serial-number)
                  (not (frame-has-been-reprocessed-p
                        current-long-operation-notification-workspace
                        frame-serial-number)))
         (delete-frame
           current-long-operation-notification-workspace))
       (reclaim-frame-serial-number frame-serial-number))))


;;; User Defined Logbook and Message Board Handlers


;;; The macro `def-user-defined-message-handler' is used to define
;;; G2 system procedures to allow the user to register a procedure
;;; to handle messages, deregister a procedure, and to retrieve
;;; the current procedure. 
;;;
;;; Where X is the argument to this macro:
;;;
;;; The G2 system procedures that are defined are:
;;; G2-REGISTER-X-MESSAGE-HANDLER
;;; G2-DEREGISTER-X-MESSAGE-HANDLER
;;; G2-GET-X-MESSAGE-HANDLER
;;;
;;; The KB-specific variable containing the registered procedure is:
;;; USER-DEFINED-X-HANDLING-PROCEDURE?
;;;
;;; The function to check for looping involving the message handler
;;; is:
;;; PASS-LOOP-CHECK-FOR-X-HANDLING-PROCEDURE-P
;;;
;;; The function to invoke the handling procedure is:
;;; INVOKE-USER-DEFINED-X-HANDLING-PROCEDURE
;;;
;;; This macro requires the following functions which are defined in STACK-KERN
;;; check-user-defined-message-handler-arguments
;;; invoke-user-defined-message-handler
;;; pass-loop-check-for-user-defined-message-handler-p 

(defmacro def-user-defined-message-handler
    (handler-name)
  (let ((name-of-g2-sysproc-to-register-handler
	  (format-symbol "G2-REGISTER-~A-MESSAGE-HANDLER"
			 handler-name))
	(name-of-g2-sysproc-to-deregister-handler 
	  (format-symbol "G2-DEREGISTER-~A-MESSAGE-HANDLER"
			 handler-name))
	(name-of-g2-sysproc-to-get-handler
	  (format-symbol "G2-GET-~A-MESSAGE-HANDLER"
			 handler-name))
	(kb-specific-var
	  (format-symbol "USER-DEFINED-~A-HANDLING-PROCEDURE\?"
			 handler-name))
	(kb-specific-var-fsn
	  (format-symbol "USER-DEFINED-~A-HANDLING-PROCEDURE-FSN"
			 handler-name))
	(name-of-invocation-function
	  (format-symbol "INVOKE-USER-DEFINED-~A-HANDLING-PROCEDURE"
			 handler-name))
	(name-of-loop-check-function
	  (format-symbol "PASS-LOOP-CHECK-FOR-~A-HANDLING-PROCEDURE-P"
			 handler-name))
	(name-of-registered-and-active-function
	  (format-symbol "REGISTERED-AND-ACTIVE-~A-HANDLING-PROCEDURE-P"
			 handler-name))
	)
    `(progn
       (def-kb-specific-variable ,kb-specific-var books nil nil nil)

       (def-kb-specific-variable ,kb-specific-var-fsn books nil nil reclaim-frame-serial-number)
       
       (defun-for-system-procedure ,name-of-g2-sysproc-to-register-handler
	   (procedure)
	 (cond  ((and (of-class-p procedure 'procedure)
		      (not (of-class-p procedure 'method-declaration))
		      (check-user-defined-message-handler-arguments procedure))
		 (setq ,kb-specific-var procedure)
		 (frame-serial-number-setf
		   ,kb-specific-var-fsn
		   (frame-serial-number procedure)))))

       (defun-for-system-procedure ,name-of-g2-sysproc-to-deregister-handler
	   ()
	 (reclaim-frame-serial-number ,kb-specific-var-fsn)
	 (setq ,kb-specific-var nil)
	 (setq ,kb-specific-var-fsn nil))


       (defun-for-system-procedure ,name-of-g2-sysproc-to-get-handler 
	   ()
	 (cond ((and ,kb-specific-var
		     (framep ,kb-specific-var)
		     (of-class-p ,kb-specific-var 'procedure)
		     (not (frame-has-been-reprocessed-p
			    ,kb-specific-var
			    ,kb-specific-var-fsn))) 
		,kb-specific-var)
	       (t (make-evaluation-truth-value-function falsity)))
	 )

       (defun ,name-of-invocation-function
	   (message-text-line) 
	 (invoke-user-defined-message-handler message-text-line
					      ,kb-specific-var)
	 )

       (defun ,name-of-loop-check-function
	   ()
	 (pass-loop-check-for-user-defined-message-handler-p 
	   ,kb-specific-var))

       (defun ,name-of-registered-and-active-function
	   ()
	 (and (of-class-p ,kb-specific-var 'procedure)
	      (not (frame-has-been-reprocessed-p ,kb-specific-var
						 ,kb-specific-var-fsn))
	      (runnable-p-function ,kb-specific-var)))
       )))




;;; Define G2 system procedures for logbook message handler

(def-user-defined-message-handler logbook)

;;; Define G2 system procedures for message-board handler

(def-user-defined-message-handler message-board)





;;;; Telewindows2 access for Books


(defun get-current-logbook-sequence ()
  (cond
    ((current-logbook?)
     (loop with list = '()
           for page in (stack-of-pages current-logbook?)
	   do
       (loop for subblock being each subblocks of page
	     do
	 (when (frame-of-class-p subblock 'message)
	   (eval-push subblock list)))
	   finally
	     (setq list (sort-list list #'frame-serial-number-<-function
				   #'frame-serial-number-function))
	     (let ((sequence
		     (allocate-evaluation-sequence list)))
	       (return sequence))))
    (t
     (allocate-evaluation-sequence nil))))


(defun get-current-message-board-sequence ()
  (cond
    ((current-message-board?)
     (loop with list = '()
	   for subblock being each subblocks of current-message-board?
	   do
       (when (frame-of-class-p subblock 'message)
	 (eval-push subblock list))
	   finally
	     (setq list (sort-list list #'frame-serial-number-<-function
				   #'frame-serial-number-function))
	     (let ((sequence
		     (allocate-evaluation-sequence list)))
	       (return sequence))))
    (t
     (allocate-evaluation-sequence nil))))

;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module EDIT2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson and Mark H. David






;;;; Forward References in EDIT

(declare-forward-references

  (note-kb-state-change-to-slot-by-saving-text function kb-save2)
  (current-kb-serial-number                    variable kb-save2)

  (get-current-user-name                       function kb-load1)

;  (find-object-near-mouse             function run)
  (find-object-near-workstation-event function run)

  (reason-for-bad-parse-as-string             function grammar0)

  (workstation-for-g2-window?-function        function)
  (embedded-rule-p                            function)
  (enter-dialog                               function)
  (confirm-or-cancel                          function)
  (get-image-if-any                           function)

;  (attribute-operation-is-allowed-p function) ; FILTERS
  (non-menu-choice-permitted-p function)

  (do-not-update-frame-authors?  variable queries)

  (evaluation-true-value                variable sets)
  (evaluation-false-value               variable sets)
  
  (recompile-cell-array function)	; CELLS
  
  (restrict-destabilization-p function)

  (do-pathname-component-conversion-if-necessary function KB-LOAD1)

  (make-icon-cell-for-entity function)
  (make-editor-subcommand-button function)
  (get-overall-minimum-width-for-subcommand-menu-column function)
  (indicate-editor-subcommand-button-pending-state function)
  (enable-or-disable-editor-subcommand-button function)
  (editor-subcommand-name-function function)

  (saving-parameters variable)		; KB-SAVE3
  )




;;;; Maintaining Authors and Times of Last Edit



;;; The slot that appears to the users as the `authors' attribute (internally
;;; the frame-author-or-authors slot) on various classes, in general
;;; definitional items (including subclasses of definition, rule, procedure,
;;; simulation-statement, etc.) and system tables, is by convention given the
;;; slot type authors-with-time-of-last-edit? on those classes for which this
;;; feature is to be enabled.  The grammar for authors-with-time-of-last-edit?
;;; produces a parse-result given to the compiler for
;;; authors-with-time-of-last-edit?.  The grammar, compiler, and writer for
;;; Grammar, authors-with-time-of-last-edit?  are found in the module GRAMMAR6B
;;; under the heading "Writer, and Compiler for Authors
;;; (authors-with-time-of-last-edit?)".  For purposes of this discussion, I'll
;;; refer to the slot as the "authors attribute".
;;;
;;; Although the slot has a grammar and can be changed by the user entry of text
;;; according to that grammar, the slot is typically not changed by that means,
;;; but rather as a side effect of editing some slot on a frame that has the
;;; authors attribute.  The function update-authors-and-time-of-frame-edit below
;;; has the job of directly updating the value of the authors attribute in such
;;; a way as to produce a value that could have entered via the text entry, and
;;; can be printed by the corresponding printer.



;;; `Update-authors-and-time-of-frame-edit' ... The author is determined
;;; as follows:
;;; 
;;;    (1) if we're in a workstation context, then if there is a
;;;        user name (to the user, the user name for their G2 window
;;;        is not "none"), that's the author; otherwise, 
;;;
;;;    (2) if we can get the user name from the OS, that name is uppercased
;;;        and made into a symbol, which symbol is the author; otherwise,
;;;
;;;    (3) no author can be found.
;;;
;;; If no author can be found, frame-author-or-authors is not updated.
;;; Otherwise, frame-author-or-authors is updated so that the current author and
;;; timestamp appears at the front of the list.  The timestamp is the current
;;; universal time in the form of a `frame edit timestamp', which is a fixnum
;;; representing the number of minutes since `time-of-frame-edit-base-time',
;;; which is midnight, GMT, August 31, 1993.  Note that times of frame edits
;;; were not maintained until September, 1993.
;;;
;;; Note: time-of-frame-edit-base-time cannot easily be changed, since the
;;; interpretation of times saved in KBs depends on it being constant.
;;; Therefore, it is defined as a constant.  On all current G2 platforms, it
;;; supports valid times a little beyond the year 3,000, which should be
;;; adequate for most applications.



(defvar time-of-frame-edit-base-time
  (gensym-encode-unix-time 0 0 0 1 9 1993))

;;; The following is used in the system procedure
;;; `g2-text-time-stamp-to-unix-time'. - jpg 7/26/07
(defvar text-time-stamp-seconds 0.0)




;;; `time-of-last-allowable-frame-edit-time' is the unix time 24 hours
;;; earlier than the highest legal frame edit timestamp.

(defparameter time-of-last-allowable-frame-edit-time
  (-e (+e time-of-frame-edit-base-time
	  (*e (float most-positive-fixnum 1.0) 60.0))
      (float (* 24 60 60) 1.0)))
  


;;; `get-current-frame-edit-timestamp' returns a fixnum representing the current
;;; time as a frame edit timestamp.  This assumes it could only be called in
;;; a context in which the function get-universal-time returns a time later
;;; than September 1, 1993, midnight, GMT.  It also assumes that the current
;;; time is not "too many" years later: at least 31 years on platforms with
;;; 25-bit fixnums (TI Explorers) and 1021 years on platforms with 30 bit
;;; fixnums (Lucid, Chestnut targets, etc.).  The formula for deriving this
;;; is (floor (/ (/ most-positive-fixnum 60) 24) 365).

(defun get-current-frame-edit-timestamp ()
  (with-temporary-gensym-float-creation
      get-current-frame-edit-timestamp
    (floor (-e (gensym-get-unix-time)
	       time-of-frame-edit-base-time)
	   60)))

(defun twrite-frame-edit-timestamp (frame-edit-timestamp)
  (with-temporary-bignum-creation
    (multiple-value-bind (seconds minutes hours date month year)
	(gensym-decode-unix-time
	  (+ time-of-frame-edit-base-time
	     (* frame-edit-timestamp 60)))
      (declare (ignore seconds))
      (print-decoded-time nil minutes hours date month year))))

#+unused
(defun twrite-frame-edit-base-timestamp ()
  (twrite-frame-edit-timestamp frame-edit-base-timestamp))


;; Cf: `twrite-frame-edit-timestamp'
(defun evaluation-structure-for-frame-edit-timestamp (frame-edit-timestamp)
  (with-temporary-bignum-creation
    (multiple-value-bind (seconds minutes hours date month year)
	(gensym-decode-unix-time
	  (+ time-of-frame-edit-base-time
	     (* frame-edit-timestamp 60)))
      (declare (ignore seconds))
      (allocate-evaluation-structure-inline
	'year year
	'month month
	'date date
	'hours hours
	'minutes minutes))))


;;; `Get-current-user-name-if-any-case-insensitive' ... If it cannot get
;;; the user name from the OS, this returns nil.  If the user name is
;;; literally nil, this returns the symbol :nil.  Otherwise, this returns
;;; the symbol that results from upcasing the user name and interning
;;; it as a lisp symbol in the standard (AB) package.

(defun-simple get-current-user-name-if-any-case-insensitive ()
  (multiple-value-bind (name made-up?)
      (get-current-user-name)
    (if made-up?
	'unknown
	(or (intern-text-string
	      (copy-text-string-with-case-conversion
		(symbol-name-text-string name)
		:all))
	    :nil))))			; "how thoughtful!" -- Neal I. Lawson



;;; `Update-authors-and-time-of-frame-edit' is called from
;;; install-current-edit-state-compiled-result right before the change is made
;;; to the frame's slot.  This may record the author, date, and old value of the
;;; slot.
;;;
;;; For now, this updates both the authors attribute
;;; (authors-and-time-of-frame-edit slot) and the change-log-of-frame.  However,
;;; at present this does not handle add change log entries for changes to slots
;;; needing class name qualification.  (Ideally, the name would be changed to
;;; be more indicative of this, or at least more open-ended in its implied
;;; functionality.)
;;;
;;; Changes are blocked (by the flag do-not-update-frame-authors?) if
;;; we are calling this function in the context of a recompile that
;;; was initiated by the inspector. 

(defun update-authors-and-time-of-frame-edit
    (frame-being-edited slot-description)
  (unless do-not-update-frame-authors?
    (let* ((authors-slot-enabled-p	   
	     (type-of-slot-if-editable	; enabled selectively for classes
	       (class frame-being-edited)
	       'frame-author-or-authors))
	   (update-authors-p
	     (and (keep-edit-history? editor-parameters)
		  authors-slot-enabled-p
		  ;; This allows you to change this slot itself without it being logged.
		  ;; It was really a bug before that this wasn't done. (MHD 1/21/96)
		  (not (eq (pretty-slot-name slot-description)
			   'frame-author-or-authors)))))
      (when update-authors-p
	(let* ((author?
		 (or (if servicing-workstation?
			 (g2-user-name-for-this-workstation? current-workstation))
		     (get-current-user-name-if-any-case-insensitive)))
	       (last-edit-timestamp
		 (get-current-frame-edit-timestamp)))
	  (when update-authors-p
	    (update-authors-attribute
	      frame-being-edited slot-description author? last-edit-timestamp)))))))

;; added do-not-update-frame-authors? flag 2/27/97 ddm


(defun decode-frame-author-or-authors-1 (author-or-authors)
  (if (consp author-or-authors)
      (if (consp (car author-or-authors))
	  (values (caar author-or-authors)     ; author
		  (cdar author-or-authors)     ; timestamp
		  (cdr author-or-authors))     ; previous-author-or-authors
	  (if (listp (cdr author-or-authors))
	      (values (car author-or-authors)  ; author
		      nil                      ; timestamp
		      (cdr author-or-authors)) ; previous-author-or-authors
	      (values (car author-or-authors)  ; author
		      (cdr author-or-authors)  ; timestamp
		      nil)))                   ; previous-author-or-authors
      (values author-or-authors  ; author
	      nil                ; timestamp
	      nil)))             ; previous-author-or-authors

(defun decode-frame-author-or-authors (author-or-authors author-to-skip)
  (loop do
    (multiple-value-bind (author timestamp previous-author-or-authors)
	(decode-frame-author-or-authors-1 author-or-authors)
      (when (and timestamp (null author))
	(setq author 'unknown))
      (cond ((and (null author) (null timestamp) (null previous-author-or-authors))
	     (return-from decode-frame-author-or-authors
	       (values nil nil nil)))
	    ((or (null author)
		 (and author-to-skip
		      (if (consp author-to-skip)
			  (memq author author-to-skip)
			  (eq author author-to-skip))))
	     (setq author-or-authors previous-author-or-authors))
	    (t
	     (return-from decode-frame-author-or-authors
	       (values author timestamp previous-author-or-authors)))))))

(defun copy-frame-author-or-authors (author-or-authors author-to-skip)
  (multiple-value-bind (author timestamp previous-author-or-authors)
      (decode-frame-author-or-authors author-or-authors author-to-skip)
    (declare (ignore timestamp))
    (if (null author)
	nil
	(slot-value-cons
	  author
	  (copy-frame-author-or-authors
	    previous-author-or-authors author-to-skip)))))

(defun update-authors-attribute
    (frame-being-edited slot-description author? last-edit-timestamp)
  (declare (ignore slot-description))
  (let* ((new-entry
	   (slot-value-cons author? last-edit-timestamp))
	 (old-author-or-authors
	   (frame-author-or-authors frame-being-edited))
	 (new-value
	   (if (null (decode-frame-author-or-authors old-author-or-authors author?))
	       new-entry
	       (slot-value-cons
		 new-entry
		 (copy-frame-author-or-authors old-author-or-authors author?)))))
    (change-slot-value
      frame-being-edited 'frame-author-or-authors
      new-value)))

(defvar fixup-authors-to-skip nil)

;  This function may return NIL, to indicate that the value doesn't need to be fixed.
(defun-simple fixup-author-or-authors-value (author-or-authors)
  (when (and (consp author-or-authors)
	     (or (consp (cdr author-or-authors))
		 (null (car author-or-authors)))
	     (or (memq nil author-or-authors)
		 (loop for tail on author-or-authors
		       for a+t = (car tail)
		       for others = (cdr tail)
		       for a = (if (consp a+t) (car a+t) a+t)
		       when (and others (memq a others))
			 return t
		       finally (return nil))))
    (multiple-value-bind (author timestamp previous-author-or-authors)
	(decode-frame-author-or-authors author-or-authors nil)
      (if (and (null author) (null timestamp) (null previous-author-or-authors))
	  nil
	  (slot-value-cons
	    (if timestamp
		(slot-value-cons (or author 'unknown) timestamp)
		(or author 'unknown))
	    (let ((fixup-authors-to-skip (gensym-list author)))
	      (prog1 (fixup-frame-author-or-authors-tail previous-author-or-authors)
		(reclaim-gensym-list fixup-authors-to-skip))))))))

(defun fixup-frame-author-or-authors-tail (author-or-authors)
  (multiple-value-bind (author timestamp previous-author-or-authors)
      (decode-frame-author-or-authors author-or-authors fixup-authors-to-skip)
    (declare (ignore timestamp))
    (if (null author)
	nil
	(slot-value-cons
	  author
	  (when previous-author-or-authors
	    (gensym-push author fixup-authors-to-skip)
	    (fixup-frame-author-or-authors-tail
	      previous-author-or-authors))))))





;;;; Changing an Edit Box and Undoing and Redoing Edits



;;; `Undo-or-redo-edit-possible-p' determines if it is possible to undo the last edit (or,
;;; if redo-case? is specified, to redo the immediately preceding undone edit) in the
;;; current workstation context, which is assumed to be an editing context.

(defun undo-or-redo-edit-possible-p (redo-case?)
  (let ((edit-state
	 (if current-edit-state
	     current-edit-state
	     specific-structure-for-current-workstation-context)))
    (if redo-case?
	(edit-redo-stack edit-state)
	(edit-undo-stack edit-state))))



;;; `Undo-or-redo-edit' undoes the last edit (or, if redo-case? is specified, redoes the
;;; last undone edit) in the current editing context.  Automatic changes (and, if
;;; [system table parameter yet to be implemented] is true, kfep conversions) that
;;; followed an edit are also undone or redone as part of the undoing or redoing of that
;;; edit.

;;; Undo-or-redo-edit should be called only when undo-or-redo-edit-possible-p would
;;; return true.  (It does nothing if undo-or-redo-edit-possible-p would return false.)

(defun undo-or-redo-edit (redo-case?)
  (if (and (not redo-case?)
	   (>f (length-of-edit-undo-stack current-edit-state)
	       (maximum-number-of-undos-to-remember editor-parameters)))
      (prune-edit-undo-stack))
  (loop as l = (if redo-case?
		   (edit-redo-stack current-edit-state)
		   (edit-undo-stack current-edit-state))
	     then next-l
	as next-l = (cdr l)
	as edit-box-change = (car l)
	while l
	do (reclaim-gensym-cons l)
	   (cond
	     (redo-case?
	      (setf (edit-redo-stack current-edit-state) next-l))
	     (t (setf (edit-undo-stack current-edit-state) next-l)
		(decff (length-of-edit-undo-stack current-edit-state))))
	   (let ((special-type-of-edit-box-change?	; for this undo OR the next redo,
		   (special-type-of-edit-box-change?	;   if any
		     (if (and redo-case? next-l)
			 (car next-l)
			 edit-box-change))))
	     (unless
	       (or (eq special-type-of-edit-box-change? 'automatic)
		   (if nil			; system table parameter!
		       (eq special-type-of-edit-box-change? 'kfep-conversion)))
	       (setq next-l nil)))
	   (change-edit-box
	     nil
	     (line-index-where-difference-in-texts-starts edit-box-change)
	     (character-index-where-difference-in-texts-starts edit-box-change)
	     nil nil nil nil nil next-l	  ; no parsing or ellipsis deletion if not done
	     (special-type-of-edit-box-change? edit-box-change)
	     edit-box-change redo-case?)
	   (setf (old-text-segment edit-box-change) nil) ; so old text won't be reclaimed
	   (reclaim-edit-box-change edit-box-change)))

;; Consider restoring the state of kana-conversion-mode? on undos and redos.



;;; Prune-edit-undo-stack reduces (edit-undo-stack current-edit-state) to the most
;;; recent (maximum-number-of-undos-to-remember editor-parameters) edit box changes,
;;; assuming there are now more than that number.

(defun prune-edit-undo-stack ()
  (cond
    ((<=f (maximum-number-of-undos-to-remember editor-parameters) 0)	; necessary?
     #-SymScale
     (reclaim-edit-undo-or-redo-stack (edit-undo-stack current-edit-state))
     #-SymScale
     (setf (edit-undo-stack current-edit-state) nil)
     #+SymScale
     (reclaim-edit-undo-or-redo-stack
       (atomic-exchange (edit-undo-stack current-edit-state) nil)))
    (t (let ((new-last-cons
	       (nthcdr (-f (maximum-number-of-undos-to-remember editor-parameters) 1)
		       (edit-undo-stack current-edit-state))))
	 (reclaim-edit-undo-or-redo-stack (cdr new-last-cons))
	 (setf (cdr new-last-cons) nil))))
  (setf (length-of-edit-undo-stack current-edit-state)
	(maximum-number-of-undos-to-remember editor-parameters)))



;; | Date: Fri, 6 May 94 10:16:02 EDT
;; | From: mhd (Mark H David)
;; | 
;; | This one puts some interesting demands on the workstation service provider....
;; | I'm not sure if this is necessary.  Perhaps it's an optimization that's not
;; | all that helpful.  I think the idea is that if you type in really fast, it
;; | will skip some dictionary lookups that it forsees never being used....
;; | 
;; | This gives a warning for the moment when you compile EDIT.  I could disable
;; | it for a while.  Well, actually, I'm doing some work on Kanji today, so I'll
;; | see.
;; | 
;; | -mhd
;; 
;; Sad to say I think this is best turned off for now.  This is getting around
;; the current lexical analysis mechinism, and that's dangerous. Both this and
;; the multiple redraw optimizations are going to have to go on hold for a
;; bit. - ben
;; 
;; -- so, that's the story.  It's for now considered obsolete, and
;; disabled.... Check the performance before the beta release ships (and
;; revise or eliminate the temporary-progn/message! (MHD 5/6/94)
;;
;; Tried out today.  I don't find it unreasonably slow.  I think it's fine,
;; unless some user really notices as complains.  I doubt they will.  (MHD
;; 7/6/94)


;;; `Pending-romaji-character-in-text-p' checks the workstation event queue, if
;;; possible, for a pending keystroke event which is an alphabetic roman
;;; character.  (Note: as of 5/6/94, this kind of checking is not possible; with
;;; time, the functionality to support it may be restored; it's not absolutely
;;; needed, especially as computers get faster. -- MHD)

(defun pending-romaji-character-in-text-p ()
;  (progn
;    (poll-workstation)
;    (let ((pending-workstation-event?
;            (car (workstation-event-queue current-workstation))))
;      (when pending-workstation-event?
;        (let ((key-code (workstation-event-code pending-workstation-event?)))
;          ;; Is this the desired test?  A-Z and a-z?
;          (letter-key-code-p key-code)))))
  nil)






;;; `Change-edit-box' is the only function that is allowed to change the text or
;;; cursor in an edit box.

;;; Text-tail?, if specified, must correspond to line-index-of-change?.  If not
;;; specified, it is computed from line-index-of-change?.  i.e. The line
;;; specified by line-index-of-change? relative to the beginning of the text, is
;;; the same as the first line of the text-tail.

;;; If neither line-index-past-deletion? or text-line-to-insert? are specified, then
;;; this is a cursor-movement operation.  In this case ONLY, text-tail?, line-index-of-
;;; change?, and character-index-of-change? may be nil with x-in-workspace? and
;;; y-in-workspace? implicitly specifying the new cursor position.  Also, in this case
;;; only, if the edit cursor is not "on", the location of the edit cursor and the
;;; values of the cursor line and character index slots of the edit state are irrelevant.

;;; The text position past the deletion, if specified, must be past the position of
;;; change.  text-line-to-insert?, if specified, is not reclaimed, and may be just
;;; an ordinary string, not necessarily a text string.

;;; Special-type-of-edit-box-change? may be nil, AUTOMATIC, KFEP-CONVERSION,
;;; TYPED-IN-SPACE-OR-\@, or PATHNAME-COMPONENT-CONVERSION.

;;; Except for the kfep conversion text region, text regions are deleted from an edit
;;; box that is to be changed, because it would be difficult to update them correctly.

;;; This assumes, as do functions subordinate to it, that complex characters are never
;;; broken across string boundaries.

;;; Kfep-conversion-text-region-expansion-limit is the maximum number of simple
;;; characters by which a kfep conversion text region could conceivably expand
;;; (not including additional ones added ...).  This is just for optimization
;;; purposes.

(defparameter kfep-conversion-text-region-expansion-limit 1024)  ; was 10.  -pto 17jul90

(defparameter default-kanji-conversion-text-region-highlight-color 'light-gray)
					; was "nil" (i.e., black) (MHD 1/26/00)

(defun change-edit-box
    (text-tail? line-index-of-change? character-index-of-change?
		&optional line-index-past-deletion? character-index-past-deletion?
		text-line-to-insert?	; never reclaimed
		x-in-workspace? y-in-workspace?
		no-parsing-or-ellipsis-deletion? special-type-of-edit-box-change?
		edit-box-change? redo-case? change-text?)

  (when (eq special-type-of-edit-box-change? 'pathname-component-conversion)
    (if (do-pathname-component-conversion-if-necessary
	    text-tail?
	  text-line-to-insert?)
	(return-from change-edit-box nil)
	(setq special-type-of-edit-box-change? nil)))

  ;; If text-tail? is null, and line-index-of-change? is supplied, then
  ;; set text-tail? to the tail corresponding to line-index-of-change?:
  (when (and (null text-tail?)
	     line-index-of-change?)
    (setq text-tail?				; changes arg
	  (find-text-tail-for-line
	    (text-being-edited current-edit-state) line-index-of-change?)))

  (let* ((just-moving-cursor?			; true if there's no deletion,
	   (not (or line-index-past-deletion?	;   insertion, or undo or redo
		    text-line-to-insert?
		    edit-box-change?)))

	 (edit-box (edit-box current-edit-state))
	 (edit-box-format (text-box-format edit-box))
	 (text-being-edited (text-being-edited current-edit-state))
	 (old-width-for-text
	   (-w (width-of-block edit-box)
	       (+w (text-box-left-border-width edit-box-format)
		   (text-cell-left-margin edit-box-format)
		   (text-cell-right-margin edit-box-format)
		   (text-box-right-border-width edit-box-format))))

	 (new-cursor-line-index? nil)	; nil => no need to move
	 new-cursor-character-index?
	 new-text-tail-for-cursor?
	 new-cursor-x-in-workspace
	 new-cursor-y-in-workspace		; on a text line baseline

	 (new-width-for-text 0)			; includes cursor position

	 new-text-segment
	 old-text-segment
	 (text-tail-past-old-text-segment? nil)
	 line-index-of-old-and-new-text-segment
	 line-index-past-new-text-segment
	 line-index-past-old-text-segment

         line-index-in-old-and-new-text
	 text-tail-in-old-text
	 text-tail-in-new-text
	 next-text-tail-in-old-text?
	 next-text-tail-in-new-text?
	 old-text-line
	 length-of-old-text-line

	 character-index-where-difference-starts?
	 distance-from-left-to-where-difference-starts?

	 (new-text-has-same-height-as-old? t)
	 text-tail-past-text-segment?

	 scroll-edit-box?

	 (line-index-for-beginning-of-kfep-conversion-text-region? nil)
	 character-index-for-beginning-of-kfep-conversion-text-region?
	 (line-index-for-end-of-kfep-conversion-text-region? nil)
	 character-index-for-end-of-kfep-conversion-text-region?

	 (try-to-expand-kfep-conversion-text-region? nil)
	 (restore-kana-conversion-mode? nil)
	 
	 )

    ;; Find the new cursor position, if just moving it.
    (when just-moving-cursor?
      (multiple-value-setq (new-cursor-line-index?
			     new-cursor-character-index?
			     new-text-tail-for-cursor?
			     new-cursor-x-in-workspace
			     new-cursor-y-in-workspace)
	(find-position-in-text			; assumed to never return nil
	  (edit-box current-edit-state) nil nil nil t x-in-workspace? y-in-workspace?
	  line-index-of-change? character-index-of-change? text-tail?))
      (setq line-index-of-change? new-cursor-line-index?)  ; for non-nil x-in-workspace?
      (setq character-index-of-change? new-cursor-character-index?))

    ;; Make the parsing position (the top element of
    ;; stack-of-positions-after-tokens) not be past the position of change, or,
    ;; if just moving the cursor, the new cursor position.
    (loop
      as first-time? = t then nil
      as (line-index-for-end-of-token
	   character-index-after-token
	   . token-self-terminating?)
	 = (car (stack-of-positions-after-tokens current-edit-state))
      while (or (<f line-index-of-change? line-index-for-end-of-token)
		(and (=f line-index-of-change? line-index-for-end-of-token)
		     (if token-self-terminating?
			 (<f character-index-of-change? character-index-after-token)
			 (<=f character-index-of-change?
			      character-index-after-token))))
      do (when first-time?
	   (erase-any-temporary-information-on-edit-workspace nil)
	   (setf (parsing-extension-mode? current-edit-state) ; not absolutely nec.
		 nil))
	 (pop-for-token)
      finally
	(unless first-time?		; not really nec.
	  (setf (text-tail-for-parsing current-edit-state)
		(if nil			; later (=f line-index-for-end-of-token
					;   (cursor-line-index current-edit-state))!?
		    (text-tail-for-cursor current-edit-state)
		    (find-text-tail-for-line
		      text-being-edited line-index-for-end-of-token)))))

    ;; This section of logic applies only when there is a kfep conversion text region.
    ;; If the position of change is before the kfep conversion text region, reinitialize
    ;; the conversion mode, unless special-type-of-edit-box-change? is AUTOMATIC (as it
    ;; will be in the case of an ellipsis insertion).  If the position of change is
    ;; within the kfep conversion text region, shrink the region accordingly unless
    ;; special-type-of-edit-box-change? is KFEP-CONVERSION or AUTOMATIC.  If the cursor
    ;; is just moving to the right on the same line as the end of the text region no
    ;; more than kfep-conversion-text-region-expansion-limit simple characters beyond
    ;; its end, try to expand the text region.  [Note by LH.  Review all KFEP logic in
    ;; this function!]
    (when (kfep-conversion-text-region? current-edit-state)
      (let ((text-region (kfep-conversion-text-region? current-edit-state)))
	(cond
	  ((or (<f line-index-of-change?
		   (line-index-for-fixed-end-of-text-region text-region))
	       (and (=f line-index-of-change?
			(line-index-for-fixed-end-of-text-region text-region))
		    (<f character-index-of-change?
			(character-index-for-fixed-end-of-text-region text-region))))
	   (unless (eq special-type-of-edit-box-change? 'automatic)
	     ;; Revise the following later so that undo will work better!
	     ;; Also, save the conversion mode in a local variable!
	     (delete-kfep-conversion-text-region-if-any)	; 13 Aug 90 -- LH
	     (setq restore-kana-conversion-mode? t)))
	  ((or (<f line-index-of-change?
		   (line-index-for-free-end-of-text-region text-region))
	       (and (=f line-index-of-change?
			(line-index-for-free-end-of-text-region text-region))
		    (<f character-index-of-change?
			(character-index-for-free-end-of-text-region text-region))))
	   (unless (or (eq special-type-of-edit-box-change? 'kfep-conversion)
		       (eq special-type-of-edit-box-change? 'automatic))
	     (update-kfep-conversion-choices-as-appropriate
	       nil line-index-of-change? character-index-of-change?)))
	  ((and just-moving-cursor?		; added  12 aug 90  LH
		(=f new-cursor-line-index?
		    (cursor-line-index current-edit-state)
		    (line-index-for-free-end-of-text-region text-region))
		(>f new-cursor-character-index?
		    (cursor-character-index current-edit-state))
		(<=f new-cursor-character-index?
		     (+f (character-index-for-free-end-of-text-region text-region)
			 kfep-conversion-text-region-expansion-limit)))
	   (setq try-to-expand-kfep-conversion-text-region? t)))))

    (unless just-moving-cursor?

      ;; Delete all text regions except for the kfep conversion text region.
      (delete-any-text-regions			; optimize?
	edit-box nil nil nil nil (kfep-conversion-text-region? current-edit-state))

      ;; Determine the minimum necessary text segment replacement that includes the
      ;; change and leaves the text appropriately reformatted.
      (cond
	(edit-box-change?
	 (setq line-index-of-old-and-new-text-segment
	       (line-index-of-old-and-new-text-segment edit-box-change?))
	 (setq line-index-past-new-text-segment
	       (line-index-past-old-text-segment edit-box-change?))
	 (setq line-index-past-old-text-segment
	       (line-index-past-new-text-segment edit-box-change?))
	 (setq new-text-segment (old-text-segment edit-box-change?))
	 (setq new-width-for-text (old-width-for-text edit-box-change?))
	 (setq old-text-segment
	       (find-text-tail-for-line
		 text-being-edited line-index-of-old-and-new-text-segment))
	 (setq text-tail-past-old-text-segment?
	       (find-text-tail-for-line
		 text-being-edited line-index-past-old-text-segment)))
	(t
	 (multiple-value-setq (new-text-segment
				new-width-for-text
				old-text-segment text-tail-past-old-text-segment?
				line-index-of-old-and-new-text-segment
				line-index-past-new-text-segment
				line-index-past-old-text-segment)
	   (reformat-text
	     text-being-edited edit-box-format
	     nil
	     t text-tail?
	     line-index-of-change? character-index-of-change?
	     line-index-past-deletion? character-index-past-deletion?
	     text-line-to-insert?
	     (minimum-width-of-text-box (edit-box current-edit-state))
	     (text-cell-plist-for-text-box edit-box)))))
      (setq text-tail-in-old-text old-text-segment)
      (setq text-tail-in-new-text new-text-segment)
      (setq line-index-in-old-and-new-text line-index-of-old-and-new-text-segment)
      (setq character-index-where-difference-starts?
	    (loop with new-text-line
		  with length-of-new-text-line
		  with lost-space-at-end-of-old-text-line
		  with lost-space-at-end-of-new-text-line
		  do (multiple-value-setq-some
			 (old-text-line nil
					lost-space-at-end-of-old-text-line
					next-text-tail-in-old-text?)
			 (get-next-text-line text-tail-in-old-text))
		     (multiple-value-setq-some
			 (new-text-line nil
					lost-space-at-end-of-new-text-line
					next-text-tail-in-new-text?)
			 (get-next-text-line text-tail-in-new-text))
		     (setq length-of-old-text-line (text-line-length old-text-line))
		     (setq length-of-new-text-line (text-line-length new-text-line))
		     (cond
		       ((=f line-index-in-old-and-new-text line-index-of-change?)
			(return
			  (cond		; NEEDS REDESIGN OR DOCUMENTATION!
			    ((and (null next-text-tail-in-new-text?)
				  (null next-text-tail-in-old-text?))
			     (minf character-index-of-change?
				   length-of-old-text-line
				   length-of-new-text-line))
			    ((<f character-index-of-change? length-of-old-text-line)
			     (minf character-index-of-change? length-of-new-text-line))
			    ((<f character-index-of-change? length-of-new-text-line)
			     length-of-old-text-line)
			    (t nil))  ; character-index-of-change? >= old & new length
			  ))
		       ((not (=f length-of-new-text-line length-of-old-text-line))
			(return (minf length-of-new-text-line length-of-old-text-line)))
		       ((and (>f length-of-old-text-line 0)  ; only for added-hyphen cases
			     (not (char=w
				    (charw old-text-line (-f length-of-old-text-line 1))
				    (charw new-text-line (-f length-of-new-text-line 1)))))
			(return  ; sample case: "mas-" "ter ..." changing to "mast" "..."
			  (-f length-of-old-text-line 1)))
		       ((not (equalw lost-space-at-end-of-new-text-line
				     lost-space-at-end-of-old-text-line))
			(return length-of-old-text-line))
		       ((or (eq next-text-tail-in-old-text? text-tail-past-old-text-segment?)
			    (null next-text-tail-in-new-text?))
			(return nil)))
		     (setq text-tail-in-old-text next-text-tail-in-old-text?)
		     (setq text-tail-in-new-text next-text-tail-in-new-text?)
		     (incff line-index-in-old-and-new-text)))
      (if character-index-where-difference-starts?
	  (setq distance-from-left-to-where-difference-starts?
		(loop with indentation = 0	; do more elegantly, later!
		      with word-spacing = (default-word-spacing edit-box-format)
		      as text-element in text-tail-in-old-text
		      until (text-line-p text-element)
		      do (cond
			   ((numberp text-element)
			    (setq indentation text-element))
			   ((symbolp text-element))
			   ((eq (car text-element) 'word-spacing)
			    (setq word-spacing (cdr text-element))))
		      finally
			(return
			  (+w (text-box-left-border-width edit-box-format)
			      (text-cell-left-margin edit-box-format)
			      (if (=f character-index-where-difference-starts? 0)
				  0		; indentation may differ in this case
				  indentation)
			      (compute-minimum-left-edge-of-character-in-line-of-text
				old-text-line character-index-where-difference-starts?
				(text-cell-font-map edit-box-format)
				word-spacing))))))
      (setq new-text-has-same-height-as-old?
	    (=f line-index-past-new-text-segment
		line-index-past-old-text-segment))	; use distances in text, later!
      (setq text-tail-past-text-segment?
	    (if new-text-has-same-height-as-old?
		text-tail-past-old-text-segment?))
      (cond
	(text-tail-past-old-text-segment?
	 (nconc text-tail-in-new-text text-tail-past-old-text-segment?)
	 (if (null next-text-tail-in-new-text?)
	     (setq next-text-tail-in-new-text? text-tail-past-old-text-segment?))))

      ;; Determine the new position for the edit cursor, if necessary.  Also,
      ;; find the position for and erase all or part of the kfep conversion text
      ;; region, or exit kfep mode, as appropriate.
      (cond
	(edit-box-change?
	 (setq new-cursor-line-index?		; always redo edit cursor
	       (old-cursor-line-index edit-box-change?))
	 (setq new-cursor-character-index?
	       (old-cursor-character-index edit-box-change?))
	 (cond
	   ((old-position-for-kfep-conversion-text-region? edit-box-change?)
	    (let ((kfep-conversion-text-region?
		    (kfep-conversion-text-region? current-edit-state))
		  (old-beginning-line-index
		    (car (old-position-for-kfep-conversion-text-region?
			   edit-box-change?)))
		  (old-beginning-character-index
		    (cdr (old-position-for-kfep-conversion-text-region?
			   edit-box-change?))))
	      (cond
		((not (or (eq special-type-of-edit-box-change? 'kfep-conversion)
			  (and kfep-conversion-text-region?
			       (=f (line-index-for-fixed-end-of-text-region
				     kfep-conversion-text-region?)
				   old-beginning-line-index)
			       (=f (character-index-for-fixed-end-of-text-region
				     kfep-conversion-text-region?)
				   old-beginning-character-index)
			       (or (<f (line-index-for-free-end-of-text-region
					 kfep-conversion-text-region?)
				       line-index-in-old-and-new-text)
				   (and (=f (line-index-for-free-end-of-text-region
					      kfep-conversion-text-region?)
					    line-index-in-old-and-new-text)
					;; should the following test for >
					;; kfep-conversion-text-region-expansion-limit
					;; characters separation, for compatibility?
					(<f (character-index-for-free-end-of-text-region
					      kfep-conversion-text-region?)
					    character-index-where-difference-starts?))))))
		 (setq line-index-for-beginning-of-kfep-conversion-text-region?
		       old-beginning-line-index)
		 (setq character-index-for-beginning-of-kfep-conversion-text-region?
		       old-beginning-character-index)))))
	   ((kfep-conversion-text-region? current-edit-state)	; exit kfep mode
	    (exit-kfep-mode-if-necessary))))
	(t (multiple-value-setq
	       (new-cursor-line-index? new-cursor-character-index?
				       new-text-tail-for-cursor?)
	     (determine-corrected-text-position-if-necessary
	       (cursor-line-index current-edit-state)
	       (cursor-character-index current-edit-state)
	       new-text-segment old-text-segment
	       line-index-of-old-and-new-text-segment
	       line-index-in-old-and-new-text
	       character-index-where-difference-starts?
	       t
	       line-index-of-change? character-index-of-change?
	       line-index-past-deletion? character-index-past-deletion?
	       text-line-to-insert?))
	   (if (kfep-conversion-text-region? current-edit-state)
	       (let ((text-region (kfep-conversion-text-region? current-edit-state)))
		 ;; Try to expand kfep conversion text region if this is a normal
		 ;; type of change starting on the same line as the end of the text
		 ;; region no more than kfep-conversion-text-region-expansion-limit
		 ;; kfep-conversion-text-region-expansion-limit simple characters
		 ;; beyond its end.
		 (if (and (null	    ; not KFEP-CONVERSION or AUTOMATIC?
			    special-type-of-edit-box-change?)
			  (=f		    ; difference starts on same line as text region
			    line-index-in-old-and-new-text
			    (line-index-for-free-end-of-text-region text-region))

			  ;; 14 SEP 90  LH
			  (or (null character-index-where-difference-starts?)	; ok if nil
			      (<=f
				character-index-where-difference-starts?
				(+f (character-index-for-free-end-of-text-region
				      text-region)
				    kfep-conversion-text-region-expansion-limit))) ; was 10

			  new-cursor-line-index?  ; cursor needs to move; non-nil => non-nil
					;   new-cursor-character-index?, too
			  (not			   ; but not to where difference starts
			    (and (=f new-cursor-line-index?
				     line-index-in-old-and-new-text)
				 (and
				   ;; previously did not checked if nil, which was a bug:
				   character-index-where-difference-starts?
				   (=f new-cursor-character-index?
				       character-index-where-difference-starts?)))))
		     (when (not (pending-romaji-character-in-text-p))	; PTO and LH -- 21Nov90
		       ;; Need to verify correctness for all cases of this test.
		       (setq try-to-expand-kfep-conversion-text-region? t)))
		 (when (multiple-value-setq
			   (line-index-for-end-of-kfep-conversion-text-region?
			     character-index-for-end-of-kfep-conversion-text-region?)
			 (determine-corrected-text-position-if-necessary
			   (line-index-for-free-end-of-text-region text-region)
			   (character-index-for-free-end-of-text-region text-region)
			   new-text-segment old-text-segment
			   line-index-of-old-and-new-text-segment
			   line-index-in-old-and-new-text
			   character-index-where-difference-starts?
			   nil
			   line-index-of-change? character-index-of-change?
			   line-index-past-deletion? character-index-past-deletion?
			   text-line-to-insert?))
		   (multiple-value-setq
		       (line-index-for-beginning-of-kfep-conversion-text-region?
			 character-index-for-beginning-of-kfep-conversion-text-region?)
		     (determine-corrected-text-position-if-necessary
		       (line-index-for-fixed-end-of-text-region text-region)
		       (character-index-for-fixed-end-of-text-region text-region)
		       new-text-segment old-text-segment
		       line-index-of-old-and-new-text-segment
		       line-index-in-old-and-new-text
		       character-index-where-difference-starts?
		       (eq special-type-of-edit-box-change?
			   'automatic)	; AUTOMATIC => ellipsis insertion
		       line-index-of-change? character-index-of-change?
		       line-index-past-deletion? character-index-past-deletion?
		       text-line-to-insert?))
		   ;; (If the end of the kfep conversion text region is needed
		   ;; for the edit box change, save it here in local variables.)
		   ;; Erase the kfep conversion text region, but if the beginning
		   ;; doesn't have to move, only erase back to where the text
		   ;; difference starts (necessarily, in this case, within the
		   ;; text region).
		   (update-text-region
		     (kfep-conversion-text-region? current-edit-state)
		     (if line-index-for-beginning-of-kfep-conversion-text-region?
			 (line-index-for-fixed-end-of-text-region text-region)
			 line-index-in-old-and-new-text)
		     (if line-index-for-beginning-of-kfep-conversion-text-region?
			 (character-index-for-fixed-end-of-text-region text-region)
			 character-index-where-difference-starts?)))))))

      ;; Fix the after-token positions.
      (when (or (<f line-index-of-old-and-new-text-segment line-index-of-change?)
		t)    ; length of first line of segment < character-index-of-change?!???
	(loop with new-line-index?
	      with new-character-index?
	      as text-position in (stack-of-positions-after-tokens current-edit-state)
	      while (multiple-value-setq (new-line-index? new-character-index?)
		      (determine-corrected-text-position-if-necessary
			(car text-position) (cadr text-position)
			new-text-segment old-text-segment
			line-index-of-old-and-new-text-segment
			line-index-in-old-and-new-text
			character-index-where-difference-starts?
;			   nil line-index-of-change? character-index-of-change?
;			   line-index-past-deletion? character-index-past-deletion?
;			   text-line-to-insert?
			))
	      do (setf (car text-position) new-line-index?)
		 (setf (cadr text-position) new-character-index?)
	      ;; until no change in position (assuming not diff. hyphenated
	      ;; over 2+ lines)!
	      )))
    
    ;; Turn off (erase) the edit cursor, if necessary.
    (when new-cursor-line-index?
      (stop-blinker (edit-cursor current-edit-state) nil))	; later optimize this?

    ;; If the cursor is moving to a different line that is not fully visible in
    ;; the edit box, make scroll-edit-box? true and erase all text in the edit box
    (if new-cursor-line-index?
	(let* ((text-cell-plist (text-cell-plist-for-text-box edit-box))
	       (line-index-of-first-fully-visible-line?
		 (if (getf text-cell-plist 'y-offset-for-text)
		     (getf text-cell-plist 'line-index-of-first-fully-visible-line))))
	  (cond
	    ((if line-index-of-first-fully-visible-line?
		 (or (<f new-cursor-line-index?
			 line-index-of-first-fully-visible-line?)
		     (>=f new-cursor-line-index?
			  (+f line-index-of-first-fully-visible-line?
			      (getf text-cell-plist
				    'number-of-fully-visible-lines)))))
	     (setq scroll-edit-box? t)
	     (let ((line-index			; just use text-being-edited?
		     (maxf (-f line-index-of-first-fully-visible-line? 1) 1)))
	       (update-text-in-edit-box
		 t
		 (find-text-tail-for-line text-being-edited line-index)
		 nil nil line-index nil edit-box))))))

    (pretend-to-use-value scroll-edit-box?)	; to be used later -- gag compiler!

    ;; Erase a portion of the text segment, as necessary.
    (unless just-moving-cursor?
      (update-text-in-edit-box
	t
	text-tail-in-old-text next-text-tail-in-old-text? text-tail-past-text-segment?
	line-index-in-old-and-new-text distance-from-left-to-where-difference-starts?
	edit-box))

    ;; Swap in the new reformatted segment of text, find the new cursor position, and
    ;; reclaim unused text.
    (cond
      ((not just-moving-cursor?)
       (if text-tail-past-old-text-segment?  ; remove common tail from old text segment
	   (loop for l on text-tail-in-old-text
		 until (eq (cdr l) text-tail-past-old-text-segment?)
		 finally (setf (cdr l) nil)))
       (setf (car text-tail-in-old-text)	; swap cars of old and new text segments
	     (prog1 (car text-tail-in-new-text)
	       (setf (car text-tail-in-new-text) (car text-tail-in-old-text))))
       (setf (cdr text-tail-in-old-text)
	     (prog1 (cdr text-tail-in-new-text)
	       (setf (cdr text-tail-in-new-text) (cdr text-tail-in-old-text))))
       (setq text-tail-in-old-text		; only for clarity
	     (prog1 text-tail-in-new-text
	       (setq text-tail-in-new-text text-tail-in-old-text)))
       (cond
	 (edit-box-change?
	  (setq new-text-tail-for-cursor?
		(find-text-tail-for-line text-being-edited new-cursor-line-index?)))
	 ((eq new-text-tail-for-cursor? text-tail-in-old-text)	; because of car swap
	  (setq new-text-tail-for-cursor? text-tail-in-new-text)))
       (if new-cursor-line-index?
	   (multiple-value-setq (new-cursor-line-index? new-cursor-character-index?
							new-text-tail-for-cursor?	; no changes in first 3
							new-cursor-x-in-workspace
							new-cursor-y-in-workspace)
	     (find-position-in-text
	       (edit-box current-edit-state) nil nil nil nil nil nil
	       new-cursor-line-index? new-cursor-character-index?
	       new-text-tail-for-cursor?)))
       (let ((edit-box-change
	       (make-edit-box-change
		 special-type-of-edit-box-change?
		 line-index-of-old-and-new-text-segment
		 line-index-in-old-and-new-text
		 (or character-index-where-difference-starts? length-of-old-text-line)
		 line-index-past-old-text-segment line-index-past-new-text-segment
		 new-text-segment old-width-for-text	; new-text-segment is really old
		 (cursor-line-index current-edit-state)
		 (cursor-character-index current-edit-state)
		 (if (kfep-conversion-text-region? current-edit-state)
		     (gensym-cons
		       (line-index-for-fixed-end-of-text-region
			 (kfep-conversion-text-region? current-edit-state))
		       (character-index-for-fixed-end-of-text-region
			 (kfep-conversion-text-region? current-edit-state)))))))
	 (cond			 ; replaced (reclaim-text new-text-segment)
	   ((or (null edit-box-change?) redo-case?)
	    (if (null edit-box-change?)
		(cond				; clear edit redo stack
		  ((edit-redo-stack current-edit-state)
		   (reclaim-edit-undo-or-redo-stack (edit-redo-stack current-edit-state))
		   (setf (edit-redo-stack current-edit-state) nil))))
	    (setf (edit-undo-stack current-edit-state)	; combine with previous one in
		  (gensym-cons			        ;   some non-redo cases?
		    edit-box-change (edit-undo-stack current-edit-state)))
	    (incff (length-of-edit-undo-stack current-edit-state))
	    (if (>f (length-of-edit-undo-stack current-edit-state)
		    (+f (maximum-number-of-undos-to-remember editor-parameters)
			10))			; 20?
		(prune-edit-undo-stack)))
	   (t (setf (edit-redo-stack current-edit-state)
		    (gensym-cons
		      edit-box-change (edit-redo-stack current-edit-state))))))))

    ;; Reflect new cursor position in new width for text.
    (when new-cursor-line-index?	 ; unnec. when edit-box-change? non-nil
      (setq new-width-for-text
	    (maxw new-width-for-text
		  (-w new-cursor-x-in-workspace
		      (left-edge-of-block edit-box)
		      (text-box-left-border-width edit-box-format)
		      (text-cell-left-margin edit-box-format)))))

    ;; Reflect unreformatted lines in new width for text, if necessary (now always!).
    (when (and (not (eq old-text-segment text-being-edited))
	       (null edit-box-change?))
      (loop with text-tail = text-being-edited
	    with line-width
	    do (multiple-value-setq-some
		   (nil nil
			nil text-tail
			nil line-width)
		   (get-next-text-line text-tail))
	       (if (>w line-width new-width-for-text)
		   (setq new-width-for-text line-width))
	    until (eq text-tail old-text-segment)))
    (when (and text-tail-past-old-text-segment? (null edit-box-change?))
      (loop with text-tail? = text-tail-past-old-text-segment?
	    with nil
	    with line-width
	    do (multiple-value-setq-some
		   (nil nil
			nil text-tail?
			nil line-width)
		   (get-next-text-line text-tail?))
	       (if (>w line-width new-width-for-text)
		   (setq new-width-for-text line-width))
	    until (null text-tail?)))

    ;; Redraw the edit box border, if necessary.  Also, if its bottom edge moves up or
    ;; down, erase any temporary information on the edit workspace (that is, anything
    ;; that could be below the edit box); this information will be redrawn again, if
    ;; necessary, by extend-parsing-as-appropriate.
    (unless (scrolling-editor-p current-edit-state)
      (let* ((new-right-edge?
	       (if (not (=w new-width-for-text old-width-for-text))
		   (maxw (+w (left-edge-of-block edit-box)
			     (minimum-width-of-text-box edit-box))
			 (+w (right-edge-of-block edit-box)	; compute afresh?
			     (-w new-width-for-text old-width-for-text)))))

	     ;; These bindings might help with a old C compiler bug. - (MHD 11/20/91)
	     (top-edge-of-block (top-edge-of-block edit-box))
	     (minimum-height-of-text-box (minimum-height-of-text-box edit-box))
	     (text-box-top-border-width
	       (text-box-top-border-width edit-box-format))
	     (text (cdr (box-translation-and-text edit-box)))
	     (text-cell-plist-for-text-box
	       (text-cell-plist-for-text-box edit-box))
	     (height-for-text
	       (compute-height-for-text	; result includes margins
		 text
		 edit-box-format text-cell-plist-for-text-box))
	     (text-box-bottom-border-width
	       (text-box-bottom-border-width edit-box-format))
	     (new-bottom-edge?
	       (if (not new-text-has-same-height-as-old?)
		   (maxw (+w top-edge-of-block
			     minimum-height-of-text-box)
			 (+w top-edge-of-block	; compute by difference in height!
			     text-box-top-border-width
			     height-for-text
			     text-box-bottom-border-width)))))
	(when (or (and new-right-edge?
		       (/=w new-right-edge? (right-edge-of-block edit-box)))
		  (and new-bottom-edge?
		       (/=w new-bottom-edge? (bottom-edge-of-block edit-box))))
	  (let ((move-kfep-conversion-choices?
		  (and new-bottom-edge?
		       (kfep-conversion-text-region? current-edit-state)	; nec?
		       (kfep-conversion-choices? current-edit-state))))
	    (when move-kfep-conversion-choices?
	      (erase-any-kfep-conversion-choices))
	    (when new-bottom-edge?
	      (erase-any-temporary-information-on-edit-workspace nil))
	    (update-border-of-text-box edit-box nil nil new-right-edge? new-bottom-edge?)
	    (when move-kfep-conversion-choices?
	      (put-up-kfep-conversion-choices t))
	    (when (and new-bottom-edge?
		       (or (do-not-have-edit-menus? current-edit-state)
			   (specific-image-plane-on-which-to-edit-in-place?
			     current-edit-state)))
	      (shrink-wrap-workspace current-edit-workspace))))))

    ;; Draw (or redraw) a portion of the text segment, as necessary.
    (unless just-moving-cursor?
      (update-text-in-edit-box
	nil
	text-tail-in-new-text next-text-tail-in-new-text? text-tail-past-text-segment?
	line-index-in-old-and-new-text distance-from-left-to-where-difference-starts?
	edit-box))
    
    ;; Move the edit cursor, if necessary.
    (when new-cursor-line-index?
      (move-edit-cursor
	(edit-cursor current-edit-state)
	new-cursor-x-in-workspace new-cursor-y-in-workspace)
      (setf (cursor-line-index current-edit-state) new-cursor-line-index?)
      (setf (cursor-character-index current-edit-state) new-cursor-character-index?)
      (setf (text-tail-for-cursor current-edit-state) new-text-tail-for-cursor?))

    (when (scrolling-editor-p current-edit-state)
      ;; Do we ever appear in more than one image-plane?
      (loop for (nil  . frame-transform) in (frame-transforms-of-block edit-box)
	    do (scroll-text-into-view
		 frame-transform
		 (cursor-line-index current-edit-state)
		 (cursor-character-index current-edit-state))))
    
    ;; Fix the kfep conversion text region, if necessary.
    (cond
      (restore-kana-conversion-mode?
       (enter-kana-conversion-mode
	 (kana-conversion-mode? current-edit-state)))
;      ((kfep-conversion-text-region? current-edit-state)
;	nil)					; FIX EDGES!!!???
      )
    (if (or line-index-for-beginning-of-kfep-conversion-text-region?  ; 15 sep 90  LH
	    line-index-for-end-of-kfep-conversion-text-region?)
	(if (null line-index-for-end-of-kfep-conversion-text-region?)
	    ;; The edit-box-change? case.
	    (set-up-kfep-conversion-text-region
	      line-index-for-beginning-of-kfep-conversion-text-region?
	      character-index-for-beginning-of-kfep-conversion-text-region?
	      t)
	    ;; The reformatting-moves-beginning-of-kfep-conversion-text-region case.
	    ;; The kfep conversion text region is empty here.
	    (progn
	      (when line-index-for-beginning-of-kfep-conversion-text-region?
		(delete-frame (kfep-conversion-text-region? current-edit-state))
		(setf (kfep-conversion-text-region? current-edit-state)
		      (make-kfep-conversion-text-region
			line-index-for-beginning-of-kfep-conversion-text-region?
			character-index-for-beginning-of-kfep-conversion-text-region?
;			(kanji-conversion-text-region-highlight-color editor-parameters)
			default-kanji-conversion-text-region-highlight-color))
;		(update-text-region   ; old code
;		  (kfep-conversion-text-region? current-edit-state)
;		  line-index-for-beginning-of-kfep-conversion-text-region?
;		  character-index-for-beginning-of-kfep-conversion-text-region?
;		  t)
		)
	      (update-text-region
		(kfep-conversion-text-region? current-edit-state)
		line-index-for-end-of-kfep-conversion-text-region?
		character-index-for-end-of-kfep-conversion-text-region?))))
    (cond
      (try-to-expand-kfep-conversion-text-region?
       (update-kfep-conversion-choices-as-appropriate t))
      ((kfep-conversion-text-region? current-edit-state)	; added  13 sep 90  LH
       (update-kfep-buttons)))

    ;; Fix the text-tail-for-parsing slot of the edit state.
    (setf (text-tail-for-parsing current-edit-state)	; nec later?
	  (find-text-tail-for-line		; do more optimally!
	    text-being-edited
	    (car (car (stack-of-positions-after-tokens current-edit-state)))))

    ;; If (a) the change is not an insertion or replacement, (b) no-parsing-or-
    ;; ellipsis-deletion? is not specified, and (c) the cursor is now touching
    ;; an ellipsis, delete the ellipsis.  [Consider also not deleting an
    ;; ellipsis on an undo or redo change.]
    (if (and (null text-line-to-insert?)	; maybe more args to simplify search??
	     (not no-parsing-or-ellipsis-deletion?))
	(let* ((count 1)	       
	       (line-index (cursor-line-index current-edit-state))
	       (character-index (cursor-character-index current-edit-state))
	       (text-tail (text-tail-for-cursor current-edit-state))
	       line-index?
	       character-index?
	       text-tail?
	       character?
	       escape-character?
	       line-index-at-end
	       character-index-at-end)
	  (if t					; unless just look left
	      (loop for i from 1 to ellipsis-text-string-length
		    do (multiple-value-setq
			   (line-index? character-index? text-tail?)
			 (find-next-character-if-any line-index character-index text-tail))
		    while line-index?
		    do (setq line-index line-index?)
		       (setq character-index character-index?)
		       (setq text-tail text-tail?)
		       (incff count)))
	  (if nil				; just look right
	      (decff count ellipsis-text-string-length))
	  (if (>f ellipsis-text-string-length 0)
	      (loop for i from 1 to count
		    do (setq line-index? (setq line-index-at-end line-index))
		       (setq character-index? (setq character-index-at-end character-index))
		       (setq text-tail? text-tail)
		    while
		    (loop with j = ellipsis-text-string-length
			  while
			  (multiple-value-setq
			      (line-index? character-index? text-tail?
					   character? escape-character?)
			    (find-previous-character-if-any
			      line-index? character-index?
			      text-tail? text-being-edited))
			  do (cond
			       ((=f j ellipsis-text-string-length)
				(setq line-index line-index?)
				(setq character-index character-index?)
				(setq text-tail text-tail?)))
			     (decff j)
			     (cond
			       ((not (eqlw character? (charw ellipsis-text-string j)))
				(return t))
			       ((=f j 0)
				(if (null edit-box-change?)
				    (change-edit-box	; inhibit second removal?
				      text-tail? line-index? character-index?
				      line-index-at-end character-index-at-end
;					nil nil nil nil 'automatic
				      )) ; use delete-intelligently-from-text-being-edited?
				(return nil))))))))

    (unless no-parsing-or-ellipsis-deletion?
      (cond
	((or (not servicing-workstation?)
	     (not (eq specific-structure-for-current-workstation-context
		      current-edit-state)))
	 ;; in case we're not servicing workstations, or (MHD 5/2/96) not
	 ;; servicing the current edit state, which we no longer necessarily
	 ;; have to be, e.g., when called from field edit, or, e.g., (MHD
	 ;; 5/2/96), when called from the cut, move, cut-and-paste, etc, command
	 ;; handler, we don't immediately extend parsing; instead, we schedule
	 ;; this to be done. (MHD 1/11/95)
	 (setf (parsing-extension-mode? current-edit-state) t))
	(t	 
	 (extend-parsing-as-appropriate
	   (if (null text-line-to-insert?)	; autocompletion only on an insertion
	       'no-autocompletion
	       t) nil nil change-text?))))

    ;; Enable/disable the undo/redo subcommands as appropriate.
    (cond
      ((edit-subcommand-menu? current-edit-state)
       (update-edit-operation-subcommands
	 (edit-subcommand-menu? current-edit-state))
       (enable-or-disable-subcommand
	 (edit-subcommand-menu? current-edit-state)
	 'undo (not (undo-or-redo-edit-possible-p nil)))
       (enable-or-disable-subcommand
	 (edit-subcommand-menu? current-edit-state)
	 'redo (not (undo-or-redo-edit-possible-p t)))))
    
    (when (function-to-call-on-changed-edit-box-text? current-edit-state)
      (funcall-symbol				; this could exit the context if it is
					;   a special entry context
	(function-to-call-on-changed-edit-box-text? current-edit-state)
	text-being-edited))))

;; Consider eliminating the text-tail? argument.

;; Maybe "character-or-" ...

;; Maybe use change-slot-value in this.




;;; `Compute-distance-of-text-line-from-top' returns the top edge of the one based
;;; line given.  For example 1 returns zero.  Lines appear once every line-height
;;; plus line-spacing units, as specified in the second argument, a
;;; text-box-format.

(defun compute-distance-of-text-line-from-top	; later, maintain in edit box text!!
       (line-index text-box-format)
  (*w (-f line-index 1)				; (*w fixnum workspace-delta)
      (+w (text-cell-line-height text-box-format)
	  (text-cell-line-spacing text-box-format))))



;;; `Update-text-in-edit-box' is used to update a portion of a text when
;;; changing it.  For a contrived example we might have:

;;;       Now is the time
;;;       for all good men
;;;       to come to the 
;;;       aid of their
;;;       country.

;;; And we are changing it to say:

;;;       Now is the time
;;;       for all fast
;;;       women to come to 
;;;       the aid of their 
;;;       country.

;;; To do this update we need to draw only the changing portion. We need to erase
;;; "good men ... aid of thier" and then draw "fast women ... aid of their".

;;; The portion to update is communicated to update-text-in-edit-box via 
;;;    text-segment   -- This is the line were the drawing starts.
;;;    line-index     -- this is the index of that line.
;;;    distance-from-left-to-where-difference-starts?
;;;                   -- This is the offset were the change starts
;;;    text-tail-past-paritial-line-update? 
;;;                   -- This is the line following the text-segment.
;;;    text-tail-past-text-segment?
;;;                   -- This is the first line that didn't change.

;;; Those are the arguments to update-text-in-edit-box, except for
;;; two additions.  The edit-box (or text-box) being updated is the
;;; last argument passed, and the usual erase?  flag is the first
;;; argument.

;;; This fans out into to calls to update-images, one for the first
;;; line of text truncated to skip the prefix specified by
;;; distance-for-left-to-where-difference-starts?  and a second for
;;; the lines following that until the text-tail-past-text-segment?
;;; starts.

;;; If distance-from-left-to-where-difference-starts?  is not specified, the
;;; full width of the text is updated and only one call to update-images is
;;; necessary.

;; - ben 10/30/92

;;; NB: historically, this had been used only for incremental updates to edit
;;; boxes, while editing.  It is now used for incremental updates to any
;;; subclass of text-box.  There are therefore several misnamings present in
;;; this function, not least the function name and the "edit-box" argument name.
;;; (This should be cleaned up some day!)

(defun update-text-in-edit-box
    (erase?
      text-segment text-tail-past-partial-line-update? text-tail-past-text-segment?
      line-index distance-from-left-to-where-difference-starts? edit-box)
  (when (superblock? edit-box)
    (let* ((region-invalidation-is-preferred t)
	   (text-box-format (text-box-format edit-box))
	   (left-edge-of-text-area (+w (left-edge-of-block edit-box)
				       (text-box-left-border-width text-box-format)))
	   (right-edge-of-text-area
	     (if (frame-transforms-of-block edit-box)  ;; Note A
		 most-positive-workspace-coordinate
		 (-w (right-edge-of-block edit-box)
		     (text-box-right-border-width text-box-format))))
	   (line-spacing (text-cell-line-spacing text-box-format))
	   (line-height  (text-cell-line-height text-box-format))
	   (baseline-to-baseline-distance (+w line-height line-spacing))
	   (extra-diacritic-height ; Note E
	     (text-cell-extra-diacritic-height text-box-format))

	   ;; Kludgey fix for slider readout turds.  They have a top margin of 6,
	   ;; but don't seem to be drawn that way.  Probably, this is a bug for
	   ;; all edit boxes, but conservatively change the behavior only for
	   ;; the bug we're fixing (HQ-395141). -fmw, 7/17/95
	   (text-cell-top-margin   ;; Note D
	     (if (frame-of-class-p edit-box 'slider-readout)
		 (-f (text-cell-top-margin text-box-format) 2) ; Fudge by 2 units
		 (text-cell-top-margin text-box-format))))

      (when distance-from-left-to-where-difference-starts?
	(let* ((distance-of-text-segment-from-top
		 (compute-distance-of-text-line-from-top
		   line-index text-box-format))
	       (top-of-first-line-of-first-update-area
		 (+w (top-edge-of-block edit-box)
		     (text-box-top-border-width text-box-format)
		     text-cell-top-margin   ;; Note D
		     distance-of-text-segment-from-top))
	       (top-of-first-update-area
		 (-w top-of-first-line-of-first-update-area
		     extra-diacritic-height))
	       (bottom-of-first-update-area
		 (+w top-of-first-line-of-first-update-area
		     baseline-to-baseline-distance)))

	  (update-images
	    erase? edit-box edit-box
	    (+w (left-edge-of-block edit-box)
		distance-from-left-to-where-difference-starts?)
	    top-of-first-update-area
	    right-edge-of-text-area
	    bottom-of-first-update-area
	    :no-bleeding
	    'draw-text-segment-in-text-box
	    text-segment text-tail-past-partial-line-update?
	    distance-of-text-segment-from-top edit-box)))
      (let ((text-segment?
	      (if distance-from-left-to-where-difference-starts?
		  text-tail-past-partial-line-update?
		  text-segment)))
	(unless (eq text-segment? text-tail-past-text-segment?)
	  (let* ((line-index-of-second-segment
		   (if distance-from-left-to-where-difference-starts?
		       (+f line-index 1)
		       line-index))
		 (distance-of-start-of-text-segment-from-top
		   (compute-distance-of-text-line-from-top
		     line-index-of-second-segment
		     text-box-format))
		 (vertical-delta-to-end-of-text-segment
		   (*w 
		     (-f (find-line-index-for-text-tail
			   text-segment
			   text-tail-past-text-segment?
			   line-index)
			 line-index-of-second-segment)
		     baseline-to-baseline-distance))
		 (top-of-first-line-of-second-update-area
		   (+w (top-edge-of-block edit-box)
		       (text-box-top-border-width text-box-format)
		       text-cell-top-margin  ;; Note D
		       distance-of-start-of-text-segment-from-top))
		 (top-of-second-update-area
		   (-w top-of-first-line-of-second-update-area
		       extra-diacritic-height))
		 (bottom-of-second-update-area
		   (+w top-of-first-line-of-second-update-area
		       vertical-delta-to-end-of-text-segment)))

	    ;; Can text-segment? really be NIL here?
	    (update-images
	      erase? edit-box edit-box
	      left-edge-of-text-area  top-of-second-update-area
	      right-edge-of-text-area bottom-of-second-update-area
	      :no-bleeding ;; Note C.
	      'draw-text-segment-in-text-box
	      text-segment? text-tail-past-text-segment?
	      distance-of-start-of-text-segment-from-top edit-box)))))))

;; Note A: This cause happens.  First we can't cheaply compute the real
;; right edge of the text that's changing so we are forced use an rough
;; estimate.  The else clause works because in classic G2 the text never
;; ran outside of the block edges.  The then clause works -- because we
;; have a frame we know that the drawing harness will create a draw area
;; for the frame interior and intersect that against this huge number.
;; Of course it is SAD that we are looking at the frame transform at all!
;; See also Note A on draw-or-change-color-of-text-box which is analagous.

;; Note B: I think that the A,B,C of text-segment text-tail-past-partial-line-update? and 
;; text-tail-past-text-segment? are such that B is found in A, and C is found in 
;; B.  So... if we did the first call to update images we have updated A..B, and
;; the second call can update just B..C, rather A..C.
;; - ben 11/02/92

;; Note C: This is one of the few calls on update images that supresses the bleeding
;; hack.  Text updating is carefully engineered to never bleed, for example
;; the drawing of text is supressed at extremely small scales.  - ben 6/23/93

;; Note D: This use of margin is risky because the workspace coordinate computed
;; here may scale into one position while text drawing code computes this line
;; boundry by a much more complex algorithum which can get a different awnser.
;; To reduce the risk of this creating turds we ought to have a low level per
;; window incremental text update routine, but instead we pretend that the
;; interline leading is sufficent protect us.

;; Note E: extra height added as part of Thai language support. (MHD 12/19/03)














;;;; Marking Contexts <OLD>


;;; `put-up-edit-operations-menu-in-current-marking-state' posts the little
;;; popup menu of edit operations on the just selected text region.

;;;  1			 2			 3
;;; ---			---			---
;;; paste		replace from scrapbook	paste (when there's a text selection)
;;; delete		delete			clear
;;; insert		insert at cursor	copy, then adjust cursor, then paste
;;; move		move to cursor		almost like: cut, then adjust cursor, then
;;; 						  paste; however, the scrapbook is then
;;; 						  somehow restored to the same state as before
;;; 						  the entire operation
;;; save		copy (to scrapbook)	copy 
;;; cut			copy and delete		cut
;;; cut and insert	copy and move to cursor	cut, then adjust cursor, then paste


;;;  4
;;; ---
;;; cut
;;; copy
;;; paste
;;; delete
;;; insert
;;; move
;;; cut and insert


;;; KEY: 1 = alternate set of menu choices; 2 = alternate, more self-documenting set;
;;; 3 = equivalences in terms of Mac guidelines; 4 = current set (like set 1, but with
;;; the first four closest to the Mac guidelines at the top and "save" changed to
;;; "copy" to be closer to the Mac guideline.


;;; `Scrap-text-region' creates and returns a scrap containing the text specified by
;;; text-region.  Text-box-format-for-scrap?, if specified, overrides the default
;;; as the format for new text box for the new scrap.  If add-to-scrapbook? is
;;; non-nil, the scrap is added to the scrapbook workspace, which is created if
;;; it cannot be gotten by get-workspace.

;;; Scraps are always added above the most recently added scrap and below the workspace
;;; name box.  The top one will always be used for pasting operations.  This is usually
;;; the most recently cut/copied scrap, but it might be otherwise if the user had manually
;;; moved some other scrap to be vertically higher up.


(defun scrap-text-region (text-region text-box-format-for-scrap? add-to-scrapbook?
				      &optional
				      replace-fragments-on-sides?
				      handle-spaces-intelligently?)
  (scrap-text
    (convert-text-string-to-text
      (convert-text-region-to-text-string text-region))
    text-box-format-for-scrap?
    add-to-scrapbook?
    replace-fragments-on-sides?
    handle-spaces-intelligently?))


;;; Scrap-text ... must be called in a for-workstation context.

(defun scrap-text (text text-box-format-for-scrap? add-to-scrapbook?
			&optional 
			replace-fragments-on-sides?
			handle-spaces-intelligently?)
  (let ((scrap (make-frame 'scrap)))
    (change-slot-value scrap 'replace-fragments-on-sides? replace-fragments-on-sides?)
    (change-slot-value scrap 'handle-spaces-intelligently? handle-spaces-intelligently?) 
    (setf (text-box-format scrap)
	  (or text-box-format-for-scrap?
	      (get-or-make-format-frame
		(default-text-box-format-name scrap))))
    (setf (box-translation-and-text scrap)
	  (slot-value-cons no-value text))
    (reformat-text-box-in-place scrap)
    (cond
      (add-to-scrapbook?
       (let* ((scrapbook
		(or (get-workspace 'scrapbook)
		    (make-workspace
		      'non-kb-workspace 'scrapbook
		      nil nil nil nil current-workstation)))
						; note: current-workstation used
						;   above is ignored in 2.0 versions.
						;   (MHD 10/1/90)
	      (workspace-margin (workspace-margin scrapbook))
	      (spacing 10)			; parameter?
	      (name-box?
		(loop for subblock being each subblock of scrapbook
		      when (of-class-p subblock 'workspace-name-box)
			return subblock))
	      (top-scrap? (get-scrap-if-any)))
	 (add-to-workspace
	   scrap scrapbook
	   (if top-scrap?
	       (left-edge-of-block top-scrap?)
	       (+w (left-edge-of-block scrapbook) workspace-margin))
	   (if top-scrap?
	       (-w (top-edge-of-block top-scrap?)
		   spacing
		   (height-of-block scrap))
	       (+w (top-edge-of-block scrapbook) workspace-margin))
	   t t)
	 (cond
	   (name-box?
	    (erase-images-of-block name-box? t)
	    (shift-block
	      name-box?
	      (-w (left-edge-of-block scrap)
		  (left-edge-of-block name-box?))
	      (-w (-w (top-edge-of-block scrap)
		      spacing
		      (height-of-block name-box?))
		  (top-edge-of-block name-box?)))	    
	    (enlarge-workspace-for-block-rectangle-if-necessary
	      name-box? scrapbook)
	    (draw-images-of-block name-box? t)))
	 (delete-excess-scraps-if-any scrapbook))))
    scrap))





;;; Delete-excess-scraps-if-any ... maintains the constraint that no more
;;; than (maximum-number-of-scraps-to-keep editor-parameters) scraps will
;;; be kept on a scrapbook.

(defun delete-excess-scraps-if-any (scrapbook)
  #-subblocks-v2
  (loop with maximum-number-of-scraps-to-keep
	  = (maximum-number-of-scraps-to-keep editor-parameters)
	with number-of-scraps-seen-so-far = 0
					; assume ordering from newest to oldest
	for remaining-subblocks on (subblocks scrapbook)
	when (frame-of-class-p (car remaining-subblocks) 'scrap)
	  do (incff number-of-scraps-seen-so-far)
	when (>f number-of-scraps-seen-so-far
		 maximum-number-of-scraps-to-keep)
	  return
	  ;; NOTE: why the list remaining-subblocks itself is not touched here?
	  (loop with copy-of-remaining-subblocks
		  = (copy-list-using-gensym-conses remaining-subblocks)
		for subblock in copy-of-remaining-subblocks
		when (frame-of-class-p subblock 'scrap)
		  do (delete-frame subblock)
		finally
		  (reclaim-gensym-list copy-of-remaining-subblocks)))
  #+subblocks-v2
  (loop with maximum-number-of-scraps-to-keep
	  = (maximum-number-of-scraps-to-keep editor-parameters)
	with number-of-scraps-seen-so-far = 0
	with constant-queue = (subblocks scrapbook)
	with head = (constant-queue-head constant-queue)
	for queue-element = #-Lockfree-Deque head
			    #+Lockfree-Deque (constant-queue-next head constant-queue)
		       then next-queue-element
	until #-Lockfree-Deque (eq queue-element constant-queue)
	      #+Lockfree-Deque (null queue-element)
	for subblock = (queue-datum queue-element)
	for next-queue-element = (constant-queue-next queue-element constant-queue)
	when (frame-of-class-p subblock 'scrap)
	  do (incff number-of-scraps-seen-so-far)
	when (>f number-of-scraps-seen-so-far
		 maximum-number-of-scraps-to-keep)
	  do (when (frame-of-class-p subblock 'scrap)
	       (delete-frame subblock)
	       ;; NOTE: in subblocks-v1 the queue element is not deleted.
	       (constant-queue-delete queue-element constant-queue))))

;; If you watch this thing work, it is disappointing that if the number of
;; scraps is at the limit, it still keeps growing upwards, leaving blank
;; space at the bottom of the workspace.  Sigh! (MHD 5/15/91)

;; This could be a little faster if it didn't have to copy the list of
;; remaining subblocks and could batch the deletions of subblocks a little
;; bit; see delete-subblocks-of-class.  Also, the does one redundant frame-
;; of-class-p.  Also, it might be possible for it to assume
;; (frame-of-class-p subblock 'scrap) for all subblocks except for the name
;; box. (MHD 5/15/91)

;; This could take a really long time, like if they changed their limit
;; from 20,000 to 1 after editing for a long time.  This could be fixed
;; by having a background "garbage collector", which we could also use
;; for Inspect results!  (MHD 5/15/91)





;;; There-is-a-scrap-p ... must be called in a for-workstation context.


(defun there-is-a-scrap-p ()  
  (let ((scrapbook? (get-workspace 'scrapbook)))
    (if scrapbook?
	(loop for subblock being each subblock of scrapbook?
	      thereis (frame-of-class-p subblock 'scrap)))))



;;; Get-scrap-if-any ... must be called in a for-workstation context.

(defun get-scrap-if-any ()
  (let ((scrapbook? (get-workspace 'scrapbook)))
    (if scrapbook?
	(loop with top-edge-so-far = (bottom-edge-of-block scrapbook?)
	      with top-choice? = nil
	      for subblock being each subblock of scrapbook?
	      as top-edge = (top-edge-of-block subblock)
	      when (and (frame-of-class-p
			  subblock 'scrap)
			(<w top-edge top-edge-so-far))
		do (setq top-choice? subblock)
		   (setq top-edge-so-far top-edge)
	      finally (return top-choice?)))))

;; Apparently this get-scrap-if-any is called for only two reasons.
;; First when there-is-a-scrap-p should have been called, and
;; Second when get-test-of-scrap should have been called. - ben 3/29/94

(defun coerce-scrap-to-text-string (&optional (scrap (get-scrap-if-any)))
  (convert-text-to-text-string
    (cdr (box-translation-and-text scrap))))








;; Functions to Support Text Region Selection

;; These are not necessarily desirable or ideal abstractions, but exist, rather,
;; to allow certain EDIT functionality to be accessed from the selection code in
;; module MENUS. (MHD 8/8/88)



;;; Change-edit-box-cursor-position ... The no-parsing-or-ellipsis-deletion? is
;;; as per change-edit-box.  This must be called in an editing context.

(defun change-edit-box-cursor-position (line-index character-index
						   &optional no-parsing-or-ellipsis-deletion?)
  (change-edit-box
    nil line-index character-index
    nil nil nil nil nil
    no-parsing-or-ellipsis-deletion?))








;;;; Cut and Paste


;;; A `scrap' is a text box which, when clicked on when editing, inserts part or all
;;; of its text into the current edit box.  Scraps contain arbitrary free text.  The
;;; top level class, SCRAP, is always used for text cut (or copied) while editing.
;;; The class SCRAP is never created explicitly by users.  The class TEXT-INSERTER,
;;; under scrap, can be created by the user under the "New Free Text" menu on
;;; workspaces.  The class scrap, for insertion purposes, behaves just like the
;;; class text-inserter.   Text inserters are intended to be useful for users
;;; creating custom editor menus for entering Kanji and special characters.  It can
;;; also be used to shorten long inspect commands, which may be frequently repeated,
;;; by allowing them to be entered by a single click.

;;; The relevant slots on scraps are handle-spaces-intelligently? and
;;; replace-fragments-on-sides?, which are used as the arguments of the same
;;; name to insert-text-string-in-text-being-edited, and which are documented
;;; there.  They are both true for the classes scrap, text-inserter, and
;;; word-inserter, and they are both false for classes character-inserter and
;;; character-sequence-inserter.

;;; Although both handle-spaces-intelligently? and replace-fragments-on-sides?
;;; are lookup slots and should not generally be changed from their defaults,
;;; either by the user or by code, we make an exception.  When creating an
;;; unspecialized scrap, which is what we use for copy, cut, and paste in the
;;; editor, we create the scrap and immediately set these variables.  We do this
;;; because the inserters which the user creates have somewhat different
;;; semantics than the inserters we need for copy and paste.  This is primarily
;;; because replace-fragments-on-sides? is true for some of the user-defined
;;; inserters.  [Changed behavior for 4.0. PGA 6/13/95]
;;;
;;; A new slot, replace-entire-text?, has been added but still is not
;;; represented by any subclass.

;;; The slots are not editable by or visible to the user.
;;;
;;; These slots are "generic" to (i.e., shared with) the class token-menu.  This
;;; requires that they be lookup slots.  The accessors happen to be defined
;;; here, i.e., for the class scrap.  (They should only be defined in one
;;; place.)

;;; A `text inserter' is a kind of scrap which inserts its entire text.  

;;; A `word inserter' is a kind of scrap which inserts the "word" the user clicked on.
;;; A "word", in this context is simply a series of characters delimited by spaces.
;;; If the user clicks in space, nothing is inserted.

;;; A `character inserter' is a kind of scrap which inserts the character clicked on.

;;; A `character sequence inserter' is like a word inserter, in that it selects
;;; sequences of characters delimited by spaces, and it like a character inserter
;;; in that it does not insert the selection with surrounding spaces.

(def-class (scrap text-box) 	; borderless-free-text until 5/23/89
  (box-translation-and-text nil (type free text))
  (default-text-box-format-name
      scrap-format
      (attribute-export-comment
	"Export text-format-name, separate mechanism for part copy of named ~
 	format"))
  (replace-fragments-on-sides?
    t lookup-slot system
    (attribute-export-comment "Export boolean, writable = false"))
  (handle-spaces-intelligently?
    t lookup-slot system
    (attribute-export-comment "Export boolean, writable = false"))
  (replace-entire-text?			; NEW. NO SUBCLASS REFINES
    nil lookup-slot system		;   THIS YET! (MHD 4/17/94)
    (attribute-export-comment "Export boolean, writable = false"))) 

(def-class (text-inserter (item scrap) (foundation-class text-inserter))
  (text-cell-plist-for-text-box nil user-overridable))

(def-class (word-inserter text-inserter (foundation-class word-inserter)))

(def-class (character-inserter text-inserter (foundation-class character-inserter))
  (replace-fragments-on-sides? nil)
  (handle-spaces-intelligently? nil))

(def-class (character-sequence-inserter text-inserter
					(foundation-class character-sequence-inserter))
  (replace-fragments-on-sides? nil)
  (handle-spaces-intelligently? nil)) 


(def-spot text-inserter-spot
    :slots nil
    :include spot ;; maybe ought to be entity or text-box spot?
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented scrap)

(def-class-method generate-spot (scrap mouse-pointer)
  (push-last-spot mouse-pointer
		  (make-text-inserter-spot)
		  scrap)) 



;; The following was put into the Kanji-menus and Kanji-flow KBs by mistake in
;; 2.0 for AAAI and an earlier spinoff to C.Itoh.  It is the format used for the
;; Hiragana-Katakana menu.  Try to get rid of it, or at least change the name!
;; (MHD 8/25/89)

(def-text-cell-format hk-format
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 0
  minimum-format-width-for-text-cell 800)

;; Consider perhaps an "expression inserter", which does the (innermost) expression
;; clicked on.



;;; Select-text-region-in-scrap ...

(defun select-text-region-in-scrap
       (scrap x-in-workspace y-in-workspace)
  (let* ((text (cdr (box-translation-and-text scrap)))
	 selected-line-index selected-character-index text-tail
	 beginning-line-index beginning-character-index
	 end-or-end-line-index end-character-index)
    (multiple-value-setq
      (selected-line-index selected-character-index text-tail)
      (find-position-in-text
	scrap nil nil nil t
	x-in-workspace y-in-workspace nil nil nil
	nil t))
    (if (frame-class-case scrap
	  ((word-inserter character-sequence-inserter)
	   (cond
	     ((not (multiple-value-bind
		       (line-index character-index text-tail character?)
		       (find-next-character-if-any
			 selected-line-index selected-character-index
			 text-tail)
		     (declare (ignore line-index character-index text-tail))
		     (or (null character?)
			 (blank-p character?))))
	      ;; not in whitespace:
	      (multiple-value-setq
		(beginning-line-index beginning-character-index)
		(find-word-boundary-in-text
		  selected-line-index selected-character-index
		  text text-tail t))
	      (multiple-value-setq
		(end-or-end-line-index end-character-index)
		(find-word-boundary-in-text
		  selected-line-index selected-character-index
		  text text-tail nil))
	      t)))
	  (character-inserter
	   (cond
	     ((multiple-value-setq
		(end-or-end-line-index end-character-index)
		(find-next-character-if-any
		  selected-line-index selected-character-index text-tail))
	      (setq beginning-line-index selected-line-index)
	      (setq beginning-character-index selected-character-index)
	      t)))
	  (t
	   (setq beginning-line-index 1)
	   (setq beginning-character-index 0)
	   (setq end-or-end-line-index 'end)
	   t))
	(make-text-region
	  scrap nil
	  beginning-line-index beginning-character-index
	  end-or-end-line-index end-character-index))))

;; Consider including up to one space on the left and one space on the right, if
;; present, in the region for the word-inserter case (and not in the character-
;; sequence-inserter case) in order to give user feedback as to how the text will
;; be inserted.



;;; Find-word-boundary-in-text ... returns as values the line index and character
;;; index of the next "word boundary", that is, the next adjacent space or newline
;;; or end of text.  If backwards? is true, it searches backwards for the word
;;; boundary, that is, the previous space or newline or beginning of text.  Note
;;; that if line-index and character-index already pointing to a word boundary, or
;;; are one character in front of a word boundary in the backwards? case, they are
;;; just returned.

(defun find-word-boundary-in-text
       (selected-line-index selected-character-index
	text selected-text-tail backwards?)	       
  (loop with adjacent-character?
	with line-index-away-from-cursor?
	with character-index-away-from-cursor?
	with text-tail?
	as line-index
	   = selected-line-index
	   then line-index-away-from-cursor?
	as character-index
	   = selected-character-index
	   then character-index-away-from-cursor?
	as text-tail
	   = selected-text-tail
	   then text-tail?
	do (multiple-value-setq
	     (line-index-away-from-cursor? character-index-away-from-cursor?
	      text-tail? adjacent-character?)
	     (if backwards?
		 (find-previous-character-if-any
		   line-index character-index text-tail text)
		 (find-next-character-if-any
		   line-index character-index text-tail)))
	   (if (or (null line-index-away-from-cursor?)
		   (and adjacent-character? (blank-p adjacent-character?)))
	       (return (values line-index character-index text-tail)))))

;; At present, this is just used twice (once forwards and once backwards) in the
;; function preceeding it; consider putting it inline or generalizing it and
;; moving it elsewhere! (MHD)



(def-text-box-format scrap-format
  text-cell-font-map (hm18)			; 1 en = 10 workspace units
  text-cell-line-height 19			; experiment with these!
  text-cell-baseline-position 14
  text-cell-line-spacing 3
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 6.75)  ; 2/3 en
  minimum-word-spacing #.(convert-to-text-width 5)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 15)	          ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 0
  text-cell-lines-justified? nil
  text-cell-line-color? black
  text-box-border-color? black
  ;; next four were commented out until 5/13/89, resulting
  ;;   in the default 2-pixel-wide box border:
;  text-box-left-border-width 0       ; borderless text boxes pose problems in dragging,
;  text-box-top-border-width 0        ;   selection, and suppression of text at small scale
;  text-box-right-border-width 0
;  text-box-bottom-border-width 3
  ;; new for 5/16/89:
  text-box-left-border-width 1
  text-box-top-border-width 1
  text-box-right-border-width 1
  text-box-bottom-border-width 1
  ;; next four were not present until 5/13/89:
;  text-cell-left-margin 4
;  text-cell-top-margin 3
;  text-cell-right-margin 4
;  text-cell-bottom-margin 3
  ;; new for 5/16/89:
  text-cell-left-margin 12
  text-cell-top-margin 8
  text-cell-right-margin 12
  text-cell-bottom-margin 4)

;; The above is a copy of free-text-format, except that text-cell-turnover-
;; line-indentation = 0. (MHD 8/6/88)

;; The `small-scrap-format' and `extra-large-scrap-format' is copied from
;; corresponding free-text-format,and modified compare free-text-format with scrap-format
;; -- GENSYMCID-736 -- xu.jingtao@glority.com 14-Jun-2012
(def-text-box-format small-scrap-format
  text-cell-font-map (hm14)			; 1 en = 10 workspace units
  text-cell-line-height 15			; experiment with these!
  text-cell-baseline-position 13
  text-cell-line-spacing 2
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 4.75)
  minimum-word-spacing #.(convert-to-text-width 4)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 12)	          ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 0
  text-cell-lines-justified? nil
  text-cell-line-color? black
  text-box-border-color? black
  text-box-left-border-width 1
  text-box-top-border-width 1
  text-box-right-border-width 1
  text-box-bottom-border-width 1
  text-cell-left-margin 8
  text-cell-top-margin 4
  text-cell-right-margin 8
  text-cell-bottom-margin 4)
(setf (corresponding-small-font-format-name 'scrap-format) 'small-scrap-format)

(def-text-box-format extra-large-scrap-format
  text-cell-font-map (hm24)			; 1 en = 10 workspace units
  text-cell-line-height 26			; experiment with these!
  text-cell-baseline-position 19
  text-cell-line-spacing 3
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 8.75)  ; 5/8 en
  minimum-word-spacing #.(convert-to-text-width 7)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 21)	          ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 0
  text-cell-lines-justified? nil
  text-cell-line-color? black
  text-box-border-color? black
  text-box-left-border-width 1
  text-box-top-border-width 1
  text-box-right-border-width 1
  text-box-bottom-border-width 1
  text-cell-left-margin 15
  text-cell-top-margin 11
  text-cell-right-margin 15
  text-cell-bottom-margin 10)
(setf (corresponding-extra-large-font-format-name 'scrap-format) 'extra-large-scrap-format)


;;; `Get-selected-text-region-for-edit-box' returns the currently
;;; selected text region.  

(defun get-selected-text-region-for-edit-box ()
  (loop for subblock being each subblock of (edit-box current-edit-state)
	when (and (frame-of-class-p subblock 'text-region)
		  (not (eq subblock
			   (kfep-conversion-text-region?
			     current-edit-state))))
	  return subblock))

;; At present, only one text region, besides possibly that used as the KFEP
;; conversion text region, may exist in an edit box, and it may be assumed to be
;; the selected one.  Later, this could change, and the above code will have to
;; changed to something more appropriate.



;;; `Paste-from-current-scrap-if-any' ...

(defun paste-from-current-scrap-if-any ()  
  (with-backtrace-for-internal-error 'paste-from-current-scrap-if-any
    (let* ((scrap? (get-scrap-if-any)))
      (when scrap?
	(let ((text-string (coerce-scrap-to-text-string scrap?)))
	  (paste-text-string
	    text-string
	    (replace-fragments-on-sides? scrap?)
	    (handle-spaces-intelligently? scrap?))
	  (reclaim-text-string text-string))
	t))))



;;; `Paste-text-string' pastes the text string at either the location of the
;;; current selection, if there is one, or else at the current cursor location.
;;; If there is a selected text region, it gets deleted and replaced with pasted
;;; text, and the cursor moves to the end of the replacement text.  Otherwise,
;;; the text is simply inserted at the cursor, and the cursor also advances to
;;; the end of the replacement text.  Note that text-string does not get
;;; reclaimed.
;;;
;;; The arguments replace-fragments-on-sides? and handle-spaces-intelligently?
;;; are as documented for insert-text-string-in-text-being-edited.

(defun paste-text-string (text-string
			   &optional
			   replace-fragments-on-sides?
			   handle-spaces-intelligently?)
  (with-backtrace-for-internal-error 'paste-text-string
    (let ((text-region? (get-selected-text-region-for-edit-box)))
      (cond
	(text-region?
	 (multiple-value-bind
	     (text-tail start-line-index start-character-index
			end-line-index end-character-index)
	     (get-text-region-position text-region?)
	   ;; We have now extracted the start and end indexes
	   ;; from the text region, and we need no further
	   ;; information from it.  So we delete it here.
	   (delete-frame text-region?)
	   ;; This moves the cursor to the end of the selected region.  That way,
	   ;; it will be kept at the end of the replacement text.  However, note
	   ;; that this shows up as an extra undoable operation.  That's probably
	   ;; not desirable.  Review this issue later! (MHD 3/21/97)
	   (change-edit-box-cursor-position ; HQ-3317175 "pasting over ..." (MHD 1/24/99)
	     end-line-index end-character-index t);    
	   (with-backtrace-for-internal-error 'insert-text-string-in-text-being-edited
	     (insert-text-string-in-text-being-edited
	       text-string
	       replace-fragments-on-sides?
	       handle-spaces-intelligently?
	       start-line-index start-character-index text-tail
	       end-line-index end-character-index))))
	(t
	 (with-backtrace-for-internal-error 'insert-text-string-at-cursor
	   (insert-text-string-at-cursor
	     text-string
	     replace-fragments-on-sides?
	     handle-spaces-intelligently?)))))))









;;; `Coerce-text-region-to-scrap' move the text covered by a text region on to
;;; the scrap, and revise the editor's buttons.  The resulting scrap will have
;;; handle-spaces-intelligently? if text-region represents a "word-like" sequence
;;; in text (see word-like-sequence-in-text-p).
;;;
;;; As of 5.0, in addition, this function copies the text to the native window
;;; clipboard.  Note that previous versions of G2 did not do this.  Those
;;; versions cannot therefore implement interclient communication, and also
;;; cannot take part in the newer G2/Telewindows Cut and Paste protocol.

(defun coerce-text-region-to-scrap (text-region)
  (let ((replace-fragments-on-sides? nil)
	(handle-spaces-intelligently?
	  (handle-spaces-intelligently-p
	    text-region)))
    
    (scrap-text-region
      text-region
      (get-or-make-format-frame 'scrap-format)
      t
      replace-fragments-on-sides?
      handle-spaces-intelligently?)
    
    (setf (workstation-clipboard-has-text-p
	    current-workstation)
	  t)
    (when (edit-subcommand-menu? current-edit-state)
      (enable-or-disable-subcommand
	(edit-subcommand-menu? current-edit-state)
	'paste nil))  ; nil means enable the command (paste) 
    (copy-text-region-to-cut-buffer-if-appropriate text-region)))


	
(defun copy-text-region-to-cut-buffer-if-appropriate (text-region)
  (when servicing-workstation?
    (when (window-supports-native-cut-and-paste current-workstation-window)
      (let ((text-string (convert-text-region-to-text-string text-region)))
	(copy-text-string-to-cut-buffer current-workstation-window text-string)
	(reclaim-text-string text-string))
      t)))



;;; The G2 system procedure `g2-copy-text-to-clipboard' can fail if the
;;; window argument is invalid in some way.

(defun-for-system-procedure g2-copy-text-to-clipboard
    ((text-string text) (g2-window item))
  (declare (values truth-value))
  (let (workstation window)
    (cond ((and (of-class-p g2-window 'g2-window)
		(setq workstation (workstation-for-g2-window? g2-window))
		(setq window (window-for-workstation workstation))
		(window-supports-native-cut-and-paste window))
	   (copy-text-string-to-cut-buffer window text-string)
	   truth)
	  (t falsity))))



;;; The function `request-paste-for-editor' is called when the user
;;; has requested a paste of text from a cut buffer, e.g., by clicking
;;; paste on the menu or typing a keyboard accelerator (e.g., ctrl+v
;;; or the Paste key on Sun keyboards).
;;;
;;; This function puts the edit state into a special mode in which it
;;; does not service any events until either it has timed out or the
;;; paste request has been fulfilled.
;;;
;;; This sends to the current gensym window, which could be a client
;;; Telewindows window, a request to get the contents of its cut buffer
;;; and send back to G2 (via the Telewindows/ICP protocol) a paste
;;; message.
;;;
;;; If this is called outside of a workstation context, this does nothing and
;;; simply returns nil.  Otherwise, it immediately returns t after sending the
;;; request and putting the edit state into its special mode.

(defun obtain-paste-request-id-for-editor (workstation)
  (prog1 (setf (current-paste-request-id? current-edit-state)
	       (workstation-paste-request-id workstation))
    (incff (workstation-paste-request-id workstation))))



(defun request-paste-for-editor ()
  (when servicing-workstation?
    (request-paste-of-cut-buffer-text
      current-workstation-window
      (obtain-paste-request-id-for-editor current-workstation))
    t))

;;; The function `request-paste-availability-for-editor' is called by G2
;;; when a new editor is being shown. It requests from TW (or the current
;;; G2 window) whether anything is available to paste. TW should respond
;;; with its ICP message update-paste-availability-status.

(defun request-paste-availability-for-editor ()
  (when servicing-workstation?
    (request-paste-availability-status
      current-workstation-window
      (obtain-paste-request-id-for-editor current-workstation))
    t))

;; The Paste Request ID Protocol: The full protocol is not quite in place.  The
;; idea is to never handle a paste out of sequence with the user's gesture, and
;; to never confuse a paste requested at time T with a paste at time T1, or a
;; paste for a different editor with a paste for this one.  These are not very
;; common, but can occur without this protocol.  Right now, we don't enter any
;; kind of special state when we're waiting for a request.  We should really
;; enter a new workstation context that almost handles nothing at all (maybe
;; abort and a few other things?), and just waits for the request to come in, or
;; time out after an unreasonable amount of time has elapsed.  Consider this for
;; later.  This now is a little bit of a race condition.  Occasionally, if there
;; a slowness for some reason -- slow X server, slow connection, huge amount of
;; data, slow processor, etc. -- this could paste at an inappropriate time,
;; i.e., after some type-in had been done.  This should never cause an abort,
;; just a slightly wrong sequence of edits to the text, from which the user can
;; typically easily recover.  (MHD 4/8/97)






;;; `handle-paste-event-in-g2' enqueues a workstation event
;;; using the paste-request keycode. When workstation
;;; events are handled, if an editor exists, then the
;;; private-editor-commands keymap results in a call to
;;; paste-into-editor. This can be called as a
;;; result of an icp message from TW or because of an event
;;; in the G2 local window.

(defun handle-paste-event-in-g2 (gensym-window text-string request-id timestamp?)
  (let ((workstation (workstation-this-is-on gensym-window)))
    (let ((x (x-in-window-of-mouse? workstation))
	  (y (y-in-window-of-mouse? workstation))
	  (timestamp (or timestamp?		
			 (+f additional-time-for-synthetic-paste-event-timestamps
			     (fixnum-time-of-mouse-pointer
			       (mouse-pointer-of-latest-event
				 workstation)))))
	  (event-code (key-code 'paste-request)))
      (multiple-value-bind (pane? image-plane?)
	  (decode-window-position gensym-window x y)
	#+development
	(when trace-local-events
	  (trace-local-event "paste " event-code x y timestamp))
	(enqueue-workstation-event
	  workstation event-code x y timestamp
	  gensym-window pane? image-plane?
	  (gensym-list request-id (copy-text-string text-string)))))))

;; The last argument to enqueue-workstation-event is the
;; event-detail: a list of the request id and the
;; text-string. The text string has to be copied because
;; the ICP event is going to go away before the workstation
;; event gets handled.




;;; `handle-paste-availability-event-in-g2' sets
;;; workstation-clipboard-has-text-p for this window, then
;;; enqueues a workstation event using the
;;; paste-availability-request keycode. When workstation
;;; events are handled, if an editor exists, then the
;;; private-editor-commands keymap results in a call to
;;; make-paste-menu-available. This can be called as a
;;; result of an icp message from TW or because of an event
;;; in the G2 local window.

(defun handle-paste-availability-event-in-g2 (gensym-window status timestamp?)
  (let ((workstation (workstation-this-is-on gensym-window)))
    (setf (workstation-clipboard-has-text-p workstation) status)
    (let ((x (x-in-window-of-mouse? workstation))
	  (y (y-in-window-of-mouse? workstation))
	  (event-code (key-code 'paste-availability-request))
	  (timestamp (or timestamp?		
			 (+f additional-time-for-synthetic-paste-event-timestamps
			     (fixnum-time-of-mouse-pointer
			       (mouse-pointer-of-latest-event
				 workstation))))))
      (multiple-value-bind (pane? image-plane?)
	  (decode-window-position gensym-window x y)
	#+development
	(when (eq trace-local-events 'paste)
	  (trace-local-event "paste availability " event-code x y timestamp))
	(enqueue-workstation-event
	  workstation event-code x y timestamp
	  gensym-window pane? image-plane?)))))




;;; `Text-string-matches-current-scrap-p' heuristically determines if its
;;; argument text-string matches the current scrap.  If it does, then G2's
;;; editor may assume that the text string was copied to the clipboard from G2,
;;; and therefore G2 should use the additional information it applied to the
;;; scrap when it was copied, i.e., analysis of whether it's "wordlike" or not.
;;; This then permits intelligent cut and paste to be supported while at the
;;; same time allowing text sharing between G2 and other applications running on
;;; the same platform.  Note that this is heuristic and may be fooled.  This
;;; also may break down around non-English alphabetic characters, normalization
;;; of spaces, tabs, and other spacing characters, different linebreak
;;; conventions, and so on.  Note that this does not reclaim or mutate
;;; text-string in any way.  Nor does it create any objects that need
;;; reclamation.

(defun text-string-matches-current-scrap-p (text-string)
  (let ((scrap? (get-scrap-if-any)))
    (if scrap?
	(let ((text-string-from-scrap
		(coerce-scrap-to-text-string scrap?)))
	  (prog1 (string=w text-string text-string-from-scrap)
	    (reclaim-text-string text-string-from-scrap))))))




;;; `Editor-has-non-empty-text-region-p' is true if there's a selected text
;;; region in the current editing context, and that region is non-empty.  (Empty
;;; regions usually exist only transiently, if at all, in this editor.)

(defun editor-has-non-empty-text-region-p ()
  (let ((text-region? (get-selected-text-region-for-edit-box)))
    (and text-region? (not (empty-text-region-p text-region?)))))


;;; `Text-can-be-transferred-within-editor-p' is true if text can be "transferred",
;;; meaning moved from a text region to a cursor position outside of that region.
;;; This returns true if the there's a selected text region in the current editing
;;; context, and that region is non-empty, and the current cursor position does not
;;; fall inclusively between the fixed and free ends of the region.

(defun text-can-be-transferred-within-editor-p ()
  (let ((text-region? (get-selected-text-region-for-edit-box)))
    (and text-region?
	 (within-text-region-p
	   text-region?
	   (cursor-line-index current-edit-state)
	   (cursor-character-index current-edit-state)))))
	   
	   

;;; `Text-can-be-cut-within-editor-p' is true iff there's a selected text region
;;; in the current editing context.

(defun text-can-be-cut-within-editor-p ()
  (editor-has-non-empty-text-region-p))


;;; `Text-can-be-copied-within-editor-p' is true iff there's a selected text
;;; region in the current editing context.

(defun text-can-be-copied-within-editor-p ()
  (editor-has-non-empty-text-region-p))


;;; `Text-can-be-pasted-in-current-workstation-p' may be called in any
;;; for-workstation context to determine if the current workstation has text in
;;; its "clipboard", i.e., available to be pasted.  Note that when talking to a
;;; 4.0 Telewindows, the "clipboard" really is the scrapbook, since Telewindows
;;; doesn't implement the native cut and paste protocol.

(defun text-can-be-pasted-in-current-workstation-p ()
  (if (window-supports-native-cut-and-paste current-workstation-window)
      (workstation-clipboard-has-text-p current-workstation)
      (there-is-a-scrap-p)))


;;; `Text-can-be-deleted-within-editor-p' is true iff there's a selected text
;;; region in the current editing context.  (Note: although it's slightly
;;; confusing, this is not true even when text could be deleted by typing the
;;; delete key; i.e., this is just for the case of having a text region to
;;; delete.)

(defun text-can-be-deleted-within-editor-p ()
  (editor-has-non-empty-text-region-p))





;;;; Handling Parsing and Compilation Problems



;;; Handle-parsing-or-compilation-problem ...  Problem string might be "This is unparsable",
;;; "This is incomplete", "This is ambiguous", "This is uncompilable", etc.

;;; If the special variable keep-edit-workspace-hidden-no-matter-what? is non-nil,
;;; handle-parsing-or-compilation-problem does not put up an edit workspace if it is
;;; hidden even if the text is unparsable.  This variable is bound at top-level to nil.

(defun handle-parsing-or-compilation-problem (problem-string &optional
							     line-index? character-index?)
  (let ((edit-workspace-hidden?
	  (null (image-planes-this-is-on current-edit-workspace))))
    ;; JED 8/10/94 Attempt to preserve real debugging info for change-the-text-of
    (unless (problem-string-of-first-reason-for-bad-parse? current-edit-state)
      (setf (problem-string-of-first-reason-for-bad-parse? current-edit-state)
	    (copy-text-string problem-string))
      (setf (line-index-of-first-reason-for-bad-parse? current-edit-state)
	    line-index?)
      (setf (character-index-of-first-reason-for-bad-parse? current-edit-state)
	    character-index?))
    (display-editor-notification
      (if edit-workspace-hidden?
	  "This has been revealed because of a parsing problem: ~A"
	  "~A")
      problem-string)
    (if (and edit-workspace-hidden?
	     (not keep-edit-workspace-hidden-no-matter-what?))
	(put-up-edit-workspace			; reveal hidden edit workspace
	  current-edit-workspace current-workstation))))











;;;; Escape Contexts


;;; This context is entered when the user types Alt-i while in the editor. The path
;;; to this point is from the `insert-accented-or-special-or-coded-character' ui-command,
;;; which just calls `handle-insertion-of-symbol' with the event that triggered it.
;;; (i.e. the Alt+i keystroke). There we check whether we are already in a special
;;; event context, in which case nothing is done. This avoids recursively invoking
;;; Alt+i once one is already in that context, which wouldn't make any sense.
;;; (Note that it also makes it impossible to invoke incremental search within these
;;; escape contexts, which is also something that probably doesn't make any sense.)
;;;
;;; The other case in `handle-insertion-of-symbol' is a call to enter-escape-context
;;; with the argument 'insertion-of-symbol. `Enter-escape-context' is just a call to
;;; enter-editing-context. It sets up the size and location of the new text-box (editor
;;; window) and supplies nils to most of the other arguments as we are not actually
;;; editing anything her.
;;;
;;; The argument (insertion-of-symbol) becomes the value of the special-entry-context?
;;; field of the new editing-context and it is dispatched off of to determine the value
;;; of the field function-to-call-on-changed-edit-box-text? which is where all the action
;;; is. That function runs as the last action after all the work has been done to
;;; handle the keyboard event when the focus is on this text box, and enter the corresponding
;;; character. See change-edit-box, In the case of having gotten into the special editing
;;; context via Alt+i this function is check-insertion-of-symbol-entry-text.(Compare the
;;; path for Alt+s, incremental search, which is the same sort of operation.)


(defun enter-escape-context (special-entry-context &optional dont-have-riding-image-plane?)
  (enter-editing-context 
    nil  ;; frame?
    nil  ;; slot-denotation
    
          ;; &optional
    nil  ;; initial-text-or-edit-box?
    nil  ;; edit-workspace-hidden?
    nil  ;; edit-box-format-or-format-name?
    nil  ;; width-for-cell?
    nil  ;; cursor-line-index?
    nil  ;; cursor-character-index?
    
    (unless dont-have-riding-image-plane?
      (find-image-plane-for-workspace-in-pane
	current-edit-workspace current-workstation-detail-pane))
    ;; here: riding image plane; aka:
    ;;   specific-image-plane-on-which-to-edit-in-place?
    
    (edit-box current-edit-state)
         ;; specific-text-box-or-table-on-which-to-edit-in-place?
    
    (+w (left-edge-of-block (edit-cursor current-edit-state)) -8)  ; KLUDGE!
         ;; left-edge-of-cell-in-table-on-which-to-edit-in-place?
    (+w (top-edge-of-block (edit-cursor current-edit-state)) 14)  ; to center below cursor
         ;; top-edge-of-cell-in-table-on-which-to-edit-in-place?
    (+w (right-edge-of-block (edit-cursor current-edit-state)) -8)
         ;; right-edge-of-cell-in-table-on-which-to-edit-in-place?
    (+w (bottom-edge-of-block (edit-cursor current-edit-state)) 14)
         ;; bottom-edge-of-cell-in-table-on-which-to-edit-in-place?
    
    nil  ;; type-of-slot?
    special-entry-context   ;; special-entry-context?
    (case special-entry-context   ;; function-to-call-on-changed-edit-box-text?
      (kanji-code-entry
       (if (eq (current-language) 'korean)
	   'check-hangul-code-entry-text	; Only Korean path in non-development
	   'check-kanji-code-entry-text))
      (hangul-code-entry			; Alternative Korean path for development-only
       'check-hangul-code-entry-text)
      (cyrillic-code-entry
       'check-cyrillic-code-entry-text)
      
      ;; Later, react to every change in the text for incremental search. (MHD/DDM 10/9/96)
      (search-for-text-in-editor
       'search-forward-incrementally-for-text-in-editor)
      
      (insertion-of-symbol
       'check-insertion-of-symbol-entry-text)
      (t 'check-special-character-entry-text))

    t  ;;  do-not-have-edit-option-buttons?

    ;; Additional optionals:
    ;;  do-not-have-edit-menus?
    ;;  slot-component-name?
    ;;  slot-component-indicator?
    )
  (let ((characters-workspace?
	  (get-instance-with-name-if-any
	    'workspace
	    (case special-entry-context
	      (kanji-code-entry
	       'kanji-characters)
	      (hangul-code-entry
	       'hangul-characters)
	      (t 'special-characters)))))
    (cond
      (characters-workspace?
       (let* ((image-plane?
		(find-image-plane-for-workspace-in-pane
		  characters-workspace? current-workstation-detail-pane))
	      (special-entry-workspace
		(edit-workspace			; NOT current-edit-workspace
		  specific-structure-for-current-workstation-context))
	      (image-plane-for-special-special-entry-workspace
		(find-image-plane-for-workspace-in-pane
		  special-entry-workspace current-workstation-detail-pane)))
	 (cond
	   ;; to disallow > 1 image per workspace:
;	   (image-plane?
;	    (transform-image
;	      image-plane? nil
;	      nil nil nil nil
;	      (left-edge-of-block characters-workspace?)
;	      (top-edge-of-block characters-workspace?)
;	      (right-edge-of-image-in-window
;		image-plane-for-special-special-entry-workspace)
;	      (bottom-edge-of-image-in-window
;		image-plane-for-special-special-entry-workspace)))
	   (t
	    (setq image-plane?
		  (new-get-available-image-plane
		    current-workstation-detail-pane
		    (lookup-frame-description-reference-of-frame-style
		      'default-workspace-frame-style
		      'default-workspace-frame-style)
		    'below
		    image-plane-for-special-special-entry-workspace))
;		  (get-available-image-plane-below-another
;		    current-workstation-detail-pane
;		    image-plane-for-special-special-entry-workspace
;		    (lookup-frame-description-reference-of-frame-style
;		      'default-workspace-frame-style
;		      'default-workspace-frame-style)))
	    (setf (workstation-context-return-information
		    current-workstation-context)
		  image-plane?)
	    (setf (workstation-context-return-information-reclaimer?
		    current-workstation-context)
		  'delete-image-plane)
	    (transform-image
	      image-plane? characters-workspace?
	      (get-default-image-x-scale image-plane?)
	      (get-default-image-y-scale image-plane?)
	      nil nil
	      (left-edge-of-block characters-workspace?)
	      (top-edge-of-block characters-workspace?)
	      (right-edge-of-image-in-window
		image-plane-for-special-special-entry-workspace)
	      (bottom-edge-of-image-in-window
		image-plane-for-special-special-entry-workspace)))))))))




;;; Any of the following three `check...' functions can be called from the Alt+i
;;; dispatch function `check-insertion-of-symbol-entry-text'. The hangul and
;;; cyrillic functions are just parameterizations to `check-kanji-code-entry-text',
;;; which also takes the parameter unicode, supplied as a default with the
;;; current-language is not one of these special three. The only thing that
;;; happens down this path is the interpretation of hexidecimal digits as
;;; character codes.


;;; Check-hangul-code-entry-text ... called as the input checking filter during
;;; Hangul code input (invoked by typing \ when the current language is KOREAN
;;; or, in development systems, by typing control-\ at any time). ...

(defun check-hangul-code-entry-text (text-being-edited &optional special-case?)
  (check-kanji-code-entry-text text-being-edited special-case? 'hangul))


(defun check-cyrillic-code-entry-text (text-being-edited &optional special-case?)
  (check-kanji-code-entry-text text-being-edited special-case? 'cyrillic))



(defun check-kanji-code-entry-text
    (text-being-edited
      &optional special-case? other-script-case?)
  (multiple-value-bind (text-line line-length
				  lost-space-at-end-of-line next-text-tail?)
      (get-next-text-line text-being-edited)
    (let* ((charset-name
	     (case other-script-case?
	       (hangul "Hangul (KS C 5601)")
	       (cyrillic "Cyrillic (ISO 8859-5)")
	       (unicode "Unicode 2.0")
	       (t "Kanji (JIS)")))
	   (code-digit-length
	     (case other-script-case?
	       (cyrillic 2)
	       (t 4)))
	   (force-hexadecimal?
	     (if (>f line-length 0)
		 (let ((first-char (charw text-line 0)))
		   (or (char=w first-char #.%\x)
		       (char=w first-char #.%\X)))))
	   (effective-line-length
	     (if force-hexadecimal?
		 (-f line-length 1) line-length))
	   (start-index
	     (if force-hexadecimal? 1 0)))
      
      (cond
	((eq special-case? 'rubout-on-blank-text)
	 (return-from-current-workstation-context
	   type-of-current-workstation-context))	
	((or special-case?			; later, special notification?
	     next-text-tail?
	     (not (eql lost-space-at-end-of-line 0))
	     (>f effective-line-length code-digit-length)
	     (not (loop for i from start-index below line-length
			always (digit-char-pw (charw text-line i) 16))))
	 (display-editor-notification "Please enter a ~d-digit ~a hex code"
	   code-digit-length charset-name)
	 t)
	((=f code-digit-length effective-line-length)
	 (loop with kanji-code = 0
	       for i from start-index below line-length
	       as hex-digit-value = (digit-char-pw (charw text-line i) 16)
	       do (setq kanji-code
			(+f (*f 16 kanji-code)
;			    (if (if force-hexadecimal?
;				    (or (=f i 1) (=f i 3))
;				    (or (=f i 0) (=f i 2)))  ; mask top bit of 1st and 3rd char
;				(logandf hex-digit-value #x7f)
;				hex-digit-value)))
			;; I can't fathom what purpose the masking above served except
			;; perhaps to force the values to conform to the jis/kuc range,
			;; and since we've now extended this routine to process Unicodes
			;; (which have no such restrictions) I've removed it (ddm 8/29/97)
			    hex-digit-value))
	       finally

		 (case other-script-case?
		   (hangul
		    (setq kanji-code (ksc-to-gensym-ksc kanji-code)))
		   (cyrillic
		    (setq kanji-code (iso-8859-5-to-gensym-cyrillic kanji-code))))
	       
		 (cond
		   ((and (if (eq other-script-case? 'unicode)
			     t
			     (not (=f kanji-code 0))) ;; code 0 is blob in jis
			 (case other-script-case?
			   (hangul (legal-gensym-ksc-character-code-p kanji-code))
			   (cyrillic (legal-gensym-cyrillic-character-p kanji-code))
			   (unicode t) ;; accept any four digit hex number
			   (t (legal-gensym-jis-character-code-p kanji-code))))
		    (return-from-current-workstation-context
		      type-of-current-workstation-context)
		    (in-editing-context (specific-structure-for-current-workstation-context)
		      (when (valid-block-in-workstation-context-p
			      (edit-workspace current-edit-state)
			      current-edit-state)
			(let* ((han-interpretation-mode	; special, may be used for mapping
				(case other-script-case?
				  (hangul 'korean)
				  (t 'japanese)))
			       (text-string-to-insert
				 (tformat-text-string
				   "~c"	; is there a better abstraction?
				  (code-wide-character
				    (case other-script-case?
				      (unicode kanji-code)
				      (t 
				       (map-gensym-character-code-to-unicode
					 (gensym-character-pair-to-code
					   kanji-code #\\))))))))
			  (insert-text-string-at-cursor
			    text-string-to-insert nil nil)
			  (reclaim-text-string
			    text-string-to-insert))))
		    (return t))
		   (t
		    (display-editor-notification
			"This is an invalid ~a code" charset-name)
		    t))))
	((<f code-digit-length effective-line-length)
	 (display-editor-notification
	     "Too many digits"))
	((>f code-digit-length effective-line-length)
	 ;; This corresponds to the 't' case in the earlier treatment. ddm 8/29/97
	 (erase-any-temporary-information-on-edit-workspace nil t)
	 nil)))))

;; Consider omitting the stripe from notifications.




;;; `Check-insertion-of-symbol-entry-text' is the value of the function-
;;; to-call-on-changed-edit-box-text? field of the editing-context when
;;; we have entered an escape context via Alt+i. It has two cases. First
;;; it looks to see whether the character that the user has just typed
;;; in can be interpreted as indicating that the character just before
;;; the cursor in the parent edit-box should be accented or whether one
;;; of the special characters such as trademark or bullet should be
;;; entered.  If that does not apply, the only other possibility is that
;;; the user is entering a set of hexidecimal digits to be interpreted
;;; as a character, for which it calls check-kanji-code-entry-text
;;; passing in an additional argument based on the current language which
;;; will dictate which code the number is interpreted in.
;;;
;;; The `special-case?' optional argument appears to have only one
;;; purpose. If it has had others they have been lost in antiquity.
;;; It can get the value rubout-on-blank-text when it is called from
;;; `delete-backward-character'.  The additional 't' argument in the
;;; call to check-special-character-entry-text signals that the call
;;; is for the general-entry-of-symbol-case. It had also been include
;;; in the call to check-kanji-code-entry-text, but there it was
;;; blocking useful editor-notifications so I took it out. It seems
;;; reasonable to keep it in the first call (where also blocks notifications)
;;; since in this case we want the first option to be able to fall
;;; through to the second. (ddm 8/29/97)

(defun check-insertion-of-symbol-entry-text
    (text-being-edited &optional special-case?)
  (or (check-special-character-entry-text
	text-being-edited special-case? t) ; 't' for general-entry-of-symbol-case
      (check-kanji-code-entry-text
	text-being-edited special-case?
	(case (current-language)
	  (korean 'hangul)
	  (russian 'cyrillic)
	  (japanese 'kanji)
	  (otherwise 'unicode)))))




;;; Generate-code-for-editor-special-character-alist is a development-only
;;; helper function that was used to generate `editor-special-character-alist',
;;; the form that follows, q.v.  This is an a-list available in production.  Its
;;; elements are of the form
;;;
;;;   (presentation-character
;;;       lowercase-equivalent?
;;;       corresponding-base-character?
;;;       character-to-type-into-editor-or-list-thereof?
;;;       #+development adobe-name)
;;;

;; This is intended to partially replace the venerable special-character-alist.
;; (MHD 9/19/96)

#+development
(defun generate-code-for-editor-special-character-alist ()
  (loop for (tilde nil lowercase? base typed-chars adobe)
	    in special-character-alist
	as gensym-code
	   = (gensym-character-pair-to-code tilde #\~)
	as wide-char
	   = (code-wide-character
	       (map-gensym-character-code-to-unicode gensym-code))
	as lowercase-code?
	   = (if lowercase?
		 (gensym-character-pair-to-code lowercase? #\~))
	as wide-lowercase-char
	   = (if lowercase-code?
		 (code-wide-character
		   (map-gensym-character-code-to-unicode lowercase-code?)))
	when typed-chars
	  collect
	  `(,wide-char
	      ,wide-lowercase-char
	      ,(if base (character-to-wide-character base))
	      ,(if (listp typed-chars)
		   (loop for c in typed-chars
			 collect (character-to-wide-character c))
		   (character-to-wide-character typed-chars))
	      ,adobe)
	  into alist
	finally
	  (format t "~%(defparameter editor-special-character-alist '(")
	
	  (loop with lisp-highest-printable-character-code
		  = 127 ; special; use 255 if we want Latin-1 in our source code
		for (a b c d e) in alist
		do (terpri)
		   (princ "  (")
		   (print-wide-character a)
		   (princ " ")
		   (if b (print-wide-character b) (princ nil))
		   (format t " ~18T")
		   (if c (print-wide-character c) (princ nil))
		   (format t " ~28T")
		   (if (listp d)
		       (loop initially 
			       (princ "(")
			     for x in d
			     do (print-wide-character x)
				(princ " ")
			     finally 
			       (princ ")"))
		       (if d (print-wide-character d) (princ nil)))
		   (format t " ~50T#+development ~s" e)
		   (princ ")"))
;alt:
;		do (format t "~%    (~s ~s ~s ~s)" a b c d)
	  (format t "~%   ))")))



;; Code generated by the above form (apart from hand-edited exceptions noted
;; below):
(defparameter editor-special-character-alist '(
  ;; presentation, lowercase?, base?, type-in(s)?, adobe or other descriptive name
  (#u00E4 NIL     #.%\a     (#.%\: #.%\" )        #+development |adieresis|)
  (#u00C4 #u00E4  #.%\A     (#.%\: #.%\" )        #+development |Adieresis|)
  (#u00E1 NIL     #.%\a     #.%\'                 #+development |aacute|)
  (#u00C1 #u00E1  #.%\A     #.%\'                 #+development |Aacute|)
  (#u00E7 NIL     #.%\c     #.%\,                 #+development |ccedilla|)
  (#u00C7 #u00E7  #.%\C     #.%\,                 #+development |Ccedilla|)
  (#u00E2 NIL     #.%\a     #.%\^                 #+development |acircumflex|)
  (#u00C2 #u00E2  #.%\A     #.%\^                 #+development |Acircumflex|)
  (#u00E9 NIL     #.%\e     #.%\'                 #+development |eacute|)
  (#u00C9 #u00E9  #.%\E     #.%\'                 #+development |Eacute|)
  (#u00EA NIL     #.%\e     #.%\^                 #+development |ecircumflex|)
  (#u00CA #u00EA  #.%\E     #.%\^                 #+development |Ecircumflex|)
  (#u00E8 NIL     #.%\e     #.%\`                 #+development |egrave|)
  (#u00C8 #u00E8  #.%\E     #.%\`                 #+development |Egrave|)
  (#u00EC NIL     #.%\i     #.%\`                 #+development |igrave|)
  (#u00CC #u00EC  #.%\I     #.%\`                 #+development |Igrave|)
  (#u00ED NIL     #.%\i     #.%\'                 #+development |iacute|)
  (#u00CD #u00ED  #.%\I     #.%\'                 #+development |Iacute|)
  (#u00EE NIL     #.%\i     #.%\^                 #+development |icircumflex|)
  (#u00CE #u00EE  #.%\I     #.%\^                 #+development |Icircumflex|)
  (#u00E0 NIL     #.%\a     #.%\`                 #+development |agrave|)
  (#u00C0 #u00E0  #.%\A     #.%\`                 #+development |Agrave|)
  (#u00F1 NIL     #.%\n     #.%\~                 #+development |ntilde|)
  (#u00D1 #u00F1  #.%\N     #.%\~                 #+development |Ntilde|)
  (#u00F6 NIL     #.%\o     (#.%\: #.%\" )        #+development |odieresis|)
  (#u00D6 #u00F6  #.%\O     (#.%\: #.%\" )        #+development |Odieresis|)
  (#u00F3 NIL     #.%\o     #.%\'                 #+development |oacute|)
  (#u00D3 #u00F3  #.%\O     #.%\'                 #+development |Oacute|)
  (#u00F4 NIL     #.%\o     #.%\^                 #+development |ocircumflex|)
  (#u00D4 #u00F4  #.%\O     #.%\^                 #+development |Ocircumflex|)

  (#u00E5 NIL     #.%\a     (#.%\o #.%\O #.%0 )   #+development |aring|)
  (#u00C5 #u00E5  #.%\A     (#.%\o #.%\O #.%0 )   #+development |Aring|)
  (#u00DF NIL     NIL       #.%\s                 #+development |germandbls|)

  (#u00F8 NIL     #.%\o     #.%\/                 #+development |oslash|)
  (#u00D8 #u00F8  #.%\O     #.%\/                 #+development |Oslash|)

  (#u00FC NIL     #.%\u     (#.%\: #.%\" )        #+development |udieresis|)
  (#u00DC #u00FC  #.%\U     (#.%\: #.%\" )        #+development |Udieresis|)
  (#u00FA NIL     #.%\u     #.%\'                 #+development |uacute|)
  (#u00DA #u00FA  #.%\U     #.%\'                 #+development |Uacute|)
  (#u0153 NIL     #.%\o     #.%\e                 #+development |oe|)
  (#u0152 #u0153  #.%\O     #.%\e                 #+development OE)
  (#u00E6 NIL     #.%\a     #.%\e                 #+development |ae|)
  (#u00C6 #u00E6  #.%\A     #.%\e                 #+development AE)
  (#u00F2 NIL     #.%\o     #.%\`                 #+development |ograve|)
  (#u00D2 #u00F2  #.%\O     #.%\`                 #+development |Ograve|)
  (#u00F9 NIL     #.%\u     #.%\`                 #+development |ugrave|)
  (#u00D9 #u00F9  #.%\U     #.%\`                 #+development |Ugrave|)
  (#u00EB NIL     #.%\e     (#.%\: #.%\" )        #+development |edieresis|)
  (#u00CB #u00EB  #.%\E     (#.%\: #.%\" )        #+development |Edieresis|)
  (#u00EF NIL     #.%\i     (#.%\: #.%\" )        #+development |idieresis|)
  (#u00CF #u00EF  #.%\I     (#.%\: #.%\" )        #+development |Idieresis|)
  (#u00E3 NIL     #.%\a     #.%\~                 #+development |atilde|)
  (#u00C3 #u00E3  #.%\A     #.%\~                 #+development |Atilde|)
  (#u00F5 NIL     #.%\o     #.%\~                 #+development |otilde|)
  (#u00D5 #u00F5  #.%\O     #.%\~                 #+development |Otilde|)
  (#u00FB NIL     #.%\u     #.%\^                 #+development |ucircumflex|)
  (#u00DB #u00FB  #.%\U     #.%\^                 #+development |Ucircumflex|)
  (#u00A2 NIL     #.%\c     #.%\/                 #+development |cent|)
  (#u00A2 NIL     #.%\C     #.%\/                 #+development |cent|)
  (#u00A9 NIL     NIL       #.%\c                 #+development |copyright|)
  (#u2122 NIL     NIL       #.%\t                 #+development |trademark|)
  (#u00AE NIL     NIL       #.%\r                 #+development |registered|)
  (#u00BF NIL     NIL       #.%\?                 #+development |questiondown|)
  (#u00A1 NIL     NIL       #.%\!                 #+development |exclamdown|)
  (#u00AB NIL     NIL       #.%\<                 #+development |guillemotleft|)
  (#u00BB NIL     NIL       #.%\>                 #+development |guillemotright|)
  (#u00A3 NIL     NIL       #.%\l                 #+development |sterling|)
  (#u00A5 NIL     NIL       #.%\y                 #+development |yen|)
  (#u0192 NIL     NIL       #.%\f                 #+development |florin|)
  (#u2022 NIL     NIL       #.%\*                 #+development |bullet|)

  ;; HAND-EDITS for Polish characters (GENSYMCID-1042, binghe 5/22/2013)
  (#u0105 NIL     #.%\a     #.%\(                 #+development |aogonek|)
  (#u0104 #u0105  #.%\A     #.%\(                 #+development |Aogonek|)
  (#u0107 NIL     #.%\c     #.%\'                 #+development |cacute|)
  (#u0106 #u0107  #.%\C     #.%\'                 #+development |Cacute|)
  (#u0119 NIL     #.%\e     #.%\(                 #+development |eogonek|)
  (#u0118 #u0119  #.%\E     #.%\(                 #+development |Eogonek|)
  (#u0144 NIL     #.%\n     #.%\'                 #+development |nacute|)
  (#u0143 #u0144  #.%\N     #.%\'                 #+development |Nacute|)
  (#u015B NIL     #.%\s     #.%\'                 #+development |sacute|)
  (#u015A #u015B  #.%\S     #.%\'                 #+development |Sacute|)
  (#u0180 NIL     #.%\z     #.%\'                 #+development |zacute|)
  (#u0179 #u0180  #.%\Z     #.%\'                 #+development |Zacute|)
  (#u0182 NIL     #.%\z     #.%\.                 #+development |zdotabove|)
  (#u0181 #u0182  #.%\Z     #.%\.                 #+development |Zdotabove|)

  ;; HAND-EDITS for L Slash! (MHD 7/31/98)					       
  (#u0142 NIL     #.%\l     #.%\/                 #+development |lslash|)
  (#u0141 #u0142  #.%\L     #.%\/                 #+development |Lslash|)

  ;; HAND-EDITS for U and O with Double-Acute! (MHD 7/31/98)
  (#u0151 NIL     #.%\o     #.%\=                 #+development |odoubleacute|)
  (#u0150 #u0151  #.%\O     #.%\=                 #+development |Odoubleacute|)
  (#u0171 NIL     #.%\u     #.%\=                 #+development |udoubleacute|)
  (#u0170 #u0171  #.%\U     #.%\=                 #+development |Udoubleacute|)

  ;; HAND-EDITS for the Euro Sign, Tab, etc.! (MHD 10/14/99)

  ;; Don't use Korean character now, since it's not in any font
  ;; burned into the executable.
;  (#u20A9 nil     nil       #.%\W #+development |won|)
  ;; Only in up-to-date Telewindows/G2:   (MHD 10/14/99)     
  (#u20AA nil     #.%\s     #.%\/ #+development |sheqelhebrew|)
  (#u20A3 nil     #.%\f     #.%\/ #+development |franc|)
  (#u20AA nil     #.%\S     #.%\/ #+development |sheqelhebrew|)
  (#u20A3 nil     #.%\F     #.%\/ #+development |franc|)

  ;; More Turkish characters added for 6.0 Alpha Rev. 2:  (MHD 1/12/99)
  (#u015F nil     #.%\s     #.%\,                 #+development |scedilla|)
  (#u015E #u015F  #.%\S     #.%\,                 #+development |Scedilla|)
  (#u011F nil     #.%\g     (#.%\u #.%\U)         #+development |gbreve|)
  (#u011E #u015F  #.%\G     (#.%\u #.%\U)         #+development |Gbreve|)

  ;; Alt+I i/I functions as a dot toggle switch::
  (#u0131 nil     #.%\i     (#.%\i #.%\I)         #+development |dotlessi|)
  (#u0130 #u0130  #.%\I     (#.%\i #.%\I)         #+development |Idotaccent|)

  ;; Only in up-to-date Telewindows/G2. (MHD 10/14/99)
  (#u20AC nil     nil       #.%\$ #+development |euro|)
  (#.%tab NIL     nil       #.%tab #+development |controlHT|)

  ;; not now: not formatted/rendered perfectly yet:
;  (#.%no-break-space
;          nil     nil       #.%space  #+development |nonbreakingspace|)
   ))

;; Note: the help tables put up (see RUN) should be made not to document
;; both letter cases for C + /, F + /, and S + /.

;; I consulted <http://fonts.apple.com/DataFiles/PostScriptNames.txt>
;; to get the new Adobe names. (MHD 10/20/99)



(defun map-editor-special-character-type-in
    (typed-character previous-base-character?)
  (loop for (presentation-character lowercase? base? type-ins)
	    in editor-special-character-alist
	when (and (or previous-base-character?
		      (null base?))
		  (if (listp type-ins)
		      (wide-character-member typed-character type-ins)
		      (char=w type-ins typed-character))
		  (or (null base?)
		      (char=w base? previous-base-character?)))
	  return (values presentation-character base?)))


(defun map-composed-character-to-base-character-for-editor (character)
  (or (third (wide-character-assoc
	       character
	       editor-special-character-alist))
      character))
  
(defun-allowing-unwind check-special-character-entry-text
    (text-being-edited
      &optional special-case?
      general-insertion-of-symbol-case?) ; true => don't check exclusively for this entry
  (protected-let*
      ((text-line
	 (convert-text-to-text-string text-being-edited)
	 (reclaim-text-string text-line))
       (line-length (text-string-length text-line))
       (superior-edit-state
	 (specific-structure-for-workstation-context
	   (second (workstation-context-stack current-workstation)))))
    (cond
      ((eq special-case? 'rubout-on-blank-text)
       nil)				; nil => not handled
      ((or special-case?			; later, special notification?
	   (>f line-length 1))
       (unless general-insertion-of-symbol-case?
	 (display-editor-notification "Please enter one character")
	 t))
      ((>f line-length 0)
       (let* ((typed-character	; char typed after after Alt-I
		(char-downcasew (charw text-line (-f line-length 1))))
	      (previous-base-character? nil))
	 (multiple-value-bind
	     (previous-line-index
	       previous-character-index
	       previous-text-tail
	       previous-character?)
	     (find-previous-character-if-any
	       (cursor-line-index superior-edit-state)
	       (cursor-character-index superior-edit-state)
	       (text-tail-for-cursor superior-edit-state)
	       (text-being-edited superior-edit-state))
	   (when previous-character?
	     (setq previous-base-character?
		   (map-composed-character-to-base-character-for-editor
		     previous-character?)))
	   (multiple-value-bind
	       (presentation-character? base?)
	       (map-editor-special-character-type-in
		 typed-character previous-base-character?)
	     ;; This makes alt-i space turn any accented character into a base character:
	     (when (and (null presentation-character?)
			previous-base-character?			  
			(char=w typed-character #.%space)) ; equiv.
	       (setq presentation-character?
		     previous-base-character?)
	       (setq base?
		     previous-base-character?))
	     (cond
	       (presentation-character?
		(cond
		  ((null base?)
		   (return-from-current-workstation-context
		     type-of-current-workstation-context)
		   (insert-character-at-cursor-from-outside
		     presentation-character?)
		   t)
		  (previous-base-character?
		   (return-from-current-workstation-context
		     type-of-current-workstation-context)
		   (in-editing-context
		       (specific-structure-for-current-workstation-context)
		     (twith-output-to-then-use-of-wide-string
		       
		       (twrite-char presentation-character?)
		       (setf (fill-pointerw current-wide-string) 1)
		       
		       (change-edit-box
			 previous-text-tail
			 previous-line-index previous-character-index
			 (cursor-line-index current-edit-state)
			 (cursor-character-index current-edit-state)
			 current-wide-string)))
		   t)))
	       (t
		(unless general-insertion-of-symbol-case?
		  (display-editor-notification
		      (if previous-base-character?
			  "Previous character (~c) cannot take this accent"
			  "This has no corresponding special character")
		    previous-base-character?))
		nil))))))
      (t (erase-any-temporary-information-on-edit-workspace nil t)
	   nil))))

;; Consider having ~<space> simply unaccent a character, when applicable.




;;;; Searching in the editor


(defun search-forward-incrementally-for-text-in-editor
    (text-being-edited &optional special-case?)
  (search-incrementally-for-text-in-editor
    text-being-edited special-case? :forward))

(defun search-backward-incrementally-for-text-in-editor
    (text-being-edited &optional special-case?)
  (search-incrementally-for-text-in-editor
    text-being-edited special-case? :backward))


(defun-allowing-unwind search-incrementally-for-text-in-editor
    (text-being-edited special-case? direction)
  (protected-let*
      ((text-line
	 (convert-text-to-text-string text-being-edited)
	 (reclaim-text-string text-line))
       (line-length (text-string-length text-line))
       (superior-edit-state
	 (specific-structure-for-workstation-context
	   (second (workstation-context-stack current-workstation)))))
    (cond
      ((eq special-case? 'end-editing)
       ;; later: when exiting, _select__++ the found text; also, save it away
       ;; for the next search!

       ;; First, get any information out of the subcontext we're in.  (Nothing
       ;; needed for now, but later, who knows?)

       ;; Next, pop the subcontext off the workstation context stack,
       ;; returning the region that covers the instance we've found
       (return-from-current-workstation-context
	 type-of-current-workstation-context
	 (first-text-region-in-edit-state superior-edit-state)))
      
      ((eq special-case? 'rubout-on-blank-text)
       (cond
	 ((=f line-length 0)
	  (return-from-current-workstation-context
	    type-of-current-workstation-context))
	 (t
	  (move-or-delete-from-cursor t t nil)
	  (erase-any-temporary-information-on-edit-workspace nil t))))
      
      ((>f line-length 0)
       (erase-any-temporary-information-on-edit-workspace nil t)
       (find-search-string-in-superior-editor
	 superior-edit-state nil direction)
       (shrink-wrap-workspace current-edit-workspace))

      (t
       (erase-any-temporary-information-on-edit-workspace nil t)
       ;; sledge hammer -- just ok for now!
       (delete-any-text-regions
	 (edit-box superior-edit-state)
	 nil nil nil nil
	 (kfep-conversion-text-region? superior-edit-state)) ; see note 
       nil))))

;; Note: it might be cleaner to have a special-purpose function, e.g.,
;; delete-search-text-regions, for this task.  Also, we should move away from
;; having to be heuristic about finding the right text region.  We now use text
;; regions for searching, marking, and the KFEP.  We've had to fix bugs more
;; than once because the different facilities were stomping on each other's
;; region.  They could be separate classes as a means of distinguishing them.
;; They could also be stored in a slot in the edit state, although that entails
;; some additional code to maintain and update such a slot.  (MHD/DDM 6/23/97)


 

(defun find-search-string-in-superior-editor
    (&optional superior-edit-state? ongoing-region? direction? reversal-of-direction?)
  (let* ((superior-edit-state
	   (or superior-edit-state?
	       (specific-structure-for-workstation-context
		 (second (workstation-context-stack current-workstation)))))	 
	 (direction (or direction? :forward))	 
	 (text-string
	   (convert-text-to-text-string
	     (text-being-edited current-edit-state)))
	 (previous-region?
	   (or ongoing-region?
	       (first-text-region-in-edit-state superior-edit-state))) ; see Note 3
	 (extension/contraction?     ; see Note 1
	   (cond (ongoing-region?
		  (not (=f (lengthw text-string)
			   (length-of-text-in-region ongoing-region?))))
		 (reversal-of-direction? ; see Note 5
		  nil )
		 (t  ;; start of the search
		  t )))
	 (line-index
	   (if ongoing-region?
	       (line-index-for-free-end-of-text-region ongoing-region?)	; see Note 2
	       (or (line-index-of-search-anchor? superior-edit-state)
		   (cursor-line-index superior-edit-state))))
	 (character-index
	   (if ongoing-region?
	       (character-index-for-free-end-of-text-region ongoing-region?)
	       (or (character-index-of-search-anchor? superior-edit-state)
		   (cursor-character-index superior-edit-state)))))
    

      (multiple-value-bind (start-line-index? start-character-index
                            end-line-index end-character-index)
	  (case direction
	    (:forward (find-string-in-text
			text-string (text-being-edited superior-edit-state)
			nil nil nil nil nil nil line-index character-index))
	    (:backward (find-string-in-text-prior-to-bounds
			 text-string (text-being-edited superior-edit-state)
			 ;; don't look past (rightward) of these indicies
			 line-index character-index)))
	(reclaim-text-string text-string)
	(cond
	  (start-line-index?
	   (cond
	     (extension/contraction?
	      (if previous-region?
		  ;; check whether its fixed end changed
		  (if (and (=f line-index start-line-index?)
			   (=f character-index start-character-index))
		      ;; we're extending/contracting this region, so all we
		      ;; have to do is move the free end.
		      (update-text-region
			previous-region?
			end-line-index end-character-index)
		      ;; The fixed end of the established region no longer corresponds
		      ;; to the fixed end of the search, so since we haven't got a
		      ;; form of 'update-region' that moves both ends because the
		      ;; purpose of that facility is mouse-driven selection, we'll
		      ;; have to trash that region and build a new one as in the
		      ;; Next/Previous case.   Collapse these into a subroutine so that
		      ;; if/when we get the right kind of region manipulation we can
		      ;; do this right !
		      (progn
			(delete-frame previous-region?)
			(unless (eq direction :forward) ; reverse pairs for reverse search
			  (rotatef start-line-index? end-line-index)
			  (rotatef start-character-index end-character-index))
			(make-text-region
			  (edit-box superior-edit-state)
			  nil 
			  start-line-index?
			  start-character-index
			  end-line-index
			  end-character-index)))
		      
		  ;; we've just started
		  (make-text-region
		    (edit-box superior-edit-state)
		    nil 
		    start-line-index?
		    start-character-index
		    end-line-index
		    end-character-index)))

	     (t ;; we've moved on the the Next/Previous instance
	      (when previous-region?
		(delete-frame previous-region?))
	      (unless (eq direction :forward) ; reverse pairs for reverse search
		(rotatef start-line-index? end-line-index)
		(rotatef start-character-index end-character-index))
	      (make-text-region
		(edit-box superior-edit-state)
		nil 
		start-line-index?
		start-character-index
		end-line-index
		end-character-index)))
	   ;; save a record of the successful search
	   (when ongoing-region?
	     (setf (line-index-of-search-anchor? superior-edit-state) start-line-index?)
	     (setf (character-index-of-search-anchor? superior-edit-state)
		   start-character-index)))
	  (previous-region?
	   ;; Next or Previous search on the current string failed to match.
	   ;; Change the color of the region as an indicator to the user. (see Note 4)
	   ;(change-color-of-text-region previous-region? 'red)
	   ; 11/15/96 this color doesn't look good because given the way regions
	   ; are done, it is XOR'd into the background color without appreciating
	   ; the effect on the color of the text, and the result is ugly.
	   (display-editor-notification "no match"))
	  (t
	   ;; if there is no previous region and the search fails, then this is
	   ;; the case of the first character typed in not matching anywhere.
	   (display-editor-notification "no match")))
	;; Assuming there's been something selected for us to look at,
	;; scroll Free end into view, as necessary (on all image planes
	;; for now, since in practice there is always just one).
	(when start-line-index?
	  (loop for (image-plane . frame-transform)
		    in (frame-transforms-of-block
			 (edit-box superior-edit-state))
		do (scroll-text-into-view
		     frame-transform
		     end-line-index end-character-index))))))

;; Note 1: We're usually called when there's been a new character added or
;; deleted from the search type-in edit-window. If this is so then the length of
;; that string will be different from the length presently in the region, and we
;; should continue the search as an extension (contraction) of the ongoing
;; region. Otherwise, if the lengths are the same, then we've been called to
;; locate the Next (Previous) instance of the text string, and should
;; consequently start looking after (before) the ongoing region.)

;; Note 2: By searching from the free end of the ongoing region, we don't
;; handle a case of, for example, searching for the next occurance of
;; abab in the string ababab when our ongoing region is over the initial
;; match.  Note that Emacs I-search works this way, too.

;; Note 3: trusting that any region retrieved will be the one that's tracking
;; the search implies that we've expunged any earlier regions that were present
;; at the time that we initiated the search process <=== do it! ///////

;; Note 4. As it stands, we do not change the color back once the user corrects
;; their typing and the search string again matches a character sequence in the
;; editor. We get this behavior by chance, since when the correction happens
;; we hit the case in the conditional that corresponds to moving the region
;; as with Next or Previous, and the existing (colored) region is deleted.
;; That is inefficient because it does unnecessary region creation, so consider
;; modifying the conditional to notice this case (probably sufficient just to
;; know it's a contraction).

      
;; Note 5. There are two ways into this function. One when a character has been added
;; or deleted from the search-editor. Here `search-incrementally-for-text-in-editor' is
;; the caller and it will always pass in Nil for the `ongoing-region' argument. The
;; other way in is via `find-next-instance-of-search-string', which is called when
;; and Alt-N or Alt-P is typed, indicating that we are to look for another instance
;; of the current search string. This call has two cases. If we are looking in the
;; same direction as we have been looking, then the currently selected retion will
;; be passed in as the ongoing-region. If we are reversing directions, then to get
;; the search anchored correctly we have to be careful (see note with that function)
;; so the ongoing-region is passed in as Nil but now the fourth argument to the
;; search function gets a value `reversal-of-direction?', allowing us to distinguish
;; this situation from the case of starting the search from scratch.




;;; The reason `first-text-region-in-edit-state' wsa written was to provide
;;; a way to get the region in the superior edit-state that corresponded to
;;; the text selected for the search. It works because there's only (ever been)
;;; one region in that editor when we've done the search, so we're just lucky.
;;;    A better scheme would involve subtyping regions to distinguish regions
;;; created for the purpose of highlighting the hits of the search process
;;; so we could look through all the regions that there might be.

(defun-simple first-text-region-in-edit-state (edit-state)
  (loop for subblock
	    being each subblock of (edit-box edit-state)
	when (and (frame-of-class-p subblock 'text-region) ; ok test for now, mhd
		  (not (eq subblock (kfep-conversion-text-region? edit-state))))
	  do (return subblock)))

;; What module does this really belong in?





(defun find-next-instance-of-search-string (&optional direction?)
  (let* ((direction
	   (or direction?
	       (if (or (null (function-to-call-on-changed-edit-box-text?
			       current-edit-state))
		       (eq (function-to-call-on-changed-edit-box-text?
			     current-edit-state)
			   'search-forward-incrementally-for-text-in-editor))
		   ':forward
		   ':backward)))
	 (superior-edit-state
	   (specific-structure-for-workstation-context
	     (second (workstation-context-stack current-workstation))))
	 (region? (first-text-region-in-edit-state superior-edit-state))
	 (this-is-a-reversal-of-the-ongoing-direction? nil))

    ;; Clear away the 'no match' notification is there is one
    (erase-any-temporary-information-on-edit-workspace nil t)
    
    ;; we know from our caller that we're in a search context, therefore
    ;; we can conclude that if there is a region in the parent edit state
    ;; it was put there by the search routine, and that if there isn't,
    ;; then the search string is empty.
    ;; {{ case: the region is there, but it reflects a failed search }}
    (when region?  ;; note 1
      (unless (case direction
		(:forward (text-region-oriented-forward-p region?))
		(t (text-region-oriented-backward-p region?)))
	;; also make sure that the text region spanning the current instance
	;; of the search string (if there is one) is oriented in the correct
	;; direction so that the reference points in
	;; find-search-string-in-superior-editor will be correct.
	(setq this-is-a-reversal-of-the-ongoing-direction? t)
	(reverse-text-region region?))
      ;; set up the anchor of the search:
      (setf (line-index-of-search-anchor? superior-edit-state)
	    (line-index-for-fixed-end-of-text-region region?))
      (setf (character-index-of-search-anchor? superior-edit-state)
	    (character-index-for-fixed-end-of-text-region region?)))
    (cond (this-is-a-reversal-of-the-ongoing-direction?  ;; note 2
	   (find-search-string-in-superior-editor
	     superior-edit-state nil direction t))
	  ((text-empty-p (text-being-edited current-edit-state)))
	  (t
	   (find-search-string-in-superior-editor
	     superior-edit-state region? direction)))))

;; Note 1: We know from our caller that we're in a search context, therefore
;; we can conclude that if there is a region in the parent edit state
;; it was put there by the search routine, and that if there isn't,
;; then the search string is empty.

;; Note 2: If we pass the region into the search, it will anchor the start
;; of the search to the free end of the region. When we're reversing
;; the direction of the search, then we want it to start from the fixed
;; end of the (now reversed) direction, which has the effect of reselecting
;; the selected region (if there is one) which is what emacs does.




;;; The text position that `find-string-in-text-prior-to-bounds' is passed as its
;;; argument is just beyond the rightmost position in the text where the string
;;; being searched for can end. E.g. if we are searching for "xx" in "xxxxxx"
;;; and the bound is set to (0,5) then the match is "xxXXxx", not "xxxXXx".

(defun find-string-in-text-prior-to-bounds
	(string text stop-line-index stop-character-index
	 &optional (case-sensitive? nil) )

  (let ((length-of-string (lengthw string)))
	
    ;; Establish where to start the search. It has to be the length of
    ;; the search-string to the left of the character bounds, which is
    ;; is only complicated if that moves us onto the prior line or
    ;; beyond the start of the text.
    (multiple-value-bind (character-index-for-search-start
			  line-index-for-search-start)
	(calculate-rightmost-start-position-for-bounded-reverse-search
	  stop-character-index stop-line-index text length-of-string)

      ;; The calculation may have determined that there isn't enough room
      ;; to fit the string in given the bounds, so no point in looking.
      (if (eq character-index-for-search-start 'no-room)
	  nil

  ;; otherwise search for a match
  (loop
    named outer-loop
    ;with length-of-string = (lengthw string)
    with max-index-of-string = (1- length-of-string)
    with first-character-in-string
    with char-index-just-after-first-character-in-string
    with length-of-line-of-text
    with character-to-check
    
    initially
      (multiple-value-setq (first-character-in-string
			    char-index-just-after-first-character-in-string)
	(find-next-character-in-text-line 0 string))
      (if (not case-sensitive?)
	  (setq first-character-in-string
		(char-downcasew first-character-in-string)))

      

    for line-index downfrom line-index-for-search-start
                   above 0

    as text-tail = (find-text-tail-for-line text line-index)
    as line-of-text
       = (loop as text-element = (pop text-tail)
	   do (cond ((text-line-p text-element)
		     (setq length-of-line-of-text
			   (text-line-length text-element))
		     (return text-element))))

    ;;do (format t "~&line being searched = ~a~%" line-of-text)    
    
    do ;; At the current character index, look for a match against
       ;; the first character of the string. If we get one, move into
       ;; a subloop to check for a match against the rest.
    
    ;; Loop through the characters on the line, When we've decremented
    ;; the index to -1, return from the loop to move on to the prior line.
    (loop as character-index
	     = (if (=f line-index stop-line-index)
		   character-index-for-search-start
		   length-of-line-of-text)
	     then (1-f character-index)  ;; go right to left
	      
	  when (not (>= character-index 0))
	    ;; drop out to decrement the line index and get
	    ;; a new line in the next iteration of the outer loop
	    do (loop-finish)

	  do (setq character-to-check
		   (charw line-of-text character-index))
	     (unless case-sensitive?
	       (setq character-to-check (char-downcasew character-to-check)))
	
	  when (char=w character-to-check first-character-in-string)
	    do
	      (if (=f length-of-string 1)
		  (return-from outer-loop
		    (values line-index
			    character-index
			    line-index
			    (+f character-index 1) )))

	      ;; See if the rest of the string matches at this point
	      ;; extending to the right and following it out onto successive
	      ;; lines as needed. 1st copy the outer loop's state onto
	      ;; locals. Then have the loop iterate through the string
	      ;; and iterate through the text at the same
	      (loop with index-of-line-being-checked = line-index
		    with line-of-text-being-checked = line-of-text
		    with length-of-line-being-checked = length-of-line-of-text

		    for i from char-index-just-after-first-character-in-string
			  to length-of-string
		    for index-of-character-being-checked from (1+ character-index)
	      
		;; have we run off this line and need to continue the check
		;; on the next line?
		    when (=f index-of-character-being-checked
			     length-of-line-being-checked)
		      do (setq index-of-line-being-checked (1+ index-of-line-being-checked))
			 (let ((text-tail?
				 (find-text-tail-for-line text index-of-line-being-checked)))
			   ;; this call is sad since we've got our hands on this very
			   ;; cons cell up above. -- yes, use get-next-text-line!
			   (when (null text-tail?)
			     ;; The increment to take us to the next line has gone beyond
			     ;; the end of the text, so return to the character iteration loop.
			     (loop-finish))
			   (setq index-of-character-being-checked 0)
			   (setq line-of-text-being-checked
				 (loop as checking-text-element
					  = (pop text-tail?)
				       when (text-line-p checking-text-element)
					 do (setq length-of-line-being-checked
						  (lengthw checking-text-element))
					    (return checking-text-element))))

		    do (progn
			 #+comment
			 (format t "~&string: ~a = ~a  line: ~a = ~a~%"
				 i (code-char (char-codew (charw string i)))
				 index-of-character-being-checked
				 (code-char (char-codew 
					      (charw line-of-text-being-checked
						     index-of-character-being-checked)))))
			 
		;; If the text stops matching the string, return to the
		;; character iteration loop to try the initial character
		;; match again at the next spot.
		    always (if case-sensitive?
			       (char=w (charw string i)
				       (charw line-of-text-being-checked
					      index-of-character-being-checked))
			       (char-equalw
				 (charw string i)
				 (charw line-of-text-being-checked
					index-of-character-being-checked)))
		    when (=f i max-index-of-string)
		      ;; we've succeeded matching it, so we're completely done
		      ;; and should get out of this function as expeditiously as
		      ;; possible
		      do (return-from outer-loop
			   (values line-index
				   character-index
				   index-of-line-being-checked
				   (+f index-of-character-being-checked 1) )))))))))



(defun calculate-rightmost-start-position-for-bounded-reverse-search
       (stop-character-index stop-line-index text length-of-string)

  (if (> length-of-string stop-character-index)
      ;; not enough room on the current line
      (if (=f 1 stop-line-index)
	  ;; but that was the first line of the text, so indicate failure
	  (values 'no-room nil)
	  ;; otherwise say we have to start on the prior line, and work out
	  ;; what the character index will have to be.
	  (let* ((spill-over (-f length-of-string (1-f stop-character-index)))
		 (prior-text-tail (find-text-tail-for-line text (1-f stop-line-index)))
		 (length-of-prior-line
		   (loop as text-element = (pop prior-text-tail)
			 do (cond ((text-line-p text-element)
				   (return (text-line-length text-element)))))))
	    (values (-f length-of-prior-line spill-over)
		    (1-f stop-line-index))))
      (values (-f stop-character-index
		  length-of-string)
	      stop-line-index)))

    
    








;;;; Editing Text "Without" the Editor 





;;; `Parse-text-for-slot' parses text just as though the user had entered it into
;;; the editor.  If the text parses OK, the slot is updated and a non-nil value
;;; is returned; otherwise, the slot is not changed, and NIL is returned.

;;; The text is reclaimed or incorporated by parse-text-for-slot.

;;; It is an error to call this function if frame's class has no type feature
;;; or a  type feature that does not allow editing.  Type-of-slot? should be
;;; supplied, if known, for the sake of efficiency.

;;; This function does not test for any other restrictions, e.g., proprietary,
;;; user restrictions, etc.

;;; This function is guaranteed not to fail (and return nil) if the type of
;;; slot is a free text slot type.  Callers may depend on this.  To determine
;;; if this is true given type-of-slot, use (free-text-slot-type-p type-of-slot).

(defun parse-text-for-slot (text frame slot-description
			    &optional runtime-change? type-of-slot?
			              slot-component-name?
				      slot-component-indicator?
				      make-reason-for-failure-p)
  (let ((type-of-slot			; it's an error for this to be nil 
	  (or type-of-slot?
	      (feature-assq 'type (slot-features slot-description)))))
    (cond
      ((and (free-text-slot-type-p type-of-slot)
 	    (text-slot-type-p type-of-slot)) ; -- require "classic" free text - mhd 2/8/05
       (let ((do-not-note-permanent-changes-p
	       (or do-not-note-permanent-changes-p runtime-change?)))
	 (when runtime-change?
	   (note-kb-state-change-to-slot-by-saving-text frame slot-description))
	 (change-slot-description-value
	   frame slot-description (slot-value-cons no-value text))))
      (t
       (for-workstation ((or (if servicing-workstation?
				 current-workstation)
			     (car (last workstations-in-service))))	; hack!
	 (let ((keep-edit-workspace-hidden-no-matter-what? t))
	   (enter-editing-context
	     frame
	     (denote-slot-using-slot-value-conses
	       slot-description (class-description-slot frame))
	     text
	     t						    ; edit-workspace-hidden?
	     nil nil nil nil nil
	     nil nil nil nil nil
	     nil nil nil
	     t						    ; do-not-have-edit-option-buttons? (Note A)
	     t						    ; do-not-have-edit-menus?
	     slot-component-name? slot-component-indicator?)
	   (in-editing-context		; needs cleanup!! (MHD 11/1/91)
	       (specific-structure-for-current-workstation-context)
	     (setf (editing-for-runtime-change? current-edit-state)
		   runtime-change?))
	   (let* ((editing-context current-workstation-context)
		  (note-as-kb-state-change? 
		    (or runtime-change?
			note-as-kb-state-change?)))

	     (finish-parsing-insofar-as-possible)

	     (cond
	       ((eq current-workstation-context editing-context)
		(let* ((edit-state? (specific-structure-for-workstation-context
				      editing-context))
		       (reason-for-failure?
			 (and make-reason-for-failure-p
			      edit-state?
			      (generate-reason-for-parsing-failure edit-state?))))
		(return-from-current-workstation-context 'editing)
		(values nil reason-for-failure?)))
	       (t t)))))))))

;; Note A: Since this editor is never displayed, save some work by not creating
;; the subcommand menu or option buttons. -fmw, 12/29/94

;; Note that the user "sees" a slight difference between the free-text case
;; above and the non-free-text case: in the latter case, the text is
;; highlighted, but not in the former.  Highlighting is not particularly desired
;; in latter case, but I don't have time to change it now, and don't feel that
;; strongly that it should be.  I do want highlighting NOT to happen in the
;; former case, at least for messages, because highlighting was never done for
;; messages before.  A further refinement might be to say that the set of slots
;; that get the compiler invoked on them is the set that gets highlighted.  This
;; implies that we'd put into the user's model a notion of a "compiler" and
;; certain slots that it works on.  There's a proposal to tie this set to
;; certain other functionality in the product, e.g., to make it the set of slots
;; that cannot be edited in a runtime-only system.  (MHD 11/5/91) with some help
;; from JRA.

;; Rework this with LH at some later point. This function is used, at present, only in
;; GFI. (MHD 10/14/88)  It is also used in init file processing and in install. (BEN 1/18/91)

(defun generate-reason-for-parsing-failure (edit-state)
  (let ((reason-for-bad-parse?
	  (problem-string-of-first-reason-for-bad-parse? edit-state)))
    (cond
      (reason-for-bad-parse?
	(let* ((line-index? (line-index-of-first-reason-for-bad-parse? edit-state))
	       (location-string?
		 (and line-index?
		      (get-next-text-line
			(find-text-tail-for-line
			  (text-being-edited edit-state)
			  line-index?)))))
	  ;; location string
	  (cond (location-string?
		 (tformat-text-string
		   "An error, \"~a\", was reported at line ~d, \"~a\""
		   reason-for-bad-parse?
		   (line-index-of-first-reason-for-bad-parse? edit-state)
;		   (character-index-of-first-reason-for-bad-parse? edit-state)
;		   (caar (stack-of-positions-after-tokens edit-state))
		   location-string?))
		(t
		 (tformat-text-string
		   "An error, \"~a\", was reported."
		   reason-for-bad-parse?)))))
      (t
       nil))))



;;; `change-the-text-of' - NOT the function that gets run when the user executes
;;; a "change the text of" from the evaluator; this is an analog made available
;;; to the Lisp developer.  Ultimately, of course, it does run much of the same
;;; code.  This function reclaims the text-string argument, or incorporates it
;;; into its result.  - mhd 11/29/04, jv 2/2/07

(defun change-the-text-of (frame slot-name text-string &optional
				 class-qualifier? runtime-change? type-of-slot?
				 slot-component-name? slot-component-indicator?
				 make-reason-for-failure-p)
  (parse-text-for-slot
    (convert-text-string-to-text text-string)
    frame
    (get-slot-description-of-frame slot-name frame class-qualifier?)
    runtime-change? type-of-slot?
    slot-component-name? slot-component-indicator?
    make-reason-for-failure-p))





;;;; Recompiling KBs




;;; Recompile-item ... need not be called in a workstation context.

;;; The variable `in-recompile-item-p' is globally bound to nil, and bound to t
;;; around the body of recompile-item (actually, around the body of the
;;; subfunction recompile-item-1).  This can be used by code that must do
;;; something special in this case.  For example, a dialog offering to recompile
;;; the KB should not be done while in the midst of recompiling the KB.

(defun recompile-item (frame)
  (if servicing-workstation?
      (recompile-item-1 frame)
      (for-workstation ((car workstations-in-service))
	(recompile-item-1 frame))))

(defvar in-recompile-item-p nil)

(defun recompile-item-1 (frame)
  (let ((in-recompile-item-p t))
  (frame-class-case frame
      (item-list nil)
      (variable
	(recompile-slot-of-frame-1 frame 'formula?))
      (procedure
	(recompile-slot-of-frame-1 frame 'procedure-definition))
      (rule
	(unless (embedded-rule-p frame)
	  (recompile-slot-of-frame-1 frame 'box-translation-and-text)
	  (when (nupec-authorized-p)
	    (recompile-slot-of-frame-1 frame 'nupec-extra-actions))))
      (action-button
	(recompile-slot-of-frame-1 frame 'translation-and-text-of-embedded-rule))
      (user-menu-choice
	(recompile-slot-of-frame-1 frame 'condition-for-using-user-menu-choice?)
	(recompile-slot-of-frame-1 frame 'action-for-user-menu-choice?))
       ((trend-chart)
       (recompile-slot-of-frame-1 frame 'trend-chart-plots))
      ((readout-table dial meter)
       (recompile-slot-of-frame-1 frame 'expressions-to-display))
      (simulation-subtable
	(recompile-slot-of-frame-1 frame 'simulation-formulas?))
      (statement
	(recompile-slot-of-frame-1 frame 'box-translation-and-text))
      (tokenizer
	(unless (recompile-slot-of-frame-1 frame 'patterns-definition)
	  (recompile-slot-of-frame-1 frame 'tokens-definition)))
      (new-table
	(recompile-cell-array frame)
	;; This is the only toggling of frame status unique to
	;; new-tables.  It is the inverse of the recompile incomplete
	;; markings.
	(update-frame-status frame nil nil)))))


(defun recompile-slot-of-frame-1 (frame slot-name? &optional class-qualifier?)
  (when (and slot-name?
	     (let ((slot-value? (get-slot-value frame slot-name? class-qualifier?)))
	       (and slot-value?
		    (consp slot-value?)
		    (not (stripped-text-p (cdr slot-value?))))))
    (enter-editing-context
      frame
      (denote-slot-using-slot-value-conses
	(get-slot-description-of-frame slot-name? frame class-qualifier?)
	(class-description-slot frame))
      nil t)
    (let ((editing-context current-workstation-context))
      (finish-parsing-insofar-as-possible)
      (when (and keep-edit-workspace-hidden-no-matter-what?
		 (eq current-workstation-context editing-context))
	(return-from-current-workstation-context 'editing)))))




;;;; Entering the Editor on Edit Boxes



;;; The function `enter-editing-context-on-text-box' fires up the editor on the
;;; text of a text-box.  It edits in-place as needed.  Optionally, the initial
;;; editor cursor position may be given, either in window coordinates or
;;; character coordinates.  Both x and y should be non-NIL if either is.

(defun enter-editing-context-on-text-box
    (text-box image-plane
	      &optional
	      ;; Pass in either window or character coordinates.
	      x-in-window? y-in-window?
	      cursor-line-index? cursor-character-index? type-of-slot?)
  (let* ((full-editor?
	   (non-menu-choice-permitted-p 'full-editor text-box))
	 (in-place-editing?
	   (not full-editor?))
	 (buttons-visible?
	   (or full-editor?
	       (non-menu-choice-permitted-p 'option-buttons-for-edit-in-place text-box)))
	 (menus-visible?
	   (non-menu-choice-permitted-p 'menus-for-edit-in-place text-box))
	 (clear-before-edit?
	   (and (not full-editor?)
	       (not (non-menu-choice-permitted-p
		      'do-not-clear-text-for-edit-in-place text-box))))
	 (initial-text-or-edit-box?
	   (if clear-before-edit? (make-empty-text))))

    (cond (clear-before-edit?
	   ;; this works around a bug down the line where
	   ;; determine-corrected-text-position-if-necessary doesn't think its
	   ;; fun mapping these cursor positions to an empty
	   ;; text. /home/mhd/dev/bugs/borderless-free-text.kb demonstrates
	   ;; this unreported bug.  (MHD 2/20/95)
	   (setq cursor-line-index? nil
		 cursor-character-index? nil))
	  (cursor-line-index?)
	  ((and x-in-window? y-in-window?)
	   (multiple-value-setq (cursor-line-index? cursor-character-index?)
	     (find-position-in-text-given-image-plane
	       text-box text-box nil nil nil nil
	       image-plane x-in-window? y-in-window?))))

    (enter-editing-context
      text-box 'box-translation-and-text
      initial-text-or-edit-box?
      nil
      ;; Do not pass text-box-format in; it causes gratuitous overrides
      ;; of the editing parameters, and is most disturbing to users editing
      ;; borderless free texts.  Even when doing click-to-edit, it does
      ;; not want to be used.  (MHD 2/20/95)
      nil				; (text-box-format text-box)
      nil
      cursor-line-index? cursor-character-index?
      (if in-place-editing? image-plane)
      (if in-place-editing? text-box)
      nil nil nil nil
      type-of-slot?
      nil nil
      (not buttons-visible?)
      (not menus-visible?))))

;; This was previously defined, a bit more simply, in FACILITIES.  Moved here
;; for modularity.  It has to be fixed or adapted for
;; enter-editing-context-on-text-box-per-edit-style's use, to deal with all the
;; leftover, non-handled edit-style attributes!  (MHD 8/15/94)





;;;; Finding Positions in Text



;;; Find-position-in-text-region ... 

#+unused
(defun find-position-in-text-region (text-region x-in-workspace y-in-workspace)
  (let ((text-box?
	  (if (null (row-index-for-text-region-cell? text-region))
	      (superblock? text-region))))
    (find-position-in-text
      text-box?
      (if (null text-box?)
	  (get-table-cell
	    (superblock? text-region)
	    (row-index-for-text-region-cell? text-region)
	    (column-index-for-text-region-cell? text-region)))
      (left-edge-of-block text-region) (top-edge-of-block text-region)
      t x-in-workspace y-in-workspace)))

;; Consider also defining "find-position-in-text-box".



;;; `Find-position-in-text' finds a "position" (see below) in the text in
;;; text-box? or text-cell? (which are mutually exclusive), if appropriate.

;;; Left-edge-of-cell? and top-edge-of-cell? must be specified only in the table
;;; case (when text-cell? is specified).

;;; When `look-in-lost-spaces-too?' is specified, then lost spaces at the end of
;;; text lines will be treated as if they were present.

;;; If `x-in-workspace?' is specified, find-position-in-text finds the text
;;; position nearest to (x-in-workspace?, y-in-workspace?), where text positions
;;; within lost spaces qualify only if look-in-lost-spaces-too? is non-nil.
;;; `Only-if-in-text?' controls three modes as to how close to the text we must
;;; be.  `NIL' always returns a value.  Useful when selecting text and the mouse
;;; may be far from the text.  `T' returns a position when the point is within
;;; the text or no farther away than a word space or half the normal line
;;; spacing.  For`:tight' the point must be within the text and not below the
;;; baseline with an extra two workspace units of leeway on all four sides.

;;; If `x-in-workspace?' is nil, (line-index?, character-index?) is converted to
;;; a workspace position on the baseline of a text line.

;;; Note that two major cases are handled:
;;;   (a) where x-in-workspace?, y-in-workspace?, and maybe only-if-in-text?
;;;       and/or find-character-instead-of-position-between? is specified; and
;;;   (b) where line-index?, character-index?, (and text-tail-if-known?, if
;;;       known) are specified.

;;; Specifically:
;;;   In case (a) if x-in-workspace? is specified then line-index?,
;;;       character-index?, and text-tail-if-known? will be ignored.
;;;   In case (b) y-in-workspace? will be ignored, and line-index?,
;;;       character-index?, and text-tail-if-known? will determine the position.

;;; Note that nil can be returned.
;;;   In case (a) only if only-if-in-text? is specified and (x-in-workspace?,
;;;      y-in-workspace?) is not "in" text, or
;;;   In case (b) if line-index? is out-of-bounds.

;;; When `find-character-instead-of-position-between?' is specified, a returned
;;; character index is for the position immediately to the left of the found
;;; character.  When find-character-instead-of-position-between? is NOT specified
;;; (the normal case), a returned position between characters implies that
;;; x-in-workspace? was between the midlines of those characters.

;;; Find-position-in-text returns either nil or the following five values:
;;;    (1) the line index;
;;;    (2) the character index;
;;;    (3) the new text tail;
;;;    (4) the x coordinate in the workspace for the text position specified by
;;;          the line index and character index (on a text line baseline); and
;;;    (5) the y coordinate.
;;; Note that the fourth and fifth values will not typically be equal to the
;;; x-in-workspace? and y-in-workspace? arguments (when those arguments are
;;; provided).

(defun find-position-in-text
       (text-box? text-cell? left-edge-of-cell? top-edge-of-cell?; reorder args!
	look-in-lost-spaces-too?
	x-in-workspace? y-in-workspace?
	&optional line-index? character-index? text-tail-if-known?
	          only-if-in-text? find-character-instead-of-position-between?
		  tab-width?)		; document! (as for compute-width-of-text-line)
  (declare (ignore text-tail-if-known?)) ; not used yet
  (loop with text-box-format
	  = (if text-box?
		(text-box-format text-box?)
		(text-cell-format text-cell?))
	with text-cell-plist
	  = (if text-box?
		(text-cell-plist-for-text-box text-box?)
		(text-cell-plist text-cell?))
	with ab-font	  ; this and following 3 needed in x-in-workspace? case only
	  = (ab-font (car (text-cell-font-map text-box-format)))
	with left-edge-of-text
	  = (+w (if text-box?
		    (+w (left-edge-of-block text-box?)
			(text-box-left-border-width text-box-format))
		    left-edge-of-cell?)
		(text-cell-left-margin text-box-format))
	with top-edge-of-text
	  = (+w (if text-box?
		    (+w (top-edge-of-block text-box?)
			(text-box-top-border-width text-box-format))
		    top-edge-of-cell?)
		(text-cell-top-margin text-box-format)
		(or (if text-cell-plist		; optimization
			(getfq text-cell-plist 'y-offset-for-text))
		    0))
	with x-magnification?
	  = (or (if text-cell-plist		; optimization
		    (getfq text-cell-plist 'x-magnification))
		(text-cell-x-magnification? text-box-format))
	with y-magnification?
	  = (or (if text-cell-plist		; optimization
		    (getfq text-cell-plist 'y-magnification))
		(text-cell-y-magnification? text-box-format))
	with x-in-text?
	  = (if x-in-workspace?
		(if x-magnification?
		    (inverse-magnify
		      (-w x-in-workspace? left-edge-of-text) x-magnification?)
		    (-w x-in-workspace? left-edge-of-text)))
	with y-in-text?
	  = (if y-in-workspace?
		(if y-magnification?
		    (inverse-magnify
		      (-w y-in-workspace? top-edge-of-text) y-magnification?)
		    (-w y-in-workspace? top-edge-of-text)))
	with baseline-to-baseline-distance
	  = (+w (text-cell-line-height text-box-format)
		(text-cell-line-spacing text-box-format))
	with distance-from-baseline-to-bottom-of-line
	  = (if (eq only-if-in-text? :tight)
		2				; changed from 0. (MHD 12/4/89)
		(+w (-w (text-cell-line-height text-box-format)
			(text-cell-baseline-position text-box-format))
		    (halfw (text-cell-line-spacing text-box-format))))
	with distance-to-next-baseline-from-top
	  = (text-cell-baseline-position text-box-format)
	with word-spacing
	  = (default-word-spacing text-box-format)
	with word-spacing-for-next-line? = nil
	with lost-spaces = 1
	with line-index = 1
	with indentation = 0
	with text = (if text-box?
			(cdr (box-translation-and-text text-box?))
			(text? text-cell?))
	with above-bottom-of-line?
	with midline-x-from-left
	with ok-to-return-position?
	with lost-spaces-value?
	as l on text
	as text-element = (car l)
	do (cond
	     ((text-line-p text-element)
	      (setq above-bottom-of-line?
		    (if x-in-text?
			(<=w y-in-text?
			     (+w distance-to-next-baseline-from-top
				 distance-from-baseline-to-bottom-of-line))))
	      (cond
		((if x-in-text?   ; fix to return nil when <= succeeds and >= fails!
		     (or (and above-bottom-of-line?
			      (or (null only-if-in-text?)	; simplify?
				  (>f line-index 1)	; added 1/13/89 by LH (see below)
				  (>=w y-in-text?
				       (-w distance-to-next-baseline-from-top
					   (if (eq only-if-in-text? :tight)
					       (+w (text-cell-baseline-position text-box-format)
						   2)	; changed from 0. (MHD 12/4/89)
					       (-w baseline-to-baseline-distance
						   distance-from-baseline-to-bottom-of-line))))))
			 (if (null only-if-in-text?)
			     (null (cdr l))))
		     (=f line-index line-index?))
		 (setq line-index? line-index)
		 (loop with line-width-a
		       with line-width-b
		       with line-length = (text-line-length text-element)
		       with end
			 = (+f line-length
			       (if (or character-index? look-in-lost-spaces-too?)
				   (if (fixnump lost-spaces)
				       lost-spaces
				       (text-line-length lost-spaces))
				   0))
		       with width-of-initial-spaces? = nil
		       with i = 0
		       with preceding-i
		       with unicode-wide-character
		       with character-width
		       initially
			 (set-text-x line-width-a line-width-b 0)
		       while (<f (setq preceding-i i) end)
		       do (progn
			    (setq unicode-wide-character
				  (read-unicode-character-from-wide-string-with-lost-spaces
				    text-element i line-length lost-spaces))
			    (cond
			      ((char=w unicode-wide-character #.%tab)
			       (let* ((a line-width-a)
				      (b line-width-b)
				      (position	; a text width
					(text-x-to-text-width a b))
				      (tab-width					
					(or tab-width?
					    (word-spacing-based-tab-width word-spacing)))
				      (next-tab-position
					(+ (- position (mod position tab-width)) tab-width)))
				 ;; Word-spacing should be default-word-spacing!  This works
				 ;; only as long as we don't have justified text or other fancy
				 ;; formatting! (MHD)
				 (setq character-width
				       (-w next-tab-position position))))
			      (t
			       (setq character-width	; see also compute-width-of-text-line
				     (if (ordinary-space-p unicode-wide-character)
					 (or word-spacing-for-next-line? word-spacing)
					 (get-unicode-set-width-as-text-width
					   unicode-wide-character ab-font)))))
			    (if (and (null width-of-initial-spaces?)
				     (not (text-break-p unicode-wide-character))
				     ;; prev. expr. replaces this expr. in comments:
;				     (not (or (ordinary-space-p unicode-wide-character)
;					      (or (char=w ; "newline-p"?
;						    unicode-wide-character
;						    #.%paragraph-separator)
;						  (char=w
;						    unicode-wide-character
;						    #.%line-separator))))
				     )
				(setq width-of-initial-spaces?
				      (text-x-to-x line-width-a line-width-b))))
		       until
		       (if x-in-text?
			     (if (>f character-width 0)
				 (>w (+w indentation	; save the +w?
					 (incremented-text-x-as-x
					   line-width-a line-width-b
					   (if find-character-instead-of-position-between?
					       character-width
					       (halff character-width))))
				     x-in-text?))
			     (=f preceding-i character-index?))
		       do (incf-text-x line-width-a line-width-b character-width)
		       finally
			 (setq character-index? preceding-i)	; changes arg!
			 (setq midline-x-from-left
			       (+w indentation
				   (text-x-to-x line-width-a line-width-b)))
			 (setq ok-to-return-position?
			       (or (null x-in-text?)
				   (null only-if-in-text?)
				   (and width-of-initial-spaces?
					;; Note: the code below was rearranged just
					;; for the sake of a very old GNU C
					;; compiler, which could not apparently
					;; handle the old code, which did not have
					;; the (unnecessary) let forms.
					;;
					;; When we start using a new version
					;; of the Chestnut translator, this will
					;; likely change the structure of the
					;; emitted C code, making this transformation
					;; unnecessary.  This change being done
					;; for both 3.1 and 3.0 rev. 3.  Note that
					;; this affects also the Motorola, which has
					;; the same compiler and the same
					;; chip, the 88000.  (MHD/JRA 5/13/93)
					(let ((indentation-offset
					       (if (eq only-if-in-text? :tight)
						   2 ; changed from 0. (MHD 12/4/89)
						   (text-width-to-x word-spacing))))
					  (>=w x-in-text?
					       (-w (+w indentation
						       width-of-initial-spaces?)
						   indentation-offset)))
					(or (<f preceding-i line-length)
					    (let ((indentation-offset-text-width
						   (if (eq only-if-in-text? :tight)
						       #.(convert-to-text-width
							  2) ; changed from 0. (MHD 12/4/89)
						       word-spacing)))
					      (<=w x-in-text?
						   (+w indentation
						       (incremented-text-x-as-x
							line-width-a line-width-b
							indentation-offset-text-width)))))))))
		 (return
		   (if ok-to-return-position?
		       (values
			 line-index? character-index?
			 (find-text-tail-for-line ; do this more efficiently!
			   text line-index?)
			 (+w left-edge-of-text
			     (if x-magnification?
				 (magnify midline-x-from-left x-magnification?)
				 midline-x-from-left))
			 (+w top-edge-of-text
			     (if y-magnification?
				 (magnify
				   distance-to-next-baseline-from-top
				   y-magnification?)
				 distance-to-next-baseline-from-top))))))
		(above-bottom-of-line?
		 (return nil)))
	      (incff line-index)
	      (setq distance-to-next-baseline-from-top
		    (+w distance-to-next-baseline-from-top
			baseline-to-baseline-distance))
	      (setq word-spacing-for-next-line? nil)
	      (setq lost-spaces 1))
	     ((fixnump text-element)
	      (setq indentation text-element))
	     ((setq lost-spaces-value? (lost-spaces-value-if-any text-element))
	      (setq lost-spaces lost-spaces-value?))
	     ((symbolp text-element))
	     ((eq (car text-element) 'leading)
	      (setq distance-to-next-baseline-from-top
		    (+w distance-to-next-baseline-from-top (cdr text-element))))
	     ((eq (car text-element) 'word-spacing)
	      (setq word-spacing-for-next-line? (cdr text-element))))))

;; Fixnump test above used to be integerp.  I changed it here and throughout
;; this module upon learning that fixnum is inlined, while integerp is a
;; function call (in Chestnut).  This is ok, althought ideally, both would be
;; inlined, I think. (MHD 6/4/92)

;; Regarding the change added 1/13/89 by LH.  This eliminates stripes between
;; lines in the :tight case, at the expense of some additional space above lines
;; other than the first that is considered "within the text".  Ideally, "within
;; the text" in the :tight case should conform to a tight outline around the
;; text; that would require computation of the indentation and width of the
;; preceding line.

;; I tuned the case where only-if-in-text? is :tight to allow 2 workspace units
;; of extra leeway on all four sides, and so documented that case.  (MHD
;; 12/4/89)


(defun find-position-in-text-given-image-plane
    (block-enclosing-text
      text-box? text-cell? left-edge-of-cell? top-edge-of-cell?
      look-in-lost-spaces-too?
      image-plane x-in-window y-in-window
      &optional line-index? character-index? text-tail?
      only-if-in-text? find-character-instead-of-position-between?)
  (let (x-in-workspace y-in-workspace)
    (let ((current-image-plane image-plane))
      (with-raw-window-transform-and-draw-area ((gensym-window-for-image-plane image-plane))
	(with-nested-transform-and-draw-area-of-image-plane-contents? (image-plane)
	  (with-frame-transform-of-block-if-any (block-enclosing-text)
	    (setf x-in-workspace (x-in-workspace x-in-window))
	    (setf y-in-workspace (y-in-workspace y-in-window))))))
    (find-position-in-text
      text-box? text-cell? left-edge-of-cell? top-edge-of-cell?	; reorder args!
      look-in-lost-spaces-too?
      x-in-workspace y-in-workspace
      line-index? character-index? text-tail?
      only-if-in-text? find-character-instead-of-position-between?)))








;;;; Subcommand Menus and Subcommands




;;; A subcommand-menu is a subclass of a menu.  These are placed upon
;;; non-kb workspaces to create a table of buttons.  For example the
;;; buttons in the login panel (aka change mode).

;;; Each button maybe configured by placing information in the `special-case'
;;; property of the text cell that representing the button.  Call this the
;;; `button-info'.  Individual buttons maybe enabled and disabled using
;;; `enable-or-disable-radio-button-subcommand'.

;;; When a mouse down is detected over a `make-subcommand-menu-button-spot' a
;;; `subcommand-state' workstation context should be entered.  This context will
;;; returns three values: the subcommand-menu, button-info, and
;;; subcommand-function-arglist?.  These maybe used to implement the button
;;; action, or the `subcommand-function?' slot maybe used.

;;; The `subcommand-function' slot contains a function that is used to implement
;;; the actions of the buttons.  The default event handler will invoke this function if
;;; the mouse is pressed and released over one of the buttons.  This function is
;;; invoked while the button is still highlighted, and is passed the
;;; subcommand-menu, and the button info.  Additional arguments can be passed
;;; using the `subcommand-function-arglist?' slot.

;;; If you want to execute the button action while highlighted, do it in
;;; the subcommand-function, if you want to do it after the button is
;;; no longer highlighted do it in the continuation following the subcommand-state.

;;; Reclaiming the subcommand-function-arglist? is implemented via
;;; the subcommand-function-arglist-reclaimer? function, which should be
;;; set at the same time as the subcommand-function. -alatto, 4/8/99

;;; Reclaiming the special-case? property is done by the
;;; text cell reclaiming mechinisms.

;;; Note that if the subcommand-function? reclaims the subcommand-menu directly
;;; or indirectly the continuation must treat the return values with approprate
;;; care.  For this reason it is best if the `button-info' is a symbol or some other
;;; non-reclaimable value.

(def-class (subcommand-menu menu)
  (subcommand-function?
    nil system vector-slot not-user-editable)
  (subcommand-function-arglist?
    nil system vector-slot not-user-editable)
  (subcommand-function-arglist-reclaimer?
    nil system vector-slot not-user-editable)
  )

(def-slot-value-reclaimer subcommand-function-arglist? (arglist subcommand-menu)
  (let ((reclaimer-function?
	  (subcommand-function-arglist-reclaimer? subcommand-menu)))
    (when reclaimer-function?
      (funcall-simple-compiled-function
	reclaimer-function? arglist))))

;; Currently this is used for g2-login, inspect results, and editor buttons.
;; Two of those use subcommand-function? one of them uses the continuation.
;; - ben 11/10/93



;;; The `generate-spot for a subcommand-menu' generates a
;;; subcommand-menu-button-spot, if the mouse is over a visible button in the
;;; subcommand menu.  Otherwise it generates a workspace-background-spot.

(def-class-method generate-spot (subcommand-menu mouse-pointer)
  (generate-spot-for-button-menu
    (make-subcommand-menu-button-spot)
    subcommand-menu
    mouse-pointer))



(def-text-box-format subcommand-menu-item-format
  text-cell-background-color? white
  text-cell-line-color? black
  
  text-cell-left-margin 1			; 8 for full margin
  text-cell-top-margin 4
  text-cell-right-margin 1			; 8 for full margin
  text-cell-bottom-margin 4
  text-cell-font-map (hm18)
  text-cell-line-height 22
  text-cell-baseline-position 17
  text-cell-line-spacing 0			; very tight leading desired
  text-cell-line-quadding? center
  minimum-format-width-for-text-cell 400)

(def-text-box-format small-subcommand-menu-item-format
  text-cell-background-color? white
  text-cell-line-color? black
  text-cell-left-margin 1			; 7 for full margin
  text-cell-top-margin 3
  text-cell-right-margin 1			; 7 for full margin
  text-cell-bottom-margin 3
  text-cell-font-map (hm14)
  text-cell-line-height 17
  text-cell-baseline-position 15
  text-cell-line-spacing 2
  text-cell-line-quadding? center
  minimum-format-width-for-text-cell 350)

(def-text-box-format extra-large-subcommand-menu-item-format
  text-cell-background-color? white
  text-cell-line-color? black

  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 8.75) ; 5/8 en
  minimum-word-spacing #.(convert-to-text-width 7)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 21)	          ; 3/2 en
  
  text-cell-left-margin 1			; 8 for full margin
  text-cell-top-margin 4
  text-cell-right-margin 1			; 8 for full margin
  text-cell-bottom-margin 4
  text-cell-font-map (hm24)
  text-cell-line-height 28
  text-cell-baseline-position 21
  text-cell-line-spacing 0			; very tight leading desired
  text-cell-line-quadding? center
  minimum-format-width-for-text-cell 400)

(setf (corresponding-small-font-format-name 'subcommand-menu-item-format)
      'small-subcommand-menu-item-format)

(setf (corresponding-extra-large-font-format-name 'subcommand-menu-item-format)
      'extra-large-subcommand-menu-item-format)

;; Note: the extra-large version was just added today -- apparently it went
;; missing until now.  (In G2 Version 3.1) (MHD 1/6/92)

;; NOTE in regard to "; 8/7 for full margin" comments:  We cut way down the margin
;; and now make up for that by inserting a space character before and after the
;; choice symbol.  The reason for that is to make the text region that is used
;; for highlighting it have a little margin around it (on the left and the right).
;; (There is still too little margin above and below, I feel).  We probably would
;; have done this with a different kind of text region or text cell coloring
;; facility with let you fill the whole cell minus a border of some width --
;; rework this if such facilities become available.  (MHD/LH 8/14/90)




(def-table-format subcommand-menu-table-format
  table-background-color? transparent
  table-row-boundary-color? transparent
  table-column-boundary-color? transparent
  table-border-color? transparent
  table-left-border-width 2
  table-top-border-width 2
  table-right-border-width 2
  table-bottom-border-width 2
  table-row-boundary-width 1
  table-column-boundary-width 1)

#+development
(def-table-format-spot-generator subcommand-menu-table-format (menu mouse-pointer)
  (declare (ignore menu mouse-pointer))
  ;; The generate spot method on the block preempts this.
  (error "Spot generator for subcommand-menu-table-format should never be called."))





;; Note: the following are saved in some 3.0 KBs.  They are obsolete in that no
;; code now creates or accesses the format frames they would define.  However,
;; some 3.0 KBs have them, because they were saved on the last days in
;; development that these format frames were in existence, and because 3.0 KBs
;; save all existing format frames, even ones not in use.  (MHD 10/4/91)

(DEF-TEXT-BOX-FORMAT ANY-TOKEN-MENU-ITEM-FORMAT
  TEXT-CELL-BACKGROUND-COLOR? WHITE		; MAYBE "LIGHT-GRAY" WHEN COLOR MAPPING
  TEXT-CELL-LINE-COLOR? BLACK			;   WORKS FOR B&W SYSTEMS, OR MAYBE
  TEXT-CELL-LEFT-MARGIN 7			;   WHITE ON BLACK A LA SUBCOMMANDS?
  TEXT-CELL-TOP-MARGIN 3			; ADJUST THESE!
  TEXT-CELL-RIGHT-MARGIN 7
  TEXT-CELL-BOTTOM-MARGIN 3
  TEXT-CELL-FONT-MAP (HM18)
  TEXT-CELL-LINE-HEIGHT 20
  TEXT-CELL-BASELINE-POSITION 15
  TEXT-CELL-LINE-SPACING 0			; VERY TIGHT LEADING DESIRED
  TEXT-CELL-LINE-QUADDING? CENTER
  MINIMUM-FORMAT-WIDTH-FOR-TEXT-CELL 400)

(DEF-TEXT-BOX-FORMAT SMALL-ANY-TOKEN-MENU-ITEM-FORMAT
  TEXT-CELL-BACKGROUND-COLOR? WHITE		; MAYBE "LIGHT-GRAY" WHEN COLOR MAPPING
  TEXT-CELL-LINE-COLOR? BLACK			;   WORKS FOR B&W SYSTEMS, OR MAYBE
  TEXT-CELL-LEFT-MARGIN 6			;   WHITE ON BLACK A LA SUBCOMMANDS?
  TEXT-CELL-TOP-MARGIN 2			; ADJUST THESE!
  TEXT-CELL-TOP-MARGIN 2
  TEXT-CELL-RIGHT-MARGIN 6
  TEXT-CELL-BOTTOM-MARGIN 2
  TEXT-CELL-FONT-MAP (HM14)
  TEXT-CELL-LINE-HEIGHT 15
  TEXT-CELL-BASELINE-POSITION 13
  TEXT-CELL-LINE-SPACING 2
  TEXT-CELL-LINE-QUADDING? CENTER
  MINIMUM-FORMAT-WIDTH-FOR-TEXT-CELL 350)

(SETF (CORRESPONDING-SMALL-FONT-FORMAT-NAME 'ANY-TOKEN-MENU-ITEM-FORMAT)
      'SMALL-ANY-TOKEN-MENU-ITEM-FORMAT)



(DEF-TEXT-BOX-FORMAT TOKEN-MENU-ITEM-FORMAT
  TEXT-CELL-LEFT-MARGIN 7			; ADJUST THESE!
  TEXT-CELL-TOP-MARGIN 3
  TEXT-CELL-RIGHT-MARGIN 7
  TEXT-CELL-BOTTOM-MARGIN 3
  TEXT-CELL-FONT-MAP (HM18)
  TEXT-CELL-LINE-HEIGHT 20
  TEXT-CELL-BASELINE-POSITION 15
  TEXT-CELL-LINE-SPACING 0			; VERY TIGHT LEADING DESIRED
  TEXT-CELL-LINE-QUADDING? CENTER
  MINIMUM-FORMAT-WIDTH-FOR-TEXT-CELL 400
  MINIMUM-WIDTH-FOR-TEXT-CELL 60)

(DEF-TEXT-BOX-FORMAT SMALL-TOKEN-MENU-ITEM-FORMAT
  TEXT-CELL-LEFT-MARGIN 6			; ADJUST THESE!
  TEXT-CELL-TOP-MARGIN 2
  TEXT-CELL-RIGHT-MARGIN 6
  TEXT-CELL-BOTTOM-MARGIN 2
  TEXT-CELL-FONT-MAP (HM14)
  TEXT-CELL-LINE-HEIGHT 15
  TEXT-CELL-BASELINE-POSITION 13
  TEXT-CELL-LINE-SPACING 2
  TEXT-CELL-LINE-QUADDING? CENTER
  MINIMUM-FORMAT-WIDTH-FOR-TEXT-CELL 350)

(SETF (CORRESPONDING-SMALL-FONT-FORMAT-NAME 'TOKEN-MENU-ITEM-FORMAT)
      'SMALL-TOKEN-MENU-ITEM-FORMAT)



(DEF-TABLE-FORMAT ANY-TOKEN-MENU-FORMAT
  TABLE-BACKGROUND-COLOR? WHITE
  TABLE-ROW-BOUNDARY-WIDTH 0
  TABLE-COLUMN-BOUNDARY-WIDTH 0
  TABLE-LEFT-BORDER-WIDTH 0
  TABLE-TOP-BORDER-WIDTH 0
  TABLE-RIGHT-BORDER-WIDTH 0
  TABLE-BOTTOM-BORDER-WIDTH 0)

#+development
(def-table-format-spot-generator any-token-menu-format (menu mouse-pointer)
  (declare (ignore menu mouse-pointer))
  ;; The generate spot method on the block preempts this.
  (error "Spot generator for any-token-menu-format should never be called."))












;;; The state of an edit subcommand is given by its text and background colors.
;;; The following are colors for the three possible states: enabled, disabled,
;;; and pending.

;; Enabled: reverse video.
(defparameter background-color-for-enabled-subcommands 'foreground)
(defparameter text-color-for-enabled-subcommands 'background)

;; Disabled: all in background color.
(defparameter background-color-for-disabled-subcommands 'background)
(defparameter text-color-for-disabled-subcommands 'background)

;; Highlighting pending commands.
(defparameter highlight-color-for-enabled-pending-subcommands 'transparent)
(defparameter highlight-color-for-enabled-non-pending-subcommands 'foreground)

(defparameter highlight-color-for-disabled-pending-subcommands 'transparent)
(defparameter highlight-color-for-disabled-non-pending-subcommands 'transparent)
  

(defparameter highlight-color-for-pending-on-radio-button-subcommands 'foreground)
(defparameter highlight-color-for-non-pending-on-radio-button-subcommands 'transparent)

(defparameter highlight-color-for-pending-off-radio-button-subcommands 'transparent)
(defparameter highlight-color-for-non-pending-off-radio-button-subcommands 'foreground)

;; I changed the text and bg colors which were TRANSPARENT to be BACKGROUND
;; instead.  Since transparent now really means it, the text was not being drawn
;; at all. -fmw, 6/10/94



;;; `Make-subcommand-menu' ... Subcommands should be a list made up of slot value
;;; conses, which will be reclaimed by this function.  A cell in the the
;;; subcommand menu (a table) will be created for each subcommand in this
;;; list.  Each subcommand may be either
;;;
;;;    (a) a symbol, which is displayed in lowercase as text, and is
;;;        made the value of the special-case? property of text cell plist
;;;        of the text cell; or
;;;
;;;    (b) a cons of the form
;;;
;;;             (symbol . string)
;;;
;;;        which is just like case (a), except that string is incorporated
;;;        or reclaimed, and is displayed (unless there's an overriding
;;;        translation); or
;;;
;;;     ... (other choices not currently implemented)

;;; Subcommands are all initially disabled.

(defun make-subcommand-menu (subcommands &optional font-size?)
  (prog1
      (make-or-reformat-table
	(loop as subcommand in subcommands
	      as subcommand-symbol
		 = (if (consp subcommand) (car subcommand) subcommand)
	      as translation?
		 = (with-localization-purpose 'button-label
		     (translation-for-symbol? subcommand-symbol))
	      as final-string
		 = (if translation?
		       (copy-text-string translation?)
		       (if (consp subcommand)
			   (copy-text-string (cdr subcommand))
			   (copy-symbol-name subcommand-symbol :first)))
	      collect final-string into final-strings using gensym-cons
	      finally			; not elegant - we make two passes,
					;   the first to get the width information
		(return
		  (prog1
		      (let ((width (get-overall-minimum-width-for-subcommand-menu-column final-strings)))
			(loop for subcommand in subcommands
			      as subcommand-symbol = (if (consp subcommand) (car subcommand) subcommand)
			      as final-string in final-strings
			      as cell
				 = (cond
				     (new-g2-classic-ui-p
				      (make-icon-cell-for-entity
					(make-editor-subcommand-button final-string subcommand-symbol width)
					2 0 2 0))
				     (t
				      (let ((text-cell
					      (make-text-cell
						(prog1
						    (convert-text-string-to-text
						      (tformat-text-string	; add sp. before & after
							" ~a "		;   to act as the margin
							final-string))
						  (reclaim-text-string final-string)) ; strings recycled here
						(choose-font-format-per-font-size
						  'subcommand-menu-item-format
						  font-size?))))
					(choose-font-format-per-font-size
					  'subcommand-menu-item-format font-size?)
					(change-text-cell-property
					  text-cell 'special-case?	; needs to be generalized!!
					  subcommand-symbol)
					(change-text-cell-property
					  text-cell 'background-color
					  background-color-for-disabled-subcommands)
					(change-text-cell-property
					  text-cell 'line-color
					  text-color-for-disabled-subcommands)
					text-cell)))
			      nconc (slot-value-list (slot-value-list cell))))
		    (reclaim-gensym-list final-strings))))
	'subcommand-menu-table-format nil 'subcommand-menu t)
    (reclaim-slot-value subcommands)))	; strings in argument recycled here

;; I flushed the half-implemented/sketched/unused code and documentation for
;; subcommands as icons and subcommands with specific text.  Also changed this
;; is undergoing changes in implementation for the new-g2-classic-ui-p
;; case. (MHD 10/5/99)



;;; Subcommand-enabled-p ...

(defun subcommand-enabled-p (subcommand-cell subcommand-menu)
  (cond
    ((cell-is-block-p subcommand-cell)
     (let ((s (first-subblock subcommand-cell)))
       (and s
	    (frame-of-class-p s 'editor-subcommand-button)
	    (not (get-slot-value ; (fwd. ref.)
		   s
		   'editor-subcommand-disabled-p)))))
    (t
     (let* (
	 ;; Fix formatting later!
	 (subcommand-text-cell subcommand-cell)
	 (text-cell-plist (text-cell-plist subcommand-text-cell))
	 (text-cell-format (text-cell-format subcommand-text-cell))
	 (background-color?
	   (or (getfq text-cell-plist 'background-color)
	       (text-cell-background-color? text-cell-format)
	       (table-background-color?
		 (table-format subcommand-menu)))))
    (not					; i.e. if text of cell is visible
      (eq (or background-color?
	      (or (workspace-background-color?
		    (superblock? subcommand-menu))
		  'white))
	  (let ((text-color?
		  (or (getfq text-cell-plist 'line-color)
		      (text-cell-line-color? text-cell-format)
		      (table-line-color?
			(table-format subcommand-menu)))))
	    (or text-color?
		(or (workspace-foreground-color?
		      (superblock? subcommand-menu))
		    'black)))))))
    ))

;; This would benefit from some improved method abstracting the color
;; defaulting pathways!!




;;; `Enable-or-disable-subcommand' ... in addition, this always turns off the pending
;;; indicator.

;;; If status-as-radio-button? is non-nil, it should be either ON or OFF and thus
;;; specifies both that the subcommand functions "radio-button style" and its
;;; initial status, on or off.  If this is nil, the radio button functioning of
;;; the subcommand is turned off.

(defun enable-or-disable-subcommand
       (subcommand-menu subcommand disable-case?
	&optional status-as-radio-button?)
  (with-backtrace-for-internal-error 'enable-or-disable-subcommand
  (when keep-edit-workspace-hidden-no-matter-what?
    (return-from enable-or-disable-subcommand nil))
  (loop for table-row in (table-rows subcommand-menu)
	as row-index from 0
	until
	  (loop for cell? in table-row
		as column-index from 0
		do (cond
		     ((null cell?))
		     ((cell-is-block-p cell?)
		      (let ((editor-subcommand-button (first-subblock cell?)))
			(when (eq (get-slot-value ; (fwd. ref.)
				    editor-subcommand-button
				    'editor-subcommand-name)
				  subcommand)
			  (enable-or-disable-editor-subcommand-button
			    editor-subcommand-button disable-case?)
			  (when status-as-radio-button?
			    (change-slot-value
			      editor-subcommand-button 'subcommand-button-radio-button-status
			      status-as-radio-button?)
			    (indicate-editor-subcommand-button-pending-state
			      editor-subcommand-button nil nil))
			  (return t))))
		     (t (let ((text-cell cell?))
			  (when (eq (getfq-macro (text-cell-plist text-cell) 'special-case?)
				    subcommand)
			    (indicate-subcommand-pending-state	; just removes indicator
			      subcommand-menu text-cell nil t	;   -- see Note X below
			      row-index column-index)
			    (let* ((background-color
				     (if disable-case?
					 background-color-for-disabled-subcommands
					 background-color-for-enabled-subcommands))
				   (line-color			    
				     (if disable-case?
					 text-color-for-disabled-subcommands
					 text-color-for-enabled-subcommands))
				   (text-cell-plist
				     (text-cell-plist text-cell)))
			      (unless (and (eq (getfq-macro text-cell-plist 'background-color)
					       background-color)
					   (eq (getfq-macro text-cell-plist 'line-color)
					       line-color))
				(change-color-of-text-cell
				  subcommand-menu text-cell nil
				  background-color
				  :no-change
				  line-color)))
			    (when status-as-radio-button?
			      (change-text-cell-property
				text-cell 'radio-button-status
				status-as-radio-button?)
			      (indicate-subcommand-pending-state	; just shows status
				subcommand-menu text-cell nil nil
				row-index column-index))
			    (return t)))))))))

;; This gets run repeatedly even when the status of a subcommand is not changing.
;; If subcommand buttons knew their current enabledness, then we could optimize
;; away the change-color-of-text-cell.


(defun enable-or-disable-radio-button-subcommand
       (subcommand-menu subcommand disable-case?)
  (loop for table-row in (table-rows subcommand-menu)
	as row-index from 0
	until
	  (loop for cell? in table-row
		as column-index from 0
		when (and cell?
			  (if (cell-is-block-p cell?)
			      ;; jv added editor-subcommand-name-function but convention in
			      ;; rest of file is to use (get-slot-value s 'editor-subcommand-name)
			      (eq (editor-subcommand-name-function (first-subblock cell?))
				  subcommand)
			      (eq (getfq-macro (text-cell-plist cell?) 'special-case?)
				  subcommand)))
		  do (cond
		       ((cell-is-block-p cell?)
			(change-slot-value
			  (first-subblock cell?)
			  'subcommand-button-radio-button-status
			  (if disable-case? 'off 'on))
			(indicate-subcommand-pending-state
			  subcommand-menu cell? nil nil
			  row-index column-index))
		       (t
			(change-text-cell-property
			  cell? 'radio-button-status
			  (if disable-case? 'off 'on))
			(indicate-subcommand-pending-state
			  subcommand-menu cell? nil nil
			  row-index column-index)))
		     (return t))))



;;; `Indicate-subcommand-pending-state' ... turns on or off, based on pending?,
;;; the pending indicator (i.e. the highlighting) for the subcommand in text-
;;; cell.  Indicate-subcommand-pending-state can also be used to initially
;;; indicate the on/off status of a "radio-button subcommand" by specifying
;;; nil for pending?.
;;;
;;; Row-index-if-known? and column-index-if-known? are optional. If supplied,
;;; they must correspond to the exact row and column index of text-cell.
;;; Supplying them should speed this function up slightly.

(defun indicate-subcommand-pending-state
    (subcommand-menu cell pending? &optional just-remove-indicator?
		     row-index-if-known? column-index-if-known?)
  (with-backtrace-for-internal-error 'indicate-subcommand-pending-state
  (let ((row-index row-index-if-known?)
	(column-index column-index-if-known?))
    (unless (and row-index-if-known? column-index-if-known?)
      (multiple-value-setq (row-index column-index)
	(get-table-cell-indices subcommand-menu cell)))
    (cond
      ((cell-is-block-p cell)
       (indicate-subcommand-pending-state-for-block-cell
	 cell subcommand-menu pending? just-remove-indicator?
	 row-index column-index))
      (t
       (indicate-subcommand-pending-state-for-text-cell
	 cell subcommand-menu pending? just-remove-indicator?
	 row-index column-index))))))

(defun indicate-subcommand-pending-state-for-text-cell
    (text-cell subcommand-menu pending? just-remove-indicator?
	       row-index column-index)
  (let* ((color
	   (case (getfq-macro (text-cell-plist text-cell) 'radio-button-status)
	     ((nil)
	      (if pending?
		  highlight-color-for-enabled-pending-subcommands
		  highlight-color-for-enabled-non-pending-subcommands))
	     (off
	      (if pending?
		  highlight-color-for-pending-off-radio-button-subcommands
		  highlight-color-for-non-pending-off-radio-button-subcommands))
	     (on
	      (if
		pending?
		highlight-color-for-pending-on-radio-button-subcommands
		highlight-color-for-non-pending-on-radio-button-subcommands
		))))
	 (text-region
	   (or
	     (loop for subblock being each subblock of subcommand-menu
		   when
		     (and (frame-of-class-p subblock 'text-region)
			  (=f (row-index-for-text-region-cell? subblock)
			      row-index)
			  (=f (column-index-for-text-region-cell? subblock)
			      column-index))
		     return subblock)
	     (unless just-remove-indicator?	; special case! -- see Note X
	       (make-text-region
		 subcommand-menu text-cell 1 0 'end nil color)))))
    (cond
      (just-remove-indicator?			; special case! -- see Note X
       (when text-region
	 (delete-frame text-region)))
      (t
       (change-color-of-text-region text-region color)))))

;; Note X -- removing the indicator, instead of changing its color to
;; "transparent", has to be done because changing a text region color after
;; the background of a table has changed causes turds.  See also the draw
;; method for text regions in TABLES.  This should really be fixed -- it
;; should avoid constantly creating and deleting text regions!! (MHD 8/15/90)


(defun indicate-subcommand-pending-state-for-block-cell
    (cell subcommand-menu pending? just-remove-indicator?
	  row-index column-index)
  (declare (ignore  subcommand-menu row-index column-index))
  (frame-class-case cell
    (icon-cell
      (let ((first-icon-cell-subblock? (first-subblock cell)))
	(cond
	  ((and first-icon-cell-subblock?
		(frame-of-class-p first-icon-cell-subblock? 'button))
	   (indicate-editor-subcommand-button-pending-state
	     first-icon-cell-subblock? pending? just-remove-indicator?))
	  (t
	   (dwarn
	     "unhandled here: icon-cell subblock (~a)"
	     first-icon-cell-subblock?)))))
    (t
      (dwarn
	"unhandled here: this class of block as table cell (~a)"
	cell))))

;; Add support for other cases here as needed.





;;;; New Subcommand State




;;; `Subcommand state' is established when a mouse down occurs on a subcommand
;;; menu.  It tracks the mouse maintaining a indication of any pending command
;;; the mouse happens over.  It then invokes that command if the mouse is
;;; released over the choice.

(define-workstation-context subcommand ()
  :selection-style top-level-with-mouse-tracking-is-selection-style
  :parent nil
  :modal t
  :constructor (make-subcommand-state
		 (subcommand-menu-for-subcommand-state
		   specific-image-plane-for-subcommand
		   selected-subcommand-menu-cell))
  :state-variables (subcommand-menu-for-subcommand-state
		     specific-image-plane-for-subcommand
		     selected-subcommand-menu-cell)
  :keymap ((<mouse-up> mouse-up-in-subcommand-state)
	   (<mouse-motion> mouse-motion-in-subcommand-state)
	   (<standard-abort-keys> abort-workstation-context)))



;;; `Valid-workstation-context-p on subcommand-state' checks that the subcommand
;;; menu still exists.  This method refinement is necessary since we don't
;;; focus on the subcommand-menu.  I wish, I knew why not?

(def-structure-method valid-workstation-context-p (subcommand-state)
  (and (funcall-superior-method subcommand-state)
       (valid-block-in-workstation-context-p
	 (subcommand-menu-for-subcommand-state subcommand-state)
	 subcommand-state)))



;;; The `clean-up-workstation-context on subcommand-state' assures that the
;;; pending command highlighting is removed from the any button.  By putting it
;;; in the cleanup we can avoid worring about it in the abort and mouse up
;;; cases.

(def-structure-method clean-up-workstation-context (subcommand-state)
  (let* ((subcommand-menu (subcommand-menu-for-subcommand-state subcommand-state))
	 (subcommand-text-cell (selected-subcommand-menu-cell subcommand-state)))
    (when (and (valid-block-in-workstation-context-p
		 (subcommand-menu-for-subcommand-state subcommand-state)
		 subcommand-state)
	       (subcommand-enabled-p subcommand-text-cell subcommand-menu))
      (indicate-subcommand-pending-state subcommand-menu subcommand-text-cell nil)))
  (funcall-superior-method subcommand-state))



;;; `Enter-subcommand-context' is called as an event handler when a mouse down
;;; occurs over a subcommand-menu-button-spot and only then.

(define-event-handler enter-subcommand-context
    ((subcommand-menu-button-spot innermost-spot)
     (subcommand-cell cell-of-table)
     (subcommand-menu block-showing-representation)
     image-plane)
  #+development
  (unless (subcommand-menu-button-spot-p subcommand-menu-button-spot)
    (warn "Oh no precondition of enter subcommand-context broken!")
    (break))
  (enter-context-in-current-workstation
    'subcommand
    (make-subcommand-state subcommand-menu image-plane subcommand-cell))
  (indicate-subcommand-pending-state subcommand-menu subcommand-cell t))



;;; `Mouse-motion-in-subcommand-state' is just that and updates the
;;; pending command and the indications of same on the screen.

(define-event-handler mouse-motion-in-subcommand-state
    ((subcommand-state workstation-context-specifics)
     &optional
     (table-cell? cell-of-table))
  (let ((subcommand-menu
	  (subcommand-menu-for-subcommand-state subcommand-state))
	(subcommand-menu-cell
	  (selected-subcommand-menu-cell subcommand-state)))
    (indicate-subcommand-pending-state
      subcommand-menu subcommand-menu-cell
      (eq table-cell? subcommand-menu-cell))))



;;; `Mouse-up-in-subcommand-state' calls mouse-motion-in-subcommand-state and
;;; exits the state.  If a pending command exists it executes it, note that
;;; the cleanup method removes the indication of the pending state.

(define-event-handler mouse-up-in-subcommand-state
    (mouse-pointer
      (subcommand-state workstation-context-specifics)
      &optional
      (table-cell? cell-of-table)
     (text-cell-of-button? text-cell-of-table))
  ;; Synchronize the mouse.
  (mouse-motion-in-subcommand-state mouse-pointer)
  ;; Do the command if we have one.
  (let* ((subcommand-menu
	   (subcommand-menu-for-subcommand-state subcommand-state))
	 (subcommand-menu-cell
	   (selected-subcommand-menu-cell subcommand-state))
	 (do-it? (if text-cell-of-button?
		     (eq text-cell-of-button? subcommand-menu-cell)
		     (eq table-cell? subcommand-menu-cell)))
	 (command-function? (subcommand-function? subcommand-menu))
	 (function-arglist? (subcommand-function-arglist? subcommand-menu))
	 (button-info  ; must be a symbol, will be returned from context
	   (if text-cell-of-button?
	       (getf (text-cell-plist text-cell-of-button?) 'special-case?)
	       (if (and table-cell?
			(cell-is-block-p table-cell?)
			(frame-of-class-p table-cell? 'icon-cell))
		   (let ((s (first-subblock table-cell?)))
		     (if (and s
			      (frame-of-class-p s 'editor-subcommand-button))
			 (get-slot-value ; fwd. ref.
			   s 'editor-subcommand-name)))))))
    (cond
      (do-it?
	  (return-from-current-workstation-context
	   'subcommand subcommand-menu button-info)
	  ;; New: no longer return function-arglist? -- too hard to
	  ;; get reclamation right, and never used. (MHD 2/29/00)
	;; This ought to be in the continuation!
	(when command-function?
	  (apply
	    command-function? subcommand-menu button-info function-arglist?)))
      (t
       (abort-current-workstation-context 'subcommand)))))



;;;; Editor Subcommands



(defun make-edit-subcommand-menu ()
  (let ((choices
	  (nconc
	    (get-edit-subcommand-menu-core-choices)
	    (get-KFEP-edit-subcomand-choices-if-appropriate)
	    (get-HFEP-edit-subcomand-choices-if-appropriate)
	    (get-cfep-edit-subcomand-choices-if-appropriate))))
    (make-subcommand-menu choices (font-for-editing fonts))))


#+unused
(defun-simple current-language-for-editor-if-legal ()
  (or (specific-natural-language-for-editor? ; overrides (current-language)
	current-edit-state)      
      (let ((current-language (current-language)))
	(if (or (and kfep-capability? (eq current-language 'japanese))
		(and hfep-capability? (eq current-language 'korean)))
	    current-language))))


(defparameter edit-operation-subcommand-names
  '(cut copy paste delete insert move cut-and-insert))

(defparameter edit-operation-subcommand-names-after-removals
  '(paste))

(defparameter basic-core-edit-subcommand-choices
  '(cancel undo redo end update))

(defparameter core-edit-subcommand-choices
  (nconc
    (copy-list basic-core-edit-subcommand-choices)
    edit-operation-subcommand-names))

(defparameter core-edit-subcommand-choices-after-removals
  (nconc
    (copy-list basic-core-edit-subcommand-choices)
    edit-operation-subcommand-names-after-removals))

(defun get-edit-subcommand-menu-core-choices ()
  (copy-and-translate-subcommand-choice-symbol-list
    (if (buttons-for-edit-operations editor-parameters)
	core-edit-subcommand-choices
	core-edit-subcommand-choices-after-removals)))


(defparameter kfep-edit-subcommand-choices
  '(kanji katakana hiragana english
    convert next previous skip
    accept expand shrink))

(defun get-kfep-edit-subcomand-choices-if-appropriate ()
  ;; Only for the KFEP:
  (if (eq (natural-language-for-editor? current-edit-state) 'japanese)
      (copy-and-translate-subcommand-choice-symbol-list
	kfep-edit-subcommand-choices)))


(defparameter hfep-edit-subcommand-choices
  '(english hangul))

(defun get-hfep-edit-subcomand-choices-if-appropriate ()
  ;; Only for the HFEP:
  (if (eq (natural-language-for-editor? current-edit-state) 'korean)
      (copy-and-translate-subcommand-choice-symbol-list
	hfep-edit-subcommand-choices)))


(defparameter cfep-edit-subcommand-choices
  '(english cyrillic))

(defun get-cfep-edit-subcomand-choices-if-appropriate () ; "cyrillic fep"
  ;; Only for the CFEP:
  (if (eq (natural-language-for-editor? current-edit-state) 'russian)
      (copy-and-translate-subcommand-choice-symbol-list
	cfep-edit-subcommand-choices)))



(defun copy-and-translate-subcommand-choice-symbol-list (choice-symbol-list)
  (loop for choice in choice-symbol-list
	collect
	   (translate-subcommand-menu-choice-as-appropriate
	     choice
	     (natural-language-for-editor? current-edit-state))
	using slot-value-cons))



;;; `Built-in-subcommand-menu-choice-translations' is an a-list of the form
;;;
;;;    ( { (language . translations) } )
;;;
;;; where translations is an alist of the form
;;;
;;;    ( { (choice . translation-string) } )
;;;
;;; where translation-string is the translation in that language for choice.
;;;
;;; At present, this contains only translations for the Japanese, Korean, and
;;; Russian languages.

(defparameter built-in-subcommand-menu-choice-translations
  (optimize-constant
    '#.(gensym-encoded-strings-to-text-strings-in-tree
	'((japanese
	   . ((cancel . "\\5u\\65\\5p\\6-\\\"1/\\qh")	; edhitachuushi
	      (undo . "\\\"+c\\o5\\tT\\3u\\yT\\3B") ; sousatorikeshi
	      (redo . "\\\"+c\\o5\\nl\\t.\\l8") ; sousasaijikkou
	      (end . "\\5u\\65\\5p\\6-\\vX\\\"NA") ; edhitashuuryou
	      (update . "\\k|\\|+")

	      ;; Note: cut, copy, delete, insert, move, and cut-and-insert taken
	      ;; from japanese.kl from 5.0 Rev. 2.  Note that move and delete
	      ;; apparently serve both for text and for items. (MHD 3/17/98)
	      (cut . "\\5x\\61\\66")
	      (copy . "\\6!\\6B\\+?")
	      (paste . "\\6H\\+?\\6'\\66")	; "pe-suto" in katakana; should be
					;   #x255a, #x213c, #x2539, #x2548
	      (delete . "\\o6\\wK")
	      (insert . "\\\"+a\\\"9O")
	      (move . "\\T(\\\"8`")
	      (cut-and-insert . "\\5x\\61\\66\\+x\\\"+a\\\"9O")
	      
	      ;; the rest are only used for the KFEP:
	      (kanji . "\\^W\\r$")
	      (katakana . "\\5x\\6-\\5x\\68")	; "katakana" in katakana
	      (hiragana . "\\3]\\3t\\37\\3U")	; "hiragana" in hiragana
	      (english . "\\V_\\im")		; "eigo" in kanji
	      (convert . "\\\"Cl\\^O")	; "henkan" in kanji
	      ;; note: convert/next mutually exclusive
	      (next . "\\sl\\iv\\\"D ")	; "tsugikouho" in kanji
	      (previous . "\\\"+3\\iv\\\"D ")	; "maekouho" in kanji
	      (skip . "\\6'\\5z\\61\\6E")	; "sukippu" in Katakana
	      ;; note: skip/accept mutually exclusive
	      (accept . "\\5o\\5|\\6)\\6E\\66") ; "akusepto" in katakana
	      (expand . "\\\"Cl\\^O\\\">E\\Sz\\[{\\\"30") ; "henkanhan'ikakuchou"
	      (shrink . "\\\"Cl\\^O\\\">E\\Sz\\vz\\y?"))) ; "henkanhan'ishukushou"
	  
	  ;; NOTE: need cut, copy, delete, insert, move, and cut-and-insert from
	  ;; korean.kl and russian.kl!! (MHD 3/17/98)

	  (korean
	   . ((cancel . "\\\"23\\u=")
	      (undo . "\\o^\\WE")		; wrong?!: "Undo \\o^\\WE" 
	      (redo . "\\\"*'\\wp\\b-")
	      (end . "\\\\S")
	      (update . "\\ua\\\",&")

	      (cut . "\\}3\\g^\\bF\\Wo") ; all these but paste imported 
	      (copy . "\\oH\\\\T\\Wo")	;  from korean.kl today. (MHD 3/21/98)
	      (paste . "\\o~\\\")k\\Wo")
	      (delete . "\\\",x\\}_\\Wo")
	      (insert . "\\\\T\\}_\\Wo")
	      (move . "\\\"9s\\\\m\\z~ \\}8\\Wo\\Wo")
	      (cut-and-insert . "\\wg\\\"6u\\gC\\\"<a\\ji\\tw \\\\T\\}i\\])\\Wo")

	      ;; the rest are only used for the HFEP:
	      (english . "\\}(\\lp")
	      (hangul . "\\\"<c\\Wh")))

	  (russian
	   . ((cancel . "\\(>\\(b\\(\\\\(U\\(]\\(X\\(b\\(l")
	      (end . "\\(7\\(P\\(Z\\(^\\(]\\(g\\(X\\(b\\(l")
	      (paste . "\\(2\\(a\\(b\\(P\\(R\\(X\\(b\\(l")
	      (redo . "\\(2\\(^\\(a\\(a\\(b\\(P\\(]\\(^\\(R\\(X\\(b\\(l")
	      (undo . "\\(>\\(b\\(Z\\(P\\(b")
	      (update . "\\(>\\(Q\\(]\\(^\\(R\\(X\\(b\\(l")
	      ;; the rest are only used for the Russian FEP:
	      (english . "\\(0\\(]\\(S\\([\\(X\\(Y\\(a\\(Z\\(X\\(Y")
	      (cyrillic . "\\(:\\(X\\(`\\(X\\([\\([\\(X\\(f\\(P")))))))

;; IMPORTANT NOTE: Verify that these do not need a special binding of
;; Han-interpretation-mode to survive the translation to Unicode.  Also,
;; eventually consider just encoding this in Unicode rather than Gensym
;; character encoding/UTF-G.

;; Russian translations TBD (MHD 7/24/95)
;; DONE. (Added for 4.0 Rev. 2. (MHD 10/6/95))


;; Note, in principle, a user might want to have both Hangul and Kanji front-
;; end processors available at the same time, and it wouldn't be that hard.  The
;; idea is that all the choices from both lists could appear, but the one choice
;; in common, English, would appear once, possibly with both the J.  and K.
;; translations. Consider this as a possible future capability.  (MHD 4/16/94)



;;; `Translate-subcommand-menu-choice' returns the translation string for choice
;;; in language, if there is one.  If not, it returns nil.  Language should be a
;;; symbol, e.g., JAPANESE, KOREAN, etc.
;;;
;;; At present, only built-in translations are possible; see
;;; built-in-subcommand-menu-choice-translations.  --- No longer the case. Now it
;;; will look for a translation from the regular source (see module language)
;;; and if there isn't one, it will then look in the built-in translations.
;;; (ddm 5/9/97)

(defun translate-subcommand-menu-choice (choice language)
  (with-localization-purpose 'button-label
    (translation-for-symbol? choice language)))

(defun use-built-in-subcommand-menu-choice-translation (choice language)
  (cdr
    (assq
      choice
      (cdr
	(assq
	  language
	  built-in-subcommand-menu-choice-translations)))))


(defparameter include-original-choice-in-subcommand-menu-choice-translation?
  #+development t #-development nil)

;; Parameterize in editor or language parameters?!


(defun translate-subcommand-menu-choice-as-appropriate (choice language?)
  (let ((translation?
	 (if language? (or (translate-subcommand-menu-choice choice language?)
			   (use-built-in-subcommand-menu-choice-translation
			     choice language?)))))
    (if translation?
	(slot-value-cons
	  choice
	  (if include-original-choice-in-subcommand-menu-choice-translation?
	      (twith-output-to-text-string
		(let ((temporary-text-string (copy-symbol-name choice :first)))
		  (tformat "~a ~a" temporary-text-string translation?)
		  (reclaim-text-string temporary-text-string)))
	      (copy-text-string translation?)))
	choice)))


;;; `Update-edit-operation-subcommands' ...

(defun update-edit-operation-subcommands (edit-subcommand-menu)
  (unless keep-edit-workspace-hidden-no-matter-what?
    (enable-or-disable-subcommand
      edit-subcommand-menu
      'cut
      (not (text-can-be-cut-within-editor-p)))
    (enable-or-disable-subcommand
      edit-subcommand-menu
      'copy
      (not (text-can-be-copied-within-editor-p)))
    (enable-or-disable-subcommand
      edit-subcommand-menu
      'paste
      (not (text-can-be-pasted-in-current-workstation-p)))
    (enable-or-disable-subcommand
      edit-subcommand-menu
      'delete
      (not (text-can-be-deleted-within-editor-p)))
    (loop with cannot-transfer
	    = (not (text-can-be-transferred-within-editor-p))
	  for command in '(insert move cut-and-insert)
	  do (enable-or-disable-subcommand
	       edit-subcommand-menu command cannot-transfer))))

(defun-void update-edit-operation-subcommands-in-current-editor ()
  (let ((edit-subcommand-menu? (edit-subcommand-menu? current-edit-state)))
    (when edit-subcommand-menu?
      (update-edit-operation-subcommands edit-subcommand-menu?))))


;;; `Disable-text-region-operation-subcommands-in-current-editor' turns off the
;;; edit operations on regions, i.e., cut, copy, delete, etc., but not paste,
;;; since it can operation with or without a selected region of text.  The main
;;; use for this is to disable these subcommand prior to marking text.

(defun disable-text-region-operation-subcommands-in-current-editor ()
  (let ((edit-subcommand-menu? (edit-subcommand-menu? current-edit-state)))
    (when edit-subcommand-menu?
      (loop for command in edit-operation-subcommand-names
	    unless (eq command 'paste)
	      do (enable-or-disable-subcommand edit-subcommand-menu? command t)))))
  



;;; `Initialize-edit-subcommand-menu' ...

(defun initialize-edit-subcommand-menu (edit-subcommand-menu)
  (enable-or-disable-subcommand
    edit-subcommand-menu
    'cancel nil)			; always available
  
  (unless (use-return-key-as-end-key-in-current-editor-p)
    (enable-or-disable-subcommand	; if you can't use the return key
      edit-subcommand-menu		;   to end, enable the END key at
      'end nil))			;   all times
  
  
  (update-edit-operation-subcommands edit-subcommand-menu)
  
  (enable-or-disable-subcommand
    edit-subcommand-menu
    'undo (not (undo-or-redo-edit-possible-p nil)))
  (enable-or-disable-subcommand
    edit-subcommand-menu
    'redo (not (undo-or-redo-edit-possible-p t)))
  (cond
    (kfep-capability?
     ;; If could enter in a kfep mode, then rework this.
     ;; These subcommand buttons are "radio-button subcommands" --
     ;; and we assume here that English is always the starting mode.
     (enable-or-disable-subcommand
       edit-subcommand-menu
       'KANJI nil 'off)
     (enable-or-disable-subcommand
       edit-subcommand-menu
       'KATAKANA nil 'off)
     (enable-or-disable-subcommand
       edit-subcommand-menu
       'HIRAGANA nil 'off)
     (enable-or-disable-subcommand
       edit-subcommand-menu
       'ENGLISH nil 'on)))
  (cond
    (hfep-capability?
     (enable-or-disable-subcommand
       edit-subcommand-menu
       'ENGLISH nil 'on)
     (enable-or-disable-subcommand
       edit-subcommand-menu 'HANGUL nil 'off)))

  (progn				; for Russian
     (enable-or-disable-subcommand
       edit-subcommand-menu
       'ENGLISH nil 'on)
     (enable-or-disable-subcommand
       edit-subcommand-menu 'CYRILLIC nil 'off)))



;;; Enable-or-disable-edit-end-and-update-buttons ...  does nothing if
;;; there is no edit subcommand menu in current-edit-state.
;;;
;;; In editors with return keys (that do newlines) and scroll bars, the END
;;; option is always up.  The END option, in the normal style of editing, and
;;; the UPDATE option, for both styles, are only shown when the cursor is after
;;; the point of something fully parsable (as the goal category).

;;; ...  This updates the UPDATE subcommand to be in the same state as
;;; the END subcommand unless there is a workstation context return
;;; function, in which case it does nothing with UPDATE.

(defun enable-or-disable-edit-end-and-update-buttons (disable-case?)
  (unless keep-edit-workspace-hidden-no-matter-what?
    (let ((subcommand-menu? (edit-subcommand-menu? current-edit-state)))
      (when subcommand-menu?
	(when (use-return-key-as-end-key-in-current-editor-p)
	  ;; don't touch unless return = END
	  (enable-or-disable-subcommand subcommand-menu? 'end disable-case?))
	(when (and (null (old-workstation-context-return-function?
			   current-workstation-context))
		   (not (editing-field? current-edit-state)))	; (MHD 8/31/92)
	  (enable-or-disable-subcommand subcommand-menu? 'update disable-case?))))))

;; The (null (workstation-context-return-function?  ...)) test is an
;; unprincipled kludge; but it happens deals with the problematic cases:
;; new statements and load/save/merge for kbs and other kinds of files.
;; It also happens to disable update on the Inspect command.  Live with
;; this for a while, but watch out for problems!  (MHD 4/30/91)

;; The UPDATE subcommand was just added today; a long time ago LH
;; thought this was a bad idea when I, MHD, suggested it, but I do not
;; remember any strong reason, other than that he did not think it would
;; be that useful or that he worried it would be "confusing".  Since
;; then, we have put in an UPDATE button in the icon editor, and a lot
;; of users (all of GMS's group, for example, plus DWR) have found that
;; they like it a lot, and use it a lot, and are not confused by it, and
;; miss having it in the editor, especially for editing procedures.  We
;; also have a similar button for the sizing dialogs ("Update Now"),
;; which has been successful.  (MHD 4/30/91)
;; --- However, they complain that it's only available when END is
;; available, which is too seldom, i.e., when the cursor is at the end
;; of a complete parse; and they, complain that it would be much more
;; convenient if available as a keystroke, esp. since all of the buttons
;; frequently have to be scrolled off of the screen.  (MHD 8/31/92)

;;; `Do-edit-subcommand' is the called as the continuation of a submenu-state
;;; when invoked from the edit state.

(defun do-edit-subcommand (edit-context)
  (declare (ignore edit-context))
  (with-workstation-context-return-values (subcommand-menu-or-abort-flag subcommand)
    (unless (eq subcommand-menu-or-abort-flag :abort)
      (in-editing-context (specific-structure-for-current-workstation-context)
	(case subcommand
	  (:abort
	   ;; The subcommand menu context unwound.
	   )
	  ;; the next three will enable/disable themselves as
	  ;;   appropriate and remove indications of being
	  ;;   in the pending state along the way
	  ((end update)
	   (setf (type-of-exit-from-edit-context? current-edit-state) 'end-exit)
	   (extend-parsing-as-appropriate 'end nil (eq subcommand 'update)))
	  ((undo redo)
	   (undo-or-redo-edit (eq subcommand 'redo)))
	  (cancel (cancel-editing))
	  (paste (do-paste-within-editor))
	  (cut (do-cut-within-editor))
	  (copy (do-copy-within-editor))
	  (delete (do-delete-within-editor))
	  (insert (do-insert-within-editor))
	  (move (do-move-within-editor))
	  (cut-and-insert (do-cut-and-insert-within-editor))
	  (kanji (enter-kana-conversion-mode nil))
	  (katakana (enter-kana-conversion-mode 'katakana))
	  (hiragana (enter-kana-conversion-mode 'hiragana))
	  (english (exit-kfep-mode-if-necessary)
		   (exit-hangul-input-mode)
		   (exit-cyrillic-input-mode))
	  (hangul (enter-hangul-input-mode))
	  (cyrillic (enter-cyrillic-input-mode))
	  ((convert next) (do-trial-kfep-conversion nil))
	  (previous (do-trial-kfep-conversion t))
	  (skip (skip-kfep-conversion))
	  (accept (accept-kfep-conversion))
	  (expand (expand-or-shrink-kfep-conversion-text-region t))
	  (shrink (expand-or-shrink-kfep-conversion-text-region nil)))))))

;; Maybe do some logic to keep the subcommands highlighted while they are
;; executing and until done and also not to bother unhighlighting when the
;; workspace is about to go away -- e.g. on cancel or end.

;; Consider having a "cycle" command under paste, which would be available
;; immediately after a paste & would mean to replace the last text pasted with
;; the next available (the next most recently copied or cut) scrap.

;; Consider moving all of the cut-and-paste menu options onto the edit subcommand
;; menu.  But cut-and-insert insert is so long, it raises the question of where
;; the menu belongs, since it causes the width to almost double.  Also, popping
;; up near the mouse may be more convenient.

;; Reverse video has been suggested, but then there is no apealling way to
;; highlight when the mouse is down.  If it were put in, it should be done so
;; that there is no highlighting, but that would be more disappointing to
;; some users.  See MHD's aaedit (8/31/89), where this was tried.

;; Have parameters for the colors or metacolors corresponding the enabled,
;; disabled, and pending states of the subcommands!

;; Have the disabled subcommands be invisible before the workspace is put up!
;; Now, you see all of them momentarily until the system disables some.

;; For now, I have tried to minimize the calls for maintenence of subcommand
;; menus -- there is one known problem: if scraps were there before editing
;; started but they all get deleted, the paste option does not get disabled,
;; even though it should.










;;;; Kanji Front-End Processing (KFEP)

(defvar kfep-search-limit-1 50)			; was 5.
(defvar kfep-search-limit-2 100)		; was 25.  -pto 17jul90




;;; The following functions handle KFEP subcommands.
;;;    `enter-kana-conversion-mode'	         NIL (for KANJI), KATAKANA, or HIRAKANA
;;;    `exit-kfep-mode-if-necessary'		 ENGLISH
;;;    `do-trial-kfep-conversion'		 CONVERT, NEXT, or PREVIOUS
;;;    `skip-kfep-conversion'		         SKIP
;;;    `accept-kfep-conversion'		         ACCEPT
;;;    `expand-or-shrink-kfep-conversion-text-region'  EXPAND or SHRINK

;;; These functions assume that the subcommand is applicable in the current edit state.
;;;
;;; Enter-kana-conversion-mode initializes kana-to-kanji converters if
;;; necessary.  This step must be taken before any of the other KFEP subcommands
;;; can be used.  It is possible for it to fail in its attempt based on external
;;; factors: success is signalled by non-nil return value.  Failure results in a
;;; return value of nil.
;;;
;;; Initialization of Katakana and Hiragana converters always succeeds.  This is
;;; indicated by non-nil ascii-to-kana-map, which happens as a result of of an
;;; attempt to initialize kana/kanji conversions (modulo internal errors).
;;; 
;;; However, Kanji converter may fail, e.g., if the dictionaries are
;;; unavailable.  When Kanji initialization fails, the variable
;;; kfep-converters-have-been-initialized? is left nil.
;;;
;;;
;;; NOTE: G2 lacks any provision at present for Kanji dictionaries going once
;;; they have been established.  This needs to be addressed.  This is not a
;;; regression from 3.0.  Consider working on this after the Beta Phase 2
;;; release is out.
;;;
;;; Two ways to go on this: (1) when Kanji is needed, read the entire dictionary
;;; into memory, so it cannot go away, and then close the file -- simplest; (2)
;;; develop robust handling around file access so that files and stream
;;; connections can come and go.
;;;
;;; (MHD 1/20/95)

(defun enter-kana-conversion-mode	 ; KANJI, KATAKANA, or HIRAKANA subcommand
    (kana-conversion-mode?)		; nil (for Kanji), KATAKANA, or HIRAGANA
  (when (or (null ascii-to-kana-map)
	    (and (null kana-conversion-mode?)
		 (null kfep-converters-have-been-initialized?)))
    (initialize-kana-to-kanji-converters))	; does non-trivial iff necessary
  (when (or kana-conversion-mode?
	    kfep-converters-have-been-initialized?)
    ;; Only enter Kanji mode if Kanji converters successfully initialized.
    (delete-kfep-conversion-text-region-if-any t)
    (setf (kana-conversion-mode? current-edit-state) kana-conversion-mode?)
    (set-up-kfep-conversion-text-region
      (cursor-line-index current-edit-state)
      (cursor-character-index current-edit-state)
      nil nil t)
    t))

;; When initializing, at present, a "long operation notification" comes up
;; during the initialization attempt.  And a notify-user message appears
;; indicating success or failure.  Consider changing this, at least not to
;; show the notification.  (MHD 1/20/95)


(defun exit-kfep-mode-if-necessary		; ENGLISH subcommand
       (&optional do-not-extend-parsing?)	; Added arg -- see note below.
  (delete-kfep-conversion-text-region-if-any t)
  (update-kfep-buttons)
  (unless do-not-extend-parsing?
    (extend-parsing-as-appropriate t)))		; have suppress option for change-edit-box?

;; Note: I added the do-not-extend-parsing? arg for the case where this is
;; called from extend-parsing-as-appropriate.  Otherwise, this would uselessly
;; recur on that function.  That may not be fatal, but should be avoided at
;; least for the reason that menus may get flashed needlessly.  Have not
;; reviewed other comment above that says "have suppress option for change-
;; edit-box?". (MHD 8/21/90)



;;; Do-trial-kfep-conversion ...
;;; When arrow-direction? is specified, it should be either LEFT, RIGHT, UP, or
;;; DOWN, and, in that case, previous-case? is ignored.  The arrow-direction? case
;;; also differs in that the conversion choice will not wrap around, e.g. when
;;; doing a right arrow on the last cell in the lowest row.  Finally, arrow-
;;; direction? may ONLY be specified when all of the kfep conversion choices
;;; have been gotton, i.e.
;;;
;;;   (not (eq (cadr (kfep-conversion-choices? current-edit-state)) t))

(defun do-trial-kfep-conversion (previous-case? &optional arrow-direction?)
						; CONVERT, NEXT, or PREVIOUS subcommand
						;   -or- special arrow key case (w/direction)
  (let* ((text-region (kfep-conversion-text-region? current-edit-state))
	 (choices
	   (kfep-conversion-choices? current-edit-state))
	 (number-of-choices (length choices))
	 (choice-index?
	   (kfep-conversion-choice-index? current-edit-state))
	 (new-choice-index?			; only possibly be nil
	   (cond				;   in arrow case
	     ((null choice-index?)
	      0)
	     (arrow-direction?
	      (let ((delta-index?
		      (get-kfep-conversion-choice-index-delta-for-arrow
			arrow-direction?)))
		(if delta-index? 
		    (maxf 0			; maxf unnecessary
			  (+f choice-index? delta-index?)))))
	     (previous-case?
	      (maxf (-f choice-index? 1) 0))	; maxf unnecessary
	     (t (+f choice-index? 1)))))
    (when new-choice-index?
      (if (eq (cadr choices) t)
	  (update-kfep-conversion-choices-as-appropriate	; gets rest of choices
	    nil
	    (line-index-for-free-end-of-text-region text-region)
	    (character-index-for-free-end-of-text-region text-region)
	    t))
      ;; unhighlight old choice, if necessary
      (if choice-index?
	  (highlight-or-unhighlight-kfep-conversion-choice
	    (modf choice-index? number-of-choices)
	    t))
      ;; highlight new choice
      (highlight-or-unhighlight-kfep-conversion-choice
	(modf new-choice-index? number-of-choices)
	nil)
      (if (null choice-index?)
	  (setf (kanji-conversion-original-string? current-edit-state)
		(convert-text-region-to-text-string text-region)))
      (setf (kfep-conversion-choice-index? current-edit-state) new-choice-index?)
      (do-kfep-conversion-edit 
	(nth 
	  (modf new-choice-index? number-of-choices)
	  choices))				; necessary?
      (update-kfep-buttons))))


(defun skip-kfep-conversion ()			; SKIP subcommand
  (let ((text-region (kfep-conversion-text-region? current-edit-state)))
    (set-up-kfep-conversion-text-region
      (line-index-for-free-end-of-text-region text-region)
      (character-index-for-free-end-of-text-region text-region)
      t
      (and (=f (line-index-for-free-end-of-text-region text-region)	; is region empty
	       (line-index-for-fixed-end-of-text-region text-region))
	   (=f (character-index-for-free-end-of-text-region text-region)
	       (character-index-for-fixed-end-of-text-region text-region))))))

(defun accept-kfep-conversion ()		; ACCEPT subcommand
  ;; tell kka program of choice
  (let ()
    (note-kfep-conversion-choice
      "foo"					; FIX!  Original string
      (kfep-conversion-choices? current-edit-state)
      (kfep-conversion-choice-index? current-edit-state)
;    (nth (modf (kfep-conversion-choice-index? current-edit-state)
;	       new-choice-index (length choices))
;	 choices)
      ))
  (set-up-kfep-conversion-text-region
    (line-index-for-free-end-of-text-region
      (kfep-conversion-text-region? current-edit-state))
    (character-index-for-free-end-of-text-region
      (kfep-conversion-text-region? current-edit-state))
    t))

(defun expand-or-shrink-kfep-conversion-text-region  ; EXPAND or SHRINK subcommand
       (expand-case?)
  (when (kfep-conversion-choice-index? current-edit-state)	; abstract as fn?
    (do-kfep-conversion-edit			; restore to original state
      (kanji-conversion-original-string? current-edit-state))
    ;; set choice index to nil, unhighlight choice, update buttons:
    (highlight-or-unhighlight-kfep-conversion-choice
      (modf (kfep-conversion-choice-index? current-edit-state)
	    (length (kfep-conversion-choices? current-edit-state)))
      t)
    (setf (kfep-conversion-choice-index? current-edit-state) nil)
    (update-kfep-buttons))
  (update-kfep-conversion-choices-as-appropriate
    expand-case?))


(defun unconvert-kfep-conversion-text-region ()	; Rubout key when cycling through 
						;   conversion menu
  (when (kfep-conversion-choice-index? current-edit-state)	; nec.?
    (do-kfep-conversion-edit			; restore to original state
      (kanji-conversion-original-string? current-edit-state))
    ;; set choice index to nil, unhighlight choice, update buttons:
    (highlight-or-unhighlight-kfep-conversion-choice
      (modf (kfep-conversion-choice-index? current-edit-state)
	    (length (kfep-conversion-choices? current-edit-state)))
      t)
    (setf (kfep-conversion-choice-index? current-edit-state) nil)
    (update-kfep-buttons))
  (update-kfep-conversion-choices-as-appropriate
    nil
    (line-index-for-free-end-of-text-region
      (kfep-conversion-text-region? current-edit-state))
    (character-index-for-free-end-of-text-region 
      (kfep-conversion-text-region? current-edit-state))))

;; Note the similarity and the amount of common code between the above two
;; functions and the suggestion in the first of these that part of it be
;; abstracted as a function!!  Or have a function named expand-or-shrink-
;; or-convert-kfep-conversion-text-region.  (MHD 9/12/90)




;;; `Update-kfep-buttons' ... always does the right thing.

(defun update-kfep-buttons ()
  (let ((edit-subcommand-menu?
	  (edit-subcommand-menu? current-edit-state))
	(kfep-conversion-text-region?
	  (kfep-conversion-text-region? current-edit-state))
	(kana-conversion-mode?
	  (kana-conversion-mode? current-edit-state))
	(kfep-conversion-choices?
	  (kfep-conversion-choices? current-edit-state))
	(kfep-conversion-choice-index?
	  (kfep-conversion-choice-index? current-edit-state)))
    (cond
      ((and kfep-capability?			; necessary?
	    edit-subcommand-menu?)
       ;; Highlight KANJI button on (if kfep-conversion-text-region?
       ;; (null kana-conversion-mode?)).
       (enable-or-disable-radio-button-subcommand
	 edit-subcommand-menu? 'KANJI
	 (not (if kfep-conversion-text-region?
		  (null kana-conversion-mode?))))
       ;; Highlight KATAKANA button on (if kfep-conversion-text-region?
       ;; (eq kana-conversion-mode? 'KATAKANA)).
       (enable-or-disable-radio-button-subcommand
	 edit-subcommand-menu? 'KATAKANA
	 (not (if kfep-conversion-text-region?
		  (eq kana-conversion-mode? 'KATAKANA))))
       ;; Highlight HIRAGANA button on (if kfep-conversion-text-region?
       ;; (eq kana-conversion-mode? 'HIRAGANA)).
       (enable-or-disable-radio-button-subcommand
	 edit-subcommand-menu? 'HIRAGANA
	 (not (if kfep-conversion-text-region?
		  (eq kana-conversion-mode? 'HIRAGANA))))
       ;; Highlight ENGLISH button on (null kfep-conversion-text-region?).
       (enable-or-disable-radio-button-subcommand
	 edit-subcommand-menu? 'ENGLISH
	 (not (null kfep-conversion-text-region?)))
       (enable-or-disable-subcommand
	 edit-subcommand-menu? 'CONVERT
	 (not (if kfep-conversion-text-region?
		  (and kfep-conversion-choices?
		       (null kfep-conversion-choice-index?)))))
       (enable-or-disable-subcommand
	 edit-subcommand-menu? 'NEXT
	 (not (if kfep-conversion-text-region?
		  (and kfep-conversion-choices?	; don't treat as ring of choices?
		       kfep-conversion-choice-index?))))
       (enable-or-disable-subcommand
	 edit-subcommand-menu? 'PREVIOUS
	 (not (if kfep-conversion-text-region?
		  (and kfep-conversion-choices?
		       kfep-conversion-choice-index?
		       (not (=f kfep-conversion-choice-index? 0))))))
       (enable-or-disable-subcommand
	 edit-subcommand-menu? 'SKIP
	 (not (if kfep-conversion-text-region?
		  (and (null kana-conversion-mode?)
		       (not (and kfep-conversion-choices?
				 kfep-conversion-choice-index?))
		       (not (and (=f (cursor-line-index current-edit-state)
				     (line-index-for-fixed-end-of-text-region
				       kfep-conversion-text-region?))
				 (=f (cursor-character-index current-edit-state)
				     (character-index-for-fixed-end-of-text-region
				       kfep-conversion-text-region?))))))))
       (enable-or-disable-subcommand
	 edit-subcommand-menu? 'ACCEPT
	 (not (if kfep-conversion-text-region?	; same test as NEXT
		  (and kfep-conversion-choices?
		       kfep-conversion-choice-index?))))
       (enable-or-disable-subcommand
	 edit-subcommand-menu? 'EXPAND
	 (not (if kfep-conversion-text-region?
		  (and kfep-conversion-choices?
		       (multiple-value-bind  ; have adjacent position that cursor doesn't precede; nec?
			 (adjacent-line-index? adjacent-character-index?)
			   (find-position-adjacent-to-end-of-kfep-conversion-text-region
			     nil)
			 (and adjacent-line-index?
			      (not (or (<f (cursor-line-index current-edit-state)
					   adjacent-line-index?)
				       (and (=f (cursor-line-index current-edit-state)
						adjacent-line-index?)
					    (<f (cursor-character-index current-edit-state)
						adjacent-character-index?))))))))))
       (enable-or-disable-subcommand
	 edit-subcommand-menu? 'SHRINK
	 (not (if kfep-conversion-text-region?
		  (and kfep-conversion-choices?
;		       (multiple-value-bind    ; adj. posn. can't precede fixed end
;			 (adjacent-line-index? adjacent-character-index?)
;			   (find-position-adjacent-to-end-of-kfep-conversion-text-region t)
;			 (not (or (<f adjacent-line-index?   ; (and adjacent-line-index? ...)!
;				      (line-index-for-fixed-end-of-text-region
;					kfep-conversion-text-region?))
;				  (and (=f adjacent-line-index?
;					   (line-index-for-fixed-end-of-text-region
;					     kfep-conversion-text-region?))
;				       (<f adjacent-character-index?
;					   (character-index-for-fixed-end-of-text-region
;					     kfep-conversion-text-region?))))))
		       ))))))))



;;; `Set-up-kfep-conversion-text-region' sets up the kfep conversion text region
;;; to begin either (a) at the next hiragana, katakana,
;;; or simple roman alphabetic character at (except when start-past-first-character? is
;;; specified) or past the specified position or (b) at the cursor position, whichever
;;; occurs first.  The text of the old kfep conversion text region, if there was one,
;;; is just left in its present state, whether it has been converted or not.  For
;;; the significance of try-to-expand?, see update-kfep-conversion-choices-as-appropriate.

(defun set-up-kfep-conversion-text-region
    (beginning-line-index beginning-character-index
			  &optional try-to-expand? start-past-first-character?
			  do-not-update-kfep-conversion-choices?)
  (loop with line-index?			; abstract as search function?
	with character-index?
	with character?
	with text-tail?
	  = (find-text-tail-for-line
	      (text-being-edited current-edit-state) beginning-line-index)
	while
	(and (multiple-value-setq
		 (line-index? character-index? text-tail?
			      character?)
	       (find-next-character-if-any
		 beginning-line-index beginning-character-index text-tail?))
	     (not				; cursor does not precede position
	       (or (<f (cursor-line-index current-edit-state) line-index?)
		   (and (=f (cursor-line-index current-edit-state) line-index?)
			(<f (cursor-character-index current-edit-state)
			    character-index?))))
	     (or (not (or (alpha-char-pw	            ;   or hiragana code or hyphen
			    character?)
			  (wide-character-member
			    character?
			    allowable-non-alpha-characters-in-kfep-conversions)
			  (wide-character-is-katakana-jis-code-p character?)
			  (wide-character-is-hiragana-jis-code-p character?)))
		 start-past-first-character?))
	do (setq beginning-line-index line-index?)	; changes args
	   (setq beginning-character-index character-index?)
	   (setq start-past-first-character? nil))
  (if (kfep-conversion-text-region? current-edit-state)
      (delete-frame (kfep-conversion-text-region? current-edit-state)))
  (if (not do-not-update-kfep-conversion-choices?)
      (erase-any-kfep-conversion-choices))
  (cond
    ((kfep-conversion-choices? current-edit-state)
     (reclaim-slot-value (kfep-conversion-choices? current-edit-state))
     (setf (kfep-conversion-choices? current-edit-state) nil)
     (cond
       ((kfep-conversion-choice-index? current-edit-state)
	(setf (kfep-conversion-choice-index? current-edit-state) nil)
	(reclaim-slot-value (kanji-conversion-original-string? current-edit-state))
	(setf (kanji-conversion-original-string? current-edit-state) nil)))))
  (setf (kfep-conversion-text-region? current-edit-state)
	(make-kfep-conversion-text-region
	  beginning-line-index beginning-character-index
;	  (kanji-conversion-text-region-highlight-color editor-parameters)
	  default-kanji-conversion-text-region-highlight-color))
  (if (not do-not-update-kfep-conversion-choices?)
      (update-kfep-conversion-choices-as-appropriate try-to-expand?)
      (update-kfep-buttons)))

;;; Consider handling the do-not-update-kfep-conversion-choices? case as a
;;; subfunction.



;;; `Make-kfep-conversion-text-region' makes a new, empty kfep conversion text region
;;; that begins at the specified position and that is to be shown in the specified
;;; color.

(defun make-kfep-conversion-text-region
       (beginning-line-index beginning-character-index text-highlight-bar-color?)
  (make-text-region
    (edit-box current-edit-state) nil
    beginning-line-index beginning-character-index nil nil
    text-highlight-bar-color?))



;;; `Delete-kfep-conversion-text-region-if-any deletes the kfep conversion text
;;; region for the current edit state, if there is one.

;;; This may be used to leave a kana conversion mode temporarily without updating
;;; all menus, as when the edit cursor is moved to the left of the kfep
;;; conversion text region.

(defun delete-kfep-conversion-text-region-if-any
    (&optional do-not-update-menus?)
  (cond
    ((kfep-conversion-text-region? current-edit-state)
     (update-kfep-conversion-choices-as-appropriate	; makes the kfep conversion
       nil					        ;   text region empty
       (line-index-for-fixed-end-of-text-region
	 (kfep-conversion-text-region? current-edit-state))
       (character-index-for-fixed-end-of-text-region
	 (kfep-conversion-text-region? current-edit-state))
       nil do-not-update-menus?)
     (delete-frame (kfep-conversion-text-region? current-edit-state))
     (setf (kfep-conversion-text-region? current-edit-state) nil))))



;;; `Update-kfep-conversion-choices-as-appropriate' tries to update the kfep
;;; conversion text region so that there will be appropriate kfep conversion
;;; choices.  In all cases, the beginning position of the kfep conversion text
;;; region will be retained.  If the kfep conversion text region is changed,
;;; related displays (buttons, menus of choices, etc.) will be updated.  (The
;;; text of the old kfep conversion text region, if there was one, is just left
;;; in its present state, whether it had been converted or not.)

;;; If try-to-expand? is non-nil, a search is conducted for the biggest expanded
;;; text region that (a) has one or more conversion choices and (b) does not
;;; extend beyond the edit cursor.  Such a text region should not contain more
;;; than kfep-search-limit-2 simple characters.  If an end position is specified
;;; (as a position between the text region and the cursor), the search will only
;;; consider expanded text regions that extend beyond that end position.  If the
;;; search is unsuccessful, nothing is changed.

;;; If try-to-expand? is nil and no end position is specified, a search is
;;; conducted for the biggest shrunken text region that has one or more conversion
;;; choices.  If no such text region is found, nothing is changed.

;;; If try-to-expand? is nil and an end position is specified, a search is
;;; conducted for the biggest text region that has one or more conversion choices
;;; and does not extend beyond the specified position.  If no such text region is
;;; found, the kfep conversion text region is made empty.  Displays are always
;;; updated in this case.

;;; A specified end position must not be beyond the edit cursor.

;;; If must-compute-all-choices? is specified, ...

;;; If do-not-update-menus-or-buttons? is specified, category menus, token menus,
;;; and buttons are not updated (though kfep conversion choices will be updated
;;; as appropriate).

(defun update-kfep-conversion-choices-as-appropriate
       (&optional try-to-expand? end-line-index? end-character-index?
	          must-compute-all-choices? do-not-update-menus-or-buttons?)
  ;; If try-to-expand? is true and the kfep conversion text region is empty,
  ;; call set-up-kfep-conversion-text-region to move the region forward, if
  ;; necessary and possible, to start with a hiragana or simple roman alphabetic
  ;; character.
  (let ((text-region
	  (kfep-conversion-text-region? current-edit-state)))
    (if (and try-to-expand?
	     (=f (line-index-for-free-end-of-text-region text-region)
		 (line-index-for-fixed-end-of-text-region text-region))
	     (=f (character-index-for-free-end-of-text-region text-region)
		 (character-index-for-fixed-end-of-text-region text-region)))
	(set-up-kfep-conversion-text-region
	  (line-index-for-fixed-end-of-text-region text-region)
	  (character-index-for-fixed-end-of-text-region text-region)
	  t nil t)))
  (let* ((text-region
	   (kfep-conversion-text-region? current-edit-state))
	 (end-line-index
	   (or end-line-index?
	       (line-index-for-free-end-of-text-region text-region)))
	 (end-character-index
	   (or end-character-index?
	       (character-index-for-free-end-of-text-region text-region)))
	 (line-index-for-new-choices? nil)
	 (character-index-for-new-choices? nil)
	 (new-choices nil))
    #-comment
    (let* ((minimum-number-of-gensym-characters-to-convert 1)
	   (line-index (line-index-for-fixed-end-of-text-region text-region))
	   (character-index (character-index-for-fixed-end-of-text-region text-region))
	   (text-tail
	     (find-text-tail-for-line
	       (text-being-edited current-edit-state) line-index)))
      (if try-to-expand?
	  (loop with line-index?
		with character-index?
		with text-tail?
		as i from 1
		while
		  (and (multiple-value-setq (line-index? character-index? text-tail?)
			 (find-next-character-if-any
			   line-index character-index text-tail))
		       (not			; cursor does not precede position
			 (or (<f (cursor-line-index current-edit-state) line-index?)
			     (and (=f (cursor-line-index current-edit-state) line-index?)
				  (<f (cursor-character-index current-edit-state)
				      character-index?))))
		       ;; character is not a kanji or simple roman alphabetic character!
		       )
		do (if (or (<f end-line-index line-index?)
			   (and (=f end-line-index line-index?)
				(<f end-character-index character-index?)))
		       (if (>f i kfep-search-limit-1)
			   (loop-finish))
		       (incff minimum-number-of-gensym-characters-to-convert))
		   (setq line-index line-index?)
		   (setq character-index character-index?)
		   (setq text-tail text-tail?))
	  (unless (and (=f end-line-index line-index)
		       (=f end-character-index character-index))
	    (setq line-index end-line-index)
	    (setq character-index end-character-index)
	    (setq text-tail
		  (find-text-tail-for-line
		    (text-being-edited current-edit-state) line-index))
	    (unless end-line-index?
	      (multiple-value-setq (line-index character-index text-tail)
		(find-previous-character-if-any
		  line-index character-index text-tail
		  (text-being-edited current-edit-state))))))
      (unless (and (=f line-index (line-index-for-fixed-end-of-text-region text-region))
		   (=f character-index
		       (character-index-for-fixed-end-of-text-region text-region)))
	(let ((text-string?
		(if (null (kana-conversion-mode? current-edit-state))
		    (convert-text-region-to-text-string
		      text-region line-index character-index))))
	  (multiple-value-bind (choices number-of-gensym-characters-to-convert?)
	      (if text-string?
		  (search-for-longest-prefix-with-kfep-word-choices
		    text-string? minimum-number-of-gensym-characters-to-convert
		    (and (not must-compute-all-choices?)
			 ;; text-string? contains exactly one character?
			 )))
	    (cond
	      (choices
	       (setq new-choices choices)
	       (setq line-index-for-new-choices?
		     (line-index-for-fixed-end-of-text-region text-region))
	       (setq character-index-for-new-choices?
		     (character-index-for-fixed-end-of-text-region text-region))
	       (setq text-tail
		     (find-text-tail-for-line
		       (text-being-edited current-edit-state) line-index-for-new-choices?))
	       (loop repeat number-of-gensym-characters-to-convert?
		     do (multiple-value-setq
			  (line-index-for-new-choices?
			   character-index-for-new-choices?
			   text-tail)
			  (find-next-character-if-any
			    line-index-for-new-choices?
			    character-index-for-new-choices?
			    text-tail))))))
	  (if text-string? (reclaim-text-string text-string?))))
      (when (and (null new-choices)
		 (not try-to-expand?)
		 end-line-index?		; for no update on unsuccessful shrink
		 )				;   when no position is specified
	(setq line-index-for-new-choices?
	      (line-index-for-fixed-end-of-text-region text-region))
	(setq character-index-for-new-choices?
	      (character-index-for-fixed-end-of-text-region text-region))))
    #+comment
    ;; FIX TO RETURN FIRST CHOICE ONLY AS APPROPRIATE!!
    ;; DOESN'T HANDLE ALL MODES APPROPRIATELY NOW (8/11/90).
    (let ((text-tail
	    (find-text-tail-for-line
	      (text-being-edited current-edit-state) end-line-index))
	  text-string choices)
      (if try-to-expand?			; old design, with search here
	  (loop while
		  (multiple-value-setq		; may set variables to nil transiently
		    (end-line-index end-character-index text-tail)
		    (find-next-character-if-any
		      end-line-index end-character-index text-tail))
		until				; until cursor precedes position
		  (or (<f (cursor-line-index current-edit-state) end-line-index)
		      (and (=f (cursor-line-index current-edit-state) end-line-index)
			   (<f (cursor-character-index current-edit-state)
			       end-character-index)))
		do (setq text-string
			 (convert-text-region-to-text-string
			   text-region end-line-index end-character-index))
		   (cond
		     ((>f (text-string-length text-string) kfep-search-limit-2)	; ????? was 25
		      (reclaim-text-string text-string)
		      (loop-finish))
		     ((setq choices (compute-kfep-conversion-choices text-string))
		      (if new-choices
			  (reclaim-slot-value new-choices))
		      (setq line-index-for-new-choices? end-line-index)
		      (setq character-index-for-new-choices? end-character-index)
		      (setq new-choices choices)))
		   (reclaim-text-string text-string))
	  (loop with beginning-line-index
		  = (line-index-for-fixed-end-of-text-region text-region)
		with beginning-character-index
		  = (character-index-for-fixed-end-of-text-region text-region)
		as first-time? = t then nil
		while
		  (or (and first-time? end-line-index?)
		      (multiple-value-setq	; may set variables to nil transiently
			(end-line-index end-character-index text-tail)
			(find-previous-character-if-any
			  end-line-index end-character-index text-tail
			  (text-being-edited current-edit-state))))
		until				; until position precedes or is at fixed end
		  (or (<f end-line-index beginning-line-index)
		      (and (=f end-line-index beginning-line-index)
			   (<=f end-character-index beginning-character-index)))
		do (setq text-string
			 (convert-text-region-to-text-string
			   text-region end-line-index end-character-index))
		when (prog1 (setq choices
				  (compute-kfep-conversion-choices text-string))
			    (reclaim-text-string text-string))
		  do (setq line-index-for-new-choices? end-line-index)
		     (setq character-index-for-new-choices? end-character-index)
		     (setq new-choices choices)
		     (return nil)
		finally
		  (cond
		    (end-line-index?
		     (setq line-index-for-new-choices? beginning-line-index)
		     (setq character-index-for-new-choices?
			   beginning-character-index))))))
    (if line-index-for-new-choices?
	(let ((old-choices?
		(kfep-conversion-choices? current-edit-state)))
	  (update-text-region
	    text-region line-index-for-new-choices? character-index-for-new-choices?)
	  (cond
	    (old-choices?
	     (erase-any-kfep-conversion-choices)
	     (reclaim-slot-value old-choices?)
	     (cond
	       ((kfep-conversion-choice-index? current-edit-state)
		(setf (kfep-conversion-choice-index? current-edit-state) nil)
		(reclaim-slot-value (kanji-conversion-original-string? current-edit-state))
		(setf (kanji-conversion-original-string? current-edit-state) nil)))))
	  (setf (kfep-conversion-choices? current-edit-state) new-choices)
	  (put-up-kfep-conversion-choices old-choices?)))
    (unless do-not-update-menus-or-buttons?	; restrict further?
      (update-kfep-buttons))))

;; Try to avoid repeating previously unsuccessful searches herein!  When this is
;; called in change-edit-box, it may well repeat previously unsuccessful efforts
;; to compute kfep conversion choices.   To do this, allow an end position to be
;; specified in the try-to-expand case and interpret it as the least advanced
;; position for the expanded text region, if any.

;; Once the kfep conversion text region has been shrunk, consider not expanding it
;; automatically.  This would require an additional edit state variable, kfep-
;; conversion-text-region-has-been-shrunk? that is set when an attempt is made to
;; shrink the region and which is reset on other calls to update-kfep-conversion-
;; choices-as-appropriate.  (Whether this would be better is not at all clear.)

;; Lower-level functions might be able to do some of the searching that is done
;; here.  However, for reasons of generality and control, it is probably best to
;; have all searching done here.

;; In the try-to-expand case, consider searching from bigger to smaller, since
;; a bigger text region is always preferred.  This would be a very small
;; optimization, however, since it should be rare for more than one expansion of
;; the text region to yield choices.

;; Note that the kfep conversion text region cannot expand past the the edit cursor
;; or shrink if it is empty.



;;;`Put-up-kfep-conversion-choices' ...

(defun put-up-kfep-conversion-choices (old-choices?)
  (let* ((kfep-conversion-choices?
	   (kfep-conversion-choices? current-edit-state))
	 (temporary-information-on-edit-workspace?
	   (temporary-information-on-edit-workspace? current-edit-state))
	 (move-temporary-information?
	   (and temporary-information-on-edit-workspace?
		(if (null old-choices?)
		    kfep-conversion-choices?
		    (null kfep-conversion-choices?)))))
    (if move-temporary-information?
	(erase-any-temporary-information-on-edit-workspace nil))
    (if (and kfep-conversion-choices?
	     (not (eq (cadr kfep-conversion-choices?) t)))  ; not first-choice-only case
	(let ((kfep-conversion-choice-menu
		(make-kfep-conversion-choice-menu kfep-conversion-choices?)))
	  (add-to-workspace
	    kfep-conversion-choice-menu
	    (edit-workspace current-edit-state)
	    (+w (left-edge-of-block (edit-box current-edit-state))
		(workspace-margin current-edit-workspace))
	    (+w (bottom-edge-of-block (edit-box current-edit-state))
		(workspace-margin current-edit-workspace)
		(or (extra-space-to-leave-below-edit-box? current-edit-state)
		    0))
	    t t)
	  ;; highlight the currently converted choice, if any
	  (if (kfep-conversion-choice-index? current-edit-state)
	      (highlight-or-unhighlight-kfep-conversion-choice
		(modf (kfep-conversion-choice-index? current-edit-state)
		      (length (kfep-conversion-choices? current-edit-state)))
		nil))))
    (if move-temporary-information?
	(extend-parsing-as-appropriate t))))



;;; Make-kfep-conversion-choice-menu ...

(defun make-kfep-conversion-choice-menu (kfep-conversion-choices)
  (make-or-reformat-table
    (loop with remaining-choices = kfep-conversion-choices
	  with ideal-number-of-choices-per-row = 7
	  with total-number-of-choices = (length kfep-conversion-choices)
	  with number-of-choices-per-row
	    = (minf total-number-of-choices
		    (maxf ideal-number-of-choices-per-row
			  (ceilingf
			    total-number-of-choices
			    3			; ideal-number-of-choices-per-row
						; for now -- until LH allows there to be an
						;   arbitrary number of rows
			    )))
	  with token-menu-item-format
	    = (get-or-make-format-frame
		(choose-token-menu-item-format-per-system-tables nil)
;		(choose-font-format-per-fonts-table
;		  'token-menu-item-format
;		  'font-for-editing)
		)
	  collect
	    (loop for choice-string in remaining-choices
		  repeat number-of-choices-per-row
		  collect
		    (make-text-cell
		      (convert-text-string-to-text
			(copy-text-string choice-string))
		      token-menu-item-format)
				    using slot-value-cons)
	    into table-rows using slot-value-cons
	  while
	    (setq remaining-choices
		  (nthcdr number-of-choices-per-row remaining-choices))
	  finally (return table-rows))
    'subcommand-menu-table-format nil 'kfep-conversion-choice-menu))




;;; Highlight-or-unhighlight-kfep-conversion-choice ... Index refers to the
;;; position of the choice in the kfep-conversion-choices? slot of the current
;;; edit state, where 0 is the index for the first element (nth 0) of that list.
;;; The menu is arranged so that index increases across row 1, then row 2, and
;;; so on.  This does nothing if a current kfep conversion choice menu cannot be
;;; found, or if index is out of range for the kfep conversion choice menu
;;; currently displayed.

(defun highlight-or-unhighlight-kfep-conversion-choice (index unhighlight-case?)
  (let ((kfep-conversion-choice-menu?
	  (loop for subblock being each subblock of (edit-workspace current-edit-state)
		when (frame-of-class-p subblock 'kfep-conversion-choice-menu)
		  return subblock)))
    (when kfep-conversion-choice-menu?
      (let ((cell?
	      (loop with choice-index-so-far = 0
		    for row in (table-rows kfep-conversion-choice-menu?)
		    thereis (loop for cell in row
				  when (=f index choice-index-so-far)
				    return cell
				  do (incff choice-index-so-far)))))
	(when cell?		     
	  (highlight-or-unhighlight-cell
	    cell? kfep-conversion-choice-menu?
	    'foreground unhighlight-case? 'text-region))))))

;; This highlights using a text region because it looks better for the highlight
;; rectangle on the menu to be the same size as highlight rectangle in the
;; edit box.

;; This assumes that KFEP conversion text regions are strictly of the class
;; text-region.



;;; Get-kfep-conversion-choice-index-delta-for-arrow ... assumes it is called when
;;;
;;;   (kfep-conversion-choice-index? current-edit-state)
;;;
;;; is non-nil.

(defun get-kfep-conversion-choice-index-delta-for-arrow (arrow-direction)
  (let* ((previous-index
	   (modf (kfep-conversion-choice-index? current-edit-state)
		 (length (kfep-conversion-choices? current-edit-state))))
	 (kfep-conversion-choice-menu?
	   (loop for subblock being each subblock of (edit-workspace current-edit-state)
		 when (frame-of-class-p subblock 'kfep-conversion-choice-menu)
		   return subblock)))
    (when kfep-conversion-choice-menu?
      (let* ((table-rows (table-rows kfep-conversion-choice-menu?))
	     (number-of-rows (length table-rows))
	     (number-of-cells-per-row (length (car table-rows))))
	;; We assume that all of the rows have the same number of cells
	;; except for the last row, which may have the same number or less.
	(multiple-value-bind (row-index column-index)
	    (truncatef previous-index number-of-cells-per-row)
	  (case arrow-direction
	    (up
	     (unless (=f row-index 0)
	       (-f number-of-cells-per-row)))
	    (down
	     (unless (=f row-index (-f number-of-rows 1))
	       (if (=f row-index (-f number-of-rows 2))
		   (let ((number-of-cells-in-last-row
			   (length (nth (-f number-of-rows 1) table-rows))))
		     (if (>f column-index (-f number-of-cells-in-last-row 1))
			 (+r (-f number-of-cells-per-row column-index)
			     (-f number-of-cells-in-last-row 1))
			 number-of-cells-per-row))
		   number-of-cells-per-row)))
	    (left
	     (unless (and (=f row-index 0) (=f column-index 0))
	       -1))
	    (right
	     (unless (and (=f row-index (-f number-of-rows 1))
			  (=f column-index
			      (-f (length (nth row-index table-rows)) 1)))
	       1))))))))




;;; `Erase-any-kfep-conversion-choices' ...  This should be called only when there
;;; is a kfep conversion text region.

(defun erase-any-kfep-conversion-choices ()
  (if (kfep-conversion-choices? current-edit-state)
      (delete-subblocks-of-class
	current-edit-workspace 'kfep-conversion-choice-menu)))



;;; `Do-kfep-conversion-edit' ...

(defun do-kfep-conversion-edit (choice-string)
  (let ((text-region (kfep-conversion-text-region? current-edit-state)))
    (change-edit-box
      nil
      (line-index-for-fixed-end-of-text-region text-region)
      (character-index-for-fixed-end-of-text-region text-region)
      (line-index-for-free-end-of-text-region text-region)
      (character-index-for-free-end-of-text-region text-region)
      choice-string nil nil nil 'kfep-conversion)))



;;; `Do-kfep-conversion-edit-from-outside' does exactly the same thing as
;;; do-kfep-conversion-edit,  except that it sets up for editing in the
;;; current workstation context, which is assumed to be an editing context.

(defun do-kfep-conversion-edit-from-outside (choice-string)
  (in-editing-context (specific-structure-for-current-workstation-context)
    (do-kfep-conversion-edit choice-string)
    (accept-kfep-conversion)))

;; Used upon return from a selection context.  See code in module MENUS. (MHD)


;;; `Find-position-adjacent-to-end-of-kfep-conversion-text-region' ...

(defun find-position-adjacent-to-end-of-kfep-conversion-text-region
       (backwards-case?)
  (let* ((line-index				;abstract this?
	   (line-index-for-free-end-of-text-region
	     (kfep-conversion-text-region? current-edit-state)))
	 (character-index
	   (character-index-for-free-end-of-text-region
	     (kfep-conversion-text-region? current-edit-state)))
	 (text-tail
	   (find-text-tail-for-line
	     (text-being-edited current-edit-state) line-index)))
    (if backwards-case?
	(find-previous-character-if-any
	  line-index character-index
	  text-tail (text-being-edited current-edit-state))
	(find-next-character-if-any 
	  line-index character-index text-tail))))





;;;; Parsing Without the Editor



;;; This section is somewhat experimental.  It's also great for
;;; doing context sensitive prompting using G2's grammars without
;;; using G2's editor.  There is an external, rpc-based interface
;;; to this functionality in EVENTS-G2.

;;; As of fall 1997 it's being used as part of Nevada's initial
;;; release to provide the internals of the text editor. (ddm)

;; TO DO:
;;  - nothing outstanding as of 4/14/98


(defvar trace-parsing-context-p nil)
(defvar trace-parsing-context-tokenizing-p nil)


(def-structure (parsing-token
		 #+development (:print-function print-parsing-token))
  (parsing-token-next nil)
  (parsing-token-previous nil)
  (parsing-token-result nil)
  (parsing-token-type-or-prefix-string nil)
  (parsing-token-self-terminating-p nil)
  (parsing-token-incomplete-phrases nil)
  (parsing-token-start-index nil)
  (parsing-token-end-index nil)
  (parsing-token-incomplete-text nil)
  (parsing-token-menus nil)
  (parsing-token-is-valid-end-p nil)
  (parsing-token-ordinal-index nil))
			   
#+development
(defun print-parsing-token (parsing-token stream depth)
  (declare (ignore depth))
  (let ((previous? (parsing-token-previous parsing-token))
	(incmpl (parsing-token-incomplete-text parsing-token)))
    (printing-random-object (parsing-token stream)
      (format stream
	      (if incmpl
		  "TOKEN ~a/~a ~a-~a ~S incmpl=~s "
		  "TOKEN ~a/~a ~a-~a ~S completed=~s ")
	      (parsing-token-ordinal-index parsing-token)
	      (if previous?
		  (parsing-token-ordinal-index previous?)
		  "nil")	      
	      (parsing-token-start-index parsing-token)
	      (parsing-token-end-index parsing-token)
	      (parsing-token-type-or-prefix-string parsing-token)
	      (or incmpl
		  (parsing-token-result parsing-token))))))


(defun parsing-token-incomplete-p (parsing-token)
  (if (and (null (parsing-token-result parsing-token))
 	   (null (parsing-token-type-or-prefix-string parsing-token)))
      (not (parsing-token-self-terminating-p parsing-token))
      
      (if (parsing-token-incomplete-phrases parsing-token)
 	  nil ; if it's been through the parser, it had to be complete
 	  
 	  (or (text-string-p (parsing-token-type-or-prefix-string parsing-token))
 	      (not (parsing-token-self-terminating-p parsing-token))
	      (not (unambiguous-parsing-token-p parsing-token)))))) ; note

;; Note: This check is particularly motivated by instances of the ']'
;; character which is intrinsically ambiguous in G2 and cannot be
;; disambiguated within the tokenizer by the means that are used in the
;; 'classic' driver for the parser because this driver does not maintain
;; all the same data structures.



;;; These four globals are holders of scratch data that is populated
;;; from the parsing context by a binding in advance-parsing-context.

(defvar current-parsing-context-text nil)
(defvar current-parsing-context-text-length nil)
(defvar current-parsing-context-line nil)
(defvar current-parsing-context-character nil)




(def-structure (parsing-context
		 (:include edit-state)
		 (:reclaimer reclaim-parsing-context-1)
		 #+development (:print-function print-parsing-context))
  (parsing-context-start-token nil)
  (parsing-context-end-token nil)
  (parsing-context-cursor-token nil)
  (parsing-context-position-in-cursor-token nil)
  (parsing-context-error-index nil) ; first ellipsis like behavior
  (parsing-context-text-length nil)
  (parsing-context-token-count 0)   ; note A.
  (parsing-context-text-string #w""))

#+development
(defun print-parsing-context (context stream depth)
  (declare (ignore depth))
  (printing-random-object (context stream)
    (format stream "PARSING-CONTEXT for ~A len=~d "
	    (frame-being-edited? context)
	    (parsing-context-text-length context))))

;; Note A.  The purpose of the token count is to aid in debugging.
;; As characters are added to the incomplete token at the cursor position,
;; This code continually generates new tokens rather than extend the
;; ones it has. By giving each token a unique `ordinal-index' that is
;; the current value of the token-count at the time it is created,
;; we can keep track of what's going on. This number always increases.



;;; These are needed for a forward reference from instance-of-category-acceptable-p
;;; in parse.

(defun parsing-context-cursor-token-function (pc)
  (parsing-context-cursor-token pc))

(defun parsing-token-incomplete-phrases-function (pt)
  (parsing-token-incomplete-phrases pt))

(defun-simple incomplete-phrases-for-previous-token ()
  (if (parsing-context-p current-edit-state)
      (parsing-token-incomplete-phrases (parsing-context-cursor-token current-edit-state))
      (car (stack-of-incomplete-phrases-at-earlier-positions current-edit-state))))




(defmacro within-parsing-context ((pc) &body body)
  `(let ((current-edit-state ,pc))
     ,@body))


(defmacro parsing-context-setf-reclaiming-old-text-string (pc new-string)
  `(progn
     (when (not (string-equalw (parsing-context-text-string ,pc) #w""))
       (reclaim-text-string (parsing-context-text-string ,pc)))
     (setf (parsing-context-text-string ,pc) ,new-string)))

;;macro parsing-context-setf-reclaiming-old-text-string created because there
;;ended up being too danged many places in the new API and I got tired of the
;;code duplication.  --yduJ, 12/04


(defun delete-parsing-context (parsing-context)
  (clean-up-workstation-context parsing-context))

#+obsolete
(defun delete-parsing-context-if-any (thing)
  (when thing
    (delete-parsing-context thing)))

(def-structure-method clean-up-workstation-context (parsing-context)
  (let ((current-edit-state parsing-context))
    (let ((first-token-incomplete-phrases
	  (parsing-token-incomplete-phrases
	  (parsing-context-start-token parsing-context))))
      (when first-token-incomplete-phrases
	#+development
	(when (cdr first-token-incomplete-phrases)
	  (cerror "go on" "too many incomplete phrases in first token"))
	(reclaim-phrase-rule-completions
	  (phrase-rule-completions (car first-token-incomplete-phrases)))))
	(loop while (parsing-context-cursor-token parsing-context)
	      do
	  (remove-token-from-parsing-context parsing-context)))
  (funcall-superior-method parsing-context))

;;Old comment from original caller in g2-update-parsing-context in events-g2:
      ;; We're getting the entire text with each call rather than
      ;; increments, and it's a new string each time so we have to
      ;; reclaim the old one. If we see that the 'old one' is actually
      ;; the initial value for this field, #w"" the empty string, then
      ;; we know that no changes have been made and we don't reclaim
      ;; it because that string was burned into the code and we'd
      ;; corrupt the code if we did. (Alternatively we could always
      ;; copy the #w"", but I like this. ddm 4/24/98)

(defun reclaim-parsing-context (parsing-context)
  (when (not (string-equalw (parsing-context-text-string parsing-context) #w""))
    (reclaim-text-string (parsing-context-text-string parsing-context)))
  ;; GENSYMCID-1552: Suspected memory leak in system procedure g2-validate-parsing-text
  (clean-up-workstation-context parsing-context))


(defmacro set-frame-being-edited (parsing-context item)
  (avoiding-variable-capture (parsing-context item)
    `(progn
       (setf (frame-being-edited? ,parsing-context) ,item)
       (frame-serial-number-setf (serial-number-of-frame-being-edited?
				   ,parsing-context)
				 (frame-serial-number ,item)))))



(defun-simple parsing-context-p-function (thing)
  (parsing-context-p thing))




(defun add-token-to-parsing-context (new-token pc)
  (cond ((parsing-context-start-token pc)
	 (let ((cursor-token (parsing-context-cursor-token pc))
	       (new-index (incff (parsing-context-token-count pc)))) 
	   (setf (parsing-token-next cursor-token) new-token)
	   (setf (parsing-token-previous new-token) cursor-token)
	   (setf (parsing-token-ordinal-index new-token) new-index)
	   (setf (parsing-context-cursor-token pc) new-token)))
	(t
	 (setf (parsing-token-ordinal-index pc)
	       (parsing-context-token-count pc)) ; i.e. 0
	 (setf (parsing-context-start-token pc) new-token)
	 (setf (parsing-context-cursor-token pc) new-token))))



;;; `Remove-token-from-parsing-context' pops the rightmost, 'cursor' token
;;; from the chain of tokens and reclaims it. The previous token becomes
;;; the new cursor token. This routine has no preclusions against removing
;;; the context's start token, so it should be used carefully. See, e.g.,
;;; clear-parsing-context. 

(defun remove-token-from-parsing-context (pc)
  (let ((cursor-token? (parsing-context-cursor-token pc)))
    (when cursor-token?
      (let ((previous-token
	      (parsing-token-previous cursor-token?)))
	(when previous-token
	  (setf (parsing-token-next previous-token) nil))
	(setf (parsing-context-cursor-token pc) previous-token))
      (reclaim-parsing-token-and-accompanying-data cursor-token?))))


(defun reclaim-parsing-token-and-accompanying-data (token)
  (when (parsing-token-incomplete-text token)
    (reclaim-text-string (parsing-token-incomplete-text token)))
  (when (parsing-token-menus token)
    (reclaim-grammar-tree (parsing-token-menus token)))
  (setf (parsing-token-menus token) nil)
  (reclaim-parsing-token token))


#+development
(defun print-token-list (pc)
  (unless (free-text-slot-being-edited? pc)
    (let ((start-token (parsing-context-start-token pc)))
      (loop for token = (parsing-token-next start-token)
		      then (parsing-token-next token)
	    while token
	    do (print token)))))



;;; `clear-parsing-context' recreates the state that occurred just after the
;;; parsing context was created by reclaiming all of the tokens, etc. except
;;; for the very first.  It also reclaims the string.  Sometimes we want to
;;; leave the string alone, so we separate out `clear-parsing-tokens' -- yduJ
;;; 2/3/04

(defun clear-parsing-tokens (pc)
  (unless (free-text-slot-being-edited? pc)
    (let ((start-token (parsing-context-start-token pc)))
      (loop for token = (parsing-token-next start-token)
		      then (parsing-token-next token)
	    while token
	    do (progn
		 #+development (when trace-parsing-context-p
				 (format t "~&  Reclaiming ~a~%" token))
		 (reclaim-parsing-token-and-accompanying-data token)))
      (setf (parsing-context-cursor-token pc) start-token)
      (setf (parsing-context-text-length pc) 0)
      (setf (parsing-context-token-count pc) 0)
      (setf (parsing-context-error-index pc) nil)
      (setf (parsing-token-next start-token) nil))))


(defun clear-parsing-context (pc)
  (clear-parsing-tokens pc)
  (parsing-context-setf-reclaiming-old-text-string pc #w""))





(defun create-parsing-context
    (&optional
     class? slot-name?
     type-of-slot?
     slot-component-name? slot-component-indicator?)
  
  (unless (or type-of-slot?
	      (and class? slot-name?))
    (return-from create-parsing-context nil))
	      
  (let* ((class-description? (class-description class?))
	 (slot-description?
	   (and class-description?
		slot-name?
		(get-slot-description-of-class-description
		  slot-name? class-description?)))
	 (type-of-slot
	   (or type-of-slot?
	       (if class-description?
		   (feature-assq
		     'type
		     (if slot-component-name?
			 (get-slot-component-features
			   slot-name?
			   nil   ; the defining-class? parameter
			   slot-component-name?)
			 (slot-features slot-description?)))
		   '(type free text))))
	 (edit-state
	   (let ((es (make-parsing-context)))
	     
	     (setf (defining-class-for-slot-being-edited? es) nil)
	     ;; Joe figures this can't be germane for an edit so we're
	     ;; nil'ing it out to avoid ossifying something we don't need
	     ;; ddm 1/5/98

	     (setf (name-of-slot-being-edited es) slot-name?)
	     (setf (type-of-slot-being-edited es) type-of-slot)

	     (setf (name-of-slot-component-being-edited? es)
		   slot-component-name?)
	     (setf (indicator-of-slot-component-being-edited? es)
		   slot-component-indicator?)
	     
	     (setf (free-text-slot-being-edited? es)
		   (free-text-slot-type-p type-of-slot))
	     ;; note that this is also the default if there's no text-type
	     
	     ;; these were just copied over from the classic
	     (setf (specific-natural-language-for-editor? es)
		   (get-natural-language-for-editor
		     editor-specific-natural-language-override?))
	     (setf (natural-language-for-editor? es)
		   (or editor-specific-natural-language-override?
		       (current-natural-language-for-editor)))
	     es))
	 
	 (current-edit-state edit-state))

    (cond
      ((free-text-slot-being-edited? current-edit-state)
       (initialize-parser-state-for-free-text))
      (t
       (initialize-parser-state-for-current-parsing-context type-of-slot)))

    edit-state))



(defun initialize-parser-state-for-current-parsing-context (type-of-slot)
  (let ((irrelevant-category
	  (with-current-grammar-for-current-edit-state
	    (get-or-make-category-for-category-symbol 'irrelevant)))
	(initial-token (make-parsing-token)))
    (setf (phrase-rule-completions-past-instance-of-category
	    current-edit-state)
	  (grammar-list
	    (make-phrase-rule-completion
	      irrelevant-category irrelevant-category nil)))
    (setf (parsing-context-token-count current-edit-state) 0)
    (setf (parsing-token-self-terminating-p initial-token) t)
    (setf (parsing-token-start-index initial-token) 0)
    (setf (parsing-token-end-index initial-token) 0)
    (setf (parsing-token-ordinal-index initial-token) 0)
    (setf (parsing-token-incomplete-phrases initial-token)
	  (phrase-cons
	    (make-incomplete-phrase	 ; initial incomplete phrase
	      (grammar-list
		(make-phrase-rule-completion
		  irrelevant-category
		  (with-current-grammar-for-current-edit-state
		    (get-or-make-category-for-category-symbol
		      (category-symbol-given-slot-type type-of-slot)))
		  (phrase-rule-completions-past-instance-of-category
		    current-edit-state)))
	      nil
	      nil)
	    nil))
    (setf (parsing-context-text-length current-edit-state) 0)
    (setf (parsing-context-text-string current-edit-state) #w"")
    (add-token-to-parsing-context initial-token current-edit-state)))


(defun initialize-parser-state-for-free-text ()
  (setf (parsing-context-text-length current-edit-state) 0)
  (setf (parsing-context-text-string current-edit-state) #w""))


;;; `end-editorless-parsing' is modeled on `try-to-end-editing'.
;;; Many of its subroutines operate on implicit arguments that they
;;; take from the current-editor-context that is established by the
;;; wrapper in the main line of this routine.
;;;
;;; Assuming that the frame still exists and there's no pending error
;;; in the text, this extracts a parse result from the current editor
;;; context, has it compiled, and then has the result of the compilation
;;; concluded into the slot/item indicated by the editor-context.
;;;
;;; If there are no problems, this returns nil. Otherwise it returns
;;; a symbol representing one of the explicitly checked for problems
;;; or a string returned by the slot-compiler that describes the
;;; problem that it found.

(defun end-editorless-parsing (pc frame editing-for-runtime-change-p)
  (cond
    ((and (framep frame) (not (frame-in-use-p frame)))
     'frame-is-null-or-reprocessed)
    ((parsing-context-error-index pc)
     'parse-is-bad)
    (t
     (within-parsing-context  (pc)	  
       (let* ((editing-free-text? (free-text-slot-being-edited? pc))
	      (parse-result-or-marker (unless editing-free-text?
					(extract-parse-result pc))))
	 (cond
	   ((eq parse-result-or-marker 'text-is-incomplete)
	    'parse-is-incomplete)
	   ((eq parse-result-or-marker 'ambiguous-phrase)
	    'parse-is-ambiguous)
   (t
    ;; Fill in more of the edit state given the parameters
    (set-frame-being-edited pc frame)
    (setf (editing-for-runtime-change? pc)
	  editing-for-runtime-change-p)

    ;; Convert the string (a copy of the entire text -- updated with
    ;; each rpc that indicates an edit or a shift in cursor position)
    ;; to a text. Texts are what the classic editor uses, and are what
    ;; the downstream processes will expect to see in the text slot of
    ;; the object. We make a copy because we may continue editing after
    ;; this and the parsing-context-text-string field is reclaimed with
    ;; each update. 
    (setf (text-being-edited pc)
	  (convert-text-string-to-text
	    (copy-text-string (parsing-context-text-string pc))))
    
    (let ((text-of-definition-being-compiled
	    (text-being-edited pc)) ; see note 1.
	  (new-value-or-bad-phrase nil)
	  (explanatory-text-string-if-does-not-compile? nil))
      
      ;; Wrap a (recording-items-made-incomplete ('edit) ...)
      ;; around this once we're prepared to offer to recompile
      ;; items made inconsistent by this conclude. Note that
      ;; the global items-made-incomplete-were-recorded? will then
      ;; have to be managed.

      (unless editing-free-text?
	(multiple-value-setq (new-value-or-bad-phrase
			      explanatory-text-string-if-does-not-compile?)
	  (compile-for-current-edit-state
	    parse-result-or-marker
	    (get-slot-value-compiler-for-current-edit-state-if-any)
	    nil))  ; the just-update? arg -- see note with end-editorless-
	           ; parsing-install-compiled-result
	     
	#+development (when trace-parsing-context-p
	  (format t "~2%Parse result = ~a~%" parse-result-or-marker)
	  (if explanatory-text-string-if-does-not-compile?
	      (format t "~%  It did not compile:~%\"~a\"~%"
		      explanatory-text-string-if-does-not-compile?)
	      (format t "~%Value after compilation: ~a~%"
		      new-value-or-bad-phrase))
	  (format t "Text = \"~a\"" (text-being-edited pc))))
	   
      (cond
	((and (eq new-value-or-bad-phrase bad-phrase)
	      (not (text-being-edited-may-have-no-value-p)))
	 explanatory-text-string-if-does-not-compile?)
	(t
	 (install-current-edit-state-compiled-result
	   (if (or (eq new-value-or-bad-phrase bad-phrase)
		   editing-free-text?)
	       no-value
	       (copy-for-slot-value new-value-or-bad-phrase))
	   nil  ; just-update?  Note 2.
	   t)))))))))))   ; no-editor?


;; Note 1. `text-of-definition-being-compiled' is a global that is used in
;; just one place (as of 12/2/97 -ddm): add-md5-identifier, which applies
;; only to procedures that are being in-lined.

;; Note 2. When working with the editor, the new-value argument to
;; change-slot-description-value for the case of text slot-types is
;; sensitive to the parameter just-update? that accompanied the
;; editor-based version of this routine. All that did, however,
;; was govern a side-effect on the box-translation-and-text field
;; of the editor's edit-box and guard against corruption if there
;; was a posibility the text being edited was going to change.
;; See make-text-value-using-current-edit-state. Here we know that
;; is not the case, and can short circuit the original calculation.





;;; What `advance-parsing-context' does and how it interprets the string
;;; that it receives as its argument depends on whether the cursor token is
;;; incomplete. If it is, then the string is assumed to be the continuation
;;; of that toke plus the text of any additional tokens that follow it.
;;;
;;; When the cursor token is incomplete it will be retokenized, which
;;; entails backing up its starting point (see the two decff's). Since this
;;; value is based on the text-length of the current parsing context care
;;; must be exercised in managing that part of the state during retreats and
;;; clears.

;;; We are always assumed to be adding on to the end of the text even if we
;;; aren't. If characters are being added (= an advance) behind the current
;;; end of the text then we effectively ignore all of the text beyond the
;;; end of the string that has been constructed for us by the caller and
;;; throw away those tokens. As a result, this is an inefficient design for
;;; anything other than creating new expressions where the vast bulk of the
;;; typing is at the end of the text (vs. editing an existing expression
;;; where you could be jumping around anywhere), however I don't know
;;; enough about how the state of the parse is reflected in the token
;;; stream to feel like mucking with this yet. (ddm 11/97)

;; string arg is consumed/absorbed

(defun advance-parsing-context-index (pc new-cursor-position)
  (advance-parsing-context
    pc
    (text-string-substring
      (parsing-context-text-string pc)
      (parsing-context-text-length pc)
      new-cursor-position)))


(defun advance-parsing-context (pc string)
  (within-parsing-context (pc)
    (let ((string-to-tokenize nil)
	  (text-start-index (parsing-context-text-length pc)))

      ;; Decide whether we're extending a partial token or not.
      ;; If so, pop off that token and restart the analysis
      ;; at its start position, backing up indicies as needed.
      (cond
	((and (parsing-context-start-token pc)
	      (parsing-token-incomplete-p
		(parsing-context-cursor-token pc)))
	 #+development (when trace-parsing-context-p
	   (format t "~%Splice case~
                      ~%   cursor token is ~a~%"
		   (parsing-context-cursor-token pc)))
	 (let* ((cursor-token
		  (parsing-context-cursor-token pc))
		(prefix-string  ; reclaimed with the token
		  (parsing-token-incomplete-text cursor-token)))
	   (setf string-to-tokenize
		 (twith-output-to-text-string
		   (twrite prefix-string)
		   (twrite string)))
	   #+development (when trace-parsing-context-p
	     (format t "prefix=~s extension=~s string-to-tokenize ~s~%"
		     prefix-string string string-to-tokenize))
	   (decff text-start-index (text-string-length prefix-string))
	   (decff (parsing-context-text-length pc)
		  (text-string-length prefix-string))
	   ;; if the incomplete token retreat is sufficient
	   ;; to clear any existing problems then do so.
	   (when (and (parsing-context-error-index pc)
		      (<f text-start-index
			  (parsing-context-error-index pc)))
	     (setf (parsing-context-error-index pc) nil))
	   (reclaim-text-string string)
	   (remove-token-from-parsing-context pc)))
	(t
	 #+development (when trace-parsing-context-p
	   (format t "~%No ongoing incomplete token.~
                      ~%   cursor-token is ~a~%"
		   (parsing-context-cursor-token pc)))
	 (setq string-to-tokenize string)))

      ;; `string' is "dead" at this point
      #+development (setf string nil)
      
      ;; Advance the parse
      (when (parsing-context-error-index pc)
	(reclaim-text-string string-to-tokenize)
	(return-from advance-parsing-context
	  (values 'after-error
		 (copy-constant-wide-string #w"cannot parse past previous error"))))
      (let* ((current-parsing-context-text
	       (slot-value-cons string-to-tokenize nil))
	     (current-parsing-context-text-length
	       text-start-index)
	     (current-parsing-context-line 1)
	     (current-parsing-context-character
	       ;; This variable specifies the start position of the first
	       ;; token in the string. Since the string passed in could
	       ;; easily start with whitespace, we have to detect that and
	       ;; shift the value to be that of the first 'real' character.
	       ;; If we don't, the leading space(s) will be incorporated
	       ;; into the token.
	       (if (memq (charw string-to-tokenize 0)
			 alphabet-whitespace-chars)
		   ;; advance over the whitespace
		   (relative-index-of-first-non-whitespace-character
		     string-to-tokenize 0)
		   0)))
	#+development (when trace-parsing-context-p
	  (format t "~&new text=~s starting at ~s~%"
		  current-parsing-context-text 
		  current-parsing-context-text-length))
	
	(multiple-value-bind (parse-status? problem-string)
	    (extend-parsing-context 'end)
	  (unless (memq parse-status? '(parsing-context-complete-status
					so-far-so-good-2
					so-far-so-good-3))
	    (setf (parsing-context-error-index pc)
		  (parsing-token-end-index  ; had been the start index
		    (parsing-context-cursor-token pc))))
	  ;; further use of text-length cannot be done
	  ;; in an error state
	  (incff (parsing-context-text-length pc)
		 (text-string-length string-to-tokenize))
	  (reclaim-slot-value-cons current-parsing-context-text)
	  (reclaim-text-string string-to-tokenize)
	  ;; GENSYMCID-1543: Suspected memory leak in system procedure g2-validate-parsing-text
	  (unless (and (parsing-context-start-token pc)
		       (parsing-token-incomplete-p (parsing-context-cursor-token pc)))
	    (when current-parsing-context?
	      (remove-token-from-parsing-context current-parsing-context?)))
	  (values parse-status? problem-string))))))


(defun relative-index-of-first-non-whitespace-character (string initial-value)
  (loop for index from initial-value
		  to (+f initial-value (lengthw string))
	as indexed-character = (charw string index)
			     then (charw string index)
	when (not (memq indexed-character
			alphabet-whitespace-chars)) ; from ALPHABET
	  return index
	finally
	  ;; We can get here if the string consists entirely of whitespace.
	  ;; We have to return something, so I've decided to return the
	  ;; initial-value. In the situation that motivated this function,
	  ;; which is a sort of 'trim' operation to get the indexes on
	  ;; parser tokens correct, this is a reasonable thing to do.
	  (return initial-value)))





(defun retreat-parsing-context (pc index)
  ;; If there is an error-index in the pc and retreating before it clears
  ;; the error then do the right thing.
  (when (and (parsing-context-error-index pc)
	     (<f index (parsing-context-error-index pc)))
    (setf (parsing-context-error-index pc) nil))
  
  #+development (when trace-parsing-context-p
    (format t "Retreating. new index is ~a~%" index))

  ;; Backoff as many tokens as needed to get to the new position
  ;; of the index.
  (cond
    ((<=f index 0)
     ;;back to zero -- do it the quick way.  This leaves the string intact but
     ;;removes all the tokens.
     (clear-parsing-tokens pc))
    (t
     (loop with cursor-token = (parsing-context-cursor-token pc)
	   do
       (progn
	 #+development (when trace-parsing-context-p
	   (format t " cursor token = ~a~
                    ~%    end index = ~a  start index = ~a~%"
		   cursor-token
		   (parsing-token-end-index cursor-token)
		   (parsing-token-start-index cursor-token)))
	 (cond
	   ((>f index (parsing-token-end-index cursor-token))
	    ;;We have retreated to within a token that is strictly prior to our
	    ;;target index -- we can simply advance to create the new token.
	    #+development	    
	    (when trace-parsing-context-p
	      (format t "Done retreating.  Setting text length to ~a~%"
		      (parsing-token-end-index cursor-token)))
	    (setf (parsing-context-text-length pc)
		  (parsing-token-end-index cursor-token))
	    (loop-finish))
	       
	   ((<=f index (parsing-token-end-index cursor-token))
	    ;;Target index is either well before or within this token.
	    ;;Pop off this token -- we want to go before it.
	    #+development
	    (when trace-parsing-context-p
	      (format t "Retreating: Popping ~a.~%" cursor-token))
	    (remove-token-from-parsing-context pc)
	    ;;Loop step: update cursor-token variable to match. 
	    (setf cursor-token (parsing-context-cursor-token pc)))))
       
	   finally
	     (progn
	       #+development
	       (when trace-parsing-context-p
		 (format t "Finally, cursor token = ~a~%~
                           index = ~a  start = ~a  end = ~a~%~
                           text = \"~a\"~%" cursor-token
			   index (parsing-token-start-index cursor-token)
			   (parsing-token-end-index cursor-token)
			   (parsing-context-text-string pc)))
	       ;;Retreated before we needed to, advance to reparse the token
	       #+development
	       (when trace-parsing-context-p
		 (format t "Advancing after a retreat:  cursor token ~a, new position ~a~%"
			 cursor-token index))))
	       ;;
     (multiple-value-bind (parse-status gripe)
	 (advance-parsing-context-index pc index)
       #+development
       (when trace-parsing-context-p
	 (format t "The new cursor token (after readvance) is ~a.~%"
		 (parsing-context-cursor-token pc)))
       (values parse-status gripe)))))







(defun advance-parsing-context-token-stream ()
  (multiple-value-bind (token-or-other-type-of-result?
			type-of-token-or-prefix-token-string?
		        line-index-for-end-of-token
			character-index-after-token
			text-tail-for-end-of-token?
			token-self-terminating?)
      (get-next-token-from-text-if-available
	g2-comment-tokenizer ;;Tokenizer recognizes rather than skips comments
	1    ; cursor-line-index?
	(text-string-length (car current-parsing-context-text)) ; cursor-character-index?
	current-parsing-context-line      ; line-index
	current-parsing-context-character ; character-index
	current-parsing-context-text      ; text-tail
	t       ;  in-editing-context?
	nil     ;  end-line-index 
	nil)     ;  end-character-index
;	t)      ;  value-for-return-partial-tokens?
    ;; If the value-for-return-partial-tokens? argument is omitted, it defaults
    ;; to whatever the value of cursor-line-index? is. 
    
    #-development (declare (ignore text-tail-for-end-of-token?))
    
    #+development (when trace-parsing-context-tokenizing-p
      (format t "~%~%Output of Get-next-token from-text-if-available:~
                 ~%  token-or-other-type-of-result? = '~a'~
		 ~%  type-of-token-or-prefix-token-string? = ~a~
		 ~%  line-index-for-end-of-token = ~a~
		 ~%  character-index-after-token = ~a~
		 ~%  text-tail-for-end-of-token? = ~a~
		 ~%  token-self-terminating? = ~a~%"
	      token-or-other-type-of-result?
	      type-of-token-or-prefix-token-string?
	      line-index-for-end-of-token
	      character-index-after-token
	      text-tail-for-end-of-token?
	      token-self-terminating?))
    
    ;; make a new parsing token
    (let ((parsing-token (make-parsing-token)))
      (setf (parsing-token-result parsing-token)
	    token-or-other-type-of-result?)
      (setf (parsing-token-type-or-prefix-string parsing-token)
	    type-of-token-or-prefix-token-string?)
      (setf (parsing-token-self-terminating-p parsing-token)
	    token-self-terminating?)

      ;; Compute its start/end indicies n.b. It is important that the
      ;; whitespace to either side of the token be correctly sorted out,
      ;; otherwise the token won't look right to the routines that compute
      ;; the prompts. In the usual case, The default start index as kept in
      ;; current-parsing-context-character is pointing to where the prior
      ;; token ended, consequently we have to skip over the following
      ;; whitespace characters to get the correct start index.  However, in
      ;; the case of the null tokens that are always produced by the
      ;; scanning procedure used in extend-parsing-context (the driver of
      ;; this routine) when we are advancing to the very end of the text,
      ;; the whitespace that may be there is not part of the token and is
      ;; only present to indicate to the tokenizer that the prior token is
      ;; complete (e.g. ".. end "), so we need to disregard it and use
      ;; the end of the prior token as the start index.
      (setf (parsing-token-start-index parsing-token)
	    (+f current-parsing-context-text-length
		(if (null token-or-other-type-of-result?)
		    current-parsing-context-character
		    (relative-index-of-first-non-whitespace-character
		      (car current-parsing-context-text)
		      current-parsing-context-character))))
      (setf (parsing-token-end-index parsing-token)
	    (+f current-parsing-context-text-length
		(or character-index-after-token
		    current-parsing-context-character)))

      ;; Is this token incomplete?
      (unless (and token-self-terminating?
		   ;; these are always complete except for the case of
		   ;; characters that require context before they can be
		   ;; disambiguated such as "]", which we test for with
		   ;; the symbolp check.
		   (symbolp type-of-token-or-prefix-token-string?))
	(when (or (text-string-p type-of-token-or-prefix-token-string?)
		  (text-string-p token-or-other-type-of-result?)
		  (and (null token-or-other-type-of-result?)
		       (null type-of-token-or-prefix-token-string?))
		  (and (consp type-of-token-or-prefix-token-string?)
		       (or (memq 'symbol type-of-token-or-prefix-token-string?)
			   (cdr type-of-token-or-prefix-token-string?))))
	  (setf (parsing-token-incomplete-text parsing-token)
		;; n.b. this substring may be adjusted below.
		(text-string-substring
		  (car current-parsing-context-text)
		  current-parsing-context-character
		  character-index-after-token))))

      (when (parsing-token-incomplete-p parsing-token)
	;; The index that had been used, current-parsing-context-character,
	;; tends to point to the whitespace that followed the prior token,
	;; so we have to strip that off if we're to get the right source
	;; for token prompts.
	(unless (equalw #w"" (parsing-token-incomplete-text parsing-token))
	  ;; Don't do this on the -end of the run- null tokens. There
	  ;; is invariably a bit of whitespace just following the last
	  ;; (real) token, and there was the bug of the start of the
	  ;; null token being one larger than its beginning.
	  
	  ;; n.b. This manipulation on the indicies of incomplete tokens
	  ;; may be unnecessary now that there's a comparable move on
	  ;; the start indicies of -all- token just above.  Check it out!
	  (let* ((substring (car current-parsing-context-text))
		 (start-index
		   (relative-index-of-first-non-whitespace-character
		     substring current-parsing-context-character))
		 (original-string? (parsing-token-incomplete-text parsing-token))
		 (new-incomplete-text (text-string-substring
					substring
					start-index
					character-index-after-token)))
	    (setf (parsing-token-incomplete-text parsing-token)
		  new-incomplete-text)
	    (when (and (null token-or-other-type-of-result?)
		       (/=f (lengthw new-incomplete-text)
			   (-f (parsing-token-end-index parsing-token)
			       (parsing-token-start-index parsing-token))))
	      ;;yduJ, 8/8/03.  The Kluge: if the tokenizer gave us no token, but
	      ;;the length of the string we passed it isn't zero, then the
	      ;;likeliest thing is that we had a comment, and are at the end of
	      ;;that comment.  We know how to skip whitespace in advance, and
	      ;;end up with nice zero length temporary tokens "starting" and
	      ;;ending at the end of the whitespace.  But if it's a comment, the
	      ;;tokenizer ignores it (providing the comment is complete.  It
	      ;;nicely tells us we're inside a comment if it's incomplete.)  We
	      ;;need to skip it.  What used to happen is that we'd end up with a
	      ;;zero length token at the START of the comment.  This caused
	      ;;various problems when we did arithmetic on the indices into the
	      ;;big string, like negative array index attempts.  So, we will
	      ;;skip over the comment and set the start and end indices of this
	      ;;token to the same value, the end of the comment, giving us a
	      ;;zero length token.  Later when we retreat into the comment, the
	      ;;right thing will happen because it'll think it's like
	      ;;whitespace, retreat enough, and re-advance into the comment with
	      ;;a new parsing-token.

	      ;;Note that this parsing-token will be completely eliminated (like
	      ;;the whitespace ones) once we advance to a real token.

	      ;;Possible problems: we are leaving the incomplete text alone,
	      ;;which is a little funky.  Perhaps we should set it to #w"".

	      ;;Advance the end:
	      (setf (parsing-token-end-index parsing-token)
		    (+f (parsing-token-start-index parsing-token) (lengthw new-incomplete-text)))
	      ;;Now advance the start too!
	      (setf (parsing-token-start-index parsing-token)
		    (parsing-token-end-index parsing-token)))
	    (when original-string?
	      (reclaim-text-string original-string?))
	    #+development (when trace-parsing-context-tokenizing-p
	      (format t "~%just set incomplete-text =~S~%"
		      (parsing-token-incomplete-text parsing-token))))))
      
      ;; advance the iteration indices
      (setq current-parsing-context-line line-index-for-end-of-token)
      (setq current-parsing-context-character character-index-after-token)
      
      ;; extend the token stream
      (add-token-to-parsing-context
	parsing-token current-edit-state)
      
      #+development (when trace-parsing-context-tokenizing-p
	(format t "~%New token: ~a~
                   ~%  current text length: ~a~
                   ~%  character index after token: ~a~
                   ~%  current-parsing-context-character: ~a"
;                   ~%  relative-non-whitespace index: ~a
		parsing-token
		current-parsing-context-text-length
		character-index-after-token
		current-parsing-context-character
;		(relative-index-of-first-non-whitespace-character
;		  (car current-parsing-context-text)
;		  current-parsing-context-character))
	))

      ;; return values that extend-parsing-context wants
      (values
	token-or-other-type-of-result?
	type-of-token-or-prefix-token-string?
	line-index-for-end-of-token
	character-index-after-token
	token-self-terminating?
	parsing-token
	(if current-parsing-context-character  ; stop-after-p
	    (=f (lengthw (car current-parsing-context-text))
		current-parsing-context-character)
	    t)
	(parsing-token-incomplete-p parsing-token)))))



(defun comment-token-p (token)
  (or (eq (parsing-token-type-or-prefix-string token) 'G2-COMMENT)
      ;;if the cursor is at the } of the comment, we will have a "incomplete
      ;;parse" of the comment, but there won't be any other possibilities for
      ;;the token type, so it will be the list of a single element.  A real
      ;;completed comment (one with more text after the }, whether whitespace or
      ;;real text) will have the single symbol to indicate real parse completion
      (equal (parsing-token-type-or-prefix-string token) '(G2-COMMENT))))

;;; a lot of code uses the prior token, but really we need to skip all possible
;;; comment tokens in certain cases in order to find the "real" previous token.
(defun maybe-skip-comment-tokens (token)
  (loop while (comment-token-p token)
	do (setq token (parsing-token-previous token)))
  token)
					 
  


(defun extend-parsing-context
       (parsing-extension-mode &optional do-not-suspend? just-update?)
  (declare (ignore just-update?))
  (setf (parsing-extension-mode? current-edit-state) nil)
  
  (unless (free-text-slot-being-edited? current-edit-state) ; trap earlier !
    (with-current-grammar-for-current-edit-state
      (loop with try-to-end-editing? = (eq parsing-extension-mode 'end)
	    with token-or-other-type-of-result?
	    with type-of-token-or-prefix-token-string?
	    with current-line-index-for-end-of-token
	    with current-character-index-after-token
	    with token-self-terminating?
	    with starting-time = 0
	    with incomplete-phrases-after-token
	    with incomplete-phrases-for-previous-token
	    with stop-after-p
	    with incomplete-token-p
	    with parsing-token = nil
	    with prior-cursor-token = nil
	    
	    do
	(setq prior-cursor-token
	      (maybe-skip-comment-tokens (parsing-context-cursor-token current-edit-state)))
	(setq incomplete-phrases-for-previous-token
	      (parsing-token-incomplete-phrases prior-cursor-token))
	(setq incomplete-phrases-after-token nil)
	
	#+development
	(when trace-parsing-context-p
	  (format t "=== Going through the Extend loop~
                   ~%   cursor token: ~a~
                   ~%   its continuations: ~a~%"
		  (parsing-context-cursor-token current-edit-state)
		  incomplete-phrases-for-previous-token))

	;; Heart of the loop: see if we can get another token from the
	;; rest of the pending text
	(multiple-value-setq (token-or-other-type-of-result?
			       type-of-token-or-prefix-token-string?
			       current-line-index-for-end-of-token
			       current-character-index-after-token
			       token-self-terminating?
			       parsing-token
			       stop-after-p
			       incomplete-token-p)
	  ;; token stream iteration
	  (advance-parsing-context-token-stream))
	
	#+development
	(cond
	  (trace-parsing-context-tokenizing-p
	   (format t "~&~%Output of Advance-parsing-context-token-stream:~
		    ~%  token-or-other-type-of-result? = '~a'~
		    ~%  type-of-token-or-prefix-token-string? = ~a~
		    ~%  token-self-terminating? = ~a~
		    ~%  parsing-token = ~a~
		    ~%  stop-after-p = ~a~
		    ~%  incomplete-token-p = ~a~%"
		   token-or-other-type-of-result?
		   type-of-token-or-prefix-token-string?
		   token-self-terminating?
		   parsing-token
		   stop-after-p
		   incomplete-token-p))
	  (trace-parsing-context-p
	   (format t "~%next token is ~a~%"
		   parsing-token)))


	
	
	;; Evaluate the token per se. Should we stop now? (= go to the finish
	;; section of the loop)
	(when (or (not parsing-token)
		  (not type-of-token-or-prefix-token-string?))
	  #+development
	  (when trace-parsing-context-p
	    (format t "~&Leaving the extend loop because ")
	    (cond
	      ((not parsing-token)
	       (format t "the parsing-token is null.~%"))
	      ((not type-of-token-or-prefix-token-string?)
	       (format t "the parsing token doesn't have a type or prefix string.~%"))))
	  (loop-finish))

	
	(when (not (symbolp type-of-token-or-prefix-token-string?))
	  #+development
	  (when trace-parsing-context-p
	    (format t "~&Leaving the extend loop because ")
	    (format t "the token's type hasn't been disambiguated to a symbol.~%"))
	  (loop-finish))

	
	(when (and stop-after-p incomplete-token-p)
	  #+development
	  (when trace-parsing-context-p
	    (format t "~&Leaving the extend loop because ")
	    (format t "the stop-after-p and incomplete-token-p flags were set.~%"))
	  (loop-finish))

       


	
	;; The token is ok per se. Feed it to the parser and see if there's a
	;; continuation.
	(unless (eq type-of-token-or-prefix-token-string? 'G2-COMMENT)
	  (setq incomplete-phrases-after-token
		(advance-parsing-for-token
		  token-or-other-type-of-result?
		  type-of-token-or-prefix-token-string?
		  incomplete-phrases-for-previous-token))
	  #+development
	  (when trace-parsing-context-p
	    (format t "~%Pending phrases available on~%  ~a~
                     ~%   ~a~%Phrases pending after advance ~
                     attempted:~%   ~a~%"
		    token-or-other-type-of-result?
		    incomplete-phrases-for-previous-token
		    incomplete-phrases-after-token))
	  
	  (setf (parsing-token-incomplete-phrases parsing-token)
		incomplete-phrases-after-token)
	  (when (or (null incomplete-phrases-after-token)
		    stop-after-p)
	    #+development
	    (when trace-parsing-context-p
	      (format t "~&Leaving the extend loop because ")
	      (format t "the parser didn't find a continuation.~%"))
	    (loop-finish))

	  
	  (setf (parsing-token-incomplete-phrases parsing-token)
		incomplete-phrases-after-token))
	;; Now go around the loop again.

	
	;; (ddm 12/00) This below is original to Joe/pkb's code. Since we run
	;; syncronously maybe it's no longer something to think about?
	
	;; need different suspension logic !!!
	(when (and nil starting-time try-to-end-editing? do-not-suspend?)
	  (setf (parsing-extension-mode? current-edit-state)
		parsing-extension-mode)
	  (return nil))


	
	;; We've decided we should stop (ran out of text, something funny
	;; about the token, token was ok but it didn't extend the
	;; parse). Evaluate the situation and return.
	    finally
	      (return
		(cond
		  ;; Good Case 1: hit cursor or end-of-text
		  ((and (null type-of-token-or-prefix-token-string?)
			(null token-or-other-type-of-result?))
		   (update-parsing-context-completions-as-appropriate 
		     parsing-token nil nil)
		   (when (parsing-token-previous parsing-token)
		     (update-parsing-context-completions-as-appropriate
		       (parsing-token-previous parsing-token) nil nil))
		   #+development (when trace-parsing-context-p
		     (format t "~%Good string: hit cursor or end-of-text~%"))
		  'parsing-context-complete-status)
		  
		  ;; Good Case 2: the parser got something from the last token
		  (incomplete-phrases-after-token
		   (update-parsing-context-completions-as-appropriate 
		     parsing-token nil nil)
		   #+development (when trace-parsing-context-p
		     (format t "~%Good string: token extended the parse~%"))
		   'so-far-so-good-2)

		  ;; An incomplete token at the end of the text
		  ((and (parsing-token-incomplete-p parsing-token)
			stop-after-p)
		   (compute-prompts-for-incomplete-token parsing-token)
		   #+development (when trace-parsing-context-p
		     (format t "~%Neutral: incomplete token at end of text~%"))
		   'so-far-so-good-3)

		  ;; Bad or unusable token Case
		  ((or (and type-of-token-or-prefix-token-string?
			    (symbolp type-of-token-or-prefix-token-string?))
		       (text-string-p token-or-other-type-of-result?))
		   (let ((problem-string
			   (copy-text-string
			     (if (problem-string-of-most-recent-reason-for-bad-parse?
				   current-edit-state)
				 (reason-for-bad-parse-as-string
				   (problem-string-of-most-recent-reason-for-bad-parse?
				     current-edit-state))
				 #w"This cannot be parsed"))))
		     #+development (when trace-parsing-context-p
		       (format t "~%Bad or un-useable token.~
                                ~%   Problem string: \"~a\"~%" problem-string))
		     (values 'problem-token problem-string)))
		  
		  ;; Incomplete Token Case
		  ((text-string-p type-of-token-or-prefix-token-string?)
		   #+development (when trace-parsing-context-p
		     (format t "~%incomplete token~%"))
		   (cond ((update-parsing-context-completions-as-appropriate
			    (parsing-token-previous parsing-token)
			    token-or-other-type-of-result?
			    type-of-token-or-prefix-token-string?
			    parsing-token)
			  'so-far-so-good-3)
			 (t
			  (values 'incomplete-token
				  (copy-text-string #w"This is incomplete")))))
		  
		  ;; Unterminated Comment Case
		  ((eq token-or-other-type-of-result? 'comment)
		   (values 'in-comment
			   (copy-text-string #w"Use } to terminate comment")))
		  
		  ;; handles escape (i.e. #\@) followed by nothing
		  ((eq token-or-other-type-of-result? 'quoted-character)
		   (values 'unknown-token-type
			   (copy-text-string #w"This is missing a character after ~@")))
		  
		  ;; This can't happen through this interface as I've wired
		  ;; it into Sequoia, but if something went wrong during
		  ;; the alpha, this saves it. ddm 11/19/97
		  ((eq token-or-other-type-of-result? 'ellipsis)
		   (values 'found-ellipsis
			   (copy-text-string #w"This contains an ellipsis")))))))))




;;; `Extract-parse-result' is intended to do that same thing as
;;; get-current-edit-state-parse-if-any but without any side-effects
;;; (since there's no G2 Editor present) and by working from the
;;; cursor token rather than the stack-of-incomplete-phrases data
;;; as that data isn't relevant to stand-alone parsing.

;; Ambiguous parses are said to 'never' occur, and I'll take Mark at his
;; word until I run simulations over the grammar.  (ddm 12/11/97)

(defun extract-parse-result (parsing-context)
  (let ((parse-result nil)
	(parse-trees nil))

    (when (eq (parsing-context-cursor-token parsing-context)
	      (parsing-context-start-token parsing-context))
      (return-from extract-parse-result 'text-is-incomplete))
    
    (macrolet ((determine-final-token (pc)
		 `(let ((cursor-token (parsing-context-cursor-token ,pc)))
		    (cond
		      ((=f (parsing-token-start-index cursor-token)
			   (parsing-token-end-index cursor-token))
		       (parsing-token-previous cursor-token))
		      (t cursor-token)))))
      
      (within-parsing-context (parsing-context)
	(setq parse-trees
	      (loop with final-token = (determine-final-token
					 parsing-context)
		    as incomplete-phrase
		       in (parsing-token-incomplete-phrases
			    final-token)
		    when (eq (phrase-rule-completions incomplete-phrase)
			     (phrase-rule-completions-past-instance-of-category
			       parsing-context))
		      collect
		      (car (incomplete-stack-of-constituents incomplete-phrase))
			using phrase-cons)))

      (setq parse-result
	    (cond ((null parse-trees) 'text-is-incomplete)
		  ((null (cdr parse-trees))
		   (copy-for-phrase (car parse-trees)))
		  (t 'ambiguous-phrase)))
      
      parse-result )))





;;; `update-parsing-context-completions-as-appropriate' determines
;;; what menus go with the token and data passed in. It's expensive,
;;; but not as bad as the comparable calculations in the classic
;;; editor since it is only called once per update. 

(defun update-parsing-context-completions-as-appropriate
    (parsing-token potential-token-types? prefix-simple-string?
		   &optional incomplete-token?)
  (unless keep-edit-workspace-hidden-no-matter-what?
    (when prefix-simple-string?
      (let ((full-caps-string (string-upcasew prefix-simple-string?)))
	(setq prefix-simple-string? full-caps-string)))

    (setq parsing-token (maybe-skip-comment-tokens parsing-token))
    (let* ((menu-content-structure-for-token-position
	     (get-or-make-menu-content-structure-for-parsing-token
	       parsing-token))
	   (category-instance-menus
	     (make-category-instance-menus
	       (if (eq (car menu-content-structure-for-token-position)
		       'end)
		   (cadr menu-content-structure-for-token-position)
		   (car menu-content-structure-for-token-position))
	       prefix-simple-string?
	       (or
		 (maximum-number-of-names-for-a-menu-override?
		   current-edit-state)
		 (maximum-number-of-names-for-a-menu
		   editor-parameters))))
	   (menu-content-structure-for-character-position	; may share structure
	     (nconc
	       (cond
		 (potential-token-types?
		  (make-menu-content-structure-for-character-position
		    menu-content-structure-for-token-position
		    potential-token-types? prefix-simple-string?))
		 (category-instance-menus
		  (copy-list-using-grammar-conses
		    menu-content-structure-for-token-position))
		 (t menu-content-structure-for-token-position))
	       category-instance-menus))
	   (endable-here?
	     (eq (car menu-content-structure-for-character-position) 'end))
	   (menus
	     (if endable-here?
		 (cdr menu-content-structure-for-character-position)
		 menu-content-structure-for-character-position)))
      
      #+development (when trace-parsing-context-p
		      (format t "~%parsing token: ~s~
                 ~%  with potential-token-types? = ~s~
                 ~%    and prefix-simple-string? = ~s~
                 ~%            incomplete-token? = ~s~
                 ~%   token position menu: ~a~
                 ~%   category instance menus: ~a~
                 ~%   character position menus: ~S~%"
			      parsing-token potential-token-types? prefix-simple-string?
			      incomplete-token? menu-content-structure-for-token-position
			      category-instance-menus
			      menu-content-structure-for-character-position)    
		      (when incomplete-token?
			(format t "which is being assigned to ~a~%" incomplete-token?)))

      (when incomplete-token?
	#+development (when trace-parsing-context-p
	  (format t "~%setting menus: ~s on incomplete token ~s~%" incomplete-token? menus))
	(setf (parsing-token-menus incomplete-token?)
	      menus))
      
      (when prefix-simple-string?
	(reclaim-text-string prefix-simple-string?))
      (or (car menus) (cdr menus)))))



(defun get-or-make-menu-content-structure-for-parsing-token (parsing-token)
  (or (parsing-token-menus parsing-token)
      (setf (parsing-token-menus parsing-token)
	    (make-menu-content-structure-for-token-position
	      (parsing-token-incomplete-phrases parsing-token)
	      (phrase-rule-completions-past-instance-of-category
		current-edit-state))))) ; this will be a parsing context

;; g2-od-start-parsing-context-for-text-field
;;  menu update callback
;;   status t/nil
;;   error-line ; can use g2-od-modify text to navigate here
;;   error-char
;;   categories
;;   instances
;;   longest-common-instance-substring g2-od-modify-text will have autocomplete as an action
;;   
;; next test for completion
;;  sets ok bit in pc
;;  advance and retreat clear the ok bit
;; commit checks the ok bit
;;   calls special interface to try to end editing



(defun compute-prompts-for-incomplete-token (incomplete-token)
  (let* ((prior-token? (maybe-skip-comment-tokens (parsing-token-previous incomplete-token)))
	 (potential-token-types?
	   (when (not (text-string-p
			(parsing-token-type-or-prefix-string incomplete-token)))
	     (parsing-token-type-or-prefix-string incomplete-token)))
	 (token-type-as-list?
	   (when potential-token-types?
	     (when (symbolp potential-token-types?) ; it should be a list
	       (gensym-list potential-token-types?)))))
    
    (when prior-token?
      (update-parsing-context-completions-as-appropriate 
	prior-token?  ; parsing-token
	(or token-type-as-list? potential-token-types?)
	(parsing-token-incomplete-text incomplete-token) ; prefix-simple-string?
	incomplete-token))  ; incomplete-token?

    (when token-type-as-list?
      (reclaim-gensym-list token-type-as-list?))))


(defun compute-parsing-context-prompts (parsing-token)
  (let* ((menus (parsing-token-menus parsing-token))
	 (can-end? (if (eq (car menus) 'end)
		       (setq menus (cdr menus))
		       nil))
	 (categories (car menus))
	 (completions (cdr menus))
	 (category-prompts
	   (and categories
		(loop with prompts = nil
		      for choice in categories
		      do
		  (slot-value-push
		    (tformat-text-string "any ~(~a~)" choice)
		    prompts)
		      finally
			(return (nreverse prompts)))))
	 (completion-prompts
	   (and completions
		(loop with prompts = nil
		      for choice-list in completions
		      do
		  (loop for choice in choice-list
			do
		    (slot-value-push
		      (twith-output-to-text-string
			(let ((write-symbols-parsably? t)
			      (write-symbols-in-lower-case? t))
			  (if (atom choice)
			      (twrite choice)
			      (loop for tail on choice
				    do (twrite (car tail))
				       (when (cdr tail)
					 (twrite-char #\space))))))
		      prompts))
		      finally
			(return (nreverse prompts)))))
	 (longest-common-completion
	   (cond
	     ((null completion-prompts)
	      nil)
	     (t
	      (loop with master-string = (car completion-prompts)
		    with pos = (text-string-length master-string)
		    for completion-string in (cdr completion-prompts)
		    as match-length
		    = (minf pos
			    (common-text-string-length
			      master-string completion-string))
		    do
		(setq pos match-length)
		    until (=f pos 0)
		    finally
		      (return (if (=f pos 0) nil
				  (text-string-substring
				    master-string 0 pos))))))))
    (values category-prompts
	    completion-prompts
	    longest-common-completion
	    can-end?)))


(defun common-text-string-length (ts1 ts2)
  (let* ((index-past-difference
	  (wide-string-compare ts1 ts2 t nil)) 
	 (index-past-difference-or-zero
	   ;; n.b. wide-string-compare will return a negative number
	   ;; if ts1 is shorter than ts2
	   (if (<f index-past-difference 0)
	       0  index-past-difference)))	  
    (cond ((=f index-past-difference-or-zero 0)
	   (text-string-length ts1))
	  (t
	   (-f index-past-difference-or-zero 1)))))



#+development
(defun piface-test-1 (proc)
  (let ((pc (create-parsing-context 
	      proc 'procedure-definition nil))
	(source #w"p1 () begin end "))
    (loop with parse-status?
	  with problem-string
	  with continue-p = t
          for i from 0 below (text-string-length source)
	  as string = (copy-constant-wide-string #w"A")
	  do
      (setf (charw string 0) (charw source i))
      (format t "____________________________________________________~%")
      (multiple-value-setq (parse-status? problem-string)
	(advance-parsing-context pc string))
      (setq continue-p (memq parse-status? '(parsing-context-complete-status
					     so-far-so-good-2
					     so-far-so-good-3)))
      (format t "first-token=~s ~%" (parsing-context-start-token pc))
      (format t "cursor-token=~s ~%" (parsing-context-cursor-token pc))
      (describe (parsing-context-cursor-token pc))
      (format t "~%Current Token Stream:~%")
      (loop for token =  (parsing-context-start-token pc)
		      then (parsing-token-next token)
	    do
	(format t "  result=~s type-or-prefix=~s incomplete-p = ~s~%"
		(parsing-token-result token)
		(parsing-token-type-or-prefix-string token)
		(parsing-token-incomplete-p token))
	    until (eq token (parsing-context-cursor-token pc)))
      (unless continue-p
	(format t "parse failed at ~s~%" i)
	(return)))))






;;; `shift-cursor-token' needs to adjust the state of the parsing context
;;; such that we can get a view of what we are to be prompted for at the
;;; new position of the cursor, including any change in the within-token
;;; prompts (widening the options by moving leftwards for example).
;;;    Furthermore, we then have to be able to add/delete characters
;;; with respect to the new position, and (to make this project manageable)
;;; do that without having to grossly revise the techniques used in the
;;; other routines of this standalone parser.
;;;    Given that, I've bit my tongue and decided to look the otherway at
;;; the wastefulness, and will treat a cursor movement that is leftwards
;;; from the current position as though it were a retreat, and one to the
;;; right as though it were an advance. That throws away all the tokens
;;; to the right of the new position each time, only to put them back a
;;; moment later, but it's much simpler than having to rewrite the algorithm
;;; inside Advance-parsing-context and it maintains the policy that the
;;; text is only parsed up to the position of the cursor when there is any
;;; change. (ddm 11/4/97)

(defun shift-cursor-token (pc new-position)
  (let ((current-position (parsing-context-text-length pc)))
    (within-parsing-context (pc)
      (cond
	((>f new-position current-position)
	 ;; n.b. if the text is longer than the new, relatively
	 ;; rightwards index, this will only get it parsed up to
	 ;; that index, not all the way to the end.
	 (multiple-value-bind (parse-status copy-of-gripe)
	     (advance-parsing-context-index pc new-position)
	   (values parse-status copy-of-gripe)))
	((<=f new-position current-position)
	 (retreat-parsing-context pc new-position))))))




;;; `Complete-and-extend-final-token-if-necessary' and the subroutines
;;; that follow it compensate for a facility of the classic editor
;;; interface to the parser that is not available in this standalone
;;; interface. The goal is to be able to conclude a parse even if the
;;; final token has not been deemed complete by the tokenizer -- the
;;; canonical example is having typed "end" at the end of a procedure
;;; without having typed the following space which would permit the
;;; tokenizer to conclude that the symbol it is parsing is complete.

(defun complete-and-extend-final-token-if-necessary (pc)
  (unless (free-text-slot-being-edited? pc)
    (within-parsing-context (pc)
      (let ((final (determine-final-token pc)))
	(when (and final
		   (parsing-token-incomplete-p final)
		   (unambiguous-parsing-token-p final)
		   (incomplete-token-can-be-construed-as-complete final)
		   (parsing-token-result final))
	  (let ((next-parser-state
		  (advance-parsing-for-token
		    (alphabet-symbol-from-portion-of-text
		      (parsing-token-result final))
		    (if (consp (parsing-token-type-or-prefix-string final))
			(first (parsing-token-type-or-prefix-string final))
			(parsing-token-type-or-prefix-string final))
		    (parsing-token-incomplete-phrases
		      (maybe-skip-comment-tokens (parsing-token-previous final))))))
	    (when next-parser-state
	      (setf (parsing-token-incomplete-phrases final)
		    next-parser-state))))))))

(defun determine-final-token (parsing-context)
  (let ((cursor-token (parsing-context-cursor-token parsing-context)))
    (cond
      ((=f (parsing-token-start-index cursor-token)
	   (parsing-token-end-index cursor-token))
       (parsing-token-previous cursor-token))
      (t cursor-token))))

(defun incomplete-token-can-be-construed-as-complete (token)
  (multiple-value-bind (category-choices completion-choices
		        longest-common-completion? can-end?)
      (compute-parsing-context-prompts token)
    (declare (ignore category-choices longest-common-completion? can-end?))
    (loop with token-string = (parsing-token-incomplete-text token)
	  for prediction-string in completion-choices
	  thereis (and (wide-string-p token-string)
		       (string=w prediction-string token-string)))))


(defun unambiguous-parsing-token-p (token)
  (let ((type-field (parsing-token-type-or-prefix-string token)))
    (or (symbolp type-field)
	(and (consp type-field)
	     (null (cdr type-field))))))


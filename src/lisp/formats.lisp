;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module FORMATS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson, Mark H. David, and Ong, Peng Tsin




(def-absent-slot-putter list-of-procedure-instances-for-entity
			(format-frame list-of-procedure-instances-for-entity)
  format-frame list-of-procedure-instances-for-entity)

;; This is an obsolete slot that may be found in KBs older than 11/28/87.

;;;; FORWARD REFERENCES

(declare-forward-reference find-differences-in-frames-if-any function)	; in LOAD1

(declare-forward-reference blocks-to-delete-after-reading-kb variable)	; in KB-*
(declare-forward-reference compiled-items-referring-to-this-name-function
			   function)
(declare-forward-reference update-frame-name-references function)

(declare-forward-reference text-cell-first-font function)


;;;; Formats



;;; A `format frame' specifies the format for a table, a text cell, or the like.
;;; Sizes specified in format frames are in workspace units.

;;; The `format name' of a format frame is a single symbol that identifies the
;;; format.  Normally, the name-or-names-for-frame slot of a format frame holds
;;; the format name.  However, if the format is not up-to-date, the format name
;;; is held in the format-change? slot and the name-or-names-for-frame slot is
;;; nil.  A KB cannot have two format frames (of any class) with the same name.

;;; On loading, a kb-specific format frame is replaced with a pre-existing one
;;; when the two are "equivalent" (see module FILES).  When a format frame is
;;; (interactively) modified, everything formatted according thereto must be
;;; reformatted forthwith.

;;; Except in release 3.0 (i.e., not in 4.0 or 2.x), only format frames that are
;;; in use by other elements of the KB are saved out.  In pre-3.0, and 4.0+,
;;; they are saved within the recursive descent of writing out slots of frames
;;; that refer to them.  In 3.0, every format frame in existence at the time of
;;; the save are present in the KB; thus, there may be many more format frames
;;; saved out than are actually needed by the KB.  These will be cleared away
;;; only when the KB is loaded (or merged) in 4.0, saved, and then reloaded (or
;;; merged after clearing the KB).

;;; The format-change?  slot may be either: nil; the format name for a format
;;; frame that is not necessarily up-to-date, as further indicated by the fact
;;; that the name-or-names-for-frame slot is nil; or an integer, during loading
;;; or merging, to indicate that blocks specifying this format that were created
;;; during loading or merging require reformatting, either because a format
;;; created during loading or merging specified a now unavailable font or
;;; because a non-equivalent substitution of this format was made during loading
;;; or merging.

;;; Due to historical circumstances, there may exist format frames that have nil
;;; in both their format-change?  and name-or-names-for-frame slot.  These are
;;; violations of the constraints given above.  However, as of 10/3/91 these
;;; cases cannot arise in G2 KB matter created entirely from scratch in 3.0; and
;;; the above circumstances notwithstanding, one or the other slot must always
;;; be non-nil.  In addition, as of 10/3/91, the KB loading software maintains
;;; the constraint that no two format frames name nil are equivalent; i.e.,
;;; every format frame named nil is unique.  This is done, when loading a KB, by
;;; deleting a format frame F2 "equivalent" to an existing format frame F1 and
;;; forwarding KB file pointers from F2 to F1.  Note that the "equivalent" test
;;; is somewhat expensive in that it must be done by iterating over all format
;;; frames, but that's ok because there is generally a rather small number of
;;; these.  Note that there has never been a violation, to our knowledge, of the
;;; constraint that no two format frame can have the same name.  See also
;;; comments and code about format frames in the KB-* modules, especially in
;;; KB-LOAD2.  [by MHD, 10/3/91]

(def-class (format-frame entity define-predicate)

  (format-change? nil lookup-slot system save)

  (modules-this-format-frame-has-been-written-in ; (MHD 1/7/93)
    nil vector-slot do-not-save)
  (modules-this-format-frame-has-been-referenced-in ; (MHD 1/7/93)
    nil vector-slot do-not-save))

;; NOTE: due to an oversight, i.e., a BUG, format-change? was never a savable
;; slot, until now, since it had no TYPE feature and no SAVE feature.  But this
;; was a moot point because we never put anything into the format-change? slot,
;; as described in the note above by MHD of 10/3/91, not counting the 11-day
;; lapse in time between that and today. [By MHD, 10/14/91] So, I added the SAVE
;; to the slot description above. (MHD 10/14/91)




;;; A `format description' describes a particular table or text cell format having
;;; a particular `format name'.  It is a global property of the format name, the
;;; value of which may be of the form
;;;
;;;    (format-frame-subclass . alternating-slot-names-and-values)
;;;
;;; The slot names and values override default slot initializations for the format
;;; frame subclass.  Note that two formats should not have the same name.  Note that
;;; (as of 4.0), the initial values are copied using copy-for-slot-value prior to
;;; setting in the slots.

;;; [Historic note: copying the slot values has not been needed so far -- if a
;;; format frame was read from a KB, the values would be copies of the initial
;;; values; if the frame was created in the course of the current KB's lifetime,
;;; the values would be EQ to the values in the slot init forms, and not eq to
;;; the slot init form for the corresponding slots.  This actually was a
;;; violation of the slot value convention -- slot value conses were being
;;; _shared_, and not with their slot init forms only.  It only didn't matter
;;; because we never change such slots' values.  If we had, corruption would
;;; have resulted.  There was a note to this effect scaring us near
;;; change-slot-value, which now can be and has been removed. Nothing ever
;;; depended on EQ-ness between initial values in the
;;; alternating-slot-names-and-values list, since it wouldn't have been
;;; preserved across kb loads anyway.  (MHD 2/4/94)]
 
(def-global-property-name format-description)



;;; Def-format-class defines:
;;;
;;;    (1) format-class (e.g., TABLE-FORMAT) as a subclass of parent-format-class
;;;        with slots as defined by slot-definitions, where parent-format-class must
;;;        be a subclass of FORMAT-FRAME, maybe FORMAT-FRAME itself;
;;;
;;;    (2) a macro for defining specific formats of class format-class, which takes
;;;        a format name followed by alternating slot names and values that override
;;;        values given in slot-definitions; and
;;;
;;;    (3) a definition of a specific (default) format of class format-class, whose
;;;        name consists of format-class prefixed with "DEFAULT-" and which has no
;;;        overrides of values given in slot-definitions.
;;;
;;; For example,
;;;
;;;    (def-format-class (table-format format-frame) ... )
;;;
;;; defines table-format, def-table-format, and default-table-format.

;;; Definitions of specific formats will be used only if and when no format
;;; frame of the specified name exists at the time the format frame is needed.
;;; Thus, for example, if the current kb already has a format frame with this
;;; name, it will take precedence over this definition.

(defmacro def-format-class ((format-class parent-format-class) &body slot-definitions)
  (let ((format-definer-name
	  (intern (format nil "DEF-~A" format-class)))
	(default-format-class
	  (intern (format nil "DEFAULT-~a" format-class))))
    `(progn
       (def-class (,format-class ,parent-format-class)
	 . ,slot-definitions)
       (defmacro ,format-definer-name
		 (format-name &body alternating-slot-names-and-values)
	 `(progn
	    (setf (format-description ',format-name)
		  (optimize-constant
		    '(,',format-class . ,alternating-slot-names-and-values)))
	    
;	    (def-kb-specific-variable ,format-name FORMATS nil) ; ENABLE!; fix module-name?
	    
	    ',format-name))
       (,format-definer-name ,default-format-class))))

;; Consider having this verify (subclassp parent-format-class 'FORMAT-FRAME).

;; Default format definitions are in use, as of 3/7/88, as follows:
;; default-table-format in TABLES (comment only), default-message-board-format
;; in BOOKS, default-graph-format in GRAPHS1 and GRAPHS2, and
;; default-plot-format in GRAPHS2.

;; NOTE to developers: this no longer (as of 4.0) jumps into your KB in
;; development, changes your format frames to be "new", and makes them look like
;; they've been changed through some interface yet to be written after more than
;; seven years.  That was too hard to support and maintin.  The flushing of
;; remove-names-of-class-instances-in-all-kbs marked the end of the old era.
;; (MHD 2/4/94)






;;; Get-or-make-format-frame either gets a format frame named format-name, if there is
;;; one, or else makes one based on the format description for format-name.  In the
;;; unlikely event that there is more than one format frame with the same name, the
;;; first to get that name is returned.  Note that there must be a format description for
;;; format-name.

(def-substitution-macro get-or-make-format-frame (format-name)
  (or (get-instance-with-name-if-any 'format-frame format-name)
      (make-format-frame format-name)))

;;; Function declaration to allow forward referencing

(defun get-or-make-format-frame-function (format-name)
  (get-or-make-format-frame format-name))

;;; Change-standard-format-frame-slot ensures that the format frame that will
;;; be returned by the next call to (get-or-make-format-frame format-name) will
;;; have new-value in its slot-name slot.  It does this by first finding an
;;; existing format frame named format-frame, if any, and, if none, then when
;;; there's no old format-frame named format-name but new-value happens not to
;;; differ from new-value, it does not have to create a format frame at all;
;;; otherwise, when there is an old format frame named format-name, and its
;;; slot-name slot differs from new-value, it moves its name to the format-change?
;;; slot.  Then it creates a new format frame named format-name and changes its
;;; slot-name slot to new-value.  But then, if it can find an old, equivalent
;;; format frame, it makes that old format frame have name format-name and then
;;; deletes the new one it created.

;;; This returns either nil, if it did not have to create or delete any frames,
;;; or the frame that now has the name format-name.

(defun change-standard-format-frame-slot (format-name slot-name new-value)
  (let ((old-format-frame?
	  (get-instance-with-name-if-any 'format-frame format-name)))
    
    (cond
      
      ((and old-format-frame?
	    (eql (get-slot-value old-format-frame? slot-name)
		 new-value))
       old-format-frame?)
      
      ((and (null old-format-frame?)
	    (eql (getf (cdr (format-description format-name)) slot-name)
		 new-value))
       nil)
      
      (t
       (when old-format-frame?
	 (change-slot-value old-format-frame? 'name-or-names-for-frame nil)
	 (change-slot-value old-format-frame? 'format-change? format-name))
       
       (let ((new-format-frame (get-or-make-format-frame format-name)))
	 (change-slot-value new-format-frame slot-name new-value)
	 (or (loop for old-format-frame being
		   each strict-class-instance
		   of (class new-format-frame)
		   when (and (not (eq old-format-frame new-format-frame))
			     (null (name-or-names-for-frame
				     old-format-frame))
			     (eq (format-change? old-format-frame)
				 format-name))
		     thereis
		     (let ((denotations-of-differing-slots
			     (find-differences-in-frames-if-any
			       old-format-frame new-format-frame)))
		       (prog1
			   (when (loop for slot-denotation in denotations-of-differing-slots
				       always ; ignores defining class!
				       (memq (unqualified-name slot-denotation)
					     '(name-or-names-for-frame format-change?)))
			     ;; We can rehabilitate an old, nameless format frame --
			     ;; delete the new one we just created.
			     (delete-frame new-format-frame)
			     (change-slot-value
			       old-format-frame 'name-or-names-for-frame format-name)
			     (change-slot-value old-format-frame 'format-change? nil)
			     old-format-frame)
			 (reclaim-slot-value denotations-of-differing-slots))))
	     new-format-frame))))))

;; In principle, we could avoid even creating a new frame if we are going to end up
;; being able to rehabilitate an old one.  That would require more abstraction of
;; the comparison code in find-differences-in-frames-if-any.  Consider doing this.
;; (MHD 10/11/91)

;; This function was introduced 10/9/91 for use by a couple of functions in
;; BOOKS.  At this time, those functions are the only users.  (MHD 10/9/91)





(defun find-existing-equivalent-format-frame (format-frame)
  ;; find an old, equivalent, unnamed format frame:
  (loop for old-format-frame being
	    each strict-class-instance
	    of (class format-frame)
	when (and (not (eq old-format-frame format-frame))
		  (null (name-or-names-for-frame
			  old-format-frame))
		  
		  ;; The following form was missing in 3.0 Prealpha
		  ;; prereleases through its fix 1/27/92 in development;
		  ;; it was found to result in text-box-format slots
		  ;; of free texts pointing to deleted frames!  I have
		  ;; not looked into ways of dealing with KBs that fell
		  ;; victim to this lossage and may be being loaded.
		  ;; (MHD 1/27/92)
		  ;; Consider a frame flag specific to format-frames which
		  ;; is set only when the format-frame is on
		  ;; blocks-to-delete-after-reading-kb.
		  (or (not reading-kb-p)
		      (not (memq old-format-frame
				 blocks-to-delete-after-reading-kb)))

		  
		  (null (find-differences-in-frames-if-any
			  format-frame old-format-frame t)))
	  return old-format-frame))





;; The following is obsolete, but used to be above.  First of all, in 3.0, we save
;; all format frames.  Second of all, there is no abstracted way, at present, to
;; search the KB even if you wanted to, although it could be abstracted.
;; (MHD 10/4/91)
;; 
;; ;;; A format frame should not be deleted if it might currently be in use, which
;; ;;; might only be discoverable by a complete search of the kb.  In any event, there is
;; ;;; little purpose in deleting format frames, since only those which are actually used
;; ;;; or have representations will be saved when the kb is saved.

(defun make-format-frame (format-name)
  (let* ((format-description
	   (or (format-description format-name)
	       (error "No format description found for ~a" format-name)))
	 (format-frame (make-frame (car format-description))))
    (put-name-or-names-for-frame		; use initialize-slot-value?
      format-frame format-name t)
    (set-permanent-block format-frame)
    (when noting-changes-to-kb-p 
      (set-block-permanently-changed format-frame))
    (loop for (slot-name slot-init-form) on (cdr format-description) by 'cddr
	  do (initialize-slot-value
	       format-frame slot-name
	       (copy-for-slot-value	; copying new for 4.0 (MHD 2/4/94)
		 slot-init-form)))	; See "Historic note" above!
    format-frame))

;; Keep the current format frame named format-name, if any, in the kb-specific variable
;; named format-name, for a bit more speed!  To do this, revise def-format-class (as
;; indicated above), get-or-make-format-frame, and put-name-or-names-for-frame (avoiding
;; setting the kb-specific variable when this is called from within remove-names-of-
;; class-instances-in-all-kbs).






;;; `test-for-format-frame-constraint-violations', defined for development only
;;; at present tests for two format frames with the same name, which would be a
;;; constraint violation.  No other tests are presently done, but may be added
;;; in the future.

#+development
(defun test-for-format-frame-constraint-violations ()
  (loop for ff being each class-instance of 'format-frame
	as name? = (name-or-names-for-frame ff)
	when name?
	  do (loop for ff2 being each class-instance of 'format-frame
		   as name-2? = (name-or-names-for-frame ff2)
		   when (and name-2?
			     (eq name? name-2?)
			     (not (eq ff2 ff)))
		     do (break "~a and ~a have the same name!" ff ff2))))










;;;; Fonts



;;; The `fonts' system table holds font selection information.

(def-system-frame fonts formats

  (font-for-attribute-tables large system vector-slot (type font-name))

  (font-for-attribute-displays			; NEW SLOT.  Use in FACILITIES. (MHD 3/15/93)
    small system lookup-slot (type font-name))	; MAKE VECTOR NEXT RECOMPILE!! (MHD 3/16/93)

  (font-for-statements large system vector-slot (type font-name))
  (font-for-free-text large system vector-slot (type font-name))

  (font-for-editing large system vector-slot (type font-name))

  (font-for-descriptions small system vector-slot (type font-name)))



;;; Font name grammar.

(add-grammar-rules '((font-name 'large)
		     (font-name 'small)
		     (font-name 'extra-large)))

(def-slot-value-writer font-name (form)
  (twrite form))



;;; A `corresponding-small-font-format-name' property on a format name specifies
;;; the name of a corresponding small-font format, if there is one.

(def-global-property-name corresponding-small-font-format-name)



;;; A `corresponding-extra-large-font-format-name' property on a format name
;;; specifies the name of a corresponding extra-large-font format, if there is one.

(def-global-property-name corresponding-extra-large-font-format-name)





;;; `Choose-font-format-per-fonts-table' returns the name of the large-font-
;;; format-name format corresponding to the font size specified in the fonts-
;;; slot-name slot of the fonts system table.

;;; For example,
;;; 
;;;       (choose-font-format
;;;         'borderless-free-text-format
;;;         'font-for-descriptions)
;;;
;;; returns SMALL-BORDERLESS-FREE-TEXT-FORMAT if (font-for-descriptions fonts)
;;; is SMALL.

;;; If, for some reason, there exists no format name corresponding to the size
;;; of font called for, this returns large-font-format-name; this should not
;;; really occur, and, if it does, probably is due to an implementor's error.

(defun choose-font-format-per-fonts-table
       (large-font-format-name fonts-slot-name)
  (choose-font-format-per-font-size
    large-font-format-name
    (get-slot-value fonts fonts-slot-name)))


(defun parameterized-attribute-table-header-format () ; aka "class format"!
  (if new-g2-classic-ui-p
      'new-class-format
      (choose-font-format-per-fonts-table
       'class-format 'font-for-attribute-tables)))

(defun parameterized-attribute-description-format ()
  (if new-g2-classic-ui-p
      'new-attribute-description-format
      (choose-font-format-per-fonts-table
       'attribute-description-format 'font-for-attribute-tables)))

(defun parameterized-attribute-value-format ()  
  (if new-g2-classic-ui-p
      'new-attribute-value-format
      (choose-font-format-per-fonts-table
       'attribute-value-format 'font-for-attribute-tables)))



;;; Choose-font-format-per-font-size is similar to choose-font-format-per-
;;; fonts-table except that it takes Font-size?, either nil or an explicit
;;; size (i.e. SMALL, LARGE, or EXTRA-LARGE) instead of fonts-slot-name,
;;; the name of a slot in the fonts system table.

;;; If either font-size? is nil or there exists no format name corresponding
;;; to font-size?, this returns large-font-format-name.

;; For debugging:
;; ;;; In development, however, this would first signal a continuable error when
;; ;;; font-size? is either SMALL or EXTRA-LARGE and no corresponding font format
;; ;;; name existed.

(defun choose-font-format-per-font-size 
       (large-font-format-name font-size?)
  (or (if font-size?
	  (case font-size?
	    (small
	     (corresponding-small-font-format-name
	       large-font-format-name))
	    (extra-large
	     (corresponding-extra-large-font-format-name
	       large-font-format-name))))
;; For debugging:
;      #+development
;      (if (memq font-size? '(small extra-large))
;	  (cerror "Use the large font format."
;		  "No corresponding ~a font format for ~a!"
;		  font-size? large-font-format-name))
      large-font-format-name))





;;; `Determine-font-size-per-format' returns the size (SMALL, LARGE, or EXTRA-LARGE)
;;; represented by format-name for large-font-format-name, the name of a format
;;; used when the size is LARGE.  If format-name-or-format-frame does not yield
;;; match, this returns nil. 

(defun determine-font-size-per-format
    (format-name-or-format-frame large-font-format-name)
  (or (let ((format-name
	      (if (symbolp format-name-or-format-frame)
		  format-name-or-format-frame
		  (name-or-names-for-frame format-name-or-format-frame))))
	(if (and (null format-name) (framep format-name-or-format-frame))
	    (let ((font-name (text-cell-first-font format-name-or-format-frame)))
	      (cond
		((eq font-name
		     (text-cell-first-font
		       (get-or-make-format-frame
			 (choose-font-format-per-font-size
			   large-font-format-name 'extra-large))))
		 'extra-large)
		((eq font-name
		     (text-cell-first-font
		       (get-or-make-format-frame
			 (choose-font-format-per-font-size
			   large-font-format-name 'small))))
		 'small)
		((eq font-name
		     (text-cell-first-font
		       (get-or-make-format-frame
			 (choose-font-format-per-font-size
			   large-font-format-name 'large))))
		 'large)))
	    (cond
	      ((eq format-name
		   (choose-font-format-per-font-size
		     large-font-format-name 'extra-large))
	       'extra-large)
	      ((eq format-name
		   (choose-font-format-per-font-size
		     large-font-format-name 'small))
	       'small)
	      ((eq format-name
		   (choose-font-format-per-font-size
		     large-font-format-name 'large))
	   'large))))
      'large))

;; Remember that files must be carriage return delimited.  -jra 9/25/89




;;;; Frame Styles


;;; Frame styles are frames created by users to describe how to enclose
;;; items (workspaces, icons, text-boxes, what ever) in a frame when
;;; rendering them.

(def-class (frame-style-definition (item entity)
				   (foundation-class frame-style-definition))
  ;; enable authors attribute for this definitional item:
  (frame-author-or-authors nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))
  
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      50 50
      ((outline (0 0) (0 49) (49 49) (49 0))
       (outline (43 7) (47 7) (47 42) (43 42))
       (outline (2 44) (41 44) (41 47) (2 47))
       (solid-rectangle (5 2) (47 5)))))
  #+obsolete
  (always-display-entire-item-inside-frame  ;; See absent slot putter
    t
    vector-slot
    system
    (type yes-or-no)
    save)
  (description-of-frame
    nil
    vector-slot
    system user-overridable
    save
    (type frame-description)
    (attribute-export-comment
      "Currently, the only description attribute exported is frame-border-size. ~
	writable = true, type = positive-integer. This is not shown in autodoc ~
so is not implemented through an attribute-mimic. Investigate???"))
  (frame-description-reference-of-frame-style-definition?
    nil   ;; Non-nil if frame-ok-p
    vector-slot
    system
    ))

(def-slot-value-reclaimer frame-description-reference-of-frame-style-definition?
    (frame-description-reference? frame-style-definition)
  (when frame-description-reference?
    (setf (dirty-frame-description-reference frame-description-reference?) t)
    (setf (frame-description-reference-of-frame-style-definition?
	    frame-style-definition)
	  (release-frame-description-reference-if-any
	    frame-description-reference?))))

(def-class-method initialize (frame-style-definition)
  (funcall-superior-method frame-style-definition)
  (funcall-method-if-any 'update-frame-status-and-notes frame-style-definition))

;;; `Cleanup' on frame-style-definition changes the description-of-frame
;;; to "none" so that any users will be revised before we pack it in.

(def-class-method cleanup (frame-style-definition)
  (funcall-superior-method frame-style-definition)
  (when (description-of-frame frame-style-definition)
    (change-slot-value frame-style-definition
		       'description-of-frame
		       nil
		       'frame-style-definition)))


;;; The slot `always-display-entire-item-inside-frame' is obsolete.  It was never
;;; implemented, but some KB exist that containing it.

(def-absent-slot-putter always-display-entire-item-inside-frame
    (frame-style-definition boolean)
  (declare (ignore frame-style-definition boolean))
  )

(def-frame-note-writer frame-style-definition-is-empty (particulars)
  (declare (ignore particulars))
  (tformat "the description of frame is missing."))

(def-class-method update-frame-status-and-notes (frame-style-definition)
  (with-updates-to-representations-supressed
      (frame-style-definition 'frame-status-and-notes)
    (funcall-superior-method frame-style-definition)
    (let ((frame-status? nil)) ;; aka OK

      ;; frame-style-definition-is-empty
      (delete-frame-note-if-any 'frame-style-definition-is-empty frame-style-definition)
      (unless (description-of-frame frame-style-definition)
	(add-frame-note
	  'frame-style-definition-is-empty
	  frame-style-definition
	  t t nil)
	(setf frame-status? 'incomplete))

      (update-frame-status frame-style-definition frame-status? nil))))



;;; The `slot putter for description-of-frame' shifts the new frame description
;;; into the slot.  The old frame description is reclaimed and any corresponding
;;; frame description reference is marked dirty, and released.  We call
;;; clean-frame-description-references, if necessary.  The concequences of the
;;; new description are taken, a frame description reference is created and
;;; frame notes for this frame are reconsidered.

(def-slot-putter description-of-frame (frame-style-definition new-value)
  (prog1
      (setf (description-of-frame frame-style-definition) new-value)
    ;; Dirty and dereference any old frame description reference.
    (let* ((old-frame-description-reference?
	     (frame-description-reference-of-frame-style-definition?
	       frame-style-definition))
	   (creating-dirty-references?
	     (and old-frame-description-reference?
		  (<f 1
		      (reference-count-of-frame-description-reference
			old-frame-description-reference?)))))
      (when old-frame-description-reference? 
	(reclaim-frame-description-reference-of-frame-style-definition?-value
	  (frame-description-reference-of-frame-style-definition?
	    frame-style-definition)
	  frame-style-definition))
      ;; Update the frame notes.
      (funcall-method 'update-frame-status-and-notes frame-style-definition)
      ;; If things are OK, make a fresh frame-style-definition.
      (when (frame-ok-p frame-style-definition)
	(setf (frame-description-reference-of-frame-style-definition?
		frame-style-definition)
	      (reference-frame-description-reference
		(create-frame-description-reference
		  (copy-tree-using-graphics-conses new-value)))))
      ;; This was previously NIL, so we have to kick the formating
      (when (and (not old-frame-description-reference?)
		 (name-or-names-for-frame frame-style-definition))
	;; Map over all those who reference this name
	(do-atom-or-list-of-atoms
	    (name (name-or-names-for-frame frame-style-definition))
	  (loop for item
		    in (compiled-items-referring-to-this-name-function name)
		do
	    (when (kb-workspace-p item) 
	      (reconsider-formatting item)))))
      (when creating-dirty-references?
	(clean-frame-description-references)))))

;; This doesn't update users when the frame style was NIL previously,
;; same for the names slot, which is probably the more thought provoking.


;;; `Lookup-frame-description-reference-from-frame-style-definition?' is
;;; only one part of the search that maps a frame style name into a fraem
;;; description reference.  This implements the search for a
;;; KB specific frame-style-description of the given name that is OK.

(defun lookup-frame-description-reference-from-frame-style-definition?
    (frame-style)
  (let ((frame-style-description?
	  (get-instance-with-name-if-any 'frame-style-definition frame-style)))
    (when (and frame-style-description?
	       (frame-ok-p frame-style-description?))
      (frame-description-reference-of-frame-style-definition?
	frame-style-description?))))
  

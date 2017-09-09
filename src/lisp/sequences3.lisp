;; -*- mode: lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module SEQUENCES3

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin




;;;; Forward References in SEQUENCES3


;; To BOXES 

(declare-forward-reference reformat-text-box-in-place function)
(declare-forward-reference reclaim-text function)
(declare-forward-reference convert-text-string-to-text function)


;; To TABLES

(declare-forward-reference suppress-updating-of-self-representations? variable)

;; The above variable actually has to be declared special to compile correctly,
;; since it is only lambda bound below (in strip-texts-from-item) as an implicit
;; parameter to update-representations-in-tables (in TABLES).  (MHD 10/30/90)


;; To FILTERS

(declare-forward-reference g2-equiv function)


;; To ACTIVATE

(declare-forward-reference superior-frame function)

;; To UTILITIES4

(declare-forward-reference inform-ui-client-interfaces-of-general-update function);view-g2
(declare-forward-reference update-subscriptions-from-virtual-attribute-change function);view-def




;;; This file contains the toolkit security functionality.

;;; Every modification to other files required for this facility
;;; is below the text "gensym-toolkit". Each is noted somewhere in this file.





;;;; Marking For Text stripping


;;; There are two frame flags for menu stripping, strip-text and
;;; do-not-strip-text. These are directives as to what frames are
;;; to be stripped, and they also control menu choices. The meaning
;;; of these flags is as follows:

;;; (00) Neither is on: The decision of whether or not the text should
;;;      be stripped is inherited.
;;; (10) Strip text is on: This item should have its text stripped.
;;; (01) Do-not-strip-text is on: This item should not have its text stripped.
;;; (11) Both are on: This is not legal.

;; Consider representing these bits some other way, without frame flags.
;; Efficiency is not an issue.

;;; Put these flags into FRAMES3!!!

;;; Gensym toolkit mode is defined below.


;;; Package-preparation-mode is a global switch which causes the marking menu
;;; choices and the strpping menu choice to be available. It is only
;;; found in G2s which are located at Gensym Cambridge for now.

(def-kb-specific-variable package-preparation-mode sequences3 nil)




(defun-simple set-package-preparation-mode (new-state)
  (setq package-preparation-mode new-state)
 (inform-ui-client-interfaces-of-general-update
   'package-preparation-mode-changed
   (if new-state evaluation-true-value evaluation-false-value)))

;;; Enter-package-preparation-mode ...

(defun enter-package-preparation-mode ()
  (notify-user "Entering Package Preparation mode.  To exit this mode, select ~
                \"Leave Package Preparation Mode\" from the Main Menu ~
                Miscellany menu.")
  (set-package-preparation-mode t))


;;; Leave-package-preparation-mode ...

(defun leave-package-preparation-mode ()
  (notify-user "Leaving Package Preparation mode.")
;  (setq simulate-proprietary? nil)
  (set-package-preparation-mode nil))




;;; Every item has menu choices when in package-preparation-mode. These choices
;;; and their associated code are not present in non gensym-toolkit G2.

;;; The menu choices depend on 6 states that an item can be in. Letting
;;; the first of three bits = 1 if the inherited context is to strip, and
;;; the next two bits are the states documented above, for example, 110
;;; means that the inherited state is to strip, and the strip-text flag is on,
;;; but the do-not-strip flag is not on.

;;; Table of menu choices:

;;; 000	  MARK TO STRIP TEXT			010
;;;       MARK NOT TO STRIP TEXT 		001

;;; 100   MARK TO STRIP TEXT *			110
;;;       MARK NOT TO STRIP TEXT *		101

;;; 010   REMOVE STRIP TEXT MARK		000		
;;;       MARK NOT TO STRIP TEXT 		001

;;; 110   REMOVE STRIP TEXT MARK *		100		
;;;       MARK NOT TO STRIP TEXT *		101

;;; 001   MARK TO STRIP TEXT			010
;;;       REMOVE D0 NOT STRIP TEXT MARK 	000

;;; 101   MARK TO STRIP TEXT *			110
;;;       REMOVE D0 NOT STRIP TEXT MARK *	100

;;; 011	  Not legal
;;; 111	  Not legal

;;; The wording of each line describes how the item is to be
;;; marked. Marking implies removing the other mark if present.

;;; The meaning of the asterisc is that stripping is inherited.

;;; Another presentation follows. For each choice, it shows
;;; the conditions under which it appears, and for each pair of
;;; choices, the desired result without the environment bit.

;;; MARK TO STRIP TEXT			000 001		10
;;; MARK TO STRIP TEXT *		100 101

;;; REMOVE STRIP TEXT MARK		010		00
;;; REMOVE STRIP TEXT MARK *		110

;;; MARK NOT TO STRIP TEXT *		100 110		01
;;; MARK NOT TO STRIP TEXT		000 010

;;; REMOVE D0 NOT STRIP TEXT MARK *	101		00
;;; REMOVE D0 NOT STRIP TEXT MARK	001


;;; Strip-choice-obtains-p is used with the above table to conditionalize
;;; the menu choices.  Choice-symbol must be one of the following:
;;; 
;;;		 mark-to-strip-text
;;;		 mark-to-strip-text-*
;;;		 remove-strip-text-mark
;;;		 remove-strip-text-mark-*
;;;		 mark-not-to-strip-text-*
;;;		 mark-not-to-strip-text
;;;		 remove-do-not-strip-text-mark-*
;;;		 remove-do-not-strip-text-mark
;;;
;;; Note that all of the symbolic values allowed for c1-or-choice-symbol
;;; have exactly corresponding menu choice symbols.

(defun strip-choice-obtains-p (kb-frame choice-symbol)
  (and package-preparation-mode
       (frame-of-class-p kb-frame 'item)
       (let* ((stripping-inherited-p (stripping-inherited-p kb-frame))
	      (strip-text-p (strip-text-p kb-frame))
	      (do-not-strip-text-p (do-not-strip-text-p kb-frame))
	      (pattern				; this form will set args
		(cdr
		  (assq
		    choice-symbol
		    '((mark-to-strip-text . (0 0 0 0 0 1))
		      (mark-to-strip-text-* . (1 0 0 1 0 1))
		      (remove-strip-text-mark . (0 1 0))
		      (remove-strip-text-mark-* . (1 1 0))
		      (mark-not-to-strip-text-* . (1 0 0 1 1 0))
		      (mark-not-to-strip-text . (0 0 0 0 1 0))
		      (remove-do-not-strip-text-mark-* . (1 0 1))
		      (remove-do-not-strip-text-mark . (0 0 1))))))
	      (c1 (first pattern))
	      (c2 (second pattern))
	      (c3 (third pattern))
	      ;; the rest may car/cdr on nil
	      (d1 (fourth pattern))
	      (d2 (fifth pattern))
	      (d3 (sixth pattern)))
	       
	 (or
	   (and
	     (g2-equiv (=f c1 1) stripping-inherited-p)
	     (g2-equiv (=f c2 1) strip-text-p)
	     (g2-equiv (=f c3 1) do-not-strip-text-p))

	   (and
	     d1
	     (g2-equiv (=f d1 1) stripping-inherited-p)
	     (g2-equiv (=f d2 1) strip-text-p)
	     (g2-equiv (=f d3 1) do-not-strip-text-p))))))

;; There is no need for speed here, and this style is compact and makes for
;; accuracy in code.  [ML's comment, presumably referring to the style of
;; passing in bits instead of a single symbol.  I disagree that that style
;; should be preferred.  I simplified it to be called symbolically instead
;; of with args c1 through c6. -mhd, 8/10/90]

;; Simplified, so that the following should be obsolete:   (MHD/ML 8/10/90)
;; 
;; ;; The above function seems to be causing a segmentation violation in the
;; ;; compile on an old platform, must likely due to a bug in the C compiler or C
;; ;; optimizer.  This function should be reorganized in the future, most likely by
;; ;; getting rid of the nested let statements, in an attempt to work around the C
;; ;; compiler bug.  For the moment, the body of this function is a no-op, except
;; ;; in development. -jra 7/3/90




(defun set-stripping-flags-as-specified (item r1 r2)
  (let ((old-strip-text-mark (strip-text-p item))
	(old-do-not-strip-text-mark (do-not-strip-text-p item)))
    (if (=f r1 1)
	(set-strip-text item)
	(clear-strip-text item))
    (if (=f r2 1)
	(set-do-not-strip-text item)
	(clear-do-not-strip-text item))
    (unless (eq (strip-text-p item) old-strip-text-mark)
      (update-subscriptions-from-virtual-attribute-change
	item (virtual-attribute 'strip-text-mark) nil))
    (unless (eq (do-not-strip-text-p item) old-do-not-strip-text-mark)
      (update-subscriptions-from-virtual-attribute-change
	item (virtual-attribute 'do-not-strip-text-mark) nil))))











;;;; The Main Menu

;;; On a gensym-toolkit G2, the main menu has options to enter and leave
;;; package-preparation-mode. In this mode, the options above are shown.
;;; When in package-preparation-mode, there is also the choice "strip kb."







;;;; Stripping Text


(def-generic-method strip-text (block stripping-inherited?)
  )

(defun strip-all-texts ()
  (cond
    (system-is-running
     (notify-user
       "You cannot strip texts while the system is running.  ~
        No texts were stripped."))
    (t
     (notify-user "Stripping texts now!")
     (loop for block being class-instances of 'kb-workspace do
       (when (and (null (superblock? block))
		  (null (parent-of-subworkspace? block)))
	 (funcall-method 'strip-text block nil)))
     (notify-user "Finished stripping texts."))))



(def-class-method strip-text (block stripping-inherited?)  
  (let* ((old-strip-text-mark? (strip-text-p block))
	 (old-do-not-strip-text-mark? (do-not-strip-text-p block))
	 (strip-item?
	  (or old-strip-text-mark?
	      (and stripping-inherited?
		   (not (do-not-strip-text-p block))))))
    
    (if strip-item? (strip-texts-from-item block))
    ;; Clear both marks from item whether stripping or not.
    (clear-strip-text block)
    (clear-do-not-strip-text block)
    (unless (eq (strip-text-p block) old-strip-text-mark?)
      (update-subscriptions-from-virtual-attribute-change
	block (virtual-attribute 'strip-text-mark) nil))
    (unless (eq (do-not-strip-text-p block) old-do-not-strip-text-mark?)    
      (update-subscriptions-from-virtual-attribute-change
	block (virtual-attribute 'do-not-strip-text-mark) nil))

    
    ;; All user defined attributes having items as values.
    (propagate-method-to-attributes block 'strip-text strip-item?)
    
    ;; Subworkspace if any of item if item is an entity.
    (if (entity-p block)
	(let ((subworkspace? (car (subworkspaces block))))
	  (if subworkspace?
	      (funcall-method 'strip-text subworkspace? strip-item?))))
    
    ;; Subblocks of a workspace which are items.
    (if (frame-of-class-p block 'kb-workspace)
	(loop for subblock being each subblock of block doing
	  (when (frame-of-class-p subblock 'item)
	    ;; Apply strip-text to the subblock which is an item
	    (funcall-method 'strip-text subblock strip-item?)
	    ;; Apply it to the output connections of the subblock
	    ;; if these are frames. This code adapted from
	    ;; activate-connection-frames-for-block.
	    (loop for connection being the output-connections of subblock
		  for connection-frame-or-class
		      = (connection-frame-or-class connection)
		  do
	      (if (framep connection-frame-or-class)
		  (funcall-method
		    'strip-text connection-frame-or-class strip-item?)))
	    
	    )))
    
    ;; If a variable, then process the simulation subtable if any.
    (if (frame-of-class-p block 'variable)
	(let ((simulation-details
		(get-slot-value block 'simulation-details)))	; forw. ref.
	  (when simulation-details
	    (funcall-method 'strip-text simulation-details strip-item?))))
    
    ;; Embedded rules are not traversed by this process. In the analogous
    ;; traversal used by activate, they are activated by special hooks put
    ;; into activate-subclass-of-entity method for action-button and menu-choice.
    ;; These do not need to be stripped, and have no substructures needing
    ;; traversal.    
    ))




;;; Strip-item-of-all-text must look for all editable text slots of item and
;;; put in the empty text.

;;; Since in general slot putters can have arbitrary side affects, this cannot
;;; and does not go through change-slot-value to update the texts.  For this
;;; reason, existing frame representations of item are not updated to reflect
;;; the new text.

;;; When item is a text box, this does end up changing the shape of the box
;;; and updatings its images to reflect the new size of the text when its
;;; box-translation-and-text slot is changed.  Since, at present in
;;; G2, no other items represent text slots graphically except as frame
;;; representations, this should be adequate as long as users can accept
;;; not having frame representations updated.  This brings up the issue
;;; of readout-tables and graphs, which are actually tables, items, and
;;; frame representations (of themselves!) all rolled into one.  In both
;;; cases, there are text slot, expressions-to-display and label-to-display,
;;; which end up being shown in the original graphic representation of these
;;; items as the label for what is being displayed.  If the text so displayed
;;; were to become stripped, these displays would most often be rendered
;;; useless.  Furthermore, editing of both these slots is then disabled, which
;;; is a feature, too.  However, note that this leaves an inconsistency between
;;; what is in frame representations and what is in the slots they represent.

(defun strip-texts-from-item (item)
  (loop with class = (class item)
	with slot-descriptions = (slot-descriptions (class-description-slot item))
	for slot-description in slot-descriptions
	for slot-name = (unique-slot-name slot-description)
	as type-of-slot? = (type-of-slot-if-editable class slot-name)
	when (and type-of-slot? (text-slot-type-p type-of-slot?))
	  do (let ((value? (get-slot-value item slot-name)))
	       (when value?
		 (updating-images-of-block (item)
		   (reclaim-text (cdr value?))
		   (setf (cdr value?)
			 (make-new-stripped-text))
		   (when (eq slot-name 'box-translation-and-text)
		     (reformat-text-box-in-place item)))

		 (let ((suppress-updating-of-self-representations?
			 t))			; to not update labels of readout
						;   tables, graphs. (MHD 8/24/90)
		   (declare (special suppress-updating-of-self-representations?))	; forward ref.
		   (update-representations-of-slot-value item slot-name)))))
  ;; Remove the annotation lookup structure
  (clean-out-annotation-lookup-structure item))

;; NOTE MODIFICATION TO ACTIVATE: superior-frame has simulation-subtable case!!!


	 


;;;; Main Menu Miscellaney Menu

;; All of the following code should be reader conditionalized under
;; gensym-toolkit mode.

;; FACILITIES has been modified to have the entries TEXT STRIPPING MODE,
;; LEAVE TEXT STRIPPING MODE, and STRIP TEXTS NOW.



;;;; Item menus

;;; Most of the choice documentation is above.

;;; stripping-inherited-p traverses the structure hierarchy upwards
;;; and returns non-nil if it finds a strip-text-p before finding a
;;; do-not-strip-text-p or arriving at the top.

(defun stripping-inherited-p (item)
  (loop for superior? = (superior-frame item)
		      then (superior-frame superior?)
	until (null superior?) doing
    (cond
      ((strip-text-p superior?) (return t))
      ((do-not-strip-text-p superior?) (return nil)))))








;;; Make-new-stripped-text returns a new stripped text, which may be used
;;; to replace the text in a text slot when it is stripped.  It is not eq
;;; to any other text.

;;; A stripped text is the text consisting of just four dots (....) with
;;; no whitespace or anything else at all.

(defun make-new-stripped-text ()
  (convert-text-string-to-text (copy-constant-wide-string #w"...."))
  )

;; Alternative texts: "....", "...", "****", {Text Unavailable}, the class
;; slot description text?





;;; Stripped-text-p is true if text is equal to archtypal-stripped-text.

;;; Archtypal-stripped-text is globally bound to a stripped text and is used
;;; by stripped-text-p for comparing texts.

;;; At present, unfortunately, it is impossible to tell if stripped-text-p
;;; of a text is true because it was stripped or because the user changed
;;; it to be that way.  Therefore, when a text is said to be stripped, it
;;; usually means that stripped-text-p of it is true, not that it is
;;; definitely known that the text stripping operation was performed on the
;;; text.

(def-kb-specific-variable archtypal-stripped-text sequences3
  (:funcall make-new-stripped-text)
  nil
  reclaim-text)

(defun stripped-text-p (text)
  (equalw archtypal-stripped-text text))




;;; Text-slots-in-frame-have-been-stripped-p is true if frame has at least one
;;; text slot, the text of which has been stripped.

(defun text-slots-in-frame-have-been-stripped-p (frame)
  (loop with class = (class frame)
	with slot-descriptions = (slot-descriptions (class-description-slot frame))
	for slot-description in slot-descriptions
	for slot-name = (unique-slot-name slot-description)
	as type-of-slot? = (type-of-slot-if-editable class slot-name)
	thereis (and type-of-slot?
		     (text-slot-type-p type-of-slot?)
		     (let ((value? (get-slot-value frame slot-name)))
		       (and value?
			    (stripped-text-p (cdr value?)))))))

;; The loop above has most of the same code as and has to be in synch with
;; strip-texts-from-item! (MHD 6/27/90)

;; The name text-slots-in-frame-have-been-stripped-p was chosen to lend
;; itself to being implemented by means of a frame flag, if we ever want
;; to do it that way. (MHD 6/27/90)





;;;; Some Consequences of Stripping


;;; Here are some further conventions and consequences of stripping:
;;;
;;; (1) When an item has any text slots that have been stripped, it may not be
;;; changed (i.e. edited manually, changed via the "change the text of ..."
;;; action, have substitutions performed via the replace command in
;;; Inspect) unless it is in a message.
;;;
;;; (2) Currently, a slot can only be recognized as having stripped text
;;; by looking at its text and seeing that it contains just the text "....".
;;;
;;; (3) As a result of (2), you can create a free text which contains
;;; just the text "....", and then you will not be able to edit it.  (Messages
;;; are an exception to this, as stated in (1).)
;;;
;;; (4) You can highlight the text in a stripped text.  That is, the Inspect
;;; command
;;;
;;;     highlight ".." in every item
;;;
;;; will certainly match every item which has stripped text.
;;;
;;; (5) The Main Menu Miscellany menu choices recompile-all-rules and
;;; recompile-everything will not recompile text slots containing stripped
;;; text.
;;;
;;; (6) The text of expression(s)-to-display and label-to-display slots
;;; of readout tables and graphs is stripped, but the text displayed in
;;; the original graphic representations is preserved.  This allows the
;;; text of their expressions to be stripped without destroying their
;;; labels.
;;;
;;; (7) Text stripping does not happen in slots which are text slots
;;; but have no text (represented internally as nil in the slot value).
;;; Thus, if a frame with only text slots with no text were stripped,
;;; its text slots would remain editable.


;; The above by MHD, 6/28/90



;; Files must end with CR


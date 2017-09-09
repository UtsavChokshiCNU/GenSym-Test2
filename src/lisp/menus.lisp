;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module MENUS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David








;;;; Forward References in MENUS


;; To CONTROLS

(declare-forward-reference evaluate-user-menu-choice-condition function)
(declare-forward-reference add-or-delete-button-frame-note function)
(declare-forward-reference check-for-and-fix-up-cloned-embedded-rule function)


;; To EDIT

(declare-forward-reference enter-editing-context function)
(declare-forward-reference editor-parameters variable)
(declare-forward-reference change-edit-box-cursor-position function)
(declare-forward-reference find-position-in-text function)
(declare-forward-reference find-position-in-text-given-image-plane function)


;; To CONTROLS

(declare-forward-reference add-as-inferior-block function)

;; To NEW-RULES

(declare-forward-reference generate-and-schedule-rule-instances function)

;; To COMP-UTILS

(declare-forward-reference compilations-up-to-date-p function)
(declare-forward-reference runnable-p-function function)


;; To KB-SAVE2

(declare-forward-reference current-kb-serial-number variable)

;; To KB-LOAD2

(declare-forward-reference note-frame-with-compilation-removed function)
(declare-forward-reference loading-kb-p variable)
(declare-forward-reference reading-kb-p variable)
(declare-forward-reference loading-version-3-or-earlier-kb-p function)

;; To RUN

;; (declare-forward-reference run-event-handler function)
(declare-forward-reference mouse-leeway-in-workspace function)


;; To NEW-MENUS

(declare-forward-reference image-plane-of-mouse-pointer function)


(declare-forward-reference inside-breakpoint-p variable)

(declare-forward-reference generate-spot-if-in-workspace-frame function)

(declare-forward-reference lambda-list-of-ui-command-named function)


;;;; Short Menus


;;; Short-menus?, when t, puts G2 in the mode using its short menus. This is off
;;; by default.  This is a system variable.  It survives knowledge base changes.

;;; The user can switch to short menus by choosing "Short Menus" from the
;;; Main Menu Miscellany menu and can switch to full menus by choosing "Long
;;; Menus" from the Main Menu Miscellany menu.

(def-system-variable short-menus? menus nil)








;;;; Menu Choice Lists


(def-global-property-name menu-string)

;;; `Def-menu-string' may be used for a menu choice or heading.  For purposes
;;; of users interfacing to choice symbols, menu-strings must be equivalent to
;;; the symbol they are for when compared by means of discarding
;;; non-alphanumeric characters and ignoring lettercase.  E.g., change-to-yes
;;; <=> change to "yes"; rotate-reflect <=> rotate/reflect; load-kb <=> "Load
;;; KB"; but NOT: quit <=> "cancel"; etc.

(defmacro def-menu-string (choice-or-heading-symbol menu-string-or-symbol)
  `(setf (menu-string ',choice-or-heading-symbol)
	 ',(if (symbolp menu-string-or-symbol)
	       menu-string-or-symbol
	       (copy-text-string menu-string-or-symbol))))

;; The spec for equivalence was added today.  There had been one violation:
;; table-from-short-representation/"table"; this was eliminated today.  (MHD
;; 6/2/92)
 
;; As of today, there are no users of def-menu-string for heading symbols,
;; only for choice symbols.  This macro was named def-menu-choice until today.
;; (MHD 8/29/91)

;; The only reason for supplying a symbol as a menu-string is to change some
;; non-alphabetic characters without specifying any particular capitalization.
;; When translated-string-for-symbol sees a string as a menu-string, no further
;; capitalization is applied. -fmw, 2/5/03


;;; Display-table-p ...

(defun display-table-p (table)
  (or (frame-of-class-p table 'graph)
      (frame-of-class-p table 'readout-table)))

;; Move elsewhere!!! Document!!!




;;; A `built-in menu choice symbol' is a menu choice symbol defined by the system,
;;; as opposed to one defined by users.  A `directory of built-in menu choices'
;;; is maintained by def-menu, which stores pairs of choice symbols and grammar
;;; categories (e.g. item-menu-choice).  Def-menu uses declare-built-in-menu-choice
;;; to add to the directory (at load-time).  During the running of G2, the user
;;; menu choice facility uses the predicate built-in-menu-choice-p to tell if
;;; menu choice symbols are already built-in.
 


;;; An alist of  (grammar-category-for-choice . list-of-choice-symbols)

(defvar directory-of-built-in-menu-choices nil)



;;; The macro `def-grammar-choices-for-menu' adds the given choices to the
;;; built-in menu choice directory for the given grammar category.

(defmacro def-grammar-choices-for-menu (grammar-category &rest choices)
  `(def-grammar-choices-for-menu-1 ',grammar-category ',choices))


(defun def-grammar-choices-for-menu-1 (grammar-category-for-choice choice-symbols)
  (loop for choice-symbol in choice-symbols
	as grammar-rule = `(,grammar-category-for-choice ',choice-symbol)
	collect grammar-rule into grammar-rules
	finally
	  (when grammar-rules
	    (add-grammar-rules grammar-rules)))
  
  (loop for choice-symbol in choice-symbols
	do (let ((association?
		   (assq grammar-category-for-choice directory-of-built-in-menu-choices)))
	     (if association?
		 (if (not (memq choice-symbol (cdr association?)))
		     (setf (cdr association?)	; keep in order
			   (nconc (cdr association?) (list choice-symbol))))
		 (push (cons grammar-category-for-choice (list choice-symbol))
		       directory-of-built-in-menu-choices))))
  grammar-category-for-choice)




(defun built-in-menu-choice-p (choice-symbol &optional grammar-category-for-choice?)
  (if grammar-category-for-choice?
      (memq choice-symbol
	    (cdr (assq grammar-category-for-choice? directory-of-built-in-menu-choices)))
      (loop for (nil . choice-symbols)
		in directory-of-built-in-menu-choices
	    thereis (memq choice-symbol choice-symbols))))





#+development
(defun print-menu-choice-to-file (&optional (filename "g2menu.text"))
  (with-open-file (*standard-output* filename :direction :output)
    (write-string "     Menu Choices for G2       ")
    (multiple-value-bind (second minute hour date month year)
	(get-decoded-real-time)
      (declare (ignore second minute hour))
      (write date)
      (write-string " ")
      (write (nth (-f month 1) '(jan feb mar apr may jun jul aug sep oct nov dec))
	     :case :capitalize)
      (write-string " ")
      (write year))
    (terpri)
    (terpri)
    (format t
      "     Copyright (c) 1986 - 2017 Gensym Corporation.
            All Rights Reserved.

     CONFIDENTIAL

     The information contained herein is confidential and
     proprietary to Gensym Corporation.  It may not be disclosed or
     transferred, directly or indirectly, to any third party without
     the explicit written permission of Gensym Corporation.")
    (terpri)
    (loop for (name . choices) in directory-of-built-in-menu-choices
	  do (format t "~%~a" name)
	     (terpri)
	     (loop for choice in choices
		   do (format t "~%~(~a~)" choice))
	     (terpri)
	     (terpri))

    ;; From NEW-TABLES
    (format t "

OTHER-TABLE-EDITS

edit-cell-expression
edit-cell-format
add-row
add-column
delete-row
delete-column")
    
    ;; from handle-choice-for-block-menu in FACILITIES
    (format t "



ROTATE/REFLECT

90-clockwise
90-counterclockwise
180
left-right-reflection
up-down-reflection")

    ;; from post-color-menu in FACILITIES
    (format t "



COLOR-MENUS

background-color
foreground-color
border-color
text-color")	    
    ))









;;;; Menus



;;; A `menu' is a subclass of table, the text cells of which may each represent
;;; a `menu choice'.  A menu choice is usually selected when the user presses the
;;; mouse down, moves the mouse inside of the cell representing the choice, and
;;; releases the mouse.  A `menu choice list' is a list of menu choices.

;;; At present, a menu should never be saved in a KB.

(def-class (menu table define-predicate)
  (menu-choice-list nil vector-slot system)
  (menu-choice-function nil vector-slot system)
  (menu-choice-arglist nil vector-slot system)		    ; Additional args to the choice function.
  (x-in-window-prior-to-posting-menu nil vector-slot system) ; Of the original event which posted the menu.
  (y-in-window-prior-to-posting-menu nil vector-slot system)
  (call-menu-choice-function-with-nil-if-dismissed? nil vector-slot system) ; Not needed: fixup choice functions.
  (menu-cell-currently-highlighted? nil vector-slot system) ; Moved here from selection-state.  -fmw, 9/20/93

  ;; Used to find menus which are for "the same thing".
  (what-this-is-a-menu-for? nil lookup-slot system)

  ;; Each menu remembers the mouse-pointer which caused it to be posted.
  (menu-mouse-pointer nil lookup-slot system)

  ;; A flag which prevents parent walking menus from being recycled.
  (reason-to-not-recycle-menu nil lookup-slot system))


;; The definition above needs some amount of work if menus were to be allowed
;; to be saved in KBs.  (MHD 4/9/91)
;; Choice-menus, token-menus, etc.?


#+development
(defun title-of-menu (menu)
  (loop for row in (table-rows menu)
	thereis (and (consp row)
		     (loop for cell? in row
			   when (and cell? (not (cell-is-block-p cell?)))
			     return (convert-text-to-text-string (text? cell?))))))

#+development
(defun title-of-menu-workspace (menu-workspace)
  (let ((menu? (first-subblock menu-workspace)))
    (when menu?
      (title-of-menu menu?))))

#+development
(def-development-printer print-menu-table (thing stream)
  (when (and (framep thing)
	     (frame-of-class-p thing 'menu))
    (printing-random-object (thing stream)
      (format stream "~a~@[ ~s~]"
	      (class thing)
	      (title-of-menu thing)))
    thing))


;;; The slot value reclaimer for the menu-choice-list reclaims only the backbone
;;; of this list.  The conses and strings that make up the choice will be
;;; reclaimed separately by virtue of their being elements of the text cell plists
;;; of the cells of the menu.

;; Obsolete.  Just copy (for slot value) each element of this list into the
;; plists (like the replacement for this facility).  (MHD 3/31/94)
;; 
;; ;;; The slot value reclaimer for the menu-choice-list reclaims only the backbone
;; ;;; of this list.  The conses and strings that make up the choice will be
;; ;;; reclaimed separately by virtue of their being elements of the text cell plists
;; ;;; of the cells of the menu.
;;
;; (def-slot-value-reclaimer menu-choice-list (menu-choice-list)
;;   (reclaim-slot-value-list menu-choice-list))


(def-slot-value-reclaimer menu-choice-function (menu-choice-function)
  menu-choice-function)				; do nothing



;;; The slot value reclaimer for menu-choice-arglist just reclaims the backbone
;;; of this list.

(def-slot-value-reclaimer menu-choice-arglist (menu-choice-arglist)
  (reclaim-slot-value-list menu-choice-arglist))



;;; The slot value reclaimer for what-this-is-a-menu-for? deletes menu as
;;; an element the menus-for-this slot of block?, if block? is non-nil.

(def-slot-value-reclaimer what-this-is-a-menu-for? (block? menu)
  (when block?
    (setf (menus-for-this block?)
	  (delete-slot-value-element menu (menus-for-this block?)))))


;;; The value of menu-cell-currently-highlighted? is a list taken from
;;; the table-rows slot of this very menu.  So it has already been reclaimed.
;;;  -fmw, 9/23/93

(def-slot-value-reclaimer menu-cell-currently-highlighted? (cell menu)
  (declare (ignore cell))
  (setf (menu-cell-currently-highlighted? menu) nil))


;;  -fmw, 10/13/93
(def-slot-value-reclaimer menu-mouse-pointer (mouse-pointer)
  (release-mouse-pointer-if-any mouse-pointer))




;;;; Menu Parameters




;;; The `menu parameters' system table holds menu parameters.

(def-system-frame menu-parameters formats

  (alignment-for-menu-choices	  ; LEFT, CENTER, RIGHT
    left system vector-slot (type alignment))

  (when-to-allow-multiple-menus	  ; NEVER, ALWAYS, IF-DIFFERENT
    never system vector-slot (type when-to-allow-multiple-menus))

  (walking-menus t system lookup-slot (type yes-or-no))

  (automatically-show-developer-menu-bar
    (on (pause reset connect))
    system lookup-slot (type automatically-show-developer-menu-bar)))

(define-slot-alias walking-menus? walking-menus menu-parameters)



(def-class-method initialize (menu-parameters)
  (funcall-superior-method menu-parameters)
  (reset-walking-menus-if-needed menu-parameters))

(def-class-method initialize-after-reading (menu-parameters)
  (funcall-superior-method menu-parameters)
  (reset-walking-menus-if-needed menu-parameters))

(defun reset-walking-menus-if-needed (menu-parameters)
  (when (and reading-kb-p (loading-version-3-or-earlier-kb-p))
    (setf (walking-menus menu-parameters) nil)))

;; Amazing fact: Reading a KB calls exactly one of the initialize or
;; initialize-after-reading methods on a system table, depending on whether the
;; system table was actually read from the KB or was instantiated directly by
;; G2 to order to fill out the suite (See `add-newer-system-tables-to-suite-if-necessary').
;; Also see similar code for drawing-parameters.




;; Honor alignment-for-menu-choices for edit menus!!  (Or consider not doing that, 
;; or separately parameterizing that.)

;; Consider parameterizing highlighting of selected menu choices -- we had intended
;; to do that when we put that feature in.  Note that edit menus do not so highlight.
;; Perhaps they could also or that could be separately parameterized.

;; Consider providing a menu choice blinking parameter ala the Mac control panel.

;; Consider dismiss-menus-after-choosing? or allow-pushpins-on-menus, after doing
;; pushpins.  Note that color-parameters has its own dismiss-color-menu-after-choosing
;; parameter.

;; Put a font-for-menus slot in FONTS!  It would be slick if it could also be here
;; and they would stay in synch or, even slicker, be the same slot shared by both
;; tables.

;; Many users have suggested that they really want IF-DIFFERENT to be the
;; default, but I think they will prefer NEVER once they see it.  Many
;; users claim they are devoted to the old (2.1 & earlier) ALWAYS behavior.

;; Above notes and system frame written today. (MHD 1/18/91)



(def-grammar-category when-to-allow-multiple-menus ()
  never
  always
  (('for 'different 'selections) if-different))


(def-grammar-category alignment ()
  left center right)


(def-slot-value-writer when-to-allow-multiple-menus (value)
  (if (eq value 'if-different)
      (twrite-string "for different selections")
      (twrite-symbol value)))


(def-slot-value-writer-as-existing-function alignment write-symbol-from-slot)





(defun choose-menu-item-format-per-menu-parameters (fat-p)
  (if fat-p
      (case (alignment-for-menu-choices menu-parameters)
	(left 'fat-left-aligned-menu-item-format)
	(center 'fat-center-aligned-menu-item-format)
	(right 'fat-right-aligned-menu-item-format))
      (case (alignment-for-menu-choices menu-parameters)
	(left 'left-aligned-menu-item-format)
	(center 'center-aligned-menu-item-format)
	(right 'right-aligned-menu-item-format))))

;;; Choose-cascade-menu-item-format-per-menu-parameters ...

(defun choose-cascade-menu-item-format-per-menu-parameters ()
  (case (alignment-for-menu-choices menu-parameters)
    (left 'left-aligned-cascade-menu-item-format)
    (center 'center-aligned-cascade-menu-item-format)
    (right 'right-aligned-cascade-menu-item-format)))


(defun-simple draw-cascading-menu-marker
	      (text-box? color-change-case?
		highlight-or-new-background-color? new-text-color?
		text-box-format text-cell-plist unhighlighted-background-color-value
		cell-background-color-difference
		left-edge-of-cell-in-window top-edge-of-cell-in-window
		right-edge-of-cell-in-window bottom-edge-of-cell-in-window)
  (declare
    (ignore text-box? color-change-case?
	    highlight-or-new-background-color? new-text-color? text-cell-plist
	    unhighlighted-background-color-value cell-background-color-difference
	    bottom-edge-of-cell-in-window))
  (let* ((position-type
	   (case (name-or-names-for-frame text-box-format)
	     (left-aligned-cascade-menu-item-format-new-large 'new-large-right)
	     (left-aligned-cascade-menu-item-format-new-small 'new-small-right)
	     (left-arrow-left-aligned-cascade-menu-item-format-new-large 'new-large-left)
	     (left-arrow-left-aligned-cascade-menu-item-format-new-small 'new-small-left)
	     (left-arrow-left-aligned-cascade-menu-item-format 'old-left)
	     (t 'old-right)))		      ; = left-aligned-cascade-menu-item-format
	 (old-position-format (or (eq position-type 'old-left)
				  (eq position-type 'old-right)))
	 (right-edge-in-workspace
	   (x-in-workspace
	     (if old-position-format
		 right-edge-of-cell-in-window
		 (right-edge-of-workspace-area-in-window current-image-plane))))
	 (left-edge-in-workspace
	   (x-in-workspace
	     (if old-position-format
		 left-edge-of-cell-in-window
		 (left-edge-of-workspace-area-in-window current-image-plane))))
	 (top-edge-in-workspace
	   (y-in-workspace top-edge-of-cell-in-window)))
    (case position-type
      (new-large-right
       (draw-rubber-stamp-widget
	 'right-marker-for-cascading-menu ; 'marker-for-cascading-menu
	 (-w right-edge-in-workspace 12) (+w top-edge-in-workspace 7)
	 (-w right-edge-in-workspace 5) (+w top-edge-in-workspace 17)))
      (new-small-right
       (draw-rubber-stamp-widget
	 'right-marker-for-cascading-menu
	 (-w right-edge-in-workspace 12) (+w top-edge-in-workspace 5)
	 (-w right-edge-in-workspace 5) (+w top-edge-in-workspace 14)))
      (new-large-left
       (draw-rubber-stamp-widget
	 'left-marker-for-cascading-menu
	 (+w left-edge-in-workspace 5) (+w top-edge-in-workspace 7)
	 (+w left-edge-in-workspace 12) (+w top-edge-in-workspace 17)))
      (new-small-left
       (draw-rubber-stamp-widget
	 'left-marker-for-cascading-menu
	 (+w left-edge-in-workspace 5) (+w top-edge-in-workspace 5)
	 (+w left-edge-in-workspace 12) (+w top-edge-in-workspace 14)))
      (old-right
       (draw-rubber-stamp-widget
	 'right-marker-for-cascading-menu
	 (-w right-edge-in-workspace 14) (+w top-edge-in-workspace 7)
	 (-w right-edge-in-workspace 4) (+w top-edge-in-workspace 17)))
      (old-left
       (draw-rubber-stamp-widget
	 'left-marker-for-cascading-menu
	 (+w left-edge-in-workspace 4) (+w top-edge-in-workspace 7)
	 (+w left-edge-in-workspace 14) (+w top-edge-in-workspace 17)))))
  nil)

(def-post-draw-method-for-text-box-format
  left-aligned-cascade-menu-item-format
  #'draw-cascading-menu-marker)

(def-post-draw-method-for-text-box-format
  left-arrow-left-aligned-cascade-menu-item-format
  #'draw-cascading-menu-marker)
 
(def-post-draw-method-for-text-box-format
  center-aligned-cascade-menu-item-format
  #'draw-cascading-menu-marker)
 
(def-post-draw-method-for-text-box-format
  right-aligned-cascade-menu-item-format
  #'draw-cascading-menu-marker)

(def-post-draw-method-for-text-box-format
  left-aligned-cascade-menu-item-format-new-large
  #'draw-cascading-menu-marker)

(def-post-draw-method-for-text-box-format
  left-arrow-left-aligned-cascade-menu-item-format-new-large
  #'draw-cascading-menu-marker)


(def-post-draw-method-for-text-box-format
  left-aligned-cascade-menu-item-format-new-small
  #'draw-cascading-menu-marker)

(def-post-draw-method-for-text-box-format
  left-arrow-left-aligned-cascade-menu-item-format-new-small
  #'draw-cascading-menu-marker)



;;; `All-menu-heading-format-names' is just a constant list enumerating all
;;; known names of text cell formats for menu headings.

(defvar all-menu-heading-format-names
  '(fat-left-aligned-menu-heading-format
    fat-center-aligned-menu-heading-format
    fat-right-aligned-menu-heading-format
    left-aligned-menu-heading-format
    center-aligned-menu-heading-format
    right-aligned-menu-heading-format))


;;; `Menu-heading-text-cell-p' is true if text-cell is used as a menu heading,
;;; rather than as a menu item with an actual choice in it.  It is to be used on
;;; text cells in a menu.

(defun menu-heading-text-cell-p (text-cell)
  (memq (name-or-names-for-frame (text-cell-format text-cell))
	all-menu-heading-format-names))


;;; Choose-menu-heading-format-per-menu-parameters ...

(defun choose-menu-heading-format-per-menu-parameters (&optional fat-p)
  (if fat-p
      (case (alignment-for-menu-choices menu-parameters)
	(left 'fat-left-aligned-menu-heading-format)
	(center 'fat-center-aligned-menu-heading-format)
	(right 'fat-right-aligned-menu-heading-format))
      (case (alignment-for-menu-choices menu-parameters)
	(left 'left-aligned-menu-heading-format)
	(center 'center-aligned-menu-heading-format)
	(right 'right-aligned-menu-heading-format))))


;;; Choose-color-menu-item-format-per-menu-parameters ...

(defun choose-color-menu-item-format-per-menu-parameters ()
  (case (alignment-for-menu-choices menu-parameters)
    (left 'left-aligned-color-menu-item-format)
    (center 'center-aligned-color-menu-item-format)
    (right 'right-aligned-color-menu-item-format)))




;;;; Posting Menus


;;; An `menu workspace' holds a menu.

(def-class (menu-workspace temporary-workspace)
  (menu-workspace-for-is-for-walking-submenu-p nil vector-slot system)
  ;; refinement on ws slot; show whole title bar:
  (stretch-new-image-planes-for-caption-p t))


#+development
(def-development-printer print-menu-workspace (thing stream)
  (when (and (framep thing)
	     (frame-of-class-p thing 'menu-workspace))
    (printing-random-object (thing stream)
      (format stream "~a~@[ ~s~]"
	      (class thing)
	      (title-of-menu-workspace thing)))
    thing))


(def-spot entire-menu-spot
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p nil
    :abstract-type nil
    :type-of-frame-represented menu)

(def-spot entire-focus-menu-spot
    :include entire-menu-spot)

(def-class-method generate-spot (menu-workspace mouse-pointer)
  (or (generate-spot-if-in-workspace-frame menu-workspace mouse-pointer)
      (push-more-detailed-spot
	mouse-pointer
	(if (eq menu-workspace
		(block-with-selection-focus-of-workstation current-workstation))
	    (make-entire-focus-menu-spot)
	    (make-entire-menu-spot))
	(first-subblock menu-workspace) ;; i.e. the menu table.
	)))



;;; The function `find-menu-workspace-to-dismiss' returns a displayed
;;; menu workspace which is "the same" as the given one in the following sense:
;;;  (1) it is for the same object or we don't care, and
;;;  (2) it has EQUAL rows to the present one.
;;; If we find a menu to dismiss, return (values menu-workspace image-plane).
;;; Otherwise, return NIL, which means that multiple menus may be allowed.

(defun find-menu-workspace-to-dismiss (menu-workspace)
  (let ((menu
	  (first-subblock menu-workspace))
	(when-to-allow-multiple-menus
	  (when-to-allow-multiple-menus menu-parameters)))
    ;; <= 2.1 behavior
    (unless (eq when-to-allow-multiple-menus 'always)
      (loop for image-plane in (stack-of-image-planes current-workstation-detail-pane)
	    as workspace? = (workspace-on-image-plane? image-plane)
	    doing
	(when (and workspace? (frame-of-class-p workspace? 'menu-workspace))
	  (let ((other-menu (first-subblock workspace?)))
	    (when (and
		    (null (reason-to-not-recycle-menu other-menu))

		    (or (eq when-to-allow-multiple-menus 'never)
			;; Otherwise, must be "the same" menu: for the same object,
			;; and with EQUAL rows.
			(and
			  (eq (what-this-is-a-menu-for? menu)	    ; Note A.
			      (what-this-is-a-menu-for? other-menu))
			  ;; This check was too restrictive.  It allows, eg,
			  ;; the main-menu and the system-tables menu up at
			  ;; once.  Besides, new menus have unique command instances
			  ;; in their items lists, so are never EQUAL. -fmw, 6/14/94
;			  (equal (table-rows menu)
;				 (table-rows other-menu))
			  )))
	      (return (values workspace? image-plane)))))))))

;; Note A: the above is an alternative to the following, equivalent except for
;; the fact that the above picks off menus that are "for nothing", i.e., that
;; have nil in their what-this-is-a-menu-for?  slot, as "the same selection";
;; e.g., a main menu miscellany menu would be considered "the same selection"
;; as the main menu or the run options menu.  That seems pretty natural right
;; now, but only because they are all really part of the same menu, the main
;; menu.  The alternative below would seem strange, because it would allow any
;; number of main menus.  The long-term solution is to put something unique in
;; the slot what-this-is-a-menu-for?  when this is the main menu to say that
;; this menu represents the "system" (or whatever the main menu is "for").
;; (MHD 4/29/91)
;; ALT:
;(member
;  (first-subblock menu-workspace)
;  (let ((block-this-is-a-menu-for?
;	  (what-this-is-a-menu-for?
;	    (first-subblock workspace?))))
;    (if block-this-is-a-menu-for?
;	(menus-for-this block-this-is-a-menu-for?))))



	     
;;; The function `post-menu-workspace' makes the given menu-workspace visible
;;; on the screen, maybe removing any similar menu which is already on the
;;; screen.  A menu workspace that either does not have its
;;; do-not-dismiss-after-choosing?  slot set or has an equal table-rows slot as
;;; the workspace to show on an existing image plane in the current workstation
;;; detail pane.

;;; Otherwise, a new image plane is created and shown in the current
;;; workstation detail pane.  In either case, the image plane that is to show
;;; menu-workspace is displayed at the front of the stack of image planes with
;;; its top center as close to (x-in-window, y-in-window) as possible, subject
;;; to the constraint that the entire image plane must fit within the pane; the
;;; image plane is, in fact, scaled to make that happen if necessary.

(defun post-menu-workspace
    (menu-workspace x-in-window y-in-window
		    &optional
		    allow-multiple-menus?
		    default-x-scale?
		    default-y-scale?
		    x-for-left-adjusting?
		    x-for-right-adjusting?
		    direction-for-adjusting?)
  (multiple-value-bind (other-menu-workspace? image-plane?)
      (unless allow-multiple-menus?
	(find-menu-workspace-to-dismiss menu-workspace))

    ;; Avoid the white flash, most obvious in TeleWindows.
    (let ((current-draw-paper-p nil))
      (multiple-value-bind (image-plane adjustment)
	  (post-workspace-in-pane
	    menu-workspace current-workstation-detail-pane
	    x-in-window y-in-window
	    :existing-image-plane? image-plane?
	    :default-x-scale? default-x-scale?
	    :default-y-scale? default-y-scale?
	    :x-for-left-adjusting? x-for-left-adjusting?
	    :x-for-right-adjusting? x-for-right-adjusting?
	    :direction-for-adjusting? direction-for-adjusting?)
	(declare (ignore image-plane))
	
	(when other-menu-workspace?
	  (delete-menu other-menu-workspace?))

	;; Get the menu up in a hurry.
	(when (and (or (eq direction-for-adjusting? 'left)
		       (eq direction-for-adjusting? 'right))
		   (not (eq adjustment direction-for-adjusting?)))
	  (delete-menu menu-workspace)
	  (return-from post-menu-workspace (values nil adjustment)))
	
	(force-workspace-drawing menu-workspace)

	(when (and (=f (mod (frame-hash menu-workspace) 11) 0)
		   g2-has-been-started?)
	  (have-a-nice-day))
	(values menu-workspace adjustment)))))

;; Consider having this take an optional menu-workspace-not-to-replace?
;; argument.  This would be useful for the case where we are transitioning
;; from a menu to its submenu.  In the case of the color menu in particular,
;; where do-not-dismiss-after-choosing? is often set, this would prevent
;; it from replacing the region menu (e.g. the one with the choices background-
;; color and foreground-color for a workspace) instead of finding a previously
;; displayed color menu, which usually happens now because the region menu
;; typically occurs earlier in the stack of subblocks, having been more recently
;; displayed. Another way to accomplish the same goal would be to make two
;; complete passes through the stack of image planes, preferring an "equal" menu
;; workspace on first pass, and accepting any dismissable menu workspace on the
;; second pass.  Consider iterating over menu-workspaces instances instead of
;; image planes.  That might also happen to fix the above problem most of the
;; time in practice.  (MHD 10/16/90)







;;;; Menu Spacers

(def-text-cell-format menu-spacer-format
  text-cell-font-map (hm14)
  text-cell-line-height 0			; 1 for the double-bar affect
  text-cell-line-spacing 0
  text-cell-baseline-position 0
  text-cell-left-margin 0
  text-cell-top-margin 0
  text-cell-right-margin 0
  text-cell-bottom-margin 0)


;;; The function `make-spanning-table-row' returns a table row which makes the given
;;; text-cell span all of the columns.

(defun make-table-spanning-row (text-cell &optional number-of-columns)
  (let ((list (make-slot-value-list (or number-of-columns 1))))
    (loop for sublist on list do (setf (car sublist) nil))
    (setf (car (last list)) text-cell)
    list))



;;; The function `make-table-spacer-cells' returns a list of text cells
;;; which serve as a thick, horizontal separator in a table.  COUNT
;;; defaults to 3 and NUMBER-OF-COLUMNS defaults to 1.

(defun make-table-spacer-cells (&optional count number-of-columns)
  (loop repeat (or count 3)
	collect	(make-table-spanning-row
		  (make-text-cell (slot-value-list (
		                                    copy-constant-wide-string #w""
		                                    ))
				  (get-or-make-format-frame 'menu-spacer-format))
		  number-of-columns)
	  using slot-value-cons))

;; Note that this hack does not yield a single thick line at all workspace scales.



;;; The function `menu-spacer-cell-p' returns T if the text cell (presumably
;;; from a menu) is a menu spacer.

(defun menu-spacer-cell-p (text-cell)
  (and (text-cell-format text-cell)
       (eq (name-or-names-for-frame (text-cell-format text-cell))
	   'menu-spacer-format)))












;;; The function `delete-menu' should be called to delete menu workspaces
;;; instead of delete-frame.

(defun delete-menu (menu-or-menu-workspace)
  (if (superblock? menu-or-menu-workspace)
      (delete-frame (superblock? menu-or-menu-workspace))
      (delete-frame menu-or-menu-workspace)))

;; This is necessary because you usually want to get rid of the entire workspace and
;; image plane that a menu (a table) is on.  This is NOT the case with token menus,
;; of course.  These are currently special cased by the mouse dispatcher, of all things.

;; Find a better way to do this, perhaps with methods.



(defun twrite-menu-backtrace-info ()
  (twrite-string "  choice: ")
  (twrite-symbol (pop-backtrace-information)))


;;; If the variable `highlight-selected-menu-items?' is true, selected menu
;;; items are to be highlighted.

(defparameter highlight-selected-menu-items? t)



;;; `Find-workspace-distance-to-rectangle-if-reasonable' finds the distance
;;; from from the point (x-in-workspace, y-in-workspace) to the rectangle given
;;; by left-edge, top-edge, right-edge, and bottom-edge, provided it is less
;;; than reasonable-distance.

(def-substitution-macro find-workspace-distance-to-rectangle-if-reasonable
      (x-in-workspace y-in-workspace reasonable-distance
       left-edge top-edge right-edge bottom-edge)
  (let (distance-if-in-range?)
    (if (and (setq distance-if-in-range?
		   (cond
		     ;; check left
		     ((<w x-in-workspace left-edge)
		      (cond
			((<w y-in-workspace top-edge)
			 (find-workspace-distance-if-in-range
			   x-in-workspace y-in-workspace left-edge
			   top-edge reasonable-distance))
			((>w y-in-workspace bottom-edge)
			 (find-workspace-distance-if-in-range
			   x-in-workspace y-in-workspace left-edge
			   bottom-edge reasonable-distance))
			(t
			 (-w left-edge x-in-workspace))))
		     ;; check right
		     ((>w x-in-workspace right-edge)
		      (cond
			((<w y-in-workspace top-edge)
			 (find-workspace-distance-if-in-range
			   x-in-workspace y-in-workspace right-edge
			   top-edge reasonable-distance))
			((>w y-in-workspace bottom-edge)
			 (find-workspace-distance-if-in-range
			   x-in-workspace y-in-workspace right-edge
			   bottom-edge reasonable-distance))
			(t
			 (-w x-in-workspace right-edge))))
		     ;; check center top
		     ((<w y-in-workspace top-edge)
		      (-w top-edge y-in-workspace))
		     ;; check center bottom
		     ((>w y-in-workspace bottom-edge)
		      (-w y-in-workspace bottom-edge))
		     ;; ok, it's dead center
		     (t 0)))
	     (<w distance-if-in-range? reasonable-distance))
	distance-if-in-range?)))

;; This was moved here from RUN because it is a macro and needs to be referenced
;; by pick-cell-from-table, below. (MHD 7/9/92)




;;; `Pick-cell-from-table' ...  returns either nil if the position (x-in-window,
;;; y-in-window) is not within a cell of the table or eight values: ...  A
;;; returned cell can be either a text cell or a block (though not a subtable,
;;; because pick-cell-from-table is applied recursively in that case).

;;; Only-if-in-text?  is used the same way as in find-position-in-text.  See
;;; find-position- in-text on its use.

;;; If find-nearest-cell?  is true, this finds the nearest cell, even if the
;;; position (x-in-window, y-in-window) is not within a cell, as long it is as
;;; close as it would have to be for the table to be "near the mouse" (see
;;; find-object-near-mouse in RUN), which is computed as
;;;
;;;   (+w (maxw left-border-width
;;;             top-border-width
;;;             right-border-width
;;;             bottom-border-width)
;;;       (mouse-leeway-in-workspace image-x-scale))
;;;
;;; Note that, at present, find-nearest-cell? only applies to top-level cells in
;;; table, not to cells in subtables.

;;; Find-nearest-cell? and Only-if-in-text? aren't really intended to be used
;;; together; if they are, find-nearest-cell? dominates.

;;; If consider-cell-visibility? is true, then the a cell's visibility is
;;; determined (heuristically), and if a cell is considered invisible, it cannot
;;; be picked.  To determine visiblity, any of the following criteria qualify:
;;; (a) a cell that is a block is visible; (b) a text cell that is
;;; text-cell-visible-without-text-in-image-plane-p is visible, and (c) a text
;;; cell whose text is found to be near enough (possibly based on other args)
;;; must also be text-cell-text-visible-in-image-plane-p to be considered
;;; visible.

(defun pick-cell-from-table (table image-plane x-in-window y-in-window
				   &optional
				   only-if-in-text?
				   find-nearest-cell?
				   consider-cell-visibility?)
  (let (x-in-workspace y-in-workspace)
    (with-image-plane-transform (image-plane)
      (setf x-in-workspace (x-in-workspace x-in-window))
      (setf y-in-workspace (y-in-workspace y-in-window)))
    (loop with image-x-scale = (image-x-scale image-plane)
	  with image-y-scale = (image-y-scale image-plane)
	  with table-format = (table-format table)
	  with format-of-superblock-if-a-table?
	  = (if (table-p (superblock? table))
		(table-format (superblock? table)))
	  with left-border-width
	  = (if (and format-of-superblock-if-a-table?
		     (>w (table-column-boundary-width
			   format-of-superblock-if-a-table?)
			 0))
		0
		(table-left-border-width table-format))
	  with left-edge-of-table-in-window
	  = (x-in-frame-transform (left-edge-of-block table) table image-plane)
	  with left-edge-of-table-interior-in-window
	  = (+r left-edge-of-table-in-window
		(if (=w left-border-width 0)
		    0
		    (maxr			; enforce-minimum
		      1 (delta-x-in-window left-border-width image-x-scale))))
	  with top-border-width
	  = (if (and format-of-superblock-if-a-table?
		     (>w (table-row-boundary-width
			   format-of-superblock-if-a-table?)
			 0))
		0
		(table-top-border-width table-format))
	  with top-edge-of-table-in-window
	  = (y-in-frame-transform (top-edge-of-block table) table image-plane)
	  with top-edge-of-table-interior-in-window
	  = (+r top-edge-of-table-in-window
		(if (=w top-border-width 0)
		    0
		    (maxr			; enforce-minimum
		      1 (delta-y-in-window top-border-width image-y-scale))))
	  with right-border-width			; only used nearby
	  = (if (and format-of-superblock-if-a-table?
		     (>w (table-column-boundary-width
			   format-of-superblock-if-a-table?)
			 0))
		0
		(table-right-border-width table-format))
	  with right-edge-of-table-in-window
	  = (x-in-frame-transform(right-edge-of-block table) table image-plane)
	  with right-edge-of-table-interior-in-window
	  = (-r right-edge-of-table-in-window
		(if (=w right-border-width 0)
		    0
		    (maxr			; enforce-minimum
		      1 (delta-x-in-window right-border-width image-x-scale))))
	  with bottom-edge-of-table = (bottom-edge-of-block table)
	  with bottom-edge-of-table-in-window
	  = (y-in-frame-transform bottom-edge-of-table table image-plane)
	  with bottom-border-width		; only used nearby
	  = (if (and format-of-superblock-if-a-table?
		     (>w (table-row-boundary-width
			   format-of-superblock-if-a-table?)
			 0))
		0
		(table-bottom-border-width table-format))
	  with bottom-edge-of-table-interior-in-window
	  = (-r bottom-edge-of-table-in-window
		(if (=w bottom-border-width 0)
		    0
		    (maxr			; enforce-minimum
		      1 (delta-y-in-window bottom-border-width image-y-scale))))
	  with row-boundary-width = (table-row-boundary-width table-format)
	  with row-boundary-width-in-window
	  = (if (=w row-boundary-width 0)
		0
		(maxr				; enforce-minimum
		  1 (delta-y-in-window row-boundary-width image-y-scale)))
	  with column-boundary-width = (table-column-boundary-width table-format)
	  with column-boundary-width-in-window
	  = (if (=w column-boundary-width 0)
		0
		(maxr				; enforce-minimum
		  1 (delta-x-in-window column-boundary-width image-x-scale)))
	  with remaining-row-edges = (row-edges table)

	  with nearest-cell-so-far? = nil
	  with nearest-cell-distance-so-far ; these are only looked at if
	  with row-index-of-nearest-cell	  ;  nearest-cell-so-far? is non-nil
	  with column-row-index-of-nearest-cell
	  with left-edge-of-nearest-cell
	  with top-edge-of-nearest-cell
	  with right-edge-of-nearest-cell
	  with bottom-edge-of-nearest-cell
	  
	  as row in (table-rows table)
	  as row-index from 0
	  as top-edge-of-cell
	  = (+w (top-edge-of-block table) top-border-width)
	     then (+w (pop remaining-row-edges) row-boundary-width)
	  as top-edge-of-cell-in-window
	  = top-edge-of-table-interior-in-window
	     then top-edge-of-next-cell-in-window
	  as bottom-edge-of-cell
	  = (or (car remaining-row-edges)
		(-w bottom-edge-of-table bottom-border-width))
	  as bottom-edge-of-cell-in-window
	  = (if remaining-row-edges
		(y-in-frame-transform bottom-edge-of-cell table image-plane)
		bottom-edge-of-table-interior-in-window)
	  as top-edge-of-next-cell-in-window	; "loose" for last row
	  = (+w bottom-edge-of-cell-in-window row-boundary-width-in-window)
	  unless (<=r top-edge-of-next-cell-in-window
		      (top-edge-of-pane-in-window image-plane))
	    do (loop with remaining-column-edges = (column-edges table)
		     with remainder-of-row = row
		     with column-index = -1
		     while remainder-of-row	; end test in unusual position
		     as left-edge-of-cell
		     = (+w (left-edge-of-block table) left-border-width)
			then (+w (pop remaining-column-edges)
				 column-boundary-width )
		     as left-edge-of-cell-in-window
		     = left-edge-of-table-interior-in-window
			then left-edge-of-next-cell-in-window
		     as cell = (loop do (incff column-index)
				     thereis (pop remainder-of-row)
				     ;; loses if only nils left
				     do (pop remaining-column-edges))
		     as right-edge-of-cell
		     = (or (car remaining-column-edges)		    
			   (-w (right-edge-of-block table) right-border-width))
		     as right-edge-of-cell-in-window
		     = (if remaining-column-edges
			   (x-in-frame-transform right-edge-of-cell
						 table image-plane) 
			   right-edge-of-table-interior-in-window)
		     as left-edge-of-next-cell-in-window	; "loose" for last column
		     = (+w right-edge-of-cell-in-window
			   column-boundary-width-in-window)
		     when (and (>=r x-in-window left-edge-of-cell-in-window)
			       (>=r y-in-window top-edge-of-cell-in-window)
			       (<=r x-in-window right-edge-of-cell-in-window)
			       (<=r y-in-window bottom-edge-of-cell-in-window))
		       do (return-from pick-cell-from-table
			    (if (and (cell-is-block-p cell) (table-p cell))
				(pick-cell-from-table
				  cell image-plane x-in-window y-in-window
				  only-if-in-text?) ; find-nearest-cell? doesn't apply
				(if (or (not only-if-in-text?)
					(cell-is-block-p cell)
					(and consider-cell-visibility?
					     (text-cell-visible-without-text-in-image-plane-p
					       cell image-plane))
					(and (find-position-in-text
					       nil cell left-edge-of-cell top-edge-of-cell
					       nil
					       x-in-workspace y-in-workspace
					       nil nil nil only-if-in-text?)
					     (or (not consider-cell-visibility?)
						 (text-cell-text-visible-in-image-plane-p
						   cell image-plane))))
				    (values
				      cell table row-index column-index
				      left-edge-of-cell top-edge-of-cell
				      right-edge-of-cell bottom-edge-of-cell))))
		     when find-nearest-cell?
		       do (let ((distance-if-reasonable?
				  (find-workspace-distance-to-rectangle-if-reasonable
				    x-in-workspace y-in-workspace
				    (if nearest-cell-so-far?
					nearest-cell-distance-so-far
					(+w (maxw
					      left-border-width
					      top-border-width
					      right-border-width
					      bottom-border-width)
					    (mouse-leeway-in-workspace
					      image-x-scale)))
				    left-edge-of-cell top-edge-of-cell
				    right-edge-of-cell bottom-edge-of-cell)))
			    (when (and distance-if-reasonable?
				       (or (null nearest-cell-so-far?)
					   (<w distance-if-reasonable?
					       nearest-cell-distance-so-far)))
			      (setq nearest-cell-so-far? cell)
			      (setq nearest-cell-distance-so-far
				    distance-if-reasonable?)
			      (setq row-index-of-nearest-cell row-index)
			      (setq column-row-index-of-nearest-cell column-index)
			      (setq left-edge-of-nearest-cell
				    left-edge-of-cell)
			      (setq top-edge-of-nearest-cell
				    top-edge-of-cell)
			      (setq right-edge-of-nearest-cell
				    right-edge-of-cell)
			      (setq bottom-edge-of-nearest-cell
				    bottom-edge-of-cell))))
	  finally
	    (return
	      (if nearest-cell-so-far?
		  (values
		    nearest-cell-so-far? table
		    row-index-of-nearest-cell
		    column-row-index-of-nearest-cell
		  left-edge-of-nearest-cell top-edge-of-nearest-cell
		  right-edge-of-nearest-cell bottom-edge-of-nearest-cell))))))

;; Note that this is, and must be, derived from the draw method for tables.
;; Always keep these in synch.  When in doubt, erase this, yank in the draw
;; method, and rederive it.



;;; A `menu-item-spot' is generated when ever the mouse is over a particular
;;; choice in the menu, except if the mouse is over the menu title.  The
;;; enclosing spot is a entire-menu-spot, and this is a top-level spot.

(def-spot menu-item-spot
    :slots (cell-of-menu-item
	     ;; These are all in coordiantes relative to the image-plane.
	     menu-item-spot-left menu-item-spot-top menu-item-spot-right menu-item-spot-bottom)
    :enclosing-spot-type entire-menu-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented null)



;;; A `menu-title-spot' is generated if the mouse is tracked over the title
;;; of a menu.  The enclosing spot is an entire-menu-spot, and this is a
;;; top level spot.

(def-spot menu-title-spot
    :enclosing-spot-type entire-menu-spot
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented null)



;;; The `Generate-spot for a menu' generates either
;;; a menu-item-spot, or a menu-title-spot.  In either case no further
;;; tracking is required.  This method preempts the default spot tracking
;;; and hence generate-spot is never called on menus, their tables, or
;;; their table formats.

(def-class-method generate-spot (menu mouse-pointer)
  (multiple-value-bind (cell-of-menu? table
				     row-index-of-nearest-cell
				     column-row-index-of-nearest-cell
				     left-edge-of-nearest-cell top-edge-of-nearest-cell
				     right-edge-of-nearest-cell bottom-edge-of-nearest-cell)
      (pick-cell-from-table
	menu
	(image-plane-of-mouse-pointer mouse-pointer)
	(x-of-mouse-pointer mouse-pointer)
	(y-of-mouse-pointer mouse-pointer)
	nil ; only-if-in-text?
	t ; find-nearest-cell?
	)
    (declare (ignore table row-index-of-nearest-cell column-row-index-of-nearest-cell))
    (let (spot)
      (cond
	((null cell-of-menu?)		; This happened once, dunno why.
	 (setf spot (make-menu-title-spot)))
	((and (not new-g2-classic-ui-p)
	      (eql (first (first (table-rows menu)))
		   cell-of-menu?))
	 (setf spot (make-menu-title-spot)))
	(t
	 (setf spot (make-menu-item-spot))
	 (setf (cell-of-menu-item spot) cell-of-menu?
	       (menu-item-spot-left spot) left-edge-of-nearest-cell
	       (menu-item-spot-top spot) top-edge-of-nearest-cell
	       (menu-item-spot-right spot) right-edge-of-nearest-cell
	       (menu-item-spot-bottom spot) bottom-edge-of-nearest-cell)))
      (setf (further-tracking-maybe-required? spot) nil)
      (push-more-detailed-spot mouse-pointer spot nil))))








;;;; Menu Formats





;;; Menu-table-format is the name of the table format used for formatting menus.

(def-table-format menu-table-format
  table-background-color? white
  table-border-color? black			; does not work!!!
  table-left-border-width 2			; fix!
  table-top-border-width 2
  table-right-border-width 2
  table-bottom-border-width 2
  table-row-boundary-width 1
  table-column-boundary-width 0)


(def-table-format menu-table-format-for-new-g2-classic-ui
  table-background-color? nil		; nil, so shows the workspace bg color through
  table-border-color? black
  table-left-border-width 0
  table-top-border-width 0
  table-right-border-width 0
  table-bottom-border-width 0
  table-row-boundary-width 0
  table-column-boundary-width 0)



;;; The `spot-generator on menu-table-format' is not used, it is preempted by
;;; the method on the entire-menu-spot.

#+development
(def-table-format-spot-generator menu-table-format (menu mouse-pointer)
  (declare (ignore menu mouse-pointer))
  (error "This shouldn't be called, preempted by the method on the entire-menu-spot."))





;;; Menu-item-format a subclass of text-cell-format used for formatting menu items,
;;; which are table cells.

(def-format-class (menu-item-format text-cell-format)
  (text-cell-left-margin 7)
  (text-cell-top-margin 3)
  (text-cell-right-margin 7)
  (text-cell-bottom-margin 3)
  (text-cell-font-map (hm18))
  (text-cell-line-height 20)
  (text-cell-baseline-position 15)
  (text-cell-line-spacing 0)
  (text-cell-line-quadding? nil)
  (text-cell-paragraph-indentation 0)
  (text-cell-turnover-line-indentation 0)
  (minimum-format-width-for-text-cell 200))	; was 400 -- but was never used
						;   (MHD 7/27/89)

;; The text formatter should, in the usual case, not break lines, and each column should
;; end up with a width that depends on the longest item.  Maybe ok right now.




;;; Menu-item-format is the name of the default menu item format (used by post-menu).
;;; Alignment is left.  Center-aligned-menu-item-format is the same except that
;;; alignment is centered.  Right-aligned-menu-item-format is the same except that
;;; alignment is right.

(def-menu-item-format left-aligned-menu-item-format
  text-cell-line-quadding? nil)

(def-menu-item-format center-aligned-menu-item-format
  text-cell-line-quadding? center)

(def-menu-item-format right-aligned-menu-item-format
  text-cell-line-quadding? right)



(def-menu-item-format fat-left-aligned-menu-item-format
  text-cell-line-quadding? nil
  text-cell-right-margin 20)

(def-menu-item-format fat-center-aligned-menu-item-format
  text-cell-line-quadding? center
  text-cell-right-margin 20)

(def-menu-item-format fat-right-aligned-menu-item-format
  text-cell-line-quadding? right
  text-cell-right-margin 20)


(def-menu-item-format left-aligned-cascade-menu-item-format
  text-cell-line-quadding? nil
  text-cell-right-margin 21)

(def-menu-item-format center-aligned-cascade-menu-item-format
  text-cell-line-quadding? center
  text-cell-right-margin 21)

(def-menu-item-format right-aligned-cascade-menu-item-format
  text-cell-line-quadding? right
  text-cell-right-margin 21)


;;; Menu-item-format is the name of the menu item format for menu headings.
;;; Alignment is left.  Center-aligned-menu-heading-format is the same except that
;;; alignment is centered.  Right-aligned-menu-heading-format is the same except that
;;; alignment is right. 

(def-menu-item-format left-aligned-menu-heading-format
  text-cell-line-quadding? nil
  text-cell-background-color? black
  text-cell-line-color? white)

(def-menu-item-format center-aligned-menu-heading-format
  text-cell-line-quadding? center
  text-cell-background-color? black
  text-cell-line-color? white)

(def-menu-item-format right-aligned-menu-heading-format
  text-cell-line-quadding? right
  text-cell-background-color? black
  text-cell-line-color? white)



(def-menu-item-format fat-left-aligned-menu-heading-format
  text-cell-right-margin 21
  text-cell-line-quadding? nil
  text-cell-background-color? black
  text-cell-line-color? white)

(def-menu-item-format fat-center-aligned-menu-heading-format
  text-cell-right-margin 21
  text-cell-line-quadding? center
  text-cell-background-color? black
  text-cell-line-color? white)

(def-menu-item-format fat-right-aligned-menu-heading-format
  text-cell-right-margin 21
  text-cell-line-quadding? right
  text-cell-background-color? black
  text-cell-line-color? white)





(defmacro def-new-g2-classic-ui-menu-item-small-formats () ; small
  (let ((inits
	  '(text-cell-line-quadding? nil
	    text-cell-left-margin 4
	    text-cell-top-margin 2
	    text-cell-right-margin 4
	    text-cell-bottom-margin 2
	    text-cell-font-map (hm14)
	    text-cell-line-height 16
	    text-cell-baseline-position 13
	    text-cell-line-spacing 0
	    text-cell-line-quadding? nil
	    text-cell-paragraph-indentation 0
	    text-cell-turnover-line-indentation 0
	    minimum-format-width-for-text-cell 180)))
    `(progn
       (def-menu-item-format left-aligned-menu-item-format-new-small
	 . ,inits)
       (def-menu-item-format left-aligned-cascade-menu-item-format-new-small
	 . ,(let ((copy (copy-list inits)))
	      (setf (getf copy 'text-cell-right-margin) 20)
	      copy))
       
       (def-menu-item-format left-arrow-left-aligned-menu-item-format-new-small
	 . ,(let ((copy (copy-list inits)))
	      (setf (getf copy 'text-cell-left-margin) 20)
	      copy))
       (def-menu-item-format left-arrow-left-aligned-cascade-menu-item-format-new-small
	 . ,(let ((copy (copy-list inits)))
	      (setf (getf copy 'text-cell-left-margin) 20)
	      copy)))))

(defmacro def-new-g2-classic-ui-menu-item-large-formats () ; large
  (let ((inits
	  '(text-cell-line-quadding? nil
	    text-cell-left-margin 4
	    text-cell-top-margin 3
	    text-cell-right-margin 4
	    text-cell-bottom-margin 3
	    text-cell-font-map (hm18)
	    text-cell-line-height 19
	    text-cell-baseline-position 15
	    text-cell-line-spacing 0
	    text-cell-line-quadding? nil
	    text-cell-paragraph-indentation 0
	    text-cell-turnover-line-indentation 0
	    minimum-format-width-for-text-cell 200
	    default-word-spacing #.(convert-to-text-width 5))))
    `(progn
       (def-menu-item-format left-aligned-menu-item-format-new-large
	 . ,inits)
       (def-menu-item-format left-aligned-cascade-menu-item-format-new-large
	 . ,(let ((copy (copy-list inits)))
	      (setf (getf copy 'text-cell-right-margin) 28)
	      copy))
       
       (def-menu-item-format left-arrow-left-aligned-menu-item-format-new-large
	 . ,(let ((copy (copy-list inits)))
	      (setf (getf copy 'text-cell-left-margin) 28)
	      copy))
       (def-menu-item-format left-arrow-left-aligned-cascade-menu-item-format-new-large
	 . ,(let ((copy (copy-list inits)))
	      (setf (getf copy 'text-cell-left-margin) 28)
	      copy)))))

(def-concept left-aligned-menu-item-format-new-small)
(def-concept left-aligned-cascade-menu-item-format-new-small)
(def-concept left-aligned-menu-item-format-new-large)
(def-concept left-aligned-cascade-menu-item-format-new-large)

(def-concept left-arrow-left-aligned-menu-item-format-new-small)
(def-concept left-arrow-left-aligned-cascade-menu-item-format-new-small)
(def-concept left-arrow-left-aligned-menu-item-format-new-large)
(def-concept left-arrow-left-aligned-cascade-menu-item-format-new-large)

(def-new-g2-classic-ui-menu-item-small-formats)
(def-new-g2-classic-ui-menu-item-large-formats)




;;;; Class Choice Facilities 



;;; Compute-recyclable-class-choices, given a list of classes, accomplishes the
;;; following mappings:
;;;
;;;    (class1), where class1 has no inheritors and is a final choice -> (class1);
;;;    
;;;    (class1), where class1 has inheritors and is a final choice
;;;              -> concatenation of (class1) and the class-choices of the inheritors
;;;                 of class1;
;;;                 
;;;    (class1), where class1 is not a final choice
;;;              -> () if class1 has no inheritors, (class1) if class1 has more than 1
;;;                 final choice inheritors, and (final-choice-inheritor-of-class1) if
;;;                 class1 has 1 final choice class inheritor.
;;;                 
;;;    (class1), where class1 is never a choice
;;;              -> () if class1 has no final choice inheriors and
;;;                 (final-choice-inheritor1-of-class1 ... final-choice-inheritorN-of-class1)
;;;                 where class1 has N final choice class inheritors.
;;;                 
;;;    (class1 ... classN), where for each class i from 1 to N,
;;;                 there corresponds a set of classes j, j = i, where the set of classes j
;;;                 is that set which results from applying the function
;;;                 `compute-recyclable-highest-level-choices-given-class' (see below) to
;;;                 the set. Finally the classes 1 through N are mapped to the union of
;;;                 the sets j from 1 to N.
;;;
;;; Compute-recyclable-class-choices produces a list composed of recyclable conses which
;;; should be dealt with appropriately.

;;; Compute-recyclable-class-choices treats its classes argument as read-only.
;;; The list returned is made of slot-value-conses and is owned by the caller.
;;; The return value does not share with the argument.


;; Moved to commands0.



;;;; Class Choices




;;; `Def-class-choice-action' defines a specialized function (a `class choice action') to
;;; act on a final class choice made from a class choice menu.  Such a definition is of
;;; the form
;;;
;;;     (DEF-CLASS-CHOICE-ACTION class (class-var)
;;;       . body)
;;;
;;; Body uses class-var to refer to the particular final class choice.  The class choice
;;; action is named "ACT-ON-CHOICE-OF-A-class".

;;; A class choice action must handle class and all of its subclasses, except where the
;;; class is handled by a more specific class choice action.

(def-global-property-name class-choice-action)

(defmacro def-class-choice-action
    (class (class-var image-plane-var x-in-window-var y-in-window-var) &body body)
  (let ((name (intern (format nil "ACT-ON-CHOICE-OF-A-~A" class))))
    (multiple-value-bind (declarations body)
	(parse-body-declarations body)
      `(progn
	 (defun ,name (,class-var ,image-plane-var ,x-in-window-var ,y-in-window-var)
	   ,@declarations
	   (when (classp ,class-var)			    ; Fix 3.0 bug.
							    ; See also the new-object UI command.
	     ,@body))
	 (setf (class-choice-action ',class) ',name)))))

(defun class-choice-action-function (symbol)
  (class-choice-action symbol))

;;; `Set-cursor-position-for-menu-if-appropriate' does nothing at present.
;;; This is presumably called when a submenu is put up and presumably with the
;;; original x and y positions of the mouse.  In G2 prior to release 2.0, this
;;; was always done on implementations on which it could be supported; in later
;;; versions, this is never done, as it has been found to be at best marginally
;;; useful, and at worst annoying, fatiguing, and confusing.  At some future
;;; point, however, it may become a parameter, so it should continue to be
;;; called before when putting up submenus.

(defun set-cursor-position-for-menu-if-appropriate (x-in-window y-in-window)
  (declare (ignore x-in-window y-in-window))
;  (if nil					; some parameter?!
;      (set-cursor-position x-in-window y-in-window))
  )

;; Move this elsewhere!

;; Review this!









;;;; User Menu Choices




;;; A `user menu choice' is similar to a built-in menu choice contained in a
;;; menu and has the following differences.  A user menu choice is created by
;;; choosing "new definition" from the workspace menu and then choosing
;;; "user-menu-choice".  The menu choice's label is displayed in its menu and
;;; its action is executed only when its condition is true (or when there is no
;;; condition).  The user menu choice is represented by a frame, grammar
;;; category, and a directory of names.
;;;
;;; `user menu choice symbol' is the label of the user menu choice that is
;;; displayed in the menu.
;;;
;;; `class for user menu choice' specifies the class, and therefore the menu,
;;; associated with this menu choice.
;;;
;;; `user menu choices for this class' is a kb-specific-property-name of the class
;;; associated with the menu choice.  Each user-menu-choice is saved in this
;;; property.

;;; Since a user-menu-choice displays its label slot in an attribute display,
;;; it does not show its name in a name box; nor does it have a NAME menu choice
;;; on its menu.  It can however [as of 3.0, starting 7/3/91] be given a name,
;;; e.g., through its NAMES (alias for name-or-names-for-frame) attribute in
;;; its table.

(def-class (user-menu-choice (item entity) (foundation-class user-menu-choice)
			     (attribute-displays
			       ; label = alias for user-menu-choice-symbol?
			       ((label) at-standard-position))
			     define-predicate)
  (frame-author-or-authors
    nil (type authors-with-time-of-last-edit?)
    (attribute-export-comment
      "Will allow 0 or more author entries. each author entry may have a date. ~
authors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true
"))
  (frame-change-log nil (type frame-change-log))

  (icon-description
    (:funcall-at-load-time
      create-icon-description
      40 60 
      ((outline (0 0) (40 0) (40 60) (0 60))
       (solid-rectangle (0 0) (40 10))
       (lines (0 10) (40 10))
       (lines (0 20) (40 20))
       (lines (0 30) (40 30))
       (lines (0 40) (40 40))
       (lines (0 50) (40 50)))))

;  (name-or-names-for-frame nil (type nil) not-user-editable)   ; commented out -- allow user 
								;  access.  (MHD 7/3/91)
  (user-menu-choice-symbol?
    nil (type user-menu-choice) system vector-slot save)
  
  ;; Add a slot for a "label" so that users can specify using free
  ;;   text, rather than just symbol syntax!!
  
  (class-for-user-menu-choice? 
    nil (type user-instantiable-kb-class?) 
    system user-overridable vector-slot save)
  ;; Note that there is now a slot-value compiler for unique-logical-expression.
  ;;   It is in GRAMMAR1. Without this, the slot does not compile the expression,
  ;;   which is a serious bug. ML, 3/13/90.

  ;; A new grammar category symbol, user-menu-choice-expression, was created for
  ;; user-menu-choice conditions.  (This replaces the use of
  ;; unique-logical-expression.) This grammar category has a slot-value-compiler
  ;; that allows references to "the item" in the expression.  This is necessary
  ;; since "the item" refers to the selected item (i.e., the item associated
  ;; with the menu).  10apr90, cpm/agh.
  (condition-for-using-user-menu-choice?
    nil						; see note below (MHD 3/7/91)
    (type user-menu-choice-expression text)
    system user-overridable vector-slot save select-changes
    (attribute-export-comment "export a menu condition parse"))

  (action-for-user-menu-choice?			; the "action" slot
    nil (type embedded-rule text)
    vector-slot system select-changes
    (attribute-export-comment "export action parse"))
  (embedded-rule-in-user-menu-choice?
    nil vector-slot system save
    (attribute-export-comment "export the uuid???"))
  (user-menu-choice-priority
    2 (type priority) lookup-slot system user-overridable save
    (attribute-export-comment "export positive-integer"))
  
  ;; initialize method now deals with initial setup -- this slot's init form
  ;; will now be nil, and inherited. (MHD 7/18/94)
;  (frame-status-and-notes
;    (:funcall
;      make-list-of-button-status-and-types-of-notes
;      incomplete
;      user-menu-choice-or-action-button-missing-action
;      user-menu-choice-missing-applicable-class
;      user-menu-choice-missing-label))
  )

;; Clean up the embedded rule facility!!!  The parts common to user menu choices
;; and action buttons should be abstracted.  (The facility for embedded rules
;; in user menu choices was cloned from that of action buttons.)  There is also
;; special code to deal with embedded rules in clone-frame (in FILES), which had
;; to be modified to make embedded rules work in action buttons.  Also, some
;; text searching code for QUERIES in EVAL was made to deal in a special case
;; way with the text in various specific slots of buttons, including the
;; text of embedded rule; however, we have not extended it yet to deal with
;; user menu choices.  (It is not clear that maintaining the text search facility
;; in such a special-case way is the right way to go in the long run, anyway.)
;; In addition, make-short-representation (in TABLES) has to have special
;; code to deal with embedded rules.


;;; The user-menu-choice methods for `note-runs-while-inactive-change' and
;;; `note-may-refer-to-inactive-items-change' should call the next method, then
;;; it should propagate the settings into the embedded rule.

(def-class-method note-runs-while-inactive-change (user-menu-choice)
  (funcall-superior-method user-menu-choice)
  (let ((rule? (embedded-rule-in-user-menu-choice? user-menu-choice)))
    (when rule?
      (change-slot-value
	rule? 'frame-flags
	(if (runs-while-inactive-p user-menu-choice)
	    (logiorf (frame-flags rule?) runs-while-inactive-flag)
	    (logandc2f (frame-flags rule?) runs-while-inactive-flag))))))

(def-class-method note-may-refer-to-inactive-items-change (user-menu-choice)
  (funcall-superior-method user-menu-choice)
  (let ((rule? (embedded-rule-in-user-menu-choice? user-menu-choice)))
    (when rule?
      (change-slot-value
	rule? 'frame-flags
	(if (may-refer-to-inactive-items-p user-menu-choice)
	    (logiorf (frame-flags rule?) may-refer-to-inactive-items-flag)
	    (logandc2f (frame-flags rule?) may-refer-to-inactive-items-flag))))))




(defun initialize-user-menu-choice-action (user-menu-choice)
  (let ((embedded-rule?
	  (embedded-rule-in-user-menu-choice? user-menu-choice)))
    (when embedded-rule?		  
      (set-parent-information
	embedded-rule? user-menu-choice
	'action-for-user-menu-choice? nil)
      (unless reading-kb-p
	(add-as-inferior-block
	  embedded-rule?
	  user-menu-choice))     
      (when (priority-p (user-menu-choice-priority user-menu-choice))
	(change-slot-value
	  embedded-rule?
	  'rule-priority
	  (user-menu-choice-priority user-menu-choice)))
      (propagate-runnable-item-options-to-embedded-rule
	embedded-rule? user-menu-choice)
      (check-for-and-fix-up-cloned-embedded-rule embedded-rule?))
    (when (and (not (compilations-up-to-date-p user-menu-choice))
	       (action-for-user-menu-choice? user-menu-choice)
	       loading-kb-p)
      (add-or-delete-button-frame-note
	user-menu-choice
	'button-or-user-menu-choice-not-compiled-up-to-date
	nil)
      (note-frame-with-compilation-removed user-menu-choice))
    (add-or-delete-button-frame-note
      user-menu-choice
      'user-menu-choice-or-action-button-missing-action
      embedded-rule?)
    (add-or-delete-button-frame-note
      user-menu-choice
      'user-menu-choice-missing-applicable-class
      (class-for-user-menu-choice? user-menu-choice))
    (add-or-delete-button-frame-note
      user-menu-choice
      'user-menu-choice-missing-label
      (user-menu-choice-symbol? user-menu-choice))))

;; It seems "none" should be legal for applicable-class, and mean "any class",
;; i.e., item, although perhaps the name could be improved in that case.  (MHD
;; 8/3/94)

(defun-void propagate-runnable-item-options-to-embedded-rule
    (embedded-rule parent-item)
  (when (or (not (eq (runs-while-inactive-p parent-item)
		     (runs-while-inactive-p embedded-rule)))
	    (not (eq (may-refer-to-inactive-items-p parent-item)
		     (may-refer-to-inactive-items-p embedded-rule))))
    (let ((frame-flags (frame-flags embedded-rule)))
      (setq frame-flags
	    (if (runs-while-inactive-p parent-item)
		(logiorf frame-flags runs-while-inactive-flag)
		(logandc2f frame-flags runs-while-inactive-flag)))
      (setq frame-flags
	    (if (may-refer-to-inactive-items-p parent-item)
		(logiorf frame-flags may-refer-to-inactive-items-flag)
		(logandc2f frame-flags runs-while-inactive-flag)))
      (change-slot-value embedded-rule 'frame-flags frame-flags))))
  


;;; The `initialize method for user-menu-choice' ...
;;;
;;; The `initialize-after-reading method for user-menu-choice' ...

(def-class-method initialize (user-menu-choice)
  (funcall-superior-method user-menu-choice)
  (initialize-user-menu-choice-slots user-menu-choice))

(def-class-method initialize-after-reading (user-menu-choice)
  (funcall-superior-method user-menu-choice)
  (initialize-user-menu-choice-slots user-menu-choice))


(defun initialize-user-menu-choice-slots (user-menu-choice)
  (initialize-user-menu-choice-action user-menu-choice)
  (initialize-user-menu-choice-symbol user-menu-choice)
  (initialize-class-for-user-menu-choice user-menu-choice)
  (initialize-condition-for-using-user-menu-choice user-menu-choice))
  




(define-slot-alias label user-menu-choice-symbol? user-menu-choice)
(define-slot-alias applicable-class class-for-user-menu-choice? user-menu-choice)
(define-slot-alias condition condition-for-using-user-menu-choice? user-menu-choice)
(define-slot-alias action action-for-user-menu-choice? user-menu-choice)
(define-slot-alias action-priority user-menu-choice-priority user-menu-choice)





(def-slot-value-writer-as-existing-function user-menu-choice-expression
    write-expression-from-slot)

(def-slot-value-writer-as-existing-function user-menu-choice-expression-initialization
    write-expression-from-slot)




;;; The slot putter for condition-for-using-user-menu-choice?  accomplishes two
;;; purposes.  The first is to force recompilation of the condition if there is
;;; one and if it is out of date.  The second reason is to reclaim an old format
;;; for this slot which is equivalent to a NIL in this location.  This format is
;;; described in the following note.  -jra 8/25/91

;; The init form for condition-for-using-user-menu-choice? was
;;   (:funcall make-text-slot-value-for-none)
;; in 2.1 and 3.0 pre-alpha.  It was NIL in 2.0 and earlier.  Nil is now good
;; again because the writer now gets called to make it appear as "none".  See
;; writer below, as well as old function, in comments.  Consider having a KB
;; cleanup form or a slot putter (?) that turns (nil (lost-spaces .  0) "none")
;; into nil upon creation while reading in instances created in 2.1 from KBs.
;; (MHD 3/7/91)

(def-slot-putter condition-for-using-user-menu-choice?
		 (user-menu-choice value initializing?)
  (prog1 (setf (condition-for-using-user-menu-choice? user-menu-choice) value)
    (unless initializing?
      (initialize-condition-for-using-user-menu-choice user-menu-choice))))


(defun initialize-condition-for-using-user-menu-choice (user-menu-choice)
  (let ((condition-slot-value-and-text?
	  (condition-for-using-user-menu-choice? user-menu-choice)))
    (when (and condition-slot-value-and-text?
	       (not (compilations-up-to-date-p user-menu-choice))
	       loading-kb-p)
      (cond
	;; Eliminate an old (historical/obsolete) value of this which is
	;; equivalent to NIL.
	((equal condition-slot-value-and-text?
		'(nil (lost-spaces . 0) "none"))
	 (setf (condition-for-using-user-menu-choice? user-menu-choice)
	       nil)
	 (reclaim-slot-value condition-slot-value-and-text?))
	;; Else, force recompilation of the condition.
	(t
	 (reclaim-slot-value (car condition-slot-value-and-text?))
	 (setf (car condition-slot-value-and-text?) no-value)
	 (add-or-delete-button-frame-note ; new frame note in 4.0 (MHD 8/3/94)
	   user-menu-choice
	   'user-menu-choice-condition-not-compiled-up-to-date
	   nil)
	 (note-frame-with-compilation-removed user-menu-choice))))))



(def-class-method denote-cell-array-element
		  (user-menu-choice element-index include-block-denotation?)
  (declare (ignore user-menu-choice element-index include-block-denotation?))
  (twrite-string "the condition")
  (denote-component-of-block-1 '*current-computation-frame* " of "))

(def-class-method cleanup (user-menu-choice)
  (funcall-superior-method user-menu-choice)
  (when (class-for-user-menu-choice? user-menu-choice)
    (remove-as-user-menu-choice-for-class
      user-menu-choice
      (class-for-user-menu-choice? user-menu-choice)
      (user-menu-choice-symbol? user-menu-choice)))
  (retract-consistency-analysis user-menu-choice))



(def-slot-putter action-for-user-menu-choice?
		 (user-menu-choice action-text initializing?)
  (when (and initializing?
	     (not (compilations-up-to-date-p user-menu-choice))
	     loading-kb-p)
    (reclaim-slot-value (car action-text))
    (setf (car action-text) no-value))
  (setf (action-for-user-menu-choice? user-menu-choice)
	action-text))

(def-slot-putter embedded-rule-in-user-menu-choice?
		 (user-menu-choice embedded-rule? initializing?)
  (prog1
      (setf (embedded-rule-in-user-menu-choice? user-menu-choice) embedded-rule?)
    (unless initializing?
      (initialize-user-menu-choice-action user-menu-choice))))


(def-slot-putter user-menu-choice-priority
    (user-menu-choice value initializing?)
  (prog1 (setf (user-menu-choice-priority user-menu-choice) value)
    (unless initializing?
      (initialize-user-menu-choice-action user-menu-choice))))



(def-slot-putter user-menu-choice-symbol? (user-menu-choice value initializing?)
  (let ((old-label? (user-menu-choice-symbol? user-menu-choice)))
    (when (and old-label? (not initializing?))
      (delete-from-directory-of-names
	old-label? 'user-menu-choice))
    (when value
      (add-to-directory-of-names value 'user-menu-choice))
    (prog1 (setf (user-menu-choice-symbol? user-menu-choice) value)
      (unless initializing?
	(let ((class? (class-for-user-menu-choice? user-menu-choice)))
	  (when class?
	    (remove-as-user-menu-choice-for-class
	      user-menu-choice class? old-label?)))
	(initialize-user-menu-choice-symbol user-menu-choice)))))


(defun initialize-user-menu-choice-symbol (user-menu-choice)
  (let ((choice-symbol? (user-menu-choice-symbol? user-menu-choice)))
    (add-or-delete-button-frame-note
      user-menu-choice 'user-menu-choice-missing-label choice-symbol?)
    (decache-dynamic-menus 'user-menu-choices)
    (let ((class? (class-for-user-menu-choice? user-menu-choice)))
      (when class?
	(add-as-user-menu-choice-for-class user-menu-choice class?)))))


(def-frame-note-writer user-menu-choice-label-conflict
    (particulars user-menu-choice)
  user-menu-choice				; not used yet
  ;; particulars is a built-in menu choice symbol, in the case where
  ;;   there is a conflict with a built-in menu choice, or, in the case of
  ;;   a conflict with other user menu choices for the same class with the
  ;;   same label, it is the number of conflicts.
  (cond
    ((symbolp particulars)
     (let ((write-symbols-in-lower-case? nil))	; choice symbol in all caps
       (tformat "~a conflicts with a built-in menu choice" particulars)))
    (t
     (let ((count-of-other-labels (-f particulars 1)))
       (declare (type fixnum count-of-other-labels))
       ;; handle conflicts with other user menu choice labels
       (tformat "the label conflicts with ~d other user menu choice~a"
		count-of-other-labels (if (>f count-of-other-labels 1) "s" ""))
       ))))


(def-kb-specific-property-name user-menu-choices-for-this-class 
    reclaim-kb-property-list-function)



;;; The slot putter for class-for-user-menu-choice? maintains the user-menu-
;;; choices-for-this-class kb-specific property for class names during the
;;; lifetime of each user menu choice. (See also the reclaimer, below).  The
;;; user-menu-choices-for-this-class property is a list (possibly empty)
;;; of user-menu-choices (frames).  The list may not contain duplicates; that
;;; is, one and only one instance of a user menu choice may be in the list.
;;; Note that this slot putter allows there to be more than one instance
;;; with the same label; a constraint disallowing more than one instance with
;;; the same label would have to be maintained elsewhere, if it were to be
;;; maintained at all.  In fact, instances are added to the list even if they
;;; do not have labels.  Their labels may come and go throughout their lifetime
;;; on the list.

;;; The reclaimer for class-for-user-menu-choice? removes the instance from
;;; its user-menu-choices-for-this-class list, if there is one.

(def-slot-putter class-for-user-menu-choice? (user-menu-choice value initializing?)
  (let* ((old-class? (class-for-user-menu-choice? user-menu-choice)))
    (prog1 (setf (class-for-user-menu-choice? user-menu-choice) value)
      (unless initializing?
	(remove-as-user-menu-choice-for-class
	  user-menu-choice old-class?
	  (user-menu-choice-symbol? user-menu-choice))
	(initialize-class-for-user-menu-choice user-menu-choice)))))


(defun initialize-class-for-user-menu-choice (user-menu-choice)
  (let* ((class? (class-for-user-menu-choice? user-menu-choice)))
    (add-or-delete-button-frame-note
      user-menu-choice 'user-menu-choice-missing-applicable-class class?)
    (if class?
	(add-as-user-menu-choice-for-class user-menu-choice class?)
	(delete-frame-note-if-any
	  'user-menu-choice-label-conflict user-menu-choice))))


(defun add-as-user-menu-choice-for-class (user-menu-choice class)
  (kb-property-pushnew
    user-menu-choice (user-menu-choices-for-this-class class))
  (let ((label? (user-menu-choice-symbol? user-menu-choice)))
    (when label?
      (update-menu-choice-label-conflict-frame-notes
	user-menu-choice class label?))))

(defun remove-as-user-menu-choice-for-class (user-menu-choice class label?)
  (setf (user-menu-choices-for-this-class class)
	(delete-kb-property-element
	  user-menu-choice
	  (user-menu-choices-for-this-class class)))
  (when label?
    (update-menu-choice-label-conflict-frame-notes
      user-menu-choice class label?)))


(defun update-menu-choice-label-conflict-frame-notes
    (user-menu-choice class label)
  (let ((particular?
	  (if (built-in-menu-choice-p label)
	      label
	      (loop for umc in (user-menu-choices-for-this-class class)
		    count (or (eq umc user-menu-choice)
			      (eq label (user-menu-choice-symbol? umc)))
		      into count
		    finally
		      (when (>f count 1)
			(return count))))))
    (loop for umc in (user-menu-choices-for-this-class class)
	  when (or (eq umc user-menu-choice)
		   (eq label (user-menu-choice-symbol? umc)))
	    do 
	      ;; Retract, then assert (revise to use consistency analysis with
	      ;; JED's assistance!) -- one of these, that for multiple uses of
	      ;; the same symbol, can affect other frames' notes.  This is now
	      ;; grossly inefficient for large numbers of instances for the same
	      ;; class!  (MHD 8/3/94)
	      (delete-frame-note-if-any 'user-menu-choice-label-conflict umc)
	      (when particular?
		(add-frame-note
		  'user-menu-choice-label-conflict umc particular?)))))
	  
    



(def-slot-value-reclaimer user-menu-choice-symbol? (user-menu-choice-symbol?)
  (if user-menu-choice-symbol?
      (delete-from-directory-of-names
	user-menu-choice-symbol? 'user-menu-choice)))

;; Move to cleanup method?!



(def-slot-value-reclaimer embedded-rule-in-user-menu-choice?
    (embedded-rule-in-user-menu-choice?)
  (if embedded-rule-in-user-menu-choice?
      (delete-frame embedded-rule-in-user-menu-choice?)))



(add-grammar-rules
  '((embedded-rule-in-user-menu-choice embedded-rule)
    (user-menu-choice unreserved-symbol)
;    (object-name? 'none nil)  ; moved to def-grammar-category for OBJECT-NAME?
			       ; Not clear what it was doing here! (MHD 7/7/04)
    ))

(define-category-evaluator-interface (user-menu-choice
				       :access read-write)
    symbol
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (call-category-setter-safely 'unreserved-symbol evaluation-value)))
  ((get-form (slot-value))
   (call-category-getter 'unreserved-symbol slot-value nil nil)))

(def-grammar-category user-instantiable-kb-class? ()
  (class)
  ('none nil))

;; Was user-instantiable-kb-class (MHD 6/19/90)


(def-slot-value-writer-as-existing-function user-menu-choice
    write-symbol-from-slot)





;;; The `manually-enable' and `manually-disable' methods for user-menu-choices
;;; propagate the setting of the enabled frame flag down into the embedded rule.
;;; It used to be that all enable/disable did was toggle whether or not
;;; something was activated.  However, for running-while-inactive rules, it now
;;; also stops their execution, regardless of activation state.  These methods
;;; propagate that value down into the embedded rule.

(def-class-method manually-enable (user-menu-choice)
  (funcall-superior-method user-menu-choice)
  (let ((embedded-rule-in-user-menu-choice?
	  (embedded-rule-in-user-menu-choice? user-menu-choice)))
    (if embedded-rule-in-user-menu-choice?
	(funcall-method
	  'manually-enable embedded-rule-in-user-menu-choice?))))

(def-class-method manually-disable (user-menu-choice)
  (funcall-superior-method user-menu-choice)
  (let ((embedded-rule-in-user-menu-choice?
	  (embedded-rule-in-user-menu-choice? user-menu-choice)))
    (if embedded-rule-in-user-menu-choice?
	(funcall-method 'manually-disable embedded-rule-in-user-menu-choice?))))


(def-class-method activate-subclass-of-entity (user-menu-choice)
  (let ((embedded-rule-in-user-menu-choice?
	  (embedded-rule-in-user-menu-choice? user-menu-choice)))
    (if embedded-rule-in-user-menu-choice?
	(funcall-method
	  'activate-if-possible-and-propagate
	  embedded-rule-in-user-menu-choice?))))

(def-class-method deactivate-subclass-of-entity (user-menu-choice)
  (let ((embedded-rule-in-user-menu-choice?
	  (embedded-rule-in-user-menu-choice? user-menu-choice)))
    (if embedded-rule-in-user-menu-choice?
	(funcall-method
	  'deactivate-and-propagate
	  embedded-rule-in-user-menu-choice? nil))))

;; The table cell labeled ACTION in action buttons and user menu choices
;; should highlight if the run option "highlight invoked rules" is on!!




(define-category-evaluator-interface (user-instantiable-kb-class?
				       :access read-write)
    (or (no-item) symbol)
  ((set-form (evaluation-value))
   (if (or (null evaluation-value) (reserved-word-p evaluation-value))
       'none
       evaluation-value))
  ((get-form (slot-value))
   (if (eq slot-value 'none)
       nil
       slot-value)))




(def-slot-value-writer-as-existing-function user-instantiable-kb-class?
    write-symbol-from-slot)



;;; The function `user-menu-choice-runnable-p' returns T if the given
;;; user-menu-choice applies and can run on frame.

(defun user-menu-choice-runnable-p (user-menu-choice frame)
  (and (runnable-p-function user-menu-choice)
       (or system-is-running
	   (and (runs-while-inactive-p user-menu-choice)
		(not inside-breakpoint-p)))
       (or (may-refer-to-inactive-items-p user-menu-choice)
	   (active-p frame))
       (evaluate-user-menu-choice-condition
	 user-menu-choice frame)))


;;; The function `get-user-menu-choice-or-choice-symbols' takes a frame that has
;;; been clicked on and optionally a menu-choice symbol.

;;; If choice-symbol? is non-nil, this returns the user menu choice
;;; corresponding to choice-symbol? for frame if it can validly be executed.
;;; Otherwise, this returns a slot value list of the valid user menu choice
;;; symbols for frame.

;;; A user menu choice may NOT be validly executed under any of the following
;;; conditions:
;;;
;;;   (1) frame is not an item;
;;;   (2) the system is not running (i.e. paused, reset, or never started);
;;;   (3) no user menu choice corresponds to the choice symbol (rare);
;;;   (4) the user menu choice is not runnable-p; or
;;;   (4) the frame is not active and the user menu choice doesn't reference
;;;       inactive items;
;;;   (5) the condition of the user menu choice fails to return or
;;;       returns false; or
;;;   (6) the choice conflicts with a built-in menu choice

;;; Note that the active-p status of frame does not affect the validity of a
;;; choice symbol, even though the action or condition within valid user menu
;;; choices might well fail if frame is not active (e.g. if it refers to frame
;;; via "the item").

(defun get-user-menu-choice-or-choice-symbols
    (frame &optional choice-symbol?)
  (when (frame-of-class-p frame 'item)
    (loop with class = (class frame)
	  with resulting-user-menu-choices-so-far = nil
	  with resulting-user-menu-choice? = nil
	  for superior-class in (class-inheritance-path (class-description class))
	  do
      (loop for user-menu-choice
		in (user-menu-choices-for-this-class superior-class)
	    as user-menu-choice-symbol?
	       = (user-menu-choice-symbol? user-menu-choice)
	    when (and user-menu-choice-symbol?
		      (if choice-symbol?
			  (eq user-menu-choice-symbol?
			      choice-symbol?)
			  (and (loop for user-menu-choice
					 in resulting-user-menu-choices-so-far
				     never (eq user-menu-choice-symbol?
					       (user-menu-choice-symbol?
						 user-menu-choice)))
			       (or (memq 'text-cell-of-table
					 (lambda-list-of-ui-command-named user-menu-choice-symbol?))
				   (not (built-in-menu-choice-p user-menu-choice-symbol?))))))
	      do (if choice-symbol?
		     (setq resulting-user-menu-choice?
			   user-menu-choice)
		     (setq resulting-user-menu-choices-so-far 
			   (slot-value-cons
			     user-menu-choice
			     resulting-user-menu-choices-so-far))))
	  when resulting-user-menu-choice?	; for choice-symbol? case
	    return
	    (if (user-menu-choice-runnable-p resulting-user-menu-choice? frame)
		resulting-user-menu-choice?)
	  finally
	    (if (and (null choice-symbol?)	; for (null choice-symbol?) case
		     resulting-user-menu-choices-so-far)	; optimization
		(return
		  (loop for user-menu-choice
			    in resulting-user-menu-choices-so-far
			when (and (runnable-p-function user-menu-choice)
				  (or system-is-running
				      (and (runs-while-inactive-p user-menu-choice)
					   (not inside-breakpoint-p)))
				  (or (may-refer-to-inactive-items-p
					user-menu-choice)
				      (active-p frame))
				  (evaluate-user-menu-choice-condition
				    user-menu-choice frame))
			  collect 
			  (user-menu-choice-symbol? user-menu-choice)
			    into resulting-user-menu-choice-symbols-so-far
			    using slot-value-cons
			finally
			  (reclaim-slot-value-list
			    resulting-user-menu-choices-so-far)
			  (return
			    resulting-user-menu-choice-symbols-so-far)))))))


;;; `Compute-user-menu-choices' returns a slot value list of the user menu
;;; choices (as symbols) applicable to frame.

(defun compute-user-menu-choices (frame)
  (get-user-menu-choice-or-choice-symbols frame nil))

;; We have to solve the problem that user-defined choices will, at present,
;; be interpreted the same way as G2 choices.  In some cases, you want the
;; user's choice to look just a like a built-in choice.  For example, in KB
;; restrictions you should not have to deal with built-in vs. non-built-in
;; choices in different ways. !!!





;;; `Window-instigating-this-rule-instance?' is used to communicate the
;;; window from which a button or menu choice was instigated to the rule
;;; that executes the associated action. It must be bound to the window
;;; at the time generate-and-schedule-rule-instances is called, or else
;;; it is bound to NIL meaning the default window.

;;; When the rule instances are executing, the window or NIL is foundin
;;; (ri-window-for-rule? rule-instance).

(def-system-variable window-instigating-this-rule-instance? new-rules nil)






;;; The macro `invoke-old-or-new-rule' invokes old or new rules as appropriate.
;;; It schedules, rather than immediately executing, the rule.  It does not
;;; filter out embedded rules, as does schedule-rule-instances-if-rule-is-
;;; not-embedded.

(defmacro invoke-old-or-new-rule
	  (rule focal-role? local-name? focal-object? purpose)
  `(generate-and-schedule-rule-instances
     ,rule ,focal-role? ,local-name? ,focal-object? ,purpose nil nil nil))

;; [Some explanation presumably belongs here as to why this is defined here.
;; ML?]   (MHD 9/27/90)




;;; The function `execute-user-menu-choice-if-possible' if it can find a user
;;; menu choice corresponding to frame that is valid to execute, executes it.
;;; The function execute-user-menu-choice provides a lower-level interface for
;;; both classic and Nevada UI's.  It returns either nil or a number of
;;; rule instances created.

(defun execute-user-menu-choice-if-possible (choice-symbol frame)
  (let ((user-menu-choice?
	   (get-user-menu-choice-or-choice-symbols frame choice-symbol)))
    (when (and user-menu-choice?
	       (embedded-rule-in-user-menu-choice? user-menu-choice?))
      (execute-user-menu-choice
	user-menu-choice? frame current-workstation-window))))

(defun-simple execute-user-menu-choice (user-menu-choice frame window-or-ui-client)
  (let ((embedded-rule?
	  (embedded-rule-in-user-menu-choice? user-menu-choice)))
    (cond
      (embedded-rule?
       (let ((window-instigating-this-rule-instance? window-or-ui-client))
	 (invoke-old-or-new-rule		; bind *current-computation-frame* ??
	   embedded-rule? 'item nil frame 'user-menu-choice)))
      (t
       nil))))





;;;; Tools for getting Tables of All Commands to Translate

;; Needs work. (MHD 10/21/94)
;#+development
;(progn
;
;(defun get-all-menu-descriptions ()
;  (let ((result nil))
;    (do-symbols (symbol (find-package 'ab))
;      (let ((menu-description? (find-menu-description symbol)))
;        (when menu-description?
;          (pushnew menu-description? result))))
;    result))
;
;(defun get-all-commands-in-menu (menu-description)
;  (let ((list-or-function
;          (menu-description-choice-list-internal menu-description)))
;    (if (atom list-or-function)
;        list-or-function
;        (loop for symbol-or-list in list-or-function
;              when (atom symbol-or-list)
;                collect (or (ui-command-named symbol-or-list)
;                            symbol-or-list)))))
;
;
;(defun get-all-menu-and-commands ()
;  (let ((all-menu-descriptions (get-all-menu-descriptions)))
;    (loop for menu-description in all-menu-descriptions
;          collect
;             (list menu-description
;                   (get-all-commands-in-menu menu-description)))))
;
;
;
;
;(defun print-all-menus-and-command ()
;  (let ((menus-and-commands-a-list (get-all-menu-and-commands)))
;    (loop for (menu-description commands) in menus-and-commands-a-list
;          do (print-menu-and-commands menu-description commands))))
;
;
;(defun print-menu-and-commands (menu-description commands &optional language-needed-for?)
;  (format t "~%Menu: ~a" (menu-description-title menu-description))
;  (print-commands commands language-needed-for?))
;
;(defun print-commands (commands &optional language-needed-for?)
;  (if (atom commands)
;      (format t "~%  ~a" commands)
;      (loop for command in commands
;            unless (or (null language-needed-for?)
;                       (null (translate-menu-choice command language-needed-for?)))
;            do (format t "~%  ~(~a~)"
;                       (if (symbolp command)
;                           command
;                           (ui-command-menu-name command))))))
;
;
;
;
;
;(defun clone-language-translation-as-free-text (language-translation)
;  (make-free-text-box
;    (convert-text-to-text-string
;      (cdr (box-translation-and-text language-translation)))
;    'free-text))
;
;)



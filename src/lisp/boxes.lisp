;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module BOXES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson and Mark H. David




;;;; Forward References

(declare-forward-references
  (draw-or-change-color-in-text-cell-for-block function tables)
  (table-background-color                      function tables)
  (table-visible-in-image-plane-p              function tables)
  (push-last-spot                              function workstation)
  (editor-parameters                           variable edit1)
  (ellipsis-text-string                        variable edit1)
  (make-text-region                            function tables)
  (delete-any-text-regions                     function tables)
  (update-text-in-edit-box                     function edit2)
  (find-position-in-text-given-image-plane     function edit2)
  (find-position-in-text                       function edit2)
  (blackboard-argument-of-mouse-pointer        function new-menus)
  (bad-4-0-beta-magnifications-in-text-boxes-removed-p-function
    function kb-load1)
  (loading-kb-p                                variable kb-load2)
  (note-kb-state-change                        function kb-save2)
  (update-runtime-structures-according-to-edit function install)
  (make-text-cell                              function)
  (make-or-reformat-table                      function)
  (make-new-top-level-kb-workspace             function)
  (redraw-transfer-representations-of-block    function)
  (color-or-metacolor-p                        function)
  (note-kb-state-change-to-slot-by-saving-text function kb-save2)
  (send-ws-representations-item-moved          function events-g2)
  )

(declare-forward-reference get-ruling-for-meter function)


;;;; Text




;;; A `text' is a list containing one or more of the following kinds of element and always
;;; having a text line as the last element.
;;;
;;;     `text-line'                   ; a wide string of Unicode characters, with
;;;                                   ;   contents as described below
;;;     
;;;
;;;     new-indentation               ; integer in workspace units; 0 or this holds until
;;;                                   ;   superceded
;;;
;;;     (leading . amount)            ; one-shot integer adjustment to vertical position
;;;     (word-spacing . text-width)   ; for adjustable spaces in next line only, as a text width
;;;
;;;     (lost-spaces . n)             ; number of ordinary spaces, or string of spaces,
;;;     (lost-spaces . text-line)     ;   lost at the NEXT (an automatic) line break
;;;
;;;     (hyphen-added)                ; hyphen was added at the NEXT (an automatic) line break
;;;
;;;     (line-width . workspace-width); includes indentation but not lost spaces, and takes
;;;                                   ;   magnification into account; "optional" (see below)
;;;     (context-carryover . symbols) ; see below
;;;     (intercepted)                 ; used in OLE text drag-drop

;;; (The term "TEXT" is overloaded in G2.  TEXT is the name of data type in the
;;; user programming language.  TEXT is the name of a grammar catagory.  TEXT is
;;; a system-defined attribute of some blocks (procedures, rules, messages for
;;; example).  The designation "the TEXT of <attr> of <designation>" is used to
;;; coerce an attribute into it's printed form as it appears in a table, and to
;;; set an attribute using the slot value compiler.  In addition, programmers
;;; working on the inference engine/procedure modules have traditionally confused
;;; "text" with "text string".  Sigh.)

;;; A `text line' (or `line in text') is a text string that represents a line of
;;; text.  A text line consists of Unicode characters.  Note that ellipses and
;;; added hyphens that appear in a text line are somewhat transient; see module
;;; EDIT.


;;; All conses in a text should be slot value conses.
;;;
;;; All strings in a text should be text strings, and all conses in a text
;;; should be slot value conses.
;;;
;;; Furthermore, such text strings and conses must be unshared and recyclable.
;;; This even includes conses used for such elements as (hyphen-added).

;;; A `text position' (e.g. a cursor position) consists of a `line index' and a
;;; `character index', where the first line in a text has line index 1 and where
;;; the position in a text line preceding the first character has
;;; character-index 0.  Note that a line break or text position may not occur
;;; within a complex character.

;;; After a text has been `formatted', there are no newlines embedded within a
;;; text line nor spaces at the ends of lines (past the cursor).  If a cursor is
;;; present there may transiently be spaces at the end of the line.

;;; In a gensym text there are no ascii newline characters nor other non-gensym
;;; characters.  At this point a function convert-ascii-to-gensym (?) is used to
;;; preprocess all raw text before it is placed in a gensym text.  A newline
;;; character in raw text typically turns into a line separator character at the
;;; beginning of a line in the corresponding formatted text.  The paragraph
;;; separator character is partially supported but not exposed to the user in
;;; the editor or normal translator.  The intention for the paragraph separator
;;; is to provide a second line break, and allow for the choice within a
;;; paragraph of embedding of displays in running text, or providing a line
;;; break which does not force reestablishment of paragraph formats.

;;; Any automatic line break made during formatting or reformatting is always
;;; completely and precisely undoable based on elements, if any, between the
;;; text lines.

;;; #.%paragraph-separator need not appear at the beginning of the
;;; first line of a text, since it is always implicitly taken to be there.
;;; Indeed, ordinary spaces at the beginning of the first line of a text cause
;;; extra indentation on turnover lines, as they would if an
;;; #.%paragraph-separator were present.

;;; Indentation, leading, adjustable spaces, and (of course) character widths
;;; should not reflect magnification, but are SUBJECT to magnification during
;;; drawing.

;;; Where no explicit word-spacing element is present, the default word spacing
;;; is implied.  Where no explicit lost-spaces or hyphen-added element is
;;; present, (lost-spaces . 1) is implied.  Note that (lost-spaces . 0) is used
;;; when a line is automatically broken where there is no space.  There may not
;;; be both hyphen-added and lost-spaces elements for a particular text line.

;;; Explicit line widths may always be present, but are required only in edit
;;; boxes and in center- or right-justified formatted texts.  If justification
;;; options are fully supported, it might be best to implement these the other
;;; way, i.e. as a context which can be carried over.  This would help with
;;; space efficiency ala ben's comment below. -pga, 3/8/95

;;; A `context carryover' is a list of symbols that represent the nesting of
;;; local font and style contexts that obtains at the beginning of the next
;;; line.  For example, (G I) would specify an italic context within an
;;; alternate font context.  At this point, both the context carryover mechanism
;;; is unreliable and the character attributes in the context are not
;;; implemented. -pga, 3/8/95

(def-concept text)

;; Consider using a single integer to represent a text position.  - (MHD ?/?/?)
;; Humm... see encode-current-source-position in the EDIT.  - ben 2/25/93

;; Consider also allowing adjustments to line spacing to be specified along with
;; indentations and text lines.

;; This data structure accounts for a LOT of the static space requirements of an
;; KB that has not been "text stripped" Some ideas: (1) create a dense form of
;; this that can be converted into this form when the slot is being worked on.
;; (2) the elements in a TEXT are of type (or integer text-string
;; slot-value-cons), and much of the space is taken by the the slot-value-cons
;; elements, if we add symbol to this list we might encode common cases that
;; currently are implemented as slot-value-cons.  (3) Add some more stuff like
;; @L to replace the slot-value-cons elements.  It is tragic that people text
;; strip just to reduce KB load time!  - ben 2/25/93



;;; The macro `lost-spaces-value-if-any' can be called on any text element, and
;;; returns the the lost spaces "value" if thing is a lost spaces element.  The
;;; value is an integer for the number of lost spaces or a text line of
;;; special-character lost spaces.  If thing is not a lost-spaces element, this
;;; returns nil.

(def-substitution-macro lost-spaces-value-if-any (thing)
  (if (and (consp thing)
	   (eq (car-of-cons thing) 'lost-spaces))
      (cdr-of-cons thing)))


;;; `Zero-lost-spaces-p' is true if thing is a text element indicating that
;;; there are no lost spaces for the following text line.

(def-substitution-macro zero-lost-spaces-p (thing)
  (eql (lost-spaces-value-if-any thing) 0))


;;; `Lost-spaces-p' is true if thing is a text element indicating that there are
;;; one or more lost spaces for the following text line.

(def-substitution-macro lost-spaces-p (thing)
  (case (lost-spaces-value-if-any thing)
    ((nil 0) nil)
    (t t)))




(defun-simple make-lost-spaces-text-element (integer-or-text-string)
  (slot-value-cons 'lost-spaces integer-or-text-string))

(defun-simple make-lost-spaces-phrase-text-element (integer-or-text-string)
  (phrase-cons 'lost-spaces integer-or-text-string))


;; `Text-line-p' is true if text-element, an element of a text, is a string
;; (necessarily a text string representing a line of text).

;(defmacro text-line-p (text-element)
;  `(text-string-p ,text-element))

;; text-line-p now defined in fonts. (MHD 2/96)


(defun text-line-p-function (text-element)
  (text-line-p text-element))



#+development
(defun valid-text-element-symbol-p (element)
  (declare (ignore element))
  nil)  ; none defined currently

#+development
(defun valid-text-element-cons-p (element)
  (let ((car (car element))
	(cdr (cdr element)))
    (case car
      (lost-spaces
       (or (fixnump cdr)
	   (text-line-p cdr)))
      (leading (fixnump cdr))
      (word-spacing (fixnump cdr))
      (hyphen-added (null cdr))
      (line-width (null cdr))
      (context-carryover (every #'symbolp cdr))
      (otherwise nil))))

#+development
(defun valid-formatted-text-p (text)
  (flet ((valid-formatted-text-element (element)
	   (or (text-line-p element)
	       (fixnump element)
	       (cond
		 ((symbolp element)
		  (valid-text-element-symbol-p element))
		 ((consp element)
		  (valid-text-element-cons-p element))))))
    (and (consp text)
	 (every #'valid-formatted-text-element text))))

;; This comes with out warrenty, but it worked for me on 2/24/95 - ben
;; I didn't want to call it valid-text-p, but the term formatted-text
;; is without pedigree.



;;; Get-one-lost-space-at-end-of-line is a macro to be called with the "lost
;;; space at end of line" value returned from get-next-text-line, the current
;;; character index, and the current line length.  It returns the appropriate
;;; space character at the given index.

(def-substitution-macro get-one-lost-space-at-end-of-line
    (lost-space-at-end-of-line character-index line-length)
  (if (fixnump lost-space-at-end-of-line)
      #.%space
      (charw lost-space-at-end-of-line
	     (-f character-index line-length))))


;;; Get-length-of-space-at-end-of-line is a macro to be called with the "lost
;;; space at end of line" value returned from get-next-text-line.  It returns
;;; the number of space characters.

(def-substitution-macro get-length-of-space-at-end-of-line
    (lost-space-at-end-of-line)
  (if (fixnump lost-space-at-end-of-line)
      lost-space-at-end-of-line
      (text-line-length lost-space-at-end-of-line)))

;; Two new macros -- should see wider use in old code! (MHD 6/14/96)





;;;; Text Loop Iteration Path


;;; A `text character' is a wide character in a text data structure.  There is a
;;; `text-character path' (a loop iteration path) for iterating over all or a
;;; subset of the text characters of a text.

(def-concept text-character)

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro text-characters-path
    (path-name variable data-type
	       prep-phrases inclusive? allowed-prepositions data)
    ;; These variables are not used.
    (declare (ignore data))
    ;; Warn of missing or inappropriate prepositional phrase.
    (when (loop for prep-phrase in prep-phrases
		never (eq (car prep-phrase) 'of))
      (error "OF is missing in ~S iteration path of ~S" path-name variable))
    (loop for prep-phrase in prep-phrases
	  when (not (memq (car prep-phrase) allowed-prepositions))
	    do (error
		 "~A unrecognized preposition in ~S iteration path of ~S"
		 (car prep-phrase) path-name variable))
    ;; Inclusive iteration is not supported.
    (when inclusive?
      (error
	"Inclusive stepping is not supported in ~S path of ~S (prep-prase = ~:S)"
	path-name variable prep-phrases))
    (let* ((character-index (loop-gentemp 'character-index))
	   (line-index (loop-gentemp 'line-index))
	   (end-character-index? (loop-gentemp 'end-character-index?))
	   (end-line-index? (loop-gentemp 'end-line-index?))
	   (suppress-lost-spaces-at-end? (loop-gentemp 'suppress-lost-spaces-at-end?))
	   (text-line (loop-gentemp 'text-line))
	   (line-length (loop-gentemp 'line-length))
	   (lost-space-at-end-of-line (loop-gentemp 'lost-space-at-end-of-line))
	   (next-text-tail? (loop-gentemp 'next-text-tail?))
	   (current-indentation (loop-gentemp 'current-indentation))
	   (explicit-paragraph-or-newline? (loop-gentemp 'explicit-paragraph-or-newline?))
	   (text (loop-gentemp 'text-))
	   (this-text-tail? (loop-gentemp 'this-text-tail?))
	   (get-char-form
	     `(loop with indentation-if-new?
		    with character
		    do (cond
			 ((>=f ,character-index ,line-length)
			  (cond
			    ((<f (-f ,character-index ,line-length)
				 (get-length-of-space-at-end-of-line
				   ,lost-space-at-end-of-line))
			     (setq character
				   (get-one-lost-space-at-end-of-line
				     ,lost-space-at-end-of-line
				     ,character-index ,line-length))
			     (incff ,character-index)
			     (loop-finish)))
			  #-development
			  (when (null ,next-text-tail?) ; never reached.  see pre-step-end-test.
			    (setq ,explicit-paragraph-or-newline? nil)
			    (setq character nil)
			    (return character))
			  (setq ,this-text-tail? ,next-text-tail?)
			  (incff ,line-index)
			  (setq ,character-index 0)
			  (multiple-value-setq
			      (,text-line ,line-length ,lost-space-at-end-of-line
					  ,next-text-tail? indentation-if-new?)
			    (get-next-text-line ,next-text-tail?))
			  (when indentation-if-new?
			    (setq ,current-indentation indentation-if-new?)))
			 (t (setq character
				  (read-character-from-wide-string
				    ,text-line ,character-index))
			    (loop-finish)))
		    finally
		      (wide-character-case
			character
			(#.%paragraph-separator
			   (setq ,explicit-paragraph-or-newline? 'paragraph))
			(#.%line-separator
			   (setq ,explicit-paragraph-or-newline? 'newline))
			(#.%return
			   (setq ,explicit-paragraph-or-newline? 'return))
			(#.%linefeed
			   (setq ,explicit-paragraph-or-newline? 'linefeed)))
		     (return character)))
	   (bindings 
	     `((,variable
		  #u0000		; dummy initial value
		  ,(or data-type 'wide-character))
	       (,line-index
		  (or ,(second (assq 'line prep-phrases)) 1) fixnum)
	       (,character-index
		  (or ,(second (assq 'character prep-phrases)) 0) fixnum)
	       (,end-line-index?
		  (or ,(second (assq 'end-line prep-phrases)) nil))
	       (,end-character-index?
		  (or ,(second (assq 'end-character prep-phrases)) nil))
	       (,suppress-lost-spaces-at-end?
		  (or ,(second (assq 'suppress-lost-spaces-at-end prep-phrases)) nil))
	       (,text-line nil)
	       (,line-length 0 fixnum)
	       (,lost-space-at-end-of-line nil)
	       (,next-text-tail? nil)
	       (,current-indentation	; not yet used; should come from format!
		  0 fixnum)
	       (,explicit-paragraph-or-newline? nil)
	       (,text ,(second (assq 'of prep-phrases)))
	       (,this-text-tail? ,(second (assq 'text-tail prep-phrases)))))
	   (prologue
	     `((or ,this-text-tail?
		   (setq ,this-text-tail?
			 (find-text-tail-for-line ,text ,line-index)))
	       (multiple-value-setq-some
		   (,text-line ,line-length ,lost-space-at-end-of-line
			       ,next-text-tail?)
		   (get-next-text-line ,this-text-tail?))))
	   (pre-step-end-test
	     `(and
		;; last line?
		(or (and ,end-line-index?
			 (=f ,line-index ,end-line-index?))
		    (null ,next-text-tail?))
		;; beyond end of line (checking for lost spaces)?
		(or (>=f ,character-index
			(if ,suppress-lost-spaces-at-end?
			    ,line-length
			    (+f ,line-length (get-length-of-space-at-end-of-line
					       ,lost-space-at-end-of-line))))
		    ;; Also quit if beyond character index
		    (and ,end-character-index?
			 (>=f ,character-index ,end-character-index?)))))
	   (steps
	     `(,variable ,get-char-form))
	   (post-step-end-test
	     '())
	   (pseudo-steps
	     '()))
      ;; Return the appropriate items.
      `(,bindings
	  ,prologue ,pre-step-end-test ,steps ,post-step-end-test ,pseudo-steps)))
)


(define-loop-path (text-characters text-character)
		  text-characters-path (of line character text-tail
					   end-line end-character
					   suppress-lost-spaces-at-end))

;; When evaluated, the following should print absolutely nothing:
;;
;; (loop for x being each text-character of '((lost-spaces . 0) #w"") do (print x))

;; When evaluated, the following should print just the wide character c:
;;
;; (loop for x being each text-character of '((lost-spaces . 0) #w"abc")
;;       line 1 character 2
;;       do (print x))
;;
;;
;; When evaluated, the following should print just the wide character b:
;;
;; (loop for x being each text-character of '((lost-spaces . 0) #w"abc")
;;       line 1 character 1 end-line 1 end-character 2
;;       do (print x))
;;
;; When evaluated, the following should print just the wide characters 
;; b and c and space:
;;
;; (loop for x being each text-character of '(#w"abc")
;;       line 1 character 1
;;       do (print x))
;;
;; When evaluated, the following should print just the wide characters 
;; b and c:
;;
;; (loop for x being each text-character of '((lost-spaces . 3) #w"abc")
;;       line 1 character 1 suppress-lost-spaces-at-end t
;;       do (print x))




;;;; Making and Reclaiming Text and Testing for Blank, Empty, and Incomplete Texts



;;; `Make-empty-text' makes a new `empty text', a text with no characters in it.

(defun make-empty-text ()
  (slot-value-list
    (make-lost-spaces-text-element 0)
    (obtain-simple-text-string 0)))



;;; `Text-blank-p' is true if text is `blank', i.e., is empty or consists of spaces only.

(defun text-blank-p (text)
  (loop for text-element in text
	never
	  (and (text-line-p text-element)
	       (>f (text-line-length text-element) 0)
	       (not (and (=f (text-line-length text-element) 1)
			 (newline-p (charw text-element 0)))))))

;; Not really doing what it's documentation says! Review! (MHD 2/21/96)


(defun text-empty-p (text)
  (loop for text-element in text
	when (text-line-p text-element)
	  do (if (=f 0 (text-line-length text-element))
	       (return t)
               (return nil))))


;;; `Reclaim-text' reclaims text.

(defun-void reclaim-text (text)
  (reclaim-slot-value text))

;; Consider implementing a more efficient version of this.





;;; `Make-incomplete-box-translation-and-text' makes a new value for a
;;; box-translation-and-text slot of a text box consisting of no-value
;;; and `incomplete text', a text with only the ellipsis string in it.

(defun make-incomplete-box-translation-and-text ()
  (slot-value-cons
    no-value
    (convert-text-string-to-text
      (copy-text-string ellipsis-text-string))))

;; (MHD 4/2/91)

;; At present, this is only used in FACILITIES.  (MHD 4/2/91)



;;; The function `text-incomplete-p' is true iff text is equal to that of
;;; ellipsis-text-string, i.e., "...", q.v.

(defun text-incomplete-p (text)
  (loop with ellipsis-char
	for i from 0
	as text-char being each text-character of text
	if (not (<f i ellipsis-text-string-length))
	  return nil
	do (setq ellipsis-char (charw ellipsis-text-string i))
	if (char/=w ellipsis-char text-char)
	  return nil
	finally
	  (return (=f i ellipsis-text-string-length))))

;; Tests:
;;   (text-incomplete-p '((lost-spaces . 0) #w"..."))
;;   => T  ; most straightforward case
;;   (text-incomplete-p '((lost-spaces . 0) #w"." (lost-spaces . 0) #w".."))
;;   => T    ; oddly but validly broken up into multiple text lines
;;   (text-incomplete-p '((lost-spaces . 0) #w""))
;;   => nil  ; blank text
;;   (text-incomplete-p '((lost-spaces . 0) #w"   ..."))
;;   => nil  ; leading spaces
;;   (text-incomplete-p '((lost-spaces . 2) #w"..."))
;;   => nil  ; trailing (lost) spaces
;;   



;;; The function `abbrev-text' is a little ditty for debugging.

#+development
(defun abbrev-text (text)
  (if (consp text)
      (loop for element in text
	    when (text-line-p element)
	      return (if (> (text-line-length element) 25)
			 (tformat-text-string
			   "~a..."
			   (text-string-substring element 0 25))
			 element))
      text))

(defun-simple add-intercepted-token-to-text (text)
  (slot-value-cons (slot-value-list 'intercepted) text))

(defun-simple intercepted-text-p (text)
  (loop while (consp text)
	for token = (pop text)
	thereis (and (consp token) (eq (car token) 'intercepted))))


;;; `texts-equal-p' -- takes two texts and returns whether or not they are the
;;; same.  In this implementation, "the same" means "they would produce the
;;; same text-string."  This function is inefficient, but I'm not sure there's
;;; a more efficient way to do the same thing, and our expert on "text"s, Mark
;;; David, is no longer here, so this will have to do for now.  This function
;;; is small and self-contained, and could always be improved later.  jv 1/12/07

(defun texts-equal-p (text1 text2)
  (let* ((text-string-1 (convert-text-to-text-string text1))
         (text-string-2 (convert-text-to-text-string text2))
         (equal-p (text-string= text-string-1 text-string-2)))
    (reclaim-text-string text-string-1)
    (reclaim-text-string text-string-2)
    equal-p))




;;;; Text Spot

;;; A `text-spot' records information about where in a fragment of text the
;;; mouse appears.  The `tightness-of-text-spot' is a metric of how close to the
;;; actual text the mouse was, currently it is one of these values
;;;   1000 -- there was actually no text.  This case arises when a table cell
;;;           contains a block.
;;;    110 -- there was text, but the mouse was very far from it.
;;;    100 -- there was text we were close, but the nearest text
;;;           was lost spaces.
;;;     50 -- we were within a half a line or word space.
;;;     20 -- we were within 2 pixels of the text.

;;; The appearance of a text spot can implies these behaviors for example:
;;;   - if tight enough we may click-to-edit
;;;   - if an editor is active we may mark text.
;;;   - if an edit menu choice is offered we may enter the editor
;;;     at a particular location.
;;;   - some things (buttons, menus, scraps, etc.) may override those behaviors.

;;; The slot `editable-text-spot-p' is set in a lazy manner by the magic
;;; argument editable-text-spot-p.  It takes on one of three values :unknown, t
;;; or NIL.  It remains :unknown until requested.

;;; The slot `enclosing-item-of-text-spot-visible-p' defaults to true, but can
;;; be set nil under certain conditions. Specifically, in fill-out-text-spot,
;;; for a table that is not visible itself, it is set to nil.  However, if the
;;; text is tightly close to the spot, it is set to true.  This is meant to
;;; ensure that only clicks that are "tightly" in text result in click-to-edit
;;; behavior, while clicks a little further away cause selection or a popup menu
;;; or similar, while far away clicks on non-visible parts are ignored. This
;;; slot is read by the click-to-edit UI command, and has to be true for
;;; click-to-edit to happen.

;;; See also fill-out-text-spot.

(def-spot text-spot
    :slots ((tightness-of-text-spot 1000)
	    (enclosing-item-of-text-spot-visible-p t)
	    (editable-text-spot-p :unknown)
	    line-index-of-text-spot
	    character-index-of-text-spot
	    x-in-workspace-for-text-cursor-of-text-spot
	    y-in-workspace-for-text-cursor-of-text-spot
	    text-of-text-spot
	    format-frame-of-text-spot
	    format-plist-of-text-spot)
    :abstract-type t
    :type-of-frame-represented block ;; currently table or text-box
    )

;;; A `table-spot' is the abstract type from which most actual table spots are
;;; refined.  Note that this is a subtype of a text-spot, but not all table
;;; cells have text in them.  See also fill-out-table-spot.

(def-spot table-spot
    :include text-spot
    :slots (row-index-of-spot
	     column-index-of-spot
	     table-cell-of-spot?
	     left-edge-of-cell-of-table-spot
	     top-edge-of-cell-of-table-spot
	     right-edge-of-cell-of-table-spot
	     bottom-edge-of-cell-of-table-spot
	     )
    :enclosing-spot-type image-plane-spot
    :innermost-spot-p nil
    :abstract-type t
    :type-of-frame-represented table)



;;; `Fill-out-text-spot' is called in the dynamic extent of generating
;;; the spots that are subtypes of text-spot.  It is called ONLY if there
;;; is actually text in the spot being generated.

(defun fill-out-text-spot (text-spot text-box-or-table mouse-pointer
				     text format-frame format-plist)
  (let ((image-plane?			; May be NIL for synthesized mouse pointers.
	  (blackboard-argument-of-mouse-pointer mouse-pointer 'image-plane))
	text-box? text-cell? left-edge-of-cell? top-edge-of-cell?)
    (setf (text-of-text-spot text-spot) text)
    (setf (format-frame-of-text-spot text-spot) format-frame)
    (setf (format-plist-of-text-spot text-spot) format-plist)
    (when (cond ((frame-of-class-p text-box-or-table 'text-box)    ;; Text-box
		 (setf text-box? text-box-or-table)
		 image-plane?)
		(t                           ;; or Table with Text
		 (setf text-cell? 
		       (table-cell-of-spot? text-spot))
		 (setf left-edge-of-cell?
		       (left-edge-of-cell-of-table-spot text-spot))
		 (setf top-edge-of-cell?
		       (top-edge-of-cell-of-table-spot text-spot))
		 (setf (enclosing-item-of-text-spot-visible-p text-spot)
		       (table-visible-in-image-plane-p
			 text-box-or-table text-cell? image-plane?))
		 t))
      (loop
	#+development
	  finally
	    #+development (error "No text-spot didn't get filled out.")
	  with x-in-window = (blackboard-argument-of-mouse-pointer
				  mouse-pointer
				  'x-in-window)
	  with y-in-window = (blackboard-argument-of-mouse-pointer
				  mouse-pointer
				  'y-in-window)
	  for tightness       in '(    20  50 100 120)
	  for tightness-arg   in '(:tight   t nil nil)
	  for lost-spaces-arg in '(   nil nil   t nil) 
	  do
	(multiple-value-bind (line-index?
			       character-index?
			       new-text-tail?
			       x-of-cursor-in-text?
			       y-of-cursor-in-text?)
	    (find-position-in-text-given-image-plane
	      text-box-or-table
	      text-box? text-cell? left-edge-of-cell? top-edge-of-cell?
	      lost-spaces-arg ;; Humm?
	      image-plane?
	      x-in-window
	      y-in-window
	      nil ; line-index?
	      nil ; character-index?
	      nil ; text-tail?
	      tightness-arg ; only-if-in-text?
	      nil) ; find-character-instead-of-position-between?
	  (declare (ignore new-text-tail?))

	  ;; Got it?
	  (when line-index?
	    ; (print (list tightness line-index? character-index?))
	    (setf (tightness-of-text-spot text-spot) tightness)
	    (setf (line-index-of-text-spot text-spot) line-index?)
	    (setf (character-index-of-text-spot text-spot) character-index?)
	    (setf (x-in-workspace-for-text-cursor-of-text-spot text-spot)
		  x-of-cursor-in-text?)
	    (setf (y-in-workspace-for-text-cursor-of-text-spot text-spot)
		  y-of-cursor-in-text?)
	    (when (and (frame-of-class-p text-box-or-table 'table)
		       (null (enclosing-item-of-text-spot-visible-p text-spot))
		       (eq tightness-arg :tight))
	      (setf (enclosing-item-of-text-spot-visible-p text-spot) t))
	    (return)))))))



;;;; Text Boxes




;;; A `text box' is a subclass of block used to display formatted
;;; text.  In a sense it is a stand alone text cell.  Sadly the
;;; code for text-cells and the code for text-boxes diverges in
;;; a number of ways.

;;; The state for the text-cell in a text box is kept in the text
;;; slot named box-translation-and-text and is formatted in
;;; accordance with the values of slots text-box-format and
;;; text-cell-plist-for-box.

;;; Text-boxes have min and max widths and heights.  Meanwhile the
;;; text cell embedded in the text-box may extend outside text-box
;;; edges to the right and below, but clipping assures it isn't drawn
;;; when it does.

;;; The text box may have a frame so the text cell is nested inside
;;; that frame, and then inside any border given by the
;;; text-box-format.  The frame may scroll the text cell.

;;; Text boxes may have subblocks for cursors and text-regions, their
;;; extents lie in the range of the text-cell bounds.

;;; There is a rich set of built in subclasses for text-boxes
;;; Some notable examples are: FREE-TEXT, MESSAGE, COMMAND, EDIT-BOX
;;; DIAL-MARKING-LABEL, SCRAP, TYPE-IN-TEXT-BOX, and QUESTION-MARK-BOX

;; What of text-cell-desired-maximum-line-measure-for-text-box?
;; What of default-text-box-format-name

(def-class (text-box block define-predicate
		     (class-export-comment
		       "These must be dissected: <br> ~
	text: g2-text,		{from box-translation-and-text} <br> ~
	text-box-format: text-format-part, <br>
	These mins and maxes should be exported with a new api. The current model is too ~
	confusing: ~
	<ul><li>minimum-width-of-text-box,  ~
	<li>text-cell-desired-maximum-line-measure-for-text-box?, ~
	<li>minimum-height-of-text-box, ~
	<li>maximum-height-of-text-box</ul>"))  

  (box-translation-and-text			; nil or (translation . text)
     nil (type statement text)			; always overridden
     vector-slot system
     do-not-identify-in-attribute-tables)

  (text-box-format				; a text box format
    nil vector-slot system save)	        ; always overridden
  (default-text-box-format-name			; must be non-nil for instantiable classes
    nil lookup-slot system
    (attribute-export-comment "Export, writable"))
  (text-cell-plist-for-text-box			; a text cell plist
    nil vector-slot system save		; made a vector slot
					;   for performance (MHD 2/7/96)
    (attribute-export-comment "These values map to text-cell-plist-for-text-box.<br> ~
<li>magnification: [x-magnification: number, y-magnification: number], ~
<li>highlight-color: color-symbol, ~
<li>border-color: color-symbol, ~
<li>line-color: color-symbol, <br>"))
  (default-text-box-colors-for-class
      nil lookup-slot system class-slot do-not-save (type text-cell-colors)
      not-user-editable no-accessor do-not-put-in-attribute-tables user-overridable
      (attribute-export-comment "Export, writable"))      
  (minimum-width-of-text-box			; vector slot?
    0 (type integer) lookup-slot system
    do-not-put-in-attribute-tables
    (attribute-export-comment "New api"))
  
  (text-cell-desired-maximum-line-measure-for-text-box?
					        ; not a hard limit, since we can't break
						;   everywhere (just at spaces & hyphens, etc.);
						;   overrides the text box format slot
    nil (type integer?) lookup-slot system      ;   maximum-format-width-for-text-cell;
						;   new for 4.0. (MHD 11/9/94)
    do-not-put-in-attribute-tables
    (attribute-export-comment "New api"))
  
  (maximum-width-of-text-box?
    nil lookup-slot system
    do-not-put-in-attribute-tables
    (attribute-export-comment "New api"))
  (minimum-height-of-text-box			; vector slot?
    0 (type integer) lookup-slot system
    do-not-put-in-attribute-tables
    (attribute-export-comment "New api"))
  (maximum-height-of-text-box
    #.(truncate (/ most-positive-workspace-coordinate 4))
    (type integer)
    lookup-slot system
    do-not-put-in-attribute-tables
    (attribute-export-comment "New api")))



(defun box-translation-and-text-function (text-box)
  (box-translation-and-text text-box))




;;; Category-Evaluator Interfaces that are used in many other
;;; categories

(define-category-evaluator-interface (color-or-metacolor
				       :access read-write)
    (member foreground background transparent
	     . #.(mapcar #'car standard-gensym-color-alist))
       
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))

(define-category-evaluator-interface (font-name
				       :access read-write)
    (member small large extra-large)
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))






;;; `Text-cell-colors' are specified for a user-defined text-box class through
;;; the default-overrides slot on class-definitions.  The class-specific value
;;; is held on the default-text-box-colors-for-class slot-description.  The
;;; actual value to be used for a class is derived from the default-text-
;;; box-colors-for-class slot-descriptions for the user-defined classes on the
;;; class inheritance path for class, and becomes the value of the
;;; text-cell-plist-for-text-box slot for the class.  This system follows the
;;; model of default-message- properties.

(add-grammar-rules
  '((text-cell-colors 'none nil nil-function)
    (text-cell-colors text-cell-colors-1)

    (text-cell-colors-1 text-cell-color (1))
    (text-cell-colors-1 (text-cell-color '\; text-cell-colors-1) (1 . 3))

    (text-cell-color (text-color-attribute 'is color-or-metacolor)
		      (1 . 3))))

(def-slot-value-compiler text-cell-colors (parse)
  (if (eq parse 'none) nil parse))

(define-category-evaluator-interface (text-cell-colors :access read-write)
    (or (no-item)
	(sequence (structure text-cell-color-spec
			     ((region (member
					border-color
					background-color
					text-color
                    line-color))
			      (color (named color-or-metacolor))))
		  1))
  ((set-form (evaluation-value))
   (if evaluation-value
       (with-evaluation-sequence-to-phrase-list-mapping
	   (evaluation-value text-cell-color-info)
	 (with-structure (text-cell-color-info text-cell-color-spec)
	   (phrase-cons region color)))
       'none))
  ((get-form (slot-value))
    (if slot-value
	(with-list-to-evaluation-sequence-mapping
	    (slot-value text-cell-color-info)
	  (with-new-structure (text-cell-color-spec)
	    (setf region (car-of-cons text-cell-color-info))
	    (setf color (cdr-of-cons text-cell-color-info))))
	nil)))

(def-slot-value-writer text-cell-colors (value)
  (if (null value)
      (twrite "none")
      (loop for (property . rest) on value
	    for region = (car property)
	    for color = (cdr property)
	    do
	(tformat "~(~a is ~a~)"
		 (if (eq region 'line-color) 'text-color region) color)
	(when rest (twrite "; ")))))

(def-class-slot-description-updater default-text-box-colors-for-class
    (text-box-class new-value)
  (change-class-slot-description-value
    'default-text-box-colors-for-class text-box-class new-value)
  (loop for class being each subclass of text-box-class
	do
    (process-default-text-box-colors class nil)))

(defun process-default-text-box-colors (class called-from-alter-inheritance?)
  (let* ((default-text-box-colors
	     (class-slot-description-value
	       'default-text-box-colors-for-class class))
	 (class-description (class-description class))
	 (class-inheritance-path
	   (class-inheritance-path class-description))
	 (specified-border-color?
	   (cdr (assq 'border-color default-text-box-colors)))
	 (specified-text-color?
	   (cdr (assq 'line-color default-text-box-colors)))
	 (specified-background-color?
	   (cdr (assq 'background-color default-text-box-colors)))
	 (plist-init-form?
	   (nconc
	     (if specified-border-color?
		 (frame-list 'border-color specified-border-color?)
		 (loop for superior in (cdr class-inheritance-path)
		       do
		   (when (and (user-defined-class-p superior)
			      (subclassp superior 'text-box))
		     (let ((superior-specified-border-color?
			     (cdr (assq 'border-color
					(class-slot-description-value
					  'default-text-box-colors-for-class
					  superior)))))
		       (when superior-specified-border-color?
			 (return (frame-list
				   'border-color
				   superior-specified-border-color?)))))))
	     (if specified-text-color?
		 (frame-list 'line-color specified-text-color?)
		 (loop for superior in (cdr class-inheritance-path)
		       do
		   (when (and (user-defined-class-p superior)
			      (subclassp superior 'text-box))
		     (let ((superior-specified-text-color?
			     (cdr (assq 'line-color
					(class-slot-description-value
					  'default-text-box-colors-for-class
					  superior)))))
		       (when superior-specified-text-color?
			 (return (frame-list
				   'line-color
				   superior-specified-text-color?)))))))
	     (if specified-background-color?
		 (frame-list 'background-color specified-background-color?)
		 (loop for superior in (cdr class-inheritance-path)
		       do
		   (when (and (user-defined-class-p superior)
			      (subclassp superior 'text-box))
		     (let ((superior-specified-background-color?
			     (cdr (assq 'background-color
					(class-slot-description-value
					  'default-text-box-colors-for-class
					  superior)))))
		       (when superior-specified-background-color?
			 (return (frame-list
				   'background-color
				   superior-specified-background-color?))))))))))
    (when plist-init-form?
      (if called-from-alter-inheritance?
	  (let* ((plist-slot-description-from-text-box-class
		  (slot-description-from-class
		    'text-box 'text-cell-plist-for-text-box))
		 (new-slot-description
		   (make-slot-description
		     'text-cell-plist-for-text-box 'text-box class nil
		     plist-init-form?
		     (vector-slot-index?
		       plist-slot-description-from-text-box-class)
		     nil
		     (slot-features
		       plist-slot-description-from-text-box-class))))
	    (reclaim-frame-list plist-init-form?)
	    new-slot-description)
	  (with-deferred-drawing ()

	    (loop for instance being each class-instance of class
		  do
	      (erase-images-of-block instance t))
	    
	    (let ((plist-slot-description
		    (get-slot-description
		      'text-cell-plist-for-text-box
		      (slot-descriptions class-description))))
	      (unless (equal plist-init-form?
			     (slot-init-form plist-slot-description))
		(update-slot-description
		  class plist-slot-description nil plist-init-form?
		  (slot-features plist-slot-description) nil nil)))
	    
	    (loop for instance being each class-instance of class
		  do
	      (draw-images-of-block instance t))
	    (reclaim-frame-list plist-init-form?))))))




;;; The `initialize method for text-box' takes care of reformatting the text of
;;; text-box, if any.  In practice, this will only be invoked with non-nil text
;;; to initialize a cloned text box, since when a text box is created it has no
;;; text or text box format; these must be filled in, however, before the text
;;; box is put into general use.

(def-class-method initialize (text-box)
  (funcall-superior-method text-box)
  (when (box-translation-and-text text-box)
    ;; if non-nil, assume (text-box-format text-box) is non-nil, and reformat
    (reformat-text-box-in-place text-box)))

;; The call to reformat used to be explicitly in clone-frame.  This is just
;; cleaner.  (MHD 7/19/94)






(def-spot text-box-spot
    :slots nil
    :include text-spot
    :enclosing-spot-type image-plane-spot		    ; Correct?
    :innermost-spot-p t					    ; Correct?
    :abstract-type nil ;; sometimes.
    :type-of-frame-represented text-box)

(def-class-method generate-spot (text-box mouse-pointer)
  (generate-text-box-spot text-box mouse-pointer (make-text-box-spot)))

(defun generate-text-box-spot (text-box mouse-pointer text-box-spot)
  (fill-out-text-spot text-box-spot text-box mouse-pointer
		      (cdr (box-translation-and-text text-box))
		      (text-box-format text-box)
		      (text-cell-plist-for-text-box text-box))
  (push-last-spot mouse-pointer text-box-spot text-box))



(define-slot-alias text box-translation-and-text text-box)

;; Alias added 6/17/91 for 3.0.  In 2.1 & earlier, this aliasing was accomplished
;; by special case code in a bunch of places, some of which still need cleanup!
;; (MHD 6/17/91)



;;; `Put-box-translation-and-text-slot-value' is a method on text-boxes...

(def-generic-method put-box-translation-and-text-slot-value (frame box-translation-and-text initializing?)
  )

(def-slot-putter box-translation-and-text
    (text-box box-translation-and-text initializing?)
  (let ((confine-updating-to-block-rectangle?
	  (and (not (has-subblocks-p text-box))	; could have attribute displays,
							    ;   or (remotely possible) name-boxes
	       (null (connections text-box))))	;   outside of block rectangle
	(stored-value nil)
	(do-not-reclaim-old-value? nil))
    
    (updating-images-of-block (text-box
				:locally confine-updating-to-block-rectangle?
				:condition (and (not initializing?) (superblock? text-box)))

      (multiple-value-setq (stored-value do-not-reclaim-old-value?)
	(funcall-method
	  'put-box-translation-and-text-slot-value
	  text-box box-translation-and-text initializing?))
      (unless initializing?
	(reformat-text-box-in-place text-box)))

    (values stored-value do-not-reclaim-old-value?)))

;; This will not work for an edit box, since an edit box may have subblocks that do not
;; fit entirely within the edit box rectangle.  Also, this would inappropriately reformat
;; an edit box.

;; Do the erasing, reformatting, and redrawing more efficiently!  (The text-box reformatting
;; could be saved in some cases by looking at an edit box.)

;; See file RULES for extensive comments on box-translation-and-text.  Its own editing will
;; cause a completely new value to appear with no common conses.  However, the value will be
;; modified (rplaca, rplacd) as a side effect of changing another slot.  This is
;; accomplished during compilation, not during slot putting of focal-role-names, and all
;; deleted pieces are released and new ones properly copied.



(def-class-method put-box-translation-and-text-slot-value
    (text-box box-translation-and-text initializing?)
  (declare (ignore initializing?))
  (values
    (setf (box-translation-and-text text-box) box-translation-and-text)
    nil))

;; This default is needed at least for readouts.







;;;; Text Cell Plists



;;; A `text cell plist' (in a text box or text cell) may have the
;;; following properties:
;;;
;;;      x-magnification   ; magnifies current-image-x(y)-scale;
;;;      y-magnification   ; overrides text-cell-x(y)-magnification?
;;;
;;;      line-color        ; takes precedence over text cell format line color
;;;                        ; this is known as text-color in the language.
;;;                               
;;;      border-color      ; takes precedence over text cell format border color
;;;
;;;      background-color  ; can be used for highlighting, done via language.
;;;      highlight-color
;;;          takes precedence over background color, is more
;;;          efficient for incremental changes, but results in false
;;;          color for text lines Rule highlighting, message board
;;;          highlighting, slot highlighting.  The slot putter for
;;;          text-cell-plist-for-text-box prevents this element from
;;;          being included in the value when initializing, either
;;;          via cloning or by reading it in from a saved KB.  This
;;;          is very kludgey. (MHD 2/25/91 and 7/19/94)
;;;
;;;      y-offset-for-text
;;;          for scrolling in a text box the next two may be
;;;          used only with y-offset-for-text  (Obsolete)
;;;
;;;      line-index-of-first-fully-visible-line  ; absent => first line
;;;      number-of-fully-visible-lines           ; absent => all remaining lines
;;;
;;;      choice           ; for menu choices
;;;
;;;      special-case?
;;;           for a special case of edit menu choice; may be
;;;           ANY-INSTANCE or a subcommand (including END); see module
;;;           EDIT the handling of these two slots varies more than
;;;           you would expect between subcommand, token, catagory,
;;;           and kfep menus
;;;      radio-button-status
;;;           Either ON, OFF, or NIL on a subcommand table.
;;;           If non-nil then this is a radio button.
;;;
;;;      workstation-event-interpretations  ; not currently used.
;;;
;;;      leave-as-single-line?
;;;            when leave-text-representation-as-a-single-line? is set
;;;            by a slot value writer; used in module TABLES when
;;;            creating a menu we set this and it speeds up vertical
;;;            layout, and it forces reformat-text to skip formatting
;;;            at all.
;;;
;;;       <frame>
;;;          A appearing on the value cells in attribute tables and
;;;          tabular functions of one argument. See comment below.
;;;
;;;       new as of 3/3/98:   (MHD 3/3/98)
;;;       text-alignment
;;;         left    => overrides/same as text-cell-line-justification? = nil
;;;         center  => overrides/same as text-cell-line-justification? = center
;;;         right   => overrides/same as text-cell-line-justification? = right

;;; In addition, the text cell plist specifies, where appropriate, the frame
;;; slot, table-of-values arg, or table-of-values value represented by the text
;;; cell.  To conserve space, this is implemented as a property whose indicator
;;; is the frame and whose value is the slot name, the position index of the
;;; table-of-values arg, or one less than the negative of the position index of
;;; the table-of-values value, respectively.

;;; Text cell plists should be nil for "normal" cases, as an optimization.

;;; All conses that make up a text cell plist should be unshared slot value conses.

(def-concept text-cell-plist)



;;; The `slot putter for text-cell-plist-for-text-box' removes the hightlight-color
;;; property from value if initializing? is true, i.e., when either reading in the
;;; text-box from a KB or cloning it.

(def-slot-putter text-cell-plist-for-text-box (text-box value initializing?)
  (setf (text-cell-plist-for-text-box text-box) value)
  (when initializing?
    (change-text-box-property text-box 'highlight-color nil))
  (text-cell-plist-for-text-box text-box))



;;; `Change-text-box-property' makes the text cell plist of text-box have the property
;;; specified by indicator and value? or, if value? is nil, not have a property under
;;; indicator.  Slot value consing or recycling is done as necessary.

(defun change-text-box-property (text-box indicator value?)
  
  ;; need to explicitly note change (if snapshotting) because setf of slot
  ;; accessor might be bypassed
  (note-change-to-block text-box 'text-cell-plist-for-text-box)
  
  (let* ((class-description (class-description-slot text-box))
	 (slot-description
	   (get-slot-description-of-class-description 
	     'text-cell-plist-for-text-box class-description))
	 (slot-init-form
	   (slot-init-form slot-description))
	 (text-cell-plist-for-text-box
	   (text-cell-plist-for-text-box text-box)))
    (if (and text-cell-plist-for-text-box
	     (eq slot-init-form text-cell-plist-for-text-box))
	(setf (text-cell-plist-for-text-box text-box)
	      (setq text-cell-plist-for-text-box	; used again below
		    (copy-for-slot-value
		      text-cell-plist-for-text-box))))
    ;; Above logic added today.  Identical logic added to
    ;;   change-icon-attribute, also. (MHD 9/11/89)
    (loop as l-trailer? = nil then (cdr l)
	  as l = text-cell-plist-for-text-box
	       then (cdr l-trailer?)
	  while l
	  when (eq (car l) indicator)
	    do (cond
		 (value?
		  ;; reclaim-slot-value here if needed later
		  (setf (cadr l) value?))
		 (t (if l-trailer?
			(setf (cdr l-trailer?) (cddr l))
			(setf (text-cell-plist-for-text-box text-box) (cddr l)))
		    (setf (cddr l) nil)
		    ;; reclaim-slot-value here if needed later (instead
		    ;;   of the following)
		    (reclaim-slot-value-list l)))
	       (return value?)
	  finally
	    (if value?
		(setf (text-cell-plist-for-text-box text-box)
		      (slot-value-cons
			indicator
			(slot-value-cons
			  value?
			  (text-cell-plist-for-text-box text-box)))))
	    (return value?))))

;; Note that all strings and list structure in this slot are assumed to be unshared
;; and recyclable.  As an optimization, this does not look for non-top-level conses
;; to recycle or text strings to recycle, since at present in practice there can be
;; none.






;;;; Text Box Formats



;;; A `text box format' specifies the format for a text box or text cell and can serve as
;;; its "type".  (Text boxes are described in module BOXES.)

;;; When a text box or cell is formatted, a particular `format width' is used.  The format
;;; used for a cell should be as near to minimum-format-width-for-text-cell as possible,
;;; unless there is extra space available in the cell due to the sizes of cells in other
;;; rows, in which case that extra space should also be used, up to a maximum of maximum-
;;; format-width-for-text-cell.  Formatting should never force the width of a text box or
;;; cell to exceed the `format width' used, except where there are unbreakable words of
;;; great length.  Note that if minimum-width-for-text-cell exceeds minimum-format-width-
;;; for-text-cell, then maximum-format-width-for-text-cell should equal minimum-format-
;;; width-for-text-cell.  Note also that when all three of these values in a particular
;;; text box format are equal, a box or cell formatted per that format can be freely
;;; edited without perturbing the left and right edge positions of the box or cell.
;;; The three values mentioned are slots in the text-box class.

;;;     Summary: by PGA, 3/8/95
;;;     Choose format-width from among the following constraints and guidelines.
;;;     The chosen format-width may be exceeded in formatting when there is an
;;;     unbreakable word which exceeds format-width. 
;;;
;;;     a. minimum-width-for-text-cell		The nominal amount of space available
;;;     b. maximum-format-width-for-text-cell	Supplied by the user? How? ****
;;;     c. minimum-format-width-for-text-cell

;;;     if a > c, then b = c, ('should =') 

;;;     if a = b = c, editing will not result in any changes to box size. Is
;;;     this strictly true, or does it depend on the absence of unbreakable
;;;     words.

;;; A properly designed text box format must provide enough line spacing for the
;;; font(s) in its font map.
;;;
;;; Here is how a text box format relates to a line of text:
;;;
;;;      -----------------------  | <- top of the line                       |
;;;                               |                                          |
;;;                               |} - text-cell-baseline-position           |
;;;                               |                                          |
;;;                               |                                          |
;;;                               |                                          |} text-cell-line-height
;;;      -----------------------  + <- baseline                              |
;;;                               |                                          |
;;;                               |} - (text-cell-line-height                |
;;;                               |     - text-cell-baseline-position)       |
;;;      -----------------------  + <- bottom of line                        |
;;;                               |} - text-cell-line-spacing
;;;      -----------------------  +
;;;
;;;  Note: font descent
;;;          <= (text-cell-line-height - text-cell-baseline-position)
;;;        font ascent
;;;          <= baseline
;;;        baseline-to-baseline distance
;;;          = (text-cell-line-spacing + text-cell-line-height)
;;;
;;; It is the programmer's responsibility to make the text box format be able to "fit"
;;; the ascent and descent characteristics of the font.  If it not done right, then
;;; lines can be partially clipped, or graphic turding may even result.
;;;
;;; The `cell of a text box' has its top edge text-box-top-border-width units from
;;; the top-edge-of-block of the text box.
;;;
;;; The top of the first line of text in a cell is text-cell-top-margin units below
;;; the top of the cell.
;;;
;;; The border width outside of a cell, and the margin inside of a cell, are not
;;; subject to magnification by text-cell-y-magnification?; but
;;; text-cell-line-spacing, text-cell-line-height, and text-cell-baseline-position
;;; are subject to magnification.
;;;
;;; Thus, the top of the first line of text in a text box is at
;;;
;;;     the top-edge-of-block of the text-box
;;;     + text-box-top-border-width + text-cell-top-margin
;;;
;;; And the top of the second line of text is at
;;;
;;;     the top-edge-of-block of the text-box
;;;     + text-box-top-border-width + text-cell-top-margin
;;;     + ((text-cell-line-height + text-cell-line-spacing)
;;;        magnified by text-cell-y-magnification?, if non-nil)
;;;
;;; When working on the drawing of text in a specific window, there are a few
;;; caveats:
;;;
;;;    (1) non-zero-width borders are scaled as "hairlines";
;;;    (2) some kinds of text boxes "grow" hairline borders at certain scales
;;;        when the border width is zero, or when the text is invisible, or ...;
;;;    (3) scaling subjects all these calculations to roundoff error, which
;;;        must be avoided in clever ways

(def-format-class (text-box-format format-frame)

  (text-cell-font-map				; a list of ab font names
    (hm14) (type font-map) vector-slot system)

  (text-cell-line-color?			; defaults to table line color
    nil (type color) vector-slot system)
  (text-cell-background-color?			; defaults to table background color
    nil (type color) vector-slot system)

  (text-cell-x-magnification?			; magnifications of current-image-x-scale
    nil (type magnification-or-factor?)		;   and current-image-x-scale
    vector-slot system)
  (text-cell-y-magnification?			; text-cell-plist can override these!
    nil (type magnification-or-factor?)
    vector-slot system)

  (text-cell-left-margin			; these are NOT subject to magnification
    12 (type width) vector-slot system)		; experiment with these!
  (text-cell-top-margin
    9 (type width) vector-slot system)
  (text-cell-right-margin
    12 (type width) vector-slot system)
  (text-cell-bottom-margin
    8 (type width) vector-slot system)

  (text-cell-line-height			; these are subject to magnification
    15 (type width) vector-slot system)
  (text-cell-baseline-position			; w.r.t. top of line
    12 (type width) vector-slot system)
  (text-cell-line-spacing			; experiment with these!
    5 (type width) vector-slot system)
  (default-word-spacing				; text width
    #.(convert-to-text-width 6)
    (type word-spacing) vector-slot system)
  (minimum-word-spacing				; text width
    #.(convert-to-text-width 3)
    (type word-spacing) vector-slot system)
  (maximum-word-spacing				; text width
    #.(convert-to-text-width 14)
    (type word-spacing) vector-slot system)

  (text-cell-paragraph-indentation		; these are subject to magnification
    24 (type width) vector-slot system)
  (text-cell-turnover-line-indentation		; experiment with these!
    0 (type width) vector-slot system)

  (text-cell-line-quadding?			; nil (for left), center, or right
    nil (type quadding) vector-slot system)
  (text-cell-lines-justified?
    nil (type boolean) vector-slot system)	; (MHD changed default to nil, 7/6/87)

						; move minimum-width-for-text-cell
						;   back here?
  (minimum-format-width-for-text-cell
    400 (type width) vector-slot system)	; 500 or 600?
  (maximum-format-width-for-text-cell
    100000				; by default, don't limit this at all,
					;   in effect; was 1000 (MHD 11/9/94)
    (type width) vector-slot system)	; was 800 (MHD 3/20/91)

  (text-cell-selection-actions			; user-input-action-bindings?
    nil vector-slot system)			;   give this a type!

  (text-box-left-border-width			; 0 for none; in workspace units
    2 (type width) vector-slot system)
  (text-box-top-border-width			; 0 for none; in workspace units
    2 (type width) vector-slot system)
  (text-box-right-border-width			; 0 for none; in workspace units
    2 (type width) vector-slot system)
  (text-box-bottom-border-width			; 0 for none; in workspace units
    2 (type width) vector-slot system)
  (text-box-border-color?			; defaults to current-default-line-color
    nil (type color) vector-slot system)


  (minimum-width-for-text-cell
     0 (type width) vector-slot system)
  (minimum-height-for-text-cell			; Added (MHD 11/9/88)
    0 (type width) vector-slot system))

(defun-simple text-cell-line-height-function (format)
  (text-cell-line-height format))

;; Improve the default slot values!

;; Use fonts sparingly in the default initialization for text-cell-font-map and in
;; text cell format descriptions.  Once their names have gotten into a saved kb, fonts
;; should be defined in AB "forever".

;; At present, minimum-width-for-text-cell is only used in reformat-text-box-in-place.

;; The use of and functionality of minimum-width-for-text-cell and minimum-height-for-
;; text-cell are not documented.  They are only used in reformat-text-box-in-place.
;; Minimum-height-for-text-cell was added, and both it and minimum-width-for-text-cell
;; were first put int into use 11/9/88 to support type-in boxes, only to support
;; functionality required by them. Format-text-cell has a comment where minimum-width-
;; for-text-cell presumably should be used and has a "FIX!" comment.  Prior to formats
;; added for type-in boxes, almost certainly no formats ever could have existed with
;; their minimum-width-for-text-cell not equal to 0. FIX!!! (MHD 11/9/88)

;; Consider changing the terms "paragraph" and "turnover".

;; Consider allowing any block to specify selection actions.


;; The slot value reclaimer 'text-cell-font-map' reclaims the text-cell-font-map slot and
;; also reclaims any entries on corresponding-icp-object-index-spaces which have
;; pointers 'eq to this font-map.  This will happen from time to time because
;; icp-objects are not copied before being added to a corresponding index.
;; Text-cell-font-map  slots are reclaimed whenever a KB is cleared.
;; This reclaimer loops over the index-spaces this font-map has been added to -
;; if it finds one which is 'eq it calls the reclaim-icp-object-map-for-font-map and
;; then exits the loop.
;; Note: the plist-of-corresponding-icp-object-maps-for-font-maps takes the following
;; form:
;;  ((<FONT1> (<ICP-PORT11> <INDEX11> ...) ... (<FONTN> (<ICP-PORTN1> <INDEXN1> ...))))



;;; The macro `text-cell-extra-diacritic-height' gives an extra amount of
;;; headroom beyond a text cell's line height to allow for diacritics.  This
;;; formula for extra height adds about 25% of the line height. This is
;;; especially needed for Thai, which commonly stacks diacritics 2 levels above
;;; a full-height base character.  Note that this does not affect positioning of
;;; a line of text, and should not normally affect formatting. Rather, it is
;;; used to determine clipping edges for painting a line of text text and
;;; invalidation areas for incremental changes to text.

(defun-substitution-macro text-cell-extra-diacritic-height (text-box-format)
  (ashw (text-cell-line-height text-box-format) -2)) ; 25% of line height

;; This is new for G2 8.0, under development. Consider making this a slot of
;; text-box-format! (MHD 12/19/03)



(def-slot-value-reclaimer text-cell-font-map
    (value frame)
  frame
  (loop for (icp-port index) on
	(get-icp-plist-element plist-of-corresponding-icp-object-maps-for-font-maps
			       (if
				 (null
				   (cdr value))
				 (car value)
				 value))
			     by 'cddr
	do
    (cond ((eq value
	       (get-object-from-index-space-if-any
		 (standard-icp-object-index-space icp-port)
		 index))
	   (reclaim-icp-object-map-for-font-map value)
	   (return t))))
   ;; Reclaim slot value after loop has completed
  (reclaim-slot-value value))

(defun text-cell-first-font (text-box-format)
  (first (text-cell-font-map text-box-format)))

(def-format-class (text-cell-format text-box-format))	; flush after eliminating uses!!



;;; Eventually, the lines-justified? and line-quadding? slots will be combined into a
;;; single slot, text-cell-line-justification?, which could have one of the four values
;;; nil (for flush left, ragged right), right, center, or justified.  For now, the
;;; equivalent macro is defined for this purpose during the transition.

(def-substitution-macro text-cell-line-justification? (text-box-format)
  (or (text-cell-line-quadding? text-box-format)
      (if (text-cell-lines-justified? text-box-format)
	  'justified
	  nil)))



;;; The macro `get-text-cell-line-justification' gets the justification to be
;;; used to format a text cell, first looking for an override specified by the
;;; text-alignment property in text-cell-plist, and, if not specified, then
;;; giving the value of the text-cell-line-justification? of text-box-format.
;;; Note that the value returned is in the format specified for
;;; text-cell-line-justification?; i.e., nil (not LEFT) represents flush left,
;;; ragged right, etc.

(defun-simple get-text-cell-line-justification
    (text-box-format text-cell-plist)
  (let ((alignment-override? (getfq-macro text-cell-plist 'text-alignment)))
    (if alignment-override?
	(if (eq alignment-override? 'left) nil alignment-override?)
	(text-cell-line-justification? text-box-format))))



;;; The macro `left-justified-text-box-p' does a quick test to see if text-box
;;; is left-justified (flush left, ragged right).

(def-substitution-macro left-justified-text-box-p (text-box)
  (null (get-text-cell-line-justification
	  (text-box-format text-box)
	  (text-cell-plist-for-text-box text-box))))



;;; `Get-backing-store-default-text-cell-line-justification' should be given a
;;; subclass of text-box.  It returns the justification specified for the text
;;; box format associated, by default, with that format frame.
;;;
;;; Note that text box formats are shared by many instances of a text box.  They
;;; thus serve as the "backing store" of format information for these instances,
;;; whereas their per-instance plist stores per-instance formatting information.
;;;
;;; The value returned is in the format specified for
;;; text-cell-line-justification?; i.e., nil (not LEFT) represents flush left,
;;; ragged right, etc.

(defun-simple get-backing-store-default-text-cell-line-justification
    (text-box-subclass)
  (let* ((format-name
	   (get-slot-init-form 'default-text-box-format-name text-box-subclass))
	 (format-description (format-description format-name)))
    (or (getfq format-description 'text-cell-line-quadding?)
	(if (getfq format-description 'text-cell-lines-justified?)
	    'justified
	    nil))))


;;; `Get-default-text-cell-line-justification' should be given a subclass of
;;; text-box.  It returns the justification that is used when an instance is
;;; created.  The value returned is in the format specified for
;;; text-cell-line-justification?; i.e., nil (not LEFT) represents flush left,
;;; ragged right, etc.

(defun-simple get-default-text-cell-line-justification (text-box-subclass)
  (let* ((init-form
	   (get-slot-init-form
	     text-box-subclass 'text-cell-plist-for-text-box)))	   
    (or (if init-form (getfq init-form 'text-alignment))
	(get-backing-store-default-text-cell-line-justification
	  text-box-subclass))))









(def-slot-putter text-cell-font-map (text-box-format font-map)
  (if loading-kb-p
      (loop for l on font-map
	    as substitute-ab-font-name?
	       = (cdr (assq (car l)
			    '((hc24 . hm24)
			      (hc14 . hm14))))	; etc! (maybe a defparameter)
	    when substitute-ab-font-name?
	      do (notify-user
		   "The obsolete font ~A, used in the just-read kb, has been changed to ~A.  ~
                    Do a save to make this change permanent."
		   (car l) substitute-ab-font-name?)
		 (setf (car l) substitute-ab-font-name?)
		 (setf (format-change? text-box-format) 0)))	; to flag font substitution
  (set-slot-value text-box-format 'text-cell-font-map font-map))

;; This assumes it is ok to clobber font-map.



(defvar post-draw-methods-for-text-box-formats '())

(defmacro def-post-draw-method-for-text-box-format (name compiled-simple-function)
  `(setf (getf post-draw-methods-for-text-box-formats ',name)
	 ,compiled-simple-function))

(defmacro text-box-post-draw-method (text-box-format)
  `(getf 
     post-draw-methods-for-text-box-formats
     (name-or-names-for-frame ,text-box-format)))




;;; The macros `x-magnification?' and `y-magnification?' get the x/y magnification
;;; for a text cell (or a text box) given its text cell format and text cell plist.
;;; If none, they return nil.

(def-substitution-macro x-magnification? (text-cell-plist text-cell-format)
  (or (if text-cell-plist (getfq text-cell-plist 'x-magnification))
      (text-cell-x-magnification? text-cell-format)))

(def-substitution-macro y-magnification? (text-cell-plist text-cell-format)
  (or (if text-cell-plist (getfq text-cell-plist 'y-magnification))
      (text-cell-y-magnification? text-cell-format)))







;;;; Text Visibility



;;; `Text-too-small-to-draw-p' is true unless text formatted according to text-box-format
;;; would be too small to draw, specifically, when the line height scaled by the mininum of
;;; x-scale and y-scale is less than the value of the minimum-line-height-of-text-to-draw
;;; slot of current-window.  See also scale-too-small-for-details-p.

(def-substitution-macro text-too-small-to-draw-p
    (text-box-format text-cell-plist x-scale y-scale)
  (let* ((x-magnification? (x-magnification? text-cell-plist text-box-format))
	 (y-magnification? (y-magnification? text-cell-plist text-box-format))
	 (magnified-x-scale
	   (if x-magnification?
	       (magnify x-scale x-magnification?)
	       x-scale))
	 (magnified-y-scale
	   (if y-magnification?
	       (magnify y-scale y-magnification?)
	       y-scale)))	
    (<r (delta-y-in-window (text-cell-line-height text-box-format)
			   (minf magnified-x-scale magnified-y-scale))
        6)))    ; minimum-line-height-of-text-to-draw slot of current-window!!

;; This should take magnification into account, using text-cell-plist!  See draw-text-
;; segment. -- UPDATE: done. (MHD 6/2/99)

;; This should take a minimum-line-height-of-text-to-draw argument!

;; Consider changing the heuristic used here.  In particular, the way x-scale is used is
;; somewhat questionable.



;;; `Text-visible-p' ...

;;; Tables should be assumed to be visible unless they are known to consist only of
;;; text, as edit menus and certain help tables do.

(defun-simple text-visible-p (text-box-format text-cell-plist x-scale y-scale)
  (not (or (scale-too-small-for-details-p x-scale y-scale)
	   (text-too-small-to-draw-p
	     text-box-format text-cell-plist x-scale y-scale))))

;; Consider defining this as a macro.



;;; `Text-box-visible-p' ... returns either nil, t, :without-text, or :just-text.  It is
;;; consistent with the draw method for a text box.  It should not be used for text boxes
;;; being dragged (because it does not take the suppression of text into account for that
;;; case).

;; This is somewhat heuristic.  It assumes that if there is any border, the (whole) text
;; box is visible.  It also assumes that when an explicit background (or highlight) color
;; is specified, it will be different than the image plane background and thus render the
;; text box visible.  Finally, it ignores the case where a text box might be considered
;; visible only because it had a text region, an edit cursor, or a name box.

(defun text-box-visible-p (text-box x-scale y-scale)
  (let* ((text-box-format (text-box-format text-box))
	 (text-cell-plist (text-cell-plist-for-text-box text-box))
	 (text-visible? (text-visible-p text-box-format text-cell-plist x-scale y-scale)))
    (if (or (or (>w (text-box-left-border-width text-box-format) 0)
		(>w (text-box-top-border-width text-box-format) 0)
		(>w (text-box-right-border-width text-box-format) 0)
		(>w (text-box-bottom-border-width text-box-format) 0))
	    (or (text-cell-background-color? text-box-format)
		(getf text-cell-plist 'background-color)
		(getf text-cell-plist 'highlight-color)))
	(if text-visible? t :without-text)
	(if (or text-visible?
		(or (null (superblock? text-box))	; but will get a border here
		    (workspace-p (superblock? text-box))))
	    :just-text))))

;; Improve the heuristics!



;;; The function `text-box-has-border-p' returns true if the text-box has a
;;; border of non-zero width.

(defun text-box-has-border-p (text-box)
  (let ((text-box-format (text-box-format text-box)))
    (or (>w (text-box-left-border-width text-box-format) 0)
	(>w (text-box-top-border-width text-box-format) 0)
	(>w (text-box-right-border-width text-box-format) 0)
	(>w (text-box-bottom-border-width text-box-format) 0))))







;;;; Text Box Width and Magnification Limits



;;; `Maximum-Text-Box-Width-Or-Height' is the absolute maximum width or height a
;;; text box should be allowed to grow.  This is currently set at 8000.
;;; [Enforcement of this limit may be spotty at present. (MHD 5/18/95)]
;;;
;;; `Minimum-magnification-for-text-boxes' and
;;; `maximum-magnification-for-text-boxes' are the minimum and maximum
;;; magnifications, respectively, allowed on the text of a text box.  These are
;;; constant, unshared gensym floats that set the range of legal user
;;; magnifications, currently [.125 .. 4.0].
;;;
;;; Note that minimum-magnification-for-text-boxes,
;;; maximum-magnification-for-text-boxes, and maximum-text-box-width-or-height are
;;; designed to work together so that a maximumally magnified text box (with
;;; reasonably narrow borders and margins, under 90 workspace units), could not
;;; exceed the limits on workspace coordinates.
;;;
;;; The magnification limits are currently imposed in the g2-system procedure
;;; interface to magnifying the text of text boxes.
;;;
;;; The width and height limits are currently imposed in the interfaces to text
;;; box minimum width around message definitions, editing parameters, and the
;;; change-min-size dialog.

(defparameter minimum-magnification-for-text-boxes .125)
(defparameter maximum-magnification-for-text-boxes 4.0)

(defparameter maximum-text-box-width-or-height
  8000)					; (round (- most-positive-workspace-coordinate
					;           most-negative-workspace-coordinate)
					;        maximum-magnification-for-text-boxes)
					; => 8192

;; Note: the software cannot currently impose this limit on height.  Should be
;; fixed!  (Roughly, a 30,000 line text using extra-large font magnified
;; maximally, and centered in a workspace, would create a workspace with edges
;; that just exceeds most-positive-workspace-coordinate and
;; most-negative-workspace-coordinate.  This in itself wouldn't cause a crash,
;; but it's now in dangerous waters... Not likely at all to occur; still good to
;; fix at some point.
;;
;; Note: historically, the width limit was enforced by observing the
;; maximum-format-width-for-text-cell of the text box format as the limit
;; on text boxes.  That is being abandoned in favor of having this be
;; overridden by the minimum-text-box-width slot on boxes.





;;;; Computing Text Width and Height



;;; `Compute-width-of-longest-line' computes the width of the longest line in
;;; text-segment, including indentation but not lost spaces, and taking
;;; magnification into account.  If put-in-indentations-and-widths?  is non-nil,
;;; explicit indentation and line width elements are put in for each text line
;;; for which they are absent, by directly modifying text (in such a way that
;;; text lines are moved to new conses).

;;; text-tail-past-text-segment? is the position in text-segment at which to stop
;;; computing the width.  (If it is non-nil, it must be one of the top level
;;; conses of text-segment.)

(defun compute-width-of-longest-line
       (text-segment text-box-format text-cell-plist
	put-in-indentations-and-widths?
	&optional text-tail-past-text-segment?)
  (loop with word-spacing = (default-word-spacing text-box-format)
	with x-magnification? = (x-magnification? text-cell-plist text-box-format)
	with width-of-longest-line-so-far = 0
	with indentation = 0
	with line-width?
	with indentation? = nil			; for next line
	as l = text-segment then next-l
	as next-l = (cdr l)
	as text-element = (car l)
	do (cond
	     ((text-line-p text-element)
	      (let ((line-width
		      (or line-width?
			  (let ((unmagnified-line-width
				  (+w indentation
				      (compute-width-of-text-line
					text-element nil nil
					(text-cell-font-map text-box-format)
					word-spacing))))
			    (if x-magnification?
				(magnify unmagnified-line-width x-magnification?)
				unmagnified-line-width)))))
		(if (>f line-width width-of-longest-line-so-far)
		    (setq width-of-longest-line-so-far line-width))
		(cond
		  (line-width?
		   (setq line-width? nil))
		  (put-in-indentations-and-widths?
		   (setf (cdr l) (slot-value-cons text-element (cdr l)))
		   (setf (car l) (slot-value-cons 'line-width line-width)))))
	      (cond
		(indentation?
		 (setq indentation? nil))
		(put-in-indentations-and-widths?
		 (setf (cdr l) (slot-value-cons (car l) (cdr l)))
		 (setf (car l) indentation))))
	     ((fixnump text-element)
	      (setq indentation (setq indentation? text-element)))
	     ((consp text-element)
	      (case (car text-element)
		(line-width
		 (setq line-width? (cdr text-element)))
		(word-spacing
		 (setq word-spacing (cdr text-element))))))
	until (or (null next-l)
		  (eq next-l text-tail-past-text-segment?))
	finally
	  (return width-of-longest-line-so-far)))


;; At present, this is used only by format-text.  Look for other places to use it!

;; Consider calling this "compute-width-of-text".



;;; `Compute-height-for-text' ... includes the top and bottom margins in its
;;; result.  It returns the sum of the top and bottom margins if the text cell
;;; has no text.  `Compute-height-for-text-without-margins' does the same but
;;; does not include the margins; it returns 0 if the text cell has no text.

(defun-simple compute-height-for-text (text text-box-format text-cell-plist)
  (+w (text-cell-top-margin text-box-format)
      (compute-height-for-text-without-margins
	text text-box-format text-cell-plist)
      (text-cell-bottom-margin text-box-format)))

(defun-simple compute-height-for-text-without-margins
    (text text-box-format text-cell-plist)
  (loop with y-magnification?
	  = (or (if text-cell-plist		; optimization
		    (getfq text-cell-plist 'y-magnification))
		(text-cell-y-magnification? text-box-format))
	with line-height = (text-cell-line-height text-box-format)
	with line-spacing = (text-cell-line-spacing text-box-format)
	with height-of-text-so-far = 0
	with first-line? = t
	as text-element in text
	do (cond
	     ((text-line-p text-element)
	      (setq height-of-text-so-far
		    (+w height-of-text-so-far
			(if first-line? line-height (+w line-height line-spacing))))
	      (setq first-line? nil))
	     ((and (not (atom text-element)) (eq (car text-element) 'leading))
	      (setq height-of-text-so-far
		    (+w height-of-text-so-far (cdr text-element)))))
	finally
	  (return
	    (if y-magnification?
		(magnify height-of-text-so-far y-magnification?)
		height-of-text-so-far))))

;; Consider defining this as a macro.



;;; `Get-extent-of-text-string-after-formatting' formats text-string and returns
;;; the resulting width and height.  It does NOT reclaim its text-string
;;; argument.

(defun get-extent-of-text-string-after-formatting
    (text-string text-cell-format text-cell-plist format-width-override?)
  (let ((text (convert-text-string-to-text
		(copy-text-string text-string))))
    (get-extent-of-text-after-formatting
      text text-cell-format text-cell-plist format-width-override?)))



;;; `Get-extent-of-text-after-formatting' formats text, reclaims it,
;;; and returns as values the width and the height of the resulting
;;; formatted text.

(defun get-extent-of-text-after-formatting
    (text text-cell-format text-cell-plist format-width-override?)
  (get-extent-of-text
    text text-cell-format text-cell-plist
    format-width-override? nil))



;;; `Get-extent-of-formatted-text' assumes text has already been formatted, and
;;; just reclaims its text argument returns its width and the height.

(defun get-extent-of-formatted-text
    (text text-cell-format text-cell-plist format-width-override?)
  (get-extent-of-text
    text text-cell-format text-cell-plist
    format-width-override? t))


;;; `Get-extent-of-text' reclaims its text argument and returns as its two
;;; values the width and the height of text, formatted according to
;;; text-cell-format and text-cell-plist.
;;;
;;; If do-not-reformat-text? is true, then text is assumed to have already been
;;; fully formatted according to these parameters.  Otherwise, text is formated
;;; according to these parameters.  Then, the width and height of that text is
;;; returned.

(defun get-extent-of-text
    (text text-cell-format text-cell-plist
	  format-width-override? do-not-reformat-text?)
  (multiple-value-bind (formatted-text width)
      (format-text
	text text-cell-format text-cell-plist
	nil do-not-reformat-text?
	nil nil nil nil nil format-width-override? nil)
    (let ((height
	    (compute-height-for-text-without-margins
	      formatted-text text-cell-format text-cell-plist)))
      ;; Text is reclaimed by calling format-text, and reclaiming the
      ;; formatted-text is all that remains to do.
      (reclaim-text formatted-text)
      (values width height))))





;;;; Truncating Strings to Fit



;;; `Truncate-string-as-necessary-to-fit' returns either: (a) a text-string copy
;;; of string and its width, if string is no wider than maximum-width; (b) anew
;;; text string and width corresponding to the longest non-empty prefix
;;; substring of string which, when suffixed by truncated-string-suffix?, is no
;;; wider than maximum-width; or (c) nil if neither (a) nor (b) is possible.
;;; String must consist entirely of unicode characters.  The width of string is
;;; its unmagnified workspace (normalized-scale) width for the specified font
;;; map and word spacing.  Word-spacing may be arbitrary if there are no spaces
;;; in string or truncated-string-suffix?.  Truncated-string-suffix? must be a
;;; string of gensym characters or nil.

;;; Here, string refers to a text string (a wide string), which is also the type
;;; of the result.

(defun truncate-string-as-necessary-to-fit
       (string maximum-width font-map word-spacing truncated-string-suffix?)
  (let ((width-of-string
	  (compute-width-of-text-line string nil nil font-map word-spacing)))
    (if (<=w width-of-string maximum-width)
	(values (copy-text-string string) width-of-string)
	(loop with text-x-a
	      with text-x-b
	      with width-so-far
	      initially
		(set-text-x
		  text-x-a text-x-b 0)
		(if truncated-string-suffix?
		    (incf-text-x
		      text-x-a text-x-b
		      (compute-width-of-text-line
			truncated-string-suffix? nil nil font-map word-spacing t)))
	      as i = 0 then next-i
	      as next-i = i
	      do (setq width-so-far (text-x-to-x text-x-a text-x-b))
		 (incff next-i)
		 (incf-text-x
		   text-x-a text-x-b
		   (compute-width-of-text-line
		     string i next-i font-map word-spacing t))
	      until (>w (text-x-to-x text-x-a text-x-b) maximum-width)
	      finally
		(return
		  (if (>f i 0)
		      (let ((new-string
			      (obtain-text-string 
				(if truncated-string-suffix?
				    (+f i (text-string-length truncated-string-suffix?))
				    i))))
			(copy-portion-of-wide-string-into-wide-string
			  string 0 i new-string 0)
			(if truncated-string-suffix?
			    (copy-portion-of-wide-string-into-wide-string			      
			      truncated-string-suffix?
			      0 (text-string-length truncated-string-suffix?)
			      new-string i))
			(values new-string width-so-far))))))))

;; This is not coded for maximum speed in the truncated-string case.









;;;; Operations on Text Boxes



;;; `Reformat-text-box-in-place' ... does nothing if there is no text or text
;;; box format.  It does not enlarge the workspace text-box is on, since
;;; text-box may well be shifted before being redrawn.  This assumes that
;;; text-box is not currently drawn.

;;; If do-not-reformat-text? is non-nil, the text in the text box is not
;;; reformatted.

;;; Text-box is returned as the first value.  Also, if cursor-line-index? and
;;; cursor- character-index? are specified, revised values for them are returned
;;; as second and third values.

;;; Text regions are deleted from a text box that is to be reformatted, because
;;; it would be unduly difficult to update them correctly.

;;; ... also [as of 6/6/91 -mhd] enlarges the workspace text-box is on, if any,
;;; if necessary.

(defun reformat-text-box-in-place
    (text-box
      &optional put-in-indentations-and-widths? do-not-reformat-text?
      cursor-line-index? cursor-character-index?
      do-not-enlarge-workspace?)
  (when (has-subblocks-p text-box)
    (delete-any-text-regions text-box))
  (let ((text-box-format (text-box-format text-box))
	(text? (cdr (box-translation-and-text text-box))))
    (when (and text?			; necessary???
	       text-box-format)		; why necessary?!
      (multiple-value-bind
	  (formatted-text width-of-longest-line
			  new-cursor-line-index? new-cursor-character-index?)
	  (format-text
	    text? text-box-format
	    (text-cell-plist-for-text-box text-box)
	    nil
	    do-not-reformat-text? nil put-in-indentations-and-widths? nil
	    cursor-line-index? cursor-character-index?
	    (minimum-width-of-text-box text-box))
	(setf (cdr (box-translation-and-text text-box)) formatted-text)
	;; Bind a new size pinning the size to the text-cell and text-box
	;; min and max widths.
	(let ((new-right? nil)
	      (new-bottom? nil))

	  (macrolet (;; I didn't need this.  - ben 6/24/94
		     (maximum-width-for-text-cell? (x) (declare (ignore x)) nil))
	    (let* ((new-width-for-text-cell
		     (let ((new-width-for-text-cell-1
			     (maxw
			       (minimum-width-for-text-cell text-box-format)
			       (+w (text-cell-left-margin text-box-format)
				   width-of-longest-line
				   (text-cell-right-margin text-box-format)))))
		       (if (maximum-width-for-text-cell? text-box-format)
			   (maxw (maximum-width-for-text-cell? text-box-format)
				 new-width-for-text-cell-1)
			   new-width-for-text-cell-1)))
		   (new-width-for-text-box
		     (let ((new-width-for-text-box-1
			     (maxw
			       (minimum-width-of-text-box text-box)
			       (+w
				 (text-box-left-border-width text-box-format)
				 new-width-for-text-cell
				 (text-box-right-border-width text-box-format)))))
		       (if (maximum-width-of-text-box? text-box)
			   (minw (maximum-width-of-text-box? text-box)
				 new-width-for-text-box-1)
			   new-width-for-text-box-1))))
	      (setq new-right? (+w (left-edge-of-block text-box) new-width-for-text-box))))
	  
	  (let* ((top-edge-of-block
		   (top-edge-of-block text-box))
		 (minimum-height-of-text-box
		   (minimum-height-of-text-box text-box))
		 (maximum-height-of-text-box
		   (maximum-height-of-text-box text-box))
		 (text-box-top-border-width
		   (text-box-top-border-width text-box-format))
		 (minimum-height-for-text-cell
		   (minimum-height-for-text-cell
		     text-box-format))
		 (height-for-text
		   (compute-height-for-text
		     formatted-text text-box-format
		     (text-cell-plist-for-text-box text-box)))
		 (text-box-bottom-border-width
		   (text-box-bottom-border-width text-box-format)))	    

	    ;; NOTE: none of the above bindings are really necessary, but I
	    ;; put them in at AC's urging because, without them, the VAX/VMS
	    ;; C Compiler seemed to choke on the C code that this translated
	    ;; into.  (MHD 5/1/91)

	    (setq new-bottom?
		  (+w top-edge-of-block
		      (pin-in-range
			minimum-height-of-text-box
			(+w
			  text-box-top-border-width
			  (maxw
			    minimum-height-for-text-cell	; (MHD 11/9/88)
			    height-for-text)	; result includes margins
			  text-box-bottom-border-width)
			maximum-height-of-text-box))))

	  (change-edges-of-block text-box nil nil new-right? new-bottom?)
	  (unless do-not-enlarge-workspace?
	    (enlarge-workspace-for-block-rectangle-if-necessary text-box nil))
	  (values text-box new-cursor-line-index? new-cursor-character-index?))))))

;; Changed width-for-cell? arg provided to format-text to be
;; minimum-width-of-text-box.  Previously, this slot could only be used to
;; affect the width of the text box, but never the text within it.  Now, it
;; causes the text to fill the width of the box as much as possible, up to a
;; maximum given by maximum-format-width-for-text-cell.
;; 
;; To make this really a worthwhile feature -- and users have been demanding
;; this for some time! -- we should go and change the defaults for
;; maximum-format-width- for-text-cell on most text cell formats, where it is
;; usually equal to the minimum-format-width-for-text-cell.  And we should also
;; change the change-size dialog to not allow enlarging beyond
;; maximum-format-width-for-text-cell, so that users do not feel "betrayed".
;;
;; Even once we change the default maximum-format-width-for-text-cell, that
;; change will not be noticed unless users load their KB with "bringing formats
;; up-to-date".  To get around this, we could automatically decide to update at
;; least this slot where it has been left as the default.  Alternatively, we
;; could just advertise that this problem has been solved, but that users must
;; load their KBs "bringing formats up-to-date" in order for it to take effect
;; in existing KBs.
;;
;; A lot of users insist it was a "bug" for it not to have worked this way all
;; along.  In light of that prevalent belief, we need not even change the
;; change- size dialog; that way, users will feel that we have just (finally)
;; fixed a bug.
;;
;; TO DO:
;;

;; - Fix formats to have nice large values for
;;   maximum-format-width-for-text-cell.
;;   -- DONE in BOXES. Most have 1000 as the maximum width; should it be bigger?
;;   (MHD 3/18/91)
;;
;;   - Remove prototype attempts to fix this problem another way in the
;;   change-size dialog (involving changing format frames) -- this was a dead
;;   end.
;;   -- DONE. (MHD 3/18/91)
;;
;; - Fix change-size dialog to show the maximum-format-width-for-text-cell limit
;;   if it is reached.
;;
;; - Make sure this works for user-defined message subclasses.
;;
;; - What about limiting the width -- what if users want a message to be no
;;   wider than a certain limit.  Users want this frequently for the message
;;   board, and the kludge that implements it is horrible, wrong, and a bug, and
;;   just wrong.
;; -- See note below. (MHD 3/18/91)
;;
;; - What about the width of procedures as viewed in tables?
;;
;; - What about the width of edit boxes?
;;
;; - What about the fact that these slots are lookup slots -- probably not a big
;;   deal.  But it would be about 4 times faster with a form like
;;      (or (get-exceptional-slot-value text-box 'minimum-width-of-text-box)
;;          0)
;;   if we implement that abstraction.  (See notes on that topic in
;;   "ma:>mhd>slots.lisp")
;;
;; (MHD 3/18/91)
;;
;; - Also fix change-size dialog to show the minimum width that is allowed.
;;   This was done, but is wrong. FIX!
;;   
;; - Consider adding maximum-width-for-text-box(?) slots.  (Default to
;;   "infinite" if no "?" or to nil if "?".)  This would allow the box to shrink
;;   to smaller than the minimum in the format.
;;
;; - Do something about the annoying feature that you cannot just set the the
;;   minimum width, only the minimum width AND height.
;;
;; (MHD 3/18/91)

;; Consider having this take text and text-box-format arguments.

;; Unkludge kludge for type-in text boxes for 1.2! (MHD 11/9/88)



;;; `Update-border-of-text-box' takes a text box and four new edges, these
;;; may be nil.  It will erase and redraw the borders.  If more than one
;;; edge changes then update area will cover the union of the old and new
;;; edges.  Otherwise only the band between the old and new edge positions
;;; are updated.

(defun update-border-of-text-box
    (text-box new-left-edge? new-top-edge? new-right-edge? new-bottom-edge?)
  (let* ((text-box-format (text-box-format text-box))
	 (number-of-edges-changing
	   (let ((count 0))
	     (when new-left-edge? (incff count))
	     (when new-top-edge? (incff count))
	     (when new-right-edge? (incff count))
	     (when new-bottom-edge? (incff count))
	     count)))
    (unless (=f 0 number-of-edges-changing)
      (let* ((old-left-edge (left-edge-of-block text-box))
	     (old-top-edge (top-edge-of-block text-box))
	     (old-right-edge (right-edge-of-block text-box))
	     (old-bottom-edge (bottom-edge-of-block text-box))
	     
	     (new-left-edge (or new-left-edge? old-left-edge))
	     (new-top-edge (or new-top-edge? old-top-edge))
	     (new-right-edge (or new-right-edge? old-right-edge))
	     (new-bottom-edge (or new-bottom-edge? old-bottom-edge))
	     
	     ;; First approximation to update area, is union of old and new.
	     (left-edge-of-update-area (minw new-left-edge old-left-edge))
	     (top-edge-of-update-area (minw new-top-edge old-top-edge))
	     (right-edge-of-update-area (maxw new-right-edge old-right-edge))
	     (bottom-edge-of-update-area (maxw new-bottom-edge old-bottom-edge)))

	;; Refine that default if we are only moving one edge.
	;;	#+ignore
	(when (=f 1 number-of-edges-changing)
	  (cond
	    (new-right-edge?
	     (setf left-edge-of-update-area
		   (-w (minw (right-edge-of-block text-box) new-right-edge?)
		       (text-box-right-border-width text-box-format))))
	    (new-bottom-edge?
	     (setf top-edge-of-update-area
		   (-w (minw (bottom-edge-of-block text-box) new-bottom-edge?)
		       (text-box-bottom-border-width text-box-format))))
	    (new-left-edge?
	     (setf right-edge-of-update-area
		   (+w (maxw (left-edge-of-block text-box) new-left-edge?)
		       (text-box-left-border-width text-box-format))))
	    (new-top-edge?
	     (setf bottom-edge-of-update-area
		   (+w (maxw (top-edge-of-block text-box) new-top-edge?)
		       (text-box-top-border-width text-box-format))))))

	(update-images-of-border-of-text-box
	  text-box t
	  left-edge-of-update-area top-edge-of-update-area
	  right-edge-of-update-area bottom-edge-of-update-area)

	;; Move the text-region subblocks
	(loop for subblock being each subblock of text-box doing
	  (when (frame-of-class-p subblock 'text-region)
	    (change-edges-of-block
	      subblock
	      (if new-left-edge?
		  (+w (left-edge-of-block subblock)
		      (-w new-left-edge? (left-edge-of-block text-box))))
	      (if new-top-edge?
		  (+w (top-edge-of-block subblock)
		      (-w new-top-edge? (top-edge-of-block text-box))))
	      (if new-right-edge?
		  (+w (right-edge-of-block subblock)
		      (-w new-right-edge? (right-edge-of-block text-box))))
	      (if new-bottom-edge?
		  (+w (bottom-edge-of-block subblock)
		      (-w new-bottom-edge? (bottom-edge-of-block text-box)))))))

	(change-edges-of-block text-box
			       new-left-edge? new-top-edge?
			       new-right-edge? new-bottom-edge?)

	;; We got turds in XOR mode here if enlarging the workspace caused
	;; part of the text-box border to be drawn.  Work around that bug
	;; by turning off document drawing here.  In paint mode, the
	;; fact that these are all idempotent invals saves us.
	;; -fmw, 5/22/95
	(let ((current-draw-document-p
		(if (xor-mode-p) nil current-draw-document-p)))
	  (enlarge-workspace-for-block-rectangle-if-necessary text-box nil))

	(update-images-of-border-of-text-box
	  text-box nil
	  left-edge-of-update-area top-edge-of-update-area
	  right-edge-of-update-area bottom-edge-of-update-area)
	))))



(defun update-images-of-border-of-text-box
       (text-box erase?
	left-edge-of-update-area? top-edge-of-update-area?
	right-edge-of-update-area? bottom-edge-of-update-area?)
  (update-images
    erase? text-box text-box
    (or left-edge-of-update-area? (left-edge-of-block text-box))
    (or top-edge-of-update-area? (top-edge-of-block text-box))
    (or right-edge-of-update-area? (right-edge-of-block text-box))
    (or bottom-edge-of-update-area? (bottom-edge-of-block text-box))
    :bleeding-on-all-sides
    'draw-or-change-color-of-text-box
    text-box
    'draw-only-borders					    ; Special case.
    nil nil nil nil))

;; In the deep past a comment here reported that we needed to extend the update
;; area by two pixels.  That should no longer be true.  If it is true then the
;; caller should be fixed.  - ben 6/23/93

;; This maybe called on just the one edge's border and that maybe so thin it
;; scales into zero width the bleeding hack must not be supressed.   - ben 6/23/93

;; Consider having this try to minimize redrawing when there is more than one new edge.

;; Currently, text-box borders update improperly at scales less than 1. -fmw, 6/9/94





;;; `Incomplete-box-translation-and-text-p' is true iff text-box is incomplete,
;;; and presumably should not be allowed to exist other than transiently on a KB
;;; workspace.
;;;
;;; For a free text, this is true if the text is completely empty ("") or it's
;;; ellipsis string ("...").
;;;
;;; For a non-free text, this is true if the text is the ellipsis string ("...").
;;;
;;; Note that this is never an invalid state. G2 must be able to deal with
;;; them. KBs may even be saved with text boxes in this state, but such text
;;; boxes are generally considered a nuisance, and so are deleted if they have
;;; been left around with no editing pending for them, e.g., at the end of an
;;; editing session.

(defun incomplete-box-translation-and-text-p (text-box)
  (let ((text (cdr (box-translation-and-text text-box))))
    (cond
      ((free-text-slot-type-p
	 (feature-assq
	   'type
	   (slot-features
	     (get-slot-description-of-frame
	       'box-translation-and-text text-box))))
       (or (text-incomplete-p text)
	   (text-empty-p text)))
      (t
       (text-incomplete-p text)))))





;;;; Text-box and text-cell colors


(defparameter default-text-cell-background-color 'transparent)

;; This is a parameter just for documentation.  There's no plan to ever change
;; the default.


(defun-substitution-macro compute-text-cell-background-color
    (text-cell-plist text-cell-format table? ignore-state-of-highlighting)
  (or (if text-cell-plist
	  (or (and (null ignore-state-of-highlighting)
		   (getfq text-cell-plist 'highlight-color))
	      (getfq text-cell-plist 'background-color)))

      (text-cell-background-color? text-cell-format)
      (if table? (table-background-color table?))

      ;; Changed the default to transparent.  This is the same as background in
      ;; XOR mode, and does the right thing in paint mode.
      default-text-cell-background-color))


(defun-substitution-macro compute-text-cell-line-color
    (text-cell-plist text-cell-format table)
  table
  (or (if text-cell-plist
	  (getfq text-cell-plist 'line-color))
      (text-cell-line-color? text-cell-format)
;      (table-line-color table)
      'foreground))


(defun-substitution-macro compute-text-cell-border-color
    (text-cell-plist text-cell-format table)
  table
  (or (if text-cell-plist
	  (getfq text-cell-plist 'border-color))
      (text-box-border-color? text-cell-format)
      'foreground))



;;; Text-box versions


(def-substitution-macro text-box-background-color (text-box)
  (compute-text-cell-background-color (text-cell-plist-for-text-box text-box)
				      (text-box-format text-box)
				      nil
				      nil))

(def-substitution-macro text-box-background-color-ignoring-highlighting
    (text-box)
  (compute-text-cell-background-color (text-cell-plist-for-text-box text-box)
				      (text-box-format text-box)
				      nil
				      t))

(def-substitution-macro text-box-line-color (text-box)
  (compute-text-cell-line-color (text-cell-plist-for-text-box text-box)
				(text-box-format text-box)
				nil))

(def-substitution-macro text-box-border-color (text-box)
  (compute-text-cell-border-color (text-cell-plist-for-text-box text-box)
				  (text-box-format text-box)
				  nil))



;;;; Change color functions




;;; `Highlight-or-unhighlight-text-box' highlights or unhighlights text-box, per
;;; unhighlight-case?.

;;; If highlight-color? is nil, the color or metacolor used is the the line-color
;;; property of the text cell plist for text-box, if that is non-nil, or else the
;;; value of the text-cell-line-color? slot of the text box format of text-box, if
;;; that is non-nil, or else FOREGROUND.  Highlight-color? is ignored in the
;;; unhighlight case.

;;; If text-region-class? is specified, highlighting means highlighting the entire
;;; text as a text region of this class; otherwise, highlighting means highlighting
;;; the text box by changing its highlight color (in a way that makes the text come
;;; out in a false color, with FOREGROUND causing foreground/background color
;;; reversal).

;;; This returns nil only in two cases: (1) in the highlight case when text-box is
;;; already highlighted as specified, and (2) in the unhighlight case when text-box
;;; is not highlighted (which could occur, for example, when a new name box is
;;; created within the editor).

(defun highlight-or-unhighlight-text-box
    (text-box highlight-color? unhighlight-case?
	      &optional text-region-class?)
  (let ((highlight-color
	  (or highlight-color?
	      (text-box-line-color text-box))))

    (cond (text-region-class?
	   (loop for subblock being each subblock of text-box
		 when (frame-of-class-p subblock text-region-class?)
		   do (cond
			(unhighlight-case?
			 (delete-frame subblock)
			 (return t))
			((eq (get-slot-value	; forward reference
			       subblock 'text-highlight-bar-color)
			     highlight-color)
			 (return nil))
			(t
			 (delete-frame subblock)
			 (loop-finish)))
		 finally
		   (when (not unhighlight-case?)
		     (return (make-text-region
			       text-box nil 1 0 'end nil nil text-region-class?)))))
	  (t
	   (let ((old-highlight-color?
		   (getf (text-cell-plist-for-text-box text-box) 'highlight-color)))
	     (when (if unhighlight-case?
		       old-highlight-color?
		       (not (eq old-highlight-color? highlight-color)))
	       (change-color-of-text-box
		 text-box nil 
		 (if (not unhighlight-case?) highlight-color)
		 :no-change :no-change
		 'highlight)))))))

;; Cf: highlight-or-unhighlight-text-cell

;; This is a bit slower than before.

;; This might need work in the nested highlight case.





;;; `with-text-color-different-from-background' ensures that the
;;; text-cell-line-color? in the current-text-box-format has a color-value
;;; different from background-color-value?. If these color values are the same
;;; then it will choose a color opposite of the background color in the
;;; map-to-black-or-white scheme. This is used, for example, to ensure that the
;;; highlight color for text in new-tables is different from the background
;;; color.
;;; Furthermore, background-color-value is overloaded with boolean semantics,
;;; i.e. if it is nil then the text-color is left as is and the entire macro is
;;; a wrapper that does nothing.

#+unused
(defmacro with-text-color-different-from-background (background-color-value? &body body)

  (avoiding-variable-capture (&aux old-text-color alter-text-color-p
				   new-text-color background-color-value-var?)
    
    `(let* ((,background-color-value-var? ,background-color-value?)
	    (,old-text-color
	       (or (text-cell-line-color? current-text-box-format)
		   'black))
	    (,alter-text-color-p
	       (and ,background-color-value-var?
		    (=f ,background-color-value-var?
			(map-color-or-metacolor-to-color-value ,old-text-color))))
	    (,new-text-color
	       (and ,alter-text-color-p
		    (if (eq 'white (map-to-black-or-white ,old-text-color))
			'black
			'white))))
       (#+development unwind-protect #-development progn 
		      (progn (when ,alter-text-color-p
			       (setf (text-cell-line-color? current-text-box-format) ,new-text-color))
			     ,@body)
		      (when ,alter-text-color-p
			(setf (text-cell-line-color? current-text-box-format) ,old-text-color))))))




;;; The defparameter `scheduled-text-highlighting' controls whether we allow
;;; text highlighting to be merged away by scheduled drawing.  If T, then we
;;; allow it.  If NIL, then we force all highlighting transitions to be
;;; visible.

(defparameter scheduled-text-highlighting t)


;;; The function `change-color-of-text-box' tries to incrementally update the
;;; text-box color.  When new-text-color? is nil, the original text color (as
;;; specified in the text box format) is implied.  When new-text-color? is
;;; :no-change, no change is done at all.  The analagous convention holds for
;;; new-border-color? and new-background-color?.

;;; Whenever color-change-case? is HIGHLIGHT, note-as-kb-state-change? should
;;; always be nil, and new-background-color? should never be :no-change.

;; See the parallel function change-color-of-text-cell in module TABLES.

(defun change-color-of-text-box
    (text-box note-as-kb-state-change?
	      new-background-color? new-border-color? new-text-color? 
	      &optional (color-change-case? t))
  (let* ((do-not-note-permanent-changes-p note-as-kb-state-change?)
	 (workspace? (get-workspace-if-any text-box))
	 (text-box-format (text-box-format text-box))

	 (old-background-color
	   (text-box-background-color text-box))

	 (new-background-color
	   (cond ((eq color-change-case? 'highlight)
		  new-background-color?)
		 ((eq new-background-color? :no-change)
		  nil)
		 (t
		  (or new-background-color?
		      ;; Now we need the text-format background color, so why does
		      ;; the first clause check the plist?
		      (getf (text-cell-plist-for-text-box text-box) 'highlight-color)
		      (text-cell-background-color? text-box-format)

		      ;; We need the color BACKGROUND (meaning the workspace background color)
		      ;; so that the transparency checks work.  Text-cells are strange in that
		      ;; a background color of BACKGROUND really means transparent.
		      ;; This fixes HQ-195440 "Messages not painted properly on reset (paint mode)"
		      ;; -fmw, 2/21/95
		      ;; BACKGROUND now means opaque.
		      default-text-cell-background-color))))

	 (new-background-color-really
	   ;; This is the truely non-NIL new background color.  We need to know
	   ;; what it is in order to see whether it is transparent.
	   (or new-background-color
	       (cond ((eq color-change-case? 'highlight)
		      (text-box-background-color-ignoring-highlighting text-box))
		     ((eq new-background-color? :no-change)
		      old-background-color))))

	 ;; Doesn't look at the text-cell-plist!
	 (old-border-color
	   (text-box-border-color text-box))
	 (new-border-color
	   (if (neq new-border-color? :no-change)
	       (or new-border-color?
		   (text-box-border-color? text-box-format)
		   (if workspace?
		       (workspace-foreground-color? workspace?))
		   'black)))

	 (old-text-color
	   (text-box-line-color text-box))
	 (new-text-color
	   (if (neq new-text-color? :no-change)
	       (or new-text-color?
		   (text-cell-line-color? text-box-format)
		   (if workspace?
		       (workspace-foreground-color? workspace?))
		   'black)))
	 (becoming-transparent?				    ; Note A
	   (or (and (neq new-background-color? :no-change)
		    (neq new-background-color old-background-color)
		    (transparent-color-p new-background-color-really))
	       (and (neq new-border-color? :no-change)
		    (neq new-border-color old-border-color)
		    (transparent-color-p new-border-color))
	       (and (neq new-text-color? :no-change)
		    (neq new-text-color old-text-color)
		    (transparent-color-p new-text-color)))))

    (macrolet ((kb-update ()
		 `(cond
		    ((eq color-change-case? 'highlight)
		     (change-text-box-property
		       text-box 'highlight-color new-background-color?))
		    (t
		     (when note-as-kb-state-change?
		       (note-kb-state-change text-box 'text-box-color-pattern))
		     (when new-background-color
		       (change-text-box-property
			 text-box 'background-color new-background-color?))
		     (when new-border-color
		       (change-text-box-property
			 text-box 'border-color new-border-color?))
		     (when new-text-color
		       (change-text-box-property
			 text-box 'line-color new-text-color?))))))

      (cond ((and (appropriate-to-invalidate-color-of-block? text-box becoming-transparent?)
		  (or scheduled-text-highlighting
		      (neq color-change-case? 'highlight)))
	     ;; Perhaps we should fall thru to do-color-revision in the
	     ;; highlight case, ie, (eq color-change-case? 'highlight), so that
	     ;; the flashes of changed regions don't get merged away?

	     (kb-update)
	     (when workspace?
	       (let ((changed-regions
		       (nconc
			 (if (neq new-background-color? :no-change)
			     (gensym-list 'background))
			 (if (neq new-text-color? :no-change)
			     (gensym-list 'text))
			 (if (neq new-border-color? :no-change)
			     (gensym-list 'border)))))
		 (invalidate-color-of-block workspace? text-box changed-regions)
		 (reclaim-gensym-list changed-regions))))
	    (t
	     (do-color-revision (text-box becoming-transparent?)
		 (draw-or-change-color-of-text-box
		   text-box nil color-change-case?
		   new-background-color new-text-color new-border-color)
	       (kb-update)))))))

;; Note A: Unfortunately, some new-xxx-color might be NIL, meaning that the
;; actual color is computed deep down in the guts of
;; draw-or-change-color-in-text-cell-for-block, so we have to compute
;; new-background-color-really to get the actual new color.
;; It's a mess.  -fmw, 8/29/94

;; We no longer treat BACKGROUND and TRANSPARENT the same for text cell background.
;; BACKGROUND means an opaque background with the same color as the workspace
;; background.  TRANSPARENT means transparent. -fmw, 5/22/95

;; Note that if a rule (or any other text box) has a workspace?, it is assumed to
;; be fully conforming to the requirements for drawing: e.g. a rule that is an
;; action button embedded rule should have not workspace? and so it is alright
;; for it not to have a text box format, etc.  Any rule on a workspace must have
;; all the normal things this and other text draw methods require.  This might
;; not be obvious. (MHD 8/18/89)

;; Extensively revised for new color functionality.  LH should go over.
;; (MHD 7/21/89)

;; Have "new-background-color?" be "new-background-color-or-no-change?" and have
;; "new-background-color" be "new-background-color?", etc!

;; Consider setting the relevant property to nil in the case where both
;;   (a) it would be given the same value as in the text box format; and
;;   (b) note-as-kb-state-change? is nil. (MHD)

;; Note that the interpretation given to :no-change and nil in this function
;; is unique.  Consider having the same interpretation in draw-or-change-
;; color-of-text-box.  Then the logic above could be simpler, and one wouldn't
;; need to encode the defaulting hierarchy separately here; also, that may
;; even need to be done as part of unkludging WHITE and BLACK above! (MHD)





;;; The function `draw-selected-regions-of-text-box' is used by the drawing
;;; task refresh-colors-of-block.

(defun draw-selected-regions-of-text-box (text-box changed-regions)
  (let* ((background-color
	   (text-box-background-color text-box))
	 (border-color					    ; Doesn't look at the text-cell-plist!
	   (text-box-border-color text-box))
	 (text-color
	   (text-box-line-color text-box)))

    (draw-or-change-color-of-text-box
      text-box nil
      'selective-redraw
      (if (memq-macro 'background changed-regions)
	  background-color)
      (if (or (memq-macro 'background changed-regions)	    ; Drawing bg => must draw text.
	      (memq-macro 'text changed-regions))
	  text-color)
      (if (memq-macro 'border changed-regions)
	  border-color))))



;;; The function `draw-selected-regions-of-block' is called from
;;; refresh-color-of-block to redraw only those regions mentioned.  For
;;; connections, we have to punt and draw all of the regions, I think.

(defun draw-selected-regions-of-block (block regions)
  (cond ((connection-frame-p block)
	 (draw-connection (connection-for-this-connection-frame block) nil))
	((text-box-p block)
	 (draw-selected-regions-of-text-box block regions))
	(t
	 (draw-selected-regions-of-icon block regions))))




;;;; Drawing Text


;;; `New-draw-text', a macro, is the primary interface between block draw
;;; methods and the rendering of text.  It takes these arguments:
;;;   text   -- the formatted text to render onto the screen.
;;;   text-cell-plist 
;;;          -- variations on the text format
;;;   {right,top,left,bottom}-edge-of-cell-in-window
;;;          -- the bounds of the formatted text.

;;; New-draw-text must be called with these dynamic extents established:
;;; on-image-plane, for-image-plane, on-window, and for-workstation.  
;;; In addition these these globals must be bound:
;;;   current-text-box-format -- to set the style for the text.
;;;   current-foreground-color-value -- to set the color of the text.
;;;   current-background-color-value -- so color differencing logic works.
;;; The behavor of this routine is also effected by the bindings of
;;;   erase-instead?
;;;   changing-colors-of-graphic-elements?

;;; The draw area as established by {left,top,right,bottom}-edge-of-draw-area
;;; should be as minimal as possible.  It is often the case that draw-area is
;;; smaller than the edges of cell in window due to occlusion or scrolling.  At some
;;; future date we might provide an interface, for scrolling, that allows the
;;; caller to provide a hint were the first visible line in the text occurs.

;;; Prior to calling new-draw-text the text should have been formatted relative
;;; to the current-text-box-format and the edges of the cell in window.  This is
;;; often done when the block is updated, since usually at that time a fresh
;;; text value is derived as necessary from any underlying data.  See
;;; `format-text' and `reformat-text' for more information.

;;; When G2 is utilizing graphic element memory a pointer to the text will be
;;; retained in graphic element memory until it is erased.  Therefore the text
;;; must be stored in the block being rendered.  During this interval the text
;;; maybe drawn many times, on many image-planes, in many colors.  But it must
;;; always be rendered in the same text box format, and with the same cell region.

;;; Supressing of details is entirely the responsiblity of the caller.

;;; The color of the text is independent of the current-text-box-format.  It is
;;; the responsiblity of the caller to select the approprate color given the
;;; current highlighting, text box format, text-cell-plist, or what ever. and to bind
;;; current-foreground-color-value to reflect choice.  If the text cell has a
;;; background color it is the caller's responsiblity to render that prior to
;;; calling new-draw-text and to rebind current-background-color-value to
;;; reflect that color.

;;; The scaling of the text is also the responsiblity of the caller, i.e. he should
;;; rebind current-{x,y}-scale-of-image-plane approprately if necessary.

(defmacro new-draw-text (text 
			  left-edge-of-cell-in-window
			  top-edge-of-cell-in-window
			  right-edge-of-cell-in-window
			  bottom-edge-of-cell-in-window)
  `(draw-text-segment-1
     ,text nil 
     0   ;; unmagnified-distance-of-text-segment-from-top
     ,left-edge-of-cell-in-window ,top-edge-of-cell-in-window
     ,right-edge-of-cell-in-window ,bottom-edge-of-cell-in-window))


(defmacro draw-text
    (text left-edge-of-cell-in-window top-edge-of-cell-in-window
	  right-edge-of-cell-in-window bottom-edge-of-cell-in-window)
  `(new-draw-text 
     ,text ,left-edge-of-cell-in-window ,top-edge-of-cell-in-window
     ,right-edge-of-cell-in-window ,bottom-edge-of-cell-in-window))

(defun draw-text-function
    (text left-edge-of-cell-in-window top-edge-of-cell-in-window
	  right-edge-of-cell-in-window bottom-edge-of-cell-in-window)
  (draw-text text left-edge-of-cell-in-window top-edge-of-cell-in-window
	     right-edge-of-cell-in-window bottom-edge-of-cell-in-window))
      
  



;;; `New-draw-text-segment', a macro, will draw only a portion of a text in the manner
;;; of new-draw-text.  Start-of-text-segment and end-of-text-segment?, the first two
;;; arguments, delimit subsequence of a full text.  The final four arguments specify the
;;; text cell within which the text lies.  The third argument specified where in this
;;; text cell the text-segment starts.

;;; The text segment must begin and end on a text line.

;;; All the comments and rules about new-draw-text apply to new-draw-text-segment.

;;; The function is used in senarios where the text currently on the screen must be
;;; revised only partially.  One example is typing, another is optimizations that
;;; supress excessive drawing when the user revising a text under program control.

(defmacro new-draw-text-segment (start-of-text-segment end-of-text-segment?
			      vertical-offset
			      left-edge-of-cell-in-window top-edge-of-cell-in-window
			      right-edge-of-cell-in-window bottom-edge-of-cell-in-window)
  `(draw-text-segment-1
     ,start-of-text-segment ,end-of-text-segment?
     ,vertical-offset   ;; unmagnified-distance-of-text-segment-from-top
     ,left-edge-of-cell-in-window ,top-edge-of-cell-in-window
     ,right-edge-of-cell-in-window ,bottom-edge-of-cell-in-window))



;;; `Draw-text-segment-1' renders a segment of text.  It is the work horse of
;;; text drawing, but it is never called directly by the block draw methods,
;;; they use new-draw-text to draw an entire piece of text and
;;; new-draw-text-segment to do incremental revisions to text.  It bridges the
;;; gap between the TEXT data type draw-line-of-text operation.

;;; Draw-text-segment is invoked within the for-image-plane context and the text
;;; is drawn in conformance with the specifications recorded in the
;;; current-text-box-format current-image-plane-{x,y}-scale, and the
;;; current-{fore,back}ground-color-value.

;;; The routine takes 7 arguments.  The last four (i.e.  {left, top, right,
;;; bottom}-edge-of-cell-in-window specify the bounds within which the text is
;;; to be formatted.  The first two arguments (i.e.  text-segment and
;;; text-tail-past-test-segment?) are delimit the text segment.  The third
;;; argument unmagnified-distance-of-text-segment-from-top is self documenting.

;;; This routine sweeps over the elements of the text segment noting the formating
;;; effect of each element and calling draw-text-line on each text-string.

;;; Draw-text-line will enforce the clipping required by image-plane and opaque
;;; block occlusion.  The caller will usually have drawn in the draw area to the
;;; block bounds.  The caller may restrict the draw area to avoid flicker making
;;; incremental changes to text.  For example to change: "Now is the time." to
;;; "Now is the moment." He may want to move left edge of the draw area to just
;;; after "the ".

;; - ben 11/02/92

(defun-void draw-text-segment-1
       (text-segment text-tail-past-text-segment?
	unmagnified-distance-of-text-segment-from-top
	left-edge-of-cell-in-window top-edge-of-cell-in-window
	right-edge-of-cell-in-window bottom-edge-of-cell-in-window)
  (loop ;; Eliminated text-box-format arg. - ben 2/25/93
        with text-box-format = current-text-box-format
	with text-cell-plist = current-text-cell-plist
	with x-magnification? = (x-magnification? text-cell-plist text-box-format)
	with y-magnification? = (y-magnification? text-cell-plist text-box-format)
	with x-scale = current-image-x-scale
	with y-scale = current-image-y-scale
	with magnified-x-scale
	  = (if x-magnification? (magnify x-scale x-magnification?) x-scale)
	with magnified-y-scale
	  = (if y-magnification? (magnify y-scale y-magnification?) y-scale)
	with font-map = (text-cell-font-map text-box-format)
	with line-spacing = (text-cell-line-spacing text-box-format)
	with line-height = (text-cell-line-height text-box-format)
	with baseline-position = (text-cell-baseline-position text-box-format)
	with left-edge-of-text-in-window
	  = (+r left-edge-of-cell-in-window
		(delta-x-in-window
		  (text-cell-left-margin text-box-format) x-scale))
	with left-edge-for-lines-in-window
	  = left-edge-of-text-in-window
	with top-edge-of-text-in-window
	  = (+r top-edge-of-cell-in-window
		(delta-y-in-window
		  (text-cell-top-margin text-box-format) y-scale))
	with distance-to-next-baseline-from-top
	  = (+w unmagnified-distance-of-text-segment-from-top baseline-position)
	with baseline-to-baseline-distance
	  = (+w line-height line-spacing)
	with extra-diacritic-height
	  = (text-cell-extra-diacritic-height text-box-format)
	with extra-diacritic-height-in-window
	  = (delta-y-in-window extra-diacritic-height magnified-y-scale)
	with extent-above-baseline-in-window	; includes half of line-spacing
	  = (delta-y-in-window (+w (halfw line-spacing) baseline-position) magnified-y-scale)
	with extent-below-baseline-in-window	; includes half of line-spacing
	  = (-w (delta-y-in-window baseline-to-baseline-distance magnified-y-scale)
		extent-above-baseline-in-window)
	  ;; fixed bug in the above expression: it had been doubly scaling
	  ;; subjecting the result to yet another delta-y-in-window -- this
	  ;; led to chopping off of descenders at smaller scales, such as the
	  ;; with the "g" in "Merge KB" in the Main Menu at scale 1895
	  ;; (three control-s's). (MHD 6/3/93)
	with word-spacing
	  = (default-word-spacing text-box-format)
	with word-spacing-for-next-line? = nil
	with baseline-in-window
	until (eq text-segment text-tail-past-text-segment?)
	as text-element = (pop text-segment)	; changes argument
	do (cond
	     ((text-line-p text-element)
	      (setq baseline-in-window
		    (+r top-edge-of-text-in-window
			(delta-y-in-window
			  distance-to-next-baseline-from-top magnified-y-scale)))
	      ;; (if (>r (+r baseline-in-window extent-below-baseline-in-window)
	      ;;         top-edge-of-draw-area)
	      ;;     (draw-line-of-text ...))  ; poss. optimiz.
	      (draw-line-of-text-handling-tabs
		left-edge-of-cell-in-window
		(maxr (-r baseline-in-window
			  extent-above-baseline-in-window
			  extra-diacritic-height-in-window)
		      top-edge-of-cell-in-window)	; necessary?
		right-edge-of-cell-in-window
		(minr (+r baseline-in-window extent-below-baseline-in-window)
		      bottom-edge-of-cell-in-window)	; necessary?
		text-element
		(or word-spacing-for-next-line? word-spacing)
		font-map
		;; Eliminated text-color-difference arg. - ben 2/25/93
		;; text-color-difference
		(color-difference current-foreground-color-value ; ***
				  current-background-color-value)
		magnified-x-scale magnified-y-scale
		left-edge-for-lines-in-window baseline-in-window)
	      (when (>r (+r baseline-in-window extent-below-baseline-in-window)
			   bottom-edge-of-draw-area)
		(loop-finish))		; assumes next line does not intrude
	      (setq distance-to-next-baseline-from-top
		    (+w distance-to-next-baseline-from-top
			baseline-to-baseline-distance))
	      (setq word-spacing-for-next-line? nil))
	     ((fixnump text-element)
	      (setq left-edge-for-lines-in-window
		    (+r left-edge-of-text-in-window
			(delta-x-in-window text-element magnified-x-scale))))
	     ((symbolp text-element))
	     ((eq (car text-element) 'leading)
	      (setq distance-to-next-baseline-from-top
		    (+w distance-to-next-baseline-from-top (cdr text-element))))
	     ((eq (car text-element) 'word-spacing)
	      (setq word-spacing-for-next-line? (cdr text-element))))))

;; Note A: the extra height above adds about 25% extra headroom. It is
;; especially needed for Thai, which stacks diacritics 2 levels above. The same
;; amount extra is used in add-or-update-text-highlight-bar. (MHD 12/19/03)


;; I observe that is called only by new-draw-text, new-draw-text-segment.  
;; - ben 2/25/92








;;;; Drawing Text Boxes



;;; The draw method for a text box draws borders, background, text lines, edit cursors,
;;; text regions, and (in old kbs only) name boxes ...

(def-class-method draw (text-box)
;  (unless (maybe-defer-refreshing-image-plane current-image-plane))  ; Hmm..
  (draw-or-change-color-of-text-box text-box nil nil nil nil nil))




;;; `Draw-or-change-color-of-text-box' is responsible for some rendering of a
;;; text box.  It is called both by the draw method for the block and by the
;;; code that does incremental color changes to the block.  Incremental updates
;;; to the text only are done by update-text-in-edit-box (sic).

;; Cf draw-or-change-color-in-table.

(defun-void draw-or-change-color-of-text-box (text-box 
					  suppress-details? ; Either NIL or DRAW-ONLY-BORDERS
					  color-change-case?
					  highlight-or-new-background-color?
					  new-text-color?
					  new-border-color?)
  (let* (;; Pick apart the text-box
	 (text-box-format (text-box-format text-box))
	 (text-cell-plist (text-cell-plist-for-text-box text-box))
	 (text (cdr (box-translation-and-text text-box)))
	 
	 (ordinary-color-change?
	   (memq-p-macro color-change-case? '(t highlight)))

	 ;; Compute the color of the border that is recorded in the cell.
	 (cell-border-color
	   (text-box-border-color text-box))

	 ;; Compute what's on the screen at this moment: in the color-change case
	 ;; the border is there now.  Otherwise, the workspace background is
	 ;; there now.
	 (existing-border-color
	   (if ordinary-color-change?
	       cell-border-color
	       'background))

	 ;; Compute what we want for a border when we are done.
	 (final-border-color
	   (if (and ordinary-color-change? new-border-color?)
	       new-border-color?
	       cell-border-color))
	 
	 ;; We need to get the text value for a special case 
	 ;; when dragging things with invisible borders.
	 (cell-text-color
	   (text-box-line-color text-box))

	 ;; Now worry about the dimensions of all this.
	 ;; Binding {left,top,right,bottom}-border-width
	 ;;         {left,top,right,bottom}-edge-of-{cell,text-box}-in-window
	 (left-border-width
	   (text-box-left-border-width text-box-format))
	 (top-border-width
	   (text-box-top-border-width text-box-format))
	 (right-border-width
	   (text-box-right-border-width text-box-format))
	 (bottom-border-width
	   (text-box-bottom-border-width text-box-format))
	 
	 ;; Take note of some special cases where
	 (suppress-text-drawing?
	   (or suppress-details?
	       (scale-too-small-for-details-p
		 current-image-x-scale current-image-y-scale)
	       (text-too-small-to-draw-p
		 text-box-format text-cell-plist
		 current-image-x-scale current-image-y-scale)
	       (and (block-is-currently-being-dragged-p text-box)
		    (not (frame-of-class-p text-box 'name-box)))))
	 (force-hairline-border?
	   (and suppress-text-drawing?
		(neq suppress-details? 'draw-only-borders)	; see UPDATE note
							    ;  above. (MHD 12/15/92)
		(and (=w left-border-width 0)		    ; interacts complexly
		     (=w top-border-width 0)		    ;  with overriding-
		     (=w right-border-width 0)		    ;  border-color-difference,
		     (=w bottom-border-width 0))	    ; q.v., below
		(not (frame-of-class-p text-box 'edit-box))
		(or (null (superblock? text-box))	    ; abstract part of this?
		    (workspace-p (superblock? text-box))
		    (block-is-currently-being-dragged-p text-box)
		    (and				    ; maybe not?
		      (not (block-inside-p text-box (superblock? text-box)))
		      (loop for superblock? = (superblock? text-box)
					    then (superblock? superblock?)
			    while superblock?
			    thereis 
			    (block-is-currently-being-dragged-p superblock?))))))

	 (left-edge-of-text-box-in-window
	   (x-in-window (left-edge-of-block text-box)))
	 (top-edge-of-text-box-in-window
	   (y-in-window (top-edge-of-block text-box)))
	 (right-edge-of-text-box-in-window
	   (x-in-window (right-edge-of-block text-box)))
	 (bottom-edge-of-text-box-in-window
	   (y-in-window (bottom-edge-of-block text-box)))
	 (frame-transform?
	   (and (frame-transforms-of-block text-box)
		(cdr
		  (assq current-image-plane
			(frame-transforms-of-block text-box)))))
	 (left-edge-of-cell-in-window
	   (+r left-edge-of-text-box-in-window
	       (cond
		 ((>w left-border-width 0)
		  (maxr (delta-x-in-window left-border-width current-image-x-scale)
			1))
		 (force-hairline-border? 1)
		 (t 0))))
	 (top-edge-of-cell-in-window
	   (+r top-edge-of-text-box-in-window
	       (cond
		 ((>w top-border-width 0)
		  (maxr (delta-y-in-window top-border-width current-image-y-scale)
			1))
		 (force-hairline-border? 1)
		 (t 0))))
	 (right-edge-of-cell-in-window
	   (if frame-transform?  ;; See Note A
	       right-edge-of-draw-area
	       (-r right-edge-of-text-box-in-window
		   (cond
		     ((>w right-border-width 0)
		      (maxr (delta-x-in-window right-border-width current-image-x-scale)
			    1))
		     (force-hairline-border? 1)
		     (t 0)))))
	 (bottom-edge-of-cell-in-window
	   (if frame-transform?  ;; See Note A
	       bottom-edge-of-draw-area
	       (-r bottom-edge-of-text-box-in-window
		   (cond
		     ((>w bottom-border-width 0)
		      (maxr (delta-y-in-window
			      bottom-border-width current-image-y-scale)
			    1))
		     (force-hairline-border? 1)
		     (t 0)))))
	 
	 ;; Some junk that enables us to use the drawing routine.
	 (image-x-scale-of-table current-image-x-scale)
	 (image-y-scale-of-table current-image-y-scale)

	 (unmagnified-width-of-text-to-draw-beyond? nil))
        
    ;; Draw the cell and it's background.
    (draw-or-change-color-in-text-cell-for-block
      text-box 
      image-x-scale-of-table
      image-y-scale-of-table
      
      color-change-case?
      new-text-color?
      suppress-details?
      highlight-or-new-background-color?
      unmagnified-width-of-text-to-draw-beyond?
      
      text
      text-box-format
      text-cell-plist
      
      left-edge-of-cell-in-window
      top-edge-of-cell-in-window
      right-edge-of-cell-in-window
      bottom-edge-of-cell-in-window)
    

    ;; Draw the border

    ;; We override the border color in some situations.  If the user would get
    ;; lost, because we are not drawing text, and because it is invisible then
    ;; we turn it on.  Note we will already have forced it to be hairline.  But
    ;; don't force anything if we are being called just to draw the borders.
    
    (when (and suppress-text-drawing?
	       (neq suppress-details? 'draw-only-borders)
	       (or (memq final-border-color '(transparent background))
		   (=f current-background-color-value
		       (map-color-or-metacolor-to-color-value final-border-color))))
      (setf final-border-color cell-text-color))

    ;; This "unless" is not really working. I think that the border is
    ;; frequently drawn unnecessarily.

    (unless (or (eq existing-border-color final-border-color)
		;; As an aside; text Boxes with frames do not have borders since
		;; the border is around the entire cell, not the block and it
		;; looks odd to scroll that.
		(and (eq color-change-case? 'selective-redraw) ; -fmw, 12/28/94
		     (null new-border-color?)))

      (let ((border-color-difference
	      (metacolor-difference final-border-color existing-border-color))
	    (existing-border-color-value
	      (map-color-or-metacolor-to-color-value existing-border-color)))

	(with-drawing-trace (text #+ignore text-box)
	  (format t "Drawing borders for ~s in ~s~%" text-box final-border-color))
	
	(with-background-color-value existing-border-color-value
	  (unless (=r top-edge-of-cell-in-window
		      top-edge-of-text-box-in-window)
	    (draw-solid-rectangle			; top border, if any
	      left-edge-of-text-box-in-window top-edge-of-text-box-in-window
	      right-edge-of-text-box-in-window top-edge-of-cell-in-window
	      border-color-difference))
	  (unless (=r bottom-edge-of-cell-in-window
		      bottom-edge-of-text-box-in-window)
	    (draw-solid-rectangle			; bottom border, if any
	      left-edge-of-text-box-in-window bottom-edge-of-cell-in-window
	      right-edge-of-text-box-in-window bottom-edge-of-text-box-in-window
	      border-color-difference))
	  (unless (=r left-edge-of-cell-in-window
		      left-edge-of-text-box-in-window)
	    (draw-solid-rectangle			; left border, if any
	      left-edge-of-text-box-in-window top-edge-of-cell-in-window
	      left-edge-of-cell-in-window bottom-edge-of-cell-in-window
	      border-color-difference))
	  (unless (=r bottom-edge-of-cell-in-window
		      bottom-edge-of-text-box-in-window)
	    (draw-solid-rectangle			; right border, if any
	      right-edge-of-cell-in-window top-edge-of-cell-in-window
	      right-edge-of-text-box-in-window bottom-edge-of-cell-in-window
	      border-color-difference)))))))

;; Note A: The bottom and right edge of the cell is used to clip the drawing and hence
;; terminate it.  In olden days  the text was inside of the bounds
;; of the block.  With scrolling the edge of the text can be far south or eastward of
;; the enclosing block.  What we want here is edges of the draw area.
;; Note there is an analagous case in draw-text-segment-in-text-box and
;; in update-text-in-edit-box.




;;; `Draw-text-segment-in-text-box' render a segment of text from a text-box
;;; by calling new-draw-text-segment after computing the text cell bounds and
;;; binding current-text-box-format and the current color values appropriately.
;;; It is called with in for-image-plane, usually by update-images.

;;; We presume that the text cell's background has already been rendered.  It
;;; is not called as part of highlighting, or color changing, but only as part
;;; of changing the text.

(defun-simple draw-text-segment-in-text-box
    (text-segment
      text-tail-past-text-segment?
      unmagnified-distance-of-text-segment-from-top
      text-box)
  (let* ((current-text-box-format (text-box-format text-box))
	 (current-text-cell-plist (text-cell-plist-for-text-box text-box))

	 (frame-transform? (and (frame-transforms-of-block text-box)
				(cdr
				  (assq current-image-plane
					(frame-transforms-of-block text-box)))))

	 ;; Bind Text Cell Edges.
	 (left-edge-of-cell-in-window
	   (let ((left-border-width
		   (text-box-left-border-width current-text-box-format))
		 (left-edge-of-text-box-in-window
		   (x-in-window (left-edge-of-block text-box))))
	     (+r left-edge-of-text-box-in-window
		 (if (=w left-border-width 0)
		     0
		     (maxr			; minimum 1
		       1 (delta-x-in-window left-border-width current-image-x-scale))))))
	 (top-edge-of-cell-in-window
	   (let ((top-border-width
		   (text-box-top-border-width current-text-box-format))
		 (top-edge-of-text-box-in-window
		   (y-in-window (top-edge-of-block text-box))))
	     
	     (+r top-edge-of-text-box-in-window
		 (if (=w top-border-width 0)
		     0
		     (maxr			; minimum 1
		       1 (delta-y-in-window top-border-width current-image-y-scale))))))
	 (right-edge-of-cell-in-window
	   (if frame-transform?  ;; See Note A on draw-or-change-color-of-text-box
	       right-edge-of-draw-area
	       (let ((right-border-width
		       (text-box-right-border-width current-text-box-format))
		     (right-edge-of-text-box-in-window
		       (x-in-window (right-edge-of-block text-box))))
		 (-r right-edge-of-text-box-in-window
		     (if (=w right-border-width 0)
			 0
			 (maxr ; minimum 1
			   1
			   (delta-x-in-window right-border-width current-image-x-scale)))))))
	 (bottom-edge-of-cell-in-window
	   (if frame-transform?  ;; See Note A on draw-or-change-color-of-text-box
	       bottom-edge-of-draw-area
	       (let ((bottom-edge-of-text-box-in-window
		       (y-in-window (bottom-edge-of-block text-box)))
		     (bottom-border-width		; only used nearby
		       (text-box-bottom-border-width current-text-box-format)))
		 (-r bottom-edge-of-text-box-in-window
		     (if (=w bottom-border-width 0)
			 0
			 (maxr ; minimum 1
			   1
			   (delta-y-in-window bottom-border-width current-image-y-scale)))))))
	 
	 ;; Bind up fore and background color, unhighlighted.
	 (desired-current-background-color-value
	   (let ((text-cell-background-color?
		   (or (if current-text-cell-plist
			   (getfq current-text-cell-plist
				  'background-color))
		       (text-cell-background-color?
			 current-text-box-format))))
	     (if text-cell-background-color?
		 (map-color-or-metacolor-to-color-value
		   text-cell-background-color?)
		 current-background-color-value)))
	 (current-foreground-color-value
	   (let ((text-cell-line-color?
		   (or (if current-text-cell-plist
			   (getfq current-text-cell-plist 'line-color))
		       (text-cell-line-color? current-text-box-format))))
	     (if text-cell-line-color?
		 (map-color-or-metacolor-to-color-value text-cell-line-color?)
		 current-foreground-color-value))))
    
    (when (getfq current-text-cell-plist 'highlight-color)
      (macrolet ((swap (a b) `(let ((temp ,a)) (setf ,a ,b) (setf ,b temp))))
	(swap desired-current-background-color-value current-foreground-color-value)))
    (with-background-color-value desired-current-background-color-value
      (unless (or (scale-too-small-for-details-p
		    current-image-x-scale current-image-y-scale)
		  (text-too-small-to-draw-p
		    current-text-box-format current-text-cell-plist
		    current-image-x-scale current-image-y-scale)
		  (block-is-currently-being-dragged-p text-box)
		  (and				; maybe not?
		    (not (block-inside-p text-box (superblock? text-box)))
		    (loop for superblock? = (superblock? text-box)
					  then (superblock? superblock?)
			  while superblock?
			  thereis 
			  (block-is-currently-being-dragged-p superblock?))))
	(new-draw-text-segment 
	  text-segment text-tail-past-text-segment?
	  unmagnified-distance-of-text-segment-from-top
	  left-edge-of-cell-in-window top-edge-of-cell-in-window
	  right-edge-of-cell-in-window bottom-edge-of-cell-in-window))))
  nil)







;;;; Text Box Scrolling


;;; `Scroll-frame-transform-of-text-box' calls thru to scroll-frame-transform.
;;; It limits the scrolling to assure the text remains in sight.

(defun scroll-frame-transform-of-text-box (text-box frame-transform dx dy)
  (let* ((text-cell-interline-distance
	   (let ((text-box-format (text-box-format text-box)))
	     (+w (text-cell-line-spacing text-box-format)
		 (text-cell-line-height text-box-format))))
	 (existing-y-offset
	   (top-edge-of-source-of-frame-transform frame-transform))
	 (requested-y-offset
	   (+w existing-y-offset dy))
	 (minimum-y-offset
	   (-f 
	     (*f text-cell-interline-distance
		 (find-end-of-text (cdr (box-translation-and-text text-box)) 0)))) ;; ugh
	 (maximum-y-offset 0)
	 (actual-dy
	   (-w
	     (maxw minimum-y-offset
		   (minw maximum-y-offset
			 requested-y-offset))
	     existing-y-offset)))
    (unless (and (=w 0 dx)
		 (=w 0 actual-dy))
      (scroll-frame-transform frame-transform dx actual-dy)
      (synch-elevator-position-to-frame-transform frame-transform)
      )))

;; Not limiting on the horizontal at this time.



;;; The `scroll-block method on text-box' calls thru to scroll-frame-transform.
;;; It maps the amount-of-step and direction-of-step into a delta x and y in
;;; workspace units.  The text-box-format is used to compute a meaing for
;;; the amount-of-step 'line, and the content-area of the block is used to
;;; get a meaning for page.

(def-class-method scroll-block
    (text-box image-plane amount-of-step direction-of-step)
  (let* ((sign (case direction-of-step
		 ((down right) -1)
		 (t +1)))
	 (horizontal-p (case direction-of-step
			 ((left right) t)
			 (otherwise nil))) ; (up down)
	 (text-cell-interline-distance
	   (let ((text-box-format (text-box-format text-box)))
	     (+w (text-cell-line-spacing text-box-format)
		 (text-cell-line-height text-box-format))))
	 (frame-transform?
	   (find-frame-transform-if-any text-box image-plane))
	 (workspace-units-to-move
	   (*f sign
	       (case amount-of-step
		 (line
		  (if horizontal-p 30 text-cell-interline-distance))
		 (page
		  (if horizontal-p
		      ;; Horz: the exact width of the block.
		      (-f (right-edge-of-block text-box)
			  (left-edge-of-block text-box))
		      ;; Vert: N-1 lines, where N fits in a page.
		      (*f text-cell-interline-distance
			  (-f (truncatef (-f (bottom-edge-of-block text-box)
					     (top-edge-of-block text-box))
					 text-cell-interline-distance)
			      1))))
		 (t 0))))
	 (dx (if horizontal-p workspace-units-to-move 0))
	 (dy (if horizontal-p 0 workspace-units-to-move)))
    (when frame-transform?
      (scroll-frame-transform-of-text-box
	text-box
	frame-transform?
	dx dy))))

;; Not actually tested on all kinds of text-boxes, known only to work on
;; edit-boxes, and then only those in the editor.

(defun scroll-line-index-to-top (frame-transform line-index)
   (let* ((text-box (block-of-frame-transform frame-transform))
	  (text-cell-interline-distance
	    (let ((text-box-format (text-box-format text-box)))
	      (+w (text-cell-line-spacing text-box-format)
		  (text-cell-line-height text-box-format))))
	  (goal-offset
	    (-w (*w (-f line-index 1) text-cell-interline-distance))))
     (scroll-frame-transform-of-text-box
       text-box
       frame-transform
       0
       (-w goal-offset
	   (top-edge-of-source-of-frame-transform frame-transform)))))

#+junk
(defun f1 (i)
  (scroll-line-index-to-top bah-ft i)
  (force-process-drawing))

#+junk
(defun f2 (i)
  (scroll-text-into-view bah-ft i 0)
  (force-process-drawing))


;;; `Suppress-scroll-text-into-view' is intended to be used by savvy text editor
;;; code that changes the cursor position in a scrolling edit box and wants to
;;; control any scrolling that would normally result from such a change itself,
;;; presumably by bringing the text into view by itself.
;;;
;;; This macro creates a dynamic extent around body, during which the low-level
;;; routine for scrolling text into view after a change in the edit box will
;;; just do nothing.
;;;
;;; This is used thus far only by the code that handles the commands for page-up
;;; and page-down (scrolling a screenful at a time).

(defvar suppress-scrolling-into-view-global-flag? nil)

(defmacro suppress-scroll-text-into-view (&body body)
  `(let ((suppress-scrolling-into-view-global-flag? t))
     . ,body))



;;; `Scroll-text-into-view' ... does nothing if called within a during a
;;; suppress-scroll-text-into-view dynamic extent.

(defun scroll-text-into-view (frame-transform line-index character-index)
  (when suppress-scrolling-into-view-global-flag?
    (return-from scroll-text-into-view 'suppressed))
  (let* ((text-box (block-of-frame-transform frame-transform)))
    (multiple-value-bind (new-line-index new-character-index new-text-tail x-in-workspace y-in-workspace)
	(find-position-in-text text-box
			       nil nil nil ; text-cell? and it's edges
			       nil ;; look-in-lost-spaces-too?
			       nil nil ;; x-in-workspace? y-in-workspace?
			       line-index character-index
			       (cdr (box-translation-and-text text-box)) ;; text-tail?
			       ;; only-if-in-text? find-character-instead-of-position-between?
			       )
      (declare (ignore new-text-tail new-line-index new-character-index))
      (let* ((text-box-format (text-box-format text-box))
	     (baseline-to-baseline-distance ; baseline-to-baseline-distance
	       (+w (text-cell-line-spacing text-box-format)
		   (text-cell-line-height text-box-format)))
	     (number-of-lines-of-padding 3)
	     (x-offset-in-cell-of-mark
	       (- x-in-workspace
		  (left-edge-of-block text-box)
		  (text-box-left-border-width text-box-format)
		  (text-cell-left-margin text-box-format)))
	     (y-offset-in-cell-of-mark
	       (- y-in-workspace
		  (top-edge-of-block text-box)
		  (text-box-top-border-width text-box-format)
		  (text-cell-top-margin text-box-format)
		  (text-cell-baseline-position text-box-format)))
	     (delta-to-bring-to-top
	       (-w (+w y-offset-in-cell-of-mark
		       (top-edge-of-source-of-frame-transform frame-transform))))
	     (delta-to-bring-to-left
	       (-w (+w x-offset-in-cell-of-mark
		       (left-edge-of-source-of-frame-transform frame-transform))))
	     (width-of-view-area (-w (right-edge-of-block text-box)
				     (left-edge-of-block text-box)))
	     (height-of-view-area (-w (bottom-edge-of-block text-box)
				      (top-edge-of-block text-box)))
	     (vertical-padding-if-we-scroll
	       (*w number-of-lines-of-padding baseline-to-baseline-distance))
	     (horizontal-padding-if-we-scroll
	       (minf (truncatef width-of-view-area 5)
		     (*f (text-width-to-x (default-word-spacing text-box-format)) 3)))
	     (actual-x-delta 0)
	     (actual-y-delta 0))
	;; Consider the Vertical.
	(cond
	  ;; Off the bottom
	  ((<w (+w delta-to-bring-to-top height-of-view-area)
	       baseline-to-baseline-distance)
	   (setf actual-y-delta 
		 (+w delta-to-bring-to-top
		     height-of-view-area
		     (-w vertical-padding-if-we-scroll))))
	  ;; Off the top
	  ((<w 0 delta-to-bring-to-top)
	   (setf actual-y-delta
		 (+w delta-to-bring-to-top
		     (*w baseline-to-baseline-distance
			 (minw line-index
			       number-of-lines-of-padding))))))
	;; Consider the Horizontal.
	; (format t "~&:x-window: ~S ~S ~S" 0 (- delta-to-bring-to-left) width-of-view-area)
	(cond
	  ;; Off the right.
	  ((<w (-w width-of-view-area (text-cell-left-margin text-box-format))
	       (-w delta-to-bring-to-left))
	   (setf actual-x-delta 
		 (+w delta-to-bring-to-left
		     width-of-view-area
		     (-w horizontal-padding-if-we-scroll))))
	  ;; Off the left
	  ((<w (-w delta-to-bring-to-left)
	       (text-cell-left-margin text-box-format))
	   (setf actual-x-delta
		 (+w delta-to-bring-to-left
		     horizontal-padding-if-we-scroll))
	   ;; Guard to pin down left edge.
	   (when (<f 0 (+f actual-x-delta
			   (left-edge-of-source-of-frame-transform frame-transform)))
	     (setf actual-x-delta (-f (left-edge-of-source-of-frame-transform frame-transform))))))
	(unless (and (=w 0 actual-x-delta)
		     (=w 0 actual-y-delta))
	  ; (format t "~&delta: ~S ~S" actual-x-delta actual-y-delta)
	  (scroll-frame-transform-of-text-box
	    text-box
	    frame-transform actual-x-delta actual-y-delta))))))


;;; `Delta-position-of-block-scroll' is called to request the updating
;;; of frame content display for the current settings of the positions
;;; of the block's elevator.  The image-plane to effect, as well as
;;; the amout by which these were just changed are passed in.

(defun delta-position-of-block-scroll (text-box
					image-plane
					horizontal-delta
					vertical-delta)
  (declare (ignore horizontal-delta))
  (unless (zerop vertical-delta)
    (let* ((frame-transform
	     (find-frame-transform-if-any text-box image-plane))
	   (number-of-lines-in-text-box
	     (find-end-of-text
	       (cdr (box-translation-and-text text-box)) 0))
	   (line-number (scalef (position-of-vertical-elevator text-box)
				number-of-lines-in-text-box)))
      (scroll-line-index-to-top frame-transform line-number))))

;; This should be a method on all blocks, but only edit-boxes are currently
;; scrolled so punt.


;;; `Synch-elevator-position-to-frame-transform' is called when ever the
;;; frame transform is revised.  Just after the view has been updated.
;;; View may have been revised directly or as a side effect of dragging
;;; the elevator, but in either case once the block has decided how to
;;; actually implement the scrolling the elevator position must be
;;; revisited.

(defun synch-elevator-position-to-frame-transform (frame-transform)
  (let* ((text-box (block-of-frame-transform frame-transform))
	 (number-of-lines-in-text-box
	   (find-end-of-text
	     (cdr (box-translation-and-text text-box)) 0))
	 (text-cell-interline-distance
	   (let ((text-box-format (text-box-format text-box)))
	     (+w (text-cell-line-spacing text-box-format)
		 (text-cell-line-height text-box-format))))
	 (current-vertical-offset
	   (-f (top-edge-of-source-of-frame-transform frame-transform)))
	 (line-number-of-top-most-line
	   (roundw current-vertical-offset
		   text-cell-interline-distance))
	 (new-vertical-position-of-elevator
	   (if (=f 0 number-of-lines-in-text-box)
	       0
	       (with-temporary-gensym-float-creation compute-scale
		 (truncate
		   (*e (coerce-fixnum-to-gensym-float #.(normalized-scale))
		       (/e (coerce-fixnum-to-gensym-float
			     line-number-of-top-most-line)
			   (coerce-fixnum-to-gensym-float
			     number-of-lines-in-text-box))))))))
    (unless (=f new-vertical-position-of-elevator
		(position-of-vertical-elevator text-box))
      (move-elevator
	text-box
	(position-of-horizontal-elevator text-box)
	new-vertical-position-of-elevator))))

;; This should be a method on all blocks, but only edit-boxes are currently
;; scrolled so punt.





;;;; Subordinate Text Boxes



;;; A `subordinate text box' is a text box that is used as a subblock of a non-workspace
;;; block, except in the case of a workspace-name-box.

(def-class (subordinate-text-box text-box))	; no instances either!



;;; A `label box' is a text box that is used as a subblock of a block to "label" it.

(def-class (label-box subordinate-text-box)

  (default-text-box-format-name label-box-format)

  (menu-items ((move) (delete) (edit))))	; allow hide?


;;; Label boxes and name boxes have different menus in facilities, so they
;;; get different spots. -fmw, 12/2/93

(def-spot label-box-spot
    :slots nil
    :include text-box-spot
    :enclosing-spot-type image-plane-spot		    ; Correct?
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented label-box)

(def-class-method generate-spot (label-box mouse-pointer)
  (generate-text-box-spot label-box mouse-pointer (make-label-box-spot)))

(defun label-box-p (thing)
  (and (framep thing) (frame-of-class-p thing 'label-box)))



;;; A `name box' is a text box that is primarily used as a subblock of a block to show
;;; the name or names of the block (the value of its name-or-names-for-frame slot).  See
;;; change-slot-value.

(def-class (name-box (exported-system-item subordinate-text-box) not-user-instantiable)

  (default-text-box-format-name name-box-format)

  (menu-items ((move) (delete "hide name") (edit)) no-accessor))



(def-system-variable allow-activation-of-name-boxes-p boxes nil)

(def-class-method activate-if-possible-and-propagate (name-box)
  (when allow-activation-of-name-boxes-p
    (funcall-superior-method name-box)))

(def-spot name-box-spot
    :slots nil
    :include text-box-spot
    :enclosing-spot-type image-plane-spot		    ; Correct?
    :innermost-spot-p t
    :abstract-type nil
    :type-of-frame-represented name-box)

(def-class-method generate-spot (name-box mouse-pointer)
  (generate-text-box-spot name-box mouse-pointer (make-name-box-spot)))

(defun name-box-p (thing)
  (and (framep thing) (frame-of-class-p thing 'name-box)))



(def-class (workspace-name-box name-box not-user-instantiable)

  (default-text-box-format-name workspace-name-box-format))

;; To save space in a knowledge base, a name box could be represented just by its positon,
;; provided that, for all purposes of drawing, picking, menu posting, etc., it behaved
;; exactly as if the name box frame were actually present.



(def-text-box-format label-box-format
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 0
  text-cell-font-map (hm18)
  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0

  ;; Labels in KBs created prior to 6/16/89 (2.0) had 12, 9, 12,
  ;;   and 8 (the default for a dialog box format) for the
  ;;   following four items, respectively.  These exactly center
  ;;   the baseline and ascender height with respect to the bottom
  ;;   and top block edges, which looks right.  (MHD 6/16/89)
  ;; Tried 12, 11, 12, 6
  ;; Now trying 9, 6, 6, 2 (MHD 6/29/89)

  ;; Labels in KBs loaded (or saved) after 8/??/89 were changed from
  ;;   class button-label to class label-box, and their formats were
  ;;   changed to label-box-format from button-label-format.  [TO
  ;;   BE DONE.] (MHD 8/14/89)

  text-cell-left-margin 9
  text-cell-top-margin 6
  text-cell-right-margin 6
  text-cell-bottom-margin 2)

(def-text-box-format name-box-format
;  text-cell-font-map (hm14)
;  text-cell-line-height 20		; experiment with these!
;  text-cell-baseline-position 15
;  default-word-spacing #.(convert-to-text-width 8)
;  minimum-word-spacing #.(convert-to-text-width 4)
;  maximum-word-spacing #.(convert-to-text-width 18)
  text-cell-left-margin 12
  text-cell-top-margin 9
  text-cell-right-margin 12
  text-cell-bottom-margin 8
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 24
  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0)

(def-text-box-format workspace-name-box-format
  text-cell-font-map (hm18)
;  text-cell-line-height 20		; experiment with these!
;  text-cell-baseline-position 15
;  default-word-spacing #.(convert-to-text-width 8)
;  minimum-word-spacing #.(convert-to-text-width 4)
;  maximum-word-spacing #.(convert-to-text-width 18)
  text-cell-background-color? black
  text-cell-line-color? white
  text-cell-left-margin 11
  text-cell-top-margin 11
  text-cell-right-margin 11
  text-cell-bottom-margin 6
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 24
  text-box-left-border-width 0			; consider having a border of 4, taken
  text-box-top-border-width 0			;   from the margin, so that a highlighted
  text-box-right-border-width 0			;   workspace name box will show a border
  text-box-bottom-border-width 0)





;; ;;; `Make-subordinate-text-box' makes a new, empty text box of class class as a subblock
;; ;;; of superblock.  (The empty text box gets filled in by update-name-box.)
;; 
;; ;;; The placement of the new empty text box is determined by ...  Place? may
;; ;;; be :center, :left, ....  When place? is nil in the name-box case, an attempt is made
;; ;;; to place the new name box so as to avoid connections.  The order of preference is:
;; ;;; bottom, top, right, bottom right.
;; 
;; (defun make-subordinate-text-box (class superblock place?)
;;   class superblock place?
;;   )
;; 
;; Implement this! Abstract portions of the following to use for other types of text
;; boxes, e.g., edit boxes and readouts, and then eliminate the following!




;;; `Make-name-box' ...

(defun make-name-box (superblock &optional positioning-spec?)
  (let* ((workspace-case		; if a workspace name box
	   (frame-of-class-p superblock 'workspace))
	 (name-box
	   (make-frame
	     (if workspace-case
		 'workspace-name-box
		 'name-box)))
	 (name-box-format
	   (get-or-make-format-frame
	     (default-text-box-format-name name-box)))
	 (height-for-name-box			; use compute-height-for-text?
	   (+w (text-box-top-border-width name-box-format)
	       (text-cell-top-margin name-box-format)
	       (text-cell-line-height name-box-format)
	       (text-cell-bottom-margin name-box-format)
	       (text-box-bottom-border-width name-box-format))))
    (setf (bottom-edge-of-block name-box) height-for-name-box)	; width remains 0
    (setf (text-box-format name-box) name-box-format)
    (if workspace-case
	;; Then:  (Superblock is a workspace.)
	(let* ((workspace-margin (workspace-margin superblock))
	       (left-edge-for-name-box
		 (+w (left-edge-of-block superblock) workspace-margin))
	       ;; Width, right edge unknowable still (unfortunately).
	       (top-edge-for-name-box		; these are just proposed still
		 (+w (top-edge-of-block superblock) workspace-margin))
	       (bottom-edge-for-name-box
		 (+w top-edge-for-name-box height-for-name-box)))
	  (shift-block
	    name-box
	    left-edge-for-name-box
	    ;; Use existing inside top edge, if easily determined to fit;
	    ;;   otherwise, climb above current workspace top edge.
	    (if (or (not (has-subblocks-p superblock))
		    (loop for subblock being each subblock of superblock
			  never
			    (<w 
			      (nth-value
				1 (determine-extreme-edges-of-block subblock))
			      bottom-edge-for-name-box)))
		;; Then:
		;;    (Either no subblocks, or none above proposed bottom edge.)
		top-edge-for-name-box
		;; Else:
		;;    (Not sure if there's room, so just enlarge.)
		(-w (top-edge-of-block superblock) height-for-name-box))))
	;; Else:   (Superblock is a workspace subblock, may have connections.)
	(if (or (frame-of-class-p superblock 'g2gl-variable)
		(eq positioning-spec? 'to-left))
	    ;; Positioning-spec? can be TO-LEFT or nil, and it's just here for
	    ;; now to support G2-BPEL; flesh out later! (MHD 12/6/04)
	    ;;
	    ;; Special handling currently for G2-BPEL (g2gl-variable class
	    ;; instances) -- generalize later! (MHD 11/29/04)
	    (shift-block-to
	      name-box
	      (-w (left-edge-of-block superblock) (width-of-block name-box))
	      (halfw (-w (+w (top-edge-of-block superblock)
			     (bottom-edge-of-block superblock))
			 height-for-name-box)))
	    (loop with top-clear? = t
		  with right-clear? = t
		  with bottom-clear? = t
		  as connection being each connection of superblock
		  when (eq (input-end-object connection) superblock)
		    do (case (get-side-given-end-position (input-end-position connection))
			 (top (setq top-clear? nil))
			 (right (setq right-clear? nil))
			 (bottom (setq bottom-clear? nil)))
		  when (eq (output-end-object connection) superblock)
		    do (case (get-side-given-end-position (output-end-position connection))
			 (top (setq top-clear? nil))
			 (right (setq right-clear? nil))
			 (bottom (setq bottom-clear? nil)))
		  finally
		    (shift-block
		      name-box
		      (if (or bottom-clear? top-clear?)
			  (halfw (+w (left-edge-of-block superblock)
				     (right-edge-of-block superblock)))
			  (+w (right-edge-of-block superblock) 4))
		      (cond
			(bottom-clear?
			 (+w (bottom-edge-of-block superblock) 4))
			(top-clear?
			 (-w (top-edge-of-block superblock) height-for-name-box))
			(right-clear?
			 (halfw (-w (+w (top-edge-of-block superblock)
					(bottom-edge-of-block superblock))
				    height-for-name-box)))
			(t (+w (bottom-edge-of-block superblock) 4)))))))
    (add-subblock name-box superblock)
    name-box))



;;; The special variable `allow-name-box-creation-without-workspace' can be
;;; bound specially by code that ends up invoking update-name-box to cause a
;;; name box to be created for a frame even when that frame is not on any
;;; workspace.  Normally, a name box is NOT created unless a frame is on a
;;; workspace (or unless it's a workspace itself).

(defvar allow-name-box-creation t)
(defvar allow-name-box-creation-without-workspace nil)

;;; `Update-name-box' updates the name box for frame, as described below, based
;;; on the current value of the name-or-names-for-frame slot of frame.  If frame
;;; has multiple names, only the first (primary) name will be represented in the
;;; name box.

;;; If frame has one or more names, frame is a workspace or is a block in a
;;; workspace, frame has no name box subblock, and showing names is allowed for
;;; frame (as determined by ...), a new name box is created, positioned, and drawn.
;;; If frame has a name box subblock, the name box is updated or, if frame has
;;; no name, deleted.  The position of a new name box is determined by ...

(defun update-name-box (frame)
  (let* ((name-box?
	   (loop for subblock being each subblock of frame
		 when (frame-of-class-p subblock 'name-box)
		   return subblock))
	 (new-name? (get-primary-name-for-frame-if-any frame)))
    (if name-box?
	(if (and (null new-name?)
		 (not (frame-of-class-p frame 'method)))
	    (delete-frame name-box?)
	    (erase-images-of-block name-box? t)))
    (cond
      (new-name?
       (if (null name-box?)
	   (let ((workspace? (get-workspace-if-any frame)))
	     (when (and (or workspace?
			    allow-name-box-creation-without-workspace)
			allow-name-box-creation
			;; showing names is allowed for frame?
			)
	       (setf name-box? (make-name-box frame)))))
       (cond
	 (name-box?
	  (let* ((new-text
		   (slot-value-list
		     (twith-output-to-text-string
		       (write-name-for-frame new-name?))))
		 (old-text-slot-value? (box-translation-and-text name-box?))
		 #+maybe
		 (slot-description
		   (get-slot-description-of-frame
		     'box-translation-and-text
		     name-box?  )))
	    (cond (old-text-slot-value?
		   (reclaim-text (cdr old-text-slot-value?))
		   (setf (cdr old-text-slot-value?) new-text))
		  (t (setf (box-translation-and-text name-box?)
			   (slot-value-cons no-value new-text)))))
	  (let ((old-right-edge (right-edge-of-block name-box?))
		(old-bottom-edge (bottom-edge-of-block name-box?)))
	    (reformat-text-box-in-place
	      name-box?
	      nil nil nil nil t)		; do not enlarge workspace, till after ...
	    (cond
	      ((frame-of-class-p frame 'g2gl-variable)	; special handling for now! (MHD 11/29/04)
	       (let ((old-left-edge (left-edge-of-block name-box?))
		     (old-top-edge (top-edge-of-block name-box?)))
		 (shift-block-to
		   name-box?
		   (-w (left-edge-of-block frame) (width-of-block name-box?))
		   (halfw (-w (+w (top-edge-of-block frame) (bottom-edge-of-block frame))
			      (height-of-block name-box?))))
		 (when (or (not (=w old-left-edge (left-edge-of-block name-box?)))
			   (not (=w old-top-edge (top-edge-of-block name-box?))))
		   (send-ws-representations-item-moved name-box? nil 0))))
	      (t
	       (if (and (not (>=w (left-edge-of-block name-box?) (right-edge-of-block frame)))
			(not (frame-of-class-p frame 'workspace)))
		   ;; if not to right of frame and not a workspace name box
		   (cond
		     ((<=w old-right-edge (left-edge-of-block frame))
		      ;; if to left of frame (its superblock), restore old right edge
		      (shift-block
			name-box?
			(-w old-right-edge (right-edge-of-block name-box?)) 0)
		      (send-ws-representations-item-moved name-box? nil 0))
		     ((or (<=w old-bottom-edge (top-edge-of-block frame))
			  (>=w (top-edge-of-block name-box?) (bottom-edge-of-block frame)))
		      ;; if above or below frame (its superblock), restore old vert. midline
		      (shift-block
			name-box?
			(halfw (-w old-right-edge (right-edge-of-block name-box?))) 0)
		      (send-ws-representations-item-moved name-box? nil 0))))))	    
	    ;; now enlarge workspace if necessary:
	    (enlarge-workspace-for-block-rectangle-if-necessary name-box? nil))
	  (update-subscriptions-from-virtual-attribute-change
	    name-box? (virtual-attribute 'text) nil)
	  (draw-images-of-block name-box? t)))))))

;; Later, this need not handle the workspace case!

;; Review repositioning for the workspace case.  (It now leaves the left edge unchanged.)

;; This assumes that a frame with a name-or-names-for-frame slot is always a
;; block and that a block can have at most one name box subblock.

;; Consider abstracting portions of this to use for other types of text boxes, e.g.,
;; edit boxes and readouts.







;;;; Blinkers



;;; Blinkers are a vistigal organ in G2.  Orignally they were intended to be used
;;; for blinking highlights, for example blinking editor cursors.  The scheduling
;;; of the task required to do frequent blinking was to difficult and was abandoned.
;;; Currently they are the parent class of editor cursors of various sizes.  All

;;; Blinkers are always drawn in the XOR drawing layer.



(def-class (blinker entity)
  (blinker-on? nil vector-slot system))		; t or nil

(def-class-method initialize (blinker)
  (funcall-superior-method blinker)
  (set-render-frame-in-xor-overlay blinker))



;;; The `draw method for a blinker' draws it, as an entity, if it is on, and
;;; does nothing if it is off.

(def-class-method draw (blinker)
  (when (blinker-on? blinker)
    (with-deferred-xor-drawing
      (draw-blinker-in-xor blinker (frame-serial-number blinker)))))


;;; `Draw-blinker-in-xor' Assumes that blinkers appear only as subblock of
;;; a text-box.  This text box may have frame-transforms, and care is taken
;;; to reestablish that tranform.

(defun draw-blinker-in-xor (blinker reference-frame-serial-number)
  (when (and (frame-has-not-been-reprocessed-p
	       blinker reference-frame-serial-number)
	     (blinker-on? blinker))
    (with-frame-transform-of-block-if-any (blinker)
      (draw-icon-for-entity blinker))))

;; The rebinding of draw area seems a little ungrounded, shouldn't the
;; with-frame-tranform-of-block do this, using the block with the frame for
;; guidance?





;;; `Shift-blinker' shifts blinker, erasing and redrawing it as necessary, by
;;; (delta-x, delta-y).  It also turns the blinker on, if it was off(!).  The
;;; workspace it is on will be enlarged as necessary.  If it is not blinking,
;;; it will be scheduled to blink.  (Note that this is NOT a shift method.)

(defun shift-blinker (blinker delta-x delta-y)
  (let ((workspace? (get-workspace-if-any blinker)))
    (when workspace?

      (when (blinker-on? blinker)
	(erase-images-of-block blinker t))
      (setf (blinker-on? blinker) nil)			    ; Not really necessary

      (shift-block blinker delta-x delta-y)
      (enlarge-workspace-for-block-rectangle-if-necessary blinker workspace?)

      ;; Before we can make any state-change in the KB, all drawing queues
      ;; must be flushed.  So, do this before changing the blinker.
      (force-workspace-drawing workspace?)

      (setf (blinker-on? blinker) t)
      (draw-images-of-block blinker t))))



;;; `Stop-blinker' stops blinker from blinking, if it is, and makes it be in the
;;; state specified by have-it-be-on?.  Blinker must not have been deleted.

(defun stop-blinker (blinker have-it-be-on?)
  (let ((workspace? (get-workspace-if-any blinker)))
    (when workspace?
      (cond (have-it-be-on?
	     (unless (blinker-on? blinker)
	       (force-workspace-drawing workspace?)	    ; Drain with blinker in OLD state.
	       (setf (blinker-on? blinker) t)
	       (draw-images-of-block blinker t)))
	    (t
	     (when (blinker-on? blinker)
	       (force-workspace-drawing workspace?)	    ; Hmm. XOR draw does this for us.
	       (erase-images-of-block blinker t)
	       (setf (blinker-on? blinker) nil)))))))








;;;; Edit Cursors



;;; An `edit cursor' is a blinker whose top is to be on a text-line baseline and whose
;;; vertical midline is to be on a "slug edge" (on the edge of a character or space).

(def-class (edit-cursor blinker)

  (icon-description
    (:funcall-at-load-time
      create-icon-description
      12 8
      (#.(create-filled-polygon-icon-description-element
	   '((0 6) (5 0) (10 6) (8 6) (5 2) (2 6)))
	 ;; It doesn't make sense to me why this was done the way it was
	 ;; previously.  The above has a flat bottom and a 3-pixel wide
	 ;; lines, while the following (old) has a stairstep bottom,
	 ;; with lines 3 pixels wide at one end, but only 2 wide at
	 ;; the other end. LH??  (MHD 7/21/93)
;       (lines (0 5) (5 0) (10 5))		; a caret of width 3
;       (lines (1 5) (5 1) (9 5))
;       (lines (1 6) (5 2) (9 6))
	 ))))

(def-class (small-edit-cursor blinker)

  (icon-description
    (:funcall-at-load-time
      create-icon-description
      8 4
      (#.(create-filled-polygon-icon-description-element
	  '((0 4) (4 0) (8 4) (7 4) (4 1) (1 4)))
;       (lines (0 4) (4 0) (8 4))		; a caret of width 2
;       (lines (1 4) (4 1) (7 4))
       ))))

;; Use a filled polygon?
;; -- UPDATE: these have been made to use filled polygons.  The lines did
;; not work out when scaling up.  (MHD 7/21/93)



;;; `Move-edit-cursor' moves edit-cursor, erasing and redrawing it as necessary, so that
;;; its vertical midline will be at midline-x and its top will be at baseline-y.  The
;;; workspace it is on will be enlarged as necessary.  If it is not blinking, it will
;;; be scheduled to blink.

(defun move-edit-cursor (edit-cursor midline-x baseline-y)
  (shift-blinker
    edit-cursor
    (-w midline-x
	(halfw (+w (left-edge-of-block edit-cursor) (right-edge-of-block edit-cursor))))
    (-w baseline-y (top-edge-of-block edit-cursor))))








;;;; Statements



(def-class (statement-or-procedure-step text-box)
  (default-text-box-format-name statement-format))

;; These inherit the spot generator from text-box.



;;; A `statement' is a text box that is expected to contain a meaningful
;;; translation in its box-translation-and-text slot in order to not be
;;; incomplete.  Note that the `initialize method for statement' supplies the
;;; status INCOMPLETE whenever it finds either nil in the
;;; box-translation-and-text slot or finds that that slot's translation is
;;; no-value.

(def-class (statement (item statement-or-procedure-step)
		      (foundation-class statement)
		      define-predicate
		      not-solely-instantiable
		      not-user-instantiable do-not-put-in-menus)
  (default-text-box-format-name statement-format
      (attribute-export-comment
	"export as default-text-box-format type = format-name, a symbol, ~
	writable = true, separately we can export part copies of formats."))
  (runtime-structures-affected-by-this-statement
    nil system vector-slot
    (attribute-export-comment "Internal")))
						 

;; Runtime-structures-affected-by-this-statement is used to uncache runtime
;; structures when the statement is edited (see INSTALL, SIMULATE).  This slot is
;; not saved.

;; Add statement-purposes and statement-invocation-names slots, with appropriate
;; slot putters.

;; The translation should include compilations, where appropriate.



(def-class-method initialize (statement)
  (funcall-superior-method statement)  
  (let ((box-translation-and-text (box-translation-and-text statement)))
    (unless (and box-translation-and-text
		 (not (no-value-p box-translation-and-text)))
      (update-frame-status statement 'incomplete nil))))

;; new. (MHD 7/18/94)


(def-class-method initialize-after-reading (text-box)
  (funcall-superior-method text-box)
  (unless (bad-4-0-beta-magnifications-in-text-boxes-removed-p-function)
    (let* ((plist (text-cell-plist-for-text-box text-box))
	   (x-magnification? (getf plist 'x-magnification))
	   (y-magnification? (getf plist 'y-magnification)))	  
      (when (or (and x-magnification?
		     (not (integerp x-magnification?)))
		(and y-magnification?
		     (not (integerp y-magnification?))))
	(change-text-box-property text-box 'x-magnification nil)
	(change-text-box-property text-box 'y-magnification nil)
	(reformat-text-box-in-place text-box)
	(notify-user
	  "~NA had bad magnification information. It's been removed."
	  text-box)))))

;; This is just to fix a bug in G2 4.0 Beta Phase 1 (in-house).  Some
;; non-magnifications (floats) were being set as the magnification by a buggy
;; version of a system procedure I wrote.  (MHD 2/16/95)



(def-slot-value-reclaimer runtime-structures-affected-by-this-statement
			  (value frame)
  value
  (update-runtime-structures-according-to-edit frame))



(def-text-box-format statement-format
  text-cell-font-map (hm18)			; 1 en = 10 workspace units
  text-cell-line-height 20			; experiment with these!
  text-cell-baseline-position 15
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 6.75)  ; 2/3 en
  minimum-word-spacing #.(convert-to-text-width 5)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 15)	          ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 26	; 4 default spaces
  text-cell-lines-justified? nil
  text-cell-line-color? nil
  text-box-border-color? nil)

(def-text-box-format small-statement-format
  text-cell-font-map (hm14)			; 1 en = 8 workspace units
  text-cell-line-height 15			; experiment with these!
  text-cell-baseline-position 12                ; changed from 13 -> 12 (to avoid chopoff
						;   of descenders -- this is more correct
						;   in terms of the BBoy of the font, -3,
						;   with a height of 15 (15-3=12). (MHD 6/7/93)
  text-cell-line-spacing 2
  default-word-spacing #.(convert-to-text-width 5)	          ; 5/8 en
  minimum-word-spacing #.(convert-to-text-width 4)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 12)	          ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 20	; 4 default spaces
  text-cell-left-margin 8
  text-cell-top-margin 4			; 5?
  text-cell-right-margin 8
  text-cell-bottom-margin 4
  text-cell-lines-justified? nil
  text-cell-line-color? nil
  text-box-border-color? nil)

;; Note that this is used as the text box format for edit boxes
;; when (font-for-editing fonts) is SMALL.  


(setf (corresponding-small-font-format-name 'statement-format) 'small-statement-format)

(def-text-box-format extra-large-statement-format
  text-cell-font-map (hm24)			; 1 en = 14 workspace units
  text-cell-line-height 26			; experiment with these!
  text-cell-baseline-position 19
  text-cell-line-spacing 3
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 8.75) ; 5/8 en
  minimum-word-spacing #.(convert-to-text-width 7)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 21)	          ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 35	; 4 default spaces
  text-cell-left-margin 15
  text-cell-top-margin 11
  text-cell-right-margin 15
  text-cell-bottom-margin 10
  text-cell-lines-justified? nil
  text-cell-line-color? nil
  text-box-border-color? nil)

(setf (corresponding-extra-large-font-format-name 'statement-format)
      'extra-large-statement-format)

;; Consider justifying text lines again at some point! (MHD 7/3/87)







;;;; Free Text Boxes



(def-class (free-text (item text-box) (foundation-class free-text))
  (text-cell-plist-for-text-box nil user-overridable)
  (box-translation-and-text nil (type free text))
  (default-text-box-format-name free-text-format)
  
  #+text-converted-to-show-encoding				; this is like "Show Paragraphs" in a real
					;   word processor
  (text-converted-to-show-encoding?	; see convert-text-to-show-encoding
    nil					; remove this if not needed!?
    (type nil)			; (type yes-or-no) ; Don't show by default
    lookup-slot system
    do-not-save					; eliminate if not development-only!
    )

  )

;; Now, make text-box-spots
;; (def-class-method generate-spot (free-text mouse-pointer)
;;   (generate-simple-item-spot free-text mouse-pointer))

(def-text-box-format free-text-format
  text-cell-font-map (hm18)			; 1 en = 10 workspace units
  text-cell-line-height 20			; experiment with these!
  text-cell-baseline-position 15
  text-cell-line-spacing 4
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 6.75)  ; 2/3 en
  minimum-word-spacing #.(convert-to-text-width 5)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 15)	          ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 0		; 12 before 11/23/88
  minimum-format-width-for-text-cell 500
  maximum-format-width-for-text-cell 1000	; defaulted before 11/23/88
						; was 500 (MHD 3/20/91)
  text-cell-lines-justified? nil
  text-cell-line-color? nil
  text-box-border-color? nil)

(def-text-box-format small-free-text-format
  text-cell-font-map (hm14)			; 1 en = 8 workspace units
  text-cell-line-height 15			; experiment with these!
  text-cell-baseline-position 13
  text-cell-line-spacing 2
  default-word-spacing #.(convert-to-text-width 5)	          ; 5/8 en
  minimum-word-spacing #.(convert-to-text-width 4)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 12)	          ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 0		; 10 before 11/23/88
  minimum-format-width-for-text-cell 500
  maximum-format-width-for-text-cell 1000	; defaulted before 11/23/88
						; was 500 (MHD 3/20/91)
  text-cell-lines-justified? nil
  text-cell-line-color? nil
  text-box-border-color? nil
  text-cell-left-margin 8
  text-cell-top-margin 4			; 5?
  text-cell-right-margin 8
  text-cell-bottom-margin 4)

(setf (corresponding-small-font-format-name 'free-text-format) 'small-free-text-format)

(def-text-box-format extra-large-free-text-format
  text-cell-font-map (hm24)			; 1 en = 14 workspace units
  text-cell-line-height 26			; experiment with these!
  text-cell-baseline-position 19
  text-cell-line-spacing 3
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 8.75) ; 5/8 en
  minimum-word-spacing #.(convert-to-text-width 7)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 21)	          ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 0
  maximum-format-width-for-text-cell 600
  minimum-format-width-for-text-cell 600
  text-cell-left-margin 15
  text-cell-top-margin 11
  text-cell-right-margin 15
  text-cell-bottom-margin 10
  text-cell-lines-justified? nil
  text-cell-line-color? nil
  text-box-border-color? nil)

(setf (corresponding-extra-large-font-format-name 'free-text-format)
      'extra-large-free-text-format)



;(defun make-text-box-opaque-if-possible
;       (text-box &optional make-non-opaque-instead?)
;  (unless (or
;	    ;; opaque iff it's supposed to be already?
;	    (if (opaque-block-p text-box)
;		(not make-non-opaque-instead?)
;		make-non-opaque-instead?)
;	    ;; can only have text regions as subblocks:
;	    (loop for subblock being each subblock of text-box
;		  thereis (not (frame-of-class-p
;				 subblock 'text-region))))
;    (let ((workspace? (get-workspace-if-any text-box)))
;      (unless (and workspace?			; must be top-level subblock
;		   (not (eq workspace? (superblock? text-box))))
;	(cond
;	  (workspace?
;	   (transfer-item text-box nil nil nil)
;	   (if make-non-opaque-instead?
;	       (clear-opaque-block text-box)
;	       (set-opaque-block text-box))
;	   (transfer-item text-box workspace? nil nil))
;	  (t
;	   (if make-non-opaque-instead?
;	       (clear-opaque-block text-box)
;	       (set-opaque-block text-box))))))))

;#+development
;(def-class (opaque-free-text free-text)
;  (frame-flags #.opaque-block-flag))

;#+development
;(def-class-method draw (opaque-free-text)
;  (paint-background-for-opaque-block opaque-free-text)
;  (draw-for-text-box opaque-free-text))

;; TEMPORARY!!

;; Removed. (ML 7/21/89)



(def-class (borderless-free-text (item text-box)
				 (foundation-class borderless-free-text))
  (text-cell-plist-for-text-box nil user-overridable)
  (box-translation-and-text nil (type free text))
  (default-text-box-format-name borderless-free-text-format)
  #+text-converted-to-show-encoding
  (text-converted-to-show-encoding?		; see convert-text-to-show-encoding
    nil (type yes-or-no) no-accessor		; don't have for borderless-free-text?
    lookup-slot system user-overridable
    (attribute-export-comment "Type (or none boolean))"))
  )

;; -fmw, 12/2/93
;; (def-class-method generate-spot (borderless-free-text mouse-pointer)
;;   (generate-simple-item-spot borderless-free-text mouse-pointer))

(def-text-box-format borderless-free-text-format
  text-cell-font-map (hm18)			; 1 en = 10 workspace units
  text-cell-line-height 20			; experiment with these!
  text-cell-baseline-position 15
  text-cell-line-spacing 4
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 6.75)  ; 2/3 en
  minimum-word-spacing #.(convert-to-text-width 5)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 15)	          ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 0		; 12 before 11/23/88
  minimum-format-width-for-text-cell 500
  maximum-format-width-for-text-cell 1000	; defaulted before 11/23/88
						; was 500 (MHD 3/20/91)
  text-cell-lines-justified? nil
  text-cell-line-color? nil
  text-box-border-color? nil
  text-cell-left-margin 6
  text-cell-top-margin 3
  text-cell-right-margin 6
  text-cell-bottom-margin 2
  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0)

(def-text-box-format small-borderless-free-text-format
  text-cell-font-map (hm14)			; 1 en = 8 workspace units
  text-cell-line-height 15			; experiment with these!
  text-cell-baseline-position 13
  text-cell-line-spacing 2
  default-word-spacing #.(convert-to-text-width 5)	          ; 5/8 en
  minimum-word-spacing #.(convert-to-text-width 4)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 12)	          ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 0		; 10 before 11/23/88
  minimum-format-width-for-text-cell 500
  maximum-format-width-for-text-cell 1000	; defaulted before 11/23/88
						; was 500 (MHD 3/20/91)
  text-cell-lines-justified? nil
  text-cell-line-color? nil
  text-box-border-color? nil
  text-cell-left-margin 5
  text-cell-top-margin 2
  text-cell-right-margin 5
  text-cell-bottom-margin 2
  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0)

(setf (corresponding-small-font-format-name 'borderless-free-text-format)
      'small-borderless-free-text-format)

(def-text-box-format extra-large-borderless-free-text-format
  text-cell-font-map (hm24)			; 1 en = 14 workspace units
  text-cell-line-height 26			; experiment with these!
  text-cell-baseline-position 19
  text-cell-line-spacing 3
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 8.75) ; 5/8 en
  minimum-word-spacing #.(convert-to-text-width 7)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 21)	          ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 0
  maximum-format-width-for-text-cell 600
  minimum-format-width-for-text-cell 600
  text-cell-left-margin 8
  text-cell-top-margin 4
  text-cell-right-margin 8
  text-cell-bottom-margin 3
  text-cell-lines-justified? nil
  text-cell-line-color? nil
  text-box-border-color? nil
  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0)

(setf (corresponding-extra-large-font-format-name 'borderless-free-text-format)
      'extra-large-borderless-free-text-format)

;; Borderless text boxes pose problems in selection when the right edge is ragged, etc.

;;;; `Scrolling-editor-text-format'


(def-text-box-format scrolling-editor-text-format
  text-cell-font-map (hm18)			; 1 en = 10 workspace units
  text-cell-line-height 20			; experiment with these!
  text-cell-baseline-position 15
  text-cell-line-spacing 4
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 6.75)  ; 2/3 en
  minimum-word-spacing #.(convert-to-text-width 5)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 15)	          ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 26	; 12 before 11/23/88, 0 before 8/17/95
  minimum-format-width-for-text-cell 500
  maximum-format-width-for-text-cell 2000
  text-cell-lines-justified? nil
  text-cell-line-color? nil
  text-box-border-color? nil
  text-cell-left-margin 6
  text-cell-top-margin 0
  text-cell-right-margin 6
  text-cell-bottom-margin 0
  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0)

(def-text-box-format small-scrolling-editor-text-format
  text-cell-font-map (hm14)			; 1 en = 8 workspace units
  text-cell-line-height 15			; experiment with these!
  text-cell-baseline-position 12	; Changed to match small-statement-format PGA 8/17/95
  text-cell-line-spacing 2
  default-word-spacing #.(convert-to-text-width 5)	          ; 5/8 en
  minimum-word-spacing #.(convert-to-text-width 4)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 12)	          ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 20		; 10 before 11/23/88, 0 before 8/17/95
  minimum-format-width-for-text-cell 500
  maximum-format-width-for-text-cell 2000
  text-cell-lines-justified? nil
  text-cell-line-color? nil
  text-box-border-color? nil
  text-cell-left-margin 5
  text-cell-top-margin 0
  text-cell-right-margin 5
  text-cell-bottom-margin 0
  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0)

(setf (corresponding-small-font-format-name 'scrolling-editor-text-format)
      'small-scrolling-editor-text-format)

(def-text-box-format extra-large-scrolling-editor-text-format
  text-cell-font-map (hm24)			; 1 en = 14 workspace units
  text-cell-line-height 26			; experiment with these!
  text-cell-baseline-position 19
  text-cell-line-spacing 3
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 8.75) ; 5/8 en
  minimum-word-spacing #.(convert-to-text-width 7)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 21)	          ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 35 ; Was 0 before 8/17/95 - pga
  minimum-format-width-for-text-cell 600
  maximum-format-width-for-text-cell 2000
  text-cell-left-margin 8
  text-cell-top-margin 0
  text-cell-right-margin 8
  text-cell-bottom-margin 0
  text-cell-lines-justified? nil
  text-cell-line-color? nil
  text-box-border-color? nil
  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0)

(setf (corresponding-extra-large-font-format-name 'scrolling-editor-text-format)
      'extra-large-scrolling-editor-text-format)


;;; `Wide-caption-format' is borderless and wide.

;; Where is this used?

(def-text-box-format wide-caption-format
  minimum-format-width-for-text-cell 700
  maximum-format-width-for-text-cell 900
  text-cell-font-map (hm18)			; 1 en = 10 workspace units
  text-cell-line-height 20			; experiment with these!
  text-cell-baseline-position 15
  text-cell-line-spacing 4
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 6.75)  ; 2/3 en
  minimum-word-spacing #.(convert-to-text-width 5)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 15)	          ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 12
  text-cell-lines-justified? nil
  text-cell-line-color? nil
  text-box-border-color? nil
  text-cell-left-margin 6
  text-cell-top-margin 3
  text-cell-right-margin 6
  text-cell-bottom-margin 2
  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0
  )



;;; `Make-free-text-box' ... uses, by default, class borderless-free-text and
;;; the default text box format for the class.  The new text box is reformatted
;;; "in place", whereupon the text line argument may turn into more than one
;;; line.  In all cases, the text-line argument is either reclaimed or
;;; incorporated into the text data structure by this function.
;;;
;;; If maximum-width-to-truncate-after? is specified, text-line will be
;;; truncated, if necessary, to be no wider than that, with
;;; truncated-string-suffix? added if possible.  Truncated-string-suffix? must
;;; be a text string or nil.

(defun make-free-text-box
       (text-line &optional class? text-box-format-name?
	maximum-width-to-truncate-after? truncated-string-suffix?
	do-not-reformat?)
  (make-free-text-box-with-text
    (if do-not-reformat?
	(prog1
	    (loop with length = (lengthw text-line)
		  for index = 0 then next-index
		  while (<f index length)
		  for new-line-position = (loop for i from (1+f index) below length
						for ch = (charw text-line i)
						when (newline-p ch)
						  return i)
		  for next-index = (or new-line-position length)
		  nconc (slot-value-list
			  (make-lost-spaces-text-element 0)
			  (text-string-substring text-line index next-index)))
	  (reclaim-text-string text-line))
	(convert-text-string-to-text
	  (if maximum-width-to-truncate-after?
	      (prog1
		  (or (let ((text-box-format
			      (get-or-make-format-frame
				(or text-box-format-name?
				    (get-slot-init-form
				      (or class? 'borderless-free-text)
				      'default-text-box-format-name)))))
			(truncate-string-as-necessary-to-fit
			  text-line
			  maximum-width-to-truncate-after?
			  (text-cell-font-map text-box-format)
			  (default-word-spacing text-box-format)
			  truncated-string-suffix?))
		      (obtain-simple-text-string 0))
		(reclaim-text-string text-line))
	      text-line)))
    class? text-box-format-name? do-not-reformat?))


;;; `Make-free-text-box-with-text' makes a free text box, incorporating text
;;; as the text of the resulting text box. 

(defun make-free-text-box-with-text
       (text &optional class? text-box-format-name? do-not-reformat?)
  (let ((free-text-box
	   (make-frame				; use faster primitive or recycled boxes?
	     (or class? 'borderless-free-text))))
    (setf (text-box-format free-text-box)
	  (get-or-make-format-frame
	     (or text-box-format-name?
		 (default-text-box-format-name free-text-box))))
    (setf (box-translation-and-text free-text-box)
	  (slot-value-cons no-value text))
    (reformat-text-box-in-place free-text-box nil do-not-reformat?)
    free-text-box))

;; At present, no need has arisen for this to handle the truncation
;; functionality as does the previous function. Consider for a later
;; time.








;;;; Support for Dialog Boxes


(def-format-class (dialog-box-format text-box-format)
  (text-box-left-margin 0)
  (text-box-top-margin 0)
  (text-box-right-margin 0)
  (text-box-bottom-margin 0)
  (text-cell-paragraph-indentation 0)
  (text-cell-turnover-line-indentation 0)
  (text-cell-line-color? nil)
  (text-box-border-color? nil)
  (text-cell-background-color? nil))

(def-dialog-box-format dialog-message-format
  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0)


(def-dialog-box-format default-button-format
  text-cell-line-quadding? center
  text-box-left-border-width 1
  text-box-top-border-width 1
  text-box-right-border-width 8
  text-box-bottom-border-width 8
  minimum-format-width-for-text-cell 50
  maximum-format-width-for-text-cell 50)


(def-dialog-box-format non-default-button-format
  text-cell-line-quadding? center
  text-box-left-border-width 1
  text-box-top-border-width 1
  text-box-right-border-width 1
  text-box-bottom-border-width 1
  minimum-format-width-for-text-cell 50
  maximum-format-width-for-text-cell 50)


(def-class (dialog-message text-box)
  (box-translation-and-text nil (type nil text))
  (default-text-box-format-name dialog-message-format))

(def-class (dialog-button text-box)
  (box-translation-and-text nil (type nil text)))

(def-class-method generate-spot (dialog-message mouse-pointer)
  (generate-simple-item-spot dialog-message mouse-pointer))

(def-class-method generate-spot (dialog-button mouse-pointer)
  (generate-simple-item-spot dialog-button mouse-pointer))




;;; `Make-dialog-message' ...

(defun make-dialog-message (constant-string)
  (make-free-text-box (copy-text-string constant-string) 'dialog-message))

;; Consider having this take an (unshared) text-line argument.



;;; `Make-dialog-button' ...

(defun make-dialog-button (constant-string translation this-is-the-default-button?)
  (let ((dialog-button
	  (make-free-text-box
	    (copy-text-string constant-string)
	    'dialog-button
	    (if this-is-the-default-button?
		'default-button-format
		'non-default-button-format))))
    (setf (car (box-translation-and-text dialog-button)) translation)	; <- kludge?!
    dialog-button))
  

;; Clean this up!








;;;; Formatting Text



;;; `Format-text' ...

;;; Format-text return four values: the text, appropriately formatted; the width of its
;;; longest line, including indentation but not lost spaces; and revised values for
;;; cursor-line-index? and cursor-character-index?, if specified.  If the returned text
;;; is not eq to the argument text (possibly modified to include indentations and line
;;; widths), the argument text will have been reclaimed.

;;; If do-not-reformat-text? is non-nil, text is not reformatted.

;;; No part of text can be currently drawn, especially since line-of-text graphic elements
;;; include the actual text lines they represent, not copies.

(defun format-text
       (text text-box-format text-cell-plist width-for-cell?
	do-not-reformat-text? reformatting-with-same-format?
	include-indentations-and-widths? known-to-have-indentations-and-widths?
	&optional cursor-line-index? cursor-character-index?
	format-width-override?
	allow-override-below-limit-p)
  reformatting-with-same-format?		; unused now
  (let ((text-cell-line-justification?
	  (get-text-cell-line-justification text-box-format text-cell-plist))
	(width-of-longest-line 0))
    (cond
      ((not do-not-reformat-text?)
       (let (old-text)
	 (multiple-value-setq (text width-of-longest-line old-text)  ; changes text arg
	   (reformat-text
	     text text-box-format width-for-cell?
	     (or include-indentations-and-widths? text-cell-line-justification?)
	     nil nil nil nil nil nil
	     format-width-override?
	     text-cell-plist
	     allow-override-below-limit-p))
	 (if (and cursor-line-index? cursor-character-index?)
	     (multiple-value-setq (cursor-line-index? cursor-character-index?)
	       (determine-corrected-text-position-if-necessary
		 cursor-line-index? cursor-character-index? text old-text 1)))
	 (reclaim-text old-text)))
      (known-to-have-indentations-and-widths?	; special case for speed only
       (loop for text-element in text
	     when (and (consp text-element) (eq (car text-element) 'line-width))
	       do (if (>f (cdr text-element) width-of-longest-line)
		      (setq width-of-longest-line (cdr text-element)))))
      (t (setq width-of-longest-line		; handle indentations properly (someday)!
	       (compute-width-of-longest-line	; include this in-line for speed?
		 text text-box-format text-cell-plist
		 (or include-indentations-and-widths? text-cell-line-justification?)))))
    (if text-cell-line-justification?
	(loop with text-tail? = text
	      with line-width
	      with width-for-justification
		= (maxw
		    width-of-longest-line
		    (-w (or format-width-override? width-for-cell? 0)
			(text-cell-left-margin text-box-format)
			(text-cell-right-margin text-box-format)))
	      as this-text-tail = text-tail?
	      do (multiple-value-setq-some
		   (nil nil nil text-tail? nil line-width)
		   (get-next-text-line text-tail?))
		 (loop with x-magnification?
		       = (x-magnification? text-cell-plist text-box-format)
		       with width-for-justification-after-magnification
			 = (if x-magnification?
			       (inverse-magnify width-for-justification x-magnification?)
			       width-for-justification)
		       with line-width-after-magnification
			 = (if x-magnification?
			       (inverse-magnify line-width x-magnification?)
			       line-width)
		       with adjustment
			 = (case text-cell-line-justification?
			     (center (halfw (-w width-for-justification-after-magnification
						line-width-after-magnification)))
			     (right (-w width-for-justification-after-magnification
					line-width-after-magnification))
			     (t 0))		; handle JUSTIFIED case later!
		       as l on this-text-tail
		       do (cond			; handle indentations properly (someday)!
			    ((fixnump (car l))	; could KNOW where it is!
			     (setf (car l) adjustment)
			     (return nil))))
	      until (null text-tail?)))
    (if (and (not include-indentations-and-widths?)
	     (or known-to-have-indentations-and-widths? text-cell-line-justification?))
	(loop with indentation = 0		; get rid of indentations and line widths
	      with l-trailer? = nil
	      as l = text then next-l?
	      as text-element = (car l)
	      as next-l? = (cdr l)
	      do (cond
		   ((if (atom text-element)
			(if (fixnump text-element)
			    (=w text-element
				(prog1 indentation
				       (setq indentation text-element))))
			(eq (car text-element) 'line-width))
		    (if (null l-trailer?)
			(setq text next-l?)
			(setf (cdr l-trailer?) next-l?))
		    (setf (cdr l) nil)
		    (reclaim-slot-value-tree l))	; be more efficient!
		   (t (setq l-trailer? l)))
	      while next-l?))
    (values text width-of-longest-line cursor-line-index? cursor-character-index?)))

;; Fix to take text-cell-plist argument!

;; Consider using compute-width-of-longest-line herein.

;; Fix indentation handling here and in reformat-text!  Make zero the default value of
;; text-cell-paragraph-indentation!  Fix all formats accordingly!

;; This is currently called from two places in module TABLES and one place in module BOXES.

;; Format-text is somewhat limited, and should ultimately be replaced.










;;;; Line Buffers



;;; A `line buffer' is a text-line, represented as a text string.




;;; `Make-text-line-buffer' makes a text-line line buffer.  This is intended
;;; only to be called from reformat-text, q.v.

(defun make-text-line-buffer ()
  (obtain-text-string (get-text-line-buffer-limit)))



;;; `Get-text-line-buffer-limit' simply returns a constant value for the
;;; maximum suggested length for a text line acting as a line buffer.  

(defun get-text-line-buffer-limit ()
  maximum-suggested-length-for-wide-strings)



;;; `Write-into-line-buffer' writes character into the specified line buffer,
;;; replacing the line buffer by a bigger one if necessary to hold character.
;;; The value of line-buffer-variable must be the line buffer, a text line.  The
;;; value of fill-pointer-variable must be the "fill pointer" for the line
;;; buffer, a fixnum one greater than the last written character therein.  The
;;; value of total-length-variable must be the length of the line buffer.
;;;
;;; `Write-kanji-code-into-line-buffer' does the equivalent for kanji-code.

;;; This macro makes no guarantees as to the order of evaluation or the number of times
;;; its variable (place) arguments may be evaluated.  At present, it is used only in
;;; module BOXES.

(defmacro write-into-line-buffer
    (character line-buffer-variable fill-pointer-variable total-length-variable)
  `(progn
     (cond
       ((>=f ,fill-pointer-variable ,total-length-variable)	; =f should suffice
	(setf ,total-length-variable
	      (+f ,total-length-variable 100))	; assumed > ,fill-pointer-variable
	(setf ,line-buffer-variable
	      (make-bigger-line-buffer
		,line-buffer-variable ,fill-pointer-variable ,total-length-variable))))
     (setf (charw ,line-buffer-variable ,fill-pointer-variable) ,character)
     (incff ,fill-pointer-variable)))

(defun-simple make-bigger-line-buffer (line-buffer current-length new-length)
  (declare (type fixnum current-length new-length))
  (let ((new-line-buffer (obtain-text-string new-length)))
    (copy-portion-of-wide-string-into-wide-string
      line-buffer 0 current-length
      new-line-buffer 0)
    (reclaim-text-string line-buffer)
    new-line-buffer))

;; Consider redoing this in terms of extend-current-text-string.








;;;; Reformatting Text



;; The following are special for the sake of get-character-if-any-for-running-text.  The
;; ones in the first group are never changed by get-character-if-any-for-running-text,
;; and thus could be passed as args.

(defvar *line-index-of-change?)
(defvar *character-index-of-change?)
(defvar *line-index-past-deletion?)
(defvar *character-index-past-deletion?)
(defvar *string-to-insert?)
(defvar *text-string-to-insert-is-simple?)

(defvar *character-index-in-string-to-insert?)
(defvar *line-buffer)
(defvar *line-index)
(defvar *character-index)
(defvar *text-line)
(defvar *text-line-is-simple?)
(defvar *line-length)
(defvar *lost-space-at-end-of-line)
(defvar *this-text-tail?)
(defvar *next-text-tail?)
(defvar *current-indentation)
(defvar *explicit-paragraph-or-newline?)
(defvar *line-buffer-fill-pointer)
(defvar *line-buffer-limit)

;; Instead of all these special variables, consider having a single structure that
;; is passed to get-character-if-any-for-running-text.

;; Use special variables *character? and *previous-character?!?





;;; `Determine-unmagnified-line-measure' .... Format-width-override?, or 0 if it
;;; is null, is maxed with the minimum-format-width-for-text-cell of
;;; text-box-format.  The result is maxed with the minimum of width-for-cell?,
;;; or zero if that is null, and either the format-width-override?  itself, if
;;; non-null, or the maximum-format-width-for-text-cell of the text-box-format.
;;;
;;; That overall result is minned with maximum-text-box-width-or-height, a very
;;; liberal limitation needed to make text boxes fit within reasonable limits
;;; and still allow them to be magnified and fit on workspaces and work well
;;; with fixnum limits.

(defun-substitution-macro determine-unmagnified-line-measure
    (text-box-format width-for-cell? format-width-override? allow-override-below-limit-p)  
  (-w (minw (maxw (or format-width-override? 0)
		  (if (and format-width-override? allow-override-below-limit-p)
		      (minw (+w (text-cell-left-margin text-box-format) (text-cell-right-margin text-box-format))
			    format-width-override?)
		      (minimum-format-width-for-text-cell text-box-format))
		   (minw (or format-width-override?
			    (maximum-format-width-for-text-cell text-box-format))
			(or width-for-cell? 0)))
	    maximum-text-box-width-or-height)
      (text-cell-left-margin text-box-format)
      (text-cell-right-margin text-box-format)))





;;; `Reformat-text' ...

;;; Reformat-text returns seven values:
;;;    (1) the new text segment;
;;;    (2) the workspace width of the longest line in the new text segment;
;;;    (3) a text tail of text corresponding to the beginning of the
;;;        "old text segment" (which is to be replaced by the new text segment);
;;;    (4) nil or a text tail of text corresponding to the end of the
;;;        old text segment (later to be nconc'ed onto the new text segment);
;;;    (5) the line index for the first line of the old and new text segment;
;;;    (6) the line index past the new text segment; and
;;;    (7) the line index past the old text segment.

;;; Text-tail-for-reformatting-only-for-change? may be specified only when line-index-
;;; of-change? is specified and only if text was produced by reformat-text using the
;;; same text box format and width.

;;; Each paragraph separator or line separator in the changed text results in at
;;; least one (possibly blank) line.

;;; Changes can be done and text-tail? can be specified only if text already has
;;; indentations and widths for each line.

;;; String-to-insert?, if non-nil, should be a text string, and is NOT reclaimed
;;; by this function.

(defun reformat-text
       (text text-box-format
	&optional width-for-cell?
	          put-in-indentations-and-widths?
	          text-tail-for-reformatting-only-for-change?
		  line-index-of-change?
		  character-index-of-change?
		  line-index-past-deletion?	; past the position of change
		  character-index-past-deletion?
		  string-to-insert?	; to be recycled; maybe "character-or-"
		  format-width-override?
		  text-cell-plist
		  allow-override-below-limit-p)
  (let* ((*line-index-of-change? line-index-of-change?)
	 (*character-index-of-change? character-index-of-change?)
	 (*line-index-past-deletion? line-index-past-deletion?)
	 (*character-index-past-deletion? character-index-past-deletion?)
	 (*string-to-insert? string-to-insert?)
	 (*text-string-to-insert-is-simple? nil)
	 (*character-index-in-string-to-insert?
	   (if *string-to-insert? 0))
	 (*line-buffer (make-text-line-buffer))
	 (*line-buffer-fill-pointer 0)
	 (*line-buffer-limit (get-text-line-buffer-limit))
	 *line-index
	 (*character-index 0)
	 *this-text-tail?
	 *text-line
	 *text-line-is-simple?
	 *line-length
	 *lost-space-at-end-of-line
	 *next-text-tail?
	 (*current-indentation 0)
	 *explicit-paragraph-or-newline?)
    (reformat-text-1
      text text-box-format
      width-for-cell?
      put-in-indentations-and-widths?
      text-tail-for-reformatting-only-for-change?
      format-width-override?
      text-cell-plist
      allow-override-below-limit-p)))

;; Reformat-text used to be just one function.  Now it has been broken into two,
;; the original, which just binds the *special variables, and the subfunction,
;; reformat-text-1, which is just internal to it.  This was done primarily to
;; get all of the *special variable bindings into a single let "contour".  This
;; is mostly because of the high cost of variable binding in Chestnut (a setjump
;; per contour + shutting off of optimization for the entire function).
;; However, this is a reasonably good way to leave things forever, so I would
;; not plan to revert this when/if Chestnut's problems are resolved.  (MHD
;; 6/4/92)



;;; Reformat-text-1 ... This handles x magnification, if any, by reducing the
;;; line measure so that magnification does not have to be applied incrementally
;;; as characters get processed.

;; Width and spacing computations in reformat-text-1 depend on text-box slots,
;; parameters, and local variables.

;; Text-box-format slots:
;;    minimum-width-for-text-cell,
;;    maximum-format-width-for-text-cell,
;;    minimum-format-width-for-text-cell,
;;    text-cell-left-margin
;;    text-cell-right-margin
;; Parameters:
;;    width-for-cell?,
;;    text-cell-desired-maximum-line-measure? ;In calls this is passed down from the text-box.
;;    put-in-indentations-and-widths?

;; Locals: 
;;    default-word-spacing ; Extracted from text-box-format at loop initialization
;;    line-width

;;    line-measure
;;    maximum-line-width
;;    minimum-line-width
;;    word-spacing

;;    width-of-longest-new-line
;;    width-a-of-line-so-far
;;    width-b-of-line-so-far

;;    ok-to-break?
;;    number-of-adjustable-spaces-so-far = 0
;;    character-index-of-last-natural-break? = nil
;;    character-index-after-last-natural-break
;;    last-natural-break-is-all-ordinary-spaces?
;;    number-of-adjustable-spaces-up-to-last-natural-break
;;    number-of-adjustable-spaces-through-last-natural-break
;;    width-a-of-line-up-to-last-natural-break
;;    width-b-of-line-up-to-last-natural-break
;;    width-a-of-line-through-last-natural-break
;;    width-b-of-line-through-last-natural-break

;;    text-width-for-character is a local which gets the value of a
;;    function call of the same name.

(defun reformat-text-1 (text text-box-format
			     width-for-cell?
			     put-in-indentations-and-widths?
			     text-tail-for-reformatting-only-for-change?
			     format-width-override?
			     text-cell-plist
			     allow-override-below-limit-p)
  (loop with x-magnification?
	  = (x-magnification? text-cell-plist text-box-format)
	with line-measure
	  = (determine-unmagnified-line-measure
	      text-box-format width-for-cell? format-width-override?
	      allow-override-below-limit-p)
	with line-justification?
	  = (get-text-cell-line-justification text-box-format text-cell-plist)
	with maximum-line-width			; as if unmagnified
	  = (if x-magnification?
		(inverse-magnify line-measure x-magnification?)
		line-measure)
	with minimum-line-width			; as if unmagnified
	  = (if (eq line-justification? 'justified)
		maximum-line-width
		(magnify maximum-line-width
			 #.(convert-to-magnification-at-compile-time .6)))
					; parameterize the above later!
	with font-map
	  = (text-cell-font-map text-box-format)
	with ab-font = (ab-font (car font-map))	; IMPROVE!
	with default-word-spacing
	  = (default-word-spacing text-box-format)
	with word-spacing = default-word-spacing    ; MINIMUM WHEN WIDTHS COMPUT. FIXED!
	with initial-line-index = (or *line-index-of-change? 1)
	with initial-text-tail
	  = (or text-tail-for-reformatting-only-for-change? text)
	with reversed-new-text-segment = nil
	with width-of-longest-new-line = 0
	with current-indentation-for-new-lines
	with line-index-for-next-new-line
	with paragraph-or-newline-for-next-new-line?  ; nil, IMPLIED-PARAGRAPH, PARAGRAPH,
	with indentation-for-next-new-line	      ;   or NEWLINE or RETURN or LINEFEED
	with indentation-for-turnover-lines
	with ok-to-break?
	with context-stack = nil
	with number-of-adjustable-spaces-so-far = 0
	with width-a-of-line-so-far
	with width-b-of-line-so-far
	with character-index-of-last-natural-break? = nil
	with character-index-after-last-natural-break
	with last-natural-break-is-all-ordinary-spaces?
	with number-of-adjustable-spaces-up-to-last-natural-break
	with number-of-adjustable-spaces-through-last-natural-break
	with width-a-of-line-up-to-last-natural-break
	with width-b-of-line-up-to-last-natural-break
	with width-a-of-line-through-last-natural-break
	with width-b-of-line-through-last-natural-break
	with context-stack-at-last-natural-break? = nil
	with get-character? = t	 ; could just call get-character-... where this is made t
	with character?
	with text-break-case?
	
	initially
	  (let (indentation-if-new? context-carryover?)
	    (multiple-value-setq-some
		(*text-line *line-length *lost-space-at-end-of-line
			    *next-text-tail? indentation-if-new?
			    nil context-carryover?)
		(get-next-text-line initial-text-tail))
	    (setq *text-line-is-simple? nil)
	    ;; IF neither the first line nor a line beginning with paragraph separator or
	    ;;      line separator
	    ;;    AND EITHER have deletion before first break position and last line has
	    ;;          no lost space
	    ;;        OR if have deletion from beginning of line through end of line or
	    ;;             break position
	    ;;        OR if inserting a space of any kind at the beginning of a turnover
	    ;;             line,
	    ;; THEN back up a line, if possible (and fix initial-line-index and
	    ;;        initial-text-tail)!!!
	    ;; (NOW it backs up a line whenever there is a deletion or an inserted space)
	    (cond
	      ((and (>f initial-line-index 1)
		    (or *line-index-past-deletion?	; SEE ABOVE!
			(if *string-to-insert?
			    (and *string-to-insert?
				 (string=w
				   *string-to-insert?
				   '#.(make-wide-string 1 :initial-element #.%space))) ; #w" "
			    )))
	       (multiple-value-setq-some
		   (*text-line *line-length *lost-space-at-end-of-line
			       *next-text-tail? indentation-if-new?
			       nil context-carryover?)
		   (get-next-text-line
		     (setq initial-text-tail
			   (find-text-tail-for-line
			     text (decff initial-line-index)))))
	       (setq *text-line-is-simple? nil)))
	    (loop for l = text then (cdr l)	  ; omit if not needed, since this is
		  until (eq l initial-text-tail)  ;   slow if text is long!
		  when (fixnump (car l))
		    do (setq *current-indentation (car l)))
	    (setq current-indentation-for-new-lines *current-indentation)
	    (if indentation-if-new?
		(setq *current-indentation indentation-if-new?))
	    (setq indentation-for-turnover-lines  ; not used if first line has paragraph
		  (case line-justification?       ;   separator or line separator
		    ((center right) 0)		; handle indentations properly (someday)!
		    (t (if (=f initial-line-index 1)
			   (text-cell-turnover-line-indentation text-box-format)
			   *current-indentation))))
	    (if context-carryover?
		(loop for symbol in context-carryover?
		      do (case symbol
			   (L ab-font))		; NEEDS WORK!
			 (setq context-stack
			       (slot-value-cons symbol context-stack)))))
	  (setq *line-index initial-line-index)
	  (setq *this-text-tail? initial-text-tail)
	  (setq line-index-for-next-new-line initial-line-index)
	  (setq paragraph-or-newline-for-next-new-line?	; combine with code below?
		(if (=f initial-line-index 1) 'implied-paragraph))
	  (setq indentation-for-next-new-line ; not used if first line has paragraph
		(if (=f initial-line-index 1) ;   separator or line separator
		    (case line-justification?
		      ((center right) 0)	; handle indentations properly (someday)!
		      (t (text-cell-paragraph-indentation text-box-format)))
		    indentation-for-turnover-lines))
	  (set-text-x			; not used if first line has paragraph
					;   separator or line separator
	    width-a-of-line-so-far width-b-of-line-so-far indentation-for-next-new-line)

	do (when get-character?
	     ;; character? is a unicode wide character
	     ;; These two variables are set only here and by another call
	     ;; below to the same function.
	     (progn
	       (setq character? (get-character-if-any-for-running-text))
	       (setq text-break-case? (and character? (text-break-p character?)))))
	   (setq ok-to-break? nil)
	   (if (and (or text-break-case?  ; natural breaks not starting beyond maximum-line-width
			(and character?	; previously checked for @Q
			     (char=w character? #.%zero-width-joiner))
			(null character?))	; end of paragraph is a natural break
		    (or (null character-index-of-last-natural-break?) ; UNTIL WORDS GET BROKEN!
			(<=w (text-x-to-x width-a-of-line-so-far width-b-of-line-so-far)
			     maximum-line-width)))
	       ;; We usually go into the following loop whenever we have a space
	       ;; break that's within the line measure; but if we've never
	       ;; broken yet, we go into this loop even if over the limit
	       ;; because we don't currently handle breaking up words except at
	       ;; hyphens.  We also enter this if we are at the end of a line
	       ;; break (a paragraph or newline).
	       ;;
	       ;; Note: above and below @Q is partnered with text-break-case?.
	       ;; This would only make sense to me (MHD) if @Q meant "permit
	       ;; break here"; however, it actually is documented to mean "don't
	       ;; permit break here".  I think this was a "thinko" or something,
	       ;; and @Q just wants to be changed to @R, which is specified as
	       ;; "permit break here".  Leaving as is for now, however, since
	       ;; this is not used at present. Not clear; needs more review.
	       ;; (MHD 3/9/95)
	       (loop with character-index-of-natural-break
		       = (-f *line-buffer-fill-pointer
			     (cond
			       ;; previously had to handle @<char>, too, but no more
			       (text-break-case? 1)
			       (t 0)))
		     with number-of-adjustable-spaces-up-to-natural-break
		       = number-of-adjustable-spaces-so-far
		     with text-width-a-of-spaces
		     with text-width-b-of-spaces
		     with width-a-of-extra-indentation
		     with width-b-of-extra-indentation
		     initially
		       (setq ok-to-break? t)
		       (set-text-x text-width-a-of-spaces text-width-b-of-spaces 0)
		       (set-text-x
			 width-a-of-extra-indentation width-b-of-extra-indentation 0)
		       (if (null character?) (loop-finish))
		     ;; ordinary spaces at the very beginning of a line are not adjustable
		     do (cond
			  ((or (null character?) (ordinary-space-p character?))
			   (incff number-of-adjustable-spaces-so-far))
			  (t (if (and character? ; previously checked for @Q
				      (char=w
					character?
					#.%zero-width-joiner)) ; hmmm...
				 (setq ok-to-break? nil))
			     (if (=f number-of-adjustable-spaces-so-far
				     (-f *line-buffer-fill-pointer 1))
				 (setq number-of-adjustable-spaces-up-to-natural-break
				       (setq number-of-adjustable-spaces-so-far 0)))))
			(let ((accumulating-extra-indentation?				
				(and paragraph-or-newline-for-next-new-line?
				     (null character-index-of-last-natural-break?)
				     (loop for i
					   from (if (eq paragraph-or-newline-for-next-new-line?
							'implied-paragraph)
						    0
						    1)
					       below *line-buffer-fill-pointer
					   always (wide-character-member
						    (charw *line-buffer i)
						    '(#.%space #.%tab)))
				     ;; old way:   not generalized for tabs
;				     (=f *line-buffer-fill-pointer
;					 (case paragraph-or-newline-for-next-new-line?
;					   (implied-paragraph
;					    number-of-adjustable-spaces-so-far)
;					   (t (+f number-of-adjustable-spaces-so-far 1))))
				     )))
			  (cond
			    ((and character? (char=w character? #.%tab))
			     (let* ((a width-a-of-line-so-far)
				    (b width-b-of-line-so-far)
				    (width-of-line-so-far (text-x-to-x a b)))
			       (add-to-text-x
				 a b text-width-a-of-spaces text-width-b-of-spaces)
			       (let* ((position (text-x-to-x a b))
				      (tab-width
					(text-width-to-x
					  (word-spacing-based-tab-width
					    default-word-spacing)))
				      (next-tab-position
					(+ (- position (mod position tab-width)) tab-width)))				 
				 ;; Not perfect -- subject to roundoff error! Fix later! (MHD) 
				 (set-text-x
				   text-width-a-of-spaces text-width-b-of-spaces
				   (-w next-tab-position width-of-line-so-far))
				 ;; This should be parameterized, and possibly only done for
				 ;; ordinary spaces!  NOTE: not currently being set true for
				 ;; tabs at the beginning of a line!
				 (when accumulating-extra-indentation?
				   (setq width-a-of-extra-indentation text-width-a-of-spaces)
				   (setq width-b-of-extra-indentation text-width-b-of-spaces)))))
			    (t			     
			     (incf-text-x
			       text-width-a-of-spaces text-width-b-of-spaces
			       (cond
				 ((and character?
				       (or (char=w character? #.%zero-width-space) ; @R
					   (char=w character? #.%zero-width-joiner))) ; @Q
				  0)
				 ;; used to handle @R, @Q, and potentially others here
				 ;; do other fixed-width spaces!
				 (accumulating-extra-indentation?
				  ;; This should be parameterized!
				  (incf-text-x
				    width-a-of-extra-indentation width-b-of-extra-indentation
				    default-word-spacing)
				  default-word-spacing)
				 (t word-spacing))))))
			(progn
			  (setq character? (get-character-if-any-for-running-text))
			  (setq text-break-case? (and character? (text-break-p character?))))
		     while (or text-break-case?
			       (and character? ; previously checked for @Q here 
				    (char=w
				      character?
				      #.%zero-width-joiner)))
		     finally
		       (incff indentation-for-turnover-lines
			      (text-x-to-x
				width-a-of-extra-indentation width-b-of-extra-indentation))
		       (cond
			 (ok-to-break?			  
			  (setq character-index-of-last-natural-break?
				character-index-of-natural-break)
			  (setq character-index-after-last-natural-break
				(if (null character?)
				    *line-buffer-fill-pointer
				    (-f *line-buffer-fill-pointer
					1)))
			  (setq last-natural-break-is-all-ordinary-spaces?
				(loop for i from character-index-of-natural-break
				      below character-index-after-last-natural-break
				      always (ordinary-space-p (charw *line-buffer i)))
				;; ... replaces:
;				;; Determining this is a bit of a hack: if the number
;				;; of spaces is equal to the number simple characters,
;				;; then we assume they're all "ordinary" -- depends on
;				;; our knowledge that "ordinary" spaces are simple
;				;; characters, and the rest are @-complex characters.
;				(=f (-f number-of-adjustable-spaces-so-far
;					number-of-adjustable-spaces-up-to-natural-break)
;				    (-f character-index-after-last-natural-break
;					character-index-of-natural-break))
				)
			  (if (=f number-of-adjustable-spaces-so-far
				  character-index-after-last-natural-break)
			      ;; case of a line of all spaces, ended by a line break
			      (setq number-of-adjustable-spaces-up-to-natural-break
				    (setq number-of-adjustable-spaces-so-far 0)))
			  (setq number-of-adjustable-spaces-up-to-last-natural-break
				number-of-adjustable-spaces-up-to-natural-break)
			  (setq number-of-adjustable-spaces-through-last-natural-break
				number-of-adjustable-spaces-so-far)
			  (setq width-a-of-line-up-to-last-natural-break
				width-a-of-line-so-far)
			  (setq width-b-of-line-up-to-last-natural-break
				width-b-of-line-so-far)))
		       (add-to-text-x
			 width-a-of-line-so-far width-b-of-line-so-far
			 text-width-a-of-spaces text-width-b-of-spaces)
		       (cond
			 (ok-to-break?
			  (setq width-a-of-line-through-last-natural-break
				width-a-of-line-so-far)
			  (setq width-b-of-line-through-last-natural-break
				width-b-of-line-so-far)
			  (if context-stack-at-last-natural-break?
			      (reclaim-slot-value-tree context-stack-at-last-natural-break?))
			  (if context-stack
			      (setq context-stack-at-last-natural-break?
				    (copy-tree-using-slot-value-conses context-stack)))))))
	   (cond
	     ((or (and (null character?)
		       (or (>f *line-buffer-fill-pointer 0)
			   (null		; end-of-text test, for empty text case only
			     *explicit-paragraph-or-newline?)
			   (=f line-index-for-next-new-line 1)))  ; ?? (@L or @P to 2nd line)
		  (and (>w (text-x-to-x width-a-of-line-so-far width-b-of-line-so-far)
			   maximum-line-width)	; assume not entirely spaces
		       (or ok-to-break?
			   ;; most standard word wrap case: space typed beyond
			   ;; the width boundary:
			   (if character-index-of-last-natural-break?  ; UNTIL WORDS GET BROKEN!
			       text-break-case?))))
	      (let* ((add-hyphen?
		       (cond
			 ((or (null character-index-of-last-natural-break?)
			      (>w (incremented-text-x-as-x 
				    width-a-of-line-up-to-last-natural-break
				    width-b-of-line-up-to-last-natural-break
				    (*f (-f (maximum-word-spacing text-box-format)
					    word-spacing)
					number-of-adjustable-spaces-up-to-last-natural-break))
				  minimum-line-width))
			  ;; hyphenate, if possible, and return non-nil if do
			  ;; in any case, fix natural break vars
			  nil)))
		     (lost-spaces-element?
		       (if (not add-hyphen?)
			   (let ((number-of-characters-in-natural-break
				   (-f character-index-after-last-natural-break
				       character-index-of-last-natural-break?)))
			     (if (or (not last-natural-break-is-all-ordinary-spaces?)
				     (not (=f (-f character-index-after-last-natural-break
						  character-index-of-last-natural-break?)
					      1)))
				 (make-lost-spaces-text-element
				   (if last-natural-break-is-all-ordinary-spaces?
				       number-of-characters-in-natural-break
				       (let ((s (make-wide-string
						  number-of-characters-in-natural-break)))
					 (copy-portion-of-wide-string-into-wide-string
					   *line-buffer
					   character-index-of-last-natural-break?
					   (+f character-index-of-last-natural-break?
					       number-of-characters-in-natural-break)
					   s 0)
					 s)))))))
		     (new-text-line
		       (obtain-text-string
			 (if add-hyphen?
			     (+f character-index-of-last-natural-break? 1)
			     character-index-of-last-natural-break?))))
		(setq word-spacing
		      (if (eq line-justification? 'justified)
			  (maxw
			    (minimum-word-spacing text-box-format)
			    (minw (maximum-word-spacing text-box-format)
				  (roundw
				    (-w (convert-to-text-width line-measure)
					(text-x-to-text-width
					  width-a-of-line-up-to-last-natural-break
					  width-b-of-line-up-to-last-natural-break))
				    number-of-adjustable-spaces-so-far)))
			  default-word-spacing))
		(copy-portion-of-wide-string-into-wide-string 	; copy into new line
		  *line-buffer 0 character-index-of-last-natural-break?
		  new-text-line 0)
		(if add-hyphen?
		    (setf (charw new-text-line character-index-of-last-natural-break?) #.%\-))
		(if (or put-in-indentations-and-widths?
			(not (=f indentation-for-next-new-line
				 current-indentation-for-new-lines)))
		    (setq reversed-new-text-segment
			  (slot-value-cons indentation-for-next-new-line
					   reversed-new-text-segment)))
		(setq current-indentation-for-new-lines indentation-for-next-new-line)
		(if context-stack
		    (setq reversed-new-text-segment
			  (slot-value-cons
			    (slot-value-cons
			      'context-carryover
			      (copy-tree-using-slot-value-conses context-stack))
			    reversed-new-text-segment)))
		(if (and (>f number-of-adjustable-spaces-up-to-last-natural-break 0)  ; nec?
			 (not (=f word-spacing default-word-spacing)))			 
		    (setq reversed-new-text-segment
			  (slot-value-cons
			    (slot-value-cons 'word-spacing word-spacing)
			    reversed-new-text-segment)))
		(if (or lost-spaces-element? add-hyphen?)
		    (setq reversed-new-text-segment
			  (slot-value-cons
			    (or lost-spaces-element?
				(slot-value-list 'hyphen-added))
			    reversed-new-text-segment)))
		(let ((line-width
			(if x-magnification?	; FIX FOR WORD SPACING!
			    (magnified-text-x-as-x
			      width-a-of-line-up-to-last-natural-break
			      width-b-of-line-up-to-last-natural-break
			      x-magnification?)
			    (text-x-to-x
			      width-a-of-line-up-to-last-natural-break
			      width-b-of-line-up-to-last-natural-break))))
		  (if (>f line-width width-of-longest-new-line)
		      (setq width-of-longest-new-line line-width))
		  (if put-in-indentations-and-widths?
		      (setq reversed-new-text-segment
			    (slot-value-cons
			      (slot-value-cons 'line-width line-width)
			      reversed-new-text-segment))))
		(setq reversed-new-text-segment
		      (slot-value-cons new-text-line reversed-new-text-segment))
		

		;; Copy-portion-of-wide-string-into-wide-string is spec'd as
		;; OK around overlapping EQ strings ("memmove semantics")
		;; (MHD 6/11/96)
		(copy-portion-of-wide-string-into-wide-string
		  *line-buffer
		  character-index-after-last-natural-break
		  *line-buffer-fill-pointer
		  *line-buffer
		  0)
		(setq *line-buffer-fill-pointer
		      (-f *line-buffer-fill-pointer
			  character-index-after-last-natural-break))
		
		(incff line-index-for-next-new-line)
		(setq paragraph-or-newline-for-next-new-line? nil)
		(setq indentation-for-next-new-line indentation-for-turnover-lines)
		(when (and text-tail-for-reformatting-only-for-change?
			   (>f *line-index
			       (or *line-index-past-deletion? *line-index-of-change?))
			   (or (and (null character?)	           ; is this redundant?
				    *explicit-paragraph-or-newline?  ; not end-of-text
				    (=f *line-buffer-fill-pointer 0))
			       (and (=f indentation-for-next-new-line *current-indentation)
				    character? ; reading a newline, paragraph, or end of text
					;   doesn't increment *character-index,
					;   making the following test invalid. Bug
					;   fix. (MHD/PGA 3/14/95)
				    (=f *line-buffer-fill-pointer *character-index))))
		  (loop-finish))		; the rest would format the same as before
		(decff number-of-adjustable-spaces-so-far
		       number-of-adjustable-spaces-through-last-natural-break)
		(subtract-from-text-x
		  width-a-of-line-so-far width-b-of-line-so-far
		  width-a-of-line-through-last-natural-break
		  width-b-of-line-through-last-natural-break)
		(incf-text-x
		  width-a-of-line-so-far width-b-of-line-so-far
		  (convert-to-text-width indentation-for-turnover-lines))
		(setq character-index-of-last-natural-break? nil))))
	   (cond
	     ((null character?)
	      ;; This is the case of hitting the end of a line, or the end of
	      ;; text.  Forget the last natural break in this case.  (Not doing
	      ;; so was a bug in 3.0, causing the "pumping" of long lines
	      ;; without natural breaks after a newline. (MHD 3/10/95))
	      (setq character-index-of-last-natural-break? nil)
	      (cond
		((>f *line-buffer-fill-pointer 0)
		 (setq get-character? nil))
		((null *explicit-paragraph-or-newline?)	; end-of-text test
		 (setq *this-text-tail? *next-text-tail?)
		 (incff *line-index)
		 (loop-finish))
		(t (progn
		     (setf (charw *line-buffer 0) ; old @L/@P case
			   (case *explicit-paragraph-or-newline?
			     (paragraph #.%paragraph-separator)
			     (newline #.%line-separator)
			     (linefeed #.%linefeed)
			     (t #.%return))) ; old: return
		     (setq *line-buffer-fill-pointer 1))
		   (setq paragraph-or-newline-for-next-new-line?
			 *explicit-paragraph-or-newline?)
		   (setq indentation-for-next-new-line
			 (case line-justification?
			   ((center right) 0)	; handle indentations properly (someday)!
			   (t (if paragraph-or-newline-for-next-new-line?
				  (case paragraph-or-newline-for-next-new-line?
				    ((newline return linefeed) 0)
				    (t (text-cell-paragraph-indentation text-box-format)))
				  indentation-for-turnover-lines))))
		   (setq indentation-for-turnover-lines
			 (case line-justification?
			   ((center right) 0)	; handle indentations properly (someday)!
			   (t (text-cell-turnover-line-indentation text-box-format))))
		   (set-text-x
		     width-a-of-line-so-far width-b-of-line-so-far
		     indentation-for-next-new-line)
		   (setq get-character? t))))
	     (text-break-case?			; this HAD extended beyond maximum-line-width
	      (setq get-character? nil))
	     ((newline-p character?)	; possible?!  handle others?! (MHD 11/18/95)
					; "formatting-character-p" ?!
	      (case character?
		((nil)))			; handle all format directives!
	      (setq get-character? t))
	     (nil
					; (eql character? #.%tab) ; Handle Tab properly! Maybe not here!
					; At a minimum, a Unicode application must pass them through as
					; "blob"/unimplemented characters

	      ;; An approach:

	      ;; note where the next tab stop is;
	      ;; 
	      ;; end the line so far;
	      ;; 
	      ;; put in one-shot indentation to the next tab stop;
	      ;; 
	      ;; put in one-shot 0-width line spacing;
	      ;; 
	      ;; start the new line;
	      ;; 
	      ;; ...
	      ;; 
	      ;; after this line, revert indentation and line spacing
	      ;;
	      ;; [main problem: this breaks any definition/assumption of each
	      ;; text line being a whole line of text (e.g.,
	      ;; find-text-tail-for-line); instead, it could be just a segment
	      ;; of a line of text; perhaps the name text-line should be changed
	      ;; to text-line-segment, and/or say that text-line is "just short
	      ;; for" text-line-segment.]
	      ;; 
	      ;; [alternative is to have a map of tab stops sent over
	      ;; the wire, as we send the width of a space.  Seems easier
	      ;; in some ways, but requires change to the ICP layer.]
	      )
	     (t				; printing character case
	      (cond			; natural break between hyphen and alpha char
		((and (>f *line-buffer-fill-pointer 2)    ; previous-character, for speed!
		      (char=w (charw *line-buffer (-f *line-buffer-fill-pointer 2)) #.%\-)
		      (alpha-numeric-p	; new: require alphanumeric char before the minus sign/hyphen
			(charw		;   to avoid break after unary - (e.g., -43.0) (MHD 7/13/99)
			  *line-buffer (-f *line-buffer-fill-pointer 3)))
		      (alpha-numeric-p character?)
		      (or (null character-index-of-last-natural-break?)  ; UNTIL WORDS GET BROKEN!
			  (<=w (text-x-to-x width-a-of-line-so-far width-b-of-line-so-far)
			       maximum-line-width)))

		 ;; NOTE: Now that I've added check-for-hyphen-more-closely, there's
		 ;; a new bug: the kana region is not updated when a new line starts
		 ;; due to the hyphen.  FIX!!!!! Bombs out.  Recipe:
		 ;;
		 ;;   New Workspace
		 ;;   New Free Text
		 ;;   Type "a" 36 times in English mode
		 ;;   Ctrl-K, Ctrl-K [Katakana Mode]
		 ;;   type suteitasu from keyboard
		 ;;   Ctrl-K, Ctrl-K [English Mode]
		 ;;   type a hyphen (-)
		 ;;   Ctrl-K, Ctrl-K [Katakana Mode]
		 ;;   su  
		 ;;   -- now notice that you have "s" followed by a
		 ;;   wrong katakana character instead of a single
		 ;;   correct katakana character, the one you got
		 ;;   above; also notice by looking at the current
		 ;;   edit state that the beginning of kana region is
		 ;;   at the end of the first line, instead of at the
		 ;;   beginning of the second.
		 ;;   (MHD 9/16/91)
		 
		 (setq character-index-of-last-natural-break?	; macro for all this?
		       (-f *line-buffer-fill-pointer 1))
		 (setq character-index-after-last-natural-break
		       character-index-of-last-natural-break?)
		 (setq last-natural-break-is-all-ordinary-spaces? t)
		 (setq number-of-adjustable-spaces-up-to-last-natural-break
		       number-of-adjustable-spaces-so-far)
		 (setq number-of-adjustable-spaces-through-last-natural-break
		       number-of-adjustable-spaces-so-far)
		 (setq width-a-of-line-up-to-last-natural-break
		       width-a-of-line-so-far)
		 (setq width-b-of-line-up-to-last-natural-break
		       width-b-of-line-so-far)
		 (setq width-a-of-line-through-last-natural-break
		       width-a-of-line-so-far)
		 (setq width-b-of-line-through-last-natural-break
		       width-b-of-line-so-far)
		 (if context-stack-at-last-natural-break?
		     (reclaim-slot-value-tree context-stack-at-last-natural-break?))
		 (setq context-stack-at-last-natural-break?
		       (copy-tree-using-slot-value-conses context-stack))))
	      ;; Here's the most normal case: a non-whitespace character in running
	      ;; text:
	      (incf-text-x
		width-a-of-line-so-far width-b-of-line-so-far
		(get-unicode-set-width-as-text-width character? ab-font))
	      (setq get-character? t)))
	finally
	  (reclaim-text-line *line-buffer)
	  (if context-stack
	      ;;;-rdf, 11/9/94
	      (reclaim-slot-value-tree context-stack))
	  (if context-stack-at-last-natural-break?
	      (reclaim-slot-value-tree context-stack-at-last-natural-break?))
	  (return
	    (values
	      (nreverse reversed-new-text-segment)
	      width-of-longest-new-line
	      initial-text-tail
	      (if (not (eq *this-text-tail? initial-text-tail))
		  *this-text-tail?)
	      initial-line-index
	      line-index-for-next-new-line
	      *line-index))))

;; Reclaim number conses!




;;; Check-for-hyphen-more-closely checks if the character before the one
;;; pointed to by line-buffer-fill-pointer in line-buffer is really the
;;; simple character hyphen (#.%\-), as opposed to an escape sequence which
;;; might happen to have a hyphen embedded within it.  Returns true if it's
;;; a simple hyphen; otherwise, nil.

(defun check-for-hyphen-more-closely (line-buffer line-buffer-fill-pointer)  
  (loop with character-in-string?
	with escape-character-in-string?
	with next-character-index
	as previous-character-in-string?
	   = nil then character-in-string?
	as previous-escape-character-in-string?
	   = nil then escape-character-in-string?
	for i = 0 then next-character-index
	while (and (<f i line-buffer-fill-pointer)
		   (multiple-value-setq
		       (character-in-string?
			 next-character-index)
		     (find-next-character-in-text-line
		       i line-buffer)))
	when (=f next-character-index line-buffer-fill-pointer)
	  return
	  (eqlw previous-character-in-string? #.%\-)))

;; The "escape-character-" args are obsolete -- from gensym-encoding days --
;; clean up!

;; This is just a subfunction of reformat-text.




;;; `Get-character-if-any-for-running-text' makes use of a large set of special
;;; variables, which are listed above.  It returns either nil, on an end-of-text
;;; or a (forced) paragraph, newline, linefeed, or return, with
;;; *explicit-paragraph-or-newline? set appropriately, or a wide character.

;; Previously returned the following three values.  But the second is obsolete as
;; of the switch to wide strings as the implementation of text strings, and the
;; third can just as easily be computed by the caller.  Now, by returning just
;; one value, we can make this a simple compiled function.
;;
;;    (1) a wide character
;;    (2) nil (an irrelevant/historic value -- used to be 
;;        either nil or the escape character beginning a complex
;;        character); and
;;    (3) either nil or non-nil for a character that's text-break-p
;;        (historically, a `text break character' (an ordinary space, @W, @X,
;;        @Y, or @R)).
;; The first value is usually nil or the next simple character, but for a complex
;; character beginning with @ or ~, it is the character after the @ or ~, and for any
;; other complex character, it is the appropriate character code.  Except when nil is
;; returned, the simple or complex character is also added to *line-buffer.

;; (prior to wide strings:
;; (@W, @X, and @Y are more-than-very-thin fixed-width spaces, and @R is a permit-line-
;; break-here character.))

(defun-simple get-character-if-any-for-running-text ()
  (loop with indentation-if-new?
	with character
	do (cond  
	     ((if *line-index-of-change?
		  (and (=f *character-index *character-index-of-change?)
		       (=f *line-index *line-index-of-change?)))
	      ;; we're at the position of a change
	      (cond
		((and *character-index-in-string-to-insert?
		      (<f *character-index-in-string-to-insert?
			  (text-line-length *string-to-insert?)))	; var for this?
		 ;; we're within a text string being inserted
		 (setq character
		       (read-character-from-wide-string
			 *string-to-insert?
			 *character-index-in-string-to-insert?))
		 (loop-finish)))
	      (cond
		(*line-index-past-deletion?
		 ;; if we're here, we didn't finish the loop above -- notice the
		 ;; (loop-finish); so we're now past the string to insert, and the
		 ;; job now is to skip past characters being deleted
		 (loop until (=f *line-index *line-index-past-deletion?)
		       do (multiple-value-setq
			    (*text-line *line-length *lost-space-at-end-of-line
			     *next-text-tail? indentation-if-new?)
			    (get-next-text-line *next-text-tail?))
			  ; (setq *text-line-is-simple? nil) ; irrelevant for wide strings!
			  (if indentation-if-new?
			      (setq *current-indentation indentation-if-new?))
			  (incff *line-index))
		 (setf *character-index *character-index-past-deletion?)))))
	   ;; what's past here must advance *character-index
	   (cond
	     ((null *line-length)
	      (return (setq *explicit-paragraph-or-newline? nil)))
	     ((>=f *character-index *line-length)
	      ;; we have no more characters explicitly in this line, but there
	      ;; may be lost spaces to go through; if it's time to go to the
	      ;; next line, this will advance the position to there, and loop
	      ;; again, unless it sees there's no more text, in which case it
	      ;; returns nil; in any other case, it does a loop-finish, which
	      ;; returns a character; see finally clause
	      (cond
		((<f (-f *character-index *line-length)
		     (if (fixnump *lost-space-at-end-of-line)
			 *lost-space-at-end-of-line
			 (text-line-length *lost-space-at-end-of-line)))
		 (setq character
		       (if (fixnump *lost-space-at-end-of-line)
			   #.%space
			   (charw *lost-space-at-end-of-line
				  (-f *character-index *line-length))))
		 (incff *character-index)
		 (loop-finish)))
	      ;; if we're here, it's time to go to the next line
	      (if (null *next-text-tail?)
		  (return (setq *explicit-paragraph-or-newline? nil)))
	      ;; if we're here, we didn't reach the end of the text; advance
	      ;; to the next line:
	      (setq *this-text-tail? *next-text-tail?)
	      (incff *line-index)
	      (setq *character-index 0)
	      (multiple-value-setq
		  (*text-line *line-length *lost-space-at-end-of-line
		   *next-text-tail? indentation-if-new?)
		  (get-next-text-line *next-text-tail?))
	      (setq *text-line-is-simple? nil)
	      (if indentation-if-new?
		  (setq *current-indentation indentation-if-new?)))
	     (t (setq character
		      (read-character-from-wide-string
			*text-line *character-index))
		(loop-finish)))
	finally
	  (wide-character-case character
	    (#.%paragraph-separator
	       (setq *explicit-paragraph-or-newline? 'paragraph)
	       (return nil))
	    (#.%line-separator
	       (setq *explicit-paragraph-or-newline? 'newline)
	       (return nil))
	    (#.%return
	       (setq *explicit-paragraph-or-newline? 'return)
	       (return nil))
	    (#.%linefeed
	       (setq *explicit-paragraph-or-newline? 'linefeed)
	       (return nil)))
	  (write-into-line-buffer
	    character *line-buffer *line-buffer-fill-pointer *line-buffer-limit)
	  (return				; return from within a let
	    character)))

;; Implement this as a macro with subfunctions for the unusual cases!  (As of 5/7/88, it
;; is called only in two places within reformat-text.)  When this is done, certain special
;; variables can be made non-special.

;; Try to simplify this!

;; Consider having this, when it does not return nil, always return a character code.

;; Consider having @P and @L added to *line-buffer, with appropriate revisions to callers.



;;; `Determine-corrected-text-position-if-necessary' determines the line and character
;;; index for a text position that will be correct after the text is changed and/or
;;; reformatted.

;;; Old-line-index and old-character-index specify the text position prior to changing
;;; and/or reformatting.  Old-text-tail and new-text-tail are corresponding tails of
;;; the text (before and after changing and/or reformatting, respectively); these tails,
;;; whose line index is given by line-index-of-tails, must contain the text position.

;;; If line-index-where-difference-starts? is specified, a corrected text position is
;;; determined only if the text position is after the position specified by
;;; line-index-where-difference-starts? and character-index-where-difference-starts?
;;; (or at that position if there is an insertion and choose-right-end-of-insertion? is
;;; specified).  If choose-right-end-of-insertion? is specified and there is an
;;; insertion (i.e., an insertion or replacement change to be made), the corrected text
;;; position will be at the right end of the insertion if the old text position was
;;; within the insertion.

;;; When there is a change to be made to the text, that change will be specified by
;;; line-index-of-change?, character-index-of-change?, line-index-past-deletion?,
;;; character-index-past-deletion?, and string-to-insert?.  See change-edit-box
;;; in EDIT.

;;; When a corrected text position is determined, three values are returned: the new
;;; line index, the new character index, and the corresponding text tail.  Otherwise,
;;; nil is returned.

(defun determine-corrected-text-position-if-necessary
    (old-line-index old-character-index
		    new-text-tail old-text-tail line-index-of-tails
		    &optional line-index-where-difference-starts?
		    character-index-where-difference-starts?
		    choose-right-end-of-insertion?
		    line-index-of-change? character-index-of-change?
		    line-index-past-deletion? character-index-past-deletion?
		    string-to-insert?)
  (when (or (null line-index-where-difference-starts?)
	    (>f old-line-index line-index-where-difference-starts?)
	    (and (=f old-line-index line-index-where-difference-starts?)
		 (or (null character-index-where-difference-starts?)
		     (>f old-character-index character-index-where-difference-starts?)
		     (if (and choose-right-end-of-insertion? string-to-insert?)
			 (=f old-character-index
			     character-index-where-difference-starts?)))))
    (cond			       ; if within deletion or replacement, move to beg.
      ((and line-index-past-deletion?  ;   thereof (for ellipsis & marked region cases)
	    (or (>f old-line-index line-index-of-change?)
		(and (=f old-line-index line-index-of-change?)
		     (>f old-character-index character-index-of-change?)))
	    (not (or (>f old-line-index line-index-past-deletion?)
		     (and (=f old-line-index line-index-past-deletion?)
			  (>=f old-character-index character-index-past-deletion?)))))
       (setq old-line-index line-index-of-change?)	; put past if closer to there?
       (setq old-character-index character-index-of-change?)))
    (loop with number-of-characters-passed = 0	; can be negative
	  with text-line			; not really used
	  with line-length
	  with lost-space-at-end-of-line
	  with line-index = line-index-of-tails
	  with next-text-tail? = old-text-tail
	  with this-text-tail
	  do (cond
	       ((and line-index-of-change?
		     (=f line-index line-index-of-change?)
		     (or (>f old-line-index line-index-of-change?)	; past the change?
			 (>f old-character-index character-index-of-change?)
			 (and string-to-insert?
			      choose-right-end-of-insertion?
			      (=f old-line-index line-index-of-change?)
			      (=f old-character-index character-index-of-change?))))
		(cond
		  ((and line-index-past-deletion?
			(not (and string-to-insert?  ; redundant and overly complex!
				  choose-right-end-of-insertion?
				  (=f old-line-index line-index-of-change?)
				  (=f old-character-index character-index-of-change?))))
		   (incff number-of-characters-passed character-index-of-change?)
		   (loop until (=f line-index line-index-past-deletion?)
			 do (multiple-value-setq	; only useful for next-text-tail?
				(text-line line-length
					   lost-space-at-end-of-line next-text-tail?)
			      (get-next-text-line next-text-tail?))
			    (incff line-index))
		   (decff number-of-characters-passed character-index-past-deletion?)))
		(if string-to-insert?
		    (incff number-of-characters-passed
			   (text-line-length string-to-insert?)))))
	     (cond
	       ((=f line-index old-line-index)
		(incff number-of-characters-passed old-character-index)
		(setq this-text-tail new-text-tail)
		(setq line-index line-index-of-tails)
		(loop with length-of-line-plus-lost-space
		      with next-next-text-tail?
		      initially
			(multiple-value-setq
			    (text-line line-length
				       lost-space-at-end-of-line next-text-tail?)
			  (get-next-text-line this-text-tail))
		      do (setq length-of-line-plus-lost-space
			       (+f line-length
				   (if (fixnump lost-space-at-end-of-line)
				       lost-space-at-end-of-line
				       (text-line-length lost-space-at-end-of-line))))
			 (cond
			   ((or (<=f number-of-characters-passed line-length)
				(<f number-of-characters-passed
				    length-of-line-plus-lost-space))
			    (loop-finish))
			   ((null next-text-tail?)
			    (if (>f number-of-characters-passed	; shouldn't ever happen
				    length-of-line-plus-lost-space)
				(setq number-of-characters-passed
				      length-of-line-plus-lost-space))
			    (loop-finish)))			       
			 (multiple-value-setq
			     (text-line line-length
					lost-space-at-end-of-line next-next-text-tail?)
			   (get-next-text-line next-text-tail?))
			 (if (and (=f number-of-characters-passed
				      length-of-line-plus-lost-space)
				  (and (>=f line-length 1)
				       (newline-p (charw text-line 0))))
			     
			     (loop-finish))
			 (decff number-of-characters-passed	; move to beg. of next line
				length-of-line-plus-lost-space)	;   if at end of lost space
			 (incff line-index)	;   and no paragraph or line separator follows
			 (setq this-text-tail next-text-tail?)
			 (setq next-text-tail? next-next-text-tail?))
		(return
		  (values line-index number-of-characters-passed this-text-tail))))
	     (multiple-value-setq
		 (text-line line-length lost-space-at-end-of-line next-text-tail?)
	       (get-next-text-line next-text-tail?))
	     (when text-line
	       (incff number-of-characters-passed
		      (+f line-length
			  (if (fixnump lost-space-at-end-of-line)
			      lost-space-at-end-of-line
			      (text-line-length lost-space-at-end-of-line))))
	       (incff line-index))
	  while text-line
	  )))

;; Simplify this!

;; It is assumed that number-of-characters-passed will remain within the fixnum range,
;; which will be the case if the number of characters in a text is always within that
;; range.

;; An optimization is possible if the text position is within a common tail of
;; old-text-tail and new-text-tail.  In this case, the text position could be
;; corrected by adding to old-line-index the difference between the line indices
;; of the common tail with respect to the old and new text tails.  This optimization
;; would require two additional arguments, line-index-past-old-text-segment and
;; line-index-past-new-text-segment.  It does not seem worthwhile.



;;; `Convert-text-to-wide-text' copies text with all text lines represented as
;;; wide strings.  If line-index? and character-index? are non-nil (both must or
;;; neither may be), this returns their equivalent values in the new text. Note
;;; that line-index? should never change.  Character-index? may change because
;;; of the switch from multiple byte to single byte representations for
;;; characters, and because it represents the physical, not the logical,
;;; character position in the multiple byte case.  This relies as well on the
;;; assumption that all characters in the initial text can be translated
;;; one-to-one with the wide characters in the wide strings.  It is an error to
;;; call this with invalid indices to begin with; the results in that case are
;;; undefined.

;;; Examples:
;;;
;;;   (convert-text-to-wide-text '("foo") 1 0)
;;;   => (#w"foo")  1  0
;;;   (convert-text-to-wide-text '("foo") 1 2)
;;;   => (#w"foo")  1  2
;;;   (convert-text-to-wide-text '("~foo") 1 2)
;;;   => (#w"\x00EAoo")  1  1
;;;   (convert-text-to-wide-text '("~f@Lo") 1 0)
;;;   => (#w"\x00EA\x2028o")  1  0
;;;   (convert-text-to-wide-text '("~f@Lo") 1 2)
;;;   => (#w"\x00EA\x2028o")  1  1
;;;   (convert-text-to-wide-text '("~f@Lo") 1 4)
;;;   => (#w"\x00EA\x2028o")  1  2
;;;   (convert-text-to-wide-text '("~f@Lo") 1 5)
;;;   => (#w"\x00EA\x2028o") 1 3

;(defun convert-text-to-wide-text (text &optional line-index? character-index?)
;  (let ((wide-text (copy-text-using-wide-strings text)))
;    (when (and line-index? character-index?)
;      (let ((text-tail (find-text-tail-for-line text line-index?))
;	    (count 0))
;	(loop with y = line-index?
;	      with x = 0
;	      while (and (=f y line-index?) ; safer, but unnec. test
;			 (<f x character-index?))
;	      do (multiple-value-setq (y x text-tail)
;		   (find-next-character-if-any y x text-tail))
;		 (incff count))
;	(setq character-index? count)))	; changes arg!
;    (values wide-text line-index? character-index?)))

;; Obsolete, and should probably never be used! (MHD 2/6/96)










;;;; Conversion Between Texts and Text Strings



;;; See also convert-raw-text-string-to-unformatted-text, in BOOKS.



;;; `Convert-text-to-text-string' returns a new text string, the content of which
;;; is all or part of the text determined by text? or text-tail?

;;; If text? is nil, then text-tail? is required. If text-tail? is non-nil, it is used,
;;; and text? is not even looked at.

;;; If beginning-line-index? is nil, it defaults to 1.  Note that when text-tail? is
;;; supplied, this does not normally want to be defaulted.  If beginning-character-index?
;;; is nil, it defaults to 0.

;;; If end-line-index? is nil, it defaults to the line index of the last line of the text.
;;; If end-character-index? is nil, it defaults to the character index of the last character
;;; in the text; if it is non-nil but end-line-index? is nil, it is constrained to be no
;;; greater than the last character index on the last line.  Note that, with the exception
;;; of end-character-index? (where end-line-index? is nil), all indices supplied are assumed
;;; to be valid.

;;; If suppress-lost-spaces-at-end is supplied true, then lost spaces at the end
;;; of text will not be returned.  Note the limitation that this does not
;;; reliably leave of all spaces at the end of the text.  For unformatted text,
;;; this cannot be used to remove all spaces, only those that are represented
;;; (internally) as lost spaces at the end of the text.  However, formatted
;;; text always has all of its spaces at the end represented as lost spaces,
;;; so for formatted text this will reliably remove all spaces at the end.

(defun convert-text-to-text-string
    (text?
      &optional text-tail? beginning-line-index? beginning-character-index?
      end-line-index? end-character-index?
      suppress-lost-spaces-at-end) ; see doc above and note below
  (twith-output-to-text-string
    (loop with beginning-line-index
	    = (or beginning-line-index? 1)
	  with beginning-character-index
	    = (or beginning-character-index? 0)
	  with text-tail
	    = (or text-tail? (find-text-tail-for-line text? beginning-line-index))
	  with end-character-index     ; may be overridden if end-line-index? is null
	    = end-character-index?
	  with end-line-index
	    = (or end-line-index?
		  (multiple-value-bind (line-index character-index)
		      (find-end-of-text text-tail beginning-line-index suppress-lost-spaces-at-end)
		    (setq end-character-index
			  (if end-character-index?
			      (minw end-character-index? character-index)
			      character-index))
		    line-index))		    
	  as line-index from beginning-line-index
	  as character-index = beginning-character-index then 0
	  with text-line
	  with line-length
	  with lost-space-at-end-of-line
	  until (or (and  (=f line-index end-line-index)
			  (>=f character-index end-character-index))
		    (>f line-index end-line-index))	; necessary??
	  do (multiple-value-setq
		 (text-line line-length lost-space-at-end-of-line text-tail
;		indentation-if-new? line-width-if-known? context-carryover?  ; handle?
			    )
	       (get-next-text-line text-tail))
	     (let* ((end
		      (if (=f line-index end-line-index)
			  end-character-index
			  (+f line-length
			      (if (fixnump lost-space-at-end-of-line)
				  lost-space-at-end-of-line
				  (text-line-length lost-space-at-end-of-line))))))
	       (twrite-portion-of-wide-string-unparsably-to-current-wide-string
		 text-line
		 (minf character-index line-length)
		 (minf end line-length))
	       (loop for i from 0
		     repeat (-f (maxf (-f end line-length) 0)
				(maxf (-f character-index line-length) 0))
		     do (twrite-wide-character
			  (if (text-string-p lost-space-at-end-of-line)
			      (charw lost-space-at-end-of-line i)
			      #.%space)))))))

(defun-simple line-begins-with-newline-p (thing)
  (when (text-string-p thing)
    (char=w (find-next-character-in-text-line 0 thing) #.%line-separator)))


(defun count-initial-spaces (text-string)
  (loop with length = (text-string-length text-string)
	with count = 0
	for i from (if (and (>f length 1) (line-begins-with-newline-p text-string)) 2 0) to (-f length 1)
	as character = (find-next-character-in-text-line i text-string)
	until
	(cond ((not (char=w character #.%\Space))
	       count)
	      (t
	       (incff count)
	       nil))
	finally
	  (return count)))


;; NOTE: Suppress-lost-spaces-at-end was added in 3.0 just so it could be used
;; for expression cells squirrelling away text while in the editor.  It remains
;; used only for that purpose, specifically by the compiler for
;; cell-expression-parse.  It always had a bug or limitation that it could only
;; operate reliably on formatted text.  For example,
;; (convert-text-to-text-string '(#w"" #w"") nil nil nil nil nil t) returns #w"
;; ", not the presumably desired result of #w"", even though the
;; suppress-lost-spaces-at-end is supplied. However, if this text had been
;; formatted, it would have become ((lost-spaces . 2) #w""), which in turn have
;; would returned the desired result of #w"".  (MHD 6/14/96)

;; Consider handling some escape characters in a special way.  For example,
;; consider, in certain modes, converting @L to a space.

;; Note that beginning-line-index? could be defaulted correctly when both text?
;; and text- tail? are supplied.  Consider doing so.

;; Consider handling lost spaces at the end by optionally not including them.





;;; `Convert-text-string-to-text-macro' ...

;;; `Convert-text-string-to-text' ...

(defmacro convert-text-string-to-text-macro (text-string)
  `(slot-value-list
     (make-lost-spaces-text-element 0)
     ,text-string))


(defun convert-text-string-to-text (text-string)
  (convert-text-string-to-text-macro text-string))

;; Modified convert-text-string-to-text to contain list-space info.  mhd (cpm),
;; 1/8/90.  Therefore, reclaim-converted-text-string-tree replaces
;; reclaim-converted-text-string-cons.

;; From 1/8/90 till today, 3/22/90, this put LIST-SPACES instead of LOST-
;; SPACES.  This maybe could have resulted, therefore, in (list-spaces . 0)
;; being put out as a text element in some KBs in some G2 2.0 Beta releases!!!
;; (MHD/CPM 3/22/90)

;; This was changed from a function to a macro and moved here from UTILITIES1
;; today. (MHD/CPM 3/22/90)



;;; `Convert-text-string-list-to-text' takes a list of text strings and returns
;;; an unformatted text, a slot value made up of fresh slot value matter, i.e.,
;;; slot value conses, symbols, text strings, etc.  The text strings in the list
;;; are absorbed into the result and become the property of this function.  The
;;; conses of the list are not owned by this function, and remain the property
;;; of the caller.
;;;
;;; The list is regarded as one long text string which is simply split into
;;; separate text strings at arbitrary points and listed.  The result will be
;;; subject to formatting, which will not, of course, change the content.
;;;
;;; For any input text string list TSL, it must be true that
;;;
;;;     (equalw (twith-output-to-text-string (loop for s in TSL do (twrite-string s)))
;;;             (convert-text-to-text-string (convert-text-string-list-to-text TSL)))

(defun convert-text-string-list-to-text (text-string-list)
  (loop for text-string in text-string-list
	collect (make-lost-spaces-text-element 0) using slot-value-cons
	collect text-string using slot-value-cons))





;;;; Finding Positions in Text



;;; `Find-text-tail-for-line' returns the text tail for the line-index line of text,
;;; or nil if there are fewer than that number of lines.

(defun find-text-tail-for-line (text line-index)
  (loop with text-tail = text
	with line-count = 0
	as l on text
	as text-element = (car l)
	do (cond
	     ((text-line-p text-element)
	      (if (=f (incff line-count) line-index)
		  (return text-tail))
	      (setq text-tail (cdr l))))))


;;; `Get-character-index-past-separator' returns 1 if the first text-line in in
;;; text-tail starts with a line or paragraph separator, otherwise 0.  See the
;;; subsection Text, above, for the conventions for placing line/paragraph
;;; separators in text lines.

(defun-simple get-character-index-past-separator (text-tail)
  (or (loop for text-element in text-tail
	    when (text-line-p text-element)
	      return (let ((length (text-line-length text-element)))
		       (if (and (>f length 0)
				(let ((char (charw text-element 0)))
				  (or (char=w char #.%line-separator)
				      (char=w char #.%paragraph-separator))))
			   1)))
      0))



;;; `Find-line-index-for-text-tail' returns the line index, offset by
;;; line-index-offset, of text-tail-to-find within text-tail-to-search. If
;;; text-tail-to-find is not a tail of text-tail-to-search, this just returns
;;; the line index, offset by line-index-offset, one past the last line of text.

(defun find-line-index-for-text-tail
       (text-tail-to-search text-tail-to-find line-index-offset)
  (loop with line-count = line-index-offset
	as candidate-text-tail on text-tail-to-search
	when (eq candidate-text-tail text-tail-to-find)
	  return line-count
	when (text-line-p (car candidate-text-tail))
	  do (incff line-count)
	finally (return line-count)))



;;; `Find-text-tail-and-indentation-for-line' returns either two values, the text tail and
;;; the indentation for the line-index line of text, or else nil if there are fewer than
;;; that number of lines.

(defun find-text-tail-and-indentation-for-line (text line-index)
  (loop with text-tail = text
	with indentation = 0
	with line-count = 0
	as l on text
	as text-element = (car l)
	do (cond
	     ((text-line-p text-element)
	      (if (=f (incff line-count) line-index)
		  (return (values text-tail indentation)))
	      (setq text-tail (cdr l)))
	     ((fixnump text-element)
	      (setq indentation text-element)))))

;; Consider having this replace find-text-tail-for-line, a strict subset of this
;; function, even though this is a bit slower.




;;; `Advance-text-tail' returns the text tail that is number-of-lines lines past
;;; text-tail, or nil if there are fewer than that number of lines.

(defun advance-text-tail (text-tail number-of-lines)
  (loop with line-count = 0
	as l on text-tail
	as text-element = (car l)
	do (cond
	     ((text-line-p text-element)
	      (if (=f line-count number-of-lines)
		  (return text-tail))
	      (incff line-count)
	      (setq text-tail (cdr l))))))	; changes arg



;;; `Get-next-text-line' returns seven values: 
;;;    (1) the next text line;
;;;    (2) its length (minus one if there was a hyphen added at the end of the line);
;;;    (3) the lost space (an integer, maybe 0, or a text string) at the end of the line;
;;;    (4) the next text tail (beyond the next line);
;;;    (5) an explicit indentation for this line, or else nil
;;;    (6) the line width, if there is a line-width element for the line, or else nil; and
;;;    (7) the "context carryover" for the next line.
;;;  It is assumed that text tail has a next line.

(defun get-next-text-line (text-tail)
  (loop with hyphen-added-at-end-of-line? = nil
	with lost-space-at-end-of-line = 1
	with context-carryover? = nil
	with explicit-indentation? = nil
	with line-width?
	with lost-spaces-value?
	as l on text-tail
	as text-element = (car l)
	do (cond
	     ((text-line-p text-element)
	      (return
		(values text-element
			(if hyphen-added-at-end-of-line?
			    (-f (text-line-length text-element) 1)
			    (text-line-length text-element))
			lost-space-at-end-of-line
			(cdr l)
			explicit-indentation?
			line-width?
			context-carryover?)))
	     ((setq lost-spaces-value? (lost-spaces-value-if-any text-element))
	      (setq lost-space-at-end-of-line lost-spaces-value?))
	     ((consp text-element)
	      (case (car text-element)
		(hyphen-added
		 (setq hyphen-added-at-end-of-line? t)
		 (setq lost-space-at-end-of-line 0))
		(line-width
		 (setq line-width? (cdr text-element)))
		(context-carryover
		 (setq context-carryover? (cdr text-element)))))
	     (t (setq explicit-indentation? text-element)))))	; only other case



;;; `Find-end-of-text' returns three values:
;;;    (1) the line index of the end of text;
;;;    (2) the character index of the end of text; and
;;;    (3) the text tail for the returned text position.

(defun find-end-of-text (text-tail line-index &optional suppress-lost-spaces-at-end?)
  (loop with line-length
	with lost-space-at-end-of-line
	with next-text-tail?
	do (multiple-value-setq-some
	     (nil line-length lost-space-at-end-of-line next-text-tail?)
	     (get-next-text-line text-tail))
	while next-text-tail?
	do (setq text-tail next-text-tail?)	; these change args
	   (incff line-index)
	finally
	  (return
	    (let ((line-length-plus-lost-space
		    (+f line-length
			(if suppress-lost-spaces-at-end? 0
			    (if (fixnump lost-space-at-end-of-line)
				lost-space-at-end-of-line
				(text-line-length lost-space-at-end-of-line))))))
	      (values line-index line-length-plus-lost-space text-tail)))))


;;; `Find-end-of-line-of-text' returns the character index of the end of the
;;; current line of text.

(defun-simple find-end-of-line-of-text (text-tail suppress-lost-spaces-at-end?)
  (multiple-value-bind (text-line line-length lost-space-at-end-of-line)
      (get-next-text-line text-tail)
    (declare (ignore text-line))
    (+f line-length
	(if suppress-lost-spaces-at-end? 0
	    (if (fixnump lost-space-at-end-of-line)
		lost-space-at-end-of-line
		(text-line-length lost-space-at-end-of-line))))))




;;; `Find-next-character-if-any' returns either nil (on end-of-text) or four
;;; values:
;;;
;;;    (1) the line index past the next character;
;;;    (2) the character index past the next character;
;;;    (3) the text tail for the returned text position;
;;;    (4) a wide character
;;;
;;; The fourth value is the character gone past.

;;; If the character gone past is at the very end of a line (including lost
;;; space), the returned text position will be either the very end of the line,
;;; if the line has no lost space or is at the end of a paragraph, or else the
;;; very beginning of the next non-empty (including lost space) line.  (Note
;;; that both paragraph and line separator characters are regarded as
;;; beginning-of-paragraph complex characters.)

;;; Find-next-character-if-any is not particularly fast.

(defun find-next-character-if-any
    (line-index character-index text-tail)
  (loop with unicode-wide-character? = nil
	with line-index-past-character
	with character-index-past-character
	with text-tail-past-character
	with text-line
	with line-length
	with lost-space-at-end-of-line
	with next-text-tail?
	with line-length-plus-lost-space
	do (multiple-value-setq
	       (text-line line-length lost-space-at-end-of-line next-text-tail?)
	     (get-next-text-line text-tail))
	   (setq line-length-plus-lost-space
		 (+f line-length
		     (if (fixnump lost-space-at-end-of-line)
			 lost-space-at-end-of-line
			 (text-line-length lost-space-at-end-of-line))))
	   (cond
	     ((<f character-index line-length-plus-lost-space) ; old @P/@L case	      
	      (cond
		(unicode-wide-character?
		 (cond
		   ((not (and (>=f line-length 1)
			      (newline-p (charw text-line 0))))
		    (setq line-index-past-character line-index)
		    (setq character-index-past-character 0)
		    (setq text-tail-past-character text-tail)))
		 (loop-finish)))
	      (setq unicode-wide-character?
		    (read-unicode-character-from-wide-string-with-lost-spaces
		      text-line character-index
		      line-length lost-space-at-end-of-line))
	      (setq line-index-past-character line-index)
	      (setq character-index-past-character character-index)
	      (setq text-tail-past-character text-tail)
	      (if (or (<f character-index line-length-plus-lost-space)
		      (=f line-length-plus-lost-space line-length))
		  (loop-finish))))
	   (if (null next-text-tail?) (loop-finish))
	   (setq text-tail next-text-tail?)	; changes arg, possibly to nil
	   (incff line-index)
	   (setq character-index 0)
	finally
	  (if unicode-wide-character?
	      (return
		(values line-index-past-character
			character-index-past-character
			text-tail-past-character
			unicode-wide-character?)))))

;; For the sake of efficiency, consider having as arguments (in lieu of text-tail)
;; text-line, line-length, lost-space-at-end-of-line, and next-text-tail?.

;; There should never be totally empty lines, except for the first in a text!  Therefore,
;; this and the following function need never move past more than one line break!!!



;;; `Find-previous-character-if-any' returns either nil (on a beginning-of-text) or
;;; four values:
;;;
;;;    (1) the line index past the previous character;
;;;    (2) the character index past the previous character;
;;;    (3) the text tail for the returned text position;
;;;    (4) a wide character
;;;
;;; The fourth value is the character gone past.

;;; If the character gone past either is a beginning-of-paragraph character or
;;; is at the very beginning of a line where the previous non-empty line had no
;;; lost space, then the returned text position will be the very end of the
;;; previous non-empty line.  Otherwise the returned text position will be just
;;; before (in the same line as) the returned character.  (Note that this is
;;; precisely the inverse of what find-next- character-if-any does.  Note also
;;; that a line with lost space is not "empty".)

;;; Find-previous-character-if-any is not particularly fast.

(defun find-previous-character-if-any
       (line-index character-index text-tail text)	; 1st two args changed below
  (loop with unicode-wide-character? = nil
	with line-index-past-character
	with character-index-past-character
	with text-tail-past-character
	with text-line
	with line-length
	with lost-space-at-end-of-line
	with previous-character-index
	initially
	  (cond
	    ((>f character-index 0)	      
	     (multiple-value-setq (text-line line-length
				   lost-space-at-end-of-line)
                 (get-next-text-line text-tail))))
	do (cond
	     ((>f character-index 0)	; old @L/@P case
	      (cond
		(unicode-wide-character?
		 (cond
		   ((or (newline-p unicode-wide-character?)
			(eql lost-space-at-end-of-line 0))
		    (setq line-index-past-character line-index)	; could return directly
		    (setq character-index-past-character character-index)
		    (setq text-tail-past-character text-tail)))
		 (loop-finish)))
	      (setq previous-character-index (-f character-index 1))
	      (setq character-index previous-character-index)
	      (setq unicode-wide-character?
		    ;; NOTE: lost-space-at-end-of-line must not be NIL when goes here.
		    (read-unicode-character-from-wide-string-with-lost-spaces
		      text-line character-index
		      line-length lost-space-at-end-of-line))
	      
	      (setq character-index previous-character-index)
	      (setq line-index-past-character line-index)
	      (setq character-index-past-character character-index)
	      (setq text-tail-past-character text-tail)
	      (if (>f character-index 0)
		  (loop-finish))))
	   (if (=f line-index 1) (loop-finish))
	   (decff line-index)
	   (setq text-tail (find-text-tail-for-line text line-index))
	   (multiple-value-setq (text-line line-length lost-space-at-end-of-line)
	       (get-next-text-line text-tail))
	   (setq character-index
		 (+f line-length
		     (if (fixnump lost-space-at-end-of-line); what if it's NIL?
			 lost-space-at-end-of-line
			 (text-line-length lost-space-at-end-of-line))))
	finally
	  (if unicode-wide-character?
	      (return
		(values line-index-past-character
			character-index-past-character
			text-tail-past-character
			unicode-wide-character?)))))

;; Fixnump test above used to be integerp.  I changed it here and throughout
;; this module upon learning that fixnum is inlined, while integerp is a function 
;; call (in Chestnut).  This is ok, althought ideally, both would be inlined, 
;; I think. (MHD 6/4/92)

;; This is inefficient if text-being-edited could have a very large number of lines.

;; For the sake of efficiency, consider having as additional arguments text-line,
;; line-length, and lost-space-at-end-of-line.





;;;; Source Code Positions


;;; The function `convert-to-non-word-wrapped-text' converts a text to
;;; an equivalent non-word-wrapped text.  If line-index? and character-index?
;;; are supplied non-nil, they are converted to their equivalents with respect
;;; to the non-word-wrapped text.
;;;
;;; The function `convert-to-non-word-wrapped-text-position' simply converts a
;;; source code position (line-index character-index) with respect to a given,
;;; presumably formatted, text, e.g., the procedure's text stored in the cdr of
;;; the procedure-definition slot of a procedure, formatted according to some
;;; particular format, presumably with word wrapping, into a position with
;;; respect to that text formatted with no word wrapping whatsoever.
;;;
;;; The result for convert-to-non-word-wrapped-text-position is returned as
;;; three values:
;;;
;;;   (1) line-index
;;;   (2) character-index
;;;   (3) line-index-past-linebreak
;;;
;;; For the function convert-to-non-word-wrapped-text, the converted text is
;;; returned as the first value and then, if the line-index/character-index args
;;; are supplied non-nil, the above three values are returned as the subsequent
;;; values.
;;;
;;; The third value is useful for giving a user-appropriate index into the text,
;;; i.e., not counting the line separator character stored at the beginning of
;;; the line, which users cannot see.
;;;
;;; Note that line-index is 1-based; i.e., the first line is 1, the second 2,
;;; and so on.  Meanwhile, character-index is zero-based; i.e., the first
;;; character is 0, the second is 1, and so on.
;;;
;;; Note that text is NOT reclaimed by either function.
;;;
;;; This makes it so that the resulting (line-index character-index) relate
;;; to lines that come after a "hard" line break only, which sometimes described
;;; as "paragraphs" in common word processors, as opposed to the "soft" line
;;; breaks that are artifacts of the particular word wrapping that was in effect
;;; when the text was last formatted.
;;;
;;; This is particularly intended to support mapping the procedures source code
;;; positions to non-word-wrapped positions that users can understand, which
;;; position can also be used in external editors, such as the G2 native editor,
;;; which just receives a text-string conversion of the text, and must map from
;;; line indexs based on the occurance of hard line breaks only (it has no
;;; knowledge of the artifactual soft line breaks).
;;;
;;; NOTE: see also determine-corrected-text-position-if-necessary, the primitive
;;; for adjusting text positions, which may be able to be used for similar
;;; purposes.
;;;
;;; Note that G2 procedure text is stored as the formatted text that happened to
;;; be in effect in the editor in which it was edited/compiled.
;;;
;;; This is currently implemented by invoking format-text on formatted-text with
;;; a dummy text-box format, `non-word-wrapped-dummy-text-box-format', which is
;;; carefully rigged to result in totally non-word-wrapped text.  The resulting
;;; "reformatted" text is thrown away (reclaimed), but the resulting adjusted
;;; text position is usefully returned.  The format
;;; non-word-wrapped-dummy-text-box-format should never be used in an actual
;;; text box, and should never be saved in a KB.

(def-text-box-format non-word-wrapped-dummy-text-box-format
  ;; all other slots are defaulted, and generally arbitrary and irrelevant.
  maximum-format-width-for-text-cell 1000000 ; "practically never" wrap
  minimum-format-width-for-text-cell 1000000)

(defun convert-to-non-word-wrapped-text-position
    (text line-index character-index)
  (multiple-value-bind
      (non-word-wrapped-text
	new-line-index
	new-character-index
	new-character-index-past-linebreak)
      (convert-to-non-word-wrapped-text
	text line-index character-index)
    (reclaim-text non-word-wrapped-text)
    (values new-line-index
	    new-character-index
	    new-character-index-past-linebreak)))

(defun convert-to-non-word-wrapped-text
    (text &optional line-index? character-index?)
  (let ((dummy-text-box-format
	  (get-or-make-format-frame
	    'non-word-wrapped-dummy-text-box-format))
	(copy-of-text (copy-text text)))
    (multiple-value-bind
	(non-word-wrapped-text woll new-line-index? new-character-index?)
	(format-text
	  copy-of-text dummy-text-box-format
	  nil nil nil nil nil nil line-index? character-index? nil)
      (declare (ignore woll))
      (values
	non-word-wrapped-text
	new-line-index?
	new-character-index?
	(if line-index?
	    (get-character-index-past-separator ; see note 3
	      (find-text-tail-for-line
		non-word-wrapped-text
		new-line-index?)))))))

;; Note 1: ideally, the function to convert positions should be optimized,
;; particularly to avoid the work of actually reformatting the text, also to
;; avoid all/most copying of text, and finally to avoid any possibility of ever
;; wrapping if the format widths "practically" never wrap text actually do.
;; Later!  Also, get rid of non-word-wrapped-dummy-text-box-format! -mhd, 2/1/05

;; Note 2: we should consider changing the text stored with procedures to be
;; either unwordwrapped, or a single string, or some other, more compact,
;; variant of text.  Storing the formatted text has no great benefit, and it's
;; NOT stored with respect to any format we can generally get our hands on, but
;; only the format in effect when last edited.  Affected code would include: (a)
;; any places where the formatted text is used directly, e.g., Inspect output,
;; and (b) the storing of source positions. -mhd, 2/1/05

;; Note 3: if this needed to be optimized, either don't support the final value
;; (index past linebreak), or find it in some way that avoids retraversing the
;; text to get to the relevant line. -mhd, 2/1/05





;;;; Text Searching



;;; `Find-string-in-text-for-inspect' calls find-string-in-text with the appropriate
;;; options per observance-of-word-boundary?.

(defun find-string-in-text-for-inspect
       (string text observance-of-word-boundary?
	&optional (start-line-index 1) (start-character-index 0))
  (unless (=f (text-string-length string) 0)
    (if observance-of-word-boundary?
	(find-string-in-text
	  string text
	  nil nil nil				       ; assume no spaces in word
	  t t
	  (case observance-of-word-boundary?
	    (symbol '(#.%\' #.%\. #.%\-))		; digits?, hyphen?, period?
	    (t  ; WORD, presumably
	     '(#.%\' #.%\.)))
	  start-line-index start-character-index)
	(find-string-in-text
	  string text
	  nil t t				       ; not case or multiple-space sensitive
	  nil nil nil
	  start-line-index start-character-index))))

;; The arg observance-of-word-boundary? used to be observe-of-word-boundary?
;; (true or false) and in the true case simply acted as it does not in the
;; observance-of-word-boundary? = WORD case.  Handling the new SYMBOL case
;; and changing the argument was added today.  (MHD 5/8/91)



;;; `Find-string-in-text' looks for the first occurence of string in text, past
;;; the start-line-index start-character-index position if specified, and
;;; subject to various case-sensitivity, touching-character, and
;;; "space-equivalence" conditions discussed below.  If there is such an
;;; occurrence, four values are returned describing its position in text: the
;;; line index and character index where it begins and the line index and
;;; character index where it ends.  Otherwise, nil is returned.  Note that
;;; string must not be an empty string.

;;; Matching is case-insensitive unless case-sensitive? is non-nil.  If
;;; treat-space-equivalents-in-text-as-spaces? is non-nil, @L, @V, @W, @X, and @Y
;;; in text (but not string) are all treated as if they were ordinary spaces.  If
;;; ignore-extra-spaces-in-text? is non-nil, "extra" spaces in text (beyond what
;;; matches one or more spaces in string) are ignored.  (Note that if, after an
;;; occurrence has been found in text of a string starting with a space, where
;;; ignore-extra-spaces-in-text? is non-nil, starting another search one
;;; character ahead could result in a match that ends at the same position in
;;; text.)

;;; An occurrence is disqualified if there is a `touching character' on either
;;; side that is disallowed per the touching-alphabetic-characters-disallowed?,
;;; touching-digits-disallowed?, and disallowed-touching-characters, arguments.
;;; Touching-alphabetic-characters-disallowed? and touching-digits-disallowed?
;;; provide an efficient means to disallow alphabetic characters and decimal digits.
;;; Disallowed-touching-characters is a list of disallowed simple gensym characters,
;;; which may not include spaces, alphabetic characters or digits.  (For finding
;;; `words' in text, it is recommended that the disallowed characters be alphabetic
;;; characters, apostrophes, and possibly digits, hyphens, and periods.)
;;; Note that an occurrence at the starting position of the search is never
;;; disqualified, that is, the character immediately before the starting position,
;;; when the search doesn't start at the beginning of text, is not examined;
;;; however, by starting the search one character position earlier and specifying
;;; no-match-at-start-position?, this limitation can be nicely circumvented.

;;; Automatic line breaks and added hyphens in text are always treated as if
;;; they are not present.  Thus, for examaple, "international business" occurs
;;; in '((hyphen-added) "our inter-" "national" "business strategy").

;;; String must be a text string.

(defun find-string-in-text
       (string text
	&optional
	(case-sensitive? nil) (treat-space-equivalents-in-text-as-spaces? nil)
	(ignore-extra-spaces-in-text? nil)
	(touching-alphabetic-characters-disallowed? nil)
	(touching-digits-disallowed? nil)
	(disallowed-touching-characters nil)
	(start-line-index 1) (start-character-index 0) (no-match-at-start-position? nil))
  (loop with string-length = (text-line-length string)
	with first-character
	with character-index-past-first-character
	with some-touching-characters-disallowed?
	  = (or touching-alphabetic-characters-disallowed?
		touching-digits-disallowed?
		disallowed-touching-characters)
	with start-line-text-tail?
	  = (find-text-tail-for-line text start-line-index)
	with saved-start-character-index
	with start-character
	with start-character-escape-character?
	with preceding-character? = nil
	with preceding-character-escape-character?
	with line-index
	with character-index
	with start-line-length			; changed by loop below
	initially
	  (multiple-value-setq (first-character
				character-index-past-first-character)
	    (find-next-character-in-text-line 0 string))
	  (if (not case-sensitive?)
	      (setq first-character
		    (char-downcasew first-character)))
	as start-line-lost-space-length = 1	; may be changed by loop below
	as start-line-lost-space-string? = nil	; may be changed by loop below
	as start-line
	   = (loop with hyphen-added-at-end-of-line? = nil
		   with lost-spaces-value?
		   as text-element = (pop start-line-text-tail?)
		   do (cond
			((text-line-p text-element)
			 (setq start-line-length
			       (if hyphen-added-at-end-of-line?
				   (-f (text-line-length text-element) 1)
				   (text-line-length text-element)))
			 (return text-element))
			((setq lost-spaces-value? (lost-spaces-value-if-any text-element))
			 (cond
			   ((text-line-p lost-spaces-value?)
			    (setq start-line-lost-space-string? lost-spaces-value?)
			    (setq start-line-lost-space-length
				  (text-line-length start-line-lost-space-string?)))
			   (t (setq start-line-lost-space-length
				    lost-spaces-value?))))
			((consp text-element)
			 (case (car text-element)
			   (hyphen-added
			    (setq hyphen-added-at-end-of-line? t)
			    (setq start-line-lost-space-length 0))))))
	when
	  (loop do (setq saved-start-character-index start-character-index)
		   (setq start-character-escape-character? nil)
		   (when (not (<f start-character-index
				  (+f start-line-length
				      start-line-lost-space-length)))
		     (loop-finish))
	           (setq start-character
			 (read-unicode-character-from-wide-string-with-lost-spaces
			   start-line start-character-index 
			   start-line-length
			   (or start-line-lost-space-string? start-line-lost-space-length)))
		   (unless case-sensitive?
		     (setq start-character
			   (char-downcasew start-character)))
		   (when (and treat-space-equivalents-in-text-as-spaces?
			      ;; MHD: Consider as a replacement test:  (MHD 12/2/95)
			      ;;
			      ;;   (= (if (space-p first-character) 1 0)
			      ;;      (if (space-p start-character) 1 0))
			      (and (char=w first-character #.%space) ; heuristic
				   (wide-character-member ; abstract!
				     start-character
				     '(#.%line-separator #.%linefeed #.%return
				       #.(unicode-hair-space)
				       #.(unicode-thin-space)
				       #.(unicode-en-space)
				       #.(unicode-em-space))))
			      ;; was:  (MHD 2/6/96)
;			       (and				     
;				  (eql start-character-escape-character? #.%\@)
;				  (eql first-character #.%space) ; heuristic
;				  (memberp start-character
;					   '(#.%\L #.%\V #.%\W #.%\X #.%\Y)))
			      )
		     (setq start-character #.%space)
		     (setq start-character-escape-character? nil))
		when (and (char=w start-character first-character)
			  (not (if (null preceding-character?)
				   no-match-at-start-position?
				   (if some-touching-characters-disallowed?
				       (cond
					 ((alphabetic-p preceding-character?)
					  touching-alphabetic-characters-disallowed?)
					 ((numeric-p preceding-character?)
					  touching-digits-disallowed?)
					 (disallowed-touching-characters
					  (wide-character-member
					    preceding-character?
					    disallowed-touching-characters)))))))
		  thereis			; for matching past first character
		    (loop with i = character-index-past-first-character
			  with next-i
			  with next-character
			  with text-tail? = start-line-text-tail?
			  with text-line = start-line
			  with line-length = start-line-length
			  with lost-space-string? = start-line-lost-space-string?
			  with lost-space-length = start-line-lost-space-length
			  with previous-character-was-a-space? ; OTHER SPACE CHARS?!
			    = (char=w start-character #.%space)
			  with lost-space-at-end-of-line
			  with character
			  initially
			    (setq line-index start-line-index)
			    (setq character-index start-character-index)
			  while
			    (loop until (>=f i string-length)	; =f should suffice
				  do (when (not (<f character-index
						    (+f line-length lost-space-length)))
				       (loop-finish))
				     (setq character
					   (read-unicode-character-from-wide-string-with-lost-spaces
					     text-line character-index
					     line-length
					     (or lost-space-length lost-space-string?)))
					; loop on @R & @Q!
				     (unless case-sensitive?
				       (setq character
					     (char-downcasew character)))
			      ;; The following was in but was baloney: it
			      ;; obviously could never have done anything
			      ;; because character can't be a space and L, V, W,
			      ;; X, or Y at the same time.  Review at some point
			      ;; later! For now comment out! (MHD 12/2/95)
;				     (when (and treat-space-equivalents-in-text-as-spaces?
;						(eql escape-character? #.%\@)
;						(eql character #.%space) ; heuristic
;						(memberp character
;							 '(#.%\L #.%\V #.%\W #.%\X #.%\Y)))	; abstract!
;				       (setq character #.%space)
;				       (setq escape-character? nil))
			      
				     (multiple-value-setq	; slow
				       (next-character next-i)
				       (find-next-character-in-text-line i string))
				     (unless case-sensitive?
				       (setq next-character
					     (char-downcasew next-character)))
				     (cond
				       ((not (char=w character #.%space))
					(setq i next-i))
				       (t (cond
					    ((and previous-character-was-a-space?
						  ignore-extra-spaces-in-text?
						  (not (char=w next-character
							       #.%space)))
					     (setq next-character #.%space))
					    (t (setq i next-i)))
					  (setq previous-character-was-a-space? t)))
				  always ;; why not char=w here ?! (MHD 12/2/95)
				  (eqlw character next-character))
			  when (or (null text-tail?)	      
				   (and (=f i string-length)
					(or (not some-touching-characters-disallowed?)
					    (<f character-index
						(+f line-length lost-space-length)))))
			    return
			      (if (=f i string-length)
				  (not (and some-touching-characters-disallowed?
					    (<f character-index line-length)
					    (let ((character ; setq?
						   (find-next-character-in-text-line
						     character-index text-line)))
					      (cond
						((alphabetic-p character)
						 touching-alphabetic-characters-disallowed?)
						((numeric-p character)
						 touching-digits-disallowed?)
						(disallowed-touching-characters
						 (wide-character-member
						   character
						   disallowed-touching-characters)))))))
			  do (multiple-value-setq
			       (text-line line-length lost-space-at-end-of-line text-tail?)
			       (get-next-text-line text-tail?))	; explicit? (as below?)
			     (incff line-index)
			     (setq character-index 0)
			     (setq lost-space-string?
				   (if (text-line-p lost-space-at-end-of-line)
				       lost-space-at-end-of-line))
			     (setq lost-space-length
				   (if (text-line-p lost-space-at-end-of-line)
				       (text-line-length lost-space-at-end-of-line)
				       lost-space-at-end-of-line)))
		do (setq preceding-character?
			 start-character)
		   (setq preceding-character-escape-character?
			 start-character-escape-character?))
	  return
	    (values
	      start-line-index saved-start-character-index line-index character-index)
	while start-line-text-tail?
	do (incff start-line-index)		; changes arg
	   (setq start-character-index 0)))	; changes arg

;; This is coded for speed more than elegance.

;; Fix this for @R and @Q!

;; Implement an option to ignore spaces in text, so that the search could be insensitive
;; to the presence or absence of spaces!  In this case, string should have had any spaces
;; stripped out of it.  (In the code, it would only be necessary to ignore spaces after
;; a first-character match.)

;; Consider having a "wild-card" feature, where string could contain something that
;; would match an arbitrary character or sequence of characters.

;; Consider allowing disallowed-touching-characters to be other than simple gensym
;; characters 
;; Consider requiring string to be a simple text string, to gain a bit of speed.

;; Consider abstracting repeated code herein as macros.







;;;; Updating Text Boxes






;;; Replace-text-with-text-string-in-text-box ...  In general, this bypasses the
;;; slot putter usually used for box-translation-and-text value putting.  This
;;; modifies the text part of the box-translation-and-text slot of text-box, but
;;; not the CAR.  Therefore, it may not be used to change the text in a non-free
;;; text box, unless the caller takes care to modify the CAR himself.  This does
;;; update the frame representations of text box, if and only if the text of
;;; text box actually changes.

;;; This is intended for optimized updating of the text of messages and other
;;; kinds of free text.  However, there is currently no optimization of text
;;; boxes that are not left-justified (e.g., center- or right-justified text
;;; boxes).

;;; This does NOT reclaim text-string-to-insert.


;;; Replace-text-in-text-box does almost the same, but takes a text rather than
;;; a text-string argument.  This does not reclaim its text argument.
;;;
;;; This takes one optional argument, suppress-lost-spaces-at-end?, which is
;;; interpreted as per the same-named argument to convert-text-to-text-string,
;;; q.v.
;;;
;;; The semantics (and currently the implementation) are as though a temporary
;;; text-string equivalent of the text is created and then passed on to
;;; replace-text-with-text-string-in-text-box.  (In the future, we may consider
;;; improving matters by having the text worked on directly without the need for
;;; the intermediate text-string copy. However, it should continue to produce
;;; the same results.)


;;; Replace-formatted-text-in-text-box does almost the same, but takes a
;;; formatted text and replaces the text (the cdr of the
;;; box-translation-and-text slot) of text-box with formatted-text.  The
;;; argument formatted-text is effectively reclaimed by this function. (It
;;; actually becomes incorporated into the text of text-box.)

(defun replace-text-with-text-string-in-text-box (text-string text-box)
  (let ((text (cdr (box-translation-and-text text-box)))
	(current-custom-reclamation-stamp? "RplcTxtWTxtStr"))	; suspect recycling bug. (MHD 2/8/93
    
    (unless (left-justified-text-box-p text-box)
      ;; Return early if not left-justifed (flush-left, ragged right), just
      ;; after doing the job in an unoptimized fashion.  Optimization has not
      ;; been done to date, but consider optimizing later.  Note that
      ;; non-left-justified text has just at this time been exposed to users for
      ;; G2 5.0 Rev. 3.  (MHD 3/27/98)
      (let* ((box-translation-and-text (box-translation-and-text text-box))
	     (translation
	       (prog1 (car box-translation-and-text)
		 (setf (car box-translation-and-text) nil)))
	     (new-box-translation-and-text
	       (slot-value-cons
		 translation
		 (convert-text-string-to-text (copy-text-string text-string)))))	
	(change-slot-value
	  text-box 'box-translation-and-text new-box-translation-and-text))
      (RETURN-FROM replace-text-with-text-string-in-text-box))
		
    (multiple-value-bind (end-line-index end-character-index end-text-tail)
	(find-end-of-text text 1)
      (loop with adjacent-character?
	    with next-line-index?
	    with next-character-index?
	    with next-text-tail?

	    with exhausted-original-text? = nil
	    with string-character?
	    with i = 0
	    with length-of-string = (text-string-length text-string)
	    with temporary-text-string? = nil
	    as string-start-index = 0 then i	  
	    as line-index
	       = 1
	       then next-line-index?
	    as character-index
	       = 0
	       then next-character-index?
	    as text-tail
	       = text
	       then next-text-tail?
	    until (>=f i length-of-string)
	    do (multiple-value-setq
		 (next-line-index? next-character-index?
		  next-text-tail?
		  adjacent-character?)
		 (find-next-character-if-any
		   line-index character-index text-tail))	     
	       
	       (multiple-value-setq (string-character? i)
		 (find-next-character-in-text-line i text-string))
	       
	    when (null adjacent-character?)
	      do (setq exhausted-original-text? t)	; used in finally loop
		 
	    while (and ; nil ; <- uncomment to see how it looks without the optimization
		       adjacent-character?
		       string-character?
		       (eqlw adjacent-character? string-character?))
	    finally
	      (when t
		;; (or (<f string-start-index length-of-string)
		;;     [string of orig. text is longer than text-string])
		;; -- possible optimization to avoid work below when there
		;; is not change whatsoever.  Defer this for now. (MHD 11/3/92)
		
		(when (>f string-start-index 0)
		  
		  ;; There's a common initial substring.
		  
		  (setq temporary-text-string?
			(text-string-substring
			  text-string string-start-index length-of-string)))
		
		;; Now see if there's a common final substring, but only if
		;; text-string is longer than the orig. text, which we determine
		;; could only be true if we did not exhaust the original text or
		;; the text string (string-start-index < length-of-string).
		
		(when (and (null exhausted-original-text?)
			   (<f string-start-index length-of-string))
		  (loop with previous-line-index?
			with previous-character-index?
			with previous-text-tail?
			
			with i-from-end = length-of-string
			as string-end-index
			   = length-of-string
			   then i-from-end
			as line-index-from-end
			   = end-line-index
			   then previous-line-index?
			as character-index-from-end
			   = end-character-index
			   then previous-character-index?
			as text-tail-from-end
			   = end-text-tail
			   then previous-text-tail?
			until (or (<=f i-from-end string-start-index)
				  (and (<=f line-index-from-end
					    line-index)
				       (<=f character-index-from-end
					    character-index)))
			do (multiple-value-setq
			     (previous-line-index? previous-character-index?
			      previous-text-tail?
			      adjacent-character?)
			     (find-previous-character-if-any
			       line-index-from-end character-index-from-end
			       text-tail-from-end text))
			   
			   (multiple-value-setq (string-character?
						 i-from-end)
			     (find-previous-character-in-text-line
			       i-from-end text-string))
			   
			while (and		; nil ; <- uncomment to see how it looks without the optimization
				adjacent-character?
				string-character?
				(eqlw adjacent-character?
				      string-character?))
			
			finally
			  (when (<f string-end-index length-of-string)
			    (when temporary-text-string?
			      (reclaim-text-string temporary-text-string?))
			    (setq temporary-text-string?
				  (text-string-substring
				    text-string string-start-index string-end-index)))
			  
			  (setq end-line-index line-index-from-end)
			  (setq end-character-index character-index-from-end)
			  (setq end-character-index character-index-from-end)))
		(change-text-box
		  text-box (or temporary-text-string? text-string)
		  text-tail line-index character-index
		  end-line-index end-character-index)
		(when temporary-text-string?
		  (reclaim-text-string temporary-text-string?))
		(when (frame-representations text-box)
		  (update-representations-of-slot-value
		    text-box 'box-translation-and-text)))))))



(defun replace-text-in-text-box (text text-box &optional suppress-lost-spaces-at-end?)
  (let ((temporary-text-string
	 (convert-text-to-text-string
	   text nil nil nil nil nil suppress-lost-spaces-at-end?)))
    (replace-text-with-text-string-in-text-box temporary-text-string text-box)
    (reclaim-text-string temporary-text-string)))

;; The below is not currently used, but it may be some day. (jpg 2/1/05)

(defun replace-formatted-text-in-text-box (text text-box)
  (update-text-in-edit-box		; erase old text
    t (cdr (box-translation-and-text text-box)) nil nil 1 nil text-box)
  
  (setf (cdr (box-translation-and-text text-box)) ; change text
	(prog1 text
	  (reclaim-text (cdr (box-translation-and-text text-box)))))
  (update-text-in-edit-box		; draw new text
    nil text nil nil 1 nil text-box)
  
  (update-representations-of-slot-value	; update representation frames
    text-box 'box-translation-and-text))

;; Currently, this does not find common subtexts to avoid drawing. Consider
;; optimizing this to do so! (MHD 4/30/04)





;;; Change-text-box ... This does NOT reclaim string-to-insert, which must be
;;; a text-string.

;;; NOTE/Warning: this has not been made to work for other than left-justified
;;; text boxes.  It should for now be considered a subfunction of its sole
;;; caller, replace-text-with-text-string-in-text-box, which undertakes to work
;;; around its present limitation by not calling it, but having the work done
;;; through slow but sure methods. (MHD 3/27/98)

(defun change-text-box
    (text-box string-to-insert
	      text-tail line-index-of-change character-index-of-change
	      line-index-past-deletion character-index-past-deletion)
  
  (let* ((current-custom-reclamation-stamp? "ChgTxtBx")	; suspect recycling bug. (MHD 2/8/93)
	 (text-box-format (text-box-format text-box))
	 (text-cell-plist-for-text-box
	   (text-cell-plist-for-text-box text-box))
	 (x-magnification? (x-magnification? text-cell-plist-for-text-box text-box-format))
	 (text-being-changed (cdr (box-translation-and-text text-box)))
	 (old-width-for-text
	   (-w (width-of-block text-box)
	       (+w (text-box-left-border-width text-box-format)
		   (text-cell-left-margin text-box-format)
		   (text-cell-right-margin text-box-format)
		   (text-box-right-border-width text-box-format))))
	 
	 (new-width-for-text 0)
	 
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
	 magnified-distance-from-left-to-where-difference-starts?
	 
	 (new-text-has-same-height-as-old? t)
	 text-tail-past-text-segment?)
    
    
    
    ;; Delete all text regions.

    
    ;; Determine the minimum necessary text segment replacement that includes the
    ;; change and leaves the text appropriately reformatted.
    (multiple-value-setq (new-text-segment new-width-for-text
					   old-text-segment text-tail-past-old-text-segment?
					   line-index-of-old-and-new-text-segment
					   line-index-past-new-text-segment
					   line-index-past-old-text-segment)
      (reformat-text
	text-being-changed text-box-format
	nil
	nil text-tail
	line-index-of-change character-index-of-change
	line-index-past-deletion character-index-past-deletion
	string-to-insert
	(minimum-width-of-text-box text-box)
	text-cell-plist-for-text-box))

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
		       ;;; What about this? PGA ****
		       (get-next-text-line text-tail-in-new-text))
		   (setq length-of-old-text-line (text-line-length old-text-line))
		   (setq length-of-new-text-line (text-line-length new-text-line))
		   (cond
		     ((=f line-index-in-old-and-new-text line-index-of-change)
		      (return
			(cond			; NEEDS REDESIGN OR DOCUMENTATION!
			  ((and (null next-text-tail-in-new-text?)
				(null next-text-tail-in-old-text?))
			   (minf character-index-of-change
				 length-of-old-text-line
				 length-of-new-text-line))
			  ((<f character-index-of-change length-of-old-text-line)
			   (minf character-index-of-change length-of-new-text-line))
			  ((<f character-index-of-change length-of-new-text-line)
			   length-of-old-text-line)
			  (t nil))		; character-index-of-change >= old & new length
			))
		     ((not (=f length-of-new-text-line length-of-old-text-line))
		      (return (minf length-of-new-text-line length-of-old-text-line)))
		     ((and (>f length-of-old-text-line 0)	; only for added-hyphen cases
			   (not (eqlw (charw old-text-line (-f length-of-old-text-line 1))
				      (charw new-text-line (-f length-of-new-text-line 1)))))
		      (return			; sample case: "mas-" "ter ..." changing to "mast" "..."
			(-f length-of-old-text-line 1)))
		     ((not (equalw lost-space-at-end-of-new-text-line ; equalw to handle integer, text 
				   lost-space-at-end-of-old-text-line))	;   string, or wide string
		      (return length-of-old-text-line))
		     ((or (eq next-text-tail-in-old-text? text-tail-past-old-text-segment?)
			  (null next-text-tail-in-new-text?))
		      (return nil)))
		   (setq text-tail-in-old-text next-text-tail-in-old-text?)

	    ;; The following reclaims the unused portion of the freshly consed
	    ;; text pointed to by text-tail-in-new-text, if appropriate, before the
	    ;; redirecting it below to point to next-text-tail-in-new-text?,
	    ;; the portion that will be used. [This was causing a leak of just
	    ;; one text line when changing a non-first line in a multiline
	    ;; text, e.g., from
	    ;;
	    ;;   b
	    ;;   cd
	    ;;
	    ;; to
	    ;;
	    ;;   b
	    ;;   cA
	    ;;
	    ;; I discovered this leak after transforming the code in
	    ;; change-edit-box; so I'm suspicious that there is this leak
	    ;; in change-edit-box, but it is so minor, obscure, and hard
	    ;; to track down, that it never was detected.  TO DO: check if
	    ;; it is there now, and fix it!  (MHD 9/25/92)
	    
		   (if (and text-tail-in-new-text
			    next-text-tail-in-new-text?
			    (not (eq text-tail-in-new-text next-text-tail-in-new-text?)))
		       (let ((text-to-reclaim text-tail-in-new-text))
			 (loop as ll = nil then l
			       for l = text-to-reclaim then (cdr l)
			       when (eq l next-text-tail-in-new-text?)
				 return (progn
					  (setf (cdr ll) nil)
					  (reclaim-text text-to-reclaim)))))
	    
	    
		   (setq text-tail-in-new-text next-text-tail-in-new-text?)
		   (incff line-index-in-old-and-new-text)))
    (when character-index-where-difference-starts?
      (setq magnified-distance-from-left-to-where-difference-starts?
	    (loop with indentation = 0	; do more elegantly, later!
		  with word-spacing = (default-word-spacing text-box-format)
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
		      (+w (text-box-left-border-width text-box-format)
			  (text-cell-left-margin text-box-format)
			  (let ((magnifiable-distance
				  (+w (if (=f character-index-where-difference-starts? 0)
					  0		; indentation may differ in this case
					  indentation)
				      (compute-minimum-left-edge-of-character-in-line-of-text
					old-text-line character-index-where-difference-starts?
					(text-cell-font-map text-box-format)
					word-spacing))))
			    (if x-magnification?
				(magnify magnifiable-distance x-magnification?)
				magnifiable-distance)))))))
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
    
    
    
    ;; Erase a portion of the text segment, as necessary.
    (update-text-in-edit-box
      t
      text-tail-in-old-text next-text-tail-in-old-text? text-tail-past-text-segment?
      line-index-in-old-and-new-text
      magnified-distance-from-left-to-where-difference-starts?
      text-box)
    
    ;; Swap in the new reformatted segment of text, and reclaim unused
    ;; text.
    
    (if text-tail-past-old-text-segment?	; remove common tail from old text segment
	(loop for l on text-tail-in-old-text
	      until (eq (cdr l) text-tail-past-old-text-segment?)
	      finally (setf (cdr l) nil)))
    (setf (car text-tail-in-old-text)		; swap cars of old and new text segments
	  (prog1 (car text-tail-in-new-text)
	    (setf (car text-tail-in-new-text) (car text-tail-in-old-text))))
    (setf (cdr text-tail-in-old-text)
	  (prog1 (cdr text-tail-in-new-text)
	    (setf (cdr text-tail-in-new-text) (cdr text-tail-in-old-text))))
    (setq text-tail-in-old-text			; only for clarity
	  (prog1 text-tail-in-new-text
	    (setq text-tail-in-new-text text-tail-in-old-text)))

    (reclaim-text text-tail-in-old-text)

    ;; Reflect unreformatted lines in new width for text, if necessary (now always!).
    (cond
      ((not (eq old-text-segment text-being-changed))
       (setq new-width-for-text
	     (maxw new-width-for-text
		   (compute-width-of-longest-line
		     text-being-changed text-box-format
		     text-cell-plist-for-text-box
		     nil old-text-segment)))))
    (cond
      (text-tail-past-old-text-segment?
       (setq new-width-for-text
	     (maxw new-width-for-text
		   (compute-width-of-longest-line
		     text-tail-past-old-text-segment?
		     text-box-format
		     text-cell-plist-for-text-box
		     nil old-text-segment)))))
    

    ;; Redraw the text box border, if necessary.  Also, if its bottom edge moves up or
    ;; down, erase any temporary information on the text workspace (that is, anything
    ;; that could be below the text box); this information will be redrawn again, if
    ;; necessary, by extend-parsing-as-appropriate.
    (let* ((new-right-edge?
	     (if (not (=w new-width-for-text old-width-for-text))
		 (maxw (+w (left-edge-of-block text-box)
			   (minimum-width-of-text-box text-box))
		       (+w (right-edge-of-block text-box)	; compute afresh?
			   (-w new-width-for-text old-width-for-text)))))

	   
	   ;; The following set of bindings are not strictly needed, since
	   ;; they could all ultimately be folded into the expression
	   ;; to create the value of new-bottom-edge?  However, AC suggested
	   ;; that this simplification might help work around a bug in the
	   ;; SUN 3 'C' compiler (on our machine California).  The bug was
	   ;; causing NIL to be passed in as the first argument to compute-
	   ;; height-for-text, even though the value in the box-translation-
	   ;; and-text slot contained a perfectly good value, when looked at
	   ;; in dbx.  (MHD 11/20/91)
	   (top-edge-of-block (top-edge-of-block text-box))
	   (minimum-height-of-text-box (minimum-height-of-text-box text-box))
	   (maximum-height-of-text-box (maximum-height-of-text-box text-box))
	   (text-box-top-border-width
	     (text-box-top-border-width text-box-format))
	   (text (cdr (box-translation-and-text text-box)))
	   (height-for-text
	     (compute-height-for-text	; result includes margins
	       text
	       text-box-format text-cell-plist-for-text-box))
	   (text-box-bottom-border-width
	     (text-box-bottom-border-width text-box-format))
	   
	   ;; End of bindings to which the above comment refers; the
	   ;; following binding is really needed:
	   
	   (new-bottom-edge?
	     (if (not new-text-has-same-height-as-old?)
		 (+w top-edge-of-block
		     (pin-in-range minimum-height-of-text-box
				   (+w text-box-top-border-width
				       height-for-text
				       text-box-bottom-border-width)
				   maximum-height-of-text-box)))))
      (cond
	((or (and new-right-edge?
		  ;; Bug in 3.0 Rev. 1: it shouldn't have been testing
		  ;; this, but it was!  And the same goes for the bottom
		  ;; edge test. This could have left text boxes permanently
		  ;; misformatted.  (MHD 3/12/93)
;	          (>w (-w new-right-edge? (left-edge-of-block text-box))
;                     (minimum-width-of-text-box text-box))
		  (/=w new-right-edge? (right-edge-of-block text-box)))
	     (and new-bottom-edge?
		  (/=w new-bottom-edge? (bottom-edge-of-block text-box))))
	 (update-border-of-text-box text-box nil nil new-right-edge? new-bottom-edge?))))

    ;; Draw (or redraw) a portion of the text segment, as necessary.
    (update-text-in-edit-box
      nil
      text-tail-in-new-text next-text-tail-in-new-text? text-tail-past-text-segment?
      line-index-in-old-and-new-text
      magnified-distance-from-left-to-where-difference-starts?
      text-box)))



;; This calls update-text-in-edit-box.  The only thing special about that function
;; is that it requires indentations and widths to be present in the text, which
;; we do here anyway.  Worry about increasing space requirements?! (MHD 9/18/92)





;; Later -- match against the ends of the text & string to avoid drawing common
;; parts, e.g., for the case where just the beginning changes, say "XXX@L12345"
;; <-> "YXX@L12345".  Note that this cannot typically save redrawing of the rest
;; of the first line, but can often avoid redrawing follow-on lines.  (MHD
;; 9/18/92)






;;;; Per-Text-Box Formats


;;; NOTE: Stuff in this section is all hypothetical, and is therefore
;;; effectively commented out with #+hypothetical.  It contains mostly stuff
;;; that was in comments, particularly around the change-size facility.  If we
;;; ever revive the full plan for format frames, this is a start.  (MHD 5/27/94)


;;; `Restore-default-text-box-format' ... This is to be called when text box has
;;; been completely erased.  This returns non-nil if it did anything.  Upon
;;; completion, unless this returns nil, text-box must be reformatted before it
;;; may again be drawn.

#+hypothetical
(defun restore-default-text-box-format (text-box)
  (when (format-change? (text-box-format text-box))
    (let* ((old-format-frame (text-box-format text-box))
	   (format-name? (format-change? old-format-frame))
	   (new-format-frame
	     (get-or-make-format-frame
	       (or format-name? (default-text-box-format-name text-box)))))
      (setf (text-box-format text-box) new-format-frame)
      (delete-frame old-format-frame))
    t))

;; This assumes that a text box with a non-null format-change? is uniquely
;; pointed to by that text box.  This would require support in clone-frame
;; which is not yet present.



;;; `Prepare-text-box-for-customized-format' ... This is to be called before
;;; making changes to a text box's format.  If it a shared format, this clones
;;; it, and makes it unique, and sets the name-or-names-for-frame and
;;; format-change? slots appropriately.  This return non-nil if it had to do
;;; anything.  Regardless of what this does, the text box should not need
;;; reformatting just by virtue of calling this.  All this does is delink the
;;; format from its default definition.  It shouldn't result in any difference
;;; in how text would be reformatted, assuming it's been formatted already.
;;; Thus, this can be called prior to erasing a text box.

#+hypothetical
(defun prepare-text-box-for-customized-format (text-box)
  (when (null (format-change? (text-box-format text-box)))
    (let* ((old-format-frame (text-box-format text-box))
	   (format-name? (name-or-names-for-frame old-format-frame))
	   (new-format-frame (clone-frame old-format-frame)))
      (setf (name-or-names-for-frame new-format-frame) nil)
      (setf (format-change? new-format-frame) format-name?)
      (setf (text-box-format text-box) new-format-frame))
    t))


;;; `Set-minimum-format-width-for-text-box' is to be called with text-box
;;; erased.  After it has been called, text box should be reformatted, and
;;; then drawn.
;;;
;;; This results in text box having a unique, unshared format, based on its
;;; original format.

#+hypothetical
(defun set-minimum-format-width-for-text-box (text-box width)
  (prepare-text-box-for-customized-format)
  (setf (minimum-format-width-for-text-cell (text-box-format text-box))
	(-w width
	    (text-cell-left-margin (text-box-format text-box))
	    (text-cell-right-margin (text-box-format text-box)))))





;;;; Device/Scaleable Text Widths

;;; in TABLES

(declare-forward-reference reformat-table-in-place function)

#+development
(progn

(defun switch-to-scaleable-widths (&optional reload-fonts? use-x-fonts? off?)
  ;; this is kludgy, but should mostly work

  (if reload-fonts?
      (if use-x-fonts?
	  (make-new-gensym-adobe-bitmap-fonts-2)
	  (make-new-gensym-adobe-bitmap-fonts)))
  
  
  (loop for class in '(text-box table chart)
	do (loop for x being each class-instance of class
		 do (erase-images-of-block x nil)))

  (setq use-scaleable-set-widths? (if off? nil t))
  (decache-font-bitmaps)
  
  (loop for class in '(text-box table chart)
	do (loop for x being each class-instance of class
		 do (case class
		      (text-box (reformat-text-box-in-place x))
		      (table (reformat-table-in-place x))
		      (chart))
		    (draw-images-of-block x nil))))



(defun switch-to-device-widths ()
  (switch-to-scaleable-widths nil nil t))





;;;; Testing/Displaying Font Scaling (for Development)



(defparameter text-demo-sizes
  '(1 .99 .98 .97 .96 .95 .94 .93 .92 .91 .90 .89 .88 .87 .86 .85 .80 .75))

(defparameter text-demo-strings-menu
  '("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!~@#$%^&*()_+|~~-=~\\`{}[]:\";'<>?,./"
    "klmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "Like architecture, the design of user interfaces is at least partly an art rather than a science. We hope that the design of user interfaces will someday become more science than art, but the climb to reach this goal is long; the ascent has begun, but there are many hard traverses ahead. In the meantime, we offer an attitude toward the design of interactive systems, and some specific dos and don'ts for the designer which, if applied creatively, can help focus attention on the human factors, also called the ergonomics, of an interactive system. [From Fundamentals of Interactive Computer Graphics, by J. D. FOLEY & A. VAN DAM, Copyright ~| 1982]"
    "Like architecture, the design of user interfaces is at least partly an art rather than a science. We hope that the design of user interfaces will someday become more science than art, but the climb to reach this goal is long; the ascent has begun, but there are many hard traverses ahead.[From Fundamentals of Interactive Computer Graphics, by J. D. FOLEY & A. VAN DAM, Copyright ~| 1982]"
    "17.5 REPRODUCING COLOR HARD COPY  Color images are reproduced in print in a way similar to that used for monochrome images, but four sets of halftone dots are printed, one for each of the subtractive primaries, plus black. Black is used because in printing it is difficult to obtain a deep black by combining the three primaries."))

(defparameter text-demo-string-menu-index 1)

(defun get-text-demo-string ()
  (nth text-demo-string-menu-index text-demo-strings-menu))

(def-text-cell-format text-demo-format
  text-cell-lines-justified? nil
  text-cell-left-margin 10
  text-cell-top-margin 10
  text-cell-right-margin 10
  text-cell-bottom-margin 10
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 0
  text-cell-font-map (hm18)
  text-cell-line-height 20
  text-cell-baseline-position 16
  text-cell-line-spacing 3
  default-word-spacing #.(convert-to-text-width 4)
  minimum-format-width-for-text-cell 600)

(defun demonstrate-text-in-table-of-different-sizes ()
  (let* ((text-cell-format
	  (get-or-make-format-frame 'text-demo-format))
	 (font-name
	   (first (text-cell-font-map text-cell-format)))
	 (outline-font-info
	   (outline-font-info font-name)))
    (put-workspace-on-pane
      (make-new-top-level-kb-workspace
	'kb-workspace
	nil
	nil ; 'font-demo-workspace 
	(make-or-reformat-table
	  (nconc
	    (slot-value-list
	      (slot-value-list
		nil
		(make-text-cell
		  (convert-text-string-to-text
		    (tformat-text-string
		      "Basic Font: ~d point ~a at ~dX~d DPI"
		      (point-size-of-the-bitmap-font outline-font-info)
		      (corresponding-outline-font outline-font-info)
		      (original-bitmap-x-device-resolution outline-font-info)
		      (original-bitmap-y-device-resolution outline-font-info)))
		  text-cell-format)))
	    (slot-value-list
	      (slot-value-list
		(make-text-cell
		  (convert-text-string-to-text
		    (tformat-text-string "%Reduction~%# scanlines"))
		  text-cell-format)
		(make-text-cell
		  (convert-text-string-to-text
		    (tformat-text-string "Sample Text"))
		  text-cell-format)))
	    (loop for size in text-demo-sizes
		  as magnification
		  = (convert-to-magnification size)
		  as size-in-percent-as-integer
		    = (with-temporary-gensym-float-creation text-demo
			(* size 100))
		  with standard-lines-per-em-as-text-width ; assume x=y scale
		    = (horizontal-lines-per-em-as-text-width outline-font-info)
		  as scaled-lines-per-em-as-text-width
		    = (magnify
			standard-lines-per-em-as-text-width
			magnification)
		  as scaled-lines-per-em-as-float
		    = (with-temporary-gensym-float-creation text-demo
			(/ scaled-lines-per-em-as-text-width 256.0))
		  collect
		    (slot-value-list
		      (make-text-cell
			(convert-text-string-to-text
			  (tformat-text-string
			    "~d% ~a"
			    size-in-percent-as-integer
			    scaled-lines-per-em-as-float))
			text-cell-format
			(slot-value-list
			  'x-magnification magnification
			  'y-magnification magnification))
		      (make-text-cell
			(convert-text-string-to-text
			  (copy-text-string (get-text-demo-string)))
			text-cell-format
			(slot-value-list
			  'x-magnification magnification
			  'y-magnification magnification)))
		    using slot-value-cons))
	  'attributes-table-format
	  nil))
      current-workstation-detail-pane nil nil nil)))

;; A window with a magnification of the pixels can be obtained
;; using
;; 
;;   xmag -mag 2.5 -source 400x400
;;
;; The original (G2) window, or the resulting magnification window
;; can be snapshotted, and a hardcopy obtained, by clicking on the
;; window of choice after invoking this:
;;
;;   xwd | xpr -device ps | lpr
;;
;; 





;;;; Testing Per-Text-Box Magnification (for Development)



;;; 2X is a development function.  It changes a text box's format to a new one
;;; that has 2X magnification in X and Y.  This has been used for testing or
;;; demonstrating the ability to magnify text.  With the second argument, undo?,
;;; true, this just reverts to the default format.

;;; This should only be used in development, and it should not be used in a KB
;;; that is to be saved, since it may put out one or more garbage, or illegal,
;;; format frames.

#+development
(defun 2x (Text-box &optional undo?)
   (erase-images-of-block text-box nil)
   (if undo?
       (setf (text-box-format text-box)
	     (get-or-make-format-frame (default-text-box-format-name text-box)))
       (let ((2x-magnification '#.(convert-to-magnification-at-compile-time 2)))
	 ;; This has no effect -- IT SHOULD, BUT IT DOESN'T -- the function
	 ;; reformat-text-1 has code that pays attention to the plist commented out
	 ;; some unexplained reason (!).  (MHD 9/15/92)
;	 (change-text-box-property text-box 'x-magnification? 2x-magnification)
;	 (change-text-box-property text-box 'y-magnification? 2x-magnification)
	 ;; This does work -- it changes the format to a new, unique one with no
	 ;; name with 2x magnification.
	 (setf (text-box-format text-box)
	       (make-format-frame (default-text-box-format-name text-box)))
	 (setf  (text-cell-x-magnification? (text-box-format text-box)) 2x-magnification)
	 (setf  (text-cell-y-magnification? (text-box-format text-box)) 2x-magnification)))
   (reformat-text-box-in-place text-box)
   (draw-images-of-block text-box nil)
   (enlarge-workspace-for-block-rectangle-if-necessary text-box nil))

;; This could leave garbage text box formats around.  If saved in a KB, at least
;; one would probably live on forever, uselessly.  Also, a 2X format frame should
;; not be allowed to exist, since it cannot now be created by the user, just
;; by hacking.  Would be good to have a POLLUTED flag we could set whenever this
;; function were used.  (MHD 9/15/92)

;; Added.  (MHD 9/15/92)

)





;;;; Truncating and Fitting Facilities



;;; The system procedure/function `g2-reformat-text-string-to-fit-message'
;;; replaces the text of message-frame (a text-box instance) with a subset of
;;; text of text-string such that the text fits inside of message frame.  An
;;; ellipsis (...) is used to indicate that text is removed.  If the text fits
;;; completely, then no ellipsis is added.  Otherwise, there will always be an
;;; ellipsis at the end of the text, except in the very rare case that even that
;;; much text will not fit.  And in addition, there may be an ellipsis present
;;; at the end of one or more lines of text (as described below).
;;;
;;; The current width and height of message-frame, along with numerous
;;; parameters specified by its text box format and text cell plist, determine
;;; maximum width and height of the final text.  This may never end up altering
;;; the block edges of message-frame.  However, note that the normal parameter
;;; for determining the width of the text, minimum-format-width-for-text-box,
;;; is ignored by this function.  The resulting text may not be consistent with
;;; that parameter.  Thus, the resulting text box is not "stable" in terms of
;;; its formatting.  For example, if you edit the text of a text box that's had
;;; its text changed by this function, without changing any text, the resulting
;;; text formatting and size of the text box may well be different. NB: For
;;; this reason, this is primarily used as a semiprivate routine by the GXL
;;; (Gensym spreadsheet) facility, and although this is a generally available
;;; system procedure, it has not been documented for end users to date (as of
;;; 4/30/04), and may never be in its current form.  At some future point, we
;;; may decide in fact to document this in its current form.  But I (MHD) would
;;; prefer we change some of its behavior to be more "stable" before we
;;; document it.
;;;
;;; If wrap-flag is true, then this applies standard word-wrapping as much as
;;; possible to the text.  This normally allows all of the beginning text to
;;; appear without an ellipsis on any line but the last.  However, in the case
;;; where a there is an unbreakable word of so great length that it cannot fit
;;; on a single line within the existing width of the enclosing text box, such
;;; a word will be truncated with an ellipsis at the end of the line to
;;; indicate the truncation.
;;;
;;; If wrap-flag is false, then this does not do word wrapping.  In this case,
;;; only explicit line break characters result in new lines.  Paragraph tend to
;;; become long lines that exceed the width constraint.  Such long lines are
;;; truncated with an ellipsis at the end of the line to indicate the
;;; truncation.

(defun-for-system-procedure g2-reformat-text-string-to-fit-message
    (message-frame text-string wrap-flag)
  (let* ((wrap-p (evaluation-truth-value-is-true-p wrap-flag))
	 (text-cell-plist-for-text-box
	   (text-cell-plist-for-text-box message-frame))	 
	 (text-box-format (text-box-format message-frame))
	 (right-edge (right-edge-of-block message-frame))
	 (left-edge (left-edge-of-block message-frame))
	 (top-edge (top-edge-of-block message-frame))
	 (bottom-edge (bottom-edge-of-block message-frame))
	 (left-margin (text-cell-left-margin text-box-format))
	 (right-margin (text-cell-right-margin text-box-format))
	 (left-border (text-box-left-border-width text-box-format))
	 (right-border (text-box-right-border-width text-box-format))
	 (width (-w right-edge left-edge))
	 (height (-w bottom-edge top-edge))
	 (class-description (class-description (class message-frame)))
	 (slot-descriptions (slot-descriptions class-description))
	 (slot-description-of-text-slot
	   (get-slot-description
	     'box-translation-and-text slot-descriptions 'message))
	 (original-minimum-format-width (minimum-format-width-for-text-cell text-box-format))
	 (new-value-to-conclude
	   (convert-text-string-to-text-within-region
	     text-string width height text-box-format wrap-p
	     text-cell-plist-for-text-box))
	 (remaining-width
	   (-f width 
	       right-margin left-margin left-border right-border)))
    
    (when wrap-p
      (setf (minimum-format-width-for-text-cell text-box-format)
	    remaining-width))  ; This is evil
    (let ((do-not-note-permanent-changes-p t))
      (note-kb-state-change-to-slot-by-saving-text
	message-frame slot-description-of-text-slot)
      (replace-text-in-text-box new-value-to-conclude message-frame t)
      (change-edges-of-block message-frame left-edge top-edge right-edge bottom-edge))
    (reclaim-slot-value new-value-to-conclude)
    (when wrap-p
      (setf (minimum-format-width-for-text-cell text-box-format)
	    original-minimum-format-width))))



;;; The function `convert-text-string-to-text-within-region' formats text-string
;;; to fit within the region bounded by width and height, as though for a text
;;; box of that width and height, and returns the resulting formatted text.
;;;
;;; This reclaims or incorporates text-string into its result.

(defun convert-text-string-to-text-within-region
    (text-string width height text-box-format wrap-p &optional text-cell-plist)
  (let* ((x-magnification?
	  (x-magnification? text-cell-plist text-box-format))
	 (left-margin (text-cell-left-margin text-box-format))
	 (top-margin (text-cell-top-margin text-box-format))
	 (right-margin (text-cell-right-margin text-box-format))
	 (bottom-margin (text-cell-bottom-margin text-box-format))
	 (left-border (text-box-left-border-width text-box-format))
	 (top-border (text-box-top-border-width text-box-format))
	 (right-border (text-box-right-border-width text-box-format))
	 (bottom-border (text-box-bottom-border-width text-box-format))
	 (remaining-width-excluding-margin
	  (-w width left-border right-border))
	 (remaining-width
	  (-w remaining-width-excluding-margin right-margin left-margin))
	 (remaining-height
	  (-w height
	      bottom-margin top-margin top-border bottom-border))
	 (widest-width 100000))		; arbitrarily incredibly high
    (let* ((text (convert-text-string-to-text text-string))
	   formatted-text
	   new-width new-height
	   line-index text-tail text-line
	   end-line-index end-character-index)
      (multiple-value-setq (formatted-text new-width)
	(format-text
	  text text-box-format text-cell-plist nil nil nil nil nil nil nil
	  (if wrap-p remaining-width-excluding-margin widest-width)
	  (if wrap-p t)))
      (setq new-height
	    (compute-height-for-text-without-margins
	      formatted-text 
	      text-box-format
	      text-cell-plist))
      (unless (and (<=w new-width remaining-width)
		   (<=w new-height remaining-height))
	;; unless everything fits without ellipsis ...	
	(multiple-value-setq (line-index text-tail text-line)
	  (compute-line-index-in-text-below-height
	    formatted-text text-box-format text-cell-plist
	    remaining-height))
	;; if the following text line is wrapped, unwrap them:
	(let* ((next-tail?
		(if text-tail (find-text-tail-for-line text-tail 2)))
	       (next-line-if-wrapped?
		(if (and next-tail?
			 (=f (get-character-index-past-separator
			       next-tail?)
			     0))
		    (get-next-text-line next-tail?)))
	       (text-line-to-truncate
		(if next-line-if-wrapped?
		    ;; reclaim at end in this case only:
		    (convert-text-to-text-string
		      formatted-text text-tail line-index 0
		      (+f line-index 1)
		      (text-string-length next-line-if-wrapped?)
		      t)
		    text-line))
	       ;; get the indentation, to subtract from the line width:
	       (indentation
		(multiple-value-bind (text-tail indentation)
		    (find-text-tail-and-indentation-for-line formatted-text line-index)
		  (declare (ignore text-tail))
		  indentation))
	       (truncated-text-line
		(truncate-text-line-to-fit-width
		  text-line-to-truncate
		  (if x-magnification?
		      (-w (inverse-magnify
			    (-w remaining-width-excluding-margin indentation)
			    x-magnification?)
			  ;; margins not subject to magnification:
			  right-margin left-margin)
		      (-w remaining-width indentation))
		  (text-cell-font-map text-box-format)
		  (default-word-spacing text-box-format)
		  nil nil t)))
	  (multiple-value-setq (end-line-index end-character-index)
	    (find-end-of-text text-tail line-index))
	  (multiple-value-bind
		(new-text-segment new-width-for-text old-text-segment)
	      (reformat-text
		formatted-text text-box-format
		nil nil nil
		line-index 0
		end-line-index end-character-index
		truncated-text-line
		(if wrap-p remaining-width-excluding-margin widest-width)
		text-cell-plist
		(if wrap-p t))
	    ;; replace old-text-segment with new-text-segment in formatted-text:
	    (cond
	      ((eq old-text-segment formatted-text)
	       (reclaim-text formatted-text)
	       (setq formatted-text new-text-segment))
	      (t
	       (loop for ll = nil then l
		     as l on formatted-text
		     when (eq l old-text-segment)
		       do (setf (cdr ll) new-text-segment)
			  (reclaim-text old-text-segment)
			  (return))))
	    (reclaim-text-string truncated-text-line)
	    (when next-line-if-wrapped?
	      (reclaim-text-string text-line-to-truncate))

	    ;; check for any remaining degenerate cases that need "emergency"
	    ;; action.  Namely, an unbreakable line of great length, e.g., 100
	    ;; "MMM...".  We find these, and change them to end in ellipsis.
	    (multiple-value-setq (formatted-text new-width-for-text)
	      (truncate-text-to-fit-width
		formatted-text
		(if x-magnification?
		    (inverse-magnify remaining-width x-magnification?)
		    remaining-width)
		text-box-format
		;; suppress mag: (don't supply: text-cell-plist)
		nil
		nil nil)))))
      formatted-text)))





;;; The function `truncate-text-line-to-fit-width' ...

(defun truncate-text-line-to-fit-width
    (text-string cutoff-width font-map word-spacing
		 &optional
		 ellipsis-override?
		 ellipsis-width-override?
		 always-append-ellipsis-p)     
  (let* ((ellipsis (or ellipsis-override? ellipsis-text-string))
	 (ellipsis-width
	   (or ellipsis-width-override?	     
	       (compute-width-of-text-line
		 '#w"...." ; 4-dots a kludge!  See note 1
		 nil nil font-map word-spacing)))
	 (num-chars (text-string-length text-string))
	 (ellipsis-length (text-string-length ellipsis))
	 (truncated-length 0)
	 truncated-string)
    (setf cutoff-width (-f cutoff-width ellipsis-width))
    (setf truncated-length
	  (compute-index-in-text-line-below-width
	    text-string nil nil font-map word-spacing cutoff-width))
    (cond ((and (=f num-chars truncated-length)
		(not always-append-ellipsis-p))
	   (copy-text-string text-string)) ;cutoff-width < 0 and num-chars == 0
	  ((=f truncated-length 0)
	   (setf truncated-length
		 (compute-index-in-text-line-below-width
		   ellipsis nil nil font-map word-spacing (+f cutoff-width ellipsis-width)))
	   (copy-portion-of-string-into-text-string
	     ellipsis
	     0 truncated-length
	     (setf truncated-string (obtain-text-string truncated-length))
	     0)
	   truncated-string)
	  (t (copy-portion-of-string-into-text-string
	       text-string
	       0 truncated-length
	       (setf truncated-string
		     (obtain-text-string
		       (+f truncated-length ellipsis-length)))
	       0)
	     (copy-portion-of-string-into-text-string
	       ellipsis
	       0 ellipsis-length
	       truncated-string
	       truncated-length)
	     truncated-string))))

;; Note 1: It looks like the computation of truncate-text-string-to-fit is off
;; by approx. 1/2 a character width, perhaps a roundoff error.  This kludge
;; seems to fix things Until I have time to see why ; the computation is a bit
;; off.  Otherwise, the ellipsis is showing up as ".." sometimes, and as "..."
;; other times.  TBD Later! (MHD 10/28/99)




(defun compute-index-in-text-line-below-width
       (text-line start? end? font-map word-spacing max-width)
  (loop with ab-font = (ab-font (car font-map))
	with i fixnum   = (or start? 0)
	with end fixnum = (or end? (text-string-length text-line))
	with text-x-a fixnum = 0
	with text-x-b fixnum = 0
	with character
	with next-index
	initially
	  (set-text-x text-x-a text-x-b 0)
	while (<f i end)
	do (multiple-value-setq (character next-index)
	     (find-next-character-in-text-line i text-line))
	   (incf-text-x
	     text-x-a text-x-b
	     (if (char=w character #.%space)
		 word-spacing
		 (get-unicode-set-width-as-text-width character ab-font)))
	   (cond
	     ((>w (text-x-to-x text-x-a text-x-b)
		  max-width)
	      (loop-finish))
	     (t
	      (setf i next-index)))
	finally
	  (return i)))



;;; The function `compute-line-index-in-text-below-height' determines the
;;; maximum line index for the text line in text that is completely above
;;; unmagnified-max-height.  Note that unmagnified-max-height should include
;;; include neither y magnification nor any extra height for text-box borders or
;;; margin, as these are not factored in to this computation.

(defun compute-line-index-in-text-below-height
    (text text-box-format text-cell-plist unmagnified-max-height)
  (loop with line-height = (text-cell-line-height text-box-format)
	with line-spacing = (text-cell-line-spacing text-box-format)
	with line-height+spacing = (+w line-height line-spacing)
	with y-magnification?
	  = (y-magnification? text-cell-plist text-box-format)
	with magnified-line-height+spacing
	  = (if y-magnification?
		(magnify line-height+spacing y-magnification?)
		line-height+spacing)
	with height-with-next-line
	  = (if y-magnification?
		(magnify line-height y-magnification?)
		line-height)
	with line-index = 1
	with text-tail = text
	with last-text-line? = nil
	as l on text
	as text-element = (car l)
	do (cond
	     ((text-line-p text-element)
	      (incfw height-with-next-line magnified-line-height+spacing)
	      (setq last-text-line? text-element)
	      (when (>w height-with-next-line unmagnified-max-height)
		(loop-finish))
	      (when (cdr l)
		(setq text-tail (cdr l))
		(incff line-index)))
	     ((and (not (atom text-element)) (eq (car text-element) 'leading))
	      (incfw height-with-next-line (cdr text-element))))
	finally
	  (return (values line-index text-tail last-text-line?))))



;;; The function `truncate-text-to-fit-width' is a variant of
;;; compute-width-of-longest-line, q.v. for doc for args and return values. But
;;; in addition to doing what that function does, it also replaces text lines
;;; whose width is great than cutoff-width, replacing characters at the end with
;;; an ellipsis.  This function returns as its third value true if truncation
;;; happened; otherwise, nil.

(defun truncate-text-to-fit-width
    (text-segment cutoff-width text-box-format text-cell-plist
		  put-in-indentations-and-widths?
		  &optional text-tail-past-text-segment?)
  (loop with word-spacing = (default-word-spacing text-box-format)
	with font-map = (text-cell-font-map text-box-format)
	with x-magnification? = (x-magnification? text-cell-plist text-box-format)
	with width-of-longest-line-so-far = 0
	with indentation = 0
	with line-width?
	with indentation? = nil			; for next line
	with truncation-happened-p = nil
	as l = text-segment then next-l
	as next-l = (cdr l)
	as text-element = (car l)
	do (cond
	     ((text-line-p text-element)
	      (let ((line-width
		     (or line-width?
			 (let ((unmagnified-line-width
				(+w indentation
				    (compute-width-of-text-line
				      text-element nil nil
				      (text-cell-font-map text-box-format)
				      word-spacing))))
			   (if x-magnification?
			       (magnify unmagnified-line-width x-magnification?)
			       unmagnified-line-width)))))
		(when (>w line-width cutoff-width)
		  (setq text-element
			(prog1 (truncate-text-line-to-fit-width
				 text-element (-w cutoff-width indentation)
				 font-map word-spacing)
			  (reclaim-text-string text-element)))
		  (setf (car l) text-element)
		  (setq truncation-happened-p t)
		  (let ((unmagnified-line-width
			 (+w indentation
			     (compute-width-of-text-line
			       text-element nil nil
			       (text-cell-font-map text-box-format)
			       word-spacing))))
		    (if x-magnification?
			(magnify unmagnified-line-width x-magnification?)
			unmagnified-line-width)))
		(if (>w line-width width-of-longest-line-so-far)
		    (setq width-of-longest-line-so-far line-width))
		(cond
		  (line-width?
		   (setq line-width? nil))
		  (put-in-indentations-and-widths?
		   (setf (cdr l) (slot-value-cons text-element (cdr l)))
		   (setf (car l) (slot-value-cons 'line-width line-width)))))
	      (cond
		(indentation?
		 (setq indentation? nil))
		(put-in-indentations-and-widths?
		 (setf (cdr l) (slot-value-cons (car l) (cdr l)))
		 (setf (car l) indentation))))
	     ((fixnump text-element)
	      (setq indentation (setq indentation? text-element)))
	     ((consp text-element)
	      (case (car text-element)
		(line-width
		 (setq line-width? (cdr text-element)))
		(word-spacing
		 (setq word-spacing (cdr text-element))))))
	until (or (null next-l)
		  (eq next-l text-tail-past-text-segment?))
	finally
	  (return
	    (values
	      text-segment
	      width-of-longest-line-so-far
	      truncation-happened-p))))

;; This was adapted from the code for compute-width-of-longest-line.  It would
;; be nice to have less duplicated code.  See if more code can be shared between
;; them! (MHD 4/30/04)





;;;; Component Access to Name Boxes


(def-virtual-attribute name-box
    ((or (class entity)  ;; class for which it's defined - is this correct?
	 (class kb-workspace))
     (or             ;; type spec
       (no-item)
       (structure 
	 ((color (structure
		   ((background-color symbol)
		    (text-color symbol))
		   (and background-color text-color)))
	  (position (or (member at-standard-position)
			(structure
			  ((x-offset integer)
			   (y-offset integer))
			  (and x-offset y-offset)))))))
     ()  ;; "slot features" - are any necessary for this attribute?
     )
  :event-updates nil
  :initial ((class)
	    (declare (ignore class))   ;; someday we may change this
	    nil)
  :getter ((entity)
	   (let ((name-box? (get-name-box-if-any? entity)))
	     (and name-box?
		  (allocate-evaluation-structure-inline
		    'color
		    (allocate-evaluation-structure-inline
		      'background-color
		      (text-box-background-color-ignoring-highlighting
			name-box?)
		      'text-color (text-box-line-color name-box?))
		    'position
		    (allocate-evaluation-structure-inline
		      ;; this is offset in user workspace coordinates
		      ;; of respective left,top pairs.  Should it be
		      ;; center,center or what?
		      'x-offset (-w (left-edge-of-block name-box?)
				    (vertical-midline-of-block entity))
		      'y-offset (-w (horizontal-midline-of-block entity)
				    (top-edge-of-block name-box?)))))))
  :setter ((entity evaluation-value)
	   (let ((name-box? (get-name-box-if-any? entity))
		 (specified-color?
		   (if evaluation-value
		       (evaluation-structure-slot evaluation-value 'color))))
	     (cond
	       ((and specified-color?
		     (or (not (color-or-metacolor-p
				(evaluation-structure-slot specified-color?
							   'text-color)))
			 (not (color-or-metacolor-p
				(evaluation-structure-slot specified-color?
							   'background-color)))))
		(if (color-or-metacolor-p
		      (evaluation-structure-slot specified-color?
						 'text-color))
		    (tformat-text-string
		      "unknown color ~a"
		      (evaluation-structure-slot specified-color? 'background-color))
		    (tformat-text-string
		      "unknown color ~a"
		      (evaluation-structure-slot specified-color? 'text-color))))
	       ((null evaluation-value)
		(when name-box?
		  (delete-frame name-box?)))
	       (t
		(let* ((position? (evaluation-structure-slot evaluation-value 'position))
		       (new-left-edge (when (evaluation-structure-p position?)
					(+w (vertical-midline-of-block entity)
					    (evaluation-structure-slot position? 'x-offset))))
		       (new-top-edge  (when (evaluation-structure-p position?)
					(-w (horizontal-midline-of-block entity)
					    (evaluation-structure-slot position? 'y-offset)))))
		  (let ((allow-name-box-creation (not name-box?)))
		    (update-name-box entity))
		  (setq name-box? (get-name-box-if-any? entity))
		  ;; move the name box into the specified position and
		  ;; set the colors properly
		  (when name-box?
		    (let* ((color? specified-color?)
			   (needs-update? (or position? color?)))
		      (when needs-update?
			(update-images-of-block name-box? t nil))
		      ;; The neat thing about at-standard-position is that we can
		      ;; ignore it -- a newly-created name-box, which this is,
		      ;; is already where it oughta be
		      (when (and new-left-edge new-top-edge)
			(shift-block name-box?
				     (-w new-left-edge
					 (left-edge-of-block name-box?))
				     (-w new-top-edge
					 (top-edge-of-block name-box?)))
			(enlarge-workspace-for-block-rectangle-if-necessary name-box? nil))
		      (when (evaluation-structure-p color?)
			(let ((background-color
				(evaluation-structure-slot color? 'background-color))
			      (text-color
				(evaluation-structure-slot color? 'text-color)))
			  (change-color-of-text-box
			    name-box? t background-color :no-change text-color)))
		      (when needs-update?
			(update-images-of-block name-box? nil nil))))
		  nil))))))
	   

(defun-simple get-name-box-if-any? (frame)
  (loop for subblock being each subblock of frame
	when (frame-of-class-p subblock 'name-box)
	  return subblock))





;;;; Component Access to Text Alignment in Text Boxes


;;; This code deals with the text-alignment virtual attribute for text boxes.
;;; See also text-alignment for charts.  (Conceivably this will some day handle
;;; text alignment for cells of charts as well??)



;;; The `text-alignment' virtual attribute is defined for subclasses of
;;; text-box.  It provides an :initial, :getter, and :setter methods.

;;; This is first being provided as of the 5.0 Rev. 3 release of G2.  No such
;;; virtual attribute existed previously.  There is, and was previously, a part type
;;; text-alignment defined for charts.  There is now, in conjunction with this
;;; virtual attribute, a new "message property" text-alignment that may be defined
;;; in the default-message-properties slot of a message definition.  The underlying
;;; formatting support, and support in text box formats, has been in G2 since its
;;; first release, but never exposed to users as a directly changeable property of
;;; text boxes.

;;; No event-updates service is provides at present.  [Note: this seems quite
;;; doable, but it's not done yet for peers, e.g., text-color, so to not be
;;; different, we've not dealt with it here. (MHD 3/9/98)]

;;; The setter, mostly as an optimization, clears the plist entry if the same
;;; value is set in the backing store.  Note that at present the backing store
;;; value (i.e., in the format) cannot in general be changed: it is defined by
;;; the system, and only changes, if at all, between releases of the product.
;;; This implementation detail should not be noticeable to users.  However, if
;;; text box formats were ordinarily subject to change, this would be
;;; noticeable, and this issue should be revisited to decide what is the right
;;; thing to do.  This uses update-text-box-alignment-override 

(def-virtual-attribute text-alignment
    ((class text-box)
     (member left center right
	     ;; justified		; support JUSTIFIED later!
	     )
     nil)
  :event-updates :within-putter
  :initial
  ((text-box-subclass)
   (or (get-default-text-cell-line-justification text-box-subclass)
       'left))
  
  :getter
  ((text-box)
   (make-evaluation-symbol
     (or (get-text-cell-line-justification
	   (text-box-format text-box)
	   (text-cell-plist-for-text-box text-box))
	 'left)))
  
  :setter
  ((text-box new-text-alignment)
   (update-text-box-alignment-override text-box new-text-alignment)
   nil))

;; Defined/added today. (MHD 3/9/98)




;;; Update-text-box-alignment-override updates the alignment on its argument
;;; text-box by setting value as the value of the text-alignment.
;;;
;;; The value argument should be one of the text alignment symbols, i.e., LEFT,
;;; CENTER, or RIGHT.  JUSTIFIED will always be at least gracefully ignored; it
;;; may be partially honored, and it will most likely be fully supported as the
;;; specification for fully justified text.  However, at this time callers all
;;; can and must provide only legal values: no error checking is done here.
;;;
;;; This handles bringing the formatting text-box's text up-to-date, and does
;;; all of the necessary screen updates to refresh the images of the text box.
;;; This optimizes the change by (a) not updating the text box or its images at
;;; all if there's no change, and (b) restricting the changes on screen to the
;;; area inside of the borders and margins of the text box, thus reducing
;;; somewhat the amount "flashing".
;;;
;;; Note that this assumes that a reformatting for alignment cannot affect the
;;; bounding box of the text.  Thus, reformatting after a change in alignment
;;; does not impact the drawing of subblocks outside the bounding box of the
;;; block.  In addition the (erase/) draw of the block does not extend to
;;; subblocks, and there is no attempt to see if the workspace needs to be
;;; enlarged after the operation.
;;;
;;; This invokes update-subscriptions-from-virtual-attribute-change for the
;;; text-alignment virtual attribute.  This is the one bottleneck for all
;;; run-time changes to text alignment.

(defun-void update-text-box-alignment-override (text-box new-text-alignment)
  (let* ((value
	   (if (eq (get-backing-store-default-text-cell-line-justification
		     (class text-box))
		   (if (eq new-text-alignment 'left) nil new-text-alignment))
	       nil
	       new-text-alignment))
	 (old-value
	   (getfq (text-cell-plist-for-text-box text-box) 'text-alignment)))
    (unless (eq old-value value)      
      (let* ((text-box-format (text-box-format text-box))
	     (inside-left-edge
	       (+w (left-edge-of-block text-box)
		   (text-box-left-border-width text-box-format)
		   (text-cell-left-margin text-box-format)))
	     (inside-top-edge
	       (+w (top-edge-of-block text-box)
		   (text-box-top-border-width text-box-format)
		   (text-cell-top-margin text-box-format)))
	     (inside-right-edge
	       (-w (right-edge-of-block text-box) -3   ; Note 2
		   (text-box-right-border-width text-box-format)
		   (text-cell-right-margin text-box-format)))
	     (inside-bottom-edge
	       (-w (bottom-edge-of-block text-box) -3  ; Note 2
		   (text-box-bottom-border-width text-box-format)
		   (text-cell-bottom-margin text-box-format))))
	(update-images-of-rectangle-of-block ; erase
	  text-box t
	  inside-left-edge inside-top-edge
	  inside-right-edge inside-bottom-edge)
	(change-text-box-property text-box 'text-alignment value) ; set value
	(reformat-text-box-in-place text-box) ; reformat
	(update-images-of-rectangle-of-block ; draw
	  text-box nil
	  inside-left-edge inside-top-edge
	  inside-right-edge inside-bottom-edge)
	(update-subscriptions-from-virtual-attribute-change
	  text-box (virtual-attribute 'text-alignment)
	  'text-box)))))		; see note 1

;; Note 1: we supply the system-defined class TEXT-BOX as the defining-class?
;; variable in the call to update-subscriptions-from-virtual-attribute-change to
;; guard against the obscure chance that a user-defined class could shadow this
;; virtual attribute with an attribute of the same name.

;; Note 2: The -3 (minus three) corrects for a kind of bleeding problem that occurs
;; with right alignments, fixing HQ-1865927. Without this patch, a right
;; alignment will clip some pixels off the rightmost characters of the text,
;; leaving a turd behind if you then realign the text to left or center.
;; The fundamental issue is how to define non-left adjustment, which is
;; presently done by a once-per-line offset from the left that is included
;; in the description of each line of the text, e.g. (60 (lost-characters 0) #w"JJJ")
;; To be more precise and not use a fudge factor like this we would have
;; to redesign the whole mechanism to anchor to a location on the right
;; and work backwards, which is more change than it's worth. mhd,ddm 3/27/98






;;;; Support for Text in Title Bars


(defun-simple get-total-title-bar-text-width (text)
  (loop with text-box-format
	  = (get-or-make-format-frame-function
	      (get-ui-parameter 'title-bar-format))
	for text-element in text
	when (text-line-p text-element)
	  maximize (compute-width-of-text-line
		     text-element nil nil
		     (text-cell-font-map text-box-format)
		     (default-word-spacing text-box-format)
		     nil)))




(defun-void draw-title-bar-text
    (text font-size
	  left-edge-of-cell-in-window top-edge-of-cell-in-window
	  right-edge-of-cell-in-window bottom-edge-of-cell-in-window)
  (let* ((current-text-box-format
	   (get-or-make-format-frame-function
	     (case font-size
	       (small 'left-aligned-menu-item-format-new-small)
	       (t 'left-aligned-menu-item-format-new-large))))
	 (current-text-cell-plist '()))
    ;; fine adjust edges based on font size:
    (case font-size
      (small
       (incfr left-edge-of-cell-in-window 0)
       (incfr top-edge-of-cell-in-window 2)
       (decfr right-edge-of-cell-in-window 20)
       (decfr bottom-edge-of-cell-in-window 2))
      (t
       (incfr left-edge-of-cell-in-window 1)
       (incfr top-edge-of-cell-in-window 2)
       (decfr right-edge-of-cell-in-window 20)
       (decfr bottom-edge-of-cell-in-window 1)))
    (loop with max-width-in-workspace
	    = (delta-x-in-workspace
		(-r right-edge-of-cell-in-window
		    left-edge-of-cell-in-window)
		current-image-x-scale)
	  with text-line = nil
	  with font-map = (text-cell-font-map current-text-box-format)
	  with word-spacing = (default-word-spacing current-text-box-format)
	  for text-element in text
	  when (text-line-p text-element)
	    do (setq text-line text-element)
	    and maximize (compute-width-of-text-line
			   text-element nil nil
			   font-map
			   word-spacing
			   nil)
		  into width-in-workspace
	    and do (loop-finish)
	  finally
	    (unless (null text-line)  ; not really nec.
	      (cond
		((>w (+w width-in-workspace 4) ; 4 for padding
		     max-width-in-workspace)
		 (let ((text-with-ellipsis
			 (convert-text-string-to-text
			   (truncate-text-line-to-fit-width
			     text-line max-width-in-workspace
			     font-map word-spacing))))
		   (draw-text-function
		     text-with-ellipsis
		     left-edge-of-cell-in-window top-edge-of-cell-in-window
		     right-edge-of-cell-in-window bottom-edge-of-cell-in-window)
		   (reclaim-text text-with-ellipsis)))
		(t
		 (draw-text-function
		   text
		   left-edge-of-cell-in-window top-edge-of-cell-in-window
		   right-edge-of-cell-in-window bottom-edge-of-cell-in-window)))))))





;;;; Support for Text in Icons



;;; The implementation of text in icons is based on the implementation of text
;;; boxes, especially for formatting.  Text box formats and texts are used
;;; transiently for text in icons.  However, high-level aspects of text boxes,
;;; in particular of the class text-box and subclasses thereof, are not
;;; user-visible.

;;; This subsection was originally written by Paul Konigsberg in 1996.  It
;;; originally resided in ICONS and CONTROLS.  Some modifications were done, as
;;; well as centralizing in this module, by Mark David in 1999.  The main
;;; advantage of moving it here was (a) getting closely related code that was
;;; previously in three different modules to be in just one; (b) to have the
;;; code be able to take advantage of accessors and macros defined in this
;;; module which it previously had to access using less efficient means; and (c)
;;; to allow the code to (more legitimately) "know" the internals of BOXES ought
;;; not to be known outside of that module.


;;; `Format-text-line-for-icon' returns two values: the formatted text
;;; corresponding to text-line and the width of the longest line in the
;;; resulting formatted text.  Text-line is not reclaimed.  The resulting text
;;; is freshly created and its reclaimation it is the responsibility of the
;;; caller.

(defmacro format-text-line-for-icon (text-line text-box-format)
  `(format-text
     (convert-text-string-to-text (copy-text-string ,text-line))
     ,text-box-format nil 100000 nil nil nil nil nil nil 100000))

;; Note: at present the only use for this is to break the text into lines where
;; there are explicit linebreaks.  Consider creating an optimized variant of
;; format-text does a lot less work to achieve this end.






;;; The macro `get-text-box-format-name-from-font-size' returns the appropriate
;;; text-box format name based on its argument font-size.  This is at present
;;; only intended for use for text in icons.  Font-size should be one of the
;;; supported (user-visible) font size symbols: SMALL, LARGE, EXTRA-LARGE.

(defun-substitution-macro get-text-box-format-name-from-font-size (font-size)
  (case font-size
    (small 'small-statement-format)
    (large 'statement-format)
    (extra-large 'extra-large-statement-format)
    #+development
    (t (cerror
	 "Continue anyway"
	 "Macro get-text-box-format-name-from-font-size got a bad value for font-size: ~a."
	 font-size))))


(defun-substitution-macro window-supports-oriented-text-in-scratchpad-rasters (gensym-window)
  (or (printing-window-p gensym-window)      
      (current-window-supports-this-icp-window-protocol-p
	icp-window-protocol-supports-oriented-text-in-scratchpad-rasters
	gensym-window)))




;;; The macro `text-too-small-to-draw-for-icon-p' is a simplified version of
;;; (forward-defined) macro text-too-small-to-draw-p (in BOXES).

(def-substitution-macro text-too-small-to-draw-for-icon-p
    (text-box-format x-scale y-scale)  
  (<r (delta-y-in-window
	(text-cell-line-height-function text-box-format)
	(minf x-scale y-scale))
      3))

;; This is half the minimum scaled height used for the text-too-small-to-draw-p.
;; We wanted a conservative change at this time.  Also, text is stamped into an
;; icon bitmap, so there is less cost to drawing it repeatedly at smaller
;; scales.  Also, it is arguable that the image qualities of text, as opposed to
;; the information qualities, are more valued in icons than in normal free text.
;; (MHD 12/17/99)



;;; The function `orient-and-scale-and-paint-text' paints a text-line type of
;;; drawing element for paint-one-bitmap-for-icon-on-scratchpad-raster in module
;;; ICONS.

(defun-void orient-and-scale-and-paint-text
  (description-element
   normalized-x-scale normalized-y-scale
   normalized-width normalized-height
   icon-reflection-and-rotation
   color-value)
  (declare (type fixnum
	    normalized-x-scale normalized-y-scale
	    normalized-width normalized-height))
  (when (window-supports-oriented-text-in-scratchpad-rasters current-window)
    (let* ((font (simple-eval-for-icon (fourth description-element)))
	   (text-box-format-name (get-text-box-format-name-from-font-size font))
	   (text-box-format (get-or-make-format-frame text-box-format-name)))
      (unless (text-too-small-to-draw-for-icon-p
	       text-box-format normalized-x-scale normalized-y-scale)
	(let* ((entire-text-line (simple-eval-for-icon (second description-element)))
	       (point (third description-element))
	       (text-drawing-element-reflection-and-rotation
		#+text-element-reflection-rotation
		(when (symbolp (fifth description-element))
		  (fifth description-element))
		#-text-element-reflection-rotation
                icon-reflection-and-rotation)
	       (orientation-code
		(get-orientation-code text-drawing-element-reflection-and-rotation))
	       (x (point-x point))
	       (y (point-y  point))
	       (word-spacing (default-word-spacing text-box-format))
	       (line-spacing (text-cell-line-spacing text-box-format))
	       (line-height  (text-cell-line-height text-box-format))
	       (baseline-position
		(text-cell-baseline-position text-box-format))
	       (font-map (text-cell-font-map text-box-format))
	       (baseline-to-baseline-distance
		(+w (text-cell-line-height text-box-format)
		    line-spacing)))
	  (declare (type fixnum
		    orientation-code x y word-spacing line-spacing line-height 
		    baseline-position baseline-to-baseline-distance))
	  (multiple-value-bind 
	   (formatted-text width-of-longest-line)
	   ;; Note: format is just to handle explicit linebreaks
	   (format-text-line-for-icon entire-text-line text-box-format)
	   (declare (type fixnum width-of-longest-line))
	   (loop with baseline fixnum = y
		 for text-element in formatted-text
		 do
		 (when (text-line-p text-element)
		   (orient-and-scale-and-paint-text-line
		    text-element
		    x baseline width-of-longest-line
		    normalized-x-scale normalized-y-scale
		    normalized-width normalized-height
		    orientation-code
		    text-drawing-element-reflection-and-rotation
		    icon-reflection-and-rotation
		    color-value
		    word-spacing line-spacing line-height baseline-position font-map)
		   (incfw baseline baseline-to-baseline-distance)))
	   (reclaim-text formatted-text)))))))


;; This is a subfunction of the above function:

(defun-void orient-and-scale-and-paint-text-line
     (text-line x y width-of-longest-line
       normalized-x-scale normalized-y-scale
       normalized-width normalized-height
       orientation-code
       orientation-symbol
       icon-reflection-and-rotation
       color-value
       word-spacing line-spacing line-height baseline-position font-map)
  (declare (type fixnum
	     x y width-of-longest-line
	     normalized-x-scale normalized-y-scale
	     normalized-width normalized-height orientation-code
	     word-spacing line-spacing line-height baseline-position))
  (let* ((left-edge x)
	 (baseline y)
	 ;; we add line-spacing in the next two for extra leeway. (MHD)
	 (top-of-line (-w baseline baseline-position))
	 (top-edge (-w top-of-line line-spacing))
	 (bottom-edge (+w (+w top-of-line line-height) line-spacing 4))
	 (right-edge (+w left-edge width-of-longest-line))
	 (oriented-x-scale
	   (oriented-x-value
	     normalized-x-scale normalized-y-scale orientation-code))
	 (oriented-y-scale
	   (oriented-y-value
	     normalized-x-scale normalized-y-scale orientation-code))
	 (scaled-baseline-in-window
	   (delta-y-in-window baseline oriented-y-scale)) ; see note!
	 (scaled-left-edge (delta-x-in-window left-edge oriented-x-scale))
	 (scaled-top-edge (delta-y-in-window top-edge oriented-y-scale))
	 (scaled-right-edge (delta-x-in-window right-edge oriented-x-scale))
	 (scaled-bottom-edge (delta-y-in-window bottom-edge oriented-y-scale))			       
	 (left-edge-of-line-of-text-in-window scaled-left-edge))
    (declare (type fixnum
	       left-edge baseline top-of-line
	       top-edge bottom-edge right-edge
	       oriented-x-scale oriented-y-scale scaled-baseline-in-window
	       scaled-left-edge scaled-top-edge
	       scaled-right-edge scaled-bottom-edge
	       left-edge-of-line-of-text-in-window))
    #+comment  ; draws a line at the baseline, sometimes useful for debugging
    (paint-solid-rectangle-in-current-scratchpad-raster
     left-edge-of-line-of-text-in-window scaled-baseline-in-window
     (-r scaled-right-edge 1) (+r scaled-baseline-in-window 1)
     color-value)
    (orient-and-paint-line-of-text-to-current-scratchpad-raster
      scaled-left-edge scaled-top-edge
      scaled-right-edge scaled-bottom-edge
      normalized-width normalized-height
      text-line
      orientation-symbol
      icon-reflection-and-rotation
      word-spacing
      font-map color-value normalized-x-scale normalized-y-scale
      left-edge-of-line-of-text-in-window scaled-baseline-in-window)))

;; Note that scaled-baseline-in-window, prior to the current release pending,
;; always had 1 pixel added to the baseline position.  This resulted in drift
;; downward.  I don't know why it was there, and neither does pbk.  We've concluded
;; it's a mistake.  We're removing it altogether.  For a time, we considered
;; making a compatibility feature to permit leaving in the mistake, but we decided
;; it's not worthwhile.  (MHD 12/30/99)





;;; The function `compute-edges-for-text-drawing-element' returns as its four
;;; values the left, top, right, and bottom edges corresponding to
;;; line-drawing-element as it would would be rendered with its appropriate
;;; formatting.

(defun compute-edges-for-text-drawing-element (line-drawing-element)
  (let* ((entire-text-line (simple-eval-for-icon (second line-drawing-element)))
	 (point (third line-drawing-element))
	 (font (simple-eval-for-icon (fourth line-drawing-element)))
	 (text-box-format-name (get-text-box-format-name-from-font-size font))
	 (text-box-format (get-or-make-format-frame text-box-format-name))
	 (line-spacing (text-cell-line-spacing text-box-format))
	 (text-line-height
	   (text-cell-line-height text-box-format))
	 (baseline-to-baseline-distance
	   (+w text-line-height line-spacing))
	 (text-line-width 0)
	 (number-of-lines
	   (multiple-value-bind (formatted-text width-of-longest-line)
	       (format-text-line-for-icon entire-text-line text-box-format)
	     (declare (type fixnum width-of-longest-line))
	     (setq text-line-width width-of-longest-line)
	     (prog1 (loop for text-element in formatted-text
			  count (text-line-p text-element))
	       (reclaim-text formatted-text))))
	 (number-of-lines-minus-one (-f number-of-lines 1))
	 (total-baseline-to-baseline-height
	   (*w number-of-lines-minus-one baseline-to-baseline-distance))
	 (text-cell-baseline-position
	   (text-cell-baseline-position text-box-format))
	 (baseline-in-window (point-y point))
	 (font-descent (-f text-line-height text-cell-baseline-position))
	 (left (point-x point))
	 (right (+f left text-line-width))
	 (top (-f baseline-in-window text-cell-baseline-position))
	 (bottom (+f baseline-in-window font-descent total-baseline-to-baseline-height)))
    (declare (type fixnum
	       line-spacing text-line-height baseline-to-baseline-distance
	       text-line-width number-of-lines number-of-lines-minus-one
	       total-baseline-to-baseline-height text-cell-baseline-position
	       baseline-in-window font-descent left right top bottom))
    (values left top right bottom)))

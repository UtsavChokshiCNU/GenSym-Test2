;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module PARSE

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson and Mark H. David






(declare-forward-reference of-class-p-function function) ; in FRAMES1
(declare-forward-reference get-slot-value-function function)	; in FRAMES2
(declare-forward-reference frame-has-been-reprocessed-p-function function) ; in FRAMES2a
(declare-forward-reference reclaim-slot-value function)	; in FRAMES3
(declare-forward-reference make-menu-of-names-from-directory-if-few-enough function)
					; in FRAMES5

;; Consider moving module PARSE past module FRAMES5, to eliminate the above.


;; To EDIT1,2
(declare-forward-reference editor-parameters variable)
(declare-forward-reference set-token-menu-string-to-display-function function)
(declare-forward-reference set-token-menu-string-to-insert-function function)

(declare-forward-reference add-to-directory-of-names function) ; in FRAMES4

(declare-forward-reference make-hfep-hanc-type-function function) ; in HFEP2
(declare-forward-reference reclaim-hfep-hanc-type-function function) ; in HFEP2

(declare-forward-reference parsing-context-cursor-token-function function) ; in EDIT2
(declare-forward-reference parsing-token-incomplete-phrases-function function) ; ditto
(declare-forward-reference current-parsing-context? variable) ; in EVENTS-G2

(declare-forward-reference generate-source-annotation-info variable) ;in DEBUG

(declare-forward-reference reclaim-pending-procedure-signature-workspaces function)

#+development
(declare-forward-reference print-parts-as-structures-p variable) ; in PARTS



;;;; Entering and Exiting Editing Contexts


(def-named-dynamic-extent editing-context
  (module edit))  

(defvar-of-named-dynamic-extent current-edit-state editing-context 
  (global-binding nil))			; nil => not in editing context

(defvar-of-named-dynamic-extent current-edit-workspace editing-context)

(defvar-of-named-dynamic-extent keep-edit-workspace-hidden-no-matter-what?
    editing-context
  (global-binding nil))

;; See handle-parsing-or-compilation-problem for a description of keep-edit-
;; workspace-hidden-no-matter-what?.



(def-kb-specific-property-name directory-of-names reclaim-grammar-tree-function)

;; used to be in FRAMES4




;;;; Context-Free Parser





;;; Parsing the G2 Grammar: Notes on Making It Faster
;;;
;;;
;;; Approaches:
;;;
;;; -get to know the grammar
;;;
;;; - what's a simple-minded way to do context?
;;;
;;;   have separate grammars - would likely get
;;;   a good improvement because with bottom-up,
;;;   it persues things that have nothing to do
;;;   with things: e.g., parsing for object names
;;;   when writing float array initializations
;;;
;;; - what are the litte kernals of grammar
;;;   needed for different high-level contexts?
;;;
;;; - context-sensitive could be done, but it's
;;;   a lot more work
;;;
;;; - this is a good pragmatic step
;;;
;;; - add arg to add-grammar-rule(s) that says which subgrammar
;;;   you're changing
;;;
;;; - Keep adding rules to the global grammar
;;;   as well -- keep a coding convention that your grammar
;;;   rules have to be written so as to fit into the global
;;;   grammar -- this is good for the transition, since it
;;;   allows easy switching and comparison of the old/new
;;;   way, and it allows, down the line, you to shift parts
;;;   of the subgrammars in and out of the global grammar --
;;;   your subgrammar can then always be used in both the
;;;   global and special-purpose way.  (If you didn't have
;;;   grammar that was in both, you could make this a development-
;;;   only feature.  You could also just call it a coding
;;;   convention.  In in-between approach would be to make
;;;   an extra arg to control adding to the global or other
;;;   grammars.
;;;
;;; - should probably do this for the rule/simulator/procedure
;;;   grammars, as well as various subgrammars
;;;
;;; - probably a lot of things =*> number,  symbol, string
;;;
;;; - don't have to go all the way and have a diff. grammar
;;;   for each thing
;;;
;;; - 1 thing: just isolate the procedure grammar - the main
;;; problem case for interactive editing  -- hope for 3 times
;;; faster
;;;
;;; - write a utility to find all grammar rules derived
;;; from a given category, say procedure.
;;;
;;; - 1 thing: just isolate the array initial values slot
;;; grammar -- hope for 10x -- the main problem is actually
;;; space - do first, then procedure
;;;
;;; - in fact, best to automatically generate the grammar
;;; given the top-level category, say procedure, and not
;;; have to go through and wrap wrappers around the various
;;; rules, which range through a large number of sources
;;; in the case of procedures -- this is also a good way
;;; to make the transition, and test it out
;;;
;;; - how to deal with reserved symbols (category UNRESERVED-SYMBOL)
;;;
;;; - now also need to fix menu generation stuff in EDIT
;;;
;;; - generating subgrammars is a good idea - could always to this
;;;   (back to the above idea) -- if space were an issue, you could
;;;   completely partition the global grammar, do the generation at
;;;   compile-time, and get rid of the partitioned global grammar at
;;;   run time


;;; We have fixed this upallowed left-recursion.
;;; To do:
;;; (1) Finish converting add-grammar-rules-for-list to left-recursion.
;;; --> done
;;; (2) Clean up setup of agendas to be efficient.
;;; (3) Add grammar rules should, in the checker, detect loops
;;;     in grammar rules of the form A -> A
;;; (4) The agenda slot, which is now actually two separate slots,
;;;     should be an "included" slot like the other included slots
;;;     that are shared by both category-for-token and
;;;     category-for-category-symbol.
;;; (5) Fix up documentation to advertise the legality of
;;;     left-recursive grammar rules.
;;; (6) Start to fix up hand-written rules that should be left-recursive.
;;; (7) Do the space optimizations advised under
;;;     fill-in-categories-this-can-be-or-begin.
;;; (MHD 3/27/93)

;;;; Annotations

;;; This facility will be used to annotate source code so we will be able to map
;;; from a line of byte code to a source code position.

(def-structure (annotation
		 (:constructor
		   make-annotation
		   (begin-line begin-char-pos))
		 #+development
		 (:print-function print-annotation))
  begin-line
  begin-char-pos)

;;; `clone-annotation' make a new annotation from an existing one

(defun-simple clone-annotation (annotation)
  (make-annotation (begin-line annotation) (begin-char-pos annotation)))

(defun-void reclaim-annotation? (annotation?)
  (when annotation?
    (reclaim-annotation annotation?)))

#+development
(defun print-annotation (ann stream depth)
  (declare (ignore depth))
  (printing-random-object (ann stream)
    (format stream "ANNOTATION (~s,~s)"
	    (begin-line ann)
	    (begin-char-pos ann))))


;;; Each edit-context will contain an `sexp-annotation-hash' which will be used
;;; to maintain the position information of "interesting" things in the parse.
;;; For now, this will be statements.  When the hash-table is reclaimed (which
;;; will happen when the containing-edit-state is reclaimed), the annotations
;;; (the "entries") are reclaimed so don't hold onto them past the edit-state
;;; context.  The sexps (the "keys") are phrase conses, so they will get GC'd as
;;; usual when the edit-state context is exited.

#+SymScale
(def-hash-table sexp-annotation
		:hash-function-or-macro sxhash-symbol
		:constructor make-sexp-annotation-hash
		:accessor get-sexp-annotation-hash
		:reclaimer reclaim-sexp-annotation-hash)

#-SymScale
(defun-simple make-sexp-annotation-hash ()
  (make-eq-hash-table 43 nil #'reclaim-annotation?))

#-SymScale
(defun-simple get-sexp-annotation-hash (sexp hash)
  (eq-gethash hash sexp nil))

(defun-simple set-sexp-annotation-hash (sexp hash annotation)
  #-SymScale
  (setf (eq-gethash hash sexp) annotation)
  #+SymScale
  (setf (get-sexp-annotation-hash sexp hash) annotation))

#-SymScale
(defsetf get-sexp-annotation-hash set-sexp-annotation-hash)

;;; `reclaim-sexp-annotation-hash?' is used by the edit-state.
(defun-void reclaim-sexp-annotation-hash? (hash?)
  (when hash?
    #-SymScale
    (reclaim-eq-hash-table hash?)
    #+SymScle
    (reclaim-sexp-annotation-hash hash?)))



;;;; Edit States and Edit Box Changes



;;; An `edit state' holds the state of an edit, on an edit workspace in an editing
;;; workstation context.

(def-structure (edit-state
		 (:include workstation-context-frame))

  frame-being-edited?
  (serial-number-of-frame-being-edited? nil :reclaimer reclaim-frame-serial-number)

  name-of-slot-being-edited
  defining-class-for-slot-being-edited?
  
  name-of-slot-component-being-edited?	; non-nil when editing a slot component (MHD 1/27/94)
  indicator-of-slot-component-being-edited? ; relevant only when editing a slot component

  type-of-slot-being-edited
  tokenizer-for-slot-being-edited
  free-text-slot-being-edited?

  edit-workspace
  ;; serial-number-of-edit-workspace is obsolete
  ;; now using frame-reference-number-of-workstation-context

  edit-box					; from the edit workspace, not to be deleted
  edit-cursor					;   until the edit workspace is deleted

  text-being-edited				; from the edit box, to be kept formatted

  specific-image-plane-on-which-to-edit-in-place?
  specific-text-box-or-table-on-which-to-edit-in-place?
  left-edge-of-cell-in-table-on-which-to-edit-in-place?
  top-edge-of-cell-in-table-on-which-to-edit-in-place?
  right-edge-of-cell-in-table-on-which-to-edit-in-place?
  bottom-edge-of-cell-in-table-on-which-to-edit-in-place?

  special-entry-context?			; SPECIAL-CHARACTER-ENTRY or KANJI-CODE-ENTRY
					;   or nil; affects RUBOUT, RETURN, etc.
  function-to-call-on-changed-edit-box-text?

  cursor-line-index				; edit (cursor) text position
  cursor-character-index
  text-tail-for-cursor				; corresponds to cursor-line-index

  (parsing-extension-mode? nil)			; NIL, T, END, or
					; NO-AUTOCOMPLETION

  text-tail-for-parsing				; corresponds to car of following stack
  (stack-of-positions-after-tokens nil)		; ({(line-index-for-end-of-token
					;    character-index-after-token
					;    . token-self-terminating?)}
					;  (1 0 . t))
					; maintained as a gensym tree in parallel
					;   with other stacks

  (phrase-rule-completions-past-instance-of-category nil) ; nil for free text
  (stack-of-incomplete-phrases-at-earlier-positions nil)  ; nil for free text, else a stack of
					;   incomplete phrases, maintained
					;   as a gensym list in parallel
					;   with other stacks

  (stack-for-token-menus nil)			; stack of menu content structures and/or
					;   nils, where nil implies menu not computed,
					;   maintained as a gensym list in
					;   parallel with other stacks

  (temporary-information-on-edit-workspace? nil); EDITOR-NOTIFICATION (implying subblocks of
					;   class editor-notification), a menu
					;   content structure (implying subblocks of
					;   class token-menu and/or category-menu),
					;   or nil
					; independently, there may be subblocks of
					;   class kfep-conversion-choice-menu when
					;   kfep-conversion-choices? is non-nil

  (edit-undo-stack				; a gensym list of edit box changes; see below
    nil :reclaimer reclaim-edit-undo-or-redo-stack)
  (edit-redo-stack				; ditto
    nil :reclaimer reclaim-edit-undo-or-redo-stack)

  (chain-of-incomplete-phrases?			; incomplete phrase chain
    nil :reclaimer reclaim-chain-of-incomplete-phrases)

  (vectors-for-phrase-conses			      ; gensym list of managed simple vectors
    nil :reclaimer reclaim-vectors-for-phrase-conses) ;   filled with phrase conses except for
  (vector-index-of-last-recorded-phrase-cons 0)	      ;   the top part of the first vector

  (text-strings-in-phrases			; gensym list of text strings
    nil :reclaimer reclaim-text-strings-in-phrases)
  
  (managed-floats-in-phrases			; gensym list of managed floats
    nil :reclaimer reclaim-managed-floats-in-phrases)

  (managed-longs-in-phrases			; gensym list of managed longs
    nil :reclaimer reclaim-managed-longs-in-phrases)

  (most-recent-reason-for-bad-parse? 
    nil :reclaimer reclaim-most-recent-reason-for-bad-parse?)
					; added by ML, 8 June 89

  (edit-subcommand-menu?		; either a gensym list of buttons (new G2 classic
					;   UI), or a subcommand menu table (old UI)
    nil :reclaimer reclaim-gensym-list-if-list)

  (length-of-edit-undo-stack 0)			; move this!

  (natural-language-for-editor? nil)	; nil (English), JAPANESE, KOREAN, or RUSSIAN (for now)

  ;; Kanji front-end-processing

  (kfep-conversion-text-region? nil)		; implies a Kana/Kanji conversion mode
					;   (see kana-conversion-mode? below);
					;   cannot be or extend past cursor;
					;   empty if at cursor position or if
					;   choices are not to be computed ahead
  (kfep-conversion-choices?			; either (a) nil, (b) a slot value list of
    nil :reclaimer reclaim-slot-value)		;   one or more text string Kanji choices
					;   for the conversion text region, or
					;   (c) a slot value list of the first
					;   choice and the symbol T to indicate
					;   that only the first choice was computed;
					;   nil iff text region is empty
  kfep-conversion-choice-index?			; nil, when the conversion text region is
					;   still unconverted, or else an integer
					;   specifying the choice that is presently
					;   in the conversion text region, as
					;   this integer mod the number of choices
  (kanji-conversion-original-string?		; nil, except when there is a trial kanji
    nil :reclaimer reclaim-slot-value)		;   conversion in the conversion text
					;   region, in which case this is a text
					;   string representing what was converted

  (kana-conversion-mode? nil)			; KATAKANA, HIRAGANA, or nil (for Kanji)

  (height-for-kanji-conversion-choices 95) ; the extra space to leave for Kanji menus


  (menu-of-names-workspace? nil)		; (New.  (MHD 1/8/91))
  (menu-of-names-image-plane? nil)

  (stack-of-tokens nil)				; maintained in parallel ... just development
  #+development
  (stack-of-types-of-tokens nil)		; maintained in parallel ... just development

  (goal-x-in-workspace-for-cursor? nil)		; for up/down line edit commands
  (previous-edit-context-specific-event? nil)	; ditto, for now at least


  (editing-for-runtime-change? nil)		; if true, save text before changing slot value

  (do-not-have-edit-menus? nil)			; if true, don't display edit (parser) 
					;   menus while editing


  (editing-field? nil)				; true => Tab key behaves as enter, and is
					;   recorded as TAB-EXIT in slot below for
					;   perusal by the return function, if any,
					;   and UPDATE function (subcommand button)
					;   is unavailable
  (type-of-exit-from-edit-context? nil)		; NIL, TAB-EXIT, ENTER-EXIT, or ERROR-EXIT
					;   NIL is true in cases of automatic exits
					;   and exits via abort.  (MHD 8/31/92)


  
  

  (hangul-input-mode? nil)			; slots below relevant only when this is
					;  non-nil

  (hfep-Cchar				; These slots are only relevant when inputting
    (make-hfep-hanc-type-function)	;    Hangul.  New.  (MHD 12/22/92)
    :reclaimer reclaim-hfep-hanc-type-function)
  (hfep-Nchar
    (make-hfep-hanc-type-function)
    :reclaimer reclaim-hfep-hanc-type-function)
  (hfep-c-state 0)
  (hfep-c-act 0)
  
  (cyrillic-input-mode? nil)

  (hfep-previous-input-flag nil)
  (scrolling-editor-p nil)


  (menu-choice-index? nil)		; if non-nil, the index of the selected
					;   token choice; indicated we're in
					;   the token-choice component of the
					;   editor (not in the text or subcommands
					;   or kfep options)


  (extra-space-to-leave-below-edit-box? nil) ; between edit box bottom and menus

  (maximum-number-of-names-for-a-menu-override? nil) ; overrides the system table

  
  ;; If `[complex-character-]punctuation-alist-subset-override?' are specified,
  ;; it must be a subset of the variables [complex-character-]punctuation-alist;
  ;; see CHARACTERS.  These are sometimes needed for special-purpose token
  ;; parsing, e.g., to provide better prompting in the case of the pathname
  ;; parser used in the KB load dialog.
  
  (punctuation-alist-subset-override? nil)
  (complex-character-punctuation-alist-subset-override? nil) ; OBSOLETE with wide characters!
					; eliminate after fixing callers / doc! (MHD 2/20/96)

  ;; If `token-menu-class-per-category-overrides?' is non-nil, it should be an
  ;; alist mapping grammar categories to token menu subclasses, overriding the
  ;; default, which uses ..., and TOKEN-MENU as a final default for token
  ;; categories, and CATEGORY-MENU as a final default for non-token categories.
  ;;
  ;; There are two special categories: :all-token and :all-category.  These
  ;; override the default, TOKEN-MENU and CATEGORY-MENU, respectively, as the
  ;; default class to use.
  ;;
  ;; This conses that make up this tree are reclaimed using reclaim-gensym-tree
  ;; upon reclamation of the edit-state structure.
  ;;
  ;; (At present, only the :all-token and :all-category cases are implemented,
  ;; since that's all that's needed; add more later!)
  (token-menu-class-per-category-overrides?
    nil :reclaimer reclaim-gensym-tree-function)


  (do-not-allow-secondary-selection? nil) ; secondary selections usually allowed,
					;   but can be disabled via a
					;   restriction or via the field
					;   editor/new edit-style mechanism
					;   (MHD 8/15/94)


  (never-confirm-cancelled-edit? nil)	; this overrides usual decency extended 
					;   now when an abort is done on changed
					;   edit text.



  (never-post-edit-operations-menu? nil) ; this overrides our natural tendency
					;   to post the "edit operations" menu,
					;   with cut, copy, paste, delete, etc.
					; NOT YET IMPLEMENTED! (MHD 8/18/94)


  (specific-natural-language-for-editor? nil) ; override for slot above,
					;   natural-language-for-editor?

  (frame-style-for-edit-workspace? nil)
  (background-color-for-edit-workspace? nil)
  (text-color-for-edit-workspace? nil)
  (line-index-of-repair-for-bad-parse? nil)
  (character-index-of-repair-for-bad-parse? nil)
  (font-size-override-for-edit-workspace? nil)	; this overrides use of the
					;   font-for-editing slot of
					;   the fonts system table

  (editor-initial-editor-height-override? nil) 	; this overrides whatever else
					;   would be figured out, i.e.,
					;   both the value
						;   in editor-parameters and
						;   the edit-in-place size.
						;   it's also just a minimum.
						;   new. (MHD 1/12/95)
  (text-region-of-edit-state? nil) ; When selecting text inside or outside
                                     ; the editor this is the owner of the
                                     ; text region in question.

  
  
  
  (line-index-of-search-anchor? nil)	; used by incremental search subcontext
  					; marks the starting position
  					;   of the current search
					; nil => uninitialized (should generally
					;   be set to the cursor pos. by search)
  (character-index-of-search-anchor? nil) ; move these !

  (current-paste-request-id? nil)	; non-nil, an ID (fixnum) when awaiting
 					;   a requested paste (protocol not yet implemented!)
  ;; An eq-hash-table of sexps built during parsing, and annotations which contain position info
  (sexp-annotation-hash nil
    :reclaimer reclaim-sexp-annotation-hash?)
  
  (pending-procedure-signature-workspaces nil
    :reclaimer reclaim-pending-procedure-signature-workspaces)

  (table-being-edited? nil)
  (frame-serial-number-of-table-being-edited? nil :reclaimer reclaim-frame-serial-number)

  (attribute-being-edited-is-virtual? nil)
  (editing-using-exported-format? nil)

  (edit-workspace-hidden? nil)

  (initial-cursor-line-index? nil)
  (initial-cursor-character-index? nil)
  ;; Specification for prompts to hide from user.
  (editor-prompt-filter? nil :reclaimer reclaim-gensym-tree-function)

  ;; Next two used only by the native editor. When we switch to the T2 API, then
  ;; they can go on the editor-view object instead.
  (editor-pending-breakpoints nil :reclaimer reclaim-if-text-string)
  (editor-compile-tick 0)

  ;; Mark as t if user use the system procedure g2-ui-close-current-editor
  (being-autoclose-with-system-procedure? nil))


;; This is defined here, rather than in module EDIT, because certain of its
;; slots must be accessed in module PARSE (et al?) for allocation purposes.

;; Reclamation of the the edit workspace, a menu content structure in the
;; temporary-information-on-edit-workspace? slot, and the three stack slots is done
;; by the clean-up method in the workstation context operation handler for editing.

;; If the edit workspace has been deleted, some edit state slots may still point
;; to deleted substructures of that workspace, unless there is special logic to
;; do this cleanup.  But that is OK, since it is verified at appropriate places
;; that the workspace still exists, and the context is exited if it does not.

;; Consider changing "in-phrase" to "for-phrase" in various names.

(def-selection-style-of-workstaton-context edit-state
    editing-and-top-level-is-selection-style)



;;; Added four pseudo-slots to the edit state that maintain
;;; a list of debugging information that is preserved not just
;;; for the edit-workspace, but for change-the-text-of too.

(defun reclaim-most-recent-reason-for-bad-parse? (list)
  (let ((first-reason? (cadddr list)))
    (when first-reason?
      (reclaim-text-string first-reason?))
    (reclaim-gensym-list list)))

(defmacro problem-string-of-most-recent-reason-for-bad-parse? (edit-state)
  (avoiding-variable-capture (edit-state)
    `(car
       (or (most-recent-reason-for-bad-parse? ,edit-state)
	   (setf (most-recent-reason-for-bad-parse? ,edit-state)
		 (gensym-list nil nil nil nil))))))

(defmacro line-index-of-first-reason-for-bad-parse? (edit-state)
  (avoiding-variable-capture (edit-state)
    `(cadr
       (or (most-recent-reason-for-bad-parse? ,edit-state)
	   (setf (most-recent-reason-for-bad-parse? ,edit-state)
		 (gensym-list nil nil nil nil))))))

(defmacro character-index-of-first-reason-for-bad-parse? (edit-state)
  (avoiding-variable-capture (edit-state)
    `(caddr
       (or (most-recent-reason-for-bad-parse? ,edit-state)
	   (setf (most-recent-reason-for-bad-parse? ,edit-state)
		 (gensym-list nil nil nil nil))))))

(defmacro problem-string-of-first-reason-for-bad-parse? (edit-state)
  (avoiding-variable-capture (edit-state)
    `(cadddr
       (or (most-recent-reason-for-bad-parse? ,edit-state)
	   (setf (most-recent-reason-for-bad-parse? ,edit-state)
		 (gensym-list nil nil nil nil))))))

#+unused
(defun clear-most-recent-reason-for-bad-parse? (edit-state)
  (when (most-recent-reason-for-bad-parse? edit-state)
    (setf (car (most-recent-reason-for-bad-parse? edit-state)) nil
	  (cadr (most-recent-reason-for-bad-parse? edit-state)) nil
	  (caddr (most-recent-reason-for-bad-parse? edit-state)) nil)
	  (cadddr (most-recent-reason-for-bad-parse? edit-state)) nil))



;;; `Note-use-of-text-string-in-phrase' ...

;;; `Reclaim-text-strings-in-phrases' ...

(defun-simple note-use-of-text-string-in-phrase (text-string)
  (setf (text-strings-in-phrases current-edit-state)
	(gensym-cons text-string (text-strings-in-phrases current-edit-state)))
  text-string)

(defun-void reclaim-text-strings-in-phrases (text-strings-in-phrases)
  (loop for text-string in text-strings-in-phrases
	do (reclaim-text-string text-string))
  (reclaim-gensym-list text-strings-in-phrases))



;;; `Note-use-of-managed-float-in-phrase' ...

;;; `Reclaim-managed-floats-in-phrases' ...

(defun-simple note-use-of-managed-float-in-phrase (managed-float)
  (setf (managed-floats-in-phrases current-edit-state)
	(gensym-cons managed-float (managed-floats-in-phrases current-edit-state)))
  managed-float)

(defun-simple note-use-of-managed-long-in-phrase (managed-long)
  (setf (managed-longs-in-phrases current-edit-state)
	(gensym-cons managed-long (managed-longs-in-phrases current-edit-state)))
  managed-long)

(defun-void reclaim-managed-floats-in-phrases (managed-floats-in-phrases)
  (loop for managed-float in managed-floats-in-phrases
	do (reclaim-managed-float managed-float))
  (reclaim-gensym-list managed-floats-in-phrases))

(defun-void reclaim-managed-longs-in-phrases (managed-longs-in-phrases)
  (loop for managed-long in managed-longs-in-phrases
	do (reclaim-managed-long managed-long))
  (reclaim-gensym-list managed-longs-in-phrases))

;;; A `phrase sequence' is a phrase cons whose car is a list of elements and whose
;;; cdr is a unique cons, the value of phrase-sequence-marker.

;;; A `phrase structure' is similar .... (Note: a phrase structure has nothing
;;; to do with phrase structure grammars, or anything of the sort; it's just the
;;; implementation of temporary structures during the parsing context, i.e.,
;;; using "phrase conses", "phrase strings", etc.)

(defvar-of-special-global phrase-sequence-marker (list 'phrase-sequence))
(defvar-of-special-global phrase-structure-marker (list 'phrase-structure))
(defvar-of-special-global phrase-item-denotation-marker (list 'phrase-item-denotation))
(defvar-of-special-global phrase-item-marker (list 'phrase-item))

(defmacro make-phrase-sequence (phrase-list-of-elements)
  `(phrase-cons ,phrase-list-of-elements phrase-sequence-marker))

(defmacro make-phrase-structure (phrase-property-list)
  `(phrase-cons ,phrase-property-list phrase-structure-marker))

(defmacro make-phrase-item-denotation (symbol-or-phrase-list-of-symbols)
  `(phrase-cons ,symbol-or-phrase-list-of-symbols phrase-item-denotation-marker))

(defmacro make-phrase-item (item)
  `(phrase-cons ,item phrase-item-marker))


(def-substitution-macro phrase-sequence-p (phrase)
  (and (consp phrase)
       (eq (cdr-of-cons phrase) phrase-sequence-marker)))

(def-substitution-macro phrase-structure-p (phrase)
  (and (consp phrase)
       (eq (cdr-of-cons phrase) phrase-structure-marker)))

(def-substitution-macro phrase-item-denotation-p (phrase)
  (and (consp phrase)
       (eq (cdr-of-cons phrase) phrase-item-denotation-marker)))

(def-substitution-macro phrase-item-p (phrase)
  (and (consp phrase)
       (eq (cdr-of-cons phrase) phrase-item-marker)))

(defmacro copy-phrase-sequence (phrase-sequence)
  `(make-phrase-sequence
     (copy-for-phrase (car ,phrase-sequence))))

(defmacro copy-phrase-structure (phrase-structure)
  `(make-phrase-structure
     (copy-for-phrase (car ,phrase-structure))))

(defmacro copy-phrase-item-denotation (phrase-structure)
  `(make-phrase-item-denotation
     (copy-for-phrase (car ,phrase-structure))))

(defmacro copy-phrase-item (phrase-structure)
  `(make-phrase-item
     (copy-for-phrase (car ,phrase-structure))))

;;; An `edit undo (or redo) stack' is a gensym list of edit box changes.

;;; An `edit box change' is a structure that is useful for undoing (or redoing)
;;; a change.

(def-structure (edit-box-change
		 (:constructor
		   make-edit-box-change
		   (special-type-of-edit-box-change?		     
		    line-index-of-old-and-new-text-segment
		    line-index-where-difference-in-texts-starts
		    character-index-where-difference-in-texts-starts
		    line-index-past-old-text-segment
		    line-index-past-new-text-segment
		    old-text-segment
		    old-width-for-text
		    old-cursor-line-index
		    old-cursor-character-index
		    old-position-for-kfep-conversion-text-region?)))

  special-type-of-edit-box-change?		; nil, AUTOMATIC, KFEP-CONVERSION,
						;   or TYPED-IN-SPACE-OR-\@
  line-index-of-old-and-new-text-segment
  line-index-where-difference-in-texts-starts
  character-index-where-difference-in-texts-starts

  line-index-past-old-text-segment
  line-index-past-new-text-segment

  (old-text-segment nil :reclaimer reclaim-slot-value)	; a text (or nil before reclaiming)
  old-width-for-text
  old-cursor-line-index
  old-cursor-character-index
  (old-position-for-kfep-conversion-text-region?	; nil or a gensym cons
    nil :reclaimer reclaim-gensym-tree))	        ;   (line-index . character-index)

;; Consider, in change-edit-box, combining successively typed non-space characters into a
;; single edit box change.

;; Consider representing insertions within a single line more efficiently, by keeping
;; the number of characters inserted in an old-text-segment-or-length-of-insertion slot.
;; This would require: renaming, redocumenting, and changing the reclaimer for the
;; old-text-segment slot; revising change-edit-box to recognize this case, store the
;; length, and reclaim the unused text segment; and revising undo-or-redo-edit
;; appropriately.

;; Consider also keeping distance-from-left-to-where-difference-starts?, old-cursor-x-
;; in-workspace, and old-cursor-y-in-workspace herein.

;; Consider restoring the state of kana-conversion-mode? on undos and redos.

;; Note that character-index-where-difference-in-texts-starts, line-index-past-old-
;; text-segment,and old-width-for-text are kept only to avoid recomputation while
;; undoing or redoing.

;; Note also that change-edit-box does not use the special-type-of-edit-box-change?,
;; line-index-where-difference-in-texts-starts, and character-index-where-difference-
;; in-texts-starts slots (though these are each used in undo-or-redo-edit) and
;; accesses each of the others exactly once.



;;; `Reclaim-edit-undo-or-redo-stack' reclaims edit-undo-or-redo-stack.

(defun reclaim-edit-undo-or-redo-stack (edit-undo-or-redo-stack)
  (loop for edit-box-change in edit-undo-or-redo-stack
	do (reclaim-edit-box-change edit-box-change))
  (reclaim-gensym-list edit-undo-or-redo-stack))


;;;; Annotation functionality that depends on edit-state

;;; `get-current-sexp-annotation-hash' is an abstraction on top of an edit-state
;;; slot access

(defun-simple get-current-sexp-annotation-hash ()
  (or (sexp-annotation-hash current-edit-state)
      #-SymScale
      (setf (sexp-annotation-hash current-edit-state) ; just in case. (parse-text-string, etc.)
	    (make-sexp-annotation-hash))
      #+SymScale
      (let ((new-hash (make-sexp-annotation-hash)))
	(if (compare-and-swap (sexp-annotation-hash current-edit-state) nil new-hash)
	    new-hash
	  (prog1 (sexp-annotation-hash current-edit-state)
	    (reclaim-sexp-annotation-hash? new-hash))))))


;;; `get-current-annotation-context' is an abstraction on top of the hash lookup
;;; for an annotation given an sexp

(defun-simple get-current-annotation-context (sexp)
  (get-sexp-annotation-hash sexp (get-current-sexp-annotation-hash)))


;;; `set-current-annotation-context' is an abstraction on top of the hashing
;;; for an annotation given an sexp

(defun-simple set-current-annotation-context (sexp annotation)
  (setf (get-sexp-annotation-hash sexp (get-current-sexp-annotation-hash)) annotation))

;;; The macro `with-current-annotation-for-sexp's job is to manage calls to the
;;; annotation hashing facility to keep them sane.  I.E.  Make sure that we
;;; handle the case when the old hashed annotation for an sexp is lost during
;;; execution of the body (typically because list structure was destructively
;;; modified). 

(defmacro with-current-annotation-for-sexp (sexp &body body)
  (let ((sexp-var (gensym))
	(current-annotation? (gensym))
	(lost-annotation? (gensym)))
    `(let* ((,sexp-var ,sexp)
	    (,current-annotation? (and generate-source-annotation-info
				       (consp ,sexp-var)
				       (get-current-annotation-context
					 ,sexp-var))))
       (prog1 (progn ,@body)
	 ;; This may be completely unnecessary if we lose the hash-table idea
	 ;; and go with the array/list.
	 ;; This may never get called now that we moved to an EQ hash table,
	 ;; so look into and remove if so -dkuznick, 1/25/99
	 (when ,current-annotation?
	   (let ((,lost-annotation? (get-current-annotation-context ,sexp-var)))
	     (when (and (neq ,current-annotation?
			     ,lost-annotation?))
	       ;; Someone modifed list structure out from under us, so we need to
	       ;; rehash.  Notice we'll have the old key still in the hashtable,
	       ;; but there's really nothing we can do about that. Advantages are
	       ;; no one can hurt us by modifying list structure in various
	       ;; compilers, disadvantages are it fills the hash table up with junk 
	       ;; THINK ABOUT THIS!! -dkuznick, 12/21/98
	       (set-current-annotation-context
		 ,sexp-var (clone-annotation ,current-annotation?)))))))))






;;;; Phrase Conses



;;; `Phrase conses' are used in parsing and slot value compilers for temporary
;;; structures that are certain to be garbage (and therefore can be entirely
;;; recycled) after parsing is finished and its results have been "compiled"
;;; (where necessary) and copied prior to storage as a slot value.  (See below,
;;; and also def-slot-value-compiler in module FRAMES3 (previously KB-FRAMES).)

;;; Phrase consing may only be done when special variable current-edit-state
;;; is appropriately bound.  A phrase cons is implemented as a gensym cons that
;;; is recorded in the current edit state and subsequently reclaimed when the
;;; edit state is reclaimed.

(defconser phrase-pool)

;;; `Phrase-cons' is like cons except that it uses an available phrase cons.  It
;;; also ensures that the list of available phrase conses does not get depleted.

;;; `Phrase-cons-macro' is a slightly faster version of phrase-cons.

(declare-function-type add-another-vector-for-phrase-conses () (t))

(defun add-another-vector-for-phrase-conses ()
  #-SymScale
  (setf (vectors-for-phrase-conses current-edit-state)
	(phrase-pool-cons
	  (allocate-managed-simple-vector 64)	; 64 occurs also below
	  (vectors-for-phrase-conses current-edit-state)))
  #+SymScale
  (phrase-pool-push-atomic (allocate-managed-simple-vector 64)
			   (vectors-for-phrase-conses current-edit-state))
  (setf (vector-index-of-last-recorded-phrase-cons current-edit-state)
	#.(- 64 1)))

;; Not thread-safe ...
(defmacro record-phrase-cons (phrase-cons)
  (let ((vector-index-of-last-recorded-phrase-cons (gensym)))
    `(let ((,vector-index-of-last-recorded-phrase-cons
	    (atomic-decff (vector-index-of-last-recorded-phrase-cons
			   current-edit-state))))
       (declare (type fixnum ,vector-index-of-last-recorded-phrase-cons))
       (if (<f ,vector-index-of-last-recorded-phrase-cons 0)
	   (setq ,vector-index-of-last-recorded-phrase-cons
		 (add-another-vector-for-phrase-conses)))
       (setf (svref (car (vectors-for-phrase-conses current-edit-state))
		    ,vector-index-of-last-recorded-phrase-cons)
	     ,phrase-cons))))

#+SymScale
(defmacro phrase-cons-macro (x y)
  (let ((cons (make-symbol "CONS")))
    `(let ((,cons (phrase-pool-cons-macro ,x ,y)))
       (if current-edit-state
	   (record-phrase-cons ,cons)
	 ,cons))))

#+ignore ; SymScale (option 2)
(defmacro phrase-cons-macro (x y)
  `(phrase-pool-cons-macro ,x ,y))

#-SymScale
(defmacro phrase-cons-macro (x y)
  `(record-phrase-cons (phrase-pool-cons-macro ,x ,y)))


;;; As long as memory meters for phrase-conses are not declared as side-effect
;;; free, we can declare phrase-cons (and the function versions of phrase-list)
;;; as side-effect-free functions.

(declare-side-effect-free-function phrase-cons)

(defun-simple phrase-cons (x y)
  (phrase-cons-macro x y))



;;; `Phrase-list' is a macro that is equivalent to list except that it does phrase
;;; consing.

;;; `Make-phrase-list' is like make-list with only a length argument, except that it
;;; does phrase consing and leaves the cars of the conses undefined.

(defmacro phrase-list (&rest elements)
  (cond
    ((null elements)
     nil)
    ((null (cdr elements))
     `(phrase-cons ,(car elements) nil))
    ((null (cddr elements))
     `(phrase-list-2 ,@elements))
    ((null (cdddr elements))
     `(phrase-list-3 ,@elements))
    ((null (cddddr elements))
     `(phrase-list-4 ,@elements))
    (t
     `(set-list-contents
	(make-phrase-list ,(length elements))
	,@elements))))

(declare-side-effect-free-function phrase-list-2)

(defun-simple phrase-list-2 (first second)
  (set-list-contents (make-phrase-list 2) first second))

(declare-side-effect-free-function phrase-list-3)

(defun-simple phrase-list-3 (first second third)
  (set-list-contents (make-phrase-list 3)
		     first second third))

(declare-side-effect-free-function phrase-list-4)

(defun-simple phrase-list-4 (first second third fourth)
  (set-list-contents (make-phrase-list 4)
		     first second third fourth))

(declare-function-type make-phrase-list (t) (t))

(declare-side-effect-free-function make-phrase-list)

(defun make-phrase-list (count)
  (loop with phrase-list = (make-phrase-pool-list-macro count)
	as phrase-cons on phrase-list
	do (record-phrase-cons phrase-cons)
	finally (return phrase-list)))




;;; The macro `phrase-list*' is like list*, in that the last argument is the cdr
;;; of the last cons created.  Note that this expands into lots of calls to
;;; phrase-cons, and so is not especially efficient, but it is convenient to
;;; use.

(defmacro phrase-list* (arg &rest other-args)
  (if other-args
      `(phrase-cons ,arg (phrase-list* ,(car other-args) ,@(cdr other-args)))
      arg))




;;; The macro `phrase-push' takes an item and a location, phrase conses the item
;;; onto the front of the list stored in location, stores the new list into the
;;; location, and returns the new list.

(defmacro phrase-push (item location)
  (cond ((symbolp location)
	 `(setf ,location (phrase-cons ,item ,location)))
	((or (symbolp item) (constantp item))
	 `(modify-macro-for-phrase-push ,location ,item))
	(t
	 (let ((item-var (gensym)))
	   `(let ((,item-var ,item))
	      (modify-macro-for-phrase-push ,location ,item-var))))))

(define-modify-macro modify-macro-for-phrase-push (item)
  phrase-cons-with-args-reversed)

(defun phrase-cons-with-args-reversed (cdr car)
  (phrase-cons car cdr))




;;; `Copy-list-using-phrase-conses' copies list? using phrase conses.

(declare-function-type copy-list-using-phrase-conses (t) (t))

(defun copy-list-using-phrase-conses (list?)
  (if (not (consp list?))
      list?
      (loop with new-list = (phrase-cons (car list?) (cdr list?))
	    with last-new-cons = new-list
	    with current-copy-position = (cdr list?)
	    until (not (consp current-copy-position))
	    do (setf (cdr last-new-cons)
		     (phrase-cons
		      (car current-copy-position)
		      (cdr current-copy-position)))
	       (setf last-new-cons (cdr last-new-cons))
	       (setf current-copy-position (cdr current-copy-position))
	    finally (return new-list))))



;;; `Reclaim-vectors-for-phrase-conses' ... refers to structure-being-reclaimed.

(defun reclaim-vectors-for-phrase-conses (vectors-for-phrase-conses)
  (loop for managed-simple-vector in vectors-for-phrase-conses
	as start-index
	   = (vector-index-of-last-recorded-phrase-cons structure-being-reclaimed)
	   then 0
	do (loop for i from start-index
		       below (length		; just 64?
			       (the simple-vector managed-simple-vector))
		 do (reclaim-phrase-pool-cons-macro
		      (svref managed-simple-vector i)))
	   (reclaim-managed-simple-vector managed-simple-vector))
  (reclaim-phrase-pool-list vectors-for-phrase-conses))




;;; Copy-tree-using-phrase-conses ...

(defun copy-tree-using-phrase-conses (x)
  (if (atom x)
      x
      (phrase-cons
	(copy-tree-using-phrase-conses (car x))
	(copy-tree-using-phrase-conses (cdr x)))))






;;; `phrase-copying-needs-annotation-rehashing' should be bound to non-NIL if
;;; copy-for-phrase needs to worry about rehashing annotations.  See
;;; documentation above maybe-annotate-constituent for more info.

(defvar phrase-copying-needs-annotation-rehashing nil)


;;; `Copy-for-phrase' copies value-for-phrase, a phrase or a slot value,
;;; by:
;;;
;;;    (1) Copying "special conses":
;;;
;;;      (1a) copying a managed float as a managed float;
;;;
;;;      (1b) copying a phrase sequence as such, with recursive
;;;         copying of each element;
;;;
;;;      (1c) copying a phrase structure as such, with recursive
;;;         copying of each name/value pair;
;;;
;;;      (1d) copying an item-denotation as such, with recursive
;;;         copying of the denotation;
;;;
;;;      (1e) copying a phrase-item as such by calling make-phrase-item
;;;
;;;    (2) copying a cons as a phrase cons, with recursive copying of
;;;        the car and cdr;
;;;
;;;    (3) copying a string as a text string;
;;;
;;;    (4) copying a gensym float (e.g., a float produced by
;;;        reading in 12.3 typed into the Lisp sources) as a
;;;        managed float [the foregoing was not done prior to
;;;        approximately 4/7/94]; and
;;;
;;;    (5) leaving anything else as is
;;;    

(defun-simple copy-for-phrase (value-for-phrase)
  (cond
    ((text-string-p value-for-phrase)
     (note-use-of-text-string-in-phrase 
       (copy-text-string value-for-phrase)))
    ((managed-float-p value-for-phrase)
     (note-use-of-managed-float-in-phrase
       (copy-managed-float value-for-phrase)))
    ((phrase-sequence-p value-for-phrase)
     (copy-phrase-sequence value-for-phrase))
    ((phrase-structure-p value-for-phrase)
     (copy-phrase-structure value-for-phrase))
    ((phrase-item-denotation-p value-for-phrase)
     (copy-phrase-item-denotation value-for-phrase))
    ;; I'm not convinced we need the following clause, but I don't think it's
    ;; wrong to have it.  It's certainly safer.  -dkuznick, 2/7/05
    ((phrase-item-p value-for-phrase)
     (copy-phrase-item value-for-phrase))
    ((gensym-float-p value-for-phrase)		; new. (MHD 4/4/94)
     (note-use-of-managed-float-in-phrase
       (allocate-managed-float value-for-phrase)))
    ((atom value-for-phrase)
     value-for-phrase)
    (t
     (let ((new-phrase-list (phrase-cons
			      (copy-for-phrase (car value-for-phrase))
			      (copy-for-phrase (cdr value-for-phrase)))))
       ;; We could avoid the following check each time through copy-for-phrase,
       ;; if we split copy-for-phrase into two different functions using some
       ;; macrology.  Then we wouldn't need the global and callers would just
       ;; need to know which to call, which they do already.  Too many diffs
       ;; for not enough benefit this late in the release cycle (8.1)
       ;; -dkuznick, 3/13/05
       (when phrase-copying-needs-annotation-rehashing
	 (let ((annotation? (get-current-annotation-context
			      value-for-phrase)))
	   (when annotation?
	     (set-current-annotation-context
	       new-phrase-list (clone-annotation annotation?)))))
       new-phrase-list))))

;; Added the gensym-float-p clause to allow us to say things like
;; (copy-for-phrase 1.0).  It also corresponds to some documentation
;; below that claims this should work.  (MHD 4/4/94)

;; This is used at present in PARTS, RULES, and EDIT.  

;; Its use in EDIT is in the update case for copying a phrase before handing
;; it off to a slot value compiler, lest it be mutated and then used in a
;; mutated state by the editor after the update.  See try-to-end-editing.
;; (MHD 1/30/92)






;;; `With-phrase-conses' allows phrase consing within body and reclaims all
;;; such phrase conses after body has been evaluated.  Thus structures built
;;; with phrase conses in body must be copied if they are to be retained,
;;; perhaps using copy-for-slot-value.  If a nested edit-state is being created,
;;; the sexp-annotation-hash from the outer table is installed in the new table to
;;; allow lookups to function correctly.  It must only be reclaimed when the
;;; outermost edit-state is reclaimed.  With-phrase-conses is currently used for
;;; compiling outside the editor, in modules FILES, RULES, and PROC-COMP.
;;;  With-phrase-conses is somewhat slow.

(defmacro with-phrase-conses (&body body)
  (let ((annotation-hash? (gensym))
	(old-edit-state? (gensym)))
    `(let ((,old-edit-state? current-edit-state)
	   (,annotation-hash? (and generate-source-annotation-info
				   (or (when current-edit-state
					 (get-current-sexp-annotation-hash))
				       (make-sexp-annotation-hash))))
	   (current-edit-state (make-edit-state)))
       (setf (sexp-annotation-hash current-edit-state) ,annotation-hash?)
       ;; This needs to be a multiple-value-prog1
       ;; for uses like in create-compiled-cell-expression to work.
       ;; -alatto, 12/3/02v
       (multiple-value-prog1
	   (progn . ,body)
	 ;;Make sure nested hash-table doesn't get reclaimed.  It'll get
	 ;; reclaimed upon reclamation of outermost edit-state
	 (when ,old-edit-state?
	   (setf (sexp-annotation-hash current-edit-state) nil))
	 (reclaim-edit-state current-edit-state)))))

;;; `with-attribute-export-conclude-context' - is like with-phrase-conses,
;;; but also sets frame-being-edited? of the whipped-up edit state to
;;; be something appropriate.

(defmacro with-attribute-export-conclude-context (frame &body body)
  `(let ((current-edit-state (make-edit-state)))
     (setf (frame-being-edited? current-edit-state) ,frame)
     (prog1 (block attribute-export-conclude-context
	      (return-from attribute-export-conclude-context
		(progn . ,body)))
       (reclaim-edit-state current-edit-state))))



;;;; Phrase Floats / Longs



;;; A `phrase float' is a representation for a float in a phrase.  At present, a
;;; phrase float is represented as a managed float.  (Prior to 8/25/91 in 3.0,
;;; phrase floats were represented as gensym floats.)

;;; In addition to the functions and macros provided below, note also that copy-
;;; for-phrase can be used to copy a phrase float (or a slot value float or a
;;; gensym float, or other things, too).  See its documentation.




;;; `Phrase-float-p' is true if value-for-slot is a phrase float.

(defmacro phrase-float-p (value-for-slot)
  `(managed-float-p ,value-for-slot))

(defmacro phrase-long-p (value-for-slot)
  `(managed-long-p ,value-for-slot))


;;; `Phrase-float-value' returns the gensym-float representation of phrase-float.
;;; Note that this should only be called in a temporary context, since otherwise
;;; it will create a permanent gensym float, which would represent a leak.

(defmacro phrase-float-value (phrase-float)
  `(managed-float-value ,phrase-float))

(defmacro phrase-long-value (phrase-long)
  `(managed-long-value ,phrase-long))


;;; `Make-phrase-float' makes a phrase float equivalent in value to
;;; gensym-float, and notes the use of the use of that float in the current edit
;;; state.

(defmacro make-phrase-float (gensym-float)
  `(note-use-of-managed-float-in-phrase
     (allocate-managed-float ,gensym-float)))

(defmacro make-phrase-long (gensym-long)
  `(note-use-of-managed-long-in-phrase
     (allocate-managed-long ,gensym-long)))

;; Consider making this a macro later for speed. (MHD 9/13/91) -- Made a simple
;; function for now.  (MHD 4/11/94) Making it a macro to get rid of the unneeded
;; float consing caused by a function boundary.  -jra 7/5/96




;;; `Phrase-number-p' is true if phrase-or-token represents a number.

(defun phrase-number-p (phrase-or-token)
  (or (numberp phrase-or-token)			; test fixnump first for speed?
      (phrase-float-p phrase-or-token)
      (phrase-long-p phrase-or-token)))


;;; `Phrase-number-value' gets the gensym-float from phrase-number,
;;; if it is a phrase-float, and otherwise just returns phrase-number.
;;; Note that this should only be called in a temporary context, because
;;; otherwise it might create a permanent gensym float, which would represent
;;; a leak.

(def-substitution-macro phrase-number-value (phrase-number)
  (cond ((phrase-float-p phrase-number)
	 (phrase-float-value phrase-number))
	((phrase-long-p phrase-number)
	 (phrase-long-value phrase-number))
	(t
	 phrase-number)))




;;; `Make-managed-float-from-phrase-float' makes a new managed float equivalent in
;;; value to phrase-float.  This does NOT note the use of the new managed float
;;; in the current edit state.

(defmacro make-managed-float-from-phrase-float (phrase-float)
  `(copy-managed-float ,phrase-float))





;;; Atomic-phrase-p is true if x is a either an atom or a phrase float.

(defun atomic-phrase-p (x)
  (or (atom x)
      (phrase-float-p x)
      (phrase-long-p x)))

;; Added for use in FUNCTIONS by the tabular functions facility.  (MHD 9/12/91)







;;;; Grammar Conses



;;; Grammar conses are used in modules PARSE and EDIT.

(defconser grammar parse)


;;; Grammar-conc-new is specialized for use in constructing grammars.  If
;;; element is not eq to any existing element found in place, which should be
;;; setf'able and evaluate to to a list, it nconcs element, listed using grammar
;;; conses, onto place.  It does not follow usual evaluation conventions, for
;;; efficiency, and because it's not generally exported.

(defmacro grammar-conc-new (place element)
  `(let ((l ,place))
     (cond
       ((null l)
	(setf ,place (grammar-list ,element)))
       ((not (memq ,element l))
	(nconc l (grammar-list ,element))))))








;;; Set-nth-element-of-variable-length-grammar-list replaces the nth element of
;;; list, a "variable-length list" with value, returning a list with the minimal
;;; number of elements.  This function may alter the structure of its argument
;;; list.  This uses the grammar conser for consing and reclaiming conses.

;;; A `variable-length list' is one that grows adds and removes "extension
;;; elements" as needed at the end.  If such a list is not long enough, extra
;;; elements whose values are extension-element are added (here using grammar
;;; conses).  If the tail of list would end up being all extension-element
;;; (tested using EQL), the conses that make up that tail are removed from the
;;; list and reclaimed.

(defun set-nth-element-of-variable-length-grammar-list
       (list n value &optional extension-element)
  (let ((size (length list)))
    (unless (<f n size)
      (setq list				; changes arg
	    (nconc list
		   (loop repeat (-f (1+f n) size)
			 collect extension-element using grammar-cons))))
    (setf (nth n list) value)
    (let* ((index?
	     (position extension-element list :from-end t :test-not #'eql)))
      (cond
	((null index?)
	 (reclaim-grammar-list list)
	 nil)
	(t
	 (let ((tail (nthcdr index? list)))
	   (reclaim-grammar-list (cdr tail))
	   (setf (cdr tail) nil)
	   list))))))

;; There is a slight chance this could cons if keyword args to CL functions
;; can cons, i.e., the call to position.  This is not used at runtime, so
;; we are not concerned by this at present.

;; This is not coded for maximum efficiency because it needn't be.  We hope
;; it is clearer this way.

;; A utility function that maybe should be generated for other cons pools
;; or generalized to make specifying which cons pool possible.




;;;; Grammar Rules



;;; A `grammar rule' is either of the form
;;;
;;;    (category-symbol instance-rule-element . transformation-list)
;;;
;;; known as an `instance rule', or of the form
;;;
;;;    (phrase-category-symbol phrase-rule-elements . transformation-list)
;;;
;;; known as a `phrase rule', where `rule element' can be a `category symbol' or
;;; quoted token, and where a `transformation list' is of the form
;;;
;;;    (transformation-template {transformation-operation})
;;;
;;; A `quoted token' is of the form (quote token), i.e., 'token, where token can
;;; be identified by an eql test and can be printed appropriately in a token
;;; menu.  Punctuation tokens may be symbols (e.g. \,) or characters (e.g. #\,),
;;; as long as they are consistently represented.

;;; Note that phrase-rule-elements must be a list of two or more rule elements.
;;; Note that during the development of G2 4.0, the restrictions of having
;;; grammars was lifted; left-recursive grammars are now allowed.

;;; Grammar rules are `added' one-by-one to a G2 environment while the modules that make
;;; up G2 are being loaded; see the functions add-grammar-rule and add-grammar-rules.

;;; When a grammar rule is added that is identical to one added earlier except for the
;;; transformation-list part, it replaces the one added earlier.  Thus, transformation
;;; lists can be added, changed, or removed from an existing grammar rule just by
;;; adding it again in the appropriate new form.



;;; The result of a grammar rule match is called a `constituent', even where it is not,
;;; or not yet, a constituent of a phrase.

;;; A `phrase' is a cons (expression) that is just like a slot value (see module FRAMES3)
;;; except that (a) phrase conses are used in place of slot value conses, (b) slot
;;; constants and "no value" cannot occur, (c) frames and connections do not occur,
;;; (d) phrase conses may appear multiply as long as there are no circular structures
;;; in the phrase; (e) a `sequence phrase' and `structure phrase' each has the unique
;;; value phrase-sequence-marker and phrase-structure-marker, respectively,
;;; as its cdr, and has, by convention, a special format for the phrase that
;;; is its car.

;;; A non-phrase (atomic) constituent is called a `token'.  A string token
;;; must be a text string whose use has been noted by the token reader using
;;; note-use-of-text-string-in-phrase.  A float token must be a phrase float (see
;;; module FRAMES3).

;;; Before a constituent (token or phrase) is stored into a slot, it is copied
;;; by means of copy-for-slot-value, and thereby becomes a slot value.  (This
;;; allows all phrase conses, managed arrays, phrase floats, and text strings in
;;; the compilation result, the parse result, and all intermediate parsing
;;; computations to be reclaimed, as well as for any special values or markers,
;;; e.g., phrase-sequence-marker, to be eliminated in the final result.)



;;; A `transformation template' is a (possibly nil) expression in which integers are
;;; used to refer to constituents matching rule elements.  In the instance rule case, 1
;;; refers to the constituent, and a template of 1 is implied if no transformation list
;;; is specified.  In the phrase rule case, 1 refers to the first constituent, 2 to the
;;; second, and so on, and a template of (1 2 3 ...) is implied if no transformation list
;;; is specified.

;;; A `transformation operation' specifies a function that either (a) transforms one
;;; constituent into another or (b) rejects the phrase by returning the value of
;;; special variable bad-phrase.  A one-argument function is specified by its name.  A
;;; multi-argument function is specified by a list consisting of the function's name and
;;; its arguments past the first (the first argument being the constituent to transform).

;;; Some of the currently implemented transformation operations are: simplify-associative-
;;; operation, simplify-sum, simplify-negation, (check-range-of-element <element-index>
;;; <minimum?> <maximum?>).  They are described below.

;;; When a transformation list applies in the instance rule case, there could be an
;;; ambiguity.  Such an ambiguity is resolved as follows.  A transformation list will be
;;; returned only when the first-encountered path from the constituent category to the
;;; more general category specifies a transformation list.  If more than one instance rule
;;; along this path specifies a transformation list, the one closest to the constituent
;;; category will be used; in other words, there will be no "compounding" of transformations
;;; in such a case.  For consistency, therefore, each possible path should specify
;;; the same, or no, transformation list, and compound transformations should not be
;;; expected.

;; Comment by ML. 5/9/91
;; (1) There is a bug in the parser making it difficult to predict when a transform will
;; be applied. (2) Generally, the ignoring of transforms goes far beyond problems caused
;; by ambiguity.       (Refer to use of 'convert-to-true-list in proc-gram for example.

;;; A transformation function should use phrase conses for all conses in its
;;; result, and it may also use them temporarily.  A transformation function may
;;; mutate phrase conses and/or allow them to appear multiply as components of
;;; its result provided that: (a) it does not mutate "subconstituents" (constituents
;;; combined per the transformation template to produce the constituent to transform)
;;; and (b) no circular structures are created thereby.  A transformation function
;;; need never concern itself with recycling phrase conses.

;;; When a transformation function creates a managed float, or a text string
;;; (say for "constant folding"), it should explicitly note that managed float
;;; or text string using `note-use-of-managed-float-in-phrase' or
;;; `note-use-of-text-string-in-phrase' (except in the case of a managed float
;;; created by make-phrase-float, where the managed float is automatically
;;; noted).  Then the Lisp object so created will get reclaimed, along with
;;; phrase conses and incomplete phrases, when the current edit state is
;;; reclaimed.  It is quite rare for a transformation function to need to note
;;; the creation of such managed floats and text strings.
;;;
;;; Similarly, transformation functions must use special functions to create
;;; structured objects intended to become (slot/evaluation-value) sequences and
;;; structures.  `Make-phrase-sequence' and `make-phrase-structure' create a
;;; Lisp object that will become a slot-value (or evaluation-value) sequence and
;;; structure, respectively.  Like the above "note-use-of-...", these ensure
;;; that proper allocation and reclamation of storage takes place upon the
;;; reclamation of the edit state. Unlike the above "note-use-of-..." functions,
;;; transformation functions should not create these objects in any other way.
;;; There are "note-use-of-..." functions corresponding to these two data types,
;;; but they are only to be used by the internals of copy-for-phrase and
;;; make-phrase-sequence and make-phrase-structure, not by transformation
;;; functions directly.

;; Consider having 0 as a transformation template mean what is implied when no
;; transformation list is specified.

;; -- UPDATE: Ahem: that's what nil as a transformation template does.  Consider
;; having 0 imply nil, i.e., the transformation template that is the empty list.
;; Or we should at least have some way to specify that nil is itself the
;; transformation template!  See make-empty-phrase-sequence-kludge in GRAMMAR1A
;; for an example of why this is needed.  (MHD 4/15/96)



;;; Here are some examples of grammar rules.
;;;
;;;    (term (factor '* term) (2 1 3) simplify-associative-operation)
;;;
;;;    (color 'red)

;;; Here is a trivial English sentence grammar.
;;;  
;;;  (add-grammar-rules   ; s = sentence; p = phrase; n = noun; 
;;;                       ; v = verb; p = preposition(al)
;;;    '((s (np vp))
;;;   
;;;      (np ('the n))
;;;
;;;      (n 'man)
;;;      (n 'dog)
;;;      (n 'leg)
;;;   
;;;      (vp (v np))
;;;      (vp (v np pp))
;;;   
;;;      (v 'bit)
;;;   
;;;      (pp (p np))
;;;   
;;;      (p 'in)))
  
;;; Here is a subset of a grammar for arithmetic expressions.

;;;  (add-grammar-rules
;;;
;;;    '((sum term-or-signed-term)
;;;      (sum (term-or-signed-term signed-sum) (+ 1 2) simplify-sum)
;;;   
;;;      (signed-sum signed-term)
;;;      (signed-sum (signed-term signed-sum) (+ 1 2) simplify-sum)
;;;   
;;;      (term-or-signed-term term)
;;;      (term-or-signed-term signed-term)
;;;   
;;;      (signed-term ('+ term) 2)
;;;      (signed-term ('- term) nil simplify-negation)
;;;   
;;;      (term factor)
;;;      (term (factor '* term) (2 1 3) simplify-associative-operation)
;;;   
;;;      (factor symbol)
;;;      (factor number)
;;;   
;;;      (number integer)
;;;   
;;;      (integer fixnum)
;;;      (integer bignum)))

;;; Here is an example of how to declare reserved words.
;;;
;;;    (reserve-words '(the + - * if then else)))



;;; `Syntactically-valid-rule-element-p' is true if rule-element is syntactically valid.

#+development
(def-substitution-macro syntactically-valid-rule-element-p (rule-element)
  (or (symbolp rule-element)
      (and (not (atom rule-element))
	   (eq (car rule-element) 'quote)
	   (not (atom (cdr rule-element)))
	   (null (cddr rule-element)))))

;; Consider verifying that the quoted token is a valid token.



;;; `Syntactically-valid-grammar-rule-p' is true if grammar-rule is syntactically valid.

#+development
(defun syntactically-valid-grammar-rule-p (grammar-rule)
  (and (true-non-empty-list-p grammar-rule)
       (symbolp (first grammar-rule))
       (let* ((rule-element-or-elements (second grammar-rule))
	      (instance-rule-case?
		(syntactically-valid-rule-element-p rule-element-or-elements)))
	 (and (or instance-rule-case?
		  (and (true-non-empty-list-p rule-element-or-elements)
		       (loop for x in rule-element-or-elements
			     always (syntactically-valid-rule-element-p x))))
	      (or (null (third grammar-rule))
		  (syntactically-valid-transformation-template-p
		    (third grammar-rule)
		    (if instance-rule-case? 1 (length rule-element-or-elements))))
	      (loop for x in (cdddr grammar-rule)
		    always (syntactically-valid-transformation-operation-p x))))))



;;; `Syntactically-valid-transformation-template-p' is true if transformation-template is
;;; syntactically valid.

#+development
(defun syntactically-valid-transformation-template-p
       (transformation-template number-of-constituents)
  (if (atom transformation-template)
      (or (not (fixnump transformation-template))
	  (and (>f transformation-template 0)
	       (not (>f transformation-template number-of-constituents))))
      (and (syntactically-valid-transformation-template-p
	     (car transformation-template) number-of-constituents)
	   (syntactically-valid-transformation-template-p
	     (cdr transformation-template) number-of-constituents))))



;;; `Syntactically-valid-transformation-operation-p' is true if transformation-operation
;;; is syntactically valid.

#+development
(defun syntactically-valid-transformation-operation-p (transformation-operation)
  (or (symbolp transformation-operation)
      (and (not (atom transformation-operation))
	   (symbolp (car transformation-operation))
	   (loop for l = (cdr transformation-operation) then (cdr l)
		 until (atom l)
		 finally (return (null l))))))

;; Consider checking the specifics of the transformation operation, not just its syntactic
;; form.



;;; `Transform-constituent' ... returns either constituent as transformed or, if any
;;; transformation operation returns it, the value of special variable bad-phrase.

(defvar-of-special-global bad-phrase (list 'bad-phrase))

(defun-simple transform-constituent (constituent transformation-list)
  (if (not (eql (car transformation-list) 1))	; just for speed
      (setq constituent				; changes arg
	    (transform-constituent-per-template (car transformation-list) constituent)))
  (if (cdr transformation-list)
      (perform-transformation-operations constituent (cdr transformation-list))
      constituent))


(def-concept splicing-transforms)

;;; The grammar rule transform syntax now supports a splicing options denoted by
;;; sub-expressions of the transform of the (@ nnn), where nnn is integer
;;; indexing the parsed constituents of the phrase rule.
;;;
;;; For example if a phrase-rule were being reduced in the following situation
;;;
;;; Constituent-index   Value:
;;;        1            bullwinkle
;;;        2            (favorite-colors (ochre burgundy)
;;;                      enemies (boris natasha))
;;;        3            (hat-size 19)
;;;
;;; then the following tranforms would yield:
;;;    
;;; (moose 1 2 3)  ->
;;;                   (moose bullwinkle
;;;                         (favorite-colors (ochre burgundy)
;;;                          enemies (boris natasha))
;;;                         (hat-size 19))
;;;
;;; Using the new, improved splicing-transform the following is possible:
;;;
;;; (moose name 1 (@ 2) . 3) -> (moose name bullwinkle
;;;                                    favorite-colors (ochre burgundy)
;;;                                    enemies (boris natasha))
;;;                                    hat-size 19)
;;;
;;; The more astute readers may see that this implies that it is possible to
;;; write grammar-rule transforms that generate normalized results, like plists,
;;; without having to resort to adding (krufty) splicing transfomation
;;; functions, doing extensive normalization in slot-value compilers, or other
;;; bad stuff.

(defvar current-transform-constituent-array nil)
(defvar current-transform-constituent-count nil)

(defun-simple ensure-transform-constituent-array (length)
  (setf current-transform-constituent-count length)
  (cond (current-transform-constituent-array
	 (unless (>=f (length-of-simple-vector current-transform-constituent-array)
		      length)
	  (reclaim-managed-simple-vector current-transform-constituent-array)
	  (setf current-transform-constituent-array
		(allocate-managed-simple-vector length))))
	(t
	 (setf current-transform-constituent-array
	       (allocate-managed-simple-vector 1024)))))
	       
(defun-simple transform-constituent-per-template (transformation-template constituent)
  (ensure-transform-constituent-array 1)
  (setf (svref current-transform-constituent-array 0) constituent)
  (transform-by-template transformation-template))

(defun-simple make-constituent-per-template
       (transformation-template stack-of-all-but-last-constituent last-constituent
	number-of-constituents-minus-one)
  (ensure-transform-constituent-array (1+f number-of-constituents-minus-one))
  (setf (svref current-transform-constituent-array
	       number-of-constituents-minus-one)
	last-constituent)
  (loop for constituent in stack-of-all-but-last-constituent
	as i from (1-f number-of-constituents-minus-one) downto 0
	do
    (setf (svref current-transform-constituent-array i) constituent))
  (transform-by-template transformation-template))


(defmacro template-splice-marker-p (template-exp)
  (let ((template (gensym)))
    `(let ((,template ,template-exp))
       (and (consp ,template)
	    (eq (car-of-cons ,template) '@)
	    (let ((cdr (cdr-of-cons ,template)))
	      (and (consp cdr)
		   (fixnump (car-of-cons cdr))
		   (null (cdr-of-cons cdr))))))))

(defun-substitution-macro transform-template-atom (template)
  (cond ((fixnump template)
	 (cond ((<=f template current-transform-constituent-count)
		(svref current-transform-constituent-array
		       (1-f template)))
	       (t
		nil)))
	(t
	 template)))

;;; `transform-by-template' is an atypical cons-tree recursive copier that
;;; allocates the new conses before recurring.  This effectively implements a
;;; recursion that has enough context to splice lists into the copied tree.
;;; This may seem academic and dry, but it permits the parser's
;;; transformation-templates to be more like backquote.

(defun-simple transform-by-template (template)
  (cond ((consp template)
	 (transform-by-template-rec template nil 'whole))
	(t
	 (transform-template-atom template))))

(defun-simple transform-by-template-rec (template parent-cons mode)
  (let ((transformed-thing
	  (cond
	    ((consp template)
	     (let ((head (car-of-cons template)))
	       (cond
		 ((template-splice-marker-p head)
		  (let ((copy (copy-for-phrase
				(transform-template-atom
				  (second-of-long-enough-list head)))))
		    (unless (consp copy)
		      (error "spliced transform must be a list: ~s" copy))
		    (transform-by-template-rec (cdr template) (last copy) 'cdr)
		    copy))
		 (t
		  (let ((cons (phrase-cons nil nil)))
		    (transform-by-template-rec (car template) cons 'car)
		    (transform-by-template-rec (cdr template) cons 'cdr)
		    cons)))))
	    (t
	     (transform-template-atom template)))))
    (ecase mode
      (car
       (setf (car-of-cons parent-cons) transformed-thing)
       nil)
      (cdr
       (setf (cdr-of-cons parent-cons) transformed-thing)
       nil)
      (whole
       transformed-thing))))

;;; Testing code

#+development
(defparameter test-moose-constituents
  '(bullwinkle
    (favorite-colors (ochre burgundy)
     enemies (boris natasha))
    (hat-size 19)))

#+development
(defparameter test-moose-transform-1 '(moose 1 2 3))

#+development
(defparameter test-moose-transform-2 '(moose name 1 (@ 2) . 3))

#+development 
(defun test-transform-by-template (template constituents)
  (with-phrase-conses
    (let ((reversed-constituents (reverse constituents)))
      (pprint
	(make-constituent-per-template
	  template
	  (cdr reversed-constituents)
	  (car reversed-constituents)
	  (1-f (length constituents))))
      nil)))



;;; `Perform-transformation-operations' seqentially applies each transformation operation
;;; in transformation-operations to constituent, ultimately returning either a
;;; (transformed) constituent or, if any transformation operation returns it, the value
;;; of special variable bad-phrase.

;;; If the value is bad-phrase then it sets (most-recent-reason-for-bad-parse?
;;; current-edit-state) either to the reason for the bad parse, if supplied, or nil.
;;; The reason for a bad parse is the second value returned by a transformation operation.


(defun-simple perform-transformation-operations (constituent transformation-operations)
  (loop with constituent-or-bad-phrase
	with reason-for-bad-phrase
	with transformed-constituent = constituent
	for transformation-operation in transformation-operations
	do (multiple-value-setq 
	     (constituent-or-bad-phrase reason-for-bad-phrase) 
	     (if (atom transformation-operation)
		 (funcall-symbol transformation-operation transformed-constituent)
		 (apply (car transformation-operation)
			transformed-constituent (cdr transformation-operation))))
	   (cond
	     ((eq constituent-or-bad-phrase bad-phrase)
	      (setf (problem-string-of-most-recent-reason-for-bad-parse? current-edit-state)
		    reason-for-bad-phrase)	; reason-for-bad-phrase could be nil!
	      (return bad-phrase)))
	   (setq transformed-constituent constituent-or-bad-phrase)
	finally
	  (return transformed-constituent)))

(def-global-property-name grammar-transform-can-return-bad-phrase-p)

(defun-void set-grammar-transform-can-return-bad-phrase-p (transform)
  (setf (grammar-transform-can-return-bad-phrase-p transform) t))

(defmacro declare-grammar-transform-can-return-bad-phrase (transform)
  `(set-grammar-transform-can-return-bad-phrase-p ',transform))



;;; `Simplify-associative-operation' is a transformation operation that converts
;;; an operation of the form
;;;
;;;   (op (op a1 ...) b1 ...)      [case A]
;;;
;;; or
;;; 
;;;    (op a1 (op b1 ...))         [case B]
;;;
;;; to
;;;
;;;   (op a1 ...  b1 ...)
;;;
;;; and leaves other operations unchanged.  

(defun simplify-associative-operation (associative-operation)
  (let ((operator (car associative-operation))
	(first-arg (second associative-operation))
	(second-arg (third associative-operation)))
    (cond
      ((and (not (atom first-arg))	; case A
	    (eq (car first-arg) operator))
       (phrase-cons
	 operator
	 (nconc
	   (copy-list-using-phrase-conses (cdr first-arg))
	   (cddr associative-operation))))
      ((and (not (atom second-arg))	; case B 
	    (eq (car second-arg) operator))
       (phrase-cons
	 operator
	 (phrase-cons (second associative-operation) (cdr second-arg))))
      (t
	associative-operation))))

;; Consider handling the case where the first argument has the same operator.




;;; `Simplify-last-of-nary-associative-operator' transforms
;;; (op a1 a2 ... (op b1 b2 ...)) into (op a1 a2 ... b1 b2 ...) and ...

(defun simplify-last-of-nary-associative-operator (form)
  (let ((last-arg (car (last form))))
    (if (and (not (atom last-arg))
	     (eq (car last-arg) (car form)))
	(phrase-cons
	  (car form)
	  (loop for cons on (cdr form)
		while (cdr cons)
		collecting (car cons) into result using phrase-cons
		finally
		  (return
		    (nconc
		      result
		      (loop for elt in (cdr last-arg)
			    collecting elt using phrase-cons)))))
	form)))
			    



;;; `Check-range-of-element' is a transformation operation on a list that returns either the
;;; value of special variable bad-phrase, if the list element in position element-index
;;; (counting from 1) is outside the range specified by minimum? and maximum?, or else
;;; just list itself.  When minimum? is nil, minus infinity is implied.  When maximum? is
;;; nil, plus infinity is implied.

(defun check-range-of-element (list element-index minimum? maximum?)
  (with-temporary-gensym-float-creation check-range-of-element
    (let* ((element-value
	     (phrase-number-value (nth (-f element-index 1) list))))
      (if (or (if minimum? (< element-value (phrase-number-value minimum?)))
	      (if maximum? (> element-value (phrase-number-value maximum?))))
	  bad-phrase
	  list))))

(declare-grammar-transform-can-return-bad-phrase check-range-of-element)



;;; `Check-multiple-choice-element' tests to see if the element is eql to one of
;;; a fixed list of choices.  Note: this is not guaranteed to work for comparing
;;; phrase floats.

#+unused
(defun check-multiple-choice-element (list element-index list-of-choices)
  (let ((element (nth (-f element-index 1) list)))
    (if (member element list-of-choices :test 'eql)
	list
	bad-phrase)))



;;; `Check-not-multiple-choice-element' is the negation of check-multiple-choice-element.
;;; It prohibits the element from being one of a list of choices.  Note: this is not
;;; guaranteed to work for comparing phrase floats.

#+unused
(defun check-not-multiple-choice-element (list element-index list-of-choices)
  (let ((element (nth (-f element-index 1) list)))
    (if (member element list-of-choices :test 'eql)
	bad-phrase
	list)))








;;;; Reserved Words



(def-global-property-name reserved-word-p)



;;; `Reserve-words' declares each symbol in the list symbols to be a reserved word.  A
;;; `reserved word' is a symbol that will not be interpreted as an instance of the
;;; open category "symbol" in a gensym grammar.  Such symbols as if, then, the, etc.
;;; should be declared reserved words to reduce parsing ambiguity.  (Punctuation symbols
;;; do not have to be declared as reserved words when they are automatically so treated,
;;; as they are in module EDIT.)

(defun reserve-words (symbols)
  (loop for symbol in symbols
	do (setf (reserved-word-p symbol) t)))

#+development
(defun list-all-reserved-words ()
  (let ((result nil))
    (do-symbols (symbol (find-package 'ab))
      (if (reserved-word-p symbol)
	  (setq result (cons symbol result))))
    (sort-list result 'string< nil)))

;; All Reserved Words, as of 9/13/94:

;; - a above across ago all an and any at available-frame-vector average be
;; becomes begin below between by call case change checking collection
;; color-pattern conclude connected could count current day days deviation do
;; down during else end every everything exists exit expiration false first
;; focus for format giving go has hour hours if in infer input integral
;; interpolated invoke is last maximum minimum minute minutes moved name named
;; nearest nil no none not nothing of on one or output over past per product
;; rate repeat return rules same second seconds send set should simulated
;; standard start subworkspace sum symbol that the then there this to true
;; undefined unspecified until upon value values via wait was week weeks were
;; when will with workspace yes

;; All Reserved Words, as of 4/26/91:

;;        - a above across ago all an and any at available-frame-vector
;;        average be becomes begin below between by call case change
;;        checking collection color-pattern conclude connected could count
;;        current day days deviation do down during else end every
;;        everything exists exit expiration false first focus for format
;;        giving go has hour hours if in infer input integral interpolated
;;        invoke is last maximum minimum minute minutes moved name named
;;        nearest nil no none not nothing of on one or output over past per
;;        product rate repeat return rules same second seconds send set
;;        should simulated standard start subworkspace sum symbol that the
;;        then there this to true undefined until upon value values via
;;        wait was week weeks were when will with workspace yes





;;;; Grammars





(defvar last-assigned-grammar-number 0)

(def-structure (gensym-grammar
		 (:constructor make-gensym-grammar-internal (grammar-name)))

  (grammar-number (incf last-assigned-grammar-number))

  (grammar-name nil)				; a symbol, can't be nil

  (indicator-for-category-of-this-name
    (intern (format nil "CATEGORY-IN-GRAMMAR-~D" last-assigned-grammar-number)))

  (indicator-for-category-of-symbol-token
    (intern (format nil "CATEGORY-OF-TOKEN-IN-GRAMMAR-~D" last-assigned-grammar-number)))

  (a-list-for-non-symbol-tokens	  ; ( { (non-symbol-token category) } )
    nil :reclaimer reclaim-grammar-tree)	; grammar conses; tokens cannot be conses

  (tokens-with-specific-categories
    nil :reclaimer reclaim-tokens-with-specific-categories)	; a grammar list

  (category-symbols
    nil :reclaimer reclaim-category-symbols)			; a grammar list

  (grammar-compiled? nil)

  (last-assigned-category-index -1)
  (category-visit-vector? nil)			; see documentation below
  (current-category-visit-stamp 0))		; incremented by 2, with wrap-around

(def-system-variable category-visit-vector? parse
  nil nil t)

(def-system-variable current-category-visit-stamp parse	; incremented by 2, with wrap-around
  0 nil t)

(defvar last-assigned-category-index -1)	; 1498 on 2/20/93



;;; The `category-visit-vector?' slot ...  When a category is visited while creating
;;; menus or extracting a subgrammar, the appropriate element of this vector, as
;;; determined by the category index of the category, is "stamped" to prevent
;;; repeated processing (visits) of this category.  Actually, in the
;;; menu case, the low order bit of the element is used to indicate that menu
;;; items were added during the visit.

;; The tokens-with-specific-categories and category-symbols information is only needed
;; for copying and compiling grammars.  Consider not maintaining this information when
;; it is not needed.

;; Consider using a hash table instead of an a-list for non-symbol tokens, if there get
;; to be more than a few entries.  Use (make-hash-table :size 100), if eql is the :test,
;; (gethash token (hash-table-for-non-symbol-tokens current-grammar)), and (setf
;; (gethash token (hash-table-for-non-symbol-tokens current-grammar)) category).

;; Consider recycling values for indicator-for-category-of-this-name and indicator-for-
;; category-of-symbol-token slots when a grammar is reclaimed.



;;; `Make-gensym-grammar' is to be used to create a gensym grammar.

;;; `Get-gensym-grammar' should be used to get a grammar, given a grammar
;;; or the name of one.  

(def-global-property-name gensym-grammar)

(defun make-gensym-grammar (grammar-name)
  (let ((gensym-grammar (make-gensym-grammar-internal grammar-name)))
    (setf (gensym-grammar grammar-name) gensym-grammar)
    gensym-grammar))


(defun get-gensym-grammar (grammar-or-grammar-name)
  (if (symbolp grammar-or-grammar-name)
      (gensym-grammar grammar-or-grammar-name)
      grammar-or-grammar-name))

;; The addition of a required grammar name to the structure required
;; changing the callers of make-gensym-grammar to supply the new arg.
;; (MHD 1/16/93)

;; Maybe just take a grammar name.  Maybe just advertise the property
;; name accessor.



(defvar required-token-types			; "known token types"
	'(symbol punctuation-mark
	         integer float whole-string left-string
		 middle-string right-string
		 unreserved-symbol))

;; use type-specifier-p to see which are really types.



;; If we have grammars independent of the global grammar, we need to ensure that
;; they get compiled -- right now you have to set their grammar-compile?  slot
;; true to get this rolling, which can be done by a call to set-current-grammar
;; at the start of the first G2 process.  (MHD 1/23/93)
       


;;; The grammar `global-grammar' is the name of the Gensym Global Grammar.
;;; The variable `global-grammar' is bound the grammar of this name.

(defvar-of-special-global global-grammar
  (make-gensym-grammar 'global-grammar))



(def-system-variable current-grammar parse)

(def-system-variable current-indicator-for-category-of-this-name parse)

(def-system-variable current-indicator-for-category-of-symbol-token parse)

;;; Set-current-grammar establishes gensym-grammar as the current grammar.

(defun set-current-grammar (gensym-grammar)
  (setq current-grammar gensym-grammar)
  (setq current-indicator-for-category-of-this-name
	(indicator-for-category-of-this-name gensym-grammar))
  (setq current-indicator-for-category-of-symbol-token
	(indicator-for-category-of-symbol-token gensym-grammar))
  (when (and *there-is-a-current-kb?*
	     (not (grammar-compiled? gensym-grammar)))
    (compile-grammar gensym-grammar))
  gensym-grammar)

(set-current-grammar global-grammar)



;;; With-current-grammar binds current-grammar, current-indicator-for-category-
;;; of-this-name, and current-indicator-for-category-of-symbol-token around body
;;; according to grammar-or-grammar-name, which may be a grammar structure or the
;;; name of a grammar.

(defmacro with-current-grammar ((grammar-or-grammar-name?) &body body)
  `(let* ((current-grammar ,grammar-or-grammar-name?)
	  (current-indicator-for-category-of-this-name
	    (indicator-for-category-of-this-name current-grammar))
	  (current-indicator-for-category-of-symbol-token
	    (indicator-for-category-of-symbol-token current-grammar)))
     . ,body))



;;; `Clear-global-grammar' clears the global grammar.  (This is available only in the
;;; development environment.)

#+development
(defun clear-global-grammar ()
  (if (not (eq current-grammar global-grammar))
      (error "Clear-global-grammar can only be used in a global environment."))
;  (reclaim-gensym-grammar global-grammar)   ; activate?
  (setq global-grammar (make-gensym-grammar 'global-grammar))
  (setq current-grammar global-grammar)
  (setq current-indicator-for-category-of-this-name
	(indicator-for-category-of-this-name current-grammar))
  (setq current-indicator-for-category-of-symbol-token
	(indicator-for-category-of-symbol-token current-grammar)))

;; Get rid of this eventually!



;;; `Set-up-category-visit' ...

(defconstant most-positive-fixnum-minus-2 (-f most-positive-fixnum 2))

(defun set-up-category-visit ()
  (if (not (and (category-visit-vector? current-grammar)
		(>f (length (category-visit-vector? current-grammar))
		    (last-assigned-category-index current-grammar))))
      (with-permanent-array-creation
	(setf (category-visit-vector? current-grammar)	; reclaim old one??	    
	      (make-array
		(+f (last-assigned-category-index current-grammar) 1)
		:initial-element 0))))
  (if (>f (current-category-visit-stamp		; this wrap-around could cause
	    current-grammar)			;   menus to be incomplete once
	  most-positive-fixnum-minus-2)		;   in the life of the universe
      (atomic-exchange (current-category-visit-stamp current-grammar) 0))
  (atomic-incff (current-category-visit-stamp current-grammar) 2))

;; Originally used for menus, now being borrowed for use by extract-global-subgrammar.

;; Needs further abstraction, better name maybe, etc.






;;;; Grammar Categories



;;; A `category' is a grammar structure that represents either a specific token or a
;;; category symbol.  In fact, there are two types of category, category-for-token and
;;; category-for-category-symbol, with the latter including all the slots of the former
;;; plus some additional slots.  A specific token t can always have its own category, but
;;; it requires one only if 't appears as a phrase rule element or if there is more than
;;; one distinct grammar rule of the form (c 't).

;; Categories for specific tokens could be eliminated in favor of the tokens themselves.
;; This would save about 32 bytes for each such category (231 as of 2/10/88), but would
;; make the parser a bit more complicated.  If this is NOT done, consider speeding up
;; the predicates category-is-for-token-p and category-is-for-category-symbol-p a bit,
;; which would speed up parsing and menu generation a bit.  (Add-constituent-to-incomplete-
;; phrases uses subcategoryp, which in turn uses category-is-for-category-symbol-p.)



(def-structure (category-for-token
		 (:constructor
		   make-category-for-token-structure (category-token))
		 (:predicate category-is-for-token-p)
		 #+development
		 (:print-function print-category-for-token))

  category-index				; used in menu making

  (more-general-categories nil :reclaimer reclaim-grammar-list)	; a grammar list

  (transformation-lists-for-more-general-categories  		; a grammar list
    nil :reclaimer reclaim-grammar-list)

  (phrase-rule-completions-for-each-category-this-may-begin	; a grammar list
    nil :reclaimer reclaim-phrase-rule-completions)

  (agenda-of-more-general-categories-to-search
    nil :reclaimer reclaim-agenda-of-more-general-categories)

  (cached-strict-subcategory-info
    nil :reclaimer reclaim-cached-strict-subcategory-info)

  category-token)


#+development
(defun print-category-for-token (category-for-token stream depth)
  (declare (ignore depth))			; unused
  (printing-random-object (category-for-token stream)
    (format stream "'~A" (category-token category-for-token))))

;; Each element of phrase-rule-completions-for-each-category-this-may-begin is a list
;; of phrase rule completions having the same category-for-completed-phrase.





(def-structure (category-for-category-symbol
;		 (:include category-for-token)
		 (:constructor
		   make-category-for-category-symbol (category-symbol))
		 (:predicate category-is-for-category-symbol-p)
		 #+development
		 (:print-function print-category-for-category-symbol))

  category-index-dummy				; used in menu making

  (more-general-categories-dummy nil :reclaimer reclaim-grammar-list)	; a grammar list

  (transformation-lists-for-more-general-categories-dummy	        ; a grammar list
    nil :reclaimer reclaim-grammar-list)

  (phrase-rule-completions-for-each-category-this-may-begin-dummy	; a grammar list
    nil :reclaimer reclaim-phrase-rule-completions)
  
  (agenda-of-more-general-categories-to-search-dummy	; (MHD 6/3/91)
    nil :reclaimer reclaim-agenda-of-more-general-categories)

  (cached-strict-subcategory-info-dummy
    nil :reclaimer reclaim-cached-strict-subcategory-info)
  
  ;; The slots above are dummies to hack an include of category-for-token
  ;; that won't complain about double definition.  Since they are in the same
  ;; positions in the structures the accessors for one will work on the other.
  ;; (Yes, I know, I know, it's very dirty.)  -jra 11/24/87

  category-symbol

  (more-specific-categories nil :reclaimer reclaim-grammar-list) ; a grammar list

  (token-instances-without-specific-categories         	; a grammar list
    nil :reclaimer reclaim-grammar-list)

  (categories-that-can-begin-a-phrase-of-this-category	; a grammar list
    nil :reclaimer reclaim-grammar-list)

  (categories-this-can-be-or-begin		; Filled in by compilation; does not
    'NOT-A-RESULT-CATEGORY)			;   include the category itself;
						;   made up of grammar conses at
						;   present
						; If this is other than the default,
						; this is to be computed by compile-
						; grammar.  Add-grammar-rule-1 is the
						; one place that sets this to nil,
						; to indicate that this is a phrase-rule
						; result category. [As of 3/31/93]

;  #+development
;  index-for-category-symbol

  (bit-vector-for-categories-this-can-be-or-begin? nil)	; set by compile-grammar

  #+development
  (non-token-categories-that-can-be-or-begin-this	; non-pool, sharable conses now
    'unknown)

  )

#+development
(defun print-category-for-category-symbol
    (category-for-category-symbol stream depth)
  (declare (ignore depth))			; unused
  (printing-random-object (category-for-category-symbol stream)
    (format stream "~(~A~)" (category-symbol category-for-category-symbol))))




;;; `Get-category-for-category-symbol-if-any' returns the grammar category named by
;;; category-symbol, if there is one, or else nil.

(defmacro get-category-for-category-symbol-if-any (category-symbol)
  `(get ,category-symbol current-indicator-for-category-of-this-name))



(defun get-or-make-category-for-category-symbol (category-symbol)
  #+development
  (if (eq category-symbol 'nil)			; Catch the problem of NIL being
      (cerror					;   made a category next time it
	"Go ahead."				;   happens! (MHD 2/20/90)
	"NIL being defined as a grammar category!  ~
     This breaks things. (See me. -mhd)"))
  (or (get-category-for-category-symbol-if-any category-symbol)
      (let ((new-category (make-category-for-category-symbol category-symbol)))

	#+development (register-definition category-symbol 'grammar-category-symbol)
	
	(setf (category-index new-category)
	      (atomic-incff (last-assigned-category-index current-grammar)))
;	#+development
;	(setf (index-for-category-symbol new-category)
;	      (atomic-incff last-assigned-index-for-category-symbol))
	#-SymScale
	(setf (category-symbols current-grammar)
	      (grammar-cons category-symbol (category-symbols current-grammar)))
	#+SymScale
	(grammar-push-atomic category-symbol
			     (category-symbols current-grammar))
	(with-permanent-allocation
	  (setf (get category-symbol current-indicator-for-category-of-this-name)
		new-category)))))



;;; `get-category-of-token' - when the token-value is not a symbol,
;;; we look in the grammar's special association list to see if there's
;;; a defined value.  However, the keys for this a list are (currently)
;;; a mix of wide-strings and fixnums (and could presumably be other
;;; types at some point.)  We do not have a predicate which will safely
;;; compare wide-strings and fixnums without consing.  Therefore,
;;; there is no good :test argument we could give to assoc to have it
;;; safely work.  So if the token-value is a string, do an ad-hoc
;;; assoc and avoid comparing wide-strings with anything but another
;;; wide string.  (Note: this previously worked by testing using eql,
;;; which is not appropriate for comparing two wide-strings when one
;;; is a key; however, it worked in the old tokenizer.  In the new
;;; tokenizer, a string will be consed up each time the token is
;;; recognized, so it will never be eql to the value in the alist).
;;; - jv 11/1/96

(defun get-category-of-token (token-value)
  (cond
    ((symbolp token-value)
     (get token-value current-indicator-for-category-of-symbol-token))
    ((wide-string-p token-value)
     (loop for (key value) in (a-list-for-non-symbol-tokens current-grammar)
	   when (and (wide-string-p key)
		     (string=w token-value key))
	     return value
	   finally
	     (return nil)))
    (t   ;; presumably a fixnum
     (second
       (assoc token-value (a-list-for-non-symbol-tokens current-grammar))))))
	      
	       



;;; `Set-category-of-token' ... returns category.

(defun set-category-of-token (token category)
  (cond ((symbolp token)
	 (as-atomic-operation		; is this fast enough? (not thread-safe)
	   (setf (symbol-plist token)
		 (grammar-cons current-indicator-for-category-of-symbol-token
			       (grammar-cons category (symbol-plist token))))))
	(t
	 #-SymScale
	 (setf (a-list-for-non-symbol-tokens current-grammar)
	       (grammar-cons
		 (grammar-list token category)
		 (a-list-for-non-symbol-tokens current-grammar)))
	 #+SymScale
	 (grammar-push-atomic (grammar-list token category)
			      (a-list-for-non-symbol-tokens current-grammar))))
  category)



(defun make-category-for-token (token existing-category-of-token?)
  #-SymScale
  (setf (tokens-with-specific-categories current-grammar)
	(grammar-cons token (tokens-with-specific-categories current-grammar)))
  #+SymScale
  (grammar-push-atomic token
		       (tokens-with-specific-categories current-grammar))

  #+development (register-definition token 'grammar-category)

  (let ((category-specifically-for-token
	  (make-category-for-token-structure token)))
    (setf (category-index category-specifically-for-token)
	  (atomic-incff (last-assigned-category-index current-grammar)))
    (cond
      (existing-category-of-token?
       (let ((token-instances-without-specific-categories
	       (token-instances-without-specific-categories
		 existing-category-of-token?)))
	 (setf (more-general-categories category-specifically-for-token)
	       (grammar-list existing-category-of-token?))
	 (setf (token-instances-without-specific-categories existing-category-of-token?)
	       (delete-grammar-element
		 (car (member token token-instances-without-specific-categories))  ; eql
		 token-instances-without-specific-categories))
	 ;; enqueue
	 (setf (more-specific-categories existing-category-of-token?)
	       (nconc (more-specific-categories existing-category-of-token?)
		      (grammar-list category-specifically-for-token))))))
    (set-category-of-token token category-specifically-for-token)))



(defun get-or-make-category-for-rule-element (rule-element)
  (if (symbolp rule-element)
      (get-or-make-category-for-category-symbol rule-element)
      (let ((category-of-token? (get-category-of-token (second rule-element))))
	(if (and category-of-token?
		(category-is-for-token-p category-of-token?))
	    category-of-token?
	    (make-category-for-token (second rule-element) category-of-token?)))))


(def-structure (category-set
		 (:constructor make-category-set (category-set-list-1 category-vector)))
  category-set-list-1
  category-vector)

(defun-void add-category-to-bit-set (category category-list)
  (let ((size (1+f (last-assigned-category-index current-grammar)))
	(vector (category-vector category-list)))	
    (unless (and (vectorp vector)
		 (<=f size (length vector)))
      (let ((new-vector (allocate-byte-vector-16 (ceilingf size 16))))
	(when vector
	  (loop for i from 0 below (length vector)
		do (setf (byte-vector-16-aref new-vector i)
			 (byte-vector-16-aref vector i))))
	(loop for i from (if vector
			     (length vector)
			     0)
		    below (length new-vector)
	      do (setf (byte-vector-16-aref new-vector i) 0))
	(when vector
	  (reclaim-byte-vector-16 vector))
	(setq vector new-vector)
	(setf (category-vector category-list) vector)))
    (let* ((index (category-index category))
	   (vector-index (right-shiftf index 4)))
      (setf (byte-vector-16-aref vector vector-index)
	    (logior (byte-vector-16-aref vector vector-index)
		    (left-shiftf 1 (logandf index #xf)))))))

(defun-simple indices-of-bits-in-category-vector (vector)
  (loop for vector-index from 0 below (length vector)
	for bits = (byte-vector-16-aref vector vector-index)
	nconc (loop for j from 0 to #xf
		    when (=f 1 (logandf 1 (right-shiftf bits j)))
		      collect (+f (*f vector-index 16) j)
			using gensym-cons)))

(defun-simple print-indices-of-bits-in-category-vector (vector stream)
  (let ((indices (indices-of-bits-in-category-vector vector)))
    (format stream "{~{~D~^,~}}" indices)
    (reclaim-gensym-list indices)))

#+development
(defvar list-of-all-category-sets nil)

(defun-simple convert-to-category-set (category-list)
  (let ((set (make-category-set category-list nil)))
    #+development
    (push set list-of-all-category-sets)
    (loop for category in category-list
	  do (add-category-to-bit-set category set))
    set))

(defun-simple category-set-memq (category category-list)
  (if (listp category-list)
      (memq-macro category category-list)
      (let* ((index (category-index category))
	     (vector (category-vector category-list))
	     (vector-index (right-shiftf index 4))
	     (bits (if (<f vector-index (byte-vector-16-length vector))
		       (byte-vector-16-aref vector vector-index)
		       0)))
	(=f 1 (logandf 1 (right-shiftf bits (logandf index #xf)))))))



(defun-simple category-set-push-1 (category category-list)
  (cond ((and (listp category-list)
	      (<=f (length category-list) maximum-size-of-category-set-as-list))
	 (grammar-cons category category-list))
	(t
	 (when (listp category-list)
	   (setq category-list (convert-to-category-set category-list)))
	 (add-category-to-bit-set category category-list)
	 (grammar-push category (category-set-list-1 category-list))
	 category-list))) ; should save space, and eliminate this

(defmacro category-set-push (category category-list)
  `(setf ,category-list
	 (category-set-push-1 ,category ,category-list)))

(def-substitution-macro category-set-list (category-list)
  (if (listp category-list)
       category-list
       (category-set-list-1 category-list)))  

(defmacro category-set-empty ()
  nil)

;;; `Subcategoryp' determines whethers or not category-1 is a `subcategory' of category-2,
;;; where a category is considered a subcategory of itself.  A true value will be either
;;; the symbol T or a transformation list.  A transformation list will be returned when
;;; the first-encountered path of increasing generality from category-1 to category-2
;;; specifies a transformation list; if more than one instance rule along this path
;;; specifies a transformation list, the one closest to category-1 will be used.  (Note
;;; that T could be returned even when there exists some path that specifies a
;;; transformation list.  For consistency, therefore, each possible path should specify
;;; the same, or no, transformation list.)


(defvar current-subcategory-path (make-array max-instance-rule-chaining))
(defvar currently-tracking-subcategory-path-max 0)

(defun strict-subcategoryp-1 (category-1 category-2)
  (loop for more-general-category in (more-general-categories category-1)
	as corresponding-transformation-lists
	   = (transformation-lists-for-more-general-categories category-1)
	   then (cdr corresponding-transformation-lists)
	thereis (if (eq more-general-category category-2)
		    (or (car corresponding-transformation-lists) t)
		    (let ((transformation-list-or-t?
			    (strict-subcategoryp-1 more-general-category category-2)))
		      (if transformation-list-or-t?
			  (or (car corresponding-transformation-lists)
			      transformation-list-or-t?))))))

(defun strict-subcategory-path-1 (category-1 category-2)
  (loop for more-general-category in (more-general-categories category-1)
	thereis (let* ((found-it (eq more-general-category category-2))
		       (path (unless found-it
			       (strict-subcategory-path-1 more-general-category category-2))))
		  (when (or found-it path)
		    (grammar-cons category-1 path)))))

(def-structure (strict-subcategory-info
		 (:constructor make-strict-subcategory-info
			       (strict-subcategory-info-category
				 strict-subcategory-info-subcategoryp
				 strict-subcategory-info-path)))
  (strict-subcategory-info-category nil)
  (strict-subcategory-info-subcategoryp nil)
  (strict-subcategory-info-path nil :reclaimer reclaim-grammar-list))

(defun reclaim-cached-strict-subcategory-info (cons)
  (when cons
    (reclaim-grammar-list (car cons))
    (loop for info in (cdr cons)
	  do (reclaim-strict-subcategory-info info))
    (reclaim-grammar-list (cdr cons))
    (reclaim-grammar-cons cons)))

(defvar strict-subcategory-infos-exist-p nil)
(defvar strict-subcategory-info-last-category-1 nil)
(defvar strict-subcategory-info-last-category-2 nil)
(defvar strict-subcategory-info-last-result nil)

;;; For-each-grammar-as-current-grammar ... only to be used by add-grammar-
;;; rule and add-grammar-rules.

(defvar names-of-grammars-to-add-rules-to '(global-grammar))

(defmacro for-each-grammar-as-current-grammar (&body body)
  `(loop for grammar-name in names-of-grammars-to-add-rules-to
	 do (let* ((current-grammar (get-gensym-grammar grammar-name))
		   (current-indicator-for-category-of-symbol-token
		     (indicator-for-category-of-symbol-token current-grammar))
		   (current-indicator-for-category-of-this-name
		     (indicator-for-category-of-this-name current-grammar)))
	      . ,body)))

(defmacro for-each-category (category &body body)
  (let ((category-symbol (make-symbol "CATEGORY-SYMBOL"))
	(token (make-symbol "TOKEN")))
    `(for-each-grammar-as-current-grammar
       (loop for ,category-symbol in (category-symbols current-grammar)
	     for ,category = (make-category-for-category-symbol ,category-symbol)
	     do (progn ,@ body))
       (loop for ,token in (tokens-with-specific-categories current-grammar)
	     for ,category = (get-category-of-token ,token)
	     do (progn ,@ body)))))

(defun decache-all-strict-subcategory-infos ()
  (when strict-subcategory-infos-exist-p
    (setq strict-subcategory-infos-exist-p nil)
    (setq strict-subcategory-info-last-category-1 nil)
    (setq strict-subcategory-info-last-category-2 nil)
    (setq strict-subcategory-info-last-result nil)
    (for-each-category category
      (reclaim-cached-strict-subcategory-info
	(cached-strict-subcategory-info category))
      (setf (cached-strict-subcategory-info category) nil))))

(defun strict-subcategory-info-1 (category-1 category-2)
  (let ((category-info (or (cached-strict-subcategory-info category-1)
			   (setf (cached-strict-subcategory-info category-1)
				 (grammar-cons (category-set-empty) nil)))))
    (cond
      ((category-set-memq category-2 (car category-info))
       nil)
      ((loop for info in (cdr category-info)
	     when (eq category-2 (strict-subcategory-info-category info))
	       return info))
      (t
       (let ((strict-subcategoryp (strict-subcategoryp-1 category-1 category-2)))
	 ;; there are about 11 times as many nils as non-nils
	 (cond ((null strict-subcategoryp)
		(category-set-push category-2 (car category-info))
		nil)
	       (t
		(let* ((path (strict-subcategory-path-1 category-1 category-2))
		       (info (make-strict-subcategory-info category-2 strict-subcategoryp path)))
		  (grammar-push info (cdr category-info))
		  info))))))))

(defun strict-subcategory-info (category-1 category-2)
  (if (and (eq category-1 strict-subcategory-info-last-category-1)
	   (eq category-2 strict-subcategory-info-last-category-2))
      strict-subcategory-info-last-result
      (let ((result (strict-subcategory-info-1 category-1 category-2)))
	(setq strict-subcategory-info-last-category-1 category-1)
	(setq strict-subcategory-info-last-category-2 category-2)
	(setq strict-subcategory-info-last-result result))))

(defun subcategoryp (category-1 category-2)
  (cond
    ((eq category-1 category-2) t)
    ((category-is-for-category-symbol-p category-2)
     (strict-subcategoryp category-1 category-2))))

(defun strict-subcategoryp (category-1 category-2)
  (let ((info? (strict-subcategory-info category-1 category-2)))
    (when info?
      (strict-subcategory-info-subcategoryp info?))))

(defun strict-subcategory-path (category-1 category-2)
  (let ((info? (strict-subcategory-info category-1 category-2)))
    (when info?
      (strict-subcategory-info-path info?))))

(defun set-current-subcategory-path (category-1 category-2)
  (let ((path (unless (eq category-1 category-2)
		(strict-subcategory-path category-1 category-2))))
    (setq currently-tracking-subcategory-path-max (length path))
    (loop for index from 1
	  for category in path
	  do (setf (svref current-subcategory-path index) category))
    path))

;; Note (JED 12/21/95)
;; I apologize for the complexity added to strict-subcategory-p. It was
;; done in service of making add-grammar-rules-without-losing-transforms
;; work.

;; Consider having the top one or two recursions expand in-line.

;; Strict-subcategoryp is referred to only in subcategoryp (and within itself).



(defun reclaim-tokens-with-specific-categories (tokens-with-specific-categories)
  (with-current-grammar (structure-being-reclaimed)
    (loop as token in tokens-with-specific-categories
	  do (reclaim-category-for-token (get-category-of-token token))))
  (reclaim-grammar-list tokens-with-specific-categories))

(defun reclaim-category-symbols (category-symbols)
  (loop as category-symbol in category-symbols
	do (reclaim-category-for-category-symbol
	     (get-category-for-category-symbol-if-any category-symbol))
	   (setf (get category-symbol current-indicator-for-category-of-this-name)
		 nil))				; reclaim the conses!!
  (reclaim-grammar-list category-symbols))

;; These must be defined here, because of their use of certain macros.

;; Note that, until and unless copy-global-grammar is revived, grammars are not reclaimed,
;; except possibly by the development function, clear-global-grammar.

;; Reclaim the properties mapping from symbols to categories!






;;;; KB-Specific Symbol Tokens


(defun reclaim-grammar-list-function (list)
  (reclaim-grammar-list-macro list))

(def-kb-specific-property-name category-symbols-for-symbol-token
    reclaim-grammar-list-function)

(def-kb-specific-property-name symbol-tokens-for-category-symbol
    reclaim-grammar-list-function)

;; May not be thread-safe but no easy solution. --binghe
(defun add-kb-specific-symbol-token (symbol category-symbol)
  (setf (category-symbols-for-symbol-token symbol)
	(grammar-cons category-symbol (category-symbols-for-symbol-token symbol)))
  (setf (symbol-tokens-for-category-symbol category-symbol)
	(grammar-cons symbol (symbol-tokens-for-category-symbol category-symbol))))







;;;; Phrase Rule Completions





(def-structure (phrase-rule-completion
		 (:constructor
		   make-phrase-rule-completion
		   (category-for-completed-phrase category-of-next-constituent
	       	    phrase-rule-completions-past-next-constituent))	; (:type list) ??
		 (:creations-at-a-time 100)
		 #+development
		 (:print-function print-phrase-rule-completion))

  category-of-next-constituent

  category-for-completed-phrase

  (transformation-list-or-t? nil)  ; nil or t or
				   ;   (transformation-template {transformation-operation})

  (phrase-rule-completions-past-next-constituent	; a grammar list
    nil :reclaimer reclaim-phrase-rule-completions)	; nil should not be nec!

  )


#+development
(defun print-phrase-rule-completion 
    (phrase-rule-completion stream depth)
  (declare (ignore depth))			; unused
  (printing-random-object (phrase-rule-completion stream)
    (format
      stream "Completion of ~A in ~A"
      (category-of-next-constituent phrase-rule-completion)
      (category-for-completed-phrase phrase-rule-completion))))

;; Consider having the #< and > removed from around the two elements that
;; get printed above.


;; Consider defining a phrase-rule substructure to hold transformation-list-or-t? and
;; phrase-rule-elements.



(defun reclaim-phrase-rule-completions (phrase-rule-completions)
  (loop for phrase-rule-completion in phrase-rule-completions
	do (reclaim-phrase-rule-completion phrase-rule-completion))
  (reclaim-grammar-list phrase-rule-completions))








;;;; Adding Rules to a Grammar



;;; `For-grammars' may be used around a series of forms that add grammar rules
;;; to one or more grammars.

;;; For now, by default, global-grammar is implies by default as one of the
;;; grammar.  For now, all grammars should be written to be compatible in
;;; a single global grammar.  Ultimately, that restriction will go away,
;;; probably.

(defmacro for-grammars ((&rest grammar-names) &body body)
  `(let ((names-of-grammars-to-add-rules-to
	   ',grammar-names
;	   '(global-grammar . ,grammar-names)
	   ))
     (progn . ,body)))

;; LH thinks there's no reason to contemplate keeping a local grammar.
;; So, you don't end up having a global grammar, but a set of grammars.

;; So, keeping a global grammar will ultimately be for checking, but
;; only for now.  Ultimately, it is not going to be necessary to keep
;; single namespace.

;; Consider a variant that just takes grammar rules directly, and doesn't
;; require the add-grammar-rule calls.






;;; `Add-grammar-rules' adds each rule in the list grammar-rules to the current grammar.
;;; See add-grammar-rule below.

;; jh, 5/8/91.  Added batch-parsing-engaged-p to add-grammar-rule to test
;; experimental parser.  If batch-parsing-engaged-p is nil (its default), G2
;; behavior will be unchanged.

(defparameter batch-parsing-engaged-p nil)

(defmacro add-grammar-rules (grammar-rules)
  `(add-grammar-rules-function
     ,(if (and (consp grammar-rules)
	       (eq (car grammar-rules) 'quote))
	  `(optimize-constant ,grammar-rules)
	  grammar-rules)))

;; Note that add-grammar-rules was changed from a function to a macro today in
;; order to switch in an optimization to the way large, constant cons trees are
;; created.  This was done to help in porting to the new release of Chestnut.
;; See optimize-constant for details.  -jra

(defun add-grammar-rules-function (grammar-rules)
  (when batch-parsing-engaged-p
    (loop for grammar-rule in grammar-rules
	  do (add-batch-grammar-rule grammar-rule)))
  (for-each-grammar-as-current-grammar
    (loop for grammar-rule in grammar-rules
	  do (add-grammar-rule-1 grammar-rule))
    (if (grammar-compiled? current-grammar)
	(compile-grammar current-grammar))))	; takes time	; takes time

;;; `Add-grammar-rule' adds grammar-rule to the current grammar.  This is non-trivial since
;;; a gensym grammar is a rather complex structure.  In a development system,
;;; grammar-rule is syntactically checked before being incorporated into the grammar.

(defun add-grammar-rule (grammar-rule)
  (when batch-parsing-engaged-p
    (add-batch-grammar-rule grammar-rule))
  (for-each-grammar-as-current-grammar
    (add-grammar-rule-1 grammar-rule)
    (if (grammar-compiled? current-grammar)
	(compile-grammar current-grammar))))	; takes time


;;; The macro `def-grammar-category' exists so that grammar categories are
;;; meta-dottable in emacs.  It adds grammar rules all of whose left hand sides
;;; are the same. -fmw

(defmacro def-grammar-category (category-name (&key transformation) &body right-hand-sides)
  (let ((rules
	  (loop for rhs in right-hand-sides
		for rule = `(,category-name
			       ,@(cond ((atom rhs)
					(list `',rhs))
				       ((null transformation)
					rhs)
				       ((= (length rhs) 1)
					`(,(first rhs) 1 ,transformation))
				       ((= (length rhs) 2)
					`(,(first rhs) ,(second rhs) ,transformation))
				       (t
					rhs)))
		collect rule)))
    `(progn
       (add-grammar-rules ',rules)
       ',category-name)))

;; This could do other nice syntactic transformations, like <category-name> ->
;; index.


;;; The macro `def-grammar-list-category' exists so that grammar list
;;; categories are meta-dottable in emacs. -fmw

(defmacro def-grammar-list-category
    (list-category (element-category)
		   &key separator conjunction empty-list-symbol)
  ;; Quoting arguments to this function did extremely bad things without
  ;; warnings, so I've at least added the warnings. (MHD 11/17/04)
  (labels ((quote-check (arg arg-name)
	     (if (and (consp arg) (eq (car arg) 'quote))
		 (warn "The ~a arg to def-grammar-list-category, ~
                      ~%~a, is quoted, but it probably should not be!"
		       arg-name arg))))
    (quote-check list-category 'list-category)
    (quote-check element-category 'element-category)
    (quote-check separator 'separator)
    (quote-check conjunction 'conjunction)
    (quote-check empty-list-symbol 'empty-list-symbol)) 
  `(progn
     (add-grammar-rules-for-list ',list-category
				 ',element-category
				 ',separator
				 ',conjunction
				 ',empty-list-symbol)
     ',list-category))


			       
;;; The function `phrase-flatten-tree' returns a new list of phrase conses,
;;; consisting of a flat list of the atoms in the given s-expression.

(defun phrase-flatten-tree (tree)
  (cond ((null tree) nil)
	((atom tree) (phrase-list tree))
	(t (nconc (phrase-flatten-tree (car-of-cons tree))
		  (phrase-flatten-tree (cdr-of-cons tree))))))


(defun-for-macro phrase-append-list-elements (list)
  (nconc (first list) (second list)))



;;; The macro `def-simple-grammar-list-category' defines a category as a simple
;;; comma-separated list of element-category, or NONE.  The result of the parse
;;; is the list, without any annoying separator symbols.

#+unused
(defmacro def-simple-grammar-list-category (name (element-category) &key
						 (separator '\,)
						 (empty-list-symbol 'none))
  (let ((rules `((,name ,element-category (1 1 1 1))
		 (,name (,name ',separator ,element-category) (1 3) phrase-append-list-elements)
		 ,@(when empty-list-symbol
		     `((,name ',empty-list-symbol nil nil-function))))))
    `(progn (add-grammar-rules (optimize-constant ',rules))
	    ',name)))

  




;; Note that it is rare in practice to add grammar rules inside of a G2 process
;; at present, or even when there is a current KB anywhere.  It is done
;; currently for G2 when units of measures are declared.  There is pretty much
;; no provision for removing grammar rules.  This could one day change;
;; specifically, we could open up grammar creation to users, e.g., for
;; customized grammars, or for localization.  (MHD 3/17/93)



;;; The function `add-batch-grammar-rule' is a stub for the grammar rule
;;; registration function of JH's compiled parser.  -jra 5/10/91

(defun add-batch-grammar-rule (rule)
  (declare (ignore rule))
  nil)


(defun instance-rule-p (grammar-rule)
  (or (atom (second grammar-rule))
      (eq (car (second grammar-rule)) 'quote)))



(defun add-grammar-rule-1 (grammar-rule)
  (process-grammar-rule-for-development-if-appropriate grammar-rule)
  (let ((category
	  (get-or-make-category-for-category-symbol (first grammar-rule)))
	(instance-or-phrase-rule-elements (second grammar-rule))
	(transformation-list (cddr grammar-rule)))
    #+ddm (make-and-cross-index-grammar-rule grammar-rule)
    (cond
      ((instance-rule-p grammar-rule)
       (add-grammar-instance-rule
	 category instance-or-phrase-rule-elements transformation-list))
      (t
       (add-grammar-phrase-rule
	 category instance-or-phrase-rule-elements transformation-list)))))

(defun add-grammar-instance-rule (category instance-rule-element transformation-list)
  (let ((category-for-instance?
	  (if (symbolp instance-rule-element)	; "instance-is-a-category-p"
	      (get-or-make-category-for-category-symbol instance-rule-element)
	      (let* ((token (second instance-rule-element))
		     (category-of-token? (get-category-of-token token)))
		(cond
		  ((and (null category-of-token?) (null transformation-list))
		   (set-category-of-token token category)
		   (setf (token-instances-without-specific-categories category)
			 (nconc
			   (token-instances-without-specific-categories category)
			   (grammar-list token)))
		   nil)
		  ((and category-of-token?
			(category-is-for-token-p category-of-token?))
		   category-of-token?)
		  ((or (and category-of-token?
			    (not (eq (category-symbol category-of-token?) category)))
		       transformation-list)
		   (make-category-for-token
		     (second instance-rule-element) category-of-token?)))))))
    (when category-for-instance?

      ;; Set up pointers for the category:
      (grammar-conc-new
	(more-specific-categories category)
	category-for-instance?)

      ;; NOTE: this was not being done until now, which caused certain
      ;; valid grammars to not work!   (MHD 6/10/96)
      (grammar-conc-new
	(categories-that-can-begin-a-phrase-of-this-category category)
	category-for-instance?)

      ;; Set up pointers for the instance category:
      (grammar-conc-new
	(more-general-categories category-for-instance?)
	category)
      ;; Note the invariant that the length of more-general-categories-list is
      ;; always greater than or equal to the length of the list of
      ;; transformation lists for more general categories, both before and
      ;; after the following operation.
      (setf (transformation-lists-for-more-general-categories category-for-instance?)
	    (set-nth-element-of-variable-length-grammar-list
	      (transformation-lists-for-more-general-categories category-for-instance?)
	      (position
		category (more-general-categories category-for-instance?))
	      transformation-list)))))


(defun add-grammar-phrase-rule
    (phrase-category phrase-rule-elements transformation-list)
  (loop with category-for-first-rule-element
	  = (get-or-make-category-for-rule-element (pop phrase-rule-elements))
	with phrase-rule-completions-for-each-category-this-may-begin
	  = (phrase-rule-completions-for-each-category-this-may-begin
	      category-for-first-rule-element)
	initially
	  (grammar-conc-new
	    (categories-that-can-begin-a-phrase-of-this-category phrase-category)
	    category-for-first-rule-element)
	as category-for-rule-element
	   = (get-or-make-category-for-rule-element (pop phrase-rule-elements))
	as second-rule-element? = t then nil
	as existing-phrase-rule-completions
	   = (if second-rule-element?
		 (loop for phrase-rule-completions
			   in phrase-rule-completions-for-each-category-this-may-begin
		       when (eq (category-for-completed-phrase
				  (car phrase-rule-completions))
				phrase-category)
			 return phrase-rule-completions)
		 (phrase-rule-completions-past-next-constituent phrase-rule-completion))
	as phrase-rule-completion
	   = (let ((phrase-rule-completion-1
		     (loop for existing-phrase-rule-completion
			       in existing-phrase-rule-completions
			   when (eq (category-of-next-constituent existing-phrase-rule-completion)
				    category-for-rule-element)
			     return existing-phrase-rule-completion)))
	       (if phrase-rule-completion-1
		   phrase-rule-completion-1
		   (let ((listed-new-phrase-rule-completion
			   (grammar-list
			     (make-phrase-rule-completion
			       phrase-category category-for-rule-element nil))))
		     ;; Mark category as being a phrase-rule result
		     ;; category, if necessary, and therefore in need of
		     ;; having its categories-this-can-be-or-begin filled
		     ;; in.  Compile-grammar looks at this, and fills it in
		     ;; when it is has a value other than its default value.
		     ;; (MHD 3/31/93)
		     (when (eq (categories-this-can-be-or-begin phrase-category)
			       'not-a-result-category)
		       (setf (categories-this-can-be-or-begin phrase-category)
			     (category-set-empty)))
		     (cond
		       (existing-phrase-rule-completions
			(nconc existing-phrase-rule-completions
			       listed-new-phrase-rule-completion))
		       (second-rule-element?
			(setf (phrase-rule-completions-for-each-category-this-may-begin
				category-for-first-rule-element)
			      (nconc
				phrase-rule-completions-for-each-category-this-may-begin
				(grammar-list listed-new-phrase-rule-completion))))
		       (t (setf (phrase-rule-completions-past-next-constituent
				  phrase-rule-completion)
				listed-new-phrase-rule-completion)))
		     (car listed-new-phrase-rule-completion))))
	while phrase-rule-elements
	finally
	  (setf (transformation-list-or-t? phrase-rule-completion)
		(or transformation-list t))
	  (return phrase-rule-completion)))


;; Transformation-list-or-t? should be copied by add-grammar-rule and
;; copy-global-grammar, so that reclaiming can be perfect!

;; Detect and warn on a "left recursion", especially where there is a cycle in
;; the more-general relation!

;; Consider giving a warning if there already exists a phrase rule with
;; different transformation lists.




;;; Process-grammar-rule-for-development-if-appropriate is called at the beginning
;;; of add-grammar-rule-1 to perform miscellaneous development-time only tasks.
;;; These include checking for syntactic validity of the grammar rule and, if
;;; called for, building an inverse grammar list and/or a complete list of all
;;; the rules of the grammar

;; The following global property and the code at the beginning of
;; add-grammar-rule-1 are for the use of make-inverse-grammar, a development
;; research facility. It is non-invasive to the parser.  ML 1/17/89

(defun process-grammar-rule-for-development-if-appropriate (grammar-rule)
  grammar-rule				; ignored in non-development
  #+development
  (if (not (syntactically-valid-grammar-rule-p grammar-rule))
      (warn "~A is not a syntactically valid grammar rule" grammar-rule))
  )





;;;; Incomplete Phrases



;;; `Incomplete phrases' are temporary structures that are certain to be garbage (and
;;; therefore can be entirely recycled) after parsing is finished.



(def-structure (incomplete-phrase
		 (:constructor
		   make-incomplete-phrase-structure
		   (phrase-rule-completions incomplete-stack-of-constituents
		    incomplete-phrases-as-of-the-beginning-of-this
		    incomplete-phrase-link?
		    #+development last-token-position))
		 #+development
		 (:print-function print-incomplete-phrase))

  phrase-rule-completions

  incomplete-stack-of-constituents		; a phrase list of phrase trees

  incomplete-phrases-as-of-the-beginning-of-this; a phrase list of incomplete phrases

;  category-if-completed

  incomplete-phrase-link?			; an incomplete phrase

  #+development last-token-position)	;taken from the edit-state when an
					;instance is made.  Can be NIL. Right
					;now it looks like this is actually the
					;end of the PREVIOUS token



(defmacro make-incomplete-phrase
	  (phrase-rule-completions incomplete-stack-of-constituents
	   incomplete-phrases-as-of-the-beginning-of-this)
  `(setf (chain-of-incomplete-phrases? current-edit-state)
	 (make-incomplete-phrase-structure
	   ,phrase-rule-completions ,incomplete-stack-of-constituents
	   ,incomplete-phrases-as-of-the-beginning-of-this
;	   ,category-if-completed
	   (chain-of-incomplete-phrases? current-edit-state)
	   ;; be careful about memory usage here.
	   #+development (car (stack-of-positions-after-tokens current-edit-state)))))

;; From DDM
#+development
(defun print-incomplete-phrase (phrase stream depth)
  (declare (ignore depth))
  (let* ((list-of-completions (phrase-rule-completions phrase))
 	 (completion (when list-of-completions
 		       (first list-of-completions)))
 	 (next (when completion
 		 (category-of-next-constituent completion))))
    (printing-random-object (phrase stream) ; wraps result in #<..>
      (if next
 	  (let ((s (category-symbol next)))
 	    (if (symbolp s)
 		(format stream "~a ~a"
			(string-downcase (symbol-name s))
			(last-token-position phrase))
 		(format stream " >> not a symbol << "))) 
 	  (format stream "incomplete-phrase")))))


(defun reclaim-chain-of-incomplete-phrases (chain-of-incomplete-phrases?)
  (loop as incomplete-phrase? = chain-of-incomplete-phrases?
	while incomplete-phrase?
	do (setq chain-of-incomplete-phrases?	; changes arg
		 (incomplete-phrase-link? incomplete-phrase?))
	   (reclaim-incomplete-phrase incomplete-phrase?)))








;;;; Parsing



(defvar incomplete-phrases-at-frontier)


;;; `transform-constituent-completely' is part of an experimental
;;; mechanism for an alternate interpretation of instance rule reduction.
;;; See add-grammar-rules-without-losing-transforms.

(defun transform-constituent-completely (constituent
					  subcategory-path category-of-completion
					  number-of-transforms)
  (let ((transformed-constituent constituent))
    ;; Step one gather categories for transforms in order
    ;; that they should be applied.  This involve going from
    ;; most specific category to most general
    (loop for i from 1 to number-of-transforms
	  as category = (svref subcategory-path i)
	  as next-category = (if (=f i number-of-transforms)
				 category-of-completion
				 (svref subcategory-path (1+f i)))
	  as more-general-catgory-index 
	     = (loop for more-general-category in (more-general-categories category)
		     as i from 0 by 1
		     when (eq more-general-category next-category)
		       return i)
	  as the-transform
	     = (and more-general-catgory-index
		    (nth more-general-catgory-index
			 (transformation-lists-for-more-general-categories category)))
	  do
      (setf transformed-constituent
	    (if the-transform
		(transform-constituent transformed-constituent the-transform)
		transformed-constituent))
      (when (eq transformed-constituent bad-phrase)
	(return-from transform-constituent-completely bad-phrase)))
    transformed-constituent))


;;; `have-constituent-to-annotate-p' is an abstraction used by
;;; add-constituent-to-incomplete-phrases to determine whether or not the
;;; constituent is one that should be annotated. 

(defun-simple have-constituent-to-annotate-p (constituent category-of-constituent)
  (and (consp constituent)		; Don't waste time on non-sexpish things.
       ;; Beacuse we don't want to annotate BEGIN-END blocks (or other
       ;; "surrounding" forms), only the statements within.  Consider
       ;; passing this along and having the compiler choose to ignore
       ;; it. -dkuznick, 1/15/99 
       (not (eq (category-symbol category-of-constituent)
		'proc-compound-statement))
       ;; hackeroo.  Consider storing result of (get- ) in global to save lookup each time or memoizing -dkuznick, 1/14/99
       (or (subcategoryp category-of-constituent
			 (get-category-for-category-symbol-if-any
			   'proc-simple-statement))
	   ;;to get logical expressions and the like
	   (subcategoryp category-of-constituent
			 (get-category-for-category-symbol-if-any 'unique-literal)))))

;;; `editing-annotatable-code-p' is a kludge to determine if we should be
;;; generating annotation information based on the thing we are editing.
;;; Currently, only procedures are ok.  We may want to add rules, functions and
;;; formulas in the future.  Possibly even inspects (which non-obviously
;;; compile their query).

(defun-substitution-macro editing-annotatable-code-p (edit-state)
  (and (eq (name-of-slot-being-edited edit-state) 'procedure-definition)
       ;; Consider abstracting the code below below because this idiom is used
       ;; in numerous places (and add to place in parts.lisp that's being
       ;; unsafe).  Look for serial-number-of-frame-being-edited? for the other
       ;; places to add the abstraction.  One reason maybe not to is because of
       ;; forward-referencing, we are being forced to use somehwat less
       ;; efficient calls here.  We could try to move this whole thing as a
       ;; function later and forward reference it instead.  -dkuznick, 2/4/03
       (let ((frame? (frame-being-edited? edit-state)))
	 (and frame?
	      (not (frame-has-been-reprocessed-p-function
		     frame?
		     (serial-number-of-frame-being-edited? edit-state)))
	      (of-class-p-function frame? 'procedure)))))


;;; In order for `maybe-annotate-constituent' to ensure that the annotations
;;; can be seen during compilation, the constituents/sexps which the compiler
;;; sees must either be EQ to the ones here, or if they get copied before
;;; compilation, the annotations must get rehashed.  Two cases which were
;;; having this problem were using the update button from the classic
;;; editor,and using the TW2 editor.  Then in G2 8.1a0 the native editor had
;;; the same problem with the apply button (because it was doing the same thing
;;; as update).  See bugs HQ-4984532 "Update from editor causes loss of go to
;;; source functionality", HQ-4595449 "Editing procedure with TW2 causes loss
;;; of go to source functionality" and HQ-4954032 "Using apply from native
;;; editor is setting invalid breakpoints." for more info.

(defun-void maybe-annotate-constituent (constituent category-of-constituent)
  (when (and generate-source-annotation-info
	     (editing-annotatable-code-p current-edit-state)
	     (have-constituent-to-annotate-p constituent category-of-constituent))
    ;; We have a statement to annotate
    (let ((position-for-annotation-hash (car (stack-of-positions-after-tokens
					       current-edit-state))))
      (when position-for-annotation-hash
	(let ((annotation (make-annotation (first position-for-annotation-hash)
					   (second position-for-annotation-hash))))
	  #+forDebugging
	  (format t "Hashing annotation ~s of category ~s for sexp ~s~%~
                 Next most recent pos: ~s~%"
		  annotation
		  category-of-constituent
		  constituent
		  (second (stack-of-positions-after-tokens current-edit-state)))
	  (set-current-annotation-context constituent annotation))))))

;;; `Add-constituent-to-incomplete-phrases' tries to extend each incomplete
;;; phrase by adding constituent, transformed and/or checked if appropriate, in
;;; all possible ways.  Where constituent completes a phrase, apply the
;;; transformations, if any, and recur as appropriate with the resulting phrase.
;;; Where a phrase may be continued after constituent is added, add an
;;; appropriate new incomplete phrase to incomplete-parses-at-frontier.

(defun add-constituent-to-incomplete-phrases
    (constituent category-of-constituent incomplete-phrases)
  (unless (eq constituent bad-phrase)
    (maybe-annotate-constituent constituent category-of-constituent))
  (loop for incomplete-phrase in incomplete-phrases
	do (loop for phrase-rule-completion
		     in (phrase-rule-completions incomplete-phrase)
		 as transformation-list-for-constituent-or-t?
		    = (subcategoryp
			category-of-constituent
			(category-of-next-constituent phrase-rule-completion))
		 for transformed-constituent-or-bad-phrase
		     = (if transformation-list-for-constituent-or-t?
			   (transform-constituent-for-add-constituent-to-incomplete-phrase
			     constituent category-of-constituent phrase-rule-completion
			     transformation-list-for-constituent-or-t?)
			   bad-phrase)
		 unless (eq transformed-constituent-or-bad-phrase bad-phrase)
		   do (let ((transformation-list-or-t?
			      (transformation-list-or-t? phrase-rule-completion)))
			(when transformation-list-or-t?
			  (let ((second-transformed-constituent-or-bad-phrase
				 (transform-constituent-for-incomplete-phrase
				   transformed-constituent-or-bad-phrase
				   transformation-list-or-t?
				   (incomplete-stack-of-constituents incomplete-phrase))))
			    (unless (eq second-transformed-constituent-or-bad-phrase bad-phrase)
			      (add-constituent-to-incomplete-phrases
			        second-transformed-constituent-or-bad-phrase
			        (category-for-completed-phrase phrase-rule-completion)
			        (incomplete-phrases-as-of-the-beginning-of-this incomplete-phrase))))))
			(add-constituent-to-incomplete-phrase-per-transformation
			  incomplete-phrase
			  (phrase-rule-completions-past-next-constituent phrase-rule-completion)
			  transformed-constituent-or-bad-phrase)))
  (let ((info (phrase-rule-completions-addable-to-some-incomplete-phrase
		category-of-constituent incomplete-phrases)))
    (begin-phrases-addable-to-some-incomplete-phrase-with-agenda
      info constituent incomplete-phrases)
    (loop for e in info do (reclaim-grammar-list e))
    (reclaim-grammar-list info)))

(defun add-constituent-to-incomplete-phrase-per-transformation
    (incomplete-phrase phrase-rule-completions-past-next-constituent transformed-constituent-or-bad-phrase)
  (let ((stack (incomplete-stack-of-constituents incomplete-phrase))
	(beginning-phrases (incomplete-phrases-as-of-the-beginning-of-this incomplete-phrase)))
    (when (and phrase-rule-completions-past-next-constituent
	       (not (phrases-addable-to-some-incomplete-phrase-inner-2
		      phrase-rule-completions-past-next-constituent
		      beginning-phrases stack
		      transformed-constituent-or-bad-phrase)))
      (phrase-push (make-incomplete-phrase
		     phrase-rule-completions-past-next-constituent
		     (phrase-cons transformed-constituent-or-bad-phrase stack)
		     beginning-phrases)
		   incomplete-phrases-at-frontier))))

;; For each level of category generality at which constituent can begin a phrase
;; that can, if and when completed, be added to one or more of the
;; incomplete phrases, add a new incomplete phrase, consisting only of constituent, to
;; incomplete-phrases-at-frontier.
(defun begin-phrases-addable-to-some-incomplete-phrase-with-agenda
       (info constituent incomplete-phrases)
  (loop for (category-or-category+transformation-list . completions) in info
	do (loop with transformation-considered-yet? = nil
		 with constituent-or-bad-phrase
		 for phrase-rule-completions in completions
		 unless (or (phrases-addable-to-some-incomplete-phrase-inner-2
			      phrase-rule-completions incomplete-phrases nil constituent)
			    (eq (cond
				  (transformation-considered-yet?
				   constituent-or-bad-phrase)
				  (t (setq transformation-considered-yet? t)
				     (setq constituent-or-bad-phrase
					   (if (consp category-or-category+transformation-list)
					       (transform-constituent
						 constituent (cdr category-or-category+transformation-list))
					       constituent))))
				bad-phrase))
		   do (phrase-push (make-incomplete-phrase
				     phrase-rule-completions
				     (phrase-cons constituent-or-bad-phrase nil)
				     incomplete-phrases)
				   incomplete-phrases-at-frontier))))

(defun-simple phrase-rule-completions-addable-to-some-incomplete-phrase
    (category-of-constituent incomplete-phrases)
  (loop with agenda = (agenda-of-more-general-categories-to-search category-of-constituent)
	for agenda-item? in (if (listp agenda) agenda '(nil))
	for category-or-category+transformation-list = (or agenda-item? agenda)
	as category-of-agenda-constituent = (if (atom category-or-category+transformation-list)
						category-or-category+transformation-list
						(car category-or-category+transformation-list))
	for completions-list = (phrase-rule-completions-addable-to-some-incomplete-phrase-1
				 category-of-agenda-constituent incomplete-phrases)
	when completions-list
	  collect (grammar-cons category-or-category+transformation-list completions-list)
	  using grammar-cons))

(defun phrase-rule-completions-addable-to-some-incomplete-phrase-1
    (category-of-agenda-constituent incomplete-phrases)
  (loop for phrase-rule-completions
	    in (phrase-rule-completions-for-each-category-this-may-begin category-of-agenda-constituent)
	as category-for-completed-phrase
	   = (category-for-completed-phrase (car phrase-rule-completions))
	as categories-completed-phrase-can-be-or-begin
	   = (categories-this-can-be-or-begin category-for-completed-phrase)
	;; The speed of the following test is critical to parsing speed, if
	;; the grammar is large.  As of 10/21/89, this test accounted for
	;; about 60% of parsing time (on an Explorer II).  Without grammar
	;; compilation, however it would be much slower, because of
	;; combinatorially explosive search redundancy.
	when (loop as incomplete-phrase in incomplete-phrases
		   thereis (loop for phrase-rule-completion
				     in (phrase-rule-completions incomplete-phrase)
				 as category-of-next-constituent
				    = (category-of-next-constituent phrase-rule-completion)
				 thereis (or (eq category-of-next-constituent category-for-completed-phrase)
					     (and (category-is-for-category-symbol-p
						    category-of-next-constituent)
						  (category-set-memq
						    category-of-next-constituent
						    categories-completed-phrase-can-be-or-begin)))))
	  collect phrase-rule-completions using grammar-cons))

(defun-simple phrases-addable-to-some-incomplete-phrase-inner-2
    (phrase-rule-completions incomplete-phrases more-constituents constituent)
  (loop for incomplete-phrase-at-frontier
	    in incomplete-phrases-at-frontier
	thereis
	(and (eq (phrase-rule-completions incomplete-phrase-at-frontier)
		 phrase-rule-completions)
	     (eq (incomplete-phrases-as-of-the-beginning-of-this incomplete-phrase-at-frontier)
		 incomplete-phrases)
	     (eq (cdr (incomplete-stack-of-constituents incomplete-phrase-at-frontier))
		 more-constituents)
	     (equal (car (incomplete-stack-of-constituents incomplete-phrase-at-frontier))
		    constituent))))

(defun transform-constituent-for-add-constituent-to-incomplete-phrase
    (constituent category-of-constituent phrase-rule-completion transformation-list-for-constituent-or-t?)
  (loop for i from 0 below max-instance-rule-chaining
	do (setf (svref current-subcategory-path i) nil))
  (set-current-subcategory-path
    category-of-constituent
    (category-of-next-constituent phrase-rule-completion))
  (let ((number-of-category-generalizations? currently-tracking-subcategory-path-max))
    (cond
      ((eq transformation-list-for-constituent-or-t? t)
       constituent)
      ((and number-of-category-generalizations?
	    (>f number-of-category-generalizations? 1))
       (transform-constituent-completely
	 constituent
	 current-subcategory-path
	 (category-of-next-constituent phrase-rule-completion)
	 number-of-category-generalizations?))
      (t
       (transform-constituent
	 constituent transformation-list-for-constituent-or-t?)))))

(defun transform-constituent-for-incomplete-phrase
    (transformed-constituent transformation-list-or-t? stack)
  (if (eq transformed-constituent bad-phrase)
      bad-phrase
      (let ((initial-result
	      (if (and (not (eq transformation-list-or-t? t))
		       (car transformation-list-or-t?))
		  (make-constituent-per-template
		    (car transformation-list-or-t?)
		    stack
		    transformed-constituent
		    (length stack))
		  (loop with constituents = (phrase-list transformed-constituent)
			while stack
			do (phrase-push (pop stack) constituents)
			finally (return constituents)))))
	(if (or (eq transformation-list-or-t? t)
		(null (cdr transformation-list-or-t?)))
	    initial-result
	    (perform-transformation-operations
	      initial-result
	      (cdr transformation-list-or-t?))))))


;; Consider separately handling the case of a single phrase rule completion in the
;; test loop.

;; Improve the efficiency of the search!

;; Consider reversing the order of the loops.

;; Consider looping instead of recurring when there is exactly one more general category
;; or exactly one list of phrase rule completions.



;;; `Add-constituent-to-incomplete-phrases' tries to extend each incomplete phrase by
;;; adding constituent, transformed and/or checked, if appropriate, in all possible ways.

;;; Where constituent completes a phrase, apply the transformations, if any, and
;;; recur as appropriate with the resulting phrase.  Where a phrase may be continued
;;; after constituent is added, add an appropriate new incomplete phrase to
;;; incomplete-parses-at-frontier.

;;; For each level of category generality at which constituent can begin a phrase (that can
;;; begin a phrase ...) that can, if and when completed, be added to one or more of the
;;; incomplete phrases, add a new incomplete phrase, consisting only of constituent, to
;;; incomplete-phrases-at-frontier.



;; Some code BAH and MHD are developing.  Credit for the idea, which is looking good,
;; should go to BAH, who thought of most of this, unless it turns out bad, in which
;; case MHD should be blamed for paying attention to it.  (MHD 5/24/91)



;;; Begin-phrases-addable-to-some-incomplete-phrase-with-agenda ... a possible
;;; replacement for begin-phrases-addable-to-some-incomplete-phrase. ... does
;;; not take a transformation-list-for-constituent? argument.  


;;; An `agenda' is either
;;;
;;;     a category (an atom)
;;;
;;; of a list of the form
;;;
;;;     ( { category | (category . transformation-list) } )
;;;
;;; Note that an agenda CANNOT be a single (category . transformation-list).


;;; The idea of this is to use the old bottom-up method, but compile in advance the
;;; paths up from the consituent to the most general category, as well as to
;;; remove duplicate elements within such paths.  This is only done for non-token
;;; categories -- in the case of token categories, the only element of the agenda
;;; would be the token category itself.  WRONG -- FIX -- needs doing for tokens.

;; To do -- the new slot should replace or at least share space with more-general-
;; categories ultimately. -- no, not really the same -- maybe in a large number
;; of cases there could be some sharing, but it might be hairy!

;; the following forms only used at grammar-compile time:

(defun set-up-agendas-of-more-general-categories-to-search ()
  (loop for category-symbol in (category-symbols current-grammar)
	do (set-up-agendas-1
	     (get-category-for-category-symbol-if-any category-symbol)))
  (loop for token in (tokens-with-specific-categories current-grammar)
	do (set-up-agendas-1 (get-category-of-token token))))


(defun set-up-agendas-1 (category)
  #+development
  (unless category
    (error "set-up-agendas-1 was called on NIL!"))
  (reclaim-agenda-of-more-general-categories
    (agenda-of-more-general-categories-to-search category))
  (setf (agenda-of-more-general-categories-to-search category) nil)
  (let ((agenda (get-more-general-categories-and-transformations category)))
    (setf (agenda-of-more-general-categories-to-search category)
	  (cond
	    ((null agenda)
	     nil)
	    ((and (null (cdr agenda))
		  (atom (car agenda)))
	     (prog1 (car agenda)
		    (setf (car agenda) nil)
		    (reclaim-grammar-cons agenda)))
	    (t agenda)))))


(defvar current-agenda-accumulating)		; just used locally below,
						;   when compiling grammar

(defun get-more-general-categories-and-transformations (category)
  (let ((current-agenda-accumulating nil))
    (get-more-general-categories-and-transformations-1 category nil)
    current-agenda-accumulating))

(defun get-more-general-categories-and-transformations-1
       (category transformation-list-for-constituent?)
  (when (and (phrase-rule-completions-for-each-category-this-may-begin category)
	     ;; see if already a member:
	     (loop for agenda-item in current-agenda-accumulating
		   never
		     (cond
		       ((atom agenda-item)
			(and (null transformation-list-for-constituent?)
			     (eq agenda-item category)))
		       ((and transformation-list-for-constituent?
			     (eq (car agenda-item) category)
			     (equal (cdr agenda-item)
				    transformation-list-for-constituent?))))))
    (setq current-agenda-accumulating
	  (grammar-cons 
	    (if transformation-list-for-constituent?
		(grammar-cons category transformation-list-for-constituent?)
		category)
	    current-agenda-accumulating)))
  (loop for more-general-category
	    in (more-general-categories category)
	as corresponding-transformation-lists
	   = (transformation-lists-for-more-general-categories category)
	   then (cdr corresponding-transformation-lists)	; hmnh!?
	do (get-more-general-categories-and-transformations-1
	     more-general-category
	     (or transformation-list-for-constituent?
		 (car corresponding-transformation-lists)))))



;;; Reclaim-agenda-of-more-general-categories ... 

(defun reclaim-agenda-of-more-general-categories (agenda)
  (unless (atom agenda)
    (loop for agenda-items on agenda
	  do (if (consp (car agenda-items))
		 (reclaim-grammar-cons (car agenda-items)))
	     (setf (car agenda-items) nil)	; not nec.
	  finally
	    (reclaim-grammar-list agenda))))




;;;; Compiling the Grammar



;;; `Grammar compilation' is done solely for the purpose of speeding up a test in
;;; begin-phrases-addable-to-some-incomplete-phrase (q.v.).



;;; `Compile-grammar' ...

(defun compile-grammar (grammar)
  (decache-all-strict-subcategory-infos)
  (get-or-make-category-for-category-symbol 'irrelevant)
  (loop for category-symbol in (category-symbols grammar)
	as category = (get-category-for-category-symbol-if-any category-symbol)
	unless (eq (categories-this-can-be-or-begin category) 'not-a-result-category)
	  do (setf (categories-this-can-be-or-begin category) (category-set-empty))
	     (fill-in-categories-this-can-be-or-begin
	       (get-category-for-category-symbol-if-any category-symbol)
	       (get-category-for-category-symbol-if-any category-symbol)))
  (set-up-agendas-of-more-general-categories-to-search)
  (setf (grammar-compiled? grammar) t))



(defun fill-in-categories-this-can-be-or-begin (category category-for-category-symbol)
  (unless (category-set-memq category (categories-this-can-be-or-begin category-for-category-symbol))
    (unless (eq category category-for-category-symbol)
      (category-set-push category (categories-this-can-be-or-begin category-for-category-symbol)))
    (loop for more-general-category in (more-general-categories category)
	  unless (eq more-general-category category-for-category-symbol)
	    do (fill-in-categories-this-can-be-or-begin
		 more-general-category category-for-category-symbol))
    (loop for phrase-rule-completions
	      in (phrase-rule-completions-for-each-category-this-may-begin category)
	  as category-for-completed-phrase
	     = (category-for-completed-phrase (car phrase-rule-completions))
	  unless (eq category-for-completed-phrase category-for-category-symbol)
	    do (fill-in-categories-this-can-be-or-begin
		 category-for-completed-phrase
		 category-for-category-symbol))))




;;; `Compute-forward-category-search-statistics' ...

#+development
(defun compute-forward-category-search-statistics ()
  (loop with number-of-categories = (length (category-symbols current-grammar))
	as category-symbol in (category-symbols current-grammar)
	as category-for-category-symbol
	   = (get-category-for-category-symbol-if-any category-symbol)
	as all-non-token-categories-that-can-be-or-begin-this
	   = (compute-all-non-token-categories-that-can-be-or-begin-this
	       category-for-category-symbol)
	as length = (-f (length all-non-token-categories-that-can-be-or-begin-this) 1)
	as length-without-duplicates
	   = (-f (length
		   (remove-duplicates all-non-token-categories-that-can-be-or-begin-this))
		 1)
	do (reclaim-gensym-list all-non-token-categories-that-can-be-or-begin-this)
	sum length into total-with-duplicates
	sum length-without-duplicates into total-without-duplicates
	when (>f length 10)
	  collect `(,category-symbol ,length ,length-without-duplicates) into the-bad-ones
	finally
	  (setq the-bad-ones (sort the-bad-ones #'(lambda (a b) (>f (cadr a) (cadr b)))))
	  (return
	    (list number-of-categories
		  (/ (float total-with-duplicates) number-of-categories)
		  (/ (float total-without-duplicates) number-of-categories)
		  the-bad-ones))))




;;; `Compute-all-non-token-categories-that-can-be-or-begin-this' ... including those for
;;; all more specific categories (transitively), and including category-for-category-symbol
;;; itself.

#+development
(defun compute-all-non-token-categories-that-can-be-or-begin-this
       (category-for-category-symbol)
  (gensym-cons
    category-for-category-symbol
    (nconc
      (loop for more-specific-category
		in (more-specific-categories category-for-category-symbol)
	    when (category-is-for-category-symbol-p more-specific-category)
	      nconc (compute-all-non-token-categories-that-can-be-or-begin-this
		      more-specific-category))
      (loop for category-that-can-begin-this
		in (categories-that-can-begin-a-phrase-of-this-category
		     category-for-category-symbol)
	    when (category-is-for-category-symbol-p category-that-can-begin-this)
	      nconc (compute-all-non-token-categories-that-can-be-or-begin-this
		      category-that-can-begin-this)))))



;;; `Compute-be-or-begin-statistics' ...

#+development
(defun compute-be-or-begin-statistics ()
  (loop with number-of-categories = (length (category-symbols current-grammar))
	as category-symbol in (category-symbols current-grammar)
	as category-for-category-symbol
	   = (get-category-for-category-symbol-if-any category-symbol)
	as categories-this-can-be-or-begin
	   = (category-set-list (categories-this-can-be-or-begin category-for-category-symbol))
	as length = (length categories-this-can-be-or-begin)
	sum length into total
	when (>f length 10)
	  collect `(,category-symbol ,length) into the-bad-ones
	finally
	  (setq the-bad-ones (sort the-bad-ones #'(lambda (a b) (>f (cadr a) (cadr b)))))
	  (return
	    (list number-of-categories
		  (/ (float total) number-of-categories)
		  the-bad-ones))))



;;; `Compute-that-can-be-this-statistics' ...

#+development
(defun compute-that-can-be-this-statistics ()
  (loop with number-of-categories = (length (category-symbols current-grammar))
	as category-symbol in (category-symbols current-grammar)
	as category-for-category-symbol
	   = (get-category-for-category-symbol-if-any category-symbol)
	as categories-that-can-be-this
	   = (compute-all-more-specific-categories
	       category-for-category-symbol)
	as length = (length categories-that-can-be-this)
	sum length into total
	when (>f length 10)
	  collect `(,category-symbol ,length) into the-bad-ones
	finally
	  (setq the-bad-ones (sort the-bad-ones #'(lambda (a b) (>f (cadr a) (cadr b)))))
	  (return
	    (list number-of-categories
		  (/ (float total) number-of-categories)
		  the-bad-ones))))

#+development
(defvar all-more-specific-categories)

#+development
(defun compute-all-more-specific-categories (category)
  (let ((all-more-specific-categories nil))
    (compute-all-more-specific-categories-1 category)
    all-more-specific-categories))

#+development
(defun compute-all-more-specific-categories-1 (category)
  (loop for more-specific-category in (more-specific-categories category)
	; unless (memq more-specific-category all-more-specific-categories)
	  do (push more-specific-category all-more-specific-categories)
	unless (category-is-for-token-p more-specific-category)
	  do (compute-all-more-specific-categories-1 more-specific-category)))



;;; `Compute-can-be-statistics' ...

#+development
(defun compute-can-be-statistics ()
  (loop with number-of-categories = (length (category-symbols current-grammar))
	as category-symbol in (category-symbols current-grammar)
	as category-for-category-symbol
	   = (get-category-for-category-symbol-if-any category-symbol)
	as categories-this-can-be
	   = (compute-all-more-general-categories
	       category-for-category-symbol)
	as length = (length categories-this-can-be)
	sum length into total
	when (>f length 10)
	  collect `(,category-symbol ,length) into the-bad-ones
	finally
	  (setq the-bad-ones (sort the-bad-ones #'(lambda (a b) (>f (cadr a) (cadr b)))))
	  (return
	    (list number-of-categories
		  (/ (float total) number-of-categories)
		  the-bad-ones))))


#+development
(defvar all-more-general-categories)

#+development
(defun compute-all-more-general-categories (category)
  (let ((all-more-general-categories nil))
    (compute-all-more-general-categories-1 category)
    all-more-general-categories))

#+development
(defun compute-all-more-general-categories-1 (category)
  (loop for more-general-category in (more-general-categories category)
	; unless (memq more-general-category all-more-general-categories)
	  do (push more-general-category all-more-general-categories)
	do (compute-all-more-general-categories-1 more-general-category)))




;;;; Testing for Acceptability of Instances of Categories

;;; `Instance-of-category-acceptable-p' is true if an instance of
;;; category-symbol is acceptable immediately following the position
;;; corresponding to incomplete-phrases. This is determined by
;;; calling the standard function that (attempts to) advance the parse,
;;; `add-constituent-to-incomplete-phrases', but intercepting the
;;; global variable where the new parsing state is assembled, thereby
;;; keeping this query from actually affecting the real parse. If there
;;; is a follow-on state from this token (i.e. incomplete-phrases-at-frontier
;;; gets a value) then we know that the token/non-terminal is acceptable.


(defun instance-of-category-acceptable-p (category-symbol incomplete-phrases
					  category-is-a-token-p)
  (when (and (null incomplete-phrases)
	     current-parsing-context?) ; indicator that we're standalone
    (let ((cursor-token (parsing-context-cursor-token-function current-parsing-context?)))
      (when cursor-token
	(setq incomplete-phrases
	      (parsing-token-incomplete-phrases-function cursor-token)))))
  (when incomplete-phrases   ; optimization
    (let ((incomplete-phrases-at-frontier nil)
	  (category
	    (if category-is-a-token-p
		(get-category-of-token category-symbol)
		(get category-symbol
		     current-indicator-for-category-of-this-name))))
      (when category
	(add-constituent-to-incomplete-phrases
	  nil category incomplete-phrases)
	incomplete-phrases-at-frontier))))






;;;; Registering a Directory of Names



;;; To be guaranteed that a grammar category for which a directory of names is
;;; maintained will appear on menus for parsing, even when it may not have a
;;; null directory-of-names property, a `registered directory of names' is
;;; needed.  (In some cases, parsing can be interfered with when there are no
;;; entries in a category directory of names, and then it is vital to register
;;; that category.)
;;;
;;; The macro `def-registered-directory-of-names' registers the category named
;;; category-symbol as a name directory.

(def-global-property-name registered-directory-of-names-p) ; t or nil

(defmacro def-registered-directory-of-names (category-symbol)
  `(progn
     (setf (registered-directory-of-names-p ',category-symbol) t)
     ',category-symbol))

;; This is needed for the fix the strange case of file-name/directory-name not
;; showing up on the KB load editor when there are no instances, and the parser
;; actually failing.  See if this kludge is really necessary, or can be avoided!
;; (MHD 4/18/94)   Elaboration: (ddm 7/15/97) Before today here were only two
;; instances where this was used, both in kb-load1 to fix the bug that Mark
;; was commenting on here. On the other hand, being able to include a prompt for
;; the category even though the directory is empty makes sense in some (all?)
;; cases, as indicated by the bugs we've gotten that finds their vicarious
;; presense to be wierd and unintutive (or a regression), e.g. HQ-951010.





;;;; Registering a abstract integer category



;;; To be guaranteed that a grammar category that rewrites simply as integer
;;; category is presented to end-users on menus for parsing, a `registered
;;; abstract integer category' is needed.
;;;
;;; The macro `def-registered-abstract-integer-category' registers the category
;;; named category-symbol as a name directory.
;;;
;;; By convention, those categories that are registered should be indexed and
;;; documented in the (G2) reference manual, unless it's very obvious what they
;;; mean (e.g., positive integer).

(def-global-property-name registered-abstract-integer-category-p) ; t or nil

(defmacro def-registered-abstract-integer-category (category-symbol)
  `(progn
     (setf (registered-abstract-integer-category-p ',category-symbol) t)
     ',category-symbol))

;; This is needed for the fix the strange case of file-name/directory-name not
;; showing up on the KB load editor when there are no instances, and the parser
;; actually failing.  See if this kludge is really necessary, or can be avoided!
;; (MHD 4/18/94)


(def-registered-abstract-integer-category priority)
(def-registered-abstract-integer-category non-negative-integer)
(def-registered-abstract-integer-category positive-integer)

;; As of 12/9/94, the set of all candidates for this were
;;
;;  vertices-list  PRIORITY  package-code  integer-attribute  POSITIVE-INTEGER
;;  tcp-ip-port-number  range-slack-spec  NON-NEGATIVE-INTEGER  point-factor
;;  vertices-list-tail  integer-list-tail  significant-digit-spec
;;  g2ds-tcp-ip-port-number  initial-margin-for-workspaces  grid-line-ratio
;;  millisecond-sleep-interval
;;
;; Those in all-caps were registered.
;; 
;; Consider solving this UI problem by offering menus like
;;
;;    any priority (an integer in the range [1..10])
;;
;;    any grid-line-ratio (an integer in the range [0..50]
;;
;; and really doing the range checking at the parser level.
;;
;; Also desirable would be, for example, length-limited strings
;;
;;    any dos-file-name (a 6.3-length file name string)
;;
;; etc.!

;; That list was computed with

#+comment
(defun compute-all-integer-preterminals ()
  (loop with all-categories
	= (let ((x nil))
	    (do-symbols (s (find-package 'ab))
	      (when (get-category-for-category-symbol-if-any s)
		(push (get-category-for-category-symbol-if-any s) x)))
	    x)
	with listed-ic = (list (get-category-for-category-symbol-if-any 'integer))
	for x in (loop for x in all-categories
		       when (equal (more-specific-categories x) listed-ic)
			 collect x)
	collect (category-symbol x)))




;;;; Menus for Parsing




;;; `Reclaim-menu-content-structure' reclaims the grammar conses in menu-content-structure.

(defun-void reclaim-menu-content-structure (menu-content-structure)
  (reclaim-grammar-tree menu-content-structure))

;; This could be done a bit more efficiently.



;;; `Make-menu-content-structure-for-character-position,' based upon its arguments, returns
;;; a `menu content structure' of the form (category-menu {token-menu}).   A `category menu'
;;; is a list of category symbols, each of which represents a category, any instance of
;;; which is a possible next token.  A `token menu' is a list of tokens and/or token
;;; sequences, where a `token sequence' is a list of tokens that constitute a possible next
;;; phrase, with :upcase optionally at the head of the list to indicate that symbols in the
;;; token menu should be printed in upper case.  The (approximate) size of a token sequence
;;; is limited, to avoid having to format menu items.

;;; The returned menu content structure consists of those elements of menu-content-
;;; structure-for-token-position that can be or begin with a token that (a) is of a type
;;; included in potential-token-types and (b) begins with prefix-simple-string.  Menu-
;;; content-structure-for-token-position should have been generated by make-menu-content-
;;; structure-for-token-position.  Prefix-simple-string should not be, though it may be,
;;; empty.  Note that a menu content structure is a list made entirely of unshared grammar
;;; conses, any non-atomic elements of which are also menu content structures, and that it
;;; should be reclaimed using reclaim-menu-content-structure.

(defparameter maximum-size-of-token-sequence 60)	; a number of characters

;; This was 25 until today, and had been so since the beginning of G2.
;; It turns out that people are mostly bothered by having to click more
;; than once to insert (or see) the complete sequence.  Try this out,
;; and see if users like it.  (Examples of things affected are the
;; Load-KB menu, in which ", bringing formats up-to-date" used to be
;; broken up into two parts, and the debugging-parameters system table,
;; in which warning-message-level grammar used to be broken up into 2 or
;; 3 parts, and parts of the grammar used in "change" slot of object
;; definitions.  (MHD 6/27/91)

   

(defun make-menu-content-structure-for-character-position
       (menu-content-structure-for-token-position
	potential-token-types prefix-simple-string)
  (let* ((old-menus
	   (if (eq (car menu-content-structure-for-token-position) 'end)
	       (cdr menu-content-structure-for-token-position)
	       menu-content-structure-for-token-position))
	 (category-symbols-for-menu nil))	; reversed
    (loop with category-menu = (car old-menus)
	  as category-symbol in category-menu
	  when (loop with category		
		       = (get-or-make-category-for-category-symbol category-symbol)
		     as type-of-token in potential-token-types
		     thereis
		       (or (if (not (eq type-of-token 'punctuation-mark))
			       (subcategoryp
				 (get-or-make-category-for-category-symbol
				   type-of-token)
				 category))
			   (if (eq type-of-token 'symbol)
			       (subcategoryp
				 (get-or-make-category-for-category-symbol
				   'unreserved-symbol)
				 category))))
	    do (setq category-symbols-for-menu
		     (grammar-cons-macro
		       category-symbol category-symbols-for-menu)))
    (grammar-cons
      (nreverse category-symbols-for-menu)
      (loop with length-of-prefix-simple-string	; have this be an arg?
	      = (lengthw prefix-simple-string)
	    as menu in (cdr old-menus)
	    nconc
	      (loop for menu-element in menu
		    when (or (eq menu-element :upcase)
			     (let* ((initial-token
				      (if (atom menu-element)
					  menu-element
					  (first menu-element)))
				    (string-for-initial-token
				      (if (symbolp initial-token)
					  (symbol-name-text-string initial-token) ; self-limiting loss
					  (twith-output-to-text-string	; abstract!
					    (let ((write-symbols-parsably? t)
						  (write-strings-parsably? t))
					      (twrite initial-token))))))
			       (prog1
				 (when (and (not (memq 'right-string potential-token-types))
					    (or (not (memq 'whole-string
							   potential-token-types))
						(text-string-p initial-token))
					    (<=f length-of-prefix-simple-string
						 (lengthw string-for-initial-token)))
				   (loop for i from 0
					       below length-of-prefix-simple-string
					 always
					 (char=w (charw string-for-initial-token i)
						 (charw prefix-simple-string i))))
				 (if (not (symbolp initial-token))	; see above!
				     (reclaim-text-string string-for-initial-token)))))
		      collect
			(if (atom menu-element)
			    menu-element
			    (copy-list-using-grammar-conses menu-element))
			into new-menu-elements using grammar-cons
		    finally
		      (return
			(if new-menu-elements
			    (grammar-cons new-menu-elements nil))))))))

;; Consider changing "menu content structure" to "edit menu structure".

;; This assumes that kb-specific symbol tokens do not need to be considered when computing
;; the category menu.  (Note that all relevant kb-specific symbol tokens should be in
;; menu-content-structure-for-token-position.)



(defconstant menu-too-many-instances '(too-many-instances))


;;; `Make-category-instance-menus' returns either a list of token menus of all
;;; instances of the categories specified in category-menu (that start with prefix-
;;; symbol-string?, if specified) or else nil.  Nil is returned if either (a) there are
;;; no such instances, or (b) the number of such instances would be greater than
;;; maximum-number-of-instances.  To avoid duplicates, no instances are computed
;;; for a category when there is at least one more general category symbol in
;;; category-menu that has a directory of names (per the more-general-category-symbols-
;;; with-directories property of category-symbol).  If the object-name-menus-in-upper-
;;; case? parameter in the editor-parameters system frame is non-nil, instances of
;;; the object-name category will be made to print in upper case.

(defun-simple make-category-instance-menus
    (category-menu prefix-simple-string? maximum-number-of-instances)
  (loop for category-symbol in category-menu
	with number-of-instances-remaining = maximum-number-of-instances
	with all-instances-so-far = '()
	with category-instance-menus-so-far = '()
	as pruned-category-instance-menu = '()
	as length-of-pruned-menu = 0
	with category-instance-menu?
	do
    (setq category-instance-menu?
	  (make-menu-of-names-from-directory-if-few-enough
	    category-symbol prefix-simple-string?
	    number-of-instances-remaining))
    (unless (null category-instance-menu?)
      (when (eq category-instance-menu? menu-too-many-instances)
	(reclaim-menu-content-structure category-instance-menus-so-far)
	(reclaim-grammar-list all-instances-so-far)
	(return nil))
      (loop for instance in category-instance-menu?
	    unless (memq instance all-instances-so-far) do
		(grammar-push instance pruned-category-instance-menu)
		(incff length-of-pruned-menu)
		(grammar-push instance all-instances-so-far))
      (reclaim-grammar-list category-instance-menu?)
      (decff number-of-instances-remaining length-of-pruned-menu)
      (when (and (eq category-symbol 'object-name)
		 (get-slot-value-function
		   editor-parameters 'object-name-menus-in-upper-case? nil)
		 pruned-category-instance-menu)
	    (grammar-push :upcase pruned-category-instance-menu))
      (unless (null pruned-category-instance-menu)
	(grammar-push
	  pruned-category-instance-menu
	  category-instance-menus-so-far)))
	finally
	  (reclaim-grammar-list all-instances-so-far)
	  (return (nreverse category-instance-menus-so-far))))

;; This is used only by update-edit-menus-or-autocomplete-as-appropriate in module EDIT.

;; When there are too many instances, consider having an editor-parameters option to
;; include at least some, with ...'s.



;;; `Make-menu-content-structure-for-token-position,' based upon incomplete-phrases-at-this-
;;; position and phrase-rule-completions-past-instance-of-category, returns a menu content
;;; structure of the form ([END] category-menu {token-menu}).  The symbol END is present to
;;; indicate that an `end action' (ending the sequence of tokens here) would yield at least
;;; one instance of the category specified for parsing.  See above for further details.

;;; A category is explicitly represented on the category menu when either
;;;
;;;   (a) it has a directory of names; or
;;;   (b) it has a registered-directory-of-names-p property (on its symbol); or
;;;   (c) when all of the following are true:
;;;
;;;     (1) there are no immediate phrase rules for it;
;;;     (2) no menu items, including category symbols, have been or are
;;;       about to be added that can be or begin an instance of
;;;       the category (unless the category symbol is singular-number
;;;       or plural-number); and
;;;     (3) this category is not being examined as a subcategory
;;;       of a category that will be explicitly represented,
;;;       unless it's the category INTEGER and the category it's
;;;       a subcategory of is NOT a registered abstract integer
;;;       category (ugh).
;;;
;;; A category with immediate phrase rules is not explicitly represented because
;;; it is assumed that there will be explicit representation for at least some
;;; initial constituent of some such phrase.  The exception for singular-number
;;; and plural-number may need to be generalized.  Note that it may happen that
;;; both a category and some subcategory thereof are explicitly represented on
;;; the category menu.
;;; 
;;; A category is explicitly represented on the category menu either when it has a
;;; directory of names OR when all of the following are true:
;;;
;;;   (1) there are no immediate phrase rules for it;
;;;   (2) no menu items, including category symbols, have been or are
;;;       about to be added that can be or begin an instance of
;;;       the category (unless the category symbol is singular-number
;;;       or plural-number); and
;;;   (3) this category is not being examined as a subcategory
;;;       of a category that will be explicitly represented.
;;;
;;; A category with immediate phrase rules is not explicitly represented because
;;; it is assumed that there will be explicit representation for at least some
;;; initial constituent of some such phrase.  The exception for singular-number
;;; and plural-number may need to be generalized.  Note that it may happen that
;;; both a category and some subcategory thereof are explicitly represented on
;;; the category menu.


;;; A token is NOT represented as a menu item when ...

;;; Heuristics are used to break up what could be a single token menu into multiple token
;;; menus....
;;;
;;; At time, kludges are hard-wired in to affect the ordering, or to short-circuit the
;;; some or all of the heuristics in order to effect a good ordering.  One such is
;;; that the category MONTH is hard-wired to order the months by their seasonal order.
;;; This works around the problem caused by the fact that MAY can start both a month
;;; phrase, and a phrase like "may cause data-seeking", which caused it to appear at
;;; the end of the set of months.

(def-global-property-name omit-from-quoted-token-menus-p)	; currently applies only to
						                ;   single or first token

(def-global-property-name
    overriding-token-instances-without-specific-categories)	; overrides token-instances-without-specific-categories



;;; `Months-of-the-year' enumerates the standard 3-letter English month abbreviations
;;; as an ordered list of symbols in seasonal order.

(defparameter months-of-the-year
	      `(jan feb mar apr may jun jul aug sep oct nov dec))


;;; Use `overriding-token-instances-without-specific-categories' to get the list
;;; of months to appear in their proper order, despite the fact that MAY is both
;;; a month and the beginning of a G2 phrase like "May cause data-seeking".

(setf (overriding-token-instances-without-specific-categories 'month)
      months-of-the-year)


(defvar category-symbols-for-non-contributing-categories)     ; reversed; so far

(defvar collected-menu-content-structure)	; "reversed-menu-content-structure-so-far"?

(defvar menu-items-for-parsing)			; "reversed-token-menu-so-far"?

(defvar token-sequence-location-plist)

;; Token-sequence-location-plist is a grammar list of the form
;;
;;    { category-for-token-1 cons-holding-token-sequence-starting-with-token-1 }.

(defun skip-menu-items-if-all-are-repeats (menu-items-for-parsing collected-menu-content-structure)
  (loop for item-list in menu-items-for-parsing
	always (loop for menu-items in collected-menu-content-structure
		     thereis (loop for menu-item-list in menu-items
				   thereis (equal menu-item-list item-list)))))

(defun make-menu-content-structure-for-token-position
    (incomplete-phrases-at-this-position
      phrase-rule-completions-past-instance-of-category)
  (set-up-category-visit)
  (let* ((category-symbols-for-non-contributing-categories nil)
	 (collected-menu-content-structure nil)
	 (token-sequence-location-plist nil)
	 (irrelevant-category
	   (get-or-make-category-for-category-symbol 'irrelevant)))
    (loop for incomplete-phrase in incomplete-phrases-at-this-position
	  do (loop for phrase-rule-completion
		       in (phrase-rule-completions incomplete-phrase)
		   as category-of-next-constituent
		      = (category-of-next-constituent phrase-rule-completion)
		   unless (eq category-of-next-constituent irrelevant-category)
		     do (add-menu-items-for-category
			  category-of-next-constituent nil nil
			  (phrase-rule-completions-past-next-constituent
			    phrase-rule-completion))))
    (let ((menus
	    (grammar-cons
	      (nreverse category-symbols-for-non-contributing-categories)
	      (nreverse
		(loop for (i l) on token-sequence-location-plist
				by 'cddr
		      collect l using grammar-cons)))))
      (reclaim-grammar-list token-sequence-location-plist)
      (if (loop for incomplete-phrase in incomplete-phrases-at-this-position
		thereis
		(eq (phrase-rule-completions incomplete-phrase)
		    phrase-rule-completions-past-instance-of-category))
	  (grammar-cons 'end menus)
	  menus))))




(defun-simple remove-grammar-plist-element (plist indicator)
  (loop as l-trailer? = nil then (cdr l)	; abstract as grammar-remf?
	as l = plist	
	     then (cdr l-trailer?)
	when (eq (car l) indicator)
	  do (if l-trailer?
		 (setf (cdr l-trailer?) (cddr l))
		 (setq plist (cddr l)))
	     (setf (cddr l) nil)
	     (reclaim-grammar-list l)
	     (return plist)))

(defun approximate-size-of-token (token)
  (if (symbolp token)
      (text-string-length (symbol-name-text-string token))
      5)) ; compute actual size of non-symbol? 7?

(defvar one-sequence-of-following-tokens-only-p nil)

(defun get-lists-of-following-tokens
    (token phrase-rule-completions-past-this? approximate-size-of-token-sequence)
  (incff approximate-size-of-token-sequence (approximate-size-of-token token))
  (when (<=f approximate-size-of-token-sequence maximum-size-of-token-sequence)
    (remove-duplicates-from-lists-of-token-lists
      (if one-sequence-of-following-tokens-only-p
	  (when (and phrase-rule-completions-past-this?
		     (null (cdr phrase-rule-completions-past-this?)))
	    (extend-lists-of-following-tokens
	      token (car phrase-rule-completions-past-this?)
	      approximate-size-of-token-sequence))
	  (loop for completion in phrase-rule-completions-past-this?
		nconc (extend-lists-of-following-tokens
			token completion
			approximate-size-of-token-sequence))))))

(defun remove-duplicates-from-lists-of-token-lists (lists-of-token-lists)
  (prog1 (loop for tail on lists-of-token-lists
	       for list in lists-of-token-lists
	       for collectp = (not (member list (cdr tail) :test 'equal))
	       when collectp
		 collect list using grammar-cons
	       unless collectp
		 do (reclaim-grammar-list list))
    (reclaim-grammar-list lists-of-token-lists)))

(defun all-token-lists-are-pre-existing-p (lists)
  (loop for list in lists 
	always (loop for (category c-lists) on token-sequence-location-plist
					    by 'cddr
		     thereis (member list c-lists :test #'equal))))

(defun extend-lists-of-following-tokens
    (token phrase-rule-completion approximate-size-of-token-sequence)
  (let ((category-of-next-constituent
	  (category-of-next-constituent phrase-rule-completion)))
    (if (category-is-for-token-p category-of-next-constituent)
	(loop with next-token = (category-token category-of-next-constituent)
	      with lists = (or (get-lists-of-following-tokens
				 next-token
				 (if (null (transformation-list-or-t? phrase-rule-completion))
				     (phrase-rule-completions-past-next-constituent
				       phrase-rule-completion))
				 (1+f approximate-size-of-token-sequence))
			       (grammar-list (grammar-list next-token)))
	      for lists-tail on lists
	      do (grammar-push token (car lists-tail))
	      finally (return lists))
	(grammar-list (grammar-list token)))))

(defun add-menu-items-for-parsing-for-category (category lists)
  (if (all-token-lists-are-pre-existing-p lists)
      (progn
	(reclaim-grammar-tree lists)
	nil)
      (let ((existing-lists (getfq token-sequence-location-plist category)))
	(if existing-lists
	    (if (loop for list in existing-lists
		      always (member list lists :test 'equal))
		(progn
		  (reclaim-grammar-tree
		    (prog1 (cdr existing-lists)
		      (setf (car existing-lists) (car lists))
		      (setf (cdr existing-lists) (cdr lists))
		      (reclaim-grammar-cons lists)))
		  nil)
		(nconc existing-lists lists))
	    (setq token-sequence-location-plist
		  (grammar-cons
		    category
		    (grammar-cons
		      lists
		      token-sequence-location-plist)))))))

(defun add-token-for-parsing-for-category (category token)
  (add-menu-items-for-parsing-for-category
    category (grammar-list (grammar-list token))))

(defun add-menu-items-for-not-yet-visited-token-category
    (category phrase-rule-completions-past-this? more-general-category?)
  (let ((token (category-token category)))
    (unless (and (symbolp token)
		 (omit-from-quoted-token-menus-p token))
      (let ((lists (get-lists-of-following-tokens
		     token phrase-rule-completions-past-this? 0)))
	(cond
	  (lists
	   (add-menu-items-for-parsing-for-category category lists))
	  ((not (and more-general-category?
		     (eq (category-symbol more-general-category?) 'function-name)
		     (memq token '(average hour minute second symbol))))
	   ;; Remember to keep the ;; quoted list above in synch with the grammar rules
	   ;; function-name -> average | hour | minute | ...
	   ;; in module GRAMMAR3 from now on.  (MHD/BAH 8/28/91)

	   ;; The following is the only case that we check for
	   ;; duplicates.  This is to allow the
	   ;; overriding-token-instances-without-specific-categories
	   ;; property on a category symbol to contain elements that
	   ;; might otherwise be added as tokens here.  Thus far,
	   ;; this is the only plase where pushnew is necessary.  It
	   ;; is avoided elsewhere for efficiency; i.e., there's no
	   ;; known use for duplicates to appear, but they don't
	   ;; occur anyway, so we need not check for them. (MHD
	   ;; 5/2/95)
	   (add-token-for-parsing-for-category category token)))))))

(defun add-menu-items-for-not-yet-visited-non-token-category
    (category more-general-category-for-which-there-are-no-menu-items?)
  (let ((more-specific-categories (more-specific-categories category))
	(categories-that-can-begin-a-phrase-of-this-category
	  (categories-that-can-begin-a-phrase-of-this-category category))
	(category-symbol (category-symbol category))
	(number-of-menu-items-added 0))
    (when (token-instances-without-specific-categories category)
      (loop for token
		in (or (overriding-token-instances-without-specific-categories
			 (category-symbol category))
		       (token-instances-without-specific-categories category))
	    do (add-token-for-parsing-for-category category token)
	       (incff number-of-menu-items-added)))
    (when (symbol-tokens-for-category-symbol category-symbol)
      (loop for token in (symbol-tokens-for-category-symbol category-symbol)
	    do (add-token-for-parsing-for-category category token)
	       (incff number-of-menu-items-added)))
    (when more-specific-categories
      (loop for more-specific-category in more-specific-categories
	    when (category-is-for-token-p more-specific-category)
	      do (incff number-of-menu-items-added
			(add-menu-items-for-category	; simplify this?
			  more-specific-category category
			  (if (=f number-of-menu-items-added 0) category)
			  nil)))	       
      (loop for more-specific-category in more-specific-categories
	    when (category-is-for-category-symbol-p more-specific-category)
	      do (incff number-of-menu-items-added
			(add-menu-items-for-category
			  more-specific-category category
			  (if (=f number-of-menu-items-added 0) category)
			  nil))))
    (loop for beginning-category
	      in categories-that-can-begin-a-phrase-of-this-category
	  for completions = (sole-completion-for-beginning-category-to-category
			     beginning-category category)
	  do (incff number-of-menu-items-added
		    (add-menu-items-for-category
		      beginning-category nil nil
		      completions)))
    (when (and categories-that-can-begin-a-phrase-of-this-category
	       (=f number-of-menu-items-added 0))
      (setq number-of-menu-items-added 1))	; see note 1 below
    (when (or (directory-of-names category-symbol)
	      (registered-directory-of-names-p category-symbol) ; added. (MHD 4/18/94)
	      (and (or (=f number-of-menu-items-added 0)
		       (eq category-symbol 'number))
		   (or (null more-general-category-for-which-there-are-no-menu-items?)
		       (categories-that-can-begin-a-phrase-of-this-category ; see note 2 below
			 more-general-category-for-which-there-are-no-menu-items?)
		       (and (memq category-symbol ; another exception; generalize/document! see 
				  '(integer))     ;   note 3 below (MHD 12/9/94)
			    (not (registered-abstract-integer-category-p
				   (category-symbol
				     more-general-category-for-which-there-are-no-menu-items?)))))))
      (grammar-pushnew category-symbol category-symbols-for-non-contributing-categories)	
      (incff number-of-menu-items-added))
    number-of-menu-items-added))

(defun-simple sole-completion-for-beginning-category-to-category (beginning-category category)
  (loop with phrase-rule-completions? = nil
	as phrase-rule-completions
	   in (phrase-rule-completions-for-each-category-this-may-begin beginning-category)
	when (subcategoryp (category-for-completed-phrase (car phrase-rule-completions))
			   category)
	  do (if phrase-rule-completions?
		 (return nil)
		 (setq phrase-rule-completions? phrase-rule-completions))
	finally (return phrase-rule-completions?)))

(defvar prune-token-categories-visited-more-than-once-p nil)

;;; `Add-menu-items-for-category' ... returns the number of menu items it adds.  Phrase-rule-
;;; completions-past-this? should be nil unless category must be completed thereby to
;;; produce a phrase.

(defvar list-of-argument-lists-to-add-menu-items-for-category nil)

(defun add-menu-items-for-category
    (category more-general-category?
	      more-general-category-for-which-there-are-no-menu-items?
	      phrase-rule-completions-past-this?)
  (let* ((entry
	   (if (category-is-for-token-p category)
	       (if (or more-general-category?
		       phrase-rule-completions-past-this?)
		   (gensym-list category more-general-category?
				phrase-rule-completions-past-this?)
		   category)
	       (if more-general-category-for-which-there-are-no-menu-items?
		   (gensym-list category
				more-general-category-for-which-there-are-no-menu-items?)
		   category)))
	 (category-index (category-index category))
	 (category-visit-vector? (category-visit-vector? current-grammar))
	 (current-category-visit-stamp (current-category-visit-stamp current-grammar))
	 (category-visit-stamp-and-flag (svref category-visit-vector? category-index))
	 (desired-value (+f current-category-visit-stamp 1)))
    (if (if (consp entry)
	    (member entry list-of-argument-lists-to-add-menu-items-for-category
		    :test 'equal)
	    (=f category-visit-stamp-and-flag desired-value))
	0 
	(let ((list-of-argument-lists-to-add-menu-items-for-category
		(if (consp entry)
		    (gensym-cons entry list-of-argument-lists-to-add-menu-items-for-category)
		    list-of-argument-lists-to-add-menu-items-for-category)))
	  (unless (consp entry)
	    (setf (svref category-visit-vector? category-index) desired-value))
	  (prog1
	      (if (category-is-for-token-p category)
		  (if (add-menu-items-for-not-yet-visited-token-category
			category phrase-rule-completions-past-this? more-general-category?)
		      1 0)
		  (add-menu-items-for-not-yet-visited-non-token-category
		    category more-general-category-for-which-there-are-no-menu-items?))
	    (when (consp entry)
	      (reclaim-gensym-cons list-of-argument-lists-to-add-menu-items-for-category)
	      (reclaim-gensym-list entry)))))))

;; Note 1: This is for the case where, for example, "number" has already been added as
;; a menu item, with "integer" therefore having its number-of-menu-items value zero,
;; and then "week-phrase" starting with an integer ...

;; Note 2: This is for the case where, for example, "object-name" would be excluded
;; because it is a subcategory of "designation" where no menu items have yet been
;; added for designation.

;; Note 3: This is for the case where, for example, grid-line-ratio shows up as a category
;; on the menu just because it rewrote as category integer.  For those categories that
;; want to so appear, just register them using def-abstract-integer-category, q.v., above.

;; The value of this function matters, at present, only insofar as it is non-zero or zero.

;; Consider always using grammar-cons-macro, for greater speed.




;;; `Print-rewrite-rules-in-bnf-to-file' ...

#+development
(progn

(defun collect-rewrite-rules-into-list ()
  (loop	with category-symbols
	  = (nreverse (copy-list-using-gensym-conses (category-symbols current-grammar)))
	as category-symbol in category-symbols
	as category = (get category-symbol
			   (indicator-for-category-of-this-name current-grammar))
	collect (collect-category-into-list category)
	using gensym-cons
	finally (reclaim-gensym-list category-symbols)))

(defun collect-category-into-list (category)
  (gensym-cons
    (category-into-list category)
    (nconc
      (loop for category-that-can-begin-a-phrase-of-this-category
		in (categories-that-can-begin-a-phrase-of-this-category category)
	    nconc (loop for phrase-rule-completions
			    in (phrase-rule-completions-for-each-category-this-may-begin
				 category-that-can-begin-a-phrase-of-this-category)
			when (and phrase-rule-completions	; true at most once
				  (eq (category-for-completed-phrase
					(car phrase-rule-completions))
				      category))
			  nconc (collect-phrase-rule-completions-into-list
				  phrase-rule-completions
				  category-that-can-begin-a-phrase-of-this-category)))
      (loop for more-specific-category in (more-specific-categories category)
	    collect (gensym-list (gensym-list (category-into-list more-specific-category))
				 nil)
	      using gensym-cons)
      (loop for token in (token-instances-without-specific-categories category)
	    collect (gensym-list (gensym-list (gensym-list 'token token))
				 nil)
	      using gensym-cons))))

(defun collect-phrase-rule-completions-into-list
    (phrase-rule-completions category-for-first-constituent)
  (let ((list-of-first-constituent-category (gensym-list category-for-first-constituent)))
    (prog1 (collect-phrase-rule-completions-into-list-1
	     phrase-rule-completions list-of-first-constituent-category)
      (reclaim-gensym-cons list-of-first-constituent-category))))

(defun collect-phrase-rule-completions-into-list-1
    (phrase-rule-completions categories-for-earlier-constituents)
  (loop with last-cons = (last categories-for-earlier-constituents)
	for phrase-rule-completion in phrase-rule-completions
	as category-of-this-constituent = (category-of-next-constituent phrase-rule-completion)
	as list-of-this-category = (gensym-list category-of-this-constituent)
	as categories-for-constituents
	   = (cond (last-cons
		    (setf (cdr last-cons) list-of-this-category)
		    categories-for-earlier-constituents)
		   (t
		    list-of-this-category))
	as transformation-list-or-t? = (transformation-list-or-t? phrase-rule-completion)
	nconc (collect-phrase-rule-completions-into-list-1
		(phrase-rule-completions-past-next-constituent phrase-rule-completion)
		categories-for-constituents)
	when transformation-list-or-t?
	  nconc (gensym-list
		  (gensym-list
		    (loop for category in categories-for-constituents
			  collect (category-into-list category)
			    using gensym-cons)
		    (unless (eq transformation-list-or-t? t)
		      (copy-tree-using-gensym-conses
			transformation-list-or-t?))))
	do (when last-cons
	     (reclaim-gensym-cons (cdr last-cons))
	     (setf (cdr last-cons) nil))))

(defun category-into-list (category)
  (if (category-is-for-token-p category)
      (gensym-list 'token (category-token category))
      (gensym-list 'non-token (category-symbol category))))

(defun copy-category-as-list (list)
  (gensym-list (car list) (cadr list)))

(defun get-category-use-list (type name grammar-as-list)
  (loop for (nil . rules) in grammar-as-list
	as i from 1
	when (loop for (rhs) in rules
		   thereis (loop for (c-type c-name) in rhs
				 thereis (and (eq c-type type)
					      (eq c-name name))))
	  collect i using gensym-cons))

(defun get-list-of-all-tokens (grammar-as-list)
  (loop with token-list = nil
	for (nil . rule-list) in grammar-as-list
	do (loop for (rhs) in rule-list
		 do (loop for token in rhs
			  for (type name) = token
			  when (and (eq type 'token)
				    (not (memq name token-list)))
			    do (gensym-push name token-list)))
	finally (return token-list)))

)


#+development
(progn

(defun write-header-for-bnf ()
  (write-string "     BNF Grammar for G2       ")
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
  (format t					; conses
	  "     Copyright (c) 1986 - 2017 Gensym Corporation.
            All Rights Reserved.

     CONFIDENTIAL

     The information contained herein is confidential and
     proprietary to Gensym Corporation.  It may not be disclosed or
     transferred, directly or indirectly, to any third party without
     the explicit written permission of Gensym Corporation.")
  (terpri))

;;; The parameter include-transformations-in-bnf-printout? controls whether transformations
;;; are included in the printout of bnf rules by print-rewrite-rules-in-bnf-to-file.  By
;;; default this variable is true.

(defvar include-transformations-in-bnf-printout? t)	; (MHD 2/27/91)

;;; The function `print-rewrite-rules-in-bnf-to-file' prints current-grammar in
;;; a file.  It must be run in an AB process.
;;;
;;; By default, the file is named "grammar.bnf" in the current directory; this
;;; can be overridden by supplying a file name string as the keyword argument
;;; :FILE-NAME.
;;;
;;; By default, an index is created at the end of the file, subdivided into two
;;; sections: (1) an index of categories, and (2) an index of tokens.  To
;;; facilitate indexing, each BNF production is printed with an index number,
;;; starting from 1, that appears in square brackets ([]) after each BNF
;;; production's category. If you supply the keyword argument :NO-INDEX as true,
;;; the index will be left off at the end of the file, and index numbers will
;;; not appear in the output of each production in the file.  This may be
;;; particularly useful for cases where you wish to compare two versions of
;;; grammar, i.e., to avoid diffs appearing for every rule starting from the
;;; first where a different index number appeared.
;;;
;;; By default, each alternative of each production that has an associated
;;; transformation list is printed with its corresponding transformation list
;;; the following format:
;;;
;;;   => <transformation template>
;;;   -> <transformation operation> -> ...

;;; If you supply the keyword argument :NO-TRANSFORMATIONS as true, then
;;; transformation lists will not be printed.

(defun print-rewrite-rules-in-bnf-to-file
    (&key (file-name "grammar.bnf") no-index no-transformations)
  (with-open-file (#-ansi-cl lisp::*standard-output*
		   #+ansi-cl common-lisp::*standard-output* file-name :direction :output)
    (let ((include-transformations-in-bnf-printout? (not no-transformations)))
      (write-header-for-bnf)
      (loop with print-parts-as-structures-p = nil
	    with grammar-as-list = (collect-rewrite-rules-into-list)
	    for (category-list . rules) in grammar-as-list
	    as i from 1
	    do (print-category-in-bnf category-list rules (if no-index nil i))
	    finally
	      (unless no-index
		(write-bnf-category-index
		  (loop for (category-list) in grammar-as-list
			for (nil category-name) = category-list
			as i from 1
			collect (gensym-list
				  (copy-category-as-list category-list) i
				  (get-category-use-list
				    'non-token category-name grammar-as-list))
			  using gensym-cons)
		  "Categories")
		(write-bnf-category-index
		  (loop for token in (get-list-of-all-tokens grammar-as-list)
			collect (gensym-list
				  (gensym-list 'token token) nil
				  (get-category-use-list
				    'token token grammar-as-list))
			  using gensym-cons)
		  "Tokens"))
	      (reclaim-gensym-tree grammar-as-list)))))

(defvar number-of-bnf-alternatives-so-far)

(defun print-category-in-bnf (category-list rules index?)
  (when rules
    (format t "~%~%")
    (write-bnf-category category-list)
    (format t (if index? " [~d] ::=" " ::=") index?)
    (loop for number-of-bnf-alternatives-so-far from 0
	  for (rhs transformation-list) in rules
	  do (when (>f number-of-bnf-alternatives-so-far 0)
	       (write-string " \|"))
	     (format t "~%    ")
	     (write-bnf-alternative rhs)
	     (write-transformation-for-bnf transformation-list))))

(defun write-bnf-alternative (rhs)
  (loop	for first-p = t then nil
	for category-list in rhs
	for line-position = 4 then next-line-position
	for string-for-last-constituent
	    = (with-output-to-gensym-string (*standard-output*)
		(write-bnf-category category-list))
	for length-of-last-constituent = (length string-for-last-constituent)
	for next-line-position-if-on-this-line
	    = (+f line-position length-of-last-constituent 1)
	for new-line-p = (and (not first-p)
			      (>f next-line-position-if-on-this-line 80))
	for next-line-position = (if new-line-p 8 next-line-position-if-on-this-line)
	when new-line-p do (format t "~%       ")
	do (format t " ~a" string-for-last-constituent)
	   (reclaim-gensym-string string-for-last-constituent)))

(defun write-bnf-category (category-list)
  (case (car category-list)
    (token (format t "~s" (cadr category-list)))
    (non-token (format t "<~(~s~)>" (cadr category-list)))))

(defun write-transformation-for-bnf (transformation-list)
  (when (and include-transformations-in-bnf-printout?
	     (consp transformation-list)
    (loop initially (format t "~%        => ~s " (car transformation-list))
	  for transformation-operation in (cdr transformation-list)
	  do (format t "~%        -> ~(~a~) " transformation-operation)))))

(defun bnf-name-< (key1 key2)
  (cond ((and (symbolp key1) (symbolp key2))
	 (string< key1 key2))
	((and (fixnump key1) (fixnump key2))
	 (<f key1 key2))
	((fixnump key2)
	 nil)
	(t t)))

(defun write-bnf-category-index (bnf-index name)
  (format t "~5%     Index of ~a~%" name)
  (loop for (category-list def uses)
	    in (sort bnf-index
		     #'(lambda (entry-1 entry-2)
			 (bnf-name-< (cadar entry-1) (cadar entry-2))))
	do (format t "~%")
	   (write-bnf-category category-list)
	   (if def
	       (format t "  ~d  " def)
	       (format t "      "))
	   (format t "~{~d~^, ~}" uses))
  (reclaim-gensym-tree bnf-index))
)

#+development
(progn
  
;(collect-categories-for-clear-text)
(defparameter categories-for-clear-text
  '(attribute-designations attribute-designations-or-none character-set data-server-aliases
    display-expression element-type embedded-rule execution-interval? export-definition-language
    export-definition-specification expression extra-grid-line-specs foreign-function-declaration
    function-definition g2-user-mode-for-login? generic-formula generic-simulation-formula
    gfi-file-pathname gfi-interface-object gfi-output-values graph-background-colors
    gsi-host-configuration han-unification-mode horizontal-graph-ruling-parameter?
    horizontal-gridline-interval? icp-connection-specification initial-sensor-value? instance-formula
    integration-algorithm-specification interface-mode interval interval-for-retry interval?
    item-designations-for-model
    #+java-export-facilities
    java-class-body-declarations-or-none
    #+java-export-facilities
    java-compilation-unit-or-none
    keep-tabular-function-sorted? keyword-strings-or-none language-translation line-separator
    list-of-graph-expressions logical-instance-formula millisecond-sleep-interval
    minimum-scheduling-interval? non-default-number? nupec-extra-action-list patterns-definition
    procedure-definition procedure-name? proprietary-package remote-procedure-declaration
    #+res-g2-facilities
    resource-definition
    rule rule-frame-flags simulation-control-specification
    specific-simulation-formula? text-conversion-style-name? tokens-definition
    unconvertible-character-spec units-declaration user-menu-choice-expression
    vertical-graph-ruling-parameter? xsi-host-configuration))

(defparameter non-alphanumeric-char-names
  '((#\tab "tab")
    (#\space "sp")
    (#\! "ex")
    (#\" "dq")
    (#\# "no")
    (#\$ "dol")
    (#\% "pct")
    (#\& "and")
    (#\' "qu")
    (#\( "op")
    (#\) "cp")
    (#\* "star")
    (#\+ "plus")
    (#\, "cm")
    (#\- "_")
    (#\. "dot")
    (#\/ "sl")
    (#\: "col")
    (#\; "sc")
    (#\< "lt")
    (#\= "eq")
    (#\> "gt")
    (#\? "qm")
    (#\backspace "bp")
    (#\page "page")
    (#\@ "at")
    (#\[ "obt")
    (#\\ "bs")
    (#\] "cbt")
    (#\^ "ct")
    (#\_ "_")
    (#\return "rt")
    (#\newline "nl")
    (#\` "bq")
    (#\{ "ob")
    (#\| "or")
    (#\} "cb")
    (#\~ "tl")
    (#\rubout "ro")
    (#\linefeed "lf")))

(defmacro yacc-name-for-category (name token-p)
  `(getf ,name (if ,token-p 'yacc-token 'yacc-non-token)))

(defun get-yacc-name-for-category (name token-p)
  (when (wide-string-p name)
    (setq name (intern-text-string (tformat-text-string "WS-~A" name))))
  (cond ((fixnump name)
	 (intern (format nil "INTEGER_~D" name)))
	((yacc-name-for-category name token-p))
	(t
	 (setf (yacc-name-for-category name token-p)
	       (intern (with-output-to-string (*standard-output*)
			 (when (and token-p
				    (loop with pname = (symbol-name name)
					  for i from 0 below (length pname)
					  thereis (lower-case-p (char pname i))))
			   (write-string "JAVA_"))
			 (when (digit-char-p (char (symbol-name name) 0))
			   (write-string (if token-p "X" "x")))
			 (loop with pname = (symbol-name name)
			       for i from 0 below (length pname)
			       for char = (char pname i)
			       do (cond ((alpha-char-p char)
					 (write-char (if token-p char (char-downcase char))))
					((digit-char-p char)
					 (write-char char))
					((or (char= char #\-)
					     (char= char #\_))
					 (write-char #\_))
					(t
					 (let ((a (assoc char non-alphanumeric-char-names)))
					   (if a
					       (format t "_~a"
						       (if token-p
							   (string-upcase (cadr a))
							   (cadr a)))
					       (format t "~D" (char-code char)))))))))))))

(defparameter extra-token-categories-for-yacc
  (append
    required-token-types
    '(double-quote hyphen illegal-character string
      regexp-character

      package-code
      named-menu
      singular-unit-of-measure plural-unit-of-measure neutral-unit-of-measure
      system-attribute
      message-name
      method-declaration-name
      hex-integer
      documented-combobox
      control-extended-style-spec
      documented-listbox
      gesture-prototype-1 gesture-prototype-2
      java-character-literal java-symbol)))

(defun print-yacc-file-for-grammar (&optional (filename "grammar.yacc"))
  (with-open-file (#-ansi-cl lisp::*standard-output*
		   #+ansi-cl common-lisp::*standard-output* filename :direction :output)
    (let* ((grammar-as-list (collect-rewrite-rules-into-list))
	   (all-tokens
	     (sort (get-list-of-all-tokens grammar-as-list)
		   #'bnf-name-<))
	   (start-categories categories-for-clear-text)
	   (start-terminals
	     (loop for category in start-categories
		   collect (intern (format nil "START--~a" category))))
	   (extra-token-categories extra-token-categories-for-yacc)
	   (extra-token-terminals
	     (loop for category in extra-token-categories
		   collect (intern (format nil "TOKEN--~a" category))))
	   (regular-expression-terminals
	     (loop for (token character) in regular-expression-tokens
		   when (and character (not (consp character)))
		     collect (intern (with-output-to-string (*standard-output*)
				       (write-char (code-char (wide-character-code
								character))))))))
      (loop for token in all-tokens
	    do (format t "%TOKEN ~A" (get-yacc-name-for-category token t))
	       (when (and (symbolp token)
			  (loop with pname = (symbol-name token)
				for i from 0 below (length pname)
				for char = (char pname i)
				thereis (not (or (alpha-char-p char)
						 (digit-char-p char)
						 (char= char #\-)))))
		 (format t "   /* ~a */" (symbol-name token)))
	       (format t "~%"))
      (format t "%TOKEN ~a~%" (get-yacc-name-for-category 'regexp-character t))
      (loop for token in extra-token-terminals
	    do (format t "%TOKEN ~a~%" (get-yacc-name-for-category token t)))
      (loop for category in start-terminals
	    do (format t "%TOKEN ~a~%" (get-yacc-name-for-category category t)))
      (format t "~%%START ~a~%" (get-yacc-name-for-category '-start- nil))
      (format t "~%%%~%")
      (loop with print-parts-as-structures-p = nil
	    with grammar-as-list
	      = (nconc
		  (gensym-list
		    (gensym-cons
		      (gensym-list 'non-token '-start-)
		      (loop for category in start-categories
			    for terminal in start-terminals
			    collect (gensym-list
				      (gensym-list (gensym-list 'token terminal)
						   (gensym-list 'non-token category))
				      nil)
			      using gensym-cons)))
		  (loop for category in extra-token-categories
			for token in extra-token-terminals
			collect (gensym-cons
				  (gensym-list 'non-token category)
				  (gensym-list
				    (gensym-list
				      (gensym-list (gensym-list 'token token))
				      nil)))
			using gensym-cons)
		  (loop for (category character) in regular-expression-tokens
			for token in regular-expression-terminals
			when (and character (not (consp character)))
			  collect (gensym-cons
				    (gensym-list 'non-token category)
				    (gensym-list
				      (gensym-list
					(gensym-list (gensym-list 'token token))
					nil)))
			    using gensym-cons)
		  (collect-rewrite-rules-into-list))
	    for (category-list . rules) in grammar-as-list
		  do (unless (or (null rules)
				 (eq (cadr category-list) 'send-list))
		       (format t "~%")
		       (write-yacc-category category-list)
		       (format t " : ")
		       (loop for number-of-bnf-alternatives-so-far from 0
			     for (rhs transformation-list) in rules
			     do (when (>f number-of-bnf-alternatives-so-far 0)
				  (write-string " \|"))
				(format t "~%    ")
				(loop for category-list in rhs
				      do (write-yacc-category category-list)
					 (write-char #\space))
				#+ignore
				(write-transformation-for-yacc transformation-list))
		       (format t " ;~%"))
		  finally (reclaim-gensym-tree grammar-as-list)))))

(defun write-yacc-category (category-list)
  (write-string (string (get-yacc-name-for-category (cadr category-list)
						    (eq (car category-list) 'token)))))

)







;;;; Grammar/Parser Debugging Facilities



;;; DC (describe-category) ...

#+development
(defun dc (category-symbol-or-token)
  (let ((category-of-token?
	  (get-category-of-token category-symbol-or-token))
	(category-for-category-symbol?
	  (if (symbolp category-symbol-or-token)
	      (get-category-for-category-symbol-if-any
		category-symbol-or-token))))
    (if category-of-token?
	(describe category-of-token?))
    (if category-for-category-symbol?
	(describe category-for-category-symbol?))
    (if (and category-of-token? category-for-category-symbol?)
	(list category-of-token? category-for-category-symbol?)
	(or category-of-token?
	    category-for-category-symbol?))))



;;;; Measuring the Size of the Grammar


;; `Measure-compiled-structures-in-grammar" ... returns a list of the form
;; 
;;    ( be-or-begin-count
;;         ; the number of be-or-begin categories
;;      agenda-count-for-non-token-categories
;;         ; the number of agenda items
;;      empty-agenda-count-for-non-token-categories
;;         ; the number of null agenda slots
;;      agenda-cons-count-for-non-token-categories
;;         ; the number of conses used by agenda items
;;      agenda-count-for-token-categories
;;         ; the number of agenda items (for tokens)
;;      empty-agenda-count-for-token-categories
;;         ; the number of null agenda slots (for tokens)
;;      agenda-cons-count-for-token-categories
;;         ; the number of conses used by agenda items (for tokens)
;;      )

#+development
(defun measure-compiled-structures-in-grammar (grammar)
  (nconc
    (loop for category-symbol in (category-symbols grammar)
	  as category = (get-category-for-category-symbol-if-any category-symbol)
	  as categories-this-can-be-or-begin 
	     = (category-set-list
		 (if (eq (categories-this-can-be-or-begin category) 'not-a-result-category)
		     (category-set-empty)
		     (categories-this-can-be-or-begin category)))
	  when (consp categories-this-can-be-or-begin)
	    sum (length categories-this-can-be-or-begin)
	      into be-or-begin-count
	  sum (if (listp (agenda-of-more-general-categories-to-search category))
		  (length (agenda-of-more-general-categories-to-search category))
		  1)
	      into agenda-count
	  when (null (agenda-of-more-general-categories-to-search category))
	    count t into empty-agenda-count
	  when (not (atom (agenda-of-more-general-categories-to-search category)))
	    sum (loop for agenda-item
			  in (agenda-of-more-general-categories-to-search category)
		      sum (if (atom agenda-item) 1 2))
	      into agenda-cons-count
	  finally (return (list be-or-begin-count agenda-count
				empty-agenda-count agenda-cons-count)))
    (loop for token in (tokens-with-specific-categories current-grammar)
	  as category = (get-category-of-token token)
	  sum (if (listp (agenda-of-more-general-categories-to-search category))
		  (length (agenda-of-more-general-categories-to-search category))
		  1)
	    into agenda-count
	  when (null (agenda-of-more-general-categories-to-search category))
	    count t into empty-agenda-count
	  when (not (atom (agenda-of-more-general-categories-to-search category)))
	    sum (loop for agenda-item
			  in (agenda-of-more-general-categories-to-search category)
		      sum (if (atom agenda-item) 1 2))
	      into agenda-cons-count
	  finally
	    (return (list agenda-count empty-agenda-count agenda-cons-count)))))


;;                                       A    B    C   D    E     F   G
;;                                       ---- ---- --- ---- ----  --- ---
;; Before optimizations: 		(5512 4025   0 3726 1243  0   913)
;; After agenda optimization: 		(5512 1490 514 1394  443  334 340)
;; After be-or-begin optimization: 	(2185 1490 514 1394  443  334 340)
;; -----------------------------------------------------------------------
;; Percentage Reductions                   60   63       63   64       63
;;
;; A = Be-or-begin count
;; B = Total Agenda Items (categories)
;; C = Empty Agendas (categories)
;; D = Total Agenda Conses (categories)
;; E = Total Agenda Items (tokens)
;; F = Empty Agendas (tokens)
;; G = Total Agenda Conses (tokens)
;;
;; The table above shows the result of the two optimizations done today.
;; [Note: this information was tabulated after the enabling of left recursion
;; and after the generation of simple-list (without AND or OR) grammars was
;; changed to take advantage of left-recursion, but before the generation
;; of lists with conjunctions (with AND/OR) used left-recursion, and before
;; any hand-written grammar used left-recursion.]
;; (MHD 3/31/93)








;;;; Grammar Rule Generators



;;; This section contains functions that add grammar rules to the global
;;; grammar from high-level specifications.  By convention, the names for
;;; these functions begin with "add-grammar-rules-for-".



;;; `Add-grammar-rules-for-list' adds grammar rules (via add-grammar-rules)
;;; for English-like lists. Conjunction?, if non-nil, may be either of the
;;; symbols AND or OR.  If nil, a simple comma series grammar is generated.
;;; Separator? may be either of the symbols \, or \;.  It defaults to \,.
;;; If empty-list-symbol? is non-nil, it specifies the symbol used in
;;; the empty-list grammar rule.  If empty-list-symbol? is nil, no
;;; empty-list grammar rule is created.

;;; When list-category-symbol is parsed, it is translated into a list of
;;; the form
;;;
;;;    (<separator> . list)
;;;
;;; If empty-list-symbol? is non-nil, then it is simply parsed into nil.
;;; Note that empty-list-symbol? usually should be made a reserved word.

;;; Example:
;;;
;;;   (add-grammar-rules-for-list 'choices 'choice '/, 'and 'nothing)
;;;
;;; Assuming a choice is a symbol, this would parse sentences such as the
;;; following:
;;;
;;;   nothing
;;;   a
;;;   foo, bar, and baz
;;;   a and b
;;
;;; which would result in the following parses, respectively:
;;; 
;;;   nil
;;;   (\, a)
;;;   (\, foo bar baz)
;;;   (\, a b)
;;;
;;; Example:
;;;
;;;  (add-grammar-rules-for-list 'alt 'alternatives 'or 'or nil)
;;;
;;; allows
;;;
;;;  <alt>
;;;  <alt> or <alt>
;;;  <alt> or <alt> or <alt>
;;;
;;; Etcetera.

;; jh, 7/18/94.  Enhanced add-grammar-rules-for-list so it can refrain from
;; calling simplify-associative-operation.  See my note this date below
;; def-simplifying-slot-value-compiler in GRAMMAR4A for further details.

(defun add-grammar-rules-for-list
       (list-category-symbol symbol-category-symbol
	&optional (separator? nil)
	          (conjunction? nil)
		  (empty-list-symbol? nil)
		  (simplify-piecemeal-p t))
  (let ((separator (or separator? '\,))
	(simplify-splice-form
	  (if simplify-piecemeal-p
	      `(simplify-associative-operation)
	      nil)))
    (cond
      ((null conjunction?)
       ;; Simple comma series:
       (let ((tail-symbol (format-symbol "~a-TAIL" list-category-symbol)))
	 (add-grammar-rules
	   `((,list-category-symbol ,tail-symbol)
	     (,tail-symbol ,symbol-category-symbol (,separator 1))
	     (,tail-symbol
		(,tail-symbol ',separator ,symbol-category-symbol)
		(,separator 1 3) ,@simplify-splice-form)
	     ,@(when empty-list-symbol?
		 `((,list-category-symbol
		      ',empty-list-symbol? nil nil-function)))))))      
      (t
       ;; CONVERT TO LEFT RECURSION!  (MHD 3/27/93)
       ;; AND/OR series:
       (let ((list-category-symbol-1
	       (format-symbol "~a-1" list-category-symbol))
	     (tail-symbol (format-symbol "~a-TAIL" list-category-symbol)))
       (add-grammar-rules
	 `((,list-category-symbol ,tail-symbol)
	   (,tail-symbol ,symbol-category-symbol (,separator 1))
	   (,tail-symbol
	    (,symbol-category-symbol ',conjunction? ,symbol-category-symbol)
	    (,separator 1 3))
	   ,@(if (eq separator conjunction?) ; e.g., OR is both separator and conjunction
		 `((,tail-symbol
		      (,list-category-symbol-1 ',conjunction? ,symbol-category-symbol)
		      (2 1 3) ,@simplify-splice-form))
		 `((,tail-symbol
		      (,list-category-symbol-1 ',separator ',conjunction? ,symbol-category-symbol)
		      (2 1 4) ,@simplify-splice-form)))
	   (,list-category-symbol-1
	      (,list-category-symbol-1 ',separator ,symbol-category-symbol )
	      (2 1 3) ,@simplify-splice-form)
	   (,list-category-symbol-1
	      (,symbol-category-symbol ',separator ,symbol-category-symbol)
	      (2 1 3) ,@simplify-splice-form)

	   ,@(when empty-list-symbol?
	       `((,list-category-symbol ',empty-list-symbol?
		  nil nil-function))))))))))




;;; `Remove-noise-at-head-of-list-phrase' is a transformation function
;;; convenient for cleaning up a list phrase that typically has certain "noise
;;; words" at its head.  This function performs the following action: if
;;; list-phrase is a cons whose car is one of the following symbols:
;;;
;;;   AND  OR  \,  \;  \:
;;;
;;; the cdr of list-phrase is returned. Otherwise, list-phrase itself is
;;; returned.

(defconstant list-phrase-noise-symbols '(and or \, \; \:))

(defun remove-noise-at-head-of-list-phrase (list-phrase)
  (cond
    ((and (consp list-phrase)		; nec.?
	  (memq (car list-phrase) list-phrase-noise-symbols))
     (cdr list-phrase))
    (t list-phrase)))



;;; `Add-words-as-instances-of-category' adds each symbol in symbols to
;;; be an instance of category.

;(defun add-words-as-instances-of-category (category symbols)
;  (add-grammar-rules
;    (loop for symbol in symbols
;	  collect `(,category ',symbol))))

;; Macro so that it does its consing while compiling, rather than loading.

(defmacro add-words-as-instances-of-category (category symbols)
  `(add-grammar-rules ',(loop for symbol in symbols
			       collect `(,category ',symbol))))



;;; `Reserve-words-as-instances-of-category' defines each symbol in the list of symbols to
;;; be an instance of category, and makes each symbol a reserved word.
;;; Written by M.L. 2/27/87

;(defun reserve-words-as-instances-of-category (category symbols)
;  (add-grammar-rules
;    (loop for symbol in symbols
;	  collect`(,category ',symbol)))
;  (reserve-words symbols))

;; The definition below was entered sometime around 8/2/89, but the function
;; definition of old above was not commented out.  I've commented out the
;; function above.  -jra 8/6/89

(defmacro reserve-words-as-instances-of-category (category symbols)
  `(progn  
     (reserve-words ',symbols)

     (add-grammar-rules ',(loop for symbol in symbols
				collect `(,category ',symbol)))))





;;;; Grammar Rule/Compiler Combinations

;; Expand this section!



;;; Slot-value-compilers for constant-designation and constant-datum lists.

(defun-void simplify-associative-list-operation-all-at-once (parse-result)
  (when (cdr parse-result)
    (loop for enclosing-operand = parse-result then first-operand
	  with new-tail = nil
	  for first-operand = (second enclosing-operand)
	  for second-operand? = (third enclosing-operand)
	  while second-operand?
	  do (phrase-push second-operand? new-tail)
	     (unless (and (consp first-operand) (eq (car first-operand) '\,))
	       (loop-finish))
	  finally
	    (phrase-push first-operand new-tail)
	    ;; The abandoned conses in the cdr of parse-result are
	    ;; phrase-conses and will be cleaned up by the editor.
	    (setf (cdr parse-result) new-tail))))

(defmacro def-simplifying-slot-value-compiler
    (name (parse-result-var &rest rest-of-arglist) &body body)
  `(def-slot-value-compiler ,name (,parse-result-var ,@rest-of-arglist)
     (simplify-associative-list-operation-all-at-once ,parse-result-var)
     ,@body))

;; jh, 7/18/94.  Modified the slot compilers for the initial-values attribute of
;; g2-arrays to simplify their associative operations all at once.  This may be
;; a fix for BUG-001-6029, in which the initial-values slot of a g2-array has
;; quadratic consing behavior since simplify-associative-operation is called for
;; each operation.  Although not a final fix, this should ease some of the
;; pressure from end-users who use the initial-values attribute to store
;; g2-array values acquired while G2 was running.  Gated this fix with
;; g2-array-initial-values-simplifies-piecemeal-p (defaulting to the old
;; behavior) until I can test in a distribution image.
;; jh, 7/20/94.  Fix works in distribution.  Removed gating defvar
;; g2-array-initial-values-simplifies-piecemeal-p.





;;;; Semi-open-categories



;;; A `semi-open category' is a grammar category which is open in that it is
;;; rewritten into the category 'unreserved-symbol, but in actual use is closed
;;; by means of rejecting functions in the grammar rules in which it occurs.
;;; This facility consists of a set of definitions, and a predicate to control
;;; rejection and acceptance of categories. 

;;; Semi-open categories are used both to disambiguate the parsing, and to
;;; control the size of menus.

;;; An example of the use of semi-open categories is the parsing of a
;;; designation after a quantifier (the, any, every). Depending on the context,
;;; "the foo", "any foo", and "every foo" may be valid where "foo" is a user
;;; defined attribute or class name. However, "any item-color" and "every item
;;; color" are never valid, and "the item-color", while valid, gets transformed
;;; into a different form than would an attribute or class name.

;;; Symbols in the list symbols-not-to-add-to-semi-open-category-directories
;;; are not added to directories, but otherwise behave as described below. The
;;; purpose of this feature is to allow old grammar to parse, but not get menu
;;; prompts for these symbols.

(defvar semi-open-category-map nil)



;;; The macro `def-semi-open-category' defines a semi-open-category. (1) It
;;; creates a grammar rule rewritting the given category into
;;; 'unreserved-symbol. (2) It creates a directory for the instances of the
;;; category at the start of a kb.
;;;  Options: :base-category     -- Superior grammer cagegory for this. Defaults to unreserved-symbol.
;;;           :string-to-display -- function on (symbol) which returns the text-string to display
;;;                                 in the token menu for this category
;;;           :string-to-insert  -- function on (symbol) which returns the text-string to insert
;;;                                 into the editor when the symbol is selected in a token menu.

(defmacro def-semi-open-category (category-and-options
				   &body list-of-semi-open-category-instances)
  (let* ((category
	   (car-or-atom category-and-options))
	 (options
	   (cdr-or-atom category-and-options))
	 (base-category
	   (getf options :base-category 'unreserved-symbol))
	 (string-to-display-function?
	   (getf options :string-to-display))
	 (string-to-insert-function?
	   (getf options :string-to-insert))
	 (instances
	   (loop for element in list-of-semi-open-category-instances
		 if (consp element)
		   append element
		 else collect element)))
    `(def-semi-open-category-1
	 ',category
	 ',instances
       ',base-category 
       ,string-to-display-function?
       ,string-to-insert-function?)))

;; Note that if there were a function directory-member-p, then the use of lists
;; of categories could be avoided. On the other hand, these lists are small,
;; and this lookup is fast.  (ML) -- There is such a function (in-directory-of-
;; names-p), but you still need the lists in order to be able to set up the
;; directories each time a new KB is created. (MHD 6/4/90)



(defun def-semi-open-category-1
    (category instances
	      &optional (base-category 'unreserved-symbol)
	      string-to-display-function?
	      string-to-insert-function?)
  (add-grammar-rule `(,category ,base-category))
  (setq semi-open-category-map
	(remove category semi-open-category-map :key #'car))
  (push `(,category  ,@instances) semi-open-category-map)

  (when string-to-display-function?
    (set-token-menu-string-to-display-function category string-to-display-function?))
  (when string-to-insert-function?
    (set-token-menu-string-to-insert-function category string-to-insert-function?))
  category)







;;; `Semi-open-category-p' ...

;;; (semi-open-category-p symbol-or-name-denotation &optional category-or-categories?)
;;; 
;;; is true if the symbol, or the unqualified name, in the name-denotation case,
;;; is in the given category, or is in any of the given categories of the list,
;;; or is in any semi-open-category when the optional argument is missing or
;;; nil.
;;;
;;; Note that in practice the data type symbol and the (abstract) datatype
;;; name-denotation are not distinguishable; this should not pose any problems,
;;; however.

;; This uses in-directory-of-names-p whereas it could more efficiently
;; use (memq symbol (cdr (assq category semi-open-category-map))) because
;; that would be more desirable from the point of view of some day saving space
;; by not keeping instances in semi-open-category-map and from the point of
;; view some day allowing user-defined instances (e.g. user-defined color
;; names).  (MHD 6/4/90)

;; The following introduced a bug in that item-x-position and its ilk were not
;; recognized as belonging to their category because they were not put into the
;; directory of names. Recoded below: ML 5/30/91

(defun semi-open-category-p
    (symbol-or-name-denotation &optional category-or-categories?)
  (let ((symbol
	  ;; This is assumes the current representations behind the name
	  ;; denotation abstraction only because name-denotation-p and
	  ;; unqualified-name are macros defined in a later module, so using
	  ;; them would currently create forward referencing problems.  It
	  ;; would be nice to clean this up! (MHD 12/6/94)
	  (if (consp symbol-or-name-denotation)
	      (third symbol-or-name-denotation)
	      symbol-or-name-denotation)))
    (cond
      ((null category-or-categories?)
       (loop for (nil . symbols) in semi-open-category-map
	     thereis (memq symbol symbols)))
      ;; This is ugly but necessary!!  (See note below.)  -ML
      ((and (eq symbol 'remote-process-initialization-string)
	    (eq category-or-categories? 'system-attribute))
       nil)
      ((symbolp category-or-categories?)
       (memq symbol (cdr (assq category-or-categories? semi-open-category-map))))

      (t (loop for category in category-or-categories?
	       thereis
	       (memq symbol (cdr (assq category semi-open-category-map))))))))

;; Added a special case to the function semi-open-category-p which
;; conceals the change action on the
;; remote-process-initialization-string of a GSI interface.  This is not
;; an advertized feature because it is unclear what should happen if a
;; remote-process-initialization-string is changed while G2 is running.
;; (ml & jh, 8/15/90)

;; jh, 11/4/96.  It has long been OK to change the
;; remote-process-initialization-string while G2 is running.  Changing the
;; clause in question to return nil instead of t, and inviting the parser gurus
;; to clean up further by removing it entirely.

;;; `Add-semi-open-categories-to-directories' ...

(defvar symbols-not-to-add-to-semi-open-category-directories nil)

(defun add-semi-open-categories-to-directories ()
  (loop for (category . instances) in semi-open-category-map
	do (loop for instance in instances
		 unless
		   (memq instance
			 symbols-not-to-add-to-semi-open-category-directories)
		   do (add-to-directory-of-names instance category))))

;; Called from switch-to-new-empty-kb.




;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module FILTERS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Ben Hyde, Fred White, Michael Levin, Paul B. Konigsberg and Mark David






;;;; An Introduction to FILTERS



;;; The module FILTERS supports the configuration of the user interface and KB
;;; specific security.  It does this with two abstractions: user restrictions and
;;; user modes.  User modes provide a per-G2-window setting of how the user
;;; interface should behave.  User restrictions provide a way to markup blocks in
;;; the KB stating how they should behave in a particular user mode.

;;; User restrictions allow the KB developer to configure how the UI appears (both
;;; what menus choices appear in menus and what slots appear in attribute tables),
;;; and how it behaves (what menu choices are legal, what keystrokes equivalents
;;; are enabled, and what happens on selecting an object).

;;; For conciseness a single user restriction can effect a number of items by using
;;; inheritance in the KB hierarchy (not the class hierarchy).  Activation and
;;; KB save also utilize the KB hierarchy, which may be partially visualized using
;;; the "show on a workspace the workspace hierarchy" command.

;;; In addition to configuring the user interface, user restrictions also play a
;;; role KB security.  They configure what set of operations is legal in each mode.

;;; Historically the kinds of users being restricted has evolved to include
;;; three different kinds:
;;;  - plant operators
;;;    (i.e.  users that access G2-window but are constrained to a particular set of user modes), 
;;;  - users of proprietary KB
;;;    (i.e.  buyer's of proprietary KB that access those KB using all tools available in 
;;;     ADMINISTRATOR mode).
;;;  - network processes
;;;    (i.e. users that access the KB over the network), and 
;;; Currently the restriction of network users (1/1/92) is not finished and the
;;; restriction of proprietary users is incomplete (1/1/92).

;;; There are other mechanisms that implement security: user login, text stripping,
;;; authorization of G2 and G2 modules, etc.

;;; When performing any workstation interaction while the user is logged in,
;;; the user-mode (a symbol) is bound to the value of the variable current-g2-
;;; user-mode?.  If the workstation is not logged in, the workstation's
;;; workstation-login-state slot will not be LOGGED-IN, and the value for
;;; current-g2-user-mode? is nil.  Logging in and the facilities for
;;; establishing users and their privileges are discussed separately in
;;; modules INT and SEQUENCES2.

;;; People often assume user restriction can do things they can't.  There are a
;;; number of common ideas about how to extend the current implementation of user
;;; restrictions, these ideas are not currently implemented.
;;;  - Increase how appearance of the KB can be controlled;
;;;    - restricted objects are not drawn differently, for example hidden,
;;;    - restrictions are not used to configure the appearance of color, workspaces, etc. and,
;;;    - they are used to configure attribute tables and menus.
;;;  - Increase the efficency of checking restrictions by caching and propogating infomation, i.e.
;;;    - use frame flags to speed queries, 
;;;    - this was in the plan for network security restrictions.
;;;  - Extend hierarchy used into the class hierarchy,
;;;    - this would be a big help in packages,
;;;    - it would allow proprietary packages to hide knowledge stored in attributes,
;;  Done.
;;;  - Provide absolute restrictions,
;;;    - it is currently possible to restrict an operation at one point the hierarchy
;;;      and then have users reenable it at a lower point in the hierarchy
;;;      ( when in operator mode menu choices exclude absolutely: edit )
;;  Done.

;;; It often surprises people that restricting one operation does not restrict
;;; another operation.  For example if you write "table menu choices for any
;;; item exclude: edit" you can still edit the text representation of a menu
;;; that appears in a workspace.  There are a very large number of examples like
;;; this.

;; ben 12/31/91






;;;; Intermodule References in FILTERS

;;; Filters exports a number of routines used in RUN, MENUS, TABLES, QUERIES and
;;; FACILITIES.  It depends on the FRAME system, and PARSE.  It imports
;;; superior-frame from ACTIVATE.

;; FILTERS should probably appear just after FRAMES in load order.  After all, it is the
;; module that implements configuring and securing frames and slots.  Currently almost all
;; it's customers are forward referencing it. - ben 1/02/92

(declare-forward-reference superior-frame function)               	; in ACTIVATE


(declare-forward-reference funcall-function-to-inferior-blocks function)		; TRANFERSALS

(declare-forward-reference add-check-boxes-to-current-dialog function)
(declare-forward-reference remove-dialog-info-from-ui-client-interface-dialog-list function) ;VIEW-G2
(declare-forward-reference selection-enabled-p function) ; COMMANDS0




;;; Permission functions have values which may have filter conses. These
;;; should be reclaimed by the caller. Most of them return two values: a list 
;;; of menu choices, for example, and either true if those choices are permitted
;;; or nil if those choices are not permitted.

(defconser filter)

(defun reclaim-filter-list-function (list)
  (reclaim-filter-list-macro list))

(defun reclaim-filter-tree-function (list)
  (reclaim-filter-tree list))

;; Needed in MENUS

(defun filter-cons-function (car cdr)
  (filter-cons car cdr))

;; Needed in DEFINITIONS.

(defun filter-copy (thing)
  (if (consp thing)
      (copy-tree-using-filter-conses thing)
      thing))




;;;; User Modes: Variations, Grammar, Compilers, and Writers

;;; User modes are symbols.  They appear in g2-windows, user restrictions, the
;;; default mode for the KB in kb-user-restrictions system table,
;;; permitted-user-modes in authorized-user frames, the authorized-users-list and
;;; in the current binding of current-g2-user-mode?.  

;;; In the slots, variables, and expressions where user mode appears there may
;;; appear three unique values.

;;; ADMINISTRATOR is the built-in user mode in which the user can not restrict any
;;; operations (except those restriction applicable to proprietary objects).  In
;;; administrator mode the user interface reverts to the "default" configutation.
;;; It is not legal to restrict this user mode, i.e. is not possible to write
;;; restrictions of the form "when in administrator mode ...".
;; Wouldn't "unless in foo mode ..." restrict admintrator mode?

;;; PROPRIETARY restrictions apply to any object marked as being proprietary.  It is
;;; used to implement the securing of knowledge in KB packages from purchasers of those
;;; packages.  It is not legal to put a G2-window into proprietary mode.  It is not
;;; possible to write restrictions of the form "unless in proprietary mode ...".

;;; NIL is the top level binding of the global current-g2-user-mode? and that can
;;; used to sense that the current operation is not taking place relative to a particular
;;; window.  Some interuptable operations must carry in their micro task the user mode of 
;;; the g2-window that spawned them.  Some operations rebind current-g2-user-mode to
;;; enable queries to be made of the user restrictions.  It usually is not appropriate to
;;; query user restrictions with NIL as the current g2 user mode.

;;; There is a directory of all known user modes.  Entries appear there for
;;; each and every user mode that appears in any user restriction.

(def-concept user-mode)



;;; `Validate-as-possible-user-mode' abstracts out the constraints on the choice
;;; of symbol so they can be used when coming in via paths that don't involve
;;; the classic 'enter a datum using the editor' context. In particular the
;;; check for it being a symbol is included, which in classic is handled by the
;;; grammar for the g2-user-mode-for-login category.
;;;
;;; To make the use of this predicate relatively self-contained given that it
;;; is deployed in situations where error messages are going to be issued,
;;; the error messages are included here and we use the special return signature
;;; that is common to category evaluators and the login procedure and such:
;;; This returns nil if the mode is a possible one, otherwise it returns a
;;; symbol designating the error. The localized text for this symbol can
;;; be gotten by passing it to `string-for-localized-symbol'. The set of
;;; these error symbols can be found by grepping on `login-errors'.

(defun-simple validate-as-possible-user-mode (user-mode)
  (or (when (not (symbolp user-mode))
	'user-mode-is-not-a-symbol)
      (when (null user-mode)  ; note
	'user-mode-may-not-be-nil)
      (when (eq user-mode '||)
	'user-mode-may-not-be-an-empty-string)
      (when (eq user-mode 'proprietary)
	'cannot-enter-proprietary-mode)))

;; Note:  If we were sure we would only be coming in from the classic editor and its
;; tokenizer then there is no need to check for the value being nil, since if
;; the tokenizer sees that string it returns the nil symbol from the keyword
;; package so there is no conflict. However with the advent of T2 and new paths
;; to this there is no harm in being paranoid.



(def-grammar-category g2-user-mode ()
  (g2-user-mode-for-login))


(def-grammar-category g2-user-mode-for-login ()
  (non-built-in-g2-user-mode)
  administrator)


;;; N.b. `non-built-in-g2-user-mode' this is the category for the
;;; directory of names. See add-or-delete-mode-name-from-directory-of-names.

(def-grammar-category non-built-in-g2-user-mode ()
  (symbol))


;;; The "?" variant on this category is used in just one place (as of 6/6/98),
;;; the initial-g2-user-mode-for-this-kb slot of the kb-configuration
;;; system frame. KBs, unlike users, can not have an initial (default)
;;; mode. Other than the provision for "none" this category is identical
;;; to its unquestioned cousin.

(def-grammar-category g2-user-mode-for-login? ()
  (g2-user-mode-for-login)
  none)



(def-slot-value-writer-as-existing-function g2-user-mode
    write-symbol-from-slot)

(def-slot-value-writer-as-existing-function g2-user-mode-for-login
    write-symbol-from-slot)

(def-slot-value-writer-as-existing-function g2-user-mode-for-login?
    write-symbol-from-slot)


;;; All changes to a user's mode except for the initial value it gets
;;; at login are funneled through `g2-user-mode-for-login'. (The initial
;;; value is handled by log-in-workstation and log-in-ui-client depending
;;; on whether the user in coming in via TW or T2.) This category is
;;; the type for user-mode slots in all the classes that have them so
;;; it gets the direct changes to the slot that the user may do by hand
;;; or programmatically using conclude.
;;;
;;; Its subroutines are shared by the two log-in routines. The validity
;;; checking routines are germane to secure G2s only and reside the
;;; sequences2. The final call to `update-user-mode-state' is what arranges
;;; for all the side-effects of changing user-mode. It resides in run along
;;; with the other such code that is used by log-in-workstation.
;;;
;;; There are two other places that need this functionality that aren't
;;; easily mediatated by the category, so to make life easy, the guts of
;;; this slot compiler have been pulled out as a separate function.
;;; These are the virtual attribute ui-client-interface and the system
;;; procedure/RPC g2-change-mode-for-window.

(def-slot-value-compiler g2-user-mode-for-login (parsed-user-mode frame)
  (check-and-install-new-g2-user-mode-for-login parsed-user-mode frame))

(defun check-and-install-new-g2-user-mode-for-login (parsed-user-mode frame)
  (macrolet ((get-user-name (frame)
	       `(frame-class-case frame
		  (g2-login
		    (get-slot-value ,frame 'g2-login-user-name?))
		  (ui-client-session
		    (get-slot-value ,frame 'ui-client-session-user-name))
		  (g2-window
		    (get-slot-value ,frame 'g2-user-name))
		  (t #+development
		     (error "We are unexpectedly looking at the frame ~A ~
                             and don't know where to look for a user-name ~
                             on it. We can't plausibly continue from here."
			    ,frame)
		     (stack-error cached-top-of-stack "Attempting to change the user-mode on an item for which that is not defined: ~NF" ,frame)))))
    
    (let ((trouble? nil))

      ;; is it something that can be a mode?
      (setq trouble?
	    (validate-as-possible-user-mode parsed-user-mode))

      ;; Check that this is a valid mode for the user if G2 is secure.
      (unless trouble?
	(setq trouble?
	      (validate-user-mode-for-user
		(get-user-name frame) parsed-user-mode)))

      (unless trouble?
	;; Side-effect the login state.
	(update-user-mode-state frame parsed-user-mode))

      (cond (trouble?
	     (when (symbolp trouble?)
	       ;; n.b. in many routines, especially those involved with
	       ;; logging in, the currency for naming errors is symbols
	       ;; rather than strings.
	       (setq trouble? (string-for-localized-symbol trouble?)))
	     (values bad-phrase
		     trouble?))
	    (t
	     parsed-user-mode)))))

;; TO DO: Do not allow adding optional subtable on a g2-window instance's
;; user-mode slot!!! (MHD 4/23/92)


(def-slot-value-compiler g2-user-mode-for-login? (parse-result)
  (if (eq parse-result 'proprietary)
      (values
	bad-phrase
	(copy-constant-wide-string #w"You cannot enter PROPRIETARY mode."))
      (if (eq parse-result 'none)
	  nil
	  parse-result)))


		      
(define-category-evaluator-interface (g2-user-mode-for-login
				       :access read-write)
    symbol
  ((get-form (slot-value))
   slot-value)
  ((set-form (evaluation-value))
   (evaluation-symbol-symbol evaluation-value)))

(define-category-evaluator-interface (g2-user-mode-for-login?
				       :access read)
    (or (no-item)
	symbol)
  ((get-form (slot-value))
   slot-value))

;; This "?" variant did not have a setter to begin with, and given that
;; it represents a fixed property of a KB I don't see that we should
;; give it one just because we have now provided a setter for the
;; user-based notion of a login mode. ddm 6/9/98




;;;; User Restrictions




;;; User restrictions consist of statements.  These statements appear in items
;;; and in the KB-CONFIGURATION system table.  The statements are compiled into
;;; an internal form analagous to their syntax.  The resulting information
;;; is then queried prior to performing all user interface operations and some
;;; evaluator operations.  These queries search the KB hierarchy to compute their
;;; results, they may appear on all blocks.  They are a lookup slot.

;;; The root of this hierarchy is found in the user restrictions slot of the
;;; system table kb-user-restrictions.  That table also contains some slots for
;;; handling two special cases: configuring the main menu, 
;;; and configuring keystrokes.

;;; There are some distinctions between what you can do with the
;;; main-menu-user-restrictions and what is possible via vanilla user-restrictions.

;;; There are some special cases around the pseudo user modes ADMINISTRATOR and
;;; PROPRIETARY.

;;; User restriction statements bind a number of particulars about the behavior
;;; of the user interface, these include:
;;;  1. KB Hierarchy:
;;;     each restriction resides in some item and effects the behavior of that 
;;;     item and the items below it in the hierarchy,
;;;  2. User Mode:
;;;     each restriction statement is specified as applying to a set of modes
;;;     this set maybe specified enumerating the modes included or excluded from
;;;     the set,
;;;  3. Class Affected:
;;;     each restriction enumerates the set of classes it effects,
;;;  4. Slots Affected
;;;     a restriction may apply only to particular slots of a class, for example
;;;     disabling the visibility or editting of a slot.
;;;  5. Enable/Disable:
;;;     each restriction enables or disables some behavior,
;;;  6. Incremental/Definitive Restriction:
;;;     each restriction may incrementally modify the behavior or absolutely specify
;;;     the behavior of the items it effects.
;;;  7. Operation:
;;;     each restriction enumerates the operation or operations it effects.

;;; The form stored in the user restrictions slot is created by the usual parsing and
;;; compiling (except for initial value of the user restrictions on the kb-configuration
;;; system table).  The user restrictions are then accessed by:
;;;   - the slot writer,
;;;   - the describe restrictions code,
;;;   - the code that maintains the directory of all user modes, and
;;;   - the large body of code that checks user restrictions called out of the user interface.

;;; The following provides a sketch of the forms used to store user restrictions.
;;; The notation below is analagous to a grammar, but instead of text we are documenting S-Expressions.
;;;   Quote is used to indicate a literal.
;;;   Plus is used to indicate one or more occurances.
;;;   Star is used to indicate zero or more occurances.
;;;   Parenthesis are used to indicate list structures.
;;;   Vertical bar is used to indicate alternatives.
;;;   Double dash is used to begin a comment.
;;;   -Note-N- indicates a catagory explained with a near by note.

;;; The user restrictions are always stored as a list with nil indicative that the user has not entered
;;; any restrictions into that slot.  Each element of the list begins with mode-pattern followed by a
;;; list of individual restrictions.  The mode pattern indicates which modes this restriction applies to.

;;;  user-restrictions:
;;;    ( user-restriction* ) -- these are in reverse order of text order so search will proceed bottom to top.
;;;  user-restriction:
;;;     ( mode-pattern restriction+ )
;;;  mode-pattern :
;;;    'when ( mode+ )     -- when mode may not include administrator
;;;    'unless ( mode+ )   -- unless mode may not include proprietary

;;; Each individual restriction contains as many as five fields.
;;;   - what group of operation this applies to.
;;;   - what class or classes of objects it applies to.
;;;   - which slots of those objects it applies to.
;;;   - how this restriction is mixed in with other restrictions
;;;   - what operations are restricted

;;;  restriction:
;;;     menu-clause
;;;     non-menu-clause
;;;     slot-visibility-clause
;;;     selection-clause
;;;     table-menu-clause

;;;  menu-clause:            
;;;        ('workspace-menu (class-2+)                   restriction-type menu-choice*)
;;;  non-menu-clause:
;;;        ('non-menu       (class-1+)                   restriction-type non-menu-choice*)
;;;  slot-visibility-clause:
;;;        ('visibility      (class-1+) (attribute-name*) restriction-type)
;;;  selection-clause:
;;;        ('selecting      (class-2+)                                    selectable-choice-1)
;;;        ('selecting-absolutely (class-2+)                              selectable-choice-1 )
;;;  table-menu-clause:
;;;        ('table          (class-1+) (attribute-name*) restriction-type table-menu-choice* )
;;;  global-keyboard-command:
;;;        ('global-keyboard-command                     restriction-type global-keyboard-command-choice+)

;;; When the additionally restriction-type is used there will be one or more menu-choices.

;;; The system table attribute main-menu-user-restrictions contains only menu-clause
;;; restrictions and the menu-choices are limited to those found in the main-menu.  
;;; Other restriction slots never contain main menu choices.

;;; The system table global-keyboard-command-user-restrictions is the only place where
;;; global-keyboard-command restrictions are found, and it contains only those.

;;; Two curious things are done with the class.

;;;  class: -note-1-
;;;  class-1:    class   | 'name-box
;;;  class-2:    class-1 | 'workspace

;;; -note-1- Class is the usual set of item class names.
;;; The pseudo class name-box is introduced to allow the user to restrict operations on
;;; the name box.  The pseudo class workspace is introduced to provides a way to restrict
;;; any workspace not just the workspaces that users create.

;; Ben, why call NAME-BOX and WORKSPACE "pseudo" classes?  They're non-item classes, but
;; they are fully classes.  On the other hand, DISPLAY is really not a class.  In the
;; past, we've called this a "pseudoclass".  (MHD 2/11/92)


;;;  attribute-name: -note-2-

;;; For those restrictions that accept a slot name an empty slot name implies
;;; that the restriction applies to all slots.  

;;; -note-2- Attribute name is the name of an attribute in the user's model.  It
;;; maybe need to be unaliased to get the internal slot name that is being
;;; restricted.

;;; The restriction type provides a rudimentary way to configure menus and attribute
;;; tables.  It is not possible to configure the ordering of entries in menus or
;;; attribute tables.  When G2 is configuring a menu/table it will search
;;; the user restrictions accumulating the choices implied by the include/exclude
;;; additionally statements stopping when it reaches a definitive include/exclude
;;; statement.  Once it has obtained a definitive statement it then checks the
;;; remaining hierarchy for absolute restrictions, any such restrictions are
;;; then removed from the set of results returned.

;;;  restriction-type:
;;;      'include               -- definitive
;;;      'exclude               -- definitive
;;;      'include-additionally  -- incremental
;;;      'exclude-additionally  -- incremental
;;;      'exclude-absolutely    -- securing

;;; The last entry in the restriction is a list of operations (aka choices) this
;;; restriction applies to.  The user can extend this list by writing user-menu-choices.
;;; Some of these choices never appear in the menus and are known as "non-menu-choices."
;;; In a sense choices are the full set of operations available to a G2 user via the
;;; user interface.  (With the exception that there is no mechnism for restricting
;;; individual inspect commands).

;;; The menu choices are broken into groups according to the menu, in the default UI, that
;;; they appear in.  This somewhat arbitrary grouping is then used to prompt the user with
;;; menu names in the editor.  The grammar of the slots helps the user to avoid entering a
;;; few of the choices that make no sense.

;;;  menu-choice: item-menu-choice | main-menu-choice | workspace-menu-choice

;;;  item-menu-choice:      -note-3- | user-menu-choice
;;;  main-menu-choice:      -note-3-
;;;  workspace-menu-choice: -note-3-
;;;  table-menu-choice:     -note-3-
;;;  global-keyboard-command-choice: -note-4-
;;; -Note-3- The grammar catagories holding the menu choices are setup by def-menu.
;;; -Note-4- The grammar catagory holdingthe keyboard command choices are setup by def-event-interpeter.

;;;  non-menu-choice:
;;;    'move-object
;;;    'move-objects-beyond-workspace-margin
;;;    'move-connection
;;;    'move-workspace
;;;    'move-workspaces-beyond-window-margin
;;;    'show-workspace
;;;    'scale-workspace
;;;    'click-to-edit
;;;    'full-editor  ; otherwise => edit-in-place, & the following apply
;;;    'option-buttons-for-edit-in-place
;;;    'menus-for-edit-in-place
;;;    'do-not-clear-text-for-edit-in-place
;; 1st try:
;;    'edit-option-buttons-for-edit-in-place
;;    'blank-for-type-in-for-edit-in-place
;;    'edit-menus-for-edit-in-place

;;;  selectable-choice: item-menu-choice | workspace-menu-choice

;;; Selectable choices are commands that the user can invoke when an item is clicked.
;;; Selectable choices may be attempted on any item.

;;;  selectable-choice-1: selectable-choice | 'nothing

;;; I don't understand the implementation of the pseudo choices NONE and NOTHING.

;;; The actual implementation may vary.

;; - ben 12/30/91

;; Need a mapping function (both ways) between symbolic names and word lists.

;; Why is "nothing" not supported in global keyboard command? - ben 12/31/91





;;;; Grammar for restrictions





;;; Grammar for Top Level Restrictions

(def-grammar-list-category main-menu-restrictions (main-menu-mode-restriction)
  :separator \;
  :empty-list-symbol none)

(def-grammar-list-category global-keyboard-command-restrictions
    (global-keyboard-command-mode-restriction)
  :separator \;
  :empty-list-symbol none)


(def-grammar-category main-menu-mode-restriction ()
  ((when-or-unless 'in mode-spec '\: main-menu-restriction-clause-list)
   (1 3 . 5) fix-mode-restriction))

(def-grammar-category when-or-unless ()
  when unless)


(def-grammar-category mode-spec ()
  ((g2-user-mode 'mode) (1))
  ((g2-user-mode 'or g2-user-mode 'mode) (1 3)) ; mode NOT plural
  ;; This parses the regular expression "M, { M, }* M, or M mode" where M
  ;; matches any g2-user-mode
  ((g2-user-mode '\, mode-list 'mode) (1 . 3) cons-car-cddr))


(def-grammar-category mode-list ()
  ((g2-user-mode '\, mode-list) (2 1 3) (simplify-associative-operation))
  ((g2-user-mode '\, 'or g2-user-mode) (2 1 4)))


(def-grammar-category global-keyboard-command-mode-restriction ()
  ((when-or-unless 'in mode-spec '\: global-keyboard-command-restriction-clause-list)
   (1 3 . 5) fix-mode-restriction))
    
(def-grammar-list-category main-menu-restriction-clause-list (main-menu-restriction-clause)
  :separator \;)

(def-grammar-list-category global-keyboard-command-restriction-clause-list
    (global-keyboard-command-restriction-clause)
  :separator \;)


;; NOTE: restriction-clauses when transformed, must not have car be '\; .


;;; Main Menu Restriction Clauses

(def-grammar-category main-menu-restriction-clause ()
  (('main 'menu 'choices restriction-type-with-colon main-menu-choices)
   (main-menu 4 . 5) (fix-tailing-associative-list 2)))

(def-grammar-category global-keyboard-command-restriction-clause ()
  (('global 'keyboard 'commands
	    restriction-type-with-colon
	    global-keyboard-command-choices)
   (global-keyboard-command 4 . 5) (fix-tailing-associative-list 2)))

(def-grammar-list-category main-menu-choices (main-menu-choice)
  :separator \,)

(def-grammar-list-category global-keyboard-command-choices
    (global-keyboard-command-choice)
    :separator \,)





;;;; Object Configuration

(eval-when (:compile-toplevel :load-toplevel :execute)
(defparameter item-menu-choices
  '(lift-to-top drop-to-bottom go-to-referenced-item
    clone-as-trend-chart table edit transfer move clone change-min-size
    align-text			; new for 5.0 rev. 3 (MHD 3/10/97)
    font				; 8.2r1 -fmw, 12/7/05
    show-unsaved-attributes table-of-hidden-attributes ; 6.0r0
    color delete go-to-message-origin enable disable describe
    view-change-log
    compile-g2gl-process
    clean-up-g2gl-compilation-postings-on-process
    execute-g2gl-process
    dynamic-rule-invocation-display describe-configuration
    mark-to-strip-text mark-to-strip-text-* remove-strip-text-mark
    remove-strip-text-mark-* mark-not-to-strip-text-*
    mark-not-to-strip-text remove-do-not-strip-text-mark-*
    remove-do-not-strip-text-mark go-to-subworkspace create-instance

    ;; For G2GL/BPEL:
    set-temporary-breakpoint remove-temporary-breakpoint
    add-stub-for-local-handler

    edit-icon
    table-of-values name rotate-reflect change-size restore-to-normal-size
    dynamic-backward-chaining describe-chaining
    dynamic-generic-rule-display create-subworkspace
    edit-cell-expression edit-cell-format other-edits add-row add-column
    delete-row delete-column hide-name))

#+enable-ole
(defparameter item-menu-choices-available-with-mouse-down
  (append '(ole-clone ole-transfer) item-menu-choices))

(defvar table-menu-choices
  '(subtable delete-subtable change-to-no change-to-yes
    change-to				; 8.3r0
    show-subtable-of-unsaved-attributes ; 6.0r0
    add-optional-subtable table choose-existing-class edit edit-icon
    transfer move clone show-attribute-display add-another-attribute
    delete-attribute add-name-of-attribute delete-name-of-attribute
    hide-attribute-display change-size enable disable go-to-original
    delete-original transfer-original describe-configuration describe
    view-change-log show-value
    ;; trend chart stuff that fell off the table in 4.0
    show-text show-summary-of-text add-subtable subtables
    dynamic-backward-chaining describe-chaining
    dynamic-generic-rule-display hide delete hide-table
    mark-to-strip-text mark-to-strip-text-* remove-strip-text-mark
    remove-strip-text-mark-* mark-not-to-strip-text-*
    mark-not-to-strip-text remove-do-not-strip-text-mark-*
    remove-do-not-strip-text-mark
    ;; Gensym-178-HQ-5673853-SUCI-Add menu-choice on table of item go-to-item
    go-to-item))

(defvar global-keyboard-command-choices
  '(pause refresh help full-scale normalized-full-scale lift-to-top
    drop-to-bottom circulate-up circulate-down shift-left-ten-percent
    shift-up-ten-percent shift-right-ten-percent shift-down-ten-percent
    shift-left-one-percent shift-up-one-percent shift-right-one-percent
    shift-down-one-percent center-origin scale-to-fit maximum-scale-to-fit
    twenty-percent-smaller twenty-percent-bigger twenty-percent-narrower
    twenty-percent-wider one-quarter-the-scale four-times-the-scale
    toggle-visible-grid))

(defvar main-menu-choices
  '(start pause resume reset restart new-workspace table-of-attributes-pane ;; Added by SoftServe
    get-workspace #+obsolete view-options inspect load-merge-save load-kb merge-kb save-kb
    system-tables run-options change-mode miscellany long-menus
    short-menus create-new-module delete-module new-title-block
    neatly-stack-windows network-info close-telewindows-connection log-out 
    change-password reinstall-authorized-users ; Added. (MHD 2/11/98)
; Development only.
;    memory-management-table telewindows-status-table
    connect-to-foreign-image disconnect-from-foreign-image
    load-attribute-file write-g2-stats
    clear-kb shut-down-g2
    turn-on-all-explanation-caching
    turn-off-all-explanation-caching enter-package-preparation-mode
    leave-package-preparation-mode strip-texts-now
    make-workspaces-proprietary-now
    flush-change-log-for-entire-kb
    enter-simulate-proprietary-mode
    leave-simulate-proprietary-mode do-not-highlight-invoked-rules
    highlight-invoked-rules enable-all-items
    remove-tracing-and-breakpoints launch-online-help
    print-window
    #+use-scc update-file #+use-scc edit-file #+use-scc unedit-file
    #+use-scc commit-file #+use-scc revert-file))

(defvar workspace-menu-choices
  '(new-object new-rule new-display new-definition
    new-free-text new-button name clone-workspace table color move
    hide-workspace go-to-superior
    lift-to-top drop-to-bottom shrink-wrap delete-workspace
    enable disable miscellany main-menu operate-on-area describe
    view-change-log
    toggle-visible-grid			; 8.3b0 -fmw, 11/21/06

    ;; For BPEL/G2GL - process body workspaces
    compile-g2gl-process-workspace
    clean-up-g2gl-compilation-postings-on-body
    execute-g2gl-process-workspace
    redo-layout-of-g2gl-body

    ;; For BPEL/G2GL - execution display workspaces
    single-step do-not-single-step
    close-and-continue
    break-on-execution-faults do-not-break-on-execution-faults
    remove-all-temporary-breakpoints
    bring-up-source
    pause-process-instance resume-process-instance
    delete-process-instance
    process-display-attributes
    g2gl-system-attributes
    
    describe-configuration print print-to-server mark-to-strip-text mark-to-strip-text-*
    remove-strip-text-mark remove-strip-text-mark-*
    mark-not-to-strip-text-* mark-not-to-strip-text
    remove-do-not-strip-text-mark-* remove-do-not-strip-text-mark))

(defparameter menu-and-attribute-visibility-configurations-restriction-types
  '(include
    include-additionally
    exclude
    exclude-additionally
    exclude-absolutely))

(defparameter menu-configuration-operation-types
  '(workspace-menu item-menu non-menu))
)


(def-grammar-list-category object-configuration (object-configuration-clause)
  :separator \;
  :empty-list-symbol none)

(def-grammar-category object-configuration-clause ()
  (configure-user-interface)
  (configure-network-access)
  (restrict-proprietary-items)
  (user-declaration-clause)
  (user-comment-clause))

(def-grammar-category configure-user-interface ()
  (('configure 'the 'user 'interface as-follows user-mode-annotations)
   (user-interface . 6) fix-object-configuration-clause))


(defun fix-network-configuration-clause (raw-network-configuration)
  (let ((network-configuration
	  (fix-object-configuration-clause raw-network-configuration)))
    (phrase-cons
      'network-access
      (let ((network-options nil))
	(loop for raw-network-option in (rest network-configuration)
	      do
	  (let ((product-or-products (first raw-network-option)))
	    (cond
	      ((consp product-or-products)
	       (let ((configuration (second raw-network-option)))
		 (loop for product in (cdr product-or-products)
		       do
		   (phrase-push
		     (phrase-list
		       product
		       nil
		       (copy-list-using-phrase-conses configuration)
		       (case product
			 (g2
			  (phrase-list 'execute 'inform 'read 'write 'connect))
			 (gsi (phrase-list 'execute 'inform 'connect))
			 (telewindows (phrase-list 'connect))))
		     network-options))))
	      (t (phrase-push raw-network-option network-options)))))
	(nreverse network-options)))))

(def-grammar-category configure-network-access ()
  (('set 'up 'network 'access as-follows network-access-options)
   (network-access . 6) fix-network-configuration-clause))


(def-grammar-category user-comment-clause ()
  (('comment as-follows comment-options)
   (comment . 3) fix-object-configuration-clause))


;;; The grammar-category `as-follows' was an attempt to get better editor
;;; prompting.

(def-grammar-category as-follows ()
  (('as 'follows '\:)))


  
;;; The function `fix-object-configuration-clause' normalizes
;;;  (type |,| options) into (type . options)

(defun fix-object-configuration-clause (form)
  (if (memq (second form) '(\; \,))
      (phrase-cons (first form) (cddr form))
      form))



(def-substitution-macro empty-item-configuration-clause-p (clause)
  (or (null clause) (singleton? clause)))

;; NOTE: the macro user-interface-clause-p has been moved back to RUN.

;; The CONFIGURE name is no longer used, but I fear it may exist in some
;; 4.0alpha kbs.

(def-substitution-macro proprietary-items-clause-p (clause)
  (eq (first clause) 'proprietary))


(def-substitution-macro workspace-menu-clause-p (clause)
  (eq (first clause) 'workspace-menu))

(def-substitution-macro absolute-user-interface-clause-p (clause)
  (eq (first clause) 'selecting-absolutely))



;; The clauses looks like 
;; (CLICKING|PRESSING <key-code> <action> [class])
;; (SELECTING|SELECTING-ABSOLUTELY (classes) action)
;; (WORKSPACE-MENU (classes) <include|exclude> . <actions>)
;;    -- equiv to selecting implies post-menu
;;       but NOT workspace-menu with exclude-absolutely!!


;;; The substitution-macro `user-interface-clause-restriction-type' returns the
;;; restriction type of a UI clause, which is include, exclude,
;;; include-additionally, exclude-additionally, exclude-absolutely, or nil.

(def-substitution-macro user-interface-clause-restriction-type (clause)
  (case (first clause)  
    (workspace-menu
     (third clause))

    (table
     (fourth clause))

    (non-menu
     (third clause))
    
    (main-menu
     (second clause))
    
    (global-keyboard-command
     (second clause))))


;;; The substitution-macro `user-interface-clause-command-names' returns a list
;;; of the command names which the given clause restricts.  Of course, the names
;;; are not necessarily the names of real UI commands.

(def-substitution-macro user-interface-clause-command-names (clause)
  (case (first clause)  
    (workspace-menu
     (cdddr clause))
    (table
     (cddddr clause))

    (non-menu
     (cdddr clause))
    
    (main-menu
     (cddr clause))
    
    (global-keyboard-command
     (cddr clause))))


(def-substitution-macro user-interface-clause-absolute-exclusions (clause)
  (when (eq (user-interface-clause-restriction-type clause)
	    'exclude-absolutely)
    (user-interface-clause-command-names clause)))



;;; The substitution-macro `workspace-menu-clause-implicitly-binds-mouse-select?'
;;; returns T for workspace-menu clauses which implicitly bind mouse-select to
;;; MENU (which posts the standard object menu).  The ADDITIONALLY and
;;; ABSOLUTELY versions do not, they merely adjust which items would appear in
;;; the menu.

(defun-substitution-macro workspace-menu-clause-implicitly-binds-mouse-select?
    (clause)
  ;; Turn off this odd behavior in the selection UI. See HQ-4576741.
  (unless (selection-enabled-p)
    (memq (user-interface-clause-restriction-type clause)
	  '(include exclude))))


(defun-substitution-macro user-interface-clause-key-code (clause)
  (case (first clause)
    ((pressing clicking)
     (second clause))
    ((selecting selecting-absolutely)
     (key-code 'mouse-select))
    (workspace-menu
     (when (workspace-menu-clause-implicitly-binds-mouse-select? clause)
       (key-code 'mouse-select)))))


(defun-substitution-macro user-interface-clause-action (clause)
  (case (first clause)
    ((pressing clicking)
     (third clause))
    ((selecting selecting-absolutely)
     (third clause))
    (workspace-menu
     (when (workspace-menu-clause-implicitly-binds-mouse-select? clause)
       'menu))))



;;; The substitution-macro `user-interface-clause-class-spec' returns
;;; NIL, a class, or a list of classes.

(defun-substitution-macro user-interface-clause-class-spec (clause)
  (case (first clause)
    ((pressing clicking)
     (fourth clause))
    ((selecting selecting-absolutely)
     (second clause))
    (workspace-menu
     (second clause))
    (table
     (second clause))
    (non-menu
     (second clause))
     
    (global-keyboard-command
     nil)

    (constrain
     (third clause))))



		    
;;;; Declarations


;; (DECLARATION class p1 v1 p2 v2 ...)

(def-grammar-category user-declaration-clause ()
  (('declare 'properties as-follows user-declarations)
   (declaration nil . 4) massage-user-declaration-clause)
  (('declare 'properties 'of item-filter as-follows user-declarations)
   (declaration 4 . 6) massage-user-declaration-clause))


;; Convert (declaration class-spec |,| (p v) (p v) ...) into
;; (declaration class-spec p v p v ...)
(defun massage-user-declaration-clause (user-declaration-clause)
  (let ((form user-declaration-clause))
    (when (memq (third form) '(\; \,))
      (setq form (phrase-list* (first form) (second form) (cdddr form))))
    (cond ((consp (third form))
	   (phrase-list*
	     (first form)
	     (second form)
	     (loop for (p v) in (cddr form)
		   collect p using phrase-cons
		   collect v using phrase-cons)))
	  (t
	   form))))



(def-grammar-list-category user-declarations (user-declaration-element)
  :separator \,)


(def-grammar-category user-declaration-element ()
  (frame-declaration (1 t))
  (('not frame-declaration) (2 nil)))
  
;; Add an "absolutely" option?
   

;;; The grammar-category `frame-declaration' includes random boolean-valued
;;; things we wish to declare on a frame.

(def-grammar-category frame-declaration ()
  stable-for-dependent-compilations
  independent-for-all-compilations
  stable-hierarchy
  ;; Things which used to be capabilities.
  activatable-subworkspace
  external-simulation
  manual-connections
  subworkspace-connection-posts

  ;; just in case the optimizer starts shooting users in the foot
  optimizable
  inlineable
  #+development
  system-action

  invisible-to-unsavable-change-protection
  )


;; Dropped from 4.0:
;  manually-enabled
;  manually-disabled
;; To avoid confusion with the state of a single block, which is called
;; "disabled", name this inherited declaration "manually-disabled"
;  proprietary     ; Only allowed on workspaces
;  text-stripped



;; (DECLARATION class p1 v1 p2 v2 ...)

(def-substitution-macro object-configuration-declare-clause-p (clause)
  (eq (first clause) 'declaration))

(def-substitution-macro declare-clause-class-spec (clause)
  (second-of-long-enough-list clause))

(def-substitution-macro declare-clause-plist (clause)
  (cdr-of-cons (cdr-of-cons clause)))


(defun make-declaration-clause-for-item-configuration (property value &optional class?)
  (when (eq property 'no-manual-connections)
    (setq property 'manual-connections
	  value (not value)))
  (slot-value-list 'declaration
		   (slot-value-list (or class? 'item))
		   property
		   (if value t nil)))

;; Called by process-pre-4.0-capabilities-of-class, which turns 3.0-capabilities
;; into declarations in instance configurations.


(def-substitution-macro object-configuration-comment-clause-p (clause)
  (eq (first clause) 'comment))


;;;; Network Access



;;; Network access annotations look like:
;;; "Allow read or write access to this pump by g2"
;;;  (network-access (g2-and-or-gsi class-spec restriction-type access-types) ... )


(def-substitution-macro network-access-clause-p (clause)
  (eq (first clause) 'network-access))

(def-substitution-macro network-access-clause-phrases (clause)
  (cdr clause))


(def-substitution-macro network-access-phrase-agent (network-phrase)
  (first network-phrase))

;; list of restricted access types:
(def-substitution-macro network-access-phrase-access-types (network-phrase)
  (fourth network-phrase))

(def-grammar-list-category network-access-options (network-access-option)
  :separator \,)

;;;; network-access-options grammar category.
;;;;
;;;;   if there were gsi-specific access types, the commented-out lines below
;;;;   would be uncommented, and grammar would be defined for
;;;;   gsi-network-access-types, etc.  -ncc, 11/30/94

(def-grammar-category network-access-option ()

  ;; Collect all access prohibitions possible by several products
  ((network-access-prefix 'access 'by network-accessing-product-list)
   (4 1)) ;fixed in configure-network-access category

  ((network-access-prefix common-network-access-types)
   (any nil 1 2))
  ((item-independent-network-access-prefix client-network-access-types)
   (any nil 1 2))
  ((network-access-prefix g2-network-access-types)
   (g2 nil 1 2))
  ;;  ((network-access-prefix gsi-network-access-types)
  ;;   (gsi nil 1 2))

  ((network-access-prefix common-network-access-types 'to item-filter)
   (any 4 1 2))
  ((network-access-prefix g2-network-access-types 'to item-filter)
   (g2 4 1 2))
  ;;  ((network-access-prefix gsi-network-access-types 'to item-filter)
  ;;   (gsi 4 1 2))

  ((network-access-prefix common-network-access-types 'by network-access-agent)
   (4 nil 1 2))
  ((network-access-prefix g2-network-access-types 'by 'g2)
   (g2 nil 1 2))
  ;;  ((network-access-prefix gsi-network-access-types 'by 'gsi)
  ;;   (gsi nil 1 2))
  ((item-independent-network-access-prefix
     client-network-access-types 'by client-access-agent)
   (4 nil 1 2))

  ((network-access-prefix common-network-access-types 'to item-filter 'by network-access-agent)
   (6 4 1 2))
  ((network-access-prefix g2-network-access-types 'to item-filter 'by 'g2)
   (g2 4 1 2))
  ;;  ((network-access-prefix gsi-network-access-types 'to item-filter 'by 'gsi)
  ;;   (gsi 4 1 2))
)

;;; The function `prohibit-connect-by-gsi' prevents the grammar from parsing
;;; any explicit mention of connect access and gsi.
;;;  The function is gone -- gsi connect access is precluded by the new grammar.
;;;     -ncc, 11/11/94

(def-grammar-category network-access-prefix ()
  ('allow include-additionally)
  ('prohibit exclude-additionally)
  (('prohibit 'absolutely) exclude-absolutely))

(def-grammar-category item-independent-network-access-prefix ()
  ('allow include-additionally)
  ('prohibit exclude-additionally))

(def-grammar-category common-network-access-types ()
  ((common-network-access-type-list 'access) 1 fix-item-filter-phrase))
(def-grammar-category g2-network-access-types ()
  ((g2-network-access-type-list 'access) 1 fix-item-filter-phrase))
(def-grammar-category client-network-access-types ()
  ((client-network-access-type 'access) (1) fix-item-filter-phrase))

(def-grammar-list-category common-network-access-type-list (common-network-access-type)
  :separator \,
  :conjunction or)
(def-grammar-list-category g2-network-access-type-list (g2-network-access-type)
  :separator \,
  :conjunction or)
(def-grammar-list-category network-accessing-product-list
    (network-accessing-product)
  :separator \,
  :conjunction or)


;; access types shared by G2 and GSI
(def-grammar-category common-network-access-type  ()
  inform execute)

;; access types that only apply to G2
(def-grammar-category g2-network-access-type  ()
  read write)

;; access types that apply to clients of G2 listener (currently G2 and
;; Telewindows)  gsi, too.
(def-grammar-category client-network-access-type  ()
  connect)

;; for the common types, a choice of agents is possible.
(def-grammar-category network-access-agent ()
  g2
  gsi
  (('g2 'and 'gsi) g2-and-gsi)
  (('gsi 'and 'g2) g2-and-gsi))

;; for the client types, a choice of agents is possible.
(def-grammar-category client-access-agent ()
  g2
  telewindows
  gsi
  (('g2 'and 'gsi) g2-and-gsi)
  (('g2 'and 'gsi 'and 'telewindows) g2-and-telewindows-and-gsi)
  (('g2 'and 'telewindows) g2-and-telewindows)
  (('g2 'and 'telewindows 'and 'gsi) g2-and-telewindows-and-gsi)
  (('gsi 'and 'g2) g2-and-gsi)
  (('gsi 'and 'g2 'and 'telewindows) g2-and-telewindows-and-gsi)
  (('gsi 'and 'telewindows) telewindows-and-gsi)
  (('gsi 'and 'telewindows 'and 'gsi) g2-and-telewindows-and-gsi)
  (('telewindows 'and 'g2) g2-and-telewindows)
  (('telewindows 'and 'g2 'and 'gsi) g2-and-telewindows-and-gsi)
  (('telewindows 'and 'gsi) telewindows-and-gsi)
  (('telewindows 'and 'gsi 'and 'g2) g2-and-telewindows-and-gsi))

(def-grammar-category network-accessing-product ()
  g2
  gsi
  telewindows)


;;;; User Interface Clauses


;; Do not allow NONE. The user has to delete the entire clause for that.
(def-grammar-list-category user-mode-annotations (user-mode-annotation)
  :separator \;)


(def-grammar-category user-mode-annotation ()
  ((when-or-unless 'in mode-spec '\: user-annotation-clause-list)
   (1 3 . 5) fix-mode-restriction))


(def-grammar-list-category user-annotation-clause-list (user-annotation-clause)
  :separator \;)


;; The user-bindable keysyms.

(defun-simple string-to-display-for-keyboard-symbol (keysym do-not-downcase?)
  (declare (ignore do-not-downcase?))
  (copy-symbol-name keysym nil))	; gets a lowercase text string

(defun-simple string-to-insert-for-keyboard-symbol (keysym)
  (let ((write-symbols-parsably? ; Magic value escapes digits and punctuation.
	  'for-filters))
    (twith-output-to-text-string
      (cond ((eq keysym '@)		; if the quoting character,
	     (twrite-string "@@"))	;   quote it  [other chars?!]
	    (t
	     (twrite-key-code (key-code keysym)))))))


;; A keyboard character which we specifically allow users to rebind.
(def-semi-open-category (keyboard-symbol :base-category symbol
					 :string-to-display #'string-to-display-for-keyboard-symbol
					 :string-to-insert #'string-to-insert-for-keyboard-symbol)
  #.bindable-keysyms)




;;; The grammar category `user-annotation-clause' includes user restrictions as
;;; a subset.  The parsed forms look like: (<type> <key-code-as-fixnum>
;;; <ui-action> <class-spec>)

(def-grammar-category user-annotation-clause ()
  (user-restriction-clause)
  (clicking-and-pressing)
  (constrain-moving))


(def-grammar-category constrain-moving ()
  (('constrain 'moving item-filter
	       'such 'that 'the 'item 'aligns 'on 'the 'grid grid-spec)
   (1 moving 3 12))
  (('constrain 'moving item-filter
	       'to 'the 'rectangle rectangle)
   (1 rectangle 3 7)))

;; Should we allow constraining the motion of workspaces, too? ***


(def-grammar-category mouse-frenzy ()
  clicking				; "Clicking" is like "Selecting"
  double-clicking
  pressing
  releasing)
  

(def-grammar-category clicking-and-pressing ()
  ;; With no class qualifier, gets only global commands
  ((mouse-frenzy user-interface-mouse-chord implies-global-command)
   (1 2 3) parse-user-interface-gesture)

  ;; "Clicking on any workspace ..." gets only workspace commands.
  ((mouse-frenzy user-interface-mouse-chord 'on workspace-filter implies-workspace-command)
   (1 2 5 4) parse-user-interface-gesture)

  ;; "Clicking on any <item> ..." gets item-menu (and user-menu) choices.
  ((mouse-frenzy user-interface-mouse-chord 'on item-filter implies-item-command)
   (1 2 5 4) parse-user-interface-gesture)

  ;; User-mouse-tracking, only on mouse-fown.
  ;; We need some way to restrict start-procedure?
  (('pressing user-interface-mouse-chord 'on item-filter 'starts
	      procedure-name 'as 'the 'mouse 'tracks 'over item-filter)
   (pressing 2 (user-mouse-tracking 6 12) 4) parse-user-interface-gesture)
  (('pressing user-interface-mouse-chord 'on item-filter 'starts
	      procedure-name 'as 'the 'mouse 'tracks
	      'continuously
	      'over item-filter)
   (pressing 2 (user-mouse-tracking 6 13 motion) 4) parse-user-interface-gesture)


  ;; "Typing" phrases are analogous to global keyboard commands.
  ;; With no class qualifier:
  (('typing user-interface-key-chord implies-global-command)
   (typing 2 3) parse-user-interface-gesture)

  ;; Workspace:
  (('typing user-interface-key-chord 'on workspace-filter implies-workspace-command)
   (typing 2 5 4) parse-user-interface-gesture)

  ;; Item:
  (('typing user-interface-key-chord 'on item-filter implies-item-command)
   (typing 2 5 4) parse-user-interface-gesture)


  ;; rolling [modifiers+] the mouse wheel (forward | backward) [over any <class>] implies ...
  ;; Global:
  (('rolling mouse-wheel-chord implies-global-command)
   (rolling 2 3) parse-user-interface-gesture)

  ;; Workspace:
  (('rolling mouse-wheel-chord 'over workspace-filter implies-workspace-command)
   (rolling 2 5 4) parse-user-interface-gesture)

  ;; Item:
  (('rolling mouse-wheel-chord 'over item-filter implies-item-command)
   (rolling 2 5 4) parse-user-interface-gesture)

  ;; "Hovering [modifiers] the mouse [over any <class>] implies ...
  (('hovering mouse-hover-chord 'over workspace-filter implies-workspace-command)
   (hovering 2 5 4) parse-user-interface-gesture)

  (('hovering mouse-hover-chord 'over item-filter implies-item-command)
   (hovering 2 5 4) parse-user-interface-gesture)
  )



;; Note that each of these allows any symbol.  See the grammar in menus.lisp.

(def-grammar-category implies-global-command ()
  (('implies main-menu-choice) 2)
  (('implies global-keyboard-command-choice) 2)
  (('does 'nothing) nothing))


(def-grammar-category implies-workspace-command ()
  (('implies workspace-menu-choice) 2)
  (('does 'nothing) nothing))


(def-grammar-category implies-item-command ()
  (('implies item-menu-choice) 2)
  (('does 'nothing) nothing))

#+enable-ole
(def-grammar-category implies-item-command-available-with-mouse-down ()
  (('implies item-menu-choice-available-with-mouse-down) 2)
  (('does 'nothing) nothing))

;; Note that item-menu-choices include user-menu-choices.
;; Should have included the ABSOLUTELY grammar here.



;;; The grammar-list-category `user-restrictable-class' is the same as
;;; restrictable-class, except that it includes WORKSPACE. It is meant to be
;;; the standard grammar category used for class names that the user can type
;;; into object configurations.

(def-grammar-list-category user-restrictable-classes (user-restrictable-class)
  :separator \,
  :conjunction or)

(def-grammar-category user-restrictable-class ()
  (class)
  ('name-box)
  ('workspace))



;;; The grammar-category `item-filter' handles the two ways of refining an
;;; object configuration based on classes of frames: "ANY class-1, class-2,
;;; ... OR class-N" and "THIS class".  We over-compactly represent the THIS
;;; case with the class as symbol, and the ANY class with the classes as a
;;; list.

(def-grammar-category item-filter ()
  (('any user-restrictable-classes) 2 fix-item-filter-phrase) ; A list of classes.
  (('this 'item)  2 fix-item-filter-phrase))		    ; Only allow "this item" here.



;;; The grammar-category `workspace-filter' is a variation just for workspaces.

(def-grammar-category workspace-filter ()
  (('any 'workspace) (workspace)))


(defun fix-item-filter-phrase (phrase)
  (cond ((null phrase)
	 nil)
	((atom phrase)
	 phrase)
	((memq (first phrase) '(\, \;))
	 (cdr phrase))
	(t
	 phrase)))


(def-grammar-category grid-spec ()
  (('\( positive-integer '\, positive-integer '\)) (2 . 4)
   grid-spec-must-be-positive))

(defun grid-spec-must-be-positive (grid-spec)
  (if (and (>f (car grid-spec) 0)
	   (>f (cdr grid-spec) 0))
      grid-spec
      (values
	bad-phrase
	(copy-constant-wide-string #w"Grid must be specified with positive values."))))

(declare-grammar-transform-can-return-bad-phrase grid-spec-must-be-positive)


;;; The grammar-category `rectangle' defines a user-coordinates workspace
;;; rectangle in the order (left,right,bottom,top).

(def-grammar-category rectangle ()
  (('\( integer '\,
	integer '\,
	integer '\,
	integer '\))
   (2 4 6 8)))



;;; The function `twrite-mouse-button-for-filters' undoes what
;;; disambiguate-mouse-button did.

(defun twrite-mouse-button-for-filters (key-code)
  ;; Until we permit other sorts of double-mouse gestures (double-down,
  ;; double-drag, etc), we map them all to double-clicking, which in 7.0r1 gets
  ;; compiled into a mouse-select key-code (in 7.0r0, it compiles into a
  ;; mouse-down, which was a bug because the word "clicking" in a configuration
  ;; is supposed to mean, and has always meant, a mouse-down and a mouse-up on
  ;; the same spot on the screen).
  (cond ((double-bit-on-p key-code)
	 (setq key-code (logandf double-mask key-code))	; Modifying argument.
	 (twrite "double-clicking "))
	((key-code-is-mouse-select-p key-code)
	 (twrite "clicking "))
	((key-code-is-mouse-down-p key-code)
	 (twrite "pressing "))
	(t
	 (twrite "releasing ")))
  (twrite-key-modifier-bits key-code nil)
  (key-case (key-index key-code)
    ((mouse-down mouse-up mouse-select)
     (twrite "any mouse button"))
    ((mouse-left-down mouse-left-up mouse-left-select)
     (twrite "the left mouse button"))
    ((mouse-middle-down mouse-middle-up mouse-middle-select)
     (twrite "the middle mouse button"))
    ((mouse-right-down mouse-right-up mouse-right-select)
     (twrite "the right mouse button"))
    (t
      (dwarn "Unfamiliar key-code ~a in twrite-mouse-button-for-filters"
	     (key-name key-code)))))



;;; The function `disambiguate-mouse-button' converts a pseudo key name
;;; ANY/LEFT/MIDDLE/RIGHT-MOUSE-BUTTON into real mouse-up, mouse-down, or
;;; mouse-select key name based on the type of parsed UI clause in which it
;;; appeared.

(defun disambiguate-mouse-button (pseudo-button ui-clause-type)
  (or (case pseudo-button
	(any-mouse-button
	 (case ui-clause-type
	   (clicking 'mouse-select)
	   (pressing 'mouse-down)
	   (releasing 'mouse-up)
	   (double-clicking 'mouse-select)))
	(left-mouse-button
	 (case ui-clause-type
	   (clicking 'mouse-left-select)
	   (pressing 'mouse-left-down)
	   (releasing 'mouse-left-up)
	   (double-clicking 'mouse-left-select)))
	(middle-mouse-button
	 (case ui-clause-type
	   (clicking 'mouse-middle-select)
	   (pressing 'mouse-middle-down)
	   (releasing 'mouse-middle-up)
	   (double-clicking 'mouse-middle-select)))
	(right-mouse-button
	 (case ui-clause-type
	   (clicking 'mouse-right-select)
	   (pressing 'mouse-right-down)
	   (releasing 'mouse-right-up)
	   (double-clicking 'mouse-right-select))))
      pseudo-button))


;;; The function `disambiguate-mouse-button-in-phrase' disambiguates any mouse
;;; button psuedo key names found in phrase. Double-clicking is handled by
;;; adding the DOUBLE modifier to the result.

(defun disambiguate-mouse-button-in-phrase (phrase ui-clause-type)
  (let ((key-spec
	  (cond ((atom phrase)
		 (disambiguate-mouse-button phrase ui-clause-type))
		(t
		 (loop for element in phrase
		       collect (disambiguate-mouse-button element ui-clause-type)
			 using phrase-cons)))))
    (case ui-clause-type
      (double-clicking
       (cond ((atom key-spec)
	      (phrase-list 'double key-spec))
	     (t
	      (phrase-cons 'double key-spec))))
      (t
       key-spec))))


;;; The function `parse-user-interface-gesture' canonicalizes the list of
;;; classes in the phrase, which looks like:
;;;    (<type> <key-name> <action> <class-or-classes>)

;;; The only types we store are SELECTING, CLICKING and PRESSING. The first two
;;; refer to mouse events and the last to keyboard events. Any other information
;;; from the phrase is folded into the key code.

(defun parse-user-interface-gesture (phrase)
  (let* ((type (first phrase))
	 (key-spec (disambiguate-mouse-button-in-phrase (second phrase) type))
	 (key-code (key-code-from-list key-spec))
	 (action (third phrase))
	 (classes (fourth phrase))
	 (type-to-store (case type	; Backtranslate to the old type.
			  (pressing 'clicking) ; Lost info is stored in the key code here.
			  (releasing 'clicking)
			  (clicking type)
			  (double-clicking 'clicking)
			  (typing 'pressing)
			  (rolling 'pressing)
			  (hovering 'pressing)
			  (selecting type)
			  (t (dwarn "Unfamiliar UI clause type ~s" type)
			     type))))
    (when (and (consp classes)
	       (eq (car classes) '\,))
      (setq classes (cdr classes)))

    (cond ((illegal-key-code-p key-code)
	   (values bad-phrase "Not a known keyboard symbol"))

	  ;; Others here?  Control+A, maybe?
	  ((key-code-equal key-code '(control y))
	   (values bad-phrase "You are not allowed to rebind control+y"))

	  ;; If you change this, you must update rebindable-key-code-p
;	  ((printable-character-key-code-p key-code)
;	   (values bad-phrase
;		   "You are not allowed to rebind printable characters without modifiers."))

	  ((consp action)
	   ;; For now, list actions are used only by user-mouse-tracking.
	   ;; There, the list format is
	   ;;     (USER-MOUSE-TRACKING procedure classes [MOTION])
	   (phrase-list type-to-store
			key-code
			(copy-list-using-phrase-conses action)
			classes))
	  (t
	   (phrase-list type-to-store key-code action classes)))))

(declare-grammar-transform-can-return-bad-phrase parse-user-interface-gesture)

;; If the key character is punctuation-mark-p, then the editor returns it as a
;; symbol in the keyword package.




;;; The function `parse-user-interface-key-chord' canonicalizes the list of
;;; modifiers and keysym.  We cannot convert to a key-code here because
;;; this transformer is not always called by the parser.

(defun parse-user-interface-key-chord (chord)
  ;; Chord looks like key or ((+ modifiers) key)
  (when (consp chord)
    (setq chord (phrase-flatten-tree chord)))
  (when (eq (first chord) '+)
    (pop chord))
  chord)


(def-grammar-category user-interface-key-chord ()
  ;; Ought to omit the printable ones here.
  (keyboard-symbol)

  ((modifier-keys '+ keyboard-symbol) (1 3) parse-user-interface-key-chord)

  ;; To make it easier to enter funny characters, like, "control+@".
  (whole-string))

   
(def-grammar-category forward-and-backward ()
  (('the 'mouse 'wheel 'forward) mouse-wheel-forward)
  (('the 'mouse 'wheel 'backward) mouse-wheel-backward))

(def-grammar-category mouse-wheel-chord ()
  (forward-and-backward)
  ((modifier-keys '+ forward-and-backward) (1 3) parse-user-interface-key-chord))

(def-grammar-category mouse-hover-chord ()
  (('the 'mouse) (mouse-hover))
  ((modifier-keys '+ 'the 'mouse) (1 mouse-hover) parse-user-interface-key-chord))


(def-grammar-category user-interface-mouse-button ()
  ;; We want the editor to prompt with the entire string "any mouse button"
  (('any 'mouse 'button) (any-mouse-button))
  (('the 'left 'mouse 'button) (left-mouse-button))
  (('the 'middle 'mouse 'button) (middle-mouse-button))
  (('the 'right 'mouse 'button) (right-mouse-button)))

(def-grammar-category user-interface-mouse-chord ()
  (user-interface-mouse-button)
  ((modifier-keys '+ user-interface-mouse-button) (1 3) parse-user-interface-key-chord))






(def-grammar-category modifier-key ()
  control shift alt)

(def-grammar-list-category modifier-key-list (modifier-key)
  :separator +)

(def-grammar-category modifier-keys ()
  (modifier-key-list 1 remove-separator-symbol-from-phrase))


(defun remove-separator-symbol-from-phrase (phrase)
  (cdr phrase))



(def-grammar-category of-item-filter-is ()
  (('of item-filter 'is) 2)
  ('is nil))


(def-grammar-category ordered-pair-of-integers ()
  (('\( integer '\, integer '\)) (2 4)))



;;; The macro `slot-value-push-property' pushes value onto
;;; the indicator property of the plist in place.

(defmacro slot-value-push-property (indicator value place)
  `(cond ((getf ,place ,indicator)
	  (let* ((old (getf ,place ,indicator))
		 (new (nconc (slot-value-list ,value) old)))
	    (setf (getf ,place ,indicator) new)))
	 (t
	  (slot-value-push (slot-value-list ,value) ,place)
	  (slot-value-push ,indicator ,place))))

;; Push on getf did not seem to work.




;;;; Proprietary clauses



(def-grammar-category restrict-proprietary-items ()
  (('restrict 'proprietary 'items as-follows
	      proprietary-restriction-clause-list)
   (proprietary . 5) fix-object-configuration-clause))


(def-grammar-list-category proprietary-restriction-clause-list (proprietary-restriction-clause)
  :separator \;)

(def-grammar-category proprietary-restriction-clause ()
  (user-restriction-clause)
  (clicking-and-pressing)
  (constrain-moving))






;;;; Comment Options



(def-grammar-list-category comment-options (comment-option)
  :separator \,)

(def-grammar-category comment-option ()
  ((symbol '\: whole-string?) (1 3)))




;;;; Grammar for User Restrictions




(def-grammar-list-category user-restrictions (user-mode-restriction)
  :separator \;
  :empty-list-symbol none)

(def-grammar-category user-mode-restriction ()
  ((when-or-unless 'in mode-spec '\: user-restriction-clause-list)
   (1 3 . 5) fix-mode-restriction))

(def-grammar-list-category user-restriction-clause-list (user-restriction-clause)
  :separator \;)



;;; User Restriction Clauses
    

(def-grammar-category user-restriction-clause ()
  (workspace-menu-clause)
  (item-menu-clause)
  (non-menu-clause)
  (workspace-selection-clause)
  (item-selection-clause)
  (slot-visibility-clause)
  (table-menu-clause))



(add-grammar-rules
  '((workspace-menu-clause
      ('menu 'choices 'for 'workspace
       restriction-type-with-colon workspace-menu-choices)
      (workspace-menu (workspace) 5 . 6)
      prohibit-nothing
      (fix-tailing-associative-list 3))

    (workspace-menu-clause
     ('menu 'choices 'for 'workspace
      include-or-exclude-with-colon 'nothing)
     (workspace-menu (workspace) 5))

    (item-menu-clause
     ('menu 'choices for-restrictable-classes
      restriction-type-with-colon item-menu-choices)
     (workspace-menu 3 4 . 5)
     prohibit-nothing
     (fix-tailing-associative-list 3)
     (fix-associative-list 1))

    (item-menu-clause
     ('menu 'choices for-restrictable-classes
      include-or-exclude-with-colon 'nothing)
     (workspace-menu 3 4)
     (fix-associative-list 1))

    (for-restrictable-classes
     ('for restrictable-classes) 2 dont-include-workspace)

    (non-menu-clause
     ('non-menu 'choices 'for restrictable-classes
      restriction-type-with-colon non-menu-choices)
     (non-menu 4 5 . 6)
     prohibit-nothing
     (fix-tailing-associative-list 3)
     (fix-associative-list 1))

    (non-menu-clause
     ('non-menu 'choices 'for restrictable-classes
      include-or-exclude-with-colon 'nothing)
     (non-menu 4 5)
     (fix-associative-list 1))

    (workspace-selection-clause
     ('selecting 'any 'workspace 'implies workspace-menu-choice)
     (selecting (workspace) 5)
     prohibit-nothing)

    ;; Added for 4.0
    (workspace-selection-clause
     ('selecting 'any 'workspace 'absolutely 'implies workspace-menu-choice)
     (selecting-absolutely (workspace) 6)
     prohibit-nothing)

    (workspace-selection-clause
     ('selecting 'any 'workspace 'does 'nothing)
     (selecting (workspace) nothing))

    ;; Added for 4.0
    (workspace-selection-clause
     ('selecting 'any 'workspace 'absolutely 'does 'nothing)
     (selecting-absolutely (workspace) nothing))
    

    (item-selection-clause
     ('selecting 'any restrictable-classes 'implies item-menu-choice)
     (selecting 3 5)
     prohibit-nothing
     (fix-associative-list 1))

    (item-selection-clause
     ('selecting 'any restrictable-classes 'absolutely 'implies item-menu-choice)
     (selecting-absolutely 3 6)
     prohibit-nothing
     (fix-associative-list 1))

    (item-selection-clause
     ('selecting 'any restrictable-classes 'does 'nothing)
     (selecting 3 nothing)
     (fix-associative-list 1))

    (item-selection-clause
     ('selecting 'any restrictable-classes 'absolutely 'does 'nothing)
     (selecting-absolutely 3 nothing)
     (fix-associative-list 1))

    (slot-visibility-clause
     ('attributes 'visible 'for restrictable-classes
      restriction-type-with-colon attribute-names)
     (visibility 4 6 5)
     prohibit-nothing
     (fix-associative-list 1)
     (fix-associative-list 2))

    (slot-visibility-clause
     ('attributes 'visible 'for restrictable-classes
      include-or-exclude-with-colon 'nothing)
     (visibility 4 nil 5)
     (fix-associative-list 1))

    (table-menu-clause
     ('table 'menu 'choices 'for 'the attribute-names-or 'of
      'any restrictable-classes restriction-type-with-colon table-menu-choices)
     (table 9 6 10 . 11)
     prohibit-nothing
     (fix-tailing-associative-list 4)
     (fix-associative-list 1)
     (fix-associative-list 2))

    (table-menu-clause
     ('table 'menu 'choices 'for 'the attribute-names-or 'of
      'any restrictable-classes include-or-exclude-with-colon 'nothing)
     (table 9 6 10)
     (fix-associative-list 1)
     (fix-associative-list 2))

    (table-menu-clause
     ('table 'menu 'choices 'for 'any
      restrictable-classes restriction-type-with-colon table-menu-choices)
     (table 6 nil 7 . 8)
     prohibit-nothing
     (fix-tailing-associative-list 4)
     (fix-associative-list 1))

    (table-menu-clause
     ('table 'menu 'choices 'for 'any
      restrictable-classes include-or-exclude-with-colon 'nothing)
     (table 6 nil 7)
     (fix-associative-list 1))

    (restriction-type-with-colon (restriction-type '\:) 1)
    (restriction-type 'include)
    (restriction-type ('include 'additionally) include-additionally)
    (restriction-type 'exclude)
    (restriction-type ('exclude 'additionally) exclude-additionally)
    (restriction-type ('exclude 'absolutely)   exclude-absolutely)

    (include-or-exclude-with-colon ('include '\:) 1)
    (include-or-exclude-with-colon ('exclude '\:) 1)

    (restrictable-class class)				    ; class was user-instantiable-
							    ;   kb-class; see Note 1 by
							    ;   its grammar in QUERIES!
							    ;   (MHD 6/6/90)

    (restrictable-class 'name-box)
    ;; More of these? E.g. BUTTON-LABEL, TABLE, SCRAP, SLIDER-
    ;;   NEEDLE, etc.? (MHD 6/6/90)

    (item-menu-choice user-menu-choice)))	; "non-built-in-item-menu-choice" ??


(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar non-menu-choices
  '(move-object
  move-objects-beyond-workspace-margin
  move-connection
  move-workspace
  move-workspaces-beyond-window-margin
  show-workspace
  scale-workspace
  click-to-edit
  ;; Maybe "click-to-edit-uses-full-editor" (implies that the EDIT menu choice remains the same).
  full-editor						    
  option-buttons-for-edit-in-place
  menus-for-edit-in-place
  do-not-clear-text-for-edit-in-place

  ;; This restriction applies to the item being edited.  It controls whether
  ;; any outside text selection is allowed by the editor editing that item.
  ;; new for 4.0: (MHD 5/20/94)
  allow-selection-of-outside-text-from-editor

  ;; This restriction applies to the text being swiped.  It controls whether
  ;; that particular piece of text can be swiped to insert it into any editor.
  allow-selection-of-text

  ;; new for 4.0:    (MHD 7/22/94)
  ;;
  ;; UPDATE: now backed out -- maybe reconsider later! (MHD 8/15/94)
  #+not-ready-for-prime-time
  use-single-line-editor
  ;; Remove later!

  select-area				; Rubberband selection
  select-object)))


(def-grammar-category non-menu-choice ()
  . #.non-menu-choices)


(defun prohibit-nothing (form) 
  (if (memq 'nothing form)
      bad-phrase
      form))

(declare-grammar-transform-can-return-bad-phrase prohibit-nothing)



(def-grammar-list-category restrictable-classes (restrictable-class)
  :separator \,
  :conjunction or)


(def-grammar-list-category attribute-names (system-or-user-defined-attribute-name)
  :separator \,)

(def-grammar-category system-or-user-defined-attribute-name ()
  (system-defined-attribute-name)
  (attribute-name)
  ((class '\:\: attribute-name) (class-qualified-name 1 3)
   convert-class-qualified-list-to-keyword-symbol))

(def-grammar-category system-or-user-defined-attribute-name-unconverted ()
  ;; Just like the above category, but doesn't convert class-qualified names
  ;; to keyword symbols.  That's currently a requirement for the conclude-that
  ;; grammar, although we're not sure why.  MHD/JV, 8/1/98
  (system-defined-attribute-name)
  (attribute-name)
  ((class '\:\: attribute-name) (class-qualified-name 1 3)))


(def-grammar-list-category user-attribute-names (user-attribute-name)
  :separator \,)

(def-grammar-category user-attribute-name ()
  (attribute-name)
  ((class '\:\: attribute-name) (class-qualified-name 1 3)
   convert-class-qualified-list-to-keyword-symbol))

(def-grammar-list-category attribute-names-or (system-or-user-defined-attribute-name)
  :separator \,
  :conjunction or)

(def-grammar-category system-defined-attribute-name ()
  (unreserved-symbol))


(def-grammar-list-category workspace-menu-choices  (workspace-menu-choice)
  :separator \,)

(def-grammar-list-category item-menu-choices (item-menu-choice)
  :separator \,)

(def-grammar-list-category non-menu-choices (non-menu-choice)
  :separator \,)

(def-grammar-list-category table-menu-choices (table-menu-choice)
  :separator \,)




;;; Cons-car-cddr and fix-mode-restriction are trivial phrase transformation
;;; functions for the user restriction grammar.

(defun cons-car-cddr (value)
  (phrase-cons (car value) (cddr value)))


;;; Fix-mode-restriction is a trivial phrase transformation function made use of by
;;; the user restriction grammar.
;;;   (?1 ?2 \; . ?3) -> (?1 ?2 . ?3)
;;;   (?1 ?2 . ?3)    -> (?1 ?2 ?3)

(defun fix-mode-restriction (form)
  (if (eq (third form) '\;)
      (phrase-cons (first form) (phrase-cons (second form) (cdddr form)))
      (phrase-list (first form) (second form) (cddr form))))




(defun dont-include-workspace (form)
  (if (or (eq form 'workspace)
	  (and (consp form) (memq 'workspace form)))
      bad-phrase form))

(declare-grammar-transform-can-return-bad-phrase dont-include-workspace)



;;; `Fix-associative-list' works on phrase conses, it copies the list
;;; given removing duplicates.  The later duplicates are prefered over
;;; earlier ones, and the first element is never eliminated.  The Nth
;;; element should be either an atom or a list who's first element is
;;; either a \, or a \;.  If it is an atom it will be converted to a
;;; list of one element.  If it is a list the first element is
;;; discarded.

;; I have no idea what an "associative-list" is?  - ben 1/03/92

(defun fix-associative-list (form n)
  (loop with list? = (nth n form)
	for l on form
	as item = (car l)
	for i from 0
	;; collect unless a duplicate or the first element.
	when  (or (zerop i)
		  (not (memq item (cdr l))))
	  collect
	    (if (=f i n)
		(if (and (consp list?)
			 (memq (car list?) '(\, \;)))
		    (cdr list?)
		    (phrase-list list?))
		item)
	      using phrase-cons))



;;; `Fix-tailing-associative-list' accomplishes the following transformation:
;;; 
;;;   (1) (x y . z) --> (x y z)
;;;   (2) (x y P z1 z2 ...) --> (x y z1 x2 ...)
;;;   
;;; P is a separator, either comma or semicolon. The zi are assumed to be
;;; atoms, or conses whose car is not a separator. The parameter n is the number
;;; of elements preceeding the part that gets "fixed," 2 in the above example.
;;; The function is non-destructive.

;;; It also removes any duplicated (i.e. EQ) elements within the list that gets
;;; fixed, leaving out all duplicates that appear earlier in the list than
;;; the last duplicate.

;;; Another way to put that is: `Fix-tailing-associative-list' works on phrase
;;; conses.  Splits a list at it's Nthcdr.  Creating a copy of the first part and
;;; then appending the second part.  The second part should be either an atom or a
;;; list who's first element is \, or \;.  If it is an atom the second part
;;; converted to a list of one element.  If it is a list the first element is
;;; dropped.

(defun fix-tailing-associative-list (form n)
    (loop with tail = (nthcdr n form)
	  for i from 1 to n
	  for l on form
	  for item = (car l)
	  when (not (loop for ll = (cdr l) then (cdr ll)	; unless a duplicate
			  until (eq ll tail)
			  thereis (eq (car ll) item)))			  
	    collect item into front using phrase-cons
	  finally
	    (return (nconc front
			   (if (and (consp tail)
				    (memq (car tail) '(\, \;)))
			       (cdr tail)
			       (phrase-list tail))))))





;;;; Object Configuration: Writers




(def-slot-value-writer object-configuration (value)
  (write-object-configuration value))


(def-slot-value-reclaimer object-configuration (value frame)
  (add-or-delete-mode-names-from-item-configuration value t)
  (reclaim-slot-value value)
  ;; Leave it in a consistent state. There were problems in drawing
  ;; during the recursive descent of delete-frame.
  (setf (object-configuration frame) nil))


;;; The function `write-object-configuration' writes object configuration
;;; clauses in the order in which they were originally entered by the user.

(defun write-object-configuration (object-configuration)
  (loop with length = (length object-configuration)
	with some = nil
	for i from (-f length 1) downto 0 
	for clause = (nth i object-configuration)
	do (if some (tformat ";~%"))
	   (write-object-configuration-clause clause)
	   (setq some t)
	finally
	  (unless some
	    (twrite "none"))))




;;; The function `write-object-configuration-clause' unravels a clause of an
;;; object configuration and twrites it parseably.

(defun write-object-configuration-clause (clause)
  (case (first clause)
    ;; (USER-INTERFACE . user-restrictions-clauses)
    ((configure user-interface)
     (tformat "configure the user interface as follows:~%")
     (write-user-restrictions (cdr clause)))

    ;; (DECLARE property value class-spec)
    (declare
     (gensym-dstruct-bind ((property value class-spec) (cdr clause))
       (twrite "declare")
       (write-list-of-classes-in-object-configuration class-spec)
       (tformat " ~(~a~a~)" (if value "" "not ") property)))

    ;; (DECLARATION class-spec p1 v1 p2 v2 ...)
    (declaration
     (let ((class-spec (declare-clause-class-spec clause))
	   (plist (declare-clause-plist clause)))
       (twrite "declare properties")
       (when class-spec
	 (twrite " of")
	 (write-list-of-classes-in-object-configuration class-spec))
       (tformat " as follows:~%  ")
       (loop for sublist on plist by 'cddr
	     as (property value) = sublist
	     as last-item = (null (cddr sublist))
	     doing
	 (when (null value)
	   (twrite "not "))
	 (twrite-symbol property)
	 (unless last-item
	   (twrite ", ")))))

    ;; (NETWORK-ACCESS (g2-and-or-gsi classes includes-excludes access-types) ...)
    (network-access
     (twrite "set up network access as follows:")	    ; configure ***
     (when (consp (second clause))			    ; Catch old rep: (network-access g2 ...)
       (loop for (accessor classes inclusion access-types) in (cdr clause)
	     as first = t then nil
	     doing
	 (if first (tformat "~%    ") (tformat ",~%    "))
	 (case inclusion
	   (include-additionally (twrite "allow"))
	   (exclude-additionally (twrite "prohibit"))
	   (exclude-absolutely (twrite "prohibit absolutely"))
	   (include (twrite "allow precisely"))		    ; These two are never generated.
	   (exclude (twrite "prohibit precisely")))
	 (when access-types
	   (twrite " ")
	   (write-symbol-list access-types '\, 'or))
	 (twrite " access")
	 (when classes
	   (write-list-of-classes-in-object-configuration classes " to "))
	 (case accessor
	   (any)
	   (g2 (twrite " by G2"))
	   (gsi (twrite " by GSI"))
	   (telewindows (twrite " by Telewindows"))
	   (g2-and-gsi (twrite " by G2 and GSI"))
	   (g2-and-telewindows (twrite " by G2 and Telewindows"))))))


    ;; (PROPRIETARY clause ...)
    (proprietary
     (twrite "restrict proprietary items as follows:")
     (loop for restriction-clause in (cdr clause)
	   as first = t then nil
	   doing
       (if first (tformat "~%  ") (tformat ";~%  "))
       (write-restriction-clause restriction-clause)))


    ;; (COMMENT (symbol string) ...)
    (comment
     (twrite "comment as follows:")
     (loop for (symbol string?) in (cdr clause)
	   as first = t then nil
	   doing
       (if first (tformat "~%   ") (tformat ",~%   "))
       (tformat "~(~a: ~s~)" symbol (or string? 'none))))

    
    (t
     (twrite clause))))



;;; The function `write-list-of-classes-in-object-configuration' write
;;; the list of classes, which is actually either a list or a symbol.
;;; If it is a symbol, then it means "this class".

(defun write-list-of-classes-in-object-configuration (classes &optional (prefix " "))
  (cond ((null classes))
	((atom classes)
	 (tformat "~(~Athis ~A~)" prefix classes))
	(t
	 (tformat "~Aany " prefix)
	 (write-symbol-list classes '\, 'or))))






;;;; User Restrictions: Writers




;;; `Write-user-restrictions' reverses both the order of the mode restrictions,
;;; and the order of the restriction clauses within a mode restriction. See
;;; comment in slot compiler for user-restrictions.

(defun write-user-restrictions (user-restrictions)
  (if (null user-restrictions)
      (twrite "none")
      (loop with length = (length user-restrictions)
	    for i from (-f length 1) downto 0 
	    do (write-mode-restriction (nth i user-restrictions))
	       (if (>f i 0) (tformat ";~%")))))





(defun write-mode-restriction (mode-restriction)
  (twrite
    (if (eq (first mode-restriction) 'when) "when in " "unless in "))
  (write-symbol-list (second mode-restriction) nil 'or "nothing")
  (tformat " mode:~%  ")		; should never be pluralized
  (loop with restriction-clauses = (cddr mode-restriction)
	with length = (length restriction-clauses)
	for i from (-f length 1) downto 0
	do (write-restriction-clause (nth i restriction-clauses))
	   (if (>f i 0) (tformat ";~%  "))))




;; This returns the type of annotation, which will be a symbol.

(def-substitution-macro annotation-clause-type (annotation)
  (first annotation))


(def-substitution-macro restriction-clause-operation-type (restriction-clause)
  (first restriction-clause))


;;; The macro `restriction-clause-restriction-type' returns the restriction-type
;;; of a clause: include,exclude,include-additionally, etc.  RESTRICTION-CLAUSE
;;; may be evaluated multiple times.

(def-substitution-macro restriction-clause-restriction-type (restriction-clause)
  (case (restriction-clause-operation-type restriction-clause)
    ((main-menu global-keyboard-command)
     (second restriction-clause))
    ((workspace-menu non-menu)
     (third restriction-clause))
    ((visibility table) 
     (fourth restriction-clause))
    (selecting
     (case (third restriction-clause)
       (nothing 'does)
       (t 'implies)))
    (selecting-absolutely
     (case (third restriction-clause)
       (nothing 'does-absolutely)
       (t 'implies-absolutely)))))

  

;;; The function `twrite-key-code-for-filters' writes the key code in lower
;;; case, properly escaped.  The default writer writes them in mixed case.

(defun twrite-key-code-for-filters (key-code)
  (key-case (key-index key-code)
    (mouse-wheel-forward
      (twrite "rolling ")
      (twrite-key-modifier-bits key-code nil)
      (twrite "the mouse wheel forward"))
    (mouse-wheel-backward
      (twrite "rolling ")
      (twrite-key-modifier-bits key-code nil)
      (twrite "the mouse wheel backward"))
    (mouse-hover
      (twrite "hovering ")
      (twrite-key-modifier-bits key-code nil)
      (twrite "the mouse"))
    (t
      (twrite "typing ")
      (let* ((write-symbols-parsably?
	       ;; Magic value escapes digits and punctuation.
	       'for-filters)
	     (string
	       (twith-output-to-text-string
		 (twrite-key-code key-code)))
	     (write-strings-parsably? t)) ; FIXME: Encloses everything in double quotes.
	(nstring-downcasew string)
	(twrite-string string)
	(reclaim-text-string string)))))

;; As far as I can tell, the only troublesome keycodes left are @ and \. --fmw
;; This software shouldn't have to know about it! -mhd


(defun twrite-class-spec-for-restrictions (class-spec this-string any-string)
  (cond ((null class-spec))
	((atom class-spec)
	 (tformat "~( ~a ~a~)" this-string class-spec))
	(t
	 (tformat " ~a " any-string)
	 (write-symbol-list class-spec '\, 'or))))



;;; The function `write-restriction-clause' writes an object-configuration clause
;;; from the user-interface branch of the grammar.

(defun write-restriction-clause (restriction-clause)
  (case (restriction-clause-operation-type restriction-clause)
    (main-menu
     (write-restriction-clause-1
       "main menu choices"
       nil
       nil
       (second restriction-clause)
       (cddr restriction-clause)))
    (global-keyboard-command
     (write-restriction-clause-1
       "global keyboard commands"
       nil
       nil
       (second restriction-clause)
       (cddr restriction-clause)))
    (workspace-menu
     (write-restriction-clause-1
       "menu choices for"
       nil
       (second restriction-clause)
       (third restriction-clause)
       (cdddr restriction-clause)))
    (non-menu
     (write-restriction-clause-1
       "non-menu choices for"
       nil
       (second restriction-clause)
       (third restriction-clause)
       (cdddr restriction-clause)))
    (selecting
     (write-restriction-clause-1
       "selecting any"
       nil
       (second restriction-clause)
       (case (third restriction-clause)
	 (nothing 'does)
	 (t 'implies))
       (third restriction-clause)))
    (selecting-absolutely
     (write-restriction-clause-1
       "selecting any"
       nil
       (second restriction-clause)
       (case (third restriction-clause)
	 (nothing 'does-absolutely)
	 (t 'implies-absolutely))
       (third restriction-clause)))
    (visibility
     (write-restriction-clause-1
       "attributes visible for"
       nil
       (second restriction-clause)
       (fourth restriction-clause)
       (third restriction-clause)))
    (table
     (write-restriction-clause-1
       (cond
	 ((null (third restriction-clause))
	  "table menu choices for any")
	 (t "table menu choices for the"))
       (cond
	 ((third restriction-clause)	  
	  (third restriction-clause)))
       (second restriction-clause)
       (fourth restriction-clause)
       (cddddr restriction-clause)))

    ;; Support the new keyboard and mouse bindings. (fmw 17-Aug-93)
    ((clicking pressing)
     (write-user-interface-clause restriction-clause))

    (constrain				; (constrain <kind> <classes> <info>)
     (gensym-dstruct-bind ((kind class-spec info)
			  (cdr restriction-clause))
       (case kind
	 (moving
	  (gensym-dstruct-bind ((dx . dy) info)
	    (tformat "constrain moving")
	    (twrite-class-spec-for-restrictions class-spec "this" "any")
	    (tformat " such that the item aligns on the grid (~d,~d)"
		     dx dy)))

	 (rectangle
	  ;; Notice the user-friendly ordering here.
	  (gensym-dstruct-bind  ((left right bottom top) info)
	    (tformat "constrain moving")
	    (twrite-class-spec-for-restrictions class-spec "this" "any")
	    (tformat " to the rectangle (~d,~d,~d,~d)" left right bottom top))))))))



;;; The function `write-user-interface-clause' twrites restriction clauses
;;; associated with the user interface (CLICKING and PRESSING), but not
;;; including SELECTING.

(defun write-user-interface-clause (user-interface-clause)
  (let ((type (first user-interface-clause))
	(key-code (second user-interface-clause))
	(action (third user-interface-clause))
	(class-spec (fourth user-interface-clause))
	(write-symbols-in-lower-case? t))

    (case type
      (clicking
       (twrite-mouse-button-for-filters key-code))
      (pressing
       (twrite-key-code-for-filters key-code))
      (t
       (dwarn "Unfamiliar UI clause type ~s" type)
       (twrite type)))

    (if (or (key-code-is-mouse-wheel-p key-code)
	    (key-code-is-mouse-hover-p key-code))
	(twrite-class-spec-for-restrictions class-spec "over this" "over any")
	(twrite-class-spec-for-restrictions class-spec "on this" "on any"))

    ;; Actions can be symbols or some special lists, or "nothing".
    (cond ((eq action 'nothing)
	   (twrite " does nothing"))
	  ((atom action)
	   (tformat " implies ")
	   (twrite action))
	  ((eq (car action) 'user-mouse-tracking)	    ; User mouse tracking action.
	   ;; See the event handler `user-mouse-tracking', which also knows this
	   ;; destructuring.
	   (gensym-dstruct-bind ((procedure-name class-spec motion) (cdr action))
	     (tformat "~( starts ~a as the mouse tracks" procedure-name)
	     (if motion
		 (twrite " continuously over")
		 (twrite " over"))
	     (twrite-class-spec-for-restrictions class-spec "this" "any"))))))


;;; `write-restriction-clause-1' takes N arguments and optionally emits a bit
;;; of text for each in order.  The resulting phrases are of the form:
;;;  <activity> [ <list-of-attributes> of any ] [ <list-of-classes> ] 
;;;      <extended-restriction-type> <choice-or-choices> [ <period> ]

(defun write-restriction-clause-1
    (activity-description
      attribute-name-or-list? object-description-or-list?
      restriction-type? choice-or-choice-list &optional write-period-at-end?)
  (twrite-string activity-description)
  (twrite-char #.%space)

  (when attribute-name-or-list?
    (if (null object-description-or-list?)
	(error "attribute-name-or-list? but no object-description-or-list?"))
    (cond ((atom attribute-name-or-list?)		; not really necessary!
	   (twrite attribute-name-or-list?))
	  ((class-qualified-name-list-p (car attribute-name-or-list?))
	   (write-name-denotation (car attribute-name-or-list?)))
	  (t (write-symbol-list attribute-name-or-list? nil 'or "nothing")))
    (twrite
      ;; Only when called from describe restrictions is object-description-or-list?
      ;; a string, namely "this item". 
      (if (text-string-p object-description-or-list?)
	  " of "
	  " of any ")))

  (when object-description-or-list?
    (if (atom object-description-or-list?)	; not really necessary!
	(twrite object-description-or-list?)
	(write-symbol-list object-description-or-list? nil 'or "nothing"))
    (twrite-char #.%space))
  
  (when restriction-type?
    (twrite
      (case restriction-type?
	(does "does ")
	(does-absolutely "absolutely does ")
	(implies "implies ")
	(implies-absolutely "absolutely implies ")
	(include "include: ")
	(exclude "exclude: ")
	(include-additionally "include additionally: ")
	(exclude-additionally "exclude additionally: ")
	(exclude-absolutely "exclude absolutely: "))))

  (case restriction-type?
    ((implies implies-absolutely does does-absolutely)
     (twrite choice-or-choice-list))
    (t
     ;; Either a list of command symbols, attribute-names, or name-denotations.
     (twrite-list choice-or-choice-list
		  :element-writer #'write-name-denotation
		  :empty "nothing"
		  :conjoiner nil)))

  (when write-period-at-end?
    (twrite-char #.%\.)))





;;;; Maintaining the Directory of User Modes





;;; `Add-or-delete-mode-names-from-directory-of-names' adds (or deletes if the
;;; second arg is non-nil) mode names from the directory of names for the
;;; category NON-BUILT-IN-G2-USER-MODE; however, note that the mode name
;;; ADMINISTRATOR is never added or deleted from this directory, since it is a
;;; built-in G2 user mode.  Mode-restrictions is assumed to be a list of mode
;;; restrictions, each of which has as its second element a list of mode names.

(defun add-or-delete-mode-names-from-directory-of-names
       (mode-restrictions delete-case?)
  (loop for mode-restriction in mode-restrictions
	do (loop for mode-name in (second mode-restriction)
		 do (add-or-delete-mode-name-from-directory-of-names
		      mode-name delete-case?))))

(defun add-or-delete-mode-name-from-directory-of-names (mode-name delete-case?)
  (unless (memq mode-name '(administrator proprietary))
    (funcall-symbol
      (if delete-case?
	  'delete-from-directory-of-names
          'add-to-directory-of-names)
      mode-name 'non-built-in-g2-user-mode)))

(defun add-or-delete-mode-names-from-item-configuration (item-configuration delete?)
  (loop for clause in item-configuration
	when (user-interface-clause-p clause)
	  do (add-or-delete-mode-names-from-directory-of-names (cdr clause) delete?)))





;;;; The Kb-Configuration System Table



;; Make the visible name for this be kb-configuration!!!

(def-system-frame (kb-configuration kb-restrictions) filters
  (object-configuration
    ((user-interface
       (unless (administrator)
	 (workspace-menu (item)
			 exclude-additionally
			 describe-configuration) ; New name for describe-restrictions.
	 (visibility
	   (kb-restrictions)
	   (main-menu-user-restrictions
	     keyboard-command-restrictions
	     initial-g2-user-mode-for-this-kb)
	   exclude)
	 ;; Hide (the alias of) the new slot name. (object-configuration)
	 (visibility
	   (item) (item-configuration)
	   exclude-additionally)))))
  (main-menu-user-restrictions				    ; Rename !!!
    nil system (type main-menu-restrictions))
  (global-keyboard-command-user-restrictions		    ; Rename !!!
    nil system (type global-keyboard-command-restrictions))

  (initial-g2-user-mode-for-this-kb
    nil system (type g2-user-mode-for-login?))

  ;; Will be a list of KB products required to run this KB. This slot
  ;; is edited only at Gensym in development mode, and is otherwise
  ;; a union of symbols inherited from all merged KBs. -ML-
  (required-kb-products nil system)
  (authorized-optional-modules-for-this-machine
    nil system not-user-editable do-not-save (type psueudo-authorized-optional-modules))
  (simulated-optional-modules
    t system do-not-save (type simulated-products?))
  (user-mode-aliases nil system save))

(defun-simple global-keyboard-command-user-restrictions-function (frame)
  (global-keyboard-command-user-restrictions frame))

(defun-simple main-menu-user-restrictions-function (frame)
  (main-menu-user-restrictions frame))

;; Introduced global-keyboard-command-user-restrictions. (MHD 9/25/91)
;; Required-kb-products is apparently a vistigal organ and should be removed - ben 12/31/91



;;; The `substitute-for-old-class for kb-restrictions' is kb-configuration.
;;; This causes read-frame-for-kb to instantiate a kb-configuration for any
;;; frames of class kb-restrictions in the KB.

(def-substitute-for-old-class kb-restrictions kb-configuration
  kb-format-revision-for-kb-restrictions-reclassification)

;; This was first entered into 4.0 development software on 6/24/94, and
;; corresponds to kb-format-revision-for-kb-restrictions-reclassification, q.v.



;;; See the introduction to section `Simulating Product Authorization', below,
;;; for details on this method

(def-class-method initialize-after-reading (kb-configuration)

  ;; System frames loaded from an older KB will have their old names.
  (when (eq (name-or-names-for-frame kb-configuration) 'kb-restrictions)
    (put-name-or-names-for-frame
      kb-configuration
      (compute-name-of-system-frame 'kb-configuration)
      nil						    ; We aren't really initializing here, since
							    ; we already have a name.
      ))
  (funcall-superior-method kb-configuration)
  (delete-frame-note-if-any 'note-status-of-simulated-product-authorization kb-configuration))



(define-slot-alias authorized-optional-modules authorized-optional-modules-for-this-machine
  kb-restrictions)

;; Note that this is the same slot name as the users see on their ok objects.
;; That's OK.  (MHD 9/22/93)


(define-slot-alias keyboard-command-restrictions global-keyboard-command-user-restrictions)

;; User-visible attribute name changed to keyboard-command-restrictions for simplicity
;; 2/11/92.  (MHD 2/11/92)



(def-class-method install-system-table (kb-configuration)
  (add-or-delete-mode-names-from-directory-of-names
    (main-menu-user-restrictions kb-configuration) nil)
  (add-or-delete-mode-names-from-directory-of-names
    (global-keyboard-command-user-restrictions kb-configuration) nil)
  (when (initial-g2-user-mode-for-this-kb kb-configuration)
    (add-or-delete-mode-name-from-directory-of-names
      (initial-g2-user-mode-for-this-kb kb-configuration) nil))
  (setup-current-simulated-product-authorization))


(def-class-method deinstall-system-table (kb-configuration)
  (add-or-delete-mode-names-from-directory-of-names
    (main-menu-user-restrictions kb-configuration) t)
  (add-or-delete-mode-names-from-directory-of-names
    (global-keyboard-command-user-restrictions kb-configuration) t)
  (when (initial-g2-user-mode-for-this-kb kb-configuration)
    (add-or-delete-mode-name-from-directory-of-names
      (initial-g2-user-mode-for-this-kb kb-configuration) t))
  (setup-current-simulated-product-authorization))







;;;; User Restrictions: Compilers, Slot Putters




(def-slot-value-compiler main-menu-restrictions (parse-result)
  (compile-user-restrictions parse-result t))



(def-slot-value-compiler global-keyboard-command-restrictions (parse-result)
  (compile-user-restrictions parse-result t))



(def-slot-putter main-menu-user-restrictions
		 (kb-restrictions-instance main-menu-user-restrictions)
  (when (system-table-installed-p kb-restrictions-instance)
    (add-or-delete-mode-names-from-directory-of-names
      (main-menu-user-restrictions kb-restrictions-instance) t)
    (add-or-delete-mode-names-from-directory-of-names	; make less inefficient?
      main-menu-user-restrictions nil))
  (setf (main-menu-user-restrictions kb-restrictions-instance)
	main-menu-user-restrictions)
  (when (system-table-installed-p kb-restrictions-instance)
    (decache-dynamic-menus 'kb-configuration))
  main-menu-user-restrictions)  



(def-slot-putter global-keyboard-command-user-restrictions
                 (kb-restrictions-instance global-keyboard-command-user-restrictions)
  (when (system-table-installed-p kb-restrictions-instance)
    (add-or-delete-mode-names-from-directory-of-names
      (global-keyboard-command-user-restrictions kb-restrictions-instance) t)
    (add-or-delete-mode-names-from-directory-of-names	; make less inefficient?
      global-keyboard-command-user-restrictions nil))
  (setf (global-keyboard-command-user-restrictions kb-restrictions-instance)
	global-keyboard-command-user-restrictions)
  (when (system-table-installed-p kb-restrictions-instance)
    (decache-dynamic-menus 'kb-configuration))
  global-keyboard-command-user-restrictions)


;; Only for the old user-restrictions do we allow "when in proprietary mode".
;; That clause is excised and put in the proper place when the restrictions
;; are copied over into the item config.

(def-slot-value-compiler user-restrictions (parse-result)
  (compile-user-restrictions parse-result nil))



(defun compile-user-restrictions (form disallow-proprietary-mode?)
  (cond
    ((null form) nil)
    ((eq form 'none) nil)
    (t
     ;; if problem, return bad phrase and error string;
     ;; otherwise, just remove leading ";" 
     (loop with unreversed-form = (cdr form)
	   for mode-restriction in unreversed-form
	   as when-or-unless = (first mode-restriction)
	   as administrator? = (memq 'administrator (second mode-restriction))
	   as proprietary? = (memq 'proprietary (second mode-restriction))
	   as problem-string?
	      = (cond ((and administrator?
			    (eq when-or-unless 'when))
		       "You may not restrict administrator mode.") ; Note A
		      ((and proprietary? disallow-proprietary-mode?)
		       "You may not restrict proprietary mode here.")
		      ((and proprietary?
			    (eq when-or-unless 'unless))
		       "You may not restrict proprietary mode using UNLESS."))
	   when problem-string?
	     return (values bad-phrase (copy-text-string problem-string?))
	   finally
	     
	     ;; User restrictions are to be scanned by the restriction computing
	     ;; routines in bottom to top order from the users perspective.
	     ;; Since it is more efficient to scan lists forward, they will be
	     ;; stored in reversed order, and reversed again upon printing.  The
	     ;; following reverses the restriction clauses in each mode
	     ;; restriction, and reverses the order of the mode restrictions as
	     ;; well.
	     (return
	       (loop for mode-restriction in unreversed-form
		     do (setf (cddr mode-restriction)
			      (nreverse (cddr mode-restriction)))
		     finally
		       (return
			 (nreverse unreversed-form))))))))

;; Note A The above message had been "You may not restrict administrator mode."
;; but that needed clarification because when we added the next message about
;; proprietary mode. (MHD 3/23/90)

;; Changed the message back since it is very confusing.  In fact, you cannot
;; restrict administrator mode using ANYTHING, although the grammar provides a
;; reminder only for the case "when in administrator mode ...".  The phrase
;; "unless in user mode ..." would seem to restrict administrator mode, but it
;; does not.  Moreover, it does not generate a warning. -fmw, 7/26/94




;;; The slot-putter `user-restrictions' actually puts the value into the item
;;; configuration slot, instead, setting the user-restrictions slot to NIL.  If
;;; the frame is proprietary, it silently ignores the put entirely.

(def-slot-putter user-restrictions (kb-frame user-restrictions initializing?)
  (cond
    ((and (not initializing?)
	  (proprietary-p kb-frame))	    ; never allow editing of user restrictions
					    ;   of proprietary frame
					    ; Should we have a notification to the
					    ;   user in this case?! (MHD 12/5/90)

     (reclaim-slot-value user-restrictions) ; Note: the system table kb-restrictions
     (values				    ;   is never a proprietary frame (MHD 10/15/91)
       (user-restrictions kb-frame)
       t))				    ; 2nd value says not to reclaim old value

    (t
     (add-or-delete-mode-names-from-directory-of-names (user-restrictions kb-frame) t)
     (add-or-delete-mode-names-from-directory-of-names user-restrictions nil)

     ;; Be careful to set the new value with the old value intact, for the sake
     ;; of journalling.
     (let ((old-value (user-restrictions kb-frame)))
       ;; The slot stays NIL.
       (setf (user-restrictions kb-frame) nil)
       (reclaim-slot-value old-value))

     (copy-user-restrictions-into-object-configuration kb-frame user-restrictions)
     (reclaim-slot-value user-restrictions)
     (values					;   is never a proprietary frame (MHD 10/15/91)
       (item-configuration kb-frame)
       t))))

;; Note that the next slot putter, i.e. class-restrictions, is almost identical.



;;; The slot-putter `class-restrictions' actually puts the value into the
;;; instance configuration slot, instead, setting the class-restrictions slot
;;; to NIL.  If the definition is proprietary, it silently ignores the put
;;; entirely.

(def-slot-putter class-restrictions (definition class-restrictions initializing?)
  (cond
    ((and (not initializing?)
	  (proprietary-p definition))
     (reclaim-slot-value class-restrictions)
     (values (class-restrictions definition)
	     t))
    (t
     (add-or-delete-mode-names-from-directory-of-names (class-restrictions definition) t)
     (add-or-delete-mode-names-from-directory-of-names class-restrictions nil)

     ;; Be careful to set the new value with the old value intact, for the sake
     ;; of journalling.
     (let ((old-value (class-restrictions definition)))
       ;; The slot stays NIL.
       (setf (class-restrictions definition) nil)
       (reclaim-slot-value old-value))

     ;; Copy over to instance configuration
     (copy-class-restrictions-into-instance-configuration definition class-restrictions)
     (reclaim-slot-value class-restrictions)
     (values (class-restrictions definition) t))))

;; Note that the previous slot-putter, i.e. user-restrictions, is almost identical.



(def-slot-putter initial-g2-user-mode-for-this-kb
    (kb-restrictions-instance new-value initializing?)
  (when (system-table-installed-p kb-restrictions-instance)
    ;; delete old mode, if any, from mode name directory
    (unless (or initializing?
		(null (initial-g2-user-mode-for-this-kb kb-restrictions-instance)))
      (add-or-delete-mode-name-from-directory-of-names
	(initial-g2-user-mode-for-this-kb kb-restrictions-instance) t))
    ;; add new mode, if any, to mode name directory
    (unless (null new-value)
      (add-or-delete-mode-name-from-directory-of-names new-value nil)))
  (setf (initial-g2-user-mode-for-this-kb kb-restrictions-instance) new-value)
	              ;;; change user mode for each workstation if it's in running status
  (when (and system-is-running (not system-has-paused))
  (loop for workstation in workstations-in-service do    
     (enter-change-user-mode-in-running 'changing-mode workstation))))



(def-slot-value-writer main-menu-restrictions (value)
  (write-user-restrictions value))

(def-slot-value-writer global-keyboard-command-restrictions (value)
  (write-user-restrictions value))


;;; Here is where we make "the user-restrictions of x" work, even though the
;;; user-restrictions slot is now always NIL.  We peek over into the
;;; object-configuration slot and print only the CONFIGURE annotations.

(def-slot-value-writer user-restrictions (value kb-frame)
  (declare (ignore value))
  (write-user-restrictions-from-object-configuration (object-configuration kb-frame)))

(def-slot-value-writer class-restrictions (value definition)
  (declare (ignore value))
  (write-user-restrictions-from-object-configuration (instance-configuration definition)))


;;; Write annotation clauses as if there were user restrictions.

;;; The function `write-user-restrictions-from-object-configuration' writes out
;;; the user-interface clauses from an object-configuration so that it
;;; looks like user restrictions.

(defun write-user-restrictions-from-object-configuration (object-configuration)
  (loop with length = (length object-configuration)
	with some = nil
	for i from (-f length 1) downto 0 
	for clause = (nth i object-configuration)
	when (user-interface-clause-p clause)
	  do (if some (tformat ";~%"))
	     (write-user-restrictions (cdr clause))
	     (setq some t)
	finally
	  (unless some
	    (twrite "none"))))

;; Yikes.  We need to scan proprietary clauses, too!!




;;;; Setf-able configuration clauses


;;; Routines in this section provide a simple get/set API for managing the
;;; contents of the item-configuration slot.  System procedures expose
;;; parts of this API to the user level.

;;; Missing from the manager's repertoire are the clauses pertaining to menu
;;; choices and propietary restrictions.  It's too painful to manage all the
;;; include/exclude/additionally/absolutely crap.

;; Unfortunately, these routines treat proprietary like a user-mode once again.
;; Separating out proprietary "mode" from user modes was probably a mistake, at
;; least in the internal representation.  Configs are so hard for users to
;; understand anyways that the additional semantic sloppiness in calling
;; proprietary a mode was probably negligible.

;; These routines do horrible, horrible list structure hacking, thanks to the
;; bogus internal representation of configs.

;; -fmw, 8/9/95


;;; The system procedures available are:

;;; g2-set-movement-limits (item, mode, left, right, bottom, top);
;;; g2-get-movement-limits (item, mode);
;;; g2-clear-movement-limits (item, mode);

;;; g2-set-movement-grid (item, mode, dx, dy);
;;; g2-get-movement-grid (item, mode);
;;; g2-clear-movement-grid (item, mode);

;; Someday:

;; g2-set-comment (item, symbol, string);
;; g2-get-comment (item, symbol);
;; g2-clear-comment (item, symbol);

;; g2-set-declaration (item, symbol, classes, value);
;; g2-get-declaration (item, symbol, classes);
;; g2-clear-declaration (item, symbol, classes);

;; g2-set-key-binding (item, mode, classes, keysym, function)
;; g2-get-key-binding (item, mode, classes, keysym)
;; g2-clear-key-binding (item, mode, classes, keysym)

;; Classes can be False, meaning this item, or a symbol naming a class.
;; Someday we may allow G2 lists of class names here.
;; Keysym is the symbol naming the key, eg, CONTROL+A.  If the keysym is
;; MOUSE-SELECT, then this manages a "selecting any .." clause.


;;; The substitution-macro `restrictions-pattern-match' returns the binding for
;;; the wildcard if the pattern matches the clause.  A pattern is simply a list
;;; of atoms, with at most one atom being the symbol *.

(def-substitution-macro restrictions-pattern-match (clause pattern)
  (let ((binding nil))
    (when (and (=f (length clause) (length pattern))
	       (loop for pattern-element in pattern
		     for clause-element in clause
		     as star? = (eq pattern-element '*)
		     if star?
		       do (setq binding clause-element)
		     always (or star?
				(equal pattern-element clause-element))))
      binding)))


(def-substitution-macro find-restrictions-pattern (clauses pattern)
  (loop for clause in clauses
	as binding? = (restrictions-pattern-match clause pattern)
	when binding?
	  return (values clause binding?)))


(defun ensure-user-interface-section (item)
  ;; Looking for (user-interface ...)
  (or (assq 'user-interface (item-configuration item))
      (let ((clause (slot-value-list 'user-interface)))
	(slot-value-push clause (item-configuration item))
	clause)))


(defun ensure-proprietary-section (item)
  ;; Looking for (proprietary ...)
  (or (assq 'proprietary (item-configuration item))
      (let ((clause (slot-value-list 'proprietary)))
	(slot-value-push clause (item-configuration item))
	clause)))


;;; The function `ensure-user-mode-section' returns a clause of the form
;;; (when|unless (mode)) for user modes, and a clause of the form (proprietary)
;;; for proprietary mode.

(defun ensure-user-mode-section (item when-or-unless mode)
  (case mode
    (proprietary
     (ensure-proprietary-section item))
    (t
     ;; Looking for (when|unless (mode) ...)
     (let ((user-interface-section
	     (ensure-user-interface-section item)))
       (or
	 (loop for clause in (cdr user-interface-section)
	       as (type modes) = clause
	       when (and (eq type when-or-unless)
			 (eq (first modes) mode)
			 (null (rest modes)))
		 return clause)
	 (let ((clause (slot-value-list when-or-unless (slot-value-list mode))))
	   (slot-value-push clause (cdr user-interface-section))
	   clause))))))


;;; The function `ensure-user-interface-clause' ensure that there
;;; is a user-interface clause, active in the given mode, which
;;; matches the given pattern.  The clause is returned.

(defun ensure-user-interface-clause (item when-or-unless mode pattern)
  (case mode
    (proprietary
     (let ((proprietary-section
	     (ensure-proprietary-section item)))
       (or (find-restrictions-pattern (cdr proprietary-section) pattern)
	   (let ((clause (copy-list-using-slot-value-conses pattern)))
	     (slot-value-push clause (cdr proprietary-section))
	     clause))))
    (t
     (let ((user-mode-section
	     (ensure-user-mode-section item when-or-unless mode)))
       (or (find-restrictions-pattern (cddr user-mode-section) pattern)
	   (let ((clause (copy-list-using-slot-value-conses pattern)))
	     (slot-value-push clause (cddr user-mode-section))
	     clause))))))


;;; The function `find-item-user-interface-clause' returns the clause, if any,
;;; which matches the given pattern.  The second value is the binding for the
;;; optional wildcard in the pattern.

(defun find-user-interface-clause (item when-or-unless mode pattern)
  (block search
    (case mode
      (proprietary
       (loop for major-clause in (item-configuration item) doing
	 (when (proprietary-items-clause-p major-clause)
	   (multiple-value-bind (clause? binding?)
	       (find-restrictions-pattern (cdr major-clause) pattern)
	     (when clause?
	       (return-from search (values clause? binding?)))))))

      (t
       (loop for major-clause in (item-configuration item) doing
	 (when (user-interface-clause-p major-clause)
	   (loop for mode-clause in (cdr major-clause)
		 as (type modes) = mode-clause
		 doing
	     (when (and (eq type when-or-unless)
			(eq (first modes) mode)
			(null (rest modes)))
	       (multiple-value-bind (clause? binding?)
		   (find-restrictions-pattern (cddr mode-clause) pattern)
		 (when clause?
		   (return-from search (values clause? binding?))))))))))))

;; This will find ONLY clauses of the form (when|unless (mode) ...), which are
;; the only kinds which created by these system procedures.




;;; The function `delete-user-interface-clause' deletes the user-interface
;;; clause which is EQ to the given one.  Containing lists are deleted if
;;; then have become empty.  The clause itself is NOT reclaimed.

(defun delete-user-interface-clause (item mode clause)
  (block search
    (case mode
      (proprietary
       (loop for major-clause in (item-configuration item) doing
	 (when (proprietary-items-clause-p major-clause)

	   (when (memq-p-macro clause (cdr major-clause))   ; Found?
	     (setf (cdr major-clause)
		   (delete-slot-value-element clause (cdr major-clause)))
	     (when (null (cdr major-clause))
	       ;; Delete and reclaim the now empty proprietary clause.
	       (setf (item-configuration item)
		     (delete-slot-value-element major-clause 
						(item-configuration item)))
	       (reclaim-slot-value-tree major-clause))
	     (return-from search clause)))))

      (t
       (loop for major-clause in (item-configuration item) doing
	 (when (user-interface-clause-p major-clause)
	   (loop for mode-clause in (cdr major-clause) doing

	     (when (memq-p-macro clause (cddr mode-clause))    ; Found?
	       (setf (cddr mode-clause)
		     (delete-slot-value-element clause (cddr mode-clause)))

	       (when (null (cddr mode-clause))
		 ;; Delete and reclaim the now empty mode clause.
		 (setf (cdr major-clause)
		       (delete-slot-value-element mode-clause (cdr major-clause)))
		 (reclaim-slot-value-tree mode-clause)

		 (when (null (cdr major-clause))
		   ;; Delete and reclaim the now empty user-interface clause.
		   (setf (item-configuration item)
			 (delete-slot-value-element major-clause 
						    (item-configuration item)))
		   (reclaim-slot-value-tree major-clause)))

	       (return-from search clause)))))))))



;;; The macro `with-mutations-to-slot-value' allows mutations to a slot's value
;;; (via rplaca, etc), to be properly reflected in the slot's representations
;;; and undo list.  It temporarily replaces the given slot of the item with a
;;; copy.  Then after the body has edited the copy, we put back the old value
;;; and use change-slot-value to set the new-value in the approved fashion.

(defmacro with-mutations-to-slot-value ((item slot-name) &body body)
  (avoiding-variable-capture (item &aux old-value new-value)
    `(let* ((,old-value
	       (,slot-name ,item))
	    (,new-value
	       (copy-for-slot-value ,old-value)))

       (setf (,slot-name ,item) ,new-value)

       (multiple-value-prog1
	   (progn ,@body)

	 ;; If was initially nil, or if the body changed the first cons.
	 (setq ,new-value (,slot-name ,item))
	 
	 (setf (,slot-name ,item) ,old-value)
	 
	 (cond ((equal ,old-value ,new-value)
		(reclaim-slot-value ,new-value))
	       (t
		(change-slot-value ,item ',slot-name ,new-value)))))))

			  
       
(defmacro with-mutations-to-item-configuration ((item) &body body)
  `(with-mutations-to-slot-value (,item object-configuration)
     ,@body))



(defmacro filters-stack-error (message &rest args)
  `(stack-error cached-top-of-stack ,message ,@args))


  
(def-substitution-macro check-clause-type-and-mode-consistency
    (when-or-unless user-mode)
  (cond ((not (memq-p-macro when-or-unless '(when unless)))
	 (filters-stack-error "The type of clause must be the symbol WHEN or UNLESS.")
	 nil)

	((and (eq when-or-unless 'when)
	      (eq user-mode 'administrator))
	 (filters-stack-error "You may not restrict administrator mode.")
	 nil)

	((and (eq when-or-unless 'unless)
	      (eq user-mode 'proprietary))
	 (filters-stack-error "Proprietary restrictions require a clause type of WHEN.")
	 nil)
	(t
	 t)))


;;;; System procedures which manage item configurations



;;; The function `g2-set-movement-limits' sets the rectangle in workspace
;;; units which the item is constrained to remain entirely inside, when the
;;; item is moved by the user.

(defun-for-system-procedure g2-set-movement-limits
    ((item item)
     (when-or-unless symbol)
     (user-mode symbol)
     (left integer)
     (right integer)
     (bottom integer)
     (top integer))
  (declare (keeps-g2-local-variables-valid t))

  (when (check-clause-type-and-mode-consistency when-or-unless user-mode)
    (with-mutations-to-item-configuration (item)
      (let* ((clause
	       (ensure-user-interface-clause
		 item when-or-unless user-mode '(constrain rectangle item *)))
	     (rectangle
	       (fourth clause)))
	
	(cond ((eq rectangle '*)
	       (setf (fourth clause)
		     (slot-value-list left right bottom top)))
	      
	      ((consp rectangle)
	       (setf (first rectangle) left
		     (second rectangle) right
		     (third rectangle) bottom
		     (fourth rectangle) top)))))))



;;; The function `g2-get-movement-limits' returns five values, the current
;;; limits for item in the given user mode, left right bottom top, and a
;;; boolean which is true if any limits exist at all.

(defun-for-system-procedure g2-get-movement-limits
    ((item item)
     (when-or-unless symbol)
     (user-mode symbol))
  (declare (values integer integer integer integer truth-value)
	   (keeps-g2-local-variables-valid t))
  (let* ((clause?
	   (find-user-interface-clause
	     item when-or-unless user-mode '(constrain rectangle item *)))
	 (rectangle?
	   (and clause? (fourth clause?))))
    (cond (rectangle?
	   (gensym-dstruct-bind ((left right bottom top) rectangle?)
	     (values left right bottom top truth)))
	  (t
	   (values 0 0 0 0 falsity)))))


(defun-for-system-procedure g2-clear-movement-limits
    ((item item)
     (when-or-unless symbol)
     (user-mode symbol))
  (declare (keeps-g2-local-variables-valid t))
  (with-mutations-to-item-configuration (item)
    (let ((clause?
	    (find-user-interface-clause
	      item when-or-unless user-mode '(constrain rectangle item *))))
      (when clause?
	(delete-user-interface-clause item user-mode clause?)
	(reclaim-slot-value-tree clause?)))))

;; It might be useful to allow wild cards here, to remove limits for all modes
;; and polarities.



;;; The system procedure `g2-set-movement-grid' sets the size of the alignment
;;; grid for the given item and user-mode.

(defun-for-system-procedure g2-set-movement-grid
    ((item item)
     (when-or-unless symbol)
     (user-mode symbol)
     (dx integer)
     (dy integer))
  (when (check-clause-type-and-mode-consistency when-or-unless user-mode)
    (with-mutations-to-item-configuration (item)
      (let* ((clause
	       (ensure-user-interface-clause
		 item when-or-unless user-mode '(constrain moving item *)))
	     (grid
	       (fourth clause)))
	(cond ((eq grid '*)
	       (setf (fourth clause)
		     (slot-value-cons dx dy)))
	      ((consp grid)
	       (setf (car grid) dx
		     (cdr grid) dy)))))))


;;; The function `g2-get-movement-grid' returns the size of alignment 
;;; grid for the given item and user-mode, as well as a third value
;;; indicating whether the grid is present at all.

(defun-for-system-procedure g2-get-movement-grid
    ((item item)
     (when-or-unless symbol)
     (user-mode symbol))
  (declare (values integer integer truth-value))
  (let* ((clause?
	   (find-user-interface-clause
	     item when-or-unless user-mode '(constrain moving item *)))
	 (grid?
	   (and clause? (fourth clause?))))
    (cond (grid?
	   (values (car grid?) (cdr grid?) truth))
	  (t
	   (values 0 0 falsity)))))


(defun-for-system-procedure g2-clear-movement-grid
    ((item item)
     (when-or-unless symbol)
     (user-mode symbol))
  (with-mutations-to-item-configuration (item)
    (let ((clause?
	    (find-user-interface-clause
	      item when-or-unless user-mode '(constrain moving item *))))
      (when clause?
	(delete-user-interface-clause item user-mode clause?)
	(reclaim-slot-value-tree clause?)))))




;;;; Item (or Object) Configuration



;;; The slot-putter `object-configuration' handles proprietary frames and the
;;; updating of workspace background images.

;;; Any given KB will contain either only user-restrictions or only
;;; object-configuration, so we can be sure that one will not clobber the other.
;;; Once the KB is running, we may get put-requests via either, but we actually
;;; store only into the object-configuration slot.

(def-slot-putter object-configuration (block new-configuration initializing?)
  (cond ((and (not initializing?)
	      (proprietary-p block))			    ; never allow editing of user restrictions
							    ;   of proprietary frame
	 (reclaim-slot-value new-configuration)
	 (values (object-configuration block)
		 t))
	(t
	 (let ((old-configuration (object-configuration block)))

	   (setq new-configuration (massage-configuration-value new-configuration))

	   (add-or-delete-mode-names-from-item-configuration old-configuration t)
	   (add-or-delete-mode-names-from-item-configuration new-configuration nil)

	   (without-consistency-analysis (block)
	     (setf (object-configuration block) new-configuration))

	   (unless (equal old-configuration new-configuration)
	     (propagate-change-in-object-configuration 'item-configuration block
						       old-configuration new-configuration))

	   (values new-configuration nil)))))


(def-slot-putter instance-configuration (definition new-configuration initializing?)
  (cond
    ((and (not initializing?)
	  (proprietary-p definition))
     (reclaim-slot-value new-configuration)
     (values (instance-configuration definition)
	     t))
    (t
     (let ((old-configuration (instance-configuration definition)))

       (setq new-configuration (massage-configuration-value new-configuration))
       
       (add-or-delete-mode-names-from-item-configuration old-configuration t)
       (add-or-delete-mode-names-from-item-configuration new-configuration nil)

       (without-consistency-analysis (definition)
	 (setf (instance-configuration definition) new-configuration))

       (unless (equal old-configuration new-configuration)
	 (propagate-change-in-object-configuration 'instance-configuration definition
						   old-configuration new-configuration))

       (values new-configuration) nil))))

(def-slot-value-reclaimer instance-configuration (value frame)
  (add-or-delete-mode-names-from-item-configuration value t)
  (reclaim-slot-value value)
  ;; Leave it in a consistent state. There were problems in drawing
  ;; during the recursive descent of delete-frame.
  (setf (instance-configuration frame) nil))



;;; The function `massage-configuration-value' destructively updates an old
;;; representation for declaration clauses.

(defun massage-configuration-value (configuration)
  (loop for clause in configuration doing
    (when (and (consp clause)
	       (eq (car-of-cons clause) 'declare))
      ;; Mutate the old (DECLARE property value class) into
      ;; (DECLARATION class property value)
      (gensym-dstruct-bind ((property value class) (cdr clause))
	(setf (first clause) 'declaration
	      (second clause) class
	      (third clause) property
	      (fourth clause) value))))
  configuration)




;;; The function `propagate-change-in-object-configuration' is used mainly to
;;; handle compilation issues, but we also use it as a hook to decache native
;;; menu bars which depend on restrictions.

(defun propagate-change-in-object-configuration (type-of-configuration
						  block
						  old-configuration new-configuration)
  (let ((stable-hierarchy-change?
	  (not
	    (equal (get-property-clause old-configuration 'stable-hierarchy)
		   (get-property-clause new-configuration 'stable-hierarchy))))
	(inline-change?
	  (not
	    (equal (get-property-clause old-configuration 'inlineable)
		   (get-property-clause new-configuration 'inlineable))))
	(stable-for-dependent-compilations-change?
	  (not
	    (equal (get-property-clause old-configuration 'stable-for-dependent-compilations)
		   (get-property-clause new-configuration 'stable-for-dependent-compilations))))
	(independent-for-all-compilations-change?
	  (not
	    (equal (get-property-clause old-configuration 'independent-for-all-compilations)
		   (get-property-clause new-configuration 'independent-for-all-compilations))))
	(all-items-processed? nil))

    ;; Changing the object-configuration on the kb-configuration system table
    ;; affects the menu bar.
    (when (and (of-class-p block 'kb-configuration)
	       (system-table-installed-p block))
      (decache-dynamic-menus 'kb-configuration))

    ;; Have compiler declarations changed in any way?
    (when (or stable-for-dependent-compilations-change?
	      independent-for-all-compilations-change?)
      ;; Loop over all affected items.
      ;; The conservative choice is to loop over all items.
      ;; Optimization: loop only over compilable things: procedures, rules, formulae, etc.

      ;; Note that the analysis is done when the stability and dependence status
      ;; has changed in any way.  It is necessary when the configuration is newly
      ;; independent or unstable because items dependent on stable items may be
      ;; affected by this change. It is also necessary when the configuration is
      ;; newly stable or dependent.  This change would not invalidate dependent
      ;; items, but it could validate dependent items that were previously
      ;; invalid.
      (cond ((and (eq type-of-configuration 'item-configuration)
		  (eq block kb-restrictions))
	     ;; Edited kb-restrictions: scan every item in the KB.

	     ;; All items, both newly dependent and newly independent, need
	     ;; analysis.

	     ;; Note that the approach of the other cases (below) of iterating
	     ;; over all items, collecting items referring to each one (i.e.,
	     ;; deferring the analysis), and then analyzing the collected items,
	     ;; is too slow for this case.  Instead, analyze every item.
	     
	     (loop for item being class-instances of 'item doing
	       (check-consistency-analysis item))
	     (setq all-items-processed? t))

	    ((and (eq type-of-configuration 'instance-configuration)
		  (name-or-names-for-frame block))
	     ;; Edited the instance-configuration in an object definition:
	     ;; loop over all instances of this class.
	     (defer-some-consistency-analysis
	       (loop for item being class-instances of
		     (name-or-names-for-frame block) doing
		 (handle-dependent-or-stable-status-change-for-item item))))
	    (t
	     ;; Call on every item at or below this one in the document
	     ;; hierarchy.
	     (defer-some-consistency-analysis
	       (note-dependent-or-stable-status-change block)))))
    (cond ((and stable-hierarchy-change?
		(not all-items-processed?))
	   (handle-stable-hierarchy-or-inline-status-change-for-item block))
	  ((and inline-change?
		(not all-items-processed?))
	   (handle-stable-hierarchy-or-inline-status-change-for-item block t)))))



;;; The simple function `note-dependent-or-stable-status-change' notes a possible
;;; change to the stability or independance of block and all its inferiors.  This
;;; is called from the TRANSFER action via note-change-to-superior-of-block-or-blocks.

(defun-simple note-dependent-or-stable-status-change (block)
  (handle-dependent-or-stable-status-change-for-item-for-filters block nil))



;;; `Handle-dependent-or-stable-status-change-for-item-for-filters', a simple
;;; function, maps over all inferiors of block in the document hierarchy.  The
;;; inverse of `superior-frame'.

(defun-simple handle-dependent-or-stable-status-change-for-item-for-filters
    (block parent)
  (declare (ignore parent))
  (when (item-p block)
    (handle-dependent-or-stable-status-change-for-item block))
  (funcall-function-to-inferior-blocks
    block #'handle-dependent-or-stable-status-change-for-item-for-filters))





;;; The slot-putter `frame-style' updates the workspace image as required.  It
;;; should not actually propagate changes to ifnerior blocks, since frame styles
;;; are not inherited in 4.0.  It is here to pick up consistency analysis.

(def-slot-putter frame-style (workspace frame-style initializing?)
  (let ((old-frame-style (frame-style workspace)))
    (without-consistency-analysis (workspace)
      (setf (frame-style workspace) frame-style))
    (unless (or initializing?
		(equal frame-style old-frame-style))
      (reconsider-formatting workspace))
    (values frame-style nil)))



(def-slot-value-compiler object-configuration (parse-result frame-for-this-parse)
  (when (and (consp parse-result)
	     (eq (first parse-result) '\;))
    (setq parse-result (cdr parse-result)))
  (compile-object-configuration parse-result frame-for-this-parse))



;;; The function `compile-object-configuration' compiles user-interface claues
;;; as user restrictions.

(defun compile-object-configuration (form frame-for-this-parse)
  (let ((trouble? nil)
	(result nil))
    (unless (or (null form) (eq form 'none))
      ;; Reverse the toplevel list, sublists of mode configuration,
      ;; and sublists of clauses.
      (loop for clause in form
	    until trouble?
	    doing

	(cond ((user-interface-clause-p clause)
	       (multiple-value-bind (answer string)
		   (compile-user-restrictions clause t)	    ; Happens to work on whole clause.
		 (cond ((eq answer bad-phrase)
			(setq trouble? string))
		       (t
			(setf (cdr clause) answer)))))
	      
	      ((network-access-clause-p clause)
	       (loop for phrase in (network-access-clause-phrases clause)
		     as access-types = (network-access-phrase-access-types phrase)
		     doing
		 (when (and (memq 'connect access-types)
			    (not (frame-of-class-p frame-for-this-parse 'kb-restrictions)))
		   (setf trouble?
			 (copy-text-string
			   "The network access type `connect' is only valid in the KB-CONFIGURATION system table."))))))

	(unless (empty-item-configuration-clause-p clause)   ; Remove empty clauses.
	  (phrase-push clause result)))

      (cond (trouble?
	     (values bad-phrase trouble?))
	    (t
	     result)))))



;;; The defparameter `things-to-rename-in-restrictions' is an alist of
;;; (old-name new-name) used to update 3.0 restrictions to 4.0.  Both names
;;; must be the user-visible names (ie, the alias if a slot name).

(defparameter things-to-rename-in-restrictions
  '((user-restrictions item-configuration)
    (class-restrictions instance-configuration)
    (describe-restrictions describe-configuration)
    (kb-restrictions kb-configuration)
    (superior-class direct-superior-classes)
    (attributes-specific-to-class class-specific-attributes)
    (default-settings attribute-initializations)))
		
;; Note: Currently this renaming happens for any symbol found in old
;; restrictions.  For example, if some loser used one of these names as a
;; user-menu-choice in 3.0 we will clobber it in the translation.  Pretty dumb.



;;; The function `rename-slots-in-restrictions' dumbly walks over the entire
;;; tree, renaming symbols in 3.0 restrictions according to the alist above.
;;; The list structure is mutated in-place.

(defun rename-slots-in-restrictions (restrictions)
  (when (consp restrictions)
    (let* ((element (car restrictions))
	   (new-element? (second (assq element things-to-rename-in-restrictions))))
      (when new-element?
	(setf (car restrictions) new-element?))
      (rename-slots-in-restrictions (car restrictions))
      (rename-slots-in-restrictions (cdr restrictions))))
  restrictions)

;; Other possibilities: main-menu-user-restrictions, keyboard-command-restrictions.



;;; The function `convert-restrictions-into-object-configuration' creates a new
;;; value for object-configuration whose user-interface and proprietary clauses
;;; are taken from the user restrictions.  The result is newly consed, sharing
;;; no structure with the inputs.

(defun convert-user-restrictions-into-object-configuration
    (object-configuration user-restrictions)
  (let ((user-interface-clauses ())
	(proprietary-clauses ()))
    
    ;; Tease out the user-restrictions which apply to proprietary "mode".
    (loop for mode-restriction in user-restrictions
	  as when-or-unless = (first mode-restriction)
	  as modes = (second mode-restriction)
	  as body = (cddr mode-restriction)
	  as proprietary-p = (memq 'proprietary modes)
	  as new-modes = (loop for mode in modes
			       unless (eq mode 'proprietary)
				 collect mode using slot-value-cons)
	  doing
      (when proprietary-p
	(setq proprietary-clauses
	      (nconc proprietary-clauses
		     (copy-tree-using-slot-value-conses body))))
      (when new-modes
	(setq user-interface-clauses
	      (nconc user-interface-clauses
		     (slot-value-list
		       (nconc (slot-value-list when-or-unless new-modes)
			      (copy-tree-using-slot-value-conses body)))))))
    
    ;; Now reconstruct the object configuration with the new UI and proprietary clauses.
    (let ((ui (and user-interface-clauses
		   (slot-value-cons 'user-interface user-interface-clauses)))
	  (prop (and proprietary-clauses
		     (slot-value-cons 'proprietary proprietary-clauses)))
	  (new-object-configuration ()))

      (loop for clause in object-configuration doing
	(cond ((user-interface-clause-p clause)
	       (when ui
		 (slot-value-push ui new-object-configuration)
		 (setq ui nil)))
	      ((proprietary-items-clause-p clause)
	       (when prop
		 (slot-value-push prop new-object-configuration)
		 (setq prop nil)))
	      (t
	       (slot-value-push (copy-tree-using-slot-value-conses clause) new-object-configuration))))

      (setq new-object-configuration (nreverse new-object-configuration))
      (when ui
	(setq new-object-configuration (nconc new-object-configuration
					      (slot-value-list ui))))
      (when prop
	(setq new-object-configuration (nconc new-object-configuration
					      (slot-value-list prop))))
      (rename-slots-in-restrictions new-object-configuration))))






;;; The macro`copy-user-restrictions-into-object-configuration-macro'. When the
;;; user-restrictions are edited, copy them into a user-interface and
;;; proprietary-items clauses in the object-configuration slot.  Any existing
;;; user-interface or proprietary-items clauses are replaced in their entirety.

(defmacro copy-restrictions-into-object-configuration-macro (block user-restrictions name-of-slot)
  `(let* ((old-object-configuration (,name-of-slot ,block))
	  (new-object-configuration
	    (convert-user-restrictions-into-object-configuration
	      old-object-configuration ,user-restrictions)))
     
     ;; Unless the old slot-value was inherited, reclaim it now.
     (unless (eq old-object-configuration (get-slot-init-form (class block) ',name-of-slot))
       (reclaim-slot-value-list old-object-configuration))
     
     ;; Don't use change-slot-value since we mutually recurse with
     ;; object-configuration's slot-putter.
     (setf (,name-of-slot ,block) new-object-configuration)
     (update-representations-of-slot-value ,block ',name-of-slot)
     new-object-configuration))



(defun copy-user-restrictions-into-object-configuration (block user-restrictions)
  (copy-restrictions-into-object-configuration-macro
    block user-restrictions object-configuration))


(defun copy-class-restrictions-into-instance-configuration (block class-restrictions)
  (copy-restrictions-into-object-configuration-macro
    block class-restrictions instance-configuration))






;;;; The standard hierarchy



;;; The function `item-like-class-description-p' ought to return T for an item or for something
;;; which is on a KB-workspace and can be clicked upon by the user.

(defun-substitution-macro item-like-class-description-p (class-description)
  (or (class-description-of-class-p class-description 'item)
      (class-description-of-class-p class-description 'name-box)         ; workspace and entity names.
      
      ;; Do we really want this?  It causes behavior to differ from 3.0 In
      ;; particular, "selecting any item implies xxx" matches tables on
      ;; workspaces in 4.0, but not in 3.0.
      (eq (class-name-of-class-description class-description) 'table)	 ; Attribute displays.
      
      (class-description-of-class-p class-description 'arrow-button)     ; Little buttons on logbook pages.

      (class-description-of-class-p class-description 'scrap)
      (class-description-of-class-p class-description 'loose-end)

      (class-description-of-class-p class-description 'table-of-values)
      (class-description-of-class-p class-description 'explanation-table) ; ?
      
      (class-description-of-class-p class-description 'ok)
      (class-description-of-class-p class-description 'authorized-user)))
      
;; Cf entity-like-p.



;;; The function `class-description-matches-class-p' returns T when the class-description is of the
;;; given "class" as supplied in user restrictions.  For the purposes of user
;;; restrictions, the class ITEM, matches any frame which might be clickable on
;;; a workspace: items, name-boxes, and attribute displays.

(defun-substitution-macro class-description-matches-class-p (class-description class-for-restrictions)
  (cond ((eq class-for-restrictions 'item)
	 (item-like-class-description-p class-description))
	((eq class-for-restrictions 'connection)
	 (or (class-description-of-class-p class-description 'connection)
	     (class-description-of-class-p class-description 'loose-end)))
	(t
	 (class-description-of-class-p class-description class-for-restrictions))))

;; This only needs special cases for those frames which are seen by the
;; restrictions search, which I think is only frames returned by
;; most-interesting-frame.



;;; The substitution-macro `frame-matches-restriction-class-spec' decides
;;; whether the given frame matches the restrictions class-spec which came from
;;; current-frame.  Class-spec is either
;;;
;;;    nil, which corresponds to no requirement for any frame
;;;    at all, or, if a frame is supplied, no class constraint
;;;    on the frame;
;;;
;;;    a symbol naming a class, which is the result of
;;;    the "this class" grammar in the object configuration; or
;;;
;;;    a list of classes, which is the result of the "any
;;;    class-1, ..., or class-n" grammar

(defun-simple frame-matches-restriction-class-spec
    (frame? class-spec current-frame?)
  (cond ((null class-spec)			   ; No classes given. Matches anything. (See Note)
	 T)
	((null frame?)				   ; No frame. Matches nothing.
	 nil)

	((atom class-spec)			   ; A "this class" specification.
	 (and (eq frame? current-frame?)
	      (class-description-matches-class-p
		(if (class-description-p frame?)
		    frame?
		    (class-description-slot frame?))
		class-spec)))

	(t						    ; An "any class" specification.
	 (loop with class-description = (if (class-description-p frame?)
					    frame?
					    (class-description-slot frame?))
	       for class in class-spec
	       thereis (class-description-matches-class-p class-description class)))))

;; Note: if there was a frame, previously, this matched against ITEM, (and
;; briefly, in 6.0 under development, edit-box), but that produced seemingly
;; random results, since non-items could show up on user and non-user
;; workspaces.  This is most easily understood and explained as matching nothing
;; under the mouse, or anything, no matter what kind of thing, under the
;; mouse. Fixes bugs HQ-3127454, HQ-3543806.  (MHD 7/11/00)





(defun class-description-matches-restriction-class-spec (class-description class-spec current-frame?)
  (declare (ignore current-frame?))
  (cond ((null class-spec)				    ; No classes given. Matches any item.
	 (class-description-matches-class-p class-description 'item))

	((atom class-spec)				    ; A "this class" specification.
	 nil)

	(t						    ; An "any class" specification.
	 (loop for class in class-spec
	       thereis (class-description-matches-class-p class-description class)))))

;; Called by filter-workspace-menu-restriction, filter-visibility-restrictions, 
;; filter-table-restrictions, and filter-non-menu-restriction in this module.

;; Notice how the (eq pseudo-class 'item) clause puts all frames into the class
;; ITEM from the point of view of restrictions!  - ben 12/31/91

;; I removed that clause.  Restrictions on item were matching, eg, menu workspaces,
;; which caused problems. Namely, mouse restrictions were usurping some of the
;; built-in menu-handlers in the top level keymap.  A better solution is probably
;; to make those handlers non-usurpable, but otherwise let thru restrictions which
;; have no class spec.  See `frame-matches-class-p', above. -fmw, 7/26/94

;; Some non-items are now not configurable with restrictions.  Authorized-user,
;; for example.



(defun class-is-visible-to-user-p (class-name)
  (class-is-subclass-of-item? (class-description class-name)))

(defun class-definition-name (class-definition)
  (cond ((consp class-definition)
	 (first (second class-definition)))
	((framep class-definition)
	 (name-or-names-for-frame class-definition))
	(t
	 class-definition)))


#+development
(defvar trace-configuration-search nil)

#+development
(defun trace-configuration-search ()
  (setq trace-configuration-search (not trace-configuration-search)))

#+development
(defun trace-configuration (location annotations)
  (format t "Configuration search: ~s has configuration:~%" location)
  (write annotations :pretty t)
  (terpri)
  (terpri))



;;; The variable `superior-frame-for-restrictions-frame?' is bound during
;;; transfer operations to a frame whose *proposed* new superior workspace is
;;; given in the variable `superior-frame-for-restrictions-superior?'. Restriction
;;; lookup will then behave as if the frame is indeed on the given workspace.

(defvar superior-frame-for-restrictions-frame? nil)
(defvar superior-frame-for-restrictions-superior? nil)


;;; The macro `do-standard-search-hierarchy' loops over each element in the
;;; standard configuration search path, from item to its parents, through
;;; kb-restrictions, and onto the class inheritance path of the item.  If item
;;; is NIL, then we run only on the kb-restrictions.  The search can be exited
;;; by returning to the tag STANDARD-SEARCH.

(defmacro do-standard-search-hierarchy ((annotations location item-or-class-description?
						     &optional positional-item?)
					&body body)
  ;; We are casual with name capture here.
  `(block standard-search
     (let* ((traversing-class-hierarchy? nil)
	    (the-class-inheritance-path ())
	    (original-item-or-class-description? ,item-or-class-description?)
	    (frame-with-modified-superior? superior-frame-for-restrictions-frame?))
       (loop with class-description?
	       = (cond ((framep original-item-or-class-description?)
			(class-description-slot original-item-or-class-description?))
		       ((class-description-p original-item-or-class-description?)
			original-item-or-class-description?))
	     for ,location
		 = (or ,positional-item?
		       (if (framep original-item-or-class-description?)
			   original-item-or-class-description?
			   kb-restrictions))
		 then (cond (traversing-class-hierarchy?
			     (let* ((class-name (pop the-class-inheritance-path))
				    (defn (and class-name
					       (neq class-name 'item)
					       (class-definition class-name))))
			       (if (consp defn)
				   class-name
				   defn)))
			    
			    ((eq ,location kb-restrictions)
			     (when class-description?
			       ;; start to search the class hierarchy
			       (setq traversing-class-hierarchy? t
				     the-class-inheritance-path
				     (class-inheritance-path class-description?))
			       (let* ((class-name (pop the-class-inheritance-path))
				      (defn (and class-name (class-definition class-name))))
				 (if (consp defn)
				     class-name
				     defn))))

			    ;; location is somewhere in the positional hierarchy of item.
			    ;; Get the superior frame positionally
			    ((eq ,location frame-with-modified-superior?)
			     (setq frame-with-modified-superior? nil)
			     superior-frame-for-restrictions-superior?)

			    ((superior-frame ,location))
			    ;; if no more, get the the kb-restrictions.
			    (t kb-restrictions))
	     while ,location
	     for ,annotations = (cond ((not traversing-class-hierarchy?)
				       (object-configuration ,location))
				      ((not (framep ,location))
				       nil)
				      (t
				       (instance-configuration ,location)))
	     doing
	 #+development (when trace-configuration-search
			 (trace-configuration ,location ,annotations))
	     ,@body))))



;;; The macro `do-item-configuration' loops over all clauses of the given type
;;; in all item-configurations which could affect the given item.  TYPE can be
;;; 'format, 'user-interface, etc.

(defmacro do-item-configuration ((clause location item? type) &body body)
  `(do-standard-search-hierarchy (annotations ,location ,item?)
     (loop for annotation in annotations doing
       (when (eq (first annotation) ,type)
	 (loop for ,clause in (cdr annotation) doing
	   ,@body)))))



;;; The substitution-macro `mode-restriction-matches-user-mode-p' returns T if
;;; the given mode matches the modes as given in the restriction clause.

(def-substitution-macro mode-restriction-matches-user-mode-p (restriction mode)
  (let ((type (first restriction))
	(modes (second restriction)))
    (case type
      ((when)
       (memq mode modes))
      ((unless)
       ;; Here is where we prevent "unless in foo mode" from matching
       ;; adminstrator mode.
       (and (neq mode 'administrator)
	    (not (memq mode modes)))))))



;;; The macro `do-matching-user-interface-clauses' runs body for each
;;; user-interface clause which matches the current user-mode and each
;;; proprietary mode clause which matches the item's proprietariness, the
;;; item's class, and the given pattern.

(defmacro do-matching-user-interface-clauses ((clause item pattern)
					      &body body)
  (avoiding-variable-capture (&aux mode place clauses top-clause mode-clause)
    `(let ((,mode (if (boundp 'current-g2-user-mode?) current-g2-user-mode?))
	   (proprietary? (and ,item (proprietary-p ,item))))
       (do-standard-search-hierarchy (,clauses ,place ,item)
	 (loop for ,top-clause in ,clauses doing

	   (cond ((user-interface-clause-p ,top-clause)
		  (loop for ,mode-clause in (cdr ,top-clause) doing
		    (when (or (null ,mode)
			      (mode-restriction-matches-user-mode-p ,mode-clause ,mode))
		      (loop for ,clause in (cddr ,mode-clause)
			    as binding? = (restrictions-pattern-match ,clause ',pattern)
			    doing
			(when (and binding?
				   (frame-matches-restriction-class-spec
				     ,item (user-interface-clause-class-spec ,clause)
				     ,place))
			  ,@body)))))

		 ((proprietary-items-clause-p ,top-clause)
		  (when (proprietary-instance-p-1
			  proprietary? traversing-class-hierarchy? ,place)
		    (loop for ,clause in (cdr ,top-clause)
			  as binding? = (restrictions-pattern-match ,clause ',pattern)
			  doing
		      (when (and binding?
				 (frame-matches-restriction-class-spec
				   ,item (user-interface-clause-class-spec ,clause)
				   ,place))
			,@body))))))))))

;; Most unfortunate that the body must be repeated.
;; This was supposed to be the easy-to-use version of
;; map-over-matching-user-interface-clauses.



(defun-substitution-macro fix-up-double-click-configuration-clause (clause)
  (when (and (eq (first clause) 'clicking)
	     (double-bit-on-p (second clause))
	     (key-code-is-mouse-down-p (second clause)))
    (setf (second clause) (convert-mouse-code-to-mouse-select (second clause)))))

;;; The function `fix-up-double-click-configuration-clauses' replaces
;;; double-mouse-down key codes with double-mouse-select. Called during load
;;; for KBs saved in 7.0r0.

(defun fix-up-double-click-configuration-clauses (configuration)
  (loop for top-clause in configuration doing
    (cond ((user-interface-clause-p top-clause)
	   (loop for mode-clause in (cdr top-clause) doing
	     (loop for clause in (cddr mode-clause) doing
	       (fix-up-double-click-configuration-clause clause))))
	  
	  ((proprietary-items-clause-p top-clause)
	   (loop for clause in (cdr top-clause) doing
	     (fix-up-double-click-configuration-clause clause))))))



;;;; Two Kinds of Proprietariness



;;; There are two kinds of proprietariness for frames in G2:

;;;  A frame is `proprietary' (satifies proprietary-p) if it lives on a
;;;  workspace with a non-NIL proprietary package attribute.

;;;  A frame is a `proprietary-instance' (satifies proprietary-instance-p) if
;;;  either it is proprietary OR it is an instance of some class whose
;;;  object-definition is proprietary.

;;; Most built-in proprietary mode behavior in G2 require that the frame be
;;; proprietary.  Filters, however, opens up the space to include frames which
;;; are merely proprietary instances.  It could be that it was not the
;;; intention to have both concepts, but this describes the situation in 3.0
;;; and 4.0

;; -fmw, 3/2/95


;;; The substitution-macro `proprietary-instance-p' is true if the frame itself
;;; is proprietary or if the frame is an instance of a proprietary object
;;; definition.

(def-substitution-macro proprietary-instance-p (frame)
  (or (proprietary-p frame)
      (loop for class in (class-inheritance-path
			   (class-description-slot frame))
	    as class-definition = (class-definition class)
	    thereis (proprietary-p class-definition))))



;;; The substitution-macro `proprietary-instance-p-1' is an efficient version
;;; of the above for use during configuration searches.

(defun-substitution-macro proprietary-instance-p-1
    (frame-is-proprietary?
      traversing-class-hierarchy?
      class-definition)
  (or frame-is-proprietary?
      (and traversing-class-hierarchy?
	   (framep class-definition)
	   (proprietary-p class-definition))))



(defvar g2-identification-for-write-locks nil)

(defun-simple g2-identification-for-write-locks ()
  (current-system-case
    (ab (or g2-identification-for-write-locks
	    (setq g2-identification-for-write-locks
		  (twith-output-to-gensym-string
		    (tformat "~A:~A:~A"
			     local-host-name "TCPIP"
			     (or tcp-listener-port-number ""))
		    (let ((mf (reconstruct-g2-time-at-start (clock-get g2-time-at-start-as-text-string))))
		      (multiple-value-bind (seconds minutes hours date months years)
			  (decode-unix-time-as-managed-float mf)
			(reclaim-managed-float mf)
			(tformat " [")
			(twrite-n-digit-number-with-0-pad 4 years)
			(tformat "-")
			(twrite-n-digit-number-with-0-pad 2 months)
			(tformat "-")
			(twrite-n-digit-number-with-0-pad 2 date)
			(tformat " ")
			(twrite-n-digit-number-with-0-pad 2 hours)
			(tformat ":")
			(twrite-n-digit-number-with-0-pad 2 minutes)
			(tformat ":")
			(twrite-n-digit-number-with-0-pad 2 seconds)
			(tformat "] ")))
		    (multiple-value-bind (user found)
			(get-current-user-name)
		      (when found
			(tformat " (~A)~%" user)))))))))

;The first time a change is made that is permanent,
;we need to check whether item-is-from-an-editable-module-p is true,
;and if it is, we need to prohibit the change, or warn, if prohibiting
;it isn't possible, or if the user has the kb configured for warnings only.

;Permanent changes are those changes to permanent items (calls to change-slot-value or
;set-slot-value) that are not preceded by calls to note-kb-state-change or
;note-kb-state-change-to-slot-by-saving-text.
;Also, calling set-permanent-and-propagate on an item with changes makes those changes
;permanent.  Also, calling transfer-blocks-with-their-external-connections.
;Actually, most ui commands should call this.

(defvar restrict-edits-to-modules-having-read-only-files-p nil)

(def-kb-specific-property-name module-is-explictly-editable-p)

(defun-simple item-explicitly-editable-p (item)
  (or (not (or source-code-control-support-enabled-p
	       restrict-edits-to-modules-having-read-only-files-p))
      (item-is-explicitly-editable item) ;transient
      (and (block-p item)
	   (block-is-invisible-to-unsavable-change-protection-p item)))) ;permanent

(defun reason-permanent-items-attribute-is-not-editable
    (item slot-name &optional class-qualifier? slot-description?)
  (unless (or in-recompile-item-p
	      (let ((class (class item)))
		(and (null class-qualifier?)
		     (eq class 'saving-parameters)
		     (or (eq slot-name 'unsavable-change-protection)
			 (and (eq item saving-parameters)
			      (eq slot-name 'default-unsavable-change-protection)))))
	      (and slot-description?
		   (reason-to-exclude-slot-description-for-compute-class-description-node-attributes
		     slot-description?)))
    (reason-permanent-items-module-is-not-editable item)))

(defun reason-permanent-items-module-is-not-editable (item &optional allow-warning-p)
  (and (not in-recompile-item-p)
       (of-class-p item 'item)
       (permanent-block-p item)
       (not (item-explicitly-editable-p item))
       (let ((module? (get-module-block-is-in item)))
	 (when module?
	   (and (not (module-is-explictly-editable-p module?))
		(let ((reason-module-is-not-editable
		       (get-reason-module-is-not-editable module?)))
		  (when (and reason-module-is-not-editable
			     allow-warning-p
			     (warn-on-unsavable-change-p module?))
		    (unless (memq item items-warned-in-edit-warning-context)
		      (with-immediate-scheduling ()
			(warn-about-editing-item
			 item (copy-frame-serial-number (frame-serial-number item))
			 (slot-value-list
			  module? reason-module-is-not-editable
			  (or (current-workstation-if-usable-for-dialog nil)
			      (get-current-ui-client-interface)))))
		      (when in-edit-warning-context-p
			(gensym-push item items-warned-in-edit-warning-context))))
		  (unless (allow-unsavable-change-p module?)
		    reason-module-is-not-editable)))))))

(defun-simple item-is-either-not-permanent-or-from-an-editable-module-p (item)
  (null (reason-permanent-items-module-is-not-editable item t)))

(declare-system-procedure-function g2-item-is-editable t)

(defun-funcallable g2-item-is-editable (item)
  (values
    (make-evaluation-boolean-value
      (item-is-either-not-permanent-or-from-an-editable-module-p item)) ; will warn!
    (copy-if-text-string
      (reason-permanent-items-module-is-not-editable item))))

(defvar see-also-for-warn-about-editing-item
  "(To turn off these warnings, or to allow edits for all items, edit the saving-parameters.)")

(defun-void warn-about-editing-item (item frame-serial-number arg-list)
  (unless (prog1 (frame-has-been-reprocessed-p item frame-serial-number)
	    (reclaim-frame-serial-number frame-serial-number))
    (let ((module? (first arg-list))
	  (reason (second arg-list))
	  (workstation-or-ui-client-interface? (third arg-list))
	  (workstation? nil)
	  (ui-client-interface? nil))
      (reclaim-slot-value-list arg-list)
      (cond ((and workstation-or-ui-client-interface?
		  (not (framep workstation-or-ui-client-interface?)))
	     (setq workstation? workstation-or-ui-client-interface?)
	     (warn-about-editing-item-for-workstation workstation? item module? reason))
	    ((setq ui-client-interface? workstation-or-ui-client-interface?)
	     (enter-dialog-for-t2
	      'edits-not-allowed-on-item
	      (eval-list (eval-list 'text
				    (tformat-text-string "Cannot edit ~NF, because ~A.  ~A"
							 item reason see-also-for-warn-about-editing-item)
				    'edit-item-warning)
			 (eval-list 'item item 'uneditable-item)
			 (eval-list 'button
				    (copy-text-string #w"OK") 'ok)
			 (eval-list 'text
				    (copy-text-string #w"Allow edits to:") 'allow-edits-to)
			 (eval-list 'check-box
				    (copy-text-string #w"this item") 'item nil)
			 (eval-list 'check-box
				    (copy-text-string #w"this item's workspace") 'workspace nil)
			 #+ignore
			 (eval-list 'check-box
				    (copy-text-string #w"this item's toplevel workspace")
				    'toplevel-workspace nil)
			 (eval-list 'check-box
				    (copy-text-string #w"this item's module") 'module nil))
	      (slot-value-list 't2-continuation-for-warn-about-editing-item
			       item (copy-frame-serial-number (frame-serial-number item)))
	      ui-client-interface?
	      nil))
	    (t ; should never get here.  item-is-either-not-permanent-or-from-an-editable-module-p
	     ;; should be called only from ui operations.  non-ui operations should call
	     ;; reason-permanent-items-attribute-is-not-editable instead.
	     (with-user-notification ()
	       (record-block-for-tformat (get-saving-parameters module?))
	       (tformat "Cannot edit ~NF, because ~A.  ~
                     See the saving-parameters and the server-parameters."
		      item reason)))))))

(defun warn-about-editing-item-for-workstation (workstation item module? reason)
  (for-workstation (workstation)
    (warn-about-editing-item-for-workstation-1 item module? reason)))

(defun warn-about-editing-item-for-workstation-1 (item module? reason)
  (declare (ignore module?))
  (enter-dialog
    (tformat-text-string "Cannot edit ~NF, because ~A.  ~A"
			 item reason see-also-for-warn-about-editing-item)
    (copy-constant-wide-string #w"OK") 'none
    'warn-about-editing-item-callback
    (slot-value-list item (copy-frame-serial-number
			    (frame-serial-number item)))
    nil nil
    (x-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation))
    (y-of-mouse-pointer (mouse-pointer-of-latest-event current-workstation)))
  (add-check-boxes-to-current-dialog
    (copy-text-string #w"Allow edits to:")
    '(("this item" item)
      ("this item's workspace" workspace)
      #+ignore ; not implemented
      ("this item's toplevel workspace" toplevel-workspace)
      ("this item's module" module))))

(defun t2-continuation-for-warn-about-editing-item (sequence-number client-item item fsn)
  (multiple-value-bind (button check-box-list)
      (leave-dialog-for-t2 sequence-number)
    (declare (ignore button))
    (remove-dialog-info-from-ui-client-interface-dialog-list
      sequence-number
      (ui-client-session-parent-interface client-item))      
    (warn-about-editing-item-callback item fsn check-box-list)))

(defun warn-about-editing-item-callback (item fsn alist)
  (unless (frame-has-been-reprocessed-p item fsn)
    (loop for (type . value) in alist
	  when value
	    do (case type
		 (item (g2-set-item-explicitly-editable item))
		 (workspace
		  (let ((workspace (get-workspace-if-any item)))
		    (when workspace
		      (g2-set-item-and-all-its-subblocks-explicitly-editable workspace))))
		 (toplevel-workspace
		  nil)
		 (module
		  (g2-set-all-items-in-module-explicitly-editable item)))))
  (reclaim-frame-serial-number fsn)
  (reclaim-slot-value-tree alist)
  nil)

(declare-system-procedure-function g2-set-item-explicitly-editable t)

(defun-funcallable g2-set-item-explicitly-editable (item)
  (setf (item-is-explicitly-editable item) t))

(declare-system-procedure-function g2-set-item-and-all-its-subblocks-explicitly-editable t)

(defun-funcallable g2-set-item-and-all-its-subblocks-explicitly-editable (item)
  (setf (item-is-explicitly-editable item) t)
  (when (frame-of-class-p item 'block)
    (loop for subblock being each subblock of item
	  do (g2-set-item-and-all-its-subblocks-explicitly-editable subblock))))

(declare-system-procedure-function g2-set-all-items-in-module-explicitly-editable t)

(defun-funcallable g2-set-all-items-in-module-explicitly-editable (item-or-module)
  (when (framep item-or-module)
    (setq item-or-module (get-module-block-is-in item-or-module)))
  (when (and item-or-module (symbolp item-or-module))
    (setf (module-is-explictly-editable-p item-or-module) t)))

(defun get-reason-module-is-not-editable (module &optional do-not-check-out-for-editing-p)
  (let ((reason-module-is-not-editable
	  (lookup-kb-specific-property-value-with-default
	    module 'reason-module-is-not-editable 'unknown)))
    (when (or do-not-check-out-for-editing-p (eq reason-module-is-not-editable 'unknown))
      (setq reason-module-is-not-editable
	    (let ((pathname? (get-true-pathname-of-module-if-any module)))
	      (when pathname?
		(check-if-module-is-editable module pathname? do-not-check-out-for-editing-p))))
      (unless do-not-check-out-for-editing-p
	(set-reason-module-is-not-editable module reason-module-is-not-editable)))
    reason-module-is-not-editable))

(defun-void recompute-editability-of-modules ()
  (loop with modules-with-unsaved-changes = (modules-with-unsaved-changes)
	for suite in modules-and-system-tables-a-list
	as module-information-instance = (first suite)
	as module-name = (top-level-kb-module? module-information-instance)
	when module-name
	  do (set-reason-module-is-not-editable module-name 'unknown)
	     (setf (module-is-writable-p module-name) 'unknown)
	     (get-reason-module-is-not-editable
	       module-name
	       (not (memq module-name modules-with-unsaved-changes)))
	finally
	  (reclaim-gensym-list modules-with-unsaved-changes)))

(defun-void unedit-up-to-date-modules ()
  (loop for suite in modules-and-system-tables-a-list
	as module-information-instance = (first suite)
	as module-name = (top-level-kb-module? module-information-instance)
	as pathname? = (get-true-pathname-of-module-if-any module-name)
	when (and module-name pathname?
		  (currently-checked-out-file-is-up-to-date-p pathname?)
		  (module-file-is-checked-out-for-writing-by-current-user
		    (get-saving-parameters module-name)))
	  do (do-scc-command 'scc-unedit pathname?)))

(defun check-if-module-is-editable (module pathname do-not-check-out-for-editing-p)
  (let ((namestring-as-gensym-string (namestring-as-gensym-string pathname))
	(reason-module-is-not-editable
	  (lookup-kb-specific-property-value-with-default
	    module 'reason-module-is-not-editable 'unknown))
	(writable-p (module-is-writable-p module)))
    (when (eq reason-module-is-not-editable 'unknown)
      (let ((scc-p (file-is-in-source-code-control-p pathname)))
	(setq reason-module-is-not-editable
	      (cond (scc-p
		     (reason-that-the-current-user-is-not-the-only-editor
		       pathname do-not-check-out-for-editing-p))
		    (restrict-edits-to-modules-having-read-only-files-p
		     (or (let ((directory (gensym-namestring-of-directory-as-file pathname)))
			   (prog1 (cond ((not (g2-stream-directory-p directory))
					 (tformat-text-string
					   "the directory of the file for module ~A is not a directory"
					   module))
					((not (g2-stream-file-is-writable-p directory))
					 (tformat-text-string
					   "the directory of the file for module ~A is not writable"
					   module)))
			     (reclaim-text-string directory)))
			 (when (and (not (and do-not-check-out-for-editing-p scc-p))
				    (g2-stream-file-is-readable-p namestring-as-gensym-string)
				    (not (g2-stream-file-is-writable-p namestring-as-gensym-string)))
			   (tformat-text-string "the file for module ~A is read only" module))))))
	(setq writable-p (not reason-module-is-not-editable))
	(setf (module-is-writable-p module) writable-p)))
    (unless (or reason-module-is-not-editable
		(module-is-locked-p module))
      (let ((error-string? (try-to-obtain-write-lock-for-kb namestring-as-gensym-string)))
	(cond ((null error-string?)
	       (setf (module-is-locked-p module) t))
	      (t
	       (unless do-not-check-out-for-editing-p
		 (setf (module-is-writable-p module) nil))
	       (setq reason-module-is-not-editable error-string?)))))
    (reclaim-gensym-string namestring-as-gensym-string)
    reason-module-is-not-editable))






;;;; Event interpretation



;;; The substitution-macro `key-code-match-for-filters-p' determines whether an
;;; actual event key code matches the "pattern" given in an item configuration.
;;; We match if either the two key-codes match exactly, or else the event key
;;; code matches a wildcard pattern, applicable only to mouse events.

;;; The two sorts of wildcard patterns are:
;;;   An "up" pattern matches either an "up" or a "select" event
;;;   A "generic" pattern matches any mouse button in the event.
;;; Both variants can be used in the same pattern.

;;; For example, the mouse-up pattern matches these events:
;;;    mouse{-left,-middle,-right,}-{up,select}

(defun key-code-match-for-filters-p (key-code-in-event? key-code-in-filters?)
  ;; In order to preserve backwards compatibility with 6.x, any mouse pattern in
  ;; a configuration which does not specify the double bit explicitly, must
  ;; match the corresponding mouse event whether the event has the double-bit
  ;; set or not.
  ;; The logic here is that a double-click *is* a click, and so must match
  ;; patterns specifying a click. In fact, the only double events we can get are
  ;; double-mouse-down and double-mouse-select, but we don't depend on that fact
  ;; here.
  ;; A previous incomplete fix here (for HQ-4506849 "Second click is ignored if
  ;; too quick") handled only mouse-down patterns in the configuration. Handling
  ;; any mouse pattern here is part of the fix for HQ-4574589 "G2 7.0r0,
  ;; configurations using "selecting" don't activate on double-click". -fmw, 5/30/03
  (when (and key-code-in-filters?
	     (mouse-key-code-p key-code-in-filters?)
	     (not (double-bit-on-p key-code-in-filters?))
	     key-code-in-event?)
    (setq key-code-in-event? (logandf key-code-in-event? double-mask)))	; Modifying argument.
  (and key-code-in-filters?
       (or (null key-code-in-event?)	; Wildcard event key code
	   ;; Either the keycodes match exactly...
	   (=f key-code-in-event? key-code-in-filters?)
	   (and
	     ;; Not an exact match, so check the various wildcard patterns.
	     ;; The modifier bits must match still match exactly.
	     (=f (key-modifier-bits key-code-in-event?)
		 (key-modifier-bits key-code-in-filters?))
	     (or
	       ;; Handle "up" but explicit on button pattern. Since an "up"
	       ;; event matching an "up" pattern was taken care of in the check
	       ;; for an exact match, we need to check here just for a "select"
	       ;; event matching an "up" pattern.
	       (and (key-code-is-mouse-up-p key-code-in-filters?)
		    (key-code-is-mouse-select-p key-code-in-event?)
		    (eq (key-code-mouse-button-name key-code-in-event?)
			(key-code-mouse-button-name key-code-in-filters?)))

	       ;; Otherwise, we can assume that the pattern is generic on the
	       ;; button: any matches where the pattern was explicit on the
	       ;; button were taken care of earlier.
	       (key-case (key-index key-code-in-filters?)
		 (mouse-down
		   (key-code-is-mouse-down-p key-code-in-event?))
		 (mouse-up
		   (or (key-code-is-mouse-select-p key-code-in-event?)
		       (key-code-is-mouse-up-p key-code-in-event?)))
		 (mouse-select
		   ;; mouse-select key-codes are stored directly in
		   ;; item-configurations for "clicking" clauses, and
		   ;; indirectly, via user-interface-clause-key-code, for
		   ;; "selecting" clauses.
		   (key-code-is-mouse-select-p key-code-in-event?))))))))



;;; The function `map-over-matching-user-interface-clauses' maps the given
;;; function over all "configure the user-interface" and "proprietary-items"
;;; clauses which match the given mode, key-code, and item class.  The function
;;; should take three arguments (clause arg-1 arg2), and return two values
;;; (new-arg-1 new-arg-2).  The final values of arg-1 and arg-2 are returned.

;;; The clause is one of:
;;;    1. (CLICKING|PRESSING <key-code> <action> [class])
;;;    2. (SELECTING|SELECTING-ABSOLUTELY (classes) <action>).
;;;    3. (WORKSPACE-MENU (classes) <INCLUDE|EXCLUDE> . <actions>)

(defun map-over-matching-user-interface-clauses-1
    (clauses key-code? frame? location function arg-1 arg-2)
  (loop for clause in clauses
	as specified-key-code? = (user-interface-clause-key-code clause)
	as class-spec? = (user-interface-clause-class-spec clause)
	as key-matches? = (key-code-match-for-filters-p
			    key-code?
			    specified-key-code?)
	doing
    ;; We see other clause types here, like VISIBILITY, but it
    ;; has a null specified-key-code?
    (with-drawing-trace (config+)
      (format t "CONFIG:  Clause ~s matches keycode?: ~s, class?: ~s~%"
	      clause
	      key-matches?
	      (frame-matches-restriction-class-spec frame? class-spec? location)))
    
    (when (and key-matches?
	       (frame-matches-restriction-class-spec frame? class-spec? location))
      #+development
      (when trace-configuration-search
	(format t "*MATCH* ~s " location)
	(write clause :pretty t)
	(terpri))
      (with-drawing-trace (config)
	(format t "CONFIG:  Found! ~s on ~s" clause location))
      (multiple-value-setq (arg-1 arg-2)
	(funcall function clause arg-1 arg-2))))
  (values arg-1 arg-2))

(defun map-over-matching-user-interface-clauses
    (mode key-code? frame? function &optional positional-frame? arg-1 arg-2)
  (macrolet
      ((map-over-clauses (clauses)
	 `(multiple-value-setq (arg-1 arg-2)
	    (map-over-matching-user-interface-clauses-1
	      ,clauses key-code? frame? location function arg-1 arg-2))))

    (let ((proprietary? (cond (positional-frame?
			       (proprietary-p positional-frame?))
			      (frame?
			       (proprietary-p frame?)))))
      
      (do-standard-search-hierarchy (annotations location frame? positional-frame?)

	(loop for clause in annotations doing
	  (cond ((user-interface-clause-p clause)
		 (loop for mode-annotation in (cdr clause) doing
		   (when (or (null mode)
			     (mode-restriction-matches-user-mode-p mode-annotation mode))
		     (map-over-clauses (cddr mode-annotation)))))

		((proprietary-items-clause-p clause)
		 (when (proprietary-instance-p-1 proprietary?
						 traversing-class-hierarchy? location)
		   (map-over-clauses (cdr clause)))))))

      (values arg-1 arg-2))))



;;; The function `event-interpretation-for-clause' returns a newly consed event
;;; interpretation for the given UI clause, or NIL.

(defun event-interpretation-for-clause (clause)
  (let ((action? (user-interface-clause-action clause)))
    (cond ((null action?)
	   nil)
	  ((eq action? 'nothing)
	   ;; Return an INTERNAL namespace interp, which runs the NOTHING event
	   ;; handler.
	   (make-event-interpretation 'internal action? nil))

	  ((and (workspace-menu-clause-p clause)
		(eq action? 'menu))
	   ;; Return an INTERNAL namespace interp, which runs the MENU event
	   ;; handler.
	   (make-event-interpretation 'internal action? nil))
	  
	  (t
	   ;; Otherwise, return a user-namespace interpretation.
	   (make-event-interpretation
	     'user
	     (car-or-atom action?)
	     (cdr-or-atom action?))))))


;;; The function `interpret-event-via-object-configuration-1' updates the state
;;; (interpretation? and state) of the search for an event interpretation.  The
;;; handling of absolute clauses makes the search complex.

;;; First, when state=NIL, we are searching for any matching clause with has a
;;; non-NIL interpretation.  Once we find one, we set the interpretation and
;;; set the state to either T, meaning we haven't seen an absolutely clause, or
;;; to ABSOLUTE if we have.

;;; Once state is non-NIL, we are then looking only for absolute clauses.  Once
;;; we've found one absolute clause, the state become ABSOLUTE.

;;; But wait.  We now have to continue searching for yet ANOTHER matching
;;; absolute clause.  If we find one, we declare a conflict and set the event
;;; interpretation to NOTHING, which does nothing, and the state to DONE, which
;;; prevents any further matches.

(defun interpret-event-via-object-configuration-1 (clause interpretation? state)
  (let ((absolute? (absolute-user-interface-clause-p clause))
	(new-interpretation? interpretation?)
	(new-state state))
    
    ;; State: NIL => searching, T => non-absolute found, ABSOLUTE => one
    ;; absolute found, DONE => two found.
    (cond ((null (user-interface-clause-action clause)))
	  
	  ((null state)
	   ;; If we've not yet found any match, then continue searching all
	   ;; clauses.
	   (setq new-interpretation? (event-interpretation-for-clause clause))
	   (when new-interpretation?
	     (setq new-state (if absolute? 'absolute t))))
	  
	  ((null absolute?))
	  ;; Otherwise, notice only absolute clauses.

	  ((null (setq new-interpretation?
		       (event-interpretation-for-clause clause))))

	  
	  ((eq state t)
	   ;; Found first matching absolute clause
	   (setq state 'absolute))

	  ((eq state 'absolute)
	   ;; Found a second absolute clause.  Slam the interpretation to NOTHING.
	   (reclaim-event-interpretation new-interpretation?)
	   (setq new-interpretation? (make-event-interpretation 'internal 'nothing nil)
		 state 'done))

	  ((eq state 'done))

	  #+development
	  (t
	   (cerror "Go ahead" "Broken ~s" state)))
    
    

    ;; Reclaim old one, if any.
    (when (and interpretation? (neq new-interpretation? interpretation?))
      (reclaim-event-interpretation interpretation?))
    
    (values new-interpretation? new-state)))





;;; The function `lookup-key-in-item-configuration' is the lookup method for
;;; the item-configuration keymap interpreter. If frame? is NIL, then we search
;;; only the kb-restrictions.

(defun lookup-key-in-item-configuration (keymap keycode spot)
  (declare (ignore keymap))
  (unless (mouse-motion-event-p keycode) ; Optimization.
    (let ((frame?			; The frame against whose class we match.
	    (most-interesting-frame-in-spot spot)))

      (with-drawing-trace (config)
	(format t "CONFIG: Lookup ~a for ~s~%" (key-name keycode) frame?))

      (map-over-matching-user-interface-clauses
	current-g2-user-mode? keycode frame?
	#'interpret-event-via-object-configuration-1))))




;;; The function `map-over-external-names-in-object-configuration' calls the
;;; compiled function on the arguments (name class) for each name referenced by
;;; the object configuration.  NAME is a symbol and CLASS is one of procedure,
;;; frame-style-definition or image-definition.
;;; Example:
;;; ((user-interface
;;;   (UNLESS (ADMINISTRATOR)
;;;     (CLICKING 770 (USER-MOUSE-TRACKING PROC (ITEM)) (THIS KB-WORKSPACE))))

(defun map-over-external-names-in-object-configuration (compiled-function object-configuration)
  (loop for annotation in object-configuration doing
    (when (consp annotation)
      (case (first annotation)
	((configure user-interface)
	 (loop for mode-annotation in (cdr annotation) doing
	   (loop for clause in (cddr mode-annotation) doing
	      (when (and (eq (first clause) 'clicking)
			 (consp (third clause))
			 (eq (first (third clause)) 'user-mouse-tracking))
		(funcall-compiled-function compiled-function (second (third clause)) 'procedure)))))))))


  

;;; The function `key-bindings-due-to-object-configurations' returns an alist
;;; of (keycode class action) composed of filter conses, for the exclusive use of
;;; `make-help-workspace'.

(defvar currently-active-event-handlers-via-object-configuration)

(defun currently-active-event-handlers-via-object-configuration-1 (clause arg-1 arg-2)
  (declare (ignore arg-1 arg-2))
  ;; Clause is one of:
  ;;  (PRESSING <keycode> <Action> <class>)
  ;;  (SELECTING|SELECTING-ABSOLUTELY <classes> <action>)
  ;;  (WORKSPACE-MENU <classes> <INCLUDE|EXCLUDE> . <actions>)
  (let ((key-code (user-interface-clause-key-code clause))
	(class-spec (or (user-interface-clause-class-spec clause)
			t))
	(action? (user-interface-clause-action clause)))
    (when action?
      (filter-push (make-keymap-bucket filter-cons
				       key-code
				       (filter-copy class-spec)
				       (filter-copy action?)
				       nil)
		   currently-active-event-handlers-via-object-configuration))
    nil))


;; Should note that mouse-select is effectively bound to POST-MENU in some
;; cases.

(defun key-bindings-due-to-object-configurations (frame?)
  (let ((currently-active-event-handlers-via-object-configuration ()))
    (map-over-matching-user-interface-clauses
      current-g2-user-mode? nil frame?
      #'currently-active-event-handlers-via-object-configuration-1)
    currently-active-event-handlers-via-object-configuration))


(defun key-bindings-for-class-description-on-workspace-1 (clause alist arg2)
  (declare (ignore arg2))
  (let* ((key-code? (user-interface-clause-key-code clause))
	 (a (assq key-code? alist))
	 (interpretation+state (cdr a))
	 (interpretation? (car interpretation+state))
	 (state (cdr interpretation+state)))
    (if (not key-code?)
	(values alist nil)
	(multiple-value-bind (new-interpretation new-state)
	    (interpret-event-via-object-configuration-1 clause interpretation? state)
	  (unless interpretation+state
	    (setq interpretation+state (slot-value-cons nil nil))
	    (setq a (slot-value-cons key-code? interpretation+state))
	    (slot-value-push a alist))
	  (setf (car interpretation+state) new-interpretation)
	  (setf (cdr interpretation+state) new-state)
	  (values alist nil)))))

(defun key-bindings-for-class-description-on-workspace (class-description workspace)
  (map-over-matching-user-interface-clauses
    current-g2-user-mode? nil class-description
    #'key-bindings-for-class-description-on-workspace-1
    workspace))


(defun ole-drop-allowed-p (workspace class)
  #+enable-ole
  (or (eq current-g2-user-mode? 'administrator)
      (let* ((class-description (class-description class))
	     (alist (key-bindings-for-class-description-on-workspace
		      class-description workspace))
	     (allowedp (loop for (key-code interpretation . state) in alist
			     for name = (event-interpretation-name interpretation)
			     when (or (eq name 'ole-clone) (eq name 'ole-transfer))
			       return t
			     finally (return nil))))
	(reclaim-slot-value-tree alist)
	(and allowedp
	     (loop for command in '(ole-clone) ; (ole-clone ole-transfer)
		   when (command-is-excluded-absolutely-p
			  command class-description workspace)
		     return nil
		   finally (return t)))))
  #-enable-ole
  (progn workspace class nil)
  )





;;;; Exclude Absolutely



;;; The `exclude-absolutely' clauses in item configurations, by definition,
;;; absolutely disable the mentioned commands no matter how they may be
;;; invoked.  These are the restrictions we check in run-event-handler, which
;;; runs commands without knowing whether they came from a menu or from a
;;; keystroke or from a mouse gesture.


;;; The function `command-is-excluded-absolutely-p' returns non-NIL iff the
;;; given command-name appears in an "excluded absolutely" clause in the search
;;; path above frame, or, in the main-menu or global-keyboard command
;;; restrictions.  In fact, some commands cannot appear in some of these
;;; locations, but we don't make use of that fact here, taking the conservative
;;; choice of disabling a command which was absolutely excluded anywhere
;;; restrictions may be found.

(defun command-is-excluded-absolutely-p (command-name frame? &optional positional-frame?)
  (macrolet
      ((search-toplevel-clauses (toplevel-clauses)
	 `(loop for toplevel-clause in ,toplevel-clauses doing
	    (cond ((user-interface-clause-p toplevel-clause)
		   (loop for mode-annotation in (cdr toplevel-clause) doing
		     (when (or (null user-mode?)
			       (mode-restriction-matches-user-mode-p
				 mode-annotation user-mode?))
		       (search-clauses (cddr mode-annotation)))))

		  ((proprietary-items-clause-p toplevel-clause)
		   (when (proprietary-instance-p-1 proprietary?
						   traversing-class-hierarchy? location)
		     (search-clauses (cdr toplevel-clause))))

		  ((memq-p-macro (first toplevel-clause) '(when unless))
		   ;; Main-menu or global-keyboard
		   (when (or (null user-mode?)
			     (mode-restriction-matches-user-mode-p toplevel-clause user-mode?))
		     (search-clauses (cddr toplevel-clause)))))))
       
       (search-clauses (clauses)
	 `(loop for clause in ,clauses
		as class-spec? = (user-interface-clause-class-spec clause)
		as absolute-exclusions = (user-interface-clause-absolute-exclusions clause)
		doing
	    (when (and absolute-exclusions
		       (frame-matches-restriction-class-spec frame? class-spec? location)
		       (memq-p-macro command-name absolute-exclusions))
	      (return-from SEARCH clause)))))

    (block SEARCH
      (let ((proprietary? (cond (positional-frame?
				 (proprietary-p positional-frame?))
				(frame?
				 (proprietary-p frame?))))
	    (user-mode? (if (boundp 'current-g2-user-mode?)
			    current-g2-user-mode?
			    'administrator)))
	
	;; Consult the standard places up the search path.
	(do-standard-search-hierarchy (annotations location frame? positional-frame?)
	  (search-toplevel-clauses annotations))

	(let ((traversing-class-hierarchy? nil)
	      (location nil))

	  ;; Consult main menu restrictions.
	  (search-toplevel-clauses
	    (main-menu-user-restrictions kb-configuration))

	  ;; Consult global keyboard command restrictions.
	  (search-toplevel-clauses
	    (global-keyboard-command-user-restrictions kb-configuration)))
	nil))))




;;;; Properties



;;; The function `describe-item-configuration-keymap' is the describe method
;;; for the item-configuration keymap.  It returns a list of key bindings
;;; define by the object configurations which apply to the given frame.  The
;;; bindings are in the same format as those in a keymap, namely, each is a
;;; list of (key-code class handler).

(defun describe-item-configuration-keymap (keymap frame?)
  (declare (ignore keymap))
  (let ((key-bindings (key-bindings-due-to-object-configurations frame?)))
    (prog1 (describe-keymap-into-table-rows
	     (tformat-text-string "User Defined Commands") key-bindings)
      (reclaim-filter-tree key-bindings))))



;;; The function `get-property-value-in-object-configuration' returns the value
;;; of given property from the DECLARE clauses in object configurations.  If
;;; the property is not declared at all, then DEFAULT is returned.

(defun-simple get-property-value-in-object-configuration (block property default)
  (block search
    (do-standard-search-hierarchy (object-configuration place block)
      (loop for clause in object-configuration doing
	(when (and (object-configuration-declare-clause-p clause)
		   (frame-matches-restriction-class-spec
		     block (declare-clause-class-spec clause) place))
	  (let ((value (loop for (p v) on (declare-clause-plist clause)
			     when (eq p property)
			       return v
			     finally
			       (return clause))))
	    (unless (eq value clause)			    ; Marker for not-found
	      (return-from SEARCH value))))))
    default))




;;; The simple function `get-comment-in-object-configuration' returns the
;;; string-value comment, if any.

(defun-simple get-comment-in-object-configuration (block symbol)
  (block search
    (do-standard-search-hierarchy (object-configuration place block)
      (loop for clause in object-configuration doing
	(when (object-configuration-comment-clause-p clause)
	  (let ((spot (assq symbol (cdr clause))))
	    (when spot
	      (return-from search (second spot)))))))))




;;; The function `get-property-clause' returns the entire declaration clause
;;; which contains any value for the given property.

(defun get-property-clause (object-configuration property)
  (loop for clause in object-configuration
	when (and (object-configuration-declare-clause-p clause)
		  (loop for (p v) on (declare-clause-plist clause) by 'cddr
			thereis (eq p property)))
	  do (return clause)))


;;; The function `set-property-value-in-object-configuration' sets the DECLARE
;;; property for this block and any descendants of this block.

#+unused
(defun set-property-value-in-object-configuration (block property new-value)
  (loop for clause in (object-configuration block)
	when (and (object-configuration-declare-clause-p clause)
		  (null (declare-clause-class-spec clause))
		  (neq (getf (declare-clause-plist clause) property)
		       new-value))
	  do (return (setf (getf (declare-clause-plist clause) property)
			   new-value))
	finally
	  (setf (object-configuration block)
		(slot-value-cons
		  (make-declaration-clause-for-item-configuration property new-value)
		  (object-configuration block))))
  new-value)

;; Should we allow values other than T or NIL?




#+unused
(defun filter-remf-function (plist indicator)
  (loop as previous = nil then (cdr sublist)
	for sublist on plist by #'cddr
	doing
    (when (eq (car sublist) indicator)
      (return
	(cond ((null previous)
	       (prog1
		   (cddr sublist)
		 (setf (cddr sublist) nil)
		 (reclaim-filter-list sublist)))
	      (t
	       (setf (cdr previous) (cddr sublist)
		     (cddr sublist) nil)
	       (reclaim-filter-list sublist)
	       plist))))
	finally
	  (return plist)))
	     

;;; The macro `filter-remf' if the same as `remf', except that conses
;;; are reclaimed as filter-conses.

#+unused
(defmacro filter-remf (place indicator)
  `(setf ,place (filter-remf-function ,place ,indicator)))



(defun class-of-block-for-object-configuration (block)
  (let ((class-of-block (class block)))
    (case class-of-block
      ((workspace kb-workspace) 'workspace)
      (t class-of-block))))






;;; `Block-can-be-dependent-p' is a property of blocks that indicates if it is
;;; acceptable for this block to be recompiled when some "stable" block changes.
;;; This effectively defaults to T for all blocks.

(defun block-can-be-dependent-p (block)
  (not (get-property-value-in-object-configuration block 'independent-for-all-compilations nil)))


;;; `Block-is-unstable' is a property of blocks that indicates G2 to arrange to
;;; limit how many things must be recompiled if changes are made to this block.
;;; This effectively defaults to T for all blocks.


(defun block-is-unstable-p (block)
  (not (get-property-value-in-object-configuration block 'stable-for-dependent-compilations nil)))


;;; `Block-is-optimizable' is a property of blocks that indicates if the
;;; block can be optimized

(defun block-is-optimizable-p (block)
  (get-property-value-in-object-configuration block 'optimizable t))


(defun block-has-stable-heirarchy-p (block)
  (get-property-value-in-object-configuration block 'stable-hierarchy nil))


(defun block-is-invisible-to-unsavable-change-protection-p (block)
  (get-property-value-in-object-configuration block 'invisible-to-unsavable-change-protection nil))


;;; `No-manual-connections-p' is a property of objects that prevents the drawing
;;; of connections to the object except where pre-existing stubs permit it.
;;; It defaults to false.

(defun no-manual-connections-p (object)
  (not (get-property-value-in-object-configuration object 'manual-connections t)))


;;; `Subworkspace-connection-posts-p' is a property on objects that allows G2 to
;;; automatically create the permanent connection post on a subworkspace that
;;; connects the object on the subworkspace to its superior object on a
;;; higher-level workspace.

(defvar disable-subworkspace-connection-posts nil)

(defun subworkspace-connection-posts-p (object)
  (unless disable-subworkspace-connection-posts
    (get-property-value-in-object-configuration
      object 'subworkspace-connection-posts nil)))

;; Should these be setf-able?




;;; The function `grid-alignment-constraint-for-block' returns grid alignment
;;; constraint for a MOVING block as (values dx dy).  DX and DY are in pixels.
;;; If the block is completely unconstrained, we return NIL.

(defun grid-alignment-constraint-for-block (block)
  (block found
    (do-matching-user-interface-clauses (clause block (constrain moving * *))
      (gensym-dstruct-bind  ((dx . dy) (fourth clause))
	(return-from found (values dx dy))))))




;;; The function `movement-limits-for-block' returns the rectangle in
;;; workspace coordinates in which the block's movement is constrained, as
;;; (values left top right bottom).

(defun movement-limits-for-block (block)
  (block found
    (do-matching-user-interface-clauses (clause block (constrain rectangle * *))
      ;; In the clause, its in the user-visible order and coordinates (- y).
      (gensym-dstruct-bind ((left right bottom top) (fourth clause))
	(return-from found
	  (values left (-f top) right (-f bottom)))))))

;; Should we canonicalize the ordering of x and y to make the rectangle
;; non-empty?


(defun compute-snap-grid-for-block (block &optional prospective-workspace-of-block?)
  (let ((x-step? nil)
	(y-step? nil)
	(workspace?
	  (or prospective-workspace-of-block?
	      (and (superblock? block)
		   (frame-of-class-p (superblock? block) 'workspace)
		   (superblock? block)))))
    ;; In operate-on-area, first-block is always the bounding box, hence
    ;; unconstrained.  Constrain only immediate subblocks of the workspace
    ;; (i.e. not attribute-displays and name-boxes).
    (when workspace?
      (let ((superior-frame-for-restrictions-frame? block)
	    (superior-frame-for-restrictions-superior? workspace?))
	(multiple-value-setq (x-step? y-step?)
	  (grid-alignment-constraint-for-block block))))

    ;; If there was no old-style constraint in item configurations, try the
    ;; global snap-grid specified in drawing-parameters.
    (unless (or x-step? y-step?)
      (multiple-value-setq (x-step? y-step?)
	(get-global-snap-grid)))
    (values x-step? y-step?)))


;;;; Utilities For Functions To Compute Restrictions



;;; The computations and return values created when computing restrictions
;;; use conses taken from the FILTER cons pool.

;;; When computing what choices are available a search is made up the 
;;; user restrictions.  As this search proceeds it accumulates those
;;; choices that the restriction have excluded or included into two sets.
;;; These are known as the prohibited and permitted sets.  The function
;;; `compute-new-restriction-set' implements the fundamental operation
;;; on this set. 

;;; The routines `g2-subset', 'g2-set-equivalent', 'g2-equiv', 
;;; and 'g2-xor' are defined here and used though out G2.

;;; Global operations, i.e. keyboard and main menu, need only search
;;; their respective slot in the kb-restrictions system table.  
;;; `Compute-user-restrictions-in-kb-restrictions' provides a general
;;; utility for doing just that.  

;;; Other operations must search the KB hierarchy beginning at the item the user is about
;;; to operate upon.  The general utility for this is provide by three components while
;;; each kind of operation must provide two components.
;;;  - routine to compute some kind of restriction on items
;;;  - `with-filters', a macro, establishes a dynamic extent
;;;  - `filter-restrictions-for-item' mapping function of the restrictions
;;;  - function to apply to each restriction encountered.
;;;  - `filter-new-restriction-set' is usually called by function applied to each restriction.








;;; `Compute-new-restriction-set' has as value a set which is:
;;;
;;;    old-set U (additions - complement-set)
;;;
;;; where "U" is set union, and "-" is set difference.

;;; Sets are represented as filter lists and are assumed to be without
;;; duplicates. Furthermore, it is assumed that the arguments additions and
;;; complement-set are disjoint. The value is then guaranteed to be
;;; without duplicates, and also is disjoint from complement-set.
;;; The elements of a set are symbols, and equality is "eq".
;;; The second and third arguments are not mutated. The first argument may be
;;; mutated if not null, by having new stuff nconced at the end.

;;; All of the above is optimized for this situation, and probably not worth
;;; turning into a utility.

(defun-simple compute-new-restriction-set
       (old-set additions complement-set-1 complement-set-2)
  (loop for element in additions
	unless (or (memq element complement-set-1)
		   (memq element complement-set-2)
		   (memq element old-set))
	  collect element into new-stuff using filter-cons
	finally (return (nconc old-set new-stuff))))


;;; `Remove-from-restriction-set' is a two argument function equivalent to
;;; nset-difference except that it works in filter conses.

(defun-simple remove-from-restriction-set (set removals)
  (loop for element in removals do
    (setq set (delete-filter-element element set))
    finally (return set)))



;; Consider generalizing the following as a utility. If so, make these names
;; better, and consider (then) making them macros if they have to be fast.

(defun g2-xor (x y) (if x (not y) y))

(defun g2-equiv (x y) (if x y (not y)))

(defun g2-set-equivalent (s1 s2)
  (and (g2-subset s1 s2) (g2-subset s2 s1)))

(defun g2-subset (small-set large-set)
  (loop for elt in small-set always (memq elt large-set)))



;;; `With-filters', a macro, creates a dynamic extent.  To simplify the
;;; following discussion of N variables bound the term "choice" should be
;;; read to mean "choice or attribute name."
;;;  - permitted-restriction-set
;;;    Choices from "include" and "include additionally" restrictions are accumulated
;;;    here until a definitive restriction is encountered.
;;;  - prohibited-restriction-set,
;;;    Choices from "exclude" and "exclude additionally" restrictions are accumulated
;;;    here until a definitive restriction is encountered.
;;;  - conditional-termination-state?
;;;    This provides a flag indicating if a definitive restriction has been encountered.
;;;    - 'NIL indicates we are still searching for a definitive restriction.
;;;    - 'PERMITTED and 'PROHIBITED indicates we have seen a definitive choice restriction.
;;;    - 'IS-VISIBLE and 'IS-NOT-VISIBLE indicates we have seen a definitive choice restriction.
;;;    A non-NIL value flags that we have seed a definitive restrictions.
;;;  - absolutely-prohibited-restriction-set
;;;    Choices from "exclude absolute" restrictions are accumulated here.
;;;    These then mask any "include" or "include additionally" restrictions
;;;    encountered later.  They can also mask "selecting any..." restrictions.
;;;  - absolutely-selected-choice?
;;;    Any "select ... absolutely ..." choice is stored here.
;;;  - conditional-selected-choice?
;;;    Any other "select ..." choice is stored here.

;;; This is always established in preparation for calling the mapping fuction
;;; filter-restrictions-for-item and so current-g2-user-mode? should be non NIL.

;;; You may return multiple values from with-filters, and filter-restrictions-for-item
;;; usually does.

(defvar permitted-restriction-set)
(defvar prohibited-restriction-set)
(defvar absolutely-prohibited-restriction-set)
(defvar absolutely-selected-choice?)
(defvar conditional-selected-choice?)
(defvar conditional-termination-state?)

(defmacro with-filters (&body body)
  `(let* ((permitted-restriction-set nil)
	  (prohibited-restriction-set nil)
	  (absolutely-prohibited-restriction-set nil)
	  (absolutely-selected-choice? nil)
	  (conditional-selected-choice? nil)
	  (conditional-termination-state? nil))
     . ,body))


(defun reclaim-permitted-restriction-set ()
  (reclaim-filter-list permitted-restriction-set)
  (setq permitted-restriction-set nil))

(defun reclaim-prohibited-restriction-set ()
  (reclaim-filter-list prohibited-restriction-set)
  (setq prohibited-restriction-set nil))

(defun-simple reclaim-absolutely-prohibited-restriction-set ()
  (reclaim-filter-list absolutely-prohibited-restriction-set)
  (setq absolutely-prohibited-restriction-set nil))




;;; `Filter-new-restriction-set' is called only within the dynamic extent
;;; established by with-filters.  It always called by the function F being
;;; mapped over the user restrictions by filter-restrictions-for-item.  It side
;;; effects most of the state established by with-filters, for example it sets
;;; conditional-termination-state?  when it encounters a definitive
;;; restriction.

;;; It accumulates, as appropriate, choices into prohibited-restriction-set and
;;; permitted-restriction-set choices until it encounters a definitive
;;; restriction.

;;; It processes absolute restrictions by updating the
;;; absolutely-prohibited-restriction-set and refining the prohibited and
;;; permitted restriction sets.

(defun-simple filter-new-restriction-set (restriction-type additions)
  (case restriction-type
    ((include include-additionally)
     (setq permitted-restriction-set
	   (compute-new-restriction-set
	     permitted-restriction-set
	     additions
	     prohibited-restriction-set
	     absolutely-prohibited-restriction-set))
     (when (eq restriction-type 'include)
       (setq conditional-termination-state? 'permitted)))
    ((exclude exclude-additionally)		; otherwise case?
     (setq prohibited-restriction-set
	   (compute-new-restriction-set
	     prohibited-restriction-set
	     additions
	     permitted-restriction-set nil))
     (when (eq restriction-type 'exclude)
       (setq conditional-termination-state? 'prohibited)))
    (exclude-absolutely
     (setq absolutely-prohibited-restriction-set
	   (compute-new-restriction-set
	     absolutely-prohibited-restriction-set
	     additions nil nil))
     (setq permitted-restriction-set
	   (remove-from-restriction-set permitted-restriction-set additions))
     (setq prohibited-restriction-set
	   (compute-new-restriction-set
	     prohibited-restriction-set
	     additions permitted-restriction-set
	     nil))))
  nil)

;; Called by filter-workspace-menu-restriction, filter-table-restrictions,
;; and filter-non-menu-restriction in this module, but not by filter-visibility-restrictions.




;;;; Network Access




#+development
(defvar trace-network-access-checking nil)



;;; Declaration:     match-network-accessor (network-accessor pattern)
;;; Type:            lisp function
;;; Purpose:         predicate returning T iff network-accessor _matches_ pattern
;;;                  _matches_ defined below.
;;; Arguments:       network-accessor is one of gsi or g2, pattern is that or g2-and-gsi, any.
;;; Return behavior: returns t iff network-accessor _matches_ pattern, nil otherwise.
;;; Users:           only check-access, in this file (filters.lisp).
;;; Prerequisites:   network-accessor, pattern must be members of  (gsi g2 g2-and-gsi)
;;; Side effects:    none.
;;; Non-local exits: none.
;;; Memory impact:   none.
;;; Notes:           network-accessor _matches_ pattern is defined as follows:
;;;                    _matches_ is NOT symmetric,
;;;                    gsi _matches_ gsi
;;;                     "      "     g2-and-gsi,
;;;                     "      "     g2-and-gsi-and-telewindows,
;;;                    g2 _matches_ g2
;;;                     "     "     g2-and-gsi,
;;;                     "     "     g2-and-telewindows,
;;;                     "     "     g2-and-gsi-and-telewindows,
;;;                    telewindows _maches_ telewindows
;;;                     "     "     g2-and-telewindows,
;;;                     "     "     g2-and-gsi-and-telewindows,
;;;                  and
;;;                    nothing else _matches_.
;;;                  it should also never be the case that both network-accessor and pattern
;;;                  are g2-and-gsi, but it's probably not worth checking.

(def-substitution-macro match-network-accessor (network-accessor pattern)
  (memq pattern
	(case network-accessor
	  (gsi
	   '(any g2-and-telewindows-and-gsi g2-and-gsi gsi))
	  (g2
	   '(any g2-and-telewindows-and-gsi g2-and-gsi g2-and-telewindows g2))
	  (telewindows
	   '(any g2-and-telewindows-and-gsi g2-and-telewindows telewindows))
	  (t
	   (dwarn "match-network-accessor: network-accessor is not one of ~
             (g2, gsi, telewindows): ~s~%"
		  network-accessor)
	   nil))))



;;written by ncc 19 Jan 1994 

;;; Declaration:     network-access-allowed-p (access-type &optional frame?)
;;; Type:	     Lisp function, a predicate
;;; Purpose:	     determines if the given access-type is an allowed network
;;;                  access type for the given frame.
;;; Arguments:	     access-type: one of (inform read write execute)
;;;                  frame?, an optional frame object.
;;; Return behavior: returns t or nil depending on the permissibility of access.
;;;                  
;;; Users:           int2.lisp: item-remotely-visible-p,
;;;                             remote-connections-restricted-p, remote-inform-restricted-p
;;;
;;;                         
;;; Prerequisites:   access-type is one of read, write, inform or execute.
;;;                    (and possibly connect as well, for kb-restrictions to
;;;                     indicate if G2 and/or GSI connections themselves are permitted.)
;;; Side effects:    none.
;;; Non-local exits: none.
;;; Memory impact:   doesn't cons.
;;; Notes:           

(defun network-access-allowed-p (access-agent access-type &optional frame?)
  (let ((access-allowed? t)				    ; By default, allow it.
	(already-found-a-clause? nil))
    (do-standard-search-hierarchy (object-configuration place frame?)
      (loop for annotation in object-configuration doing
	;; (NETWORK-ACCESS (g2-and-or-gsi classes includes-excludes access-types) ...)
	(when (network-access-clause-p annotation)
	  (loop for network-clause in (cdr annotation)
		as access-agents = (first network-clause)
		as class-spec = (second network-clause)
		as inclexcl = (third network-clause)
		as access-types = (fourth network-clause)
	      doing
	    #+development (when trace-network-access-checking
			    (format t "Frame ~s, clause ~s~%" place network-clause))
	  (when (and (frame-matches-restriction-class-spec frame? class-spec place)
		     (match-network-accessor access-agent access-agents)
		     (or (null access-types)		    ; NIL means any access-type.
			 (memq access-type access-types)))
	    #+development (when trace-network-access-checking
			    (format t "  matched: ~s ~s old-value ~s~%"
				    inclexcl access-types access-allowed?))
	    (case inclexcl
	      (include-additionally
	       (unless already-found-a-clause?
		 (setq access-allowed? t)))
	      (exclude-additionally
	       (unless already-found-a-clause?
		 (setq access-allowed? nil)))
	      (exclude-absolutely
	       (setq access-allowed? nil)
	       (return-from STANDARD-SEARCH)))
	    (setq already-found-a-clause? t))))))
    access-allowed?))
		     


;;;; Interface Into User Restrictions




;;; Most of the external interface for asking questions of user restrictions are defined
;;; in this section.
;;; These two implement the global restrictions
;;;    compute-main-menu-restrictions
;;;    compute-global-keyboard-command-restrictions
;;; These four implement restrictions on items in the KB hierarchy.
;;;    compute-menu-restrictions-for-click-on-workspace
;;;    compute-menu-restrictions-for-click-on-table
;;;    compute-non-menu-restrictions-for-item
;;;    include-slot-in-attribute-table-p
;;; also
;;;    non-menu-choice-permitted-p

;;; Some of the interface is found elsewere for describe restrictions,
;;; network security, and for restricting frame operations are found latter.

;;; Make-table-describing-restrictions is in the next section.

;;; Network security, an unfinished facility, is provided by and the four stub routines:
;;;   item-remotely-visible-p,
;;;   item-remotely-modifiable-p,
;;;   remote-connections-restricted-p, and
;;;   remote-inform-restricted-p
;;; which are defined in INT2 since they got entangled with Telewindows.

;;; Finally the section "Restricting Frame Operations Via Proprietary Marks 
;;; and User Restrictions" implements just that.



;;; The four routines that query restrictions for items in the KB hiearachy 
;;; each have an associated mapping function they apply to restrictions
;;; using filter-restrictions-for-item.  These each immediately follow the
;;; four routines.




;;; `Compute-main-menu-restrictions' has as values (1) a list either of permitted
;;; or prohibited main menu (and its tributaries) choices. The second argument is
;;; true (non-nil) in the first case, and nil in the second case. If there are no
;;; restrictions, then the function return the empty list of prohibited choices and nil.
;;; As with all the following functions that return such lists, the list is of
;;; filter-conses and must be reclaimed.

(defun compute-main-menu-restrictions ()
  (compute-user-restrictions-in-kb-restrictions
   (main-menu-user-restrictions kb-restrictions)))



;;; The function `main-menu-command-permitted-p' returns non-NIL iff the given
;;; command name is permitted according to the menu-menu-user-restrictions.

(defun main-menu-command-permitted-p (command-name)
  (multiple-value-bind (restrictions permitted?)
      (compute-main-menu-restrictions)
    (prog1
	(if (memq command-name restrictions) permitted? (not permitted?))
      (reclaim-filter-list-function restrictions))))



(defun compute-global-keyboard-restrictions ()
  (compute-user-restrictions-in-kb-restrictions
    (global-keyboard-command-user-restrictions kb-restrictions)))


;;; The function `global-keyboard-command-permitted-p' returns T if the given
;;; command is permitted by keyboard-command-restrictions.  The command-name
;;; must be the user-visible command name (the menu-name, also known as the
;;; generic command name).

(defun global-keyboard-command-permitted-p (command-name)
  (multiple-value-bind (restrictions permitted?)
      (compute-global-keyboard-restrictions)
    (prog1
	(if (memq command-name restrictions) permitted? (not permitted?))
      (reclaim-filter-list-function restrictions))))



;;; `choice-conflict' is a signal that more than one absolute selection
;;; has been found in the restriction traversal. In this case, nothing
;;; should happen.

(defvar choice-conflict (list 'choice-conflict))




;;; The function `compute-menu-restrictions-for-click-on-workspace' returns
;;; three values, (choices permitted-p select-action).  But wait!  Its function
;;; is really to compute what to do for a mouse-select on an item or a
;;; workspace, so the choices list is not always what you might expect.  If
;;; there is an action bound to mouse-select (via a "selecting" configuration
;;; clause), the choices and permitted-p are invalid, namely, always NIL!
;;; Otherwise, the select-action is NIL and the choices and permitted-p values
;;; are correct.

;;; This function applies both to workspaces and to item menus.  (See
;;; documentation for compute-main-menu-restrictions.)

(defun compute-menu-restrictions-for-click-on-workspace (item)
  (with-filters
    (filter-restrictions-for-item
      item
      '(workspace-menu selecting selecting-absolutely)
      #'filter-workspace-menu-restriction nil)))

;; Called by make-table-describing-restrictions in this module.
;; Called by compute-choices-for-choice-computer in MENUS.



;;; The function `compute-menu-restrictions-for-workspace' returns the standard
;;; two values (choices permitted-p) for workspace and item menus.  It does NOT
;;; scan "selecting" clauses, which is the only way to get
;;; filter-restrictions-for-item to return the list of choices reliably.

(defun compute-menu-restrictions-for-workspace (item)
  (with-filters
    (filter-restrictions-for-item
      item
      '(workspace-menu)
      #'filter-workspace-menu-restriction nil)))


;;; The function `item-menu-command-permitted-p' returns T if the given
;;; command is available in the item (or workspace) menu for the given
;;; item.

(defun item-menu-command-permitted-p (command-name item)
  (multiple-value-bind (restrictions permitted?)
      (compute-menu-restrictions-for-workspace item)
    (prog1
	(if (memq command-name restrictions) permitted? (not permitted?))
      (reclaim-filter-list-function restrictions))))

;; Used by g2-system-command.  See also menu-item-permitted-p.



;;; The simple function `filter-workspace-menu-restriction' is the helper
;;; function for the above.

(defun-simple filter-workspace-menu-restriction (restriction-clause item current-item)
  (when (frame-matches-restriction-class-spec
	  item (second restriction-clause) current-item)
    (let ((activity-type (first restriction-clause)))
      (case activity-type
	(workspace-menu
	 (filter-new-restriction-set
	   (third restriction-clause)
	   (cdddr restriction-clause)))
	(selecting
	 (setq conditional-selected-choice? (third restriction-clause)))
	(selecting-absolutely
	 (setq absolutely-selected-choice?
	       (if absolutely-selected-choice?
		   choice-conflict
		   (third restriction-clause)))))))
  nil)

;; Funcalled by filter-restrictions-for-item by request of
;; compute-menu-restrictions-for-click-on-workspace.



;;; The variable `exact-class-names-for-menu-restrictions' is bound to a list of
;;; class names to match exactly.

(defvar exact-class-names-for-menu-restrictions)

(defun filter-menu-restriction-for-kb (restriction-clause item current-item)
  (declare (ignore item current-item))
  (when (eq (first restriction-clause) 'workspace-menu)
    (let ((class-spec? (second restriction-clause)))
      (when (cond ((null class-spec?) t)
		  ((memq class-spec? exact-class-names-for-menu-restrictions)
		   t)
		  ((atom class-spec?)
		   nil)
		  (t
		   (loop for class-name in exact-class-names-for-menu-restrictions
			 thereis (memq class-name class-spec?))))
	(filter-new-restriction-set
	  (third restriction-clause)
	  (cdddr restriction-clause)))))
  nil)


;;; The function `compute-restrictions-of-type' returns the usual values of
;;; choices and permitted-p for restrictions of given type. If frame? is NIL,
;;; then we look only in the KB configuration for clauses which either match
;;; either any class or specify exactly ITEM or WORKSPACE. In other words, those
;;; restrictions which would apply to any item or any workspace. Uses
;;; current-g2-user-mode?.

(defun compute-restrictions-of-type (type &optional frame?)
  (case type
    (main-menu (compute-main-menu-restrictions))
    (global-keyboard (compute-global-keyboard-restrictions))
    ((workspace-menu item-menu)
     (cond (frame?
	    (compute-menu-restrictions-for-workspace frame?))
	   (t
	    ;; With no frame, look only at KB-configuration, and in there,
	    ;; look only at classes of ITEM or WORKSPACE.
	    (let ((exact-class-names-for-menu-restrictions
		    (case type
		      (workspace-menu '(item workspace)) ; workspaces match either.
		      (item-menu '(item)))))
	      (with-filters
		(filter-restrictions-for-item
		  nil '(workspace-menu) #'filter-menu-restriction-for-kb nil))))))))


;;; The function `compute-all-restrictions' returns a new filter-tree of all the
;;; types of restrictions, as an alist with each entry of the form:

;;;    (type permitted? . choice-symbols)

;;; If frame? is nil, then we look only in kb-configuratgion, and in the case of
;;; item and workspace restrictions, we only return those which are guarenteed
;;; to be applicable; that is, those which specify a class of exactly ITEM or
;;; WORKSPACE. If frame? is a frame, then we sum restrictions over the standard
;;; search path, as usual.

(defun compute-all-restrictions (user-mode &optional frame?)
  (let ((current-g2-user-mode? user-mode)
	(result nil))
    (loop for type in '(main-menu workspace-menu item-menu global-keyboard) doing
      (multiple-value-bind (restrictions permitted?)
	  (compute-restrictions-of-type type frame?)
	(when (or restrictions permitted?)
	  (filter-push (filter-cons type (filter-cons permitted? restrictions))
		       result))))
    result))



;;;; Slot visibility restrictions



;;; The variable `slot-description-for-restrictions' is bound in a dynamic
;;; extent established by include-slot-in-attribute-table-p for use by the
;;; function it maps over the restrictions.

(defvar slot-description-for-restrictions)

(defvar slot-alias-for-restrictions)



;;; The substitution-macro `get-slot-description-for-filters' is careful to
;;; unalias slot names in order to get the slot description.

(def-substitution-macro get-slot-description-for-filters
    (slot-name-or-alias class-description defining-class)
  (get-slot-description-of-class-description
    (unalias-slot-name-if-necessary
      slot-name-or-alias
      (class-name-of-class-description class-description))
    class-description
    defining-class))



(def-substitution-macro user-authorized-in-current-workstation? ()
  (and (g2-secure-p)
       (g2-user-in-this-workstation-has-backdoor-privileges?
	 current-workstation)))




;;; The function `include-slot-in-attribute-table-p' returns non-nil if the
;;; slot of the table for the given item ought to be displayed.  It establishes
;;; a with-filters extent and maps `filter-visibility-restrictions' over the
;;; visibility restrictions of the item passed.

;;; The slot name MUST be the user-visible slot name, which is the alias if
;;; there is one, else is the pretty slot name from the slot-description.

;;; This does not need to be called in a for-workstation context, for example
;;; when displaying a file progress indicator.  If servicing-workstations?  is
;;; nil, this behaves as though the current user mode is ADMINISTRATOR.

;;; This routine contains code to implement a number of exceptional cases.
;;; These arise in service of login, the ok objects, proprietary and the slot
;;; showing module assignment in workspaces.

;; And it needs one more to get the file progress indicator (and other things?) 
;; to be visible even if restrictions are very extreme.  - Ben 5/1/92 ??

;; Note that slot-name-for-restrictions has already been aliased.

(defun include-slot-in-attribute-table-p (item aliased-slot-name defining-class)
  (include-slot-in-attribute-table-for-mode-p
    item aliased-slot-name defining-class (if servicing-workstation?
					      current-g2-user-mode?
					      'administrator)))

(defun include-slot-in-attribute-table-for-mode-p
    (item-or-class-description aliased-slot-name defining-class user-mode)
  ;; shadow the current value of this variable, just for this function...
  (let* ((current-g2-user-mode? user-mode)
	 (framep (framep item-or-class-description))
	 (class-description 
	  (if framep
	      (class-description-slot item-or-class-description)
	      item-or-class-description)))
    (cond
      ;; Implement the access "make-g2-secure" to only those 
      ;; workstations that logged in as secure.
      ((and (eq aliased-slot-name 'make-g2-secure?)
	    (class-description-of-class-p class-description 'ok))
       (user-authorized-in-current-workstation?))
    
      ;; Assure that some built in classes used for progress
      ;; indicators are allowed to show their attributes inspite of
      ;; what the user might attempt to do.
      ((or (class-description-of-class-p class-description 'file-progress)
	   (class-description-of-class-p class-description 'kb-search-state)
	   (class-description-of-class-p class-description 'icon-editor-table-info-frame))
       t)
    
      ;; Assure that user's security can't hide the login panel.
      ((class-description-of-class-p class-description 'g2-login)
       t)
      
      (t
       (and
	 ;; unless package-preparation-mode is true or (proprietary-p item)
	 ;;   ("in proprietary mode"), do not show proprietary-package
	 ;;   slot ...
	 (or (not (eq aliased-slot-name 'proprietary-package))
	     package-preparation-mode
	     (and framep (proprietary-p item-or-class-description)))
       
       
	 ;; The following is to maintain the constraint that the
	 ;; module-this-is-part-of? slot of a kb workspace should not
	 ;; be displayed in an attribute table unless it's a top-level
	 ;; kb workspace.
	 (or (not (class-description-of-class-p class-description 'kb-workspace))
	     (not (eq aliased-slot-name
		      (alias-slot-name-if-necessary 'module-this-is-part-of? 'kb-workspace)))
	     (and framep (null (parent-of-subworkspace? item-or-class-description))))
       
	 ;; ... show slot only if permitted by normal user restrictions
;	 (cerror "" "")
	 (let ((slot-alias-for-restrictions 
		 aliased-slot-name)
	       (slot-description-for-restrictions
		 (unless (eq aliased-slot-name 'class)
		   (get-slot-description-for-filters
		     aliased-slot-name class-description defining-class))))
	 
	   ;; *** To avoid a possible crash in the 4/25/94 build, do not allow
	   ;; *** slot components (pseudo slots w/o slot descriptions) to be
	   ;; *** restricted.  Warn in development. Fix this someday. -fmw,
	   ;; 4/25/94
	   
	   (cond ((null slot-description-for-restrictions)
		  #+development
		  (unless (eq aliased-slot-name 'table-header) ; This one is OK.
		     (dwarn "No slot-description for the ~s of ~s: not restricting it."
			    aliased-slot-name item-or-class-description))
		  t)
		 (t
		  (with-filters
		    (case (filter-restrictions-for-item
			    item-or-class-description '(visibility) #'filter-visibility-restrictions t)
		      ((is-visible nil)
		       t)
		      ((is-not-visible)
		       nil)))))))))))

;; Called by TABLES, and FACILITIES (for attribute displays).
;; Called by make-table-describing-restrictions in here.


;;; The substitution-macro `slot-strictly-matches-name-denotation-p' embodies
;;; the restrictive test as used in "include" restrictions: an unqualified
;;; element of the list matches the given slot only if that slot does not need
;;; a qualifier (in which case class-qualifier?  will be NIL).

(def-substitution-macro slot-strictly-matches-name-denotation-p
    (class-description slot-description name-denotation)
  (and (eq slot-alias-for-restrictions			    ; Redundant but quick check.
	   (unqualified-name name-denotation))
       (eq slot-description
	   (get-slot-description-of-class-description
	     (unalias-slot-name-if-necessary
	       (unqualified-name name-denotation)
	       (class-name-of-class-description class-description)) ; Ever an alias? Yes!!
	     class-description
	     (class-qualifier name-denotation)))))



;;; The substitution-macro `slot-loosely-matches-name-denotation-p' implements 
;;; the looser test as used in "excludes" restrictions: if the name-denotation
;;; does not have a class qualifier, then we match each any slot with the
;;; same name.  Otherwise, we match if the name denotation denotes this slot
;;; precisely.  The name-denotations include ALIASED slot names.

(def-substitution-macro slot-loosely-matches-name-denotation-p
    (class-description slot-description name-denotation)
  (and (or (eq name-denotation (unique-slot-name slot-description))
	   (eq slot-alias-for-restrictions
	       (unqualified-name name-denotation)))
       (or (null (class-qualifier name-denotation))
	   (eq slot-description
	       (get-slot-description-of-class-description
		 (unalias-slot-name-if-necessary
		   (unqualified-name name-denotation)
		   (class-name-of-class-description class-description))
		 class-description
		 (class-qualifier name-denotation))))))


(def-substitution-macro slot-in-restrictions-list-p
    (class-description slot-description name-denotations restriction-type)
  (case restriction-type
    ((include include-additionally)
     (loop for name-denotation in name-denotations
	   thereis (slot-strictly-matches-name-denotation-p
		     class-description slot-description name-denotation)))
    (t
     (loop for name-denotation in name-denotations
	   thereis (slot-loosely-matches-name-denotation-p
		     class-description slot-description name-denotation)))))


    
;;; The simple function `filter-visibility-restrictions' implements the
;;; following rule: an unqualified slot name in the restrictions matches all
;;; slots of that name when it is used in an "excludes" clause, and matches
;;; only the leaf slot of that name if it is used in an "includes" clause.
;;; Thus, we take the choice which minimizes slot visibility.  The required
;;; dynamic extent includes slot-alias-for-restrictions and
;;; slot-description-for-restrictions.

(defun-simple filter-visibility-restrictions
    (restriction-clause item-or-class-description current-item)
;  (format t "  filter-vis clause=~s ~%    item/cd=~s ~%    curr-item=~s~%"
;	  restriction-clause item-or-class-description current-item)
  (when (if (framep item-or-class-description)
	    (frame-matches-restriction-class-spec
	      item-or-class-description (second restriction-clause) current-item)
	    (class-description-matches-restriction-class-spec
	      item-or-class-description (second restriction-clause) current-item))
    (let* ((name-denotations (third restriction-clause))
	   (restriction-type (fourth restriction-clause))
	   (class-description (if (framep item-or-class-description)
				  (class-description-slot item-or-class-description)
				  item-or-class-description))
	   (slot-in-list-p (slot-in-restrictions-list-p
			     class-description
			     slot-description-for-restrictions
			     name-denotations restriction-type)))
      (case restriction-type
	((include include-additionally)
	 (cond
	   (slot-in-list-p
	    ;; conditionally visible
	    (setq conditional-termination-state? 'is-visible)
	    nil)
	   (t (case restriction-type
		(include
		 ;; not visible
		 (setq conditional-termination-state? 'is-not-visible)
		 t)
		;; no decision
		(otherwise nil)))))
	
	((exclude exclude-additionally exclude-absolutely)
	 (cond
	   (slot-in-list-p
	    ;; not visible
	    (setq conditional-termination-state? 'is-not-visible)
	    t)
	   (t (case restriction-type
		(exclude			; conditionally visible
		 (setq conditional-termination-state? 'is-visible)
		 nil)
		;; no decision
		(otherwise nil)))))))))

;; Funcalled by filter-restrictions-for-item on request of include-slot-in-attribute-table-p.






;;; `Compute-visible-slots-for-attribute-table' establishes a with-filters context and maps
;;; `filter-attribute-visibility-restrictions' over the the visibility restrictions
;;; of the item passed.  Finally it returns the set of slot visible for this item??

(defun-simple filter-attribute-visibility-restrictions (restriction-clause item current-item)
  (when (frame-matches-restriction-class-spec item (second restriction-clause) current-item)
    (let ((slot-names (third restriction-clause))
	  (restriction-type (fourth restriction-clause)))
      (filter-new-restriction-set
	restriction-type
	slot-names)))
  nil)


;;; `Compute-visible-slots-for-attribute-table' is documented above.

(defun compute-visible-slots-for-attribute-table (item)
  (with-filters
    (filter-restrictions-for-item
      item '(visibility)
      #'filter-attribute-visibility-restrictions nil)))




;;; `Compute-menu-restrictions-for-click-on-table', if given a slot name,
;;; provides restrictions for the menu when clicking on the slot.  With nil, it
;;; provides restrictions for clicking in any other area of the table.

;;; Compute-menu-restrictions-for-click-on-table establishes a with-filters
;;; context and binds slot-name-for-restrictions then maps
;;; filter-table-restrictions the restrictions of the item.

;;; Note that the assertion "the table menu for any ..." is taken to be valid
;;; anywhere on the table including any slot area, and the assertion "the table
;;; menu for the ... of any ..." makes an assertion about a given slot. When
;;; computing the restrictions for a slot, both types of assertion are
;;; examined.


;;; The function `filter-table-restrictions' is mapped over the table
;;; restrictions by compute-menu-restrictions-for-click-on-table.  These
;;; restrictions are of the form: (table (pseudo-class*) (slots*)
;;; restriction-type choices*).  The required dynamic extent includes
;;; slot-alias-for-restrictions and slot-description-for-restrictions.

(defun-simple filter-table-restrictions (restriction-clause item current-item)
  (when (frame-matches-restriction-class-spec item (second restriction-clause) current-item)
    (let ((name-denotations (third restriction-clause)))
      (when (or (null name-denotations)
		(and slot-description-for-restrictions
		     (slot-in-restrictions-list-p
		       item slot-description-for-restrictions name-denotations 'includes))) ; ***
	(filter-new-restriction-set
	  (fourth restriction-clause) (cddddr restriction-clause)))))
  nil)


(defun compute-menu-restrictions-for-click-on-table
    (item slot-name-or-alias? defining-class)
  (with-filters
    (let ((slot-alias-for-restrictions 
	    slot-name-or-alias?)
	  (slot-description-for-restrictions
	    (and slot-name-or-alias?
		 (get-slot-description-for-filters
		   slot-name-or-alias?
		   (class-description-slot item)
		   defining-class))))
      
      ;; *** This must be fixed someday.  Slot components may be restricted, but
      ;; they do not have slot descriptions. -fmw, 4/25/94
      #+development
      (when (and slot-name-or-alias?
		 (not (virtual-attribute slot-name-or-alias?))
		 (null slot-description-for-restrictions))
	(dwarn "Could not find a slot-description for the ~s of ~s."
	       slot-name-or-alias? item))
      
      (filter-restrictions-for-item
	item '(table) #'filter-table-restrictions nil))))





;;; `Compute-non-menu-restrictions-for-item' takes an item and returns two
;;; values a list of choices and a flag indicating if they are permited
;;; or not.  It establishes a with-filters context and maps filter-non-menu-restrictions
;;; over the item's non-menu restrictions.

(defun-simple filter-non-menu-restriction (restriction-clause item current-item)
  (when (frame-matches-restriction-class-spec item (second restriction-clause) current-item)
    (filter-new-restriction-set
      (third restriction-clause) (cdddr restriction-clause)))
  nil)

;; Funcalled via compute-non-menu-restrictions-for-item by filter-restrictions-for-item.


;;; `Compute-non-menu-restrictions-for-item' is documented above.

(defun compute-non-menu-restrictions-for-item (item?)
  (with-filters
    (filter-restrictions-for-item
      item? '(non-menu) #'filter-non-menu-restriction nil)))

;; Called only by non-menu-choice-permitted-p and make-table-describing-restrictions.


;;; `Non-menu-choice-permitted-p' is true of non-menu-choice if it is not
;;; restricted at its particular level in the current KB's hierarchy.

(defun non-menu-choice-permitted-p (non-menu-choice item?)
  (multiple-value-bind (restrictions permitted?)
      (compute-non-menu-restrictions-for-item item?)
    (prog1
      (if (memq non-menu-choice restrictions) permitted? (not permitted?))
      (reclaim-filter-list-macro restrictions))))

;; Called from FACILITIES MOVES RUN




;;; `Workspaces-can-be-shown-at-this-kb-level-p' is true if workspaces can be
;;; shown at block's level of the KB hierarchy in workstation based on the user
;;; mode workstation is in and the KB restrictions at block's level.  Note that
;;; if block is not in the KB hierarchy, e.g. if it is a non-kb workspace or if
;;; block is not an item, this can only return true.  

(defun workspaces-can-be-shown-at-this-kb-level-p (block workstation)
  (or (not (frame-of-class-p block 'item))
      (let ((workspace? (get-workspace-if-any block)))
	(and workspace?
	     (not (frame-of-class-p workspace? 'item))))
      (let ((current-g2-user-mode?	        ; special
	      (g2-user-mode-for-this-workstation? workstation)))
	(non-menu-choice-permitted-p 'show-workspace block))))










;;;; Describe User Restrictions




;;; Make-table-describing-restrictions is called from FACILITIES.  It will
;;; create a table describing the restrictions on an item.

;; I don't quite understand this.  Apparently the description comes in two
;; parts.  
;; The first part describes how the UI is configured in this mode for this
;; item, i.e. 
;;   - selection action or
;;   - menu choices offered.
;;   - table slots visible
;;   - table menus on those slots.

;; The second part is a walk up the KB hierarchy showing the raw contents
;; of the user restriction slots.  Nothing is shown in the
;; second part if no restrictions were specified.

;; The resulting display will have N cells with an arbitrary number taken
;; for the first part and an arbitrary number taken for the second part.

;;; "Restrictions for <designation>"
;;; "Selecting this item ..."
;;; "Menus for this item [include|exclude] ..."
;;; "Non-menu choices for this item [include|exclude] ..."
;;; "Table menus for this item [include|exclude] ..."
;;; For each attribute <A> 
;;;    "The attribute <A> is not visible."
;;; or "Table menus for the <A> of this item [include|exclude] ..."
;;; or "There are no table restrictions for the ~a of this item."
;;; For each item in the hierarchy, with restrictions, 
;;;    "User restrictions for the <designation>  <restrictions>"
;;; or "Class restrictions on <designation>  <restrictions>"
;;; or "User restrictions on <designation> <restrictions>"

(defun make-table-describing-restrictions (item)
  (let* ((write-symbols-in-lower-case? t)
	 choice-restrictions include? single-action-for-click?
	 (header
	   (slot-value-list    
	     (tformat-text-string "Item configuration for ~NF" item)))
	 (selecting-clauses
	   ;; "Selecting this item ..."
	   ;; "Menus for this item [include|exclude] ..."
	   ;; !! This needs to be extended for object configurations (clicking
	   ;; and pressing clauses).
	   (if (or 
		 (multiple-value-setq
		     (choice-restrictions include? single-action-for-click?)
		   (compute-menu-restrictions-for-click-on-workspace item))
		 single-action-for-click?)
	       (prog1
		   (slot-value-list
		     (twith-output-to-text-string
		       (cond
			 (single-action-for-click?
			  (write-restriction-clause-1
			    "Selecting this item"
			    nil nil
			    (case single-action-for-click?
			      (nothing 'does)
			      (t 'implies))
			    single-action-for-click? t))
			 (t
			  (write-restriction-clause-1
			    "Menus for this item"
			    nil nil
			    (if include? 'include 'exclude)
			    choice-restrictions t)))))
		 (if choice-restrictions
		     (reclaim-filter-list choice-restrictions)))))

	 (non-menu-choices
	   ;; "Non-menu choices for this item [include|exclude] ..."
	   (if (multiple-value-setq
		   (choice-restrictions include?)
		 (compute-non-menu-restrictions-for-item item))
	       (prog1
		   (slot-value-list
		     (twith-output-to-text-string
		       (write-restriction-clause-1
			 "Non-menu choices for this item"
			 nil nil
			 (if include? 'include 'exclude)
			 choice-restrictions t)))
		 (reclaim-filter-list choice-restrictions))))

	 (table-menu-choices
	   ;; "Table menus for this item [include|exclude] ..."
	   (if (multiple-value-setq
		   (choice-restrictions include?)
		 (compute-menu-restrictions-for-click-on-table item nil nil))
	       (slot-value-list
		 (twith-output-to-text-string
		   (write-restriction-clause-1
		     "Table menus for this item"
		     nil nil
		     (if include? 'include 'exclude)
		     choice-restrictions t)))))

	 (visibility-restrictions
	   ;; Describe the Table choices for each of the attributes.
	   (prog1
	       ;; For each attribute <A> one of these three:
	       ;; "The attribute <A> is not visible."
	       ;; "Table menus for the <A> of this item [include|exclude] ..."
	       ;; "There are no table restrictions for the ~a of this item."
	       (let ((text-strings ()))
		 (do-attribute-table-slots (item) (slot-name class-qualifier? alias?)
		   (let* ((aliased-slot-name (or alias? slot-name))
			  (text-string?
			    (cond ((include-slot-in-attribute-table-p
				     item aliased-slot-name class-qualifier?)
				   (multiple-value-bind
				       (choice-restrictions-for-slot include-for-slot?)
				       (compute-menu-restrictions-for-click-on-table
					 item aliased-slot-name nil)
				     (when (or (g2-xor include? include-for-slot?)
					       (not (g2-set-equivalent
						      choice-restrictions
						      choice-restrictions-for-slot)))
				       (twith-output-to-text-string
					 (if choice-restrictions-for-slot
					     (write-restriction-clause-1
					       "Table menus for the"
					       aliased-slot-name "this item" 
					       (if include? 'include 'exclude)
					       choice-restrictions-for-slot t)
					     (tformat
					       "There are no table restrictions for the ~a of this item."
					       aliased-slot-name))))))
				  (t
				   (if class-qualifier?
				       (tformat-text-string "The attribute ~(~a::~a~) is not visible."
							    class-qualifier? aliased-slot-name)
				       (tformat-text-string "The attribute ~a is not visible."
							    aliased-slot-name))))))
		     
		     (when text-string?
		       ;; collect text strings and reverseorder:
		       (slot-value-push text-string? text-strings))))
		 (nreverse text-strings))
	     (when choice-restrictions
	       (reclaim-filter-list choice-restrictions))))


	 (active-restrictions
	   (nconc
	     selecting-clauses
	     non-menu-choices
	     table-menu-choices
	     visibility-restrictions))

	 (potential-restrictions
	   (let (list)
	     ;; For each item in the hierarchy, with restrictions, 
	     ;;    "User restrictions for the <designation>  <restrictions>"
	     ;; or "Class restrictions on <designation>  <restrictions>"
	     ;; or "User restrictions on <designation> <restrictions>"
	     (do-standard-search-hierarchy (object-configuration place item)

	       ;; The class, or the class of the instance, must be visible.
	       (when (class-is-visible-to-user-p
		       (if traversing-class-hierarchy?
			   (class-definition-name place)
			   (class place)))
		 (slot-value-push 
		   (twith-output-to-text-string
		     (if (eq place kb-restrictions)
			 (twrite "Item configuration on the KB:")
			 (tformat
			   (if traversing-class-hierarchy?
			       "Instance configuration on ~nf:"
			       "Item configuration on ~nf:")
			   place))
		     (if object-configuration (tformat "~%") (twrite " "))
		     (write-object-configuration object-configuration))
		   list)))
	     (nreverse list)))

	 ;; Visually separate the active object-configuration from the potential ones.
	 (rows-of-text-strings-for-text-cells
	   (if active-restrictions
	       (nconc header active-restrictions (make-table-spacer-cells 2) potential-restrictions)
	       (nconc header potential-restrictions))))
    
    (make-or-reformat-table
      (loop for l on rows-of-text-strings-for-text-cells
	    as format = 'class-format then (choose-font-format-per-fonts-table
					     'borderless-free-text-format
					     'font-for-descriptions)
	    if (text-string-p (car l))
	      do (setf (car l)
		       (slot-value-list
			 (make-text-cell (slot-value-list (car l)) format)))
	    finally (return rows-of-text-strings-for-text-cells))
      (if new-g2-classic-ui-p
	  (get-ui-parameter 'attributes-table-format)
	  'attributes-table-format)
      nil)))



;;;; Restricting Frame Operations Via Proprietary Marks and User Restrictions



;;; This section exports the routine `frame-system-operation-is-allowed-p' along
;;; with a set of names for frame system operations.  This routine allows  
;;; inspect, the evaluators, and the UI to determine if they should proceed with
;;; an operation that requires the use of some fundamental operation of the frame
;;; system.

;;; For example inspect should decline to replace text in attributes that are
;;; restricted from editing in either the current user mode or because they
;;; are proprietary and there are proprietary restrictions on editting
;;; the attribute in question.

;;; Frame system operations are restricted implicitly.  For example changing
;;; the superior of a frame is restricted if any of the KB hierarchy below the
;;; frame contains proprietary knowledge.  Using the editor to change a slot
;;; is restricted if the table menu choice EDIT is excluded on that slot.


(defvar current-filters-search-result)

;;; `contains-proprietary-p' is called on blocks.  It searchs the KB hierarchy
;;; below and including that block to assure that there is no proprietary
;;; knowledge secreted away in that hierarchy.

(defvar contains-proprietary-p-1)

(defun-simple contains-proprietary-p-1 (block superior-block)
  (declare (ignore superior-block))
  (if (proprietary-p block)
      (setf current-filters-search-result t)
      (funcall-function-to-inferior-blocks
	block
	contains-proprietary-p-1)))

(setq contains-proprietary-p-1 #'contains-proprietary-p-1)

(defun contains-proprietary-p (block)
  (let ((current-filters-search-result nil))
    (contains-proprietary-p-1 block nil)
    current-filters-search-result))



;;; `Contains-either-really-transient-or-proprietary-p' takes a block and
;;; searches the KB hierarchy as defined by funcall-function-to-inferior-blocks.
;;; It returns true if the the block contains anything that is proprietary.  It
;;; returns true if we are this G2 has only a runtime or embedded license and the
;;; item contains transient items that have never been permanent.

;;; Generally this is called only when either embedded or runtime-option is 
;;; enabled.

(defvar contains-either-really-transient-or-proprietary-p-1)

(defun-simple contains-either-really-transient-or-proprietary-p-1 (block superior-block)
  (declare (ignore superior-block))
  (cond
    ((proprietary-p block)
     (setf current-filters-search-result t))
    ((and (transient-p block)
	  (not (was-once-permanent-p block)))
     (setf current-filters-search-result t))
    (t
     (funcall-function-to-inferior-blocks 
       block
       contains-either-really-transient-or-proprietary-p-1))))

(setq contains-either-really-transient-or-proprietary-p-1
      #'contains-either-really-transient-or-proprietary-p-1)

(defun contains-either-really-transient-or-proprietary-p (block)
  (let ((current-filters-search-result nil))
    (contains-either-really-transient-or-proprietary-p-1 block nil)
    current-filters-search-result))



;;; `def-restrictable-frame-system-operation' defines a name for a frame system operation
;;; as well as a list of UI operations who's restriction implicitly restrict that
;;; operation.  For example edit-attribute is restricted whenever EDIT is restricted.
;;; CHOOSE-EXISTING-CLASS, CHANGE-TO-YES, CHANGE-TO-NO also restrict the
;;; edit-slot-contents operation as well as NAME on entities & workspaces, and EDIT-ICON
;;; on the icon-description slot of a class-definition.

;;; def-restrictable-frame-system-operation takes a symbol as it's first argument and
;;; that is then defined as a frame system operation.  An empty argument list is then
;;; followed by forms that provide information about this operation.  These forms
;;; are limited to:
;;;   (restricted-if-it-is-proprietary)
;;;    restricted if: (proprietary-p block)
;;;   (restricted-if-it-contains-proprietary)
;;;    restricted if: (contains-proprietary-p block)
;;; The rest all depend upon current-g2-user-mode?
;;;   (restricted-if-slot-not-visible)
;;;    restricted if: (include-slot-in-attribute-table-p block slot-name)
;;;   (restricted-if-all-attributes-are-not-visible)
;;;    restricted if: (multiple-value-bind 
;;;			  (slot-names permitted?)
;;;			  (compute-visible-slots-for-attribute-table block))
;;;			(and permitted? (null slot-names))
;;;   (restricted-by-these-input-operations-on-block . choices)
;;;    restricted if: not (always (non-menu-choice-permitted-p choice block) for choice in choices)
;;;   (restricted-by-these-input-operations-on-slot . table-choices)
;;;    restricted if: (multiple-value-bind 
;;;			  (choice-restrictions permitted?)
;;;			  (compute-menu-restrictions-for-click-on-table block slot-name?)
;;;			(if permitted?
;;;			    ;; All the choices-that-imply-restriction must be permitted
;;;			    (loop for choice in table-choices
;;;				  always (memq choice choice-restrictions))
;;;			    ;; Any
;;;			    (not (loop for choice in table-choices
;;;				       thereis (memq choice choice-restrictions)))))


(defmacro def-restrictable-frame-system-operation 
	  (&whole whole
	   frame-system-operation null-arglist 
	   &body info-about-operation)
  (unless (symbolp frame-system-operation)
    (warn "The operation in a def-restrictable-frame-system-operation was not a symbol: ~S"
	  whole))
  (unless (null null-arglist) 
    (warn "The arg list should be null in def-restrictable-frame-system-operation ~S"
	  frame-system-operation))
  (let ((ui-operations
	  (loop with set-of-input-operations-on-slot
		with other-info
		for info in info-about-operation
		for (kind-of-info ) =  info
		if (not '(restricted-by-these-input-operations-on-slot ; *** BUG *** -fmw. If is no-op.
			   restricted-if-slot-not-visible
			   restricted-if-it-is-proprietary
			   restricted-if-it-contains-proprietary))
		  do (warn "Unknown kind of info provide for restrictable frame system operation.")
		else if (eq kind-of-info 'restricted-by-these-input-operations-on-slot)
		       do
			 (loop for operation in (rest info)
			       do 
			   (pushnew operation set-of-input-operations-on-slot))
		else
		  do
		    (push info other-info)
		finally
		  (return `(,@other-info
			    ,@(when set-of-input-operations-on-slot
				`((restricted-by-these-input-operations-on-slot
				    ,@set-of-input-operations-on-slot))))))))
    `(progn
       (setf (info-for-restrictable-frame-system-operation
	       ',frame-system-operation)
	     ',ui-operations)
       ',frame-system-operation)))



;;; `info-for-restrictable-frame-system-operation' stores the information declared by
;;; def-restrictable-frame-system-operation for each frame system operation in a 
;;; permanent list.

(def-global-property-name info-for-restrictable-frame-system-operation)



;;; The following frame system operations are defined, they maybe restricted implicitly by
;;; some UI operation being restricted.  Once they are restricted G2 will, generally,
;;; decline to perform these operations on the restricted workspace, block, or attribute.
;;;    edit-attribute, an operation on attributes.
;;;    write-attribute, an operation on attributes.
;;;    change-superior, an operation on blocks
;;;    change-set-of-inferiors, an operation on blocks
;;;    block-visible-to-inspect, an operation on blocks
;;;    show-workspace, an operation on kb-workspace

;;; What it means to decline varies.  In the evaluators it means an error is generated.
;;; Inspect generates some output indicating that it was restricted from showing
;;; something.



;;; When edit-attribute is restricted it is not appropriate to make any change to the
;;; attribute utilizing the editor.  This operation is restricted by the table menu choice
;;; edit.  Restriction of edit-attribute restricts, among other things, "change the text
;;; of <place>", replace and highlight in inspect, and reading attribute files.

;; It would be appropriate to restrict some UI operations when this is restricted
;; but that amount of work is inappropriate at this time, i.e. edit-icon, change-to-yes,
;; choose-existing-class, even edit in the item menu, etc.

(def-restrictable-frame-system-operation edit-attribute () ; (block slot)
  (restricted-by-these-input-operations-on-slot 
    edit))



;;; `View-attribute' is a frame system operation that may be implicitly restricted
;;; on attributes if the attribute's visibility is restricted.  Restriction of
;;; view-attribute restricts, amoung other things: writing attribute files, most
;;; operations in inspect, and "the text of <place>".

;; It would be appropriate to restrict some UI operations when this is restricted
;; but that amount of work is inappropriate at this time, i.e. drawing attribute
;; tables, and statements on workspaces.  These have some interesting issues
;; that the workspace's rendering would vary with user mode.

(def-restrictable-frame-system-operation view-attribute () ; (block slot)
  (restricted-if-slot-not-visible))


;;; The function `attribute-is-visible-via-the-text-of-p' is called from
;;; serve-text-of-attribute to determine whether the expression "the text of
;;; <attribute>" is permissable (along with other conditions).

(defun attribute-is-visible-via-the-text-of-p (frame aliased-slot-name class-qualifier?)
  (or (memq aliased-slot-name '(user-restrictions class-restrictions))           ; What is this?  Needed?
      ;; The attribute is restricted for viewing.  Note that for 2.1,
      ;; backward compatibilty, the text of messages and free-text are not
      ;; restricted, even if proprietary.
      (and (or (of-class-p frame 'message) (of-class-p frame 'free-text))
	   (eq aliased-slot-name 'text))
      (let ((slot-description? (get-slot-description-for-filters
				 aliased-slot-name
				 (class-description-slot frame)
				 class-qualifier?)))
	(and slot-description?
	     (attribute-operation-is-allowed-p
	       'view-attribute frame aliased-slot-name (defining-class slot-description?))))))



;;; `Change-superior' is a frame system operation on blocks that may be implicity
;;; restricted by making the block or any block it contains proprietary.  Restricting
;;; change-superior restricts, among other things: the transfer actions.

(def-restrictable-frame-system-operation change-superior () ; (block)
  (restricted-if-it-contains-proprietary))



;;; `Clone-block' is a frame system operation on blocks that may be implictly restricted
;;; by making anything contained inside of the block proprieratry.

(def-restrictable-frame-system-operation clone-block () ; (block)
  (restricted-if-it-contains-proprietary))



;;; `Change-set-of-inferiors' is a frame system operation on blocks that may be implicitly
;;; restricted by making the frame proprietary.  Restricting change-set-of-inferiors
;;; restricts, amoung other things: the transfer actions.

(def-restrictable-frame-system-operation change-set-of-inferiors () ; (block)
  (restricted-if-it-is-proprietary))

;; Currently many operations in the UI are restricted from change-superior and
;; change-set-of-inferiors , but not using the frame-system-operation-is-restricted-p
;; bottleneck.  It may be that not all operations that effect inferior/superior link
;; are restricted yet, delete-subtable, and add-subtable come to mind.



;;; `Change-permanence' is a frame system operation on blocks that may be implicitly
;;; restricted by making the block proprietary.

(def-restrictable-frame-system-operation make-transient () ; (block)
  (restricted-if-it-contains-proprietary))


;;; `Make-permanent' is a frame system operation blocks that is restricted if the
;;; block contains proprietary objects or if we are in a runtime G2 and the item
;;; contains transient items that have never been permanent.

(def-restrictable-frame-system-operation make-permanent () ; (block)
  (restricted-if-it-contains-proprietary-or-when-runtime-contains-never-permanent-transients))

;;; `Block-visible-to-inspect' is a frame system operation on blocks that may be implicitly
;;; restricted either by restricting the visibility of all attributes on the block, or
;;; by restricting the superior workspace of the block.  Restricting block visible
;;; restricts these operations, among others: most inspect operations, and the show
;;; action.

(def-restrictable-frame-system-operation block-visible-to-inspect ()  ; (block)
  (restricted-if-all-attributes-are-not-visible))



;;; `show-workspace' is a frame system operation that is restricted when
;;; the non-menu choice show-workspace is restricted.

(def-restrictable-frame-system-operation show-workspace ()  ; (workspace)
  (restricted-by-these-input-operations-on-block
    show-workspace))



;;; `Development-check-frame-operation-slot-is' supports the following function.

(defmacro development-check-frame-operation-slot-is (case slot-name?)
  #-development (declare (ignore case slot-name?))
  #+development
  (case case
    (:not-supplied
     `(when ,slot-name?
	(error "Inappropriate situation (slot-name? is non-nil) in frame-system-operation-is-restricted-p")))
    (:supplied
     `(unless ,slot-name?
	(error "Inappropriate situation (slot-name? is nil) in frame-system-operation-is-restricted-p")))
    (t (error "Invalid case ~A" case))))



;;; `Frame-system-operation-is-allowed-p' checks if the given frame system operation is
;;; appropriate for the block (and any optionally supplied slot).  The list of frame system
;;; operations is defined above, as well as exactly what can restrict them.  A third
;;; argument may specify the user mode---it defaults to current-g2-user-mode?  or
;;; ADMINISTRATOR if that is nil.  Microtasks that cache the user mode that they were
;;; spawned from should pass this argument.

;;; Not all code that must use this routine actually does.  Some just check the underlying
;;; things that imply the operation is restricted directly.  Other code ignores the issue,
;;; sometimes for backward compatibility, sometimes because you can restrict it by another
;;; route more explicitly, sometimes because we haven't had time to do the work yet.

;; The caller is responsible for checking all objects being operated upon, not
;; just one of them.

(defun frame-system-operation-is-allowed-p (frame-system-operation block)
  (frame-or-attribute-operation-is-allowed-p
    frame-system-operation block nil nil))


;;; The function `attribute-operation-is-allowed-p' is similar for attribute
;;; operations.  It takes the ALIASED (user-visible) slot-name.

(defun attribute-operation-is-allowed-p 
    (attribute-operation block aliased-slot-name defining-class)
  (frame-or-attribute-operation-is-allowed-p
    attribute-operation block aliased-slot-name defining-class))


;;; The function `edit-attribute-allowed-p' returns T if the edit-attribute
;;; operation has not been restricted for the given slot, denoted by its
;;; internal (unaliased) slot name and defining class.

(defun edit-attribute-allowed-p (frame internal-slot-name defining-class?)
  (let ((defining-class
	    (or defining-class?
		(defining-class (get-slot-description-of-frame
				  internal-slot-name
				  frame)))))
    (attribute-operation-is-allowed-p
      'edit-attribute
      frame
      (alias-slot-name-if-necessary internal-slot-name frame)
      defining-class)))




(defun frame-or-attribute-operation-is-allowed-p (frame-system-operation
						   block
						   aliased-slot-name?
						   defining-class?)
  (frame-or-attribute-operation-is-allowed-for-mode-p
    frame-system-operation block aliased-slot-name? defining-class?
    (or (and servicing-workstation?
	     current-g2-user-mode?)
	'administrator)))

(defun frame-or-attribute-operation-is-allowed-for-mode-p (frame-system-operation
						   block
						   aliased-slot-name?
						   defining-class?
						   user-mode)
  (loop with info-for-restrictable-frame-system-operation 
	  = (info-for-restrictable-frame-system-operation frame-system-operation)
	    #+development
	initially
	  #+development
	  (unless info-for-restrictable-frame-system-operation 
	    (error "Unknown restrictable-frame-system-operation: ~S" frame-system-operation))
	;; assume the operation is allowed unless code in the loop body
	;; disallows it by exiting with nil
	finally (return t)
	for (how-implicitly-restricted . optional-args)
	    in info-for-restrictable-frame-system-operation
	do
      (case how-implicitly-restricted
	(restricted-if-it-is-proprietary
	 (when (proprietary-p block) (return nil)))

	(restricted-if-it-contains-proprietary-or-when-runtime-contains-never-permanent-transients
	 (when (if #-pre-g2-v5-licensing
		   nil
		   #+pre-g2-v5-licensing
		   (or (runtime-option-authorized-p)
		       (embedded-option-authorized-p))
		   (contains-either-really-transient-or-proprietary-p block)
		   (contains-proprietary-p block))
	   (return nil)))

	(restricted-if-it-contains-proprietary
	 (when (contains-proprietary-p block) (return nil)))

	(restricted-if-slot-not-visible
	 (development-check-frame-operation-slot-is :supplied aliased-slot-name?)
	 (return
	   (let ((current-g2-user-mode? user-mode))
	     (include-slot-in-attribute-table-p block aliased-slot-name? defining-class?))))

	(restricted-by-these-input-operations-on-slot
	 (let ((choices-that-imply-restriction optional-args))
	   (development-check-frame-operation-slot-is :supplied aliased-slot-name?)
	   (multiple-value-bind 
	       (choice-restrictions permitted? single-action-for-click?)
	       (let ((current-g2-user-mode? user-mode))
		 (compute-menu-restrictions-for-click-on-table block aliased-slot-name? defining-class?))
	     (declare (ignore single-action-for-click?))
	     (let ((result
		     (if permitted?
			 ;; All the choices-that-imply-restriction must be permitted
			 (loop for choice in choices-that-imply-restriction
			       always (memq choice choice-restrictions))
			 ;; Any
			 (not 
			   (loop for choice in choices-that-imply-restriction
				 thereis (memq choice choice-restrictions))))))
	       (reclaim-filter-list choice-restrictions)
	       (return result)))))
	
	(restricted-by-these-input-operations-on-block
	 (development-check-frame-operation-slot-is :not-supplied aliased-slot-name?)
	 ;; currently the only choice is a non-menu choice on the block
	 (unless (loop with choices-that-imply-restriction = optional-args
		       with current-g2-user-mode? = user-mode
		       for non-menu-choice in choices-that-imply-restriction
		       always (non-menu-choice-permitted-p non-menu-choice block))
	   (return nil)))
	
	(restricted-if-all-attributes-are-not-visible
	 (multiple-value-bind 
	     (slot-names permitted?)
	     (let ((current-g2-user-mode? user-mode))
	       (compute-visible-slots-for-attribute-table block))
	   (if (and permitted?
		    (null slot-names))
	       (return nil))))
	#+development
	(t
	 (error "Invalid restriction ~s" how-implicitly-restricted)))))

;; It is unclear if this routine and include-slot-in-attribute-table-p are
;; cooperating about the handling of user mode.






;;;; Mapping Over Restrictions


;;; This section implements the functions that actually know how to walk over 
;;; the restriction hierarchy.  `Filter-restrictions-for-item' is the meaty
;;; one used to map over the entire hierarchy.  

;;; `Compute-user-restrictions-in-kb-restrictions' used for main menu and
;;; keyboard restrictions where only the kb-restrictions system table needs
;;; to be searched.



;;; `Filter-restrictions-for-item' takes an item, a list of restriction-kinds,
;;; and a compiled-function.  It maps that function over all restrictions of that
;;; kind.  It searchs, starting with the item, up the KB-Hierarchy through the
;;; kb-restrictions system table and finally up the class hiearchy.  Within each
;;; item encountered it scans the restrictions bottom to top order (as they are
;;; printed).

;;; The function gets arguments: (restriction-clause item current-item).

;;; Usually the return value is (values <list> <flag/boolean>) where the list
;;; is contains either attribute names or choices.  If flag is NIL, then the
;;; list contains those elements which are forbidden., if the flag is T, then
;;; the list contains those elemets which are permitted.

;;; For example, (values nil nil) means everything is allowed, and (values nil
;;; t) means nothing is allowed.

;;; "Selecting ... [implies/does] ..." restrictions cause the return value
;;; to look like (values nil nil <choice-or-nil>).

;;; Finally if the mapping function is  #'filter-visibility-restrictions the
;;; return value is either IS-VISIBLE, or IS-NOT-VISIBLE. In this case, the fourth
;;; argument is t. (Chestnut did not like the form
;;; (eq function #'filter-visibility-restrictions), hence the new argument.

;;; It must be called within the dynamic extent established by with-filters, and
;;; the documentation for that context provides the details of how this works.

;;; This assumes that current-g2-user-mode? is appropriately bound for the
;;; workstation/user in question.   If not in a for-workstation context, then
;;; current-g2-user-mode? should be bound to the value of the g2-user-mode-for-
;;; this-workstation? slot of the workstation in question.

(defun filter-restrictions-for-item (item-or-class-description?
				      keywords simple-compiled-function
				      filtering-visibility-restrictions?)
  (macrolet ((map-over-restriction-clauses (restriction-clauses)
	       `(loop for restriction-clause in ,restriction-clauses
		      for operation-type = (restriction-clause-operation-type
					     restriction-clause)
		      for restriction-type = (restriction-clause-restriction-type
					       restriction-clause)
		      doing

		  (when (and (memq operation-type keywords)
			     (or (and (null conditional-selected-choice?)
				      (null conditional-termination-state?))
				 ;; Once the conditional search has completed,
				 ;; only absolutely clauses are examined.
				 (eq operation-type 'selecting-absolutely)
				 (eq restriction-type 'exclude-absolutely)))

		    #+development
		    (when trace-configuration-search
		      (format t "*MATCH* ~s " location)
		      (write restriction-clause :pretty t)
		      (terpri))

		    (with-drawing-trace (config)
		      (format t "CONFIG:  Found! ~s on ~s" restriction-clause location))

		    (when (funcall-simple-compiled-function
			    simple-compiled-function restriction-clause
			    item-or-class-description? location)
		      (return-from standard-search))))))

    (let ((proprietary? (and item-or-class-description?
			     (framep item-or-class-description?)
			     (proprietary-p item-or-class-description?))))
      (do-standard-search-hierarchy (object-configuration location item-or-class-description?)
	(loop for clause in object-configuration doing
	  (cond ((user-interface-clause-p clause)
		 (loop for mode-restriction in (cdr clause)
		       as mode-list = (second mode-restriction)
		       doing
		   #+development
		   (when (memq 'proprietary mode-list)
		     (warn "Proprietary mode seen in the mode-list of a user-interface clause."))

		   (when (case (first mode-restriction)
			   ((when)
			    (memq current-g2-user-mode? mode-list))
			   ((unless)
			    (and (neq current-g2-user-mode? 'administrator)
				 (not (memq current-g2-user-mode? mode-list)))))
		     (map-over-restriction-clauses (cddr mode-restriction)))))

		((proprietary-items-clause-p clause)
		 (when (proprietary-instance-p-1 proprietary?
						 traversing-class-hierarchy? location)
		   (map-over-restriction-clauses (cdr clause)))))))))

  (cond (filtering-visibility-restrictions?
	 conditional-termination-state?)

	(absolutely-selected-choice?
	 (reclaim-permitted-restriction-set)
	 (reclaim-prohibited-restriction-set)
	 (cond
	   ((or (memq absolutely-selected-choice?
		      absolutely-prohibited-restriction-set)
		(eq absolutely-selected-choice? choice-conflict))
	    (reclaim-absolutely-prohibited-restriction-set)
	    ;; Here we have either two conflicting "selecting absolutely" clauses,
	    ;; or one such clause which was negated by a "exclude absolutely"
	    (values nil nil 'nothing))
	   (t (reclaim-absolutely-prohibited-restriction-set)
	      (values nil nil absolutely-selected-choice?))))

	(conditional-selected-choice?
	 (reclaim-permitted-restriction-set)
	 (reclaim-prohibited-restriction-set)
	 (cond
	   ((memq conditional-selected-choice?
		  absolutely-prohibited-restriction-set)
	    (reclaim-absolutely-prohibited-restriction-set)
	    ;; Found a "selecting" clause, but its action was "excluded absolutely".
	    (values nil nil 'nothing))
	   (t (reclaim-absolutely-prohibited-restriction-set)
	      (values nil nil conditional-selected-choice?))))

	((eq conditional-termination-state? 'permitted)
	 (reclaim-prohibited-restriction-set)
	 (reclaim-absolutely-prohibited-restriction-set)
	 (values permitted-restriction-set t))

	(t
	 (reclaim-permitted-restriction-set)
	 (reclaim-absolutely-prohibited-restriction-set)
	 (values prohibited-restriction-set nil))))

;; Called by: 
;;   compute-menu-restrictions-for-click-on-workspace passing filter-workspace-menu-restriction
;;   include-slot-in-attribute-table-p                passing filter-visibility-restrictions
;;   compute-menu-restrictions-for-click-on-table     passing filter-table-restrictions
;;   compute-non-menu-restrictions-for-item           passing filter-non-menu-restrictions
;; in this module



;;; The function `compute-user-restrictions-in-kb-restrictions' is used to compute
;;; main-menu restrictions and global keyboard command restrictions.

(defun compute-user-restrictions-in-kb-restrictions
    (user-restrictions-in-slot-of-kb-restrictions)
  (cond
    ((eq current-g2-user-mode? 'administrator)		    ; What about proprietary?
     (values nil nil))
    (t
     (loop with permitted-set = nil
	   with prohibited-set = nil
	   with absolutely-prohibited-set = nil
	   with termination-state? = nil
	   for mode-restriction in user-restrictions-in-slot-of-kb-restrictions
	   as restricted-mode?
	      = (memq current-g2-user-mode? (second mode-restriction))
	   do (when (if (eq (first mode-restriction) 'when)	; "unless" otherwise
			restricted-mode?
			(not restricted-mode?))
		(loop for restriction-clause in (cddr mode-restriction)
		      as restriction-type = (second restriction-clause)
		      as additions = (cddr restriction-clause)
		      do (case restriction-type
			   ((include include-additionally)
			    (unless termination-state?
			      (setq permitted-set
				    (compute-new-restriction-set
				      permitted-set additions
				      prohibited-set absolutely-prohibited-set))
			      (if (eq restriction-type 'include)
				  (setq termination-state? 'include))))

			   ((exclude exclude-additionally)
			    (unless termination-state?
			      (setq prohibited-set
				    (compute-new-restriction-set
				      prohibited-set additions 
				      permitted-set nil))
			      (if (eq restriction-type 'exclude)
				  (setq termination-state? 'exclude))))

			   (exclude-absolutely
			    (setq absolutely-prohibited-set
				  (compute-new-restriction-set
				    absolutely-prohibited-set
				    additions nil nil))
			    (setq permitted-set
				  (remove-from-restriction-set
				    permitted-set
				    ;; Was restriction-clause  -- a bug with no effect.
				    additions))
			    (setq prohibited-set
				  (compute-new-restriction-set
				    prohibited-set additions
				    nil nil))))))

	   finally
	     (return
	       (case termination-state?
		 (include
		  (reclaim-filter-list prohibited-set)
		  (reclaim-filter-list absolutely-prohibited-set)
		  (values permitted-set t))
		 (otherwise
		  (reclaim-filter-list permitted-set)
		  (reclaim-filter-list absolutely-prohibited-set)
		  (values prohibited-set nil))))))))







;;;; Simulating Product Authorization



;;; To enable a KB developer to test his KB in licenses less than
;;; those that his machine is currently configured for we provide
;;; a few slots in the user restrictions system table.  The first
;;; of these "Authorized optional modules for this machine" reports
;;; what the OK object setup for this machine.  This slot is
;;; read only.  

;;; This slot is displayed exactly in the same syntax as the "Authorized
;;; optional modules" slot of the OK object.  It is stored internally
;;; as a list of symbols (unlike the OK object which special cases a
;;; list of one element).

;;; The second slot "Simulated Optional Modules" is editable.  
;;; It's syntax is that of the "Authorized optional modules" plus
;;; a phrase "not currently simulating any optional modules" that
;;; disables simulation.  Internally it is stored as a possible empty 
;;; list of symbols or the value T.  The value T indicates that
;;; we are not simulating.

;;; Simulation runs a parrallel set of books outside those of the actual
;;; authorization.  One part of these is the global
;;; authorized-products-of-this-machine is set by when the OK file is read.
;;; The simulated-optional-modules slot of the installed user-restrictions
;;; system table controls the actual simulation state.

;;; The authorization predicates include checks on the simulated
;;; state, this is obfiscated in the usual way.  When this code
;;; toggles that state it uses one path of conses, and when the
;;; authorization predicates test it they use another path of
;;; conses.

;;; When ever the simulated-optional-modules slot changes set slam all the
;;; toggles into conformance.  If the value is T then we slam them into
;;; conformance with the machines default as recorded in
;;; authorized-products-of-this-machine.  The routine
;;; `setup-current-simulated-product-authorization' does this.
;;; This happens when ever the system table is installed, and when ever
;;; the slot value is changed.  This routine must be clever enough
;;; to do the right thing in when a system table is being uninstalled.

;;; `Setup-current-simulated-product-authorization' also manages the
;;; creation of our frame note.  

;;; We use a frame note to report to users that they are simulating, and
;;; exactly what they are simulating.  This frame note contrasts the the
;;; simulated authorization with the set of all possible authorizations.
;;; By simulating exactly what he is licensed for this frame note will
;;; allows the user to query the details of his license.  That awnsers
;;; questions like what does "runtime, offline, icp" mean?

;;; Since the frame note reports information about a non-saved slot care must
;;; be taken around KB-saving.  This is managed in two parts:
;;; initialize-after-reading method on the frame removes this frame note after
;;; loading, and the frame note writer is a NOP when it is called and there is
;;; no simulation in progress.  Except for this funny case around KB saving
;;; this frame note is found in the frame only when the simulated products are
;;; specified and the frame is the installed system frame.

;; ben  4/23/93




;;; `Setup-current-simulated-product-authorization' is discussed in the
;;; introduction to this section.  This is robust enough to be called even
;;; during the deinstall-system table method, when the global is bound to the
;;; table, but the flag on the table indicates it isn't installed.

(defun setup-current-simulated-product-authorization ()
  (let* ((simulating-p
	   (and (system-table-installed-p kb-restrictions)
		(not (eql t (simulated-optional-modules kb-restrictions)))))
	 (atomic-products-authorized 
	   (atomic-products-authorized
	     (if simulating-p
		 (simulated-optional-modules kb-restrictions)
		 authorized-products-of-this-machine))))
    (delete-frame-note-if-any 'note-status-of-simulated-product-authorization kb-restrictions)
    (setup-atomic-products-for-simulation atomic-products-authorized)
    (when simulating-p
      (add-frame-note 'note-status-of-simulated-product-authorization kb-restrictions))
    (kick-out-unauthorized-telewindows)
    (reclaim-slot-value-list atomic-products-authorized)))



;;; `Setup-atomic-products-for-simulation' is a utility function of 
;;; setup-current-simulated-product-authorization.

(defun setup-atomic-products-for-simulation (list-of-atomic-products)
  (loop for (product nil atomic-product-p) in optional-modules-map
	as simulated-state? = (get product 'simulation-state)
	when atomic-product-p
	  do (setf (second simulated-state?) 
		   (if (memq product list-of-atomic-products)
		       (first simulated-state?)
		       nil))))



;;; `Atomic-products-authorized' takes a list of visible products.  It returns
;;; fresh slot-value list of atomic products (visible and invisible) that are
;;; would be authorized if the user authorized these products.  This is a subfunction
;;; of setup-current-simulated-product-authorization.

(defun atomic-products-authorized (visible-products-authorized)
  (loop with result = nil 
	for visible-product in visible-products-authorized
	as (nil visible-product-bits atomic-product-p) = (assq visible-product optional-modules-map)
	do
	  (cond
	    (atomic-product-p
	     (slot-value-pushnew visible-product result))
	    (t
	     (loop for (known-product known-product-bits known-atomic-product-p) in optional-modules-map
		   do
		     (when known-atomic-product-p
		       (unless (zerop (logandf known-product-bits visible-product-bits))
			 (slot-value-pushnew known-product result))))))
	  finally
	    (when (memq 'offline visible-products-authorized)
	      ;; Consider subtracting these
	      (loop for disabled-product in '(gsi gfi icp)
		    unless (memq disabled-product visible-products-authorized)
		      do (setf result (delete-slot-value-element disabled-product result))))
	    (return result)))



;;; `Psueudo-authorized-optional-modules's slot value writer' is identical to that
;;; for products?, the grammar used in the OK object.

(def-slot-value-writer psueudo-authorized-optional-modules (value)
  (declare (ignore value))
  (write-symbol-list authorized-products-of-this-machine))



;;; `Simulated-products slot value writer' is identical to that
;;; for products? plus it handles the value T emitting 

(def-slot-value-writer simulated-products? (value)
  (if (eql value t)
      (tformat "do not simulate")
      (write-symbol-list value)))



;;; The compiler for `simulated-products?' assures that the
;;; parse is either a list of symbols or T.

(def-slot-value-compiler simulated-products? (parse)
  (cond
    ((consp parse)     (rest parse))
    ((eql 'none parse) nil)
    ((eql 't parse)    parse)
    ((atom parse)    (phrase-cons parse nil))
    (t parse)))



;;; The grammar for `simulated-products?' is just like that for
;;; products? (the slot in the OK object) plus the phrase
;;; "not currently simulating any optional modules".

(def-grammar-category simulated-products? ()
  (('do 'not 'simulate) t)
  (products?))



;;; When the slot `simulated-optional-modules' resynchronize the
;;; simulation if this is the currently installed system table.

(def-slot-putter simulated-optional-modules (kb-restrictions-instance simulated-products?)
  (setf (simulated-optional-modules kb-restrictions-instance) simulated-products?)
  (when (system-table-installed-p kb-restrictions-instance)
    (setup-current-simulated-product-authorization))
  simulated-products?)


;;; Some subtle issues around life cycle of the frame note
;;; `note-status-of-simulated-product-authorization' are mentioned in the
;;; introduction to this section.

(def-frame-note-writer note-status-of-simulated-product-authorization (particulars)
  (declare (ignore particulars))
  (when (listp (simulated-optional-modules kb-restrictions))
    (let* ((simulated-optional-modules (simulated-optional-modules kb-restrictions))
	   (write-symbols-in-lower-case? nil)
	   (offline-is-forced? (memq 'offline authorized-products-of-this-machine))
	   (offline-is-simulated? (memq 'offline (simulated-optional-modules kb-restrictions)))
	   (forced-license-level (license-level authorized-products-of-this-machine))
	   (simulated-license-level (license-level simulated-optional-modules))
	   (visible-atomic-products-suppressed-by-offline
	     (when (or offline-is-forced?
		       offline-is-simulated?)
	       (loop with result finally (return result)
		     for p in '(GSI ICP GFI)
		     when (or (and offline-is-forced?
				   (not (memq p authorized-products-of-this-machine)))
			      (and offline-is-simulated?
				   (not (memq p simulated-optional-modules))))
		       do (slot-value-push p result))))
	   visible-atomic-products-forced-to-not-simulate
	   visible-atomic-products-not-being-simulated
	   visible-atomic-products-being-simulated
	   visible-non-atomic-products-being-simulated)
      
      ;; Accumulate the various catagories of products.
      (loop for (visible-product visible-bits atomic-p invisible-p) in optional-modules-map
	    unless invisible-p
	      do
		(cond
		  ((and atomic-p
			(not (memq visible-product visible-atomic-products-suppressed-by-offline))
			(loop for simulated-product
				  in simulated-optional-modules
			      as (nil simulated-bits) 
				 = (assq simulated-product optional-modules-map)
			      thereis (not (zerop (logandf simulated-bits visible-bits)))))
		   (cond 
		     ((visible-atomic-product-maybe-simulated-on-this-machine-p visible-product)
		      (slot-value-push visible-product visible-atomic-products-being-simulated))
		     (t
		      (slot-value-push visible-product visible-atomic-products-forced-to-not-simulate))))
		  (atomic-p
		   (slot-value-push visible-product visible-atomic-products-not-being-simulated))
		  ((eql 'offline visible-product))
		  ((memq visible-product simulated-optional-modules)
		   (slot-value-push
		     visible-product visible-non-atomic-products-being-simulated))))
      
      
      (let ((minimum-license (minf forced-license-level
				   simulated-license-level)))
	(tformat "G2 is currently simulating ~A ~A license for this machine with the following details."
		 (if (=f 0 minimum-license) "an" "a")
		 (getf '(0 "embedded" 1 "runtime" 2 "restricted-use" 3 "development") 
		       minimum-license)))
      
      (when visible-atomic-products-forced-to-not-simulate
	(tformat "  Warning: the simulation does not include ~L,| ~
                  because ~a not licensed."
		 visible-atomic-products-forced-to-not-simulate
		 (if (cdr visible-atomic-products-forced-to-not-simulate)
		     "they are"
		     "it is")))
      
      (when (<f forced-license-level simulated-license-level)
	(tformat "  Warning: you cannot simulate ~A ~A license on this machine."
		 (if (=f 0 simulated-license-level) "an" "a")
		 (getf '(0 "embedded" 1 "runtime" 2 "restricted-use" 3 "development")
		       simulated-license-level)))
      
      (when visible-atomic-products-being-simulated
	(tformat "  The simulation includes ~L,&."
		 visible-atomic-products-being-simulated))
      
      (when offline-is-forced?
	(tformat "  Licensed only for OFFLINE."))
      (when offline-is-simulated?
	(tformat "  Simulating the limited OFFLINE license."))
      
      ;; What non-atomic products are being simulated that include in
      ;; invisible atomic products.
      (when (and visible-non-atomic-products-being-simulated
		 visible-atomic-products-suppressed-by-offline)
	(loop for non-atomic-product in visible-non-atomic-products-being-simulated
	      do
	  (tformat "  The ~S package is included, but ~L,& ~
                    ~a not included because of OFFLINE."
		   non-atomic-product
		   visible-atomic-products-suppressed-by-offline
		   (if (cdr visible-atomic-products-suppressed-by-offline)
		       "are"
		       "is"))))
      
      (when visible-atomic-products-not-being-simulated
	(tformat "  The simulation does not include ~L,|."
		 visible-atomic-products-not-being-simulated))
      
      (reclaim-slot-value-list visible-atomic-products-forced-to-not-simulate)
      (reclaim-slot-value-list visible-atomic-products-suppressed-by-offline)
      (reclaim-slot-value-list visible-atomic-products-not-being-simulated)
      (reclaim-slot-value-list visible-atomic-products-being-simulated)
      (reclaim-slot-value-list visible-non-atomic-products-being-simulated))))

;; Issues:   (MHD 9/22/93)
;;
;; (1) (when (consp (simulated-optional-modules kb-restrictions)) ...)
;;    is incorrect; it leads to "and note that" followed by nothing
;;    if NONE is entered.
;;    solution: changed to (when (listp ...) ...)
;;
;; (2) "can not" should be "cannot"
;;    solution: changed to "cannot"
;;
;; (3) "these" is singularized as "the", whereas its singular is "this"
;;    solution: "the" changed to "this"
;;    [but see below -- this was all rearranged.]
;;
;; (4) Are two spaces after periods (.) necessary?
;;
;; (5) Can't we have a list-printing directive to tformat to make this
;;    easier to do?
;;    solution: finish implementing the ~L (list) directive for tformat
;;    and use it.
;;
;; (6) "a embedded" wrong (in second case only)
;;    solution: change to "an embedded" (as done for first case)
;;
;; (7) default doesn't clear when you edit it; NONE does. It would be
;; nice if the text cleared when the value = the default in certain
;; cases, such as in the case if this slot.
;;
;; (8) "this machine" repeated too many times -- not really needed
;;   at all, and certainly not beyond the introductory "... for this
;;   machine with the following details:"
;;
;;   solution: change
;;      Warning: the simulation does not include JAPANESE or KOREAN
;;      because this machine does not have these licenses
;;   to 
;;      Warning: the simulation does not include JAPANESE or KOREAN
;;      because they are not licensed
;;
;;   and change
;;      This machine is licensed only for OFFLINE.
;;   to 
;;      Licensed only for OFFLINE.
;;   Don't be bothered by having a sentence fragment; note that not all
;;   of the "details" are complete statements, e.g.,
;;   "Simulating the limited OFFLINE license."
;;
;; (9) PUSH was being used to build up visible-non-atomic-products-being-simulated.
;;   solution: change PUSH to SLOT-VALUE-PUSH.
;;
;; (10) Statements that were supposed to come out like
;;        The RESTRICTED-USE package is included but GSI, ICP, and GFI
;;        are not included because of OFFLINE.
;;      were missing the entire second line above.
;;    solution: fix the paren error causing this -- include the second
;;    line in the loop, instead of having it outside.
;;
;; (11) Doing the a-or-an thing the way it's done here is inelegant
;;
;; (12) "not currently simulating any optional modules" is too wordy,
;;      and usually takes up two lines; why not "none"?
;;   solution: "none" means to simulate, so that can't be used -- note
;;   that we want to tail into (use) the grammar already defined for
;;   the authorized-optional-modules slot of an OK object.  (That's
;;   also why "none" we get "none" => nil for free; see (7), above.)
;;
;;   so: just make it less wordy, and use the grammar "do not simulate".
;;   Now we have
;;
;;      simulated optional modules: DO NOT SIMULATE
;;
;;   as the default.
;;
;; (13) IS should be used in singular case in sentence
;;
;;       but BLAH _is_ not included because of OFFLINE.
;;     solution: fixed.
;;
;; (14) Authorized-optional-modules-for-this-machine -- it seems that
;;   we're tacking on "-for-this-machine" just to distinguish it from
;;   the OK attribute authorized-optional-modules.  I think the "this
;;   machine" is implied, and any remaining confusion is due to its
;;   being a read-only slot.  It's sadder that this takes up two whole
;;   lines in a default attribute table.
;;   
;;    solution: fixed by making them be the same externally, by adding an alias
;;    for the slot: authorized-optional-modules.  They're still the same --
;;    different -- internally.  Note that you could make them be different
;;    externally again by changing the OK object.  That would be changing a
;;    non-item that's never accessed by KBs; it is, however, accessed by
;;    documentation.
;;
;; (15) Use of the term "module" is problematic.  I'd like to lower
;;   confusion between this use of "module" and the use having to
;;   do with KB modularity.  This facilitiy is exacerbating the
;;   situation.
;;
;; (16) Putting this into the kb-restrictions table at all is problematic.
;; These slots have nothing in common with the old slots of kb-restrictions,
;; except perhaps that they all have to do with "security", generically
;; speaking.  Why not make that argument that this should be on
;; module-information, since both facilities deal with "modules", generically
;; speaking? The best solution that comes to mind would be a new system table.
;; It could have these two new slots, as well as slots incorporating the
;; information on the title block (machine type, g2 version, etc.) and in the
;; network information table.
;; 
;; [Ben: I like it, as compaired to other senarios.]






;;; `License-level' is a utility function of
;;; note-status-of-simulated-product-authorization's writer.  It is returns an
;;; integer indicating how "potent" the license implied by the given products
;;; is.

(defun license-level (authorized-products)
  (or
    (loop for product in authorized-products
	  do (case product
	       (embedded (return 0))
	       (runtime (return 1))
	       (restricted-use (return 2))))
    3))



;;; `Visible-atomic-product-maybe-simulated-on-this-machine-p' is a utility
;;; function of note-status-of-simulated-product-authorization's writer.

(defun visible-atomic-product-maybe-simulated-on-this-machine-p (product)
  (or (memq product authorized-products-of-this-machine)
      (eq product 'g1)
      (loop with code = (second-of-long-enough-list (assq product optional-modules-map))
	    for authorized-product in authorized-products-of-this-machine
	    as (nil product-bits atomic-p invisible-p) = (assq authorized-product optional-modules-map)
	    unless (zerop (logandf code product-bits)) do (return t))))




;;; `G2-describe-g2-license' is a system procedure that returns a
;;; large text string showing the table for the OK object which
;;; licensed this G2.  This string is in the formated as if by
;;; the inspect command "write to a file".

;;; Note that the mechanism inside of defun-for-system-procedure,
;;; when told that the return value is a text, automatically
;;; calls make-evaluation-text for its return value.  Therefore,
;;; the body of this function is just the real, internal copy
;;; of the string we want to return.  It looks like we're giving
;;; the user a pointer to our copy, but really we're not.  If
;;; we explicitly copied it here (as we used to), that would be
;;; a leak.

(defun-for-system-procedure g2-describe-g2-license ()
  (declare (values text)
	   (keeps-g2-local-variables-valid t))
  text-representation-of-our-ok-object)


(defun-for-system-procedure set-inherit-stdio-handles (new-value)
  (c-set_inherit_stdio_handles new-value))



;;; `Marshall-exceptional-float-arguments' is a deviously-named system procedure
;;; of no arguments.  It returns a text string that represents the machine ID
;;; used to authorize G2.  If this function cannot locate a machine ID, it
;;; returns an empty text string.  To maintain security, it must not call the
;;; same code we use for periodic ID checks; instead, it does something more
;;; devious.

(defvar foremost-attribute-for-multiplexed-chaining? nil)

(defun-for-system-procedure marshall-exceptional-float-arguments ()
  (cond
    (foremost-attribute-for-multiplexed-chaining?
     (copy-text-string foremost-attribute-for-multiplexed-chaining?))
    (t (let* ((machine-id-tag #w"Machine id")
	      (position-of-machine-id?
		(text-string-search+
		  machine-id-tag
		  text-representation-of-our-ok-object)))
	 (cond
	   (position-of-machine-id?
	    (let ((ok-text-length
		    (text-string-length text-representation-of-our-ok-object)))
	      (loop for i from (+f position-of-machine-id?
				   (text-string-length machine-id-tag))
			  below ok-text-length
		    for this-char
			= (charw text-representation-of-our-ok-object i)
		    do 
		(when (eqlw this-char #.%\")
		  (setq foremost-attribute-for-multiplexed-chaining?
			(twith-output-to-text-string
			  (loop for i2 from (1+f i) below ok-text-length
				for this-char
				    = (charw
					text-representation-of-our-ok-object
					i2)
				do
			    (wide-character-case this-char
			      (#.%\" (loop-finish))
			      (otherwise (twrite-char this-char))))))
		  (return
		    (copy-text-string
		      foremost-attribute-for-multiplexed-chaining?)))
		    finally (return (copy-constant-wide-string #w"")))))
	    (t (copy-constant-wide-string #w"")))))))





;;; `Get-g2-license-level' ... This attempts to "dumb down", i.e., to choose the
;;; less capable license, if we are currently simulating a license.  This is used
;;; when a Telewindows connection is established.

(defun get-g2-license-level ()
  (if (and (boundp 'kb-restrictions)
	   kb-restrictions
	   (system-table-installed-p kb-restrictions)
	   (not (eql t (simulated-optional-modules kb-restrictions))))
      (minf (license-level (simulated-optional-modules kb-restrictions))
	    (license-level authorized-products-of-this-machine))
      (license-level authorized-products-of-this-machine)))

;; NOTE: it is intended that this will be called during the establishment of all
;; Telewindows connections.  For this reason, I (MHD) have piled on an extra
;; layer of paranoia around the evaluation of the kb-restrictions slot just in
;; case it's not called during a fully established KB, e.g., while loading a KB,
;; as if that could happen (I don't know). (MHD 1/30/95)

;; NOTE: guards have to be built to recognize if this dumming down changes, lest
;; we let in a "Trojan Horse".  This dumbing-down feature is intended to allow
;; runtime versions of Telewindows to sometimes connect to full-development
;; G2's, i.e., when they're simulating less capable versions of G2.  Ben has
;; spoken of wanting to implement (the rest of) this feature.  (MHD 1/30/95)





;;;; MHD's notes

;; Table-header can't be restricted in 2.1.  What about 3.0?  
;; apparently the table header can be restricted, even if you don't know it's 
;; "name" by restrictions of the form: "table menu choices for any item exclude:
;; transfer" or "table menu choices for the table-header of any item exclude: 
;; transfer." 

;; Creation implies editing, but shouldn't be taken.

;; Non-menu choices
;; ----------------
;;
;; A few facts:
;;   restricting CLICK-TO-EDIT does not restrict the menu choice EDIT




;;;; Item-configuration category evaluator interface






;;; `fix-acceptable-applicable-items-for-object-configuration' and
;;; `make-acceptable-applicable-items-for-object-configuration' are helper functions
;;; for the object-configuration category evaluator interface. They make up for
;;; some of the shenannigans that go on in the grammar-rule transforms that
;;; implement the parser this slot/category.

(defun-simple fix-acceptable-applicable-items-for-object-configuration (evaluation-value)
  (if (evaluation-sequence-p evaluation-value)
      (let ((thing
	      (with-evaluation-sequence-to-phrase-list-mapping (evaluation-value element)
		element)))
	(if (and (eq (car thing) 'this)
		 (null (cddr thing))
		 (cdr thing))
	    (cadr thing)
	    thing))
      nil))
  
(defun make-acceptable-applicable-items-for-object-configuration (slot-value)
  (cond
    ((null slot-value)
     slot-value)
    ((consp slot-value)
     (with-list-to-evaluation-sequence-mapping (slot-value element)
       element))
    (t
     (let ((thing (gensym-list 'this slot-value)))
       (prog1
	   (with-list-to-evaluation-sequence-mapping (thing element)
	     element)
	 (reclaim-gensym-list thing))))))






;;;; Item configuration slot-value access macros
;; Note that these are not setf-able

(defmacro internal-configuration-type (object-configuration)
  `(car ,object-configuration))
;; Returns the type of configuration for a single configuration
;; Note that the slot object-configuration holds a list of
;; these configurations.

(defmacro internal-operation-type (configuration-clause)
  `(car ,configuration-clause))

(defmacro internal-restriction-type (configuration-clause)
  `(let ((internal-operation-type
	   (internal-operation-type ,configuration-clause)))
     (case internal-operation-type
       ((table visibility)
	(fourth ,configuration-clause))
       (t
	(third ,configuration-clause)))))

(defmacro menu-choices (configuration-clause)
  `(let ((internal-operation-type
	   (internal-operation-type ,configuration-clause)))
     (case internal-operation-type
       (table
	(cddddr ,configuration-clause))
       (t
	(cdddr ,configuration-clause)))))

(defmacro applicable-attributes (configuration-clause)
  `(when (eq (internal-operation-type ,configuration-clause) 'table)
     (third ,configuration-clause)))

(defmacro applicable-items (configuration-clause)
  `(second ,configuration-clause))




;;;; Item Configuration conversion macros
;; Note that these are not setf-able

(defmacro internal-to-external-configuration-type-name (internal-type-name)
  `(let ((internal-name ,internal-type-name))
     (case internal-name
       (user-interface 'configure-user-interface)
       (proprietary 'restrict-proprietary-items)
       (network-access 'set-up-network-access)
       (declaration 'declare-properties)
       (comment 'comment))))

(defmacro external-to-internal-configuration-type-name (external-type-name)
  `(let ((external-name ,external-type-name))
     (case external-name
       (configure-user-interface 'user-interface)
       (restrict-proprietary-items 'proprietary)
       (set-up-network-access 'network-access)
       (declare-properties 'declaration)
       (comment 'comment))))

(defmacro external-to-internal-operation-type (external-operation-type)
  `(let ((op-type ,external-operation-type))
     (case op-type
       (item-menu 'workspace-menu)
       (table-menu 'table)
       (attribute-visibility 'visibility)
       (typing 'pressing)
       ((pressing releasing) 'clicking)
       (moving 'constrain)
       (t op-type))))

(defmacro internal-to-external-operation-type (internal-operation-type)
  `(let ((int-op-type ,internal-operation-type))
     (case int-op-type
       (workspace-menu 'item-menu)
       (table 'table-menu)
       (visibility 'attribute-visibility)
       (pressing 'typing)
       (clicking 'pressing-or-releasing) ; see differentiate-pressing-from-releasing
       (constrain 'moving)
       (t int-op-type))))

(defun differentiate-pressing-from-releasing (key-code)
  (cond ((key-code-is-mouse-select-p key-code)
	 'clicking)
	((key-code-is-mouse-up-p key-code)
	 'releasing)
	(t
	 'pressing)))

(defmacro external-to-internal-network-restriction-type (restriction-type)
  `(case ,restriction-type
     (allow 'include-additionally)
     (prohibit 'exclude-additionally)
     (prohibit-absolutely 'exclude-absolutely)))

(defmacro internal-to-external-network-restriction-type (restriction-type)
  `(case ,restriction-type
     (include-additionally 'allow)
     (exclude-additionally 'prohibit)
     (exclude-absolutely 'prohibit-absolutely)))




;;;; Item Configuration category name macros
;; Note that these are not setf-able

(defmacro external-object-configuration-type-to-category-name (external-name)
  `,external-name)

(defmacro internal-operation-type-to-category-name (internal-op-type)
  `(let ((internal-operation-type ,internal-op-type))
     (case internal-operation-type
       (#.menu-configuration-operation-types
	'menu-configurations)
       (table 'table-menu-configurations)
       (visibility 'attribute-visibility-configurations)
       (clicking 'configure-mouse-click)
       (pressing 'configure-keystroke)
       (hovering 'configure-keystroke)	; Mouse hovering is more like a keystroke than a mouse button.
       ((selecting selecting-absolutely) 'configure-selection)
       (constrain 'constrain-movement-of-items))))







(define-category-evaluator-interface (menu-and-attribute-visibility-configurations-restriction-type
				       :access read-write)
    (member . #.menu-and-attribute-visibility-configurations-restriction-types)
  
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))

(define-category-evaluator-interface (table-menu-choice
				       :access read-write)
    (member . #.table-menu-choices)
  ((set-form (menu-choice))
   menu-choice)
  ((get-form (menu-choice))
   menu-choice))

(define-category-evaluator-interface (table-menu-choices
				       :access read-write)
    (sequence (named table-menu-choice) 0)

  ((set-form (menu-choices))
   (with-safe-category-setter-calling
       (with-evaluation-sequence-to-phrase-list-mapping
	   (menu-choices menu-choice-element)
	 (call-category-setter-safely 'table-menu-choice
				      menu-choice-element))))
  ((get-form (internal-menu-choices))
   (with-list-to-evaluation-sequence-mapping
       (internal-menu-choices source-menu-choice-element)
     (call-category-getter 'table-menu-choice
			   source-menu-choice-element
			   nil nil))))

(define-category-evaluator-interface (menu-choices
				       :access read-write)
    (sequence symbol 0) ;pbk (or (member) symbol) ??

  ((set-form (menu-choices))
   (with-evaluation-sequence-to-phrase-list-mapping
       (menu-choices menu-choice-element)
     menu-choice-element))
  ((get-form (internal-menu-choices))
   (with-list-to-evaluation-sequence-mapping
       (internal-menu-choices source-menu-choice-element)
     source-menu-choice-element)))

(define-category-evaluator-interface (table-menu-configurations
				       :access read-write)
    (structure table-menu-configurations-spec
	       ((operation-type (member table-menu))
		(restriction-type
		  (named menu-and-attribute-visibility-configurations-restriction-type))
		(menu-choices (named table-menu-choices))
		(applicable-attributes (sequence symbol 0)) 
		(applicable-items (sequence symbol 1)))
	       (and operation-type menu-choices applicable-items restriction-type))
  
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value table-menu-configurations-spec)
	 (phrase-cons
	   (external-to-internal-operation-type operation-type)
	   (nconc
	     (if (null applicable-attributes)
		 (phrase-list
		   (fix-acceptable-applicable-items-for-object-configuration applicable-items)
		   restriction-type)
		 (phrase-list
		   (fix-acceptable-applicable-items-for-object-configuration applicable-items)
		   (with-evaluation-sequence-to-phrase-list-mapping
		       (applicable-attributes attribute-element)
		     attribute-element)
		   restriction-type))
	     (call-category-setter-safely 'table-menu-choices
					  menu-choices))))))
  ((get-form (slot-value))
   (with-new-structure (table-menu-configurations-spec)
     (setf operation-type
	   (internal-to-external-operation-type (internal-operation-type slot-value)))
     (setf restriction-type (internal-restriction-type slot-value))
     (setf menu-choices
	   (call-category-getter 'table-menu-choices (menu-choices slot-value) nil nil))
     (setf applicable-attributes
	   (with-list-to-evaluation-sequence-mapping
	       ((applicable-attributes slot-value) source-attribute-element)
	     source-attribute-element))
     (setf applicable-items
	   (make-acceptable-applicable-items-for-object-configuration
	     (applicable-items slot-value))))))
    

(define-category-evaluator-interface (menu-configurations
				       :access read-write)
    (structure menu-configurations-spec
	       ((operation-type (member workspace-menu item-menu non-menu))
		(restriction-type
		  (named menu-and-attribute-visibility-configurations-restriction-type))
		(menu-choices (named menu-choices))
		(applicable-items (sequence symbol 1)))
	       (and operation-type menu-choices applicable-items restriction-type))
  
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value menu-configurations-spec)
	 (phrase-cons
	   (external-to-internal-operation-type operation-type)
	   (nconc
	     (phrase-list
	       (fix-acceptable-applicable-items-for-object-configuration applicable-items)
	       restriction-type)
	     (call-category-setter-safely 'menu-choices
					  menu-choices))))))
  ((get-form (slot-value))
   (with-new-structure (menu-configurations-spec)
     (setf operation-type
	   (internal-to-external-operation-type (internal-operation-type slot-value)))
     (setf restriction-type (internal-restriction-type slot-value))
     (setf menu-choices
	   (call-category-getter 'menu-choices (menu-choices slot-value) nil nil))
     (setf applicable-items
	   (make-acceptable-applicable-items-for-object-configuration
	     (applicable-items slot-value))))))




(define-category-evaluator-interface (attribute-visibility-configurations
				       :access read-write)
    (structure attribute-visibility-configurations-spec
	       ((operation-type (member attribute-visibility))
		(restriction-type
		  (named menu-and-attribute-visibility-configurations-restriction-type))
		(attributes (sequence symbol 0))
		(applicable-items (sequence symbol 1)))
	       (and operation-type attributes applicable-items restriction-type))

  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value attribute-visibility-configurations-spec)
	 (phrase-cons
	   (external-to-internal-operation-type operation-type) 
	   (phrase-list
	     (fix-acceptable-applicable-items-for-object-configuration applicable-items)
	     (with-evaluation-sequence-to-phrase-list-mapping (attributes attribute-element)
	       attribute-element)
	     restriction-type)))))
  ((get-form (slot-value))
   (with-new-structure (attribute-visibility-configurations-spec)
     (setf operation-type 
	   (internal-to-external-operation-type (internal-operation-type slot-value)))
     (setf attributes
	   (with-list-to-evaluation-sequence-mapping
	       ((third slot-value) source-attribute-element)
	     source-attribute-element))
     (setf restriction-type (internal-restriction-type slot-value))
     (setf applicable-items
	   (make-acceptable-applicable-items-for-object-configuration
	     (applicable-items slot-value))))))




(define-category-evaluator-interface (user-interface-consequent-action
				       :access read-write)
    (or (or (member . #.item-menu-choices)
	    symbol)
	(structure mouse-tracking-spec
		   ((mouse-tracking-procedure-name symbol)
		    (mouse-tracking-applicable-items (sequence symbol 1))
		    (mouse-motion-tracking? truth-value))
		   (and mouse-tracking-procedure-name
			mouse-tracking-applicable-items)))
  
  ((set-form (consequent-action))
   (cond ((symbolp consequent-action)
	  consequent-action)
	 (t ;;(evaluation-structure-p consequent-action)
	  (with-structure (consequent-action mouse-tracking-spec)
	    (let ((mouse-tracking-applicable-items-info
		    (fix-acceptable-applicable-items-for-object-configuration
		      mouse-tracking-applicable-items)))
	      (if (null mouse-motion-tracking?) ;;????pbk
		  (phrase-list 'user-mouse-tracking mouse-tracking-procedure-name
			       mouse-tracking-applicable-items-info)
		  (phrase-list 'user-mouse-tracking mouse-tracking-procedure-name
			       mouse-tracking-applicable-items-info 'motion)))))))
  ((get-form (source-consequent-action))
   (if (consp source-consequent-action)
       (with-new-structure (mouse-tracking-spec)
	 (gensym-dstruct-bind ((nil source-mouse-tracking-procedure-name
				   source-mouse-tracking-applicable-items
				   source-mouse-motion)
			      source-consequent-action)
	   (setf mouse-tracking-procedure-name source-mouse-tracking-procedure-name)
	   (setf-non-nil 
	     mouse-tracking-applicable-items 
	     (make-acceptable-applicable-items-for-object-configuration
	       source-mouse-tracking-applicable-items))
	   (when source-mouse-motion 
	       (setf mouse-motion-tracking? evaluation-true-value))))
       source-consequent-action)))

(define-category-evaluator-interface (modifier-key
				       :access read-write)
    (member control shift alt)
  
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))


(define-category-evaluator-interface (keyboard-symbol
				       :access read-write)
    (member . #.bindable-keysyms)
  
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))

(define-category-evaluator-interface (mouse-button
				       :access read-write)
    (member any left middle right)

  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))



(defun exported-key-modifier-bits (key-code)
  (logiorf (if (shift-bit-on-p key-code) 1 0)
	   (if (or (control-bit-on-p key-code)
		   (special-control-key-p key-code))
	       2 0)
	   (if (alternate-bit-on-p key-code) 4 0)
	   (if (double-bit-on-p key-code) 8 0)))

(defun key-symbol (key-code)
  (convert-key-code-to-key-symbol
    (let* ((index1 (key-index key-code))
	   (index2 (if (special-control-key-p index1)
		       (logiorf index1 64)
		       index1)))
      (upcase-letter-key-code index2))))


(defmacro canonical-control-key-p (canonical-modifiers)
  `(/=f (logandf ,canonical-modifiers 2) 0))

(defmacro canonical-alt-key-p (canonical-modifiers)
  `(/=f (logandf ,canonical-modifiers 4) 0))

(defmacro canonical-shift-key-p (canonical-modifiers)
  `(/=f (logandf ,canonical-modifiers 1) 0))

(defmacro canonical-double-key-p (canonical-modifiers)
  `(/=f (logandf ,canonical-modifiers 8) 0))


(define-category-evaluator-interface (user-interface-key-chord
				       :access read-write)
    (structure key-chord
	       ((modifiers integer)
		(keyboard-symbol (named keyboard-symbol)))
	       (and modifiers keyboard-symbol))

  ((set-form (evaluation-value))
   (with-structure (evaluation-value key-chord)
     (let ((key-spec (gensym-list keyboard-symbol)))
       (when (canonical-control-key-p modifiers)
	 (gensym-push 'control key-spec))
       (when (canonical-shift-key-p modifiers)
	 (gensym-push 'shift key-spec))
       (when (canonical-alt-key-p modifiers)
	 (gensym-push 'alt key-spec))
       (prog1 (key-code key-spec)
	 (reclaim-gensym-list key-spec)))))
  ((get-form (key-code))
   (with-new-structure (key-chord)
     (when (upper-case-letter-key-code-p key-code)
       (setq key-code
	     (logiorf (invert-case-of-letter-key-code key-code) shift-bit)))
     (setf keyboard-symbol
	   (key-symbol key-code))
     (setf modifiers (exported-key-modifier-bits key-code)))))


       

(define-category-evaluator-interface (configure-keystroke
				       :access read-write)
    (structure
      configure-keystroke-spec
      ((operation-type (member typing hovering))
       (key-code (named user-interface-key-chord))
       (consequent-action (named user-interface-consequent-action))
       (applicable-items (sequence symbol 1)))
      (and operation-type key-code consequent-action))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value configure-keystroke-spec)
	 (phrase-cons
	   (external-to-internal-operation-type operation-type)
	   (let ((consequent-action-info
		   (call-category-setter-safely
		     'user-interface-consequent-action
		     consequent-action))
		 (applicable-items-info
		   (fix-acceptable-applicable-items-for-object-configuration
		     applicable-items))
		 (internal-key-code
		   (call-category-setter-safely
		     'user-interface-key-chord
		     key-code)))
	     (phrase-list internal-key-code
			  consequent-action-info
			  applicable-items-info))))))
  ((get-form (slot-value))
   (with-new-structure (configure-keystroke-spec)
     (setf operation-type
	   (internal-to-external-operation-type
	     (internal-operation-type slot-value)))
     (gensym-dstruct-bind ((nil source-key-code
			       source-consequent-action
			       source-applicable-items)
			  slot-value)
       (setf key-code
	     (call-category-getter
	       'user-interface-key-chord
	       source-key-code
	       nil nil))
       (setf consequent-action
	     (call-category-getter
	       'user-interface-consequent-action
	       source-consequent-action
	       nil nil))
       (setf-non-nil applicable-items
		     (make-acceptable-applicable-items-for-object-configuration
		       source-applicable-items))))))


;;; The function `import-mouse-chord' compute the key-code to store into an
;;; item-configuration given the external form which is a 4-bit bitmask of
;;; modifier bits and a button name (left,middle,right,any).

(defun import-mouse-chord (operation-type modifiers button)
  (let ((key-spec nil))
    (when (canonical-control-key-p modifiers)
      (gensym-push 'control key-spec))
    (when (canonical-shift-key-p modifiers)
      (gensym-push 'shift key-spec))
    (when (canonical-alt-key-p modifiers)
      (gensym-push 'alt key-spec))
    (when (canonical-double-key-p modifiers)
      (gensym-push 'double key-spec))
    (let ((mouse-key-name
	    (case operation-type
	      (pressing
	       (case button
		 (left 'mouse-left-down)
		 (middle 'mouse-middle-down)
		 (right 'mouse-right-down)
		 (any 'mouse-down)))
	      (releasing
	       (case button
		 (left 'mouse-left-up)
		 (middle 'mouse-middle-up)
		 (right 'mouse-right-up)
		 (any 'mouse-up)))
	      (clicking
	       (case button
		 (left 'mouse-left-select)
		 (middle 'mouse-middle-select)
		 (right 'mouse-right-select)
		 (any 'mouse-select)))
	      (t
	       (dwarn "Unknown operation type ~s in import-mouse-chord" operation-type)
	       'mouse-select))))
      (gensym-push mouse-key-name key-spec))
    (prog1
	(key-code key-spec)
      (reclaim-gensym-list key-spec))))

;; TODO: don't get clicking clauses out of this.

(defun check-for-disallowed-mouse-chord (operation-type modifiers button)
  (declare (ignore button))
  (when (and (canonical-double-key-p modifiers)
	         (not (memq operation-type '(pressing clicking))))
    "The double-bit is permitted only with operation-type PRESSING."))


(define-category-evaluator-interface (configure-mouse-click
				       :access read-write)
    (structure
      configure-mouse-click-spec
      ((operation-type (member pressing releasing clicking))
       (key-code  (structure mouse-chord
			     ((modifiers integer)
			      (mouse-button (named mouse-button)))
			     (and mouse-button)))
       (consequent-action (named user-interface-consequent-action))
       (applicable-items (sequence symbol 1)))
      (and operation-type key-code consequent-action))
  
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value configure-mouse-click-spec)
	 (let ((error-message?
		 (with-structure (key-code mouse-chord)
		   (check-for-disallowed-mouse-chord operation-type modifiers mouse-button))))
	   (cond (error-message?
		  (values bad-phrase (copy-text-string error-message?)))
		 (t
		  (phrase-cons
		    (external-to-internal-operation-type operation-type)
		    (let ((consequent-action-info
			    (call-category-setter-safely
			      'user-interface-consequent-action
			      consequent-action))
			  (applicable-items-info
			    (fix-acceptable-applicable-items-for-object-configuration
			      applicable-items))
			  (internal-key-code
			    (with-structure (key-code mouse-chord)
			      (import-mouse-chord operation-type modifiers mouse-button))))
		      (phrase-list internal-key-code
				   consequent-action-info
				   applicable-items-info)))))))))
  ((get-form (slot-value))		; eg (CLICKING 770 INSPECT NIL)
   (with-new-structure (configure-mouse-click-spec)
     (setf operation-type
	   (let ((external-type
		   (internal-to-external-operation-type
		     (internal-operation-type slot-value))))
	     (cond ((eq external-type 'pressing-or-releasing)
		    (differentiate-pressing-from-releasing
		      (cadr slot-value))) ; (user-interface-clause-key-code slot-value)
		   (t external-type))))
     (gensym-dstruct-bind ((nil		; So much for abstraction
			    source-key-code
			    source-consequent-action
			    source-applicable-items)
			  slot-value)
       (setf key-code
	     (with-new-structure (mouse-chord)
	       (when (upper-case-letter-key-code-p source-key-code)
		 (setq source-key-code
		       (logiorf
			 (invert-case-of-letter-key-code source-key-code)
			 shift-bit)))
	       (setf mouse-button (key-code-mouse-button-name source-key-code))
	       (setf modifiers (exported-key-modifier-bits source-key-code))))
       (setf consequent-action
	     (call-category-getter
	       'user-interface-consequent-action
	       source-consequent-action
	       nil nil))
       (setf-non-nil applicable-items
		     (make-acceptable-applicable-items-for-object-configuration
		       source-applicable-items))))))






(define-category-evaluator-interface (configure-selection
				       :access read-write)
    (structure
      configure-selection-spec
      ((operation-type (member selecting selecting-absolutely))
       (consequent-action (named user-interface-consequent-action))
       (applicable-items (sequence symbol 1)))
      (and operation-type consequent-action))
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value configure-selection-spec)
	 (phrase-cons
	   (external-to-internal-operation-type operation-type)
	   (let ((consequent-action-info
		   (call-category-setter-safely
		     'user-interface-consequent-action
		     consequent-action))
		 (applicable-items-info
		   (fix-acceptable-applicable-items-for-object-configuration
		     applicable-items)))
	     (phrase-list
	       applicable-items-info
	       consequent-action-info))))))
  ((get-form (slot-value))
   (with-new-structure (configure-selection-spec)
     (gensym-dstruct-bind ((internal-operation-type source-applicable-items source-consequent-action)
			  slot-value)
       (setf operation-type
	     (internal-to-external-operation-type internal-operation-type))
       (setf consequent-action source-consequent-action)
       (setf-non-nil
	 applicable-items
	 (make-acceptable-applicable-items-for-object-configuration
	   source-applicable-items))))))

(define-category-evaluator-interface (rectangle
					:access read-write)
    (structure rectangle-spec
	       ((left-edge integer)
		(right-edge integer)
		(top-edge integer)
		(bottom-edge integer))
	       (and left-edge right-edge top-edge bottom-edge))
  
  ((set-form (evaluation-value))
   (with-structure (evaluation-value rectangle-spec)
     (phrase-list left-edge right-edge top-edge bottom-edge)))
  ((get-form (source-constrained-region))
   (with-new-structure (rectangle-spec)
     (gensym-dstruct-bind ((source-left-edge source-right-edge
					    source-top-edge source-bottom-edge)
			  source-constrained-region)
       (setf left-edge source-left-edge)
       (setf right-edge source-right-edge)
       (setf top-edge source-top-edge)
       (setf bottom-edge source-bottom-edge)))))

(define-category-evaluator-interface (grid
				       :access read-write)
    (structure grid-spec
	       ((x-grid-length integer)
		(y-grid-length integer))
	       (and x-grid-length y-grid-length))

  ((set-form (evaluation-value))
   (with-structure (evaluation-value grid-spec)
     (cond ((not (<f 0 x-grid-length))
	    (values bad-phrase
		    (tformat-text-string
		     "The x-grid-length, ~NV, must be positive"
		     x-grid-length)))
	   ((not (<f 0 y-grid-length))
	    (values bad-phrase
		    (tformat-text-string
		     "The y-grid-length, ~NV, must be positive"
		     y-grid-length)))
	   (t
	    (phrase-cons x-grid-length y-grid-length)))))
  ((get-form (source-constrained-region))
   (with-new-structure (grid-spec)
     (setf x-grid-length (car source-constrained-region))
     (setf y-grid-length (cdr source-constrained-region)))))

    

(define-category-evaluator-interface (constrain-movement-of-items
				       :access read-write)
    (structure
      constrain-movement-of-items-spec
      ((operation-type (member moving)) ;;pbk/jpt why not constrain-moving ???
       (type-of-region (member rectangle grid)) 
       (constrained-region (or (named rectangle)
			       (named grid)))
       (applicable-items (sequence symbol 1)))
      (and operation-type type-of-region constrained-region applicable-items))
  
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-structure (evaluation-value constrain-movement-of-items-spec)
	 (let* ((applicable-items-info
		  (fix-acceptable-applicable-items-for-object-configuration
		    applicable-items))
		(type-of-region-info
		  (if (eq type-of-region 'rectangle)
		      type-of-region
		      'moving))
		(constrained-region-category-name
		  type-of-region)
		(constrained-region-info
		  (call-category-setter-safely
		    constrained-region-category-name
		    constrained-region)))
	   (phrase-list 'constrain
			type-of-region-info
			applicable-items-info
			constrained-region-info)))))
  ((get-form (slot-value))
   (with-new-structure (constrain-movement-of-items-spec)
     (gensym-dstruct-bind ((nil source-type-of-region
			       source-applicable-items
			       source-constrained-region)
			  slot-value)
       (setf operation-type 'moving)
       (setf type-of-region
	     (if (eq source-type-of-region 'moving)
		 'grid
		 'rectangle))
       (setf constrained-region	     
	     (call-category-getter
	       type-of-region 
	       source-constrained-region
	       nil nil))
       (setf applicable-items
	     (make-acceptable-applicable-items-for-object-configuration
	       source-applicable-items))))))







(define-category-evaluator-interface (restrict-proprietary-items-and-configure-user-interface-statement
				       :access read-write)
    (or (named menu-configurations)
	(named table-menu-configurations)
	(named attribute-visibility-configurations)
	(named configure-mouse-click)
	(named configure-keystroke)
	(named configure-selection)
	(named constrain-movement-of-items))

  ((set-form (statement-element))
   (with-safe-category-setter-calling
       (let* ((external-type
		(evaluation-structure-slot statement-element 'operation-type))
	      (category-name-for-operation-type
		(internal-operation-type-to-category-name
		  (external-to-internal-operation-type external-type))))
	 (call-category-setter-safely category-name-for-operation-type
				      statement-element))))
  ((get-form (statement-element))
   (let ((category-name-for-operation-type
	   (internal-operation-type-to-category-name
	     (internal-operation-type statement-element))))
     (call-category-getter category-name-for-operation-type
			   statement-element nil nil))))

(define-category-evaluator-interface (configure-user-interface-statements
				       :access read-write)
    (sequence (named restrict-proprietary-items-and-configure-user-interface-statement)
	      1)
  
  ((set-form (statements))
   (with-safe-category-setter-calling
       (with-evaluation-sequence-to-phrase-list-mapping
	   (statements statement-element)
	 (call-category-setter-safely
	   'restrict-proprietary-items-and-configure-user-interface-statement
	   statement-element))))
  ((get-form (statements))
   (nreverse-evaluation-sequence
     (with-list-to-evaluation-sequence-mapping (statements statement-element)
       (call-category-getter
	 'restrict-proprietary-items-and-configure-user-interface-statement
	 statement-element nil nil)))))





(define-category-evaluator-interface (applicable-user-modes
				       :access read-write)
    (structure applicable-user-modes
	       ((negative truth-value)
		(modes (sequence (named unreserved-symbol)
				 1)))
	       (and modes))
  
  ((set-form (applicable-user-modes))
   (with-structure (applicable-user-modes applicable-user-modes)
     (phrase-list
       (if (and (evaluation-truth-value-p negative)
		(evaluation-truth-value-is-true-p negative))
	   'unless
	   'when)
       (with-evaluation-sequence-to-phrase-list-mapping
	   (modes mode)
	 mode))))
  ((get-form (configure-user-interface-info))
   (with-new-structure (applicable-user-modes)
     (setf negative
	   (if (eq (car configure-user-interface-info) 'unless)
	       evaluation-true-value
	       evaluation-false-value))
     (setf modes (allocate-evaluation-sequence
		   (copy-list-using-eval-conses
		     (second configure-user-interface-info)))))))





;;; `configure-user-interface'
;;; The following is the category evaluator interface
;;; for configuring the user interface.
;;; The statements attribute may be a sequence of the following:
;;; menu-configurations, table-menu-configurations,attribute-visibility-configurations
;;; configure-mouse-click, configure-keystroke, configure-selection,
;;; and constrain-movement-of-items.

(define-category-evaluator-interface (configure-user-interface
				       :access read-write)
    (sequence (structure configure-user-interface-spec
			 ((applicable-user-modes (named applicable-user-modes))
			  (statements (named configure-user-interface-statements)))
			 (and applicable-user-modes statements))
	      1)
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (with-evaluation-sequence-to-phrase-list-mapping
	   (evaluation-value configure-user-interface-info)
	 (with-structure (configure-user-interface-info configure-user-interface-spec)
	   (nconc
	     (call-category-setter-safely 'applicable-user-modes applicable-user-modes)
	     (call-category-setter-safely 'configure-user-interface-statements
					  statements))))))
  ((get-form (slot-value))
   (nreverse-evaluation-sequence
    (with-list-to-evaluation-sequence-mapping (slot-value configure-user-interface-info)
     (with-new-structure (configure-user-interface-spec)
       (setf applicable-user-modes
	     (call-category-getter 'applicable-user-modes
				   configure-user-interface-info
				   nil nil))
       (setf statements
	     (call-category-getter 'configure-user-interface-statements
				   (cddr configure-user-interface-info)
				   nil nil)))))))
 

;;; The category evaluator interface for
;;; `restrict-proprietary-items' configuration.
;;; May be a sequence of the following:
;;; menu-configurations, table-menu-configurations,attribute-visibility-configurations
;;; configure-mouse-click, configure-keystroke, configure-selection,
;;; and constrain-movement-of-items.
;; Note that this is similiar to configure-user-interface-statements
;; except that it doesn't need to nreverse the sequence.

(define-category-evaluator-interface (restrict-proprietary-items
				       :access read-write)
    (sequence (named restrict-proprietary-items-and-configure-user-interface-statement) 
  	      1)
  
  ((set-form (statements))
   (with-safe-category-setter-calling
       (with-evaluation-sequence-to-phrase-list-mapping
	   (statements statement-element)
	 (call-category-setter-safely
	   'restrict-proprietary-items-and-configure-user-interface-statement
	   statement-element))))
  ((get-form (statements))
   (with-list-to-evaluation-sequence-mapping (statements statement-element)
     (call-category-getter
       'restrict-proprietary-items-and-configure-user-interface-statement
       statement-element nil nil))))




;;; The category evaluator interface for
;;; `set-up-network-access' configuration.


(define-category-evaluator-interface (set-up-network-access
				       :access read-write)
    (sequence
      (structure set-up-network-access-spec
		 ((restriction-type (member allow
					    prohibit
					    prohibit-absolutely))
		  (access-types (sequence (member execute
						  connect
						  inform
						  read
						  write)
					  1))
		  (access-agent (member any g2 gsi g2-and-gsi g2-and-telewindows
					g2-and-telewindows-and-gsi telewindows-and-gsi))
		  (applicable-items (sequence symbol 1)))
		 (and restriction-type access-types access-agent))
      1)
  
  ((set-form (evaluation-value))
   (with-evaluation-sequence-to-phrase-list-mapping
       (evaluation-value set-up-network-access-info)
     (with-structure (set-up-network-access-info set-up-network-access-spec)
       (let ((internal-restriction-type
	       (external-to-internal-network-restriction-type
		 restriction-type))
	     (access-types-info
	       (with-evaluation-sequence-to-phrase-list-mapping
		   (access-types access-type-element)
		 access-type-element))
	     (applicable-items-info
	       (fix-acceptable-applicable-items-for-object-configuration
		 applicable-items)))
	 (phrase-list access-agent
		      applicable-items-info
		      internal-restriction-type
		      access-types-info)))))
  ((get-form (slot-value))
   (with-list-to-evaluation-sequence-mapping (slot-value set-up-network-access-info)
     (with-new-structure (set-up-network-access-spec)
       (gensym-dstruct-bind ((source-access-agent source-applicable-items
						 source-restriction-type source-access-types)
			    set-up-network-access-info)
	 (setf restriction-type
	       (internal-to-external-network-restriction-type
		 source-restriction-type))
	 (setf access-agent source-access-agent)
	 (setf access-types
	       (with-list-to-evaluation-sequence-mapping
		   (source-access-types source-access-type-element)
		 source-access-type-element))
	 (setf-non-nil applicable-items
		       (make-acceptable-applicable-items-for-object-configuration
			 source-applicable-items)))))))
	







(defmacro convert-properties-plist-to-evaluation-values
    (properties-plist)
  `(allocate-evaluation-structure
     (loop as features-list = ,properties-plist	 
			    then (cddr features-list)
	   while features-list
	   as feature-name = (car features-list)
	   as feature-value = (cadr features-list)
	   collect feature-name using eval-cons
	   collect
	   (if feature-value
	       evaluation-true-value
	       evaluation-false-value)
	     using eval-cons)))



;;; `declare-properties'
;;; The category evaluator interface for
;;; the property declaration configuration.

(defconstant declared-properties-attributes
  '(independent-for-all-compilations stable-for-dependent-compilations stable-hierarchy
    manual-connections optimizable inlineable activatable-subworkspace external-simulation
    subworkspace-connection-posts))

(define-category-evaluator-interface (declare-properties
				       :access read-write)
    (structure
      declare-properties-spec
      ((declared-properties
	 (structure
	   declared-properties-spec
	   ((independent-for-all-compilations truth-value)
	    (stable-for-dependent-compilations truth-value)
	    (stable-hierarchy truth-value)
	    (manual-connections truth-value)
	    (optimizable truth-value)
	    (inlineable truth-value)
	    (activatable-subworkspace truth-value)
	    (external-simulation truth-value)
	    (subworkspace-connection-posts truth-value))
	   (or independent-for-all-compilations
	       stable-for-dependent-compilations
	       stable-hierarchy manual-connections
	       optimizable inlineable
	       activatable-subworkspace
	       external-simulation
	       subworkspace-connection-posts)))
       (applicable-items (sequence symbol 1)))
      (and declared-properties))
  ((set-form (evaluation-value))
   (with-structure (evaluation-value declare-properties-spec)
     (let ((declared-properties-info
	     (loop for (property-name . property-value)		   
		       being each evaluation-structure-pair of declared-properties
		   when (memq property-name declared-properties-attributes)
		     collect property-name
		       using phrase-cons
		     and
		     collect (evaluation-truth-value-is-true-p property-value)
		       using phrase-cons))
	   (applicable-items-info
	     (fix-acceptable-applicable-items-for-object-configuration applicable-items)))
       (phrase-cons applicable-items-info declared-properties-info))))
  ((get-form (slot-value))
   (let ((declared-properties-value
	   (convert-properties-plist-to-evaluation-values (cdr slot-value)))
	 (applicable-items-value
	   (make-acceptable-applicable-items-for-object-configuration (car slot-value))))
     (with-new-structure (declare-properties-spec)
       (setf declared-properties declared-properties-value)
       (unless (null applicable-items-value)
	 (setf applicable-items applicable-items-value))))))





;;; `comment'
;;; The category evaluator interface for user comment configuration

(define-category-evaluator-interface (comment
				       :access read-write)
    (sequence (structure comment-spec
			 ((tag-name symbol)
			  (associated-text text))
			 (and tag-name))
	      1)
  ((set-form (evaluation-value))
   (with-evaluation-sequence-to-phrase-list-mapping (evaluation-value element)
     (with-structure (element comment-spec)
       (phrase-list
	 tag-name
	 (if (evaluation-text-p associated-text)
	     (copy-for-phrase (evaluation-text-value associated-text))
	     'none)))))
  ((get-form (slot-value))
   (with-list-to-evaluation-sequence-mapping (slot-value element)
     (with-new-structure (comment-spec)
       (setf tag-name (car element))
       (setf-non-nil associated-text
		     (if (text-string-p (cadr element))
			 (make-evaluation-text (cadr element))
			 nil))))))







(define-category-evaluator-interface (object-configuration-spec
				       :access read-write)
    (structure object-configuration-spec
	       ((type (member configure-user-interface
			      restrict-proprietary-items
			      set-up-network-access
			      declare-properties
			      comment))
		(clauses (or (named configure-user-interface)
			     (named restrict-proprietary-items)
			     (named set-up-network-access)
			     (named declare-properties)
			     (named comment))))
	       (and type clauses))

  ((set-form (object-configuration-info))
   (with-safe-category-setter-calling
       (with-structure (object-configuration-info object-configuration-spec)
	 (let ((internal-configuration-type-name 
		 (external-to-internal-configuration-type-name type))
	       (category-name
		 (external-object-configuration-type-to-category-name type)))
	   (phrase-cons
	     internal-configuration-type-name
	     (call-category-setter-safely category-name clauses))))))
  ((get-form (object-configuration-info))
   (with-new-structure (object-configuration-spec)
     (let* ((internal-type-name
	      (internal-configuration-type object-configuration-info))
	    (external-type-name
	      (internal-to-external-configuration-type-name internal-type-name))
	    (category-name
	      (external-object-configuration-type-to-category-name 
		external-type-name)))
       (setf type external-type-name)
       (setf clauses
	     (call-category-getter
	       category-name
	       (cdr object-configuration-info)
	       nil nil))))))

;;; `object-configuration'
;;; The top-level category for item configuration

(define-category-evaluator-interface (object-configuration
					 :access read-write)
    (or (no-item)
	(sequence (named object-configuration-spec)
		  1))
  
  ((set-form (evaluation-value))
   (evaluation-etypecase
     evaluation-value
     ((no-item) 'none)
     ((sequence)
      (with-safe-category-setter-calling
	  (phrase-cons
	    '\;
	    (with-evaluation-sequence-to-phrase-list-mapping
		(evaluation-value object-configuration-info)
	      (call-category-setter-safely
		'object-configuration-spec
		object-configuration-info)))))))
  ((get-form (slot-value))
   (cond
     (slot-value
      (nreverse-evaluation-sequence
       (with-list-to-evaluation-sequence-mapping
	   (slot-value object-configuration-info)
	 (call-category-getter
	   'object-configuration-spec
	   object-configuration-info
	   nil nil))))
     (t
      nil))))









	     
;;;; kb-configuration category evaluator interfaces

(define-category-evaluator-interface (main-menu-restrictions-statements
				       :access read-write)
    (sequence
      (structure
	statement-spec
	((restriction-type
	   (named
	     menu-and-attribute-visibility-configurations-restriction-type))
	 (menu-choices
	   (sequence
	     (or (member . #.main-menu-choices)
		 symbol)
	     1)))
	(and restriction-type menu-choices))
      1)
  
  ((set-form (statements))
   (with-safe-category-setter-calling
       (with-evaluation-sequence-to-phrase-list-mapping
	   (statements statement-element)
	 (with-structure (statement-element statement-spec)
	   (phrase-cons
	     'main-menu
	     (phrase-cons
	       restriction-type
	       (call-category-setter-safely
		 'menu-choices menu-choices)))))))
  ((get-form (main-menu-restriction-info))
   (nreverse-evaluation-sequence
     (with-list-to-evaluation-sequence-mapping ((cddr main-menu-restriction-info)
						statement-info)
       (with-new-structure (statement-spec)
	 (setf restriction-type (second statement-info))
	 (setf menu-choices
	       (call-category-getter 'menu-choices
				     (cddr statement-info)
				     nil nil)))))))

(define-category-evaluator-interface (main-menu-restrictions
				       :access read-write)
    (or (no-item)
	(sequence
	  (structure
	    main-menu-restriction-spec
	    ((applicable-user-modes (named applicable-user-modes))
	     (statements (named main-menu-restrictions-statements)))
	    (and applicable-user-modes statements))
	  1))
  
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (evaluation-etypecase
	 evaluation-value
	 ((no-item) 'none)
	 ((sequence)
	  (phrase-cons
	    '\;
	    (with-evaluation-sequence-to-phrase-list-mapping
		(evaluation-value main-menu-restriction-info)
	      (with-structure (main-menu-restriction-info main-menu-restriction-spec)
		(nconc
		  (call-category-setter-safely 'applicable-user-modes
					       applicable-user-modes)
		  (call-category-setter-safely 'main-menu-restrictions-statements
					       statements)))))))))  
  ((get-form (slot-value))
   (cond
     (slot-value
      (nreverse-evaluation-sequence
       (with-list-to-evaluation-sequence-mapping (slot-value main-menu-restriction-info)
	(with-new-structure (main-menu-restriction-spec)
	  (setf applicable-user-modes
		(call-category-getter 'applicable-user-modes
				      main-menu-restriction-info
				      nil nil))
	  (setf statements
		(call-category-getter 'main-menu-restrictions-statements
				      main-menu-restriction-info
				      nil nil))))))
     (t
      nil))))


(define-category-evaluator-interface (global-keyboard-command-restrictions-statements
				       :access read-write)
    (sequence
      (structure statement-spec
		 ((restriction-type
		    (named
		      menu-and-attribute-visibility-configurations-restriction-type))
		  (command-choices
		    (sequence
		      (member . #.global-keyboard-command-choices)
		      1)))
		 (and restriction-type command-choices))
      1)

  ((set-form (statements))
   (with-evaluation-sequence-to-phrase-list-mapping
       (statements statement-element)
     (with-structure (statement-element statement-spec)
       (let ((restriction-type-info
	       (phrase-list 'global-keyboard-command restriction-type)))
	 (nconc
	   restriction-type-info
	   (with-evaluation-sequence-to-phrase-list-mapping
	       (command-choices command-choice-element)
	     command-choice-element))))))
  ((get-form (global-keyboard-command-restriction-info))
   (nreverse-evaluation-sequence
     (with-list-to-evaluation-sequence-mapping
	 ((cddr global-keyboard-command-restriction-info)
	  statement-info)
       (with-new-structure (statement-spec)
	 (setf restriction-type (second statement-info))
	 (setf command-choices
	       (with-list-to-evaluation-sequence-mapping
		   ((cddr statement-info)
		    command-choice-element)
		 command-choice-element)))))))

(define-category-evaluator-interface (global-keyboard-command-restrictions
				       :access read-write)
    (or (no-item)
	(sequence (structure
		    global-keyboard-command-restriction-spec
		    ((applicable-user-modes
		       (named applicable-user-modes))
		     (statements
		       (named global-keyboard-command-restrictions-statements)))
		    (and applicable-user-modes statements))
		  1))
  
  ((set-form (evaluation-value))
   (with-safe-category-setter-calling
       (evaluation-etypecase
	 evaluation-value
	 ((no-item) 'none)
	 ((sequence)
	  (phrase-cons
	    '\;
	    (with-evaluation-sequence-to-phrase-list-mapping
		(evaluation-value global-keyboard-command-restriction-info)
	      (with-structure
		  (global-keyboard-command-restriction-info
		    global-keyboard-command-restriction-spec)
		(nconc
		  (call-category-setter-safely
		    'applicable-user-modes
		    applicable-user-modes)
		  (call-category-setter-safely
		    'global-keyboard-command-restrictions-statements
		    statements)))))))))
  ((get-form (slot-value))
   (cond
     (slot-value
      (nreverse-evaluation-sequence
       (with-list-to-evaluation-sequence-mapping
	   (slot-value global-keyboard-command-restriction-info)
	(with-new-structure (global-keyboard-command-restriction-spec)
	  (setf applicable-user-modes
		(call-category-getter
		  'applicable-user-modes
		  global-keyboard-command-restriction-info
		  nil nil))
	  (setf statements
		(call-category-getter
		  'global-keyboard-command-restrictions-statements
		  global-keyboard-command-restriction-info
		  nil nil))))))      		  
     (t
      nil))))


(define-category-evaluator-interface (psueudo-authorized-optional-modules
				       :access read)
    (sequence symbol 1)
  ((get-form ())
   (with-list-to-evaluation-sequence-mapping
       (authorized-products-of-this-machine element)
     element)))

(define-category-evaluator-interface (simulated-products?
				       :access read-write)
    (or (no-item)
	symbol
	(sequence symbol 1))
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
    ((no-item) 'none)
    (symbol
     (if (eq evaluation-value 'do-not-simulate)
	 t
	 (values bad-phrase
		 (tformat-text-string "Illegal value ~NV" evaluation-value))))
    ((sequence)
     (phrase-cons
       '\,
       (with-evaluation-sequence-to-phrase-list-mapping (evaluation-value element)
	 element)))))
  ((get-form (slot-value))
   (cond
     (slot-value 
      (if (eq slot-value t)
	  'do-not-simulate
	  (with-list-to-evaluation-sequence-mapping (slot-value element)
	    element)))
     (t
      nil))))
    
;; `make-new-alias' is moved here from RUN.

(defun make-new-alias (g2-login)
  (let ((alias (make-user-mode-alias))
        (alias-name (g2-login-user-name? g2-login))
        (alias-parent (g2-login-user-mode g2-login)))
    (setf (alias-name alias) alias-name)
    (setf (parent-user-mode alias) alias-parent)
    (setf (date-of-alias-creation alias)
          (allocate-managed-float (gensym-get-unix-time)))
    (setf (who-created-the-alias alias)
          current-g2-user-mode?)
    ;; TODO: push it atomically.
    (setf (user-mode-aliases kb-configuration)
          (gensym-cons alias (user-mode-aliases kb-configuration)))
    (add-or-delete-mode-name-from-directory-of-names alias-name nil)
    (add-alias-to-configuration 'main-menu-user-restrictions
                                kb-configuration alias-name alias-parent)
    (add-alias-to-configuration 'global-keyboard-command-user-restrictions
                                kb-configuration alias-name alias-parent)
    (loop for item being class-instances of 'item doing
      (add-alias-to-configuration 'object-configuration
                                  item alias-name alias-parent)
      (when (class-definition-p item)
        (add-alias-to-configuration 'instance-configuration
                                    item alias-name alias-parent))))
  t)

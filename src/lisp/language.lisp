;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module LANGUAGE

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David and David D. McDonald


;;; The code for default language and current language was moved here
;;; from MENUS 4/4/97.


;;;; Forward References

(declare-forward-references
  (read-symbol-from-text-string function edit1))





;;;; The Default Language

;;; The _default_ default language used to be influenced by the OK
;;; file.  If the optional modules included JAPANESE or KOREAN, then
;;; the first one that appeared would override the default, which is
;;; ENGLISH.

;;; We are now phasing out Japanese and Korean as optional modules,
;;; since they're now included with G2.  We also never had a way to
;;; make some other language be the default.

;;; Solution: Add a command line argument/Environment variable to G2:
;;;   default-language / G2_DEFAULT_LANGUAGE

;;; This should be a symbol naming a language (if an empty string,
;;; it's taken to be nil/none).  This becomes the _default_ value of
;;; the current-language slot of the language-parameters system table.
;;; That doesn't mean that it will override the value of that slot
;;; saved in all KBs.  It will only be used in either new
;;; language-parameters system tables (e.g., the one you get after a
;;; clear KB), or in language-parameters system tables that have not
;;; had a value other than the default specified previously.
;;;
;;; (MHD 1/23/95)



(def-kb-specific-variable default-language  language
  (:funcall initialize-default-language))

;; Notes:
;;  - must preceed language-parameters def.
;;  - must be a kb-specific variable because japanese-authorized-p or
;;    korean-authorized-p change by loading a KB (i.e., the OK file)

(defun initialize-default-language ()
  (or ; first-asian-language-option-in-ok-object?
	     ; obsolete/removed (MHD 1/23/95)
      (get-g2-default-language-via-environment)
      'english))

;; OBSOLETE: Removed. (MHD 1/23/95)
;;
;; ;; If G2 is authorized for both Korean and Japanese, this chooses
;; JAPANESE.  ;; There should be a way to control whether JAPANESE or
;; KOREAN is chosen as the ;; default default language.  Right now,
;; Japanese wins because it came first -- ;; it's sort of
;; "grandfathered" in.  But that would not be likely to sit well ;;
;; with Koreans.  Consider doing something as simple- minded as
;; choosing KOREAN ;; first in this case where it appeared first in
;; the list of authorized options ;; in the OK object for this
;; machine.  Or, to get fancier, add a slot in the OK ;; object to
;; control this.  (MHD 10/20/92) ;; -------- UPDATE: see doc. for
;; first-asian-language-option-in-ok-object?, in ;; module SEQUENCES1.
;; (MHD 11/13/92)
;;
;; See the following function:




;;; `Get-g2-default-language-via-environment' gets the default default
;;; language G2 is to use from "the environment".  This is currently
;;; defined as searching the following for the first found:
;;;
;;;    default-language -- command line keyword argument -- symbol is
;;;                        "read" as though in the G2 editor
;;;
;;;    G2_DEFAULT_LANGUAGE -- environment variable (or equivalent on
;;;                           non-unix) note that underscores are used
;;;                           as they're more conventional here (hyphens
;;;                           seem to be preferred for command line args)
;;;
;;; In both cases, the string is handled as follows:
;;;
;;;    (1) it is interpreted as a gensym text string -- so non-gensym
;;;    characters are stripped out -- this isn't that great, but it's
;;;    the only way users will have a chance at all of naming their
;;;    languages with non-ASCII names, giving the result so far
;;;
;;;    (2) if the result so far is either nil, or an empty string, the
;;;    answer is nil;
;;;
;;;    (3) otherwise, the result so far is the result of calling
;;;    read-symbol-from-text-string on the result so far, which just
;;;    gives the interpretation that the editor would give to the
;;;    symbol (e.g., case insensitive, handles Gensym characters,
;;;    etc.)
;;;        
;;;
;;; (Later, the rule as to how we arrive at this could be changed.
;;; Perhaps we will want to use the LOCALE environment variable, for
;;; example.  Or we may go back to using the OK file, or an extension
;;; of that concept that serves as a "configuration" KB file giving
;;; various pieces of persistent information that survives KBs clears
;;; and resets as this does.  Perhaps that might also be handled as a
;;; text file.)

(defun get-g2-default-language-via-environment ()
  (let* ((raw-text-string?		; if non-nil, needs reclamation
	   (or (copy-if-text-string	; See Note!
		 (get-command-line-keyword-argument
		   #w"default-language"))
	       (get-gensym-environment-variable
		 #w"G2_DEFAULT_LANGUAGE")))
	 (imported-text-string?
	   (if raw-text-string?
	       (prog1
		   (import-text-string
		     raw-text-string?
		     'DEFAULT-LANGUAGE-SPEC-VIA-ENVIRONMENT)
		 (reclaim-text-string raw-text-string?)))))
    (unless (or (null imported-text-string?)
		(string=w imported-text-string? #w""))
      (read-symbol-from-text-string imported-text-string?))))

;; Note: unfortunately, the two "parallel" functions
;; get-command-line-keyword-argument and
;; get-gensym-environment-variable differ in policy regarding the
;; return of shared vs. unshared string data!  Clean up some day!
;; Similar idiom (copying the one, not the other) was introduced in
;; several places in the sources on this day.  (MHD 12/4/96)







;;;; The Current Language


(def-system-frame language-parameters  language
  (current-language-if-other-than-default?
    nil vector-slot system (type current-language))
  (text-conversion-style
    nil 
    (type text-conversion-style-name?)
    lookup-slot system))



;;; The macro `current-language' returns the first of the following
;;; values that is non-nil:
;;;
;;;    1. (get-language-for-current-workstation-if-any)
;;;    2. (current-language-if-other-than-default? language-parameters)
;;;    3. default-language

(defmacro current-language ()
  `(or (get-language-for-current-workstation-if-any)
       (and language-parameters
	    (current-language-if-other-than-default? language-parameters))
       default-language))



;;; `Get-natural-language-for-editor' returns the best match possible
;;; in G2 for the specified language.  At present, only NIL (=
;;; ENGLISH), JAPANESE, KOREAN, and RUSSIAN have good matches;
;;; everything else just maps into NIL (i.e., English).
;;; 
;;; `Current-natural-language-for-editor' matches (current-language)
;;; using the above function.

(defun current-natural-language-for-editor ()
  (get-natural-language-for-editor (current-language)))

(defun get-natural-language-for-editor (language)
  (case language
    ((japanese korean russian) language)
    (t nil)))



;;; `Get-language-for-current-workstation-if-any' is at present just a
;;; stub.  When implemented it will convey any per-window language
;;; that user has selected to override the default language specified
;;; in the language-parameters system table.
;;;
;;; Note that the per-window language should be able to be changed by
;;; the user from the change-user-settings dialog (the "control-y"
;;; command).  However, that is not yet implemented as of this date.

(defun-simple get-language-for-current-workstation-if-any ()
  (if servicing-workstation? ; <- check should not be needed
                             ;  remove some day!
      (specific-language-for-this-workstation? current-workstation))) 

;; To be done.  (MHD 4/7/94)
  



(def-absent-slot-putter current-language-if-other-than-english?
			(language-parameters value)
  (setf (current-language-if-other-than-default? language-parameters) value))


(define-slot-alias current-language current-language-if-other-than-default?
  language-parameters)



;;; Current-language slot value writer ... 

(def-slot-value-writer current-language
		       (current-language-if-other-than-default?)
  (twrite
    (or current-language-if-other-than-default?
	default-language)))

;; Review capitalization for names of foreign languages!




;;; The Grammar for current-language and language ... Current-language
;;; can be the current language.  Language can be translated --
;;; i.e. it cannot be English, since English cannot be subject to
;;; translation.  Note that the compiler translates current-language
;;; into nil if it is the same as default-language.  The writer for
;;; that category, therefore, writes nil as default-language.
;;; Finally, when initializing?, the slot putter for the
;;; current-language-if- other-than-default? changes
;;; current-language-if-other-than-default? into nil if it is the same
;;; as default-language.

;;; Note that, at present, default-language can only be ENGLISH, JAPANESE,
;;; RUSSIAN, or KOREAN.  But other ones could be added in the future.

(add-grammar-rules
  '((current-language language)
    (current-language 'english)
    (language 'japanese)
    (language 'korean)
    (language 'russian)
    (language unreserved-symbol)))


(def-slot-value-compiler current-language (parse-result)
  (if (eq parse-result default-language)
      nil
      parse-result))



(def-slot-value-reclaimer current-language-if-other-than-default?
    (old-language? language-parameters)
  ;; OK to maintain this, even if not the installed system table; see putter
  ;; below.  (MHD 10/15/91)
  (add-or-delete-as-language-contributor
    language-parameters old-language? t))
  



;;; The slot putter for current-language-if-other-than-default?, when
;;; initializing?, changes language? to nil if it is the same as
;;; default-language.  This is non- standard for a slot putter, but
;;; necessary in the case where a KB was saved out when the the
;;; default language was, say Japanese, and loaded in when the default
;;; language was English, since in that case, we would find ENGLISH as
;;; the value of language?.  Note that default-language is never
;;; expected to change during the the running of any one G2 session,
;;; since it is based on whether this is a Japanese G2 image or not.

(def-slot-putter current-language-if-other-than-default?
		 (language-parameters-instance language? initializing?)
  (if (and initializing? (eq language? default-language))
      (setq language? nil))
  ;; I think these side effects are still ok to leave here despite the
  ;; new constraints on global side effects for system tables.  Even
  ;; if language-parameters-instance is not installed, having its
  ;; current-language value maintained in the main directory should
  ;; still be done, I'm thinking. (MHD 10/15/91)
  (add-or-delete-as-language-contributor
    language-parameters-instance
    (current-language-if-other-than-default? language-parameters-instance)
    t)
  (add-or-delete-as-language-contributor
    language-parameters-instance
    language?
    nil)
  (let ((changed (neq (current-language-if-other-than-default? language-parameters-instance)
		      language?)))
    (setf (current-language-if-other-than-default? language-parameters-instance)
	  language?)
    (when changed
      (decache-dynamic-menus 'language))))

  



;;; The `translation-contributors' KB property of a symbol L is a list
;;; (made up of kb property conses) of frames which introduced L as
;;; the name of a language.  These frames can either be language
;;; translation frames or the language parameters frame.  Each frame
;;; that appears in this list may only appear once.
;;;
;;; This property acts like a reference count in a garbage collection
;;; protocol, and is used to manage the directory of names for the
;;; `grammar category language?'.  If the list becomes empty the
;;; language (symbol) is removed from the directory.

(def-kb-specific-property-name translation-contributors
    reclaim-kb-property-list-function)


;;; `Add-or-delete-as-language-contributor' ... If language? is NIL, JAPANESE,
;;; KOREAN, or ENGLISH, this does nothing.  Note that JAPANESE and KOREAN are
;;; predefined as built-in rewrites for the LANGUAGE? grammar category, and
;;; that ENGLISH is predefined as a built-in rewrite for the LANGUAGE grammar
;;; category.

(defun add-or-delete-as-language-contributor (frame language? delete-case?)
  (unless (memq language? '(english japanese korean nil))
    (let ((translation-contributors (translation-contributors language?)))
      (cond
	(delete-case?
	 (cond
	   ((memq frame translation-contributors)
	    (setf (translation-contributors language?)
		  (delete-kb-property-element
		    frame translation-contributors))
	    (if (null (translation-contributors language?))
		(delete-from-directory-of-names language? 'language)))))
	(t
	 (cond
	   ((not (memq frame translation-contributors))
	    (setf (translation-contributors language?)
		  (kb-property-cons frame translation-contributors))
	    (if (null translation-contributors)	; add the 1st time
		(add-to-directory-of-names language? 'language)))))))))









;;;; Contexts in the New Language Translation facility

;;; The 'new' language translation facility supercedes the G2-internal
;;; facility that has been in place to translate menus. KBs using the
;;; old syntax and assumptions are grandfathered in by using defaults.
;;;
;;; The advantage of the new design is that it associates every
;;; translation with a `context', so that we can avoid mistakes in
;;; languages where, e.g., the English word "table" gets different
;;; translations depending on whether it is what we display to show
;;; the attributes of an object or is the physical thing that goes
;;; with chairs.
;;;
;;; To distinguish these contexts from others, they are referred to as
;;; "localization contexts". We have 'internationalized' various
;;; facilities within G2 by making it possible refer to specific
;;; 'localization' data which specified the current language (above)
;;; and the current context, and from them looking up a translation
;;; for the thing we are presenting if one has been defined
;;;
;;; A localization context consists of two parts.
;;;
;;;   purpose -- One of a relatively small, predetermined, fixed set
;;;              that describe what kind of thing the term is.
;;;              Examples include attribute, error, button label,
;;;              or status message.
;;;
;;;   domain -- The domain anchors the purpose to a particular case:
;;;             the attributes or errors of the User Settings Editor,
;;;             the buttons of the Text Editor or of the Icon Editor,
;;;             and so on.
;;;
;;; Purposes are indicated by symbols. The set of presently defined
;;; purposes is given later in this file in a call to the function
;;; populate-the-fixed-localization-categories. Domains are also
;;; indicated by symbols, but can also be indicated as the name of
;;; any class (which is a symbol). The set of presently defined specific
;;; domains is given below in that same call.
;;;
;;; Translations are only permitted if there is some localization
;;; context if effect at the moment when the call to look for a
;;; contextually appropriate translation is made. In development, a
;;; cerror is signaled if the call isn't within the scope of some
;;; purpose and domain (see just below). In production the check for a
;;; translation will just return nil in that situation.
;;;
;;; This way of internationalizing the texts that G2 produces is not
;;; extendable by an end-user. It requires a developer with access to
;;; the sources. (Which is not to say that we can't develop an API for
;;; this way of using contexts and add it to G2. It could be an
;;; interesting extension to the end-user internationalization
;;; facility that Mark Kramer added to GFR.)


(def-concept localization-context)



#+development
(defvar debug-localization-p nil)

(defmacro debug-localization (format-string &rest format-args)
  (if (eval-feature :development)
      `(when debug-localization-p
	 (format t ,(concatenate 'string "~&~%" format-string "~%")
		 ,@format-args))
      nil))



;;; Localization contexts are established by placing calls to the two
;;; wrappers with-localization-purpose and with-localization-domain at
;;; the appropriate points in G2's code. They thereby establish a
;;; dynamic extent around the calls to the translation lookup
;;; function.  In development, all that is managed and checked by the
;;; dynamic extent `localization-context'.
;;;
;;; The functions that these macros have currently been placed in
;;; are indicated in the comments in the call to populate-the-fixed-
;;; localization-categories. If you extend the internationalization to
;;; new parts of G2 (the various sets of error messages are a nice
;;; candidate) then you must identify the appropriate fixed points
;;; in the calling chains of those facilities and insert calls to
;;; these macros, as well as include a call to the translation lookup
;;; function (see the section on 'Translating a Symbol at Runtime').

(def-dynamic-extent (localization-context
		      (module language))
  (current-localization-purpose? (global-binding nil))
  (current-localization-domains? (global-binding nil)))



;;; Only one purpose can be valid at a time. The binding protocol
;;; that `with-localization-purpose' uses ensures that the first
;;; (earliest) statement of a purpose that is encountered in a
;;; thread of the code will be the one that is used. Any later
;;; instances of this wrapper that are encountered while within
;;; the scope of an earlier instance are ignored.

(defmacro with-localization-purpose (purpose &body body)
  `(with-named-dynamic-extent localization-context
       ((current-localization-purpose? (or current-localization-purpose?
					  ,purpose)))
     ,@body))




;;; Any number of domains can be valid simultaneously. Typically there
;;; will be two, for example an editor that is used to constrain the
;;; translations for its buttons and a class that constrains the
;;; translations of its attributes. However this is designed so that
;;; there is no limit on the number of possible domains.
;;;
;;; Accordingly, `with-localization-domain' has been written so that
;;; the set of domains in force is organized as a list of arbitrary
;;; length. There is a priority among domains of the same type, which
;;; is handled by having earler, wider-scope instances of this wrapper
;;; put their domains earlier in the list, i.e. as each instance of
;;; the wrapper is encountered, it places its domain at the end of the
;;; list, while when the list is used to specify the domain in force
;;; it is searched from the beginning. This entails some special-case
;;; machinery to manage the lists; I considered using the constant-
;;; queue facility, but it supported far more functionality than this
;;; requires. This is just a shallow-binding protocol with ideosyncratic
;;; subroutines to manage the extension and contraction of the list
;;; from its tail rather than its beginning.

(defmacro with-localization-domain (domain &body body)
  `(with-named-dynamic-extent localization-context ()
     (push-item-to-end-of-current-localization-domains ,domain)
     (unwind-protect-for-development with-localization-domain
	 (values (progn ,@body))     	; this can only return 1 value
       (remove-last-item-in-current-localization-domains))))

;; Consider Push-onto-end in new-menus.  It doesn't have these
;; optimizations, on the other hand it's a more general treatment
;; though as of 4/7/97 no one is calling it.

(defun push-item-to-end-of-current-localization-domains (additional-domain)
  (if (null current-localization-domains?)
      ;; optimize the most frequent case
      (setf current-localization-domains?
	    (kb-property-list additional-domain))
      
      (if (consp current-localization-domains?)
	  (if (null (cdr current-localization-domains?))
	      ;; Optimize the addition of the 2d domain.
	      ;; Having two domains will be quite common.
	      (setf (cdr current-localization-domains?)
		    (kb-property-cons additional-domain
				      nil))

	      ;; Is there are reason not to use nconc?
	      (push-item-to-end-of-kb-property-list
		current-localization-domains? additional-domain))

	  #+development
	  (error "Ill-formed current-localization-domains?. ~
                  should be a list but it isn't."))))


;;; `Push-item-to-end-of-kb-property-list' extends a list by consing
;;; onto its final cdr. It is intended to be used when the elements
;;; of the list are added in separate calls and consequently the
;;; collect facility of the Loop macro cannot be used. As the name
;;; implies it uses kb-property conses. (Abstract this?  Are there
;;; cons-pool specific variations on nconc?)
;;;
;;; It is the caller's responsibility to pass in a non-null list. 

;;; This function is only used once in `push-item-to-end-of-current-localization-domains'.

(defun push-item-to-end-of-kb-property-list (list item)
  (loop for tail-of-list on list
	when (null (cdr tail-of-list))
	  do
	    (setf (cdr tail-of-list)
		  (kb-property-cons item nil))
	    (return)))

;; Garish, but does the job. If there is any reason to expect
;; the lists to be long, then modify this and its caller(s)
;; to use a tail-concatenate scheme.


(defun remove-last-item-in-current-localization-domains ()
  (when current-localization-domains?
    (if (null (cdr current-localization-domains?))
	(progn
	  (reclaim-kb-property-cons current-localization-domains?)
	  (setf current-localization-domains? nil))

	(loop with penultimate-cons-cell = nil
	      with cons-cell = nil
	      with remainder = nil
	      for tail on current-localization-domains?
	      do
	  (setq penultimate-cons-cell tail
		cons-cell (cdr tail)
		remainder (cddr tail))
	  (when (null remainder)
	    (reclaim-kb-property-cons cons-cell)
	    (setf (cdr penultimate-cons-cell) nil)
	    (return))))))

;; Even more garish, but wasn't provided for in InterLisp's
;; tconc, so even that treatment would take some thought. 








;;;; Predefined G2-internal Contexts

;;; Not every domain makes sense for every purpose, and the legal
;;; pairs and defaults need to be coordinated. We can't do that in the
;;; parser because our grammar is context-free. Instead it is done in
;;; the slot-compiler for language-translation, and invalid pairs are
;;; rejected as uncompilable.
;;;
;;; The data in this section is what the compiler uses to test the
;;; purpose - domain combinations that are passed to it from the
;;; parser.
;;;
;;; This also serves to docoment in one place the ad-hoc names we have
;;; created to refer our editors, for menus that are not associated
;;; with a frame, and for our defaults. As well as the points in the
;;; rest of G2 where localization context macros referring to these
;;; context elements have been placed.


;;; The call to `populate-the-fixed-localization-categories' is
;;; organized as an association list that pairs the lexical categories
;;; of the localization grammar with the tokens that instantiate
;;; them. After defining the needed grammar rules, it stores the alist
;;; as is on the symbol `known-localizations', which is a defvar because
;;; this is permanent data that never changes. This is consulted
;;; by the slot compiler.

(defvar known-localizations nil)

(defun populate-the-fixed-localization-categories (alist-by-category)
  (loop for (category-symbol terminals) in alist-by-category
	do
    (loop for terminal-symbol in terminals
	  do
      (add-grammar-rules
	`((,category-symbol ',terminal-symbol)))))
  
  (setf known-localizations alist-by-category))



(populate-the-fixed-localization-categories
    '(
      ;#+ignore
      ;; Turned off the 'any' defaults for while so that the expansion
      ;; from just the user-settings-editor to the other two editors
      ;; and the full spectrum of class-specializations could be
      ;; digested and the sites of their wrappers checked out without
      ;; having to worry about this additional complication at the
      ;; same time. (ddm 5/7/97)
      (default-localization-domain
       (; editor  ; not in place yet
	menu     ; is in make-menu-from-description
	table    ; is in twrite-string-that-identifies-attribute
	))
      
      #+ignore   ; none of these are in place
      (named-menu
       (main-menu editor-operations-menu))
      

      (editor
       (text-editor   ; is in enter-editing-context
	icon-editor   ; is in create-icon-editor
	g2-login-dialog
           ;; is in enter-user-settings-editor,
	   ;;  and also in the slot-value-writer for g2-login-comments
	password-change-dialog
	   ;; is in enter-user-setting-editor
	   ;;  and also in the slot-value-writer for g2-login-comments
	))


      (localization-purpose
       (attribute   ; is in twrite-string-that-identifies-attribute
	button-label
	  ;; is in make-subcommand-menu for the user-settings-editor,
	  ;; in translate-subcommand-menu-choice for the text-editor,
	  ;; and in create-icon-editor-button for the icon-editor
	menu-item   ; is in menu-item-string
	simple-message    ; is in the slot-value-writer for g2-login-comments
	simple-condition  ; dito
	))

      ;; For attributes, the `class' case of a domain is in
      ;; make-attributes-table

      ;; The specific case of the class `g2-login' (which isn't a user-
      ;; accessible class) is in enter-user-settings-editor
      
      ;; Class isn't sited yet for menu items.
      
      ))


;;; This function piggybacks on the data above (the fixed-
;;; localization-categories). It has to be kept in sync or else the
;;; use of "the" vs. "a" will be incorrect in descriptions of a
;;; domain.

(defun unique-localization-domain-p (symbol)
  (case symbol
    ((editor menu table) nil)
    ((main-menu editor-operations-menu) t)
    ((text-editor icon-editor g2-login-dialog password-change-dialog) t)
    (otherwise
     ;; we assume all other symbols are names of classes
     nil )))




;;; In addition to defining what symbols are legal purposes and
;;; domains for use by the parser, we have to link the two. The link
;;; is from the purpose to its legal domains. Each purpose must have
;;; this data specified for it to be seen as legal by the slot
;;; compiler. `Define-domains-consistent-with-localization-purpose' is
;;; used to do this. It takes a set of key words that mimic the set of
;;; fields in the `domains-consistent-with-localization-purpose' list
;;; structure that is used to store the information. This structure
;;; is stored on the `domains-consistent-with-localization-purpose'
;;; global property of the symbol that names the purpose.
;;;
;;; `Known-localization-domains-for-purpose' handles the case of
;;; where the domains for a purpose are a fixed set. It looks up
;;; the lexical category that lists those domains as its fixed set
;;; of legal tokens in the grammar and returns the already existing
;;; list.


(def-global-property-name domains-consistent-with-localization-purpose)


(def-list-structure (domains-consistent-with-localization-purpose
		      (:constructor define-consistent-localization-domains)
		      (:consing-function cons))  ; These are permanent
    
    (default-localization-domain
     ;; The value of this field is one of the tokens (symbols) of
     ;; the default-localization-domain category as given above.
     ;; When the translation statement does not include a domain
     ;; this is the one that is supplied.

     localization-domain-includes-classes-p
     ;; Either T or Nil.

     category-of-localization-domain
     ;; Corresponds to the `fixed-domain' argument. This is either
     ;; no-fixed-localization-domains if there can be any number of
     ;; possible domains since the purpose applies to any item, or one
     ;; of the lexical categories of the localization grammar. There
     ;; hasn't yet been a case where both have applied.
     ))


(defun define-domains-consistent-with-localization-purpose
       (purpose &key default accepts-classes? fixed-domain)
  (let ((struct
	  (define-consistent-localization-domains
	      default accepts-classes? fixed-domain)))
    (setf (domains-consistent-with-localization-purpose purpose)
	  struct)))

;; This should check that the symbols it is given are actually
;; defined, if only to catch spelling errors.


(defun known-localization-domains-for-purpose (symbol-naming-purpose)
  (let* ((consistency-data
	   (domains-consistent-with-localization-purpose
	     symbol-naming-purpose))
	 (category? (category-of-localization-domain consistency-data)))
    
    (when category?
      (if (eq category? 'no-fixed-localization-domains)
	  'no-fixed-localization-domains
	  (second (assq category? known-localizations))))))

;; This doesn't check that the purpose exists before it operates.
;; The slot-compiler doesn't call it until it has established
;; that the purpose is defined. 



;;; We need a predicate to test whether a symbol names a localization
;;; purpose -- if only to check for spelling errors. The definitive
;;; operational definition of a localization purpose is being
;;; defined as such in the grammar, which is accessible from the
;;; fixed data.

(defun known-localization-purpose-p (symbol)
  (let ((purposes
	  (second (assq 'localization-purpose known-localizations))))
    (memq symbol purposes)))





(define-domains-consistent-with-localization-purpose 'button-label
    :default 'editor
    :accepts-classes? nil
    :fixed-domain 'editor)

(define-domains-consistent-with-localization-purpose 'attribute
    :default 'table
    :accepts-classes? t
    :fixed-domain 'no-fixed-localization-domains)

(define-domains-consistent-with-localization-purpose 'menu-item
    :default 'menu
    :accepts-classes? t
    :fixed-domain 'named-menu)

(define-domains-consistent-with-localization-purpose 'simple-message
    :default 'editor         ; Could be any. Extension required!
    :accepts-classes? t
    :fixed-domain 'editor)   ; ditto!

(define-domains-consistent-with-localization-purpose 'simple-condition
    :default 'editor         ; ditto. Editor is sufficient when all that's
    :accepts-classes? t      ; involved is the user-settings-editor,
    :fixed-domain 'editor)   ; but these two (simple-*) are general notions
                             ; that need considerable reconsideration later








;;;; The Language Translation Class

;;; At this stage in the design of the G2-internal internationalization
;;; facility, we are using KBs to define and save all the localization
;;; information. If only to facilitate grandfathering the old-style
;;; menu translations, we use their `language-translation' class as
;;; the basis of the internationalization.
;;;
;;; A (new) language-translation statement specifies a language, a
;;; context, and any number of term - translation pairs, where the
;;; term is given as a symbol and the translation is given as either
;;; a symbol or a string. All of this information, as derived from
;;; the parser and checked for validity by the slot compiler, is
;;; stored in the box-translation-and-text field of the language-
;;; translation frame.
;;;
;;; When the frame is brought online (i.e. when it is first defined
;;; or when it is loaded from a stored KB), the terms inside the
;;; statement are pulled out and the frame is associated with them
;;; as a property (or the frame is added to an already existing property
;;; value that was created by some earlier frame that mentioned
;;; the term). The runtime search for a language and context appropriate
;;; translation of the term is organized off this property. It
;;; examines each of the frames in turn until one is found or the
;;; list exhausted. 

(def-class (language-translation
	     statement (foundation-class language-translation)
	     define-predicate)
  
  (frame-author-or-authors
    nil (type authors-with-time-of-last-edit?)
    (attribute-export-comment
      "Will allow 0 or more author entries. each author entry may have ~
       a date. authors: ([ name: symbol, date: gensym-time ] * ), ~
       editor-grammar: struct, defining-class: item, writable: true"))
  
  (frame-change-log nil (type frame-change-log))
  
  (box-translation-and-text nil (type language-translation text)
			    select-changes))



;;; The value field of a language-translation's box-translation-and-text
;;; slot (its car) has to hold all of the data that is supplied in the
;;; statement, i.e. the language, purpose, domain, and however many pairs
;;; of terms (symbols) and their translations as the user happened to
;;; include in that statement.
;;;
;;; The original design encoded that information in a relatively flat
;;; list, i.e. ( language purpose domain . term-translation-pairs ).
;;;
;;; However, that structure isn't compatible with the encoding that's
;;; used in the 'old' language translation frames that were used just
;;; for menu items, which leads to fatal errors when a KB with the
;;; flat encoding is loaded into a G2 that was built earlier than
;;; the point when this new design for internationalization was
;;; committed. The old encoding was
;;;
;;;     ( language . term-translation-pairs )
;;;
;;; To compensate, we adopted a new encoding (somewhat under duress,
;;; as the flat encoding seems easier to appreciate for what it is
;;; when someone does a describe on one of these frames and sees the
;;; unabstracted data structure), where the purpose and domain are
;;; pushed onto the term-translation alist as the first pair.
;;; This is evident in the list-structure that is used to abstract
;;; this layout, `language-translation-data'. Note that all of the
;;; rest of the code uses the accessors provided by the list structure,
;;; so it can be modified without having to make any other changes. 

(def-list-structure (language-translation-data
		      (:constructor make-language-translation-data)
		      (:consing-function phrase-cons))

    ( localization-data-language
       .  (  ( localization-data-purpose
		. localization-data-domain )
	     . localization-data-term-translation-pairs ))
  )



;;; Accessors that make reference to the frame.

(defun data-of-language-translation (frame)
  (car (box-translation-and-text frame)))

(defun language-of-language-translation (frame)
  (localization-data-language (car (box-translation-and-text frame))))

(defun purpose-of-language-translation (frame)
  (localization-data-purpose (car (box-translation-and-text frame))))

(defun domain-of-language-translation (frame)
  (localization-data-domain (car (box-translation-and-text frame))))


(defun term-translation-pairs (frame)
  (localization-data-term-translation-pairs
    (car (box-translation-and-text frame))))




;;; The existence of a language-translation frame has two side-effects.
;;;
;;;   1. The language that the frame refers to is present in the
;;;      directory for the grammar category `language?'.
;;;
;;;   2. The symbols (terms) for which the frame provides a translation
;;;      in a particular context include the frame on their property
;;;      `translations-for-symbol'.
;;;
;;; When the frame goes out of existence (its `cleanup' is run)
;;; these side-effects are reaped. (Though there may be other references
;;; to the language from other frames.)
;;;
;;; Its `put-box-translation-and-text-slot-value' method puts the
;;; side-effects into place when the frame is initially created or when
;;; it is loaded in by a KB. There is a special case for KBs that
;;; use the old-style of translation that applies to menu items.
;;;
;;; When the frame is modified (edited) it checks against the old
;;; values of the frame's data to see whether some of the corresponding
;;; side-effects should be removed.
;;;
;;; The `initialize-after-reading' method has nothing to do since
;;; all the relevant frame notes are managed by side-effects of the
;;; calls made by the slot-putter. It is included for completeness.


(def-class-method cleanup (language-translation)
  (funcall-superior-method language-translation)
  (let* ((frame language-translation)   ; renamed for clarity
	 (data (car (box-translation-and-text frame))))
    (when (not (or (null data) (eq data no-value)))
      
      (add-or-delete-as-language-contributor
	frame (localization-data-language data) t) ; "t" means delete.
      
      (loop with terms-removed = nil
	    for (symbol . translation-string)
		in (localization-data-term-translation-pairs data)
	    unless (memq symbol terms-removed)
	      do
		(remove-translation-statement-from-term symbol frame)
		(gensym-push symbol terms-removed)
	    finally (reclaim-gensym-list terms-removed)))))

;; The call below was in the original cleanup method. What is its purpose
;; given that this frame is about to be deleted ?  Leaving it in causes a
;; bug since it's operating on a deleted frame.  (change-slot-value
;; language-translation 'box-translation-and-text nil)



(def-class-method initialize-after-reading (language-translation)
  (funcall-superior-method language-translation))


(def-class-method put-box-translation-and-text-slot-value
    (language-translation box-translation-and-text initializing?)
  
  (let* ((frame language-translation)
	 (value-field (car box-translation-and-text))
	 (value?
	   (if (not (or (null value-field) (eq value-field no-value)))
	       value-field))
	 (prior-value-field (car (box-translation-and-text frame)))
	 (prior-value?
	   (if (and prior-value-field
		    (not (or (null prior-value-field)
			     (eq prior-value-field no-value))))
	       prior-value-field)))

    (unless initializing?
      (update-frame-status frame nil nil))

    (setf (box-translation-and-text frame) box-translation-and-text)

    (when value?
      (cond
	#+development  ; see note with predicate
	((flat-encoded-language-translation-p value?)
	 (setq box-translation-and-text
	       (process-flat-encoded-language-translation-slot-value
	       value? frame (cdr box-translation-and-text)))
	 (setf (box-translation-and-text frame) box-translation-and-text))

	((old-style-language-translation-p value?)
	 (process-old-style-menu-translation-slot-value
	   value? frame initializing?))
	
	(t (process-new-style-translation-slot-value
	     value? prior-value? frame))))
    
    (values box-translation-and-text nil)))


(defun process-new-style-translation-slot-value (value prior-value? frame)
  (let ((language (localization-data-language value))
	(prior-language (if prior-value?
			    (localization-data-language prior-value?)))
	(term-translation-pairs
	  (localization-data-term-translation-pairs value))
	(prior-term-translation-pairs
	  (if prior-value?
	      (localization-data-term-translation-pairs prior-value?))))

    (if prior-value?
	(progn
	  (unless (eq language prior-language)
	    (add-or-delete-as-language-contributor frame prior-language t))

	  ;; remove the ones that were in the old and aren't in the new
	  (loop for (symbol . translation-string)
		    in prior-term-translation-pairs
		unless (assq symbol term-translation-pairs)
		  do
		    (remove-translation-statement-from-term symbol frame))

	  ;; add ones that are in the new and not in the old
	  (loop for (symbol . translation-string)
		    in term-translation-pairs
		unless (assq symbol prior-term-translation-pairs)
		  do
		    (add-translation-statement-to-term symbol frame)
		when (assq symbol prior-term-translation-pairs)
		  do
		    ;; we'll miss the case of an update to the statement
		    ;; adding a duplication unless we explicitly check.
		    (check-for-duplicate-instances-in-language-translation
		      symbol frame)))

	(extend-localization-data language term-translation-pairs frame))))


(defun extend-localization-data (language term-translation-pairs frame)
  (loop for (symbol . translation-string) in term-translation-pairs
	do
    (add-translation-statement-to-term symbol frame))
  (add-or-delete-as-language-contributor frame language nil))




;;; An 'old style' language translation does not have context data.
;;; The cdr of the value of its box-translation-and-text is its set
;;; of ( symbol-for-menu-choice . translating-symbol-or-string ) pairs.
;;; We've made the new values conform to this encoding by adding
;;; the context data as an additional pair ( symbol-for-purpose .
;;; symbol-for-domain ) at the beginning of the alist.  In order to
;;; distinguish new ones from old, we examine the symbol in the car
;;; of the first pair (which corresponds to a position for which
;;; we have an accessor) and see if it is the name of purpose.
;;;
;;; This stands a chance of accidentally interpreting an old frame
;;; as a new one should it happen that there is a menu choice with
;;; the same name as a purpose and the very first pair of some
;;; old frame provides a translation for it. This is a pretty low
;;; probability event, but if it seems possible, we can augment this
;;; test with a check against the value of the symbol (should it be
;;; one and not a string) in the domain's position. Note that even
;;; this test could fail, since some purposes can take class names
;;; as their domains, and since the list of these is not fixed, we
;;; can't make a gold-standard (platinum?) test.

(defun old-style-language-translation-p (value)
  (let ((possible-localization-purpose
	  (localization-data-purpose value)))
    (not (known-localization-purpose-p possible-localization-purpose))))


(defun process-old-style-menu-translation-slot-value
       (value frame initializing?)
  #+development
  (unless initializing?
    (error "Unexpected situation. An 'old-style' menu translation frame ~
            has been passed in but we are not initializing a KB."))
  (when initializing?
    (let* ((language (car value))
	   (term-translation-pairs (cdr value)))

      ;; Add a new 'pair' to provide the context data.
      ;; We have to do this by hand (rather than via a call to
      ;; make-language-translation-data) because it uses phrase-conses.
      (setf (cdr value)
	    (slot-value-cons (slot-value-cons 'menu-item  ; purpose
					      'menu)      ; domain
			     (cdr value)))

      (extend-localization-data language term-translation-pairs frame)
      
      value )))
      


;;; Catch-22. With the change over to an encoding that mimics the
;;; old style, we effectively stranded several valuable KBs that were
;;; defined under the 'flat', encoding originally used for the new
;;; style.  These two functions detect that style and convert it.

#+development
(defun flat-encoded-language-translation-p (value)
  (when (consp value)
    (symbolp (second value))))

#+development
(defun process-flat-encoded-language-translation-slot-value (value frame text)
  (let ((language (first value))
	(purpose (second value))
	(domain (third value))
	(term-translation-pairs (fourth value)))

    (let ((revised-value
	    (slot-value-cons
	      language
	      (slot-value-cons (slot-value-cons purpose
						domain)
			       term-translation-pairs))))

      (extend-localization-data language term-translation-pairs frame)

      (let ((revised-slot-value
	      (slot-value-cons revised-value text)))

	;; Pass the value back so it can be returned as the value
	;; of the putter.
	revised-slot-value ))))






(def-slot-value-writer language-translation (language-translation)
  #+development
  (cerror "continue" "This should never be called. Language-translation ~
          is a text slot. See mhd or ddm.")
  (let* ((frame language-translation)
	 (language (language-of-language-translation frame))
	 (term-translation-pairs (term-translation-pairs frame)))
    (twrite-string "in ")
    (twrite-symbol language)
    (twrite-string " : ")
    (loop for ((term . translation) . more?) on term-translation-pairs
	  do
      (tformat "~%  ")
      (twrite-symbol term)
      (twrite-string " = ")
      (tformat "~s" translation)
      (when more? (tformat "~s" '\,)))))







;;;; Registering Message strings and Buttons 

;;; ... The name is added to the grammar as an instance of the
;;; category message, which has the effect of including it among
;;; the prompts the user will see when typing in terms to be
;;; translated.

(defmacro define-simple-message (name string)
  (let ((message-name (intern (format nil "~a-MESSAGE" (symbol-name name)))))
    `(progn       
       (add-grammar-rules '((simple-message ',name)))
       (defun ,message-name ()
	 (let ((translation? (translation-for-symbol? ',name)))
	   (or translation?
	       ,string))))))

;; The one place this is used is for "Please modify user settings."
;; in the slot-writer for g2-login.

;; Extend to take arguments, making the control string smart about
;; localization issues (at which point it's no longer a 'simple'
;; message). Consider abstracting this into a generator that can
;; include localization specifications for purpose and applicable
;; domains, probably varying the extension to the function name
;; accordingly. Applies to error messages from the OK file parser.

;; Is there any reason not to abstract the body of this into a
;; function call to save space?



(defun register-symbol-as-simple-condition (symbol)
  (add-grammar-rules `((simple-condition ',symbol))))

;; The one place where it's presently used is in controls just after
;; the function log-in-workstation, where it notes all of the symbols
;; used in that code to represent reasons why the user can't be logged
;; in. The purpose is to record those symbols as instances of
;; localizable terms so they will appear as prompts in the
;; editor. 


(defun register-button-label-for-internationalization (symbol)
  (add-grammar-rules `((button-label ',symbol))))

(defun register-button-labels-for-internationalization (list-of-symbols)
  (loop for symbol in list-of-symbols
	do
    (register-button-label-for-internationalization symbol)))

;; The one place this is used is after make-user-settings-editor-state
;; in run.





;;;; Associating Translations with Symbols

;;; `Translations-for-symbol' is the property on which the language-
;;; translation frames that refer to a given term (symbol) are
;;; stored for use at runtime. The frames are stored in a simple
;;; list constructed using kb-property conses.
;;;
;;; The original internationalization scheme that was used for menus
;;; organized the value of the equivalent property as an alist by
;;; language. Since in this scheme we have three levels of dispatch
;;; rather than just one (language, purpose, domain), it seems to be
;;; undue overhead to maintain any structure on the property since
;;; we're very likely to have to search several frames before one
;;; matches in all three components. It's simpler to have a uniform
;;; search mechanism by frame rather than try to optimize when all of
;;; the data has to be kept on the frame regardless. In a design where
;;; we weren't using frames/KBs as the medium, we could optimize
;;; the search.

(def-kb-specific-property-name translations-for-symbol
    reclaim-translations-for-symbol)

(defun reclaim-translations-for-symbol (translations-for-symbol)
  (reclaim-kb-property-list translations-for-symbol))




(defun add-translation-statement-to-term (symbol frame)
  (let ((entry (translations-for-symbol symbol)))
    (cond
      ((null entry)
       (setf (translations-for-symbol symbol)
	     (kb-property-list frame)))
      
      ((memq frame entry)
       ;; If the frame is already present this might be a duplicate
       ;; instance within its term-translation-pairs.
       (check-for-duplicate-instances-in-language-translation
	 symbol frame)

       ;; For that matter, it might be a duplication of a symbol
       ;; that's in another frame as well.
       (check-for-other-language-translations symbol frame))

      (t
       ;; This frame is new to the entry, but there could be
       ;; other language-translation frames already on the
       ;; entry that could have a value for this symbol in
       ;; the same context, in which case we have a different
       ;; sort of duplication. 
       (check-for-other-language-translations symbol frame)

       ;; We include this frame even if it is a duplicate, since
       ;; we can't predict which frame the user will choose to
       ;; remove. 
       (setf (translations-for-symbol symbol)
	     (kb-property-cons frame entry))))))


(defun remove-translation-statement-from-term (symbol frame)
  (unless releasing-kb?
    (let ((entry (translations-for-symbol symbol)))
      (cond
	((null entry)
	 #+development
	 (cerror "continue" "Call made to remove frame from the translations-~
                  for-symbol of ~a, but there is no entry" symbol)
	 nil)
	
	((memq frame entry)
	 ;; Check whether we were (one of) the frames that duplicated
	 ;; the translation for this symbol, and if so, clean up the
	 ;; note.
	 (check-for-other-language-translations symbol frame t)
	 (setf (translations-for-symbol symbol)
	       (delete-kb-property-element frame entry)))
	
	(t #+development
	   (cerror "continue" "Call made to remove frame from the ~
                    translations-for-symbol of ~a, but it isn't there."
		   symbol)
	   nil)))))





;;; At various points throughout the code, notably in log-in-
;;; workstation and its friends, symbols are used directly as the
;;; source of the wording to be used in a message to the user. It
;;; would be nice if that changed, but in the meantime, an
;;; `english-localization' lets you associate a string with the symbol
;;; to use by default if no translation has been provided for it in
;;; the current language.
;;;
;;; This also lets you provide a different or more expansive text when
;;; the current language is English, since in that case the actual
;;; value of current language internally may actually be nil and the
;;; other facilities in this module will not apply.
;;;
;;; To use this facility, you populate the facility with
;;; `define-internationalized-symbol' which takes either a cons of a symbol
;;; and a wide-string (its English localization) or just a symbol. You
;;; access the facility with `string-for-localized-symbol'.  That routine
;;; can be used safely with any symbol since if no translation or English
;;; localization is available it defaults to copy-symbol-name.


(def-global-property-name english-localization)


(defun-simple define-internationalized-symbol (symbol-or-cons)
  (let ((symbol (if (symbolp symbol-or-cons)
		    symbol-or-cons (car symbol-or-cons)))
	(English-text (when (consp symbol-or-cons)
			(cdr symbol-or-cons))))
    
    ;; make it visible to G2's internationalization expressions.
    (register-symbol-as-simple-condition symbol)
    
    ;; If a clean rendering of the symbol was provided, remember it.
    (setf (English-localization symbol) English-text)))




;;; `Twrite-localized-symbol' handles the mechanics of accessing the
;;; readable default English string that may have been associated with
;;; the symbol if no translation has been defined for it. It is up to
;;; the caller to impose the appropriate localization domain and purpose
;;; to govern the choice of translation. If this call is not wrapped
;;; in localization wrappers then in production translation-for-symbol?
;;; will return nil and in development you'll get a cerror complaining
;;; that they are absent.  Note that it is also the caller's responsibility
;;; to reclaim the string that this produces.

(defun-simple string-for-localized-symbol (symbol)
  (let* ((translation? (translation-for-symbol? symbol))
	 (english? (english-localization symbol)))
    (or (when translation? (copy-text-string translation?))
	(when english? (copy-text-string english?))
	(copy-symbol-name symbol :first t))))







;;;; Translating a Symbol at Runtime

;;; To internationalize a given facility in G2` you need to augment
;;; its code. Where you now have code that derives a string from a
;;; symbol you need to add a call to `translation-for-symbol?'. As its
;;; name suggests, this function takes a symbol as its sole argument
;;; and then looks in the available localization data for a string
;;; that is a translation of that symbol in the current language and
;;; localization context. Note that if the current language is English
;;; this function returns nil, since we don't think of our base case
;;; as a 'translation'. Consequently, the usual idiom is:
;;;
;;;    ... (or (translation-for-symbol? 'my-symbol)
;;;            (copy-symbol-name 'my-symbol))  ; or the equivalent
;;;
;;; The original string as stored in the localization data is
;;; returned, so it is the caller's responsibility to make a copy of
;;; it as needed.

;;; The following is an exhaustive (as of 4/11/97) list of functions
;;; that use translation-for-symbol?.
;;;
;;;    translated-string-for-symbol  -- for menu items
;;;    make-subcommand-menu          -- for button-labels
;;;    twrite-string-that-identifies-attribute  -- for attributes
    

(def-concept internationalization)
(def-concept translation)



;;; `Translation-for-symbol?' Is the entry point used elsewhere in the
;;; code as the way to get a symbol's translation. It returns the
;;; string to be used for the symbol given the current localization
;;; context and language.  Since there are no translations for English
;;; (it's the default), this returns Nil when English is the
;;; current-language. Nil is also returned if there is no entry for
;;; this symbol in the current language or in the current context.
;;;
;;; The current language will typically be the language specified for
;;; the G2 or the window, but there is a provision for the language
;;; used by the text editor to be different from those. This is handled
;;; by the optional overriding-language? parameter.

(defun translation-for-symbol? (symbol &optional overriding-language?)
  (let ((current-language (or overriding-language?
			      (current-language))))
    (if (not (eq current-language 'english))
	(contextually-appropriate-translation-of-symbol?
	  symbol current-language))))


;;; `Translation-in-context' is for testing the contents of the
;;; translation pool by stipulating the context rather than
;;; running the actual code. All the arguments are symbols.
#+development
(defun translation-in-context (symbol language purpose list-of-domains)
  (let ((current-localization-purpose? purpose)
	(current-localization-domains? list-of-domains))
    (contextually-appropriate-translation-of-symbol? symbol language)))



;;; `Contextually-appropriate-translation-of-symbol?' does all the
;;; data checking needed to establish that we are in a dynamic context
;;; that supports internationaliation. Since that capacity depends on
;;; the placement of wrappers at strategic common paths in the code,
;;; this is a real possiblity when new components of G2 are being
;;; worked up for internationalization during development.

(defun contextually-appropriate-translation-of-symbol? (symbol language)
  (with-named-dynamic-extent localization-context ()
    (let ((localization-entry? (translations-for-symbol symbol)))
      (when localization-entry?
	(let ((purpose current-localization-purpose?)
	      (domains current-localization-domains?))

	  (cond
	    ((and (null purpose) (null domains))
	     #+development  ; redundant with named-dynamic-extent ??
	     (cerror "continue with no translation"
		     "A translation is being sought for ~
                      the symbol ~a, but we are not currently in ~
                      the scope of a localization domain or a ~
                      localization purpose" symbol)
	     nil)
	    ((null domains)
	     #+development
	     (cerror "continue with no translation"
		     "A translation is being sought for ~
                      the symbol ~a, but we are not currently in ~
                      the scope of a localization domain" symbol)
	     nil)
	    ((null purpose)
	     #+development
	     (cerror "continue with no translation"
		     "A translation is being sought for ~
                     the symbol ~a, but we are not currently in ~
                     the scope of a localization purpose" symbol)
	     nil)
	    (t
	     (find-translation-for-symbol-in-contextually-appropriate-frame
	       symbol localization-entry? language purpose domains))))))))



;;; `Find-translation-for-symbol-in-contextually-appropriate-frame' lets
;;; us abstract out the search algorithm.

(defun find-translation-for-symbol-in-contextually-appropriate-frame
       (symbol frames language purpose domains)
  (debug-localization "Attempting to translate ~a into ~a.~%  The context is~
                       ~%    purpose = ~a~%    domains = ~a"
		      symbol language purpose domains)
  (let ((frame-to-use?
	  (search-language-translation-frames
	    frames language purpose domains)))
    (when frame-to-use?
      (extract-translation-from-language-translation-frame
	symbol frame-to-use?))))



;;; `Search-language-translation-frames' does all the heavy
;;; lifting. The current algorithm is optimized for ease of
;;; maintaining a consistent body of language-translation frames and
;;; their data, -not- for runtime efficiency. (If we wanted
;;; efficiency, we'd compile the whole search down to a network so we
;;; wouldn't have to keep asking the same questions over and over.)
;;; When the domains involved are classes, it goes through the
;;; whole set of frames (most of which will likely be for a different
;;; language -- an example of a redundant question) and keep track
;;; of which candidate class is the most specific.

(defun search-language-translation-frames (frames language purpose domains)
  (loop with best-so-far? = nil
	for frame in frames
	do
    (when (frame-matches-localization-context-p
	    frame language purpose domains)

      ;; If the frame's purpose takes (only) class names as it's domain,
      ;; we need to check for subsumption and test all the frames.
      ;; If it takes specific symbols (the alternative) then there's
      ;; no possiblity for more than one match so we bail out on
      ;; the first one.
      (if (eq purpose 'attribute) ; cheats. Revise when default implemented for attributes
	  (if best-so-far?
	      ;; Is the current candate frame more specific than the
	      ;; current best, i.e. is it a subclass of it. This is a
	      ;; predicate over class-descriptions, so we're comparing
	      ;; the class-description that's stored as the domain
	      ;; of the (possibly more specific) candidate frame
	      ;; against that same object in the currently best frame.
	      (when (subclassp (domain-of-language-translation frame)
			       (domain-of-language-translation best-so-far?))
		(setq best-so-far? frame))

	      (setq best-so-far? frame))

	  ;; specific symbol case.
	  (return frame)))
    
	finally
	  (return best-so-far?)))


#+obsolete
;; Original inner loop that took the first frame that satisfied the context.
;; It is inadequate unless the frames are sorted from most to least
;; specific, which is a problematic thing to do only if we want to take
;; into account the possibility that the class hierarchy will change
;; during the lifetime of the use of the translation search process.
;; Otherwise it's just a one bubble operation each time a language-translation
;; frame is compiled.
(loop for frame in frames
      when (frame-matches-localization-context-p
	     frame language purpose domains)
	do (return
	     (extract-translation-from-language-translation-frame
	       symbol frame)))


;;; `Frame-matches-localization-context-p' determines whether a specific
;;; language-translation frame is consistent with the current localization
;;; context. The only interesting part is how domains are checked.

(defun frame-matches-localization-context-p (frame language purpose domains)
  (let ((data (car (box-translation-and-text frame))))
    (when (eq (localization-data-language data) language)
      (when (eq (localization-data-purpose data) purpose)
	(when (one-of-the-localization-domains-subsumes-domain-p
		domains (localization-data-domain data) purpose)
	  t )))))



;;; In `one-of-the-localization-domains-subsumes-domain-p' the
;;; list-of-domains is a list of symbols and frames representing the
;;; contexts in force at the time the translation is done. The domain
;;; is the domain specified in the language-translation frame that is
;;; being considered by frame-matches-localization-context-p. The
;;; domain is always a symbol, but it may be interpreted as the name
;;; of a class in the situation where the localization purpose is as
;;; an attribute of frame. In the case of the context being a frame
;;; and the domain of the translation under test being a class we
;;; ought to be testing for subsumption: is the class of the frame
;;; that defines the current context at the same level or higher in
;;; the current class hierarchy than class of the
;;; language-translation. As it stands, we're testing
;;; inheritance-class-memq (because that's easy and I don't yet know
;;; how to do the real test in any simple way) and hoping that the
;;; difference will sort itself out in the lessp check done by
;;; search-language-translation-frames.


(defun one-of-the-localization-domains-subsumes-domain-p
       (list-of-domains domain purpose)
  
  (loop for possible-governing-domain in list-of-domains
	when
	  (typecase possible-governing-domain
	    (symbol
	     ;; This case is for editors, named menus, and generics.
	     ;; An example is user-settings-editor
	     (eq domain possible-governing-domain))
	    
	    (otherwise	     
	     #+development
	     (unless (framep possible-governing-domain)
	       (cerror "continue as in production"
		       "Unanticipated type of object passed in as ~
                        a domain:~%~A~%It must be a frame in this case!"
		       domain))
	     
	     (when (eq purpose 'attribute)   ; note A.
	       ;; Is the class of this frame-based domain included in
	       ;; the inheritance path of the current localization domain?
	       (when (classp domain)
		 (frame-of-class-p possible-governing-domain domain)))))
	  do (return t)
	finally
	  (return nil)))

;; Note A. Strictly speaking, the purpose can be any symbol that
;; has the property localization-domain-includes-classes-p (see the
;; usage in the slot compiler for localization contexts).  At the
;; present time (5/9/97) the only one of these is attribute.




(defun extract-translation-from-language-translation-frame (symbol frame)
  (let ((term-translation-pairs (term-translation-pairs frame)))
    (cdr (assq symbol term-translation-pairs))))







;;;; The Toplevel Grammar Rule for Language-Translation

(add-grammar-rules
  '((language-translation
     ('in language '\, localizing-context '\: term-translation-pairs)
     (2 4 6))))


;;; the 'old' toplevel rule. Note that the only terms that can
;;; be translated using this production are menu-items.

(add-grammar-rules
  '((language-translation
     ('in language '\: menu-item-translation-pairs)
     (2 . 4))))



;;; The grammar rules for localization contexts. Note that the grammar
;;; of its lexical non-terminals (localization-purpose, named-menu,
;;; editor, and default-localization-domain) is created by special forms
;;; (above) since their legal values are fixed and have to be coordinated.

(add-grammar-rules
  '(
    ;; e.g. "an attribute of a g2-login"
    (localizing-context
     ('as a-or-an localization-purpose 'of a-or-an class)
     (3 . 6))

    ;; e.g. "an attribute" or "a menu" implying that no specific
    ;; domain is intended and we should supply the default.
    (localizing-context
     ('as a-or-an localization-purpose)
     (3))
    
    ;; e.g. "a menu-choice in the main-menu"
    ;; These are symbols we define to correspond to the various
    ;; sorts of menu we have that aren't associated with the spot
    ;; being over a specific frame. All predefined.
    (localizing-context
     ('as a-or-an localization-purpose 'in 'the named-menu)
     (3 . 6))

    ;; e.g. "a button-label in the user-settings-editor"
    ;; These are symbols we define to correspond to the various
    ;; sorts of editors we have. All predefined.
    (localizing-context
     ('as a-or-an localization-purpose 'in 'the editor)
     (3 . 6))

    ;; e.g. "... any editor", "...any menu"  These are defacto
    ;; superclasses of the context creators (editors, general menus)
    ;; that aren't in the class system. We predefine all the legal
    ;; possibilities
;    (localizing-context
;     ('as a-or-an localization-purpose 'of 'any default-localization-domain)
;     (3 . 6))
;; pulling this case temporarily to simplify the installation of the icon
;; and text editors
    ))





;;; The `slot compiler for language-translation' has to distinguish
;;; between the grandfathered menu translations, which do not have
;;; context data, and the new translations which do. Grandfathered
;;; translations have a default context created for them here. It also
;;; has the context data checked against the set of legal purpose -
;;; domain pairs, and against the set of default ('any') domains. If
;;; the semantic checks fail, it returns the bad-parse value and an
;;; error message. Otherwise it packages the language, the two
;;; elements of the context, and list of symbol - wide-string pairs
;;; into a list and returns them as the compilation result.

(def-slot-value-compiler language-translation (parse-result)
  (let* ((language (first parse-result))
	 (includes-context? (not (eq (second parse-result) '|,|)))
	 (term-translation-pairs
	   (if includes-context?	   
	       (cdr (third parse-result))    ; drop the comma
	       (cddr parse-result))))        ; ditto

    (replace-symbol-translations-with-strings term-translation-pairs)
    
    (multiple-value-bind (context? error-message?)
	(if includes-context?
	    (compile-localizing-context (second parse-result)))
      
      (if error-message?
	  (values bad-phrase error-message?)
	  (if context?
	      (make-language-translation-data
		language
		(car context?)
		(cdr context?)
		term-translation-pairs)
	      (make-language-translation-data
		language
		'menu-item  ; defaults for grandfathered
		'menu       ; menu item translations
		term-translation-pairs))))))



(defun replace-symbol-translations-with-strings (term-translation-pairs)
  (loop for pair in term-translation-pairs
	when (symbolp (cdr-of-cons pair))
	  do
	    (setf-cdr-of-cons
	      pair (copy-symbol-name (cdr pair) nil))))

;; What should happen to the symbol? Presumably it shouldn't just be unhooked
;; into the heap ?????????????????



(defun compile-localizing-context (parse-result)
  (let* ((purpose (car parse-result))
	 (domain? (cdr parse-result))
	 (error-message? nil))

    (macrolet ((error-in-semantics-of-translation-statement
		   (control-string  &optional arg1 arg2 arg3 arg4 arg5)
		 `(setq error-message?
			(tformat-text-string
			  ,control-string
			  ,arg1 ,arg2 ,arg3 ,arg4 ,arg5))))
      
      (let ((consistency-data?
	      (domains-consistent-with-localization-purpose purpose)))
	(cond
	  ((null consistency-data?)
	   ;; This will be unreachable provided that the grammar of
	   ;; localization purposes is automatically generated.
	   ;; It is effectively a check for that.
	   (error-in-semantics-of-translation-statement
	     "~a is not a known localization purpose" purpose))
	  
	  ((null domain?)
	   (let ((default? (default-localization-domain consistency-data?)))
	     (if (null default?)
		 (error-in-semantics-of-translation-statement
		   "The localization purpose ~a cannot be defaulted. ~
                    An explicit domain must be provided." purpose))
		 (setq domain? default?)))
	  
	  ((classp domain?)
	   (unless (localization-domain-includes-classes-p consistency-data?)
	     (error-in-semantics-of-translation-statement
	       "The class name ~a is not a valid domain for the localization ~
                purpose ~a because that purpose does not apply to items."
	       domain? purpose)))
	  
	  (t
	   (let* ((legal-domains?
		    (known-localization-domains-for-purpose purpose)))
	     (cond
	       ((null legal-domains?)
		;; This isn't a good msg !!  The fact of the matter is
		;; that we should never get here if our fixed data
		;; is thorough.  What does it take to guarentee that ?
		(error-in-semantics-of-translation-statement
		  "No domain information is available for the ~
                   localization purpose ~a." purpose))

	       ((eq legal-domains? 'no-fixed-localization-domains)
		(unless (eq domain? 'password-change)
		  ;; Kludge. This error pertains to purposes that go with
		  ;; classes, such as "an attribute in the g2-login", and while
		  ;; there should be a class/frame in this instance, there isn't
		  ;; (yet), so hencer the variable doing-password-change-p. 
		  ;; ddm 3/13/98
		  (error-in-semantics-of-translation-statement
		    "~a is not a legal domain for the localization purpose ~a"
		    domain? purpose)))

	       (t
		(unless
		    (localization-domain-includes-classes-p consistency-data?)
		  ;; Allow classes to be referenced in translation frames
		  ;; before they're defined (available) in the KB, but only
		  ;; if the designated purpose supports classes.
		  ;; Otherwise insist it be a anticipated domain.
		  (unless (memq domain? legal-domains?)
		    (error-in-semantics-of-translation-statement
		      "~a is not one of the legal specific domains for the ~
                      localization purpose ~a, i.e. ~a"
		      domain? purpose legal-domains?))))))))))
	
    (if error-message?
	(values nil error-message?)
	(values (phrase-cons purpose domain?) nil))))







;;; The grammar for term-translation pairs, adapted from the original
;;; grammar by changing the names of the non-terminals to abstract them
;;; away from the original case of menu-items.

(add-grammar-rules
  '((term-translation-pair
     (localizable-term '= symbol-or-string)
     (1 . 3))))

(add-grammar-rules-for-list
  'term-translation-pairs 'term-translation-pair
  '\, nil nil )




;;; Expansions for the category `localizable-term' so that we get
;;; prompts for them in the editor

(add-grammar-rules
  '((localizable-term menu-choice)
    (localizable-term attribute-of-a-class)
    (localizable-term button-label)
    (localizable-term simple-message)
    (localizable-term simple-condition)
    ))

;; Lexical instances of Button-labels and simple-messages and
;; simple-conditions are added directly to the grammar in the manner
;; of menu-choices rather than put into directories. They are all
;; g2-internal specific cases rather than things the users can extend,
;; so they are not expanded out into symbols. Special forms are used
;; and sited near the location where they are referenced/defined in
;; the code. See define-simple-message, register-symbol-as-simple
;; -condition, and register-button-label-for-internationalization in
;; this module. The forms appear in the code near a place where the
;; editor button or message type is referenced.  This ought to be
;; rationalized and centralized. (And all of these things (and more)
;; almost certainly should go into directories since there are so
;; vastly many that they clutter the prompt area and are largely
;; impossible to navigate since they're unordered.)


;;; Expand menu-choice
(add-grammar-rules
  '((menu-choice item-menu-choice)
    (menu-choice main-menu-choice)
    (menu-choice workspace-menu-choice)
    (item-menu-choice symbol)	       	; Why do these allow any symbol?
    #+enable-ole (item-menu-choice-available-with-mouse-down symbol)
    (main-menu-choice symbol)))

;; N.b. Using this expansion has the effect of having the list of these
;; various sorts of menu-choices appear as explicit prompts (vs. directories
;; that expand only when selected, as with attribute-name or
;; system-defined-attribute-name. This feels like an inconsistency
;; that we should address at some point. 


;;; Expand attribute-of-a-class
;; This is a new category. The category 'attribute' is defined somewhere,
;; but it expands into float, class, structure-attrubute (sic), string,
;; and number, which is just unworkable.
(add-grammar-rules
  '((attribute-of-a-class attribute-name)
    (attribute-of-a-class system-defined-attribute-name)))


;; This should be moved to a suitably general module
(add-grammar-rules
  '((symbol-or-string symbol)
    (symbol-or-string whole-string)))





;;; The 'old' inner rules for language-translation, which are retained so
;;; that existing KBs with this style of rule for translating menu
;;; items can be supported. Note that any new language translation
;;; statement defined using this toplevel rule (without any context) will be
;;; interpreted as defining the tranlation of a menu item.

(add-grammar-rules-for-list
  'menu-item-translation-pairs 'menu-item-translation-pair
  '\, nil nil)

(add-grammar-rules
  '((menu-item-translation-pair
     (menu-choice '= symbol-or-string)
     (1 . 3))))


;;; The actual equivalent part of the original grammar
;;(add-grammar-rules
;;  '((menu-choice-translation
;;      (menu-choice '= symbol-or-string)
;;      (1 . 3))
;;    (symbol-or-string symbol)	       	; move elsewhere!
;;    (symbol-or-string whole-string)
;;    (item-menu-choice symbol)	       	; Why do these allow any symbol?
;;    (main-menu-choice symbol)
;;    (workspace-menu-choice symbol)
;;    (menu-choice item-menu-choice)
;;    (menu-choice main-menu-choice)
;;    (menu-choice workspace-menu-choice)))
;;
;;(add-grammar-rules-for-list
;;  'menu-choice-translations 'menu-choice-translation
;;  '\, nil nil)



;; Move this when the symbol-or-string grammar rules are moved.

(define-category-evaluator-interface (symbol-or-string
				       :access read-write)
    (or symbol text)
  
  ((set-form (evaluation-value))
   (copy-for-phrase evaluation-value))
  ((get-form (slot-value))
   (copy-evaluation-value slot-value)))


(define-category-evaluator-interface (localizable-term
				       :access read-write)
    symbol
  
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))

(define-category-evaluator-interface (term-translation-pair
				       :access read-write)
    (structure
      term-translation-pair
      ((localizable-term (named localizable-term))
       (value (named symbol-or-string))) 
      (and localizable-term value))
  
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
     ((structure)
      (with-structure (evaluation-value term-translation-pair)
	(with-safe-category-setter-calling
      	(phrase-cons
	  (call-category-setter-safely 'localizable-term localizable-term)
	  (call-category-setter-safely 'symbol-or-string value)))))))
  ((get-form (slot-value))
   (cond
     (slot-value
      (with-new-structure (term-translation-pair)
	(setf localizable-term (call-category-getter 'localizable-term
						(car slot-value) nil nil))
	(setf value (call-category-getter 'symbol-or-string
					  (cdr slot-value) nil nil))))
     (t nil))))



(define-category-evaluator-interface (term-translation-pairs
				       :access read-write)
    (sequence
      (named term-translation-pair)
      1)
  
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
     ((sequence)
      (with-safe-category-setter-calling
      (with-evaluation-sequence-to-phrase-list-mapping
	  (evaluation-value term-translation-pair)
	(call-category-setter-safely 'term-translation-pair
				     term-translation-pair))))))
  ((get-form (slot-value))
   (cond
     (slot-value
        (with-list-to-evaluation-sequence-mapping
	    (slot-value term-translation-pair)
	  (call-category-getter 'term-translation-pair
				term-translation-pair nil nil)))
     (t nil))))








;;;; Notes on Language Translation Frames

;;; In addition to the existence of a language-translation frame
;;; having side-effects, it has an effect on the overall consistency
;;; of the system's localization data in so far as its translations
;;; may duplicate the translations for the same term made by some
;;; other language translation frame, or it may even contain
;;; duplications itself.
;;;
;;; The consistency checking is largely done as part of adding or
;;; removing language translation frames from the symbols that
;;; they provide translations for, i.e. as part of a call to
;;; `{add,remove}-translation-statement-{to,from}-term'.



;;; `Check-for-duplicate-instances-in-language-translation' looks
;;; for multiple instances of the same symbol in a single frame.
;;; It uses `multiple-translations-in-frame' as its note type, and
;;; the list of symbols that are duplicated as the particulars.
;;;
;;; This is a bit wastefull computationally, as we get the
;;; count of the symbol as part of determining that it is duplicated
;;; and then rederive the count when it comes time to write the
;;; note. This is necessary becase there can only be one instance
;;; of a given note type with each frame, and only one particulars
;;; list. Given my druthers, I'd have separate instances of this note
;;; for each instance of a duplicated symbol, and would include both
;;; the symbol and the count with it. (ddm 4/9/97)

(defun check-for-duplicate-instances-in-language-translation
        (target-symbol frame)
  (let ((count (loop for (symbol . translation)
			 in (term-translation-pairs frame)
		     count (eq symbol target-symbol))))
    (when (> count 1)
      (add-to-frame-note-particulars-list-if-necessary
	target-symbol 'multiple-translations-in-frame frame))))
			

(def-frame-note-writer multiple-translations-in-frame
  (duplicated-symbols frame)
  (loop with number-of-subnotes = (length duplicated-symbols)
	for target-symbol in duplicated-symbols
	as i from 1 to number-of-subnotes
	do (tformat
	     "there are ~d translations of ~a in this statement"
	     (loop for (symbol)
		       in (term-translation-pairs frame)
		   count (eq symbol target-symbol))
	     target-symbol)
	   (if (not (=f i number-of-subnotes))
	       (twrite-string "; "))
	finally
	  (incff frame-note-index-skip (-f i 1))))



;;; `Check-for-other-language-translations' looks for the possibility
;;; that the symbol already has a definition in another language-
;;; translation frame that specifies exactly the same context as
;;; the frame now being created (modified) does.
;;;
;;; When it is called from `add-translation-statement-to-term', the
;;; current frame has not yet been added to the list for this symbol,
;;; so any frame we find (whose context matches), will be a duplicate,
;;; and it and this frame should get the appropriate note.
;;;
;;; When called from `remove-translation-statement-from-term', we
;;; check the number of duplicated frames. If it is one, there wasn't
;;; a duplication. If two, there was, but there isn't any more since
;;; the current frame is one of the two. If greater than two, there
;;; still is a duplication, but the current frame is no longer one of
;;; the offenders, and and since it is about to be deleted we don't
;;; need to do anything given the nature of what this note type
;;; reports (i.e. it doesn't identify the duplicating frames since a
;;; list of frames inside a note would be too difficult to maintain
;;; consistently).

(defun check-for-other-language-translations
       (symbol frame-being-checked  &optional remove?)
  (let* ((data (data-of-language-translation frame-being-checked ))
	 (language (localization-data-language data))
	 (purpose (localization-data-purpose data))
	 (domain (localization-data-domain data))
	 (frames
	   (loop with domains = (kb-property-list domain)		
		 for frame in (translations-for-symbol symbol)
		 when (frame-matches-localization-context-p
			frame language purpose domains)
		   collect frame using kb-property-cons
		 finally (reclaim-kb-property-list domains))))

    (let ((number-of-frames (length frames)))
      (if remove?
	  (cond
	    ((=f number-of-frames 0)
	     #+development
	     (cerror "continue" "Zero frames in list. ~
                      Shouldn't have gotten here"))
	    ((=f number-of-frames 1))
	    ((=f number-of-frames 2)
	     (let ((other-frame
		     (if (eq (first frames) frame-being-checked)
			 (second frames)
			 (first frames))))
	       (delete-other-translation-note other-frame symbol)))
	    (t
	     (loop for frame in frames
		   do
	       (decf-other-translation-note frame symbol))))

	  ;; We're adding the frame being checked, so anything we see
	  ;; is a duplication.
	  (cond
	    ((=f number-of-frames 0))
	    ((=f number-of-frames 1)  ; optimizing first duplication
	     (create-other-translation-note
	       (first frames) symbol 1 language purpose domain)
	     (create-other-translation-note
	       frame-being-checked symbol 1 language purpose domain))
	    (t
	     (loop for frame in frames  ;; see note
		   thereis (find-other-translation-particular frame symbol)
		   finally (return-from check-for-other-language-translations))
	     (loop for frame in frames
		   do
	       (incf-other-translation-note frame symbol))
	     (create-other-translation-note
	       frame-being-checked symbol number-of-frames
	       language purpose domain)))))

  (reclaim-kb-property-list frames)))

;; Note: There is a situation described in bug HQ-3541712 whereby it's
;; conceivable that the frame notes were stripped from the already
;; existing duplicated frames. This check keeps us from blowing up
;; in the code that would have followed it. 



;;; The standard routines for changing the particulars associated
;;; with frame notes presently (4/97) use different tests to determine
;;; a particulars identity given the key (the particular) passed in to them.
;;; `add-to-frame-note-particulars-list-if-necessary' uses equal, and
;;; `delete-from-frame-note-particulars-list' uses eq. This means that
;;; care must be exercised when applying these to the multi-element
;;; particular data we use with the duplicated-translation frame note.
;;;
;;; The data is implemented as a structured list, and all manipulations to
;;; an existing datum (particular) must first identify the list by
;;; using `find-other-translation-particular' to ensure that we are
;;; always dealing with eq objects. 

(def-list-structure (other-translation-particular
		      (:consing-function kb-property-cons))
    (other-translation-symbol
     other-translation-count
     other-translation-language
     other-translation-purpose
     other-translation-domain))

(defun find-other-translation-particular (frame symbol)
  (let ((existing-particulars
	  (get-particulars-of-frame-note-if-any
	    'duplicated-translation frame)))
    #+development
    (unless existing-particulars  ; for debugging
      (cerror "watch it blow up" "Unanticipated situation: no existing particulars"))
    (when existing-particulars
      (loop for particular in existing-particulars
	    when (eq (other-translation-symbol particular) symbol)
	      do (return particular)
	    finally
	      #+development (error "shouldn't have gotten here")))))


(defun create-other-translation-note
       (frame symbol count language purpose domain)
  (let ((particular (make-other-translation-particular
		      symbol count language purpose domain)))
    (add-to-frame-note-particulars-list-if-necessary
      particular 'duplicated-translation frame)))

(defun delete-other-translation-note (frame symbol)
  (let ((particular (find-other-translation-particular frame symbol)))
    (delete-from-frame-note-particulars-list
      particular 'duplicated-translation frame)))



;;; When the only change to a frame's duplicated-translation note
;;; is to the number of other frames listed in the particular
;;; for the duplicated term, the change is made to an internal
;;; field in an existing particular, and we do not go the route
;;; of the standard add/delete-frame-note-particulars-list functions.
;;; As a result, the writers for the note fields of these
;;; frames are not automatically called again to update what is
;;; shown in any tables for these frames, which is disconcerting.
;;;
;;; To compensate, we include a call to `update-representations-of
;;; -slot-value' within the `{incf/decf}-other-translation-note'
;;; functions.

(defun incf-other-translation-note (frame symbol)
  (let ((particular (find-other-translation-particular frame symbol)))
    (incf (other-translation-count particular)))
  (update-representations-of-slot-value frame 'frame-status-and-notes))

(defun decf-other-translation-note (frame symbol)
  (let ((particular (find-other-translation-particular frame symbol)))
    (decf (other-translation-count particular)))
  (update-representations-of-slot-value frame 'frame-status-and-notes))




(def-frame-note-writer duplicated-translation
    (particulars)

  ;; The <language> translation of <symbol>
  ;; as a <purpose> for [ <domain> doesn't have enough info ?? ]
  ;; is duplicated in
  ;; { another language-translation item
  ;;  / <count> other language-translation items }

  (loop with number-of-particulars = (length particulars)
	for particular in particulars
	as i from 1
	do
    (when (>f (length particulars) 1)
      (tformat " (~d) " i))
    
    (tformat "the ~a translation of ~a "
	     (other-translation-language particular)
	     (other-translation-symbol particular))
    (tformat "as a ~a of "
	     (other-translation-purpose particular))
    (tformat "~a ~a "
	     (if (unique-localization-domain-p
		   (other-translation-domain particular))
		 "the"
		 (supply-a-or-an (other-translation-domain particular)))
	     (other-translation-domain particular))
    (tformat "is duplicated in ")
    (let ((count (other-translation-count particular)))
      (if (>f count 1)
	  (tformat "~a other language-translation items" count)		 
	  (tformat "another language-translation item" count)))

    (when (not (=f i number-of-particulars))
      (twrite-string "; "))

	finally
	  (when (>f (length particulars) 1)
	    (incff frame-note-index-skip (-f i 1)))))


#+ignore  ;; original -- useful for reference while tweeking wording methods
(write-frame-notes-for-names
  list-of-duplicated-symbols
  "the term "
  "the terms "
  " is duplicated in other language-translation items."
  " are duplicated in other language-translation items.")





;;; `Clear-translation-frame-notes-if-any' is called from the putter.
;;; It lets us avoid having to delete frame notes explicitly when we
;;; determine that they are obsolete, simplifying the code
;;; accordingly.  The put-box-translation-and-text-slot-value method
;;; will review the status of any old side-effects (when the frame is
;;; changed) and establish all the germane side-effects each time it
;;; is called, so we won't lose any notes we should have.

(defun clear-translation-frame-notes-if-any (frame)
  (delete-frame-notes-of-types-in-list
    frame
    '(duplicated-translation
      multiple-translations-in-frame

      ;; These two can be found in old KBs for menu-item translations,
      ;; and should also be cleared since they are redundant in
      ;; purpose with the two new ones.
      non-disjointness-among-language-translations  ; = duplicated-translation
      multiply-translated-menu-choices      ; =  multiple-translations-in-frame
      )

    nil   ; arg = delete-only-from-component-particulars?
    ))




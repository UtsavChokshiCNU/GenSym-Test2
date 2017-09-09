;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module FRAMES4: Frames for Knowledge Bases

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson








;;;; Forward References




(declare-forward-references-to-module
  kb-save2
  note-as-frame-with-kb-state-changes)

(declare-forward-references-to-module
  draw
  enlarge-workspace-if-necessary
  enlarge-workspace-for-block-and-subblocks-as-necessary
  change-workspace-edges-after-margin-change
  add-subblock)

(declare-forward-references-to-module
  boxes
  update-name-box
  make-empty-text
  convert-text-to-text-string
  make-lost-spaces-text-element)

(declare-forward-references-to-module
  connect2
  add-loose-ends-as-subblocks-and-shift)

(declare-forward-references-to-module
  tables
  copy-text)

(declare-forward-references-to-module
  frames5
  change-slot-value)

(declare-forward-references-to-module
  kb-load2
  (loading-kb-p variable)
  #+connections-v2
  (blocks-with-connections-from-kb-read variable))

(declare-forward-references-to-module
  kb-load1
  (kb-flags variable))

(declare-forward-references-to-module
  menus
  delete-menu)

(declare-forward-references-to-module
  simulate5
  (models-used-p variable)
  install-item-in-model-if-appropriate)

(declare-forward-references-to-module
  filters
  attribute-operation-is-allowed-p)

(declare-forward-references-to-module
  panes
  reclaim-workspace-region
  workspace-showing-p-function)

(declare-forward-reference
  count-of-pending-workspace-drawing variable panes)
	
(declare-forward-references-to-module
  connect1
  upgrade-connections)


;;;; Fixing Saved KBs during Reading



;;; `Def-absent-slot-putter' defines an `absent-slot putter', a function to deal
;;; with a slot initialization in a saved kb for a slot named pretty-slot-name,
;;; where the frame in question no longer has a slot of that name.  The
;;; absent-slot putter receives the frame and slot value in variables frame-var
;;; and slot-value-var, respectively, and does whatever is appropriate in body.
;;; (Body should do nothing if the slot is obsolete and its initializations are
;;; to be discarded, or it should use change-slot- value appropriately if the
;;; slot name has changed.)

(def-global-property-name absent-slot-putter)

(defmacro def-absent-slot-putter (pretty-slot-name (frame-var slot-value-var) &body body)
  (let ((name (intern (format nil "PUT-~A-WHERE-SLOT-IS-ABSENT" pretty-slot-name))))
    `(progn
       (defun-simple ,name (,frame-var ,slot-value-var)
	 ,@body
	 nil)
       (setf (absent-slot-putter ',pretty-slot-name) #',name)
       ',name)))



;;; `Def-substitute-for-old-class' specifies that substitute-class is to be substituted
;;; for original-class during the reading of a saved kb, provided that original-class is
;;; not now the name of a class with a class definition.  At the end of reading a saved
;;; kb, every frame that has had a class substitution will have invoked on it its
;;; fix-frame-with-substitute-class class method, if it has one.  Such a method may, if
;;; appropriate, delete the frame.  The reason that the fix-frame-with-substitute-class
;;; method is applied at the end of reading the saved kb is to ensure that all
;;; references to the frame to be fixed up or deleted are in place.
;;;
;;; 
;;; Note that this spec allows for a defined class to have a substitute defined
;;; for it.  This might be used, for example, to change a class from an
;;; instantiable class to a non-instantiable one, i.e., by reclassifying all
;;; instances upon read-in of a KB.
;;;
;;; [Note that this feature could never be used until today.  An obsolete
;;; restriction of the code in read-frame-for-kb prevented it.  This restriction
;;; has been removed.  The one use of this feature at present is to have
;;; KB-RESTRICTIONS, which had instances in all 3.0 KBs, become a
;;; non-instantiable class, with instances reclassified as KB-configuration.
;;; (MHD 6/24/94)]



;;; Some slots, subblocks for example, are no longer represented as simple slots.
;;; Only need absent slot putters for these two since Edges are handled specially
;;; by KB save, and superblock?  is not saved.
;;;
;;; NOTE: also see `process-slot-group-for-block'.

(def-absent-slot-putter subblocks (block value)
  (loop for subblock in value
     do (set-superblock-and-faction subblock block))
  (when value
    (setf (subblocks block)
	  #-subblocks-v2 value
	  #+subblocks-v2 (upgrade-subblocks value))))

(def-absent-slot-putter connections (block value)
  (when value
    (setf (connections block)
	  #-connections-v2 value
	  #+connections-v2 (upgrade-connections value))
    #+connections-v2
    (gensym-push block blocks-with-connections-from-kb-read)))

;; The Four slots were never actually used, but we did a Beta while they
;; were in the product.

(def-absent-slot-putter left-edge-of-content-of-block-1 (block edge)
  (declare (ignore block edge))
  ;;  (left-edge-of-content-of-block-1 -1 system lookup-slot save)
  )

(def-absent-slot-putter top-edge-of-content-of-block-1 (block edge)
  (declare (ignore block edge)))

(def-absent-slot-putter right-edge-of-content-of-block-1 (block edge)
  (declare (ignore block edge)))

(def-absent-slot-putter bottom-edge-of-content-of-block-1 (block edge)
  (declare (ignore block edge)))



;;; As of version 3.0, any new use of def-substitute-for-old-class must be accompanied by
;;; an increment of kb-flags. The third argument must be the new kb-flag. The effect of
;;; this is to restrict substitution to occur only when a kb with older kb-flags is
;;; being loaded.



(def-global-property-name substitute-class-and-kb-flags)

(defmacro def-substitute-for-old-class
	  (original-class substitute-class &optional (kb-flags 199))
  `(setf (substitute-class-and-kb-flags ',original-class)
	 (cons ',substitute-class ,kb-flags)))



;;; `Substitute-class' has as a substitute class as value only when loading a kb
;;; and def-substitute-for-old-class exists for the argument, and the kb being
;;; loaded was last processed with software earlier than the specified kb-flags.

(defmacro substitute-class (class)
  `(and loading-kb-p
	(let ((substitute-class-and-kb-flags?
		(substitute-class-and-kb-flags ,class)))
	  (and substitute-class-and-kb-flags?
	       (<f kb-flags (cdr-of-cons substitute-class-and-kb-flags?))
	       (car (substitute-class-and-kb-flags ,class))))))






;;; `Class-qualified-name-list-p' returns t when its argument is a list and
;;; the car of the list is EQ to CLASS-QUALIFIED-NAME; otherwise it returns nil.

(def-substitution-macro class-qualified-name-list-p (name-or-class-qualified-name-list)
  (and (consp name-or-class-qualified-name-list)
       (eq (car-of-cons name-or-class-qualified-name-list)
	   'class-qualified-name)))




;;; `Write-name-or-class-qualified-name' prints <class-qualifier>::<name> when
;;; its name-denotation needs qualification; otherwise, it prints <name>.  If
;;; name-denotation is not valid, the results are undefined.

(defun-simple write-name-or-class-qualified-name (name-denotation)
  (write-name-denotation name-denotation))

;; Phase out above, and switch callers to use "write-name-denotation"? (MHD 2/18/94)



;;; A `name denotation' is either a list or a symbol.  In the list case, it's
;;; a list of the form
;;;
;;;    (CLASS-QUALIFIED-NAME <defining-class?/symbol> <name/symbol>)
;;;
;;; where name is a slot name or a method name, and class-qualifer? is either nil
;;; or the qualifier upon the name.
;;;
;;; These two components, name and defining-class?, are known collectively as
;;; the `name denotation components' of a name denotation.
;;;
;;; Operations for a name denotation are
;;;
;;;    `denote-name-using-slot-value-conses'  -- creates the least qualified
;;;      name denotation necessary based on a slot description and a
;;;      class description
;;;    `make-slot-name-denotation' -- makes a name denotation given a slot
;;;      name and either nil or a defining classs
;;;    `write-name-denotation-for-slot' -- conceptually creates the least qualified
;;;      name denotation necessary based on a slot description and a
;;;      class description, and then twrites it (but it doesn't really cons)
;;;    `name-denotation-p' -- tests if it looks like one, valid in limited domains
;;;    `unqualified-name' -- returns the name component of a name denotation
;;;    `class-qualifier' -- returns the defining-class? component of a name denotation
;;;    `write-name-denotation' -- twrites a name denotation,
;;;       using the :: syntax if qualified
;;;    `twrite-name-denotation-components' -- same, but takes each component
;;;       as an arg
;;;    `slot-in-name-denotations-list-p' -- takes a slot name, a class qualifer,
;;;       or else nil if it's unnecessary, and a list of name denations; returns
;;;       true when a matching name denotation is in the list


;;; The macro `make-slot-name-denotation' creates a slot name denotation
;;; given a slot name and defining-class?, a class if qualification is needed,
;;; and otherwise nil.  These args are evaluated.
;;;
;;; Conser?, which is not evaluated, should be either nil or a symbol naming a
;;; function or macro that behaves the same as the function CONS.  If nil, it
;;; defaults to SLOT-VALUE-CONS.

(defmacro make-slot-name-denotation (slot-name defining-class? &optional conser?)
  (let ((conser (or conser? 'slot-value-cons)))
    (avoiding-variable-capture (slot-name defining-class?)
      `(if ,defining-class?
	   (,conser
	      'class-qualified-name
	      (,conser
		 ,defining-class?
		 (,conser
		    ,slot-name
		    nil)))
	   ,slot-name))))


;;; `Denote-slot-using-slot-value-conses' returns a class qualified name list when
;;; the slot description is not the default slot description among those slot
;;; descriptions in the class description that have the same pretty slot name;
;;; otherwise it returns the pretty slot name.  It is up to the caller of this function
;;; to reclaim the slot value conses.

(defun-simple denote-slot-using-slot-value-conses
    (slot-description class-description)
  (make-slot-name-denotation
    (pretty-slot-name slot-description)
    (if (slot-name-needs-qualification-p slot-description class-description)
	(defining-class slot-description))))

   

(defun-void write-name-denotation-for-slot (slot-description class-description)
  (write-name-denotation-components
    (if (system-defined-slot-description-p slot-description)
	(or (get-alias-for-slot-name-if-any
	      (pretty-slot-name slot-description)
	      (class-name-of-class-description class-description))
	    (pretty-slot-name slot-description))
	(pretty-slot-name slot-description))
    (if (slot-name-needs-qualification-p slot-description class-description)
	(defining-class slot-description))))

;; GHW & MHD: We'd like to phase out "name-or-class-qualified-name-list" and
;; phase in "name denotation".  Review after the release.  (MHD/GHW 2/18/94)

  


;;; `Name-denotation-p' is true iff thing is either a cons whose car is
;;; CLASS-QUALIFIED-NAME.
;;;
;;; This is valid only in limited domains.  Note that this does not definitively
;;; distinguish this object from all other Lisp objects.  It is the callers
;;; responsibility to meet any other requirements, namely that the list be three
;;; long, that it have symbols in its second and third conses, that they be
;;; semantically correct, etc.

(def-substitution-macro class-qualified-name-denotation-p (thing)
  (and (consp thing)
       (eq (car-of-cons thing) 'class-qualified-name)))

(def-substitution-macro name-denotation-p (thing)
  (or (symbolp thing)
      (class-qualified-name-denotation-p thing)))



;;; `Unqualified-name' takes a name or a class qualified name list and
;;; returns the name.

(def-substitution-macro unqualified-name (name-denotation)
  (if (consp name-denotation)
      (third-of-long-enough-list name-denotation)
      name-denotation))


;;; `Class-qualifier' takes a name or a class qualified name list and
;;; returns nil for the former and the class name for the latter.
	
(def-substitution-macro class-qualifier (name-denotation)
  (when (consp name-denotation)
    (second-of-long-enough-list name-denotation)))


;;; `Write-name-denotation' prints <class-qualifier>::<name> when its
;;; name-denotation needs qualification; otherwise, it prints <name>.  If
;;; name-denotation is not valid, the results are undefined.

(defun-simple write-name-denotation (name-denotation)
  (write-name-denotation-components
    (unqualified-name name-denotation) (class-qualifier name-denotation)))


;;; `write-name-denotation-components' prints <defining-class?>::<name> when
;;; defining-class? is non-nil; otherwise, it prints <name>.

(defun-simple write-name-denotation-components (name defining-class?)
  (tformat
    (if defining-class? "~(~a::~a~)" "~(~a~)")
    (or defining-class? name)
    name))


;;; `slot-denotation-member' says whether the slot denoted by slot-name and
;;; class-qualifier? is a member of the list name-denotations-list.  If so, it
;;; returns the tail of the list starting with the name denotation for slot-name
;;; and class-qualifier?, a la the function member.
;;; 
;;; Class-qualifier?  must be nil if it is to match unqualified name denotations
;;; in the list.  I.e., this does not ever check any actual class structures.
;;; It just does a trivial check, more or less like the function MEMBER.

(defun-simple slot-denotation-member
    (slot-name class-qualifier? name-denotations-list)
  (loop for name-denotations on name-denotations-list
	as name-denotation = (car name-denotations)
	when (and
	       (eq slot-name (unqualified-name name-denotation))
	       (eq class-qualifier? (class-qualifier name-denotation)))
	  return name-denotations))

;;; The function `get-pretty-slot-name-for-parent-attribute-if-any' returns the
;;; pretty slot of the parent attribute that contains the given subobject.  If
;;; the pretty name is not found, for example, if the frame is not a subobject,
;;; then NIL is returned.

(defun get-pretty-slot-name-for-parent-attribute-if-any (item)
  (multiple-value-bind
      (parent-frame? parent-slot-name? parent-defining-class?)
      (get-kb-parent-information item)
    (declare (ignore parent-frame? parent-defining-class?))
    parent-slot-name?))

;; Is this still needed? (MHD 2/19/94)

;; Note that this function is not needed if the parent-attribute-name slot
;; contains a pretty-slot name.  - cpm, 2/22/94



;;; The function `get-defining-class-for-parent-attribute-if-any' returns the
;;; defining class of the parent attribute that contains the given subobject.
;;; If the defining class is not found, for example, if the frame is not a
;;; subobject, then NIL is returned.

(defun get-defining-class-for-parent-attribute-if-any (item)
  (multiple-value-bind
      (parent-frame? parent-slot-name?
		     parent-slot-name-defining-class?)
      (get-kb-parent-information item)
    (if parent-frame?
	(or parent-slot-name-defining-class?
	    (defining-class
		;; We use the unoptimized slot-description lookup here because
		;; this function is called by item-deactivation code possibly
		;; when the class hierarchy is changing and the slot-description
		;; hash-tables are temporarily out-of-sync.
		(get-slot-description
		  parent-slot-name?
		  (slot-descriptions
		    (class-description-slot parent-frame?))))))))




;;; The function `get-slot-description-for-parent-attribute-if-any' returns the
;;; slot-description of the parent attribute that contains the given subobject.
;;; If the slot-description is not found, for example, if the frame is not a
;;; subobject, then NIL is returned.

#+unused
(defun get-slot-description-for-parent-attribute-if-any (item)
  (multiple-value-bind
      (parent-frame? parent-slot-name?
		     parent-slot-name-defining-class?)
      (get-kb-parent-information item)
    (if parent-frame?
	(get-slot-description-of-frame
	  parent-slot-name?
	  parent-frame?
	  parent-slot-name-defining-class?))))

;; Rewrite this function if the parent-attribute-name no longer contains the
;; unique-slot-name.  - cpm, 2/22/94
;;
;; -- DONE.  Revised these for new format of that slot.  Are these still needed?
;; (MHD 2/22/94)


;;; no checking no overhead
(defmacro defining-class-of-qualified-attribute (qualified-attribute)
  `(cdr-of-cons ,qualified-attribute))

(defmacro defining-class-of-qualified-attribute-if-any? (qualified-attribute?)
  (let ((attribute (gensym)))
    `(let ((,attribute ,qualified-attribute?))
       (if (consp ,attribute)
	   (cdr-of-cons ,attribute)))))

(defmacro attribute-of-qualified-attribute (qualified-attribute)
  `(car-of-cons ,qualified-attribute))




;;; The function `slot-exists-in-frame-p' returns T iff the given slot
;;; currently exists for the given frame.
;; -fmw, 8/26/94

(defun slot-exists-in-frame-p (slot-designation frame)
  (not (null
	 (get-slot-description-of-frame (unqualified-name slot-designation)
					frame
					(class-qualifier slot-designation)))))







;;; The function `parse-slot-name-denotation' returns a slot name denotation
;;; parsed from a symbol naming a slot of the form BAR or FOO::BAR.  The
;;; denotation is composed of slot-value conses.  NIL is returned if the symbol
;;; was not parseable (for example, FOO:).  The returned slot-name is
;;; unaliased, thus, this routine performs the entire translation from external
;;; to internal form.

(defun parse-slot-name-denotation (symbol frame)
  (let* ((string (symbol-name-text-string symbol))
	 (end (text-string-length string))
	 (delimiter #.%\:)
	 (pos? (position-in-text-string delimiter string)))
    (multiple-value-bind (slot-name? class-name?)
	(cond ((null pos?)
	       (values symbol (class frame)))
	      (t
	       (let ((pos2
		       ;; Allow any number of colons.
		       (loop for i from pos? below end
			     while (char-equalw (charw string i) delimiter)
			     finally (return i))))
		 (values
		   (and (<f pos2 end)
			(intern-text-string-substring string pos2 end))
		   (intern-text-string-substring string 0 pos?)))))
      (when slot-name?
	(make-slot-name-denotation
	  (unalias-slot-name-if-necessary slot-name? class-name?)
	  class-name?)))))






;;;; Slot Types



;;; The `type' of a slot, if any, is a slot feature of the form
;;;
;;;    (TYPE grammar-category-symbol . slot-edit-features) or
;;;
;;;    (TYPE FREE . slot-edit-features) or
;;;
;;;    (TYPE NIL [TEXT]),
;;;
;;; where slot-edit-features is a possibly empty list of symbols.

;;; Slot edit features are directives that may effect editing, parsing, and
;;; slot compiling.  Note that the entire type feature is available within
;;; the dynamic scope of editing as (type-of-slot-being-edited current-edit-state).

;; What can we assume is always present within this dynamic extent? A
;; current-edit-state structure? Probably not a type?

;;; Slot edit features may be used to specify that a slot may be edited with
;;; a particular form of graphic editing technique, e.g. an icon editor.

;;; Each type should be documented below. They should only be accessed through
;;; the abstractions given below. 

;;; For a slot to be shown in an "attributes table" (q.v.), (1) it must have a
;;; TYPE feature and either no DO-NOT-PUT-IN-ATTRIBUTE-TABLES feature, or no
;;; DO-NOT-PUT-IN-ATTRIBUTE-TABLES that is a list of the form
;;; (DO-NOT-PUT-IN-ATTRIBUTE-TABLES condition), where condition is one of NUPEC or
;;; NOT-NUPEC, and where the condition holds for NUPEC if (nupec-authorized-p) is
;;; true, and the condition holds for NOT-NUPEC if (nupec-authorized-p) is false,
;;; and (2) it must have no DO-NOT-PUT-IN-ATTRIBUTE-TABLES-IF-NULL feature if the
;;; value of the slot is NIL.

;;; Added a condition to DO-NOT-PUT-IN-ATTRIBUTE-TABLES: NO-ENHANCED-TRACING
;;; which holds when (explanation-related-features-enabled-func?) is
;;; false. -dkuznick, 7/15/98
;;;
;;; For a slot to be user-editable, (1) it must have a TYPE feature that specifies
;;; the grammar category of text representations of legal values for the slot.  (Such
;;; a grammar category cannot be named FREE or NIL.)  (2) It must have no NOT-USER-EDITABLE
;;; slot feature.  And (3) if this is a runtime-only system, it must not have the slot
;;; feature SELECT-CHANGES.  The function type-of-slot-if-editable returns the TYPE feature
;;; if and only if all of these conditions are met; it should be used as the only method
;;; to determine if a slot is editable.

;;; The presence of a TYPE feature may also affect whether or not a slot's value is saved
;;; in a saved kb.  Specifically, a slot value is saved only if it either has a TYPE
;;; feature and no DO-NOT-SAVE feature or a SAVE feature and no TYPE feature.

;;; A `text slot' is a slot that has, within its value, a text representation precisely as
;;; it was after its most recent editing by the user, possibly with one or more `ellipses'
;;; to indicate that it was not or could not have been parsed, translated, and compiled.
;;; A text slot must have a type feature of the form (TYPE grammar-category-symbol TEXT).
;;; A `free text slot' is a text slot whose type feature is precisely (TYPE FREE TEXT);
;;; the `free text' in a free text slot is not parsed.

;;; A `text slot value' must be of the form
;;;
;;;    (translation-or-compilation . text),
;;;
;;;    (no-value . text), or
;;;
;;;    NIL.
;;;
;;; `No-value', the value of special variable no-value, appears when the text is free text
;;; or was not or could not have been parsed, translated, and compiled.




;;; `Get-type-of-slot-if-any' returns the type feature, if any, for the slot in frame
;;; named slot-name.

(defun get-type-of-slot-if-any (frame pretty-slot-name &optional class-qualifier?)
  (let ((slot-description? (get-slot-description-of-frame
			     pretty-slot-name frame class-qualifier?)))
    (if slot-description?
	(feature-assq 'type (slot-features slot-description?))
	nil)))

;; Implement this in terms of a slot feature lookup abstraction!








;;; `Category-symbol-given-slot-type' is the accessor for the category symbol component of
;;; type-of-slot, a type feature.

(defmacro category-symbol-given-slot-type (type-of-slot)
  `(second ,type-of-slot))

;; Use def-list-structure to define the above accessors!



;;; The slot edit feature `TEXT' is discussed above.

;;; The slot edit feature `PROCEDURE' is used to limit the
;;; grammar for procedures to a subset of those used for the inference engine.



;;; `Text-slot-type-p' is true if type-of-slot describes a text slot,
;;; that is, if 'text is a slot-edit-feature of the slot. This macro
;;; is here only because 'text predates the generalized idea of a
;;; slot-edit-feature.

(defmacro text-slot-type-p (type-of-slot)
  `(memq 'text (cddr ,type-of-slot)))		; change later?



;;; `Free-text-slot-type-p' is true if type-of-slot describes a free text slot.

(defun-substitution-macro free-text-slot-type-p (type-of-slot)
  (or (eq (cadr type-of-slot) 'free)		; change later?
      (eq (cadr type-of-slot) 'free-text-attribute)))



;;; `Slot-edit-feature-p' is true if type-of-slot has the specified
;;; slot-edit-feature.

(defmacro slot-edit-feature-p (slot-edit-feature type-of-slot)
  `(memq ,slot-edit-feature (cddr ,type-of-slot)))





;;; Type-of-slot-if-editable returns the type feature, if any, for the slot in frame
;;; named slot-name if that slot is editable.

;;; Either both class?  and slot-name?  must be non-nil or
;;; slot-description-if-known?  must be non-nil.

(defun type-of-slot-if-editable
       (class? slot-name? &optional slot-description-if-known? class-if-specific?)
  (if (framep class?)				; changes arg!
      (setq class? (class class?)))		; for compatibility -- fix all callers!!
  (let* ((slot-description
	   (or slot-description-if-known?
	       (slot-description-from-class
		 class? slot-name? class-if-specific?)))
	 (slot-features (slot-features slot-description)))
    (type-slot-feature-assq-if-editable slot-features)))



;;; Get-type-from-slot-features-if-editable returns the type feature out of
;;; slot-features provided that all of the following conditions are met:
;;;
;;;   (1) there's no NOT-USER-EDITABLE feature;
;;;   
;;;   (2) the type is either a free text type or
;;;       contains a grammar category symbol; AND
;;;       
;;;   (3) gathering-normally-editable-slots-for-search? is true
;;;       OR this is either not a runtime system or
;;;          the SELECT-CHANGES features is present
;;;
;;; The special variable `gathering-normally-editable-slots-for-search?' is
;;; bound globally to nil, and is intended to be bound to true by the search
;;; facilities in Inspect in order to achieve non-destructive searches of
;;; editable slots.  As said above, it overrides the normal desire of
;;; type-slot-feature-assq-if-editable to refuse to select slots non-editable
;;; only due to authorization/licensing.

(defvar gathering-normally-editable-slots-for-search? nil)

(defun type-slot-feature-assq-if-editable (slot-features)  
  (unless (feature-assq 'not-user-editable slot-features)
    (let ((type-of-slot? (feature-assq 'type slot-features)))
      (when (and type-of-slot?
		 (or (free-text-slot-type-p type-of-slot?)
		     (get-category-for-category-symbol-if-any
		       (category-symbol-given-slot-type type-of-slot?))))
	(when (or gathering-normally-editable-slots-for-search?
		  (not (and (g1-authorized-p)
			    (memq 'PROCEDURE-DEFINITION type-of-slot?)))
		  #+pre-g2-v5-licensing
		  (and (not (runtime-option-authorized-p))
		       (not (restricted-use-option-authorized-p))
		       (not (embedded-option-authorized-p))
		       (not (and (g1-authorized-p)
				 (memq 'PROCEDURE-DEFINITION type-of-slot?))))
		  (not (feature-assq 'select-changes slot-features)))
	  type-of-slot?)))))







;;; `Get-slot-description-if-editable-attribute' ... aliased-slot-name and
;;; class-qualifier?  here constitute an "untrusted attribute reference".  This
;;; returns the designated slot description if any only if the designation is
;;; for a slot that is user editable.
;;;
;;; A further condition is that the slot must be editable per the current
;;; "configurations" (i.e., user restrictions, etc.), which is determined by a
;;; call to attribute-operation-is-allowed-p for the EDIT-ATTRIBUTE
;;; operation.

;;; For now, restrictions on class-qualified attributes are not supported; you
;;; can only restrict an unqualified attribute name, and that applies to all
;;; attributes that have that name, which there are potentially more than one of
;;; (at least for user-defined attributes).
;;
;; This may change in the future.  The easiest next step to imagine is to have
;; an unqualified attribute name reference _in the restrictions_ (not here)
;; continue to "match" all slots with attribute-name ("wildcarding"), but then
;; allowing qualified attribute name references there "match" at most one slot
;; (in a given frame).  For now, frame-system-operation-is-allowed-p only
;; supports the wildcarding option.

(defun get-slot-description-if-editable-attribute
    (frame aliased-slot-name class-qualifier?)
  (let* ((slot-name
	   (unalias-slot-name-if-necessary
	     aliased-slot-name
	     frame
	     ;; class-qualifier? ; some day! (MHD 2/15/94)
	     ))
	 (class-description
	   (class-description-slot frame))
	 (slot-description?
	   (get-slot-description-of-class-description	    ; May return nil
	     slot-name class-description class-qualifier?)))
    (when (and slot-description?
	       (type-slot-feature-assq-if-editable
		 (slot-features slot-description?))
	       (attribute-operation-is-allowed-p
		 'edit-attribute frame
		 aliased-slot-name			    ; Note: restriction on the _alias_
		 (defining-class slot-description?)))
      slot-description?)))




;;; The function `slot-editable-p' is the same as the preceding, except that it
;;; takes an INTERNAL (unaliased) slot name.

(defun slot-editable-p (frame internal-slot-name class-qualifier?)
  (get-slot-description-if-editable-attribute
    frame
    (alias-slot-name-if-necessary internal-slot-name frame)
    class-qualifier?))





;;;; Slot Value Compilation and Phrase Floats



(def-global-property-name slot-value-compiler)
(def-global-property-name use-slot-value-compiler-for-default-overrides-p)


;;; `Def-slot-value-compiler' defines a `slot value compiler', a function that compiles a
;;; slot value for slots whose TYPE feature specifies grammar-category-symbol.

;;; A slot value compiler compiles a successful and unambiguous `parse result', the
;;; result of parsing a text representation for a slot value of the type specified by
;;; grammar-category-symbol.  A parse result is an instance of the grammar category that
;;; matches, in a unique way, some grammar rule of the form (grammar-category-symbol
;;; ...).  Structurally, a parse result is just like a slot value except that (a) phrase
;;; conses are used in place of slot value conses, (b) slot constants and "no value"
;;; cannot occur, (c) frames and connections do not occur, (d) phrase conses may
;;; appear multiply as long as there are no circular structures in the parse result.
;;; An atomic parse result is called a `token', and a non-atomic parse result is called
;;; a `phrase'.

;;; Body, which will be the function's body, refers to the parse result to be
;;; compiled via parse-result-var, and, if frame-and-maybe-slot-name-vars is
;;; specified, body may refer to the frame and maybe the slot name via the
;;; specified variables, say to examine the current slot value.  In addition,
;;; defining-class?, slot-component-name, and slot-component-group vars may
;;; also defined and referred to; note that the actual parameter to the
;;; defining-class? var passed in when the compiler is called will be non-nil
;;; only if a class-qualification is necessary.

;;; Body should return either a `compilation result' (the compilation of the parse
;;; result) or the value of special variable bad-phrase.  A `compilation result' has
;;; exactly the same form as a parse result.  This is necessarily so, because if no
;;; slot value compiler has been defined for a particular grammar category, the parse
;;; result serves as the compilation result.

;;; When a slot value compiler returns bad-phrase, it may also return, as a second
;;; value, a (recyclable) text string explaining why it rejected the input.  

;;; Before a compilation result is stored into a slot, it is copied by means of
;;; copy-for-slot-value, and thereby becomes a slot value.  (This allows all
;;; phrase conses, phrase floats, managed arrays, managed floats, and text strings
;;; in the compilation result, the parse result, and all intermediate parsing
;;; computations to be reclaimed.)

;;; A slot value compiler should use phrase conses (see module PARSE) for all conses
;;; in the compilation result, and it may also use them for temporary structures
;;; required during compilation.  It must not, however, use phrase conses in any
;;; non-compilation-result-component structures it might store as side-effects, even
;;; where such structures are parts of components of the compilation (say a procedure
;;; compilation).  A slot value compiler may mutate phrase conses and/or allow them to
;;; appear multiply as components of the compilation result (provided that no circular
;;; structures are created thereby and provided it is wary of multiple occurences of
;;; phrase conses in the parse result).  A slot value compiler need never concern
;;; itself with recycling phrase conses.

;;; When a slot value compiler creates a managed float or a text string (other than
;;; for the second value in a bad-phrase return), it should explicitly note that
;;; managed float or text string using note-use-of-managed-float-in-phrase or
;;; note-use-of-text-string-in-phrase, respectively (except in the case of a managed
;;; float created by make-phrase-float, where the managed float is automatically
;;; noted).  Then the managed float or text string will get reclaimed, along with
;;; phrase conses and incomplete phrases, when the current edit state is reclaimed.
;;; (It is quite rare for a slot value compiler to create such managed floats or
;;; text strings.)  


;;; Variable Naming Conventions
;;;
;;; When defining a slot value compiler, we recommend that you conventionally
;;; name the (first) argument parse-result, and, when the compilation is
;;; successful, the (first) value compilation-result.
;;;
;;; The name TRANSLATION is actually somewhat more frequently encountered
;;; instead of parse-result, especially in older code; however, in common usage
;;; its meaning is not precise: translation is often used to mean a parse
;;; result, but it is also used to mean a compilation result.  For example, the
;;; slot box-translation-and-text usually contains a compilation result
;;; different than its original parse result.  For another example, the COMPILE1
;;; module uses the term translation, but usually with the qualifier "raw";
;;; here, a "raw translation" is "transformed" into a "compiled expression".
;;;
;;; `Translation' is a good generic term for the overall parsing and compilation
;;; process, as well as for the various intermediate results of that process.
;;; But the precise names for the argument (parse-result) and result
;;; (compilation-result) are preferred when using def-slot-value-compiler.
;;;
;;; You will also encounter, mostly in older code, either the name VALUE for
;;; parse-result, or the name of the grammar category symbol for parse-result.
;;; Neither of these make sense, and neither should be used.  Using the grammar
;;; category symbol is at best redundant with the symbol that appears textually
;;; before it, e.g. (def-slot-value-compiler xyz (xyz ...) ...).  It is not
;;; clear why one would choose to use the name value, except perhaps by immitation
;;; of or confusion with the common name for the new-value var used in
;;; def-slot-putter forms.
;;;
;;; Using the grammar category symbol as the parse result variable is inherently
;;; a bit confusing, since then you have a situation in which an argument is named
;;; after some grammar category, say X, and then is transformed into something
;;; different, which other functions (e.g. the slot value writers) will then also
;;; call an X.
;;;
;;; If, after reading the above, you are still determined to use a nongeneric
;;; name for the parse-result variable, it is quite reasonable to construct one of
;;; the form
;;;
;;;    <grammar-category-symbol>-PARSE-RESULT

;; Above "Variable Naming Conventions" added today.  At about the same time, I toured
;; all of the slot value compilers and changed them as follows:
;;
;;     In all cases where parse-result-var was TRANSLATION or PARSE-RESULT, I left
;;     it as is. (roughly 30%)
;;
;;     In all cases, where parse-result-var was VALUE, FORM, THING, or PARSE, I
;;     changed it to PARSE-RESULT.  (roughly 35%)
;;
;;     In all cases where parse-result-var was the same as grammar-category-symbol
;;     (or only trivially different or different for obviously trivial reasons), I
;;     changed it to parse-result. (roughly 33% (61 slots))
;;
;;        These slots include
;;
;;            relation-name? (RELATIONS)
;;            authorization-interval? (SEQUENCES2)
;;            current-language (MENUS)
;;            interval-for-retry (SETS)
;;            data-server-aliases (VARIABLES)
;;            nupec-extra-action-list (RULES)
;;            tabular-function-data-type (FUNCTIONS)
;;            keep-tabular-function-sorted? (FUNCTIONS)
;;            add-or-delete-rows (FUNCTIONS)
;;            procedure-name? (PROC-GRAM)
;;            chart-style (CHARTS1)
;;            data-series-descriptions (CHARTS1)
;;            chart-annotations (CHARTS1)
;;            item-designations-for-model (SIMULATE5)
;;            constant-designation-list? (GRAMMAR1)
;;            constant-designation-list (GRAMMAR1)
;;            symbol-list (GRAMMAR1)
;;            quantity-list (GRAMMAR1)
;;            integer-list (GRAMMAR1)
;;            float-list (GRAMMAR1)
;;            whole-string-list (GRAMMAR1)
;;            truth-value-list (GRAMMAR1)
;;            non-default-number? (GRAMMAR2)
;;            attribute (GRAMMAR2)
;;            validity-intervar (GRAMMAR2)
;;            sensor-validity-interval (GRAMMAR2)
;;            interval? (GRAMMAR2)
;;            interval (GRAMMAR2)
;;            positive-interval? (GRAMMAR2)
;;            specific-simulation-formula? (GRAMMAR2)
;;            whole-string? (GRAMMAR2)
;;            number? (GRAMMAR2)
;;            integer? (GRAMMAR2)
;;            symbol? (GRAMMAR2)
;;            simulation-time-increment? (GRAMMAR2)
;;            simulation-time-increment (GRAMMAR2)
;;            positive-integer (GRAMMAR2)
;;            priority (GRAMMAR2)
;;            non-negative-integer (GRAMMAR2)
;;            symbolic-value-list (GRAMMAR2)
;;            icon-description? (GRAMMAR2)
;;            connections? (GRAMMAR2)
;;            object-change (GRAMMAR2)
;;            connection-change (GRAMMAR2)
;;            message-change (GRAMMAR2)
;;            stub-designation-or-none (GRAMMAR2)
;;            cross-section-pattern (GRAMMAR2)
;;            extra-grid-line-specs (GRAMMAR2)
;;            dial-ruling-parameter (GRAMMAR2)
;;            meter-ruling-parameter (GRAMMAR2)
;;            horizontal-graph-rulijng-parameter? (GRAMMAR2)
;;            vertical-graph-ruling-parameter? (GRAMMAR2)
;;            vertical-gridline-interval? (GRAMMAR2)
;;            display-interval (GRAMMAR2)
;;            yes-or-no (GRAMMAR2)
;;            yes-or-no? (GRAMMAR2)
;;            display-expression (GRAMMAR2)
;;            list-of-display-expressions (GRAMMAR2)
;;            list-of-graph-expressions (GRAMMAR2)
;;            gsi-interface-name (GSI)
;;            g2-to-g2-interface-name (G2DS)
;;            g2-meter-name (G2-METERS)
;;            
;;            
;;            
;;     A few slots do not fit in with any of the above cases and were written by
;;     me and are maintained by me; in these cases, I found it fine to change
;;     their parse-result-var names to parse-result as well. (roughly 1%)
;;
;;     In the case of other slots, I left parse-result-var as is.  (roughly 1%)
;;
;;        These slots include
;;
;;            expression-cell (CELLS)
;;            cell-format (CELLS)
;;            close-log-file (GRAMMAR2)
;;            backup-log-file (GRAMMAR2)
;;
;; In numerous cases, I added documentation to clarify what was expected in terms of
;; a parse-result argument, where that was at all evident and where it was not too
;; much trouble (for me).
;;
;; This commentary is also being put into the paper trail with the title "Slot Compiler
;; Variable Names".  (MHD 2/26/91)

(defmacro def-slot-value-compiler
    (grammar-category-symbol
     (parse-result-var &optional frame-var?
		       slot-name-var? defining-class?-var?
		       slot-component-name-var?
		       slot-component-group-var?)
     &body body)
  (let ((name (intern (format nil "COMPILE-~A-FOR-SLOT" grammar-category-symbol)))
        ignored-vars frame-var
	slot-name-var defining-class?-var
        slot-component-name-var slot-component-group-var)
    (if frame-var?
	(setf frame-var frame-var?)
	(push (setf frame-var (gensym)) ignored-vars))
    (if slot-name-var?
	(setf slot-name-var slot-name-var?)
	(push (setf slot-name-var (gensym)) ignored-vars))
    (if defining-class?-var?
	(setf defining-class?-var defining-class?-var?)
	(push (setf defining-class?-var (gensym)) ignored-vars))
    (if slot-component-name-var?
	(setf slot-component-name-var slot-component-name-var?)
	(push (setf slot-component-name-var (gensym)) ignored-vars))
    (if slot-component-group-var?
	(setf slot-component-group-var slot-component-group-var?)
	(push (setf slot-component-group-var (gensym)) ignored-vars))
    (multiple-value-bind (doc-and-decl-forms body-after-doc-and-decl)
	(split-defun-body body)
      (let* ((use-slot-value-compiler-for-default-overrides-p
	      (null frame-var?))
	     (doc-and-decl-forms-for-defun
	      (loop for doc-and-decl-form in doc-and-decl-forms
		    collect
		    (if (not (and (consp doc-and-decl-form)
				  (eq (car doc-and-decl-form) 'declare)))
			doc-and-decl-form
			(cons
			 'declare
			 (loop for decl in (cdr doc-and-decl-form)
			       for decl-type? = (and (consp decl) (car decl))
			       if (eq decl-type? 'use-for-default-overrides)
				 do (setq use-slot-value-compiler-for-default-overrides-p t)
			       else
				 if (eq decl-type? 'do-not-use-for-default-overrides)
				   do (setq use-slot-value-compiler-for-default-overrides-p nil)
				 else
				   collect decl))))))
	`(progn
	   (defun ,name (,parse-result-var ,frame-var ,slot-name-var
					   &optional
					   ,defining-class?-var
					   ,slot-component-name-var
					   ,slot-component-group-var)
	     ,@(when ignored-vars
		 `((declare (ignore ,@ignored-vars))))
	     ,@doc-and-decl-forms-for-defun
	     ,@body-after-doc-and-decl)
	   (setf (slot-value-compiler ',grammar-category-symbol) #',name)
	   (setf (use-slot-value-compiler-for-default-overrides-p ',grammar-category-symbol)
		 ,use-slot-value-compiler-for-default-overrides-p)
	   ',grammar-category-symbol)))))





;;;; Outputting to (Unformatted) Text


;;; NOTE: this section logically belongs in the module BOXES in or right after
;;; the section that defines the "text" data structure.  However, it appears
;;; here in order to allow its defined macro to be used in the sections that
;;; follow. Please see the section defining the text datatype (where the concept
;;; "text" is defined), in BOXES, for further information on text.


;;; `Twith-output-to-text' executes body in a twith-output-to-text-string
;;; context, and then returns as its result a text data structure corresponding
;;; to the resulting text output by evaluating body.  The text is unformatted,
;;; and needs to be formatted, in general, before being presented to the user on
;;; a workspace.


(defmacro twith-output-to-text (&body body)
  `(let* ((gensym-list-of-wide-strings
	   (twith-output-to-wide-string-list
	     . ,body)))
     (prog1
	 (loop for string in gensym-list-of-wide-strings
	       collect (make-lost-spaces-text-element 0)
		 using slot-value-cons-macro
	       collect (if (<f (wide-string-length string)
			       use-full-size-of-with-output-wide-string-cutoff)
			   (let ((short-string (copy-text-string string)))
			     (reclaim-text-string string)
			     short-string)
			   string)
		 using slot-value-cons-macro)
       (reclaim-gensym-list gensym-list-of-wide-strings))))
    





;;;; Text Representations for Slot Values

;; Consider moving the contents of this section to one or more other places.



(def-global-property-name slot-value-writer)



;;; `Def-slot-value-writer' defines a `slot value writer', a function that writes the
;;; value of slots of a particular type, namely, slots whose TYPE feature specifies
;;; grammar-category-symbol.  Body, which will be the slot value writer's body,
;;; refers to the slot value via slot-value-var, and, if listed-frame-var is
;;; specified, body may refer to the frame containing the slot via this listed
;;; variable.

;;; A slot value writer is invoked when a text representation for a slot value is
;;; being generated by make-text-representation-for-slot-value (see below), but it
;;; can also be invoked, via write-slot-value, while "twriting" a larger text.  Note
;;; that for each grammar category specified in a TYPE feature of a slot, a slot
;;; value writer MUST be defined.

;;; Slot value writers should use twrite, twrite-character, twrite-string, tformat,
;;; etc.; see the documentation and restrictions for these in UTILITIES1.  Special
;;; variables write-symbols-in-lower-case? and write-symbols-parsably? are bound to
;;; true during the execution of body, so that symbols written by slot value writers
;;; appear, by default, in lower case with characters quoted as necessary.  These
;;; and other defaults can be overridden locally within a slot value writer by
;;; setting or binding the appropriate special variables locally or by using
;;; specialized write functions such as twrite-parsably.  Slot value writers do not
;;; have to write newline characters, since what they write will be formatted before
;;; being displayed or printed, but they may write line separation characters using
;;; twrite-line-break to force line breaks.

;;; The special variable `leave-text-representation-as-a-single-line?' is a system
;;; variable with a global binding, initially nil, but irrelevent in most contexts.
;;; If a slot value writer wishes to indicate that what it has written should be
;;; formatted as a single line, it should set special variable
;;; leave-text-representation-as-a-single-line?  non-nil.  The users of this variable
;;; set it to nil immediately before calling a slot value writer, and then
;;; immediately make use of its value when creating or reformatting a text cell.
;;; This helps update-representations-in-tables be more efficient.  See
;;; update-representations-in-tables and make-text-cell-for-slot for examples.  Most
;;; things should ignore the value of this variable; in particular, formatting code
;;; should not directly use it.

(def-system-variable leave-text-representation-as-a-single-line? frames4 nil)

(defmacro def-slot-value-writer
	  (grammar-category-symbol (slot-value-var . listed-frame-var) &body body)
  (let ((name (intern (format nil "WRITE-~A-FROM-SLOT" grammar-category-symbol)))
	(frame-var (if listed-frame-var (car listed-frame-var) (gensym))))
    `(progn
       (defun ,name (,slot-value-var ,frame-var)
	 ,@(if (null listed-frame-var) `((declare (ignore ,frame-var))))
	 . ,body)
       (setf (slot-value-writer ',grammar-category-symbol) #',name)
       ',name)))

;; Consider binding write-symbols-parsably? to nil when a slot writer is writing
;; the value of a slot with the feature NOT-USER-EDITABLE.  This would produce
;; a more aesthetic result in certain cases, but on the other hand might seem
;; somewhat inconsistent to the user, would lose a bit of speed, and would
;; require some revamping of calls to make-text-representation-for-slot-value et al.

;; Consider changing the way slot value writers are named, perhaps eliminating the
;; "-FROM-SLOT" part of the name.

;; Consider attaching slot value writers to slot names too.



;;; `Def-slot-value-writer-as-existing-function' is used to define a slot-writer for a
;;; user-defined grammar category. It would be unacceptable to call def-slot-value-writer
;;; at this time, since it would either create an interpretive definition, or invoke
;;; a Lisp compiler, both of which are unacceptable.  Fortunately this is not necessary
;;; because the function will already exist, being more general than what is needed
;;; for the particular slot.  This is used in the function DEFINE-UNITS-OF-MEASURE
;;; in module GRAMMAR.  The function called is WRITE-ATTRIBUTE-FROM-SLOT.

(defmacro def-slot-value-writer-as-existing-function
	  (grammar-category-symbol existing-function-name)
  `(setf (slot-value-writer ',grammar-category-symbol) #',existing-function-name))

;; Note that slot-value-writer is a global property being written with kb-specific
;; information. This doesn't appear to lead to trouble right now as long as
;; conflicting definitions are not set up.  Consider changing this!

;; This macro is only currently used at top level in the file GRAMMAR2.
;; A compile time use of this macro is appropriate when the declarations
;; are independant of individual knowledge bases.  -jra 2/21/91






;;; For the common case of the grammar category symbol whose slot value
;;; writer expects value to be a symbol (in the AB package), :nil, or nil, we
;;; define here a generic slot value writer, `write-symbol-from-slot'.  This
;;; is to be used with def-slot-value-writer-as-existing-function to define
;;; slot value writers.  This should not be used if NONE the symbol must be
;;; distinguished from NIL (to mean what's called nil in Lisp), since they
;;; are both written identically, and thus cannot be distinguished when written
;;; by this function.  This writes symbol in upper or lower case, according to
;;; write-symbols-in-lower-case?, which is lowercase by default and by
;;; convention.

(defun write-symbol-from-slot (symbol frame)
  (declare (ignore frame))
  (twrite-symbol (or symbol 'none)))

(defun write-expression-from-slot (expression frame)
  (declare (ignore frame))
  (write-expression (or expression 'none)))

;; obsolete!
;(defun write-symbol-or-none-in-lowercase-from-slot (value frame)
;  (declare (ignore frame))
;  (twrite-symbol (or value 'none)))


;; ;;; Similarly, we define `write-symbol-in-lowercase-from-slot', which does not
;; ;;; handle the case where value is NIL by writing it as "none"; instead, NIL
;; ;;; would simply be written as nil.
;;
;; (defun write-symbol-in-lowercase-from-slot (value frame)
;;    (declare (ignore frame))
;;    (twrite-symbol value))
;;
;; -- not needed -- type in nil & you get :nil.  

;; Write-symbol-from-slot will properly write :NIL as "nil", and nil as "none".
;; As written, the reader cannot then distinguish NONE the symbol from NONE
;; meaning nil, but that's not the writer's problem; NONE is a reserved word,
;; so it usually cannot be a problem, but if that is a problem, this should not
;; be used.  (MHD 3/8/91)







;;; `Write-slot-value' invokes the slot value writer for grammar-category-symbol to
;;; write slot-value, the value of a slot in a frame.  Such a slot writer must exist.
;;; Special variables write-symbols-in-lower-case? and write-symbols-parsably? are
;;; bound to true around the invocation.  Frame? should be specified unless it is
;;; known that the slot value writer definition does not specify a frame variable
;;; by means of which it can refer to the frame containing the slot.

(def-substitution-macro write-slot-value (grammar-category-symbol slot-value frame?)
  (let ((slot-value-writer? (slot-value-writer grammar-category-symbol)))
    (if slot-value-writer?
	(let ((write-symbols-in-lower-case? t)
	      (write-symbols-parsably? t))
	  (funcall-simple-compiled-function slot-value-writer? slot-value frame?))
	#+development
	(tformat "~S [slot value writer missing for type ~A]"
		 slot-value grammar-category-symbol)
	#-development
	(twrite "[deleted attribute]")
	)))

;; Update-representations... does not deal with the case where an existing table has
;; different rows than are appropriate for an item that has gained or lost attributes.
;; The last line above is a cosmetic fix. 2/7/90 ML.






;;; Text-slot-value-p ... true if slot-value is (translation . text) as opposed
;;; to nil or, possibly, some other nonstandard value for a text slot.  If
;;; slot-value is a cons whose cdr is a cons, then (text-slot-value-p slot-value)
;;; returns true.

(def-substitution-macro text-slot-value-p (slot-value)
  (and slot-value
       (consp slot-value)
       (consp (cdr slot-value))))





;;; `Make-text-representation-for-slot-value' returns a brand-new text
;;; representation for the value of the slot denoted by slot-name and
;;; class-qualifier? in frame.
;;;
;;; If the slot is a text slot, and its value is text-slot-value-p, a copy is made of
;;; the text therefrom; otherwise, if there is a slot value writer for the grammar
;;; category specified by the type of the slot, it is invoked to write the text;
;;; otherwise, a new empty text is made.  For example, to save space the slot
;;; condition-for-using-user-menu-choice? of the class user-menu-choice has nil as
;;; its initial value and (type user-menu-choice-expression text) as its type
;;; specification.  There is a slot value writer defined for
;;; user-menu-choice-expression which can be expected to be called (only) when the
;;; slot's value is nil.  In that case, it simply writes "none".  When the slot's value
;;; is non-nil, it could only be a text slot value, i.e., of the form
;;; (TRANSLATION . TEXT), and so in that case, TEXT is copied and returned by
;;; make-text-representation-for-slot-value.

;;; If the slot is not a text slot, the slot value writer for the grammar
;;; category specified by the type of the slot is invoked to write the text.
;;; The TYPE feature for the slot is taken from the slot.  The type must exist
;;; and should not be (TYPE NIL).

;;; After make-text-representation-for-slot-value has been invoked, the value of
;;; special variable leave-text-representation-as-a-single-line?  may be relevant;
;;; see def-slot-value-writer.

;;; `Make-text-representation-for-slot-value-itself' is similar but takes the
;;; slot value instead of the slot name, requires type-of-slot, and req.

(defun make-text-representation-for-slot-value
    (frame pretty-slot-name &optional class-qualifier?)
  (let ((slot-description
	  (get-slot-description-of-frame
	    pretty-slot-name frame class-qualifier?)))
    (make-text-representation-for-slot-value-itself
      frame
      (get-slot-description-value frame slot-description)
      (feature-assq 'type (slot-features slot-description)))))

;; Above spec for the text slot case was revised by MHD, 3/7/91.  -- Again -- no
;; longer takes the type, since it becomes almost redundant with the function
;; below. And fixed callers.  (MHD 2/15/94)
;; 
;;
;; At present, it is just relied upon for the user-menu-choice slot described
;; above.
;;
;; The new feature should now be used to fix slots like the formula? slot of
;; variables, which default to nil but allow NONE, and without this feature show
;; up as blank text when their value is nil.
;;
;; It should also now be used to save a bit more space in stripped texts.  In these
;; cases, the slot could be written as (translation . nil), and then the slot writers
;; could just write "...." for them.  This would currently save on the text stored
;; now to represent stipped text, which is
;;   ((lost-spaces . 0) "....")
;; or about three conses and string of length 4.
;;
;; Another place to go from here is to turn certain "simple" text slot values typed
;; in by the user into non-text slot values to save space.  An easy example is
;; when a user types in NONE, you can turn the whole slot value back into nil.
;; But also this could be done for a subset of the range of values for expression
;; slots, like the expression-to-display slot of a readout.  Here, you could
;; eliminate the text if it's easy to regenerate it just from the compilation
;; result: e.g., when the expression is just a number or the name of an item.
;;
;; Perhaps, this could be used to "clean up" the embedded rule facility.  Not sure.
;;
;; (MHD 3/7/91)

;;; Make-text-string-representation-for-slot-value ...

#+unused
(defun make-text-string-representation-for-slot-value
    (frame pretty-slot-name class-qualifier?)
  (let ((slot-description
	  (get-slot-description-of-frame
	    pretty-slot-name frame class-qualifier?)))
    (make-text-string-representation-for-slot-description-value
      frame slot-description)))

#+unused
(defun make-text-string-representation-for-slot-description-value
       (frame slot-description)
  (make-text-string-representation-for-slot-value-itself
    frame
    (get-slot-description-value frame slot-description)
    (feature-assq 'type (slot-features slot-description))))


(defun make-text-representation-for-slot-description-value
    (frame slot-description)
  (make-text-representation-for-slot-value-itself
    frame
    (get-slot-description-value frame slot-description)
    (feature-assq 'type (slot-features slot-description))))

(defun make-text-string-representation-for-slot-value-itself
       (frame slot-value type-of-slot)
  (make-text-or-text-string-representation-for-slot-value-itself
    frame slot-value type-of-slot nil))

(defun make-text-representation-for-slot-value-itself
       (frame slot-value type-of-slot)
  (make-text-or-text-string-representation-for-slot-value-itself
    frame slot-value type-of-slot t))

(defun make-text-or-text-string-representation-for-slot-value-itself
       (frame slot-value type-of-slot text-case?)
  (or (if (text-slot-type-p type-of-slot)
	  (if (text-slot-value-p slot-value)
	      (if text-case?
		  (copy-text (cdr slot-value))
		  (convert-text-to-text-string (cdr slot-value)))
	      (if (null (slot-value-writer
			  (category-symbol-given-slot-type type-of-slot)))
		  (if text-case?
		      (make-empty-text)
		      (obtain-simple-text-string 0)))))
      (if text-case?
	  (write-slot-value-to-text frame slot-value type-of-slot)
	  (write-slot-value-to-string frame slot-value type-of-slot))))

;;; GENSYMCID-1535: Float to text default format and default precision
;;;
;;; NOTE: special binding of (default-float-to-text-format 'default) for
;;; the following two functions has been removed, to allow users to see
;;; the full value from attribute displays. The actual format will be
;;; finally set to (float-to-text-default-format-from-system-table), by
;;; function `write-floating-point-number-simple-c-format'.
;;; -- Chun Tian (binghe), Nov 2, 2015.

(defun write-slot-value-to-string (frame slot-value type-of-slot)
  (let () ; old: ((default-float-to-text-format 'default))
    (twith-output-to-text-string
      (write-slot-value
        (category-symbol-given-slot-type type-of-slot)
        slot-value frame))))

(defun write-slot-value-to-text (frame slot-value type-of-slot)
  (let () ; old: ((default-float-to-text-format 'default))
    (twith-output-to-text
      (write-slot-value
        (category-symbol-given-slot-type type-of-slot)
        slot-value frame))))
;; This is not (yet) the full cross product of all the combinations of arguments
;; and desired results, e.g. of text vs. text-string result and slot-name
;; argument vs. slot-description argument.  Add more as necessary.  Also,
;; documentation should be added -- will await a request for now, to save time!
;; (MHD 1/24/96)







;;;; Frames



;;; A `frame' typically belongs to a knowledge base.  In fact, a knowledge base consists
;;; almost exclusively of frames and structures held in slots of frames.

;(def-class (kb-frame root define-predicate)

;;  (frame-flags 0 system vector-slot (type nil))	;moved to root

;  (frame-status-and-notes			; a frame status or a list of the form
;    nil system vector-slot			;   (frame-status . frame-note-plist)
;    (type frame-status-and-notes) save do-not-clone
;    not-user-editable)

;  (frame-author-or-authors 			; a symbol or a list of symbols or nil
;    nil system lookup-slot (type nil)		; (type name-or-names) later!
;    do-not-clone)

;  (frame-representations			; a list of tables (and other things?)
;    nil system vector-slot save)

;  (original-kb-state-plist			; a plist of kb state variables and their
;    nil system lookup-slot)			;   original values; see custom 
;						;   reclaimer defined below
;  (user-restrictions nil system lookup-slot (type user-restrictions))

;  )

;; Have class kb-frame be equivalent to class root (though animated areas, certain tables,
;; etc. don't need authors or timestamps)!

;; Consider having frame-status-and-notes be a lookup slot.

;; Rename "frame-representations" to "table-representations", since it is now
;; only used for that purpose (in modules FRAMES4, FRAMES5, TABLES, and EDIT)!

;; Consider adding a frame-documentation slot here.


;;; The `slot putter for original-kb-state-plist', when called when cloning,
;;; i.e., not when loading in a KB, will remove the position information, which
;;; should not be cloned.  If, after this is done, there is still a non-nil
;;; value, it calls note-as-frame-with-kb-state-changes to register this block
;;; as one with KB state changes.
;;;
;;; Note that the cleanup method for block handles the removal of the
;;; registration done by note-as-frame-with-kb-state-changes, and that the
;;; default reclamation of the slot value (i.e., reclaim-slot-value) is done to
;;; reclaim the value of this slot when block is deleted.

(def-slot-putter original-kb-state-plist (block value initializing?)
  (when (and initializing? value (not loading-kb-p))
    (when (or (getf value 'item-position) (getf value 'icon-position))
      (setq value
	    (prog1
		(loop for (indicator value) in value by 'cddr
		      unless (or (eq indicator 'item-position)
				 (eq indicator 'icon-position))
			nconc (slot-value-list indicator value))
	      (reclaim-slot-value-list value)))))
  (when value
    (note-as-frame-with-kb-state-changes block))
  (setf (original-kb-state-plist block) value))



;;; The slot kb-state-changes-previous-cons? is either nil or a cons shared with
;;; a cons in kb-state-changes, so no reclamation should be done.
;;;
;;; Note this slot is not to be cloned or saved in KBs, and it uses the
;;; declarations do-not-save and do-not-clone in the slot definition to achieve
;;; these requirements.  (Unfortunately, there is no declaration such as
;;; do-not-reclaim.) The slot putter just serves to prevent reclamation of a
;;; cons that may be the value of this slot.
;;;
;;; The slot-value reclaimer for this slot just does nothing, also just to prevent
;;; reclamation of this cons.


(def-slot-value-reclaimer kb-state-changes-previous-cons? (value)
  (declare (ignore value))
  nil)

(def-slot-putter kb-state-changes-previous-cons? (block value)
  (values (setf (kb-state-changes-previous-cons? block) value)
	  t))  ; second value true => do not reclaim





;;; `Reclaim-menus-for-this-value', the slot value reclaimer for the menus-for-this
;;; slot of a block, expects value to be a slot value list, possibly empty, of
;;; menus for frame.

;;; Note that this maintains the constraint that deleted frames are never
;;; present in the what-this-is-a-menu-for slot of a menu, and does so by
;;; working in close collaboration with that slot's reclaimer.

(def-slot-value-reclaimer menus-for-this (value frame)
  (loop for menu in value
	do (set-slot-value			; slot accessor forward ref.!
	     menu 'what-this-is-a-menu-for? nil); prevent circular reclamation
	   (delete-menu menu))
  (when (consp value)
    (reclaim-slot-value-list value))
  (setf (menus-for-this frame) nil))







;;;; Dependent Frames





;;; Dependent frames are frames having a lower overhead in size, creation
;;; time and deletion time than blocks.   They are slot values. 

;;; Class Hierarchy: All frames are kb-frames. These are bifurcated into 
;;; blocks and dependent-frames. Do not create any other 
;;; subclass of kb-frame or root.

;;; Non-supported features:
;;;    The following slots do not exist for dependent-frames.
;;;       frame-serial-number
;;;       frame-flags
;;;       frame-status-and-notes
;;;       frame-author-or-authors
;;;       frame-representations
;;;       original-kb-state-plist
;;;       user-restrictions

;;;  The following will always be valid:
;;;       class, framep, frame-of-class-p, of-class-p, make-frame and
;;;       delete-frame. (But see note on delete-frame.)

;;; Subclasses of dependent-frame may be defined using def-class. There are
;;; no user defined or user visible subclasses.

;;; Class-description-slot and lookup-structure should always be regarded as
;;; internals.

;;; Registration and iteration: Dependent frames are not registered as
;;; instances of their class. There is no way to iterate over instances of
;;; class of dependent frames. The highest level class over which one may
;;; iterate instances is now 'block.

;;; The KB saving requires that it reach a dependent frame only once.  No
;;; support is provided for handling a second savable reference.  I.e.  a
;;; dependent frame must be referenced exactly once within a savable
;;; structure: a slot of a kb-frame or within a slot value.

;;; Just like any saved slot value, dependent frames are owned by one
;;; and only one block.  Warm boot requires that when modifications are
;;; being made to a dependent frame current-block-of-dependent-frame
;;; must be bound approprately.

;;; Copy-for-slot-value will copy dependent frames using the copy-frame
;;; method for the dependent frames of that class. It is an error to use
;;; copy-for-slot-value on a dependent frame without having provided such a
;;; method. See documentation for copy-for-slot-value.

;;; Reclaim-slot-value will reclaim any dependent frame that it encounters.
;;; Delete frame for any block must delete all its dependent frames. If the
;;; cleaning up of a slot containing dependent frames is done by any means 
;;; other than reclaim-slot-value, it is your responsibility to see that
;;; dereferencing and deleting are done correctly. This has to work even for
;;; clearing a KB since there is no iteration over dependent frames. Note that
;;; if there is a tree of dependent frames in a slot of a block, and the tree
;;; depth > 1, you must make some provision for deleting the sub-frames, since
;;; it will not happen automatically. 

;;; Pointers to dependent frames, other than those in the saving hierarchy must
;;; consider these rules.
;;;   (1) The pointer must not be savable.
;;;   (2) The pointer must not be cloned.
;;;   (3) The pointer must not be reclaimed.

;;; Maintaining KBs: def-substitute-for-class and def-absent-slot-putter may
;;; be used for dependent frames as for other frames.

;;; Frame methods work for dependent frames as for other frames.

;;; Do not use (:funcall ...) as a slot-init-value. (If this is badly
;;; needed, we can relax this, but I'm trying to keep them as cheap as possible.)

(def-class (dependent-frame kb-frame))



;;; `Copy-frame' is a class method defined for all subclasses of dependent-frame
;;; it should copy the dependent frame along with any of it's substructure.  Additional
;;; discussion may be found in the documentation for copy-for-slot-value above.

(def-generic-method copy-frame (dependent-frame))



;;; As a debugging aid, a copy-frame method on dependent frame signals an error
;;; in development to flag the lack of a dependent frame method.

#+development
(def-class-method copy-frame (dependent-frame)
  (error "No copy-frame method was defined for the dependent frames ~S" (class dependent-frame)))

;; It strikes me that it would be more useful to have the default method be
;;    (def-class-method copy-frame (dependent-frame) (clone-frame dependent-frame))
;; Most subclasses do this at some point, so they would use call superior
;; method.  I don't know why this wasn't chosen originally.  (MHD 12/8/93)




;;;; Blocks




;;; A `block' is a frame that has a rectangular graphic representation, the
;;; `rectangle' for the block.  A block may have a `superblock' and any number of
;;; `subblocks'.  The subblocks of a block are ordered and will not be arbitrarily
;;; reordered.

;;; A block only becomes visible as part of an "image" of the workspace (see
;;; below) it belongs to, if any.  There may be any number of such images of
;;; this workspace, at different scales and showing different levels of detail.
;;; (See "Gensym Window Geometry".)

;;; The left, top, right, and bottom edges of a block are integers in the
;;; coordinate system of the workspace containing the block, and are such that
;;; left-edge is less than or equal to right-edge and top-edge is less than or
;;; equal to bottom-edge.  The width of a block is given by (right-edge -
;;; left-edge) and the height by (bottom-edge - top-edge).  When the edges of a
;;; block are mapped into a window coordinate system, point (left-edge,
;;; top-edge) maps into the upper left-hand corner pixel, and point (right-edge
;;; - 1, top-edge - 1) maps into the lower right-hand pixel.  Viewed in this
;;; way, the edges of a block are treated asymmetrically.  The edges of a new
;;; block are initially zero.

;;; Note that icon representations of entities can overflow the right and bottom
;;; edges of the window area they map into by one pixel.  Also, certain types of
;;; blocks can have subblocks that are not entirely within (confined to) the
;;; block's rectangle.  But other types of blocks, e.g., text boxes (other than
;;; edit boxes) and tables, are such that they are always drawn entirely within
;;; their rectangles.

;;; Name-for-debugging, when non-nil, is a temporary name for a block that did
;;; not have a name-or-names-for-frame name when a name was needed for a user
;;; notification.  It is not to be saved in a kb.  It is either NIL, a string,
;;; or a cons whose car is a string.  The functions Get-or-make-up-designation-
;;; for-block and get-cached-name-for-block in tables are responsible for
;;; setting and getting user visible designations from this slot.

;;; Superblock? links are not explicitly saved in a saved kb, but instead are
;;; reconstructed from subblock links (which are saved specifically, not as
;;; subblocks slot values).

;(def-class (block kb-frame define-predicate)

;  (superblock? nil system vector-slot do-not-clone)
;  (subblocks nil system vector-slot save)	; each subblock has this block as its superblock

;  (left-edge-of-block 0 system vector-slot)
;  (top-edge-of-block 0 system vector-slot)
;  (right-edge-of-block 0 system vector-slot)
;  (bottom-edge-of-block 0 system vector-slot)

;  (connections nil system vector-slot save)	; ({{connection-name} connection})

;  (name-or-names-for-frame			; symbol or list of symbols
;    nil vector-slot system (type name-or-names) do-not-clone)

;  (name-for-debugging nil system lookup-slot)
;  (tracing-and-breakpoints nil system lookup-slot save (type nil))

;  (parent-frame nil system vector-slot)	 ; nil or a frame with this frame as an attribute value
;  (parent-attribute-name nil system vector-slot)	    ; the attribute in question

;;  (menu-items nil system lookup-slot)		; might be needed later

;  ;; Used to cache role values.
;  (role-cache nil system vector-slot)
;  (relation-instances nil system vector-slot)	
;  ;; used to access the lists that this is a member of.  See the file lists.
;  (list-elements-for-item nil system lookup-slot)
;  (cell-array nil system lookup-slot)
;  )

;; Rename the connections slot "connections-and-names", and document it!

;; Consider "demoting" this slot to the entity level until, if ever, connections between
;; other classes of blocks come into use.  If this is done, revise determine-extreme-edges-
;; of-elements appropriately.

;; Consider having subblocks and name-or-names-for-frame be lookup slots.

;; See add-subblock and remove-as-subblock-if-necessary in module DRAW.



;;; `Width-of-block' computes the width of block by subtracting the left edge from
;;; the right edge.  `Height-of-block' computes the height of block by subtracting
;;; the top edge from the bottom edge.

(def-substitution-macro width-of-block (block)
  (-w (right-edge-of-block block) (left-edge-of-block block)))

(def-substitution-macro height-of-block (block)
  (-w (bottom-edge-of-block block) (top-edge-of-block block)))

#+unused
(defun width-of-block-function (block)
  (width-of-block block))



;;; `Vertical-midline-of-block' ...
;;; `Horizontal-midline-of-block' ...

(def-substitution-macro vertical-midline-of-block (block)
  (halfw (+w (left-edge-of-block block) (right-edge-of-block block))))

(def-substitution-macro horizontal-midline-of-block (block)
  (halfw (+w (top-edge-of-block block) (bottom-edge-of-block block))))

;; The following were defined today.  Although I have not made use of them
;; in non-development code, I am quite sure there are many potential customers.
;; (MHD 5/23/91)

(def-substitution-macro midline-x-of-block (block)
  (vertical-midline-of-block block))

(def-substitution-macro midline-y-of-block (block)
  (horizontal-midline-of-block block))

;; These are the same, but seem a bit easier to use in that the x/y in the names
;; help you keep the x/y orientation straight! (MHD 5/22/02)

(defun midline-x-of-block-function (block)
  (vertical-midline-of-block block))

(defun midline-y-of-block-function (block)
  (horizontal-midline-of-block block))



;;; `Delete-subblocks-of-class' ...

;;; `Delete-subblocks-not-of-class' ...

(defun delete-subblocks-of-class (block class-or-classes)
  (delete-subblocks-based-on-class block class-or-classes nil))

(defun delete-subblocks-not-of-class (block class-or-classes)
  (delete-subblocks-based-on-class block class-or-classes t))

(defun delete-subblocks-based-on-class
       (block class-or-classes not-of-class-case?)
  (loop with frame-reference-serial-number = (copy-frame-serial-number (current-frame-serial-number))
	with class? = (if (atom class-or-classes) class-or-classes)
	for subblock being each subblock of block
	when (if (if class? 
		     (frame-of-class-p subblock class?)
		     (loop for class in class-or-classes
			   thereis (frame-of-class-p subblock class)))
		 (not not-of-class-case?)
		 not-of-class-case?)
	  collect subblock into subblocks-to-delete using gensym-cons-macro
	finally
	  (when subblocks-to-delete
	    (delete-frame			; first can't have been deleted
	      (car subblocks-to-delete))
	    (when (cdr subblocks-to-delete)
	      (loop for subblock-to-delete in (cdr subblocks-to-delete)
		    unless (frame-has-been-reprocessed-p
			     subblock-to-delete
			     frame-reference-serial-number)
		      do (delete-frame subblock-to-delete)))
	    (reclaim-gensym-list subblocks-to-delete))
	(reclaim-frame-serial-number frame-reference-serial-number)))

;; The thing that makes this complicated is that deleting one subblock can
;; delete other subblocks as a side effect.  (MHD 5/29/91)

(defun reclaim-subblocks-value (superblock)
  (let ((subblocks (subblocks superblock)))
    ;; The following two forms are needed to cut off bidirectional pointers
    ;; between subblocks & superblock -- this is because this function
    ;; is savvy to the fact that calling delete-frame below on subblocks
    ;; would otherwise follow pointers back to this function, which would
    ;; be bad.
    (cond
      ((and (frame-of-class-p superblock 'kb-workspace)
	    models-used-p)
       (loop for subblock being each subblock of superblock do
	 (setf (superblock? subblock) nil)
	 (when (frame-of-class-p subblock 'model-definition)
	   (install-item-in-model-if-appropriate superblock nil t))))
      (t
       (loop for subblock being each subblock of superblock do
	 (setf (superblock? subblock) nil))))
    (loop with reference-serial-number = (copy-frame-serial-number (current-frame-serial-number))
	  for subblock being each subblock of superblock
	  when (frame-has-not-been-reprocessed-p subblock reference-serial-number)
	    do (delete-frame subblock)
	  finally (reclaim-frame-serial-number reference-serial-number))
    #-subblocks-v2
    (reclaim-slot-value-list subblocks)
    #+subblocks-v2
    (when subblocks
      (reclaim-constant-queue subblocks))
    (setf (subblocks superblock) nil)))

(declare-forward-reference reclaim-connections-value function)

(def-slot-value-reclaimer slot-group-for-block? (slot-group-for-block? block)
  (when slot-group-for-block?
    (reclaim-subblocks-value block)
    (reclaim-connections-value block)
    (reclaim-icon-slot-group slot-group-for-block?))
  (setf (slot-group-for-block? block) nil))

;; There should not be a slot value reclaimer for superblock?, since
;; delete-frame will handle that slot explicitly.







;;; Legal-shift-in-workspace-coordinates-for-block-p ... 

(def-substitution-macro legal-shift-in-workspace-coordinates-for-block-p
  (block delta-x delta-y)
  (and
    ;; are the inputs within legal coordinates?
    (fixnump delta-x)
    (fixnump delta-y)
    (<=w (twicew most-negative-workspace-coordinate) delta-x (twicew most-positive-workspace-coordinate))
    (<=w (twicew most-negative-workspace-coordinate) delta-y (twicew most-positive-workspace-coordinate))
    ;; Now is our result within legal coordinates?  (Note that we assume that
    ;; the block's coordinate's are in legal workspace coordinates.)
    (<=w most-negative-workspace-coordinate (+w (left-edge-of-block block) delta-x))
    (<=w (+w (right-edge-of-block block) delta-x) most-positive-workspace-coordinate)
    (<=w most-negative-workspace-coordinate (+w (top-edge-of-block block) delta-y))
    (<=w (+w (bottom-edge-of-block block) delta-y) most-positive-workspace-coordinate)))

;; Consider implementing legal-workspace-coordinates-for-block-p some day, which
;; takes absolute left-edge-for-block and top-edge-for-block arguments. 

;; New macro added today.  Only used in development so far by shift method for
;; block. (MHD/BAH 3/19/92)





;;; `Shift' is a method on blocks, taking the block and a delta in the x and y
;;; dimensions it moves the block.  The prefered interface to this is 
;;; the shift-block function.  A method is defined for block, calling it via
;;; funcall superior method typically a good practice.

(def-generic-method shift (block delta-x delta-y))



;;; `Shift-block' shifts block by (delta-x-in-workspace, delta-y-in-workspace).

(defun shift-block (block delta-x-in-workspace delta-y-in-workspace)
  (funcall-method 'shift block delta-x-in-workspace delta-y-in-workspace))

;; Use this in place of direct funcall-method calls!

;; Implement similar abstractions of other method calls, maybe in terms of
;; something like "def-operation"!





;;; `Shift-block-to' shifts block to the specified position. 

(defun shift-block-to (block x-in-workspace y-in-workspace)
  (shift-block
    block
    (-w x-in-workspace (left-edge-of-block block))
    (-w y-in-workspace (top-edge-of-block block))))





;; This is the generic `shift method' for blocks. There is another method on tables.

(def-class-method shift (block delta-x delta-y)
  #+development
  (unless (legal-shift-in-workspace-coordinates-for-block-p
	    block delta-x delta-y)
    (cerror "Continue (in error!)"
	    "Illegal delta-x/delta-y (~d/~d) specified!"
	    delta-x delta-y))

  (let ((new-left? nil)
	(new-top? nil)
	(new-right? nil)
	(new-bottom? nil))
    (unless (=w delta-x 0)
      (setq new-left? (+w (left-edge-of-block block) delta-x)
	    new-right? (+w (right-edge-of-block block) delta-x)))
    (unless (=w delta-y 0)
      (setq new-top? (+w (top-edge-of-block block) delta-y)
	    new-bottom? (+w (bottom-edge-of-block block) delta-y)))

    (change-edges-of-block block new-left? new-top? new-right? new-bottom?))
   ; (send-representations-item-moved block delta-x delta-y))
  
  (loop for subblock being each subblock of block
	do (funcall-method 'shift subblock delta-x delta-y)))



;;; `Draw-images-of-block' is equivalent to the draw case of
;;; update-images-of-block.  (It is NOT a "draw function or macro", in the sense
;;; of module DRAW, since it may update any number of image planes.)

(defmacro draw-images-of-block (block confine-updating-to-block-rectangle?)
  `(update-images-of-block ,block nil ,confine-updating-to-block-rectangle?))



;;; `Erase-images-of-block' is equivalent to the erase case of
;;; update-images-of-block.  (It is NOT a "draw function or macro", in the sense
;;; of module DRAW, since it may update any number of image planes.)

(defmacro erase-images-of-block (block confine-updating-to-block-rectangle?)
  `(update-images-of-block ,block t ,confine-updating-to-block-rectangle?))



(def-substitution-macro block-inside-rectangle-p
			(block left-edge-in-workspace top-edge-in-workspace
			       right-edge-in-workspace bottom-edge-in-workspace)
  (and (>=w (left-edge-of-block block) left-edge-in-workspace)
       (>=w (top-edge-of-block block) top-edge-in-workspace)
       (<=w (right-edge-of-block block) right-edge-in-workspace)
       (<=w (bottom-edge-of-block block) bottom-edge-in-workspace)))



(def-substitution-macro block-inside-p (block-1 block-2)
  (block-inside-rectangle-p
    block-1
    (left-edge-of-block block-2) (top-edge-of-block block-2)
    (right-edge-of-block block-2) (bottom-edge-of-block block-2)))




(def-substitution-macro block-overlaps-rectangle-p
  (block left-edge-in-workspace top-edge-in-workspace
	 right-edge-in-workspace bottom-edge-in-workspace)
  (and (<w (maxw left-edge-in-workspace (left-edge-of-block block))
	   (minw right-edge-in-workspace (right-edge-of-block block)))
       (<w (maxw top-edge-in-workspace (top-edge-of-block block))
	   (minw bottom-edge-in-workspace (bottom-edge-of-block block)))))




(def-substitution-macro block-or-subblocks-overlap-rectangle-p
  (block left-edge-in-workspace top-edge-in-workspace
	 right-edge-in-workspace bottom-edge-in-workspace)
  (multiple-value-bind (extreme-left-edge extreme-top-edge
			extreme-right-edge extreme-bottom-edge)
      (determine-extreme-edges-of-block block)
    (and (<w (maxw left-edge-in-workspace extreme-left-edge)
	     (minw right-edge-in-workspace extreme-right-edge))
	 (<w (maxw top-edge-in-workspace extreme-top-edge)
	     (minw bottom-edge-in-workspace extreme-bottom-edge)))))



;; Blocks-overlap-p ...

;(def-substitution-macro blocks-overlap-p (block-1 block-2)
;  (block-overlaps-rectangle-p
;    block-1
;    (left-edge-of-block block-2) (top-edge-of-block block-2)
;    (right-edge-of-block block-2) (bottom-edge-of-block block-2)))








;;;; Workspaces and Opaque Blocks



;;; A `workspace' is a block of class workspace with no superblock that is
;;; intended to contain subblocks and their connections.  Every subblock or
;;; connection (at any level) in a workspace must be entirely contained
;;; within the workspace rectangle, with at least workspace-margin to spare.
;;; Every workspace has (defines) its own `workspace coordinate system', the
;;; (0,0) point of which is its `workspace origin'.

;;; An `opaque block' is a subblock of a workspace which, when drawn, can
;;; obscure other blocks and connections on the workspace.  A block is
;;; distinguished as such by means of the opaque-block frame flag (though
;;; that flag may also be set in a block with no superblock, so that it will
;;; become an opaque block when added to a workspace).

;; This comment is obsolete: An opaque block must be included in both the
;; subblocks and the stack of subblocks of the workspace.  (Add-subblock will
;; push a block whose opaque-block frame flag is set onto the stack of
;; subblocks, and remove-as-subblock-if-necessary will correspondingly remove
;; it.)

;;; An opaque block must be drawn so as to obscure anything later in the
;;; stack or not on the stack, and the drawing of the opaque block and its
;;; subblocks must be confined to the block rectangle.  An opaque block is
;;; "added" by painting its entire rectangle; this may be done by first
;;; painting a background and then adding or painting upon that, though
;;; anything that is to be separately erasable must be "added" to the
;;; background.  An opaque block is "subtracted" (erased) by doing nothing
;;; beyond cleaning up the graphic element memory, and then expecting
;;; update-images (q.v.) to refresh the rectangle.

;;; A non-opaque subblock of a workspace behaves somewhat like a
;;; transparency, except that the non-transparent parts are typically
;;; "added" (and "subtracted") by "xor"ing.  A non-opaque block is occluded
;;; by every opaque block, if any, that intersects it.

;; Consider allowing a subblock to be opaque even though it is not a subblock
;; of a workspace, requiring only that an appropriate (and not necessarily
;; opaque) workspace subblock be included in the stack of subblocks for the
;; workspace.  The workspace subblock would then be partially opaque and
;; partially transparent.  If this were done, many things, including
;; add-subblock, would have to be revised.

;; Consider allowing an opaque block to have subblocks that are drawn outside
;; of the opaque block's rectangle.

;; Consider having workspace units be hundredths of an inch or centimeter.

(def-class (workspace block define-predicate)

  (image-planes-this-is-on nil system vector-slot)

  (workspace-margin			; margin to maintain along edges
    30 system vector-slot
    (type non-negative-integer))	; type changed positive- => non-negative-
					; for 3.0 (MHD 10/18/91)

  (parent-of-subworkspace?		; an entity or nil; see module ENTITIES
    nil system vector-slot save do-not-clone)

  (plist-of-remembered-window-positions-and-scales  ; see module PANES
    nil system vector-slot save)	; save new. (MHD 6/21/89)

  (number-of-opaque-blocks-on-workspace	; Used to optimize drawing in some cases.
    0 system vector-slot)
  (number-of-blocks-on-workspace	; Helps determine when indexing is needed.
    0 system lookup-slot)

  (workspace-background-color?		; defaults to
    nil system vector-slot save)	;   workspace-area-background-color?
  (workspace-foreground-color?		; defaults to
    nil system vector-slot save)	;   workspace-area-foreground-color?

  ;; The KB-level pending drawing info.  Seemed to be worth vector slots.
  (invalid-region-of-workspace?		; NIL or a workspace-region object, includes bleeding.
    nil system vector-slot)
  (changed-blocks-of-workspace		; List of blocks with non-NIL block-changes.
    nil system vector-slot)
  

  ;; Slots related to the spacial index.
  
  (workspace-spacial-index?		; An index of block&connection positions.
    nil system lookup-slot)
  (workspace-connections-which-need-indexing ; List of connections whose edges have changed somehow.
    nil system lookup-slot)
  (workspace-layer-positions-are-valid-p ; Whether cached layer positions need updating.
    nil system lookup-slot)

  

  ;; New slots which used to be part of the object configuration.
  (background-images nil (type background-images)) ; A list of (image-name x y).
  (frame-style nil (type frame-style-name?))
  (title-bar-caption-text		; a text or nil; shown if non-nil
    nil system (type text) do-not-put-in-attribute-tables)
  (stretch-new-image-planes-for-caption-p
    nil system (type yes-or-no) do-not-put-in-attribute-tables)
  (title-bar-text
    nil system (type workspace-title-bar-text))
  
  ;; Info about last images displayed. See refresh-background-images.
  (workspace-previous-background-images-info nil)


  (workspace-geometry-tick		; Incremented whenever ws or subblocks change shape.
    0 system vector-slot)
  
  (view-preferences nil lookup-slot system save (type view-preferences))
  (unused-area-color? nil lookup-slot system save)

  ;; Moved the prefer-buffered-drawing slot up to workspace from KB-workspace
  ;; for 8.1. (MHD 1/30/05)
  (prefer-buffered-drawing nil lookup-slot system save (type yes-or-no))
  
  ;; Moved the proprietary-package slot up to workspace from KB-workspace for
  ;; 8.1, to allow proprietary restrictions on system-managed non-kb-workspace
  ;; instances, e.g., G2GL-execution-display. (MHD 4/8/05)
  (proprietary-package
    nil vector-slot system (type proprietary-package)
    (attribute-export-comment "Proprietary package exports as a symbol type: ~
(member (proprietary non-proprietary potentially-proprietary)). However ~
the slot is only visible when package-preparation mode is on. The ~
user may change the value only from non-proprietary to potentially-proprietary, ~
and only when package-preparation mode is on, Some special-casing would be ~
necessary to conditionally export this attribute. ")))


;; Added do-not-clone feature for stack-of-subblocks and
;; parent-of-subworkspace?  These allow us to remove the special-case code
;; that inhibits their cloning in clone-frame.  (MHD 4/14/94)

(defun reclaim-background-images-info (images-info)
  (loop for image-info in images-info
	do
    (reclaim-frame-serial-number (second image-info))
    (setf (second image-info) nil))
  (reclaim-slot-value-tree images-info))
  
(def-slot-value-reclaimer workspace-previous-background-images-info (images-info)
  (reclaim-background-images-info images-info))


;;; The slot-value-reclaimers for `changed-blocks-of-workspace' and
;;; `invalid-region-of-workspace?' maintain the
;;; `count-of-pending-workspace-drawing' cache when a workspace is deleted.

(def-slot-value-reclaimer changed-blocks-of-workspace (changed-blocks)
  (atomic-decff count-of-pending-workspace-drawing (length changed-blocks))
  (reclaim-slot-value-list changed-blocks))

(def-slot-value-reclaimer invalid-region-of-workspace? (workspace-region)
  (atomic-decff count-of-pending-workspace-drawing 1)
  (reclaim-workspace-region workspace-region))

;; The update for changed-blocks-of-workspace would normally happen
;; automatically as each subblock of the workspace is deleted, via
;; `remove-block-from-drawing-queues'.  Unfortunately, when `delete-frame'
;; deletes a workspace (or any frame with subblocks), it first, via
;; `reclaim-subblocks-value', SETFs the superblock of each subblock to NIL, and
;; then deletes the subblocks.  At this point,
;; `remove-block-from-drawing-queues' is called on the subblock, but since the
;; superblock is NIL it does nothing.  Fixes were for HQ-3742490 -fmw, 12/4/01




(def-substitution-macro workspace-has-opaque-blocks-p (workspace)
  (>f (number-of-opaque-blocks-on-workspace workspace) 0))


;;; The `cleanup' method on a workspace clears all slots which refer to names,
;;; which removes us as a user of those names.

(def-class-method cleanup (workspace)
  (funcall-superior-method workspace)
  (change-slot-value workspace 'background-images nil))




;;; The absent-slot-putter `stack-of-subblocks' throws away any list passed in.

(def-absent-slot-putter stack-of-subblocks (workspace list-of-blocks)
  (declare (ignore workspace))
  (reclaim-slot-value-list list-of-blocks)
  nil)


(def-slot-putter workspace-margin (workspace workspace-margin initializing?)
  (setf (workspace-margin workspace) workspace-margin)
  (unless initializing?
    (change-workspace-edges-after-margin-change workspace))
  workspace-margin)

;; Added slot putter to fix edges so that at least the required margin exists
;; along all sides after a change.  I did not have this be done, however, when
;; initializing, since this works by examining other slots in workspace, and
;; it is not clear that's safe to do here.  Also, this should only really need
;; to be done when the margin changes.  It is a little expensive to do also,
;; since it touches every subblock.  Note that a workspace in an old KB that
;; got its workspace margin changed may not reflect that in its margin; if you
;; wanted to depend on that, you would want to have a post-loading function
;; to ensure that.  (MHD 8/6/90)

;; I assume a dependent frame may not be edited.  A bunch of code would probably
;; break in the EDIT module if it saw a dependent frame! (MHD 9/27/93)


(def-grammar-category frame-style-name ()
  (unreserved-symbol))

(def-grammar-category frame-style-name? ()
  (frame-style-name)
  none)

(def-slot-value-compiler frame-style-name? (parse-result)
  (if (eq parse-result 'none)
      nil
      parse-result))

(define-category-evaluator-interface (frame-style-name?
				       :access read-write)
    (or (no-item) symbol)
  ((set-form (evaluation-value))
   (if evaluation-value
       evaluation-value
       'none))
  ((get-form (slot-value))
   slot-value))

(def-slot-value-writer-as-existing-function frame-style-name write-symbol-from-slot)
(def-slot-value-writer-as-existing-function frame-style-name? write-symbol-from-slot)


    
(def-absent-slot-putter non-default-background-color-for-workspace?
			(workspace color?)
  (if color? (setf (workspace-background-color? workspace) color?)))


(def-absent-slot-putter non-default-foreground-color-for-workspace?
			(workspace color?)
  (if color? (setf (workspace-foreground-color? workspace) color?)))

;; Pre-alpha slots. Added (MHD 4/7/89). And removed. (MHD 8/8/89) 







(def-substitute-for-old-class workblock workspace)	; 3/12/88

(def-absent-slot-putter workblock-margin (workspace workspace-margin)	; 3/12/88
  (setf (workspace-margin workspace) workspace-margin))



;;; A `non-kb workspace' is a workspace that will not be saved in a saved kb,
;;; except in the unlikely event that the workspace frame has a representation
;;; that is saved.  `Non-kb-workspace-p' can be used to identify a non-kb
;;; workspace.

(def-class (non-kb-workspace workspace define-predicate)
  (only-workstation-this-non-kb-workspace-can-be-on?	; nil or a workstation
    nil system vector-slot))				;   pointing back here



(def-slot-value-reclaimer only-workstation-this-non-kb-workspace-can-be-on?
    (workstation? non-kb-workspace)
  (when workstation?
    (setf (non-kb-workspaces-for-this-workstation-only workstation?)
	  (delete-gensym-element
	    non-kb-workspace
	    (non-kb-workspaces-for-this-workstation-only workstation?)))))



;;; Workspace-can-appear-on-workstation-p is true if workspace, which can be any
;;; kind of a workspace, is not a non-kb workspace specific to some workstation
;;; other than workstation (the arg).

(defun workspace-can-appear-on-workstation-p (workspace workstation)
  (or (not (frame-of-class-p workspace 'non-kb-workspace))
      (null (only-workstation-this-non-kb-workspace-can-be-on?
	      workspace))
      (eq (only-workstation-this-non-kb-workspace-can-be-on?
	    workspace)
	  workstation)))

;; Consider eliminating "can-be-on", "for-", "only-", et al, and just defining
;; and consistently using "specific-to" here.







;;; A `temporary workspace' is a non-kb workspace that gets automatically
;;; deleted when either (a) it is removed from the only image plane it is on or
;;; (b) its only subblock is removed.  (When a temporary workspace gets
;;; automatically deleted, not only will each of its subblocks be deleted to all
;;; levels, but any "command statement" represented exclusively by a table being
;;; deleted will be deleted also.)  `Temporary-workspace-p' can be used to
;;; identify a temporary workspace.

(def-class (temporary-workspace non-kb-workspace define-predicate))






;;; `Get-workspace-if-any' returns either: (a) block, if it is a workspace; (b)
;;; the workspace, if any, containing block; or (c) nil.

(def-substitution-macro get-workspace-if-any-macro (block)
  (loop as this-block = block then superblock?
	as superblock? = (superblock? this-block)
	when (null superblock?)
	  return (if (workspace-p this-block) this-block)))

;; Consider defining this as a macro.

;; OK, I did.  It is a performace hog, and is now a macro. -fmw, 11/16/94

(defun-simple get-workspace-if-any (block)
  (get-workspace-if-any-macro block))





;;; The following macros have to do with authorization violations. Most of the code
;;; is in SEQUENCES2. There is a secret convention here in that if
;;; only-workstation-workspace-can-be-on? has the value -1 (otherwise an
;;; inappropriate value) then disarm-destroyer is called.

(defvar workspace-image-plane-per-window (list nil nil))

(defvar image-plane-is-obscured-p (cons nil (cdr workspace-image-plane-per-window)))

(defmacro arm-destroyer ()
  '(setf (second workspace-image-plane-per-window) t))

(defmacro disarm-destroyer ()
  '(setf (second image-plane-is-obscured-p) nil))

(defmacro destroyer-armed-p ()
  '(second workspace-image-plane-per-window))





;;; `Make-workspace' makes a workspace of the specified class.  If name?  is
;;; specified, the workspace will be given that name.  If initial-subblock?  is
;;; specified, it is shifted, if necessary, so as to be centered on the (0,0)
;;; position of the workspace, and is then made to be the only subblock of the
;;; workspace.  If non-default-margin?  is specified, it replaces the default
;;; value of the workspace-margin slot.  If no initial-subblock?  is specified,
;;; the workspace will be a square, twice the workspace margin in width and
;;; height, centered on (0,0).  If minimum-initial-width?  and/or
;;; minimum-initial-height?  are specified, the workspace will be made at least
;;; that wide and/or high.

;;; If only-workstation-workspace-can-be-on?  is specified, workspace must be a
;;; non- kb workspace.  When specified, only-workstation-workspace-can-be-on?
;;; is made the workstation the resulting workspace is specific to.

(defun make-workspace
       (class
	&optional name? initial-subblock? non-default-margin?
	          minimum-initial-width? minimum-initial-height?
		  only-workstation-workspace-can-be-on?)

  (let ((workspace (make-frame class)))

    (if non-default-margin?
	(setf (workspace-margin workspace) non-default-margin?))

    (change-edges-of-block
      workspace
      (if minimum-initial-width? (-w (halfw minimum-initial-width?)) 0)
      (if minimum-initial-height? (-w (halfw minimum-initial-height?)) 0)
      (if minimum-initial-width?
	  (+w minimum-initial-width? (-w (halfw minimum-initial-width?)))
	  0)
      (if minimum-initial-height?
	  (+w minimum-initial-height? (-w (halfw minimum-initial-height?)))
	  0))

    (cond
      ((eql only-workstation-workspace-can-be-on? -1)
       (disarm-destroyer))
      ((and only-workstation-workspace-can-be-on?
	    (frame-of-class-p			; bother?
	      workspace 'non-kb-workspace))
       (gensym-push
	 workspace
	 (non-kb-workspaces-for-this-workstation-only
	   only-workstation-workspace-can-be-on?))
       (setf (only-workstation-this-non-kb-workspace-can-be-on? workspace)
	     only-workstation-workspace-can-be-on?)))

    (if initial-subblock?
	(let ((delta-x
		(-w (halfw (+w (left-edge-of-block initial-subblock?)
			       (right-edge-of-block initial-subblock?)))))
	      (delta-y
		(-w (halfw (+w (top-edge-of-block initial-subblock?)
			       (bottom-edge-of-block initial-subblock?))))))
	  (funcall-method			; use a more abstract function!
	    'shift initial-subblock? delta-x delta-y)
	  (add-subblock initial-subblock? workspace)
	  (enlarge-workspace-for-block-and-subblocks-as-necessary
	    initial-subblock? workspace)
	  (add-loose-ends-as-subblocks-and-shift
	    initial-subblock? workspace delta-x delta-y)
	  (if (frame-of-class-p initial-subblock? 'entity)
	      (update-name-box initial-subblock?)))
	(enlarge-workspace-if-necessary workspace 0 0 0 0))

    (if name? (change-slot-value workspace 'name-or-names-for-frame name?))

    workspace))

;; Consider eliminating arguments if not now used, e.g. name?.  At least, move the name?
;; argument later in the argument sequence.



;;; `Orphan-workspace-p' tests whether workspace is an `orphan workspace', a workspace that
;;; has no name, is not a subworkspace, is not on an image plane, and has no subblocks.

(defun orphan-workspace-p (workspace)
  (and (null (name-or-names-for-frame workspace))
       (null (parent-of-subworkspace? workspace))
       (null (workspace-showing-p-function workspace nil))
       (not (has-subblocks-p workspace))))

;; Consider having a workspace be deemed an orphan (1) even when it has subblocks, provided
;; that all of those subblocks are "useless", (2) even when it is on one or more image
;; planes, provided that all of those image planes are "irrelevant", and (3) even when it
;; is a subworkspace, provided that its parent is "useless".


;;;; View Preferences


;;; `View-preferences' is a new workspace attribute, as of 8.0r1, containing a
;;; slot-value-plist of options which influence the default view created when
;;; the workspace is shown, modulo the capabilities of the g2-window.

;;; The view (aka image-plane) gets a copy of the preferences upon creation, in
;;; the slot `image-plane-view-preferences'. Someday users will be able to
;;; further modify options directly on the view object.

;;; Currently, all of the defined preferences are pure booleans.  The slot
;;; grammar is defined up in GRAMMAR7.  Workspace view-preferences are SAVED
;;; with the KB.

(def-concept view-preferences)

(defparameter known-view-preferences nil)

(defmacro def-view-preference (name (type) grammar)
  (let ((parse (case type
		 (truth-value (cons name t))
		 #+development
		 (t (warn "Unknown type ~s in def-view-preference for ~s" type name)))))
    `(push-update (list ',name ',type ',grammar ',parse) known-view-preferences :key car)))

(defun get-view-preference (plist indicator)
  #+development (assert-for-development (member indicator known-view-preferences :key #'car))
  (getf plist indicator))

(defun set-view-preference-1 (plist indicator value)
  #+development (assert-for-development (member indicator known-view-preferences :key #'car))
  #+development (assert-for-development (atom value))
  (cond (value
	 (set-property-macro plist indicator slot-value-cons value))
	(t
	 (remove-property-macro plist indicator reclaim-slot-value-cons))))

(defmacro setf-view-preference (place indicator value)
  `(setf ,place (set-view-preference-1 ,place ,indicator ,value)))


(def-view-preference fixed-size (truth-value)
  ('fixed 'size))

(def-view-preference unselectable (truth-value)
  'unselectable)

(def-view-preference visible-grid (truth-value)
  ('visible 'grid))


;;;; Unsaved Slots in Representation Tables (Development Only)



;;; There are a few system-defined slots that are not saved, but yet may be
;;; included in attribute tables. There is slight complexity restoring such
;;; tables from saved KBs in that the value is not saved in the KB, and may well
;;; have changed since the save, generally to the default value, so the text in
;;; the text cell of a table representing such a slot's value is not going to be
;;; right.
;;;
;;; The solution, as of the commits being done today (3/28/03), is to refresh
;;; all represented slots upon loading.  Some refreshing of slots that don't have
;;; this problem might have avoided, with some additional record-keeping and
;;; complexity, but I (MHD) found through testing and benchmarking that the
;;; amount of overhead that could be avoided would be rather slight compared to
;;; the overall file loading time, and therefore not worth the additional coding
;;; and complexity.

;;; The following functions were useful for testing and determining possibly
;;; problematic slots.  Particularly useful was the function
;;; `print-do-not-save-slots'. It currently prints a lengthy list of all the
;;; do-not-save slots of classes that inherit from ITEM.  Some, but not all,
;;; would have not displayed the right thing in tables saved in KBs. A few would 
;;; have worked anyway due to alternative mechanisms to accomplish that. 

#+development
(progn

(defun class-may-have-unsaved-represented-slots-p (class)
  (class-description-may-have-unsaved-represented-slots-p
    (class-description class)))

(defun class-description-may-have-unsaved-represented-slots-p
    (class-description)
  (loop with slot-descriptions = (slot-descriptions class-description)
	for slot-description in slot-descriptions
	thereis (slot-may-have-unsaved-representions-p slot-description)))

(defun slot-may-have-unsaved-representions-p (slot-description)
  (let ((features (slot-features slot-description)))
    (and (category-symbol-given-slot-type (feature-assq 'type features))
	 (feature-assq 'do-not-save features)
	 (null (feature-assq 'do-not-put-in-attribute-tables features))
	 (null (feature-assq 'previously-put-in-attribute-tables features)))))


(defun do-not-save-slots ()
  (loop with a-list-so-far = '()
	for class being each subclass of 'root
	as class-description = (class-description class)
	as slot-descriptions = (slot-descriptions class-description)
	do (loop for slot-description in slot-descriptions
		 when (slot-may-have-unsaved-representions-p slot-description)
		   do (let ((slot-name (pretty-slot-name slot-description))
			    entry)
			(unless (setq entry (assq slot-name a-list-so-far))
			  (setq entry (list slot-name))
			  (push entry a-list-so-far))
			(setf (cdr entry) (nconc (cdr entry) (list class)))))
	finally (return (nreverse a-list-so-far))))

(defun print-do-not-save-slots ()
  (let ((a-list (do-not-save-slots)))
    (loop for (slot-name . classes) in a-list
	  as count from 1
	  when (loop for class in classes
		     thereis (subclassp class 'item))
	    do (format t "~2%(~d) ~(~a: ~a~)" count slot-name classes))))

;; Note: if we wanted to remove all overhead during KB load, we could use some
;; of the functionality in this subsection to record in class descriptions the
;; presence of such slots, and then limit refreshing to just those slots/frames.
;; For now, I don't think the overhead is so significant that we should bother
;; with the complexity and code necessary do that. (MHD 3/28/03)


)  ; #+development (progn ...)

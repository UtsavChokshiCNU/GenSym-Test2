;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module DEFINITIONS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin, Stephen R. DeVoy, and Gretchen Wang





;;;; Forward References


(declare-forward-references-to-module
  books
  update-default-message-properties-if-inherited-in-instances
  notify-engineer)

(declare-forward-references-to-module
  boxes
  update-name-box
  process-default-text-box-colors)

(declare-forward-references-to-module
  charts1
  set-up-part-dictionaries)

(declare-forward-references-to-module
  comp-utils
  (current-computation-component-particulars variable)
  (*current-computation-frame* variable)
  stable-class-p
  handle-dependent-or-stable-status-change-for-item
  handle-stable-hierarchy-or-inline-status-change-for-item)

(declare-forward-references-to-module
  controls
  change-icon-variables)

(declare-forward-references-to-module
  eval
  add-built-in-functions-to-directory)

(declare-forward-references-to-module
  grammar1a
  attribute-definition-type-modifications
  attribute-definition-type-specification)

(declare-forward-references-to-module
  grammar5
  fix-data-type
  set-appropriate-instance-frame-flags-for-update-slot-description
  date-format-quantity-attribute-function
  date-format-integer-attribute-function
  date-format-float-attribute-function)

(declare-forward-references-to-module
  grammar6b
  write-attribute-description)

(declare-forward-references-to-module
 grammar7
 get-initial-evaluation-value-for-default-override-1
 slot-description-from-superior-class
 map-alias-to-system-slot-name
 get-grammar-category-for-default-override)

(declare-forward-references-to-module
  install
  update-generic-simulation-formula-for-variable-or-parameter
  put-attribute-description-value
  write-frame-notes-for-names
  validate-kb-after-runtime-definition-change
  compiled-items-referring-to-this-name-function
  analyze-attributes-of-subclasses-for-consistency
  analyze-class-attributes-for-consistency
  analyze-compiled-items-for-consistency
  do-consistency-analysis-work-on-subframe-overrides
  set-simulation-stored-history-spec-for-update-slot-description)

(declare-forward-references-to-module
  kb-load1
  connections-for-class-slot-correct-format-p
  (kb-flags variable)
  (new-saved-kb-format-p variable)
  find-differences-in-frames-if-any)

(declare-forward-references-to-module
  kb-load2
  (loading-kb-p variable)
  fix-line-drawing-description-for-class)

(declare-forward-references-to-module
  kb-merge
  (currently-automatically-resolving-class-name-conflicts? variable)
  transfer-values-to-interim-class-definition-for-merge
  merge-differing-slots-in-definitions
  combine-class-definitions
  get-slot-values-to-save-for-conflict-resolution
  reinstate-non-default-values-after-merge)

(declare-forward-references-to-module
  kb-save2
  (releasing-kb? variable)
  remove-kb-state-variable-record)

(declare-forward-references-to-module
  kb-save3
  note-change-or-deletion)

(declare-forward-references-to-module
  sets
  type-specification-for-user-or-datum-type)

(declare-forward-references-to-module
  activate
  suspend-activation
  resume-activation
  activate-in-new-activation-unit)

(declare-forward-references-to-module
  simulate5
  install-items-of-class-in-model)

(declare-forward-references-to-module
  relations
  block-relation-instances-violate-class-type-p
  remove-invalid-relation-instances)

(declare-forward-references-to-module
  tables
  delete-all-attribute-displays
  make-attribute-displays-per-specs
  update-representations
  update-frame-name-references
  update-attribute-tables-for-instances)

(declare-forward-references-to-module
  variables
  update-indexed-attribute-properties
  remove-indexed-attribute-properties 
  collect-all-indexed-attributes-for-class
  update-indexed-attribute-hash-table 
  clear-indexed-attribute-hash-table
  data-type-of-variable-or-parameter-function)

(declare-forward-references-to-module
  chaining
  decache-class-chaining-lists)

(declare-forward-references-to-module
  grammar6a
  compile-list-of-classes-for-slot
  reserved-system-slot-name-p)

(declare-forward-references-to-module
  media
  cache-media-bin-if-possible)

(declare-forward-references-to-module
  g2-bpel
  reflect-g2gl-object-icon-substitutions)


;; To KB load stuff.
(declare-forward-reference main-kb-being-read? variable)
(declare-forward-reference namestring-for-kb-being-read variable)
(declare-forward-reference current-kb-pathname? variable)

;;to proc-utills
(declare-forward-reference get-named-procedure-methods-for-class function)
;;to events-g2
(declare-forward-reference send-ws-representations-item-virtual-attribute-change function)
(declare-forward-reference send-ws-representations-connection-moved function)


(declare-forward-reference break-out-of-debug-messages function)

(declare-forward-reference update-runtime-structures-according-to-edit function)

(declare-forward-reference possibly-aliased-slot-description-from-superior-class function)


;; COMMANDS2
(declare-forward-reference update-icon-views function)



;;;; Attribute-p and related macros



; Documented later in this file.
(def-kb-specific-property-name class-and-symbol-values-for-attribute
    reclaim-frame-tree-for-attribute)

(defun reclaim-frame-tree-for-attribute (class-and-symbol-values-for-attribute)
  (reclaim-frame-tree class-and-symbol-values-for-attribute))


;;; `Attribute-p' is true if its argument is an attribute in some user class-
;;; definition, one of the "predefined user attributes", which means it should
;;; have an entry in the a-list predefined-user-attributes.

(def-substitution-macro attribute-p (symbol)
  (class-and-symbol-values-for-attribute symbol))




;;; `Attribute-of-class-p' is true if symbol is a user defined attribute of the given
;;; class (or a superior class).

(defun attribute-of-class-p (symbol class)
  (loop with class-and-symbol-values-for-attribute =
      (class-and-symbol-values-for-attribute symbol)
    for class-1 in (class-inheritance-path (class-description class))
    thereis
      (assq class-1 class-and-symbol-values-for-attribute)
      until (eq class-1 'block)))




;;; `Attribute-of-class-or-subclass-p' (symbol class) is true if symbol is a
;;; user defined attribute of class (or a superior class) or any subclass of
;;; class.

(defun-simple attribute-of-class-or-subclass-p (symbol class)
  (let ((class-and-symbol-values (class-and-symbol-values-for-attribute symbol)))
    (and class-and-symbol-values
     (or (eq class 'item)
         (let ((class-description (class-description class)))
           (and class-description
            (loop for (defining-class) in class-and-symbol-values
              for defining-class-description
                  = (class-description defining-class)
              thereis (and defining-class-description
                       (or (class-description-subclass-of-class-description-p
                         class-description
                         defining-class-description)
                       ;; See Note! (MHD 9/18/03)
                       (loop for defining-class-subclass
                             being each subclass of defining-class
                         thereis
                           (class-description-subclass-of-class-description-p
                             (class-description defining-class-subclass)
                             class-description)))))))))))

;; Note: this has been changed in a manner analogous to
;; exported-attribute-of-class-or-subclass-p, q.v., for a discussion of recent
;; changes/bug fixes for 7.1r0. (MHD & ALatto 9/18/03)




;;; The global property `classes-defining-exported-attribute' is used to hold
;;; the list of disjoint classes defining an exported attribute name.  This is
;;; used to help compute the notes of computations refering to system attribute
;;; names.  Note that this does NOT include virtual attributes.

(def-global-property-name classes-defining-exported-attribute)

(defun-void add-defining-class-for-exported-attribute (attribute-name class)
  (let ((existing-classes (classes-defining-exported-attribute attribute-name)))
    (loop with existing-classes-to-remove = nil
      with new-class-description? = nil
      for existing-class in existing-classes
      for existing-class-description = (class-description existing-class)
      do
      (cond ((class-description-subclass-of-class-description-p
          (or new-class-description?
          (setq new-class-description? (class-description class)))
          existing-class-description)
         (return nil))
        ((class-description-subclass-of-class-description-p
           existing-class-description new-class-description?)
         (with-permanent-allocation
           (push existing-class existing-classes-to-remove))))
      finally
        (loop for existing-class in existing-classes-to-remove do
          (setq existing-classes
            (delete existing-class existing-classes :test #'eq)))
        (with-permanent-allocation
          (setf (classes-defining-exported-attribute attribute-name)
            (cons class existing-classes))))))
          
      



;;; The function `exported-attribute-of-class-or-subclass-p' checks to see if a
;;; given symbol names an attribute exported through category-evaluator
;;; interfaces for the given class or some subclass of the given class.  This
;;; function is used to determine whether or not a frame note should be issued
;;; for a reference to this attribute on an item of the given class.  Also note
;;; that virtual attributes are NOT handled through this interface.

(defun-simple exported-attribute-of-class-or-subclass-p
    (attribute-name superior-class)
  (let ((defining-classes (classes-defining-exported-attribute attribute-name)))
    (and defining-classes
     (or (eq superior-class 'item)
         (let ((superior-class-description (class-description superior-class)))
           (and superior-class-description
            (loop for class in defining-classes
              for class-description = (class-description class)
              thereis
                (or (class-description-subclass-of-class-description-p
                  superior-class-description class-description)
                ;; now test subclasses of class, since a
                ;; subclass might be a subclass of
                ;; superior-class even if class is not,
                ;; i.e., due to multiple inheritance. See
                ;; note below. (MHD 9/18/03)
                (loop for class-subclass being each subclass of class
                      thereis
                        (class-description-subclass-of-class-description-p
                      (class-description class-subclass)
                      superior-class-description))))))))))

;; This is to fix a bug/limitation that's been in the software for a long time,
;; but was just exposed (or noticed* at least) due to changes in the class
;; hierarchy made for G2 7.1r0.  The bug that records this is HQ-4615417
;; "g2-window-user-name-in-operating-system reference gets notes". (MHD 9/18/03)

;; * On subsequent review, we found that this sort of problem has been around
;; for some time, and users could run into it with similar use of multiple
;; inheritance.  A separate bug (perhaps dating back to the first release with
;; multiple inhertance) might be made, but we are probably going to resolve it
;; now as part of this bug.  In particular, note that we've done the
;; corresponding changes to attribute-of-class-or-subclass-p.
;; (MHD and ALatto 9/18/03)



;;; `Method-of-class-or-subclass-p' (symbol class) is true if symbol is a
;;; defined method of class (or a superior class) or any subclass of
;;; class.

(defun method-of-class-or-subclass-p (method-name class)
  (let ((result? nil)
    (class-description? (class-description class)))
    (when class-description?
      (loop for inherited-class in  (class-inheritance-path class-description?)
        for method-list? = (get-named-procedure-methods-for-class
                 method-name inherited-class)
        for method-name? = (and method-list? (car-of-cons method-list?))
        until result?
        do
    (when (eq method-name? method-name)
      (setq result? t))))
    result?))




;;; The def-class form for `definition' is included for support of pre-5.0
;;; kbs, so that class-definition and its direct-inferior classes, object-
;;; definiiton, connection-definition, and message-definition will be
;;; definitions.

(def-class (definition (item entity) (foundation-class definition)
         define-predicate not-solely-instantiable
         not-user-instantiable do-not-put-in-menus
         ;; The class-export-comment class feature and the slots for class
         ;; have been moved up from class-definition to definition in order
         ;; to support generic references to definitions.  (ghw 12/10/96)
         (class-export-comment
           "The original parts document showed the following attributes for class-definition: reconcile.
<ul>
<li>direct-superior-classes: (symbol + ), 
<li>class-specific-attributes: ; Use this. attributes-specific-to-class is obsolete.
<ul>
<li>( [name: symbol,
<li> inital-value: value | class: symbol, 
<li> type: symbol  | type-description ] * ),
</ul>
<li>inherited-attributes:,
<ul>
<li>( [name: symbol,
<li> inital-value: value | class: symbol, 
<li> type: symbol  | type-description ] * ),
</ul>
<li>instance-configuration: ( configuration-expression-part *),
<li>menu-option: (member (a-final-menu-choice, not-a-final-menu-choice, never-a-menu-choice)),
<li>class-inheritance-path: ( symbol *) <!--from class-inheritance-path-of-definition,-->
<li>initializable system attributes,
<li>attribute-initializations: ( attribute-initialization-part *), 
<li>attribute-displays: ,; attribute-displays-spec, attribute-displays-for-class
<li>capabilities-and-restrictions: (configuration-expression-part *),
<li>stubs,; stubs-for-class
<li>class-restrictions: (configuration-expression-part *),
<li>connections-for-class: ??? ,  ; instances or definitions?
<li>default-overrides: ,
<li>default-settings: ,
<li>definition-menu-option: ,
<li>direct-superior-classes: ,; direct-superiors-of-defined-class
<li>icon-description-for-class?: ( regions-and-drawing-commands * ) | icon,
<li>name-of-defined-class: symbol,
<li>superior-class: symbol,
<li>user-overridable-system-attributes: , <!--was user-overridable-system-slots-->
<!--old-value-of-indexed-attributes, indexed-attributes-for-definition-->
</ul>"))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 52
      ((outline (30 0) (60 52) (0 52))
       (outline (30 1) (59 51) (1 51)))))
  
  (frame-author-or-authors
    nil (type authors-with-time-of-last-edit?)
    (attribute-export-comment
      "Will allow 0 or more author entries. each author entry may have a date. ~
authors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: structure, defining-class: item, writable: true
"))
  (frame-change-log nil (type frame-change-log))

  (name-or-names-for-frame
    nil do-not-save (type nil)
    do-not-put-in-attribute-tables)

  (name-of-defined-class
    nil vector-slot system (type new-class) do-not-clone)

  (direct-superiors-of-defined-class
    nil vector-slot system (type list-of-classes)
    (class-of-optional-subframe item))
  
  (indexed-attributes-for-definition nil system save)

  (class-specific-attributes
    nil vector-slot system (type attribute-descriptions))

  ;; Obsoleted slot.
  (class-restrictions nil lookup-slot system (type user-restrictions) do-not-save
              previously-put-in-attribute-tables)
  
  ;; New name for class-restrictions  -fmw, 9/7/93.
  (instance-configuration nil vector-slot system (type object-configuration))

  (change
    nil vector-slot system save (type class-definition-change))

  ;; The following two slots take the place of definition-menu-option for
  ;; 5.0.
  (instantiate? t vector-slot system user-overridable save
        (type yes-or-no) save)
  
  (include-in-menus? t vector-slot system user-overridable save
             (type yes-or-no) save)

  (class-inheritance-path-of-definition
    nil do-not-save lookup-slot system not-user-editable
    (type class-inheritance-path-of-definition)
    do-not-clone)
  
  (inherited-attributes
    nil system (type inherited-attributes) not-user-editable)

  (user-overridable-system-slots nil do-not-save system (type list-of-slots)
                 do-not-clone not-user-editable)

  (default-overrides nil vector-slot
    (type default-overrides-for-class-definitions) system do-not-clone )

  (icon-description-for-class?
    nil lookup-slot system (type icon-description?))

  ;; The purpose of this slot is to store the old value of
  ;; indexed-attributes-for-definition as a means of conveying it from the slot
  ;; compiler of attribute-descriptions to the slot putter of
  ;; class-specific-attributes. It is promptly reclaimed without
  ;; interrupts.    
  (old-value-of-indexed-attributes nil system)

  ;; The following three slots are for supporting change-the-text roles
  ;; in pre-4.0 kbs.
  (superior-class
    nil lookup-slot system (type old-superior-class)
    previously-put-in-attribute-tables do-not-save)
  
  (capabilities-and-restrictions
    nil lookup-slot system (type previous-capabilities)
    previously-put-in-attribute-tables do-not-save)

  (attributes-specific-to-class
    nil lookup-slot system (type old-attribute-descriptions)
    previously-put-in-attribute-tables do-not-save)

  ;; This slot is now obsolete.  It has been replaced by instantiate?
  ;; and include-in-menus? in 5.0.
  (definition-menu-option nil lookup-slot system (type menu-option)
              previously-put-in-attribute-tables
              do-not-save)
  (icon-background-images
       nil lookup-slot system save) ; (type background-images)))

  (entangled-slots nil lookup-slot system do-not-save))



;;; A `class-definition' is an entity which provides the user interface for
;;; defining item subclasses in G2.  Class-definition has three inferior-
;;; classes, object-definition, message-definition, and connection-definition
;;; which are included for supporting pre-5.0 kbs.  Class-definition can
;;; be used for specifying all user-defined classes.



(def-class (class-definition definition (foundation-class class-definition)
                 define-predicate)
  (number-of-renderings-for-bulk-delete
    #.default-number-of-renderings-for-bulk-delete
    vector-slot system)
  (maximum-renderings-for-class
    #.default-maximum-renderings-for-class
    vector-slot system))

(defun icon-decaching-parameters (class-name?)
  (let ((class-description? (class-description class-name?)))
    (cond ((and class-description?
        (class-description-is-user-defined-p class-description?))
       (let* ((class-definition (class-definition class-name?))
          (number-of-renderings-to-delete
            (number-of-renderings-for-bulk-delete class-definition))
          (maximum-renderings-for-class
            (maximum-renderings-for-class class-definition)))
         (values maximum-renderings-for-class
             number-of-renderings-to-delete)))
      (t
       (values #.default-maximum-renderings-for-class
           #.default-number-of-renderings-for-bulk-delete)))))
        

   
  
(define-slot-alias instantiate instantiate?)
(define-slot-alias include-in-menus include-in-menus?)

(define-slot-alias class-inheritance-path class-inheritance-path-of-definition)

(define-slot-alias initializable-system-attributes user-overridable-system-slots)

(def-absent-slot-putter superior-class (definition value)
  (declare (ignore definition value)))

(def-absent-slot-putter attributes-specific-to-class (definition value)
  (declare (ignore definition value)))

(def-substitution-macro class-definition-defines-object-class-p
    (class-definition)
  (memq 'object (class-inheritance-path-of-definition class-definition)))




#+development
(defun check-user-overridable-slots ()
  (let ((slots-without-feature nil)
    (slot-names-without-slot-descriptions nil))
  (loop for (class nil) in list-of-user-overridable-system-slots
    for class-description = (class-description class)
    for overridable-slots =
    (make-list-of-unaliased-user-overridable-system-slots-for-class
      (class-inheritance-path class-description))
    do
    (loop for slot-name in overridable-slots
      for slot-description = (get-slot-description-of-class-description
                   slot-name class-description)
      do
      (if slot-description
      (unless (feature-assq 'user-overridable
                (slot-features slot-description))
        (push (list class slot-name) slots-without-feature))
      (push (list class slot-name) slot-names-without-slot-descriptions))))
  (values slots-without-feature slot-names-without-slot-descriptions)))

#+development
(defun determine-aliased-overridable-slots-for-class-level (class)
  (let ((list-to-return nil)
    (overridable-slots
      (second (car (member class list-of-user-overridable-system-slots
                   :test 'car-eq))))
    (exception-slots
      (third (car (member class list-of-user-overridable-system-slots
                   :test 'car-eq)))))
    (loop for slot-name in overridable-slots
      do
      (unless (memq slot-name exception-slots)
    (setq list-to-return (nconc list-to-return (list slot-name)))))
    list-to-return))

#+development
(defun print-aliased-overridable-slots-for-subclassable-item-classes ()
  (loop for class being each subclass of 'item
    when (feature-assq 'foundation-class
               (class-features (class-description class)))
      do
        (format t "~%~%~A : " class)
        (loop for inheritance-class in (class-inheritance-path
                         (class-description class))
          do
          (cond ((eq inheritance-class 'item)
             (format t "item")
             (loop-finish))
            (t
             (format t "~(~a, ~)" inheritance-class))))
        (let ((slots (determine-aliased-overridable-slots-for-class-level
               class)))
          (loop for slot-name in slots
            do
        (format t "~%    ~(~a~)" slot-name)))))




;;; The macro `class-definition-defines-user-editable-icon-class-p' returns
;;; true when the set of direct superiors on a class-definition indicates
;;; that the class can have a user-defined icon; otherwise it returns nil.

(def-substitution-macro class-definition-defines-user-editable-icon-class-p
    (class-definition)
  (and (class-inheritance-path-of-definition class-definition)
       (loop for superior in (direct-superiors-of-defined-class
                   class-definition)
         thereis (and (subclassp superior 'entity)
              (not (subclassp superior 'connection))
              (not (subclassp superior 'meter))
              (slot-init-form
                (slot-description-from-class
                  superior 'icon-description))))))

(defun name-of-defined-class-function (frame)
  (name-of-defined-class frame))

#+unused
(defun class-specific-attributes-function (class-definition)
  (class-specific-attributes class-definition))

(def-absent-slot-putter mother-class-of-class (class-definition value)
  (declare (ignore class-definition value)))

(def-absent-slot-putter accumulated-changes (class-definition value)
  (declare (ignore class-definition value)))

(def-kb-specific-property-name temporary-class-instance-list)




;;; `Potential-inferior-class-definitions' of a direct superior class
;;; symbol is a list of inferior class definitions which are incomplete.  A
;;; definition is added to the list when the definition lacks a name or is
;;; transient, and so is not about to define a class.  It is removed from the
;;; list when the inferior definition becomes a class.

(def-global-or-kb-specific-property-name potential-inferior-class-definitions
    copy-list-using-class-description-conses-function)




;;; An `object-definition' is a definition whose purpose is to cause a
;;; class definition (in the frames system) to exist when the
;;; object-definition is installed, and to cease to exist when the
;;; object-definition is not in use or deleted.  Such definitions are
;;; always kb-specific, and always define subclasses of entity.

(def-class (object-definition class-definition
                  (foundation-class object-definition)
                  define-predicate)

  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 52
      ((outline (30 0) (60 52) (0 52))
       (outline (30 1) (59 51) (1 51)))))

  (direct-superiors-of-defined-class
    nil vector-slot system
    (type list-of-object-classes)
    (class-of-optional-subframe object))

  (change
    nil vector-slot system (type object-change))

  (user-overridable-system-slots nil system (type nil)
                 do-not-put-in-attribute-tables)

  (default-overrides nil vector-slot
    (type default-overrides-for-object-definitions) system do-not-clone)

  (attribute-displays-spec?         
    nil lookup-slot system (type attribute-displays-spec?)) 
                        
  (connections-for-class?
    nil vector-slot system (type connections?))

  ;; This slot is for supporting "change the text of default settings in
  ;; pre-4.0 kbs.
  (default-settings
    nil lookup-slot system (type old-default-settings)
    previously-put-in-attribute-tables do-not-save))




(def-substitution-macro get-icon-description-given-class (class)
  (slot-init-form
    (slot-description-from-class class 'icon-description)))



;;; `Fix-icon-description-for-class-slot' for width-of-icon-for-class?,
;;; height-of-icon-for-class?, and line-drawing-description-for-class? maintains
;;; compatability between KBs created in G2 releases prior to release 2.0 or in
;;; a development version of 2.0 prior to 7/28/89.
;;;
;;; When called with color?, this can be assumed to be called as the last
;;; element.  Note that this arg is new for 4.0, and can only be called for 4.0
;;; loading a 2.0 or earlier KB.  This represents the now-absent
;;; line-color-of-icon slot, which lacks an explicit absent slot putter, but has
;;; special purpose handling in read-frame-for-kb.
;;;
;;; When reading in a 3.0 KB, fix-icon-description-for-class-slot should be
;;; entirely bypassed.

(defun fix-icon-description-for-class-slot
    (definition width? height? description? color?)
  (when (null (icon-description-for-class? definition))
    (setf (icon-description-for-class? definition) (slot-value-list nil nil)))
  (when width?
    (setf (first (icon-description-for-class? definition)) width?))
  (when height?
    (setf (second (icon-description-for-class? definition)) height?))
  (when description?    
    (setf (cddr (icon-description-for-class? definition)) description?))
  (when (or color?          ; always called last
        description?)       ; to fix blinking areas, say
    (setf (cddr (icon-description-for-class? definition))
      (fix-line-drawing-description-for-class
        (cddr (icon-description-for-class? definition))
        color?)))
  (let ((icon-description-for-class-so-far
      (icon-description-for-class? definition)))
    (cond
      ;; must succeed once and only once per definition:
      ((and (first icon-description-for-class-so-far)
        (second icon-description-for-class-so-far)
        (cddr icon-description-for-class-so-far)
        (get-polychrome-header-if-any ; require polychrome header
          (cddr icon-description-for-class-so-far))
        (get-variable-specification-if-any 
          icon-description-for-class-so-far)
        (get-icon-background-layer-if-any
          icon-description-for-class-so-far))
       (setf (icon-description-for-class? definition) nil)
       (initialize-slot-value
     definition 'icon-description-for-class?
     icon-description-for-class-so-far)))))

(def-absent-slot-putter width-of-icon-for-class? (frame slot-value)
  (fix-icon-description-for-class-slot
    frame slot-value nil nil nil))

(def-absent-slot-putter height-of-icon-for-class? (frame slot-value)
  (fix-icon-description-for-class-slot
    frame nil slot-value nil nil))

(def-absent-slot-putter line-drawing-description-for-class? (frame slot-value)
  (fix-icon-description-for-class-slot
    frame nil nil (copy-for-slot-value slot-value) nil))








;;;; Specifying Attribute Displays



;;; `Attribute displays' may be specified to appear under objects by
;;; editing the attributes-display-spec, with the following grammar:
;;;
;;;    { {<attribute-name-spec> [WITH NAME]}+
;;;      [AT (<x-offset>, <y-offset>):]
;;;    }+
;;;
;;;    | INHERITED
;;;    | NONE
;;;
;;;

;;; The slot named attribute-displays-spec? is shown to users via its alias,
;;; attribute-displays.

(define-slot-alias attribute-displays attribute-displays-spec? object-definition)

(add-grammar-rules-for-list
  'attribute-displays-spec? 'attribute-display-spec
  '\; nil 'inherited)

(add-grammar-rules-for-list
  'attributes-list-part-of-attribute-display-spec
  'attribute-name-spec
  '\,)

(add-grammar-rules
  '((attribute-displays-spec? 'none)

    (attribute-display-spec
      (attributes-list-part-of-attribute-display-spec
    position-part-of-attribute-display-spec))
    (position-part-of-attribute-display-spec
      ('offset 'by '\( number '\, number '\))
      (4 6))                    ; dotted?
    (position-part-of-attribute-display-spec
      ('at 'standard 'position)
      at-standard-position)
    (attribute-name-spec
      system-or-user-defined-attribute-name) ; unlisted means show value only
    (attribute-name-spec        ; listed means show value with name
      (system-or-user-defined-attribute-name 'with 'name)
      (1))))

(def-slot-value-compiler attribute-displays-spec? (parse-result)
  (cond
    ((eq parse-result 'inherited)
     nil)
    ((eq parse-result 'none)
     'none)
    (t
     ;; else of the form
     ;;   (\; {<individual-display-spec>}+)
     ;; make it be
     ;;   ({<individual-display-spec>}+)
     ;; with numbers turned into integers
     (loop for individual-display-spec in (cdr parse-result)
       as offset-spec
          = (second individual-display-spec)
       
       do (unless (eq offset-spec 'at-standard-position)
        ;; make sure offset-spec is (integer integer):
        (when (not (integerp (first offset-spec)))
          (setf (first offset-spec)
            (with-temporary-gensym-float-creation ads
              (round (phrase-number-value (first offset-spec))))))
        (when (not (integerp (second offset-spec)))
          (setf (second offset-spec)
            (with-temporary-gensym-float-creation ads
              (round (phrase-number-value (second offset-spec)))))))
        
          ;; take out \, in
          ;;   (( \, {<attribute-name-spec>}+ ) <offset-spec>)
       do (setf (first individual-display-spec)
            (cdr (first individual-display-spec)))
          
       finally
         (return 
           (cdr parse-result))))))

(def-slot-value-writer attribute-displays-spec? (value)
  (write-attribute-displays-for-class value))

(defun write-attribute-displays-for-class (value)
  (cond
    ((null value)
     (twrite-symbol 'inherited))
    ((eq value 'none)
     (twrite-symbol 'none))
    (t     
      (loop for l on value
        as attribute-display-spec = (car l)
        as attributes-part = (first attribute-display-spec)
        as offset-part = (second attribute-display-spec)
        do (loop for l on attributes-part
             for attribute-name-spec
             = (car l)           
             do (if (name-denotation-p attribute-name-spec)
                (write-name-denotation attribute-name-spec)
                (progn
                  (write-name-denotation (first attribute-name-spec))
                  (twrite-string " with name")))                  
            (if (cdr l) (twrite-string ", ")))
           (if (eq offset-part 'at-standard-position)
           (tformat " at standard position")
           (tformat
             " offset by (~d, ~d)"
             (first offset-part) (second offset-part)))
           (if (cdr l) (tformat ";~%"))))))




;;; `Attribute-displays-spec?' is a slot on object-definitions.  It is
;;; maintained for backward compatibility.  There is no such slot on class-
;;; definitions.  All defined object classes have a class-specific-value
;;; (lookup) slot, `attribute-displays-for-class', that contains the class value
;;; for all defined object classes (whether defined with a class-definition or
;;; with an object-definition) just as the attribute-displays-spec?  slot
;;; contains the class value for classes defined with an object-definition.

;; As well as a list of attribute-display specifications, new-value? can be
;; 'none ("none") and nil ("inherited").  If the default value for a class is
;; nil and there is no inherited specifications, there will be no attribute-
;; displays class feature on the class; otherwise the class will have a
;; attribute-displays class feature, the cdr of which is a list of specifications
;; or 'none.  None can be inherited.

(def-slot-putter attribute-displays-spec? (object-definition new-value)
  (let ((user-class (name-of-defined-class object-definition)))
    (setf (attribute-displays-spec? object-definition) new-value)
    (if (and (classp user-class)
         (slot-description-from-class
           user-class 'attribute-displays-for-class))
    (update-attribute-displays-for-class user-class new-value)
    new-value)))

(def-class-slot-description-updater attribute-displays-for-class
    (object-class new-value)
  (change-class-slot-description-value
    'attribute-displays-for-class object-class new-value)
  (loop for subclass being each subclass of object-class
    for current-class-feature? = (get-class-feature-if-any
                       subclass 'attribute-displays)
    for subclass-class-description = (class-description subclass)
    for desired-attribute-displays-spec? =
    (loop for class in (class-inheritance-path subclass-class-description)
          for attribute-displays-for-class? =
              (and (class-description-is-user-defined-p
             (class-description class))
               (slot-description-from-class
             class 'attribute-displays-for-class)
               (class-slot-description-value
             'attribute-displays-for-class class))
          when attribute-displays-for-class?
        return attribute-displays-for-class?)
    do
    (unless (equal (cdr current-class-feature?) desired-attribute-displays-spec?)
      (if desired-attribute-displays-spec?
      (add-class-feature
        subclass
        (class-description-cons
          'attribute-displays
          (copy-tree-using-class-description-conses
        desired-attribute-displays-spec?)))
      (remove-class-feature subclass 'attribute-displays))))
  new-value)




;;; A `connection-definition' is a definition whose purpose is to cause a class
;;; definition for a connection (in the frames system) to exist when the
;;; connection-definition is installed and ok.

(def-class (connection-definition class-definition
                  (foundation-class connection-definition)
                  define-predicate)  

  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 52
      ((outline (30 0) (60 52) (0 52))
       (outline (30 1) (59 51) (1 51))
       
       (lines (0 27) (60 27))
       (lines (0 28) (60 28))
       (lines (0 31) (60 31))
       (lines (0 32) (60 32)))))

  (direct-superiors-of-defined-class
    nil vector-slot system
    (type list-of-connection-classes)    
    (class-of-optional-subframe connection))

  (change
    nil vector-slot system (type connection-change))

  (user-overridable-system-slots nil system (type nil)
                 do-not-put-in-attribute-tables)

  (icon-background-images
    nil lookup-slot system (type nil) do-not-put-in-attribute-tables)

  (default-overrides nil vector-slot
    (type default-overrides-for-connection-definitions) system do-not-clone)

  ;; Suppress these two slots for connection definitions.
  (instantiate? t vector-slot system save (type nil))
  (include-in-menus? t vector-slot system save (type nil))


  (icon-description-for-class?
    nil lookup-slot system do-not-put-in-attribute-tables)

  (cross-section-pattern-for-connection
    nil vector-slot system (type cross-section-pattern))

  (stub-length-for-connection
    nil vector-slot system (type stub-length))

  (junction-block-class-for-connection
    nil vector-slot system
    (type junction-class)))    ; junction-class was object-name (MHD 6/6/90)

  


(def-class (message-definition class-definition
                   (foundation-class message-definition)
                   define-predicate)

  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 52
      ((outline (30 0) (60 52) (0 52))
       (outline (30 1) (59 51) (1 51))
       (outline (15 44) (45 44) (45 36) (15 36)))))

  (change
    nil vector-slot system (type message-change))

  (user-overridable-system-slots nil system (type nil)
                 do-not-put-in-attribute-tables)

  (icon-background-images
    nil lookup-slot system (type nil) do-not-put-in-attribute-tables)

  (default-overrides nil vector-slot
    (type default-overrides-for-message-definitions) system do-not-clone)
  
  (direct-superiors-of-defined-class
    nil vector-slot system
    (type list-of-message-classes)      ; list-of-message-classes used to be
                     ;   message-class (9/10/93)
                     ; message-class used to be class (MHD 6/6/90)
    (class-of-optional-subframe message))

  (icon-description-for-class?
    nil lookup-slot system do-not-put-in-attribute-tables)

  (default-message-properties nil vector-slot system (type message-properties)))




;;; The macro `definition-class-is-subclass-of-obj-conn-mess-definition-p' will
;;; return non-nil when the class of the definition is a subclass of either
;;; an object-definition, a connection-definition, or a message-definition;
;;; otherwise it will return nil.

(defun definition-class-is-subclass-of-obj-conn-mess-definition-p
    (definition)
  (or (frame-of-class-p definition 'object-definition)
      (frame-of-class-p definition 'connection-definition)
      (frame-of-class-p definition 'message-definition)))




;;; The function `get-specialized-definition-class' will return the most
;;; specialized system-defined definition class for the definition.

(defun get-specialized-definition-class (definition)
  (frame-class-case definition
    (object-definition 'object-definition)
    (connection-definition 'connection-definition)
    (message-definition 'message-definition)
    (t 'class-definition)))


;;; The function `get-primary-foundation-class-for-definition' will return the
;;; most general class definition can define, e.g., message for
;;; message-definition, item for class-definition, etc.  This class is known as
;;; the `primary foundation class' for the definition.

(defun get-primary-foundation-class-for-definition (definition)
  (frame-class-case definition
    (object-definition 'object)
    (connection-definition 'connection)
    (message-definition 'message)
    (t 'item)))





;;; The function `definition-hierarchy-is-mixed-p' returns the different
;;; specialized definition class when the class hierarchy of the definition
;;; contains a definition with a different specialized class than the argument
;;; does; otherwise it returns nil.

(defun definition-hierarchy-is-mixed-p (definition)
  (let ((class-name? (name-of-defined-class definition)))

    (if (definition-class-is-subclass-of-obj-conn-mess-definition-p definition)
         
    (or (loop for superclass being each superclass of class-name?
          for superclass-definition = (class-definition superclass)
          when (framep superclass-definition)
            thereis
            (and (not
               (definition-class-is-subclass-of-obj-conn-mess-definition-p
                   superclass-definition))
             (get-specialized-definition-class superclass-definition)))
        
        (loop for subclass being each subclass of class-name?
          for subclass-definition = (if (eq (name-of-defined-class definition)
                            subclass)
                        definition
                        (class-definition subclass))
          thereis
          (and (not
             (definition-class-is-subclass-of-obj-conn-mess-definition-p
                 subclass-definition))
               (get-specialized-definition-class subclass-definition)))
        
        (loop for potential-definition being each potential-definition of class-name?
          thereis
          (and (not
             (definition-class-is-subclass-of-obj-conn-mess-definition-p
                 potential-definition))
               (get-specialized-definition-class potential-definition)))

        (loop for superior in (direct-superiors-of-defined-class definition)
          thereis
          (loop for potential-superior-definition being
            each potential-superior-definition of superior
            thereis
            (and
              (not (definition-class-is-subclass-of-obj-conn-mess-definition-p
                   potential-superior-definition))
              (get-specialized-definition-class
                potential-superior-definition)))))

    (or (loop for superclass being each superclass of class-name?
          for superclass-definition = (class-definition superclass)
               when (framep superclass-definition)
             thereis
             (and (definition-class-is-subclass-of-obj-conn-mess-definition-p
                  superclass-definition)
                  (get-specialized-definition-class superclass-definition)))
         
         (loop for subclass being each subclass of class-name?
               for subclass-definition = (if (eq (name-of-defined-class definition)
                             subclass)
                             definition
                             (class-definition subclass))
               thereis
               (and (definition-class-is-subclass-of-obj-conn-mess-definition-p
                subclass-definition)
                (get-specialized-definition-class subclass-definition)))
         
         (loop for potential-definition being each potential-definition of class-name?
               thereis
               (and (definition-class-is-subclass-of-obj-conn-mess-definition-p
                  potential-definition)
                (get-specialized-definition-class potential-definition)))

         (loop for superior in (direct-superiors-of-defined-class definition)
               thereis
               (loop for potential-superior-definition being
                 each potential-superior-definition of superior
                 thereis
                 (and
                   (definition-class-is-subclass-of-obj-conn-mess-definition-p
                   potential-superior-definition)
                   (get-specialized-definition-class
                 potential-superior-definition))))))))

                

  

;;; The macro `definitions-classes-are-compatible-p' returns non-nil when the
;;; two definitions are both subclasses of the same definition class.

(def-substitution-macro definition-classes-are-compatible-p
    (definition-1 definition-2)
  (cond
    ((frame-of-class-p definition-1 'object-definition)
     (frame-of-class-p definition-2 'object-definition))
    ((frame-of-class-p definition-1 'connection-definition)
     (frame-of-class-p definition-2 'connection-definition))
    ((frame-of-class-p definition-1 'message-definition)
     (frame-of-class-p definition-2 'message-definition))
    ((frame-of-class-p definition-1 'class-definition)
     (not (definition-class-is-subclass-of-obj-conn-mess-definition-p
            definition-2)))
    (t nil)))

(defun check-hierarchy
       (user-class-definition class-to-merge-to-definition)
  (let* ((parent (class-name-of-class-description 
                  (class-description-slot class-to-merge-to-definition)))
         (user-class (name-of-defined-class user-class-definition)))
    (cond
      ((or (null parent)
           (eq parent 'class-definition)
           (definition-class-is-subclass-of-obj-conn-mess-definition-p
             class-to-merge-to-definition))
       (return-from check-hierarchy t))
      ((eq parent user-class)
       (return-from check-hierarchy nil))
      (t
       (check-hierarchy user-class-definition
         (lookup-global-or-kb-specific-property-value parent 'class-definition))))))

;;; The function `inheritance-for-merge-is-acceptable-p' returns t when
;;; the direct-superior classes for target-class-definition are accepted by
;;; the slot-value compiler for definition-to-merge; otherwise it returns nil.

(defun-simple inheritance-for-merge-is-acceptable-p
    (definition-to-merge target-class-definition)
  (if (null (check-hierarchy definition-to-merge target-class-definition)) 
    (return-from inheritance-for-merge-is-acceptable-p nil))
  (let* ((copied-target-class-direct-superiors
      (copy-for-slot-value
        (direct-superiors-of-defined-class target-class-definition)))
     (value-for-compiler
       (when copied-target-class-direct-superiors
         (slot-value-cons '\, copied-target-class-direct-superiors)))
     (compile-result
       (compile-list-of-classes-for-slot
         value-for-compiler definition-to-merge
         'direct-superiors-of-defined-class)))
    (reclaim-slot-value-list value-for-compiler)
    (not (eq compile-result bad-phrase))))
       

    
    


    



;;;; Data Structures

;;; An `attribute-description' is a structure used to describe an attribute.  It
;;; sits on the class-specific-attributes slot of a user class class-definition.
;;; An accessor is defined for each of its components, attribute-name,
;;; attribute-type-specification-etc, attribute-initial-value,
;;; attribute-initial-type, attribute-range.

;;; The accessor `attribute-type-specification' formerly (< 4/12/04) was an
;;; accessor for the list structure, but now it is a complex accessor that
;;; accesses the attribute-type-specification of
;;; attribute-type-specification-etc, which may either hold a simple
;;; specification or a specification with modifications.

;;; The accessor `attribute-type-modifications' accesses the modifications, if
;;; any, from the attribute-type-specification-etc.

;;; The above accessors are setf'able.

;;; Note that KBs saved before this feature was implemented can never have
;;; attribute type modifications.  An attribute with no parsing or formatting
;;; modifications will also not have any modifications present, so will have a
;;; simple attribute type specification stored in the
;;; attribute-type-specification-etc field.

;;; Because of the occasional need to change the format of these structures, it
;;; is strongly discouraged for code to assume the layout of the list structure
;;; except for internals or certain cases.  In particular, avoid using loop
;;; destructing bind type of iteration, e.g., (loop for (attribute-name ...) in
;;; attribute-descriptions ...).  This will break if fields are added or moved
;;; around, and such code hard to locate and maintain.  Instead, just use the
;;; accessors to access each "field" -- in practice, there will almost never be
;;; any efficiency concern, e.g., (loop for ad in attribute-descriptions as
;;; attribute-name = (attribute-name ad) ...).

;;; NOTE: for additional code and information integral to this facility, see
;;; also the slot putter for class-specific-attributes, the slot compiler for
;;; attribute-descriptions, the def-grammar for attribute-definition-type in
;;; GRAMMAR1A, the grammar for attribute-descriptions in GRAMMAR6A, and the
;;; writer for attribute-descriptions in GRAMMAR6B.

(def-list-structure (attribute-description (:consing-function slot-value-cons))
  (attribute-name
    attribute-type-specification-etc
    attribute-initial-value
    attribute-initial-type
    . attribute-range))

(defun attribute-type-specification (attribute-description)
  (attribute-definition-type-specification
    (attribute-type-specification-etc attribute-description)))

(defun attribute-type-modifications (attribute-description)
  (attribute-definition-type-modifications
    (attribute-type-specification-etc attribute-description)))

(defsetf attribute-type-specification set-attribute-type-specification)

(defsetf attribute-type-modifications set-attribute-type-modifications)

;;; The constant `type-and-modifications-tag' has as its value the symbol
;;; :type-and-modifications (in the keyword package), which is used as the car
;;; of a cons to mark it as a list holding a type specification as its second
;;; element and modifications as its third element.  Note that we depend on
;;; keyword symbols surviving saving and loading in KBs, which they do.

(defconstant type-and-modifications-tag ':type-and-modifications)

(defun set-attribute-type-specification (attribute-description specification)
  (let ((etc (attribute-type-specification-etc attribute-description)))
    (cond
      ((and (consp etc) (eq (car etc) type-and-modifications-tag))
       (reclaim-slot-value (second etc))
       (setf (second etc) specification))
      (t (setf (attribute-type-specification-etc attribute-description)
           specification)))))

(defun set-attribute-type-modifications (attribute-description modifications)
  (let ((etc (attribute-type-specification-etc attribute-description)))
    (cond
      ((and (consp etc) (eq (car etc) type-and-modifications-tag))
       (cond
     ((null modifications)      ; reduce to simple format
      (setf (attribute-type-specification-etc attribute-description)
        (prog1 (second etc)
          (setf (second etc) nil)
          (reclaim-slot-value etc))))
     (t   
      (reclaim-slot-value (third etc))
      (setf (third etc) modifications))))
      (t (setf (attribute-type-specification-etc attribute-description)
           (slot-value-list type-and-modifications-tag etc modifications))))))


#+unused
(defun attribute-name-function (attribute-description)
  (attribute-name attribute-description))
    







;;;; Macros





;;; Used for the comparison of the content of attribute descriptions,
;;; `attribute-description-equal-p' returns t if its two attribute description
;;; arguments contain equal information.

(def-substitution-macro attribute-description-equal-p
            (attribute-description1 attribute-description2)
  (and (eq (attribute-name attribute-description1)
       (attribute-name attribute-description2))
       (eq (attribute-initial-value attribute-description1)
       (attribute-initial-value attribute-description2))
       (eq (attribute-initial-type attribute-description1)
       (attribute-initial-type attribute-description2))
       (equal (attribute-range attribute-description1)
          (attribute-range attribute-description2))))




;;; `Get-attribute-description?' expands into a form which returns the
;;; attribute description with the attribute name; otherwise it returns
;;; nil.

(defmacro get-attribute-description (attribute-name attribute-descriptions)
  `(assq ,attribute-name ,attribute-descriptions))







;;;; Predicates




;;; Class-definition-is-frame-p says whether class-definition is a frame, i.e.,
;;; an instance of the class DEFINITION, or a cons, i.e., a built-in,
;;; system-defined class definition.

(def-substitution-macro class-definition-is-frame-p (class-definition)
  (not (consp class-definition)))

;; Note: this as well as the unabstracted consp test is used almost everywhere
;; at present to mean "user-defined, not system-defined" without comment.
;; (MHD/ML 1/3/91)









;;;; Updating Functions




;;; `Update-icon-description', when reverting-to-superior-icon-description is
;;; non-null, changes the icon-description (slot-init-form) to the icon
;;; description of a superior class; otherwise the icon description is changed
;;; to the value of new-slot-init-form?


(defun update-icon-description
    (new-slot-init-form? class-definition
             &optional revert-to-superior-icon-description?)
  (let* ((user-class? (name-of-defined-class class-definition))
     (icon-background-layer (icon-background-images class-definition)))
         
    (when (classp user-class?)

      (let* ((user-class-description (class-description user-class?))
         (user-class-slot-descriptions
           (slot-descriptions user-class-description))
         (user-class-icon-slot-description
           (get-slot-description
         'icon-description user-class-slot-descriptions))
         (user-class-slot-init-form
           (slot-init-form user-class-icon-slot-description))
         (user-class-slot-features
           (slot-features user-class-icon-slot-description))
         (delta-width 0)
         (delta-height 0))

    ;; This needs to be wrapped around KB updates which update images.
    (with-deferred-drawing ()

      ;; Must erase old images *before* changing any data structure.
      (update-images-of-instances-governed-by-this-definition user-class? t)

      (if revert-to-superior-icon-description?

          (let* ((least-specific-superior-that-defines-icon-description
               (let ((reversed-class-inheritance-path
                   (nreverse
                 (copy-list-using-frame-conses
                   (class-inheritance-path user-class-description)))))
             (loop for class in reversed-class-inheritance-path
                   when (slot-description-from-class
                      class 'icon-description)
                 return (progn (reclaim-frame-list
                         reversed-class-inheritance-path)
                           class))))
             (least-specific-superior-icon-slot-description
               (get-slot-description-of-class-description
             'icon-description
             (class-description
               least-specific-superior-that-defines-icon-description)))
             (superior-class-icon-slot-description
               (slot-description-of-most-specific-superior-refining-slot
             (class-inheritance-path user-class-description)
             least-specific-superior-icon-slot-description))
             (superior-slot-init-form
               (slot-init-form superior-class-icon-slot-description)))
        (unless (eq user-class-slot-init-form
                superior-slot-init-form)
          (setq delta-width
            (-w (width-of-icon superior-slot-init-form)
                (width-of-icon user-class-slot-init-form)))
          (setq delta-height
            (-w (height-of-icon superior-slot-init-form)
                (height-of-icon user-class-slot-init-form)))
          (update-slot-description
            user-class? user-class-icon-slot-description nil nil nil t nil)))

          ;; updating an inherited or uninherited slot
          (let* ((icon-width (first new-slot-init-form?))
             (icon-height (second new-slot-init-form?))
             (line-drawing-description
               (copy-for-slot-value (cddr new-slot-init-form?)))
             (new-icon-description    
               (create-icon-description-if-valid
             icon-width icon-height line-drawing-description
             nil
             (copy-for-slot-value icon-background-layer))))
        (setf (icon-owner-class new-icon-description) user-class?)
        (setq delta-width
              (-w (width-of-icon new-icon-description)
              (width-of-icon user-class-slot-init-form)))
        (setq delta-height
              (-w (height-of-icon new-icon-description)
              (height-of-icon user-class-slot-init-form)))
        (update-slot-description 
          user-class? user-class-icon-slot-description nil
          new-icon-description user-class-slot-features nil nil)))

      ;; Probably the fourth argument should be changed to
      ;; get a list of variables from new-slot-init-form, at least
      ;; when revert-to-superior-icon-description? is true. But I
      ;; don't want to risk the change right now. -alatto, 10/31/05
      (adjust-and-draw-images-governed-by-this-class
        user-class? delta-width delta-height nil)
      (when g2gl-object-icon-substitutions-may-be-in-use-p
        (reflect-g2gl-object-icon-substitutions)))))))




;;; The function `subclass-inherits-icon-description-from-superior' returns
;;; t when subclass inherits its icon description from superior; otherwise
;;; it returns nil.

(defun subclass-inherits-icon-description-from-superior-p
    (subclass superior superior-icon-description)
  (let ((subclass-class-description
      (class-description subclass)))
    (and (not (class-has-override-on-slot-p
        subclass-class-description 'icon-description))
     (eq superior
         (most-specific-superior-that-refines-slot
           (class-inheritance-path subclass-class-description)
           superior-icon-description)))))




;;; The defvar `preserve-non-default-icon-colors-or-variables?', when non-NIL, prevents
;;; adjust-and-draw-images-governed-by-this-class-1 from throwing away KB state
;;; changes to the icon-colors or icon-variables of icons.

(defvar preserve-non-default-icon-colors-or-variables? nil)





;;; The function `adjust-and-draw-images-governed-by-this-class' draws the
;;; icons for instances of user-class and those subclasses of user-class
;;; that inherit their icon description from user-class.

(defun adjust-and-draw-images-governed-by-this-class
       (user-class delta-width delta-height variables-to-save)
  (when (classp user-class)
    (adjust-and-draw-images-governed-by-this-class-1
      user-class delta-width delta-height variables-to-save
      ;; The unoptimized slot-description accessor is used here
      ;; because this function is called when the class hierarchy
      ;; is changing (alter-inheritance-of-class-without-changing
      ;; foundation-class) or the icon-descriptions are changing
      ;; (update-icon-description).
      (get-slot-description
    'icon-description
    (slot-descriptions (class-description user-class))))

    ;; Update views of the icon for the named class. -fmw, 7/9/03
    (update-icon-views user-class)))

(defun adjust-and-draw-images-governed-by-this-class-1
    (user-class delta-width delta-height variables-to-save icon-description)

  (loop with defining-class-for-user-class-icon-description =
    (if (class-has-override-on-slot-p
          (class-description user-class) 'icon-description)
        user-class
        (most-specific-superior-that-refines-slot
          (class-inheritance-path (class-description user-class))
          icon-description))
    for subclass being each subclass of user-class
    for subclass-inherits-icon-description? =
    (or (eq subclass user-class)
        (subclass-inherits-icon-description-from-superior-p
          subclass defining-class-for-user-class-icon-description
          icon-description))
    do
    (when subclass-inherits-icon-description?
      (let ((subclass-icon-description
          (if (eq subclass user-class)
          icon-description
          (get-slot-description
            'icon-description
            (slot-descriptions (class-description subclass))))))
    (loop for entity being each strict-class-instance of subclass
          do
      ;; Usually, the connections have already been erased at this point.
      ;; This erase is necessary for cases where two or more instances of
      ;; the class being adjusted are joined by one connection.  The
      ;; connection will be drawn twice in this case, and must be erased
      ;; in between (or x-or problems will result).
      (when (or (/=w delta-width 0)
            (/=w delta-height 0))
        (adjust-edges-of-instance entity delta-width delta-height))
      
      ;; Changing icon description means getting rid of KB state changes
      ;; to line color and color pattern.  In previous releases, we always
      ;; did this for polychrome icons, but had some odd exceptions for
      ;; monochrome.  Now it's consistent.  (MHD 5/7/95)
      (unless preserve-non-default-icon-colors-or-variables?
        (change-icon-variables entity (saved-variable-values entity variables-to-save))
        (change-icon-attribute entity 'line-color nil)
        (remove-kb-state-variable-record entity 'icon-color)
        (change-icon-attribute entity 'icon-color-pattern nil)
        (remove-kb-state-variable-record entity 'icon-color-pattern))
      
      (when (or (>w delta-width 0)
            (>w delta-height 0))
        (enlarge-workspace-for-block-rectangle-if-necessary entity nil))
      (cond ((entity-is-opaque-p entity)
         (set-opaque-block entity)) 
        (t (clear-opaque-block entity)))
      (update-images-of-block entity nil nil)
      (update-input-connections-of-entity
        entity nil subclass-icon-description))))))

(defun saved-variable-values (entity variables-to-save)
  (let (saved-values)
    (loop for (variable value) on
      (get-computed-values-plist (icon-attributes-plist entity)) by #'cddr
      do
      (when (memq variable variables-to-save)
    (slot-value-push variable saved-values)
    (slot-value-push (if (wide-string-p value)
                 (copy-wide-string value)
                 value)
             saved-values)))
    (nreverse saved-values)))

;;; The function `update-images-of-instances-governed-by-this-definition' draws
;;; or erases the icons for instances of user-class and those subclasses of
;;; user-class that inherit their icon description from user-class.

(defun update-images-of-instances-governed-by-this-definition
    (user-class erase?)
  (when (classp user-class)
    (update-images-of-instances-governed-by-this-definition-1
      user-class erase?
      ;; The unoptimized slot-description accessor is used here
      ;; because this function is called when the class hierarchy
      ;; is changing (alter-inheritance-of-class-without-changing
      ;; foundation-class) or the icon-descriptions are changing
      ;; (update-icon-description).
      (get-slot-description
    'icon-description (slot-descriptions (class-description user-class))))))

(defun update-images-of-instances-governed-by-this-definition-1
    (user-class erase? icon-description)
  (loop with defining-class-for-user-class-icon-description =
         (if (class-has-override-on-slot-p
           (class-description user-class) 'icon-description)
         user-class
         (most-specific-superior-that-refines-slot
           (class-inheritance-path (class-description user-class))
           icon-description))
    for subclass being each subclass of user-class
    for subclass-inherits-icon-description? =
        (or (eq subclass user-class)
        (subclass-inherits-icon-description-from-superior-p
          subclass defining-class-for-user-class-icon-description
          icon-description))
    do
    (when subclass-inherits-icon-description?
      (loop with subclass-icon-description =
        (if (eq subclass user-class)
        icon-description
        (get-slot-description
          'icon-description
          (slot-descriptions (class-description subclass))))
        for instance being each strict-class-instance of subclass
        do
    (update-images-of-block instance erase? nil)
    (update-input-connections-of-entity 
      instance erase? subclass-icon-description)))))




(defun icon-description-for-instance (instance)
  (get-slot-description-of-class-description 
    'icon-description (class-description-slot instance)))




(defun adjust-edges-of-instance (entity delta-width delta-height)
  (let* ((icon-attributes-plist (icon-attributes-plist entity))
     (icon-description (icon-description entity))
     (reflection-and-rotation?
       (getfq icon-attributes-plist 'reflection-and-rotation))
     (x-magnification?
       (or (getf icon-attributes-plist 'x-magnification)
           (icon-x-magnification? icon-description)))
     (y-magnification?
       (or (getf icon-attributes-plist 'y-magnification)
           (icon-y-magnification? icon-description)))
     (sides-to-shift nil)
     (rotated-delta-width nil)
     (rotated-delta-height nil)
     (straight-connections-with-deltas
       (loop for connection being each connection of entity
         as delta? = (connection-is-straight? connection)
         nconc (when delta?
             (gensym-list (gensym-cons connection delta?)))))
     ;; These must be collected before adjusting edges since
     ;; adjusting edges invalidates connection-is-straight?
    (new-left? nil)
    (new-top? nil)
    (new-right? nil)
    (new-bottom? nil))

    (if (and delta-width x-magnification?)
    (setq delta-width (magnify delta-width x-magnification?)))
    (if (and delta-height y-magnification?)
    (setq delta-height (magnify delta-height y-magnification?)))
    (multiple-value-setq
      (rotated-delta-width rotated-delta-height)
      (rotate-point-in-line-drawing-description
    reflection-and-rotation? 0 0 
    (or delta-width 0)
    (or delta-height 0)))
    (case reflection-and-rotation?
      ((nil normal reflected-clockwise-270)
       (if (not (=w rotated-delta-width 0))
       (setq new-right? (+w (right-edge-of-block entity) rotated-delta-width)
         sides-to-shift (gensym-cons 'right sides-to-shift)))
       (if (not (=w rotated-delta-height 0))
       (setf new-bottom? (+w (bottom-edge-of-block entity) rotated-delta-height)
         sides-to-shift (gensym-cons 'bottom sides-to-shift))))
      ((clockwise-90 reflected)
       (if (not (=w rotated-delta-width 0))
       (setq new-left? (+w (left-edge-of-block entity) rotated-delta-width)
         sides-to-shift (gensym-cons 'left sides-to-shift)))
       (if (not (=w rotated-delta-height 0))
       (setq new-bottom? (+w (bottom-edge-of-block entity) rotated-delta-height)
         sides-to-shift (gensym-cons 'bottom sides-to-shift))))
      ((clockwise-180 reflected-clockwise-90)
       (if (not (=w rotated-delta-width 0))
       (setq new-left? (+w (left-edge-of-block entity) rotated-delta-width)
         sides-to-shift (gensym-cons 'left sides-to-shift)))
       (if (not (=w rotated-delta-height 0))
       (setq new-top? (+w (top-edge-of-block entity) rotated-delta-height)
         sides-to-shift (gensym-cons 'top sides-to-shift))))
      (t 
       (if (not (=w rotated-delta-width 0))
       (setq new-right? (+w (right-edge-of-block entity) rotated-delta-width)
         sides-to-shift (gensym-cons 'right sides-to-shift)))
       (if (not (=w rotated-delta-height 0))
       (setq new-top? (+w (top-edge-of-block entity) rotated-delta-height)
         sides-to-shift (gensym-cons 'top sides-to-shift)))))

    (change-edges-of-block entity new-left? new-top? new-right? new-bottom?)
    
    (loop for side-to-shift in sides-to-shift
      do
      (adjust-connections-according-to-new-edge 
    entity straight-connections-with-deltas
    side-to-shift rotated-delta-width rotated-delta-height))
    (reclaim-gensym-tree straight-connections-with-deltas)
    (reclaim-gensym-list sides-to-shift)))

;; Note that the deltas are magnified by the magnification.  This ensures 
;; reversibility.  For example, suppose that the icon width is changed,
;; then the magnification is changed, then the icon width is changed back
;; to its original value.  If deltas aren't magnified, then connections
;; won't touch icon in correct spot.

;; Note that this is different from magnify-icon since the position on side
;; of connections are not magnified.  Thus, existing icons are changed to
;; look like newly created icons of the class.

;; Consider abstracting a function get-rotated-side-given-original-side-and-rotation.




;;; The function `flush-icon-caches-and-redraw-instances' discards any cached
;;; icon renderings and redraws all affected instances.  It should be called
;;; when, even though the icon description has not changed, its "meaning" has.
;;; For example, when an image referenced by name in the icon description
;;; acquires new data, affected icons must be redrawn.

(defun flush-icon-caches-and-redraw-instances (class-definition)
  (let ((preserve-non-default-icon-colors-or-variables? t))
    (update-icon-description (icon-description-for-class? class-definition)
                 class-definition)))




;;; `Slot-descriptions-are-equivalent-p' replaces the EQ test for slot
;;; descriptions that was in force under single inheritance.  For multiple
;;; inheritance, both system-defined and user-defined slot descriptions are
;;; copied when there is an addition or an update.

(defun slot-descriptions-are-equivalent-p
    (slot-description-1 slot-description-2)
  (or (eq slot-description-1 slot-description-2)
      (and (eq (unique-slot-name slot-description-1)
           (unique-slot-name slot-description-2))
       (eq (defining-class slot-description-1)
           (defining-class slot-description-2))
       (slot-value-equal-p (slot-init-form slot-description-1)
                   (slot-init-form slot-description-2))
       (equal (slot-type-specification slot-description-1)
          (slot-type-specification slot-description-2))
       (equal (slot-features slot-description-1)
          (slot-features slot-description-2)))))




;;; `Update-slot-description-for-system-defined-class' updates the
;;; slot-init-form of a system-defined slot-description.  If system-class is the
;;; defining class for the class-level-slot-description, it sets the
;;; slot-init-form component of it to the new slot-init-form; otherwise it makes
;;; a new slot-description with system-class as the defining-class component and
;;; slot-init-form as the new slot-init-form component.  For the inferior
;;; classes of system-class, if the existing slot-description is eq to
;;; class-level-slot-description, it is replaced by the new slot description
;;; made for system-class.  This is not intended to be used when there is a
;;; current kb, i.e., when there are instances.
;;;
;;; Features, if non-nil, are prepended to the existing a-list of features,
;;; effectively overriding them.

(defun update-slot-description-for-system-defined-class
    (system-class pretty-slot-name slot-init-form &optional features)
  (let* ((class-level-slot-description
       (get-slot-description
         pretty-slot-name
         (slot-descriptions (class-description system-class))))
     (defining-class (defining-class class-level-slot-description))
     (new-slot-description?
       (when (or (not (eq system-class defining-class))
             features)
         (make-slot-description
           pretty-slot-name system-class system-class
           (slot-type-specification class-level-slot-description)
           slot-init-form (vector-slot-index? class-level-slot-description) nil
           (if features
           (append      ; could just replace as appropriate
             features       ;   to save a few conses
             (slot-features class-level-slot-description))
           (slot-features class-level-slot-description))
           t))))

    (when new-slot-description?
      (setf (slots-local-to-class (class-description system-class))
        (cons pretty-slot-name
          (slots-local-to-class (class-description system-class)))))

    (if new-slot-description?
    
    (loop for system-subclass being each unoptimized-subclass of system-class
          for class-description = (class-description system-subclass)
          for existing-slot-description =
                (get-slot-description
              pretty-slot-name (slot-descriptions class-description))
          do
      (when (eq existing-slot-description class-level-slot-description)
        (setf (car (memq existing-slot-description
                 (slot-descriptions class-description)))
          new-slot-description?)
        (when (eq system-subclass system-class)
          (add-slot-description-to-hash-table
        new-slot-description? class-description))))
        
    (setf (slot-init-form class-level-slot-description) slot-init-form))))




;;; The macro `slot-value-conforms-to-type-specification-p' will return non-null
;;; when the slot-value conforms to a slot-type-specification.  It takes care of
;;; converting slot constants to evaluation values which is what type-specification-
;;; type-p expects.

(defun slot-value-conforms-to-type-specification-p (slot-value slot-type-specification)
  (if (slot-constantp slot-value)
      (let ((evaluation-value
          (cast-slot-constant-into-evaluation-value slot-value)))
    (prog1 (type-specification-type-p
         evaluation-value slot-type-specification)
      (reclaim-if-evaluation-value evaluation-value)))
      (type-specification-type-p slot-value slot-type-specification)))

(defun check-initial-value-of-variable-or-parameter (compiled-value overrides definition)
  (let* ((stored-data-type
      (get-data-type-of-variable-or-parameter-from-frame definition overrides))
     (data-type ; see type-specification-of-variable-or-parameter-value
      (cond ((symbolic-type-specification-subtype-p stored-data-type 'datum)
         stored-data-type)
        ((number-subtype-p stored-data-type)
         'number)
        (t
         'datum))))
    (or (slot-value-conforms-to-type-specification-p compiled-value data-type)
    (and (eq data-type 'truth-value)
         (or (eq compiled-value 'true)
         (eq compiled-value 'false)))
    (and (eq data-type 'symbol)
         (null compiled-value)))))

;;; See get-slot-init-form-for-override-value for the conversion to slot-init-form.

(defun get-data-type-of-variable-or-parameter-from-frame (frame &optional supplied-overrides)
  (fix-data-type
   (cond ((of-class-p frame 'definition)
      (let ((overrides (or supplied-overrides (default-overrides frame))))
        (or (second (assq 'data-type-of-variable-or-parameter overrides))
        (let ((data-type-sd
               (slot-description-from-superior-class
            'data-type-of-variable-or-parameter
            frame)))
          (when data-type-sd
            (slot-init-form data-type-sd))))))
     ((of-class-p frame 'variable-or-parameter)
      (data-type-of-variable-or-parameter-function frame)))))

(defun get-allow-no-value-of-variable-or-parameter-from-frame (frame)
  (cond ((of-class-p frame 'definition)
     (not (memq 'parameter (class-inheritance-path-of-definition frame))))
    ((of-class-p frame 'parameter)
     nil)
    (t
     t)))



;;; `Update-slot-description' is called when a user makes a change to an
;;; attribute in the class specific attributes component of a definition and
;;; that change does not alter the attribute name, when there is a change to
;;; the slot-init-form due to a default override or the user putting a
;;; different value in a user-editable system slot, or when the user reverts a
;;; user-edtiable system slot to none.

;;; When this function is called from change-attribute-in-definition the
;;; default overrides on user-defined slots have been removed.

;;; A new slot description is made for the user-class as well as for each inferior
;;; class when the inferior-class slot description has the same slot init form as
;;; the user-class slot description.  The previous slot descriptions are
;;; reclaimed.

;; Reverting-to-superior? is t when called for the following reasons:
;;    (1) The icon-description is reverting to that of the most-specific
;;          superior.
;;    (2) These default message properties are reverting to those
;;          of the most-specific-superior.
;;            default-text-box-format-name
;;            text-cell-plist-for-text-box
;;            minimum-width-of-text-box
;;            minimum-height-of-text-box
;;   (3) When a default override is removed from a system-defined or a
;;       user-defined slot.

(defun update-slot-description
    (user-class user-class-slot-description slot-type-specification
        slot-init-form slot-features reverting-to-superior?
        called-from-change-attribute-in-definition?)
  (let* ((pretty-slot-name (pretty-slot-name user-class-slot-description))
     (defining-class (defining-class user-class-slot-description))
     (unique-slot-name (unique-slot-name user-class-slot-description))
     (user-class-unchanged-slot-init-form
       (slot-init-form user-class-slot-description))
     (changed-slot-type-specification?
       (unless reverting-to-superior?
         (not (equal slot-type-specification
             (slot-type-specification
               user-class-slot-description)))))
     (inherited-slot-description?
       (when reverting-to-superior?
         (slot-description-of-most-specific-superior-refining-slot
           (class-inheritance-path (class-description user-class))
           user-class-slot-description)))
     (slot-is-frame-flags? (eq pretty-slot-name 'frame-flags))
     (slot-descriptions-to-reclaim? nil)
     (check-initial-value-with-data-type?
       (and (eq pretty-slot-name 'initial-value-of-variable-or-parameter)
        (or (and (subclassp user-class 'quantitative-variable)
             (not (subclassp user-class 'integer-variable))
             (not (subclassp user-class 'float-variable)))
            (and (subclassp user-class 'quantitative-parameter)
             (not (subclassp user-class 'integer-parameter))
             (not (subclassp user-class 'float-parameter)))))))
    #+development
    (unless (class-description-is-user-defined-p (class-description user-class))
      (cerror "definitions" "bug in update-slot-description"))
    
    (loop for subclass being each subclass of user-class
      for subclass-description = (class-description subclass)
      for subclass-slot-descriptions = (slot-descriptions subclass-description)
      for unchanged-class-level-slot-description = (get-slot-description
                             unique-slot-name
                             subclass-slot-descriptions)
      for unchanged-slot-description-owner-class =
        (owner-class unchanged-class-level-slot-description)
      for unchanged-slot-init-form =
        (slot-init-form unchanged-class-level-slot-description)
      for class-inherited-slot-description? =
        (unless (class-has-override-on-slot-p
              subclass-description unique-slot-name)
          (slot-description-of-most-specific-superior-refining-slot
        (class-inheritance-path subclass-description)
        unchanged-class-level-slot-description))
      do
      (decache-cached-class-data subclass)
      (let* ((new-slot-description?
          (cond ((eq subclass user-class)
             (cond (reverting-to-superior?
                (make-slot-description
                  pretty-slot-name defining-class subclass
                  (slot-type-specification inherited-slot-description?)
                  (slot-init-form inherited-slot-description?)
                  (vector-slot-index? inherited-slot-description?)
                  (user-vector-slot-index?
                unchanged-class-level-slot-description)
                  (slot-features inherited-slot-description?)))
               (t (make-slot-description
                pretty-slot-name defining-class subclass
                slot-type-specification
                slot-init-form
                (vector-slot-index?
                  unchanged-class-level-slot-description)
                (user-vector-slot-index?
                  unchanged-class-level-slot-description)
                slot-features))))
            (t
             (cond (called-from-change-attribute-in-definition?
                (make-slot-description
                  pretty-slot-name defining-class subclass
                  slot-type-specification
                  slot-init-form
                  nil
                  (user-vector-slot-index?
                unchanged-class-level-slot-description)
                  slot-features))
               ((and class-inherited-slot-description?
                 (not (slot-descriptions-are-equivalent-p
                    unchanged-class-level-slot-description
                    class-inherited-slot-description?)))
                (make-slot-description
                  pretty-slot-name defining-class subclass
                  (slot-type-specification class-inherited-slot-description?)
                  (slot-init-form class-inherited-slot-description?)
                  (vector-slot-index? class-inherited-slot-description?)
                  (user-vector-slot-index? unchanged-class-level-slot-description)
                  (slot-features class-inherited-slot-description?)))
               ;; This case occurs during kb merging when a subclass of user-class
               ;; has a default-override on the slot but it has not yet been
               ;; processed.
               ((member unchanged-slot-description-owner-class
                    slot-descriptions-to-reclaim? :test 'car-eq)
                (let ((new-owner-class-slot-description
                   (get-slot-description
                     unique-slot-name
                     (slot-descriptions
                       (class-description
                     unchanged-slot-description-owner-class)))))
                  (make-slot-description
                pretty-slot-name defining-class subclass
                (slot-type-specification new-owner-class-slot-description)
                (slot-init-form new-owner-class-slot-description)
                (vector-slot-index? new-owner-class-slot-description)
                (user-vector-slot-index? unchanged-class-level-slot-description)
                (slot-features new-owner-class-slot-description))))
               (t nil)))))
         (new-slot-init-form?
           (if new-slot-description?
           (slot-init-form new-slot-description?)
           (slot-init-form unchanged-class-level-slot-description))))

    ;; If user-defined slots were still implemented as lookup slots, or if
    ;; system-defined slots had type specifications, it would be necessary
    ;; to reclaim non-default instance attribute values here before the new
    ;; slot description replaces the old.

    (when new-slot-description?
      (setf (car (get-appropriate-slot-descriptions-cons
               unique-slot-name (slot-descriptions subclass-description)))
        new-slot-description?)
      (delete-slot-description-from-hash-table
        unchanged-class-level-slot-description subclass-description)
      (add-slot-description-to-hash-table
        new-slot-description? subclass-description)

      (when (eq unchanged-slot-description-owner-class subclass)
        (setq slot-descriptions-to-reclaim?
          (nconc slot-descriptions-to-reclaim?
             (frame-list
               (frame-cons
                 subclass unchanged-class-level-slot-description))))))

    (cond (slot-is-frame-flags?
           (set-appropriate-instance-frame-flags-for-update-slot-description
         subclass unchanged-slot-init-form new-slot-init-form?
         unchanged-class-level-slot-description))
          ((eq pretty-slot-name 'history-specification-for-simulation-subtables?)
           (set-simulation-stored-history-spec-for-update-slot-description
         subclass unchanged-slot-init-form new-slot-init-form?))
          (t
           (loop with strict-class-instances-without-recursive-subframes
             = (loop for instance being each strict-class-instance of subclass
                 collect instance using frame-cons)
             for instance in
             strict-class-instances-without-recursive-subframes
             do
           ;; A check for recycled frames is necessary in case the subframe
           ;; is of the same class as the parent frame.
           (when (frame-in-use-p instance)
             (let* ((old-slot-value
                  ;; Use the unchanged class-level slot-description so
                  ;; that default lookup slot values will be correct.
                  (get-slot-description-value-macro
                instance unchanged-class-level-slot-description)))
               (when (or (eq old-slot-value unchanged-slot-init-form)
                 (eq old-slot-value user-class-unchanged-slot-init-form)
                 (and changed-slot-type-specification?
                      (not (slot-value-conforms-to-type-specification-p
                         old-slot-value slot-type-specification))))
             (unless (and check-initial-value-with-data-type?
                      (incompatible-initial-value-and-data-type-p
                    new-slot-init-form?
                    (get-data-type-of-variable-or-parameter-from-frame instance)))
               (let* ((slot-description
                    (get-slot-description
                      unique-slot-name subclass-slot-descriptions))
                  (value-to-set
                    (if (slot-init-form-needs-evaluation? new-slot-init-form?)
                    (let ((instantiate-class?
                        (if (user-defined-class-p subclass)
                            (class-in-attribute-conforms-to-type-p
                              slot-description subclass t)
                            t)))
                      (if instantiate-class?
                          (let ((frame-being-made instance))
                        (eval-slot-init-form new-slot-init-form?))
                          nil))
                    new-slot-init-form?)))
                 ;; Set the instance values that are EQ to the unchanged-slot-
                 ;; init-form to nil so that change-slot-value will not reclaim
                 ;; them.
                 (when (and (or (eq old-slot-value unchanged-slot-init-form)
                        (eq old-slot-value
                        user-class-unchanged-slot-init-form))
                    (not (integerp old-slot-value))
                    (not (symbolp old-slot-value)))
                   (set-slot-description-value-without-noting
                 instance slot-description nil))
                 ;; Note that frames that are to be deleted as slot values
                 ;; have this done by put-attribute-description-value, which
                 ;; must eventually be called in the user-defined slot case.
                 (change-slot-description-value
                   instance slot-description value-to-set))))))
               finally (reclaim-frame-list
                 strict-class-instances-without-recursive-subframes))))))

    (when slot-descriptions-to-reclaim?
      (reclaim-list-of-slot-descriptions slot-descriptions-to-reclaim?)
      (reclaim-frame-tree slot-descriptions-to-reclaim?))))




;;; `Update-name-of-user-class' New-class is a symbol for which an
;;; application of the predicates classp and potential-class-p both
;;; return nil, and where old-class is the name of a class (for which
;;; the application of classp returns non nil), changes the name of the
;;; old class, old-class, to that of the new class name.  This is called
;;; only when the class already exists.

;; This is presently called only from the slot putter code for name-of-
;; defined-class when old-class is defined. (12/10/93 ghw)

(defun update-name-of-user-class (new-class old-class)
  (let* ((class-definition (class-definition old-class))
         (direct-superior-classes (direct-superior-classes old-class))
         (class-description (class-description old-class))
         (instances-specific-to-this-class
          (instances-specific-to-this-class old-class))
         junction-block-class
         junction-block-definition)
    (decache-cached-class-data old-class)
    (setf (class-description new-class) class-description)
    (setf (class-definition new-class) class-definition)
    (setf (instances-specific-to-this-class new-class)
      instances-specific-to-this-class)
    (setf (instances-specific-to-this-class-tail-pointer new-class)
      (instances-specific-to-this-class-tail-pointer old-class))
    (setf (inferior-classes new-class) (inferior-classes old-class))
    (setf (direct-superior-classes new-class)
      (direct-superior-classes old-class))

    (loop with attribute-descriptions =
        (class-specific-attributes class-definition)
      for attribute-description in attribute-descriptions
      as attribute-name = (attribute-name attribute-description)
      as values = (attribute-range attribute-description)
      do
      (undeclare-implied-attribute old-class attribute-name values nil)
      (declare-implied-attribute new-class attribute-name values nil))

    (analyze-compiled-items-for-consistency new-class)
    (analyze-compiled-items-for-consistency old-class)
    
    (loop for direct-superior in direct-superior-classes
      do
      (setf (inferior-classes direct-superior)
        (class-description-cons new-class
            (delete-class-description-element
              old-class (inferior-classes direct-superior)))))
    
    (setf (class-name-of-class-description class-description) new-class)
    
    (update-class-in-connections old-class new-class)
    (setf (definition-state new-class) 'being-redefined)

    ;; Update the direct-superior-classes property and the direct-superiors-of-
    ;; defined-class slot for inferior classes.
    (loop for inferior-class in (inferior-classes new-class)
      for inferior-class-definition = (class-definition inferior-class) 
      for direct-superior-classes-of-inferior =
            (direct-superior-classes inferior-class)
      for cons-holding-old-class-in-direct-superior-classes =
            (memq old-class direct-superior-classes-of-inferior)
      for direct-superiors-of-defined-class =
            (direct-superiors-of-defined-class inferior-class-definition)
      for cons-holding-old-class-in-direct-superiors-of-defined-class
            = (memq old-class direct-superiors-of-defined-class)
      do
      (setf (car cons-holding-old-class-in-direct-superior-classes) new-class)
      (setf (car cons-holding-old-class-in-direct-superiors-of-defined-class)
        new-class)
      (update-representations-of-slot-value
    inferior-class-definition 'direct-superiors-of-defined-class))

    ;; For all subclasses, fix up the class inheritance paths on the class
    ;; description and on the class definition, and change the owner class
    ;; element of method tables.
    (loop for class being each subclass of new-class
      for class-definition = (class-definition class)
      for class-description = (class-description class)
      for method-table-of-class-description =
            (method-table-of-class-description class-description)
      for full-hash-table-class = (full-hash-table-class class-description)
      for class-inheritance-path-of-description =
            (class-inheritance-path (class-description class))
      for cons-holding-old-class-on-class-inheritance-path-of-description
            = (memq old-class class-inheritance-path-of-description)
      for class-inheritance-path-of-definition =
            (class-inheritance-path-of-definition class-definition)
      ;; This cons will be nil for the new-class level definition class
      ;; inheritance path because it is set in the slot putter code.
      for cons-holding-old-class-on-class-inheritance-path-of-definition?
            = (memq old-class class-inheritance-path-of-definition)
      for class-description-inheritance-path? =
            (class-description-inheritance-path-internal class-description)
      do
      (decache-cached-class-data class)
      (when (eq (owner-class-of-method-table method-table-of-class-description)
        old-class)
    (set-owner-class-of-method-table
      method-table-of-class-description new-class))
      (when (eq full-hash-table-class old-class)
    (setf (full-hash-table-class class-description) new-class))
      (setf (car cons-holding-old-class-on-class-inheritance-path-of-description)
        new-class)
      (when cons-holding-old-class-on-class-inheritance-path-of-definition?
    (setf (car cons-holding-old-class-on-class-inheritance-path-of-definition?)
          new-class))
      (update-representations-of-slot-value
    class-definition 'class-inheritance-path-of-definition)
      (when class-description-inheritance-path?
    (reclaim-class-description-list class-description-inheritance-path?)
    (setf (class-description-inheritance-path-internal class-description) nil)))

    ;; Update the slot descriptions defined for old-class.
    (let ((new-slots-local-to-class-list nil)
      (old-slots-local-to-class (slots-local-to-class class-description))
      (class-specific-attributes (class-specific-attributes class-definition)))
      (loop for old-class-unique-slot-name in old-slots-local-to-class
        for pretty-slot-name =
            (pretty-slot-name (get-slot-description
                    old-class-unique-slot-name
                    (slot-descriptions class-description)))
        for new-class-unique-slot-name =
              (make-unique-slot-name-symbol new-class pretty-slot-name)
        do
    (let* ((corresponding-attribute-description-cons?
         (member pretty-slot-name class-specific-attributes
             :test 'car-eq))
           (attribute-range
         (when corresponding-attribute-description-cons?
           (attribute-range
             (car-of-cons corresponding-attribute-description-cons?)))))
      (undeclare-implied-attribute
        old-class old-class-unique-slot-name attribute-range t)
      (declare-implied-attribute
        new-class new-class-unique-slot-name attribute-range t))
    (setq new-slots-local-to-class-list
          (class-description-cons
        new-class-unique-slot-name new-slots-local-to-class-list))
    (loop for class being each subclass of new-class
          for class-description = (class-description class)
          for class-level-slot-description? =
            (get-slot-description
          old-class-unique-slot-name
          (slot-descriptions class-description))
          do
      (when class-level-slot-description?
        (delete-slot-description-from-hash-table
          class-level-slot-description? class-description)
        (setf (unique-slot-name class-level-slot-description?)
          new-class-unique-slot-name)
        (setf (defining-class class-level-slot-description?) new-class)
        (add-slot-description-to-hash-table
          class-level-slot-description? class-description))))
      (reclaim-class-description-list old-slots-local-to-class)
      (setf (slots-local-to-class class-description)
        new-slots-local-to-class-list))

    ;; Change the owner-class components of slot-descriptions and
    ;; icon-descriptions.
    (loop for class being each subclass of new-class
      do
      (loop for slot-description in (slot-descriptions (class-description class))
        do
    (when (eq (owner-class slot-description) old-class)
      (setf (owner-class slot-description) new-class))
    (when (eq (pretty-slot-name slot-description) 'icon-description)
      (let ((slot-init-form (slot-init-form slot-description)))
        (when (and (icon-description-p slot-init-form)
               (eq (icon-owner-class-function slot-init-form) old-class))
          (set-icon-owner-class new-class slot-init-form))))))
    
    (setf (definition-state new-class) 'defined)
    (setf (class-description old-class) nil)
    (setf (class-definition old-class) nil)
    (setf (instances-specific-to-this-class old-class) nil)
    (setf (instances-specific-to-this-class-tail-pointer old-class) nil)
    (setf (inferior-classes old-class) nil)
    (setf (direct-superior-classes old-class) nil)

    (when old-class
      (loop for potential-definition in
              (potential-inferior-class-definitions old-class)
        for direct-superiors-of-defined-class =
              (direct-superiors-of-defined-class potential-definition)
        for direct-superiors-cons =
              (memq old-class direct-superiors-of-defined-class)
        for class-inheritance-path-of-definition? =
              (class-inheritance-path-of-definition potential-definition)
        for inheritance-path-cons? =
              (and class-inheritance-path-of-definition?
               (memq old-class class-inheritance-path-of-definition?))
        do
    (setf (car direct-superiors-cons) new-class)
    (update-representations-of-slot-value
      potential-definition 'direct-superiors-of-defined-class)
    (when inheritance-path-cons?
      (setf (car inheritance-path-cons?) new-class)
      (update-representations-of-slot-value
        potential-definition 'class-inheritance-path-of-definition?))))

    (when (and (memq 'connection (class-inheritance-path class-description))
           (setq junction-block-class
             (class-slot-description-value
               'junction-block-class-for-class new-class))
           (setq junction-block-definition
             (get-instance-with-name-if-any
               'class-definition junction-block-class))
           (null (superblock? junction-block-definition))
           (eq junction-block-class
           (intern-text-string
             (tformat-text-string
               "JUNCTION-BLOCK-FOR-~A" old-class))))
      (let ((new-name-for-junction-block-class
          (intern-text-string
        (tformat-text-string
          "JUNCTION-BLOCK-FOR-~A" new-class))))
    (when (frame-of-class-p class-definition 'connection-definition)
      (change-slot-value
        class-definition 'junction-block-class-for-connection
        new-name-for-junction-block-class)
      (update-representations-of-slot-value
        class-definition 'junction-block-class-for-connection))
    (update-junction-block-class-for-class
      new-class new-name-for-junction-block-class)
    (change-slot-value junction-block-definition
               'name-of-defined-class
               new-name-for-junction-block-class)))

    (install-items-of-class-in-model new-class)

    ;; update instances (if any):   new. (MHD/GHW 11/18/93)
    (update-attribute-tables-for-instances new-class nil)))



(defun update-class-in-connections (old-class new-class)
  (loop for block being each class-instance of 'block
        do
    (loop for connection being each output-connection of block
          do
      (when (eq (connection-frame-or-class connection) old-class)
        (setf (connection-frame-or-class connection) new-class)))))




;;; The function `incompatible-initial-value-and-data-type-p' returns t when the
;;; initial-value is a float and the data type is integer or the initial-value
;;; is an integer and the data-type is float; otherwise it returns nil.  It is
;;; used for checking the initial values and data types of
;;; quantitative-parameters and quantitative-variables.

(defun incompatible-initial-value-and-data-type-p (initial-value data-type)
  (or (and (managed-float-p initial-value)
       (eq data-type 'integer))
      (and (integerp initial-value)
       (eq data-type 'float))))




;;; Types that are valid in slot-constants are all numeric types, text and truth-value.
;;; The car of a parameter must be a number or string presently.

(defmacro slot-constant-type-p (type)
  `(let ((type ,type))
     (and (symbolp type)
      (or (number-subtype-p type) (memq type '(text truth-value))))))

;; Consider making this a function, and have functions for making init-form
;; and entire slot-description!



(def-global-property-name date-format-description)

;;; `Make-slot-features-for-user-defined-slot' conses up the slot features prior
;;; to making a slot description for a user-defined slot.  It is up to the
;;; caller to reclaim these conses after the slot description has been made.

(defun-simple make-slot-features-for-user-defined-slot (attribute-description)
  (let* ((attribute-type-specification
       (attribute-type-specification attribute-description))
     (attribute-type-modifications
       (attribute-type-modifications attribute-description))
     (format-override? (assq 'format-override attribute-type-modifications))
     (date-format? (when (and format-override? (symbolp (second format-override?)))
             (date-format-description (second format-override?))))
     (attribute-initial-type (attribute-initial-type attribute-description))
     slot-features)
    ;; The following form fixes up in-house 5.0 kbs that were given unlisted
    ;; sequence and structure attribute-initial-value components.  (ghw 1/16/97)
    (unless (class-type-specification-p attribute-type-specification)
      (when (or (eq attribute-initial-type 'sequence)
        (eq attribute-initial-type 'structure))
    (setf (attribute-initial-type attribute-description)
          (slot-value-list attribute-initial-type))))
    (setq slot-features
      (cond
        ((equal attribute-type-specification '(or item-or-datum (no-item)))
         (frame-list
           (frame-list 'type 'item-or-datum-or-no-item-attribute)
           (frame-list 'class-of-optional-subframe 'object)))
        ((and (consp attribute-type-specification)
          (eq (car-of-cons attribute-type-specification) 'class))
         (frame-list
           (frame-list 'type 'item-or-datum-attribute)
           (frame-list 'class-of-optional-subframe
               (cadr attribute-type-specification))))
        (t
         (frame-list
           (frame-list
         'type
         (cond
           ((symbolic-type-specification-p attribute-type-specification)
            (case attribute-type-specification
              (datum 'datum-attribute)
              (number
               (case (second format-override?)
             (interval 'interval-attribute)
             (time-stamp 'time-stamp-attribute)
             (ddd.dddd-format 'ddd.dddd-format-attribute)
             (t
              (if date-format?
                  (date-format-quantity-attribute-function date-format?)
                  'number-attribute))))
              (integer
               (case (second format-override?)
             (interval 'interval-integer-attribute)
             (time-stamp 'time-stamp-integer-attribute date-format?)
             (ddd.dddd-format 'ddd.dddd-format-integer-attribute)
             (t
              (if date-format?
                  (date-format-integer-attribute-function date-format?)
                  'integer-attribute))))
              (float
               (case (second format-override?)
             (interval 'interval-float-attribute)
             (time-stamp 'time-stamp-float-attribute)
             (ddd.dddd-format 'ddd.dddd-format-float-attribute)
             (t
              (if date-format?
                  (date-format-float-attribute-function date-format?)
                  'float-attribute))))
              (truth-value 'truth-value-attribute)
              (symbol 'symbol-attribute)
              (text
               (case (second format-override?)
             (free-text 'free-text-attribute)
             (t 'text-attribute)))
              (item-or-datum 'item-or-datum-attribute)
              (t
               #+development
               (cerror
             "definitions"
             "error1 in make-slot-features-for-user-defined-slot")
               'datum-attribute)))
           ((structure-type-specification-p attribute-type-specification)
            'structure-attribute)
           ((sequence-type-specification-p attribute-type-specification)
            'sequence-attribute)
           (t
            (cond
              ((or (eq attribute-type-specification 'sequence)
               (eq attribute-type-specification 'structure))
               ;; The following form fixes up in-house 5.0 kbs that were given
               ;; unlisted sequence and structure attribute-type-specification
               ;; components.  (ghw 1/16/97)
               (setf (attribute-type-specification attribute-description)
                 (slot-value-list attribute-type-specification))
               (if (eq attribute-type-specification 'sequence)
               'structure-attribute
               'sequence-attribute))
              (t
               #+development
               (cerror
             "definitions"
             "error2 in make-slot-features-for-user-defined-slot")
               'datum-attribute)))))))))
    (when attribute-type-modifications
      (setq slot-features
        (nconc slot-features
           (copy-tree-using-frame-conses
             attribute-type-modifications))))
    slot-features))




;;; `Add-user-defined-slot-to-user-class' is called when a user adds an
;;; attribute to the attribute descriptions for class slot of a definition.
;;; This function takes care of altering the class descriptions of the defining
;;; class and all of its inferior classes.  The necessary changes to class
;;; descriptions are: the new attribute name is added to the slots local to
;;; class component of the defining class; and a slot description is made for
;;; the added attribute and added to the slot descriptions and slot
;;; descriptions hash table of the defining class and all of its inferior
;;; classes.  This function does not deal with instance changes; this is left
;;; to adjust-slot-description-indices-and-instances-for-attribute-changes.

(defun add-user-defined-slot-to-user-class
    (user-class-definition attribute-description)
  
  (let* ((user-class (name-of-defined-class user-class-definition))
     (attribute-name 
       (attribute-name attribute-description))
     (user-class-class-description (class-description user-class))
     (user-class-slot-description?
       (get-slot-description
         attribute-name (slot-descriptions user-class-class-description)
         user-class))
     (attribute-initial-type? (attribute-initial-type attribute-description))
     (attribute-type-specification
       (attribute-type-specification attribute-description))
     (slot-constant? (slot-constant-type-p attribute-initial-type?))
     (slot-features
       (make-slot-features-for-user-defined-slot attribute-description))
     (slot-init-form
       (if slot-constant?
           (make-slot-constant
         (copy-for-slot-value
           (attribute-initial-value attribute-description)) attribute-initial-type? t)
           (attribute-initial-value attribute-description))))

    #-development (declare (ignore user-class-slot-description?))

    #+development
    (when (and user-class-slot-description?
           (eq (defining-class user-class-slot-description?)
           user-class))
      (cerror "definitions" "error in add-user-defined-slot-to-user-class"))

    (loop for class being each subclass of user-class
      for class-description = (class-description class)
      for slot-descriptions = (slot-descriptions class-description)
      for new-slot-description =
        (make-slot-description
          attribute-name user-class class attribute-type-specification
          slot-init-form nil t slot-features)
      for preceding-slot-description =
        (preceding-slot-description-for-positioning-slot-addition
          class user-class attribute-name)
      for slot-descriptions-cons-after-which-to-insert =
        (get-appropriate-slot-descriptions-cons
          (unique-slot-name preceding-slot-description)
          slot-descriptions)
      do
      (decache-cached-class-data class)
      (setf (cdr slot-descriptions-cons-after-which-to-insert)
        (class-description-cons new-slot-description
                    (cdr slot-descriptions-cons-after-which-to-insert)))
      (when (eq class user-class)
    (let ((class-specific-attributes
        (class-specific-attributes user-class-definition)))
      (if (eq attribute-name
          (attribute-name (car-of-cons class-specific-attributes)))
          (setf (slots-local-to-class user-class-class-description)
            (class-description-cons
              (unique-slot-name new-slot-description)
              (slots-local-to-class user-class-class-description)))
          (let* ((attribute-after-which-to-insert
               (loop for sublist on class-specific-attributes
                 when (eq attribute-name
                      (attribute-name (cadr sublist)))
                   return (attribute-name (car-of-cons sublist))))
             (unique-name-after-which-to-insert
               (unique-slot-name
             (get-slot-description-of-class-description
               attribute-after-which-to-insert class-description)))
             (slots-local-to-class (slots-local-to-class class-description))
             (cons-after-which-to-insert
               (loop for sublist on slots-local-to-class
                 when (eq unique-name-after-which-to-insert
                      (car sublist))
                   return sublist)))
        (setf (cdr cons-after-which-to-insert)
              (class-description-cons
            (unique-slot-name new-slot-description)
            (cdr cons-after-which-to-insert)))))))
      (add-slot-description-to-hash-table
    new-slot-description class-description))
    (when (and slot-constant? (consp slot-init-form))
      (reclaim-initial-slot-value slot-init-form))
    (reclaim-frame-tree slot-features)))




;;; `Add-slot-description-to-hash-table' adds a slot description to the hash
;;; table of the class description when a user has added an attribute to the
;;; class-specific-attributes slot of a class definition.

;;; See FRAMES1 for a discussion of full and sparse hash tables.

(defun-void add-slot-description-to-hash-table
    (slot-description class-description)
  (if (class-description-has-full-hash-table-p class-description)
      (add-slot-description-to-full-hash-table
    slot-description class-description)
      (add-slot-description-to-sparse-hash-table-if-appropriate
    slot-description class-description)))

(defun-void add-slot-description-to-full-hash-table
    (slot-description class-description)
  (let* ((pretty-slot-name (pretty-slot-name slot-description))
     (class-inheritance-path (class-inheritance-path class-description))
     (slot-descriptions-hash-table
       (slot-descriptions-hash-table class-description))
     (hash-table-value-for-pretty-slot-name?
       (get-slot-hash pretty-slot-name slot-descriptions-hash-table)))
    (setf (get-slot-hash
        (unique-slot-name slot-description) slot-descriptions-hash-table)
      slot-description)
    (when (or (null hash-table-value-for-pretty-slot-name?)
          (<f (position
            (defining-class slot-description) class-inheritance-path)
          (position
            (defining-class hash-table-value-for-pretty-slot-name?)
            class-inheritance-path)))
      (setf (get-slot-hash pretty-slot-name slot-descriptions-hash-table)
        slot-description))))

(defun-void add-slot-description-to-sparse-hash-table-if-appropriate
    (slot-description class-description)
  (let* ((class (class-name-of-class-description class-description))
     (hash-table (slot-descriptions-hash-table class-description))
     (unique-slot-name (unique-slot-name slot-description))
     (defining-class (defining-class slot-description))
     (differs-from-superior-slot-description?
       (unless (eq defining-class class)
         (loop for superior in (cdr (class-inheritance-path class-description))
           for superior-slot-description? =
                 (get-slot-description
               unique-slot-name
               (slot-descriptions (class-description superior)))
           until superior-slot-description?
           finally
             (if (eq slot-description superior-slot-description?)
             (return nil)
             (return t))))))
    (when (or (eq defining-class class)
          differs-from-superior-slot-description?)
      (setf (get-slot-hash unique-slot-name hash-table) slot-description)
      (when (user-defined-slot-description-p slot-description)
    (let* ((pretty-slot-name (pretty-slot-name slot-description))
           (existing-pretty-name-slot-description?
         (get-slot-hash pretty-slot-name hash-table)))
      (when (or (null existing-pretty-name-slot-description?)
            (more-specific-class-p
              defining-class
              (defining-class existing-pretty-name-slot-description?)
              (class-inheritance-path class-description)))
        (setf (get-slot-hash pretty-slot-name hash-table) slot-description)))))))


      


;;; `Delete-user-defined-slot' deletes the slot description with pretty-slot-name
;;; and with defining class of user class from all subclasses of user class.

(defun delete-user-defined-slot (user-class pretty-slot-name)
  (let* ((user-class-class-description (class-description user-class))
     (user-class-slot-description
       (get-slot-description-of-class-description
         pretty-slot-name user-class-class-description user-class))
     (unique-slot-name (unique-slot-name user-class-slot-description))
     (slot-descriptions-for-reclamation nil))
    
    #+development
    (unless (and (class-description-is-user-defined-p (class-description user-class))
         (eq (defining-class user-class-slot-description) user-class))
      (cerror "definitions" "bug in delete-attribute-from-user-class"))

    (loop for class being each subclass of user-class
      for slot-description? = nil
      do
      (decache-cached-class-data class)
      (loop for instance being each strict-class-instance of class
        do
    ;; For each class we'll only bother to fetch the slot description if
    ;; there are instances.
    (unless slot-description?
      (setq slot-description?
        (get-slot-description
          unique-slot-name
          (slot-descriptions (class-description class)))))
    ;; Let put-attribute-description-value deal with reclamation and
    ;; deactivation.
    (put-attribute-description-value instance slot-description? nil nil)))
    
    (setf (slots-local-to-class user-class-class-description)
      (delete-class-description-element
        unique-slot-name
        (slots-local-to-class user-class-class-description)))
    (loop for class being each subclass of user-class
      for class-description = (class-description class)
      for slot-description =
            (get-slot-description
          unique-slot-name (slot-descriptions class-description))
      do
      (when (eq (owner-class slot-description) class)
    (setq slot-descriptions-for-reclamation
          (nconc slot-descriptions-for-reclamation
             (frame-list
               (frame-cons class slot-description)))))
      
      (delete-class-description-element-from-slot-descriptions
    slot-description class-description)
      (delete-slot-description-from-hash-table
    slot-description class-description))

    (when slot-descriptions-for-reclamation
      (reclaim-list-of-slot-descriptions slot-descriptions-for-reclamation)
      (reclaim-frame-tree slot-descriptions-for-reclamation))))




;;; `Add-class-feature' adds new-class-feature-in-tree-form to the list
;;; of class features for the class.  If user-class already has such a
;;; feature the new one replaces the old.

(defun add-class-feature
    (user-class new-class-feature-in-class-description-tree-form)
  (let* ((feature-name (car new-class-feature-in-class-description-tree-form))
     (class-description (class-description user-class))
     (class-features (class-features class-description))
     (cons-holding-relevant-class-feature?
       (member feature-name class-features :test 'car-eq))
     (existing-class-feature?
       (and cons-holding-relevant-class-feature?
        (car cons-holding-relevant-class-feature?))))
    (cond (cons-holding-relevant-class-feature?
       (setf (car cons-holding-relevant-class-feature?)
         new-class-feature-in-class-description-tree-form)
       (reclaim-class-description-tree existing-class-feature?))
      (t (setf (class-features class-description)
           (class-description-cons
             new-class-feature-in-class-description-tree-form
             class-features))))))




;;; `Remove-class-feature' removes from the list of class features of
;;; user-class the class-feature of name old-class-feature-name if there
;;; is such a feature.  Otherwise it does nothing.

(defun remove-class-feature (user-class old-class-feature-name)
  (let* ((class-description (class-description user-class))
     (class-features (class-features class-description)))
    (when (feature-assq old-class-feature-name class-features)

    (cond ((eq old-class-feature-name (car (car class-features)))
           (reclaim-class-description-cons 
         (prog1 class-features
            (reclaim-class-description-tree (car class-features))
            (setf (class-features class-description)
                  (cdr class-features)))))
          (t
           (loop for sublist on class-features
             do
         (when (eq old-class-feature-name (car (cadr sublist)))
           (reclaim-class-description-cons
             (prog1 (cdr sublist)
                (reclaim-class-description-tree (cadr sublist))
                (setf (cdr sublist) (cddr sublist)))))))))))




;;; `Frame note writers' for class definitions:



(def-frame-note-writer transient-class-definition (particulars)
  (declare (ignore particulars))
  (tformat "this class definition is transient"))

(def-frame-note-writer inconsistent-instantiate-value (particulars)
  (declare (ignore particulars))
  (tformat "the value of instantiate should be changed to \"no\" because system class inheritance precludes instantiation"))

(def-frame-note-writer undefined-direct-superiors (undefined-classes)
  (write-frame-notes-for-names
    undefined-classes 
    "the direct superior class " "the direct superior classes "
    " is not defined" " are not defined"))

(def-frame-note-writer no-direct-superiors (particulars)
  (declare (ignore particulars))
  (tformat
    "no direct superior classes are specified"))

(def-frame-note-writer no-class-name (particulars)
  (declare (ignore particulars))
  (tformat
    "no class name is specified"))

(def-frame-note-writer class-specific-attribute-is-a-system-slot-name
    (attribute-names-to-display)
  (write-frame-notes-for-names
    attribute-names-to-display
    "the class-specific-attribute " "the class-specific-attributes "
    " is now a reserved G2 attribute. You must rename it before starting G2."
    " are now reserved G2 attributes. You must rename them before starting G2."))

(def-frame-note-writer default-override-on-user-attribute-is-a-system-slot-name
    (attribute-names-to-display)
  (write-frame-notes-for-names
    attribute-names-to-display
    "the attribute initialization for " "the attribute initializations for "
    " uses class-specific-attribute syntax but the name is now a reserved G2 attribute.  You must rename it before starting G2."
    " use class-specific-attribute syntax but the names are now reserved G2 attributes. You must rename them before starting G2."))

(def-frame-note-writer no-corresponding-inherited-attribute-for-override
    (slot-names-to-display)
  (write-frame-notes-for-names
    slot-names-to-display
    "the initialization for " "the initializations for "
    " has no corresponding inherited attribute and cannot be implemented"
    " have no corresponding inherited attributes and cannot be implemented"))

(def-frame-note-writer override-value-is-not-compatible
    (slot-names-to-display)
  (write-frame-notes-for-names
    slot-names-to-display
    "the initialization value for "  "the initialization values for "
    " does not conform to the declared attribute type and will not be implemented"
    " do not conform to the declared attribute types and will not be implemented"))

(def-frame-note-writer override-of-class-level-attribute
    (slot-names-to-display)
  (write-frame-notes-for-names
    slot-names-to-display
    "the initialization for " "the initializations for "
    " has a class-level corresponding attribute and will not be implemented"
    " have class-level corresponding attributes and will not be implemented"))

(def-frame-note-writer attributes-have-more-than-one-override
    (slot-names-to-display)
  (write-frame-notes-for-names
    slot-names-to-display
    "" "the default settings for "
    "" " have the same corresponding attribute and will not be implemented"))

(def-frame-note-writer initial-value-class-incompatible-with-type
    (slot-names-to-display)
  (write-frame-notes-for-names
    slot-names-to-display
    "the initial-value class for the attribute "
    "the initial-value classes for the attributes "
    " is not a subclass of the declared attribute type and will not be instantiated"
    " are not subclasses of the declared attribute types and will not be instantiated"))










;;;; Object State Changing Functions



(defun attempt-circular-path (class superior-class)
  (notify-engineer
    "If ~A were the superior of ~A, that would make the class inheritance ~
     tree circular"
    superior-class class))




;;; `Instantiate-or-uninstantiate-class-in-attributes-when-appropriate'
;;; instantiates or deletes the classes in attributes when a change in the
;;; class hierarchy validates or invalidates the slot.  The possible
;;; symbols for class-status are newly-defined, undefined, name-change,
;;; change-in-inheritance.

(defun instantiate-or-uninstantiate-class-in-attributes-as-appropriate
    (class class-status &optional new-class?)
  (let ((compiled-items-referring-to-this-name
      (compiled-items-referring-to-this-name-function class)))
    (loop for item in compiled-items-referring-to-this-name
      do
      (when (subclassp (class item) 'class-definition)
    
    (loop for attribute-description in (class-specific-attributes item)
          for attribute-type-specification = (attribute-type-specification
                           attribute-description)
          for class-type-specification? = (class-type-specification-p
                          attribute-type-specification)
          for class-type? = (and class-type-specification?
                     (type-specification-class-function
                       attribute-type-specification))
          for attribute-initial-type = (attribute-initial-type
                         attribute-description)
          do
      (when (or (eq attribute-initial-type class) (eq class-type? class)) 
        (let ((class-of-definition (name-of-defined-class item))
          (attribute-name (attribute-name attribute-description)))
          (loop for referencing-class being each subclass of class-of-definition
            for slot-description = (get-slot-description
                         attribute-name
                         (slot-descriptions
                           (class-description
                         referencing-class))
                         class-of-definition)
            for slot-init-form = (slot-init-form slot-description)
            for funcall-value? =
                  ;; there may be an override that is not a funcall form
                  (slot-init-form-needs-evaluation? slot-init-form)
            for class-conforms-to-type? =
                  (class-in-attribute-conforms-to-type-p
                slot-description referencing-class t)
            do
        (when funcall-value?
          (case class-status
            (newly-defined
             (when class-conforms-to-type?
               (loop for instance being each strict-class-instance
                       of referencing-class
                 for slot-value = (get-slot-description-value
                        instance
                        slot-description)
                 do
             (unless slot-value
               (change-slot-description-value
                 instance slot-description
                 (eval-slot-init-form slot-init-form))))))
            (undefined
             (when (and (eq class-type? class)
                (classp attribute-initial-type))
               (loop for instance being each strict-class-instance
                 of referencing-class
                 do
             (change-slot-description-value
               instance slot-description nil))))
            (name-change
             (if (eq attribute-initial-type class)
             (loop for instance being each strict-class-instance
                         of referencing-class
                   for slot-value = (get-slot-description-value
                          instance
                          slot-description)
                   do
               (when (and (framep slot-value)
                      (eq (class slot-value) new-class?))
                 (change-slot-description-value
                   instance slot-description nil)))
             (if class-conforms-to-type?
                 (loop with slot-description-defining-class
                         = (defining-class slot-description)
                   ;; G2 allows objects to have object
                   ;; attributes that have the same class as
                   ;; the parent object, but it limits the
                   ;; nesting to 20 deep.  The most deeply
                   ;; nested object, then, will have a null
                   ;; value for its object attribute.  The
                   ;; code below prevents G2 from trying to
                   ;; slam in an object that will exceed the
                   ;; nesting limit and cause an infinite
                   ;; loop.
                   with recursive-subobjects? =
                           (and (eq attribute-initial-type
                            slot-description-defining-class)
                        (eq referencing-class
                            slot-description-defining-class))
                    for instance being each strict-class-instance
                          of referencing-class
                    for slot-value = (get-slot-description-value
                               instance slot-description)
                    for parent-frame? = (parent-frame instance)
                    do
                (unless (or (and (framep slot-value)
                         (eq (class slot-value)
                             attribute-initial-type))
                        (and recursive-subobjects?
                         ;; This instance is a subobject.
                         parent-frame?
                         (eq (class parent-frame?)
                             referencing-class)
                         (null slot-value)))
                  (change-slot-description-value
                    instance slot-description
                    (eval-slot-init-form
                      (slot-init-form slot-description)))))
                 (loop for instance being each strict-class-instance
                         of referencing-class
                   do
                   (change-slot-description-value
                 instance slot-description nil)))))
            (change-in-inheritance
             (when class-type-specification?
               (cond (class-conforms-to-type?
                  (loop with slot-description-defining-class
                         = (defining-class slot-description)
                    ;; See the name-change case above for a
                    ;; comment about resursive objects.
                    with recursive-subobjects? =
                           (and (eq attribute-initial-type
                            slot-description-defining-class)
                        (eq referencing-class
                            slot-description-defining-class))
                    for instance being each strict-class-instance
                          of referencing-class
                    for slot-value = (get-slot-description-value
                               instance slot-description)
                    for parent-frame? = (parent-frame instance)
                    do
                (unless (or (and (framep slot-value)
                         (eq (class slot-value)
                             attribute-initial-type))
                        (and recursive-subobjects?
                         ;; This instance is a subobject.
                         parent-frame?
                         (eq (class parent-frame?)
                             referencing-class)
                         (null slot-value)))
                  (change-slot-description-value
                    instance slot-description
                    (eval-slot-init-form
                      (slot-init-form slot-description))))))
                 (t  ;; non-type-conforming
                  (loop for instance being each strict-class-instance
                    of referencing-class
                    do
                (change-slot-description-value
                  instance slot-description nil))))))
            (t nil)))))))
    
    (loop for override in (default-overrides item)
          for class-of-definition = (name-of-defined-class item)
          for class-to-instantiate? = (class-to-instantiate-for-override
                        override)
          do
      (when (and (eq class-to-instantiate? class)
             (classp class-of-definition))
        (let* ((name-denotation (car-of-cons override))
           (no-inherited-attribute-for-override?
             (member name-denotation 
                 (get-particulars-of-frame-note-if-any
                   'no-corresponding-inherited-attribute-for-override
                   item)
                 :test 'equal)))
          (unless no-inherited-attribute-for-override?
        (let* ((pretty-slot-name (unqualified-name name-denotation))
               (defining-class (class-qualifier name-denotation))
               (slot-description (get-slot-description
                       pretty-slot-name
                       (slot-descriptions
                         (class-description class-of-definition))
                       defining-class)))
          (when slot-description
            (let* ((implemented-override?
                 (implemented-override-p item override))
               (override-slot-init-form
                 (car-of-cons (second override)))
               (override-value-conforms-to-type?
                 (class-in-attribute-conforms-to-type-p
                   slot-description class-of-definition t
                   override-slot-init-form))
               (list-of-unimplementable-overrides?
                 (add-frame-notes-for-unimplementable-overrides
                   item)))
              (case class-status
            (newly-defined
             (when override-value-conforms-to-type?
               (unless (member override list-of-unimplementable-overrides?
                       :test 'equal)
                 (add-slot-to-inherited-slots-this-class-overrides
                   class-of-definition (unique-slot-name slot-description))
                 (update-slot-description
                   class-of-definition slot-description
                   (slot-type-specification slot-description)
                   override-slot-init-form
                   (slot-features slot-description) nil nil))))
            (undefined
             (when implemented-override?
               (remove-default-override
                 class-of-definition slot-description)))
            (name-change
             (when implemented-override?
               (remove-default-override
                 class-of-definition slot-description)))
            (change-in-inheritance
             (when (class-type-specification-p
                 (slot-type-specification slot-description))
               (cond (override-value-conforms-to-type?
                  (unless implemented-override?
                    (update-slot-description
                      class-of-definition slot-description
                      (slot-type-specification slot-description)
                      override-slot-init-form
                      (slot-features slot-description) nil nil)))
                 (t
                  (when implemented-override?
                    (remove-default-override
                      class-of-definition slot-description))))))
            (t nil))
              (reclaim-frame-list
            list-of-unimplementable-overrides?))))))))))))




;;; `Define-user-class', given a class-definition, causes the class to become
;;; part of the class hierarchy, capable of being subclassed and possibly
;;; instantiated.

;;; This function is called with class definitions that have valid values in the
;;; name-of-defined-class and direct-superiors-of-defined-class slots.  See the
;;; slot-putter code for these slots for validity information.

(defun define-user-class (class-definition)
  (let ((class (name-of-defined-class class-definition)))   
    (loop for superior in (direct-superiors-of-defined-class class-definition)
      do
      (when (or (eq class superior)
        (subclassp superior class))
    (attempt-circular-path class superior))))

  (let* ((class (name-of-defined-class class-definition))
     (class-was-previously-defined? (classp class))
     (previous-direct-superiors?
       (direct-superior-classes class))
     (direct-superiors-of-defined-class
       (direct-superiors-of-defined-class class-definition))
     (class-definition-is-object-definition?
       (frame-of-class-p class-definition 'object-definition))
     (class-inheritance-path-of-definition?
       (class-inheritance-path-of-definition class-definition))
     (foundation-class
       (most-refined-foundation-class-of-direct-superiors
         direct-superiors-of-defined-class))
     (class-inheritance-path
       (if (or previous-direct-superiors?
           (not class-inheritance-path-of-definition?))
           ;; A copy-for-slot-value path list is returned.
           (make-class-inheritance-path-for-user-defined-class
         class direct-superiors-of-defined-class)
           class-inheritance-path-of-definition?))
     (object-class? (memq 'object class-inheritance-path))
     (class-specific-attributes
       (class-specific-attributes class-definition))
     (icon-description-for-class? nil)
     (new-slot-descriptions-for-class nil)
     ;; Note that the following two consing operations are temporary.
     ;; The conses are reclaimed at the end of this function after
     ;; make-slot-description has copied them.
     (slot-features-for-class-slot
       (frame-list (frame-list 'type 'class-instance-header))))

    (when (or previous-direct-superiors?
          (not class-inheritance-path-of-definition?))
      (when class-inheritance-path-of-definition?
    (reclaim-slot-value class-inheritance-path-of-definition?))
      (setf (class-inheritance-path-of-definition class-definition)
        class-inheritance-path))

    (loop for attribute-description in class-specific-attributes
      as attribute-name = (attribute-name attribute-description)
      as attribute-type-specification = (attribute-type-specification attribute-description)
      as attribute-initial-value = (attribute-initial-value attribute-description)
      as attribute-initial-type = (attribute-initial-type attribute-description)
      as attribute-range = (attribute-range attribute-description)
      for slot-constant? = (when (slot-constant-type-p attribute-initial-type)
                 (make-slot-constant
                   (copy-for-slot-value
                     attribute-initial-value)
                   attribute-initial-type t))

      do
      (let ((slot-features
          (make-slot-features-for-user-defined-slot attribute-description)))
    (declare-implied-attribute class attribute-name attribute-range nil)
    (let ((new-slot-description
        (make-slot-description
          attribute-name class class
          (if slot-constant?
              (copy-tree-using-class-description-conses attribute-type-specification)
              attribute-type-specification)
          (if slot-constant?
              slot-constant?
              attribute-initial-value)
          nil t
          (if slot-constant?
              (copy-tree-using-class-description-conses slot-features)
              slot-features)             
          ;; dont copy the init form if it is a slot constant
          slot-constant?)))
      (declare-implied-attribute
        class (unique-slot-name new-slot-description) attribute-range t)
      (setq new-slot-descriptions-for-class
        (nconc
          new-slot-descriptions-for-class
          (class-description-list new-slot-description))))

    (reclaim-frame-tree slot-features)))

    ;; Merge-slot-descriptions-for-user-defined-class will add the inherited
    ;; vector-slot-index and slot-features to the system slot-descriptions.
    (when object-class?
      (setq new-slot-descriptions-for-class
        (nconc
          new-slot-descriptions-for-class
          (class-description-list
        (make-slot-description 
          'attribute-displays-for-class 'object class nil
          (when class-definition-is-object-definition?
            (attribute-displays-spec? class-definition))
          nil nil nil))))
      (setq new-slot-descriptions-for-class
        (nconc
          new-slot-descriptions-for-class
          (class-description-list
        (make-slot-description 
          'stubs-for-class 'object class nil
          (when class-definition-is-object-definition?
            (connections-for-class? class-definition))
          nil nil nil)))))

    (when (memq 'connection class-inheritance-path)
      (let ((junction-block-class-for-connection? nil)
        (stub-length-for-connection? nil)
        (cross-section-pattern-for-connection? nil))
    (when (frame-of-class-p class-definition 'connection-definition)
      (setq junction-block-class-for-connection?
        (junction-block-class-for-connection class-definition))
      (setq stub-length-for-connection?
        (stub-length-for-connection class-definition))
      (setq cross-section-pattern-for-connection?
        (cross-section-pattern-for-connection class-definition)))
    (setq new-slot-descriptions-for-class
          (nconc
        new-slot-descriptions-for-class
        (class-description-list
          (make-slot-description
            'junction-block-class-for-class 'connection class
            nil junction-block-class-for-connection? nil nil nil))))
    (when junction-block-class-for-connection?
      (setq new-slot-descriptions-for-class
        (nconc
          new-slot-descriptions-for-class
          (class-description-list
            (make-slot-description
              'junction-block-class 'connection class nil
              junction-block-class-for-connection?
              nil nil nil)))))
    (setq new-slot-descriptions-for-class
          (nconc
        new-slot-descriptions-for-class
        (class-description-list
          (make-slot-description
            'stub-length-for-class 'connection class
            nil stub-length-for-connection? nil nil nil))))
    (when stub-length-for-connection?
      (setq new-slot-descriptions-for-class
        (nconc
          new-slot-descriptions-for-class
          (class-description-list
            (make-slot-description
              'stub-length 'connection class nil
              stub-length-for-connection? nil nil nil)))))
    (setq new-slot-descriptions-for-class
          (nconc
        new-slot-descriptions-for-class
        (class-description-list
          (make-slot-description
            'cross-section-pattern-for-class 'connection class
            nil cross-section-pattern-for-connection? nil nil nil))))
    (when cross-section-pattern-for-connection?
      (setq new-slot-descriptions-for-class
        (nconc
          new-slot-descriptions-for-class
          (class-description-list
            (make-slot-description
              'cross-section-pattern 'connection class nil
              cross-section-pattern-for-connection? nil nil nil)))))))

    (when (memq 'message class-inheritance-path)
      (let ((default-message-properties?
        ;; Default-message-properties defined on a class-definition
        ;; (not a subclass of message-definition) will be
        ;; in the default-overrides slot and go through process-
        ;; default-overrides.
        (when (frame-of-class-p class-definition 'message-definition)
          (default-message-properties class-definition))))
    (setq new-slot-descriptions-for-class
          (nconc
        new-slot-descriptions-for-class
        (class-description-list
          (make-slot-description
            'default-message-properties-for-class 'message class
            nil default-message-properties? nil nil nil))))
    (when default-message-properties?
      (setq new-slot-descriptions-for-class
        (nconc
          new-slot-descriptions-for-class
          (process-default-message-properties 
            class-definition class-inheritance-path t nil))))))

    (when (memq 'text-box class-inheritance-path)
      (setq new-slot-descriptions-for-class
        (nconc
          new-slot-descriptions-for-class
          (class-description-list
        (make-slot-description
          'default-text-box-colors-for-class 'text-box class
          nil nil nil nil nil)))))

    ;; All definition classes have the slot icon-description-for-class?
    (when (setq icon-description-for-class?
          (icon-description-for-class? class-definition))
      (if (slot-description-from-class foundation-class 'icon-description)
      (let ((icon-slot-init-form
          (frame-list
            ':funcall-at-load-time
            'create-icon-description-if-valid
            ;; width
            (first icon-description-for-class?)
            ;; height
            (second icon-description-for-class?)
            (cddr icon-description-for-class?)
            nil
            (copy-for-slot-value
              (icon-background-images class-definition)))))
        (setq new-slot-descriptions-for-class
          (nconc
            new-slot-descriptions-for-class
            (class-description-list
              (make-slot-description
            'icon-description 'object class nil
            icon-slot-init-form nil nil nil nil))))
        (reclaim-frame-list icon-slot-init-form))
      (change-slot-value
        class-definition 'icon-description-for-class? nil)))
    
    (setf (definition-state class) 'being-redefined)

    (add-class-to-environment
      class
      direct-superiors-of-defined-class
      (copy-list-using-class-description-conses class-inheritance-path)
      ;; class-features
      (let* ((foundation-class-class-feature
           (class-description-list
         (class-description-list 'foundation-class foundation-class)))
         (not-solely-instantiable-class-feature?
           (when (direct-superiors-preclude-instantiability-p
               direct-superiors-of-defined-class)
         (class-description-list
           (class-description-list 'not-solely-instantiable))))
         (not-user-instantiable-class-feature?
           (when (or not-solely-instantiable-class-feature?
             (null (instantiate? class-definition)))
         (class-description-list
           (class-description-list 'not-user-instantiable))))
         (do-not-put-in-menus-class-feature?
           (unless (include-in-menus? class-definition)
         (class-description-list
           (class-description-list 'do-not-put-in-menus))))
         (indexed-attributes-class-feature?
           (when (or (indexed-attributes-for-definition class-definition)
             (loop for superior in direct-superiors-of-defined-class
                   thereis (get-class-feature-if-any
                     superior 'has-indexed-attributes)))
         (class-description-list
           (class-description-list 'has-indexed-attributes))))
         (attribute-displays-class-feature?
           (when object-class?
         (let ((attribute-displays-specification?
             (or (and class-definition-is-object-definition?
                  (attribute-displays-spec? class-definition))
                 (loop for superior in (cdr class-inheritance-path)
                   for superior-class-description = (class-description
                                      superior)
                   for attribute-displays-for-class? =
                   (and (class-description-is-user-defined-p
                      superior-class-description)
                    (slot-description-from-class
                      superior 'attribute-displays-for-class)
                    (class-slot-description-value
                      'attribute-displays-for-class superior))
                   when attribute-displays-for-class?
                     return attribute-displays-for-class?))))
           (when attribute-displays-specification?
             (class-description-list
              (class-description-cons
            'attribute-displays
            (copy-tree-using-class-description-conses
              attribute-displays-specification?)))))))
         (stubs-class-feature?
           (let ((stubs-specification?
               (or (and class-definition-is-object-definition?
                (connections-for-class? class-definition))
               (get-inherited-stubs-class-feature-for-class
                 class-inheritance-path))))
         (when stubs-specification?
           (if (eq stubs-specification? 'none)
               (class-description-list
             (class-description-cons 'stubs 'none))
               (class-description-list
             (copy-tree-using-class-description-conses
               stubs-specification?))))))
         (disjoint-from-class-feature?
           (loop for superior in direct-superiors-of-defined-class
             for class-feature? =
                   (feature-assq
                 'disjoint-from
                 (class-features (class-description superior)))
             when class-feature?
               return (class-description-list
                (copy-list-using-class-description-conses class-feature?))))
         (not-normally-transient-feature?
           (loop for superior in direct-superiors-of-defined-class
             for class-feature? =
             (feature-assq
               'not-normally-transient
               (class-features (class-description superior)))
             when class-feature?
               return (class-description-list
                (copy-list-using-class-description-conses class-feature?)))))
    (nconc
      foundation-class-class-feature
      not-solely-instantiable-class-feature?
      not-user-instantiable-class-feature?
          do-not-put-in-menus-class-feature?
      indexed-attributes-class-feature?
      attribute-displays-class-feature?
      stubs-class-feature?
      disjoint-from-class-feature?
      not-normally-transient-feature?))
      ;; do-not-propagate-methods?
      t
      new-slot-descriptions-for-class
      previous-direct-superiors?
      class-definition
      ;; user-defined-class?
      t)

    (process-default-overrides class nil)

    (delete-multiple-frame-notes-if-any
      '(undefined-direct-superiors 
    no-direct-superiors no-class-name transient-class-definition)
      class-definition)
      
    (analyze-compiled-items-for-consistency class)

    (update-representations class-definition)

    (loop for potential-definition
            in (potential-inferior-class-definitions class)
      do
      (delete-from-frame-note-particulars-list
    class 'undefined-direct-superiors potential-definition)
      (when (complete-definition-p potential-definition)
    (let* ((direct-superiors
         (direct-superiors-of-defined-class potential-definition))
           (disjoint-foundation-class-direct-superiors?
         (loop for sublist on direct-superiors
               until (null (cdr sublist))
               for superior = (car sublist)
               for superior-foundation-class? =
                 (get-foundation-class-for-class superior)
              thereis
              (and superior-foundation-class?
               (loop for other-superior in (cdr sublist)
                 for other-superior-foundation-class? =
                       (get-foundation-class-for-class
                     other-superior)
                 thereis
                 (and other-superior-foundation-class?
                      (not (subclassp
                         superior-foundation-class?
                         other-superior-foundation-class?))
                      (not (subclassp
                         other-superior-foundation-class?
                         superior-foundation-class?)))))))
           (disjoint-from-direct-superiors?
         (and (cdr direct-superiors)
              (loop for superior in direct-superiors
                for disjoint-from-feature? =
                (get-class-feature-if-any superior 'disjoint-from)
                thereis
                (and disjoint-from-feature?
                 (loop for other-superior in direct-superiors
                       thereis
                       (loop for class in (cdr disjoint-from-feature?)
                         thereis
                         (subclassp other-superior class))))))))
      (cond ((or disjoint-foundation-class-direct-superiors?
         disjoint-from-direct-superiors?)
         (change-slot-value
           potential-definition 'direct-superiors-of-defined-class nil)
         (notify-engineer
           "The definition of ~a has invalidated the direct-superior-classes ~
                attribute of one of its potential inferior classes, ~NF.  This ~
                attribute has been changed to none."
           class potential-definition))
        (t
         (define-user-class potential-definition))))))

    (loop for direct-superior in direct-superiors-of-defined-class
      do
      (add-or-delete-class-or-name-for-frame direct-superior class nil)
      (setf (potential-inferior-class-definitions direct-superior)
            (delete-class-description-element
              class-definition
              (potential-inferior-class-definitions direct-superior))))

    ;; Fix for bug HQ-1876659.
    (when (memq 'connection class-inheritance-path-of-definition?)
      (let ((cross-section-pattern?
          (or (class-slot-description-value 'cross-section-pattern-for-class class)
          (let* ((cross-section-pattern-slot-description
               (slot-description-from-class class 'cross-section-pattern)))
            (slot-init-form
              (slot-description-of-most-specific-superior-refining-slot
            class-inheritance-path
            cross-section-pattern-slot-description))))))
    (update-junction-block-for-connection
      class class-definition cross-section-pattern?)
    (update-connection-subrectangle-structures
      class cross-section-pattern?)))
    (when (and (not class-was-previously-defined?)
           class-definition-is-object-definition?
           object-class?)
      (update-stubs-for-class class (connections-for-class? class-definition)))
    (setf (definition-state class) 'defined)
    (analyze-compiled-items-for-consistency class)
    (instantiate-or-uninstantiate-class-in-attributes-as-appropriate
      class 'newly-defined)
    (update-frame-status class-definition nil nil)

    (reclaim-frame-tree slot-features-for-class-slot)))




;;; `Define-user-class-if-possible' is called immediately after making a
;;; transient definition permanent. At this time, the definition does not define
;;; a class (does not have a class description) and has no instances.  When the
;;; definition does not have a class name or an acceptable set of direct
;;; superiors, the definition will be permanent and, therefore, kb-saved, even
;;; though the class is not defined.  When the definition does have a class name
;;; and a complete set of direct superiors the definition becomes permanent and
;;; the class is defined.  Classes with transient definitions should never be
;;; defined, and define-user-class-if-possible must not be called with permanent
;;; definitions.

(defun define-user-class-if-possible (class-definition)
  (let* ((name? (name-of-defined-class class-definition))
     (direct-superiors-of-defined-class? 
       (direct-superiors-of-defined-class class-definition))
     (icon-description?
       (icon-description-for-class? class-definition))
     (default-message-properties?
         (when (frame-of-class-p class-definition 'message-definition)
           (default-message-properties class-definition)))
     (cross-section-pattern?
       (when (frame-of-class-p class-definition 'connection-definition)
         (cross-section-pattern-for-connection class-definition))))

    #+development
    (when (classp name?)
      (cerror "definitions" "define-user-class-if-possible error"))

    (when (and name? direct-superiors-of-defined-class?)
      (setf (direct-superiors-of-defined-class class-definition) nil)
      (when icon-description?
    (setf (icon-description-for-class? class-definition) nil))
      (when default-message-properties?
    (setf (default-message-properties class-definition) nil))
      (when cross-section-pattern?
    (setf (cross-section-pattern-for-connection class-definition) nil))
      
      (change-slot-value
    class-definition 'direct-superiors-of-defined-class
    direct-superiors-of-defined-class?)
      (when icon-description?
    (change-slot-value
      class-definition 'icon-description-for-class? icon-description?))
      (when default-message-properties?
    (change-slot-value
      class-definition 'default-message-properties default-message-properties?))
      (when cross-section-pattern?
    (change-slot-value
      class-definition 'cross-section-pattern-for-connection
      cross-section-pattern?)))))




(defun update-junction-block-for-connection
    (class class-definition cross-section-pattern-for-class)
  ;; The class must be defined.
  (let* ((cross-section-size-for-junction
       (+f (compute-connection-width-given-stripe
         (get-cross-section-stripes cross-section-pattern-for-class))
           4))
     (name-for-junction-block-class
       (intern-text-string
         (tformat-text-string "JUNCTION-BLOCK-FOR-~A" class)))
     (existing-junction-block-class
       (class-slot-description-value 'junction-block-class-for-class class)))
    (cond
      ((null existing-junction-block-class)
       (if (frame-of-class-p class-definition 'connection-definition)
       (change-slot-value
         class-definition 'junction-block-class-for-connection
         name-for-junction-block-class)
       (update-junction-block-class-for-class
         class name-for-junction-block-class))
       (locate-or-create-junction-block-definition
     name-for-junction-block-class cross-section-size-for-junction))
      ((eq existing-junction-block-class name-for-junction-block-class)
       (locate-or-create-junction-block-definition
     name-for-junction-block-class cross-section-size-for-junction)))))




(define-slot-alias default-message-properties default-message-properties-for-class message)

;;; `Process-default-message-properties' abstracts the decoding and integrating
;;; of the information contained in the default-message-properties of a
;;; message-definition.  There are six properties whose values are stored in
;;; four slot descriptions.  The slot description for text-cell-plist-for-text-
;;; box encodes three of the properties.

;;; When called from alter-inheritance-of-class-without-changing-foundation-
;;; class, this function returns a slot description for
;;; text-cell-plist-for-text-box when any of the three properties it encodes are
;;; user specified; otherwise it returns nil.  When called from
;;; define-user-class, this function returns a list of any slot descriptions
;;; that encode class-specific information; otherwise it returns nil.
;;; Otherwise, this function is called from the slot-putter code for
;;; default-message-properties where update-slot-description is called to make
;;; the necessary changes to the message slot descriptions.

(defun process-default-message-properties
    (class-definition class-inheritance-path
              called-from-define-user-class?
              called-from-alter-inheritance?)
  (let* ((class (name-of-defined-class class-definition))
     (default-message-properties
         (if (classp class)
         (class-slot-description-value
           'default-message-properties-for-class class)
         (and (frame-of-class-p class-definition 'message-definition)
              (default-message-properties class-definition))))
     ;; The text-cell-plist-for-text-box slot-init-form for a class will
     ;; contain only values that have been explicitly specified by the user
     ;; for border-color, background-color, text-color, and [as of 5.0
     ;; rev. 3, in development as of 3/3/98] text-alignment in the
     ;; default-message-properties slot of a message-definition or the
     ;; default-overrides of class-definitions.  The plist-for-text-box
     ;; slot-description for the system-defined message class has a null
     ;; slot-init-form.
     (plist-init-form?
       (loop for property-name
             in '(border-color line-color background-color text-alignment)
         nconc (get-specified-or-superior-message-property
             default-message-properties
             property-name
             class-inheritance-path)))
     (message-class-description (class-description 'message))
     (plist-slot-description-from-message-class
       (get-slot-description-of-class-description
         'text-cell-plist-for-text-box message-class-description)))

    (if called-from-alter-inheritance?
    (when plist-init-form?
      (let ((plist-slot-description
          (make-slot-description
            'text-cell-plist-for-text-box 'text-box class nil
            plist-init-form?
            (vector-slot-index?
              plist-slot-description-from-message-class)
            nil
            (slot-features plist-slot-description-from-message-class))))
      (reclaim-frame-list plist-init-form?)
      plist-slot-description))
    (let* ((specified-font?
         (cdr (assq 'font default-message-properties)))
           (specified-width?
         (cdr (assq 'minimum-width default-message-properties)))
           (specified-height?
         (cdr (assq 'minimum-height default-message-properties)))
           ;; The default slot-init-form value is that specified by message
           ;; class in its default-text-box-format-name slot
           ;; (message-format).
           (font-init-form?
         (if specified-font?
             (case specified-font?
               (small 'message-format)
               (large 'large-message-format)
               (extra-large 'extra-large-message-format))
             (unless called-from-define-user-class?
               (loop for superior in (cdr class-inheritance-path)
                 do
             (when (subclassp superior 'message)
               (let ((default-text-box-format-name-slot-description? 
                     (get-slot-description
                       'default-text-box-format-name
                       (slot-descriptions
                     (class-description superior)))))
                 (when default-text-box-format-name-slot-description?
                   (return
                 (slot-init-form
                   default-text-box-format-name-slot-description?)))))))))
           ;; The default slot-init-form value is that specified by text-box
           ;; class in its minimum-width-of-text-box slot (0).
           (minimum-width-init-form?
         (or specified-width?
             (unless called-from-define-user-class?
               (loop for superior in (cdr class-inheritance-path)
                 do
             (when (subclassp superior 'message)
               (let ((minimum-width-of-text-box-slot-description?
                   (get-slot-description
                     'minimum-width-of-text-box
                     (slot-descriptions
                       (class-description superior)))))
                 (when minimum-width-of-text-box-slot-description? 
                   (return
                 (slot-init-form
                   minimum-width-of-text-box-slot-description?)))))))))
           ;; The default slot-init-form value is that specified by text-box
           ;; class in its minimum-height-of-text-box slot (0).
           (minimum-height-init-form?
         (or specified-height?
             (unless called-from-define-user-class?
               (loop for superior in (cdr class-inheritance-path)
                 do
             (when (subclassp superior 'message)
               (let ((minimum-height-of-text-box-slot-description? 
                   (get-slot-description
                     'minimum-height-of-text-box
                     (slot-descriptions
                       (class-description superior)))))
                 (when minimum-height-of-text-box-slot-description? 
                   (return
                 (slot-init-form
                   minimum-height-of-text-box-slot-description?))))))))))
      (if called-from-define-user-class?
          ;; Make a slot-description for default-text-box-format-name only if the
          ;; class definition specifies a font; make a slot-description for
          ;; minimum-width-of-text-box only if the class definition specifies a
          ;; width, and make a slot-description for minimum-height-of-text-box
          ;; only if the class definiton specifies a height.  For unspecified
          ;; characteristics, the new class will inherit the slot from the
          ;; most-specific superior that defines one.
          (let ((slot-descriptions-to-return
              (nconc
            (when specified-font?
              (let ((slot-description-from-message-class
                  (get-slot-description-of-class-description
                    'default-text-box-format-name
                    message-class-description)))
                (class-description-list
                  (make-slot-description
                'default-text-box-format-name 'message class nil
                font-init-form?
                (vector-slot-index?
                  slot-description-from-message-class) nil
                (slot-features
                  slot-description-from-message-class)))))
            (when specified-width?
              (let ((slot-description-from-message-class
                  (get-slot-description-of-class-description
                    'minimum-width-of-text-box
                    message-class-description)))
                (class-description-list
                  (make-slot-description
                'minimum-width-of-text-box 'text-box class nil
                minimum-width-init-form?
                (vector-slot-index?
                  slot-description-from-message-class)
                nil
                (slot-features slot-description-from-message-class)))))
            (when specified-height?
              (let ((slot-description-from-message-class
                  (get-slot-description-of-class-description
                    'minimum-height-of-text-box
                    message-class-description)))
                (class-description-list
                  (make-slot-description
                'minimum-height-of-text-box 'text-box class nil
                minimum-height-init-form?
                (vector-slot-index?
                  slot-description-from-message-class) nil
                (slot-features
                  slot-description-from-message-class)))))
            (when plist-init-form?
              (class-description-list
                (make-slot-description
                  'text-cell-plist-for-text-box 'text-box class nil
                  plist-init-form?
                  (vector-slot-index?
                plist-slot-description-from-message-class) nil
                (slot-features
                  plist-slot-description-from-message-class)))))))
        (reclaim-frame-list plist-init-form?)
        slot-descriptions-to-return)
          
          (with-deferred-drawing ()

        (let ((class-slot-descriptions
            (slot-descriptions (class-description class))))
          
          (loop for instance being each class-instance of class
            do
            (erase-images-of-block instance t))
          
          (let ((font-slot-description
              (get-slot-description
                'default-text-box-format-name
                class-slot-descriptions)))
            (unless (eq font-init-form?
                (slot-init-form font-slot-description))
              (update-slot-description
            class font-slot-description nil font-init-form?
            (slot-features font-slot-description) nil nil)))

          (let ((width-slot-description
              (get-slot-description
                'minimum-width-of-text-box
                class-slot-descriptions)))
            (unless (eq minimum-width-init-form?
                (slot-init-form width-slot-description))
              (update-slot-description
            class width-slot-description nil minimum-width-init-form?
            (slot-features width-slot-description) nil nil)))

          (let ((height-slot-description
              (get-slot-description
                'minimum-height-of-text-box class-slot-descriptions)))
            (unless (eq minimum-height-init-form?
                (slot-init-form height-slot-description))
              (update-slot-description
            class height-slot-description nil minimum-height-init-form?
            (slot-features height-slot-description) nil nil)))

          (let ((plist-slot-description
              (get-slot-description
                'text-cell-plist-for-text-box class-slot-descriptions)))
            (unless (equal plist-init-form?
                   (slot-init-form plist-slot-description))
              (update-slot-description
            class plist-slot-description nil plist-init-form?
            (slot-features plist-slot-description) nil nil)))
          
          (loop for instance being each class-instance of class
            do
            (draw-images-of-block instance t)))
        (reclaim-frame-list plist-init-form?)))))))



;; Get-specified-or-superior-message-property is an internal subfunction of
;; process-default-message-properties.

(defun-simple get-specified-or-superior-message-property
    (default-message-properties property-name class-inheritance-path)
  (let ((value? (cdr (assq property-name default-message-properties))))
    (if value?
    (frame-list property-name value?)
    (loop for superior in (cdr class-inheritance-path)
          do (when (and (user-defined-class-p superior)
                (subclassp superior 'message))
           (let ((superior-specified-border-color?
               (cdr (assq property-name
                      (class-slot-description-value
                    'default-message-properties-for-class
                    superior)))))
             (when superior-specified-border-color?
               (return (frame-list
                 property-name
                 superior-specified-border-color?)))))))))




;;; `Make-class-inheritance-path-obsolete' is used on a class-definition when it
;;; no longer has a correct class-inheritance-path-of-definition (usually due to
;;; undefining a superior).

(defun-void make-class-inheritance-path-obsolete (class-definition)
  (reclaim-slot-value (class-inheritance-path-of-definition class-definition))
  (setf (class-inheritance-path-of-definition class-definition) nil)
  (update-representations-of-slot-value class-definition
                    'class-inheritance-path-of-definition))



;;; `Undefine-user-class', given a user class definition, causes the class to
;;; become undefined (lose its class description).  If the definition is being
;;; deleted, the class will also lose its class definition.  If the definition
;;; is not being deleted, but becoming incomplete because a change in the direct
;;; superiors has reverted them to none, or specified at least one undefined
;;; superior, or the name of defined class has reverted to none, the class
;;; definition remains but its status changes to incomplete.

;;; Subclasses that are not already potential classes become potential classes.
;;; Then all potential-classes will experience a change of frame notes.

(defun-void undefine-user-class
    (definition delete-frame-called-on-definition? class-name-reverting-to-none?)

  (let* ((user-class (name-of-defined-class definition))
     (direct-superiors-of-defined-class
       (direct-superiors-of-defined-class definition))
     (attribute-descriptions
       (class-specific-attributes definition))
     (object-class-p (or (eq (class definition) 'object-definition)
                 (memq 'object (class-inheritance-path-of-definition
                         definition)))))
    (decache-cached-class-data user-class)
    ;; Fix for storm leaks
    (loop for direct-superior in direct-superiors-of-defined-class
      do
      (add-or-delete-class-or-name-for-frame direct-superior user-class t))
    
    (cond (releasing-kb?
       ;; The inferior-classes property is not changed when releasing-kb?
       ;; because the loop iteration paths are useful for determining
       ;; reclamability.  Delete-classes-queued-by-delete-frame will
       ;; deal with this work.
       (add-or-delete-class-or-name-for-frame user-class user-class t)
       (delete-instances-specific-to-this-class user-class)
       (reclaim-class-description-list
         (potential-inferior-class-definitions user-class))
       (setf (potential-inferior-class-definitions user-class) nil)
       (analyze-compiled-items-for-consistency user-class)

       (loop for attribute-description in attribute-descriptions
         as attribute-name = (attribute-name attribute-description)
         as attribute-range = (attribute-range  attribute-description)
         for corresponding-slot-description = (slot-description-from-class
                            user-class attribute-name
                            user-class)
         do
         (undeclare-implied-attribute user-class attribute-name attribute-range nil)
         (undeclare-implied-attribute
           user-class (unique-slot-name corresponding-slot-description)
           attribute-range t))

       (setf (class-definition user-class) nil)
       (setf (definition-state user-class) nil))

      ;; The definition class is becoming undefined either because of a
      ;; delete-class action (including deleting a workspace)
      ;; or because there has been a change in the
      ;; direct-superiors-of-defined-class slot or name-of-defined-class
      ;; slot that causes the definition to become incomplete.  In the
      ;; former case, the class definition will be reclaimed by delete-
      ;; frame.  In the latter case, the class will retain its definition.
      ;; In both cases, all instances of the class will be deleted down the
      ;; class hierarchy.  Subclasses become potentential classes.
      ;; The class-descriptions are reclaimed by delete-classes-queued-
      ;; by-delete-frame after the exit of delete-frame.
      (t
       (add-or-delete-class-or-name-for-frame user-class user-class t)
       (let ((subclass-list
           (nreverse
             (loop for subclass being each subclass of user-class
               when (class-definition subclass)
                 collect subclass using frame-cons))))

         ;; Note that the above loop for constructing a subclass-list omits
         ;; subclasses whose class-definitions have been reclaimed.  During
         ;; reclamation the inferior-classes property of a class will not
         ;; be updated when a subclass class-definition has been deleted
         ;; because the reclamation of class-descriptions is not done until
         ;; the final exit of delete-frame in order to reclaim only those
         ;; data structures that are not shared with a class that is not
         ;; being deleted.  Keeping the inferior-classes properties intact
         ;; helps in deciding whether a data structure is reclaimable.

         (loop for subclass in subclass-list
           for class-definition? = (class-definition subclass)
           do
           ;; The framep check is necessary for cases when an instance
           ;; of subclass had a subworkspace that contained the subclass
           ;; definition.  In that case, the code enclosed in the when
           ;; clause would already have been executed.
           (when class-definition?
         (let ((direct-superiors
             (direct-superiors-of-defined-class class-definition?))
               (attribute-descriptions
             (class-specific-attributes class-definition?)))
           (delete-instances-specific-to-this-class subclass)
           (when (framep class-definition?)
             (analyze-compiled-items-for-consistency subclass)
             (loop for attribute-description in attribute-descriptions
               as attribute-name = (attribute-name attribute-description)
               as attribute-range = (attribute-range attribute-description)
               for corresponding-slot-description = (slot-description-from-class
                                  subclass attribute-name
                                  subclass)
               do
               (undeclare-implied-attribute
             subclass attribute-name attribute-range nil)
               (undeclare-implied-attribute
             subclass (unique-slot-name corresponding-slot-description)
             attribute-range t))

             (when delete-frame-called-on-definition?
               (unless (memq subclass queue-of-classes-to-be-undefined)
             (setq queue-of-classes-to-be-undefined
                   (nconc queue-of-classes-to-be-undefined
                      (frame-list subclass)))))

             ;; Add a frame note to the potential definitions of subclass
             ;; that subclass is now undefined.
             (loop for potential-definition
                   in (potential-inferior-class-definitions subclass)
               do
               (make-class-inheritance-path-obsolete potential-definition)
               (add-to-frame-note-particulars-list-if-necessary
             subclass 'undefined-direct-superiors potential-definition))

             ;; When delete-frame-called-on-definition? is null, undefine-
             ;; user class has been called from the slot putter code for
             ;; direct-superiors-of-defined-class or name-of-defined-class.
             (unless (and (eq subclass user-class)
                  (not delete-frame-called-on-definition?))
               ;; At user-class level, the class inheritance path is dealt with by
               ;; the slot putter code for direct-superiors-of-defined-class.
               ;; When the class name is reverting to NONE, the class-inheritance-
               ;; path, if there is one, is not affected at class level.
               (unless (and (eq subclass user-class) class-name-reverting-to-none?)
             (make-class-inheritance-path-obsolete class-definition?))
               
               ;; When called from the slot putter code for direct-superiors-of-
               ;; defined-class the value of the direct-superiors-of-defined-
               ;; class still reflects the old value.  The work done here for
               ;; subclasses is done in the direct-superiors-of-defined-class
               ;; and name-of-defined-class slot putter code for user-class,
               ;; including placing the definition on the potential-inferior-
               ;; class-definitions properties of its direct superior classes.
               (loop for superior in direct-superiors
                 do
             (setf (potential-inferior-class-definitions superior)
                   (class-description-pushnew
                 class-definition?
                 (potential-inferior-class-definitions superior)))
             ;; Because the class descriptions for classes queued by
             ;; delete-frame are not reclaimed and set to nil until
             ;; the final exit of delete-frame, a classp test is not
             ;; sufficient.
             (when (or (not (classp superior))
                   (memq superior subclass-list)
                   (memq superior queue-of-classes-to-be-undefined))
               (add-to-frame-note-particulars-list-if-necessary
                 superior 'undefined-direct-superiors class-definition?)))

               ;; The slot putter code for direct-superiors-of-defined-class
               ;; and name-of-defined-class update the frame status for
               ;; user-class depending on whether it will be redefined or not.
               (update-frame-status class-definition? 'incomplete nil))

             ;; When (indirectly) called from delete-frame, the slots on the
             ;; definition have not yet been reclaimed.
             (unless (and (eq subclass user-class)
                  delete-frame-called-on-definition?)
               (when (frame-of-class-p definition 'message-definition)
             (remove-default-message-overrides class-definition?))
               (when (or (frame-of-class-p definition 'object-definition)
                 (frame-of-class-p definition 'class-definition))
             (remove-default-overrides-on-system-slots class-definition? t))
               (clear-override-frame-notes-from-definition class-definition?))))))

             (when delete-frame-called-on-definition?
           (loop for direct-superior in direct-superiors-of-defined-class
             do
         (setf (potential-inferior-class-definitions direct-superior)
               (delete-class-description-element
             definition
             (potential-inferior-class-definitions direct-superior))))
           (setf (class-definition user-class) nil))

         (unless delete-frame-called-on-definition?
           (reclaim-queued-class-descriptions subclass-list)
           (update-representations definition))

         (setf (definition-state user-class) nil)
         (when object-class-p
           (instantiate-or-uninstantiate-class-in-attributes-as-appropriate
         user-class 'undefined))

           (reclaim-frame-list subclass-list))))))




;;; `Direct-superiors-are-defined-p' returns t if there are one or more
;;; direct superiors, and all of the direct superior
;;; classes are defined classes; otherwise it returns nil.

(defun-simple direct-superiors-are-defined-p (direct-superiors?)
  (when direct-superiors?
    (loop for superior in direct-superiors?
      when (not (classp superior))
        return nil
      finally (return t))))




;;; `Direct-superiors-preclude-instantiability-p' returns nil when class
;;; inheritance makes it possible to instantiate the class; otherwise it returns t.

(defun-simple direct-superiors-preclude-instantiability-p
    (direct-superior-classes)
  (let* ((foundation-class
      (most-refined-foundation-class-of-direct-superiors
        direct-superior-classes))
     (foundation-class-features
       (class-features (class-description foundation-class))))
    (feature-assq 'not-solely-instantiable foundation-class-features)))




;;; `Complete-definition-p' returns t when the class for definition
;;; can be defined (has acceptable direct superiors, is named, and the
;;; clas-definition is not transient) otherwise it returns nil.

(defun-simple complete-definition-p (definition)
  (and
    (not (transient-p definition))
    (not (incomplete-direct-superior-classes-p definition))
    (name-of-defined-class definition)))




;;; `Incomplete-direct-superior-classes-p' returns t when the direct-superiors-
;;; of-defined-class slot of the definition contains an acceptable set of
;;; direct superior classes; otherwise it returns nil.
;;; 
(defun-simple incomplete-direct-superior-classes-p (definition)
  (or (frame-has-note-p definition 'no-direct-superiors)
      (frame-has-note-p definition 'undefined-direct-superiors)
      (let ((direct-superiors (direct-superiors-of-defined-class definition)))
    (or (null direct-superiors)
        (loop for superior in direct-superiors
          thereis (not (classp superior)))
        (null (most-refined-foundation-class-of-direct-superiors direct-superiors))))))




;;; `Undefine-user-class-becoming-transient' must be called before making a
;;; permanent class transient. It is the responsibility of the caller that this
;;; definition, if it defines a class, does not have instances or subclasses.
;;; The definition will be left in an incomplete state, and it will not define a
;;; class upon exit.

(defun undefine-user-class-becoming-transient (definition)
  (let ((direct-superiors-of-defined-class?
      (direct-superiors-of-defined-class definition))
    (class (name-of-defined-class definition)))

    (when (classp class)
      (when (subclassp class 'connection)
    (delete-junction-block-definition-if-appropriate
      class (class-slot-description-value 'junction-block-class-for-class class))
    (change-class-slot-description-value
      'junction-block-class-for-class class nil))
      (reclaim-class-description-of-class
    class (class-description class) nil))
    
    (when (frame-of-class-p definition 'message-definition)
      (remove-default-message-overrides definition))
    (when (or (frame-of-class-p definition 'object-definition)
          (frame-of-class-p definition 'class-definition))
      (remove-default-overrides-on-system-slots definition t))
    
    (update-frame-status definition 'incomplete nil)
    (change-slot-value definition 'inherited-attributes nil)

    (reclaim-class-description-list (direct-superior-classes class))
    (setf (direct-superior-classes class) nil)
    
    (loop for direct-superior in direct-superiors-of-defined-class?
      do
      (class-description-pushnew 
    definition
    (potential-inferior-class-definitions direct-superior))
      (setf (inferior-classes direct-superior)
        (delete-class-description-element
          class (inferior-classes direct-superior))))))
    



;;; `Undefine-potential-user-class', given a user class class-definition, causes
;;; the potential class to no longer be a class at all.  Called only from
;;; cleanup-for-definition.

(defun undefine-potential-user-class (definition)
  (let* ((class
       (name-of-defined-class definition))
     (direct-superiors-of-defined-class?
       (direct-superiors-of-defined-class definition)))
    (loop for direct-superior in direct-superiors-of-defined-class?
      do
      (setf (potential-inferior-class-definitions direct-superior)
        (delete-class-description-element
          definition
          (potential-inferior-class-definitions direct-superior))))
      
      ;; This when clause is commented out because the inferior-classes property
      ;; should be used only for defined classes (ghw).
;      (when class
;        (setf (inferior-classes direct-superior)
;              (delete-frame-element
;                class (inferior-classes direct-superior)))))

    ;; RECLAMATION:  The slots on the definition should be reclaimed!!! (ghw)
    (setf (class-definition class) nil)
    (analyze-compiled-items-for-consistency class)))


;; Now called by cleanup-for-definition whenever the definition is not
;; of a class. The WHEN conditions are needed because it may not even have
;; a superior-class or a class. The use of this function is new as of 15 Feb, 89,
;; and fixes a bug that must have been in the system for over a year.
;; Without this cleanup, the class-definition property of a deleted definition 
;; could reference its reclaimed frame, and the inferior-classes of a symbol
;; could list the names of definitions which have been deleted.




;;; `Rename-attribute' changes the name of the attribute of class denoted by
;;; old-attribute-name to new-attribute-name.  The change not only applies to
;;; the class and its subclasses but applies also to all instances of the class.

(defun rename-attribute (definition user-class old-name new-name)
  (let* ((attribute-description-of-definition
       (get-attribute-description 
         old-name (class-specific-attributes definition)))
     (attribute-range (attribute-range attribute-description-of-definition))
     (class-description (class-description user-class))
     (user-class-slot-description
       (get-slot-description-of-class-description
         old-name class-description user-class))
     (old-unique-slot-name (unique-slot-name user-class-slot-description))
     (slot-descriptions-affected nil)
     (new-unique-slot-name
       (make-unique-slot-name-symbol user-class new-name)))

    ;; Remove default-override-related frames notes from all subclasses of
    ;; user-class.
    (clear-override-frame-notes-from-class-definitions user-class)
    (undeclare-implied-attribute
      user-class old-unique-slot-name attribute-range t)
    (declare-implied-attribute
      user-class new-unique-slot-name attribute-range t)

    (when (reserved-system-slot-name-p definition old-name)
      (delete-from-frame-note-particulars-list
    old-name 'class-specific-attribute-is-a-system-slot-name definition))

    (delete-from-directory-of-names old-name 'attribute-name)
    (add-to-directory-of-names new-name 'attribute-name)
    (setf (car (memq old-unique-slot-name
             (slots-local-to-class class-description)))
      new-unique-slot-name)

    (loop for class being each subclass of user-class
      for class-description = (class-description class)
      for slot-descriptions = (slot-descriptions class-description)
      for unchanged-slot-description =
            (if (eq class user-class)
            user-class-slot-description
            (get-slot-description
              old-unique-slot-name slot-descriptions))
      do
      (decache-cached-class-data class)
      (delete-slot-description-from-hash-table
    unchanged-slot-description class-description)
      (when (not (memq unchanged-slot-description slot-descriptions-affected))
    (setq slot-descriptions-affected
          (frame-cons
        unchanged-slot-description slot-descriptions-affected))))

    (loop for slot-description in slot-descriptions-affected
      do
      (setf (unique-slot-name slot-description) new-unique-slot-name)
      (setf (pretty-slot-name slot-description) new-name)
      (setf (slot-description-cached-reclaimer? slot-description) nil))

    (reclaim-frame-list slot-descriptions-affected)

    (loop for class being each subclass of user-class
      for class-description = (class-description class)
      for changed-slot-description =
            (get-slot-description
          new-unique-slot-name (slot-descriptions class-description))
      do
      (add-slot-description-to-hash-table
    changed-slot-description class-description)

      (loop for instance being each strict-class-instance of class
        do
    (update-representations instance)))

    (setf (attribute-name attribute-description-of-definition) new-name)
    (process-default-overrides user-class t)

    ;; The index information for a slot is kept on a separate list,
    ;; indexed-attributes-for-definition. If the name of an attribute changes,
    ;; then the occurance of that name, if any, on this list must have the same
    ;; change.
    (loop with change-to-index? = nil
      with indexed-attributes = (indexed-attributes-for-definition definition)
      with copy-of-old-value =
             (copy-list-using-gensym-conses indexed-attributes) 
      for listed-attribute-name on indexed-attributes
      doing
      (when (eq (first listed-attribute-name) old-name)
    (setf (first listed-attribute-name) new-name)
    (setq change-to-index? t))
      finally
        (when change-to-index?
          (update-indexed-attribute-properties
        definition t copy-of-old-value nil))
        (reclaim-gensym-list copy-of-old-value)))

  ;; new. (MHD/GHW 11/18/93)
  (update-attribute-tables-for-instances user-class nil))





;;;; Definition Initialization Method



(def-class-method initialize (class-definition)
  (funcall-superior-method class-definition)    ; per convention
  (when (or (null (name-of-defined-class class-definition))
        (null (direct-superiors-of-defined-class class-definition)))
    (update-frame-status class-definition 'incomplete nil)
    (when (null (name-of-defined-class class-definition))
      (add-frame-note 'no-class-name class-definition))
    (when (null (direct-superiors-of-defined-class class-definition))
      (add-frame-note 'no-direct-superiors class-definition))))





;;;; Slot Putters

(def-slot-putter name-of-defined-class (definition new-name? initializing?)
  ;; Deferral of analysis is needed particularly by the cached-attribute
  ;; free-reference.  It is done for efficiency reasons and, also, so that
  ;; changes to definitions are completed before the analysis is done.
  (defer-some-consistency-analysis
    (let ((old-name? (name-of-defined-class definition))
      (class-change-requires-kb-validation? nil)
      (analyze-attributes-of-subclasses-if-necessary? nil))

      (decache-class-chaining-lists)

      (cond
    ;; No change. Do nothing.
    ((eq old-name? new-name?) new-name?)

    ;; Name in use. Don't replace old name.
    ((or (system-defined-class-p new-name?)
         (let ((frame-with-this-name 
             (get-instance-with-name-if-any
               'class-definition new-name?)))
           (and frame-with-this-name
            (neq frame-with-this-name definition))))     
     (notify-engineer "The name ~A is already in use." new-name?)
     old-name?)

    ((and new-name?
          initializing?
          (type-specification-for-user-or-datum-type new-name?))
     (notify-user
       "~%~% Urgent:  ~
              This kb has a class named ~a which now specifies a data ~
              type in G2. ~
              ~% It is extremely important to rename the ~a class before ~
              running this kb or doing any further development work to aviod ~
              a likely G2 failure."
       new-name? new-name?))

    ;; The new name also occurs in the list of direct superiors.
    ((and new-name?
          (memq new-name?
            (direct-superiors-of-defined-class definition)))
     (notify-engineer "~A is the name of a direct superior class."
              new-name?))
    
    (t
     (let* ((direct-superiors?
          (direct-superiors-of-defined-class definition))
        (class-inheritance-path-of-definition?
          (class-inheritance-path-of-definition definition))
        (any-class-instances? nil))

       ;; Test for instances before any definition changes are made.
       (when (and old-name? (classp old-name?))
         (loop for thing being each class-instance of old-name?
           do
           (setq any-class-instances? t)
           until any-class-instances?))
       
       (if (null new-name?)
           (add-frame-note 'no-class-name definition)
           (delete-frame-note-if-any 'no-class-name definition))

       (when class-inheritance-path-of-definition?
         (if new-name?
         (setf (car class-inheritance-path-of-definition?) new-name?)
         (setf (car class-inheritance-path-of-definition?) nil))
         (unless initializing?
           (update-representations-of-slot-value
         definition 'class-inheritance-path-of-definition)))

       (if initializing?
           (put-name-or-names-for-frame definition new-name? initializing?)
           (change-slot-value definition 'name-or-names-for-frame new-name?))

       (when new-name?
         (setf (class-definition new-name?) definition))
       
       (cond
         ;; The class is defined.
         ((classp old-name?)
          (when any-class-instances?
        (setq class-change-requires-kb-validation? t))
          (add-or-delete-class-or-name-for-frame old-name? old-name? t)
          (cond (new-name?
             (loop for direct-superior in direct-superiors?
               do
               (when (classp direct-superior)
             (add-or-delete-class-or-name-for-frame
               direct-superior new-name? nil)))
             (setf (name-of-defined-class definition) new-name?)
             (update-name-of-user-class new-name? old-name?)
             ;; The potential-inferior-class-definitions of the new name
             ;; can now be defined if they are complete.  If they are
             ;; still incomplete, remove the undefined-direct-superiors
             ;; frame note for the new name.
             (loop for potential-definition in
               (potential-inferior-class-definitions new-name?)
               for direct-superiors-of-defined-class =
               (direct-superiors-of-defined-class
                 potential-definition)
               do
               ;; Fix for bug HQ-1715292
               (delete-from-frame-note-particulars-list
             new-name? 'undefined-direct-superiors potential-definition)
               (when (and (complete-definition-p potential-definition)
                  (or (and (not (transient-p potential-definition))
                       (permanent-block-p potential-definition))
                      (and loading-kb-p
                       ;; It is a pre-3.0 kb.
                       (not new-saved-kb-format-p))))
                  (setq analyze-attributes-of-subclasses-if-necessary? t)
                  (unless (transient-p potential-definition)
                (update-frame-status potential-definition nil nil)
                (define-user-class potential-definition))))
             ;; Merge the potential-inferior-class-definitions for both
             ;; names and place them in the new name property.
             (setf (potential-inferior-class-definitions new-name?)
               (nconc
                 (potential-inferior-class-definitions old-name?)
                 (potential-inferior-class-definitions new-name?)))
             (setf (potential-inferior-class-definitions old-name?)
               nil)

             (analyze-compiled-items-for-consistency old-name?)
             (instantiate-or-uninstantiate-class-in-attributes-as-appropriate
               old-name? 'name-change new-name?)
             (analyze-compiled-items-for-consistency new-name?)
             (instantiate-or-uninstantiate-class-in-attributes-as-appropriate
               new-name? 'newly-defined)
             (loop for subclass being each subclass of new-name?
               do
               (unless (eq subclass new-name?)
             (analyze-compiled-items-for-consistency subclass)
             (instantiate-or-uninstantiate-class-in-attributes-as-appropriate
               subclass 'change-in-inheritance))))

            ;; Class name is reverting to none.
            (t
             (loop for superior in direct-superiors?
               do
               (setf (potential-inferior-class-definitions superior)
                 (class-description-pushnew
                   definition
                   (potential-inferior-class-definitions superior))))
             (update-frame-status definition 'incomplete t)
             (undefine-user-class definition nil t)
             (setf (name-of-defined-class definition) nil))))

         ;; The class is not defined, but is now ready to be defined.
         ((and new-name?
           direct-superiors?
           (not (incomplete-direct-superior-classes-p definition))
           (or (and (not (transient-p definition))
                (permanent-block-p definition))
               (and loading-kb-p
                (not new-saved-kb-format-p))))
          ;; The attributes of subclasses need to be analyzed because
          ;; making this class newly "complete" could affect the location
          ;; of attributes in subclasses.  Attribute location can change
          ;; if the subclass was at one time complete and, therefore,
          ;; having its attribute locations defined, before having this
          ;; incomplete superior class.
          ;; Note that the subclass analysis must be done after the
          ;; subclasses are defined as classes.
          (setq analyze-attributes-of-subclasses-if-necessary? t)
          (update-frame-status definition nil nil)
          (setf (name-of-defined-class definition) new-name?)
          (unless (transient-p definition)
        (define-user-class definition)))
         
         ;; The class will remain undefined.
         ((not (complete-definition-p definition))
          (loop for potential-definition in
            (potential-inferior-class-definitions old-name?)
            do
        (delete-from-frame-note-particulars-list
          old-name? 'undefined-direct-superiors potential-definition)
        (when new-name?
          (add-to-frame-note-particulars-list-if-necessary
            new-name? 'undefined-direct-superiors
            potential-definition)))
          (setf (name-of-defined-class definition) new-name?))
         ;; The class is transient
         (t (setf (name-of-defined-class definition) new-name?)))

       (setf (class-definition old-name?) nil)

       (if (classp new-name?)
           (when (and (direct-superiors-preclude-instantiability-p
                  (direct-superiors-of-defined-class definition))
              (instantiate? definition))
         (add-frame-note 'inconsistent-instantiate-value definition))
           (delete-frame-note-if-any
         'inconsistent-instantiate-value definition))

       (update-representations-of-slot-value
         definition 'name-of-defined-class)
       
       (unless initializing?
         ;; Update indexed-attributes when G2 is reset, running, or
         ;; paused.
         (let ((indexed-attributes?
             (indexed-attributes-for-definition definition)))
           (when indexed-attributes?
         (update-indexed-attribute-properties
           definition t nil old-name?))))

       (when class-change-requires-kb-validation?
         (validate-kb-after-runtime-definition-change
           new-name? old-name? t))

       (when (and analyze-attributes-of-subclasses-if-necessary? new-name?
              (classp new-name?) (not loading-kb-p))
         ;; Analyze attributes of subclasses when it is possible that the
         ;; attribute locations may have been affected by this new
         ;; class.
         (analyze-attributes-of-subclasses-for-consistency
           new-name? t))        ; analyze inherited-attributes also.

       new-name?))))))




;;; `Foundation-class-change-p' returns the most refined foundation class of the
;;; previous direct superior chasses when it differs from the most refined
;;; foundation class of the new direct superior classes; otherwise it returns nil.

(defun foundation-class-change-p
    (previous-direct-superior-classes new-direct-superior-classes)
  (let ((previous-foundation-class
      (most-refined-foundation-class-of-direct-superiors
        previous-direct-superior-classes)))
    (when (not (eq previous-foundation-class
           (most-refined-foundation-class-of-direct-superiors
             new-direct-superior-classes)))
      previous-foundation-class)))




(defvar called-within-locate-or-create-junction-block-definition nil)
(defvar called-within-clear-text-loading nil)




;;; `Make-class-inheritance-path-for-user-defined-class' linearizes the acyclic
;;; directed graph of the class hierarchy with multiple inheritance.  The
;;; inheritance path for a new class is built by merging the inheritance paths
;;; of the direct superiors of the new class.  This function should only be
;;; called only when the direct superior classes are an acceptable set as
;;; determined by the slot value compiler for list-of-classes in GRAMMAR6.

;;; An example of the merging paths algorithm for a new class becoming a member
;;; of this class hierarchy:
;;;
;;;                                object
;;;                                /    \
;;;                               /      \
;;;                              A        B
;;;                             / \       /
;;;                            /  (1)   (2)
;;;                           /     \   /
;;;                           C       D
;;;                           \       /
;;;                           (2)   (1)
;;;                             \   /
;;;                            new-class
;;;
;;;
;;; The class inheritance path for new-class is initially (new-class)
;;;
;;; The direct superior classes for new-class are D, C.  Because a superior
;;; class which appears earlier in a set of direct superior classes has precedence
;;; over direct superior classes that come later in the set, D is given precedence
;;; over C in the class inheritance path for new-class.
;;;
;;;     class inheritance path for D:  (D A B object . . .)
;;;     class inheritance path for C:  (C A object . . .)
;;;
;;; The common ancestors in the direct superior class inheritance paths:  A object . . .
;;;
;;; For each common ancestor, add the classes that appear earlier than the common
;;; ancestor in the respective class inheritance paths of the direct superiors to the
;;; class inheritance path for the new class, processing each direct superior in
;;; order of precedence; then add the common ancestor.
;;;
;;; Processing the first common ancestor, A, the class inheritance path grows to:
;;;   (new-class D C A)
;;; Processing the second common ancestor, object, the class inheritance path grows
;;;   to (new-class D C A B object . . .)
;;; The class inheritance paths of the direct superiors will now merge on the same
;;; set of system-defined superiors and can be appended to the class inheritance
;;; path for new class, making the completed path:
;;;      (new-class D C A B object item entity block kb-frame root)

(defun make-class-inheritance-path-for-user-defined-class
       (new-class direct-superior-classes)
  (loop with path = (copy-list-using-frame-conses
              (class-inheritance-path 
            (class-description (car direct-superior-classes))))
    for superior-class in (cdr direct-superior-classes)
    for merging-path = nil
    for classes-collected = nil
    for superior-path
        = (copy-list-using-frame-conses
        (class-inheritance-path (class-description superior-class)))
    do (loop with list-of-common-ancestors
           = (loop for class in superior-path
               when (memq class path)
                 collect class using frame-cons)
         for common-ancestor in list-of-common-ancestors
         when (and (memq common-ancestor path)
               (memq common-ancestor superior-path))
           do (setq merging-path
                (nconc
                  merging-path
                  (loop for class in path
                    until (eq class common-ancestor)
                    for class-is-collected?
                        = (memq class classes-collected)
                    unless class-is-collected?
                      collect class using frame-cons
                    do
                (frame-pop path)
                (unless class-is-collected?
                  (frame-push class classes-collected)))
                  (loop for class in superior-path
                    until (eq class common-ancestor)
                    for class-is-collected?
                        = (memq class classes-collected)
                    unless class-is-collected?
                      collect class using frame-cons
                    do
                (frame-pop superior-path)
                (unless class-is-collected?
                  (frame-push class classes-collected)))
                  (frame-list common-ancestor)))
              (frame-pop path)
              (frame-pop superior-path)
         finally (reclaim-frame-list list-of-common-ancestors))
       (reclaim-frame-list superior-path)
       (reclaim-frame-list path)
       (setq path (copy-list-using-frame-conses merging-path))
       (reclaim-frame-list merging-path)
           (reclaim-frame-list classes-collected)
    finally
      ;; When there is a single direct superior class, path is the class-
      ;; inheritance of that superior; otherwise the merged path ends with
      ;; block.
      (setq path (frame-cons new-class path))
      (return
        (prog1 (copy-for-slot-value path)
          (reclaim-frame-list path)))))


        
          
;;; `Error messages for unacceptable sets of direct superior classes' are
;;; defined below and used for the slot value compiler code and the slot putter
;;; code for direct superior classes to inform the user of invalid sets.

(defun-simple no-editing-of-default-junction ()
  (tformat-text-string
    "The attributes of an automatically created junction block ~
     cannot be edited."))

(defun-simple default-junction-cannot-be-a-direct-superior-class
    (default-junction)
  (tformat-text-string
    "Because ~A is an automatically created junction block, ~
     it cannot be specified as a direct superior class."
    default-junction))

(defun-simple no-editing-of-transient-definition-with-defaults
    (message-defaults?)
  (if message-defaults?
      (tformat-text-string
    "The direct superior classes of a transient definition cannot be ~
         changed when the definition has default message properites. ~
         To make this change, the defaults must be removed first.")
      (tformat-text-string
    "The direct superior classes of a transient definition cannot be ~
         changed when the definitions has default overrides on ~
         system-defined attributes.  To make this change, the defaults ~
         must be removed first.")))

(defun-simple specified-an-internal-system-class (class)
  (tformat-text-string
    "~A is the name of a system-defined class that is not user-extensible."
    class))

(defun-simple direct-superior-not-the-class-definition-type
    (direct-superior class-primary-foundation-class)
  (cond ((eq class-primary-foundation-class 'object)
     (tformat-text-string
       "~A cannot be a direct superior on this object-definition because ~
                it is either a connection, a message, or an instantiable-item class."
       direct-superior))
    ((eq class-primary-foundation-class 'connection)
     (tformat-text-string
       "~A cannot be a direct superior on this connection-definition because ~
                it is either an object, a message, or an instantiable-item class."
       direct-superior))
    (t
     (tformat-text-string
       "~A cannot be a direct superior on this message-definition because ~
                it is either an object, a connection, or an instantiable-item class."
       direct-superior))))

(defun-simple superior-on-potential-superior-not-the-class-definition-type
    (prohibited-superior class-primary-foundation-class
             superior-potential-definition)
  (tformat-text-string
    "There is a potential superior class ~A which has a direct superior, ~
     ~A, that cannot be inherited by this ~(~A~) class ~
     because it is either ~A, or an instantiable-item class."
    (name-of-defined-class superior-potential-definition)
    prohibited-superior
    (case class-primary-foundation-class
      (object 'object-definition)
      (connection 'connection-definition)
      (t 'message-definition))      ; see note below
    (case class-primary-foundation-class
      (object "a connection, a message")
      (connection "an object, a message")
      (t "an object, a connection"))))

;; Note: before this was rewritten today, this had connection-definition in
;; error in the case where it should have had message-definition. (MHD 10/25/01)



(defun-simple potential-definition-cannot-inherit-foundation-class
    (prohibited-superior potential-definition specialized-definition-class)
  (let ((potential-definition-name (name-of-defined-class potential-definition)))
    (if potential-definition-name
    (if (eq specialized-definition-class 'object-definition)
        (tformat-text-string
          "There is a direct-superior class, ~A, on this definition that cannot ~
               be in the inheritance of a potential subclass, named ~A, which is being ~
               defined with an OBJECT-DEFINITION."
               prohibited-superior potential-definition-name)
        (tformat-text-string
          "There is a direct-superior class, ~A, on this definition that cannot ~
               be in the inheritance of a potential subclass, named ~A, which is being ~
               defined with a ~A." prohibited-superior potential-definition-name
           specialized-definition-class))
    (if (eq specialized-definition-class 'object-definition)
        (tformat-text-string
          "There is a direct-superior class, ~A, on this definition that cannot ~
               be in the inheritance of an unnamed potential subclass which is being ~
               defined with an OBJECT-DEFINITION." prohibited-superior)
        (tformat-text-string
          "There is a direct-superior class, ~A, on this definition that cannot ~
               be in the inheritance of an unnamed potential subclass which is being ~
               defined with a ~A."
               prohibited-superior specialized-definition-class)))))
    
(defun-simple direct-superior-not-the-mixed-hierarchy-type
    (direct-superior other-specialized-definition-class)
  (cond
    ((eq other-specialized-definition-class 'object-definition)
     (tformat-text-string
       "~A cannot be a direct-superior on this class-definition because ~
         object-definition is also used to define the hierarchy, and ~A ~
         is either a connection, message, or instantiable-item class."
       direct-superior direct-superior))
    ((eq other-specialized-definition-class 'connection-definition)
     (tformat-text-string
       "~A cannot be a direct-superior on this class-definition because ~
         connection-definition is also used to define the hierarchy, and ~A ~
         is either an object, message, or instantiable-item class."
       direct-superior direct-superior))
    (t
     (tformat-text-string
       "~A cannot be a direct-superior on this class-definition because ~
         message-definition is also used to define the hierarchy, and ~A ~
         is either an object, connection, or instantiable-item class."
       direct-superior direct-superior))))

(defun-simple potential-definition-superior-not-the-mixed-hierarchy-type
    (definition potential-definition prohibited-direct-superior)
  (let ((potential-definition-name?
      (name-of-defined-class potential-definition)))
    (cond
      ((frame-of-class-p definition 'object-definition)
       (if potential-definition-name?
       (tformat-text-string
         "A potential subclass, named ~A, will not be able to inherit ~
              from this object class because it has a direct-superior, ~A, ~
              that is either a message, connection, or instantiable-item class."
         potential-definition-name? prohibited-direct-superior)
       (tformat-text-string
         "An unnamed potential subclass will not be able to inherit ~
              from this object class because it has a direct-superior, ~A, ~
              that is either a message, connection, or instantiable-item class."
         prohibited-direct-superior)))
      ((frame-of-class-p definition 'connection-definition)
       (if potential-definition-name?
       (tformat-text-string
         "A potential subclass, ~A, will not be able to inherit ~
              from this connection class because it has a direct-superior, ~A, ~
              that is either a message, object, or instantiable-item class."
         potential-definition-name? prohibited-direct-superior)
       (tformat-text-string
         "An unnamed potential subclass will not be able to inherit ~
              from this connection class because it has a direct-superior, ~A, ~
              that is either a message, object, or instantiable-item class."
         prohibited-direct-superior)))
       (t
     (if potential-definition-name?
         (tformat-text-string
           "A potential subclass, ~A, will not be able to inherit ~
                from this message class because it has a direct-superior, ~A, ~
                that is either a object, connection, or instantiable-item class."
           potential-definition-name? prohibited-direct-superior)
         (tformat-text-string
           "An unnamed potential subclass will not be able to inherit ~
                from this message class because it has a direct-superior, ~A, ~
                that is either a object, connection, or instantiable-item class."
           prohibited-direct-superior))))))

(defun-simple potential-definition-class-type-is-incompatible
    (potential-definition specialized-potential-definition-class subclass-or-superior)
  (let ((potential-definition-name? (name-of-defined-class potential-definition)))
    (tformat-text-string
      "There is ~A ~(~a~) that is defined with ~A ~A."
      (if potential-definition-name? "a potential" "an unnamed potential")
      subclass-or-superior
      (if potential-definition-name? ", named " "")
      (or potential-definition-name? "")
      (if potential-definition-name? ", " "")
      (supply-a-or-an specialized-potential-definition-class)
      specialized-potential-definition-class)))

(defun-simple incompatible-definition-classes (specialized-definition-class prohibited-superior)
  (tformat-text-string
    "~A cannot be a direct superior on this ~A because it is ~Adefined with an ~A."
    prohibited-superior
    specialized-definition-class
    (if (classp prohibited-superior) "" "being ")
    (get-specialized-definition-class (class-definition prohibited-superior))))
       

(defun-simple system-inheritance-change-for-instantiated-class
    (class? no-instantiable-direct-superior? undefined-direct-superior?
        previous-foundation-class? new-foundation-class? reverting-to-none?)
  (cond (no-instantiable-direct-superior?
     (tformat-text-string
       "Because there is no instantiable direct superior class, this ~
            change cannot be made to an instantiated class.  The instances ~
            must be deleted first."))
    (undefined-direct-superior?
     (tformat-text-string
       "Because ~A is undefined, it cannot be specified as a ~
            direct superior for an instantiated class.  To make ~
            this change, the instances must be deleted first."
       undefined-direct-superior?))
    (reverting-to-none?
     (tformat-text-string
       "The direct superior classes of an instantiated class ~
            cannot revert to NONE.  To make this change, the ~
            instances must be deleted first."))
    (t
     (tformat-text-string
       "The foundation class of an instantiated class cannot be ~
            changed because it would alter the basic system inheritance ~
            of the class.  The foundation class for ~A is presently ~A.  ~
            To change it to ~A, its instances must be deleted first."
       class? previous-foundation-class? new-foundation-class?))))

(defun-simple circularity-in-potential-definition-inheritance
    (prohibited-superior)
  (tformat-text-string
    "This value would cause circular class inheritance because there ~
     is a potential subclass for ~A that has this class as a direct ~
     superior." prohibited-superior))

(defun-simple invalidates-direct-superiors-for-potential-definition
    (potential-definition-class-name? first-foundation-class
                      second-foundation-class)
  (tformat-text-string
    "This direct-superior-classes value would invalidate the ~
         direct superiors for a potential ~
         subclass~A~A.  It would give the subclass two ~
         incompatible foundation classes, ~a and ~a."
    (if potential-definition-class-name? " named " "")
    (or potential-definition-class-name? "")
    first-foundation-class
    second-foundation-class))

(defun-simple circularity-of-inheritance-in-the-class-hierarchy
    (class-name prohibited-superior)
  (tformat-text-string
    "This change would cause circular inheritance in the class ~
     hierarchy because a potential superior of ~A, ~A, currently ~
     lists ~A as a direct superior."
    class-name prohibited-superior class-name))

(defun-simple direct-superior-is-name-of-class ()
  (tformat-text-string
    "A direct superior class cannot be the same symbol as the name ~
     of the class"))

(defun-simple subclass-appears-after-superior-in-direct-superior-classes
    (superior-class inferior-class)
  (if (eq superior-class inferior-class)
      (tformat-text-string
    "The symbol ~A appears more than once." superior-class)
      (tformat-text-string
    "When two direct superior classes have an inferior/superior ~
         relationship, the inferior class should be placed before ~
         its superior, or the superior class can be omitted ~
         because its inferior has inherited its attributes. ~
         Here ~A is superior to ~A."
    superior-class inferior-class)))

(defun-simple subclass-appears-after-superior-for-subclass-direct-superiors
    (superior-class inferior-class subclass)
  (tformat-text-string
    "This change invalidates the inferior/superior ordering of two ~
     direct superior classes, ~A and ~A, for a subclass ~A."
    superior-class inferior-class subclass))

(defun-simple subclass-appears-after-superior-for-potential-definition
    (superior-class inferior-class potential-definition-name?)
  (tformat-text-string
    "This change invalidates the inferior/superior ordering of two ~
         direct superior classes, ~A and ~A, for ~A~A."
    superior-class inferior-class
    (if potential-definition-name?
    "a potential subclass named "
    "an unnamed potential subclass")
    (or potential-definition-name? "")))

(defun-simple disjoint-foundation-classes
    (first-foundation-class second-foundation-class)
  (tformat-text-string
    "This would give the new class two system-defined foundation classes, ~
         ~A and ~A, that are incompatible."
    first-foundation-class second-foundation-class))

(defun-simple disjoint-foundation-classes-for-subclass-or-potential-definition
    (first-foundation-class second-foundation-class problem-inferior-class?)
  (tformat-text-string
    "This choice of direct-superior classes would give ~A~A~A~
    two system-defined foundation classes, ~A and ~A, that are incompatible."
    (if problem-inferior-class? "a subclass, named " "the potential subclass ")
    (or problem-inferior-class? "")
    (if problem-inferior-class? ", " "")
    first-foundation-class second-foundation-class))

(defun-simple disjoint-superior-classes
    (first-foundation-class second-foundation-class)
  (tformat-text-string
    "This would give the new class two superior classes, ~
     ~A and ~A, that are incompatible."
    first-foundation-class second-foundation-class))

(defun-simple disjoint-superior-classes-for-potential-definition
    (potential-definition-class-name? first-foundation-class
                      second-foundation-class)
  (tformat-text-string
    "This direct-superior-classes value would give a ~
         potential subclass~A~A two ~
         superior classes, ~A and ~A, that are ~
         incompatible."
    (if potential-definition-class-name? " named " "")
    (or potential-definition-class-name? "")
    first-foundation-class second-foundation-class))

(defun-simple direct-superior-incompatible-with-foundation-class
    (direct-superior foundation-class compatible-class?)
  (if compatible-class?
      (tformat-text-string
    "~A is not compatible with the proposed foundation class, ~A. ~
         ~A is only compatible with ~A classes."
    direct-superior foundation-class direct-superior
    compatible-class?)
      (tformat-text-string
    "~A is not compatible with the potential foundation class, ~A."
    direct-superior foundation-class)))

(defun-simple definition-has-irreconcilable-dependencies
    (dependent-definition)
  (tformat-text-string
    "The direct superior classes for this definition will make savability ~
     impossible because this definition and the definition for ~A ~
     mutually depend on each other for their inheritance."
     (name-of-defined-class dependent-definition)))

(defun-simple direct-superiors-give-ancestors-different-precedence
    (one-direct-superior another-direct-superior inferior-class?
             potential-inferior-class?)
  (cond (inferior-class?
     (tformat-text-string
       "This change would invalidate the inheritance of an inferior class, ~
            ~A, because the inheritance paths of two direct superior classes ~
            of ~A, ~A and ~A, would have common superior classes but not in ~
            the same precedence ordering, making the superior class precedence ~
            ordering for ~A ambiguous.  Either choose different direct superiors ~
        for this class or for ~A."
       inferior-class? inferior-class? one-direct-superior
       another-direct-superior inferior-class? inferior-class?))
    (potential-inferior-class?
     (if (name-of-defined-class potential-inferior-class?)
         (let ((potential-name
             (name-of-defined-class potential-inferior-class?)))
           (tformat-text-string
             "This change would invalidate the inheritance of a potential ~
                      subclass, named ~A, because the inheritance paths of two direct ~
                      superior classes of ~A, ~A and ~A, would have common superior ~
                      classes but not in the same precedence ordering, making the ~
                      superior class precedence ordering for ~A ambiguous.  Either ~
                      choose different direct superiors for this class or for ~A, ~
                      or delete ~A."
             potential-name potential-name one-direct-superior
             another-direct-superior potential-name potential-name
             potential-name))
         (tformat-text-string
           "This change would invalidate the inheritance of an unnamed ~
                potential subclass because the inheritance paths of two ~
                direct superior classes of the potential subclass, ~A and ~A, ~
                would have common superior classes but not in the same ~
                precedence ordering, making the superior class precedence ~
                ordering for the potential subclass ambiguous.  Either ~
                choose different direct superiors for this class or for ~
                the potential subclass, or delete the potential subclass definition."
           one-direct-superior another-direct-superior)))
    (t
     (tformat-text-string
       "The inheritance paths of two direct superiors, ~A and  ~A, have ~
            common superior classes but they are not given the same precedence ~
            ordering, making the superior class precedence ordering for the ~
            new class ambiguous."
       one-direct-superior another-direct-superior))))

(defun-simple class-hierarchy-subgraph-precedence-violated
    (one-direct-superior another-direct-superior common-ancestor
       inferior-class? potential-inferior-class? potential-name?)
  (cond (inferior-class?
     (tformat-text-string
       "This change would invalidate the inheritance of an inferior class, ~
            ~A, because it would cause two direct superiors of ~A, ~A and ~A, ~
            to have a common ancestor, ~A, but they would not give ~A or a ~
            subclass of ~A the same precedence in their own sets of direct ~
            superiors.  This situation would give precedence to a class that ~
            is outside of the branch of the class hierarchy that includes the ~
            two direct superiors and their common ancestor."
       inferior-class? inferior-class? one-direct-superior
       another-direct-superior common-ancestor common-ancestor
       common-ancestor))
    (potential-inferior-class?
     (if potential-name?
         (tformat-text-string
           "This change would invalidate the inheritance of a potential ~
                subclass, ~A, because it would cause two direct superiors ~
                of ~A, ~A and ~A, to have a common ancestor, ~A, but they would ~
                not give ~A or a  subclass of ~A the same precedence in their ~
                own sets of direct superiors.  This situation would give ~
                precedence to a class that is outside of the branch of the ~
                class hierarchy that includes the two direct superiors and ~
                their common ancestor."
           potential-name? potential-name? one-direct-superior
           another-direct-superior common-ancestor common-ancestor
           common-ancestor)
         (tformat-text-string
           "This value would invalidate the inheritance of an unnamed ~
                potential subclass because it would cause two direct ~
                superiors of the potential definition, ~A and ~A, to have ~
                a common ancestor, ~A, but they would not give ~A or a ~
                subclass of ~A the same precedence in their own sets of ~
                direct superiors.  This situation would give precedence ~
                to a class that is outside of the branch of the class ~
                hierarchy that includes the two direct superiors and ~
                their common ancestor."
           one-direct-superior another-direct-superior common-ancestor
           common-ancestor common-ancestor)))
     (t
       (tformat-text-string
         "Two direct superiors, ~A and ~A, have a common ancestor, ~
              ~A, but they do not give ~A or a subclass of ~A the ~
              same precedence in their own sets of direct superiors. ~
              This situation would give precedence to a class that ~
              is outside of the branch of the class hierarchy that ~
              includes the two direct superiors and their common ancestor."
         one-direct-superior another-direct-superior common-ancestor
         common-ancestor common-ancestor))))

(defun-simple potential-definition-has-different-class-type
    (class-name specialized-definition-class potential-definition)
  (let ((specialized-potential-definition-class
      (get-specialized-definition-class potential-definition))
    (potential-definition-class-name?
      (name-of-defined-class potential-definition)))
    (if potential-definition-class-name?
    (tformat-text-string
      "The definition types of a class and its potential subclasses must be ~
           compatible.  There is a potential subclass, named ~A, with ~A as a superior, ~
           but the definition type of ~A is ~A, while this definition type is ~A."
      potential-definition-class-name? class-name potential-definition-class-name? 
      specialized-potential-definition-class specialized-definition-class)
    (tformat-text-string
      "The definition types of a class and its potential subclass must be ~
           compatible.  There is a unnamed potential class with ~A as a superior, ~
           but its definition type is ~A, while this defintion type is ~A."
      class-name specialized-potential-definition-class
      specialized-definition-class))))

 
      

(defun collect-potential-definitions (class)
  (let* ((definitions (frame-list class))
     (definitions-tail-pointer definitions))
    (loop for potential-definitions-traversal-pointer
          = definitions
          then (cdr-of-cons potential-definitions-traversal-pointer)
      while potential-definitions-traversal-pointer
      for superior = (car-of-cons potential-definitions-traversal-pointer)
      do
      (loop for potential-definition in (potential-inferior-class-definitions
                      (if (framep superior)
                          (name-of-defined-class superior)
                          superior))
        do
    (unless (memq potential-definition definitions)
      (let ((new-definition-cons (frame-list potential-definition)))
        (setf (cdr definitions-tail-pointer) new-definition-cons)
        (setq definitions-tail-pointer new-definition-cons)))))
    (reclaim-frame-cons 
      (prog1 definitions
    (setq definitions (cdr definitions))))
    definitions))

(defun rule-2-violation-for-potential-definitions (class class-inheritance-path)
  (let ((potential-definitions (collect-potential-definitions class))
    (potential-definition-class-inheritance-paths
      (frame-list (copy-list-using-frame-conses class-inheritance-path)))
    (prohibited-superior? nil)
    (colliding-superior? nil)
    (problem-potential-definition? nil))
    (loop with class-name-counter = 0
      for potential-definition in potential-definitions
      for potential-class-name = (name-of-defined-class potential-definition)
      for direct-superiors = (direct-superiors-of-defined-class
                   potential-definition)
      for other-direct-superiors-not-defined? =
      (loop for superior in direct-superiors
        thereis
        (and (not (classp superior))
             (not (member superior
                  potential-definition-class-inheritance-paths
                  :test 'car-eq))))
      do
      (unless other-direct-superiors-not-defined?
    (let* ((class-inheritance-paths
         (let ((paths nil))
           (loop for superior in direct-superiors
             do
             (if (classp superior)
             (setq paths
                   (nconc paths
                      (frame-list (class-inheritance-path
                            (class-description superior)))))
             (setq paths
                   (nconc paths
                      (frame-list
                    (car
                      (member superior
                          potential-definition-class-inheritance-paths
                          :test 'car-eq)))))))
           paths)))
      (multiple-value-setq (prohibited-superior? colliding-superior?)
        (merging-paths-common-ancestor-rule-2-violation-p
          class-inheritance-paths))
      (reclaim-frame-list class-inheritance-paths)
      (if prohibited-superior?
          (return (setq problem-potential-definition? potential-definition))
          (let ((potential-definition-inheritance-path
              (loop with first-direct-superior = (car direct-superiors)
                with path =
                (copy-list-using-frame-conses
                  (if (classp first-direct-superior)
                  (class-inheritance-path
                    (class-description first-direct-superior))
                  (car (member first-direct-superior
                           potential-definition-class-inheritance-paths
                           :test 'car-eq))))
                with merging-path = nil
                for superior-class in (cdr direct-superiors)
                for superior-path =
                (copy-list-using-frame-conses
                  (if (classp superior-class)
                  (class-inheritance-path
                    (class-description superior-class))
                  (car (member superior-class
                           potential-definition-class-inheritance-paths
                           :test 'car-eq))))

                do
            (loop with list-of-common-ancestors =
                  (loop for class in superior-path
                    until (eq class 'kb-frame)
                    when (memq class path)
                      collect class using frame-cons)
                  for common-ancestor in list-of-common-ancestors
                  do
              (setq merging-path
                (nconc
                  merging-path
                  (loop for class in path
                    until (eq class common-ancestor)
                    collect class using frame-cons
                    do
                    (frame-pop path))
                  (loop for class in superior-path
                    until (eq class common-ancestor)
                    collect class using frame-cons
                    do
                    (frame-pop superior-path))
                  (frame-list common-ancestor)))
              (frame-pop path)
              (frame-pop superior-path)
                  finally (reclaim-frame-list list-of-common-ancestors))

            (reclaim-frame-list superior-path)
            (reclaim-frame-list path)
            (setq path (copy-list-using-frame-conses merging-path))
            (reclaim-frame-list merging-path)
            (setq merging-path nil)
                finally
                  (let ((top-of-class-hierarchy
                      (when (cdr direct-superiors)
                    (nconc (frame-list 'kb-frame) (frame-list 'root)))))
                (setq path
                      (frame-cons
                    (if potential-class-name
                        potential-class-name
                        (prog1
                        (intern-text-string
                          (tformat-text-string
                            "POTENTIAL-XXX~A" class-name-counter))
                          (setq class-name-counter
                            (1+f class-name-counter))))
                    (nconc path top-of-class-hierarchy)))
                (return path)))))
        (setq potential-definition-class-inheritance-paths
              (frame-cons potential-definition-inheritance-path
                  potential-definition-class-inheritance-paths)))))))
    (reclaim-frame-list potential-definitions)
    (reclaim-frame-tree potential-definition-class-inheritance-paths)
    (values problem-potential-definition? prohibited-superior? colliding-superior?)))
    



;;; `Merging-paths-common-ancestor-rule-2-violation-p' returns an error
;;; condition when the inheritance paths of two superior classes have classes in
;;; common but the common classes are given a different ordering.

(defun merging-paths-common-ancestor-rule-2-violation-p (class-inheritance-paths)
  (let ((ancestor-error-condition? nil)
    (prohibited-superior? nil)
    (colliding-superior? nil))

    (loop for sublist on class-inheritance-paths
      when ancestor-error-condition?
        return ancestor-error-condition?
      until (null (cdr sublist))
      for first-path = (car sublist)
      do
      (loop for comparison-path in (cdr sublist)
        for first-path-common-ancestor-ordering =
              (loop for class in first-path
            until (eq class 'item)
            when (and (not (system-defined-class-p class))
                  (memq class comparison-path))
              collect class using frame-cons)
        for comparison-path-common-ancestor-ordering =
              (loop for class in comparison-path
            until (eq class 'item)
            when (and (not (system-defined-class-p class))
                  (memq class first-path))
              collect class using frame-cons)
        do
    (cond ((not (equal first-path-common-ancestor-ordering
               comparison-path-common-ancestor-ordering))
           (reclaim-frame-list first-path-common-ancestor-ordering)
           (reclaim-frame-list comparison-path-common-ancestor-ordering)
           (setq prohibited-superior? (car-of-cons comparison-path))
           (setq colliding-superior? (car-of-cons first-path))
           (return (setq ancestor-error-condition? t)))
          (t (reclaim-frame-list first-path-common-ancestor-ordering)
         (reclaim-frame-list
           comparison-path-common-ancestor-ordering)))))
    (values prohibited-superior? colliding-superior?)))




;;; The function `inconguent-inheritance-path-orderings-p' takes two
;;; class-inheritance-paths and determines whether or not the common classes
;;; between the two inheritance paths are listed in the same order within the
;;; two lists.  When the orderings are wrong, the first class that had an
;;; incongruent ordering is returned.

#+development
(defun-simple inconguent-inheritance-path-orderings-p
    (first-path second-path new-class)
  (loop with common-list = (loop for class in first-path
                 until (eq class 'item)
                 when (and (or (user-defined-class-p class)
                           (eq class new-class))
                       (memq class second-path))
                   collect class using frame-cons)
    with current-second-path-head = second-path
    for common-class in common-list
    do
    (loop for second-path-cons on current-second-path-head
      do
      (when (eq common-class (car-of-cons second-path-cons))
    (setq current-second-path-head (cdr-of-cons second-path-cons))
    (return nil))
      finally
        (reclaim-frame-list common-list)
        (return-from inconguent-inheritance-path-orderings-p common-class))
    finally
      (reclaim-frame-list common-list)
      (return-from inconguent-inheritance-path-orderings-p nil)))
          
    


;;; `Merging-paths-common-ancestor-rule-3-violation-p' returns a error condition
;;; when two direct superior classes have a common ancestor but they do not give
;;; the common ancestor, or a subclass of the common ancestor, the same
;;; precedence in their own sets of direct superior classes.

#+development
(defun merging-paths-common-ancestor-rule-3-violation-p (direct-superior-classes)
  (let ((incongruent-class? nil)
    (common-ancestor? nil)
    (faulty-direct-superior? nil)
    (comparison-direct-superior? nil))
    (loop with error-condition? = nil
      for sublist on direct-superior-classes
      until (or error-condition? (null (second sublist)))
      for first-direct-superior = (car sublist)
      for first-class-description = (class-description first-direct-superior)
      for first-inheritance-path = (class-inheritance-path
                     first-class-description)
      do
      (loop for comparison-direct-superior in (cdr sublist)
        until error-condition?
        for comparison-class-description = (class-description
                         comparison-direct-superior)
        for comparison-inheritance-path = (class-inheritance-path
                        comparison-class-description)
        for common-ancestors = (loop for class in first-inheritance-path
                      until (eq class 'item)
                      when (memq class
                             comparison-inheritance-path)
                        collect class using frame-cons)
        do
    (loop for ancestor in common-ancestors
          for first-subgraph-classes =
          (loop for class being each superclass of first-direct-superior
            when (subclassp class ancestor)
              collect class using frame-cons)
          for first-path-incongruent-class? =
          (loop for class in (cdr first-inheritance-path)
            until (eq class ancestor)
            when (not (memq class first-subgraph-classes))
              return class)
          for comparison-subgraph-classes =
          (loop for class being each superclass of comparison-direct-superior
            when (subclassp class ancestor)
              collect class using frame-cons)
          for comparison-path-incongruent-class? =
          (loop for class in (cdr comparison-inheritance-path)
            until (eq class ancestor)
            when (not (memq class comparison-subgraph-classes))
              return class)
          thereis (or (and (setq incongruent-class? first-path-incongruent-class?)
                   (setq common-ancestor? ancestor)
                   (setq faulty-direct-superior? first-direct-superior)
                   (setq comparison-direct-superior? comparison-direct-superior)
                   (setq error-condition? t)
                   (progn (reclaim-frame-list common-ancestors) t))
              (and (setq incongruent-class? comparison-path-incongruent-class?)
                   (setq common-ancestor? ancestor)
                   (setq faulty-direct-superior? comparison-direct-superior)
                   (setq comparison-direct-superior? first-direct-superior)
                   (setq error-condition? t)
                   (progn (reclaim-frame-list common-ancestors) t)))
          finally (reclaim-frame-list common-ancestors))))
    (values incongruent-class? common-ancestor? faulty-direct-superior?
    comparison-direct-superior?)))




;;; The predicate `incorrect-foundation-class-for-this-definition-p' returns
;;; a non-null value when a direct-superior cannot be supported by the
;;; definition used to define a class.  This predicate is currently used by
;;; the slot-putter for name-of-defined-class and the compiler for class
;;; (for potential-inferior-classes) and the slot-putter for direct-superiors-
;;; of-defined-class and the compiler for list-of-classes (for subclasses).

(defun incorrect-foundation-class-for-this-definition-p
    (direct-superiors class-primary-foundation-class
              other-specialized-definition-class?)
  (loop for superior in direct-superiors
    for superior-primary-foundation-class
        = (cond ((subclassp superior 'object) 'object)
            ((subclassp superior 'connection) 'connection)
            ((subclassp superior 'message) 'message)
            (t 'item))
    do
    (when (classp superior)
              ;; Allow any item that has a foundation-class to be
              ;; a direct superior on class-definitions that are
              ;; not in mixed hierarchies.
      (unless (or (and (eq class-primary-foundation-class 'item)
               (null other-specialized-definition-class?))
          
          ;; Allow abstract/mixin item direct superiors in
          ;; all definitions.
          (and (eq superior-primary-foundation-class 'item)
               (feature-assq
             'not-solely-instantiable
             (class-features (class-description superior))))
          
          ;; Restrict direct superiors on object/connection/message-
          ;; definitions to be not-solely-instantiable item classes
          ;; and object/connection/message classes respectively.
          (and (or (eq class-primary-foundation-class 'object)
               (eq other-specialized-definition-class?
                   'object-definition))
               (neq superior-primary-foundation-class 'connection)
               (neq superior-primary-foundation-class 'message)
               (neq superior-primary-foundation-class 'item))
          (and (or (eq class-primary-foundation-class 'connection)
               (eq other-specialized-definition-class?
                   'connection-definition))
               (neq superior-primary-foundation-class 'object)
               (neq superior-primary-foundation-class 'message)
               (neq superior-primary-foundation-class 'item))
          (and (or (eq class-primary-foundation-class 'message)
               (eq other-specialized-definition-class?
                   'message-definition))
               (neq superior-primary-foundation-class 'object)
               (neq superior-primary-foundation-class 'connection)
               (neq superior-primary-foundation-class 'item)))
    (return superior)))))




;;; The variables `definition-being-analyzed-for-savability' and
;;; `definitions-that-have-been-visited' are used to test user-defined
;;; class-definition class hierarchies for inheritance cycles that would make
;;; the kb unsavable.  The definition-being-analyzed-for-savability is bound by
;;; the compiler for list-of-classes which is the grammar category for
;;; direct-superiors-of-defined-class, and by the function,
;;; invalid-set-of-direct-superior-classes-p, which is called when the value of
;;; the direct-superiors-of-defined-class is chosen from the menu.

(defvar definition-being-analyzed-for-savability nil)
(defvar definitions-that-have-been-visited nil)




;;; The function `definition-is-not-savable-p' with its recursive helper
;;; function `definition-is-not-savable-aux-p' is used to discover inheritance
;;; cycles in user-defined class-definition class hierarchies.

;;; There are two types of links in these hierarchies.  One is the link between
;;; a definition class and its direct-superior classes, and the other is the
;;; link between the definition class and the class-type of the definition it
;;; is being defined on.

;;; When these links produce an unsavable/unloadable class-definition ordering,
;;; this function returns a non-null value which is the class-definition with
;;; which the definition argument is mutually dependent for its inheritance;
;;; otherwise it returns nil.

(defun-simple definition-is-not-savable-p (definition direct-superiors)
  (setq definition-being-analyzed-for-savability definition)
  (let ((mutually-dependent-definition?
      (definition-is-not-savable-aux-p definition direct-superiors)))
    (reclaim-frame-list definitions-that-have-been-visited)
    (setq definitions-that-have-been-visited nil)
    mutually-dependent-definition?))
  
(defun-simple definition-is-not-savable-aux-p (definition direct-superiors)
  
  (frame-push definition definitions-that-have-been-visited)
  
  ;; The frame-consed-dependent-definitions? will consist of the user-defined
  ;; class-definition that defines the class-type for this definition (if any),
  ;; and the definitions for the direct-superior classes that are user-defined
  ;; class-definitions.
  (let ((frame-consed-dependent-definitions?
      (nconc
        (let* ((class-of-definition (class definition)) 
           (definition-for-class-of-definition      
               (class-definition class-of-definition)))
          (and (framep definition-for-class-of-definition)
           (frame-list definition-for-class-of-definition)))
        (loop for superior in direct-superiors
          for superior-class-definition = (class-definition superior)
          when (and (subclassp superior 'class-definition)
                (framep superior-class-definition))
            collect superior-class-definition using frame-cons))))
    
    (cond (frame-consed-dependent-definitions?
       (loop for dependent-definition in frame-consed-dependent-definitions?
         do
               ;; When the definition we are testing for savability becomes
               ;; a dependent definition, there is a cycle in the definition
               ;; class hierarchy and we return the value of the last argument
               ;; to this function.
         (cond ((eq dependent-definition definition-being-analyzed-for-savability)
            (reclaim-frame-list frame-consed-dependent-definitions?)
            (return definition))
           (t
            (unless (memq dependent-definition
                  definitions-that-have-been-visited)
              (let ((definition-is-not-savable?
                (definition-is-not-savable-aux-p
                    dependent-definition
                    (direct-superiors-of-defined-class
                      dependent-definition))))
            (when definition-is-not-savable?
              (reclaim-frame-list frame-consed-dependent-definitions?)
              (return definition-is-not-savable?))))))
         finally
           (progn (reclaim-frame-list frame-consed-dependent-definitions?)
              nil)))
      (t nil))))

  
  
  
;;; The `slot putter for direct-superiors-of-defined-class' ...

;;; `Invalid-set-of-direct-superior-classes-p' is called by the slot putter code
;;; for direct-superiors-of-defined-class to check for invalid sets of direct
;;; superior classes and notify the user when it finds one.  When the set is
;;; invalid, this function calls notify-user to give an error message and
;;; returns t; otherwise it returns nil, silently.

;;; This code is for the specification of direct superior classes that by-pass
;;; the compiler code.  This will happen for menu choices which currently
;;; support single choices only.

;;; The individual tests for a valid set of direct superior classes is done by
;;; calling do-valid-superior-tests, which runs test functions defined via the
;;; macro def-valid-superior-test, defined in a subsection below.

(defun invalid-set-of-direct-superior-classes-p (direct-superior-classes? definition)
  (cond
    ((equal direct-superior-classes?
        (direct-superiors-of-defined-class definition))
     ;; If new = previous direct superiors, then nil (OK)
     nil)
    (t
     (let* ((possible-class-inheritance-path?
          (if (direct-superiors-are-defined-p direct-superior-classes?)
          (make-class-inheritance-path-for-user-defined-class
            (name-of-defined-class definition)
            direct-superior-classes?)))
        (error-string?
          (do-valid-superior-tests
        direct-superior-classes?
        definition
        possible-class-inheritance-path?)))
       (prog1 (when error-string?
        (notify-user "~a" error-string?)
        (reclaim-text-string error-string?)
        t)
     (if possible-class-inheritance-path?
         (reclaim-slot-value possible-class-inheritance-path?)))))))

(defun invalid-class-hierarchy (direct-superior-classes-qm definition)
    (let* ((user-class (name-of-defined-class definition))
            temp-definition parent)
        (block verification-loop
            (loop for superior-classes in direct-superior-classes-qm do
                (setq temp-definition 
                    (lookup-global-or-kb-specific-property-value 
                        superior-classes 'class-definition))
                (if (not temp-definition)
                    (return-from verification-loop))
                ;; Need more investigations here !!!
                (setq parent (if (consp temp-definition) ; (redef-class ...)
                                 (caadr temp-definition)
                               (class-name-of-class-description 
                                (class-description-slot temp-definition))))
                (if (eq user-class parent)
                    (return-from invalid-class-hierarchy t))))
        nil))


;; Note that as of version 4.0, a change to the superior-classes is no longer
;; invalid when G2 is running or paused.  - cpm, 3/15/94

;; Note that as of version 4.0, the direct-superiors-of-defined-class slot of
;; definitions is no longer restricted from being done while G2 is running or
;; paused.  - cpm, 3/15/94

(def-slot-putter direct-superiors-of-defined-class
    (class-definition new-value initializing?)
  ;; Deferral of analysis is needed particularly by the cached-attribute
  ;; free-reference.  It is done for efficiency reasons and, also, so that
  ;; changes to definitions are completed before the analysis is done.

  ;; Menu choices are single symbols.
  (when (and new-value (atom new-value))
    (setq new-value (slot-value-list new-value)))
  (decache-dynamic-menus 'class-name)
  (defer-some-consistency-analysis

    (decache-class-chaining-lists)
    
    (when (equal new-value (direct-superiors-of-defined-class class-definition))
      (setf (direct-superiors-of-defined-class class-definition) new-value)
      (update-representations-of-slot-value
       class-definition 'direct-superiors-of-defined-class)
      (return-from put-direct-superiors-of-defined-class (values new-value nil)))

    (when (and (not loading-kb-p)
           (not called-within-locate-or-create-junction-block-definition)
           (not called-within-clear-text-loading)
           (name-of-defined-class class-definition)
           (null (superblock? class-definition))
           (not (transient-p class-definition)))
      (reclaim-slot-value new-value)
      (return-from put-direct-superiors-of-defined-class
        (values (direct-superiors-of-defined-class class-definition) t)))

    (when (and (not initializing?)
               (invalid-set-of-direct-superior-classes-p new-value class-definition))
      (return-from put-direct-superiors-of-defined-class
        (values (direct-superiors-of-defined-class class-definition) t)))

    (when (invalid-class-hierarchy new-value class-definition)
      (notify-engineer 
       "Unable to conclude a new value into the direct-superior-classes of ~a."
       (name-of-defined-class class-definition))
      (return-from put-direct-superiors-of-defined-class
        (values (direct-superiors-of-defined-class class-definition) t)))

    (let* ((new-direct-superiors?
         (when new-value
           (let ((substituted-value new-value))
         (loop for class in new-value
               for substitute-class = (substitute-class class)
               do
           (when substitute-class
             (let ((cons-holding-class
                 (memq class substituted-value)))
               (setf (car cons-holding-class) substitute-class))))
         substituted-value)))
       (direct-superiors-are-defined?
         (direct-superiors-are-defined-p new-direct-superiors?))
       (user-class? (name-of-defined-class class-definition))
       (definition-class (class class-definition))
       (previous-direct-superiors? 
         (direct-superiors-of-defined-class class-definition))
       (previous-direct-superiors-are-defined?
         (direct-superiors-are-defined-p previous-direct-superiors?))
       (previous-class-inheritance-path?
         (class-inheritance-path-of-definition class-definition))
       (current-computation-frame-previously-bound?
         (and (boundp '*current-computation-frame*)
          (framep *current-computation-frame*)))
       (change-of-foundation-class?
         (when (and direct-superiors-are-defined?
            previous-direct-superiors-are-defined?)
           (foundation-class-change-p
         new-direct-superiors? previous-direct-superiors?)))
       (any-class-instances? nil)
       (class-change-requires-kb-validation? nil)
       (old-indexed-attribute-info-if-not-reset? nil)
       (class-change-requires-indexed-attribute-update? nil)
       (this-definition-is-a-class-definition?
         (eq (class class-definition) 'class-definition))
       (previous-system-classes
         (loop for class in previous-class-inheritance-path?
           when (system-defined-class-p class)
             collect class using frame-cons)))
      ;; Test for instances before any definition changes are made.
      (when (and user-class? (classp user-class?))
    (loop for thing being each class-instance of user-class?
          do
      (setq any-class-instances? t)
          until any-class-instances?))

      ;; In continue-read-kb, before automatically resolving conflicts,
      ;; all indexed-attribute hash-tables are reclaimed, and remade
      ;; afterwards.  The unless form below prevents the calling of
      ;; clear-indexed-attribute-hash-table and update-indexed-attribute-
      ;; hash-table, both of which, assume update-to-date hash tables.
      (unless (or loading-kb-p
          currently-automatically-resolving-class-name-conflicts?)
    (when (and user-class? any-class-instances?
           (or system-has-paused system-is-running))
      (setq class-change-requires-indexed-attribute-update? t)
      (setq old-indexed-attribute-info-if-not-reset?
        ;; Collect the old, inherited indexed-attributes before the old
        ;; superiors are removed.  Note that this is a gensym-list that
        ;; must be RECLAIMED below.
        (collect-all-indexed-attributes-for-class user-class?))))

      (unless current-computation-frame-previously-bound?
    (setq *current-computation-frame* class-definition))

      ;; Clear the existing direct superior frame notes.
      (delete-multiple-frame-notes-if-any
    '(undefined-direct-superiors no-direct-superiors
      inconsistent-instantiate-value) class-definition)
      ;; Any "incomplete" status is cleared, and then readjusted in the
      ;; conditions below.
      (update-frame-status class-definition nil t)
      (reclaim-slot-value
    (class-inheritance-path-of-definition class-definition))
      (setf (class-inheritance-path-of-definition class-definition) nil)
      (when this-definition-is-a-class-definition?
    (reclaim-slot-value
      (user-overridable-system-slots class-definition))
    (setf (user-overridable-system-slots class-definition) nil))

      ;; When the class definition is not complete, set the potential-
      ;; inferior-class-definitions properties of the direct superiors.
      (when (or (null user-class?)
        (not direct-superiors-are-defined?)
        (transient-p class-definition))
    (loop for superior in new-direct-superiors?
          do
      (setf (potential-inferior-class-definitions superior)
        (class-description-pushnew
          class-definition
          (potential-inferior-class-definitions superior)))))
      (decache-cached-class-data user-class?)
      
      (cond
    ((classp user-class?)
     (when any-class-instances?
       (setq class-change-requires-kb-validation? t))

     ;; The class will revert to undefined if the new slot value
     ;; is reverting to none or has any undefined classes.
     (cond
       ;; Reverting to none.
       ((null new-direct-superiors?)
        (update-frame-status class-definition 'incomplete t)
        (add-frame-note 'no-direct-superiors class-definition)
        (undefine-user-class class-definition nil nil)
        (setf (direct-superiors-of-defined-class class-definition) nil))
       ;; Undefined direct superiors.
       ((not direct-superiors-are-defined?)
        (update-frame-status class-definition 'incomplete t)
        (loop for superior in new-direct-superiors?
          do
          (when (not (classp superior))
        (add-to-frame-note-particulars-list-if-necessary
          superior 'undefined-direct-superiors class-definition)))
        (undefine-user-class class-definition nil nil)
        (setf (direct-superiors-of-defined-class class-definition)
          new-direct-superiors?))
       ;; Foundation class is unchanged.
       ((not change-of-foundation-class?)
        ;; The class definition maintains its "OK" status. 
        (clear-override-frame-notes-from-class-definitions user-class?)
        (let* ((new-class-inheritance-path
             (make-class-inheritance-path-for-user-defined-class
               user-class? new-direct-superiors?))
           (new-system-classes
             (loop for class in new-class-inheritance-path
               when (system-defined-class-p class)
                 collect class using frame-cons))
           (different-system-classes?
             (not (equal previous-system-classes new-system-classes)))
           (instances-to-reactivate nil))
          (reclaim-slot-value-list new-class-inheritance-path)
          (reclaim-frame-list previous-system-classes)
          (reclaim-frame-list new-system-classes)
          (when different-system-classes?
        (loop for instance being each class-instance of user-class?
              do
          (when (active-p instance)
            (gensym-push instance instances-to-reactivate)
            (suspend-activation instance))))
          (alter-inheritance-of-class-without-changing-foundation-class
        class-definition new-direct-superiors? nil nil)
          (when instances-to-reactivate
        (loop for instance in instances-to-reactivate
              do
          (resume-activation instance))
        (reclaim-gensym-list instances-to-reactivate)))
        (process-default-overrides user-class? nil))
       ;; Foundation class is changing.  Class is uninstantiated.
       ;; Define-user-class will change the definition status to "OK".
       ((not (complete-definition-p class-definition))
        nil)
       (t
        (when (eq definition-class 'message-definition)
          (remove-default-message-overrides class-definition))
        (when (or (frame-of-class-p class-definition 'object-definition)
              (frame-of-class-p class-definition 'class-definition))
          (remove-default-overrides-on-system-slots class-definition nil))
        (undefine-user-class class-definition nil nil)
        (setf (direct-superiors-of-defined-class class-definition)
          new-direct-superiors?)
        (define-user-class class-definition)
        (when this-definition-is-a-class-definition?
          (setf (user-overridable-system-slots class-definition)
            (make-list-of-aliased-overridable-system-slots-for-definition
              (class-inheritance-path-of-definition class-definition)))))))

    ;; The class is not defined.
    (t 
     (when previous-direct-superiors?
       (loop for superior in previous-direct-superiors?
         do
         (unless (memq superior new-direct-superiors?)
           (setf (potential-inferior-class-definitions superior)
             (delete-class-description-element
               class-definition
               (potential-inferior-class-definitions superior))))))
     (cond
       ((null new-direct-superiors?)
        (add-frame-note 'no-direct-superiors class-definition)
        (setf (direct-superiors-of-defined-class class-definition) nil)
        (update-frame-status class-definition 'incomplete nil))
       ((not direct-superiors-are-defined?)
        (loop for superior in new-direct-superiors?
          do
          (when (not (classp superior))
        (add-to-frame-note-particulars-list-if-necessary
          superior 'undefined-direct-superiors class-definition)))
        (setf (direct-superiors-of-defined-class class-definition)
          new-direct-superiors?)
        (update-frame-status class-definition 'incomplete nil))

       ;; The direct superiors are now complete.
       (t
        (setf (direct-superiors-of-defined-class class-definition)
          new-direct-superiors?)
        (setf (class-inheritance-path-of-definition class-definition)
          (make-class-inheritance-path-for-user-defined-class
            user-class? new-direct-superiors?))
        
        (when this-definition-is-a-class-definition?
          (setf (user-overridable-system-slots class-definition)
            (make-list-of-aliased-overridable-system-slots-for-definition
              (class-inheritance-path-of-definition class-definition))))
        ;; The definition will have an incomplete status if transient
        ;; or lacking a class name.
        (if (not (complete-definition-p class-definition))
        (update-frame-status class-definition 'incomplete nil)
        (define-user-class class-definition))))))

      (when (classp user-class?)
    (loop for subclass being each subclass of user-class?
          for class-definition = (class-definition subclass)
          when (and (direct-superiors-preclude-instantiability-p
              (direct-superiors-of-defined-class class-definition))
            (instantiate? class-definition))
        do (add-frame-note 'inconsistent-instantiate-value class-definition)))

      (update-representations-of-slot-value
    class-definition 'direct-superiors-of-defined-class)
      (update-representations-of-slot-value
    class-definition 'class-inheritance-path-of-definition)
      (update-representations-of-slot-value
    class-definition 'inherited-attributes)
      (update-representations-of-slot-value
    class-definition 'user-overridable-system-slots)

      ;; Important: new superior classes must be installed already for the
      ;; following update of indexed-attributes.
      (when class-change-requires-indexed-attribute-update?
    ;; Update indexed-attribute hash-tables when G2 is running or paused.
    ;; Because the superior classes are changing, this class and inferiors
    ;; classes may now have different inherited indexed-attributes.
    ;; Therefore, the hashed-tables for all new and old inherited
    ;; indexed-attributes must be cleared and updated.
    ;; Note that the indexed-attribute properties do not need updating
    ;; because the class or the class's non-inherited indexed-attributes
    ;; are not being redefined.
    (let ((current-indexed-attribute-info?
        ;; Collect the list of current indexed-attributes, now that
        ;; the new superior classes have been installed.  This is a
        ;; gensym-list that must be RECLAIMED.
        (and user-class?
             (collect-all-indexed-attributes-for-class user-class?))))
      (loop for (old-indexed-attribute . nil) in
        old-indexed-attribute-info-if-not-reset?
        do
        (clear-indexed-attribute-hash-table old-indexed-attribute)
        (update-indexed-attribute-hash-table old-indexed-attribute))
      (loop for (current-indexed-attribute . nil) in
        current-indexed-attribute-info?
        do
        ;; Only clear and update the hash-table, if it wasn't already done
        ;; in the list of old indexed-attributes.
        (when (not (assq current-indexed-attribute
                 old-indexed-attribute-info-if-not-reset?))
          (clear-indexed-attribute-hash-table current-indexed-attribute)
          (update-indexed-attribute-hash-table current-indexed-attribute)))
      (reclaim-gensym-tree current-indexed-attribute-info?))
    (when old-indexed-attribute-info-if-not-reset?
      (reclaim-gensym-tree old-indexed-attribute-info-if-not-reset?)))

      ;; Validate other parts of the KB affected by this change, if necessary.
      (when class-change-requires-kb-validation?
    (validate-kb-after-runtime-definition-change user-class? nil t))

      ;; Analyze the attributes defined in some old superiors, new superiors,
      ;; and subclasses.
      (when (not loading-kb-p)
    ;; Analyze the attributes of former superior classes.  The removal of
    ;; these superior classes can affect the vector location of class
    ;; attributes or can cause some attribute references to now be
    ;; undefined.
    (loop for previous-superior in previous-direct-superiors?
          when (and (not (memq previous-superior new-direct-superiors?)) 
            (not (system-defined-class-p previous-superior)))
        do
          ;; Note that this analyzes all attributes, including those
          ;; that are inherited. 
          (analyze-class-attributes-for-consistency
            previous-superior t))

    ;; Analyze the attributes of all superior classes.  The addition of
    ;; these superior classes can affect the vector location of class
    ;; attributes or can cause some attribute references to now be defined.
    ;; Note that all superiors, and not just new ones are analyzed.
    ;; Existing superiors need to be analyzed because their ordering in the
    ;; class-inheritance-path may have changed, which can affect attribute
    ;; locations.
    (loop for new-superior in new-direct-superiors?
          when (not (system-defined-class-p new-superior))
        do
          ;; Note that this analyzes all attributes, including those
          ;; that are inherited. 
          (analyze-class-attributes-for-consistency new-superior t))

    ;; changing the superiors can alter dependencies induced by stable
    ;; hierarchy declarations
    (loop for previous-superior in previous-direct-superiors?
          do
      (handle-stable-hierarchy-or-inline-status-change-for-item previous-superior))
    (loop for new-superior in new-direct-superiors?
          do
      (unless (memq new-superior previous-direct-superiors?)
        (handle-stable-hierarchy-or-inline-status-change-for-item new-superior)))
    
    (when (and user-class? (classp user-class?) (not loading-kb-p))
      ;; The change to the superior classes may have affected attribute
      ;; vector locations of this class and inferior classes.  Therefore,
      ;; analyze for consistency all attributes (not inherited) of this
      ;; class and subclasses.  This analysis is needed by the
      ;; cached-attribute free-reference, which inlines the attribute vector
      ;; index, when possible.  Refer to check-for-cached-attribute.

      ;; Note that this analysis needs to be done after the superior classes
      ;; have been installed.  Analyze inherited-attributes also.
      (analyze-attributes-of-subclasses-for-consistency user-class? t)))

      (when (classp user-class?)
    ;; A change to the superiors of this class may change the stability or
    ;; dependent status of instances.
    (loop for item being every class-instance of user-class? doing
      (handle-dependent-or-stable-status-change-for-item item))
    ;; Items dependent on this class or inferior classes need to be analyzed
    ;; because the class hierarchy (i.e., the superior of the class) has
    ;; changed.  This analysis may need to be done, even if this class (the
    ;; definition of this slot-putter) is not stable.
    (loop for subclass being each subclass of user-class?
          when (stable-class-p subclass)
        do
          (analyze-compiled-items-for-consistency subclass)))

      (unless current-computation-frame-previously-bound?
    (setq *current-computation-frame* nil))
      
      (values new-direct-superiors? nil))))




;;; The function `make-list-of-aliased-overridable-system-slots-for-definition'
;;; returns the slot-value-listed value of the user-overridable-system-slots
;;; slot on class definitions.  It uses the system variable,
;;; user-overridable-system-slots which is in this form:

;;; (class-name overridable-slots-aliased masked-slots-aliased
;;;             overridable-slots-unaliased masked-slots-unaliased).

;;; Masked slots are those not inherited from a superior class.

(defun-simple make-list-of-aliased-overridable-system-slots-for-definition
    (class-inheritance-path)
  (let ((list-to-return nil))
    (loop with slots-to-mask? =
      (loop for class in class-inheritance-path
        for masked-slots? =
        (and (system-defined-class-p class)
             (third
               (car (member class list-of-user-overridable-system-slots
                    :test 'car-eq))))
        nconc masked-slots?)
      for class in class-inheritance-path
      for overridable-slots-for-class? =
      (second
        (car (member
           class list-of-user-overridable-system-slots :test 'car-eq)))
      do
      (when overridable-slots-for-class?
    (loop for slot-name in overridable-slots-for-class?
          do
      ;; Icon-description is not handled by default-overrides.
      (unless (memq slot-name slots-to-mask?)
        (setq list-to-return
          (nconc list-to-return (slot-value-list slot-name)))))))
    list-to-return))





;;; Note on `directory-of-names' for attribute names.  The names of attributes
;;; come from the class-specific-attributes slot of definitions.  A name
;;; is added to or deleted from the directory every time it is added to or
;;; deleted from, respectively, that slot of any definition.  The effect of
;;; this is to make names available even if they are part of incomplete
;;; definitions that are not yet classes. This is much simpler than trying to
;;; maintain the directory of names from class-descriptions whose modification
;;; is much more complicated.




;;; `List-abbreviation-changes-for-added-or-deleted-attribute', when given a
;;; newly added attribute name, returns a list of triples that refer to slot
;;; description references that currently appear without a defining-class
;;; component but now need a defining class component because their status is
;;; changing from default to non-default.  When given a newly deleted attribute
;;; name, this function returns a list of triples that refer to slot description
;;; references that currently appear with a defining-class component but now do
;;; not need a defining-class component because their status is changing from
;;; non-default to default.

;;; Each triple is in the form: (<class-name> <pretty-slot-name> <defining-class>).

;;; This function is currently called from the slot putter code for class-specific-
;;; attributes and the slot putter code for change when the change is a change in
;;; attribute name.  A change in attribute name is handled as a attribute deletion
;;; followed by an attribute addition.  In the case of additions, it is important
;;; to call this function before the new slot description is added to the class,
;;; and, in the case of deletions, to call it after the slot description is
;;; deleted from the class.

;(defun list-abbreviation-changes-for-added-or-deleted-attribute
;    (user-class new-or-deleted-attribute-name)
;  (let ((user-class-class-description (class-description user-class))
;        (abbreviation-change-list? nil))
;    (loop for class being each subclass of user-class
;          for class-description = (class-description class)
;          for class-slot-description? =
;                (get-slot-description-of-class-description
;                  new-or-deleted-attribute-name class-description)
;          do
;      (when class-slot-description?
;        (let ((defining-class (defining-class class-slot-description?)))
;          (when (class-description-of-class-p
;                  user-class-class-description defining-class)
;            (setq abbreviation-change-list?
;                  (frame-cons
;                    (frame-list
;                      class new-or-deleted-attribute-name defining-class)
;                    abbreviation-change-list?))))
;        abbreviation-change-list?))))




;;; `Attribute-changes-amount-to-renaming' compares the attribute-list
;;; of a definition before and after an editorial change. If (1) the new
;;; list is identical to old list except that certain attribute names have changed,
;;; and if (2) the new names are distinct from any names previously in the list,
;;; then the value is a frame-list of frame-conses of dotted pairs of old and
;;; new names. This is used (and reclaimed by the caller) to implement the change
;;; as a sequence of renames, a la rename-attribute (in the change slot).

;;; If the value is NIL, then either there are no changes to be made or the
;;; changes do not conform to the above.


(defun attribute-changes-amount-to-renaming (old-value new-value)
  (if (=f (length old-value) (length new-value))
      (loop with result = nil
        for old-attribute-description in old-value
        for old-attribute-name = (attribute-name old-attribute-description)
        for new-attribute-description in new-value
        for new-attribute-name = (attribute-name new-attribute-description)
        do
    (cond
      ((slot-value-equal-p old-attribute-description new-attribute-description))
      
      ((and (slot-value-equal-p (cdr old-attribute-description)
                    (cdr new-attribute-description))
        (not (member new-attribute-name old-value :test 'car-eq)))
       (setq result (frame-cons
              (frame-cons old-attribute-name new-attribute-name)
              result)))
      (t (reclaim-frame-tree result)
         (return-from attribute-changes-amount-to-renaming nil)))
        finally
          (return result))
      nil))




;;; The function `resequence-slot-descriptions-if-necessary' changes the
;;; order of the slot descriptions defined for user-class for all
;;; subclasses of user-class when the class-specific-attributes slot has
;;; been edited in such a way that the attribute ordering is different
;;; from the previous attribute-description ordering.  This function
;;; returns t when reordering has been done, and returns nil when no
;;; reordering was necessary.

(defun-simple resequence-slot-descriptions-if-necessary
    (user-class user-class-attribute-descriptions)
  (let* ((sublist-holding-user-class-slot-descriptions
       (loop for sublist on (slot-descriptions
                  (class-description user-class))
         when (eq (defining-class (car sublist))
              user-class)
           return sublist))
     (attributes-have-been-resequenced?
       (loop for attribute in user-class-attribute-descriptions
         for slot-description in
         sublist-holding-user-class-slot-descriptions
         thereis (not (eq (attribute-name attribute)
                  (pretty-slot-name slot-description))))))
    (if attributes-have-been-resequenced?
    (loop for class being each subclass of user-class
          for class-description = (class-description class)
          for slot-descriptions = (slot-descriptions class-description)
          do
      (decache-cached-class-data class)
      (loop for attribute-description in user-class-attribute-descriptions
        for attribute-name = (attribute-name attribute-description)
        for corresponding-slot-description =
        (get-slot-description
          attribute-name (slot-descriptions class-description)
          user-class)
        do
        (delete-class-description-element-from-slot-descriptions
          corresponding-slot-description class-description)
        (let* ((preceding-slot-description 
             (preceding-slot-description-for-positioning-slot-addition
               class user-class attribute-name))
           (slot-descriptions-cons-after-which-to-insert
             (get-appropriate-slot-descriptions-cons
               (unique-slot-name preceding-slot-description)
               slot-descriptions)))
          (setf (cdr slot-descriptions-cons-after-which-to-insert)
            (class-description-cons
              corresponding-slot-description
              (cdr slot-descriptions-cons-after-which-to-insert)))))
          finally (return t))
    nil)))

    
              
    
    




;;; The `slot-putter for class-specific-attributes' ...

;;; Modified the slot-putter to do consistency analysis on the subclasses of the
;;; given class, when an attribute is being added or deleted to the class.  The
;;; attribute locations in subclasses may be affected by the attribute change in
;;; the class.  This analysis is needed to maintain the cached-attribute
;;; free-reference, which can contain the attribute vector index.

;; - cpm, 9/23/93

(def-slot-putter class-specific-attributes (definition new-value)
  ;; Deferral of analysis is needed particularly by the cached-attribute
  ;; free-reference.  It is done for efficiency reasons and, also, so that
  ;; changes to definitions are completed before the analysis is done.  See
  ;; analyze-attributes-of-subclasses-for-consistency.
  (defer-some-consistency-analysis
    (let* ((user-class (name-of-defined-class definition))
       (old-value? (class-specific-attributes definition))
       old-new-value
       (old-indexed-attributes
         (old-value-of-indexed-attributes definition))
       (list-of-attribute-name-changes-only?
         (when (classp user-class)
           (attribute-changes-amount-to-renaming old-value? new-value)))
       (deleted-slots? nil)
       (list-of-names-of-added-slots? nil)
       (resequenced-attribute-descriptions? nil)
       (analyze-attributes-of-subclasses? nil)
       (any-class-instances? nil)
       ;; Validation may be required when there is an attribute change or
       ;; deletion, such that an attribute frame may have been deleted or
       ;; is now defined to be of another class.
       (attribute-change-requires-kb-validation? nil)
       ;; Need to change attribute descriptions of the form (<name>
       ;; <type-specification> nil nil) to (<name> <type-specification>)
       ;; and (<name> <type-specification> <:funcall instantiate <class>>
       ;; nil) to (<name> <type-specification> <:funcall instantiate <class>>
       ;; <class>)
       (descriptions-need-adjustment-for-4.0?
         (loop for description in new-value
           for attribute-initial-value = (attribute-initial-value description)
           for attribute-initial-type = (attribute-initial-type description)
           thereis (or (null (cdr description))
                   (and (null attribute-initial-type)
                    (=f (length description) 4))
                   (and (consp attribute-initial-value)
                    (eq (car attribute-initial-value)
                    ':funcall)
                    (not (eq attribute-initial-type
                         (third attribute-initial-value))))))))

      
      (when descriptions-need-adjustment-for-4.0?
    (setq old-new-value new-value)
    (setq new-value
          (adjust-class-specific-attributes-for-4.0 new-value))
    (reclaim-slot-value-list old-new-value))

      (when (classp user-class)
    (clear-override-frame-notes-from-class-definitions user-class))

      (unless list-of-attribute-name-changes-only?
    (without-consistency-analysis (definition) 
      (setf (class-specific-attributes definition) new-value)))
      
      (when (classp user-class)
    ;; Test for instances before any definition changes are made.
    (loop for thing being each class-instance of user-class
          do (setq any-class-instances? t)
          until any-class-instances?)
    (cond
      (old-value?
       (cond
         (list-of-attribute-name-changes-only?
          (make-attribute-name-changes-for-class-specific-attributes
        definition list-of-attribute-name-changes-only?)
          (return-from put-class-specific-attributes
        (values (class-specific-attributes definition) t)))
         (t
          ;; Delete attributes that are only in the old definition.
          (loop for attribute-description in old-value?
            for attribute-name = (attribute-name attribute-description) 
            for new-attribute-description?
            = (get-attribute-description attribute-name new-value)
            do
        (unless new-attribute-description?
          (setq deleted-slots? t)
          ;; The deleted attribute may cause a frame to be removed.
          ;; Note that this change requires validation even if the
          ;; slot description specifies it to be of a type more
          ;; general than item, for example, item-or-value.  In that
          ;; case, the attribute could have been deleted manually and
          ;; replaced by an object.  So, if deleting a slot, always
          ;; validate.
          (when any-class-instances?
            (setq attribute-change-requires-kb-validation? t))
          (delete-attribute-from-definition
            definition attribute-name attribute-description)
          (remove-class-qualifier-from-parent-attribute-names-if-necessary
            user-class attribute-name)
          (setq analyze-attributes-of-subclasses? t)))

          (loop for attribute-description in new-value
            for attribute-name = (attribute-name attribute-description)
            for old-attribute-description?
            = (get-attribute-description attribute-name old-value?) 
            do
        (cond
          ;; Add attributes that are only in the new definition.
          ((null old-attribute-description?)
           (setq list-of-names-of-added-slots?
             (frame-cons attribute-name list-of-names-of-added-slots?))
           (add-class-qualifier-to-parent-attribute-names-if-necessary
             user-class attribute-name)
           (add-attribute-to-definition definition attribute-description)
           (setq analyze-attributes-of-subclasses? t))

          ;; Change attributes that are in both definitions and not
          ;; equal.
          ((not (slot-value-equal-p
              attribute-description old-attribute-description?))
           ;; The changed attribute may cause a frame to be removed or
           ;; to be of another class.  Note that this change requires
           ;; validation even if the old slot description specifies it
           ;; to be of a type more general than item, for example,
           ;; item-or-value.  In that case, the attribute could have
           ;; been deleted manually and replaced by an object.  So, if
           ;; changing a slot, always validate.
           (when any-class-instances?
             (setq attribute-change-requires-kb-validation? t))

           ;; Note that analyze-attributes-of-subclasses? is not set
           ;; to T.  The attribute already exists, and so its
           ;; attribute location is not changing and does not need
           ;; analysis.
           (change-attribute-in-definition
             definition attribute-description
             old-attribute-description?))))

          (setq resequenced-attribute-descriptions?
            (and new-value
             (resequence-slot-descriptions-if-necessary
               user-class new-value)))
          (when resequenced-attribute-descriptions?
        (setq analyze-attributes-of-subclasses? t)))))

      ;; There are no previous attributes for this class.
      (t
       (loop for attribute-description in new-value
         as attribute-name = (attribute-name attribute-description)
         as attribute-range = (attribute-range attribute-description)
         do
         (setq list-of-names-of-added-slots?
           (frame-cons attribute-name list-of-names-of-added-slots?))
         (add-class-qualifier-to-parent-attribute-names-if-necessary
           user-class attribute-name)
         (add-attribute-to-definition definition attribute-description)
         (setq analyze-attributes-of-subclasses? t))))

    (when (or deleted-slots? list-of-names-of-added-slots?
          resequenced-attribute-descriptions?)
      (adjust-slot-description-indices-and-instances-for-attribute-changes
        user-class list-of-names-of-added-slots?)
      (reclaim-frame-list list-of-names-of-added-slots?))

    (update-inherited-attributes-slot-of-tree user-class))

      (when (classp user-class)
    (process-default-overrides user-class t))

      ;; Delete old attributes not in new attributes from directory of names.
      ;; Done for defined and undefined classes.
      (loop for (name . nil) in old-value? doing
    (unless (member name new-value :test 'car-eq)
      (if (reserved-system-slot-name-p definition name)
          (delete-from-frame-note-particulars-list
        name 'class-specific-attribute-is-a-system-slot-name definition)
          (delete-from-directory-of-names name 'attribute-name))))

      ;; Add new attribute names that are not in old attribute names.
      ;; Done for defined and undefined-classes.
      (loop for (name . nil) in new-value doing
    (unless (member name old-value? :test 'car-eq)
      (if (reserved-system-slot-name-p definition name)
          (progn 
        (add-to-frame-note-particulars-list-if-necessary
          name 'class-specific-attribute-is-a-system-slot-name definition)
        (when loading-kb-p 
          (notify-user 
            "~A is the name of a G2 system attribute and cannot be ~
                     a user-defined attribute."
            name)))
          (add-to-directory-of-names name 'attribute-name))))

      ;; Redisplay the inherited attributes for tables of definitions of all
      ;; subclasses.  Update indexed-attribute information, as necessary.
      ;; Possibly, analyze attributes subclasses for consistency.
      (when (classp user-class)
    (when (not loading-kb-p)
      (when analyze-attributes-of-subclasses?
        ;; This is a user class that has a new or deleted attribute or
        ;; resequenced attributes and the KB is not currently being
        ;; loaded.  Analyze for consistency all attributes of all
        ;; subclasses, in case any subclass attribute locations are
        ;; affected by the attribute change for this class.  This
        ;; analysis is needed by the cached-attribute free-reference,
        ;; which inlines the attribute vector index, when possible.
        ;; Refer to check-for-cached-attribute. - cpm, 9/16/93 Note that
        ;; this analysis needs to be done after the attribute locations
        ;; of the class and subclasses have been updated (i.e.,
        ;; re-ordered).  Analyze inherited-attributes also.
        (analyze-attributes-of-subclasses-for-consistency user-class t))

      ;; The indexed-attributes-for-definition is set by the slot-value
      ;; compiler for attribute-descriptions
      (if (or (indexed-attributes-for-definition definition)
          (loop for direct-superior in (direct-superiors-of-defined-class
                         definition)
            thereis (get-class-feature-if-any
                  direct-superior 'has-indexed-attributes)))
          (add-indexed-feature-to-class-and-subclasses user-class)
          (remove-indexed-feature-from-class-and-subclasses-if-appropriate
        user-class))

      ;; new. (MHD/GHW 11/18/93)
      (update-attribute-tables-for-instances user-class nil))
    (update-inherited-attributes-slot-of-tree user-class))

      ;; Update the indexed-attribute properties.
      (let ((indexed-attributes
          (indexed-attributes-for-definition definition)))
    (when (or old-indexed-attributes indexed-attributes)
      (update-indexed-attribute-properties
        definition t old-indexed-attributes nil))
    (reclaim-slot-value old-indexed-attributes)
    (setf (old-value-of-indexed-attributes definition) nil))

      ;; This slot-putter may have deleted or changed the class of a frame
      ;; contained in an attribute.  When this is the case, validate parts of
      ;; this KB that may be affected by this.

      ;; Note that changing the class of an attribute frame init form does not
      ;; affect the class hierarchy of an existing attribute object.  First
      ;; the old attribute object is removed and then a new one is added.
      ;; Therefore, the validation function is passed a NIL argument,
      ;; indicating that the class hiearchy of existing items are unchanged.
      (when attribute-change-requires-kb-validation?
    (validate-kb-after-runtime-definition-change user-class nil nil))
      )))

;; The above validation of KB runtime-definition changes could be made more
;; efficient by not calling the validation function when we can be certain that
;; no instance has an attribute object that removed (or whose class has
;; changed).  We cannot always be sure, even based on the attribute slot init
;; form of the class, because the user could have manually added or deleted the
;; object conatined in the attribute.  Perhaps, we could check the type spec, if
;; any, of the attribute init form and make certain it is only the type or
;; subtype of "value".  - cpm, 7/22/94

(defun adjust-class-specific-attributes-for-4.0 (new-value)
  (loop for description in new-value
    for attribute-initial-value = (attribute-initial-value description)
    for attribute-initial-type = (attribute-initial-type description)
    for new-description = nil
    collect
    (cond ((null (cdr description))
           (setf (cdr description)
             (slot-value-list
               (slot-value-list
             'or 'item-or-datum (slot-value-list 'no-item))))
           description)
          ((and (null attribute-initial-type)
            (=f (length description) 4))
           (cond ((null attribute-initial-value)
              (setq
            new-description
            (slot-value-list
              (copy-for-slot-value (attribute-name  description))
              (copy-for-slot-value (attribute-type-specification description))))
              (reclaim-slot-value description)
              new-description)
             (t
              (if (and (consp attribute-initial-value)
                   (eq (car attribute-initial-value)
                   ':funcall))
              (progn
                (setq new-description
                  (slot-value-list
                    (copy-for-slot-value
                      (attribute-name description))
                    (copy-for-slot-value
                      (attribute-type-specification description))
                    (copy-for-slot-value attribute-initial-value)
                    (copy-for-slot-value
                      (third attribute-initial-value))))
                (reclaim-slot-value description)
                new-description)
              description))))
          ((and (consp attribute-initial-value)
            (eq (car attribute-initial-value)
            ':funcall)
            (not (eq attribute-initial-type
                 (third attribute-initial-value))))
           (reclaim-slot-value (attribute-initial-type description))
           (setf (attribute-initial-type description)
             (third attribute-initial-value))
           description)
          (t description))
      using slot-value-cons))

;; Note: the name of above function should NOT be taken to imply it's only
;; needed for KBs saved in 4.0.  This needs to run all modern versions of G2,
;; and with KBs saved in all modern versions, e.g., today's 8.0 and beyond. This
;; performs some important transformations; this needs doc -- there's some at
;; the call site; also, consider giving this a better and less historic name!
;; (MHD 6/17/04)


(defun make-attribute-name-changes-for-class-specific-attributes
    (definition list-of-attribute-name-changes-only?)
  (loop for (old-name . new-name)
        in list-of-attribute-name-changes-only?
    do
    (put-change
      definition
      (slot-value-list 'rename-attribute old-name new-name) nil))
  (reclaim-frame-tree list-of-attribute-name-changes-only?))


;;; `Adjust-slot-description-indices-and-instances-for-attribute-changes' is
;;; called from the slot-putter code for class-specific-attributes.  After the
;;; user-class and subclass slot-descriptions have been changed for all the
;;; slot-description deletions and additions caused by an edit of the
;;; attribute-descriptions-for-class slot, this function adjusts all the
;;; instance lookup-structures to reflect the changes as well as renumbering
;;; the user-vector-slot-index? components for the slot-descriptions.

(defun adjust-slot-description-indices-and-instances-for-attribute-changes 
       (user-class list-of-names-of-new-slots)
  ;; level 1
  (loop with do-not-note-permanent-changes-p = t
	for class being each subclass of user-class
	for class-description = (class-description class)
	for old-class-user-vector-length =
	  (class-user-vector-length class-description)
	for slot-descriptions =
          (slot-descriptions class-description)
	for number-of-user-vector-slots =
	  (loop for slot-description in slot-descriptions
		count (user-defined-slot-description-p slot-description))
	do
    (setf (class-user-vector-length class-description) 
      number-of-user-vector-slots)
    ;; level 2
    (loop for instance being each strict-class-instance of class
	  for old-lookup-structure = (lookup-structure instance)
	  for lookup-portion =
            (if old-lookup-structure
		(-f (length-of-simple-vector old-lookup-structure)
		    old-class-user-vector-length)
	      0)
	  for new-lookup-structure =
            (if (or (>f number-of-user-vector-slots 0)
		    (>f lookup-portion 0))
		(allocate-frame-lookup-structure-vector
		  (+f number-of-user-vector-slots lookup-portion) nil)
	      nil)
	  for current-index = 0
	  do
      ;; Transfer the old user-vector-slot values into the new lookup structure.
      (when (>f number-of-user-vector-slots 0)
	(loop for slot-description in slot-descriptions
	      do
	  (when (user-defined-slot-description-p slot-description)
	    ;; The list-of-names-of-new-slots consists of pretty slot names.
	    (unless (and (eq (defining-class slot-description) user-class)
			 (memq (pretty-slot-name slot-description)
			       list-of-names-of-new-slots))
	      (setf (svref new-lookup-structure current-index)
		    (svref old-lookup-structure
			   (user-vector-slot-index? slot-description))))
	    (incff current-index))))

      ;; Transfer the lookup-slot values from the old lookup-structure
      ;; to the new lookup-structure.
      (when (and old-lookup-structure new-lookup-structure
		 (>f lookup-portion 0))
	(loop for old-index from old-class-user-vector-length
	        below (length-of-simple-vector old-lookup-structure)
	      for new-index from number-of-user-vector-slots
                below (length-of-simple-vector new-lookup-structure)
	      do
	  (setf (svref new-lookup-structure new-index)
		(svref old-lookup-structure old-index))))

      (setf (lookup-structure instance) new-lookup-structure)
      (when old-lookup-structure
	(reclaim-frame-lookup-structure-vector old-lookup-structure)))) ; level 1 ends

  ;; Now that the old slot-values are in the new lookup-structures, the
  ;; user-vector-slot-indices can be renumbered for all subclasses, and
  ;; the new slot values can be initialized.
  (loop with slot-descriptions-to-reclaim? = nil
	for class being each subclass of user-class
	for class-description = (class-description class)
	for class-slot-descriptions = (slot-descriptions class-description)
	for strict-instances-of-class
            = (loop for instance being each strict-class-instance of class
		    collect instance using frame-cons)
	for current-index = 0
	do
    (loop for class-slot-description in class-slot-descriptions
          when (user-defined-slot-description-p class-slot-description)
	  do
      (let* ((unique-slot-name (unique-slot-name class-slot-description))
	     (slot-description-is-shared-but-different-index?
	      (or (member class-slot-description
			  slot-descriptions-to-reclaim? :test 'cdr-eq)
		  (loop for subclass being each subclass of
			  (owner-class class-slot-description)
			for subclass-slot-description? =
			  (and (neq subclass class)
			       (get-slot-description unique-slot-name
						     (slot-descriptions
						       (class-description subclass))))
			thereis
			  (and subclass-slot-description?
			       (eq class-slot-description
				   subclass-slot-description?)
			       (let ((subclass-slot-description-index
				      (user-vector-slot-index?
				        subclass-slot-description?)))
				 (and (neq subclass-slot-description-index t)
				      (/= subclass-slot-description-index
					  current-index)))))))
	     (new-slot-description?
	      (when slot-description-is-shared-but-different-index?
		(make-slot-description
		  (pretty-slot-name class-slot-description)
		  (defining-class class-slot-description)
		  class
		  (slot-type-specification class-slot-description)
		  (slot-init-form class-slot-description) nil current-index
		  (slot-features class-slot-description)))))
	(cond (new-slot-description?
	       (setf (car (get-appropriate-slot-descriptions-cons
			    unique-slot-name class-slot-descriptions))
		     new-slot-description?)
	       (delete-slot-description-from-hash-table
		 class-slot-description class-description)
	       (add-slot-description-to-hash-table
		 new-slot-description? class-description)
	       ;; Set attribute values that were EQ to the old slot-
	       ;; description slot-init form to now be EQ to the
	       ;; new slot-description slot-init form.
	       (loop for instance in strict-instances-of-class
		     for old-slot-init-form = (slot-init-form
					        class-slot-description)
		     for new-slot-init-form = (slot-init-form
					        new-slot-description?)
		     for lookup-structure = (lookup-structure instance)
		     for slot-value = (svref lookup-structure current-index)
		     do
		 (when (eq slot-value old-slot-init-form)
		   (setf (svref lookup-structure current-index)
			 new-slot-init-form)))
	       (when (eq (owner-class class-slot-description) class)
		 (setq slot-descriptions-to-reclaim?
		       (nconc slot-descriptions-to-reclaim?
			      (frame-list
			        (frame-cons class class-slot-description))))))
	      (t
	       (setf (user-vector-slot-index? class-slot-description)
		     current-index)))
	(incff current-index))) ; level 2 loop ends

    ;; Now that all of the slot-descriptions have been brought up to date,
    ;; we can initialize the new slots.  We could not do this in the first
    ;; loop because there may be nested self-instantiation.
    (loop for class-slot-description in class-slot-descriptions
	  do
      (when (and (user-defined-slot-description-p class-slot-description)
		 (memq (pretty-slot-name class-slot-description)
		       list-of-names-of-new-slots)
		 (eq (defining-class class-slot-description) user-class))
	(let ((slot-init-form
	       (slot-init-form class-slot-description))
	      (unique-slot-name
	       (unique-slot-name class-slot-description)))
	  (loop for instance in strict-instances-of-class
		do
	    (initialize-slot-value
	      instance unique-slot-name
	      (eval-slot-init-form slot-init-form)
	      user-class)))))
    (reclaim-frame-list strict-instances-of-class)

    finally
      (when slot-descriptions-to-reclaim?
	(reclaim-list-of-slot-descriptions slot-descriptions-to-reclaim?)
	(reclaim-frame-tree slot-descriptions-to-reclaim?))))

(defun add-indexed-feature-to-class-and-subclasses (user-class)
  (loop for class being each subclass of user-class
    do
    (add-class-feature
      class (class-description-list 'has-indexed-attributes))
    (loop for instance being each strict-class-instance of class doing
      (set-has-indexed-attributes instance))))

(defun remove-indexed-feature-from-class-and-subclasses-if-appropriate
    (user-class)
  (loop for class being each subclass of user-class
    do
    (cond ((eq class user-class)
       (remove-class-feature user-class 'has-indexed-attributes)
       (loop for instance being each strict-class-instance of class
         do
         (clear-has-indexed-attributes instance)))
      (t
       (let ((class-definition (class-definition class)))
         (unless (or (indexed-attributes-for-definition
               (class-definition class))
             (loop for superior in (direct-superiors-of-defined-class
                         class-definition)
                   thereis (get-class-feature-if-any
                     superior 'has-indexed-attributes)))
           (remove-class-feature user-class 'has-indexed-attributes)
           (loop for instance being each strict-class-instance of class
             do
         (clear-has-indexed-attributes instance))))))))
    





(defun update-inherited-attributes-slot-of-tree (root)
  (when (and root (classp root))
    (loop for subclass being each subclass of root
      for subclass-definition = (class-definition subclass) doing
      (if (framep subclass-definition)
      (update-representations-of-slot-value
        (class-definition subclass) 'inherited-attributes)))))




;;; The following four functions are called by the slot putter for
;;; class-specific-attributes.  The definition must be for a
;;; defined class at the time of the call.  At the time of the call, the
;;; new slot-value has already been placed into the definition.  The old
;;; value has been retained locally, but is not accessible to the called
;;; functions.  The functions modify class-descriptions, and are
;;; executed for their effects.

;;; In the following commentary "old value" refers to the previous
;;; contents of class-specific-attributes.  "New value" refers to
;;; the new contents which are the argument of the above slot-putter.

;;; add-attribute-to-definition adds the described attribute to the
;;; class.  The attribute is one that is not in the old value, and is in
;;; the new value.  The attribute may also be defined in some superior
;;; or inferior class.

(defun add-attribute-to-definition (definition attribute-description)
  (let* ((user-class (name-of-defined-class definition))
     (attribute-name (attribute-name attribute-description))
     (attribute-range (attribute-range attribute-description)))
    (update-representations-of-slot-value
      definition 'class-specific-attributes)
    (declare-implied-attribute user-class attribute-name attribute-range nil)
    (add-user-defined-slot-to-user-class definition attribute-description)
    (let ((unique-slot-name
        (unique-slot-name
          (slot-description-from-class user-class attribute-name))))
      (declare-implied-attribute user-class unique-slot-name attribute-range t))))




;;; `Delete-attribute-from-definition' is called when a user deletes attribute
;;; name from the class-specific-attributes slot.

(defun delete-attribute-from-definition 
       (definition attribute-name old-attribute-description)
  (let* ((user-class (name-of-defined-class definition)))
    
    (let* ((attribute-range (attribute-range old-attribute-description))
       (corresponding-slot-description
         (slot-description-from-class
           user-class attribute-name user-class)))
      (delete-from-directory-of-names attribute-name 'attribute-name)

      (update-representations-of-slot-value
    definition
    'class-specific-attributes)
      
      (delete-user-defined-slot user-class attribute-name)
      
      ;; Note that the attribute has been removed from the directory of names
      ;; and the attribute has been removed from the class definition before
      ;; calling the following function which does consistency analysis.  - cpm,
      ;; jra 6/26/92
      (undeclare-implied-attribute user-class attribute-name attribute-range nil)
      (undeclare-implied-attribute
    user-class (unique-slot-name corresponding-slot-description)
    attribute-range t))))




;;; `Change-attribute-in-definition' is called when a user changes a component
;;; of an existing attribute description and that change does not alter the
;;; attribute name.

(defun change-attribute-in-definition
    (definition attribute-description old-attribute-description)
  (let* ((user-class (name-of-defined-class definition))
     (attribute-name (attribute-name attribute-description))
     (attribute-type-specification
       (attribute-type-specification attribute-description))
     (old-attribute-type-specification
       (attribute-type-specification old-attribute-description))
     (changed-attribute-type-specification?
       (not (equal attribute-type-specification
               old-attribute-type-specification)))
     (changed-attribute-type-modifications?
       (not (equal (attribute-type-modifications attribute-description)
               (attribute-type-modifications old-attribute-description))))
     (value-or-init-form (attribute-initial-value attribute-description))
     (old-initial-value (attribute-initial-value old-attribute-description))
     (changed-initial-value?
       (not (slot-value-equal-p value-or-init-form old-initial-value)))
     (attribute-initial-type (attribute-initial-type attribute-description))
     (old-initial-type (attribute-initial-type old-attribute-description))
     (changed-initial-type?
       (not (equal attribute-initial-type old-initial-type)))
     (slot-description-changes?
       (or changed-attribute-type-specification?
           changed-attribute-type-modifications?
           changed-initial-value?
           changed-initial-type?))
     (new-attribute-range? (attribute-range attribute-description))
     (old-attribute-range? (attribute-range old-attribute-description))
     (change-in-attribute-range-only?
       (and (or new-attribute-range? old-attribute-range?)
        (not (equal new-attribute-range? old-attribute-range?))
        (not slot-description-changes?)))
     (new-init-form nil))

    (when (not (equal old-attribute-range? new-attribute-range?))
      (let* ((corresponding-slot-description
           (slot-description-from-class
         user-class attribute-name user-class))
         (unique-slot-name (unique-slot-name corresponding-slot-description)))
      ;; First examine old attribute-description, and delete any declarations
      ;; of implied attribute.
      (undeclare-implied-attribute
    user-class attribute-name old-attribute-range? nil)
      (undeclare-implied-attribute
    user-class unique-slot-name old-attribute-range? t)
      ;; Then add new implied attribute declaration if any.
      (declare-implied-attribute
    user-class attribute-name new-attribute-range? nil)
      (declare-implied-attribute
    user-class unique-slot-name new-attribute-range? t)))

    (unless change-in-attribute-range-only?
    ;; The new init form is either a slot-constant or the given init value.
      (setq new-init-form
        ;; This slot-init-form is going to be copied by update-slot-description
        ;; therefore, any further copying here only increases the lossage.
        ;; The correct thing to do would be to reclaim the argument which
        ;; requires understanding which pieces are shared. ML 3/19/91!!!
        ;; Currently (3/1/94 ghw), new slot descriptions are made and old ones
        ;; are recycled.
        (if (and attribute-initial-type
             (slot-constant-type-p attribute-initial-type))
        (make-slot-constant value-or-init-form attribute-initial-type t)
        value-or-init-form)))

    (when slot-description-changes?
      (let ((user-class-slot-description
          (get-slot-description
        attribute-name
        (slot-descriptions (class-description user-class))))
        (new-slot-features?
          (when (or changed-attribute-type-specification?
            changed-attribute-type-modifications?)
        (make-slot-features-for-user-defined-slot attribute-description))))
    (update-slot-description
      user-class user-class-slot-description
      attribute-type-specification new-init-form
      (if new-slot-features?
          new-slot-features?
          (slot-features user-class-slot-description))
      nil t)
    (when new-slot-features? (reclaim-frame-tree new-slot-features?))))))




;;; `Set-superior-inferior-data-for-inheritance-change' changes the direct-
;;; superior-classes and inferior-classes properties for a class changing
;;; direct-superior classes.

(defun set-superior-inferior-data-for-inheritance-change
    (user-class definition new-direct-superiors previous-direct-superiors)

  (setf (direct-superior-classes user-class)
    (copy-list-using-class-description-conses-function
      new-direct-superiors))
  (setf (direct-superiors-of-defined-class definition)
    new-direct-superiors)

  (loop for previous-superior in previous-direct-superiors
    do
    (unless (memq previous-superior new-direct-superiors)
      (setf (inferior-classes previous-superior)
        (delete-class-description-element 
          user-class (inferior-classes previous-superior)))))

  (loop for superior in new-direct-superiors
    do
    (unless (memq user-class (inferior-classes superior))
      (copy-kb-specific-property-from-global-if-necessary
    superior 'inferior-classes)
      (setf (inferior-classes superior)
        (nconc (inferior-classes superior)
           (class-description-list user-class))))))




;;; `Change-system-slot-values-for-inheritance-change' changes values of system
;;; slots when a change of inheritance has given them different values.

(defun change-system-slot-values-for-inheritance-change
    (class all-slot-descriptions-for-class old-slot-descriptions)
  (loop for instance being each strict-class-instance of class
    do
    (loop for new-slot-description in all-slot-descriptions-for-class
      do
      (when (and (system-defined-slot-description-p new-slot-description)
         (not (feature-assq
            'do-not-put-in-attribute-tables
            (slot-features new-slot-description))))
    (let* ((old-slot-description?
         (get-slot-description
           (unique-slot-name new-slot-description)
           old-slot-descriptions))
           (existing-slot-value?
         (when old-slot-description?
           (get-slot-description-value-macro
             instance old-slot-description?)))
           (previous-slot-init-form?
         (when old-slot-description?
           (slot-init-form
             old-slot-description?)))
           (present-slot-init-form
         (slot-init-form new-slot-description)))
      (when (and old-slot-description?
             (and (not (eq previous-slot-init-form?
                   present-slot-init-form))
              (or (eq existing-slot-value? previous-slot-init-form?)
                  (and (consp previous-slot-init-form?)
                   (eq (car-of-cons previous-slot-init-form?) :funcall))
                  (slot-init-form-needs-evaluation? present-slot-init-form))))
        (if (slot-init-form-needs-evaluation? present-slot-init-form)
        (let ((new-value
            (let ((frame-being-made instance))
              (eval-slot-init-form present-slot-init-form))))
          (initialize-slot-description-value
            instance new-slot-description new-value)) 
        (set-slot-description-value-without-noting
          instance new-slot-description present-slot-init-form))))))))




;;; `Update-attribute-displays-and-stubs-for-inheritance-change' changes any
;;; attribute-displays or stubs that have changed due to a change in inheritance.

(defun update-attribute-displays-and-stubs-for-inheritance-change
    (class class-inheritance-path)
  ;; Update the attribute-displays class feature.
  (let ((current-attribute-displays-class-feature?
      (get-class-feature-if-any class 'attribute-displays))
    (desired-attribute-displays-spec? 
      (loop for inheritance-path-class in class-inheritance-path
        for attribute-displays-spec? =
        (and (user-defined-class-p inheritance-path-class)
             (slot-description-from-class
               inheritance-path-class 'attribute-displays-for-class)
             (class-slot-description-value
               'attribute-displays-for-class inheritance-path-class))
        when attribute-displays-spec?
          return attribute-displays-spec?)))
    (unless (equal (cdr current-attribute-displays-class-feature?)
           desired-attribute-displays-spec?)
      (if desired-attribute-displays-spec?
      (add-class-feature
        class
        (class-description-cons
          'attribute-displays
          (copy-tree-using-class-description-conses
        desired-attribute-displays-spec?)))
      (remove-class-feature class 'attribute-displays))))

  ;; This removes any attribute displays that are for slots not in the
  ;; new inheritance.  It also updates the value of slots that are in
  ;; the new and old inheritance but have a different default value in
  ;; the new inheritance.  Note that even though the attribute-displays
  ;; class feature may have changed due to the change in inheritance,
  ;; this does not affect existing instances.  It only affects new
  ;; instances.
  (update-attribute-tables-for-instances class t)

  ;; Update the stubs class feature
  (let ((current-stubs-class-feature?
      (get-class-feature-if-any class 'stubs))
    (desired-stubs-specification?
      (and (slot-description-from-class class 'stubs-for-class)
           (or (class-slot-description-value 'stubs-for-class class)
           (get-inherited-stubs-class-feature-for-class
             class-inheritance-path)))))
    (cond ((eq desired-stubs-specification? 'none)
       (unless (and current-stubs-class-feature?
            (eq (cdr current-stubs-class-feature?) 'none))
         (add-class-feature
           class
           (class-description-cons 'stubs 'none))))
      (desired-stubs-specification?
       (unless (equal current-stubs-class-feature?
              desired-stubs-specification?)
         (add-class-feature
           class
           (copy-tree-using-class-description-conses
         desired-stubs-specification?))))
      (t (remove-class-feature class 'stubs)))))




;;; `Change-default-overrides-for-inheritance-change-when-combining-definitions'
;;; takes care of changing class-qualified default overrides on the old-class-
;;; name to overrides on the new-class-name slot when there is a change in
;;; inheritance due to combining class definitions.

(defun change-default-overrides-for-inheritance-change-when-combining-definitions
    (class-definition class-description new-class-name old-class-name)
  (loop for override in (default-overrides class-definition)
    for name-denotation = (first override)
    for class-qualified-name? =
    (class-qualified-name-list-p name-denotation)
    for unqualified-name? =
    (when class-qualified-name?
      (unqualified-name name-denotation))
    do
    (when (and class-qualified-name?
           (eq (class-qualifier name-denotation) old-class-name)
           ;; Make sure the override is not for a superior of
           ;; old-class-name.
           (loop for attribute-description in
             (class-specific-attributes
               (class-definition old-class-name))
             thereis (eq (attribute-name attribute-description)
                 unqualified-name?))
           (not (get-slot-description
              unqualified-name? (slot-descriptions class-description)
              new-class-name)))
      (setf (car override)
        (slot-value-list
          'class-qualified-name new-class-name unqualified-name?)))))




;;; `Determine-class-icon-change-for-inheritance-change' returns a frame-cons
;;; list of the class and the new icon width and height when a change in
;;; inheritance gives the class a new icon description.
;;; a new, fourth, element of the returned frame-list is a frame-list of
;;; icon-variables that should not be deleted during the inheritance change,
;;; since they are present in the new slot-init-form. -alatto, 10/31/05
(defun determine-class-icon-change-for-inheritance-change
    (class class-description all-slot-descriptions-for-class)
  (let ((old-icon-description-slot-init-form
      (slot-init-form
        (get-slot-description
          'icon-description (slot-descriptions class-description))))
    (new-icon-description-slot-init-form
      (slot-init-form
        (get-slot-description
          'icon-description all-slot-descriptions-for-class))))
    (unless (eq old-icon-description-slot-init-form
        new-icon-description-slot-init-form)
      (let* ((old-icon-width
           (width-of-icon old-icon-description-slot-init-form))
         (new-icon-width
           (width-of-icon new-icon-description-slot-init-form))
         (old-icon-height
           (height-of-icon old-icon-description-slot-init-form))
         (new-icon-height
           (height-of-icon new-icon-description-slot-init-form))
         (delta-width
           (-w new-icon-width old-icon-width))
         (delta-height
           (-w new-icon-height old-icon-height))
         (variables-to-save
           (let ((variables?
               (get-variable-specification-if-any
             (icon-line-drawing-description new-icon-description-slot-init-form))))
         (when variables?
           (loop for variable-name-list on (cdr variables?) by #'cddr
             collect (car variable-name-list) using frame-cons)))))
    (frame-list class delta-width delta-height variables-to-save)))))




;;; `Alter-inheritance-of-class-without-changing-foundation-class' is called
;;; from the slot putter code of direct-superiors-of-defined-class when there is
;;; change of direct superior classes that does not involve a change of
;;; foundation class.  It is also called from combine-class-definitions in
;;; kb-merge, and in this case, old-class-name? is the class that is being
;;; merged into new-class-name?.  The class can be an instantiated or
;;; uninstantiated class.  This function takes care of changing the class
;;; descriptions for user-class and all subclasses of user-class.

(defun alter-inheritance-of-class-without-changing-foundation-class
    (user-class-definition new-direct-superiors old-class-name? new-class-name?)
  (let* ((class-is-undergoing-inheritance-change? t)
     (do-not-note-permanent-changes-p t)
     (user-class (name-of-defined-class user-class-definition))
     (object-class-p?
       (loop for direct-superior in new-direct-superiors
         for direct-superior-class-inheritance-path =
             (class-inheritance-path (class-description direct-superior))
         when (memq 'object direct-superior-class-inheritance-path)
           return t))
     (previous-direct-superiors 
       (direct-superiors-of-defined-class user-class-definition))
     (subclasses-with-changing-icons? nil)
     (default-slot-descriptions-for-classes?
         (loop for class being each subclass of user-class
           for class-description = (class-description class)
           when (instantiated-class-p class)
             collect (frame-list
                   class
                   (loop for slot-description in (slot-descriptions
                                   class-description)
                     when (and (user-defined-slot-description-p
                         slot-description)
                           (not (eq (defining-class
                                slot-description)
                            class)))
                       collect slot-description using frame-cons))
               using frame-cons))
     (lookup-slots-to-set? nil)
     (slot-descriptions-to-reclaim? nil))



    (update-frame-status user-class-definition nil nil)
    ;; Change the direct-superior-classes and inferior-classes properties.
    (set-superior-inferior-data-for-inheritance-change
      user-class user-class-definition new-direct-superiors previous-direct-superiors)

    (loop for instance-and-slot-descriptions-list? = nil
      for foundation-class =
      (get-foundation-class-for-class user-class)
      for class being each subclass of user-class
      for current-class-definition = (class-definition class)
      do
      (let* ((class-definition (class-definition class))
         (class-description (class-description class))
         (direct-superiors (direct-superior-classes class))
         (class-inheritance-path 
           (make-class-inheritance-path-for-user-defined-class
         class direct-superiors))
         (old-slot-descriptions (slot-descriptions class-description))
         (default-inherited-slot-descriptions-for-class? 
         (when (instantiated-class-p class)
           (second
             (car-of-cons
               (member class default-slot-descriptions-for-classes?
                   :test 'car-eq)))))
         (slot-descriptions-defined-for-class nil)
         (class-owned-slot-descriptions? nil))

    ;; If this is a combining-class situation and there is a class-
    ;; qualified default override on an old-class-name slot and there is no
    ;; same-named new-class-name slot, put the override on the new-class-name
    ;; slot.  For all other overrides, let the process-default-override code
    ;; deal with the overrides (and the resulting frame notes).
    (when new-class-name?
      (change-default-overrides-for-inheritance-change-when-combining-definitions
        class-definition class-description new-class-name? old-class-name?))

    ;; Because this code is iterating over all of the subclasses and changing
    ;; their slot inheritance, the inherited-slots-this-class-overrides must
    ;; not contain inherited slot names that will not be in the new inheritance.
    ;; Merge-slot-descriptions-for-user-defined-class depends on this component
    ;; being up-to-date.
    (loop for unique-slot-name in (inherited-slots-this-class-overrides
                    class-description)
          for slot-in-new-inheritance? = (loop for superior in direct-superiors
                           thereis
                           (slot-description-from-class
                             superior unique-slot-name))
          unless slot-in-new-inheritance?
        do (delete-slot-from-inherited-slots-this-class-overrides
             class unique-slot-name))

    ;; Gather the slot descriptions defined for class.
    (loop for old-slot-description in old-slot-descriptions
          do
      (when (eq (owner-class old-slot-description) class)
        (setq class-owned-slot-descriptions?
          (frame-cons old-slot-description
                  class-owned-slot-descriptions?)))
      (if (user-defined-slot-description-p old-slot-description)
          (when (eq (defining-class old-slot-description) class)
        (setq slot-descriptions-defined-for-class
              (nconc slot-descriptions-defined-for-class
                 (class-description-list old-slot-description))))
          (let ((pretty-slot-name (pretty-slot-name old-slot-description)))
        (when (or (eq pretty-slot-name 'class)
              (class-has-override-on-slot-p
                class-description
                (unique-slot-name old-slot-description)))
          (setq slot-descriptions-defined-for-class
            (nconc slot-descriptions-defined-for-class
                   (class-description-list old-slot-description)))))))
    
    (when (memq 'message class-inheritance-path)
      ;; This slot must be handled specially because it contains values
      ;; for three default message properties.  Only process-default-message-
      ;; properties can handle it.
      (let ((plist-for-text-box-slot-description?
          (process-default-message-properties
            class-definition class-inheritance-path nil t)))
        (when plist-for-text-box-slot-description?
          (let ((plist-slot-description-in-list?
              (get-slot-description
            'text-cell-plist-for-text-box
            slot-descriptions-defined-for-class)))
        (if plist-slot-description-in-list?
            (let ((cons-holding-slot-description
                (memq plist-slot-description-in-list?
                  slot-descriptions-defined-for-class)))
              (setf (car cons-holding-slot-description)
                plist-for-text-box-slot-description?))
            (setq slot-descriptions-defined-for-class
              (nconc slot-descriptions-defined-for-class
                 (class-description-list
                   plist-for-text-box-slot-description?))))))))

    (when (memq 'text-box class-inheritance-path)
      (let ((plist-for-text-box-slot-description?
          (process-default-text-box-colors class t)))
        (when plist-for-text-box-slot-description?
          (let ((plist-slot-description-in-list?
              (get-slot-description
            'text-cell-plist-for-text-box
            slot-descriptions-defined-for-class)))
        (if plist-slot-description-in-list?
            (let ((cons-holding-slot-description
                (memq plist-slot-description-in-list?
                  slot-descriptions-defined-for-class)))
              (setf (car cons-holding-slot-description)
                plist-for-text-box-slot-description?))
            (setq slot-descriptions-defined-for-class
              (nconc slot-descriptions-defined-for-class
                 (class-description-list
                   plist-for-text-box-slot-description?))))))))
                    
    (multiple-value-bind
        (all-slot-descriptions-for-class class-user-vector-length)
        (merge-slot-descriptions-for-user-defined-class
          class class-inheritance-path
          slot-descriptions-defined-for-class nil)

      (when object-class-p?
        (let ((icon-change?
            (determine-class-icon-change-for-inheritance-change
              class class-description all-slot-descriptions-for-class)))
          (when icon-change?
        (setq subclasses-with-changing-icons?
              (frame-cons icon-change? subclasses-with-changing-icons?))
        (update-images-of-instances-governed-by-this-definition
          class t))))

      (multiple-value-bind
          (slot-descriptions-hash-table full-hash-table-class)
          (make-slot-descriptions-hash-table
        class all-slot-descriptions-for-class class-inheritance-path
        direct-superiors t)

        ;; Now calling adjust-instance-lookup-structures-for-inheritance-
        ;; change with old-class-name? and new-class-name? in order to
        ;; keep slot-descriptions from the old and new inheritance straight.
        ;; (ghw 2/19/97)
        (when (instantiated-class-p class)
          (setq instance-and-slot-descriptions-list?
            (adjust-instance-lookup-structures-for-inheritance-change
              class all-slot-descriptions-for-class
              class-user-vector-length
              default-inherited-slot-descriptions-for-class?
              old-class-name? new-class-name?))

          ;; Set the values of any system-defined slots that that are in
          ;; the old inheritance as well as the new inheritance but have a
          ;; different default value.
          (change-system-slot-values-for-inheritance-change
        class all-slot-descriptions-for-class old-slot-descriptions)

          ;; Gather a list of system-defined slots that are in the new
          ;; inheritance but not in the old.  Note that these will be
          ;; lookup slots because no change of foundation class is allowed
          ;; for instantiated classes.  These slots must be set after the
          ;; classes have received their new inheritance.
          (when (eq class user-class)
        (setq lookup-slots-to-set?
              (loop for slot-description in all-slot-descriptions-for-class
                when (and (system-defined-slot-description-p slot-description)
                      (not (get-slot-description
                         (pretty-slot-name slot-description)
                         old-slot-descriptions)))
                  collect (pretty-slot-name slot-description)
                using frame-cons))))

        ;; Reclaim old class-description component values and set new ones.
        (reclaim-class-description-list
          (class-inheritance-path class-description))
        (setf (class-inheritance-path class-description)
          (copy-list-using-class-description-conses class-inheritance-path))
        (let ((class-description-inheritance-path?
            (class-description-inheritance-path-internal class-description)))
          (when class-description-inheritance-path?
        (reclaim-class-description-list class-description-inheritance-path?)
        (setf (class-description-inheritance-path-internal class-description) nil)))
        (reclaim-slot-value
          (class-inheritance-path-of-definition class-definition))
        (setf (class-inheritance-path-of-definition class-definition)
          class-inheritance-path)
        (setf (class-user-vector-length class-description)
          class-user-vector-length)
        (reclaim-byte-vector (class-bit-vector class-description))
        (setf (class-bit-vector class-description)
          (make-class-bit-vector
            (class-bit-number class-description) class-inheritance-path))
        (reclaim-class-description-list slot-descriptions-defined-for-class)
        (reclaim-class-description-list old-slot-descriptions)
        (setf (slot-descriptions class-description)
          all-slot-descriptions-for-class)
        (reclaim-slot-hash (slot-descriptions-hash-table class-description))
        (setf (slot-descriptions-hash-table class-description) nil)
        (setf (slot-descriptions-hash-table class-description)
          slot-descriptions-hash-table)
        (setf (full-hash-table-class class-description)
          full-hash-table-class)
        (when (eq (class class-definition) 'class-definition)
          (setf (user-overridable-system-slots class-definition)
            (make-list-of-aliased-overridable-system-slots-for-definition
              class-inheritance-path)))
        (update-representations class-definition)))

    (loop for instance being each strict-class-instance of class
          do (clear-item-mark instance))
    (loop with all-slot-descriptions = (slot-descriptions (class-description class))
          with other-instance-and-slot-descriptions-list
        = (nconc
            (loop for (instance . slot-description-list)
                  in instance-and-slot-descriptions-list?
              do (set-item-mark instance)
              collect (frame-cons
                    instance
                    (loop for slot-description in all-slot-descriptions
                      when (and (user-defined-slot-description-p slot-description)
                            (not (memq slot-description slot-description-list)))
                        collect slot-description using frame-cons))
                using frame-cons)
            (loop for instance being each strict-class-instance of class
              unless (item-mark-p instance)
                collect (frame-cons
                      instance
                      (loop for slot-description in all-slot-descriptions
                        when (user-defined-slot-description-p slot-description)
                          collect slot-description using frame-cons))
                  using frame-cons))
          for (instance . slot-description-list)
          in other-instance-and-slot-descriptions-list
          do
      (loop for slot-description in slot-description-list
        for slot-value = (get-slot-description-value instance slot-description)
        do
        (when (framep slot-value)
          (if (frame-of-class-p slot-value 'variable-or-parameter)
          (update-generic-simulation-formula-for-variable-or-parameter
            slot-value)
          (when (frame-of-class-p slot-value 'object)
            (update-runtime-structures-according-to-edit
              slot-value))))
        (update-runtime-structures-according-to-edit instance))
          finally (reclaim-frame-tree other-instance-and-slot-descriptions-list))
    
    (when instance-and-slot-descriptions-list?
      (loop for (instance . slot-descriptions)
            in instance-and-slot-descriptions-list?
        do
        (loop for slot-description in slot-descriptions
          for slot-init-form = (slot-init-form slot-description)
          do
          (let ((value-to-set
              (if (slot-init-form-needs-evaluation? slot-init-form)
              (if (class-in-attribute-conforms-to-type-p
                slot-description (class instance) t)                  
                  (let ((frame-being-made instance))
                (eval-slot-init-form slot-init-form))
                  nil)
              slot-init-form)))
        (change-slot-description-value
          instance slot-description value-to-set))))
      (reclaim-frame-tree instance-and-slot-descriptions-list?))

    (loop with new-slot-descriptions = (slot-descriptions class-description)
          for slot-description in class-owned-slot-descriptions?
          for unique-slot-name = (unique-slot-name slot-description)
          for new-slot-description? =
          (get-slot-description unique-slot-name new-slot-descriptions)
          do
      (unless (eq slot-description new-slot-description?)
        (setq slot-descriptions-to-reclaim?
          (frame-cons (frame-cons class slot-description)
                  slot-descriptions-to-reclaim?))))

    (when object-class-p?
      (instantiate-or-uninstantiate-class-in-attributes-as-appropriate
        class 'change-in-inheritance))))

    ;; Now set the system lookup slots that are new to the classes.
    (when (instantiated-class-p user-class)
      (loop for lookup-slot in lookup-slots-to-set?
        do
    (loop for class being each subclass of user-class
          for slot-description = (slot-description-from-class
                       class lookup-slot)
          for slot-init-form = (slot-init-form slot-description)
          do
      (loop for instance being each strict-class-instance of class
        do
        (if (slot-init-form-needs-evaluation? slot-init-form)
        (let ((new-value
            (let ((frame-being-made instance))
              (eval-slot-init-form slot-init-form))))
          (initialize-slot-description-value
            instance slot-description new-value))
        (set-slot-description-value-without-noting
          instance slot-description slot-init-form)))))
      (reclaim-frame-list lookup-slots-to-set?))

    ;; Now that the system slots have their values, update attribute displays and
    ;; stubs.  (fix for HQ-1919487)
    (when object-class-p?
      (loop for class being each subclass of user-class
        do
    (update-attribute-displays-and-stubs-for-inheritance-change
      class (class-inheritance-path (class-description class)))))

    (reclaim-frame-tree default-slot-descriptions-for-classes?)

    (if (or (indexed-attributes-for-definition user-class-definition)
        (loop for direct-superior in new-direct-superiors
          thereis (get-class-feature-if-any
                direct-superior 'has-indexed-attributes)))
    (add-indexed-feature-to-class-and-subclasses user-class)
    (remove-indexed-feature-from-class-and-subclasses-if-appropriate
      user-class))

    ;; Remove any relations that no longer conform to class-type.
    (unless currently-automatically-resolving-class-name-conflicts?
      (loop for instance being each class-instance of user-class
        when (block-relation-instances-violate-class-type-p instance)
          do (remove-invalid-relation-instances instance)))

    ;; Redraw icons that have changed.
    (when subclasses-with-changing-icons?
      (loop for (class delta-width delta-height variables-to-save)
        in subclasses-with-changing-icons?
        do
    (adjust-and-draw-images-governed-by-this-class
      class delta-width delta-height variables-to-save))
      (reclaim-frame-tree subclasses-with-changing-icons?))

    (update-attribute-tables-for-instances user-class nil)

    (when slot-descriptions-to-reclaim?
      (reclaim-list-of-slot-descriptions slot-descriptions-to-reclaim?)
      (reclaim-frame-tree slot-descriptions-to-reclaim?))
    (initialize-or-update-method-tables-of-class-descriptions
      user-class)))




;;; `Adjust-instance-lookup-structures-for-inheritance-change' changes the
;;; instance lookup structures when there is a change in direct superiors for
;;; an instantiated class.  Since it is illegal to change the direct superiors
;;; when it involves a foundation class change, this function need not deal
;;; with altering the instance main frames.  This function returns a list of
;;; dotted pairs to its caller, alter-inheritance-of-class-without-changing-
;;; foundation-class, (<instance> . <slot-descriptions>) where the
;;; slot-descriptions correspond to the slots that need to be set via
;;; change-slot-description-value-function when the class-descriptions of the
;;; classes has been changed to reflect the new inheritance.  Old-class-name?
;;; and new-class-name? are non-nil when this function has been called via
;;; combine-class-definitions.  Old-class-name? is the class that is being
;;; merged into new-class-name?.

;;; For each slot in the old version of the class, this function tries
;;; to find an identical or equivalent slot in the new version. the
;;; slots-already-used variable is used to ensure that two slots in the
;;; old version of the class are not mapped to the same slot in the
;;; new version, since otherwise, the values in both of the old slots
;;; are preserved, even though there's only one slot to put them in,
;;; resulting in bug HQ-4811056, "Losing attribute from instance via
;;; inheritance change may leak or corrupt" -alatto, 5/3/05
(defun adjust-instance-lookup-structures-for-inheritance-change
    (class new-slot-descriptions new-class-user-vector-length
       default-inherited-slot-descriptions-for-class? old-class-name?
       new-class-name?)
  (let* ((do-not-note-permanent-changes-p t)
     (instance-and-slot-descriptions-list? nil)
     (class-description (class-description class))
     (old-slot-descriptions (slot-descriptions class-description))
     ;; The new slot descriptions need to have their order reversed
     ;; in order to obtain the correct default slot-description.
     (new-slot-descriptions-in-reverse-order
       (nreverse (copy-list-using-frame-conses new-slot-descriptions)))
     (old-class-user-vector-length
       (class-user-vector-length class-description))
     (slot-description-equivalents? nil)
     (slots-already-used nil))
    
    ;; Reclaim the slot values for old slot descriptions omitted in the
    ;; new inheritance, being absolutely sure that lookup slots with
    ;; default values will not be changed because this process may
    ;; allocate a lookup structure or enlarge an existing lookup
    ;; structure.
    (let ((class-is-undergoing-inheritance-change? t))
      (loop for old-slot-description in old-slot-descriptions
        do
    (when (user-defined-slot-description-p old-slot-description)
      (let* ((pretty-slot-name (pretty-slot-name old-slot-description))
         (defining-class (defining-class old-slot-description))
         ;; New-slot-description will have equal components as
         ;; the old, except for the class names when there 
         ;; there is a old-class-name? and new-class-name?
         (candidate-new-slot-description?
           (get-slot-description
             pretty-slot-name new-slot-descriptions
             (if (eq defining-class old-class-name?)
             new-class-name?
             defining-class)))
         (new-slot-description?
           (unless
               (memq candidate-new-slot-description? slots-already-used)
             candidate-new-slot-description?))
         (equivalent-slot-description? 
           (unless new-slot-description?
             (and (memq old-slot-description
                default-inherited-slot-descriptions-for-class?)
              ;; Attempt to match inherited defaults (with
              ;; the same pretty-slot-name) in the old and new slot-
              ;; descriptions.
              (let ((new-equivalent?
                  (get-slot-description
                    pretty-slot-name
                    new-slot-descriptions-in-reverse-order)))
                (and new-equivalent?
                 (not (memq new-equivalent? slots-already-used))
                 (not (eq (defining-class new-equivalent?) class))
                 new-equivalent?))))))
        (when equivalent-slot-description? 
          (setq slot-description-equivalents?
            (frame-cons
              (frame-list equivalent-slot-description? old-slot-description)
              slot-description-equivalents?)))
        (when (or new-slot-description? equivalent-slot-description?)
          (frame-push
        (or new-slot-description? equivalent-slot-description?)
        slots-already-used))
        ;; Reclaim the slot-values for slots that are not in the new inheritance.
        (unless (or new-slot-description? equivalent-slot-description?)
          (loop for instance being each strict-class-instance of class
            for slot-value = (get-slot-description-value
                       instance old-slot-description)
            do
        (when (and slot-value
               (not (fixnump slot-value))
               (not (eq slot-value (slot-init-form old-slot-description))))
          (change-slot-description-value-without-updating-representations
            instance old-slot-description nil pretty-slot-name
            (defining-class old-slot-description) nil nil nil))))))))

    (loop for instance being each strict-class-instance of class
      for old-lookup-structure? = (lookup-structure instance)
      for lookup-portion =
            (if old-lookup-structure?
            (-f (length-of-simple-vector old-lookup-structure?)
            old-class-user-vector-length)
            0)
      for lookup-slot-information? =
            (when (and old-lookup-structure?
               (>f lookup-portion 0))
          (loop for index from old-class-user-vector-length
                  below (1-f (length-of-simple-vector
                           old-lookup-structure?))
                      by 2
            for lookup-slot-name? =
                  (svref old-lookup-structure? index)
            for slot-present-in-new-slot-descriptions? =
                  (and lookup-slot-name?
                   (get-slot-description
                     lookup-slot-name? new-slot-descriptions))
            when lookup-slot-name?
              count index into slot-name-count
            when (and lookup-slot-name?
                  (not slot-present-in-new-slot-descriptions?))
              collect lookup-slot-name? into slot-name-list
                using frame-cons and
              ;; Reclaim the values of the lookup slots that are
              ;; not in the new inheritance.
              ;; The slot-value reclaimer for uuid will adjust
              ;; the duplicate-uuid frame notes (HQ-2124731).
              ;; (ghw 11/3/98)
              do (let ((slot-value?
                     (svref old-lookup-structure? (+f index 1))))
                   (when slot-value?
                 (let ((slot-value-reclaimer?
                     (slot-value-reclaimer lookup-slot-name?)))
                   (if slot-value-reclaimer?
                       (funcall-simple-compiled-function
                     slot-value-reclaimer? slot-value? instance)
                       (reclaim-slot-value slot-value?)))))
            finally (return
                  (frame-list
                    slot-name-count slot-name-list))))
      for old-number-of-lookup-slots =
            (if lookup-slot-information?
            (first lookup-slot-information?)
            0)
      for list-of-obsolete-lookup-slots-on-old-structure? =
            (and lookup-slot-information?
             (second lookup-slot-information?))
      for number-of-obsolete-slots =
            (if list-of-obsolete-lookup-slots-on-old-structure?
            (length list-of-obsolete-lookup-slots-on-old-structure?)
            0)
      for new-number-of-lookup-slots =
            (-f old-number-of-lookup-slots
            number-of-obsolete-slots)
      for new-lookup-structure? =
          (if (or (>f new-class-user-vector-length 0)
              (>f new-number-of-lookup-slots 0))
          (allocate-frame-lookup-structure-vector
            (+f new-class-user-vector-length
            (*f new-number-of-lookup-slots 2))
            nil)
          nil)
      do
      ;; Put the user vector slot values into the new lookup structure when there
      ;; is a corresponding old slot-description and the slot values are non-default
      ;; or the old slot-description is equal to the new slot-description or the value
      ;; needs evaluation.
      (when (>f new-class-user-vector-length 0)
    (loop with list-of-slot-descriptions-that-need-setting? = nil
          for new-slot-description in new-slot-descriptions-in-reverse-order
          until (system-defined-slot-description-p new-slot-description)
          for user-vector-slot-index? =
            (user-vector-slot-index? new-slot-description)
          for pretty-slot-name = (pretty-slot-name new-slot-description)
          for slot-type-specification =
                (slot-type-specification new-slot-description)
          for defining-class = (defining-class new-slot-description)
          for new-slot-init-form = (slot-init-form new-slot-description)
          for new-slot-init-form-needs-evaluation? =
            (slot-init-form-needs-evaluation? new-slot-init-form)
          for equivalent-slot-description? = nil
          for old-slot-description? =
                (or (get-slot-description
              pretty-slot-name old-slot-descriptions
              (if (eq defining-class new-class-name?)
                  old-class-name?
                  defining-class))
            (let ((cons-holding-new-slot-description?
                (member
                  new-slot-description
                  slot-description-equivalents?
                  :test 'car-eq)))
              (and cons-holding-new-slot-description?
                   (setq equivalent-slot-description? t)
                   (second
                 (car-of-cons
                   cons-holding-new-slot-description?))))) 
          for old-slot-init-form? =
            (when old-slot-description?
              (slot-init-form old-slot-description?))
          do
      (setf (svref new-lookup-structure? user-vector-slot-index?)
        
        (cond (old-slot-description?
               (let* ((old-slot-value
                (get-slot-description-value
                  instance old-slot-description?)))
            (cond
              ;; Put the old slot values on the new lookup-structure
              ;; in these cases:
                   ;; This is an optimization.
              ((or (eq new-slot-description old-slot-description?)
                   (and (neq old-slot-value old-slot-init-form?)
                    (slot-value-conforms-to-type-specification-p
                      old-slot-value slot-type-specification)))
               (get-slot-description-value
                 instance old-slot-description?))
              (t
               ;; Will not use old slot values because the old-slot-
               ;; value is EQ to the old slot-init-form (and must be
               ;; set EQ to the new slot-inot-form) or the old-slot-value
               ;; does not conform to type.
               (frame-push
                 new-slot-description
                 list-of-slot-descriptions-that-need-setting?)
               (change-slot-description-value-without-updating-representations
                 instance old-slot-description? nil
                 pretty-slot-name defining-class nil nil nil)
               nil))))
              (t
               (frame-push
             new-slot-description
             list-of-slot-descriptions-that-need-setting?)
               nil)))
          finally
        (when list-of-slot-descriptions-that-need-setting?
          (setq instance-and-slot-descriptions-list?
            (frame-cons
              (frame-cons
                instance list-of-slot-descriptions-that-need-setting?)
              instance-and-slot-descriptions-list?)))))
      ;; Copy the lookup-slot values from the old lookup-structure
      ;; to the new lookup-structure.
      (when (and old-lookup-structure? new-lookup-structure?
         (>f new-number-of-lookup-slots 0))
    (loop with new-index = new-class-user-vector-length     
          for old-index from old-class-user-vector-length
                        below (1-f (length-of-simple-vector old-lookup-structure?))
                        by 2
          for lookup-slot-name? = (svref old-lookup-structure? old-index)
          do
          ;; There are gaps in the lookup portion of the lookup structure
          ;; in order to avoid frequent allocation of lookup-structures. 
      (if (null lookup-slot-name?)
          nil
          (unless (memq lookup-slot-name?
                list-of-obsolete-lookup-slots-on-old-structure?)
        (setf (svref new-lookup-structure? new-index)
              (svref old-lookup-structure? old-index))
        (setf (svref new-lookup-structure? (+f new-index 1))
              (svref old-lookup-structure? (+f old-index 1)))
        (setq new-index (+f new-index 2))))))

      (setf (lookup-structure instance) new-lookup-structure?)
      (when old-lookup-structure?
    (reclaim-frame-lookup-structure-vector old-lookup-structure?))
      (reclaim-frame-tree lookup-slot-information?))
    (reclaim-frame-list new-slot-descriptions-in-reverse-order)
    (reclaim-frame-list slots-already-used)
    (reclaim-frame-tree slot-description-equivalents?)
    instance-and-slot-descriptions-list?))
    



;;; `User-vector-slot-location-differs-in-subclass-p' determines whether the
;;; user vector slot index for the slot referenced by user-vector-slot-name is
;;; the same for class and all of the subclasses of class.  If the index is the
;;; same, this function returns nil; otherwise it returns t.  If
;;; class-of-slot-reference? is non-nil, the slot is the slot of that name
;;; defined specifically for the class symbol denoted by class-of-
;;; slot-reference?; otherwise it is the default slot with that name for each
;;; class examined.  This function assumes the validity of all of its
;;; arguments.

(defun-simple user-vector-slot-location-differs-in-subclass-p-1
    (class-slot-description pretty-slot-name class class-of-slot-reference?)
  (loop with class-slot-location =
           (user-vector-slot-index? class-slot-description)
    for subclass being each subclass of class
    for subclass-slot-description =
          (get-slot-description-of-class-description
        pretty-slot-name (class-description subclass)
        class-of-slot-reference?)
    for subclass-slot-location =
          (user-vector-slot-index? subclass-slot-description)
    when (/=f class-slot-location subclass-slot-location)
      return subclass))

(defun user-vector-slot-location-differs-in-subclass-p
    (pretty-slot-name class &optional class-of-slot-reference?)
  (let* ((class-description (class-description class))
     (subclass-change-timestamp (class-description-subclass-change-timestamp class-description))
     (class-slot-description
       (get-slot-description-of-class-description
         pretty-slot-name class-description
         class-of-slot-reference?)))
    (if (and subclass-change-timestamp
         (eql subclass-change-timestamp
          (timestamp-for-cached-user-vector-slot-location-differs-in-subclass-p class-slot-description)))
    (cached-user-vector-slot-location-differs-in-subclass-p class-slot-description)
    ;; we would like call user-vector-slot-location-differs-in-subclass-p-1 with a third argument
    ;; of class, but since we are going to cache the result in the slot-description,
    ;; we have to use that slot's owner-class instead.  The result may be nil when it could actually
    ;; be t, which is slower, but OK.
    (let* ((class-1 (owner-class class-slot-description))
           (result (user-vector-slot-location-differs-in-subclass-p-1
            class-slot-description pretty-slot-name class-1 class-of-slot-reference?)))
      (setf (cached-user-vector-slot-location-differs-in-subclass-p class-slot-description)
        result)
      (setf (timestamp-for-cached-user-vector-slot-location-differs-in-subclass-p class-slot-description)
        subclass-change-timestamp)
      result))))




;;; The slot-putter `icon-description-for-class?' is here in order to pick up
;;; the macro `without-consistency-analysis.'

(def-slot-putter icon-description-for-class? (definition icon-description?)
  ;; The icon description may now include names of image-definitions,
  ;; as well as text-drawing-elements.
  (let ((class? (name-of-defined-class definition))
    (background-layer?
      (second (get-icon-background-layer-if-any
            (cddr icon-description?)))))
    (without-consistency-analysis (definition)
      (setf (icon-description-for-class? definition) icon-description?)
      (setf (icon-background-images definition)
        (copy-for-slot-value background-layer?)))
    (when (classp class?)
      (cond (icon-description?
         (add-slot-to-inherited-slots-this-class-overrides
           class? 'icon-description)
         (add-slot-to-inherited-slots-this-class-overrides
           class? 'icon-background-images)
         (update-icon-description icon-description? definition))
        (t
         (delete-slot-from-inherited-slots-this-class-overrides
           class? 'icon-description)
         (delete-slot-from-inherited-slots-this-class-overrides
           class? 'icon-background-images)
         (update-icon-description nil definition t)))))
  icon-description?)


;;; The function `get-inherited-stubs-class-feature-for-class' finds and returns
;;; the stubs class feature the class will inherit when there is no class-
;;; specific value in the connections-for-class? slot of the class definition.
;;; If no superior specifies a connections-for-class? value, this function will
;;; return nil.
;;;
;;; The process of determining inherited stubs does not follow the inheritance
;;; determination of other class properties.  For example, the icon-description
;;; that a class inherits (when there is no class-specific icon-description) is
;;; the icon-description of the most-specific superior on the class inheritance
;;; path that defines an icon-description.  If the same process was used for
;;; stubs, a multiple-inheritance class could inherit an icon-description from
;;; one branch of the class hierarchy and a stubs specification from another
;;; branch of the hierarchy, and the two specifications could be weirdly
;;; mismatched.
;;; 
;;; The solution for G2 4.0 was for a class to inherit its stubs specification
;;; from the same class from which it inherited its icon-description.  However,
;;; users have found this to be counter-intuitive, as well as quite different
;;; from G2 3.0 behavior.  For example, looking at two user-defined classes,
;;; class-a and class-b, where the direct superior of class-a is object and the
;;; direct superior of class-b is class-a, when class-a defines a stubs
;;; specification but no icon-description, class-b in G2 4.0 inherits its
;;; icon-description and its stub specification from object, leaving class-b
;;; without a stubs class feature.
;;;
;;; This function changes that stubs/icon pairing.  The stubs a class now
;;; inherits are those belonging to the most-specific superior on the
;;; class-inheritance-path for class that inherits its icon-description from the
;;; same superior that the class inherits its icon-description.  In the example
;;; above, then, class-b would inherit the stubs of class-a as it does in G2
;;; 3.0, and a class with multiple inheritance would be assured of having both
;;; the stubs and icon defined in the same branch of the class hierarchy.

(defun get-inherited-stubs-class-feature-for-class
    (user-class-inheritance-path)
  (let* ((object-level-icon-slot-description
       (get-slot-description-of-class-description
         'icon-description (class-description 'object)))
     (superior-that-bestowed-icon-description-on-user-class
       (most-specific-superior-that-refines-slot
         user-class-inheritance-path
         object-level-icon-slot-description))
     (superior-icon-description-inheritor-or-definer
       (loop for superior in (cdr user-class-inheritance-path)
         for superior-that-bestowed-icon-description-on-superior
             =
         (most-specific-superior-that-refines-slot
           (class-inheritance-path (class-description superior))
           object-level-icon-slot-description)
         until (eq
             superior
             superior-that-bestowed-icon-description-on-user-class)
         when (eq superior-that-bestowed-icon-description-on-superior
              superior-that-bestowed-icon-description-on-user-class)
           return superior
         finally (return
               superior-that-bestowed-icon-description-on-user-class))))
    (get-class-feature-if-any
      superior-icon-description-inheritor-or-definer 'stubs)))




;;; `Connections-for-class?' is a slot on object-definitions.  It is maintained
;;; for backward compatibility.  There is no such slot on class-definitions.
;;; All defined object classes have a class-specific-value (lookup) slot,
;;; `stubs-for-class', that contains the class value for all defined object
;;; classes (whether defined with a class-definition or with an object-
;;; definition) just as the attribute-displays-spec?  slot contains the class
;;; value for classes defined with an object-definition.

;; New-value? can be of the form (stubs () () ..), or none ("none"), or
;; nil ("inherited").

(def-slot-putter connections-for-class?
    (object-definition new-value? initializing?)
  ;; HQ-1296674 and HQ-1296589
  (without-consistency-analysis (object-definition)
    (let ((class-name? (name-of-defined-class object-definition)))
      (when (and loading-kb-p
         (not (connections-for-class-slot-correct-format-p))
         (consp new-value?))
    (loop for stub-spec in (cdr new-value?) do
      (when (=f (length stub-spec) 5)
        (setf (cdr (nthcdr 4 stub-spec)) (slot-value-cons nil nil))))
    (when (consp new-value?)
      (loop for connection-description in (cdr new-value?) 
        for substitute-class = (substitute-class
                     (second connection-description))
        if substitute-class
          do (setf (second connection-description) substitute-class))))
      (setf (connections-for-class? object-definition) new-value?)
      (cond ((and (classp class-name?)
          (slot-description-from-class class-name? 'stubs-for-class))
         (update-stubs-for-class class-name? new-value?))
        (t (when (slot-description-from-class class-name? 'stubs-for-class)
         (do-stubs-consistency-analysis
             object-definition new-value? initializing?))
           new-value?)))))

(def-class-slot-description-updater stubs-for-class
    (object-class new-value)
  (let ((old-value?
	 (class-slot-description-value 'stubs-for-class object-class)))
    (when (not (symbolp old-value?))
      (loop for (port-name?) in (cdr old-value?)
	    when port-name?
	    do (delete-from-directory-of-names port-name? 'port-name)))
    (change-class-slot-description-value 'stubs-for-class object-class new-value)
    (loop for subclass being each subclass of object-class
	  for subclass-class-description = (class-description subclass)
	  for current-class-feature? = (get-class-feature-if-any subclass 'stubs)
	  for desired-stubs-specification? =
	      (or (class-slot-description-value 'stubs-for-class subclass)
		  (get-inherited-stubs-class-feature-for-class
		    (class-inheritance-path subclass-class-description)))
	  do
      (cond ((eq desired-stubs-specification? 'none)
	     (unless (and current-class-feature?
			  (eq (cdr current-class-feature?) 'none))
	       (add-class-feature
		 subclass
		 (class-description-cons 'stubs 'none))))
	    (desired-stubs-specification?
	     (unless (equal current-class-feature?
			    desired-stubs-specification?)
	       (add-class-feature
		 subclass
		 (copy-tree-using-class-description-conses
		   desired-stubs-specification?))))
	    (t (remove-class-feature subclass 'stubs))))
    new-value))

(defun do-stubs-consistency-analysis (class-definition new-value? initializing?)
  (let ((user-class (name-of-defined-class class-definition)))
    (without-consistency-analysis (class-definition)
      (let ((old-value?
          (if (classp user-class)
          (class-slot-description-value 'stubs-for-class user-class)
          (when (and (not initializing?)
                 (frame-of-class-p
                   class-definition 'object-definition))
            (connections-for-class? class-definition)))))
    (when (not (symbolp old-value?))        ; nil or none
      (loop for (port-name?) in (cdr old-value?)
        when port-name?
          do (delete-from-directory-of-names port-name? 'port-name)))
    (when (not (symbolp new-value?))        ; nil or none
      (loop for (port-name?) in (cdr new-value?)
        when port-name?
          do (add-to-directory-of-names port-name? 'port-name)))))))

(defun cleanup-for-stubs-for-class (frame)
  (unless (classp (name-of-defined-class frame))
    (let ((old-value? (connections-for-class? frame)))
      (unless (symbolp old-value?)
    (loop for (port-name?) in (cdr old-value?)
          when port-name?
        do (delete-from-directory-of-names port-name? 'port-name))))))



;;; `Cross-section-pattern-for-connection' is a slot on connection-definitions.
;;; It is maintained for backward compatibility.  There is no such slot on
;;; class-definitions.  All defined connection classes have a class-specific-
;;; value (lookup) slot, `cross-section-pattern-for-class', that contains the
;;; class value for all defined connection classes (whether defined with a class
;;; definition or with an connection-definition), just as the cross-section-
;;; pattern-for-connection slot contains the class value for classes defined
;;; with connection-definition.

(def-slot-putter cross-section-pattern-for-connection
    (class-definition new-value)
  (setf (cross-section-pattern-for-connection class-definition) new-value)
  (when (not (transient-p class-definition))
    (let ((class (name-of-defined-class class-definition)))
      (if (classp class)
      (update-cross-section-pattern-for-class class new-value)
      new-value))))


(def-class-slot-description-updater cross-section-pattern-for-class
    (connection-class new-value)
  (let* ((class-definition (class-definition connection-class))
     (class-description (class-description connection-class))
     (cross-section-pattern-slot-description
       (get-slot-description
         'cross-section-pattern (slot-descriptions class-description)))
     (revert-to-superior? (if new-value nil t)))
    (if new-value
    (add-slot-to-inherited-slots-this-class-overrides
      connection-class 'cross-section-pattern)
    (delete-slot-from-inherited-slots-this-class-overrides
      connection-class 'cross-section-pattern))
    (change-class-slot-description-value
      'cross-section-pattern-for-class connection-class new-value)
    (update-junction-block-for-connection
      connection-class class-definition new-value)
    (update-all-connections-of-class connection-class t nil)
    (update-slot-description
      connection-class cross-section-pattern-slot-description nil new-value
      (slot-features cross-section-pattern-slot-description) revert-to-superior? nil)
    (update-subrectangle-structures-for-class-and-subclasses
      connection-class
      (if revert-to-superior?
      (slot-init-form
        (slot-description-of-most-specific-superior-refining-slot
         (class-inheritance-path class-description)
           cross-section-pattern-slot-description))
      new-value))
    (update-all-cross-section-patterns-of-instances connection-class)
    (update-all-connections-of-class connection-class nil nil))
  new-value)




(defun update-subrectangle-structures-for-class-and-subclasses
       (connection-class new-value)
  (update-subrectangle-structures-for-class-and-subclasses-1
    connection-class new-value
    (get-slot-description
      'cross-section-pattern
      (slot-descriptions (class-description connection-class)))))




(defun update-subrectangle-structures-for-class-and-subclasses-1
       (connection-sub-class new-value slot-description)
  (when (eq (get-slot-description
          'cross-section-pattern
          (slot-descriptions (class-description connection-sub-class)))
        slot-description)
    (update-connection-subrectangle-structures
      connection-sub-class new-value)
    (loop for inferior-class in (inferior-classes connection-sub-class)
      do (update-subrectangle-structures-for-class-and-subclasses-1
           inferior-class new-value slot-description))))

;; Note that since generation of subrectangle structures is based solely 
;; on the cross-section-stripe and not the cross-section-region, and since
;; only the cross-section-region can be changed for instances, there is
;; no need to check here whether instances have been changed.




(defun update-connection-subrectangle-structures 
       (connection-class cross-section-pattern)
  (reclaim-connection-subrectangle-structures
    (connection-subrectangle-structures-for-drawing connection-class))
  (setf (connection-subrectangle-structures-for-drawing connection-class)
    (generate-connection-subrectangle-structures cross-section-pattern)))



;; Could discover whether or not the old icon description is user created.


(defun locate-or-create-junction-block-definition (name size)
  (let ((junction-block-definition (class-definition name))
    (called-within-locate-or-create-junction-block-definition t))
    (if junction-block-definition

    (progn (unless (eql size
                (second
                  (icon-description-for-class?
                junction-block-definition)))

         (change-slot-value
           junction-block-definition
           'icon-description-for-class?
           (slot-value-list
             (copy-for-slot-value size)
             (copy-for-slot-value size)
             (slot-value-list 'polychrome)
             (slot-value-list 'variables)
             (slot-value-list 'background-layer)
             (slot-value-list 'outline
                      (slot-value-list 0 0)
                      (slot-value-list (copy-for-slot-value size) 0)
                      (slot-value-list (copy-for-slot-value size)
                               (copy-for-slot-value size))
                      (slot-value-list 0 (copy-for-slot-value size)))))))
    
    (progn (setq junction-block-definition
             ;; make-frame was used here until today, so a fixup should 
             ;; now be added for old KBs!  (This interacts with the new
             ;; transfer-original menu choice.) (MHD 7/7/92)
             (make-entity 'object-definition))
           ;; Note: this still does not manage to get a name box put under
           ;; the entity! That interacts poorly with the transfer-original
           ;; menu choice, but the bug is so obscure we could probably live
           ;; with it for a while.  (MHD 7/7/92)
           (change-slot-value junction-block-definition 
                  'name-of-defined-class name)
           (change-slot-value junction-block-definition
                  'direct-superiors-of-defined-class
                  (slot-value-list 'default-junction))
           (change-slot-value       ; exact same code as in then
         junction-block-definition  ;   clause above!
         'icon-description-for-class?
         (slot-value-list
           (copy-for-slot-value size)
           (copy-for-slot-value size)
           (slot-value-list 'polychrome)
           (slot-value-list 'variables)
           (slot-value-list 'background-layer)
           (slot-value-list 'outline
                    (slot-value-list 0 0)
                    (slot-value-list (copy-for-slot-value size) 0)
                    (slot-value-list (copy-for-slot-value size)
                             (copy-for-slot-value size))
                    (slot-value-list 0 (copy-for-slot-value size)))))
           (change-slot-value junction-block-definition 'instantiate? t)
           (change-slot-value
         junction-block-definition 'include-in-menus? nil)))

    (set-permanent-block junction-block-definition)
    
    junction-block-definition))




;;; `Stub-length-for-connection' is a slot on connection-definitions.  It is
;;; maintained for backward compatibility.  There is no such slot on class-
;;; definitions.  All defined connection classes have a class-specific-value
;;; (lookup) slot, `stub-length-for-class', that contains the class value for
;;; all defined connection classes (whether defined with a class definition or
;;; with an connection-definition), just as the stub-length-for-connection slot
;;; contains the class value for classes defined with connection-definition.

(def-slot-putter stub-length-for-connection (definition new-value)
  (let ((connection-class (name-of-defined-class definition)))
    (setf (stub-length-for-connection definition) new-value)
    (if (classp connection-class)
    (update-stub-length-for-class connection-class new-value)
    new-value)))

(def-class-slot-description-updater stub-length-for-class
    (connection-class new-value)
  (let ((stub-length-slot-description
      (slot-description-from-class connection-class 'stub-length)))
    (if new-value
    (add-slot-to-inherited-slots-this-class-overrides
      connection-class 'stub-length)
    (delete-slot-from-inherited-slots-this-class-overrides
      connection-class 'stub-length))
    (change-class-slot-description-value
      'stub-length-for-class connection-class new-value)
    (update-slot-description
      connection-class stub-length-slot-description
      nil new-value (slot-features stub-length-slot-description) nil nil)))




;;; `Junction-block-class-for-connection' is a slot on connection-definitions.
;;; It is maintained for backward compatibility.  There is no such slot on
;;; class-definitions.  All defined connection classes have a
;;; class-specific-value (lookup) slot, `junction-block-class-for-class', that
;;; contains the class value for all defined connection classes (whether defined
;;; with a class definition or with an connection-definition), just as the
;;; junction-block-class-for-connection slot contains the class value for
;;; classes defined with connection-definition.

(def-slot-putter junction-block-class-for-connection
    (connection-definition new-value)
  (let* ((new-value (or (substitute-class new-value) new-value))
     (connection-class (name-of-defined-class connection-definition)))
    (setf (junction-block-class-for-connection connection-definition) new-value)
    (if (classp connection-class)
    (update-junction-block-class-for-class connection-class new-value)
    new-value)))

(def-class-slot-description-updater junction-block-class-for-class
    (connection-class new-value)
  (let ((old-value
      (class-slot-description-value
        'junction-block-class-for-class connection-class)))
    (when (neq old-value new-value)
      (delete-junction-block-definition-if-appropriate
    connection-class old-value)))
  (if new-value
      (add-slot-to-inherited-slots-this-class-overrides
    connection-class 'junction-block-class)
      (delete-slot-from-inherited-slots-this-class-overrides
    connection-class 'junction-block-class))
  (change-class-slot-description-value
    'junction-block-class-for-class connection-class new-value)
  (let ((junction-block-class-slot-description
      (slot-description-from-class connection-class 'junction-block-class)))
    (update-slot-description
      connection-class junction-block-class-slot-description
      nil new-value (slot-features junction-block-class-slot-description)
      (not new-value) nil)))




;;; `Default-message-properties' is a slot on message-definitions.  It is
;;; maintained for backward compatibility.  There is no such slot on
;;; class-definitions.  All defined message classes have a class-specific-value
;;; (lookup) slot, `default-message-properties-for-class', that contains the
;;; class value for all defined message classes (whether defined with a class
;;; definition or with an message-definition), just as the
;;; default-message-properties slot contains the class value for classes defined
;;; with message-definition.

(def-slot-putter default-message-properties (message-definition new-value)
  (let ((class (name-of-defined-class message-definition)))
    (setf (default-message-properties message-definition) new-value)
    (if (classp class)
    (update-default-message-properties-for-class class new-value)
    new-value)))

(def-class-slot-description-updater default-message-properties-for-class
    (message-class new-value)
  (change-class-slot-description-value
    'default-message-properties-for-class message-class new-value)
  
  (if (cdr (assq 'font new-value))
      (add-slot-to-inherited-slots-this-class-overrides
    message-class 'default-text-box-format-name)
      (delete-slot-from-inherited-slots-this-class-overrides
    message-class 'default-text-box-format-name))
  (if (or (cdr (assq 'border-color new-value))
      (cdr (assq 'line-color new-value))
      (cdr (assq 'background-color new-value)))
      (add-slot-to-inherited-slots-this-class-overrides
    message-class 'text-cell-plist-for-text-box)
      (delete-slot-from-inherited-slots-this-class-overrides
    message-class 'text-cell-plist-for-text-box))
  (if (cdr (assq 'minimum-width new-value))
      (add-slot-to-inherited-slots-this-class-overrides
    message-class 'minimum-width-of-text-box)
      (delete-slot-from-inherited-slots-this-class-overrides
    message-class 'minimum-width-of-text-box))
  (if (cdr (assq 'minimum-height new-value))
      (add-slot-to-inherited-slots-this-class-overrides
    message-class 'minimum-height-of-text-box)
      (delete-slot-from-inherited-slots-this-class-overrides
    message-class 'minimum-height-of-text-box))

  (loop for subclass being each subclass of message-class
    for subclass-class-definition = (class-definition subclass)
    do
    (process-default-message-properties
      subclass-class-definition
      (class-inheritance-path-of-definition subclass-class-definition)
      nil nil)))







;;; `prepare-for-indexed-attributes-moveage' is used to set up some internal
;;; bookkeeping information on class-definitions if attributes with indices are
;;; being moved around.  NEW-VALUE must not share list structure with OLD-VALUE.

(defun-void prepare-for-indexed-attributes-moveage (definition old-value new-value)
  ;; I doubt the reclaim is necessary since this function shouldn't be called
  ;; during the short lifetime of the old-vales-of-.. slot, but this will prevent a
  ;; leak in case that assumption is incorrect.  Existing code was doing it so
  ;; who am I to break with tradition?  Though see slot-value-compiler for
  ;; old-attribute-descriptions which is not doing the reclaim.  -dkuznick, 3/2/01
  (reclaim-slot-value (old-value-of-indexed-attributes definition))
  (setf (old-value-of-indexed-attributes definition) old-value)
  (setf (indexed-attributes-for-definition definition) new-value))





;;;; Testing for Valid Superior Classes



;; Note: this section was originally the once-giant
;; invalid-set-of-direct-superior-classes-p function, which used to be just
;; above the slot putter for direct-superiors-of-defined-class. It was also part
;; of the once-giant slot-value compiler for list-of-classes (GRAMMAR6), which
;; had much nearly identical code. (MHD 10/26/01)

;; Note: in certain cases, the order of the tests differed between the slot
;; putter and the slot value compiler; in such cases, the order was changed to
;; have the same order as the compiler, since that's the been the main consumer
;; of these tests in previous releases. Also, in a few cases, tests were missing
;; from the putter, were only present in the compiler. They're now become common
;; to both. (MHD 10/26/01)





;;; `Do-valid-superior-tests' is used by the slot compiler and slot putter for
;;; direct-superiors-of-defined-class.  It runs test functions defined via the
;;; macro def-valid-superior-test. Each test returns nil if there is no problem
;;; found; otherwise, an error message as a newly created text string, in which
;;; case the caller is respondible for reclaiming or incorporating the resulting
;;; text string.

(defvar all-valid-superior-test-functions '())

(defmacro def-valid-superior-test
    (test-name
      (direct-superior-classes?-var
    definition-var
    &optional possible-class-inheritance-path?-var)
      &body body)
  (let* ((function-name (build-ab-symbol 'test test-name))
     (arglist
       `(,direct-superior-classes?-var
           ,definition-var
           ,possible-class-inheritance-path?-var)))
    `(progn
       (defun ,function-name ,arglist
     . ,body)
       (unless (memq ',function-name all-valid-superior-test-functions)
     (setq all-valid-superior-test-functions
           (nconc all-valid-superior-test-functions
              (list ',function-name))))
       ',test-name)))

(defun do-valid-superior-tests
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (loop for test-function in all-valid-superior-test-functions
    thereis
      (funcall
        test-function
        direct-superior-classes?
        definition
        possible-class-inheritance-path?)))




;;; The `valid superior' tests are as follows. They are numbered so as make it easier
;;; to write a series of tests that can be easily ordered and referred to by number.

;;; 1. `specified-an-internal-system-class': a direct superior is a
;;;   non-user-extensible system-defined class.

(def-valid-superior-test specified-an-internal-system-class
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore definition possible-class-inheritance-path?))
  (loop for superior in direct-superior-classes?
    when (and (system-defined-class-p superior)
          (null (get-class-feature-if-any superior 'foundation-class)))
      return (specified-an-internal-system-class superior)))



;;; 2. `no-editing-of-default-junction': Editing an automatically created
;;;   junction block.

(def-valid-superior-test no-editing-of-default-junction
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore direct-superior-classes? possible-class-inheritance-path?))
  (when (and (null (superblock? definition))
         (subclassp (name-of-defined-class definition) 'default-junction))
    (no-editing-of-default-junction)))


;;; 3. `default-junction-cannot-be-a-direct-superior-class': an automatically
;;;   created junction block cannot be specified as a direct superior class.

(def-valid-superior-test default-junction-cannot-be-a-direct-superior-class
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore definition possible-class-inheritance-path?))
  (loop for superior in direct-superior-classes?
    for superior-definition = (class-definition superior)
    when (and superior-definition
          (framep superior-definition)
          (null (superblock? superior-definition))
          (not loading-kb-p)
          (not called-within-clear-text-loading))
      return (default-junction-cannot-be-a-direct-superior-class superior)))


;;; 4. `no-editing-of-transient-definition-with-defaults': A transient definition
;;;   has default message properties or default overrides on system slots.

(def-valid-superior-test no-editing-of-transient-definition-with-defaults
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore direct-superior-classes? possible-class-inheritance-path?))
  (when (and (transient-p definition)
         (or (and (frame-of-class-p definition 'message-definition)
              (default-message-properties definition))
         (default-overrides-on-system-slots-p definition)))
    (no-editing-of-transient-definition-with-defaults
      (if (frame-of-class-p definition 'message-definition) t nil))))



;;; 5. `direct-superior-is-name-of-class': A direct superior has the same symbol
;;;   as the class.

(def-valid-superior-test direct-superior-is-name-of-class
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore possible-class-inheritance-path?))
  (when (memq (name-of-defined-class definition) direct-superior-classes?)
    (direct-superior-is-name-of-class)))



;;; 6. `incorrect-foundation-class-for-this-definition': A defined direct
;;;   superior class is not the correct primary foundation class for this
;;;   definition; for instance, this definition is an object definition and the
;;;   primary foundation class for a direct superior is message.  This loop also
;;;   catches violations to mixed hierarchies where we need to consider the
;;;   limitations of the most specialized class on the hierarchy.  For example,
;;;   this class is a class-definition but there is also an object-definition
;;;   used to defined the class hierarchy.

(def-valid-superior-test incorrect-foundation-class-for-this-definition
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore possible-class-inheritance-path?))
  (let* ((class-primary-foundation-class
       (get-primary-foundation-class-for-definition definition))
     (other-specialized-definition-class?
       (definition-hierarchy-is-mixed-p definition))
     prohibited-superior?)
    (when (and direct-superior-classes?
           (setq prohibited-superior?
             (incorrect-foundation-class-for-this-definition-p
               direct-superior-classes? class-primary-foundation-class
               other-specialized-definition-class?)))
      (if (and other-specialized-definition-class?
           (neq other-specialized-definition-class? 'class-definition))
      (direct-superior-not-the-mixed-hierarchy-type
        prohibited-superior? other-specialized-definition-class?)
      (direct-superior-not-the-class-definition-type
        prohibited-superior? class-primary-foundation-class)))))



;;; 7. `direct-superior-not-the-mixed-hierarchy-type': there is a violation to a
;;;   mixed hierarchy that is still in the potential stage of development.  For
;;;   example, there is a potential superior class that is using a more
;;;   specialized definition and there is an instantiated item class on the
;;;   direct superiors for this definition.

(def-valid-superior-test direct-superior-not-the-mixed-hierarchy-type
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore possible-class-inheritance-path?))
  (loop with superior-potential-definition-primary-foundation-class? = nil
    with other-specialized-definition-class?
      = (definition-hierarchy-is-mixed-p definition)
    for superior in direct-superior-classes?
    for prohibited-superior-class?
        = (loop for potential-superior-definition being each
            potential-superior-definition of superior
            for superior-definition-primary-foundation-class
            = (get-primary-foundation-class-for-definition
                potential-superior-definition)
            for current-prohibited-superior?
            = (incorrect-foundation-class-for-this-definition-p
                direct-superior-classes?
                superior-definition-primary-foundation-class
                other-specialized-definition-class?)
            when current-prohibited-superior?
              do (setq superior-potential-definition-primary-foundation-class?
                   superior-definition-primary-foundation-class)
             (return current-prohibited-superior?))
    when prohibited-superior-class?
      return (direct-superior-not-the-mixed-hierarchy-type
           prohibited-superior-class?
           superior-potential-definition-primary-foundation-class?)))



;;; 8. `incompatible-definition-classes': the class-definition class of a
;;;   user-defined direct superior is not compatible with this definition class.

(def-valid-superior-test incompatible-definition-classes
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore possible-class-inheritance-path?))
  (let ((prohibited-superior?
      (loop for superior in direct-superior-classes?
        for superior-class-definition? = (class-definition superior)
        do
        (when (framep superior-class-definition?)
          (unless (or (definition-classes-are-compatible-p
                  definition superior-class-definition?)
              ;; One of them is a class-definition.
              (or (not
                (definition-class-is-subclass-of-obj-conn-mess-definition-p
                    definition))
                  (not
                (definition-class-is-subclass-of-obj-conn-mess-definition-p
                    superior-class-definition?))))
        (return superior))))))
    (if prohibited-superior?
    (incompatible-definition-classes
      (get-specialized-definition-class definition)
      prohibited-superior?))))

;;; 9. `superior-on-potential-superior-not-the-class-definition-type': there is a
;;;   potential superior whose direct-superior classes are not inheritable by
;;;   this definition.

(def-valid-superior-test superior-on-potential-superior-not-the-class-definition-type
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore possible-class-inheritance-path?))
  (loop with class-primary-foundation-class
      = (get-primary-foundation-class-for-definition definition)
    with superior-potential-definition? = nil
    for superior in direct-superior-classes?
    for prohibited-inheritance-class?
        = (loop for potential-superior-definition being each
            potential-superior-definition of superior
            for potential-definition-superiors?
            = (direct-superiors-of-defined-class
                potential-superior-definition)
            for prohibited-superior-class?
            = (and potential-definition-superiors?
                   (incorrect-foundation-class-for-this-definition-p
                 potential-definition-superiors?
                 class-primary-foundation-class nil))
            when prohibited-superior-class?
              do (setq superior-potential-definition?
                   potential-superior-definition)
             (return prohibited-superior-class?))
    when prohibited-inheritance-class?
      return (superior-on-potential-superior-not-the-class-definition-type
           prohibited-inheritance-class?
           class-primary-foundation-class
           superior-potential-definition?)))



;;; 10. `potential-definition-class-type-is-incompatible': there is a
;;;   potential-superior definition that is incompatible with this definition.
;;;   For example, an object-definition while this definition is a
;;;   connection-defintion.

(def-valid-superior-test potential-definition-class-type-is-incompatible 
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore possible-class-inheritance-path?))
  (loop with superior-potential-definition? = nil
    with specialized-definition-class
      = (get-specialized-definition-class definition)
    for superior in direct-superior-classes?
    for potential-superior-incompatible-definition-type?
        = (loop for potential-superior-definition being each
            potential-superior-definition of superior
            for potential-superior-specialized-definition
            = (get-specialized-definition-class
                potential-superior-definition)
            do
        (unless (or (definition-classes-are-compatible-p
                definition potential-superior-definition)
                (eq specialized-definition-class 'class-definition)
                (eq potential-superior-specialized-definition
                'class-definition))
          (setq superior-potential-definition? potential-superior-definition)
          (return potential-superior-specialized-definition)))
    when potential-superior-incompatible-definition-type?
      return (potential-definition-class-type-is-incompatible
           potential-superior-incompatible-definition-type?
           superior-potential-definition?
           'superior)))



;;; 11. `system-inheritance-change-for-instantiated-class': there is a system
;;;   inheritance change to an instantiated class: either a foundation class
;;;   change, the direct superiors reverting to none, no instantiable direct
;;;   superior class, or the specification of an undefined direct superior.

(def-valid-superior-test system-inheritance-change-for-instantiated-class
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore possible-class-inheritance-path?))
  (let* ((undefined-direct-superior?
       (loop for superior in direct-superior-classes?
         when (not (classp superior))
           return superior))
     (previous-direct-superiors?
       (direct-superiors-of-defined-class definition))
     (class-name? (name-of-defined-class definition))
     (previous-foundation-class? nil)
     (new-foundation-class? nil))
    (when (and (classp class-name?)
           (essentially-instantiated-class-p class-name?)
           (or undefined-direct-superior?
           (null direct-superior-classes?)
           (direct-superiors-preclude-instantiability-p
             direct-superior-classes?)
           (and (setq previous-foundation-class?
                  (most-refined-foundation-class-of-direct-superiors
                previous-direct-superiors?))
            (setq new-foundation-class?
                  (most-refined-foundation-class-of-direct-superiors
                direct-superior-classes?))
            (not (eq previous-foundation-class? new-foundation-class?)))))
      (cond
    (undefined-direct-superior?
     (system-inheritance-change-for-instantiated-class
       nil nil undefined-direct-superior? nil nil nil))
    ((null direct-superior-classes?)
     (system-inheritance-change-for-instantiated-class
       nil nil nil nil nil t))
    (previous-foundation-class?
     (system-inheritance-change-for-instantiated-class
       class-name? nil nil previous-foundation-class?
       new-foundation-class? nil))
    (t
     (system-inheritance-change-for-instantiated-class
       nil t nil nil nil nil))))))



;;; 12. `circularity-of-inheritance-in-the-class-hierarchy': there is inheritance
;;;   circularity in the class hierarchy.

(def-valid-superior-test circularity-of-inheritance-in-the-class-hierarchy
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore direct-superior-classes?))
  (loop with class-name? = (name-of-defined-class definition)
    for superior in (cdr possible-class-inheritance-path?)
    when (memq class-name? (direct-superior-classes superior))
      return (circularity-of-inheritance-in-the-class-hierarchy
           class-name? superior)))



;;; 13. `circularity-in-potential-definition-inheritance': there is a circularity
;;;   in inheritance for two potential definitions.  Two definitions have the
;;;   name of defined class of the other definition as a superior class.
    
(def-valid-superior-test circularity-in-potential-definition-inheritance
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore possible-class-inheritance-path?))
  (loop with class-name? = (name-of-defined-class definition)
    for potential-definition being each potential-definition of class-name?
    for potential-definition-name?
        = (name-of-defined-class potential-definition)
    when (and potential-definition-name?
          (memq potential-definition-name? direct-superior-classes?))
      return (circularity-in-potential-definition-inheritance
           potential-definition-name?)))



;;; 14. `subclass-appears-after-superior-in-direct-superior-classes': merging
;;;   paths rule 1 violation: a subclass appears after one of its superior
;;;   classes in the list of direct superiors.

(def-valid-superior-test subclass-appears-after-superior-in-direct-superior-classes 
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore definition possible-class-inheritance-path?))
  (loop for sublist on direct-superior-classes?
    for preceding-superior = (car sublist)
    as prohibited-superior?
       = (loop for superior in (cdr sublist)
           when (subclassp superior preceding-superior)
             return superior)
    when prohibited-superior?
      return (subclass-appears-after-superior-in-direct-superior-classes
           preceding-superior prohibited-superior?)))



;;; 15. `subclass-appears-after-superior-for-subclass-direct-superiors': merging
;;;   paths rule 1 violation for subclasses.

(def-valid-superior-test subclass-appears-after-superior-for-subclass-direct-superiors
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore direct-superior-classes?))
  (let* ((class-name? (name-of-defined-class definition))
     preceding-superior? following-superior? prohibited-superior?)
    (when (loop for subclass being each subclass of class-name?
        for subclass-direct-superiors = (direct-superior-classes subclass)
        thereis
        (loop for sublist on subclass-direct-superiors
              until (null (second sublist))
              for preceding-superior = (first sublist)
              for following-superior = (second sublist)
              for following-superior-inheritance-path =
              (if (eq following-superior class-name?)
              possible-class-inheritance-path?
              (class-inheritance-path
                (class-description following-superior)))
              thereis
              ;; If class A appears on the inheritance path of a class
              ;; that follows it, class A is a superior of the following
              ;; class.
              (and (memq preceding-superior
                 following-superior-inheritance-path)
               (setq preceding-superior? preceding-superior)
               (setq following-superior? following-superior)
               (setq prohibited-superior? subclass))))
      (subclass-appears-after-superior-for-subclass-direct-superiors
    preceding-superior? following-superior? prohibited-superior?))))



;;; 16. `subclass-appears-after-superior-for-potential-definition': merging paths
;;;   rule 1 violation for potential-inferior classes.

(def-valid-superior-test subclass-appears-after-superior-for-potential-definition
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore direct-superior-classes?))
  (let* ((class-name? (name-of-defined-class definition))
     preceding-superior? following-superior? prohibited-superior?)
    (when (loop for potential-definition
            being each potential-definition of class-name?
        for direct-superiors
            = (direct-superiors-of-defined-class potential-definition)
        thereis
        (loop for sublist on direct-superiors
              until (null (second sublist))
              for preceding-superior = (first sublist)
              for following-superior = (second sublist)
              for following-superior-inheritance-path? =
              (if (eq following-superior class-name?)
              possible-class-inheritance-path?
              (let ((class-description nil))
                (and (setq class-description
                       (class-description following-superior))
                 (class-inheritance-path class-description))))
              for preceding-superior-potential-definitions? =
              (loop for potential-definition being each
                potential-definition of preceding-superior
                collect potential-definition using frame-cons)
              thereis
              (and (or (and following-superior-inheritance-path?
                    (memq preceding-superior
                      following-superior-inheritance-path?))
                   (and preceding-superior-potential-definitions?
                    (prog1
                    (memq (class-definition following-superior)
                          preceding-superior-potential-definitions?)
                      (reclaim-frame-list
                    preceding-superior-potential-definitions?))))
               (setq preceding-superior? preceding-superior)
               (setq following-superior? following-superior)
               (setq prohibited-superior?
                 (name-of-defined-class potential-definition)))))
      (subclass-appears-after-superior-for-potential-definition
    preceding-superior? following-superior? prohibited-superior?))))



;;; 17. `subclass-appears-after-superior-for-potential-definition': the foundation
;;;   classes of two direct superiors do not have an inferior/superior
;;;   relationship (they are disjoint)

(def-valid-superior-test disjoint-foundation-classes
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore definition possible-class-inheritance-path?))
  (let (first-foundation-class? second-foundation-class?)
    (when (loop for sublist on direct-superior-classes?
        until (null (cdr sublist))
        for superior = (car sublist)
        for superior-foundation-class?
            = (when (classp superior)
            (get-foundation-class-for-class superior))
        thereis
        (and superior-foundation-class?
             (loop for other-superior in (cdr sublist)
               for other-superior-foundation-class? =
               (when (classp other-superior)
                 (get-foundation-class-for-class
                   other-superior))
               thereis
               (and other-superior-foundation-class?
                (not (subclassp
                       superior-foundation-class?
                       other-superior-foundation-class?))
                (not (subclassp
                       other-superior-foundation-class?
                       superior-foundation-class?))
                (setq first-foundation-class?
                      superior-foundation-class?)
                (setq second-foundation-class?
                      other-superior-foundation-class?)))))
      (disjoint-foundation-classes
    first-foundation-class? second-foundation-class?))))



;;; 18. `disjoint-foundation-classes-for-subclass-or-potential-definition': the
;;;   change in foundation class for class will give a subclass or potential
;;;   class disjoint foundation classes.

(def-valid-superior-test disjoint-foundation-classes-for-subclass-or-potential-definition
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore possible-class-inheritance-path?))
  (let* ((undefined-direct-superior?
       (loop for superior in direct-superior-classes?
         when (not (classp superior))
           return superior))
     (foundation-class?
       (unless undefined-direct-superior?
         (most-refined-foundation-class-of-direct-superiors
           direct-superior-classes?)))
     (class-name? (name-of-defined-class definition))
     (first-foundation-class? nil)
     (second-foundation-class? nil)
     (problem-inferior-class? nil))
  (when (and foundation-class?
         (or
           (loop for subclass being each subclass of class-name?
             for direct-superiors = (direct-superior-classes subclass)
             for class-inheritance-path = (class-inheritance-path
                            (class-description subclass))
             thereis
             (unless (or (eq subclass class-name?)
                 (null (cdr direct-superiors)))
               (loop for sublist on (cdr class-inheritance-path)
                 until (eq (second sublist) 'item)
                 for superior = (car sublist)
                 for superior-foundation-class? =
                 (if (eq superior class-name?)
                 foundation-class?
                 (get-foundation-class-for-class
                   superior))
                 thereis
                 (loop for other-superior in (cdr sublist)
                   for other-superior-foundation-class? =
                   (if (eq other-superior class-name?)
                       foundation-class?
                       (get-foundation-class-for-class
                     other-superior))
                   thereis
                   (and superior-foundation-class?
                    other-superior-foundation-class?
                    (not (subclassp
                           superior-foundation-class?
                           other-superior-foundation-class?))
                    (not (subclassp
                           other-superior-foundation-class?
                           superior-foundation-class?))
                    (setq first-foundation-class?
                          superior-foundation-class?)
                    (setq second-foundation-class?
                          other-superior-foundation-class?)
                    (setq problem-inferior-class? subclass))))))
           (loop for potential-definition being each potential-definition
             of class-name?
             for potential-direct-superiors = (direct-superiors-of-defined-class
                            potential-definition)
             thereis
             (when (cdr potential-direct-superiors)
               (loop for sublist on potential-direct-superiors
                 until (null (cdr sublist))
                 for superior = (car sublist)
                 for superior-foundation-class? =
                 (if (eq superior class-name?)
                 foundation-class?
                 (and (classp superior)
                      (get-foundation-class-for-class
                    superior)))
                 thereis
                 (loop for other-superior in (cdr sublist)
                   for other-superior-foundation-class? =
                   (if (eq other-superior class-name?)
                       foundation-class?
                       (and (classp other-superior)
                        (get-foundation-class-for-class
                          other-superior)))
                   thereis
                   (and superior-foundation-class?
                    other-superior-foundation-class?
                    (not (subclassp
                           superior-foundation-class?
                           other-superior-foundation-class?))
                    (not (subclassp
                           other-superior-foundation-class?
                           superior-foundation-class?))
                    (setq first-foundation-class?
                          superior-foundation-class?)
                    (setq second-foundation-class?
                          other-superior-foundation-class?))))))))
    (disjoint-foundation-classes-for-subclass-or-potential-definition
      first-foundation-class? second-foundation-class?
      problem-inferior-class?))))



;;; 19. `disjoint-superior-classes': The class inheritance path for the new class
;;;   will have disjoint classes (as detected by the disjoint-from class
;;;   feature)

(def-valid-superior-test disjoint-superior-classes
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore definition))
  (let* (preceding-superior?
      prohibited-superior?)
    (when (and possible-class-inheritance-path?
           (cdr direct-superior-classes?) ; more-than-one-direct-superior?
           (loop for superior in direct-superior-classes?
             for disjoint-from-feature?
             = (get-class-feature-if-any superior 'disjoint-from)
             thereis
             (and disjoint-from-feature?
              (loop for other-class in direct-superior-classes?
                thereis
                (loop for class in (cdr disjoint-from-feature?)
                      thereis
                      (and (subclassp other-class class)
                       (setq preceding-superior? superior)
                       (setq prohibited-superior? other-class)))))))
      (disjoint-superior-classes preceding-superior? prohibited-superior?))))



;;; 20. `disjoint-superior-classes-for-potential-definition': A potential inferior
;;;   class will have disjoint classes in its inheritance (as detected by the
;;;   disjoint-from class-feature)

(def-valid-superior-test disjoint-superior-classes-for-potential-definition
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore possible-class-inheritance-path?))
  (let* ((class-name? (name-of-defined-class definition))
     preceding-superior?
     prohibited-superior?
     potential-definition-class-name?)
    (when (loop for potential-inferior
            being each potential-definition of class-name?
        for direct-superiors
            = (direct-superiors-of-defined-class potential-inferior)
        thereis
        (and (cdr direct-superiors)
             (loop for superior in direct-superiors
               for disjoint-from-feature-class-list?
                   = (and (or (eq superior class-name?)
                      (classp superior))
                      (loop for superior1 in (if (eq superior class-name?)
                                 direct-superior-classes?
                                 (direct-superior-classes superior))
                        for disjoint-from-class-feature?
                        = (get-class-feature-if-any superior1 'disjoint-from)
                        when disjoint-from-class-feature?
                          return (progn (setq preceding-superior? superior)
                                (cdr disjoint-from-class-feature?))))
               thereis
               (and disjoint-from-feature-class-list?
                (loop for other-superior in direct-superiors
                      thereis
                      (and (or (eq other-superior class-name?)
                           (classp other-superior))
                       (not (eq preceding-superior? other-superior))
                       (loop for class in (if (eq other-superior class-name?)
                                  direct-superior-classes?
                                  (direct-superior-classes
                                    other-superior))
                         thereis
                         (loop for class1 in disjoint-from-feature-class-list?
                               when (subclassp class class1)
                             return (progn
                                  (setq potential-definition-class-name?
                                    (name-of-defined-class
                                      potential-inferior)) 
                                  (setq prohibited-superior?
                                    class))))))))))
      (disjoint-superior-classes-for-potential-definition
    potential-definition-class-name?
    preceding-superior? prohibited-superior?))))



;;; 21. `direct-superior-incompatible-with-foundation-class': a direct superior
;;;   class is not compatible with the potential foundation class (as detected
;;;   by the only-compatible-with class feature).

(def-valid-superior-test direct-superior-incompatible-with-foundation-class
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore definition possible-class-inheritance-path?))
  (let ((undefined-direct-superior?
      (loop for superior in direct-superior-classes?
        when (not (classp superior))
          return superior))
    compatible-class?
    prohibited-superior?
    new-foundation-class?)
    (when (and (not undefined-direct-superior?)
           (cdr direct-superior-classes?) ; more-than-one-direct-superior?
           (let ((most-refined-foundation-class
               (most-refined-foundation-class-of-direct-superiors
             direct-superior-classes?)))
         (loop for superior in direct-superior-classes?
               for only-compatible-with-feature? =
               (get-class-feature-if-any superior 'only-compatible-with)
               do
           (when (and only-compatible-with-feature?
                  (loop for compatible-class in
                    (cdr only-compatible-with-feature?)
                    when (subclassp
                       most-refined-foundation-class
                       compatible-class)
                      return nil
                    finally (return t)))
             (when (null (cdr (cdr only-compatible-with-feature?)))
               (setq compatible-class? (second only-compatible-with-feature?)))
             (setq prohibited-superior? superior)
             (return (setq new-foundation-class? most-refined-foundation-class))))))
    (direct-superior-incompatible-with-foundation-class
      prohibited-superior? new-foundation-class? compatible-class?))))



;;; 22. `definition-has-irreconcilable-dependencies': the direct superiors will
;;;   render the kb unsavable because this definition, which defines a
;;;   class-definition subclass, and another definition which also does, are
;;;   mutually dependent on each other for their inheritance.

(def-valid-superior-test definition-has-irreconcilable-dependencies
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore possible-class-inheritance-path?))
  (let* ((undefined-direct-superior?
       (loop for superior in direct-superior-classes?
         when (not (classp superior))
           return superior))
     (interdependent-definition?
       (if (and (not undefined-direct-superior?)
            (name-of-defined-class definition)
            (loop for superior in direct-superior-classes?
              for superior-definition = (class-definition superior)
              thereis
              (and (subclassp superior 'class-definition)
                   (framep superior-definition))))     
           (definition-is-not-savable-p definition direct-superior-classes?))))
    (if interdependent-definition?
    (definition-has-irreconcilable-dependencies interdependent-definition?))))

;; Note: this derives not the slot putter, in DEFINITIONS, but from the
;; compiler, in GRAMMAR6A. (MHD 10/26/01)



;;; 23. `invalidates-direct-superiors-for-potential-definition': the foundation
;;;   class for this class would invalidate the direct superiors of a potential
;;;   definition.

(def-valid-superior-test invalidates-direct-superiors-for-potential-definition
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (declare (ignore possible-class-inheritance-path?))
  (let* ((class-name? (name-of-defined-class definition))
     (undefined-direct-superior?
       (loop for superior in direct-superior-classes?
         when (not (classp superior))
           return superior))
     (foundation-class?
       (unless undefined-direct-superior?
         (most-refined-foundation-class-of-direct-superiors
           direct-superior-classes?)))
     first-foundation-class?
     second-foundation-class?
     potential-definition-class-name?)
    (when (loop for potential-definition
            being each potential-definition of class-name?
        for direct-superiors
            = (direct-superiors-of-defined-class potential-definition)
        thereis
        (and (cdr direct-superiors)
             (loop for sublist on direct-superiors
               until (null (cdr sublist))
               for superior = (car sublist)
               for superior-foundation-class?
                   = (or (and (eq superior class-name?)
                      foundation-class?)
                     (and (classp superior)
                      (get-foundation-class-for-class superior)))
               thereis
               (and superior-foundation-class?
                (loop for other-superior in (cdr sublist)
                      for other-superior-foundation-class?
                      = (or (and (eq other-superior class-name?)
                             foundation-class?)
                        (and (classp other-superior)
                             (get-foundation-class-for-class
                               other-superior)))
                      thereis
                      (and other-superior-foundation-class?
                       (not (subclassp
                          superior-foundation-class?
                          other-superior-foundation-class?))
                       (not (subclassp
                          other-superior-foundation-class?
                          superior-foundation-class?))
                       (progn
                         (setq potential-definition-class-name?
                           (name-of-defined-class potential-definition))
                         (setq first-foundation-class?
                           superior-foundation-class?)
                         (setq second-foundation-class?
                           other-superior-foundation-class?))))))))
      (invalidates-direct-superiors-for-potential-definition
    potential-definition-class-name?
    first-foundation-class? second-foundation-class?))))



;;; 24. `direct-superiors-give-ancestors-different-precedence':
;;;
;;;   Case 1: merging paths rule 2 violation: the inheritance paths of two
;;;   superior classes have classes in common but the common classes are given a
;;;   different precedence ordering;
;;;
;;;   Case 2: merging paths rule 2 violation for inferior or potential classes:
;;;   the inheritance paths of two superior classes have classes in common but
;;;   the common classes are given a different ordering.

(def-valid-superior-test direct-superiors-give-ancestors-different-precedence
    (direct-superior-classes? definition possible-class-inheritance-path?)
  (let* ((class-name? (name-of-defined-class definition))
     (undefined-direct-superior?
       (loop for superior in direct-superior-classes?
         when (not (classp superior))
           return superior))
     (prohibited-superior? nil)
     (colliding-superior? nil)
     (inferior-potential-definition? nil)
     (problem-inferior-class? nil))
    (when (or
        ;; Case 1:
        (and direct-superior-classes?
         (not undefined-direct-superior?)
         (let ((class-inheritance-paths-for-direct-superiors
             (loop for superior in direct-superior-classes?
                   collect (class-inheritance-path (class-description superior))
                 using frame-cons)))
           (multiple-value-setq (prohibited-superior? colliding-superior?)
             (merging-paths-common-ancestor-rule-2-violation-p
               class-inheritance-paths-for-direct-superiors))
           (reclaim-frame-list class-inheritance-paths-for-direct-superiors)
           prohibited-superior?))
        ;; Case 2:
        (and possible-class-inheritance-path?
         (or (loop for subclass
                   being each subclass of class-name?
               for subclass-direct-superiors
                   = (direct-superior-classes subclass)
               do
               (unless (or (eq subclass class-name?)
                   (null (cdr subclass-direct-superiors)))
             (let* ((class-inheritance-paths
                  (let ((paths nil))
                    (loop for superior in subclass-direct-superiors
                      do
                      (if (eq superior class-name?)
                      (setq paths
                        (nconc paths
                               (frame-list
                             possible-class-inheritance-path?)))
                      (setq paths
                        (nconc paths
                               (frame-list
                             (class-inheritance-path
                               (class-description
                                 superior)))))))
                    paths)))
               (multiple-value-setq (prohibited-superior? colliding-superior?)
                 (merging-paths-common-ancestor-rule-2-violation-p
                   class-inheritance-paths))
               (reclaim-frame-list class-inheritance-paths)
               (return prohibited-superior?))))
             (multiple-value-setq (inferior-potential-definition?
                        prohibited-superior? colliding-superior?)
               (rule-2-violation-for-potential-definitions
             class-name? possible-class-inheritance-path?))
             inferior-potential-definition?)))
      (direct-superiors-give-ancestors-different-precedence
    prohibited-superior? colliding-superior?
    problem-inferior-class?
    inferior-potential-definition?))))


;;; For now this is an uncapped system procedure.  It is called by
;;; g2-get-all-reserved-system-attribute-names in sys-mod.kb. - jpg 8/2/06

(defun-for-system-procedure system-class-is-not-user-extensible (class)
  (let ((truep 
      (and (system-defined-class-p class)
           (not (get-class-feature-if-any class 'foundation-class)))))
    (make-evaluation-truth-value (if truep truth falsity))))



;;;; Changing the superior of a class

;;; 1. May not change if new superior is presently an inferior at any level
;;;    of the class.

;;; 2. When there are instances: 
;;;    2a: May not change to something which is not a class. If you want to do this,
;;;        first explicitly delete all instances.
;;;    2b: May not change if the effect would be do add or remove any "foundation class"
;;;        from the inheritance. The `foundation classes' are: object, sensor,
;;;        quantitative variable, logical variable, symbolic variable or text variable.

;;; 3. The instances of the class and all subclasses are hidden by transferring the instances
;;;    lists from instances-specific-to-this-class to
;;;    temporary-class-instance-list.

;;; 4. All changes are then made to the definitions and the descriptions of all
;;;    affected classes. Note that the set of subclasses does not change.

;; Note that as of version 4.0, the change feature "merge all instances and
;; subclasses into definition" is no longer restricted from being done while G2
;; is running or paused.  If a runtime change is made that affect other parts of
;; the KB, these parts are validated and will no longer refer to invalid items.
;; - cpm, 3/15/94

(def-slot-putter change (definition new-value)
  ;; Deferral of analysis is needed particularly by the cached-attribute
  ;; free-reference.  It is done for efficiency reasons and, also, so that
  ;; changes to definitions are completed before the analysis is done.
  (defer-some-consistency-analysis
      (let* ((type-of-change (first new-value))
         (arguments-of-change (rest new-value))
         (user-class (name-of-defined-class definition))
         (class-is-defined? (classp user-class))
         (any-class-instances? nil)
         ;; Validation may be required when there is an attribute change or
         ;; deletion, such that an attribute frame may have been deleted or
         ;; is now defined to be of another class.
         (change-requires-kb-validation? nil)
         (possible-class-hierarchy-change? nil))

    ;; Test for instances before any definition changes are made.
    (when class-is-defined?
      (loop for thing being each class-instance of user-class
        do
        (setq any-class-instances? t)
        until any-class-instances?))
    (case type-of-change
      (move-attribute
       (let* ((attribute-name (second new-value))
          (target-class (third new-value))
          (user-class-class-specific-attributes
            (class-specific-attributes definition))
          (attribute-description
            (copy-for-slot-value
              (car (member attribute-name
                   user-class-class-specific-attributes
                   :test 'car-eq))))
          (new-user-class-class-specific-attributes
            (loop for attribute-description in
                    user-class-class-specific-attributes
              when (not (eq (attribute-name attribute-description)
                    attribute-name))
                collect (copy-for-slot-value attribute-description)
                using slot-value-cons))
          (target-class-definition (class-definition target-class))
          (new-target-class-class-specific-attributes
            (nconc
              (copy-for-slot-value
            (class-specific-attributes target-class-definition))
              (slot-value-list attribute-description)))
          (class-level-affected
            (if (subclassp user-class target-class)
            user-class
            target-class))
          (list-of-non-default-instance-values
            (loop with list-to-return = nil
              for class being each subclass of class-level-affected
              do
              (when (instantiated-class-p class)
            (let* ((slot-description
                 (get-slot-description
                   attribute-name
                   (slot-descriptions (class-description class))
                   user-class))
                   (slot-init-form
                 (slot-init-form slot-description)))
              (loop for instance being each strict-class-instance of class
                for slot-value = (get-slot-description-value
                           instance slot-description)
                do
                (unless (eq slot-value slot-init-form)
                  (setq list-to-return
                    (frame-cons
                      (frame-cons instance slot-value)
                      list-to-return))
                  (set-slot-description-value-without-noting
                instance slot-description nil)))))
                  finally (return list-to-return))))
         ;; If necessary, prepare the indexed-attributes related slots on the source and target
         (let ((indexed-attributes-for-definition
             (indexed-attributes-for-definition definition)))
           (when (memq attribute-name indexed-attributes-for-definition)
         (prepare-for-indexed-attributes-moveage
           definition
           indexed-attributes-for-definition
           (loop for indexed-attr-name in indexed-attributes-for-definition
             unless (eq indexed-attr-name attribute-name)
               collect indexed-attr-name using slot-value-cons))
         (let ((indexed-attributes-for-target-definition
             (indexed-attributes-for-definition target-class-definition)))
           (prepare-for-indexed-attributes-moveage
             target-class-definition
             indexed-attributes-for-target-definition
             (slot-value-cons attribute-name
                      (copy-list-using-slot-value-conses
                    indexed-attributes-for-target-definition))))))
         ;; Remove the attribute from user-class.
         (change-slot-value
           definition 'class-specific-attributes
           new-user-class-class-specific-attributes)
         ;; Add the attribute to the target-class.
         (change-slot-value
           target-class-definition 'class-specific-attributes
           new-target-class-class-specific-attributes)
         ;; Put the non-default values in the instances.
         ;;
         ;; NOTE: The following potentially updates table representations
         ;; twice.  This is wasteful, and should be investigated at a later
         ;; time! I am not sure from looking at the code if the full table
         ;; update is necessary due to changes above.  If it is, then at
         ;; least the table-update part of the change-slot-value should be
         ;; eliminated for efficiency.  (MHD 6/8/00)
         (loop for (instance . slot-value) in list-of-non-default-instance-values
           do (change-slot-value instance attribute-name slot-value target-class)
           collect instance into instances using frame-cons
           finally 
             (update-attribute-tables-for-instances instances nil)
             (reclaim-frame-list instances))
         (reclaim-frame-list list-of-non-default-instance-values)))
      
      (rename-attribute
       (let* ((old-attribute-name (first arguments-of-change))
          (new-attribute-name (second arguments-of-change))
          (attribute-descriptions
            (class-specific-attributes definition))
          (attribute-description?
            (get-attribute-description 
              old-attribute-name attribute-descriptions))
          (attribute-description-for-new-name?
            (get-attribute-description
              new-attribute-name attribute-descriptions)))

         (cond (attribute-description-for-new-name?
            (notify-engineer
              "The attribute ~A cannot be renamed to ~A because there ~
                       already is an attribute with that name."
              old-attribute-name new-attribute-name))

           ((reserved-system-slot-name-p definition new-attribute-name)
            (notify-engineer
              "The attribute ~A cannot be renamed to ~A because ~A ~
                       is the name of a G2 system attribute."
              old-attribute-name new-attribute-name new-attribute-name))
         
           (attribute-description?

            (let ((attribute-range
                (attribute-range attribute-description?)))
              (when class-is-defined?
            ;; Declare and undeclare implied attributes.
            (undeclare-implied-attribute
              user-class old-attribute-name attribute-range nil)
            (declare-implied-attribute
              user-class new-attribute-name attribute-range nil))

              (add-class-qualifier-to-parent-attribute-names-if-necessary
            user-class new-attribute-name)
              
              ;; Change the attribute name.
              (rename-attribute
            definition user-class old-attribute-name new-attribute-name)

              (remove-class-qualifier-from-parent-attribute-names-if-necessary
            user-class old-attribute-name)
              
              (update-representations-of-slot-value
            definition 'class-specific-attributes)
              (determine-possible-parent-attribute-name-changes
            user-class new-attribute-name)
              (update-inherited-attributes-slot-of-tree user-class)))

           (t 
            (notify-engineer
              "Because the class ~A does not have a class-specific ~A attribute, ~
                       the rename change to ~A cannot be implemented."
              (name-of-defined-class definition)
              old-attribute-name new-attribute-name)))))
         
      ;; What is intended here is that the superior icon description is copied
      ;; into the class level icon description as if the user had typed that
      ;; value at the class level.  Consequently, the class-level slot
      ;; description will not be EQ to the superior icon slot description.
      (copy-inherited-icon-description
       (when class-is-defined?
         (let* ((user-class-inheritance-path
              (class-inheritance-path (class-description user-class)))
            (object-level-icon-slot-description
              (get-slot-description-of-class-description
            'icon-description (class-description 'object)))
            (superior-that-bestowed-icon-description-on-user-class
              (most-specific-superior-that-refines-slot
            user-class-inheritance-path
            object-level-icon-slot-description))
            (superior-icon-description
              (slot-init-form
            (get-slot-description
              'icon-description
              (slot-descriptions
                (class-description
                superior-that-bestowed-icon-description-on-user-class)))))
            (superior-stubs-feature
              (get-inherited-stubs-class-feature-for-class
            user-class-inheritance-path)))
           (change-slot-value
         definition 'icon-description-for-class?
         (nconc
           (slot-value-list
             (copy-for-slot-value (width-of-icon superior-icon-description))
             (copy-for-slot-value (height-of-icon superior-icon-description)))
           (copy-for-slot-value (icon-line-drawing-description
                      superior-icon-description))))
           (let ((new-value-for-stubs
               (cond ((null superior-stubs-feature)
                  nil)
                 ((eq (cdr superior-stubs-feature) 'none)
                  'none)
                 (t (copy-for-slot-value superior-stubs-feature)))))
         (change-stub-specifications-for-class
           definition new-value-for-stubs)))))

      ((change-instance-values
         change-instance-values-preserving-non-default-values-in-some-cases)
       (let* ((class (name-of-defined-class definition))
          (slot-name-or-alias (second new-value))
          (pretty-slot-name
            (unalias-slot-name-if-necessary slot-name-or-alias class))
          (slot-description?
            (get-slot-description-of-class-description 
              pretty-slot-name (class-description class))))
         (cond
           ((null slot-description?)
        (notify-engineer
          "There is no ~A attribute for the class ~A."
          pretty-slot-name class))
           ((and
          (not (attribute-p pretty-slot-name))
          (not (semi-open-category-p
             slot-name-or-alias 'defaulted-attribute-name)))
        (notify-engineer
          "You may not initialize ~a, which is not a user defined attribute or an ~
                   attribute controlled by the default settings of the definition."
          slot-name-or-alias))
           (t
        (revert-instances-governed-by-slot-description-to-default-value
          class slot-description?
          (not (eq type-of-change 'change-instance-values)))

        ;; Update any indexed-attribute information.  Indexed-
        ;; attributes hash parent-objects based on the attribute
        ;; value.
        (update-indexed-attribute-properties definition nil nil nil)

        ;; Need to validate other parts of the KB because this change
        ;; could have caused some frames contained in attributes to be
        ;; deleted.  I assume that changing to a default value cannot
        ;; cause the class hiearchy of an existing attribute object to
        ;; change.
        (when any-class-instances?
          (setq change-requires-kb-validation? t))))))
      
      ;; It is now possible to merge a class defined with an object/message/
      ;; connection definition into a class defined with a class-definition.
      ;; (ghw 11/14/96).
      (merge-definitions
       (let ((class-to-merge-to (first arguments-of-change)))
         
         (if (or (system-defined-class-p class-to-merge-to)
             (not (classp class-to-merge-to)))
         
         (notify-engineer
           "Class ~a cannot be merged into class ~a because ~a ~
                   is not a user-defined class."
           user-class class-to-merge-to class-to-merge-to)
         
         (let* ((definition-to-merge-to?
                (class-definition class-to-merge-to))
            (compatible-definitions?
              (definition-classes-are-compatible-p
                  definition definition-to-merge-to?))
            (unacceptable-class-inheritance?
              ;; This checks whether the new direct-superiors
              ;; pass the compiler for that slot.
              (not (inheritance-for-merge-is-acceptable-p
                 definition definition-to-merge-to?)))
            (slot-values-that-differ? nil)
            (subworkspaces? (subworkspaces definition)))

           (cond
             ((eq user-class class-to-merge-to)
              (notify-engineer
            "A class cannot be merged into itself."))
             ((and
            (definition-class-is-subclass-of-obj-conn-mess-definition-p
                definition-to-merge-to?)
            (not (definition-class-is-subclass-of-obj-conn-mess-definition-p
                 definition)))
              (notify-engineer
            "Class ~a cannot be merged into class ~a because a ~
                         class-definition cannot be merged into an object-definition ~
                         or a connection-definition or a message-definition."
            user-class class-to-merge-to))
             (unacceptable-class-inheritance?
              (notify-engineer
            "Class ~a cannot be merged into class ~a because the ~
                         direct superior classes of ~a cannot be inherited by ~
                         ~a."
             user-class class-to-merge-to class-to-merge-to user-class))
             ((and (not (instantiated-class-or-connection-class-p user-class))
               (null (inferior-classes user-class)))
              (notify-engineer
            "~A has no instances or subclasses to merge." user-class))
             ((and compatible-definitions?
               (setq slot-values-that-differ?
                 (find-differences-in-frames-if-any
                   definition definition-to-merge-to? nil t)))
              (let ((alias-of-first-slot-difference
                  (alias-slot-name-if-necessary
                (car-of-cons slot-values-that-differ?) definition)))
            (prog1 (notify-engineer
                 "Class ~a cannot be merged into class ~a because ~
                                  the ~a attribute in ~a is not equivalent to the ~
                                  ~a attribute in ~a."
                 user-class class-to-merge-to
                 alias-of-first-slot-difference user-class
                 alias-of-first-slot-difference class-to-merge-to)
              (reclaim-slot-value-list slot-values-that-differ?))))
             (t
              (notify-engineer
            "Starting to merge the class ~a into ~a."
            user-class class-to-merge-to)

              (let ((old-indexed-attributes-for-definition?
                  ;; Reclaimed below.
                  (copy-list-using-gensym-conses
                (indexed-attributes-for-definition definition)))
                (old-indexed-attributes-for-definition-to-merge-to?
                  ;; Reclaimed below.
                  (copy-list-using-gensym-conses
                (indexed-attributes-for-definition
                  definition-to-merge-to?))))
            (cond
              ((and
                 (definition-class-is-subclass-of-obj-conn-mess-definition-p
                 definition)
                 (not (definition-class-is-subclass-of-obj-conn-mess-definition-p
                      definition-to-merge-to?)))
               (let ((interim-class-definition (make-frame 'class-definition)))
                 (transfer-values-to-interim-class-definition-for-merge
                   interim-class-definition definition)
                 (let* ((denotations-of-differing-slots?
                      (find-differences-in-frames-if-any
                    definition-to-merge-to? interim-class-definition
                    nil t))
                    (preserved-non-default-values?
                      (and denotations-of-differing-slots?
                       (memq 'class-specific-attributes
                          denotations-of-differing-slots?)
                       (memq 'direct-superiors-of-defined-class
                          denotations-of-differing-slots?)
                       (get-slot-values-to-save-for-conflict-resolution
                         definition definition-to-merge-to?))))
                   (when denotations-of-differing-slots?
                 (merge-differing-slots-in-definitions
                   definition-to-merge-to? interim-class-definition
                   denotations-of-differing-slots?)
                 #+development
                 (when (find-differences-in-frames-if-any
                     definition-to-merge-to? interim-class-definition t t)
                   (cerror
                     "DEFINITIONS"
                     "change attribute merging problem: tell ghw.")))
                   (combine-class-definitions
                 definition-to-merge-to? interim-class-definition)
                   (delete-frame interim-class-definition)
                   (change-slot-value definition 'name-of-defined-class nil)
                   (change-slot-value
                 definition 'name-of-defined-class user-class)
                   (when preserved-non-default-values?
                 (reinstate-non-default-values-after-merge
                   preserved-non-default-values?)))))
              (t
               (combine-class-definitions
                 definition-to-merge-to? definition))) 

            ;; Remove any relation-instances that now violate the class
            ;; types on the relation instance.  For subclasses this task
            ;; is done by alter-inheritance-of-class-without-changing-
            ;; foundation-class.
            (unless currently-automatically-resolving-class-name-conflicts?
              (loop for instance being each
                strict-class-instance of class-to-merge-to
                do
                (when (block-relation-instances-violate-class-type-p instance)
                  (remove-invalid-relation-instances instance))))

            ;; Remove any indexed-attribute information for the class
            ;; being merged.
            (remove-indexed-attribute-properties
              old-indexed-attributes-for-definition? user-class nil
              (if (or loading-kb-p
                  currently-automatically-resolving-class-name-conflicts?)
                  nil
                  (instantiated-class-p user-class)))
            ;; Update any indexed-attribute information for the class
            ;; being merged into.  Indexed-attributes hash parent-objects
            ;; based on the attribute value.  Need to remove old
            ;; indexed-attribute information, in case the merge caused
            ;; some attributes to be newly indexed or non-indexed.
            (update-indexed-attribute-properties
              definition-to-merge-to? t
              old-indexed-attributes-for-definition-to-merge-to? nil)
            (when old-indexed-attributes-for-definition?
              (reclaim-gensym-list
                old-indexed-attributes-for-definition?))
            (when old-indexed-attributes-for-definition-to-merge-to?
              (reclaim-gensym-list
                old-indexed-attributes-for-definition-to-merge-to?)))
              (notify-user
            (if currently-automatically-resolving-class-name-conflicts?
                "The definition of ~a has been ~amerged into the definition ~
                       of ~a.  The definition of ~a is being deleted~a"
                "The definition of ~a has been ~amerged into the definition ~
                       of ~a. You may wish to delete the definition of ~a~a")
            user-class
            (if currently-automatically-resolving-class-name-conflicts?
                "automatically "
                "")
            class-to-merge-to
            user-class
            (if subworkspaces?
                (if currently-automatically-resolving-class-name-conflicts?
                "; note that it contained a subworkspace."
                ", but note that it has a subworkspace.")
                "."))))))))
      
      (add-stub
       (add-stub-to-definitions-and-instances
         definition (copy-for-slot-value (car arguments-of-change))))
      (delete-stub
       (delete-stub-from-definitions-and-instances
         definition (car arguments-of-change))
       ;; When not reset, validate items that contain runtime data and that
       ;; can be affected by this change.  Validate those parts of the KB
       ;; and G2 that may refer to deleted connections.
       (when any-class-instances?
         (setq change-requires-kb-validation? t)))
      (move-stub
       (move-stub-in-definitions-and-instances
         definition (first arguments-of-change) (cdr arguments-of-change)))
      (change-portname
       (change-portname-in-definitions-and-instances
         definition (first arguments-of-change)
         (second arguments-of-change)))
      (change-direction
       (let ((direction? (second arguments-of-change)))
         (when (eq direction? 'none)
           (setq direction? nil))
         (change-direction-in-definitions-and-instances
           definition (first arguments-of-change) direction?)))
      (change-connection-class
       (change-connection-class-in-definitions-and-instances
         definition
         (first arguments-of-change)
         (second arguments-of-change))
       ;; When not reset, validate items that contain runtime data and that
       ;; can be affected by this change.  Validate those parts of the KB
       ;; and G2 that may refer to connections and expect them to be of the
       ;; old class.
       (when any-class-instances?
         (setq change-requires-kb-validation? t)
         (setq possible-class-hierarchy-change? t)))

      (update-definition-attribute
       (case (first arguments-of-change)
         (stubs)            ; deferred (for object definitions)
         (stub-length)      ; deferred (for connection definitions)
         (attribute-displays
          (let ((class? (name-of-defined-class definition)))
        (when (and (classp class?) ; a defined class
               (subclassp class? 'object))  ; only entities have attr. displays
          (loop for subclass being each subclass of class?
            for attribute-displays-spec? =
                  (cdr (get-class-feature-if-any
                     subclass 'attribute-displays))
            do
            (loop for instance being each strict-class-instance of subclass
              do
              (delete-all-attribute-displays instance))
            (when attribute-displays-spec?
              (unless (eq attribute-displays-spec? 'none)
            (loop for instance being each strict-class-instance of subclass
                  do
              (make-attribute-displays-per-specs
                instance attribute-displays-spec?))))))))
         (default-message-properties
         (update-default-message-properties-governed-by-this-definition
           definition))))

      (t nil))


    (when change-requires-kb-validation?
      ;; Validate other parts of the KB affected by this change, if
      ;; necessary.
      (validate-kb-after-runtime-definition-change
        (name-of-defined-class definition)
        nil
        possible-class-hierarchy-change?))

    ;; the value is always nil. The top level structure of the argument
    ;; is never used. Possibly more of the structure of new-value shouls be
    ;; reclaimed then we are doing here.
    (reclaim-slot-value new-value)

    nil)))

;;; Review the change-instance-values and change-instance-values-preserving-non-
;;; default-values-in-some-cases operations above in regard to changes required
;;; for KB validation.  Are there cases were changing instances values
;;; (changing to the default values) will not affect objects contained in
;;; attributes?  In these cases, the KB validation for runtime changes can be
;;; ommitted.  - cpm, 7/22/94



(defun update-default-message-properties-governed-by-this-definition
    (class-definition)
  (let ((class? (name-of-defined-class class-definition)))
    (when (and class? (classp class?) (subclassp class? 'message))
      (loop for subclass being each subclass of class?      
        do (update-default-message-properties-if-inherited-in-instances
         class? subclass)))))




;;; `Revert-instances-governed-by-slot-description-to-default-value' changes
;;; the slot value of the named slot of all instances to the default value for
;;; their class.

(defun revert-instances-governed-by-slot-description-to-default-value
    (user-class user-class-slot-description 
        &optional preserving-non-default-values-in-some-cases?)
  (loop with pretty-slot-name = (pretty-slot-name user-class-slot-description)
    with defining-class = (defining-class user-class-slot-description)
    for class being each subclass of user-class
    for class-level-slot-description =
          (if (eq class user-class)
          user-class-slot-description
          (get-slot-description
            pretty-slot-name
            (slot-descriptions (class-description class))
            defining-class))
    do
    (loop for instance being each strict-class-instance of class
      do
      (revert-instance-to-default-value
    instance class-level-slot-description
    preserving-non-default-values-in-some-cases?))))
    


      
;; Previously, this function assumed that the slot was a lookup-slot, and that
;; there was a pair to be removed from the lookup-structure.  Modified on 5/9/90
;; to make no assumption.  For example, the slot could very well be a vector
;; slot such as validity-interval.  Two #+development cerrors were removed.  ML.

(defun revert-instance-to-default-value
       (instance slot-description
    &optional preserving-non-default-values-in-some-cases?)
  (let ((pretty-slot-name (pretty-slot-name slot-description))
    (slot-init-form (slot-init-form slot-description))
    (defining-class (defining-class slot-description)))
    (cond
      ((slot-init-form-needs-evaluation? slot-init-form)
       (let* ((old-value-possibly-as-slot-constant  ; messy!
        (get-slot-description-value instance slot-description))
          (old-value
        (if (slot-constantp old-value-possibly-as-slot-constant)
            (get-slot-value-number-or-string-from-slot-constant
              old-value-possibly-as-slot-constant)
            old-value-possibly-as-slot-constant)))
     (cond
       ((and (consp slot-init-form)
         (eq (second slot-init-form) 'instantiate-variable)
         (symbolp (third slot-init-form))
         (framep old-value)
         (eq (class old-value) (third slot-init-form))))
        ;; If the slot spec says "a FOO" and the existing instance is
        ;; (strictly) "a FOO", then leave the instance.  In 2.1 & earlier
        ;; versions of G2, it would reinstantiate the instance, but we
        ;; now wish to regard that behavior as a bug.  I believe that
        ;; users either do not care about or do not want the old
        ;; functionality.
       (t
        (let* ((new-value
             (let ((frame-being-made instance))
               (eval-slot-init-form slot-init-form)))
           (initial-value-of-variable-or-parameter?
             (when (and preserving-non-default-values-in-some-cases?
                (not (framep old-value))
                (framep new-value)
                
                ;; Note that units of measure may be entered but
                ;;   are discarded for variable/parameter initial
                ;;   values, and so may be discarded.
                
                (frame-class-case new-value
                  ((logical-parameter logical-variable)
                   (and (slot-value-number-p old-value)
                    (integerp (slot-value-number-value old-value))
                    (if (slot-constantp old-value-possibly-as-slot-constant)
                        (eq (get-unit-from-slot-constant
                          old-value-possibly-as-slot-constant)
                        'truth-value))))
                  ((integer-parameter integer-variable)
                   (and (slot-value-number-p old-value)
                    (or (and (integerp (slot-value-number-value old-value))
                         (not (if (slot-constantp old-value-possibly-as-slot-constant)
                              (eq (get-unit-from-slot-constant
                                old-value-possibly-as-slot-constant)
                                  'truth-value))))
                        (with-temporary-gensym-float-creation
                        revert-instance-to-default-value-1
                          (multiple-value-bind (nearest-integer remainder)
                          (round (slot-value-number-value old-value))
                        ;; NEED RECLAMATION LOGIC HERE???!!
                        ;; It's an issue whether this is a
                        ;;   good restriction/heuristic; i.e., should
                        ;;   we instead always use the nearest integer?
                        ;;   This way:
                        ;;      6.0 => 6
                        ;;   i.e., because zero remains after rounding,
                        ;;   but
                        ;;      6.1, "foo", BAR, or .1 true
                        ;;      => 0
                        ;;   i.e., because these cannot be rounded (with
                        ;;   zero remaining), and 0 because its the
                        ;;   default initial value.
                        (when (= remainder 0.0)
                          (setq old-value nearest-integer)
                          t))))))
                  ((quantitative-parameter quantitative-variable)
                   ;; Assuming that quantitative-parameter/variable prefer
                   ;; floats, i.e., 0.0, as their defaults.
                   (and (slot-value-number-p old-value)
                    (or (slot-value-float-p old-value)
                        ;; NEED RECLAMATION LOGIC HERE???!!
                        (with-temporary-gensym-float-creation
                        revert-instance-to-default-value-2
                          (setq old-value
                            (make-slot-value-float
                              (coerce-to-gensym-float old-value)))
                          t))))
                  ((symbolic-parameter symbolic-variable)
                   (symbolp old-value))
                  ((text-parameter text-variable)
                   (text-string-p old-value))))
               (copy-for-slot-value old-value))))
          (change-slot-value instance pretty-slot-name new-value defining-class)
          (when initial-value-of-variable-or-parameter?
        (change-slot-value
          new-value 'initial-value-of-variable-or-parameter
          initial-value-of-variable-or-parameter?)))))))
      (t (let* ((old-value
          (get-slot-description-value instance slot-description))
        (substitute-for-slot-init-form-from-initial-value?
          (when (and preserving-non-default-values-in-some-cases?
                 (framep old-value)
                 (frame-of-class-p old-value 'variable-or-parameter))
            (let* ((initial-value-of-variable-or-parameter?
                 (get-slot-value
                   old-value
                   'initial-value-of-variable-or-parameter))
               (default-initial-value-of-variable-or-parameter?
                   (get-slot-init-form
                 (class old-value)
                 'initial-value-of-variable-or-parameter)))
              (if (and initial-value-of-variable-or-parameter?
                   (not (slot-value-equal-p
                      initial-value-of-variable-or-parameter?
                      default-initial-value-of-variable-or-parameter?)))
              (if (or (slot-value-number-p initial-value-of-variable-or-parameter?)
                  (text-string-p initial-value-of-variable-or-parameter?))
                  ;; REVIEW RECYCLING ISSUES!!
                  (make-slot-constant
                (copy-for-slot-value initial-value-of-variable-or-parameter?)
                (if (slot-value-number-p initial-value-of-variable-or-parameter?)
                    (frame-class-case old-value
                      ((logical-variable logical-parameter)
                       'truth-value)
                      (t
                    'number))
                    'text)
                nil)
                  initial-value-of-variable-or-parameter?))))))
       (change-slot-value
         instance pretty-slot-name
         (or substitute-for-slot-init-form-from-initial-value?
         slot-init-form) defining-class))))))






;;;; Changes to Stubs


;;; The grammar for stub changes is specified with the grammar category
;;; stub-change which is a sub-category of object-change.  

;;; The following functions are handlers for the change options and are called
;;; by the slot putter for the change slot.  All these handlers, except the one
;;; for adding a stub, call get-stub-info-or-warn-if-none to get the stub
;;; information in the definition corresponding to the stub specification.  If
;;; one is found, the change is made in the stub info and change-slot-value is
;;; called with the new value being a copy of the old value with the change.
;;; Then, propagate-stub-change-to-strict-class-instances is called to perform
;;; the change to all strict class instances of the class defined by the
;;; definition.  Finally, propagate-stub-change-to-instances-of-sub-classes is
;;; called to make the change in all definitions for subclasses for which the
;;; stubs slot is inherited, and in instances of classes defined by such
;;; definitions.  The handler for an add change is the same as the others except
;;; that it makes a new stub information list rather than calling
;;; get-stub-info-or-warn-if-none.

;;; A warning is posted if the stub designation does not designate a stub in the
;;; definition (if get-stub-info-or-warn-if-none fails).  However, no warning is
;;; posted if the stub designation does not designate a stub in an instance
;;; while propagating to instances.  A warning is posted if a change is
;;; attempted in a definition where the stubs are inherited.  It is necessary to
;;; copy the stub spec so that it is not inherited, before a change can be made.
;;; This is in keeping with similar restrictions on inheritance of icon
;;; descriptions.

;;; The basic test for stub changes is to make at least three class definitions
;;; that define a path in the class hierarchy.  Have the stubs for the two
;;; inferior classes inherit from the superior class.  Make changes in the
;;; change slot of the most superior class and note changes in the stubs slot
;;; and in instances.



(defmacro with-non-inherited-old-stub-spec (definition &body body)
  `(let* ((class (name-of-defined-class ,definition))
      (old-value (class-slot-description-value 'stubs-for-class class)))
     (if old-value
     ,@body
     (warn-of-attempt-to-change-inherited-stubs-of-class definition class))))

(defun warn-of-attempt-to-change-inherited-stubs-of-class (definition class)
  ;; This is just a subfunction of the above macro.
  (if (frame-of-class-p definition 'object-definition)
      (write-warning-message* 1
    (tformat
      "Attempting to change the inherited stubs of class ~A.  ~
           Stubs that are inherited cannot be changed.  ~
           Copying the inherited stubs with the change attribute ~
           will also copy its accompanying stubs if there are any. ~
           Stubs can be added to this class by editing the stubs ~
           attribute on this definition." class))
      (write-warning-message* 1
    (tformat
      "Attempting to change the inherited stubs of class ~A.  ~
           Stubs that are inherited cannot be changed.  ~
           Copying the inherited stubs with the change attribute ~
           will also copy its accompanying stubs if there are any. ~
           Stubs can be added to this class by editing the ~
           attribute-initializations attribute on this definition." class))))




;;; The function `change-stub-specifications-for-class' is called when the
;;; change attribute is edited to add a stub, delete a stub, change the
;;; portname of a stub, move a stub, change the connection class of a stub,
;;; and change the direction of a stub.  It is also called from the cleanup
;;; code for class-definition.  In the case of object-defintions, this function
;;; changes the value of the connections-for-class? attribute of the definition;
;;; otherwise it changes the value of the default-overrides for class-
;;; definitions.

(defun change-stub-specifications-for-class (definition new-value)
  (if (frame-of-class-p definition 'object-definition)
      (change-slot-value definition 'connections-for-class? new-value)
      ;; For class-definitions, we add the new-value to the default-overrides.
      (let* ((copied-default-overrides?
           (copy-for-slot-value (default-overrides definition)))
         (cons-holding-stubs-specification?
           (car (member
              'stubs-for-class copied-default-overrides? :test 'car-eq)))
         (new-value-for-default-overrides
           (if cons-holding-stubs-specification?
           (cond ((eq new-value 'none)
              (prog1 (setq copied-default-overrides?
                       (delete-slot-value-element
                     cons-holding-stubs-specification?
                     copied-default-overrides?))
                (reclaim-slot-value cons-holding-stubs-specification?)))
             (t
              (let ((copied-old-value
                  (cadr-of-cons cons-holding-stubs-specification?)))
                (setf (cadr-of-cons cons-holding-stubs-specification?)
                  new-value)
                (reclaim-slot-value copied-old-value)
                copied-default-overrides?)))
                   ;; There currently is no stubs specification.
           (unless (eq new-value 'none)
             (nconc copied-default-overrides?
                (slot-value-list
                  (slot-value-list 'stubs-for-class new-value)))))))
    (change-slot-value
      definition 'default-overrides new-value-for-default-overrides))))

          
  

(defun add-stub-to-definitions-and-instances (definition stub-info)
  (with-non-inherited-old-stub-spec 
    definition
    (cond
      ((subclassp (second stub-info) 'connection)
       (let ((new-value
           (cond 
         ((or (null old-value)
              (eq old-value 'none))
          (slot-value-cons 'stubs (slot-value-list stub-info)))
         (t
          (nconc
            (copy-for-slot-value old-value)
            (slot-value-list stub-info))))))
     (change-stub-specifications-for-class definition new-value)
     (propagate-stub-change-to-strict-class-instances
       class stub-info 'add-stub-to-object-and-draw nil)
     (propagate-stub-change-to-instances-of-subclasses 
       class stub-info 'add-stub-to-object-and-draw nil)))
      (t
       (write-warning-message* 1
     (tformat "Attempting to add a connection of class ~A, which is not a defined connection class."
          class))))))



(defun add-stub-to-object-and-draw (object stub-info change-arg)
  (declare (ignore change-arg))
  (when (and (null (parent-frame object))
         (null (parent-attribute-name object)))
    (let ((new-stub? (add-stub-given-spec object stub-info)))
      (when new-stub?
    (update-connection-images nil (superblock? object) new-stub?)))))



(defun delete-stub-from-definitions-and-instances (definition stub-designation)
  (with-non-inherited-old-stub-spec 
    definition
    (let ((stub-info-to-be-deleted?
        (get-stub-info-or-warn-if-none 
          old-value stub-designation definition))
      new-value)
      (when stub-info-to-be-deleted?
    (setq new-value
          (loop for stub-info in (cdr old-value)
            nconc (when (not (eq stub-info stub-info-to-be-deleted?))
                (slot-value-list
                  (copy-for-slot-value stub-info)))))
    (setq new-value
          (if new-value 
          (slot-value-cons 'stubs new-value)
          'none))
    (change-stub-specifications-for-class definition new-value)
    (propagate-stub-change-to-strict-class-instances 
      class stub-designation 'delete-stub-given-stub-designation nil)
    (propagate-stub-change-to-instances-of-subclasses
      class stub-designation 'delete-stub-given-stub-designation nil)))))


(defun delete-stub-given-stub-designation (object stub-designation change-arg)
  (declare (ignore change-arg))
  (when (get-workspace-if-any-macro object)
    (let ((designated-connection?
        (get-connection-given-stub-designation object stub-designation)))
      (when designated-connection?
    (delete-connection-to-stub designated-connection?)
    (setq designated-connection?
          (get-connection-given-stub-designation object stub-designation))
    (when designated-connection?
      (delete-connection designated-connection?))))))

  ;; This is a bit inefficient in that it finds the connection twice, first to
;; delete it to a stub (so that other end is deleted to stub), then to delete it.
;; Consider improving by writing a delete function that deletes other end to stub
;; while deleting it completely in object.



(defun change-portname-in-definitions-and-instances
       (definition stub-designation portname)
  (with-non-inherited-old-stub-spec 
    definition
    (let ((stub-info-to-be-changed?
        (get-stub-info-or-warn-if-none
          old-value stub-designation definition)))
      (when (and stub-info-to-be-changed?
         (not (eq (first stub-info-to-be-changed?) portname)))
    (setf (first stub-info-to-be-changed?) portname)
    (change-stub-specifications-for-class
      definition (copy-for-slot-value old-value))
    (propagate-stub-change-to-strict-class-instances 
      class stub-designation 
      'change-portname-given-stub-designation portname)
    (propagate-stub-change-to-instances-of-subclasses
      class stub-designation 
      'change-portname-given-stub-designation portname)))))

(defun change-portname-given-stub-designation 
       (object stub-designation portname)
  (let ((designated-connection?
	 (get-connection-given-stub-designation object stub-designation)))
    (when designated-connection?
      #-connections-v2
      (let ((connections-sublist-for-connection
	     (get-connections-sublist-for-connection
	       object designated-connection?)))
	(if (symbolp (car connections-sublist-for-connection))  ; connection has a portname  
	    (setf (car connections-sublist-for-connection) portname)
	  (insert-portname-for-connection 
	    object designated-connection? portname)))
      #+connections-v2
      (when-let* ((connections (connections object))
		  (connection-item
		   (get-connection-item designated-connection? connections)))
	(case (get-direction-of-connection designated-connection? object)
	  (input
	   (when (connection-item-input-names connection-item)
	     (reclaim-slot-value-list (connection-item-input-names connection-item)))
	   (setf (connection-item-input-names connection-item)
		 (slot-value-list portname)))
	  (t
	   (when (connection-item-output-names connection-item)
	     (reclaim-slot-value-list (connection-item-output-names connection-item)))
	   (setf (connection-item-output-names connection-item)
		 (slot-value-list portname)))))
      (flush-subworkspace-connection-posts-for-object
	designated-connection? object nil)
      (determine-subworkspace-connection-posts-for-object
	designated-connection? object))))

;; If the designated connection has a portname, it is changed.  If it does not
;; have a portname, then it is inserted.

(defun insert-portname-for-connection (block connection portname)
  #-connections-v2
  (loop with tail-pointer = nil
	with connections = (connections block)
	as portname-or-connection = (car connections)
	while connections   ; not necessary if connection is always in connections
	do
    (when (eq connection portname-or-connection)
      (if tail-pointer
      (setf (cdr tail-pointer) (slot-value-cons portname connections))
      (setf (connections block) (slot-value-cons portname connections)))
      (return (values)))
    (setq tail-pointer connections
      connections (cdr connections)))
  #+connections-v2
  (when-let (connection-item
	     (get-connection-item connection (connections block)))
    (case (get-direction-of-connection connection block)
      (input
       (slot-value-push portname (connection-item-input-names connection-item)))
      (t ; output or undirected
       (slot-value-push portname (connection-item-output-names connection-item))))))

(defun move-stub-in-definitions-and-instances
       (definition stub-designation stub-move-spec)
  (with-non-inherited-old-stub-spec 
    definition
    (let ((stub-info-to-be-changed?
        (get-stub-info-or-warn-if-none
          old-value stub-designation definition)))
      (when stub-info-to-be-changed?
    (let* ((position-in-stub-info (fifth stub-info-to-be-changed?))
           (new-position
         (get-new-position-given-stub-move-spec
           stub-move-spec position-in-stub-info)))
      (when (not (=w position-in-stub-info new-position))
        (setf (fifth stub-info-to-be-changed?) new-position)
        (change-stub-specifications-for-class
          definition (copy-for-slot-value old-value))
        (propagate-stub-change-to-strict-class-instances 
          class stub-designation 
          'move-stub-given-stub-designation stub-move-spec)
        (propagate-stub-change-to-instances-of-subclasses
          class stub-designation 
          'move-stub-given-stub-designation stub-move-spec)))))))


(defun move-stub-given-stub-designation 
       (object stub-designation stub-move-spec)
  (let ((designated-connection?
      (get-connection-given-stub-designation object stub-designation)))
    (when designated-connection?
      (let* ((end-position 
           (get-position-at-this-end-of-connection 
         designated-connection? object))
         (connection-side 
           (get-side-given-end-position end-position))
         (position-on-side
           (get-position-on-side-given-end-position end-position))
         (shift 
           (get-shift-given-stub-move-spec stub-move-spec position-on-side))
         (delta-for-straight-connection? 
           (connection-is-straight? designated-connection?))
         (straight-connections-with-deltas?
           (when delta-for-straight-connection?
         (gensym-list (gensym-cons designated-connection? 
                       delta-for-straight-connection?))))
         (output-connection? 
           (eq (input-end-object designated-connection?) object)))
    (update-connection-images t (superblock? object) designated-connection?)
    (if (left-or-right-side? connection-side)
        (shift-connection
          designated-connection? object straight-connections-with-deltas?
          output-connection? 0 shift)
        (shift-connection
          designated-connection? object straight-connections-with-deltas?
          output-connection? shift 0))
    (shift-end-position-of-connection
      object designated-connection? straight-connections-with-deltas?
      output-connection?
      connection-side shift) 
    (reclaim-gensym-list straight-connections-with-deltas?)
    (update-connection-images 
      nil (superblock? object) designated-connection?))
      (flush-subworkspace-connection-posts-for-object
    designated-connection? object nil)
      (determine-subworkspace-connection-posts-for-object
    designated-connection? object))))

(defun get-new-position-given-stub-move-spec (stub-move-spec current-position)
  (if (eq (car stub-move-spec) 'to)
      (second stub-move-spec)   ; absolute position
      (+w current-position (second stub-move-spec))))

(defun get-shift-given-stub-move-spec (stub-move-spec current-position)
  (if (eq (car stub-move-spec) 'by)
      (second stub-move-spec)   ; shift
      (-w (second stub-move-spec) current-position)))




(defun change-connection-class-in-definitions-and-instances
       (definition stub-designation connection-class)
  (with-non-inherited-old-stub-spec 
    definition
    (cond
      ((subclassp connection-class 'connection)
       (let* ((copy-of-old-value
        (copy-for-slot-value old-value))
          (stub-info-to-be-changed?
        (get-stub-info-or-warn-if-none
          copy-of-old-value stub-designation definition)))
     (when (and stub-info-to-be-changed?
            (not (eq (second stub-info-to-be-changed?) connection-class)))
       (setf (second stub-info-to-be-changed?) connection-class)
       (change-stub-specifications-for-class definition copy-of-old-value)
       (propagate-stub-change-to-strict-class-instances 
         class stub-designation 
         'change-connection-class-given-stub-designation connection-class)
       (propagate-stub-change-to-instances-of-subclasses
         class stub-designation 
         'change-connection-class-given-stub-designation connection-class))))
      (t
       (write-warning-message* 1
     (tformat "Attempting to change connection class to ~A, which is not a defined connection class."
          connection-class))))))
     



(defun change-connection-class-given-stub-designation
       (object stub-designation connection-class)
  (let ((designated-connection?
      (get-connection-given-stub-designation object stub-designation)))
    (when designated-connection?
      (let ((connection-frame-or-class
          (connection-frame-or-class designated-connection?)))
    (update-connection-images t (superblock? object) designated-connection?)
    (cond
      ((symbolp connection-frame-or-class)
       (setf (connection-frame-or-class designated-connection?)
         connection-class))
      (t
       (delete-frame connection-frame-or-class)
       (make-and-install-new-connection-frame
         designated-connection? connection-class)))
    (update-connection-images 
      nil (superblock? object) designated-connection?)))))



(defun change-direction-in-definitions-and-instances
       (definition stub-designation direction?)
  (with-non-inherited-old-stub-spec 
    definition
    (let ((stub-info-to-be-changed?
        (get-stub-info-or-warn-if-none
          old-value stub-designation definition)))
      (when (and stub-info-to-be-changed?
         (not (eq (third stub-info-to-be-changed?) direction?)))
    (setf (third stub-info-to-be-changed?) direction?)
    (change-stub-specifications-for-class
      definition (copy-for-slot-value old-value))
    (propagate-stub-change-to-strict-class-instances 
      class stub-designation 
      'change-direction-given-stub-designation direction?)
    (propagate-stub-change-to-instances-of-subclasses
      class stub-designation 
      'change-direction-given-stub-designation direction?)))))


(defun change-direction-given-stub-designation
       (object stub-designation direction?)
  (let ((designated-connection?
      (get-connection-given-stub-designation object stub-designation)))
    (when designated-connection?
      (update-connection-images t (superblock? object) designated-connection?)
      (if direction?
       (set-connection-directed designated-connection?)
       (set-connection-not-directed designated-connection?))
      (case direction?
    (output
     (when (not (output-connection-p object designated-connection?))
       (change-direction-of-connection designated-connection?)))
    (input
     (when (not (input-connection-p object designated-connection?))
       (change-direction-of-connection designated-connection?))))
      (update-connection-images 
    nil (superblock? object) designated-connection?)
      (when g2-has-v5-mode-windows-p
    (let ((connection-frame
        (connection-frame-or-class designated-connection?)))
      (send-ws-representations-item-virtual-attribute-change
        connection-frame (virtual-attribute 'connection-is-directed) nil)
      ;;the order of the connection-position-sequence has been reversed
      (send-ws-representations-connection-moved designated-connection?))))))



(defun change-direction-of-connection (connection)
  (with-connection connection t t nil nil
    (declare (ignore 
           input-end-x-position input-end-y-position
           output-end-x-position output-end-y-position))
    (when (delta-or-deltas connection)
      (let* ((all-deltas
           (add-missing-deltas-to-connection connection))
         (inverted-deltas
           (invert-connection-deltas all-deltas nil)))
    (reclaim-slot-value-list (delta-or-deltas connection))
    (setf (delta-or-deltas connection) inverted-deltas)
    (remove-redundant-deltas-from-connection connection)))
    (setf (input-end-object connection) output-end-object
      (input-end-position connection) output-end-position
      (output-end-object connection) input-end-object
      (output-end-position connection) input-end-position)))





(defun propagate-stub-change-to-strict-class-instances 
       (class stub-info-or-designation 
    function-to-perform-stub-change change-arg)
  (loop for object being each strict-class-instance of class
    do
    (funcall function-to-perform-stub-change
         object stub-info-or-designation change-arg)))

;; Stub-info-or-designation will be stub-info if adding a stub, stub-designation
;; otherwise.


(defun propagate-stub-change-to-instances-of-subclasses 
       (class stub-info-or-designation 
    function-to-perform-stub-change change-arg)
  (loop with slot-description-for-class
      = (get-slot-description
          'connections
          (slot-descriptions (class-description class)))
    for subclass in (inferior-classes class)
    do
    (when (eq slot-description-for-class
          (get-slot-description
        'connections
        (slot-descriptions (class-description subclass))))
      ;; if stub specs are inherited
      (propagate-stub-change-to-strict-class-instances 
    subclass stub-info-or-designation 
    function-to-perform-stub-change change-arg)
      (propagate-stub-change-to-instances-of-subclasses 
    subclass stub-info-or-designation 
    function-to-perform-stub-change change-arg))))



(defun get-stub-info-given-stub-designation
       (stubs-in-definition stub-designation)
  (cond
    ((not (consp stubs-in-definition))
     nil)
    ((consp stub-designation)  ; stub designation is by side and position
     (loop with designated-side = (first stub-designation)
       with designated-position = (second stub-designation)
       for stub-info in (cdr stubs-in-definition)
       as stub-info-side = (fourth stub-info)
       as stub-info-position = (fifth stub-info)
       do
       (when (and (eq designated-side stub-info-side)
          (=w designated-position stub-info-position))
     (return stub-info))))
    (t
     ;; else, if stub-designation is a portname
     (loop for stub-info in (cdr stubs-in-definition)
       as stub-info-portname = (first stub-info)
       do
       (when (eq stub-designation stub-info-portname)
     (return stub-info))))))


(defun get-stub-info-or-warn-if-none 
       (stubs-in-definition stub-designation definition)
  (let ((stub-info? (get-stub-info-given-stub-designation
              stubs-in-definition stub-designation)))
    (cond
      (stub-info? stub-info?)
      (t
       (write-warning-message* 1
     (tformat "The stubs slot of the object definition for ~A has no "
          (name-of-defined-class definition))
     (if (consp stub-designation)
         (tformat "connection located at ~A ~D."
              (first stub-designation) (second stub-designation))
         (tformat "connection at ~A." stub-designation)))
       nil))))


(defun get-connection-given-stub-designation (object stub-designation)
  (if (consp stub-designation)  ; stub designation is by side and position
      (loop with designated-side = (first stub-designation)
        with designated-position = (second stub-designation)
        for connection being each connection of object
        as end-position 
           = (get-position-at-this-end-of-connection connection object)
        as connection-side 
           = (get-side-given-end-position end-position)
        as position-on-side
           = (get-position-on-side-given-end-position end-position)
        do
        (when (and (eq designated-side connection-side)
                   (=w designated-position position-on-side))
          (return connection)))
      ;; else, if stub-designation is a portname
      (loop for connection being each connection of object at-port stub-designation
        do (return connection))))


;;; The `instantiate?' and `include-in-menus' slots have replaced the
;;; definition-menu-choice slot for G2 5.0.  (ghw 4/9/96)

(def-slot-putter instantiate? (definition new-value)
  (unless (eq new-value (instantiate? definition))
    (setf (instantiate? definition) new-value)
    (let ((class (name-of-defined-class definition)))
      (and class
       (classp class)
       (let ((current-not-instantiable-class-feature?
           (get-class-feature-if-any class 'not-user-instantiable)))
         (cond (new-value
            ;; Even if the value of the user-editable instantiate? slot
            ;; is t; the class may not be instantiable because of its
            ;; system-class inheritance.
            (cond ((direct-superiors-preclude-instantiability-p
                   (direct-superiors-of-defined-class definition))
               (add-frame-note
                 'inconsistent-instantiate-value definition)
               (unless current-not-instantiable-class-feature?
                 (add-class-feature
                   class
                   (class-description-list 'not-user-instantiable))))
              (t
               (remove-class-feature class 'not-user-instantiable))))
           (t
            (delete-frame-note-if-any
              'inconsistent-instantiate-value definition)
            (unless current-not-instantiable-class-feature?
              (add-class-feature
            class
            (class-description-list 'not-user-instantiable))))))))
    (update-representations-of-slot-value definition 'instantiate?)))

(def-slot-putter include-in-menus? (definition new-value)
  (unless (eq new-value (include-in-menus? definition))
    (setf (include-in-menus? definition) new-value)
    (let ((class (name-of-defined-class definition)))
      (and class
       (classp class)
       (let ((current-do-not-put-in-menus-class-feature?
           (get-class-feature-if-any class 'do-not-put-in-menus)))
         (if new-value
         (when current-do-not-put-in-menus-class-feature?
           (remove-class-feature class 'do-not-put-in-menus))
         (unless current-do-not-put-in-menus-class-feature?
           (add-class-feature
             class (class-description-list 'do-not-put-in-menus)))))))
    (update-representations-of-slot-value definition 'include-in-menus?)))




;;; The `definition-menu-option' slot is now obsolete.  The slot-putter code
;;; shunts the values to the slot-putter code for instantiate? and for
;;; include-in-menus? which replace the definition-menu-option slot for G2 5.0.
;;; (ghw 4/9/96)

(def-slot-putter definition-menu-option (definition new-value)
  (case new-value
    (not-a-final-choice
     (put-instantiate? definition nil nil)
     (put-include-in-menus? definition nil nil))
    (never-a-choice
     (put-instantiate? definition t nil)
     (put-include-in-menus? definition nil nil))
    (t
     (put-instantiate? definition t nil)
     (put-include-in-menus? definition t nil)))
  (values nil nil))










;;;; Default overrides




;;; Default overrides for user-defined slots are in these forms:
;;; (name (value type) 'user-defined) or (('class-qualified-name class name)
;;; (value type) 'user-defined)




;;; The macro `override-is-for-user-defined-slot-p' returns a non-null value
;;; when the override is for a user-defined slot.

(defmacro override-is-for-user-defined-slot-p (override)
  `(eq (third ,override) 'user-defined))



(defun class-has-override-on-pretty-slot-name-p (class-definition pretty-slot-name)
  (loop for override in (default-overrides class-definition)
    for name-denotation = (car-of-cons override)
    thereis (and (override-is-for-user-defined-slot-p override)
             (eq (unqualified-name name-denotation) pretty-slot-name))))




;;; The function `funcalled-value-for-user-defined-slot-override-p' returns
;;; a non-null value when the override value is a funcall form; otherwise it
;;; returns nil.

(defun funcalled-value-for-user-defined-slot-override-p (override)
  (and (override-is-for-user-defined-slot-p override)
       (let ((override-value (second override)))
     (and (consp override-value)
          (consp (car-of-cons override-value))
          (eq (car-of-cons (car-of-cons override-value)) ':funcall)))))





;;; The function `class-to-instantiate-for-override' returns the class name
;;; of a funcall-valued override; otherwise it returns nil.

(defun class-to-instantiate-for-override (override)
  (and (funcalled-value-for-user-defined-slot-override-p override)
       (third (car-of-cons (second override)))))




;;; `Get-slot-init-form-for-override-value' makes a slot constant from the
;;; override value form when it is a number, truth-value, or text.

; See the comments before get-grammar-category-for-default-override for
; the the desired format of the resulting value, for initial-value-of-variable-or-parameter.

; Format of the result of the Slot Value Compilers
;   (variables have an ending "?", parameters do not)
;   (the categories with "?" all include the symbol NONE as a parse result)
; logical      truth-value           an integer from 1000 to -1000
; quantitative quantity              see initial-sensor-value?
; float        initial-value-float   see initial-sensor-value?
; long         initial-value-long    see initial-sensor-value?
; integer      initial-value-integer see initial-sensor-value?
; symbolic     standard-or-class-qualified-symbol symbol
; text         whole-string          test-string

; sensor       initial-sensor-value?
;                                    nil
;                                    ({an integer from 1000 to -1000} truth-value)
;                                    atom
;                                    number

(defun get-slot-init-form-for-override-value
    (pretty-slot-name override-value-form override-class? slot-defining-class?
              slot-description definition)
  (let ((slot-type (feature-assq 'type (slot-features slot-description))))
    (cond
      ((eq pretty-slot-name 'initial-value-of-variable-or-parameter)
       ;; override-value-form is in the form returned by the svc for ATTRIBUTE
       (copy-for-slot-value
        (case (category-symbol-given-slot-type slot-type)
          ((truth-value truth-value?)
           (case override-value-form
             (true truth)
             (false falsity)
             (t
              (if (atom override-value-form)
                  override-value-form
                (car override-value-form)))))
          (standard-or-class-qualified-symbol
           (or override-value-form 'none))
          ((standard-or-class-qualified-symbol? whole-string whole-string?)
           override-value-form)
          (t
           (cond
             ((atom override-value-form)
              (if (eq 'truth-value
                      (get-data-type-of-variable-or-parameter-from-frame definition))
                  (case override-value-form
                    (true truth)
                    (false falsity)
                    (t override-value-form))
                override-value-form))
             ((and (consp (cdr override-value-form))
                   (eq (cadr override-value-form) 'truth-value))
              override-value-form)
             (t
              (car override-value-form)))))))
      ((text-slot-type-p slot-type) ; condition-for-using-user-menu-choice?
       (slot-value-cons
        (copy-for-slot-value override-value-form)
        (twith-output-to-text
         (write-slot-value
          (category-symbol-given-slot-type slot-type)
          override-value-form
          nil))))
      ((consp override-value-form)
       (let ((slot-value (car-of-cons override-value-form)))
         (cond
           ((and (consp slot-value)
             (eq (car-of-cons slot-value) :funcall))
        (copy-for-slot-value slot-value))
           ((eq pretty-slot-name 'g2-array-initial-values)
        (if (eq override-class? slot-defining-class?)
            (copy-for-slot-value override-value-form)
            (convert-slot-value-init-for-g2-array-initial-values
             pretty-slot-name override-value-form override-class? slot-defining-class?
             definition)))
           ((atom (cdr override-value-form))
        (copy-for-slot-value override-value-form))
           (t
        (let ((possible-slot-value-type?
               (unless (and (consp override-value-form)
                    (or (third override-value-form)
                    (eq (car-of-cons override-value-form)
                        :funcall)))
             (second override-value-form))))
          (cond ((slot-init-form-needs-evaluation? slot-value)
             (copy-for-slot-value slot-value))
            ((and possible-slot-value-type?
                  (symbolp possible-slot-value-type?))
             (if (slot-constant-type-p possible-slot-value-type?)
                 ;; The value is a numeric type, truth-value, or text.
                 ;; The remaining possibility is symbol; otherwise
                 ;; it is a two-element list.  (ghw 1/25/99)
                 (make-slot-constant slot-value possible-slot-value-type? t)
                 (if (eq possible-slot-value-type? 'symbol)
                 (copy-for-slot-value slot-value)
                 (copy-for-slot-value override-value-form))))
            (t
             (copy-for-slot-value override-value-form))))))))
      (t
       (copy-for-slot-value override-value-form)))))

(defun convert-slot-value-init-for-g2-array-initial-values
    (pretty-slot-name override-value-form override-class? slot-defining-class? definition)
  (let* ((grammar-category-for-value
      (get-grammar-category-for-default-override
       'g2-array-initial-values override-class? t))
     (grammar-category-for-class
      (get-grammar-category-for-default-override
       'g2-array-initial-values slot-defining-class? t))
     (evaluation-value
      (get-initial-evaluation-value-for-default-override-1
       override-value-form definition grammar-category-for-value)))
    (with-phrase-conses
      (multiple-value-bind
      (initialization-or-bad-phrase error-string?)
      (call-category-setter grammar-category-for-class
                evaluation-value nil nil nil)
    (if error-string?
        (progn ; the time for error messages is the s.v.compiler, not the putter
          (reclaim-text-string error-string?)
          nil)
        (copy-for-slot-value
         (funcall-compiled-function
          (slot-value-compiler grammar-category-for-class)
          initialization-or-bad-phrase
          nil pretty-slot-name slot-defining-class?
          nil nil)))))))

(defun check-g2-array-initial-values (override definition)
  (let* ((slot-name 'g2-array-initial-values)
         (compiled-value (second override))
         (override-class? (third override))
         (slot-description?
          (get-slot-description
            slot-name
            (slot-descriptions (class-description (name-of-defined-class definition)))))
         (slot-defining-class?
          (defining-class slot-description?))
         (grammar-category-for-value
          (get-grammar-category-for-default-override slot-name override-class? t))
         (grammar-category-for-class
          (get-grammar-category-for-default-override slot-name slot-defining-class? t))
         (evaluation-value
          (get-initial-evaluation-value-for-default-override-1
            compiled-value definition grammar-category-for-value)))
    (with-phrase-conses
      (multiple-value-bind
          (initialization-or-bad-phrase error-string?)
        (call-category-setter grammar-category-for-class
                              evaluation-value nil nil nil)
        (declare (ignore initialization-or-bad-phrase))
        (if error-string?
            (progn ; the time for error messages is the s.v.compiler, not the putter
              (reclaim-text-string error-string?)
              nil) ; the putter can do notes, however (handled by this function's caller)
          t)))))



;;; `Override-conflicts-with-type-specification-p' returns the declared slot
;;; value type when the override initialization value is not a subtype of the
;;; declared attribute type; otherwise it returns nil.  This function is called
;;; for defined classes only.

(defun override-conflicts-with-type-specification-p (user-class override)
  (let* ((default-initialization (second override))
     (default-value
         (if (aggregate-evaluation-value-p default-initialization)
         default-initialization
         (car default-initialization)))
     (value-type
       (if (aggregate-evaluation-value-p default-initialization)
           (aggregate-evaluation-value-type-symbol default-initialization)
           (or (class-to-instantiate-for-override override)
           (second default-initialization))))
     (name-or-class-qualified-name-list (car override))
     (corresponding-slot-description?
       (get-slot-description
         (unqualified-name name-or-class-qualified-name-list)
         (slot-descriptions (class-description user-class))
         (class-qualifier name-or-class-qualified-name-list)))
     (slot-type-specification?
       (when corresponding-slot-description?
         (slot-type-specification corresponding-slot-description?)))
     (constraining-type-specification?
       (when (and slot-type-specification?
              (not (equal slot-type-specification?
                   '(or item-or-datum (no-item)))))
         slot-type-specification?))
     (constraining-type?
       (when constraining-type-specification?
         ;; class
         (cond
           ((class-type-specification-p constraining-type-specification?)
        (type-specification-class constraining-type-specification?))
           ((structure-type-specification-p constraining-type-specification?)
        'structure)
           ((sequence-type-specification-p constraining-type-specification?)
        'sequence)
           (t
        constraining-type-specification?))))
     (type-conflict?
       (and constraining-type?
        (case constraining-type?
          (item-or-datum
           nil)
          (datum
           (when (or (eq default-value 'none)
                 (and (consp default-value)
                  (eq (car-of-cons default-value)
                      ':funcall)))
             'datum))
          (sequence
           (not (eq value-type 'sequence)))
          (structure
           (not (eq value-type 'structure)))
          (number
           (unless (eq value-type 'number) 'number))
          (integer
           (unless
               (and (eq value-type 'number) (integerp default-value))
             'integer))
          (float
           (unless (and (eq value-type 'number)
                (managed-float-p default-value))
             'float))
          (symbol
           (unless (eq value-type 'symbol) 'symbol))
          (truth-value
           (unless (eq value-type 'truth-value) 'truth-value))
          (text
           (unless (eq value-type 'text) 'text))
          (t
           (if (subclassp value-type constraining-type?)
               nil
               constraining-type?))))))
    type-conflict?))

             


;;; `Clear-override-frame-notes-from-class-definitions' clears the default-
;;; override-related frame notes from the class definitions of all subclasses of
;;; user-class.


(defun clear-override-frame-notes-from-class-definitions (user-class)
  (loop for class being each subclass of user-class
    ;; There may be no class-definition when within undefine-user-class 
    for class-definition? = (class-definition class)
    do
    (and class-definition?
     (clear-override-frame-notes-from-definition class-definition?))))

(defun clear-override-frame-notes-from-definition (definition)
  (delete-multiple-frame-notes-if-any
    '(no-corresponding-inherited-attribute-for-override
      override-value-is-not-compatible
      override-of-class-level-attribute
      attributes-have-more-than-one-override) definition))




;;; `implemented-override-p' is true when the class definition does not have
;;; a default-override-related frame note for the override.

(defun implemented-override-p (definition override)
  (let ((name-or-class-qualified-name-list (first override)))
    (not
      (or (member name-or-class-qualified-name-list
          (get-particulars-of-frame-note-if-any
            'no-corresponding-inherited-attribute-for-override
            definition) :test 'equal)
      (member name-or-class-qualified-name-list
          (get-particulars-of-frame-note-if-any
            'override-value-is-not-compatible definition)
          :test 'equal)
      (member name-or-class-qualified-name-list
          (get-particulars-of-frame-note-if-any
            'override-of-class-level-attribute definition)
          :test 'equal)
      (member name-or-class-qualified-name-list
          (get-particulars-of-frame-note-if-any
            'attributes-have-more-than-one-override definition)
          :test 'equal)))))




;;; `Add-frame-notes-for-unimplementable-overrides' checks the definition
;;; default overrides for unimplementable overrides.  When it finds one, it adds
;;; a frame note to the definition.  The return value is a list of
;;; unimplementable overrides.  The class must be defined.

(defun-simple add-frame-notes-for-unimplementable-overrides (definition)
  (let ((unimplementable-overrides? nil)
    (duplicating-override? nil))
    (loop with class = (name-of-defined-class definition)
      with overrides = (default-overrides definition)
      with class-description = (class-description class)
      with foundation-class = (get-foundation-class-for-class class)
      for override in overrides
      for name-or-class-qualified-name-list = (car override)
      for unqualified-name =
            (unqualified-name name-or-class-qualified-name-list)
      for class-qualifier? = (class-qualifier
                   name-or-class-qualified-name-list)
      for class-to-instantiate? = (class-to-instantiate-for-override
                    override)
      for unaliased-slot-name
          = (unalias-slot-name-if-necessary
         unqualified-name foundation-class)
      for slot-description
          = (get-slot-description
         unaliased-slot-name
         (slot-descriptions class-description)
         class-qualifier?)
      do
      (cond ((null slot-description)
         (add-to-frame-note-particulars-list-if-necessary
           (copy-for-slot-value name-or-class-qualified-name-list)
           'no-corresponding-inherited-attribute-for-override definition))
        ((eq (defining-class slot-description) class)
         (when (not (member override unimplementable-overrides?
                :test 'equal))
           (setq unimplementable-overrides?
             (frame-cons override unimplementable-overrides?))
           (add-to-frame-note-particulars-list-if-necessary
         (copy-for-slot-value name-or-class-qualified-name-list)
         'override-of-class-level-attribute definition)))
        ((and
           (not
         (member override unimplementable-overrides? :test 'equal))
           (loop for other-override in overrides
             for other-name-or-class-qualified-name-list =
             (car other-override)
             for other-unqualified-name =
                   (unqualified-name
                 other-name-or-class-qualified-name-list)
             thereis
             (and (not (eq override other-override))
              (eq unqualified-name other-unqualified-name)
              (eq slot-description
                  (get-slot-description
                (unalias-slot-name-if-necessary
                  other-unqualified-name 'variable-or-parameter)
                (slot-descriptions class-description)
                (class-qualifier
                  other-name-or-class-qualified-name-list)))
              (setq duplicating-override? other-override))))
         (when (not (member override unimplementable-overrides?
                :test 'equal))
           (setq unimplementable-overrides?
             (frame-cons override unimplementable-overrides?))
           (add-to-frame-note-particulars-list-if-necessary
         (copy-for-slot-value name-or-class-qualified-name-list)
         'attributes-have-more-than-one-override definition))
         (when (not (member duplicating-override? unimplementable-overrides?
                :test 'equal))
           (setq unimplementable-overrides?
             (frame-cons duplicating-override?
                 unimplementable-overrides?))
           (add-to-frame-note-particulars-list-if-necessary
         (copy-for-slot-value (car duplicating-override?))
         'attributes-have-more-than-one-override definition)))
        ((and class-to-instantiate?
          (not (classp class-to-instantiate?)))
         ;; This is necessary at load time when the class-to-instantiate? is not
         ;; yet defined and the override was not implemented for some reason.
         ;; If class-to-instantiate? is defined this will cause the override to
         ;; be implemented.
         (do-consistency-analysis-work-on-subframe-overrides
         definition class-to-instantiate?)
         (when (not (member override unimplementable-overrides? :test 'equal))
           (setq unimplementable-overrides?
             (frame-cons override unimplementable-overrides?))))
        ((and (not (override-is-for-user-defined-slot-p override))
          (case unaliased-slot-name
            (initial-value-of-variable-or-parameter
             (not (check-initial-value-of-variable-or-parameter
               (second override) overrides definition)))
            (g2-array-initial-values
             (not (check-g2-array-initial-values override definition)))))
         (setq unimplementable-overrides?
           (frame-cons override unimplementable-overrides?))
         (add-to-frame-note-particulars-list-if-necessary
          (copy-for-slot-value name-or-class-qualified-name-list)
          'override-value-is-not-compatible definition))
        ((and (override-is-for-user-defined-slot-p override)
          (not (member override unimplementable-overrides?
                   :test 'equal))
          (override-conflicts-with-type-specification-p
           class override))
         (setq unimplementable-overrides?
           (frame-cons override unimplementable-overrides?))
         (add-to-frame-note-particulars-list-if-necessary
          (copy-for-slot-value name-or-class-qualified-name-list)
          'override-value-is-not-compatible definition))))
    unimplementable-overrides?))





;;; `Class-has-override-on-slot-description-p' returns the class-level override
;;; on the slot description when there is a slot-description for the override;
;;; otherwise it returns nil.  Note that the override may not be an
;;; implementable override.

(defun class-has-override-on-slot-description-p (class slot-description)
  (when (class-description-is-user-defined-p (class-description class))
    (loop with slot-description-pretty-slot-name =
        (pretty-slot-name slot-description)
      with slot-description-defining-class =
        (defining-class slot-description)
      with class-definition = (class-definition class)
      with class-description = (class-description class)
      with class-overrides = (and class-definition
                      (default-overrides class-definition))
      for override in class-overrides
      for override-name-or-class-qualified-name-list = (car override)
      for override-possibly-aliased-slot-name =
            (unqualified-name override-name-or-class-qualified-name-list)
      for override-unaliased-slot-name =
            (unalias-slot-name-if-necessary
          override-possibly-aliased-slot-name class)
      for class-level-slot-description = nil
      when (and (eq override-unaliased-slot-name
            slot-description-pretty-slot-name)
            (setq class-level-slot-description
              (get-slot-description
                override-unaliased-slot-name
                (slot-descriptions class-description)
                (class-qualifier
                  override-name-or-class-qualified-name-list)))
            (if (user-defined-slot-description-p slot-description)
            (eq (defining-class class-level-slot-description)
                slot-description-defining-class)
            t))
        return override)))




;;; `Class-has-implemented-override-on-slot-description-p' returns the
;;; class-level override on the slot description when there is one and it is
;;; implemented.

(defun class-has-implemented-override-on-slot-description-p
    (class slot-description)
  (let ((override? nil))
    (when (and (setq override?
             (class-has-override-on-slot-description-p
               class slot-description))
           (implemented-override-p (class-definition class) override?))
      override?)))




;;; `Get-more-specific-override-on-slot-description' returns the implemented
;;; override on the slot description of the most specific class below
;;; superior-class on the class inheritance for subclass when there is one;
;;; otherwise it returns nil.
  
(defun get-more-specific-override-on-slot-description
    (superior-class subclass slot-description)
  (loop with class-inheritance-path =
           (class-inheritance-path (class-description subclass))
    for class in class-inheritance-path
    until (eq class superior-class)
    for class-level-override = nil
    when (setq class-level-override
           (class-has-implemented-override-on-slot-description-p
             class slot-description))
      return class-level-override))



;;; `Get-next-most-specific-override-on-slot-description' returns the override on
;;; the slot description of the most specific class above user class on the
;;; class inheritance path for user class when there is one; otherwise it
;;; returns nil.

(defun get-next-most-specific-override-on-slot-description
    (user-class slot-description)
  (loop with class-inheritance-path =
           (class-inheritance-path (class-description user-class))
    for class in (cdr class-inheritance-path)
    for class-level-override = nil
    when (and (classp class)
          (not (system-defined-class-p class))
          (setq class-level-override
            (class-has-implemented-override-on-slot-description-p
              class slot-description)))
      return class-level-override))




;;; The functions `add-slot-to-inherited-slots-this-class-overrides' and
;;; `delete-slot-from-inherited-slots-this-class-overrides' add or delete
;;; unique slot-names from the inherited-slots-this-class-overrides component
;;; of class-descriptions.  They are called from the default-override handling
;;; code.

(defun add-slot-to-inherited-slots-this-class-overrides
    (class unique-slot-name)
  (let* ((class-description (class-description class))
     (inherited-slots-this-class-overrides
       (inherited-slots-this-class-overrides class-description)))
    (unless (memq unique-slot-name inherited-slots-this-class-overrides)
      (setf (inherited-slots-this-class-overrides class-description)
        (class-description-cons
          unique-slot-name inherited-slots-this-class-overrides)))))
        
(defun delete-slot-from-inherited-slots-this-class-overrides
    (class unique-slot-name)
  (let* ((class-description (class-description class))
     (inherited-slots-this-class-overrides
       (inherited-slots-this-class-overrides class-description)))
    (when (memq unique-slot-name inherited-slots-this-class-overrides)
      (if (eq (car inherited-slots-this-class-overrides) unique-slot-name)
      (reclaim-class-description-cons 
        (prog1 inherited-slots-this-class-overrides
          (setf (inherited-slots-this-class-overrides class-description)
            (cdr inherited-slots-this-class-overrides))))
      (loop for sublist on inherited-slots-this-class-overrides
        for unique-slot-name-on-list = (cadr sublist)
        do
        (when (eq unique-slot-name-on-list unique-slot-name)
          (reclaim-class-description-cons 
        (prog1 
            (cdr sublist) 
          (setf (cdr sublist) (cddr sublist))))
          (loop-finish)))))))




;;; `Process-default-overrides' deals with implementing the default overrides
;;; for the subclasses of user-class.  User-class should be defined.  If an
;;; override is not implementable, a frame note is placed on the user-class
;;; definition; otherwise the override is implemented throughout the user-class
;;; hierarchy.

(defun process-default-overrides (user-class user-defined-slot-overrides-only?)
  (loop for class being each subclass of user-class
    for class-definition = (class-definition class)
    for class-description = (class-description class)
    for overrides = (default-overrides class-definition)
    for unimplementable-overrides?
        = (add-frame-notes-for-unimplementable-overrides class-definition)
    do
    (loop for unique-slot-name in (inherited-slots-this-class-overrides
                    class-description)
      for class-slot-description? = (get-slot-description-of-class-description
                      unique-slot-name class-description)
      do
      (unless class-slot-description?
    (delete-slot-from-inherited-slots-this-class-overrides class unique-slot-name)))
                    
    (loop for override in overrides
      do
      (multiple-value-bind (unaliased-slot-name override-on-user-slot?)
      (decode-default-override override class-definition)
    (let* ((name-or-class-qualified-name-list unaliased-slot-name)
           (class-slot-description-updater?
        (unless override-on-user-slot?
          (get-class-slot-description-updater-if-any unaliased-slot-name)))
           (slot-description?
        (unless (and user-defined-slot-overrides-only?
                 (not override-on-user-slot?))
          (get-slot-description
           (unqualified-name unaliased-slot-name)
           (slot-descriptions (class-description class))
           (class-qualifier name-or-class-qualified-name-list))))
           (slot-defining-class?
        (when slot-description?
          (defining-class slot-description?)))
           (current-slot-init-form
        (when (and slot-description?
               (null class-slot-description-updater?))
          (slot-init-form slot-description?))))
      #+development
      (when (and (subclassp user-class 'network-wire)
             (or (eq unaliased-slot-name 'stubs-for-class)
             (eq unaliased-slot-name 'attribute-displays-for-class)))
        (cerror "definitions" "support as been removed -- trouble -- see ghw"))

      (cond ((null slot-description?))
        (class-slot-description-updater?
         (funcall-simple-multi-valued-compiled-function 
          class-slot-description-updater?
          class (second override)))
        ((or (member override unimplementable-overrides? :test 'slot-value-equal-p)
             (and (eq unaliased-slot-name 'data-type-of-variable-or-parameter)
              (assq 'initial-value-of-variable-or-parameter unimplementable-overrides?)))
         (let ((desired-slot-init-form
            (slot-init-form
             (slot-description-of-most-specific-superior-refining-slot
              (class-inheritance-path (class-description class))
              slot-description?))))
           (unless (slot-value-equal-p
                current-slot-init-form desired-slot-init-form)
             (delete-slot-from-inherited-slots-this-class-overrides
              class (unique-slot-name slot-description?))
             (update-slot-description
              class slot-description? nil nil nil t nil))))
        (t
         (let ((desired-slot-init-form
            (get-slot-init-form-for-override-value
             unaliased-slot-name (second override)
             (third override) slot-defining-class?
             slot-description?
             class-definition)))
           (unless (and (slot-value-equal-p
                 current-slot-init-form desired-slot-init-form)
                (equal (type-of desired-slot-init-form)
                       (type-of current-slot-init-form)))
             (add-slot-to-inherited-slots-this-class-overrides
              class (unique-slot-name slot-description?))
             (update-slot-description
              class slot-description? (slot-type-specification slot-description?)
              desired-slot-init-form (slot-features slot-description?) nil nil))
           ;; fix for HQ-1687276 and Storm leak
           (if (and (consp desired-slot-init-form)
                (non-float-default-slot-constant-p desired-slot-init-form))
               (reclaim-slot-constant desired-slot-init-form)
               (reclaim-slot-value desired-slot-init-form))))))))
    finally
      (reclaim-frame-list unimplementable-overrides?)))




;;; `Remove-default-override' either updates the existing slot-init-form on user
;;; class with the next most specific override value or it updates the user
;;; class slot description to the slot init form of the defining-class slot
;;; description.

(defun remove-default-override (user-class slot-description)
  (let* ((unique-slot-name (unique-slot-name slot-description))
     (class-slot-description-updater?
      (get-class-slot-description-updater-if-any unique-slot-name)))
    (if class-slot-description-updater?
    (funcall-simple-multi-valued-compiled-function 
      class-slot-description-updater? user-class nil)
    (let ((next-most-specific-override?
        (get-next-most-specific-override-on-slot-description
          user-class slot-description)))
      (delete-slot-from-inherited-slots-this-class-overrides
        user-class (unique-slot-name slot-description))
      (if next-most-specific-override?
          (let* ((name-or-class-qualified-name-list
               (car next-most-specific-override?))
             (unqualified-name
               (unqualified-name name-or-class-qualified-name-list))
             (unaliased-slot-name
               (unalias-slot-name-if-necessary
             unqualified-name
             'item)) ;???
             (slot-defining-class?
              (defining-class slot-description))
             (slot-init-form
               (get-slot-init-form-for-override-value
             unaliased-slot-name (second next-most-specific-override?)
             (third next-most-specific-override?)
             slot-defining-class?
             slot-description
             (class-definition user-class))))
        (update-slot-description
          user-class slot-description (slot-type-specification slot-description)
          slot-init-form (slot-features slot-description) nil nil)
        (reclaim-slot-value slot-init-form))
          (update-slot-description
        user-class slot-description nil nil nil t nil))))))


(defun decode-default-override (override definition &optional return-category-p)
  (let* ((slot-name (first override))
     (unqualified-name (unqualified-name slot-name))
     (specified-class-of-override? (third override))
     (user-defined-p (eq specified-class-of-override? 'user-defined))
     (class-of-override
      (unless user-defined-p
        (or specified-class-of-override?
        (let ((slot-description?
               (possibly-aliased-slot-description-from-superior-class
            unqualified-name definition)))
          (when slot-description?
            (defining-class slot-description?))))))
     (unaliased-slot-name
      (if user-defined-p
          slot-name
          (unalias-slot-name-if-necessary slot-name class-of-override)))
     (grammar-category?
      (when (and class-of-override return-category-p)
        (get-grammar-category-for-default-override
         unaliased-slot-name class-of-override t))))
    (values unaliased-slot-name user-defined-p class-of-override grammar-category?)))

(def-slot-putter default-overrides (definition new-overrides)
  (defer-some-consistency-analysis
    (let* ((class? (name-of-defined-class definition))
       (class-is-defined? (classp class?))
       (any-class-instances? nil)
       (previous-default-overrides (default-overrides definition))
       (unimplemented-default-overrides?
         (loop for previous-override in previous-default-overrides
           when (not (implemented-override-p definition previous-override))
             collect previous-override using frame-cons)))

      ;; Fixing up an error in converting 3.0 attributes to overrides
      ;; during the 4.0 beta.
      ;; (could be a post-loading function, instead.  but it's quick, so it doesn't matter)
      (loop for override in new-overrides
        with value-to-reclaim = nil
        do
    (when (and (override-is-for-user-defined-slot-p override)
           (consp (second override))
           (null (first (second override)))
           (null (second (second override))))
      (setq value-to-reclaim (second override))
      (setf (second override) nil)
      (reclaim-slot-value value-to-reclaim)))

      (loop for override in previous-default-overrides
        when (and (override-is-for-user-defined-slot-p override)
              (reserved-system-slot-name-p
            definition (unqualified-name (car-of-cons override))))
          do (delete-from-frame-note-particulars-list
           (unqualified-name (car-of-cons override))
           'default-override-on-user-attribute-is-a-system-slot-name
           definition))

      (loop for override in new-overrides
        when (and (override-is-for-user-defined-slot-p override)
              (reserved-system-slot-name-p
            definition (unqualified-name (car-of-cons override))))
          do (add-to-frame-note-particulars-list-if-necessary
           (unqualified-name (car-of-cons override))
           'default-override-on-user-attribute-is-a-system-slot-name
           definition))
        
      (when class-is-defined?
    ;; Test for instances before any definition changes are made.
    (loop for thing being each class-instance of class?
          do
      (setq any-class-instances? t)
          until any-class-instances?)
    (clear-override-frame-notes-from-class-definitions class?))
      
      (without-consistency-analysis (definition) 
    (setf (default-overrides definition) new-overrides))

      (when class-is-defined?
    ;; Remove deleted overrides.
    (loop with class-description = (class-description class?)
          for previous-override in previous-default-overrides
          do
      (unless (member previous-override unimplemented-default-overrides?
              :test 'slot-value-equal-p)
        (if (override-is-for-user-defined-slot-p previous-override)
        (let* ((name-or-class-qualified-name-list
             (car previous-override))
               (previous-override-unqualified-name
             (unqualified-name name-or-class-qualified-name-list))
               (class-qualifier?
             (class-qualifier name-or-class-qualified-name-list))
               (previous-override-applicable-slot-description?
             (get-slot-description
               previous-override-unqualified-name
               (slot-descriptions class-description) class-qualifier?)))
          (unless
              (or (null previous-override-applicable-slot-description?)
              (loop for override in new-overrides
                do
                (when (override-is-for-user-defined-slot-p override)
                  (let* ((name-or-class-qualified-name-list
                       (car override))
                     (new-override-unqualified-name
                       (unqualified-name
                     name-or-class-qualified-name-list))
                     (class-qualifier?
                       (class-qualifier
                     name-or-class-qualified-name-list))
                     (new-override-applicable-slot-description?
                       (and (eq previous-override-unqualified-name
                        new-override-unqualified-name)
                        (get-slot-description
                          new-override-unqualified-name
                          (slot-descriptions class-description)
                          class-qualifier?))))
                (when (eq previous-override-applicable-slot-description?
                      new-override-applicable-slot-description?)
                  (return t))))))
            (remove-default-override
              class? previous-override-applicable-slot-description?)))
        (let ((slot-name (car previous-override)))
          (unless (member slot-name new-overrides :test 'car-eq)
            (let ((applicable-slot-description?
                (get-slot-description
                  (unalias-slot-name-if-necessary
                slot-name class?)
                  (slot-descriptions class-description))))
              (when applicable-slot-description?
            (remove-default-override
              class? applicable-slot-description?))))))))
    (reclaim-frame-list unimplemented-default-overrides?)
    (process-default-overrides class? nil)
    (update-attribute-tables-for-instances class? nil)
    ;; This slot-putter may have deleted or changed the class of a frame
    ;; contained in an attribute.  This can happen when a default value
    ;; is added, removed, or changed.  Therefore, validate parts of this
    ;; KB that may be affected by this.
    (when any-class-instances?
      (validate-kb-after-runtime-definition-change class? nil nil))))

    (values new-overrides nil)))




;; The above validation of KB runtime-definition changes could be made more
;; efficient by not calling the validation function when we can be certain that
;; no instance has an attribute object that removed (or whose class has
;; changed).  We cannot always be sure, even based on the attribute slot init
;; form of the class, because the user could have manually added or deleted the
;; object conatined in the attribute.  Perhaps, we could check the type spec, if
;; any, of the attribute init form and make certain it is only the type or
;; subtype of "value".  - cpm, 7/22/94



;;; `Remove-default-message-overrides' sets the default message properites to
;;; nil.  This must be done in the event that the foundation class is about to
;;; change or the definition is about to become undefined.  It is done for
;;; message-definition classes only.  Remove-default-overrides-on-system-slots
;;; does similar work on object-definitions and class-definitions.

(defun remove-default-message-overrides (message-definition)
  (loop for class being each subclass of (name-of-defined-class
                       message-definition)
    for class-definition? = (class-definition class)
    for default-message-properties?
          = (and class-definition?
             (frame-of-class-p class-definition? 'message-definition)
             (default-message-properties class-definition?))
    do
    (when default-message-properties?
      (reclaim-slot-value default-message-properties?)
      (set-slot-value-and-update-representations
    class-definition? 'default-message-properties nil))
    (when (and class-definition?
           (frame-of-class-p class-definition? 'message-definition))
      (reset-default-message-properties-from-potential-subclasses class))))


(defun reset-default-message-properties-from-potential-subclasses (class)
  (loop with potential-inferior-class-definitions =
      (potential-inferior-class-definitions class)
    for definition in potential-inferior-class-definitions
    for default-message-properties =
          (and (frame-of-class-p definition 'message-definition)
           (default-message-properties definition))
    do
    (reclaim-slot-value default-message-properties)
    (setf (default-message-properties definition) nil)
    (update-representations-of-slot-value
      definition 'default-message-properties)))




;;; `Default-overrides-on-system-slots-p' returns true when there is
;;; a default override on a system-defined slot in the definition.

(defun default-overrides-on-system-slots-p (definition)
  (loop for override in (default-overrides definition)
    thereis
    (not (override-is-for-user-defined-slot-p override))))




;;; `Remove-default-overrides-on-system-slots' removes the overrides on
;;; system slots from the object definition.  It keeps the overrides on the
;;; user-defined attributes with their appropriate frame notes.  This
;;; is done when the foundation class is changing or the definition-level
;;; definition is being deleted.

;; Note that there is a check for there being a definition for a subclass.
;; This is done because the inferior-class properties of classes is not
;; updated until the final exit from delete-frame in order to help data-
;; structure reclamation when the kb is not being cleared.

(defun remove-default-overrides-on-system-slots
    (definition called-from-undefine-user-class?)
  (loop for class being each subclass of (name-of-defined-class definition)
    for class-definition? = (class-definition class)
    for default-overrides? =
          (and class-definition?
           (default-overrides class-definition?))
    for default-overrides-on-system-slots? =
          (and default-overrides?
           (loop for override in default-overrides?
             thereis (not (override-is-for-user-defined-slot-p
                       override))))
    do
    (when (and default-overrides? default-overrides-on-system-slots?)
      (let ((new-default-overrides?
          (loop for override in default-overrides?
            when (override-is-for-user-defined-slot-p override)
              collect (copy-for-slot-value override) using slot-value-cons)))
    (cond (called-from-undefine-user-class?
           (reclaim-slot-value default-overrides?)
           (setf (default-overrides class-definition?) new-default-overrides?))
          (t (change-slot-value
           class-definition? 'default-overrides new-default-overrides?)))))
    (when class-definition?
      (reset-default-overrides-on-system-slots-from-potential-subclasses class))))


(defun reset-default-overrides-on-system-slots-from-potential-subclasses (class)
  (loop with potential-inferior-class-definitions =
      (potential-inferior-class-definitions class)
    for definition in potential-inferior-class-definitions
    for default-overrides? = (default-overrides definition)
    for default-overrides-on-system-slots? =
          (and default-overrides?
           (loop for override in default-overrides?
             thereis (not (override-is-for-user-defined-slot-p
                       override))))
    do
    (when (and default-overrides? default-overrides-on-system-slots?)
      (let ((new-default-overrides?
          (loop for override in default-overrides?
            when (override-is-for-user-defined-slot-p override)
              collect (copy-for-slot-value override) using slot-value-cons)))
    (change-slot-value definition 'default-overrides new-default-overrides?)))))



;;; The class-method `cleanup' fusses with connections and attribute names,
;;; and also NILs the icon description slot, in order to release any references
;;; it may contain to names of images.

(def-class-method cleanup (class-definition)
  ;; Deferral of analysis is needed particularly by the cached-attribute
  ;; free-reference.  It is done for efficiency reasons and, also, so that
  ;; changes to definitions are completed before the analysis is done.
  (funcall-superior-method class-definition)    ; per convention

  (defer-some-consistency-analysis
    (let ((old-indexed-attributes
	   (indexed-attributes-for-definition class-definition))
	  (class-name (name-of-defined-class class-definition)))

      (loop for attribute-description in (class-specific-attributes class-definition)
	    do
	(delete-from-directory-of-names
	  (attribute-name attribute-description) 'attribute-name))

      (when (and (classp class-name)
		 (class-definition-defines-user-editable-icon-class-p
		   class-definition))
	(reclaim-slot-value (icon-description-for-class? class-definition))
	(setf (icon-description-for-class? class-definition) nil))

      (cond ((classp class-name)
	     (when (memq 'connection
			 (class-inheritance-path-of-definition class-definition))
	       (update-all-connections-of-class class-name t t)
	       (delete-junction-block-definition-if-appropriate
		 class-name
		 (class-slot-description-value 'junction-block-class-for-class class-name))
	       ;; During cleanup, we don't go through the updater because the
	       ;; side effects may try to access reclaimed data structures.
	       (change-class-slot-description-value
		 'junction-block-class-for-class class-name nil)
	       (when (frame-of-class-p class-definition 'connection-definition)
		 (setf (junction-block-class-for-connection class-definition) nil)))
	     (undefine-user-class class-definition t nil))

	    (t
	     (when (frame-of-class-p class-definition 'connection-definition)
	       (delete-junction-block-definition-if-appropriate
		 class-name (junction-block-class-for-connection class-definition)))
	     (undefine-potential-user-class class-definition)))

      ;; It would be nicer if we had a smarter way to decache, but the big
      ;; hammer is being used in other places as well.  This was added to fix a
      ;; leak - HQ-3760291 -dkuznick, 12/22/00
      (decache-class-chaining-lists)

      ;; Cleanup indexed-attribute info.  Do this after all the class instances
      ;; have been removed.  (This fixes a bug in deleting modules containing
      ;; indexed-attributes.  - cpm, 1/9/94.)
      (setf (indexed-attributes-for-definition class-definition) nil)
      (update-indexed-attribute-properties
        class-definition t old-indexed-attributes nil)
      (reclaim-slot-value-list old-indexed-attributes))))

;; Note A: This line was added to version 1.168 definitions.lisp in order to
;; fix a crash in consistency analysis.  The slot icon-description-for-class?
;; can now refer to names (names of images, actually), and hence must be made
;; to not refer to those names during cleanup, so that the re-assert of
;; consistency will not immediately notice them again.  Unfortuntately, the
;; change-slot-value has multitudinous side effects, known only to the wise
;; ones.  We need a better way to make the slot stop refering to any
;; names. -fmw, 6/8/94
;; (6/13/94 -- ghw):  I have replaced the change-slot-value call on the icon-
;; description-for-class? with a slot-value reclaim and setting to nil.
;; The problem is that the class can have instances that are in a state of
;; partial reclamation (because of the recursive nature of delete-frame).
;; However, the slot putter code for icon-description-of-class? tries
;; to readjust the icon edges of all of the instances of the class and will
;; crash when accessing a reclaimed icon-attributes-plist.  Because all of the
;; instances of class will be deleted in the call to undefine-user-class, we
;; can probably get away without adjusting the icons.  The icon-description-for-
;; class? slot is unique for a definition (not inherited by subclasses) so it is
;; safe to reclaim it and set it to nil.





;;; Used above. The junction-block definition is deleted if (1) its name
;;; is derived from the name of the connection class (i.e. it is appropriate),
;;; and (2) it exists, and (3) it is in limbo.

(defun delete-junction-block-definition-if-appropriate
       (connection-class junction-block-class)
  (let* ((appropriate-name
       (intern-text-string
         (tformat-text-string "JUNCTION-BLOCK-FOR-~A" connection-class)))
     junction-block-definition?)
    (when (and (eq appropriate-name junction-block-class)
           (setq junction-block-definition?
             (get-instance-with-name-if-any
               'class-definition junction-block-class))
           (null (superblock? junction-block-definition?)))
      (delete-frame junction-block-definition?))))


(defun car-of-sublists-eq? (list-1 list-2)
  (and (=f (length list-1)
       (length list-2))
       (loop for sub-list-1 in list-1
         for sub-list-2 in list-2
         with result? = t
         while result?
         do
     (setq result? (eq (car sub-list-1) (car sub-list-2)))
         finally
           (return result?))))




(defun update-all-cross-section-patterns-of-instances (connection-class)
  (loop for entity being each class-instance of 'entity
    for connections =
    (loop for connection being the output-connections of entity
          collecting connection using frame-cons )
    doing
    (loop for connection in connections
      for frame-or-class = (connection-frame-or-class connection)
      for class-name = (if (framep frame-or-class)
                   (class frame-or-class)
                   frame-or-class)
      for class-description? = (class-description class-name)
      with frame-or-class-pattern
      with frame-regions and frame-stripes
      with same-region-names? and same-stripe-names?
      with default-cross-section-pattern
      with class-stripes and class-regions
      when class-description?
        ;; It is a constraint violation to have a kb with an instance
        ;; without a corresponding class definition, or to have an
        ;; instance appear before its corresponding class definition
        ;; (even for connection instances that are structures!), but
        ;; there are such kb out there because of a kb-save error.
        ;; The check for a class-description is made to let the loding
        ;; continue in the hope that it is the case that the class
        ;; definition will appear later and the kb will be consistent.
        ;; (ghw/rdf 6/16/95)
        do
          (setq default-cross-section-pattern 
            (slot-init-form
              (get-slot-description
               'cross-section-pattern
                (slot-descriptions class-description?))))
          (setq class-stripes
            (get-cross-section-stripes default-cross-section-pattern))
          (setq class-regions
            (get-cross-section-regions default-cross-section-pattern))
          (when (and (framep frame-or-class)
             (subclassp
               (class frame-or-class)
               connection-class))
        ;; only do something in the non-default case
        (unless (eq (cross-section-pattern frame-or-class)
                default-cross-section-pattern)
          (setq frame-or-class-pattern
            (cross-section-pattern frame-or-class))
          (setq frame-regions
            (get-cross-section-regions frame-or-class-pattern))
          (setq frame-stripes
            (get-cross-section-stripes frame-or-class-pattern))
          ;; we can only do this if the names of the regions are the same,
          ;; otherwise we punt
          (setq same-region-names?
            (car-of-sublists-eq? frame-regions class-regions))
          (setq same-stripe-names?
            (car-of-sublists-eq? frame-stripes class-stripes))
          (cond ((and same-stripe-names? same-region-names?)
             (loop for frame-stripe in frame-stripes
                   for class-stripe in class-stripes
                   do
               #+development
               (unless (fixnump (cdr class-stripe))
                 (break "widths must be a fixnum"))
               (when (fixnump (cdr class-stripe))
                 (setf (cdr frame-stripe)
                   (cdr class-stripe)))))
            (t
             ;; if we can't be slick we slam it to be eq to the default value
             ;; remember we can't get here unless we're in the non default case
             (reclaim-slot-value (cross-section-pattern frame-or-class))
             (setf (cross-section-pattern frame-or-class)
                   default-cross-section-pattern))))))
    (reclaim-frame-list connections)))




;;; Update-all-connections-of-class is used by the cleanup method for 
;;; definition for the case of connection definitions and also by the
;;; slot putter for cross-section-pattern-for-connection to perform
;;; an update of all connections for a particular class.

(defun update-all-connections-of-class (connection-class erase? delete?)
  (loop for entity being each class-instance of 'entity
    for connections =
    (loop for connection being the output-connections of entity
          collecting connection using frame-cons) doing
    (loop for connection in connections doing
      (if (let ((frame-or-class (connection-frame-or-class connection)))
        (subclassp
          (if (framep frame-or-class)
          (class frame-or-class)
          frame-or-class)
          connection-class))
      (progn
        (when (and (superblock? entity)
               ;; the following condition was added to prevent
               ;;   turding.  In the erase? AND delete? case,
               ;;   this was erasing here explicitly, and then
               ;;   calling delete-connection, which would then
               ;;   do a second erase, resulting in a turd.  (In
               ;;   earlier versions of the system, this turding
               ;;   was masked by an optimization in DRAW.)
               ;;   (MHD 10/15/90)
               (not (and erase? delete?)))
          (update-connection-images
        erase? (superblock? entity) connection))
        (when delete? (delete-connection connection)))))
    (reclaim-frame-list connections)))

;; If erase? is nil, then delete? should be also.




;;; `Get-last-system-defined-slot-description' returns the last system-defined
;;; slot descriptions in the slot descriptions of the class description for
;;; class.

(defun-simple get-last-system-defined-slot-description (class)
  (loop with slot-descriptions =
           (slot-descriptions (class-description class))
    for sublist on slot-descriptions
    when (or (null (second sublist))
         (user-vector-slot-index? (second sublist)))
      return (first sublist)))




;;; `Get-slot-description-preceding-defining-class-slot-descriptions' returns
;;; a slot description from the slot descriptions of class that is to precede
;;; an added slot description when the slot description is for the first
;;; attribute for class-that-defines-slot.  

(defun-simple get-slot-description-preceding-defining-class-slot-descriptions
    (class class-that-defines-slot)
  (let* ((class-description (class-description class))
     (class-inheritance-path
       (class-inheritance-path class-description))
     (less-specific-classes-than-defining-class-on-path
       (cdr (memq class-that-defines-slot class-inheritance-path))))

    (loop for less-specific-class
            in less-specific-classes-than-defining-class-on-path
      for class-specific-attributes? =
            (when (not (system-defined-class-p less-specific-class))
          (class-specific-attributes
            (class-definition less-specific-class)))

      do
      (when class-specific-attributes?
    (return (get-slot-description
          (attribute-name (car (last class-specific-attributes?)))
          (slot-descriptions class-description) less-specific-class)))
      finally
      (return (get-last-system-defined-slot-description class)))))

               
             
             
               
;;; `Preceding-slot-description-for-positioning-slot-addition' returns the
;;; class-level slot-description after which the new slot description should be
;;; added.  Slot descriptions for user-defined classes appear in this order (1)
;;; system-defined slot descriptions, (2) user-defined slot descriptions for
;;; superior classes from least specific to most specific, and (3) user-defined
;;; slot-descriptions for the class.

(defun-simple preceding-slot-description-for-positioning-slot-addition
    (class class-that-defines-slot pretty-slot-name)
  (let* ((class-definition-for-class-that-defines-slot
       (class-definition class-that-defines-slot))
     (class-specific-attributes-for-class-that-defines-slot
       (class-specific-attributes
         class-definition-for-class-that-defines-slot))
     (attribute-position-in-descriptions
       (position pretty-slot-name
             class-specific-attributes-for-class-that-defines-slot
             :test 'car-eq)))
    (if (zerop attribute-position-in-descriptions)
    (get-slot-description-preceding-defining-class-slot-descriptions
      class class-that-defines-slot)
    (let ((name-of-slot-preceding-added-slot
        (attribute-name
          (nth (1-f attribute-position-in-descriptions)
               class-specific-attributes-for-class-that-defines-slot))))
      (get-slot-description
        name-of-slot-preceding-added-slot
        (slot-descriptions (class-description class))
        class-that-defines-slot)))))



(defun cdr-eq (x some-cons) (eq x (cdr some-cons)))
(defun cadr-eq (x some-cons) (eq x (cadr some-cons)))
(defun car-car-eq (cons1 cons2) (eq (car cons1) (car cons2)))





;;; The `handle-change-or-deletion-fanout method for definition' ...

(def-class-method handle-change-or-deletion-fanout
    (class-definition slot-name-or-t-in-change-case?)
  (funcall-superior-method class-definition slot-name-or-t-in-change-case?)
  (unless (memq slot-name-or-t-in-change-case?
        '(slot-group-for-block? frame-representations
          icon-attributes-plist subworkspaces))
    (let ((defined-class?
          (if (classp (name-of-defined-class class-definition))
          (name-of-defined-class class-definition))))
      ;; the following can visit class-definition nodes twice
      ;; in the obscure case of a class having multiple paths
      ;; to the same inferior; that case is not optimized for,
      ;; but is safe
      (when defined-class?
    (loop for instance being each strict-class-instance
          of defined-class?
          do (note-change-or-deletion instance t)))
      (loop for inferior-class in (inferior-classes defined-class?)
        as class-definition ; can't fail (or a constraint violation)
        = (get-instance-with-name-if-any 'class-definition inferior-class)
        do (note-change-or-deletion class-definition t)))))






;;;; Implied Attributes

 

;;; `Attribute-value' is a KB specific property with value of the form,
;;; ({(<class> . <attribute-name>)}), where <class> is a class with an
;;; <attribute-name> attribute such that the symbol of which the property
;;; value is an attribute-value property is within the range of possible
;;; values of the attribute.

(def-kb-specific-property-name attribute-value)




;;; `Class-and-symbol-values-for-attribute' is a KB specific property list which
;;; stores an alist of classes and possible values for a given attribute.  When
;;; a new symbolic attribute is defined for a class, this property should be
;;; updated to include that new class name and the new set of possible values.
;;; This management is handled by the `declare-implied-attribute' and
;;; `undeclare-implied-attribute' functions.  To find the specific set of values
;;; for an attribute/class pair, call the function
;;; `value-set-given-attribute-and-class'.

;;; Modified by ML, 3 October, '89 so that for symbol A which is a user defined
;;; attribute of a class C, this property of A is a list containing as an element 
;;; the list (C . values) even in the case where there are no values. This will now
;;; be used to support diagnostic frame notes. (The property was present only some
;;; of the time when there were no values before this fix.


;(def-kb-specific-property-name class-and-symbol-values-for-attribute)

; The above has been moved to before attribute-p in this file.



;;; The 'Value-set-given-attribute-and-class' macro gets the list of classes and
;;; values for a particular attribute name, then finds and returns the most
;;; specific set of values for the given class, returning NIL if none are defined for
;;; this class and attribute.

(defun value-set-given-attribute-and-class (attribute class)
  (let ((class-and-values-alist (class-and-symbol-values-for-attribute attribute)))
    (when class-and-values-alist
      (loop with found-alist-entry = nil
        for superior-class in
        (class-inheritance-path (class-description class))
        do
    (setq found-alist-entry (assq superior-class class-and-values-alist))
        until found-alist-entry
        finally (return (cdr found-alist-entry))))))





;;; The `declare-value-set-for-attribute-and-class' function sets the value set
;;; definition for an attribute and class in the
;;; class-and-symbol-values-for-attribute KB specific property, removing any old
;;; definition, if there was one.  This set represents the possible values for a
;;; symbolic attribute of class instance, and may be looked up using the
;;; value-set-given-attribute-and-class function.  Frames conses are used to
;;; store the set, and the function remove-value-set-for-attribute-and-class
;;; should be used to undefine this set.

(defun declare-value-set-for-attribute-and-class (attribute class value-list)
  (remove-value-set-for-attribute-and-class attribute class)
  (setf (class-and-symbol-values-for-attribute attribute)
    (frame-cons
      (frame-cons
        class
        (copy-list-using-frame-conses value-list))
      (class-and-symbol-values-for-attribute attribute))))




;;; The `remove-value-set-for-attribute-and-class' function modifies the
;;; class-and-symbol-values-for-attribute KB specific property list so as to
;;; remove any definition of a value set for an attribute/class pair, if there
;;; is any currently defined.  The function reclaims the frame conses which were
;;; used to store the definition.

(defun remove-value-set-for-attribute-and-class (attribute class)
  (let ((class-value-alist (class-and-symbol-values-for-attribute attribute)))
    ;; First check if this class is the first one on the list, then enter a loop
    ;; to check for the general case of it being somewhere in the middle.
    (cond ((and class-value-alist
        (eq (caar class-value-alist) class))
       (setf (class-and-symbol-values-for-attribute attribute)
         (cdr class-value-alist))
       (reclaim-frame-list (car class-value-alist))
       (reclaim-frame-cons class-value-alist))
      (class-value-alist
       ;; At this point we know that we're not going to reclaim the cons
       ;; pointed to by sub-alist, but we are checking its cdr to see if
       ;; that is the cell that will be split out.
       (loop for sub-alist on class-value-alist
         until (null (cdr sub-alist))
         do
         (when (eq (caadr sub-alist) class)
           (reclaim-frame-list (cadr sub-alist))
           (reclaim-frame-cons
         (prog1 (cdr sub-alist)
            (setf (cdr sub-alist) (cddr sub-alist))))
           (return t)))))))




;;; (declare-implied-attribute <class name> <attribute name> <listed values>)
;;; declares an association between the listed values and attributes of the
;;; given class.  A declaration of this sort enables the system to determine
;;; `implied attributes'.  An `implied attribute' is an attribute determined by
;;; the unique association between a value and an attribute of a class.  Two
;;; mappings are stored about the associations, one to get the appropriate
;;; attribute given the value and class, and one to get the approriate values
;;; given the attribute and class.  These are stored in the attribute-value and
;;; class-and-symbol-values-for-attribute KB specific property lists.  They are
;;; looked up with unique-attribute-of-class-with-potential-symbolic-value and
;;; value-set-given-attribute-and-class.

;;; Declare-implied-attribute and undeclare-implied-attribute must be called for
;;; all attributes, not just those having a non-null range. This is because of
;;; the new use being made of class-and-symbol-values-for-attribute for compile-time
;;; diagnostics. ML, 3 October, 89

(defun declare-implied-attribute
    (class attribute-name values class-qualified-attribute-name?)
  
  ;; We do not want class-qualified attribute-name symbols to appear on the
  ;; attribute-value property, because this property is checked for determining
  ;; the uniqueness of the name on the class.

  ;; We do want both class-qualified and un-class-qualified attribute-name
  ;; symbols to appear on the class-and-symbol-values-for-attribute property
  ;; because that property is checked for user attribute access.
  
  (unless class-qualified-attribute-name?
    (loop with attribute-value
      with association?
      for value in values
      doing
      (when (symbolp value)         ; When not, frame note?
    (setq attribute-value (attribute-value value))
    (setq association?
          (loop for association in attribute-value
            as  (c . aname) = association
            thereis (and (eq class c)
                 (eq attribute-name aname)
                 association)))
    (unless association?
      ;; Test to ensure uniqueness.
      (setf (attribute-value value)
        (frame-cons
          (frame-cons class attribute-name)
          attribute-value))))))
  ;; Finally, set up the value set.
  (declare-value-set-for-attribute-and-class attribute-name class values)
  (analyze-compiled-items-for-consistency attribute-name))




(defun undeclare-implied-attribute
    (class attribute-name values class-qualified-attribute-name?)
  (unless class-qualified-attribute-name?
    (loop with attribute-value
      for value in values
      doing
      (setq attribute-value (attribute-value value))
      (when attribute-value
    (if (and (eq (caar attribute-value) class)
         (eq (cdar attribute-value) attribute-name))
        (reclaim-frame-cons
          (prog1 attribute-value
        (reclaim-frame-cons
          (car attribute-value))
        (setf (attribute-value value)
              (cdr attribute-value))))
        (loop as sublist = attribute-value then (cdr sublist)
          until (null (cdr sublist))
          thereis (and (eq (caadr sublist) class)
                   (eq (cdadr sublist) attribute-name)
                   (progn
                 (reclaim-frame-cons
                   (prog1
                       (cdr sublist)
                     (reclaim-frame-cons
                       (cadr sublist))
                     (setf (cdr sublist) (cddr sublist))))
                 t)))))))
  (remove-value-set-for-attribute-and-class attribute-name class)
  (analyze-compiled-items-for-consistency attribute-name))




        



;;;; Inherited attributes



(def-slot-value-writer inherited-attributes (value definition)
  (declare (ignore value))
  (let* ((direct-superiors?
       (if definition (direct-superiors-of-defined-class definition)))
     (superiors-are-classes?
       (loop for direct-superior in direct-superiors?
         when (not (classp direct-superior))
           return nil
         finally (return t)))
     (class-inheritance-path
       (if definition
           (class-inheritance-path-of-definition definition))))
     
    (if (and direct-superiors? superiors-are-classes?)
    (loop with inherited-attributes? = nil
          with slot-names-already-written =
          (loop for attribute-description in
              (class-specific-attributes definition)
             collect (attribute-name attribute-description)
               using frame-cons)
          with first-inherited-attribute? = t
          for superior in (cdr class-inheritance-path)
          until (eq superior 'item)
          for superior-definition = (class-definition superior)
          for superior-attribute-descriptions? =
                (when (not (system-defined-class-p superior))
              (class-specific-attributes superior-definition))
          do
      (when superior-attribute-descriptions?
        (setq inherited-attributes? t))
      (loop for attribute-description in superior-attribute-descriptions?
        do
        (if first-inherited-attribute?
        (setq first-inherited-attribute? nil)
        (tformat ";~%"))
        ;; Write the class-specifiers for non-default slots only.
        (cond ((memq (attribute-name attribute-description)
             slot-names-already-written)
           (write-attribute-description
             attribute-description
             superior-definition definition superior))
          (t
           (setq slot-names-already-written
             (frame-cons (attribute-name attribute-description)
                     slot-names-already-written))
           (write-attribute-description
             attribute-description superior-definition definition nil))))
          finally (reclaim-frame-list slot-names-already-written)
              (unless inherited-attributes?
            (twrite "none")))
    (twrite "none"))))




#+development
(defun reformat-attribute-list (attribute-list)
(loop for attribute-desc in attribute-list 
      for name = (car attribute-desc)
      for init = (second attribute-desc)
      collect (cond
        ((numberp init) (list name init 'number))
        ((symbolp init) (list name init 'symbol))
        ((and (consp init) (eq (car init) :funcall))
         (list name init nil))
        ((consp init) (list name (car init) (cadr init))))))




#+development
(defun layout-icons (list-of-icons workspace no-of-columns width height x-init y-init)
  (loop with x = x-init and y = y-init and column = 1
    for icon in list-of-icons doing
    (setf (name-or-names-for-frame icon) (name-of-defined-class icon)) 
    (funcall-method 'shift icon x y)
    (add-subblock icon workspace)
    (update-name-box icon)
    (enlarge-workspace-for-block-rectangle-if-necessary icon workspace)
    (cond
      ((< column no-of-columns)
       (incf x width)
       (incf column))
      (t (incf y height)
     (setq x x-init)
     (setq column 1)))))







;;;; Free-text-definition





(add-grammar-rules
  '((message-properties 'none nil nil-function)
    (message-properties message-properties-1)

    (message-properties-1 message-property (1))
    (message-properties-1 (message-property '\; message-properties-1) (1 . 3))

    (message-property (text-color-attribute 'is color-or-metacolor)
              (1 . 3))
    (message-property (message-dimension '= positive-integer)
              (1 . 3))
    (message-property ('font 'is font-name) (1 . 3))

    ;; added for 5.0 rev. 3: note that TEXT-ALIGNMENT was chosen (over
    ;; alignment) because that is used in the parts annotations for charts,
    ;; which already existed.  Also, note that the grammar for
    ;; text-alignment-kind is defined in parts.  However, this facility will
    ;; probably be soon extended to allow at least one new kind of alignment: a
    ;; decimal point aligned to a specified offset from the left (and maybe
    ;; alternatively the right) edge.  That's TBD. (MHD 3/3/98)
    (message-property
     ('text-alignment 'is text-alignment-kind)
     (1 . 3))
    

    (text-color-attribute 'border-color)
    (text-color-attribute 'background-color)
    (text-color-attribute 'text-color line-color)

    (message-dimension 'minimum-width)
    (message-dimension 'minimum-height)))


;; It is an empirical fact that the above grammar normally fails to execute the
;; nil-function call, making the slot-compiler below necessary. Yet on an
;; Explorer, if the grammar above is recompiled after loading, this parsing bug
;; goes away!!!

(def-slot-value-compiler message-properties (parse)
  (if (eq parse 'none)
      nil
      (loop for sym in '(line-color background-color border-color
             minimum-width minimum-height font text-alignment)
        for assoc = (assq sym parse)
        when assoc
          collect assoc using phrase-cons)))

(def-slot-value-writer message-properties (value)
  (if (null value)
      (twrite "none")
      (loop for (property . rest) on value do
    (tformat "~(~a ~a ~a~)"
         (if (eq (car property) 'line-color) 'text-color (car property))
         (if (memq (first property) '(minimum-width minimum-height))
             "=" "is")
         (cdr property))
    (if rest (twrite "; ")))))

(define-category-evaluator-interface (message-properties
                       :access read-write)
    (or (no-item)
    (structure
      message-properties-spec
      ((message-text-color (or (no-item) symbol))
       (message-background-color (or (no-item) symbol))
       (message-border-color (or (no-item) symbol))
       (message-minimum-width (or (no-item) integer))
       (message-minimum-height (or (no-item) integer))
       (message-font (or (no-item) (member small large extra-large)))
       ;;Very unfortunate -- we would like to use text-alignment-kind below,
       ;;but the evaluation will be all wrong.  -yduJ, 3/02
       (message-text-alignment (or (no-item) (member left center right))))))

  ((set-form (evaluation-value))
   (when evaluation-value
     (with-structure (evaluation-value message-properties-spec)
       (nconc
     (when message-text-color
       (phrase-list (phrase-cons 'line-color message-text-color)))
     (when message-background-color
       (phrase-list
         (phrase-cons 'background-color message-background-color)))
     (when message-border-color
       (phrase-list (phrase-cons 'border-color message-border-color)))
     (when message-minimum-width
       (phrase-list (phrase-cons 'minimum-width message-minimum-width)))
     (when message-minimum-height
       (phrase-list (phrase-cons 'minimum-height message-minimum-height)))
     (when message-font
       (phrase-list (phrase-cons 'font message-font)))
     (when message-text-alignment
       (phrase-list (phrase-cons 'text-alignment message-text-alignment)))))))

  ((get-form (slot-value))
   (if slot-value
       (with-new-structure (message-properties-spec)
     (setf-non-nil message-text-color (cdr (assq 'line-color slot-value)))
     (setf-non-nil message-background-color
           (cdr (assq 'background-color slot-value)))
     (setf-non-nil message-border-color
           (cdr (assq 'border-color slot-value)))
     (setf-non-nil message-minimum-width (cdr (assq 'minimum-width slot-value)))
     (setf-non-nil message-minimum-height (cdr (assq 'minimum-height slot-value)))
     (setf-non-nil message-font (cdr (assq 'font slot-value)))
     (setf-non-nil message-text-alignment (cdr (assq 'text-alignment slot-value))))
       'none)))
       







;;;; Initializing KB Name Directories

;; jv, 9/12/96 - removing "more-general-category-symbols-with-directories."
;; See comments near its (now conditionally excluded) definition for details.

  ;; Set up links between more and less general category
  ;;   symbols with directories:
  ;; (set-up-more-general-category-symbols-with-directories)

(defun-void initialize-kb-name-directories ()

  ;; Class Names:
  (add-or-delete-class-or-name-for-frame 'item 'item nil t)
  (add-special-class-names-to-foundation-class-directories)

  ;; Slot Names:  
  (add-system-defined-attributes-to-directory)
  (add-predefined-user-attributes-to-directory)

  ;; Function Names:
  (add-built-in-functions-to-directory 'function-name)

  ;; Miscellaneous Names:
  (add-semi-open-categories-to-directories)

  ;; Set up dictionaries for part types that need them.
  (set-up-part-dictionaries 'chart))


;;; `Add-special-class-names-to-foundation-class-directories' adds some
;;; additional foundation classes to the main foundation class directories.

(defun-void add-special-class-names-to-foundation-class-directories ()
  (loop for class-definition-type
        in '(foundation-connection-class
         foundation-object-class
         foundation-message-class)
    do (loop for special-class-name
             in '(gsi-message-service unique-identification)
         do (add-to-directory-of-names
              special-class-name class-definition-type))))


;;; `Add-class-and-subclasses-to-directory' ...  This is invoked by
;;; switch-to-new-empty-kb.

(defun add-class-and-subclasses-to-directory (class)
  (if t
; See note 1 below!
;      (not (or (get-class-feature-if-any class 'not-a-final-choice)
;          (get-class-feature-if-any class 'never-a-choice)))
      (add-or-delete-class-or-name-for-frame class class nil))
  (loop for subclass in (inferior-classes class)
    do (add-class-and-subclasses-to-directory
         subclass)))

;; ;; Is the test for menu choice appropriate?!!! I would think that users
;; ;; ought to be able to iterate over members of an abstract class also.
;; ;; ML, 4/1/89
;; 
;; Note 1: It is certainly not generally appropriate!  In any case, it is not
;; done for user-defined classes, why should it be done for system-defined
;; classes?  If anything, this should check if the class has the feature
;; system-internal, or a new, similar feature might be needed.  (MHD 6/6/90)





;;; System-Defined Attributes:

;;; The function `add-to-system-defined-attribute-name-directory-if-appropriate' adds
;;; the user-visible name of the slot to the system-defined-attribute-name directory
;;; when the slot description has a type feature and it fails the do-not-put-
;;; in-attribute-tables-p.

(defun add-to-system-defined-attribute-name-directory-if-appropriate
    (slot-description)
  (when (and (category-symbol-given-slot-type
           (feature-assq 'type (slot-features slot-description)))
         (not (do-not-put-slot-in-attribute-tables-p
              slot-description nil)))
    (let* ((defining-class (defining-class slot-description))
       (attribute-name
         (alias-slot-name-if-necessary
           (pretty-slot-name slot-description)
           defining-class)))
      (unless (in-directory-of-names-p
        attribute-name 'system-defined-attribute-name)
    (add-to-directory-of-names
      attribute-name 'system-defined-attribute-name))
      (add-defining-class-for-exported-attribute
    attribute-name defining-class))))
  



;;; The function `add-system-defined-attributes-to-directory' iterates over the
;;; slot-descriptions of item and its direct inferior classes and the
;;; slots-local-to-class of the reamining item classes and adds the user-
;;; visible name to the system-defined-attribute-name directory when appropriate.

(defun add-system-defined-attributes-to-directory ()
  (loop for inferior-class in (inferior-classes 'item)
    do
    (loop for slot-description in (slot-descriptions
                    (class-description inferior-class))
      do
      (add-to-system-defined-attribute-name-directory-if-appropriate
    slot-description))
    (loop for subclass being each subclass of inferior-class
      do
      (unless (eq subclass inferior-class)
    (when (cdr (direct-superior-classes subclass))
      (loop for direct-superior in (direct-superior-classes subclass)
        for superior-class-description = (class-description
                           direct-superior)
        do
        (unless (class-is-subclass-of-item? superior-class-description)
          (loop for slot-description in (slot-descriptions
                          superior-class-description)
            do
        (add-to-system-defined-attribute-name-directory-if-appropriate
          slot-description)))))
    (loop with class-description = (class-description subclass)
          for slot-name in (slots-local-to-class class-description)
          for slot-description = (get-slot-description-of-class-description
                       slot-name class-description)
          do
      (add-to-system-defined-attribute-name-directory-if-appropriate
        slot-description))))))




;;; `Predefined User Attributes' are like user-defined attributes in many ways.
;;; Unlike most user-defined attributes, however, they never take on the
;;; add-optional-subtable choice (and therefore never get the
;;; delete-optional-subtable or subtable choices).

(defparameter predefined-user-attributes
  #+obsolete                ; -jallard 5/10/97
  '((g2-user-name . g2-extension)
    (g2-user-mode . g2-window)
    (g2-connection-status . g2-extension)
    (g2-routing-information . g2-extension)
    (g2-window-management-type . g2-window))
  nil
  )

;; Commenting out the contents of this slot.  If the warning notes computations
;; through the new exported attribute facilities all works out, we should remove
;; this variable and its references.  -jallard 5/10/97

;; Note that this list competes with "authorized-system-slots" for being the
;; "right" way to do this stuff.  At least one of these should be done away
;; with.  -jra 8/24/95

;; Another competitor to virtual attributes to be removed.  FIND ME, JRA!  -jra 6/10/96

;; Note that the fact that these all begin with "g2" allows for a nice menu
;; to be put up when the user types in "g2" in the editor.

;; FACILITIES currently contains an unabstracted assq on
;; predefined-user-attributes to determine if the add-optional-subtable choice
;; must be suppressed on these slots.  Note, however, that this test was not
;; added until today, 3.1, and therefore a bug existed until now that G2 would
;; bomb out if a subtable was added as a g2-user-mode.  The bombout only
;; happened when the table was printed.  There is also a kb flag and a
;; post-loading function designed to clean up instances of g2-window that have
;; non-symbol values in their g2-user-mode slot; see comments and code with the
;; same initials/timestamp as this comment in FACILITIES, KB-LOAD1, KB-LOAD2.
;; (MHD 12/28/92)
;; --- UPDATE: The guard (in FACILITIES) was backpatched into the software in
;; 3.0 rev. 3 to keep subtables from going in, as described above, but the fixer
;; upper was not added to that version of the software.  We did not want to have
;; to backpatch the kb flag change, but at least we could keep users of the new
;; 3.0 rev from creating more problems.



(defun add-predefined-user-attributes-to-directory ()
  (loop for (attribute . class) in predefined-user-attributes
    do ; (add-to-directory-of-names attribute 'attribute-name)
       ; -- removed from directory of names.  This should
       ; be renames "install-predefined-user-attributes"!
       ; (MHD 4/21/94)
       (setf (class-and-symbol-values-for-attribute attribute)
         (frame-list (frame-list class)))))






;;; `Classes-and-directory-categories-for-namable-frames' ...

(defparameter classes-and-directory-categories-for-frame-names
    '((item
        . item-name)

      ;; When kb-workspace was workspace, the setup of more-general-
      ;;   category-symbols-with-directories did not happen so that,
      ;;   e.g., FOO would not appear twice if both ITEM-NAME and
      ;;   WORKSPACE-NAME were called for, because workspace is not
      ;;   subclass of item.  The following setup is necessary
      ;;   as a trick to get workspace-name directory to be known
      ;;   as a subset of the item-name directory.  Note that
      ;;   kb-workspace and message-board are item subclasses, and
      ;;   therefore the only classes we want to keep name
      ;;   directories for.  [However, for reasons I don't quite
      ;;   understand, things worked that way when we only had
      ;;   (workspace . workspace-name) here before anyway.]
      ;;   (MHD 6/14/90)
      (kb-workspace
        . workspace-name)
      (message-board
        . workspace-name)
      
      (object
        . object-name)
      (variable-or-parameter
        . variable-or-parameter-name)
      (g2-window
        . g2-window-name)

      (g2-list
        . g2-list-name)
      (quantity-list
       . quantity-list-name)

      ;; Add connection-name? message-name?
      
      (function-definition
        . function-name)
      (tabular-function
        . function-name)
      (foreign-function-declaration
        . function-name)
      
      (procedure
        . procedure-name)
      (remote-procedure-declaration
        . procedure-name)

      (text-conversion-style
        . text-conversion-style-name)

      (method-declaration . method-name)
      
      (image-definition                 ; Added -fmw, 1/7/94.
        . image-name)
      (frame-style-definition
        . frame-style-name)))

(defvar classes-and-directory-categories-for-classes
    '((item
        . class)
      (object
        . object-class)
      (connection
        . connection-class)
      (message
        . message-class)
      (variable-or-parameter
        . variable-or-parameter-class)
      (simulation-subtable
       . simulation-subtable-class)
      (default-junction           ; unfortunate name! (not JUNCTION
        . junction-class)             ;   for historical reasons!)
      (g2-window
        . g2-window-class)))


(defvar class-and-foundation-class-directory-categories
  '((item . foundation-class)
    (object . foundation-object-class)
    (connection . foundation-connection-class)
    (message . foundation-message-class)))

(add-grammar-rules
  '((foundation-class unreserved-symbol)
    (foundation-object-class unreserved-symbol)
    (foundation-connection-class unreserved-symbol)
    (foundation-message-class unreserved-symbol)))


;;; `Add-or-delete-class-or-name-for-frame' deletes name as instances of all the
;;; appropriate name directories, based on the class specified by class-or-
;;; namable-frame.  If class-or-namable-frame is a class (a symbol), it adds to
;;; the directories specified by classes-and-directory-categories-for-classes.
;;; Otherwise, class-or-namable-frame should be a frame, and classes-and-
;;; directory-categories-for-frame-names specifies the appropriate name
;;; directories.  

;;; If subclasses-too? is true, class-or-namable-frame must certainly be a
;;; class, and in this case, this function is called on subclasses of class-
;;; or-namable-frame recursively to all levels.

;;; Note that class-or-namable-frame is not always the same as name; e.g. when
;;; defining a new class, name is the class being defined, class-or-namable-
;;; frame is its superior class.

;;; If table-of-class-directory-pairs? is supplied, subclasses-too?
;;; must not be specified.  This is only to be called in a special
;;; recursive case from within this function, namely to add to
;;; directories of foundation classes.

(defun add-or-delete-class-or-name-for-frame
       (class-or-namable-frame name delete-case?
    &optional subclasses-too? table-of-class-directory-pairs?)
  (loop with class-case? = (symbolp class-or-namable-frame)
    with class-description? =
      (if class-case?
          (class-description class-or-namable-frame)
          (class-description-slot class-or-namable-frame))
    with inheritance-path
      = (if class-description?
        (class-inheritance-path class-description?))

    ;; Walk through all the entries in the appropriate table until
    ;; we get to the case that applies to us.  When the loop variable
    ;; 'class' is one of the superclasses of the class/frame that
    ;; we were passed in, then add (delete) it from the directory
    ;; indicated by the category-symbol given in the table. 
    for (class . category-symbol)
        in (if class-case?
           (or table-of-class-directory-pairs?
               classes-and-directory-categories-for-classes)
           classes-and-directory-categories-for-frame-names)
    when (and (inheritance-path-memq class inheritance-path)
          (null (get-slot-feature-if-any
              (if class-case?
                  class-or-namable-frame
                  (class class-or-namable-frame))
              'name-or-names-for-frame
              'local-name-or-names)))
      do
        (if delete-case?
         (delete-from-directory-of-names name category-symbol)
         (add-to-directory-of-names name category-symbol)))

  (unless table-of-class-directory-pairs?
    (when (and (symbolp class-or-namable-frame)
           (get-foundation-class-for-class class-or-namable-frame))
      ;; Classes that are foundation classes should additionally appear in a
      ;; foundation-xx-class directory. We need to do exactly the set of
      ;; operations above, so we use that code, stipulating the table through a
      ;; 2d optional argument, and using the presence of that argument to avoid
      ;; a recursive infinite loop.
      (add-or-delete-class-or-name-for-frame
    class-or-namable-frame
    class-or-namable-frame
    delete-case? nil
    class-and-foundation-class-directory-categories)))

  (if subclasses-too?
      (loop for class in (inferior-classes class-or-namable-frame)
        do (add-or-delete-class-or-name-for-frame
         class class delete-case? t))))



;;; `Set-up-more-general-category-symbols-with-directories' sets up the more-
;;; general-category-symbols-with-directories on various symbols, based partly
;;; on the state of the class system and also on various other information.  

;;; More-general-category-symbols-with-directories is used by make-category-
;;; instance-menus (q.v. in PARSE).

#+development
(defparameter variables-for-classes-and-directory-categories
          '(classes-and-directory-categories-for-frame-names
         classes-and-directory-categories-for-classes))

#+development
(loop for var in variables-for-classes-and-directory-categories
      do (pushnew var *list-of-symbols-for-symbol-value*))



;; This is to be run at start-up time primarily because it is based on the state
;; of the class system; other information is available at load/definition time.
;; In a non-development G2, this just be run at the end of loading, since it
;; only needs to know the state of the built-in class system.  This should only
;; be called from initialize-kb-name-directories.  (MHD 6/15/90)

;; The more-general-category-symbols-with-directories property is set up exclusively
;; here, and is used exclusively by the function make-category-instance-menus, in
;; PARSE.  Its purpose is to keep a directory name instance from appearing on
;; an edit menu if it is going to appear on another menu whose set of names are
;; a proper superset of it.  For example, if both variable-or-parameter-name
;; and object-name are called for, and there is a variable named FOO, this will
;; keep FOO from being displayed twice, which is both desirable and makes sense,
;; since variable is a subclass of variable-or-parameter, and variable-or-parameter
;; is a subclass of object.

;; This is not called as of 9/12/96.  It never really worked quite right.  For
;; example, it never prompted built-in function names, since it thought functions
;; were a subclass of item (which user-defined functions are). Also, it would 
;; prompt a symbol twice if it was both an item and a class, since neither of those
;; is a subclass of the other.  See make-category-instance-menus in PARSE for how
;; avoiding duplicate prompts is now handled.  (JV)





;;;; System-defined Attributes






;;; System-defined-attribute-p is true if attribute is a system defined
;;; attribute.  Attribute is assumed to be aliased, and this function unaliases
;;; as necessary.  Class? should be either nil or the name of a class.  If it is
;;; supplied non-nil, this checks if attribute is the alias for a slot defined
;;; for that class.  Otherwise, this checks if attribute is in the directory of
;;; names for system-defined-attribute-name, which directory contains the
;;; aliases of all user-visible slots found in subclasses of ITEM.

(defun system-defined-attribute-p (attribute &optional class?)
  (if class?
      (let* ((class-description? (class-description class?)))
    (when class-description?
      (let* ((unaliased-attribute-name
          (unalias-slot-name-if-necessary attribute class?))
         (slot-description?
           (get-slot-description-of-class-description
             unaliased-attribute-name class-description?)))
        (and slot-description?
         (not (user-defined-slot-description-p slot-description?))))))
      (in-directory-of-names-p attribute 'system-defined-attribute-name)))






;;;; Image definitions



;; Image-definitions live on the G2-side only.  The guts of images is in the
;; IMAGES module, which lives in both G2 and TW.  Image-definitions would like
;; to be defined in ENTITIES, but we need to call create-icon-description at
;; load-time.



(def-class (image-definition (item entity) (foundation-class image-definition)
                 define-predicate)
  ;; Enable authors attribute for this definitional item:
  (frame-author-or-authors
    nil (type authors-with-time-of-last-edit?)
    (attribute-export-comment
      "Will allow 0 or more author entries. each author entry may have a date. ~
authors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: structure, defining-class: item, writable: true
"))
  (frame-change-log nil (type frame-change-log))

  ;; This is stored as a G2 text-string, and converted to an ASCII pathname as needed.
  (file-name-of-image?
    nil (type whole-string?) user-overridable do-not-clone
    (attribute-export-comment
      "Possibly provide a structured filename part: (or none filename) Assume ~
 no change for now: (or none string)."))

  ;; By default, image data is kept in external files.
  (save-image-data-with-kb nil (type yes-or-no) user-overridable)

  ;; These slots are user-visible but read-only. They are flagged as system
  ;; slots so that they are also not readable except via the-text-of (needed since
  ;; symbol? and positive-integer? are slot types known at user level.
  (format-of-image nil (type symbol?) not-user-editable do-not-clone system
           (attribute-export-comment
             "Export as symbol (member gif ps ...)"))
  (width-of-image nil (type positive-integer?) not-user-editable do-not-clone
          system user-overridable
          (attribute-export-comment "Export as integer-range"))
  (height-of-image nil (type positive-integer?) not-user-editable do-not-clone
           system user-overridable
           (attribute-export-comment "Export as integer-range"))
  (depth-of-image nil (type positive-integer?) not-user-editable do-not-clone
          system user-overridable
          (attribute-export-comment "Export as integer-range"))

  (image-definition-cached-data?
    nil             ; An image-data object.
    (attribute-export-comment "Image-data object, internal???"))
  (image-definition-cached-data-tick
    0               ; Bumped whenever data changed.
    (attribute-export-comment "Incremented when data changed, readable???"))
  
  ;; This is kb-saveable list of all of the info from one of our image-data object.
  ;; We translate to and from this list at kb save and load time, repectively, so that
  ;; a new saveable data type is not required just for images.
  (image-definition-saveable-image-info
    nil save (attribute-export-comment "Readable???"))

  (icon-description
    (:funcall-at-load-time
      create-icon-description
      50 50
      ((lines (10 0) (10 50)) (lines (20 0) (20 50)) (lines (30 0) (30 50))
       (lines (40 0) (40 50)) (lines (0 10) (50 10)) (lines (0 20) (50 20))
       (lines (0 30) (50 30)) (lines (0 40) (50 40))
       (solid-rectangle (10 10) (20 20))
       (solid-rectangle (30 20) (40 30))
       (solid-rectangle (20 30) (30 40))
       (outline (0 0) (0 50) (50 50) (50 0))))

    (attribute-export-comment
      "Should we handle exporting of this icon-description, which is defined ~
 on the class rather than inherited, differently from those on most other classes?"))
  (image-definition-media-bin nil save))

;; (1) Do not clone the filename, since that means we would have to re-read
;;    the file, creating a new image object.
;;    If in the next G2 we have reference-counted shared image-data, then we
;;    could allow this.
;; (2) Generalize to source-of-image: "File <filename>, Array <arrayname>"

(define-slot-alias file-name-of-image file-name-of-image? image-definition)


(defun image-definition-data? (image)
  (image-definition-cached-data? image))


;; The old name of this slot, which exists in some 4.0-alpha kbs.

(def-absent-slot-putter filename-of-image (image-definition value)
  (dwarn "For ~s: the filename-of-image attribute is obsolete.  Please use file-name-of-image."
     image-definition)
  (setf (file-name-of-image? image-definition) value))



;;; The class-method `initialize' is called after a new instance has
;;; been created either by make-frame or by clone-frame.  Is not
;;; not called if the frame was created by kb-loading. (See next)

(def-class-method initialize (image-definition)
  (funcall-superior-method image-definition)
  (ensure-image-definition-data image-definition)
  (funcall-method-if-any 'update-frame-status-and-notes image-definition))


;;; The class-method `initialize-after-reading' is called by kb-load INSTEAD of
;;; the `initialize' method.

(def-class-method initialize-after-reading (image-definition)
  (funcall-superior-method image-definition)
  (ensure-image-definition-data image-definition)
  (funcall-method-if-any 'update-frame-status-and-notes image-definition))


;;; The constant `allowed-image-formats' includes the secret easter egg format,
;;; PBM (portable bit map).

(defconstant allowed-image-formats '(gif jpeg png xbm pbm))


(def-frame-note-writer image-definition-file-name-is-empty (particulars)
  (declare (ignore particulars))
  (tformat "the file name of image is missing"))

(def-frame-note-writer image-definition-file-not-found (particulars)
  (declare (ignore particulars))
  (tformat "the file for this image was not found"))

(def-frame-note-writer image-definition-file-unknown-format (particulars)
  (declare (ignore particulars))
  (tformat "the file for this image is not in a recognized format (GIF, JPEG, PNG or XBM)"))



;;; The function `current-kb-directory?' returns a NEWLY CONSED gensym pathname
;;; for the directory from which the current KB was or is being loaded.

(defun current-kb-directory? ()
  (let ((pathname?
      (or (if (and (boundp 'main-kb-being-read?)
               (boundp 'namestring-for-kb-being-read)
               main-kb-being-read?)
          namestring-for-kb-being-read)
          current-kb-pathname?)))
    (when pathname?
      (let ((namestring (os-pathname-directory pathname? g2-operating-system)))
    (prog1 (gensym-pathname namestring)
      (reclaim-text-string namestring))))))

;; During loading, current-kb-pathname? is for the previous KB, so we have to
;; look ahead into namestring-for-kb-being-read.  But not if we are only
;; merging!



;;; The function `full-pathname-of-image?' returns a newly consed
;;; gensym-pathname, which is the fully specified pathname of the image's data
;;; file. Or it returns NIL.

(defun full-pathname-of-image? (image-definition)
  (let* ((filename-as-text-string?
       (file-name-of-image? image-definition))
     (ascii-filename?
       (and filename-as-text-string?
        (convert-text-string-to-ascii-filename-as-much-as-possible
          filename-as-text-string?))))
    (when ascii-filename?
      (let ((kb-directory? (current-kb-directory?)))
    (prog1 (gensym-merge-pathnames ascii-filename?
                       (or kb-directory?
                       process-specific-system-pathname))
      (reclaim-text-string ascii-filename?)
      (when kb-directory?
        (reclaim-gensym-pathname kb-directory?)))))))


(def-class-method update-frame-status-and-notes (image-definition)
  (with-updates-to-representations-supressed
      (image-definition 'frame-status-and-notes)
    (funcall-superior-method image-definition)

    (let ((frame-status? nil)                   ; aka OK
      (pathname? (full-pathname-of-image? image-definition)))

      (delete-frame-note-if-any 'image-definition-file-name-is-empty image-definition)
      (delete-frame-note-if-any 'image-definition-file-not-found image-definition)
      (delete-frame-note-if-any 'image-definition-file-unknown-format image-definition)

      (cond ((null pathname?)
         (unless (image-definition-cached-data? image-definition)
           (add-frame-note 'image-definition-file-name-is-empty image-definition)
           (setq frame-status? 'incomplete)))

        ((not (file-exists-p pathname?))
         (add-frame-note 'image-definition-file-not-found image-definition)
         ;; Force it back to "none" if no file and no data.
         ;; If we do have data, then it must have come from the kb-load.
         ;; Note that?
         ;;  This is no good.  We should be clearing width,height, etc, too,
         ;; at least after the user edits the pathname.
         (when (and (format-of-image image-definition)
            (null (image-definition-data? image-definition)))
           (change-slot-value image-definition 'format-of-image nil))
         ;; Don't become BAD (implies become inactive).
         (setq frame-status? 'incomplete))

        ((not (memq (format-of-image image-definition) allowed-image-formats))
         (add-frame-note 'image-definition-file-unknown-format image-definition)
         (setf frame-status? 'incomplete)))
      
      ;; If we have data after all, then we are actually OK, but leave the notes.
      ;; This how we reflect the hidden state that the iamge data was read from
      ;; the KB, and the file does not exist.
      (when (image-definition-data? image-definition)
    (setq frame-status? nil))

      (when pathname?
    (reclaim-gensym-pathname pathname?))
      
      (update-frame-status image-definition frame-status? nil))))



;;; The slot-putter `file-name-of-image?' needs to read the new image data and
;;; update any icons or workspaces which depend on it.  If the new pathname is
;;; string-equal to the old, then we assume that nothing needs to be done.  The
;;; slot is maintained as a G2 text-string, and is converted into an ASCII
;;; pathname only when we need to do file operations.

(def-slot-putter file-name-of-image? (image-definition new-pathname? initializing?)
  (setf (file-name-of-image? image-definition) new-pathname?)

  (unless initializing?
    (refresh-image-definition-from-file image-definition))

  new-pathname?)



(def-slot-putter save-image-data-with-kb (image-definition new-value initializing?)
  (declare (ignore initializing?))
  (setf (save-image-data-with-kb image-definition) new-value)
  (when (null new-value)
    (discard-existing-image-info image-definition)))

;; The discard wants to be done after KB-save completes, but since we have no
;; hook for that, we keep it around until the user changes this slot to NO.



;;; Make sure we delete the media-bin when the image-definition
;;; is deleted.

(def-slot-value-reclaimer image-definition-media-bin (media-bin)
  (when media-bin
    (delete-frame media-bin)))

;;; The function `refresh-image-definition-from-file' clears the cached data,
;;; if any, for the image and then tries to re-read data from the current
;;; filename.  It is used by the g2-refresh-image-definition sysproc.

(defun refresh-image-definition-from-file (image-definition)
  (let ((pathname? (full-pathname-of-image? image-definition)))

    (when (and (image-definition-cached-data? image-definition)
           (or pathname?
           (not (save-image-data-with-kb image-definition))))
      (reclaim-image-data (image-definition-cached-data? image-definition))
      (setf (image-definition-cached-data? image-definition) nil)
      (discard-existing-image-info image-definition))

    (when pathname?
      ;; There is a bug that changing file-name-of-image to "none" does not
      ;; redraw affected workspaces.  Calling ensure-image-definition-data
      ;; outside the when fixes that, but it may possibly break GMS, which sets
      ;; the filename none while saving the image data with the KB.  So we defer
      ;; the fix for a bit. -fmw, 1/31/02
      (ensure-image-definition-data image-definition)
      (let ((image-definition-data?
          (image-definition-data? image-definition)))
    (setf (image-definition-saveable-image-info image-definition)
          (if (and (save-image-data-with-kb image-definition)
               image-definition-data?)
          (construct-image-info-from-image-data image-definition-data?)
          nil))))

    (funcall-method-if-any 'update-frame-status-and-notes image-definition)

    (when pathname?
      (reclaim-gensym-pathname pathname?))

    ;; update media bin only if cached
    (when (image-definition-media-bin image-definition)
      (cache-media-bin-if-possible image-definition t))
    
    image-definition))



;;; The function `analyze-items-which-refer-to-us-by-name' re-analyzes all
;;; items which refer to us by any of our names.  In the case of image definitions,
;;; this should be called whenever our image data changes.

(defun analyze-items-which-refer-to-us-by-name (block)
  (let ((names (name-or-names-for-frame block)))
    (cond ((null names))
      ((atom names)
       (analyze-compiled-items-for-consistency names))
      (t
       (loop for name in names doing
         (analyze-compiled-items-for-consistency name))))))



;;; The function `copy-image-data-slots-into-image-definition' copys some
;;; useful info into up into the image-definition slots, where they can be seen
;;; by the user.

(defun copy-image-data-slots-into-image-definition (image-definition image-data?)
  (change-slot-value image-definition 'width-of-image
             (and image-data? (image-data-width image-data?)))
  (change-slot-value image-definition 'height-of-image
             (and image-data? (image-data-height image-data?)))
  (change-slot-value image-definition 'depth-of-image
             (and image-data? (image-data-depth image-data?)))
  (change-slot-value image-definition 'format-of-image
             (and image-data? (image-data-format image-data?))))



;;; The function `prepare-image-definitions-for-saving' is called directly by
;;; save-kb.  Too bad we can't prepare only those image definitions which are
;;; actually touched by this save.

(defun prepare-image-definitions-for-saving ()
  (loop for image-definition being each class-instance of 'image-definition
    when (save-image-data-with-kb image-definition)
      do (prepare-image-definition-for-kb-save image-definition)))




;;; The function `prepare-image-definition-for-kb-save' copies any cached
;;; image-data we have into the saveable image-info slot.

(defun prepare-image-definition-for-kb-save (image-definition)
  (discard-existing-image-info image-definition)
  (when (image-definition-data? image-definition)
    (setf (image-definition-saveable-image-info image-definition)
      (construct-image-info-from-image-data (image-definition-data? image-definition)))))


(defun discard-existing-image-info (image-definition)
  (let ((old-image-info? (image-definition-saveable-image-info image-definition)))
    (when old-image-info?
      (setf (image-definition-saveable-image-info image-definition) nil)
      (reclaim-image-info old-image-info?))))



;;; The function `construct-image-info-from-image-data' contructs the image-info
;;; plist, which is a kb-saveable data structure.  We share the color-map and
;;; the byte vectors from the image data, but copy everything else.

(defun construct-image-info-from-image-data (image-data)
  (slot-value-list
    'image-info
    'pathname (copy-text-string (image-data-pathname image-data)) ; ASCII full pathname.
    'number-of-colors (image-data-number-of-colors image-data)
    'format (image-data-format image-data)
    'width (image-data-width image-data)
    'height (image-data-height image-data)
    'depth (image-data-depth image-data)
    'transparent-color-index (image-data-transparent-color-index image-data)
    'byte-code-bodies           ; Later, perhaps, 'compressed-bytes, etc.
    (when (ensure-image-data-pixels image-data)
      (let ((shredded-raster? (image-data-cache? image-data)))
    (when shredded-raster?
      (loop for i below (shredded-raster-height shredded-raster?)
        as buffer = (shredded-raster-buffer shredded-raster? i)
        as length = (length buffer)
        collect (make-byte-code-body length buffer nil nil nil)
          using slot-value-cons))))
    ;; HQ-4752588: Grab color map *after* ensure-image-data-pixels
    'color-map (image-data-color-map image-data))) ; Managed arrays are saveable.

;; Note that this image-info shares the color map and the byte vectors with image-data.


;;; The function `reclaim-image-info' reclaims an image-info plist as
;;; constructed by the above function.  It knows what was shared with
;;; the image-definition (namely, color map and byte vectors), and carefully
;;; skips reclaiming them.

(defun reclaim-image-info (image-info)
  (let* ((plist (cdr image-info))
     (byte-code-bodies (getf plist 'byte-code-bodies))
     (pathname (getf plist 'pathname)))
    (loop for byte-code-body in byte-code-bodies doing
      ;; I do not want to reclaim the byte-vector.  However, reclaim-byte-code-body
      ;; expects there to be one.  So, we have to stuff in a new one.
      (setf (byte-code-body-byte-vector byte-code-body) (allocate-byte-vector 1))
      (reclaim-byte-code-body byte-code-body))
    (reclaim-slot-value-list byte-code-bodies)
    (reclaim-slot-value-list image-info)
    (reclaim-text-string pathname)))




;;; The function `construct-image-data-from-image-info' creates an image-data
;;; object from the image-info, as stored in a KB.  All of the objects in
;;; image-info are either reclaimed or moved into the image-data object.

(defun construct-image-data-from-image-info (image-info)
  (let* ((plist (cdr image-info))
     (image-data (make-image-data
               (getf plist 'pathname)           ; Ascii
               (getf plist 'width)
               (getf plist 'height)
               (getf plist 'depth)
               (getf plist 'format)
               (getf plist 'number-of-colors)
               (getf plist 'color-map)
               (getf plist 'transparent-color-index)))
     (height (image-data-height image-data))
     (shredded-raster (allocate-shredded-raster
                (image-data-width image-data)
                (image-data-height image-data)
                (image-data-depth image-data)
                (image-data-number-of-colors image-data)
                (image-data-color-map image-data)
                (image-data-transparent-color-index image-data)))
     (byte-code-bodies (getf plist 'byte-code-bodies)))

    (loop for byte-code-body in byte-code-bodies
      as i below height
      as byte-vector = (byte-code-body-byte-vector byte-code-body)
      doing
      (setf (shredded-raster-buffer shredded-raster i) byte-vector))

    (reclaim-image-info image-info)

    (setf (image-data-cache? image-data) shredded-raster)
    (setf (image-data-was-constructed-p image-data) t)
    image-data))



(def-virtual-attribute image-data
    ((class image-definition)
     (or (no-item)
     (structure ((pathname text)
             (number-of-colors integer)
             (color-map (sequence integer))
             (format datum)
             (width integer)
             (height integer)
             (depth integer)
             (transparent-color-index datum)
             (contents (or integer
                   (sequence text))))
            (and pathname width height depth contents
             number-of-colors color-map)))
     ())
  :event-updates nil
  :initial
  ((class)
   (declare (ignore class))
   nil)
  :getter
  ((image-definition)
   (let ((image-data (image-definition-data? image-definition)))
     (when image-data
       (allocate-evaluation-structure-inline
     'pathname (copy-text-string (image-data-pathname image-data))
     'number-of-colors (image-data-number-of-colors image-data)
     'color-map (allocate-evaluation-sequence
              (loop with map = (image-data-color-map image-data)
                for i from 0 below (managed-array-length map)
                collect (managed-svref map i)
                  using eval-cons))
     'format (image-data-format image-data)
     'width (image-data-width image-data)
     'height (image-data-height image-data)
     'depth (image-data-depth image-data)
     'transparent-color-index (image-data-transparent-color-index image-data)
     'contents 
     (when (ensure-image-data-pixels image-data)
       (let ((shredded-raster? (image-data-cache? image-data)))
         (when shredded-raster?
           (allocate-evaluation-sequence
         (loop with length = (length (shredded-raster-buffer shredded-raster? 0))
               with wlength = (ceilingf length 2)
               for i below (shredded-raster-height shredded-raster?)
               for buffer = (shredded-raster-buffer shredded-raster? i)
               for text-string = (make-wide-string wlength)
               do (loop for wj from 0 below (ashf length -1)
                for j from 0 by 2
                do (setf (charw text-string wj)
                     (code-wide-character
                       (+f (byte-vector-aref buffer j)
                           (ashf (byte-vector-aref buffer (1+f j)) 8)))))
              (when (=f 1 (logandf length 1))
                (setf (charw text-string (1-f wlength))
                  (code-wide-character (byte-vector-aref buffer (1-f length)))))
               collect (mark-wide-string-as-binary text-string)
             using eval-cons)))))))))
  :setter
  ((image-definition new-value)
   (when (evaluation-structure-p new-value)
     (let* ((pathname (evaluation-structure-slot new-value 'pathname))
        (number-of-colors (evaluation-structure-slot new-value 'number-of-colors))
        (color-map-value (evaluation-structure-slot new-value 'color-map))
        (color-map (allocate-managed-array (evaluation-sequence-length color-map-value)))
        (format (evaluation-structure-slot new-value 'format))
        (width (evaluation-structure-slot new-value 'width))
        (height (evaluation-structure-slot new-value 'height))
        (depth (evaluation-structure-slot new-value 'depth))
        (transparent-color-index (evaluation-structure-slot new-value 'transparent-color-index))
        (contents (evaluation-structure-slot new-value 'contents))
        (contents-sequence-p (evaluation-sequence-p contents)))
       (cond
     ((or (>f width maximum-size-of-images)
          (>f height maximum-size-of-images)
          (not (or (=f depth 1) (=f depth 8) (=f depth 24))))
      (copy-text-string #w"bad image contents"))
     ((and contents-sequence-p
           (not (and (=f height (evaluation-sequence-length contents))
             (loop with length = (unaligned-bytes-per-scan-line width depth)
                   for text-string being each evaluation-sequence-element of contents
                   thereis (>=f (ashf (lengthw text-string) 1) length)))))
      (copy-text-string #w"bad image contents"))
     (t
      (let* ((image-data
           (make-image-data
             pathname width height depth format
             number-of-colors color-map transparent-color-index))
         (shredded-raster
           (allocate-shredded-raster
             width height depth
             number-of-colors color-map contents-sequence-p
             transparent-color-index)))
        (loop for i from 0
          for element being each evaluation-sequence-element of color-map-value
          do (setf (managed-svref color-map i) element))
        (when contents-sequence-p
          (loop with length = (length (shredded-raster-buffer shredded-raster 0))
            with wlength = (ceilingf length 2)
            for i from 0 below height
            for buffer = (shredded-raster-buffer shredded-raster i)
            for text-string being each evaluation-sequence-element of contents
            do (loop for wj from 0 below (ashf length -1)
                 for j from 0 by 2
                 for wchar = (wide-character-code (charw text-string wj))
                 do (setf (byte-vector-aref buffer j) (logandf #xff wchar))
                (setf (byte-vector-aref buffer (1+f j)) (ashf wchar -8)))
               (when (=f 1 (logandf length 1))
             (setf (byte-vector-aref buffer (1-f length))
                   (wide-character-code (charw text-string (1-f wlength)))))))
        (setf (image-data-cache? image-data) shredded-raster)
        (setf (image-definition-cached-data? image-definition) image-data)
        (setf (image-data-was-constructed-p image-data) t)
        nil)))))))


;;; The class-method `cleanup' is called by delete-frame before it starts
;;; reclaiming any slots.  It ought also to refresh any workspace or block
;;; which used us as a background or icon region.

(def-class-method cleanup (image-definition)
  (funcall-superior-method image-definition)
  (let ((image-data? (image-definition-cached-data? image-definition))
    (image-info? (image-definition-saveable-image-info image-definition)))
    (when image-data?
      (reclaim-image-data image-data?)
      (setf (image-definition-cached-data? image-definition) nil)
      (incff (image-definition-cached-data-tick image-definition)))
    (when image-info?
      (reclaim-image-info image-info?)
      (setf (image-definition-saveable-image-info image-definition) nil))))


;;; The function `find-image-named' returns an image-definition instance, or
;;; NIL.

(defun find-image-named (name)
  (or (get-instance-with-name-if-any 'image-definition name)
      #+rh-gensym-logo
      (and (memq name list-of-built-in-image-definitions)
       (construct-built-in-image-definition name))))

#+rh-gensym-logo
(defun construct-built-in-image-definition (image-name)
  (let ((image-definition (make-frame-without-computed-initializations
               (class-description 'image-definition)
               nil nil)))
    (change-slot-value image-definition 'name-or-names-for-frame image-name)
    (setf (image-definition-saveable-image-info image-definition)
      (get-savable-image-info-for-image-name image-name))
    (funcall-method 'initialize-after-reading image-definition)
    image-definition))


;;; The function `find-image-data' returns an image-data structure,
;;; or nil.

(defun find-image-data (image-name)
  (let ((image-definition? (find-image-named image-name)))
    (when image-definition?
      (image-definition-data? image-definition?))))


(defun has-background-images-p (workspace)
  (loop for (image-name) in (workspace-background-images workspace)
    thereis (find-image-data image-name)))



;;; The function `ensure-image-definition-data' returns the image-data
;;; for the image definition, if any.  If we already have data, we simply
;;; return it.  if we do not, we try to construct data from either the
;;; image-info from the last kb-load or from our pathname.

;;; Note that this function now reads only the file header, not the pixels.

(defun ensure-image-definition-data (image-definition)
  (let ((image-data? (image-definition-cached-data? image-definition))
    (image-info? (image-definition-saveable-image-info image-definition))
    (pathname? (full-pathname-of-image? image-definition)))
    ;; Construct image data either from kb-loaded image-info,
    ;; or by reading from pathname.
    (cond (image-data?)
      (image-info?
       (setf image-data? (construct-image-data-from-image-info image-info?)
         (image-definition-saveable-image-info image-definition) nil))
      (pathname?
       (let ((namestring                    ; Ascii?
           (gensym-namestring pathname?)))
         (setf image-data? (make-image-data namestring))
         (read-image-data-header image-data?) ; Only need the header so far.
         (reclaim-text-string namestring))))

    ;; Update slots in the image-definition, whether or not we got data.
    (copy-image-data-slots-into-image-definition image-definition image-data?)

    (cond ((null image-data?))
      ((null (image-data-cache? image-data?))
       (reclaim-image-data image-data?)
       (setq image-data? nil)
       (setf (image-definition-cached-data? image-definition) nil)
       (setf (image-definition-media-bin image-definition) nil))
      (t
       (setf (image-definition-cached-data? image-definition) image-data?
         (image-data-image? image-data?) image-definition)
       (incff (image-definition-cached-data-tick image-definition))))

    ;; Data has changed
    (analyze-items-which-refer-to-us-by-name image-definition)
    (when pathname?
      (reclaim-gensym-pathname pathname?))
    image-data?))


;;; `Draw-empty-image-in-current-window' is used to draw an image onto a
;;; telewindow which does not support image drawing.

(defun draw-empty-image-in-current-window (image-data x-in-window y-in-window
                              left top right bottom
                              x-scale y-scale
                              rotation quality
                              foreground background)
  (declare (ignore rotation foreground))
  (cond ((eq quality 'tiled)
     (draw-solid-rectangle left top right bottom
                   (color-difference background
                         current-background-color-value)))
    (t
     (let* ((width (image-data-width image-data))
        (height (image-data-height image-data))
        (dw (delta-x-in-window width x-scale))
        (dh (delta-y-in-window height y-scale))
        (x1 (maxr left x-in-window))
        (y1 (maxr top y-in-window))
        (x2 (minr right (+r x-in-window dw)))
        (y2 (minr bottom (+r y-in-window dh))))
       ;; Perhaps, pick a color which best represents the image?
       (when (and (<r x1 x2) (<r y1 y2))
         (draw-solid-rectangle x1 y1 x2 y2
                   (color-difference (map-to-color-value 'gray)
                             current-background-color-value)))))))



(defun invalidate-all-image-renderings ()
  ;; Invalidate all current renderings.
  (loop for image-definition being class-instances of 'image-definition doing
    (incff (image-definition-cached-data-tick image-definition)))

  ;; Invalidate affected workspace regions.
  (loop for workspace being class-instances of 'kb-workspace doing
    (when (background-images workspace)
      (refresh-background-images workspace))))

    


;;;; Interface between image backgrounds and drawing


(def-substitution-macro image-spec-image-definition? (image-spec)
  (find-image-named (image-spec-image-name image-spec)))



;;; The substitution-macro `compute-image-position' returns the position of the
;;; upper-left corner of the image in workspace coordinates, given the
;;; coordinates as specified by the user in the background-images slot.

(def-substitution-macro compute-image-position (image-data x-user y-user)
  (values (-r x-user (floorf-positive (image-data-width image-data) 2))
      (-r (-r y-user) (floorf-positive (image-data-height image-data) 2))))





;;; The function `draw-background-images' is called by
;;; `draw-paper-for-current-image-plane'.  LTRB are window coordinates of the
;;; rectangle to refresh which presumably overlaps the image someplace.  State?
;;; is either NIL or the index of the next image to draw.

(defun draw-background-images (image-plane state? left top right bottom)
  (let* ((foreground (compute-workspace-foreground-color-value image-plane))
     (background (compute-workspace-background-color-value image-plane))
     (background-images (image-plane-background-images image-plane))
     (next-image (or state? 0)))
    (loop as image-spec = (nth next-image background-images)
      while image-spec
      as image-name = (image-spec-image-name image-spec)
      as x-user = (image-spec-user-x-position image-spec)
      as y-user = (image-spec-user-y-position image-spec)
      as tiled? = (image-spec-tiled-p image-spec)
      as image-data? = (find-image-data image-name)
      as proceed = (or (null image-data?)
               (draw-background-image
                 current-image-plane image-data? x-user y-user tiled?
                 left top right bottom
                 foreground background))
      do (if proceed (incff next-image))
      while proceed
;     until (or (not proceed)
;           (drawing-time-slice-expired-p))
      finally
        (return
          (and (<f next-image (length background-images))
           next-image)))))

;; Image-plane must be on the current-window.


;;; The function `draw-background-image' draws the given workspace background
;;; image and returns T if it finished doing so. At the moment, it always
;;; finishes the drawing and always returns T.

(defun draw-background-image (image-plane image-data x-user y-user tiled?
                      left top right bottom
                      foreground background)
  (let ((x-in-window nil)
    (y-in-window nil)
    (quality (if tiled? 'tiled))
    (done nil))
    (multiple-value-bind (left-in-workspace top-in-workspace)
    (compute-image-position image-data x-user y-user)
      ;; The fact that I need this wrapper indicates some modularity problem.
      (with-image-plane-transform (image-plane)
    (setf x-in-window (x-in-window left-in-workspace))
    (setf y-in-window (y-in-window top-in-workspace))

    (cond ((not (window-supports-painting-this-image-data current-window image-data))
           (draw-empty-image-in-current-window
         image-data x-in-window y-in-window
         left top right bottom current-image-x-scale current-image-y-scale
         nil quality
         foreground background)
           (setq done t))

          ((icp-window-p current-window)
           (unless (finished-transmitting-image-data-p image-data)
         (when (icp-connection-open-p current-icp-socket)
           (send-all-image-data image-data)))

           (cond ((not (icp-connection-open-p current-icp-socket))
              ;; Even if the ICP connection is closed, ensure that our
              ;; state variable is advanced.  This change was patched into
              ;; the C sources by hand.  -fmw, 6/23/95
              (setq done t))
             ((finished-transmitting-image-data-p image-data)
              (draw-image
            image-data x-in-window y-in-window
            left top right bottom
            current-image-x-scale current-image-y-scale
            nil quality
            foreground background)
              (setq done t))))
          (t                    ; X11 or printing window.
           (draw-image
         image-data x-in-window y-in-window
         left top right bottom
         current-image-x-scale current-image-y-scale
         nil quality
         foreground background)
           (setq done t)))))
    done))

;; If the time-slice is unlimited, then the caller is not prepared for a
;; premature return, so don't allow it.  This means that we could clog the ICP
;; connection once again.


;;; The function `compute-image-spec-info' returns a newly consed list of info
;;; about the current image represented by image-spec. The format of this list
;;; in known only by this routine and by refresh-background-images.

(defun compute-image-spec-info (workspace image-spec)
  (let ((image-definition? nil)
    (image-data? nil)
    (left nil)
    (top nil)
    (right nil)
    (bottom nil)
    (tick nil)
    (serial nil)
    (x (image-spec-user-x-position image-spec))
    (y (image-spec-user-y-position image-spec))
    (tiled? (image-spec-tiled-p image-spec)))

    ;; Fill in as many of the info slots as we can.
    (cond ((null (setq image-definition? (image-spec-image-definition? image-spec))))
      (t
       (setq tick (image-definition-cached-data-tick image-definition?)
         serial (frame-serial-number image-definition?))
       (cond ((null (setq image-data? (image-definition-data? image-definition?))))
         ((null (image-data-cache? image-data?)))
         (tiled?
          ;; A tiled image covers the entire workspace interior. Since
          ;; that may have changed since this image-info was cached, our
          ;; caller actually recomputes these edges.
          (setq left (left-edge-of-block workspace)
            top (top-edge-of-block workspace)
            right (right-edge-of-block workspace)
            bottom (bottom-edge-of-block workspace)))
         (t
          (multiple-value-setq (left top)
            (compute-image-position image-data? x y))
          (setq right (+r left (image-data-width image-data?))
            bottom (+r top (image-data-height image-data?)))))))
    
    (slot-value-list image-definition? (copy-frame-serial-number serial)
             tick left top right bottom x y tiled?)))



;;; The function `refresh-background-images' incrementally refreshes regions of
;;; the workspace whose background images have changed since the last refresh.
;;; We also take care of enlarging the workspace as needed to contain all of
;;; the current images.  All coordinates here are in workspace units.
;;;  We attempt to handle only a few incremental cases here:
;;;    (1) If images added or deleted at the end of the list, then images in the
;;;        common leading sublist do not cause region invalidations
;;;    (2) If before and after lists are the same length, then images at corresponding
;;;        positions which have not changed do not cause an invalidation.

(defun refresh-background-images (workspace)
  (let* ((previous-images-info
       (workspace-previous-background-images-info workspace))
     (present-images
       (workspace-background-images workspace))
     (new-images-info
       (loop for new-image-spec in present-images
         collect (compute-image-spec-info workspace new-image-spec)
           using slot-value-cons))
     (region-to-invalidate
       (make-empty-region)))

    (loop with previous-images-info-list = previous-images-info
      with new-images-info-list = new-images-info
      as previous-image-info = (pop previous-images-info-list)
      as new-image-info = (pop new-images-info-list)
      while (or previous-image-info new-image-info)
      doing
      (gensym-dstruct-bind ((old-image-definition? frame-serial-number
                          tick left top right bottom x y old-tiled-p)
               previous-image-info)
    (when old-tiled-p       ; If workspace changed size, need new values here.
      (setq left (left-edge-of-block workspace)
        top (top-edge-of-block workspace)
        right (right-edge-of-block workspace)
        bottom (bottom-edge-of-block workspace)))
    (gensym-dstruct-bind ((new-image-definition? nil
                            new-tick new-left new-top new-right new-bottom
                            new-x new-y new-tiled-p)
                          new-image-info)
      (when (and new-left new-top new-right new-bottom (not new-tiled-p))
        (enlarge-workspace-if-necessary workspace new-left new-top new-right new-bottom))
      
      (when (or (neq old-image-definition? new-image-definition?)
            ;; If old image has been recycled, or changed, invalidate its region.
            (and old-image-definition?
             (frame-has-been-reprocessed-p old-image-definition? frame-serial-number))
            (and old-image-definition? new-image-definition?
             (or (not (eql tick new-tick))
                 (not (eql left new-left))
                 (not (eql top new-top))
                 (not (eql right new-right))
                 (not (eql bottom new-bottom))
                 (not (eql x new-x))
                 (not (eql y new-y))
                 (neq old-tiled-p new-tiled-p))))
        (when left
          (setq region-to-invalidate
            (add-rectangle-to-region left top right bottom
                         region-to-invalidate)))
        (when new-left
          (setq region-to-invalidate
            (add-rectangle-to-region new-left new-top new-right new-bottom
                         region-to-invalidate)))))))

    ;; Save the new info.
    (setf (workspace-previous-background-images-info workspace) new-images-info)
    (reclaim-background-images-info previous-images-info)

    ;; Invalidate, without the sketch, which would make movies flash.
    (let ((current-draw-paper-p nil))
      (invalidate-region-of-workspace workspace region-to-invalidate
                      ':bleeding-on-all-sides))
    ;; The bleeding works around bug HQ-352777.
    
    (reclaim-region region-to-invalidate)
    (values)))





;;;; Workspace backgrounds





(def-slot-putter workspace-background-color? (workspace new-value initializing?)
  (cond ((and (null new-value) (null (workspace-background-color? workspace))) ; Optimization
     (values nil nil))
    (t
     (without-consistency-analysis (workspace)
       (setf (workspace-background-color? workspace) new-value)

       (unless (or initializing?
               (frame-being-deleted-p workspace))
         (when (eq (unused-area-color? workspace) 'same-as-workspace)
           (synchronize-unused-area-color workspace))
         (invalidate-workspace workspace)))
     (values new-value t))))

(def-slot-putter workspace-foreground-color? (workspace new-value initializing?)
  (cond ((and (null new-value) (null (workspace-foreground-color? workspace))) ; Optimization
     (values nil nil))
    (t
     (without-consistency-analysis (workspace)
       (setf (workspace-foreground-color? workspace) new-value)

       (unless (or initializing?
               (frame-being-deleted-p workspace))
         (invalidate-workspace workspace)))
     
     (values new-value t))))


;;; The substitution-macro `default-position-of-image-upon-workspace' returns
;;; the default position of an image on the given workspace, in the
;;; *user-visible* workspace coordinates (negated y).

(def-substitution-macro default-position-of-image-upon-workspace (workspace)
  (values (floorf-positive (+w (left-edge-of-block workspace)
                   (right-edge-of-block workspace))
               2)
      (-w (floorf-positive (+w (top-edge-of-block workspace)
                   (bottom-edge-of-block workspace))
                   2))))

;; The default is now the workspace center, usually 0 for new workspaces.
  


;;; The function `mark-background-image-coordinates-as-needing-update' is
;;; called during the reading of a workpsace from a KB old enough to have
;;; upper-left relative background-image coordinates.  We simply mark the
;;; workspace as such, and clean the thing up in the post-loading function,
;;; below.  The cleanup must be delayed until all image-definitions have been
;;; loaded.

(defun mark-background-image-coordinates-as-needing-update (workspace)
  (when (background-images workspace)
    (slot-value-push :upper-left-relative (background-images workspace))))
    

;;; The function `center-workspace-background-images-after-loading' is
;;; called by a KB post-loading function.

(defun center-workspace-background-images-after-loading ()
  (loop for workspace being each class-instance of 'workspace
    doing
    (recenter-background-images-of-workspace workspace)))


(defun recenter-background-images-of-workspace (workspace)
  (when (and (background-images workspace)
         (eq (car (background-images workspace))
         :upper-left-relative))
    ;; Get rid of the bogus token NOW.
    (slot-value-pop (background-images workspace))

    (loop for image-spec in (background-images workspace)
      as image-name = (image-spec-image-name image-spec)
      as image-defn? = (image-spec-image-definition? image-spec)
      as width? = (and image-defn? (width-of-image image-defn?))
      as height? = (and image-defn? (height-of-image image-defn?))
      collect (if (and width? height?)
              (slot-value-list 
            image-name
            (incff (image-spec-user-x-position image-spec)
                   (floorf-positive width? 2))
            (decff (image-spec-user-y-position image-spec)
                   (floorf-positive height? 2)))
              (slot-value-list
            image-name
            (image-spec-user-x-position image-spec)           
            (image-spec-user-y-position image-spec)))
        into new-value using slot-value-cons
      finally
        (change-slot-value workspace 'background-images new-value))))

;;; The slot-putter for `background-images' assigns x,y positions for all
;;; images which did not have the "at" clause.  It either copies the position
;;; from the corresponding previous image, or computes a default.

(def-slot-putter background-images (workspace new-value initializing?)
  (cond ((and (null new-value) (null (background-images workspace))) ; Optimization
     (values nil nil))

    (t
     (when (and (consp new-value)               ; Bug?
            (eq (car new-value) '\,))
       (slot-value-pop new-value))
     (when (and new-value (atom new-value))         ; Bug?
       (setq new-value (slot-value-list new-value)))
     
     (let* ((old-background-images (background-images workspace))
        (new-background-images
          ;; In so far as possible, copy x,y coordinates from the old images.
          (loop with images = old-background-images
            for image-spec in new-value
            as old-image-spec = (pop images)
            collect (cond ((consp image-spec)
                       (copy-list-using-slot-value-conses image-spec))
                      ((consp old-image-spec) ; Should always be true if non-NIL
                       (slot-value-list image-spec
                            (second old-image-spec)
                            (third old-image-spec)))
                      (t
                       (multiple-value-bind (x y)
                       (default-position-of-image-upon-workspace workspace)
                     (slot-value-list image-spec x y))))
              using slot-value-cons)))

       ;; Does this take care of all the refreshing?
       (without-consistency-analysis (workspace)
         (setf (background-images workspace) new-background-images))

       (unless (or initializing?
               (equal new-background-images old-background-images)
               (frame-being-deleted-p workspace))
         (refresh-background-images workspace))

       (reclaim-slot-value-tree old-background-images)
       (reclaim-slot-value-tree new-value)
       
       (values new-background-images t)))))



  
;;; The defun-void `update-extreme-edges-from-background-images' adds the size
;;; of each background image to the extreme edges of the interior of a
;;; workspace.

(defun-void update-extreme-edges-from-background-images (workspace)
  (loop for image-spec in (workspace-background-images workspace)
    as image-name = (image-spec-image-name image-spec)
    as x-user = (image-spec-user-x-position image-spec)
    as y-user = (image-spec-user-y-position image-spec)
    as tiled? = (image-spec-tiled-p image-spec)
    as image-data? = (find-image-data image-name)
    doing
    (when (and image-data? (not tiled?))
      (multiple-value-bind (left top)
      (compute-image-position image-data? x-user y-user)
    (update-extreme-edges-from-point left top)
    (update-extreme-edges-from-point (+r left (image-data-width image-data?))
                     (+r top (image-data-height image-data?)))))))





;;; The function `region-containing-background-images' is used by
;;; project-paper-for-frame to avoid painting background color underneath
;;; images.

(defun region-containing-background-images (image-plane)
  (let ((region (make-empty-region))
    (background-images (image-plane-background-images image-plane))
    (workspace (workspace-on-image-plane? image-plane)))

    ;; Merging-in an old KB draws the workspace BEFORE calling the post-loading
    ;; functions!  So fixup the slot here.
    (recenter-background-images-of-workspace workspace)
    
    (loop for image-spec in background-images
      as image-name = (image-spec-image-name image-spec)
      as x-user = (image-spec-user-x-position image-spec)
      as y-user = (image-spec-user-y-position image-spec)
      as tiled? = (image-spec-tiled-p image-spec)
      as image-data? = (find-image-data image-name)
      doing
      (when image-data?
    (cond (tiled?
           (setq region
             (add-rectangle-to-region
               (left-edge-of-workspace-area-in-window image-plane)
               (top-edge-of-workspace-area-in-window image-plane)
               (right-edge-of-workspace-area-in-window image-plane)
               (bottom-edge-of-workspace-area-in-window image-plane)
               region)))
          (t
           (multiple-value-bind (left-in-workspace top-in-workspace)
           (compute-image-position image-data? x-user y-user)
         (let* ((left (x-in-window left-in-workspace))
            (top (y-in-window top-in-workspace))
            (width (delta-x-in-window
                 (image-data-width image-data?)
                 current-image-x-scale))
            (height (delta-y-in-window
                  (image-data-height image-data?)
                  current-image-y-scale))
            (right (+f left width))
            (bottom (+f top height)))
           (setq region
             (add-rectangle-to-region
               left top right bottom region))))))))
    region))

;; This function carefully matches the size computations in, eg,
;; image-rendering-last-tile-height, so that the region agrees precisely with
;; that actually drawn in the image rendering code.



(def-grammar-category background-image ()
  (image-name 1)
  ((image-name 'at ordered-pair-of-integers) (1 . 3)))

;; Used?
(def-grammar-category background-image? ()
  ('none nil)
  (background-image 1))



;;; Completely bogus workaround for a bug in the parser wherein a list category
;;; whose elements parse into lists themselves is broken.

(def-grammar-category listed-background-image ()
  (image-name (1))
  ((image-name 'at ordered-pair-of-integers) (1 . 3))
  ((image-name 'tiled) (1 nil nil tiled) turn-nils-into-zeroes)
  ((image-name 'tiled 'at ordered-pair-of-integers) (1 4 tiled) flatten-phrase-tree))

(def-grammar-list-category bogus-background-images (listed-background-image)
  :separator \,
  :empty-list-symbol none)

(def-grammar-category background-images ()
  (bogus-background-images 1 fixup-background-images-at-parse-time))

(defun turn-nils-into-zeroes (phrase)
  (loop for spot on phrase
    when (null (car spot))
      do (setf (car spot) 0))
  phrase)

(define-category-evaluator-interface (ws-background-point
                       :access read-write)
    (structure point
           ((x integer)
        (y integer))
           (and x y))
  ((set-form (evaluation-value))
   evaluation-value)
  ((get-form (slot-value))
   slot-value))

(def-slot-value-compiler background-images (parse-result)
  (cond ((and (consp parse-result)
          (>f (loop for image-spec in parse-result
            count (image-spec-tiled-p image-spec)) 1))
     (values bad-phrase
         (copy-constant-wide-string #w"At most one background image may be tiled.")))
    (t
     parse-result)))

(define-category-evaluator-interface (background-images :access read-write)
    (or (no-item)
    (sequence (structure background-images-spec
                 ((image-name symbol)
                  (point (named ws-background-point))
                  (tiled truth-value))
                 (and image-name))
          1))
  ((set-form (evaluation-value))
   (when evaluation-value
     (with-safe-category-setter-calling
     (with-evaluation-sequence-to-phrase-list-mapping
         (evaluation-value background-images-info)
       (with-structure (background-images-info background-images-spec)
         (cond ((and tiled (evaluation-truth-value-is-true-p tiled))
            (nconc (phrase-list image-name)
               (call-category-setter-safely 'point point)
               (phrase-list 'tiled)))
           (point
            (phrase-cons image-name
                 (call-category-setter-safely 'point point)))
           (t image-name)))))))
  ((get-form (slot-value))
   (cond (slot-value
      (with-list-to-evaluation-sequence-mapping (slot-value background-image)
        (with-new-structure (background-images-spec)
          (setf image-name (image-spec-image-name background-image))
          (setf-non-nil
        point
        (call-category-getter 'point (cdr background-image) nil nil))
          (setf tiled (make-evaluation-boolean-value
                (image-spec-tiled-p background-image))))))
     (t nil))))
     
(defun fixup-background-images-at-parse-time (parse)
  (cond ((null parse) nil)
    ((atom parse) (dwarn "Bug!") nil)
    (t
     (loop for element in (cdr parse)           ; CDR-off the comma.
           collect (if (and (consp element) (singleton? element))
               (car element)
               element)
         using phrase-cons))))



(def-slot-value-writer background-images (value)
  (twrite-list value :empty "none" :conjoiner ", "
           :element-writer #'twrite-background-image))

(defun-simple twrite-background-image (image-spec)
  (cond ((atom image-spec)
     (tformat "~(~A~)" image-spec))
    ((image-spec-tiled-p image-spec)
     (tformat "~(~A tiled at (~A,~A)~)"
          (image-spec-image-name image-spec)
          (image-spec-user-x-position image-spec)
          (image-spec-user-y-position image-spec)))
    (t
     (tformat "~(~A at (~A,~A)~)"
          (image-spec-image-name image-spec)
          (image-spec-user-x-position image-spec)
          (image-spec-user-y-position image-spec)))))

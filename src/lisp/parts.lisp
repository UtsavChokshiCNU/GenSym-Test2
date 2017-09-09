;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module PARTS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Author: Ben Hyde






;;;; Introduction To Part Descriptions




;;; Part Descriptions provide a way to describe an object (like a table or a
;;; chart) where the component parts of the object are laid out in a tree.  The
;;; particulars of individual component subparts are often inherited to save
;;; space.  This inheritance is done in the tree that defines the breakdown
;;; structure, not in a class system.

;;; Consider this example of the part description for a chart axis:
;;;                (axis
;;;                 axis-heading north
;;;                 axis-minimum    -1.0
;;;                 axis-crossover 0.0
;;;                 axis-maximum   10.0
;;;                 subpart-defaults (chart-data-point ((chart-data-point
;;;                                                      data-point-show-indicator nil))))))



;;; A `part description' is a list structure constructed from slot value
;;; conses.  Part descriptions are instances of part types.  The head of
;;; the list `part-description-type' is always a part type, a symbol.
;;; The rest of the list is a property list known as the
;;; `part-description-features.' Compile time declarations for all part
;;; types and their features are required.

(def-list-structure (part-description (:consing-function slot-value-cons))
    (part-description-type . part-description-features))

;;; Parts may have subparts.  For example tables have cells, charts have
;;; data series, data series have points, etc.  The part subpart
;;; relationship defines a spanning tree over the parts.  Three "built
;;; in" part features interact to control this hierarchy: subparts,
;;; subpart-defaults, and subpart-exceptions.

;;;  An instance of a part need not specify all the features declared
;;; for that part type.  The absent feature values are specified by the
;;; ancestors of the subparts.  The part feature known as `subparts' is
;;; used to hold the immediate subparts of an part.  The part feature
;;; `subpart-defaults' is used to hold defaults for sets of descendant
;;; parts.

;;; Subparts of a part may be generated on the fly by the application.
;;; Consider this example.  The tick marks on a chart axis are
;;; implicitly generated, i.e.  no storage is allocated for them.  If
;;; the user modifies some aspect of a single tick mark, we will have to
;;; allocate storage.  This storage is known as a part exception. It is
;;; kept in an ancestor of the tick marks, and used to override the
;;; tickmark particulars generated on the fly.  The part feature
;;; `subpart-exceptions' is used to hold these records.

;;; Part descriptions come in two flavors: `part instances', and `part
;;; templates'.  A part instance is the description of a particular
;;; instance of a chart.  A part template describes default behavior
;;; for some number of instances.  Generally you can not distinguish a
;;; template from an instance without context.

;;; For example consider this part description.
;;;
;;;   (chart
;;;      chart-title "X v.s. Y"
;;;      subparts  (data-series ((data-series ...) (data-series ...) (data-series ..))
;;;                 axis ((axis ...) (axis ...)))
;;;      subpart-defaults (data-series ((data-series ...))
;;;                        axis ((axis ...)))
;;;      subpart-exceptions (data-series ((data-series data-series-index 1 ...))))

;;; All part features have a compile time declared simple type.  The three subpart
;;; features are all of the type subpart-collection.

;;; `Subpart-collection' is a simple type used as the type
;;; in part descriptions to describe subparts of a parent part.
;;; Subpart collections are property lists whose keys are part-type
;;; names.  The values are lists of part descriptions of that
;;; type.

(deftype-simple subparts-collection () 't)

;;; The SUBPARTS collections hold any part instances for this part.
;;; The SUBPART-DEFAULT collections hold a default for instances of a given type of part.
;;; The SUBPART-EXCEPTIONS collections hold values that override the default values
;;; for part features that would be automatically generated.







;;;; Forward References For Part Descriptions

(declare-forward-reference fake-attribute variable)                ;; GRAMMAR3
(declare-forward-reference color-or-metacolor-p function) ;; GRAMMAR4
(declare-forward-reference send-ws-representations-item-virtual-attribute-change
                           function);; EVENTS-G2






;;;; Dynamic State Used In Module




;;; When scanning a part description a stack is used to restore
;;; dynamic state when scanning of a subpart is completed.  The backbone
;;; of this stack is built from conses taken from the `part-stack'
;;; cons pool.

(defconser part-stack parts)

(defmacro part-stack-push-macro (element place)
  (unless (and (or (symbolp element)
                   (and (consp element)
                        (eq 'quote (car element))))
               (symbolp place))
    (warn "Part-stack-push-macro is approprate only on literals"))
  `(setq ,place (part-stack-cons-macro ,element ,place)))

;;; The dynamic extent `working-on-annotated-frame' must be established whenever
;;; a part feature might be reclaimed.  When working-on-annotated-frame is
;;; established, a binding is given to `current-annotated-frame.'  That provides
;;; a way for the part feature reclaimers to remove data, and to do display
;;; updates, from the parent frame when necessary.

;;; It is usually the case that you will also need to establish bindings for
;;; current-block-of-dependent-frame and current-computation-style when working
;;; on annotated frames, but these are not currently part of this dynamic
;;; extent.

(def-named-dynamic-extent working-on-annotated-frame
  (module parts))

(defvar-of-named-dynamic-extent current-annotated-frame working-on-annotated-frame)


;;; Scanning-subparts-of-block is established to create the stacks used when
;;; scanning part descriptions.

(def-named-dynamic-extent scanning-subparts-of-block
  (module parts)
  (dynamic-superior working-on-annotated-frame))



;;; The stack `part-feature-recall-stack' and is bound when scanning-subparts-of-block
;;; is established.   Its backbone is part-stack conses.

(defvar-of-named-dynamic-extent part-feature-recall-stack scanning-subparts-of-block
  (process-binding nil)
  (global-binding nil))



;;; `Stack-of-current-part-descriptions' contains all part descriptions that
;;; with-part-description has currently been asked to scan.  This is useful in
;;; debugging, but is also used in describe to find who established what features
;;; of the part being described.

(defvar-of-named-dynamic-extent stack-of-current-part-descriptions scanning-subparts-of-block
  (process-binding nil))


;;; `Maintain-stack-of-current-part-descriptions-p' by default disables the
;;; costs associated with maintaining the stack-of-current-part-descriptions.

(defvar-of-named-dynamic-extent maintain-stack-of-current-part-descriptions-p scanning-subparts-of-block
  (process-binding nil))





;;; `Part-exceptions-from-parents' is maintained when scanning the subparts of a block
;;; to provides a search path for exceptions to default behavor established by a parent.

(defvar-of-named-dynamic-extent part-exceptions-from-parents scanning-subparts-of-block)









;;;; Projection, a Dynamic Extent for Draw-like operations.




;;; Projection, a dynamic extent, is current during the process of
;;; walking over something in the natural order of drawing it.  Various
;;; refinements of projection are then used to implement different
;;; operations, for example drawing or tracking the mouse.  Projection
;;; forms a skeleton for many operations that need to have all or some of
;;; the fine details of how a kb-frame is rendered available during their
;;; implementation.  There are two dimensions to this variation: `mode'
;;; and `focus'.

;;; When you project a block you may want to project only some parts of
;;; the block.  For example just those parts that depend on a particular
;;; cell in the cell array.  Limiting the projection to a particular
;;; subset of the entire block is called `focusing' the projection.

;;; When you project a block you may do so for differing purposes.
;;; Examples include drawing, tracking the mouse, recomputing the overall
;;; size, etc.  The purpose for which you are projecting is controlled by
;;; the setting of the `projection-mode.'  Each projection mode may
;;; augment the projection dynamic extent with additional data to
;;; parameterize the projection in that mode.


(def-named-dynamic-extent projection
  (module parts))



;;; Projection is never established directly, rather refinements of
;;; projection are established.  Each different refinement
;;; causes the projection routine to do a different activity for each
;;; subpart in the block.  The binding of `projection-mode' communicates
;;; this to the projection routine.  This table summarizes these modes.

;;;    - Binding For Mode -                      - Kind Of Projection -
;;;   draw-projection-mode                       projection-drawing
;;;   tracking-projection-mode                   projection-tracking
;;;   update-dependencies                        projection-update-dependencies
;;;   compute-path-of-focus-projection-mode      projection-computing-path-of-focus
;;;   funcall-on-focus-projection-mode           projection-funcall-on-focus

;;; Each of these projection modes is discussed in more detail in the
;;; sections below.

(defvar-of-named-dynamic-extent projection-mode projection)


;;; In addition to the projection mode we have the concept of projection
;;; focus method.  When the projection routine is called it maybe asked to
;;; focus only on a subset of all the subparts of a given block.  For example
;;; to focus only on those subparts affected by a given expression.  This
;;; provides the tools to do only partial redraw.  Bindings established
;;; prior to projection control the focus.

;;; `Projection-focus-method' is one of NIL, ANNOTATION, or CELL.  It is bound
;;; globally to NIL, and NIL implies that the projection to visit all parts of
;;; the block.

;; Someday there will be a screen area focus, for mouse tracking, scrolling, etc.

(defvar-of-named-dynamic-extent projection-focus-method projection
  (global-binding nil))



;;; When the focus is ANNOTATION then projection-focus-annotation is bound to an
;;; annotation.  The projection should focus on all parts who's behavor is affected
;;; by that annotation.  This may be many parts if the annotation sets some
;;; defaults.

(defvar-of-named-dynamic-extent projection-focus-annotation projection)



;;; When the focus is CELL, the projection-focus-cell-index is bound to
;;; the cell index of a cell in the block's cell array.  The projection
;;; should focus on all parts whose behavor is affected by this cell.
;;; This maybe could be many parts.

(defvar-of-named-dynamic-extent projection-focus-cell-index projection)



;;; When the focus is CELL and the projection mode is updating
;;; dependencies then a binding is provided to
;;; projection-focus-cell-new-cached-value so that the projection method
;;; will have access to both the current and incoming values for the cell
;;; being changed.

(defvar-of-named-dynamic-extent projection-focus-cell-new-cached-value projection)




;;; `Projection-drawing' is the principal refinement of the dynamic
;;; extent projection.  When projection drawing, the projection routine
;;; should draw all components of the item that are in the current focus.


(def-named-dynamic-extent projection-drawing
  (module parts)
  (includes projection))

;; This should be changed to two methods draw, and revise screen where revise
;; screen can be used to commit an incremental change using XOR, or what ever.



;;; `Projection-funcall-on-focus' is a refinement of the dynamic extent
;;; known as projection.  Current-projection-function-for-funcall is
;;; bound in this extent to a function known as the focus function
;;; approprate to funcall-compiled-function whose argument is a
;;; symbol that will indicate where in the projection scan the function
;;; was called.  If the function returns a non-nil value the scan will be
;;; abandoned as soon as possible (though the function may be called
;;; again since some projection functions do not support abandoning the
;;; scan in the midst of processing).

;;; This mode is intended for low performance access to the projection
;;; method.  For example computing designations, and descriptions.

;;; The symbol passed to the focus function is one of the following:
;;; ENTER-FOCUS, or ENTER-SUBPART.  ENTER-FOCUS indicates that at this
;;; point in the scan, the focus for the first time began to match.
;;; ENTER-SUBPART is called whenever a component part of the block that
;;; matches the focus is encountered.

(def-named-dynamic-extent projection-funcall-on-focus
  (module parts)
  (includes projection))
(defvar-of-named-dynamic-extent
  current-projection-function-for-funcall
  projection-funcall-on-focus)



;;; `Projection-tracking' a refinement of projection  and it's
;;; variables:
;;;   - current-tracking-x-in-window
;;;   - current-tracking-y-in-window
;;;   - current-tracking-subcomponent
;;;   - create-subpart-upon-tracking-p
;;; are not yet documented.

(def-named-dynamic-extent projection-tracking
  (module parts)
  (includes projection))
(defvar-of-named-dynamic-extent current-tracking-x-in-window   projection-tracking)
(defvar-of-named-dynamic-extent current-tracking-y-in-window   projection-tracking)
(defvar-of-named-dynamic-extent current-tracking-subcomponent  projection-tracking)
(defvar-of-named-dynamic-extent create-subpart-upon-tracking-p projection-tracking)



;;; `Projection-update-dependencies' a refinement of projection is
;;; not yet documented. Nor are it's varaible:
;;;  - current-kind-of-change
;;;  - current-thing-changed
;;; document yet.

(def-named-dynamic-extent projection-update-dependencies
  (module parts)
  (includes projection))
(defvar-of-named-dynamic-extent current-kind-of-change projection-update-dependencies)
(defvar-of-named-dynamic-extent current-thing-changed  projection-update-dependencies)



;;; `Projection-computing-path-of-focus' a refinement of projection is
;;; not yet documented. Nor is it variable:
;;;  - projection-computing-path-of-focus
;;; documented yet.

(def-named-dynamic-extent projection-computing-path-of-focus
  (module parts)
  (includes projection))
(defvar-of-named-dynamic-extent projection-focus-path projection-computing-path-of-focus)







;;;; Avoiding Erasing When Already Erased



;;; `Parts-of-annotated-frames-currently-erased' provides the dynamic to
;;; avoid erasing a part of a frame we have already erased.  It is
;;; always NIL at top level.  It is managed as a stack.  The stack is
;;; an alist, keyed by block.  The CDR of each entry is a list.  This
;;; list consists of each part this update is focused on.

;;; In outline each update method looks like so:
;;;    1. Erase part of the block.
;;;    2. Make the change that part of the block.
;;;    3. Redraw the block.
;;; the problem we arises if during step 2 another update to the same
;;; part takes place.

;;; Update methods push an entry on the stack in step 1, and pop it
;;; of in step 2.  If another entry, identical, entry is already in
;;; stack they should niether erase or redraw.

;;; When the update method is focused on the entire block then the entry
;;; should have T in its cdr.

;;; In some cases the update method is focused on some other aspect of
;;; the part than an entire part.  Updates from cells in the cell-array
;;; is one example of this.  In these cases the part being affected
;;; may not be apparent directly to the update method, in which case
;;; it creates the entry with a NIL in the position for the part
;;; description.  The projection routine must then fill in the part
;;; affected and preempt the erase if a prior entry exists.

(def-kb-specific-variable parts-of-annotated-frames-currently-erased parts nil)

(defun erase-entire-annotated-block (block)
  (let ((blocks-already-erased parts-of-annotated-frames-currently-erased))
    (part-stack-push
      (part-stack-cons block nil)
      parts-of-annotated-frames-currently-erased)
    (unless (assq block blocks-already-erased)
      (update-images-of-block block t t))))

(defun redraw-entire-annotated-block ()
  (let* ((erase-record (part-stack-pop parts-of-annotated-frames-currently-erased))
         (block (first erase-record)))
    (reclaim-part-stack-cons erase-record)
    (unless (assq block parts-of-annotated-frames-currently-erased)
      (update-images-of-block block nil t))))


(defun erase-part-of-block (frame-containing-part part)
  (let ((projection-focus-method 'annotation)
        (projection-focus-annotation part))
    (erase-entire-annotated-block frame-containing-part)))

(defun redraw-part-of-block (part)
  (let ((projection-focus-method 'annotation)
        (projection-focus-annotation part))
    (redraw-entire-annotated-block)))







;;;; Highlighting



;; This code was moved down here to pick up the definition of the
;; working-on-annotated-frame named dynamic extent.  -jra 5/2/91

(defvar currently-supressing-part-highlighting nil)

(defun highlight-part-of-frame (frame-containing-annotation part)
  (unless currently-supressing-part-highlighting
    (let ((projection-focus-method 'annotation)
          (projection-focus-annotation part))
      (erase-entire-annotated-block frame-containing-annotation)
      (set-simple-part-feature part 'highlighted? t)
      (redraw-entire-annotated-block))))

(defun unhighlight-part-of-frame (frame-containing-annotation part)
  (when (get-simple-part-feature part 'highlighted?)
    (with-named-dynamic-extent working-on-annotated-frame
                               ((current-annotated-frame frame-containing-annotation))
      (let ((projection-focus-method 'annotation)
            (projection-focus-annotation part))
        (erase-entire-annotated-block frame-containing-annotation)
        (remove-simple-part-feature part 'highlighted?)
        (redraw-entire-annotated-block)))))






;;;; Translation Between Internal and User Symbols.



;;; We have some internal symbolic names that we want to have different
;;; in the user's expressions.  For example, chart-data-point is known as
;;; a data-point to the user.  We keep a mapping for such spellings on
;;; the property list of the symbols involved.  The values of these
;;; properties are property lists, the keys are what kind of use the
;;; symbol is in, while the values are the alias symbolic name.

;; Very tempting to move this in to utilities, and then make tformat &
;; friends know something about it.  That would require something like:
;;    (tformat "~/context/~S" 'constant t)  -> "true"
;; or very volatile dynamic extent of some sort.


;;; `User-spellings-of-internal-symbol' and `internal-spellings-of-user-symbol'
;;; are the two global properties used to store this information.

(def-global-property-name user-spellings-of-internal-symbol)

(def-global-property-name internal-spellings-of-user-symbol)



;;; `Def-user-spellings' is used to define these.  It takes three arguments:
;;; internal-symbol context and external-spelling.  The context specifies
;;; what context this translation applies within.  This is used to allow a symbol
;;; to have one translation for one part of the product, and another
;;; for a different part.

(defun def-user-spelling (internal-symbol context external-symbol)
  (setf (getf (internal-spellings-of-user-symbol external-symbol) context)
        internal-symbol)
  (setf (getf (user-spellings-of-internal-symbol internal-symbol) context)
        external-symbol))



;;; `Get-user-spelling' and `get-internal-spelling' are used to look
;;; up these aliases.  These both take two arguments, the symbol to
;;; translate, and a context.

(defun get-user-spelling (internal-symbol context)
  (or
    (getf (user-spellings-of-internal-symbol internal-symbol) context)
    internal-symbol))

(defun get-internal-spelling (user-symbol context)
  (let ((result? (internal-spellings-of-user-symbol user-symbol)))
    (if (memq context result?)
        (getf result? context)
        user-symbol)))






;;;; Parser Utilities Used By Parts




;;; True and False are user spellings in the context of constants for T and Nil.

(def-user-spelling 't 'constant 'true)

(def-user-spelling 'nil 'constant 'false)


;;; `Fix-up-parse-upon-reduction' is called only as the reducing form in a Parser rule.
;;; It sweeps over a parse and rewrites forms in the parse.  It rewrites these
;;; forms:
;;;     (get-internal-spelling <user-spelling> <domain>) -> alternate-spelling
;;;     (coerce-to-phrase-float <number>) -> <phrase-float>
;;; It never rejects a parse.

(defun fix-up-parse-upon-reduction (parse)
  (cond
    ((not (consp parse))
     parse)
    (T
     (case (first parse)
       (get-internal-spelling
        (get-internal-spelling (second parse) (third parse)))
       (otherwise
        (setf (car parse) (fix-up-parse-upon-reduction (car parse)))
        (setf (cdr parse) (fix-up-parse-upon-reduction (cdr parse)))
        parse)))))



;;; `Reduce-annotation' is a grammar rule reduction function.  It
;;; converts a parse into a single statement that when executed will add
;;; this annotation to the current part description.  Background
;;; necessary to understanding what this routine is doing is provided in
;;; the documenation for compile-part-description.

;;; The input parse is a pair:
;;;    (<affected-part-feature> <desired-part-value>), i.e.
;;; The output is a statement of the form:
;;;    (set-simple-part-feature current-part-description '<part-feature> '<part-value>)
;;;

;;; Some conversions are done to internal format.  For example (indicator
;;; square) becomes (set-simple-part-feature current-part-description
;;; 'data-point-indicator 'simple-square) The desired-part-feature is
;;; converted to internal spelling, if necessary.  The desired-part-value
;;; is also converted to internal representation; if it is a symbol an
;;; internal spelling is found, if necessary.

;;; For a small number of part-features, a bogus, conversion to phrase
;;; float is forced.

(defun reduce-annotation (parse)
  (let* ((part-description-to-annotate (first parse))
         (external-part-feature  (second parse))
         (external-desired-value (third parse))
         (internal-part-feature
           (get-internal-spelling external-part-feature 'part-feature))
         (internal-desired-value
           (cond
             ((symbolp external-desired-value)
              (get-internal-spelling external-desired-value 'constant))
             (t
              external-desired-value)))
         (parse-after-reduction
           (phrase-list 'set-simple-part-feature
                        part-description-to-annotate
                        (phrase-list 'quote internal-part-feature)
                        (phrase-list 'copy-for-slot-value
                                     (phrase-list 'quote internal-desired-value))
                        #+obsolete ;; managed floats are now atoms.
                        (if (atom internal-desired-value)
                            (phrase-list 'quote internal-desired-value)
                            (phrase-list 'copy-for-slot-value
                                     (phrase-list 'quote internal-desired-value))))))
    parse-after-reduction))


(defun reduce-annotation-with-expression (parse)
  (let* ((part-description-to-annotate (first parse))
         (external-part-feature  (second parse))
         (external-desired-value (third parse))

         (internal-part-feature
           (if (atom external-part-feature)
               (get-internal-spelling external-part-feature 'part-feature)
               external-part-feature))
         (internal-desired-value
           (cond
             ((symbolp external-desired-value)
              (get-internal-spelling external-desired-value 'constant))
             (t
              external-desired-value)))

         (parse-after-reduction
           (phrase-list 'set-simple-part-feature
                        part-description-to-annotate
                        (phrase-list 'quote internal-part-feature)
                        (if (atom internal-desired-value)
                            (phrase-list 'quote internal-desired-value)
                            (phrase-list 'compile-computed-part-feature
                                         (phrase-list 'quote internal-desired-value))))))

    parse-after-reduction))






;;;; Declaring Part Descriptions




;;; We maintain a declarative framework for part-types.  For each part type we know
;;; its name and the set of part features that may appear in it.  This information
;;; is stored on the property lists of the part-type-name, and the individual
;;; symbols used to name part features.

;;; These declarative structures are used to:
;;;   1. validate, in development, part instances
;;;   2. show, in development, the declarative structures.
;;;   3. build grammar, at compile and load time.
;;;   4. write part descriptions, at slot writing time.
;;;   5. scan part descriptions, at run time.
;;;   6. validate user input, at parse and compile time.


;;; The declarative structures are built from structures and vectors.
;;; Structures are used to store knowledge of the part-type and each
;;; part feature.  A vector is used to store knowledge of the
;;; part features for a given part, allowing that knowledge to
;;; be accessed in constant time.  This vector is sparse. We allocate
;;; enough elements to allow any part-type to have any known part
;;; feature.  Each part feature is given a unique index, i.e. width
;;; might be assigned 12, and then any part-type that has width
;;; will have an entry in it's vector at 12.

;;; `Maximum-number-of-part-features' is a compile time constant that
;;; sets a global limit on the total number of part features.  If, as we
;;; develop additional part features, then this number may need to be
;;; increased.

(defparameter maximum-number-of-part-features 91)

(defvar part-feature-indexes
        (make-array-with-nils maximum-number-of-part-features))

(def-global-property-name part-feature-index)

(defvar last-part-features-index-allocated -1)

(defun get-or-make-part-feature-index (part-feature)
  (or (part-feature-index part-feature)
      (progn
        (incff last-part-features-index-allocated)
        (when (svref part-feature-indexes last-part-features-index-allocated)
          (setf last-part-features-index-allocated
                (loop for i from 0 below maximum-number-of-part-features
                      when (null (svref part-feature-indexes i))
                        return i
                      finally
                        (error "No additional part-feature indexes are available."))))
        (setf (svref part-feature-indexes last-part-features-index-allocated)
              part-feature)
        (setf (part-feature-index part-feature)
              last-part-features-index-allocated))))



;;; The PART-TYPE-DESCRIPTION property appears on part type names.  It maps
;;; to a property list of information about the part type.

(def-global-property-name part-type-description)



;;; A `part-type-description' list structure is found as the value of
;;; the part-type-description property.  The `part-type-features' slot
;;; is a property list, keyed by the feature and with values that are
;;; part-feature-description list structures.

(def-list-structure (part-type-description)
                    (part-type-name                          ;; symbol
                     part-type-features                      ;; (plist-of feature-name feature-description)
                     part-type-user-spelling                 ;; symbol
                     part-type-includes                      ;; (list-of part-type-name)
                     part-type-hidden-features               ;; (list-of feature-name)
                     part-type-allow-individual-exceptions-in-parents  ;; boolean
                     part-type-allow-defaulting-in-parents   ;; boolean
                     part-type-semantic-check                ;; (or null symbolic-name-of-function)
                     ))



;;; `Immediate-part-feature-description', a macro, is the accessor for a
;;; part-feature-description, while `part-feature-description', a
;;; function, will search the included types.

;;; The part description consists of a property list.  One element in that
;;; property list information about the features that appear on this part
;;; type.

(defmacro immediate-part-feature-description (part-type part-feature)
  `(getf
     (part-type-features (part-type-description ,part-type))
     ,part-feature))

(defun part-feature-description (part-type part-feature)
  (let ((part-type-description (getfq-macro (symbol-plist part-type)
                                            'part-type-description)))
    (or (getfq-macro (part-type-features part-type-description)
              part-feature)
        (loop for included-part-type in (part-type-includes (part-type-description part-type))
              as description = (part-feature-description included-part-type part-feature)
              when description
                do
                  (return description)))))



;;; The `feature-appears-on-these-part-types' property appears on part feature names,
;;; and contains a list of part type names.  This property is maintained only in
;;; development.

#+development
(def-global-property-name feature-on-these-part-types)



;;; `Def-part-type' is used to declare a new part type.    These switches are
;;; given in the form of an alist (individual symbols are converted to single
;;; element lists).  These arguments are supported.
;;;   (children-part-types <part-type> ...)
;;;      These part types may appear as direct desendant of an instance of this
;;;      part type.
;;;   (other-descendant-part-types <part-type> ...)
;;;      These part types may appear as indirect descendant of an instance of this
;;;      part type, and hence may have defaults specified for them on instances of
;;;      this part type.
;;;   (user-spelling <symbol>)
;;;      In messages to the user this symbol's spelling should be used instead of
;;;      the internal spelling.
;;;   (includes <part-type> ...)
;;;      This part type is a refinement of a part-type previously introduced.
;;;      for example in charting an AXIS is a refinement of a DATA-SERIES.
;;;   (hidden-features <part-feature-name> ...)
;;;      This provides a way for a type to supress from user view features
;;;      of included types.  For example an expression might suppress the
;;;      allow forward chaining feature of a computation style.
;;;   (allow-individual-exceptions-in-parents t)
;;;   (allow-defaulting-in-parents t)
;;;      These declare the willingness of the part handling code to
;;;      search into their ancestors for exceptions or default values.

;;; A named dynamic extent is created of the same name as the part type,
;;; with scanning-subparts-of-block as a dynamic superior.  A
;;; defvar-of-named-dynamic-extent for CURRENT-<part-type-name> is done.
;;; Routines that scan the part data structures usually bind these
;;; variables.

;;; A part-type always includes the part BASIC-PART, which of course does not include
;;; itself.

(defmacro def-part-type (part-type-name &body part-type-args)
  "Additional args: children-part-types other-descendant-part-types user-spelling includes
   hidden-features allow-individual-exceptions-in-parents allow-defaulting-in-parents"
  (unless (symbolp part-type-name)
    (warn "Part type name must be a symbol."))
  ;; Normalize the part-type-args into an alist.
  (setf part-type-args
        (loop for part-type-arg in part-type-args
              do (assert (or (symbolp part-type-arg)
                             (consp part-type-arg)))
              collect (if (symbolp part-type-arg)
                          (list part-type-arg)
                          part-type-arg)))
  (let (;; Argument defaults
        children
        other-descendant-part-types
        (includes (if (eq part-type-name 'basic-part)
                      ()
                      '(basic-part))))
    (loop for (part-arg-name . argument-details) in part-type-args
          do
      (case part-arg-name
        (children-part-types
         (setf children argument-details))
        (other-descendant-part-types
         (setf other-descendant-part-types argument-details))
        (includes
         (setf includes (nconc (copy-list argument-details) includes)))
        ((user-spelling
           hidden-features
           allow-individual-exceptions-in-parents
           allow-defaulting-in-parents)
         ; handled in def-part-type-1
         )
        (otherwise
         (warn "Unknown argument to def-part-type ~S" part-arg-name))))
    (let* ((current-instance-name
             (intern
               (format nil "CURRENT-~A" part-type-name)))
           (descendants (concatenate'list
                         children
                         other-descendant-part-types)))
      `(progn
         ,@(unless (eq part-type-name 'basic-part)
             `((def-named-dynamic-extent ,part-type-name
                 (module parts)
                 (includes ,@includes))))
         (defvar-of-named-dynamic-extent ,current-instance-name ,part-type-name
           (global-binding 'symbol-standing-in-for-unbound))
         (def-part-type-1 ',part-type-name
                          ',includes
                          ',part-type-args)
         (def-part-feature (,part-type-name subparts)
           (type (subparts-collection ,@children))
           (user-visible nil)
           (means-of-scanning call-handlers #'enter-part-feature-subparts #'exit-part-feature-subparts))
         (def-part-feature (,part-type-name subpart-defaults)
           (type (subparts-collection ,@descendants))
           (user-visible nil)
           (means-of-scanning call-handlers #'enter-subpart-defaults #'exit-subpart-defaults))
         (def-part-feature (,part-type-name subpart-exceptions)
           (type (subparts-collection ,@descendants))
           (user-visible nil)
           (means-of-scanning call-handlers #'enter-subpart-exceptions #'exit-subpart-exceptions))))))



;;; `def-part-type-1' is called at load time initialize the type description.

(defun def-part-type-1 (part-type-name includes args)
  (let* ((user-spelling-specified-p (assq 'user-spelling args))
         (user-spelling? (second user-spelling-specified-p))
         (hidden-features-specified-p (assq 'hidden-features args))
         (hidden-features? (rest hidden-features-specified-p))
         (allow-individual-exceptions-in-parents-specified-p
           (assq 'allow-individual-exceptions-in-parents args))
         (allow-individual-exceptions-in-parents
           (if allow-individual-exceptions-in-parents-specified-p
               (second allow-individual-exceptions-in-parents-specified-p)
               t))
         (allow-defaulting-in-parents-specified-p
           (assq 'allow-defaulting-in-parents args))
         (allow-defaulting-in-parents
           (if allow-defaulting-in-parents-specified-p
               (second allow-defaulting-in-parents-specified-p)
               t)))
    (when user-spelling?
      (def-user-spelling part-type-name 'part-type user-spelling?))
    (setf
      (part-type-description part-type-name)
      (make-part-type-description
        part-type-name
        ()
        (if user-spelling-specified-p
            user-spelling?
            part-type-name)
        includes
        hidden-features?
        allow-individual-exceptions-in-parents
        allow-defaulting-in-parents
        nil))))




;;; For each part-feature we record some some information about that feature.
;;; We know it name, the type of the values it takes on, and optionally
;;; a name that the user uses to refer to this feature.

(def-list-structure (part-feature-description)
                   ( part-feature-name
                     part-feature-means-of-scanning
                     part-feature-type
                     part-feature-user-spelling
                     part-feature-user-visible?
                     ))


;;; `part-feature-{enter,exit}-methods' are two vectors used for a performance
;;; enhancment.  They map from the part-feature index to the routines manage
;;; the scanning of a particular feature.  They are filled out by
;;; def-part-feature-1.  `part-feature-{enter,exit}-method' provides a slight
;;; bit of abstraction to this lookup.

(defvar part-feature-enter-methods (make-array maximum-number-of-part-features))

(defvar part-feature-exit-methods  (make-array maximum-number-of-part-features))

(defmacro part-feature-enter-method (part-feature-index)
  `(svref part-feature-enter-methods ,part-feature-index))

(defmacro part-feature-exit-method (part-feature-index)
  `(svref part-feature-exit-methods ,part-feature-index))



;;; `Part-type-descendant-part-types' returns the set of part-types that may appear nested
;;; inside of the given part type.  This is computable since we know the type
;;; of the part-features, we know that all parts have a subpart-defaults feature,
;;; and finally we know that the type of that is (subparts-collection
;;; <list-of-descendant-part-types>)

(defun part-type-descendant-part-types (part-type)
  (rest
    (part-feature-type
      (part-feature-description part-type 'subpart-defaults))))



;;; Def-part-feature is used to declare a feature in a part.
;;; The arguments is a list of flags, analogous to those
;;; passed to def-struct.
;;;   type             -- a simple type spec.
;;;   user-spelling    -- the user's name use for this.
;;;   suppress-defvar  -- used internally only.
;;;   user-visible
;;;   means-of-scanning -- see below.

;;; The means of scanning controls how a part feature is handled when
;;; a part description is entered and exited.
;;;   (means-of-scanning special-variable <special-variable>)
;;;   (means-of-scanning call-handlers    <entry-handler> <exit-handler>)
;;;   (means-of-scanning structure-slot   <current-instance> <structure-slot-name>)
;;;   (means-of-scanning class-slot       <current-instance> <class-slot-name>)
;;;   (means-of-scanning none)

;;; Special-variable is the default means-of-scanning.  When the means of
;;; scanning requested is special variable then the given special variable
;;; which defaults to the part feature name is set and restored as you
;;; enter and leave the part.  Additionally when special variable handling
;;; is requested a defvar-of-named-dynamic-extent is generated for the
;;; special variable in the dynamic extent of this part type.

;;; When the means-of-scanning requested in call-handlers then the routines
;;; given are called with the old and new values for the part feature as the
;;; scan enters and leaves a part with this features.

;;; When the means-of-scanning requested is none scanning a part with
;;; this feature has no side effects.


(defmacro def-part-feature ((part-type feature-name) &body args)
  "Additional arguments include: type user-spelling means-of-scanning"        ; suppress-defvar is private
  (unless (symbolp part-type)
    (warn "def-part-feature, part-type isn't a symbol"))
  (unless (symbolp feature-name)
    (warn "def-part-feature, feature-name isn't a symbol"))
  (setf args (loop for x in args collect (if (symbolp x) (list x) x)))
  ;; Check that only legal args were passed
  (let ((type t)
        (user-spelling feature-name)
        (user-visible t)
        (supress-defvar nil)
        (means-of-scanning `(special-variable ,feature-name))
        (enter-feature-routine-name (intern (format nil "ENTER-PART-FEATURE-~A" feature-name)))
        (exit-feature-routine-name (intern (format nil "EXIT-PART-FEATURE-~A" feature-name)))
        enter-feature-routine-body
        exit-feature-routine-body
        name-of-special-variable)
    (loop for argument in args
          do
      (case (first argument)
        (type
         (setf type (second argument))
         (unless
           (or
             (and
               (consp type)
               (eq 'subparts-collection (first type)))
             (valid-simple-type-specification type))
           (warn "Incomprehensible simple type specification: ~S." type)))
        (user-spelling
         (setf user-spelling
               (if (cdr argument)
                   (second argument)
                   t)))
        (user-visible
         (setf user-visible (if (cdr argument)
                                (second argument)
                                t)))
        (supress-defvar
         (setf supress-defvar (if (cdr argument)
                                  (second argument)
                                  t)))
        (means-of-scanning
         (setf means-of-scanning (rest argument)))
        (otherwise
         (warn "def-part-feature: ~S, isn't a legal argument."
                argument))))

    (case (first means-of-scanning)
      (special-variable
       (setf name-of-special-variable (second means-of-scanning))
       (setf enter-feature-routine-body
             `((part-stack-push ,name-of-special-variable part-feature-recall-stack)
               (setf ,name-of-special-variable new-value)))
         (setf exit-feature-routine-body
               `((setf ,name-of-special-variable (part-stack-pop part-feature-recall-stack)))))
      (call-handlers
       (let ((enter-feature-routine (second means-of-scanning))
             (exit-feature-routine (third means-of-scanning)))
         (unless (and (consp enter-feature-routine)
                      (eql 'function (car enter-feature-routine)))
           (warn "Enter feature routine for ~S of ~S must be a compiled function, not ~S"
                 feature-name part-type enter-feature-routine))
         (unless (and (consp exit-feature-routine)
                      (eql 'function (car exit-feature-routine)))
           (warn "Exit feature routine for ~S of ~S must be a compiled function, not ~S"
                 feature-name part-type exit-feature-routine))
         (setf enter-feature-routine-name (second enter-feature-routine))
         (setf exit-feature-routine-name (second exit-feature-routine))
         (setf enter-feature-routine-body nil)
         (setf exit-feature-routine-body nil)))
      ((structure-slot class-slot)
       (let ((current-structure (second means-of-scanning))
             (slot-name (third means-of-scanning)))
         (setf enter-feature-routine-body
               `((part-stack-push (,slot-name ,current-structure) part-feature-recall-stack)
                 (setf (,slot-name ,current-structure) new-value)))
         (setf exit-feature-routine-body
               `((setf (,slot-name ,current-structure) (part-stack-pop part-feature-recall-stack))))))
      (none
       (setf enter-feature-routine-name 'scan-feature-doing-nothing)
       (setf exit-feature-routine-name 'scan-feature-doing-nothing)
       (setf enter-feature-routine-body nil)
       (setf exit-feature-routine-body nil))
      (otherwise
       (warn "Unknown means-of-scanning requested: ~S" means-of-scanning)))



    ;; Check that the type spec is well formed.
    `(progn
       ,@(when (and name-of-special-variable
                    (not supress-defvar))
           `((defvar-of-named-dynamic-extent
               ,name-of-special-variable
               ,part-type (global-binding 'symbol-standing-in-for-unbound))))
       ,@(when enter-feature-routine-body
         `((defun-simple ,enter-feature-routine-name (new-value)
             ,@enter-feature-routine-body
             nil)))
       ,@(when exit-feature-routine-body
         `((defun-simple ,exit-feature-routine-name ()
             ,@exit-feature-routine-body
             nil)))
       #+development
       (loop for method-implementation-function-name
                 in ',(list enter-feature-routine-name exit-feature-routine-name)
             as (method-name . required-signature) in '((enter-feature (T) (T)) (exit-feature () (T)))
             as function-type-declaration
                = (get method-implementation-function-name 'function-type-declaration)
             unless (equal function-type-declaration required-signature)
               do (warn "the ~S method implemented by ~S isn't declared to take ~S type args and or return ~S type values."
                        method-name
                        method-implementation-function-name
                        (first required-signature)
                        (second required-signature)))
       (def-part-feature-1
         ',part-type
         ',feature-name
         ',type
         ',user-spelling
         ',user-visible
         #',enter-feature-routine-name
         #',exit-feature-routine-name
         ',means-of-scanning)
         ',feature-name)))

(defun def-part-feature-1 (part-type
                           feature-name
                           type
                           user-spelling
                           user-visible
                           enter-feature-routine
                           exit-feature-routine
                           means-of-scanning)

  #+development
  (pushnew part-type (feature-on-these-part-types feature-name))
  #+development
  (unless (part-type-description part-type)
    (warn "define-part-feature: unknown part-type: ~S" part-type))
  (let ((part-feature-index (get-or-make-part-feature-index feature-name)))
    (setf (part-feature-enter-method part-feature-index) enter-feature-routine)
    (setf (part-feature-exit-method part-feature-index) exit-feature-routine))
  (when user-spelling
    (def-user-spelling feature-name 'part-feature user-spelling))
  (setf (immediate-part-feature-description part-type feature-name)
        `(,feature-name
          (,enter-feature-routine
           ,exit-feature-routine
           ,@means-of-scanning)
          ,type
          ,user-spelling
          ,user-visible)))



(defun scan-feature-doing-nothing (old-value new-value)
  (declare (ignore old-value new-value)))




;;; `Def-part-type-semantic-check' defines a function of one argument that is called
;;; as within the dynamic extent of a slot value compiler.  It will be called with
;;; a part description who's features have already been checked for conformance with
;;; their declared types.

;;; This function should return NIL or a string.  The string will be recycled by the
;;; caller.  The string should report in the manner of def-slot-value-compiler what
;;; was unacceptable about the part description.

;;; The macro def-part-type-semantic-check expects to recieve: a part-type, a single
;;; argument argument list, and the body of the semantic checking function.

(defmacro def-part-type-semantic-check (part-type (part-description-to-be-checked) &body body)
  (let ((check-function (intern (format nil "SEMANTIC-CHECK-~S-PART-TYPE" part-type))))
    `(progn
       #+development
       (unless (part-type-description ',part-type)
         (warn "def-part-type-semantic-check: unknown part-type: ~S" ',part-type))
       (defun ,check-function (,part-description-to-be-checked) ,@body)
       (setf (part-type-semantic-check (part-type-description ',part-type))
             ',check-function))))






;;;; Debugging Printers and Describe for Parts

;;; This section is entirely development code.  It defines a
;;; the printer and describe "method".

#+development
(defvar print-parts-as-structures-p t)

#+development
(defun development-part-instance-p (thing)
  (and print-parts-as-structures-p
       (consp thing)
       (symbolp (car thing))
       (get (car thing) 'part-type-description)
       ;; could be a dotted pair
       (consp (cdr thing))
       (endp (cdr (last thing))) ;; a proper list
       (oddp (length thing)) ;; but not a plist
       ))

#+development
(def-development-printer print-part-instance (thing stream)
  (when (development-part-instance-p thing)
    (printing-random-object (thing stream)
      (format stream "~a part" (car thing)))
    t))

#+development
(def-development-describer describe-part-instance (thing)
  (when (development-part-instance-p thing)
    (format t "~S" thing)
    (loop for (slot-name value) on (cdr thing) by #'cddr
          as i from 2 by 2
          do
      (describe-slot-in-frame-or-structure i nil slot-name value))
    (format t "~%Valid? ")
    (format t "~A.~%"
            (if (validate-part-instance (car thing) thing) "Yes" "Nope"))
    thing))




;;;; The Basic Part Type



;;; Basic-part is included, by default, into all other part types.
;;; A basic part has these features: part-index, subparts,
;;; subpart-defaults, and subpart-exceptions.  These features
;;; are all of the type subparts collection, except part-index
;;; which is an integer.



;;; The `part-index' feature of a part description is used in
;;; to specify the ordinal position in the parent part's collection
;;; of parts of this kind.

;;; For example consider a chart axis with 20 tickmarks.  These
;;; tickmarks are usually generated implicitly but if the user selects
;;; the seventh tickmark and changes its color we will then create part
;;; description for that color and put that into the subpart-exceptions
;;; of the parent axis.  This exception part description will have a
;;; part index of 7.



;;; The `subpart-defaults' of a part description maybe used to
;;; store default values for any descendant part of a part description.

;;; The format of these subpart collections is limited.  Recall that
;;; a subpart collection has a list of part instances for each given
;;; part type.  In the subpart-collection of a subpart-defaults these
;;; lists will have only a single member.

;;; When scanning a part description the subpart-defaults are scanned
;;; by entering all the part descriptions provided.  This creates
;;; the effect, in the dynamic state, of setting all the features
;;; given.  This only works out in some cases.  If two types have
;;; the same feature, say background-color, and they both appear
;;; as descendants of the same parent you will get collisions.

(defvar subpart-defaults 'symbol-standing-in-for-unbound)

(defun-simple enter-subpart-defaults (new-value)
  (setf subpart-defaults new-value)
  (loop for (nil (part-template)) on new-value by #'cddr
        do (enter-part-description part-template))
  (part-stack-push subpart-defaults part-feature-recall-stack)
  nil)

(defun-simple exit-subpart-defaults ()
  (setf subpart-defaults (part-stack-pop part-feature-recall-stack))
  nil)



;;; The `subparts' of a part description hold
;;; the full set of instances of any subpart of that part description
;;; which are not implicitly generated.


(def-named-dynamic-extent basic-part
  (module parts))

(defvar-of-named-dynamic-extent subparts basic-part
  (global-binding 'symbol-standing-in-for-unbound))

(defun-simple enter-part-feature-subparts (new-value)
  (part-stack-push subparts part-feature-recall-stack)
  (setf subparts new-value)
  nil)

(defun-simple exit-part-feature-subparts ()
  (setf subparts (part-stack-pop part-feature-recall-stack))
  nil)

;;; The `subpart-exceptions' of a part description are used to
;;; record user modifications to implicitly generated descendant parts
;;; that are specified by the user.

;;; The format of the subpart collection is constrainted in the
;;; same way as for subpart-defaults.

;;; When exceptions are encountered during the scan of a part
;;; description they are pushed into a stack containing the currrent
;;; outstanding exceptions.  In the dynamic extent of this context
;;; the mechinism that generates the implied parts must search
;;; this stack to any outstanding exceptions.

(defvar subpart-exceptions 'symbol-standing-in-for-unbound)



;;; `Part-exceptions-from-parents' is a list of graph cons
;;; which dynamically stacks the contents of subpart-exceptions
;;; found in parents during the scan.  We currently search this
;;; data structure for exceptions.  That is slow but will do
;;; for now.

(defmacro with-part-type-scanning (&body body)
  `(let ((part-exceptions-from-parents ()))
     ,@body))

(defun-simple enter-subpart-exceptions (new-value)
  (setf subpart-exceptions new-value)
  (part-stack-push new-value part-exceptions-from-parents)
  nil)

(defun-simple exit-subpart-exceptions ()
  (setf subpart-exceptions (part-stack-pop part-exceptions-from-parents))
  nil)



(defvar-of-named-dynamic-extent current-part-description basic-part
  (global-binding nil))



(def-part-type basic-part
  (user-spelling nil))

(def-part-feature (basic-part subpart-defaults)
  (type subparts-collection)
  (means-of-scanning call-handlers
                     #'enter-subpart-defaults
                     #'exit-subpart-defaults))


(def-part-feature (basic-part subpart-exceptions)
  (type subparts-collection)
  (means-of-scanning call-handlers
                     #'enter-subpart-exceptions
                     #'exit-subpart-exceptions))

(def-part-feature (basic-part part-index)
  (type fixnum))





;;;; Misc. Simple Types Used In Part Features



;;; This section is used to accumulate many of the simple types,
;;; along with their supporting routines used in part features.
;;; They are gathered here, as a group, rather than at the point
;;; of their first (and often only) use so that it will be more
;;; likely we can integrate them with the evaluator's type models
;;; at some point.




(deftype-simple color-or-metacolor ()
  '(satisfies color-or-metacolor-p))

(deftype-simple compute-part-feature-of-type-color-or-metacolor ()
  '(satisfies compute-part-feature-of-type-color-or-metacolor-p))

(defun compute-part-feature-of-type-color-or-metacolor-p (data)
  (or (evaluated-computed-part-feature-p data)
      (color-or-metacolor-p data)))

(deftype-writer compute-part-feature-of-type-color-or-metacolor (x)
  (write-computed-part-feature 'symbol 'color-or-metacolor x))

;; A def-part-feature-type-reclaimer for
;; compute-part-feature-of-type-color-or-metacolor
;; was moved down below the definition of def-part-feature-type-reclaimer.  -jra 10/10/91

(deftype-simple text-alignment-kind () '(member left center right))
;; Note that if you change the type definition text-alignment-kind, you will
;; also need to change the category evaluator for message-properties, located in
;; definitions.lisp --yduJ 3/02

(defun workspace-measure-p (x)
  (with-temporary-gensym-float-creation workspace-distance-p
    (and (slot-value-number-p x)
         (let ((value (slot-value-number-value x)))
           (if (fixnump value)
               (<=f 1 value 4092)
               (<=e 1.0 value 4092.0))))))

(deftype-simple workspace-measure ()
  '(satisfies workspace-measure-p))

(deftype-simple text-size () '(member small large extra-large))

(deftype-simple value-domain-kind ()
  '(member inference-engine g2-simulator))

(deftype-simple trace-level ()  '(member 0 1 2 3))
(deftype-simple break-level ()  '(member 0 1 2 3))
(deftype-simple warning-level ()  '(member 0 1 2 3))

(defun simple-interval-p (x)
  (or (and (fixnump x)
           (<f 0 x))
      (and (managed-float-p x)
           (with-temporary-gensym-float-creation simple-interval-p
             (<e 0.0 (managed-float-value x))))
       ;; Do we have a policy about the upper limit?
       ))

(deftype-simple simple-interval () '(satisfies simple-interval-p))

(deftype-simple priority-level ()
  '(member 1 2 3 4 5 6 7 8 9 10))

(deftype-error-printer priority-level ()
  "not an integer from 1 through 10")

(deftype-simple cell-expression-and-text () 'cons)

(deftype-simple expression-cell-index () 'fixnum)

(deftype-writer slot-value-float (x)
  (with-temporary-gensym-float-creation write-annotation
    (let ((actual-value (slot-value-float-value x)))
      (if (=e (frounde actual-value) actual-value)
          (tformat "~(~D~)" (truncate actual-value))
          (tformat "~(~A~)" actual-value)))))

(deftype-writer boolean (x)
  (tformat "~A" (if x "true" "false")))

(deftype-simple text-string () '(satisfies text-string-p))

(deftype-simple network-access-kind () '(member nil read write))




;;;; The Formatted Part

;;; A `formatted-part' is a "mixin" included into other parts.  Parts
;;; that include formatted-part gain features that control some aspects
;;; of how the part is displayed on the screen.

;;; In this section we define many primitive simple types used in
;;; formatted parts.  For example color and metacolor.

;;; When scanning formatted parts the dynamic state is mantained in an
;;; instance of a text cell format frame.  This instance is stored in
;;; current-text-box-format, is named dynamic-table-cell-format.  When
;;; scanning a formatted part you must bind this and initialize it to the
;;; defaults your part requires.

(def-text-cell-format dynamic-text-cell-format
  text-cell-lines-justified? nil
  text-cell-line-quadding? right
  text-cell-left-margin 8
  text-cell-top-margin 4
  text-cell-right-margin 8
  text-cell-bottom-margin 4
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 8
  text-cell-font-map (hm14)
  text-cell-line-height 15
  text-cell-baseline-position 14
  text-cell-line-spacing 3
  default-word-spacing #.(convert-to-text-width 4)
  minimum-format-width-for-text-cell 300)


;; The following should never be used, but has been found to exist in some
;; 3.0 KBs; note that ALL instantiated format frames are saved whenever a
;; KB is saved.  It was found in ma:>ab>sys-proc.kb.1.  (MHD 10/12/91)

(DEF-TEXT-CELL-FORMAT NEW-TABLE-CELL-FORMAT
  TEXT-CELL-LINES-JUSTIFIED? NIL
  TEXT-CELL-LINE-QUADDING? RIGHT
  TEXT-CELL-LEFT-MARGIN 8
  TEXT-CELL-TOP-MARGIN 4
  TEXT-CELL-RIGHT-MARGIN 8
  TEXT-CELL-BOTTOM-MARGIN 4
  TEXT-CELL-PARAGRAPH-INDENTATION 0
  TEXT-CELL-TURNOVER-LINE-INDENTATION 8
  TEXT-CELL-FONT-MAP (HM14)
  TEXT-CELL-LINE-HEIGHT 18
  TEXT-CELL-BASELINE-POSITION 14
  TEXT-CELL-LINE-SPACING 3
  DEFAULT-WORD-SPACING #.(CONVERT-TO-TEXT-WIDTH 4)
  MINIMUM-FORMAT-WIDTH-FOR-TEXT-CELL 300)


(def-part-type formatted-part
  (user-spelling formatting-attributes))




;; Note that color-or-metacolor-p could vary over time.

(defun-simple enter-background-color (compute-part-feature-of-type-color-or-metacolor)
  (part-stack-push
    (text-cell-background-color? current-text-box-format)
    part-feature-recall-stack)
  (let ((color? (value-of-computed-part-feature compute-part-feature-of-type-color-or-metacolor 'background)))
    (setf
      (text-cell-background-color? current-text-box-format)
      (if (gensym-color-p color?)
          color?
          'background)))
  nil)

(defun-simple exit-background-color ()
  (setf
    (text-cell-background-color? current-text-box-format)
    (part-stack-pop part-feature-recall-stack))
  nil)

(def-part-feature (formatted-part background-color)
  (type compute-part-feature-of-type-color-or-metacolor)
  (means-of-scanning
    call-handlers #'enter-background-color #'exit-background-color)
  user-visible)


(def-part-feature (formatted-part line-color)
  (type color-or-metacolor)
  (means-of-scanning
    special-variable formatted-part-true-line-color)
  user-visible)

(def-part-feature (formatted-part border-color)
  (type color-or-metacolor)
  (means-of-scanning
    class-slot current-text-box-format text-box-border-color?)
  user-visible)

(def-part-feature (formatted-part text-color)
  (type color-or-metacolor)
  (means-of-scanning
    class-slot current-text-box-format text-cell-line-color?)
  user-visible)

(def-part-feature (formatted-part highlighted?)
  (type boolean)
  (means-of-scanning
    special-variable formatted-part-highlight-flag)
  (user-visible nil))

(def-part-feature (formatted-part text-alignment)
                  (type text-alignment-kind)
  (means-of-scanning
    class-slot current-text-box-format text-cell-line-quadding?)
  user-visible)

(defvar-of-named-dynamic-extent current-width-of-formatted-part formatted-part
  (global-binding 'symbol-standing-in-for-unbound))

;;; `Width' a part feature

(defun-simple enter-formatted-part-width (new-width)
  (part-stack-push current-width-of-formatted-part part-feature-recall-stack)
  (setf current-width-of-formatted-part new-width)
  (part-stack-push (minimum-format-width-for-text-cell current-text-box-format) part-feature-recall-stack)
  (setf (minimum-format-width-for-text-cell current-text-box-format) new-width)
  (part-stack-push (maximum-format-width-for-text-cell current-text-box-format) part-feature-recall-stack)
  (setf (maximum-format-width-for-text-cell current-text-box-format) new-width)
  nil)

;; This looks a little racy, since the width can be a slot-value-float.
;; - ben 1/27/95

(defun-simple exit-formatted-part-width ()
  (setf (maximum-format-width-for-text-cell current-text-box-format) (part-stack-pop part-feature-recall-stack))
  (setf (minimum-format-width-for-text-cell current-text-box-format) (part-stack-pop part-feature-recall-stack))
  (setf current-width-of-formatted-part (part-stack-pop part-feature-recall-stack))
  nil)

(def-part-feature (formatted-part width)
  (type workspace-measure)
  (means-of-scanning
    call-handlers #'enter-formatted-part-width #'exit-formatted-part-width)
  user-visible)

(def-part-feature (formatted-part height)
  (type workspace-measure)
  (means-of-scanning special-variable current-height-of-formatted-part)
  user-visible)

(defvar part-text-size-parameters
  '((small
      (hm14)                                        ; text-cell-font-map
      18                                        ; text-cell-line-height
      14                                        ; text-cell-baseline-position
      3                                                ; text-cell-line-spacing
      #.(convert-to-text-width 5)                ; default-word-spacing
      #.(convert-to-text-width 4)                ; minimum-word-spacing
      #.(convert-to-text-width 12)                ; maximum-word-spacing
      )
    (large ; used to be `regular' in the old naming scheme
      (hm18)                                        ; text-cell-font-map        -- 1 en = 10 workspace units
      20                                        ; text-cell-line-height
      15                                        ; text-cell-baseline-position
      2                                                ; text-cell-line-spacing
      #.(convert-any-number-to-text-width-at-compile-time 6.75)        ; default-word-spacing -- 2/3 en
      #.(convert-to-text-width 5)                ; minimum-word-spacing         -- 1/2 en
      #.(convert-to-text-width 15)                ; maximum-word-spacing         -- 3/2 en
      )
    (extra-large ; used to be `large' in the old naming scheme
      (hm24)                                        ; text-cell-font-map        -- 1 en = 14 workspace units
      26                                        ; text-cell-line-height
      19                                        ; text-cell-baseline-position
      3                                                ; text-cell-line-spacing
      #.(convert-any-number-to-text-width-at-compile-time 8.75)        ; default-word-spacing -- 5/8 en
      #.(convert-to-text-width 7)                ; minimum-word-spacing -- 1/2 en
      #.(convert-to-text-width 21)                ; maximum-word-spacing --  3/2 en
      )
    #|| This was what was used for extra-large in the old naming scheme
    (extra-large
      (hm24)                                        ; text-cell-font-map
      35                                        ; text-cell-line-height
      19                                        ; text-cell-baseline-position
      5                                                ; text-cell-line-spacing
      #.(convert-to-text-width 10)                ; default-word-spacing
      #.(convert-to-text-width 8)                ; minimum-word-spacing
      #.(convert-to-text-width 14)                ; maximum-word-spacing
      ) ||#
    ))

(defun-simple enter-text-size (new-text-size)
  (let ((new-settings (rest (assq new-text-size part-text-size-parameters))))
    (macrolet ((set-and-remember (what)
                 `(part-stack-push
                    (shiftf (,what current-text-box-format) (pop new-settings))
                    part-feature-recall-stack)))
      (set-and-remember text-cell-font-map)
      (set-and-remember text-cell-line-height)
      (set-and-remember text-cell-baseline-position)
      (set-and-remember text-cell-line-spacing)
      (set-and-remember default-word-spacing)
      (set-and-remember minimum-word-spacing)
      (set-and-remember maximum-word-spacing)))
  nil)

(defun-simple exit-text-size ()
  (macrolet ((reset (what)
                    `(setf (,what current-text-box-format)
                           (part-stack-pop part-feature-recall-stack))))
    (reset maximum-word-spacing)
    (reset minimum-word-spacing)
    (reset default-word-spacing)
    (reset text-cell-line-spacing)
    (reset text-cell-baseline-position)
    (reset text-cell-line-height)
    (reset text-cell-font-map))
  nil)

(def-part-feature (formatted-part text-size)
  (type text-size)
  (means-of-scanning
    call-handlers #'enter-text-size #'exit-text-size)
  user-visible)

;;; This exists in order to bring up to date any charts and new-tables which still
;;; use the old naming scheme for text-sizes. It will be called by their
;;; initialize-after-reading methods.

(defun standardize-text-size-feature-in-part-description (part-description)
  (loop for p on (rest part-description) by #'cddr
        do
    (when (eq 'text-size (car p))
      (setf (cadr p)
            (or (cdr (assoc (cadr p) '((small . small) (regular . large)
                                       (large . extra-large) (extra-large . extra-large))))
                (progn #+development
                       (cerror "Use text-size small" "Invalid old style text-size: ~A" (cadr p))
                       'small))))))

;;;; Default Formatted-part For Current

(defun get-default-formatted-part-of-class ()
  (frame-class-case *current-computation-frame*
    (new-table
     '(formatted-part
        text-color foreground
        line-color foreground
        border-color foreground
        background-color transparent

        text-size small
        text-alignment right))
    (t
      #+development
      (cerror "Resume"
              "Not good, get-default-formatted-part-of-class when ~S is current-computation-fame"
              *current-computation-frame*)
      '(formatted-part))))




;;;; Validating a Part Instance




;;; Validate-part-instance will check that a part, and its subparts,
;;; conforms to its declarations.  This is a recursive process, and
;;; a handful of dynamic constructs are used to guide it.
;;; A catch is wrapped around the entire validation to allow it to
;;; unwind when any invalid part of the instance is uncovered.  Part
;;; descriptions that are used to as wild cards have slightly different
;;; rules than those that are actually instances.  The special variable
;;; validate-defaults, is used to flag that.

#+development
(def-global-property-name part-feature-type-validation-routine)

(defmacro def-part-feature-type-validation (type-name (instance) &body body)
  #-development
  (declare (ignore type-name instance body))
  #+development
  (let ((routine-name (intern (format nil "FEATURE-TYPE-VALIDATOR-FOR-~A" type-name))))
    (unless (symbolp type-name) (warn "~S, the type-name, isn't a symbol." type-name))
    (unless (valid-simple-type-specification type-name)
            (warn "~S, the type name, is not a known simple type." type-name))
    `(progn
       (defun ,routine-name (,instance) ,@body)
       (setf (part-feature-type-validation-routine ',type-name)
             ',routine-name))))


#+development
(defvar validate-path)

#+development
(defvar validate-defaults)

#+development
(defmacro with-validation-frame ((place type value) &body body)
  `(let ((validate-path
           (list* (list ,place ,type ,value)
                  validate-path)))
     ,@body))

#+development
(defmacro with-validation-catching (&body body)
  `(let ((validate-defaults nil)
         (validate-path ()))
     (catch 'validation-failure
       ,@body
       T)))

#+development
(defun fail-validation (arg)
  (let ((*print-case* :downcase)
        (*print-level* 1)
        (*print-length* 2))
    (format t "~%~A" arg)
    (loop for (place type value) in validate-path
          do
      (format t "~%~A:~A ~20T i.e. ~S" place type value))
    (throw 'validation-failure nil)))

#+development
(defun-allowing-unwind validate-part-instance (part-type-name part-instance)
  (with-validation-catching
    (with-validation-frame ('<given> part-type-name part-instance)
      (validate-part-instance-inner part-type-name part-instance))))

#+development
(defun validate-part-instance-inner (part-type-name part-instance)
  (let ((part-type-description (part-type-description part-type-name)))

    (unless part-type-description
      (fail-validation "unknown part type."))

    (unless (consp part-instance)
      (fail-validation "Part instance isn't even a cons."))

    (unless (eq part-type-name (first part-instance))
      (fail-validation "Header wrong."))

    (loop
      for (feature-name feature-value) on (rest part-instance) by #'cddr
      do
      (validate-part-feature part-type-name feature-name feature-value))))

#+development
(defun validate-part-feature (part-type-name feature-name feature-value)
  (let* ((part-feature-description
           (part-feature-description part-type-name feature-name))
         (type (part-feature-type part-feature-description))
         (type-description
           (if (not part-feature-description) '<unknown> type))
         (subpart-collection?
           (and (consp type-description)
                (eq 'subparts-collection (first type-description))))
         validation-routine)

    (with-validation-frame (feature-name type-description feature-value)
      (cond

        ((not part-feature-description )
         (fail-validation "Unknown feature."))

        (subpart-collection?
         (loop
            for (subpart-type subparts-list) on feature-value
                              by #'cddr
            do
           (unless (part-type-description subpart-type)
             (fail-validation "unknown part type key in subpart-collection"))
           (loop for subpart in subparts-list
                 do (validate-part-instance-inner subpart-type subpart))))

        ((not (simple-typep feature-value type))
         (fail-validation "feature of bad type"))

        ((setf validation-routine (part-feature-type-validation-routine type))
         (funcall validation-routine feature-value))))))







;;;; Debugging Tools for Part Declarative Data Structures and Dynamic State




;;; These routines, available only in development, provide utilities
;;; to display the current state of the part declarative data structures.
;;;  `show-part-type-names' returns a list of all the known part types.
;;;  `show-part-type-description' will show what we know about a
;;;      particular type.
;;;  `show-part-type-feature-names' returns a list of all the known part
;;;      attribute names.
;;;  `show-dynamic-bindings-for-parts' will show the current values
;;;      in the dynamically scoped variables for attributes of a given
;;;      set of part types.

#+development
(defun show-part-type-names ()
  (let ((result ()))
    (do-symbols (s (find-package "AB"))
      (let ((part-type-description (part-type-description s)))
        (when part-type-description
          (push s result))))
    result))

#+development
(defun show-part-type-description (part-type-name)
  (let ((*print-case* :downcase))
    (let* ((part-type-description (part-type-description part-type-name)))
      (cond
        ((not part-type-description)
         (format t "~%~A not a known part-type" part-type-description))
        (T
         (format t "~%~A, a part type" (getf part-type-description 'part-type-name))
         (loop
          for (feature-name feature-description . nil)
              on (part-type-features part-type-description)
                            by #'cddr
          do (format t "~%  ~A~20T~S" feature-name feature-description)))))))

#+development
(defun show-part-type-feature-names ()
  (let ((*print-case* :downcase))
    (let ((result ()))
      (do-symbols (s (find-package "AB"))
        (let ((info (get s 'feature-on-these-part-types)))
          (when info
            (push s result)
            (format t "~%~S:~{~S ~}" s info))))
      result)))

#+development
(defun show-dynamic-bindings-for-parts (&rest part-types)
  (let ((*print-case* :downcase))
    (loop for part-type-name in part-types
          do
      (loop for (part-feature nil)
                on (part-type-features (part-type-description part-type-name))
                by #'cddr
            do
        (format t "~%~S~30T~S" part-feature (symbol-value part-feature))))))







;;;; Managing The Dynamic Scope When Scanning a Part Description




;;; With-part-description provides a dynamic context within which
;;; the state vector has been brought into synch with a given
;;; part's description.


(defmacro mark-part-description-recall-stack ()
  `(part-stack-push-macro 'mark part-feature-recall-stack))

(defun enter-part-description (part-description)
  (loop for (part-feature-name new-feature-value) on (part-description-features part-description)
                               by #'cddr
        as part-feature-index = (part-feature-index part-feature-name)
        as enter-feature-handler = (part-feature-enter-method part-feature-index)
        do
    #+development
    (assert enter-feature-handler
            () "Apparently the part-feature-index ~S is wrong for ~S."
            part-feature-index part-feature-name)
    ;; Save old value in state vector
    (funcall-simple-compiled-function enter-feature-handler new-feature-value)
    (part-stack-push-macro part-feature-index part-feature-recall-stack)))

(defmacro exit-part-description ()
  `(loop
     for part-feature-index = (part-stack-pop part-feature-recall-stack)
     until (eq part-feature-index 'mark)
     as exit-feature-handler  = (part-feature-exit-method part-feature-index)
     do (funcall-simple-compiled-function exit-feature-handler)))


(defmacro with-part-description ((part-description) &body body)
  `(let ((old-current-part-description current-part-description)
         #+development
         (old-recall-stack part-feature-recall-stack))
     (setf current-part-description ,part-description)
     (when maintain-stack-of-current-part-descriptions-p
       (part-stack-push-macro current-part-description stack-of-current-part-descriptions))
     (mark-part-description-recall-stack)
     (unwind-protect-for-development
       with-part-description
       (with-named-dynamic-extent-given (first current-part-description) ()
         (enter-part-description current-part-description)
         ,@body)
       (progn
         (exit-part-description)
         (setf current-part-description old-current-part-description)
         (when maintain-stack-of-current-part-descriptions-p
           (part-stack-pop stack-of-current-part-descriptions))
         #+development
         (assert (eql old-recall-stack
                      part-feature-recall-stack)
                 () "after cleaning up a with-part-description the recall stack wasn't right")
         ))))

(defmacro with-part-descriptions ((part-description &rest more-part-descriptions?)
                                  &body body)
  (if more-part-descriptions?
      `(with-part-description (,part-description)
         (with-part-descriptions (,@more-part-descriptions?)
           ,@body))
      `(with-part-description (,part-description)
         ,@body)))

(defmacro with-part-exceptions ((part-type index) &body body)
  `(with-part-description ((lookup-part-exception ,part-type ,index))
     ,@body))


(defun lookup-part-exception (part-type index)
  (loop for exception-collection in part-exceptions-from-parents
        as exception-for-part-type? = (getf exception-collection part-type)
        do
    (when exception-for-part-type?
      (loop for part-exception in exception-for-part-type?
            do
        (when (eql index (getf (rest part-exception) 'part-index))
          (return-from lookup-part-exception part-exception))))))

;; This handling of exceptions is very simple minded.  It wins in that the
;; it doesn't build a lot of dynamic data structure, but it loses in that
;; the lookup-part-exception code must engage in that search every time it
;; gets called.  If that was done for every data point we would be in big
;; trouble!

;; Secondly it doesn't handle double nesting of the exceptions.  For example
;; a situation where both the parent, and grand parent provided exceptions
;; for an particular part.







;;;; Writing For Part Descriptions


;;; Writing the compiled version of an part description (or annotation)
;;; is a little complex since you can't emit individual statements
;;; during the recursive scan of the part template until you get to the
;;; individual key/value pairs in the templates.  What you write at that
;;; point for the annotation part pattern depends on the path you took
;;; during the recursive scan.  The dynamic variable
;;; write-annotation-part-pattern-stack is used to the information seen
;;; on that path.

(def-named-dynamic-extent writing-annotations
  (module parts))

(defvar-of-named-dynamic-extent write-annotations-part-pattern-stack writing-annotations)
(defvar-of-named-dynamic-extent wrote-first-annotation-flag          writing-annotations)
(defvar-of-named-dynamic-extent part-features-to-write               writing-annotations)
(defvar-of-named-dynamic-extent write-annotations-indent             writing-annotations)
(defvar-of-named-dynamic-extent write-annotations-suppress-the-p     writing-annotations)

;;; `Write-annotation' does writes the individual annotations out.
;;; When called the length of write-annotation-part-pattern-stack
;;; will be a multiple of three.  Each tuple of three elements
;;; consists of:
;;;   1. nil, or the part-index of the element passed thru.
;;;   2. the part type of the template stepped thru.
;;;   3. the collection part-feature stepped thru.

(defun write-annotation (part-type part-feature feature-value)
  (within-named-dynamic-extent writing-annotations
    (when (or (eq T part-features-to-write)
              (memq part-feature part-features-to-write))
      ;; Write the LHS of the annotation.
      (let ((part-feature-user-name (get-user-spelling part-feature 'part-feature)))
        (when wrote-first-annotation-flag
          (tformat ";~%"))
        (setf wrote-first-annotation-flag t)
        (loop for i from 0 to write-annotations-indent do (twrite-char #.%space))
        (unless write-annotations-suppress-the-p
          (tformat "the "))
        (tformat "~(~A~)" part-feature-user-name)
        (loop for (part-index? ancestor-part-type collection-feature-name)
                  on write-annotations-part-pattern-stack by #'cdddr
              as ancestor-part-type-user-name = (get-user-spelling ancestor-part-type 'part-type)
              do
          (case collection-feature-name
            (subpart-defaults
             (tformat "~( of any ~A~)"
                      ancestor-part-type-user-name))
            (subpart-exceptions
             (tformat "~( of ~A ~D~)"
                      ancestor-part-type-user-name part-index?))

            (this-part-defaults                                    ; -fmw, 1/20/94
             (tformat "~( of this ~A~)"
                      ancestor-part-type-user-name))
            )))
      ;; Write assignment, and the RHS of the annotation
      (let ((feature-type
              (part-feature-type
                (part-feature-description part-type part-feature))))
        (tformat "~( ~A ~)"
                 (if (or (symbolp feature-value)
                         (eql feature-type 'compute-part-feature-of-type-color-or-metacolor) ;; HACK!!
                         )
                     "is" "="))
        (write-instance-of-simple-type feature-type feature-value)))))



;;; `Write-annotation-part-pattern' will sweep over a set of
;;; of subpart templates in a part template and write out
;;; any annotations in those template.

(defun write-annotation-part-pattern (part-feature subpart-template-collection)
  (within-named-dynamic-extent writing-annotations
    (slot-value-push part-feature write-annotations-part-pattern-stack)
    (loop
    for (part-type part-templates-for-type) on subpart-template-collection by #'cddr
    do
      (slot-value-push part-type write-annotations-part-pattern-stack)
      (loop for part-template in part-templates-for-type
            do (write-annotations-in-part-template part-template))
      (slot-value-pop write-annotations-part-pattern-stack))
    (slot-value-pop write-annotations-part-pattern-stack)))

;;; `Write-annotations-in-part-template' scans a part-template
;;; and will write out one annotation for each part-feature, while
;;; letting write-annotation-part-pattern write out the annotations
;;; for the subpart collection part-features.

(defun write-annotations-in-part-template (part-template)
  (within-named-dynamic-extent writing-annotations
    (slot-value-push
      (get-simple-part-feature part-template 'part-index)
      write-annotations-part-pattern-stack)
    (loop with (part-type . part-features) = part-template
          for (part-feature feature-value) on part-features
                            by #'cddr
          do
      (case part-feature
        ((subpart-defaults subpart-exceptions)
         (write-annotation-part-pattern part-feature feature-value))
        (part-index
         ;; don't write this
         )
        (otherwise
         (write-annotation part-type part-feature feature-value))))
    (slot-value-pop write-annotations-part-pattern-stack)))

;;; `Write-part-description' is called from slot value writers to display
;;; part descriptions.  The optional argument provides a way to limit which
;;; features are actually displayed.

(defun write-part-description (annotations-slot-value
                               &optional
                               (part-features-to-write t)
                               (indent 0)
                               (suppress-the-p nil))
  (with-named-dynamic-extent writing-annotations
                             ((write-annotations-part-pattern-stack ())
                              (wrote-first-annotation-flag nil)
                              (write-annotations-indent indent)
                              (write-annotations-suppress-the-p suppress-the-p))
    (loop with (part-type . part-features) = annotations-slot-value
          for (part-feature feature-value) on part-features
                            by #'cddr
          do (case part-feature
               ((subpart-defaults subpart-exceptions)
                (write-annotation-part-pattern part-feature feature-value))
               (otherwise
                (write-annotation part-type part-feature feature-value)))
          finally
            (unless wrote-first-annotation-flag
              (twrite-symbol 'none)))
    #+development
    (assert (null write-annotations-part-pattern-stack))))







;;;; Compiling And Semantic Checking For Part Descriptions




;;; Semantic checking of part description parses is done in the
;;; dynamic extent of a catch handler.  When semantic errors are
;;; encountered a string describing the semantic error is thrown
;;; to this catch.

;;; `With-semantic-checking-of-part-description' sets up the
;;; catch.

(defmacro with-semantic-checking-for-part-description (&body body)
  `(catch 'semantic-error
     ,@body
     nil
     ))


(defvar last-semantic-check-error-string nil)

;;; `Semantic-error-exit' is used to throw the semantic error message.

(defmacro semantic-error-exit (error-string)
  (avoiding-variable-capture (error-string)
    `(progn
       (setq last-semantic-check-error-string ,error-string)
       (throw 'semantic-error ,error-string))))



;;; `Semantic-check-part-description' simulates the evaluation of the
;;; parse, checking the semantics of the subexpressions.  The type of
;;; each part is computed, and checks are made that only known visible
;;; features of those parts are accessed.  Finally checks are made that
;;; only values of the appropriate type are bound to the features changed.

;;; If a string is returned, that string is a description of any semantic
;;; errors uncovered.  The string should be reclaimed by the caller.

(defun-allowing-unwind semantic-check-part-description
                       (part-description-parse)
  (with-semantic-checking-for-part-description
    (loop for annotation in (rest part-description-parse)
          as statement-number from 1
          as (nil part-lookup (nil part-feature) value-desired) = annotation
          ;; i.e. (set-simple-part-feature (lookup-subpart-of-collection ...) indicator-visible 'T)
          as subpart-type = (semantic-check-part-lookup statement-number part-lookup)
          as hidden-features = (part-type-hidden-features (part-type-description subpart-type))
          do
      (unless (part-feature-description subpart-type part-feature)
        (let ((subpart-type-user-spelling (get-user-spelling subpart-type 'part-type)))
          (semantic-error-exit
            (tformat-text-string
              "~(In statement #~D, ~A is not a known feature of ~A ~A.~)"
              statement-number
              (get-user-spelling part-feature 'part-feature)
              (supply-a-or-an subpart-type-user-spelling)
              subpart-type-user-spelling))))
      (when (memq part-feature hidden-features)
        (let ((part-type-user-spelling
                (get-user-spelling subpart-type 'part-type)))
          (semantic-error-exit
            (tformat-text-string
              "~(In statement #~D, ~A is not a supported attribute of ~A ~A.~)"
              statement-number
              (get-user-spelling part-feature 'part-feature)
              (supply-a-or-an part-type-user-spelling)
              part-type-user-spelling))))
      (let ((actual-value (cond
                              ((atom value-desired)
                               value-desired)
                              ((eq 'quote (first value-desired))
                               (second value-desired))
                              ((and (eql 'copy-for-slot-value (car value-desired))
                                    (eql 'quote (car (second value-desired))))
                               (second (second value-desired)))
                              ((eq 'compile-computed-part-feature (first value-desired))
                               ;; This kludge is safe only because we know this is the only
                               ;; computed part type.
                               'red)))
            (type-spec
              (part-feature-type
                (part-feature-description
                  subpart-type
                  part-feature))))
        (unless (simple-typep actual-value type-spec)
          (semantic-error-exit
            (twith-output-to-text-string
              (tformat "~(In statement #~D for ~S: ~)"
                       statement-number
                       (get-user-spelling part-feature 'part-feature))
              (tformat-type-error
                (if (symbolp actual-value)
                    (get-user-spelling actual-value 'constant)
                    actual-value)
                type-spec))))))))



;;; `Semantic-check-part-lookup' returns the type of the part-lookup, after checking
;;; the semantics of any nested expressions.

(defun semantic-check-part-lookup (statement-number part-lookup)
  ;; part-lookup are, by example, like:
  ;; (lookup-subpart-of-collection current-part-description 'subpart-defaults 'data-series nil)
  ;; current-part-description
  (cond
    ((eq part-lookup 'current-part-description)
     (first current-part-description))
    (T
     (gensym-dstruct-bind
       ((nil parent-part-lookup (nil subpart-flavor) (nil desired-subpart-type) nil) part-lookup)
       (case subpart-flavor
         (subpart-defaults
          ;; Check that this type of object have a default over all instances. (axis can't)
          (unless (part-type-allow-defaulting-in-parents
                    (part-type-description
                      desired-subpart-type))
            (semantic-error-exit
              (tformat-text-string "Defaulting via \"any ~(~A~)\" is not supported."
                                   (get-user-spelling desired-subpart-type 'part-type)))))
         (subpart-exceptions
          ;; check that this type of part can have individual exceptions. (data-points can't)
          (unless (part-type-allow-individual-exceptions-in-parents
                    (part-type-description
                      desired-subpart-type))
            (semantic-error-exit
              (tformat-text-string "Setting a feature of an individual ~(~A~) is not supported."
                                   (get-user-spelling desired-subpart-type 'part-type))))))


       (let ((subpart-type (semantic-check-part-lookup statement-number parent-part-lookup)))
         ;; check that this subpart-type can be inside a this subpart-type  TBD
         (declare (ignore subpart-type))
         desired-subpart-type
         )))))

;; Should check a part-type-description slot to determine if wild carding or individual
;; setting is supported.



;;; `Compile-part-description' transforms the parse of part description into an actual
;;; part description.  The part description is scanned twice, once to check for semantic
;;; errors, and once to construct the resulting part description.

;;; The implementation of this routine has unusual memory management.  The parse is moved
;;; out of the phrase-cons memory managment domain and into the slot value memory management
;;; domain.  All the compilation work is then done in the slot value memory management
;;; domain.  Finally it is copied back into the phrase cons memory management domain.
;;; This is done because all the routines that manipulate part descriptions work in
;;; the slot value memory management domain.  These include, for example, the type
;;; checking and the part description modifiers.

;;; This must be called only withing a working-on-annotated-frame dynamic extent.

(defun compile-part-description (part-description-parse part-type)
  (when (or (eq part-description-parse 'none)
            (null part-description-parse))
    (return-from compile-part-description nil))
  (setf (first part-description-parse) 'progn)        ; yes: rewrite to be (progn ...)
  (let ((result bad-phrase)
        error-message?)

    (setq error-message?
          (kludge-to-avoid-computed-part-feature-in-certain-places
            part-description-parse))

    (unless error-message?
      (let* ((part-description-parse-in-slot-value-conses
               (copy-for-slot-value part-description-parse))
             (current-part-description
               (slot-value-list part-type)))

        ;; Semantic checking pass.
        (setq error-message?
              (let ((current-part-description
                      (slot-value-list part-type)))
                (prog1
                  (semantic-check-part-description part-description-parse-in-slot-value-conses)
                  (reclaim-slot-value-list current-part-description))))


        ;; Convert into a part description
        (unless error-message?
          (setq result (simple-eval part-description-parse-in-slot-value-conses))
          ;; No point in trying to use multiple-value-setq, because simple-eval
          ;; does not use multiple-values in its recursion. -jv, 6/3/97

          (cond
            ((eq result bad-phrase)
             (setq error-message?
                   (if (or (null last-semantic-check-error-string)
                           (probable-reclaimed-wide-string-p
                             last-semantic-check-error-string))
                       (twith-output-to-text-string
                         (twrite-string "  Please report this bug to Gensym ")
                         (twrite-string "software support with the source code ")
                         (twrite-string "which caused this message."))
                       last-semantic-check-error-string))
             (setq last-semantic-check-error-string nil))
            (t
             ;; Global consistency check if necesary.
             (let ((semantic-check-function? (part-type-semantic-check
                                               (part-type-description part-type))))
               (when semantic-check-function?
                 (setq error-message?
                       (funcall semantic-check-function? current-part-description)))))))

        ;; Move result back into editor pools
        (if error-message?
            (setf result bad-phrase)
            (setf result
                  (copy-for-phrase current-part-description)))
      ;; Reclaim temps.
      (reclaim-slot-value part-description-parse-in-slot-value-conses)
      (reclaim-slot-value current-part-description)))

    (values result error-message?)))



;;; `kludge-to-avoid-computed-part-feature-in-certain-places' implements the bogus
;;; restriction that you may not put a computed formating feature in the default cell
;;; format of a new-table.

(defun kludge-to-avoid-computed-part-feature-in-certain-places (parse-of-part-description)
  (when (and (eql (name-of-slot-being-edited current-edit-state) 'default-cell-format)
             (frame-of-class-p (frame-being-edited? current-edit-state) 'new-table))
    (kludge-to-avoid-computed-part-feature-in-certain-places-1 parse-of-part-description)))

(defun kludge-to-avoid-computed-part-feature-in-certain-places-1 (parse-tree)
  (typecase parse-tree
    (cons
     (or
       (kludge-to-avoid-computed-part-feature-in-certain-places-1 (car parse-tree))
       (kludge-to-avoid-computed-part-feature-in-certain-places-1 (cdr parse-tree))))
    (symbol
     (when (eq 'compile-computed-part-feature parse-tree)
       (copy-constant-wide-string #w"This attribute may not contain any computed expressions.")))))








;;;; Reclaiming A Part Description


;;; Part descriptions should be reclaimed by `reclaim-part-description'.
;;; Individual features should be reclaimed via `reclaim-part-features'.
;;; The declared type is used to guide the reclaimer choosen for a
;;; given part feature.  The macro `def-part-feature-type-reclaimer' is
;;; used to create the routine that will reclaim a given feature.  By default
;;; reclaim-slot-value is used to reclaim a part feature and its backbone.

;;; This section contains: the reclaiming routines; the data structures that
;;; guide those routines;  the macros for defining those data structures; and
;;; finally the reclaimers for the standard slots in part descriptions.



;;; The global property `part-feature-type-reclaimer' is used to assocate
;;; from simple type names to the function naming the reclaimer for that
;;; simple type.

(def-global-property-name part-feature-type-reclaimer)

(defmacro def-part-feature-type-reclaimer (type-name (value-to-reclaimed) &body body)
  (let ((reclaimer-name (intern (format nil "FEATURE-TYPE-RECLAIMER-FOR-~A" type-name))))
    (unless (symbolp type-name) (warn "~S, the type-name, isn't a symbol." type-name))
    (unless (valid-simple-type-specification type-name)
      (warn "~S, the type name, is not a known simple type." type-name))
    `(progn
       (defun ,reclaimer-name (,value-to-reclaimed) ,@body)
       (setf (part-feature-type-reclaimer ',type-name)
             ',reclaimer-name))))



;;; `Reclaim-part-description' is used to reclaim a part description.
;;; The backbone of the part description is reclaimed into the slot-value
;;; cons pool.  The individual features are reclaimed by reclaim-part-feature.

(defun reclaim-part-description (part-description)
  (delete-all-editors-of-cell part-description)
  (when part-description
    (reclaim-part-features
      (car part-description)
      (cdr part-description))
    (reclaim-slot-value-cons part-description)
    nil))


;;; `Reclaim-part-features' will reclaim a list of part features, given
;;; the enclosing part type and the list of features as arguments.

(defun reclaim-part-features (part-type part-features)
  (assert-that-within-named-dynamic-extent 'working-on-annotated-frame)
  (loop for p on part-features by #'cddr
        as (part-feature-name part-feature-value) = p
        do
    (reclaim-part-feature part-type part-feature-name part-feature-value)
    (setf (second p) nil))
  (reclaim-slot-value-list part-features)
  nil)



;;; `Reclaim-part-feature' will call the declared reclaimer
;;; declared for features of this type.  If no such reclaimer was
;;; declared it will return the value to the slot value pools.

(defun reclaim-part-feature (part-type feature-name feature-value)
  (assert-that-within-named-dynamic-extent 'working-on-annotated-frame)
  (let* ((part-feature-type (part-feature-type (part-feature-description part-type feature-name)))
         (part-type-reclaimer (part-feature-type-reclaimer
                                (if (symbolp part-feature-type)
                                    part-feature-type
                                    (car part-feature-type)))))
    (if part-type-reclaimer
        (funcall part-type-reclaimer feature-value)
        (reclaim-slot-value feature-value))))



;;; We define reclaimers for standard features that contain part collections,
;;; this assures that the reclaiming process recurses approprately

(def-part-feature-type-reclaimer subparts-collection (the-part-collection)
  (loop for (nil list-of-part-descriptions)
            on the-part-collection by #'cddr
        do
    (loop for p2 on list-of-part-descriptions
          do
      (setf (car p2)
            (reclaim-part-description (car p2)))))
  (reclaim-slot-value-tree the-part-collection))



;;; The reclaimer for `compute-part-feature-of-type-color-or-metacolor'
;;; deactivates any embedded cell prior to deleteing it.  This allows the
;;; update caused by deactivation to be projected while the cell is still
;;; well formed.  Since deleting is recursive siblings of this feature
;;; may already have been deleted, and the projection must be robust in
;;; the presence of any such deleting, or the cell must have been deactivated
;;; earlier in the delete.

(def-part-feature-type-reclaimer compute-part-feature-of-type-color-or-metacolor
                                 (compute-part-feature-of-type-color-or-metacolor)
  (when (evaluated-computed-part-feature-p compute-part-feature-of-type-color-or-metacolor)
    (deactivate-cell-of-g2-cell-array
      (cell-array current-annotated-frame)
      (get-simple-part-feature
        compute-part-feature-of-type-color-or-metacolor
        'expression-cell-index))
    (reclaim-part-description compute-part-feature-of-type-color-or-metacolor)))








;;;; Accessors and Editing Operations For Part Descriptions




;;; Generally part descriptions are modified using the routines in
;;; in this section.  Parsing, a primary example, creates a progn
;;; that consists of calls to the routines defined in this section.

;;; A quick overview of these routines:
;;;  part-description-of-frame   -- almost aka get-slot-value
;;;  get-simple-part-feature     -- fetch feature
;;;  set-simple-part-feature     -- set feature
;;;  remove-simple-part-feature  -- discard feature
;;;
;;;  get-subpart-collection      -- fetch entire collection.
;;;  set-subpart-collection-without-reclaiming
;;;                              -- set entire collection.
;;;
;;;  get-subpart-of-collection     -- fetch individual of collection.
;;;  lookup-subpart-of-collection  -- fetch indivdual, creating if necessary.
;;;  set-simple-part-features
;;;  get-simple-part-feature-as-float
;;;
;;; The operations that modify part descriptions will call the approprate
;;; reclaimer.  They must be invoked with a working-on-annotated-frame dynamic
;;; extent established.


(defun part-description-of-frame (slot-name frame)
  (get-slot-value frame slot-name))

(defun get-simple-part-feature (part-description part-feature)
  #+development
  (unless (listp (rest part-description))
    (cerror "whatever" "non part-description received"))
  (getf (rest part-description) part-feature))

(defun get-subpart-collection (part-description part-feature part-type)
  (let* ((subpart-collection (get-simple-part-feature part-description part-feature))
         (subparts-for-this-type (getf subpart-collection part-type)))
    subparts-for-this-type))

(defun set-subpart-collection-without-reclaiming
       (part-description collection-feature part-type new-collection)
  (loop with subpart-collection
          = (get-simple-part-feature part-description collection-feature)

        initially
          (unless (memq part-type subpart-collection)
            (set-simple-part-feature
              part-description
              collection-feature
              (setf subpart-collection
                    (slot-value-cons
                      part-type
                      (slot-value-cons
                        nil
                        subpart-collection)))))

        for p on subpart-collection by #'cddr
        as subpart-type = (first p)
        when (eq subpart-type part-type)
          do
            (setf (second p) new-collection)
            (return nil)))

(defun get-subpart-of-collection (part-description part-feature part-type part-index)
  (let* ((subparts-for-this-type
           (get-subpart-collection part-description part-feature part-type)))
    (case part-feature
      (subparts
       (nth part-index subparts-for-this-type))
      (subpart-exceptions
       (loop for exceptional-part-template in subparts-for-this-type
             as exceptional-part-index =
               (get-simple-part-feature exceptional-part-template 'part-index)
             do
         (cond
           ((> exceptional-part-index part-index)
            (return nil))
           ((= exceptional-part-index part-index)
            (return exceptional-part-template)))))
      (subpart-defaults
       (first subparts-for-this-type)))))

;;; `Set-simple-part-feature' maintains arrival order.

(defun set-simple-part-feature (part-description part-feature new-value)
  (assert-that-within-named-dynamic-extent 'working-on-annotated-frame)
  (unless (eq new-value bad-phrase)
    (loop with (part-type . part-features) = part-description
          for (key . value-cons) on part-features by #'cddr
          do (when (eq key part-feature)
               (reclaim-part-feature part-type key (car value-cons))
               (return (setf (car value-cons) new-value)))
          finally
            (let ((new-bit (slot-value-list part-feature new-value)))
              (if (null value-cons)        ; value-cons is null iff part-description is empty
                  (setf (cdr part-description) new-bit)
                  (setf (cdr value-cons) new-bit)))))
  new-value)

(defun set-simple-part-feature-without-reclaiming (part-description part-feature new-value)
  (assert-that-within-named-dynamic-extent 'working-on-annotated-frame)
  (loop with (nil . part-features) = part-description
        for (key . value-cons) on part-features by #'cddr
        do (when (eq key part-feature)
             (return (setf (car value-cons) new-value)))
        finally
          (let ((new-bit (slot-value-list part-feature new-value)))
            (if (null value-cons)                ; value-cons is null iff part-description is empty
                (setf (cdr part-description) new-bit)
                (setf (cdr value-cons) new-bit))))
  new-value)

;;; `Part-has-feature-p' returns a non-NIL value if the part description, passed
;;; as its first argument, has the part-feature named by its second argument.
;;; It returns that value, if non-NIL, otherwise it returns T.

(defun part-has-feature-p (part-description part-feature)
  (loop for (actual-part-feature feature-value)
            on (rest part-description)
            by #'cddr
        do
    (when (eq part-feature
              actual-part-feature)
      (return (or feature-value t)))))


;;; `map-over-part-description' is used rarely.  It applies its first argument,
;;; a function of one argument, to each part description in the part description
;;; given in its second argument.  They are visited in bottom up order.  The
;;; part description passed is also mapped over.  This will visit the
;;; subparts, subpart-defaults, and subpart-exceptions.  Any other embedded
;;; part descriptions must be managed by the caller.

(defun map-over-part-description (function part-description)
  (loop for (feature-name feature-value) on (rest part-description) by #'cddr
        do
    (when (memq feature-name '(subparts subpart-defaults subpart-exceptions))
      (map-over-subpart-collection function feature-value))
        finally
          (funcall function part-description)))

(defun map-over-subpart-collection (function subpart-collection)
  (loop for (nil instances) on subpart-collection by #'cddr
        do
    (loop for part-description in instances
          do
      (map-over-part-description function part-description))))



;;; `Remove-simple-part-feature' will remove a given part-feature from
;;; a part-description, if present, and reclaim its storage.  This is
;;; the internal implementation of setting a part feature to "default."

(defun remove-simple-part-feature (part-description part-feature)
  (assert-that-within-named-dynamic-extent 'working-on-annotated-frame)
  (loop with part-type = (first part-description)
        for p on part-description by #'cddr
        as (nil cantidate-feature old-value) = p
        when (eq cantidate-feature part-feature)
          do
            (let ((bit-to-reclaim (cdr p)))
              ;; Call the reclaimer, note some reclaimers presume
              ;; it is in the parent data structure.
              (reclaim-part-feature part-type part-feature old-value)
              ;; Slice it out of the list
              (setf (cdr p) (cdddr p))
              (setf (cddr bit-to-reclaim) nil)
              (reclaim-slot-value-list bit-to-reclaim)))
  nil)

(defun remove-simple-part-feature-without-reclaiming (part-description part-feature)
  (assert-that-within-named-dynamic-extent 'working-on-annotated-frame)
  (loop for p on part-description by #'cddr
        as (nil cantidate-feature nil) = p
        when (eq cantidate-feature part-feature)
          do
            (let ((bit-to-reclaim (cdr p)))
              (setf (cdr p) (cdddr p))
              (setf (cddr bit-to-reclaim) nil)
              (reclaim-slot-value-list bit-to-reclaim)))
  nil)

(defun lookup-subpart-of-collection (part-description part-feature part-type part-index)
  (let* (;; Get subpart-collection, creating it if necessary.
         (subpart-collection
           (let ((subpart-collection? (get-simple-part-feature part-description part-feature)))
             (if subpart-collection?
                 subpart-collection?
                 (set-simple-part-feature part-description part-feature
                                          (slot-value-list part-type ())))))

         ;; Sweep over the subpart collection, looking for the entry for this
         ;; part-type, creating it if necessary.  Bind the cons cell that
         ;; contains the list of part-descriptions in its car, so we can
         ;; insert into that list in a moment if necessary.
         (cons-of-subparts-for-this-type
           (loop with found-it-flag = nil
                 for (part-type-for-these . cantidate-cons) on subpart-collection by #'cddr
                 as last-cons = cantidate-cons
                 do (when (eq part-type part-type-for-these)
                      (setf found-it-flag t)
                      (return cantidate-cons))
                 finally
                   (unless found-it-flag
                     (return
                       (cdr (setf (cdr last-cons) (slot-value-list part-type ())))))))

         (subparts-for-this-type? (car cons-of-subparts-for-this-type)))

    ;; Dispatch on the part-feature, to determine the fine details of
    ;; how we should look (and create as necessary the part-description.
    (case part-feature
      (subparts
       (let ((result (nth part-index subparts-for-this-type?)))
         (unless result (error "Can not create new parts instances on the fly.")) ;;;
         result))
      (subpart-defaults
       (cond
         (subparts-for-this-type?
          (first subparts-for-this-type?))
         (T
          (let ((new-bit (slot-value-list   ; i.e. `((,part-type))
                           (slot-value-list part-type))))
            (setf
              (car cons-of-subparts-for-this-type)
              new-bit)
            (car new-bit)))))
      (subpart-exceptions
       (cond
         (subparts-for-this-type?
            (loop with found-it-flag = nil
                  for last-cons = nil then exceptional-part-template-cons
                  as exceptional-part-template-cons on subparts-for-this-type?
                  as cantidate-result = (car exceptional-part-template-cons)
                  as exceptional-part-index =
                     (get-simple-part-feature cantidate-result 'part-index)
                  do
              (cond
                ((= exceptional-part-index part-index)
                 (setf found-it-flag t)
                 (return cantidate-result))
                ((> exceptional-part-index part-index)
                 ;; Splice in a new bit of list before this latter exception.
                 (setf found-it-flag t)
                 (let ((new-bit                        ; i.e. `((,part-type part-index ,part-index))
                         (slot-value-list
                           (slot-value-list part-type 'part-index part-index))))
                   (cond
                     (last-cons
                      (shiftf (cdr new-bit) (cdr last-cons) new-bit))
                     (T
                      (shiftf (cdr new-bit) (car cons-of-subparts-for-this-type) new-bit)))
                   (return (car new-bit)))))
                  finally
                    (unless found-it-flag
                      (let ((new-bit ; i.e. `((,part-type part-index ,part-index))
                              (slot-value-list
                                (slot-value-list part-type 'part-index part-index))))
                        (setf (cdr last-cons) new-bit)
                        (return (car new-bit))))))
         (T
          (let ((new-bit (slot-value-list (slot-value-list part-type 'part-index part-index))))
            (setf (car cons-of-subparts-for-this-type) new-bit)
            (car new-bit))))))))


;;; `get-simple-part-feature-as-float' ...

(defmacro get-simple-part-feature-as-float (part feature)
  `(slot-value-number-value-as-float
     (get-simple-part-feature ,part ,feature)))


;;; `set-simple-part-features' ...

(defmacro set-simple-part-features (part &rest features-values)
  (let ((part-var '#:part))
    `(let ((,part-var ,part))
       ,@(loop for (feature value) on features-values by #'cddr
               collect `(set-simple-part-feature ,part-var ,feature ,value)))))


;#+development
;(defen test-part-accessors-and-setters ()
;  (block nil
;    (prog1
;      T
;      (let ((test-case (slot-value-list 'chart))
;            (test-step 0))
;        (flet ((check-1 (form expected-value-form form-result expected-value)
;                        (declare (ignore expected-value-form))
;                        (incf test-step)
;                        (unless (equal form-result expected-value)
;                          (format
;                            t
;                            "~(~%test-part-accessors-failed, step ~D: ~% doing: ~S~%result: ~S~%post: ~S~)"
;                            test-step
;                            form
;                            form-result
;                            test-case)
;                          (return nil))))
;          (macrolet ((check (form expected-value)
;                            `(check-1 ',form ',expected-value ,form ,expected-value)))
;            ;; Test simple features
;            (check (get-simple-part-feature test-case 'chart-title) nil)
;            (check (set-simple-part-feature test-case 'chart-title "Hi There") "Hi There")

;            ;; Test subparts feature
;            (set-simple-part-feature test-case 'subparts (copy-tree-using-slot-value-conses
;                                                           '(axis ((axis axis-maximum 10 axis-minimum 0)))))
;            (check (get-simple-part-feature test-case 'subparts)
;                   '(axis ((axis axis-maximum 10 axis-minimum 0))))
;            (check
;              (get-subpart-of-collection test-case 'subparts 'axis 0)
;              '(axis axis-maximum 10.0 axis-minimum 0.0))

;            ;; Test subpart-defaults feature
;            (check     ; shouldn't be one yet.
;              (get-subpart-of-collection test-case 'subpart-defaults 'axis nil)
;              nil)
;            (check     ; insert an empty one.
;              (lookup-subpart-of-collection test-case 'subpart-defaults 'axis nil)
;              '(axis))
;            (check     ; see if it's there.
;              (get-subpart-of-collection test-case 'subpart-defaults 'axis nil)
;              '(axis))
;            (check     ; see if lookup gets it too.
;              (lookup-subpart-of-collection test-case 'subpart-defaults 'axis nil)
;              '(axis))

;            ;; Test subpart-exceptions feature
;            (check  ; Shouldn't be one now.
;              (get-subpart-of-collection test-case 'subpart-exceptions 'data-series 5)
;              nil)
;            ;; Insert a first one.
;            (check  ; Insert one upon lookup.
;              (lookup-subpart-of-collection test-case 'subpart-exceptions 'data-series 5)
;              '(data-series part-index 5))
;            (check  ; See if get sees it.
;              (get-subpart-of-collection test-case 'subpart-exceptions 'data-series 5)
;              '(data-series part-index 5))
;            (check  ; See if vanilla lookup sees it.
;              (lookup-subpart-of-collection test-case 'subpart-exceptions 'data-series 5)
;              '(data-series part-index 5))

;            ;; Insert on after all the ones we have.
;            (check  ; See if get sees it.
;              (get-subpart-of-collection test-case 'subpart-exceptions 'data-series 7)
;              nil)
;            (check  ; Insert one upon lookup.
;              (lookup-subpart-of-collection test-case 'subpart-exceptions 'data-series 7)
;              '(data-series part-index 7))
;            (check  ; See if get sees it.
;              (get-subpart-of-collection test-case 'subpart-exceptions 'data-series 7)
;              '(data-series part-index 7))
;            (check  ; See if vanilla lookup sees it.
;              (lookup-subpart-of-collection test-case 'subpart-exceptions 'data-series 7)
;              '(data-series part-index 7))

;            ;; Insert one before all the ones we have
;            (check  ; See if get sees it.
;              (get-subpart-of-collection test-case 'subpart-exceptions 'data-series 1)
;              nil)
;            (check  ; Insert one upon lookup.
;              (lookup-subpart-of-collection test-case 'subpart-exceptions 'data-series 1)
;              '(data-series part-index 1))
;            (check  ; See if get sees it.
;              (get-subpart-of-collection test-case 'subpart-exceptions 'data-series 1)
;              '(data-series part-index 1))
;            (check  ; See if vanilla lookup sees it.
;              (lookup-subpart-of-collection test-case 'subpart-exceptions 'data-series 1)
;              '(data-series part-index 1))


;            (print test-case)

;            ))))))







;;;; Editing Part Descriptions Or Features Of Part Descriptions




;;; The editor likes to work on slots of frames.  Since we store information in
;;; part descriptions, and in the subexpressions of part descriptions.  We need
;;; to build some glue to get between these two.  This is done by creating a
;;; temporary frame (aka a annotation-editing-info) and placing a pointer to the
;;; substructure we want to edit in a slot of this frame.  The editor is then
;;; invoked on this frame and slot.  Different slots are available for different
;;; types of subexpressions.

;;; This mechanism has the usual problems with microtasking the user interface.
;;; We pick up control again, after the editor is done, in the editor return
;;; function.  The annotation-editing-info frame is used to hold  everything
;;; the continuation needs to store the value back into the original annotation
;;; and trigger the resulting display updates.  As usual frame serial numbers
;;; are used to clean up if the frame that actually contains the annotation is
;;; deleted.

;;; The function `start-edit-of-annotation-subexpression' is used to launch the
;;; editor.  This routine will edit either a single feature of a
;;; part-description, or an entire part description.

;;; The editor is given a copy to work on, so that when the editor calls the
;;; slot value compiler and slot putter it will be working on data private to
;;; the temporary frame.  This assures that the original value is available when
;;; the finish routine is erasing from the screen and (de)installing names.

;;; The start routine takes an part-description to edit.  A part-feature name
;;; provided to names what part should edit. T is used to indicate the entire
;;; part-description should be edited.  Finally a grammar type is passed.

;;; The function finish-edit-of-annotation-of-subexpression is called by the
;;; editor when the edit finishs.  It erases the block containing the
;;; annotation, change the value, and finally redraw the block.

;;; The consistency analysis of blocks with parts is done in a somewhat
;;; unusual way.  Recall that this analysis is: asserted when the frame
;;; is initialized, retracted when by the block's cleanup method when
;;; deleted, and retracted otherwise only within short windows around
;;; those transactions that change the set of names used by the frame.
;;; Most frames open these temporary windows only in the slot putter of
;;; the slots in frame that contain names.

;;; For blocks with embedded parts the consistency analysis windows are
;;; opened more often, e.g. on any transaction implemented via this
;;; editor harness.

;;; All use of names (with an temporary (sic) exception for charts) by
;;; blocks with subparts are owned by the cell array of that block.
;;; When we compile a new cell array entry the set of names changes.
;;; So a window in the consistency analysis is opened by all slot value
;;; compilers that register new entries in the cell array.  Entries in
;;; the cell array are owned by part descriptions, correct denotation
;;; of these entries is based on the denotation of this owner.  Entries
;;; are not stored back into the part description until the finish
;;; routine comits the edit.  To generate accurate denotates we must
;;; open a window around that commit, if any table is showing for the
;;; cell.

;;; The temporary frame has one slot for each such grammar type.  That slot
;;; and grammar type then guide which writer, compiler, and slot putter
;;; are utilized by the editor.

;;; These grammar types are currently supported.

;;;    cell-format  -- That subset of information stored in a cell's part
;;;                    description is public to the user.
;;;    expression-cell-index-and-computation-style

;;; A feature of that is edited as an expression-in-cell will be installed in
;;; the cell-array of the owning frame by the slot value compiler.  This may
;;; give rise to frame notes, and log book messages.

;;; A part description that is edited as a cell-format is merged with
;;; the original cell description so that the non-public components are
;;; left unchanged.

(def-class (annotation-editing-info block)
  ;; Information needed by the continuation
  (frame-being-edited nil                        vector-slot system)
  (frame-serial-number-of-frame-being-edited nil vector-slot system)
  (annotation-containing-feature nil             vector-slot system)
  (feature-of-annotation-being-edited nil        vector-slot system)
  (type-of-feature-being-edited nil              vector-slot system)

  ;; Slots for the editor to work on.
  (editable-slot-for-cell-expression-and-text
    nil                                          vector-slot system
    (type cell-expression-parse))

  (reference-to-data-in-frame-containing-annotation
    t     vector-slot system
    (type cell-format))
  )


;; Notice that editable-slot-for-cell-expression-and-text is not type text,
;; the slot-value compiler.

;; Since the editor needs a frame serial number, this can not be
;; a dependent-frame.


(def-slot-value-reclaimer frame-being-edited (frame)
  (declare (ignore frame))
  ;; This by its superior and should not be reclaimed.
  )

(def-slot-value-reclaimer annotation-containing-feature (annotation)
  (declare (ignore annotation))
  ;; This is owned by the frame being edited and should not be reclaimed.
  )

(def-slot-value-reclaimer editable-slot-for-cell-expression-and-text (cell-expression-and-text)
  (declare (ignore cell-expression-and-text))
  ;; This is owned by the frame being edited and should not be reclaimed.
  )

(def-slot-value-reclaimer reference-to-data-in-frame-containing-annotation (data-we-ignore)
  (declare (ignore data-we-ignore))
  ;; This is owned by the frame being edited and should not be reclaimed.
  )

(def-slot-value-reclaimer frame-serial-number-of-frame-being-edited (serial-number annotation-editing-info)
  (reclaim-frame-serial-number serial-number)
  (setf (frame-serial-number-of-frame-being-edited annotation-editing-info) nil))

;;; `Start-edit-of-annotation-subexpression' launches the editor on the value we
;;; want it to edit.  As explained above the user's control stream will
;;; then pop out again latter in the slot putter defined for the slot
;;; we actually selected to work on.

;;; Annotation-containing-feature is the innermost annotation
;;; that contains the feature that we want edited.

(defun start-edit-of-annotation-subexpression (frame-containing-annotation
                                                annotation-containing-feature
                                                feature-to-edit
                                                type-of-feature-being-edited
                                                &optional
                                                (hide-workspace-p nil))
  (highlight-part-of-frame
    frame-containing-annotation
    annotation-containing-feature)
  (let ((temporary-frame-for-editor (make-frame 'annotation-editing-info))
        slot-to-edit)
    (setf (frame-being-edited temporary-frame-for-editor)
          frame-containing-annotation)
    (frame-serial-number-setf (frame-serial-number-of-frame-being-edited temporary-frame-for-editor)
                              (frame-serial-number frame-containing-annotation))
    (setf (annotation-containing-feature temporary-frame-for-editor)
          annotation-containing-feature)
    (setf (feature-of-annotation-being-edited temporary-frame-for-editor)
          feature-to-edit)
    (setf (type-of-feature-being-edited temporary-frame-for-editor)
          type-of-feature-being-edited)
    (setf slot-to-edit
          (getf
            '(cell-format
              reference-to-data-in-frame-containing-annotation

              cell-expression-and-text
              editable-slot-for-cell-expression-and-text

              )
            type-of-feature-being-edited))
    (let ((value-for-editor-to-work-on
            (let ((original-value
                    (if (eq T feature-to-edit)
                        annotation-containing-feature
                        (get-simple-part-feature annotation-containing-feature feature-to-edit))))
              (if (eql type-of-feature-being-edited 'cell-format)
                  original-value
                  (copy-for-slot-value ;; Note A.
                    original-value)))))
      (case type-of-feature-being-edited
        (cell-format
         (setf (reference-to-data-in-frame-containing-annotation temporary-frame-for-editor)
               value-for-editor-to-work-on)
         )
        (cell-expression-and-text  ;; Note B.
         (when (and value-for-editor-to-work-on
                    (compiled-cell-expression-p
                      (car
                        value-for-editor-to-work-on)))
           (remove-simple-part-feature-without-reclaiming
             (car value-for-editor-to-work-on)
             'expression-cell-index))
         (setf (editable-slot-for-cell-expression-and-text
                 temporary-frame-for-editor)
               value-for-editor-to-work-on))))
    (with-old-style-workstation-return-function
        ( 'finish-edit-of-annotation-subexpression
           temporary-frame-for-editor
           'cleanup-edit-of-annotation-subexpression)
      (enter-editing-context
        temporary-frame-for-editor
        slot-to-edit
        nil
        hide-workspace-p
        nil
        nil
        nil
        nil
        nil
        nil
        nil
        nil
        nil
        nil
        (case type-of-feature-being-edited
          (cell-expression-and-text '(type cell-expression-parse)) ;; Bogus rewrite
          (cell-format '(type cell-format))
          (otherwise
           (error
             "start-edit-of-annotation-subexpression unknown type-of-feature-being-edited: ~S." type-of-feature-being-edited)))
        ))))


;; Note A: We work on a copy, the original is replaced by
;; finish-edit-of-annotation-subexpression.

;; Note B: The expression-cell-index is, effectively, a pointer to the
;; cell.  If we don't remove it from the copy we will have two pointers;
;; from the copy and the original.  That will could cause double
;; reclaimation.


(defun delete-all-editors-of-cell (part-description)
  (let* ((aei-list
           (loop for annotation-editing-info being each class-instance of 'annotation-editing-info
                 when (eq (annotation-containing-feature annotation-editing-info) part-description)
                   collect annotation-editing-info using gensym-cons))
         (frame-list
           (loop for workstation in workstations-in-service
                 nconc (loop for context in (workstation-context-stack workstation)
                             when (and (eq (type-of-workstation-context context) 'editing)
                                       (memq (workstation-context-return-information context) aei-list))
                               collect (edit-workspace
                                         (specific-structure-for-workstation-context context))
                                 using gensym-cons))))
    (loop for annotation-editing-info in aei-list
          do (setf (annotation-containing-feature annotation-editing-info) nil))
    (loop for frame in frame-list
          do (delete-frame frame))
    (reclaim-gensym-list aei-list)
    (reclaim-gensym-list frame-list)))




;;; `Update-part-dependencies' should be defined for blocks that contain part
;;; descriptions.  It is used to allow the block an oportunity to recompute
;;; information that is derived from the data being changed (for example to
;;; reformat.).  It is called by change-annotation...

(def-generic-method update-part-dependencies (block kind-of-change what-changed)
  )



;;; When editing a cell-format we write only those part features that contribute to
;;; formatting, any other part features are left unchanged.  We do this, first, by having the
;;; slot value writer show only the formatting features; and second by having the slot
;;; putter merge the result of the user's editing back into the original.

;; The following defparameter was moved here to resolve a forward reference
;; within this file.  -jra 10/10/91

(defparameter cell-format-part-features
              '(background-color
                 width
                 height
                 border-color
                 text-alignment
                 text-color
                 text-size))




;;; The slot putter for `Reference-to-data-in-frame-containing-annotation' removes the old
;;; data and stores the new data in the frame referenced.  It brackets this will these
;;; dynamic extents:
;;;  - without consistency analysis
;;;  - the affected part of the block is erased.
;;;  - working on annotated-frame is established.
;;;  - binding for current-block-of-dependent-frame

;;; All data is deleted prior to installing new data.  The approprate reclaimer is called
;;; on the deleted data.

;;; When the entire annotation is being editted only those slots declared for the given
;;; type are revised.

(def-slot-putter reference-to-data-in-frame-containing-annotation (annotation-editing-info new-compiled-data)
  (let* ((original-slot-value
           (reference-to-data-in-frame-containing-annotation annotation-editing-info))
         (frame-being-edited
           (frame-being-edited annotation-editing-info))
         (annotation-containing-feature
           (annotation-containing-feature annotation-editing-info))
         (feature-of-annotation-being-edited
           (feature-of-annotation-being-edited annotation-editing-info))
         (current-block-of-dependent-frame
           frame-being-edited)
         (needs-update-p nil))
    (without-consistency-analysis (frame-being-edited)
      (with-named-dynamic-extent working-on-annotated-frame
                                 ((current-annotated-frame frame-being-edited)
                                  ;; current-computation-style is not bound in this situation.
                                  )
        (erase-part-of-block frame-being-edited annotation-containing-feature)
        (cond
          ((eql t feature-of-annotation-being-edited)
           ;; Merge new features with the current value,
           ;; but first remove any old features the new value should override,
           ;; and before we do that deactivate any embedded computations.
           (loop with original-slot-value
                   = (reference-to-data-in-frame-containing-annotation annotation-editing-info)
                 initially ;; Remove any old features.
                   (loop with features-this-overrides
                           = (case (type-of-feature-being-edited annotation-editing-info)
                               (cell-format cell-format-part-features)
                               #+development
                               (t  (error "Unsupported type-of-feature-being-edited.")))
                         initially
                           (when (memq 'background-color features-this-overrides) ;; See Note A
                             (let ((possibly-embedded-computation
                                     (get-simple-part-feature original-slot-value 'background-color)))
                               (when (compiled-cell-expression-p possibly-embedded-computation)
                                 (deactivate-cell-of-g2-cell-array
                                   (cell-array current-block-of-dependent-frame)
                                   (get-simple-part-feature
                                     possibly-embedded-computation
                                     'expression-cell-index)))))
                         for part-feature in features-this-overrides
                         do
                     (remove-simple-part-feature original-slot-value part-feature))
                 for (feature-key feature-value)
                     on (cdr new-compiled-data) by #'cddr
                 do
             (set-simple-part-feature
               original-slot-value
               feature-key
               (copy-for-slot-value feature-value))

             ;; If changing this slot requires that we need to reformat-text, hence update the frame,
             ;; then make a note of this. todo: This memq should be abstracted into an appropriate arity predicate

             (when (memq feature-key '(text-size text-alignment))
               (setq needs-update-p t))

             (when (compiled-cell-expression-p feature-value)
               (let ((g2-cell-array (cell-array current-block-of-dependent-frame))
                     (index (get-simple-part-feature feature-value 'expression-cell-index)))
                 (register-expression-cell-during-slot-putter g2-cell-array index nil)))
                 finally
                   (reclaim-slot-value-list new-compiled-data)))
          (t
           #+development
           (error "Reference-to-data-in-frame-containing-annotation doesn't work yet on single features.")))

        ;; This ensures, e.g. that a cell in a freeform-table is updated (which does a reformat-text)
        ;; if the text-size or text-alignment have just been changed.
        (when g2-has-v5-mode-windows-p
          (frame-class-case frame-being-edited
            (freeform-table
              (send-ws-representations-item-virtual-attribute-change
                frame-being-edited (virtual-attribute 'table-cells) nil))))
        (when needs-update-p
          (let ((projection-focus-method 'annotation)
                (projection-focus-annotation annotation-containing-feature))
            (funcall-method-if-any 'update-part-dependencies frame-being-edited 'annotation annotation-containing-feature)))
        (redraw-part-of-block annotation-containing-feature)))
    (values original-slot-value t)))

;; Note A: This is currently the only computed formating attribute, but this should be computed
;; in a more abstract way.



;;; `Finish-edit-of-annotation-subexpression' commits the edit into the original frame.
;;; Doing this requires first erasing the block, as it was rendered prior to the change,
;;; after that it commits the change, and redraws the frame.  If the feature being
;;; changed is an expression-cell it also retracts and reasserts any name registrations.

(defun finish-edit-of-annotation-subexpression (edit-workstation-context)
  (let* ((temporary-frame-for-editor
           (workstation-context-return-information edit-workstation-context))
         (frame-containing-annotation
           (frame-being-edited temporary-frame-for-editor))
         (supress-reclaiming-old-value-flag
           nil)
         (current-block-of-dependent-frame frame-containing-annotation)
         (annotation-containing-feature
           (annotation-containing-feature temporary-frame-for-editor))
         (simple-type-of-feature
           (type-of-feature-being-edited temporary-frame-for-editor)))
    (when (frame-serial-number-equal (frame-serial-number-of-frame-being-edited temporary-frame-for-editor)
                                     (frame-serial-number frame-containing-annotation))
      (erase-part-of-block frame-containing-annotation annotation-containing-feature)
      (unless (eq 'cell-format simple-type-of-feature)
        (let* ((slot-that-was-edited
                 (getf
                   '(
                     cell-expression-and-text
                     editable-slot-for-cell-expression-and-text)
                   simple-type-of-feature)))
          (when (eq simple-type-of-feature 'cell-format)
            (setf supress-reclaiming-old-value-flag t))
          (change-annotation
            frame-containing-annotation
            annotation-containing-feature
            (feature-of-annotation-being-edited temporary-frame-for-editor)
            simple-type-of-feature
            supress-reclaiming-old-value-flag
            (get-slot-value
              temporary-frame-for-editor
              slot-that-was-edited))))
      (unhighlight-part-of-frame
        frame-containing-annotation
        annotation-containing-feature)
      (redraw-part-of-block annotation-containing-feature)))
  (exit-current-workstation-context-in-return-function 'editing))


;;; `Cleanup-edit-of-annotation-subexpression' reclaims the temporary frame
;;; and removes the highlight.  It is the unwind protect's clean up clause
;;; of the editor context.

(defun cleanup-edit-of-annotation-subexpression (temporary-frame-for-editor)
  (let* ((frame-containing-annotation
           (frame-being-edited temporary-frame-for-editor))
         (current-block-of-dependent-frame frame-containing-annotation)
         (annotation-containing-feature
           (annotation-containing-feature temporary-frame-for-editor)))
    (when (frame-has-not-been-reprocessed-p
            frame-containing-annotation
            (frame-serial-number-of-frame-being-edited
              temporary-frame-for-editor))
      (unhighlight-part-of-frame
        frame-containing-annotation
        annotation-containing-feature)))
  (delete-frame temporary-frame-for-editor))



(defun recompile-component-of-part-description (part-description part-feature type-of-feature)
  (let ((currently-supressing-part-highlighting t))
    (start-edit-of-annotation-subexpression
      *current-computation-frame*
      part-description
      part-feature
      type-of-feature
      t)
    (let ((editing-context current-workstation-context))
      (finish-parsing-insofar-as-possible)
      (when (and keep-edit-workspace-hidden-no-matter-what?
                 (eq current-workstation-context editing-context))
        (return-from-current-workstation-context 'editing)))))


;;; `Change-annotation' is to part description what change-slot-value is
;;; to frames.  It erases from the screen all representations of the
;;; frame, changes the annotation, and then restores them to the screen.

;;; The arguments are:
;;;    frame-containing-annotation   -- a frame
;;;    annotation                    -- a part description
;;;    part-feature-or-T             -- a part-feature or T
;;;    simple-type-of-feature        -- a simple type, or T
;;;    supress-reclaiming-old-value-flag  -- boolean
;;;    new-value                     -- an instance of that simple type,
;;;                                  -- or a list of part features.

;;; If part-feature is T then all the part features of the frame are
;;; replaced by the new part features

;;; The update-subparts-effected-by-this-annoation method of the
;;; containing frame is does the erase and redraw.

;; This routine is under review and is being replaced the mechinisms
;; around reference-to-data-in-frame-containing-annotation.

(defun change-annotation (frame-containing-annotation
                          annotation
                          part-feature-or-T
                          simple-type-of-feature

                          supress-reclaiming-old-value-flag
                          new-value)
  (without-consistency-analysis (frame-containing-annotation)
    (with-named-dynamic-extent working-on-annotated-frame
                               ((current-annotated-frame frame-containing-annotation)
                                ;; current-computation-style is not bound in this situation.
                                )
      (erase-part-of-block frame-containing-annotation annotation)
      ;; Store the new value
      (cond
        ;; Replace entire annotation?
        ((eq T part-feature-or-T)
         (let ((old-part-features
                 (shiftf (cdr annotation)
                         (cdr new-value)
                         nil)))
           (unless supress-reclaiming-old-value-flag
             (reclaim-part-features
               (car annotation)
               old-part-features))
           (reclaim-slot-value-cons new-value)))
        ;; Is this a situation where we should remove the
        ;; feature, rather than set it?
        ((and (eq 'cell-contents part-feature-or-T)
              (null (car new-value)))
         (remove-simple-part-feature annotation part-feature-or-T)
         (reclaim-part-feature (part-description-type annotation)
                               part-feature-or-t
                               new-value))
        ;; Otherwise replace this feature of this annotation.
        (t
         #+development
         (assert (not supress-reclaiming-old-value-flag))
         (set-simple-part-feature
           annotation
           part-feature-or-T
           new-value)))

      (let ((projection-focus-method 'annotation)
            (projection-focus-annotation annotation))
        (funcall-method 'update-part-dependencies current-annotated-frame 'annotation annotation))

      (redraw-part-of-block annotation)
      (when g2-has-v5-mode-windows-p
        (frame-class-case frame-containing-annotation
          (freeform-table
            (send-ws-representations-item-virtual-attribute-change
              frame-containing-annotation (virtual-attribute 'table-cells) nil))))

      ;; Do any side effects of the store that
      ;; are approprate after the redraw.
      (case simple-type-of-feature
        (cell-expression-and-text
         (when (compiled-cell-expression-p (car new-value))
           (register-expression-cell-during-slot-putter
             (cell-array frame-containing-annotation)
             (get-simple-part-feature (car new-value) 'expression-cell-index)
             nil)))
        (cell-expression
         (when (compiled-cell-expression-p new-value)
           (register-expression-cell-during-slot-putter
             (cell-array frame-containing-annotation)
             (get-simple-part-feature new-value 'expression-cell-index)
             nil)))))))


;; Note A: This should call a new entry point analagous to
;; reclaim-part-description. ??








;;;; Computation Style Descriptions


;;; Computation style descriptions are the part descriptions which are
;;; associated with some computation.  They record how this computation's style
;;; varies from the default style of its parent context.  When the computation
;;; is registered with the inference engine the full set of computation style
;;; settings is provided to the inference engine in the kb specific variable
;;; current-computation-style.  In support of maintaining the
;;; current-computation-style, the features of a
;;; computation-style-description are scanned to maintain slots of that
;;; structure.

;;; First we need some routines to support scanning these kinds of part
;;; descriptions.

;;; The part features that control tracing and breakpoints are handled by
;;; masking their value into the approprate slot in the bit fields that
;;; make up the current-computation-style's slot
;;; computation-style-tracing-and-breakpoints.

(defun-simple enter-tracing-or-breakpoints-setting (new-value shift)
  (let ((original-computation-style-tracing-and-breakpoints
          (computation-style-tracing-and-breakpoints
            current-computation-style)))
    (part-stack-push
      original-computation-style-tracing-and-breakpoints
      part-feature-recall-stack)
    (setf
      (computation-style-tracing-and-breakpoints
        current-computation-style)
      (logior
        (logandc2 ; clear bits.
          (or original-computation-style-tracing-and-breakpoints
              completely-unspecified-debugging-code)
          (ash message-field-mask shift))
        (ash new-value shift))))
  nil)

(defun-simple exit-tracing-or-breakpoints-setting ()
  (setf
    (computation-style-tracing-and-breakpoints
      current-computation-style)
    (part-stack-pop part-feature-recall-stack))
  nil)

(defun-simple enter-warning-level (warning-level)
  (enter-tracing-or-breakpoints-setting warning-level warning-shift)
  nil)

(defun-simple enter-tracing-level (tracing-level)
  (enter-tracing-or-breakpoints-setting tracing-level tracing-shift)
  nil)

(defun-simple enter-break-level (break-level)
  (enter-tracing-or-breakpoints-setting break-level breakpoint-shift)
  nil)


;;; Now the actual part features.

(def-part-type computation-style-description
  (user-spelling evaluation-attributes))

(def-part-feature (computation-style-description priority)
  (type priority-level)
  (means-of-scanning
    class-slot current-computation-style computation-style-priority)
  user-visible)

(def-part-feature (computation-style-description scan-interval)
  (type simple-interval)
  (means-of-scanning
    class-slot current-computation-style computation-style-scan-interval)
  user-visible)

(def-part-feature (computation-style-description initial-scan-wait-interval)
  (type simple-interval)
  (means-of-scanning
    class-slot current-computation-style computation-style-initial-scan-wait-interval)
  user-visible)

(def-part-feature (computation-style-description value-domain)
  (type value-domain-kind)
  (means-of-scanning
    class-slot current-computation-style computation-style-value-domain)
  user-visible)

(def-part-feature (computation-style-description update-only-when-shown)
  (type boolean)
  (means-of-scanning
    class-slot current-computation-style computation-style-update-only-when-shown)
  user-visible)

(def-part-feature (computation-style-description trace-message-level-for-computation-style)
  (type trace-level)
  (user-spelling trace-message-level)
  (means-of-scanning call-handlers #'enter-tracing-level #'exit-tracing-or-breakpoints-setting)
  user-visible)

(def-part-feature (computation-style-description warning-message-level-for-computation-style)
  (type warning-level)
  (user-spelling warning-message-level)
  (means-of-scanning call-handlers #'enter-warning-level #'exit-tracing-or-breakpoints-setting)
  user-visible)

(def-part-feature (computation-style-description break-message-level-for-computation-style)
  (type break-level)
  (user-spelling break-message-level)
  (means-of-scanning call-handlers #'enter-break-level #'exit-tracing-or-breakpoints-setting)
  user-visible)

(def-part-feature (computation-style-description may-request-event-updates)
  (type boolean)
  (means-of-scanning
    class-slot current-computation-style computation-style-may-request-event-updates)
  user-visible)

(def-part-feature (computation-style-description may-request-data-seeking)
  (type boolean)
  (means-of-scanning
    class-slot current-computation-style computation-style-may-request-data-seeking)
  user-visible)

(def-part-feature (computation-style-description time-out-when-requesting-data-seeking)
  (type simple-interval)
  (means-of-scanning
    class-slot current-computation-style computation-style-time-out-when-requesting-data-seeking)
  user-visible)

(def-part-feature (computation-style-description may-provide-data-on-request)
  (type boolean)
  (means-of-scanning
    class-slot current-computation-style computation-style-may-provide-data-on-request)
  user-visible)

(def-part-feature (computation-style-description may-provide-event-updates)
  (type boolean)
  (means-of-scanning
    class-slot current-computation-style computation-style-may-provide-event-updates)
  user-visible)

(def-part-feature (computation-style-description update-after-edits)
  (type boolean)
  (means-of-scanning
    class-slot current-computation-style computation-style-may-provide-event-updates)
  (user-visible nil))

(def-part-feature (computation-style-description network-access-attempt)
  (type network-access-kind)
  (means-of-scanning
    class-slot current-computation-style computation-style-network-access-attempt)
  (user-visible nil))









;;; The user specifies the style of a computation in the manner this example
;;; suggests: "foo+bar; evaluate it every 3 seconds"  The `evaluate it' statement
;;; is appended on the end of the expression.  There are three flavors
;;; of evaluate it forms; a short form used for common things, like the
;;; scan interval, a long form which allows all the obscure details to
;;; be specified, and a form used only when the user wants to
;;; give no settings.  These are some examples:

;;;    evaluate it every 3 seconds
;;;    evaluate it at priority 4 every 3 seconds
;;;    evaluate it using default settings
;;;    evaluate it with these settings: scan-interval = 3, priority = 4, tracing-message-level = 2

(add-grammar-rules '((boolean 'true)
                     (boolean 'false)))

(add-grammar-rules
  '((computation-style ('evaluated common-computation-phrases)
                       2)
    (computation-style ('evaluated complete-computation-phrase)
                       2)

    (common-computation-phrases common-computation-phrases-tail)
    (common-computation-phrases-tail common-computation-phrase
                                   (progn 1))
    (common-computation-phrases-tail
      (common-computation-phrase common-computation-phrases-tail)
      (progn 1 2)
      simplify-associative-operation)


    (common-computation-phrase ('at 'priority integer)
                               (current-part-description priority 3) reduce-annotation)
    (common-computation-phrase ('every quantity-interval)
      (current-part-description scan-interval 2) reduce-common-computation-phrase-scan-interval)

    (complete-computation-phrase ('with 'these 'settings '\: computation-setting-list) 5)

    (computation-setting-list computation-setting-list-tail)
    (computation-setting-list-tail computation-setting
                                   (progn 1))
    (computation-setting-list-tail
      (computation-setting '\; computation-setting-list-tail)
      (progn 1 3)
      simplify-associative-operation)


    (computation-setting ('priority '= number)
                         (current-part-description priority 3) reduce-annotation)

    (computation-setting ('scan-interval '= number)
                         (current-part-description scan-interval 3) reduce-annotation)
    (computation-setting ('initial-scan-wait-interval '= number)
                         (current-part-description initial-scan-wait-interval 3) reduce-annotation)

    (computation-setting ('value-domain 'is 'inference-engine)
                         (current-part-description value-domain 3) reduce-annotation)
    (computation-setting ('value-domain 'is 'g2-simulator)
                         (current-part-description value-domain 3) reduce-annotation)

    (computation-setting ('update-only-when-shown 'is boolean)
                         (current-part-description update-only-when-shown 3) reduce-annotation)

    (computation-setting ('trace-message-level '= number)
                         (current-part-description trace-message-level 3) reduce-annotation)
    (computation-setting ('warning-message-level '= number)
                         (current-part-description warning-message-level 3) reduce-annotation)
    (computation-setting ('break-message-level '= number)
                         (current-part-description break-message-level 3) reduce-annotation)

    (computation-setting ('time-out-when-requesting-data-seeking '= number)
                         (current-part-description time-out-when-requesting-data-seeking 3) reduce-annotation)
    (computation-setting ('may-request-event-updates 'is boolean)
                         (current-part-description may-request-event-updates 3) reduce-annotation)
    (computation-setting ('may-request-data-seeking 'is boolean)
                         (current-part-description may-request-data-seeking 3) reduce-annotation)
    (computation-setting ('may-provide-data-on-request 'is boolean)
                         (current-part-description may-provide-data-on-request 3) reduce-annotation)
    (computation-setting ('may-provide-event-updates 'is boolean)
                         (current-part-description may-provide-event-updates 3) reduce-annotation)

    ))

(defun reduce-common-computation-phrase-scan-interval (parse)
  (setf (third parse) (car (third parse))) ; drop the "seconds" from the interval
  (reduce-annotation parse))


;;; `Computation-style-on-expression' is the external grammar that enables the
;;; user to edit the compuation-style part features of the
;;; compiled-cell-expression in a cell-expression-and-text (got that).  The
;;; parsed form for this is just a compilation-style parse.

(add-grammar-rules
  '((computation-style-on-expression 'none)
    (computation-style-on-expression computation-style)))

(defun twrite-computation-style (computation-style on-fresh-line)
  (let ((part-features-of-computation-style
          '(may-provide-event-updates
             may-provide-data-on-request
             time-out-when-requesting-data-seeking
             may-request-data-seeking
             may-request-event-updates
             break-message-level-for-computation-style
             warning-message-level-for-computation-style
             trace-message-level-for-computation-style
             update-only-when-shown
             value-domain
             initial-scan-wait-interval
             scan-interval
             priority))
        (use-none t)
        (scan-interval nil)
        (priority nil)
        (use-short-form t))
    (loop for (feature value) on (part-description-features computation-style) by #'cddr
          do
          (when (memq feature part-features-of-computation-style)
            (setq use-none nil)
            (case feature
              (scan-interval
               (setq scan-interval value))
              (priority
               (setq priority value))
              (t
               (setq use-short-form nil)))))
    (cond
      (use-none
;       (tformat "none")
       )
      (use-short-form
       (when on-fresh-line (tformat "~%  "))
       (tformat "evaluated")
       (when scan-interval
         (tformat " every ~NC"
                  scan-interval 'seconds))
       (when priority
         (tformat " at priority ~D" priority)))
      (T
       (when on-fresh-line (tformat "~%  "))
       (tformat "evaluated with these settings:~%")
       (write-part-description
         computation-style
         part-features-of-computation-style
         4
         t)))))

;;; Grammar, Compiler, and Writer for Computation-Style-Or-None

(add-grammar-rules
  '((computation-style-or-none computation-style-on-expression)))

(def-slot-value-writer computation-style-or-none (computation-style-or-none)
  (cond
    (computation-style-or-none
     (twrite-computation-style computation-style-or-none nil))
    (T
     (twrite-string "none"))))

(def-slot-value-compiler computation-style-or-none (parse-result frame-containing-annotation)
  (declare (use-for-default-overrides))
  (let (result error-message?)
    (with-named-dynamic-extent working-on-annotated-frame
                               ((current-block-of-dependent-frame
                                  (frame-being-edited frame-containing-annotation))
                                (current-annotated-frame frame-containing-annotation)
                                (current-computation-style the-only-dynamic-computation-style))
      (multiple-value-setq (result error-message?)
        (compile-part-description parse-result 'computation-style-description)))
    (values result error-message?)))



(define-category-evaluator-interface (computation-style-or-none
                                       :access read-write)
    (or (no-item)
        (structure
          computation-style-spec
          ((priority (member 1 2 3 4 5 6 7 8 9 10))
           (scan-interval number)
           (initial-scan-wait-interval number)
           (value-domain (member inference-engine g2-simulator))
           (update-only-when-shown truth-value)
           (trace-message-level (member 0 1 2 3))
           (warning-message-level (member 0 1 2 3))
           (break-message-level (member 0 1 2 3))
           (time-out-when-requesting-data-seeking integer)
           (may-request-event-updates truth-value)
           (may-request-data-seeking truth-value)
           (may-provide-data-on-request truth-value)
           (may-provide-event-updates truth-value))
          (or priority scan-interval initial-scan-wait-interval
              value-domain update-only-when-shown
              trace-message-level warning-message-level
              break-message-level time-out-when-requesting-data-seeking
              may-request-event-updates may-request-data-seeking
              may-provide-data-on-request may-provide-event-updates)))
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
    ((no-item) nil)
    ((structure)
     (phrase-cons
       'progn
       (loop for (feature-name . feature-value)
                 being each evaluation-structure-pair of evaluation-value
             collect (phrase-list
                       'set-simple-part-feature
                       'current-part-description
                       (phrase-list 'quote feature-name)
                       (phrase-list 'copy-for-slot-value
                                    (phrase-list
                                      'quote
                                      (if (evaluation-truth-value-p feature-value)
                                          (evaluation-truth-value-is-true-p feature-value)
                                          feature-value))))
               using phrase-cons)))))

  ((get-form (slot-value))
   (cond
     (slot-value
      (let ((feature-list
              (loop for (feature-name feature-value) on (cdr slot-value) by #'cddr
                    collect feature-name using eval-cons
                    collect (make-evaluation-value-based-on-type feature-value)
                      using eval-cons)))
        (allocate-evaluation-structure feature-list)))
     (t
      nil))))



;;;; Cell-Format And Associate Types And Editor Routines



(add-grammar-rules
  '(
    ;; There are only simple scalar features for cell format.
    ;; And we enumerate them one, at a time.

    ;; "the line-color is blue"
    (cell-format-annotation ('the 'line-color 'is color-or-metacolor)
                            (current-part-description 2 4) reduce-annotation)

    ;; "the background-color is blue"
    (cell-format-annotation ('the 'background-color 'is compute-part-feature-of-type-color-or-metacolor)
                            (current-part-description 2 4)
                            reduce-annotation-with-expression)

    ;; "the border-color is blue"
    (cell-format-annotation ('the 'border-color 'is color-or-metacolor)
                            (current-part-description 2 4) reduce-annotation)

    ;; "the text-alignment is center"
    (cell-format-annotation ('the 'text-alignment 'is text-alignment-kind)
                            (current-part-description 2 4) reduce-annotation)
    (text-alignment-kind 'left)
    (text-alignment-kind 'center)
    (text-alignment-kind 'right)

    ;; "the text-color is black"
    (cell-format-annotation ('the 'text-color 'is color-or-metacolor)
                            (current-part-description 2 4) reduce-annotation)

    (cell-format-annotation ('the 'text-size 'is text-size-kind)
                            (current-part-description 2 4) reduce-annotation)
    (text-size-kind 'small)
    (text-size-kind 'large)
    (text-size-kind 'extra-large)

    ;; "the width is 200"
    (cell-format-annotation ('the 'width '= integer)
                            (current-part-description 2 4) reduce-annotation)

    ;; "the height is 200"
    (cell-format-annotation ('the 'height '= integer)
                            (current-part-description 2 4) reduce-annotation)

    ))

(add-grammar-rules-for-list
  'cell-format 'cell-format-annotation
  '\; nil 'none)

(add-grammar-rules
  '((compute-part-feature-of-type-color-or-metacolor color-or-metacolor)
    (compute-part-feature-of-type-color-or-metacolor
      (left-part-of-compute-part-feature-of-type-color-or-metacolor
        actual-cell-expression-parse)
      (the 1 2))
    (left-part-of-compute-part-feature-of-type-color-or-metacolor
      ('given 'by 'the 'symbolic 'expression)
      (or symbol (unknown-datum))
      reduce-noting-source-position)))

(def-slot-value-writer cell-format (cell-part-description)
  (write-part-description cell-part-description cell-format-part-features))



;; None gets show, which is sad.

(def-slot-value-compiler cell-format (cell-part-description-parse frame-containing-annotation)
  (let (result error-message?)
    (with-named-dynamic-extent* working-on-annotated-frame
                                ((current-block-of-dependent-frame
                                   (frame-being-edited frame-containing-annotation))
                                 (current-annotated-frame current-block-of-dependent-frame)
                                 (current-computation-style the-only-dynamic-computation-style))
      (multiple-value-setq (result error-message?)
        (compile-part-description cell-part-description-parse 'cell)))
    (values result error-message?)))



;(def-slot-putter editable-slot-for-cell-format (annotation-editing-info new-value initializing-p)
;  (cond
;    (initializing-p
;     (setf (editable-slot-for-cell-format annotation-editing-info)
;           new-value))
;    (t
;     (let ((original-slot-value (editable-slot-for-cell-format annotation-editing-info)))
;       (with-named-dynamic-extent working-on-annotated-frame
;                                  ((current-annotated-frame
;                                     (frame-being-edited annotation-editing-info))
;                                   (current-block-of-dependent-frame
;                                     (frame-being-edited annotation-editing-info))
;                                   (current-computation-style
;                                     the-only-dynamic-computation-style))

;         ;; Remove any now obsolete formatting info.
;         (loop for part-feature in cell-format-part-features
;               do
;           (remove-simple-part-feature original-slot-value part-feature))
;         ;; Insert the new formatting info.
;         (loop for (feature-key feature-value)
;                   on (cdr new-value) by #'cddr
;               do
;           (set-simple-part-feature
;             original-slot-value
;             feature-key
;             (copy-for-slot-value feature-value)))
;         (reclaim-slot-value-list new-value))
;       (values original-slot-value t)))))



;;; `Cell-format-or-none'

(add-grammar-rules
  '((cell-format-or-none 'none)
    (cell-format-or-none cell-format)))

(def-slot-value-writer cell-format-or-none (cell-format-or-none-parse)
  (if (eq 'none cell-format-or-none-parse)
      (tformat "none")
      (write-part-description cell-format-or-none-parse cell-format-part-features)))


(def-slot-value-compiler cell-format-or-none (cell-format-or-none-parse frame-containing-annotation)
  (declare (use-for-default-overrides))
  (if (eq 'none cell-format-or-none-parse)
      nil
      (let (result error-message?)
        (with-named-dynamic-extent working-on-annotated-frame
                                   ((current-annotated-frame frame-containing-annotation)
                                    (current-block-of-dependent-frame frame-containing-annotation)
                                    (current-computation-style the-only-dynamic-computation-style))
          (multiple-value-setq (result error-message?)
            (compile-part-description cell-format-or-none-parse 'cell)))
        (values result error-message?))))


(define-category-evaluator-interface (cell-format-or-none
                                       :access read-write)
    (or (no-item)
        (structure cell-format-spec
                   ((background-color (named color-or-metacolor))
                    (line-color (named color-or-metacolor))
                    (border-color (named color-or-metacolor))
                    (text-color (named color-or-metacolor))
                    (text-alignment (member left center right))
                    (text-size (named font-name))
                    (width integer)
                    (height integer))
                   (or background-color line-color
                       border-color text-color
                       text-alignment text-size
                    width height)))
  ((set-form (evaluation-value))
   (evaluation-etypecase evaluation-value
    ((no-item) nil)
    ((structure)
     (phrase-cons
       '\;
       (loop for (feature-name . feature-value) being
             each evaluation-structure-pair of evaluation-value
             collect (phrase-list
                       'set-simple-part-feature
                       'current-part-description
                       (phrase-list 'quote feature-name)
                       (if (eq feature-name 'background-color)
                           (phrase-list 'quote feature-value)
                           (phrase-list 'copy-for-slot-value
                                        (phrase-list 'quote feature-value))))
               using phrase-cons)))))
  ((get-form (slot-value))
   (cond
     (slot-value
      (allocate-evaluation-structure (copy-list-using-slot-value-conses (cdr slot-value))))
     (t
      nil))))



;;;; Cell-Expression And Associate Types And Editor Routines




;;; The grammar type `cell-expression-parse' is compiled into a part
;;; description of the part type `cell-expression'.  The editor wraps
;;; this with the actual text the user typed creating a list structure
;;; of the type cell-expression-and-text.  Instances of
;;; cell-expression-and-text are found in part features, for example the
;;; cell-contents of a table cell.

;;; To summarize:
;;;     cell-expression-parse    -- a grammar type
;;;     cell-expression          -- a part type
;;;     cell-expression-and-text -- a simple type, a part feature type,
;;;                              -- a list structure
;;;     cell-contents            -- a part feature of type cell-expression-and-text

(def-list-structure (cell-expression-and-text
                      (:consing-function slot-value-cons))
    (cell-expression-of-cell-expression-and-text
      . text-of-cell-expression-and-text))


;(add-grammar-rules
;  '((cell-expression-parse 'none)
;    (cell-expression-parse expression)
;    (cell-expression-parse
;      (expression '\; computation-style)
;      (expression-with-computation-style 1 3))))

(add-grammar-rules
  '((cell-expression-parse 'none)
    (cell-expression-parse actual-cell-expression-parse)
    (actual-cell-expression-parse expression 1 reduce-noting-source-position)
    (actual-cell-expression-parse
      (expression '\; computation-style) nil reduce-to-bad-phrase)
    (actual-cell-expression-parse
      (actual-cell-expression-parse-1 computation-style)
      (expression-with-computation-style 1 2))
    (actual-cell-expression-parse-1
      (expression '\;)
      1 reduce-noting-source-position)))

(defun reduce-to-bad-phrase (x)
  (declare (ignore x))
  bad-phrase)





;;; When a cell-expression-parse is compiled the result is a `cell-expression.'
;;; Cell-expressions come in two flavors, compiled-cell-expression, and
;;; simple-cell-expression.

;;; A cell expression value is used when the value will be displayed to the
;;; user as text.  The type computable-feature, discussed below, is used when
;;; the text value is not needed.

;;; Simple-cell-expression are constants that do not require the
;;; evaluator to compute their value, they are represented as a slot
;;; value cons with the atom that is the expression in their car and the
;;; symbol simple-cell-expression in their cdr.  The predicate
;;; `simple-cell-expression-p' is provided.  Instances may be reclaimed with
;;; reclaim-slot-value.  Simple-cell-expressions are created when the user
;;; enters a float, integer, or string.  They are not created for truth
;;; values.

;;; Compiled-cell-expressions are represented as part descriptions of
;;; the type compiled-cell-expression.  A compiled-cell expression is
;;; defined as a refinement of the computation-style part with an
;;; additional `expression-cell-index' and `expression-source-text' part feature.
;;; The predicate `compiled-cell-expression-p is provided.

;;; Compiled-cell-expressions are used in two places.  First they are
;;; used in the slots values of the type of cell-expression-and-text.
;;; They also appear as the values of some part features when it is legal
;;; for those part features to be specified by a computed value.

(def-list-structure (simple-cell-expression-p)
                    (simple-cell-expression-value . simple-cell-expression-tag))

(defun simple-cell-expression-p (x)
  (and (consp x)
       (eq 'simple-cell-expression
           (simple-cell-expression-tag x))))

(def-part-type compiled-cell-expression
  (includes computation-style-description)
  (user-spelling nil)
  (hidden-features
    may-provide-data-on-request ; may-request-data-seeking
    may-provide-event-updates))

(defun compiled-cell-expression-p (x)
  (and (consp x)
       (eq 'compiled-cell-expression
           (part-description-type x))))

(def-part-feature (compiled-cell-expression expression-cell-index)
  (type expression-cell-index))

(def-part-feature (compiled-cell-expression expression-source-text)
  (type text-string))

;;; Care is required when reclaiming part descriptions that contain these
;;; types.  The cell-array must be kept in synch.  Since the cell may have
;;; tasks associated with it the cell must be deactivated prior to triggering
;;; the reclaimers.  Deactivating the cell will trigger a display update
;;; so it must be deactivated prior to removing it from the enclosing frame.

(def-part-feature-type-reclaimer expression-cell-index (expression-cell-index)
  (let ((*current-computation-frame* current-annotated-frame)
        (current-computation-component-particulars
          (slot-value-list 'cell-array-element expression-cell-index)))
    (within-named-dynamic-extent working-on-annotated-frame
      (delete-cell-from-g2-cell-array
        (cell-array current-annotated-frame)
        expression-cell-index))
    (reclaim-slot-value-list current-computation-component-particulars)))

(def-part-feature-type-reclaimer cell-expression-and-text
                                 (cell-expression-and-text)
  (let ((cell-expression
          (cell-expression-of-cell-expression-and-text
            cell-expression-and-text)))
    (when (compiled-cell-expression-p cell-expression)
       (deactivate-cell-of-g2-cell-array
         (cell-array current-annotated-frame)
         (get-simple-part-feature
           cell-expression
           'expression-cell-index))
       (reclaim-part-description cell-expression)
       (setf
         (cell-expression-of-cell-expression-and-text
           cell-expression-and-text)
         nil)))
  (reclaim-slot-value cell-expression-and-text))


(def-part-feature-type-validation cell-expression-and-text
                                  (cell-expression-and-text)
  (let ((cell-expression
          (cell-expression-of-cell-expression-and-text
            cell-expression-and-text)))
    (cond
      ((compiled-cell-expression-p cell-expression)
       (validate-part-instance-inner
         'compiled-cell-expression
         cell-expression))
      ((simple-cell-expression-p cell-expression)
       (unless (and (simple-cell-expression-p cell-expression)
                    (let ((value (simple-cell-expression-value cell-expression)))
                      (or (text-string-p value)
                          (integerp value)
                          (slot-value-float-p value))))
         (fail-validation "malformed simple-cell-expression-p"))))))


(defun compile-a-cell-expression-with-optional-computation-style (expression-parse desired-evaluation-type)
  (let ((text-end-position? nil)
        (computation-style-parse? nil))

    ;; Pick the parse apart into three pieces:
    ;; a computation style, an expression parse, and the "text" of that expression

    (when (and (consp expression-parse)
               (eq 'expression-with-computation-style
                   (first expression-parse)))

      ;; At this point it looks like:
      ;; (expression-with-computation-style
      ;;     (source-position <expression-parse> . <end-source-position>)
      ;;     <computation-style>)
      ;; where <source-pos> is the source position after the semicolon that terminated the expression.

      (destructuring-setq (nil expression-parse computation-style-parse?) expression-parse))

    ;; Note: it may be the case that every expression-parse that reaches this point is always wrapped
    ;; within its source position.  However, to be safe, I inserted this guard because verifying this
    ;; assertion is of much lower priority than attending to other outstanding tasks.  --wgd 06/24/92

    (if (not (and (consp expression-parse) (eq (car expression-parse) 'source-position)))
        (progn #+development
               (cerror "continue" "expression missing source position?"))
        (destructuring-setq (nil expression-parse . text-end-position?) expression-parse))

    (multiple-value-bind (result error-message?)
        (compile-a-compiled-cell-expression-from-style-and-expression-parse
          expression-parse
          computation-style-parse?
          desired-evaluation-type)
      (values result error-message? text-end-position?))))

;; This is a mess.  This routine is called to handle expressions that appear in both
;; formating attributes and in the cell expressions of tables.  In both those cases
;; the grammar should be unified.  The unified grammar should decorate the parse
;; with a start and end source position, and the desired evaluation type.  The uglyness
;; of this code and it's two callers arises from the grammar optionally included all
;; three of these.



;;; The `compiler of a cell-expression-parse' creates nil or a
;;; cell-expression as its output.  Nil is returned if the parse was
;;; NONE.  It returns a simple-cell-expression if possible.  Otherwise
;;; the compilation of a compiled-cell-expression proceeds in two
;;; stages; first any computation-style is compiled, and then the
;;; expression is registered into the cell array.  Only the first stage
;;; can fail, returning bad-phrase.  The second stage has lots of side
;;; effects on the ultimate target frame.  These are documented under
;;; the routine register-expression-cell-during-compilation in the
;;; module CELLS.

;;; The analysis of consistency is retracted around the second stage since
;;; the names used by the enclosing block are changed by the compile.

(def-slot-value-compiler cell-expression-parse
                         (cell-expression-parse temporary-frame-for-editor)
  (unless (frame-has-been-reprocessed-p        ; condition added. (MHD 10/10/96)
            (frame-being-edited temporary-frame-for-editor)
            (frame-serial-number-of-frame-being-edited
              temporary-frame-for-editor))
    ;; <<< -- Note: formatting anomoly -- I'm not reformatting to minimize CVS diffs. (MHD 10/10/96)
  ;; First decide if this parse can be compiled into a simple-cell-expression.
  (let ((result 'unknown)
        (error-message? nil)
        (expression-text-end-position? nil)
        expression-text-string
        (possible-scalar (if (and (consp cell-expression-parse)
                                  (eq 'source-position
                                      (car cell-expression-parse)))
                             (second cell-expression-parse)
                             cell-expression-parse)))
    (cond
      ((eq 'none cell-expression-parse)
       (setq result nil))
      ((or (text-string-p possible-scalar)
           (integerp possible-scalar)
           (slot-value-float-p possible-scalar))
       (setq result
             (phrase-cons possible-scalar 'simple-cell-expression))
       (setq expression-text-string (convert-text-to-text-string
                                      (text-being-edited current-edit-state)
                                      nil nil nil nil nil t
                                      )))
      (t
       ;; Oh well, we have to make it a compiled-cell-expression
       (let* ((current-block-of-dependent-frame (frame-being-edited temporary-frame-for-editor)))
         (multiple-value-setq (result error-message? expression-text-end-position?)
           (compile-a-cell-expression-with-optional-computation-style
             cell-expression-parse
             '(or datum (unknown-datum) (obsolete-datum))))
         (unless (eq result bad-phrase)
           (setf expression-text-string
                 (text-string-from-current-source nil expression-text-end-position?))
           (note-use-of-text-string-in-phrase expression-text-string)))))

    (if (eq result bad-phrase)
        (values bad-phrase
                error-message?)
        (values (phrase-cons result
                             expression-text-string)
                error-message?)))))

;;; Compiles into a compiled-cell-expression given both an expression parse and
;;; a computation style parse.  It returns two values the first of which is the
;;; resulting part-description or bad-phrase.  If bad-phrase is returned the
;;; second value is an error message

;;; A third argument indicates the type desired for the values computed by the
;;; cell, it is copied internally.  The computation-style-parse may be nil.

;;; This must be invoked with current-block-of-dependent-frame bound
;;; approprately so the cell array can be accessed.

;;; The caller must take care to save the expression text so it may be accessed
;;; when editing, text stripping, recompiling or tracing.

(defun compile-a-compiled-cell-expression-from-style-and-expression-parse
       (expression-parse computation-style-parse? desired-evaluation-value-type)
  (let (result
        error-message?)
    (with-named-dynamic-extent working-on-annotated-frame
                               ((current-annotated-frame   current-block-of-dependent-frame)
                                (*current-computation-frame* current-block-of-dependent-frame)
                                ;; (current-computation-style the-only-dynamic-computation-style)
                                )
      ;;; Compile the computation style.
      (multiple-value-setq (result error-message?)
        (cond
          (computation-style-parse?
           (compile-part-description
             computation-style-parse?
             'compiled-cell-expression))
          (T
           (phrase-list 'compiled-cell-expression))))

      ;; Compile the expression, install it in the cell array, and record it in the result.
      (unless (eq bad-phrase result)
        (nconc result
               (phrase-list
                 'expression-cell-index
                 (compile-a-compiled-cell-expression-from-expression-parse-and-style-description
                   expression-parse
                   result
                   desired-evaluation-value-type)))))
    (values result error-message?)))

;;; `Compile-a-compiled-cell-expression-from-expression-parse-and-style-description' returns
;;; a cell index of an expression cell in the cell array of the current block of dependent frame.
;;; The three arguments passed configure the cell.
;;;    1. an expression parse.
;;;    2. a computation style description.
;;;    3. the desired evaluation type.
;;; The storage used by the arguments is the responsiblity of the caller.

;;; This should be invoked within these dynamic extents:
;;;    A. working-on-annotated-frame
;;;    B. current-block-of-dependent-frame is bound
;;;    C. *current-computation-frame* is bound
;;;    D. in an editor context.
;;; It will establish these dynamic extents:
;;;    E. without-consistency-analysis
;;;    F. cell-index-currently-being-registered is bound
;;;    G. current-compuation-component-particulars will be bound
;;; so that errors during compilation of the frame may be recorded in frame
;;; notes approprately and so that log book messages denote the source of
;;; the problem approprately.  G is useful when the cell index has not
;;; been installed into the frame yet.

(defun compile-a-compiled-cell-expression-from-expression-parse-and-style-description
       (expression-parse computation-style-description-for-embedded-part desired-evaluation-value-type)
  (let* ((cell-array (cell-array current-block-of-dependent-frame))
         (new-cell-index (make-empty-expression-cell cell-array))
         (cell-index-currently-being-registered new-cell-index)
         (current-computation-component-particulars
           (slot-value-list 'cell-array-element new-cell-index))
         (current-computation-style the-only-dynamic-computation-style))
    (without-consistency-analysis (*current-computation-frame*)
      ;; Can't use set-simple-part-feature, we are in the phrase cons pool
      (with-part-description ((get-default-computation-style-of-class))
        (with-part-description ((get-default-computation-style-of-frame))
          ;; Note 1.
          (let* ((g2-lambda? (and (consp expression-parse)
                                  (eq (car expression-parse) 'g2-lambda)))
                 (argument?  (when g2-lambda? (car (second expression-parse))))
                 (local?     (when g2-lambda? (car argument?)))
                 (class?     (when g2-lambda? (second (second argument?))))
                 (domain?    (when g2-lambda? (phrase-cons class? local?)))

                 ;; AC 8-31-91 Replaced cons with phrase-cons in the previous expression.
                 ;; There was a problem in the translation in that there
                 ;; was a local variable "cons" as well as a call to the function "cons"
                 ;; and the compiler wouldn't accept it.

                 (attribute? (when g2-lambda? fake-attribute)))
            (when g2-lambda?
              (destructuring-setq (nil ((local? (nil class?))) . nil) expression-parse)
              ;;(modify-tree      expression-parse
              ;;                        (nil ((     1 (nil    nil))) . nil) class?)
              (setf (car (car (second expression-parse))) class?))
            (with-part-description (computation-style-description-for-embedded-part)
              (register-expression-cell-during-compilation
                cell-array
                new-cell-index
                nil
                expression-parse
                desired-evaluation-value-type
                domain? attribute?))
            (when g2-lambda?
              ;;(modify-tree        expression-parse
              ;;                        (nil ((     1 (nil    nil))) . nil) local?)
              (setf (car (car (second expression-parse))) class?))))))
    (reclaim-slot-value-list current-computation-component-particulars)
    new-cell-index))

;; Note 1: This bogosity handles the current implementation of compile-expression
;; downstream from here.




;;; `Get-default-computation-style-of-class' returns a computation-style-description.
;;; The computation style description returned is based on the class of the
;;; *current-computation-frame*.  The returned list is owned by this routine and
;;; should not be reclaimed.

;;; The computation style of any fragment of code is computed using
;;; information from many sources.  These include:

;;;   1. G2 default computation style for all computations.
;;;   2. KB specific settings as given in system tables.
;;;   3. G2 default settings for a class
;;;   4. KB specific setting for a class as given in system tables.
;;;   5. Instance specific settings.
;;;   6. Computation specific settings

;;; The third of these is hardwired into this routine.  Therefore this routine
;;; is the basis of documenting the default behavor of most computations.

(defun get-default-computation-style-of-class ()
  (frame-class-case *current-computation-frame*
    ((new-table chart)
     '(computation-style-description
        scan-interval nil
        priority 2
        initial-scan-wait-interval 2
        update-only-when-shown t
        value-domain inference-engine

        may-request-event-updates t
        may-request-data-seeking nil  ;; T causes a cute behavor in response to expired value events.
         time-out-when-requesting-data-seeking  nil

        may-provide-data-on-request nil
        may-provide-event-updates nil
        ))

    ;; The scan interval and initial scan wait interval are not applicable to
    ;; generic or instance formulas (at least not now), and so are zero.  The
    ;; priority of the execution of the formula is completely determined by the
    ;; caller of the formula, and so defaults to 10 here.  Whether or not the
    ;; formula is shown does not affect the execution.  It is not invokable via
    ;; forward chaining.  Backward chaining to formulas is implemented outside
    ;; of the cells facility (for now) and so invokable via backward chaining is
    ;; off.  May cause backward chaining is true by default, and may cause
    ;; forward chaining is inapplicable, since formulas don't contain actions.
    ((variable generic-formula)
     '(computation-style-description
        scan-interval nil
        priority 10
        initial-scan-wait-interval 0
        update-only-when-shown nil
        value-domain inference-engine
        may-request-event-updates nil
        may-request-data-seeking t
        time-out-when-requesting-data-seeking nil
        may-provide-data-on-request nil
        may-provide-event-updates nil))

    ((inter-g2-data-request-holder)
     '(computation-style-description
        scan-interval nil
        priority 6
        initial-scan-wait-interval 0
        update-only-when-shown nil
        value-domain inference-engine
        may-request-event-updates nil
        may-request-data-seeking t
        time-out-when-requesting-data-seeking nil  ;; Is infinite.
        may-provide-data-on-request nil
        may-provide-event-updates nil))

    ((readout-table dial meter)
     '(computation-style-description
        scan-interval 5
        priority 2
        initial-scan-wait-interval 2
        update-only-when-shown t
        value-domain inference-engine
        may-request-event-updates nil
        may-request-data-seeking t
        time-out-when-requesting-data-seeking nil
        may-provide-data-on-request nil
        may-provide-event-updates nil))
    ((user-menu-choice)
     '(computation-style-description
        scan-interval nil
        priority 10
        initial-scan-wait-interval 2
        update-only-when-shown nil
        value-domain inference-engine
        may-request-event-updates nil
        may-request-data-seeking nil
        time-out-when-requesting-data-seeking nil
        may-provide-data-on-request nil
        may-provide-event-updates nil))

    (block
      '(computation-style-description
         priority 2
         scan-interval nil
         initial-scan-wait-interval 2
         update-only-when-shown nil
         value-domain inference-engine
         may-request-event-updates nil
         may-request-data-seeking nil
         time-out-when-requesting-data-seeking nil
         may-provide-data-on-request nil
         may-provide-event-updates nil))
    #+development
    (t
      (error "Not good, get-default-computation-style-of-class when ~S is current-computation-fame"
             *current-computation-frame*))))




;;; `Get-default-computation-style-of-frame' returns a computation-style-description.
;;; This description specifies any computation style settings that are unique to the
;;; *current-computation-frame*.  The returned value should not be reclaimed by
;;; the caller.

;;; See also get-default-computation-style-of-class which enumerates all possible
;;; contributors to the computation style.  This routine implements a class independent
;;; way to obtain number five in that list (i.e. instance-specific-settings).

(defun get-default-computation-style-of-frame ()
  (or (class-case (class *current-computation-frame*)
        (new-table
          (get-slot-value *current-computation-frame* 'default-evaluation-setting)))
    '(computation-style-description)))



(def-slot-value-writer cell-expression-parse (cell-expression-and-text)
  (gensym-dstruct-bind ((cell-expression . expression-text-string) cell-expression-and-text)
    (tformat "~A" expression-text-string)
    (when (compiled-cell-expression-p cell-expression)
      (twrite-computation-style cell-expression t))))







;;;; Computed Part Features And Associate Types And Editor Routines



;;; Computed-part-features are a type of value found in part features
;;; when we have allowed the user to specify the value either by
;;; a simple constant as in:
;;;    "RED"
;;; or via an expression as in:
;;;    "GIVEN BY THE SYMBOLIC EXPRESSION
;;;      (IF THE STATUS OF PUMP2 IS OK THEN "GREEN" ELSE "RED")


;;; Computed-part-features come in two flavors constant or evaluated.
;;; The predicates constant-computed-part-feature-p and
;;; evaluated-computed-part-feature-p are provided to distinguish them.
;;; The constant values are represented directly, and hence take little
;;; space.  The evaluated values are represented as a computed-part-expression
;;; part description.

(defun constant-computed-part-feature-p (computed-part-feature)
  (atom computed-part-feature))

(defun evaluated-computed-part-feature-p (computed-part-feature)
  (consp computed-part-feature))



;;; Value-of-computed-part-feature returns an evaluation value for
;;; the given computed-part-feature.   This must be invoked when
;;; current-block-of-dependent-frame is bound to the block within
;;; with the cell array will be found.

;;; Value-of-computed-part-feature takes two arguments; a computed-part-feature
;;; and a default-value.  When an evaluated-computed-part-feature is registered
;;; into the cell array the actual desired type is union'ed with the types
;;; (unknown-datum), (obsolete-datum).  If value-of-computed-part-feature
;;; encounters either of these the default-value is returned.

(defun value-of-computed-part-feature (computed-part-feature default-value)
  (if (constant-computed-part-feature-p computed-part-feature)
      computed-part-feature
      (let* ((expression-cell
               (managed-svref (g2-cell-array-managed-array
                                (cell-array current-block-of-dependent-frame))
                              (get-simple-part-feature
                                computed-part-feature
                                'expression-cell-index)))
             (result
               (g2-expression-cell-cached-value expression-cell)))
        (if (or (evaluation-obsolete-datum-p result)
                (null result)) ; (evaluation-unknown-datum-p result)
            default-value
            result))))


;;; `Compile-computed-part-feature' is called to convert a the parse of computed
;;; part feature into a part description and associated expression cell.

;;; This is called via simple eval as it processes a part description's parts
;;; that contained the parse of a computed-part-feature.  So the result is made
;;; a made from slot value conses.

;;; The incomming parse looks like so:
;;;   (the (source-position <evaluation-type> <source-pos-1>) <expression-plus>)
;;; where the <evaluation-type> indicates the type to request when we install the
;;; expression cell, and <source-pos-1> indicates the beginning of the expression.

;;; The <expression-plus> either just an expression
;;;   <expression>
;;; or it is of the form:
;;;   (expression-with-computation-style
;;;      (source-position <expression> <source-pos-2>)
;;;      <evaluation-setting-parse>)

;;; The <evaluation-settings-parse>, if any, processed by compile-part description.
;;; That forms the first draft of the resulting part-description, a compiled-part-feature.
;;; The souce text of the expression is extracted from the current source using
;;; <source-pos-1> and <source-pos-2> and this is stored into the result.
;;; The <expression> is registered into a new expression cell with the desired type
;;; (or <evaluation-type> (unknown-datum)), and this cell is stored into the part
;;; description.

(defun compile-computed-part-feature (parse-of-computed-part-feature)
  ;; Pick apart the parse.
  (let (result
        error-message?
        source-position-2?)

    (gensym-dstruct-bind ((nil (nil desired-evaluation-type . source-position-1) expression)
                         parse-of-computed-part-feature)
      (multiple-value-setq (result error-message? source-position-2?)
           (compile-a-cell-expression-with-optional-computation-style
             expression
             desired-evaluation-type))

      ;;; Snarf and stuff the expression text.
      (cond
        ((null error-message?)
         ;; In the phrase-cons pool, can't use set-simple-part-feature.
         (nconc result
                (phrase-list 'expression-source-text
                             (text-string-from-current-source
                               source-position-1 source-position-2?)))
         (copy-for-slot-value result))
        (t
         (values bad-phrase error-message?))))))


(defun write-computed-part-feature (desired-evaluation-type embedded-simple-type computed-part-feature)
  (cond
    ((constant-computed-part-feature-p computed-part-feature)
     (write-instance-of-simple-type embedded-simple-type computed-part-feature))
    (t
     (tformat "given by the ~A expression~A"
              (case desired-evaluation-type
                (symbol "symbolic"))
              (get-simple-part-feature computed-part-feature 'expression-source-text))
     (twrite-computation-style computed-part-feature t))))



;;;; To Do List for Part Descriptions




;; = Design Issues
;;  - The defvar suppression mechanism is now a historical artifact, the
;;    provision for include in part-type makes is unnecessary.
;;  - Need to make means of scanning upon a computed feature more integral.
;;  - Including the focus triggering.
;;  - Including the simple type spec.
;;  - Printing an annotation's is/= is bogus, an evaluation type association
;;    on simple types might help.
;;  - need to review all users of background-color!!!!

;; = Issues with Debugging Tools
;;  - Validation of parts does not validate the differences between the
;;    kinds of subpart-collections correctly.

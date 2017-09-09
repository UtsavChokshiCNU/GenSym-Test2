;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module FRAMES2B (used to be FRAMES2A)

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; M. Levin


(declare-forward-reference note-change-to-block-1 function)

(declare-forward-reference rebuild-backpointers-of-g2-cell-array function) ; CELLS

(declare-forward-reference remove-compilations-from-obsolete-cell-array function)	; CELLS

(declare-forward-reference loading-kb-p variable)	; KB-LOAD2

(declare-forward-reference compilations-up-to-date-p function)	; COMP-UTILS

(declare-forward-reference update-frame-status function)	; FRAMES5

(declare-forward-reference note-frame-with-compilation-removed function)	; KB-LOAD2


(declare-forward-reference release-lock function)        ; PROC-UTILS



;;;; Kb-frame and block




(def-class (kb-frame root define-predicate))




;;; The `class virtual attribute' returns the symbol naming the class of the given item.

(def-virtual-attribute class ((class root) symbol ())
  :event-updates nil
  :initial ((class) class)
  :getter  ((item) (class-name-of-class-description
		     (class-description-slot item))))

(def-virtual-attribute foundation-class ((class root) symbol ())
  :event-updates nil
  :initial ((class)
	    (let ((class-description? (class-description class)))
	      (or (and class-description?
		       (second
			 (get-class-feature-in-class-description-if-any
			   class-description? 'foundation-class)))
		  class)))
  :getter  ((item)
	    (second (get-class-feature-in-class-description-if-any
		      (class-description-slot item)
		      'foundation-class))))

;; One could imagine a :setter operation that would allow us to transform an
;; instance of one class into an instance of another, but that ain't here yet.
;; -jra 5/17/96




;;; The definition of block has been moved here from FRAMES3.
;;; Most of what follows it is left there for now. The purpose of
;;; this is to introduce the slots frame-flags, frame-flags-2 and
;;; frame-serial-number at this point. frame-flags and frame-serial-number
;;; were previously defined as part of root.

;;; The slot `Name-for-debugging' on block is discussed in the module tables
;;; near the routine get-or-make-up-designation-for-block.

;; Consider having another class at this point, 

(def-class (block (kb-frame system-item) define-predicate)

  ;; The following were formerly on kb-frame
  ;; GENSYMCID-1140: G2 performances slow down executing the same test
  ;; Change to vector slot for performance. -- Chun Tian (binghe), Apr 16, 2014
  (frame-status-and-notes			; a frame status or a list of the form
    nil system vector-slot			;   (frame-status . frame-note-plist)
    (type frame-status-and-notes) save do-not-clone
    not-user-editable
    (attribute-export-comment
      "Frame status and notes is broken into 2 attribute-mimics for export: ~
       item-status and notes"))
  (frame-author-or-authors 		; a symbol or a list of symbols or
					;   a list of  ((symbol . date) . symbols)
					;   or nil
					; where (>= date time-of-frame-edit-base-time)
					; (Format changed to include date
					;   in development of 4.0. (MHD 4/12/94))
					; Note: this is defined for all classes, but
					;   has a type feature (to cause it to be
					;   displayed as an attribute and edited
					;   only for certain select classes, namely
					;   the "definitional" classes; see
					;   all-definitional-classes
    nil system lookup-slot
    ; (type authors-with-time-of-last-edit?)  ; use on selectively enabled classes
    do-not-clone			   ; should be enabled on definition and
					   ;   the "definitional" classes; see
					   ;   the list in KB-MERGE
    (attribute-export-comment
      "Will allow 0 or more author entries. each author entry may have a date. ~
authors: ([ name: symbol, date: gensym-time ] * ), editor-grammar: struct, defining-class: item, writable: true
"))
  
  (change-log-information
    nil system lookup-slot  ;; should be a vector slot?
    (type nil)
    do-not-clone
    do-not-put-in-attribute-tables)

  (frame-change-log			; Disciple of frame-author-or-authors (MHD 11/1/96)
    nil
    not-user-editable			; value managed by system
    ; (type frame-change-log) ; use on selectively enabled classes
    system lookup-slot
    do-not-clone
    (attribute-export-comment
      "(to replace authors attribute; however, no documentation is available at this time)"))
  
  
  

  (frame-representations		; a list of tables (and other things?)
    nil system save vector-slot)	; keep as a vector slot; critical to attributes
					;   displays and T2/Javalink publish/subscribe mechanism

  (changed-slots-to-represent		; ( { changed-slot } ), where changed-slot
    nil system vector-slot do-not-save)	;   is either slot-description or (slot-description
					;      slot-component-name? slot-componenent-indicator?)
					; gets to be non-nil when frame is added to
					;   table-representation-update-schedule;
					;   must be nil otherwise; see TABLES

  (frame-transforms-of-block		; A list of graphics alist of 
    nil system lookup-slot do-not-save) ;    (image-plane . frame-transform)
					; (NB: "frame" here means graphic 
					;   transformation frames, not frame-
					;   system "frame", as with the other
					;   slots.)
  ;; ; See bind-initial-transformation-of-frame-transform
  ;; for discussion of the next two slots.
  (remembered-block-transform nil system lookup-slot save)
  (unsaved-but-remembered-block-transforms nil system lookup-slot do-not-save)
  

  ;; A cached slot-value-list of blocks and connections which overlap us.
  (overlapping-blocks-cache
    nil system lookup-slot do-not-save)

  (block-changes			 ; Indicator of pending drawing. Reclaimer in PANES.
    nil system vector-slot do-not-save)

  (layer-position-of-block		 ; Position in superblock, if any.
    0 system lookup-slot do-not-save)
  

  (original-kb-state-plist		 ; a plist of kb state variables and their
    nil system lookup-slot
    (attribute-export-comment		;   original values; see custom 
      "plist of kb state variables and their original values. Internal for now? ~
	Export as kb-state-after-reset?"))
					 ;   reclaimer defined in FRAMES4
  (kb-state-changes-previous-cons?	; either nil or the cons before the cons holding
   nil system lookup-slot		;   this frame in kb-state-changes; not saved/cloned,
   do-not-clone do-not-save)		;   not reclaimed (special reclaimer is a noop)

  (menus-for-this			 ; a list of menus that point back
    nil system lookup-slot do-not-save)	 ;   via what-this-is-a-menu-for; see 
					 ;   custom reclaimer defined in FRAMES4

  ;; Deprecate the user-restrictions slot: don't show to the user and don't save.
  (user-restrictions nil system lookup-slot (type user-restrictions)
		     ;; This curious option makes the slot invisible except to GPL programs.
		     previously-put-in-attribute-tables
		     do-not-save
		     (attribute-export-comment
		       "Deprecate the user-restrictions slot: don't show to the user and don't save."))

  ;; New lookup slot which replaces user-restrictions.  (fmw 11-Aug-93)
  (object-configuration nil system lookup-slot (type object-configuration)
			(attribute-export-comment "Object-configuration is aliased to item-configuration. ~
The value is a list of ( <I>configuration-expression</I> * ), writable = true. ~
Will we read and write the individual configuration expressions as text?"))

  ;; This is where block attributes began before 3/11/91.
  ;; Further changes will reduce the number of slots.

  (name-or-names-for-frame			; symbol or list of symbols
    nil system (type name-or-names) do-not-clone
    namelike-slot ; new: replaces obsolete declare-namelike-slot declaration (MHD 5/14/00)
    (attribute-export-comment "See comment in class block"))

  (name-for-debugging
    nil system lookup-slot
    (attribute-export-comment "names-for-debugging: ( <I>symbol</I> *), e.g. tank-xxx-1"))
  (tracing-and-breakpoints
    nil system lookup-slot user-overridable save (type nil)
    (attribute-export-comment "[warning-message-level: (or default &lt;integer&gt;), ~
tracing-message-level: (or default &lt;integer&gt;), ~
breakpoint-level: (or default &lt;integer&gt;)]"))

  ;; Used to cache role values.
  (role-cache nil system lookup-slot)

  ;; GENSYMCID-1164: G2 performances slowdown between MAR 13 and JUL 13 release.
  ;;
  ;; The slot-type of `relation-instances' has been changed from lookup-slot to
  ;; vector-slot for better performance.  -- Chun Tian (binghe), Jan 23, 2014
  (relation-instances nil (type relation-instances) system
		      vector-slot ; old: lookup-slot
		      save
		      do-not-put-in-attribute-tables do-not-clone)

  ;; used to access the lists that this is a member of.  See the file lists.
  (list-elements-for-item
    nil system vector-slot ; for push-atomic, previous: lookup-slot
    (attribute-export-comment
      "Used to access the lists that this is a member of.  Internal."))
  ;; GENSYMCID-1824: Cat-freeform-table issue (UNACEM)
  ;; Use `vector-slot' for debugging of cell arrays. -- Chun Tian (binghe), Aug 14, 2016.
  (cell-array nil system lookup-slot save)

  ;; Slot-group-for-block? holds the superblock?, subblocks? and block edges.
  (slot-group-for-block? nil system vector-slot save)

  ;; squirreled-data is used transiently during warmboot. It is not saved, nor
  ;; is it user visible.
  (squirreled-data nil system lookup-slot)
  (registered-event-detectors
    nil system vector-slot
	(attribute-export-comment "callbacks: ( <I>callback</I> * ),"))

  ;; An obsolete set of slots...
  ;; The content rectangle overlaps the block edges.  It is the actual
  ;; portion of the block being displayed when the block is enclosed
  ;; by a scrolling frame.  When bound this plus the frame's indent is
  ;; the extent of the block for the "extreme edges."  This is a slot
  ;; value list of four W values.
  ;;  (left-edge-of-content-of-block-1 -1 system lookup-slot save)
  ;;  (top-edge-of-content-of-block-1 -1 system lookup-slot save)
  ;;  (right-edge-of-content-of-block-1 -1 system lookup-slot save)
  ;;  (bottom-edge-of-content-of-block-1 -1 system lookup-slot save)
  (position-of-horizontal-elevator 0 system lookup-slot save)
  (position-of-vertical-elevator 0 system lookup-slot save)
  (invocation-locking-this-object nil system do-not-save do-not-clone))

(def-slot-value-reclaimer invocation-locking-this-object (invocation entity)
  (setf (invocation-locking-this-object entity) nil)
  (release-lock invocation))

;; The following was an impossibly long class comment.  -jra 5/21/96

;(class-export-comment
;                    "Re: name-or-names-for-frame, aliased to names. The name ~
; or names of the item. Should be changed to attribute-mimic: names. ~
; Type of name-or-names is ( <I>symbol</I> *).  Though the internal name ~
; of the grammar-category is name-or-names, I propose the exported name of ~
; the grammar category be the simpler 'name-list, and perhaps the type should ~
; be (or none name-list). Another possibility is (or none name (seq name)). ~
; The issue of how we treat singular/plural attribute names should be ~
; resolved quickly.
;
;Attributes described in original document as those based on item or workspace: Reconcile.
;
;<ul>
;<!--variables, parameters, rules and procedures?--><br> 
;
;<li>invisible-color: color-symbol,
;<li>magnification: [x-magnification: number, y-magnification: number],
;<li>size: [x-dimension: number, y-dimension: number]
;<li>rotation/reflection: rotation/reflection-symbol,
;<li>item-layer-position: integer,               ; {from layer-position-of-block}
;<li>item-x-position: integer,
;<li>item-y-position: integer,
;<li>attribute-displays: ( view * ), ; not writable
;<li>attribute-tables:  ( view * ), ; not writable
;<li>name-boxes: ( view * ), ; not writable
;<li>item-views: ( view * ),     ; {from frame-representations}, not writable
;<li>module: module-name <br>
;
;{;;; Status Attributes: These are from frame flags some of them pertain only to specialized classes.}
;<li>active: (member enabled, disabled, ...),
;<li>do-not-save: boolean,  {from do-not-save-in-kb)
;<li>transient: boolean,
;<li>class-is-user-defined: boolean, {from class-of-frame-is-user-defined)
;<li>do-not-strip-text: boolean,
;<li>savable-kb-workspace: boolean,
;<li>strip-text: boolean, <br>
;</ul>
;
;Attributes described in original document as item but not workspace: reconcile.
;<ul>
;<li>superior-workspace: workspace-or-none,              ; {from parent-frame}. Use workspace of item as well???
;<li>subworkspaces: ( kb-workspace * ), <br>
;; a new r/o attribute based on workspace:number-of-blocks-on-workspace 
;<li>number-of-subworkspaces: integer,
;</ul>
;
;Attributes described in original document as workspace: reconcile.
;<ul>
;<li>item-superior-to: item-or-none,     ; {from parent-of-subworkspace}
;<li>items-upon: ( [remembered-uuid: uuid, item: item] *), <br>
;; a new r/o attribute based on workspace:number-of-blocks-on-workspace
;<li>number-of-items-upon: integer, <br>
;<li>windows-showing-this-workspace ( [window: window, frame-transform: frame-transform-part] * ), ; from image-planes-this-is-on, 
;</ul>
;
;Also, the following should be added to all the classes which get icon-description.
;<ul>
;<li>ports: (connection-port *)
;</ul>
;
;")

(define-category-evaluator-interface (name-or-names
				       :access read-write)
    (or symbol
	(sequence symbol 0)
	(no-item))
  ((set-form (new-names))
   (cond ((evaluation-sequence-p new-names)
	  (let ((length (evaluation-sequence-length new-names)))
	    (cond 
	      ((=f length 1)
	       (evaluation-sequence-aref new-names 0))
	      ((>f length 0)
	       (let ((names
		       (with-evaluation-sequence-to-phrase-list-mapping
				    (new-names name)
				  name)))
		 ;; slot-value-compiler will strip this off
		 (phrase-push '\, names)))
	      (t
	       nil))))
	 (t
	  new-names)))
  ((get-form (slot-value))
   (cond ((consp slot-value)
	  (allocate-evaluation-sequence
	    (copy-list-using-eval-conses slot-value)))
	 (t
	  slot-value)))) ; guaranteed to be symbol or nil
	      

;; The following virtual attribute is replaced by the above category-eval-interface.
;; This is being done because we have no clear model of shadowing virtual
;; attributes of real attributes and we are not going to get one in the next
;; two weeks.  JED 10/2/97

;#+obsolete
;(def-virtual-attribute names
;    ((class block) (or symbol (sequence symbol) (no-item)) ()))
	      
(defmacro block-denotation-p (block)
  `(or (copy-for-slot-value (get-primary-name-for-frame-if-any ,block))
       (item-uuid ,block)))




;;; The alias for the slot named object-configuration is `item-configuration'.
;;; Thus, users view this slot as having the attribute name item-configuration.

;;; The slot named instance-configuration has no alias.  Thus, its attribute
;;; name is simply the same as its slot name, `instance-configuration'.

(define-slot-alias item-configuration object-configuration block)

(defmacro item-configuration (block)
  `(object-configuration ,block))

;; Note that the term "object" in object-configuration is not meant to imply
;; that it pertains to instances of OBJECT and its subclasses.  It was felt by
;; some, and by me most strongly among the developers, that the prefix would
;; mislead some users into believing that it did in fact pertain to the class
;; name.  While the prefix "object-" works well in some respects, I feel that it
;; is not essential, and that, on balance, it's best not to use it in this way
;; in the product at this time.  Thankfully, all interested parties (in
;; management, development, and documentation) have weighed in with either a
;; "lack of strong attachment" to using object-configuration, or a preference
;; for the final choice, configuration. (MHD 2/18/94)
;; 
;; --- UPDATE
;;
;; The one thing we agreed would make us backtrack was: if GUIDE had an
;; attribute named CONFIGURATION.  We thought it didn't, but it did.  Now what?
;; 
;; I'm all for name overloading, but it only makes sense to overload the same
;; name all the time.  Choosing to "overload" a new, different word is only
;; justified within a plan that calls for followthrough in all of the other
;; places where we chose a different word.
;;
;; Well, I still feel that ITEM is the term we've chosen to overload for such a
;; purpose, and not OBJECT.  (Recall that we have item-or-value, item-array,
;; item passing, etc., etc., as data types, class names, concepts, etc., in G2.)
;; While we can't echo the word that's getting so much hype these days in
;; marketing circles, OBJECT, we can echo the word that is important to the
;; product, ITEM.  It's true that we were forced by a historical compatibility
;; problem to give up on saying that users deal with "objects" in their KBs, and
;; instead must say that they deal with "items".
;;
;; In the choice between "item-configuration" and "object-configuration", you
;; have on the side of "item" that it basically makes sense in English, and
;; that, as its name implies, it applies to all items.  On the side of object,
;; you have that it not only makes sense in English, but perhaps sounds a bit
;; more natural (in a vacuum), and that it echoes the "hype" word, object.
;; Against it, you have that it doesn't apply only to objects, and that this is
;; contrary to most users' expectations, and contrary to our naming conventions
;; in general.  
;;
;; So, in summary, I've changed the alias name to item-configuration.
;;
;; (MHD 2/23/94)








(defun block-p-function (x) (block-p x)) ;; - ben (for mhd) 11/27/91

;;; Framep-function ... just for funcalling or forward-referencing.

(defun framep-function (x)
  (framep x))

;; MHD: for twrite in utilities1. (MHD 2/18/92)


;;; The function `is-block-p' is handy.

(defun is-block-p (thing)
  (and thing (framep thing) (block-p thing)))




(define-slot-alias options frame-flags)

(def-slot-putter cell-array (block new-cell-array? initializing?)
  (let ((current-block-of-dependent-frame block)
	(remove-compilations?
	  (and initializing?
	       loading-kb-p
	       (not (compilations-up-to-date-p block)))))
    (when remove-compilations?
      (update-frame-status block 'incomplete initializing?)
      (when new-cell-array?
	(remove-compilations-from-obsolete-cell-array new-cell-array?))
      (note-frame-with-compilation-removed block))
    (setf (cell-array block) new-cell-array?)
    (when new-cell-array?
      (rebuild-backpointers-of-g2-cell-array block new-cell-array?))
    new-cell-array?))

(def-slot-value-reclaimer cell-array (cell-array parent-frame)
  (when cell-array
    (delete-frame cell-array))
  (setf (cell-array parent-frame) nil))

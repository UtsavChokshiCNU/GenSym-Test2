; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module QUERIES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark David, Ben Hyde, Michael Levin, and Jim Allard






;;;; Intermodule References




(declare-forward-reference gsi-interface-p-function function) ; G2-GSI
(declare-forward-reference gsi-data-service-p-function function)            ; G2-GSI
(declare-forward-reference gsi-message-service-p-function function)         ; G2-GSI
(declare-forward-reference goto-frame-instance function)                    ; CONTROLS
(declare-forward-reference get-block-on-workspace-for-frame function)       ; CONTROLS
(declare-forward-reference embedded-rule-p function)                        ; CONTROLS
(declare-forward-reference editable-text-cell-p function)                   ; COMMANDS
(declare-forward-reference make-button-to-update-virtual-attributes-table function)
(declare-forward-reference get-values-for-t2-dialog function) ;VIEW-G2
(declare-forward-reference remove-dialog-info-from-ui-client-interface-dialog-list function) ;VIEW-G2
(declare-forward-reference update-dialog-for-t2 function) ;VIEW-G2
(declare-forward-reference export-graph-node function) ;EVENTS-G2






;;;; Queries


(add-grammar-rules
  '(
    (version-control
     ('use 'version 'control 'to)
     version-control)

    (the-change-log-entry ('the 'change 'log 'entry))

    (vc-slot-designation ;; already defined, not specific to version-control???
     ('of 'the system-or-user-defined-attribute-name 'of query-item-name)
     (3 5))

    (change-log-entry-spec
     (the-change-log-entry vc-slot-designation)
     (1 2))

    (change-log-tag symbol)

    (change-log-revision integer)

    (vc-timestamp
     ('as 'of frame-edit-timestamp)
     (timestamp 3))

    (vc-tag-id
     ('with 'tag change-log-tag)
     (tag 3))

    (vc-revision-id
     ('with 'revision change-log-revision)
     (revision 3))

    (change-log-specification
     vc-timestamp)

    (change-log-specification
     vc-tag-id)

    (change-log-specification
     vc-revision-id)

    (qualified-change-log-entry-spec
     (change-log-entry-spec change-log-specification)
     (1 2))

    (revert-the-text ('revert 'the 'text))

    (every-logged-attribute
     ('of 'every 'logged 'attribute 'of 'every 'item))

    (using-tag
     ('using 'tag change-log-tag)
     (tag 3))

    (rollback-spec
     ('to the-change-log-entry using-tag)
     3)

    (rollback-spec
     ('to the-change-log-entry vc-timestamp)
     3)

    (tag-every-attribute-in-module
     ('tag the-change-log-entry every-logged-attribute 'in 'module module-name)
     (tag-module 6))

    (revert-every-attribute-in-module
     (revert-the-text every-logged-attribute 'in 'module module-name)
     (revert-module 5))

    (vc-command
     ('tag change-log-entry-spec using-tag)
     (tag-entry 2 3))

    (vc-command
     ('tag change-log-entry-spec vc-timestamp using-tag)
     (tag-entry 2 4 3))

    (vc-command
     ('tag change-log-entry-spec vc-revision-id using-tag)
     (tag-entry 2 4 3))

    (vc-command
     (revert-the-text vc-slot-designation 'to the-change-log-entry
      change-log-specification)
     (revert-entry 2 5))

    (vc-command
     ('delete qualified-change-log-entry-spec)
     (delete-entry 2))

    (vc-command
     (tag-every-attribute-in-module using-tag)
     (tag-every-attribute 2 1))

    (vc-command
     (tag-every-attribute-in-module vc-timestamp using-tag)
     (tag-every-attribute 3 1 2))

    (vc-command
     (revert-every-attribute-in-module rollback-spec)
     (revert-every-attribute 2 1))

    (vc-command
     ('enable 'change 'logging 'on query-item-name)
     (enable-change-logging 5))

    (vc-command
     ('disable 'change 'logging 'on query-item-name)
     (disable-change-logging 5))

    (query-command
     (version-control vc-command)
     (query (1 . 2)))

    (the-diffs-between ('the 'differences 'between))

    (show-on-a-workspace-the-diffs-between
     (show-on-a-workspace the-diffs-between)
     (version-control show-diffs-on-a-workspace))

    (query-command
     (show-on-a-workspace-the-diffs-between qualified-change-log-entry-spec
      'and qualified-change-log-entry-spec)
     (query 1 2 4))

    (the-logged-changes ('the 'logged 'changes))

    (show-on-a-workspace-the-logged-changes
     (show-on-a-workspace the-logged-changes)
     (version-control show-logged-changes-on-a-workspace))

    (query-command
     (show-on-a-workspace-the-logged-changes 'of query-item-name)
     (query 1 3))

    (show-on-a-workspace-the-change-log-entry
     (show-on-a-workspace the-change-log-entry)
     (version-control show-change-log-entry-on-a-workspace))

    (query-command
     (show-on-a-workspace-the-change-log-entry vc-slot-designation
      change-log-specification)
     (query 1 2 3))

))



;; show on a workspace the differences between
;; the change log entry of the <attribute> of <item> [ as of <timestamp> | with revision <num> | with tag <tag> ]
;; and
;; the change log entry [ as of <timestamp> | with revision <num> | with tag <tag> ]


;;; The `queries' system within G2 is a facility for searching the knowledge
;;; base and displaying results of a search.  It contains a set of commands for
;;; presenting results and a language for setting up searches.

;;; This is the BNF grammar for the queries system.

;;; Query: (query-command query-retrieval)

;;; Query-command:
;;;   'write 'to 'a 'file
;;;   'show 'on 'a 'workspace
;;;   'go 'to
;;;   'replace
;;;   'highlight
;;;   'display 'a 'table 'of
;;;   'display 'a 'table 'columnwise 'of

;;; Query-retrieval:
;;;   Query-set

;;; Query-set:
;;;   ('every Classes {Query-restrictions})

;;; Query-restrictions:
;;;   Query-disjunct
;;;   (Query-disjunct 'or Query-restrictions)

;;; Query-disjunct:
;;;   Query-conjunct
;;;   (Query-conjunct 'and Query-disjunct)

;;; Query-conjunct:
;;;   Query-restriction
;;;   ('not Query-restrictions)

;;; Query-restriction:
;;;   ('containing symbol-or-string)
;;;   ('containing 'the 'word symbol-or-string)
;;;   ('containing 'the 'symbol symbol-or-string)
;;;   ('with 'notes)
;;;   ('where system-or-user-defined-attribute-name comparitor constant)
;;;   ('such 'that logical-expression)

;;; The `containing' restrictions will perform a search through the text of the
;;; slot values of the given items.  The `with notes' restriction will filter for
;;; those items with frame notes.  This restriction should be expanded when different
;;; types of notes are used on frames.  The `where' restriction gives a convenient
;;; way of filtering objects by a numeric or symbolic comparitor on a given
;;; attribute. The `such that' restriction allows the user to write an arbitrary
;;; logical expression as the filtering function.  Note that when using this
;;; restriction, designations of attributes of an object must be written in the
;;; same way as in rules, that is they must reference the attribute as a role of
;;; the bound object being searched across.  For example, a designation must be
;;; "the level of the mixer" rather than just "the level."

;;; This is the grammar as seen by users of the query facility.  Internally,
;;; query retrievals work as a non-atomic role.  Query restrictions translate
;;; into logical functions on their object and constant arguments which are then
;;; used by the query retrieval role server.  This will allow us to easily
;;; integrate these predicates and mapping abilities into generic rules if we so
;;; wish, or else into some kind of iterating form for procedures.

;;; The internal grammar form for queries is as follows, with words in capitals
;;; representing constant symbols and and words in lowercase representing
;;; grammar catagories.

;;; Query: (QUERY query-command query-designation)
;;;
;;; Query-designation :
;;;   name
;;;   (EVERY query-set)
;;;
;;; Query-set:
;;;   (QUERY-SET Classes)
;;;   (QUERY-SET-WITH-RESTRICTIONS (QUERY-SET Classes) query-restrictions)
;;;   (QUERY-SET-WITH-NAME class? name)
;;;
;;; Query-restrictions:
;;;   (AND {query-restrictions})
;;;   (OR {query-restrictions})
;;;   (NOT query-restrictions)
;;;   (CONTAINING designation symbol-or-string)
;;;   (CONTAINING-WORD designation symbol-or-string)
;;;   (CONTAINING-SYMBOL designation symbol-or-string)
;;;   (WITH-NOTES designation)
;;;   (WITH-STATUS designation frame-status)
;;;   (IN-MODULE designation frame-status)   ; new for 4.0
;;;   logical-expression
;;;
;;; Frame-status:
;;;   OK | BAD | INCOMPLETE | ACTIVE | INACTIVE | ENABLED | DISABLED




(add-grammar-rules
  '(;; Class hierarchy display

    (query-command
     show-on-a-workspace-the-class-hierarchy
     (query 1 item))

    (query-command
     (show-on-a-workspace-the-class-hierarchy 'of query-class)
     (query 1 3))

    (show-on-a-workspace-the-class-hierarchy
     (show-on-a-workspace the-class-hierarchy)
     show-class-hierarchy-on-a-workspace)

    (the-class-hierarchy ('the 'class 'hierarchy))


    (query-command
     show-on-a-workspace-the-procedure-invocation-hierarchy
     (query 1))

    (show-on-a-workspace-the-procedure-invocation-hierarchy
     (show-on-a-workspace the-procedure-invocation-hierarchy)
     show-procedure-invocation-hierarchy-on-a-workspace)

    (the-procedure-invocation-hierarchy ('the 'procedure 'invocation 'hierarchy))



    ;; Procedure calling hierarchy display (adding -pga, 12/4/95)

    (query-command
     show-on-a-workspace-the-procedure-calling-hierarchy
     (query 1 item))

    (query-command
     (show-on-a-workspace-the-procedure-calling-hierarchy 'of query-item-name) ; procedure-name
					; was class - procedure not defined?
     (query 1 3))

    (show-on-a-workspace-the-procedure-calling-hierarchy
     (show-on-a-workspace the-procedure-calling-hierarchy)
     show-procedure-calling-hierarchy-on-a-workspace)

    (the-procedure-calling-hierarchy ('the 'procedure 'calling 'hierarchy))


    ;; Procedure caller hierarchy display (adding -pga, 12/4/95)

    (query-command
     show-on-a-workspace-the-procedure-caller-hierarchy
     (query 1 item))

    (query-command
     (show-on-a-workspace-the-procedure-caller-hierarchy 'of query-item-name) ; procedure-name
					; was class - procedure not defined?
     (query 1 3))

    (show-on-a-workspace-the-procedure-caller-hierarchy
     (show-on-a-workspace the-procedure-caller-hierarchy)
     show-procedure-caller-hierarchy-on-a-workspace)

    (the-procedure-caller-hierarchy ('the 'procedure 'caller 'hierarchy))


    ;; Method hierarchy display

    (query-command
      (show-on-a-workspace-the-method-hierarchy 'of procedure-name)
      (query 1 3))

    (show-on-a-workspace-the-method-hierarchy
      (show-on-a-workspace the-method-hierarchy)
      show-method-hierarchy-on-a-workspace)

    (the-method-hierarchy ('the 'method 'hierarchy))




    ;; Method inheritance path display

    (query-command
     (show-on-a-workspace-the-method-inheritance-path 'for query-class)
     (query 1 3 3))

    (query-command
     (show-on-a-workspace-the-method-inheritance-path
      'for query-class 'and 'the 'method procedure-name)
     (query 1 3 7))

    (show-on-a-workspace-the-method-inheritance-path
     (show-on-a-workspace the-method-inheritance-path)
     show-method-inheritance-path-on-a-workspace)

    (the-method-inheritance-path ('the 'method 'inheritance 'path))




    ;; Workspace hierarchy display

    (query-command
      show-on-a-workspace-the-workspace-hierarchy
      (query 1 nil))

    (query-command
      (show-on-a-workspace-the-workspace-hierarchy 'of object-or-workspace-name)
      (query 1 3))

    (show-on-a-workspace-the-workspace-hierarchy
      (show-on-a-workspace 'the 'workspace 'hierarchy)
      show-workspace-hierarchy-on-a-workspace)

    (object-or-workspace-name object-name)
    (object-or-workspace-name workspace-name)


    ;; Module hierarchy display

    (query-command
      show-on-a-workspace-the-module-hierarchy
      (query 1 nil))

    (query-command
      (show-on-a-workspace-the-module-hierarchy 'of module-name)
      (query 1 3))

    (show-on-a-workspace-the-module-hierarchy
      (show-on-a-workspace 'the 'module 'hierarchy)
      show-module-hierarchy-on-a-workspace)


    ;; inspect command history display

    (query-command
      show-on-a-workspace-the-inspect-command-history
      (query 1 nil))
    (show-on-a-workspace-the-inspect-command-history
      (show-on-a-workspace 'the 'inspect 'command 'history)
      show-inspect-command-history-on-a-workspace)


    ;; Module consistency-check display

    (query-command check-for-consistent-modularization (query 1 nil))

    (check-for-consistent-modularization
     ('check 'for 'consistent 'modularization)
     check-for-consistent-modularization)



    ;; Class hierarchy output to file

    (query-command
      write-to-file-the-class-hierarchy
      (query 1 item))

    (query-command
      (write-to-file-the-class-hierarchy 'of query-class)
      (query 1 3))

    (write-to-file-the-class-hierarchy
      ('write 'to 'the 'file file-name 'the 'class 'hierarchy)
      (write-class-hierarchy-to-file 5))


;    ;; Procedure reference hierarchy output to file -pga, 12/4/95
;
;    (query-command
;     write-to-file-the-procedure-reference-hierarchy
;     (query 1 item))
;
;    (query-command
;     (write-to-file-the-procedure-reference-hierarchy 'of procedure-name)
;     (query 1 3))
;
;    (write-to-file-the-procedure-reference-hierarchy
;     ('write 'to 'the 'file file-name 'the 'procedure 'reference 'hierarchy)
;     (write-procedure-reference-hierarchy-to-file 5))


    ;; The original definitions for query-command:

    (query-command (query-verb query-designations) (query 1 2))
    (query-command (query-verb the+query-attributes+of query-designations) (query 1 3 2))
    ;; query-verb, and the+query+attributes+of are always wrapped in a source-position

    (the+query-attributes+of
      ('the query-attributes 'of)
      2 cdr-and-reduce-noting-source-position)

    (query-verb ('write 'to 'the 'file file-name)
		(write-to-a-file 5)
		reduce-noting-source-position)
    (query-verb show-on-a-workspace)
    (query-verb display-a-table)
    (query-verb 'recompile
		1
		reduce-noting-source-position)

    (show-on-a-workspace			; later, just "show"!
      ('show 'on 'a 'workspace)
      show-on-a-workspace
      reduce-noting-source-position)

    (display-a-table
      ('display 'a 'table 'of)
      display-a-table
      reduce-noting-source-position)
    (display-a-table
      ('display 'a 'table 'columnwise 'of)
      display-a-table-columnwise
      reduce-noting-source-position)

    (query-verb ('replace query-symbol-or-string 'with query-symbol-or-string 'in)
		(replace non-word 2 4)
		not-runtime-or-embedded
		reduce-noting-source-position)
    (query-verb ('replace 'the 'word query-symbol-or-string 'with
		 query-symbol-or-string 'in)
		(replace word 4 6)
		not-runtime-or-embedded
		reduce-noting-source-position)
    (query-verb ('replace 'the 'symbol query-symbol-or-string 'with
		 query-symbol-or-string 'in)
		(replace symbol 4 6)
		not-runtime-or-embedded
		reduce-noting-source-position)

    (query-verb ('highlight query-symbol-or-string 'in)
		(highlight non-word 2)
		reduce-noting-source-position)
    (query-verb ('highlight 'the 'word query-symbol-or-string 'in)
		(highlight word 4)
		reduce-noting-source-position)
    (query-verb ('highlight 'the 'symbol query-symbol-or-string 'in)
		(highlight symbol 4)
		reduce-noting-source-position)

    (query-symbol-or-string query-symbol)	; Note: order important
    (query-symbol-or-string whole-string)	;   here due to bug; notes
						;   on bug follow:


    ;; Notes on a parser bug for LH to look at eventually:   (MHD 6/14/90)
;    (query-verb ('foo query-symbol-or-string)
;                (highlight word 2))
;    (query-verb ('bar whole-string)
;                (highlight word 2))
;    (query-verb ('bar query-symbol)
;                (highlight word 2))
;    (query-verb ('baz xxx)                      ; works (w/ integer not whole-string)
;                (highlight word 2))
;    (query-verb ('blech yyy)                    ; loses same way (w/string not whole-string)
;                (highlight word 2))
;    (query-verb ('boob zzz)                     ; works (/ query-symbol, then whole-string,
;                                                ;   then integer) -- order matters?
;                (highlight word 2))

;    (query-verb ('beeb aaa)			; eureka! transposing order of rules
;                (highlight word 2))		;   x -> query-symbol, x -> whole-string
;						;   works around the problem
;    (aaa query-symbol)
;    (aaa whole-string)

;    (zzz query-symbol)
;    (zzz whole-string)
;    (zzz integer)

;    (yyy string)
;    (yyy query-symbol)

;    (xxx integer)
;    (xxx query-symbol)

;    (query-symbol-or-string whole-string)
;    (query-symbol-or-string query-symbol)

    ))

(defun cdr-and-reduce-noting-source-position (parse)
  (reduce-noting-source-position (cdr parse)))

(add-grammar-rules-for-list
  'query-attributes 'system-or-user-defined-attribute-name '\, 'and)

;; The query-symbol-or-string category is used to accept tokens for
;; the highlight and replace inspect options.  The query-symbol category
;; should receive all of the symbol containing directories that we can think
;; of.  We should consider whether we want the menus to be shown when in
;; the non-word case of the replace and highlight.  -jra & lh 6/27/89


(defun not-runtime-or-embedded (parse)
  (if #-pre-g2-v5-licensing
      t
      #+pre-g2-v5-licensing
      (and (not (runtime-option-authorized-p))
	   (not (embedded-option-authorized-p)))
      parse
      (values bad-phrase 'cannot-replace-in-runtime-or-embedded-g2)))

(declare-grammar-transform-can-return-bad-phrase not-runtime-or-embedded)



(add-grammar-rules
   `((query-symbol symbol)
     (query-symbol item-name)
     (query-symbol class)
     (query-symbol attribute-name)
     (query-symbol function-name)
     (query-symbol procedure-name)
     (query-symbol method-declaration-name)))


(add-grammar-rules
  '((query-class class)
    (query-class 'item)
    (query-class 'object)
    (query-class 'variable-or-parameter)
    (query-class 'procedure)
    (query-class 'rule)
    (query-class 'kb-workspace)
    (query-class 'message)
    (query-class 'g2-window)))

;; Problem: If, e.g., you type in "IT" you might see ITEM and ITEM-LIST in the
;; editor's right-hand-side directory of names and ITEM also on the left-hand-
;; side query-class grammar!
;;
;; To do: keep directory of names facility from putting up, e.g., ITEM twice
;; when it is explicitly specified as well as an instance of a name directory!
;; (MHD 1/4/91)


;; No, this is too much.  Go back to hand picking!  Hand-picked set
;; above -- needs review!  (MHD 6/14/90)
;; ;; Generate grammar for query-symbol:
;;
;; (add-grammar-rules
;;   `((query-symbol symbol)
;;     (query-symbol attribute-name)
;;     (query-symbol system-defined-attribute-name)
;;     (query-symbol function-name)
;;     ,@(loop for var in '(classes-and-directory-categories-for-frame-names
;;                           classes-and-directory-categories-for-classes)
;;             nconc
;;               (loop for (class . category)
;;                         in (symbol-value var)
;;                     collect `(query-symbol ,category)))))

;; The above replaces the following three:   (MHD 6/7/90)
;(query-symbol-or-string object-name)
;(query-symbol-or-string class)
;(query-symbol-or-string attribute-name)


(add-grammar-rules
  '(
    (query-command (query-verb-go-to query-item-name)
     (query 1 2))
    (query-verb-go-to ('go 'to) visit reduce-noting-source-position)

    (query-item-name item-name)
    (query-item-name (class '\:\: item-name) (class-qualified-method 1 3)
     convert-class-qualified-list-to-keyword-symbol)
    ;; Visit is defined for single names only at the moment. -jra 10/26/87

    ;; query-designation:
    ;; OLD FEATURE: You used to be able make query-designations as list, using semicolon

    (query-designations new-query-designation)
    ;; Every reducition leading to query-designation looks like:
    ;;     (source-position (g2-lambda ((<arg> (class <class>)) <predicate>)) . # )
    ;;     Except! the reduction from item-name which looks like <name>

    (new-query-designation query-item-name)
    ;; What we wish we could write but the parse won't let us.
    ;;			   1
    ;;			   ((every-instance-such-that
    ;;			      1
    ;;			      (g2-lambda (item (class item))
    ;;					 (and (has-a-name (the item))
    ;;					      (is (the (role-server name) (the item)) '1))))
    ;;			    :source-text)
    ;;			   reduce-noting-source-position)
    (new-query-designation new-query-designation-via-name)
    (new-query-designation new-query-designation-using-every)
    (new-query-designation-via-name ('the query-class 'named item-name)
				    ((every-instance-such-that
				       2 
				       (g2-lambda ((:temporary-name (class 2)))
						  (and (has-a-name :argument-1)
						       (is (the (role-server name) :argument-1) '4))))
				     . :source-text)
				    reduce-noting-source-position)
    (new-query-designation-using-every ('every query-class)
				       ((every-instance-such-that
					  2
					  (g2-lambda ((:temporary-name (class 2))) true))
					. :source-text)
				       reduce-noting-source-position)
    (new-query-designation-using-every ('every query-class query-restrictions)
				       ((every-instance-such-that
					  2
					  (g2-lambda ((:temporary-name (class 2))) 3))
					. :source-text)
				       reduce-noting-source-position)
    (new-query-designation-using-every ('every query-class local-name-in-inspect query-restrictions)
				       ((every-instance-such-that
					  2
					  (g2-lambda ((3 (class 2))) 4))
					. :source-text)
				       reduce-noting-source-position)
    (local-name-in-inspect local-name 1 reject-inspect-keywords-as-local-names)))

;; There are two things making the above more complex than usual.  First the
;; parse has forms that record the source position of some tokens embedded in
;; it.  This provides the slot value compiler an opportunity to snarf the
;; original source text of the query-designation out of the editor state.  The
;; compiler then discards the source position information.

;; Secondly the parses have holes where information can be filled.  This info
;; is generally encountered later in the parsing process.  The holes are filled
;; by the slot value compiler.  The holes are marked with keywords.

;; The grammar category user-instantiable-kb-class is used in file FILTERS.

;; Note 1: User-instantiable-kb-class was replaced with class above.  Its
;; main feature was that it included "pseudo classes" like DISPLAY and FREE-
;; TEXT and DEFINITION (but not WORKSPACE).  Thus, it held out the promise
;; of bridging the gap between the class hierarchy presented by the menus
;; (e.g. New Workspace, New Free Text, New Display) and the "real" item
;; class hierarchy.  However, it was not working at the time of the change;
;; i.e. "show on a workspace every free-text|display" always found
;; nothing, and "show on a workspace every definition" only found instances
;; of the class DEFINITION, not procedures, formulas, etc.  Furthermore,
;; as the note above states, user-instantiable-kb-class is used in FILTERS
;; as the grammar for ITEM-NAME -- poor name which will have to be changed! --
;; but those restrictions did not work either.  Finally, having a preterminal
;; with so many instances is a pain, and really can only have been rationalized
;; before the advent of name directories.  Fortunately, we have a name directory
;; which serves our purpose: CLASS.  We are therefore replacing occurances
;; of user-instantiable-kb-class in the right-hand sides of grammar rules
;; with class. (MHD 6/6/90)

;; Note 2: One could consider now adding a few special case pseudoclasses
;; like DISPLAY, FREE-TEXT, DEFINITION.  A better alternative, I feel, would
;; be to quit allowing menus to present an alternative hierarchy! (MHD 6/6/90)


(add-grammar-rules
  '((query-restrictions query-disjunct)
    (query-restrictions
      (query-disjunct 'or query-restrictions)
      (or 1 3) simplify-associative-operation)

    (query-disjunct query-conjunct)
    (query-disjunct
      (query-conjunct 'and query-disjunct)
      (and 1 3) simplify-associative-operation)

    (query-conjunct query-restriction)
    (query-conjunct ('not query-restriction) (not 2))

    (query-restriction ( '\( query-restrictions '\) ) 2)
    (query-restriction ('such 'that unique-logical-expression) 3)))




;;; The following grammar defines operations that can be performed on items
;;; being filtered with query restrictions.  They are implemented as
;;; def-evaluators so that a datum-evaluate on these operations with the object
;;; being filtered bound to its class name will return a logical value.  The
;;; operations defined are containing, containing-word, containing-symbol,
;;; and with-notes.

(add-grammar-rules
  '(
    ;; Containing ...
    (query-restriction ('containing              whole-string) (containing      :argument-1  2))
    (query-restriction ('containing              query-symbol) (containing      :argument-1 '2))
    (query-restriction ('containing 'the 'word   whole-string) (containing-word :argument-1  4))
    (query-restriction ('containing 'the 'word   query-symbol) (containing-word :argument-1 '4))
    ;; The next two had been using the containing-word evaluator -- the original
    ;; documentation and design here called for for it to use containing-symbol,
    ;; an evaluator.  Now fixed.  Note: this did not affect "highlight ..."
    ;; inspect commands, only the "show ... containing ..."  (MHD 8/1/94)
    (query-restriction ('containing 'the 'symbol whole-string) (containing-symbol :argument-1  4))
    (query-restriction ('containing 'the 'symbol query-symbol) (containing-symbol :argument-1 '4))

    ;; With notes, and with status...
    (query-restriction ('with 'notes)                    (with-notes  :argument-1   ))
    (query-restriction ('whose 'status 'is frame-status) (with-status :argument-1 '4))
    (frame-status 'ok)
    (frame-status 'bad)
    (frame-status 'incomplete)
    (frame-status 'active)
    (frame-status 'inactive)
    (frame-status 'enabled)
    (frame-status 'disabled)

    ;; assigned to module <module/symbol>
    ;; assigned to the module hierarchy of <module/symbol>
    (query-restriction ('assigned 'to 'module module-name)
     (assigned-to-module :argument-1 '4 false))
    (query-restriction ('assigned 'to 'the 'hierarchy 'of 'module module-name)
     (assigned-to-module :argument-1 '7 true))

    ;; with changes logged [<log-restriction>]
    ;; log-restriction => {since <date>} | {by <user>}
    (query-restriction ('with 'changes 'logged)
     (with-changes-logged-2 :argument-1 false false false))
    (query-restriction ('with 'changes 'logged
			'before date-as-edit-timestamp)
     (with-changes-logged-2 :argument-1 5 false false))
    (query-restriction ('with 'changes 'logged
			'after date-as-edit-timestamp)
     (with-changes-logged-2 :argument-1 false 5 false))
    (query-restriction ('with 'changes 'logged
			'before date-as-edit-timestamp 'and 'after date-as-edit-timestamp)
     (with-changes-logged-2 :argument-1 5 8 false))
    (query-restriction ('with 'changes 'logged 'by author)
     (with-changes-logged-2 :argument-1 false false '5))
    (query-restriction ('with 'changes 'logged 'by author
			'before date-as-edit-timestamp)
     (with-changes-logged-2 :argument-1 7 false 5))
    (query-restriction ('with 'changes 'logged 'by author
			'after date-as-edit-timestamp)
     (with-changes-logged-2 :argument-1 false 7 5))
    (query-restriction ('with 'changes 'logged 'by author
			'before date-as-edit-timestamp 'and 'after date-as-edit-timestamp)
     (with-changes-logged-2 :argument-1 7 10 5))

    (query-restriction ('with 'unsaved 'changes)
     (with-unsaved-changes :argument-1))

    ;; Where <attr> ...
    (query-restriction ('where system-or-user-defined-attribute-name fuzzy-comparator constant)
		       (3 (the 2 (the :class)) 4))
    (query-restriction ('where system-or-user-defined-attribute-name '>= constant)
		       (>= (the 2 (the :class)) 4))
    (query-restriction ('where system-or-user-defined-attribute-name '<= constant)
		       (<= (the 2 (the :class)) 4))
    (query-restriction ('where system-or-user-defined-attribute-name 'is symbol)
		       (4 (is (the 2 (the :class)) '4)) where-is-symbol-cannot-be-true-or-false)
    (query-restriction ('where system-or-user-defined-attribute-name 'is 'not symbol)
		       (5 (not (is (the 2 (the :class)) '5))) where-is-symbol-cannot-be-true-or-false)
    (query-restriction ('where system-or-user-defined-attribute-name 'is 'true)
		       (the 2 (the :class)))
    (query-restriction ('where attribute-name 'is 'false)
		       (false (the 2 (the :class))))

    ;; In the catagory, which has focal class, which has focal object
    (query-restriction ('in 'the 'category rule-category-name)
		       (and (is (the class :argument-1) 'rule)
			    (in-the-category :argument-1 '4)))
    (query-restriction ('which 'has 'the 'focal 'class focal-class)
		       (and (is (the class :argument-1) 'rule)
			    (which-has-the-focal-class :argument-1 '6)))
    (query-restriction ('which 'has 'the 'focal 'object focal-object-name)
		       (and (is (the class :argument-1) 'rule)
			    (which-has-the-focal-object :argument-1 '6)))
    (focal-class unreserved-symbol)
    (focal-object-name unreserved-symbol)
    (workspace-name unreserved-symbol)

    ;; found on the workspace
    (query-restriction ('found 'on 'the 'workspace workspace-name)
		       (and
			 (exists (the (role-server workspace kb-workspace) :argument-1))
			 (same-as (the (role-server workspace kb-workspace) :argument-1) 5)))

    ))

(defun where-is-symbol-cannot-be-true-or-false (parsed-where)
  (gensym-dstruct-bind ((symbol? actual-parse) parsed-where)
    (if (or (eq symbol? 'true)
	    (eq symbol? 'false))
	bad-phrase
	actual-parse)))

(declare-grammar-transform-can-return-bad-phrase where-is-symbol-cannot-be-true-or-false)




;;; Reject-inspect-keywords-as-local-names takes a parse of the rule
;;; local-name-in-inspect, which gives a symbol, and rejects it if it
;;; is one of the following Inspect keywords:
;;;
;;;   found
;;;   where
;;;   containing
;;;   which
;;;   whose
;;;   assigned  (added 11/12/93 -- MHD)
;;;
;;; Note that the following would need to be added if they were not "reserved
;;; words" already:
;;;
;;;   in
;;;   such
;;;   with
;;;
;;; Note that \( also need not be considered because it is parsed as a
;;; punctuation symbol.

(defun reject-inspect-keywords-as-local-names (parse-of-local-name)
  (cond
    ((member parse-of-local-name '(found where containing which whose assigned))
     bad-phrase)
    (t parse-of-local-name)))

(declare-grammar-transform-can-return-bad-phrase reject-inspect-keywords-as-local-names)

;; Consider this for local-name in the main grammar! (MHD)






;;;; Query Evaluator Functions


;;; The following functions are defined for restriction predicates in query
;;; retrieval designations.

;;; The evaluator `containing' is used to check whether or not the texts
;;; of user visible slot values contain the passed string or symbol.  The
;;; evaluator `containing-word' does the same, except that it observes word
;;; boundaries during the search.  The evaluator `containing-symbol' does the
;;; same, except that it observes symbol boundaries during the search.

;;; Several versions of the containing evaluators have been written.  This one
;;; should now be a true version of this facility, which can arbitrarily search
;;; any frame in the system for string in the printed representation of its slot
;;; value.

;;; The evaluators (def-funcalled-evaluator forms) that call back to this
;;; section are defined in the module STACK-EVAL, section "Query Evaluators".
;;; Code therein calls back to this section in this module.




;;; `Do-query-evaluation-for-containing' ...

(defun do-query-evaluation-for-containing
       (item what-to-look-for observance-of-word-boundary?)
  (loop with gathering-normally-editable-slots-for-search? = t
	;; special, to defeat product authorization restrictions,
	;; e.g., no editing of the text of procedures (MHD 5/30/95)

	with found? = nil
	with string-to-look-for
	  = (if (symbolp what-to-look-for)
		(copy-symbol-name-parsably what-to-look-for nil)
		what-to-look-for)
	with slot-texts
	  = (make-attributes-table-description item nil nil '(class))
	for (nil nil text-representation-of-slot-value) in slot-texts
	when (find-string-in-text-for-inspect
	       string-to-look-for text-representation-of-slot-value
	       observance-of-word-boundary?)
	  do (setq found? t)
	     (loop-finish)
	finally
	  (if (not (eq string-to-look-for what-to-look-for))
	      (reclaim-text-string string-to-look-for))
	  (reclaim-slot-value slot-texts)
	  (return found?)))




;;; `Do-query-evaluation-for-with-status' ...

(defun do-query-evaluation-for-with-status (item status)
  (case status
    ((ok bad incomplete)
     (let* ((goal-internal-status (if (eq status 'ok) nil status))
	    (frame-status-and-notes (frame-status-and-notes item)))
       (eq goal-internal-status
	   (if (atom frame-status-and-notes)
	       frame-status-and-notes
	       (car frame-status-and-notes)))))
    ((active inactive)
     (eq (if (or
	       (ancestor-not-activatable-p item)
	       (and (or system-is-running system-has-paused)
		    (not (frame-of-class-p item 'simulation-subtable))
		    (not (active-p item))))
	     'inactive
	     'active)
	 status))
    ((enabled disabled)
     (eq (if (manually-disabled-p item)
	     'disabled
	     'enabled)
	 status))))




;;; `Do-query-evaluation-for-rule-restriction' is currently called with slot-name
;;; being one of the following (system-defined) slots:
;;;
;;;   rule-categories
;;;   focal-classes
;;;   focal-objects
;;;
;;; Each of these slots are present in a rule, and each holds a list of symbols.
;;; This function returns true if item is a rule, and name is present the
;;; designated list of symbols.

(defun do-query-evaluation-for-rule-restriction
    (item name slot-name &optional class-qualifier?)
  (and (frame-of-class-p item 'rule)
       (memq name			; slots contain lists of names
	     (get-slot-value item slot-name class-qualifier?))))








;; No longer in 3.0 (MHD 10/28/91)
;;
;; ;;; The evaluator `found-on-the-workspace' returns the three values truth, NEVER,
;; ;;; and TRUTH-VALUE if the designated item is a subblock of the designated
;; ;;; kb workspace; otherwise, it returns the three values nil, nil, and nil.
;;
;; ;;; Note that the connections are never subblocks of any workspace.  Note that
;; ;;; message boards are not kb workspaces.
;;
;;
;; #+old-evaluators
;; (defun do-query-evaluation-for-found-on-the-workspace (item name)
;;   (let ((workspace?
;;           (cond
;;             ((frame-of-class-p item 'workspace)
;;              nil)
;;             ((frame-of-class-p item 'connection)
;;              (let ((output-end-object?
;;                      (output-end-object
;;                        (connection-for-this-connection-frame item))))
;;                (if output-end-object?           ; maybe unnec.!
;;                    (get-workspace-if-any output-end-object?))))
;;             (t
;;              (get-workspace-if-any item)))))
;;     (and workspace?
;;          (item-workspace-p workspace?)
;;          (name-for-frame-p name workspace?))))
;;
;; ;; Probably, this should call a subfunction, item-on-workspace-of-name-p!




;;; The function `make-full-pathname' ... assumes that its file-name argument is
;;; in the Gensym character set, as opposed to ASCII (e.g., it assumes
;;; backslashes and tildes are escaped).  It may be either a string or a symbol.
;;; If a symbol, its symbol-name (print name) is used, and must also be in the
;;; Gensym character set.  The arg, when a string, is not reclaimed.

(defun-allowing-unwind make-full-pathname (file-name-string-or-symbol)
  (protected-let* ((name-string
		     (if (symbolp file-name-string-or-symbol)
			 (copy-symbol-name file-name-string-or-symbol nil)
			 (copy-text-string file-name-string-or-symbol))
		     (reclaim-text-string name-string))
		   (ascii-file-name
		     (convert-text-string-to-ascii-filename-as-much-as-possible
		       name-string)
		     (reclaim-text-string ascii-file-name))
		   (default-full-pathname
		     (gensym-make-pathname
		       :type     #w"qp"
		       :version  :newest
		       :defaults (or current-kb-pathname?
				     process-specific-system-pathname))
		     (reclaim-gensym-pathname default-full-pathname))
		   (merged-pathname
		     (gensym-merge-pathnames ascii-file-name
					     default-full-pathname))
		   (merged-name-string
		     (gensym-namestring-as-text-string merged-pathname)
		     (reclaim-text-string merged-name-string)))
    ;; The following does ~-expansion into its first argument. - jpg 12/17/02
    (augment-pathname-from-file-system
      merged-pathname merged-name-string)
    merged-pathname))




;;; `Open-file-for-search-results' ... returns nil if it cannot open the file
;;; named by namestring; otherwise, it returns a gensym stream, writes the
;;; inspect file header, using inspect-command? for that purpose if provided,
;;; and returns the open stream.  This function assumes its namestring argument
;;; is in the ASCII character set, as opposed to the Gensym character set (e.g.,
;;; it assumes backslashes and tildes are not escaped).

(defun-allowing-unwind open-file-for-search-results
                       (namestring inspect-command?)
  (with-dynamic-creation
    (handling-file-errors
      (let ((file-stream-for-printing-search-results?
              (g2-stream-open-for-output namestring)))
        (if file-stream-for-printing-search-results?
            (write-inspect-file-header
              file-stream-for-printing-search-results?
              inspect-command?))
        file-stream-for-printing-search-results?))))




;;; `print-frame-to-file-for-search-results' ...

(defun-allowing-unwind print-frame-to-file-for-search-results
    (file-stream-for-printing-search-results frame slots-to-include?)
  (with-dynamic-creation
    (handling-file-errors
      (print-frame
        frame slots-to-include? file-stream-for-printing-search-results
        (or
          (if (text-conversion-style language-parameters)
              (get-text-conversion-style-structure-per-name
                (text-conversion-style language-parameters)))
          default-text-conversion-style)))))




;;; `Close-file-for-search-results' ...

(defun-allowing-unwind close-file-for-search-results
                       (file-stream-for-printing-search-results)
  (with-dynamic-creation
    (handling-file-errors
      (g2-stream-close file-stream-for-printing-search-results))))








;;; The function `write-inspect-file-header' writes the header information
;;; for a "write to the file" command to file-stream-for-printing-search-results,
;;; which should be a G2 stream.

;;; The header information includes the name of the KB name, the output
;;; file name, and the date and time written.  In addition, if query-
;;; command? is specified, the inspect command which produced the file is
;;; also written.

(defun write-inspect-file-header (file-stream-for-printing-search-results
                                   &optional query-command?)
  (let* ((output-file-namestring
           (gensym-namestring-as-text-string
             (gensym-truename file-stream-for-printing-search-results)))
         (transcode-text-conversion-style
           (or
             (if (text-conversion-style language-parameters)
                 (get-text-conversion-style-structure-per-name
                   (text-conversion-style language-parameters)))
             default-text-conversion-style)))
    (loop with initial-header-lines
           = (slot-value-list
               (copy-constant-wide-string
                 #w"** Gensym G2 Knowledge Base Inspection Output")
               (tformat-text-string
                 "** From KB:    ~a"                ; 2nd Column in character column 15
                 (or (if current-kb-pathname?
                         (gensym-namestring current-kb-pathname?))
                     "An unsaved knowledge base."))
               (tformat-text-string
                 "** File:       ~a"
                 output-file-namestring)
               (twith-output-to-text-string
                 (tformat "** Written at: ")
                 (multiple-value-bind (second minute hour day month year)
                     (get-decoded-real-time)
                   (print-decoded-time second minute hour day month year)))
               (copy-constant-wide-string #w"")
               (copy-constant-wide-string #w"")
               (copy-constant-wide-string #w""))
          for line in initial-header-lines
          do (export-and-emit-text-line
               line
               transcode-text-conversion-style
               file-stream-for-printing-search-results)
          finally (reclaim-slot-value initial-header-lines))
    (when query-command?
      (export-and-emit-text-line
        #w"** Command: "
        transcode-text-conversion-style
        file-stream-for-printing-search-results)
      (print-frame                                ; prints the command
        query-command?
        '(box-translation-and-text)
        file-stream-for-printing-search-results
        transcode-text-conversion-style))
    (export-and-emit-text-line
      #w""
      transcode-text-conversion-style
      file-stream-for-printing-search-results)
    (export-and-emit-text-line
      #w"** Results follow this line:"
      transcode-text-conversion-style
      file-stream-for-printing-search-results)))







;;; The class `inspect-command' is defined to provide the hook into processing
;;; for query retrievals.  An instance of inspect-command is created when the
;;; user selects "Inspect" from the main menu.

;;; The slot value compiler for inspect-command is used to provide the jumping
;;; off point for the command to be executed.  This is a bit of a kludge and
;;; should be cleaned up into a more general facility for commands which doesn't
;;; misuse the slot value compiler.

(def-class (inspect-command command)
  (box-translation-and-text nil (type query-command text))
  (search-state-for-inspect-command? nil system vector-slot)
  (frame-serial-number-for-inspect-command-search-state?
    nil system vector-slot)
  (run-command-invisibly-p nil system vector-slot)
  (run-command-to-completion-p nil system vector-slot)
  (run-command-remotely-p nil system vector-slot))

(def-class (inspect-history command)
  (box-translation-and-text nil (type query-command text)))

(def-slot-value-reclaimer frame-serial-number-for-inspect-command-search-state?
    (value block)
  (reclaim-frame-serial-number value)
  (setf (frame-serial-number-for-inspect-command-search-state? block) nil))

(def-spot inspect-command-spot
    :slots nil
    :include text-box-spot
    :enclosing-spot-type spot
    :innermost-spot-p t  ;; Not right, but ok for now.
    :abstract-type nil
    :type-of-frame-represented inspect-command)

(def-class-method generate-spot (inspect-command mouse-pointer)
  (generate-text-box-spot
    inspect-command mouse-pointer (make-inspect-command-spot)))

(def-slot-value-compiler query-command (query-command-parse-result)
  (rewrite-query-command-parse-into-nicer-format query-command-parse-result))

(def-system-variable temporary-name-number-1 queries
  (:funcall gentemp "TEMPORARY-NAME"))
(def-system-variable temporary-name-number-2 queries
  (:funcall gentemp "TEMPORARY-NAME"))




;;; `Rewrite-query-command-parse-into-new-format' makes the parse we wish we had
;;; actually made for this command the user typed.  It also snarfs the source
;;; text for the filter (if any) and it spreads the class over the parse.

(defun rewrite-query-command-parse-into-nicer-format
       (query-command-parse-result)
  (let ((query-command
          (let ((x (second query-command-parse-result)))
            (cond
              ;; e.g. (query show-on-a-workspace-the-workspace-hierarcy...)
              ((symbolp x)
               x)
              ;; e.g. (query (cmd ...) ...) This case doesn't arise.
              ((not (eq (car x) 'source-position))
               (car x))
              ;; e.g. (query (source-position show-on-a-workspace) ...)
              ((symbolp (second x))
               (second x))
              ;; e.g. (query (source-position (replace ...) ...))
              (t
               (car (second x)))))))
    (cond
      ((not (memq query-command '(highlight replace show-on-a-workspace
                                            display-a-table
                                            display-a-table-columnwise
                                            visit write-to-a-file
                                            recompile)))
       query-command-parse-result)
      (T
       ;; This almost looks like
       ;;
       ;;    (query <command-w-srcpos> <filter-w-srcpos> [<attr-arg])
       ;;
       ;; where <foo-w-srcpos> looks like
       ;;
       ;;    (source-position <foo> . #)
       ;;
       ;; except in the situation where the filter is merely an item name,
       ;; so first we normalize the name case to look like above.
       ;; i.e.: show on a workspace naked-name

       ;; We also land in this god-forsaken code when we are working with class
       ;; qualified method names, e.g. show on a workspace uffda::fromage -jra
       ;; 5/31/95
       (let ((name (third query-command-parse-result))
             normalized-name)
         (cond
           ((and (consp name)
                 (eq (car-of-cons name) 'class-qualified-method))
            (setf normalized-name
                  (copy-for-phrase
                    '(source-position
                      ((every-instance-such-that
                        :name
                        (g2-lambda ((:temporary-name (class method)))
                                   true)
                        . :source-text)))))
            (nsubst name :name normalized-name)
            (setf (third query-command-parse-result) normalized-name))
           ((symbolp name)
            (setf normalized-name
                  (copy-for-phrase
                    '(source-position
                       ((every-instance-such-that
                          item
                          (g2-lambda ((:temporary-name (class item)))
                                     (or
                                       (there-exists-literal
                                         (((role-server name) . :temporary-name-2) :argument-1)
                                         (= :temporary-name-2 ':name))
                                       (g2-inspect-internal-name-for-debugging-p :argument-1 ':name))))
                        . :source-text))))
            (nsubst name :name normalized-name)
            (setf (third query-command-parse-result) normalized-name))))

       ;; This now looks like this: (query <command-w-srcpos> <filter-w-srcpos> [<attr-arg])
       ;;    where <FOO-w-srcpos> looks like (source-position <FOO> . # )
       (gensym-dstruct-bind ((nil
                              (nil query-command-symbol-or-form . start-filter-source-position)
                              (nil query-domain . end-filter-source-position)
                              . optional-attribute-argument)
                            query-command-parse-result)
         (let (attribute-argument?
               (query-command (if (symbolp query-command-symbol-or-form)
                                  query-command-symbol-or-form
                                  (car query-command-symbol-or-form))))
           (cond
             ((not (memq query-command '(highlight replace show-on-a-workspace
                                                   display-a-table display-a-table-columnwise
                                                   visit write-to-a-file
                                                   recompile)))
              (strip-source-positions query-command-parse-result))
             (t
              ;; We want to do some rewrites around the domain.
              ;; A. snarf the original source text for that argument.
              ;; B. normalize the argument into a predicate.

              ;; Step A: Reset the starting position if we had an attributes argument.
              (when optional-attribute-argument
                (destructuring-setq
                  ((nil attribute-argument? . start-filter-source-position))
                  optional-attribute-argument))

              ;; Snarf the source from the editor, and the class from
              ;; the parse.
              (let* ((source-text
                       (text-string-from-current-source
                         start-filter-source-position
                         end-filter-source-position))
                     phrase-text-string)
                ;; Query domain now looks like:
                ;;   ((every-class-instance-such-that <class>
                ;;       (g2-lambda ((<argument-1> (class :class)))
                ;;            <predicate>) [<attr-arg>]) . <source-text> )
                ;; and we want to backpatch some things.
                (setq phrase-text-string (copy-for-phrase source-text))
                ;; now we get rid of the old one
                (when (text-string-p source-text)
                  (reclaim-text-string source-text))
                (gensym-dstruct-bind (((nil class (nil ((argument-1 . nil)) . nil) . nil) . nil) query-domain)
                  ;; Stuff the source and class into the parse.
                  (nsubst phrase-text-string :source-text query-domain)
                  (nsubst class :class query-domain)
                  (nsubst argument-1 :argument-1 query-domain)
                  (nsubst temporary-name-number-1 :temporary-name query-domain)
                  (nsubst temporary-name-number-2 :temporary-name-2 query-domain)
                  ;; Put everything back into the original parse.
                  (setf (second query-command-parse-result)
                        query-command-symbol-or-form)
                  (setf (third query-command-parse-result)
                        query-domain)
                  (when attribute-argument?
                    (setf (fourth query-command-parse-result)
                          attribute-argument?))
                  query-command-parse-result))))))))))




(defun strip-source-positions (phrase-cons-tree)
  (typecase phrase-cons-tree
    (cons
     (cond
       ((eql (car-of-cons phrase-cons-tree) 'source-position)
        (strip-source-positions (second phrase-cons-tree)))
       (t
        (setf (car phrase-cons-tree) (strip-source-positions (car phrase-cons-tree)))
        (setf (cdr phrase-cons-tree) (strip-source-positions (cdr phrase-cons-tree)))
        phrase-cons-tree)))
    (t
     phrase-cons-tree)))



(def-class-method cleanup (inspect-command)
  (funcall-superior-method inspect-command)
  (cancel-search-state-for-inspect-command-if-necessary inspect-command))


(defun cancel-search-state-for-inspect-command-if-necessary (inspect-command)
  (let ((search-state?
          (search-state-for-inspect-command? inspect-command)))
    (when (and search-state?
               (not
                 (frame-has-been-reprocessed-p
                   search-state?
                   (frame-serial-number-for-inspect-command-search-state?
                     inspect-command))))
      (cancel-scheduled-search-if-necessary search-state?)
      (delete-frame search-state?)

      ;; Try not to leave a deleted frame in the slot.  It's hopeless, though,
      ;; because search-states are deleted at random times by
      ;; work-on-current-query-for-workstation. -fmw, 1/27/95
      (setf (search-state-for-inspect-command? inspect-command) nil))))


;;Gensym-419, for cloned workspace to be deleted, it will not be searched by INSPECT
(defun-simple cloned-workspace-to-be-deleted-p (frame)
 (let ((superblock? (superblock? frame)))
    (when superblock? (and (or (frame-of-class-p frame 'kb-workspace)
            (and (framep superblock?)(workspace-p superblock?)))
       (not (frame-in-use-p superblock?))))))




;;; `Evaluate-query-to-first-approximation' is called as an inspect command involving
;;; a query is getting up a head of steam.  It is fast, but not very accurate.
;;; It returns a list using eval-conses some subset of which is a perfect match
;;; for the query in question.  Currently it just returns a list of all the instances
;;; in the class questioned.

;;; Since this calls thru to the designation evaluation code current computation frame
;;; must be bound.

(defun-simple ignore-in-recompile-p (frame)
  (if (g2-enterprise-p)
    (frame-class-case frame
      (parameter t)
      (quantity-array t)
      (hash-table t)
      (priority-queue t)
      (t nil))
    nil))

(defun evaluate-query-to-first-approximation (query-designation ignore-in-recompile?)
  (let* ((current-computation-flags current-computation-flags)
         (eval-list-of-items nil))
    (setf (role-serve-inactive-objects?) t)
    ;; The query-designations looks like
    ;; (<query-kind> <class> <predicate>)
    ;; For now just collect all instances of that class
    (setq eval-list-of-items
          (gensym-dstruct-bind ((nil class predicate) query-designation)
            ;; The predicate looks like (g2-lambda ((<local> (class <class>))) <logical-expression>)
            (let ((logical-expression (third predicate)))
              (let (name workspace-designation)
                (cond
                  ;; First handle the case where the class is not a class, but
                  ;; is instead a role to fetch class qualified methods.  This
                  ;; approach seems to be in keeping with the unrepentant
                  ;; hackery exhibited in every other sibling cond clause to
                  ;; this.  At least I sign my sins.  -jra 5/31/95
                  ((and (consp class)
                        (eq (car-of-cons class) 'class-qualified-method))
                   (serve-eval-list-of-role-values class nil))

                  ;; Has the name given, as either a debugging, primary or secondary name
                  ((multiple-value-bind (flag result)
                       (logical-expression-includes-pattern
                         logical-expression
                         '(or
                           (there-exists-literal
                            (((role-server name) . :symbol) :symbol)
                            (= :a ':symbol))
                           (g2-inspect-internal-name-for-debugging-p :B ':C))
                         3)
                     (setf name result)
                     flag)
                   (let ((role-1 (slot-value-list 'named-by-debugging-name class))
                         (domain-1 (make-temporary-constant-no-expiration name 'symbol))
                         (role-2 (slot-value-list 'named-by class))
                         (domain-2 (make-temporary-constant-no-expiration name 'symbol)))
                     (prog1 (nconc (serve-eval-list-of-role-values role-1 domain-1)
                                   (serve-eval-list-of-role-values role-2 domain-2))
                       (reclaim-slot-value role-1)
                       (reclaim-temporary-constant domain-1)
                       (reclaim-slot-value role-2)
                       (reclaim-temporary-constant domain-2))))

                  ;; Has this primary name.
                  ((multiple-value-bind (flag result)
                       (logical-expression-includes-pattern
                         logical-expression
                         '(and (has-a-name :symbol)
                           (is (the (role-server name) :A) ':symbol))
                         2)
                     (setf name result)
                     flag)
                   (let ((role (slot-value-list 'named-by class))
                         (domain (make-temporary-constant-no-expiration name 'symbol)))
                     (prog1
                         (serve-eval-list-of-role-values role domain)
                       (reclaim-slot-value role)
                       (reclaim-temporary-constant domain))))

                  ;; Has this primary or secondary name.
                  ((multiple-value-bind (flag result)
                       (logical-expression-includes-pattern
                         logical-expression
                         '(or
                           (and (has-a-name :symbol)
                            (is (the (role-server name) :A) ':symbol))
                           (g2-inspect-internal-name-for-debugging-p :A ':B))
                         2)
                     (setf name result)
                     flag)
                   (let ((role-1 (slot-value-list 'named-by-debugging-name class))
                         (domain-1 (make-temporary-constant-no-expiration name 'symbol))
                         (role-2 (slot-value-list 'named-by class))
                         (domain-2 (make-temporary-constant-no-expiration name 'symbol)))
                     (prog1
                         (nconc
                           (serve-eval-list-of-role-values role-1 domain-1)
                           (serve-eval-list-of-role-values role-2 domain-2)
                           (reclaim-slot-value role-1)
                           (reclaim-temporary-constant domain-1)
                           (reclaim-slot-value role-2)
                           (reclaim-temporary-constant domain-2)))))

                  ;; Is on the given workspace.
                  ((multiple-value-bind (flag result)
                       (logical-expression-includes-pattern
                         logical-expression
                         '(and
                           (exists (the (role-server workspace kb-workspace) :symbol))
                           (same-as (the (role-server workspace kb-workspace) :A) :symbol))
                         2)
                     (setf workspace-designation result)
                     flag)
                   ;; Build a designation like "(every (upon item) gum)" and use it.
                   (let ((workspace? (evaluate-designation workspace-designation nil))
                         (class-description? (class-description class)))
                     (if (and workspace?
                              class-description?
                              (class-description-of-class-p class-description? 'item)
                              (or (of-class-p workspace? 'kb-workspace)
                                  (of-class-p workspace? 'message-board)))
                         (loop for frame being each subblock of workspace?
                               if (frame-of-class-description-p frame class-description?)
                                 collect frame using eval-cons)
                         nil)))

                  ;; Oh well, just get everybody in this class.
                  (t
                   (let ((designation (slot-value-list 'any class)))
                     (prog1
                         (serve-eval-list-of-designation-values designation)
                       (reclaim-slot-value-list designation)))))))))
    ;; The following egregious hack provides a thin veneer over the fact that
    ;; action buttons and user menu choices are implemented by embedding rule
    ;; frames.  Access to such rules should really only be through the
    ;; embedding object.  So, we'll filter them out of inspect results here
    ;; and now, in hopes of getting actions into g2-cell-arrays later.  -jra
    ;; 12/9/94
    (when eval-list-of-items
      (loop with eval-cons-trailer = nil
            with eval-cons = eval-list-of-items
            for next-eval-cons = (cdr-of-cons eval-cons)
            do
        (cond ((embedded-rule-p (car-of-cons eval-cons))
               (reclaim-eval-cons eval-cons)
               (setq eval-cons next-eval-cons)
               (if eval-cons-trailer
                   (setf (cdr-of-cons eval-cons-trailer) next-eval-cons)
                   (setq eval-list-of-items next-eval-cons)))
               ;;Gensym-419, for cloned workspace to be deleted, it will be remove for search-items
               ((cloned-workspace-to-be-deleted-p (car-of-cons eval-cons))
               (reclaim-eval-cons eval-cons)
               (setq eval-cons next-eval-cons)
               (if eval-cons-trailer
                   (setf (cdr-of-cons eval-cons-trailer) next-eval-cons)
                   (setq eval-list-of-items next-eval-cons)))
	       ((and ignore-in-recompile?
		     (ignore-in-recompile-p (car-of-cons eval-cons)))
		(reclaim-eval-cons eval-cons)
                (setq eval-cons next-eval-cons)
                (if eval-cons-trailer
                    (setf (cdr-of-cons eval-cons-trailer) next-eval-cons)
                    (setq eval-list-of-items next-eval-cons)))
              (t
               (setq eval-cons-trailer eval-cons)
               (setq eval-cons next-eval-cons)))
            while eval-cons))
    eval-list-of-items))






;;; `Logical-expression-includes-pattern' is a subfunction of evaluate-query-to-first-approximation.
;;; It is used to recognize the presense of a given pattern within a predicate.
;;; It will search nested AND clauses in predicate for pattern.  The pattern is it's self
;;; a predicate expression except that wild cards may appear at the leaves of the pattern.
;;; These wild cards include:
;;;    :any  -- matchs anything.
;;;    :symbol  -- matches only a symbol.
;;;    :A :B :C  -- matches exactly and earlier :any or :symbol card match.

;;; Three parameters are required, and two values are returned.  The predicate and pattern
;;; are passed followed by an one based index.  The first return value is a boolean indicating
;;; success.  The second return value is the Nth :any or :symbol wild card match as selected
;;; by the one based index.

(defvar match-pattern-for-inspect-binding-vector  (make-array 3))
(defvar fill-pointer-for-match-pattern-for-inspect-binding-vector)

(defun logical-expression-includes-pattern (logical-expression pattern return-index)
  (setf fill-pointer-for-match-pattern-for-inspect-binding-vector 0)
  (block search
    (when (match-pattern-for-inspect-1 logical-expression pattern)
      (return-from search
        (values t (svref match-pattern-for-inspect-binding-vector
                         (1- return-index)))))
    (when (and (consp logical-expression)
               (eq 'and (car logical-expression)))
      (loop for sub-expression in (rest logical-expression)
            do
        (multiple-value-bind (flag result)
                             (logical-expression-includes-pattern sub-expression pattern return-index)
          (when flag
            (return-from search (values flag result))))))
    nil ;; Default for block.
    ))

(defun match-pattern-for-inspect-1 (target pattern)
  (if (consp pattern)
      (and (consp target)
           (match-pattern-for-inspect-1 (car target) (car pattern))
           (match-pattern-for-inspect-1 (cdr target) (cdr pattern)))
      (cond
        ((keywordp pattern)
         (let ((add-to-binding-vector? nil))
           (prog1
             (case pattern
               (:any (setf add-to-binding-vector? t)
                     t)
               (:symbol (setf add-to-binding-vector? t)
                        (symbolp target))
               (:A (eq target
                       (svref match-pattern-for-inspect-binding-vector 0)))
               (:B (eq target
                       (svref match-pattern-for-inspect-binding-vector 1)))
               (:C (eq target
                       (svref match-pattern-for-inspect-binding-vector 2)))
               #+development
               (otherwise
                (cerror "Ignore and go" "Unknown pattern wildcard encountered in match-pattern-for-inspect ~A" pattern)
                nil))
             (when add-to-binding-vector?
               (setf (svref match-pattern-for-inspect-binding-vector
                            fill-pointer-for-match-pattern-for-inspect-binding-vector)
                     target)
               (incff fill-pointer-for-match-pattern-for-inspect-binding-vector)))))
        ((atom pattern)
         (eq pattern target))
        (t (eq pattern target)))))



;;; `g2-permit-inspector-within-restricted-license' is a system-procedure-function
;;; that sets a flag, override-limited-license-block-on-inspect?, which is read
;;; by the define-ui-command for inspect (in COMMANDS1).  It does what it says.
;;; It is checked when the license restriction has kicked in and allows the
;;; call to inspect to go through when it would otherwise have been blocked.

(declare-system-procedure-function g2-permit-inspector-within-restricted-license t)

(defparameter override-limited-license-block-on-inspect? nil)

(defun-funcallable g2-permit-inspector-within-restricted-license ()
  (setq override-limited-license-block-on-inspect? t)
  (copy-evaluation-truth-value evaluation-true-value))

(defconstant inspect-command-history-list-max-size 50
  "the maximum size of `inspect-command-history-list' below.")

;;; the executed inspect command list,from newer to older.
;;; The duplicated older history command will be removed when
;;; insert a same one, and the oldest history command will be removed
;;; when the list exceed `inspect-command-history-list-max-size'
;;; FIXME: use `def-kb-specific-variable' here?
(defvar inspect-command-history-list nil)

(defun-void clear-inspect-command-history-list ()
  (loop for history-string in inspect-command-history-list
	do (reclaim-text-string history-string))
  (reclaim-gensym-list inspect-command-history-list)
  (setf inspect-command-history-list nil))

(defun-void cache-inspect-command-history (inspect-command)
  ;; don't cache the history inspect command itself.
  (let* ((query (car (box-translation-and-text inspect-command)))
	 (query-handler
	  (if (consp (second query)) (first (second query)) (second query))))
    (when (equal 'show-inspect-command-history-on-a-workspace query-handler)
      (return-from-defun-void)))

  (let ((inspect-command-string
         (convert-text-to-text-string (cdr (box-translation-and-text inspect-command)))))
    ;; remove the same older one if have.
    (loop for trailing-pointer-1 = nil then leading-pointer-1
	  for leading-pointer-1 = inspect-command-history-list then (cdr leading-pointer-1)
	  until (null leading-pointer-1)
	  do
       (when (string=w (car leading-pointer-1) inspect-command-string)
	 (if trailing-pointer-1
	   (setf (cdr-of-cons trailing-pointer-1) (cdr leading-pointer-1))
	   (setf inspect-command-history-list (cdr inspect-command-history-list)))
	 (reclaim-text-string (car leading-pointer-1))
	 (reclaim-gensym-cons leading-pointer-1)
	 ;; and add the newer one to front of inspect-command-history-list.
	 (setf inspect-command-history-list (nconc (gensym-list inspect-command-string)
						   inspect-command-history-list))
	 (return-from-defun-void)))

    ;; if the `inspect-command-history-list' has exceed the maximum size, remove the last one.
    (when (>=f (length inspect-command-history-list) inspect-command-history-list-max-size)
      (loop for trailing-pointer-2 = nil then leading-pointer-2
	    for leading-pointer-2 = inspect-command-history-list then (cdr leading-pointer-2)
	    when (null (cdr leading-pointer-2))
	      do
	   (reclaim-text-string (car-of-cons leading-pointer-2))
	   (reclaim-gensym-cons leading-pointer-2)
	   (setf (cdr-of-cons trailing-pointer-2) nil)
	   (loop-finish)))
    (setf inspect-command-history-list
	    (nconc (gensym-list inspect-command-string)
		   inspect-command-history-list))))

(defun-void show-inspect-command-history-on-a-workspace (inspect-command)
  (let* ((workspace
	   (or (get-and-clear-workspace-for-inspect-command inspect-command)
	       (make-inspect-workspace inspect-command)))
	 (interitem-spacing 5)
	 (workspace-margin (workspace-margin workspace))
	 (left-edge-in-workspace
	   (+w (left-edge-of-block workspace)
	       workspace-margin))
	 (top-edge-in-workspace
	  (+w (bottom-edge-of-block inspect-command)
	      interitem-spacing)))
    (cond (inspect-command-history-list
	   (let ((note-text-box
                  (make-free-text-box
                    (tformat-text-string "~% There exists ~D command history.~%~%"
                                         (length inspect-command-history-list)))))
	     (add-to-workspace
	      note-text-box workspace
	      left-edge-in-workspace top-edge-in-workspace)
	     (setf top-edge-in-workspace 
		      (+w (bottom-edge-of-block note-text-box)
			  interitem-spacing)))
	   (loop for command-history-text in inspect-command-history-list
		 for history-frame = (make-text-box 'inspect-history)
		 do
	      (setf (box-translation-and-text history-frame)
		      (slot-value-cons
		       no-value
		       (convert-text-string-to-text (copy-text-string command-history-text))))
	      (reformat-text-box-in-place history-frame)
	      (add-to-workspace history-frame workspace
		  left-edge-in-workspace top-edge-in-workspace)
	      (setf top-edge-in-workspace 
		      (+w (bottom-edge-of-block history-frame)
			  interitem-spacing))))
	  (t 
	   (let ((free-text-box (make-free-text-box (tformat-text-string "No inspect command history."))))
	     (add-to-workspace
	      free-text-box workspace
	      left-edge-in-workspace top-edge-in-workspace))))
    (shrink-wrap-workspace workspace)
    (put-inspect-workspace-on-current-detail-pane workspace)))

(def-class-method execute-command (inspect-history)
  (let* ((inspect-command-string (convert-text-to-text-string (cdr (box-translation-and-text inspect-history))))
	 (inspect-command (make-inspect-command-or-signal-error inspect-command-string)))
    (reformat-text-box-in-place inspect-command)
    (execute-inspect-command inspect-command)))


(def-class-method execute-command (inspect-command)
  (execute-inspect-command inspect-command))

(defun-allowing-unwind execute-inspect-command (inspect-command)
  (with-backtrace-for-internal-error 'execute-inspect-command
    (let* ((query (car (box-translation-and-text inspect-command)))
           (query-handler
             (if (consp (second query)) (first (second query)) (second query))))

      ;; Cancel the background previous search process if any before doing any of
      ;; these commands:
      (cancel-search-state-for-inspect-command-if-necessary inspect-command)

      (cache-inspect-command-history inspect-command)

      (case query-handler
        ((highlight replace show-on-a-workspace ; This is where we figure out whether to go to a
                                        ; specialized graphing version of "show
                                        ; on a workspace" or whether to do a
                                        ; regular searching type of inspect.
                    display-a-table display-a-table-columnwise
                    visit write-to-a-file
                    recompile)

         (let* ((query-designations (third query))
                (item-filter
                  (copy-for-slot-value query-designations))        ; => ({class filter-for-class})
                (ignore-in-recompile? (eq query-handler 'recompile))
                (frame-list
                  (let ((*current-computation-frame* inspect-command)) ;; ?? BAH
                    (evaluate-query-to-first-approximation (car item-filter) ignore-in-recompile?))))
           (cond
             ((memq query-handler
                    '(show-on-a-workspace
                      visit write-to-a-file recompile
                      display-a-table display-a-table-columnwise))
              (protected-let* ((write-to-a-file-p
                                 (eq query-handler 'write-to-a-file))
                               (pathname-for-search-items?
                                 (and write-to-a-file-p
                                      (make-full-pathname
                                        (second (second query))))
                                 (reclaim-gensym-pathname
                                   pathname-for-search-items?))
                               (namestring-for-search-items?
                                 (and write-to-a-file-p
                                      (gensym-namestring-as-text-string
                                        pathname-for-search-items?
                                        t)))
                               (ascii-namestring-for-search-items?
                                 (and write-to-a-file-p
                                      (gensym-namestring
                                        pathname-for-search-items?
                                        nil))))
                (search-items
                  frame-list item-filter nil nil nil
                  (not (or (eq query-handler 'show-on-a-workspace)
                           (eq query-handler 'visit)))
                  namestring-for-search-items?
                  ascii-namestring-for-search-items?
                  inspect-command
                  (eq query-handler 'visit)
                  (case query-handler
                    (display-a-table t)
                    (display-a-table-columnwise 'columnwise)
                    (t nil))
                  (copy-list-using-slot-value-conses
                    (fourth query))
                  (eq query-handler 'recompile))))
             (t                                        ; replace and highlight cases
              (let* ((observance-of-word-boundary?
                       (unless (or (text-string-p (second (second query)))        ; stringp case obsolete?!
                                   (eq (second (second query)) 'non-word))
                         (second (second query))))
                     (what-to-look-for
                       (third (second query)))
                     (replacement?
                       (fourth (second query)))
                     (string-to-look-for
                       (if (symbolp what-to-look-for)
                           (copy-symbol-name-parsably what-to-look-for nil)
                           what-to-look-for))
                     (replacement-string?
                       (if replacement?                ; can't handle symbol nil!
                           (if (symbolp replacement?)
                               (copy-symbol-name-parsably replacement? nil)
                               replacement?))))
                (search-items
                  frame-list item-filter
                  string-to-look-for replacement-string?
                  observance-of-word-boundary?
                  nil                                ; no-results-table? -- later, optional!
                  nil nil inspect-command nil nil
                  (copy-list-using-slot-value-conses
                    (fourth query)))
                (if (not (eq string-to-look-for what-to-look-for))
                    (reclaim-text-string string-to-look-for))
                (if (not (eq replacement-string? replacement?))
                    (reclaim-text-string replacement-string?)))))
           (reclaim-eval-list frame-list)))
        ((show-class-hierarchy-on-a-workspace
           show-workspace-hierarchy-on-a-workspace)
         (unless (run-command-invisibly-p inspect-command)
           (show-workspace-or-class-hierarchy-on-a-workspace
             (third query)
             (eq query-handler 'show-class-hierarchy-on-a-workspace)
             inspect-command)))
        (show-procedure-invocation-hierarchy-on-a-workspace
         (unless (run-command-invisibly-p inspect-command)
           (graph-detailed-procedures nil inspect-command)))
        (show-method-inheritance-path-on-a-workspace
         (unless (run-command-invisibly-p inspect-command)
           (show-method-inheritance-path-for-class-on-a-workspace
             (third query) (fourth query) inspect-command)))
        (show-method-hierarchy-on-a-workspace
         (unless (run-command-invisibly-p inspect-command)
           (show-method-hierarchy-on-a-workspace
             (third query)
             inspect-command)))
        (show-inspect-command-history-on-a-workspace
         (unless (run-command-invisibly-p inspect-command)
           (show-inspect-command-history-on-a-workspace inspect-command)))
        (show-module-hierarchy-on-a-workspace
         (unless (run-command-invisibly-p inspect-command)
           (show-module-hierarchy-on-a-workspace (third query) inspect-command)))
        (show-procedure-calling-hierarchy-on-a-workspace ; (QUERY SHOW-PROCEDURE-REFERENCE-HIERARCHY-ON-A-WORKSPACE MYPROC)
          (unless (run-command-invisibly-p inspect-command)
            (show-procedure-reference-hierarchy-on-a-workspace (third query) inspect-command)))
        (show-procedure-caller-hierarchy-on-a-workspace ; (QUERY SHOW-PROCEDURE-caller-hierarchy-ON-A-WORKSPACE MYPROC)
         (unless (run-command-invisibly-p inspect-command)
           (show-procedure-reference-hierarchy-on-a-workspace (third query) inspect-command t)))
        (check-for-consistent-modularization
         (search-items
           nil nil nil nil nil t
           nil nil inspect-command nil nil nil nil
           'inspect-kb-for-modularity-problems
           (slot-value-list inspect-command)))
        (write-class-hierarchy-to-file
         ;; Most of the code is the same as the query verb write-to-file
         (let* ((file-name (second (second query)))
                (class (third query)))
           (write-class-hierarchy-to-file
             file-name class inspect-command)))
        (version-control
         (version-control-query
           inspect-command
           (run-command-invisibly-p inspect-command)))))))


;; It would be nice to have an input kill ring to get at previous commands.
;; Something like the following could be involved:
;;
;;    (scrap-text
;;       (copy-text (cdr (box-translation-and-text inspect-command)))
;;       nil t)


;; jh per mhd, 1/22/91.  Converted the execute-command method for inspect to use
;; the new gensym-pathnames to identify files.  The old lisp streams are still
;; used after we get a namestring, but this will change soon.



;;; Inspect-kb-for-modularity-problems ...

(defun inspect-kb-for-modularity-problems (inspect-command?)
  (check-savability-of-kb-in-terms-of-modularity inspect-command?)
  nil)

;; [later, make this interruptable -- it should return T to indicate
;; it has more work to do, nil to indicated it's finished.  Right now,
;; it only works in batch mode.]


;;; Frame-matches-item-filter-p ...

;;; An `item filter' is a list of the form
;;;
;;;    ({class unique-logical-expression})

;;; ... Kb-search-state is used as the value of *current-computation-frame*.

(defun frame-matches-item-filter-p (kb-search-state frame item-filter)
  (let* ((cell-index (third (car item-filter)))
         (*current-computation-frame* kb-search-state)
         (current-block-of-dependent-frame kb-search-state)
         (current-computation-component-particulars
           (slot-value-list 'cell-array-element cell-index))
         (truth-value-or-unknown-datum
           (funcall-expression-cell-1 cell-index frame)))
    (reclaim-slot-value current-computation-component-particulars)
    (if (null truth-value-or-unknown-datum)
        nil
        (evaluation-truth-value-is-true-p truth-value-or-unknown-datum))))

;; Ben,
;; The above documentation is no longer true, evidently.  The item filter used
;; by search-items-a-little for the query "every procedure-invocation" is
;;
;;    ((every-instance-such-that procedure-invocation 0)
;;     . " every procedure-invocation")
;;
;; Furthermore, there used to not even be an item filter for such a simple query.
;; That means that search-items-a-little never had to call frame-matches-item-
;; filter-p for every item when given a trivial (i.e., non-existent) filter, e.g.
;; "every procedure" (period).  Why do we have to pay the extra overhead?!
;; (MHD 4/16/92)
;;
;; --- I just found this documentation in search-items:   (MHD 4/16/92, later)
;;
;;    ;; Item-filter-for-kb-search? looks like
;;    ;;
;;    ;;   ((<query-kind> <class> <predicate>) . <source-text>)
;;    ;;
;;    ;; Replace <predicate> with a <cell-index>.




(defun funcall-expression-cell-1 (cell-index argument-1)
  (let* ((argument-list (eval-list argument-1))
         (expression-cell (managed-svref
                            (g2-cell-array-managed-array
                              (cell-array current-block-of-dependent-frame))
                            cell-index)))
    (cond
      ((not (expression-cell-able-to-compute-p expression-cell))
       nil)
      (t
       (attempt-expression-cell-execution expression-cell argument-list t)
       (reclaim-eval-list argument-list)
       (g2-expression-cell-cached-value expression-cell)))))

(def-class-method expression-cell-updated
                  (kb-search-state g2-cell-array cell-index old-value? new-value?)
  (declare (ignore kb-search-state g2-cell-array cell-index old-value? new-value?)))


;;; Name-for-frame-p is true if frame has name as a member of its name-or-
;;; names-for-frame slot or if name is the same as the debugging name for the
;;; frame.  This function takes either a string or a symbol as the name, but
;;; will only return true for a string when the string is the same as the
;;; debugging name for the frame.

(defun name-for-frame-p (name frame)
  (let ((name-or-names-for-frame (name-or-names-for-frame frame)))
    (or (if (atom name-or-names-for-frame)
            (eq name name-or-names-for-frame)
            (memq name name-or-names-for-frame))
        (and (block-p frame)
             (debugging-name-for-block-p
               frame
               (if (symbolp name)
                   (symbol-name-text-string name)
                   name))))))

;; General function -- move to one of the FRAMES modules! (MHD)

;; Note that this function is mis-named.  This should be
;; name-or-debugging-name-for-frame-p.  -jra 9/21/90






;;; Make-inspect-workspace ... creates it with a name like "INSPECT-<n>", where
;;; <n> is a counter.  ... This must be called in a for-workstation context.
;;; The resulting workspace is a non-kb workspace specific to the current
;;; workstation.

;; Make sure kbs cannot end up with orphan workspaces for kb search results!

(def-system-variable inspection-instance-counter queries
  0)                                                ; increment before each use

(defun make-inspect-workspace (inspect-command? &optional show-name-box?)
  (let ((workspace
          (make-workspace
            'temporary-workspace
            nil nil 5 nil nil current-workstation)))
    (setf (name-or-names-for-frame workspace)
          (intern-text-string
            (tformat-text-string
              "INSPECT-~d"
              (incff inspection-instance-counter))))
    (if show-name-box?
        (update-name-box workspace))
    (if inspect-command?
        (add-to-workspace
          inspect-command? workspace
          (+w (left-edge-of-block workspace)
              (workspace-margin workspace))
          (+w (top-edge-of-block workspace)        ; would lose with name box!
              (workspace-margin workspace))))
    workspace))

;; Consider making a special class of workspace, inspect-workspace.
;; Consider making that class be a subclass of non-kb-workspace but not
;; of temporary-workspace so that hiding the workspace does not delete it.
;; The problem I see with that, and even with the current way, is that
;; deleting the workspace is too much of a hassle -- it's bad enough
;; to have to click to get the menu, then click on delete-workspace, but
;; then to have to confirm would be a hassle.  In addition, there is what
;; I consider a bug in that kb restrictions on workspaces apply to
;; non-kb workspace -- meaning that when delete-workspace is globally
;; disallowed, one cannot delete an inspect workspace at all without
;; changing modes! (MHD 3/23/90)

;;; Class-hierarchy-borderless-free-text-format ... The idea is to never have
;;; line breaks, so this is just like borderless-free-text-format, except that
;;; minimum-format- width-for-text-cell and maximum-format-width-for-text-cell
;;; are virtually infinite.

(def-text-box-format class-hierarchy-borderless-free-text-format
  text-cell-font-map (hm18)                        ; 1 en = 10 workspace units
  text-cell-line-height 20                        ; experiment with these!
  text-cell-baseline-position 15
  text-cell-line-spacing 4
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 6.75)        ; 2/3 en
  minimum-word-spacing #.(convert-to-text-width 5)        ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 15)        ; 3/2 en
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 12
  text-cell-lines-justified? nil
  text-cell-line-color? black
  text-box-border-color? black
  text-cell-left-margin 6
  text-cell-top-margin 3
  text-cell-right-margin 6
  text-cell-bottom-margin 2
  text-box-left-border-width 0
  text-box-top-border-width 0
  text-box-right-border-width 0
  text-box-bottom-border-width 0

  maximum-format-width-for-text-cell 2000        ;lots of space so that
  minimum-format-width-for-text-cell 2000        ;text doesn't wrap round
  )

;; Class-hierarchy-borderless-free-text-format is obsolete, but it could
;; conceivably still be in old KBs (prior to 2.0).  It was used for
;; the line-printer style output of class hierarchies prior to the tree-style
;; output introduced for 2.0.  Through "transfer" text boxes with it as their
;; format might have gotten saved out.  (MHD 6/11/90)





;;; `Write-class-hierarchy-to-file' ... assumes that its file-name argument is
;;; in the Gensym character set, as opposed to ASCII (e.g., it assumes
;;; backslashes and tildes are escaped).

(defun-allowing-unwind write-class-hierarchy-to-file
    (file-name class query-command)
  (protected-let* ((pathname-for-write-hierarchy
                     (make-full-pathname file-name)
                     (reclaim-gensym-pathname
                       pathname-for-write-hierarchy))
                   (namestring-for-write-hierarchy
                     (gensym-namestring
                       pathname-for-write-hierarchy)
                     (reclaim-text-string
                       namestring-for-write-hierarchy)))
    (with-dynamic-creation
      (handling-file-errors
        (protected-let ((output-file-stream?
                          (g2-stream-open-for-output
                            namestring-for-write-hierarchy)
                          (g2-stream-close
                            output-file-stream?)))
          ;; jh, 1/11/95.  Added null check to swallow error opening file.  This
          ;; is probably not a final fix, but further refinement should be done
          ;; by the owner of this facility, mhd.
          (when output-file-stream?
            (let ((transcode-text-conversion-style
                    (or
                      (if (text-conversion-style language-parameters)
                          (get-text-conversion-style-structure-per-name
                            (text-conversion-style language-parameters)))
                      default-text-conversion-style)))
              (write-inspect-file-header
                output-file-stream?
                query-command)
              (show-inheritance-tree
                class output-file-stream?
                transcode-text-conversion-style))))))))

;; jh per mhd, 1/22/91.  Converted write-class-hierarchy-to-file to use the new
;; non-consing gensym-pathname structures.  Will soon convert the with-open-file
;; forms, since they leak too, but at least we don't crash anymore.

;;; Show-inheritance-tree prints out the inheritance hierarchy with class as root.

;;; If destination-g2-stream? is nil, this writes its output to the value
;;; of *standard-output*; otherwise, destination-g2-stream? should be a "g2 stream"
;;; open for output, and this then writes its output to that stream.

(defun show-inheritance-tree (class &optional destination-g2-stream?
                                    transcode-text-conversion-style-if-stream)
  (show-inheritance-tree-1
    class 0 destination-g2-stream?
    transcode-text-conversion-style-if-stream))

#+development
(defun show-class-tree (class)
  (let* ((wide-classes
           (twith-output-to-text-string (show-inheritance-tree class)))
         (classes (export-text-string wide-classes 'ascii)))
    (write-string classes)
    (reclaim-gensym-string classes)
    (reclaim-text-string wide-classes)
    (values)))


(defun show-inheritance-tree-1
    (class depth destination-g2-stream?
           &optional
           transcode-text-conversion-style-if-stream)
  (print-frame-newline-idiom)                ; unkludge later! (MHD 8/12/96)
  (loop with string = #w"|  "
        for tab from 1 to depth
        do (print-frame-string-idiom string))
  (print-frame-string-idiom (symbol-name-text-string class))
  (let ((number-of-instances
          (compute-number-of-instances-specific-to-class class)))
    (if (>f number-of-instances 0)
        (let ((text-string
                (tformat-text-string
                  " -- ~d instance~a"
                  number-of-instances
                  (if (>f number-of-instances 1) "s" ""))))
          (print-frame-string-idiom text-string))))
  (loop for inferior-class in (inferior-classes class)
        do (show-inheritance-tree-1
             inferior-class (+f depth 1)
             destination-g2-stream?
             transcode-text-conversion-style-if-stream)))

;; Converted to handle new arg destination-g2-stream? by writing to it using
;; g2-stream operations if it's non-nil, and continuing to use Lisp stream
;; operations if it's nil.  Also, changed the format slightly to improve and
;; simplify its appearance -- see 2.1 sources and/or its respective output
;; for details.  (MHD 7/8/91)

;; Note that users have complained of missing the number-of-instances
;; information only available through this interface in the on-screen
;; interface.  I can also imagine them not wanting it here in some cases.
;; (MHD 7/8/91)

;; I moved it here from FRAMES1, and removed #+development restriction.
;; (MHD 6/8/90)





(defun compute-number-of-instances-specific-to-class (class)
  (let ((count-so-far 0))
    (loop as next-frame?
             = (instances-specific-to-this-class class)
             then (class-specific-instances-forward-pointer next-frame?)
          until (null next-frame?)
          do (incff count-so-far))
    count-so-far))





;; Show On A Workspace The Workspace Hierarchy

;; Added by M. Levin, 4/6/90



;;; `Show-workspace-or-class-hierarchy-on-a-workspace' ...

;;; If class-case? is nil, this displays a hierarchy of
;;; workspaces (as short representations). If the argument is NIL,
;;; the entire kb-workspace hierarchy is displayed. This is unified
;;; into a tree by rooting it in the symbol KNOWLEDGE-BASE. If the
;;; the symbol names an item, then the tree rooted in that item is
;;; displayed. Otherwise, there is no display, and a notification is
;;; written. The value is t when a display is created, else nil.

;;; The nodes of the tree are always kb-workspaces except (1) if the the
;;; knowledge base is displayed, the root is the symbol KNOWLEDGE-BASE
;;; as mentioned above, and (2) if the the request designates an item
;;; which is not a kb-workspace and has no subworkspace, the tree consists
;;; of that item alone.

;;; If class-case? is true, this shows a graphical tree of the given class
;;; and its subclasses on a temporary workspace.

;;; If workspace? is specified, ...

;;; If inspect-command? is specified?, ...

(defun show-workspace-or-class-hierarchy-on-a-workspace
       (class-or-item-or-workspace-name? class-case?
        &optional inspect-command?)
  (let* ((item?
           (if (not class-case?)
               (if class-or-item-or-workspace-name?
                   (get-instance-with-name-if-any
                     'item
                     class-or-item-or-workspace-name?))))
         (class                                        ; look at if class-case? is non-nil
           (if class-case?
               class-or-item-or-workspace-name?))
         (workspace-with-inspect-command?
           (if inspect-command?
               (get-and-clear-workspace-for-inspect-command
                 inspect-command?))))
    (cond ((if class-case?
               (subclassp class 'item)
               (or (null class-or-item-or-workspace-name?)
                   item?))
           (reclaim-graph-display
             (graph-frame-hierarchy
               (if class-case?
                   'item ; (or (get-instance-with-name-if-any 'definition class) class)
                   (cond
                     ((null item?) nil)
                     ((and (frame-of-class-p item? 'entity)
                           (subworkspaces item?))
                      (car (subworkspaces item?)))
                     (t item?)))
               (if class-case?
                   'subclasses-of-class-for-graph-display
                   'subcomponents-of-workspace-or-item-for-display)
               (if class-case?
                   class
                   nil)
               (if class-case?
                   'short-representation-of-symbol-or-frame
                   'short-representation-of-symbol-or-frame-or-top-level)
               ;hash-function
               'hash-symbol-or-frame
               ;orientation
               'horizontal
               ;vertical-spacing
               1
               ;horizontal-spacing
               50                                 ; 50 is the lowest value
                                                ;   that doesn't result in
                                                ;   a bad connection when
                                                ;   you have
                                                ;
                                                ;    |-x
                                                ;    |-x
                                                ;  x1|-x2
                                                ;    |-x
                                                ;    |-x
                                                ;
                                                ;   x2's connection goes into x1
                                                ;   2 pixels too far.  AGH should
                                                ;   fix!  Try "show ... class hierarchy
                                                ;   of g2-list" in a new kb to see.
                                                ;   (MHD 6/21/90)
               ; pane-for-workspace-display
               (if (null workspace-with-inspect-command?)
                   current-workstation-detail-pane)
               ;class-of-workspace
               nil
               ; workspace?
               (or workspace-with-inspect-command?
                   (make-inspect-workspace inspect-command?))
               ;left-edge-for-graph?
               (if inspect-command?
                   (left-edge-of-block inspect-command?))
               ;top-edge-for-graph?
               (if inspect-command?
                   (+w (bottom-edge-of-block inspect-command?)
                       5))))
           t)
          (class-case?
           (notify-user
             "Cannot show the class hierarchy for ~a, since it is not ~a."
             class
             (if (classp class) "a subclass of item" "a class"))
           nil)
          (t
           (notify-user
             "Cannot show the workspace hierarchy for ~a, since it is not ~
              the name of an item."
             class-or-item-or-workspace-name?)
           nil))
    (if workspace-with-inspect-command?
        (shrink-wrap-workspace workspace-with-inspect-command?))))




(defun subclasses-of-class-for-graph-display
       (definition-or-class class-of-interest)
  (loop with current-class-name
          = (if (symbolp definition-or-class)
                definition-or-class
                (name-of-defined-class definition-or-class))
        with inferior-classes = (inferior-classes current-class-name)
        with current-class-is-subclass?
          = (subclassp current-class-name class-of-interest)
        for class in inferior-classes
        when (or current-class-is-subclass?
                 (eq class class-of-interest)
                 (subclassp class-of-interest class))
          collect (or (get-instance-with-name-if-any 'class-definition class) class)
                  using gensym-cons))



;;; The function `show-method-inheritance-path-for-class-on-a-workspace' sets
;;; up the tree for "show on a workspace the method inheritance path for
;;; <class> [and method <method>]".
;;;
;;; When class-of-interest and method-or-class-name are EQ, all inherited
;;; methods for a class are graphed; otherwise the inherited methods
;;; with method-or-class-name are graphed.

(defun show-method-inheritance-path-for-class-on-a-workspace
    (class-of-interest method-or-class-name &optional inspect-command?)

  (if (classp class-of-interest)
      (cond ((if (eq class-of-interest method-or-class-name)
                 (loop for class in (class-inheritance-path
                                      (class-description class-of-interest))
                       thereis (procedure-methods-of-class class))
                 (loop for class in (class-inheritance-path
                                      (class-description class-of-interest))
                       thereis (get-named-procedure-methods-for-class
                                 method-or-class-name class)))
             (let ((workspace-with-inspect-command?
                     (when inspect-command?
                       (get-and-clear-workspace-for-inspect-command
                         inspect-command?)))
                   (extra-arg-for-graphing
                     (if (eq class-of-interest method-or-class-name)
                         class-of-interest
                         (gensym-list class-of-interest method-or-class-name))))
               (reclaim-graph-display
                 (graph-frame-hierarchy
                   (or (get-instance-with-name-if-any
                         'class-definition class-of-interest)
                       class-of-interest)
                   'next-methods-for-graph-display
                   extra-arg-for-graphing
                   'short-representation-of-symbol-or-frame
                   ;hash-function
                   'hash-symbol-or-frame
                   ;orientation
                   'horizontal
                   ;vertical-spacing
                   1
                   ;horizontal-spacing
                   25
                   ;pane-for-workspace-display?
                   (if (null workspace-with-inspect-command?)
                       current-workstation-detail-pane)
                   ;class-of-workspace
                   nil
                   ;workspace?
                   (or workspace-with-inspect-command?
                       (make-inspect-workspace inspect-command?))
                   ;left-edge-for-graph?
                   (if inspect-command?
                       (left-edge-of-block inspect-command?))
                   ;top-edge-for-graph?
                   (if inspect-command?
                       (+w (bottom-edge-of-block inspect-command?)
                           5))))
               (when workspace-with-inspect-command?
                 (shrink-wrap-workspace workspace-with-inspect-command?))
               (when (consp extra-arg-for-graphing)
                 (reclaim-gensym-list extra-arg-for-graphing))))
            (t
             (if (eq class-of-interest method-or-class-name)
                 (notify-user
                   "There are no methods defined on the class hierarchy for ~a."
                   class-of-interest)
                 (notify-user
                   "There are no ~a methods defined on the class hierarchy for ~a."
                   method-or-class-name class-of-interest))))
      (notify-user
        "Cannot show the method hierarchy for ~a because it is not ~
          a defined class." class-of-interest)))




;;; The function `next-methods-for-graph-display' returns lists of children for
;;; "show on a workspace the method inheritance path for <class>
;;; [and method <method>]".

(defun next-methods-for-graph-display
    (frame-or-name class-name-or-list)
  (let* ((query-class
           (if (consp class-name-or-list)
               (car-of-cons class-name-or-list)
               class-name-or-list))
         (specific-method-of-interest?
           (and (consp class-name-or-list)
                (car-of-cons (cdr-of-cons class-name-or-list))))
         (class-inheritance-path
           (class-inheritance-path (class-description query-class))))

          ;; The last node is a class-name or class-definition:
          ;; If there is a specific-method-of-interest, the value
          ;; returned will be a listed method name or a listed method-
          ;; declaration frame; otherwise the value returned will be
          ;; a list of all of the uniquely-named methods for the class
          ;; in symbol or frame form.
    (cond ((or (and (framep frame-or-name) (class-definition-p frame-or-name))
               (classp frame-or-name))
           (if specific-method-of-interest?

               (gensym-list
                 (or (get-instance-with-name-if-any
                       'method-declaration specific-method-of-interest?)
                     specific-method-of-interest?))

               (loop with method-name-list = nil
                     for class in class-inheritance-path
                     for class-methods = (procedure-methods-of-class class)
                     do
                 (loop for (method-name nil) in class-methods
                       do
                   (unless (memq method-name method-name-list)
                     (cond ((null method-name-list)
                            (setq method-name-list
                                  (gensym-list method-name)))
                           ((string-lesspw
                              (symbol-name-text-string method-name)
                              (symbol-name-text-string
                                (car-of-cons method-name-list)))
                            (setq method-name-list
                                  (gensym-cons
                                    method-name method-name-list)))
                           (t
                            (let ((cons-after-which-to-insert-method-name
                                    (loop for cons on method-name-list
                                          when (and (string-greaterpw
                                                      (symbol-name-text-string method-name)
                                                      (symbol-name-text-string
                                                        (car-of-cons cons)))
                                                    (or (null (cdr cons))
                                                        (string-lesspw
                                                          (symbol-name-text-string method-name)
                                                          (symbol-name-text-string
                                                            (car-of-cons
                                                              (cdr-of-cons cons))))))
                                            return cons)))
                              (setf (cdr cons-after-which-to-insert-method-name)
                                    (gensym-cons
                                      method-name
                                      (cdr
                                        cons-after-which-to-insert-method-name))))))))
                     finally
                       (let ((next-methods-to-return
                               (loop for method in method-name-list
                                     collect
                                     (or (get-instance-with-name-if-any
                                           'method-declaration method)
                                         method)
                                     using gensym-cons)))
                         (reclaim-gensym-list method-name-list)
                         (return next-methods-to-return)))))


          ;; The last node is a method frame:  return the next method on the
          ;; hierarchy with the same name and number of arguments, if any.
          ((and (framep frame-or-name) (method-p frame-or-name))
           (let ((argument-count (argument-count frame-or-name))
                 (method-name (procedure-method-name frame-or-name))
                 (class-for-method
                   (procedure-method-class frame-or-name)))
             (loop for class in (cdr (memq class-for-method
                                           class-inheritance-path))
                   for methods-for-this-class? =
                         (get-named-procedure-methods-for-class
                           method-name class)
                   for method-with-correct-number-of-arguments? =
                         (and methods-for-this-class?
                              (loop for method in (cdr-of-cons
                                                    methods-for-this-class?)
                                    when (eq (argument-count method)
                                             argument-count)
                                      return method))
                   when method-with-correct-number-of-arguments?
                     return (gensym-list
                              method-with-correct-number-of-arguments?))))

          ;; The last node is a method name or a method-declaration frame:
          ;; return the method frames of the first-encountered methods of
          ;; that name with a unique argument count.
          (t
           (loop with list-of-argument-counts-represented = nil
                 with next-methods-to-return? = nil
                 with method-name = (if (framep frame-or-name)
                                        (name-or-names-for-frame frame-or-name)
                                        frame-or-name)
                 for class in class-inheritance-path
                 for methods-for-this-class? =
                 (get-named-procedure-methods-for-class method-name class)
                 do
             (when methods-for-this-class?
               (loop for method in (cdr-of-cons methods-for-this-class?)
                     for argument-count = (argument-count method)
                     do
                 (unless (memq argument-count
                               list-of-argument-counts-represented)
                   (setq list-of-argument-counts-represented
                         (gensym-cons argument-count
                                      list-of-argument-counts-represented))
                   (cond ((null next-methods-to-return?)
                          (setq next-methods-to-return?
                                (gensym-list method)))
                         ((<f argument-count
                              (argument-count
                                (car-of-cons next-methods-to-return?)))
                          (setq next-methods-to-return?
                                (gensym-cons
                                  method next-methods-to-return?)))
                         (t
                          (let ((cons-after-which-to-insert-method
                                  (loop for cons on next-methods-to-return?
                                        when (and (>f argument-count
                                                      (argument-count
                                                        (car-of-cons cons)))
                                                  (or (null (cdr cons))
                                                      (<f argument-count
                                                          (argument-count
                                                            (car-of-cons
                                                              (cdr-of-cons
                                                                cons))))))
                                          return cons)))
                            (setf (cdr cons-after-which-to-insert-method)
                                  (gensym-cons
                                    method
                                    (cdr cons-after-which-to-insert-method)))))))))
                 finally
                   (progn
                     (reclaim-gensym-list list-of-argument-counts-represented)
                     (return next-methods-to-return?)))))))






(defun short-representation-of-symbol-or-frame (symbol-or-frame)
  (if (symbolp symbol-or-frame)
      (make-description-box
        (tformat-text-string "~a" symbol-or-frame))
      (make-short-representation symbol-or-frame nil 'small)))





;;; `Make-short-representation-as-appropriate', if string-to-look-for? is not specified,
;;; returns a short representation table representing only the box-translation-and-text
;;; or class slot of frame, according to whether frame is a text box or not.  If
;;; string-to-look-for? is specified, a short representation table is returned only if
;;; the representation of some editable slot of frame contains string-to-look-for? or,
;;; where specified, second-string-to-look-for?.  In this second case, the table will
;;; contain representations for the box-translation-and-text or class slot plus editable
;;; slots in which one or both strings occur, and a second value will be returned to
;;; indicate if the representation of the box-translation-and-text or class slot contains
;;; either of the strings or not, where nil indicates that it does and the slot name
;;; indicates that it does NOT.  If only-find-string-to-look-for?-if-editable? is true,
;;; string-to-look-for? will not be matched in slots that are not editable because
;;; they either are not of an editable type or, unless frame is a message, because
;;; they have been stripped.

;;; When candidate-denotations-of-slots-to-describe-or-search? is specified, it
;;; should be a list of the slot denotations, or aliases thereof, of slots to
;;; always include in a resulting table and to limit the search to.  This list
;;; is not recycled by this function.

;;; This function used to be in tables.lisp.  It has since been rewritten as
;;; make-short-representation-for-queries, and short-representation-for-ref-
;;; hierarchy was removed.  We just realized that short-representation-for-ref-
;;; hierarchy is actually necessary, so I'm restoring it, along with the old
;;; version of this function.  - jv, 6/15/99

(defun make-short-representation-as-appropriate        ; used in search-items-a-little
    (frame
      &optional string-to-look-for? second-string-to-look-for? observe-word-boundaries?
      only-find-string-to-look-for?-if-editable?
      candidate-denotations-of-slots-to-describe-or-search?
      background-color?)
  (let* ((attributes-table-description? nil)
         ;; (class-description (class-description-slot frame))
         (slot-denotations-for-occurrences
           (if string-to-look-for?
               (loop as (slot-name defining-class? text-representation-for-slot-value?)
                        in (setq attributes-table-description?
                                 (make-attributes-table-description
                                   frame t
                                   candidate-denotations-of-slots-to-describe-or-search?
                                   ;; Why not include non-editable slots, esp. if
                                   ;;    not replacing?!
                                   ;; Also review evaluator for containing in
                                   ;;    QUERIES, which does not check the CLASS
                                   ;;    slot and also (redundantly) does not
                                   ;;    include non-editable slots!
                                   ))
                     as text? = (or text-representation-for-slot-value?
                                    (cdr (get-slot-value frame slot-name defining-class?)))
                     when (if text?
                              (or (if
                                    (or
                                      (not
                                        only-find-string-to-look-for?-if-editable?)
                                      (and (type-of-slot-if-editable
                                             (class frame) slot-name nil defining-class?)
                                           (or (transient-p frame)
                                               (permanent-block-p frame))
                                           ;; if a text slot, not stripped:
                                           (or text-representation-for-slot-value?
                                               (not (stripped-text-p text?))
                                               (frame-of-class-p frame 'message))
                                           (edit-attribute-allowed-p
                                             frame slot-name
                                             defining-class?)))

                                    (find-string-in-text-for-inspect
                                      string-to-look-for? text? observe-word-boundaries?))
                                  (if second-string-to-look-for?
                                      (find-string-in-text-for-inspect
                                        second-string-to-look-for?
                                        text? observe-word-boundaries?))))
                       collect (make-slot-name-denotation slot-name defining-class?)
                         using slot-value-cons)))
         (key-slot-name-if-no-occurrence? nil)
         (slot-denotations-for-table
           (if candidate-denotations-of-slots-to-describe-or-search?
               (if (or (null string-to-look-for?)
                       slot-denotations-for-occurrences)
                   (let ((attributes-table-description
                           (make-attributes-table-description
                             frame t
                             candidate-denotations-of-slots-to-describe-or-search?
                             nil t)))
                     (prog1
                         (nconc
                           (loop for (slot-name defining-class?)
                                     in attributes-table-description
                                 unless (slot-denotation-member
                                          slot-name defining-class?
                                          slot-denotations-for-occurrences)
                                   collect (make-slot-name-denotation slot-name defining-class?)
                                     using slot-value-cons)
                           slot-denotations-for-occurrences)
                       (reclaim-slot-value attributes-table-description))))
               (if (or (null string-to-look-for?)
                       slot-denotations-for-occurrences)
                   (let ((key-slot-name
                           (if (text-box-p frame)
                               'box-translation-and-text
                               'class)))
                     (if (and string-to-look-for?
                              (slot-denotation-member
                                key-slot-name
                                nil ; system slots never qualified now.
                                slot-denotations-for-occurrences))
                         slot-denotations-for-occurrences
                         (slot-value-cons
                           (setq key-slot-name-if-no-occurrence? key-slot-name)
                           slot-denotations-for-occurrences))))))
         (attribute-table?
           (if slot-denotations-for-table
               (make-attributes-table
                 frame
                 'short-representation-table-format 'short-representation-class-format
                 nil nil slot-denotations-for-table t))))

    (when attribute-table?
      (change-background-color-of-short-representation-table
        attribute-table? background-color?))
    (if attributes-table-description?
        (reclaim-slot-value attributes-table-description?))
    (cond
      (slot-denotations-for-table
       (reclaim-slot-value-tree slot-denotations-for-table)
       (values attribute-table? key-slot-name-if-no-occurrence?)))))

;; I added the candidate-denotations-of-slots-to-describe-or-search? arg.

;; Include all appropriate features of make-short-representation herein, so that
;; this may be used for Inspect generally.

;; Consider having this include, where string-to-look-for? is specified, representations
;; of NON-EDITABLE slots in which one or both strings occur, since replace-editable-
;; occurrences-of-string-in-table will ignore them anyway.




(defun short-representation-for-ref-hierarchy ; -pga, 1/12/96
    (symbol-or-frame &optional table-class? font-size? background-color?)
  (cond
    ((symbolp symbol-or-frame)
     (make-free-text-description-box
       (tformat-text-string "~a, a symbol"  symbol-or-frame)))
    ((listp symbol-or-frame)
     (make-free-text-description-box
       (tformat-text-string "~a, a generic method" (car symbol-or-frame))))
    (t (make-short-representation-as-appropriate
         symbol-or-frame table-class? font-size? background-color?))))



(defun make-free-text-description-box (text-line) ; -pga, 2/9/96
  (make-free-text-box
    text-line 'free-text
    (choose-font-format-per-fonts-table
      'short-representation-class-format ; 'free-text-format
      'font-for-free-text)))

(defun hash-symbol-or-frame (symbol-or-frame)
  (if (symbolp symbol-or-frame)
      (sxhash symbol-or-frame)                ; sxhashw not needed here; no wide strings
      (frame-hash symbol-or-frame)))


;;; Subcomponents-of-workspace-or-item-for-display returns a gensym list
;;; of workspaces.  If frame? is nil, the value is the list of top level
;;; workspaces; otherwise, frame? should be an item, and the value is the
;;; list of subworkspaces of entites which are subblocks (a) of the item
;;; if it is a kb-workspace or (b) of the subworkspace of frame? if it is
;;; an entity.  The list is always empty if frame? is an item other than
;;; a kb-workspace or an entity having a subworkspace.

(defun subcomponents-of-workspace-or-item-for-display (frame? extra-arg)
  (declare (ignore extra-arg))
  (if frame?
      (let ((workspace?
              (cond
                ((frame-of-class-p frame? 'kb-workspace)
                 frame?)
                ((and (frame-of-class-p frame? 'entity)
                      (frame-of-class-p                ; nec?!
                        frame? 'item)
                      (subworkspaces frame?))
                 (car (subworkspaces frame?)))
                (t
                 (multiple-value-bind (block? workspace?)
                     (get-block-on-workspace-for-frame frame?)
                   (when (and block? workspace?)        ; fixes old bug -- we
                                                ;   previously did not check this,
                                                ;   which meant you'd bomb out if you
                                                ;   did "show ... the workspace hierarchy of XXX"
                                                ;   where XXX was an item not on a workspace,
                                                ;   e.g., the g2-window for the initial (system)
                                                ;   window, or a transient item not on any
                                                ;   workspace.  (MHD 3/18/93)
                     (if (frame-of-class-p        ; nec?!
                           workspace? 'kb-workspace)
                         workspace?)))))))
        (when workspace?
          (loop for subblock being each subblock of workspace?
                for subworkspace?
                    = (if (and (frame-of-class-p subblock 'entity)
                               (frame-of-class-p subblock 'item))        ; nec?!
                          (car (subworkspaces subblock)))
                when subworkspace?
                  collect subworkspace? using gensym-cons)))
      (loop for block being class-instances of 'kb-workspace
            when (null (parent-of-subworkspace? block))        ; a top-level workspace?
              collect block using gensym-cons)))


;; Change this so that if arg is an item and not a workspace,
;; and if it has a workspace, use workspace instead.





(defun show-method-hierarchy-on-a-workspace (method-name &optional inspect-command?)
  (let ((workspace-with-inspect-command?
          (if inspect-command?
              (get-and-clear-workspace-for-inspect-command
                inspect-command?))))
    (cond
      ((methods-exist-in-subclass-hierarchy 'item method-name)
       (reclaim-graph-display
         (graph-frame-hierarchy
           'item
           'subnodes-of-method-hierarchy
           method-name
           'short-representation-of-symbol-or-frame
           ;hash-function
           'hash-symbol-or-frame
           ;orientation
           'horizontal
           ;vertical-spacing
           1
           ;horizontal-spacing
           50
           ;pane-for-workspace-display?
           (if (null workspace-with-inspect-command?)
               current-workstation-detail-pane)
           ;class-of-workspace
           nil
           ;workspace?
           (or workspace-with-inspect-command?
               (make-inspect-workspace inspect-command?))
           ;left-edge-for-graph?
           (if inspect-command?
               (left-edge-of-block inspect-command?))
           ;top-edge-for-graph?
           (if inspect-command?
               (+w (bottom-edge-of-block inspect-command?)
                   5)))))
      (t
       (notify-user
         "Cannot show the method hierarchy for ~a, since no methods are defined for it."
         method-name)))
    (if workspace-with-inspect-command?
        (shrink-wrap-workspace workspace-with-inspect-command?))))


(defun methods-exist-in-subclass-hierarchy (class-name method-name)
  (loop for subclass being each subclass of class-name
        thereis (get-named-procedure-methods-for-class method-name subclass)))

(defun subnodes-of-method-hierarchy (definition-class-or-method method-name)
  (cond ((not (or (not (of-class-p definition-class-or-method 'method))
                  (eq (car (cdr (get-named-procedure-methods-for-class
                                  (procedure-method-name definition-class-or-method)
                                  (procedure-method-class definition-class-or-method))))
                      definition-class-or-method)))
         nil)
        ((and (symbolp definition-class-or-method)
              (>=f (length (get-named-procedure-methods-for-class
                            method-name definition-class-or-method))
                   2)) ; old: 3, changed by GENSYMCID-1470 'Bug: Method Hierarchy'
         (copy-list-using-gensym-conses
           (cdr (get-named-procedure-methods-for-class
                            method-name definition-class-or-method))))
        (t
         (let ((current-class-name
                 (cond ((symbolp definition-class-or-method)
                        definition-class-or-method)
                       ((class-definition-p definition-class-or-method)
                        (name-of-defined-class definition-class-or-method))
                       (t                        ; must be a method
                        (procedure-method-class definition-class-or-method)))))
           (loop for class in (inferior-classes current-class-name)
                 for class-methods
                     = (cdr (get-named-procedure-methods-for-class method-name class))
                 when (or class-methods
                          (methods-exist-in-subclass-hierarchy class method-name))
                   nconc (if (and class-methods
                                  (null (cdr class-methods)))
                             (copy-list-using-gensym-conses class-methods)
                             (gensym-list class)))))))

(defun short-representation-of-symbol-or-frame-or-top-level (symbol-or-frame?)
  (short-representation-of-symbol-or-frame
    (or symbol-or-frame? 'knowledge-base)))





(defun get-directly-required-module-information-system-tables
       (module-information-system-table &optional ignored-extra-arg)
  (declare (ignore ignored-extra-arg))
  (loop for module
            in (directly-required-kb-modules module-information-system-table)
        as system-table-for-module?
           = (module-information-instance-for-module? module)
        ;; switched over to the above. (MHD 6/4/92)
;           (get-system-table-of-class-for-module-or-nil
;             module 'module-information)
        when system-table-for-module?
          collect system-table-for-module? using gensym-cons))

(defun make-attributes-table-for-module-information-in-hierarchy
       (module-information-system-table)
  (make-attributes-table
    module-information-system-table
    'short-representation-table-format
    nil ;'attribute-display-class-format
    nil ;'attribute-display-value-format
    nil ;'attribute-display-description-format
    '(top-level-kb-module?)
    nil
    '(top-level-kb-module?)))

(defun show-module-hierarchy-on-a-workspace
    (module-to-start-with? &optional inspect-command?)
  (let* ((ultimate-top-level-module?        ; nil if no real top-level module
           (top-level-kb-module? module-information))
         (workspace
           (or (if inspect-command?
                   (get-and-clear-workspace-for-inspect-command
                     inspect-command?))
               (make-inspect-workspace inspect-command?)))
         (interitem-spacing 5)
         (workspace-margin (workspace-margin workspace))
         (left-edge-in-workspace
           (+w (left-edge-of-block workspace)
               workspace-margin))
         (top-edge-in-workspace
           (if inspect-command?
               (+w (bottom-edge-of-block inspect-command?)
                   interitem-spacing)
               (+w (top-edge-of-block workspace)
                   workspace-margin)))
         (system-table-for-top-module?
           (if module-to-start-with?
               (module-information-instance-for-module? module-to-start-with?)
               module-information)))
    (if (and system-table-for-top-module?
             (top-level-kb-module? system-table-for-top-module?))
        (let ((graph
                (graph-frame-hierarchy
                  system-table-for-top-module?
                  'get-directly-required-module-information-system-tables
                  nil
                  'make-attributes-table-for-module-information-in-hierarchy
                  ;hash-function
                  'hash-symbol-or-frame
                  ;orientation
                  'vertical
                  ;vertical-spacing
                  50
                  ;horizontal-spacing
                  5
                  ;pane-for-workspace-display?
                  nil
                  ;class-of-workspace
                  nil
                  ;workspace?
                  workspace
                  ;left-edge-for-graph?
                  left-edge-in-workspace
                  ;top-edge-for-graph?
                  top-edge-in-workspace)))
          (setq top-edge-in-workspace
                (+w (graph-display-bottom-edge graph)
                    (twicew interitem-spacing)))
          (reclaim-graph-display graph))
        (let ((free-text-box
                (make-free-text-box
                  (tformat-text-string
                    "No module hierarchy ~a~a"
                    (if module-to-start-with? "can be shown for " "exists, because the top-level module is unnamed.")
                    (or module-to-start-with? "")))))
          (add-to-workspace
            free-text-box workspace
            left-edge-in-workspace top-edge-in-workspace t)
          (setq top-edge-in-workspace
                (+w (bottom-edge-of-block free-text-box)
                    (twicew interitem-spacing)))
          (when (null module-to-start-with?)
            (setq free-text-box
                  (make-free-text-box
                    (tformat-text-string
                      "Top-Level Module-Information System Table: ")))
            (add-to-workspace
              free-text-box workspace
              left-edge-in-workspace top-edge-in-workspace t)
            (setq top-edge-in-workspace
                  (+w (bottom-edge-of-block free-text-box)
                      (twicew interitem-spacing)))
            (let ((table
                    (make-attributes-table-for-module-information-in-hierarchy
                      module-information)))
              (add-to-workspace
                table workspace
                left-edge-in-workspace top-edge-in-workspace t)
              (setq top-edge-in-workspace
                    (+w (bottom-edge-of-block table)
                        (twicew interitem-spacing)))))))
    (loop with initial-x-in-workspace
            = left-edge-in-workspace
          with x-in-workspace
            = left-edge-in-workspace
          with y-in-workspace
            = top-edge-in-workspace
          with any-tables-up? = nil
          for module-information-instance
              being each class-instance of 'module-information
          as module? = (top-level-kb-module? module-information-instance)
          initially (propagate-kb-requires-module-p-to-all-modules)
          when (unless
                   ;; Don't graph if the module is the installed top-level module
                   (eq module-information-instance module-information)
                 ;; Do graph if there is no parent module above
                 (or (null module?)
                     ;; or if the module is not required anywhere.  For this to
                     ;; work, the expression below must conclude that a module is
                     ;; not required anywhere if its ultimate parent is an
                     ;; unnamed top-level module, i.e. if no module may be
                     ;; required if the top level module is unassigned.
                     (null ultimate-top-level-module?)
                     (not (efficient-kb-requires-module-p module?))))
            do (let ((table
                       (make-attributes-table-for-module-information-in-hierarchy
                         module-information-instance)))
                 (when (not any-tables-up?)
                   (setq any-tables-up? t)
                   (let ((text-box
                           (make-free-text-box
                             (copy-constant-wide-string #w"Modules not required by the KB:"))))
                     (add-to-workspace
                       text-box workspace
                       x-in-workspace y-in-workspace t)
                     (setq x-in-workspace        ; not really nec.
                           initial-x-in-workspace)
                     (setq y-in-workspace
                           (+w (bottom-edge-of-block text-box) 5))))
                 (add-to-workspace
                   table workspace
                   x-in-workspace y-in-workspace t)
                 (setq x-in-workspace
                       (+w (right-edge-of-block table) 5))
                 (when (>w (-w x-in-workspace initial-x-in-workspace)
                           400)
                   (setq x-in-workspace initial-x-in-workspace)
                   (setq y-in-workspace
                         (+w (bottom-edge-of-block table) 5)))))
    (shrink-wrap-workspace workspace)
    (put-inspect-workspace-on-current-detail-pane workspace)))

(defun find-method-declaration-for-name (generic-name)
  (let ((candidates (frame-or-frames-with-this-name generic-name)))
    (if (listp candidates)
        (loop for elt in candidates
              when (eq (class elt) 'method-declaration) return elt)
        (if (eq (class candidates) 'method-declaration)
            candidates))))

;(get-named-procedure-methods-for-class
;                                  (nth 2 root-procedure-name) (nth 1 root-procedure-name))

(defun show-procedure-reference-hierarchy-on-a-workspace (root-procedure-name &optional inspect-command? upward?) ; -pga, 1/11/96
  (let* ((method-p? ())
         (root-procedure (cond ((symbolp root-procedure-name)
                                (get-instance-with-name-if-any 'procedure root-procedure-name))
                               ((eq (car root-procedure-name) 'class-qualified-method)
                                (setq method-p? t)
                                (find-method-declaration-for-name
                                  (nth 2 root-procedure-name))))))
    (if (null root-procedure)
        (notify-user "Cannot show the procedure reference hierarchy for ~a, since it is not a procedure."
                     root-procedure-name)
        (let* ((workspace-with-inspect-command?
                 (if inspect-command?
                     (get-and-clear-workspace-for-inspect-command
                       inspect-command?))))
          (reclaim-graph-display
            (graph-frame-hierarchy
              root-procedure        ; procedure or list of methods
              (if upward?
                  'referencing-procedures-for-graph-display  ; Parent-function
                  'referenced-procedures-for-graph-display) ; Children-function
              (if (and (eq (class root-procedure) 'method-declaration) (listp root-procedure-name))
                  (nth 1 root-procedure-name)
                  inspect-command?)                        ; extra-argument?
              'short-representation-for-ref-hierarchy
              ;hash-function
              'hash-symbol-or-frame
              ;orientation
              'horizontal
              ;vertical-spacing
              1
              ;horizontal-spacing
              50
              ;pane-for-workspace-display?
              (if (null workspace-with-inspect-command?)
                  current-workstation-detail-pane) ; What's this for? do I need it?
              ;class-of-workspace
              nil
              ;workspace?
              (or workspace-with-inspect-command?
                  (make-inspect-workspace inspect-command?))
              ;left-edge-for-graph?
              (if inspect-command?
                  (left-edge-of-block inspect-command?))
              ;top-edge-for-graph?
              (if inspect-command?
                  (+w (bottom-edge-of-block inspect-command?)
                      5))))
          (when workspace-with-inspect-command?
            (shrink-wrap-workspace workspace-with-inspect-command?)
            (put-inspect-workspace-on-current-detail-pane workspace-with-inspect-command?))))))


;;; `put-up-verson-control-inspect-workspace'

(defun put-up-verson-control-inspect-workspace (list-of-strings inspect-command?)
  (let* ((interitem-spacing 20)
         (workspace
           (or (if inspect-command?
                   (get-and-clear-workspace-for-inspect-command
                     inspect-command?))
               (make-inspect-workspace inspect-command?)))
         (workspace-margin (workspace-margin workspace))
         (left-edge-in-workspace
           (+w (left-edge-of-block workspace)
               workspace-margin))
         (top-edge-in-workspace
           (if inspect-command?
               (+w (bottom-edge-of-block inspect-command?)
                   interitem-spacing)
               (+w (top-edge-of-block workspace)
                   workspace-margin))))
    (loop for string in list-of-strings
          as new-text-box = (make-free-text-box string 'free-text) do
      (add-to-workspace
        new-text-box workspace
        left-edge-in-workspace top-edge-in-workspace t)
      (setq top-edge-in-workspace
            (+w (bottom-edge-of-block new-text-box)
                interitem-spacing)))
    (reclaim-gensym-list list-of-strings)
    (shrink-wrap-workspace workspace)
    (put-inspect-workspace-on-current-detail-pane workspace)))


(defun referencing-procedures-for-graph-display (symbol-or-item &optional extra-arg?) ; -pga, 1/12/96
  ;; Caller must reclaim result.
  (let* ((procedure-methods
           (cond ((and (listp symbol-or-item)
                       (eq (car symbol-or-item) 'class-qualified-method))
                  (cdr (get-named-procedure-methods-for-class
                         (nth 2 symbol-or-item) (nth 1 symbol-or-item))))
                 ((and (eq (type-of symbol-or-item) 'simple-vector)
                       (eq (class symbol-or-item) 'method-declaration))
                  (if (symbolp extra-arg?)
                      (cdr (get-named-procedure-methods-for-class
                             (get-primary-name-for-frame-if-any symbol-or-item) extra-arg?))
                      (loop for elt in (compiled-items-referring-to-this-name
                                         (get-primary-name-for-frame-if-any
                                           symbol-or-item))
                            when (eq (class elt) 'method) collect elt using gensym-cons))))))
    (or procedure-methods
        (let* ((items (referencing-items-for-graph-display symbol-or-item extra-arg?)))
          (loop for item in items
                ;; GENSYMCID-1228: g2-get-procedure-caller-hierarchy not working
                when (or (get-instance-with-name-if-any 'procedure (get-primary-name-for-frame-if-any item))
                         (get-instance-with-name-if-any 'method (get-primary-name-for-frame-if-any item)))
                  collect item using gensym-cons)))))

(defun referencing-items-for-graph-display (symbol-or-item &optional inspect-command?) ; -pga, 1/12/96
  inspect-command?
  (if (symbolp symbol-or-item)
      (compiled-items-referring-to-this-name symbol-or-item)
      (compiled-items-referring-to-this-name (get-primary-name-for-frame-if-any symbol-or-item))))

(defun referenced-procedures-for-graph-display (symbol-or-item &optional extra-arg?)        ; -pga, 1/12/96
  ;; Caller must reclaim result.
  (let ((procedure-methods
          (cond ((and (listp symbol-or-item)
                      (eq (car symbol-or-item) 'class-qualified-method))
                 (cdr (get-named-procedure-methods-for-class
                        (nth 2 symbol-or-item) (nth 1 symbol-or-item))))
                ((and (eq (type-of symbol-or-item) 'simple-vector)
                      (eq (class symbol-or-item) 'method-declaration))
                 (if (symbolp extra-arg?)
                     (cdr (get-named-procedure-methods-for-class
                            (get-primary-name-for-frame-if-any symbol-or-item) extra-arg?))
                     (loop for elt in (compiled-items-referring-to-this-name
                                        (get-primary-name-for-frame-if-any
                                          symbol-or-item))
                           when (eq (class elt) 'method) collect elt using gensym-cons))))))
    (or procedure-methods
        (if (symbolp symbol-or-item)
            nil
            (let* ((references (free-references-from-procedure symbol-or-item))
                   (names (loop for ref in references
                                nconcing (extract-procedure-names-from-free-reference-vector ref)))
                   (result (loop for sym in names
                                 for proc? = (get-instance-with-name-if-any 'procedure sym)
                                 when sym collect (or proc? sym) using gensym-cons)))
              (reclaim-gensym-list references)
              (reclaim-gensym-list names)
              result)))))

;;; `free-references-from-procedure' returns a freshly consed gensym-list.  Each
;;; element is a simple-vector of the free-references for each code-body of the
;;; procedure {remember that procedures with "on error" or "do in parallel"
;;; statements have multilpe code-bodies}.  The simple-vectors are owned by the
;;; procedure.

(defun free-references-from-procedure (procedure) ; -pga, 1/12/96
  (let* ((procedure-code-bodies (procedure-code-bodies-3.0-beta procedure)))
    (loop for code-body in procedure-code-bodies
          for byte-code-body = (if code-body (code-body-byte-code-body code-body))
          for free-references = (if byte-code-body (byte-code-body-free-references byte-code-body))
          when free-references collect free-references using gensym-cons)))

;;; `free-reference-list-extractor' returns a freshly consed list using the
;;; specifed conser {gensym-cons if none specified} of the free-references
;;; specified.  Be careful with the contents of the list as whether it's fresh
;;; or shared is dependent on the free-reference-accessor you pass in.
;;;
;;; VECT is the simple-vector containing the free-references
;;;
;;; FREE-REFERENCE is evaluated and expected to return a symbol matching one of
;;; the free-references (like 'inline or 'procedure-call)
;;;
;;; FREE-REFERENCE-ACCESSOR is a symbol which is not evaluated which should
;;; name the accessor to use to get at the "value" of the free-reference.
;;;
;;; The optional CONSER which defaults to gensym-cons is what will be used to
;;; build the list which is returned.  This argument is not evaluated.

(defmacro free-reference-list-extractor
    (vect free-reference free-reference-accessor &optional (conser 'gensym-cons))
  (let ((vect-sym (gensym))
        (index-sym (gensym)))
    `(let ((,vect-sym ,vect))
       (loop for ,index-sym from 0 below (length ,vect-sym) by 2
             when (eq (svref ,vect-sym ,index-sym)
                      ,free-reference)
               collect (,free-reference-accessor (svref ,vect-sym
                                                        (1+f ,index-sym)))
                 using ,conser))))

(defun extract-procedure-names-from-free-reference-vector (free-reference-vector) ; -pga, 1/12/96
  (free-reference-list-extractor free-reference-vector 'procedure-call car))

(defun possibly-qualified-inlined-name (free-reference)
  (make-slot-name-denotation (cadr free-reference)
                             (car free-reference)
                             gensym-cons))

(defun extract-inlined-procedures-from-free-reference-vector (free-reference-vector)
  (free-reference-list-extractor
    free-reference-vector 'inline possibly-qualified-inlined-name))





;;;; Searching in KB and Substituting in Tables, part 1

(defvar current-remote-search-representation? nil)

;;; A `kb search state' ...

(def-class (kb-search-state entity)

  (kb-search-status?
    nil (type kb-state-search-status) system vector-slot
    not-user-editable
    do-not-identify-in-attribute-tables) ; mostly to save space

  (kb-search-results-workspace nil system vector-slot)        ; a temporary workspace
  (frame-serial-number-for-kb-search-results-workspace
    nil system vector-slot)

  (frames-for-kb-search nil system vector-slot)
  (frame-serial-number-for-kb-search
    nil system vector-slot)

  (item-filter-for-kb-search?
    nil (type item-filter?)
    system vector-slot not-user-editable)

  (string-to-look-for?                                ; for tables cases only
    nil system vector-slot not-user-editable)
  (replacement-string?                                ; for tables substitution only
    nil system vector-slot not-user-editable)
  (observance-of-word-boundary?                        ; always hidden
    nil system vector-slot not-user-editable)

  (total-number-of-items-to-examine
    0 (type integer) system vector-slot not-user-editable)
  (number-of-items-examined-so-far
    0 (type integer) system vector-slot not-user-editable)
  (number-of-substitutions-in-tables                ; for tables substitution only
    0 system vector-slot not-user-editable)
  (number-of-resulting-parsing-failures                ; for tables substitution only
    0 system vector-slot not-user-editable)
  (number-of-items-found
    0 (type integer) system vector-slot not-user-editable)
  (number-of-occurrences-in-tables                ; for tables cases only
    0 system vector-slot not-user-editable)

  (file-name-for-printing-search-results?
    nil system vector-slot not-user-editable)
  (ascii-file-name-for-printing-search-results?
    nil system vector-slot not-user-editable
    do-not-put-in-attribute-tables)
  (file-stream-for-printing-search-results?
    nil system vector-slot not-user-editable)

  (visit-items-when-found?                        ; true => goes to item
    nil system vector-slot not-user-editable)        ;   found [only 1st at present]

  (time-at-start-of-search?
    nil system vector-slot not-user-editable)

  (time-of-last-table-update?
    nil system vector-slot not-user-editable)

  (display-a-table?                                ; nil, COLUMNWISE, or non-
    nil system vector-slot not-user-editable)        ;   nil (=> rowwise)
  (table-rows-for-showing-as-a-table?
    nil system vector-slot not-user-editable)
  (denotations-of-slots-shown-as-a-table?
    nil system vector-slot not-user-editable)
  (slot-denotations-for-showing-as-a-table?
    nil system vector-slot not-user-editable)

  (old-kb-search-result-tables-and-text-boxes        ; list of frames; check for reprocessing
    nil system vector-slot not-user-editable)        ;   using frame-serial-number-for-kb-search

  (left-edge-for-next-kb-search-result-block        ; workspace coordinates
    0 system vector-slot not-user-editable)
  (top-edge-for-next-kb-search-result-block
    0 system vector-slot not-user-editable)

  (subcommand-menu-for-kb-search?
    nil system vector-slot not-user-editable)
  (frame-serial-number-for-subcommand-menu-for-kb-search?
    nil system vector-slot not-user-editable)
  (inspect-command-for-kb-search?
    nil system vector-slot not-user-editable)
  (frame-serial-number-for-inspect-command-for-kb-search?
    nil system vector-slot not-user-editable)

  (recompile-found-items?
    nil system vector-slot not-user-editable)

  (no-results-tables?                                ; to keep resulting tables from
    nil system vector-slot not-user-editable)        ;   being put on the workspace


  (file-operation-complete-or-error-string?        ; nil, t, or a string explaining
    nil system vector-slot not-user-editable)        ;   failure.
                                                ; MOVE SLOT UP! (MHD 9/12/91)



  (initial-top-edge-for-kb-search-result-tables        ; 2/13/92: for multicolumns
    nil system vector-slot not-user-editable)

  (maximum-bottom-edge-for-kb-search-result-tables        ; 2/13/92: for multicolumns
    nil system vector-slot not-user-editable)

  (maximum-right-edge-of-kb-search-result-tables-so-far
    nil system vector-slot not-user-editable)

  (number-of-kb-search-result-tables-in-this-column-so-far        ; 2/13/92: for multicolumns
    nil system vector-slot not-user-editable)

  (maximum-height-for-row-of-kb-search-result-tables        ; ultimately, parameterize for users?!
    10000 system vector-slot not-user-editable)

  (minimum-number-of-kb-search-result-tables-per-column        ; ultimately, parameterize for users?!
    1 system vector-slot not-user-editable)        ; never should be less than 1; if
                                                ;   parameterized, positive-integer

  (spacing-between-search-result-blocks
    5 system vector-slot not-user-editable)

  (items-with-suppressed-warning-notes?           ; a list of slot-value cons'd frames
    nil system vector-slot not-user-editable)  ; that were recompiled and had notes

  (kb-search-state-invisible-p
    nil system vector-slot not-user-editable)

  (kb-search-state-no-time-slice-expiration-p
    nil system vector-slot not-user-editable)

  (kb-search-state-remote-representation?
    nil system vector-slot not-user-editable))


(def-class-method initialize (kb-search-state)
  (funcall-superior-method kb-search-state)
  (let ((cloning? (cell-array kb-search-state)))
    (unless cloning?
      (initialize-slot-value kb-search-state 'cell-array (make-frame 'g2-cell-array)))))


;;; The `cleanup' method on kb-search-state objects is called just before
;;; they are deleted. At present the only thing to do that's specific
;;; to a search state is check whether any warnings about frames notes
;;; made during a recompile are still waiting to be posted.

(def-class-method cleanup (kb-search-state)
  (funcall-superior-method kb-search-state)
  (do-inspector-suppressed-warnings-notes kb-search-state))


(def-class-method activate (kb-search-state)
  (let ((current-block-of-dependent-frame kb-search-state))
    (unless in-suspend-resume-p
      (activate-g2-cell-array (cell-array kb-search-state)))
    (funcall-superior-method kb-search-state)))

(def-class-method deactivate (kb-search-state)
  (let ((current-block-of-dependent-frame kb-search-state))
    (unless in-suspend-resume-p
      (deactivate-g2-cell-array (cell-array kb-search-state)))
      (funcall-superior-method kb-search-state)))

(define-slot-alias items-to-examine total-number-of-items-to-examine)
(define-slot-alias items-examined-so-far number-of-items-examined-so-far)
(define-slot-alias status kb-search-status? kb-search-state)
(define-slot-alias filter item-filter-for-kb-search? kb-search-state)

(def-slot-value-reclaimer file-stream-for-printing-search-results? (stream? kb-search-state)
  (if stream?
      (setf (file-stream-for-printing-search-results?        ; set nil for safety
              kb-search-state)
            (prog1
              nil
              (close-file-for-search-results stream?)))))

;;; we reclaim the serial number here, rather than in their own slot value reclaimers, to ensure that
;;; they are reclaimed after this reclaimer runs, rather than before.
(def-slot-value-reclaimer old-kb-search-result-tables-and-text-boxes (value kb-search-state)
  (when value
    (loop with frame-serial-number
            = (frame-serial-number-for-kb-search kb-search-state)
          for table in value
          unless (frame-has-been-reprocessed-p table frame-serial-number)
            do (delete-frame table)
          finally
            (reclaim-slot-value-list value)))
  (reclaim-frame-serial-number (frame-serial-number-for-kb-search kb-search-state))
  (setf (frame-serial-number-for-kb-search kb-search-state) nil))

(def-slot-value-reclaimer frame-serial-number-for-kb-search (serial-number)
  ;; already reclaimed above
  (declare (ignore serial-number))
  nil)

(def-slot-value-reclaimer frame-serial-number-for-kb-search-results-workspace (serial-number kb-search-state)
  (reclaim-frame-serial-number serial-number)
  (setf (frame-serial-number-for-kb-search-results-workspace kb-search-state) nil))

(def-slot-value-reclaimer frame-serial-number-for-subcommand-menu-for-kb-search? (serial-number kb-search-state)
  (reclaim-frame-serial-number serial-number)
  (setf (frame-serial-number-for-subcommand-menu-for-kb-search? kb-search-state) nil))

(def-slot-value-reclaimer frame-serial-number-for-inspect-command-for-kb-search? (serial-number kb-search-state)
  (reclaim-frame-serial-number serial-number)
  (setf (frame-serial-number-for-inspect-command-for-kb-search? kb-search-state) nil))

(def-class-method denote-cell-array-element
                  (kb-search-state cell-index include-denotation-for-block)
  (declare (ignore kb-search-state cell-index include-denotation-for-block))
  (twrite-string "this filter")
  (denote-component-of-block-1 '*current-computation-frame* " of "))

(def-slot-value-writer item-filter? (item-filter? kb-search-state)
  ;; The following loop write string-to-write after skipping
  ;; the #\space characters therein.  (Should be fixed to
  ;; skip all whitespace, e.g., @L, and abstracted!)
  (loop with string-to-twrite = (cdr item-filter?)
        for i from 0 below (lengthw string-to-twrite)
        when (not (char=w (charw string-to-twrite i) #.%space))
          return
            (let ((temporary-text-string
                    (text-string-substring string-to-twrite i nil)))
              (twrite-string temporary-text-string)
              (reclaim-text-string temporary-text-string)))
  (let ((frame-notes-for-component-particulars
          (get-particulars-of-frame-note-if-any
            'frame-notes-for-component-particulars
            kb-search-state)))
    (when frame-notes-for-component-particulars
      (tformat "~%~%but ")
      (funcall-simple-compiled-function
        (frame-note-writer 'frame-notes-for-component-particulars)
        frame-notes-for-component-particulars
        kb-search-state))))


(def-slot-value-writer kb-state-search-status (arbitrary-value kb-search-state)
  (declare (ignore arbitrary-value))
  (cond
    ((and (file-name-for-printing-search-results? kb-search-state)
          (null (file-stream-for-printing-search-results?
                  kb-search-state))
          (or (null (file-operation-complete-or-error-string? kb-search-state))
              (text-string-p (file-operation-complete-or-error-string? kb-search-state))))
     (tformat "File operation ... ")
     (when (file-operation-complete-or-error-string? kb-search-state)
       (tformat
         "FAILED!  (~a)"
         (file-operation-complete-or-error-string? kb-search-state))))
    ((not (=f (total-number-of-items-to-examine kb-search-state)
              (number-of-items-examined-so-far kb-search-state)))
     (tformat "Searching ... [Seconds elapsed: ~d]"
              (convert-fixnum-time-difference-to-seconds
                (fixnum-time-difference
                  (get-fixnum-time)
                  (time-at-start-of-search? kb-search-state)))))
    (t
     (let ((number-of-seconds
             (convert-fixnum-time-difference-to-seconds
               (fixnum-time-difference
                 (get-fixnum-time)
                 (time-at-start-of-search? kb-search-state)))))
       (tformat "Search took ~D second~A.  "
                number-of-seconds (if (=f number-of-seconds 1) "" "s")))
     (tformat
       "~D item~A ~A found."
       (number-of-items-found kb-search-state)
       (if (=f (number-of-items-found kb-search-state) 1) "" "s")
       (if (=f (number-of-items-found kb-search-state) 1) "was" "were")))))




;;; A `file output search state' ... the file-name-for-printing-search-results?
;;; slot is in the Gensym character set and must be converted to ASCII (as with
;;; convert-text-string-to-ascii-filename-as-much-as-possible) before being
;;; passed to the gensym-pathnames or g2-stream facilities ...

(def-class (file-output-search-state kb-search-state)
  (file-name-for-printing-search-results?
    nil (type whole-string?) system vector-slot not-user-editable do-not-save))

(define-slot-alias name-of-file-with-results file-name-for-printing-search-results?
  file-output-search-state)


;; Modified by ML. Added do-not-save to the result. 3/24/91


;;; A `tables search state' ...

(def-class (tables-search-state kb-search-state)

  (string-to-look-for?
    nil (type whole-string?) system vector-slot not-user-editable do-not-save)

  (number-of-occurrences-in-tables
    0 (type integer) system vector-slot not-user-editable do-not-save))

(define-slot-alias string-to-look-for string-to-look-for?
  tables-search-state)

(define-slot-alias items-with-occurrences number-of-items-found
  tables-search-state)

(define-slot-alias occurrences number-of-occurrences-in-tables
  tables-search-state)



;;; A `tables substitution state' ...

;;; Note that the number-of-occurrences-in-tables slot will not reflect
;;; substitutions in which the parser has inserted ellipses.

(def-class (tables-substitution-state kb-search-state)

  (string-to-look-for?
    nil (type whole-string?) system vector-slot not-user-editable do-not-save)
  (replacement-string? nil (type whole-string?)
                       system vector-slot not-user-editable do-not-save)

  (number-of-substitutions-in-tables
    0 (type integer) system vector-slot not-user-editable do-not-save)
  (number-of-resulting-parsing-failures
    0 (type integer) system vector-slot not-user-editable do-not-save)
  (number-of-occurrences-in-tables
    0 (type integer) system vector-slot not-user-editable do-not-save))

(define-slot-alias string-to-replace string-to-look-for?
  tables-substitution-state)

(define-slot-alias replacement-string replacement-string?)

(define-slot-alias substitutions-made number-of-substitutions-in-tables)

(define-slot-alias resulting-parsing-failures number-of-resulting-parsing-failures)

(define-slot-alias items-containing-replacement-string number-of-items-found
  tables-substitution-state)

(define-slot-alias occurrences-of-replacement-string number-of-occurrences-in-tables
  tables-substitution-state)

;; Consider allowing string-to-look-for?, replacement-string?, and observe-word-
;; boundaries? to be user-editable.



(def-class (special-purpose-kb-search-state kb-search-state)
  (special-purpose-kb-search-function? nil not-user-editable do-not-save)
  (special-purpose-kb-search-arglist? nil not-user-editable do-not-save))





;;; `Get-search-state-for-inspect-command-results-if-any' maps an inspect
;;; command to its corresponding search state, if any.  If there is none, or
;;; if it is deleted, this returns nil.
;;;
;;; `Get-results-workspace-for-search-state-if-any' maps a kb-search-state
;;; instance to its corresponding workspace, if any. If there is none, or if
;;; it is delete, this returns nil.

(defun-simple get-search-state-for-inspect-command-results-if-any (inspect-command)
  (let ((search-state?
         (search-state-for-inspect-command? inspect-command))
        (serial-number
         (frame-serial-number-for-inspect-command-search-state?
           inspect-command)))
    (when (and search-state?
               (not (frame-has-been-reprocessed-p search-state? serial-number)))
      search-state?)))

(defun-simple get-results-workspace-for-search-state-if-any (search-state)
  (let ((workspace (kb-search-results-workspace search-state)))
    (cond ((kb-search-state-invisible-p search-state)
           nil)
          ((not (frame-has-been-reprocessed-p
                  workspace
                  (frame-serial-number-for-kb-search-results-workspace
                    search-state)))
           workspace)
          (t
           nil))))






;;;; Suppressing Logbook Notifications During Recompiles Initiated by Inspect


;;; The dynamic extent `recompile-from-inspect' is largely a placeholder
;;; for the state information we anticipate we'll want as the options
;;; for what to do with the results of a recompilation are explored
;;; (especially for the case when a great many frames or notes are
;;; involved). Right now it just maintains flags that override the normal
;;; behavior of some facility when it is being called within the scope
;;; of a recompile.

;;; The variable `suppress-consistency-analysis-warnings-notes?' blocks just
;;; the notification of any problem with the consistency analysis by gating
;;; the processing in post-analyzer-warning-note-if-necessary.

;;; The variable `do-not-update-frame-authors?' is read in update-authors-
;;; and-time-of-frame-edit and as it says, keeps that function from doing
;;; its update. If this weren't done, then whenever a person loaded a kb
;;; that needed a recompile they would become the new author of the kb's
;;; frames, losing the information about who had actually written them.


(def-dynamic-extent (recompile-from-inspect
                      (module queries))
  (suppress-consistency-analysis-warnings-notes? (global-binding nil))
  (do-not-update-frame-authors? (global-binding nil)))




(defmacro with-recompile-from-inspect-environment (&body body)
  `(with-named-dynamic-extent recompile-from-inspect
       ((suppress-consistency-analysis-warnings-notes? t)
        (do-not-update-frame-authors? t))
     ,@body ))





;;; `Note-frame-for-inspector-suppressed-warnings' is called from the inspector
;;; in search-items-a-little when a frame is being recompiled. In conjunction
;;; with the flag suppress-consistency-analysis-warnings-notes?, this delays the
;;; notification of consistency analysis warnings until the search has been
;;; completed. When recompiling a whole kb this will eliminate warnings that
;;; are transient in that the note of the frame will be resolved and removed
;;; as later elements of the kb are processed.

(defun note-frame-for-inspector-suppressed-warnings (frame kb-search-state)
  (macrolet
      ((add-frame-to-suppressed-warning-list (frame)
         `(setf (items-with-suppressed-warning-notes? kb-search-state)
                (slot-value-cons
                  ,frame (items-with-suppressed-warning-notes? kb-search-state)))))
    (let ( embedded-rule? )
      (cond ((frame-of-class-p frame 'action-button)
             (setq embedded-rule? (embedded-rule?-function frame))
             (when embedded-rule?
               (add-frame-to-suppressed-warning-list embedded-rule?)))
            ((frame-of-class-p frame 'user-menu-choice)
             (setq embedded-rule? (embedded-rule-in-user-menu-choice? frame))
             (when embedded-rule?
               (add-frame-to-suppressed-warning-list embedded-rule?)))))
    (add-frame-to-suppressed-warning-list frame)))

;; The action button and menu choice are the only frames that we now have that
;; can be embedded, and yet are not (supposed to be) user visible.  C.f.,
;; simulation-subtables, which are embedded, but users can explicitly get to
;; them, and we'd be happy to show them.  I think that we think that such full
;; items will appear as separate top-level items in a list of items to
;; recompile. (MHD/DDM 1/31/97)



;;; `Clear-suppressed-warnings-cache-if-necessary' is needed so that
;;; when the search state is being deleted we can tell whether the warnings
;;; have been posted yet. Whether the slot has a value or not seems to be
;;; a simple way of providing this state information.

(defun clear-suppressed-warnings-cache-if-necessary (kb-search-state)
  (let ((list (items-with-suppressed-warning-notes? kb-search-state)))
    (when list
      (setf (items-with-suppressed-warning-notes? kb-search-state) nil)
      (reclaim-slot-value-list list))))



;;; `Do-inspector-suppressed-warnings-notes' takes the frames off the list and sends
;;; them through post-analyzer-warning-note-if-necessary again. This time the notes
;;; will go through because the flag that inhibits them is down.

(defun do-inspector-suppressed-warnings-notes (kb-search-state)
  (when (items-with-suppressed-warning-notes? kb-search-state)
    (let ((add-as-item-referring-to-name? t) ; see note
          (reference-serial-number (frame-serial-number-for-kb-search kb-search-state)))
      (loop for frame in (items-with-suppressed-warning-notes? kb-search-state)
            unless (frame-has-been-reprocessed-p frame reference-serial-number)
              do (post-analyzer-warning-note-if-necessary frame))))
  (clear-suppressed-warnings-cache-if-necessary kb-search-state))

;; This is the locus that all the notifications go through during an inspect-
;; generated recompile. Consider some alternatives to just sending this whole
;; set to the logbook as had been the practice in the past (incrementally)
;; and this code is doing now:
;;   -  Summarize the problems rather than make a logbook message for
;;      each one, e.g. one logbook message listing all the problematic
;;      frames, or if there is a zillion of them, post the number and
;;      the recipe to use with inspect in order to view them.
;;
;;   -  Post the problematic frames on the inspect workspace in a manner
;;      similar to the one used by go-to. If clicking on them would not
;;      only bring them to the top but also open their table or otherwise
;;      display their notes (or just the problematic one(s)), so much
;;      the better.  Another presentation possibility is an independent
;;      workspace like the one used to present the sequence of modules
;;      that will be loaded.

;; Note: We're binding add-as-item-referring-to-name? because it is one of
;; the gating flags in post-analyzer-warning-note-if-necessary. It is part of
;; the dynamic extent analyze-for-consistency-in-progress and is T when the
;; analysis is in name-registration mode. See documentation in Install.




;;; `Summarize-inspector-suppressed-warnings-if-any' is called when the search
;;; has been suspended and we want to give an indication that there are
;;; warnings pending without actually doing the full posting.

(defun summarize-inspector-suppressed-warnings-if-any (kb-search-state)
  (when (items-with-suppressed-warning-notes? kb-search-state)
    (let ((length (length (items-with-suppressed-warning-notes? kb-search-state))))
      (if (=f 1 length)
          (notify-user
            "Inspect was suspended while recompiling, but there was an item ~
             with notes.")
          (notify-user
            "Inspect was suspended while recompiling, but there were ~d ~
             items with notes."
            length)))))

;; The whole point of this deferal mechanism is that during the recompilation
;; there can be more frames with notes that will prompt notifications than there
;; will be at the end because some of them are artifacts of the order in which
;; the elements of the kb are loaded. Should that be indicated in this message?
;; ("..that may have pending warnings"), or should we not worry that this number
;; will change and is probably larger than the final set of notifications?






;;;; Searching in KB and Substituting in Tables, part 2


;;; `Multiple-add-to-results-for-inspect-command' takes an eval list of
;;;  items and strings and (unless running invisibly, adds text-boxes or
;;;  short-representations(resectively) to commands results workspace(if it has one).
;;;  Sends the list to any remote inspect clients as well.
;;;  Reclaims the eval list items-or-strings?

(defun-void multiple-add-to-results-for-inspect-command (items-or-strings?
                                                         inspect-command)
  (loop with search-state?
          = (get-search-state-for-inspect-command-results-if-any inspect-command)
        with remotep
          = (and search-state?
                 (kb-search-state-remote-representation? search-state?))
        with invisiblep
          = (run-command-invisibly-p inspect-command)
        for item-or-string in items-or-strings?
        do
    (cond ((text-string-p item-or-string)
           (cond ((and (not invisiblep) remotep) ;;both using the string
                  #+development
                  (cerror "continue" "Why is there a visible remote inspect command?")
                  (setq item-or-string (copy-text-string item-or-string)))
                 ((and invisiblep (not remotep)) ;;neither using the string
                  (reclaim-text-string item-or-string)))
           (unless invisiblep
             (add-to-inspect-search-results (make-message item-or-string) search-state?)))
          (t
           (add-to-inspect-search-results (make-short-representation item-or-string nil nil) search-state?)))
        finally
          (cond (remotep
                 (when items-or-strings?
                   (return-remote-query-results search-state? items-or-strings? nil)))
                (t
                 (reclaim-eval-list items-or-strings?)))))

(defun-void add-to-inspect-search-results (text-box-or-table search-state)
  (let ((workspace? (get-results-workspace-for-search-state-if-any search-state)))
    (when workspace?
      (when (and (not
                   (<f
                     (number-of-kb-search-result-tables-in-this-column-so-far search-state)
                     (minimum-number-of-kb-search-result-tables-per-column search-state)))
                 (>w (+w (top-edge-for-next-kb-search-result-block search-state)
                         (height-of-block text-box-or-table))
                     (maximum-bottom-edge-for-kb-search-result-tables search-state)))
        (setf (top-edge-for-next-kb-search-result-block search-state)
              (initial-top-edge-for-kb-search-result-tables search-state))
        (setf (left-edge-for-next-kb-search-result-block search-state)
              (+w (maximum-right-edge-of-kb-search-result-tables-so-far search-state)
                  10))
        (setf (number-of-kb-search-result-tables-in-this-column-so-far search-state) 0))
      (add-to-workspace
        text-box-or-table (kb-search-results-workspace search-state)
        (left-edge-for-next-kb-search-result-block search-state)
        (top-edge-for-next-kb-search-result-block search-state)
        t t)
      (setf (top-edge-for-next-kb-search-result-block search-state)
            (+w (bottom-edge-of-block text-box-or-table)
                (spacing-between-search-result-blocks search-state)))
      (setf (maximum-right-edge-of-kb-search-result-tables-so-far search-state)
            (maxw (right-edge-of-block text-box-or-table)
                  (maximum-right-edge-of-kb-search-result-tables-so-far search-state)))
      (incff (number-of-kb-search-result-tables-in-this-column-so-far search-state)))))





;;; `Search-items' ...

;;; Frames should be a slot value list of frames, the conses of which are
;;; reclaimed by this function.

;;; Item-filter-for-kb-search?, if non-nil, should have only reclaimable slot
;;; value conses and text strings; it is to be reclaimed via reclaim-slot-value.

;;; String-to-look-for? and replacement-string? are copied by this function; the
;;; caller is therefore responsible for reclaiming them as necessary.  Whenever
;;; replacement-string? is specified, string-to-look-for? must also be specified.
;;; ...

;;; Search-items expects to be called in a for-workstation context.

;;; Results-file-name? if non-nil, is a gensym-pathname that specifies the name of
;;; a file to open and in which to print results.  Whenever string-to-look-for?
;;; is specified, however, results-file-name? cannot be specified.  Results-
;;; file-name? is owned by the caller, i.e., never recycled by this function.

;;; Inspect-command?, if specified, is used to mean that this should do some
;;; tasks for the Inspect facility, including (1) finding the workspace the
;;; inspect-command? is on, (2) using that workspace as the results workspace,
;;; (3) deleting all subblocks on that workspace except for its workspace name
;;; box and inspect command, (4) when writing to file, handing the inspect
;;; command to the file header printer so that its text will be included in the
;;; output, and (5) putting backpointers to the kb search state that
;;; search-items creates into inspect-command?, descheduling and deleting a
;;; previously pointed to kb search state, if there is one.

;;; Visit?, if specified, means that all items should be "visited", meaning
;;; that the equivalent of the user menu choice go-to-original be executed
;;; on each item found.

;;; If display-a-table? is specified, a table of the search results is
;;; displayed, and, if display-a-table? is COLUMNWISE, the items are put
;;; into columns, and otherwise are put into rows.  Also when display-a-
;;; table? is specified, slot-denotations-for-showing-as-a-table? is used to
;;; limit the slots shown in the table.  Also when display-a-table? is
;;; specified, string-to-look-for?,  replacement-string?, and observe-word-
;;; boundaries? are ignored.

(defun search-items
       (frames item-filter-for-kb-search?
        string-to-look-for? replacement-string? observance-of-word-boundary?
        &optional
        no-results-tables? results-file-name? ascii-results-file-name?
        inspect-command? visit?
        display-a-table? slot-denotations-for-showing-as-a-table?
        recompile-found-items?
        special-purpose-function? special-purpose-arglist?)
  (let ((kb-search-state
         (create-kb-search-state
           frames item-filter-for-kb-search?
           string-to-look-for? replacement-string? observance-of-word-boundary?
           no-results-tables? results-file-name? ascii-results-file-name?
           inspect-command? visit?
           display-a-table? slot-denotations-for-showing-as-a-table?
           recompile-found-items? special-purpose-function? special-purpose-arglist?)))
    (setf (kb-search-state-no-time-slice-expiration-p kb-search-state)
          (and inspect-command?
               (run-command-to-completion-p inspect-command?)))
    (setf (kb-search-state-invisible-p kb-search-state)
          (and inspect-command?
               (run-command-invisibly-p inspect-command?)))
    (setf (kb-search-state-remote-representation? kb-search-state)
          (and inspect-command?
               (run-command-remotely-p inspect-command?)
               current-remote-search-representation?))
    (search-items-a-little
      kb-search-state (frame-serial-number kb-search-state))))


;;; `Set-kb-search-state-for-inspect-command' ...

(defun set-kb-search-state-for-inspect-command (inspect-command kb-search-state)
  (cancel-search-state-for-inspect-command-if-necessary inspect-command)
  (setf (search-state-for-inspect-command? inspect-command) kb-search-state)
  (frame-serial-number-setf (frame-serial-number-for-inspect-command-search-state? inspect-command)
                            (frame-serial-number kb-search-state)))


;;; `Create-kb-search-state' returns an instance of a kb-search-state configured
;;; based on the arguments, and ready for use by search-items-a-little.

(defun create-kb-search-state
    (frames item-filter-for-kb-search?
            string-to-look-for? replacement-string? observance-of-word-boundary?
            no-results-tables? results-file-name? ascii-results-file-name?
            inspect-command? visit?
            display-a-table? slot-denotations-for-showing-as-a-table?
            recompile-found-items?
            special-purpose-function? special-purpose-arglist?)
  (let ((kb-search-state
          (make-frame
            (cond
              (replacement-string? 'tables-substitution-state)
              (string-to-look-for? 'tables-search-state)
              (results-file-name? 'file-output-search-state)
              (special-purpose-function? 'special-purpose-kb-search-state)
              (t 'kb-search-state)))))


    (frame-serial-number-setf (frame-serial-number-for-kb-search kb-search-state)
                              (current-frame-serial-number))
    (setf (frames-for-kb-search kb-search-state)
          (copy-list-using-slot-value-conses frames))
    (setf (total-number-of-items-to-examine kb-search-state)
                                        ; compute when copy?
          (length (frames-for-kb-search kb-search-state)))


    (setf (no-results-tables? kb-search-state) no-results-tables?)

    (setf (recompile-found-items? kb-search-state) recompile-found-items?)

    (setf (file-name-for-printing-search-results? kb-search-state)
          results-file-name?)
    (setf (ascii-file-name-for-printing-search-results? kb-search-state)
          ascii-results-file-name?)

    (setf (time-of-last-table-update? kb-search-state)
          (setf (time-at-start-of-search? kb-search-state)
                (get-fixnum-time)))

    (setf (visit-items-when-found? kb-search-state) visit?)

    (setf (display-a-table? kb-search-state) display-a-table?)
    (setf (slot-denotations-for-showing-as-a-table? kb-search-state)
          slot-denotations-for-showing-as-a-table?)

    (when item-filter-for-kb-search?
      (compile-item-filter-into-kb-search-state
        item-filter-for-kb-search?
        kb-search-state))

    (setf (string-to-look-for? kb-search-state)
          (if string-to-look-for?
              (copy-text-string string-to-look-for?)))
    (setf (replacement-string? kb-search-state)
          (if replacement-string?
              (copy-text-string replacement-string?)))
    (setf (observance-of-word-boundary? kb-search-state)
          observance-of-word-boundary?)

    (when (frame-of-class-p kb-search-state 'special-purpose-kb-search-state)
      (setf (special-purpose-kb-search-function? kb-search-state)
            special-purpose-function?)
      (setf (special-purpose-kb-search-arglist? kb-search-state)
            special-purpose-arglist?))

    (when inspect-command?
      (set-kb-search-state-for-inspect-command inspect-command? kb-search-state))

    (unless (and inspect-command?
                 (run-command-invisibly-p inspect-command?))
      (set-kb-search-results-workspace kb-search-state inspect-command?))

    kb-search-state))



;;; `Compile-item-filter-into-kb-search-state' is a subfunction of
;;; create-kb-search-state, which is used to set the item-filter-for-kb-search?
;;; slot in kb-search-state to item-filter and to "compile" item-filter, as
;;; follows.
;;;
;;; When this is called, item-filter looks like
;;;
;;;   ((<query-kind> <class> <predicate>) . <source-text>)
;;;
;;; This replaces <predicate> with a <cell-index>.
;;;
;;; Notes that may be relevant (e.g., a free reference to an unknown variable in
;;; a "such that" clause) are handled with frame notes attached to
;;; kb-search-state.  However, notifications to the logbook that notes have been
;;; posted are suppressed, since the notes are not in permanent KB objects that
;;; can be gone to, and since the user is looking right at the table typically,
;;; and therefore doesn't need notification.
;;;
;;; This does not return any useful values at present.

(defun compile-item-filter-into-kb-search-state (item-filter kb-search-state)
  (with-phrase-conses
    (let* ((current-block-of-dependent-frame kb-search-state)
           (*current-computation-frame* current-block-of-dependent-frame)
           (current-annotated-frame current-block-of-dependent-frame))
      (setf (item-filter-for-kb-search? kb-search-state) item-filter)
      (let ((predicate-expression (third (car item-filter))))
        (setf (third (car item-filter))
              (let ((post-compiler-warning-note? nil))
                (compile-a-compiled-cell-expression-from-expression-parse-and-style-description
                  predicate-expression
                  '(computation-style-description
                    may-provide-data-on-request nil
                    may-request-event-updates nil
                    update-after-edits nil
                    update-only-when-shown nil)
                  '(or truth-value (unknown-datum)))))
        (reclaim-slot-value predicate-expression)))))





;;; `Set-kb-search-results-workspace' is a subfuction of create-kb-search-state
;;; that sets up a workspace for the results of the kb search based on
;;; the supplied kb-search-state and inspect-command?, if any.
;;;
;;; This returns no useful values.

(defun set-kb-search-results-workspace (kb-search-state inspect-command?)
  (let* ((kb-search-results-workspace
          (or (if inspect-command?
                  (get-and-clear-workspace-for-inspect-command
                    inspect-command? kb-search-state))
              (make-inspect-workspace inspect-command?)))
         (table-for-kb-search-state
          (make-attributes-table
            kb-search-state
            'search-state-table-format
            nil nil nil
            ;; specifically suppress class, notes, names, user
            ;;   restrictions instead?
            '(item-filter-for-kb-search?
              string-to-look-for? replacement-string?
              observance-of-word-boundary? total-number-of-items-to-examine
              number-of-items-examined-so-far
              number-of-substitutions-in-tables
              number-of-resulting-parsing-failures
              number-of-items-found number-of-occurrences-in-tables
              file-name-for-printing-search-results? kb-search-status?)))
         (subcommand-menu
          (make-subcommand-menu
            (slot-value-list 'hide 'suspend 'continue 'rerun 'edit))))
    (setf (kb-search-results-workspace kb-search-state)
          kb-search-results-workspace)
    (frame-serial-number-setf (frame-serial-number-for-kb-search-results-workspace
                                kb-search-state)
                              (frame-serial-number kb-search-results-workspace))

    (setf (left-edge-for-next-kb-search-result-block kb-search-state)
          (+w (left-edge-of-block kb-search-results-workspace)
              (workspace-margin kb-search-results-workspace)))
    (setf (top-edge-for-next-kb-search-result-block kb-search-state)
          (+w (loop for subblock being each subblock of kb-search-results-workspace
                    maximize (bottom-edge-of-block subblock))
              5))
    (add-to-workspace
      subcommand-menu kb-search-results-workspace
      (-w (left-edge-of-block inspect-command?)
          (workspace-margin kb-search-results-workspace)
          (width-of-block subcommand-menu))
      (top-edge-of-block inspect-command?))
    (setf (subcommand-function? subcommand-menu) 'finish-inspect-subcommand)
    (setf (subcommand-function-arglist? subcommand-menu)
          (slot-value-list
            inspect-command? (copy-frame-serial-number (frame-serial-number inspect-command?))
            kb-search-state (copy-frame-serial-number (frame-serial-number kb-search-state))))
    (setf (subcommand-function-arglist-reclaimer? subcommand-menu) #'reclaim-finish-inspect-subcommand-arglist)
    (enable-or-disable-subcommand subcommand-menu 'hide nil)
    (enable-or-disable-subcommand subcommand-menu 'suspend nil)
    (enable-or-disable-subcommand subcommand-menu 'continue t)
    (enable-or-disable-subcommand subcommand-menu 'rerun nil)
    (enable-or-disable-subcommand subcommand-menu 'edit nil)
    (setf (subcommand-menu-for-kb-search? kb-search-state) subcommand-menu)
    (frame-serial-number-setf (frame-serial-number-for-subcommand-menu-for-kb-search? kb-search-state)
                              (frame-serial-number subcommand-menu))
    (setf (inspect-command-for-kb-search? kb-search-state)
          inspect-command?)
    (frame-serial-number-setf (frame-serial-number-for-inspect-command-for-kb-search?
                                kb-search-state)
                              (frame-serial-number inspect-command?))
    (add-to-workspace
      table-for-kb-search-state kb-search-results-workspace
      (left-edge-for-next-kb-search-result-block kb-search-state)
      (top-edge-for-next-kb-search-result-block kb-search-state)
      t t)
    (setf (top-edge-for-next-kb-search-result-block kb-search-state)
          (+w (bottom-edge-of-block table-for-kb-search-state)
              60))

    ;; 2/13/92: for multicolumns
    (setf (initial-top-edge-for-kb-search-result-tables kb-search-state)
          (top-edge-for-next-kb-search-result-block kb-search-state))
    (setf (maximum-bottom-edge-for-kb-search-result-tables kb-search-state)
          (+w (top-edge-for-next-kb-search-result-block kb-search-state)
              (maximum-height-for-row-of-kb-search-result-tables kb-search-state)))
    (setf (maximum-right-edge-of-kb-search-result-tables-so-far kb-search-state)
          (left-edge-for-next-kb-search-result-block kb-search-state))
    (setf (number-of-kb-search-result-tables-in-this-column-so-far kb-search-state)
          0)
    (put-inspect-workspace-on-current-detail-pane kb-search-results-workspace)))




;;; `Search-items-a-little' ... called in a for-workstation context, either
;;; by search-items or by service-workstation. ...

(defun search-items-a-little (kb-search-state frame-serial-number)
  (if (not (frame-has-been-reprocessed-p kb-search-state frame-serial-number))
      (loop with kb-search-results-workspace
              = (get-results-workspace-for-search-state-if-any kb-search-state)
            with item-filter-for-kb-search?
              = (item-filter-for-kb-search? kb-search-state)
            with string-to-look-for? = (string-to-look-for? kb-search-state)
            with replacement-string? = (replacement-string? kb-search-state)
            with observance-of-word-boundary? = (observance-of-word-boundary? kb-search-state)
            with file-stream-for-printing-search-results?
              = (file-stream-for-printing-search-results? kb-search-state)
            with table? = nil
            with key-slot-name-if-no-occurrence? = nil
            with filtered-items-for-this-time-slice = nil
            as frames-for-kb-search
               = (frames-for-kb-search kb-search-state)
            as old-kb-search-result-tables-and-text-boxes
               = (old-kb-search-result-tables-and-text-boxes kb-search-state)
            as frame = (car frames-for-kb-search)
            as frame-serial-number-for-kb-search
               = (copy-frame-serial-number (frame-serial-number-for-kb-search kb-search-state))
            as number-of-items-examined-so-far
            from (number-of-items-examined-so-far kb-search-state)
            while (or frames-for-kb-search
                      old-kb-search-result-tables-and-text-boxes
                      (and (frame-of-class-p
                             kb-search-state
                             'special-purpose-kb-search-state)
                           (special-purpose-kb-search-function?
                             kb-search-state)
                           (apply        ; returns true iff more work to do
                             (special-purpose-kb-search-function?
                               kb-search-state)
                             (special-purpose-kb-search-arglist?
                               kb-search-state))))
            initially
              (let ((original-file-name?
                      (file-name-for-printing-search-results?
                        kb-search-state)))
                (when (and original-file-name?
                           (null (file-stream-for-printing-search-results?
                                   kb-search-state)))
                  (let ((ascii-file-name
                          (ascii-file-name-for-printing-search-results?
                            kb-search-state)))
                    (setq file-stream-for-printing-search-results?
                          (setf (file-stream-for-printing-search-results?
                                  kb-search-state)
                                (open-file-for-search-results
                                  ascii-file-name
                                  (inspect-command-for-kb-search?
                                    kb-search-state))))
                    (cond
                      (file-stream-for-printing-search-results?
                       (reclaim-text-string original-file-name?)
                       (let ((truename
                               (gensym-truename
                                 file-stream-for-printing-search-results?)))
                         (setf (file-name-for-printing-search-results?
                                 kb-search-state)
                               (gensym-namestring-as-text-string
                                 truename))
                         (reclaim-gensym-pathname truename)
                         (update-representations-of-slot-value
                           kb-search-state
                           'file-name-for-printing-search-results?)))
                      (t (setf (file-operation-complete-or-error-string?
                                 kb-search-state)
                               (tformat-text-string        ; GET ACTUAL ERROR STRING! (MHD 9/12/91)
                                 "unable to open file"))
                         (loop-finish))))))
            do
        (when old-kb-search-result-tables-and-text-boxes
          (unless (frame-has-been-reprocessed-p
                    (car old-kb-search-result-tables-and-text-boxes)
                    frame-serial-number-for-kb-search)
            (delete-table-or-text-box
              (car old-kb-search-result-tables-and-text-boxes)))
          (setf (old-kb-search-result-tables-and-text-boxes kb-search-state)
                (cdr old-kb-search-result-tables-and-text-boxes))
          (reclaim-slot-value-cons old-kb-search-result-tables-and-text-boxes)
          (setq old-kb-search-result-tables-and-text-boxes
                (cdr (old-kb-search-result-tables-and-text-boxes kb-search-state))))
        (when frames-for-kb-search
          (let ((slot-denotations-to-show?
                  (slot-denotations-for-showing-as-a-table? kb-search-state)))
            (cond
              ((and (not (frame-has-been-reprocessed-p
                           frame frame-serial-number-for-kb-search))
                    (or (null item-filter-for-kb-search?)
                        (frame-matches-item-filter-p
                          kb-search-state frame item-filter-for-kb-search?))
                    (or (and (or (display-a-table? kb-search-state)
                                 (no-results-tables? kb-search-state))
                             (null string-to-look-for?))
                        (let ((foundp nil)
                              (gathering-normally-editable-slots-for-search?
                                (null replacement-string?)))
                          ;; special, to defeat product authorization
                          ;; restrictions, e.g., no editing of the text
                          ;; of procedures, but only do this if not replacing
                          ;; (MHD 5/30/95)
                          (multiple-value-setq (foundp table? key-slot-name-if-no-occurrence?)
                            (make-short-representation-for-queries
                              frame
                              string-to-look-for?
                              observance-of-word-boundary?
                              replacement-string?
                              slot-denotations-to-show?
                              nil)) ;;         (kb-search-state-invisible-p kb-search-state)))
                          foundp)))
               (cond
                 ((or (display-a-table? kb-search-state)
                      (no-results-tables? kb-search-state))
                  (when table?
                    (delete-frame table?)
                    (setq table? nil)
                    (setq key-slot-name-if-no-occurrence? nil))
                  (when (display-a-table? kb-search-state)
                    (multiple-value-bind (table-rows slot-denotations)
                        (merge-frame-into-multiframe-table-rows
                          frame
                          slot-denotations-to-show?
                          (table-rows-for-showing-as-a-table? kb-search-state)
                          (denotations-of-slots-shown-as-a-table? kb-search-state))
                      (setf (table-rows-for-showing-as-a-table? kb-search-state)
                            table-rows)
                      (setf (denotations-of-slots-shown-as-a-table? kb-search-state)
                            slot-denotations))))
                 (t
                  (let (number-of-substitutions number-of-resulting-parsing-failures)
                    (when replacement-string?
                      (multiple-value-setq
                          (number-of-substitutions number-of-resulting-parsing-failures)
                        (let ((keep-edit-workspace-hidden-no-matter-what?
                                (kb-search-state-invisible-p kb-search-state)))
                          (replace-editable-occurrences-of-string-in-table
                            table? string-to-look-for? replacement-string?
                            observance-of-word-boundary? key-slot-name-if-no-occurrence?)))
                      (if (>f number-of-substitutions 0)
                          (change-slot-value
                            kb-search-state 'number-of-substitutions-in-tables
                            (+f (number-of-substitutions-in-tables kb-search-state)
                                number-of-substitutions)))
                      (if (>f number-of-resulting-parsing-failures 0)
                          (change-slot-value
                            kb-search-state 'number-of-resulting-parsing-failures
                            (+f (number-of-resulting-parsing-failures kb-search-state)
                                number-of-resulting-parsing-failures)))
                      (unless (=f 0 number-of-substitutions)
                        (incff (number-of-items-found kb-search-state)))        ; table update later
                      )
                    (if (and string-to-look-for?
                             ;; NEW:  (MHD 4/30/91)
                             (or (null replacement-string?)
                                 (>f number-of-substitutions 0)))
                        (let ((number-of-occurrences
                                (mark-occurrences-of-string-in-table
                                  table?
                                  (or replacement-string? string-to-look-for?)
                                  observance-of-word-boundary?
                                  t nil key-slot-name-if-no-occurrence?)))
                          (if (>f number-of-occurrences 0)
                              (incff        ; table updated later
                                (number-of-occurrences-in-tables kb-search-state)
                                number-of-occurrences))))
                    (if (kb-search-state-invisible-p kb-search-state)
                        (and table? (delete-frame table?))
                        (add-to-inspect-search-results table? kb-search-state)))))
               (when (and (visit-items-when-found? kb-search-state)
                          (not (kb-search-state-invisible-p kb-search-state)))
                 (goto-frame-instance frame))
               (when file-stream-for-printing-search-results?
                 (print-frame-to-file-for-search-results
                   file-stream-for-printing-search-results?
                   frame slot-denotations-to-show?))
               (when (kb-search-state-remote-representation? kb-search-state)
                 (eval-push frame filtered-items-for-this-time-slice))
               (when (recompile-found-items? kb-search-state)
                 (let ((keep-edit-workspace-hidden-no-matter-what?
                         (kb-search-state-invisible-p kb-search-state)))
                   (with-recompile-from-inspect-environment
                       (recompile-item frame)
                     (when (frame-has-frame-notes-p frame)
                       (note-frame-for-inspector-suppressed-warnings
                         frame kb-search-state)))))
               (unless replacement-string?
                 (incff (number-of-items-found kb-search-state)))))        ; table updated later
            (setf (frames-for-kb-search kb-search-state)
                  (cdr frames-for-kb-search))
            (setf (cdr frames-for-kb-search) nil)
            (reclaim-slot-value-cons frames-for-kb-search)
            ;; NO! -- the following is not OK to do for at least the
            ;;   following reason: this does not make sure that the inference
            ;;   engine is not currently computing with these connection
            ;;   frames here.  And it would be too much work to have this
            ;;   make sure right now. (MHD/BAH 6/28/90)
            (let ((fixnum-time-now (get-fixnum-time)))
              (if (>=f (fixnum-time-difference
                         fixnum-time-now
                         (time-of-last-table-update? kb-search-state))
                       fixnum-time-interval-for-one-second)
                  ;; Every second:
                  (progn
                    (change-slot-value        ; only nec. if display not up-to-date
                      kb-search-state 'number-of-items-examined-so-far
                      (+f number-of-items-examined-so-far 1))
                    (update-representations-of-slot-value
                      kb-search-state 'number-of-items-found)
                    (update-representations-of-slot-value
                      kb-search-state 'number-of-occurrences-in-tables)
                    (update-representations-of-slot-value
                      kb-search-state 'kb-search-status?)
                    (setf (time-of-last-table-update? kb-search-state)
                          fixnum-time-now))
                  (setf (number-of-items-examined-so-far kb-search-state)
                        (+f number-of-items-examined-so-far 1))))))
            when (if (kb-search-state-no-time-slice-expiration-p kb-search-state)
                     nil
                     (time-slice-expired-p))
              do (cond ((kb-search-state-remote-representation? kb-search-state)
                        (return-remote-query-results
                          kb-search-state filtered-items-for-this-time-slice nil)
                        (schedule-search-task kb-search-state)
                        (return nil))
                       (t
                        (schedule-search-with-workstation-necessary kb-search-state)
                        (return nil)))
            finally
              (when (and (subcommand-menu-for-kb-search? kb-search-state)
                         (not (frame-has-been-reprocessed-p
                                (subcommand-menu-for-kb-search? kb-search-state)
                                (frame-serial-number-for-subcommand-menu-for-kb-search?
                                  kb-search-state))))
                ;; handler for finishing subcommand button prepared to deal with this
                (enable-or-disable-subcommand
                  (subcommand-menu-for-kb-search? kb-search-state)
                  'suspend t)
                (enable-or-disable-subcommand
                  (subcommand-menu-for-kb-search? kb-search-state)
                  'continue t))

              (progn
                (update-representations-of-slot-value
                  kb-search-state 'number-of-items-examined-so-far)
                (update-representations-of-slot-value
                  kb-search-state 'number-of-items-found)
                (update-representations-of-slot-value
                  kb-search-state 'number-of-occurrences-in-tables)
                (update-representations-of-slot-value
                  kb-search-state 'kb-search-status?)
                (setf (time-of-last-table-update? kb-search-state)
                      (get-fixnum-time)))                ; unnec.
              (when (items-with-suppressed-warning-notes? kb-Search-State)
                (do-inspector-suppressed-warnings-notes kb-search-state))
              (when kb-search-results-workspace
                (when (and (display-a-table? kb-search-state)
                           (table-rows-for-showing-as-a-table? kb-search-state))
                  ;; Remove and reclaim any rows for frames that have been
                  ;; deleted, and then, if any rows for non-deleted frames
                  ;; remain, finish making the table and put it on the
                  ;; workspace:
                  (multiple-value-bind (table-rows number-of-frames-remaining)
                      (remove-deleted-frames-in-multiframe-table-rows
                        (table-rows-for-showing-as-a-table? kb-search-state)
                        frame-serial-number-for-kb-search)
                    (setf (table-rows-for-showing-as-a-table? kb-search-state)
                          table-rows)
                    (change-slot-value
                      kb-search-state 'number-of-items-found
                      number-of-frames-remaining)
                    (if (>f number-of-frames-remaining 0)
                        (add-to-workspace
                          (prog1
                              (finish-making-multiframe-table
                                (table-rows-for-showing-as-a-table? kb-search-state)
                                (eq (display-a-table? kb-search-state) 'columnwise))
                            (setf (table-rows-for-showing-as-a-table? kb-search-state)
                                  nil))
                          kb-search-results-workspace
                          (left-edge-for-next-kb-search-result-block kb-search-state)
                          (top-edge-for-next-kb-search-result-block kb-search-state)
                          t
                          t))))                        ; this is the last block to add
                (shrink-wrap-workspace kb-search-results-workspace))
              (reclaim-frame-serial-number frame-serial-number-for-kb-search)
              (if (file-stream-for-printing-search-results? kb-search-state)
                  (setf (file-stream-for-printing-search-results?
                          kb-search-state)
                        (prog1
                            nil
                          (setf (file-operation-complete-or-error-string?
                                  kb-search-state)
                                t)
                          (close-file-for-search-results
                            (file-stream-for-printing-search-results?
                              kb-search-state)))))
              (suppressing-table-refresh-interval ; don't have updates scheduled
                (update-representations kb-search-state))
              (loop for table?
                        = (loop for frame-representation
                                    in (frame-representations kb-search-state)
                                when (frame-of-class-p
                                       frame-representation 'table)
                                  return frame-representation)
                    while table?
                    do (detach-table-from-frames-it-represents table?))
              (cond
                ((kb-search-state-remote-representation? kb-search-state)
                 ;; the following does the cleanup
                 (return-remote-query-results
                   kb-search-state filtered-items-for-this-time-slice t))
                (t
                 (cancel-scheduled-search-if-necessary kb-search-state)
                 (delete-frame kb-search-state))))))

;; Note 1: The final arg to add-to-workspace,
;; confine-updating-to-block-rectangle, is needed for efficiency; if
;; blocks other than tables are ever added or if tables with graphics
;; drawn outside of their rectangle can ever be added, this has to be
;; reviewed.  (MHD 6/20/90)

;; Consider having make-short-representation-as-appropriate include
;; representations for non-editable slots also.  See note on that
;; function.

;; When an edit workspace is revealed, it should be placed below the
;; workspace that shows the tables substitution state table!

;; Consider improving the efficiency of the kb search state table update
;; by having a slot putter for the number-of-items-examined-so-far slot
;; that updates not only that slot but also others.

;; Instead of counting deleted frames as examined, consider instead
;; decrementing the number of items to be examined.

;; As of today, it only counts "occurences of replacement string" (alias
;; for number-of-occurrences-in-tables) in items in which a replacement
;; occurred.  One might want to consider an alias like "occurences of
;; replacement string in items with some replacements", but such a
;; lengthy name might seem unreasonable.  (MHD 4/30/91)


(defun delete-table-or-text-box (table-or-text-box)
  (cond
    ((text-box-p table-or-text-box)
     ;; improve later?
     )
    (t
     (detach-table-from-frames-it-represents table-or-text-box)
     (let ((table-rows (table-rows table-or-text-box)))
       (setf (table-rows table-or-text-box) nil)
       (reclaim-slot-value table-rows))))
  (delete-frame table-or-text-box))


;;; Cancel-scheduled-search-if-necessary ... must be called in for-workstation
;;; context.
;; No longer true.  We now always get the correct workstation from the kb-search-state. -dkuznick, 11/3/98

(defun cancel-scheduled-search-if-necessary (kb-search-state)
  (when (or (kb-search-state-no-time-slice-expiration-p kb-search-state)
            (kb-search-state-remote-representation? kb-search-state))
    (return-from cancel-scheduled-search-if-necessary nil))
  #+:development
  (when (and (boundp 'current-workstation)
             (not (eq current-workstation
                      (only-workstation-this-non-kb-workspace-can-be-on?
                        (kb-search-results-workspace kb-search-state)))))
    (cerror "Continue" "Tell dkuznick he shouldn't have taken jed's advice"))

  ;; We can't assume there is a current-workstation.  For instance we could be
  ;; in the middle of a clear-kb kicked off from a system-procedure.  -dkuznick, 11/3/98
  (let* ((workstation (only-workstation-this-non-kb-workspace-can-be-on?
                        (kb-search-results-workspace kb-search-state))) 
	  entry-in-this-workstation?)
	 (if (null workstation) (return-from cancel-scheduled-search-if-necessary nil))
         (setq entry-in-this-workstation?
           (assq kb-search-state
                 (search-states-in-this-workstation workstation)))
    (when entry-in-this-workstation?
      (setf (search-states-in-this-workstation workstation)
            (delete-gensym-element
              entry-in-this-workstation?
              (search-states-in-this-workstation workstation)))
      (reclaim-frame-serial-number (cdr entry-in-this-workstation?))
      (reclaim-gensym-cons entry-in-this-workstation?))))


;;; `schedule-search-with-workstation-necessary' ... must be called in for-workstation context.

(defun schedule-search-with-workstation-necessary (kb-search-state)
  (unless (assq kb-search-state
                (search-states-in-this-workstation current-workstation))
    (setf (search-states-in-this-workstation current-workstation)
          (gensym-cons
            (gensym-cons kb-search-state (copy-frame-serial-number (frame-serial-number kb-search-state)))
            (search-states-in-this-workstation current-workstation)))))



(defun suspend-inspect-kb-search (subcommand-menu kb-search-state)
  (cancel-scheduled-search-if-necessary kb-search-state)
  (enable-or-disable-subcommand subcommand-menu 'suspend t)
  (enable-or-disable-subcommand subcommand-menu 'continue nil)
  (summarize-inspector-suppressed-warnings-if-any kb-search-state))

;; This is exactly the code that was originally in finish-inspect-subcommand
;; which has been pulled out in anticipation that it will eventually be
;; called from other points as well.  The arguments it's taking are
;; what it needed as a unit of code at its original site; they may well
;; want to be changed to something more general.  ddm as per mhd 1/22/97



;;; `Finish-inspect-subcommand' is bound into the subcommand-function?  of the
;;; subcommand menu of the inspect results workspace.  It is invoked by the
;;; subcommand-state when the user selects a button.  When invoked we are in the
;;; subcommand state, and the button is highlighted.

(defun finish-inspect-subcommand
    (subcommand-menu command
                     inspect-command frame-serial-number-for-inspect-command
                     kb-search-state frame-serial-number-for-kb-search-state)
  (case command
    (hide
     (unless (frame-has-been-reprocessed-p
               inspect-command frame-serial-number-for-inspect-command)
       (delete-frame (superblock? inspect-command))))
    ((suspend continue)
     (unless (frame-has-been-reprocessed-p
               kb-search-state frame-serial-number-for-kb-search-state)
       (cond
         ((eq command 'suspend)
          (suspend-inspect-kb-search subcommand-menu kb-search-state))
         (t
          (schedule-search-with-workstation-necessary kb-search-state)
          (enable-or-disable-subcommand subcommand-menu 'suspend nil)
          (enable-or-disable-subcommand subcommand-menu 'continue t)))))
    ((rerun edit)
     (unless (frame-has-been-reprocessed-p
               inspect-command frame-serial-number-for-inspect-command)
       (handle-inspect-command
         inspect-command nil nil
         (eq command 'rerun))   ; hidden edit workspace for rerun
       (if (eq command 'edit)                        ; unnecessary for rerun:
           (enable-or-disable-subcommand        ; turn off pending indication
             subcommand-menu command nil))))))

(defun reclaim-finish-inspect-subcommand-arglist (arglist)
  (reclaim-slot-value (first arglist))
  (reclaim-frame-serial-number (second arglist))
  (reclaim-slot-value (third arglist))
  (reclaim-frame-serial-number (fourth arglist))
  (reclaim-slot-value-list arglist))

;;; `Get-and-clear-workspace-for-inspect-command' returns nil or the workspace
;;; that inspect-command is on, after deleting all items not of class
;;; inspect-command or workspace-name-box.

(defun get-and-clear-workspace-for-inspect-command
    (inspect-command &optional kb-search-state?)
  (let ((workspace? (get-workspace-if-any inspect-command)))
    (when workspace?
      (with-deferred-drawing-in-process (:force-drawing-at-end t)
        (cond
          ((and kb-search-state?
                (not
                  (memq (second (car (box-translation-and-text inspect-command)))
                        '(show-on-a-workspace-the-workspace-hierarchy
                          show-on-a-workspace-the-class-hierarchy
                          show-on-a-workspace-the-inspect-command-history
                          show-on-a-workspace-the-module-hierarchy
                          show-on-a-workspace-the-method-hierarchy
                          show-on-a-workspace-the-method-inheritance-path
                          show-on-a-workspace-the-procedure-reference-hierarchy ; -pga, 1/11/96
                          show-on-a-workspace-the-procedure-invocation-hierarchy))))

           ;; This hack relies on the fact that every subblock except for the
           ;;   Inspect command (text box) are now known to be tables or text
           ;;   boxes not of class INSPECT-COMMAND.
           ;;
           ;; The job here is to get them out of the way quickly (i.e. remove
           ;;   them physically and graphically from the workspace) to be
           ;;   deleted later.  We exploit the fact that removing subblocks
           ;;   from workspaces is a lot faster than deleting them.  Note that
           ;;   the slot value reclaimer for old-kb-search-result-tables-and-text-boxes
           ;;   deletes all of the remaining subblocks in its slot if the
           ;;   search is aborted (i.e. by deleting the Inspect command)
           ;;   prematurely.  Unfortunately, that has to be done atomically,
           ;;   so a noticeable delay could result.  (MHD 10/24/90)

           ;; What was this hack supposed to do?  It will always fire if kb-search-state?
           ;; is true because the symbols stored in the inspect command are really
           ;; SHOW-CLASS-HIERARCHY-ON-A-WORKSPACE, SHOW-WORKSPACE-HIERARCHY-ON-A-WORKSPACE,
           ;; or SHOW-MODULE-HIERARCHY-ON-A-WORKSPACE,  not the ones tested for here.
           ;; -fmw, 3/2/94

           (loop for table-or-text-box?
                     = (loop for subblock being each subblock of workspace?
                             when (or (table-p subblock)
                                      (and (text-box-p subblock)
                                           (not (frame-of-class-p subblock 'inspect-command))))
                               return subblock)
                 while table-or-text-box?
                 do (let ((region-invalidation-is-preferred t))        ; Note A
                      (erase-images-of-block table-or-text-box? t)
                      (remove-as-subblock-if-necessary table-or-text-box? workspace?))
                    (setf (old-kb-search-result-tables-and-text-boxes kb-search-state?)
                          (slot-value-cons
                            table-or-text-box?
                            (old-kb-search-result-tables-and-text-boxes kb-search-state?)))
                 finally
                   ;; this is for the hierarchy case, i.e., when switching from
                   ;;   a workspace that had been displaying a hierarchy to one that's
                   ;;   to display tables and text boxes. -- make resumable later!
                   ;;   (MHD 7/6/92)
                   (let ((delete-connections-without-leaving-stubs? t))        ; important special
                     (delete-subblocks-not-of-class
                       workspace? '(inspect-command workspace-name-box)))
                   (shrink-wrap-workspace workspace?)))
          (t
           ;; this is the hierarchy case -- make resumable later!
           (let ((delete-connections-without-leaving-stubs? t))        ; important special
             (invalidate-workspace workspace?)
             (delete-subblocks-not-of-class
               workspace?
               '(inspect-command workspace-name-box)))))))

    workspace?))

;; Note A: This binding works around a bug in the protocol for drawing, fixing
;; HQ-167514 "Painting of inspect workspaces".  See the extensive note in
;; handle-dialog-button in facilities for more information. -fmw, 1/25/95


(defun normalize-designation (designation)
    (if (symbolp designation)
	(copy-symbol-name designation :first)
	(copy-wide-string designation)))
				    

;;; `Put-inspect-workspace-on-current-detail-pane' puts inspect-workspace on
;;; the current detail pane if necessary.  This does nothing if
;;; inspect-workspace is already showing as desired.

(defun put-inspect-workspace-on-current-detail-pane (inspect-workspace)
  (when new-g2-classic-ui-p
    (let ((designation (get-or-make-up-designation-for-block inspect-workspace)))
      (setq designation (normalize-designation designation))	
      (change-slot-value
        inspect-workspace 'title-bar-caption-text
        (convert-text-string-to-text designation)))
    (change-slot-value
      inspect-workspace 'workspace-background-color?
      (get-ui-parameter 'system-workspace-background-color)))
  (let ((main-image-plane
          (or (loop for image-plane
                        in (image-planes-this-is-on inspect-workspace)
                    when (eq (pane-for-image-plane image-plane)
                             current-workstation-detail-pane)
                      do (return image-plane))
              (put-workspace-on-pane
                inspect-workspace current-workstation-detail-pane
                'left 'top nil))))
    main-image-plane                                ; not used now
    ;; The following is cute, but needs too much design and review
    ;;   to persue at this time:   (MHD 6/18/90)
;        (unless (loop for image-plane
;                          in (image-planes-this-is-on inspect-workspace)
;                      when (and (not (eq image-plane main-image-plane))
;                                (eq (pane-for-image-plane image-plane)
;                                    current-workstation-detail-pane))
;                        do (return image-plane))
;          (let ((overview-image-plane
;                  (get-available-image-plane        ; on top
;                    current-workstation-detail-pane
;                   (lookup-frame-description-reference-of-frame-style
;                         'default-workspace-frame-style
;                         'default-workspace-frame-style) nil)))
;            (put-image-on-image-plane
;              overview-image-plane inspect-workspace
;              #.(round (normalized-scale) 20)        ; very small
;              #.(round (normalized-scale) 20)
;              nil nil
;              (left-edge-of-block inspect-workspace)
;              (top-edge-of-block inspect-workspace)
;              (+r (left-edge-of-pane-in-window overview-image-plane) 10)
;              (+r (top-edge-of-pane-in-window overview-image-plane) 10))))
    )
  #+development
  (test-assertion
    (stack-of-image-planes current-workstation-detail-pane)))


;;; `Mark-occurrences-of-string-in-table' ... returns the number of occurrences marked.
;;; Name-of-slot-to-ignore? is ignored if both only-in-text-representations-for-slot-values?
;;; and only-editable-occurrences? are nil. If only-editable-occurrences? is true,
;;; string-to-look-for? will not be matched in slots that are not editable because
;;; they either are not of an editable type or because, unless the frame they represent
;;; is a message, they have been stripped.

;;; To unmark table, do (delete-any-text-regions table).

(defun mark-occurrences-of-string-in-table
       (table string-to-look-for observance-of-word-boundary?
        &optional (only-in-text-representations-for-slot-values? t)
                  (only-editable-occurrences? t)
                  name-of-slot-to-ignore?)
  (loop as row in (table-rows table)
        sum (loop as cell? in row
                  when (and cell?
                            (not (cell-is-block-p cell?))        ; a text cell
                            (or (and (not only-in-text-representations-for-slot-values?)
                                     (not only-editable-occurrences?))
                                (multiple-value-bind
                                    (frame? slot-name-or-index? defining-class?)
                                    (get-slot-represented-by-text-cell-if-any cell?)
                                  ;; This predicate should always be the same as the predicate that is used
                                  ;; by replace in inspect. If you change this you should also change it there.
                                  ;; Someday these two uses should be abstracted appropriately.
                                  (and frame?
                                       (symbolp slot-name-or-index?)
                                       (or (not only-editable-occurrences?)
                                           (let ((type-of-slot-if-editable?
                                                   (type-slot-feature-assq-if-editable
                                                     (slot-features
                                                       (get-slot-description-of-frame
                                                         slot-name-or-index?
                                                         frame?
                                                         defining-class?)))))
                                             (and type-of-slot-if-editable?
                                                  (or (not (text-slot-type-p
                                                             type-of-slot-if-editable?))
                                                      (not (stripped-text-p (text? cell?)))
                                                      (frame-of-class-p frame? 'message)))))
                                       (not (if name-of-slot-to-ignore?
                                                (eq slot-name-or-index?
                                                    name-of-slot-to-ignore?)))


                                       ;; The following is to maintain
                                       ;; the constraint that you can
                                       ;; only edit items that are
                                       ;; transient or permanent

                                       (or (transient-p frame?)
                                           (permanent-block-p frame?))

                                       (edit-attribute-allowed-p
                                          frame? slot-name-or-index?
                                          defining-class?)
                                       ;; PASS IN DEFINING-CLASS?! (MHD 2/16/94)
                                       ;; Is this really "defining-class" ? That should never be NIL.

;                                       ;; The following is to maintain
;                                       ;; the constraint that editing of
;                                       ;; non-top-level module's system
;                                       ;; tables is not allowed
;
;                                       (or (not (frame-of-class-p frame? 'system-table))
;                                           (system-table-installed-p frame?))


                                       ;; The following is to maintain
                                       ;; the constraint that the
                                       ;; module-this-is-part-of?  slot
                                       ;; of a kb workspace cannot be
                                       ;; edited unless the it's a
                                       ;; top-level workspace.

; This is not needed because attribute tables can't ever get this slot into them.
;
;                                       (or (not (eq slot-name-or-index? 'module-this-is-part-of?))
;                                           (not (frame-of-class-p frame? 'kb-workspace))
;                                           (null (parent-of-subworkspace? frame?)))
                                       ))))

                    sum (mark-occurrences-of-string-in-text
                          table cell?
                          string-to-look-for observance-of-word-boundary?))))

;; Consider having this recur in the case where a cell is a (sub)table.






;;; `Replace-editable-occurrences-of-string-in-table' ... returns two values: the number
;;; of substitutions made and the number of resulting parsing failures.

;;; String-to-replace will not be matched in slots that are not editable because
;;; they either are not of an editable type or, unless the frame they represent
;;; is a message, because they have been stripped.

(defun replace-editable-occurrences-of-string-in-table
    (table string-to-replace replacement-string observance-of-word-boundary?
           &optional name-of-slot-to-ignore? ignore-unmarked-cells?)
  (loop with number-of-substitutions = 0
        with number-of-resulting-parsing-failures = 0
        as row-index from 0
        as row in (table-rows table)
        do (loop as column-index from 0
                 as cell? in row
                 as text?
                    = (if (and cell? (not (cell-is-block-p cell?)))
                          (text? cell?))
                 with frame?
                 with slot-name-or-index?
                 with defining-class?
                 with beginning-line-index?
                 with beginning-character-index?

                 ;; This predicate should always be the same as the predicate that is used by
                 ;; mark-occurence-of-string-in-table.  If you change this you should also
                 ;; change it there.  Someday these two uses should be abstracted
                 ;; appropriately.

                 when (and text?
                           (editable-text-cell-p table cell?)
                           (not (if name-of-slot-to-ignore?
                                    (eq slot-name-or-index?
                                        name-of-slot-to-ignore?)))
                           (or (not ignore-unmarked-cells?)
                               (loop for subblock        ; abstract as "text-cell-marked-p"?
                                         being each subblock of table
                                     thereis
                                     (if (frame-of-class-p subblock 'text-region)
                                         (and (=f (row-index-for-text-region-cell?
                                                    subblock)
                                                  row-index)
                                              (=f (column-index-for-text-region-cell?
                                                    subblock)
                                                  column-index)))))
                           (multiple-value-setq  ; note 1
                               (frame? slot-name-or-index? defining-class?)
                             (get-slot-represented-by-text-cell-if-any
                               cell?))
                           (edit-attribute-allowed-p
                             frame? slot-name-or-index?
                             defining-class?)
                           (multiple-value-setq
                               (beginning-line-index? beginning-character-index?)
                             (find-string-in-text-for-inspect
                               string-to-replace text? observance-of-word-boundary?)))

                   do (enter-editing-context
                        frame?
                        (make-slot-name-denotation
                          slot-name-or-index?
                          defining-class?)
                        (copy-text text?)
                        t
                        nil nil                        ; supply format and width?
;                          nil nil nil
                        beginning-line-index? beginning-character-index?)

                      (in-editing-context (specific-structure-for-current-workstation-context)
                        (loop with end-line-index?
                              with end-character-index?
                              while
                              (multiple-value-setq        ; always succeeds on 1st iteration
                                  (beginning-line-index? beginning-character-index?
                                                         end-line-index? end-character-index?)
                                (find-string-in-text-for-inspect
                                  string-to-replace (text-being-edited current-edit-state)
                                  observance-of-word-boundary?
                                  (cursor-line-index current-edit-state)
                                  (cursor-character-index current-edit-state)))
                              do (change-edit-box        ; move cursor to end
                                   nil end-line-index? end-character-index?
                                   nil nil nil nil nil t)  ; no parsing or ellipsis deletion
                                 (change-edit-box        ; do substitution
                                   nil beginning-line-index? beginning-character-index?
                                   end-line-index? end-character-index? replacement-string)
                                 (incff number-of-substitutions)))
                      (if (not (let ((editing-context current-workstation-context))
                                 (prog1 (finish-parsing-insofar-as-possible)
                                   (when (and keep-edit-workspace-hidden-no-matter-what?
                                              (eq current-workstation-context editing-context))
                                     (return-from-current-workstation-context 'editing)))))
                          (incff number-of-resulting-parsing-failures)))
        finally
          (return
            (values number-of-substitutions number-of-resulting-parsing-failures))))

;; Note 1:  The same access to get-slot-represented-by-text-cell-if-any and
;; check for edit-attribute-allowed-p is done in editable-text-cell-p, but
;; has to be done again here because we need to operate on the objects that
;; it returns. If these were abstracted to a different interface we could
;; remove that redundancy.

;; Note that updating a table does not invalidate its table-rows slot.

;; See also the handling of the recompile-everything menu choice in module MENUS.

;; Consider doing replacements on a flattened text (flattened by means of convert-text-to-
;; text-string) before entering the editor, to gain a bit of speed.

;; Consider avoiding reformatting at the start and end of editing, to gain a bit of speed.

;; Consider having a do-only-one-substitution? argument.

;; Consider having arguments and values that specify where to continue looking (row
;; index, column index, line index, character index), to avoid substituting within
;; an earlier substitution and to avoid wasted search effort.  If this is done,
;; however, it must be remembered that a table might have otherwise changed between
;; substitutions.

;; Consider having this recur in the case where a cell is a (sub)table.






;;;; Launching Compiles

(def-kb-specific-variable remote-query-id-for-kb-recompile queries nil)

;;; `Launch-compile-to-bring-kb-up-to-date' launches an Inspect command in the
;;; current workstation, provided that servicing-workstations? is true.  The
;;; command includes the following comment, in brackets ({}):
;;;
;;;    Comment: G2 has launched this Inspect command to compile
;;;    this KB up-to-date.
;;;
;;; The text in additional-comment-text-string?, if any, is placed after the
;;; above text in the comment.
;;;
;;; Following the comment, the following command appears:
;;;
;;;    recompile every item whose status is incomplete
;;;
;;; The user may then suspend, cancel, restart, or edit the command as they see
;;; fit, i.e., as though they had initiated the Inspect command themselves.
;;;
;;; If this fails to launch an inspect command, it returns nil.  Otherwise, it
;;; returns non-nil.

(defun launch-compile-to-bring-kb-up-to-date
    (&optional additional-comment-text-string?)
  (let* ((comment-text-string
           (tformat-text-string
             "{Comment: G2 has launched this Inspect command to compile ~
                 this KB up-to-date.~a~a}"
             (if additional-comment-text-string? "  " "")
             (or additional-comment-text-string? "")))
         (message
           (prog1
               (tformat-text-string
                 "~a~%~%~a"
                 comment-text-string
                 "recompile every item whose status is incomplete")
             (reclaim-text-string comment-text-string))))
    (cond (ui-client-interface-in-which-to-launch-recompilation?
           (enter-dialog-for-t2
             'recompile
             (eval-list (eval-list 'text (copy-text-string message) 'recomile-message)
                        (eval-list 'button (copy-constant-wide-string #w"Pause") 'pause)
                        (eval-list 'button (copy-constant-wide-string #w"Rerun") 'rerun)
                        (eval-list 'button (copy-constant-wide-string #w"Hide") 'hide))
             'handle-remote-recompile-dialog-request
             ui-client-interface-in-which-to-launch-recompilation?
             nil)
           (setq remote-query-id-for-kb-recompile
                   (start-inspect-session-internal
                     message
                     ;;SEE NOTE BY start-inspect-session-internal when changing this function
                     'notify-t2-for-local-recompile
                     nil
                     1
                     (allocate-managed-float 1.0))))
          (t
           (handle-inspect-command (make-command-frame 'inspect-command message) nil nil t)))
    (when additional-comment-text-string?
      (reclaim-text-string additional-comment-text-string?))
    t))

(defun handle-remote-recompile-dialog-request (dialog-sequence-number client-item)
  (let ((button (get-values-for-t2-dialog dialog-sequence-number))
        (id remote-query-id-for-kb-recompile))
    (case button
      (pause
       (for-dummy-workstation
         (g2-pause-inspect-session id))
       (update-dialog-for-t2
         'recompile
         (eval-list 'pause
                    (copy-constant-wide-string #w"Resume") 'resume)
         'button-update))
      (resume
       (update-dialog-for-t2
         'recompile
         (eval-list 'resume
                    (copy-constant-wide-string #w"Pause") 'Pause)
         'button-update)
       (for-dummy-workstation
         (g2-resume-inspect-session id)))
      (hide
       (leave-dialog-for-t2 dialog-sequence-number)
       (remove-dialog-info-from-ui-client-interface-dialog-list
         dialog-sequence-number
         (ui-client-session-parent-interface client-item))
       (setq ui-client-interface-in-which-to-launch-recompilation? nil)
       (setq remote-query-id-for-kb-recompile nil))
      (rerun
       (leave-dialog-for-t2 dialog-sequence-number)
       (remove-dialog-info-from-ui-client-interface-dialog-list
         dialog-sequence-number
         (ui-client-session-parent-interface client-item))
       (setq remote-query-id-for-kb-recompile nil)
       (launch-recompilation-for-this-kb)))))








;;; `Launch-inspect-command' launches an Inspect window with the text of
;;; command-as-text-string as its command.  Text-of-command should be a text
;;; string to be copied and used as the command. It is not reclaimed by this
;;; function.  G2-window must be either nil (unspecified) or a G2-window in
;;; which to execute the command.  In the unspecified case, the "system window"
;;; is used.  (When the system-window facility is phased out, this will have to
;;; be reengineered.)  Note that the G2 window must be a logged-in G2 window; if
;;; not, this will not launch the command and return nil.  If this launches the
;;; command, this returns true.

#+development
(defun launch-inspect-command (command-as-text-string &optional g2-window)
  (unless g2-window
    (setq g2-window
          (g2-window-for-this-workstation?
            (workstation-this-is-on system-window))))
  (let ((workstation-for-g2-window? (workstation-for-g2-window? g2-window)))
    (when (and workstation-for-g2-window?
               (eq (workstation-login-state
                     workstation-for-g2-window?)
                   'logged-in))
      (for-workstation (workstation-for-g2-window?)
        (handle-inspect-command
          (make-command-frame
            'inspect-command
            (copy-text-string command-as-text-string))
          nil nil t))
      t)))

;; We would like to not rely on a system-window, but that's the most expedient
;; implementation for now, and this is not the only facility that relies on it.
;; A search for system-window will reveal others. (MHD 10/7/96)

;; In the future, this may want to be made available to the user as an action,
;; and/or as a system procedure.  It would be nice not to require any window.
;; This should also return a handle to the inspector, either as the inspect
;; command or something else, and give an API to at least pause, resume, rerun,
;; reedit (change text of), and hide (delete inspect workspace).  Right now
;; this is intended to be used for internal users, such as VKP, in order to
;; expedite product preparation.  (MHD 10/7/96)





;;;; Checking Savability



;;; The following command may be used in Inspect to check for the
;;; savability of a KB.
;;;
;;;     check savability of this KB [with <problem> [, <problem> ...]]
;;;
;;;     find problems with the KB [of
;;;       class <problem class> [, <problem class> ...]]
;;;
;;;     show ... every kb-problem





;;;; Describe: Introduction




;;; The `describe' facility takes an object and makes an appropriate description
;;; of it for placement on a temporary workspace.

;;; A large amount of the code in this facility implements descriptions
;;; of the forward and backward chaining which will occur on behalf of
;;; the given variable.

;;; The backbone of describe is provided by describe-item-on-temporary-workspace
;;; and the describe-frame methods defined for various blocks.  These methods
;;; create a "display list" which is then used to create a temporary workspace
;;; containing that display.






;;;; Describe: General Display List Utilities


;;; The function `make-description-box' takes a text-line and returns a
;;; borderless free text box in an appropriate format for displaying
;;; descriptions.  The function `make-description-box-with-text' is similar, but
;;; takes a text, not a text string.

;;; `With-output-to-description-box' is a corresponding macro, the body of which
;;; is to write the text.

(defun make-description-box (text-line)
  (make-free-text-box
    text-line nil
    (choose-font-format-per-fonts-table
      'borderless-free-text-format
      'font-for-descriptions)))

(defun make-description-box-with-text (text)
  (make-free-text-box-with-text
    text nil
    (choose-font-format-per-fonts-table
      'borderless-free-text-format
      'font-for-descriptions)))

(defmacro with-output-to-description-box (&body forms)
  `(make-description-box-with-text (twith-output-to-text ,@forms)))

;; Note that small-borderless-free-text-format was
;; describe-variable-borderless-prose-format prior to 11/23/88.



;;; The function `describe-item-on-temporary-workspace' takes an item
;;; as its only argument and will pop up a temporary workspace containing
;;; a series of blocks which describe the item.  This series of items is
;;; computed by the describe-frame method on the item.

;;; The describe-frame method creates a program in a little micro language
;;; that is then interpreted to create the actual display.  The syntax is
;;; analagous to a Lisp programs.

;;; The allocation rules about the forms in the program are as follows.
;;; Conses are taken from the eval cons pool and are returned there after
;;; the evaluation completes.  Frames and strings are usually incorporated
;;; into the blocks the resulting workspace.

;;; Each form in a statement list is evaluated and then added to the
;;; workspace being built.  Nil, Strings, and frames are self evaluating.
;;; Frames are added to the workspace directly.  Strings are wrapped in a
;;; free-text-box using make-description-box.  Nil is ignored.

;;; The result of the call on describe-frame is a statement-list.

;;; Each frame added to the resulting workspace is placed in the workspace
;;; from top to bottom with 10 workspace units between them.

;; The cool thing would be to add a special form
;;   (with-format (<plist>) &body <statement-list>)
;; That created alternate behavor for the act of adding a frame to the
;; workspace.  For example
;;   (with-format (:indent 5 :spacing 2 :heading east :text-box-format-name ...) ...)

(defun describe-item-on-temporary-workspace (item)
  (let* ((*current-computation-frame* item)        ; needed for calling role servers
         (display-description (nreverse (funcall-method 'describe-frame item)))
         (workspace (make-workspace
                      'temporary-workspace nil nil 50
                      nil nil)))
    ;; Header.
    (cond
      (new-g2-classic-ui-p
       (change-slot-value
         workspace 'title-bar-caption-text
         (twith-output-to-text
           (tformat "Description of ~(~NF~)" item)))
       (change-slot-value
         workspace 'workspace-background-color?
         (get-ui-parameter 'system-workspace-background-color)))
      (t
       (eval-push
         (tformat-text-string "Description of ~(~NF.~)" item)
         display-description)))

    ;; New for 6.0:  (MHD 9/13/99)
    (eval-push
      (make-class-header-string item)
      display-description)

    ;; Show display-description on the workspace.
    (loop with current-y = 0
          for display-statement in display-description
          as result-of-evaluation
             = (typecase display-statement
                 (atom display-statement)
                 #+development
                 (t
                  (cerror "Ignore" "No nested forms yet in describe display descriptions.")))
          as block-to-add-to-workspace?
             = (cond
                 ((null display-statement)
                  nil)
                 ((text-string-p display-statement)
                  (make-description-box result-of-evaluation))
                 ;; new for 5.0: allow "didplay-statement" here to be a text:
                 ;; (MHD 1/24/96)
                 ((consp display-statement) ; "text-p"!!! - abstract further1
                  (make-description-box-with-text result-of-evaluation))
                 (t result-of-evaluation))
          when block-to-add-to-workspace?
            do (add-to-workspace
                 block-to-add-to-workspace? workspace 0 current-y)
               (incfw current-y                        ; 5 is vertical spacing
                      (+w (height-of-block block-to-add-to-workspace?) 10))
          finally
            (put-workspace-on-pane
              workspace current-workstation-detail-pane
              'left 'top t))
    (reclaim-eval-list display-description)))

;; The list returned by frames-to-show could have more structure.  For
;; example annotations about formating to provide some outlining, or
;; columns.  The list returned could be augmented with "user
;; restrictions" to allow cuter behavor on mouse actions.




;;;; Describe: The Describe-Frame Method




;;; `Describe-frame' is a method on blocks.  It takes no arguments and returns
;;; an eval-list of "display statements".  A `display statement' is either
;;;
;;;   (a) a text box containing free text;
;;;   (b) a text string that should become the text contents of a text box; or
;;;   (c) a text that should become the text contents of a text box
;;;
;;; It is invoked by describe-item-on-temporary-workspace.  who places this list
;;; of blocks on a temporary workspace in reverse order from top to bottom.  The
;;; returned value is owned by the caller.

;;; If you refine the method for a particular class of blocks it is critical
;;; that you call the superior method for the block.  New methods that refine
;;; those on existing methods should arrange to behave as if the combination
;;; method was nconc.  These new methods should be after methods.

;;; The describe-frame method is called with an approprate binding for
;;; *current-computation-frame* established.  The binding of current
;;; computation-component-particulars is unspecified.

(def-generic-method describe-frame (block))



;;; Describe-frame for block will display these things about a block:
;;;  - The module block resides in, if any, IFF (kb-has-modularity-
;;;    information-p) [New. (MHD 1/31/92)]
;;;  - Disassembly of embedded computations (in development only).
;;;  - Membership in any relations (but not arrays).
;;;  - Membership in any lists (but not arrays).

;;; It probably ought to, but doesn't show:
;;;  - Workspace hierarchy info.
;;;    - path to the root.
;;;    - physical location.
;;;    - activation status of decendents and ancestors.
;;;    - user restrictions of decendents and ancestors.
;;;  - Connection network info
;;;    - Actual connections.
;;;    - Missing and spontanous stubs.
;;;  - Class hierarchy info.
;;;  - Evaluation info.
;;;    - Enumeration of embedded computations.
;;;    - Event service links of any embedded computations?
;;;    - Current data service requests.
;;;  - Names registered with constency analysis.
;;;  - Format attribute details (color, resizing, etc.)
;;; Some of these things are shown by some of the refinements of this method.

(def-class-method describe-frame (block)
  (let ((frames-to-show nil)
	(relation-instances (relation-instances block))
	(class-of-item (class block)))

    ;; If there is modularity information, say which module this resides
    ;; in, if any.
    (when (kb-has-modularity-information-p)
      (let* ((module? (get-module-block-is-in block))
	     (reason? (and module? (get-reason-module-is-not-editable module?)))
	     (write-symbols-in-lower-case? nil))	; special
	(eval-push
	  (cond (reason?
		 (tformat-text-string
		   "This is assigned to module ~a, which is not editable because ~a."
		   module? reason?))
		(module?
		 (tformat-text-string
		   "This is assigned to module ~a."
		   module?))
		(t
		 (tformat-text-string
		   "This is not assigned to any module."))) ;  was: does not reside any module
	  frames-to-show)))

    ;; A disassembly
    (when (or #+development t
	      (and disassemble-enabled?
		   (not (proprietary-p block))))
      (setq frames-to-show
	    (nconc (disassemble-item-if-appropriate block) frames-to-show)))

    ;; Item is an element(s) in some relation(s)
    (when relation-instances
      (loop for relation-instance-form being each relation-instance of relation-instances
	    for given-name = (relation-instance-name relation-instance-form)
	    for relation = (relation-instance-relation relation-instance-form)
	    for related-items = (relation-instance-items relation-instance-form)
	    doing
      (eval-push
	(if (or (eq given-name (relation-name relation))
		(eq given-name (inverse-of-relation relation)))
	    (tformat-text-string "The following items are ~(~a this ~a~)."
				 given-name class-of-item)
	    (tformat-text-string "This ~(~a is ~a~) the following items."
				 class-of-item (relation-name relation)))	      
	frames-to-show)
      (loop for related-item being each related-item of related-items
	    when related-item do
	(eval-push
	  (make-short-representation related-item nil 'small)
	  frames-to-show))))

    ;; Description of the g2-lists that contain this element.
    (let ((element-structures (list-elements-for-item block)))
      (when element-structures
	(eval-push
	  (if (second element-structures)
	      (tformat-text-string
		"This ~(~a~) is a member of the following g2-lists: "
		class-of-item)
	      (tformat-text-string
		"This ~(~a~) is a member of the following g2-list: "
		class-of-item))
	  frames-to-show)
	(loop for element in element-structures doing
	  (eval-push
	    (make-short-representation (list-frame element) nil 'small)
	    frames-to-show))))

    ;; If item is proprietary, say so
    (let ((proprietary-package? (proprietary-p block)))
      (when proprietary-package?
	(eval-push
	  (tformat-text-string
	    "This item is proprietary to ~(~a~)." proprietary-package?)
	  frames-to-show)))

    ;; Creation backtrace
    (let ((backtrace?
	    (and tracked-items-call-vector-table
		 (get-tracked-items-call-vector-table block tracked-items-call-vector-table))))
      (when (and backtrace? (<f 0 (evaluation-sequence-length backtrace?)))
	(eval-push (tformat-text-string "The following procedures were on the stack when this was created:")
		   frames-to-show)
	(loop for proc being each evaluation-sequence-element of backtrace?
	      doing
	  (eval-push
	    (make-short-representation proc nil 'small)
	    frames-to-show))))

    frames-to-show))


;;; The describe-frame method on new-tables is in progress.

;;; Describe-frame on a new-table computes component particulars given
;;; based on the current-workstation-event if any.  Projects the table
;;; focused on the mouse location provided by the current workstation
;;; event if any.

#+development
(def-class-method describe-frame (new-table)
  (nconc
    (funcall-superior-method new-table)
    (describe-new-table)))



;;; The describe-frame method on connections will enumerate all the
;;; blocks immediately reachable from this connection.  This is
;;; done using `make-connection-description-text-string' and
;;; `print-connection-describe-info'

(def-class-method describe-frame (connection)
  (let ((frames-to-show nil)
        (connection-structure
          (connection-for-this-connection-frame connection)))
    (with-connection
      connection-structure t t nil
      ((port-name-for-input-end?
         (get-port-name-given-block-and-connection
           input-end-object connection-structure 'output))
       (port-name-for-output-end?
         (get-port-name-given-block-and-connection
           output-end-object connection-structure 'input)))
      (setq frames-to-show
            (eval-cons
              (make-description-box-with-text
                (twith-output-to-text
                  (cond
                    ((connection-not-directed? connection-structure)
                     (let ((vertical-distance-between-endpoints
                             (-w input-end-y-position output-end-y-position))
                           (horizontal-distance-between-endpoints
                             (-w input-end-x-position output-end-x-position))
                           input-end output-end
                           (input-end-first-p t))
                       (if (>w (absw vertical-distance-between-endpoints)
                               (absw horizontal-distance-between-endpoints))
                           (if (>=w vertical-distance-between-endpoints 0)
                               (setq input-end "Bottom" output-end "Top"
                                     input-end-first-p nil)
                               (setq input-end "Top" output-end "Bottom"))
                           (if (>=w horizontal-distance-between-endpoints 0)
                               (setq input-end "Right" output-end "Left"
                                     input-end-first-p nil)
                               (setq input-end "Left" output-end "Right")))
                       (if input-end-first-p
                           (print-connection-describe-info
                             nil
                             input-end input-end-object
                             port-name-for-input-end?
                             input-end-side input-end-position-on-side
                             output-end output-end-object
                             port-name-for-output-end?
                             output-end-side output-end-position-on-side)
                           (print-connection-describe-info
                             nil
                             output-end output-end-object
                             port-name-for-output-end?
                             output-end-side output-end-position-on-side
                             input-end input-end-object
                             port-name-for-input-end?
                             input-end-side input-end-position-on-side))))
                    (t
                     (print-connection-describe-info
                       t
                       "Input" input-end-object
                       port-name-for-input-end?
                       input-end-side input-end-position-on-side
                       "Output" output-end-object
                       port-name-for-output-end?
                       output-end-side output-end-position-on-side)))))
              (nconc
                (funcall-superior-method connection)
                frames-to-show))))))

#+unused
(defun make-connection-description-text-string (connection)
  (let ((connection-structure
          (connection-for-this-connection-frame connection)))
    (with-connection
      connection-structure t t nil
      ((port-name-for-input-end?
         (get-port-name-given-block-and-connection
           input-end-object connection-structure))
       (port-name-for-output-end?
         (get-port-name-given-block-and-connection
           output-end-object connection-structure)))
      (twith-output-to-text-string
        (cond
          ((connection-not-directed? connection-structure)
           (let ((vertical-distance-between-endpoints
                   (-w input-end-y-position output-end-y-position))
                 (horizontal-distance-between-endpoints
                   (-w input-end-x-position output-end-x-position))
                 input-end output-end
                 (input-end-first-p t))
             (if (>w (absw vertical-distance-between-endpoints)
                     (absw horizontal-distance-between-endpoints))
                 (if (>=w vertical-distance-between-endpoints 0)
                     (setq input-end "Bottom" output-end "Top"
                           input-end-first-p nil)
                     (setq input-end "Top" output-end "Bottom"))
                 (if (>=w horizontal-distance-between-endpoints 0)
                     (setq input-end "Right" output-end "Left"
                           input-end-first-p nil)
                     (setq input-end "Left" output-end "Right")))
             (if input-end-first-p
                 (print-connection-describe-info
                   nil
                   input-end input-end-object
                   port-name-for-input-end?
                   input-end-side input-end-position-on-side
                   output-end output-end-object
                   port-name-for-output-end?
                   output-end-side output-end-position-on-side)
                 (print-connection-describe-info
                   nil
                   output-end output-end-object
                   port-name-for-output-end?
                   output-end-side output-end-position-on-side
                   input-end input-end-object
                   port-name-for-input-end?
                   input-end-side input-end-position-on-side))))
          (t
           (print-connection-describe-info
             t
             "Input" input-end-object
             port-name-for-input-end?
             input-end-side input-end-position-on-side
             "Output" output-end-object
             port-name-for-output-end?
             output-end-side output-end-position-on-side)))))))

(defun print-connection-describe-info
       (directed?
        end1 end1-block port-name-for-end1? end1-side end1-position-on-side
        end2 end2-block port-name-for-end2? end2-side end2-position-on-side)
  (declare (ignore directed?))
  (let ((print-info-for-end1? (not (frame-of-class-p end1-block 'loose-end)))
        (print-info-for-end2? (not (frame-of-class-p end2-block 'loose-end))))

    ;; This was judged to be too verbose.
;    (tformat
;      "This ~a connection has "
;      (if directed? 'directed 'non-directed))

    (when print-info-for-end1?
      (tformat "~A end connected to ~nf "
               end1
               end1-block)
      (tformat "at ~(~a~) ~d " end1-side end1-position-on-side)
      (when port-name-for-end1?        (tformat "at port ~a " port-name-for-end1?))
      (tformat "~%"))

;    (when (and print-info-for-end1? print-info-for-end2?)
;      (tformat "and "))

    (when print-info-for-end2?
      (tformat "~A end connected to ~nf "
               end2
               end2-block)
      (tformat "at ~(~a~) ~d " end2-side end2-position-on-side)
      (when port-name-for-end2?        (tformat "at port ~a " port-name-for-end2?)))))



;;; The describe-frame method on g2-arrays and g2-lists will
;;; enumerate the elements in that list.

(def-class-method describe-frame (g2-array)
  (nconc (funcall-superior-method g2-array)
         (describe-frame-that-is-either-g2-array-or-g2-list
           g2-array)))

(def-class-method describe-frame (g2-list)
  (nconc (funcall-superior-method g2-list)
         (describe-frame-that-is-either-g2-array-or-g2-list
           g2-list)))

;(defun describe-frame-that-is-either-g2-array-or-g2-list (item)
;  (let* ((frames-to-show nil)
;         (class-of-item (class item))
;         (element-type
;           (frame-class-case item
;             (g2-array (g2-array-element-type item))
;             (g2-list (list-type item))))
;         (reclaim-array-managed-float-elements? nil)
;         (list-of-elements
;           ;; Arrays and lists must be active to contain elements.
;           (when (active-p item)
;             (frame-class-case item
;               (g2-array
;                 (when (eq element-type 'float)
;                   (setq reclaim-array-managed-float-elements? t))
;                 (let ((head? nil) (tail? nil))
;                   (do-g2-array-elements (element item head?)
;                     (enqueue
;                       (if (number-needing-boxing-p element)
;                           (allocate-managed-float element)
;                           element)
;                       head? tail? g2-list-cons)))) ; use g2-list cons pool so
;               (g2-list                 ;   same as g2-list-elements
;                 (g2-list-elements item))))))
;    (when list-of-elements
;      (cond
;        ((and (not (memq element-type g2-element-datum-types))
;              (not (eq element-type 'item-or-value)))
;         (setq frames-to-show
;               (describe-g2-array-or-list-item-elements
;                 list-of-elements class-of-item)))
;        ;; else - print the elements that are constant values.
;        (t
;         (setq frames-to-show
;               (eval-cons
;                 (make-description-box
;                   (twith-output-to-text-string
;                     (tformat
;                       "The following ~a of this ~(~a~):~%"
;                       (if (cdr list-of-elements)
;                           "values are members"
;                           "value is a member")
;                       class-of-item)
;                     (loop with printable-type
;                             = (if (eq element-type 'quantity)
;                                   'number
;                                   element-type)
;                           for (element . more?) on list-of-elements
;                           do
;                       (cond
;                         ((null element)
;                          (twrite-string "no value"))
;                         ((evaluation-value-p element)
;                          (tformat "~NV" element))
;                         ((temporary-constant-p element)
;                          (tformat
;                            "~NC"
;                            (cached-constant-value element)
;                            (constant-type element)))
;                         (t
;                          (tformat
;                            "~NC" element printable-type)))
;                           when more? do (tformat ", "))
;                     (twrite-string ".")))
;                 frames-to-show))))
;      (when reclaim-array-managed-float-elements?
;        (loop for element in list-of-elements
;              do
;          (when (managed-float-p element)
;            (reclaim-managed-float element))))
;      (reclaim-g2-list-list list-of-elements))
;    frames-to-show))

;; Remove the above, commented out version of describe-frame-that-is-either-g2-
;; array-or-g2-list, when the new version is tested!!  - cpm, 12/8/93



;;; The function `describe-frame-that-is-either-g2-array-or-g2-list' describes
;;; the elements of the g2-list or g2-array to the user.  This is used in the
;;; DESCRIBE menu-choice of G2.  This is the main way of seeing the elements of
;;; a list or array.  Note that this description of elements is not dynamic.  It
;;; is not updated as the elements change.

(defun describe-frame-that-is-either-g2-array-or-g2-list (item)
  (let* ((frames-to-show nil)
         (class-of-item (class item))
         (element-type
           (frame-class-case item
             (g2-array (g2-array-element-type item))
             (g2-list (list-type item))))
         (reclaim-array-managed-float-elements? nil)
         (list-of-elements
           ;; Arrays and lists must be active to contain elements.
           ;; Not now that we have permanent lists and arrays.
           (frame-class-case item
               (g2-array
                 (when (or (and (array-is-permanent item)
                                (simple-vector-p (managed-g2-array item))
                                ;; This case is guarding against the possibility
                                ;; of describing an inactive non-permanent value array
                                ;; has been edited to be permanent but not yet activated.
                                (or (not (frame-of-class-p item 'value-array))
                                    (and (not (zerop (g2-array-length item)))
                                         (g2-array-aref item 0))))
                           (active-p item))
                   (when (eq element-type 'float)
                     (setq reclaim-array-managed-float-elements? t))
                 (let ((head? nil) (tail? nil))
                   (do-g2-array-elements (element item head?)
                     (enqueue-1
                       (if (number-needing-boxing-p element)
                           (allocate-managed-float element)
                           element)
                       head? tail? g2-list-cons))))) ; use g2-list cons pool so
               (g2-list                        ;   same as g2-list-elements
                 (when (or (list-is-permanent item) (active-p item))
                   (when (list-structure item)
                     (g2-list-elements item))))))
         (element-type-spec-contains-datum?
           (type-specification-for-user-or-datum-type element-type)))
    (when list-of-elements
      (setq frames-to-show
            (cond
              ((and element-type-spec-contains-datum?
                    (not (eq element-type-spec-contains-datum? 'item-or-datum)))
               (describe-g2-array-or-list-datum-elements
                 list-of-elements element-type class-of-item))
              (t
               (describe-g2-array-or-list-item-or-datum-elements
                 list-of-elements element-type class-of-item
                 (or (null element-type-spec-contains-datum?)
                     (not (eq element-type-spec-contains-datum?
                              'item-or-datum)))))))
      (when reclaim-array-managed-float-elements?
        (loop for element in list-of-elements
              do
          (when (managed-float-p element)
            (reclaim-managed-float element))))
      (reclaim-g2-list-list list-of-elements))
    frames-to-show))

(def-substitution-macro tformat-g2-array-or-list-datum-element
    (element element-type)
  (cond
    ((null element)
     (twrite-string "no value"))
    ((and (eq element-type 'truth-value) (fixnump element))
     ;; Truth-value-arrays contain integers.
     (tformat
       "~NC" element 'truth-value))
    ((evaluation-value-p element)
     (tformat "~NV" element))
    ((temporary-constant-p element)
     (tformat
       "~NC" (cached-constant-value element) (constant-type element)))
    ((framep element)
     (tformat "~NF" element))
    ;; Should not reach this condition.
    (t (twrite-string "unknown value"))))

(defun describe-g2-array-or-list-item-or-datum-elements
    (list-of-elements element-type class-of-item items-only?)
  (let ((frames-to-show
         (eval-list
           (make-description-box
             (tformat-text-string
               "The following are the elements of this ~(~a~):"
               class-of-item)))))
    (loop for element in list-of-elements
          do (setq frames-to-show
                   (eval-cons
                     (cond
                       ((null element)
                        (make-description-box
                           (copy-text-string
                             (if items-only? "no item" "no item or value"))))
                       ((or items-only? (framep element))
                        (make-short-representation element nil 'small))
                       (t
                        (make-description-box-with-text
                          (twith-output-to-text
                            (tformat-g2-array-or-list-datum-element
                              element element-type)))))
                     frames-to-show)))
    frames-to-show))



;;; The variable `maximum-number-of-array-or-list-elements-to-describe' is the
;;; limit on the number of list or array elements to "describe".  This is needed
;;; so that we do not print very long lists or arrays, which could require
;;; strings longer than the maximum allowed.

(defvar maximum-number-of-array-or-list-elements-to-describe 1000)

(defun describe-g2-array-or-list-datum-elements
    (list-of-elements element-type class-of-item)
  (eval-list
    (make-description-box-with-text
      (twith-output-to-text
        (tformat
          "The following ~a of this ~(~a~):~%"
          (if (cdr list-of-elements)
              "values are members"
              "value is a member")
          class-of-item)
        (loop for element in list-of-elements
              as index from 0
              while (<f index
                        maximum-number-of-array-or-list-elements-to-describe)
              do
          (unless (=f index 0)
            (twrite-string ", "))
          (tformat "[~d] " index) ; added for 4.0 (MHD 10/28/94)
          (tformat-g2-array-or-list-datum-element element element-type)
              finally
                (twrite-string ".")
                (unless (<f index
                            maximum-number-of-array-or-list-elements-to-describe)
                  (let ((number-of-elements-not-printed
                          (-f (length list-of-elements) index)))
                    (tformat
                      "~%This operation describes at most ~a elements.  ~
                      There ~a ~a remaining element~a."
                      maximum-number-of-array-or-list-elements-to-describe
                      (if (=f number-of-elements-not-printed 1) "is" "are")
                      number-of-elements-not-printed
                      (if (=f number-of-elements-not-printed 1) "" "s")))))))))



;;; The describe-frame method on a variable-or-parameter will
;;; descibe how this is involved in any simulations.

(def-class-method describe-frame (variable-or-parameter)
  (let ((frames-to-show nil)
        (initial-value? nil)
        (simulation-info? (simulation-info? variable-or-parameter)))
    (when simulation-info?
      (let ((class-to-print
              (if (frame-of-class-p variable-or-parameter 'variable) 'variable 'parameter))
            (simulation-specifier-to-use
              (get-simulation-specifier-to-use variable-or-parameter)))
        (cond
          ((simulation-subtable-p simulation-specifier-to-use)
           (setq frames-to-show
                 (eval-cons
                   (with-output-to-description-box
                     (tformat
                       "This ~(~a~) is simulated using the simulation formula ~
                            in its simulation subtable." class-to-print))
                   frames-to-show)))
          (t
           (setq frames-to-show
                 (eval-cons
                   (with-output-to-description-box
                     (tformat
                       "This ~(~a~) is simulated using the following ~a."
                       class-to-print
                       (if (generic-simulation-formula-p
                             simulation-specifier-to-use)
                           "generic simulation formula"
                           "external simulation definition")))
                   frames-to-show))
           (setq frames-to-show
                 (eval-cons
                   (make-short-representation
                     simulation-specifier-to-use nil 'small)
                   frames-to-show))))
        (setq frames-to-show
              (eval-cons
                (with-output-to-description-box
                  (tformat
                    "The simulation category is ~(~a~)."
                    (simulation-category simulation-info?))
                  (cond
                    ((and (variable-p variable-or-parameter)
                          (non-default-initial-simulated-value? variable-or-parameter))
                     (setq initial-value? (non-default-initial-simulated-value? variable-or-parameter)))
                    (t
                     (setq initial-value? (initial-value? simulation-info?))))
                  (when initial-value?
                    (with-temporary-gensym-float-creation initial-value
                      (tformat
                        "  The initial value is ~(~a~)."
                        (if (slot-value-float-p initial-value?)
                            (slot-value-float-value initial-value?)
                            initial-value?))))
                  (with-temporary-gensym-float-creation describe-time-increment
                    (let ((specific-time-increment?
                            (slot-value-number-value
                              (specific-time-increment? simulation-info?))))
                      (when specific-time-increment?
                        (tformat
                          "  The non-default time increment is ~(~a~) ~(~a~)."
                          specific-time-increment?
                          (if (= specific-time-increment? 1)
                              'second 'seconds))))))
                frames-to-show))
        (when (model-definition? simulation-info?)
          (setq frames-to-show
                (eval-cons
                  (with-output-to-description-box
                    (tformat
                      "This ~(~a~) belongs to the following model definition."
                      class-to-print))
                  frames-to-show))
          (setq frames-to-show
                (eval-cons
                  (make-short-representation
                    (model-definition? simulation-info?) nil 'small)
                  frames-to-show)))))
    (nconc (funcall-superior-method variable-or-parameter)
           frames-to-show)))



;;; The describe-frame for a variable will ...

(def-class-method describe-frame (variable)
  (let*
      ((frames-to-show nil)
       (class-of-item (class variable))
       (forward-chain? (forward-chain-p variable))
       (depth-first? (depth-first-p variable))
       (dont-data-seek? (passive-p variable))
       (data-server? (get-data-server variable))
       (name-of-data-server?
        (if (data-server-p data-server?)
            (name-of-data-server data-server?)
          data-server?))
       (manually-disabled? (manually-disabled-p variable))
       (disabled-through-ancestor? (ancestor-not-activatable-p variable))
       (dont-backward-chain? (dont-backward-chain-p variable))
       (specific-formula? (car (formula? variable)))
       (generic-formulas (collect-generic-formulas-for-variable variable))
       (data-type (type-specification-of-variable-or-parameter-value variable))
       (backward-chaining-links
        (unless (or dont-data-seek? dont-backward-chain?)
          (let ((*links-and-objects* nil))
            (collect-rules-for-backward-chaining variable data-type)
            *links-and-objects*)))
       (backward-chaining-rules
        (rules-in-backward-link-list backward-chaining-links))

       forward-chaining-frames-to-show
       forward-chaining-rules)
    (setq frames-to-show
          (eval-cons
           (with-output-to-description-box
             (cond (manually-disabled?
                    (tformat
                     "Please note that this variable has been disabled!  "))
                   (disabled-through-ancestor?
                    (tformat
                     "Please note that this variable is disabled because ~
                        it has a disabled parent or ~
                        is on a subworkspace of an object with the ~
                        deactivatable subworkspaces capability.  ")))
             (if name-of-data-server?
                 (progn
                   (tformat "The data server for this variable is the ")
                   (write-data-server-map-from-slot name-of-data-server? nil)
                   (tformat "."))
               (tformat
                "This variable references an UNDEFINED data map or alias!"))
             (cond (dont-data-seek?
                    (tformat "  This variable does not seek data."))
                   ((neq data-server? 'computation)
                    (tformat
                     "  This variable will seek data from its data server."))
                   (dont-backward-chain?
                    (tformat
                     "  This variable does not backward chain."))
                   (depth-first?
                    (tformat
                     "  This variable depth first backward chains to rules."))
                   (t
                    (tformat
                     "  This variable breadth first backward chains to rules.")))
             (tformat
              (if forward-chain?
                  "  This variable may cause forward chaining when it ~
                     receives a new value."
                "  This variable may not cause forward chaining when it ~
                     receives a new value.")))
           frames-to-show))

    ;; The following section describes a GSI variable, and checks
    ;; matters of consistency with its corresponding GSI interface object.
    ;; (jh, 3/14/90)

    (let ((item-has-gsi-data-service-p (gsi-data-service-p-function variable))
          (item-has-gsi-message-service-p (gsi-message-service-p-function variable)))
      (when (or item-has-gsi-data-service-p
                item-has-gsi-message-service-p)
        (let* ((item-has-both-gsi-services-p
                (and item-has-gsi-data-service-p
                     item-has-gsi-message-service-p))
               (gsi-interface-name
                (get-slot-value-if-any variable 'gsi-interface-name))
               (gsi-interface
                (and gsi-interface-name
                     (get-instance-with-name-if-any 'object gsi-interface-name)))
               (interface-has-capability-p
                (and gsi-interface
                     (gsi-interface-p-function gsi-interface)))
               (required-sensor-id-attribute-or-attributes
                (and gsi-interface
                     (get-slot-value-if-any
                      gsi-interface
                      'identifying-attributes)))
               (disjoint-sensor-attributes-p
                (if (consp required-sensor-id-attribute-or-attributes)
                    (loop for required-sensor-id-attribute
                          in required-sensor-id-attribute-or-attributes
                          never (attribute-of-class-p
                                 required-sensor-id-attribute
                                 class-of-item))
                  (not (attribute-of-class-p
                        required-sensor-id-attribute-or-attributes
                        class-of-item)))))
          (setq frames-to-show
                (eval-cons
                 (with-output-to-description-box
                   (block describing-gsi-sensor

                     ;; Describe types of gsi service.
                     (tformat "This variable has ")
                     (when item-has-gsi-data-service-p
                       (tformat "GSI data service "))
                     (when item-has-both-gsi-services-p
                       (tformat "and "))
                     (when item-has-gsi-message-service-p
                       (tformat "GSI message service "))
                     (if item-has-both-gsi-services-p
                         (tformat "capabilities.  ")
                       (tformat "capability.  "))

                     ;; Give interface name.
                     (cond (gsi-interface-name
                            (tformat "The interface name of this variable is ~a.  "
                                     gsi-interface-name))
                           (t (tformat "Please note that no GSI interface name ~
                                           has been specified for this variable.  ")
                              (return-from describing-gsi-sensor)))

                     ;; Check if interface exists.
                     (unless gsi-interface
                       (tformat "Please note that no object named ~a exists."
                                gsi-interface-name)
                       (return-from describing-gsi-sensor))

                     ;; Check for interface capability.
                     (unless interface-has-capability-p
                       (tformat "Please note that the object ~a does not have ~
                                    GSI interface configuration capability.  "
                                gsi-interface-name)
                       (return-from describing-gsi-sensor))

                     ;; Check for sensor ID attributes.
                     (unless required-sensor-id-attribute-or-attributes
                       (tformat "Please note that the interface object named ~a ~
                                    contains no attributes which identify a sensor.  "
                                gsi-interface-name)
                       (return-from describing-gsi-sensor))

                     ;; Check sensor ID attributes for consistency.
                     (when disjoint-sensor-attributes-p
                       (tformat "Please note that the GSI interface object ~a ~
                                    expects this variable to have "
                                gsi-interface-name)
                       (if (consp required-sensor-id-attribute-or-attributes)
                           (case (length required-sensor-id-attribute-or-attributes)
                             (1 (tformat "the attribute ~a.  "
                                         (first required-sensor-id-attribute-or-attributes)))
                             (2 (tformat "at least one of the attributes ~a or ~a.  "
                                         (first required-sensor-id-attribute-or-attributes)
                                         (second required-sensor-id-attribute-or-attributes)))
                             (t (tformat "at least one of the following attributes: ")
                                (loop for (required-attribute . remaining-required-attributes)
                                      on required-sensor-id-attribute-or-attributes
                                      do (case (length remaining-required-attributes)
                                           (0 (tformat "~a.  " required-attribute))
                                           (1 (tformat "~a, or " required-attribute))
                                           (t (tformat "~a, " required-attribute))))))
                         (tformat "the attribute ~a.  "
                                  required-sensor-id-attribute-or-attributes))
                       (tformat "However, this variable lacks ")
                       (if (consp required-sensor-id-attribute-or-attributes)
                           (case (length required-sensor-id-attribute-or-attributes)
                             (1 (tformat "the expected attribute.  "))
                             (2 (tformat "either of the expected attributes.  "))
                             (t (tformat "any of the expected attributes.  ")))
                         (tformat "the expected attribute.  "))
                       (return-from describing-gsi-sensor))))
                 frames-to-show)))))
    ;; End of description specific to gsi sensor variables.

    (when specific-formula?
      (setq
       frames-to-show
       (eval-cons
        (make-description-box
         (twith-output-to-text-string
           (tformat
            "This variable receives its value from this specific formula.")))
        frames-to-show))

      (setq frames-to-show
            (eval-cons
             (make-description-box-with-text
              (copy-text (cdr (formula? variable))))
             frames-to-show)))

    (when generic-formulas
      (if (null specific-formula?)
          (setq frames-to-show
                (eval-cons
                 (make-description-box
                  (twith-output-to-text-string
                    (if (cdr generic-formulas)
                        (tformat
                         "The variable receives its value from this generic ~
                             formula, and the following formulas are shadowed ~
                             by it.")
                      (tformat
                       "The variable receives its value from this generic ~
                             formula."))))
                 frames-to-show))
        (setq frames-to-show
              (eval-cons
               (make-description-box
                (twith-output-to-text-string
                  (tformat
                   "The following generic formula~a shadowed by the ~
                         specific formula."
                   (if (cdr generic-formulas)
                       "s are"
                     " is"))))
               frames-to-show)))
      (loop for generic in generic-formulas
            for short-representation
            = (make-short-representation generic nil 'small)
            do
            (setq frames-to-show (eval-cons short-representation frames-to-show))))
    (when backward-chaining-links
      (if (or specific-formula? generic-formulas)
          (setq frames-to-show
                (eval-cons
                 (make-description-box
                  (twith-output-to-text-string
                    (tformat
                     "The following backward chaining rule~a shadowed by ~
                         the formula."
                     (if (cdr backward-chaining-links)
                         "s are"
                       " is"))))
                 frames-to-show))
        (setq frames-to-show
              (eval-cons
               (make-description-box
                (twith-output-to-text-string
                  (tformat
                   "The following rule~a ~abackward chained to to ~
                         supply a value for the variable."
                   (if (cdr backward-chaining-links) "s are" " is")
                   (if (cdr backward-chaining-links)
                       (if depth-first? "depth first " "breadth first ")
                     ""))))
               frames-to-show)))
      (setq frames-to-show
            (nconc (short-representations-of-backward-invocations
                    backward-chaining-links)
                   frames-to-show)))
    (reclaim-eval-tree backward-chaining-links)
    (reclaim-eval-list generic-formulas)

    (multiple-value-setq (forward-chaining-frames-to-show forward-chaining-rules)
        (collect-all-rules-for-forward-chaining variable))

    (setq frames-to-show
          (nconc forward-chaining-frames-to-show frames-to-show))

    (setq backward-chaining-rules
          (nconc backward-chaining-rules forward-chaining-rules))

    (setq frames-to-show
          (nconc (collect-all-mentioning-rules variable backward-chaining-rules)
                 frames-to-show))

    (reclaim-eval-list backward-chaining-rules)
    (nconc (funcall-superior-method variable)
           frames-to-show)))



;;; The describe-frame method for a parameter will ...

(def-class-method describe-frame (parameter)
  (let
    ((frames-to-show nil)
     (forward-chain? (forward-chain-p parameter))
     (manually-disabled? (manually-disabled-p parameter))
     (disabled-through-ancestor? (ancestor-not-activatable-p parameter))
     forward-chaining-frames-to-show)

    (setq frames-to-show
          (eval-cons
            (with-output-to-description-box
              (cond (manually-disabled?
                     (tformat
                       "Please note that this parameter has been disabled!  "))
                    (disabled-through-ancestor?
                     (tformat
                       "Please note that this parameter is disabled because ~
                            it has a disabled parent or ~
                            is on a subworkspace of an object with the ~
                            deactivatable subworkspaces capability.  ")))
              (tformat
                (if forward-chain?
                    "This parameter may cause forward chaining when it ~
                     receives a new value."
                    "This parameter may not cause forward chaining when it ~
                     receives a new value.")))
            frames-to-show))

    (multiple-value-setq-some (forward-chaining-frames-to-show nil)
      (collect-all-rules-for-forward-chaining parameter))
    (setq frames-to-show
          (nconc forward-chaining-frames-to-show frames-to-show))
    (nconc (funcall-superior-method parameter)
           frames-to-show)))




;;; The class-method `describe-frame' describes the image represented by
;;; an image-definition.

(def-class-method describe-frame (image-definition)
  (nconc
    (funcall-superior-method image-definition)
    (let ((frames ())
          (image-data? (image-definition-cached-data? image-definition)))
      ;; Mention its format, whether cached, how many bytes consumed (including renderings?).
      (when image-data?
        (eval-push
          (tformat-text-string "This is a ~dx~dx~d ~a image"
                               (image-data-width image-data?)
                               (image-data-height image-data?)
                               (image-data-depth image-data?)
                               (or (image-data-format image-data?) ""))
          frames))
      (nreverse frames))))



;;; The describe-frame method on method-declarations lists the specific-procedure-
;;; methods, by class, that define a method of this name.

(def-class-method describe-frame (method-declaration)
  (let* ((frames-to-show nil)
         (description-header nil)
         (name-or-names? (name-or-names-for-frame method-declaration))
         (method-name?
           (and name-or-names? (symbolp name-or-names?) name-or-names?))
         (specific-methods-defined-p? nil))

    (when method-name?
      (loop for (class . nil) in (classes-of-procedure-method method-name?)
            for class-methods? =
               (get-named-procedure-methods-for-class method-name? class)
            do
        (when class-methods?
          (setq specific-methods-defined-p? t)
          (loop for specific-method in (cdr class-methods?)
                do
            (setq frames-to-show
                  (eval-cons
                    (make-short-representation specific-method        nil 'small)
                    frames-to-show))))))
    (setq description-header
          (make-description-box
            (cond
              (specific-methods-defined-p?
               (tformat-text-string
                 "The following are methods defined for ~
                  this method-declaration:"))
              (t
               (tformat-text-string
                 "There are no methods defined for this ~
                  method-declaration.")))))
    (nconc
      (funcall-superior-method method-declaration)
      (nconc frames-to-show (eval-list description-header)))))



(def-class-method describe-frame (class-definition)
  (let* ((class-methods?
           (procedure-methods-of-class (name-of-defined-class class-definition)))
         (frames-to-show?
           (when class-methods?
             (loop with short-representations = nil
                   for method-information in class-methods?
                   do
               (loop for method in (cdr method-information)
                     do
                 (setq short-representations
                       (eval-cons
                         (make-short-representation method nil 'small)
                         short-representations)))
                   finally (return short-representations))))
         (description-header
           (make-description-box
             (if class-methods?
                 (tformat-text-string
                   "The following methods are defined specifically for this class.")
                 (tformat-text-string
                   "There are no methods defined specifically for this class.")))))
    (nconc
      (funcall-superior-method class-definition)
      (nconc frames-to-show? (eval-list description-header)))))






;;;; Describe: Disassembly Support




(defun disassemble-item-if-appropriate (item)
  (let ((code-bodies-and-denotations? nil)
        (g2-cell-array? (cell-array item)))
    (macrolet ((note-code-body (denotation code-body)
                               `(eval-push (eval-cons ,denotation ,code-body) code-bodies-and-denotations?)))
      (when g2-cell-array?
        (let ((managed-array (g2-cell-array-managed-array g2-cell-array?)))
          (when managed-array
            (loop with current-computation-component-particulars = (slot-value-list 'cell-array-element 0)
                  for index from 0 below (managed-array-length managed-array)
                  for element = (managed-svref managed-array index)
                  do
              (when (of-class-p-function element 'g2-expression-cell)
                (setf (second current-computation-component-particulars) index)
                (note-code-body
                  (twith-output-to-text-string
                    (twrite-string "Disassembly for ")
                    (denote-component-of-block nil))
                  (g2-expression-cell-byte-code-body element)))
                  finally
                    (reclaim-slot-value-list current-computation-component-particulars)))))
      (frame-class-case item
        (procedure
          (when (code-bodies item)
            (return-from disassemble-item-if-appropriate
              (eval-list
                (make-description-box-with-text
                  (twith-output-to-text
                    (write-disassembled-code-bodies (code-bodies item))))))))
        (function-definition
          (note-code-body nil (function-definition-byte-code-body item)))
        (rule
          (note-code-body nil (rule-byte-code-body item)))
        (generic-simulation-formula
          (note-code-body (copy-constant-wide-string #w"Disassembly of the formula:")
                          (generic-simulation-formula-byte-code-body item))
          (when (generic-simulation-initial-value-byte-code-body item)
            (note-code-body (copy-constant-wide-string #w"Disassembly of the inital value expression:")
                            (generic-simulation-initial-value-byte-code-body item))))
        (simulation-subtable
          (note-code-body nil (simulation-subtable-byte-code-body item))
          (note-code-body (copy-constant-wide-string #w"Disassembly of the initial value expression:")
                          (simulation-subtable-initial-value-byte-code-body item)))
        (action-button
          (when (get-slot-value item 'embedded-rule?)
            (note-code-body nil (rule-byte-code-body (get-slot-value item 'embedded-rule?)))))
        (user-menu-choice
          (when (embedded-rule-in-user-menu-choice? item)
            (note-code-body nil (rule-byte-code-body (embedded-rule-in-user-menu-choice? item))))))

      (setq code-bodies-and-denotations? (nreverse code-bodies-and-denotations?))
      (loop with frames-to-show = nil
            for (denotation? . code-body?) in code-bodies-and-denotations?
            do
          (eval-push
            (make-description-box
              (if denotation?
                  denotation?
                  (copy-constant-wide-string #w"Disassembly:")))
            frames-to-show)
          (eval-push
            (make-description-box-with-text
              (if (byte-code-body-p code-body?)
                  (twith-output-to-text
                    (write-byte-code-body
                      code-body?
                      (byte-code-body-constant-vector code-body?)))
                  (convert-text-string-to-text
                    (copy-constant-wide-string #w"No code body"))))
            frames-to-show)
            finally
              (reclaim-eval-tree code-bodies-and-denotations?)
              (return frames-to-show)))))






;;;; Describe: Generic Formula Utilities




;;; The function `collect-generic-formulas-for-variable' collects and returns an
;;; eval cons list of all generic formulas which apply to a given variable.
;;; They are listed in order of specificity, with the most specific being the
;;; one refering the to most specific class of the parent.

(defun collect-generic-formulas-for-variable (variable)
  (multiple-value-bind (parent-entity? slot-name defining-class?)
      (get-kb-parent-information variable)
    ;; FIND ME, JRA  -jra 11/6/96
    (DECLARE (IGNORE DEFINING-CLASS?))        ; JRA -- work to do here!
    (if parent-entity?
        (loop with generic-formulas = (formulas-for-this-role
                                        (unqualified-name slot-name))
              with found-formulas = nil
              for class in (class-inheritance-path
                             (class-description-slot parent-entity?))
              do
          (loop for formula in generic-formulas
                do
            (when (and (eq class (formula-class formula))
                       (or (and (not system-is-running)
                                (not system-has-paused))
                           (runnable-p formula)))
              (setq found-formulas
                    (eval-cons formula found-formulas))))
              finally
                (return (nreverse found-formulas))))))






;;;; Describe: Utilities That Understand Chaining



;;; The function `rules-in-backward-link-list' returns an eval cons list of the
;;; rules in the given list of backward chaining links.  Similarly, the function
;;; `rules-in-forward-link-list' returns an eval cons list of the rules in the
;;; given list of forward chaining links.  Note that some of the links in the
;;; list may contain references to true value update functions, and so are not
;;; reflected in the returned list.

(defun rules-in-backward-link-list (link-list)
  (loop for link-entry in link-list
        collect (backward-link-rule (car link-entry)) using eval-cons))

(defun rules-in-forward-link-list (link-list)
  (loop for link-entry in link-list
        for recipient = (forward-link-recipient (car link-entry))
        when (of-class-p recipient 'rule)
          collect recipient using eval-cons))



;;; The function `collect-all-rules-for-forward-chaining' performs a search
;;; which finds all rules which could be forward chained to if this variable
;;; were to receive a value.  It returns two values.  The first is an eval list
;;; of short representations which should be added to the describe display for
;;; the variable.  These short representations will describe all forward
;;; chaining proceeding from this variable and the values needed for each
;;; scenario.  The second value is a list of the rules which are represented in
;;; the description.  Note that it is possible, though unlikely, that a
;;; particular rule will be in this list more than once.

(defun collect-all-rules-for-forward-chaining (variable)
  (let* ((variable-name-or-names?
           (name-or-names-for-frame variable))
         (variable-name-cons?
           (if (and variable-name-or-names?
                    (symbolp variable-name-or-names?))
               (setq variable-name-or-names?
                     (eval-cons-macro variable-name-or-names? nil))
               nil))
         (parent-stack (make-parent-stack variable))
         (data-type (type-specification-of-variable-or-parameter-value variable)))
    (multiple-value-bind (result rule-list)
        (cond ((eq data-type 'truth-value)
               (collect-all-rules-for-logical-forward-chaining
                 variable variable-name-or-names? parent-stack))
              ((eq data-type 'symbol)
               (collect-all-rules-for-symbolic-forward-chaining
                 variable parent-stack variable-name-or-names?))
              (t
               (collect-all-rules-for-general-forward-chaining
                 variable variable-name-or-names? parent-stack)))
      (reclaim-parent-stack parent-stack)
      (if variable-name-cons?
          (reclaim-eval-cons variable-name-cons?))

      ;; Result is now an eval cons list of {text-box|table}.
      ;;
      ;; Rule-list is now an eval cons list of rules incorporated into
      ;; result.

      (values result rule-list))))

(defun collect-all-rules-for-logical-forward-chaining
       (variable variable-names parent-stack)
  (let ((truth-chaining nil) (falsity-chaining nil) (either-chaining nil)
        (*links-and-objects* nil)
        (descriptive-elements-to-show nil)
        (rule-list nil))
    (collect-rules-for-logical-forward-chaining
     variable 1000 (forward-chain-p variable) parent-stack variable-names)
    (setq truth-chaining *links-and-objects*)
    (setq *links-and-objects* nil)
    (collect-rules-for-logical-forward-chaining
     variable -1000 (forward-chain-p variable) parent-stack variable-names)
    (setq falsity-chaining *links-and-objects*)
    (loop for truth-entry in truth-chaining
          do (loop for falsity-entry in falsity-chaining
                   when (equal truth-entry falsity-entry)
                   do (setq truth-chaining
                            (delete-eval-element truth-entry truth-chaining))
                   (setq either-chaining
                         (eval-cons truth-entry either-chaining))
                   (setq falsity-chaining
                         (delete-eval-element falsity-entry falsity-chaining))
                   (reclaim-eval-cons falsity-entry)
                   (loop-finish)))
    (loop for logical-case in '(true false any)
          as links-and-object-list
          = (case logical-case
              (true truth-chaining) (false falsity-chaining) (t either-chaining))
          as descriptive-text-string
          = (tformat-text-string
             "These rules are forward chained to when ~a is received."
             (case logical-case
               (true "true") (false "false") (t "any new value")))
          as descriptive-elements-for-chaining
          = (short-representations-of-forward-invocations links-and-object-list)
          do (setq descriptive-elements-to-show
                   (nconc descriptive-elements-for-chaining
                          (eval-cons
                           (make-description-box descriptive-text-string)
                           descriptive-elements-to-show))))
    (setq rule-list
          (nconc (rules-in-forward-link-list either-chaining)
                 (rules-in-forward-link-list falsity-chaining)
                 (rules-in-forward-link-list truth-chaining)))
    (reclaim-eval-tree either-chaining)
    (reclaim-eval-tree falsity-chaining)
    (reclaim-eval-tree truth-chaining)
    (values descriptive-elements-to-show rule-list)))

(defun collect-all-rules-for-general-forward-chaining
       (variable variable-names parent-stack)
  (let ((*links-and-objects* nil)
        (descriptive-elements-to-show nil)
        (rule-list nil))
    (collect-rules-for-general-forward-chaining
     variable (forward-chain-p variable) parent-stack variable-names)
    (let ((short-representations-of-chaining
           (short-representations-of-forward-invocations *links-and-objects*)))
      (when short-representations-of-chaining
        (setq descriptive-elements-to-show
              (eval-cons
               (let ((descriptive-text-string
                      (tformat-text-string
                       "These rules are forward chained to when a value is ~
                           received.")))
                 (make-description-box descriptive-text-string))
               descriptive-elements-to-show))
        (setq descriptive-elements-to-show
              (nconc short-representations-of-chaining
                     descriptive-elements-to-show))))
    (setq rule-list (rules-in-forward-link-list *links-and-objects*))
    (reclaim-eval-tree *links-and-objects*)
    (values descriptive-elements-to-show rule-list)))


(defun collect-all-rules-for-symbolic-forward-chaining
       (variable parent-stack variable-name-or-names?)
  (let ((possible-values? nil)
        (parent-stack-entry (car parent-stack))
        (*links-and-objects* nil)
        (rule-list nil))
    ;; First chain on references to a parent entity.  This is so
    ;; that we can find a set of possible values for this variable
    ;; as the first thing that happens, if that list is available.
    (when parent-stack-entry
      ;; If we've got a parent entity, get the set of possible values.
      (setq possible-values?
            (value-set-given-attribute-and-class
             (parent-stack-attribute parent-stack-entry)
             (class (parent-stack-frame parent-stack-entry))))

      ;; If there are names for this parent object, chain on direct
      ;; references to names.
      (loop for name-for-parent?
            in (parent-stack-parent-names parent-stack-entry)
            do
            (loop for link in (forward-chaining-list name-for-parent?)
                  for symbolic-value = (forward-link-symbolic-value link)
                  for sense = (forward-link-sense link)
                  do
                  (if (and (symbolic-sense-matches-for-all-p
                            possible-values?
                            symbolic-value
                            sense
                            (forward-chain-p variable))
                           (symbolp (forward-link-designation link)))
                      (add-tuple-to-link-list link nil))))
      ;; Chain on the attribute of the parent, to handle the case of
      ;; references to the variable through a named attribute of an
      ;; object.
      (loop for link in (forward-chaining-list
                         (parent-stack-attribute parent-stack-entry))
            for link-symbolic-value = (forward-link-symbolic-value link)
            for link-sense = (forward-link-sense link)
            do
            (when (symbolic-sense-matches-for-all-p
                   possible-values?
                   link-symbolic-value
                   link-sense
                   (forward-chain-p variable))
              (let ((parent-frame? (find-referenced-parent
                                    parent-stack
                                    (forward-link-designation link))))
                (if parent-frame?
                    (add-tuple-to-link-list link parent-frame?)))))
      ;; Chain on the references to this variable through the class of
      ;; its parent entity.
      (collect-all-forward-chaining-for-symbolic-class-references
       (parent-stack-frame parent-stack-entry) possible-values? t
       (forward-chain-p variable))
      ;; Chain on the references to the parent through attributes of
      ;; its further parent, if any.
      (when (cdr parent-stack)
        (setq parent-stack-entry (second parent-stack))
        (loop for link in (forward-chaining-list
                           (parent-stack-attribute parent-stack-entry))
              for link-symbolic-value = (forward-link-symbolic-value link)
              for link-sense = (forward-link-sense link)
              do
              (when (symbolic-sense-matches-for-all-p
                     possible-values? link-symbolic-value
                     link-sense (forward-chain-p variable))
                (let ((parent-frame? (find-referenced-parent
                                      (cdr parent-stack)
                                      (forward-link-designation link))))
                  (if parent-frame?
                      (add-tuple-to-link-list link parent-frame?)))))) )
    ;; Next, chain on references directly to the variable itself.
    ;; First, references to the name of the variable.
    (loop for name-for-variable in variable-name-or-names?
          do
          (loop for link in (forward-chaining-list name-for-variable)
                for symbolic-value = (forward-link-symbolic-value link)
                for sense = (forward-link-sense link)
                do
                (if (and (symbolic-sense-matches-for-all-p
                          possible-values? symbolic-value sense
                          (forward-chain-p variable))
                         (symbolp (forward-link-designation link)))
                    (add-tuple-to-link-list link nil))))
    ;; Next, chain on references to this variable through its class.
    (collect-all-forward-chaining-for-symbolic-class-references
     variable possible-values? nil (forward-chain-p variable))
    ;; Sort the frames into categories depending on whether they get chained to
    ;; for specific new values or whether they are value independent.
    (let ((descriptive-elements-to-show nil))
      (when *links-and-objects*
        (let ((any-value-chaining nil)
              (value-dependent-chaining nil))
          (loop for link-and-object in *links-and-objects*
                for sense = (forward-link-sense (car link-and-object))
                do
                (when (of-class-p (forward-link-recipient (car link-and-object))
                                  'rule)
                  (if (memq sense '(either receives-a-value))
                      (setq any-value-chaining
                            (eval-cons link-and-object any-value-chaining))
                    (let* ((value (forward-link-symbolic-value
                                   (car link-and-object)))
                           (entry-for-value
                            (assq value value-dependent-chaining)))
                      (when (null entry-for-value)
                        (setq entry-for-value (eval-list value nil nil))
                        (setq value-dependent-chaining
                              (eval-cons entry-for-value
                                         value-dependent-chaining)))
                      (if (eq sense t)
                          (setf (second entry-for-value)
                                (eval-cons link-and-object
                                           (second entry-for-value)))
                        (setf (third entry-for-value)
                              (eval-cons link-and-object
                                         (third entry-for-value))))))))
          ;; Next format these frames for display.
          (when value-dependent-chaining
            (loop for value-entry in value-dependent-chaining
                  for value = (first value-entry)
                  for match-chaining = (second value-entry)
                  for mismatch-chaining = (third value-entry)
                  do
                  (when match-chaining
                    (setq descriptive-elements-to-show
                          (eval-cons
                           (let ((descriptive-text-string
                                  (tformat-text-string
                                   "These rules are forward chained to when ~
                                   the value ~a is received."
                                   value)))
                             (make-description-box descriptive-text-string))
                           descriptive-elements-to-show))
                    (setq descriptive-elements-to-show
                          (nconc (short-representations-of-forward-invocations
                                  match-chaining)
                                 descriptive-elements-to-show))
                    (reclaim-eval-list match-chaining))
                  (when mismatch-chaining
                    (setq descriptive-elements-to-show
                          (eval-cons
                           (let ((descriptive-text-string
                                  (tformat-text-string
                                   "These rules are forward chained to when any ~
                                   value other than ~a is received."
                                   value)))
                             (make-description-box descriptive-text-string))
                           descriptive-elements-to-show))
                    (setq descriptive-elements-to-show
                          (nconc (short-representations-of-forward-invocations
                                  mismatch-chaining)
                                 descriptive-elements-to-show))
                    (reclaim-eval-list mismatch-chaining))
                  (reclaim-eval-list value-entry))
            (reclaim-eval-list value-dependent-chaining))
          (when any-value-chaining
            (setq descriptive-elements-to-show
                  (eval-cons
                   (let ((descriptive-text-string
                          (tformat-text-string
                           "These rules are forward chained to when any ~
                               new value is received.")))
                     (make-description-box descriptive-text-string))
                   descriptive-elements-to-show))
            (setq descriptive-elements-to-show
                  (nconc (short-representations-of-forward-invocations
                          any-value-chaining)
                         descriptive-elements-to-show))
            (reclaim-eval-list any-value-chaining)))
        (setq rule-list (rules-in-forward-link-list *links-and-objects*))
        (reclaim-eval-tree *links-and-objects*))
      (values descriptive-elements-to-show rule-list))))


(defun symbolic-sense-matches-for-all-p
       (possible-values stored-value sense chaining-as-well-as-events?)
  (or (eq sense 'receives-a-value)
      (and chaining-as-well-as-events?
           (or (eq sense 'either)
               (and (or (eq sense nil) (eq sense t))
                    (or (null possible-values)
                        (memq stored-value possible-values)))))))

(defun collect-all-forward-chaining-for-symbolic-class-references
       (object possible-values? stored-symbol-required? chaining-as-well-as-events?)
  ;; Iterate over each super-class of this class up to but not including
  ;; "entity".
  (loop for class in (class-inheritance-path
                       (class-description-slot object))
        do
    ;; Iterate over each link in each class list.
    (loop for link in (forward-chaining-list class)
          for symbolic-value = (forward-link-symbolic-value link)
          for sense = (forward-link-sense link)
          for designation = (forward-link-designation link)
          do
      (if (and (or (not stored-symbol-required?)
                   symbolic-value)
               (symbolic-sense-matches-for-all-p
                 possible-values?
                 symbolic-value
                 sense
                 chaining-as-well-as-events?)
               (not (symbolp designation))
               (not (and (domain-of-designation designation)
                         (symbolp (role-of-designation designation)))))
          (add-tuple-to-link-list link object)))
        until (eq class 'item)))




;;; The function `collect-all-mentioning-rules' takes an entity and a list of
;;; rules which should not be included in the returned list.  This function will
;;; return an eval cons list of short frame representations which list all rules
;;; in the current KB which contain designations which could apply to the given
;;; entity.  Note that this search does not verify that all roles and other
;;; contraints of the rule do actually apply to the given entity, but it does
;;; filter on class, attribute, and parent nesting considerations.

(defun collect-all-mentioning-rules (entity rules-to-exclude)
  (let ((mentioning-rules nil)
        (descriptive-elements-to-show nil)
        (parent-stack? (make-parent-stack entity)))
    (when parent-stack?
      (loop for rule being each class-instance of 'rule
            do
        (when (not (memq rule rules-to-exclude))
          (if (and (not (embedded-rule-p rule))
                   (rule-mentions-entity-p rule entity parent-stack?))
              (setq mentioning-rules (eval-cons rule mentioning-rules)))))
      (reclaim-parent-stack parent-stack?))
    (when mentioning-rules
      (setq descriptive-elements-to-show
            (eval-cons
              (let ((descriptive-text-string
                      (tformat-text-string
                        "The following rules mention the variable, though they are not ~
                         invoked via any chaining mechanisms.")))
                (make-description-box descriptive-text-string))
              descriptive-elements-to-show))
      (loop for rule in mentioning-rules
            do
        (setq descriptive-elements-to-show
              (eval-cons
                (make-short-representation rule nil 'small)
                descriptive-elements-to-show)))
      (reclaim-eval-list mentioning-rules))


    ;; Descriptive-elements-to-show is now an eval cons list of {text-box|table}
    ;; in reverse order of display.

    descriptive-elements-to-show))

(defun rule-mentions-entity-p (rule entity parent-stack)
  (let ((translation (get-new-translation-of-text-slot
                       (box-translation-and-text rule))))
    (when translation
      (let ((designations-in-rule nil))
        ;; First note then move past designations in FOR iterators in the
        ;; beginning of rules.
        (loop while (and (consp translation) (eq (first translation) 'for))
              do
          (lookup-previous-reference-and-note-designation (second translation))
          (setq translation (third translation)))
        ;; Next note the designations in the antecedent of the rule.
        (note-designations-in-expression-using-environment (second translation))
        ;; Next node the designations in the consequents of the rule.
        (note-designations-in-consequent-using-environment (third translation))
        ;; All designations have now been found, see if any of them could
        ;; reference this object.
        (prog1
          (loop for designation-entry in designations-in-rule
                for designation = (cdr designation-entry)
                do
            (if (picky-designation-could-denote-entity
                  designation entity parent-stack)
                (return t)))
          (reclaim-installation-tree designations-in-rule))))))


(defun picky-designation-could-denote-entity (designation entity parent-stack)
  (let ((role nil))
    (cond ((symbolp designation)
           (let ((name-or-names (name-or-names-for-frame entity)))
             (if (consp name-or-names)
                 (memq designation name-or-names)
                 (eq designation name-or-names))))
          ((symbolp (setq role (simple-role-of-role
                                 (role-of-designation designation))))
           (if (null (domain-of-designation designation))
               (frame-of-class-p entity role)
               (let ((simple-designation
                       (simple-installation-designation designation)))
                 (prog1
                   (not (null (find-referenced-parent
                                parent-stack simple-designation)))
                   (reclaim-installation-tree simple-designation)))))
          (t
           (let ((class? (atomic-class-element-of-role role)))
             (if class?
                 (frame-of-class-p entity class?)
                 nil))))))




;;; The function `note-designations-in-expression-using-environment' takes an
;;; expression and notes all designations within on the designations-in-rule
;;; special variable.  Note that this function is allowed to use the environment
;;; from the current KB to help resolve ambiguities designation, such as implied
;;; attributes.

(defun note-designations-in-expression-using-environment (expression)
  (cond ((null expression) nil)
        ((designation-p expression)
         (lookup-previous-reference-and-note-designation expression))
        ((consp expression)
         (let ((operator (first expression)))
           (when (symbolp operator)
             (case operator
               ((is is-not)
                (let* ((designation
                         (lookup-previous-reference-and-note-designation
                           (second expression)))
                       (class? (class-of-designation-result designation))
                       (symbolic-value (second (third expression)))
                       (attribute?
                         (when class?
                           (unique-attribute-of-class-with-potential-symbolic-value
                             class? symbolic-value))))
                  (when attribute?
                    (let ((new-designation
                            (eval-list
                              'the
                              attribute?
                              designation)))
                      (lookup-previous-reference-and-note-designation
                        new-designation)
                      (reclaim-eval-list new-designation)))))
               (t
                 (let ((template? (lookup-function-template operator)))
                   (if (null template?)
                       (loop for sub-expression in (cdr expression)
                             do
                         (note-designations-in-expression-using-environment sub-expression))
                       (note-designations-in-expression-given-template-using-environment
                         expression template?))))))))))

(defun note-designations-in-expression-given-template-using-environment
       (expression template)
  (loop for argument in (cdr expression)
        for argument-type in (cdr template)
        do
    (case argument-type
      ((expression)
       (note-designations-in-expression-using-environment argument))
      ((designation)
       (lookup-previous-reference-and-note-designation argument))
      ((scope)
       (let ((designation (installation-cons
                            'any
                            (copy-tree-using-installation-conses argument))))
         (lookup-previous-reference-and-note-designation designation)
         (reclaim-installation-tree designation)))
      ((other)
       t)
      (otherwise
        #+development
        (cerror "Continue."
                "Unknown argument type ~a from function template."
                argument-type)))))

(defun class-of-designation-result (designation)
  (cond ((symbolp designation)
         (let ((frames (frame-or-frames-with-this-name designation)))
           (cond ((framep frames)
                  (class frames))
                 ((consp frames)
                  (class (first frames)))
                 (t
                  nil))))
        ((consp designation)
         (let ((role (simple-role-of-role (role-of-designation designation))))
           (cond ((consp role)
                  (atomic-class-element-of-role role))
                 ((and (symbolp role)
                       (null (domain-of-designation designation)))
                  role)
                 (t nil))))
        (t nil)))

(defun note-designations-in-consequent-using-environment (consequent)
  (when (consp consequent)
    (case (car consequent)
      ((and in-order simultaneously)
       (loop for action in (cdr consequent)
             doing
         (note-designations-in-consequent-using-environment action)))
      ;; Note the designation which is being set.
      ((conclude-not conclude-has-no-current-value focus)
       (lookup-previous-reference-and-note-designation (second consequent)))
      ;; Note the designation which is being set.  If there is an expression
      ;; supplying a value for this conclusion, note the designations in it.
      ((conclude)
       (let ((designation
               (lookup-previous-reference-and-note-designation
                 (second consequent))))
         (when (third consequent)
           (note-designations-in-expression-using-environment (third consequent))
           (when (and (consp (third consequent))
                      (eq (first (third consequent)) 'quote)
                      (symbolp (second (third consequent))))
             (let* ((class? (class-of-designation-result designation))
                    (attribute?
                      (if class?
                          (unique-attribute-of-class-with-potential-symbolic-value
                            class? (second (third consequent))))))
               (when attribute?
                 (let ((new-designation (eval-list 'the attribute? designation)))
                   (lookup-previous-reference-and-note-designation new-designation)
                   (reclaim-eval-list new-designation))))))))
      ;; If this is an every action, note its scope and the actions in it.
      ((every)
       (let ((designation
               (eval-cons 'any
                          (copy-tree-using-eval-conses (second consequent)))))
         (lookup-previous-reference-and-note-designation designation)
         (reclaim-eval-tree designation))
       (note-designations-in-consequent-using-environment (third consequent)))
      ;; We don't need to add invoke-with-wait here because it's not allowed
      ;; for rules.  -dkuznick, 7/20/05
      ((invoke)
       (when (third consequent)
         (lookup-previous-reference-and-note-designation (third consequent))))
      ;; For the halt action, do nothing.
      ((halt)
       nil)
      ;; Get Michael's help on the inform structure.
      ((inform)
       (lookup-previous-reference-and-note-designation (second consequent))
       (let ((message (third consequent)))
         (when (consp message)
           (loop for expression in (cddr message) by #'cddr
                 do
             (note-designations-in-expression-using-environment expression)))))
      ((set)
       (lookup-previous-reference-and-note-designation (second consequent))
       (note-designations-in-expression-using-environment (third consequent)))
      ((activate deactivate)
       (lookup-previous-reference-and-note-designation (second consequent)))
      ((show hide)
       (lookup-previous-reference-and-note-designation (second consequent)))
      ((move set-position)
       (lookup-previous-reference-and-note-designation (second consequent))
       (note-designations-in-expression-using-environment (third consequent))
       (note-designations-in-expression-using-environment (fourth consequent)))
      ((rotate set-heading)
       (lookup-previous-reference-and-note-designation (second consequent))
       (note-designations-in-expression-using-environment (third consequent)))
      ((change-icon-color)
       (lookup-previous-reference-and-note-designation (second consequent))
       (when (consp (third consequent))
         (note-designations-in-expression-using-environment (second (third consequent)))))
      ;; Otherwise I don't know what it is, so don't analyze it.
      (t
        nil))))

;;; The function `short-representations-of-backward-invocations' returns an eval
;;; cons list of short representation frames which represent the list of
;;; backward chaining rule invocations given the list of backward chaining links
;;; and focus objects.


(defun short-representations-of-backward-invocations (link-and-objects-list)
  (let ((frames-to-show nil))
    (loop for entry in link-and-objects-list
          for link = (car entry)
          for object = (cdr entry)
          for rule = (backward-link-rule link)
          for focus? = (backward-link-focus link)
          for local-name? = (backward-link-focus-local-name link)
          do
      (if focus?
          (setq frames-to-show
                (eval-cons
                  (make-description-box
                    (twith-output-to-text-string
                      (tformat
                        "Invoked with focus on ~nf as the ~(~a~)"
                        object
                        focus?)
                      (if local-name?
                          (tformat " ~a:" local-name?)
                          (tformat ":"))))
                  frames-to-show)))
      (setq frames-to-show
            (eval-cons (make-short-representation rule nil 'small)
                       frames-to-show)))
    frames-to-show))





;;; The function `short-representations-of-forward-invocations' returns an eval
;;; cons list of short representation frames which represent the list of forward
;;; chaining rule invocations in the list of forward chaining links and focus
;;; objects.

(defun short-representations-of-forward-invocations (link-and-objects-list)
  (let ((descriptive-elements-to-show nil))
    (loop for entry in link-and-objects-list
          for link = (car entry)
          for object = (cdr entry)
          for rule = (forward-link-recipient link)
          for focus? = (forward-link-focus link)
          for local-name? = (forward-link-focus-local-name link)
          do
      (when (of-class-p rule 'rule)
        (if focus?
            (setq descriptive-elements-to-show
                  (let ((descriptive-text-string
                          (twith-output-to-text-string
                            (tformat
                              "Invoked with focus on ~nf as the ~(~a~)"
                              object
                              focus?)
                            (if local-name?
                                (tformat " ~a:" local-name?)
                                (tformat ":")))))
                    (eval-cons
                      (make-description-box
                        descriptive-text-string)
                      descriptive-elements-to-show))))
        (setq descriptive-elements-to-show
              (eval-cons
                (make-short-representation rule nil 'small)
                descriptive-elements-to-show))))
    descriptive-elements-to-show))







;;;; (NUPEC) Explanation

;;; The NUPEC Explanation facility has now become a standard part of G2.

;;; The explanation facility generates and displays explanations for a
;;; specified conclusion by presenting the data and rules used for the
;;; inference.  The user will access this facility by pre-setting options on
;;; variables (and possibly rules) to make them cache local explanations for
;;; their most recent values.  Explanations are transient objects which are made
;;; (using a new "create" action) to store an explanation of the value of a
;;; variable and to contain a display of the explanation on its subworkspace.
;;; Since values in G2 are constantly changing, an explanation must be stored so
;;; that it can be viewed for a period of time without changing.  This also
;;; makes it possible to store several explanations for the values of a single
;;; variable as it changes over time.  Explanations are show by displaying the
;;; subworkspace of the explanation (transient) object.  Explanations must
;;; eventually be deleted in the same was as a transient object is deleted to
;;; avoid using all of system memory.

;;; Explanation Format:

;;; A variable explanation consists of the current value, collection time, and
;;; expiration time at the time of the explanation creation; the rule, formula,
;;; procedure, etc. that concluded the variable value; and optionally (if the
;;; rule, etc. has a cache explanation option) the variables used by to
;;; make the conclusion.  These variables (used in the conclusion) can also be
;;; explainable if they contain cache explanation options.

;;; Cache Explanation Option:

;;; The options slot of all variables and parameters in G2 will contain a new
;;; option, which has the possible values "cache data for explanations"
;;; and "do not cache data for explanations".  Variables and parameters
;;; will by default not cache explanations.  This option must be set for the
;;; variable to retain data about which rule last concluded a value for it.
;;; The cache data option controls whether or not a variable or a rule will be
;;; able to produce a subtree for itself in an explanation.
;;;
;;; The options slot of rules will also include the new "cache data for
;;; explanations" option.  By default, all rules will not cache explanations.
;;; This option must be set for a rule display in an explanation to be able to
;;; explain which variables were used during its execution.
;;;
;;; Data-servers, initial values, buttons and procedures do not have the option
;;; of caching explanations when making conclusions.  But, explanations of
;;; conclusions by rules, specific formulas, and generic formulas can be
;;; cached.
;;;
;;; There are two new options in the Miscellany sub-menu from the Main Menu of
;;; G2.  The first is used to turn on the explanation caching option for all
;;; rules, formulas, (??)
;;; and variables, and the second is to turn it off.

;;; Create Explanation Action:

;;; The "create an explanation" action creates explanation objects.  Its
;;; grammar is similar to that of the Create action.  Its grammar is as follows:
;;;
;;;    Create an Explanation [<local name>] For <variable or parameter>
;;;
;;; This creates an explanation transient object for the value of the referenced
;;; variable or parameter, storing it into the local name, if one is specified.
;;; If the variable or parameter does not have the cache explanation
;;; option, the create explanation action does not return a value??

;;; Explanation Trees:

;;; Explanation tree displays will be made as follows.  Each variable in the
;;; tree will be shown with the value which it had when its explanation was
;;; cached, and below it will be the rule, formula, procedure, data-server, etc.
;;; which concluded its value.  The rules which were used to conclude the values
;;; of these variables will be shown with the bindings which were in effect for
;;; its generic references when the rules was executed.  If the rule caches data
;;; for explanations, then below the rule there will be variables which were
;;; evaluated during its execution.  Those variables which have the Cache Data
;;; for Explanations option will also show the value they had at the time
;;; of execution, and any further explanations for their values displayed below.
;;; Therefore, the leaves of an explanation hierarchy are those variables which
;;; did not have the Cache Data for Explanation option set or which did
;;; not receive their values from rule conclusions (??),
;;; and those rules which did not have their Cache Data option set.

;;; Cached Explanation Data:

;;; Note that all caches will actually reside on variable or parameter frames.
;;; The option on rules is required so that every rule does not have to
;;; constantly have get-current-value consing and reclaiming lists.  This is
;;; also necessary for the future development of rule compilers, in that the
;;; source parse for a rule may not be available for analysis to find the
;;; variables.  This approach is better than a search which generates the
;;; variable list from a generic binding context, in that the actual list is
;;; more accurate and more efficient at caching time.

;;; When caching explanations in put-current-value *current-computation-frame* and
;;; current-computation-instance must have the following bindings depending on
;;; the caller:
;;;
;;; Initial Value:
;;;   frame    = variable
;;;   instance = INITIAL-VALUE, a symbol
;;;
;;; Data Server (e.g., gfi, gsi, g2-to-g2, etc.)
;;;   frame    = variable
;;;   instance = data-server structure
;;;
;;; Button:
;;;   frame    = the button ????
;;;   instance = nil        ????
;;;
;;; Procedure:
;;;   frame    = procedure-invocation
;;;   instance = code-body-invocation
;;;
;;; Specific Formula and Generic Formula:
;;;   frame    = variable
;;;   instance = variable
;;;
;;; Rule:
;;;   frame    = rule
;;;   instance = rule-instance
;;;
;;; User-Menu-Choice:
;;;   frame    = ???
;;;   instance = ???


;;; Miscellany Menu:

;;; The Miscellany menu item to set Data Caching will iterate over all rules and
;;; variables, and actually mutate the option on their frames.  We could
;;; consider a default value approach if we further analyzed when the default
;;; value should override the value on the frame itself.




;;; The function `cache-explanation-variables' caches a variable or
;;; parameter frame and frame serial number.  (This information is later used
;;; when caching (and then creating) an explanation.)  These cached variables
;;; (or parameters) were used in finding the value of another variable (e.g., by
;;; backward chaining, a specific formula, etc.)
;;;
;;; Current-computation-instance must be let-bound before calling this function.
;;; If the current-computation-instance is a rule instance then variable
;;; explanation information is cached in a slot of the rule instance.  Otherwise,
;;; the special variable explanation-variables must be let-bound when this
;;; function is called and the variable explanation information is added to that
;;; list.  Also, the special variable cache-explanation-variables? should
;;; be tested for a non-nil value before calling this function.

(defun cache-explanation-variables (variable-or-parameter)
  (cond ((rule-instance-p current-computation-instance)
         ;; Add to the slot in the rule instance if necessary.
         (let ((cached-explanation-variables
                 (ri-explanation-variables
                   current-computation-instance)))
           (when (not (assq variable-or-parameter
                            cached-explanation-variables))
             (setf (ri-explanation-variables
                     current-computation-instance)
                   (eval-cons
                     ;; Consider changing to item-references -dkuznick, 5/19/06
                     (eval-cons variable-or-parameter
                                (copy-frame-serial-number (frame-serial-number variable-or-parameter)))
                     cached-explanation-variables)))))
        (t
         ;; add to the special variable list if necessary.
         (when (not (assq variable-or-parameter explanation-variables))
           (setq explanation-variables
                 (eval-cons
                   (eval-cons variable-or-parameter
                              (copy-frame-serial-number (frame-serial-number variable-or-parameter)))
                   explanation-variables))))))




(def-structure (cached-explanation (:reclaimer nil))) ;because of below

(defun-void reclaim-cached-explanation (cached-explanation)
  (reclaim-structure cached-explanation))


(def-structure (cached-explanation-from-data-server-or-initial-value
                 (:include cached-explanation)
                 (:constructor
                   make-cached-explanation-from-data-server-or-initial-value
                   (explanation-string)))
  ;; never nil
  (explanation-string nil :reclaimer reclaim-text-string))

(def-structure (cached-explanation-from-specific-formula
                 (:include cached-explanation)
                 (:constructor make-cached-explanation-from-specific-formula
                               (explanation-specific-formula-text
                                explanation-evaled-variables-from-specific-formula)))
  ;; never nil
  (explanation-specific-formula-text nil :reclaimer reclaim-text-string)
  (explanation-evaled-variables-from-specific-formula nil :reclaimer reclaim-evaled-variables-list))

;; Used for buttons (not action-buttons), procedures and generic-formulas.
;; Only generic-formulas have their own sub-structure.
(def-structure (cached-explanation-from-frame
                 (:include cached-explanation)
                 (:constructor make-cached-explanation-from-frame
                               (cached-explanation-item-reference)))
  ;; never nil
  (cached-explanation-item-reference
    nil :reclaimer reclaim-if-evaluation-item-reference))

(def-structure (cached-explanation-from-generic-formula
                 (:include cached-explanation-from-frame)
                 (:constructor make-cached-explanation-from-generic-formula
                               (cached-explanation-item-reference
                                explanation-evaled-variables-from-generic-formula)))
  ;; Note we are taking advantage of the (documented) layout of structures to
  ;; overlay the following slot.
  (explanation-evaled-variables-from-generic-formula nil :reclaimer reclaim-evaled-variables-list))

(def-structure (cached-explanation-from-rule
                 (:include cached-explanation-from-frame)
                 (:constructor make-cached-explanation-from-rule
                               (cached-explanation-item-reference
                                explanation-evaled-variables-from-rule
                                explanation-rule-context
                                explanation-rule-context-guard)))
  ;; Ditto the overlay comment above.
  (explanation-evaled-variables-from-rule nil :reclaimer reclaim-evaled-variables-list)
  (explanation-rule-context nil :reclaimer reclaim-if-environment-vector)
  (explanation-rule-context-guard nil :reclaimer reclaim-frame-serial-number))

(defun-void reclaim-if-environment-vector (v?)
  (when v?
    (reclaim-environment-vector v?)))


(defun-simple get-valid-frame-from-explanation (cached-explanation-from-frame)
  (get-item-if-item-reference
    (cached-explanation-item-reference cached-explanation-from-frame)))


(def-generic-structure-method get-cached-explanation-evaled-variables-if-any
    (struct))


(def-structure-method get-cached-explanation-evaled-variables-if-any (cached-explanation)
  (declare (ignore cached-explanation))
  nil)

(def-structure-method get-cached-explanation-evaled-variables-if-any (cached-explanation-from-specific-formula)
  (explanation-evaled-variables-from-specific-formula cached-explanation-from-specific-formula))

(def-structure-method get-cached-explanation-evaled-variables-if-any (cached-explanation-from-generic-formula)
  (explanation-evaled-variables-from-generic-formula cached-explanation-from-generic-formula))

(def-structure-method get-cached-explanation-evaled-variables-if-any (cached-explanation-from-rule)
  (explanation-evaled-variables-from-rule cached-explanation-from-rule))


;;; `make-cached-explanation-node' returns an explanation-table for the given
;;; cached-explanation.  It can only be given valid explanations.

(def-generic-structure-method make-cached-explanation-node (struct))

;;; `make-cached-explanation-rule-node' takes as an argument an explanation from
;;; a rule, action-button, or user-menu-choice and returns a table that is used
;;; in an explanation to represent that node.

(def-structure-method make-cached-explanation-node (cached-explanation-from-rule)
  (let ((rule (get-valid-frame-from-explanation cached-explanation-from-rule)))
    (make-explanation-table
      rule
      (make-slot-value-lists-of-context
        rule
        (explanation-rule-context cached-explanation-from-rule)

        ;; The old code wasn't copying, so this won't either.  Note the
        ;; context isn't being copied above so this is probably
        ;; ok. -dkuznick, 5/19/06
        (explanation-rule-context-guard cached-explanation-from-rule)))))


;;; `make-cached-explanation-node' for
;;; cached-explanation-from-data-server-or-initial-value takes as an argument
;;; an explanation from an initial-value, data server, etc.  It returns a table
;;; that is used in an explanation to represent that node.

(def-structure-method make-cached-explanation-node (cached-explanation-from-data-server-or-initial-value)
  (make-explanation-table
    nil
    (slot-value-cons
      (copy-text-string
        (explanation-string
          cached-explanation-from-data-server-or-initial-value))
      nil)))


;;; `make-cached-explanation-node' for cached-explantion-from-specific-formula
;;; takes as argument an explanation from a specific formula and returns a
;;; table that is used in an explanation to represent that formula.

(def-structure-method make-cached-explanation-node (cached-explanation-from-specific-formula)
  (make-explanation-table
    nil
    (slot-value-cons
      (copy-text-string
        (explanation-specific-formula-text
          cached-explanation-from-specific-formula))
      nil)))


;;; `make-cached-explanation-node' for a cached-explanation-from-frame takes as
;;; an argument an explanation from a frame (currently, button or procedure.
;;; Generic-formulas use their own method) and returns a table that is used in
;;; an explanation to represent that node.

(def-structure-method make-cached-explanation-node (cached-explanation-from-frame)
  (make-explanation-table
    (get-valid-frame-from-explanation cached-explanation-from-frame)))



;;; `cached-explanation-from-frame' returns its argument if it is valid, else
;;; it returns nil.  The only way an explanation can be invalid, is if the
;;; frame it is for has been deleted/recycled.

(def-generic-structure-method return-cached-explanation-if-valid (struct))

(def-structure-method return-cached-explanation-if-valid (cached-explanation)
  cached-explanation)

(def-structure-method return-cached-explanation-if-valid (cached-explanation-from-frame)
  (and (get-valid-frame-from-explanation cached-explanation-from-frame)
       cached-explanation-from-frame))



(def-generic-structure-method export-cached-explanation-node (struct))


(def-structure-method export-cached-explanation-node
    (cached-explanation-from-data-server-or-initial-value)
  ;; Prior to the 8.3r0 release, we might treat this one very differently as
  ;; it's currently a little ugly.  -dkuznick, 7/20/06
  (allocate-evaluation-structure-inline
    'node-type (make-evaluation-symbol 'data-server-or-initial-value)
    'item-or-value  (make-evaluation-text
                      (explanation-string
                        cached-explanation-from-data-server-or-initial-value))
    'node-specific-data (allocate-evaluation-sequence nil)))


(def-structure-method export-cached-explanation-node
    (cached-explanation-from-specific-formula)
  (allocate-evaluation-structure-inline
    'node-type (make-evaluation-symbol 'specific-formula)
    'item-or-value (make-evaluation-text
                     (explanation-specific-formula-text
                       cached-explanation-from-specific-formula))
    'node-specific-data (allocate-evaluation-sequence nil)))


(def-structure-method export-cached-explanation-node (cached-explanation-from-frame)
  (allocate-evaluation-structure-inline
    'node-type (make-evaluation-symbol 'item)
    'item-or-value (copy-evaluation-item-reference
                     (cached-explanation-item-reference
                       cached-explanation-from-frame))
    'node-specific-data (allocate-evaluation-sequence nil)))

;; We don't need a seperate override method for
;; cached-explanation-from-generic-formula because it is just like frame from
;; the user's point of view {except it can have non-empty children, but that's
;; dealt with elsewhere}

(def-structure-method export-cached-explanation-node (cached-explanation-from-rule)
  (allocate-evaluation-structure-inline
    'node-type (make-evaluation-symbol 'rule)
    'item-or-value (copy-evaluation-item-reference
                     (cached-explanation-item-reference
                       cached-explanation-from-rule))
    'node-specific-data
    (allocate-evaluation-sequence
      (loop with context-lists = (make-slot-value-lists-of-context
                                   ;; Need NULL check?
                                   (evaluation-item-reference-referenced-item
                                     (cached-explanation-item-reference
                                       cached-explanation-from-rule))
                                   (explanation-rule-context
                                     cached-explanation-from-rule)
                                   (explanation-rule-context-guard
                                     cached-explanation-from-rule)
                                   t)
            for local-name-and-bindings in context-lists
            collect (prog1
                        (allocate-evaluation-structure-inline
                          'local-name
                          (first local-name-and-bindings)
                          'item-or-value
                          (second local-name-and-bindings))
                      (reclaim-slot-value-list local-name-and-bindings))
              using eval-cons
            finally (reclaim-slot-value-list context-lists)))))



(defun-simple export-cached-explanation-node-for-vorp (vorp)
  (allocate-evaluation-structure-inline
    'node-type (make-evaluation-symbol 'variable-or-parameter)
    'item-or-value vorp
    'node-specific-data
    (allocate-evaluation-sequence
      (let ((structure?
              (get-evaluation-value-of-variable-or-parameter vorp nil)))
        (when structure?
          (eval-list structure?))))))


(defun-simple create-exported-cached-explanation-node
    (item-or-cached-explanation)
  ;; Can we get a deleted frame here?
  (if (framep item-or-cached-explanation)
      (export-cached-explanation-node-for-vorp item-or-cached-explanation)
      (export-cached-explanation-node item-or-cached-explanation)))


;;; The function `cache-explanation' caches a variable or parameter
;;; explanation onto the variable or parameter.  This information is later used
;;; when creating an explanation for the current (or expired) value of a
;;; variable.  The cached explanation contains information that indicates how
;;; the current value was arrived at and its format varies depending on the
;;; source of the value (rule, formula, procedure, etc.).
;;;
;;; The flag-predicate, (cache-data-for-explanation-p variable-or-parameter),
;;; should be tested for a non-nil value before calling this function.
;;;
;;; *current-computation-frame* and current-computation-instance must be let-bound
;;; before calling this function depending on the source of the value.
;;;   Initial Value:
;;;   frame    = variable
;;;   instance = INITIAL-VALUE, a symbol
;;;
;;;   Data Server (e.g., gfi, gsi, g2-to-g2, etc.)
;;;   frame    = variable
;;;   instance = data-server structure
;;;
;;;   Button:
;;;   frame    = the button ????
;;;   instance = nil        ????
;;;
;;;   Procedure:
;;;   frame    = procedure-invocation
;;;   instance = code-body-invocation
;;;
;;;   Specific Formula and Generic Formula:
;;;   frame    = variable
;;;   instance = variable
;;;
;;;   Rule:
;;;   frame    = rule
;;;   instance = rule-instance
;;;
;;;   User-Menu-Choice:
;;;   frame    = ???
;;;   instance = ???



(defun reclaim-evaled-variables-list (variables)
  (loop for var in variables
        do
    (reclaim-frame-serial-number (cdr var))
    (reclaim-eval-cons var))
  (reclaim-eval-list variables))


;;; Here are the main environments this gets called in:
;;; 1) inital-values
;;;          current-compuation-frame -> variable-or-parameter
;;;          current-computation-instance -> 'initial-value
;;;
;;; 2) "normal" conclude
;;;          current-compuation-frame -> definitional item of the thing doing
;;;                                      the conclude (procedure, rule)
;;;          current-computation-instance -> "invocation-ish" of the thing
;;;                                      doing the conclude
;;;                                      (procedure-invocation, rule-instance,
;;;                                      etc).
;;;
;;; 3) specific formula - only in variable case
;;;          *current-computation-frame* -> variable-or-parameter
;;;          current-computation-instance -> formula-invocation
;;;
;;; 4) generic formula - only in variable case
;;;          *current-computation-frame* -> generic-formula
;;;          current-computation-instance -> formula-invocation
;;;
;;; 5) data-service - only in variable case
;;;          *current-computation-frame* -> variable-or-parameter
;;;          current-computation-instance -> data-server
;;;
;;; 5) conclude via the value-structure virtual-attribute
;;;          current-compuation-frame -> variable-or-parameter
;;;          current-computation-instance -> invocation (as case 2).

(defun cache-explanation (variable-or-parameter)
  (let ((cached-explanation
          (cached-explanation variable-or-parameter)))
    (when cached-explanation
      (reclaim-cached-explanation cached-explanation)
      (setf (cached-explanation variable-or-parameter) nil)))
  (cond
    ;; This condition only seems to be true for initial-values OR VARIABLES
    ;; (not parameters) -dkuznick, 6/24/98
    ;; NOPE, I missed a case.  It's true for parameters and variables when a
    ;; value is being concluded through the value-structure virtual attribute,
    ;; but not through a direct conclude (then the definitional thing doing the
    ;; conclude is the *current-computation-frame*).  -dkuznick, 3/18/05
    ((eq *current-computation-frame* variable-or-parameter)
     (cond ((eq current-computation-instance 'initial-value)
            (setf (cached-explanation variable-or-parameter)
                  (make-cached-explanation-from-data-server-or-initial-value
                    (copy-constant-wide-string #w"Initial Value"))))

           ((data-server-p current-computation-instance)
            ;; gfi, gsi, g2ds, g2-meters, simulator.
            (setf (cached-explanation variable-or-parameter)
                  (make-cached-explanation-from-data-server-or-initial-value
                    (copy-constant-wide-string #w"External Data Server"))))

           (;;(eq current-computation-instance variable-or-parameter)
            (formula-invocation-p current-computation-instance)
            ;; specific formula.
            (setf (cached-explanation variable-or-parameter)
                  (make-cached-explanation-from-specific-formula
                    (convert-text-to-text-string
                      (formula? variable-or-parameter))
                    (copy-explanation-variables
                      explanation-variables))))
           ;; Now we are at the case for a conclude through the value-structure
           ;; virtual-attribute.  -dkuznick, 3/18/05
           ((rule-instance-p current-computation-instance)
            (setf (cached-explanation variable-or-parameter)
                  (make-cached-explanation-from-rule-and-rule-instance
                    (ri-rule current-computation-instance)
                    current-computation-instance)))

           ((procedure-invocation-p current-computation-instance)
            (setf (cached-explanation variable-or-parameter)
                  (make-cached-explanation-from-procedure-frame
                    (procedure-of-invocation current-computation-instance))))
           (t
            #+development
            (warning-message
                1 "Unknown explanation var/param type in cache-explanation!")
            nil)))
    ((generic-formula-p *current-computation-frame*)
     (setf (cached-explanation variable-or-parameter)
           (make-cached-explanation-from-generic-formula
             (get-reference-to-item *current-computation-frame*)        ;maybe current-computation-instance?
             (copy-explanation-variables explanation-variables))))

     ((rule-p *current-computation-frame*)
     ;; Rules, action buttons, and user-menu-choices have
     ;; *current-computation-frame* bound to a rule.
      (setf (cached-explanation variable-or-parameter)
            (if (rule-is-embedded-p *current-computation-frame*)
                ;; Action-buttons and user-menu-choices
                (make-cached-explanation-from-frame
                  (get-reference-to-item
                    (parent-frame *current-computation-frame*)))
                (make-cached-explanation-from-rule-and-rule-instance
                  *current-computation-frame* current-computation-instance))))

    ((procedure-p *current-computation-frame*)
     (setf (cached-explanation variable-or-parameter)
           (make-cached-explanation-from-procedure-frame
             *current-computation-frame*)))

    ((frame-of-class-p *current-computation-frame* 'button)
     ;; radio button, check-box, type-in, slider
     ;; (Action button has current-computation frame of class rule.)
     (setf (cached-explanation variable-or-parameter)
           (make-cached-explanation-from-frame
             (get-reference-to-item *current-computation-frame*))))

    (t
     #+development
     (warning-message
         1 "Unknown explanation type in cache-explanation!")
     nil))

  #+development
  (cached-explanation variable-or-parameter))



;;; `make-cached-explanation-from-rule-and-current-computation-instance' is a
;;; helper function for cache-explanation.  If it is passed a rule,
;;; current-computation-instance must be bound to the correct rule-instance.
(defun make-cached-explanation-from-rule-and-rule-instance
    (rule rule-instance)
  (make-cached-explanation-from-rule
    (get-reference-to-item rule)
    (copy-variables-list
      (ri-explanation-variables rule-instance))
    ;;  Embedded-rules can have NIL for their
    ;; invocation-local-var-vector.  Have to handle here and in
    ;; reclaimage.  -dkuznick, 6/16/98
    (let ((locals (invocation-local-var-vector rule-instance)))
      (when locals
        (copy-environment-vector locals)))
    (copy-frame-serial-number (ri-frame-serial-number rule-instance))))

;;; `make-cached-explanation-from-procedure-frame' is a helper function for
;;; cache-explanation.
(defun make-cached-explanation-from-procedure-frame (procedure)
  (make-cached-explanation-from-frame
    (get-reference-to-item procedure)))


;;; Instances of the class `explanation' are used to create explanation of
;;; variable or parameter values.  The explanation tree is added to the
;;; subworkspace of the explanation.

(def-class (explanation (item entity))
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((lines (47 18) (47 26))
       (outline (44 26) (44 31) (50 31) (50 26))
       (lines (39 39) (55 39))
       (lines (47 31) (47 39))
       (lines (39 39) (39 47))
       (lines (55 39) (55 47))
       (outline (52 47) (52 52) (58 52) (58 47))
       (outline (36 47) (36 52) (42 52) (42 47))
       (outline (9 26) (9 31) (15 31) (15 26))
       (lines (12 18) (12 26))
       (outline (1 47) (1 52) (7 52) (7 47))
       (lines (4 39) (20 39))
       (lines (12 31) (12 39))
       (lines (4 39) (4 47))
       (lines (20 39) (20 47))
       (outline (17 47) (17 52) (23 52) (23 47))
       (lines (30 10) (30 18))
       (lines (12 18) (47 18))
       (outline (27 5) (27 10) (33 10) (33 5))
       (outline (0 0) (0 60) (60 60) (60 0))))))


(defun-simple create-explanation-graph (variable-or-parameter)
  (graph-frame-hierarchy
    variable-or-parameter 'get-explanation-children nil
    'make-explanation-node-representation
    ;;hash-function
    'hash-explanation-node
    nil nil nil nil
    ;;class-of-workspace
    'kb-workspace
    nil nil nil))

;;; The function `create-explanation' creates a transient object of class explanation.
;;; If there is a cached explanation, it is formatted and put on a newly created
;;; subworkspace of the explanation.  (It is not displayed.) If there is no
;;; cached explanation and regardless of whether the object is explainable, a
;;; representation of the object is put on the workspace with no further
;;; explanation (subtree).

;;; The explanation is a tree with a start node of the explainable variable or
;;; parameter.  Below this is the rule, formula, etc. that concluded this value.
;;; If this rule, formula, etc. is explainable then the variables or parameters
;;; used to make this conclusion are displayed below this node.  The tree
;;; continues in the same way if the children-nodes are explainable.
(defun create-explanation (variable-or-parameter)
  (let* ((explanation-object
           (make-transient-item 'explanation))
         (graph (create-explanation-graph variable-or-parameter))
         (graph-workspace  (graph-display-workspace graph)))
    (reclaim-graph-display graph)
    ;; Make the graph-workspace the subworkspace of the explanation.
    (add-subworkspace graph-workspace explanation-object)
    ;; Return the explanation transient object.
    explanation-object))


;;; The function `get-explanation-children' is used in
;;; create-an-explanation to graph the explanation.  This function returns
;;; the children of two types of graph-nodes.  If the node represents a variable
;;; or parameter, the child returned is the cached explanation.  If the node is
;;; a cached explanation, then the variables or parameters (if any) cached as
;;; part of the explanation are returned.  If no variables were cached, NIL is
;;; returned.  By checking the frame numbers of all children, deleted children
;;; (frames) are not returned.

(defun get-explanation-children
       (variable-parameter-or-cached-explanation extra-arg)
  (declare (ignore extra-arg))

  (if (and (framep variable-parameter-or-cached-explanation)
           (variable-or-parameter-p variable-parameter-or-cached-explanation))
      (let ((cached-explanation (get-valid-cached-explanation
                                  variable-parameter-or-cached-explanation)))
        (if cached-explanation
            (gensym-list cached-explanation)
            nil))
      (make-explanation-variable-list
        ;; Expected to return nil for button (not action-button), procedure,
        ;; data server, or initial value.
        (get-cached-explanation-evaled-variables-if-any
          variable-parameter-or-cached-explanation))))



;;; The function `get-valid-cached-explanation' takes a variable or parameter
;;; as an argument and returns a "valid" cached-explanation for it.  An
;;; explanation is valid if the frame associated with the explanation (e.g.,
;;; rule, generic-formula, etc.) has not been deleted.  If an explanation has
;;; not been cached or if the explanation is not valid, NIL is returned.
;;; Otherwise, the cached explanation is returned.

(defun get-valid-cached-explanation (variable-or-parameter)
  (let ((explanation? (cached-explanation variable-or-parameter)))
    (and explanation?
         (return-cached-explanation-if-valid explanation?))))




;;; The function `make-explanation-variable-list' takes as an argument an
;;; alist of variables or parameters and their associated frame numbers.  The
;;; current frame numbers are compared with the frame number and the list.
;;; Those frames are collected into a list using gensym conses.  (Gensym conses
;;; are used in the frame-graphing facility.)

(defun make-explanation-variable-list (variable-explanation-alist)
  ;; This will change if we switch to item-references -dkuznick, 5/19/06
  (loop for (variable-or-parameter . frame-serial-number)
            in variable-explanation-alist
        when (frame-has-not-been-reprocessed-p
               variable-or-parameter
               frame-serial-number)
          collect variable-or-parameter using gensym-cons))





;;; The function `make-explanation-variable-node' takes as an argument a
;;; variable or parameter and returns a table that is used in an
;;; explanation to represent that variable or parameter.

;; This function should be called from a temporary gensym-float context because
;; the float value of time-of-most-recent-value is referenced.  - cpm, 6/8/94

(defun make-explanation-variable-node (variable-or-parameter)
  (let* ((expiration
           (if (parameter-p variable-or-parameter)
               'never
               (expiration-time-of-current-value
                 variable-or-parameter)))
         (expiration-is-number?
           (typep expiration 'fixnum)))
      (make-explanation-table
        variable-or-parameter
        (if (and expiration-is-number?
                 (=f expiration *some-time-ago*))
            (slot-value-list
              (slot-value-list (copy-constant-wide-string #w"Value")
                               (copy-constant-wide-string #w"no value"))
              (slot-value-list (copy-constant-wide-string #w"Timestamp")
                               (copy-constant-wide-string #w"none"))
              (slot-value-list (copy-constant-wide-string #w"Expiration")
                               (copy-constant-wide-string #w"none")))
            (slot-value-list
              (slot-value-list
                (copy-constant-wide-string #w"Value")
                (twith-output-to-text-string
                  (print-constant (extract-cached-number-or-value
                                    (current-value-of-variable-or-parameter
                                      variable-or-parameter))
                                  (data-type-of-variable-or-parameter
                                    variable-or-parameter))))
              (slot-value-list
                (copy-constant-wide-string #w"Timestamp")
                (twith-output-to-text-string
                  (print-constant (- (extract-number
                                       (time-of-most-recent-value
                                       variable-or-parameter))
                                     (managed-float-value
                                       (clock-get g2-time-at-start)))
                                  'time-stamp)))
              (slot-value-list
                (copy-constant-wide-string #w"Expiration")
                (if expiration-is-number?
                    (twith-output-to-text-string
                      (print-constant
                        (- expiration (clock-get gensym-time-at-start))
                        'time-stamp))
                    (copy-constant-wide-string #w"valid indefinitely"))))))))



(defun make-slot-value-lists-of-context
    (rule context cached-frame-serial-number?
          &optional use-actual-value-p)
  (let ((environment-description
          (byte-code-body-environment-description
            (rule-byte-code-body rule))))
    (loop with var-spot = (proc-list 'var-spot 0)
          for index from 0 below (rule-context-length rule)
          repeat (length environment-description)
          for value = (svref context index)
          for var-name = (var-name-from-index environment-description index)
          for var-description = (var-general-description-from-index environment-description index)
          do
      (setf (second var-spot) index)
      collect
          (slot-value-list
            ;; Consider using a symbol for this element instead of text if
            ;; use-actual-value-p is non-NIL -dkuznick, 7/14/06
            (twith-output-to-text-string
              (print-var-spot-for-stack-using-name-and-description
                var-spot var-name var-description))
            (if (frame-or-deleted-frame-p value)
                (if (and cached-frame-serial-number?
                         (frame-has-been-reprocessed-p
                           value
                           cached-frame-serial-number?))
                    (if use-actual-value-p
                        nil
                        (copy-text-string #w"<deleted item>"))
                    (if use-actual-value-p
                        value
                        (tformat-text-string "~NF" value)))
                (if use-actual-value-p
                    ;; Not considering debug/internal data.  Can we ever get it
                    ;; here? -dkuznick, 7/14/06
                    (copy-and-box-element-value-if-necessary value)
                    (twith-output-to-text-string
                      (write-stored-value value)))))
        into result using slot-value-cons
          finally (reclaim-proc-list var-spot)
                  (return result))))



;;; The function `make-explanation-node-representation' given a node of
;;; the explanation graph returns a frame that represents the node in the graph
;;; display.

(defun make-explanation-node-representation
       (variable-parameter-or-cached-explanation)
  (if (and (framep variable-parameter-or-cached-explanation)
           (variable-or-parameter-p variable-parameter-or-cached-explanation))

      (make-explanation-variable-node
        variable-parameter-or-cached-explanation)

      (make-cached-explanation-node variable-parameter-or-cached-explanation)))



;;; The function 'hash-explanation-node' given a node of the explanation
;;; graph returns a hash number associated with the node.  This is useful when
;;; comparing nodes.

(defun hash-explanation-node (variable-parameter-or-cached-explanation)
  (if (and (framep variable-parameter-or-cached-explanation)
           (variable-or-parameter-p variable-parameter-or-cached-explanation))
      (frame-hash variable-parameter-or-cached-explanation)
      ;; This used to do frame-serial-number-hash on the stored
      ;; frame-serial-number for generic-formula, rule, button and procedure,
      ;; and return 0 otherwise.  Is the below ok instead?  -dkuznick, 5/22/06
      (sxhash variable-parameter-or-cached-explanation)))



(defun-for-system-procedure g2-get-explanation-hierarchy (variable-or-parameter)
  (declare (keeps-g2-local-variables-valid t))
  (let ((graph (create-explanation-graph variable-or-parameter)))
    (prog1 (export-graph-node
             (graph-display-root graph)
             #'create-exported-cached-explanation-node
             t)
      ;; We have to delete the workspace created for the graph-display as this
      ;; is a side-effect of building the graph.  In the interactive case, we
      ;; keep it around so the user can get to the explanation-table {it's made
      ;; a subworkspace of the explanation object the user created.  Since we
      ;; are doing all that behind the users back, we need to clean up.}
      (delete-frame (graph-display-workspace graph))
      (reclaim-graph-display graph))))





;;;; Explanation - Turn Explanation Off/On




;;; The function `turn-off-explanation-caching-for-all' turns off
;;; explanation caching for all rules, variables, and parameters.  The option
;;; for caching explanations is turned off; cached explanation are reclaimed and
;;; cleared; and any explanation variable lists are reclaimed and reset.  This
;;; function is called from the Miscellany sub-menu of the Main menu.

(defun turn-off-explanation-caching-for-all ()
  (loop for rule being each class-instance of 'rule
        do
    (when (cache-data-for-explanation-p rule)
      (clear-cache-data-for-explanation rule)
      (update-representations-of-slot-value rule 'frame-flags)
      (loop for rule-instance being each hash-value of
                (hash-table-of-rule-instances rule)
            do
        (let ((cached-variables
                (ri-explanation-variables rule-instance)))
          (when cached-variables
            (reclaim-evaluation-variables-list cached-variables)
            (setf (ri-explanation-variables rule-instance) nil))))))

  (loop for variable-or-parameter being each
            class-instance of 'variable-or-parameter
        do
    (when (cache-data-for-explanation-p variable-or-parameter)
      (clear-cache-data-for-explanation variable-or-parameter)
      (update-representations-of-slot-value
        variable-or-parameter 'frame-flags)
      ;; Clear cached explanation.
        (let ((cached-explanation
                (cached-explanation variable-or-parameter)))
          (when cached-explanation
            (reclaim-cached-explanation cached-explanation)
            (setf (cached-explanation variable-or-parameter) nil))))))




;;; The function `turn-on-explanation-caching-for-all' turns on
;;; explanation caching option for all rules, variables, and parameters.

(defun turn-on-explanation-caching-for-all ()
  (loop for rule being each class-instance of 'rule
        do
    (unless (cache-data-for-explanation-p rule)
      (set-cache-data-for-explanation rule)
      (update-representations-of-slot-value rule 'frame-flags)))

  (loop for variable-or-parameter being each
            class-instance of 'variable-or-parameter
        do
    (unless (cache-data-for-explanation-p variable-or-parameter)
      (set-cache-data-for-explanation variable-or-parameter)
      (update-representations-of-slot-value
        variable-or-parameter 'frame-flags))))






;;;; Frame Displayer




;;; The frame display is a method of displaying frames or frame-representations
;;; on a frame-display-workspace.  There are functions to add and remove frames,
;;; and create, show, update, delelete-and-reclaim the frame-display.  Frames
;;; are displayed from top to bottom based on information in the frame-display.
;;; As frames are removed, the frame-display is updated based on a count of the
;;; frames removed (before an update has occurred) and a count of the current
;;; frames displayed.  If the workspace of the frame-display is deleted, the
;;; frame-display is deleted and reclaimed.




;;; NUPEC conses

;;(defconser nupec)
(defconser frame-display)        ; -dkuznick, 7/10/98







;;; The structure `frame-display' is used to contain state information for
;;; a display of frames.  This information is used to update the display.  The
;;; make-frame-display constructor should be called when creating a new
;;; display.  This structure is needed in functions that create and update the
;;; display.

(def-structure (frame-display
                 (:include dynamic-workspace-associated-structure))
  (frame-display-hash-key nil)
  (frame-display-workspace nil)
  (frame-display-alist nil :reclaimer reclaim-frame-display-alist)
  (frame-display-initial-y 0)
  (frame-display-current-y 0)
  (frame-display-deletion-count-before-redisplay 0))

(defun reclaim-frame-display-alist (alist)
  (loop for item in alist do
    (reclaim-frame-serial-number (cddr item))
    (reclaim-frame-display-cons (cdr item))
    (reclaim-frame-display-cons item))
  (reclaim-frame-display-list alist))

;;; The function `create-frame-display' creates an explanation frame display,
;;; initializes frame-display state information, sets the workspace slot to
;;; point to the dynamic-frame-display, and returns the frame-display.

(defun create-frame-display ()
  (let ((frame-display (make-frame-display))
        (workspace
          (make-workspace
            'dynamic-temporary-workspace nil nil
            #.frame-display-workspace-margin
            nil nil)))
    (setf (frame-display-workspace frame-display) workspace)
    frame-display))




;;; The function `show-frame-display' takes a frame-display and shows its
;;; workspace on the screen.

(defun show-frame-display (frame-display)
  (put-workspace-on-pane (frame-display-workspace frame-display)
                         current-workstation-detail-pane
                         'left 'top t))




;; The function `nupec-show-frames-on-frame-display' displays the given
;; frames (in order) on a new temporary workspace.  The nupec-frame-display
;; argument must be a newly created structure.  Display state information is
;; saved within this structure for later display updates.  The frame-list
;; argument becomes property of this module, and will be reclaimed by the
;; module when needed.

;; based on code from Queries module (i.e., show-on-a-workspace).

;(defun nupec-show-frames-on-frame-display
;       (short-representation-frame-list nupec-frame-display)
;  (loop with workspace
;          = (make-workspace
;              'temporary-workspace nil nil
;              #.nupec-frame-display-workspace-margin
;              nil nil)
;        with current-x = 0
;        with current-y = 0
;        for short-representation in short-representation-frame-list
;        do (add-to-workspace
;             short-representation workspace current-x current-y)
;           (incfw current-y
;                  (+w (height-of-block short-representation)
;                      #.nupec-frame-display-vertical-spacing))
;        finally
;          (put-workspace-on-pane
;            workspace current-workstation-detail-pane
;            'left 'top t)
;          (setf (frame-display-workspace nupec-frame-display) workspace)
;          (setf (frame-display-current-y nupec-frame-display) current-y)
;          (setf (frame-display-alist nupec-frame-display)  ; rewrite using the alist!
;                short-representation-frame-list)))



;; The function `nupec-add-frames-on-frame-display' is used to add frames
;; to the bottom of an existing display.  (The display is expanded as
;; necessary.)  The state of nupec display information is updated.
;; The frame-list argument becomes property of this module, and will be
;; reclaimed by the module when needed.

;(defun nupec-add-frames-on-frame-display
;       (short-representation-frame-list nupec-frame-display)
;  (loop with workspace = (frame-display-workspace nupec-frame-display)
;        with current-x = 0
;        with current-y = (frame-display-current-y nupec-frame-display)
;        for short-representation in short-representation-frame-list
;;;        for block in short-representation-frame-list
;;;        for short-representation = (make-short-representation block)
;        do (add-to-workspace
;             short-representation workspace current-x current-y t t)
;           (incfw current-y
;                  (+w (height-of-block short-representation)
;                      #.nupec-frame-display-vertical-spacing))
;        finally
;          (setf (frame-display-current-y nupec-frame-display) current-y)
;          (setf (frame-display-alist nupec-frame-display)  ; rewrite using the alist!
;          alist!
;                (if (frame-display-list nupec-frame-display)
;                    (nconc (frame-display-list nupec-frame-display)
;                            short-representation-frame-list)
;                    short-representation-frame-list))))



;;; The function `add-thing-to-frame-display' is used to add a
;;; frame-representation to the bottom of an existing frame display.  (The
;;; display is expanded as necessary.)  The state of dynamic display information
;;; is updated.  The frame-representation argument is the frame that is actually
;;; displayed.  The thing argument is needed when updating the frame-display at
;;; another time.  If the frame-representation is successfully added, the frame
;;; is returned.  If the frame-representation is already displayed, NIL is
;;; returned.  The check-for-duplicate-add? argument determines if a test is
;;; done to see if the frame is already displayed.

(defun add-thing-to-frame-display
       (thing frame-representation frame-display check-for-duplicate-add?)
  (let ((workspace (frame-display-workspace frame-display))
        (frame-display-alist (frame-display-alist frame-display))
        (current-y (frame-display-current-y frame-display))
        (current-x 0))

    (cond ((and check-for-duplicate-add?
                (assq thing frame-display-alist))
           ;; Return NIL, thing is already displayed.
           nil)
          (t
           (add-to-workspace
             frame-representation workspace current-x current-y t t)
           (incfw current-y
                  (+w (height-of-block frame-representation)
                      #.frame-display-vertical-spacing))

           (setf (frame-display-current-y frame-display) current-y)
           (setf (frame-display-alist frame-display)
                 (if (frame-display-alist frame-display)
                     (nconc (frame-display-alist frame-display)
                            (frame-display-list
                              (frame-display-cons
                                thing
                                (frame-display-cons
                                  frame-representation
                                  (copy-frame-serial-number (current-frame-serial-number))))))
                     (frame-display-list
                       (frame-display-cons
                         thing
                         (frame-display-cons frame-representation
                                             (copy-frame-serial-number (current-frame-serial-number)))))))
           ;; Return thing.
           thing))))




;;; The function `remove-thing-from-frame-display' erases and removes the
;;; frame-representation for thing (e.g., rule-instance or frame) from the
;;; frame-display-workspace.  The workspace display is updated (frames
;;; repositioned and workspace redrawn) after certain number of removals.  If
;;; the removal is successful, T is returned; otherwise, NIL is returned.

(defun remove-thing-from-frame-display (frame frame-display)
  (loop for previous-cons? = nil then cons?
        for cons? = (frame-display-alist frame-display) then (cdr cons?)
        while (and cons?
                   (not (eq frame (car (first cons?)))))
        finally (when cons?
                  (let* ((entry (car cons?))
                         (frame-representation (cadr entry))
                         (frame-representation-fsn (cddr entry))
                         (frame-representation?
                           (unless (frame-has-been-reprocessed-p
                                     frame-representation frame-representation-fsn)
                             frame-representation))
                         (frame-representation-height?
                           (and frame-representation?
                                (height-of-block frame-representation?)))
                         (deleted-last-cons? (null (cdr cons?)))
                         (deletion-count
                           (frame-display-deletion-count-before-redisplay frame-display)))
                    (if previous-cons?
                        (setf (cdr previous-cons?) (cdr cons?))
                        (setf (frame-display-alist frame-display) (cdr cons?)))
                    (reclaim-frame-serial-number frame-representation-fsn)
                    (reclaim-frame-display-cons (cdr entry))
                    (reclaim-frame-display-cons entry)
                    (reclaim-frame-display-cons cons?)
                    (when frame-representation?
                      (delete-frame frame-representation?))
                    (incff deletion-count)
                    ;; Test for workspace update.
                    (cond
                      ((<=f (length (frame-display-alist frame-display)) 2)
                       (update-frame-display frame-display nil t)
                       (setf (frame-display-deletion-count-before-redisplay
                               frame-display)
                             0))
                      ((>f deletion-count
                           #.frame-display-reformat-after-count-deleted)
                       (update-frame-display frame-display t t)
                       (setf (frame-display-deletion-count-before-redisplay
                               frame-display)
                             0))
                      ((and deleted-last-cons? frame-representation-height?)
                       (setf (frame-display-current-y frame-display)
                             (-w (frame-display-current-y frame-display)
                                 frame-representation-height?
                                 #.frame-display-vertical-spacing)))
                      (t
                       (setf (frame-display-deletion-count-before-redisplay
                               frame-display)
                             deletion-count)))))
                (return (not (null cons?)))))




;;; The function `update-frame-display' updates a frame-display.  (The
;;; workspace should already be displayed on a pane.) The positions of the
;;; frames are recomputed and optionally redisplayed.  The workspace is
;;; optionally shrink-wrapped.  (This function is used when some frames have
;;; been deleted and the workspace contents should be redisplayed.  It is called
;;; by remove-thing-from-dynamic-frame-display.)  The frame-display
;;; alist is first validated by checking for reprocessed frame-representations.
;;; If any have been reprocessed, the corresponding entry in the alist is
;;; removed.

(defun update-frame-display
       (frame-display redisplay? shrink-wrap?)
  (loop with workspace = (frame-display-workspace frame-display)
        with current-x = 0
        with current-y = (frame-display-initial-y frame-display)
        for (nil frame-representation)
            in (validate-and-update-frame-display-alist frame-display)
        do
    (when (and frame-representation redisplay?
               (or (not (=w current-x
                            (left-edge-of-block frame-representation)))
                   (not (=w current-y
                            (top-edge-of-block frame-representation)))))
      ;; erase the frame-representation.

      (update-images-of-block frame-representation t t)
      (shift-block
        frame-representation
        (-w current-x (left-edge-of-block frame-representation))
        (-w current-y (top-edge-of-block frame-representation)))
      (update-images-of-block frame-representation nil t))
    (setf current-y (+w (height-of-block frame-representation)
                        #.frame-display-vertical-spacing
                        current-y))
        finally
          (setf (frame-display-current-y frame-display) current-y)
          ;; When there are frames displayed, shrink the workspace.
          (when (and shrink-wrap? (frame-display-alist frame-display))
            (shrink-wrap-workspace workspace))))



;;; The function `validate-and-update-frame-display-alist' is used to validate a
;;; frame-display alist.  The form of the alist is:
;;; ((thing . (frame-representation . current-frame-serial-number)) ...)
;;; If a reclaimed frame is found the associated cons it is removed from the
;;; alist.  The frame-display-alist is returned.

;; Used in NUPEC.

(defun validate-and-update-frame-display-alist (frame-display)
  (loop with head = nil
        with element-to-check = (frame-display-alist frame-display)
        while element-to-check
        do
    (cond ((frame-has-been-reprocessed-p
             (cadar element-to-check) (cddar element-to-check))
           (if (null head)
               (setf (frame-display-alist frame-display) (cdr element-to-check))
               (setf (cdr head) (cdr element-to-check)))
           (reclaim-frame-serial-number (cddar element-to-check))
           (reclaim-frame-display-list-given-tail (car element-to-check)
                                                  (cdar element-to-check))
           (setq element-to-check
                 (prog1 (cdr element-to-check)
                        (reclaim-frame-display-cons element-to-check))))
          (t
           (setq head element-to-check)
           (setq element-to-check (cdr element-to-check)))))
  (frame-display-alist frame-display))




;;; The function `delete-and-reclaim-frame-display' deletes and reclaims
;;; the frame-display.  Optionally, the workspace and its sub-blocks are also
;;; deleted and reclaimed.  The frame-display structure and its contents are
;;; reclaimed and should not be referenced after calling this function.

(defun delete-and-reclaim-frame-display
       (frame-display delete-workspace?)
  (when delete-workspace?
    (delete-frame (frame-display-workspace frame-display))
;    (loop for (frame . frame-representation) in
;              (frame-display-alist frame-display)
;          do
;      (delete-frame frame-representation)
;          finally
;            (delete-frame (frame-display-workspace frame-display)))
    )

  (reclaim-frame-display frame-display))


; Is it necessary to delete the sub-blocks of the workspace or does deleting
; the workspace delete the sub-blocks !!????






;;;; Enhanced KB Building Facilities


;;; ...




;;; The hash table `dynamic-rule-displays' is used to hash from rules to
;;; displays: dynamic-rule-displays and generic-rule-displays.  This is useful
;;; when updating displays.

(def-hash-table dynamic-rule-displays
                :hash-function-or-macro frame-hash-function)




;;; The system variable `dynamic-rule-display-hash-table' is used to hold
;;; the hash-table which hashed from rules to dynamic-rule-displays and objects
;;; to generic-rule-displays.

(def-system-variable dynamic-rule-display-hash-table
                     queries nil)




;;; The function `create-dynamic-rule-display' creates and initializes a
;;; frame-display for a rule or object.  It sets a slot of the workspace to point
;;; to the frame-display.  (This allows the deleting and reclaiming of the
;;; frame-display when the workspace is deleted.)  Also, the display associated
;;; with the frame is saved in the dynamic-rule hash-table, and the hash-key is
;;; saved.  The frame-display is returned.

(defun create-dynamic-rule-display (rule-or-object-frame)
  (let ((frame-display (create-frame-display)))
    (setf (associated-dynamic-structure
            (frame-display-workspace frame-display))
          frame-display)
    (setf (reclaimer-for-dynamic-workspace-associated-structure frame-display)
          'reclaim-dynamic-rule-display)
    ;; Save the hash key.
    (setf (frame-display-hash-key frame-display) rule-or-object-frame)
    ;; Hash the display of the rule or object.
    (setf (get-dynamic-rule-displays rule-or-object-frame
                                     dynamic-rule-display-hash-table)
          (frame-display-cons frame-display (get-dynamic-rule-displays
                                              rule-or-object-frame
                                              dynamic-rule-display-hash-table)))
    frame-display))




;;; The function `reclaim-dynamic-rule-display' deletes and reclaims a
;;; frame-display.  It also clears the workspace pointer to the frame-display,
;;; and updates the frame-display hash-table.  This function does not delete the
;;; associated workspace.  (When the workspace is deleted, this function is
;;; called.)

(defun reclaim-dynamic-rule-display (frame-display)
  ;; Update the frame-display hash-table value for the rule-frame.
  (let* ((object-or-rule-frame (frame-display-hash-key frame-display))
         (new-display-list (delete-frame-display-element
                             frame-display
                             (get-dynamic-rule-displays
                               object-or-rule-frame
                               dynamic-rule-display-hash-table))))
    (if new-display-list
        (setf (get-dynamic-rule-displays object-or-rule-frame
                                         dynamic-rule-display-hash-table)
              new-display-list)
        (delete-dynamic-rule-displays object-or-rule-frame
                                      dynamic-rule-display-hash-table))
                                                       ; The cleanup function
                                                       ; for the frame-display
                                                       ; needs to be abstracted.
                                                       ; cpm, 1-30-90.
    (cleanup-dynamic-rule-display frame-display)

    (setf (associated-dynamic-structure (frame-display-workspace frame-display))
          nil)
    (reclaim-frame-display frame-display)))




;;; The function `delete-dynamic-rule-displays-for-rule-or-object' deletes
;;; and reclaims all frame-displays (and associated workspaces) for an object or
;;; rule.  This function works by deleting the workspace, which then reclaims
;;; the dynamic-rule-display, updating the frame-display hash-table.  This
;;; function should be called when a rule or object is deleted.

(defun delete-dynamic-rule-displays-for-rule-or-object (object-or-rule)
  (when dynamic-rule-display-hash-table
    (loop for rule-display in
          (get-dynamic-rule-displays
            object-or-rule dynamic-rule-display-hash-table)
          ;; Collect rule-displays first since delete-workspace calls
          ;; dynamic-rule-display reclaimer which then operates on the
          ;; rule-display list.
          collect rule-display into rule-displays using frame-display-cons
          finally
            (loop for display in rule-displays
                  as display-workspace = (frame-display-workspace display)
                  when display-workspace
                    do (delete-frame display-workspace))
            (reclaim-frame-display-list rule-displays))))



;;; Functions and macros that create the frame representations that are
;;; displayed in the frame-display.

(defmacro make-explanation-display-text (title-text-string)
  `(make-explanation-table
     nil (slot-value-cons
           (copy-text-string ,title-text-string) nil)))

(defmacro make-explanation-frame-representation (frame)
  `(make-short-representation ,frame nil 'small))

(defun make-explanation-rule-instance-representation (rule-instance display-rule-frame?)
  (let* ((rule (ri-rule rule-instance))
         (serial-number (copy-frame-serial-number (ri-frame-serial-number rule-instance)))
         (context-list
          (make-slot-value-lists-of-context
            rule
            (invocation-local-var-vector rule-instance)
            serial-number)))
    (reclaim-frame-serial-number serial-number)
    (if display-rule-frame?
        (make-explanation-table rule context-list)
        (if context-list
            (make-explanation-table
              nil
              (slot-value-cons
                (copy-constant-wide-string #w"Generic bindings of rule invocation")
                context-list))
            (make-explanation-display-text
              "Invocation with no generic bindings.")))))









;;;; Enhanced KB Building Facilities - Dynamic Rule Display


;;; There are several new facilities to be used by a developer when building and
;;; debugging a knowledge base.  One of these is a "dynamic rule display".  This
;;; display contains a display of each rule-instance that is being executed for
;;; a given rule.  The display is dynamically update as rule-instances are
;;; created and deleted.

;;; The top-level function, make-dynamic-rule-invocation-display, is
;;; called as a result of a user menu selection for a rule.  Rule-instances are
;;; added to and deleted from the display in generate-and-schedule-rule-
;;; instances and dismiss-rule-instances respectively.

;;; A hash-table, which is held in a system variable, is used to map between
;;; rules and rule-displays.  This allows the efficient updating of
;;; rule-displays (i.e., when adding or removing rule instances).  The
;;; hash-table is created upon the first creation of a frame-display.  An alist
;;; is kept on the frame-display structure to map between rule-instances and
;;; rule-instance-representations on the rule-display.




;;; The function `add-rule-instance-to-dynamic-rule-displays' takes a
;;; rule-instance argument.  For each display showing the rule, if the
;;; rule-instance is not yet represented on the display, a frame-representation
;;; is created and added to the frame-display, and the frame-display information
;;; is updated.

(defun add-rule-instance-to-dynamic-rule-displays (rule-instance)
  (when dynamic-rule-display-hash-table
    ;; only update displays when the hash-table is defined (some displays
    ;; already exist).
    (let* ((rule (ri-rule rule-instance))
           (frame-displays (get-dynamic-rule-displays
                             rule
                             dynamic-rule-display-hash-table))
           (update-made? nil))
      (loop for display in frame-displays
            as instance-representation? =
               (if (not (assq rule-instance
                              (frame-display-alist display)))
                   (make-explanation-rule-instance-representation rule-instance nil)
                   nil)
            when instance-representation?
              do
                (progn
                  (add-thing-to-frame-display
                    rule-instance instance-representation? display nil)
                  (setq update-made? t)))
      (when (and update-made?
                 (dynamic-display-delay-in-milliseconds
                   debugging-parameters))
        (force-process-drawing)                ;-dkuznick, 7/16/98
        (c-uninterruptible-sleep
          (dynamic-display-delay-in-milliseconds
                            debugging-parameters))))))

;;; The function `remove-rule-instance-from-dynamic-rule-displays' removes
;;; the frame-representation of a rule-instance from all frame-displays for the
;;; rule.  The frame-display information is updated and the display itself is
;;; updated (redrawn when necessary).

(defun remove-rule-instance-from-dynamic-rule-displays (rule-instance)
  (when dynamic-rule-display-hash-table
    ;; only update displays when the hash-table is defined (some displays
    ;; already exist).
    (let* ((rule (ri-rule rule-instance))
           (frame-displays (get-dynamic-rule-displays
                             rule
                             dynamic-rule-display-hash-table))
           (update-made? nil))
      (loop for display in frame-displays
            as instance-representation? =
               (cadr (assq rule-instance
                          (frame-display-alist display)))
            when instance-representation?
              do
                (progn
                  (remove-thing-from-frame-display
                    rule-instance display)
                  (setq update-made? t)))
      (when (and update-made?
                 (dynamic-display-delay-in-milliseconds
                   debugging-parameters))
        (force-process-drawing)                ;-dkuznick, 7/16/98
        (c-uninterruptible-sleep
        (dynamic-display-delay-in-milliseconds
                            debugging-parameters))))))




;;; The function `make-dynamic-rule-invocation-display' is the top-level
;;; function for creating a display of rule instances for a specified rule.
;;; This display consists of a workspace of frames which represent the
;;; rule-instances.  It is dynamically updated as rule-instances are created and
;;; deleted.  This function is called as a result of the user selecting a
;;; menu-choice associated with a rule.
;;;
;;; The display is created and initialized.  The frame-display hash table is
;;; updated for the rule.  A header (title and rule frame) is added to the
;;; display and the display is shown.

(defun make-dynamic-rule-invocation-display (rule-frame)
  ;; create the hash-table if necessary.
  (unless dynamic-rule-display-hash-table
    (setq dynamic-rule-display-hash-table
          (make-dynamic-rule-displays)))

  (let ((rule-display (create-dynamic-rule-display rule-frame))
        (display-header-title
          (make-explanation-display-text "Dynamic Rule Invocation Display"))
        (display-header-rule (make-explanation-frame-representation rule-frame)))

    ;; add the header to the rule-display.
    (add-thing-to-frame-display
      display-header-title display-header-title rule-display nil)
    (add-thing-to-frame-display
      display-header-rule display-header-rule rule-display nil)
    (when (hash-table-of-rule-instances rule-frame)
      (loop for rule-instance being each hash-value of
                (hash-table-of-rule-instances rule-frame)
            do
        (add-thing-to-frame-display
          rule-instance
          (make-explanation-rule-instance-representation rule-instance nil)
          rule-display
          nil)))
    ;; show the rule-display.
    (show-frame-display rule-display)))






;;;; Enhanced KB Building Facilities - Generic Rule Display




;;; This facility, "generic rule display", is another of the new facilities to
;;; be used by a developer when building and debugging a knowledge base.  This
;;; display contains all currently executing rule instances that have a generic
;;; binding equal to a specified object.  The display is dynamically update as
;;; rule-instances are created and deleted.

;;; The top-level function, make-dynamic-generic-rule-display, is called
;;; as a result of a user menu selection for an object.  Rule-instances are
;;; added to and deleted from the display in generate-and-schedule-rule-
;;; instances and dismiss-rule-instances respectively.

;;; A hash-table, which is held in a system variable, is used to map between
;;; objects and rule-displays.  This allows the efficient updating of
;;; rule-displays (i.e., when adding or removing rule instances).  The
;;; hash-table is created upon the first creation of a frame-display.  An alist
;;; is kept on the frame-display structure to map between rule-instances and
;;; rule-instance-representations on the rule-display.




;;; The hash table `generic-rule-instance-displays' is used to hash from rules to
;;; displays: dynamic-rule-displays and generic-rule-displays.  This is useful
;;; when updating displays.

(def-hash-table generic-rule-instance-displays
                :hash-function-or-macro ri-cached-context-hash-number)



;;; The system variable `generic-rule-instance-display-hash-table' is used
;;; to hold the hash-table which hashed from rule-instances to
;;; generic-rule-displays.  This hash-table is necessary, in addition to
;;; dynamic-rule-display-hash-table, because when dismissing
;;; a rule-instance, the rule-instance no longer has a rule-context (which is
;;; used when hashing from a generic-binding object to a frame-display).

(def-system-variable generic-rule-instance-display-hash-table
                     queries nil)




;;; The function `add-rule-instance-to-generic-rule-displays' takes a
;;; rule-instance argument.  For each display showing an object used as a
;;; generic reference in the rule, if the rule-instance is not yet represented
;;; on the display, a frame-representation is created and added to the
;;; frame-display, and the frame-display information is updated.

(defun add-rule-instance-to-generic-rule-displays (rule-instance)
  (when (and dynamic-rule-display-hash-table
             generic-rule-instance-display-hash-table)
    ;; Only update displays when the hash-table is defined (some displays
    ;; already exist).
    (loop with rule = (ri-rule rule-instance)
          with environment-description
            =
            (byte-code-body-environment-description
              (rule-byte-code-body rule))
          with context = (invocation-local-var-vector rule-instance)
          for index from 0 below (rule-context-length rule)
          repeat (var-count environment-description)
          for value = (svref context index)
          with update-made? = nil
          do
      (when (of-class-p value 'object)
        (loop for display in (get-dynamic-rule-displays
                               value
                               dynamic-rule-display-hash-table)
            as instance-representation? =
               (if (not (assq rule-instance
                              (frame-display-alist display)))
                   (make-explanation-rule-instance-representation rule-instance t)
                   nil)
              when instance-representation?
              do
                (progn
                  ;; Add to display, when not already on the display.
                  (add-thing-to-frame-display
                    rule-instance instance-representation? display nil)

                  ;; Hash the display of the rule instance.
                  (setf (get-generic-rule-instance-displays
                          rule-instance
                          generic-rule-instance-display-hash-table)
                        (frame-display-cons
                          display
                          (get-generic-rule-instance-displays
                            rule-instance
                            generic-rule-instance-display-hash-table)))
                  (setq update-made? t))))
          finally
            (when (and update-made?
                       (dynamic-display-delay-in-milliseconds
                         debugging-parameters))
              (force-process-drawing)                ;-dkuznick, 7/16/98
              (c-uninterruptible-sleep
                (dynamic-display-delay-in-milliseconds
                  debugging-parameters))))))




;;; The function `remove-rule-instance-from-generic-rule-displays' removes
;;; the frame-representation of a rule-instance from all frame-displays for the
;;; object.  The frame-display information is updated and the display itself is
;;; updated (redrawn when necessary).

(defun remove-rule-instance-from-generic-rule-displays (rule-instance)
  (when (and dynamic-rule-display-hash-table
             generic-rule-instance-display-hash-table)
    ;; only update displays when the hash-table is defined (some displays
    ;; already exist).
    (loop for display in
                (get-generic-rule-instance-displays
                   rule-instance
                   generic-rule-instance-display-hash-table)
          as instance-representation? =
             (cadr (assq rule-instance (frame-display-alist display)))
          with update-made? = nil
          when instance-representation?
            do
              (progn
                (remove-thing-from-frame-display
                  rule-instance display)
                (setq update-made? t))
          finally

            ;; Reclaim and delete the hash-table entry for the rule
            ;; instance.
            (reclaim-frame-display-list
              (get-generic-rule-instance-displays
                rule-instance
                generic-rule-instance-display-hash-table))
            (delete-generic-rule-instance-displays
              rule-instance
              generic-rule-instance-display-hash-table)

            (when (and update-made?
                       (dynamic-display-delay-in-milliseconds
                         debugging-parameters))
              (force-process-drawing)                ;-dkuznick, 7/16/98
              (c-uninterruptible-sleep
                (dynamic-display-delay-in-milliseconds
                                  debugging-parameters))))))




;;; The function `make-dynamic-generic-rule-display' is the top-level
;;; function for creating a display of rule instances for a specified object.
;;; This display consists of a workspace of frames which represent the
;;; rule-instances.  It is dynamically updated as rule-instances are created and
;;; deleted.  This function is called as a result of the user selecting a
;;; menu-choice associated with an object.

;;; The display is created and initialized.  The frame-display hash table is
;;; updated for the rule.  A header (title and rule frame) is added to the
;;; display and the display is shown.

(defun make-dynamic-generic-rule-display (object)
  ;; create the hash-table if necessary.
  (unless dynamic-rule-display-hash-table
    (setq dynamic-rule-display-hash-table
          (make-dynamic-rule-displays)))

  (unless generic-rule-instance-display-hash-table
    (setq generic-rule-instance-display-hash-table
          (make-generic-rule-instance-displays)))

  (let ((rule-display (create-dynamic-rule-display object))
        (display-header-title
          (make-explanation-display-text "Dynamic Generic Rule Display"))
        (display-header-rule
          (make-explanation-frame-representation object)))

    ;; add the header to the rule-display.
    (add-thing-to-frame-display
      display-header-title display-header-title rule-display nil)
    ;; add the header to the rule-display.
    (add-thing-to-frame-display
      display-header-rule display-header-rule rule-display nil)

    ;; Add relevant existing rule instances to the frame-display.
    (loop for rule-frame being each class-instance of 'rule
      do
      (when (hash-table-of-rule-instances rule-frame)
        (loop for rule-instance being each hash-value of
                  (hash-table-of-rule-instances rule-frame)
              do
          (when (include-rule-instance-in-dynamic-generic-display-of-object
                  rule-instance object)

            ;; Hash the display of the rule instance.
            (setf (get-generic-rule-instance-displays
                    rule-instance
                    generic-rule-instance-display-hash-table)
                  (frame-display-cons
                    rule-display
                    (get-generic-rule-instance-displays
                      rule-instance
                      generic-rule-instance-display-hash-table)))

            (add-thing-to-frame-display
              rule-instance
              (make-explanation-rule-instance-representation rule-instance t)
              rule-display
              nil)))))

    ;; show the rule-display.
    (show-frame-display rule-display)))




;;; The function
;;; `include-rule-instance-in-dynamic-generic-display-of-object' is used
;;; to determine if a given rule instance should be shown in the display of a
;;; particular object.  This predicate is useful when initially creating the
;;; display for an object.

(defun include-rule-instance-in-dynamic-generic-display-of-object
       (rule-instance object)
    (loop with rule = (ri-rule rule-instance)
          with environment-description =
            (byte-code-body-environment-description
              (rule-byte-code-body rule))
          with context = (invocation-local-var-vector rule-instance)
          for index from 0 below (rule-context-length rule)
          repeat (var-count environment-description)
          for value = (svref context index)
          thereis (eq object value)))



;;; The function `cleanup-dynamic-rule-display' is used to do any cleanup
;;; specific to a type of frame-display before deletion of the frame-display.
;;; In this case, generic-rule-instance-display-hash-table needs to be
;;; updated based on the rule-instances displayed on the frame-display.  This
;;; update occurs only if the hash-table is defined and if the frame-display is
;;; displaying generic-rules for a specific object.

;; this should be abstracted!! cpm, 1-30-90.

(defun cleanup-dynamic-rule-display (frame-display)
  (when generic-rule-instance-display-hash-table
    (when (of-class-p (frame-display-hash-key frame-display) 'object)
      ;; When hashing rule instances for an generic-rule display, delete the
      ;; hash-table entry for the rule-instance.
      (loop for (frame-or-rule-instance . nil) in
                (frame-display-alist frame-display)
            when (rule-instance-p frame-or-rule-instance)
              do
                ;; remove the display from the hash-table for the rule-instance.
                (let ((new-display-list
                        (delete-frame-display-element
                          frame-display
                          (get-generic-rule-instance-displays
                            frame-or-rule-instance
                            generic-rule-instance-display-hash-table))))
                  (if new-display-list
                      (setf (get-generic-rule-instance-displays
                              frame-or-rule-instance
                              generic-rule-instance-display-hash-table)
                            new-display-list)
                      (delete-generic-rule-instance-displays
                        frame-or-rule-instance
                        generic-rule-instance-display-hash-table)))))))



#+NUPEC
(defun get-frame-display (dynamic-temporary-workspace)
  (associated-dynamic-structure dynamic-temporary-workspace))

#+NUPEC
(defun get-rule-instance-displays (rule-instance)
  (get-generic-rule-instance-displays
    rule-instance
    generic-rule-instance-display-hash-table))

;; Show on a workspace every rule or procedure
;;
;; Show on a workspace every rule or procedure such that the rule
;;   or procedure ... [can't do it!]
;;
;; Show on a workspace every rule and procedure
;;
;; Show on a workspace every rule and procedure such that the
;;   rule is active or the procedure is active


;; function names not in directory!!

;; The query
;;
;;     show ... every rule such that is-contained-in-
;;       text (the rule, "CONFLICT")
;;
;; prints out @'s in front of the quotes in the Filter slot of the
;; search table.

;; TBD for switch over to new evaluator.







;;;; Todo list of switchover to the new evaluator

;; figure out the policy on where (leave as bug)
;; review how I'm putting notes on the filter.



;;;; Known Bugs

;; Bugs to Fix/To Do
;;
;; "display a table of the class of every definition" displays two different
;; columns of class slots, one with just the class name, and one with
;; the whole description that you see in attribute table headers.  Note that
;; the name-or-names-for-frame slot is aliased for definitions as CLASS.
;; (found by BAH, 3/19/91)


;; Still sending out a few notify users (to every workstations' logbook)
;; for some of the inspect commands, e.g., write-to-file and show-...-hierarchy.
;; At present, I think these are limited to cases of failure.  (MHD 9/12/91)
;; (MHD 9/12/91)


;; Leaves leading spaces that were typed in before, e.g., "every item", in
;; the "filter" slot of the progress table.   Also, doesn't reformat the
;; text --- well, yes it does, but leaves in explicit line breaks and leading
;; and internal spaces, etc.   (MHD 9/12/91)


;; "Filter" is not a good name.  "such that ...", "where ...", etc. are filters.
;; "every ..." is not a filter, but a ??? !   (However, Ben thinks filter is a
;; good name.)  (MHD 9/12/91)



;;;; Old To Do List

;;
;; ;; To Do
;;
;; ;; Visit query-verb
;;
;; ;; hardcopy query-verb
;;
;; ;; finish file names for show in a file.
;;
;; ;; Modify query interface to use an object table with slots that change the
;; ;; different attributes used to setting up a query.
;;
;; ;; do query orderings
;;
;; ;; finish modifying and referencing query-set roles.
;;
;; ;; Move the roles and evaluators for queries into the files roles and eval.
;;
;; ;; Clobber the old find system.


;; command-string is consumed

(defun make-inspect-command-or-signal-error (command-string)
  (let ((inspect-command
          (make-command-frame 'inspect-command command-string)))
    (with-phrase-conses
      (multiple-value-bind (parse-result-or-bad-phrase error-string?)
          (parse-text-string command-string 'query-command inspect-command)
        (cond ((eq parse-result-or-bad-phrase bad-phrase)
               (delete-frame inspect-command)
               (stack-error cached-top-of-stack error-string?))
              (t
               (let* ((bogus-edit-state
                        (make-edit-state))
                      (command-text
                        (convert-text-string-to-text
                          (copy-text-string command-string))))
                 (setf (car (box-translation-and-text inspect-command))
                       (copy-for-slot-value
                         (let ((current-edit-state bogus-edit-state))
                           (setf (text-being-edited current-edit-state) command-text)
                           (rewrite-query-command-parse-into-nicer-format
                             parse-result-or-bad-phrase))))
                 (reclaim-edit-state bogus-edit-state)
                 (reclaim-text command-text)
                 inspect-command)))))))


;;; `g2-run-inspect-command' runs inspect as a command with no results.  For its side effects.
;;; Should be used for replacing and recompiling.

(defun-for-system-procedure g2-run-inspect-command (command-string)
  (let ((inspect-command
          (make-inspect-command-or-signal-error command-string)))
    ;; set command to be "invisible" and have and unlimited time slice
    (setf (run-command-invisibly-p inspect-command) t)
    (setf (run-command-to-completion-p inspect-command) t)
    (for-dummy-workstation
      (execute-inspect-command inspect-command))
    (delete-frame inspect-command)))

(define-system-rpc-access (g2-run-inspect-command ())
    ((command-string text))
  (g2-run-inspect-command command-string))

(defvar highest-inspect-session-id 1)

(def-class (query-representation
             callback-representation define-predicate)
  (query-representation-task nil vector-slot)
  (query-representation-user-data nil vector-slot) ;this is an evaluation-value!
                                                   ; -dougo, 1/31/05
  (query-representation-command nil vector-slot)
  (query-representation-priority nil vector-slot)
  (query-representation-task-interval nil vector-slot)
  (query-representation-session-id nil vector-slot)
  (query-representation-paused-p nil vector-slot))

(def-slot-value-reclaimer query-representation-task (value frame)
  (declare (ignore value))
  (cancel-task (query-representation-task frame)))

(def-slot-value-reclaimer query-representation-user-data (user-data frame)
  (reclaim-if-evaluation-value user-data)
  (setf (query-representation-user-data frame) nil))

(defun schedule-search-task (kb-search-state)
  (let ((query-representation
          (kb-search-state-remote-representation? kb-search-state)))
    (unless (query-representation-paused-p query-representation)
      (with-temporary-gensym-float-creation schedule-search-task
        (with-future-scheduling
            ((query-representation-task query-representation)
             (query-representation-priority query-representation)
             (+e (managed-float-value (clock-get current-g2-time))
                 (managed-float-value
                 (query-representation-task-interval query-representation)))
             nil
             nil
             t
             (nil nil 'reclaim-frame-serial-number))
          (resume-search-task-in-workstation
            current-workstation kb-search-state
            (copy-frame-serial-number (frame-serial-number kb-search-state))))))))

(defun resume-search-task-in-workstation (workstation kb-search-state reference-serial-number)
  (if (dummy-workstation-p workstation)
      (for-dummy-workstation
        (search-items-a-little kb-search-state reference-serial-number))
      (for-workstation (workstation)
        (search-items-a-little kb-search-state reference-serial-number))))

(defun-for-system-procedure g2-start-inspect-session
    (command-string callback user-data priority task-interval)
 (start-inspect-session-internal
   command-string
   (demand-representation-callback-remote-procedure-name callback)
   user-data priority task-interval))

;;; NOTE: this function does not call demand-representation-callback-remote-procedure-name
;;; on the callback argument before setting it in the query representation
;;; Therefore, if the callback is a symbol, it is assumed by start-local-representation-callback
;;; that the callback is a local lisp function, accepting the exact arugments assumed by
;;; return-remote-query-results.
(defun-simple start-inspect-session-internal
    (command-string callback user-data priority task-interval)
  (let* ((inspect-command
           (make-inspect-command-or-signal-error command-string))
         (representation
           (make-query-representation inspect-command callback user-data priority task-interval)))
    ;; set command to be "invisible" and have and unlimited time slice
    (setf (run-command-invisibly-p inspect-command) t)
    (setf (run-command-remotely-p inspect-command) t)
    (let ((current-remote-search-representation? representation))
      (for-dummy-workstation
        (execute-inspect-command inspect-command)))
    (query-representation-session-id representation)))

(defun-simple make-query-representation (inspect-command callback user-data priority task-interval)
  (let* ((socket (or current-system-rpc-icp-socket? local-pseudo-socket))
         (representation
           (make-representation
             socket
             inspect-command 'query-representation)))
    (store-callback-representation representation)
    (setf (representation-address representation)
          (slot-value-list
            'socket socket
            'session-id (if current-system-rpc-icp-socket?
                            (icp-socket-session-id current-system-rpc-icp-socket?)
                            12345678)))
    (setf (callback-representation-callback-procedure representation) callback)
    (when (framep callback)
      (frame-serial-number-setf (callback-representation-callback-serial-number representation)
                                (frame-serial-number callback)))
    (setf (query-representation-user-data representation) user-data)
    (setf (query-representation-command representation) inspect-command)
    (setf (query-representation-priority representation)
          (minf 10 (maxf priority 1)))
    (setf (query-representation-task-interval representation) task-interval)
    (setf (query-representation-session-id representation)
          (incff highest-inspect-session-id))
    representation))

(defun-simple find-query-representation-by-id (session-id)
  (loop for representation being each class-instance of 'query-representation
        when (=f (query-representation-session-id representation) session-id)
          return representation
        finally
          (return nil)))

(defun-for-system-procedure g2-pause-inspect-session (session-id)
  (let ((representation? (find-query-representation-by-id session-id)))
    (when representation?
      (setf (query-representation-paused-p representation?) t))
    nil))

(defun-for-system-procedure g2-resume-inspect-session (session-id)
  (let ((representation? (find-query-representation-by-id session-id)))
    (when representation?
      (setf (query-representation-paused-p representation?) nil)
      (let ((kb-search-state?
              (search-state-for-inspect-command?
                (query-representation-command representation?))))
        (when kb-search-state?
          (schedule-search-task kb-search-state?))))
    nil))

(defun-for-system-procedure g2-abort-inspect-session (session-id)
  (let ((representation? (find-query-representation-by-id session-id)))
    (when representation?
      (setf (query-representation-paused-p representation?) t)
      (when (query-representation-task representation?)
        (cancel-task (query-representation-task representation?)))
      (delete-frame
        (query-representation-command representation?)))))

;;; item-list (of eval conses) is consumed

(defun return-remote-query-results (kb-search-state item-list done-p)
  (let* ((query-representation
           (kb-search-state-remote-representation? kb-search-state))
         (argument-list
          (eval-list
            (if done-p 'finished 'frames-remaining)
            (total-number-of-items-to-examine kb-search-state)
            (number-of-items-examined-so-far kb-search-state)
            (number-of-items-found kb-search-state)
            (allocate-evaluation-sequence item-list)
            (copy-if-evaluation-value
              (query-representation-user-data query-representation))))
         (address (representation-address query-representation))
         (socket (getfq address 'socket)))
    (callback-representation-fire-callback
      query-representation socket argument-list)
    (when done-p
      (delete-frame
        (query-representation-command query-representation)))))

(define-system-rpc-access (g2-start-inspect-session (integer))
    ((command-string text)
     (callback symbol)
     (user-data datum)
     (priority integer)
     (task-interval float))
  (g2-start-inspect-session command-string callback user-data
                            priority task-interval))

(define-system-rpc-access (g2-pause-inspect-session ())
    ((session-id integer))
  (g2-pause-inspect-session session-id))

(define-system-rpc-access (g2-resume-inspect-session ())
    ((session-id integer))
  (g2-resume-inspect-session session-id))

(define-system-rpc-access (g2-abort-inspect-session ())
    ((session-id integer))
  (g2-abort-inspect-session session-id))

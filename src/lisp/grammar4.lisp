;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GRAMMAR4

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Michael Levin and Mark H. David

;;;; NUPEC Synchronize Action Grammar



;;; To GRAMMAR4A


;;; The NUPEC synchronize action grammar specifies a list of things to
;;; synchronize and a G2 to G2 interface object across which the synchronize
;;; should occur.  The things are in a list separated with commas, and using
;;; 'and before the last one when there are 3 or more. (This form of grammar is
;;; known to be user unfriendly even if "Englishy".  It requires more editing
;;; than a list with just commas when making changes to the rule. -ml 12/4/89 I
;;; added your name to the editorial comment here, Michael.  -jra 12/5/89) The
;;; things are either unqie designations or "every <class>".  The
;;; internal-form of the action is:

;;;   (nupec-synchronize synchronization-object list-of-designations
;;;                      list-of-classes)

;;; The template should be:
;;;   (nupec-synchronize designation designation-list other)

(add-grammar-rules
  '(
;;    Moved to authorize-nupec.  cpm, 3/15/91
;    (action ('nupec 'synchronize synchronize-reference-list
;	     'across unique-designation)
;	    (nupec-synchronize 5 3)
;	    fix-nupec-synchronize)

    (synchronize-reference-list synchronize-reference)
    (synchronize-reference-list
      (synchronize-reference 'and synchronize-reference)
      (and 1 3))
    (synchronize-reference-list
      (synchronize-reference '\, synchronize-reference-tail)
      (and 1 3) simplify-associative-operation)

    (synchronize-reference-tail 
      (synchronize-reference '\, 'and synchronize-reference)
      (and 1 4))
    (synchronize-reference-tail
      (synchronize-reference '\, synchronize-reference-tail)
      (and 1 3) simplify-associative-operation)

    (synchronize-reference unique-designation)
    (synchronize-reference ('every class))
    ))




;;; The function `fix-nupec-synchronize' is given (nupec-synchronize designation
;;; x) where x is (AND Y1 Y2 ...) or Y1. Each Y is either a unique-designation
;;; or (EVERY <class). The list is sorted into two lists, one for unique
;;; designations, and one for class names. The output is according to the
;;; template for nupec-synchronize specified above.

(defun fix-nupec-synchronize (form)
  (loop with reference-list = (third form)
	with fixed-reference-list =
	  (if (and (consp reference-list)
		   (eq (car reference-list) 'and))
	      (cdr reference-list)
	      (phrase-list reference-list))
	with unique-designations = nil
	with classes = nil
	for reference in fixed-reference-list
	doing
    (if (and (consp reference) (eq (car reference) 'every))
	(setq classes (nconc classes (phrase-list (second reference))))
	(setq unique-designations
	      (nconc unique-designations (phrase-list reference))))
    finally
      (return (phrase-list 'nupec-synchronize
			   (second form)
			   unique-designations
			   classes))))




;;;; Create Explanation Grammar




;;; The Create Explanation action grammar creates an explanation for a
;;; variable or parameter.

;;; The internal-form of the actions are:
;;;   (create-explanation variable-or-parameter [local-name])

;;; The action template is:
;;;   (create-explanation designation designation)


;; Moved the following grammar to authorize-nupec.  cpm, 3/15/91
;;
;; Back here now that it's part of standard G2. -dkuznick, 7/15/98
;;
(add-grammar-rules
  
  ;; "a-or-an" in the following two rules used to be 'a, but that was too
  ;; cute; when users selected "a" they would get a subset of the grammar
  ;; they would have gotten if they had selected "an", since the other rules
  ;; contribute additional grammar (for ACTION, following CREATE) that can
  ;; begin with "an". (MHD 1/11/91)
  '((action ('create a-or-an 'explanation 'for unique-designation)
	    (create-explanation 5))
   
    (action ('create a-or-an 'explanation local-name 'for unique-designation)
	    (create-explanation 6 4))))






;;;; NUPEC extra action grammar.  This is used in the module Rules.




(add-grammar-rules
  '((nupec-extra-action-list
      (action 'and action-list-3) (and 1 3) simplify-associative-operation)
    (nupec-extra-action-list action)
    (nupec-extra-action-list 'none nil)))






;;;; Action Grammar




(add-grammar-rules 

  '((action ('move e-designation 'by '\( unique-expression '\, unique-expression '\) )
          (move 2 5 7))
    (action ('move e-designation 'to '\( unique-expression '\, unique-expression '\) )
          (set-position 2 5 7))
    
    (action ('transfer e-designation 'to e-designation)
     (transfer 2 4) reject-transfer-to-the-mouse-of)
    (action ('transfer e-designation 'to e-designation 'at
	     '\( unique-expression '\, unique-expression '\))
     (transfer 2 4 7 9) reject-transfer-to-the-mouse-of)
    ;; TRANSFER <item/e-designation> TO THE MOUSE OF <g2-window/e-designation>
    ;; See also the concept transfer-item-to-mouse, and FMW's note there on the
    ;; implementation history around this feature.  This addition to the grammar
    ;; resolved bug HQ-765877 "Promping: transfer <item> to the mouse of
    ;; <window>".  The reject-... transformation for the previous rules
    ;; with "transfer ... to" syntax prevents ambuity.  (MHD 6/17/99)
    (action ('transfer e-designation 'to 'the 'mouse 'of e-designation)
     (transfer 2 7))
    (action ('transfer e-designation 'off)
     (transfer 2))
    
    (action ('rotate e-designation 'by unique-expression 'degrees) (rotate 2 4))
    (action ('rotate e-designation 'to 'the 'heading unique-expression 'degrees)
          (set-heading 2 6))

    (action ('update e-designation))

    (the-word-rules 'rules)

    ;; color change actions:

    ;; change the <region> icon-color of <e-designation> to <iqe>
    ;; change the <region> stripe-color of <e-designation> to <iqe>
    ;; change the <system-attribute> of <e-designation> to <iqe>
    ;; 
    ;; The internal form of these is:
    ;;     (change-item-color e-designation iqe region-or-system-region)
    ;;    region-or-system-region may be a region name, or one of:
    ;;              'icon-color, 'stripe-color, 'background-color,
    ;;              'text-color, 'border-color, 'foreground-color
    ;;    'icon-color and 'stripe-color are not really useful information.

    ;; When a user supplies a region, it is given as the third argument.
    ;; If the user does not supply a region argument, then the third
    ;; argument will be either icon-color, or stripe-color.  This is
    ;; really unneccesary information, but is passed on anyway.
    
    ;;     
    ;; IQE is either a symbol which is translated with a quote, or else it is
    ;; a non-atomic unique-expression.
    ;;
    ;; change the color-pattern of <designation> so that
    ;;    {<region> = <expression> or
    ;;    <region> is <color-or-metacolor>} with commas
    ;;
    ;; The internal form is
    ;;     (change-item-color-pattern e-designation {(region . <expression>)})
    ;;   where expression, if a color is quoted.
    ;;   
    ;; The old form will still be interpreted, but will not result from
    ;; new grammar.

    (action color-change-action)

    (color-change-action
     ('change 'the color-attribute 'of e-designation 'to unique-iqe)
     (change-item-color 5 7 '3)
     (fix-iqe 2))
    (color-change-action
     ('change 'the region icon-or-stripe-color 'of e-designation 'to unique-iqe)
     (change-item-color 6 8 '3) (fix-iqe 2))

    (color-change-action
     ('change 'the 'color-pattern 'of e-designation 'so 'that color-change)
     (change-item-color-pattern 5 8))
    (color-change-action
     ('change 'the 'color-pattern 'of e-designation 'so 'that
      color-change-list)
     (change-item-color-pattern 5 . 8))

    (color-change (region-or-color-attribute 'is color-or-metacolor) ('1 . '3))
    (color-change (region-or-color-attribute '= unique-expression) ('1 . 3))

    (color-change-list color-change-list-1 1 cdr)

    (color-change-list-1 (color-change '\, color-change) (2 1 3))
    (color-change-list-1
     (color-change '\, color-change-list-1)
     (2 1 3)
     simplify-associative-operation)
    

    ;; An IQE is an Implicitly Quoted Expresion.  In the case that it is
    ;; a color, it must be turned into a quoted form.
    
    (unique-iqe unique-expression)
    (unique-iqe color)
    (unique-iqe metacolor)

    (color-or-metacolor color)
    (color-or-metacolor metacolor)

    (color-for-class? color-or-metacolor 1 filter-out-illegal-color-names)
    (color-for-class? 'inherited nil nil-function) 	; <- NOT WORKING -- Not succeeding in
							; transforming INHERITED to NIL. Must
							;  handle in compiler! investigate!
							;  (MHD 4/28/92)
    (region unreserved-symbol 1 filter-out-illegal-region-names)
    (region? region 1)
    (region? 'none nil nil-function)


    (region-or-color-or-metacolor color-or-metacolor)	; "label", "line-
    (region-or-color-or-metacolor region)		;   drawing-label" ??

    (icon-or-stripe-color 'icon-color)
    (icon-or-stripe-color 'stripe-color)

;    (color-attribute 'background-color)
;    (color-attribute 'text-color)
;    (color-attribute 'border-color)
;    (color-attribute 'foreground-color)
;    (color-attribute 'foreground-color)
;    (color-attribute icon-or-stripe-color)

    (region-or-color-attribute region)
    (region-or-color-attribute color-attribute)

    ;; End of grammar for color change.


    ;; This is the beginning of a facility to change system attributes of items.
    ;; The general form is "change the <system slot name> of <designation> to
    ;; <expression>). Presently, the system-slot-name will be made into a
    ;; semi-open category as with graphic attributes.

    (action ('change 'the 'array-length 'of e-designation 'to unique-expression)
	    (change-system-attribute 5 '3 7))

    (action ('change 'the 'gsi-interface-name 'of e-designation 'to unique-expression)
	    (change-system-attribute 5 '3 7))

    (action ('change 'the 'size 'of e-designation 'to 'minimum)
	    (change-system-attribute 5 '3 '7))

    (action ('change 'the 'name 'of e-designation 'to unique-expression)
	    (change-system-attribute 5 '3 7))

    ;; Change-the-text-of action grammar.

    ;; generic e-designation grammar.
    (action ('change 'the 'text 'of e-designation 'to unique-expression)
	    (change-the-text-of-attribute 5 7))
    ;; The special-designation for change limits the visibility of the change
    ;; slot to change-the-text-of grammar.
    (change-designation ('the 'change 'of e-designation) (the change 4))
    (action ('change 'the 'text 'of change-designation 'to unique-expression)
	    (change-the-text-of-attribute 5 7))
    (action ('change 'the 'text 'of special-designation 'to unique-expression)
            (change-the-text-of-attribute 5 7))
    ;; The "change array-or-list element" grammar was added in version 3.0.
    ;; In version 4.0, modified the grammar in the following ways:
    ;; 1. The following grammar produces a frame-note warning, but still
    ;;    compiles.
    ;;      "change the attribute of array-or-list [index] = ..."
    ;;    This action references the array-or-list contained in the attribute.
    ;;    It should be illegal and will be made obsolete in a later release!!
    ;; 2. The following grammar is new to version 4.0 and is the correct way
    ;;    of referencing an array-or-list contained in an attribute.  (This is
    ;;    the replace grammar mentioned in #1.)
    ;;      "change (the attribute of array-or-list) [index] = ..."
    ;; 3. "CHANGE EVERY list-or-array-designation [index]"
    ;;    is only valid for "change every <class> [index]".
    ;;    Note that CONCLUDE, allows generic references, but the array-or-list
    ;;    must be a unique designation.

    ;; Note that the transformation function allows both for the old grammar
    ;; (#1) and the new, correct grammar (#2).
    ;; Note also that the action compiler changes the parse before compiling it.
    ;; It removes the nth-element role and compiles the list-or-array
    ;; designation and index expression separately.  (It does this so that it
    ;; does not compile into an item-or-place-reference.)  This modification is
    ;; not done in the parse transformation function because the compiler needs
    ;; to be able to recognize the old grammar (#1) and give a warning.
    ;; - cpm, 11/11/94

    ;; New grammar (#2 above)
    ;; (change-nth-element
    ;;   (the (nth-element item-or-datum) array-or-list index)
    ;;   expression)
    ;; Transformed in the compiler to:
    ;;   (change-nth-element array-or-list index expression)

    ;; Old grammar, causes a warning (#1 above)
    ;; (change-nth-element
    ;;   (quantifier role designation-ending-with-nth-element)
    ;;   expression)
    ;; Where designation-ending-with-nth-element =
    ;;  (quantifier role designation-ending-with-nth-element)
    ;; OR
    ;;  (quantifier role (the (nth-element item-or-datum) item index)
    ;; Transformed in the compiler to:
    ;;   (change-nth-element
    ;;     (quantifier role modified-designation-ending-with-nth-element)
    ;;     index expression)
    ;; Where modified-designation-ending-with-nth-element =
    ;;   the designation with the nth-element role and quantifier removed but
    ;;   the first item domain kept.
    ;;   For example:
    ;;     (quantifier-N-3 role-N-3 (q-N-2 r-N-2 (q-N-1 r-N-1 item)))

    (action
     ('change nth-element-designation '\= unique-expression)
     (change-nth-element 2 4)
     validate-change-nth-element-parse)
    (action ('change nth-element-designation '\= unique-logical-expression)
     (change-nth-element 2 4)
     validate-change-nth-element-parse)
    (action
     ('change nth-element-designation 'to 'have 'no 'value)
     (change-nth-element-to-no-value 2)
     validate-change-nth-element-parse)
    ;; CHANGE EVERY <CLASS> [index] = VALUE
    ;;  Only allow a simple form of EVERY, so that version 3.0 KB's that allowed
    ;;  this expression in the old (3.0) grammar will still compile in 4.0.
    ;;  - cpm, 1/20/95
    (action ('change 'every class '[ unique-expression ']
	     '\= unique-logical-expression)
     (change-nth-element (2 3) 5 8)
     (restrict-if-slot-edit-feature procedure e-designation))
    (action ('change 'every class '[ unique-expression ']
	     '\= unique-expression)
     (change-nth-element (2 3) 5 8)
     (restrict-if-slot-edit-feature procedure e-designation))
    (action ('start procedure-designation procedure-calling-argument-list) 
	    (1 2 3) fix-start-action)
    (action ('start procedure-designation '\( '\) )
            (1 2 nil) fix-start-action)
    #+mtg2
    (action ('spawn procedure-designation procedure-calling-argument-list) 
            (1 2 3) fix-start-action)
    #+mtg2
    (action ('spawn procedure-designation '\( '\) )
	    (1 2 nil) fix-start-action)
	;added by SoftServe
	#+lispworks
	(action ('start 'thread procedure-designation procedure-calling-argument-list) 
	    ('start-thread 3 4) fix-start-action)
    #+lispworks
	(action ('start 'thread procedure-designation '\( '\) )
	    ('start-thread 3 nil) fix-start-action)
	;end of changes
    (action ('start procedure-designation procedure-calling-argument-list
	     start-action-tail)
	    (1 2 3 . 4) fix-start-action)
    (action ('start procedure-designation '\( '\) start-action-tail)
	    (1 2 nil . 5) fix-start-action)

    (procedure-designation e-designation)
    (procedure-designation procedure-name)

    (start-action-tail ('at 'priority unique-expression) ((priority 3)))
    (start-action-tail ('after unique-expression) ((interval 2)))
    (start-action-tail ('at 'priority unique-expression 'after unique-expression)
		       ((priority 3) (interval 5)))
    (start-action-tail ('across unique-designation) ((across 2)))
    (start-action-tail ('at 'priority unique-expression 'across unique-designation)
		       ((priority 3) (across 5)))
    (start-action-tail ('after unique-expression 'across unique-designation)
		       ((interval 2) (across 4)))
    (start-action-tail ('at 'priority unique-expression
			'after unique-expression 'across unique-designation)
		       ((priority 3) (interval 5) (across 7)))

    (procedure-calling-argument unique-expression)
    (procedure-calling-argument unique-logical-expression)
    (procedure-calling-argument e-designation)

    (procedure-calling-argument-list ( '\( procedure-calling-argument '\) ) (2))
    (procedure-calling-argument-list ( '\( procedure-calling-argument '\,
				    procedure-calling-argument-list-tail) (2 . 4))
  
    (procedure-calling-argument-list-tail (procedure-calling-argument '\) ) (1))
    (procedure-calling-argument-list-tail
      (procedure-calling-argument '\, procedure-calling-argument-list-tail) (1 . 3))

    ;; CREATE A <class> [USING STRUCT]
    (action ('create a-or-an class)
	    (create (quote 3)))

    ;; CREATE A <class> <local-name> [USING STRUCT]
    (action ('create a-or-an class local-name)
	    (create (quote 3) 4))

    ;; CREATE AN INSTANCE OF THE CLASS NAMED BY <symbol> [USING STRUCT]
    (action ('create a-or-an 'instance 'of 'the 'class 'named 'by
	     unique-expression)
	    (create 9))

    ;; CREATE AN INSTANCE OF THE CLASS <local-name> NAMED BY <symbol>
    ;;  [USING STRUCT]
    (action ('create a-or-an 'instance local-name 'of 'the 'class 'named 'by
	     unique-expression)
	    (create 10 4))

    ;; "a-or-an" in the above rules ("create instance of the class named by")
    ;; used to be 'an, but that was too cute; when users selected "an" they
    ;; would get a subset of the grammar they would have gotten if they had
    ;; selected "a", since the above rules contribute additional grammar that
    ;; can begin with "a". (MHD 1/11/91)

    ;; CREATE A <class> BY CLONING <item> [USING STRUCT]
    (action ('create a-or-an class 'by 'cloning unique-designation)
	    (create-by-cloning (quote 3) 6))

    ;; CREATE A <class> <local-name> BY CLONING <item> [USING STRUCT]
    (action ('create a-or-an class local-name 'by 'cloning unique-designation)
     (create-by-cloning (quote 3) 7 4))
    (action ('delete e-designation))
    
    ;; Make-permanent, make-transient, and make-subworkspace were added for G2
    ;; version 3.0.
    (action ('make e-designation 'permanent) (make-permanent 2))
    (action ('make e-designation 'transient) (make-transient 2))
    (action ('make unique-designation 'the 'subworkspace 'of unique-designation)
	    (make-subworkspace 2 6))

    ;; In version 4.0, the INSERT action is parsed to G2-LIST-INSERT, instead of
    ;; g2-list-insert-expression or g2-list-insert-designation.
    ;;
    ;; In 4.0, there is a new grammar that does not require the list-type in the
    ;; action statement.  Both the old and new grammars now parse to the new
    ;; g2-list-insert action.  We are keeping the old grammar so that existing
    ;; KB's can still compile.  It would be nice to phase out the old grammar at
    ;; some point.  - cpm, 11/18/93

    (action ('insert unique-expression 'at 'the 'beginning 'of 'the
	     g2-non-logical-datum-type 'list e-designation)
	    (g2-list-insert 10 2 nil beginning))
    (action ('insert unique-logical-expression 'at 'the 'beginning 'of 'the
	     'truth-value 'list e-designation)
	    (g2-list-insert 10 2 nil beginning))
    (action ('insert e-designation 'at 'the 'beginning 'of 'the class 'list
	     e-designation) 
	    (g2-list-insert 10 2 nil beginning))

    ;; new grammar for version 4.0
    (action ('insert unique-expression 'at 'the 'beginning 'of e-designation)
	    (g2-list-insert 7 2 nil beginning))
    (action ('insert unique-logical-expression 'at 'the 'beginning 'of e-designation)
	    (g2-list-insert 7 2 nil beginning))
    (action ('insert e-designation 'at 'the 'beginning 'of e-designation) 
	    (g2-list-insert 7 2 nil beginning))

    (action ('insert unique-expression 'at 'the 'end 'of 'the
	     g2-non-logical-datum-type 'list e-designation) 
	    (g2-list-insert 10 2 nil end))
    (action ('insert unique-logical-expression 'at 'the 'end 'of 'the 'truth-value
	     'list e-designation)
	    (g2-list-insert 10 2 nil end))
    (action ('insert e-designation 'at 'the 'end 'of 'the class 'list
	     e-designation) 
	    (g2-list-insert 10 2 nil end))

    ;; new grammar for version 4.0
    (action ('insert unique-expression 'at 'the 'end 'of e-designation) 
	    (g2-list-insert 7 2 nil end))
    (action ('insert unique-logical-expression 'at 'the 'end 'of e-designation)
	    (g2-list-insert 7 2 nil end))
    (action ('insert e-designation 'at 'the 'end 'of e-designation) 
	    (g2-list-insert 7 2 nil end))

    (action ('insert unique-expression 'before expression 'in 'the
	     g2-non-logical-datum-type 'list e-designation)
	    (g2-list-insert 9 2 4 before))
    (action ('insert unique-logical-expression 'before unique-logical-expression 'in 'the
	     'truth-value 'list e-designation)
	    (g2-list-insert 9 2 4 before))
    (action ('insert e-designation 'before e-designation 'in 'the class 'list
	     e-designation) 
	    (g2-list-insert 9 2 4 before))

    ;; new grammar for version 4.0
    (action ('insert unique-expression 'before expression 'in e-designation)
	    (g2-list-insert 6 2 4 before))
    (action ('insert unique-logical-expression 'before unique-logical-expression 'in
	     e-designation)
	    (g2-list-insert 6 2 4 before))
    (action ('insert e-designation 'before e-designation 'in e-designation) 
	    (g2-list-insert 6 2 4 before))
    (action ('insert unique-expression 'before 'element expression 'of e-designation) 
	    (g2-list-insert 7 2 5 before-element))
    (action ('insert unique-expression 'after expression 'in 'the
	     g2-non-logical-datum-type 'list e-designation) 
	    (g2-list-insert 9 2 4 after))
    (action ('insert unique-logical-expression 'after
	     
	     unique-logical-expression			; Fixed! LOGICA-EXPRESSION was
						;   here in 2.1, 2.0!
						;   (MHD 2/21/91)
	     'in 'the
	     'truth-value 'list e-designation) 
	    (g2-list-insert 9 2 4 after))
    (action ('insert e-designation 'after e-designation 'in 'the class 'list
	     e-designation)
	    (g2-list-insert 9 2 4 after))

    
    ;; new grammar for version 4.0
    (action ('insert unique-expression 'after expression 'in e-designation) 
	    (g2-list-insert 6 2 4 after))
    (action ('insert unique-expression 'after 'element expression 'of e-designation) 
	    (g2-list-insert 7 2 5 after-element))
    (action ('insert unique-logical-expression 'after unique-logical-expression 'in
	     e-designation) 
	    (g2-list-insert 6 2 4 after))
    (action ('insert e-designation 'after e-designation 'in e-designation)
	    (g2-list-insert 6 2 4 after))

    ;; In version 4.0, the REMOVE action is parsed to G2-LIST-REMOVE, instead of
    ;; g2-list-remove-expression or g2-list-remove-designation.  When removing
    ;; a specific element from the list (instead of the first or last element of
    ;; a type), the type is no longer required.

;    (action ('remove 'the 'first g2-datum-type 'from e-designation)
;            (g2-list-remove 6 nil 4 first))
;    (action ('remove 'the 'first class 'from e-designation)
;            (g2-list-remove 6 nil 4 first))

    ;; In 4.0, replaces the above grammar.
    (action ('remove 'the 'first element-type 'from e-designation)
	    (g2-list-remove 6 nil 4 first))

;    (action ('remove 'the 'last g2-datum-type 'from  e-designation)
;            (g2-list-remove 6 nil 4 last))
;    (action ('remove 'the 'last class 'from  e-designation)
;            (g2-list-remove 6 nil 4 last))

    ;; In 4.0, replaces the above grammar.
    (action ('remove 'the 'last element-type 'from  e-designation)
	    (g2-list-remove 6 nil 4 last))

    (action ('remove unique-expression 'from 'the g2-non-logical-datum-type
	     'list e-designation)
	    (g2-list-remove 7 2 nil element))
    (action ('remove unique-logical-expression 'from 'the 'truth-value 'list
	     e-designation)
	    (g2-list-remove 7 2 nil element))
    (action ('remove e-designation 'from 'the class 'list e-designation)
	    (g2-list-remove 7 2 nil element))

    ;; positional remove new to 5.0 -rdf, 4/12/96
    (action ('remove 'element expression 'from e-designation)
	    (g2-list-remove 5 3 nil element-position))

    ;; new grammar for version 4.0
    (action ('remove unique-expression 'from e-designation)
	    (g2-list-remove 4 2 nil element))
    (action ('remove unique-logical-expression 'from e-designation)
	    (g2-list-remove 4 2 nil element))
    (action ('remove e-designation 'from e-designation)
	    (g2-list-remove 4 2 nil element))
    ))



;;; The grammar transformation function `reject-transfer-to-the-mouse-of' is to
;;; be called with the phrase that results from the grammar rules of the form
;;; action -> TRANSFER <item> TO <designation> ....  It should return bad phrase
;;; if the designation part of the phrase is actually going to be interpreted as
;;; a "TRANSFER TO THE MOUSE OF" action; otherwise, it just returns phrase.  See
;;; concept transfer-item-to-mouse.

;;; Phrase is assumed to be a list of at least three elements, the third of
;;; which is a list of at least two elements.  If the list that is third element
;;; of phrase has as its first and second THE and MOUSE, respectively, it is
;;; taken to be a transfer-to-the-mouse expression and rejected by virtue of
;;; this function returning bad-phrase.  Otherwise, phrase is simply returned.

(defun reject-transfer-to-the-mouse-of (phrase)
  (let ((destination (third phrase)))
    (if (and (consp destination)
	     (eq (first destination) 'the)
	     (eq (second destination) 'mouse))
	bad-phrase	
	phrase)))


;;; The function `validate-change-nth-element-parse' is used to verify the parse
;;; of the change-nth-element action.

;;; Validate only in two cases: when nth-element is the outermost designation
;;; and when it is the innermost designation.  The former is the new, correct
;;; parse.  The latter relates to version 3.0 code that should be allowed for
;;; this release, but causes a warning in the action compiler.  The warning says
;;; that the expression will be obsolete in a future release.

;;; Look for (the (nth-element item-or-datum) array-or-list index) OR
;;;          (quantififer role
;;;             (... (the (nth-element item-or-datum) array-or-list index)))

(defun validate-change-nth-element-parse (parse)
  ;; Validate the array-or-list designation parse.
  (if (validate-change-nth-element-parse-1 (second parse))
      parse
      (values bad-phrase 'change-nth-element-no-array-or-list)))

(declare-grammar-transform-can-return-bad-phrase validate-change-nth-element-parse)

(defun validate-change-nth-element-parse-1 (designation-parse)
  (cond
    ((or (null designation-parse) (not (listp designation-parse)))
     nil)
    (t
     (gensym-dstruct-bind
	 ((designation-quantifier? designation-role? designation-first-domain?
				   designation-second-domain?)
	  designation-parse)
       (cond
	 ((and (eq designation-quantifier? 'the)
	       (consp designation-role?)
	       (eq (car-of-cons designation-role?) 'nth-element)
	       designation-first-domain?
	       designation-second-domain?)
	  t)
					; Remove this COND clause when the
					; obsolete 3.0 grammar should no longer
					; be available or compile (sometime
					; after 4.0).  - cpm, 11/11/94
	 #+obsolete
	 ((and designation-first-domain?
	       (listp designation-first-domain?))
	  (validate-change-nth-element-parse-1 designation-first-domain?))
	 (t nil))))))


;; If changes are made to the following grammar, there is some specialized code
;; in compile2 that must be kept up to date.  See
;; compile1-create-connection-spec and friends. -dkuznick, 5/4/00

(add-grammar-rules 
  '(;; "a-or-an" in the following four rules used to be 'a, but that was too
    ;; cute; when users selected "a" they would get a subset of the grammar
    ;; they would have gotten if they had selected "an", since the other rules
    ;; contribute additional grammar (for ACTION, following CREATE) that can
    ;; begin with "an". (MHD 1/11/91)
    (action ('create a-or-an 'connection connection-creation-specifier)
	    (create-connection 'connection 4))

    (action ('create a-or-an 'connection local-name connection-creation-specifier)
            (create-connection 'connection 5 4))

    (action ('create a-or-an 'connection 
	     connection-class-specifier connection-creation-specifier)
	    (create-connection 4 5))

    (action ('create a-or-an 'connection local-name 
	     connection-class-specifier connection-creation-specifier)
	    (create-connection 5 6 4))

    (action ('delete e-designation 'removing 'connection 'stubs)
	    (1 2 t nil))

    (action ('delete e-designation 'without 'permanence 'checks)
            (1 2 nil t))

    (action ('delete e-designation 'removing 'connection 'stubs
    	                           'without 'permanence 'checks)
            (1 2 t t))

    (action ('delete e-designation 'without 'permanence 'checks
                                   'removing'connection 'stubs)
            (1 2 t t))

    (connection-class-specifier
      ('of 'class connection-class) (quote 3))
    (connection-class-specifier
      ('of 'the 'class 'named 'by unique-expression) 6)

    (connection-creation-specifier
      ('connected 'between connection-end-specifier 
       'and connection-end-specifier)
      (connected-between 3 5))
    (connection-creation-specifier
      ('connected 'between connection-end-specifier 
       'and connection-end-specifier connection-details-specifiers)
      (connected-between 3 5 6))
    (connection-creation-specifier
      ('connected 'to connection-end-specifier)
      (connected-to 3))
    (connection-creation-specifier
      ('connected 'to connection-end-specifier connection-details-specifiers)
      (connected-to 3 4))

    (connection-details-specifiers 
      connection-details-specifiers-1 1 
      convert-connection-details-specifiers-to-canonical-form)

    (connection-details-specifiers-1 connection-details-specifier)
    (connection-details-specifiers-1
      (connection-details-specifier '\, connection-details-specifiers-1)
      (2 1 3) simplify-associative-operation)

    (connection-details-specifier connection-style-specifier)
    (connection-details-specifier connection-direction-specifier)
    (connection-details-specifier connection-vertices-specifier)

    (connection-style-specifier
      ('with 'style connection-style) (with-style (quote 3)))
    (connection-style-specifier
      ('with 'the 'style 'named 'by unique-expression) (with-style 6))

    (connection-direction-specifier
      ('with 'direction direction) (with-direction (quote 3)))
    (connection-direction-specifier
      ('with 'the 'direction 'named 'by unique-expression) (with-direction 6))

    (connection-vertices-specifier
      ('with 'vertices vertices-list) (with-vertices . 3) fix-line-list)
    (vertices-list integer (+ 1))
    (vertices-list (integer vertices-list-tail)  (+ 1 2) simplify-associative-operation)
    (vertices-list-tail integer)
    (vertices-list-tail (integer vertices-list-tail) (+ 1 2) simplify-associative-operation)

    (connection-vertices-specifier
      ('with 'the 'vertices 'given 'by unique-expression) (with-vertices 6))

    (connection-style 'diagonal)
    (connection-style 'orthogonal)

    (connection-end-specifier
      (end-object-specifier end-position-specifier)
      (1 2))
    (end-object-specifier unique-designation)
    (end-position-specifier
      ('at connection-port-specifier)
      (located-at nil nil 2))
    (end-position-specifier
      ('locating 'it 'at side-specifier position-specifier)
      (located-at 4 5))
    (end-position-specifier
      ('at connection-port-specifier
       'locating 'it 'at side-specifier position-specifier)
      (located-at 6 7 2))
    (end-position-specifier
      ('newly 'locating 'it 'at side-specifier position-specifier)
      (newly-located-at 5 6))
    (end-position-specifier
      ('newly 'locating 'it 'at side-specifier position-specifier
       'at connection-port-specifier)
      (newly-located-at 5 6 8))

    (connection-port-specifier port-name (quote 1))
    (connection-port-specifier 
      ('the 'port 'named 'by unique-expression) 5)

    (side-specifier edge (quote 1))
    (side-specifier
      ('the 'side 'named 'by unique-expression) 5)

    (position-specifier positive-integer)
    (position-specifier
      ('at 'the 'position 'given 'by unique-expression) 6)

    ))



(defun convert-connection-details-specifiers-to-canonical-form
       (connection-details-specifiers)
  (let ((canonical-form-for-details-specifiers
	  (phrase-list nil nil nil)))
    (if (eq (car connection-details-specifiers) '\,)
	(loop for connection-details-specifier
		  in (cdr connection-details-specifiers) do
	  (put-connection-details-specifier-into-canonical-form
	    connection-details-specifier
	    canonical-form-for-details-specifiers))
	(put-connection-details-specifier-into-canonical-form
	  connection-details-specifiers
	  canonical-form-for-details-specifiers))
    canonical-form-for-details-specifiers))

;; Canonical form for connection details specifiers is 
;; (<style-expression> <direction-expession> <vertices-expression>).



(defun connection-vertices-are-constant-list? (vertices)
  (and (consp vertices)
       (numberp (car vertices))))

(defun put-connection-details-specifier-into-canonical-form
       (connection-details-specifier canonical-form-for-details-specifiers)
  (case (car connection-details-specifier)
    (with-style
     (setf (first canonical-form-for-details-specifiers)
	   (second connection-details-specifier)))
    (with-direction
     (setf (second canonical-form-for-details-specifiers)
	   (second connection-details-specifier)))
    (with-vertices
     (setf (third canonical-form-for-details-specifiers)
	   (if (connection-vertices-are-constant-list?
		 (cdr connection-details-specifier))
	       (cdr connection-details-specifier)
	       (second connection-details-specifier))))))



;;; (add-grammar-rules '((color 'white) ... [ETC.] ...))

;(add-grammar-rules
;  `(,@(loop for color in all-colors
;	    collect `(color ',color))))



;;;; (add-grammar-rules '((metacolor 'transparent) ... [ETC.] ...))

;(add-grammar-rules
;  `(,@(loop for metacolor in all-metacolors
;	    collect `(metacolor ',metacolor))))



;; What's the difference between this and gensym-color-p?

(defun color-or-metacolor-p (candidate-color)
  (or (semi-open-category-p candidate-color '(color metacolor))
      (rgb-color-p candidate-color)))


;;; Filter-out-illegal-region-names is a transformation for the grammar
;;; rule (region unreserved-symbol) which prohibits colors, metacolors,
;;; and either of the symbols COPY or INHERITED.  The latter must be prohibited
;;; because they conflict with other grammar used in connection cross section
;;; pattern specifications in connection definitions.

(defun illegal-region-name-p (candidate-region-name)
  (or (eq candidate-region-name 'copy)
      (eq candidate-region-name 'inherited)
      (color-or-metacolor-p candidate-region-name)))

(defun filter-out-illegal-region-names (candidate-region-name)
  (case candidate-region-name
    (copy
     (values bad-phrase 'region-cannot-be-the-symbol-copy))
    (inherited
     (values bad-phrase 'region-cannot-be-the-symbol-inherited))
    (t
     (if (color-or-metacolor-p candidate-region-name)
	 (values bad-phrase 'region-cannot-be-a-color-or-metacolor)
	 candidate-region-name))))

(declare-grammar-transform-can-return-bad-phrase filter-out-illegal-region-names)

;; COPY will probably be able to be removed, since "copy inherited pattern" will
;; probably be removed from the grammar for specifying cross section patterns
;; in connection definitions.  Eventually. (MHD 9/1/89)



;;; Filter-out-illegal-color-names ... 

(defun filter-out-illegal-color-names (candidate-color-name)
  (case candidate-color-name
    (inherited
     (values bad-phrase 'color-cannot-be-the-symbol-inherited))
    (t candidate-color-name)))

(declare-grammar-transform-can-return-bad-phrase filter-out-illegal-color-names)





(defun fix-start-action (form)
  (gensym-dstruct-bind ((kind proc args fourth fifth sixth) form)
    (let* ((priority
	     (cond
	       ((and fourth (eq (car fourth) 'priority))
		(second fourth))
	       ((and fifth (eq (car fifth) 'priority))
		(second fifth))
	       ((and sixth (eq (car sixth) 'priority))
		(second sixth))
	       (t nil)))
	   (interval
	     (cond
	       ((and fourth (eq (car fourth) 'interval))
		(second fourth))
	       ((and fifth (eq (car fifth) 'interval))
		(second fifth))
	       ((and sixth (eq (car sixth) 'interval))
		(second sixth))
	       (t nil)))
	   (across
	     (cond
	       ((and fourth (eq (car fourth) 'across))
		(second fourth))
	       ((and fifth (eq (car fifth) 'across))
		(second fifth))
	       ((and sixth (eq (car sixth) 'across))
		(second sixth))
	       (t nil))))
      (case kind
	#+mtg2
	(spawn (phrase-list 'start proc args priority interval :faction))
	(start (phrase-list 'start proc args priority interval across))
	(t (phrase-list 'start-thread proc args priority interval across))))))




(defun fix-action-list (rule)
  (let* ((action-or-actions (third rule))
	 (action-or-symbol (first action-or-actions)))
    (cond
      ((eq action-or-symbol 'in-order))

      ((eq action-or-symbol 'and)
       (setf (first action-or-actions) 'simultaneously))

      (t (setf (third rule)
	       (phrase-list 'simultaneously action-or-actions))))

    rule))




;;; Fix-iqe examines the nth item in form (indexed from 0)
;;; and if it is a symbol, it is quoted.

(defun fix-iqe (form n)
  (let ((iqe (nth n form)))
    (if (symbolp iqe)
	(setf (nth n form) (phrase-list 'quote iqe))))
  form)



;;; Unlist-1 ((x) ...) --> (x ...)
(defun unlist-1 (form)
  (phrase-cons (caar form) (cdr form)))

;;; unlist-1-2 ((x) (y) ...) --> (x y ...)
(defun unlist-1-2 (form)
  (phrase-cons (caar form) (phrase-cons (caadr form) (cddr form))))

;;; car-2-1 ((x (y . z))) --> ((x y))
(defun car-2-1 (form)
  (phrase-list (phrase-list (caar form) (caadar form))))


(defun choose-is-or-= (expression)
  (cond ((memq (car expression) '(current-value-of value-of))
	 (unless (designation-p (second (second expression)))
	   (setf (first (second expression))
		 (if (eq (first (second expression)) 'is) '= '/=))))

	(t (unless (designation-p (second expression))
	     (setf (first expression)
		   (if (eq (first expression) 'is) '= '/=)))))
  expression)


#+unused
(defun fix-duration (action)
  (prog1 action
	 (loop for thing on action doing
	   (if (and (consp (car thing)) (eq (caar thing) 'duration))
	       (setf (second (car thing)) (car (second (car thing))))))))


(defun put-designation-in-qualifier (factor)
  (setf (second (cdr factor)) (car factor))
  (cdr factor))

(defun fuzzy-comparator-reparser (parsed-fuzzy)
  (setf (car parsed-fuzzy)
	(cdr (assq (car parsed-fuzzy)
		   '((= . fuzzy-=) (/= . fuzzy-not-=) (> . fuzzy->) (< . fuzzy-<)))))
  parsed-fuzzy)

#+unused
(defun no-duplicates-in-list (parse index)
  (let ((element (nth (- index 1) parse)))
    (if (duplicates-p (second element)) bad-phrase parse)))

;; Replaced with duplicates-p which is equivalent and better coded.
;(defun has-duplicates (list)
;  (and (not (null list))
;       (or (memq (car list) (cdr list)) (has-duplicates (cdr list)))))


(defun category-hack (invoke-action)
  (setf (second invoke-action)
	(phrase-cons 'category
		     (if (symbolp (second invoke-action))
			 (phrase-cons (second invoke-action) nil)
			 (cdr (second invoke-action)))))
  invoke-action)


(defun symbol-cannot-be-true-false-or-not (form)
  (if (not (memq (second (third form)) '(true false not)))
      form
      bad-phrase))

(declare-grammar-transform-can-return-bad-phrase symbol-cannot-be-true-false-or-not)


(defun check-ddd-dddd-format (message-expression)
  (if (memq (third message-expression) '(time-stamp seconds))
      message-expression
      (multiple-value-bind (left right)
	  (decode-format (third message-expression))
	(if (null left)
	    bad-phrase
	    (prog1 message-expression
		   (setf (first message-expression) 'fixed-format)
		   (setf (third message-expression) left)
		   (setf (cdddr message-expression)
			 (phrase-cons right nil)))))))

(declare-grammar-transform-can-return-bad-phrase check-ddd-dddd-format)



;;; Decode format, if given a symbol whose symbol-name is a string of upper or
;;; lower-case d's, a period, and another string of such d's, has as values two
;;; integers specifying the number of d's to the left and right of the period
;;; respectively. If the symbol is not of such a format, the value nil is returned.

(defun decode-format (symbol)
  (loop with left-count
	with  bad-char = nil
	with  format = (symbol-name-text-string symbol)
	with length = (text-string-length format)
	for index from 0 below length
	for char = (charw format index)		; not valid to use schar here! (MHD)
	unless (wide-character-member
		 char '(#.%\d #.%\D #.%\.))
	  do  (setq bad-char t)
	count (char=w char #.%\.) into tally
	when (char=w char #.%\.)
	  do (setq left-count index)
	finally 
	  (return (if (or bad-char (/= tally 1))
		      nil
		      (values left-count (-f length left-count 1))))))


;; Apparently no used!!

;(defun any-every (designation)
;  (if (and (consp designation)
;	   (eq (car designation) 'any)
;	   (consp (third designation))
;	   (eq (first (third designation)) 'every))
;      bad-phrase
;      designation))



(defun fix-in-order-action-list (form)
  (phrase-cons (first form) (cdr (second form))))



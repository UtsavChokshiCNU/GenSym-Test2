;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module STACK-ACTS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Jim Allard and Chris Morel 






;;;; Stack Actions




;;; This file implements actions for stack-eval.  These actions are executed
;;; using a new stack instruction, funcall-instruction.

;;; `Funcall-instruction' is the stack-instruction which executes funcalled-
;;; instructions.  It is similar to the funcall-evaluator instruction, but
;;; executes funcalled-instructions, such as actions, and uses a single type of
;;; function dispatch.

;;; `Funcalled-instructions' are executed out-of-line from the
;;; funcall-instruction.  The funcalled-instruction function is passed the
;;; top-of-stack pointer and local-stack, and must return the new top-of-stack.
;;; Any arguments and return values specific to the funcalled instruction are
;;; referenced through the local-stack as evaluation-values.

;;; Note that funcalled instructions are responsible for reclaiming evaluation
;;; values from the stack as necessary.  Values that do not need reclaiming are
;;; not cleared from the stack.  When calling stack-error or write-stack error,
;;; the stack arguments do not need to be reclaimed.  As long as the top of
;;; stack is correct and passed as an argument, the handler for stack-error will
;;; reclaim values from the stack as necessary.

;;; Note that many of the stack-actions do not type test their arguments.  In
;;; many cases, the type test code as already been executed.  See the code
;;; emitters for these actions in PROC-INST.


;;; WHEN ADDING NEW FUNCALLED-INSTRUCTIONS, CHECK THIS FILE AND STACK-EVAL FOR
;;; THE LAST INSTRUCTION NUMBER USED!




;;; Forward References

(declare-forward-references
  (write-list-in-chicago-style                function GRAMMAR6B)
  (show-or-hide                               function CONTROLS)
  (show-workspace                             function CONTROLS)
  (embedded-rule-p                            function CONTROLS)
  (g2-to-g2-data-interface-p-function         function G2DS)
  (create-explanation                   function QUERIES)
  (gsi-interface-p-function     function G2-GSI)
  (frame-may-be-rotated-or-reflected-p        function)	; commands0
  (transfer-item-to-mouse-of-window           function COMMANDS1)
  (insert-action-duplicate-element-backward-compatibility-p
                                              function GRAMMAR7)
  )

(declare-forward-reference make-button function)
(declare-forward-reference funcall-function-to-inferior-blocks function)


;; -- Notes --

;; Call error-if-simulation-procedure for actions other than SET that cannot be
;; executed in the simulator.

;; There will not be a separate printer for each action.  The printer for
;; funcalled-instruction will handle each action.

;; Review Actions module!!  Compare to procedure actions and update comments.

;; Changed numbers of funcalled-instructions (actions) to start at 0?



;; -- Notes on Error Messages --

;; Convert call to print-designation and (tformat "~ND ..." etc.) to  (tformat
;; "~a ..." (get-or-make-up-designation-for-block ...) or to (tformat "~NF ..."
;; etc.).

;; Check for user warning-messages "hidden" within functions or macros called
;; from the funcalled-instructions (actions), e.g.,
;; unique-attribute-of-class-with-potential-symbolic-value!!



;; -- Special Forms --


;; Invoke, Change-Item-Color-Pattern, Show, Hide, Inform, Nupec-Synchronize,
;; Create Connection.






;;;; Procedure Actions Not Implemented




;;; CONCLUDE-NOT, procedure-instruction 31.  Calls to this action
;;; should be compiled into the conclude action with a false value.

;;; EDIT, procedure-instruction 48.  This was a test and was never
;;; part of G2.  It is replaced by change-the-text-of-attribute.





;;;; Stack Actions Funcalled Instruction Pprinters




;;; The pprinter `pprint-conclude-action' prints the conclude action except for
;;; any expiration or collection time arguments.

;;; "conclude that <item> = <value>
;;;   args: item, datum, expiration?, collection?

(defun pprint-conclude-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (let* ((stack-args-ok? (=f top-of-stack cached-top-of-stack))
	 (expiration? (and stack-args-ok?
			   (svref stack (-f top-of-stack 1))))
	 (collection? (and stack-args-ok?
			   (svref stack top-of-stack))))
    (twrite-string "conclude that ")
    (write-stack-argument 1 4 stack top-of-stack)
    (twrite-string " = ")
    (write-stack-argument 2 4 stack top-of-stack)
    (when (or expiration? collection?)
      (twrite-string " with expiration ")
      (if (and expiration? (evaluation-quantity-p expiration?))
	  (print-constant
	    (evaluation-quantity-value expiration?) 'time-stamp)
	  (write-stack-argument 3 4 stack top-of-stack))
      (twrite-string " with collection time ")
      (if (and collection? (evaluation-quantity-p collection?))
	  (print-constant
	    (evaluation-quantity-value collection?) 'time-stamp)
	  (write-stack-argument 4 4 stack top-of-stack)))))

;;; The pprinter `pprint-compare-and-swap-action' prints the CAS-conclude action.

;;; "conclude that <item> = <value> compare <old>
;;;   args: item, datum, old-value?

(defun pprint-compare-and-swap-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (let* ((stack-args-ok? (=f top-of-stack cached-top-of-stack))
         (old-value? (and stack-args-ok?
                          (svref stack top-of-stack))))
    (twrite-string "conclude that ")
    (write-stack-argument 1 3 stack top-of-stack)
    (twrite-string " = ")
    (write-stack-argument 2 3 stack top-of-stack)
    (when old-value?
      (twrite-string " compare ")
      (write-stack-argument 3 3 stack top-of-stack))))



;;; The pprinter `pprint-conclude-attribute-action' prints the conclude
;;; attribute action.

;;; "conclude that the [<class-qualifier>::]<attribute-name> of <item> = <value>
;;;   args: class-qualifier?, attribute-name, item, datum

(defun pprint-conclude-attribute-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (let* ((stack-args-ok? (=f top-of-stack cached-top-of-stack))
	 (class-qualifier? (if stack-args-ok?
			       (svref stack (-f top-of-stack 3))
			       nil)))
    (twrite-string "conclude that the ")
    (when class-qualifier?
      (twrite-symbol class-qualifier?)
      (twrite-string "::"))
    (write-stack-argument 2 4 stack top-of-stack)
    (twrite-string " of ")
    (write-stack-argument 3 4 stack top-of-stack)
    (twrite-string " = ")
    (write-stack-argument 4 4 stack top-of-stack)))


;;; "move <item> by (<x>, <y>)"

(defun pprint-move-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "move ")
  (write-stack-argument 1 3 stack top-of-stack)
  (twrite-string " by (")
  (write-stack-argument 2 3 stack top-of-stack)
  (twrite-string ", ")
  (write-stack-argument 2 3 stack top-of-stack)
  (twrite-character #.%\)))


;;; "move <item> to (<x>, <y>)"

(defun pprint-set-position-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "move ")
  (write-stack-argument 1 3 stack top-of-stack)
  (twrite-string " to (")
  (write-stack-argument 2 3 stack top-of-stack)
  (twrite-string ", ")
  (write-stack-argument 2 3 stack top-of-stack)
  (twrite-character #.%\)))


;;; "rotate <item> by <degrees>"

(defun pprint-rotate-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "rotate ")
  (write-stack-argument 1 2 stack top-of-stack)
  (twrite-string " by ")
  (write-stack-argument 2 2 stack top-of-stack)
  (twrite-string " degrees"))


;;; "rotate <item> to the heading <degrees>"

(defun pprint-set-heading-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "rotate ")
  (write-stack-argument 1 2 stack top-of-stack)
  (twrite-string " to the heading ")
  (write-stack-argument 2 2 stack top-of-stack)
  (twrite-string " degrees"))


;;; "conclude that <item> has no current value"

(defun pprint-conclude-has-no-current-value-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "conclude that ")
  (write-stack-argument 1 1 stack top-of-stack)
  (twrite-string " has no current value"))


;;; "conclude that <item> has no value"

(defun pprint-conclude-has-no-value-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "conclude that ")
  (write-stack-argument 1 1 stack top-of-stack)
  (twrite-string " has no value"))


;;; "focus on <item>"

(defun pprint-focus-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "focus on ")
  (write-stack-argument 1 1 stack top-of-stack))


;;; "focus on <item>, awaiting completion"

(defun pprint-focus-with-wait-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "focus on ")
  (write-stack-argument 1 1 stack top-of-stack)
  (twrite-string ", awaiting completion"))


;;; "change the <color-attribute> of <item> to <color-expression>"
;;;   args: item, color, region

(defun pprint-change-item-color-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "change the ")
  (write-stack-argument 3 3 stack top-of-stack)
  (twrite-string " of ")
  (write-stack-argument 1 3 stack top-of-stack)
  (twrite-string " to ")
  (write-stack-argument 2 3 stack top-of-stack))


;;; "change the color-pattern of <item> so that <color-attribute> =
;;; <color-expression> [, <color-attribute> = <color-expression>]

;;;   args: item {color-pattern-component} arg-count

(defun pprint-change-item-color-pattern-action
       (description pc byte-code-body constant-vector stack top-of-stack arg-count result-count)
  (declare (ignore description pc byte-code-body constant-vector result-count))
  (cond
    ((=f top-of-stack cached-top-of-stack)
     (let ((color-arg-count-plus-one arg-count))
       (twrite-string "change the color-pattern of ")
       (write-stack-argument
	 1 color-arg-count-plus-one stack top-of-stack)
       (twrite-string " to ")
       (loop for index from 2 below color-arg-count-plus-one
	     for first-loop-iteration? = t then nil
	     do
	 (unless first-loop-iteration?
	   (twrite-string ", "))
	 (write-stack-argument index color-arg-count-plus-one stack top-of-stack)
	 (twrite-string " = ")
	 (incff index)
	 (write-stack-argument
	   index color-arg-count-plus-one stack top-of-stack))))
    (t
     (twrite-string "change the color-pattern of <arguments unavailable>"))))


;;; The pprinter `pprint-hide-action' writes the hide action except for the
;;; window argument which may be nil.

;;; "hide <item> [on <window>]"
;;;   args: item, window?

(defun pprint-hide-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "hide ")
  (write-stack-argument 1 2 stack top-of-stack)
  (twrite-string " on ")
  (write-stack-argument 2 2 stack top-of-stack))


;;; "activate <item>"

(defun pprint-activate-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "activate the subworkspace of ")
  (write-stack-argument 1 1 stack top-of-stack))


;;; "deactivate <item>"

(defun pprint-deactivate-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "deactivate the subworkspace of ")
  (write-stack-argument 1 1 stack top-of-stack))


;;; "set <item> to <value>"
;;;   args: place, datum

(defun pprint-set-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "set ")
  (write-stack-argument 1 2 stack top-of-stack)
  (twrite-string " to ")
  (write-stack-argument 2 2 stack top-of-stack))


;;; The function `pprint-inform-action' pprints the inform action with only the
;;; message text and not the other arguments.  These other arguments, including
;;; destination-or-operator, may be nil.

;;; "inform <message>"
;;;   6 args: destination?, message, duration?, on-workspace?, below-item?,
;;;   above-item?

(defun pprint-inform-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (cond
    ((=f top-of-stack cached-top-of-stack)
     (let ((destination? (svref stack (-f top-of-stack 5)))
	   (duration? (svref stack (-f top-of-stack 3))))
       (twrite-string "inform ")
       (cond ((null destination?)
	      (twrite-string "the operator"))
	     (t
	      (write-stored-value destination?)))
       (twrite-string " on ")
       (write-stack-argument 4 6 stack top-of-stack)
       (twrite-string " below ")
       (write-stack-argument 5 6 stack top-of-stack)
       (twrite-string " above ")
       (write-stack-argument 6 6 stack top-of-stack)
       (twrite-string " for the next ")
       (if (and duration? (evaluation-quantity-p duration?))
	   (print-constant
	     (evaluation-quantity-value duration?) 'seconds)
	   (write-stack-argument 3 6 stack top-of-stack))
       (twrite-string " that ")
       (write-stack-argument 2 6 stack top-of-stack)))
    (t
     (twrite-string "inform <arguments unavailable>"))))


;;; The function `pprint-add-relation-action' pprints the add-relation action
;;; without the now-case? argument.

;;; "conclude that <item> is <relation> <item>"
;;;   args: relation-name, item, item, now-case?

(defun pprint-add-relation-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (cond
    ((=f top-of-stack cached-top-of-stack)
     (let ((now-case (svref stack top-of-stack)))
       (twrite-string "conclude that ")
       (write-stack-argument 2 4 stack top-of-stack)
       (cond
	 ((as-true-as (evaluation-truth-value-value now-case) truth)
	  (twrite-string " is now "))
	 (t
	  (twrite-string " is ")))
       (write-stack-argument 1 4 stack top-of-stack)
       (twrite-character #.%space)
       (write-stack-argument 3 4 stack top-of-stack)))
    (t
     (twrite-string "conclude relation <arguments unavailable>"))))
    


;;; "conclude that <item> is not <relation> <item>"
;;;   args: relation-name, item, item

(defun pprint-remove-relation-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "conclude that ")
  (write-stack-argument 2 3 stack top-of-stack)
  (twrite-string " is not ")
  (write-stack-argument 1 3 stack top-of-stack)
  (twrite-character #.%space)
  (write-stack-argument 3 3 stack top-of-stack))


;;; The function `pprint-create-action' pprints the create action without any
;;; local-name, and does not print in the "class named by <expression> format.
;;; The instruction to handle the local-name is emitted separately from this
;;; action.

;;; "create a(n) <class>"

(defun pprint-create-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "create a(n) ")
  (write-stack-argument 1 1 stack top-of-stack))


;;; "delete <item>"
;;;   args: item, delete-connections-without-leaving-stubs?

(defun pprint-delete-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "delete ")
  (write-stack-argument 1 2 stack top-of-stack))


;;; The function `pprint-transfer-action' pprints the transfer action except for
;;; the workspace, x, and y arguments which can be nil.

;;; "transfer <item> {off | to <workspace> at (<x>, <y>)}"
;;;   args: transient-item, workspace?, x?, y?

(defun pprint-transfer-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (cond
    ((=f top-of-stack cached-top-of-stack)
     (let ((workspace? (svref stack (-f top-of-stack 2))))
       (twrite-string "transfer ")
       (write-stack-argument 1 4 stack top-of-stack)
       (cond ((null workspace?)
	      (twrite-string " off"))
	     (t
	      (twrite-string " to ")
	      (write-stack-argument 2 4 stack top-of-stack)
	      (twrite-string " at (")
	      (write-stack-argument 3 4 stack top-of-stack)
	      (twrite-string ", ")
	      (write-stack-argument 4 4 stack top-of-stack)
	      (twrite-character #.%\))))))
    (t
     (twrite-string "transfer <arguments unavailable>"))))


;;; "change the <system-attribute> of <item> to <value>"
;;;   args: item, name-of-attribute, value

(defun pprint-change-system-attribute-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "change the ")
  (write-stack-argument 2 3 stack top-of-stack)
  (twrite-string " of ")
  (write-stack-argument 1 3 stack top-of-stack)
  (twrite-string " to ")
  (write-stack-argument 3 3 stack top-of-stack))


;;; "change the text of the <attribute> of <item> to <value>"
;;;   args: item-or-place, value

(defun pprint-change-the-text-of-attribute-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "change the text of ")
  (write-stack-argument 1 2 stack top-of-stack)
  (twrite-string " to ")
  (write-stack-argument 2 2 stack top-of-stack))


;;; "change <item> [<integer>] = <value>"
;;;   args: item, element, index

(defun pprint-change-nth-element-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "change ")
  (write-stack-argument 1 3 stack top-of-stack)
  (twrite-string " [")
  (write-stack-argument 3 3 stack top-of-stack)
  (twrite-string "] = ")
  (write-stack-argument 2 3 stack top-of-stack))


;;; "insert <item-or-value> in the <element-type> <list>"
;;;   5 args: g2-list, element-type, new-element, insertion-type,
;;;   existing-element?

(defun pprint-g2-list-insert-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (let* ((stack-args-ok? (=f top-of-stack cached-top-of-stack))
	 (element-type? (and stack-args-ok? (svref stack (-f top-of-stack 3)))))
    (cond (stack-args-ok?
	   (let ((insert-type (svref stack (-f top-of-stack 1))))
	     (setq insert-type (evaluation-symbol-symbol insert-type))
	     (twrite-string "insert ")
	     (write-stack-argument 3 5 stack top-of-stack)
	     (case insert-type
	       (beginning
		(twrite-string " at the beginning of"))
	       (end
		(twrite-string " at the end of"))
	       (before
		(twrite-string " before ")
		(write-stack-argument 5 5 stack top-of-stack)
		(twrite-string " in"))
	       (after
		(twrite-string " after ")
		(write-stack-argument 5 5 stack top-of-stack)
		(twrite-string " in"))
	       (t
		(twrite-string " in")))
	     (twrite-string " the ")
	     (tformat "~NT" element-type?)
	     (twrite-string " list ")
	     (write-stack-argument 1 5 stack top-of-stack)))
	  (t
	   (twrite-string "insert ")
	   (write-stack-argument 3 5 stack top-of-stack)
	   (twrite-string " in ")
	   (write-stack-argument 1 5 stack top-of-stack)))))


;;; "insert <item-or-value> in <list>"
;;;   4 args: g2-list, new-element, insertion-type, existing-element?

(defun pprint-g2-list-insert-item-or-value-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (cond ((=f top-of-stack cached-top-of-stack)
	 (let ((insert-type (svref stack (-f top-of-stack 1))))
	   (setq insert-type (evaluation-symbol-symbol insert-type))
	   (twrite-string "insert ")
	   (write-stack-argument 2 4 stack top-of-stack)
	   (case insert-type
	     (beginning
	      (twrite-string " at the beginning of"))
	     (end
	      (twrite-string " at the end of"))
	     (before
	      (twrite-string " before ")
	      (write-stack-argument 4 4 stack top-of-stack)
	      (twrite-string " in"))
	     (after
	      (twrite-string " after ")
	      (write-stack-argument 4 4 stack top-of-stack)
	      (twrite-string " in "))
	     (t
	      (twrite-string " in ")))
	   (write-stack-argument 1 4 stack top-of-stack)))
	(t
	 (twrite-string "insert ")
	 (write-stack-argument 2 4 stack top-of-stack)
	 (twrite-string " in ")
	 (write-stack-argument 1 4 stack top-of-stack))))


;;; "remove <item-or-value> from the <element-type> <list>"
;;; "remove the {first | last} <element-type> from <list>"
;;;   4 args: g2-list, required-element-type, removal-type, element?

(defun pprint-g2-list-remove-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (let* ((stack-args-ok? (=f top-of-stack cached-top-of-stack)))
    (cond (stack-args-ok?
	   (let ((removal-type-arg (svref stack (-f top-of-stack 1)))
		 (element-type?
		   (and stack-args-ok? (svref stack (-f top-of-stack 2)))))
	     (setq removal-type-arg
		   (if (evaluation-symbol-p removal-type-arg)
		       (evaluation-symbol-symbol removal-type-arg)
		       removal-type-arg))
	     (twrite-string "remove ")
	     (case removal-type-arg
	       (first
		(twrite-string "the first ")
		(tformat "~NT" element-type?)
		(twrite-string " from ")
		(write-stack-argument 1 4 stack top-of-stack))
	       (last
		(twrite-string "the last ")
		(tformat "~NT" element-type?)
		(twrite-string " from ")
		(write-stack-argument 1 4 stack top-of-stack))
	       (element
		(write-stack-argument 4 4 stack top-of-stack)
		(twrite-string " from the ")
		(tformat "~NT" element-type?)
		(twrite-string " list ")
		(write-stack-argument 1 4 stack top-of-stack)))))
	  (t
	   (twrite-string "remove ")
	   (write-stack-argument 4 4 stack top-of-stack)
	   (twrite-string " from ")
	   (write-stack-argument 1 4 stack top-of-stack)))))


;;; "REMOVE <item-or-value> FROM <list>" and
;;; "REMOVE THE {FIRST | LAST} <element-type> FROM <list>"
;;;   4 args: g2-list, element?, required-element-type?, removal-type

;;; The new g2-list-remove action needs a separate writer because the order of
;;; the arguments and the grammar have changed.

(defun pprint-g2-list-remove-item-or-value-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (let ((stack-args-ok? (=f top-of-stack cached-top-of-stack)))
    (cond (stack-args-ok?
	   (let ((removal-type-arg (svref stack top-of-stack))
		 (element-type?
		   (and stack-args-ok? (svref stack (-f top-of-stack 1)))))
	     (setq removal-type-arg
		   (if (evaluation-symbol-p removal-type-arg)
		       (evaluation-symbol-symbol removal-type-arg)
		       removal-type-arg))
	     (twrite-string "remove ")
	     (case removal-type-arg
	       (first
		(twrite-string "the first ")
		(tformat "~NT" element-type?)
		(twrite-string " from ")
		(write-stack-argument 1 4 stack top-of-stack))
	       (last
		(twrite-string "the last ")
		(tformat "~NT" element-type?)
		(twrite-string " from ")
		(write-stack-argument 1 4 stack top-of-stack))
	       (element
		(write-stack-argument 2 4 stack top-of-stack)
		(twrite-string " from ")
		(write-stack-argument 1 4 stack top-of-stack)))))
	  (t
	   (twrite-string "remove ")
	   (write-stack-argument 2 4 stack top-of-stack)
	   (twrite-string " from ")
	   (write-stack-argument 1 4 stack top-of-stack)))))


;;; "create an explanation for <v-or-p>"

(defun pprint-create-explanation-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "create an explanation for ")
  (write-stack-argument 1 1 stack top-of-stack))


;;; "update <display>"

(defun pprint-update-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "update ")
  (write-stack-argument 1 1 stack top-of-stack))


;;; "start <procedure> (<argument>, ...) [at priority <integer>] [after
;;; <interval>]
;;;   args: procedure, arguments, ..., argument-count, priority?, wait?

(defun pprint-start-action
       (description pc byte-code-body constant-vector stack top-of-stack arg-count result-count)
  (declare (ignore description pc byte-code-body constant-vector result-count))
  (cond
    ((=f top-of-stack cached-top-of-stack)
     (let ((wait? (svref stack top-of-stack))
	   (priority? (svref stack (-f top-of-stack 1)))
	   (proc-arg-count (-f arg-count 3))
	   (stack-arg-count arg-count))
       (twrite-string "start ")
       (write-stack-argument 1 stack-arg-count stack top-of-stack)
       (twrite-string " (")
       (loop with last-proc-arg-index = (+f proc-arg-count 1)
	     for stack-index from 2 to last-proc-arg-index
	     for first-proc-arg? = t then nil
	     do
	 (unless first-proc-arg?
	   (twrite-string ", "))
	 (write-stack-argument
	   stack-index stack-arg-count stack top-of-stack))
       (twrite-character #.%\))
       (twrite-string " at priority ")
       (write-stored-value priority?)
       (twrite-string " after ")
       (if (and wait? (evaluation-quantity-p wait?))
	   (print-constant
	     (evaluation-quantity-value wait?) 'seconds)
	   (write-stored-value wait?))))
    (t
     (twrite-string "start <arguments unavailable>"))))


;;; "start <procedure> (<argument>, ...) [at priority <integer>] [after
;;; <interval>] across <g2-to-g2-interface>

;;;   args: remote-procedure, arguments, ..., argument-count, priority?, wait?,
;;;   icp-interface

(defun pprint-start-rpc-action
       (description pc byte-code-body constant-vector stack top-of-stack arg-count result-count)
  (declare (ignore description pc byte-code-body constant-vector result-count))
  (cond
    ((=f top-of-stack cached-top-of-stack)
     (let ((icp-interface (svref stack top-of-stack))
	   (wait? (svref stack (-f top-of-stack 1)))
	   (priority? (svref stack (-f top-of-stack 2)))
	   (proc-arg-count (-f arg-count 4))
	   (stack-arg-count arg-count))
       (twrite-string "start ")
       (write-stack-argument 1 stack-arg-count stack top-of-stack)
       (twrite-string " (")
       (loop with last-proc-arg-index = (+f proc-arg-count 1)
	     for stack-index from 2 to last-proc-arg-index
	     for first-proc-arg? = t then nil
	     do
	 (unless first-proc-arg?
	   (twrite-string ", "))
	 (write-stack-argument
	   stack-index stack-arg-count stack top-of-stack))
       (twrite-character #.%\))
       (twrite-string " at priority ")
       (write-stored-value priority?)
       (twrite-string " after ")
       (if (and wait? (evaluation-quantity-p wait?))
	   (print-constant
	     (evaluation-quantity-value wait?) 'seconds)
	   (write-stored-value wait?))
       (twrite-string " across ")
       (write-stored-value icp-interface)))
    (t
     (twrite-string "start across <arguments unavailable>"))))


(defun pprint-call-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (cond
    ((=f top-of-stack cached-top-of-stack)
     (let ((proc-arg-count (svref stack top-of-stack))
	   (stack-arg-count (svref stack (-f top-of-stack 1))))
       (setq proc-arg-count (evaluation-integer-value proc-arg-count))
       (setq stack-arg-count (+f proc-arg-count 4))
       (twrite-string "call ")
       (write-stack-argument 1 stack-arg-count stack top-of-stack)
       (twrite-string " (")
       (loop for stack-index = 2 then (+f stack-index 1)
	     with last-proc-arg-index = (+f proc-arg-count 1)
	     with first-proc-arg? = t
	     until (>f stack-index last-proc-arg-index)
	     do
	 (cond (first-proc-arg?
		(setq first-proc-arg? nil))
	       (t
		(twrite-string ", ")))
	 (write-stack-argument
	   stack-index stack-arg-count stack top-of-stack))
       (twrite-character #.%\))))
    (t
     (twrite-string "call <arguments unavailable>"))))

;;; "abort <procedure-or-procedure-invocation>"

(defun pprint-abort-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "abort ")
  (write-stack-argument 1 1 stack top-of-stack))


;;; "shut down g2"

(defun pprint-shut-down-g2-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare
    (ignore description pc byte-code-body stack top-of-stack constant-vector))
  (twrite-string "shut down g2"))


;;; The function `pprint-create-by-cloning-action' pprints the create by cloning
;;; action without any local-name.  The instruction to handle the local-name is
;;; emitted separately from this action.

;;; "create a(n) <class> by cloning <item>"

(defun pprint-create-by-cloning-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "create a(n) ")
  (write-stack-argument 1 1 stack top-of-stack)
  (twrite-string " by cloning ")
  (write-stack-argument 1 2 stack top-of-stack))


;;; "make <item> permanent"

(defun pprint-make-permanent-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "make ")
  (write-stack-argument 1 1 stack top-of-stack)
  (twrite-string " permanent"))


;;; "make <workspace> a subworkspace of <item>"

(defun pprint-make-subworkspace-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "make ")
  (write-stack-argument 1 2 stack top-of-stack)
  (twrite-string " a subworkspace of ")
  (write-stack-argument 2 2 stack top-of-stack))


;;; "print <workspace>"

(defun pprint-print-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "print ")
  (write-stack-argument 1 1 stack top-of-stack))


;;; "make <item> transient"

(defun pprint-make-transient-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "make ")
  (write-stack-argument 1 1 stack top-of-stack)
  (twrite-string " transient"))


;;

;;; "start kb"

(defun pprint-start-kb-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare
    (ignore description pc byte-code-body stack top-of-stack constant-vector))
  (twrite-string "start kb"))

;;; "resume kb"

(defun pprint-resume-kb-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare
    (ignore description pc byte-code-body stack top-of-stack constant-vector))
  (twrite-string "resume kb"))

;;; "enable <item>"

(defun pprint-enable-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "enable")
  (write-stack-argument 1 1 stack top-of-stack))
 

;;; "disable <item>"

(defun pprint-disable-action
       (description pc byte-code-body constant-vector stack top-of-stack)
  (declare (ignore description pc byte-code-body constant-vector))
  (twrite-string "disable")
  (write-stack-argument 1 1 stack top-of-stack))


;;;; Funcalled-Instructions




;;; Instruction 0, the `CONCLUDE funcalled stack-instruction' takes as
;;; stack-arguments an object, datum, expiration time, and a collection time.
;;; The instruction performs a conclude action on the variable or parameter.

;;; The expiration and collection time arguments should be NIL if these values
;;; were not provided by the user.  The datum arg, if not specified by the user,
;;; has been compiled as true.

;;; If the datum arg is not a symbol, then an attempt is made to put the value
;;; into the object which must be a variable or parameter.  If, however, the
;;; datum is a symbol, then the following occurs.

;; Old Documentation For Concluding A Symbolic Value (no longer correct):
;;
;; If, however, the datum is a symbol, then there are two cases.
;;
;; In the first case, the value of the evaluation results in a list of symbols.
;; Such a case is handled exactly as in the forementioned case of a non
;; symbolic value.
;;
;; The second case has two possibilities.  If the item is a variable or a
;; constant, then it is treated as above.  However, if the designation denotes
;; an entity which is not a variable, then an attempt is made to find an
;; implied attribute, a unique attribute of the entity of which the value is in
;; the range of possible values for the attribute.  If it is found then the
;; variable or constant denoted by that attribute of the entity is used as the
;; location into which the value is attempted to be put.  If no such unique
;; attribute is found, the attempt is abandonded and a frame note concerning
;; the matter is posted on the rule which attempted the action.

;;; The above documentation was not correct in non-stack or stack rule or
;;; procedure actions.  When the value is a symbol, the action always checked
;;; for an implied attribute.  If an implied attribute was found which was not a
;;; variable or parameter, the conclude was not made even if the original object
;;; was a variable or parameter!  Now, in this case, the conclude is made into
;;; the original variable or parameter.  There are still some questions.  Should
;;; we even check for an implied attribute if the item is a variable or
;;; parameter?  What if both the parent object and an implied attribute are
;;; suitable to receive the new value??  cpm, 4/11/91

;;; When a value cannot be concluded, a warning is issued instead of a frame not
;;; being posted.

;;; Note that the default expiration, if not supplied by the action, is the
;;; binding of stack-expiration.  Stack-expiration should be either the minimum
;;; of the expression expiration and the antecedent expiration or the default
;;; expiration for procedures (which was 'never in non-stack version).  This
;;; does not override any existing validity interval.

;; Was procedure-instruction 30.

;;; COMPILER NOTES:

;;; 1.  There is now only one CONCLUDE action instruction.  All calls
;;; to conclude, including "conclude that x" and "conclude that not x", should
;;; use this instruction.  An exception is concluding that a place does not have
;;; a value or a current value.

;;; 2.  A nil datum value compiles into true for conclude and false for
;;; conclude-not.

;;; FUNCTIONALITY CHANGE:
;;; 1. If an implied attribute is found that is not a
;;; variable or parameter, then a conclude is made into the original item if it
;;; is a variable or parameter.  See above comments.
;;; 2. The rule non-stack action wrote trace messages.
;;; 3.  PUT-CURRENT-VALUE RETURN VALUE is now tested for an error condition.  It
;;; the expiration return value is nil, an error has occurred an a
;;; warning-message has been displayed.  Put-current-value and
;;; put-new-value-if-compatible issue level 1 and 3 warnings for inactive
;;; object, validity interval not supplied, and type not compatible.
;;; Previously, this value was not tested.  Now a warning-message is displayed
;;; and then a stack-error is signaled.
;;; This should be modified to call stack-error directly with the error message
;;; and not displaying the message separately!!  cpm, 5/15/91

;;; Can now conclude constants into user-defined attributes.

;;; Can now conclude values into datum-arrays and datum-lists.

;;;   CONCLUDE (item datum expiration? collection?)

(def-funcalled-instruction conclude (0 (inference procedure) 4 0 nil
				       pprint-conclude-action)
  (let ((item-or-place-reference (stack-arg 0))
	(value-arg (stack-arg 1))
	(expiration-arg (stack-arg 2))
	(collection-arg (stack-arg 3)))
    (if (evaluation-place-reference-p item-or-place-reference)
	(let* ((component-particulars
		 (evaluation-place-reference-component-particulars
		   item-or-place-reference))
	       (item (evaluation-place-reference-block-or-symbol
		       item-or-place-reference)))
	  (unless (evaluation-place-reference-valid-p item-or-place-reference)
	    (stack-error
	      top-of-stack "Cannot conclude a value into ~NV."
	      item-or-place-reference))

	  (let ((error-message?
		  (conclude-into-component-dispatch
		    item component-particulars value-arg nil
		    component-particulars)))
	    (when error-message?
	      (if (text-string-p error-message?)
		  (write-stack-error top-of-stack
		    (twrite-string error-message?)
		    (reclaim-text-string error-message?))
		  (stack-error top-of-stack "Failed to conclude."))))
	  (reclaim-evaluation-place-reference item-or-place-reference))
	
	(let* ((item item-or-place-reference)
	       (value-arg (stack-arg 1))
	       (user-provided-expiration?
		 (if expiration-arg
		     (evaluation-value-value expiration-arg)))
	       (user-provided-collection?
		 (if collection-arg
		     (evaluation-value-value collection-arg)))
	       (place? (if (evaluation-symbol-p value-arg)
			   (get-implied-attribute-place
			     item (evaluation-symbol-symbol value-arg)
			     top-of-stack)
			   item))
	       (parameter? (if place? (parameter-p place?))))
	  (when user-provided-collection?
	    (setq user-provided-collection?
		  (if (fixnump user-provided-collection?)
		      (convert-gensym-time-to-unix-time
			(+f (clock-get gensym-time-at-start) user-provided-collection?))
		      (+e user-provided-collection?
			  (managed-float-value (clock-get g2-time-at-start))))))
	  (when (and user-provided-expiration? (not parameter?))
	    (setq user-provided-expiration?
                  (+f (clock-get gensym-time-at-start)
                      (if (fixnump user-provided-expiration?)
                          user-provided-expiration?
                          (g2-round user-provided-expiration?))))

	    ;; The arguments to put-current-value are still in gensym-time format.

	    ;; jh, 11/11/94.  From what I can tell, the above explanation as to why the
	    ;; following form is commented out is out-of-date.  In other words,
	    ;; put-current-evaluation-value, the successor to put-current-value, now accepts
	    ;; arguments in g2-time format in addition to gensym-time format, as long as the
	    ;; former is a float and the latter is a fixnum.  So it should be OK to comment
	    ;; in the following user-provided-expiration? in a manner analogous to the new
	    ;; user-provided-collection? form above (i.e., put it in a non-fixnum branch).
	    ;; I leave this task to the actual owners of this code, though; I had to fix
	    ;; user-provided-collection?  to make object-passing work, and that is the
	    ;; extent of my expertise for now.
	    
	    ;;(setq user-provided-expiration?
	    ;;      (+ (evaluation-float-value g2-time-at-start)
	    ;;         user-provided-expiration?))
	    )
	  (cond
	    ((null place?)
	     ;; Missing implied attribute error.
	     (stack-error
	       top-of-stack
	       "While executing a CONCLUDE action, could not locate a variable ~
                or parameter attribute of ~NF which has ~NV in its range of ~
                possible values."
	       item value-arg))
	    ((and (not parameter?)
		  (not (variable-or-parameter-p place?)))
	     (stack-error
	       top-of-stack
	       "Cannot conclude a value for ~NF, since it is not a variable or ~
                parameter."
	       place?))
	    (t
	     (let ((problem-description?
		    (put-current-evaluation-value
		      place? value-arg
		      (or user-provided-expiration? stack-expiration)
		      user-provided-collection?
		      (not (null user-provided-expiration?)))))
	       (when problem-description?
		 (signal-conclude-problem top-of-stack problem-description?)))))))
    (reclaim-if-evaluation-value expiration-arg)
    (reclaim-if-evaluation-value collection-arg)
    nil))

(def-funcalled-instruction compare-and-swap (83 (inference procedure) 4 1 nil
				       pprint-compare-and-swap-action)
  (let ((item-or-place-reference (stack-arg 1))
	(value-arg (stack-arg 2))
        (old-value-arg (stack-arg 3)))
    (if (evaluation-place-reference-p item-or-place-reference)
	(let* ((component-particulars
		 (evaluation-place-reference-component-particulars
		   item-or-place-reference))
	       (item (evaluation-place-reference-block-or-symbol
		       item-or-place-reference)))
	  (unless (evaluation-place-reference-valid-p item-or-place-reference)
	    (stack-error
	      top-of-stack "Cannot conclude a value into ~NV."
	      item-or-place-reference))

	  (let ((error-message?
		  (conclude-into-component-dispatch
		    item component-particulars value-arg nil
		    component-particulars)))
	    (when error-message?
	      (if (text-string-p error-message?)
		  (write-stack-error top-of-stack
		    (twrite-string error-message?)
		    (reclaim-text-string error-message?))
		  (stack-error top-of-stack "Failed to conclude."))))
	  (reclaim-evaluation-place-reference item-or-place-reference))
        (let* ((item item-or-place-reference)
	       (place? (if (evaluation-symbol-p value-arg)
			   (get-implied-attribute-place
			     item (evaluation-symbol-symbol value-arg)
			     top-of-stack)
			   item))
	       (parameter? (if place? (parameter-p place?))))
	  (cond
	    ((null place?)
	     ;; Missing implied attribute error.
	     (stack-error
	       top-of-stack
	       "While executing a CONCLUDE action, could not locate a variable ~
                or parameter attribute of ~NF which has ~NV in its range of ~
                possible values."
	       item value-arg))
	    ((and (not parameter?)
		  (not (variable-or-parameter-p place?)))
	     (stack-error
	       top-of-stack
	       "Cannot conclude a value for ~NF, since it is not a variable or ~
                parameter."
	       place?))
	    (t
             (let* ((put-current-evaluation-value-old-value? old-value-arg)
		    (put-current-evaluation-value-return-value nil)
		    (problem-description?
		     (put-current-evaluation-value
		       place? value-arg
		       stack-expiration
		       nil nil)))
	       (setf (stack-arg 0) ; return value to local var
		     (if put-current-evaluation-value-return-value
			 (make-evaluation-truth-value truth)
			 (make-evaluation-truth-value falsity)))
	       (when problem-description?
		 (signal-conclude-problem top-of-stack problem-description?)))))))
    nil))



(defun place-reference-set-error
    (top-of-stack place-reference error-message)
  (write-stack-error
      top-of-stack
    (tformat "Cannot conclude a value for ~NV.  ~NW" place-reference error-message)
    (reclaim-error-text error-message)))

(defun signal-conclude-problem (top-of-stack problem-description)
  (write-stack-error
      top-of-stack
    (tformat "Error while executing a conclude action.  ~NW" problem-description)
    (reclaim-error-text  problem-description)))


;(def-funcalled-instruction conclude (0 (inference procedure) 4 nil)
;  (error-if-simulation-procedure "CONCLUDE" top-of-stack)
;  (let* ((item (stack-arg 0))
;	 (value-arg (stack-arg 1))
;	 (value (evaluation-value-value value-arg))
;	 (expiration-arg (stack-arg 2))
;	 (user-provided-expiration? (evaluation-value-value expiration-arg))
;	 (collection-arg (stack-arg 3))
;	 (user-provided-collection? (evaluation-value-value collection-arg))
;	 (place? (if (symbolp value)
;		     (get-implied-attribute-place item value top-of-stack)
;		     item))
;	 (type (evaluation-value-type value-arg))
;	 (parameter? (parameter-p place?)))
;    (when user-provided-collection?
;      (setq user-provided-collection?
;	    (+f gensym-time-at-start (g2-round user-provided-collection?))))
;    (when (and user-provided-expiration? (not parameter?))
;      (setq user-provided-expiration?
;	    (+f gensym-time-at-start (g2-round user-provided-expiration?))))
;    (cond
;      ((null place?)
;       ;; Missing implied attribute error.
;       (stack-error
;	 top-of-stack
;	 "While executing a CONCLUDE action, could not locate a variable or ~
;         parameter attribute of ~NF which has ~NV in its range of possible ~
;         values."
;	 item value-arg))
;      ((and (not parameter?)
;	    (not (variable-or-parameter-p place?)))
;       (stack-error
;         top-of-stack
;	  "Cannot conclude a value for ~NF which is not a variable or ~
;          parameter."
;	 place?))
;      (t
;       (multiple-value-bind (value expiration)
;	   (put-current-value
;	     place? value type (or user-provided-expiration? stack-expiration)
;	     user-provided-collection? (not (null user-provided-expiration?)))
;	 (declare (ignore value))
;	 (when (null expiration)
;	   (stack-error
;            top-of-stack
;	     "Could not CONCLUDE a value ~NV for ~NF." value-arg item))
;	 (reclaim-evaluation-value value-arg)
;	 (reclaim-if-evaluation-value expiration-arg)
;	 (reclaim-if-evaluation-value collection-arg)
;	 ;; return the new top-of-stack.
;	 (-f top-of-stack 4))))))




;;; Instruction 1, the `MOVE funcalled stack-instruction' is used to implement
;;; the move action.  It moves an icon on a workspace relative to its current
;;; position.  Note that move instructions may not be executed in simulation
;;; procedures.  Note that if the object is currently being dragged by the user,
;;; this instruction will have no effect.  Any item can be moved except for
;;; workspaces.

;; Was procedure-instruction 32.

;;; COMPILER NOTE: Type check for item.  (The item is tested at runtime to not be
;;; a workspace.)

;;; FUNCTIONALITY CHANGE: In a rule move action, if the item was a workspace, no
;;; warning message was given and 'no was returned.  This action in procedures
;;; did signal an error. 

;;;   MOVE (item delta-x delta-y)

(def-funcalled-instruction move (1 (inference procedure) 3 0 nil pprint-move-action)
  (let ((item (stack-arg 0)))
    (perform-any-deferred-icon-set-up item)
    (let* ((delta-x-evaluation-value (stack-arg 1))
	   (delta-y-evaluation-value (stack-arg 2))
	   (delta-x (evaluation-quantity-value delta-x-evaluation-value))
	   (delta-y (evaluation-quantity-value delta-y-evaluation-value)))
      (cond ((block-is-currently-being-dragged-p item)
	     ;; Decided to change the dragging collision case to a no-op.  -jra
	     ;; 6/14/89
	     t)
	    ((frame-of-class-p item 'workspace)
	     (stack-error
	       top-of-stack
	       "The workspace, ~NF, cannot be moved by a MOVE BY action." item))
	    ((or (exceptional-float-p delta-x)
		 (exceptional-float-p delta-y)
		 (< (+ (left-edge-of-block item) delta-x)
		    most-negative-workspace-coordinate)
		 (> (+ (right-edge-of-block item) delta-x)
		    most-positive-workspace-coordinate)
		 (< (+ (top-edge-of-block item) delta-y)
		    most-negative-workspace-coordinate)
		 (> (+ (bottom-edge-of-block item) delta-y)
		    most-positive-workspace-coordinate))
	     (stack-error
	       top-of-stack
	       "In the MOVE BY action, the delta X and Y values for ~NF, ~a ~
	     and ~a, would move the item outside the allowable range for ~
             workspace coordinates, ~a to ~a inclusive."
	       item delta-x delta-y
	       most-negative-workspace-coordinate
	       most-positive-workspace-coordinate))
	    (t (move-item-by item delta-x delta-y)
	       (invoke-rules-for-movement-chaining item 'is-moved-by-g2)))
      
      (reclaim-evaluation-quantity delta-x-evaluation-value)
      (reclaim-evaluation-quantity delta-y-evaluation-value)
      nil)))


(defun workspace-coordinates-in-error? (x-value? y-value? item-involved name-of-action top-of-stack)
  (cond ((or (and x-value?
		  (exceptional-float-p x-value?))
	     (and y-value?
		  (exceptional-float-p y-value?)))
	 (stack-error
	   top-of-stack
	   "In the ~a action, the new X and Y coordinates for ~NF, ~a ~
          and ~a, are not valid numbers."
	   name-of-action
	   item-involved x-value? y-value?
	   most-negative-workspace-coordinate
	   most-positive-workspace-coordinate))
	((or (and x-value?
		  (or (< x-value?
			 most-negative-workspace-coordinate)
		      (> x-value?
			 most-positive-workspace-coordinate)))
	     (and y-value?
		  (or (< y-value?
			 most-negative-workspace-coordinate)
		      (> y-value?
			 most-positive-workspace-coordinate))))
	 (stack-error
	   top-of-stack
	   "In the ~a action, the new X and Y coordinates for ~NF, ~a ~
          and ~a, are outside the allowable range for workspace ~
          coordinates, ~a to ~a inclusive."
	   name-of-action
	   item-involved x-value? y-value?
	   most-negative-workspace-coordinate
	   most-positive-workspace-coordinate))))

;;; Instruction 2, the `SET-POSITION funcalled stack-instruction' is used to
;;; implement the set-position action.  It positions an icon on a workspace at a
;;; position relative to the origin.

;; Was procedure-instruction 33.

;;; COMPILER NOTE: Type check for item.  (Type check of "not workspace" is done at
;;; run-time.)

;;; FUNCTIONALITY CHANGE: 
;;; 1.  In a rule, if the item was a workspace, no warning message was given and
;;; 'no was returned.  This action in procedures did signal an error.
;;; 2. In a rule, if the item was currently being dragged by the user, 'no was
;;; returned.  This differs from the rule move action which returned t.

;;;   SET-POSITION (item x-in-workspace y-in-workspace)

(def-funcalled-instruction set-position (2 (inference procedure) 3 0 nil
					   pprint-set-position-action)
  (let ((item (stack-arg 0)))
    (perform-any-deferred-icon-set-up item)
    (let* ((x-evaluation-value (stack-arg 1))
	   (x-in-workspace (evaluation-quantity-value x-evaluation-value))
	   (y-evaluation-value (stack-arg 2))
	   (y-in-workspace (evaluation-quantity-value y-evaluation-value)))
      (cond ((block-is-currently-being-dragged-p item)
	     ;; Decided to change the dragging collision case to a no-op.  -jra
	     ;; 6/14/89
	     t)
	    ((frame-of-class-p item 'workspace)
	     (stack-error
	       top-of-stack
	       "The workspace, ~NF, cannot be moved by a MOVE TO action." item))
	    ((workspace-coordinates-in-error? x-in-workspace y-in-workspace "MOVE" item top-of-stack)
	     )
	    (t (move-item item x-in-workspace y-in-workspace)
	       (invoke-rules-for-movement-chaining item 'is-moved-by-g2)))

      (reclaim-evaluation-quantity x-evaluation-value)
      (reclaim-evaluation-quantity y-evaluation-value)
      nil)))



;;; `Require-rotatable-and-reflectable-item' is used by the actions and system
;;; procedures that need to set an item's rotation and reflection.  It signals
;;; a stack error with an appropriate error message if item may not be rotated
;;; or reflected.

(defun require-rotatable-and-reflectable-item (item top-of-stack)
  (unless (frame-may-be-rotated-or-reflected-p item)
    (stack-error
      top-of-stack
      "Cannot rotate ~NF because this item does not have an icon ~
       or is not of a class that permits rotation."
      item)))



;;; Instruction 3, the `ROTATE funcalled stack-instruction' is used to
;;; implement the rotate action.  It rotates an icon on a workspace 0, 90, 180,
;;; or 270 degrees clockwise from its current degree of rotation.  Note that it
;;; is an error to execute this instruction in a simulation procedure.

;; Was procedure-instruction 34.

;;; COMPILER NOTE: Type check for item.  (At run-time, type check for entity).

;;; FUNCTIONALITY CHANGE: 
;;; 1. In a rule, if the item was not an entity (e.g., a workspace), no warning
;;; message was given and 'no was returned.  This action in procedures did
;;; signal an error.
;;; 2. In a rule, if the item was currently being dragged by the user, 'no was
;;; returned.  This differs from the rule move action which returned t.

;;; Possibly Bug: check how rotate works for buttons!!

;;;   ROTATE (item degree-of-rotation)

(def-funcalled-instruction rotate (3 (inference procedure) 2 0 nil pprint-rotate-action)
  (let* ((item (stack-arg 0))
	 (degree-of-rotation (stack-arg 1))
	 (rotation-value (evaluation-quantity-value degree-of-rotation)))
    (perform-any-deferred-icon-set-up item)

    (require-rotatable-and-reflectable-item item top-of-stack) ; may throw
    
    (rotate-and-reflect-icon item rotation-value nil nil nil t)
    (invoke-rules-for-movement-chaining item 'is-moved-by-g2)
    
    (reclaim-evaluation-quantity degree-of-rotation)
    nil))



;;; Instruction 4, the `SET-HEADING funcalled stack-instruction' is used to
;;; implement the set-heading action.  It rotates an icon on a workspace 0, 90,
;;; 180, or 270 degrees clockwise from its original vertical position.  Note
;;; that it is an error to execute this instruction in a simulation procedure.

;; Was procedure-instruction 35.

;;; COMPILER NOTE: Type check for item.  (At run-time, type check for entity).

;;; FUNCTIONALITY CHANGE:
;;; 1. In a rule, if the item was not an entity (e.g., a workspace), no warning
;;; message was given and 'no was returned.  This action in procedures did
;;; signal an error.
;;; 2. In a rule, if the item was currently being dragged by the user, 'no was
;;; returned.  This differs from the rule move action which returned t.

;;;   SET-HEADING (item degree-of-rotation)

(def-funcalled-instruction set-heading (4 (inference procedure) 2 0 nil
					  pprint-set-heading-action)
  (let* ((item (stack-arg 0))
	 (degree-of-rotation (stack-arg 1))
	 (rotation-value (evaluation-quantity-value degree-of-rotation)))
    (perform-any-deferred-icon-set-up item)

    (require-rotatable-and-reflectable-item item top-of-stack) ; may throw
    
    (cond #+ignore
	  ((block-is-currently-being-dragged-p item)
	   ;; Decided to change the dragging collision case to a no-op.  -jra
	   ;; 6/14/89
	   ;; The drawing substrate handles this case correctly now.  I see no
	   ;; reason keep around the restriction. -fmw, 11/7/94
	   t)
	  (t
	   (rotate-and-reflect-icon
	     item (- rotation-value (icon-heading item)) nil
	     (item-x-position item)		       ; center of rotation in
	     (-w (item-y-position item))	       ; workspace coordinates
	     t)
	   (invoke-rules-for-movement-chaining item 'is-moved-by-g2)))

    (reclaim-evaluation-quantity degree-of-rotation)
    nil))



;;; Instruction 5, the `CONCLUDE-HAS-NO-CURRENT-VALUE funcalled
;;; stack-instruction' is used to implement the conclude-has-no-current-value
;;; action for procedures.  It makes any current value of the denoted variable
;;; become expired.  If the variable does not have a current value, this
;;; action is a no-op.  Note that it is an error to execute this statement in
;;; a simulation procedure.

;; Was procedure-instruction 36.

;;; COMPILER NOTE: Type check for variable (not parameter).

;;;   CONCLUDE-HAS-NO-CURRENT-VALUE (variable)


(def-funcalled-instruction conclude-has-no-current-value (5 (inference procedure) 1 0 nil
							    pprint-conclude-has-no-current-value-action)
  (put-has-no-current-value (stack-arg 0))
  nil)



;;; Instruction 6, the `CONCLUDE-HAS-NO-VALUE funcalled stack-instruction' is
;;; used to implement the conclude-has-no-value action.  It clears out any
;;; current value of the variable and makes the variable appear as it would if
;;; it had never been given a value.  (Note that this does not affect the
;;; history of the variable in any way.)  It does this by setting the expiration
;;; of the variable to the value of the *some-time-ago*.  This is the defined
;;; reset value for variable expirations.  Note that it is an error to execute
;;; this instruction in a simulation procedure.

;; Was procedure-instruction 37.

;;; COMPILER NOTE: Type check for variable (not parameter).

;;;   CONCLUDE-HAS-NO-VALUE (variable)

(def-funcalled-instruction conclude-has-no-value (6 (inference procedure) 1 0 nil
						    pprint-conclude-has-no-value-action)
  (let ((item-or-place-reference (stack-arg 0)))
    (cond ((evaluation-place-reference-p item-or-place-reference)
	   (let ((component
		   (evaluation-place-reference-component-particulars
		     item-or-place-reference))
		 (item (evaluation-place-reference-block-or-symbol
			 item-or-place-reference)))
	     (unless (evaluation-place-reference-valid-p item-or-place-reference)
	       (stack-error
		 top-of-stack "Cannot conclude a value into ~NV."
		 item-or-place-reference))
	     (let ((error-message?
		     (conclude-into-component-dispatch item component nil nil component)))
	       (when error-message?
		 (write-stack-error top-of-stack
		   (twrite-string error-message?)
		   (reclaim-text-string error-message?)))
	       (reclaim-evaluation-place-reference item-or-place-reference))))
	  (t
	   (put-has-no-value item-or-place-reference)))
    nil))



(defun-simple execute-focus-instruction (item wait?)
  (let ((name-or-names (name-or-names-for-frame item))
	(current-ri-completion-notification-collection?
	  (when wait?
	    (set-up-completion-notification-collection
	      current-computation-instance))))
    (when name-or-names
      (if (symbolp name-or-names)
	  (loop for rule-of-this-role-name
		    in (rules-of-this-class-or-object-name
			 name-or-names)
		doing
	    (schedule-rule-instances-if-rule-is-not-embedded
	      rule-of-this-role-name nil nil nil 'focusing))
	  
	  (loop for name in name-or-names doing
	    (loop for rule-of-this-role-name
		      in (rules-of-this-class-or-object-name name)
		  doing
	      (schedule-rule-instances-if-rule-is-not-embedded
		rule-of-this-role-name nil nil nil 'focusing)))))
    
    (loop for class in 
	      (class-inheritance-path (class-description-slot item))
	  doing
      (loop for rule-of-this-role-name
		in (rules-of-this-class-or-object-name class)
	    doing
	(schedule-rule-instances-if-rule-is-not-embedded
	  rule-of-this-role-name class nil item 'focusing))

	  until (eq class 'item))
    (when wait?
      ;; Though this is preventing a leak when there is nothing to wait on,
      ;; it's not stopping the code-body-invocation from waiting forever.  See
      ;; focus-with-wait for details. -dkuznick, 5/5/06 
      (remove-completion-notification-collection-if-empty
	current-computation-instance))
    nil))

;;; Instruction 7, the `FOCUS funcalled stack-instruction' is used to implement
;;; the focus action.  It causes all rules about the item, those of the class
;;; and superclasses of the item, to be invoked.  Note that it is an error to
;;; execute this instruction in a simulation procedure.

;; Was procedure-instruction 38.

;; Review the behavior of Focus!!  When focusing on a focal-object for a
;; generic-rule, all objects are iterated over in the generic rule.  When
;; focusing on a focal-class for a generic rule, only that one object is applied
;; to that generic rule.  Either make this consistent for both cases or rewrite
;; the User documentation!!  cpm, 4/9/91.

;;;   FOCUS (item)
(def-funcalled-instruction focus (7 (inference procedure) 1 0 nil pprint-focus-action)
  (execute-focus-instruction (stack-arg 0) nil))


;; This is analogous to invoke-with-wait.  See that for details.  This
;; instruction should be merged with focus on the next KB forced recompile.
(def-funcalled-instruction focus-with-wait (82 (procedure) 1 0 nil
					       pprint-focus-with-wait-action) 

  ;; We are currently waiting forever if there are no rule-instances to focus
  ;; on.  That's because we don't do the wait here, but the compiler generates
  ;; a pause after this instruction.  Bug HQ-5273160 - "focus on <obj>,
  ;; awaiting completion" waits forever if no rules to invoke.  This possibly
  ;; needs to be fixed by adding a new instruction which does a
  ;; need-to-wait-after-attempting-rule-scheduling before the
  ;; inner-context-switch-to-next-computation-instance, ala
  ;; pause-if-called-code-bodies. -dkuznick, 5/5/06
  (execute-focus-instruction (stack-arg 0) t))



;;; Instruction 8, the `INVOKE funcalled stack-instruction' is used to
;;; implement the invoke action.  If the focal-entity?  arg is non-NIL, invoke
;;; will behave the same as "focus" with the exception that invoke will
;;; invoke-rules only if the query-restriction applies to the relationship
;;; between the rule and the entity.  If the focal-entity?  arg is NIL then
;;; things are quite different.  All rules satisfying the query-restriction will
;;; be invoked with null focal entities and null focal roles.

;;; This is a special form action.  The query-restriction argument was not
;;; evaluated and is in the constant-vector as an internal-constant.

;; Was procedure-instruction 39.

;;;   INVOKE (query-restriction focal-entity?)

;; This action is implemented as a stack-instruction since it accesses an
;; internal-constant (i.e., Lisp form) on the stack!!




;;; The system variable `executing-change-item-color-instruction-p' is
;;; temporarily bound in the instructions change-item-color and change-item-
;;; color-pattern so that the code that detects missing or unnamed color
;;; regions for icons can return an error value to the instruction code
;;; where stack-error can be called instead of warning-message.

(def-system-variable executing-change-item-color-instruction-p stack-acts nil)

(defun missing-color-region-stack-error (entity region top-of-stack)
  (stack-error
    top-of-stack
    "Cannot change the ~a region of ~NF.  The class definition for ~a ~
     does not have a region named ~a."
    region entity (class entity) region))

(defun unnamed-color-region-stack-error (entity region top-of-stack)
  (stack-error
    top-of-stack
      "Cannot change an unnamed color region in ~NF using its color name ~
       (~a).  Unnamed color regions cannot be changed."
    entity region))

(defun illegal-colors-stack-error (illegal-colors top-of-stack)
  (loop for remaining-colors on illegal-colors
	when (loop for previous-illegal-colors on illegal-colors
		   until (eq previous-illegal-colors remaining-colors)
		   never (eq (car previous-illegal-colors)
			     (car remaining-colors)))
	  collect (car remaining-colors)
	    into remaining-colors-without-duplicates  using gensym-cons
	finally
	  (write-stack-error top-of-stack
	    (write-symbol-list
	      remaining-colors-without-duplicates
	      '\, 'and)
	    (twrite-string
	      (if (cdr remaining-colors-without-duplicates)
		  " are illegal colors"
		  " is an illegal color"))
	    (reclaim-gensym-list
	      remaining-colors-without-duplicates)
	    (reclaim-gensym-list illegal-colors))))




;;; Instruction 8, the `CHANGE-ITEM-COLOR funcalled stack-instruction' is used
;;; to implement the change-item-color action.  Color is an expression returning
;;; a symbol which is the new color.  The region expression is an expression
;;; returning the symbol that is the region name.  At the present time this will
;;; always be a quoted symbol, but in the future may be a more general
;;; expression.  The color change is a kb-state-change.

;; Was procedure-instruction 40.

;; Note that change-color-of-item can give level-2 warning messages.

;;; COMPILER NOTE: Type check for item.

;;; FUNCTIONALITY CHANGE: The rule action, unlike the procedure action, did not
;;; test for a frame of class item.

;;;   CHANGE-ITEM-COLOR (item color region)

(def-funcalled-instruction change-item-color (8 (inference procedure) 3 0 nil
						pprint-change-item-color-action)
  (let ((item (stack-arg 0))
	(color (stack-arg 1))
	(region (stack-arg 2)))
    
    (let* ((executing-change-item-color-instruction-p t)
	   (color-change-error?
	     (change-color-of-item
	       item t (evaluation-symbol-symbol region)
	       (evaluation-symbol-symbol color))))
      (when color-change-error?
	(let ((type-of-error (car-of-cons color-change-error?))
	      (error-args (cdr-of-cons color-change-error?)))
	  (reclaim-gensym-cons color-change-error?)
	  (cond ((eq type-of-error 'missing-color-region)
		 (missing-color-region-stack-error
		   item error-args top-of-stack))
		((eq type-of-error 'unnamed-color-region)
		 (unnamed-color-region-stack-error
		   item error-args top-of-stack))
		((eq type-of-error 'illegal-colors)
		 (illegal-colors-stack-error error-args top-of-stack))
		(t nil)))))

    (reclaim-evaluation-value color)
    (reclaim-evaluation-value region)
    nil))




;;; Instruction 9, the `CHANGE-ITEM-COLOR-PATTERN funcalled stack-instruction'
;;; is used to implement the change-item-color-pattern action.

;; Was procedure-instruction 41.

;;; Note, that for the special-form evaluators that take a variable number of
;;; arguments, the argument-count in the funcalled-instruction definition is not
;;; correct.

;;; This is a special-form action since it takes a variable number of arguments.
;;; Arg-count is the first stack argument and is the count of additional stack
;;; arguments including the first (which is the arg-count itself).  It is
;;; assumed that there is always an item argument and that there an even number
;;; of color pattern arguments (i.e., pairs of region and color values).

;; Note that change-color-of-item can give level-2 warning messages.

;;; COMPILER NOTE: Type check for item.

;;; FUNCTIONALITY CHANGE: The rule action, unlike the procedure action, did not
;;; test for a frame of class item.

;;;   CHANGE-ITEM-COLOR-PATTERN (item {color-pattern-component} arg-count)

(def-funcalled-instruction change-item-color-pattern (9 (inference procedure) (0) 0 nil
							pprint-change-item-color-pattern-action)
  (let* ((arg-count (1+f (evaluation-integer-value (stack-arg 0))))
	 (index (-f top-of-stack (-f arg-count 1)))
	 (item (svref local-stack index))
	 (last-index (-f top-of-stack 1))
	 (evaluated-color-pattern
	   (unless (<=f arg-count 2)
	     (incff index)
	     (loop for region = (svref local-stack index)
		   for color = (svref local-stack (+f index 1))
		   collect (proc-cons 
			     (evaluation-symbol-symbol region)
			     (evaluation-symbol-symbol color))
		   using proc-cons
		   do
	       (reclaim-evaluation-symbol region)
	       (reclaim-evaluation-symbol color)
	       (incff index 2)
		   until (>=f index last-index)))))

    (change-item-color-pattern-from-evaluation-stack
      top-of-stack item evaluated-color-pattern t)
    
    (reclaim-proc-tree evaluated-color-pattern)
    (reclaim-evaluation-integer (svref local-stack top-of-stack))
    nil))

;; Note that the cons tree above should be made out of slot value conses, since
;; that is the pool that change-color-of-item uses when reclaiming this tree in
;; error cases.  -jra, 8/17/95




;;; `Change-item-color-pattern-from-evaluation-stack' is called both from the
;;; change-item-color-pattern instruction and from the g2-set-item-color-pattern
;;; system procedure.  It either changes item's color pattern per the
;;; color-pattern arg or signals a stack error, as appropriate.
;;;
;;; The first arg, top-of-stack, should correspond to the top of the evaluation
;;; stack.
;;;
;;; Color-pattern should be a "color change pattern" (see ENTITIES) made up of
;;; proc conses.
;;;
;;; Note-as-kb-state-change? normally be normally true when called from the
;;; instruction, but the policy around calling it from the system procedure has
;;; not yet been firmly established, so it remains a parameter.
;;; 
;;; Note that in the case of signalling an error, the color change pattern is
;;; reclaimed.  In all other cases, it is not reclaimed, and remains the
;;; property of the calling function.  [JRA: Please verify that this is
;;; correct! (MHD 8/17/95)]

(defun change-item-color-pattern-from-evaluation-stack
    (top-of-stack item color-pattern note-as-kb-state-change?)
  (let* ((executing-change-item-color-instruction-p t)
	 (color-change-error?
	   (change-color-of-item
	     item note-as-kb-state-change? nil color-pattern)))
    (when color-change-error?
      (let ((type-of-error (car-of-cons color-change-error?))
	    (error-args (cdr-of-cons color-change-error?)))
	(reclaim-gensym-cons color-change-error?)
	(cond ((eq type-of-error 'missing-color-region)
	       (missing-color-region-stack-error
		 item error-args top-of-stack))
	      ((eq type-of-error 'unnamed-color-region)
	       (unnamed-color-region-stack-error
		 item error-args top-of-stack))
	      ((eq type-of-error 'illegal-colors)
	       (illegal-colors-stack-error error-args top-of-stack))
	      (t nil))))))



;;; The `SHOW stack-instruction' is in the STACK-INST module.

;;;   SHOW (item window? show-details?)

;; In the stack version of this instruction, the block, window?, and
;; show-details are required, though they may be nil.  In the non-stack version
;; the window was contained in the show-details argument.  The show-details?
;; argument is an internal-constant, not an evaluation-value.

;; The SHOW funcalled stack-instruction was used to implement the SHOW action.
;; It is now implemented as a stack-instruction because it accesses an
;; internal-constant (i.e., Lisp form) on the stack!  It was
;; funcalled-instruction 11, and before that procedure-instruction 42.

;; Note that there is a modification to the SHOW action for version 4.0.  It now
;; evaluates its arguments and so requires a new instruction.  The old
;; instruction is still used for existing KB's.  Note that we could remove this
;; old stack-instruction the next time that we require all KB's to be recompiled
;; on load.  - cpm, 11/5/93



;;; Instruction 27, the `SHOW-NEW funcalled stack-instruction' is used to
;;; implement the show action for version 4.0.  This new action, unlike the SHOW
;;; stack-instruction, evaluates its arguments.  Both signal an error if the
;;; action is restricted for the given item.

;;; Note that the 3.x SHOW action is still suppported.  See the instruction in
;;; the STACK-INST module.

;;;   SHOW-NEW
;;;     (block-or-workspace g2-window? go-to-block?
;;;      symbolic-x-scale?        symbolic-y-scale?
;;;      symbolic-x-in-workspace? symbolic-y-in-workspace?
;;;      symbolic-x-in-window?    symbolic-y-in-window?
;;;      x-offset-units?          symbolic-x-offset-direction?
;;;      y-offset-units?          symbolic-y-offset-direction?
;;;      x-magnification?         y-magnification?
;;;      x-in-workspace?          y-in-workspace?
;;;      x-in-window?             y-in-window?)
(def-funcalled-instruction show-new (27 (inference procedure) 19 0 nil)
  (let* ((item (stack-arg 0))
         (g2-window? (stack-arg 1))
         (stack-arg2 (stack-arg 2))
         (stack-arg3 (stack-arg 3))
         (stack-arg4 (stack-arg 4))
         (stack-arg5 (stack-arg 5))
         (stack-arg6 (stack-arg 6))
         (stack-arg7 (stack-arg 7))
         (stack-arg8 (stack-arg 8))
         (stack-arg9 (stack-arg 9))
         (stack-arg10 (stack-arg 10))
         (stack-arg11 (stack-arg 11))
         (stack-arg12 (stack-arg 12))
         (stack-arg13 (stack-arg 13))
         (stack-arg14 (stack-arg 14))
         (stack-arg15 (stack-arg 15))
         (stack-arg16 (stack-arg 16))
         (stack-arg17 (stack-arg 17))
         (stack-arg18 (stack-arg 18))
         (go-to-block?
	  (if (evaluation-value-p stack-arg2)
	      (evaluation-value-value stack-arg2)
	      stack-arg2))
         (symbolic-x-scale?
	  (if (evaluation-value-p stack-arg3)
	      (evaluation-value-value stack-arg3)
	      stack-arg3))
         (symbolic-y-scale?
	  (if (evaluation-value-p stack-arg4)
	      (evaluation-value-value stack-arg4)
	      stack-arg4))
         (symbolic-x-in-workspace?
	  (if (evaluation-value-p stack-arg5)
	      (evaluation-value-value stack-arg5)
	      stack-arg5))
         (symbolic-y-in-workspace?
          (if (evaluation-value-p stack-arg6)
              (evaluation-value-value stack-arg6)
              stack-arg6))
         (symbolic-x-in-window?
          (if (evaluation-value-p stack-arg7)
              (evaluation-value-value stack-arg7)
              stack-arg7))
         (symbolic-y-in-window?
          (if (evaluation-value-p stack-arg8)
              (evaluation-value-value stack-arg8)
              stack-arg8))
         (x-offset-units?
          (if (evaluation-value-p stack-arg9)
              (evaluation-value-value stack-arg9)
              stack-arg9))
         (symbolic-x-offset-direction?
          (if (evaluation-value-p stack-arg10)
              (evaluation-value-value stack-arg10)
              stack-arg10))
         (y-offset-units?
          (if (evaluation-value-p stack-arg11)
              (evaluation-value-value stack-arg11)
              stack-arg11))
         (symbolic-y-offset-direction?
          (if (evaluation-value-p stack-arg12)
              (evaluation-value-value stack-arg12)
              stack-arg12))
	 (x-magnification?
          (if (evaluation-value-p stack-arg13)
              (evaluation-value-value stack-arg13)
              stack-arg13))
	 (y-magnification?
          (if (evaluation-value-p stack-arg14)
              (evaluation-value-value stack-arg14)
              stack-arg14))
	 (x-in-workspace?
          (if (evaluation-value-p stack-arg15)
              (evaluation-value-value stack-arg15)
              stack-arg15))
	 (y-in-workspace?
          (if (evaluation-value-p stack-arg16)
              (evaluation-value-value stack-arg16)
              stack-arg16))
	 (x-in-window?
          (if (evaluation-value-p stack-arg17)
              (evaluation-value-value stack-arg17)
              stack-arg17))
	 (y-in-window?
          (if (evaluation-value-p stack-arg18)
              (evaluation-value-value stack-arg18)
              stack-arg18))
	 ;; end taking of stack args
	 (ok-to-show?
	  (cond ((kb-workspace-p item)
		 (frame-system-operation-is-allowed-p 'show-workspace item))
		(t
		 (let ((workspace? (get-workspace-if-any item)))
		   (and workspace?
			(frame-system-operation-is-allowed-p 'show-workspace workspace?)))))))
    (if ok-to-show?
	(show-workspace
	  item g2-window? nil symbolic-x-scale? symbolic-y-scale?
	  symbolic-x-in-workspace? symbolic-y-in-workspace?
	  symbolic-x-in-window? symbolic-y-in-window?
	  x-offset-units? symbolic-x-offset-direction?
	  y-offset-units? symbolic-y-offset-direction?
	  x-magnification? y-magnification?
	  x-in-workspace? y-in-workspace?
	  x-in-window? y-in-window?
	  ;; This will be the value of the above-or-below-or-t-for-same? argument
	  ;; to show-workspace which is documented above that function.  (ghw 5/11/98)
	  go-to-block?)
	(stack-error
	  top-of-stack
	  "Cannot show ~NF.  The show action has been restricted for this item."
	  item))
    ;; Don't need to reclaim stack-args 0 and 1.  Arg 0 is the item and arg1 is
    ;; a window or NIL.
    (reclaim-if-evaluation-value stack-arg2) ; go-to-block?
    (reclaim-if-evaluation-value stack-arg3) ; symbolic-x-scale?
    (reclaim-if-evaluation-value stack-arg4) ; symbolic-y-scale?
    (reclaim-if-evaluation-value stack-arg5) ; symbolic-x-in-workspace?
    (reclaim-if-evaluation-value stack-arg6) ; symbolic-y-in-workspace?
    (reclaim-if-evaluation-value stack-arg7) ; symbolic-x-in-window?
    (reclaim-if-evaluation-value stack-arg8) ; symbolic-y-in-window?
    (reclaim-if-evaluation-value stack-arg9) ; x-offset-units?
    (reclaim-if-evaluation-value stack-arg10) ; symbolic-x-offset-direction?
    (reclaim-if-evaluation-value stack-arg11) ; y-offset-units?
    (reclaim-if-evaluation-value stack-arg12) ; symbolic-y-offset-direction?
    (reclaim-if-evaluation-value stack-arg13) ; x-magnification?
    (reclaim-if-evaluation-value stack-arg14) ; y-magnification?
    (reclaim-if-evaluation-value stack-arg15) ; x-in-workspace?
    (reclaim-if-evaluation-value stack-arg16) ; y-in-workspace?
    (reclaim-if-evaluation-value stack-arg17) ; x-in-window?
    (reclaim-if-evaluation-value stack-arg18) ; y-in-window?
    nil))





;;; Instruction 10, the `HIDE funcalled stack-instruction' is used to implement
;;; the hide action.

;; Was procedure-instruction 43.

;; In the stack version of this instruction, the block, window?, and
;; hide-details are required, though they may be nil.  In the non-stack version
;; the window was contained in the hide-details argument.

;;;   HIDE (item window?)

(def-funcalled-instruction hide (10 (inference procedure) 2 0 nil pprint-hide-action)
  (let* ((item (stack-arg 0))
	 (window-arg (stack-arg 1))	 
	 (designated-window-g2-extension? 
	   (if (evaluation-value-p window-arg)
	       (evaluation-value-value window-arg)
	       window-arg)))
    (show-or-hide item nil nil designated-window-g2-extension?)
    (reclaim-if-evaluation-value window-arg)
    nil))


;;; Instruction 11, the `ACTIVATE funcalled stack-instruction' is used to
;;; implement the activate action.

;; Was procedure-instruction 44.

;;; FUNCTIONALITY CHANGE: The rule action, unlike the procedure non-stack
;;; action, gave level 2 and 3 errors, instead of level 1, for no workspace and
;;; inactive item errors.

;;;   ACTIVATE (item)

(def-funcalled-instruction activate (11 (inference procedure) 1 0 nil pprint-activate-action)
  (let* ((item (stack-arg 0))
	 (subworkspace? (car (subworkspaces item))))
;    (break "calling the instruction")
    (cond ((null subworkspace?)
	   (stack-error
	     top-of-stack
	     "Attempting to activate ~NF which has no subworkspace."
	     item))
	  ((ancestor-p subworkspace? *current-computation-frame*)
	   ;; The subworkspace can never be inactivate because it is superior to
	   ;; the computation frame, which is active and currently executing!

	   ;; Note that this action previously checked if the item (parent of
	   ;; the subworkspace), instead of the subworkspace, was an ancestor of
	   ;; the computation frame.  This change was needed to allow activation
	   ;; of action-button subworkspaces.  In this case, the parent item is
	   ;; an ancestor of the button's embedded-rule, but the subworkspace is
	   ;; not.  - cpm, 3/22/95
	   (stack-error
	     top-of-stack
	     "Attempting to activate an item ~NF which is superior to the ~
              item that is doing the activation."
	     item))
	  ((not (activatable-subworkspace-p item))
	   (stack-error
	     top-of-stack
	     "Attempting to activate ~NF, which is not an object that ~
              is capable of having an activatable subworkspace."
	     item))
	  ((not (active-p item))
	   (stack-error
	     top-of-stack
	     "Attempting to activate a subworkspace of ~NF, which is ~
                     not itself active."
	     item))
	  (t
	   (funcall-method 'activate-if-possible-and-propagate subworkspace?)))
    nil)) 

;;; `parent-is-inactive-p' returns non-nil if the parent is inactive.
;;;  This is very similar to parent-is-transient-p, except that it is
;;;  checking whether the parent frame is inactive, rather than transient.

(defun-simple parent-is-inactive-p (frame)
  (let ((superblock? (superblock? frame)))
    (if superblock?
	(not (active-p superblock?))
	(let ((parent-frame? (parent-frame frame)))
	  (if parent-frame?
	      (not (active-p parent-frame?))
	      (frame-class-case frame
		(workspace 
		  (let ((parent-of-subworkspace? 
			  (parent-of-subworkspace? frame)))
		    (and parent-of-subworkspace?
			 (not (active-p parent-of-subworkspace?)))))
		(simulation-subtable
		  (not (active-p (parent-variable frame))))
		(connection 
		  (let* ((connection-structure
			   (connection-for-this-connection-frame frame))
			(input-object (input-end-object connection-structure)))
		      (and (not (active-p input-object))
			   (not (loose-end-p input-object)))))))))))


(declare-system-procedure-function g2-complete-activation t)

(defun g2-complete-activation (item)
  (cond ((frame-of-class-p item 'kb-workspace)
	 (set-inactive-and-update-representations-of-status item)
	 (activate-for-kb-workspace item)
	 (activate-code-for-item item))))

;;; `update-current-computation-instance-frame-serial-number' encapsulates
;;; the standard update to procedure and rule instances that needs to be
;;; done for actions that make existential changes to items. 

(defmacro update-current-computation-instance-frame-serial-number ()
  `(cond ((code-body-invocation-p current-computation-instance)
	  (update-code-body-invocation-frame-serial-number
	    current-computation-instance))
	 ((rule-instance-p current-computation-instance)
	  (frame-serial-number-setf (ri-frame-serial-number current-computation-instance)
		(current-frame-serial-number)))))
  
;;; Instruction 12, the `DEACTIVATE funcalled stack-instruction' is used to
;;; implement the deactivate action.

;; Was procedure-instruction 45.

;;; FUNCTIONALITY CHANGE: The rule action, unlike the procedure non-stack
;;; action, gave a level 2 error, instead of level 1, for the no workspace
;;; error.

;;;   DEACTIVATE (item)

(def-funcalled-instruction deactivate (12 (inference procedure) 1 0 nil
					  pprint-deactivate-action)
  (let* ((item (stack-arg 0))
	 (subworkspace? (car (subworkspaces item))))
    (cond ((null subworkspace?)
	   (stack-error
	     top-of-stack
	     "Attempting to deactivate ~NF which has no subworkspace."
	     item))
	  ((ancestor-p subworkspace? *current-computation-frame*)
	   ;; The subworkspace cannot be deactivated because it is superior to
	   ;; the computation frame, which is active and currently executing!

	   ;; Note that this action previously checked if the item (parent of
	   ;; the subworkspace), instead of the subworkspace, was an ancestor of
	   ;; the computation frame.  This change was needed to allow
	   ;; deactivation of action-button subworkspaces.  In this case, the
	   ;; parent item is an ancestor of the button's embedded-rule, but the
	   ;; subworkspace is not.  - cpm, 3/22/95
	   (stack-error
	     top-of-stack
	     "Attempting to deactivate an object which is superior to the ~
              item that is doing the deactivation."))
	  ((not (activatable-subworkspace-p item))
	   (stack-error
	     top-of-stack
	     "Attempting to deactivate ~NF, which is not an object that is ~
              capable of having an activatable subworkspace."
	     item))	  
	  (t
	   (update-current-computation-instance-frame-serial-number)
	   (funcall-method 'deactivate-and-propagate subworkspace? nil)
	   (validate-computation-instance-environment
	     current-computation-instance
	     nil  nil)))
    nil))


;;; Instruction 25, the `HALT funcalled stack-instruction' was used to implement
;;; the halt action.

;;;   HALT (text-message?)

;; This action is now implemented as a stack instruction since it needs to
;; access the local-var-vector.



;;; Instruction 13, the `SET funcalled stack-instruction' is used to implement
;;; the set action.  `Set' is the action which is used to set values into
;;; external variables.  This is done through the function stored in
;;; function-to-set-external-variable of the data server for the variable being
;;; set.  The implementation of this function closely follows conclude, except
;;; that once a place is determined for a variable, it is set into the spot with
;;; the function-to-set-external-variable, instead of put-current-value.

;; Was procedure-instruction 47.

;;; COMPILER NOTE: Type check for variable-or-parameter.

;; FUNCTIONALITY CHANGE:
;; 1. The rule non-stack action returned nil when the expression did not return
;; a value.
;; 2. The rule non-stack action issued all level 2 warning-messages except when
;; trying to set a parameter outside of a simulation procedure.

;; Should we still write trace messages??  Both the rule and procedure non-stack
;; actions did.  cpm, 4/11/91

;;;   SET (place datum)

(def-funcalled-instruction set (13 all 2 0 nil pprint-set-action)
  (let* ((place (stack-arg 0))
	 (value (stack-arg 1))
	 (type-of-expression (evaluation-value-type value))
	 (data-server? nil))

    (cond ((and (parameter-p place)
		(not evaluating-simulator-procedure?))
	   (stack-error
	     top-of-stack
	     "A SET statement attempted to act on the parameter ~NF.  SET ~
              can operate on parameters only from within a simulation ~
              procedure."
	     place))
	  (t
	   (setf data-server? (if evaluating-simulator-procedure?
				  (data-server 'simulator-data-server)
				  (get-data-server place)))
	   (cond ((null data-server?)
		  (stack-error
		    top-of-stack
		    "A SET action cannot complete.  A data server cannot be ~
                     found for ~NF, which was to receive the value ~NV."
		    place value))
		 ((eq data-server? 'computation)
		  (stack-error
		    top-of-stack
		    "A SET action could not change the value of ~NF, since ~
                     its data server is the inference engine.  It should be G2 ~
                     Simulator or some external data server."
		    place))
		 (t
		  (funcall-symbol
		    (function-to-set-external-variable data-server?)
		    place value
		    type-of-expression)))))

    (reclaim-evaluation-value value)
    nil))




;;; Instruction 14, the `INFORM funcalled stack-instruction' is used to
;;; implement the inform action.

;;; Destination is either an item or the symbol OPERATOR.

;;; Features: (DURATION n), (ON workspace), and (UNDER|ABOVE object).

;; Note that the stack version of Inform has been modified to take a fixed
;; number of arguments.  There is now an argument for each Inform feature.
;; Also, the evaluation of the message is handled by the Format-Form evaluator
;; and is not duplicated in Inform.

;; Note that Inform, as well as format-form, in an earlier version, evaluated
;; NAME of a designation themselves.  At some point the grammar changed to parse
;; into the role-server for NAME.  The role-server did not create names based on
;; the item class, attribute, or parent as Inform and Format-Form did.  Since
;; users currently don't have this feature, though they did at one time, this
;; behavior will not be duplicated in Inform, Format-Form, or the Name
;; role-server.  cpm, 5/15/91

;; Was procedure-instruction 49.

;; OPEN ISSUES:
;; 1. The documentation footnote on page 334 is not correct!  It states that when
;; specifying either "below <item>" or "above <item>", "on <workspace>" is not
;; recommended (but if supplied item must be on workspace).  The action
;; currently requires "on <workspace>".  Should workspace be required?
;; 2.  Should we have a new capability, g2-to-g2-message-service, similar to
;; gsi-message-service.  Currently, the gsi-message-service and
;; g2-to-g2-data-service capabilities can be used together to hack this feature.
;; (Modify the gsi-message-service attribute from gsi-data-service to
;; g2-to-g2-data-service.) The g2ds-send-message is used in this case instead of
;; gsi-deliver-message.

;; FUNCTIONALITY CHANGE:
;; 1. The rule non-stack action printed "***" on the final continuation of a
;; rule.
;; 2. In the non-stack version, inform to a non-item destination was equivalent
;; to "Inform the operator".  This is now an error.


;;; INFORM (destination-or-operator message duration? on-workspace?
;;;         below-item? above-item?)

(def-funcalled-instruction inform (14 (procedure inference) 6 0 nil pprint-inform-action)
  (let* ((destination-or-operator (stack-arg 0))
	 (message-string (evaluation-text-value (stack-arg 1)))
	 (duration-arg (stack-arg 2))
	 (duration? (if duration-arg (evaluation-value-value duration-arg) nil))
	 (on-workspace? (stack-arg 3))
	 (above-item? (stack-arg 4))
	 (below-item? (stack-arg 5))
	 (name-of-data-server nil)
	 (data-server nil)
	 (urgency? nil)
	 (object-near-message? nil)
	 (above? nil))
    (when (null destination-or-operator)
      ;; Operator
      (setq destination-or-operator 'operator))
    (when (evaluation-value-p on-workspace?)
      ;; Nil, no on workspace.
      (setq on-workspace?
	    (evaluation-value-value on-workspace?)))
    (when (evaluation-value-p above-item?)
      ;; Nil, no above item.
      (setq above-item? (evaluation-value-value above-item?)))
    (when (evaluation-value-p below-item?)
      ;; Nil, no below item.
      (setq below-item? (evaluation-value-value below-item?)))
    (when (null duration?)
      ;; Use the default duration.
      (setq duration? (let ((minimum-display-interval
			      (minimum-display-interval
				message-board-parameters)))
			(if (numberp minimum-display-interval)
			    minimum-display-interval
			    nil))))
    (when (framep destination-or-operator)
      (setq name-of-data-server
	      (get-slot-value-if-any
		destination-or-operator 'data-server-for-messages))
      (setq data-server
	    (if (and name-of-data-server (symbolp name-of-data-server))
		(data-server-or-alias? name-of-data-server))))

    (setq object-near-message? (or below-item? above-item?))
    (setq above? (not (null above-item?)))

    (cond ((and (null on-workspace?) (or above-item? below-item?))
						       ; Check this with the
						       ; Reference Manual
						       ; footnote on page 334!!
						       ; cpm, 3/23/91
	   (stack-error
	     top-of-stack
	     "Inform may not post a message above or below an object ~
              without specifying a workspace. The message is:~%~s."
	     message-string))
	  ((or (and above-item? (neq (superblock? above-item?) on-workspace?))
	       (and below-item? (neq (superblock? below-item?) on-workspace?)))
	   (stack-error
	     top-of-stack
	     "Inform does not place messages above or below objects ~
              not on the named workspace, or above or below ~
              connections generally.  The message is:~%~s."
	     message-string))
	  (t
	   (cond ((and data-server (data-server-p data-server))
		  ;; The on workspace and under/above features will be ignored
		  ;; for now if the message is going to a data server.
		  (funcall-symbol
		    (function-to-deliver-messages data-server)
		    message-string urgency? duration? *current-computation-frame*
		    destination-or-operator))
		 (t
		  (post-on-message-board
		    message-string urgency? duration? *current-computation-frame*
		    nil on-workspace? object-near-message? above?)))))

    ;; Don't reclaim stack-arg 1, the message.  It is reclaimed by the message
    ;; posting function.
    (reclaim-if-evaluation-value (stack-arg 0))
    (reclaim-if-evaluation-value (stack-arg 2))
    (reclaim-if-evaluation-value (stack-arg 3))
    (reclaim-if-evaluation-value (stack-arg 4))
    (reclaim-if-evaluation-value (stack-arg 5))
    nil))



;; The following code was an attempt at evaluating the message in the Inform
;; action, which was done in the non-stack version.  This code may be useful when
;; implementing Format-Form, which will evaluate a formatted-string.  cpm, 4/10/91

;; The message of inform may be a string, or a list beginning with AND and
;; consisting of components each of which is a string, an expression, (FORMAT
;; expression format-string-or-unit), or (FIXED-FORMAT expression integral-size
;; fraction-size). 

;; Message: string |
;;          (and message-component [, message-component])
;; where message-component:
;;          string, expression, (FORMAT expression format-string-or-unit),
;;          (FIXED-FORMAT expression integral-size fraction-size)})
;; where format-string-or-unit:
;;          TIME-STAMP | SECONDS | format-string
;; where integral-size and fraction-size are integers

;   (twith-output-to-text-string
;     (loop for message-component = (svref local-stack stack-index)
;	   with message-component-count = 0
;	   with message-format = nil
;	   with message-format-value = nil
;	   until (>=f message-component-count message-component-length)
;	   do
;       (incff message-component-length)
;       (cond ((eq message-component inform-format)
;	      (setq message-format
;		    (svref local-stack (-f stack-index 1)))
;	      (setq message-format-value
;		    (svref local-stack (-f stack-index 2)))
;	      (cond
;		((eq message-format 'time-stamp)
;		 (print-constant 
;		   (evaluation-value-value message-format-value)
;		   'time-stamp))
;		((eq message-format 'seconds)
;		 (print-constant
;		   (evaluation-value-value message-format-value)
;		   'seconds))
;		(t (tformat message-format
;			    (evaluation-value-value
;			      message-format-value))))
;	      (reclaim-if-evaluation-value message-format)
;	      (reclaim-if-evaluation-value message-format-value)
;	      (setq stack-index (-f stack-index 3)))
;	     ((eq message-component inform-fixed-format)
;	      (let ((float (svref local-stack (-f stack-index 1)))
;		    (integral-size
;		      (svref local-stack (-f stack-index 2)))
;		    (fraction-size
;		      (svref local-stack (-f stack-index 3))))
;		(write-floating-point-number
;		  float integral-size fraction-size
;		  nil)
;		(reclaim-if-evaluation-value float)
;		(reclaim-if-evaluation-value integral-size)
;		(reclaim-if-evaluation-value fraction-size)
;		(setq stack-index (-f stack-index 4))))
;	     (t (write-evaluation-value message-component)
;		(reclaim-evaluation-value message-component)
;		(setq stack-index (-f stack-index 1))))))




;;; Instruction 15, the `add-relation funcalled stack-instruction' takes a
;;; relation name, two items and a now-case, and establishes the named relation
;;; between the two items.  If now-case is nil, constraints of "one to many",
;;; "one to one", etc.  are followed.  In this case, the relation will not be
;;; added if the constraints would be violated.  If now-case is non-nil and if
;;; adding the instance would violate constraints, old instances are removed as
;;; necessary before the new instance is added.

;; Was procedure-instruction 50.

;; The call to add-to-relation is passed a called-from-procedure-arg? of T in
;; all cases.  This arg specifies that error messages should not be printed by
;; the function (which calls warning-message), but should be returned as a
;; string which is reclaimable by the caller.

;; FUNCTIONALITY CHANGE:
;; 1. Error cases in non-stack rules previously printed a warning message and
;; returned t instead of 'no.  An exception to this is if the item-designations
;; did not evaluate to items.  In that case 'no was returned.

;;;   ADD-RELATION (relation-name item item now-case?)

(def-funcalled-instruction add-relation (15 (procedure inference) 4 0 nil
					    pprint-add-relation-action)
  (let* ((relation-name (stack-arg 0))
	 (item-1 (stack-arg 1))
	 (item-2 (stack-arg 2))
	 (now-case-arg (stack-arg 3))
	 (now-case? (as-true-as (evaluation-truth-value-value now-case-arg)
				truth))
	 (returned-value?
	   (add-to-relation 
	     (evaluation-symbol-symbol relation-name) item-1 item-2 now-case?
	     t t)))
    (if (and returned-value? (text-string-p returned-value?))
	(signal-stack-error-reclaiming-message returned-value? top-of-stack)
	(progn
	  (reclaim-evaluation-symbol relation-name)
	  (reclaim-evaluation-truth-value now-case-arg)
	  nil))))

(defun signal-stack-error-reclaiming-message (error-message top-of-stack)
  (write-stack-error
    top-of-stack
    (twrite-string error-message)
    (reclaim-text-string error-message)))




;;; Instruction 16, the `remove-relation funcalled stack-instruction' takes a
;;; relation name and two items, and removes the named relation between the two
;;; items.

;; Was procedure-instruction 51.

;; The call to remove-from-relation is passed a called-from-procedure-arg?  of T
;; in all cases.  This arg specifies that error messages should not be printed
;; by the function (which calls warning-message), but should be returned as a
;; string which is reclaimable by the caller.

;; FUNCTIONALITY CHANGE:
;; 1. Error cases in non-stack rules previously printed a warning message and
;; returned t instead of 'no.  An exception to this is if the item-designations
;; did not evaluate to items.  In that case 'no was returned.

;;;   REMOVE-RELATION (relation-name item item)

(def-funcalled-instruction remove-relation (16 (procedure inference) 3 0 nil
					       pprint-remove-relation-action)
  (let* ((relation-name (stack-arg 0))
	 (item-1 (stack-arg 1))
	 (item-2 (stack-arg 2))
	 (returned-value?
	   (remove-from-relation
	     (evaluation-symbol-symbol relation-name) item-1 item-2 t t nil)))
    (if (and returned-value? (text-string-p returned-value?))
	(signal-stack-error-reclaiming-message returned-value? top-of-stack)
	(progn
	  (reclaim-evaluation-symbol relation-name)
	  nil))))



;; Comments, from the obsolete ACTIONS module, related to CREATE and DELETE.  -
;; cpm, 10/23/95

;;; The `create action' and `delete action' are used to implement transient
;;; objects.  The `transient object capabilities' are simple the ability to
;;; instantiate and delete object frames under rule and procedure control during
;;; run-time.  Create instantiates an instance of a class, possibly binding the
;;; new frame into a rule or procedure local name.  By binding a created frame
;;; into a local variable, a user can cause subsequent in order actions of a
;;; rule modify the slots of the frame and/or take graphic actions on the
;;; object, such as transfering the object onto a workspace for display.

;;; Delete deletes and reclaims the frame given it.  Any frames which are
;;; attributes of the given frame will also be deleted, along with any
;;; subworkspace on the given frame, and any frames on the subworkspace.  Note
;;; that there are issues to be delt with about the referencing of deleted
;;; frames.  When a rule deletes a frame, all bindings of that frame to local
;;; names will be deleted.  Any further references to the deleted from in
;;; subsequent in order actions, or in any actions executed simultaneously with
;;; the delete actions which reference the deleted frame are errors.  Any other
;;; ongoing rules which reference the deleted frame will be cancelled.

;;; When a proceudre deletes a frame, any bindings of that frame to local names
;;; of the procedure will be deleted.  A reference within that procedure to the
;;; deleted frame will be an error.  Any other ongoing procedures which
;;; reference the deleted frame will be allowed to continue, but if any
;;; reference a deleted frame, that will cause an error.

;;; Transient objects are instantiated with the CREATE action and deleted with
;;; the DELETE action.  There are restrictions as to the kinds of objects that
;;; can be transient, the kinds of objects that can be deleted, and the sets of
;;; operations that can be performed on transient objects.

;;; Transient objects must always be active, so it is an error to attempt to
;;; deactivate a transient object, to place a transient object on an inactive
;;; workspace, or to attempt to instantiate an object with activatable
;;; subworkspaces as a transient object.  Transient objects can be placed on
;;; workspaces, and their icon display will then be shown on that workspace.
;;; Transient objects can only be placed on one workspace at a time, so
;;; successive place actions operate in a fashion similar to transfer.  The
;;; remove action takes them off a workspace.

;;; When a KB is reset, all transient objects should be deleted.  The delete
;;; action deletes transient objects.  It is not allowed to delete a transient
;;; object which is stored as an attribute.  Allowing this would open the door
;;; to dynamically changing values of attributes themselves, which so far has
;;; been avoided.  Saved KB's should not contain transient objects, and so the
;;; sub-blocks traversal for saving must recognize and skip over transient
;;; objects.

;;; The create action needs to optionally take a variable reference which will
;;; be mutated to contain the newly created object.  The delete action needs to
;;; take an environment for the rule or action performing the delete, and it
;;; needs to remove from the environment any references to the frames which are
;;; deleted in this action.  (Note that sub-frames of a deleted frame must also
;;; be removed from the environment.)

;; End of CREATE and DELETE comments, from the ACTIONS module.



;;; Instruction 17, the `create funcalled stack-instruction' is used to create
;;; transient objects.  It takes a symbol naming a class, creates an instance of
;;; the given class, and pushes the instance on the stack.

;; Was procedure-instruction 52.


;; OPEN ISSUE:
;; 1. Rule non-stack action gave a warning when attempting to bind a
;; created instance into a non-inorder rule binding.

;; COMPILER NOTE: The return value is left on the stack.  If a var-spot is
;; provided, the POP-INTO-LOCAL-VAR instruction is used to put the value into
;; the var-spot.  If the value is not used it is popped off the stack.

;;;   CREATE (class-name)

(def-funcalled-instruction create (17 (procedure inference) 1 1 nil pprint-create-action)
  (let* ((class-evaluation-symbol (stack-arg 0))
	 (class (evaluation-symbol-symbol class-evaluation-symbol)))

    (setf (svref local-stack top-of-stack)
	  (create-action-internal class top-of-stack))
    
    ;; After the transient-item is made, update the frame-serial number
    ;; of the invocation.  This is necessary because after this create
    ;; instruction completes, the newly created item may be pushed into
    ;; a local-variable of the invocation.
    (update-current-computation-instance-frame-serial-number)
    
    (reclaim-evaluation-symbol class-evaluation-symbol)
    nil))

(defun-simple create-action-internal (class top-of-stack)
  (let ((class-description? (class-description class))
	(class-frame? (get-instance-with-name-if-any 'class-definition class)))
    (cond ((null class-description?)
	   (stack-error top-of-stack "~a is not a defined class." class))
	  ((not (class-can-be-transient-p class-description?))
	   (if (subclassp class 'item)
	       (stack-error
		 top-of-stack
		 "Attempted to create an instance of ~a, but this class ~
                    is not allowed to be created transiently."
		 class)
	       (stack-error top-of-stack "~a is not a defined class."
			    class)))
	  ((get-class-feature-in-class-description-if-any
	     class-description? 'not-user-instantiable)
	   (stack-error
	     top-of-stack
	     "An instance of ~a cannot be created because it is either an abstract ~
                class or the instantitiate attribute on its class-definition ~
                is set to `no'."  class)) 
	  ((and class-frame? (transient-p class-frame?))
	   (stack-error
	     top-of-stack
	     "Cannot create an instance of ~a.  This definition is transient."
	     class))
	  ((class-description-of-class-p class-description? 'connection)
	   (stack-error
	     top-of-stack
	     "When creating transient instances of the class ~a, ~
                a subclass of connection, you must use the additional ~
                CONNECTED grammar to initially connect it to something."
	     class))
	  (t
	   (handling-queued-existential-rule-invocations
	     (make-transient-item-of-class-description class-description?))))))
    
;;; The function `make-transient-item' takes a class name as an argument, and
;;; returns a newly created transient frame.  The given symbol should already
;;; have been verified as a valid class name by class-can-be-transient-p, and
;;; which is an OK final menu choice.

;; Need to ask Mark David why there is a make-entity, and if that is the
;; function that I'll need to use here.  That thing should be clobbered and its
;; activities merged in with make-frame, either through slot initializations or
;; the frame initialization-method.  -jra 7/23/89

;; Need to tell Mark David and Andreas Q.  Hoffman to get rid of the specific
;; class creation functions, and allow make-frame to work as it should.  -jra
;; 1/18/91

;; Changed by ML, 12 August, 89 to call make-entity. Note that not all items are
;; entities. Right now we create only dynamic OBJECTS, and these are entities.

;; Correction: As of 9/4/89, the class MESSAGE can have transient instances.
;; (MHD/ML 9/4/89)

;; Modified to allow the creation of transient definitions (e.g., object,
;; connection, and message).  - cpm, 1/17/92

(defun-simple make-frame-for-class-description (class-description)
  (let ((class (class-name-of-class-description class-description)))
    (class-description-class-case class-description
      ;; jh, 7/18/91.  Added following seven clauses to complete the
      ;; "create" action for transient items.  These are special cases which
      ;; need more initialization than that provided by make-frame or
      ;; make-entity.  We should consider putting all the frame-making
      ;; machinery back into make-frame instead of distributing it all
      ;; around the sources.
      (button (make-button class))
      (dial (make-dial class))
      (meter (make-meter class))
      (message (make-message nil class)) ; note that message is a subclass of text-box
      (text-box (make-text-box class))	 ; includes rules
      (readout-table (make-readout-table class))
      (workspace
	(if (or (eq class 'kb-workspace)
		(not (subclassp class 'kb-workspace)))
	    (make-new-top-level-kb-workspace 'kb-workspace)
	    (make-new-top-level-kb-workspace
	      class nil nil nil
	      (class-slot-description-value
		'kb-workspace-initial-width class)
	      (class-slot-description-value
		'kb-workspace-initial-height class)
	      (class-slot-description-value
		'module-this-is-part-of? class))))
      (graph (make-graph class))
      (trend-chart (make-trend-chart class))
      (entity (make-entity-of-class-description class-description :transient t))
      (t (make-frame-of-class-description class-description)))))

(defun make-frame-for-class (class)
  (make-frame-for-class-description (class-description class)))

(defun-simple make-transient-item (class)
  (make-transient-item-of-class-description (class-description class)))

(defun-simple make-transient-item-without-initialization (class)
  (let ((do-not-initialize-specializations t))
    (make-transient-item class)))

(defun-simple make-permanent-item (class)
  (make-permanent-item-of-class-description (class-description class)))

(defun-simple make-permanent-item-without-initialization (class)
  (let ((do-not-initialize-specializations t))
    (make-permanent-item class)))

(defun-simple make-transient-item-of-class-description (class-description)
  (let ((new-frame (make-frame-for-class-description class-description)))
    (set-transient-and-propagate new-frame nil)
    (unless do-not-initialize-specializations
      (funcall-method 'activate-if-possible-and-propagate new-frame)) 
    new-frame))

(defun-simple make-permanent-item-of-class-description (class-description)
  (let ((new-frame (make-frame-for-class-description class-description)))
    (set-permanent-and-propagate new-frame nil)
    (unless do-not-initialize-specializations
      (funcall-method 'activate-if-possible-and-propagate new-frame)) 
    new-frame))

(defun-simple make-permanent-item-of-class-description-without-initialization (class-description)
  (let* ((do-not-initialize-specializations t)
	 (item (make-frame-for-class-description class-description)))
    (set-permanent-and-propagate item nil)
    item))

;;; System Procedure Functions Used by G2-Create and G2-Initialize

;;; The system procedure function `g2-attributes-and-classes-to-initialize'
;;; will determine which attributes of an item will require to be initialized.
;;; This function will return a sequence containing structs.  Each struct will have
;;; a class-name and an attribute-name field.  The sequence which is returned will be
;;; empty if there are no attributes which require to be initialized.

(declare-system-procedure-function g2-attributes-and-classes-to-initialize t)

(defun g2-attributes-and-classes-to-initialize (new-item)
  (let* ((class-description
	   (class-description-slot new-item))
	 (slot-descriptions
	   (slot-descriptions class-description))
	 (pre-sequence nil))
    (loop for slot-description in slot-descriptions
	  as slot-name = (pretty-slot-name slot-description)
	  as slot-value? = (get-slot-description-value-macro
			     new-item slot-description)
	  as slot-init-form? = (slot-init-form slot-description)
	  do
      (if (and  slot-init-form?
		(slot-init-form-needs-evaluation? slot-init-form?)
		(null slot-value?))
	  (eval-push
	    (allocate-evaluation-structure-inline
	      'class-name
	      (third slot-init-form?)
	      ;; Should be called attribute-name but bug HQ-917097
	      ;; prevents it.
	      'notes
	      slot-name)
	    pre-sequence)))
    (allocate-evaluation-sequence
      (nreverse pre-sequence))))

;;; The system procedure function `g2-install-subobject' installs a subobject
;;; into a given attribute of an object.  This is used in the base G2-intitialize
;;; method to install subobjects which have been initialized by the user.

(declare-system-procedure-function g2-install-subobject t)

(defun g2-install-subobject (new-item new-subobject attribute-name)
  (change-slot-value new-item attribute-name new-subobject))

;;; The system procedure `g2-post-create-interaction' will check to see that 
;;; there this is an interactive create. If the new-item requires an immediate
;;; editing context this function will launch the editing context.  Otherwise
;;; this function will simply transfer the item to the mouse.
;;; Important Note:  This function will no longer be necessary once a number
;;; of G2 structure access bugs have been fixed.  This should be reviewed at that
;;; time.

(declare-system-procedure-function g2-post-create-interaction t)

(defun g2-post-create-interaction (new-item details)    
  (with-unleashed-and-verified-structure-args
      (details
	t
	((create-interactively (or boolean
				   (class g2-window)))
	 (x-in-window integer)
	 (y-in-window integer)))
    (invoke-rules-for-existential-chaining new-item 'is-created nil)
    (if (and create-interactively
	     (framep create-interactively))
	(let ((class? (class new-item))
	      (workstation? (workstation-for-g2-window?
			      create-interactively)))
	  (when workstation?
	    (for-workstation (workstation?)
	      (cond ((and class?
			  (subclassp class? 'kb-workspace))
		     (put-workspace-on-pane
		       new-item
		       current-workstation-detail-pane
		       'center 'center
		       nil))
		    (t
		     (when (and x-in-window
				y-in-window)
		       (cond ((and class?
				   (or (subclassp class? 'statement)
				       (subclassp class? 'text-box)))
			      (with-old-style-workstation-return-function
				  ('hand-place-on-return
				     (gensym-list
				       new-item x-in-window y-in-window
				       (copy-frame-serial-number (frame-serial-number new-item)))
				     'reclaim-hand-placement-return-information)
				(enter-editing-context
				  new-item 'box-translation-and-text
				  (make-empty-text))))    
			     (t (manifest-item-creation
				  new-item
				  nil
				  x-in-window y-in-window))))))))))))

;;; The system procedure function `g2-in-reset-state-p' is used in
;;; g2-create to determine that G2 is currently in the reset state.
;;; G2-create will not call g2-activate on a newly created item when
;;; G2 is in a reset state. 

(declare-system-procedure-function g2-in-reset-state-p t)

(defun g2-in-reset-state-p ()
  (if (or system-is-running
	  system-has-paused)
      evaluation-false-value
      evaluation-true-value))

(defun-simple class-can-be-transient-p (class-description)
  (and (class-description-of-class-p class-description 'item)
       (not (or
	      ;; Need this check lest the user of a limited-use G2 concoct a
	      ;; KB which permits full rule- and procedure-editing.
	      #+pre-g2-v5-licensing
	      (and
		(or (runtime-option-authorized-p)
		    (restricted-use-option-authorized-p)
		    (embedded-option-authorized-p) ;Added (jh, 12/20/91)
		    )
		(or (class-description-of-class-p
		      class-description 'procedure)
		    (class-description-of-class-p
		      class-description 'rule)))
	      (get-class-feature-in-class-description-if-any
		class-description 'not-normally-transient)))))

(defun-simple old-class-can-be-transient-p (class-description)
  (and (class-description-of-class-p class-description 'item)
       (not (or
	      ;; Need this check lest the user of a limited-use G2 concoct a
	      ;; KB which permits full rule- and procedure-editing.
	      #+pre-g2-v5-licensing
	      (and
		(or (runtime-option-authorized-p)
		    (restricted-use-option-authorized-p)
		    (embedded-option-authorized-p) ;Added (jh, 12/20/91)
		    )
		(or (class-description-of-class-p
		      class-description 'procedure)
		    (class-description-of-class-p
		      class-description 'rule)))
	      (class-description-of-class-p
		class-description 'procedure-invocation)
	      
	      ;; Ben felt queasy when we suggested transient message-boards.
	      ;; Review this later!!!  -jra&cpm 1/18/91 [I wish to note my
	      ;; queasiness here about message boards, too.  (MHD 7/18/91)]
	      (class-description-of-class-p
		class-description 'message-board)
	      
	      (class-description-of-class-p
		class-description 'simulation-subtable)
	      
	      ;; I bet Ben would feel queasy if this were transient.  Review
	      ;; later.  -jra&cpm 1/18/91 [I wish to note my queasiness here
	      ;; about logbook-page and system-table, too.  (MHD 7/18/91)]
	      (class-description-of-class-p
		class-description 'logbook-page)
	      (class-description-of-class-p
		class-description 'system-table)))))

;; Note that as of version 4.0, relations can be made transiently.  Previously,
;; in version 3.0, relations could only be modified when G2 was reset.  Now, a
;; relation can be modified at any time and the corresponding relations
;; instances (i.e., relations between items) are updated based on the change.  -
;; cpm, 7/28/94



;;; The function `set-transient-and-propagate' takes an item and sets its
;;; transient object bits on, and then propagates the transient object bits to
;;; its inferiors.

;;; Note that may-be-made-transient-p must be true before this function is
;;; called.

;; cpm, 1/22/92.  For permanent definitions with no subclass and no instances,
;; undefine the class and make it incomplete.  The definition should not have
;; any instances or subclasses when this function is called.

(defvar currently-within-make-transient-instruction-p nil)

(defun-simple set-transient-and-propagate (item x)
  (declare (ignore x))
  (unless (parent-is-neither-transient-nor-permanent-p item)
    (when (frame-of-class-p item 'class-definition)
      #+development
      (when (locate-definition-with-subclass-or-instance item)
	(cerror "continue"
		"This item or an inferior of this item is a definition that has ~
               either instances or subclasses.  This is an error when making ~
               an item transient.  The problem definition was ~a"
		(locate-definition-with-subclass-or-instance item)))
      ;; Must be called before becoming transient.  The definition must be
      ;; permanent, have no subclasses, and have no instances.  That is it must
      ;; pass may-be-made-transient-p!  The definition will become incomplete
      ;; after this call returns.
      (undefine-user-class-becoming-transient item)
      (add-frame-note 'transient-class-definition item))

    (set-transient item)
    (when (permanent-block-p item)
      (note-permanent-changes item 'transient)
      (when currently-within-make-transient-instruction-p
	(set-was-once-permanent item))
      (clear-permanent-block item))
    (cond
      ((frame-of-class-p item 'connection)
       (make-connection-transient
	 (connection-for-this-connection-frame item)))
      (t
       (set-connections-of-transient-block-transient item)))
    (funcall-function-to-inferior-blocks item #'set-transient-and-propagate)
    (loop for frame-representation in (frame-representations item)
	  when (and (frame-of-class-p frame-representation 'block)
		    (not (transient-p frame-representation)))
	    do (set-transient-and-propagate frame-representation nil))
    nil))




;;; The function `set-permanent-and-propagate' takes an item and sets its
;;; transient object bits off, and then propagates the transient object bits to its
;;; inferiors.

;; jh, 8/14/91.  For make-permanent action (see STACK-ACTS).

;; cpm, 1/22/92.  For transient definitions, define the class and make it
;; complete, if possible.

(defun-simple set-permanent-and-propagate (item superior-block)
  (declare (ignore superior-block))
  (let ((already-permanent? (permanent-block-p item)))    
    (when (not (parent-is-transient-p item))
      ;; Test must be repeated for benefit of connections
      ;; because this is called recursively
      ;; via funcall-function-to-inferior-blocks.
      (clear-transient item)
      (set-permanent-block item)
      (ensure-uuid-for-item item)
      (cond ((frame-of-class-p item 'connection)
	     (make-connection-permanent
	       (connection-for-this-connection-frame item)))
	    (t
	     (set-connections-of-permanent-block-permanent item)
	     (when (frame-of-class-p item 'class-definition)
	       ;; must be called after becoming permanent.
	       (unless already-permanent?
		 (define-user-class-if-possible item)
		 (delete-frame-note-if-any 'transient-class-definition item)))))
      (let ((plist (original-kb-state-plist item)))
	(unless do-not-note-permanent-changes-p
	  (when (or plist (not already-permanent?))
	    (note-permanent-changes item (or plist 'permanent))))
	(when plist
	  (remove-kb-state-changes item)))
      (funcall-function-to-inferior-blocks item #'set-permanent-and-propagate)
      (loop for frame-representation in (frame-representations item)
	    when (and (frame-of-class-p frame-representation 'block)
		      (not (permanent-block-p frame-representation)))
	      do (set-permanent-and-propagate frame-representation nil))
      nil)))


;;; The function `set-neither-permanent-nor-transient-and-propagate' takes an
;;; item and sets its neither-permanent-nor-transient object bits on, and then
;;; propagates the neither-permanent-nor-transient object bits to its inferiors.

;;; There is, in reality, no real flag called neither-permanent-nor-transient;
;;; rather, this is a state implied by the bits for permanent and transient both
;;; being off.  But that should be transparent to this function's callers.

(defun-simple set-neither-permanent-nor-transient-and-propagate (item x)
  (declare (ignore x))
  (when (frame-of-class-p item 'class-definition)
    #+development
    (when (locate-definition-with-subclass-or-instance item)
      (cerror "continue"
	      "This item or an inferior of this item is a definition that has ~
               either instances or subclasses.  This is an error when making ~
               an item neither-permanent-nor-transient.  The problem definition was ~a"
	      (locate-definition-with-subclass-or-instance item)))
    ;; Must be called before becoming neither-permanent-nor-transient.  The definition
    ;; must be permanent, have no subclasses, and have no instances.  That is it must
    ;; pass made-be-made-neither-permanent-nor-transient-p!  The definition will
    ;; become incomplete after this call returns.
    (undefine-user-class-becoming-transient item))
  (clear-transient item)
  (clear-permanent-block item)
  (cond
    ((frame-of-class-p item 'connection)
     (make-connection-neither-permanent-nor-transient
       (connection-for-this-connection-frame item)))
    (t
     (set-connections-of-neither-permanent-nor-transient-block-neither-permanent-nor-transient item)))
  (funcall-function-to-inferior-blocks item #'set-neither-permanent-nor-transient-and-propagate)
  ;; For each frame representations R that is now either permanent or transient,
  ;; if there is no superblock, or if the superblock is neither, make R be
  ;; neither. (MHD 1/10/99)
  (loop for frame-representation in (frame-representations item)
	when (and (frame-of-class-p frame-representation 'block)
		  (or (transient-p frame-representation)
		      (permanent-block-p frame-representation))
		  (or (null (superblock? frame-representation))
		      (and (not (transient-p (superblock? frame-representation)))
			   (not (permanent-block-p (superblock? frame-representation))))))
	  do (set-neither-permanent-nor-transient-and-propagate frame-representation nil))
  nil)



;;; The function `locate-definition-with-subclass-or-instance' checks if this
;;; item or any item in the kb-hierarchy is a definition with instances or
;;; subclasses.  This is necessary when checking if an item can be made
;;; transient.

;;; The name of the definition that has instances or subclasses is returned.

(defvar definition-with-subclass-or-instance-in-kb-hierarchy nil)

(defun-simple locate-definition-with-subclass-or-instance (inferior)
  (let ((definition-with-subclass-or-instance-in-kb-hierarchy nil))    ; bind special
    (locate-definition-with-subclass-or-instance-1 inferior nil)
    definition-with-subclass-or-instance-in-kb-hierarchy))

(defun-funcallable locate-definition-with-subclass-or-instance-1
		   (inferior superior?)
  (declare (ignore superior?))
  (let ((definition-name? (and (of-class-p inferior 'class-definition)
			       (name-of-defined-class inferior))))
    (unless definition-with-subclass-or-instance-in-kb-hierarchy
      (if (and definition-name?
	       (or (loop for class being each subclass of definition-name?
			 do
		     (when (and class (not (eq class definition-name?)))
		       (return t)))
		   ;; instance frames
		   (instances-specific-to-this-class definition-name?)
		   ;; connection structures
		   (and (memq
			  'connection
			  (class-inheritance-path-of-definition inferior))
			(loop for entity being each class-instance of 'entity
			      thereis
			      (loop for connection being the connections
				    of entity
				    when (subclassp
					   (if (framep connection)
					       (class connection)
					       (get-connection-class-given-connection-frame-or-class
						 (connection-frame-or-class connection)))
					   definition-name?)
				      return t)))))
	     (setq definition-with-subclass-or-instance-in-kb-hierarchy
		   definition-name?)
	     ;; check all definitions in the kb-hierachy
	     (funcall-function-to-inferior-blocks
	       inferior #'locate-definition-with-subclass-or-instance-1)))))



;; Comments from the ACTIONS module regarding DELETE.  - cpm, 10/23/95

;;; The ability for users to delete frames from within a rule or procedure makes
;;; if possible for users to write rules or procedures which reference deleted
;;; objects.  The following rules have been adopted to control what happens to
;;; rules and procedures which are referencing deleted frames.

;;; 1.  Delete removes dead frames from the environment of the rule or procedure
;;; executing the delete, but leaves it running.  If the rule accesses the local
;;; name for the deleted item in any subsequent in order, or any other
;;; simultaneous action, it is an error and the rule will be aborted.  If the
;;; procedure accesses the local name of the deleted item without first assigned
;;; a new item into its local name, then it is an error, and the procedure will
;;; be aborted.

;;; 2.  Other existing procedure invocations whose environments still contain
;;; references the deleted item will continue to run, but if the procedure
;;; accesses the local name of the deleted item without first assigning to to
;;; another value, it is an error and the procedure will be aborted.

;;; 3.  Other existing rule executions (which are waiting on wake-up) which
;;; reference the deleted frame will be aborted.

;;; 4.  Deleted frames are immediately removed from any lists or relations that
;;; they are a part of.

;;; What this means, is that the rule or procedure which executed the delete
;;; operation will continue to run, but it is an error to try and reference an
;;; item after it has been deleted.  Other ongoing rule instances which
;;; reference the deleted frame will be aborted, since it is assumed that they
;;; will have to reference the deleted frame when they resume.  (Note that this
;;; is not necessarily the case for in order rules which have completed some of
;;; their actions, but it seemed a difficult exception to users to understand,
;;; and so all rules are being treated alike.)  Other ongoing procedures WILL be
;;; allowed to continue, but it will be an error if they access the deleted
;;; item.  They are allowed to continue under the assumption that procedures
;;; have more control over their processing and so can reasonably continue under
;;; these circumstances.

;; End of comments from ACTIONS module.


;;; Instruction 18, the `delete funcalled stack-instruction' is used to delete
;;; transient objects.  It takes a transient object, and will delete that
;;; object from the system.  This function also will remove the deleted frame
;;; (and any deleted subframes) from all reachable environments of the
;;; containing code body invocation.

;;; Note that the delete-connections-without-leaving-stubs?  is bound into a
;;; special variable.

;; Was procedure-instruction 53.

;; OPEN ISSUES:
;; 1.  Delete needs to be fixed.  Are current-code-body-invocation and code-body
;; still used?
;; 2. Check the "every list" of frames.  This fixes a problem in in-order rules.
;; 3. See jra note after delete action in ACTIONS regarding illegal references
;; to deleted frames in simultaneous rule actions.
;; 4. Also, see jra note in ACTIONS after the delete action about not adding
;; subworkspaces and instances of definitions to the list of frames about to be
;; deleted.

;;;   DELETE (item delete-connections-without-leaving-stubs?)

(def-funcalled-instruction delete (18 (procedure inference) 2 0 nil pprint-delete-action)
  (let* ((item-to-delete (stack-arg 0))
	 (symbol-or-t-or-nil (stack-arg 1))
	 (without-permanence-checks-p
	   (or (eq symbol-or-t-or-nil 'without-permanence-checks)
	       (eq symbol-or-t-or-nil
		   'without-permanence-checks-without-leaving-stubs)))
	 (without-leaving-stubs-p
	   (or (eq symbol-or-t-or-nil t)
	       (eq symbol-or-t-or-nil
		   'without-permanence-checks-without-leaving-stubs))))

    (delete-action-internal
      item-to-delete
      without-permanence-checks-p
      without-leaving-stubs-p
      top-of-stack
      t)
    (reclaim-evaluation-symbol (stack-arg 1))
    nil))

;;; `delete-action-internal' exists so the delete action can be invoked from
;;; system-rpcs.  The validate-environment arg is set to T for the instruction
;;; case and nil otherwise.  This is not to say that deletions don't invalidate
;;; the environment in other cases, but rather that the validation is handled
;;; by execute-lisp-call-stack-instruction if called from a system-procedure
;;; and there is no environment to invaliate for system-rpcs.

(defun-void delete-action-internal
    (item-to-delete without-permanence-checks-p without-leaving-stubs-p
		    top-of-stack validate-environment-p)
  (cond
    ((and (not without-permanence-checks-p)
	  (not (transient-p item-to-delete)))
     (stack-error
       top-of-stack
       "Cannot delete ~NF.  It is not a transient item."
       item-to-delete))
    ((and (proprietary-p item-to-delete)
	  (not (transient-p item-to-delete)))
     (stack-error
       top-of-stack
       "Cannot delete ~NF.  It is a permanent proprietary item."
       item-to-delete))
    ((frame-of-class-p item-to-delete 'procedure-invocation)
     (stack-error
       top-of-stack
       "This action cannot delete the procedure-invocation ~NF.  ~
        This item is deleted automatically when the ~
        procedure-invocation completes execution or if the ~
        procedure or procedure-invocation is aborted."
       item-to-delete))
    ((or (frame-of-class-p item-to-delete 'simulation-subtable)
	 (frame-of-class-p item-to-delete 'system-table)
	 (parent-frame item-to-delete))
     ;; This error message doesn't necessarily make sense.  However, I'm
     ;; just duplicating the old implementation of delete-action-internal.
     (stack-error
       top-of-stack
       "Cannot delete ~NF.  It is either an attribute or simulation ~
        subtable of a superior object."
       item-to-delete))
    ((and (or (transient-p *current-computation-frame*)
	      (and without-permanence-checks-p
		   (not (transient-p item-to-delete))))
	  (existence-depends-on-p *current-computation-frame* item-to-delete))
     (stack-error
       top-of-stack
       "Cannot delete ~NF, since the delete action is being ~
        executed within ~NF, which would be deleted as part of ~NF."
       item-to-delete *current-computation-frame* item-to-delete))
    (t
     (when validate-environment-p
       (update-current-computation-instance-frame-serial-number))
     (handling-queued-existential-rule-invocations
       (let*-sim ((delete-connections-without-leaving-stubs?
		    without-leaving-stubs-p))
	 (delete-item item-to-delete)))
     (when validate-environment-p
       (validate-computation-instance-environment
	 current-computation-instance
	 nil nil)))))


;;; `remove-frame-from-parent-attribute' is a helper function that cuts a frame
;;; loose from its parent

(defun remove-frame-from-parent-attribute (item top-of-stack)
  (let (slot-description)
    (multiple-value-bind (parent pretty-name class-qualifier?)
	(get-kb-parent-information item)
      
      (cond ((not (frame-system-operation-is-allowed-p
		    'change-set-of-inferiors parent))
	     (stack-error
	       top-of-stack
	       "In the TRANSFER action, the inferiors of ~a cannot be changed"  parent))
	    ((not (frame-system-operation-is-allowed-p
		    'change-superior item))
	     (stack-error
	       top-of-stack
	       "In the TRANSFER action, the superior of ~a cannot be changed"  item))
	    (t
	     (setq slot-description
		   (get-slot-description-of-frame pretty-name parent class-qualifier?))
	     (change-slot-description-value-without-updating-representations
	       parent slot-description nil
	       (pretty-slot-name slot-description)
	       (defining-class slot-description)
	       nil nil t)
	     (set-parent-information item nil nil nil))))))

;;; Instruction 19, the `transfer funcalled stack-instruction' is used to
;;; transfer objects from one workspace to another, or transient objects from
;;; floating in the ether to a workspace.  For the moment this will only work
;;; for transient objects.  It takes an object, a workspace, and optionally
;;; expressions for the x and y coordinates of the target workspace.  In the
;;; case where workspace (workspace-designation) is nil, the object is
;;; transferred "off" of the workspace.  (The item is transfered into "limbo"
;;; or "nowhere", which is just like being transfered to an active workspace,
;;; as far as activating is concerned.)

;;; FUNCTIONALITY CHANGE:
;;; 1.  Since items can now be transient, transient items,
;;; as well as objects, can be transferred.  An exception is transient
;;; kb-workspaces, which cause an error to be signalled.

;; Was procedure-instruction 54.

;; OPEN ISSUE:
;; 1. Does transfer still deactivate the transient-item when it is moving the
;; item between workspaces?




;;;   TRANSFER (transient-item workspace? x? y?)

(def-funcalled-instruction transfer (19 (procedure inference) 4 0 nil pprint-transfer-action)
  (let ((item (stack-arg 0))
	(workspace-or-place-reference-arg
	  (stack-arg 1))
	(x-arg (stack-arg 2))	; can be a float
	(y-arg (stack-arg 3))	; can be a float
	)

    (transfer-action-internal
      item workspace-or-place-reference-arg x-arg y-arg
      top-of-stack t)
    nil))

;;; Gensym-79 fix
;;; `superior-block-p' returns T if block is superior for item
;;; Used by `transfer-action-internal' to avoid transferring item to its subobjects

(defun superior-block-p (block? item?)
  (when (and block? item? (block-p block?)) 
    ;;subblocks
    (loop for subblock being each subblock of block?
      do (when (or (eq subblock item?) (superior-block-p subblock item?))
        (return-from superior-block-p T)))

    (when (frame-of-class-p block? 'entity)
      ;; subworkspace
      (let ((subworkspace? (car (subworkspaces block?))))
      (when (or (eq subworkspace? item?) (superior-block-p subworkspace? item?))
        (return-from superior-block-p T)))

      ;; image definition
      (frame-class-case block?
        (image-definition
          (let ((media-bin? (image-definition-media-bin block?)))
            (when (or (eq media-bin? item?) (superior-block-p media-bin? item?))
              (return-from superior-block-p T)))))))
 Nil)
;;; `transfer-action-internal' exists so actions call be invoked via
;;; system-rpc in addition to this above instruction. 

(defun transfer-action-internal (item workspace-or-place-reference-arg
				      x-arg y-arg
				      top-of-stack validate-environment-p)
  (perform-any-deferred-icon-set-up item)
  (macrolet ((transfer-error (format &rest args)
	       `(if disable-stack-error
		    (return-from transfer-action-internal
		      (tformat-text-string ,format ,@args))
		    (stack-error top-of-stack ,format ,@args))))
  (let* ((component-particulars
	   (and (evaluation-place-reference-p workspace-or-place-reference-arg)
		(evaluation-place-reference-component-particulars
		  workspace-or-place-reference-arg)))
	 (transient-p (transient-p item))
	 (target-item
	   (if (evaluation-place-reference-p workspace-or-place-reference-arg)
	       (evaluation-place-reference-block-or-symbol workspace-or-place-reference-arg)
	       workspace-or-place-reference-arg))
	 workspace?
	 workspace-p?
	 (x-in-workspace? (and x-arg (evaluation-value-value x-arg)))
	 (y-in-workspace? (and y-arg (evaluation-value-value y-arg)))
	 (is-connected?
	   ;; Does this item connect to a non-loose-end block.
	   (loop for connection being each connection of item
		 as output-end-object = (output-end-object connection)
		 as block-at-other-end = (if (eq output-end-object item)
					     (input-end-object connection)
					     output-end-object)
		 thereis (not (loose-end-p block-at-other-end))))
	 (invalid-item-for-transfer?
	   (or (frame-of-class-p item 'simulation-subtable)
	       (frame-of-class-p item 'workspace)
	       (frame-of-class-p item 'connection)))
	 (reason-target-is-not-editable?
	   (when (framep target-item)
	     (reason-permanent-items-module-is-not-editable target-item)))
	 (reason-item-is-not-editable?
	   (reason-permanent-items-module-is-not-editable item)))
    (cond
      (reason-target-is-not-editable?
       (transfer-error
	 "Transfer is not permitted to ~NF, because ~A"
	 target-item reason-target-is-not-editable?))
      (reason-item-is-not-editable?
       (transfer-error
	 "Transfer is not permitted for ~NF, because ~A"
	 item reason-item-is-not-editable?))
      ((not (or transient-p
		(and permit-transfer-of-permanent-items-p
		     (framep target-item)
		     (permanent-block-p target-item)
		     ;; may-be-made-transient-p, but without the call to
		     ;; locate-definition-with-subclass-or-instance
		     (and (or (frame-of-class-p item 'message-board)
			      (permanent-block-p item))
			  (not (or (frame-of-class-p item 'system-table)
				   (frame-of-class-p item 'ui-client-session)
				   (frame-of-class-p item 'simulation-subtable))))
		     (not (proprietary-p item)))))
       (transfer-error
	 (if permit-transfer-of-permanent-items-p
	     "Transfer is not permitted for ~NF."
	     "Transfer can currently only be applied to transient items, ~
              and ~NF is not transient.")
	 item))
      ((and (not transient-p) ; guide transfers transient items to proprietary workspaces
	    (proprietary-p target-item))    
       (transfer-error
	 "Transfer to ~NF is not permitted, because it is proprietary."
	 target-item))
      ((eq item workspace-or-place-reference-arg)
       (transfer-error
	 "Cannot transfer an item onto itself"
	 item))
      ((and component-particulars
	    (null (evaluation-place-reference-valid-p workspace-or-place-reference-arg)))
       (transfer-error "Cannot transfer a value into ~NV."
	 workspace-or-place-reference-arg))
      ((and component-particulars
	    (attribute-component-particulars-p component-particulars))
       ;; the tests here mimic those in the `conclude' action 
       ;; For 5.0 only object frames can be attribute values. (ghw 8/29/96)
       (if (object-p item)
	   (if (connections item)
	       (transfer-error
		 "Objects with stubs cannot be transferred to attributes.")
	       (let* ((slot-name (attribute-component-particulars-attribute-name
				   component-particulars))
		      (defining-class
			  (attribute-component-particulars-defining-class
			    component-particulars))
		      (slot-description
			(get-slot-description-of-frame
			  slot-name target-item defining-class)))
		 (cond
		   ((or (null slot-description)
			(not (user-defined-slot-description-p slot-description)))
		    (if (null slot-description)
			(transfer-error
			  "Cannot transfer a value into the ~(~a~) of ~NF. ~
                               The attribute is not defined."
			  slot-name target-item)
			(transfer-error
			  "Cannot transfer a value into the ~(~a~) of ~NF, since ~
                               that is a system attribute."
			  slot-name target-item)))
		   (t
		    (let ((slot-type-specification
			    (slot-type-specification slot-description)))
		      
		      (cond
			((not (type-specification-type-p 
				item slot-type-specification))
			 (transfer-error
			   "The value to transfer to the ~NS of ~NF must conform ~
                                to the data type of its attribute type specification, ~
                                ~NT."
			   slot-description (class-description (class target-item))
			   target-item slot-type-specification))
			(t
			 (when validate-environment-p
			   (update-current-computation-instance-frame-serial-number))
			 (cond
			   ((framep item)
			    (cond
			      ;; The target-item is a subframe of the item
			      ((loop for sub-item = target-item then parent-frame?
				     when (eq item sub-item) return sub-item
				     for parent-frame? = (parent-frame sub-item)
				     until (null parent-frame?))
			       (transfer-error
				 "Cannot transfer ~NF into the ~(~a~) of ~NF ~
                                    because ~NF is a suboject of ~NF."
				 item slot-name target-item target-item item))
			      ;; The target-item is on a subworkspace of the item.
			      ((ancestor-p item target-item)
			       (transfer-error
				 "Cannot transfer ~NF into the ~(~a~) of ~NF ~
                                    because ~NF is on a subworkspace of ~NF ~
                                    or ~NF is a suboject on a subworkspace of ~NF."
				 item slot-name target-item target-item item
				 target-item item))
			      (t
			       (when (parent-frame item)
				 (remove-frame-from-parent-attribute item top-of-stack))
			       (change-slot-description-value
				 target-item slot-description item)
			       (update-attribute-tables (parent-frame item))
			       (when (superblock? item)
				 (erase-images-of-block item nil)
				 (transfer-workspace-subblock
				   item (superblock? item) nil)))))
			   (t
			    (transfer-error
			      "The value to transfer to the ~NS of ~NF must be a frame"
			      slot-description (class-description (class target-item))
			      target-item
			      slot-type-specification)))
			 (when validate-environment-p
			   (validate-computation-instance-environment
			     current-computation-instance nil nil)))))))))
	   (transfer-error
	     "Cannot transfer ~NF to an attribute.  The only instances allowed ~
                     as attribute values are objects and procedures." item))
       (reclaim-evaluation-place-reference
	 workspace-or-place-reference-arg)
       nil)
      (invalid-item-for-transfer?
       (cond ((of-class-p item 'kb-workspace)
	      (transfer-error
		"Cannot transfer ~NF because it is a kb-workspace.  The make ~
                  subworkspace action can be used to give a transient ~
                  kb-workspace a new superior object."
		item))
	     (t
	      (transfer-error
		"Cannot transfer ~NF because it is a ~a."
		item (class item)))))
      ((and component-particulars
	    (virtual-attribute-component-particulars-p component-particulars))
       (transfer-error
	 "Cannot transfer ~NF into the ~(~a~) of ~NF, since that is a system attribute."
	 item
	 (attribute-component-particulars-attribute-name component-particulars)
	 (evaluation-place-reference-block-or-symbol workspace-or-place-reference-arg)))
      ((evaluation-value-p workspace-or-place-reference-arg)
       (transfer-error
	 "Cannot transfer ~NF into ~NV."
	 item
	 workspace-or-place-reference-arg))
      (t
       (setq workspace? workspace-or-place-reference-arg)
       (setq workspace-p? (and workspace? (workspace-p workspace?)))
       (let ((parent-frame? (parent-frame item))
	     (parent-slot-name? nil)
	     (parent-slot-name-defining-class? nil)
	     (type-specification-class? nil))
	 (cond
	   ((and (not workspace-p?)
		 (object-p item)
		 (and workspace? (object-p workspace?))
		 (parent-attribute-name workspace?))
	    (transfer-error
	      "Cannot transfer ~NF to an attribute that already contains an object."
	      item))
	   ((and workspace-p? (or (ancestor-p item workspace?) (superior-block-p item workspace?)))
	    (transfer-error
	      "Cannot transfer ~NF to the workspace ~NF because ~NF is superior to ~
                 this workspace."
	      item workspace? item))
	   ((and workspace-p?
		 (block-can-be-dependent-p item)
		 (item-currently-contains-compiled-value item)
		 (not (block-can-be-dependent-p workspace?)))
	    ;; Restrict only transfer of compiled dependent items to an independent
	    ;; workspace.  Don't need to restrict the transfer of stable transient
	    ;; items because they are not dependable for stability.
	    (transfer-error
	      "Cannot transfer ~NF to the workspace ~NF.  ~NF is a dependent item ~
                 containing a compiled attribute and ~NF is not dependent."
	      item workspace? item workspace?))
	   (is-connected?
	    (transfer-error
	      "Cannot transfer ~NF because it is connected to another item."
	      item))
	   ((workspace-coordinates-in-error?
	      x-in-workspace? y-in-workspace? item "TRANSFER" top-of-stack))
	   ((and parent-frame?
		 (let* ((parent-attribute-name (parent-attribute-name item))
			(pretty-slot-name
			  (if (consp parent-attribute-name)
			      (car-of-cons parent-attribute-name)
			      parent-attribute-name))
			(defining-class?
			    (when (consp parent-attribute-name)
			      (cdr-of-cons parent-attribute-name)))
			(parent-frame-slot-description
			  (get-slot-description-of-frame
			    pretty-slot-name parent-frame? defining-class?))
			(slot-type-specification
			  (slot-type-specification parent-frame-slot-description))
			(class-of-type-specification?
			  (and (class-type-specification-p slot-type-specification)
			       (second slot-type-specification))))
		   (when class-of-type-specification?
		     (setq parent-slot-name? pretty-slot-name)
		     (setq parent-slot-name-defining-class? defining-class?)
		     (setq type-specification-class? class-of-type-specification?))))
	    (transfer-error
	      "Cannot transfer ~NF from the ~NQ of ~NF.  The attribute ~
                 type specification requires the value to be of class ~
                 ~a"
	      item parent-slot-name? parent-slot-name-defining-class?
	      parent-frame? type-specification-class?))
	   (t
	    (when (parent-frame item)
	      (remove-frame-from-parent-attribute item top-of-stack)
	      (update-attribute-tables parent-frame?)
	      (update-attribute-tables item))
	    
	    ;; Note that transfer may cause some items to become deactivated,
	    ;; and so we must protect the enviroments from these deactivated
	    ;; thingees.  -jra 2/5/92
	    (when validate-environment-p
	      (update-current-computation-instance-frame-serial-number))
	    
	    ;; Handle "transfer <item> to the mouse of <window>", which we
	    ;; sneaked in by binding workspace? to a window. -fmw, 2/15/94
	    (prog1 (cond ((and workspace?
			       (frame-of-class-p workspace? 'g2-window))
			  (transfer-item-to-mouse-of-window item workspace?)
			  (when parent-frame?
			    (update-attribute-tables parent-frame?))
			  nil)
			 ((and workspace? (not workspace-p?))
			  (transfer-error
			    "Cannot transfer ~a to an ~a."
			    item (class workspace-or-place-reference-arg)))
			 (t
			  (prog1 (transfer-item
				   item workspace?
				   (if x-in-workspace? (g2-round x-in-workspace?))
				   (if y-in-workspace? (g2-round y-in-workspace?))
				   t)
			    (when (parent-frame item)
			      (update-attribute-tables (parent-frame item))))))

	      (when validate-environment-p
		(validate-computation-instance-environment
		  current-computation-instance nil nil))
	      (reclaim-if-evaluation-value workspace-or-place-reference-arg)
	      (reclaim-if-evaluation-value x-arg)
	      (reclaim-if-evaluation-value y-arg))))))))))


;;; Item-to-transfer-connected-stack-error ... reclaims blocks as a list of
;;; dragging conses.

(defun item-to-transfer-connected-stack-error (blocks)
  (if disable-stack-error
      (twith-output-to-text-string
	(write-list-in-chicago-style blocks "and" t)
	(reclaim-dragging-list blocks)
	(tformat
	  " cannot be transferred due to connection to ~
       a block which is not being transferred."))
      (write-stack-error cached-top-of-stack
	(write-list-in-chicago-style blocks "and" t)
	(reclaim-dragging-list blocks)
	(tformat
	  " cannot be transferred due to connection to ~
       a block which is not being transferred."))))



;;; Instruction 20, the `change-system-attribute funcalled stack-instruction'
;;; takes an item, attribute name, and a datum, and changes the attribute of
;;; item to be the datum value.

;;; This change action allows the modification of a select group of system
;;; attributes.  The values of these attributes require no parsing.  For those
;;; attributes that require parsing, see change-the-text-of-attribute.

;;; The system attributes changeable by the change-system-attribute action are:
;;; gsi-interface-name
;;;    - type symbol, for variable? with gsi-data-service, gsi-message-service;
;;;      Note, not a kb-state-change.
;;; array-length - type integer, for g2-array;
;;; name - type symbol, for item.
;;; size - type symbol, for kb-workspace or message-board;
;;; remote-process-initialization-string - type text, for object with
;;;        capabilities gsi-interface;
;;;        INTERNAL USE, Not documented.

;; In pre-3.0, the TEXT of MESSAGES were changed in this action.  This now is
;; handled with the other text changes in change-the-text-of-attribute action.

;;; In version 4.0, the NAME attribute cannot be changed for most stable items.

;;; IMPORTANT: When adding or modifying the system-attributes available in this
;;; action, in GRAMMAR2, update the system-attribute semi-open-category and the
;;; parameter system-attribute-types.  Exceptions to this are name, size, and
;;; remote-process-initialization-string.  The first two are not really
;;; attributes and have their own grammar rules.  The third is not documented to
;;; the user.

;; Was procedure-instruction 55.

;; NOTE:
;; 1.Change to remote-process-initialization is intentionally undocumented.
;; See the comment after this instruction.  It is not a kb-state-change.
;; 2. The documentation said that the text of free messages could be changed.
;; This is not currently the case.
;; 3. The attribute gsi-interface-name is not a kb-state-change.  It is not
;; undone on reset of G2.  Since KBs from 2.0 may depend on this it is not being
;; changed.

;;;   CHANGE-SYSTEM-ATTRIBUTE (item name-of-attribute value)

(def-funcalled-instruction change-system-attribute (20 (procedure inference) 3 0 nil
						       pprint-change-system-attribute-action)
  (let* ((item (stack-arg 0))
	 (system-attribute-name (stack-arg 1))
	 (evaluation-value (stack-arg 2))
	 (value (evaluation-value-value evaluation-value))
	 (type (evaluation-value-type evaluation-value))
	 (ok-classes nil) 
	 (ok-types nil)
	 (required-class-inheritance nil))
    ;; Depending on the system-attribute, the acceptable classes for
    ;; the item, and the acceptable types for the value are restricted.
    (case system-attribute-name
      
      ;; There is no required class, because of the confusion at
      ;; present!!! Rather, an appropriate capability must be present. (ML?)

      ;; Added VARIABLE to ok-classes to pass the test below until
      ;; we decide how to handle capabilities that create the
      ;; same attribute.  (jh, 3/18/90)
      (gsi-interface-name
       (setq ok-classes '(variable))
       (setq ok-types '(symbol))
       (setq required-class-inheritance
	     '(gsi-data-service gsi-message-service)))
      (size
       (setq ok-classes '(kb-workspace message-board))
       (setq ok-types '(symbol)))
      (remote-process-initialization-string
       (setq ok-classes '(object))
       (setq ok-types '(text))
       (setq required-class-inheritance '(gsi-interface)))
      (array-length
       (setq ok-classes '(g2-array))
       (setq ok-types '(integer)))
      (name
       (setq ok-classes '(item))
       (setq ok-types '(symbol))))

    (when (or (loop for class in ok-classes 
		    never (frame-of-class-p item class))
	      
	      ;; Cannot change the name of any item that is not directly
	      ;; editable by the user.  These include procedures and relations.
	      
	      (and (eq system-attribute-name 'name)
		   (null (type-of-slot-if-editable
			   (class item) 'name-or-names-for-frame))))
      (stack-error
	top-of-stack
	"You cannot change the ~a attribute of the ~a ~NF."
	system-attribute-name (class item) item))
    
    (when (loop for type-1 in ok-types 
		never (value-type-compatible type-1 type))
      (stack-error
	top-of-stack
	"~NV is of the wrong type to be the value of the ~a attribute ~
         of the ~a ~NF."
	evaluation-value system-attribute-name (class item) item))

    ;; Required-capabilities is interpreted disjunctively, except that if NIL,
    ;; none are required.  (ML?)
    ;; Added this test, analogous to the one in the ACTIONS module. (jh,
    ;; 3/18/90)
    (when (and required-class-inheritance
	       (loop for class in required-class-inheritance
		     never (subclassp (class item) class)))
	  (stack-error
	    top-of-stack
	    "You cannot change the ~a attribute of the ~a ~NF to ~NV because ~
             its class definition does not have that attribute."
	    system-attribute-name (class item) item evaluation-value))
    
    (case system-attribute-name
      (gsi-interface-name			; Added this case. (jh, 3/18/90)
       ;; Does not note-kb-state-change in G2 version 2.0.  We are not changing
       ;; this since some kbs may rely on this.  cpm & jh 4/12/91
       (let ((current-computation-component-particulars nil))  ; specials
	 (change-slot-value item 'gsi-interface-name value)))
      (size
       (change-size-of-workspace-to-minimum item))
      (remote-process-initialization-string
       ;; Internal.  Not documented to the user.
       (change-slot-value
	 item
	 'remote-process-initialization-string
	 (copy-text-string value)))
      (array-length
       (when (not (g2-array-length-ok-p item value))
	 (bad-g2-array-length-stack-error item evaluation-value top-of-stack))
       (let ((note-as-kb-state-change? t)
	     (do-not-note-permanent-changes-p t)
	     (current-computation-component-particulars nil))  ; specials
	 (note-kb-state-change item 'g2-array-length)
	 (change-slot-value item 'g2-array-length value)))
      (name
       (let ((note-as-kb-state-change? t)
	     (current-computation-component-particulars nil))  ; specials
	 (cond
	   ((destabilizing-operation-restricted-for-item-p item)
	    (stack-error
	      top-of-stack
	      "Cannot change the name of ~NF.  The name of a stable item ~
               cannot be changed from an action."
	      item))
	   (t
	    (let ((do-not-note-permanent-changes-p t))
	      (note-kb-state-change-to-slot-by-saving-text
		item
		(get-slot-description-of-frame 'name-or-names-for-frame item))
	      (change-slot-value item 'name-or-names-for-frame value)))))))
    (reclaim-evaluation-value evaluation-value)
    nil))

;; Added undocumented change action for remote-process-initialization
;; string.  Documenting this change action would confuse users, because
;; it is unclear what GSI should do if a
;; remote-process-initialization-string is changed while the GSI
;; interface is connected.  (ml & jh, 8/15/90)


;;; The function `make-text-slot-for-whole-string' creates a new
;;; box-translation-and-text form that can serve as a text slot value with
;;; text-string itself being the "translation" and a text copy of it as the
;;; value.

(defun make-text-slot-for-whole-string (text-string)
  (slot-value-cons
    text-string
    (convert-text-string-to-text
      (twrite-parsably text-string))))



;;; Instruction 21, `change-the-text-of-attribute funcalled stack-instruction'
;;; modifies the value of a system or user attribute.  The change is similar to
;;; an edit of the attribute by the user, but the change from this instruction
;;; is a kb-state change which is undone on reset of G2.  Note that the value is
;;; the "parse" of the text argument.  The parse is the same result as if the
;;; user enterred the new attribute value in the editor, without the surrounding
;;; quotes.

;;; An error is signalled if the attribute is not defined for the item, if the
;;; the attribute is a non-editable system slot, if the attribute already
;;; contains a frame, or if the the parsed value is not valid for the attribute.
;;; There are also several other error cases noted below.

;;; This instruction differs from the change-system-attribute instruction, which
;;; modifies a small set of system-attributes and does not "parse" the new
;;; attribute value.

;;; The change is restricted in the following cases:
;;; 1. Proprietary kb restrictions are followed, other kb-restrictions are not.
;;; 2. In run-time systems, a slot with the select-changes feature, such as the
;;; text of rules, cannot be modified.
;;; 3. Attributes of TABULAR-FUNCTIONS cannot be modified.
;;; 4. Some attributes of DEFINITIONS cannot be modified (see note below).
;;;      In version 3.0, only editable attributes of transient definitions could
;;;    be modifed.
;;;     In version 4.0, all attributes of permanent definitions can be modified.
;;;       Note that the "foundation-class" cannot change when there are
;;;     instances for the definition.
;;;       Changes are propagated to definitions, as necessary.
;;; 5. As of version 4.0, RELATIONS attributes can be modified at runtime
;;; and while there are relation instances.
;;; 6. As of version 4.0, cannot change several slots of some STABLE, PERMANENT
;;; items.  The slots are:
;;;  NAMES (name-or-names-for-frame) of ITEMS,
;;;  CLASS-NAME (name-of-defined-class) of DEFINITIONS,
;;;  DIRECT-SUPERIOR-CLASSES (direct-superiors-of-defined-class) of DEFINITIONS,
;;;  the unnamed TEXT attribute of STATEMENTS and PROCEDURES.

;; Notes:

;; Was procedure-instruction 64.

;; If there is no aliased or non-aliased system attribute for the domain, check
;; for a user-attribute by that name.

;; Unlike other actions in a simultaneous rule, we are not able to test the
;; value (i.e., parse) before attempting to parse and modify the attribute.
;; Therefore this action can fail within a simultaneous rule.

;; In 3.0, this action now handles change the text of unnamed TEXT attribute.
;; Was previously in the change-system-attribute action.  E.g., change the text
;; of <rule>.

;;;   CHANGE-THE-TEXT-OF-ATTRIBUTE (item-or-place value)

(def-funcalled-instruction change-the-text-of-attribute (21 (procedure inference) 2 0 nil
							    pprint-change-the-text-of-attribute-action)
  (let* ((item-or-place (stack-arg 0))
	 (place-reference-to-reclaim? nil)
	 component-particular
	 item attribute-name slot-name defining-class
	 (text-evaluation-value (stack-arg 1))
	 (text-string-to-parse
	   (evaluation-text-value text-evaluation-value))
	 modification-while-executing?
	 (unnamed-text-attribute? nil))	       ;e.g., text of a rule

    ;; Find the attribute of the place or frame.  Get an slot unalias.  IF this
    ;; is an unnamed text attribute use "text".
    (cond
      ((evaluation-place-reference-p item-or-place)
       (setq component-particular
	     (evaluation-place-reference-component-particulars
	       item-or-place))
       (cond
	 ((or (not (evaluation-place-reference-valid-p item-or-place))
	      (not (or (attribute-component-particulars-p component-particular)
		       (virtual-attribute-component-particulars-p
			 component-particular) 
		       (aliased-attribute-component-particulars-p
			 component-particular)
		       (and (consp component-particular)
			    (eq (car-of-cons component-particular)
				'rule-scan-interval)))))
	  ;; Component-definition location.  This is where the place reference
	  ;; is validated to an attribute which can hold text.  -jra 5/9/96
	  (stack-error
	    top-of-stack
	    "Cannot change the text of ~NV." item-or-place))
	 (t
	  (setq item (evaluation-place-reference-block-or-symbol item-or-place))
	  (cond
	    ((aliased-attribute-component-particulars-p
	       component-particular)
	     (setq attribute-name
		   (aliased-attribute-alias component-particular))
	     (setq slot-name
		   (aliased-attribute-actual-attribute
		     component-particular))
	     (setq defining-class
		   (aliased-attribute-defining-class
		     component-particular)))
	    ;; Virtual attributes can shadow aliased or unaliased system
	    ;; attributes that are use accessible.  Allow change the text of to
	    ;; see them here.
	    ((virtual-attribute-component-particulars-p
	       component-particular)
	     (let* ((name (virtual-attribute-component-particulars-name
			    component-particular))
		    (unaliased-name
		      (or (get-slot-name-for-alias-if-any name item)
			  name)))
	       (setq attribute-name name)
	       (setq slot-name unaliased-name)
	       (setq defining-class nil)))
	    ((and (consp component-particular)
		  (eq (car-of-cons component-particular)
		      'rule-scan-interval))
	     ;; Component-definition location.  This is where an attribute-mimic
	     ;; or reference to a system slot turns into the appriate actual
	     ;; attribute of a frame.  -jra 5/9/96
	     (setq attribute-name 'scan-interval)
	     (setq slot-name 'rule-scan-interval))
	    (t
	     (setq attribute-name
		   (attribute-component-particulars-attribute-name
		     component-particular))
	     (setq slot-name attribute-name)
	     (setq defining-class
		   (attribute-component-particulars-defining-class
		     component-particular))))
	  ;; Defer reclaiming the evaluation-place-reference until the very end
	  ;; so that any subsequent calls to stack-error can print and reclaim
	  ;; it.
	  (setq place-reference-to-reclaim? item-or-place))))
      ((framep item-or-place)
       (cond
	 ((setq slot-name
		(get-slot-name-for-alias-if-any
		  'text item-or-place))
	  (setq item item-or-place)
	  (setq attribute-name 'text)
	  (setq defining-class nil)
	  (setq unnamed-text-attribute? t))
	 (t
	  (stack-error
	    top-of-stack "~NF has no TEXT attribute." item-or-place)))
       (when (eq item-or-place *current-computation-frame*)
	 (stack-error
	   top-of-stack
	   "Cannot change the text of ~NF.  This ~a is currently executing."
	   item-or-place (class item-or-place))))
      (t
       (stack-error
	 top-of-stack
	 "Cannot change the text of ~NV." item-or-place)))

    ;; Make the change if possible.
    (cond
      ((frame-of-class-p item 'tabular-function)
       ;; Can't change any attributes tabular functions.
       (stack-error
	 top-of-stack
	 "Cannot change the text of the ~a of ~NF.  ~
          Attributes of tabular-functions cannot be changed from this action."
	 attribute-name item))
      ((setq modification-while-executing?
	     (modification-while-executing? item slot-name))
       (stack-error
	 top-of-stack
	 modification-while-executing?))
      ((and (frame-of-class-p item 'class-definition)
	    (not (frame-of-class-p item 'object-definition))
	    (eq slot-name 'icon-description-for-class?)
	    (not (class-definition-defines-user-editable-icon-class-p item)))
       (stack-error
	 top-of-stack
	 "Cannot change the text of the icon-description of ~NF.  The ~
          value of the direct-superior-classes attribute on the ~
          class-definition does not indicate that the class has a ~
          changeable icon-description." item))
      (t
       (let* ((slot-description?
		(get-slot-description-of-frame slot-name item defining-class))
	      (type-of-slot-if-editable?
		(if slot-description?
		    (type-slot-feature-assq-if-editable
		      (slot-features slot-description?)))))
	 (cond
	   ((null slot-description?)
	    ;; This test is needed since the slot name may be a global unalias
	    ;; of an a slot and may not be present on this item.
	    (stack-error
	      top-of-stack
	      "Cannot change the text of the ~a of ~NF.  This ~
               item does not have this attribute."
	      attribute-name item))
	   ((null type-of-slot-if-editable?)
	    (stack-error
	      top-of-stack
	      "Cannot change the text of the ~a of ~NF.  This ~
               attribute cannot be modified from an action."
	      attribute-name item))
	   ((framep (get-slot-description-value item slot-description?))
	    (stack-error
	      top-of-stack
	      "Cannot change the text of the ~a of ~NF.  This ~
               attribute contains an item."
	      attribute-name item))
	   ((and (not (attribute-operation-is-allowed-p
			'edit-attribute item attribute-name (defining-class slot-description?)))
		 ;; Changing text of a message is never restricted.
		 (not (and (of-class-p item-or-place 'message)
			   unnamed-text-attribute?)))
	    ;; The attribute is restricted for editing.  For 2.1, backward
	    ;; compatibilty, the text of messages are not restricted, even
	    ;; if proprietary.
	    ;; --- Note that it was only possible to change
	    ;; the text of MESSAGE instances in 2.1.  In particular, it was
	    ;; not possible to change the text of FREE-TEXT class instances.
	    ;; There was a misunderstanding, however, in 3.0 Rev. 0, about
	    ;; this.  In that rev., instances of FREE-TEXT only, but not
	    ;; BORDERLESS-FREE-TEXT or TEXT-INSERTER instances, were
	    ;; included with message for backward compatibility.  "Change
	    ;; the text of" also was extended to deal with ALL instance of
	    ;; TEXT-BOX, including, for example, RULE instances.  This was
	    ;; not much documented.  Therefore, for Rev. 1, I am removing
	    ;; the erroneous "grandfathering" of FREE-TEXT instances; FREE-TEXT
	    ;; is NOT a grandfather, like message, but a newcomer, like RULE and
	    ;; especially like his sibling class BORDERLESS-FREE-TEXT.  Thus:
	    ;; MESSAGE alone has never been restricted; FREE-TEXT was
	    ;; like MESSAGE in 3.0 Rev. 0, but like BORDERLESS-FREE-TEXT in
	    ;; 2.1 and 3.0 Rev. 1 and later.  (MHD 11/16/92)
	    (if unnamed-text-attribute?
		(stack-error
		  top-of-stack
		  "Cannot change the text of ~NF.  The modification of this ~
                   item has been restricted."
		  item)
		(stack-error
		  top-of-stack
		  "Cannot change the text of the ~a of ~NF.  The modification ~
                   of this item has been restricted."
		  attribute-name item)))
	   
	   ((restrict-destabilization-p item slot-description?)
	    (cannot-change-text-stack-error
		top-of-stack item slot-description? unnamed-text-attribute?
		"Since this item is declared stable, this change would cause ~
                 dependent parts of the KB to become ~
                 incomplete and require recompilation.  This change is therefore ~
                 not permitted from an action."))
;           ((and unnamed-text-attribute?
;                 (or (frame-of-class-p item 'statement)
;                     (frame-of-class-p item 'procedure))
;                 (destabilizing-operation-restricted-for-item-p item))
;            (stack-error
;              top-of-stack
;              "Cannot change the text of ~NF.  The text of a stable ~
;               ~a cannot be changed from an action."
;              item (class item)))
;           ((and (or (eq slot-name 'name-or-names-for-frame)
;                     (and (or (eq slot-name 'name-of-defined-class)
;                              (eq slot-name 'direct-superiors-of-defined-class))
;                          (frame-of-class-p item 'definition)))
;                 ;; Note the above tests the actual, possibly unaliased, slot
;                 ;; name.
;                 (destabilizing-operation-restricted-for-item-p item))
;            (stack-error
;              top-of-stack
;              "Cannot change the text of the ~a of ~NF.  The ~a of a stable ~
;               cannot be changed from an action."
;              attribute-name item attribute-name))
	   (t
	    ;; The following call needs to take the value of defining-class,
	    ;; already bound above!!!  -jra 2/15/94 --- OK. (MHD 2/15/94)
	    (multiple-value-bind (success? reason-for-failure?)
		(parse-and-change-slot
		  item slot-description?
		  text-string-to-parse
		  type-of-slot-if-editable?)
	      ;; The text-string-to-parse is reclaimed by the following error
	      ;; handler since it is still on the stack.
	      (unless success?
		(cannot-change-text-stack-error
		  top-of-stack item slot-description? unnamed-text-attribute?
		  "~a~%The following text is not valid for this attribute:~%~%~A"
		  (or reason-for-failure? "") ; not sure reason can ever 
		  text-evaluation-value)      ;   be nil (JED)
		(when reason-for-failure?
		  (reclaim-text-string reason-for-failure?)))))))))
    (when place-reference-to-reclaim?
      (reclaim-evaluation-place-reference place-reference-to-reclaim?))
    nil))



;;; Returns nil if modification of the named slot in the named item is OK.
;;; If it isn't OK, because it's currently executing, it returns an error
;;; message string, suitable for use in stack-error.

(defun-simple modification-while-executing? (item slot-name)
  (when
      (and *current-computation-frame*
	   (embedded-rule-p *current-computation-frame*)
	   (eq (parent-frame *current-computation-frame*) item)
	   (or
	     (and (frame-of-class-p item 'action-button)
		  (eq slot-name 'translation-and-text-of-embedded-rule))
	     (and (frame-of-class-p item 'user-menu-choice)
		  (eq slot-name 'action-for-user-menu-choice?))))
    (tformat-text-string
      "Cannot change the text of the action of ~NF.  It is currently ~
          executing."
      item)))

;;; `Cannot-change-text-stack-error' ...

(defun cannot-change-text-stack-error
    (top-of-stack item slot-description unnamed-text-attribute?
     &optional format-control-string?
     arg1 arg2 arg3 arg4 arg5 arg6 asrg7 arg8 arg9)
  (write-stack-error
      top-of-stack
    (tformat "Cannot change the text of ")
    (if unnamed-text-attribute?
	(tformat "~NF" item)
	(tformat
	  "the ~NQ of ~NF"
	  (alias-slot-name-if-necessary
	    (pretty-slot-name slot-description)
	    item)
	  (if (slot-name-needs-qualification-p
		slot-description
		(class-description-slot item))
	      (defining-class slot-description))
	  item))
    (tformat ".")
    (when format-control-string?
      (tformat "  ")
      (funcall
	#'tformat format-control-string?
	arg1 arg2 arg3 arg4 arg5 arg6 asrg7 arg8 arg9))
    ;; GENSYMCID-1544: Suspected memory leak when programmatically changing text
    ;;                 of a function-definition to an expression with invalid syntax
    (reclaim-text-string arg1)))

;; CPM should review/make more use of this above.  (MHD 6/1/94)




;;; Parse-and-change-slot returns false (nil) to indicate failure and true
;;; (non-nil) to indicate success.  This reclaims text-string-to-parse iff
;;; it succeeds.  ...

(defun parse-and-change-slot
    (item slot-description text-string-to-parse type-of-slot)
  (let ((*current-computation-frame* nil)		; specials
	(current-computation-component-particulars nil))
    (cond
      ((free-text-slot-type-p type-of-slot)
       (cond
	 ;; new: optimized update for free-text text boxes. (MHD 9/16/92)
	 ((and
					; (text-box-p item) ; unnec.
	    (eq (pretty-slot-name slot-description)
		'box-translation-and-text))
	  (let ((do-not-note-permanent-changes-p t))
	    (note-kb-state-change-to-slot-by-saving-text item slot-description)
	    (replace-text-with-text-string-in-text-box text-string-to-parse item))
	  (reclaim-text-string text-string-to-parse)
	  t)
	 (t
	  (parse-text-for-slot
	    (convert-text-string-to-text text-string-to-parse)
	    item slot-description t)
	  ;; CANNOT fail and return nil
	  )))
      (t
       (multiple-value-bind (success? reason-for-failure?)
	   (parse-text-for-slot
	     (convert-text-string-to-text
	       (copy-text-string text-string-to-parse))
	     item slot-description t
	     nil nil nil t)
	(if success?
	   (progn (reclaim-text-string text-string-to-parse)
		  t)
	   (values nil reason-for-failure?)))
       ;; can fail and return nil; if it fails and returns nil, then
       ;; text-string-to-parse cannot be reclaimed, and instead it must
       ;; be reclaimed by the caller.
       ))))



;;; The function `change-g2-array-element' is used to change the element of a
;;; g2-array.  This function is used by the Change action when modifying both
;;; item or datum arrays and by the Conclude action when modifying datum arrays.
;;; It is up to the Conclude Action to test for datum-arrays.

;;; The new-element is either an item or an evaluation-value.  This function
;;; assumes that the new item or datum element is of the correct type and is not
;;; tested here.  See the stack-instructions coerce-matching-element-type and
;;; coerce-matching-element-type-or-unknown.  The error-symbol argument should
;;; be something like CONCLUDE or CHANGE.

;;; Note that this function does reclaim evaluation-value arguments but does not
;;; modify the top of stack.  This function does not return if an error is
;;; signaled.

(defun change-g2-array-element (g2-array index new-element error-symbol
				top-of-stack)
  (cond ((not (g2-array-with-elements-p g2-array))
	 (stack-error
	   top-of-stack
	   "Cannot ~(~a~) the element at index ~NV in array ~NF.  This ~
            array is of length 0."
	   error-symbol index g2-array))
	((not (g2-array-index-ok-p g2-array index))
	 (stack-error
	   top-of-stack
	   "Cannot ~(~a~) the element at index ~NV in array ~NF.  ~NV is ~
            not in the range 0 to ~a."
	   error-symbol index g2-array index (-f (g2-array-length g2-array) 1)))
	(t
	 (mutate-g2-array-reclaiming-evaluation-values
	   g2-array index new-element)))
  nil)


(defun change-g2-list-element-final-processing (les val)
  #-SymScale
  (let ((old-value (list-element-value les)))
    (setf (list-element-value les) val)
    (cond ((framep old-value)
	   (delete-from-list-elements-for-item old-value les))
	  (t
	   (reclaim-if-evaluation-value old-value))))
  #+SymScale
  (loop for old-value = (list-element-value les) do
    ;; Add the new value to the g2-list.  This assumes that the new
    ;; element is of the correct g2-list element type.
    (when (compare-and-swap (list-element-value les) old-value val)
      (cond ((framep old-value)
	     ;; Remove the information for the old element value.
	     (delete-from-list-elements-for-item old-value les))
	    (t
	     (reclaim-if-evaluation-value old-value)))
      (return)))

  ;; Update the g2-list information for this item element.
  (when (framep val)
    (add-to-list-elements-for-item val les)))
  
;;; The function `change-g2-list-element' is used to change the element of a
;;; g2-list.  This function is used by the Change action when modifying both
;;; item or value lists and by the Conclude action when modifying value lists.
;;; It is up to the Conclude Action to test for value-lists.  (See also
;;; change-g2-array-element.)

;;; The new-element is either an item or an evaluation-value.  This function
;;; assumes that the new item or value element is of the g2-list element type
;;; and is not tested here.  The error-symbol argument should be something like
;;; CONCLUDE or CHANGE.

;;; Note that this function does consumes or reclaims any evaluation-value
;;; element argument.  So, the caller should not hold onto or reclaim the
;;; element.

;;; This function does not modify the top of stack.  Note that it does not
;;; return if an error is signaled.

(defun change-g2-list-element
    (g2-list index item-or-evaluation-value error-symbol top-of-stack)
  (when (g2-list-empty-p g2-list)
    (stack-error
      top-of-stack
      "Cannot ~a the element at index ~NV in ~NF.  This g2-list ~
        contains no elements."
      error-symbol index g2-list))
  (when (or (<f index 0) (>=f index (list-size g2-list)))
    (stack-error
      top-of-stack
      "G2 List index is out of bounds"
      error-symbol index g2-list))
  ;; without duplicate check, code is simple
  (when (insert-duplicate-elements? g2-list)
    (if (>f (-f (list-size g2-list) index) index)
	;; insert from head to tail if index is small
	(loop with g2-list-structure = (list-structure g2-list)
	      for element-count = 0 then (1+f element-count)
	      for element-structure being g2-list-structure-element of g2-list-structure
	      with nth-element-structure? = nil
	      do
	  (when (=f element-count index)
	    (setq nth-element-structure? element-structure))
	      until (or (null element-structure) nth-element-structure?)
	      finally
	        (change-g2-list-element-final-processing nth-element-structure?
							 item-or-evaluation-value))
        ;; insert from tail and head if index is big
	(loop with g2-list-structure = (list-structure g2-list)
	      for element-count = (1-f (list-size g2-list)) then (1-f element-count)
	      for element-structure being g2-list-structure-reverse-element of g2-list-structure
	      with nth-element-structure? = nil
	      do
	  (when (=f element-count index)
	    (setq nth-element-structure? element-structure))
	      until (or (null element-structure) nth-element-structure?)
	      finally 
	        (change-g2-list-element-final-processing nth-element-structure?
							 item-or-evaluation-value)))
    (return-from change-g2-list-element))

  ;; Iterate over the elements of the non-empty list, finding the nth element.
  ;; Check for duplicates and signal an error when necessary.
  (loop with allow-duplicates? = (insert-duplicate-elements? g2-list)
	with new-value-item-p? = (framep item-or-evaluation-value)
	with g2-list-structure = (list-structure g2-list)
	with nth-element-structure? = nil
	for element-count = 0 then (1+f element-count)
	for element-structure being g2-list-structure-element of g2-list-structure
	for element-value = (list-element-value element-structure)
	do
    (cond ((=f element-count index)
	   (setq nth-element-structure? element-structure))
	  ((and (null allow-duplicates?)
		(or (and new-value-item-p?
			 (eq item-or-evaluation-value element-value))
		    ;; Both old and new elements are evaluation-values.
		    (and (evaluation-value-p element-value)
			 (evaluation-value-=
			   item-or-evaluation-value element-value))))
	   (duplicate-g2-list-element-stack-error
	     g2-list index element-value element-count error-symbol
	     top-of-stack)))
	until (or (null element-structure)
		  (and nth-element-structure? allow-duplicates?))
	finally
	  ;; Signal an error if the element was not found.  The index is outside
	  ;; the bounds of the list.
	  (when (null nth-element-structure?)
	    (if (/=f element-count 0)
		(stack-error
		  top-of-stack
		  "Cannot ~(~a~) the element at index ~a in ~NF.  Since this ~
                  g2-list contains ~a elements, the index must be in the range ~
                  from 0 to ~a."
		  error-symbol index g2-list (+f element-count 1) element-count)
		(stack-error
		  top-of-stack
		  "Cannot ~(~a~) the element at index ~a in ~NF.  Since this g2-list ~
                  contains 1 element, the index must be 0."
		  error-symbol index g2-list)))
          (change-g2-list-element-final-processing nth-element-structure?
						   item-or-evaluation-value)))
				

;;; Instruction 22, the `change-nth-element funcalled stack-instruction' takes a
;;; g2-array or g2-list, an element, which could be an item or value,
;;; depending on the element type, and an index.

;; Was procedure-instruction 65.

;; Note that the name of this instruction was change-g2-array-element.  The
;; instruction was modified to handle g2-lists as well as g2-arrays.  - cpm,
;; 8/2/91.

;; Note that there are two instructions, coerce-matching-element-type-or-unknown
;; and coerce-matching-element-type, which are emitted by the compiler of this
;; action before calling the change-nth-element action instruction.  These
;; instructions get the current value of variable or parameter elements as
;; needed, tests the element for the correct element type, and leaves the value
;; on the stack.  (Unlike some actions, such as g2-list "insert", we are not
;; able to know at compile time if the element is the item or the value of the
;; item.)  Change-nth-element instruction, therefore, does not data seek values.
;; It assumes that the type of the new element and the element-type of the array
;; or list do not change after the type is tested and before this action is
;; executed.

;;;   CHANGE-NTH-ELEMENT (item element index)

(def-funcalled-instruction change-nth-element (22 (procedure inference) 3 0 nil
						  pprint-change-nth-element-action)
  (let* ((g2-array-or-list (stack-arg 0))
	 (element (stack-arg 1))
	 (index-evaluation-value (stack-arg 2))
	 (index (evaluation-integer-value index-evaluation-value)))
    (cond ((g2-array-p g2-array-or-list)
	   (change-g2-array-element
	     g2-array-or-list index element 'change top-of-stack))
	  ((g2-list-p g2-array-or-list)
	   ;; Uses or reclaims any evaluation-values.
	   (change-g2-list-element
	     g2-array-or-list index element 'change top-of-stack))
	  (t
	   (stack-error top-of-stack "Neither array nor list?! ~NF"
			g2-array-or-list)))
    (reclaim-evaluation-integer index-evaluation-value)
    nil))




;;; Instruction 23, the `g2-list-insert-expression funcalled stack-instruction'
;;; takes a g2-list, a required-element-type, a datum element, an
;;; insertion-type, and a second datum element (or nil).  The instruction
;;; inserts the first datum into the list at the indicated position.

;;; The second datum element is the element that is used in the before and after
;;; insert-types to indicate the element position.  This arg can be nil if the
;;; insertion-type does not use this value.

;;; There are several insertion-types: beginning, end, before, and after.

;;; An error is signaled if:
;;;   the required element type is invalid for the g2-list element-type,
;;;   the element is invalid for the g2-list element-type,
;;;   the insert operation fails.

;;; G2-LIST-INSERT-EXPRESSION 
;;;    (g2-list required-element-type element-datum-1 insertion-type 
;;;     element-datum-2?)

;; Was procedure-instruction 56.

;; OPEN ISSUES:

;; 1.  Improve the speed of insert before and after into a list that does not
;; allow duplicate elements.  Traverse the list once looking for a duplicate
;; element, when necessary, and looking for the place to add the element.

(def-funcalled-instruction g2-list-insert-expression (23 (procedure inference) 5 0 nil
							 pprint-g2-list-insert-action)
  (let* ((g2-list (stack-arg 0))
	 (required-element-type-arg (stack-arg 1))
	 (required-element-type
	   (evaluation-symbol-symbol required-element-type-arg))
	 (list-element-type (list-type g2-list))
	 (element-1-arg (stack-arg 2))
	 (insertion-type-arg (stack-arg 3))
	 (insertion-type (evaluation-symbol-symbol insertion-type-arg))
	 (element-2-arg (stack-arg 4))
	 (no-insert-but-no-error? nil))
    (cond ((not (required-datum-type-ok-for-g2-list-or-array-p
		  required-element-type (list-type g2-list) t))
	   (stack-error
	     top-of-stack
	     "Cannot INSERT ~NA into the g2-list ~NF.  The element type of ~
              the list, ~a, conflicts with the required type, ~NV, specified ~
              in the action."
	     element-1-arg g2-list (list-type g2-list) required-element-type))
	  ((not (datum-ok-for-g2-list-or-array-p
		  element-1-arg list-element-type))
	   (stack-error
	     top-of-stack
	     "Cannot INSERT ~NA into the g2-list ~NF.  The type of this ~
              element conflicts with the list element type ~a."
	     element-1-arg g2-list (list-type g2-list)))
	  ((eq insertion-type 'beginning)
	   (unless (or (g2-list-insert-at-beginning element-1-arg g2-list)
		       (setq no-insert-but-no-error?
			     (insert-action-duplicate-element-backward-compatibility-p)))
	       (stack-error
		 top-of-stack
		 "Cannot insert ~NA at the beginning of ~NF.  ~NA is already an ~
                 element and the g2-list does not allow duplicate elements."
		 element-1-arg g2-list element-1-arg)))
	  ((eq insertion-type 'end)
	   (unless (or (g2-list-insert-at-end element-1-arg g2-list)
		       (setq no-insert-but-no-error?
			     (insert-action-duplicate-element-backward-compatibility-p)))
	     (stack-error
	       top-of-stack
	       "Cannot insert ~NA at the end of ~NF.  ~NA is already an ~
                element and the g2-list does not allow duplicate elements."
	       element-1-arg g2-list element-1-arg)))
	  (t
	   (let ((result-flag
		   (cond
		     ((eq insertion-type 'before)
		      (g2-list-insert-before
			element-1-arg element-2-arg g2-list nil))
		     ((eq insertion-type 'after)
		      (g2-list-insert-after
			element-1-arg element-2-arg g2-list nil))
		     (t 0))))		; unknown error type
	   (cond
	     ((eq result-flag 1) nil) ; success
	     ((eq result-flag 0)
	      #+development
	      (cerror "Error!" "Unknown g2-list insert expression action!")
	      (stack-error
		top-of-stack "Cannot insert ~NA into ~NF."
		element-1-arg g2-list))
	     (t
	      (write-stack-error
		  top-of-stack
		(tformat
		  "Cannot insert ~NA ~a ~NA in ~NF."
		  element-1-arg insertion-type element-2-arg g2-list)
		(cond
		  ((eq result-flag -1)
		   ;; Before/After element not found error.
		   (tformat
		     "  ~NA is not an element of the g2-list."
		     element-2-arg))
		  ((eq result-flag -2)
		   ;; Duplicate element error.
		   (tformat
		     "  ~NA is already an element and the g2-list does not ~
                         allow duplicate elements."
		     element-1-arg)))))))))
    ;; If element-1-arg is an evaluation-value, it is added, not copied,
    ;; into the g2-list and so does not need to be reclaimed here.
    ;; Except in the following duplicate case with
    ;; ignore-duplicate-list-element-error enabled. - jpg 7/18/01
    (when no-insert-but-no-error?
      (reclaim-if-evaluation-value element-1-arg))
    (reclaim-if-evaluation-value element-2-arg)
    (reclaim-evaluation-symbol required-element-type-arg)
    (reclaim-evaluation-symbol insertion-type-arg)
    nil))



;;; Instruction 24, the `g2-list-insert-designation funcalled stack-instruction'
;;; takes a g2-list, a required-element-type, an item element, an
;;; insertion-type, and a second item element (or nil).  The instruction inserts
;;; the first element into the list at the indicated position.

;;; The second element is the element that is used in the before and after
;;; insertion-types to indicate the element position.  This arg can be nil if
;;; the insertion-type does not use this value.

;;; There are several insertion-types: beginning, end, before, and after.

;;; An error is signaled if:
;;;   the required element type is invalid for the g2-list element-type,
;;;   the element is invalid for the g2-list element-type,
;;;   the insert operation fails.

;;; G2-LIST-INSERT-DESIGNATION
;;;    (g2-list required-element-type element-item-1 insertion-type
;;;     element-item-2?)

;; Was procedure-instruction 57.

;; OPEN ISSUES:
;; 1.  Improve the speed of insert before and after into a list that does not
;; allow duplicate elements.  Traverse the list once looking for a duplicate
;; element, when necessary, and looking for the place to add the element.

(def-funcalled-instruction g2-list-insert-designation (24 (procedure inference) 5 0 nil
							  pprint-g2-list-insert-action)
  (let* ((g2-list (stack-arg 0))
	 (required-element-type-arg (stack-arg 1))
	 (required-element-type
	   (evaluation-symbol-symbol required-element-type-arg))
	 (list-element-type (list-type g2-list))
	 (element-1 (stack-arg 2))
	 (insertion-type-arg (stack-arg 3))
	 (insertion-type (evaluation-symbol-symbol insertion-type-arg))
	 (element-2? (stack-arg 4))
	 (no-insert-but-no-error? nil))
    (cond ((not (required-item-type-ok-for-g2-list-or-array-p 
		  required-element-type (list-type g2-list) t))
	   (stack-error
	     top-of-stack
	     "Cannot INSERT ~NA into the g2-list ~NF.  The element type of the ~
              list, ~a, conflicts with the required type, ~NV, specified in ~
              the action."
	     element-1 g2-list list-element-type required-element-type))
	  ((not (item-ok-for-g2-list-or-array-p element-1 list-element-type))
	   (stack-error
	     top-of-stack
	     "Cannot INSERT ~NA into the g2-list ~NF.  The type of this ~
              element conflicts with the list element type, ~a."
	     element-1 g2-list list-element-type))
	  ((eq insertion-type 'beginning)
	   (unless (or (g2-list-insert-at-beginning element-1 g2-list)
		       (setq no-insert-but-no-error?
			     (insert-action-duplicate-element-backward-compatibility-p)))
	     (stack-error
	       top-of-stack
	       "Cannot insert ~NA at the beginning of ~NF.  ~NA is already an ~
                element and the g2-list does not allow duplicate elements."
	       element-1 g2-list element-1)))
	  ((eq insertion-type 'end)
	   (unless (or (g2-list-insert-at-end element-1 g2-list)
		       (setq no-insert-but-no-error?
			     (insert-action-duplicate-element-backward-compatibility-p)))
	     (stack-error
	       top-of-stack
	       "Cannot insert ~NA at the end of ~NF.  ~NA is already an ~
                element and the g2-list does not allow duplicate elements."
	       element-1 g2-list element-1)))
	  (t
	   (let ((result-flag
		   (cond
		     ((eq insertion-type 'before)
		      (g2-list-insert-before element-1 element-2? g2-list nil))
		     ((eq insertion-type 'after)
		      (g2-list-insert-after element-1 element-2? g2-list nil))
		     (t 0))))		; unknown error type
	   (cond
	     ((eq result-flag 1) nil) ; success
	     ((eq result-flag 0)
	      #+development
	      (cerror "error!" "unknown g2-list insert designation action!")
	      ;; unknown error type
	      (stack-error
		top-of-stack "Cannot insert ~NA into ~NF."
		element-1 g2-list))
	     (t
	      (write-stack-error
		  top-of-stack
		(tformat
		  "Cannot insert ~NA ~a ~NA in ~NF."
		  element-1 insertion-type element-2? g2-list)
		(cond
		  ((eq result-flag -1)
		   ;; Before/After element not found error.
		   (tformat
		     "  ~NA is not an element of the g2-list."
		     element-2?))
		  ((eq result-flag -2)
		   ;; Duplicate element error.
		   (tformat
		     "  ~NA is already an element and the g2-list does not ~
                         allow duplicate elements."
		     element-1)))))))))
    ;; Don't reclaim element 1 here.  It is either an item or 
    ;; reclaimed above as part of a stack-error.
    ;; Except in the following duplicate case with
    ;; ignore-duplicate-list-element-error enabled. - jpg 7/18/01
    (when no-insert-but-no-error?
      (reclaim-if-evaluation-value element-1))
    (reclaim-evaluation-symbol required-element-type-arg)
    (reclaim-evaluation-symbol insertion-type-arg)
    (reclaim-if-evaluation-value element-2?)
    nil))



;;; Instruction 71, the `g2-list-insert funcalled stack-instruction' takes a
;;; g2-list, a new item-or-datum element, an existing item-or-datum element (or
;;; nil), and an insertion-type.  The instruction inserts the first datum into
;;; the list at the indicated position.

;;; The existing item-or-datum element is used with the "before" and "after"
;;; insert-types to indicate the element position.  This argument can be nil if
;;; the insertion-type does not use this value.

;;; There are several insertion-types: beginning, end, before, and after.

;;; An error is signaled if:
;;;   the element is invalid for the g2-list element-type,
;;;   the insert operation fails.

;;; This instruction was added in version 4.0 because we no longer require the
;;; grammar to specify the element-type of the g2-list.  This is determined at
;;; runtime.

;; At some point we may determine the element-type of the g2-list at compile
;; time, making use of the stable and dependent features.  - cpm, 11/12/93

;;; G2-LIST-INSERT
;;;    (g2-list new-item-or-value-element existing-item-or-value-element?
;;;     insertion-type)

;; OPEN ISSUES:

;; 1.  Improve the speed of "insert before" and "insert after" into a list that
;; does not allow duplicate elements.  Traverse the list once looking for a
;; duplicate element, when necessary, and looking for the place to add the
;; element.

(def-funcalled-instruction g2-list-insert (71 (procedure inference) 4 0 nil
					      pprint-g2-list-insert-item-or-value-action)
  (let* ((g2-list (stack-arg 0))
	 (list-element-type (list-type g2-list))
	 (new-element (stack-arg 1))
	 (existing-element? (stack-arg 2))
	 (insertion-type-arg (stack-arg 3))
	 (insertion-type (evaluation-symbol-symbol insertion-type-arg))
	 (no-insert-but-no-error? nil))
    (cond ((not (g2-list-or-array-element-ok-p new-element list-element-type))
	   (stack-error
	     top-of-stack
	     "Cannot INSERT ~NA into the g2-list ~NF.  The type of this ~
              element conflicts with the list element type ~a."
	     new-element g2-list (list-type g2-list)))
	  ((eq insertion-type 'beginning)
	   (unless (or (g2-list-insert-at-beginning new-element g2-list)
		       (setq no-insert-but-no-error?
			     (insert-action-duplicate-element-backward-compatibility-p)))
	     (stack-error
	       top-of-stack
	       "Cannot insert ~NA at the beginning of ~NF.  ~NA is already an ~
                element and the g2-list does not allow duplicate elements."
	       new-element g2-list new-element)))
	  ((eq insertion-type 'end)
	   (unless (or (g2-list-insert-at-end new-element g2-list)
		       (setq no-insert-but-no-error?
			     (insert-action-duplicate-element-backward-compatibility-p)))
	     (stack-error
	       top-of-stack
	       "Cannot insert ~NA at the end of ~NF.  ~NA is already an ~
                element and the g2-list does not allow duplicate elements."
	       new-element g2-list new-element)))
	  (t
	   (let ((result-flag
		   (cond
		     ((eq insertion-type 'before)
		      (g2-list-insert-before
			new-element existing-element? g2-list nil))
		     ((eq insertion-type 'after)
		      (g2-list-insert-after
			new-element existing-element? g2-list nil))
		     ((eq insertion-type 'before-element)
		      (g2-list-insert-before
			new-element existing-element? g2-list t))
		     ((eq insertion-type 'after-element)
		      (g2-list-insert-after
			new-element existing-element? g2-list t))
		     (t 0))))		; unknown error type
	   (cond
	     ((eq result-flag 1) nil) ; success
	     ((eq result-flag 0)
	      #+development
	      (cerror "Error!" "Unknown g2-list insert expression action!")
	      (stack-error
		top-of-stack "Cannot insert ~NA into ~NF."
		new-element g2-list))
	     (t
	      (write-stack-error
		  top-of-stack
		(tformat
		  "Cannot insert ~NA ~a ~NA in ~NF."
		  new-element insertion-type existing-element? g2-list)
		(cond
		  ((eq result-flag -1)
		   ;; Before/After element not found error.
		   (cond ((memq insertion-type '(before-element after-element))
			  (tformat
			    " index ~NA does not designate an element of the g2-list."
			    existing-element?)
			  )
			 (t
			  (tformat
			    "  ~NA is not an element of the g2-list."
			    existing-element?))))
		  ((eq result-flag -2)
		   ;; Duplicate element error.
		   (tformat
		     "  ~NA is already an element and the g2-list does not ~
                         allow duplicate elements."
		     new-element)))))))))
    ;; If new-element is an evaluation-value, it is added, not copied,
    ;; into the g2-list and so does not need to be reclaimed here.
    ;; Except in the following duplicate case with
    ;; ignore-duplicate-list-element-error enabled. - jpg 7/18/01
    (when no-insert-but-no-error?
      (reclaim-if-evaluation-value new-element))
    (reclaim-if-evaluation-value existing-element?)
    (reclaim-evaluation-symbol insertion-type-arg)
    nil))



;;; Instruction 25, the `g2-list-remove-expression' funcalled stack-instruction'
;;; takes a g2-list, a required-element-type, removal-type, and a datum element
;;; (or nil).  The instruction removes an element from the list at the indicated
;;; position.  If the list or position is not valid for the list a warning is
;;; given.  There are several removal-types: first, last, and element.  The
;;; element arg is used in the "element" removal-type to indicate the element
;;; position.  This arg can be nil if the particular removal-type does not use
;;; this value.

;; Was procedure-instruction 58.

;; COMPILER-NOTE: this instruction is also used to remove the first and last
;; item from a g2-list!  See g2-list-remove-designation instruction.

;; OPEN ISSUES:
;; 1. Give a warning when removing first or last element and the list is empty.

;;; G2-LIST-REMOVE-EXPRESSION 
;;;    (g2-list required-element-type removal-type element?)

(def-funcalled-instruction g2-list-remove-expression (25 (procedure inference) 4 0 nil
							 pprint-g2-list-remove-action)
  (let* ((g2-list (stack-arg 0))
	 (required-element-type-arg (stack-arg 1))
	 (removal-type-arg (stack-arg 2))
	 (element-arg? (stack-arg 3))
	 (required-element-type 
	   (evaluation-symbol-symbol required-element-type-arg))
	 
	 (removal-type (evaluation-symbol-symbol removal-type-arg)))
    (cond ((not (g2-list-or-array-type-ok-p
		  required-element-type (list-type g2-list) t))
	   ;; Could be an element or item type.
	   (write-stack-error
	     top-of-stack
	     (twrite-string "Cannot REMOVE ")
	     (case removal-type
	       (first (tformat "the first ~a " required-element-type))
	       (second (tformat "the second ~a " required-element-type))
	       (element (tformat "~NA " element-arg?))
	       (t (twrite-string "the element ")))
	     (tformat
	       "from ~NF.  The element type, ~a, conflicts with ~a ~
                the element-type of the g2-list."
	       g2-list required-element-type (list-type g2-list))))
	  (t
	   (case removal-type
	     (first (g2-list-remove-first g2-list required-element-type))
	     (last (g2-list-remove-last g2-list required-element-type))
	     (element
	      (cond ((not (datum-ok-for-g2-list-or-array-p
			    element-arg? (list-type g2-list)))
		     (stack-error
		       top-of-stack
		       "Cannot REMOVE ~NA from the g2-list ~NF.  The type of ~
                        this element conflicts with the list element type, ~a."
		       element-arg? g2-list (list-type g2-list)))
		    ((null (g2-list-remove element-arg? nil  g2-list))
		     (stack-error
		       top-of-stack
		       "Cannot REMOVE element ~NA from ~NF.  This element is not in the ~
                        g2-list."
		       element-arg? g2-list))
		    ;; Else, Successfully removed the element!
		    ))
	     ('remove-element
	      (g2-list-remove element-arg? t g2-list))
	     #+development
	     (t (cerror "Error!" "Unknown g2-list remove expression action!")))))
    (reclaim-evaluation-symbol required-element-type-arg)
    (reclaim-evaluation-symbol removal-type-arg)
    (reclaim-if-evaluation-value element-arg?)
    nil))







;;; Instruction 26, the `g2-list-remove-designation funcalled stack-instruction'
;;; takes a g2-list, a required-element-type, removal-type, and a datum element
;;; (or nil).  The instruction removes the indicated item from the list.  If the
;;; list or position is not valid for the list, a warning is given.

;;; Note, that the removal-type arg may not be needed.  If the first or last
;;; element needs to be removed, the instruction g2-list-remove-expression
;;; should be used.

;; Was procedure-instruction 59.

;; COMPILER NOTE: When the removal-type is first or last, compile into
;; g2-list-remove-expression!

;;; G2-LIST-REMOVE-DESIGNATION (g2-list required-element-type removal-type item)

(def-funcalled-instruction g2-list-remove-designation (26 (procedure inference) 4 0 nil
							  pprint-g2-list-remove-action)
  (let* ((g2-list (stack-arg 0))
	 (required-element-type-arg (stack-arg 1))
	 (removal-type-arg (stack-arg 2))
	 (element-item (stack-arg 3))
	 (required-element-type
	   (evaluation-symbol-symbol required-element-type-arg))
	 (removal-type (evaluation-symbol-symbol removal-type-arg)))
    (cond ((not (required-item-type-ok-for-g2-list-or-array-p
		  required-element-type (list-type g2-list) t))
	   (write-stack-error
	       top-of-stack
	     (twrite-string "Cannot REMOVE ")
	     (case removal-type
	       (element (tformat "~NA " element-item))
	       ;; First and second should not happen here.
	       (first (tformat "the first ~a " required-element-type))
	       (second (tformat "the second ~a " required-element-type))
	       (t (twrite-string "the element ")))
	     (tformat
	       "from ~NF.  The element type, ~a, conflicts with ~a ~
                the element-type of the g2-list."
	       g2-list required-element-type (list-type g2-list))))
	  ((eq removal-type 'element)
	   (cond ((not (item-ok-for-g2-list-or-array-p
			 element-item (list-type g2-list)))
		  (stack-error
		    top-of-stack
		    "Cannot REMOVE ~NA from the g2-list ~NF.  The type of ~
                        this element conflicts with the list element type, ~a."
		    element-item g2-list (list-type g2-list)))
		 ((null (g2-list-remove element-item nil g2-list))
		  (stack-error
		    top-of-stack
		    "Cannot REMOVE ~NA from ~NF.  This element is not in the ~
                        g2-list."
		    element-item g2-list))
		 ;; Else, Successfully removed the element!
		 (t nil)))
	  ((eq removal-type 'first)
	   #+development
	   (cerror
	     "Error!"
	     "Unused removal types in g2-list-remove-designation action!")
	   (g2-list-remove-first g2-list required-element-type))
	  ((eq removal-type 'last)
	   #+development
	   (cerror
	     "Error!"
	     "Unused removal types in g2-list-remove-designation action!")
	   (g2-list-remove-last g2-list required-element-type))
	  #+development
	  (t (cerror "Error!" "Unknown g2-list remove designation action!")))
    (reclaim-evaluation-symbol required-element-type-arg)
    (reclaim-evaluation-symbol removal-type-arg)
    nil))



;;; Instruction 72, the `g2-list-remove funcalled stack-instruction' takes a
;;; g2-list, an item-or-value element (or nil), an element-type (or nil), and a
;;; removal-type.  It removes the specified element or the element of the given
;;; element-type at the indicated position.  An error is signaled if the
;;; position is not valid, the element-type conflicts with the list type, or if
;;; the element is not found.

;;; The element-type argument indicates the type of the value to remove from the
;;; list.  This argument can be NIL, when the element item-or-value argument is
;;; provided.

;;; There are several removal-types: FIRST, LAST, and ELEMENT.

;;; When the removal-type is ELEMENT, the element argument must be non-NIL.  The
;;; element indicates which item-or-value to remove from the list.

;;; Cases:
;;;   Remove the FIRST element of the given element-type.
;;;   Remove the LAST element of the given element-type.
;;;   Remove the given ELEMENT.

;; Open Issues:
;; 1. Give a warning (or error) when removing first or last element and the list
;; is empty.

;;; The commented out code involving remove-succeeded-p is a fix for bug
;;; HQ-727347.  However, I'm afraid it would break old kbs.  The bug is that
;;; (for example) if you say, "remove the first integer from my-list", and
;;; my-list is a non-empty list capable of holding integers, but in fact it
;;; doesn't have any integers in it, then no error is thrown.  We can easily
;;; detect the failure, since g2-list-remove-first and g2-list-remove-last both
;;; return t for success and nil for failure.  Then, we can throw a stack error
;;; if we want go.  The code to generate the error is immediately below:
;      (when (and required-element-type?
;		 (not remove-succeeded-p))
;	(write-stack-error
;	    top-of-stack
;	  (twrite-string "Cannot REMOVE ")
;	  (case removal-type
;	    (first (tformat "the first ~a " required-element-type?))
;	    (second (tformat "the second ~a " required-element-type?))
;	    (element (tformat "~NA " element-arg?))
;	    (t (twrite-string "the element ")))
;	  (tformat
;	    "from ~NF.  There are no elements of type ~a in the g2-list."
;	    g2-list required-element-type?)))

;;; G2-LIST-REMOVE (g2-list item-or-value-element? element-type? removal-type)

(def-funcalled-instruction g2-list-remove (72 (procedure inference) 4 0 nil
					      pprint-g2-list-remove-item-or-value-action)
  (let* ((g2-list (stack-arg 0))
	 (element-arg? (stack-arg 1))
	 (required-element-type-arg? (stack-arg 2))
	 (required-element-type?
	   (and required-element-type-arg?
		(evaluation-symbol-symbol required-element-type-arg?)))
;	 (remove-succeeded-p t)
	 (removal-type-arg (stack-arg 3))
	 (removal-type (evaluation-symbol-symbol removal-type-arg)))
    (when (and required-element-type?
	       (not (g2-list-or-array-type-ok-p
		      required-element-type? (list-type g2-list) t)))
      ;; Could be an element or item type.
      (write-stack-error
	  top-of-stack
	(twrite-string "Cannot REMOVE ")
	(case removal-type
	  (first (tformat "the first ~a " required-element-type?))
	  (second (tformat "the second ~a " required-element-type?))
	  (element (tformat "~NA " element-arg?))
	  (t (twrite-string "the element ")))
	(tformat
	  "from ~NF.  The element type, ~a, conflicts with ~a ~
           , the element-type of the g2-list."
	  g2-list required-element-type? (list-type g2-list))))
    (case removal-type
      (first
       ;; (setq remove-succeeded-p ...)
       (g2-list-remove-first g2-list required-element-type?))
      (last
       ;; (setq remove-succeeded-p ...)
       (g2-list-remove-last g2-list required-element-type?))
      (element
       (unless (g2-list-or-array-element-ok-p
		 element-arg? (list-type g2-list))
	 (stack-error
	   top-of-stack
	   "Cannot REMOVE ~NA from the g2-list ~NF.  The type of ~
            this element conflicts with the list element type, ~a."
	   element-arg? g2-list (list-type g2-list)))
       (unless (g2-list-remove element-arg? t g2-list)
	 (stack-error
	   top-of-stack
	   "Cannot REMOVE element ~NA from ~NF, as it is not in the ~
            g2-list."
	   element-arg? g2-list)))
      (element-position
       (unless (g2-list-remove element-arg? 'element-position g2-list)
	 (stack-error
	   top-of-stack
	   "Cannot REMOVE item at index ~NA from the g2-list ~NF, as there is ~
            no item at that index"
	   element-arg? g2-list ))
       nil)
      #+development
      (t (cerror "Error!" "Unknown g2-list remove expression action!")))
    ;; check remove-succeeded-p here (see comment above)
    (reclaim-if-evaluation-value required-element-type-arg?)
    (reclaim-evaluation-symbol removal-type-arg)
    (reclaim-if-evaluation-value element-arg?)
    nil))



;;; The `NUPEC synchronize funcalled stack-instruction' is used to execute a
;;; synchronization operation in the NUPEC specific enhancements to G2.  Note
;;; that this needs to subvert the stuff which checks for a procedure hogging
;;; the processor, since the system will be within this instruction for quite
;;; some time.  Also, if this instruction is executed in a non-NUPEC version of
;;; G2, then a procedure error should be given.

;; Was procedure-instruction 60.

;;; This is a special-form action since it takes a variable number of arguments.
;;; Arg-count is the first stack argument and is the count of additional stack
;;; arguments including the first (which is the arg-count itself).

;;;   NUPEC-SYNCHRONIZE (g2-to-g2-object {item} class-list arg-count)

;; This action is now implemented as a stack instruction since it may need to
;; access the class list argument directly from the constant-vector.

;; Funcalled-instruction number 27 is no longer used here.




;;; Instruction 28, the `create explanation funcalled stack-instruction' is used
;;; to create explanations (transient objects) for variables or parameters.  It
;;; takes a designation which returns a variable or parameter, and it takes a
;;; possible var spot for the new explanation.  It should create an instance of
;;; explanation, and assign it to the local var spot, if supplied.  This
;;; instruction creates an explanation for variables or parameters regardless of
;;; whether they are caching explanations.  (Those that do not cache
;;; explanations, will have an explanation that consists of the object itself.)

;; Was procedure-instruction 61.

;; COMPILER NOTES:
;; 1. The return value is left on the stack.  If a var-spot is
;; provided, the POP-INTO-LOCAL-VAR instruction should used to put the value
;; into the var-spot.  If the value is not used it should be popped off the
;; stack.
;; 2. Compile with a check for variable-or-parameter.

;; OPEN ISSUE:
;; 1. Rule non-stack action gave a warning when attempting to bind a
;; created instance into a non-inorder rule binding.

;;;   CREATE-EXPLANATION (variable-or-parameter)

(def-funcalled-instruction create-explanation (28 (procedure inference) 1 1 nil
						  pprint-create-explanation-action)
  ;; No longer need NUPEC authorization for this. -dkuznick, 7/15/98
; (unless (nupec-authorized-p)
;    (stack-error
;      top-of-stack
;      "This knowledge base was written in a NUPEC enhanced ~
;       version of G2, but this version of G2 is not enhanced ~
;       for NUPEC.  The create NUPEC explanation instruction cannot ~
;       be executed."))
  (error-if-simulation-procedure "CREATE-EXPLANATION" top-of-stack)

  (setf (svref local-stack top-of-stack)
	(create-explanation (stack-arg 0)))
  nil)



;;; Instruction 29, the `update instruction' is used to update displays (charts,
;;; readout-tables, graphs, etc.).  If the item argument is not one of these
;;; displays, a stack error is issued.

;;;   UPDATE (display)

;; Was procedure-instruction 62.

(def-funcalled-instruction update (29 (procedure inference) 1 0 nil
				      pprint-update-action)
  (let ((frame-to-update (stack-arg 0))) 
    (cond
      ((variable-p frame-to-update)
       (attempt-new-variable-value-collection
	 frame-to-update priority-of-current-task t))
      ((or (kind-of-cell-based-display-p frame-to-update)
	   (frame-of-class-p frame-to-update 'freeform-table))
       (schedule-g2-cell-array-update frame-to-update)
       (when (frame-of-class-p frame-to-update 'trend-chart)
	 (update-trend-chart frame-to-update t nil t)))
      ((kind-of-display-p frame-to-update)              ; graphs, digital clocks
                                                        ; force update even if hidden
       (funcall-method 'update-display frame-to-update nil nil t)) 
      ((frame-of-class-p frame-to-update 'chart)
       (update-chart frame-to-update))
      (t
       (stack-error
	 top-of-stack
	 "Cannot update ~NF, can only update kinds of displays."
	 frame-to-update)))
    nil))

;; Schedule-expression-cell-execution may fail to find an expression cell.
;; Currently, no error is issued if this happens; the task is just not scheduled.
;; This should eventually be improved.  - AGH 9/3/91



;;; Instruction 51, the `create connection instruction' was used to create a
;;; new connection.

;; Was procedure-instruction 63.

;;;   CREATE-CONNECTION (class-expression connection-specification var-spot?)

;; This action is now implemented as a stack instruction since it may need to
;; access the vertices argument directly from the constant-vector.  If the
;; vertices value is a constant, it may not be put on the stack since it is a
;; lisp form (i.e.g, a list of numbers).




;;; Instruction 30, the `START instruction' takes a designation, an
;;; argument list, an optional overriding priority expression, and an optional
;;; wait interval expression.  This statement will cause the designated
;;; procedure to be invoked on the given arguments after the wait interval and
;;; at the given priority or at its default priority.  This procedure does not
;;; relinquish the processor after executing this statement.

;;; This instruction receives its arguments as follows.  The procedure to start
;;; is the first argument, followed by any arguments to the procedure.  Next
;;; there is a count of the number of arguments to the procedure, a priority or
;;; NIL, and a wait interval or NIL.

;;; Note that the START instruction should signal an error if executed within a
;;; simulation procedure.

;;;   START (procedure arguments... argument-count priority? wait?)

(def-funcalled-instruction start (30 (procedure inference) (+ (0) 3) 0 nil
				     pprint-start-action)
  (let* ((stack-argument-count (stack-arg 2))
	 (argument-count (-f stack-argument-count 3))
	 (priority? (stack-arg 0))
	 (wait? (stack-arg 1))
	 (top-of-arguments-index (-f top-of-stack 3))
	 (procedure-stack-index (-f top-of-arguments-index argument-count))	 
	 (procedure (svref local-stack procedure-stack-index))
	 (new-code-body-invocation nil))

    (unless (or (null priority?)
		(and (>=f priority? 1) (<=f priority? 10)))
      (stack-error
	top-of-stack
	"Cannot start procedure ~NF at priority ~a.  The priority must be in ~
         the range 1 to 10."
	procedure priority?))

    ;; Need to copy wait? because it gets "owned" by
    ;; start-procedure-invocation-in-place, but we need the value for the trace
    ;; message -dkuznick, 8/22/01
    (let ((wait-copy? (copy-if-evaluation-value wait?)))
      (setq new-code-body-invocation
	    (start-procedure-invocation-in-place
	      procedure priority? wait?
	      local-stack top-of-arguments-index argument-count
	      nil nil
	      top-of-stack
	      nil 'start))
      (prog1 (if (error-text-p new-code-body-invocation)
		 new-code-body-invocation
		 (progn
		   (write-major-trace-message
		     (setq forgive-long-procedure-instruction? t)
		     (twrite-string "Starting procedure ")
		     (write-procedure-invocation-instance-from-slot
		       (procedure-invocation-of-code-body new-code-body-invocation) nil)
		     (when wait-copy?
		       (twrite-string " after ")
		       (print-constant wait-copy? 'seconds))
		     (when priority?
		       (tformat " at priority ~a" priority?))
		     (twrite-string "."))
		   nil))
	(reclaim-if-evaluation-value wait-copy?)))))


;;; Instruction 31, the `START-RPC instruction' is like START, except that
;;; instead of a procedure, it should take a remote procedure declaration, and
;;; it takes an icp-interface object as an argument on the stack after the wait?
;;; argument.

;;;   START-RPC (remote-procedure arguments...  argument-count priority? wait?
;;;              icp-interface)

(def-funcalled-instruction start-rpc (31 (procedure inference) (+ (0) 4) 0 nil
					 pprint-start-rpc-action)
  (let* ((stack-argument-count (stack-arg 3))
	 (argument-count (-f stack-argument-count 4))
	 (priority? (stack-arg 0))
	 (wait? (stack-arg 1))
	 (icp-interface (stack-arg 2))
	 (top-of-arguments-index (-f top-of-stack 4))
	 (remote-procedure-stack-index
	   (-f top-of-arguments-index argument-count))
	 (remote-procedure (svref local-stack remote-procedure-stack-index))
	 (arguments
	   (prepare-procedure-argument-list-for-stack-procedure
	     remote-procedure local-stack top-of-arguments-index
	     argument-count t))
	 (new-top-of-stack (-f remote-procedure-stack-index 1)))

    (unless (or (null priority?)
		(and (>=f priority? 1) (<=f priority? 10)))
      (stack-error
	top-of-stack
	"Cannot start procedure ~NF across ~NF at priority ~a.  The priority ~
         must be in the range 1 to 10."
	remote-procedure icp-interface priority?))

    (cond ((or (g2-list-p icp-interface)
	       (g2-array-p icp-interface))
	   (cond ((=f 0 (if (g2-list-p icp-interface)
			    (g2-list-length icp-interface)
			    (g2-array-length icp-interface)))
		  (stack-error
		    top-of-stack
		    "~NF is a list or array that is not active, or has no elements, ~
                     and so cannot be used as a pathway for ~
                     a remote procedure call or remote procedure start."
		    icp-interface))
		 ((not (all-elements-ok-for-parallel-rpc-start icp-interface))
		  (stack-error
		    top-of-stack
		    "~NF contained an element without the capability G2-TO-G2-DATA-INTERFACE or ~
                     GSI-INTERFACE, and so cannot be used as a pathway for ~
                     a remote procedure call or remote procedure start."
		    icp-interface))))			   
	  ((not (or (g2-to-g2-data-interface-p-function icp-interface)
		    (gsi-interface-p-function icp-interface)))

	   (stack-error
	     top-of-stack
	     "~NF did not have the capability G2-TO-G2-DATA-INTERFACE or ~
         GSI-INTERFACE, and so cannot be used as a pathway for ~
         a remote procedure call or remote procedure start."
	     icp-interface)))
    
    (write-major-trace-message
      (setq forgive-long-procedure-instruction? t)
      (tformat
	"Starting remote procedure ~NF("
	remote-procedure)
      (write-procedure-argument-list arguments)
      (tformat ") across ~NF" icp-interface)
      (when wait?
	(tformat " after ~NC" wait? 'seconds))
      (when priority?
	(tformat " at priority ~a" priority?))
      (twrite-string "."))

    (start-remote-procedure
      remote-procedure icp-interface arguments
      wait? priority? new-top-of-stack)				       

    nil))




;;; NOTE THAT FUNCALLED INSTRUCTIONS NUMBERS 32-37 ARE DEFINED IN STACK-EVAL.
;;; cpm, 6/17/91




;;; The `abort instruction' is used to abort a procedure invocation or all
;;; invocations of a procedure.

;; Since this is a new action in G2 version 3.0, there is no corresponding
;; procedure-instruction.

;;; ABORT (procedure-or-procedure-invocation)

(def-funcalled-instruction abort (38 (procedure inference) 1 0 nil
				     pprint-abort-action)
  (abort-procedure-invocation (stack-arg 0))
  nil)


;;; The `shut down G2 instruction' is used to shut down G2 from a rule or
;;; procedure.  Before the shut down, G2 is reset.  This causes the currently
;;; executing task and all currently executing procedures to be aborted.  The
;;; aborted procedures execute any "on exit" code.  Also, any open files are
;;; closed on reset.  After shut down, the process completes and control returns
;;; to the operating system.

;; Since this is a new action in G2 version 3.0, there is no corresponding
;; procedure-instruction.

;;; SHUT-DOWN-G2 ()

(def-funcalled-instruction shut-down-g2 (39 (procedure inference) 0 0 nil
					    pprint-shut-down-g2-action)
  (declare (ignore local-stack top-of-stack))
  (system-pause)
  (shut-down-ab-process 'requested)
  nil)




;;; The `reset kb instruction' and `pause kb instruction' are implemented as
;;; stack-instructions since they need to "go exit-stack-eval".

;;;    RESET KB ()
;;;    PAUSE KB ()




;;; The `create by cloning funcalled stack-instruction' is used to create
;;; transient items by cloning.  It takes a symbol naming a class and an item to
;;; clone.  The newly cloned item is pushed onto the stack.

;; OPEN ISSUE: Rule non-stack create action gave a warning when attempting to
;; bind a created instance into a non-inorder rule binding.

;; COMPILER NOTE: The return value is left on the stack.  If a var-spot is
;; provided, the POP-INTO-LOCAL-VAR instruction is used to put the value into
;; the var-spot.  If the value is not used it is popped off the stack.

;;;   CREATE-BY-CLONING (class-name, item)

(def-funcalled-instruction create-by-cloning (40 (procedure inference) 2 1 nil
						 pprint-create-by-cloning-action)
  (let* ((class-evaluation-symbol (stack-arg 0))
	 (class (evaluation-symbol-symbol class-evaluation-symbol))
	 (item-to-clone (stack-arg 1))
	 (cloned-item?
	   (create-by-cloning-action-internal
	     class item-to-clone top-of-stack t)))
    ;;; We believe cloned-item? cannot be nil. 
    (setq top-of-stack (-f top-of-stack 1))
    (setf (svref local-stack top-of-stack) cloned-item?)
    (reclaim-evaluation-symbol class-evaluation-symbol)
    nil))

;;; `create-by-cloning-action-internal' returns the newly created clone
;;; or throws stack-error.

(defun-simple create-by-cloning-action-internal (class item-to-clone
						       top-of-stack
						       validate-environment-p)
  (let ((class-description? (class-description class))
	(newly-cloned-item? nil))
    (cond
      ((null class-description?)
       (stack-error top-of-stack "~a is not a defined class." class))
      ((not (class-can-be-transient-p class-description?))
       (if (subclassp class 'item)
	   (stack-error
	     top-of-stack
	     "Attempted to create an instance of ~a, but this class ~
                is not allowed to be created transiently."
	     class)
	   (stack-error top-of-stack "~a is not a defined class." class)))
      ((not (class-can-be-transient-p (class-description-slot item-to-clone)))
       (stack-error
	 top-of-stack
	 "Attempted to create an instance of ~a, but this class ~
            is not allowed to be created transiently."
	 (class item-to-clone)))
      ((or (subclassp class 'connection)
	   (of-class-p item-to-clone 'connection))
       (stack-error
	 top-of-stack
	 "When creating transient instances of a subclass ~
            of connection, you must not clone it and must use the additional ~
            CONNECTED grammar to initially connect it to something."
	 class))
      ;; GENSYMCID-1221: Status of TW_Mgr module in Integrity v5
      ((or (not (frame-system-operation-is-allowed-p 'clone-block item-to-clone))
	   (frame-of-class-p item-to-clone 'procedure-invocation))
       ;; Item is restricted from being cloned.
       (stack-error
	 top-of-stack
	 "Cannot create an item by cloning ~NF.  The clone action has been ~
            restricted for this item."
	 item-to-clone))
      (t
       ;; Clone a new item and mark the item and all inferior objects and
       ;; subworkspaces transient.
       (setq newly-cloned-item? (clone-frame item-to-clone))
       (cond (newly-cloned-item?
	      (set-transient-and-propagate newly-cloned-item? nil)
	      (funcall-method-macro
		'activate-if-possible-and-propagate newly-cloned-item?)
	      (prog1 newly-cloned-item?
		(when validate-environment-p
		  (update-current-computation-instance-frame-serial-number))))
	     (t
	      (stack-error
		top-of-stack
		"Error in CREATE BY CLONING of ~NF." item-to-clone)))))))




;;; System Procedure Functions Used by G2-Clone and G2-Initialize-For-Clone


;;; The system-procedure function `g2-attributes-and-classes-to-clone'
;;; determines which attributes of an item require cloning initialization.  This
;;; function returns a sequence of structs, with each struct containing three
;;; fields, a class-name, attribute-name, and original subobject.  The suboject
;;; is the object, within the attribute, that should be cloned as part of the
;;; new item.  Note that the sequence is empty if there are not attributes to
;;; clone.

;;; NOTE that the two argument arguments must be of the same class and that the
;;; attributes requiring clone initialization in the new-item must already
;;; contain a subobject in the original item.

(declare-system-procedure-function g2-attributes-and-classes-to-clone t)

(defun g2-attributes-and-classes-to-clone (new-item old-item)
  (let* ((class-description
	   (class-description-slot new-item))
	 (slot-descriptions
	   (slot-descriptions class-description))
	 (pre-sequence nil))
    (loop for slot-description in slot-descriptions
	  as slot-name = (pretty-slot-name slot-description)
	  as slot-init-form? = (slot-init-form slot-description)
	  as slot-value? = (get-slot-description-value-macro
			     new-item slot-description)
	  as old-slot-value? =
   	     (get-slot-description-value-macro
	       old-item slot-description) ; Okay to new-frame slot-description.
	  do
      ;; The following predicates are similar to that in clone-frame, when
      ;; interating over the slot-descriptions.
      (when (and (null slot-value?)
		 old-slot-value?
		 (not (feature-assq
			'do-not-clone (slot-features slot-description)))
		 (slot-description-is-of-savable-slot-p slot-description)
		 (not (eq old-slot-value? slot-init-form?))
		 (of-class-p old-slot-value? 'item))
	  (eval-push
	    (allocate-evaluation-structure-inline
	      'class-name (class old-slot-value?)
	      'attribute-name slot-name
	      'attribute-value old-slot-value?)
	    pre-sequence)))
    (allocate-evaluation-sequence
      (nreverse pre-sequence))))

;; Note that this function borrows from AJS's code for the function
;; g2-attributes-and-classes-to-initialize.  Note that the above function
;; returns a diffent structure.  - cpm, 11/13/96



;;; The system procedure `g2-post-clone-interaction' is similar to
;;; g2-post-create-interaction, in that if this is an interactive operation (in
;;; this case, clone) and it will attach the item to the mouse.  But, unlike the
;;; "create" version of this function, it does not test whether an editing
;;; context needs to be created.  A manual clone operation does not currently
;;; launch an editor.

(declare-system-procedure-function g2-post-clone-interaction t)

(defun g2-post-clone-interaction (new-item details)    
  (with-unleashed-and-verified-structure-args
      (details
	t
	((clone-interactively (or boolean (class g2-window)))
	 (x-in-window integer)
	 (y-in-window integer)))
    (invoke-rules-for-existential-chaining new-item 'is-created nil)
    (if (and clone-interactively
	     (framep clone-interactively))
	(let ((class? (class new-item))
	      (workstation? (workstation-for-g2-window?
			      clone-interactively)))
	  (when workstation?
	    (for-workstation (workstation?)
	      (cond ((and class?
			  (subclassp class? 'kb-workspace))
		     ;; Cloned workspace does not get attached to the mouse.
		     (put-workspace-on-pane
		       new-item
		       current-workstation-detail-pane
		       'center 'center
		       nil))
		    (t
		     (when (and x-in-window y-in-window)
		       (manifest-item-creation
			 new-item nil x-in-window y-in-window))))))))))

;; IMPORTANT NOTE: review AJS's note in g2-post-create-interaction that indicates that
;; these functions will no longer be necessary when a number of G2 structure
;; access bugs have been fixed.  - cpm, 11/13/96



;;; The `make-permanent action' is used to make a transient item, every subobject,
;;; and all items on subworkspaces permanent.  Permanent means that the object and
;;; its descendants are no longer transient and will not be deleted on reset, and
;;; that kb state changes for the affected items are not undone on reset.  Dynamic
;;; changes which are not kb state changes, such as the current value of a
;;; variable, are not made permanent.

;;;   (MAKE-PERMANENT item)

;; jh, 8/14/91.  Implemented make-permanent action.  Manual test is in
;; ma:>jh>kb>make-permanent.kb.  No player or regression test exists as yet.

;; cpm, 1/13/92.  The item argument must either be a kb-workspace or an item
;; that is on a kb-workspace or has a superior that is on a kb-workspace.  This
;; prevents G2 from having permanent objects in limbo, not on a kb-workspace.
;; These newly permanent orphans were not being saved in KB's.

;; cpm, 1/15/92.  Now follows proprietary kb restrictions.

;; cpm, 1/15/92.  This action is restricted in the runtime and embedded versions
;; of G2.

;; cpm, 1/22/92.  Ok, for transient definitions.  Possibly, change the
;; incomplete status to complete for this definition and other transient
;; definitions in the kb-hierarchy to complete.  Note that we do not need to
;; test for transient superior classes, since transient definitions cannot have
;; subclasses.

;; ben, 4/19/92. Revised guards to move more into the frame-system-operation-is-allowed-p
;; check.  Moved the runtime restriction into that check, and changed the operation
;; being checked from change-permanence (no obsolete) to make-transient.  
;; See make-transient in FILTERS for additional details.

(def-funcalled-instruction make-permanent (41 (procedure inference) 1 0 nil
					      pprint-make-permanent-action)
  (let* ((item (stack-arg 0)))
    (make-permanent-action-internal item top-of-stack)
    nil))

(defun-void make-permanent-action-internal (item top-of-stack)
  (let ((top-level-parent-frame? (loop for child? = item then parent?
				       for parent? = (parent-frame child?)
				       until (null parent?)
				       finally
					 (return child?))))
    (cond ((parent-is-transient-p item)
	   (stack-error
	     top-of-stack
	     "Cannot make ~NF permanent.  The superior of this item is transient."
	     item))
	  ((and (not (transient-p item))
		(not (permanent-block-p item)))
	   (stack-error
	     top-of-stack
	     "Cannot make ~NF permanent.  It must be either transient ~
              or permanent to begin with." item))
	  ((and (not (frame-of-class-p item 'connection))
		(null (get-workspace-if-any (or top-level-parent-frame? item)))
		(not (permanent-block-p item)))
	   (stack-error
	     top-of-stack
	     "Cannot make ~NF permanent.  It is must be either a kb-workspace ~
              or found on a kb-workspace or permanent to begin with."
	     item))
	  ((frame-of-class-p item 'procedure-invocation)
	   (stack-error
	     top-of-stack
	     "~NF cannot be made permanent because it is a ~
              procedure-invocation."
	     item))
	  ((not (frame-system-operation-is-allowed-p 'make-permanent item))
	   ;; The item is restricted from being made permanent.  Currently, it
	   ;; is not possible for a transient item to be on a restricted
	   ;; workspace.  But, this action can be making a permanent item
	   ;; permanent so as to undo the kb-state changes.
	   (stack-error
	     top-of-stack
	     "Cannot make ~NF permanent.  The make permanent action has been ~
              restricted for this item."
	     item))
	  (t
	   (set-permanent-and-propagate item nil)
	   (remove-kb-state-changes item)))))

;; Added the clause "or permanent to begin with" to the error message.  And
;; added the logic to make it so.  Clearly, something that's already permanent
;; can be made permanent, which at worst does nothing and at best allows
;; change-the-text-of changes to be made permanent.  Crucial for online module
;; editing.  Presumably, all items that pass this test are instances of
;; system-table.  Note that I do not here deal with the problem of making
;; default-junction subclass definitions permanent.  That's a problem for
;; another day!  (MHD 5/31/95)

;; The call on remove-kb-state-changes looks like it is redundent.  I think that
;; set-permanent-and-propagate does it.  - ben 4/19/93


;;; `Parent-is-transient-p' returns non-nil if the parent (as defined in ML's
;;; Paper Trail memo on Saving KBs) of the given frame is transient.

(defun-simple parent-is-transient-p (frame)
  (let ((parents (parents frame)))
    (prog1
	(loop for parent in parents
	      thereis (transient-p parent))
      (reclaim-gensym-list parents))))

(defun-simple parent-is-neither-transient-nor-permanent-p (frame)
  (let ((parents (parents frame)))
    (prog1
	(loop for parent in parents
	      thereis (and (not (transient-p parent))
			   (not (permanent-block-p parent))))
      (reclaim-gensym-list parents))))

;;; The function `parents' returns a gensym-list of the blocks that
;;; the given frame is inferior to, in the sense of
;;; funcall-function-to-inferior-blocks.

(defun parents (frame)
  (let ((superblock? (superblock? frame)))
    (if superblock?
	(gensym-list superblock?)
	(let ((parent-frame? (parent-frame frame)))
	  (if parent-frame?
	      (gensym-list parent-frame?)
	      (frame-class-case frame
		(workspace 
		  (let ((parent-of-subworkspace? 
			  (parent-of-subworkspace? frame)))
		    (and parent-of-subworkspace?
			 (gensym-list parent-of-subworkspace?))))
		(simulation-subtable
		  (gensym-list (parent-variable frame)))
		(connection 
		  (let* ((connection-structure
			   (connection-for-this-connection-frame frame))
			 (input-object (input-end-object connection-structure))
			 (output-object (output-end-object connection-structure)))
		    (let ((possible-parents nil))
		      (unless (loose-end-p input-object)
			(gensym-push input-object possible-parents))
		      (unless (loose-end-p output-object)
			(gensym-push output-object possible-parents))
		      possible-parents)))))))))

;; I worry, but not much, that this isn't the exact inverse of
;; funcall-function-to-inferior-blocks. - ben 4/19/93



;;; The `make-subworkspace action' is used to make a transient kb-workspace the
;;; subworkspace of another item.  This workspace can either be a top-level
;;; workspace or already be the subworkspace of another item.  If the
;;; kb-workspace is already a subworkspace, it is first removed and not
;;; deactivated.  It is then added as a subworkspace of the item and activated
;;; or deactivated depending on whether the superior item is active or not.
;;; It is an error if the new superior item already has a subworkspace and it
;;; is not this subworkspace.

;;; This following description of the activation status of the new subworkspace
;;; is taken from an email message from jra dated 1/2/92.  "The activation
;;; status of the new subworkspace X is left unchanged, except if its old
;;; activation status is incompatible with its new location below Y in the
;;; object hierarchy of the KB.  There is only one case that can arise in which
;;; the activation status must be changed.  If the workspace (1) is a
;;; subworkspace of an object with the activatable subworkspaces capability, (2)
;;; the subworkspace is currently deactivated, and (3) the workspace is moved to
;;; be the subworkspace of a currently active object which does not have the
;;; activatable subworkspaces capability; then the subworkspace will be
;;; activated as a side effect of the make subworkspaces action."

;;; Note that the stack compiler emits instructions to test that the first
;;; argument is an instance of kb-workspace.

;;;   (MAKE-SUBWORKSPACE kb-workspace, item)

(def-funcalled-instruction make-subworkspace (42 (procedure inference) 2 0 nil
						 pprint-make-subworkspace-action)
  (let* ((kb-workspace (stack-arg 0))
	 (target-item (stack-arg 1)))
    (make-subworkspace-action-internal
      kb-workspace target-item top-of-stack)
    nil))

(defun-simple make-subworkspace-action-internal (kb-workspace target-item top-of-stack)
  (macrolet ((make-sws-error (format &rest args)
	       `(if disable-stack-error
		    (return-from make-subworkspace-action-internal
		      (tformat-text-string ,format ,@args))
		    (stack-error top-of-stack ,format ,@args))))
  (let* ((invalid-target-item?
	   (or (parent-frame target-item)	; attribute
	       (frame-of-class-p target-item 'simulation-subtable)
	       (frame-of-class-p target-item 'kb-workspace)
	       (frame-of-class-p target-item 'connection)
	       ;; Any other classes that can't have subworkspaces, e.g.,
	       ;; rules.
	       (not 
		 (get-slot-description-of-frame 'subworkspaces target-item))))
	 (dependency-problem?
	   (existence-depends-on-p target-item kb-workspace))
	 (current-item-subworkspace?
	   (and (not invalid-target-item?) (subworkspaces target-item))))
    (cond ((and (not (transient-p kb-workspace))
		(not permit-transfer-of-permanent-items-p))
	   (make-sws-error
	     "Cannot make ~NF the subworkspace of ~NF because ~NF is not ~
              transient."
	     kb-workspace target-item kb-workspace))
	  (invalid-target-item?
	   (if (parent-frame target-item)
	       (make-sws-error
		 "Cannot make ~NF a subworkspace of ~NF.  ~NF is an attribute ~
                  of ~NF."
		 kb-workspace target-item target-item
		 (parent-frame target-item))
	       (make-sws-error
		 "Cannot make ~NF a subworkspace of ~NF.  ~NF is a ~a."
		 kb-workspace target-item target-item (class target-item))))
	  (dependency-problem?
	   ;; There are two possible dependency problems related to the kb or
	   ;; class hierarchy.  In this action, the problem must be related to
	   ;; the kb-hierarchy.  The target item is on this workspace or a
	   ;; further subworkspace.  Note that the second problem, the class
	   ;; hierarchy dependency problem, cannot occur.  Since the workspace
	   ;; is transient, it is not possible to have a definition on this
	   ;; workspace with instances.  Transient definitions cannot have
	   ;; instances.
	   (make-sws-error
	     "Cannot make ~NF a subworkspace of ~NF because ~NF is either on ~
              this subworkspace or on a further subworkspace."
	     kb-workspace target-item target-item))
	  ((not (frame-system-operation-is-allowed-p 'change-superior kb-workspace))
	   ;; Kb-workspace is restricted from being made a subworkspace.
						       ;Currently, this case is
						       ;not possible.  The
						       ;kb-workspace must be
						       ;transient.  Therefore,
						       ;it cannot be restricted
						       ;because it is either not
						       ;on a workspace or can
						       ;not be transferred to a
						       ;restricted workspace.
						       ;Leave this test in, in
						       ;case this changes.  -
						       ;cpm, 1/15/92
	   (make-sws-error
	     "Cannot make ~NF the subworkspace of ~NF.  This action has been ~
              restricted for ~NF."
	     kb-workspace target-item kb-workspace))
	  ((not (frame-system-operation-is-allowed-p
		       'change-set-of-inferiors target-item))
	   ;; Target item is restricted from getting new inferior items.
	   (make-sws-error
	     "Cannot make ~NF the subworkspace of ~NF.  This action has been ~
              restricted for ~NF."
	     kb-workspace target-item target-item))
	  ((and current-item-subworkspace?
		(null (cdr current-item-subworkspace?)))
	   ;; If the item's subworkspace is already this kb-workspace, this
	   ;; action is a no-op.  Otherwise, an error is signaled.
	   (unless (eq (car current-item-subworkspace?) kb-workspace)
	     (make-sws-error
	       "Cannot make ~NF the subworkspace of ~NF because ~NF already ~
                has a subworkspace."
	       kb-workspace target-item target-item)))
	  (t (replace-subworkspace-if-any kb-workspace target-item)
	     nil)))))



;;; The `print action' is used to print the contents of a workspace, both
;;; kb-workspace and temporary workspace, to a postscript file.  A future version,
;;; may extend this to allow the printing of other types of items.  The type of
;;; the item argument is tested at here run-time, since the compiler cannot type
;;; test for superior classes of item.

;;;   (PRINT kb-workspace)

(def-funcalled-instruction print (43 (procedure inference) 1 0 nil
				     pprint-print-action)
  (let ((item (stack-arg 0)))
    (cond ((not (frame-of-class-p item 'workspace))
	   (stack-error
	     top-of-stack
	      "Cannot print ~NF because it is not a workspace."
	     item))
	  ((not (frame-system-operation-is-allowed-p 'show-workspace item))
	   ;; The item is restricted from being shown and so can't be printed.
	   (stack-error
	     top-of-stack
	     "Cannot print ~NF.  The print action has been restricted for this ~
              item."
	     item))
	  (t
	   (print-workspace-from-action item))))
  nil)



;;; `may-be-made-transient-p' is the test for allowing an item to be made
;;; transient by an action.  The item must be not transient.  Attributes,
;;; embedded rules and simulation-subtables may not be made transient since they
;;; can not be deleted by actions.

;; Added test that the item is on or is a kb-workspace.  This prevents making
;; permanent items in limbo, junction-blocks and g2-windows, transient.  - cpm &
;; ml 1/22/92

;; Added tests for definitions.  Checks if there is a subclass of the definition
;; or if there are instances of the definition.  Also checks these things for
;; any definitions inferior to this item in the kb-hierarchy.  - cpm, 1/22/92

(def-substitution-macro may-be-made-transient-p (item)
  (let* ((kb-hierarchy-problem?
	   (locate-definition-with-subclass-or-instance item)))
    (and (or (frame-of-class-p item 'message-board) ; see note below
	     (and (not (transient-p item))
		  (permanent-block-p item)
		  (not (frame-of-class-p item 'system-table))))
	 (not kb-hierarchy-problem?)
	 (not (embedded-rule-p item))
	 (not (frame-of-class-p item 'ui-client-session))
	 (not (frame-of-class-p item 'simulation-subtable)))))

;; Message-boards are neither permanent nor transient, yet they should
;; be deletable and non-savable.  Consider making them permanent and
;; exempting them from saving.  (ghw/mhd 3/18/96)




;;; The `make-transient action' is used to make a permanent item, every
;;; subobject, and all items on subworkspaces transient.  These items are no
;;; longer permanent and will be deleted on reset.  This action does not affect
;;; kb-state changes or dynamic values, such as current variable values, for any
;;; items.

;; cpm, 1/15/92.  Now follows proprietary kb restrictions.

;; cpm & ml, 1/22/92.  Added test that requires the item to be on a kb-workspace
;; or to be a kb-workspace.  This prevents the making transient of permanent
;; items in "limbo", such as junction-blocks and g2-windows.

;; cpm, 1/22/92.  Cannot make transient if this is either a permanent definition
;; with a subclass or instances.  This restriction applies to any definition in
;; the kb-hierarchy below this item.

;; In version 4.0, cannot make stable items transient.  - cpm, 2/25/94

;;;   (MAKE-TRANSIENT item)

(def-funcalled-instruction make-transient (44 (procedure inference) 1 0 nil
					      pprint-make-transient-action)
  (let ((item (stack-arg 0)))
    (make-transient-action-internal item top-of-stack)
    nil))


(defun make-transient-action-internal (item top-of-stack)
  (let* ((ok-to-be-made-transient? (may-be-made-transient-p item))
	 (currently-within-make-transient-instruction-p t))
    (cond ((not ok-to-be-made-transient?)
	   (make-transient-stack-error item top-of-stack))
	  ((not (frame-system-operation-is-allowed-p 'make-transient item))
	   ;; The item is restricted from being made transient.
	   (stack-error
	     top-of-stack
	     "Cannot make ~NF transient.  The make transient action has been ~
              restricted for this item."
	     item))
	  ((destabilizing-operation-restricted-for-item-p item)
	   (stack-error
	     top-of-stack
	     "Cannot make ~NF transient because it is a stable item."
	     item))
	  (t (set-transient-and-propagate item nil)))))


(defun-simple make-transient-stack-error (item top-of-stack)
  (cond ((transient-p item)
	 ;; If the item is already transient, we don't need to
	 ;; propagate to subblocks since permanent items cannot be
	 ;; subblocks of transient items.  This is a no-op.
	 nil)
	((parent-frame item)
	 (stack-error
	   top-of-stack
	   "Cannot make ~NF transient because it is an attribute of ~NF."
	   item (parent-frame item)))
	((null (get-workspace-if-any item))
	 (stack-error
	   top-of-stack
	   "Cannot make ~NF transient.  It is must be either a kb-workspace or ~
            found on a kb-workspace."
	   item))
	(t
	 (let ((kb-hierarchy-problem-with-definition?
		 (locate-definition-with-subclass-or-instance item)))
	   (cond (kb-hierarchy-problem-with-definition?
		  (let ((definition-name?
			  (and (of-class-p item 'class-definition)
			       (name-or-names-for-frame item))))
		    (write-stack-error
		      top-of-stack
		      (tformat "Cannot make ~NF transient.  " item)
		      (if (eq definition-name?
			      kb-hierarchy-problem-with-definition?)
			  (twrite-string "This class-definition ")
			  (tformat "An inferior item, the class-definition ~a, "
				   kb-hierarchy-problem-with-definition?))
		      (if (loop for class being each subclass of definition-name?
				do
			    (when (and class (not (eq class definition-name?)))
			      (return t)))
			  (twrite-string "has subclasses.")
			  (twrite-string "has instances.")))))
		 (t
		  (stack-error
		    top-of-stack
		    "Cannot make ~NF transient.  It is of class ~a."
		    item (class item))))))))






;;;; Event Detectors




;;; The `install-event-detector funcalled instruction' is used to install event
;;; detectors on frames and place references.

;;; Note that the compilation of this statement requires a first argument type
;;; of (or (class variable-or-parameter) (place-reference)), so the variable
;;; name item-or-place-reference is a tad too broad.

;;;   INSTALL-EVENT-DETECTOR (item-or-place-reference, event-type-symbol)

(def-funcalled-instruction install-event-detector (45 (procedure inference) 2 0 nil)
  (error-if-simulation-procedure "WAIT UNTIL EVENT" top-of-stack)
  (let ((item-or-place-reference (stack-arg 0))
	(type-of-event-detector (stack-arg 1)))
    (case type-of-event-detector
      ((receives-a-value)
       (cond
	 ((evaluation-place-reference-p item-or-place-reference)
	  (let* ((component-particulars
		   (evaluation-place-reference-component-particulars
		     item-or-place-reference))
		 (item (evaluation-place-reference-block-or-symbol
			 item-or-place-reference)))
	    (unless (evaluation-place-reference-valid-p item-or-place-reference)
	      (stack-error
		top-of-stack
		"Cannot wait until ~NV receives a value."
		item-or-place-reference))
	    (cond
	      ;; Since this action received a place reference instead of a frame
	      ;; or NIL, we can assume that the slot exists, and that it does
	      ;; not contain a frame.  However, it does not necessarily mean
	      ;; that it is a user defined attribute, and so we must verify that
	      ;; here.
	      ((attribute-component-particulars-p component-particulars)
	       (let ((slot-name (attribute-component-particulars-attribute-name
				  component-particulars)))
		 (install-event-detector
		   item 'receives-a-value current-computation-instance
		   slot-name)))
	      (t
	       (stack-error
		 top-of-stack
		 "Cannot wait until ~NV receives a value.  This event detector ~
                  can only be registered on variables, parameters, or ~
                  attributes of items."
		 item-or-place-reference)))
	    (reclaim-evaluation-place-reference item-or-place-reference)))
	 ;; Must be a variable or parameter.
	 (t
	  (install-event-detector
	    item-or-place-reference 'receives-a-value
	    current-computation-instance nil))))
      (otherwise
       (stack-error
	 top-of-stack
	 "Attempted to register an event detector on ~a events, which are not ~
          defined.  Please report this bug in the wait until statement to~
          Gensym software support."
	 type-of-event-detector)))
    nil))



;;; The funcalled instruction `clear-event-detectors' takes no arguments and
;;; clears all event detectors from the current computation instance.  Note that
;;; this can only be executed from procedures at this time.

;;;   CLEAR-EVENT-DETECTORS ()

(def-funcalled-instruction clear-event-detectors (46 (procedure inference) 0 0 nil)
  (declare (ignore local-stack))
  (error-if-simulation-procedure "WAIT UNTIL EVENT" top-of-stack)
  (clear-event-detectors current-computation-instance)
  nil)






;;;; Coercion of Procedure Arguments and List or Array Elements




;;; The `PREPARE-PROCEDURE-ARGUMENTS' funcalled instruction is used to type test
;;; and possibly coerce a procedure's arguments before executing the procedure.
;;; This instruction does not cause data-seeking, unlike
;;; prepare-possibly-unknown-procedure-arguments.

;;; It expects to receive on the stack a procedure, zero or more procedure
;;; arguments, which are evaluation values or items, and a count of the
;;; procedure arguments that will be passed.  Any coerced value or value of a
;;; variable or parameter is left on the stack in place of the original value.

;;; If an argument is not of the correct type and can not be coerced to the
;;; expected type, a stack error is signaled.

;;; Note that non-specific method-declaration arguments are not tested.  These
;;; type of methods are not executed directly.

;;;   PREPARE-PROCEDURE-ARGUMENTS (procedure . arguments argument-count)

(def-funcalled-instruction prepare-procedure-arguments (47 all (0) (0) nil)
  (prepare-procedure-arguments-on-stack top-of-stack local-stack nil)
  nil)


;; See prepare-procedure-argument-list-in-place-for-stack-procedure
(defun prepare-procedure-arguments-on-stack
       (top-of-stack local-stack unknown-allowed?)
  (let* ((stack-argument-count (svref local-stack top-of-stack))
	 (argument-count (1-f stack-argument-count))
	 (procedure-stack-position (-f top-of-stack stack-argument-count))
	 (procedure? (svref local-stack procedure-stack-position))
	 (procedure nil)
	 (local-procedure? nil)
	 (argument-descriptions nil)	 
	 (formal-arg-restp-index nil)
	 (value nil))
   (cond ((of-class-p procedure? 'procedure)
	  (when (of-class-p procedure? 'method-declaration)
	    ;; Don't test non-specific procedure methods.  The corresponding
	    ;; specific-method will be tested when called or started.
	    (return-from prepare-procedure-arguments-on-stack nil))
	 (setq procedure procedure?)
	 (setq local-procedure? t)
	 (setq argument-descriptions (argument-list-description procedure)))
	((of-class-p procedure? 'remote-procedure-declaration)
	 (setq procedure procedure?)
	 (setq local-procedure? nil)
	 (setq argument-descriptions
	       (remote-procedure-argument-description-function procedure)))
	((or (not unknown-allowed?) stack-expiration)
	 #+development
	 (break "about to error")
	 (stack-error
	   top-of-stack
	   "Internal G2 error: bad procedure ~a while preparing arguments."
	   procedure?))
	(t 
	 ;; The expression computing the procedure must have been unknown.
	 (return-from prepare-procedure-arguments-on-stack nil)))
   (let ((i (1-f (var-count argument-descriptions))))
     (when (and (<=f 0 i)
		(getf (var-general-description-from-index argument-descriptions i)
		      :all-remaining))
       (setq formal-arg-restp-index i)))
   (when (if formal-arg-restp-index
	     (<f argument-count formal-arg-restp-index)
	     (/=f argument-count (var-count argument-descriptions)))
     (signal-wrong-number-of-arguments-stack-error 
       top-of-stack procedure formal-arg-restp-index 
       (if formal-arg-restp-index
	   (1-f (var-count argument-descriptions))
	   (var-count argument-descriptions))
       argument-count))
    (loop for stack-index from (+f procedure-stack-position 1) below top-of-stack
	  for index = 0 then (if (and formal-arg-restp-index (=f index formal-arg-restp-index))
				 index (1+f index))
	  for stack-value = (svref local-stack stack-index)
	  for name = (var-name-from-index argument-descriptions index)
	  for type = (var-type-from-index argument-descriptions index)
	  do
      (unless (type-specification-type-p stack-value type)
	(cond ((or (of-class-p stack-value 'parameter)
		   (and unknown-allowed?
			(of-class-p stack-value 'variable)))
	       (setq value (get-current-value-based-on-current-environment
			     stack-value top-of-stack))
	       (setf (svref local-stack stack-index) value))
	      (t
	       (setq value stack-value)))
	(cond ((and unknown-allowed? (null stack-expiration))
	       ;; Variable did not have a current value.
	       nil)
	      ((framep value)
	       (procedure-argument-list-error
		 top-of-stack procedure name type value))
	      ((type-specification-type-p value type)
	       ;; ok datum value
	       nil)
	      ((and (eq type 'float)
		    (evaluation-integer-p value))
	       (setf (svref local-stack stack-index) 
		     (make-evaluation-float
		       (coerce-fixnum-to-gensym-float
			 (evaluation-integer-value value)))))
	      (t
	       (procedure-argument-list-error
		 top-of-stack procedure name type value)))))))




;;; The `PREPARE-POSSIBLY-UNKNOWN-PROCEDURE-ARGUMENTS' funcalled instruction is
;;; used to type test and possibly coerce a procedure's arguments before
;;; executing the procedure.  This instruction does cause data-seeking, unlike
;;; prepare-procedure-arguments.

;;; It expects to receive on the stack a procedure, zero or more procedure
;;; arguments, which are evaluation values or items, and a count of the
;;; procedure arguments that will be passed.  Any coerced value or value of a
;;; variable or parameter is left on the stack in place of the original value.

;;; If an argument is not of the correct type and can not be coerced to the
;;; expected type, a stack error is signaled.  If a variable does not currently
;;; have a value, nil is put in it's stack location and the stack-expiration is
;;; set to nil.

;;;   PREPARE-POSSIBLY-UNKNOWN-PROCEDURE-ARGUMENTS (procedure .  arguments
;;;   argument-count)

(def-funcalled-instruction prepare-possibly-unknown-procedure-arguments (48 all 1 0 nil)
  (prepare-procedure-arguments-on-stack top-of-stack local-stack t)
  nil)



;;; The `COERCE-ITEM-OR-VALUES-TO-MATCHING-ELEMENT-TYPE' and
;;; `COERCE-ITEM-OR-VALUES-TO-MATCHING-ELEMENT-TYPE-OR-UNKNOWN' funcalled
;;; instructions are used to type test and possibly coerce potential g2-list or
;;; g2-array elements.

;;; These instructions receive on the stack a g2-array-or-list, zero or more
;;; potential elements, and a count of the potential elements that were passed.

;;; For consistency with other funcalled instructions, whose argument count
;;; is always total number of elements on stack that are accessed, the count
;;; is now one more, since it cludes the g2-array-or-list too -alatto, 8/14/98

;;; For g2-arrays or g2-lists of datum element-type, the new element value is
;;; coerced to a datum.  If necessary, an integer datum is coerced to float.  If
;;; the value cannot be coerced or is not already a datum an error is signaled.
;;; In all cases, the datum or item element must match that of the g2-array or
;;; g2-list.  Otherwise, an error is signaled.

;;; The new element argument could be an evaluation value or any item.  Note
;;; that the coerce-item-or-values-to-matching-element-type instruction signals
;;; an error when the argument is a non-parameter item.  The "unknown" version
;;; of the instruction can reference the value of variables.

;;; The instruction leaves the g2-array-or-list argument on the stack.  It
;;; replaces the new element value with the coerced, matching value.

;;; Note that the coerce-item-or-values-to-matching-element-type-or-unknown
;;; can replace the new element value with nil if there is no current value.

;;; Note that these two instructions differ from the coerce-matching-element-
;;; type and coerce-matching-element-type-or-unknown in-line stack instructions
;;; which can only coerce one element.  These instructions were needed for the
;;; INSERT action, which can reference two elements.

;;;   COERCE-ITEM-OR-VALUES-TO-MATCHING-ELEMENT-TYPE
;;;     (g2-array-or-list . item-or-value-elements element-count)

(declare-optimizer-stack-instruction
  coerce-item-or-values-to-matching-element-type)

(def-funcalled-instruction coerce-item-or-values-to-matching-element-type (73 all 1 1 nil)
  (coerce-elements-to-matching-element-type-on-stack
    top-of-stack local-stack nil)
  nil)




;;;   COERCE-ITEM-OR-VALUES-TO-MATCHING-ELEMENT-TYPE-OR-UNKNOWN
;;;     (g2-array-or-list . item-or-value-elements element-count)

(declare-optimizer-stack-instruction
  coerce-item-or-values-to-matching-element-type-or-unknown)

(def-funcalled-instruction coerce-item-or-values-to-matching-element-type-or-unknown (74 all (0) (0) nil)
  (coerce-elements-to-matching-element-type-on-stack top-of-stack local-stack t)
  nil)

(defun coerce-elements-to-matching-element-type-on-stack
       (top-of-stack local-stack unknown-allowed?)
  (let* ((argument-count (1-f (svref local-stack top-of-stack)))
	 (g2-array-or-list-stack-index (-f top-of-stack argument-count 1))
	 (g2-array-or-list (svref local-stack g2-array-or-list-stack-index)))
    (loop for stack-index from (+f g2-array-or-list-stack-index 1) below
	  top-of-stack
	  for stack-value = (svref local-stack stack-index)
	  with new-value? = nil
	  do
      (multiple-value-bind (register-1 register-2)
	   (coerce-matching-element-type-or-unknown
	     g2-array-or-list stack-value top-of-stack unknown-allowed?)
	 (when register-2
	   (raw-stack-error-named-error top-of-stack register-2))
	 (setq new-value? register-1))
      (reclaim-if-evaluation-value stack-value)
      (setf (svref local-stack stack-index) new-value?))))




;;; The function `conclude-into-component' takes an item, a component
;;; particulars into which the new value will be placed, a new value, an
;;; original component-particulars to use for generating error messages and for
;;; passing to the event detectors, and finally a stack of deferred component
;;; nestings, which should initially be NIL.  This function will conclude the
;;; new value into the subpart of the item denoted by the component particulars.
;;; If it succeeds, it returns NIL.  If it fails, it returns a text-string
;;; describing the failure.  The returned string must be reclaimed by the
;;; caller.

;;; Note that there may not be a virtual attribute or exported grammar category
;;; that directly matches the given component particulars, but that the given
;;; particulars may name a subpart of an exported attribute.  In the case where
;;; this function is given a component particular that encloses another
;;; component particular, and where there is no available interface to the
;;; current component particular, then this function will eval-cons the current
;;; component particular onto the stack of deferred component nestings, and
;;; recurse to itself given the new deferred stack and the enclosed component
;;; particular.  Once this recursion process finds a component particular for
;;; which there is an exported interface, then the current value should be
;;; fetched from that location, the stack of deferred component particulars
;;; should be used to modify the denoted subpart of that value, and then the
;;; modified value should be concluded back into the exported interface.

;; Currently the only means of exporting attributes is directly off of items.
;; It is our intent to provide a second means of interfacing into components
;; where an interface may be provided directly into a deep subpart of a
;; component, for example the color of a plot of a trend-chart.  In this case,
;; the process laid out above is still followed, but it may find an interface
;; before the stack of nested component particulars has been exhausted.  -jra
;; 10/3/96

(defun-simple conclude-into-component-dispatch
    (item component-particulars new-value deferred-components
	  original-component)
  ;; (show-component-disambiguation item component-particulars new-value)
  (conclude-into-component
    item component-particulars new-value deferred-components
    original-component))

(defun-simple conclude-into-component
    (item component-particulars new-value deferred-components
	  original-component)
  (cond
    ((attribute-component-particulars-p component-particulars)
     (with-attribute-component-particulars
	 ((attribute-name class-qualifier? enclosed-component)
	  component-particulars)
       (if (eq enclosed-component '*current-computation-frame*)
           (cond
             ((evaluation-structure-p item)
               (conclude-into-structure-attribute item attribute-name class-qualifier? new-value
                 deferred-components original-component))
             (t
              (conclude-into-attribute-component
               item attribute-name class-qualifier? new-value
                deferred-components original-component)))
           (conclude-into-component
             item enclosed-component new-value
             (eval-cons component-particulars
              deferred-components)
             original-component))))
    ((aliased-attribute-component-particulars-p component-particulars)
     (with-aliased-attribute-component-particulars
	 ((alias name class enclosed-component) component-particulars)
       (declare (ignore alias))
       (if (eq enclosed-component '*current-computation-frame*)
	   (conclude-into-attribute-component
	     item name class new-value deferred-components
	     original-component)
	   (conclude-into-component
	     item enclosed-component new-value
	     (eval-cons component-particulars deferred-components)
	     original-component))))
    ((virtual-attribute-component-particulars-p component-particulars)
     (with-virtual-attribute-component-particulars
	 ((name enclosed-component) component-particulars)
       (if (eq enclosed-component '*current-computation-frame*)
	   (let ((error-string?
		   (conclude-into-virtual-attribute-component
		     item name (virtual-attribute name)
		     new-value deferred-components original-component)))
	     (unless error-string?
	       (reclaim-if-evaluation-value new-value))
	     error-string?)
	   ;; The following shouldn't ever happen.
	   (tformat-text-string
	     "The attribute ~a is only found on items." name))))
    ((element-component-particulars-p component-particulars)
     (with-element-component-particulars ((index enclosed-component)
					  component-particulars)
       (if (eq enclosed-component '*current-computation-frame*)
	   (conclude-into-element-component
	     item index new-value deferred-components original-component)
	   (conclude-into-component
	     item enclosed-component new-value
	     (eval-cons component-particulars deferred-components)
	     original-component))))
    
    (t
     #+development
     (cerror "continue" "No support for concluding into component ~a."
	     component-particulars)
     (tformat-text-string
       "No support for concluding into ~NB components.  This is a G2 ~@
        internal error, please call Gensym customer support."
       component-particulars item))))




;;; The function `rebuild-deferred-component' takes a list of
;;; component-particulars whose mutations had been deferred by
;;; conclude-into-component, and it rebuilds a component-particular that
;;; reverses and re-nests the ones in the list.  This is needed when an item is
;;; found in the traversal done by perform-deferred-component-mutations and we
;;; need to start all over again at a new item root.

(defun-simple rebuild-deferred-component (deferred-component-list)
  (loop with rebuilt-component = '*current-computation-frame*
	for component in deferred-component-list
	do
    (setq rebuilt-component
	  (cond ((attribute-component-particulars-p component)
		 (with-attribute-component-particulars
		     ((name class further-component) component)
		   (declare (ignore further-component))
		   (make-attribute-component-particulars
		     name class rebuilt-component)))
		((aliased-attribute-component-particulars-p component)
		 (with-aliased-attribute-component-particulars
		     ((alias name class further-component) component)
		   (declare (ignore further-component))
		   (make-aliased-attribute-component-particulars
		     alias name class rebuilt-component)))
		((element-component-particulars-p component)
		 (make-element-component-particulars
		   (element-component-particulars-index component)
		   rebuilt-component))
		(t
		 (error "Cannot rebuild component ~a." component))))
	finally (return rebuilt-component)))




;;; The structure `component-change-report' is used to report unexpected conditions to
;;; the callers of perform-deferred-component-mutations.  If the text attribute
;;; is filled in, then an error occurred which is described by this text.  If
;;; the text is NIL, then an item was found within the traversal of
;;; deferred-component-mutations, and it was successfully modified.  This means
;;; that the caller need not do their own mutations.

(def-structure (component-change-report
		 (:constructor make-component-change-report
			       (component-change-report-text)))
  (component-change-report-text nil :reclaimer reclaim-if-text-string))

(defmacro report-component-change-error (tformat-control-string &rest args)
  `(make-component-change-report
     (tformat-text-string ,tformat-control-string ,@args)))




;;; The function `perform-deferred-component-mutations' takes a sequence or
;;; structure (S1), an eval-cons list of component particulars, and a value to
;;; place within S1 at the location described by the list of component
;;; particulars.  If successful, S1 will be reclaimed (or modified) by this
;;; function and the modified S1 will be returned.  If unsuccessful, this
;;; function will return a component-change-report structure instead.  If an
;;; error text is found in the report, then the change failed, S1 will not have
;;; been modified or reclaimed, and text describes what went wrong.  If there is
;;; no error text in the report, then an item was found within the depths of
;;; this traversal, that item was modified, and again S1 will not have been
;;; modified or reclaimed.  (See footnote *1.)  If the setting is successful,
;;; then the new-value will have been reclaimed or incorporated into the
;;; returned value, which is the newly modified copy of S1.  If the setting
;;; cannot be accomplished (i.e. a report with a text is returned), then the
;;; new-value will not have been reclaimed.  The component-change-report should
;;; be reclaimed by the caller of this function.

;;; Note that the S1 argument is only required to be an evaluation-value, this
;;; function will return an error description if it is not a sequence or
;;; structure.

;;; *1 Note that this contract requires that errors can be recognized and
;;; initiated only on the downward path through the recursion of this function.
;;; Once some subpart of this value has been modified, then we are committed to
;;; completing successfully.  Note that this requirement enables efficient use
;;; of this function, since a value can be pulled from an attribute, be directly
;;; modified, and then directly returned into the original location without the
;;; non-modified parts ever being copied.

(defun-simple perform-deferred-component-mutations
    (evaluation-value component-particular-list new-value)
  (let ((component-particulars (car-of-cons component-particular-list))
	(new-list (cdr-of-cons component-particular-list)))
    (cond
      ((framep evaluation-value)
       (let ((new-component (rebuild-deferred-component
			      component-particular-list)))
	 (prog1
	     (make-component-change-report 
	       (conclude-into-component
		 evaluation-value new-component new-value nil new-component))
	   (reclaim-component-particulars new-component))))
      ((attribute-component-particulars-p component-particulars)
       (let ((attribute (attribute-component-particulars-attribute-name
			  component-particulars)))
	 (cond
	   ((not (evaluation-structure-p evaluation-value))
	    (report-component-change-error
	      "Unable set the ~a of ~NA, it's not a structure."
	      attribute evaluation-value))
	   ((not (mutable-evaluation-structure-p evaluation-value))
	    (let* ((mutable-structure
		     (make-unique-evaluation-structure-copy evaluation-value))
		   (modified-value-or-error
		     (perform-deferred-component-mutations
		       mutable-structure component-particular-list new-value)))
	      (cond ((component-change-report-p modified-value-or-error)
		     (reclaim-evaluation-structure mutable-structure)
		     modified-value-or-error)
		    (t
		     (reclaim-evaluation-structure evaluation-value)
		     modified-value-or-error))))
	   (new-list
	    (let* ((enclosed-value
		     (evaluation-structure-slot evaluation-value attribute)))
	      (if enclosed-value
		  (let ((modified-value-or-error
			  (perform-deferred-component-mutations
			    enclosed-value new-list new-value)))
		    (cond
		      ((component-change-report-p modified-value-or-error)
		       modified-value-or-error)
		      (t (unless (eq modified-value-or-error enclosed-value)
			   (overwrite-evaluation-structure-slot-macro
			     evaluation-value attribute modified-value-or-error))
			 evaluation-value)))
		  (report-component-change-error
		    "Unable to change values within the ~a attribute, since ~@
                     ~NA has no value for that attribute."
		    attribute evaluation-value))))
	   (t (setf (evaluation-structure-slot evaluation-value attribute)
		    new-value)
	      evaluation-value))))

      ((element-component-particulars-p component-particulars)
       (let ((index (element-component-particulars-index component-particulars)))
	 (cond
	   ((not (evaluation-sequence-p evaluation-value))
	    (report-component-change-error
	      "Unable to set element ~a of ~NA, it's not a sequence."
	      index evaluation-value))
	   ((not (mutable-evaluation-sequence-p evaluation-value))
	    (let* ((mutable-sequence
		     (allocate-new-evaluation-sequence-copy evaluation-value))
		   (modified-value-or-error
		     (perform-deferred-component-mutations
		       mutable-sequence component-particular-list new-value)))
	      (cond ((component-change-report-p modified-value-or-error)
		     (reclaim-evaluation-sequence mutable-sequence)
		     modified-value-or-error)
		    (t
		     (reclaim-evaluation-sequence evaluation-value)
		     modified-value-or-error))))
	   (t
	    
	    (let ((enclosed-value? (evaluation-sequence-aref evaluation-value index)))
	      (cond
		((and (null enclosed-value?)
		      (not (<f -1 index (evaluation-sequence-length evaluation-value))))
		 (report-component-change-error
		   "Unable to change values within element ~a, since ~NA has ~@
                    no value at that index."
		   index evaluation-value))
		(new-list
		 (let ((modified-value-or-error
			 (perform-deferred-component-mutations
			   enclosed-value? new-list new-value)))
		   (cond ((component-change-report-p modified-value-or-error)
			  modified-value-or-error)
			 (t (unless (eq modified-value-or-error enclosed-value?)
			      (setf (evaluation-sequence-ref evaluation-value index)
				    modified-value-or-error))
			    evaluation-value))))
		(t
		 (reclaim-if-evaluation-value enclosed-value?)
		 (setf (evaluation-sequence-ref evaluation-value index)
		       new-value)
		 evaluation-value)))))))
      
      (t
       (make-component-change-report
	 (twith-output-to-text-string
	   (twrite-string "Unrecognized reference within conclude: ")
	   (denote-component-of-block
	     nil component-particulars nil)))))))

;;; `conclude-into-attribute-component' and `conclude-into-structure-attribute'
;;; Consumes or reclaims original-new-value and deferred-components.
;;; Consumption of original-new-value may be through stack-error stack
;;; reclaimation.
;;; Returns nil if ok, else an error string.

(defvar change-the-text-of-attributes-without-category-evaluator-interfaces-p nil)

(defun conclude-into-structure-attribute
    (ev-structure attribute-name
      class-qualifier? original-new-value deferred-components
      original-component)
  (declare (ignore class-qualifier? original-component))
  (let* ((new-value (copy-if-evaluation-value original-new-value))
         (item-slot
           (evaluation-structure-slot ev-structure attribute-name))
         ;; item-slot should be evaluation structure if deferred-components
		 ;;  is not nil
         (item-slot-is-valid?
           (or (not deferred-components)
               (evaluation-structure-p item-slot)))
         (item-slot-copy
           (and item-slot-is-valid?
                (copy-evaluation-structure item-slot)))
         ;; modified-value-or-error contains new value that will be set
         (modified-value-or-error
           (and item-slot-is-valid?
                (if deferred-components
                    (perform-deferred-component-mutations item-slot-copy
                      deferred-components new-value)
                    new-value))))

      (when deferred-components
        (reclaim-eval-list deferred-components))

      (cond
        ((not item-slot-is-valid?) ; slot is not a structure
         (reclaim-if-evaluation-value new-value)
         (tformat-text-string
           "Unable change ~a attribute, ~NA it's not a structure."
           attribute-name item-slot))

        ((component-change-report-p modified-value-or-error)
         ;; there was an error during concluding operation
         (reclaim-evaluation-value item-slot-copy)
         (if (component-change-report-text modified-value-or-error)
             (reclaim-if-evaluation-value new-value)
             (reclaim-if-evaluation-value original-new-value))
             (reclaim-evaluation-value item-slot-copy)
             (prog1
               (copy-if-text-string
                 (component-change-report-text modified-value-or-error))
                 (reclaim-component-change-report modified-value-or-error)))
        (t
          ;; set new value
          (setf (evaluation-structure-slot ev-structure attribute-name) modified-value-or-error)
          (reclaim-evaluation-value item-slot-copy)
          (reclaim-if-evaluation-value original-new-value)
          nil))))

(defun conclude-into-attribute-component
    (item attribute-name
	  class-qualifier? original-new-value deferred-components
	  original-component &optional attribute-description?)
  (let ((reason-not-editable?
	  (reason-permanent-items-attribute-is-not-editable item attribute-name class-qualifier?)))
    (when reason-not-editable?
      (return-from conclude-into-attribute-component
	(tformat-text-string "Cannot edit ~NF, because ~A.  See the saving-parameters."
			     item reason-not-editable?))))
  (let* ((class-description (class-description-slot item))
	 (attribute-description-is-slot-description-p
	   (and attribute-description?
		(slot-description-p attribute-description?)))
	 (slot-description?
	   (if attribute-description-is-slot-description-p
	       attribute-description?
	       (get-slot-description-of-class-description
		 attribute-name class-description class-qualifier?)))
	 (unaliased-name?
	   (cond
	     ((or (null slot-description?)
		  (system-defined-slot-description-p slot-description?))
	      (get-slot-name-for-alias-if-any attribute-name item))
	     (attribute-description-is-slot-description-p
	      (pretty-slot-name attribute-description?))))
	 (user-attribute?
	   (and slot-description?
		(user-defined-slot-description-p slot-description?)))
	 (new-value original-new-value))
    (cond
      (user-attribute?
       (let* ((slot-value? (get-slot-description-value item slot-description?))
              (slot-value-class-description? (framep slot-value?)))
         (cond
           (slot-value-class-description?
            (cond
	      (deferred-components
	       (reclaim-eval-list deferred-components)
	       (tformat-text-string
		 "Unable to conclude into ~NB, since the ~NS of ~NF contained ~@
                     an item, ~NF, when a structure or sequence was expected."
		 original-component item
		 slot-description? class-description
		 item
		 slot-value?))
	      ((serve-item-p slot-value?)
	       (let ((place-or-error-text?
		       (if (and new-value (evaluation-symbol-p new-value))
			   (get-implied-attribute-place-or-error-description
			     slot-value?
			     (evaluation-symbol-symbol new-value))
			   slot-value?)))
		 (cond
		   ((null place-or-error-text?)
		    ;; Missing implied attribute error.
		    (tformat-text-string
		      "While executing a CONCLUDE action, could not locate a ~
                       variable or parameter attribute of ~NF which has ~NV in ~
                       its range of possible values."
		      item new-value))
		   ((text-string-p place-or-error-text?)
		    place-or-error-text?)
		   ((not (frame-of-class-p
			   place-or-error-text? 'variable-or-parameter))
		    (tformat-text-string
		      "Cannot conclude a value for ~NF, since it is a ~(~a~), ~@
                       not a variable-or-parameter."
		      place-or-error-text? (class place-or-error-text?)))
		   ((null new-value)
		    (cond
		      ((frame-of-class-p place-or-error-text? 'variable)
		       (put-has-no-value place-or-error-text?)
		       nil)
		      (t
		       (tformat-text-string
			 "Unable to conclude that ~NF has no value, because ~@
                          it is not an instance of the class variable."
			 place-or-error-text?))))
		   
		   (t
		    (with-temporary-gensym-float-creation conclude-into-attribute-component
		      (put-current-evaluation-value
			place-or-error-text? new-value stack-expiration nil nil))))))
	      (t
	       (tformat-text-string
		 "Cannot conclude into the ~NS of ~NF because the item in ~@
                  this attribute (~NF) is not active."
		 slot-description? class-description item
		 slot-value?))))
	    (t
	     (let ((slot-type-specification
		     (slot-type-specification slot-description?))
		   (reassigned-new-value-p nil))
	       (when deferred-components
		 (let* ((slot-copy (copy-evaluation-value slot-value?))
			(new-value-copy (copy-if-evaluation-value new-value))
			(modified-value-or-error
			  (perform-deferred-component-mutations
			    slot-copy deferred-components
			    new-value-copy)))
		   (reclaim-eval-list deferred-components)
		   (cond
		     ((component-change-report-p modified-value-or-error)
		      (reclaim-evaluation-value slot-copy)
		      (if (component-change-report-text modified-value-or-error)
			  (reclaim-if-evaluation-value new-value-copy)
			  ;; The reason the reclaim below is correct, is that in
			  ;; a sense, this is as if reassigned-new-value-p had
			  ;; been set to t and control continued.  Instead,
			  ;; because we are about to return, we need to reclaim
			  ;; the value passed in because the contract of this
			  ;; function says the value gets consumed or reclaimed.
			  ;; Note that the reason we don't reclaim if there is
			  ;; text in the change report is because that should
			  ;; ultimately lead to a stack-error being thrown which
			  ;; automatically reclaims the stack. -dkuznick,
			  ;; 7/25/01
			  (reclaim-if-evaluation-value original-new-value))
		      (return-from
			conclude-into-attribute-component
			(prog1 (copy-if-text-string
				 (component-change-report-text
				   modified-value-or-error))
			  (reclaim-component-change-report
			    modified-value-or-error))))
		     (t
		      (setq reassigned-new-value-p t)
		      (setq new-value modified-value-or-error)))))
	       (cond
		 ((type-specification-type-p
		    new-value slot-type-specification)
		  (cond ((evaluation-truth-value-p new-value)
			 (change-slot-description-value
			   item slot-description?
			   (slot-value-list
			     (evaluation-truth-value-value new-value)
			     'truth-value))
			 (reclaim-evaluation-truth-value new-value))
			((evaluation-float-p new-value)
			 (with-temporary-gensym-float-creation conclude-into-attribute-component
			   (change-slot-description-value
			     item slot-description? new-value)))
			(t
			 (change-slot-description-value
			   item slot-description? new-value)))
		  (when reassigned-new-value-p
		    (reclaim-if-evaluation-value original-new-value))
		  nil)
		 ((and (evaluation-integer-p new-value)
		       (eq slot-type-specification 'float))
		  (let ((float-value (make-evaluation-float
				       (coerce-fixnum-to-gensym-float
					 (evaluation-integer-value new-value)))))
		    (reclaim-evaluation-integer new-value)
		    (when reassigned-new-value-p
		      (reclaim-if-evaluation-value original-new-value))
		    (change-slot-description-value
		      item slot-description? float-value)
		    nil))
		 (t
		  (prog1 (make-conclude-type-error-string
			  new-value slot-description? class-description
			  item slot-type-specification)
		    (when reassigned-new-value-p
		      (reclaim-if-evaluation-value new-value))))))))))
      (t
       (when (and unaliased-name? (not attribute-description-is-slot-description-p))
	 (setq slot-description?
	       (get-slot-description-of-class-description
		 unaliased-name? class-description)))
       ;; GENSYMCID-1919: G2 aborts when concluding the size of G2 List
       (when (and slot-description?
		  (feature-assq 'not-user-editable (slot-features slot-description?)))
	 (return-from conclude-into-attribute-component
		      (tformat-text-string "The attribute ~A of ~NF is read-only." attribute-name item)))
       (let* ((slot-type?
		(if slot-description?
		    (feature-assq 'type (slot-features slot-description?))))
	      (category?
		(if slot-type?
		    (category-symbol-given-slot-type slot-type?)))
	      (text-slot?
		(if slot-type? (text-slot-type-p slot-type?) nil))
	      (parse-result-maker?
		(evaluation-value-to-category-function category?))
	      (text-of-definition-being-compiled
		(if (and (text-category-evaluator-interface-p category?)
			 (text-string-p new-value))
		    (convert-text-string-to-text new-value)))
	      (virtual-attribute? nil)
	      (reassigned-new-value-p nil))
	(prog1 ; To reclaim text-of-definition-being-compiled at the end
	 (cond
	   (parse-result-maker?
	    (when deferred-components
	      (let* ((evaluator-info
		       (get-slot-description-evaluator-info slot-description?))
		     (getter? (evaluator-slot-info-category-getter evaluator-info))
		     (new-value-copy
		       (copy-if-evaluation-value new-value))
		     (current-value
		       (if getter?
			   (multiple-value-bind (extracted-value reclaim-p)
			       (funcall-simple-multi-valued-compiled-function
				 (evaluator-slot-info-category-extracter evaluator-info)
				 (get-slot-description-value item slot-description?)
				 evaluator-info)
			     (prog1 (call-category-getter-fn
				      getter?
				      extracted-value
				      item slot-description?)
			       (when reclaim-p
				 (reclaim-slot-value extracted-value))))
			   (progn
			     ;; This case shouldn't even happen, all components
			     ;; with setters should have getters.  -jra 10/10/96
			     (reclaim-slot-value-tree text-of-definition-being-compiled)
			     (return-from conclude-into-attribute-component
			       (tformat-text-string
				"Unable to conclude ~NB, unable to fetch the ~@
				~NS attribute to modify its subparts."
				original-component item
				slot-description? class-description)))))
		     (modified-value-or-error
		       (perform-deferred-component-mutations
			 current-value deferred-components new-value-copy)))
		(reclaim-eval-list deferred-components)
		(cond
		  ((component-change-report-p modified-value-or-error)
		   (reclaim-if-evaluation-value current-value)
		   (when (component-change-report-text modified-value-or-error)
		     (reclaim-if-evaluation-value new-value-copy))
		   (reclaim-slot-value-tree text-of-definition-being-compiled)
		   (return-from conclude-into-attribute-component
		     (prog1 (copy-if-text-string
			      (component-change-report-text
				modified-value-or-error))
		       (reclaim-component-change-report
			 modified-value-or-error))))
		  (t
		   (setq reassigned-new-value-p t)
		   (setq new-value modified-value-or-error)))))
	    (with-attribute-export-conclude-context
		item
	      (multiple-value-bind (parse-result-or-bad-phrase error-string?)
		  (call-category-setter-fn
		    parse-result-maker?
		    new-value item slot-description? nil)
		(cond ((eq parse-result-or-bad-phrase bad-phrase)
		       (when reassigned-new-value-p
			 (reclaim-if-evaluation-value new-value))
		       (return-from attribute-export-conclude-context
			 (prog1 (tformat-text-string
				  "Unable to conclude a new value into the ~NS of ~NF: ~a"
				  slot-description? class-description item error-string?)
			   (when error-string?
			     (reclaim-text-string error-string?)))))
		      (t
		       (let ((commit-error-string?
			       (simple-commit-parse-result
				 item (or unaliased-name? attribute-name)
				 class-qualifier?
				 slot-description? nil nil
				 category? text-slot?
				 parse-result-or-bad-phrase nil
				 new-value)))
			 (cond (commit-error-string?
				(when reassigned-new-value-p
				  (reclaim-if-evaluation-value new-value))
				(return-from attribute-export-conclude-context
				  (prog1 (tformat-text-string
					   "Unable to conclude a new value into the ~NS of ~NF: ~a"
					   slot-description? class-description item
					   commit-error-string?)
				    (reclaim-text-string commit-error-string?))))
			       (t
				(when reassigned-new-value-p
				  (reclaim-if-evaluation-value original-new-value))
				(reclaim-if-evaluation-value new-value)))))))))
	   ((and (setq virtual-attribute?
		       (if (and attribute-description?
				(not attribute-description-is-slot-description-p))
			   attribute-description?
			   (virtual-attribute attribute-name)))
		 (type-specification-type-p
		   item
		   (virtual-attribute-arg-type virtual-attribute?)))
	    (let ((error-string?
		    (conclude-into-virtual-attribute-component
		      item attribute-name virtual-attribute? new-value
		      deferred-components original-component)))
	      (unless error-string?
		(reclaim-if-evaluation-value new-value))
	      error-string?))
	   ((and change-the-text-of-attributes-without-category-evaluator-interfaces-p
		 (text-string-p new-value)
		 category?
		 (not (memq (pretty-slot-name slot-description?)
			    '(identifier-of-basis-kb filename-of-basis-kb))))
	    (multiple-value-bind (success? reason-for-failure?)
		(parse-and-change-slot item slot-description? new-value slot-type?)
	      (declare (ignore success?))
	      reason-for-failure?))
	   (t
	    (twith-output-to-text-string
	      (write-attribute-returned-no-values-error-message
		attribute-name item class-qualifier?))))
	 ;; prog1
	 (reclaim-slot-value-tree text-of-definition-being-compiled)))))))

(defun make-conclude-type-error-string
    (new-value slot-description? class-description
	       item slot-type-specification)
  (twith-output-to-text-string
    (cond ((framep new-value)
	   (tformat "The ~(~A ~NF~)" (class new-value) new-value))
	  ((null new-value)
	   (tformat "none"))
	  ((or (evaluation-sequence-p new-value)
	       (evaluation-structure-p new-value))
	   (tformat "The value ~NV" new-value))
	  (t
	   (tformat "The ~(~NT~) ~NV"
		    (evaluation-value-type new-value)
		    new-value)))
    (tformat
     ", concluded for the ~NS of ~NF does not ~
      conform to the data type of its attribute type ~
      specification, ~NT."
     slot-description? class-description item
     slot-type-specification)))


;;; `conclude-into-virtual-attribute-component'
;;; Returns an error-string if the conclude does not succeed,
;;; otherwise, returns nil.
;;; Does not modify, incorporate or reclaim original-new-value.
;;; Reclaims deferred-components.

(defun-simple conclude-into-virtual-attribute-component
    (item attribute-name virtual-attribute original-new-value deferred-components
	  original-component)
  (let ((new-value original-new-value)
	(reassigned-new-value-p nil))
    (when deferred-components
      (let* ((current-value
	       (get-virtual-attribute item virtual-attribute))
	     (new-value-copy (copy-if-evaluation-value new-value))
	     (modified-value-or-error
	       (if (neq current-value no-component-value)
		   (perform-deferred-component-mutations
		     current-value deferred-components
		     new-value-copy))))
	(reclaim-eval-list deferred-components)
	(cond
	  ((eq current-value no-component-value)
	   ;; This case should not happen.  All virtual attributes with
	   ;; setters should most likely have getters.  -jra 10/10/96
	   (reclaim-if-evaluation-value new-value-copy)
	   (return-from conclude-into-virtual-attribute-component
	     (tformat
	       "Unable to conclude into ~NB, no value could be read ~@
                        from ~a to produce the new structured value."
	       original-component item attribute-name)))
	  ((component-change-report-p modified-value-or-error)
	   (reclaim-if-evaluation-value current-value)
	   (when (component-change-report-text modified-value-or-error)
	     (reclaim-if-evaluation-value new-value-copy))
	   (return-from conclude-into-virtual-attribute-component
	     (prog1 (copy-if-text-string
		      (component-change-report-text
			modified-value-or-error))
	       (reclaim-component-change-report
		 modified-value-or-error))))
	  (t
	   (setq reassigned-new-value-p t)
	   (setq new-value modified-value-or-error)))))
    (prog1
	(cond
	  ((not (type-specification-type-p
		  new-value
		  (virtual-attribute-value-type virtual-attribute)))
	   (let* ((value-at-type-failure nil)
		  (type-at-type-failure nil)
		  (reason-for-type-failure nil)
		  (context-of-type-failure nil)
		  (last-slot-checked-of-type-failure nil)
		  (type (virtual-attribute-value-type virtual-attribute))
		  (type-error-string
		   (progn
		     (type-specification-type-p--with-explanation
		      new-value type)
		     (type-error-in-setter
		      new-value type
		      value-at-type-failure type-at-type-failure reason-for-type-failure
		      context-of-type-failure last-slot-checked-of-type-failure))))
	   (tformat-text-string
	     "Error concluding the ~NQ of ~NF: ~A"
	     attribute-name nil item type-error-string)))
	  (t
	   (set-virtual-attribute
	     item attribute-name virtual-attribute new-value)))
      (when reassigned-new-value-p
	(reclaim-if-evaluation-value new-value)))))

(defun-simple conclude-into-element-component
    (item index new-value deferred-components original-component)
  (declare (ignore original-component))
  (when deferred-components
    (let* ((stored-element (fetch-nth-element item index 0 nil))
	   (modified-value-or-error
	     (perform-deferred-component-mutations
	       stored-element deferred-components new-value)))
      (reclaim-eval-list deferred-components)
      (cond
	((component-change-report-p modified-value-or-error)
	 (reclaim-if-evaluation-value stored-element)
	 ;; How come the new-value isn't being reclaimed if there's a
	 ;; text-string in the component-change-report?  It seems like other
	 ;; callers do this.  This code is too hairy to chance adding a random
	 ;; reclaim if it may cause a double-reclaim to happen. -dkuznick, 10/30/01
	 (return-from conclude-into-element-component
	   (prog1 (copy-if-text-string
		    (component-change-report-text modified-value-or-error))
	     (reclaim-component-change-report modified-value-or-error))))
	(t
	 (setq new-value modified-value-or-error)))))
  (multiple-value-bind (valid-element error-text)
      ;; The following always returns a copy of new-value.  New semantics for G2 6.0
      (coerce-matching-element-type-or-unknown item new-value cached-top-of-stack nil)
    (when error-text
      (raw-stack-error-named-error cached-top-of-stack error-text))
    
    ;; The element is validated above.  The test does not return if an error is
    ;; signaled.  The following change actions do not test the element type.
    ;; Note that this is wrong, and should be changed to return some error
    ;; indication that can be turned into an error string.  FIND ME, JRA!  -jra
    ;; 10/14/96

    ;; The test above appears as if it would always signal an error when the
    ;; value NIL is being placed in, when in fact it should be OK to put NIL
    ;; into an item-array.  FIND ME, JRA!  -jra 10/14/96

    ;; There is a slight flaw in this implementation as of G2 6.0.
    ;; change-g2-array-element and change-g2-list-element can signal a
    ;; stack-error.  If they do, valid-element will leak.  This is because
    ;; in some cases, they are called directly from instructions, so the normal
    ;; stack cleanup mechanism will handle the reclaimage.  In others, they are
    ;; called like here, and have a caller where a fresh copy was made and not
    ;; in a position to be automatically reclaimed.  This can be changed
    ;; to not have them signal a stack-error, but to return a text-string to
    ;; indicate failure and have the caller do the right thing.  There are other
    ;; options as well involving some extra abstraction to differentiate between
    ;; the times when the reclaimage needs to be done explicitly as opposed to
    ;; automatically.  One caveat however, is that I'm not sure those
    ;; stack-errors can ever be signalled from this path as the array-length
    ;; problem seems to be caught somewhere much earlier. However, even if this
    ;; is so, for clarity and to "do the right thing", this implementation should
    ;; be changed.  -dkuznick, 10/30/01
    (let ((error-string? 
	    (cond ((g2-array-p item)
		   (change-g2-array-element
		    item index valid-element 'conclude cached-top-of-stack))
		  ((g2-list-p item)
		   ;; The following uses or reclaims any evaluation-values.
		   (change-g2-list-element
		     item index valid-element 'conclude cached-top-of-stack))
		  (t
		   (tformat-text-string
		     "Cannot conclude a new element at index ~a for ~NF.  ~@
                                This item is a ~a, but should be a g2-array or g2-list."
		     index item (class item))))))
      (if error-string?
	  ;; In this case, the coerced value was not incorported, so that's
	  ;; what needs to be reclaimed.  Someone up the stack should be
	  ;; reclaiming the new-value.  I'm also not convinced you can reach
	  ;; this branch...  -dkuznick, 10/29/01
	  (reclaim-if-evaluation-value valid-element)
	  (reclaim-if-evaluation-value new-value))
      error-string?)))



;;; The funcalled instruction `CONCLUDE-ATTRIBUTE' is the optimized case for the
;;; conclude action putting values into attributes of items.  This case does not
;;; yet know if the value within the attribute is a frame or a constant value,
;;; but it does know that the value given is an item.

(def-funcalled-instruction conclude-attribute (77 all 4 0 nil
						  pprint-conclude-attribute-action)
  (let* ((class-qualifier? (stack-arg 0))
	 (attribute-name (stack-arg 1))
	 (item-or-place-reference (stack-arg 2))
	 (new-value (stack-arg 3))
	 (place-reference?
	   (evaluation-place-reference-p item-or-place-reference))
	 (component
	   (make-attribute-component-particulars
	     attribute-name class-qualifier?
	     (if place-reference?
		 (if (evaluation-place-reference-valid-p item-or-place-reference)
		     (evaluation-place-reference-component-particulars
		       item-or-place-reference)
		     (stack-error
		       top-of-stack "Cannot conclude a value into ~NV."
		       item-or-place-reference))
		 '*current-computation-frame*)))
	 (error-message?
	   (if place-reference?
	       (conclude-into-component-dispatch
		 (evaluation-place-reference-block-or-symbol
		   item-or-place-reference)
		 component new-value nil component)
	       (conclude-into-attribute-component
		 item-or-place-reference attribute-name class-qualifier?
		 new-value nil component))))
    (reclaim-attribute-component-particulars-without-recursion component)
    (when error-message?
      (write-stack-error top-of-stack
	(twrite-string error-message?)
	(reclaim-text-string error-message?)))
    (when place-reference?
      (reclaim-evaluation-place-reference item-or-place-reference))
    nil))

(defun-void signal-category-conclude-error
    (slot-description class-description item error-string)
  (write-stack-error cached-top-of-stack
    (tformat "Unable to conclude a new value into the ~NS of ~NF: ~a"
	     slot-description class-description item error-string)
    (reclaim-text-string error-string)))

(defun-void signal-virtual-attribute-conclude-error
    (attribute-name class-qualifier? item error-string)
  (write-stack-error cached-top-of-stack
    (tformat "Unable to conclude a new value into the ~NQ of ~NF: ~a"
	     attribute-name class-qualifier? item error-string)
    (reclaim-text-string error-string)))	    


;;; The funcalled-instruction `start-kb' is new for 5.0.  If the system is not
;;; running and is not paused it will call system-start.  Start-kb can be a
;;; funcalled instruction because it does not require to exit stack-eval.

(def-funcalled-instruction start-kb (80 (procedure inference) 0 0 nil
					pprint-start-kb-action)
  (declare (ignore local-stack top-of-stack))
  (cond (system-is-running
	 (stack-error
	   cached-top-of-stack
	   "Attempt to Start KB failed because KB is already running."
	   ))
	(system-has-paused
	 (stack-error
	   cached-top-of-stack
	   "Attempt to Start KB failed because KB is paused.  The Resume KB ~
             action should be used when the KB is paused."
	   )))
  (system-start)
  nil)


;;; System Procedure Functions used by g2-start in g2root.kb


;;; The system procedure function `g2-get-system-tables-to-activate' is
;;; called from the method g2-start in g2root.kb
;;; This function returns a sequence of instances of
;;; system-frame which are also instances of item.

(declare-system-procedure-function g2-get-system-tables-to-activate t)

(defun g2-get-system-tables-to-activate ()
  (let ((pre-sequence nil))
    (loop for block being class-instances of 'system-frame
	  do (if (subclassp (class block) 'item)
		 (eval-push
		   block
		   pre-sequence)
		 ;; Activate those system-frames which are not items.
		 (funcall-method 'activate-if-possible-and-propagate 
				 block)))
    (allocate-evaluation-sequence (nreverse pre-sequence))))

;;; The system procedure function `g2-get-message-boards' is
;;; called from the methods g2-reset and g2-start in g2root.kb
;;; This function returns a sequence of message-boards.
;;; Usually there is only one message board.

(declare-system-procedure-function g2-get-message-boards t)

(defun g2-get-message-boards ()
  (let ((pre-sequence nil))
     (loop for item being class-instances of 'message-board do
          (eval-push
	    item
	    pre-sequence))
    (allocate-evaluation-sequence
      (nreverse pre-sequence))))
    
;;; The system procedure function `g2-get-top-level-workspaces' is
;;; called from the methods g2-reset and g2-start in g2root.kb
;;; This function returns a sequence of workspaces.

(declare-system-procedure-function g2-get-top-level-workspaces t)

(defun g2-get-top-level-workspaces ()
  (let ((pre-sequence nil))
    (loop for item being class-instances of 'kb-workspace do
       (when (and (null (superblock? item))
		      (null (parent-of-subworkspace? item)))
	  (eval-push
	    item
	    pre-sequence)))
    (allocate-evaluation-sequence
      (nreverse pre-sequence))))

;;; The system procedure function `g2-get-top-level-extensions' is
;;; called from the procedures g2-reset and g2-start in g2root.kb
;;; This function returns a sequence of extension items. 

(declare-system-procedure-function g2-get-top-level-extensions t)

(defun g2-get-top-level-extensions ()
  (let ((pre-sequence nil))  
    (loop for g2-extension being each class-instance of 'g2-extension do
      (unless (and (superblock? g2-extension)
		   (null (frame-status g2-extension)))
	(eval-push
	  g2-extension
	  pre-sequence)))
    (allocate-evaluation-sequence
      (nreverse pre-sequence))))


;;; The funcalled-instruction `resume-kb' is new for 5.0.  If the system is
;;; not running and is paused it will call system-resume.  Resume-kb can be a
;;; funcalled instruction because it does not require to exit stack-eval.

(def-funcalled-instruction resume-kb (81 (procedure inference) 0 0 nil
					 pprint-resume-kb-action)
  (declare (ignore local-stack top-of-stack))
  (cond (system-is-running
	 (tformat-stack-error-text-string
	   "Attempt to Resume KB failed because KB is already running."))
	((not system-has-paused)
	 (tformat-stack-error-text-string
	   "Attempt to Resume KB failed because KB is not paused.  The Start KB ~
             action should be used when the KB is not paused."))
	(t
	 (system-resume)
	 nil)))




;;;; Stack-Action Error Messages




;;; G2-List Stack-Error Messaages.  Calls to these functions do not return.

(defun duplicate-g2-list-element-stack-error
       (g2-list element-index duplicate-item-or-datum duplicate-element-index
		error-symbol
	top-of-stack)
  (write-stack-error top-of-stack
    (tformat "Cannot ~a the element at index ~NV in ~NF to "
	     error-symbol element-index g2-list)
    (cond ((of-class-p duplicate-item-or-datum 'item)
	   (tformat "~NF" duplicate-item-or-datum))
	  ((evaluation-value-p duplicate-item-or-datum)
	   (write-evaluation-value duplicate-item-or-datum))
	  ((temporary-constant-p duplicate-item-or-datum)
	   (print-constant 
	     (cached-constant-value duplicate-item-or-datum)
	     (constant-type duplicate-item-or-datum)))
	  (t (twrite duplicate-item-or-datum)))
    (twrite-string ".  ")
    (tformat "This value is already in element ~a and this g2-list ~
             does not allow duplicate elements."
	     duplicate-element-index)))



;;; G2-Array Stack-Error Messages.  Calls to these functions do not return.

(defun bad-g2-array-length-stack-error (g2-array bad-length top-of-stack)
  (write-stack-error
    top-of-stack
    (twrite-string "The array-length ")
    (if (evaluation-value-p bad-length)
	(write-evaluation-value bad-length)
	(twrite bad-length))
    (tformat " is not valid for the G2-array ~NF." g2-array)))

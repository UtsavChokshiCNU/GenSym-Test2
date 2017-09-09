;;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module PROC-INST 

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Jim Allard and Chris Morel






;;;; Procedure Instructions




;;; This module contains the declarations for procedure statement compilers
;;; and instruction emitters.  PROC-INST2 also includes non-action instruction
;;; emitters.

;;; The emitter information used to be included in the old
;;; def-procedure-instruction macros.  Those definitions implemented code which
;;; actually executed the instructions at run time.  "Procedure instructions"
;;; and now really only "procedure compiler instructions", which are an
;;; effective assembly code for the procedure compiler.  This file implements
;;; the emitters which link the procedure compiler and the byte-code interpreter
;;; in stack-kern.

;;; The macro def-pseudo-instruction-byte-code-emitter is defined in PROC-COMP.  These
;;; declarations would normally have been included in that file, but that would
;;; have caused a huge number of forward references to the functions which emit
;;; byte-codes for stack-instructions.






;;;; Procedure Action Compilers




;;; The procedure action compilers defining form is being replaced by individual
;;; procedure action statement compilers.  The old action compiler should be
;;; commented out as the new ones are being added.

;;; The new action compilers differ from the old compilers in several ways.  They
;;; do not use the action templates.  They pass a data type argument when
;;; compiling designations or expressions.  They compile some actions into other
;;; action statements.  For example, the conclude-not statement compiles into the
;;; conclude statement.


;; Most of the procedure action statement compilers have been rewritten to pass
;; the expected types when compiling procedure expressions and designations.

;; Several actions have been modified to use the stack or non-stack compilation,
;; since the compilation has changed.  For example, some actions have changed
;; from taking a variable number of arguments to taking a fixed number.  These
;; actions include Change-Item-Color-Pattern, Show, And Hide.  Inform now does
;; not have its own special evaluation within the action.  It parses to
;; "format-form" instead of "and" when necessary.  cpm, 4/10/91

;(def-procedure-action-compilers
;  (inform print-inform-instruction)
;  (change-item-color-pattern print-change-item-color-pattern-instruction)
;  (start print-start-instruction)
;  (show print-show-instruction)
;  (hide print-hide-instruction)
;  (set print-set-instruction)
;  (conclude print-conclude-instruction)
;  (conclude-not print-conclude-not-instruction)
;  (conclude-has-no-current-value print-conclude-has-no-current-value-instruction)
;  (conclude-has-no-value print-conclude-has-no-value-instruction)
;  (focus print-focus-instruction)
;  (invoke print-invoke-instruction)
;  (move print-move-instruction)
;  (set-position print-set-position-instruction)
;  (rotate print-rotate-instruction)
;  (set-heading print-set-heading-instruction)
;  (change-item-color print-change-item-color-instruction)
;  (halt print-halt-instruction)
;  (activate print-activate-instruction)
;  (deactivate print-deactivate-instruction)
;  (add-relation print-add-relation)
;  (remove-relation print-remove-relation)
;  (edit print-edit-instruction) - obsolete
;  (delete print-delete-instruction)
;  (transfer print-transfer-instruction)
;  (change-system-attribute print-change-system-attribute-instruction)
;  (change-system-attribute-as-text print-change-system-attribute-as-text-instruction)
;  (change-g2-array-element print-change-g2-array-element-instruction)
;  (g2-list-remove-designation print-g2-list-remove-designation-instruction)
;  (g2-list-remove-expression print-g2-list-remove-expression-instruction)
;  (g2-list-insert-designation print-g2-list-insert-designation-instruction)
;  (g2-list-insert-expression print-g2-list-insert-expression-instruction)
;  (nupec-synchronize print-nupec-synchronize-instruction)
;  (update print-update-instruction)
;  )






;;;; Procedure Action Statement Compilers and Emitters




;;; These procedure statement compilers replace the procedure action compilers
;;; defined above using action templates.



(declare-forward-reference write-expression function)  ; GRAMMAR6
(declare-forward-reference
  decode-show-details-as-phrase-list function) ; CONTROLS
(declare-forward-reference
  phrase-quote-if-non-nil function) ; CONTROLS

;;; Instruction 20, the `START p-code instruction' takes a designation, an
;;; argument list, an optional overriding priority expression, and an optional
;;; wait interval expression.  This statement will cause the designated
;;; procedure to be invoked on the given arguments after the wait interval and
;;; at the given priority or at its default priority.  This procedure does not
;;; relinquish the processor after executing this statement.

;;; Note that the START instruction should signal an error if executed within a
;;; simulation procedure.

;;;   (START designation argument-list priority? wait? across?)

(defun print-start-instruction (instruction)
  (gensym-dstruct-bind ((nil designation argument-expressions
			    priority? wait? across?)
		       instruction)
    (twrite-string "START ")
    (print-designation designation)
    (twrite-string " (")
    (loop for arg in argument-expressions
	  for first-time? = t then nil
	  do
      (unless first-time? (twrite-string ", "))
      (write-expression arg))
    (twrite-string ") AFTER ")
    (if wait?
	(write-expression wait?)
	(twrite-string "no"))
    (twrite-string " SECONDS AT ")
    (cond (priority?
	   (twrite-string "PRIORITY ")
	   (write-expression priority?))
	  (t
	   (twrite-string "DEFAULT PRIORITY")))
    (when across?
      (twrite-string " ACROSS ")
      (print-designation across?))))

(def-action-compiler (start print-start-instruction)
  (gensym-dstruct-bind ((nil designation argument-expressions
			    priority? wait? across?)
		       statement)
    (let* ((argument-count (length argument-expressions))
	   (argument-stack-nodes nil)
	   #+mtg2
	   (faction? (if (eq across? :faction)
			 (progn
			   (setf across? nil)
			   t)))
	   (stable-procedure? nil)
	   (stable-arg-types? nil)
	   (recorded-procedure-call-free-reference? nil)
	   (compiled-procedure-or-rpd
	     (compile-stack-expression
	       designation
	       (maybe-add-unknown (if across?
				      '(class remote-procedure-declaration)
				      '(class procedure))
				  unknown-allowed?)))
	   (block-of-variables?
	     (unless leave-on-stack?
	       ;;Not able to use generate-block-of-new-variable-spots here.
	       (nconc
		 (phrase-list (generate-new-variable-spot
				(if across?
				    '(class remote-procedure-declaration)
				    '(class procedure))))
		 (loop repeat argument-count
		       collect (generate-new-variable-spot 'item-or-datum)
				    using phrase-cons)
		 ;; Priority, wait, and possibly across arguments.
		 (if across?
		     (generate-block-of-new-variable-spots
		       '(or integer (unknown-datum))
		       '(or number (unknown-datum))
		       '(class item))
		     (generate-block-of-new-variable-spots
		       '(or integer (unknown-datum))
		       '(or number (unknown-datum))))))))

      (when (dependent-compilation-p)
	(setq stable-procedure?
	      (stable-denoted-procedure-p compiled-procedure-or-rpd))
	(when stable-procedure?
	  (setq stable-arg-types?
		(collect-types-into-list-using-phrase-conses
		  (argument-list-description stable-procedure?)))
	  (cond
	    ((/=f (length stable-arg-types?) argument-count)
	     (compiler-dependence-warning
	       "Because of an argument count mismatch for ~ND, a call to it ~
                could not be optimized."
	       designation)
	     (setq stable-arg-types? nil)
	     (setq stable-procedure? nil))
	    (t
	     ;; Everythings OK.
	     (setq recorded-procedure-call-free-reference? t)
	     ;; Record the defined procedure argument and return types.  Note
	     ;; that this differs from the [remote-]procedure-call
	     ;; free-reference.
	     (record-free-reference
	       (if across? 'stable-remote-procedure-call 'stable-procedure-call)
	       (phrase-list designation stable-arg-types? nil))))))

      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(if across?
	    (activity-index "start rpc action")
	    (activity-index "start action"))
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	;; Note that dependent-call-rpc won't happen until we have a
	;; stable-rpd-p function, not stable-procedure-p used above.  -jra, cpm
	;; 1/14/93
	(if across?
	    'start-rpc-prolog
	    'start-prolog)
	compiled-procedure-or-rpd
	(setq argument-stack-nodes
	      (loop for argument in argument-expressions
		    for type-cons? = stable-arg-types?
				   then (cdr type-cons?)
		    collect
		      (compile-stack-expression
			argument
			(maybe-add-unknown
			  (or (car type-cons?) 'item-or-datum)
			  unknown-allowed?))
				   using phrase-cons))
	(when priority?
	  (compile-stack-expression
	    priority? (maybe-add-unknown 'integer unknown-allowed?)))
	(when wait?
	  (compile-stack-expression
	    wait? (maybe-add-unknown 'number unknown-allowed?)))
	(when across?
	  (compile-stack-expression
	    across?
	    (maybe-add-unknown '(class item) unknown-allowed?)))
	unknown-allowed?
	block-of-variables?
	stable-procedure?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (if across?
	      (activity-index "start rpc action")
	      (activity-index "start action"))))
      (emit-instruction-to-stream
	epilog-stream
	(if across? 'start-rpc-epilog 'start-epilog)
	(or block-of-variables?
	    (+f (length argument-expressions)
		(if across? 4 3))))
      #+mtg2
      (when faction?
	(emit-instruction-to-stream
	 epilog-stream
	 'wait-for-interval
	 (compile-stack-expression
	  0.01 (maybe-add-unknown 'number unknown-allowed?))))
      (when (and (null recorded-procedure-call-free-reference?)
		 (symbolp designation)
		 (not (indirectly-denoted-item-p compiled-procedure-or-rpd)))
	(record-free-reference
	  (if across? 'remote-procedure-call 'procedure-call)
	  (phrase-list
	    designation
	    (loop for argument-node in argument-stack-nodes
		  collect (type-specification-minus-type 
			    (type-specification-minus-type
			      (stack-node-value-type argument-node)
			      '(unknown-datum))
			    '(no-item))
		  using phrase-cons)
	    nil)))
      block-of-variables?)))


(defun emit-common-start-bytes (byte-code-stream instruction)
  (gensym-dstruct-bind ((nil procedure arguments priority? wait?)
		       instruction)
    (emit-stack-node-tree byte-code-stream procedure)
    (loop for argument in arguments do
      (emit-stack-node-tree byte-code-stream argument))
    (cond ((and (null priority?) (null wait?))
	   (call-stack-instruction-emitter push-nones byte-code-stream 2))
	  (t
	   (if priority?
	       (emit-stack-node-tree byte-code-stream priority?)
	       (call-stack-instruction-emitter push-nones byte-code-stream 1))
	   (if wait?
	       (emit-stack-node-tree byte-code-stream wait?)
	       (call-stack-instruction-emitter push-nones byte-code-stream 1))))
    ;; Length is returned and emitted by the caller as the last stack argument.
    (length arguments)))




;;; The function `emit-action-common-start-bytes' is used in the start and
;;; start-rpc action emitters.

(defun emit-action-common-start-bytes (byte-code-stream instruction)
  (gensym-dstruct-bind ((nil procedure arguments priority? wait?
			    across? unknown-allowed? var-spot-block?
			    stable-procedure?)
		       instruction)
    (emit-stack-node-tree byte-code-stream procedure)
    (loop for argument in arguments do
      (emit-stack-node-tree byte-code-stream argument))
    (when (not stable-procedure?)
      (let ((args+1 (1+ (length arguments))))
	(call-stack-instruction-emitter
	  funcall-instruction
	  byte-code-stream
	  (if unknown-allowed?
	      'prepare-possibly-unknown-procedure-arguments
	      'prepare-procedure-arguments)
	  args+1
	  args+1)))
    (cond ((and (null priority?) (null wait?))
	   (call-stack-instruction-emitter push-nones byte-code-stream 2))
	  (t
	   (if priority?
	       (emit-stack-node-tree byte-code-stream priority?)
	       (call-stack-instruction-emitter push-nones byte-code-stream 1))
	   (if wait?
	       (emit-stack-node-tree byte-code-stream wait?)
	       (call-stack-instruction-emitter push-nones byte-code-stream 1))))
    (when across?
      (emit-stack-node-tree byte-code-stream across?))
    (when var-spot-block?
      ;; Note that even if the values are unknown, we can do this block copy and
      ;; we won't break anything.
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'start-prolog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor ninth-arg-as-var-spot-block
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles
    values-consumed second-value-with-third-as-list-value-consumer
    cost 2))


(def-pseudo-instruction-byte-code-emitter start-prolog
  (emit-action-common-start-bytes byte-code-stream instruction))

(declare-instruction-for-optimizer
  'start-rpc-prolog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor ninth-arg-as-var-spot-block
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles))

(def-pseudo-instruction-byte-code-emitter start-rpc-prolog
  (emit-action-common-start-bytes byte-code-stream instruction))

(declare-instruction-for-optimizer
     'start-epilog
     '(no-wait-states
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor second-arg-as-var-spot
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor second-arg-as-var-spot
       cannot-write-roles
       cannot-read-roles
       cost 100))

(def-pseudo-instruction-byte-code-emitter start-epilog
  (let ((var-spot-block? (second instruction)))
    (when (and var-spot-block? (not (fixnump var-spot-block?)))
      ;; Need to test for deleted frames since some of the var-spots, and
      ;; possible some of the argument var-spots, may be items.
      (loop for var-spot in var-spot-block?
	    for args-remaining from (1- (length var-spot-block?)) downto 0
	    do
	(if (or (=f args-remaining 1) (=f args-remaining 0)) ; priority?, wait?
	    (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	      byte-code-stream var-spot)
	    (call-stack-instruction-emitter push-from-surrounding-local-var
	      byte-code-stream var-spot))))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'start
				    (if (fixnump var-spot-block?)
					var-spot-block?
					(length var-spot-block?))
				    0)))


(declare-instruction-for-optimizer
     'start-rpc-epilog
     '(no-wait-states
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor second-arg-as-var-spot-block
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor second-arg-as-var-spot-block
       cannot-write-roles
       cannot-read-roles
       cost 100))


(def-pseudo-instruction-byte-code-emitter start-rpc-epilog
  (let ((var-spot-block? (second instruction)))
    (when (and var-spot-block? (not (fixnump var-spot-block?)))
      ;; Need to test for deleted frames since some of the var-spots, and
      ;; possible some of the argument var-spots, may be items.
      (loop for var-spot in var-spot-block?
	    for args-remaining from (1- (length var-spot-block?)) downto 0
	    do
	(if (or (=f args-remaining 2) (=f args-remaining 1)) ; priority?, wait?
	    (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	      byte-code-stream var-spot)
	    (call-stack-instruction-emitter push-from-surrounding-local-var
              byte-code-stream var-spot))))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'start-rpc
				    (if (fixnump var-spot-block?)
					var-spot-block?
					(length var-spot-block?))
				    0)))



;;; The `conclude-statement' emits a call to the conclude instruction.

;;;   (CONCLUDE-STATEMENT designation expression? expiration? collection?)

;; Note that the certainty of rule antecedents will be passed as the expression
;; when compiling this statement in rules which have no explicit conclusion
;; value.  Also note that the type of the designation which is the target of the
;; conclude is (class item), because of implied attributes.  Possibly implied
;; attribute conclusions should be parsed into a different action?  Hmm, maybe
;; can't detect them all at parse time.  -jra 5/27/91

;;; The function `compile-conclude-action' is used when compiling both the
;;; conclude and conclude-not actions.

;;; This function returns the generated "block of variables", if any.

(defun compile-conclude-action
       (designation expression? expiration? collection? old-value? local-name?
	unknown-allowed? leave-on-stack? prolog-stream epilog-stream)
  (emit-instruction-to-stream
    prolog-stream
    'begin-activity
    (activity-index "conclude action")
    unknown-allowed?)
  ;; Rebuild deep left-hand-side designations.  In some cases, the rule compiler
  ;; will introduce let-action forms which hide parts of the left-hand-side from
  ;; the new deep conclude facilities.  This call will replace references to
  ;; let-action bound local-names with the original expressions.
  (setq designation (rebuild-deep-conclude-designation designation))
  (cond
    ;; Note that the attribute-named-by case could also be handled here, is
    ;; "just a simple matter of programming" in this function.  -jra 1/21/95
    ((and (null expiration?)
	  (null collection?)
	  (and (consp designation)
	       (>=f (length designation) 3)
	       (let ((role (second designation)))
		 (or (symbolp role)
		     (class-qualified-name-list-p role)
		     (and (consp role)
			  (eq (car-of-cons role) 'attribute-value))))))
     (let* ((role (second designation))
	    (item-designation (third designation))
	    (attribute-name-expr
	      (cond ((symbolp role)
		     (phrase-list 'quote role))
		    ((class-qualified-name-list-p role)
		     (phrase-list 'quote (unqualified-name role)))
		    ;; Else the attribute-value case, it's the fourth argument.
		    (t (fourth designation))))
	    (class-qualifier? (if (class-qualified-name-list-p role)
				  (class-qualifier role)
				  nil))
	    (value-type (if (and (consp role)
				 (eq (car-of-cons role) 'attribute-value))
			    (type-specification-of-role role)
			    'datum))
	    (block-of-variables?
	      (unless leave-on-stack?
		(generate-block-of-new-variable-spots
		  'symbol 'symbol '(class item) 'datum)))
	    (compiled-class-qualifer?
	      (if class-qualifier?
		  (compile-stack-expression
		    (phrase-list 'quote class-qualifier?) 'symbol)
		  nil))
	    (compiled-attribute-name 
	      (compile-stack-expression attribute-name-expr 'symbol))
	    (compiled-item-or-place-reference
	      (compile-stack-expression
		item-designation
		(maybe-add-unknown
		  '(or (class item) (place-reference)) unknown-allowed?)))
	    (item-or-place-reference-type
	      (primary-type-of-type-specification
		(stack-node-value-type compiled-item-or-place-reference))))
       
       ;; When there are constant expressions for the attribute name and class
       ;; qualifier, record free references for them.
       (when (and (consp attribute-name-expr)
		  (eq (car attribute-name-expr) 'quote)
		  (symbolp (second attribute-name-expr))
		  (type-specification-subtype-p
		    item-or-place-reference-type '(class item)))
	 (let ((item-class
		 (if (class-type-specification-p item-or-place-reference-type)
		     (type-specification-class item-or-place-reference-type)
		     'item)))
	   (cond
	     ((null class-qualifier?)
	      (record-free-reference
		'attribute-of-class
		(phrase-cons (second attribute-name-expr) item-class)))
	     (t
	      (record-free-reference
		'class-qualified-attribute-of-class
		(phrase-list (second attribute-name-expr)
			     class-qualifier?
			     item-class))))))
	      
       (unless (type-specification-subtype-p value-type 'datum)
	 (setq value-type 'datum))
       (emit-instruction-to-stream
	 prolog-stream
	 'conclude-attribute-prolog
	 compiled-class-qualifer?
	 compiled-attribute-name
	 compiled-item-or-place-reference
	 (if expression?
	     (compile-stack-expression
	       expression? (maybe-add-unknown value-type unknown-allowed?))
	     (compile-stack-expression 'true value-type))
	 block-of-variables?)
       (when unknown-allowed?
	 (emit-instruction-to-stream
	   epilog-stream
	   'begin-activity
	   (activity-index "conclude action")))
       (emit-instruction-to-stream
	 epilog-stream 'conclude-attribute-epilog block-of-variables?)
       ;; Should be the return value of the caller, the action compiler.
       block-of-variables?))

    ;; GENSYMCID-1331: Implement KB level atomic CONCLUDE for SymScale
    (old-value?
     (let ((var-spot? nil)
	   (var-spot-description? nil)
	   (var-spot-type? nil)
	   (compiler-error? nil)
	   (created-type 'truth-value)
	   (check-created-type? nil)
	   (block-of-variables? (unless leave-on-stack?
				  (generate-block-of-new-variable-spots
				    '(or (class item) (place-reference))
				    'datum 'datum 'datum))))
       (when local-name?
	 (multiple-value-setq (var-spot? var-spot-description?)
	   (variable-spot-and-description-for-local-name local-name?))
	 (cond
	   ((null var-spot?)
	    (setq compiler-error? t)
	    (procedure-compiler-missing-local-name-error local-name?))
	   (t
	    (setq var-spot-type? (getfq (cdr var-spot-description?) :type))
	    (when (not (type-specification-subtype-p created-type var-spot-type?))
	      (cond ((type-specifications-could-intersect-p
		       created-type var-spot-type?)
		     (setq check-created-type? var-spot-type?))
		    (t
		     (compiler-error
		       "In the conclude action, the local name ~a is declared to ~
                        hold ~NT, not ~NT."
		       local-name? var-spot-type? created-type)))))))
       (unless compiler-error?
	 (emit-instruction-to-stream
	   prolog-stream
	   'compare-and-swap-prolog
	   (compile-stack-expression
	     designation
	     (maybe-add-unknown
	       '(or (class item) (place-reference)) unknown-allowed?))
	   (if expression?
	       (compile-stack-expression
		 expression? (maybe-add-unknown 'datum unknown-allowed?))
	     (compile-stack-expression 'true 'datum))
	   (if old-value?
	       (compile-stack-expression
		 old-value? (maybe-add-unknown 'datum unknown-allowed?))
	     nil)
	   block-of-variables?)
	 (when unknown-allowed?
	   (emit-instruction-to-stream
	     epilog-stream
	     'begin-activity
	     (activity-index "conclude action")))
	 (emit-instruction-to-stream
	   epilog-stream 'compare-and-swap-epilog var-spot? check-created-type?
	   block-of-variables?))
       ;; Should be the return value of the caller, the action compiler.
       block-of-variables?))
    (t
     (let ((block-of-variables? (unless leave-on-stack?
				  (generate-block-of-new-variable-spots
				    '(or (class item) (place-reference))
				    'datum 'number 'number))))
       (emit-instruction-to-stream
	 prolog-stream
	 'conclude-prolog
	 ;; Class is item because the value could be an implied attribute.  -jra
	 ;; 4/1/91
	 (compile-stack-expression
	   designation
	   (maybe-add-unknown
	     '(or (class item) (place-reference)) unknown-allowed?))
	 (if expression?
	     (compile-stack-expression
	       expression? (maybe-add-unknown 'datum unknown-allowed?))
	     (compile-stack-expression 'true 'datum))
	 (if expiration?
	     (compile-stack-expression
	       expiration? (maybe-add-unknown 'number unknown-allowed?))
	     nil)
	 (if collection?
	     (compile-stack-expression
	       collection? (maybe-add-unknown 'number unknown-allowed?))
	     nil)
	 block-of-variables?)
       (when unknown-allowed?
	 (emit-instruction-to-stream
	   epilog-stream
	   'begin-activity
	   (activity-index "conclude action")))
       (emit-instruction-to-stream
	 epilog-stream 'conclude-epilog block-of-variables?)
       ;; Should be the return value of the caller, the action compiler.
       block-of-variables?))))

(def-action-compiler (conclude write-conclude-that-statement)
  (gensym-dstruct-bind ((nil designation expression? expiration? collection?
			 old-value? local-name?)
		       statement)
    (compile-conclude-action
      designation expression? expiration? collection? old-value? local-name?
      unknown-allowed? leave-on-stack? prolog-stream epilog-stream)))





;;; The function `rebuild-deep-conclude-designation' is used to undo any
;;; abbreviating of the left-hand-side of conclude assignments statements.  In
;;; some cases, the rule compiler (or user) will introduce local-names into
;;; designations which make it impossible for a conclude to see all the way down
;;; to the attribute reference whose held structure or sequence leaf is being
;;; mutated.  This function takes a designation and replaces any references to
;;; let-action bound local names in deep-conclude mutation positions so that the
;;; place that refered to the local name now refers to the expression that was
;;; used to initialize the local name.

(defun-simple rebuild-deep-conclude-designation (designation)
  (if current-let-action-bindings
      (rebuild-deep-conclude-designation-1
	(copy-tree-using-phrase-conses designation))
      designation))

(defparameter deep-concludable-role-names
  '(nth-element class-qualified-name attribute-value))

(defun-simple rebuild-deep-conclude-designation-1 (designation)
  (cond
    ((symbolp designation)
     (let* ((original-expression?
	      (second (assq designation current-let-action-bindings)))
	    (role? (and (designation-p original-expression?)
			(consp original-expression?)
			(>=f (length original-expression?) 3)
			(simple-role-of-role
			  (role-of-designation original-expression?)))))
       (if (and role?
		(or (symbolp role?)
		    (memq (role-name-of-role role?)
			  deep-concludable-role-names)))
	   (rebuild-deep-conclude-designation-1 original-expression?)
	   designation)))
    ((and (consp designation) (>=f (length designation) 3))
     (let* ((role (simple-role-of-role (role-of-designation designation)))
	    (role-name (role-name-of-role role)))
       (when (or (symbolp role)
		 (memq role-name deep-concludable-role-names))
	 (setf (third designation)
	       (rebuild-deep-conclude-designation-1 (third designation))))
       designation))
    (t designation)))

	   
	



;;; The `conclude-not-statement' emits a call to the conclude instruction.
;;;
;;;   (CONCLUDE-NOT-STATEMENT designation expiration? collection?)

(def-action-compiler (conclude-not write-conclude-that-statement)
  (gensym-dstruct-bind ((nil designation
			 expiration? collection? old-value? local-name?)
			statement)
    (compile-conclude-action
      designation 'false expiration? collection? old-value? local-name?
      unknown-allowed?
      leave-on-stack? prolog-stream epilog-stream)))



;;; Instruction 30, the `CONCLUDE p-code instruction' takes a designation and an
;;; expression, and will perform a conclude that action on the variable denoted
;;; by the designation or var-spot such that it takes the value of the given
;;; expression.  It also may take an expiration time argument and a collection
;;; time argument.  If supplied, these will be passed along to the variable.  If
;;; not supplied, these arguments should be NIL.

;;; Note that it is an error to execute this instruction in a simulation
;;; procedure.

;; COMPILER NOTES: 
;; 1. There is now only one action instruction to conclude values.  All calls
;; to conclude, including "conclude that x" and "conclude that not x", should
;; use this instruction.  Exceptions are concluding that a place does not have
;; a value or a current value and concluding relations.
;; 2. The expression argument always has a value here.  The procedure statement
;; compiler has already added the appropriate argument for actions of the form
;; "conclude that x" and "conclude that not x".

;;; The function `emit-conclude-procedure-instruction' is used to emit stack
;;; instructions for several versions of the conclude procedure instruction,
;;; e.g., conclude and conclude not.


;; Does conclude need to test the type of the datum??

;; Yes, in that it has to guarantee that the datum given (and there will be a
;; datum given) matches in type with the variable or parameter given.  In some
;; cases we will be able to determine this at compile time, and we can consider
;; putting in an optimized instruction for this case.  -jra 4/1/91

;; The comment near the datum defaulting code about "certainty" is correct, in
;; that in the rule system, the conclusion should be from the certainty of the
;; antecedant.  This should be resolved at compile time (i.e. before "emit
;; time") so that if the certainty is being concluded, a stack node tree will be
;; given in the datum argument which contains a reference to the local or stack
;; frame variable containing the certainty.  In fact, all defaulting should
;; properly be done before this emitter.  -jra 4/1/91


;;;   (CONCLUDE designation expression expiration? collection?)

(declare-instruction-for-optimizer
  'conclude-prolog
  '(no-wait-states
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor sixth-arg-as-var-spot-block
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor sixth-arg-as-var-spot-block
    values-produced 5
    cannot-read-roles
    cannot-write-roles
    cost 2))


(def-pseudo-instruction-byte-code-emitter conclude-prolog
  (gensym-dstruct-bind ((nil variable-or-parameter datum expiration? collection?
                             var-spot-block?)
		       instruction)
    (emit-stack-node-tree byte-code-stream variable-or-parameter)
    (emit-stack-node-tree byte-code-stream datum)
    (cond (expiration?
	   (emit-stack-node-tree byte-code-stream expiration?)
	   (if collection?
	       (emit-stack-node-tree byte-code-stream collection?)
	       (call-stack-instruction-emitter push-constant
		 byte-code-stream (make-evaluation-symbol nil))))
	  (collection?
	   (call-stack-instruction-emitter push-constant
	     byte-code-stream (make-evaluation-symbol nil))
	   (emit-stack-node-tree byte-code-stream collection?))
	  (t
	   (call-stack-instruction-emitter push-nones byte-code-stream 2)))
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))


(declare-instruction-for-optimizer
  'compare-and-swap-prolog
  '(no-wait-states
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor sixth-arg-as-var-spot-block
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor sixth-arg-as-var-spot-block
    values-produced 5
    cannot-read-roles
    cannot-write-roles
    cost 2))


(def-pseudo-instruction-byte-code-emitter compare-and-swap-prolog
  (gensym-dstruct-bind ((nil variable-or-parameter datum
			 old-value? var-spot-block?)
		       instruction)
    (call-stack-instruction-emitter push-nones byte-code-stream 1)
    (emit-stack-node-tree byte-code-stream variable-or-parameter)
    (emit-stack-node-tree byte-code-stream datum)
    (cond (old-value?
           (emit-stack-node-tree byte-code-stream old-value?))
          (t
           (call-stack-instruction-emitter push-constant
	     byte-code-stream (make-evaluation-symbol nil))))
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))


(declare-instruction-for-optimizer
  'conclude-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    cannot-read-roles
    writes-only-roles-specified-by-argument
    role-write-accessor consume-values-from-stack
    values-consumed 5
    cost 100))


(def-pseudo-instruction-byte-code-emitter conclude-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      ;; We have to push the first argument by itself to test for deletion of
      ;; the frame.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (car var-spot-block?))
      ;; The remaining arguments are always datum or NIL, and so can be copied
      ;; as a block without checking for deleted frames.
      (call-stack-instruction-emitter push-from-block-of-local-vars
	byte-code-stream (second var-spot-block?) (length (cdr var-spot-block?))))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'conclude)))


(declare-instruction-for-optimizer
  'compare-and-swap-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-and-fourth-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-and-fourth-as-var-spot-block
    cannot-read-roles
    writes-only-roles-specified-by-argument
    role-write-accessor consume-values-from-stack
    values-consumed 5
    cost 100))

(def-pseudo-instruction-byte-code-emitter compare-and-swap-epilog
  (gensym-dstruct-bind ((nil item-var-spot? item-var-spot-type-to-check?
			 var-spot-block?)
			instruction)
    (when var-spot-block?
      ;; We have to push the first argument by itself to test for deletion of
      ;; the frame.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (car var-spot-block?))
      ;; The remaining arguments are always datum or NIL, and so can be copied
      ;; as a block without checking for deleted frames.
      (call-stack-instruction-emitter push-from-block-of-local-vars
	byte-code-stream (second var-spot-block?) (length (cdr var-spot-block?))))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'compare-and-swap)
    (cond (item-var-spot?
	   (when item-var-spot-type-to-check?
	     (call-stack-instruction-emitter type-check
	       byte-code-stream item-var-spot-type-to-check?))
	   (call-stack-instruction-emitter pop-into-surrounding-local-var
	     byte-code-stream item-var-spot?))
	  (t (emit-instruction-byte-code byte-code-stream 'pop)))))



;;; The `CONCLUDE-ATTRIBUTE-PROLOG pseudo-instruction' is used to set up values
;;; for the optimization of conclude in the attribute case.  We only enter this
;;; case when there is no explicitly provided expiration or collection time.

(declare-instruction-for-optimizer
  'conclude-attribute-prolog
  '(no-wait-states
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor sixth-arg-as-var-spot-block
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor sixth-arg-as-var-spot-block
    values-produced 5
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter conclude-attribute-prolog
  (gensym-dstruct-bind ((nil class-qualifier? attribute-name item value
			    var-spot-block?)
		       instruction)
    (if class-qualifier?
	(emit-stack-node-tree byte-code-stream class-qualifier?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (emit-stack-node-tree byte-code-stream attribute-name)
    (emit-stack-node-tree byte-code-stream item)
    (emit-stack-node-tree byte-code-stream value)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'conclude-attribute-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    cannot-read-roles
    writes-only-roles-specified-by-argument ; Need to get right specification of
					    ; which role is written.  -jra 1/21/95
    role-write-accessor consume-values-from-stack
    values-consumed 5
    cost 50))

(def-pseudo-instruction-byte-code-emitter conclude-attribute-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	byte-code-stream (first var-spot-block?))
      (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	byte-code-stream (second var-spot-block?))
      ;; We have to push the item individually to check for deletion of the
      ;; frame.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (third var-spot-block?))
      (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	byte-code-stream (fourth var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'conclude-attribute)))




;;; Instruction 31, the `CONCLUDE-NOT p-code instruction' takes a designation
;;; and will perform a conclude-not that action on the variable denoted by the
;;; designation or var-spot such that it takes the value of the
;;; given expression.  It also may take an expiration time argument and a
;;; collection time argument.  If supplied, these will be passed along to the
;;; variable.  If not supplied, these arguments should be NIL.  

;;; Conclude-not is an action of which there are two forms.  The first form of
;;; conclude-not is (conclude-not <designation>).  In this case, if designation
;;; denotes a variable or constant of type compatible with truth-value, then the
;;; value of the location is set to the negative of the absolute value of the
;;; value to which certainty is bound upon execution of the action.  (NOTE: this
;;; actually happens only in rules.  In procedures, value of the location is set
;;; to falsity.) The alterative form of conclude-not is (conclude-not
;;; <designation> <expression>), where <expression> is expected to denote a
;;; symbol and is NOT ALLOWED AT PRESENT.

;;; Note that it is an error to execute a conclude-not instruction in a
;;; simulation procedure.

;;;   (CONCLUDE-NOT designation expiration? collection?)
;;;   (CONCLUDE-NOT designation expression expiration? collection?) - currently
;;;   not used!

;; The emitter is no longer needed.  The conclude-not statement compiles into
;; the conclude instruction.




;;; The `move-statement' emits a call to the move instruction.
;;;
;;;   (MOVE-STATEMENT designation delta-x delta-y)

;;; Note that designation must be an item and not a workspace.  The type check for
;;; '(not workspace) is done at run-time.  A compile-time type check of item and
;;; not a workspace always produces compiler warnings.

(defun print-move-instruction (instruction)
  (gensym-dstruct-bind ((nil designation x-expression y-expression)
		       instruction)
    (twrite-string "MOVE ")
    (print-designation designation)
    (twrite-string " BY ")
    (write-expression x-expression)
    (twrite-string ", ")
    (write-expression y-expression)))

(def-action-compiler (move print-move-instruction)
  (gensym-dstruct-bind ((nil designation delta-x delta-y) statement)
    (let ((block-of-variables? (unless leave-on-stack?
				 (generate-block-of-new-variable-spots
				   '(class item) 'number 'number))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "move action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'move-prolog
	(compile-stack-expression
	  designation
	  (maybe-add-unknown '(class item) unknown-allowed?))
	(compile-stack-expression
	  delta-x (maybe-add-unknown 'number unknown-allowed?))
	(compile-stack-expression
	  delta-y (maybe-add-unknown 'number unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "move action")))
      (emit-instruction-to-stream
	epilog-stream 'move-epilog block-of-variables?)
      block-of-variables?)))


;;; Instruction 32, the `MOVE p-code instruction' is used to implement the move
;;; action for procedures.  It moves an icon on a workspace relative to its
;;; current position.  Note that move instructions may not be executed in
;;; simulation procedures.  Note that if the object is currently being dragged
;;; by the user, this instruction will have no effect.  Any item can be moved
;;; except for workspaces.

;;;   (MOVE designation delta-x delta-y)

(declare-instruction-for-optimizer
  'move-prolog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor fifth-arg-as-var-spot-block
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter move-prolog
  (gensym-dstruct-bind ((nil item delta-x delta-y var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream item)
    (emit-stack-node-tree byte-code-stream delta-x)
    (emit-stack-node-tree byte-code-stream delta-y)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
     'move-epilog
     '(no-wait-states
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor second-arg-as-var-spot-block
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor second-arg-as-var-spot-block
       moves-objects
       cannot-read-roles
       cost 100))


(def-pseudo-instruction-byte-code-emitter move-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      ;; Push and test for a deleted item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (car var-spot-block?))
      (call-stack-instruction-emitter push-from-block-of-local-vars
	byte-code-stream
	(second var-spot-block?)
	(length (cdr var-spot-block?))))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'move)))



;;; The `set-position-statement' emits a call to the set-position instruction.
;;;
;;;   (SET-POSITION-STATEMENT designation x-expression y-expression)

;;; Note that designation must be an item and not a workspace.  The type check for
;;; '(not workspace) is done at run-time.  A compile-time type check of item and
;;; not a workspace always produces compiler warnings.

(defun print-set-position-instruction (instruction)
  (gensym-dstruct-bind ((nil designation x-expression y-expression)
		       instruction)
    (twrite-string "MOVE ")
    (print-designation designation)
    (twrite-string " TO ")
    (write-expression x-expression)
    (twrite-string ", ")
    (write-expression y-expression)))

(def-action-compiler (set-position print-set-position-instruction)
  (gensym-dstruct-bind ((nil designation x-expression y-expression)
		       statement)
    (let ((block-of-variables? (unless leave-on-stack?
				 (generate-block-of-new-variable-spots
				   '(class item) 'number 'number))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "move action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'set-position-prolog
	(compile-stack-expression
	  designation
	  (maybe-add-unknown '(class item) unknown-allowed?))
	(compile-stack-expression
	  x-expression (maybe-add-unknown 'number unknown-allowed?))
	(compile-stack-expression
	  y-expression (maybe-add-unknown 'number unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "move action")))
      (emit-instruction-to-stream
	epilog-stream 'set-position-epilog block-of-variables?)
      block-of-variables?)))


;;; Instruction 33, the `SET-POSITION p-code instruction' is used to implement
;;; the set-position action for procedures.  It positions an icon on a workspace
;;; at a position relative to the origin.

;;;   (SET-POSITION designation x-expression y-expression)

(declare-instruction-for-optimizer
     'set-position-prolog
     '(no-wait-states
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor fifth-arg-as-var-spot-block
       cannot-read-local-variables
       cannot-write-roles
       cannot-read-roles
       cost 2))

(def-pseudo-instruction-byte-code-emitter set-position-prolog
  (gensym-dstruct-bind ((nil item x-expression y-expression var-spot-block?)
		       instruction)
    (emit-stack-node-tree byte-code-stream item)
    (emit-stack-node-tree byte-code-stream x-expression)
    (emit-stack-node-tree byte-code-stream y-expression)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
     'set-position-epilog
     '(no-wait-states
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor second-arg-as-var-spot-block
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor second-arg-as-var-spot-block
       moves-objects
       cannot-read-roles
       cost 100))


(def-pseudo-instruction-byte-code-emitter set-position-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      ;; Push and test for a deleted item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (car var-spot-block?))
      (call-stack-instruction-emitter push-from-block-of-local-vars
	byte-code-stream (second var-spot-block?) (length (cdr var-spot-block?))))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'set-position)))



;;; The `rotate-statement' emits a call to the rotate instruction.
;;;
;;;   (ROTATE-STATEMENT designation degree-of-rotation)

;;; Note that designation must be an entity (e.g., not a workspace).  This is
;;; tested at run-time.  Compiling with a type of class entity always produces
;;; frame-note warning.

(defun print-rotate-instruction (instruction)
  (gensym-dstruct-bind ((nil designation degree-of-rotation)
		       instruction)
    (twrite-string "ROTATE ")
    (print-designation designation)
    (twrite-string " BY ")
    (write-expression degree-of-rotation)
    (twrite-string " DEGREES")))

(def-action-compiler (rotate print-rotate-instruction)
  (gensym-dstruct-bind ((nil designation degree) statement)
    (let ((block-of-variables? (unless leave-on-stack?
				 (generate-block-of-new-variable-spots
				   '(class item) 'number))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "rotate action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'rotate-prolog
	(compile-stack-expression
	  designation (maybe-add-unknown '(class item) unknown-allowed?))
	(compile-stack-expression
	  degree (maybe-add-unknown 'number unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "rotate action")))
      (emit-instruction-to-stream
	epilog-stream 'rotate-epilog block-of-variables?)
      block-of-variables?)))


;;; Instruction 34, the `ROTATE p-code instruction' is used to implement the
;;; rotate action for procedures.  It rotates an icon on a workspace 0, 90, 180,
;;; or 270 degrees clockwise from its current degree of rotation.  Note that it
;;; is an error to execute this instruction in a simulation procedure.

;;;   (ROTATE designation degree-of-rotation)


(declare-instruction-for-optimizer
  'rotate-prolog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor fourth-arg-as-var-spot-block
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles))

(def-pseudo-instruction-byte-code-emitter rotate-prolog
  (gensym-dstruct-bind ((nil item degree-expression var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream item)
    (emit-stack-node-tree byte-code-stream degree-expression)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))


;; can move objects
(declare-instruction-for-optimizer
     'rotate-epilog
     '(no-wait-states
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor second-arg-as-var-spot-block
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor second-arg-as-var-spot-block
       moves-objects
       cannot-read-roles
       cost 100))


(def-pseudo-instruction-byte-code-emitter rotate-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      ;; Push and test for a deleted item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?))
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (second var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'rotate)))



;;; The `set-heading-statement' emits a call to the set-heading instruction.
;;;
;;;   (SET-HEADING-STATEMENT designation degree-of-rotation)

;;; Note that designation must be an entity (e.g., not a workspace).  This is
;;; tested at run-time.  Compiling with a type of class entity always produces
;;; frame-note warning.

(defun print-set-heading-instruction (instruction)
  (gensym-dstruct-bind ((nil designation degree-of-rotation)
		       instruction)
    (twrite-string "ROTATE ")
    (print-designation designation)
    (twrite-string " TO THE HEADING ")
    (write-expression degree-of-rotation)
    (twrite-string " DEGREES")))

(def-action-compiler (set-heading print-set-heading-instruction)
  (gensym-dstruct-bind ((nil designation degree) statement)
    (let ((block-of-variables? (unless leave-on-stack?
				 (generate-block-of-new-variable-spots
				   '(class item) 'number))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "rotate action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'set-heading-prolog
	(compile-stack-expression
	  designation (maybe-add-unknown '(class item) unknown-allowed?))
	(compile-stack-expression
	  degree (maybe-add-unknown 'number unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "rotate action")))
      (emit-instruction-to-stream
	epilog-stream 'set-heading-epilog block-of-variables?)
      block-of-variables?)))


;;; Instruction 35, the `SET-HEADING p-code instruction' is used to implement
;;; the set-heading action for procedures.  It rotates an icon on a workspace 0,
;;; 90, 180, or 270 degrees clockwise from its original vertical position.  Note
;;; that it is an error to execute this instruction in a simulation procedure.

;;;   (SET-HEADING designation degree-of-rotation)

(declare-instruction-for-optimizer
  'set-heading-prolog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor fourth-arg-as-var-spot-block
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles
    cost 2))


(def-pseudo-instruction-byte-code-emitter set-heading-prolog
  (gensym-dstruct-bind ((nil item degree-expression var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream item)
    (emit-stack-node-tree byte-code-stream degree-expression)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
     'set-heading-epilog
     '(no-wait-states
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor second-arg-as-var-spot-block
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor second-arg-as-var-spot-block
       moves-objects
       cannot-read-roles
       cost 100))

(def-pseudo-instruction-byte-code-emitter set-heading-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      ;; Push and test for a deleted item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?))
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (second var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'set-heading)))



;;; The `conclude-has-no-current-value-statement' emits a call to the
;;; conclude-has-no-current-value instruction.
;;;
;;;   (CONCLUDE-HAS-NO-CURRENT-VALUE (variable)

(defun print-conclude-has-no-current-value-instruction (instruction)
  (gensym-dstruct-bind ((nil designation)
		       instruction)
    (twrite-string "CONCLUDE THAT ")
    (print-designation designation)
    (twrite-string " HAS NO CURRENT VALUE")))

(def-action-compiler (conclude-has-no-current-value
		       print-conclude-has-no-current-value-instruction)
  (gensym-dstruct-bind ((nil designation) statement)
    (let ((block-of-variables? (unless leave-on-stack?
				 (generate-block-of-new-variable-spots
				   '(class item)))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "conclude has no current value action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'conclude-has-no-current-value-prolog
	(compile-stack-expression
	  designation (maybe-add-unknown '(class variable) unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "conclude has no current value action")))
      (emit-instruction-to-stream
	epilog-stream 'conclude-has-no-current-value-epilog block-of-variables?)
      block-of-variables?)))


;;; Instruction 36, the `CONCLUDE-HAS-NO-CURRENT-VALUE p-code instruction' is
;;; used to implement the conclude-has-no-current-value action for procedures.
;;; It makes any current value of the denoted variable become expired.  If the
;;; variable does not have a current value, this action is a no-op.  Note that
;;; it is an error to execute this statement in a simulation procedure.

;;;   (CONCLUDE-HAS-NO-CURRENT-VALUE designation)

(declare-instruction-for-optimizer
  'conclude-has-no-current-value-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter conclude-has-no-current-value-prolog
  (gensym-dstruct-bind ((nil variable var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream variable)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'conclude-has-no-current-value-epilog
  '(no-wait-states
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 100))

(def-pseudo-instruction-byte-code-emitter conclude-has-no-current-value-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      ;; Push and test for a deleted item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (car var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction
      byte-code-stream 'conclude-has-no-current-value)))



;;; The `conclude-has-current-value-statement' emits a call to the
;;; conclude-has-no-value instruction.
;;;
;;;   (CONCLUDE-HAS-NO-VALUE (variable)

(defun print-conclude-has-no-value-instruction (instruction)
  (gensym-dstruct-bind ((nil designation)
		       instruction)
    (twrite-string "CONCLUDE THAT ")
    (print-designation designation)
    (twrite-string " HAS NO VALUE")))

(def-action-compiler (conclude-has-no-value
		       print-conclude-has-no-value-instruction)
  (gensym-dstruct-bind ((nil designation) statement)
    (let ((block-of-variables? (unless leave-on-stack?
				 (generate-block-of-new-variable-spots
				   '(class item)))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "conclude has no value action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'conclude-has-no-value-prolog
	(compile-stack-expression
	  designation (maybe-add-unknown '(or (class variable) (place-reference)) unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "conclude has no value action")))
      (emit-instruction-to-stream
	epilog-stream 'conclude-has-no-value-epilog block-of-variables?)
      block-of-variables?)))



;;; Instruction 37, the `CONCLUDE-HAS-NO-VALUE p-code instruction' is used to
;;; implement the conclude-has-no-value action for procedures.  It clears out
;;; any current value of the variable and makes the variable appear as it would
;;; if it had never been given a value.  Note that this does not affect the
;;; history of the variable in any way.  If does this by setting the expiration
;;; of the variable to the value of the parameter *some-time-ago*.  This is the
;;; defined reset value for variable expirations.  Note that it is an error to
;;; execute this instruction in a simulation procedure.

;;;   (CONCLUDE-HAS-NO-VALUE designation)

(declare-instruction-for-optimizer
  'conclude-has-no-value-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter conclude-has-no-value-prolog
  (gensym-dstruct-bind ((nil variable var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream variable)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'conclude-has-no-value-epilog
  '(no-wait-states
    cannot-read-local-variables
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 100))

(def-pseudo-instruction-byte-code-emitter conclude-has-no-value-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      ;; Push and test for a deleted item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (car var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction
      byte-code-stream 'conclude-has-no-value)))



;;; The `focus-statement' emits a call to the focus or focus-with-wait
;;; instruction.  
;;;
;;;   FOCUS (designation)

(defun print-focus-instruction (instruction)
  (gensym-dstruct-bind ((nil designation wait?)
		       instruction)
    (twrite-string "FOCUS ON ")
    (print-designation designation)
    (when wait?
      (twrite-string ", AWAITING COMPLETION"))))

(def-action-compiler (focus print-focus-instruction)
  (gensym-dstruct-bind ((nil designation wait?) statement)
    (let ((block-of-variables? (unless leave-on-stack?
				 (generate-block-of-new-variable-spots
				   '(class item)))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "focus action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'focus-prolog
	(compile-stack-expression
	  designation (maybe-add-unknown '(class item) unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "focus action")))
      (emit-instruction-to-stream
	epilog-stream 'focus-epilog block-of-variables? wait?)
      block-of-variables?)))


;;; Instruction 38, the `FOCUS p-code instruction' is used to implement the
;;; focus action for procedures.  It causes all rules about the entity, those of
;;; the class and superclasses of the entity, to be invoked.  Note that it is an
;;; error to execute this instruction in a simulation procedure.

;;;   (FOCUS designation)

(declare-instruction-for-optimizer
  'focus-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter focus-prolog
  (gensym-dstruct-bind ((nil designation var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream designation)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'focus-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 100))

(def-pseudo-instruction-byte-code-emitter focus-epilog
  (let ((var-spot-block? (second instruction))
	(wait? (third instruction)))
    (when var-spot-block?
      ;; Push and test for a deleted item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream
				    (if wait?
					'focus-with-wait
					'focus))
    (when wait?
      (emit-instruction-byte-code byte-code-stream 'pause))))



;;; The `invoke-statement' emits a call to the invoke instruction.
;;;
;;;   INVOKE (query-restriction focal-entity?)

;;; This is a special form.  Query-restriction is not evaluated.

(declare-forward-reference
  write-list-in-chicago-style function)


(defun print-invoke-instruction (instruction)
  (gensym-dstruct-bind ((nil query-restriction entity-expression? wait?)
		       instruction)
    (twrite-string "INVOKE ")
    (write-list-in-chicago-style (cdr query-restriction) 'and)
    (when entity-expression? 
      (twrite-string " FOR ")
      (print-designation entity-expression?))
    (when wait?
      (twrite-string ", AWAITING COMPLETION"))))

(def-action-compiler (invoke print-invoke-instruction)
  (gensym-dstruct-bind ((nil query-restriction focal-entity? wait?) statement)
    (let ((block-of-variables?
	    (unless leave-on-stack?
	      ;; query-restriction constant index and item.
	      (generate-block-of-new-variable-spots 'integer '(class item)))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	;; I think if we needed to differentiate between invoke and
	;; invoke-with-wait here and below {just for debugging and profiling
	;; purposes I think}, we would also need to add invoke-with-wait to
	;; registered-activities-array, which the internal doc says requires a
	;; recompile, so we can't do it now.  -dkuznick, 7/20/05
	(activity-index "invoke action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'invoke-prolog
	query-restriction
	(if focal-entity?
	    (compile-stack-expression
	      focal-entity? (maybe-add-unknown '(class item) unknown-allowed?))
	    nil)
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "invoke action")))
      (emit-instruction-to-stream
	epilog-stream 'invoke-epilog (not (null focal-entity?))
	block-of-variables?
	wait?)
      block-of-variables?)))


;;; Instruction 39, the `INVOKE p-code instruction' is used to implement the
;;; invoke action for procedures.  This action has behaviour contingent upon the
;;; presence of its optional third argument.  If the third argument is supplied,
;;; invoke will behave as does focus with the exception that invoke will
;;; invoke-rules only if the query-restriction applies to the relationship
;;; between the rule and the entity.  If the third argument is nil then things
;;; are quite different.  All rules satisfying the query-restriction will be
;;; invoked with null focal entities and null focal roles.

;;;   (INVOKE query-restriction focal-entity?)

(declare-instruction-for-optimizer
  'invoke-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor fourth-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter invoke-prolog
  (gensym-dstruct-bind ((nil query-restriction focal-entity? var-spot-block?)
		       instruction)
    (let ((index (register-internal-constant-in-byte-code-stream
		   byte-code-stream query-restriction)))
      (call-stack-instruction-emitter push-constant
	byte-code-stream (make-evaluation-integer index)))
    (if focal-entity?
	(emit-stack-node-tree byte-code-stream focal-entity?)
	(call-stack-instruction-emitter push-constant
	  byte-code-stream (make-evaluation-symbol nil)))
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'invoke-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor third-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 100))

(def-pseudo-instruction-byte-code-emitter invoke-epilog
  (gensym-dstruct-bind ((nil entity-p? var-spot-block? wait?) instruction)
    (when var-spot-block?
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?))
      (if entity-p?
	  (call-stack-instruction-emitter push-from-surrounding-local-var
	    byte-code-stream (second var-spot-block?))
	  (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	    byte-code-stream (second var-spot-block?))))
    (emit-instruction-byte-code byte-code-stream
				(if wait?
				    'invoke-with-wait
				    'invoke))))



;;; The `change-item-color-statement' emits a call to the change-item-color
;;; instruction.
;;;
;;;   CHANGE-ITEM-COLOR (item color region)

(defun print-change-item-color-instruction (instruction)
  (gensym-dstruct-bind
    ((nil designation color-expression region-expression)
     instruction)
    (twrite-string "CHANGE THE ")
    (if (and (consp region-expression)
	     (eq (car region-expression) 'quote))
	(tformat " ~(~a~) " (second region-expression))
	(progn
	  (twrite-string " THE REGION NAMED BY ")
	  (write-expression region-expression)))
    (twrite-string " OF ")
    (print-designation designation)
    (twrite-string " TO ")
    (if (and (consp color-expression)
	     (eq (car color-expression) 'quote))
	(tformat " ~(~a~)" (second color-expression))
	(write-expression color-expression))))

(def-action-compiler (change-item-color
		       print-change-item-color-instruction)
  (gensym-dstruct-bind ((nil item color region) statement)
    (let ((block-of-variables?
	    (unless leave-on-stack?
	      (generate-block-of-new-variable-spots
		'(class item) 'symbol 'symbol))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "change color action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'change-item-color-prolog
	(compile-stack-expression
	  item (maybe-add-unknown '(class item) unknown-allowed?))
	(compile-stack-expression
	  color (maybe-add-unknown 'symbol unknown-allowed?))
	(compile-stack-expression
	  region (maybe-add-unknown 'symbol unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "change color action")))
      (emit-instruction-to-stream
	epilog-stream 'change-item-color-epilog block-of-variables?)
      block-of-variables?)))


;;; Instruction 40, the `CHANGE-ITEM-COLOR p-code instruction' is used to
;;; implement the change-item-color action for procedures.  Color is an
;;; expression returning a symbol which is the new color.  The region expression
;;; is an expression returning the symbol that is the region name.  At the
;;; present time this will always be a quoted symbol, but in the future may be a
;;; more general expression.

;;;   (CHANGE-ITEM-COLOR designation color-expression region-expression)

(declare-instruction-for-optimizer
  'change-item-color-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor fifth-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter change-item-color-prolog
  (gensym-dstruct-bind ((nil item color-expression region-expression
			    var-spot-block?)
		       instruction)
    (emit-stack-node-tree byte-code-stream item)
    (emit-stack-node-tree byte-code-stream color-expression)
    (emit-stack-node-tree byte-code-stream region-expression)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))


(declare-instruction-for-optimizer
  'change-item-color-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    cannot-read-roles
    writes-item-region-colors
    cost 100))

(def-pseudo-instruction-byte-code-emitter change-item-color-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      ;; We have to push the first argument by itself to test for deletion of
      ;; the frame.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (car var-spot-block?))
      ;; The remaining arguments are always datum or NIL, and so can be copied
      ;; as a block without checking for deleted frames.
      (call-stack-instruction-emitter push-from-block-of-local-vars
	byte-code-stream (second var-spot-block?)
	(length (cdr var-spot-block?))))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'change-item-color)))



;;; The `change-item-color-pattern-statement' emits a call to the
;;; change-item-color-pattern instruction.
;;;
;;;   CHANGE-ITEM-COLOR-PATTERN (item . color-pattern)

;; This is not yet used since the emitted-instruction format is not the same as
;; non-stack-eval format.  The color-pattern is emitted as a separate list.
;; Therefore, the compiler has been modified to test that stack-eval is turned
;; on.  This test should be removed when stack-eval is always on!!  cpm, 4/9/91.

(defun print-change-item-color-pattern-instruction (instruction)
  (let ((designation (second instruction))
	(color-pattern (cddr instruction)))
    (twrite-string "CHANGE THE COLOR PATTERN OF ")
    (print-designation designation)
    (twrite-string " TO ")
    (loop for pattern in color-pattern
	  do
      (tformat "~%    ")
      (write-expression (first pattern))
      (twrite-string " = ")
      (write-expression (cdr pattern)))))

(def-action-compiler (change-item-color-pattern
		       print-change-item-color-pattern-instruction)
  (gensym-dstruct-bind ((nil item . color-pattern) statement)
    (let* ((color-pattern-count (*f (length color-pattern) 2))
	   (block-of-variables?
	     (unless leave-on-stack?
	       (nconc
		 (phrase-list (generate-new-variable-spot '(class item)))
		 (loop repeat color-pattern-count
		       collect (generate-new-variable-spot 'symbol)
			 using phrase-cons)))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "change color action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'change-item-color-pattern-prolog
	(compile-stack-expression
	  item (maybe-add-unknown '(class item) unknown-allowed?))
	(loop for (region-expression . color-expression) in color-pattern
	      collect
		(phrase-cons
		  (compile-stack-expression
		    region-expression
		    (maybe-add-unknown 'symbol unknown-allowed?))
		  (compile-stack-expression
		    color-expression
		    (maybe-add-unknown 'symbol unknown-allowed?)))
				     using phrase-cons)
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "change color action")))
      (emit-instruction-to-stream
	epilog-stream 'change-item-color-pattern-epilog
	(or block-of-variables?
	    (+f color-pattern-count 1)))
      block-of-variables?)))


;;; Instruction 41, the `CHANGE-ITEM-COLOR-PATTERN p-code instruction' is used
;;; to implement the change-item-color-pattern action for procedures.

;;;   (CHANGE-ITEM-COLOR-PATTERN designation color-pattern)

;;; This is a special form.  A count of all the action arguments, including this
;;; count-argument, is pushed onto the stack as the last value.  It is last so
;;; that it can be accessed using local-stack while not knowing the size of the
;;; stack.

(declare-instruction-for-optimizer
  'change-item-color-pattern-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor fifth-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))


(def-pseudo-instruction-byte-code-emitter change-item-color-pattern-prolog
  (gensym-dstruct-bind ((nil item color-pattern var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream item)
    (loop for (region . color) in color-pattern
	  do
      (emit-stack-node-tree byte-code-stream region)
      (emit-stack-node-tree byte-code-stream color))
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'change-item-color-pattern-epilog
  '(no-wait-states
    cannot-write-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    cannot-read-roles
    writes-icon-colors
    cost 100))

(def-pseudo-instruction-byte-code-emitter change-item-color-pattern-epilog
  (let ((var-spot-block? (second instruction)))
    (when (and var-spot-block? (not (fixnump var-spot-block?)))
      ;; We have to push the first argument by itself to test for deletion of
      ;; the frame.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (car var-spot-block?))
      ;; The remaining arguments are always datum or NIL, and so can be copied
      ;; as a block without checking for deleted frames.
      (call-stack-instruction-emitter push-from-block-of-local-vars
	byte-code-stream (second var-spot-block?)
	(length (cdr var-spot-block?))))
    (call-stack-instruction-emitter funcall-instruction
      byte-code-stream 'change-item-color-pattern
      (if (fixnump var-spot-block?)
	  var-spot-block?
	  (length var-spot-block?))
      0)))




;;; The `show-statement' emits a call to the show instruction.
;;;
;;;   SHOW (block . show-details?)

;; Note that this compilation differs from the non-stack version.  It does not
;; put the window back into the show-details list.  Therefore, the compiler has
;; been modified to test that stack-eval is turned on.  This test should be
;; removed when stack-eval is always on!!  cpm, 4/9/91.

;; OPEN ISSUE: The non-stack show action called block-evaluate with
;; role-serve-inactive-objects?  bound to t.  We should probably serve inactive
;; objects here also.  We would need some new stack-instructions to push from
;; and pop into role-serve-inactive-objects?  variable!!  cpm, 4/11/91

;; Note that this is the 3.x version of SHOW.  There is a SHOW-NEW action
;; for version 4.0.  See the corresponding action and compiler in this file.
;; The old 3.x SHOW action is still supported for existing KBs.
;; - cpm, 11/9/93

(defun print-show-instruction (instruction)
  (let ((designation (second instruction))
	(show-detail-list (cddr instruction)))
    (twrite-string "SHOW ")
    (print-designation designation)
    (loop for show-detail = (first show-detail-list)
	  then (first show-detail-list)
	  while show-detail-list
	  do
      (setq show-detail-list (cdr show-detail-list))
      (case (car show-detail)
	(scale
	 (twrite-string " AT ")
	 (twrite (second show-detail))
	 (twrite-string " SCALE"))
	(workspace-position
	  (twrite-string " WITH ITS ")
	  (twrite-reference-point-details (cdr show-detail))
	  (twrite-string " ")
	  (twrite-reference-point-details (cdr (first show-detail-list)))
	  (twrite-string " OF THE SCREEN")
	  (setq show-detail-list (cdr show-detail-list)))
	 (screen-position
	  (twrite-string " ")
	  (twrite-reference-point-details (cdr show-detail))
	  (twrite-string " OF THE SCREEN"))
	 (in
	  ;; "in" grammar is seen as "on" by the user.
	  (twrite-string " ON ")
	  (print-designation (second show-detail)))))))




;;; The function `twrite-reference-point-details' prints the
;;; reference-point-details (a term used in module grammar1) for an instruction,
;;; such as "show".  This information is used as screen and workspace positions.  
;;; This function is used in print-show-instruction.  This function should be
;;; called within the form twith-output-to-text-string.  Spaces are not printed
;;; before or after the reference point information.  Therefore, the caller
;;; should handle any necessary formatting (spaces) around it.

(defun twrite-reference-point-details (reference-point-detail-list) 
  (loop with reference-point-details = reference-point-detail-list
	with first-reference-point? = t
	while reference-point-details do

    (let ((element-1 (first reference-point-details))
	  (element-2 (second reference-point-details)))
      (if first-reference-point?
	  (setq first-reference-point? nil)
	  (twrite-string " "))

      (cond ((consp element-1)
	     (twrite-reference-point-details element-1)
	     (setq reference-point-details (cdr reference-point-details)))

	    (t (cond ((numberp element-2)
		      (twrite element-2)
		      (twrite-string " UNITS ")
		      (twrite element-1)
		      (when (or (eq element-1 'left) (eq element-1 'right))
			(twrite-string " OF "))
		      (if (cddr reference-point-details)
			  (twrite-string "AND")
			  (twrite-string "THE"))
		      (setq reference-point-details
			    (cddr reference-point-details)))
		     (t
		      (twrite element-1)
		      (if (eq element-1 'at)
			  (twrite-string " THE"))
		      (setq reference-point-details
			    (cdr reference-point-details)))))))))

(def-action-compiler (show print-show-instruction)
  (gensym-dstruct-bind ((nil item . show-details?) statement)
    (let ((window-designation?
	    (when (eq (caar show-details?) 'in)
	      (second (car show-details?))))
	  (block-of-variables? (unless leave-on-stack?
				 (generate-block-of-new-variable-spots
				   '(class item) '(class item) 'integer))))
      (when window-designation?
	(setq show-details? (cdr show-details?)))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "show action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'show-prolog
	(compile-stack-expression
	  item (maybe-add-unknown '(class item) unknown-allowed?))
	(if window-designation?
	    (compile-stack-expression
	      window-designation?
	      (maybe-add-unknown '(class ui-client-item)
				 unknown-allowed?))
	    nil)
	show-details?
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "show action")))
      (emit-instruction-to-stream
	epilog-stream 'show-epilog (not (null window-designation?))
	block-of-variables?)
      block-of-variables?)))


;;; Instruction 42, the `SHOW p-code instruction' is used to implement the show
;;; action for procedures.
;;;
;;;   (SHOW block? window? show-details?)

;; This is a special form.  In the stack version of this instruction, the block,
;; window?, and show-details are required, though they may be nil.  In the
;; non-stack version the window was contained in the show-details argument.

(declare-instruction-for-optimizer
  'show-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor fifth-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter show-prolog
  (gensym-dstruct-bind ((nil item window? show-details? var-spot-block?)
		       instruction)
						       ; Role Serve inactive
						       ; objects!!
    (emit-stack-node-tree byte-code-stream item)
    (if window?
	(emit-stack-node-tree byte-code-stream window?)
	(call-stack-instruction-emitter push-constant
	  byte-code-stream (make-evaluation-symbol nil)))
    (if show-details?
	(let ((index (register-internal-constant-in-byte-code-stream
		       byte-code-stream show-details?)))
	  (call-stack-instruction-emitter push-constant
	    byte-code-stream (make-evaluation-integer index)))
	(call-stack-instruction-emitter push-constant
	  byte-code-stream (make-evaluation-symbol nil)))
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'show-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor third-arg-as-var-spot-block
    cannot-read-roles
    makes-items-visible
    cost 100))

(def-pseudo-instruction-byte-code-emitter show-epilog
  (gensym-dstruct-bind ((nil window-p? var-spot-block?) instruction)
    (when var-spot-block?
      ;; Push and test for deletion of the item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?))
      (if window-p?
	  ;; Push and test for deletion of the window.
	  (call-stack-instruction-emitter push-from-surrounding-local-var
	    byte-code-stream (second var-spot-block?))
	  ;; There is no window.
	  (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	    byte-code-stream (second var-spot-block?)))
      ;; Show-details constant index.
      (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	byte-code-stream (third var-spot-block?)))
    (emit-instruction-byte-code byte-code-stream 'show)))



;;; The `show-new action compiler' emits a call to the new, version 4.0 SHOW
;;; instruction.  This action, unlike the 3.x SHOW, evaluates its arguments.
;;;
;;; Note that the 3.x action is still supported.
;;; Note that this action is not show an inactive item.
;;;
;;;   SHOW-NEW (item . show-details?)

;;; Added for 50rev3:  This action now has an option that will maintain the
;;; workspace layering instead of automatically bringing the workspace to the top.
;;; This information is communicated to the drawing code with the go-to-block?
;;; variable which was previously null in all cases (unused).  (ghw 5/11/98)

(defun print-show-new-instruction (instruction)
  (print-show-instruction instruction))

;; Note that the printer for SHOW-NEW may need to be rewritten.  Modify this
;; function as the grammar changes are implemented.  - cpm, 11/9/93

(def-action-compiler (show-new print-show-new-instruction)
  (gensym-dstruct-bind ((nil item . show-details?) statement)
    (let* ((preserving-layering?
	     (when (and show-details? (eq (car-of-cons show-details?) t))
	       (setq show-details? (cdr show-details?))
	       t))
 	   (window-designation?
	    (when (eq (caar show-details?) 'in)
	      (second (car show-details?))))
	  ;; See the "Added for 50rev3" comment above to understand this binding. 
	  (go-to-block? preserving-layering?)
	  (block-of-variables?
	   (unless leave-on-stack?
	     (generate-block-of-new-variable-spots
	       '(class item) '(class item) 'boolean
	       'symbol 'symbol 'symbol 'symbol 'symbol 'symbol
	       'number 'symbol 'number 'symbol
	       'number 'number
	       'number 'number
	       'number 'number))))
      (when window-designation?
	(setq show-details? (cdr show-details?)))
      (gensym-dstruct-bind
	    ((symbolic-x-scale? symbolic-y-scale?
	      symbolic-x-in-workspace? symbolic-y-in-workspace?
	      symbolic-x-in-window? symbolic-y-in-window?
	      x-offset-units? symbolic-x-offset-direction?
	      y-offset-units? symbolic-y-offset-direction?
	      x-magnification? y-magnification?
	      x-in-workspace? y-in-workspace?
	      x-in-window? y-in-window?)
	     (decode-show-details-as-phrase-list show-details?))
	(emit-instruction-to-stream
	  prolog-stream
	  'begin-activity
	  (activity-index "show action")
	  unknown-allowed?)
	(emit-instruction-to-stream
	  prolog-stream
	  'show-new-prolog
	  (compile-stack-expression
	    item (maybe-add-unknown '(class item) unknown-allowed?))
	  (if window-designation?
	      (compile-stack-expression
		window-designation?
		(maybe-add-unknown '(class ui-client-item)
				   unknown-allowed?))
	      nil)
	  go-to-block?
	  (if symbolic-x-scale?
	      (compile-stack-expression
		symbolic-x-scale? (maybe-add-unknown 'symbol unknown-allowed?))
	      nil)
	  (if symbolic-y-scale?
	      (compile-stack-expression
		symbolic-y-scale? (maybe-add-unknown 'symbol unknown-allowed?))
	      nil)
	  (if symbolic-x-in-workspace?
	      (compile-stack-expression
		symbolic-x-in-workspace?
		(maybe-add-unknown 'symbol unknown-allowed?))
	      nil)
	  (if symbolic-y-in-workspace?
	      (compile-stack-expression
		symbolic-y-in-workspace?
		(maybe-add-unknown 'symbol unknown-allowed?))
	      nil)
	  (if symbolic-x-in-window?
	      (compile-stack-expression
		symbolic-x-in-window?
		(maybe-add-unknown 'symbol unknown-allowed?))
	      nil)
	  (if symbolic-y-in-window?
	      (compile-stack-expression
		symbolic-y-in-window?
		(maybe-add-unknown 'symbol unknown-allowed?))
	      nil)
	  (if x-offset-units?
	      (compile-stack-expression
		x-offset-units? (maybe-add-unknown 'number unknown-allowed?))
	      nil)
	  (if symbolic-x-offset-direction?
	      (compile-stack-expression
		symbolic-x-offset-direction?
		(maybe-add-unknown 'symbol unknown-allowed?))
	      nil)
	  (if y-offset-units?
	      (compile-stack-expression
		y-offset-units? (maybe-add-unknown 'number unknown-allowed?))
	      nil)
	  (if symbolic-y-offset-direction?
	      (compile-stack-expression
		symbolic-y-offset-direction?
		(maybe-add-unknown 'symbol unknown-allowed?))
	      nil)
	  (if x-magnification?
	      (compile-stack-expression
		x-magnification? (maybe-add-unknown 'number unknown-allowed?))
	      nil)
	  (if y-magnification?
	      (compile-stack-expression
		y-magnification? (maybe-add-unknown 'number unknown-allowed?))
	      nil)
	  (if x-in-workspace?
	      (compile-stack-expression
		x-in-workspace? (maybe-add-unknown 'number unknown-allowed?))
	      nil)
	  (if y-in-workspace?
	      (compile-stack-expression
		y-in-workspace? (maybe-add-unknown 'number unknown-allowed?))
	      nil)
	  (if x-in-window?
	      (compile-stack-expression
		x-in-window? (maybe-add-unknown 'number unknown-allowed?))
	      nil)
	  (if y-in-window?
	      (compile-stack-expression
		y-in-window? (maybe-add-unknown 'number unknown-allowed?))
	      nil)
	  block-of-variables?)
	(when unknown-allowed?
	  (emit-instruction-to-stream
	    epilog-stream
	    'begin-activity
	    (activity-index "show action")))
	(emit-instruction-to-stream
	  epilog-stream 'show-new-epilog (not (null window-designation?))
	  block-of-variables?)
	block-of-variables?))))

(declare-instruction-for-optimizer
     'show-new
     '(no-wait-states
       cannot-write-local-variables
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor second-and-third-args-as-var-spots
       cannot-write-roles
       cost 100))

(def-pseudo-instruction-byte-code-emitter show-new
  (gensym-dstruct-bind ((nil the-item show-details?) instruction)
    (emit-stack-node-tree  byte-code-stream the-item)
    (emit-stack-node-tree  byte-code-stream show-details?)
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'show-new)
    ))




(declare-instruction-for-optimizer
     'show-new-prolog
     '(no-wait-states
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor twenty-first-arg-as-var-spot-block
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor twenty-first-arg-as-var-spot-block
       cannot-write-roles
       values-produced 18
       cost 100))

;;; The `SHOW-NEW p-code instruction' is used to implement the new SHOW action
;;; for procedures and rules.
;;;
;;;   (SHOW-NEW 
;;;      block-or-workspace g2-window? go-to-block?
;;;      symbolic-x-scale?        symbolic-y-scale?
;;;      symbolic-x-in-workspace? symbolic-y-in-workspace?
;;;      symbolic-x-in-window?    symbolic-y-in-window?
;;;      x-offset-units?          symbolic-x-offset-direction?
;;;      y-offset-units?          symbolic-y-offset-direction?
;;;      x-magnification?         y-magnification?
;;;	 x-in-workspace?          y-in-workspace?
;;;	 x-in-window?             y-in-window?)

(def-pseudo-instruction-byte-code-emitter show-new-prolog
  (gensym-dstruct-bind
	((nil item g2-window? go-to-block?
	      symbolic-x-scale? symbolic-y-scale?
	      symbolic-x-in-workspace? symbolic-y-in-workspace?
	      symbolic-x-in-window? symbolic-y-in-window?
	      x-offset-units? symbolic-x-offset-direction?
	      y-offset-units? symbolic-y-offset-direction?
	      x-magnification? y-magnification?
	      x-in-workspace? y-in-workspace?
	      x-in-window? y-in-window?
	      var-spot-block?)
	 instruction)
    (emit-stack-node-tree byte-code-stream item)
    (if g2-window?
	(emit-stack-node-tree byte-code-stream g2-window?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (call-stack-instruction-emitter push-constant byte-code-stream
				    (make-evaluation-symbol go-to-block?))
    (if symbolic-x-scale?
	(emit-stack-node-tree byte-code-stream symbolic-x-scale?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (if symbolic-y-scale?
	(emit-stack-node-tree byte-code-stream symbolic-y-scale?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (if symbolic-x-in-workspace?
	(emit-stack-node-tree byte-code-stream symbolic-x-in-workspace?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (if symbolic-y-in-workspace?
	(emit-stack-node-tree byte-code-stream symbolic-y-in-workspace?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (if symbolic-x-in-window?
	(emit-stack-node-tree byte-code-stream symbolic-x-in-window?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (if symbolic-y-in-window?
	(emit-stack-node-tree byte-code-stream symbolic-y-in-window?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (if x-offset-units?
	(emit-stack-node-tree byte-code-stream x-offset-units?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (if symbolic-x-offset-direction?
	(emit-stack-node-tree byte-code-stream symbolic-x-offset-direction?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (if y-offset-units?
	(emit-stack-node-tree byte-code-stream y-offset-units?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (if symbolic-y-offset-direction?
	(emit-stack-node-tree byte-code-stream symbolic-y-offset-direction?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (if x-magnification?
	(emit-stack-node-tree byte-code-stream x-magnification?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (if y-magnification?
	(emit-stack-node-tree byte-code-stream y-magnification?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (if x-in-workspace?
	(emit-stack-node-tree byte-code-stream x-in-workspace?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (if y-in-workspace?
	(emit-stack-node-tree byte-code-stream y-in-workspace?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (if x-in-window?
	(emit-stack-node-tree byte-code-stream x-in-window?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (if y-in-window?
	(emit-stack-node-tree byte-code-stream y-in-window?)
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))


(declare-instruction-for-optimizer
     'show-new-epilog
     '(no-wait-states
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor third-arg-as-var-spot-block
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor third-arg-as-var-spot-block
       cannot-write-roles
       values-consumed 14
       cost 100))

(def-pseudo-instruction-byte-code-emitter show-new-epilog
  (gensym-dstruct-bind ((nil window-p? var-spot-block?) instruction)
    (when var-spot-block?
      ;; Push and test for deletion of the item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?))
      (if window-p?
	  ;; Push and test for deletion of the window.
	  (call-stack-instruction-emitter push-from-surrounding-local-var
	    byte-code-stream (second var-spot-block?))
	  ;; There is no window.
	  (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	    byte-code-stream (second var-spot-block?)))
      (call-stack-instruction-emitter push-from-block-of-local-vars
	byte-code-stream (third var-spot-block?)
	(length (cddr var-spot-block?))))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'show-new)))



;;; The `hide-statement' emits a call to the hide instruction.
;;;
;;;   HIDE (block . hide-details?)

;; Note that this compilation differs from the non-stack version.  It does not
;; put the window back into the show-details list.  Therefore, the compiler has
;; been modified to test that stack-eval is turned on.  This test should be
;; removed when stack-eval is always on!!  cpm, 4/9/91.

;; OPEN ISSUE: The non-stack show action called block-evaluate with
;; role-serve-inactive-objects?  bound to t.  We should probably serve inactive
;; objects here also.  We would need some new stack-instructions to push from
;; and pop into role-serve-inactive-objects?  variable!!  cpm, 4/11/91

(defun print-hide-instruction (instruction)
  (twrite-string "HIDE ")
  (print-designation (second instruction))
  (let ((hide-details? (cddr instruction)))
    (when (eq (caar hide-details?) 'in)
      ;; "in" grammar is seen as "on" by the user.
      (twrite-string " ON ")
      (print-designation (second (car hide-details?))))))

(def-action-compiler (hide print-hide-instruction)
  (gensym-dstruct-bind ((nil item . hide-details?) statement)
    (let ((window-designation? (when (eq (caar hide-details?) 'in)
				 (second (car hide-details?))))
	  (block-of-variables? (unless leave-on-stack?
				 (generate-block-of-new-variable-spots
				   '(class item) '(class item)))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "hide action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'hide-prolog
	(compile-stack-expression
	  item (maybe-add-unknown '(class item) unknown-allowed?))
	(if window-designation?
	    (compile-stack-expression
	      window-designation?
	      (maybe-add-unknown '(class ui-client-item)
				 unknown-allowed?))
	    nil)
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "hide action")))
      (emit-instruction-to-stream
	epilog-stream 'hide-epilog (not (null window-designation?))
	block-of-variables?)
      block-of-variables?)))


;;; Instruction 43, the `HIDE p-code instruction' is used to implement the hide
;;; action for procedures.

;;;   HIDE (block window?)

;; This is a special form.  In the stack version of this instruction, the block
;; and window?  are required, though they may be nil.  Note, that only the
;; window may be in the hide-details argument.  Therefore, the hide-details
;; argument is not passed to the action as in the "show" action.

(declare-instruction-for-optimizer
  'hide-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor fourth-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter hide-prolog
  (gensym-dstruct-bind ((nil item window? var-spot-block?) instruction)
						       ; Role Serve inactive
						       ; objects!!
    (emit-stack-node-tree byte-code-stream item)
    (if window?
	(emit-stack-node-tree byte-code-stream window?)
	(call-stack-instruction-emitter push-constant
	  byte-code-stream (make-evaluation-symbol nil)))
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'hide-epilog
  '(no-wait-states
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor third-arg-as-var-spot-block
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    cannot-read-roles
    hides-objects
    cost 100))

(def-pseudo-instruction-byte-code-emitter hide-epilog
  (gensym-dstruct-bind ((nil window-p? var-spot-block?) instruction)
    (when var-spot-block?
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?))
      (if window-p?
	  (call-stack-instruction-emitter push-from-surrounding-local-var
	    byte-code-stream (second var-spot-block?))
	  (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	    byte-code-stream (second var-spot-block?))))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'hide)))



;;; The `activate-statement' emits a call to the activate instruction.
;;;
;;;   ACTIVATE (item)

;; Change which should not affect functionality: The non-stack actions tested
;; for an entity instead of an item.

(defun print-activate-instruction (instruction)
  (twrite-string "ACTIVATE THE SUBWORKSPACE OF ")
  (print-designation (second instruction)))

(def-action-compiler (activate print-activate-instruction)
  (gensym-dstruct-bind ((nil item) statement)
    (let ((block-of-variables? (unless leave-on-stack?
				 (generate-block-of-new-variable-spots
				   '(class item)))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "activate action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'activate-prolog
	(compile-stack-expression
	  item (maybe-add-unknown '(class item) unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "activate action")))
      (emit-instruction-to-stream
	epilog-stream 'activate-epilog block-of-variables?)
      block-of-variables?)))



;;; Instruction 44, the `ACTIVATE p-code instruction' is used to implement the
;;; activate action for procedures.

;;;   (ACTIVATE item)

(declare-instruction-for-optimizer
  'activate-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter activate-prolog
  (gensym-dstruct-bind ((nil item var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream item)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream (first var-spot-block?)))))

(declare-instruction-for-optimizer
  'activate-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    cannot-read-roles
    makes-inactive-objects-visible
    cost 100))

(def-pseudo-instruction-byte-code-emitter activate-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      ;; Push the item and test for deletion.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?))))
  (call-stack-instruction-emitter funcall-instruction byte-code-stream 'activate))


;;; `activate' methodized action


;;; The `deactivate-statement' emits a call to the deactivate instruction.
;;;
;;;   DEACTIVATE (item)

;; Change which should not affect functionality: The non-stack actions tested
;; for an entity instead of an item.

(defun print-deactivate-instruction (instruction)
  (twrite-string "DEACTIVATE THE SUBWORKSPACE OF ")
  (print-designation (second instruction)))

(def-action-compiler (deactivate print-deactivate-instruction)
  (gensym-dstruct-bind ((nil item) statement)
    (let ((block-of-variables? (unless leave-on-stack?
				 (generate-block-of-new-variable-spots
				   '(class item)))))
      (when (procedure-p *current-computation-frame*)
	(set-procedure-can-invalidate-environment *current-computation-frame*))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "deactivate action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'deactivate-prolog
	(compile-stack-expression
	  item (maybe-add-unknown '(class item) unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "deactivate action")))
      (emit-instruction-to-stream
	epilog-stream 'deactivate-epilog block-of-variables?)
      block-of-variables?)))


;;; Instruction 45, the `DEACTIVATE p-code instruction' is used to implement the deactivate
;;; action for procedures.

;;;   (DEACTIVATE item)

(declare-instruction-for-optimizer
  'deactivate-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter deactivate-prolog
  (gensym-dstruct-bind ((nil item var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream item)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream (first var-spot-block?)))))

(declare-instruction-for-optimizer
  'deactivate-epilog
  '(no-wait-states
    cannot-read-local-variables
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    cannot-read-roles
    makes-active-objects-inactive
    cost 100))

(def-pseudo-instruction-byte-code-emitter deactivate-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      ;; Push the item and test for deletion.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?))))
  (call-stack-instruction-emitter funcall-instruction byte-code-stream 'deactivate))


(defun decode-deactivate-details-in-phrase-rule (statement)
  (gensym-dstruct-bind ((nil item)
		       statement)
    (phrase-list
      'call-action
      'g2-deactivate
      (phrase-list
	item
	(phrase-list 'evaluated-structure
		     (phrase-quote-if-non-nil
		       'deactivate-subworkspace-only)
		     'true)))))


;;; The `halt-statement' emits a call to the halt instruction.
;;;
;;;   HALT (text-message?)

(defun print-halt-instruction (instruction)
  (let ((text-message (second instruction)))
    (twrite-string "HALT")
    (when text-message
      (twrite-string " WITH ")
      (print-constant text-message 'text))
      (twrite-string " IF BREAKPOINTS ARE ENABLED")))

(def-action-compiler (halt print-halt-instruction)
  (gensym-dstruct-bind ((nil text-message?) statement)
    (let ((block-of-variables? (unless leave-on-stack?
				 (generate-block-of-new-variable-spots
				   'text))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "halt action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'halt-prolog
	(if text-message?
	    (compile-stack-expression
	      text-message? (maybe-add-unknown 'text unknown-allowed?))
	    nil)
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "halt action")))
      (emit-instruction-to-stream
	epilog-stream 'halt-epilog (not (null text-message?))
	block-of-variables?)
      block-of-variables?)))


;;; Instruction 46, the `HALT p-code instruction' is used to implement the halt
;;; action for procedures. 

;;;   (HALT) or (HALT text-message)

(declare-instruction-for-optimizer
  'halt-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter halt-prolog
  (gensym-dstruct-bind ((nil text? var-spot-block?) instruction)
    (if text?
	(emit-stack-node-tree byte-code-stream text?)
	(call-stack-instruction-emitter push-constant
	  byte-code-stream (make-evaluation-symbol nil)))
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream (first var-spot-block?)))))


(declare-instruction-for-optimizer
     'halt-epilog
     '(reads-only-local-variables-specified-by-argument
       local-var-read-accessor third-arg-as-var-spot-block
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor third-arg-as-var-spot-block
       cannot-write-roles
       cannot-read-roles
       return-flow
       cost 100))


(def-pseudo-instruction-byte-code-emitter halt-epilog
  (gensym-dstruct-bind ((nil text-p? var-spot-block?) instruction)
    (when var-spot-block?
      (if text-p?
	  (call-stack-instruction-emitter push-from-surrounding-local-var
	    byte-code-stream (first var-spot-block?))
	  (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	    byte-code-stream (first var-spot-block?))))
    (emit-instruction-byte-code byte-code-stream 'halt)))



;;; The `set-statement' emits a call to the set instruction.
;;;
;;;   SET (place datum)

(defun print-set-instruction (instruction)
  (gensym-dstruct-bind ((nil place-designation expression)
		       instruction)
    (twrite-string "SET ")
    (print-designation place-designation)
    (twrite-string " TO ")
    (write-expression expression)))

(def-action-compiler (set print-set-instruction)
  (gensym-dstruct-bind ((nil place datum) statement)
    (let ((block-of-variables? (unless leave-on-stack?
				 (generate-block-of-new-variable-spots
				   '(class variable-or-parameter)
				   'datum))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "set action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'set-prolog
	(compile-stack-expression
	  place
	  (maybe-add-unknown '(class variable-or-parameter) unknown-allowed?))
	(compile-stack-expression
	  datum (maybe-add-unknown 'datum unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "set action")))
      (emit-instruction-to-stream
	epilog-stream 'set-epilog block-of-variables?)
      block-of-variables?)))


;;; Instruction 47, the `SET p-code instruction' is used to implement the set
;;; action for procedures.  `Set' is the action which is used to set values into
;;; external variables. This is done through the function stored in function-to-
;;; set-external-variable of the data server for the variable being set.  The
;;; implementation of this function closely follows conclude, except that once a
;;; place is determined for a variable, it is set into the spot with the
;;; function-to-set-external-variable, instead of put-current-value.

;;;   (SET place expression)

(declare-instruction-for-optimizer
  'set-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor fourth-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter set-prolog
  (gensym-dstruct-bind ((nil place expression var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream place)
    (emit-stack-node-tree byte-code-stream expression)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'set-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 100))

(def-pseudo-instruction-byte-code-emitter set-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      ;; Push and test if the item is deleted.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?))
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (second var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'set)))



;;; Instruction 48, the `EDIT p-code instruction' is used to implement the edit
;;; action for procedures.  Edit is an action which given a block, an attribute
;;; (slot) name, and a parsable text for that slot, causes a kb change as if
;;; entered by editing. 

;;; The Edit instruction is obsolete and was never released as part of G2.  It
;;; is replaced by the "Change the Text of" instruction which modifies certain
;;; system attributes that require parsed text.




;;; The `inform-statement' emits a call to the inform instruction.
;;;
;;;   INFORM (destination message . features)

;; The role (the name <designation>) was being evaluated within the inform action.
;; It either returned the name or made up a name based on the class name.  A
;; pre-3.0 change was made to compile into the name evaluator and not the name
;; role.  In 3.0, we are keeping with the name evaluator.

;; For actions that can handle "unknown" (e.g., rules), the inform message is
;; compiled into "(first-that-has-a-value message "****")".  This keeps the
;; current non-stack rule functionality of inform, that prints "****" when the
;; rule can not get a value for the message and times out.

;; Rewrite print-inform-instruction to handle the new parse for inform!!  cpm,
;; 5/7/91

						       ; temporary hack, see below!!
(declare-forward-reference stack-eval? variable)       ; PROC-UTILS


;;; The function `compile-procedure-inform-feature' is used to compile the
;;; options of the inform procedure statement.

(defun compile-procedure-inform-feature (inform-option)
  (cond ((null inform-option)
	 nil)
	((eq (car inform-option) 'duration)
	 (phrase-list
	   (car inform-option)
	   (compile-stack-expression
	     (second inform-option) 'integer)))
	((eq (car inform-option) 'on)
	 (phrase-list
	   (car inform-option)
	   (compile-stack-expression
	     (second inform-option) '(class kb-workspace))))
	((eq (car inform-option) 'above)
	 (phrase-list
	   (car inform-option)
	   (compile-stack-expression
	     (second inform-option) '(class item))))
	((eq (car inform-option) 'below)
	 (phrase-list
	   (car inform-option)
	   (compile-stack-expression
	     (second inform-option) '(class item))))
	(t inform-option)))


;;; The function `compile-action-inform-feature' is used to compile the options
;;; of the inform action.

(defun compile-action-inform-feature (inform-option unknown-allowed?)
  (cond ((eq (car inform-option) 'duration)
	 (compile-stack-expression
	     (second inform-option)
	     (maybe-add-unknown 'integer unknown-allowed?)))
	((eq (car inform-option) 'on)
	 (compile-stack-expression
	     (second inform-option)
	     (maybe-add-unknown '(class kb-workspace) unknown-allowed?)))
	((eq (car inform-option) 'above)
	 (compile-stack-expression
	   (second inform-option)
	   (maybe-add-unknown '(class item) unknown-allowed?)))
	((eq (car inform-option) 'below)
	 (compile-stack-expression
	   (second inform-option)
	   (maybe-add-unknown '(class item) unknown-allowed?)))
	(inform-option
	 (compiler-bug
	   "Inform action" "Unknown Inform option ~a." inform-option))
	(t (compiler-bug "Inform action" "Missing Inform option."))))

;; The Inform action writes onto the message board by default.  The compiler has
;; been modified to convert a reference of on "message board" also to the
;; default".  Both cases will write to the message-board, first creating the
;; message-board, if necessary.  "on message-board" reference is the only
;; exception of "on <designation>" not referring to a kb-workspace.  This change
;; now prevents the user from displaying on their own kb-workspace which is
;; named message-board.  This is probably ok because message-board should be a
;; reserved word in G2.  This has been revied with MHD.  Mark mentioned another
;; problem problem when referring to the message-board indirectly, e.g., "on the
;; workspace named by <symbol>", where the symbol is message-board.  This case
;; would fail because the conversion to the default by the compiler cannot
;; happen.  The runtime test for kb-workspace would then fail.  There is also a
;; problem if the name of the message-board is changed.  - cpm, 1/31/92.

(defun print-inform-instruction (instruction)
  (gensym-dstruct-bind ((nil destinations message . features)
		       instruction)
    (twrite-string "INFORM ")
    (print-designation destinations)
    (loop for feature in features
	  do
      (case (first feature)
	(on (twrite-string " ON ")
	    (print-designation (second feature)))
	(above (twrite-string " ABOVE ")
	       (print-designation (second feature)))
	(below (twrite-string " BELOW ")
	       (print-designation (second feature)))
	(duration (twrite-string " FOR THE NEXT ")
		  (print-constant (second feature) 'seconds))
	(t (twrite feature))))
    (twrite-string " THAT ")
    (if (consp message)
	(loop for message-component in (cdr message)
	      do
	      (if (text-string-p message-component)
		  (twrite-parsably message-component)
		  (progn
		    (if (consp message-component)
			(case (first message-component)
			  ((format fixed-format)
			   (if (eq (first (second message-component)) 'the)
			       (print-designation (second message-component))
			       (twrite (second message-component))))
			  (the (print-designation message-component))
			  (t 
			   (write-expression message-component)))
			(twrite message-component))))
	      (twrite-string " "))
	(print-constant message 'text))))

(def-action-compiler (inform print-inform-instruction)
  (gensym-dstruct-bind
    ((nil destination-or-operator message . inform-options) statement)
    (let ((block-of-variables?
	    (unless leave-on-stack?
	      ;; destination, message, duration?, on?, above?, below?
	      (generate-block-of-new-variable-spots
		'(class item) 'text 'number '(class kb-workspace) '(class item)
		'(class item))))
	  (destination?
	    (and (not (equal destination-or-operator '(the operator)))
		 (not (eq destination-or-operator 'operator))
		 destination-or-operator))
	  duration-p? on-p? above-p? below-p?)
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "inform action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'inform-prolog
	(if destination?
	    (compile-stack-expression
	      destination? (maybe-add-unknown '(class item) unknown-allowed?))
	    nil)
	(cond ((and (consp message) (eq (car message) 'and))
	       ;; TEMPORARY HACK until the inform grammar is changed to use
	       ;; "format-form" instead of "and"!!  This allows both stack and
	       ;; non-stack versions of inform to work simultaneously.  REMOVE
	       ;; WHEN ONLY USING THE STACK VERSION!!  cpm, 5/7/91

	       ;; Welllll, we still need it.  The grammar has never been
	       ;; changed to produce format-form instead of an and.  So that
	       ;; still needs to be done.  -jra & cpm 4/22/93
	       (setf (car message) 'format-form)
	       (if unknown-allowed?
		   (compile-stack-expression
		     (phrase-list 'first-that-has-a-value message #w"****")
		     '(or text (unknown-datum)))
		   ;; in procedures
		   (compile-stack-expression message 'text)))
	      (t (compile-stack-expression
		   message (maybe-add-unknown 'text unknown-allowed?))))
	(loop for option in inform-options
	      do
	  (when (eq (car option) 'duration)
	    (setq duration-p? t)
	    (return
	      (compile-action-inform-feature option unknown-allowed?))))
	(loop for option in inform-options
	      do
	  (when (and (eq (car option) 'on)
		     ;; Changed to convert message-board reference to the
		     ;; default case.  See the above documentation.  - cpm,
		     ;; 1/31/92
		     (not (eq (cadr option) 'message-board)))
	    (setq on-p? t)
	    (return
	      (compile-action-inform-feature option unknown-allowed?))))
	(loop for option in inform-options
	      do
	  (when (eq (car option) 'above)
	    (setq above-p? t)
	    (return
	      (compile-action-inform-feature option unknown-allowed?))))
	(loop for option in inform-options
	      do
	  (when (eq (car option) 'below)
	    (setq below-p? t)
	    (return
	      (compile-action-inform-feature option unknown-allowed?))))
	block-of-variables?)

      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "inform action")))
      (emit-instruction-to-stream
	epilog-stream 'inform-epilog (not (null destination?)) duration-p? on-p?
	above-p? below-p? block-of-variables?)
      block-of-variables?)))


;;; Instruction 49, the `INFORM p-code instruction' is used to implement the
;;; inform action for procedures.

;;; Destination is either a workspace, the symbol OPERATOR, or (the OPERATOR).

;;; Message: is a formatted string that is evaluated by the Format-Form
;;; evaluator.  The documentation for that evaluator describes the format for
;;; that string.

;;; Features: (DURATION n), (ON workspace), and (UNDER|ABOVE object).

;; Destination (the operator) and operator emits as the constant operator.  I
;; don't see any use of destination lists as described in the non-stack actions.
;; cpm, 6/10/91.

(declare-instruction-for-optimizer
  'inform-prolog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor eighth-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor eighth-arg-as-var-spot-block
    values-produced 6
    cannot-read-roles
    cannot-write-roles
    cost 100))

(def-pseudo-instruction-byte-code-emitter inform-prolog
  (gensym-dstruct-bind ((nil destination message duration? on? above? below?
			    var-spot-block?)
		       instruction)
    (let ((nil-arg-count 0))
      (if (null destination)
	  (call-stack-instruction-emitter push-constant
	    byte-code-stream (make-evaluation-symbol nil))
	  (emit-stack-node-tree byte-code-stream destination))
      (emit-stack-node-tree byte-code-stream message)
      (if duration?				       ;integer
	  (emit-stack-node-tree byte-code-stream duration?)
	  (incff nil-arg-count))
      (cond (on?				       ;workspace
	     (when (>f nil-arg-count 0)
	       (call-stack-instruction-emitter push-nones byte-code-stream nil-arg-count)
	       (setq nil-arg-count 0))
	     (emit-stack-node-tree byte-code-stream on?))
	    (t (incff nil-arg-count)))
      (cond (above?				       ;item
	     (when (>f nil-arg-count 0)
	       (call-stack-instruction-emitter push-nones byte-code-stream nil-arg-count)
	       (setq nil-arg-count 0))
	     (emit-stack-node-tree byte-code-stream above?))
	    (t (incff nil-arg-count)))
      (cond (below?				       ;item
	     (when (>f nil-arg-count 0)
	       (call-stack-instruction-emitter push-nones byte-code-stream nil-arg-count)
	       (setq nil-arg-count 0))
	     (emit-stack-node-tree byte-code-stream below?))
	    (t (incff nil-arg-count)
	       (call-stack-instruction-emitter push-nones byte-code-stream nil-arg-count)))
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?))))))

(declare-instruction-for-optimizer
  'inform-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor seventh-arg-as-var-spot-block-masked-by-previous-args
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor seventh-arg-as-var-spot-block-masked-by-previous-args
    values-consumed 6
    cannot-read-roles
    cannot-write-roles
    cost 100))

(def-pseudo-instruction-byte-code-emitter inform-epilog
  (gensym-dstruct-bind ((nil destination-p? duration-p? on-p? above-p? below-p?
			    var-spot-block?)
		       instruction)
    (when var-spot-block?
      (gensym-dstruct-bind ((destination message duration on above below)
			   var-spot-block?)
	(if destination-p?
	    (call-stack-instruction-emitter push-from-surrounding-local-var
	      byte-code-stream destination)
	    (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	      byte-code-stream destination))
	(call-stack-instruction-emitter push-from-surrounding-local-var
	  byte-code-stream message)
	(if duration-p?
	    (call-stack-instruction-emitter push-from-surrounding-local-var
	      byte-code-stream duration)
	    (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	      byte-code-stream duration))
	(if on-p?
	    (call-stack-instruction-emitter push-from-surrounding-local-var
	      byte-code-stream on)
	    (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	      byte-code-stream on))
	(if above-p?
	    (call-stack-instruction-emitter push-from-surrounding-local-var
	      byte-code-stream above)
	    (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	      byte-code-stream above))
	(if below-p?
	    (call-stack-instruction-emitter push-from-surrounding-local-var
	      byte-code-stream below)
	    (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	      byte-code-stream below))))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'inform)))



;;; The `add-relation-statement' emits a call to the add-relation instruction.
;;;
;;;   ADD-RELATION (relation-name item item now-case?)

(defun print-add-relation (instruction)
  (gensym-dstruct-bind ((nil relation-name designation-1 designation-2)
		       instruction)
    (twrite-string "CONCLUDE THAT ")
    (print-designation designation-1)
    (tformat " IS ~a " relation-name)
    (print-designation designation-2)))

(def-action-compiler (add-relation print-add-relation)
  (gensym-dstruct-bind ((nil relation-name item1 item2 now-case?) statement)
    (let ((block-of-variables?
	    (unless leave-on-stack?
	      (generate-block-of-new-variable-spots
		'symbol '(class item) '(class item) 'truth-value))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "conclude relation action")
	unknown-allowed?)
    (emit-instruction-to-stream
      prolog-stream
      'add-relation-prolog
      relation-name
      (compile-stack-expression
	item1 (maybe-add-unknown '(class item) unknown-allowed?))
      (compile-stack-expression
	item2 (maybe-add-unknown '(class item) unknown-allowed?))
      (compile-stack-expression
	(if now-case? 'true 'false) 'truth-value)
      block-of-variables?)
    (when unknown-allowed?
      (emit-instruction-to-stream
	epilog-stream
	'begin-activity
	(activity-index "conclude relation action")))
    (emit-instruction-to-stream
      epilog-stream 'add-relation-epilog block-of-variables?)
    block-of-variables?)))


;;; Instruction 50, the `add-relation p-code instruction' takes a relation
;;; name, two item designations and a now-case, and establishes the named
;;; relation between the two items.  If now-case is nil, ints of "one to
;;; many", "one to one", etc. are followed.  In this case, the relation will not 
;;; be added if the constraints would be violated.  If now-case is non-nil and
;;; if adding the instance would violate constraints, old instances are removed
;;; as necessary before the new instance is added.

;;;   (ADD-RELATION relation-name item-designation item-designation now-case)

(declare-instruction-for-optimizer
  'add-relation-prolog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor sixth-arg-as-var-spot-block
    cannot-read-local-variables
    cannot-read-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter add-relation-prolog
  (gensym-dstruct-bind ((nil relation-name item-1 item-2 now-case-expression
			    var-spot-block?)
		       instruction)
    (call-stack-instruction-emitter push-constant
      byte-code-stream (make-evaluation-symbol relation-name))
    (emit-stack-node-tree byte-code-stream item-1)
    (emit-stack-node-tree byte-code-stream item-2)
    (emit-stack-node-tree byte-code-stream now-case-expression)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'add-relation-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    add-relations
    cannot-read-roles
    cost 100))

(def-pseudo-instruction-byte-code-emitter add-relation-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      (gensym-dstruct-bind ((relation-name item-1 item-2 now-case?)
			   var-spot-block?)
	(call-stack-instruction-emitter push-from-surrounding-local-var
	  byte-code-stream relation-name)
	;; Push and test for a deleted item.
	(call-stack-instruction-emitter push-from-surrounding-local-var
	  byte-code-stream item-1)
	;; Push and test for a deleted item.
	(call-stack-instruction-emitter push-from-surrounding-local-var
	  byte-code-stream item-2)
	(call-stack-instruction-emitter push-from-surrounding-local-var
	  byte-code-stream now-case?)))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'add-relation)))



;;; The `remove-relation-statement' emits a call to the remove-relation
;;; instruction.
;;;
;;;   REMOVE-RELATION (relation-name item item)

(def-action-compiler (remove-relation print-add-relation)
  (gensym-dstruct-bind ((nil relation-name item1 item2) statement)
    (let ((block-of-variables?
	    (unless leave-on-stack?
	      (generate-block-of-new-variable-spots
		'symbol '(class item) '(class item)))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "conclude not related action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'remove-relation-prolog
	relation-name
	(compile-stack-expression
	  item1 (maybe-add-unknown '(class item) unknown-allowed?))
	(compile-stack-expression
	  item2 (maybe-add-unknown '(class item) unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "conclude not related action")))
      (emit-instruction-to-stream
	epilog-stream 'remove-relation-epilog block-of-variables?)
      block-of-variables?)))


;;; Instruction 51, the `remove-relation p-code instruction' takes a relation
;;; name and two item designations, and establishes the named relation between
;;; the two items.

;;;   (REMOVE-RELATION relation-name item-designation item-designation)

(declare-instruction-for-optimizer
  'remove-relation-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor fifth-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter remove-relation-prolog
  (gensym-dstruct-bind ((nil relation-name item-1 item-2 var-spot-block?)
		       instruction)
    (call-stack-instruction-emitter push-constant
      byte-code-stream (make-evaluation-symbol relation-name))
    (emit-stack-node-tree byte-code-stream item-1)
    (emit-stack-node-tree byte-code-stream item-2)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'remove-relation-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    cannot-read-roles
    removes-relations
    cost 100))

(def-pseudo-instruction-byte-code-emitter remove-relation-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?))
      ;; Push and test for a deleted item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (second var-spot-block?))
      ;; Push and test for a deleted item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (third var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'remove-relation)))



;;; The `create-statement' emits a call to the create instruction.
;;;
;;;   (CREATE class-name var-spot?)

(defun print-create-instruction (instruction)
  (gensym-dstruct-bind ((nil class-expression local-name?) instruction)
    (twrite-string "CREATE AN INSTANCE ")
    (when local-name?
      (print-designation local-name?)
      (twrite-string " "))
    (twrite-string "OF THE CLASS NAMED BY ")
    (write-expression class-expression)))

(def-action-compiler (create print-create-instruction)
  (gensym-dstruct-bind ((nil class-expression local-name?) statement)
    (let ((var-spot? nil)
	  (var-spot-description? nil)
	  (var-spot-type? nil)
	  (compiler-error? nil)
	  (created-type
	    (make-class-type-specification
	      (if (and (consp class-expression)
		       (eq (car class-expression) 'quote))
		  (second class-expression)
		  'item)))
	  (check-created-type? nil)
	  (block-of-variables?
	    (unless leave-on-stack?
	      (generate-block-of-new-variable-spots 'symbol))))
      (when local-name?
	(multiple-value-setq (var-spot? var-spot-description?)
	  (variable-spot-and-description-for-local-name local-name?))
	(cond
	  ((null var-spot?)
	   (setq compiler-error? t)
	   (procedure-compiler-missing-local-name-error local-name?))
	  (t
	   (setq var-spot-type? (getfq (cdr var-spot-description?) :type))
	   (when (not (type-specification-subtype-p created-type var-spot-type?))
	     (cond ((type-specifications-could-intersect-p
		      created-type var-spot-type?)
		    (setq check-created-type? var-spot-type?))
		   (t
		    (compiler-error
		      "In the create action, the local name ~a is declared to ~
                       hold ~NT, not ~NT."
		      local-name? var-spot-type? created-type)))))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "create action")
	unknown-allowed?)
      (unless compiler-error?
	(emit-instruction-to-stream
	  prolog-stream
	  'create-prolog
	  (compile-stack-expression
	    class-expression (maybe-add-unknown 'symbol unknown-allowed?))
	  block-of-variables?)
	(when unknown-allowed?
	  (emit-instruction-to-stream
	    epilog-stream
	    'begin-activity
	    (activity-index "create action")))
	(emit-instruction-to-stream
	  epilog-stream 'create-epilog var-spot? check-created-type?
	  block-of-variables?))
      block-of-variables?)))


;;; Instruction 52, the `create p-code instruction' is used to create transient
;;; objects.  It takes an expression which returns a symbol naming a class, and
;;; it takes a possible var spot and var spot type for the new frame.  It should
;;; create an instance of the given class, type test it for the var spot, and
;;; assign it to the local var spot, if supplied.

;;;   (CREATE symbol-expression var-spot? var-spot-type?)

(declare-instruction-for-optimizer
  'create-prolog
  '(no-wait-states
    cannot-write-local-variables
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor third-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter create-prolog
  (gensym-dstruct-bind ((nil symbol-expression var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream symbol-expression)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'create-epilog
  '(no-wait-states
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-and-fourth-as-var-spot-block
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-and-fourth-as-var-spot-block
    cannot-read-roles    
    creates-new-item
    cost 100))

(def-pseudo-instruction-byte-code-emitter create-epilog
  (gensym-dstruct-bind ((nil item-var-spot? item-var-spot-type-to-check?
			    var-spot-block?)
		       instruction)
    (when var-spot-block?
      (call-stack-instruction-emitter push-from-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'create)
    (cond (item-var-spot?
	   (when item-var-spot-type-to-check?
	     (call-stack-instruction-emitter type-check
	       byte-code-stream item-var-spot-type-to-check?))
	   (call-stack-instruction-emitter pop-into-surrounding-local-var
	     byte-code-stream item-var-spot?))
	  (t (emit-instruction-byte-code byte-code-stream 'pop)))))

(declare-instruction-for-optimizer
  'create
  '(no-wait-states
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor third-arg-as-var-spot
    cannot-write-local-variables
    cannot-read-roles    
    creates-new-item
    cost 100))

(def-pseudo-instruction-byte-code-emitter create
  (gensym-dstruct-bind ((nil the-class
			    item-var-spot? item-var-spot-type-to-check?) instruction)
    (emit-stack-node-tree byte-code-stream the-class)
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'create)
    (cond (item-var-spot?
	   (when item-var-spot-type-to-check?
	     (call-stack-instruction-emitter type-check
	       byte-code-stream item-var-spot-type-to-check?))
	   (call-stack-instruction-emitter pop-into-surrounding-local-var
	     byte-code-stream item-var-spot?))
	  (t (emit-instruction-byte-code byte-code-stream 'pop)))))



;;; The `delete-statement' emits a call to the delete instruction.
;;;
;;;   DELETE (item delete-connections-without-leaving-stubs?)

(defun print-delete-instruction (instruction)
  (twrite-string "DELETE ")
  (print-designation (second instruction)))

(def-action-compiler (delete print-delete-instruction)
  (gensym-dstruct-bind ((nil item delete-connections-without-leaving-stubs?
			    without-permanence-checks?)
		       
		       statement)
    (let ((block-of-variables?
	    (unless leave-on-stack?
	      (generate-block-of-new-variable-spots '(class item) 'datum))))
      (when (procedure-p *current-computation-frame*)
	(set-procedure-can-invalidate-environment *current-computation-frame*))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "delete action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'delete-prolog
	(compile-stack-expression
	  item (maybe-add-unknown '(class item) unknown-allowed?))
	(if without-permanence-checks?
	    (if delete-connections-without-leaving-stubs?
		'without-permanence-checks-without-leaving-stubs
		'without-permanence-checks)
	    delete-connections-without-leaving-stubs?)
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "delete action")))
      (emit-instruction-to-stream
	epilog-stream 'delete-epilog block-of-variables?)
      block-of-variables?)))


;;; Instruction 53, the `delete p-code instruction' is used to delete transient
;;; objects.  It takes a designation returning a transient object, and will
;;; delete that object from the system.  This function also will remove the
;;; deleted frame (and any deleted subframes) from all reachable environments of
;;; the containing code body invocation.

;;;   (DELETE designation delete-connections-without-leaving-stubs?)


(declare-instruction-for-optimizer
  'delete-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor fourth-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))


(def-pseudo-instruction-byte-code-emitter delete-prolog
  (gensym-dstruct-bind ((nil item delete-connections-without-leaving-stubs?
			    var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream item)
    (call-stack-instruction-emitter push-constant
      byte-code-stream
      (make-evaluation-symbol delete-connections-without-leaving-stubs?))
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (first var-spot-block?) (length var-spot-block?)))))


(declare-instruction-for-optimizer
     'delete-epilog
     '(no-wait-states
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor second-arg-as-var-spot-block
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor second-arg-as-var-spot-block
       deletes-item
       cannot-read-roles
       cost 100))


(def-pseudo-instruction-byte-code-emitter delete-epilog
  (gensym-dstruct-bind ((nil var-spot-block?) instruction)
    (when var-spot-block?
      ;; Push and test for deletion of the item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?))
      (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	byte-code-stream (second var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'delete)))


;;; The `transfer-statement' emits a call to the transfer instruction.
;;;
;;;   TRANSFER (transient-item workspace? x? y?)

(defun print-transfer-instruction (instruction)
  (gensym-dstruct-bind ((nil object-designation workspace-designation?
			    x-expression? y-expression?)
		       instruction)
    (twrite-string "TRANSFER ")
    (print-designation object-designation)
    (if workspace-designation?
	(progn
	  (twrite-string " TO ")
	  (print-designation workspace-designation?)
	  (when x-expression?
	    (twrite-string " AT (")
	    (write-expression x-expression?)
	    (twrite-string ", ")
	    (write-expression y-expression?)
	    (twrite-string ")")))
	(twrite-string " OFF"))))




;;; The 4.0 action `transfer-item-to-mouse' has been implemented by subterfuge.
;;; We redefine the meaning of the grammar "transfer <item-1> to the mouse of
;;; <item-2>" to enter the dragging state on the g2-window given by <item-2>.
;;; The meaning of this action in 3.0 would be to transfer <item-1> to the
;;; workspace given by the mouse attribute of <item-2>.  Old kbs will retain the
;;; old meaning until their rules are recompiled.
;;;  This redefinition required changes only to the transfer compiler and to
;;; the transfer instruction.  -fmw, 2/15/94

(def-concept transfer-item-to-mouse)


;;; The substitution-macro `transfer-item-to-mouse-designation?' is true
;;; if the given designation is of the form (the mouse <something>),
;;; which is compiled simply as <something> when it is the destination
;;; of a transfer action.  In that case, <something> should evaluate
;;; to a g2-window.

(def-substitution-macro transfer-item-to-mouse-designation? (designation)
  (and (consp designation)
       (eq (first designation) 'the)
       (eq (second designation) 'mouse)
       (not (null (third designation)))))


(def-action-compiler (transfer print-transfer-instruction)
  (gensym-dstruct-bind ((nil transient-item workspace-or-designation? x? y?)
		       statement)

    (let* ((transfer-item-to-mouse?
	     (transfer-item-to-mouse-designation? workspace-or-designation?))
	   type-of-destination
	   block-of-variables?)
      (when (and (and (consp workspace-or-designation?)
		      (=f (length workspace-or-designation?) 3)
		      (let ((role (second workspace-or-designation?)))
			(or (symbolp role)
			    (class-qualified-name-list-p role)))))
	)
      (setq type-of-destination (if transfer-item-to-mouse?
				    '(class g2-window)
				    
;				    '(class kb-workspace)
				    '(or (class item) (place-reference))))
      (setq block-of-variables?
	    (unless leave-on-stack?
	      (generate-block-of-new-variable-spots
		'(class item) type-of-destination 'number 'number)))
      (when (procedure-p *current-computation-frame*)
	
	(set-procedure-can-invalidate-environment *current-computation-frame*))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "transfer action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'transfer-prolog
	(compile-stack-expression
	  transient-item (maybe-add-unknown '(class item) unknown-allowed?))

	;; Handle "transfer <item> to the mouse of <window>".
	;; Here, we simply emit the desired type-checking. -fmw, 2/15/94
	(cond ((null workspace-or-designation?) nil)
	      (transfer-item-to-mouse?
	       ;; Looks like (the mouse <g2-window>)
	       (compile-stack-expression
		 (third workspace-or-designation?)
		 (maybe-add-unknown type-of-destination unknown-allowed?)))
	      (t
	       (compile-stack-expression
		 workspace-or-designation?
		 (maybe-add-unknown type-of-destination unknown-allowed?))))

	(if x?
	    (compile-stack-expression
	      x? (maybe-add-unknown 'number unknown-allowed?))
	    nil)
	(if y?
	    (compile-stack-expression
	      y? (maybe-add-unknown 'number unknown-allowed?))
	    nil)
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "transfer action")))
      (emit-instruction-to-stream
	epilog-stream
	'transfer-epilog
	(not (null workspace-or-designation?)) (not (null x?)) (not (null y?))
	block-of-variables?)
      block-of-variables?)))


;;; Instruction 54, the `transfer p-code instruction' is used to transfer
;;; objects from one workspace to another, or transient objects from floating in
;;; the ether to a workspace.  For the moment this will only work for transient
;;; objects.  It takes an object, a workspace, and optionally expressions for
;;; the x and y coordinates of the target workspace.  In the case where
;;; workspace (workspace-designation) is nil, the object is transferred "off" of
;;; the workspace.  (The item is transfered into "limbo" or "nowhere", which is
;;; just like being transfered to an active workspace, as far as activating is
;;; concerned.) 

;;;   TRANSFER (transient-item workspace? x? y?)
(declare-instruction-for-optimizer
  'transfer-prolog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor sixth-arg-as-var-spot-block
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles))

(def-pseudo-instruction-byte-code-emitter transfer-prolog
  (gensym-dstruct-bind ((nil item workspace? x? y? var-spot-block?)
		       instruction)
    (let ((nil-arg-count 0))
      (emit-stack-node-tree byte-code-stream item)
      (if workspace?
	  (emit-stack-node-tree byte-code-stream workspace?)
	  (incff nil-arg-count))
      (cond (x?
	     (when (>f nil-arg-count 0)
	       (call-stack-instruction-emitter push-nones byte-code-stream nil-arg-count)
	       (setq nil-arg-count 0))
	     (emit-stack-node-tree byte-code-stream x?))
	    (t (incff nil-arg-count)))
      (cond (y?
	     (when (>f nil-arg-count 0)
	       (call-stack-instruction-emitter push-nones byte-code-stream nil-arg-count)
	       (setq nil-arg-count 0))
	     (emit-stack-node-tree byte-code-stream y?))
	    (t (incff nil-arg-count)
	       (call-stack-instruction-emitter push-nones byte-code-stream nil-arg-count)))
      (when var-spot-block?
	(call-stack-instruction-emitter pop-into-block-of-local-vars
	  byte-code-stream (first var-spot-block?) (length var-spot-block?))))))

(declare-instruction-for-optimizer
     'transfer-epilog
     '(no-wait-states
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor fifth-arg-as-var-spot-block
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor fifth-arg-as-var-spot-block
       moves-objects
       cannot-read-roles))

(def-pseudo-instruction-byte-code-emitter transfer-epilog
  (gensym-dstruct-bind ((nil workspace-p? x-p? y-p? var-spot-block?) instruction)
    (when var-spot-block?
      (gensym-dstruct-bind ((item workspace x y) var-spot-block?)
	;; Push and test for deletion of the item.
	(call-stack-instruction-emitter push-from-surrounding-local-var byte-code-stream item)

	(if workspace-p?
	    ;; Push and test for deletion of the kb-workspace.
	    (call-stack-instruction-emitter push-from-surrounding-local-var
	      byte-code-stream workspace)
	    ;; There is no kb-workspace.
	    (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
 	      byte-code-stream workspace))
	(if x-p?
	    (call-stack-instruction-emitter push-from-surrounding-local-var byte-code-stream x)
	    (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	      byte-code-stream x))
	(if y-p?
	    (call-stack-instruction-emitter push-from-surrounding-local-var byte-code-stream y)
	    (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	      byte-code-stream y))))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'transfer)))



;;; The `change-system-attribute-statement' emits a call to the
;;; change-system-attribute instruction.
;;;
;;;   CHANGE-SYSTEM-ATTRIBUTE (item name-of-attribute value)

(defun print-change-system-attribute-instruction (instruction)
  (gensym-dstruct-bind ((nil item-designation (nil system-attribute-name)
			    value-expression)
		       instruction)
    (twrite-string "CHANGE THE ")
    (twrite system-attribute-name)
    (twrite-string " OF ")
    (print-designation item-designation)
    (twrite-string " TO ")
    (write-expression value-expression)))

(def-action-compiler (change-system-attribute
		       print-change-system-attribute-instruction)
  (gensym-dstruct-bind ((nil item name-of-attribute value) statement)
    (let ((block-of-variables?
	    (unless leave-on-stack?
	      (generate-block-of-new-variable-spots
		'(class item) 'symbol 'datum))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "change action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'change-system-attribute-prolog
	(compile-stack-expression
	  item (maybe-add-unknown '(class item) unknown-allowed?))
	(compile-stack-expression
	  name-of-attribute (maybe-add-unknown 'symbol unknown-allowed?))
	(compile-stack-expression
	  value (maybe-add-unknown 'datum unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "change action")))
      (emit-instruction-to-stream
	epilog-stream 'change-system-attribute-epilog block-of-variables?)
      block-of-variables?)))


;;; Instruction 55, the `change-system-attribute p-code instruction' takes an
;;; item-designation, attribute name, and an expression, and changes the
;;; attribute of item to be the value of the expression. 

;;; (CHANGE-SYSTEM-ATTRIBUTE item-designation 'name-of-attribute value-expression)

(declare-instruction-for-optimizer
  'change-system-attribute-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor fifth-arg-as-var-spot
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter change-system-attribute-prolog
  (gensym-dstruct-bind ((nil item name-of-attribute value var-spot-block?)
		       instruction)
    (emit-stack-node-tree byte-code-stream item)
    (emit-stack-node-tree byte-code-stream name-of-attribute)
    (emit-stack-node-tree byte-code-stream value)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (first var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'change-system-attribute-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    cannot-read-roles
    writes-certain-system-attributes
    cost 100))

(def-pseudo-instruction-byte-code-emitter change-system-attribute-epilog
  (gensym-dstruct-bind ((nil var-spot-block?) instruction)
    (when var-spot-block?
      ;; Push and test for deletion of the item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?))
      (call-stack-instruction-emitter push-from-block-of-local-vars
	byte-code-stream (second var-spot-block?)
	(length (cdr var-spot-block?))))
    (call-stack-instruction-emitter funcall-instruction
      byte-code-stream 'change-system-attribute)))



;;; The `change-the-text-of-attribute-statement' emits a call to the
;;; change-the-text-of-attribute instruction.
;;;
;;;   CHANGE-THE-TEXT-OF-ATTRIBUTE (item-or-place text)

;; This statement was previous called change-system-attribute-as-text.  Now it
;; applies to user attributes as well.

(defun print-change-the-text-of-instruction (instruction)
  (gensym-dstruct-bind ((nil item-designation value-expression)
		       instruction)
    (twrite-string "CHANGE THE TEXT OF ")
    (print-designation item-designation)
    (twrite-string " TO ")
    (write-expression value-expression))) 

(def-action-compiler (change-the-text-of-attribute
		       print-change-the-text-of-instruction)
  (gensym-dstruct-bind ((nil item-or-place text) statement)
    (let ((block-of-variables? (unless leave-on-stack?
				 (generate-block-of-new-variable-spots
				   '(or (class item) (place-reference))
				   'text)))
	  ;; Allow references to authorized system-slots.
	  (compile-reference-to-system-slot t))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "change text action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'change-the-text-of-attribute-prolog
	(compile-stack-expression
	  item-or-place
	  (maybe-add-unknown '(or (class item) (place-reference)) unknown-allowed?))
	(compile-stack-expression
	  text (maybe-add-unknown 'text unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "change text action")))
      (emit-instruction-to-stream
	epilog-stream 'change-the-text-of-attribute-epilog
	block-of-variables?)
      block-of-variables?)))


;;; Instruction 64, the `change-the-text-of-attribute p-code instruction'
;;; takes an item-designation, attribute name, and an text-expression, and
;;; changes the attribute of item to be the parse of the value of the
;;; text-expression.  This differs from the change-system-attribute instruction
;;; which does not parse its value.

;;; (CHANGE-THE-TEXT-OF-ATTRIBUTE
;;;     item-designation name-of-attribute text-expression)

;(def-pseudo-instruction-byte-code-emitter change-system-attribute-as-text
;  (gensym-dstruct-bind ((nil item name-of-attribute text-expression)
;		       instruction)
;    (emit-stack-node-tree byte-code-stream item)
;    (emit-stack-node-tree byte-code-stream name-of-attribute)
;    (emit-stack-node-tree byte-code-stream text-expression)
;    (call-stack-instruction-emitter funcall-instruction
;      byte-code-stream 'change-system-attribute-as-text)))

(declare-instruction-for-optimizer
  'change-the-text-of-attribute-prolog
  '(no-wait-states
    cannot-write-local-variables
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor fourth-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter change-the-text-of-attribute-prolog
  (gensym-dstruct-bind ((nil item-or-place text-expression var-spot-block?)
		       instruction)
    (emit-stack-node-tree byte-code-stream item-or-place)
    (emit-stack-node-tree byte-code-stream text-expression)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (first var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'change-the-text-of-attribute-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot
    cannot-read-roles
    change-arbitrary-attribute-values
    cost 100))

(def-pseudo-instruction-byte-code-emitter change-the-text-of-attribute-epilog
  (gensym-dstruct-bind ((nil var-spot-block?) instruction)
    (when var-spot-block?
      ;; Push and test for deletion of the item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?))
      (call-stack-instruction-emitter push-from-block-of-local-vars
	byte-code-stream (second var-spot-block?) (length (cdr var-spot-block?))))
    (call-stack-instruction-emitter funcall-instruction
      byte-code-stream 'change-the-text-of-attribute)))



;;; The `change-nth-element-statement' emits a call to the change-nth-element
;;; instruction.
;;;
;;;   CHANGE-NTH-ELEMENT (element-designation element-value)

;; Emits arguments as: ITEM, ELEMENT, INDEX

(defun print-change-nth-element-instruction (instruction)
  (gensym-dstruct-bind ((nil g2-array-element-designation element-expression)
		       instruction)
    (twrite-string "CHANGE ")
    (print-designation g2-array-element-designation)  ;; e.g., my-array [index]
    (twrite-string " = ")
    ;; element expression can be a datum expression or item designation.
    (write-expression element-expression)))

(def-action-compiler (change-nth-element print-change-nth-element-instruction)
  (let ((designation (second statement))
	(element (third statement))
	(item nil)
	(index nil)
	(block-of-variables? (unless leave-on-stack?
			       ;; index is put as the third arg on the stack.
			       (generate-block-of-new-variable-spots
				 '(class item) 'item-or-datum 'integer)))
	(action-compiler-error? nil))
    (cond ((symbolp designation)
	   ;; EVERY case, where designation is the class.
	   (setq item (nth 1 statement))
	   (setq index (nth 2 statement))
	   (setq element (nth 3 statement)))
	  ((and (consp designation)
		(consp (second designation))
		(eq (car-of-cons (second designation)) 'nth-element))
	   (setq item (third designation))
	   (setq index (fourth designation)))
	  ((and (consp designation) (cddr designation))
	   ;; Fix the parse.  The nth-element is located elsewhere (not the
	   ;; outermost role).  This is an old 3.0 parse, which is still valid
	   ;; in 4.0, but produces a warning.
	   ;; NOTE: that this grammar will be obsolete in a release after 4.0.
	   ;; For more information see the grammar for change-nth-element.  -
	   ;; cpm, 11/11/94
	   (loop for current-designation =  designation
					 then (and (listp current-designation)
						   (third current-designation))
		 for domain-designation = (third current-designation)
		 for domain-role = (second domain-designation)
		 until (or (null current-designation)
			   (and (listp domain-role)
				(eq (first domain-role) 'nth-element)))
		 finally
		   (cond 
		     ((and (listp domain-role)
			   (eq (first domain-role) 'nth-element))

					; Improve the wording of the warning
					; message!!  - cpm, 11/11/94
		      (compiler-warning
			"parentheses should be added around the expression ~
                        before the [ ] in `~ND' to avoid misinterpretation.  ~
                        (This current interpretation, which G2 ~
                        Version 3.0 introduced in error, is ~
                        subject to change in a future release)"
			designation)
		      ;; Fixup the parse so that it will execute as in version
		      ;; 3.0.  Remove the nth-element role.   
		      ;; Note that CONSES of the domain-designation are dropped.
		      ;; This is okay because they are PHRASE-CONSES and they
		      ;; are automatically reclaimed.
		      (setf (third current-designation)
			    (third domain-designation))
		      ;; The entire designation becomes the array-or-list
		      ;; designation.
		      (setq item designation)
		      (setq index (fourth domain-designation)))
		     (t
		      (setq action-compiler-error? t)
		      (compiler-error
			"Cannot compile a statement containing the change ~
                         action.  `~ND' does not refer to an array or list ~
                         element"
			designation)))))
	  (t
	   (setq action-compiler-error? t)
	   (compiler-error
	     "Cannot compile a statement containing the change ~
              action.  `~ND' does not refer to an array or list ~
              element"
	     designation)))

    (unless action-compiler-error?
      (let ((plist (create-pseudo-instruction-property-list)))
	(emit-instruction-to-stream
	  prolog-stream
	  'begin-activity
	  (activity-index "change array or list element action")
	  unknown-allowed?)
	;; Emit: ITEM, ELEMENT, INDEX
	;; Note that this ordering differs from the order of the expressions in
	;; the parse.
	(emit-instruction-to-stream
	  prolog-stream
	  'change-nth-element-prolog
	  (compile-stack-expression
	    item (maybe-add-unknown '(or (class g2-array) (class g2-list))
				    unknown-allowed?))
	  (compile-stack-expression
		element
		(maybe-add-unknown 'item-or-datum unknown-allowed?))
	  (compile-stack-expression
	    index (maybe-add-unknown 'integer unknown-allowed?))
	  unknown-allowed?
	  block-of-variables?
	  plist)
	(when unknown-allowed?
	  (emit-instruction-to-stream
	    epilog-stream
	    'begin-activity
	    (activity-index "change array or list element action")))
	(emit-instruction-to-stream
	  epilog-stream
	  'change-nth-element-epilog
	  block-of-variables?
	  plist)))
    block-of-variables?))

(defun print-change-nth-element-to-no-value-instruction (instruction)
  (gensym-dstruct-bind ((nil g2-array-element-designation )
		       instruction)
    (twrite-string "CHANGE ")
    (print-designation g2-array-element-designation)  ;; e.g., my-array [index]
    (twrite-string " = no-value")))

(def-action-compiler (change-nth-element-to-no-value
		       print-change-nth-element-to-no-value-instruction)
  (let ((designation (second statement))
	(item nil)
	(index nil)
	(block-of-variables? (unless leave-on-stack?
			       ;; index is put as the third arg on the stack.
			       (generate-block-of-new-variable-spots
				 '(class item) 'item-or-datum 'integer)))
	(action-compiler-error? nil))
    (cond ((symbolp designation)
	   ;; EVERY case, where designation is the class.
	   (setq item (nth 1 statement))
	   (setq index (nth 2 statement))
	   )
	  ((and (consp designation)
		(consp (second designation))
		(eq (car-of-cons (second designation)) 'nth-element))
	   (setq item (third designation))
	   (setq index (fourth designation)))
	  ((and (consp designation) (cddr designation))
	   ;; Fix the parse.  The nth-element is located elsewhere (not the
	   ;; outermost role).  This is an old 3.0 parse, which is still valid
	   ;; in 4.0, but produces a warning.
	   ;; NOTE: that this grammar will be obsolete in a release after 4.0.
	   ;; For more information see the grammar for change-nth-element.  -
	   ;; cpm, 11/11/94
	   (loop for current-designation =  designation
					 then (and (listp current-designation)
						   (third current-designation))
		 for domain-designation = (third current-designation)
		 for domain-role = (second domain-designation)
		 until (or (null current-designation)
			   (and (listp domain-role)
				(eq (first domain-role) 'nth-element)))
		 finally
		   (cond 
		     ((and (listp domain-role)
			   (eq (first domain-role) 'nth-element))

					; Improve the wording of the warning
					; message!!  - cpm, 11/11/94
		      (compiler-warning
			"parentheses should be added around the expression ~
                        before the [ ] in `~ND' to avoid misinterpretation.  ~
                        (This current interpretation, which G2 ~
                        Version 3.0 introduced in error, is ~
                        subject to change in a future release)"
			designation)
		      ;; Fixup the parse so that it will execute as in version
		      ;; 3.0.  Remove the nth-element role.   
		      ;; Note that CONSES of the domain-designation are dropped.
		      ;; This is okay because they are PHRASE-CONSES and they
		      ;; are automatically reclaimed.
		      (setf (third current-designation)
			    (third domain-designation))
		      ;; The entire designation becomes the array-or-list
		      ;; designation.
		      (setq item designation)
		      (setq index (fourth domain-designation)))
		     (t
		      (setq action-compiler-error? t)
		      (compiler-error
			"Cannot compile a statement containing the change ~
                         action.  `~ND' does not refer to an array or list ~
                         element"
			designation)))))
	  (t
	   (setq action-compiler-error? t)
	   (compiler-error
	     "Cannot compile a statement containing the change ~
              action.  `~ND' does not refer to an array or list ~
              element"
	     designation)))

    (unless action-compiler-error?
      (let ((plist (create-pseudo-instruction-property-list)))
	(emit-instruction-to-stream
	  prolog-stream
	  'begin-activity
	  (activity-index "change array or list element action")
	  unknown-allowed?)
	;; Emit: ITEM, ELEMENT, INDEX
	;; Note that this ordering differs from the order of the expressions in
	;; the parse.
	(emit-instruction-to-stream
	  prolog-stream
	  'change-nth-element-to-no-value-prolog
	  (compile-stack-expression
	    item (maybe-add-unknown '(or (class g2-array) (class g2-list))
				    unknown-allowed?))
	  (compile-stack-expression
	    index (maybe-add-unknown 'integer unknown-allowed?))
	  unknown-allowed?
	  block-of-variables?
	  plist)
	(when unknown-allowed?
	  (emit-instruction-to-stream
	    epilog-stream
	    'begin-activity
	    (activity-index "change array or list element action")))
	(emit-instruction-to-stream
	  epilog-stream
	  'change-nth-element-to-no-value-epilog
	  block-of-variables?
	  plist)))
    block-of-variables?))



;;; Instruction 65, the `change-nth-element p-code instruction' takes a g2-array
;;; or g2-list designation, an element expression (which could be a datum value
;;; or an item, depending on the array or list element type) and an index
;;; expression.

;;; (CHANGE-NTH-ELEMENT item-designation element-expression index-expression)


(declare-instruction-for-optimizer
  'change-nth-element-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor sixth-arg-as-var-spot
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter change-nth-element-prolog
  (gensym-dstruct-bind ((nil item element index
			    unknown-allowed? var-spot-block? plist)
		       instruction)
    (setf (pseudo-instruction-property plist 'value-type-of-array)
	  (stack-node-value-type item))
    (setf (pseudo-instruction-property plist 'value-type-of-index)
	  (stack-node-value-type index))
    (emit-stack-node-tree byte-code-stream item)
    (emit-stack-node-tree byte-code-stream element)
    (emit-coerce-matching-element-type-or-unknown-if-necessary
      byte-code-stream item element unknown-allowed?)
    (emit-stack-node-tree byte-code-stream index)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (first var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'change-nth-element-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    cannot-read-roles
    writes-list-or-array-elements
    cost 100))

(def-pseudo-instruction-byte-code-emitter change-nth-element-epilog
  (gensym-dstruct-bind ((nil var-spot-block? plist) instruction)
    (when var-spot-block?
      ;; Push and test for deletion of the array/list.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?))
      ;; Emit and test for the deleted element.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (second var-spot-block?))
      ;; Index
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (third var-spot-block?)))
    (cond
      ((and allow-inline-evaluate-role-instructions-p
	    (pseudo-instruction-property plist 'value-type-of-index)
	    (type-specification-subtype-p
	      (pseudo-instruction-property plist 'value-type-of-index)
	      'integer))
       (cond ((type-specification-subtype-p
		(pseudo-instruction-property plist 'value-type-of-array)
		'(class integer-array))
	      (emit-instruction-byte-code
		byte-code-stream 'change-nth-integer-array-element))
	     ((type-specification-subtype-p
		(pseudo-instruction-property plist 'value-type-of-array)
		'(class float-array))
	      (emit-instruction-byte-code
		byte-code-stream 'change-nth-float-array-element))
	     (t
	      (call-stack-instruction-emitter funcall-instruction
		byte-code-stream 'change-nth-element))))
      (t
       (call-stack-instruction-emitter funcall-instruction
	 byte-code-stream 'change-nth-element)))
    (reclaim-create-pseudo-instruction-property-list plist)))



(declare-instruction-for-optimizer
  'change-nth-element-to-no-value-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor sixth-arg-as-var-spot
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter change-nth-element-to-no-value-prolog
  (gensym-dstruct-bind ((nil item ;nil ;element
			    index
			    nil ;unknown-allowed?
			    var-spot-block? plist)
		       instruction)
    (setf (pseudo-instruction-property plist 'value-type-of-array)
	  (stack-node-value-type item))
    (setf (pseudo-instruction-property plist 'value-type-of-index)
	  (stack-node-value-type index))
    (emit-stack-node-tree byte-code-stream item)
    ;; Emit the no-value
    (call-stack-instruction-emitter push-nones byte-code-stream 1)
    (emit-instruction-byte-code
      byte-code-stream 'coerce-matching-element-type)
;    (emit-stack-node-tree byte-code-stream element)
;    (emit-coerce-matching-element-type-or-unknown-if-necessary
;      byte-code-stream item element unknown-allowed?)
    (emit-stack-node-tree byte-code-stream index)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (first var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'change-nth-element-to-no-value-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    cannot-read-roles
    writes-list-or-array-elements
    cost 100))

(def-pseudo-instruction-byte-code-emitter change-nth-element-to-no-value-epilog
  (gensym-dstruct-bind ((nil var-spot-block? plist) instruction)
    (when var-spot-block?
      ;; Push and test for deletion of the array/list.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?))
      ;; Emit no-value (do not emit from var-spot block because no-value is treated
      ;; as invalid by the push-from-local-var instruction, and we already know that
      ;; it will be no-value in any case).
      (call-stack-instruction-emitter push-nones byte-code-stream 1)
      ;; Index
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (third var-spot-block?)))
    (cond
      ((and allow-inline-evaluate-role-instructions-p
	    (pseudo-instruction-property plist 'value-type-of-index)
	    (type-specification-subtype-p
	      (pseudo-instruction-property plist 'value-type-of-index)
	      'integer))
       (cond ((type-specification-subtype-p
		(pseudo-instruction-property plist 'value-type-of-array)
		'(class integer-array))
	      (emit-instruction-byte-code
		byte-code-stream 'change-nth-integer-array-element))
	     ((type-specification-subtype-p
		(pseudo-instruction-property plist 'value-type-of-array)
		'(class float-array))
	      (emit-instruction-byte-code
		byte-code-stream 'change-nth-float-array-element))
	     (t
	      (call-stack-instruction-emitter funcall-instruction
		byte-code-stream 'change-nth-element))))
      (t
       (call-stack-instruction-emitter funcall-instruction
	 byte-code-stream 'change-nth-element)))
    (reclaim-create-pseudo-instruction-property-list plist)))



;;; The `g2-list-insert-expression-statement' emits a call to the
;;; g2-list-insert-expression instruction.

;;; Note that this action is being phased out starting in 4.0.  The existing
;;; action will still be supported, but any new edits or compiles of the action
;;; will parse and compile into the new G2-LIST-INSERT action. 

;; Because of the above change, the printer and action will be left as is to
;; support existing KB's, and the compiler and the pseudo-instruction byte-code
;; emitter are commented out.  - cpm, 11/18/93

;;; G2-LIST-INSERT-EXPRESSION 
;;;    (g2-list required-element-type element-datum-1 insertion-type 
;;;     element-datum-2?)

(defun print-g2-list-insert-expression-instruction (instruction)
  (gensym-dstruct-bind
    ((nil list-designation grammar-list-type element-expression-1 insert-type
	  element-expression-2)
     instruction)
    (twrite-string "INSERT ")
    (write-expression element-expression-1)
    (case insert-type
      (beginning
       (tformat " AT THE BEGINNING OF THE ~a LIST " grammar-list-type)
       (print-designation list-designation))
      (end
       (tformat " AT THE END OF THE ~a LIST " grammar-list-type)
       (print-designation list-designation))
      (before
       (twrite-string " BEFORE ")
       (write-expression element-expression-2)
       (tformat " IN THE ~a LIST " grammar-list-type)
       (print-designation list-designation))
      (after
       (twrite-string " AFTER ")
       (write-expression element-expression-2)
       (tformat " IN THE ~a LIST " grammar-list-type)
       (print-designation list-designation))
      #+development
      (t (cerror
	   "error!"
	   "unknown g2-list insert expression while printing instruction!")))))

;(def-action-compiler (g2-list-insert-expression
;                       print-g2-list-insert-expression-instruction)
;  (gensym-dstruct-bind ((nil g2-list required-element-type datum-1 insertion-type
;                            datum-2?) statement)
;    (let ((block-of-variables?
;            (unless leave-on-stack?
;              (generate-block-of-new-variable-spots
;                '(class item) 'symbol 'datum 'symbol 'datum))))
;      (emit-instruction-to-stream
;        prolog-stream
;        'begin-activity
;        (activity-index "insert action")
;        unknown-allowed?)
;      (emit-instruction-to-stream
;        prolog-stream
;        'g2-list-insert-expression-prolog
;        (compile-stack-expression
;          g2-list (maybe-add-unknown '(class g2-list) unknown-allowed?))
;        required-element-type    
;        (compile-stack-expression
;          datum-1 (maybe-add-unknown 'datum unknown-allowed?))
;        insertion-type
;        (if datum-2?
;            (compile-stack-expression
;              datum-2? (maybe-add-unknown 'datum unknown-allowed?))
;            nil)
;        block-of-variables?)
;      (when unknown-allowed?
;        (emit-instruction-to-stream
;          epilog-stream
;          'begin-activity
;          (activity-index "insert action")))
;      (emit-instruction-to-stream
;        epilog-stream 'g2-list-insert-expression-epilog (not (null datum-2?))
;        block-of-variables?)
;      block-of-variables?)))


;;; Instruction 56, the `g2-list-insert-expression p-code instruction'
;;; takes a g2-list, a required-element-type, a datum element, an
;;; insertion-type, and a second datum element (or nil).  The instruction
;;; inserts the first datum into the list at the indicated position.  If the
;;; list is not valid or if the element is not a valid type for the list, a
;;; warning is given.  There are several insertion-types: beginning, end,
;;; before, and after.  The second datum element is the element that is used in
;;; the before and after insert-types to indicate the element position.  This
;;; arg can be nil if the insertion-type does not use this value.

;;; G2-LIST-INSERT-EXPRESSION 
;;;    (g2-list required-element-type datum-1 insertion-type datum-2?)

;(def-pseudo-instruction-byte-code-emitter g2-list-insert-expression-prolog
;  (gensym-dstruct-bind ((nil g2-list required-element-type datum-1 insertion-type
;                            datum-2? var-spot-block?)
;                       instruction)
;    (emit-stack-node-tree byte-code-stream g2-list)
;                                                       ; Use "required element
;                                                       ; type" to emit type
;                                                       ; checking code??  cpm,
;                                                       ; 7/5/91
;    (call-stack-instruction-emitter push-constant
;      byte-code-stream (make-evaluation-symbol required-element-type))
;    (emit-stack-node-tree byte-code-stream datum-1)
;    (call-stack-instruction-emitter push-constant
;      byte-code-stream (make-evaluation-symbol insertion-type))
;    (if (null datum-2?)
;        (call-stack-instruction-emitter push-constant
;          byte-code-stream (make-evaluation-symbol nil))
;        (emit-stack-node-tree byte-code-stream datum-2?))
;    (when var-spot-block?
;      (call-stack-instruction-emitter pop-into-block-of-local-vars
;        byte-code-stream (first var-spot-block?) (length var-spot-block?)))))

;(def-pseudo-instruction-byte-code-emitter g2-list-insert-expression-epilog
;  (gensym-dstruct-bind ((nil datum-2-p? var-spot-block?) instruction)
;    (when var-spot-block?
;      (gensym-dstruct-bind ((g2-list required-element-type datum-1 insertion-type
;                                    datum-2?)
;                           var-spot-block?)
;        ;; Push and test for deletion of the item.
;        (call-stack-instruction-emitter push-from-surrounding-local-var
;          byte-code-stream g2-list)
;        (call-stack-instruction-emitter push-from-surrounding-local-var
;          byte-code-stream required-element-type)
;        (call-stack-instruction-emitter push-from-surrounding-local-var
;          byte-code-stream datum-1)
;        (call-stack-instruction-emitter push-from-surrounding-local-var
;          byte-code-stream insertion-type)
;        (if datum-2-p?
;            (call-stack-instruction-emitter push-from-surrounding-local-var
;              byte-code-stream datum-2?)
;            (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
;              byte-code-stream datum-2?))))
;    (call-stack-instruction-emitter funcall-instruction
;      byte-code-stream 'g2-list-insert-expression)))




;;; The `g2-list-insert-designation-statement' emits a call to the
;;; g2-list-insert-designation instruction.

;;; Note that this action is being phased out starting in 4.0.  The existing
;;; action will still be supported, but any new edits or compiles of the action
;;; will parse and compile into the new G2-LIST-INSERT action. 

;; Because of the above change, the printer and action will be left as is to
;; support existing KB's, and the compiler and the pseudo-instruction byte-code
;; emitter are commented out.  - cpm, 11/18/93

;;; G2-LIST-INSERT-DESIGNATION
;;;    (g2-list required-element-type item-1 insertion-type item-2?)

(defun print-g2-list-insert-designation-instruction (instruction)
  (gensym-dstruct-bind
    ((nil list-designation grammar-list-type element-designation-1 insert-type
	  element-designation-2)
     instruction)
    (twrite-string "INSERT ")
    (print-designation element-designation-1)
    (case insert-type
      (beginning
       (tformat " AT THE BEGINNING OF THE ~a LIST " grammar-list-type)
       (print-designation list-designation))
      (end
       (tformat " AT THE END OF THE ~a LIST " grammar-list-type)
       (print-designation list-designation))
      (before
       (twrite-string " BEFORE ")
       (print-designation element-designation-2)
       (tformat " IN THE ~a LIST " grammar-list-type)
       (print-designation list-designation))
      (after
       (twrite-string " AFTER ")
       (print-designation element-designation-2)
       (tformat " IN THE ~a LIST " grammar-list-type)
       (print-designation list-designation))
      #+development
      (t (cerror
	   "error!"
	   "unknown g2-list insert expression while printing instruction!")))))
;
;(def-action-compiler (g2-list-insert-designation
;                       print-g2-list-insert-designation-instruction)
;  (gensym-dstruct-bind ((nil g2-list required-element-type item-1 insertion-type
;                            item-2?)
;                       statement)
;    (let ((block-of-variables?
;            (unless leave-on-stack?
;              (generate-block-of-new-variable-spots
;                '(class item) 'symbol '(class item) 'symbol '(class item)))))
;      (emit-instruction-to-stream
;        prolog-stream
;        'begin-activity
;        (activity-index "insert action")
;        unknown-allowed?)
;      (emit-instruction-to-stream
;        prolog-stream
;        'g2-list-insert-designation-prolog
;        (compile-stack-expression
;          g2-list (maybe-add-unknown '(class g2-list) unknown-allowed?))
;        required-element-type    
;        (compile-stack-expression
;          item-1 (maybe-add-unknown '(class item) unknown-allowed?))
;        insertion-type
;        (if item-2?
;            (compile-stack-expression
;              item-2? (maybe-add-unknown '(class item) unknown-allowed?))
;            nil)
;        block-of-variables?)
;      (when unknown-allowed?
;        (emit-instruction-to-stream
;          epilog-stream
;          'begin-activity
;          (activity-index "insert action")))
;      (emit-instruction-to-stream
;        epilog-stream 'g2-list-insert-designation-epilog (not (null item-2?))
;        block-of-variables?)
;      block-of-variables?)))


;;; Instruction 57, the `g2-list-insert-designation p-code instruction' takes a
;;; g2-list, a required-element-type, an item element, an insertion-type, and a
;;; second item element (or nil).  The instruction inserts the first element
;;; into the list at the indicated position.  If the list is not valid or if the
;;; element is not valid type for the list a warning is given.  There are
;;; several insertion-types: beginning, end, before, and after.  The second
;;; element is the element that is used in the before and after insertion-types
;;; to indicate the element position.  This arg can be nil if the insertion-type
;;; does not use this value.

;;; G2-LIST-INSERT-DESIGNATION
;;;    (g2-list required-element-type item-1 insertion-type item-2?)

;(def-pseudo-instruction-byte-code-emitter g2-list-insert-designation-prolog
;  (gensym-dstruct-bind ((nil g2-list required-element-type item-1 insertion-type
;                            item-2? var-spot-block?)
;                       instruction)
;    (emit-stack-node-tree byte-code-stream g2-list)
;    (call-stack-instruction-emitter push-constant
;      byte-code-stream (make-evaluation-symbol required-element-type))
;    (emit-stack-node-tree byte-code-stream item-1)
;    (call-stack-instruction-emitter push-constant
;      byte-code-stream (make-evaluation-symbol insertion-type))
;    (if (null item-2?)
;        (call-stack-instruction-emitter push-constant
;          byte-code-stream (make-evaluation-symbol nil))
;        (emit-stack-node-tree byte-code-stream item-2?))
;    (when var-spot-block?
;      (call-stack-instruction-emitter pop-into-block-of-local-vars
;        byte-code-stream (first var-spot-block?) (length var-spot-block?)))))
;
;(def-pseudo-instruction-byte-code-emitter g2-list-insert-designation-epilog
;  (gensym-dstruct-bind ((nil item-2-p? var-spot-block?) instruction)
;    (when var-spot-block?
;      (gensym-dstruct-bind ((g2-list required-element-type item-1 insertion-type
;                                    item-2?)
;                           var-spot-block?)
;        ;; Push and test for deletion of the item.
;        (call-stack-instruction-emitter push-from-surrounding-local-var
;          byte-code-stream g2-list)
;        (call-stack-instruction-emitter push-from-surrounding-local-var
;          byte-code-stream required-element-type)
;        (call-stack-instruction-emitter push-from-surrounding-local-var
;          byte-code-stream item-1)
;        (call-stack-instruction-emitter push-from-surrounding-local-var
;          byte-code-stream insertion-type)
;        (if item-2-p?
;            (call-stack-instruction-emitter push-from-surrounding-local-var
;              byte-code-stream item-2?)
;            (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
;              byte-code-stream item-2?))))
;    (call-stack-instruction-emitter funcall-instruction
;      byte-code-stream 'g2-list-insert-designation)))



;;; The `g2-list-insert-statement' emits a call to the g2-list-insert
;;; instruction.  This is a new form of the INSERT action, which does not
;;; require a element-type specified in the grammar.  This was added for version
;;; 4.0.
;;;
;;; G2-LIST-INSERT
;;;   (g2-list new-item-or-datum-element existing-item-or-datum-element?
;;;    insertion-type)

(defun print-g2-list-insert-instruction (instruction)
  (gensym-dstruct-bind
    ((nil list-designation item-or-datum element? insert-type) instruction)
    (twrite-string "INSERT ")
    (write-expression item-or-datum)
    (case insert-type
      (beginning
       (twrite-string " AT THE BEGINNING OF ")
       (print-designation list-designation))
      (end
       (twrite-string " AT THE END OF ")
       (print-designation list-designation))
      (before
       (twrite-string " BEFORE ")
       (write-expression element?)
       (twrite-string " IN ")
       (print-designation list-designation))
      (after
       (twrite-string " AFTER ")
       (write-expression element?)
       (twrite-string " IN ")
       (print-designation list-designation))
      #+development
      (t (cerror
	   "error!"
	   "Unknown G2-list INSERT action type in printing instruction!")))))


(def-action-compiler (g2-list-insert print-g2-list-insert-instruction)
  (gensym-dstruct-bind ((nil g2-list item-or-datum element? insertion-type)
		       statement)
    (let ((block-of-variables?
	    (unless leave-on-stack?
	      (generate-block-of-new-variable-spots
		'(class item) 'item-or-datum 'item-or-datum 'symbol))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "insert action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'g2-list-insert-prolog
	(compile-stack-expression
	  g2-list (maybe-add-unknown '(class g2-list) unknown-allowed?))
	(compile-stack-expression
	  item-or-datum (maybe-add-unknown 'item-or-datum unknown-allowed?))
	(if element?
	    (compile-stack-expression
	      element? (maybe-add-unknown 'item-or-datum unknown-allowed?))
	    nil)
	insertion-type
	unknown-allowed?
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "insert action")))
      (emit-instruction-to-stream
	epilog-stream 'g2-list-insert-epilog (not (null element?))
	block-of-variables?)
      block-of-variables?)))



;;; The `g2-list-insert p-code instruction' takes a g2-list, an item-or-datum,
;;; an element (or nil), and an insertion-type.  The instruction inserts the
;;; item-or-datum into the list at the indicated position.

;;; An error is signalled, if the list is not valid or if the element is not a
;;; valid type for the list.

(declare-instruction-for-optimizer
  'g2-list-insert-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor seventh-arg-as-var-spot-block
    values-produced 5
    cannot-read-roles
    cannot-write-roles
    cost 2))


;;; There are several insertion-types: beginning, end, before, and after.  The
;;; element argument is used in the "before" and "after" insert-types to
;;; indicate the element position.  The element argument is NIL if the
;;; insertion-type is "beginning" or "end".

;;; This is a new version of the INSERT action that does not take a required
;;; element-type argument.  This was implemented for version 4.0.

;;; G2-LIST-INSERT
;;;   (g2-list item-or-datum element? insertion-type)

(def-pseudo-instruction-byte-code-emitter g2-list-insert-prolog
  (gensym-dstruct-bind
	((nil g2-list item-or-datum element? insertion-type unknown-allowed?
	      var-spot-block?)
	 instruction)
    (emit-stack-node-tree byte-code-stream g2-list)
    (emit-stack-node-tree byte-code-stream item-or-datum)
    (cond
      ((null element?)
       (emit-coerce-matching-element-type-or-unknown-if-necessary
	 byte-code-stream g2-list item-or-datum unknown-allowed?)
       (call-stack-instruction-emitter push-nones byte-code-stream 1))
      ;; in this case the element should be an integer, & not
      ;; match the type of the list
      ((memq insertion-type '(before-element after-element))
       (unless
	   (stack-node-matches-element-type-p g2-list item-or-datum)
	 (call-stack-instruction-emitter
	   funcall-instruction
	   byte-code-stream
	   (if unknown-allowed?
	       'coerce-item-or-values-to-matching-element-type-or-unknown
	       'coerce-item-or-values-to-matching-element-type)
	   2 2))
       (emit-stack-node-tree byte-code-stream element?)
       (call-stack-instruction-emitter type-check byte-code-stream 'integer))
      (t
       (emit-stack-node-tree byte-code-stream element?)
       (unless
	   (and (stack-node-matches-element-type-p g2-list item-or-datum)
		(stack-node-matches-element-type-p g2-list element?))
	 (call-stack-instruction-emitter
	   funcall-instruction
	   byte-code-stream
	   (if unknown-allowed?
	       'coerce-item-or-values-to-matching-element-type-or-unknown
	       'coerce-item-or-values-to-matching-element-type)
	   3 3))))
    (call-stack-instruction-emitter push-constant
      byte-code-stream (make-evaluation-symbol insertion-type))
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (first var-spot-block?) (length var-spot-block?)))))


(declare-instruction-for-optimizer
  'g2-list-insert-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor third-arg-as-var-spot-block
    values-consumed 5
    cannot-read-roles
    writes-list-or-array-elements
    cost 100))

(def-pseudo-instruction-byte-code-emitter g2-list-insert-epilog
  (gensym-dstruct-bind ((nil element-p? var-spot-block?) instruction)
    (when var-spot-block?
      (gensym-dstruct-bind ((g2-list item-or-datum element? insertion-type)
			   var-spot-block?)
	;; Push and test for deletion of the item.
	(call-stack-instruction-emitter push-from-surrounding-local-var
	  byte-code-stream g2-list)
	(call-stack-instruction-emitter push-from-surrounding-local-var
	  byte-code-stream item-or-datum)
	(if element-p?
	    (call-stack-instruction-emitter push-from-surrounding-local-var
	      byte-code-stream element?)
	    (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	      byte-code-stream element?))
	(call-stack-instruction-emitter push-from-surrounding-local-var
	  byte-code-stream insertion-type)))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'g2-list-insert)))



;;; The `g2-list-remove-expression-statement' emits a call to the
;;; g2-list-remove-expression instruction.

;;; Note that this action is being phased out starting in 4.0.  The existing
;;; action will still be supported, but any new edits or compiles of the action
;;; will parse and compile into the new G2-LIST-REMOVE action. 

;; Because of the above change, the printer and action will be left as is to
;; support existing KB's, and the compiler and the pseudo-instruction byte-code
;; emitter are commented out.  - cpm, 11/18/93

;;; G2-LIST-REMOVE-EXPRESSION 
;;;    (g2-list required-element-type removal-type element?)

(defun print-g2-list-remove-expression-instruction (instruction)
  (gensym-dstruct-bind
    ((nil list-designation grammar-list-type remove-type element-expression)
     instruction)
    (twrite-string "REMOVE ")
    (case remove-type
      (first
       (tformat "THE FIRST ~a FROM " grammar-list-type)
       (print-designation list-designation))       
      (last
       (tformat "THE LAST ~a FROM " grammar-list-type)
       (print-designation list-designation))       
      (element
       (write-expression element-expression)
       (tformat " FROM THE ~a LIST " grammar-list-type)
       (print-designation list-designation))       
      #+development
      (t (cerror
	   "error!"
	   "unknown g2-list remove expression while priting instruction!")))))

;(def-action-compiler (g2-list-remove-expression
;                       print-g2-list-remove-expression-instruction)
;  (gensym-dstruct-bind ((nil g2-list required-element-type removal-type datum?)
;                       statement)
;    (let ((block-of-variables?
;            (unless leave-on-stack?
;              (generate-block-of-new-variable-spots
;                '(class item) 'symbol 'symbol 'datum))))
;      (emit-instruction-to-stream
;        prolog-stream
;        'begin-activity
;        (activity-index "remove action")
;        unknown-allowed?)
;      (emit-instruction-to-stream
;        prolog-stream
;        'g2-list-remove-expression-prolog
;        (compile-stack-expression
;          g2-list (maybe-add-unknown '(class g2-list) unknown-allowed?))
;        required-element-type    
;        removal-type
;        (if datum?
;            (compile-stack-expression
;              datum? (maybe-add-unknown 'datum unknown-allowed?))
;            nil)
;        block-of-variables?)
;      (when unknown-allowed?
;        (emit-instruction-to-stream
;          epilog-stream
;          'begin-activity
;          (activity-index "remove action")))
;      (emit-instruction-to-stream
;        epilog-stream 'g2-list-remove-expression-epilog (not (null datum?))
;        block-of-variables?)
;      block-of-variables?)))


;;; Instruction 58, the `g2-list-remove-expression' p-code instruction' takes a
;;; g2-list, a required-element-type, removal-type, and a datum element (or
;;; nil).  The instruction removes an element from the list at the indicated
;;; position.  If the list or position is not valid for the list a warning is
;;; given.  There are several removal-types: first, last, and element.  The
;;; element arg is used in the "element" removal-type to indicate the element
;;; position.  This arg can be nil if the particular removal-type does not use
;;; this value.

;;; G2-LIST-REMOVE-EXPRESSION 
;;;    (g2-list required-element-type removal-type datum?)


;(def-pseudo-instruction-byte-code-emitter g2-list-remove-expression-prolog
;  (gensym-dstruct-bind ((nil g2-list required-element-type removal-type datum?
;                            var-spot-block?) instruction)
;    (emit-stack-node-tree byte-code-stream g2-list)
;                                                       ; Use "required element
;                                                       ; type" to emit type
;                                                       ; checking code??  cpm,
;                                                       ; 7/5/91
;    (call-stack-instruction-emitter push-constant
;      byte-code-stream (make-evaluation-symbol required-element-type))
;    (call-stack-instruction-emitter push-constant
;      byte-code-stream (make-evaluation-symbol removal-type))
;    (if datum?
;        (emit-stack-node-tree byte-code-stream datum?)
;        (call-stack-instruction-emitter push-constant
;          byte-code-stream (make-evaluation-symbol nil)))
;    (when var-spot-block?
;      (call-stack-instruction-emitter pop-into-block-of-local-vars
;        byte-code-stream (first var-spot-block?) (length var-spot-block?)))))
;
;(def-pseudo-instruction-byte-code-emitter g2-list-remove-expression-epilog
;  (gensym-dstruct-bind ((nil datum-p? var-spot-block?) instruction)
;    (when var-spot-block?
;      (gensym-dstruct-bind ((g2-list required-element-type removal-type datum?)
;                           var-spot-block?)
;        ;; Push and test for deletion of the item.
;        (call-stack-instruction-emitter push-from-surrounding-local-var
;          byte-code-stream g2-list)
;        (call-stack-instruction-emitter push-from-surrounding-local-var
;          byte-code-stream required-element-type)
;        (call-stack-instruction-emitter push-from-surrounding-local-var
;          byte-code-stream removal-type)
;        (if datum-p?
;            (call-stack-instruction-emitter push-from-surrounding-local-var
;              byte-code-stream datum?)
;            (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
;              byte-code-stream datum?))))
;    (call-stack-instruction-emitter funcall-instruction
;      byte-code-stream 'g2-list-remove-expression)))



;;; The `g2-list-remove-designation-statement' emits a call to the
;;; g2-list-remove-designation instruction.

;;; Note that this action is being phased out starting in 4.0.  The existing
;;; action will still be supported, but any new edits or compiles of the action
;;; will parse and compile into the new G2-LIST-REMOVE action. 

;; Because of the above change, the printer and action will be left as is to
;; support existing KB's, and the compiler and the pseudo-instruction byte-code
;; emitter are commented out.  - cpm, 11/18/93

;;; G2-LIST-REMOVE-DESIGNATION (g2-list required-element-type removal-type item)

(defun print-g2-list-remove-designation-instruction (instruction)
  (gensym-dstruct-bind
    ((nil list-designation grammar-list-type nil element-designation)
     instruction)
    (twrite-string "REMOVE ")
    (print-designation element-designation)
    (tformat " FROM THE ~a LIST " grammar-list-type)
    (print-designation list-designation)))

;(def-action-compiler (g2-list-remove-designation
;                       print-g2-list-remove-designation-instruction)
;  (gensym-dstruct-bind ((nil g2-list required-element-type removal-type item)
;                       statement)
;    (let ((block-of-variables?
;            (unless leave-on-stack?
;              (generate-block-of-new-variable-spots
;                '(class item) 'symbol 'symbol '(class item)))))
;      (emit-instruction-to-stream
;        prolog-stream
;        'begin-activity
;        (activity-index "remove action")
;        unknown-allowed?)
;      (emit-instruction-to-stream
;        prolog-stream
;        'g2-list-remove-designation-prolog
;        (compile-stack-expression
;          g2-list (maybe-add-unknown '(class g2-list) unknown-allowed?))
;        required-element-type
;        removal-type
;        (compile-stack-expression
;          item (maybe-add-unknown '(class item) unknown-allowed?))
;        block-of-variables?)
;      (when unknown-allowed?
;        (emit-instruction-to-stream
;          epilog-stream
;          'begin-activity
;          (activity-index "remove action")))
;      (emit-instruction-to-stream
;        epilog-stream 'g2-list-remove-designation-epilog block-of-variables?)
;      block-of-variables?)))


;;; Instruction 59, the `g2-list-remove-designation p-code instruction' takes a
;;; g2-list, a required-element-type, removal-type, and a datum element (or
;;; nil).  The instruction removes the indicated item from the list.  If the
;;; list or position is not valid for the list, a warning is given.  Currently,
;;; the removal type is ignored.  Therefore, an action that removes an element
;;; by position compiles into g2-list-remove-expression.

;;; G2-LIST-REMOVE-DESIGNATION
;;;    (g2-list required-element-type removal-type item)
;(def-pseudo-instruction-byte-code-emitter g2-list-remove-designation-prolog
;  (gensym-dstruct-bind ((nil g2-list required-element-type removal-type item
;                            var-spot-block?) instruction)
;    (emit-stack-node-tree byte-code-stream g2-list)
;                                                       ; Use "required element
;                                                       ; type" to emit type
;                                                       ; checking code??  cpm,
;                                                       ; 7/5/91
;    (call-stack-instruction-emitter push-constant
;      byte-code-stream (make-evaluation-symbol required-element-type))
;    (call-stack-instruction-emitter push-constant
;      byte-code-stream (make-evaluation-symbol removal-type))
;    (emit-stack-node-tree byte-code-stream item)
;    (when var-spot-block?
;      (call-stack-instruction-emitter pop-into-block-of-local-vars
;        byte-code-stream (first var-spot-block?) (length var-spot-block?)))))
;
;(def-pseudo-instruction-byte-code-emitter g2-list-remove-designation-epilog
;  (let ((var-spot-block? (second instruction)))
;    (when var-spot-block?
;      (gensym-dstruct-bind ((g2-list required-element-type removal-type item)
;                           var-spot-block?)
;        ;; Push and test for deletion of the item.
;        (call-stack-instruction-emitter push-from-surrounding-local-var
;          byte-code-stream g2-list)
;        (call-stack-instruction-emitter push-from-surrounding-local-var
;          byte-code-stream required-element-type)
;        (call-stack-instruction-emitter push-from-surrounding-local-var
;          byte-code-stream removal-type)
;        ;; Push and test for deletion of the item.
;        (call-stack-instruction-emitter push-from-surrounding-local-var
;          byte-code-stream item)))
;    (call-stack-instruction-emitter funcall-instruction
;      byte-code-stream 'g2-list-remove-designation)))



;;; The `g2-list-remove-statement' emits a call to the g2-list-remove
;;; instruction.  This is new to version 4.0 and is a replace for the
;;; g2-list-remove-expression and g2-list-remove-designation instructions.
;;; In this new instruction the required-element-type can be NIL.

;;; G2-LIST-REMOVE
;;;    (g2-list item-or-datum-element? required-element-type? removal-type)

;; Note that the argument order to this new action differs from the remove
;; expression and designation actions.  The item-or-datum element argument is
;; immediately after the g2-list.  This is needed for the coerce instruction.  -
;; cpm, 11/18/93

(defun print-g2-list-remove-instruction (instruction)
  (gensym-dstruct-bind
    ((nil list-designation element-expression? required-element-type?
	  removal-type)
     instruction)
    (twrite-string "REMOVE ")
    (case removal-type
      (first
       (tformat "THE FIRST ~a FROM " (or required-element-type? 'item-or-value))
       (print-designation list-designation))       
      (last
       (tformat "THE LAST ~a FROM " (or required-element-type? 'item-or-value))
       (print-designation list-designation))       
      (element
       (write-expression element-expression?)
       (twrite-string " FROM ")
       (print-designation list-designation))       
      #+development
      (t (cerror
	   "error!"
	   "unknown g2-list remove expression while priting instruction!")))))




(def-action-compiler (g2-list-remove print-g2-list-remove-instruction)
  (gensym-dstruct-bind ((nil g2-list item-or-datum? required-element-type?
			    removal-type)
                       statement)
    (let ((block-of-variables?
            (unless leave-on-stack?
              (generate-block-of-new-variable-spots
                '(class item) 'item-or-datum 'symbol 'symbol))))
      (emit-instruction-to-stream
        prolog-stream
        'begin-activity
        (activity-index "remove action")
        unknown-allowed?)
      (emit-instruction-to-stream
        prolog-stream
        'g2-list-remove-prolog
        (compile-stack-expression
          g2-list (maybe-add-unknown '(class g2-list) unknown-allowed?))
        (if item-or-datum?
            (compile-stack-expression
              item-or-datum?
	      (maybe-add-unknown 'item-or-datum unknown-allowed?))
            nil)
        required-element-type?
        removal-type
	unknown-allowed?
        block-of-variables?)
      (when unknown-allowed?
        (emit-instruction-to-stream
          epilog-stream
          'begin-activity
          (activity-index "remove action")))
      (emit-instruction-to-stream
        epilog-stream
	'g2-list-remove-epilog
	(not (null item-or-datum?))
	block-of-variables?)
      block-of-variables?)))



;;; The `g2-list-remove' p-code instruction' takes a g2-list, an item-or-datum
;;; element (or nil), a required-element-type (or NIL), and a removal-type.  The
;;; instruction removes an element from the list at the indicated position.

;;; An error is signalled, if the list or position is not valid.

;;; There are several removal-types: first, last, and element.  If the
;;; removal-type is "element", then the element argument cannot be NIL and
;;; specifies the element that is to be removed.

;;; G2-LIST-REMOVE
;;;    (g2-list item-or-datum? required-element-type removal-type)

(declare-instruction-for-optimizer
  'g2-list-remove-prolog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor seventh-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor seventh-arg-as-var-spot-block
    cannot-read-roles
    values-produced 5
    writes-list-or-array-elements
    cost 100))

(def-pseudo-instruction-byte-code-emitter g2-list-remove-prolog
  (gensym-dstruct-bind
	((nil g2-list item-or-datum? required-element-type? removal-type
	       unknown-allowed? var-spot-block?)
	 instruction)
    (emit-stack-node-tree byte-code-stream g2-list)
    (cond
      (item-or-datum?
       (emit-stack-node-tree byte-code-stream item-or-datum?)
       (unless (eq removal-type 'element-position)
	 (emit-coerce-matching-element-type-or-unknown-if-necessary
	   byte-code-stream g2-list item-or-datum? unknown-allowed?)))
      (t
       (call-stack-instruction-emitter push-nones byte-code-stream 1)))
    (if required-element-type?
	(call-stack-instruction-emitter push-constant
	  byte-code-stream (make-evaluation-symbol required-element-type?))
	(call-stack-instruction-emitter push-nones byte-code-stream 1))
    (call-stack-instruction-emitter push-constant
      byte-code-stream (make-evaluation-symbol removal-type))
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
        byte-code-stream (first var-spot-block?) (length var-spot-block?)))))


(declare-instruction-for-optimizer
  'g2-list-remove-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor third-arg-as-var-spot-block
    cannot-read-roles
    values-consumed 5
    writes-list-or-array-elements
    cost 100))

(def-pseudo-instruction-byte-code-emitter g2-list-remove-epilog
  (gensym-dstruct-bind ((nil item-or-datum-p? var-spot-block?) instruction)
    (when var-spot-block?
      (gensym-dstruct-bind
	  ((g2-list item-or-datum? required-element-type? removal-type)
	   var-spot-block?)
	;; Push and test for deletion of the item.
	(call-stack-instruction-emitter push-from-surrounding-local-var
	  byte-code-stream g2-list)
	(if item-or-datum-p?
	    (call-stack-instruction-emitter push-from-surrounding-local-var
	      byte-code-stream item-or-datum?)
	    (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	      byte-code-stream item-or-datum?))
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream required-element-type?)
	(call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	  byte-code-stream removal-type)))
    (call-stack-instruction-emitter funcall-instruction
	   byte-code-stream 'g2-list-remove)))



;;; The `nupec-synchronize-statement' emits a call to the nupec-synchronize
;;; instruction.
;;;
;;;   NUPEC-SYNCHRONIZE (g2-to-g2-object designation-list class-list)

(defun print-nupec-synchronize-instruction (inst)
  (declare (ignore inst))
  (twrite-string "NUPEC SYNCHRONIZE"))

(def-action-compiler (nupec-synchronize print-nupec-synchronize-instruction)
  (gensym-dstruct-bind ((nil g2-to-g2-object designation-list class-list)
		       statement)
    (let* ((designation-count (length designation-list))
	   (block-of-variables?
	     (unless leave-on-stack?
	       (nconc
		 (generate-block-of-new-variable-spots '(class item))
		 (loop repeat designation-count
		       collect (generate-new-variable-spot '(class item))
				       using phrase-cons)
		 ;; class-list constant index and argument count.
		 (generate-block-of-new-variable-spots 'integer 'integer)))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "nupec synchronize action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'nupec-synchronize-prolog
	(compile-stack-expression
	  g2-to-g2-object (maybe-add-unknown '(class item) unknown-allowed?))
	(loop for designation in designation-list
	      collect
		(compile-stack-expression
		  designation
		  (maybe-add-unknown '(class item) unknown-allowed?))
			      using phrase-cons)
	class-list
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "nupec synchronize action")))
      (emit-instruction-to-stream
	epilog-stream 'nupec-synchronize-epilog block-of-variables?
      	;; argument count: g2-to-g2-object, designations, and class-list.
		(+f designation-count 2))
      block-of-variables?)))


;;; Instruction 60, the `NUPEC synchronize procedure instruction' is used to
;;; execute a synchronization operation in the NUPEC specific enhancements to
;;; G2.  Note that this needs to subvert the stuff which checks for a procedure
;;; hogging the processor, since the system will be within this instruction for
;;; quite some time.  Also, if this instruction is executed in a non-NUPEC
;;; version of G2, then a procedure error should be given.

;;;   (NUPEC-SYNCHRONIZE
;;;     g2-to-g2-object list-of-designations list-of-classes)

;; This is implemented as a special form.  There are a variable number of
;; designations which are compiled.  The list of classes is not compiled and is
;; put in the constant-vector as an internal-constant.  Since the action for
;; this statement takes a variable number of arguments, a count of the total
;; number of arguments, not including the count argument, is left on the top of
;; the stack.

(declare-instruction-for-optimizer
  'nupec-synchronize-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor sixth-arg-as-var-spot
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter nupec-synchronize-prolog
  (gensym-dstruct-bind ((nil g2-to-g2-object list-of-designations
			    list-of-classes var-spot-block?)
		       instruction)
    (let ((index (register-internal-constant-in-byte-code-stream
		   byte-code-stream list-of-classes)))
      (emit-stack-node-tree byte-code-stream g2-to-g2-object)
      (loop for designation in list-of-designations
	    do
	(emit-stack-node-tree byte-code-stream designation))
      (call-stack-instruction-emitter push-constant
	byte-code-stream (make-evaluation-integer index))
      (when var-spot-block?
	(call-stack-instruction-emitter pop-into-block-of-local-vars
	  byte-code-stream (first var-spot-block?) (length var-spot-block?))))))

(declare-instruction-for-optimizer
  'nupec-synchronize-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot
    cannot-read-roles
    cannot-write-roles
    cost 100))

(def-pseudo-instruction-byte-code-emitter nupec-synchronize-epilog
  (let ((var-spot-block? (second instruction)))
    (loop for var-spot in var-spot-block?
	  do
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream var-spot))
    (emit-instruction-byte-code byte-code-stream 'nupec-synchronize)
    (write-byte-code-to-stream byte-code-stream (third instruction))))



;;; The `create-explanation-statement' emits a call to the
;;; create-explanation instruction.
;;;
;;;   CREATE-EXPLANATION (variable-or-parameter local-name?)

(defun print-create-explanation-instruction (instruction)
  (gensym-dstruct-bind ((nil designation local-name?) instruction)
    (twrite-string "CREATE AN EXPLANATION ")
    (when local-name?
      (print-designation local-name?)
      (twrite-string " "))
    (twrite-string "FOR ")
    (print-designation designation)))

(def-action-compiler (create-explanation
		       print-create-explanation-statement)
  (gensym-dstruct-bind
    ((nil variable-or-parameter-designation local-name?) statement)
    (let ((var-spot? nil)
	  (var-spot-description? nil)
	  (var-spot-type? nil)
	  (compiler-error? nil)
	  (created-type (make-class-type-specification 'explanation))
	  (block-of-variables?
	    (unless leave-on-stack?
	      (generate-block-of-new-variable-spots 'symbol))))
      (when local-name?
	(multiple-value-setq (var-spot? var-spot-description?)
	  (variable-spot-and-description-for-local-name local-name?))
	(cond
	  ((null var-spot?)
	   (setq compiler-error? t)
	   (procedure-compiler-missing-local-name-error local-name?))
	  (t
	   (setq var-spot-type? (getfq (cdr var-spot-description?) :type))
	   (when (not (type-specifications-could-intersect-p
			created-type var-spot-type?))
	     (setq compiler-error? t)
	     (compiler-error
	       "In the create explanation action, the local name ~
                ~a is declared to hold ~NT, not ~NT."
	       local-name? var-spot-type? created-type)) )))
      (unless compiler-error?
	(emit-instruction-to-stream
	  prolog-stream
	  'begin-activity
	  (activity-index "create explanation action")
	  unknown-allowed?)
	(emit-instruction-to-stream
	  prolog-stream
	  'create-explanation-prolog
	  (compile-stack-expression
	    variable-or-parameter-designation
	    (maybe-add-unknown '(class variable-or-parameter) unknown-allowed?))
	  block-of-variables?)
	(when unknown-allowed?
	  (emit-instruction-to-stream
	    epilog-stream
	    'begin-activity
	    (activity-index "create explanation action")))
	(emit-instruction-to-stream
	  epilog-stream 'create-explanation-epilog var-spot?
	  var-spot-type? block-of-variables?))
      block-of-variables?)))




;;; Instruction 61, the `create explanation instruction' is used to create
;;; explanations (transient objects) for variables or parameters.  It takes a
;;; designation which returns a variable or parameter, and it takes a possible
;;; var spot for the new explanation.  It should create an instance of
;;; explanation, and assign it to the local var spot, if supplied.  This
;;; instruction creates an explanation for variables or parameters regardless of
;;; whether they are caching explanations.  (Those that do not cache
;;; explanations, will have an explanation that consists of the object itself.)

;;;   (CREATE-EXPLANATION variable-or-parameter var-spot?)

(declare-instruction-for-optimizer
  'create-explanation-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter create-explanation-prolog
  (gensym-dstruct-bind ((nil variable-or-parameter var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream variable-or-parameter)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'create-explanation-epilog
  '(no-wait-states
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor fourth-arg-as-var-spot-block
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot
    cannot-read-roles
    cannot-write-roles
    cost 100))

(def-pseudo-instruction-byte-code-emitter create-explanation-epilog
  (gensym-dstruct-bind ((nil var-spot? var-spot-type? var-spot-block?)
		       instruction)
    (when var-spot-block?
      (call-stack-instruction-emitter push-from-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction
      byte-code-stream 'create-explanation)
    (cond (var-spot?
	   (call-stack-instruction-emitter type-check byte-code-stream var-spot-type?)
	   (call-stack-instruction-emitter pop-into-surrounding-local-var
	     byte-code-stream var-spot?))
	  (t (emit-instruction-byte-code byte-code-stream 'pop)))))



;;; The `update-statement' emits a call to the update instruction.
;;;
;;;   UPDATE (chart)

(defun print-update-instruction (instruction)
  (twrite-string "UPDATE ")
  (write-expression (second instruction)))

(def-action-compiler (update print-update-instruction)
  (gensym-dstruct-bind ((nil display) statement)
    (let ((block-of-variables?
	    (unless leave-on-stack?
	      (generate-block-of-new-variable-spots '(class item)))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "update action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'update-prolog
	(compile-stack-expression
	  display
	  (maybe-add-unknown '(class item) unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "update action")))
      (emit-instruction-to-stream
	epilog-stream 'update-epilog block-of-variables?)
      block-of-variables?)))


;;; Instruction 62, the `update instruction' is used to update the display of a
;;; chart.  It takes a designation that should denote a chart.  If the given
;;; item is not a chart, issue a level 1 error.

;;;   (UPDATE chart)

(declare-instruction-for-optimizer
  'update-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot
    cannot-read-roles
    updates-displays
    cost 2))

(def-pseudo-instruction-byte-code-emitter update-prolog
  (gensym-dstruct-bind ((nil chart var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream chart)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (first var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'update-epilog
  '(no-wait-states
    cannot-write-local-variables
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot
    cannot-read-roles
    cannot-write-roles))

(def-pseudo-instruction-byte-code-emitter update-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      ;; Push and test for deletion of the item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'update)))



;;; The `create-connection-statement' emits a call to the create-connection
;;; instruction.
;;;
;;;   CREATE-CONNECTION (class-expression connection-specification var-spot?)

(defun print-create-connection-instruction (instruction)
  (gensym-dstruct-bind 
    ((nil class-expression connection-specification local-name?) instruction)
    connection-specification
    (twrite-string "CREATE AN INSTANCE ")
    (when local-name?
      (print-designation local-name?)
      (twrite-string " "))
    (twrite-string "OF THE CLASS NAMED BY ")
    (write-expression class-expression)))

(def-action-compiler (create-connection print-create-connection-statement)
  (gensym-dstruct-bind 
    ((nil class-expression connection-specification local-name?) statement)
    (let ((connected-between-case?  ; two end specifiers
	    (eq (first connection-specification) 'connected-between)))
      (if (null local-name?)
	  (emit-create-connection-action
	    connected-between-case? class-expression
	    connection-specification nil nil prolog-stream epilog-stream
	    leave-on-stack? unknown-allowed?)
	  (multiple-value-bind (var-spot description)
	      (variable-spot-and-description-for-local-name local-name?)
	    (if (null var-spot)
		(procedure-compiler-missing-local-name-error local-name?)
		(let ((type (getfq (cdr description) :type)))
		  (cond ((not (type-specifications-could-intersect-p
				'(class connection) type))
			 (compiler-error
			   "The local name ~a is declared to hold the type ~
                            ~NT, which does not include the type ~NT."
			   local-name? type '(class connection)))
			(t
			 (emit-create-connection-action
                           connected-between-case?  class-expression
                           connection-specification var-spot type prolog-stream
                           epilog-stream leave-on-stack?
                           unknown-allowed?))))))))))


(defun emit-create-connection-action
    (connected-between-case? class-expression? connection-specification
			     var-spot? var-spot-type? prolog-stream? epilog-stream? leave-on-stack?
			     unknown-allowed?)
  (let ((block-of-variables?
          (unless leave-on-stack?
	    ;; class, first end specifier, second end specifier, style,
	    ;; direction, vertices.
	    (generate-block-of-new-variable-spots
	      'symbol
	      '(class item) 'symbol 'symbol 'integer 'symbol
	      '(class item) 'symbol 'symbol 'integer 'symbol
	      'symbol 'symbol 'item-or-datum))))
    (gensym-dstruct-bind
	((end-1-designation?  make-new-stub-1?  side-1?
			      position-1?  portname-1?  end-2-designation?
			      make-new-stub-2?  side-2?  position-2?  portname-2?
			      style? direction? vertices?)
	 (nconc
	   (compile-connection-end-specifier
	     (second connection-specification) unknown-allowed?)
	   ;; second end specifier
	   (if connected-between-case?
	       (compile-connection-end-specifier
		 (third connection-specification) unknown-allowed?)
	       (compile-connection-end-specifier nil unknown-allowed?))
	   (if connected-between-case?
	       (compile-connection-creation-details
		 (fourth connection-specification) unknown-allowed?)
	       (compile-connection-creation-details
		 (third connection-specification) unknown-allowed?))))
      (emit-instruction-to-stream
	prolog-stream?
	'begin-activity
	(activity-index "create connection action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream?
	'create-connection-prolog
	(when class-expression?
	  (compile-stack-expression
	    class-expression? (maybe-add-unknown 'symbol unknown-allowed?)))
	end-1-designation? make-new-stub-1? side-1? position-1? portname-1?
	end-2-designation? make-new-stub-2? side-2? position-2? portname-2?
	style? direction? vertices?
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream?
	  'begin-activity
	  (activity-index "create connection action")))
      (emit-instruction-to-stream
	epilog-stream?
	'create-connection-epilog
	(not (null end-1-designation?)) (not (null make-new-stub-1?)) (not (null side-1?))
	(not (null position-1?)) (not (null portname-1?)) (not (null end-2-designation?))
	(not (null make-new-stub-2?)) (not (null side-2?)) (not (null position-2?))
	(not (null portname-2?))
	(not (null style?)) (not (null direction?)) (not (null vertices?)) 
	var-spot? var-spot-type? block-of-variables?))))


(defun compile-connection-end-specifier (end-specifier? unknown-allowed?)
  (if end-specifier?
      (let* ((end-position-specifier (second end-specifier?))
	     (make-new-stub? 
	       (eq (first end-position-specifier) 'newly-located-at))
	     (side? (second end-position-specifier))
	     (position-on-side? (third end-position-specifier))
	     (portname? (fourth end-position-specifier)))
	(phrase-list
	  (compile-stack-expression
	    (first end-specifier?)
	    (maybe-add-unknown '(class item) unknown-allowed?))
	  (if make-new-stub? t nil)
	  (when side?
	    (compile-stack-expression
	      side? (maybe-add-unknown 'symbol unknown-allowed?)))
	  (when position-on-side?
	    (compile-stack-expression
	      position-on-side? (maybe-add-unknown 'number unknown-allowed?)))
	  (when portname? 
	    (compile-stack-expression
	      portname? (maybe-add-unknown 'symbol unknown-allowed?)))))
      (phrase-list nil nil nil nil nil)))

(defun compile-connection-creation-details (details? unknown-allowed?)

  (if details?
      (let ((style-details? (first details?))
	    (direction-details? (second details?))
	    (vertices-details? (third details?)))
	(phrase-list
	  (when style-details?
	    (compile-stack-expression
	      style-details? (maybe-add-unknown 'symbol unknown-allowed?)))
	  (when direction-details?
	    (compile-stack-expression
	      direction-details? (maybe-add-unknown 'symbol unknown-allowed?)))
	  (when vertices-details?
	    (cond
;	      ((connection-vertices-are-constant-list? vertices-details?)
;	       vertices-details?)
	      ;; Nil or a list of numbers.
	      ((and (consp vertices-details?)		    
		    (not (designation-p vertices-details?)))
	       vertices-details?)
	      (t
	       (compile-stack-expression 
		 vertices-details?
		 (maybe-add-unknown '(class quantity-list) unknown-allowed?)))))))
      (phrase-list nil nil nil)))




;;; Instruction 63, the `create connection instruction' is used to create a 
;;; new connection.

;;;   (CREATE-CONNECTION class first-end-specification ...
;;;   second-end-specification ... connection-details ... var-spot?
;;;   var-spot-type?)


(declare-instruction-for-optimizer
  'create-connection-prolog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor sixteenth-arg-as-var-spot-block
    cannot-read-local-variables
    values-produced 14
    cannot-write-roles
    cannot-read-roles))

(def-pseudo-instruction-byte-code-emitter create-connection-prolog
  (gensym-dstruct-bind ((nil class? end-1-designation? make-new-stub-1? side-1?
			    position-1? portname-1? end-2-designation?
			    make-new-stub-2? side-2? position-2? portname-2?
			    style? direction? vertices? var-spot-block?)
		       instruction)
    (if (null class?)
	(call-stack-instruction-emitter push-constant
	  byte-code-stream (make-evaluation-symbol 'connection))
	(emit-stack-node-tree byte-code-stream class?))

    ;; First end specifier.
    (emit-stack-node-tree-or-nil byte-code-stream end-1-designation?)
    (call-stack-instruction-emitter push-constant
      byte-code-stream (make-evaluation-symbol make-new-stub-1?))
    (emit-stack-node-tree-or-nil byte-code-stream side-1?)
    (emit-stack-node-tree-or-nil byte-code-stream position-1?)
    (emit-stack-node-tree-or-nil byte-code-stream portname-1?)

    ;; Second end specifier.
    (emit-stack-node-tree-or-nil byte-code-stream end-2-designation?)
    (call-stack-instruction-emitter push-constant
      byte-code-stream (make-evaluation-symbol make-new-stub-2?))
    (emit-stack-node-tree-or-nil byte-code-stream side-2?)
    (emit-stack-node-tree-or-nil byte-code-stream position-2?)
    (emit-stack-node-tree-or-nil byte-code-stream portname-2?)

    (emit-stack-node-tree-or-nil byte-code-stream style?)
    (emit-stack-node-tree-or-nil byte-code-stream direction?)

    (cond ((null vertices?)
	   (call-stack-instruction-emitter push-constant
	     byte-code-stream (make-evaluation-symbol nil)))
	  ((consp vertices?)
	   ;; List of numbers.
	   (let ((index (register-internal-constant-in-byte-code-stream
			  byte-code-stream vertices?)))
	     (call-stack-instruction-emitter push-constant
	       byte-code-stream (make-evaluation-integer index))))
	  (t
	   ;; quantity-list item
	   (emit-stack-node-tree byte-code-stream vertices?)))

    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))


(declare-instruction-for-optimizer
  'create-connection-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor sixteenth-arg-as-var-spot-block
    cannot-read-local-variables
    values-consumed 14
    cannot-write-roles
    cannot-read-roles))



(def-pseudo-instruction-byte-code-emitter create-connection-epilog
  (gensym-dstruct-bind ((nil end-1-designation-p? make-new-stub-1-p? side-1-p?
			    position-1-p? portname-1-p? end-2-designation-p?
			    make-new-stub-2-p? side-2-p? position-2-p? portname-2-p?
			    style-p? direction-p? vertices-p? var-spot?
			    var-spot-type? var-spot-block?)
		       instruction)
    (when var-spot-block?
      (gensym-dstruct-bind
	((class end-1-var-spot make-new-stub-1-var-spot side-1-var-spot
		position-1-var-spot portname-1-var-spot end-2-var-spot
		make-new-stub-2-var-spot side-2-var-spot position-2-var-spot
		portname-2-var-spot style-var-spot direction-var-spot
		vertices-var-spot)
	 var-spot-block?)
      ;; class
      (call-stack-instruction-emitter push-from-surrounding-local-var byte-code-stream class)
      ;; First end specifier.
      (if end-1-designation-p?
	  (call-stack-instruction-emitter push-from-surrounding-local-var
	    byte-code-stream end-1-var-spot)
	  (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	    byte-code-stream end-1-var-spot))
      (if make-new-stub-1-p?
	  (call-stack-instruction-emitter push-from-surrounding-local-var
	    byte-code-stream make-new-stub-1-var-spot)
	  (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	    byte-code-stream make-new-stub-1-var-spot))
      (if side-1-p?
	  (call-stack-instruction-emitter push-from-surrounding-local-var
	    byte-code-stream side-1-var-spot)
	  (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	    byte-code-stream side-1-var-spot))
      (if position-1-p?
	  (call-stack-instruction-emitter push-from-surrounding-local-var
	    byte-code-stream position-1-var-spot)
	  (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	    byte-code-stream position-1-var-spot))
      (if portname-1-p?
	  (call-stack-instruction-emitter push-from-surrounding-local-var
            byte-code-stream portname-1-var-spot)
          (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
            byte-code-stream portname-1-var-spot))
    ;; Second end specifier.
      (if end-2-designation-p?
	  (call-stack-instruction-emitter push-from-surrounding-local-var
	    byte-code-stream end-2-var-spot)
	  (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	    byte-code-stream end-2-var-spot))
      (if make-new-stub-2-p?
	  (call-stack-instruction-emitter push-from-surrounding-local-var
	    byte-code-stream make-new-stub-2-var-spot)
	  (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	    byte-code-stream make-new-stub-2-var-spot))
      (if side-2-p?
	  (call-stack-instruction-emitter push-from-surrounding-local-var
	    byte-code-stream side-2-var-spot)
	  (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	    byte-code-stream side-2-var-spot))
      (if position-2-p?
	  (call-stack-instruction-emitter push-from-surrounding-local-var
	    byte-code-stream position-2-var-spot)
	  (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	    byte-code-stream position-2-var-spot))
      (if portname-2-p?
	  (call-stack-instruction-emitter push-from-surrounding-local-var
            byte-code-stream portname-2-var-spot)
          (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
            byte-code-stream portname-2-var-spot))

      (if style-p?
	  (call-stack-instruction-emitter push-from-surrounding-local-var
            byte-code-stream style-var-spot)
          (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
            byte-code-stream style-var-spot))
      (if direction-p?
	  (call-stack-instruction-emitter push-from-surrounding-local-var
            byte-code-stream direction-var-spot)
          (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
            byte-code-stream direction-var-spot))

      (if vertices-p?
	  ;; Quantity-list or constant index to a list of numbers.
	  (call-stack-instruction-emitter push-from-surrounding-local-var
            byte-code-stream vertices-var-spot)
          (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
            byte-code-stream vertices-var-spot))))

    (emit-instruction-byte-code byte-code-stream 'create-connection)
    (cond (var-spot?
	   (call-stack-instruction-emitter type-check byte-code-stream var-spot-type?)
	   (call-stack-instruction-emitter pop-into-surrounding-local-var
	     byte-code-stream var-spot?))
	  (t (emit-instruction-byte-code byte-code-stream 'pop)))))

      
;;; The `abort action compiler' emits a call to the abort action instruction.
;;; This action aborts a procedure-invocation or all invocations of a procedure.
;;; The action is new to G2 version 3.0.  Therefore, there is no corresponding
;;; procedure statement compiler.

;;;   ABORT (procedure | procedure-invocation)

(defun print-abort-instruction (instruction)
  (twrite-string "ABORT ")
  (write-expression (second instruction)))

(def-action-compiler (abort print-abort-instruction)
  (gensym-dstruct-bind ((nil procedure-or-invocation) statement)
    (let ((block-of-variables?
	    (unless leave-on-stack?
	      (generate-block-of-new-variable-spots '(class item)))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "abort action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'abort-prolog
	(compile-stack-expression
	  procedure-or-invocation
	  (maybe-add-unknown
	    '(or (class procedure) (class procedure-invocation))
	    unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "abort action")))
      (emit-instruction-to-stream
	epilog-stream 'abort-epilog block-of-variables?)
      block-of-variables?)))


;;; The `abort instruction' is used to abort a procedure-invocation or all
;;; invocations of a procedure.  The action is new to G2 version 3.0.  Therefore,
;;; there is no corresponding pseudo-instruction byte-code emitter, only prolog
;;; and epilog emitters.  It takes a designation that should denote a procedure or
;;; procedure invocation.

;; Note that this instruction needs to check if the current procedure was the
;; one that got aborted.  This cannot happen inside of a funcalled instruction!
;; -jra 11/9/91

;;;   (ABORT procedure | procedure-invocation)

(declare-instruction-for-optimizer
  'abort-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter abort-prolog
  (gensym-dstruct-bind ((nil procedure-or-invocation var-spot-block?)
		       instruction)
    (emit-stack-node-tree byte-code-stream procedure-or-invocation)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (first var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'abort-epilog
  '(reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    
    deletes-procedure-invocations ;a role writer
    cannot-read-roles
    cost 100))

(def-pseudo-instruction-byte-code-emitter abort-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      ;; Push and test for deletion of the item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'abort)))


;;; The `shut down G2 action compiler' emits a call to the shut down G2 action
;;; instruction.  The action is new to G2 version 3.0.  Therefore, there is
;;; no corresponding procedure statement compiler.

;;;   SHUT DOWN G2 ()

(defun print-shut-down-g2-instruction (instruction)
  (declare (ignore instruction))
  (twrite-string "SHUT DOWN G2"))

(def-action-compiler (shut-down-g2 print-shut-down-g2-instruction)
  (declare (ignore leave-on-stack? unknown-allowed?))
  (emit-instruction-to-stream prolog-stream 'shut-down-g2-prolog)
  ;; Only 1 begin-activity instruction is emitted because the
  ;; shutdown-prolog is a no-op.  This activity is profiled.
  (emit-instruction-to-stream
    epilog-stream
    'begin-activity
    (activity-index "shut down G2 action"))
  (emit-instruction-to-stream epilog-stream 'shut-down-g2-epilog)
  nil)


;;; The `shut down G2 instruction' is used to shut down G2 from rule or
;;; procedure control.  G2 is reset before being shutdown.  The action is new to
;;; G2 version 3.0.  Therefore, there is no corresponding pseudo-instruction
;;; byte-code emitter.  This action takes no arguments.

;;;   SHUT DOWN G2 ()


(declare-instruction-for-optimizer
  'shut-down-g2-prolog
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles
    cost 0))

(def-pseudo-instruction-byte-code-emitter shut-down-g2-prolog
  (declare (ignore instruction byte-code-stream))
  ;; The prolog emitter is a no-op.
  nil)

(declare-instruction-for-optimizer
  'shut-down-g2-epilog
  '(return-flow
    cost 100))

(def-pseudo-instruction-byte-code-emitter shut-down-g2-epilog
  (declare (ignore instruction))
  (call-stack-instruction-emitter funcall-instruction byte-code-stream 'shut-down-g2))




;;; The `reset kb action compiler' emits a call to the reset knowledge-base
;;; action instruction.  The action is new to G2 version 3.0.  Therefore, there
;;; is no corresponding procedure statement compiler.

;;;   RESET KB ()

(defun print-reset-kb-instruction (instruction)
  (declare (ignore instruction))
  (twrite-string "RESET KNOWLEDGE-BASE"))

(def-action-compiler (reset-kb print-reset-kb-instruction)
  (declare (ignore leave-on-stack? unknown-allowed?))
  (emit-instruction-to-stream prolog-stream 'reset-kb-prolog)
  ;; Only 1 begin-activity instruction is emitted because the
  ;; reset-kb-prolog is a no-op.  This activity is profiled.
  (emit-instruction-to-stream
    epilog-stream
    'begin-activity
    (activity-index "reset kb action"))
  (emit-instruction-to-stream epilog-stream 'reset-kb-epilog)
  nil)


;;; The `reset kb instruction' is used to reset G2 from rule or procedure
;;; control.  The action is new to G2 version 3.0.  Therefore, there is no
;;; corresponding pseudo-instruction byte-code emitter.  This action takes no
;;; arguments.

;;;   RESET KB ()

(declare-instruction-for-optimizer
     'reset-kb-prolog
     '(no-wait-states
       cannot-write-local-variables
       cannot-read-local-variables
       cannot-write-roles
       cannot-read-roles
       cost 0))

(def-pseudo-instruction-byte-code-emitter reset-kb-prolog
  (declare (ignore instruction byte-code-stream))
  ;; The prolog emitter is a no-op.
  nil)

(declare-instruction-for-optimizer
  'reset-kb-epilog
  '(cost 100))

(def-pseudo-instruction-byte-code-emitter reset-kb-epilog
  (declare (ignore instruction))
  (emit-instruction-byte-code byte-code-stream 'reset-kb))




;;; The `pause kb action compiler' emits a call to the pause kb action
;;; instruction.  The action is new to G2 version 3.0.  Therefore, there is no
;;; corresponding procedure statement compiler.

;;;   PAUSE KB ()

(defun print-pause-kb-instruction (instruction)
  (declare (ignore instruction))
  (twrite-string "PAUSE KNOWLEDGE-BASE"))

(def-action-compiler (pause-kb print-pause-kb-instruction)
  (declare (ignore leave-on-stack? unknown-allowed?))
  (emit-instruction-to-stream prolog-stream 'pause-kb-prolog)
  ;; Only 1 begin-activity instruction is emitted because the
  ;; pause-kb-prolog is a no-op.  This activity is profiled.
  (emit-instruction-to-stream
    epilog-stream
    'begin-activity
    (activity-index "pause kb action"))
  (emit-instruction-to-stream epilog-stream 'pause-kb-epilog)
  nil)




;;; The `pause kb instruction' is used to pause G2 from rule or procedure
;;; control.  The action is new to G2 version 3.0.  Therefore, there is no
;;; corresponding pseudo-instruction byte-code emitter.  This action takes no
;;; arguments.

;;;   PAUSE KB ()



(declare-instruction-for-optimizer
  'pause-kb-prolog
  '(cost 1))

(def-pseudo-instruction-byte-code-emitter pause-kb-prolog
  (declare (ignore instruction byte-code-stream))
  ;; The prolog emitter is a no-op.
  nil)


(declare-instruction-for-optimizer
  'pause-kb-epilog
  '(cost 100))

(def-pseudo-instruction-byte-code-emitter pause-kb-epilog
  (declare (ignore instruction))
  (emit-instruction-byte-code byte-code-stream 'pause-kb))




;;; The `create-by-cloning statement' emits a call to the create-by-cloning
;;; instruction.  The action is new to G2 version 3.0.  Therefore, there is no
;;; corresponding procedure statement compiler.

;;;   (CREATE-BY-CLONING class-name designation var-spot?)

(defun print-create-by-cloning-statement (instruction)
  (gensym-dstruct-bind ((nil class-expression designation local-name?)
		       instruction)
    (twrite-string "CREATE AN INSTANCE ")
    (when local-name?
      (print-designation local-name?)
      (twrite-string " "))
    (tformat "OF THE CLASS NAMED BY ~NE BY CLONING ~ND." class-expression
	     designation)))



(def-action-compiler (create-by-cloning print-create-by-cloning-statement)
  (gensym-dstruct-bind ((nil class-expression designation local-name?) statement)
    (let* ((var-spot? nil)
	   (var-spot-description? nil)
	   (var-spot-type? nil)
	   (compiler-error? nil)
	   (created-type
	     (make-class-type-specification
	       (if (and (consp class-expression)
			(eq (car class-expression) 'quote))
		   (second class-expression)
		   'item)))
	   (check-created-type? nil)
	   (block-of-variables?
	     (unless leave-on-stack?
	       (generate-block-of-new-variable-spots 'symbol created-type))))
      (when local-name?
	(multiple-value-setq (var-spot? var-spot-description?)
	  (variable-spot-and-description-for-local-name local-name?))
	(cond
	  ((null var-spot?)
	   (setq compiler-error? t)
	   (procedure-compiler-missing-local-name-error local-name?))
	  (t
	   (setq var-spot-type? (getfq (cdr var-spot-description?) :type))
	   ;; Need to always test the type of the cloned item with the var-spot
	   ;; type.
	   (cond ((type-specifications-could-intersect-p
		    created-type var-spot-type?)
		  (setq check-created-type? var-spot-type?))
		 (t
		  (compiler-error
		    "In the create action, the local name ~a is declared to ~
                       hold ~NT, not ~NT."
		    local-name? var-spot-type? created-type))))))
      (unless compiler-error?
	(emit-instruction-to-stream
	  prolog-stream
	  'begin-activity
	  (activity-index "create by cloning action")
	  unknown-allowed?)
	(emit-instruction-to-stream
	  prolog-stream
	  'create-by-cloning-prolog
	  (compile-stack-expression
	    class-expression (maybe-add-unknown 'symbol unknown-allowed?))
	  ;; Shouldn't the following use the more specific class available
	  ;; above?  -jra & jh 3/5/92
	  (compile-stack-expression
	    designation (maybe-add-unknown '(class item) unknown-allowed?))
	  block-of-variables?)
	(when unknown-allowed?
	  (emit-instruction-to-stream
	    epilog-stream
	    'begin-activity
	    (activity-index "create by cloning action")))
	(emit-instruction-to-stream
	  epilog-stream 'create-by-cloning-epilog var-spot? check-created-type?
	  block-of-variables?))
      block-of-variables?)))


;;; The `create-by-cloning p-code instruction' is used to create transient items
;;; by cloning.  It takes an expression which returns a symbol naming a class, a
;;; designation to clone, and a possible var spot and var spot type for the new
;;; frame.  It should create an instance of the given class by cloning, type
;;; test it for the var spot, and assign it to the local var spot, if supplied.

;;; The action is new to G2 version 3.0.  Therefore, there is no corresponding
;;; pseudo-instruction byte-code emitter.

;;;   (CREATE-BY-CLONING symbol-expression var-spot? var-spot-type?)


(declare-instruction-for-optimizer
     'create-by-cloning-prolog
     '(no-wait-states
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor fourth-arg-as-var-spot-block
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor fourth-arg-as-var-spot-block
       values-produced 2
       creates-new-item
       cannot-read-roles
       cost 100))


(def-pseudo-instruction-byte-code-emitter create-by-cloning-prolog
  (gensym-dstruct-bind ((nil symbol-expression designation var-spot-block?)
		       instruction)
    (emit-stack-node-tree byte-code-stream symbol-expression)
    (emit-stack-node-tree byte-code-stream designation)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))



(declare-instruction-for-optimizer
     'create-by-cloning-epilog
     '(no-wait-states
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor fourth-arg-as-var-spot-block
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor fourth-arg-as-var-spot-block
       values-consumed 2
       creates-new-item
       cannot-read-roles
       cost 100))

(def-pseudo-instruction-byte-code-emitter create-by-cloning-epilog
  (gensym-dstruct-bind ((nil item-var-spot? item-var-spot-type-to-check?
			    var-spot-block?)
		       instruction)
    ;; Note that the following block is wrong!  The restoration of the item to
    ;; be cloned should happen as an explicit push, so that deletion tests will
    ;; occur.  -jra 3/5/92
    (when var-spot-block?
      (call-stack-instruction-emitter push-from-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'create-by-cloning)
    (cond (item-var-spot?
	   (when item-var-spot-type-to-check?
	     (call-stack-instruction-emitter type-check
	       byte-code-stream item-var-spot-type-to-check?))
	   (call-stack-instruction-emitter pop-into-surrounding-local-var
	     byte-code-stream item-var-spot?))
	  (t (emit-instruction-byte-code byte-code-stream 'pop)))))




;;; The `make-permanent-statement' emits a call to the make-permanent
;;; instruction.  The action is new to G2 version 3.0.  Therefore, there is no
;;; corresponding procedure statement compiler.

;;;   MAKE-PERMANENT (item)

(defun print-make-permanent-instruction (instruction)
  (tformat "MAKE ~ND PERMANENT" (second instruction)))

(def-action-compiler (make-permanent print-make-permanent-instruction)
  (gensym-dstruct-bind ((nil item) statement)
    (let ((block-of-variables?
	    (unless leave-on-stack?
	      (generate-block-of-new-variable-spots '(class item)))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "make permanent action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'make-permanent-prolog
	(compile-stack-expression
	  item (maybe-add-unknown '(class item) unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "make permanent action")))
      (emit-instruction-to-stream
	epilog-stream 'make-permanent-epilog block-of-variables?)
      block-of-variables?)))


;;; The `make-permanent instruction' is used to make a transient item, every
;;; subobject, and all items on subworkspaces permanent.  Permanent means that
;;; the object is no longer transient and will not be deleted on reset, and that
;;; kb state changes for the effected items are not undone on reset.  Dynamic
;;; changes which are not kb state changes, usch as the current value of a
;;; variables, are not made permanent.

;;;   (MAKE-PERMANENT item)

;;; The action is new to G2 version 3.0.  Therefore, there is no corresponding
;;; pseudo-instruction byte-code emitter.

(declare-instruction-for-optimizer
  'make-permanent-prolog
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter make-permanent-prolog
  (gensym-dstruct-bind ((nil item var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream item)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (first var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'make-permanent-epilog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    cannot-read-roles
    makes-certain-items-permanent
    cost 100))

(def-pseudo-instruction-byte-code-emitter make-permanent-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      ;; Push and test for deletion of the item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'make-permanent)))




;;; The `make-transient-statement' emits a call to the make-transient
;;; instruction.  The action is new to G2 version 3.0.  Therefore, there is no
;;; corresponding procedure statement compiler.

;;;   MAKE-TRANSIENT (item)

(defun print-make-transient-instruction (instruction)
  (tformat "MAKE ~ND TRANSIENT" (second instruction)))

(def-action-compiler (make-transient print-make-transient-instruction)
  (gensym-dstruct-bind ((nil item) statement)
    (let ((block-of-variables?
	    (unless leave-on-stack?
	      (generate-block-of-new-variable-spots '(class item)))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "make transient action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'make-transient-prolog
	(compile-stack-expression
	  item (maybe-add-unknown '(class item) unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "make transient action")))
      (emit-instruction-to-stream
	epilog-stream 'make-transient-epilog block-of-variables?)
      block-of-variables?)))


;;; The `make-transient instruction' is used to make a permanent item, every
;;; subobject, and all items on subworkspaces transient.  These new transient
;;; items are no longer permanent and will be deleted on reset.  This action
;;; does not affect kb state changes or dynamic values, such as current variable
;;; values.

;;;   (MAKE-TRANSIENT item)

;;; The action is new to G2 version 3.0.  Therefore, there is no corresponding
;;; pseudo-instruction byte-code emitter.

(declare-instruction-for-optimizer
  'make-transient-prolog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter make-transient-prolog
  (gensym-dstruct-bind ((nil item var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream item)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (first var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
     'make-transient-epilog
     '(no-wait-states
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor second-arg-as-var-spot-block
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor second-arg-as-var-spot-block
       makes-certain-items-transient
       cannot-read-roles
       cost 100))

(def-pseudo-instruction-byte-code-emitter make-transient-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      ;; Push and test for deletion of the item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'make-transient)))




;;; The `make-subworkspace-statement' emits a call to the make-subworkspace
;;; instruction.  The action is new to G2 version 3.0.  Therefore, there is no
;;; corresponding procedure statement compiler.

;;;   MAKE-SUBWORKSPACE (kb-workspace item)

(defun print-make-subworkspace-instruction (instruction)
  (tformat "MAKE ~ND THE SUBWORKSPACE OF ~ND"
	   (second instruction) (third instruction)))

(def-action-compiler (make-subworkspace print-make-subworkspace-instruction)
  (gensym-dstruct-bind ((nil kb-workspace item) statement)
    (let ((block-of-variables?
	    (unless leave-on-stack?
	      (generate-block-of-new-variable-spots
		'(class kb-workspace) '(class item)))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "make subworkspace action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'make-subworkspace-prolog
	(compile-stack-expression
	  kb-workspace
	  (maybe-add-unknown '(class kb-workspace) unknown-allowed?))
	(compile-stack-expression
	  item
	  (maybe-add-unknown '(class item) unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "make subworkspace action")))
      (emit-instruction-to-stream
	epilog-stream 'make-subworkspace-epilog block-of-variables?)
      block-of-variables?)))


;;; The `make-subworkspace instruction' is used to make a kb-workspace a
;;; subworkspace of an item.

;;;   MAKE-SUBWORKSPACE (kb-workspace item)

;;; The action is new to G2 version 3.0.  Therefore, there is no corresponding
;;; pseudo-instruction byte-code emitter.

(declare-instruction-for-optimizer
  'make-subworkspace-prolog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor fourth-arg-as-var-spot-block
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles))


(def-pseudo-instruction-byte-code-emitter make-subworkspace-prolog
  (gensym-dstruct-bind ((nil kb-workspace item var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream kb-workspace)
    (emit-stack-node-tree byte-code-stream item)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (first var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
     'make-subworkspace-epilog
     '(no-wait-states
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor second-arg-as-var-spot-block
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor second-arg-as-var-spot-block
       creates-new-item
       cannot-read-roles
       cost 100))

(def-pseudo-instruction-byte-code-emitter make-subworkspace-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      ;; Push and test for deletion of the kb-workspace and the item.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?))
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (second var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'make-subworkspace)))



;;; The `print-statement' emits a call to the print instruction.  The action is
;;; new to G2 version 3.0.  Therefore, there is no corresponding procedure
;;; statement compiler.  Currently, this action only accepts an argument of type
;;; kb-workspace.  A future version, may extend this to allow the printing of
;;; other types of items.

;;; The compiler for print tests for an argument of type item.  The action itself
;;; will check that the item is a workspace.  This is done at run-time since the
;;; compiler does not type test for superior classes of item without issuing frame
;;; note warnings.  The compiler could have tested for kb-workspace, which is a
;;; subclass of item, but this does not include temporary workspaces.

;;;   PRINT (workspace)

(defun print-print-instruction (instruction)
  (tformat "PRINT ~ND" (second instruction)))

(def-action-compiler (print print-print-instruction)
  (gensym-dstruct-bind ((nil workspace) statement)
    (let ((block-of-variables?
	    (unless leave-on-stack?
	      (generate-block-of-new-variable-spots
		'(class item)))))
      (emit-instruction-to-stream
	prolog-stream
	'begin-activity
	(activity-index "print action")
	unknown-allowed?)
      (emit-instruction-to-stream
	prolog-stream
	'print-prolog
	(compile-stack-expression
	  workspace
	  (maybe-add-unknown '(class item) unknown-allowed?))
	block-of-variables?)
      (when unknown-allowed?
	(emit-instruction-to-stream
	  epilog-stream
	  'begin-activity
	  (activity-index "print action")))
      (emit-instruction-to-stream
	epilog-stream 'print-epilog block-of-variables?)
      block-of-variables?)))


;;; The `print instruction' is used to print the contents of a workspace to a
;;; postscript file.

;;;   PRINT (workspace)

;;; The action is new to G2 version 3.0.  Therefore, there is no corresponding
;;; pseudo-instruction byte-code emitter.

(declare-instruction-for-optimizer
  'print-prolog
  '(no-wait-states
    cannot-write-local-variables
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor third-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles
    cost 2))

(def-pseudo-instruction-byte-code-emitter print-prolog
  (gensym-dstruct-bind ((nil workspace var-spot-block?) instruction)
    (emit-stack-node-tree byte-code-stream workspace)
    (when var-spot-block?
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (first var-spot-block?) (length var-spot-block?)))))

(declare-instruction-for-optimizer
  'print-epilog
  '(no-wait-states
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot-block
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    prints-objects
    cannot-read-roles
    cost 100))

(def-pseudo-instruction-byte-code-emitter print-epilog
  (let ((var-spot-block? (second instruction)))
    (when var-spot-block?
      ;; Push and test for deletion of the workspace.
      (call-stack-instruction-emitter push-from-surrounding-local-var
	byte-code-stream (first var-spot-block?)))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'print)))


(defun decode-print-details-as-phrase-rule (statement)
  (gensym-dstruct-bind ((nil workspace)
			   statement)
    (phrase-list
      'start
      'g2-print
      (phrase-list workspace
		   'false))))


;;;; call templates

(defun print-call-instruction (instruction)
  (gensym-dstruct-bind ((nil procedure-designation argument-list desired-value-count)
		       instruction)
    (twrite-string "CALL ")
    (print-designation procedure-designation)
    (twrite-string " (")
    (loop for arg in argument-list
	  for first-time? = t then nil
	  do
      (unless first-time? (twrite-string ", "))
      (write-expression arg))
    
    (twrite-string ") returning")
    (write-expression desired-value-count)
    (twrite-string " values")))


(defun print-call-assignment-instruction (instruction)
  (gensym-dstruct-bind ((nil nil procedure-designation argument-list desired-value-count)
		       instruction)
    (twrite-string "CALL ")
    (print-designation procedure-designation)
    (twrite-string " (")
    (loop for arg in argument-list
	  for first-time? = t then nil
	  do
      (unless first-time? (twrite-string ", "))
      (write-expression arg))
    
    (twrite-string ") returning")
    (write-expression desired-value-count)
    (twrite-string " values")))

(declare-instruction-for-optimizer
  'call-prolog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles
    values-consumed fourth-value-with-eighth-as-list-value-consumer
    cost 2))

(declare-instruction-for-optimizer
  'call-assignment-prolog
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles
    values-consumed fourth-value-with-ninth-as-list-value-consumer
    cost 2))

(def-action-compiler (call-action print-call-instruction)
  (gensym-dstruct-bind ((nil procedure-designation
			    argument-list
			    across?)
		       statement)
    (let* ((argument-count (length argument-list))
	   (desired-value-count 0)
	   (argument-stack-nodes nil)
	   (stable-procedure? nil)
	   (stable-arg-types? nil)
	   (recorded-procedure-call-free-reference? nil)
	   (compiled-procedure
	     (compile-stack-expression
	       procedure-designation
	       (maybe-add-unknown
		 (if across?
		     '(class remote-procedure-declaration)    
		     '(class procedure))
		 unknown-allowed?)))
	   (block-of-variables?
	     ;;Not able to use generate-block-of-new-variable-spots here.
	     (unless leave-on-stack?
	       (nconc
		 (phrase-list (generate-new-variable-spot
				(if across?
				    '(class remote-procedure-declaration)    
				    '(class procedure))))
		 (loop repeat argument-count
		       collect (generate-new-variable-spot 'item-or-datum)
			 using phrase-cons)))))
      (when (>f argument-count 255)
	(compiler-error
	  "CALL accepts a maximum of 255 arguments, this call passed ~a."
	  argument-count))
      (when (>f desired-value-count 255)
	(compiler-error
	  "CALL receives a maximum of 255 values, this call requested ~a."
	  desired-value-count))
      
      (when (procedure-p *current-computation-frame*)
	(when (indirectly-denoted-item-p compiled-procedure)
	  (set-procedure-contains-indirect-procedure-call
	    *current-computation-frame*))
	(when (not (dependent-compilation-p))
	  (set-procedure-call-without-validated-environment
	    *current-computation-frame*)))

      (when (dependent-compilation-p)
	(setq stable-procedure?
	      (stable-denoted-procedure-p compiled-procedure))
	(when stable-procedure?
	  (setq stable-arg-types?
		(collect-types-into-list-using-phrase-conses
		  (argument-list-description stable-procedure?)))
	  (cond
	    ((/=f (length stable-arg-types?) argument-count)
	     (compiler-dependence-warning
	       "Because of an argument count mismatch for ~ND, a call to it ~
                could not be optimized."
	       procedure-designation)
	     (setq stable-arg-types? nil)
	     (setq stable-procedure? nil))
	    (t
	     ;; Everythings OK.
	     (setq recorded-procedure-call-free-reference? t)
	     ;; Record the defined procedure argument and return types.  Note
	     ;; that this differs from the [remote-]procedure-call
	     ;; free-reference.
	     (record-free-reference
	       (if across?
		   'stable-remote-procedure-call
		   'stable-procedure-call)
	       (phrase-list procedure-designation stable-arg-types? nil))))))

            (cond ((null across?)
             (emit-instruction-to-stream
	       prolog-stream
	       'begin-activity
	       (activity-index "call action")
	        unknown-allowed?)
	     (emit-instruction-to-stream
	       prolog-stream
	       ;; Note that dependent-call-rpc won't happen until we have a
	       ;; stable-rpd-p function, not stable-procedure-p used above.  -jra, cpm
	       ;; 1/14/93
	       'call-prolog
	       argument-count
	       block-of-variables?
	       compiled-procedure
	       desired-value-count
	       unknown-allowed?
	       stable-procedure?
	       (setq argument-stack-nodes
		     (loop for argument in argument-list
			   for type-cons? = stable-arg-types?
					  then (cdr type-cons?)
			   collect
			   (compile-stack-expression
			     argument
			     (maybe-add-unknown
			       (or (car type-cons?) 'item-or-datum)
			       unknown-allowed?))
			     using phrase-cons))
	       nil
	       )
	     (when unknown-allowed?
	       (emit-instruction-to-stream
		 epilog-stream
		 'begin-activity
	         (activity-index "call action")))
	     (emit-instruction-to-stream
		epilog-stream
		(if stable-procedure?
		    'call-dependent-epilog
		    'call-epilog)
		block-of-variables?
		argument-count))
	   (t
	      (emit-instruction-to-stream
	       prolog-stream
	       'begin-activity
	       (activity-index "call rpc action")
	        unknown-allowed?)
	     (emit-instruction-to-stream
	       prolog-stream
	       'call-prolog
	       argument-count
	       block-of-variables?
	       compiled-procedure
	       desired-value-count
	       unknown-allowed?
	       stable-procedure?
	       (setq argument-stack-nodes
		     (loop for argument in argument-list
			   for type-cons? = stable-arg-types?
					  then (cdr type-cons?)
			   collect
			   (compile-stack-expression
			     argument
			     (maybe-add-unknown
			       (or (car type-cons?) 'item-or-datum)
			       unknown-allowed?))
			     using phrase-cons))
	       (compile-stack-expression
		   across?
		   (maybe-add-unknown '(class item) unknown-allowed?))	                      )
	     (when unknown-allowed?
	       (emit-instruction-to-stream
		 epilog-stream
		 'begin-activity
	         (activity-index "call rpc action")))
	     (emit-instruction-to-stream
		epilog-stream
       ;; Note that dependent-call-rpc won't happen until we have a
       ;; stable-rpd-p function, not stable-procedure-p used above.  -jra, cpm
       ;; 1/14/93
		(if stable-procedure?
		    'call-dependent-rpc-epilog
		    'call-rpc-epilog)
		block-of-variables?
		argument-count)))

       (when (and (null recorded-procedure-call-free-reference?)
		 (symbolp procedure-designation)
		 (not (indirectly-denoted-item-p compiled-procedure)))
	(record-free-reference
	  (if across? 'remote-procedure-call 'procedure-call)
	  (phrase-list
	    procedure-designation
	    (loop for argument-node in argument-stack-nodes
		  collect (type-specification-minus-type 
			    (type-specification-minus-type
			      (stack-node-value-type argument-node)
			      '(unknown-datum))
			    '(no-item))
		    using phrase-cons)
	    nil)))
      block-of-variables?)))


(def-pseudo-instruction-byte-code-emitter call-prolog
  (gensym-dstruct-bind ((nil argument-count var-spot-block?
			    procedure 
			    nil
			    unknown-allowed? 
			    stable-procedure?
			    arguments
			    across?)
		       instruction)
    (emit-stack-node-tree byte-code-stream procedure)
    (loop for argument in arguments do
      (emit-stack-node-tree byte-code-stream argument))
    (when  (not stable-procedure?)
      (call-stack-instruction-emitter
	funcall-instruction
	byte-code-stream
	(if unknown-allowed?
	    'prepare-possibly-unknown-procedure-arguments
	    'prepare-procedure-arguments)
	(1+f argument-count)
	(1+f argument-count)))
    (when across?
      (emit-stack-node-tree byte-code-stream across?))
     (when var-spot-block?
      ;; Note that even if the values are unknown, we can do this block copy and
      ;; we won't break anything.
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))
    ))

(defun emit-common-call-epilog-bytes
    (byte-code-stream instruction call-type)
  (let ((var-spot-block? (second instruction))
	 (arg-count (third instruction)))
      ;; Need to test for deleted frames since some of the var-spots, and
      ;; possible some of the argument var-spots, may be items.
      (loop for var-spot-cons = var-spot-block? then (cdr var-spot-cons)
	    for var-spot = (first var-spot-cons)
	    until (null var-spot-cons)
	    do
	  (call-stack-instruction-emitter push-from-surrounding-local-var
	  byte-code-stream var-spot)
    finally
    (emit-instruction-byte-code byte-code-stream call-type)
    (write-byte-code-to-stream byte-code-stream arg-count)
    ;; no return values
    (write-byte-code-to-stream byte-code-stream 0))))

(def-pseudo-instruction-byte-code-emitter call-epilog
  (emit-common-call-epilog-bytes
    byte-code-stream instruction 'call))
  
(def-pseudo-instruction-byte-code-emitter call-dependent-epilog
  (emit-common-call-epilog-bytes
    byte-code-stream instruction 'dependent-call))

(def-pseudo-instruction-byte-code-emitter call-rpc-epilog
  (emit-common-call-epilog-bytes
    byte-code-stream instruction 'call-rpc))

(declare-instruction-for-optimizer
     'call-epilog
     '(no-wait-states
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor second-arg-as-var-spot
       cannot-write-local-variables
       cannot-write-roles
       cannot-read-roles
       cost 100))

(declare-instruction-for-optimizer
     'call-dependent-epilog
     '(no-wait-states
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor second-arg-as-var-spot
       cannot-write-local-variables
       cannot-write-roles
       cannot-read-roles
       cost 100))

(declare-instruction-for-optimizer
     'call-rpc-epilog
     '(no-wait-states
       reads-only-local-variables-specified-by-argument
       local-var-read-accessor second-arg-as-var-spot
       cannot-write-local-variables
       cannot-write-roles
       cannot-read-roles
       cost 100))

(declare-instruction-for-optimizer
     'call-assignment-epilog
     '(no-wait-states
       cannot-read-local-variables
       cannot-write-local-variables
       cannot-write-roles
       cannot-read-roles
       cost 100))

(declare-instruction-for-optimizer
     'call-assignment-rpc-epilog
     '(no-wait-states
       cannot-read-local-variables
       cannot-write-local-variables
       cannot-write-roles
       cannot-read-roles
       cost 100))

(declare-instruction-for-optimizer
     'call-assignment-dependent-epilog
     '(no-wait-states
       cannot-read-local-variables
       cannot-write-local-variables
       cannot-write-roles
       cannot-read-roles
       cost 100))


;;; The `call-assignment-statement' is emitted as a pair of instructions, a call
;;; and a receive-values.  All local names to be bound must be defined.

;;; Note that this compiler needs to register free references to the procedures
;;; and remote-procedure-declarations that it references, along with the types
;;; of the arguments and return values.

;;;   (CALL-ASSIGNMENT-STATEMENT local-names proc-designation arg-expressions)

(def-action-compiler (call-assignment-action
		       print-call-assignment-instruction)
  (setq call-statement-processed? t)
  (gensym-dstruct-bind ((nil  local-names designation argument-list  across?)
		       statement)
    (let* ((argument-count (length argument-list))
	   (return-spots nil)
	   (return-types nil)
	   (argument-stack-nodes nil)
	   (desired-return-types nil)
	   (stable-procedure? nil)
	   (stable-proc-arg-types? nil)
	   (stable-proc-return-types? nil)
	   (recorded-procedure-call-free-reference? nil)
	   (compiled-procedure-or-rpd
	     (if (null across?)
		 (compile-procedure-expression designation '(class procedure))
		 (compile-procedure-expression
		   designation '(class remote-procedure-declaration))))
	   (compiler-error? nil)
	   (block-of-variables?
	     ;;Not able to use generate-block-of-new-variable-spots here.
	     (unless leave-on-stack?
	       (nconc
		 (loop repeat argument-count
		       collect (generate-new-variable-spot 'item-or-datum)
			 using phrase-cons)
		 ))))
      (setf (compiler-code-body-maximum-received-value-count
	      (current-compiler-code-body))
	    (maxf (compiler-code-body-maximum-received-value-count
		    (current-compiler-code-body))
		  (length local-names)))

      (loop with var-spot with description with type
	    for local-name in local-names
	    do
	(multiple-value-setq (var-spot description)
	  (variable-spot-and-description-for-local-name local-name))
	(setq type (getfq (cdr description) :type))
	(when (null var-spot)
	  (procedure-compiler-missing-local-name-error local-name)
	  (setq compiler-error? t))
	(setq return-spots (phrase-cons var-spot return-spots))
	(setq return-types (phrase-cons type return-types)))
      (setq return-spots (nreverse return-spots))
      (setq return-types (nreverse return-types))

      (when (procedure-p *current-computation-frame*)
	(when (indirectly-denoted-item-p compiled-procedure-or-rpd)
	  (set-procedure-contains-indirect-procedure-call
	    *current-computation-frame*))
	(when (not (dependent-compilation-p))
	  (set-procedure-call-without-validated-environment
	    *current-computation-frame*)))

      (when (and (null compiler-error?) (dependent-compilation-p))
	(setq stable-procedure?
	      (stable-denoted-procedure-p compiled-procedure-or-rpd))
	(when (procedure-p *current-computation-frame*)
	  ;; Work remains to be done on trees of calls that are always valid.
	  ;; Is this a stability issue?  No recompile is needed if the call tree
	  ;; changes such that environments can be invalidated, all that's
	  ;; needed is a change in the runtime behavior in
	  ;; return-stack-values-to-caller where it checks
	  ;; procedure-environment-always-valid-p.  Hmmmm.  -jra & cpm 4/5/93
	  (cond
;	    ((and stable-procedure?
;		  (procedure-environment-always-valid-p stable-procedure?))
;	     (record-free-reference
;	       'stable-procedure-with-valid-environment designation))
	    (t
	     (set-procedure-call-without-validated-environment
	       *current-computation-frame*))))
	(when stable-procedure?
	  (setq stable-proc-arg-types?
		(collect-types-into-list-using-phrase-conses
		  (argument-list-description stable-procedure?)))
	  (setq stable-proc-return-types?
		(collect-types-into-list-using-phrase-conses
		  (returned-values-description stable-procedure?)))
	  (cond
	    ((/=f (length stable-proc-arg-types?) (length argument-list))
	     (compiler-dependence-warning
	       "Because of an argument count mismatch for ~ND, a call to it ~
                could not be optimized."
	       designation)
	     (setq stable-proc-arg-types? nil)
	     (setq stable-proc-return-types? nil)
	     (setq stable-procedure? nil))
	    ((<f (length return-types) (length local-names))
	     (compiler-dependence-warning
	       "Because of a return value count mismatch for ~ND, a call to ~
                it could not be optimized."
	       designation)
	     (setq stable-proc-arg-types? nil)
	     (setq stable-proc-return-types? nil)
	     (setq stable-procedure? nil))
	    (t
	     ;; Everythings OK.
	     (setq recorded-procedure-call-free-reference? t)
	     ;; Record the defined procedure argument and return types.  Note
	     ;; that this differs from the [remote-]procedure-call
	     ;; free-reference.
	     (record-free-reference
	       (if across? 'stable-remote-procedure-call 'stable-procedure-call)
	       (phrase-list
		 designation stable-proc-arg-types?
		 stable-proc-return-types?))))))

      (cond (stable-proc-return-types?
	     (setq desired-return-types
		   (copy-list-using-phrase-conses return-types))
	     (loop for stable-type in stable-proc-return-types?
		   for desired-type-cons on desired-return-types
		   do
	       (when (type-specification-subtype-p
		       stable-type (car-of-cons desired-type-cons))
		 (setf (car desired-type-cons) nil))))
	    (t
	     (setq desired-return-types return-types)))
      (cond ((null across?)
	     (emit-instruction-to-stream
	       prolog-stream
	       'call-assignment-prolog
	       argument-count
	       block-of-variables?
	       compiled-procedure-or-rpd
	       (length local-names)
	       local-names
	       t
	       stable-procedure?	       	       	
	       (setq argument-stack-nodes
		     (loop for argument in argument-list
			   for type-cons? = stable-proc-arg-types?
					  then (cdr type-cons?)
			   collect
			   (compile-stack-expression
			     argument
			     (maybe-add-unknown
			       (or (car type-cons?) 'item-or-datum)
			       unknown-allowed?))
			     using phrase-cons))
	       nil
	       )
	     (emit-instruction-to-stream
	       epilog-stream
	       (if stable-procedure?
		   'call-assignment-dependent-epilog
		   'call-assignment-epilog)
	       argument-count
	       compiled-procedure-or-rpd
	       local-names
	       return-spots
	       desired-return-types)
	     (emit-instruction-to-stream
	       epilog-stream
	       'receive-values return-spots return-types))
	    (t
	      (emit-instruction-to-stream
	       prolog-stream
	       'call-assignment-prolog
	       argument-count
	       block-of-variables?
	       compiled-procedure-or-rpd
	       (length local-names)
	       local-names
	       t
	       stable-procedure?	       	       	
	       (setq argument-stack-nodes
		     (loop for argument in argument-list
			   for type-cons? = stable-proc-arg-types?
					  then (cdr type-cons?)
			   collect
			   (compile-stack-expression
			     argument
			     (maybe-add-unknown
			       (or (car type-cons?) 'item-or-datum)
			       unknown-allowed?))
			     using phrase-cons))
	         (compile-stack-expression
		   across?
		   (maybe-add-unknown '(class item) unknown-allowed?))
	       )
	     (emit-instruction-to-stream
	       epilog-stream
	       (if stable-procedure?
		   'call-assignment-dependent-rpc-epilog
		   'call-assignment-rpc-epilog)
	       argument-count
	       compiled-procedure-or-rpd
	       local-names
	       return-spots
	       desired-return-types)
	     (emit-instruction-to-stream
	       epilog-stream
	       'receive-values return-spots return-types))))))

(def-pseudo-instruction-byte-code-emitter call-assignment-prolog
  (gensym-dstruct-bind ((nil argument-count 
			    var-spot-block?
			    procedure
			    nil ;return-count
			    nil ;return-names
			    unknown-allowed? 
			    stable-procedure?
			    arguments
			    across?)
		       instruction)
    (emit-stack-node-tree byte-code-stream procedure)
    (loop for argument in arguments do
      (emit-stack-node-tree byte-code-stream argument))
    (when (not stable-procedure?)
      (call-stack-instruction-emitter
	funcall-instruction
	byte-code-stream
	(if unknown-allowed?
	    'prepare-possibly-unknown-procedure-arguments
	    'prepare-procedure-arguments)
	(1+f argument-count)
	(1+f argument-count)))
    (when across?
      (emit-stack-node-tree byte-code-stream across?))
    (when var-spot-block?
      ;; Note that even if the values are unknown, we can do this block copy and
      ;; we won't break anything.
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))
    ))

(defun emit-common-call-assignment-epilog-bytes
    (byte-code-stream instruction call-type)
  (gensym-dstruct-bind ((nil
			 argument-count
			 nil ;compiled-procedure
			 local-names
			 nil
			 nil) ;return-types
		       instruction)
	(emit-instruction-byte-code byte-code-stream call-type)
	(write-byte-code-to-stream byte-code-stream argument-count)
	(write-byte-code-to-stream byte-code-stream (length local-names))))

(def-pseudo-instruction-byte-code-emitter call-assignment-epilog
  (emit-common-call-assignment-epilog-bytes
       byte-code-stream instruction 'call))

(def-pseudo-instruction-byte-code-emitter call-assignment-rpc-epilog
    (emit-common-call-assignment-epilog-bytes
       byte-code-stream instruction 'call-rpc))

(def-pseudo-instruction-byte-code-emitter call-assignment-dependent-epilog
    (emit-common-call-assignment-epilog-bytes
      byte-code-stream instruction 'dependent-call))



;;; New actions for G2 v5.0. ajs (6/15/96)

;;; START-KB ()

(defun print-start-kb-instruction (instruction)
  (declare (ignore instruction))
  (twrite-string "START KNOWLEDGE-BASE"))

;;; Start-KB action - implemented by by call to funcalled-instruction
;;; start-kb.

(def-action-compiler (start-kb print-pause-kb-instruction)
  (declare (ignore leave-on-stack? unknown-allowed?))
  (emit-instruction-to-stream prolog-stream 'start-kb-prolog)
  ;; Only 1 begin-activity instruction is emitted because the
  ;; pause-kb-prolog is a no-op.  This activity is profiled.
  (emit-instruction-to-stream
    epilog-stream
    'begin-activity
    (activity-index "start kb action"))
  (emit-instruction-to-stream epilog-stream 'start-kb-epilog)
  nil)

(declare-instruction-for-optimizer
  'start-kb-prolog
  '(cost 1))

(def-pseudo-instruction-byte-code-emitter start-kb-prolog
  (declare (ignore instruction byte-code-stream))
  ;; The prolog emitter is a no-op.
  nil)

(declare-instruction-for-optimizer
  'start-kb-epilog
  '(return-flow
    cost 100))

(def-pseudo-instruction-byte-code-emitter start-kb-epilog
  (declare (ignore instruction))
  (call-stack-instruction-emitter funcall-instruction byte-code-stream 'start-kb))


;;; RESUME-KB ()

(defun print-resume-kb-instruction (instruction)
  (declare (ignore instruction))
  (twrite-string "RESUME KNOWLEDGE-BASE"))

;;; Resume-KB action - implemented by by call to funcalled-instruction
;;; resume-kb.

(def-action-compiler (resume-kb print-pause-kb-instruction)
  (declare (ignore leave-on-stack? unknown-allowed?))
  (emit-instruction-to-stream prolog-stream 'start-kb-prolog)
  ;; Only 1 begin-activity instruction is emitted because the
  ;; resume-kb-prolog is a no-op.  This activity is profiled.
  (emit-instruction-to-stream
    epilog-stream
    'begin-activity
    (activity-index "resume kb action"))
  (emit-instruction-to-stream epilog-stream 'resume-kb-epilog)
  nil)

(declare-instruction-for-optimizer
  'resume-kb-prolog
  '(cost 1))

(def-pseudo-instruction-byte-code-emitter resume-kb-prolog
  (declare (ignore instruction byte-code-stream))
  ;; The prolog emitter is a no-op.
  nil)

(declare-instruction-for-optimizer
  'resume-kb-epilog
  '(return-flow
    cost 100))

(def-pseudo-instruction-byte-code-emitter resume-kb-epilog
  (declare (ignore instruction))
  (call-stack-instruction-emitter funcall-instruction byte-code-stream 'resume-kb))


;;;
;;; KB Threads support in the compiler
;;;

(defun emit-action-start-thread-bytes (byte-code-stream instruction)
  (gensym-dstruct-bind ((nil procedure arguments nil nil
			 nil unknown-allowed? var-spot-block?
			 stable-procedure?)
		       instruction)
    (emit-stack-node-tree byte-code-stream procedure)
    (loop for argument in arguments do
      (emit-stack-node-tree byte-code-stream argument))
    (when (not stable-procedure?)
      (let ((args+1 (1+ (length arguments))))
	(call-stack-instruction-emitter
	  funcall-instruction
	  byte-code-stream
	  (if unknown-allowed?
	      'prepare-possibly-unknown-procedure-arguments
	      'prepare-procedure-arguments)
	  args+1
	  args+1)))
    (call-stack-instruction-emitter push-nones byte-code-stream 2)
    (when var-spot-block?
      ;; Note that even if the values are unknown, we can do this block copy and
      ;; we won't break anything.
      (call-stack-instruction-emitter pop-into-block-of-local-vars
	byte-code-stream (car var-spot-block?) (length var-spot-block?)))))

(def-pseudo-instruction-byte-code-emitter start-thread-prolog
  (emit-action-start-thread-bytes byte-code-stream instruction))

(def-pseudo-instruction-byte-code-emitter start-thread-epilog
  (let ((var-spot-block? (second instruction)))
    (when (and var-spot-block? (not (fixnump var-spot-block?)))
      ;; Need to test for deleted frames since some of the var-spots, and
      ;; possible some of the argument var-spots, may be items.
      (loop for var-spot in var-spot-block?
	    for args-remaining from (1- (length var-spot-block?)) downto 0
	    do
	(if (or (=f args-remaining 1) (=f args-remaining 0)) ; priority?, wait?
	    (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
	      byte-code-stream var-spot)
	    (call-stack-instruction-emitter push-from-surrounding-local-var
	      byte-code-stream var-spot))))
    (call-stack-instruction-emitter funcall-instruction byte-code-stream 'start-thread
				    (if (fixnump var-spot-block?)
					var-spot-block?
					(length var-spot-block?))
				    0)))  
	 
(def-action-compiler (start-thread nil)
  (gensym-dstruct-bind ((nil designation argument-expressions)
		       statement)
    (let* ((argument-count (length argument-expressions))
	   (argument-stack-nodes nil)
	   (stable-procedure? nil)
	   (stable-arg-types? nil)
	   (recorded-procedure-call-free-reference? nil)
	   (compiled-procedure-or-rpd
	     (compile-stack-expression
	       designation
	       (maybe-add-unknown 
				      '(class procedure)
				  unknown-allowed?)))
	   (block-of-variables?
	     (unless leave-on-stack?
	       ;;Not able to use generate-block-of-new-variable-spots here.
	       (nconc
		 (phrase-list (generate-new-variable-spot
				    '(class procedure)))
		 (loop repeat argument-count
		       collect (generate-new-variable-spot 'item-or-datum)
				    using phrase-cons)
		 ;; Priority, wait, and possibly across arguments.
		     (generate-block-of-new-variable-spots
		       '(or integer (unknown-datum))
		       '(or number (unknown-datum)))))))
      (emit-instruction-to-stream
	     prolog-stream
	    'start-thread-prolog
	compiled-procedure-or-rpd
	(setq argument-stack-nodes
	      (loop for argument in argument-expressions
		    for type-cons? = stable-arg-types?
				   then (cdr type-cons?)
		    collect
		      (compile-stack-expression
			argument
			(maybe-add-unknown
			  (or (car type-cons?) 'item-or-datum)
			  unknown-allowed?))
				   using phrase-cons))
	unknown-allowed?
	block-of-variables?
	stable-procedure?)
   (emit-instruction-to-stream
	epilog-stream
	'start-thread-epilog
	(or block-of-variables?
	    (+f (length argument-expressions)
		3)))
      (when (and (null recorded-procedure-call-free-reference?)
		 (symbolp designation)
		 (not (indirectly-denoted-item-p compiled-procedure-or-rpd)))
	(record-free-reference
	  'procedure-call
	  (phrase-list
	    designation
	    (loop for argument-node in argument-stack-nodes
		  collect (type-specification-minus-type 
			    (type-specification-minus-type
			      (stack-node-value-type argument-node)
			      '(unknown-datum))
			    '(no-item))
		  using phrase-cons)
	    nil)))
      block-of-variables?)))
	 
	 
	 
;end of SoftServe changes


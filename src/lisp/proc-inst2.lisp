;;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module PROC-INST2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Jim Allard and Chris Morel





;;;; Procedure Instruction Emitters




;;; The file PROC-INST2 is a temporary file to hold the emitters being written
;;; for existing procedure instructions by JRA on 4/4/91.  This will in all
;;; likelihood be merged back into proc-inst sometime in the future.



;;; Instruction 0, the `DATUM-ASSIGN p-code instruction' sets a variable value
;;; in this environment to the value of an evaluated expression.  Its first
;;; argument is the var-spot to put the result, and its second argument is the
;;; expression to evaluate.

;;; Note that there really is no difference anymore between datum-assign and
;;; item-assign.  Towards the end of this process we should have all
;;; datum-assign and item-assign statements changed into assign-local-var.

;; Obsolete, replaced with assign-local-var.  -jra 4/4/91

;;;   (DATUM-ASSIGN var-spot expression)

;(def-pseudo-instruction-byte-code-emitter datum-assign
;  (gensym-dstruct-bind ((nil var-spot expression) instruction)
;    (emit-stack-node-tree byte-code-stream expression)
;    (call-stack-instruction-emitter pop-into-surrounding-local-var byte-code-stream var-spot)))



;;; Instruction 1, the `ITEM-ASSIGN p-code instruction' sets a variable value in
;;; this environment to the item denoted by a designation.  Its first argument
;;; is the var-spot to put the result, and its second argument is the
;;; designation to evaluate.

;; Obsolete, replaced with assign-local-var.  -jra 4/4/91

;;;   (ITEM-ASSIGN var-spot designation)

;(def-pseudo-instruction-byte-code-emitter item-assign
;  (gensym-dstruct-bind ((nil var-spot designation) instruction)
;    (emit-stack-node-tree byte-code-stream designation)
;    (call-stack-instruction-emitter pop-into-surrounding-local-var byte-code-stream var-spot)))




;;; Instruction 2, the `ASSIGN-TYPE-AND-VALUE p-code instruction' is used to
;;; override and reclaim any existing value in the given var-spot and change
;;; that spot's type and value to the given type and the value of the given
;;; expression.  This is used by the returning mechanisms to set up return
;;; values from code body invocations other than the base.  The DATUM-ASSIGN and
;;; ITEM-ASSIGN instructions are preferred in the most situations.
;;;
;;;   (ASSIGN-TYPE-AND-VALUE var-spot type expression)

;; Obsolete, replaced with assign-local-var.  -jra 4/4/91

;(def-pseudo-instruction-byte-code-emitter assign-type-and-value

;  ;; Does this instruction handle both items and datum??

;  ;; Yep.  -jra 3/15/91

;  (gensym-dstruct-bind ((nil var-spot expression) instruction)
;    (emit-stack-node-tree byte-code-stream expression)

;    ;; This is wrong.  We need new stack-instructions change-type-of-local-var
;    ;; and change-type-of-surrounding-local-var!!  cpm, 3/5/91

;    ;; Local vars don't really have types stored in them any more, so I think
;    ;; this is actaully right, or not even needed.  -jra 3/15/91

;    (call-stack-instruction-emitter pop-into-surrounding-local-var
;      byte-code-stream var-spot)))




;;; The instruction tag-statement registers the current address to the tag in
;;; the statement.

;;;   (TAG-STATEMENT tag)

;; from the optimizer standpoint, one of the prototypical "do nothing" instructions
(declare-optimizer-stack-instruction tag-statement)

(def-pseudo-instruction-byte-code-emitter tag-statement
  (register-tag-in-byte-code-stream
    byte-code-stream (second instruction)))




;;; The instruction jump-tag-statement registers the current address of this tag
;;; as a jump target.

;;;   (JUMP-TAG-STATEMENT tag)

(declare-optimizer-stack-instruction jump-tag-statement)


(def-pseudo-instruction-byte-code-emitter jump-tag-statement
  (register-tag-in-byte-code-stream
    byte-code-stream (second instruction) t))




;;; The instruction ASSIGN-LOCAL-VAR takes a var spot and a stack node tree and
;;; emits instructions to change that local var.  Note that this can take either
;;; items or datum, or handle what used to be done by the assign-type-and-value
;;; instruction.

;;;   (ASSIGN-LOCAL-VAR var-spot expression)

(declare-instruction-for-optimizer
  'assign-local-var
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot
    local-variables-write-type-constructor? pop-one-variable-off-of-stack
    cannot-read-roles
    cannot-write-roles
    cost 1))

(def-pseudo-instruction-byte-code-emitter assign-local-var
  (gensym-dstruct-bind ((nil var-spot expression) instruction)
    (emit-stack-node-tree byte-code-stream expression)
    (call-stack-instruction-emitter pop-into-surrounding-local-var byte-code-stream var-spot)))



;;; The instruction BRANCH takes an instruction tag and causes an instruction to
;;; be emitted which will branch to the address of that tag.  Note that the
;;; optimizations for doing something other than an actual branch long are done
;;; by the address resolver of branch-long.
;;;
;;;   (BRANCH tag)

(declare-instruction-for-optimizer
  'branch
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles
    unconditional-branch-flow
    cost 2))


(def-pseudo-instruction-byte-code-emitter branch
  (gensym-dstruct-bind ((nil tag) instruction)
    (call-stack-instruction-emitter branch-long byte-code-stream tag)))




;;; Instruction 4, the `BRANCH-IF-TRUE p-code instruction' evaluates a logical
;;; expression, and if that expression is as true as or truer than the
;;; truth-threshold in the inference engine parameters, it then it executes a
;;; branch to the given instruction address.

;;; The BRANCH-IF-TRUE instruction emits a logical expression 
;;;
;;;   (BRANCH-IF-TRUE logical-expression target-address)

;; Should we create a branch-if-true stack instruction instead of emitting code
;; for the branch-if-not-true stack instruction!!  cpm, 3/9/91


(declare-instruction-for-optimizer
  'branch-if-true
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles
    branch-if-stack-true-flow
    cost 2))


(def-pseudo-instruction-byte-code-emitter branch-if-true
  (gensym-dstruct-bind ((nil logical-expression target-address) instruction)
    (emit-stack-node-tree byte-code-stream logical-expression)
    (emit-instruction-byte-code byte-code-stream 'not)
    (call-stack-instruction-emitter branch-long-if-not-true byte-code-stream target-address)))




;;; Instruction 5, the `BRANCH-IF-NOT-TRUE p-code instruction' evaluates a
;;; logical expression, and if the result is not as true as or truer than the
;;; truth-threshold of the inference engine parameters, it then branches to the
;;; given instruction.

;;;   (BRANCH-IF-NOT-TRUE logical-expression target-address)



(declare-instruction-for-optimizer
  'branch-if-not-true
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles
    branch-if-stack-not-true-flow
    cost 2))

(def-pseudo-instruction-byte-code-emitter branch-if-not-true
  (gensym-dstruct-bind ((nil logical-expression target-address) instruction)
    (emit-stack-node-tree byte-code-stream logical-expression)
    (call-stack-instruction-emitter branch-long-if-not-true
      byte-code-stream target-address)))




;;; Instruction 6, the `JUMP p-code instruction' performs a branch statement
;;; between code-body-invocations.  This instruction pops the stack of code body
;;; callers as many levels as are specified in the first argument, and begins
;;; execution of that code body invocation at the instruction given in its
;;; second argument.  The target code body invocation is filo enqueued on the
;;; immediate stack so that this is a wait state free branch with no intervening
;;; executions of other code bodies.

;;;   (JUMP code-body-levels-to-exit target-jump-tag)

(declare-instruction-for-optimizer
     'jump
     '(no-wait-states
       cannot-write-local-variables
       cannot-read-local-variables
       cannot-write-roles
       cannot-read-roles
       jump-flow))

(def-pseudo-instruction-byte-code-emitter jump
  (call-stack-instruction-emitter jump
    byte-code-stream (second instruction) (third instruction)))




;;; The CASE-DISPATCH instruction performs multi-way branches based on an
;;; integer argument.  It uses an array of addresses (stored in the instruction
;;; byte-vector) to quickly lookup an address given a dispatching integer.  If
;;; the value of the expression is out of bounds of the table, then control is
;;; transfered to the else instruction.  If there was no otherwise clause in the
;;; source code, then an otherwise clause will already have been generated by
;;; the compiler which contains a statement to signal a level one error.  The
;;; instruction table is a list of tag names, where the first tag is for the
;;; integer given in table-base.

;;;   (CASE-DISPATCH expression table-base table-length
;;;                  else-instruction instruction-table)



(declare-instruction-for-optimizer
     'case-dispatch
     '(no-wait-states
       cannot-write-local-variables
       cannot-read-local-variables
       cannot-write-roles
       cannot-read-roles
       cost 2
       multi-way-unconditional-branch-flow))

(def-pseudo-instruction-byte-code-emitter case-dispatch
  (gensym-dstruct-bind ((nil expression table-base table-length
			    else-tag tag-table)
		       instruction)
    (emit-stack-node-tree byte-code-stream expression)
    (call-stack-instruction-emitter case-dispatch
      byte-code-stream table-base table-length else-tag tag-table)))




;;; Instruction 8, the `RETURN-VALUES p-code instruction' returns a possibly
;;; empty set of values to the caller of this procedure, and schedules immediate
;;; execution of the caller.  After possibly returning values this code body
;;; invocation is closed (closing the procedure invocation as well) and the code
;;; body invocation interpreter is halted for this invocation.  The stack
;;; instruction implementation for this operation takes one code constant byte,
;;; which is the number of returned values it should expect to find on the
;;; stack.  The expressions should be evaluated in left to right order, with the
;;; first value to be returned deepest in the stack.

;;; (RETURN-VALUES (expression ...))


(declare-instruction-for-optimizer
  'return-values
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    write-state-into-caller
    cannot-read-roles
    values-consumed second-value-as-list-value-consumer
    return-flow))

(def-pseudo-instruction-byte-code-emitter return-values
  (let ((expressions (second instruction)))
    (loop for expression in expressions do
	(emit-stack-node-tree byte-code-stream expression))
  (call-stack-instruction-emitter return-values byte-code-stream (length expressions))))




;;; Instruction 9, the `CALL p-code instruction' takes a procedure definition
;;; designation, a list of argument expressions, and a count of the number of
;;; values which are expected back from this call.  If the returned value count
;;; is anything but zero, the RECEIVE-VALUES p-code instruction must be used to
;;; accept the values returned by the called instruction.

;;; Note that in 3.0 CALL-RPC has been made to implement CALL ACROSS, instead of
;;; determining which to do at run-time.  -jra 4/10/91

;;;   (CALL designation (expressions ...) desired-returned-values-count)


(declare-instruction-for-optimizer
     'call
     '(cannot-write-local-variables
       cannot-read-local-variables
       cannot-write-roles
       cannot-read-roles
       values-consumed second-value-with-third-as-list-value-consumer))

(def-pseudo-instruction-byte-code-emitter call
  (gensym-dstruct-bind ((nil procedure-designation argument-list
			    desired-value-count)
		       instruction)
    (let ((arg-count (length argument-list))
	  (emit-byte-codes-p t))
      (when (>f arg-count 255)
	(compiler-error
	  "CALL accepts a maximum of 255 arguments, this call passed ~a."
	  arg-count)
	(setq emit-byte-codes-p nil))
      (when (>f desired-value-count 255)
	(compiler-error
	  "CALL receives a maximum of 255 values, this call requested ~a."
	  desired-value-count)
	(setq emit-byte-codes-p nil))
      (when emit-byte-codes-p
	(emit-stack-node-tree byte-code-stream procedure-designation)
	(loop for arg in argument-list do
	  (emit-stack-node-tree byte-code-stream arg))
	(emit-instruction-byte-code byte-code-stream 'call)
	(write-byte-code-to-stream byte-code-stream arg-count)
	(write-byte-code-to-stream byte-code-stream desired-value-count)))))




;;; The pseudo-instruction `dependent-call' is used to emit calls to the
;;; optimized version of the call instruction.  This instruction is used when
;;; validation of the called procedures arguments can be done at runtime.

;;; This emitter is quite similar to that of the call instruction.

;;; The instruction takes a procedure definition designation, a list of argument
;;; expressions, and a count of the number of values which are expected back
;;; from this call.  If the returned value count is anything but zero, the
;;; RECEIVE-VALUES p-code instruction must be used to accept the values returned
;;; by the called instruction.

;;; Note that this instruction does not handle RPC calls.

;;;   (DEPENDENT-CALL designation (expressions ...) desired-returned-values-count)

(declare-instruction-for-optimizer
     'dependent-call
     '(cannot-write-local-variables
       cannot-read-local-variables
       cannot-write-roles
       cannot-read-roles))


(def-pseudo-instruction-byte-code-emitter dependent-call
  (gensym-dstruct-bind ((nil procedure-designation argument-list
			    desired-value-count)
		       instruction)
    (let ((arg-count (length argument-list))
	  (emit-byte-codes-p t))
      (when (>f arg-count 255)
	(compiler-error
	  "CALL accepts a maximum of 255 arguments, this call passed ~a."
	  arg-count)
	(setq emit-byte-codes-p nil))
      (when (>f desired-value-count 255)
	(compiler-error
	  "CALL receives a maximum of 255 values, this call requested ~a."
	  desired-value-count)
	(setq emit-byte-codes-p nil))
      (when emit-byte-codes-p
	(emit-stack-node-tree byte-code-stream procedure-designation)
	(loop for arg in argument-list do
	  (emit-stack-node-tree byte-code-stream arg))
	(emit-instruction-byte-code byte-code-stream 'dependent-call)
	(write-byte-code-to-stream byte-code-stream arg-count)
	(write-byte-code-to-stream byte-code-stream desired-value-count)))))




;;; Instruction 10, the `RECEIVE-VALUES p-code instruction' takes a set of
;;; var-spots and a set of corresponding expected types, and will unpack
;;; returned values from a procedure call into the set of var-spots.  The length
;;; of the list of var-spots must agree with the length of the desired value
;;; types list given in the CALL instruction which should immediately preceed
;;; any call to this instruction.  This instruction should emit stack
;;; instructions which push the values from the return position of the
;;; environment vector onto the stack, then one by one type check and store the
;;; values.  Note that the list of types can contain NILS.  When a given type is
;;; NIL, then this instruction should not check the type at all, but should
;;; still pop the value into the correct var-spot.

;;; (RECEIVE-VALUES (var-spot ...) (type? ...))

(declare-instruction-for-optimizer
  'receive-values
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-arg-as-var-spot-block
    cannot-read-roles
    cannot-write-roles))

(def-pseudo-instruction-byte-code-emitter receive-values
  (gensym-dstruct-bind ((nil var-spots types) instruction)
    (when var-spots
      (let* ((var-length (length var-spots))
	     (need-long-instruction-p
	       (or (>f var-length 255)
		   (and current-return-values-position
			(>f current-return-values-position 255)))))
	(emit-instruction-byte-code byte-code-stream
				    (if need-long-instruction-p
					'push-returned-values-long
					'push-returned-values))
	(if need-long-instruction-p
	    (progn
	      (emit-long-code-constant-to-stream byte-code-stream var-length)
	      (emit-long-code-constant-to-stream byte-code-stream
						 (or current-return-values-position
						     var-length)))
	    (progn
	      (write-byte-code-to-stream byte-code-stream var-length)
	      (write-byte-code-to-stream byte-code-stream
					 (or current-return-values-position
					     var-length)))))
      (loop for var-spot in var-spots
	    for type? in types
	    do
	(when type?
	  (call-stack-instruction-emitter type-check byte-code-stream type?))
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream var-spot)))))




;;; New to 3.0, the `CALL-RPC p-code instruction' is similar to the call
;;; instruction, except that it receives a remote procedure declaration instead
;;; of a procedure as its first argument, and it receives an additional argument
;;; which is the icp-interface object across which the call should be made.
;;; Values are received back from this call in the same way as from normal
;;; calls, via the receive-values p-code instruction.

;;;   (CALL-RPC designation icp-interface-object (expressions ...)
;;;             desired-returned-values-count)

;;; call-rpc ??? this instruction declaration is questionable.

(declare-instruction-for-optimizer
     'call-rpc
     '(cannot-write-local-variables
       cannot-read-local-variables
       cannot-write-roles
       cannot-read-roles))


(def-pseudo-instruction-byte-code-emitter call-rpc
  (gensym-dstruct-bind ((nil designation icp-designation arguments
			    desired-values-count)
		       instruction)
    (let ((arg-count (length arguments))
	  (emit-byte-codes-p t))
      (when (>f arg-count 255)
	(compiler-error
	  "CALL-ACROSS accepts a maximum of 255 arguments, this call passed ~a."
	  arg-count)
	(setq emit-byte-codes-p nil))
      (when (>f desired-values-count 255)
	(compiler-error
	  "CALL-ACROSS receives a maximum of 255 values, this call requested ~a."
	  desired-values-count)
	(setq emit-byte-codes-p nil))
      (when emit-byte-codes-p
	(emit-stack-node-tree byte-code-stream designation)
	(emit-stack-node-tree byte-code-stream icp-designation)
	(loop for arg in arguments do
	  (emit-stack-node-tree byte-code-stream arg))
	(emit-instruction-byte-code byte-code-stream 'call-rpc)
	(write-byte-code-to-stream byte-code-stream arg-count)
	(write-byte-code-to-stream byte-code-stream desired-values-count)))))




;;; Instruction 11, the `ALLOW-OTHER-PROCESSING p-code instruction' takes no
;;; arguments.  If the current time slice is expired, this statement causes a
;;; code body to enter a wait state, while scheduling itself for execution on
;;; the queue of code body invocations currently waiting for processing.  This
;;; will cause all other procedure instances waiting at this priority to get
;;; some processing time before this one gets another time slice.

;;;   (ALLOW-OTHER-PROCESSING)

(declare-instruction-for-optimizer
  'allow-other-processing
  '())

(def-pseudo-instruction-byte-code-emitter allow-other-processing
  (emit-instruction-byte-code byte-code-stream (car instruction)))




;;; The `OPEN-ROLE-ITERATION-NO-DOMAIN p-code instruction' is used to begin an
;;; iteration over the values returned by a role which takes no domain.  The
;;; arguments to this instruction are the role, the var-spot of the
;;; continuation, the var-spot for the first value, the required type of the
;;; value, the type returned by the role (or NIL if it is unknown), and the tag
;;; to branch to if no values are given by this role.

;;;   (OPEN-ROLE-ITERATION-NO-DOMAIN
;;;     role continuation-spot value-spot value-type role-type?
;;;     no-value-tag)


(declare-instruction-for-optimizer
  'open-role-iteration-no-domain
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-and-fourth-args-as-var-spots    
    cannot-read-local-variables
    cannot-write-roles
    branch-iteration-flow))

(def-pseudo-instruction-byte-code-emitter open-role-iteration-no-domain
  (gensym-dstruct-bind ((nil role continuation-spot value-spot value-type
			    role-type? no-value-tag)
		       instruction)
    (if (symbolp role)
	(record-free-reference 'class role)
	(record-free-references-of-role role))
    (call-stack-instruction-emitter open-role-iteration-no-domain
      byte-code-stream role no-value-tag)
    (call-stack-instruction-emitter pop-into-surrounding-local-var
      byte-code-stream continuation-spot)
    (unless (and role-type?
		 (type-specification-subtype-p role-type? value-type))
      (call-stack-instruction-emitter type-check byte-code-stream value-type))
    (call-stack-instruction-emitter pop-into-surrounding-local-var
      byte-code-stream value-spot)))




;;; The `OPEN-ROLE-ITERATION p-code instruction' is used to begin an iteration
;;; over the values returned by a role which does take a domain.  The arguments
;;; to this instruction are the role, the var-spot of the continuation, the
;;; var-spot for the first value, the required type of the value, the type
;;; returned by the role (or NIL if it is unknown), the tag to branch to if no
;;; values are given by this role, and the compiled domain designation.

;;;   (OPEN-ROLE-ITERATION
;;;     role continuation-spot value-spot value-type role-type?
;;;     no-value-tag . domain-list)

(declare-instruction-for-optimizer
  'open-role-iteration
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-and-fourth-args-as-var-spots    
    cannot-read-local-variables
    cannot-write-roles
    branch-iteration-flow))

(def-pseudo-instruction-byte-code-emitter open-role-iteration
  (gensym-dstruct-bind ((nil role continuation-spot value-spot value-type
			    role-type? no-value-tag . domain-list)
		       instruction)
    (record-free-references-of-role
      role
      (loop for domain in domain-list
	    collect (stack-node-value-type domain) using phrase-cons))
    (loop for domain in domain-list do
      (emit-stack-node-tree byte-code-stream domain))
    (call-stack-instruction-emitter open-role-iteration
      byte-code-stream role no-value-tag (length domain-list))
    (call-stack-instruction-emitter pop-into-surrounding-local-var
      byte-code-stream continuation-spot)
    (unless (and role-type?
		 (type-specification-subtype-p role-type? value-type))
      (call-stack-instruction-emitter type-check byte-code-stream value-type))
    (call-stack-instruction-emitter pop-into-surrounding-local-var
      byte-code-stream value-spot)))




;;; The `SERVE-NEXT-ITERATION-VALUE p-code instruction' is used to fetch the
;;; next value from an iteration state.  It receives var-spots for the
;;; iteration-state and value location, types for the value var-spot and role
;;; (if any), and a tag to branch to if there are no more values remaining.

;;;   (SERVE-NEXT-ITERATION-VALUE
;;;     continuation-spot value-spot required-type iteration-type?
;;;     no-values-tag)

(declare-instruction-for-optimizer
  'serve-next-iteration-value
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor second-and-third-args-as-var-spots
    reads-only-local-variables-specified-by-argument
    local-var-read-accessor second-arg-as-var-spot
    cannot-read-roles
    cannot-write-roles
    branch-iteration-flow))

(def-pseudo-instruction-byte-code-emitter serve-next-iteration-value
  (gensym-dstruct-bind ((nil continuation-spot value-spot
			    required-type iteration-type?
			    no-values-tag)
		       instruction)
    (call-stack-instruction-emitter serve-next-iteration-value
      byte-code-stream continuation-spot no-values-tag)
    (unless (and iteration-type?
		 (type-specification-subtype-p
		   iteration-type? required-type))
      (call-stack-instruction-emitter type-check byte-code-stream required-type))
    (call-stack-instruction-emitter pop-into-surrounding-local-var
      byte-code-stream value-spot)))




;;; The `CLOSE-ITERATION p-code instruction' is used to reclaim an
;;; iteration-state after it has been exhausted, or when an exit if leaves the
;;; scope of a generic iteration.  It takes the var-spot of the iteration-state.

;;;   (CLOSE-ITERATION iteration-state-var-spot)

(declare-instruction-for-optimizer
     'close-iteration
     '(no-wait-states
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor second-arg-as-var-spot
       cannot-read-local-variables
       cannot-write-roles
       cannot-read-roles))


(def-pseudo-instruction-byte-code-emitter close-iteration
  (call-stack-instruction-emitter close-iteration byte-code-stream (second instruction)))




;;; Instruction 22, the `SIGNAL-ERROR p-code instruction' takes expressions
;;; returning a symbol and a string, and will signal an error with the given
;;; name and description.

;;;   (SIGNAL-ERROR error-name-expression error-text-expression)

(declare-instruction-for-optimizer
  'signal-error
  '(return-flow))

(def-pseudo-instruction-byte-code-emitter signal-error
  (emit-stack-node-tree byte-code-stream (second instruction))
  (emit-stack-node-tree byte-code-stream (third instruction))
  (emit-instruction-byte-code byte-code-stream 'signal-error))




;;; Old instruction 24, the `CLOSE-CODE-BODY p-code instruction' closes the
;;; currently executing code body invocation and reschedules its parent, if any.
;;; Note that there should always be a parent, but it is checked in this
;;; implementation.

;;;   (CLOSE-CODE-BODY)

(declare-instruction-for-optimizer
  'close-code-body
  '(no-wait-states
    return-flow))

(def-pseudo-instruction-byte-code-emitter close-code-body
  (declare (ignore instruction))
  (emit-instruction-byte-code byte-code-stream 'close-code-body))




;;; Instruction 26, the `CALL-CODE-BODY p-code instruction' is used to launch a
;;; parallel, called code body from the current code body.  The expressions are
;;; arguments to the code body, to be bound to the first N local var positions
;;; within the newly created code body's environment.  The called code body is
;;; scheduled onto the immediate queue, and will be executed without wait state
;;; after the current code body invocation (and other code body invocations
;;; already on the immediate queue) have exited thier executions.

;;;   (CALL-CODE-BODY code-body-number . (arg-expression...))

(declare-optimizer-stack-instruction call-code-body)

(def-pseudo-instruction-byte-code-emitter call-code-body
  (gensym-dstruct-bind ((nil code-body-number . arg-expressions) instruction)
    (loop for arg in arg-expressions do
      (emit-stack-node-tree byte-code-stream arg))
    (call-stack-instruction-emitter call-code-body
      byte-code-stream code-body-number (length arg-expressions))))




;;; The `CALL-SCHEDULED-CODE-BODY p-code instruction' is similar to
;;; call-code-body, except that the code body which is launched is scheduled
;;; into the current queue, not the immediate queue, and so contains an implicit
;;; wait state between the launch and the beginning of execution of the called
;;; code body.

;;;   (CALL-SCHEDULED-CODE-BODY code-body-number . (arg-expression...))


(declare-instruction-for-optimizer
     'call-scheduled-code-body
     '(cannot-write-local-variables
       cannot-read-local-variables
       creates-new-code-body-invocation
       modifies-stack
       cannot-read-roles))

(def-pseudo-instruction-byte-code-emitter call-scheduled-code-body
  (gensym-dstruct-bind ((nil code-body-number . arg-expressions) instruction)
    (loop for arg in arg-expressions do
      (emit-stack-node-tree byte-code-stream arg))
    (call-stack-instruction-emitter call-scheduled-code-body
      byte-code-stream code-body-number (length arg-expressions))))




;;; Instruction 25, the `WAIT-FOR-CALLED-CODE-BODIES p-code instruction' is used
;;; to resynchronize execution in a code body which has launched parallel code
;;; bodies.  This instruction will wait until all called code bodies have
;;; returned.
;;;
;;;   (WAIT-FOR-CALLED-CODE-BODIES)

;;; the called code bodies would be the ones introducing the waiting/reshceduling
;;; rdf 11/5/93???


(declare-instruction-for-optimizer
     'wait-for-called-code-bodies
     '(cannot-write-local-variables
       cannot-read-local-variables
       cannot-write-roles
       cannot-read-roles))

(def-pseudo-instruction-byte-code-emitter wait-for-called-code-bodies
  (declare (ignore instruction))
  (emit-instruction-byte-code byte-code-stream 'wait-for-called-code-bodies))




;;; Instruction 23, the `ABORT-CALLED-CODE-BODIES p-code instruction' is used to
;;; abort all called code body invocations from the executing code body
;;; invocation.
;;;
;;;   (ABORT-CALLED-CODE-BODIES)

(declare-instruction-for-optimizer
  'abort-called-code-bodies
  '(cannot-read-local-variables
    cannot-write-local-variables
    deletes-procedure-invocations ;a role writer
    cannot-read-roles
    no-wait-states))

(def-pseudo-instruction-byte-code-emitter abort-called-code-bodies
  (declare (ignore instruction))
  (emit-instruction-byte-code byte-code-stream 'abort-called-code-bodies))




;;; Instruction 27, the `PAUSE p-code instruction' is used to enter a wait state
;;; for this procedure, waiting for something else to restart its processing.
;;; On restart, processing proceeds again at the next instruction.

;;;   (PAUSE)

(declare-instruction-for-optimizer
  'pause
  '())

(def-pseudo-instruction-byte-code-emitter pause
  (declare (ignore instruction))
  (emit-instruction-byte-code byte-code-stream 'pause))




;;; The `PAUSE-IF-CALLED-CODE-BODIES p-code instruction' is used to enter a wait
;;; state after a loop whose bodies execute with as a do in parallel until one
;;; completes.  This instruction will only pause if there are some called code
;;; bodies.

;;;   (PAUSE-IF-CALLED-CODE-BODIES)

;;; the called code bodies would be the ones introducing the waiting/reshceduling
;;; rdf 11/5/93???

(declare-instruction-for-optimizer
     'pause-if-called-code-bodies
     '(cannot-write-local-variables
       cannot-read-local-variables
       cannot-write-roles
       cannot-read-roles))


(def-pseudo-instruction-byte-code-emitter pause-if-called-code-bodies
  (declare (ignore instruction))
  (emit-instruction-byte-code byte-code-stream 'pause-if-called-code-bodies))




;;; The `POLLED-WAIT p-code instruction' is used to wait until an inferred
;;; logical expression becomes true, checking the condition on a polled basis.

;;;   (POLLED-WAIT inferred-logical wait-interval wait-interval-cache-var)

(declare-instruction-for-optimizer
  'polled-wait
  '(cannot-write-local-variables
    cannot-read-local-variables
    cannot-write-roles
    cannot-read-roles))


(def-pseudo-instruction-byte-code-emitter polled-wait
  (gensym-dstruct-bind ((nil inferred-logical wait-interval wait-var)
		       instruction)
    (if (type-specification-subtype-p
	  '(unknown-datum)
	  (stack-node-value-type inferred-logical))
	(let ((try-again-tag (generate-new-goto-tag))
	      (known-value-tag (generate-new-goto-tag))
	      (unknown-rejoins-tag (generate-new-goto-tag))
	      (get-out-tag (generate-new-goto-tag)))
	  ;; Cache the wait interval.
	  (emit-stack-node-tree byte-code-stream wait-interval)
	  (call-stack-instruction-emitter pop-into-surrounding-local-var
	    byte-code-stream wait-var)
	  ;; Emit a retry tag, and the instructions to evaluate the wait
	  ;; condition.
	  (register-tag-in-byte-code-stream
	    byte-code-stream try-again-tag)
	  (call-stack-instruction-emitter push-constant
	    byte-code-stream (make-evaluation-truth-value truth))
	  (emit-instruction-byte-code
	    byte-code-stream 'pop-into-default-allow-data-seeking)
	  (call-stack-instruction-emitter push-constant
	    byte-code-stream (make-evaluation-truth-value truth))
	  (emit-instruction-byte-code
	    byte-code-stream 'pop-into-allow-data-seeking)
	  (emit-instruction-byte-code byte-code-stream 'open-wake-up-collection)
	  (emit-stack-node-tree byte-code-stream inferred-logical)
	  (call-stack-instruction-emitter push-constant
	    byte-code-stream (make-evaluation-truth-value falsity))
	  (emit-instruction-byte-code
	    byte-code-stream 'pop-into-default-allow-data-seeking)
	  (call-stack-instruction-emitter push-constant
	    byte-code-stream (make-evaluation-truth-value falsity))
	  (emit-instruction-byte-code
	    byte-code-stream 'pop-into-allow-data-seeking)
	  ;; Branch out if no known value.
	  (call-stack-instruction-emitter branch-long-if-known
	    byte-code-stream known-value-tag)
	  ;; If the value is unknown, set wake ups, pop the unknown value, and
	  ;; push false.  After that branch to the spot where unknown rejoins.
	  (emit-instruction-byte-code byte-code-stream 'set-wake-ups)
	  (emit-instruction-byte-code byte-code-stream 'pop)
	  (call-stack-instruction-emitter push-constant
	    byte-code-stream (make-evaluation-truth-value falsity))
	  (call-stack-instruction-emitter branch-long byte-code-stream unknown-rejoins-tag)
	  ;; If the value is known, clear all wake ups and join the common
	  ;; thread.
	  (register-tag-in-byte-code-stream
	    byte-code-stream known-value-tag)
	  (emit-instruction-byte-code byte-code-stream 'clear-wake-ups)
	  ;; For both known and unknown, reset the expiration, close wake up
	  ;; collection, and then branch to the end if true.
	  (register-tag-in-byte-code-stream
	    byte-code-stream unknown-rejoins-tag)
	  (emit-instruction-byte-code
	    byte-code-stream 'reset-expiration)
	  (emit-instruction-byte-code
	    byte-code-stream 'close-wake-up-collection)
	  (call-stack-instruction-emitter branch-long-if-not-false
	    byte-code-stream get-out-tag)
	  ;; If the value was false or unknown, wait for the retry interval,
	  ;; then branch up and try again.  Note that if wake ups are set, they
	  ;; will wake it up sooner than the retry, and we will branch up to the
	  ;; top again.
	  (call-stack-instruction-emitter push-from-surrounding-local-var
	    byte-code-stream wait-var)
	  (emit-instruction-byte-code byte-code-stream 'wait-for-interval)
	  (call-stack-instruction-emitter begin-activity
	    byte-code-stream 
	    (activity-index "wait until statement")
	    t)
	  (call-stack-instruction-emitter branch-long byte-code-stream try-again-tag)
	  (register-tag-in-byte-code-stream
	    byte-code-stream get-out-tag))
	;; If inferred expression is always known.
	(let ((try-again-tag (generate-new-goto-tag))
	      (get-out-tag (generate-new-goto-tag)))
	  ;; Cache the wait interval.
	  (emit-stack-node-tree byte-code-stream wait-interval)
	  (call-stack-instruction-emitter pop-into-surrounding-local-var
	    byte-code-stream wait-var)
	  ;; Emit a retry tag, and the instructions to evaluate the wait
	  ;; condition.
	  (register-tag-in-byte-code-stream
	    byte-code-stream try-again-tag)
	  (emit-stack-node-tree byte-code-stream inferred-logical)
	  (call-stack-instruction-emitter branch-long-if-not-false
	    byte-code-stream get-out-tag)
	  ;; If the value was false or unknown, wait for the retry interval,
	  ;; then branch up and try again.  Note that if wake ups are set, they
	  ;; will wake it up sooner than the retry, and we will branch up to the
	  ;; top again.
	  (call-stack-instruction-emitter push-from-surrounding-local-var
	    byte-code-stream wait-var)
	  (emit-instruction-byte-code byte-code-stream 'wait-for-interval)
	  (call-stack-instruction-emitter begin-activity
	    byte-code-stream 
	    (activity-index "wait until statement")
	    t)
	  (call-stack-instruction-emitter branch-long byte-code-stream try-again-tag)
	  (register-tag-in-byte-code-stream
	    byte-code-stream get-out-tag)))))




;;; The `WAIT-FOR-INTERVAL p-code instruction' is used to wait for an interval
;;; of time.  When issued alone, the procedure will sleep for the given interval
;;; of time.  When given as part of a polled wait or other compound statement,
;;; it will wait for at most this long, or until woken up by some other event.

;;;   (WAIT-FOR-INTERVAL interval-expression)

(declare-instruction-for-optimizer
  'wait-for-interval
  '())

(def-pseudo-instruction-byte-code-emitter wait-for-interval
  (emit-stack-node-tree byte-code-stream (second instruction))
  (emit-instruction-byte-code byte-code-stream 'wait-for-interval))




;;; The `WAIT pseudo-code instruction' is used to cause a code body invocation
;;; to wait until woken up or killed by something else.  Note that this
;;; instruction is the same as pause, except that this is not considered an
;;; unconditional branch by the dead code eliminator.  In other words, it is
;;; possible to be woken up from a wait, but not from a pause.

;;;   (WAIT)

(declare-instruction-for-optimizer
  'wait
  ;; really and truly anything can happen
  '())

(def-pseudo-instruction-byte-code-emitter wait
  (declare (ignore instruction))
  (emit-instruction-byte-code byte-code-stream 'pause))




;;; The `INSTALL-EVENT-DETECTOR pseudo-code instruction' is used to install an
;;; event detector in a given variable-or-parameter or place reference.  The
;;; location is the first argument to this instruction, and the type of event
;;; detector is a symbol which is the second argument.

;;;   INSTALL-EVENT-DETECTOR (install-location, event-type)

(declare-instruction-for-optimizer
     'install-event-detector
     '(no-wait-states
       cannot-write-local-variables
       cannot-read-local-variables
       modifies-computation-instance-event-detector
       cannot-read-roles))


(def-pseudo-instruction-byte-code-emitter install-event-detector
  (gensym-dstruct-bind ((nil location-expression event-type-expression)
		       instruction)
    (emit-stack-node-tree byte-code-stream location-expression)
    (emit-stack-node-tree byte-code-stream event-type-expression)
    (call-stack-instruction-emitter funcall-instruction
      byte-code-stream 'install-event-detector)))


(declare-instruction-for-optimizer
     'clear-event-detectors
     '(no-wait-states
       cannot-write-local-variables
       cannot-read-local-variables
       writes-event-detector-list-on-current-computation-frame
       cannot-read-roles))


(def-pseudo-instruction-byte-code-emitter clear-event-detectors
  (declare (ignore byte-code-stream instruction))
  nil)



;;;




;;; The `COLLECT-DATA p-code instruction' is used to collect sets of expression
;;; results into procedure local variables.  The instruction takes five
;;; arguments: a list of pairs of var-spots and expressions, a nil or the
;;; var-spot containing the timestamp of the timeout time, an instruction
;;; address to branch to if all collections completed, an instruction address to
;;; branch to if the collection timed out, and a compiled expression which
;;; returns whether or not the expression is timed out.

;;; If all evaluations of the expressions succeed, values will be set into the
;;; var-spots given, all failed to receive a value flags for those var-spots
;;; will be set to 0, and control will be branched to the completion instruction
;;; address.  If any of the expressions returned unknown and there is no
;;; timeout, wake ups will be set from the variables that had no values to the
;;; currently executing code body invocation, the program counter will be set to
;;; resume at this instruction again, and the invocation will enter a wait
;;; state.  If any of the expressions returned unknown, there is a timeout
;;; given, and the timeout has not expired, a task will be scheduled for the
;;; timeout time to wake up this invocation, wake ups will be set from the
;;; variables that had no values, the program counter will be set to resume at
;;; this instruction, and a wait state will be entered.  If any of the
;;; expressions returned unknown, there is a timeout, and the timeout has
;;; expired, then those var-spots whose expressions returned values will be
;;; mutated, their failed to receive a value flags will be set to 0, the
;;; var-spots whose expressions had no values will not be mutated, but their
;;; failed flags will be set to 1, and finally the program counter will be
;;; resumed at the timeout instruction.  Note that if there is no timeout time
;;; given, no timeout instruction address need be given.

;;; Note that it is an error to execute this statement in a simulation
;;; procedure.

;;;   (COLLECT-DATA ((var-spot expression) ...)
;;;     timeout-varspot? completed-tag? failed-tag? timeout-predicate?
;;;     success-spot time-remaining-expression?)

(declare-instruction-for-optimizer
     'collect-data
     '(cannot-read-local-variables
       cannot-write-roles
       cannot-read-roles
       timeout-flow))

(def-pseudo-instruction-byte-code-emitter collect-data
  (gensym-dstruct-bind ((nil var-spot-expression-pairs
			    timeout-varspot? completed-tag? failed-tag?
			    timeout-predicate? success-spot
			    time-remaining-expression?)
		       instruction)
    (let ((retry-tag (generate-new-goto-tag))
	  (some-failed-tag (generate-new-goto-tag))
	  (non-timeout-tag (generate-new-goto-tag))
	  (success-tag (generate-new-goto-tag))
	  (reversed-var-spots nil))
      (cond
	(timeout-varspot?
	 ;; Set the final evaluation flag, cache the success-flag, and open wake
	 ;; up collection.
	
         (call-stack-instruction-emitter push-constant ;added by SoftServe
                                         byte-code-stream (make-evaluation-truth-value falsity)) 
        
	 (register-tag-in-byte-code-stream
	   byte-code-stream retry-tag)
	 ;(emit-stack-node-tree byte-code-stream timeout-predicate?)
	 (emit-instruction-byte-code
	   byte-code-stream 'pop-into-final-evaluation-attempt)
	 (call-stack-instruction-emitter push-constant
	   byte-code-stream (make-evaluation-truth-value truth))
	 (call-stack-instruction-emitter pop-into-surrounding-local-var
	   byte-code-stream success-spot)
	 (emit-instruction-byte-code byte-code-stream 'open-wake-up-collection)
	 (call-stack-instruction-emitter push-constant
	   byte-code-stream (make-evaluation-truth-value truth))
	 (emit-instruction-byte-code
	   byte-code-stream 'pop-into-default-allow-data-seeking)

	 ;; Evaluate all expressions.  If any is unknown, stuff false into the
	 ;; success flag, and leave a NIL on the stack.  Leave all good values
	 ;; on the stack.
	 (loop for (var-spot expression) in var-spot-expression-pairs
	       for unknown-allowed? = (type-specification-subtype-p
					'(unknown-datum)
					(stack-node-value-type expression))
	       do
	   (setq reversed-var-spots (phrase-cons var-spot reversed-var-spots))
	   (emit-stack-node-tree byte-code-stream expression)
	   (when unknown-allowed?
	     (let ((known-tag (generate-new-goto-tag)))
	       (call-stack-instruction-emitter branch-long-if-known byte-code-stream known-tag)
	       (emit-instruction-byte-code byte-code-stream 'pop)
	       (call-stack-instruction-emitter push-constant
		 byte-code-stream (make-evaluation-truth-value falsity))
	       (call-stack-instruction-emitter pop-into-surrounding-local-var
		 byte-code-stream success-spot)
	       (call-stack-instruction-emitter push-nones byte-code-stream 1)
	       (register-tag-in-byte-code-stream
		 byte-code-stream known-tag)
	       (emit-instruction-byte-code byte-code-stream
					   'reset-expiration))))
	 (call-stack-instruction-emitter push-constant
	   byte-code-stream (make-evaluation-truth-value falsity))
	 (emit-instruction-byte-code
	   byte-code-stream 'pop-into-default-allow-data-seeking)
         (call-stack-instruction-emitter push-from-surrounding-local-var
	      byte-code-stream success-spot)
	    (call-stack-instruction-emitter branch-long-if-true
                                         byte-code-stream success-tag)
	   	  
	 ;; If this is not the timeout pass, branch to the normal handlers.
	 (call-stack-instruction-emitter push-from-surrounding-local-var
	   byte-code-stream success-spot)
	 (call-stack-instruction-emitter branch-long-if-true
	   byte-code-stream success-tag)	 
	 (emit-stack-node-tree byte-code-stream timeout-predicate?)
	 (call-stack-instruction-emitter branch-long-if-not-true
	   byte-code-stream non-timeout-tag)
	 ;; This is the timeout pass, clear wake ups, reset the final attempt
	 ;; flag, pop all the variable values into the locals (possibly popping
	 ;; some nils, which is ok) and branch if success to the end of collect
	 ;; data, else branch to the timeout statement.
	 (emit-instruction-byte-code byte-code-stream 'clear-wake-ups)
	 (emit-instruction-byte-code byte-code-stream 'close-wake-up-collection)
	 (call-stack-instruction-emitter push-constant
	   byte-code-stream (make-evaluation-truth-value falsity))
	 (emit-instruction-byte-code
	   byte-code-stream 'pop-into-final-evaluation-attempt)
	 (loop for var-spot in reversed-var-spots
	       do
	   (call-stack-instruction-emitter pop-into-surrounding-local-var
	     byte-code-stream var-spot))
	 (unless (eql completed-tag? failed-tag?)
	   (call-stack-instruction-emitter push-from-surrounding-local-var
	     byte-code-stream success-spot)
	   (call-stack-instruction-emitter branch-long-if-not-true
	     byte-code-stream failed-tag?))
	 (call-stack-instruction-emitter branch-long byte-code-stream completed-tag?)
	 ;; In the non-timeout case, branch to some-failed code if success flag
	 ;; has been set false.
	 (register-tag-in-byte-code-stream
	   byte-code-stream non-timeout-tag)
	 (call-stack-instruction-emitter push-from-surrounding-local-var
	   byte-code-stream success-spot)
	 (call-stack-instruction-emitter branch-long-if-not-true
	   byte-code-stream some-failed-tag)
	 ;; All succeeded, clear the wake ups, close wake up collection, pop the
	 ;; values into the local vars, and branch to the end of the collect
	 ;; data.
     ;(if (g2-enterprise-p) 				;add by glority, the register-tag-in-byte-code-stream 
	 ;(register-tag-in-byte-code-stream     ; has been call twice when enterprise version.
	 ;  byte-code-stream success-tag)	    ;So delete one of it.
     ;  nil)								;end edit by glority.
	 (register-tag-in-byte-code-stream
	   byte-code-stream success-tag)
	 (emit-instruction-byte-code byte-code-stream 'clear-wake-ups)
	 (emit-instruction-byte-code byte-code-stream 'close-wake-up-collection)
	 (loop for var-spot in reversed-var-spots
	       do
	   (call-stack-instruction-emitter pop-into-surrounding-local-var
	     byte-code-stream var-spot))
	 (call-stack-instruction-emitter branch-long byte-code-stream completed-tag?)
	 ;; We know that some failed and that this is not the timeout case.  Set
	 ;; the wake ups, close wake up collection, pop the values off the
	 ;; stack, enter a wait-for-interval until the timeout, then branch back
	 ;; up to the top again.
	 (register-tag-in-byte-code-stream byte-code-stream some-failed-tag)
	 (emit-instruction-byte-code byte-code-stream 'set-wake-ups)
	 (emit-instruction-byte-code byte-code-stream 'close-wake-up-collection)
	 (call-stack-instruction-emitter pop-values byte-code-stream (length
							reversed-var-spots))
	 (emit-stack-node-tree byte-code-stream time-remaining-expression?)
	 (emit-instruction-byte-code byte-code-stream 'wait-for-interval)

	 (emit-stack-node-tree byte-code-stream timeout-predicate?) ;moved this predicate here

	 (call-stack-instruction-emitter branch-long byte-code-stream retry-tag))
	(t
	 ;; Cache the success-flag, and open wake up collection.
	 (register-tag-in-byte-code-stream byte-code-stream retry-tag)
	 (call-stack-instruction-emitter push-constant
	   byte-code-stream (make-evaluation-truth-value truth))
	 (call-stack-instruction-emitter pop-into-surrounding-local-var
	   byte-code-stream success-spot)
	 (emit-instruction-byte-code byte-code-stream 'open-wake-up-collection)
	 (call-stack-instruction-emitter push-constant
	   byte-code-stream (make-evaluation-truth-value truth))
	 (emit-instruction-byte-code
	   byte-code-stream 'pop-into-default-allow-data-seeking)

	 ;; Evaluate all expressions.  If any is unknown, stuff false into the
	 ;; success flag, and leave a NIL on the stack.  Leave all good values
	 ;; on the stack.
	 (loop for (var-spot expression) in var-spot-expression-pairs
	       for unknown-allowed? = (type-specification-subtype-p
					'(unknown-datum)
					(stack-node-value-type expression))
	       do
	   (setq reversed-var-spots (phrase-cons var-spot reversed-var-spots))
	   (emit-stack-node-tree byte-code-stream expression)
	   (when unknown-allowed?
	     (let ((known-tag (generate-new-goto-tag)))
	       (call-stack-instruction-emitter branch-long-if-known byte-code-stream known-tag)
	       (call-stack-instruction-emitter push-constant
		 byte-code-stream (make-evaluation-truth-value falsity))
	       (call-stack-instruction-emitter pop-into-surrounding-local-var
		 byte-code-stream success-spot)
	       (register-tag-in-byte-code-stream byte-code-stream known-tag)
	       (emit-instruction-byte-code byte-code-stream
					   'reset-expiration))))
	 (call-stack-instruction-emitter push-constant
	   byte-code-stream (make-evaluation-truth-value falsity))
	 (emit-instruction-byte-code
	   byte-code-stream 'pop-into-default-allow-data-seeking)
	   

	 ;; Branch to some-failed code if success flag has been set false.
	 (call-stack-instruction-emitter push-from-surrounding-local-var
	   byte-code-stream success-spot)
	 (call-stack-instruction-emitter branch-long-if-not-true
	   byte-code-stream some-failed-tag)
	 ;; All succeeded, clear the wake ups, close wake up collection, pop the
	 ;; values into the local vars, and branch to the end of the collect
	 ;; data.
	 (emit-instruction-byte-code byte-code-stream 'clear-wake-ups)
	 (emit-instruction-byte-code byte-code-stream 'close-wake-up-collection)
	 (loop for var-spot in reversed-var-spots
	       do
	   (call-stack-instruction-emitter pop-into-surrounding-local-var
	     byte-code-stream var-spot))
	 (call-stack-instruction-emitter branch-long byte-code-stream completed-tag?)
	 ;; We know that some failed and that this is not the timeout case.  Set
	 ;; the wake ups, close wake up collection, pop the values off the
	 ;; stack, enter a wait-for-interval until the timeout, then branch back
	 ;; up to the top again.
	 (register-tag-in-byte-code-stream byte-code-stream some-failed-tag)
	 (emit-instruction-byte-code byte-code-stream 'set-wake-ups)
	 (emit-instruction-byte-code byte-code-stream 'close-wake-up-collection)
	 (call-stack-instruction-emitter pop-values byte-code-stream (length reversed-var-spots))
	 (emit-instruction-byte-code byte-code-stream 'pause)
	 (call-stack-instruction-emitter branch-long byte-code-stream retry-tag))))))



;;; The `RETURN-FROM-FUNCTION p-code instruction' is used to return a value on
;;; the stack from a user-defined function.  This instruction takes one value
;;; off the stack and returns it.

;;; Note that this instruction exits user functions and that the instruction
;;; return-from-function knows how to clean up extra stack values.  So, this
;;; emitter handles generating space for any stack frame vars, since the
;;; return-from-instruction will clean them up very quickly by itself.

;;;   RETURN-FROM-FUNCTION (expression)

(declare-instruction-for-optimizer
     'return-from-function
     '(no-wait-states
       cannot-write-local-variables
       cannot-read-local-variables
       cannot-write-roles
       cannot-read-roles
       return-flow))


(def-pseudo-instruction-byte-code-emitter return-from-function
  (let* ((stack-node (second instruction))
	 (stack-frame-vars (stack-node-stack-frame-vars-needed stack-node)))
    (when (>f stack-frame-vars 0)
      (call-stack-instruction-emitter push-nones byte-code-stream stack-frame-vars)
      (setf (stack-node-stack-frame-vars-needed stack-node) 0))
    (emit-stack-node-tree byte-code-stream stack-node)
    (emit-instruction-byte-code byte-code-stream 'return-from-function)))




;;; Instruction 29, the `SYSTEM-CALL p-code instruction' takes a list of
;;; var-spots, a function name, and a list of argument expressions.

;;; The procedure-statement-compilers for system-call and system-call-assignment
;;; test that the number of arguments and return values are not greater than the
;;; maximum allowed.

;;; Code is emitted that will push the lisp-name and the arguments onto the
;;; stack, execute the system-call instruction with argument count and expected
;;; return value count code constants, and type check and pop the return values
;;; into the local variables.

;; Note that this instruction was previously called lisp-call.  cpm, 6/30/91.

;;;   (SYSTEM-CALL (var-spots ...) (return-types ...) lisp-name (expressions ...))

(declare-instruction-for-optimizer
  'system-call
  '())


(def-pseudo-instruction-byte-code-emitter system-call
  (gensym-dstruct-bind ((nil var-spots return-types lisp-name arguments)
		       instruction)
    #+development
    (unless (memq lisp-name system-call-function-list)
      (cerror
	"Continue compilation of SYSTEM-CALL statement."
	"Before compiling this system-procedure, the lisp function ~a must be ~
         declared (in the G2 source) using declare-system-procedure-function.  ~
         Add this declaration and then recompile this system-procedure."
	lisp-name))
    #+development
    (gensym-pushnew lisp-name compiled-system-call-function-list)
    (call-stack-instruction-emitter push-constant byte-code-stream lisp-name)
    (loop for arg in arguments do
      (emit-stack-node-tree byte-code-stream arg))
    (emit-instruction-byte-code byte-code-stream 'system-call)
    (write-byte-code-to-stream byte-code-stream (length arguments))
    (write-byte-code-to-stream byte-code-stream (length var-spots))
    ;; The values will be pushed on the stack in reverse order.  The first value
    ;; is on top.
    (loop for var-spot in var-spots
	  for return-type in return-types
	  do
      (call-stack-instruction-emitter type-check byte-code-stream return-type)
      (call-stack-instruction-emitter pop-into-surrounding-local-var
	byte-code-stream var-spot))))




;;; The pseudo-instruction `execute-antecedent' takes a compiled antecedent
;;; logical expression, a var-spot for a certainty cache variable (or NIL), a
;;; var-spot for an expiration cache (or NIL), a tag to branch to if the
;;; antecedent is true, a tag for false, and a possibly tag for unknown.  When
;;; the tag for unknown is omitted, it is because the logical-expresion has been
;;; proven to always return a known value, so no code need be emitted to handle
;;; that case.

;;;   (EXECUTE-ANTECENDENT
;;;     logical-expression certainty-cache? expiration-cache?
;;;     true-tag false-tag unknown-tag?)

(declare-instruction-for-optimizer
  'execute-antecedent
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-and-fourth-args-as-var-spots
    cannot-read-local-variables
    writes-stack-expiration-value
    true-false-or-unknown-flow
    cannot-read-roles))


(def-pseudo-instruction-byte-code-emitter execute-antecedent
  (gensym-dstruct-bind ((nil logical-expression
			    certainty-var-spot? expiration-var-spot?
			    true-tag false-tag unknown-tag?)
		       instruction)
    (let ((known-tag (generate-new-goto-tag)))
      ;; Evaluate the antecedent.
      (emit-stack-node-tree byte-code-stream logical-expression)
      (when unknown-tag?
	(call-stack-instruction-emitter branch-long-if-known byte-code-stream known-tag)
	;; If unknown pop the value off the stack and branch to the unknown tag.
	(emit-instruction-byte-code byte-code-stream 'pop)
	(call-stack-instruction-emitter branch-long byte-code-stream unknown-tag?)
	(register-tag-in-byte-code-stream byte-code-stream known-tag))
      ;; If known, cache the expiration and value and branch to the true and
      ;; false tags.
      (when certainty-var-spot?
	(emit-instruction-byte-code byte-code-stream 'push-copy-of-top-of-stack)
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream certainty-var-spot?))
      (when expiration-var-spot?
	(emit-instruction-byte-code byte-code-stream 'push-expiration)
	(call-stack-instruction-emitter pop-into-surrounding-local-var
	  byte-code-stream expiration-var-spot?))
      (call-stack-instruction-emitter branch-long-if-not-true byte-code-stream false-tag)
      (call-stack-instruction-emitter branch-long byte-code-stream true-tag))))



;;; The pseudo-instruction `execute-simulation-formula' takes a compiled
;;; simulation formula expression, a var-spot for the result, and a tag to branch
;;; to if the result is unknown.


;(def-optimizer-goto-tag-references execute-simulation-formula ;
;    simulation-forumula-unknown)

(declare-instruction-for-optimizer
  'execute-simulation-formula
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles
    sets-expiration
    branch-if-unknown-flow))

(def-pseudo-instruction-byte-code-emitter execute-simulation-formula
  (gensym-dstruct-bind ((nil expression result-var-spot unknown-tag) instruction)
    (let ((known-tag (generate-new-goto-tag)))
      ;; Evaluate the expression.
      (emit-stack-node-tree byte-code-stream expression)
      (call-stack-instruction-emitter branch-long-if-known byte-code-stream known-tag)
      ;; If unknown pop the value off the stack and branch to the unknown tag.
      (call-stack-instruction-emitter pop-into-surrounding-local-var 
	byte-code-stream result-var-spot)
      (call-stack-instruction-emitter branch-long byte-code-stream unknown-tag)
      ;; If known, put the value into the result var spot.
      (register-tag-in-byte-code-stream byte-code-stream known-tag)
      (call-stack-instruction-emitter pop-into-surrounding-local-var 
	byte-code-stream result-var-spot))))

;; A branch, and the known tag, could be avoided here if there were an
;; call-stack-instruction-emitter branch-long-if-unknown



;;; The pseudo-instruction `complete-rule-instance' directly emits the stack
;;; instruction to complete a rule instance.  It takes one argument on the
;;; stack, which is whether or not to close the instance, or allow it to
;;; continue if it has not timed out.

;;; Argument is now a 1 or 0 in the instruction stream, rather than a
;;; true or false on the stack. This is more efficient, and also provides
;;; more useful information to the C compiler -alatto, 10/15/98

;;;   (COMPLETE-RULE-INSTANCE close?)

;; seems to only side effect the ri-state of the current-computation-instance

(declare-optimizer-stack-instruction complete-rule-instance)

(def-pseudo-instruction-byte-code-emitter complete-rule-instance
  (emit-instruction-byte-code byte-code-stream 'complete-rule-instance)
  (write-byte-code-to-stream byte-code-stream
			     (if (second instruction) 1 0)))

;;; The pseudo-instruction `complete-simulation-variable-evaluation' directly
;;; emits the stack instruction to complete an evaluation of a simulated variable.
;;; It takes one argument on the stack, which indicates whether or not the
;;; evaluation returned a known value.

(declare-instruction-for-optimizer
     'complete-simulation-variable-evaluation
     '(no-wait-states
       cannot-write-local-variables
       cannot-read-local-variables
       cannot-write-roles
       cannot-read-roles
       return-flow))

(def-pseudo-instruction-byte-code-emitter complete-simulation-variable-evaluation
  (let ((value-known? (second instruction)))
    (call-stack-instruction-emitter push-constant
      byte-code-stream
      (if value-known?
	  (make-evaluation-truth-value truth)
	  (make-evaluation-truth-value falsity)))
    (emit-instruction-byte-code 
      byte-code-stream 'complete-simulation-variable-evaluation)))



;;; The pseudo-instruction `check-stack' is only emitted during development
;;; compiles.  It checks that the stack is empty, and if not issues a stack
;;; error.

;;;   (CHECK-STACK)

(declare-instruction-for-optimizer
     'check-stack
     '(no-wait-states
       cannot-write-local-variables
       cannot-read-local-variables
       modifies-stack
       cannot-read-roles))


(def-pseudo-instruction-byte-code-emitter check-stack
  (declare (ignore instruction))
  (emit-instruction-byte-code byte-code-stream 'check-stack))




;;; The pseudo-instruction `open-wake-up-collection' sets up the environment for
;;; registering wake ups to the current computation instance.

;;;   (OPEN-WAKE-UP-COLLECTION)

(declare-instruction-for-optimizer
     'open-wake-up-collection
     '(no-wait-states
       cannot-write-local-variables
       cannot-read-local-variables
       write-variables-that-did-not-have-values
       cannot-read-roles))

(def-pseudo-instruction-byte-code-emitter open-wake-up-collection
  (declare (ignore instruction))
  (emit-instruction-byte-code byte-code-stream 'open-wake-up-collection))




;;; The pseudo-instruction `set-wake-ups' sets any currently pending wake ups
;;; which have been collected.

;;;   (SET-WAKE-UPS)


(declare-instruction-for-optimizer
     'set-wake-ups
     '(no-wait-states
       cannot-write-local-variables
       cannot-read-local-variables
       write-variables-that-did-not-have-values
       cannot-read-roles))


(def-pseudo-instruction-byte-code-emitter set-wake-ups
  (declare (ignore instruction))
  (emit-instruction-byte-code byte-code-stream 'set-wake-ups))




;;; The pseudo-instruction `clear-wake-ups' clears any currently pending wake
;;; ups which have been collected.

;;;   (CLEAR-WAKE-UPS)

(declare-instruction-for-optimizer
     'clear-wake-ups
     '(no-wait-states
       cannot-write-local-variables
       cannot-read-local-variables
       write-variables-that-did-not-have-values
       cannot-read-roles))


(def-pseudo-instruction-byte-code-emitter clear-wake-ups
  (declare (ignore instruction))
  (emit-instruction-byte-code byte-code-stream 'clear-wake-ups))




;;; The pseudo-instruction `close-wake-up-collection' closes the collection
;;; environment for wake ups.  If there are any currently pending wake ups, they
;;; are cleared before the close.

;;;   (CLOSE-WAKE-UP-COLLECTION)

(declare-instruction-for-optimizer
     'close-wake-up-collection
     '(no-wait-states
       cannot-write-local-variables
       cannot-read-local-variables
       sets-wake-ups
       cannot-read-roles))

(def-pseudo-instruction-byte-code-emitter close-wake-up-collection
  (declare (ignore instruction))
  (emit-instruction-byte-code byte-code-stream 'close-wake-up-collection))




;;; The pseudo-instruction `set-expiration' takes a var-spot and will cause the
;;; value stored in the variable to pushed into the stack-expiration register.

;;;   (SET-EXPIRATION var-spot)

(declare-instruction-for-optimizer
  'set-expiration
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-read-roles
    sets-stack-expiration))

(def-pseudo-instruction-byte-code-emitter set-expiration
  (let ((var-spot (second instruction)))
    (call-stack-instruction-emitter push-from-surrounding-local-var byte-code-stream var-spot)
    (emit-instruction-byte-code byte-code-stream 'pop-expiration)))




;;; The pseudo-instruction `branch-if-known' takes a tag as its argument and
;;; causes a branch to occur to that tag if the current expiration register
;;; shows a known value.

;;;   (BRANCH-IF-KNOWN tag)

(declare-instruction-for-optimizer
  'branch-if-known
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles
    sets-expiration
    branch-if-known-flow
    cost 2))



(def-pseudo-instruction-byte-code-emitter branch-if-known
  (let ((tag (second instruction)))
    (call-stack-instruction-emitter branch-long-if-known byte-code-stream tag)))




;;; The pseudo-instruction `begin-rule-actions' emits the stack instruction of
;;; the same name.  This instruction is executed when we have committed to
;;; beginning to take actions in a rule.

;;;   (BEGIN-RULE-ACTIONS)

(declare-instruction-for-optimizer
     'begin-rule-actions
     '(no-wait-states
       cannot-write-local-variables
       cannot-read-local-variables
       writes-rule-instance-state
       cannot-read-roles))


(def-pseudo-instruction-byte-code-emitter begin-rule-actions
  (declare (ignore instruction))
  (emit-instruction-byte-code byte-code-stream 'begin-rule-actions))




;;; The pseudo-instruction `add-to-action-cache' emits stack instructions to
;;; cache a block of variables into an action cache.  This instruction takes two
;;; arguments, a var-spot containing an action-cache, and block of var-spots to
;;; be cached.  Note that the block of var spots is a list of variable spots,
;;; where the first var-spot in the list is local to the current environment
;;; (i.e.  does not point to a spot in a surrounding environment), and the rest
;;; of the var spots occupy successive locations in the same environment vector.

;;;   (ADD-TO-ACTION-CACHE action-cache-var-spot var-spot-block)


(declare-instruction-for-optimizer
  'add-to-action-cache
  '(no-wait-states
    cannot-read-local-variables
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    modifies-stack
    cannot-write-roles
    branch-if-not-true-flow))

(def-pseudo-instruction-byte-code-emitter add-to-action-cache
  (gensym-dstruct-bind ((nil action-cache var-spot-block) instruction)
    (call-stack-instruction-emitter add-to-action-cache
      byte-code-stream action-cache var-spot-block)))




;;; The pseudo-instruction `restore-from-action-cache-or-branch' emits
;;; instructions which will either restore the values from an action cache back
;;; into the variables starting at the given var-spot-block location and
;;; continues execution in the main stream, or if the action cache is empty it
;;; will branch to the given tag.

;;;   (RESTORE-FROM-ACTION-CACHE-OR-BRANCH
;;;     action-cache? var-spot-block action-cache-empty-tag?)

(declare-instruction-for-optimizer
  'restore-from-action-cache-or-branch
  '(no-wait-states
    writes-only-local-variables-specified-by-argument
    local-var-write-accessor third-arg-as-var-spot-block
    cannot-read-local-variables
    cannot-read-roles
    cannot-write-roles
    branch-if-unknown-flow))

(def-pseudo-instruction-byte-code-emitter restore-from-action-cache-or-branch
  (gensym-dstruct-bind ((nil action-cache var-spot-block action-cache-empty-tag)
		       instruction)
    (call-stack-instruction-emitter restore-from-action-cache-or-branch
      byte-code-stream action-cache var-spot-block action-cache-empty-tag)))




;;; The pseudo-instruction `clear-action-cache' takes a local var pointing to an
;;; action cache object and clears any collected cachings in this variable.
;;; This is done to ensure that a previous attempt at a rule did not leave
;;; anything in the cache between attempts at the actions of a rule.

;;; This instruction is currently implemented by assigning NIL into that
;;; location, which causes the previous value to be reclaimed as an evaluation
;;; value.

;;;   (CLEAR-ACTION-CACHE action-cache-var-spot)

(declare-instruction-for-optimizer
     'clear-action-cache
     '(no-wait-states
       writes-only-local-variables-specified-by-argument
       local-var-write-accessor second-arg-as-var-spot
       cannot-read-local-variables
       cannot-write-roles
       cannot-read-roles))

(def-pseudo-instruction-byte-code-emitter clear-action-cache
  (call-stack-instruction-emitter push-constant byte-code-stream (make-evaluation-symbol nil))
  (call-stack-instruction-emitter pop-into-surrounding-local-var
    byte-code-stream (second instruction)))




;;; The pseudo-instruction `allocate-stack-frame-vars' is used to push NILs onto
;;; the stack to provide for any needed stack frame vars.  These vars are left
;;; there on that stack, and then either a pop-values or and explicit
;;; close-rule-instance instruction is allowed to remove them with any other
;;; stack values it finds.  Note that this is used before entry to rule
;;; executions in general, and around individual procedure statements.

;;; ALLOCATE-STACK-FRAME-VARS(var-count)

;;; DEALLOCATE-STACK-FRAME-VARS(var-count)

(declare-instruction-for-optimizer
  'allocate-stack-frame-vars
  '(no-wait-states
    cannot-write-local-variables
    cannot-read-local-variables
    cannot-read-roles
    modifies-stack
    cost 2))

(def-pseudo-instruction-byte-code-emitter allocate-stack-frame-vars
  (let ((var-count (second instruction)))
    (when (>f var-count 0)
      (call-stack-instruction-emitter push-nones byte-code-stream var-count))))

(declare-optimizer-stack-instruction deallocate-stack-frame-vars)

(def-pseudo-instruction-byte-code-emitter deallocate-stack-frame-vars
  (let ((var-count (second instruction)))
    (when (>f var-count 0)
      (call-stack-instruction-emitter pop-values byte-code-stream var-count))))




;;; The pseudo-instruction `complete-generic-formula' is used to context switch
;;; out of a formula and into the next computation.  It takes one argument, the
;;; result of the formula.  The pseudo-instruction `complete-cell-expression' is
;;; used to context switch out of a cell expression evaluation and into the next
;;; computation.  It takes one argument, the result of the expression.

;;; COMPLETE-GENERIC-FORMULA(formula-result)

;;; COMPLETE-CELL-EXPRESSION(expression-result)


(declare-instruction-for-optimizer
     'complete-generic-formula
     '(no-wait-states
       cannot-write-local-variables
       cannot-read-local-variables
       cannot-write-roles
       cannot-read-roles
       return-flow))

(def-pseudo-instruction-byte-code-emitter complete-generic-formula
  (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
    byte-code-stream (second instruction))
  (emit-instruction-byte-code byte-code-stream 'complete-generic-formula))

(declare-instruction-for-optimizer
     'complete-cell-expression
     '(no-wait-states
       cannot-write-local-variables
       cannot-read-local-variables
       cannot-write-roles
       cannot-read-roles
       return-flow))

(def-pseudo-instruction-byte-code-emitter complete-cell-expression
  (call-stack-instruction-emitter push-value-or-none-from-surrounding-local-var
    byte-code-stream (second instruction))
  (emit-instruction-byte-code byte-code-stream 'complete-cell-expression))




;;; The pseudo-instruction `begin-activity' is used to register the beginning
;;; point of a new activity within the computation context and the profiling
;;; facilities.  Each action and most procedure statements are activities.  It
;;; takes two constant argument, an activity which has already been transformed
;;; from a string to a fixnum, a flag indicating if this change of activity
;;; should not be profiled.

;;;   BEGIN-ACTIVITY(activity-number, suppress-profile-p)

(declare-instruction-for-optimizer
     'begin-activity
     '(no-wait-states
       cannot-write-local-variables
       cannot-read-local-variables
       writes-current-activity
       cannot-read-roles))

(def-pseudo-instruction-byte-code-emitter begin-activity
  (call-stack-instruction-emitter begin-activity
    byte-code-stream (second instruction) (third instruction)))



;;; The pseudo-instruction `assert' is used as a no-op pseudo-instruction that
;;; holds structures used during optimizations.  The emitter for this
;;; instruction should simply return.

;;;   ASSERT(<info for optimizations>)

(declare-optimizer-stack-instruction assert)

(def-pseudo-instruction-byte-code-emitter assert
  (declare (ignore instruction byte-code-stream))
  nil)


;;; `SIGNAL-ERROR-NEW p-code instruction' takes an expressions
;;; returning an error object, and will signal an error with that object

;;;   (SIGNAL-ERROR-NEW error-object-expression)
;;; ajs (5/29/96)

(declare-instruction-for-optimizer
  'signal-error-new
  '(return-flow))

(def-pseudo-instruction-byte-code-emitter signal-error-new
  (emit-stack-node-tree byte-code-stream (second instruction))
  (emit-instruction-byte-code byte-code-stream 'signal-error-new))

;;; `ANNOTATION annotation' is used to indicate annotation info for the
;;; following instructions.  For now this is line number and position info in
;;; the source.  It is essentially a no-op. -dkuznick, 1/12/99

;; If necessary, do a declare-instruction-for-optimizer.
(declare-optimizer-stack-instruction annotation)

(def-pseudo-instruction-byte-code-emitter annotation
  (let ((annotation? (cadr instruction)))
    (when annotation?	;some annotations are NIL.  We MAY want to take advantage of this info later.
      ;; This list will need to be reversed right before it's put into the byte-code-cody
      (phrase-push (phrase-list (byte-code-stream-address byte-code-stream)
				(begin-line annotation?)
				(begin-char-pos annotation?))
		   (byte-code-stream-text-position-information? byte-code-stream))))
  nil)

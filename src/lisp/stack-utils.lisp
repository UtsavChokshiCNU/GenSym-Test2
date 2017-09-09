;;; -*- Mode: LISP; Syntax: Common-Lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module STACK-UTILS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All rights reserved.

;;; Jim Allard and Chris Morel






;;;; Forward References




;;; In STACK-KERN

(declare-forward-reference stack-eval-for-execute-computation-instance function)

;;; In STACK-EVAL

(declare-forward-reference pprint-infix-evaluator function)

(declare-forward-reference pprint-functional-evaluator function)

;;; In G2-BPEL

(declare-forward-reference g2gl-call-invocation-p-function function)
(declare-forward-reference calling-process-of-g2gl-call-invocation function)

;; In PROC-UTILS
(declare-forward-reference get-byte-code-body-if-any function)


;;;; The Stack Evaluator




;;; The stack evaluator is a new implementation of the evaluators in G2.  This
;;; module unifies and replaces the separate evaluators in the inference engine,
;;; procedures, and the simulator.  The reasons for this re-implementation are
;;; to increase run-time speed, decrease code size, simplify code maintenance,
;;; simplify evaluator defining forms, and change from "special form" style
;;; evaluation to lisp-like EVAL semantics.

;;; The run-time speed has been increased by dispatching to the evaluator more
;;; quickly without any function calls, not computing expiration values where
;;; it's not necessary, returning only one value from evaluators, adding type
;;; specific operations for numeric operators, and using a simple vector as a
;;; stack for returning values, rather than using function calls and the Lisp
;;; stack.

;;; Code size is decreased and code maintenance is simplified by unifying the
;;; three types of evaluators and abstracting argument evaluation code and error
;;; handling outside of the evaluators.  Compiled code memory requirements are
;;; reduced by storing instructions as 1 byte elements of an (unsigned-byte 8)
;;; array.  Instructions can take arguments as bytes in the instruction stream.
;;; Pointers to code constant objects will be kept within a seperate code
;;; constant simple vector, using 1 or 2 byte indexes from the instruction
;;; vector to refer to them.

;;; The software definition of evaluators is simpler because the evaluation of
;;; the arguments and much of the error handling for the arguments occur before
;;; the evaluator is called.  The vast majority of the evaluators do not deal
;;; with expiration times of values and only return one value or signal an
;;; error.  The error handling is similar to procedures in that a throw (or go
;;; to) is performed.

;;; There will be two types of evaluators: in-line and funcalled.  The in-line
;;; evaluators will be implemented as stack machine instructions and will be
;;; executed as code which has been inserted directly in-line into the
;;; stack-eval function.  These instructions will be dispatched to without a
;;; single function call, and so can be very fast.  By the same token they
;;; should be very small so that the stack-eval function doesn't bloat into
;;; something too big to execute efficiently.  The funcalled, or out-of-line,
;;; evaluators will be executed as function calls.  They will be implemented as
;;; a single in-line stack machine instruction which dispatches to a
;;; compiled-function pointer stored in a simple-vector.

;;; Note that the arguments and return value of in-line evaluators are on the
;;; stack.  These values are, therefore, evaluation values.  Funcalled
;;; evaluators are passed their arguments as evaluation-value values.  These
;;; values must not be reclaimed.  Arguments and return value evaluation-values
;;; of the funcalled evaluators are managed in the instruction that does the
;;; funcall.






;;;; Evaluator Descriptions




;;; The function `make-evaluator-description' is a function used at load time to
;;; create evaluator descriptions being placed into the in-line-evaluator-array
;;; and the funcalled-evaluator-array.  It takes an evaluator name (a symbol
;;; returned by the parser naming this operation), and instruction name (which
;;; may be the same symbol as the evaluator name), a list of the environments in
;;; which the evaluator is allowed to run (environment names are inference,
;;; procedure, simulator), a list of the argument types taken by the evaluator,
;;; a symbol which is the type returned by the evaluator, a symbol which names
;;; the function that prints this evaluator, a symbol which names the function
;;; or macro that implements this evaluator, an in-line?  flag, and an in-line
;;; or funcalled evaluator number.  This function should only be called at load
;;; time as new evaluators are being defined.  Note that pointers to the given
;;; lists and symbols will be retained by the data structure created by this
;;; function.

(declare-side-effect-free-function make-evaluator-description)

(defun make-evaluator-description
       (evaluator-name instruction-name evaluator-instruction-precedence
        environments arguments result-type printer-function
        implementation-function-or-macro-name in-line? evaluator-number
        result-in-register-1? pprinter-function function-name?)
  (let ((new-description (make-array 15))        ; Always called from top level.
        (converted-arguments arguments)
        (converted-result-type result-type))
    (setf (evaluator-name new-description) evaluator-name)
    (setf (instruction-name new-description) instruction-name)
    (setf (evaluator-instruction-precedence new-description)
          evaluator-instruction-precedence)
    (setf (evaluator-environments new-description)
          (if (eq environments 'all)
              '(inference procedure simulator)
              environments))
    (setf (evaluator-arguments new-description) converted-arguments)
    (setf (evaluator-result-type new-description) converted-result-type)
    (setf (evaluator-printer-function new-description) printer-function)
    (setf (evaluator-function-or-macro-name new-description)
          implementation-function-or-macro-name)
    (setf (evaluator-in-line-p new-description) in-line?)
    (setf (evaluator-number new-description) evaluator-number)
    (setf (evaluator-result-in-register-1? new-description)
          result-in-register-1?)
    (setf (evaluator-pprinter-function new-description)
          pprinter-function)
    (setf (evaluator-function-name new-description) function-name?)
    new-description))




;;; The function `register-in-line-evaluator' is used to store evaluator
;;; description information registered with a particular in-line instruction
;;; number.  The function `register-funcalled-evaluator' stores
;;; evaluator-descriptions for funcalled (out-of-line) evaluators.  This
;;; function is called at the top level of files which define evaluators.

;; This function was modified to not "normalize" the evaluator instruction
;; number during registration.  The normalized number is now part of the in-line
;; evaluator definition.  To get the actual stack instruction number, the
;; base-in-line-evaluator-number is added to this normalized number.
;; Previously, the actual stack instruction number was used in the in-line
;; evaluator definition and the registration subtracted the base.  This change
;; was made so that we can easily move the starting number of all in-line
;; evaluators when necessary.  - cpm, 3/6/91.

(defun register-in-line-evaluator
       (evaluator-description evaluator-instruction-number)
  (when (or (<f evaluator-instruction-number 0)
            (>=f evaluator-instruction-number
                 (+f maximum-number-of-in-line-evaluators maximum-number-of-extended-inline-evaluators)))
    (error "In-line evaluator number ~a above maximum for ~a."
           evaluator-instruction-number
           (evaluator-name evaluator-description)))
	;added by SoftServe
	(when (=f evaluator-instruction-number dispatch-instruction-number)
		(error "Evaluator instruction number collides with dispatch instruction number"))
	;end of changes	
    (let ((old-description
            (svref in-line-evaluator-array evaluator-instruction-number)))
      (when (and old-description
                 (neq (instruction-name old-description)
                      (instruction-name evaluator-description)))
        (warn "In-line evaluator #~a changing from ~a to ~a."
              evaluator-instruction-number
              (instruction-name old-description)
              (instruction-name evaluator-description))))
    (setf (svref in-line-evaluator-array evaluator-instruction-number)
          evaluator-description)
    (loop with new-instruction-name = (instruction-name evaluator-description)
          for old-description-cons on
              (stack-evaluators (evaluator-name evaluator-description))
          do
      (when (eq (instruction-name (car old-description-cons))
                new-instruction-name)
        (when (/=f (evaluator-number (car old-description-cons))
                   (evaluator-number evaluator-description))
          (warn "In-line evaluator ~a changing from #~a to #~a."
                new-instruction-name
                (evaluator-number (car old-description-cons))
                (evaluator-number evaluator-description)))
        (setf (car old-description-cons) evaluator-description)
        (return-from register-in-line-evaluator nil))
          finally
            (push evaluator-description
                  (stack-evaluators (evaluator-name evaluator-description)))))

(defun register-funcalled-evaluator
       (evaluator-description evaluator-number evaluator-dispatch-type)
  (when (or (<f evaluator-number 0)
            (>=f evaluator-number maximum-number-of-funcalled-evaluators))
    (error "Funcalled evaluator number ~a above maximum for ~a."
           evaluator-number (evaluator-name evaluator-description)))
  (let ((old-description (svref funcalled-evaluator-array evaluator-number)))
    (when (and old-description
               (neq (instruction-name old-description)
                    (instruction-name evaluator-description)))
      (warn "Funcalled evaluator #~a changing from ~a to ~a."
            evaluator-number
            (instruction-name old-description)
            (instruction-name evaluator-description))))
  (setf (svref funcalled-evaluator-functions evaluator-number)
        (evaluator-function-or-macro-name evaluator-description))
  (setf (svref funcalled-evaluator-dispatch-type evaluator-number)
        evaluator-dispatch-type)
  (setf (svref funcalled-evaluator-array evaluator-number)
        evaluator-description)
  (push evaluator-description
        (stack-evaluators (evaluator-name evaluator-description)))
  nil)




;;; The macro `in-line-evaluator-description-for-op-code' takes an op-code and
;;; returns the evaluator-description, if any, for the in-line evaluator which
;;; is implemented by the given op-code.

(defmacro in-line-evaluator-description-for-op-code (op-code)
  `(svref in-line-evaluator-array
          (-f ,op-code base-in-line-evaluator-number)))




;;; During implementation of the new evaluators we will use the
;;; def-new-evaluator macro to at least compile new definitions for evaluators
;;; which we have not placed in the in-line or funcalled groups.  These will be
;;; registered so as to have some kind of listing of them using the function
;;; `register-dummy-evaluator' in a list `dummy-evaluators-list'.

(defvar dummy-evaluators-list nil)

(defun register-dummy-evaluator (evaluator-description)
  (loop with new-evaluator-name = (evaluator-name evaluator-description)
        for old-description-cons on dummy-evaluators-list
        do
    (when (eq new-evaluator-name (evaluator-name (car old-description-cons)))
      (setf (car old-description-cons) evaluator-description)
      (return-from register-dummy-evaluator nil))
        finally
          (push evaluator-description dummy-evaluators-list)))





;;;; Variables and Descriptions for Funcall-Instruction Support




;;; The constant `maximum-number-of-funcalled-instructions' defines the maximum
;;; instruction number of funcalled-instructions.

(defconstant maximum-number-of-funcalled-instructions 100)



;;; The array `funcalled-instructions' contains the funcalled instruction
;;; descriptions.

;;; `Funcalled-instruction-functions' contains the funcalled function (pointer to
;;; the function, not the function name) for funcalled instructions.

(defvar funcalled-instructions
        (make-array-with-nils maximum-number-of-funcalled-instructions))

(defvar funcalled-instruction-functions
        (make-array-with-nils maximum-number-of-funcalled-instructions))



;;; The following macros access the elements of an funcalled-instruction
;;; description.  SETF may be used with this accessors to mutate the description
;;; slot value.  The macros are: `funcalled-instruction-name',
;;; `funcalled-instruction-number', `funcalled-instruction-environments',
;;; `funcalled-instruction-argument-count?', and
;;; `funcalled-instruction-printer-function'.

(defmacro funcalled-instruction-name (funcalled-instruction-description)
  `(svref ,funcalled-instruction-description 0))

(defmacro funcalled-instruction-number (funcalled-instruction-description)
  `(svref ,funcalled-instruction-description 1))

(defmacro funcalled-instruction-environments (funcalled-instruction-description)
  `(svref ,funcalled-instruction-description 2))

(defmacro funcalled-instruction-argument-count
          (funcalled-instruction-description)
  `(svref-with-inlining ,funcalled-instruction-description 3))

(defmacro funcalled-instruction-result-count
          (funcalled-instruction-description)
  `(svref-with-inlining ,funcalled-instruction-description 4))

(defmacro funcalled-instruction-printer-function
          (funcalled-instruction-description)
  `(svref ,funcalled-instruction-description 5))

(defmacro funcalled-instruction-function (funcalled-instruction-description)
  `(svref ,funcalled-instruction-description 6))

(defmacro funcalled-instruction-pprinter-function
          (funcalled-instruction-description)
  `(svref ,funcalled-instruction-description 7))

(defmacro funcalled-instruction-function-name
          (funcalled-instruction-description)
  `(svref-with-inlining ,funcalled-instruction-description 8))




;;; The global property `funcalled-instruction-description' relates
;;; stack-instruction name symbols with the funcalled stack-instruction
;;; description.

(def-global-property-name funcalled-instruction-description)




;;; The function `make-and-register-funcalled-instruction-description' is a
;;; function used at load time to create funcalled-instruction descriptions being
;;; placed into the funcalled instructions array.

;;; It takes as arguments an instruction name (which may be the same symbol as the
;;; evaluator name), a funcalled-instruction number (which is different from stack
;;; instruction-numbers), a list of the environments in which the evaluator is
;;; allowed to run (environment names are inference, procedure, simulator), an
;;; argument count (which is the number of stack arguments accessed by this
;;; instruction), a symbol which names the function that prints this evaluator.

;;; This function should only be called at load time as new funcalled-instructions
;;; are being defined.  Note that pointers to the given lists and symbols will be
;;; retained by the data structure created by this function.

(defun make-and-register-funcalled-instruction-description
       (name instruction-number environments argument-count result-count
        implementation-function printer? pprinter? function-name)
  (let ((description (with-permanent-allocation (make-array 9))))
    (setf (funcalled-instruction-name description) name)
    (setf (funcalled-instruction-number description) instruction-number)
    (setf (funcalled-instruction-environments description)
          (if (eq environments 'all)
              '(inference procedure simulator)
              environments))
    (setf (funcalled-instruction-argument-count description) argument-count)
    (setf (funcalled-instruction-result-count description) result-count)
    (setf (funcalled-instruction-function description) implementation-function)
    (setf (funcalled-instruction-printer-function description) printer?)
    (setf (funcalled-instruction-pprinter-function description) pprinter?)
    (setf (funcalled-instruction-function-name description) function-name)

    (let ((old-description? (svref funcalled-instructions instruction-number)))
      (when (and old-description?
                 (neq (funcalled-instruction-name old-description?)
                      name))
        (warn
          "Funcalled-instruction #~a changing from ~a to ~a."
          instruction-number
          (funcalled-instruction-name old-description?)
          name))

      (setf (svref funcalled-instructions instruction-number) description)
      (setf (svref funcalled-instruction-functions instruction-number)
            implementation-function)
      (setf (funcalled-instruction-description name) description)
      nil)))






;;;; Funcalled-Evaluator Dispatch Types

;;; The funcalled-evaluator dispatch types are constants used in the definition
;;; and dispatch of funcalled-evaluators.  These values specify the number of
;;; item or evaluation-value arguments.  Note that it is up to the funcalled-
;;; evaluator to reference evaluation-value-values and to reclaim evaluation-
;;; values, as necessary.

(defconstant funcall-eval-type-0-arg 0)
(defconstant funcall-eval-type-1-arg 1)
(defconstant funcall-eval-type-2-arg 2)
(defconstant funcall-eval-type-3-arg 3)
(defconstant funcall-eval-type-4-arg 4)
(defconstant funcall-eval-type-5-arg 5)
(defconstant funcall-eval-type-6-arg 6)
;[tam.srogatch][2010-11-23]: We need a KB-level function with 8 arguments
(defconstant funcall-eval-type-7-arg 7)
(defconstant funcall-eval-type-8-arg 8)





;;;; The Stack Evaluator Stack




;;; The variable `global-stack' is used to hold an allocated stack in-between
;;; executions of the stack-eval function.

;;; Note that there is an issue about the size of the global stack and the
;;; recursion-limit system table parameter.  This stack should be made large
;;; enough that there is no possibility that the user can overflow it given that
;;; he stays within the recursion limit.  If the recursion limit is exceeded
;;; then a level one error should occur.

;;; But how to get a size for this stack?  Given a recursion limit and a maximum
;;; stack frame size, then a size for this vector can be determined.  But how to
;;; get maximum stack frame size?  One approach is to compute the maximum stack
;;; frame size for all compiled things which use the stack.  Another way is to
;;; impose a maximum and not allow anything to be compiled which attempts to use
;;; more.  Both of these choices mean something weird can occur when a user
;;; tries to compile.

;;; Say that no maximum is imposed on the stack frame size.  When a user
;;; compiles an item, if its stack frame size is so large that the recursion
;;; limit cannot be guaranteed safe, then we could mark that compiled thing as
;;; bad until either it was rewritten to reduce the stack size, or until the
;;; recursion limit was decreased.  Until that was done, the stack would be
;;; endangered by this compiled thing.  If a maximum stack frame size is
;;; imposed, then the user's only alternative would have to be to rewrite the
;;; compiled expressions to use less stack space.  I can almost hear Amber's
;;; phone ringing as I think about either of these alternatives.

;;; For the moment, I'll choose the imposed maximum stack frame size approach
;;; since it is easier to implement.  However, it would be great to change this
;;; to the no imposed maximum approach and design a set of messages for the user
;;; which would be understandable.  Another possibility it so resize the stack
;;; given a bigger maximum stack frame size or recursion limit, but even this
;;; must have some limit.  If it does have a limit, we should just allocate a
;;; stack that is that size to start with and push back on the recursion limit
;;; and the maximum stack frame size.  -jra 10/25/90

;;; Given all these ruminations above, nothing was actually done, and I now have
;;; a bug because a G2 gets corrupted when someone does overflow the stack.  So,
;;; what will be done now is to check that there is room for the maximum sized
;;; stack frame on entry to a function.  If the user is within that limit of the
;;; stack limit, an error will be signaled.  -jra 1/14/92

;;; The `global-stack-size' is 8K (8192), the initial recursion-limit is 50
;;; (found in the file SETS), and the `maximum-stack-frame-size' is 350.

(defconstant global-stack-size 8192)

(def-system-variable global-stack utilities0 ; should be stack-utils?
  (:funcall make-global-stack))

(defun make-global-stack ()
  (with-permanent-array-creation (make-array global-stack-size)))

(def-system-variable free-global-stacks stack-utils nil)

(defmacro with-global-stack (&rest body)
  `(let ((global-stack (or (gensym-pop free-global-stacks)
                           (make-global-stack))))
     (prog1 (progn ,@body)
       (gensym-push global-stack free-global-stacks))))

(defconstant maximum-stack-frame-size 350)





;;;; Debugging Stack Instructions




;;; Since stack instructions and in-line evaluators are macros which are never
;;; used until the macro expansion and compile of stack-eval, it can be very
;;; difficult to relate compile time bugs in stack eval back to individual
;;; instructions.  To help fix this problem, during development a function will
;;; be defined per instruction which includes the macro-expansion of the
;;; instruction.

;;; The macro `stack-eval-locals' defines all local variables available in
;;; stack-eval for use in instructions.  This macro is used in the development
;;; time dummy functions for instructions, and by stack-eval itself.

(defparameter stack-eval-locals-bindings
  '((instruction-vector (byte-code-body-byte-vector byte-code-body))
    (local-stack global-stack)
    (top-of-stack initial-top-of-stack)
    (stack-frame-base initial-stack-frame-base)
    (stack-program-counter initial-program-counter)
    (instruction-count 0)
    (byte-instruction 0)
    (local-truth-threshold (truth-threshold inference-engine-parameters))
    (detailed-tracing? nil)
    (major-tracing? nil)
    (register-1 nil)
    (register-2 nil)
    (register-3 nil)
    (register-4 nil)
    (register-5 nil)
    (fixnum-register-1 0)
    (fixnum-register-2 0)
    (recursion-depth initial-recursion-depth)
    (float-register-1 0.0)
    (float-register-2 0.0)))

(defmacro stack-eval-locals (&body forms)
  `(let* ,stack-eval-locals-bindings
     (declare (simple-vector local-stack)
              (fixnum top-of-stack stack-frame-base stack-program-counter
                      instruction-count
                      local-truth-threshold fixnum-register-1 fixnum-register-2
                      recursion-depth)
              (type (unsigned-byte 8) byte-instruction)
              (type gensym-float float-register-1 float-register-2))
     ,@forms))




;;; The development only macro `dummy-stack-eval-references' is used in the dummy
;;; functions for stack instructions to include a reference to all local
;;; variables, so that "unused variable" warnings won't show up there.

#+development
(defmacro dummy-stack-eval-references ()
  '(dummy-stack-eval-var-ref-function
     instruction-vector
     constant-vector
     local-var-vector
;     fixnum-start-time
     fixnum-time-limit?
     local-stack
     top-of-stack
     stack-frame-base
     stack-program-counter
;     current-program-counter
     instruction-count
     byte-instruction
     local-truth-threshold
     detailed-tracing?
     major-tracing?
     register-1
     register-2
     register-3
     register-4
     register-5
     fixnum-register-1
     fixnum-register-2
     recursion-depth
     float-register-1
     float-register-2))

#+development
(defun dummy-stack-eval-var-ref-function
       (instruction-vector constant-vector local-var-vector
;        fixnum-start-time
        fixnum-time-limit?
        local-stack top-of-stack stack-frame-base
        instruction-count stack-program-counter
;        current-program-counter
        byte-instruction local-truth-threshold
        detailed-tracing? major-tracing?
        register-1 register-2 register-3 register-4 register-5
        fixnum-register-1 fixnum-register-2 recursion-depth
        float-register-1 float-register-2)
  (declare (ignore
             instruction-vector constant-vector local-var-vector
;             fixnum-start-time
             fixnum-time-limit?
             local-stack top-of-stack stack-frame-base
             instruction-count stack-program-counter
;             current-program-counter
             byte-instruction local-truth-threshold
             detailed-tracing? major-tracing?
             register-1 register-2 register-3 register-4 register-5
             fixnum-register-1 fixnum-register-2
             recursion-depth float-register-1 float-register-2))
  nil)




;;; The function `print-stack-node-tree' is a development only printer for the
;;; trees of stack nodes and stack node instructions produced by the stack
;;; compiler.

#+development
(defun print-stack-node-tree (stack-node &optional (indent-level 0))
  (let ((*print-length* 0)
        (*print-level* 0)
        (lines
          (gensym-cons
            (twith-output-to-text-string
              (twrite-n-spaces (*f indent-level 2))
              (tformat "~a ~(~a~), ~(~a~) val = ~NT, reqd = ~NT"
                       stack-node
                       (stack-node-operation stack-node)
                       (and (stack-node-chosen-evaluator stack-node)
                            (instruction-name
                              (stack-node-chosen-evaluator stack-node)))
                       (stack-node-value-type stack-node)
                       (stack-node-required-value-type stack-node)))
            (gensym-cons
              (twith-output-to-text-string
                (twrite-n-spaces (*f (+f indent-level 2) 2))
                (tformat "~(~a~) node, ~(~a~) tree"
                         (stack-node-type stack-node)
                         (stack-node-tree-type stack-node)))
              (when (and (stack-node-instruction-p stack-node)
                         (stack-node-instruction-extra-info stack-node))
                (let ((extra (stack-node-instruction-extra-info stack-node)))
                  (gensym-list
                    (twith-output-to-text-string
                      (twrite-n-spaces (*f (+f indent-level 2) 2))
                      (if (evaluation-value-p-function extra)
                          (tformat "extra-val = ~NV" extra)
                          (tformat "extra-inf = ~a" extra))))))))))
    (loop for line in lines do
      (terpri)
      (princ line)
      (reclaim-text-string line))
    (reclaim-gensym-list lines)
    (loop with new-level = (+f indent-level 1)
          for arg-node in (stack-node-argument-nodes stack-node)
          do
      (print-stack-node-tree arg-node new-level))))

#+development
(defun pprint-stack-node-tree (stack-node indent-level)
  (loop repeat indent-level do (format t "    "))
  (format t "~((~a) ~A~)("
          (stack-node-value-type stack-node)
          (if (stack-node-chosen-evaluator stack-node)
              (instruction-name
                (stack-node-chosen-evaluator stack-node))
              (stack-node-operation stack-node)))
  (loop for first = t then nil
        for arg in (stack-node-argument-nodes stack-node)
        do
    (unless first
      (format t ","))
    (terpri)
    (pprint-stack-node-tree arg (1+f indent-level)))
  (cond ((stack-node-instruction-p stack-node)
         (when (stack-node-argument-nodes stack-node)
           (format t ","))
         (terpri)
         (loop repeat (1+f indent-level) do (format t "    "))
         (format t "~(~a~))"
                 (if (evaluation-value-p (stack-node-instruction-extra-info
                                           stack-node))
                     (twith-output-to-gensym-string
                       (write-evaluation-value
                         (stack-node-instruction-extra-info stack-node) t))
                     (stack-node-instruction-extra-info stack-node))))
        (t
         (format t ")"))))

#+development
(defun pprint-pseudo-instruction (instruction)
  (format t "~(~a~)" (car instruction))
  (loop for arg in (cdr instruction) do
    (format t "~%")
    (if (or (stack-node-p arg) (stack-node-instruction-p arg))
        (pprint-stack-node-tree arg 1)
        (format t "    ~(~a~)" arg)))
  (format t ";"))

#+development
(defun pprint-pseudo-instructions (pseudo-instructions)
  (loop for instruction in pseudo-instructions do
    (pprint-pseudo-instruction instruction)
    (terpri)))








;;;; Evaluator Defining Forms




;;; The macro `def-in-line-evaluator' is used to define new evaluator functions.
;;; The arguments to the macro are the name of the evaluator, an optional
;;; evaluator precedence, specifiers for the environment, argument types, return
;;; type, an optional flag which indicates if the result will be in register-1,
;;; and the body of the evaluator.

;;; The environment specifier is the symbol ALL or a list of any of INFERENCE,
;;; PROCEDURE, and SIMULATOR.  It specifies the computation environments in
;;; which this operation is valid.  This information is used at compile time.

;;; The types in the argument and return type specifiers should be type
;;; specifications.  The typical ones are SYMBOL, TEXT, TRUTH-VALUE, QUANTITY,
;;; INTEGER, or FLOAT; a list containing the symbols CLASS and an other symbol
;;; naming a class, which means an instance of that class; the type
;;; specification DATUM, which means any of the data types; or the symbol
;;; ITEM-OR-DATUM, which accepts any instance of item or any datum.

;;; The arguments contain evaluation-values and should be referenced within the
;;; body with the following macro form.
;;;     (stack-arg <argument number>)
;;; The count to arg is zero based (i.e., the first argument is (stack-arg 0)).
;;; Note that this is guaranteed to return a value of the declared type for that
;;; argument position.

;;; The value of the evaluator form must be left in register-1 if that optional
;;; argument is non-NIL.  Otherwise, the value of the evaluator form is the
;;; value of the last form of the body of the evaluator.  The return value must
;;; match the type declared in the evaluator definition and must be an
;;; evaluation-value.

;;; Errors should be signaled with the form
;;;     (eval-error <error-level> <tformat args> ...) or
;;;     (write-eval-error <error-level>
;;;         <twriting forms>)

;;; Evaluators can not be defined to have optional arguments.  Therefore, when
;;; an operator can have varying number and type of arguments, a separate
;;; evaluator should be defined for each set of arguments.

;;; Evaluators can not have an unlimited number of arguments (ie., an &rest
;;; format).  The evaluator for an operator, such as "+", which can receive two
;;; or more operands, should be written to handle two arguments.  If the operand
;;; has more than two arguments, the compiler will produce the correct number of
;;; calls to the evaluator passing only two values, the appropriate argument and
;;; the incremental result.

;; This function was modified to pass the evaluator-number plus the
;; base-in-line-evaluator-number to make-evaluation-description.  This change is
;; needed since the "normalized" evaluator number is now used in the definition
;; of the in-line stack-evaluator.  The number is no longer normalized during
;; registration of the in-line evaluator.  See the comments for
;; register-in-line-evaluator.  - cpm, 3/6/91

;; all in-line-evaluators are automatically optimizer stack instructions --rdf

(defmacro def-in-line-evaluator
          (name-or-evaluator-name-instruction-name-and-precedence
           (instruction-number
             environments arg-types result-type
             &optional result-in-register-1? pprinter?)
           &body body)
  (unless (or (and (symbolp environments)
                   (eq environments 'all))
              (and (consp environments)
                   (not (loop for environment in environments
                              thereis
                                (not (memq environment
                                           '(inference procedure
                                                       simulator)))))))
    (error "In-line environments argument malformed for ~a."
           name-or-evaluator-name-instruction-name-and-precedence))
  ;; Insert code to check arg-types and return-type.
  (let* ((evaluator-name
           (if (symbolp name-or-evaluator-name-instruction-name-and-precedence)
               name-or-evaluator-name-instruction-name-and-precedence
               (first name-or-evaluator-name-instruction-name-and-precedence)))
         (instruction-name
           (if (symbolp name-or-evaluator-name-instruction-name-and-precedence)
               name-or-evaluator-name-instruction-name-and-precedence
               (second name-or-evaluator-name-instruction-name-and-precedence)))
         (instruction-precedence
           (if (symbolp name-or-evaluator-name-instruction-name-and-precedence)
               1
               (or (third name-or-evaluator-name-instruction-name-and-precedence)
                   1)))
         (evaluator-macro
           (intern (format nil "EVAL-~a-IN-LINE" instruction-name)))
         (dummy-function (intern (format nil "EVAL-~A-DEBUG" instruction-name)))
         (arg-count (length arg-types))
         (arg-count-minus-one (-f arg-count 1)))
    (when (<f 0 arg-count)
      (loop for i from 0 to arg-count-minus-one
            for offset = (-f arg-count-minus-one i)
            for new = (if (=f i arg-count-minus-one)
                          `(svref local-stack top-of-stack)
                          `(svref local-stack (-f top-of-stack ,offset)))
            do (setq body (subst new
                                 `(stack-arg ,i)
                                 body
                                 :test 'equal))))
    (check-instruction-precedence instruction-precedence instruction-name)
    `(progn
       ,@(if (not (eval-feature :no-macros))
             `((defmacro ,evaluator-macro ()
                 '(progn ,@body))))
       ,@(if (and (not (eval-feature :no-macros))
                  (eval-feature :development))
             `((defun ,dummy-function
                      (byte-code-body constant-vector local-var-vector
                       fixnum-time-limit? initial-program-counter
                       initial-top-of-stack initial-stack-frame-base
                       initial-recursion-depth)
                 (stack-eval-locals
                   (tagbody
                       (dummy-stack-eval-references)
                       (,evaluator-macro)
                       (go exit-stack-eval)
                    exit-stack-eval))
                 nil)))
       (declare-optimizer-stack-instruction ,evaluator-name)
       (register-in-line-evaluator
         (make-evaluator-description
           ',evaluator-name ',instruction-name ,instruction-precedence
           ',environments ',arg-types ',result-type nil
           ',evaluator-macro
           t
           (+f base-in-line-evaluator-number ,instruction-number)
           ,result-in-register-1?
           ,(if pprinter?
                `#',pprinter?
                nil)
           nil)
         ,instruction-number)
       ',evaluator-macro)))




;;; The macro `stack-arg-of-stack-count' is used to access the stack when the
;;; arg count of the stack is not known until runtime.  Both args are evaluated.
;;; See other macros, such as the macro-let "arg", which call
;;; expand-in-line-stack-arg, for a more optimized reference to stack-args.

(defmacro stack-arg-of-stack-count (arg-number arg-count)
  `(svref local-stack (-f top-of-stack (-f ,arg-count ,arg-number 1))))

(defun-for-macro expand-in-line-stack-arg (arg-number arg-count-minus-one)
  (when (>f arg-number arg-count-minus-one)
    (error
      "This evaluator takes only ~a args, referenced #~a."
      (+f arg-count-minus-one 1)
      arg-number))
  `(svref local-stack
          ,(if (=f arg-number arg-count-minus-one)
               'top-of-stack
               `(-f top-of-stack
                    ,(- arg-count-minus-one arg-number)))))

(defun-for-macro check-instruction-precedence
                 (instruction-precedence instruction-name)
  (unless (fixnump instruction-precedence)
    (error "Bad instruction precedence for ~a, must be a fixnum, was ~a."
           instruction-name
           instruction-precedence)))






;;; The macro `def-funcalled-evaluator' is used to define new funcalled
;;; evaluator functions.  The arguments to this macro are the name of the
;;; evaluator, optional instruction precedence, function argument names,
;;; funcalled evaluator number, specifiers for the environment, argument types,
;;; return type, dispatch type, optional form-writer, and the body of the
;;; evaluator.

;;; See def-in-line-evaluator for documentation on the environment specifier,
;;; argument types, and return types.

;;; The arguments should be referenced within the body with the argument names
;;; provided in the definition.  Evaluators can not be defined to have optional
;;; arguments.  Note that in version 3.0, arguments were evaluation-value values
;;; and therefore were not to be reclaimed or referenced after a call to the
;;; evaluator.  As of version 4.0, the argument dispatch has been rewritten to
;;; pass evaluation-value or item arguments.  The funcalled-evaluators,
;;; therefore, should reference the evaluation-value-value and reclaim these
;;; evaluation-values, when necessary.

;;; The value of the evaluator form is the value of the last form of the body of
;;; the evaluator.  This value must match the type declared in the evaluator
;;; definition.  The return value is an evaluation-value.

;;; Errors should be signaled with the form
;;;     (eval-error <error-level> <tformat args> ...) or
;;;     (write-eval-error <error-level>
;;;         <twriting forms>)

(defmacro def-funcalled-evaluator
          (name-or-evaluator-name-instruction-name-and-precedence function-arguments
           (funcalled-number environments arg-types result-type
                             funcalled-dispatch-type &optional form-writer pprinter)
           &body body)
  (let* ((evaluator-name
           (if (symbolp name-or-evaluator-name-instruction-name-and-precedence)
               name-or-evaluator-name-instruction-name-and-precedence
               (car name-or-evaluator-name-instruction-name-and-precedence)))
         (instruction-name
           (if (symbolp name-or-evaluator-name-instruction-name-and-precedence)
               name-or-evaluator-name-instruction-name-and-precedence
               (second name-or-evaluator-name-instruction-name-and-precedence)))
         (instruction-precedence
           (if (symbolp name-or-evaluator-name-instruction-name-and-precedence)
               1
               (or (third name-or-evaluator-name-instruction-name-and-precedence)
                   1)))
         (evaluator-function
           (intern (format nil "EVAL-~a-FUNCALLED" instruction-name))))
    (check-instruction-precedence instruction-precedence instruction-name)
    `(progn
       (declare-optimizer-stack-instruction ,evaluator-name)
       (defun-simple ,evaluator-function ,function-arguments
         ,@body)
       (register-funcalled-evaluator
         (make-evaluator-description
           ',evaluator-name ',instruction-name ,instruction-precedence
           ',environments ',arg-types ',result-type ',form-writer
           #',evaluator-function nil ,funcalled-number nil
           ,(if pprinter
                `#',pprinter
                nil)
           ',evaluator-function)
         ,funcalled-number ,funcalled-dispatch-type)
       ',evaluator-function)))




;;; The variable `float-contagion-stack-operators' contains a list of the stack
;;; operators that do floating point contagion when given mixed float and integer
;;; arguments.  The integer arguments are coerced to floats before performing the
;;; operation.

(defvar float-contagion-stack-operators nil)


;;; The macro `def-float-contagion-stack-operator' specifies that a stack operator
;;; uses floating point contagion when passed both integer and float arguments.
;;; This information is used during the compilation of stack expressions.

;;; This is a non-standard macro that does not evaluate its argument.

(defmacro def-float-contagion-stack-operator (operator)
  `(pushnew ',operator float-contagion-stack-operators))


;;; The function `float-contagion-stack-operator-p' is used to test whether a
;;; stack-operator, such as +, performs float contagion on its arguments.

(defun float-contagion-stack-operator-p (stack-operator)
  (memq stack-operator float-contagion-stack-operators))

;;;; Funcalled-Instruction Defining Forms




;;; The macro `def-funcalled-instruction' is used to define new funcalled
;;; instructions.  The arguments to this macro are: the name of the evaluator, the
;;; funcalled-instruction number, specifiers for the environment, argument count,
;;; form-writer, and the body of the evaluator.

;;; The environment specifier is the symbol ALL or a list of any of INFERENCE,
;;; PROCEDURE, and SIMULATOR.  It specifies the computation environments in
;;; which this operation is valid.  This information is used at compile time.

;;; The arguments passed to a funcalled-instruction are top-of-stack and
;;; local-stack.  Arguments on the stack should be referenced using the
;;; stack-arg macro which references these two arguments.  Stack arguments
;;; should be reclaimed and cleared by the funcalled-instruction as necessary.

;;; The value of the funcalled-instruction form is the value of the last form of
;;; the body of the instruction and must be the new top-of-stack.

;;; Errors should be signaled with the form
;;;     (eval-error <error-level> <tformat args> ...) or
;;;     (write-eval-error <error-level>
;;;         <twriting forms>)

(defmacro def-funcalled-instruction
          (instruction-name
           (instruction-number environments arg-count result-count
                               &optional printer? pprinter?)
           &body body)
                                                       ; Abstract this.  cpm, 6/17/91
  (unless (or (and (symbolp environments)
                   (eq environments 'all))
              (and (consp environments)
                   (not (loop for environment in environments
                              thereis
                                (not (memq environment
                                           '(inference procedure
                                                       simulator)))))))
    (error "Funcalled instruction environments argument malformed for ~a."
           instruction-name))

  (let* ((instruction-function
           (intern (format nil "FUNCALL-~a-INST" instruction-name)))
         (arg-count-minus-one (1-f (cond ((fixnump arg-count)
                                          arg-count)
                                         ((equal arg-count '(0))
                                          1)
                                         (t ; (+ (0) n)
                                          (third arg-count)))))
         (declarations
           (loop for statement in body
                 while (and (consp statement) (eq (car statement) 'declare))
                 collect statement))
         (actual-body (nthcdr (length declarations) body)))
    `(progn
       (defun-simple ,instruction-function (top-of-stack local-stack)
         ,@declarations
         (macrolet ((stack-arg (stack-argument-number)
                      (expand-in-line-stack-arg
                        stack-argument-number ,arg-count-minus-one)))
           ,@actual-body))
       (make-and-register-funcalled-instruction-description
         ',instruction-name ,instruction-number ',environments
         ',arg-count ',result-count
         #',instruction-function ',printer?
         ,(if pprinter?
              `#',pprinter?
              nil)
         ',instruction-function))))






;;;; Stack Instruction Definition Utilities




;;; The macro `stack-arg-macro' is used to access a numbered reference to an
;;; argument of a stack instruction, when there are variable numbers of
;;; arguments to an instruction.  If the number of arguments to an instruction
;;; is fixed, you should use the ARG macro.  This macro takes a zero-based
;;; arg-number, and a second argument which is the total count of arguments for
;;; this instruction minus one.

;; Note:  An attempt was made to optimize this macro for the translation of the
;; stack-eval function in Chestnut.  The approach was to compute the fixnum
;; stack index number, put it into a fixnum-register, and then call svref.  This
;; turned out to be a poor choice, since more temporary variables got allocated
;; for stack-eval in this approach than had been in the first.  It has been
;; reverted to its simple form, and an attempt will be made to get Chestnut to
;; recognize side-effect free expressions.  -jra 1/20/91

(defmacro stack-arg-macro (arg-number arg-count-minus-one)
  (let ((arg arg-number)
        (arg-count arg-count-minus-one))
    (when (>f arg arg-count)
      (error
        "This evaluator takes only ~a args, referenced #~a."
        (+f arg-count 1) arg))
    (if (= arg arg-count)
        '(svref local-stack top-of-stack)
        `(svref local-stack (-f top-of-stack ,(- arg-count arg))))))




;;; The macro `arg' takes a fixnum and returns the numbered argument to an
;;; instruction.  (This macro will be defined as part of the expansion of
;;; stack-eval.)

;;; Note that there is an issue to be resolved here as to the ordering of
;;; arguments to instructions and functions on the stack.  If the zeroth
;;; argument to an instruction is at the top of the stack (making this argument
;;; fetch operation trivial to implement), then arguments must be pushed onto
;;; the stack evaluating from right to left.  At the moment the computational
;;; model of G2 guarantees "reference-perspective side-effect free expression
;;; evaluation".  This should make argument evaluation order irrelevant.
;;; However, in the future mutations of procedures, there is a possibility of
;;; implementing CALLS to procedures as expression sub-components.  Users who
;;; don't care about possible wait state problems or who can guarantee that
;;; their procedures are wait-state free would like this.  In this case, we do
;;; have to consider order of argument evaluation, and left to right would be
;;; nice.  If this is implemented, then the argument fetch operation needs to
;;; know the total number of arguments expected by an instruction, and index off
;;; the top-of-stack minus the total expected.

;;; Given this consideration, it is tempting to push the arguments onto the
;;; stack in normal forward argument order, with the zeroth argument buried in
;;; the stack, and the Nth argument at the top of the stack.  If the number of
;;; arguments for an instruction is known at macro-expand time of the
;;; instruction code into the stack-eval function (which is possible), then an
;;; automatic conversion could be done.  This might be able to be implemented
;;; using macrolet.  (Note that compiler-let has been removed from CLtL II.)

;;; On the other hand, implementors of instructions could be required to pop
;;; thier arguments off the stack in reverse order.

;;; On yet another hand, if the total number of arguments to an instruction is
;;; given as an extra argument to stack-instruction-arg, then the expansion of
;;; this macro could be performed without resorting to macrolet.

;;; For the moment, Chris is going ahead with instruction implementation where
;;; he refers to arguments in forward order, without passing the total number of
;;; arguments.  Onward macrolet!  -jra 11/2/90

;;; The macro `code-constant' takes a zero-based index and reads a byte from the
;;; instruction stream which is the indexed code constant for the currently
;;; executing instruction.

;;; NOTE!  This macro's execution is dependant on the stack-program-counter
;;; variable, and so must be run before any branching operations (i.e.  SETQs to
;;; stack-program-counter).

(defmacro code-constant (index)
  (if (constantp index)
      (let ((index-evaled (eval index)))
        (if (=f index-evaled 0)
            `(byte-vector-aref instruction-vector stack-program-counter)
            `(byte-vector-aref
               instruction-vector
               (+f stack-program-counter ,index-evaled))))
      `(byte-vector-aref
         instruction-vector
         (+f stack-program-counter ,index))))




;;; The macro `long-code-constant' takes a zero-based index to the first byte of
;;; a two byte code constant.  The code constant should be stored with the high
;;; byte as the first byte in the stream, and the low byte as the second.  This
;;; function then extracts a high byte and low byte from the instruction stream,
;;; adds them, and returns the constant.  Note that this macro is dependant on
;;; the stack-program-counter variable, and so must be run before any branching
;;; operations.  This macro can only be used within instruction definitions.

(defmacro long-code-constant (high-byte-index)
  (if (constantp high-byte-index)
      (let ((doubled-index (* (eval high-byte-index) 2)))
        (if (= doubled-index 0)
            `(+f (ashf (byte-vector-aref
                         instruction-vector stack-program-counter)
                       8)
                 (byte-vector-aref instruction-vector (+f stack-program-counter 1)))
            `(+f (ashf (byte-vector-aref
                         instruction-vector
                         (+f stack-program-counter ,doubled-index))
                       8)
                 (byte-vector-aref
                   instruction-vector
                   (+f stack-program-counter ,(+ doubled-index 1))))))
      `(long-code-constant-in-byte-vector
         instruction-vector
         (+f stack-program-counter (twicef ,high-byte-index)))))

(declare-side-effect-free-function long-code-constant-in-byte-vector)

(defun-simple long-code-constant-in-byte-vector (byte-vector index)
  (declare (type fixnum index))
  (+f (ashf (byte-vector-aref byte-vector index) 8)
      (byte-vector-aref byte-vector (+f index 1))))

(defsetf long-code-constant-in-byte-vector setf-long-code-constant)

(defun setf-long-code-constant (byte-vector index long-code-constant)
  (setf (byte-vector-aref byte-vector index)
        (ashf long-code-constant -8))
  (setf (byte-vector-aref byte-vector (+f index 1))
        (logandf long-code-constant 255))
  long-code-constant)

(defun emit-long-code-constant-to-stream (byte-code-stream constant)
  (write-byte-code-to-stream byte-code-stream (ashf constant -8))
  (write-byte-code-to-stream byte-code-stream (logandf constant 255))
  nil)




;;; The macro `relative-code-constant' takes a zero-based index to a code
;;; constant which has had 128 added to it before storage in the instruction
;;; stream.  This macro fetches the referenced constant, offsets it by 128, and
;;; returns the fixnum value.

(defmacro relative-code-constant (index)
  (if (and (constantp index) (= (eval index) 0))
      `(-f (byte-vector-aref instruction-vector stack-program-counter)
           128)
      `(-f (byte-vector-aref instruction-vector
                             (+f stack-program-counter ,index))
           128)))

(defun-simple relative-code-constant-in-byte-vector (byte-vector index)
  (declare (type fixnum index))
  (-f (byte-vector-aref byte-vector index) 128))

(defsetf relative-code-constant-in-byte-vector
         setf-relative-code-constant-in-byte-vector)

(defun setf-relative-code-constant-in-byte-vector (byte-vector index constant)
  (setf (byte-vector-aref byte-vector index) (+f constant 128))
  constant)

(defun-simple relative-code-constant-p (fixnum)
  (and (>=f fixnum -128)
       (<=f fixnum 127)))

(defun emit-relative-code-constant-to-stream (byte-code-stream constant)
  (write-byte-code-to-stream byte-code-stream (+f constant 128)))


;;; For efficiency, some instructions have different expansions for the
;;; byte-code interpreter and for the new C-emitting back end.

(defmacro if-emitting-c-code (compiler-form interpreter-form)
  (declare (ignore compiler-form))
  interpreter-form)

;;; for the compiler...
(defmacro funcall-simple-compiled-function-without-decaching
    (function arg1 arg2)
  `(funcall-simple-compiled-function ,function ,arg1 ,arg2))

;;; The global variable `stack-instructions' contains an array 300 elements
;;; long.  This array contains instruction-descriptions for all defined
;;; instructions.

(defconstant stack-instructions-count-in-g2 300)

(defvar stack-instructions (make-array-with-nils stack-instructions-count-in-g2))




;;; The following macros define accessors for stack-instruction-descriptions.
;;; The components of a stack instruction description are the `stack-
;;; instruction-name', `stack-instruction-argument-count?', `stack-instruction-
;;; printer?', `stack-instruction-number', and `stack-instruction-macro-name'.

(defmacro stack-instruction-marker-slot (simple-vector)
  `(svref ,simple-vector 0))

(defmacro stack-instruction-name (stack-instruction-description)
  `(svref ,stack-instruction-description 1))

(defmacro stack-instruction-byte-length (stack-instruction-description)
  `(svref ,stack-instruction-description 2))

(defmacro stack-instruction-argument-count? (stack-instruction-description)
  `(svref ,stack-instruction-description 3))

(defmacro stack-instruction-printer? (stack-instruction-description)
  `(svref ,stack-instruction-description 4))

(defmacro stack-instruction-number (stack-instruction-description)
  `(svref ,stack-instruction-description 5))

(defmacro stack-instruction-macro-name (stack-instruction-description)
  `(svref ,stack-instruction-description 6))

(defmacro stack-instruction-pprinter? (stack-instruction-description)
  `(svref ,stack-instruction-description 7))

(defmacro stack-instruction-expanded-body (stack-instruction-description)
  `(svref ,stack-instruction-description 8))




;;; The global property `instruction-description' relates stack-instruction name
;;; symbols with the stack-instruction description.

(def-global-property-name instruction-description)




;;; The function `make-and-register-stack-instruction-description' takes
;;; a name, length-in-bytes, argument-count?, printer?,
;;; instruction-number, and macro-name for a stack evaluator
;;; instruction.  This function makes a stack instruction description
;;; and registers it in the stack-instructions global array.

(defun make-and-register-stack-instruction-description
       (name length-in-bytes argument-count? printer?
        instruction-number macro-name pprinter?)
  (let ((description (with-permanent-allocation (make-array 9))))
    (setf (stack-instruction-marker-slot description) 'stack-instruction)
    (setf (stack-instruction-name description) name)
    (setf (stack-instruction-byte-length description) length-in-bytes)
    (setf (stack-instruction-argument-count? description) argument-count?)
    (setf (stack-instruction-printer? description) printer?)
    (setf (stack-instruction-number description) instruction-number)
    (setf (stack-instruction-macro-name description) macro-name)
    (setf (stack-instruction-pprinter? description) pprinter?)
    (let ((old-description (svref stack-instructions instruction-number)))
      (when (and old-description
                 (neq (stack-instruction-name old-description) name))
        (warn "Stack instruction #~a changing from ~a to ~a."
              instruction-number
              (stack-instruction-name old-description)
              name)))
    (setf (svref stack-instructions instruction-number)
          description)
    (setf (instruction-description name) description)
    nil))

(defun-simple stack-instruction-description-p (thing)
  (and (simple-vector-p thing)
       (>f (length (the simple-vector thing)) 0)
       (eq (stack-instruction-marker-slot thing) 'stack-instruction)))

;;;
;;; This C function is aimed to return the CPU cycles count since a system (PC) startup
;;;

(def-gensym-c-function c-get-cpu-ticks-count 
				(:fixnum-int "g2ext_get_cpu_ticks_count")
	())
	
(def-gensym-c-function c-get-tsc-difference 
				(:fixnum-int "g2ext_get_tsc_difference")
	((:fixnum-int cell-index-1) (:fixnum-int cell-index-2)))


(defun add-text-to-string-with-align
       (main-string string-to-append gap-length reclaim-main? reclaim-appendee?)
  (let* ((pad-line (make-stringw gap-length :initial-element #.%space))
	 (composed-line-1 (concatenate-text-strings main-string pad-line))
	 (composed-line (concatenate-text-strings composed-line-1 string-to-append)))
    (when reclaim-main?
      (reclaim-wide-string main-string))
    (when reclaim-appendee?
      (reclaim-wide-string string-to-append))
    (reclaim-wide-string pad-line)
    (reclaim-wide-string composed-line-1)
    composed-line))


;;; The macro `execute-stack-instruction' takes an integer from 0 through 255 as
;;; its first argument, and an unquoted symbol naming a go tag as its second
;;; argument.  This macro will execute the stack instruction for the given
;;; number and then branch back to the given tag.  Note that branch instructions
;;; to the tag are inserted after the body of every instruction to avoid the
;;; extra branch to the end of the CASE statement before actually branching the
;;; target tag.

;;; NOTE THAT THIS IS A NON-STANDARD MACRO.  If the instruction-number returned
;;; by the expression in the first argument does not denote an actual
;;; instruction, then the instruction expression will be evaluated a second time
;;; while printing the error message.  A second non-standard behavior is of
;;; course the go to a tag given as an argument.  A third thing to be aware of
;;; is that instructions which experience errors will perform throws to the
;;; :stack-error tag, leaving this form non-locally.

;; Note that this macro is emitting calls to fully check all arguments and
;; return values of in-line evaluators.  Typically this will only be done in
;; development, but during QA it will always be done.  Note that this is a HUGE
;; performance hog.  -jra & cpm 9/9/91

(defmacro execute-stack-instruction (instruction-number go-tag debuggable?)
  (declare (ignore debuggable?))
  (let* ((fully-check-values? (eval-feature :development))
         (instruction-case-clauses
           (loop for instruction-index from 0 below 256
                 for stack-instruction-description? =
                 (svref stack-instructions instruction-index)
                 when stack-instruction-description?
                   collect `((,instruction-index)
                             (,(stack-instruction-macro-name
                                 stack-instruction-description?))
                             (go ,go-tag))))
         (evaluator-case-clauses
           (loop for normalized-in-line-index
                 from 0
                     below maximum-number-of-in-line-evaluators
                 for description? =
                 (svref in-line-evaluator-array normalized-in-line-index)
                 for op-code = (when description?
                                 (evaluator-number description?))
                 when description?
                   collect
                   (let ((values-to-pop
                           (-f (length (evaluator-arguments description?)) 1))
                         (macro-name (evaluator-function-or-macro-name
                                       description?))
                         (value-left-in-register-1?
                           (evaluator-result-in-register-1? description?)))
                     (if (and (=f values-to-pop 0)
                              (null value-left-in-register-1?))
                         `((,op-code)
                           ,@(when fully-check-values?
                               `((progn-for-development
                                   (check-stack-evaluator-arguments
                                     ,op-code t local-stack top-of-stack))))
                           (setf (svref local-stack top-of-stack)
                                 (,macro-name))
                           ,@(when fully-check-values?
                               `((progn-for-development
                                   (check-stack-evaluator-result
                                     ,op-code t (svref local-stack top-of-stack)
                                     top-of-stack))))
                           (go ,go-tag))
                         `((,op-code)
                           ,@(when fully-check-values?
                               `((progn-for-development
                                   (check-stack-evaluator-arguments
                                     ,op-code t local-stack top-of-stack))))
                           ,(if value-left-in-register-1?
                                `(,macro-name)
                                `(setq register-1 (,macro-name)))
                           ,@(case values-to-pop
                               ((-1) `((incff top-of-stack)))
                               ((0) `())
                               ((1) `((decff top-of-stack)))
                               (t `((decff top-of-stack ,values-to-pop))))
                           ,@(when fully-check-values?
                               `((progn-for-development
                                   (check-stack-evaluator-result
                                     ,op-code t register-1 top-of-stack))))
                           (setf (svref local-stack top-of-stack) register-1)
                           (go ,go-tag))))))
		(extended-evaluators-case-clauses
				(loop for normalized-in-line-index
                 from maximum-number-of-in-line-evaluators
                     below (+f maximum-number-of-in-line-evaluators maximum-number-of-extended-inline-evaluators)
                 for description? =
                 (svref in-line-evaluator-array normalized-in-line-index)
                 for op-code = (when description?
                                 (-f (evaluator-number description?) 255))
                 when description?
                   collect
                   (let ((values-to-pop
                           (-f (length (evaluator-arguments description?)) 1))
                         (macro-name (evaluator-function-or-macro-name
                                       description?))
                         (value-left-in-register-1?
                           (evaluator-result-in-register-1? description?)))
                     (if (and (=f values-to-pop 0)
                              (null value-left-in-register-1?))
                         `((,op-code)
                           ,@(when fully-check-values?
                               `((progn-for-development
                                   (check-stack-evaluator-arguments
                                     ,op-code t local-stack top-of-stack))))
                           (setf (svref local-stack top-of-stack)
                                 (,macro-name))
                           ,@(when fully-check-values?
                               `((progn-for-development
                                   (check-stack-evaluator-result
                                     ,op-code t (svref local-stack top-of-stack)
                                     top-of-stack)))))
                         `((,op-code)
                           ,@(when fully-check-values?
                               `((progn-for-development
                                   (check-stack-evaluator-arguments
                                     ,op-code t local-stack top-of-stack))))
                           ,(if value-left-in-register-1?
                                `(,macro-name)
                                `(setq register-1 (,macro-name)))
                           ,@(case values-to-pop
                               ((-1) `((incff top-of-stack)))
                               ((0) `())
                               ((1) `((decff top-of-stack)))
                               (t `((decff top-of-stack ,values-to-pop))))
                           ,@(when fully-check-values?
                               `((progn-for-development
                                   (check-stack-evaluator-result
                                     ,op-code t register-1 top-of-stack))))
                           (setf (svref local-stack top-of-stack) register-1))))))
		(dispatch-instruction-clause (gensym-list (gensym-list (gensym-list 255)
			 `(progn (setq cached-top-of-stack top-of-stack) 
						(decff top-of-stack) 
						(fixnum-case (the (integer 0 255) (svref local-stack (+f top-of-stack 1)))
							,@extended-evaluators-case-clauses)
							(go ,go-tag))))))   
    (setq instruction-case-clauses
          (sort (append instruction-case-clauses evaluator-case-clauses)
                #'<
                :key #'caar))
	(setq instruction-case-clauses (append instruction-case-clauses dispatch-instruction-clause))			
    `(fixnum-case (the (integer 0 255) ,instruction-number)
       ,@instruction-case-clauses
       (otherwise
         (bad-instruction-error ,instruction-number top-of-stack)
         (go ,go-tag)))))




;;; The function `check-stack-in-line-evaluator-arguments' takes a normalized
;;; in-line evaluator number, the stack, and the top-of-stack index, and checks
;;; that the arguments on the stack are validly typed arguments for the
;;; evaluator.  This function is only called in development G2 images, and will
;;; be inserted for a short time in the optimized image during QA.

(defun check-stack-evaluator-arguments
       (evaluator-number-or-op-code in-line? local-stack top-of-stack)
  (let* ((evaluator-description
           (if in-line?
               (in-line-evaluator-description-for-op-code
                 evaluator-number-or-op-code)
               (svref funcalled-evaluator-array evaluator-number-or-op-code)))
         (argument-types (evaluator-arguments evaluator-description))
         (argument-count (length argument-types))
         (incremented-top-of-stack (+f top-of-stack 1)))
    (when (<f incremented-top-of-stack argument-count)
      (stack-error
        top-of-stack
        "Not enough arguments passed to ~a.  It needed ~a and received ~a.  ~
         Please report this stack evaluator internal error to Gensym software ~
         support with the source code of the item named in the error message."
        (instruction-name evaluator-description)
        argument-count
        incremented-top-of-stack))
    (loop for argument-type in argument-types
          for stack-index from (-f incremented-top-of-stack argument-count)
          for argument = (svref local-stack stack-index)
          do
      (unless (type-specification-type-p argument argument-type)
        (write-stack-error
          top-of-stack
          (tformat
            "Wrong argument type given to ~a.  It needed ~NT and received "
            (instruction-name evaluator-description)
            argument-type)
          (write-stored-value argument)
          (tformat
            ".  Please report this stack evaluator internal error to Gensym ~
             software support with the source code of the item named in the ~
             error message."))))))




;;; The function `check-stack-evaluator-result' takes a normalized
;;; in-line evaluator number, the value being returned by the evaluator, and the
;;; top-of-stack, and checks that it is of the correct type.

(defun check-stack-evaluator-result
       (evaluator-number-or-op-code in-line? return-value top-of-stack)
  (let* ((evaluator-description
           (if in-line?
               (in-line-evaluator-description-for-op-code
                 evaluator-number-or-op-code)
               (svref funcalled-evaluator-array evaluator-number-or-op-code)))
         (value-type (evaluator-result-type evaluator-description)))
    #+development
    (when (typep return-value 'bignum)
      (format t "~% Bignum guard ")
      (setq return-value most-positive-fixnum))
    (unless (type-specification-type-p return-value value-type)
      (write-stack-error
        top-of-stack
        (tformat
          "Wrong result type returned from ~a.  It should return ~NT, but ~
           instead returned "
          (evaluator-name evaluator-description)
          value-type)
        (write-stored-value return-value)
        (tformat
          ".  Please report this evaluator internal error to Gensym software ~
           support with the source code of the item named in the error message.")))))

;;;






;;;; Defining Stack Evaluator Instructions




;;; The macro `def-stack-instruction' defines an instruction for the stack
;;; evaluator.  The arguments to this macro are the stack instruction name, the
;;; instruction number, the number of bytes this instruction uses in the
;;; byte-code-vector or a symbol which names a function that computes it, the
;;; number of arguments this instruction takes off the stack if known, a printer
;;; function if the printing of this instruction is not just printing the
;;; instruction name, and the body of the instruction.  The body of the
;;; instruction will be in-lined into the STACK-EVAL function.

;;; The function to compute the number of bytes in an instruction takes the
;;; address of an instruction, the raw-byte-vector, and the constant vector, and
;;; should return the number of bytes the instruction at that address occupies.
;;; This is used by the printer functions.

;;; The following macros can be used in defintions of stack instructions.

;;; The macro `arg' gets arguments to the instruction off the top of the stack.
;;; It takes one argument, a zero-based index to the argument.  This macro is
;;; only available in stack instruction definitions which have supplied the
;;; stack-arg-count argument to def-stack-instruction.  The first argument to an
;;; instruction is referenced with (arg 0), the second with (arg 1), etc.  Note
;;; that arguments to stack instructions are stored with the first argument to
;;; an instruction deepest within the stack and the last instruction argument at
;;; the top of the stack.  The macro arg correctly performs this referencing.

;;; The macro `code-constant' gets code constant arguments from the instruction
;;; stream for the current instruction.  It takes one argument, a zero-based
;;; index to the code constant argument.  It returns a one-byte long integer as
;;; a fixnum.  The implementation of this accessor depends on the value of
;;; stack-program-counter, so any accesses of code constants has to occur before
;;; any branching operations (i.e. SETQs to stack-program-counter).

;;; The macro `stack-frame-local-var' references indexed local variables of a
;;; stack frame.

;;; The macro `stack-frame-arg' references non-optional arguments to a stack
;;; frame.

;;; Note that it now numbers them in an unusual way: see the long
;;; comment immediately above the definition of stack-frame-arg

;;; The variable `stack-program-counter' contains a fixnum which is the program
;;; counter of the next instruction to execute.  A branch is achieved by SETQing
;;; this variable to a new integer.

;;; The variable `local-stack' contains a simple vector which is the stack.

;;; The variable `top-of-stack' contains a fixnum which is an index to the value
;;; on the top of the stack stored in local-stack.  Note that the index is NOT
;;; to the next available position in the stack, but indeed points to the value
;;; at the top.  Instructions should typically use the ARG macro to access
;;; arguments to instructions instead of referencing local-stack and
;;; top-of-stack.  However, top-of-stack and local-stack must be used directly
;;; to pop values off and push values onto the stack.

;;; The variable `constant-vector' contains either a simple vector which holds
;;; the Lisp code constants for a compiled entity, or NIL.  Instructions which
;;; reference this variable should not have to check for NIL, since pseudo-code
;;; vectors should never contain the instructions referencing this array when
;;; the array is absent.

;;; The variables `register-<N>' should be used as local variables within stack
;;; instructions.  A let declares these variables in stack-eval.  Instructions
;;; can arbitrarily use these variables to store values during the execution of
;;; an instruction, and may leave them in any state on exit from the
;;; instruction.  Instructions must expect that the values in registers will be
;;; overwritten between separate invocations of an instruction.  These registers
;;; are using instead of new LET variables within an instruction to avoid extra
;;; pushing and popping instructions on the Lisp stack.  Be aware of the use of
;;; substitution macros which may expand in LET statements, and attempt to use
;;; only symbol arguments to these macros.  At the moment, there are 4
;;; registers, though this can be increased at will.

;;; The variables `fixnum-register-<N>' and `float-register-<N>' should be used
;;; as fixnum and gensym-float local variables within stack instructions.  The
;;; same restrictions that apply to untyped registers apply to this variables,
;;; with the additional restriction that only fixnums and gensym-floats should
;;; be stored in these locations.  There are currently 4 fixnum and 2 float
;;; registers.

;;; Note that the use of macrolet in this expansion defines the macro ARG, which
;;; is only available within the definitions of stack instructions which have
;;; declared numbers of arguments.

(defmacro def-stack-instruction ((name
                                   instruction-number
                                   length-in-bytes
                                   &optional
                                   stack-arg-count
                                   printer-function?
                                   pprinter-function?)
                                 &body body)
  (let ((macro-name (intern (format nil "STACK-~a-BODY" name)))
        (dummy-function (intern (format nil "STACK-~A-DEBUG" name))))
    (unless (and (symbolp name)
                 (fixnump instruction-number)
                 (or (fixnump length-in-bytes) (symbolp length-in-bytes))
                 (or (null stack-arg-count) (fixnump stack-arg-count))
                 (or (null printer-function?) (symbolp printer-function?)))
      (error "Bad args to def-stack-instruction."))
    (when (and stack-arg-count (<f 0 (eval stack-arg-count)))
      (loop with stack-arg-count = (eval stack-arg-count)
            with stack-arg-count-minus-one = (1-f stack-arg-count)
            for i from 0 to stack-arg-count-minus-one
            for offset = (-f stack-arg-count-minus-one i)
            for new = (if (=f i stack-arg-count-minus-one)
                          `(svref local-stack top-of-stack)
                          `(svref local-stack (-f top-of-stack ,offset)))
            do (setq body (subst new
                                 `(arg ,i)
                                 body
                                 :test 'equal))))
    `(progn
       (defmacro ,macro-name ()
         '(progn ,@body))

       ,(if (eval-feature :development)
            `(defun ,dummy-function
                    (byte-code-body constant-vector local-var-vector
                     fixnum-time-limit? initial-program-counter
                     initial-top-of-stack initial-stack-frame-base
                     initial-recursion-depth)
               (stack-eval-locals
                 (tagbody
                     (dummy-stack-eval-references)
                     (,macro-name)
                     (go exit-stack-eval)
                  exit-stack-eval
                    exit-stack-eval-inner))
               nil))
       (make-and-register-stack-instruction-description
         ',name
         ,(if (symbolp length-in-bytes)
              `#',length-in-bytes
              length-in-bytes)
         ,stack-arg-count
         ,(if printer-function?
              `#',printer-function?
              nil)
         ,instruction-number
         ',macro-name
         ,(if pprinter-function?
              `#',pprinter-function?
              nil))
       ',name)))






;;;; Byte Code Emitter and Address Resolver Utilities




;;; The macro `op-code-for-stack-instruction' takes a symbol naming a stack
;;; instruction and returns the stack-instruction-number of that instruction.

(declare-side-effect-free-function op-code-for-stack-instruction)

(defun-simple op-code-for-stack-instruction (name)
  (let ((description (instruction-description name)))
    (cond (description
           (stack-instruction-number description))
          (t
           (compiler-bug
             "op-code fetcher"
             "No stack instruction description for ~a."
             name)
           0))))




;;; The function `instruction-description-for-op-code' takes a one-byte fixnum
;;; op-code, and returns the instruction description if any for that op-code.
;;; Note that in-line-evaluations may be defined for op-codes which have no
;;; instruction description.

(declare-side-effect-free-function instruction-description-for-op-code)

(defun-simple instruction-description-for-op-code (op-code)
  (declare (type fixnum op-code))
  (svref stack-instructions op-code))




;;; The macro `emit-instruction-byte-code' takes a byte-code-stream and a symbol
;;; naming a stack instruction.  This macro will cause a byte to be emitted into
;;; the byte code stream for the given instruction.

(defmacro emit-instruction-byte-code (byte-code-stream instruction-name)
  (let ((op-code? (if (and (eval-feature :no-macros)
                           (constantp instruction-name))
                      (op-code-for-stack-instruction (eval instruction-name))
                      nil)))
    (if op-code?
        `(write-byte-code-to-stream
           ,byte-code-stream
           ,op-code?)
        `(write-byte-code-to-stream
           ,byte-code-stream
           (op-code-for-stack-instruction ,instruction-name)))))




;;; The macro `def-byte-code-resolver' defines a tag to address resolution
;;; function which will be called when replacing references to tags to actual
;;; addresses of instructions within byte-code vectors.  All branching code
;;; which is emitted should have a byte-code resolver defined for it.  The
;;; global property `byte-code-resolver' relates instruction name symbols to
;;; compiled-functions which implement the resolvers.

(def-global-property-name byte-code-resolver)

(defmacro def-byte-code-resolver
          (instruction-name (byte-code-stream-var
                              byte-vector-var
                              instruction-address-var
                              tag-or-tag-list-var)
           &body declarations-and-forms)
  (let ((resolver-name (intern (format nil "BC-~A-RESOLVER" instruction-name))))
    `(progn
       (defun-void-into-place (,resolver-name
                                 (byte-code-resolver ',instruction-name))
           (,byte-code-stream-var ,byte-vector-var ,instruction-address-var
                                  ,tag-or-tag-list-var)
         ,@declarations-and-forms)
       ',instruction-name)))




;;; The function `resolve-procedure-byte-code-addresses' takes a
;;; byte-code-stream which received emitted instruction byte-codes, registered
;;; references to be resolved, and registered addresses for tags.  This function
;;; will make a byte-code-vector from the given byte-code-stream, then iterate
;;; down it, calling address resolution functions on those instructions which
;;; have them.

(defvar current-code-body-entry nil)

(defun entry-point-number (address compiler-code-body)
  (let ((entry-points (compiler-code-body-entry-points compiler-code-body)))
    (or (position address entry-points)
        (if entry-points
            (progn
              (rplacd (last entry-points) (phrase-list address))
              (1-f (length entry-points)))
            (progn (setf (compiler-code-body-entry-points compiler-code-body)
                         (phrase-list address))
                   0)))))

(defun resolve-procedure-byte-code-addresses
       (byte-code-stream &optional code-body-entry?)
  (let ((current-code-body-entry code-body-entry?))
    (loop with byte-vector = (read-byte-code-stream-vector byte-code-stream)
          with byte-vector-length fixnum
                                  = (byte-code-stream-address byte-code-stream)
          for (address . tag-or-tag-list) in
          (byte-code-stream-addresses-to-resolve byte-code-stream)
          for op-code = (byte-vector-aref byte-vector address)
          for instruction-description?
              = (instruction-description-for-op-code op-code)
          for instruction-name?
              = (if instruction-description?
                    (stack-instruction-name instruction-description?))
          for resolver?
              = (if instruction-name?
                    (byte-code-resolver instruction-name?))
          do
      (if resolver?
          (funcall-simple-compiled-function
            resolver? byte-code-stream byte-vector address tag-or-tag-list)
          (compiler-bug
            "address resolver"
            "No address resolver for stack instruction op-code ~a."
            op-code))
          finally
            (when code-body-entry?
              (let ((error-handler-spec?
                      (compiler-code-body-error-handler-spec? code-body-entry?)))
                (when error-handler-spec?
                  (setf (first error-handler-spec?)
                        (entry-point-number
                          (instruction-address-for-tag (first error-handler-spec?) t)
                          (nth
                            (compiler-code-body-surrounding-body-number?
                              code-body-entry?)
                            code-body-entries-in-compilation))))))
            (return (values byte-vector byte-vector-length)))))


(defun activity-and-text-position-information (byte-code-stream)
  (let ((activity-info? (byte-code-stream-activity-information? byte-code-stream))
        (text-position-info? (byte-code-stream-text-position-information? byte-code-stream)))
    (setf (byte-code-stream-activity-information? byte-code-stream) nil)
    (setf (byte-code-stream-text-position-information? byte-code-stream) nil)
    (values activity-info? text-position-info?)))




;;; The macro `def-stack-instruction-emitter' defines an emitter function for
;;; the named stack-instruction.  The name of the emitted instruction is
;;; "EMIT-name-BYTE-CODES".  It registers the defined function as the emitter
;;; function for the named instruction.

;;; This function must take only two
;;; arguments, the byte-code-stream to emit into, and one extra value.  When
;;; making a stack-instruction-node to represent this instruction, the
;;; registered datum will be given to the emitter function.

;;; The above paragraph is nonsense; this function can take as many arguments
;;; as it likes -alatto, 8/14/98

(defmacro def-stack-instruction-emitter (name arglist &body forms)
  (let ((function-name (intern (format nil "EMIT-~A-BYTE-CODES" name))))
    `(defun ,function-name ,arglist ,@forms)))


(defmacro call-stack-instruction-emitter (name &rest args)
  (let ((function-name (intern (format nil "EMIT-~A-BYTE-CODES" name))))
    `(,function-name ,@args)))




;;;; Writing Stack Instructions




;;; The function `write-byte-code-vector' takes a byte-code-vector, the number
;;; of instructions in that vector, and the associated constant-vector.  This
;;; function will cause the instructions to be twritten.

(defun write-byte-code-body (byte-code-body constant-vector)
  (let ((bytes (byte-code-body-length byte-code-body))
        (environment-description
          (byte-code-body-environment-description byte-code-body)))
    (tformat "Environment~%")
    (write-code-body-environment environment-description nil)
    (tformat "~%Constants")
    (if constant-vector
        (if (eq constant-vector
                (byte-code-body-constant-vector byte-code-body))
            (loop for index from 0 below (length constant-vector)
                  for value = (svref constant-vector index)
                  do
              (tformat "~%")
              (twrite-right-justified-unsigned-short index 4)
              (twrite-string " : ")
              (write-stored-value value))
            (tformat "~%  Inherited from base code body"))
        (tformat "~%  None"))
    (tformat "~%Free References")
    (write-byte-code-body-free-references byte-code-body)
    (tformat "~%Instructions")
    (loop with index fixnum = 0
          while (<f index bytes)
          do
      (tformat "~%")
      (incff index (write-stack-instruction
                     index byte-code-body constant-vector)))))

(defun instruction-should-not-be-compiled (op-code)
  (and (not (in-line-evaluator-op-code-p op-code))
       (let* ((description (instruction-description-for-op-code op-code))
              (name (and description
                         (stack-instruction-name description))))
         (or (null description)
             (eq 'system-call name)
             (eq 'nupec-synchronize name)
             (eq 'halt name)
             (eq 'add-to-action-cache name)
             (eq 'restore-from-action-cache-or-branch name)
             (eq 'reset-kb name)))))

(defparameter maximum-byte-code-body-length-to-compile 5000)

(defun byte-code-body-is-too-long-to-compile-p (byte-code-body)
  (<f maximum-byte-code-body-length-to-compile (byte-code-body-length byte-code-body)))

(defun byte-code-body-contains-instruction-that-should-not-be-compiled-p (byte-code-body constant-vector)
  (loop with total-bytes = (byte-code-body-length byte-code-body)
        with instruction-vector = (byte-code-body-byte-vector byte-code-body)
        with program-counter fixnum = 0
        while (<f program-counter total-bytes)
        for op-code = (byte-vector-aref instruction-vector program-counter)
        do
    (incff program-counter
           (if (in-line-evaluator-op-code-p op-code)
               1
               (let* ((description
                        (instruction-description-for-op-code op-code))
                      (byte-length-or-function?
                        (and description
                             (stack-instruction-byte-length description)))
                      (byte-length?
                        (cond ((fixnump byte-length-or-function?)
                               byte-length-or-function?)
                              ((compiled-function-p byte-length-or-function?)
                               (funcall-compiled-function
                                 byte-length-or-function?
                                 program-counter instruction-vector constant-vector))
                              (t 1))))
                 (when (instruction-should-not-be-compiled op-code)
                   (return t))
                 byte-length?)))))

(defun byte-code-body-contains-backward-branch-p (byte-code-body constant-vector)
  (loop with total-bytes = (byte-code-body-length byte-code-body)
        with instruction-vector = (byte-code-body-byte-vector byte-code-body)
        with program-counter fixnum = 0
        while (<f program-counter total-bytes)
        for op-code = (byte-vector-aref instruction-vector program-counter)
        do
    (incff program-counter
           (if (in-line-evaluator-op-code-p op-code)
               1
               (let* ((description
                        (or (instruction-description-for-op-code op-code)
                            (return nil)))
                      (byte-length-or-function?
                        (stack-instruction-byte-length description))
                      (byte-length?
                        (cond ((fixnump byte-length-or-function?)
                               byte-length-or-function?)
                              ((compiled-function-p byte-length-or-function?)
                               (funcall-compiled-function
                                 byte-length-or-function?
                                 program-counter instruction-vector constant-vector))
                              (t 1)))
                      (lowest-address-from-instruction?
                        (case (stack-instruction-name description)
                          ((branch branch-if-not-true branch-if-known)
                           (let ((stack-program-counter (+f program-counter 1)))
                             (code-constant 0)))
                          ((branch-long branch-long-if-not-true
                            branch-long-if-known boolean-branch-long-if-not-true)
                           (let ((stack-program-counter (+f program-counter 1)))
                             (long-code-constant 0)))
                          ((branch-relative branch-relative-if-not-true
                            branch-relative-if-known boolean-branch-relative-if-not-true)
                           (let ((stack-program-counter (+f program-counter 1)))
                             (+f program-counter (relative-code-constant 0))))
                          ((case-dispatch open-role-iteration-no-domain open-role-iteration
                            serve-next-iteration-value restore-from-action-cache-or-branch)
                           nil) ;; do these later...
                          (t
                           nil))))
                 (when (and lowest-address-from-instruction?
                            (<f lowest-address-from-instruction? program-counter))
                   (return t))
                 byte-length?)))))



;;; The function `show-code-body' will show a code body in the background
;;; stream when debugging.

#+development
(defun show-code-body (code-body &optional constant-vector)
  (cond
    ((not (byte-code-body-p code-body))
     (warn "Can not show this, it isn't a byte-code-body"))
    (t
     (let* ((text-string
              (twith-output-to-text-string
                (write-byte-code-body
                  code-body
                  (or (byte-code-body-constant-vector code-body)
                      (cond ((byte-code-body-p constant-vector)
                             (byte-code-body-constant-vector constant-vector))
                            (t
                             constant-vector))))))
            (gensym-string
              (export-text-string
                text-string
                'iso-8859-1-gensym-string)))
       (write-string gensym-string)
       (reclaim-text-string text-string)
       (reclaim-gensym-string gensym-string)
       nil))))




;;; The global variable show-stack-bytes?  controls if the raw bytes of stack
;;; instructions are printed in disassembles.

(defvar show-stack-bytes? nil)




;;; The function `write-stack-instruction' twrites a stack instruction.  This
;;; function also returns the number of bytes that this instruction occupies
;;; within the byte-vector.

(defun write-stack-instruction (op-code-address byte-code-body constants)
  (let* ((raw-byte-vector (byte-code-body-byte-vector byte-code-body))
         (environment-description
           (byte-code-body-environment-description byte-code-body))
         (op-code (byte-vector-aref raw-byte-vector op-code-address))
         (bytes nil))
    (twrite-right-justified-unsigned-short op-code-address 5)
    (twrite-string " : ")
    (if (in-line-evaluator-op-code-p op-code)
        (let ((description?
                (in-line-evaluator-description-for-op-code op-code)))
          (cond (description?
                 (twrite-symbol (instruction-name description?)))
                (t
                 (twrite-string
                   "BAD INSTRUCTION, UNUSED IN-LINE EVAL OP-CODE ")
                 (twrite-positive-fixnum op-code)))
          (setq bytes 1))
        (let* ((description? (instruction-description-for-op-code op-code))
               (printer-function?
                 (when description?
                   (stack-instruction-printer? description?)))
               (byte-length-or-function?
                 (when description?
                   (stack-instruction-byte-length description?)))
               (byte-length?
                 (cond ((fixnump byte-length-or-function?)
                        byte-length-or-function?)
                       ((compiled-function-p byte-length-or-function?)
                        (funcall-compiled-function
                          byte-length-or-function?
                          op-code-address raw-byte-vector constants))
                       (t nil))))
          (cond (printer-function?
                 (twrite-symbol
                   (stack-instruction-name description?))
                 (funcall-simple-compiled-function
                   printer-function?
                   op-code-address raw-byte-vector constants
                   environment-description)
                 (setq bytes byte-length?))
                (description?
                 (twrite-symbol
                   (stack-instruction-name description?))
                 (setq bytes byte-length?))
                (t
                 (twrite-string "BAD INSTRUCTION, UNUSED OP-CODE ")
                 (twrite-positive-fixnum op-code)
                 (setq bytes 1)))))
    (when show-stack-bytes?
      (loop initially
              (twrite-string " <bytes = ")
            for index from op-code-address
            repeat bytes
            do
        (unless (=f index op-code-address)
          (twrite-string ", "))
        (twrite-positive-fixnum (byte-vector-aref raw-byte-vector index))
            finally
              (twrite-character #.%\>)))
    bytes))




;;; The function `twrite-right-justified-unsigned-short' takes an unsigned
;;; integer whose magnitude is less than 65536 and twrites it, padding it on the
;;; left so that the right columns will line up in a field whose width is given
;;; in the second argument.

(defun twrite-right-justified-unsigned-short (unsigned-short field-width)
  (let ((integer-width (cond ((<f unsigned-short 10) 1)
                             ((<f unsigned-short 100) 2)
                             ((<f unsigned-short 1000) 3)
                             ((<f unsigned-short 10000) 4)
                             (t 5))))
    (when (>f field-width integer-width)
      (twrite-string
        (case (-f field-width integer-width)
          ((4) "    ")
          ((3) "   ")
          ((2) "  ")
          ((1) " ")
          (t ""))))
    (twrite-positive-fixnum unsigned-short)
    nil))




;;; The development only function `print-in-line-evaluators' prints the names
;;; actual instruction numbers of the in-line evaluators.

#+development
(defun print-in-line-evaluators ()
  (loop for index from 0 below (length in-line-evaluator-array)
        for description? = (svref in-line-evaluator-array index)
        do
    (when description?
      (format t "~%~3d ~a"
              (evaluator-number description?)
              (instruction-name description?)))))




;;; The function `print-all-stack-instructions' is available in development for
;;; printing the full set of stack instructions, be they defined with
;;; def-stack-instruction, def-in-line-evaluator, or def-funcalled-evaluator.

#+development
(defun print-all-stack-instructions (&optional show-op-codes?)
  (with-faster-standard-output
    (format t "Stack Instructions~%~%")

    (loop for op-code from 1 to 255 do
      (if (in-line-evaluator-op-code-p op-code)
          (let ((description?
                  (in-line-evaluator-description-for-op-code op-code)))
            (cond (description?
                   (when show-op-codes?
                     (format t "~3d " op-code))
                   (format t "~(~a~)~%" (instruction-name description?)))
                  (show-op-codes?
                   (format t "~3d unused~%" op-code))))
          (let ((description? (instruction-description-for-op-code op-code)))
            (cond (description?
                   (when show-op-codes?
                     (format t "~3d " op-code))
                   (format t "~(~a~)~%"
                           (stack-instruction-name description?)))
                  (show-op-codes?
                   (format t "~3d unused~%" op-code))))))

    (format t "~%~%Funcalled Instructions~%~%")

    (loop for op-code from 0
          repeat maximum-number-of-funcalled-instructions
          for description? =
          (svref funcalled-instructions op-code)
          do
      (cond (description?
             (when show-op-codes?
               (format t "~3d " op-code))
             (format t "funcall-instruction ~(~a~)~%"
                     (funcalled-instruction-name description?)))
            (show-op-codes?
             (format t "~3d unused~%" op-code))))

    (format t "~%~%Funcalled Evaluators~%~%")

    (loop for op-code from 0
          repeat maximum-number-of-funcalled-evaluators
          for description? =
          (svref funcalled-evaluator-array op-code)
          do
      (cond (description?
             (when show-op-codes?
               (format t "~3d " op-code))
             (format t "funcall-evaluator ~(~a~)~%"
                     (instruction-name description?)))
          (show-op-codes?
           (format t "~3d unused~%" op-code))))))

;;; `known-stack-instruction-name?' is used by the intermediate code optimizer
;;; to determine if the name designates a known instruction.

#+development
(defun known-stack-instruction-name? (name)
  (let ((result nil))
    (loop for op-code from 1 to 255
          until result
          do
      (if (in-line-evaluator-op-code-p op-code)
          (let ((description?
                  (in-line-evaluator-description-for-op-code op-code)))
            (when (and description?
                       (eq (instruction-name description?) name))
              (setq result t)))
          (let ((description? (instruction-description-for-op-code op-code)))
            (when (and description?
                       (eq (stack-instruction-name description?) name))
              (setq result t)))))
    (unless result
      (loop for op-code from 0
            repeat maximum-number-of-funcalled-instructions
            for description? =
                (svref funcalled-instructions op-code)
            until result
            do
        (when (and description?
                   (eq name (funcalled-instruction-name description?)))
          (setq result t))))
    (unless result
      (loop for op-code from 0
            repeat maximum-number-of-funcalled-evaluators
            for description? =
                (svref funcalled-evaluator-array op-code)
            until result
            do
        (when (and description?
                   (eq name (instruction-name description?)))
          (setq result t))))
    (values result)))




;;; The development only function `system-function-namespace-violations' finds
;;; all evaluators not listed in the defined-functions parameter.

#+development
(defun system-function-namespace-violations (&optional show-op-codes?)
  (with-faster-standard-output
    (format t "Stack Instructions~%~%")

    (loop for op-code from 1 to 255 do
      (when (in-line-evaluator-op-code-p op-code)
        (let ((description?
                (in-line-evaluator-description-for-op-code op-code)))
          (when (and description?
                     (not (memq (evaluator-name description?)
                                *built-in-functions*)))
            (when show-op-codes?
              (format t "~3d " op-code))
            (format t "~(~a (~a)~)~%"
                    (evaluator-name description?)
                    (instruction-name description?))))))

    (format t "~%~%Funcalled Evaluators~%~%")

    (loop for op-code from 0
          repeat maximum-number-of-funcalled-evaluators
          for description? =
          (svref funcalled-evaluator-array op-code)
          do
      (when (and description?
                 (not (memq (evaluator-name description?)
                            *built-in-functions*)))
        (when show-op-codes?
          (format t "~3d " op-code))
        (format t "funcall-evaluator ~(~a (~a)~)~%"
                (evaluator-name description?)
                (instruction-name description?))))))








;;;; Pretty Printing Stack Instructions




;;; This section implements printers for instructions with their arguments in a
;;; form similar to what is entered by the user with the arguments that the
;;; instruction is currently executing.  This code works by taking as arguments
;;; the stack and top-of-stack as well as the byte-code-body, constant-vector
;;; and program-counter.

;;; Not all instructions will have printers.  In this pass at this facility,
;;; only those instructions which should be shown to users will be given
;;; printers.  Internal instructions, such as those dealing with expirations,
;;; will not be shown.  Predicates are provided for the tracing facilities to
;;; determine if a particular instruction should or should not be traced for the
;;; user.

;;; Since most evaluators are printable, there will be default printers for the
;;; in-line evaluators.  The default will depend on the argument count for the
;;; evaluator.  If the argument count is two, then the default printing for an
;;; in-line evaluator will be as an infix operator.  If the argument count is
;;; anything other than 2, then a functional format will be used.  If a symbol
;;; naming a

(defun pprint-stack-instruction
       (op-code-address byte-code-body constants stack top-of-stack)
  (let* ((raw-byte-vector (byte-code-body-byte-vector byte-code-body))
         (op-code (byte-vector-aref raw-byte-vector op-code-address))
         (bytes nil))
    (if (in-line-evaluator-op-code-p op-code)
        (let* ((description?
                 (in-line-evaluator-description-for-op-code op-code))
               (arg-count (when description?
                            (length (evaluator-arguments description?))))
               (pprinter? (when description?
                            (evaluator-pprinter-function description?))))
          (cond ((null description?)
                 ;; This should never happen.
                 (twrite-string
                   "internal in-line evaluation op-code ")
                 (twrite-positive-fixnum op-code))
                (pprinter?
                 (funcall-simple-compiled-function
                   pprinter? description? op-code-address byte-code-body
                   constants stack top-of-stack))
                ((=f arg-count 2)
                 (pprint-infix-evaluator
                   description? op-code-address byte-code-body
                   constants stack top-of-stack))
                (t
                 (pprint-functional-evaluator
                   description? op-code-address byte-code-body
                   constants stack top-of-stack)))
          (setq bytes 1))
        (let* ((description? (instruction-description-for-op-code op-code))
               (pprinter-function?
                 (when description?
                   (stack-instruction-pprinter? description?)))
               (byte-length-or-function?
                 (when description?
                   (stack-instruction-byte-length description?)))
               (byte-length?
                 (cond ((fixnump byte-length-or-function?)
                        byte-length-or-function?)
                       ((compiled-function-p byte-length-or-function?)
                        (funcall-simple-compiled-function
                          byte-length-or-function?
                          op-code-address raw-byte-vector constants))
                       ;; Should never happen.
                       (t 1))))
          (cond (pprinter-function?
                 (funcall-simple-compiled-function
                   pprinter-function?
                   op-code-address byte-code-body constants stack top-of-stack)
                 (setq bytes byte-length?))
                (t
                 ;; Shouldn't happen unless a stack error happens in an
                 ;; instuction without a printer.
                 (twrite-string "internal op-code ")
                 (twrite-positive-fixnum op-code)
                 (setq bytes byte-length?)))))
    (when show-stack-bytes?
      (loop initially
              (twrite-string " <bytes = ")
            for index from op-code-address
            repeat bytes
            do
        (unless (=f index op-code-address)
          (twrite-string ", "))
        (twrite-positive-fixnum (byte-vector-aref raw-byte-vector index))
            finally
              (twrite-character #.%\>)))
    bytes))




;;; The function `pprinter-for-stack-instruction-p' takes an op-code-address and
;;; a byte-code-body, and returns whether or not a pretty printer exists for the
;;; indicated instruction within the byte code body.  This is used to determine
;;; whether or not tracing and breakpoints messages should be offered for a
;;; particular instruction, or if it should silently execute.  When instructions
;;; without pretty printers are given to pprint-stack-instruction, it writes
;;; something like "internal instruction N" where N is the instruction number.

(defun-simple pprinter-for-stack-instruction-p (op-code-address byte-code-body)
  (declare (type fixnum op-code-address))
  (let* ((raw-byte-vector (byte-code-body-byte-vector byte-code-body))
         (op-code (byte-vector-aref raw-byte-vector op-code-address)))
    (declare (type fixnum op-code))
    (or (in-line-evaluator-op-code-p op-code)
        (let ((description? (instruction-description-for-op-code op-code)))
          (when description?
            (if (eq (stack-instruction-name description?) 'funcall-instruction)
                (pprinter-for-funcalled-instruction-p
                  (byte-vector-aref raw-byte-vector (+f op-code-address 1)))
                (stack-instruction-pprinter? description?)))))))

(defun-simple pprinter-for-funcalled-instruction-p
              (funcalled-instruction-number)
  (declare (type fixnum funcalled-instruction-number))
  (let ((funcalled-instruction-description?
          (svref funcalled-instructions funcalled-instruction-number)))
    (and funcalled-instruction-description?
         (funcalled-instruction-pprinter-function
           funcalled-instruction-description?))))




;;; Note that these printers should compare the given top-of-stack with the
;;; global variable cached-top-of-stack.  If these do not match, then the
;;; instruction has already reclaimed some of the arguments, and this printer
;;; should not attempt to print any of them.

;;; The function `write-stack-argument' should be used to print all arguments to
;;; instructions.  Its first argument is the 1 based index to the argument to be
;;; printed.  The second argument is the number of arguments that this
;;; instruction accepts.  The third argument is the stack, and the fourth is the
;;; top of stack.  If the given top of stack agrees with the cached top of
;;; stack, then this function will print the argument at the indicated position
;;; in the stack.  If they do not agree, then this prints argument unavailable.

(defun write-stack-argument (index arg-count stack top-of-stack)
  (let ((arg-index (-f top-of-stack (-f arg-count index))))
    (if (and (=f top-of-stack cached-top-of-stack)
             (not (minuspf arg-index)))
        (write-stored-value (svref stack arg-index))
        (twrite-string "<unavailable argument>"))))






;;;; Stack Frames and Functions




;;; The stack evaluator will put function call frames onto the stack when
;;; executing user defined functions and optimized procedures which do not
;;; contain wait states.  Note that these frames I'm talking about are stack
;;; frames in the typical stack machine sense, not G2 frames which are
;;; instances of G2 classes.  When the stack-eval function is called at top
;;; level, environment, instruction, and constant vectors will be passed in as
;;; arguments.  These make up the top level function frame of the stack
;;; evaluator, an implied top-level frame.  When a user defined function is
;;; called, a new, explicit stack frame will be created on the stack.  Further
;;; calls to user defined functions from the first function will push further
;;; frames onto the stack.  Note that at compile time, we cannot tell if the
;;; function call is dispatching to a user defined function, a tabular
;;; function, or a foreign function.  The call site compilations will then be
;;; the same for all of these, and the CALL-FUNCTION instruction will handle
;;; each specially.

;;; A function call site is compiled as follows.  The arguments to the called
;;; function are pushed on the stack, followed by flags indicating whether
;;; unknown and/or no-item are allowable values, followed by the number of
;;; arguments.  The type of the arguments to functions is item-or-datum, and
;;; allows no-item or unknown in the arguments if the required type for the
;;; function call allows no-item or unknown.  Finally the function frame is
;;; pushed on the stack.  The type of the argument to call function is class
;;; item, since it can be any of several types of functions.  Next the
;;; CALL-FUNCTION instruction is executed.  When execution resumes in the
;;; calling code, the arguments and all other things pushed for the function
;;; will have been popped off the stack, and the result of the function will be
;;; left on the stack.  Note that if the function is allowed to return unknown,
;;; then the expiration of the function result will have been minimized with
;;; the global expiration.  If the function can return no-item, then NIL can be
;;; left on the stack.

;;; When the function is a foreign function or a tabular function, then the
;;; compiled Lisp code within the call-function instruction will fetch its
;;; arguments off the stack and leave the value on the stack.  The required
;;; type of arguments to foreign functions is datum and so arguments should be
;;; coerced to datum, paying attention to the unknown allowed flag.  See
;;; documentation in the call-function instruction for details.

;;; When the function is a user defined function, it is handled as follows.
;;; The count and types of arguments are checked against an argument list
;;; description stored in the function definition object.  If any of the
;;; arguments should be datum, but a variable-or-parameter is found, then an
;;; attempt will be made to call get-current-value on the frame.  If a good
;;; value is found from the frame, then the value will replace the frame in the
;;; stack.  (Note that this can only happen if we know the types of the
;;; arguments as something more specific than item-or-datum.  This will not
;;; happen in 3.0.  -jra 2/4/92)

;;; This call to get-current-value is affected by the unknown allowed flag,
;;; since variables will not be fetched if called in an environment where
;;; unknown is not allowed.  If this is unable to resolve the frame into the
;;; correct datum type or if there is some other kind of type mismatch, then an
;;; error should be signaled, or unknown returned, depending on whether unknown
;;; is allowed.

;;; Arguments may evaluate to no-item, depending on the no-item allowed flag.

;;; After the arguments have been deemed acceptable, and before the old stack
;;; frame is pushed onto the stack, the tracing and breakpoints context of the
;;; old stack frame is exited.  This should be done without any tracing or
;;; breakpoints messages, since we aren't really "exiting" this context, we're
;;; just pushing it onto the stack.

;;; Next the state of the old frame will be pushed onto the stack and the
;;; environment for the new stack frame will be written into the local
;;; variables of stack-eval.  The state of the old frame contains 6 elements:
;;; the old stack-frame-base, the old stack program counter, the old byte code
;;; body, the old constant vector, the old computation frame, and the old
;;; computation component particulars.

;;; After pushing the state of the old frame, the top-of-stack index + 1
;;; becomes the new stack-frame-base.  This means that stack-frame-var 0 is
;;; found at the stack frame base location, and that the eventual function
;;; value will be found at the stack-frame-base index.  If there are any
;;; optional arguments to this function, they are pushed onto the top of stack,
;;; or the default values are pushed instead (note that we don't have any
;;; optionals now -jra 5/30/91).  These optional arguments will always be the
;;; first of any local variables in a frame.  This organization of arguments
;;; and local variables implies that fixed position arguments are accessed
;;; through negative offsets from the stack-frame-base index, and that local
;;; variables are non-negative offsets.

;;; Next the state of the new stack frame is set into the local variables of
;;; stack-eval.  Stack frame base is set to top-of-stack + 1, stack program
;;; counter is set to 0, instruction vector is set to the function's
;;; instruction vector, constant vector is set to the function's constant
;;; vector, computation frame is set to the function-definition, and component
;;; particulars is set to NIL.

;;; After the new stack frame is established, we should enter the tracing and
;;; breakpoints context of the new stack frame.  This should be done with an
;;; entry message, to announce the new frame.

;;; When CALL-FUNCTION returns, stack eval will begin executing the
;;; instructions for the function.  Before returning, CALL-FUNCTION should set
;;; the instruction count to instructions-between-time-checks, so that the
;;; tracing flags will be reset using the new stack frame's flags.  Finally,
;;; CALL-FUNCTION returns and begins execution of the function.  (I believe we
;;; now just set the flags directly within call-function.  This speeds up
;;; function calls.  -jra 2/4/92)

;;; Within the function, the arguments will be fetched using stack-arg
;;; var-spots found from expression bound local names.  Note that the function
;;; must be compiled in four ways, the combinations of allowing or disallowing
;;; no-item and unknown.  The flag which determines whether the function is or
;;; is not allowed to return unknown is found in (stack-arg arg-list-length)
;;; and the no-item flag is found in (stack-arg arg-list-length) + 1.

;;; The function returns by calling the RETURN-FROM-FUNCTION stack instruction.
;;; This instruction performs the following operations.  First it verbosely
;;; exits the tracing and breakpoints context of the function, printing the
;;; value about to be returned.  Next it should restore the old stack frame
;;; from the locations just below stack frame base.  Next it should pop the
;;; arguments and every else above them off the stack.  Then it should copy the
;;; old top of stack (i.e.  the value to be returned) down to where the first
;;; argument to this function was pushed.  Next it should silently reenter the
;;; tracing and breakpoints context of the old stack frame, set the instruction
;;; counter to instructions-between-time-checks, and return, thus resuming
;;; execution of the calling stack frame.

;;; Note that (stack-arg k) denotes the position on the stack, not of the
;;; k'th arg, but the (n-k+2)'th arg. This is done so that all stack-arg
;;; references can be done relative to stack-frame-base, rather than requiring
;;; an additional redirection.
;;; (stack-arg 1) refers to the unknown-p arg, while
;;; (stack-arg 0) refers to the no-item-p arg. -alatto, 10/13/98

;;; So, the following is a picture of a stack frame as a called user-defined
;;; function is just about to execute its first instruction.  SFB stands for
;;; stack-frame-base.

;;;   arg 1                     : SFB - 10 - arg-count  (stack-arg N+1)
;;;    ...
;;;   arg N                     : SFB - 11              (stack-arg 2)
;;;   unknown-p                 : SFB - 10              (stack-arg 1)
;;;   no-item-p                 : SFB - 9               (stack-arg 0)
;;;   arg-count (N)             : SFB - 8
;;;   function-definition       : SFB - 7
;;;   old-stack-frame-base      : SFB - 6
;;;   old-stack-program-counter : SFB - 5
;;;   old-byte-code-body        : SFB - 4
;;;   old-constant-vector       : SFB - 3
;;;   old-computation-frame     : SFB - 2
;;;   old-component-particulars : SFB - 1, Top-of-stack
;;;


;;; The macro `stack-frame-arg' takes a fixnum from 0 through 255 as its
;;; argument and returns the stack value which is the apropriately
;;; numbered argument to the
;;; stack frame. "appropriately numbered" means that the arguments are numbered
;;; in descending order, from N+1 down to 2, leaving (stack-arg 1) and
;;; (stack-arg-0) to refer to the extra  unknown-p and no-item-p arguments.
;;; Note that this macro does NO bounds checking on the actual
;;; stack frame argument count, nor on the 256 limit.  It is up to the compiler
;;; and instruction to only reference stack frame arguments which have actually
;;; been supplied.  This macro may only be called within STACK-EVAL or the body
;;; of an in-line instruction macro.

;;; The arguments to stack frames are pushed in order onto the stack.  This
;;; means that we have to use the total number of arguments as a further offset
;;; from the stack-frame-base.  -jra 11/2/90

;;; Not any more, now that we have been clever and numbered them in the
;;; opposite direction (see above)! -alatto, 10/13/98

;;; The macro `stack-frame-arg-stack-index' returns the stack index to an
;;; indexed stack-frame-arg.  Do this if you need to reference the arg location
;;; several times and don't want to keep recomputing its address within the
;;; stack.

(defmacro stack-frame-arg (argument-number)
  `(svref local-stack (stack-frame-arg-stack-index ,argument-number)))

(defmacro stack-frame-arg-stack-index (argument-number)
  `(-f (-f stack-frame-base 9)
       ,argument-number))

;;; The macro `stack-frame-local-var' takes a fixnum from 0 through 255 and
;;; returns the local stack frame variable value at that index.  Note that this
;;; macro does no bounds checking, so the compiler and instruction
;;; implementation must prevent any out of stack references.  This macro may
;;; only be called within STACK-EVAL or the body of any in-line instruction
;;; macro.

;;; The macro `stack-frame-local-var-stack-index' takes an argument like
;;; stack-frame-local-var, but instead this macro returns a fixnum which is the
;;; index in the stack to that local-var.  Do this if you need to reference the
;;; variable several times and don't want to keep recomputing the location
;;; within the stack.

(defmacro stack-frame-local-var (local-variable-number)
  `(svref local-stack
          (stack-frame-local-var-stack-index ,local-variable-number)))

(defmacro stack-frame-local-var-stack-index (local-variable-number)
  (if (and (constantp local-variable-number)
           (= (eval local-variable-number) 0))
      'stack-frame-base
      `(+f stack-frame-base ,local-variable-number)))

(defmacro stack-frame-first-argument-index (stack-frame-base argument-count)
  `(-f (-f ,stack-frame-base ,argument-count) 10))




;;; The following macros access components of a stack-frame, given the stack
;;; frame base and the stack.

(defmacro stack-frame-unknown-ok-p (stack stack-frame-base)
  `(svref ,stack (-f ,stack-frame-base 10)))

(defmacro stack-frame-no-item-ok-p (stack stack-frame-base)
  `(svref ,stack (-f ,stack-frame-base 9)))

(defmacro stack-frame-argument-count-index (stack-frame-base)
  `(-f ,stack-frame-base 8))

(defmacro stack-frame-argument-count (stack stack-frame-base)
  `(svref ,stack (stack-frame-argument-count-index ,stack-frame-base)))

(defmacro stack-frame-function-definition (stack stack-frame-base)
  `(svref ,stack (-f ,stack-frame-base 7)))

(defmacro stack-frame-old-stack-frame-base (stack stack-frame-base)
  `(svref ,stack (-f ,stack-frame-base 6)))

(defmacro stack-frame-stack-program-counter (stack stack-frame-base)
  `(svref ,stack (-f ,stack-frame-base 5)))

(defmacro stack-frame-byte-code-body (stack stack-frame-base)
  `(svref ,stack (-f ,stack-frame-base 4)))

(defmacro stack-frame-constant-vector (stack stack-frame-base)
  `(svref ,stack (-f ,stack-frame-base 3)))

(defmacro stack-frame-computation-frame (stack stack-frame-base)
  `(svref ,stack (-f ,stack-frame-base 2)))

(defmacro stack-frame-computation-component-particulars (stack stack-frame-base)
  `(svref ,stack (-f ,stack-frame-base 1)))

(defconstant number-of-extra-stack-frame-values 6)

(defmacro incff-top-of-stack-with-caching (increment)
  `(incff top-of-stack ,increment))

;;; The function `write-called-function-and-arguments' takes a stack and the
;;; stack frame base of the call to this function on the stack.  This function
;;; then twrites the name and arguments of that function in a way suitable for
;;; showing to users.  Note that the index to the function is merely the
;;; top-of-stack value when the call-function instruction is executed.

;;; If nargs is supplied, it means that the stack frame is not fully built-inu
;;; yet, and the nargs is not yet on the stack. -alatto, 8/13/98

(defun write-called-function-and-arguments
    (stack base &optional nargs function)
  (let* ((function (or function (stack-frame-function-definition stack base)))
         (argument-count
           (or nargs
               (evaluation-integer-value (stack-frame-argument-count stack base))))
         (first-argument-index
           (stack-frame-first-argument-index base argument-count)))
    (declare (type fixnum argument-count first-argument-index))
    (denote-component-of-block t nil function)
    (twrite-char #.%\()
    (loop for argument-index fixnum from first-argument-index
                             below (+f first-argument-index argument-count)
          do
      (unless (=f argument-index first-argument-index)
        (twrite-string ", "))
      (write-stored-value (svref stack argument-index)))
    (twrite-string ")")))

;;;






;;;; Standard Error Messages




;;; The following section implements printers for informatation about contexts
;;; within the stack evaluator.  These functions are to be used by all error
;;; handling contexts to provide consistent descriptions of the current state of
;;; the run-time system.

;;; The function `generate-standard-error-message' takes information about an
;;; error which has occured in the evaluators and information about the
;;; currently executing thing.  It generates and returns an error-text object
;;; containing the error message which should be displayed to the user or passed
;;; through on-error handling.  The caller is responsible for reclaiming the
;;; returned string.

;;; The argument error can be either an error object or a symbol.  If it is
;;; an error object the class of the error object is used as the name of
;;; the error.
;;; This change made to accomodate error object handling in 5.0. -ajs (5/23/96)

(defun generate-standard-error-message
    (error error-text-string computation-frame
           computation-component-particulars
           computation-instance byte-code-body?
           constant-vector? current-program-counter? local-stack? top-of-stack?
           local-var-vector?)
  (let ((error-name (if (symbolp error) error
                        (class error))))
    (twith-output-to-error-text                                    ; Return an error-text.
      (if (eq error-name 'error)
          (twrite-string "Error:")
          (tformat "Error:  (~a)" error-name))
      (tformat "~%~%~nw~%~%" error-text-string)
      (write-computation-context
        computation-frame computation-component-particulars
        computation-instance byte-code-body? constant-vector?
        current-program-counter? local-stack? top-of-stack? local-var-vector?))))

(defun write-computation-context
       (computation-frame computation-component-particulars
        computation-instance byte-code-body? constant-vector? program-counter?
        local-stack? top-of-stack? local-var-vector?)
  (when (and program-counter? byte-code-body? local-stack?
             top-of-stack?)
    (twrite-string "Operation: ")
    (pprint-stack-instruction
      program-counter? byte-code-body? constant-vector? local-stack?
      top-of-stack?))
  (when (and program-counter? disassemble-enabled?
             (not (and (framep computation-frame) (proprietary-p computation-frame))))
    (when (and byte-code-body? constant-vector?)
      (tformat "~%")
      (write-stack-instruction
        program-counter? byte-code-body? constant-vector?))
    (tformat "~%Program Counter: ~a" program-counter?))
  (cond ((and byte-code-body?
              computation-frame
              program-counter?
              (byte-code-body-activity-description byte-code-body?))
         (tformat "~%Activity: ")
         (write-activity-given-pc-and-byte-code-body
           byte-code-body? program-counter?))
        ((and computation-frame current-computation-activity)
         (tformat "~%Activity: ")
         (write-activity-given-index
           computation-frame computation-component-particulars
           current-computation-activity)))
  (tformat "~%Within: ")
  (write-stack-evaluator-backtrace
    computation-frame computation-component-particulars
    computation-instance local-stack? top-of-stack? cached-stack-frame-base)
  (cond ((code-body-invocation-p computation-instance)
         (write-code-body-invocation-environment
           computation-instance 0 nil))
        (local-var-vector?
         (tformat "~%Local Names:~%")
         (let* ((computation-instance-byte-code-body?
                  (computation-instance-byte-code-body computation-instance))
                (environment-description?
                  (when computation-instance-byte-code-body?
                    (byte-code-body-environment-description
                      computation-instance-byte-code-body?))))
           (write-code-body-environment
             environment-description? local-var-vector?))))

  (when (and disassemble-enabled? local-stack? top-of-stack?
             (not (and (framep computation-frame) (proprietary-p computation-frame))))
    (write-stack-contents local-stack? top-of-stack? 4)))

(defun write-computation-context-to-console
    (computation-frame computation-component-particulars
     computation-instance byte-code-body? constant-vector? program-counter?
     local-stack top-of-stack)
  (let ((string
          (twith-output-to-text-string
            (when program-counter?
              (when (and byte-code-body? constant-vector?)
                (write-stack-instruction
                  program-counter? byte-code-body? constant-vector?))
              (tformat "  "))
            (write-stack-evaluator-top-frame
              computation-frame computation-component-particulars
              computation-instance local-stack cached-stack-frame-base)
            (when top-of-stack (tformat "  tos: ~d" top-of-stack)))))
    (notify-user-at-console string)
    (reclaim-text-string string)))



(defun write-code-body-invocation-environment
    (code-body-invocation depth writing-local-vars-from-inferior-code-body?)
  ;; The writing-local-vars-from-inferior-code-body? argument should be passed
  ;; NIL in the top-level call, but is set in the recursive call.  It is used to
  ;; indicate whether any of the called code bodies will be printing local vars.
  (let* ((computation-instance-byte-code-body?
           (computation-instance-byte-code-body code-body-invocation))
         (environment-description?
           (when computation-instance-byte-code-body?
             (byte-code-body-environment-description
               computation-instance-byte-code-body?)))
         (local-var-vector? (invocation-local-var-vector
                              code-body-invocation))
         (write-local-vars? (and environment-description? local-var-vector?)))
    (unless (base-code-body-invocation-p code-body-invocation)
      (setq depth
            (write-code-body-invocation-environment
              (code-body-caller code-body-invocation) depth
              (or writing-local-vars-from-inferior-code-body?
                  write-local-vars?))))
    (when write-local-vars?
      (if (and (=f depth 0)
               (null writing-local-vars-from-inferior-code-body?))
          (tformat "~%Local Names:~%")
          (tformat "~%Local Names, Calling level ~a:~%" depth))
      (write-code-body-environment
        environment-description? local-var-vector?))
    (+ depth 1)))



(defun computation-instance-byte-code-body (computation-instance)
  (cond ((code-body-invocation-p computation-instance)
         (invocation-byte-code-body computation-instance))
        ((rule-instance-p computation-instance)
         (invocation-byte-code-body computation-instance))
        ((formula-invocation-p computation-instance)
         (invocation-byte-code-body computation-instance))
        ((inference-background-collection-p computation-instance)
         nil)
        ((of-class-p computation-instance 'g2-expression-cell)
         (g2-expression-cell-byte-code-body computation-instance))
        ;; Simulation?
        ((of-class-p computation-instance 'variable-or-parameter)
         (when current-simulation-runtime-structure
           (let ((byte-code-body
                   (simulation-byte-code-body-and-environment
                     computation-instance)))
             ;; This let discards the extra values from
             ;; simulation-byte-code-body-and-environment.
             byte-code-body)))
        (t
         nil)))

;; There are several existing functions:
;;
;; computation-instance-byte-code-body
;; get-byte-code-body-if-any
;; convert-frame-internals-to-vectors-as-necessary
;; disassemble-item-if-appropriate
;;
;; that try to do it uniformly.
;; Maybe they need to be refactored.
;; Cf. the comment of 8/13/98 of by dkuznick in proc-comp.lisp
(defun computation-instance-another-byte-code-body (computation-instance)
  (get-byte-code-body-if-any
   (cond ((procedure-invocation-p computation-instance)
	  (procedure-of-invocation computation-instance))
	 ((rule-instance-p computation-instance)
	  (ri-rule computation-instance))
	 (t computation-instance))
   nil))
   

(defparameter backtrace-depth-limit 20)

(defun write-stack-evaluator-backtrace
       (computation-frame computation-component-particulars
        computation-instance stack top-of-stack stack-frame-base)
  (declare (ignore top-of-stack))
  (loop with separator-format-control-string = "~%  <- "
        with skipping? = nil
        for count = 1 then (+f count 1)
        for first? = t then nil
        while computation-frame
        do
    (unless (or first? skipping?)
      (tformat separator-format-control-string))
    (frame-class-case computation-frame
      ((function-definition)
       (let* ((next-computation-frame
                (stack-frame-computation-frame stack stack-frame-base))
              (next-is-function?
                (function-definition-p next-computation-frame))
              (skipped-frames (-f count backtrace-depth-limit 1)))
         (cond ((and (>f count backtrace-depth-limit)
                     (not skipping?)
                     next-is-function?)
                (setq skipping? t))
               ((and skipping? (not next-is-function?))
                (tformat "[~a intervening function~a]"
                         skipped-frames
                         (if (=f skipped-frames 1) "" "s"))
                (tformat separator-format-control-string)
                (write-called-function-and-arguments stack stack-frame-base)
                (setq skipping? nil)
                (setq count 0))
               ((not skipping?)
                (write-called-function-and-arguments stack stack-frame-base)))
         (setq computation-frame next-computation-frame)
         (setq computation-component-particulars
               (stack-frame-computation-component-particulars
                 stack stack-frame-base))
         (setq stack-frame-base
               (stack-frame-old-stack-frame-base stack stack-frame-base))))
      ((procedure)
       (let* ((procedure-invocation
                (procedure-invocation-of-code-body computation-instance))
              (calling-procedure-invocation?
                (calling-procedure-invocation procedure-invocation)))
         (cond ((and (>f count backtrace-depth-limit)
                     (not skipping?)
                     calling-procedure-invocation?)
                (setq skipping? t))
               ((and skipping? (null calling-procedure-invocation?))
                (tformat "[~a intervening procedure~a]"
                         (-f count backtrace-depth-limit 1)
                         (if (=f (-f count backtrace-depth-limit 1) 1) "" "s"))
                (tformat separator-format-control-string)
                (write-procedure-invocation-instance-from-slot
                  procedure-invocation nil)
                (setq skipping? nil))
               ((not skipping?)
                (write-procedure-invocation-instance-from-slot
                  procedure-invocation nil)))

         (cond (calling-procedure-invocation?
                (setq computation-frame
                      (procedure-of-invocation calling-procedure-invocation?))
                (setq computation-component-particulars nil)
                (setq computation-instance
                      (base-code-body-invocation calling-procedure-invocation?)))
               (t
                (setq computation-frame nil)
                (setq computation-component-particulars nil)
                (setq computation-instance nil)
                (when (not (true-base-of-procedure-invocation-stack-p
                             procedure-invocation))
                  (tformat separator-format-control-string)
                  (let ((calling-invoc
                          (calling-code-body-invocation procedure-invocation)))
                    (cond ((g2gl-call-invocation-p-function calling-invoc)
                           (tformat "called from G2GL process ~NF"
                                    (calling-process-of-g2gl-call-invocation
                                      calling-invoc)))
                          (t
                           (twrite-string "called as server for a remote procedure call")))))))))
      ((rule)
       (denote-component-of-block
         t computation-component-particulars computation-frame)
       (let ((purposes (ri-purposes computation-instance)))
         (cond ((null purposes)                        ; Shouldn't happen
                nil)
               ((null (cdr-of-cons purposes))
                (twrite-string ", invoked by ")
                (write-rule-purpose (car-of-cons purposes)))
               (t
                (twrite-string ", invoked by the following:")
                (loop for purpose in purposes do
                  (tformat separator-format-control-string)
                  (twrite-string "  ")
                  (write-rule-purpose purpose)))))
       (setq computation-frame nil)
       (setq computation-component-particulars nil)
       (setq computation-instance nil))
      (t
        (denote-component-of-block
          t computation-component-particulars computation-frame)
        (setq computation-frame nil)
        (setq computation-component-particulars nil)
        (setq computation-instance nil)) )))

(defun write-stack-evaluator-top-frame
       (computation-frame computation-component-particulars
        computation-instance stack stack-frame-base)
  (frame-class-case computation-frame
    ((function-definition)
     (write-called-function-and-arguments stack stack-frame-base))
    ((procedure)
     (write-procedure-invocation-instance-from-slot
       (procedure-invocation-of-code-body computation-instance)
       nil))
    (t
      (denote-component-of-block
        t computation-component-particulars computation-frame))))

(defun write-rule-purpose (purpose)
  (cond ((and (consp purpose) (eq (car-of-cons purpose) 'backward-chaining))
         (tformat "backward chaining for ~NF" (cdr-of-cons purpose)))
        ((symbolp purpose)
         (twrite-string
           (case purpose
             ((user-menu-choice) "user menu choice selection")
             ((action-button) "action button selection")
             ((forward-chaining) "forward chaining")
             ((scanning) "scan interval")
             ((initializing) "initial rule invocation")
             ((focusing) "focus action")
             ((invoking) "invoke action")
             ;; The following clause should never happen.
             (otherwise
              #+development
              (cerror "Continue" "Unknown rule purpose ~a" purpose)
              "rule purpose not recorded"))))
        ;; The following clause should never happen.
        (t
         #+development
         (cerror "Continue" "Unknown rule purpose ~a" purpose)
         (twrite-string "rule purpose not recorded"))))

(defun get-call-sequence (depth computation-frame computation-instance stack-frame-base)
  (allocate-evaluation-sequence
    (loop with stack = global-stack
          for count from 1 to depth
          while computation-frame
          for current-frame
              = (frame-class-case computation-frame
                  ((function-definition)
                   (prog1 (stack-frame-function-definition stack stack-frame-base)
                     (setq computation-frame (stack-frame-computation-frame stack stack-frame-base))
                     (setq stack-frame-base (stack-frame-old-stack-frame-base stack stack-frame-base))))
                  ((procedure)
                   (let* ((procedure-invocation
                            (procedure-invocation-of-code-body computation-instance))
                          (calling-procedure-invocation?
                            (calling-procedure-invocation procedure-invocation)))
                     (prog1 (procedure-of-invocation procedure-invocation)
                       (cond (calling-procedure-invocation?
                              (setq computation-frame (procedure-of-invocation calling-procedure-invocation?))
                              (setq computation-instance (base-code-body-invocation calling-procedure-invocation?)))
                             (t
                              (setq computation-frame nil)
                              (setq computation-instance nil))))))
                  (t
                    (prog1 computation-frame
                      (setq computation-frame nil)
                      (setq computation-instance nil))))
          when (framep current-frame)
            collect current-frame using eval-cons)))

(defun get-computation-instance-for-block (block computation-frame computation-instance stack-frame-base)
  (loop with stack = global-stack
        while (and computation-frame (code-body-invocation-p computation-instance))
        for index from 0
        for computation-instance-for-current-frame = computation-instance
        for current-frame
            = (frame-class-case computation-frame
                ((function-definition)
                 (when (<=f 0 (stack-frame-first-argument-index stack-frame-base -1))
                   (prog1 (stack-frame-function-definition stack stack-frame-base)
                     (setq computation-frame (stack-frame-computation-frame stack stack-frame-base))
                     (setq stack-frame-base (stack-frame-old-stack-frame-base stack stack-frame-base)))))
                ((procedure)
                 (let* ((procedure-invocation
                         (procedure-invocation-of-code-body computation-instance))
                        (calling-procedure-invocation?
                         (calling-procedure-invocation procedure-invocation)))
                   (prog1 (procedure-of-invocation procedure-invocation)
                     (cond (calling-procedure-invocation?
                            (setq computation-frame (procedure-of-invocation calling-procedure-invocation?))
                            (setq computation-instance (base-code-body-invocation calling-procedure-invocation?)))
                           (t
                            (setq computation-frame nil)
                            (setq computation-instance nil))))))
                (t
                 (prog1 computation-frame
                   (setq computation-frame nil)
                   (setq computation-instance nil))))
        when (eq block current-frame)
          return (values computation-instance-for-current-frame index)))

;;;






;;;; Executing Computation Instances




;;; The macro `modify-major-stack-eval-locals' is called from context switching
;;; code.  It is responsible for fetching information from the
;;; current-computation-instance and other global variables and setqing local
;;; variables of stack eval inner.  The variables to be changed are
;;; byte-code-body, local-var-vector, and stack-program-counter.  This is
;;; actually also called from outer context switches as well.

;;; will-not-resume argument is used by compiler only; has no interpreted
;;; semantics. Indicates that the old current computation instance will
;;; not later be resumed at the following instruction.
(defmacro modify-major-stack-eval-locals (&optional go-to-beginning-p will-not-resume)
  (declare (ignore will-not-resume))
  `(let ((instance current-computation-instance))
     (let ((bcb (invocation-byte-code-body instance)))
       (when (null (byte-code-body-byte-vector bcb))
	 ;; Sometimes instance's INVOCATION-BYTE-CODE-BODY is reclaimed
	 ;; before it gets executed,
	 ;; while there is a valid one deeper in the structure.
	 ;; It can be avoided by changing DO-NOT-RECLAIM-OLD-VALUE-OVERRIDE?
	 ;; parameter of
	 ;; CHANGE-SLOT-DESCRIPTION-VALUE-WITHOUT-UPDATING-REPRESENTATIONS
	 ;; macro from NIL to T in CHANGE-SLOT-DESCRIPTION-VALUE-FUNCTION,
	 ;; frames5.lisp, but it can lead to leaks, so catch it here
	 (let ((b (computation-instance-another-byte-code-body instance)))
	   (when b
	     (setq bcb b)
	     (setf (invocation-byte-code-body instance) bcb)
	     (setf (invocation-constant-vector instance)
		   (byte-code-body-constant-vector bcb)))))
       (setq byte-code-body bcb))
     (setq cached-byte-code-body byte-code-body)
     (if-emitting-c-code
       (decache-local-var-vector)
       nil)
     (setq local-var-vector
           (invocation-local-var-vector instance))
     ;; Probably want to set saved-local-var-vector here as well.
     ;; Forward-reference issue -dkuznick, 8/14/03
     (setq constant-vector
           (invocation-constant-vector instance))
     (setq stack-program-counter
           ,(case go-to-beginning-p
             ((t)   `0)
             ((nil) `(invocation-stack-program-counter instance))
             (t
              `(if ,go-to-beginning-p
                   0
                   (invocation-stack-program-counter instance)))))
     ;; The below setq was added to fix bug HQ-4603240 - "Sometimes abort or BAD
     ;; INSTRUCTION message: rule or formula error in busy G2".  If this is not
     ;; done, after the context-switch cached-stack-program-counter may still be
     ;; pointing to something related to the old context, which is a corruption
     ;; {say if a stack-error gets thrown before cached-stack-program-counter
     ;; gets reset to something intelligent} -dkuznick, 8/14/03
     (setq cached-stack-program-counter stack-program-counter)))

;;; will-not-resume argument is used by compiler only; has no interpreted
;;; semantics. Indicates that the old current computation instance will
;;; not later be resumed at the following instruction.
(defmacro modify-minor-stack-eval-locals (&optional will-not-resume
                                                    stack-already-decached)
  (declare (ignore will-not-resume stack-already-decached))
  `(progn
     (setq instruction-vector (byte-code-body-byte-vector byte-code-body))
     (setq detailed-tracing? (detail-trace-message-will-be-written-p))
     (setq major-tracing? (major-trace-message-will-be-written-p))
     (if-emitting-c-code
       (go exit-stack-eval-inner)
       (when (and enable-running-compiled-code-p
                  (byte-cody-body-compiled-function byte-code-body))
         (go exit-stack-eval-inner)))))


;;; The function `execute-computation-instance' is called from the top level
;;; scheduler to begin execution of a scheduled computation.  This includes
;;; rules, procedures, cell expressions, and formulas (which are a special case
;;; of cell expressions).  Entrance of this function is a so-called `outer
;;; context switch' in that it switches execution of the stack evaluator to a
;;; computation instance from outside of the evaluator itself.  For as long as
;;; the time slice lasts and there are computations to perform, then `inner
;;; context switches' will happen from within the stack eval inner function.
;;; Both of these switches attempt to use the same facilities, leading to some
;;; clumsy code here, but better performance overall.

(defun-void execute-computation-instance (computation-instance)
  (when (queue-invocation-for-lock-if-necessary computation-instance)
    (if inside-breakpoint-p
        (schedule-computation-instance-execution-for-breakpoint computation-instance)
        (let ((fixnum-time-limit?
               (enter-or-reclaim-computation-instance-context computation-instance)))
          (unless (and current-schedule-task
                       (immediate-scheduled-task-p current-schedule-task))
            (setq cached-fixnum-start-time (get-fixnum-time)))
          (when current-computation-instance
            (let (byte-code-body
                   constant-vector
                   local-var-vector
                   stack-program-counter)
              (modify-major-stack-eval-locals)
              (stack-eval-for-execute-computation-instance
                byte-code-body
                constant-vector
                local-var-vector
                cached-fixnum-start-time
                fixnum-time-limit?
                stack-program-counter)
              (clear-computation-context-variables)))))))




;;; The macro `inner-context-switch-to-next-computation-instance' is used to
;;; change execution from within a stack instruction to a new computation
;;; instance.  It takes one required argument, which is the kind of computation
;;; context currently being exited.  This should be one of the following keyword
;;; values :code-body-invocation, :rule-instance, :formula-invocation, :unknown
;;; if it can't be predicted, or :none if the context has already been exited.
;;; This macro also takes a second optional argument, which is the next
;;; computation instance to be entered, or the keyword :none, if no new context
;;; should be entered and stack-eval should be exited.

;;; This macro first pops all values off the stack and exits the computation
;;; context for the currently executing computation instance.  It looks for a
;;; new computation instance by checking if there are any immediate invocations
;;; to run.  If there are none, then it checks the time slice to see if we can
;;; enter another, then fetches and attempts to enter the next instance on the
;;; scheduler queue for the current priority.  If it finds and enters one
;;; through the scheduled queue, then it resets the fixnum start time, and sets
;;; all major and minor context variables.  Once done, this macro returns and
;;; execution will proceed in the next computation.  If no computation instances
;;; were found, or if the time slice has expired, then this macro sets current
;;; computation instance to NIL, and performs a GO to exit-stack-eval.

(defmacro inner-context-switch-to-next-computation-instance
          (exit-kind &optional next-instance? does-not-resume)
  `(progn
     ,@(case exit-kind
         ((:unknown)
          `((cond ((code-body-invocation-p current-computation-instance)
                   (exit-computation-context-for-code-body-invocation
                     current-computation-instance stack-program-counter nil))
                  ((rule-instance-p current-computation-instance)
                   (exit-last-rule-instance-context stack-program-counter))
                  ((formula-invocation-p current-computation-instance)
                   (exit-computation-context-for-variable-formula
                     current-computation-instance)))))
         ((:code-body-invocation)
          `((exit-computation-context-for-code-body-invocation
             current-computation-instance stack-program-counter nil)))
         ((:rule-instance)
          `((exit-last-rule-instance-context stack-program-counter)))
         ((:formula-invocation)
          `((exit-computation-context-for-variable-formula
              current-computation-instance)))
         ((:none)
          nil)
         (otherwise
          (warn "Inner-context-switch given invalid exit-kind, ~a"
                exit-kind)))
     (setq cached-top-of-stack top-of-stack)
     (reclaim-top-of-stack)
     (setq top-of-stack -1)
     ;; This is a white lie; It's only true if
     ;; stack-frame-base is 0. But this is only false in functions,
     ;; and this never gets called inside functions.
     ;; This is needed to tell the constant-folder that stack-offset
     ;; is -1 at this point, so that the "branch 0" that typically follows
     ;; "complete-rule-instance" doesn't result in inconsistent offsets.
     ;; -alatto, 10/19/98
     (if-emitting-c-code
       (setq stack-offset -1)
       nil)
     ,@(cond ((and (eq exit-kind :none)
                   (eq next-instance? 'current-computation-instance))
              nil)
             ((eq next-instance? :none)
              `((setq current-computation-instance nil)))
             (next-instance?
              `((setq current-computation-instance ,next-instance?)))
             (t
              `((setq current-computation-instance nil)
                (setq fixnum-time-limit?
                      (fetch-and-enter-next-current-computation-instance
                        priority-of-current-task)))))
     ,(if (eq next-instance? :none)
          `(go exit-stack-eval)
          `(cond ((null current-computation-instance)
                  (go exit-stack-eval))
                 (t
                  (if-emitting-c-code
                    (if ,does-not-resume
                        (modify-major-stack-eval-locals nil t)
                        (modify-major-stack-eval-locals))
                    (modify-major-stack-eval-locals))
                  (modify-minor-stack-eval-locals))))))

(defun-void reclaim-top-of-stack ()
  (loop for index fixnum from 0 to cached-top-of-stack
        do
    (reclaim-if-evaluation-value (svref global-stack index))))

(defun-simple within-stack-eval-p ()
  current-computation-instance)

;;; The function `detect-deadlocks' returns nil if there is currently
;;; no deadlock. If there is a deadlock, it returns t if find-cycle is nil.
;;; If find-cycle is non-nil, it returns a proc-list of
;;; code-body-invocations, where each one is waiting for the following one in
;;; the list (and the last one is waiting for the first one); "X is waiting for
;;; Y" can mean any of
;;; 1. X has called Y.
;;; 2. Y is an "on error" block within X.
;;; 3. Y is one of a "do in parallel" or "do in parallel until one completes"
;;; block within X. Care is taken to ensure that only genuine deadlocks
;;; are returned in the case of "do in parallel until one completes"

;;; Algorithm to detect deadlocks is to first produce a list of
;;; `invocation-entries', one for each code-body invocation that might be involved
;;; in a deadlock (we find these by starting from method invocations that are
;;; waiting for a lock, and adding any invocation waiting for one of these
;;; invocations, and so forth). An invocation entry is a proc-list of length 3, containing
;;; a waiting invocation, the number of other invocations that must terminate before this
;;; one can be scheduled (this is one, except if this invocation has invoked a "do in parallel",
;;; (not a "do in parallel until one completes, in which case the number is 1)
;;; in which case it is the number of parallel invocations currently waiting, and the set
;;; of invocation entries that are waiting for this one. The algorithm finds a possible
;;; order in which things can execute. It does this by finding an entry whose "number of things
;;; waiting for" is 0, which could therefore execute first. It then subtracts one from the
;;; "number of things this invocation is waiting for" in all invocations that are waiting
;;; for this invocation, and repeats this process until either an order has been found
;;; for all invocations, proving that no deadlocks exist, or it has reached a point where
;;; all remaining invocations are waiting for at least one other invocation, proving
;;; that a deadlock exists. As an optimization, a separate list of "invocation entries
;;; currently waiting for 0 other invocations" is maintained, adding an entry to this
;;; list when it's "number of entries this is waiting for" is decremented to 0, and
;;; removing an entry when it's processed as "an invocation that could finish next".

;;; (This is just the standard non-recursive topological sort algorithm, except that
;;; for a "do in parallel until one completes" node, we use 1 instead of the number
;;; of invocations this invocation is waiting for).
(defun detect-deadlocks (find-cycle)
  ;; invocations-hash-table maps an invocation to its associated
  ;; invocation entry.
  (let ((invocations-hash-table
          (make-eq-hash-table 10 nil nil))
        invocations-to-process
        invocation-entries
        awaiting-serialization
        (number-of-unserialized-invocations 0))

    ;; Start with all the method invocations.
    (loop for method being each class-instance of 'procedure do
      ;; Maybe only push an invocation if it's waiting for a lock; this
      ;; will result in a smaller graph to search. -alatto, 10/12/06
      (let ((invocations (procedure-invocations method)))
        (when invocations
          (loop for invocation being each procedure-invocation of invocations do
            (proc-push invocation invocations-to-process)))))

    ;; Now follow call chains from all of them to find all invocations
    ;; that might be involved in deadlocks.
    (loop while invocations-to-process do
      (let ((invocation (proc-pop invocations-to-process)))
        (unless (eq-gethash invocations-hash-table invocation nil)
          (let ((invocation-entry
                  (proc-list
                    invocation
                    (cond
                      ((invocation-holding-lock-this-is-waiting-for invocation) 1)
                      ((waiting-for-do-in-parallel-until-one-completes invocation)
                       (if (called-code-bodies invocation) 1 0))
                      (t (length (called-code-bodies invocation))))
                    nil)))
            (setf (eq-gethash invocations-hash-table invocation) invocation-entry)
            (proc-push invocation-entry invocation-entries)
            (incff number-of-unserialized-invocations)
            (loop for waited-for-invocation in
                  ;; no need to follow
                  ;; invocation-holding-lock-this-is-waiting-for here,
                  ;; since that's always an invocation of an instance of a
                  ;; method, so it's already on the list.
                  (called-code-bodies invocation) do
              (unless (eq-gethash invocations-hash-table waited-for-invocation nil)
                (proc-push waited-for-invocation invocations-to-process)))))))

    ;; For each invocation entry, fill in the third element of the list
    ;; with the invocation entries that are waiting for it.
    (loop for invocation-entry in invocation-entries do
      (let ((invocation (car invocation-entry)))
        (loop for waiting-invocation in
              (invocations-waiting-for-lock-held-by-this-invocation
                invocation) do
          (proc-push
            (eq-gethash invocations-hash-table waiting-invocation nil)
            (third invocation-entry)))
        (when (code-body-caller invocation)
          (proc-push
            (eq-gethash invocations-hash-table
                        (code-body-caller invocation)
                        nil)
            (third invocation-entry)))
        (when (=f (second invocation-entry) 0)
          (proc-push invocation-entry awaiting-serialization))))

    (reclaim-eq-hash-table invocations-hash-table)

    ;; Use the topological sort algorithm to find a possible execution
    ;; order for the invocations; all those that we are unable to
    ;; serialize (if any) are deadlocked, or waiting for deadlocked
    ;; invocations
    (loop while awaiting-serialization do
      (let ((invocation-entry (proc-pop awaiting-serialization)))
        (decff number-of-unserialized-invocations)
        (loop for waiter in (third invocation-entry) do
          (when (=f (decff (second waiter)) 0)
            (proc-push waiter awaiting-serialization)))))

    (prog1
        (if (=f number-of-unserialized-invocations 0)
            nil
            (if find-cycle
                (find-cycle-in-invocation-entry-list invocation-entries)
                t))
      (loop for entry in invocation-entries do
        (reclaim-proc-list (third entry))
        (reclaim-proc-list entry))
      (reclaim-proc-list invocation-entries))))

(defun waiting-for-do-in-parallel-until-one-completes (invocation)
  ;; find the code body, find the next instruction to execute, see if it's
  ;; abort-called-code-bodies.
  (eq (stack-instruction-name
        (instruction-description-for-op-code
          (byte-vector-aref (byte-code-body-byte-vector
                              (invocation-byte-code-body invocation))
                            (invocation-stack-program-counter invocation))))
      'abort-called-code-bodies))



(defun find-cycle-in-invocation-entry-list (invocation-entries)
  (loop for entry in invocation-entries do
    (unless (=f (second entry) 0)
      (let ((cycle (find-cycle-or-extend-path-in-invocation-entry-list entry)))
        (when cycle (return cycle))))
        #+development finally
          #+development
          (let ((*print-circle* t))
            (cerror "Continue" "Failure to find cycle in deadlock graph ~S" invocation-entries))))



;;; The function `find-cycle-or-extend-path-in-invocation-entry-list'
;;; returns two values. If the second value is nil, the first value
;;; is either nil, if the argument is not contained in any cycle, or a cycle of
;;; invocations, where each one is waiting for the previous one,
;;; and the first one is waiting for the last one. If the second value
;;; is non-nil, then the second value is an invocation, and the first
;;; value is a list of invocations, where the first entry in the list
;;; is the invocation that is the car of the argument to this call
;;; to find-cycle-or-extend-path-in-invocation-entry-list, the last invocation
;;; in the list is also given by the second returned value, every entry
;;; in the list is waiting for the previous one (though not cyclicly), and
;;; it is known that this path can be extended to a cycle, because the
;;; returned second value was an argument to a call to
;;; find-cycle-or-extend-path-in-invocation-entry-list above this one in
;;; the call tree.

;;; In the case where the argument is not part of any cycle, it, and all entries
;;; that are waiting for it, are marked as such by setting the second element
;;; of the invocation entry to 0, so that these are not searched again in the search
;;; for a cycle.
;;;
;;; To put it another way, as the function
;;; find-cycle-or-extend-path-in-invocation-entry-list is called
;;; recursively, it wanders through the graph of invocations that are
;;; deadlocked, backtracking if it fails to find a cycle, marking each one currently
;;; on the stack of recursive invocations by changing the second element of
;;; the list to t. When it finds an entry it has seen before, and has
;;; therefore been called on a cycle of invocation entries, it returns
;;; a list of that entry. Each recursively calling instance of
;;; find-cycle-or-extend-path-in-invocation-entry-list tacks its argument
;;; onto the returned list, until that list is a cycle. calls higher
;;; up on the call tree, representing invocations on a path that led to
;;; the cycle, just return the cycle they are passed by the recursive call,
;;; which is what is ultimately returned.

(defun find-cycle-or-extend-path-in-invocation-entry-list (entry)
  (if (eq (second entry) t)
      (values (proc-list (car entry)) (car entry))
      (loop for waiting-for-this in (third entry) do
        (cond
          ((eq waiting-for-this entry)
           ;; This would only happen if an entry is waiting for itself.
           ;; This should never happen, but we return the correct result
           ;; (a cycle of length one) for completeness.
           (return (values (proc-list (car entry)) nil)))
          ((eql (second waiting-for-this) 0) (return (values nil nil)))
          (t
           (setf (second entry) t)
           (multiple-value-bind (path-or-cycle end-of-path)
               (find-cycle-or-extend-path-in-invocation-entry-list waiting-for-this)
             (if end-of-path
                 (if (eq end-of-path (car entry))
                     (return (values path-or-cycle nil))
                     (return (values (proc-cons (car entry) path-or-cycle) end-of-path)))
                 (if path-or-cycle
                     (return (values path-or-cycle nil))
                     (setf (second entry) 0)))))))))

(defun abort-to-break-deadlock (code-body-invocation)
  (signal-code-body-invocation-error
   code-body-invocation
   ;error
   'g2-deadlock-error
   ;error-level
   1
   ;error-text
   (copy-text-string "Procedure aborted to break a deadlock")
   ;byte-code-body?
   (invocation-byte-code-body code-body-invocation)
   ; program-counter?
   ;; use nil instead of
   ;; (invocation-stack-program-counter code-body-invocation),
   ;; because the current instruction is misleading so we don't want
   ;; it in the abort message.
   nil
   ;stack?
   global-stack
   ;top-of-stack?
   -1
   ;suppress-debugging-info?
   t))

;;; The function `detect-and-break-deadlocks' will continue to detect and break deadlocks
;;; until no further deadlocks remain. The choice of which invocation to abort is made
;;; using the following two criteria:
;;; 1. When possible, abort a procedure that will result in the error being handled by
;;; an on-error block.
;;; 2. Within a call chain, prefer to abort the called procedure, rather than the caller.
;;; This will avoid unnecessarily aborting other called procedures in the case of a
;;; do-in-parallel, as well as providing a more informative backtrace. It also
;;; ensures that the aborted procedure is waiting for a deadlock, rather than waiting
;;; for something it has called, which will be what is expected by the user, and provide
;;; a clearer indication of the cause of the deadlock.

(defun detect-and-break-deadlocks ()
  (let ((deadlock-found nil))
    (loop
      (let ((invocation-cycle (detect-deadlocks t)))
        (unless invocation-cycle
          (return-from detect-and-break-deadlocks deadlock-found))
        (setf deadlock-found t)
        (break-one-deadlock invocation-cycle)))))

(defun-void break-one-deadlock (invocation-cycle)
  (let ((candidate-procedure-to-abort-cons invocation-cycle))
    (loop for candidate on invocation-cycle do
      (when (find-error-handler-for-code-body-invocation
              'g2-deadlock-error (car candidate))
        (setq candidate-procedure-to-abort-cons candidate)
        (loop-finish)))
    ;; Now we've found an invocation whose abort will be handled, if possible,
    ;; or an arbitrary one in the cycle, otherwise. Now walk around the who-waits-for-who
    ;; cycle to find something waiting for a lock, rather than waiting for a called
    ;; thing to return.
    (loop
      (let ((next (or (cdr candidate-procedure-to-abort-cons) invocation-cycle)))
        (if (eq (code-body-caller (car next)) (car candidate-procedure-to-abort-cons))
            (setq candidate-procedure-to-abort-cons next)
            (loop-finish))))
    (abort-to-break-deadlock (car candidate-procedure-to-abort-cons)))
  (reclaim-proc-list invocation-cycle))

(defun detect-deadlocks-for-ui ()
  (if (detect-deadlocks nil)
      (notify-user "Deadlock detected: Use detect-and-break-deadlocks to abort deadlocked procedures")
      (notify-user "No deadlock detected")))

(defun detect-and-break-deadlocks-for-ui ()
  (unless (detect-and-break-deadlocks)
      (notify-user "No deadlock detected")))

;;; Returns true if a deadlock was found, and false otherwise.
(defun-for-system-procedure g2-detect-deadlocks ()
  (declare (keeps-g2-local-variables-valid t))
  (make-evaluation-boolean-value (detect-deadlocks nil)))


;;; Returns true if a deadlock was found, and false otherwise.
;;; If deadlock exists, breaks deadlocks until no deadlocks exist.
(defun-for-system-procedure g2-detect-and-break-deadlocks ()
  (make-evaluation-boolean-value (detect-and-break-deadlocks)))

(def-system-variable automatic-deadlock-detection-task stack-utils nil)
(def-system-variable automatic-deadlock-detection-frequency stack-utils nil)

(defun set-deadlock-detection-frequency (new-frequency force?)
  (unless (and
            (not force?)
            (or (and (null new-frequency)
                     (null automatic-deadlock-detection-frequency))
                (and new-frequency
                     automatic-deadlock-detection-frequency
                     (=f
                       new-frequency
                       automatic-deadlock-detection-frequency))))
    (cancel-task automatic-deadlock-detection-task)
    (when new-frequency
      (with-temporary-gensym-float-creation set-deadlock-detection-frequency
            (let ((frequency-as-float (float new-frequency)))
              (with-future-scheduling
                  (automatic-deadlock-detection-task
                    0
                (+e (gensym-get-unix-time) frequency-as-float)
                frequency-as-float)
            (detect-and-break-deadlocks))))
      (setq automatic-deadlock-detection-frequency new-frequency))))



;;; `handle-extend-current-text-string-error' - called (via funcall) from
;;; UNICODE.  It can't be defined there because it needs to use stack-error and
;;; wants to use within-stack-eval-p.

(defun handle-extend-current-text-string-error ()
  (if (within-stack-eval-p)
      (stack-error cached-top-of-stack
                   #.extend-current-text-string-error-message)
      (error #.extend-current-text-string-error-message)))
